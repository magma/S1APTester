
/********************************************************************20**
  
        Name:     Common Domain Name Server Library
    
        Type:     header file 
  
        Desc:     common library for Accessing DNS Services 
                    
        File:     cm_dns.c

        Sid:      cm_dns.c@@/main/18 - Wed Dec  1 18:29:20 2010
  
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


#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* General layer */
#include "ssi.h"           /* System services */
#include "cm_inet.h"       /* Common Sockets Library */
#include "cm_tpt.h"        /* Common Transport Defines */
#include "cm_dns.h"        /* common DNS library */

/* header/extern include files (.x) */
#include "gen.x"           /* General layer */
#include "ssi.x"           /* System services */
#include "cm_inet.x"       /* Common Sockets Library */
/* Removing the cm_tkns.x file*/
#include "cm_tpt.x"        /* Common Transport Definitions */
#include "cm_dns.x"        /* common DNS library */
#include "cm_lib.x"        /* Common Library */



/* local defines */

/* local externs */

/* forward references */

PRIVATE S16 cmDnsEncodeQuery ARGS((
        U16             rqstId,        /* Request Identifier */
        CmDnsQueryInfo  *queryInfo,    /* Query Information */
        Buffer          *mBuf          /* Message Buffer for encoding */
      )); 

PRIVATE S16 cmDnsEncode2782SrvQry ARGS((
        CmDnsQueryInfo  *queryInfo,    /* Query Information */
        U8              *qName,        /* String where query is being packed */
        U16             *qNameIdx      /* Current Index into string */
      )); 

/* public variable declarations */

/* public variable definitions */
PUBLIC CmDnsSuppSrvcs srvcs[CM_DNS_MAX_SUPP_SRVCS]=
{
   {"_http",   5},
   {"_pop",    4},
   {"_telnet", 7},
   {"_ftp",    4},
   {"_h2250-annex-g", 14},
   {"_sip",    4},
   {"_im", 3},
   {"_sips",    5},
   {"_pres",    5}
};

PUBLIC CmDnsSuppProtos protos[CM_DNS_MAX_SUPP_PROTOS]=
{
   {"_ip",   3},
   {"_tcp",  4},
   {"_udp",  4},
   {"_sip",  4},
   {"_tcp",  4},
   {"_sctp",  5}
};




/************************************************************************
            Initialize DNS CB
 ************************************************************************/
/*
*
*
*       Fun:   cmDnsInitDnsCb
*
*       Desc:  Initializes a DNS Control Block. Parameters are:
*
*              dnsCb        -  DNS Control Block. Memory Owned by the user
*              dbgInfo      -  Debug Information.
*              dnsTptAddr   -  DNS Transport Address
*              txFunc       -  Function to be used for transmission of request
*                              to DNS. The function is implementd in user's 
*                              layer
*              rxFunc       -  Function used by library to pass response 
*                              received from DNS to the user. The function is
*                              implemented in user's layer
*              sMem         -  Static Memory Region and Pool to be used by
*                              the library for memory allocation
*              elmnt        -  Element Using Library
*              tapaEnt      -  Tapa Entity using library
*              reqIdLstSz   -  Request Id List Size
*
*       Ret:   ROK      - initialization successful
*              RFAILED  - initialization failed, lack of memory
*
*       Notes: None
*
*       File:  cm_dns.c
*
*/

#ifdef ANSI
PUBLIC S16 cmDnsInitDnsCb
(
CmDnsCb            *dnsCb,             /* DNS Information Control Block */
CmDnsDbgInfo       *dbgInfo,           /* Debug Information */
#ifndef CM_MULTIPLE_DNS_SERVER
CmTptAddr          *dnsTptAddr,        /* DNS Transport Address */
#else 
CmTptAddr          dnsTptAddr[],        /* cm_dns_c_001.main_12: DNS Transport Addr List */
U16                numberOfDnsServers,  /* cm_dns_c_001.main_12: Number of DNS servers */
#endif
USRTXFUNC          txFunc,             /* User Tx Function */
USRRXFUNC          rxFunc,             /* User Rx Function */
Mem                *sMem,              /* Static Memory Region and Pool */
U16                entId,              /* Entity Id */
EntityId           *tapaEnt,           /* TAPA Entity Id */
U16                reqIdLstSz          /* Request Id List Size */
)
#else
#ifndef CM_MULTIPLE_DNS_SERVER
PUBLIC S16 cmDnsInitDnsCb (dnsCb, dbgInfo, dnsTptAddr, txFunc, rxFunc, sMem, 
                           entId, tapaEnt, reqIdLstSz)
#else
PUBLIC S16 cmDnsInitDnsCb (dnsCb, dbgInfo, dnsTptAddr, numberOfDnsServers, txFunc, rxFunc, sMem, 
                           entId, tapaEnt, reqIdLstSz)
#endif
CmDnsCb            *dnsCb;             /* DNS Information Control Block */
CmDnsDbgInfo       *dbgInfo;           /* Debug Information */
#ifndef CM_MULTIPLE_DNS_SERVER
CmTptAddr          *dnsTptAddr;        /* DNS Transport Address */
#else
CmTptAddr          dnsTptAddr[];        /* DNS Transport Address */
U16                numberOfDnsServers;  /* Number of DNS servers */
#endif
USRTXFUNC          txFunc;             /* User Tx Function */
USRRXFUNC          rxFunc;             /* User Rx Function */
Mem                *sMem;              /* Static Memory Region and Pool */
U16                entId;              /* Entity Id */
EntityId           *tapaEnt;           /* TAPA Entity Id */
U16                reqIdLstSz;         /* Request Id List Size */
#endif
{
   U32             *tmp;               /* Temporary Variable */
   U16             idx;                /* Loop Index */
   CmDnsReqIdLst   *reqLst;            /* Request Id List */

   TRC2(cmDnsInitDnsCb)

#if (ERRCLASS & ERRCLS_DEBUG)
   if ((dnsCb == NULLP) || (dbgInfo == NULLP) || (dnsTptAddr == NULLP) ||
        (sMem == NULLP) || (tapaEnt == NULLP) || (reqIdLstSz == 0))
   {
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
           "cmDnsInitDnsCb(): Invalid Parameters passed\n");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   /* Check if DNS Control Block is already initialised */
   if (dnsCb->state == CM_DNS_CB_OK2USE)
      RETVALUE(ROKDNA);

   /* Copy DNS Transport Address */
#ifndef CM_MULTIPLE_DNS_SERVER
   cmMemcpy((U8 *)&(dnsCb->dnsTptAddr), (CONSTANT U8 *)dnsTptAddr, 
            sizeof(CmTptAddr));
#else
   /*-- cm_dns_c_001.main_12: Copy all the DNS server addresses 
      into dnsCb --*/
   for ( idx = 0; idx < numberOfDnsServers; idx++)
   {
      /* Copy tptAddr into DnsCb */
      cmMemcpy((U8 *)&(dnsCb->dnsTptAddr[idx]), (CONSTANT U8 *)&(dnsTptAddr[idx]), 
               sizeof(CmTptAddr));
   }
   dnsCb->numberOfDnsServers = numberOfDnsServers;
#endif

   /* Initialise user transmission and reception functions */
   dnsCb->txFunc = txFunc;
   dnsCb->rxFunc = rxFunc;

   /* update memory region and pool */
   dnsCb->sMem.region = sMem->region;
   dnsCb->sMem.pool   = sMem->pool;

   /* Copy Service User Information */
   dnsCb->tapaEnt.ent  = tapaEnt->ent;
   dnsCb->tapaEnt.inst = tapaEnt->inst;
   dnsCb->entId        = entId;

   /* Copy Debug Information */
   dnsCb->dbgInfo.dbgMask   = dbgInfo->dbgMask;
   dnsCb->dbgInfo.prntBuf   = dbgInfo->prntBuf;
   dnsCb->dbgInfo.layerName = dbgInfo->layerName;

   /* Copy Request Id List Size */
   dnsCb->requestIdLstSz = reqIdLstSz;

   /* Allocate memory for pointers in the request list */
   if ((SGetSBuf(sMem->region, sMem->pool, (Data **) &tmp, 
                 sizeof(CmDnsReqIdLst *))) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
           "cmDnsInitDnsCb(): RequestIdLst Pointer Memory Alloc Failed \n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

      RETVALUE(RFAILED);
   }

   dnsCb->dnsReqLst = (CmDnsReqIdLst **)tmp;

   /* Allocate memory for request Id list */
   tmp = NULLP;
   if ((SGetSBuf(sMem->region, sMem->pool, (Data **) &tmp,
                 (reqIdLstSz * sizeof(CmDnsReqIdLst)))) != ROK)
   {
      SPutSBuf(sMem->region, sMem->pool, (Data *)(dnsCb->dnsReqLst), 
               sizeof(CmDnsReqIdLst *));

#if (ERRCLASS & ERRCLS_DEBUG)
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
           "cmDnsInitDnsCb(): RequestIdLst Memory Alloc Failed \n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

      RETVALUE(RFAILED);
   }

   *(dnsCb->dnsReqLst) = (CmDnsReqIdLst *)tmp;

   /* 
    * Initialise the request Id list - It is a linked list implementation of array
    * wherein next free index is stored in the available index..with end of the list
    * marked specifically as last element in the array
    */
   reqLst = (*(dnsCb->dnsReqLst));

   for (idx = 0; idx < reqIdLstSz; idx++)
   {
      reqLst[idx].indx  = idx+1;
      reqLst[idx].usrPtr = NULLP;
   }

   reqLst[idx-1].indx = CM_DNS_INVALID_RQSTID;

   /* Next available free request Id List */
   dnsCb->nxtRequestId   = 0;
   /*-- cm_dns_c_001.main_16: Intialising last freed requestId--*/
   dnsCb->lastRequestId   = idx-1;

   /* Update DNS Control Block State */
   dnsCb->state = CM_DNS_CB_OK2USE;

   RETVALUE(ROK);

} /* end of cmDnsInitDnsCb() */




/************************************************************************
            DeInitialize DNS CB
 ************************************************************************/

/*
*
*       Fun:   cmDnsDeInitDnsCb
*
*       Desc:  De-Initializes a DNS Control Block and frees memory allocated.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PUBLIC Void cmDnsDeInitDnsCb
(
CmDnsCb            *dnsCb              /* DNS Information Control Block */
)
#else
PUBLIC Void cmDnsDeInitDnsCb (dnsCb)
CmDnsCb            *dnsCb;             /* DNS Information Control Block */
#endif
{
 
   TRC2(cmDnsDeInitDnsCb)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (dnsCb == NULLP)
   {
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
           "cmDnsDeInitDnsCb(): Invalid Parameters passed\n");
      RETVOID;
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   /* Check if DNS Control Block is already initialised */
   if (dnsCb->state == CM_DNS_CB_NOTOK2USE)
      RETVOID;

   if (*(dnsCb->dnsReqLst) == NULLP)
      RETVOID;

   /* Update DNS Control Block State */
   dnsCb->state = CM_DNS_CB_NOTOK2USE;

   /* Release Memory for the Request Id List */
   SPutSBuf (dnsCb->sMem.region,dnsCb->sMem.pool,(Data *) *(dnsCb->dnsReqLst),
             (dnsCb->requestIdLstSz * sizeof(CmDnsReqIdLst)));

   /* Release memory for list pointer */
   SPutSBuf (dnsCb->sMem.region, dnsCb->sMem.pool, 
             (Data *) dnsCb->dnsReqLst, sizeof(CmDnsReqIdLst *));

   RETVOID;

} /* end of cmDnsDeInitDnsCb() */





/************************************************************************
             Generate Request to DNS
 ************************************************************************/
/*
*
*       Fun:   cmDnsGenRslvReq
*
*       Desc:  Generates a resolve request to be  DNS
*
*       Ret:   ROK     - Request Generated Successfully
*              RFAILED - Failed
*
*       Notes: None
*
*       File:  cm_dns.c
*
*/
/* cm_dns_c_001.main_17 - correcting non-ANSI compilation error  */
#ifndef CM_MULTIPLE_DNS_SERVER
#ifdef ANSI
PUBLIC S16 cmDnsGenRslvReq
(
CmDnsCb            *dnsCb,             /* DNS Information Control Block */
Ptr                usrTxFuncParam,     /* User Tx Func Param */
CmDnsQueryInfo     *queryInfo,         /* Query Information */
Ptr                usrPtr,             /* Associated User Entry */
U16                *requestId,         /* Request Id for DNS Resolve Request */
Mem                *dMem               /* Dynamic Memory Region and Pool */
)
#else
PUBLIC S16 cmDnsGenRslvReq (dnsCb, usrTxFuncParam, queryInfo, usrPtr, requestId,
                            dMem)
CmDnsCb            *dnsCb;             /* DNS Information Control Block */
Ptr                usrTxFuncParam;     /* User Tx Func Param */
CmDnsQueryInfo     *queryInfo;         /* Query Information */
Ptr                usrPtr;             /* Associated User Entry */
U16                *requestId;         /* Request Id for DNS Resolve Request */
Mem                *dMem;              /* Dynamic Memory Region and Pool */
#endif
#else/*CM_MULTIPLE_DNS_SERVER*/
#ifdef ANSI
PUBLIC S16 cmDnsGenRslvReq
(
CmDnsCb            *dnsCb,             /* DNS Information Control Block */
Ptr                usrTxFuncParam,     /* User Tx Func Param */
CmDnsQueryInfo     *queryInfo,         /* Query Information */
Ptr                usrPtr,             /* Associated User Entry */
U16                *requestId,         /* Request Id for DNS Resolve Request */
Mem                *dMem,              /* Dynamic Memory Region and Pool */
U8                 currentDnsServer    /*Current DNS server index for this query*/
)
#else
PUBLIC S16 cmDnsGenRslvReq (dnsCb, usrTxFuncParam, queryInfo, usrPtr, requestId, 
                            dMem, currentDnsServer)
CmDnsCb            *dnsCb;             /* DNS Information Control Block */
Ptr                usrTxFuncParam;     /* User Tx Func Param */
CmDnsQueryInfo     *queryInfo;         /* Query Information */
Ptr                usrPtr;             /* Associated User Entry */
U16                *requestId;         /* Request Id for DNS Resolve Request */
Mem                *dMem;              /* Dynamic Memory Region and Pool */
U8                 currentDnsServer;   /* Current DNS server index for this query*/
#endif
#endif/*CM_MULTIPLE_DNS_SERVER*/
{
   U16             rqstId;             /* Request Identifier */
   CmDnsReqIdLst   *reqLst;            /* Request Id List */
   Buffer          *mBuf;              /* Message Buffer */

   TRC2(cmDnsGenRslvReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if ((dnsCb == NULLP) || (queryInfo == NULLP) || 
       (queryInfo->qNameLen == 0) || (requestId == NULLP) || (dMem == NULLP))
   {
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
           "cmDnsGenRslvReq(): Invalid Parameters passed\n");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   /* Initialise variables */
   mBuf     = NULLP;

   /* Check if we have a request Id available */
   if (dnsCb->nxtRequestId == CM_DNS_INVALID_RQSTID)
      RETVALUE(RFAILED);

   /* Allocate memory for the message buffer */
   if ((SGetMsg(dMem->region, dMem->pool, &mBuf)) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
           "cmDnsGenRslvReq(): Failed to allocate message buffer \n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);
   }

   /* Obtain a request Id */
   CM_DNS_GET_FREE_REQID(dnsCb, rqstId);

   if ((cmDnsEncodeQuery(rqstId, queryInfo, mBuf)) != ROK)
   {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
           "cmDnsGenRslvReq(): Failed to encode query \n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);
   }

   /* Store the associated user entry and query information in request list */
   reqLst =  *(dnsCb->dnsReqLst);

   reqLst[rqstId].usrPtr = usrPtr;

   /* Pass the allocated request Id to the user */
   *requestId = rqstId;

   /* Everything went well...transmit the data packet using txFunc */
#ifndef CM_MULTIPLE_DNS_SERVER
   dnsCb->txFunc(usrTxFuncParam, &(dnsCb->dnsTptAddr), mBuf);
#else
   /* cm_dns_c_001.main_12: dnsCb now has a list of DNS servers
      we need to use the current one. */
   dnsCb->txFunc(usrTxFuncParam, &(dnsCb->dnsTptAddr[currentDnsServer]), mBuf);
#endif

   RETVALUE(ROK);

} /* end of cmDnsGenRslvReq() */



/************************************************************************
                           Encode Query
 ************************************************************************/
/*
*
*       Fun:   cmDnsEncodeQuery
*
*       Desc:  Encodes a query into a message buffer 
*
*       Ret:   ROK      - Implies Success
*              RFAILED  - Implies Failure
*
*       Notes: None
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PRIVATE S16 cmDnsEncodeQuery 
(
U16                rqstId,             /* Request Identifier */
CmDnsQueryInfo     *queryInfo,         /* Query Information */
Buffer             *mBuf               /* Message Buffer for encoding */
)
#else
PRIVATE S16 cmDnsEncodeQuery (rqstId, queryInfo, mBuf)
U16                rqstId;             /* Request Identifier */
CmDnsQueryInfo     *queryInfo;         /* Query Information */
Buffer             *mBuf;              /* Message Buffer for encoding */
#endif
{
   U16             byteIdx;            /* Byte Index */
   U16             lblLenIdx;          /* Index into a label */
   U16             lblIdx;             /* Index into Label String */
   U16             parsedLen;          /* Parsed Label Length */
   U16             qNameIdx;           /* QNAME Index */
   U8              *qName;             /* QNAME */
   U8              buf[CM_DNS_QRY_SZ]; /* Flat Buffer for composing Query */

   TRC2(cmDnsEncodeQuery)

   /* Check for support QNAME */
   if ((queryInfo->qType != CM_DNS_QTYPE_A)  
#ifdef CM_AAAA
       && (queryInfo->qType != CM_DNS_QTYPE_AAAA)
#endif /* CM_AAAA */
#ifdef CM_NAPTR
       && (queryInfo->qType != CM_DNS_QTYPE_NAPTR)
#endif /* CM_NAPTR */
       && (queryInfo->qType != CM_DNS_QTYPE_SRV)
       )
   {
      /* Unsupported QNAME */
      RETVALUE(RFAILED);
   }

   /* Check for QCLASS */
   if (queryInfo->qclass != CM_DNS_QCLASS_IN)
   {
      /* Unsupported QCLASS */
      RETVALUE(RFAILED);
   }

   /* Initialise variables */
   byteIdx  = 0;
   cmMemset (buf, 0, CM_DNS_QRY_SZ);

   /* Start Composing the request buffer - encode 16 bit request Id */
   buf[byteIdx++] = GetHiByte(rqstId);
   buf[byteIdx++] = GetLoByte(rqstId);

   /*
    * We support only standard query at this point of time and recursion may or
    * may not be desired...depending on the value of the define
    * 3rd Byte in header has all zero's except possibly recursion desired (RD)
    * And 4th header byte is zero
    */
   buf[byteIdx++] = CM_DNS_RECURSION_DESIRED;
   buf[byteIdx++] = 0;   

   /* QDCOUNT - 16 bit..value is one */
   buf[byteIdx++] = 0;   
   buf[byteIdx++] = 1;   

   /* 
    * ANCOUNT, NSCOUNT, ARCOUNT are all zero - increment byte index to
    * point to Question Section Format in flat buffer
    */
   byteIdx = CM_DNS_MSG_HEADER_SIZE;

   /* Fill QNAME Section - depending upon the QNAME type */
   qName    = &(buf[byteIdx]);
   qNameIdx = 0;

   /* 
    * Encode Packet in accordance with QTYPE..Currently we implement RFC 1035 
    * and RFC 2782. For support of these two RFC's, RFC 2782 has some difference 
    * in query format portion which is being done as part of a separate function
    * Common portion between 1035 and 2782 is implemented here after switch 
    * statement
    */
   switch (queryInfo->qType)
   {
      case CM_DNS_QTYPE_SRV:
      {
         if ((cmDnsEncode2782SrvQry (queryInfo, qName, &qNameIdx)) != ROK)
            RETVALUE(RFAILED);
      }
      break;

      case CM_DNS_QTYPE_A:
#ifdef CM_AAAA
      case CM_DNS_QTYPE_AAAA:
#endif /* CM_AAAA */
         break;

#ifdef CM_NAPTR
      case CM_DNS_QTYPE_NAPTR:
      break;
#endif /* CM_NAPTR */

     default:
        RETVALUE(RFAILED);
   }

   /* From here Common portion for qType = SRV Record or Host Record Starts */
   parsedLen = 0;
   lblIdx  = 0;

   /* Pack QNAME into the string in the required format */
   while (parsedLen < queryInfo->qNameLen)
   {
      lblLenIdx = qNameIdx++;     /* Index where length is to be inserted */

      for (;;)
      {
         if (queryInfo->qName[lblIdx] == CM_DNS_LABEL_END) 
         {
            /* Move to next Index */
            lblIdx++;

            /* Insert the length of the label at saved index */
            qName[lblLenIdx] = (qNameIdx - lblLenIdx-1);
            parsedLen++;
            break;
         }

         /* Store the character in the string */
         qName[qNameIdx++] = queryInfo->qName[lblIdx++];
         parsedLen++;

         if (parsedLen >= queryInfo->qNameLen)
         {
           qName[lblLenIdx] = (qNameIdx - lblLenIdx-1);
           break;
         }

      } /* end of for loop */
   }

   /* fill the root domain name - i.e. length 0 */
   qName[qNameIdx++] = 0;

   /* Fill the QTYPE */
   qName[qNameIdx++] = GetHiByte(queryInfo->qType);
   qName[qNameIdx++] = GetLoByte(queryInfo->qType);

   /* Fill the QCLASS */
   qName[qNameIdx++] = GetHiByte(queryInfo->qclass);
   qName[qNameIdx++] = GetLoByte(queryInfo->qclass);

   /* Query has been composed - get the total length of the buffer */
   byteIdx += qNameIdx;

   /* Compose the message buffer */
   if ((SAddPstMsgMult (buf, (MsgLen) byteIdx, mBuf)) != ROK)
      RETVALUE(RFAILED);

   RETVALUE(ROK);

} /* end of cmDnsEncodeQuery() */





/************************************************************************
                           Encode 2782 Query
 ************************************************************************/

/*
*
*       Fun:   cmDnsEncode2782SrvQry
*
*       Desc:  Encodes a RFC 2782 Query specific portion into a string
*
*       Ret:   ROK      - Implies Success
*              RFAILED  - Implies Failure
*
*       Notes: None
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PRIVATE S16 cmDnsEncode2782SrvQry 
(
CmDnsQueryInfo     *queryInfo,         /* Query Information */
U8                 *qName,             /* String where query is being packed */
U16                *qNameIdx           /* Current Index into string */
)
#else
PRIVATE S16 cmDnsEncode2782SrvQry (queryInfo, qName, qNameIdx)
CmDnsQueryInfo     *queryInfo;         /* Query Information */
U8                 *qName;             /* String where query is being packed */
U16                *qNameIdx;          /* Current Index into string */
#endif
{
   U8              lblLen;             /* Label Length */

   TRC2(cmDnsEncode2782SrvQry)

   /* Encode Supported Services */
   switch (queryInfo->service)
   {
      case CM_DNS_SERVICE_HTTP:
      case CM_DNS_SERVICE_POP:
      case CM_DNS_SERVICE_TELNET:
      case CM_DNS_SERVICE_FTP:
      case CM_DNS_SERVICE_H225_ANX_G:
      case CM_DNS_SERVICE_SIP:
      case CM_DNS_SERVICE_SIPS:
      case CM_DNS_SERVICE_IM:
      case CM_DNS_SERVICE_PRES:
      {
         lblLen  = (U8)srvcs[queryInfo->service].srvcLen;
         qName[(*qNameIdx)++] = lblLen;
         cmMemcpy((U8 *) &(qName[*qNameIdx]), 
                  (CONSTANT U8 *)srvcs[queryInfo->service].service, lblLen);

         /* Increment qNameIdx */
         *qNameIdx += lblLen;
      }
      break;

      default:
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
           "cmDnsEncode2782SrvQry(): Unsupported Service Type\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
         RETVALUE(RFAILED);
      }
   } /* end of switch(service) */

   /* Encode Supported Protocols */
   switch (queryInfo->protocol)
   {
      case CM_DNS_PROTOCOL_IP:
      case CM_DNS_PROTOCOL_TCP:
      case CM_DNS_PROTOCOL_TLS_TCP:
      case CM_DNS_PROTOCOL_UDP:
      case CM_DNS_PROTOCOL_SIP:
      case CM_DNS_PROTOCOL_SCTP:
      {
         /* encode protocol string length */
         lblLen = (U8)protos[queryInfo->protocol].protoLen;
         qName[(*qNameIdx)++] = lblLen;

         /* Encode Protocol */
         cmMemcpy((U8 *)&(qName[*qNameIdx]), 
                  (CONSTANT U8 *)protos[queryInfo->protocol].protocol,
                  lblLen);
               
         /* Increment qNameIdx */
         *qNameIdx += lblLen;
      }
      break;

      default:
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
           "cmDnsEncode2782SrvQry(): Unsupported Protocol Type\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
         RETVALUE(RFAILED);
      }
   } /* end of switch(protocol) */

   RETVALUE(ROK);

} /* end of cmDnsEncode2782SrvQry() */




/************************************************************************
            Process Response received from DNS
 ************************************************************************/
/*
*
*       Fun:   cmDnsPrcDnsRsp
*
*       Desc:  Decodes the message buffer received from DNS
*
*       Ret:   ROK      - Decoded Successfully
*              RFAILED  - Failed
*
*       Notes: Buffer Memory is owned by the user of the library
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PUBLIC S16 cmDnsPrcDnsRsp
(
CmDnsCb            *dnsCb,             /* DNS Information Control Block */
CmTptAddr          *srcTptAddr,        /* Source Transport Address */
Buffer             *mBuf               /* Message Buffer */
)
#else
PUBLIC S16 cmDnsPrcDnsRsp (dnsCb, srcTptAddr, mBuf)
CmDnsCb            *dnsCb;             /* DNS Information Control Block */
CmTptAddr          *srcTptAddr;        /* Source Transport Address */
Buffer             *mBuf;              /* Message Buffer */
#endif
{

  U8               *msg;               /* Message Pointer */
  /*cm_dns_c_001.main_16:102061 Changed from U16 MsgLen for msgLength */
  MsgLen           msgLength;          /* Message Length */
  CmDnsResponse    dnsRsp;             /* DNS Response */
  MsgLen           cnt;                /* Counter */
  U16              indx;              /* Index */
  CmDnsReqIdLst    *reqLst;            /* Request Id List */


   TRC2(cmDnsPrcDnsRsp);

  /* Check for Invalid Parameters */
   if ((dnsCb == NULLP) || (srcTptAddr == NULLP) || (mBuf == NULLP))
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
           "cmDnsPrcDnsRsp(): Invalid Parameters passed\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);
   }


   /* Initialise */
   cmMemset((U8 *)&(dnsRsp), 0 , sizeof(CmDnsResponse));
   /* 
    * Compare srcTptAddr with Transport Address of DNS to which request was
    * sent...This is used as a security mechanism to avoid spoofing of ports
    * to exploit security holes - RFC 2181
    */
#ifndef CM_MULTIPLE_DNS_SERVER
   if (cmDnsCmpTptAddr(srcTptAddr, &(dnsCb->dnsTptAddr)))
  {
#if (ERRCLASS & ERRCLS_DEBUG)
       CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
                   "cmDnsPrcDnsRsp(): Incorrect Port \n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);
   }
#else
   cmMemcpy((U8 *)&(dnsRsp.srcTptAddr), (CONSTANT U8 *)srcTptAddr ,sizeof(CmTptAddr));
#endif
   /* Initialise */
   indx  = 0;    

 
   /* Find Length of the Buffer */
   if (SFndLenMsg(mBuf, &msgLength) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
       CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
                   "cmDnsPrcDnsRsp(): Invalid Message Length \n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
       RETVALUE(RFAILED);
   }
 

   /* Get Buffer to store message */
   if(SGetSBuf(dnsCb->sMem.region, dnsCb->sMem.pool, (Data **)&msg,
       msgLength) != ROK)
   {
      RETVALUE(RFAILED);
   }

   /* Initialise */
   cmMemset ((Data *)msg, 0, msgLength);

   /* Copy message buffer into an array */
   if (SCpyMsgFix(mBuf, (MsgLen)0, msgLength, (Data *)msg,  
              &cnt) != ROK)
     RETVALUE(RFAILED);


   /* decode Header */
   if ((cmDnsDecodeHdr(&dnsRsp, msg, &indx)) != ROK)
   {
     SPutSBuf(dnsCb->sMem.region, dnsCb->sMem.pool,(Data *)msg, msgLength);
#if (ERRCLASS & ERRCLS_DEBUG)
     CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
                   "cmDnsPrcDnsRsp(): Failed to Decode Header \n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
     RETVALUE(RFAILED);
   }
   
   /* Check for Validity of Request ID */
   reqLst =  *(dnsCb->dnsReqLst);

   if (reqLst[dnsRsp.header.requestId].usrPtr == NULLP)
   {
     SPutSBuf(dnsCb->sMem.region, dnsCb->sMem.pool,(Data *)msg, msgLength);
#if (ERRCLASS & ERRCLS_DEBUG)
     CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
                   "cmDnsPrcDnsRsp(): Invalid Request ID \n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
     RETVALUE(RFAILED);
   }



   /* Decode Query Info. Technically this can be more than 1
    But we currently support only one*/

   if (dnsRsp.header.qdCount !=0)
   {
      if (cmDnsDecodeQuery(dnsCb, &dnsRsp, msg, &indx) != ROK)
      {
        SPutSBuf(dnsCb->sMem.region, dnsCb->sMem.pool,(Data *)msg, msgLength);
#if (ERRCLASS & ERRCLS_DEBUG)
        CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
                     "cmDnsPrcDnsRsp(): Failed to Decode Query \n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
        RETVALUE(RFAILED);
      }
   }
 


   /* Decode Answer RR */
   /* Change parameters to Decode RR*/
   if (cmDnsDecodeRR(dnsCb, &dnsRsp, msg, &indx, CM_DNS_ANS_RR, 
                     &dnsRsp.header.anCount, CM_DNS_MAX_ANSWR) != ROK)
   {
      SPutSBuf(dnsCb->sMem.region, dnsCb->sMem.pool,(Data *)msg, msgLength);
#if (ERRCLASS & ERRCLS_DEBUG)
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
                   "cmDnsPrcDnsRsp(): Failed to Decode Answer \n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);
   }



   if (dnsRsp.header.anCount > CM_DNS_MAX_ANSWR)
     dnsRsp.header.anCount = CM_DNS_MAX_ANSWR;

   /* Decode Auth RR */
   /* Changed count to pass address instead of value */
   if  ((cmDnsDecodeRR(dnsCb, &dnsRsp, msg, &indx, CM_DNS_AUTH_RR, 
                       &dnsRsp.header.nsCount, CM_DNS_NONE)) == RFAILED)
   {
      SPutSBuf(dnsCb->sMem.region, dnsCb->sMem.pool,(Data *)msg, msgLength);
#if (ERRCLASS & ERRCLS_DEBUG)
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
                    "cmDnsPrcDnsRsp(): Failed to Decode Auth RR \n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);
   }

   /* Decode Additinal  RR */
   /* Changed count to pass address instead of value */
   if (cmDnsDecodeRR(dnsCb, &dnsRsp, msg, &indx, CM_DNS_ADD_RR, 
                     &dnsRsp.header.arCount, CM_DNS_NONE) != ROK)
   {
      SPutSBuf(dnsCb->sMem.region, dnsCb->sMem.pool,(Data *)msg, msgLength);
#if (ERRCLASS & ERRCLS_DEBUG)
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
                   "cmDnsPrcDnsRsp(): Failed to Decode Auth RR \n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);
   }

   /* this is a temp fix.
    * The DNS lib current does not decode auth RR and additional RR.
    * The last parameter passed in the function call to cmDnsDecodeRR for 
    * auth and add RRs is CM_DNS_NONE, implying that these need not be
    * decoded. So the dnsRsp.header counts fro these twotypes need to be reset
    * to 0, to show that these have not been decoded. 
    * When the DNS implementation is changed to support decode of these RRs.
    * The initilaizations below must be removed. */
   dnsRsp.header.nsCount = 0;
   dnsRsp.header.arCount = 0;

   /* Release memory used for decoding */
   SPutSBuf(dnsCb->sMem.region, dnsCb->sMem.pool,(Data *)msg, msgLength);

   /* Call the Receive Function in the layer */
   dnsCb->rxFunc(reqLst[dnsRsp.header.requestId].usrPtr, &dnsRsp);
  
   RETVALUE(ROK);

} /* end of cmDnsPrcDnsRsp() */




/************************************************************************
            Decode Response Header
 ************************************************************************/

/*
*
*       Fun:   cmDnsDecodeHdr
*
*       Desc:  Decodes the Header of the Response received from DNS
*
*       Ret:   ROK      - Decoded Successfully
*              RFAILED  - Failed
*
*       Notes: Buffer Memory is owned by the user of the library
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PUBLIC S16 cmDnsDecodeHdr
(
CmDnsResponse      *dnsRsp,     /* DNS Response structure*/
U8                 *msg,        /* Response message */
U16                *indx
)
#else
PUBLIC S16 cmDnsDecodeHdr(dnsRsp, msg, indx)
CmDnsResponse      *dnsRsp;
U8                 *msg;
U16                *indx;
#endif
{
   U16 requestId;
   U16 msgIdx;

   TRC2(cmDnsDecodeHdr);   
   
   msgIdx = *indx;
   requestId =0;

   requestId = (U16)PutHiByte(requestId, msg[msgIdx++]);
   requestId = (U16)PutLoByte(requestId, msg[msgIdx++]);

   dnsRsp->header.requestId = requestId;

   CM_DNS_GET_MSGTYPE(msg[msgIdx],dnsRsp->header.msgType);

   if (!(dnsRsp->header.msgType))
     RETVALUE(RFAILED);

   
   CM_DNS_GET_OPCODE(msg[msgIdx], dnsRsp->header.opCode);
   CM_DNS_GET_ISAUTH(msg[msgIdx], dnsRsp->header.isAuth);
   CM_DNS_GET_ISTRUNC(msg[msgIdx], dnsRsp->header.isTrunc);
   CM_DNS_GET_QRYRECURSIVE(msg[msgIdx++], dnsRsp->header.qryRecursive);

   CM_DNS_GET_RECURAVL(msg[msgIdx],dnsRsp->header.recurAvl);
   CM_DNS_GET_RESPONSECODE(msg[msgIdx++],dnsRsp->header.responseCode);


   dnsRsp->header.qdCount = 
     (U16)PutHiByte(dnsRsp->header.qdCount, msg[msgIdx++]);
   dnsRsp->header.qdCount = 
     (U16)PutLoByte(dnsRsp->header.qdCount, msg[msgIdx++]);

   dnsRsp->header.anCount = 
     (U16)PutHiByte(dnsRsp->header.anCount, msg[msgIdx++]);
   dnsRsp->header.anCount = 
     (U16)PutLoByte(dnsRsp->header.anCount, msg[msgIdx++]);

   dnsRsp->header.nsCount = 
     (U16)PutHiByte(dnsRsp->header.nsCount, msg[msgIdx++]);
   dnsRsp->header.nsCount = 
     (U16)PutLoByte(dnsRsp->header.nsCount, msg[msgIdx++]);

   dnsRsp->header.arCount = 
     (U16)PutHiByte(dnsRsp->header.arCount, msg[msgIdx++]);
   dnsRsp->header.arCount = 
     (U16)PutLoByte(dnsRsp->header.arCount, msg[msgIdx++]);        

   /* Increment the index to current decode point */
   *indx = msgIdx;

   RETVALUE(ROK);
}




/************************************************************************
            Decode Query Section of the Response
 ************************************************************************/

/*
*
*       Fun:   cmDnsDecodeQuery
*
*       Desc:  Decode Query Section of the Response
*
*       Ret:   ROK      - Decoded Successfully
*              RFAILED  - Failed
*
*       Notes: Buffer Memory is owned by the user of the library
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PUBLIC S16 cmDnsDecodeQuery
(
CmDnsCb            *dnsCb,    /* DNS Information Control Block */
CmDnsResponse      *dnsRsp,    /* DNS Response Structure */
U8                 *msg,       /* Response Message */
U16                *indx      /* index */
)
#else
PUBLIC S16 cmDnsDecodeQuery(dnsCb, dnsRsp,msg, indx)
CmDnsCb            *dnsCb;    /* DNS Information Control Block */
CmDnsResponse      *dnsRsp;
U8                 *msg;
U16                *indx;
#endif
{
  U16 msgIdx;


  TRC2(cmDnsDecodeQuery);
  
  /* If first character is a '-' it represents a SRV record, so decode
     SRV record */

  if (msg[(*indx)+1] == CM_DNS_START_SRVRCRD)
  {
    if (cmDnsDecode2782Name(dnsCb, msg, indx, 
                            &dnsRsp->queryInfo.service, 
                            &dnsRsp->queryInfo.protocol) !=ROK)
      RETVALUE(RFAILED);
  }

  /* Decode Domain Name */ 
  if (cmDnsDecodeDmnName(dnsRsp->queryInfo.qName, msg, indx, 
                         &dnsRsp->queryInfo.qNameLen) != ROK)
    RETVALUE(RFAILED);

  
  msgIdx =*indx;
  
  /* Read the next 2 octets for the QType */
  dnsRsp->queryInfo.qType = PutHiByte(dnsRsp->queryInfo.qType, msg[msgIdx++]);
  dnsRsp->queryInfo.qType = PutLoByte(dnsRsp->queryInfo.qType, msg[msgIdx++]);


  /* Read the next 2 octets for the QClass */
  dnsRsp->queryInfo.qclass = PutHiByte(dnsRsp->queryInfo.qclass,
                                       msg[msgIdx++]);
  dnsRsp->queryInfo.qclass = PutLoByte(dnsRsp->queryInfo.qclass,
                                       msg[msgIdx++]);
  
  *indx = msgIdx;

  RETVALUE(ROK);
}




/************************************************************************
            Decode RRs in the Response
 ************************************************************************/

/*
*
*       Fun:   cmDnsDecodeRR
*
*       Desc:  Decodes the message buffer received from DNS
*
*       Ret:   ROK      - Decoded Successfully
*              RFAILED  - Failed
*
*       Notes: Buffer Memory is owned by the user of the library
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PUBLIC S16 cmDnsDecodeRR
(
CmDnsCb            *dnsCb,    /* DNS Information Control Block */
CmDnsResponse      *dnsRsp,   /* DNS Response Structure */
U8                 *msg,      /* Response Message */
U16                *indx,     /* Message index */
U8                 rrType,    /* ANS, AUTH/ ADD RR */
U16                *noOfRR,    /* Index into the RR Array */
U16                maxRR      /* Max no of RRs */
)
#else
PUBLIC S16 cmDnsDecodeRR(dnsCb, dnsRsp, msg, indx,rrType, noOfRR, maxRR)
CmDnsCb            *dnsCb;    /* DNS Information Control Block */
CmDnsResponse      *dnsRsp;
U8                 *msg;
U16                *indx;
U8                 rrType;
U16                *noOfRR;
U16                maxRR;   /* Max no of RRs */
#endif
{
  CmDns1035RR *rsrcRcrd;
  CmDns2782RR *srvRcrd;
#ifdef CM_NAPTR
  CmDns2915RR *naptrRcrd; 
#endif /* CM_NAPTR */
  U16 rrIndex;
  Bool canonical;
  U16 rrToDecode;
  U16 origIndex;

  TRC2(cmDnsDecodeRR);

  canonical = FALSE;

  if ((*noOfRR) >= maxRR)
    rrToDecode = maxRR;
  else
    rrToDecode = *noOfRR;

  for (rrIndex = 0; rrIndex < rrToDecode; rrIndex++)
  {
    /* The NS has sent back a RR of canonical type */
    if (canonical == TRUE)
    {
       canonical = FALSE;
      /*  Fix problem in decrementing of index */
     
      /*  Commented
      * Because decoding of CNAME 1035 RRs is now not recursive
      * (see comments in cmDnsDecode1035RR) we don't need to reduce
      * the number of RRs to decode here. */

       /* noOfRR Field in pointer now */
      (*noOfRR)--;

      if (rrIndex >= rrToDecode)
         RETVALUE(ROK);  
    }


    switch (dnsRsp->queryInfo.qType)
    {
#ifdef CM_NAPTR
      case CM_DNS_QTYPE_NAPTR:
         if (rrType == CM_DNS_ANS_RR)
         {
            naptrRcrd = &dnsRsp->ans[rrIndex].naptrRcrd;

            cmMemset ((U8 *) naptrRcrd, 0 , sizeof(CmDns2915RR));

            if (cmDnsDecode2915RR(dnsCb, naptrRcrd, msg, indx, rrIndex) != ROK)
            {
               RETVALUE(RFAILED);
            }
         }
         else
         {
            switch(rrType)
            {
               case CM_DNS_AUTH_RR:
                  rsrcRcrd = &dnsRsp->auth[rrIndex];
                  break;
               case CM_DNS_ADD_RR:
                  rsrcRcrd = &dnsRsp->add[rrIndex];
                  break;
               default:
                  RETVALUE(RFAILED);
            }
            cmMemset ((U8 *) rsrcRcrd, 0 , sizeof(CmDns1035RR));
            
            if ((cmDnsDecode1035RR(rsrcRcrd, msg, indx, &canonical)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
#endif /* CM_NAPTR */
      case CM_DNS_QTYPE_SRV:
         if (rrType == CM_DNS_ANS_RR)
         {
     /* cm_dns_c_001.main_13: Added CNAME support in DNS */
#ifdef CNAME_DNS  
            /* Try to decode RR as 1035 & check if there are any CNAME. */

            rsrcRcrd = &dnsRsp->ans[rrIndex].rsrcRcrd;
            cmMemset ((U8 *) rsrcRcrd, 0 , sizeof(CmDns1035RR));
            
            origIndex = *indx;
            (void)cmDnsDecode1035RR(rsrcRcrd, msg, indx, &canonical);

            if (!canonical)
            {
               /*Not a CNAME element, reparse as SRV*/
               cmMemset ((U8 *) rsrcRcrd, 0 , sizeof(CmDns1035RR));
#else
     /* cm_dns_c_001.main_13:End */

            /*  
            * Handle cases where the answers in the response to a SRV
            * request include a CNAME RR followed by one or more SRV RRs.
            * Try to decode RR as
            * 1035 & check if there are any CNAME. Ignore if CNAME is present
            * and continue 
            * decodeing remaing SRV RRs*/
            rsrcRcrd = &dnsRsp->ans[rrIndex].rsrcRcrd;
            cmMemset ((U8 *) rsrcRcrd, 0 , sizeof(CmDns1035RR));
            
            origIndex = *indx;
            if ((cmDnsDecode1035RR(rsrcRcrd, msg, indx, &canonical)) != ROK)
               RETVALUE(RFAILED);

            if (!canonical)
            {
#endif
               /* reparse as a SRV RR */
               *indx = origIndex;
               srvRcrd = &dnsRsp->ans[rrIndex].srvRcrd;
               cmMemset ((U8 *) srvRcrd, 0 , sizeof(CmDns2782RR));
               if (cmDnsDecode2782RR(dnsCb, srvRcrd, msg, indx, rrIndex) !=ROK)
               {
                  RETVALUE(RFAILED);
               }
            }

          
         }
         else
         {
            switch (rrType)
            {
            case CM_DNS_AUTH_RR:
               rsrcRcrd = &dnsRsp->auth[rrIndex];
               break;
            case CM_DNS_ADD_RR:
               rsrcRcrd = &dnsRsp->add[rrIndex];
               break;
            default:
               RETVALUE(RFAILED);
            }
            cmMemset ((U8 *) rsrcRcrd, 0 , sizeof(CmDns1035RR));
            
            if ((cmDnsDecode1035RR(rsrcRcrd, msg, indx, &canonical)) != ROK)
               RETVALUE(RFAILED);
         }
         break;

      
      case CM_DNS_QTYPE_A:
#ifdef CM_AAAA
      case CM_DNS_QTYPE_AAAA:
#endif /* CM_AAAA */
      {
         switch (rrType)
         {
           case CM_DNS_ANS_RR:
             rsrcRcrd =  &dnsRsp->ans[rrIndex].rsrcRcrd;
             break;
           case CM_DNS_AUTH_RR:
             rsrcRcrd = &dnsRsp->auth[rrIndex];
             break;
           case CM_DNS_ADD_RR:
             rsrcRcrd = &dnsRsp->add[rrIndex];
             break;
           default:
             RETVALUE(RFAILED);
         }
         cmMemset ((U8 *) rsrcRcrd, 0 , sizeof(CmDns1035RR));

         if ((cmDnsDecode1035RR(rsrcRcrd, msg, indx, &canonical)) != ROK)
            RETVALUE(RFAILED);
      }
      break;
        
      default:
        RETVALUE(RFAILED);

    } /* End of switch */

  } /* End for */

  RETVALUE(ROK);

}





/************************************************************************
                          Decode 1035 RR
 ************************************************************************/

/*
*
*       Fun:   cmDnsDecode1035RR
*
*       Desc:  Decodes the message buffer received from DNS
*
*       Ret:   ROK      - Decoded Successfully
*              RFAILED  - Failed
*
*       Notes: Buffer Memory is owned by the user of the library
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PUBLIC S16 cmDnsDecode1035RR
(
CmDns1035RR       *rsrcRcrd,     /* 1035 RR */
U8                *msg,          /* Response Message */
U16               *indx,         /* Message index */
Bool              *canonical     /* Canonical RR present/not present */
)
#else
PUBLIC S16 cmDnsDecode1035RR(rsrcRcrd, msg, indx, canonical)
CmDns1035RR       *rsrcRcrd;
U8                *msg;
U16               *indx;
Bool              *canonical;     /* Canonical RR present/not present */
#endif
{
  
  U16 tmp;
  U16 msgIdx;
#ifdef CM_AAAA
  U8  i;
#endif /* CM_AAAA */

  TRC2(cmDnsDecode1035RR);

  /* Decode Domain Name */
  if (cmDnsDecodeDmnName(rsrcRcrd->name, msg, indx, 
                             &rsrcRcrd->nameLen) != ROK)
        RETVALUE(RFAILED);

  /* Initialise */
  msgIdx = *indx;
  tmp    = 0;

  rsrcRcrd->type = PutHiByte(rsrcRcrd->type, msg[msgIdx++]);
  rsrcRcrd->type = PutLoByte(rsrcRcrd->type, msg[msgIdx++]); 

  rsrcRcrd->qclass = PutHiByte(rsrcRcrd->qclass, msg[msgIdx++]);
  rsrcRcrd->qclass = PutLoByte(rsrcRcrd->qclass, msg[msgIdx++]); 

  if (rsrcRcrd->qclass != CM_DNS_QCLASS_IN)
     RETVALUE(RFAILED);

  tmp = PutHiByte(tmp, msg[msgIdx++]);
  tmp = PutLoByte(tmp, msg[msgIdx++]);
  rsrcRcrd->ttl = PutHiWord(rsrcRcrd->ttl, tmp);
 
  tmp = PutHiByte(tmp, msg[msgIdx++]);
  tmp = PutLoByte(tmp, msg[msgIdx++]);
  rsrcRcrd->ttl = PutLoWord(rsrcRcrd->ttl, tmp);

  switch (rsrcRcrd->type)
  {
    case CM_DNS_QTYPE_A:
    {
      /* IP address is 4 bytes..so skip extraction of length */
      msgIdx += 2;

      tmp = PutHiByte(tmp, msg[msgIdx++]);
      tmp = PutLoByte(tmp, msg[msgIdx++]);
      rsrcRcrd->rdata.ipAddress = PutHiWord(rsrcRcrd->rdata.ipAddress, tmp);

      tmp = PutHiByte(tmp, msg[msgIdx++]);
      tmp = PutLoByte(tmp, msg[msgIdx++]);
      rsrcRcrd->rdata.ipAddress = PutLoWord(rsrcRcrd->rdata.ipAddress, tmp);
    }
    break;
#ifdef CM_AAAA
    case CM_DNS_QTYPE_AAAA:
    {
       /* IP address is 16 bytes..so skip extraction of length */
       msgIdx += 2;

       for (i = 0; i < CM_INET_IPV6ADDR_SIZE; i++)
          rsrcRcrd->rdata.ipv6Address[i] = msg[msgIdx++];
    }
    break;
#endif /* CM_AAAA */
    case CM_DNS_QTYPE_CANON:
      tmp =0;
      tmp = PutHiByte(tmp, msg[msgIdx++]);
      tmp = PutLoByte(tmp, msg[msgIdx++]);
      
      *indx = msgIdx;

#ifdef CNAME_DNS
/* Decode CNAME */
      /* cm_dns_c_001.main_14: Update for Release SIP 2.3 */
      if (cmDnsDecodeDmnName(rsrcRcrd->rdata.cname.val, msg, 
                             indx, (U8 *)&rsrcRcrd->rdata.cname.len) != ROK)
        RETVALUE(RFAILED);

        msgIdx = *indx;
#endif
    
       *canonical = TRUE;
      RETVALUE(ROK);
    default:
       break;
  }
  *indx = msgIdx;
  RETVALUE(ROK);
} /* end of cmDnsDecode1035RR */





/************************************************************************
                          Decode 2782 Domain Name
 ************************************************************************/

/*
*
*       Fun:   cmDnsDecode2782Name
*
*       Desc:  Decodes the message buffer received from DNS
*
*       Ret:   ROK      - Decoded Successfully
*              RFAILED  - Failed
*
*       Notes: Buffer Memory is owned by the user of the library
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PUBLIC S16 cmDnsDecode2782Name
(
CmDnsCb            *dnsCb,           /* DNS Information Control Block */
U8                 *msg,             /* Response Message */
U16                *indx,            /* Message index */
U8                 *service,         /* Service type */
U8                 *protocol         /* Protocol type */
)
#else
PUBLIC S16 cmDnsDecode2782Name(dnsCb, msg, indx, service, protocol)
CmDnsCb            *dnsCb;           /* DNS Information Control Block */
U8                 *msg;             /* Response Message */
U16                *indx;            /* Message Index */
U8                 *service;         /* Service Type */
U8                 *protocol;        /* Protocol Type */
#endif
{
  U8               length;           /* Length */
  U16              i;                /* Temporary Variable */
  U8               srvStr[CM_DNS_SRVC_STRLEN];  /* Service String */
  U8               protStr[CM_DNS_PROTO_STRLEN];/* Protocol String */
  U16              msgIdx;


   msgIdx = *indx;
  
   /* Decode the service string */
/*   if ((cmDnsDecodeDmnName(&srvStr, msg, indx, &length)) != ROK)
      RETVALUE(RFAILED); */

   msgIdx = *indx;
  
   length = msg[msgIdx++];

   cmMemcpy((U8 *)(&srvStr), (CONSTANT U8 *)(msg+msgIdx), length);
  
   msgIdx += length;



   for (i=0; i < CM_DNS_MAX_SUPP_SRVCS; i++)
   {
     if (length == srvcs[i].srvcLen)
     {
       if (!(cmStrncmp((CONSTANT U8 *)srvStr, 
                       (CONSTANT U8 *)srvcs[i].service, length)))
       {
         *service = (U8)i;
         break;
       }
     }
   }
   
   if (i == CM_DNS_MAX_SUPP_SRVCS)
     RETVALUE(RFAILED);


   /* Decode Protocol String */
 /*  if ((cmDnsDecodeDmnName(&protStr, msg, indx, &length)) != ROK)
      RETVALUE(RFAILED); */


   length = msg[msgIdx++];


   cmMemcpy((U8 *)(&protStr), (CONSTANT U8 *)(msg+msgIdx), length);

   msgIdx += length;


  for (i=0; i < CM_DNS_MAX_SUPP_PROTOS; i++)
   {
     if (length == protos[i].protoLen)
     {
       if (!(cmStrncmp((CONSTANT U8 *)protStr, 
                       (CONSTANT U8 *)protos[i].protocol, length)))
       {
         *protocol = (U8)i;
         break;
       }
     }
   }

  if (i == CM_DNS_MAX_SUPP_PROTOS)
    RETVALUE(RFAILED);

  *indx = msgIdx;

  RETVALUE(ROK);
}


#ifdef CM_NAPTR
/************************************************************************
                          Decode 2915 RR
 ************************************************************************/
/*
*
*       Fun:   cmDnsDecode2915RR
*
*       Desc:  Decodes the message buffer received from DNS
*
*       Ret:   ROK      - Decoded Successfully
*              RFAILED  - Failed
*
*       Notes: Buffer Memory is owned by the user of the library
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PUBLIC S16 cmDnsDecode2915RR
(
CmDnsCb            *dnsCb,           /* DNS Information Control Block */
CmDns2915RR        *naptrRcrd,         /* 2915 RR */
U8                 *msg,             /* Response Message */
U16                *indx,            /* Message index */
U16                rrIndex           /* Index into the RR Array */
)
#else
PUBLIC S16 cmDnsDecode2915RR(dnsCb, naptrRcrd, msg, indx, rrIndex)
CmDnsCb            *dnsCb;           /* DNS Information Control Block */
CmDns2915RR        *naptrRcrd;       /* 2915 RR */
U8                 *msg;
U16                *indx;
U16                rrIndex;
#endif
{
  U16 msgIdx;
  U16 tmp;
  U16 rrLength;

  TRC2(cmDnsDecode2915RR);
  UNUSED(dnsCb);

  tmp = 0;
  rrLength = 0;

  /* Decode Domain Name */
  if (cmDnsDecodeDmnName(naptrRcrd->name, msg, indx, 
                         &naptrRcrd->nameLen) != ROK)
    RETVALUE(RFAILED);

  
  msgIdx = *indx;

  /* Decode Type */
  naptrRcrd->type = PutHiByte(naptrRcrd->type, msg[msgIdx++]);
  naptrRcrd->type = PutLoByte(naptrRcrd->type, msg[msgIdx++]); 


  /* Decode Class */
  naptrRcrd->qclass = PutHiByte(naptrRcrd->qclass, msg[msgIdx++]);
  naptrRcrd->qclass = PutLoByte(naptrRcrd->qclass, msg[msgIdx++]); 

  /* Decode TTl */
 
  tmp = PutHiByte(tmp, msg[msgIdx++]);
  tmp = PutLoByte(tmp, msg[msgIdx++]);
  naptrRcrd->ttl = PutHiWord(naptrRcrd->ttl, tmp);
 
  tmp = PutHiByte(tmp, msg[msgIdx++]);
  tmp = PutLoByte(tmp, msg[msgIdx++]);
  naptrRcrd->ttl = PutLoWord(naptrRcrd->ttl, tmp);

  /* Length of RR */
  rrLength = PutHiByte(rrLength, msg[msgIdx++]);
  rrLength = PutLoByte(rrLength, msg[msgIdx++]); 
  
  /* Decode Priority */
  naptrRcrd->order = PutHiByte(naptrRcrd->order, msg[msgIdx++]);
  naptrRcrd->order = PutLoByte(naptrRcrd->order, msg[msgIdx++]); 

  /* Decode weight */
  naptrRcrd->preference = PutHiByte(naptrRcrd->preference, msg[msgIdx++]);
  naptrRcrd->preference = PutLoByte(naptrRcrd->preference, msg[msgIdx++]); 

  naptrRcrd->flagLen = msg[msgIdx++];
  if (naptrRcrd->flagLen)
     cmMemcpy((U8 *)naptrRcrd->flag, (CONSTANT U8 *)&(msg[msgIdx]),
           naptrRcrd->flagLen);

  msgIdx += naptrRcrd->flagLen;

  naptrRcrd->serviceLen = msg[msgIdx++];
  if (naptrRcrd->serviceLen)
     cmMemcpy((U8 *)naptrRcrd->service, (CONSTANT U8 *)&(msg[msgIdx]),
           naptrRcrd->serviceLen);

  msgIdx += naptrRcrd->serviceLen;

  naptrRcrd->regexpLen = msg[msgIdx++];
  if (naptrRcrd->regexpLen)
     cmMemcpy((U8 *)naptrRcrd->regexp, (CONSTANT U8 *)&(msg[msgIdx]),
           naptrRcrd->regexpLen);

  msgIdx += naptrRcrd->regexpLen;

  *indx = msgIdx;

  /* Decode Target Name */
  if (cmDnsDecodeDmnName(naptrRcrd->replacement, msg, indx, 
                         &naptrRcrd->replacementLen) != ROK)
    RETVALUE(RFAILED);

  RETVALUE(ROK);
}

#endif /* CM_NAPTR */



/************************************************************************
                          Decode 2782 RR
 ************************************************************************/
/*
*
*       Fun:   cmDnsDecode2782RR
*
*       Desc:  Decodes the message buffer received from DNS
*
*       Ret:   ROK      - Decoded Successfully
*              RFAILED  - Failed
*
*       Notes: Buffer Memory is owned by the user of the library
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PUBLIC S16 cmDnsDecode2782RR
(
CmDnsCb            *dnsCb,           /* DNS Information Control Block */
CmDns2782RR        *srvRcrd,         /* 2782 RR */
U8                 *msg,             /* Response Message */
U16                *indx,            /* Message index */
U16                rrIndex           /* Index into the RR Array */
)
#else
PUBLIC S16 cmDnsDecode2782RR(dnsCb, srvRcrd, msg, indx, rrIndex)
CmDnsCb            *dnsCb;           /* DNS Information Control Block */
CmDns2782RR        *srvRcrd;       /* 2782 RR */
U8                 *msg;
U16                *indx;
U16                rrIndex;
#endif
{
  U16 msgIdx;
  U16 tmp;
  U16 qtype;
  U16 rrLength;

  TRC2(cmDnsDecode2782RR);

  tmp = 0;
  qtype = 0;
  rrLength = 0;

/*  if (cmDnsDecode2782Name(dnsCb, msg, indx, 
                          &srvRcrd->service, &srvRcrd->protocol) !=ROK)
    RETVALUE(RFAILED); */

  /* Decode Domain Name */
  if (cmDnsDecodeDmnName(srvRcrd->name, msg, indx, 
                         &srvRcrd->nameLen) != ROK)
    RETVALUE(RFAILED);

  
  msgIdx = *indx;

  /* Decode Type */
  qtype = PutHiByte(qtype, msg[msgIdx++]);
  qtype = PutLoByte(qtype, msg[msgIdx++]); 


  /* Decode Class */
  srvRcrd->qclass = PutHiByte(srvRcrd->qclass, msg[msgIdx++]);
  srvRcrd->qclass = PutLoByte(srvRcrd->qclass, msg[msgIdx++]); 

  /* Decode TTl */
 
  tmp = PutHiByte(tmp, msg[msgIdx++]);
  tmp = PutLoByte(tmp, msg[msgIdx++]);
  srvRcrd->ttl = PutHiWord(srvRcrd->ttl, tmp);
 
  tmp = PutHiByte(tmp, msg[msgIdx++]);
  tmp = PutLoByte(tmp, msg[msgIdx++]);
  srvRcrd->ttl = PutLoWord(srvRcrd->ttl, tmp);

  /* Length of RR */
  rrLength = PutHiByte(rrLength, msg[msgIdx++]);
  rrLength = PutLoByte(rrLength, msg[msgIdx++]); 
  
  /* Decode Priority */
  srvRcrd->priority = PutHiByte(srvRcrd->priority, msg[msgIdx++]);
  srvRcrd->priority = PutLoByte(srvRcrd->priority, msg[msgIdx++]); 

  /* Decode weight */
  srvRcrd->weight = PutHiByte(srvRcrd->weight, msg[msgIdx++]);
  srvRcrd->weight = PutLoByte(srvRcrd->weight, msg[msgIdx++]); 

  /* Decode Port */
  srvRcrd->port = PutHiByte(srvRcrd->port, msg[msgIdx++]);
  srvRcrd->port = PutLoByte(srvRcrd->port, msg[msgIdx++]); 

  *indx = msgIdx;

  /* Decode Target Name */
  if (cmDnsDecodeDmnName(srvRcrd->target, msg, indx, 
                         &srvRcrd->targetLen) != ROK)
    RETVALUE(RFAILED);

  RETVALUE(ROK);
}





/************************************************************************
                          Decode Domain Name
 ************************************************************************/

/*
*
*       Fun:   cmDnsDecodeDmnName
*
*       Desc:  Decodes the message buffer received from DNS
*
*       Ret:   ROK      - Decoded Successfully
*              RFAILED  - Failed
*
*       Notes: Buffer Memory is owned by the user of the library
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PUBLIC S16 cmDnsDecodeDmnName
(
U8                 *domain,        /* Domain Name */
U8                 *msg,           /* Response Message */
U16                *indx,          /* Message index */ 
U8                 *nameLen        /* Length of the Domain Name */
)
#else
PUBLIC S16 cmDnsDecodeDmnName(domain, msg, indx, nameLen)
U8                 *domain;
U8                 *msg;
U16                *indx;
U8                 *nameLen;
#endif
{
  U8 length;
  U16 lblIndex;
  U16 msgIdx;
  U16 ptr;
  U16 labelLen;
  U8 isPtr;
  /*Fix the decoding ptr problem */
  U8 isLabelLenPtr;

  TRC2(cmDnsDecodeDmnName);
  lblIndex=0;
  msgIdx = *indx;
  ptr  =0;

  for(;;)
  {
    length = msg[msgIdx++];
    
    /* If the first 2 bits are 1 then the octet is a pointer.
       The offset value is in the remaining 6 bits */
    isPtr = 0;
    CM_DNS_CHK_LENGTH(length, isPtr)
    if (isPtr)
    {
      length = (U8)(length & CM_DNS_LENGTH_MASK);
      ptr = PutHiByte(ptr, length);
      ptr = PutLoByte(ptr, msg[msgIdx++]);

      labelLen = msg[ptr++];
      isLabelLenPtr = 0;
      CM_DNS_CHK_LENGTH(labelLen, isLabelLenPtr)

      
      while (labelLen && !isLabelLenPtr)
      {
        /* Copy the label */
        cmMemcpy((U8 *)&(domain[lblIndex]), (CONSTANT U8 *) &(msg[ptr]), 
                  labelLen);

        /* Increment the lengths copied */
        lblIndex += labelLen;
        ptr      += labelLen;
        *nameLen += labelLen;

        /* Get the next label length */
        labelLen = msg[ptr++];
        isLabelLenPtr = 0;
        CM_DNS_CHK_LENGTH(labelLen, isLabelLenPtr) 

        /* Put the dot after having copied the label */
        if (labelLen && !isLabelLenPtr)
        {
          domain[lblIndex++] = CM_DNS_LABEL_END;
          (*nameLen)++;
        }
      }
      break;
    }

    /* If Octet is not a pointer */
    if (length)
    {
      if (lblIndex != 0)
      {
         domain[lblIndex++] = CM_DNS_LABEL_END;

         /* Increment the domain name length */
         (*nameLen)++;
      }
     
      /* Copy the label */
      cmMemcpy((U8 *) &(domain[lblIndex]), (CONSTANT U8 *)&(msg[msgIdx]), length);
      lblIndex += length;
      msgIdx   += length;

      *nameLen  +=length;
/*cm_dns_c_001.main_13: Upadte for CNAME in DNS */
#ifdef CNAME_DNS
      /* Put the dot after having copied the label */
        if (length )
        {
          domain[lblIndex++] = CM_DNS_LABEL_END;
          (*nameLen)++;
        }
#endif 

    }
    else
      break;
  }
  
  *indx = msgIdx;

  RETVALUE(ROK);
}




/************************************************************************
                         Abort Resolve Request
 ************************************************************************/

/*
*
*       Fun:   cmDnsAbortRslvReq
*
*       Desc:  Abort a request sent to DNS - Free all resources attached to the
*              request
*
*       Ret:   None
*
*       Notes: None
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PUBLIC Void cmDnsAbortRslvReq
(
CmDnsCb            *dnsCb,             /* DNS Information Control Block */
U16                requestId           /* Request Identifier */
)
#else
PUBLIC Void cmDnsAbortRslvReq (dnsCb, requestId)
CmDnsCb            *dnsCb;             /* DNS Information Control Block */
U16                requestId;          /* Request Identifier */
#endif
{
   TRC2(cmDnsAbortRslvReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (dnsCb == NULLP)
   {
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
           "cmDnsAbortRslvReq(): Invalid dnsCb pointer\n");
      RETVOID;
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

#if (ERRCLASS & ERRCLS_DEBUG)
   if (dnsCb->state != CM_DNS_CB_OK2USE)
   {
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
           "cmDnsAbortRslvReq(): Invalid dnsCb state\n");
      RETVOID;
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   /* if request Id is not in use ..return */
   if ((*(dnsCb->dnsReqLst))[requestId].usrPtr == NULLP)
      RETVOID;

   /* Free the request Id */
   CM_DNS_FREE_REQID (dnsCb, requestId);

   RETVOID;

} /* end of cmDnsAbortRslvReq() */




/************************************************************************
                         Compare two port Addresses
 ************************************************************************/

/*
*
*       Fun:   cmDnsCmpTptAddr
*
*       Desc:  Compare two transport addresses of the type CmTptAddr
*
*       Ret:   -ve  if addr1 < addr2
*              zero if addr1 == addr2
*              +ve  if addr1 > addr2
*
*       Notes: None
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PUBLIC S16 cmDnsCmpTptAddr
(
CmTptAddr  *addr1,       /* first transport address */
CmTptAddr  *addr2        /* second transport address */
)
#else
PUBLIC S16 cmDnsCmpTptAddr(addr1, addr2)
CmTptAddr  *addr1;       /* first transport address */
CmTptAddr  *addr2;       /* second transport address */
#endif
{
   S16     retVal;       /* return value */

   TRC2 (cmDnsCmpTptAddr)

   if (addr1->type != addr2->type)
   {
      RETVALUE (1);
   }

   if ((addr1->type != CM_TPTADDR_IPV4) && (addr1->type != CM_TPTADDR_IPV4))
   {
      RETVALUE (1);
   }

   if (addr1->type == CM_TPTADDR_IPV4)
   {
      if (addr1->u.ipv4TptAddr.address ^ addr2->u.ipv4TptAddr.address)
         RETVALUE(addr1->u.ipv4TptAddr.address -
                  addr2->u.ipv4TptAddr.address);
      else
         RETVALUE(addr1->u.ipv4TptAddr.port - addr2->u.ipv4TptAddr.port);
   }
   else if (addr1->type == CM_TPTADDR_IPV6)
   {
      if ((retVal = cmMemcmp (addr1->u.ipv6TptAddr.ipv6NetAddr,
                              addr2->u.ipv6TptAddr.ipv6NetAddr,
                              sizeof (CmIpv6NetAddr))))
         RETVALUE(retVal);
      else
         RETVALUE(addr1->u.ipv6TptAddr.port - addr2->u.ipv6TptAddr.port);
   }

   RETVALUE(1);
} /* end of cmDnsCmpTptAddr */

/* cm_dns_c_001.main_15: 99301: Added function */
/************************************************************************
            Get user entry from Dns response
 ************************************************************************/
/*
*
*       Fun:   cmDnsGetUsrEntryFrmRsp
*
*       Desc:  To get the User Entry from Dns response
*
*       Ret:   Ptr    - Successful
*              NULLP  - Failed
*
*       Notes: 
*
*       File:  cm_dns.c
*
*/
#ifdef ANSI
PUBLIC Ptr cmDnsGetUsrEntryFrmRsp
(
CmDnsCb            *dnsCb,             /* DNS Information Control Block */
CmDnsResponse      *dnsRsp             /* DNS Response */
)
#else
PUBLIC Ptr cmDnsGetUsrEntryFrmRsp (dnsCb, dnsRsp)
CmDnsCb            *dnsCb;             /* DNS Information Control Block */
CmDnsResponse      *dnsRsp;            /* DNS Response */
#endif
{
   CmDnsReqIdLst    *reqLst;            /* Request Id List */

   TRC2(cmDnsGetUsrEntryFrmRsp);

   /* Check for Invalid Parameters */
   if ((dnsCb == NULLP) || (dnsRsp == NULLP))
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      CMDNSLOGERROR(ERRCLS_DEBUG, ECMDNSXXX, (ErrVal) 0, 
            "cmDnsGetUsrEntryFrmRsp(): Invalid Parameters passed\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(NULLP);
   }

   reqLst =  *(dnsCb->dnsReqLst);

   /* return the userentry  */
   RETVALUE(reqLst[dnsRsp->header.requestId].usrPtr);

} /* end of cmDnsGetUsrEntryFrmRsp() */





/********************************************************************30**
 
         End of file:     cm_dns.c@@/main/18 - Wed Dec  1 18:29:20 2010
 
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
/main/3      ---      dw   1. bug fixes
/main/4      ---      dvs  1. ClearCase release
/main/5      ---      asa  1. Added SIP defines
/main/6      ---      rg   1. initialized variables qType and rrLength
/main/7      ---      cy   1. Added code to support SIP requirement
/main/7      ---      zmc   1. Added code to support SIPS requirement
/main/8      ---    wh      1. SIP release 2.1 changes.
/main/9      ---     rbabu  1. Updated for NBAP software release 1.2
/main/10     ---     aj     1. noOfRR arg of cmDnsDecodeRR() is made
                               pointer.
                            2. Fixed the decoding of pointer.   
                            3. Fixed problems with DNS SRV responses where the answers
                               contained CNAME followed by SRV RRs.
/main/12+  cm_dns_c_001.main_12 sm 1. Added changes needed for Multiple 
                                      DNS support.
/main/13  cm_dns_c_001.main_13 gs 1. Added changes needed for CNAME in DNS 
/main/15     ---      cm_dns_c_001.main_14 ve 1. Update for Release SIP 2.3
/main/16     ---      cm_dns_c_001.main_15 rk 1. Added function to get user entry 
                                                 from Dns response
/main/17     ---      cm_dns_c_001.main_16 vg 1. Intialising last freed requestId
/main/18     ---      cm_dns_c_001.main_17 vkulkarni  1. Correcting non-ANSI compilation error  
*********************************************************************91*/
