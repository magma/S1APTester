
/********************************************************************20**

     Name:     TCP/UDP Convergence Layer

     Type:     C source file

     Desc:     Socket related functionality.

     File:     hi_bdy3.c

     Sid:      tl_bdy3.c@@/main/tenb_5.0_SIB_KNOWNSENSE/5 - Tue Feb  9 11:15:43 2016

     Prg:      kp

*********************************************************************21*/


/* header include files (.h) */

#include "envopt.h"        /* environment options */  
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */

/* external headers */

#include "cm_hash.h"       /* common hash list */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common sockets */
#include "cm_tpt.h"        /* common transport defines */

#ifdef FTHA
#include "sht.h"           /* SHT interface */
#endif

#include "lhi.h"           /* layer management, TUCL  */
#include "hit.h"           /* HIT interface */
#include "hi.h"            /* TUCL internal defines */
#include "hi_err.h"        /* TUCL errors */


/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_inet.x"       /* common sockets */
#include "cm_tpt.x"        /* common transport typedefs */

#ifdef FTHA
#include "sht.x"           /* SHT interface */
#endif


#include "lhi.x"           /* layer management, TUCL */
#include "hit.x"           /* HIT interface */

#include "hi.x"            /* TUCL internal typedefs */
 

/* hi032.201: Added new header file inclusion */
#ifdef SS_LINUX
#include<linux/version.h>
#endif


/* local defines */


/* local typedefs */
typedef SLockId MUTEX_TYPE;

struct CRYPTO_dynlock_value
{
   MUTEX_TYPE   mutex;
};


/* local externs */


/* forward references */


/* functions in other modules */


/* public variable declarations */


/* private variable declarations */




/* Socket related functionality.
 */



/*
*
*       Fun:    hiCreateSock
*
*       Desc:   Create a new socket, bind it, and set the
*               specified socket options.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy3.c
*
*/
#ifdef ANSI
PUBLIC S16 hiCreateSock
(
Bool            server,         /* server or client */
U8              type,           /* connection type */
CmTptAddr       *tptAddr,       /* transport address to use */
CmTptParam      *tPar,          /* transport parameters */
HiConCb         *conCb          /* connection control block */
)
#else
PUBLIC S16 hiCreateSock(server, type, tptAddr, tPar, conCb)
Bool            server;         /* server or client */
U8              type;           /* connection type */
CmTptAddr       *tptAddr;       /* transport address to use */
CmTptParam      *tPar;          /* transport parameters */
HiConCb         *conCb;         /* connection control block */
#endif
{
   S16          ret;
   HiSap        *sap;
   CmInetFd     fd;


   TRC2(hiCreateSock);

   /* get the SAP */
   sap = conCb->sap;

   /* create the socket */
   ret = HI_OPEN_SOCKET(type, &fd, conCb->protocol,
            (tptAddr->type == CM_TPTADDR_IPV6 ? HI_IPV6 : HI_IPV4));
   if (ret != ROK)
   {
      HILOGERROR_ADD_RES(EHI088, ret, 0, "Could not create socket");
      HI_INC_ERRSTS(hiCb.errSts.sockOpenErr);
      RETVALUE(HI_SOCK_OPEN_ERR);
   }

   /* apply the socket reuse address option */
   HI_SET_SOCKOPT_REUSEADDR(&fd);

   /* bind the socket to the specified address, if specified */
   if (HI_CHK_ADDR(tptAddr))
   {
      ret = HI_BIND_SOCKET(&fd, tptAddr);
      if (ret != ROK)
      {
         HI_CLOSE_SOCKET(&fd);
         HILOGERROR_ADD_RES(EHI089, ret, 0, "Socket bind error");
         HI_INC_ERRSTS(hiCb.errSts.sockBindErr);
         RETVALUE(HI_SOCK_BIND_ERR);
      }
   }

   /* apply TCP no-delay option */
   if (type == CM_INET_STREAM)
      HI_SET_SOCKOPT_TCP_NODELAY(&fd);

   /* copy the socket descriptor into the connection */
   cmMemcpy((U8 *)&conCb->conFd, (U8 *)&fd, sizeof (CmInetFd));

   /* set provided socket options if present */
   /* hi002.105  added check for CM_TPTPARAM_NOTPRSNT */
   if (tPar && (tPar->type != CM_TPTPARAM_NOTPRSNT ))
   {
      ret = hiSetSockOpt(conCb, tPar);
      if (ret != ROK)
      {
         HI_CLOSE_SOCKET(&conCb->conFd);
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
                "Could not set socket options\n"));
         RETVALUE(HI_SOCK_SOPT_ERR);
      }
   }

#ifndef IPV6_SUPPORTED
   conCb->locTptAddr.type = CM_TPTADDR_IPV4;
#endif

/* hi023.202: To support multiple SCTP ports on solaris 10 platform */
#ifdef HI_SOL10_MULTIPORT
   conCb->locTptAddr = *tptAddr;
#else
   /* get the local address associated with the socket */
   ret = HI_GET_SOCKNAME(&conCb->conFd, &conCb->locTptAddr);
   if (ret != ROK)
   {
      HI_CLOSE_SOCKET(&conCb->conFd);
      HILOGERROR_ADD_RES(EHI090, ret, 0, "Could not get socket name");
      RETVALUE(HI_SOCK_NAME_ERR);
   }
#endif /* HI_SOL10_MULTIPORT */

   RETVALUE(ROK);
} /* hiCreateSock() */


/*
*
*       Fun:    hiSetSockOpt
*
*       Desc:   Apply specified socket options.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  If cmInetSetOpt returns RNA, the connection
*               control block is marked as not supporting IP
*               header inclusion. Otherwise, if an option to
*               include headers has been specified, the connection
*               control block is so marked.
*
*       File:   hi_bdy3.c
*
*/
#ifdef ANSI
PUBLIC S16 hiSetSockOpt
(
HiConCb         *conCb,         /* connection */
CmTptParam      *tPar           /* socket options */
)
#else
PUBLIC S16 hiSetSockOpt(conCb, tPar)
HiConCb         *conCb;         /* connection */
CmTptParam      *tPar;          /* socket options */
#endif
{
   S16                  i, ret;
   U8                   numOpts;
   CmSockOpts           *sockOpts, *opt;
   Ptr                  value;
   CmInetMCastInf       mCastInf;
   CmInetIpAddr         lclAddr;


   TRC2(hiSetSockOpt);

   /* initialize locals */
   sockOpts = NULLP;

   /* get the options from the right place */
   numOpts = 0;
   if (tPar->type == CM_TPTPARAM_SOCK)
   {
      numOpts   = tPar->u.sockParam.numOpts;
      sockOpts  = tPar->u.sockParam.sockOpts;
   }

   /* apply the socket options */
   for (i = 0;  i < (S16)numOpts;  i++)
   {
      opt = &sockOpts[i];

      /* add/drop multicast group membership */
      if (opt->option == CM_SOCKOPT_OPT_ADD_MCAST_MBR
            ||  opt->option == CM_SOCKOPT_OPT_DRP_MCAST_MBR)
      {
         mCastInf.mCastAddr = opt->optVal.mCastInfo.mCastAddr.u.ipv4NetAddr;
         mCastInf.localAddr = opt->optVal.mCastInfo.localAddr.u.ipv4NetAddr;
         value = (Ptr)&mCastInf;
      }

      /* local interface for outgoing multicast */
      else if (opt->option == CM_SOCKOPT_OPT_MCAST_IF)
      {
         lclAddr = opt->optVal.lclAddr.u.ipv4NetAddr;
         value = (Ptr)&lclAddr;
      }

#ifdef IPV6_SUPPORTED
      /* add/drop IPv6 multicast group membership */
      else if (opt->option == CM_SOCKOPT_OPT_ADD_MCAST6_MBR
               ||  opt->option == CM_SOCKOPT_OPT_DRP_MCAST6_MBR)
         value = (Ptr)&opt->optVal.mCastInfo6;

      /* local interface for outgoing multicast IPv6 */
      /* hi001.105 - Fix compilation error */
      else if (opt->option == CM_SOCKOPT_OPT_MCAST6_IF)
         value = (Ptr)&opt->optVal.infId;
#endif

      else
         value = (Ptr)&opt->optVal.value;

      /* set the option */
      ret = cmInetSetOpt(&conCb->conFd, opt->level, opt->option, value);
      if (ret == RNA)
         conCb->hdrIncldFlag |= HI_HDRINCLD_NT_SUPPORTED;
      else if (ret != ROK)
      {
         HI_INC_ERRSTS(hiCb.errSts.sockSOptErr);
         RETVALUE(RFAILED);
      }
   }

   /* If header inclusion is supported, and has been requested,
    * mark the connection control block.
    */
   if (!(conCb->hdrIncldFlag & HI_HDRINCLD_NT_SUPPORTED))
   {
      for (i = 0;  i < (S16)numOpts;  i++)
      {
         if (sockOpts[i].option == CM_SOCKOPT_OPT_HDRINCLD)
         {
            conCb->hdrIncldFlag |= HI_INCLUDE_HDR;
            break;
         }
      }
   }

   RETVALUE(ROK);
} /* hiSetSockOpt() */



/* hi032.201: Added new function to support filteration of ICMP messages 
 * as per user request and protected under CM_ICMP_FILTER_SUPPORT flag */
#ifdef CM_ICMP_FILTER_SUPPORT
/*
* 
*        Fun:    hiCreateIcmpSock
* 
*        Desc:   Create a new ICMP socket, bind it, and set the
*                specified socket options.
* 
*        Ret:    ROK     - ok
*                RFAILED - failed
* 
*        Notes:  None
* 
*        File:   hi_bdy3.c
* 
*/
#ifdef ANSI
PUBLIC S16 hiCreateIcmpSock
(
 Bool            server,         /* server or client */
 U8              type,           /* connection type */
 CmTptAddr       *tptAddr,       /* transport address to use */
 HiConCb         *conCb          /* connection control block */
 )
#else
PUBLIC S16 hiCreateIcmpSock(server, type, tptAddr, conCb)
   Bool            server;         /* server or client */
   U8              type;           /* connection type */
   CmTptAddr       *tptAddr;       /* transport address to use */
   HiConCb         *conCb;         /* connection control block */
#endif
{
   S16          ret = 0;
   CmInetFd     fd;
   U8 prot;
   U16 idx;


   TRC2(hiCreateIcmpSock);


   if (conCb->icmpType == CM_NETADDR_IPV4)
   {
      prot = CM_PROTOCOL_ICMP;
   }
#ifdef IPV6_SUPPORTED
   else
   {
      prot = CM_PROTOCOL_ICMPV6;
   }
#endif

   /* create the socket */
   ret = HI_OPEN_SOCKET(type, &fd, prot,
         (tptAddr->type == CM_TPTADDR_IPV6 ? HI_IPV6 : HI_IPV4));
   if (ret != ROK)
   {
      HILOGERROR_ADD_RES(EHI088, ret, 0, "Could not create socket");
      HI_INC_ERRSTS(hiCb.errSts.sockOpenErr);
      RETVALUE(HI_SOCK_OPEN_ERR);
   }

   /* bind the socket to the specified address, if specified */
   if (HI_CHK_ADDR(tptAddr))
   {
      ret = HI_BIND_SOCKET(&fd, tptAddr);
      if (ret != ROK)
      {
         HI_CLOSE_SOCKET(&fd);
         HILOGERROR_ADD_RES(EHI089, ret, 0, "Socket bind error");
         HI_INC_ERRSTS(hiCb.errSts.sockBindErr);
         RETVALUE(HI_SOCK_BIND_ERR);
      }
   }


   for(idx = 0; idx < CM_MAX_ICMP_SOCKET; idx++)
   {
      if(hiCb.icmpInfo[idx].usedFlag == TRUE)
         continue;
      else
      {
         if (conCb->icmpType == CM_NETADDR_IPV4)
            hiCb.icmpInfo[idx].icmpConFd = fd;
#ifdef IPV6_SUPPORTED
         else
            hiCb.icmpInfo[idx].icmp6ConFd = fd;
#endif
         conCb->idx = idx;
         break;
      }
   }

   if(idx >= CM_MAX_ICMP_SOCKET)
   {
      if (conCb->icmpType == CM_NETADDR_IPV4)
         hiCb.icmpInfo[idx].icmpConFd = fd;
#ifdef IPV6_SUPPORTED
      else
         hiCb.icmpInfo[idx].icmp6ConFd = fd;

#endif
      conCb->idx = idx;
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);

} /* hiCreateIcmpSock */



/*
*  
*          Fun:    hiSetIcmpSockOpt
*    
*          Desc:   This function is user to set ICMP
*                  socket option.
*      
*          Ret:    ROK     - ok
*          RFAILED - failed
*         
*          Notes: None 
*
*          File:   hi_bdy3.c
*                 
*/
#ifdef ANSI
PUBLIC S16 hiSetIcmpSockOpt
(
 HiConCb         *conCb         /* connection */
 )
#else
PUBLIC S16 hiSetIcmpSockOpt(conCb)
   HiConCb         *conCb;         /* connection */
#endif
{
   S16          fdGrpNum;
   HiThrMsg     tMsg;
   HiConCb      *prevConCb;
   S16          ret;
   Bool         done;
   U16           i;
   S16         msgType;
   U32           icmpFilter;
   U32          filterData, tempData;
   U32           icmpMask;
   U8           numUsers;
#ifdef IPV6_SUPPORTED
   U8 j, cnt;
   Bool flag;
   CmInetIcmp6Filter value;
#endif

   TRC2(hiSetIcmpSockOpt)

      prevConCb = NULLP;
      done = FALSE; 
      ret = 0;

      if (conCb->icmpType == CM_NETADDR_IPV4)
      {
         msgType = HI_THR_STARTICMP;
         numUsers = hiCb.icmpInfo[conCb->idx].icmpUsers;
      }
#ifdef IPV6_SUPPORTED
      else
      {
         msgType = HI_THR_STARTICMP6;
         numUsers = hiCb.icmpInfo[conCb->idx].icmp6Users;
      }
#endif

   if (conCb->icmpType == CM_NETADDR_IPV4)
   {
      icmpFilter = 0;
      tempData = 0;
      filterData = 0;

      for (i = 0;  i < conCb->numFilters;  i++)
      {
         icmpMask = 0xffffffff;
         tempData = 1<<conCb->icmpError[i].errType;
         tempData = icmpMask ^ tempData;
         filterData = filterData | tempData;

      }
      conCb->filterData = filterData;

      while ((ret = cmHashListGetNext(&hiCb.icmpInfo[conCb->idx].conCbHlCp, (PTR)prevConCb,
                  (PTR *)&conCb)) == ROK)
      {

         icmpFilter = icmpFilter | conCb->filterData;
         prevConCb = conCb;
      }
#ifdef SS_LINUX
      ret = cmInetSetOpt(&hiCb.icmpInfo[conCb->idx].icmpConFd, CM_SOCKOPT_LEVEL_RAW,
            CM_INET_OPT_ICMP_FILTER, &icmpFilter);
      if (ret != ROK)
      {
         HI_INC_ERRSTS(hiCb.errSts.sockSOptErr);
         RETVALUE(RFAILED);
      }
#else
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
               "FIlteartion of ICMP messages is not supported in this machine\n"));
#endif
   }

#ifdef IPV6_SUPPORTED
   else
   {
      cmMemset((U8 *)&value, 0, sizeof(CmInetIcmp6Filter));
      if (conCb->icmp6Mask & ALL_ICMP_MSG)
      {
         CM_INET_ICMP6_FILTER_SETPASSALL(hiCb.icmpInfo[conCb->idx].icmp6Filter);
      }
      else
      {
         for (i = 0; i <= CM_MAX_ICMPV6_MSGTYPE; i++)
         {
            j =0;
            flag = TRUE;
            while (j < conCb->numFilters)
            {
               if (i ==  conCb->icmpError[j].errType)
               {
                  flag = FALSE;
                  break;
               }
               j++;
            }

            if (flag)
               CM_INET_ICMP6_FILTER_SETBLOCK(i, hiCb.icmpInfo[conCb->idx].icmp6Filter);
         }
      }

      cmMemcpy((U8 *)&conCb->ipv6FilterData,
            (U8 *)&hiCb.icmpInfo[conCb->idx].icmp6Filter, sizeof(CmInetIcmp6Filter));

      while ((ret = cmHashListGetNext(&hiCb.icmpInfo[conCb->idx].conCbHlCp,(PTR)prevConCb,
                  (PTR *)&conCb)) == ROK)
      {
         for(cnt = 0; cnt < CM_MAX_IPV6_FILTER; cnt++)
         {
#ifdef SS_LINUX
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18)
            value.icmp6_filt[cnt] = value.icmp6_filt[cnt] | conCb->ipv6FilterData.icmp6_filt[cnt];
#else
            value.data[cnt] = value.data[cnt] | conCb->ipv6FilterData.data[cnt];
#endif
#else
#ifdef SS_VW 
            value.icmp6_filt[cnt] = value.icmp6_filt[cnt] | conCb->ipv6FilterData.icmp6_filt[cnt];
#else
            value.__icmp6_filt[cnt] = value.__icmp6_filt[cnt] | conCb->ipv6FilterData.__icmp6_filt[cnt];
#endif
#endif

         }
         prevConCb = conCb;
      }

      ret =  cmInetSetOpt(&hiCb.icmpInfo[conCb->idx].icmp6ConFd, CM_INET_PROTO_ICMPV6,
            CM_INET_OPT_ICMP6_FILTER, &value);
      if (ret != ROK)
      {
         HI_INC_ERRSTS(hiCb.errSts.sockSOptErr);
         RETVALUE(RFAILED);
      }
   }
#endif

   if(numUsers == 1)
   {
      fdGrpNum = hiCb.lastGrp;

      if (fdGrpNum == hiCb.numFdGrps)
         fdGrpNum = 0;

      while (fdGrpNum < (S16)hiCb.numFdGrps  &&  !done)
      {

#ifdef HI_MULTI_THREADED
         HI_LOCK(&hiCb.fdGrps[fdGrpNum]->lock);
#endif

         /* see if the group has room */
         if (hiCb.fdGrps[fdGrpNum]->numFds < hiCb.cfg.numFdsPerSet)
         {
            /* store the group number in the connection */
            hiCb.icmpInfo[conCb->idx].icmpFdGrpNum = fdGrpNum;
            hiCb.lastGrp = fdGrpNum + 1;
            done = TRUE;
         }

#ifdef HI_MULTI_THREADED
         HI_UNLOCK(&hiCb.fdGrps[fdGrpNum]->lock);
#endif

         fdGrpNum++;
      }

      /* give the new connection to the group's thread, if we found one */
      if (done)
      {

         tMsg.idx = conCb->idx;
         tMsg.spId = conCb->sap->spId;
         tMsg.spConId = conCb->spConId;
         tMsg.type = msgType;
         ret = hiSendThrMsg(hiCb.icmpInfo[conCb->idx].icmpFdGrpNum, &tMsg);
      }
      if (ret != ROK)
      {
         HILOGERROR_ADD_RES(EHI084, 0, 0,
               "hiSetIcmpSockOpt(): could not assign fd to group");
         RETVALUE(ret);
      }
   }

   RETVALUE(ROK);
} /* hiSetIcmpSockOpt */

#endif /* CM_ICMP_FILTER_SUPPORT */




/* Protocol related functionality.
 */


/*
*
*       Fun:    hiProcessIcmpReq
*
*       Desc:   Process server open requests with ICMP filters
*               specified.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy3.c
*
*/
#ifdef ANSI
PUBLIC S16 hiProcessIcmpReq
(
HiConCb         *conCb,         /* connection */
CmIcmpFilter    *icmpFilter     /* ICMP filter */
)
#else
PUBLIC S16 hiProcessIcmpReq(conCb, icmpFilter)
HiConCb         *conCb;         /* connection */
CmIcmpFilter    *icmpFilter;    /* ICMP filter */
#endif
{
   U16                  num;
   CmIcmpv4Filter       *icmpv4Filter;
#ifdef IPV6_SUPPORTED
   CmIcmpv6Filter       *icmpv6Filter;
#endif


   TRC2(hiProcessIcmpReq);


   conCb->numFilters = 0;
   conCb->icmpError = NULLP;


   /* handle ICMPv4 */
   if (icmpFilter->type == CM_ICMPVER4_FILTER)
   {
      conCb->icmpType = CM_NETADDR_IPV4;
      icmpv4Filter = (CmIcmpv4Filter *)&icmpFilter->u.icmpv4Filter;
      if (icmpv4Filter->allMsg)
      {
         if (icmpv4Filter->protocol == CM_PROTOCOL_RAW)
            conCb->icmpMask |= ALL_ICMP_MSG;
         else
         {
            conCb->filterProtocol = icmpv4Filter->protocol;
            conCb->icmpMask |= ALL_PROTO_SPEC_MSG;
         }
      }
      else
      {
         if (icmpv4Filter->protocol == CM_PROTOCOL_RAW)
            conCb->icmpMask |= ALL_FLTRD_ICMP_MSG;
         else
         {
            conCb->filterProtocol = icmpv4Filter->protocol;
            conCb->icmpMask |= FLTRD_PROTO_SPEC_MSG;
         }

         num = conCb->numFilters = icmpv4Filter->num;
         HI_ALLOC(num * sizeof (CmIcmpError), conCb->icmpError);
         if (!conCb->icmpError)
            RETVALUE(RFAILED);
         cmMemcpy((U8 *)conCb->icmpError, (U8 *)icmpv4Filter->icmpError,
                  num * sizeof (CmIcmpError));
      }
   }

#ifdef IPV6_SUPPORTED
   /* handle ICMPv6 */
   else
   {
      conCb->icmpType = CM_NETADDR_IPV6;
      icmpv6Filter = (CmIcmpv6Filter *)&icmpFilter->u.icmpv6Filter;
      if (icmpv6Filter->allMsg)
         conCb->icmp6Mask |= ALL_ICMP_MSG;
      else
      {
         conCb->icmp6Mask |= ALL_FLTRD_ICMP_MSG;
         num = conCb->numFilters = icmpv6Filter->num;
         HI_ALLOC(num * sizeof (CmIcmpError), conCb->icmpError);
         if (!conCb->icmpError)
            RETVALUE(RFAILED);
         cmMemcpy((U8 *)conCb->icmpError, (U8 *)icmpv6Filter->icmpError,
                  num * sizeof (CmIcmpError));
      }
   }
#endif


   RETVALUE(ROK);
} /* hiProcessIcmpReq() */


/*
*
*       Fun:    hiAddTPKTHdr
*
*       Desc:   Mark boundaries of data in a TCP octet stream.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_proto.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAddTPKTHdr
(
Buffer          *mBuf,          /* message buffer */
MsgLen          *newLen         /* updated with new message length */
)
#else
PUBLIC S16 hiAddTPKTHdr(mBuf, newLen)
Buffer          *mBuf;          /* message buffer */
MsgLen          *newLen;        /* updated with new message length */
#endif
{
   S16          ret;
   U16          nLen;
   U8           hdr[HI_TPKT_HDR_LEN];


   TRC2(hiAddTPKTHdr);


   /* encode the length */
   nLen = (U16)(*newLen) + HI_TPKT_HDR_LEN;
   hdr[0] = GetLoByte(nLen);
   hdr[1] = GetHiByte(nLen);  
   hdr[2] = HI_TPKT_HDR_RESERVED;
   hdr[3] = HI_TPKT_HDR_VERSION;


   /* put in the header and add to message length on success */
   ret = SAddPreMsgMult(hdr, HI_TPKT_HDR_LEN, mBuf);


   RETVALUE(ret);
} /* hiAddTPKTHdr() */


/*
*
*       Fun:    hiPkIpv4Hdr
*
*       Desc:   Pack the specified IPv4 header into a message.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_proto.c
*
*/
#ifdef ANSI
PRIVATE S16 hiPkIpv4Hdr
(
CmIpv4Hdr       *ipv4Hdr,       /* IPv4 header */
Buffer          *mBuf           /* message buffer */
)
#else
PRIVATE S16 hiPkIpv4Hdr(ipv4Hdr, mBuf)
CmIpv4Hdr       *ipv4Hdr;       /* IPv4 header */
Buffer          *mBuf;          /* message buffer */
#endif
{
   S16          ret, cnt, idx;
   Data         revPkArray[CM_IPV4_HDRLEN]; 
   Data         pkArray[CM_IPV4_HDRLEN];


   /* initialize locals */
   cnt = 0;
   cmMemset(revPkArray, 0, CM_IPV4_HDRLEN);
   cmMemset(pkArray, 0, CM_IPV4_HDRLEN);


   /* Pack Header Version */
   pkArray[cnt++] = ipv4Hdr->hdrVer;

   /* Pack TOS */
   pkArray[cnt++] = ipv4Hdr->tos;

   /* On some BSD-like systems, the ip_len and ip_off field are in
    * host byte order when passed into kernel. We need to reverse
    * the order on a little endian processor in such a case. If
    * your OS is behaves this way, enable BSD_SIM_CORE.
    */
#ifndef BSD_SIM_CORE
   pkArray[cnt++] = (Data)GetHiByte(ipv4Hdr->length);
   pkArray[cnt++] = (Data)GetLoByte(ipv4Hdr->length);
#else
   pkArray[cnt++] = (Data)GetHiByte(CM_INET_HTON_U16((U16)ipv4Hdr->length));
   pkArray[cnt++] = (Data)GetLoByte(CM_INET_HTON_U16((U16)ipv4Hdr->length));
#endif

   /* Pack Id */
   pkArray[cnt++] = (Data) GetHiByte(ipv4Hdr->id);
   pkArray[cnt++] = (Data) GetLoByte(ipv4Hdr->id);

   /* Pack Offset */
#ifndef BSD_SIM_CORE
   pkArray[cnt++] = (Data)GetHiByte(ipv4Hdr->off);
   pkArray[cnt++] = (Data)GetLoByte(ipv4Hdr->off);
#else
   pkArray[cnt++] = (Data)GetHiByte(CM_INET_HTON_U16((U16)ipv4Hdr->off));
   pkArray[cnt++] = (Data)GetLoByte(CM_INET_HTON_U16((U16)ipv4Hdr->off));
#endif

   /* Pack TTL */
   pkArray[cnt++] = ipv4Hdr->ttl;

   /* Pack Protocol */
   pkArray[cnt++] = ipv4Hdr->proto;

   /* Pack Checksum */
   pkArray[cnt++] = (Data)GetHiByte(ipv4Hdr->chkSum);
   pkArray[cnt++] = (Data)GetLoByte(ipv4Hdr->chkSum);

   /* Pack Source Address */
   pkArray[cnt++] = (Data)GetHiByte(GetHiWord(ipv4Hdr->srcAddr));
   pkArray[cnt++] = (Data)GetLoByte(GetHiWord(ipv4Hdr->srcAddr));
   pkArray[cnt++] = (Data)GetHiByte(GetLoWord(ipv4Hdr->srcAddr));
   pkArray[cnt++] = (Data)GetLoByte(GetLoWord(ipv4Hdr->srcAddr));

   /* Pack Destination Address */
   pkArray[cnt++] = (Data)GetHiByte(GetHiWord(ipv4Hdr->destAddr));
   pkArray[cnt++] = (Data)GetLoByte(GetHiWord(ipv4Hdr->destAddr));
   pkArray[cnt++] = (Data)GetHiByte(GetLoWord(ipv4Hdr->destAddr));
   pkArray[cnt++] = (Data)GetLoByte(GetLoWord(ipv4Hdr->destAddr));

   for (idx = 0;  idx < CM_IPV4_HDRLEN;  idx++)
      revPkArray[idx] = pkArray[CM_IPV4_HDRLEN - idx -1];

   /* this function automatically reverses revPkArray */
   ret = SAddPreMsgMult(revPkArray, (MsgLen)cnt, mBuf);


   RETVALUE(ret);
} /* hiPkIpv4Hdr() */


/*
*
*       Fun:    hiUnpkIpv4Hdr
*
*       Desc:   Unpack an IPv4 header from the specified message.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_proto.c
*
*/
#ifdef ANSI
PRIVATE S16 hiUnpkIpv4Hdr
(
Buffer          *mBuf,          /* message buffer */
CmIpv4Hdr       *ipv4Hdr,       /* IPv4 header */
CmIpHdrParm     *hdrParm        /* header options */
)
#else
PRIVATE S16 hiUnpkIpv4Hdr(mBuf, ipv4Hdr, hdrParm) 
Buffer          *mBuf;          /* message buffer */
CmIpv4Hdr       *ipv4Hdr;       /* IPv4 header */
CmIpHdrParm     *hdrParm;       /* header options */
#endif
{
   S16          ret, temp;
   U8           cnt;
#ifdef IPV4_OPTS_SUPPORTED
   Data         unPkArray[CM_IPV4_HDRLEN + CM_IPV4_OPTS_MAXLEN];
   S8           extraBytes;
#else
   Data         unPkArray[CM_IPV4_HDRLEN];
#endif


   /* initialize locals */
   cnt = 0;
   temp = 0;


#ifdef IPV4_OPTS_SUPPORTED
   cmMemset(unPkArray, 0, CM_IPV4_HDRLEN + CM_IPV4_OPTS_MAXLEN);
#else
   cmMemset(unPkArray, 0, CM_IPV4_HDRLEN);
#endif


   /* extract IP header from the message */
   ret = SRemPreMsgMult((Data *)unPkArray, CM_IPV4_HDRLEN, mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "hiUnpkIpv4Hdr(): SRemPreMsgMult failed\n"));
      RETVALUE(RFAILED);
   }
#endif


   /* Unpack Header Version */
   ipv4Hdr->hdrVer = unPkArray[cnt++];

   /* Unpack TOS */
   ipv4Hdr->tos = unPkArray[cnt++];

   /* Unpack Length */
   ipv4Hdr->length = PutHiByte(ipv4Hdr->length, unPkArray[cnt++]);
   ipv4Hdr->length = PutLoByte(ipv4Hdr->length, unPkArray[cnt++]);

   /* Unpack Id */
   ipv4Hdr->id = PutHiByte(ipv4Hdr->id, unPkArray[cnt++]);
   ipv4Hdr->id = PutLoByte(ipv4Hdr->id, unPkArray[cnt++]);

   /* Unpack Offset */
   ipv4Hdr->off = PutHiByte(ipv4Hdr->off, unPkArray[cnt++]);
   ipv4Hdr->off = PutLoByte(ipv4Hdr->off, unPkArray[cnt++]);

   /* Unpack TTL */
   ipv4Hdr->ttl = unPkArray[cnt++];

   /* Unpack Protocol */
   ipv4Hdr->proto= unPkArray[cnt++];

   /* Unpack Checksum */
   ipv4Hdr->chkSum = PutHiByte(ipv4Hdr->chkSum, unPkArray[cnt++]);
   ipv4Hdr->chkSum = PutLoByte(ipv4Hdr->chkSum, unPkArray[cnt++]);

   /* Unpack Source Address */
   temp = PutHiByte(temp, unPkArray[cnt++]);
   temp = PutLoByte(temp, unPkArray[cnt++]);
   ipv4Hdr->srcAddr = PutHiWord(ipv4Hdr->srcAddr, temp);

   temp = PutHiByte(temp, unPkArray[cnt++]);
   temp = PutLoByte(temp, unPkArray[cnt++]);
   ipv4Hdr->srcAddr = PutLoWord(ipv4Hdr->srcAddr, temp);

   /* Unpack Destination Address */
   temp = PutHiByte(temp, unPkArray[cnt++]);
   temp = PutLoByte(temp, unPkArray[cnt++]);
   ipv4Hdr->destAddr = PutHiWord(ipv4Hdr->destAddr, temp);

   temp = PutHiByte(temp, unPkArray[cnt++]);
   temp = PutLoByte(temp, unPkArray[cnt++]);
   ipv4Hdr->destAddr = PutLoWord(ipv4Hdr->destAddr, temp);

#ifdef IPV4_OPTS_SUPPORTED
   /* extract all IPv4 options present in the header */
   extraBytes = ((ipv4Hdr->hdrVer & 0x0f) - 0x05) * 4;

   if (extraBytes > 0)
   {
      hdrParm->u.hdrParmIpv4.ipv4HdrOpt.pres = TRUE;
      hdrParm->u.hdrParmIpv4.ipv4HdrOpt.len = extraBytes;

      ret = SRemPreMsgMult((Data *)hdrParm->u.hdrParmIpv4.ipv4HdrOpt.val,
                           extraBytes, mBuf);
   }   
#endif


   RETVALUE(ret);
} /* hiUnpkIpv4Hdr() */


/*
*
*       Fun:    hiProcHdrParm
*
*       Desc:   Process the header parameters specified by the
*               service user in a HiUiHitUDatReq().
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_proto.c
*
*/
#ifdef ANSI
PUBLIC S16 hiProcHdrParm
(
HiConCb         *conCb,         /* connection */
CmTptAddr       *srcAddr,       /* source address */
CmTptAddr       *remAddr,       /* remote address */
CmIpHdrParm     *hdrParm,       /* header parameters */
Buffer          *mBuf,          /* message buffer */
MsgLen          mLen            /* message length */
)
#else
PUBLIC S16 hiProcHdrParm(conCb, srcAddr, remAddr, hdrParm, mBuf, mLen)
HiConCb         *conCb;         /* connection */
CmTptAddr       *srcAddr;       /* source address */
CmTptAddr       *remAddr;       /* remote address */
CmIpHdrParm     *hdrParm;       /* header parameters */
Buffer          *mBuf;          /* message buffer */
MsgLen          mLen;           /* message length */
#endif
{
   S16          ret;
   U8           c;
   CmIpv4Hdr    ipv4Hdr;
   CmTptParam   lclTPar;
#ifdef IPV4_OPTS_SUPPORTED   
   Bool         appendHdrOpts;
   MsgLen       msgLen;
#endif


   TRC2(hiProcHdrParm);


   /* handle IPv4 header parameters */
   if (hdrParm->type == CM_HDRPARM_IPV4)
   {
      /* does this connection wants header inclusion? */
      if (conCb->hdrIncldFlag & HI_INCLUDE_HDR)
      {
#ifdef IPV4_OPTS_SUPPORTED
         appendHdrOpts = FALSE;

         /* If IP options have not been specified in the header
          * parameters, reset on the socket if necessary.
          */
         if (hdrParm->u.hdrParmIpv4.ipv4HdrOpt.pres == FALSE)
         {
            /* reset ONLY if it was set before, otherwise ignore */
            if (conCb->ipv4OptionSet)
            {
               hdrParm->u.hdrParmIpv4.ipv4HdrOpt.pres = TRUE;
               hdrParm->u.hdrParmIpv4.ipv4HdrOpt.len = 0;
               ret = cmInetSetOpt(&conCb->conFd, CM_SOCKOPT_LEVEL_IP,
                                  CM_INET_OPT_IP_OPTIONS,
                                  &hdrParm->u.hdrParmIpv4.ipv4HdrOpt);
               if (ret != ROK)
                  RETVALUE(ret); 

               hdrParm->u.hdrParmIpv4.ipv4HdrOpt.pres = FALSE;
               conCb->ipv4OptionSet = FALSE;
            }
         }

         /* IP options have been specified; set on the socket if
          * not already set.
          */
         else
         { 
            if (!conCb->ipv4OptionSet)
            {
               ret = cmInetSetOpt(&conCb->conFd, CM_SOCKOPT_LEVEL_IP,
                                  CM_INET_OPT_IP_OPTIONS,
                                  &hdrParm->u.hdrParmIpv4.ipv4HdrOpt);

               /* If setting router alert fails, we have to insert
                * it manually later.
                */
               if (ret == RNA)
                  appendHdrOpts = TRUE;
               else if (ret != ROK)
                  RETVALUE(ret);

               conCb->ipv4OptionSet = TRUE; 
            }
         }   
#endif /* IPV4_OPTS_SUPPORTED */ 


         /* prepare the IPv4 header */
         HI_ZERO(&ipv4Hdr, sizeof (CmIpv4Hdr));
         ipv4Hdr.length = CM_IPV4_HDRLEN + mLen;
         ipv4Hdr.hdrVer = 0x45;


#ifdef IPV4_OPTS_SUPPORTED
         /* add in IP options header length */
         if (appendHdrOpts  &&  hdrParm->u.hdrParmIpv4.ipv4HdrOpt.pres)
         {
            ipv4Hdr.length += hdrParm->u.hdrParmIpv4.ipv4HdrOpt.len;
            ipv4Hdr.hdrVer
               = 0x40 + (5 + hdrParm->u.hdrParmIpv4.ipv4HdrOpt.len/4);
         }
#endif

         /* put in the various header fields */
         if (hdrParm->u.hdrParmIpv4.proto.pres)
            ipv4Hdr.proto = hdrParm->u.hdrParmIpv4.proto.val;
         else
            ipv4Hdr.proto = conCb->protocol;

         if (hdrParm->u.hdrParmIpv4.dfBit.pres)
            ipv4Hdr.off |= CM_DF_MASK;

         if (hdrParm->u.hdrParmIpv4.tos.pres)
            ipv4Hdr.tos = hdrParm->u.hdrParmIpv4.tos.val;

         if (hdrParm->u.hdrParmIpv4.ttl.pres)
            ipv4Hdr.ttl = hdrParm->u.hdrParmIpv4.ttl.val;

         if (srcAddr->type == CM_TPTADDR_IPV4)
            ipv4Hdr.srcAddr = srcAddr->u.ipv4TptAddr.address;

         ipv4Hdr.destAddr = remAddr->u.ipv4TptAddr.address;


         /* add in the IPv4 header */
         ret = hiPkIpv4Hdr(&ipv4Hdr, mBuf);
         if (ret != ROK)
         {
            HILOGERROR_ADD_RES(EHI091, 0, 0,
               "Could not pack IPv4 header");
            RETVALUE(ret);
         }


         /* hi009.104 - Insert Router Alert manually to the end of the 
          * mBuf (Copy the 4 bytes) */
#ifdef IPV4_OPTS_SUPPORTED            
         /* Insert router alert manually at index 20 of the
          * message if the option is present and it has to be done
          * manually.
          */
         if (hdrParm->u.hdrParmIpv4.ipv4HdrOpt.pres  && appendHdrOpts)
         {
            ret = SCpyFixMsg((Data *)&hdrParm->u.hdrParmIpv4.ipv4HdrOpt.val,
                             mBuf, CM_IPV4_HDRLEN,
                             hdrParm->u.hdrParmIpv4.ipv4HdrOpt.len,
                             &msgLen);
            if (ret != ROK
                ||  msgLen != hdrParm->u.hdrParmIpv4.ipv4HdrOpt.len)
               RETVALUE(RFAILED);
         }
#endif
      }


      /* no header inclusion wanted for this connection */
      else 
      {
         /* is IP header inclusion not supported? */
         if (conCb->hdrIncldFlag & HI_HDRINCLD_NT_SUPPORTED)
         {
            lclTPar.type = CM_TPTPARAM_SOCK;
            lclTPar.u.sockParam.numOpts = c = 0;

            if (hdrParm->u.hdrParmIpv4.dfBit.pres)
            {
               if (!(conCb->ipParamMask & HI_DF_MASK))
               {
                  lclTPar.u.sockParam.sockOpts[c].option
                     = CM_SOCKOPT_OPT_DONTFRAGMENT;
                  lclTPar.u.sockParam.sockOpts[c].level
                     = CM_SOCKOPT_LEVEL_IP;
                  lclTPar.u.sockParam.sockOpts[c].optVal.value
                     = CM_SOCKOPT_ENABLE;
                  c++;
                  conCb->ipParamMask |= HI_DF_MASK;
               }
            }
            else 
            {
               if (conCb->ipParamMask & HI_DF_MASK)
               {
                  lclTPar.u.sockParam.sockOpts[c].option
                     = CM_SOCKOPT_OPT_DONTFRAGMENT;
                  lclTPar.u.sockParam.sockOpts[c].level
                     = CM_SOCKOPT_LEVEL_IP;
                  lclTPar.u.sockParam.sockOpts[c].optVal.value
                     = CM_SOCKOPT_DISABLE;
                  c++;
                  conCb->ipParamMask &= ~HI_DF_MASK;
               }
            }

            if (hdrParm->u.hdrParmIpv4.tos.pres)
            {
               if (conCb->ipTos != hdrParm->u.hdrParmIpv4.tos.val)
               {
                  lclTPar.u.sockParam.sockOpts[c].option
                     = CM_SOCKOPT_OPT_TOS;
                  lclTPar.u.sockParam.sockOpts[c].level
                     = CM_SOCKOPT_LEVEL_IP;
                  lclTPar.u.sockParam.sockOpts[c].optVal.value
                     = hdrParm->u.hdrParmIpv4.tos.val;
                  c++;
                  conCb->ipTos = hdrParm->u.hdrParmIpv4.tos.val;
               }
            }

            if (hdrParm->u.hdrParmIpv4.ttl.pres)
            {
               if (conCb->ipTtl != hdrParm->u.hdrParmIpv4.ttl.val)
               {
                  lclTPar.u.sockParam.sockOpts[c].option
                     = CM_SOCKOPT_OPT_TTL;
                  lclTPar.u.sockParam.sockOpts[c].level
                     = CM_SOCKOPT_LEVEL_IP;
                  lclTPar.u.sockParam.sockOpts[c].optVal.value
                     = hdrParm->u.hdrParmIpv4.ttl.val;
                  c++;
                  conCb->ipTtl=hdrParm->u.hdrParmIpv4.ttl.val;
               }
            }

            if ((lclTPar.u.sockParam.numOpts = c) > 0)
            {
               ret = hiSetSockOpt(conCb, &lclTPar);
               if (ret != ROK)
                  RETVALUE(ret);
            }


#if (defined(IPV4_OPTS_SUPPORTED) && (!defined(SS_LINUX) || !defined(SS_VW)))
            /* If IP options have not been specified in the header
             * parameters, reset on the socket if necessary.
             */
            if (hdrParm->u.hdrParmIpv4.ipv4HdrOpt.pres == FALSE)
            {
               if (conCb->ipv4OptionSet)
               {
                  hdrParm->u.hdrParmIpv4.ipv4HdrOpt.pres = TRUE;
                  hdrParm->u.hdrParmIpv4.ipv4HdrOpt.len = 0;
                  ret = cmInetSetOpt(&conCb->conFd, CM_SOCKOPT_LEVEL_IP,
                                     CM_INET_OPT_IP_OPTIONS,
                                     &hdrParm->u.hdrParmIpv4.ipv4HdrOpt);
                  if (ret != ROK)
                     RETVALUE(ret);

                  hdrParm->u.hdrParmIpv4.ipv4HdrOpt.pres = FALSE; 
                  conCb->ipv4OptionSet = FALSE;
               }
            }                        

            /* IP options have been specified; set on the socket if
             * not already set.
             */
            else
            {         
               if (!conCb->ipv4OptionSet)
               {
                  ret = cmInetSetOpt(&conCb->conFd, CM_SOCKOPT_LEVEL_IP,
                                     CM_INET_OPT_IP_OPTIONS,
                                     &hdrParm->u.hdrParmIpv4.ipv4HdrOpt);
                  if (ret == RNA  ||  ret == RFAILED)
                     RETVALUE(RFAILED);

                  conCb->ipv4OptionSet = TRUE;
               }
            }
#endif /* IPV4_OPTS_SUPPORTED */     

         }
      }
   }


#ifdef IPV6_SUPPORTED 
   /* handle IPv6 header parameters */
   else if (hdrParm->type == CM_HDRPARM_IPV6)
   {
      lclTPar.type = CM_TPTPARAM_SOCK;
      lclTPar.u.sockParam.numOpts = 0;

#ifndef CMINETFLATBUF
      if (hdrParm->u.hdrParmIpv6.ttl.pres)
      {
         if (conCb->ipTtl != hdrParm->u.hdrParmIpv6.ttl.val)
         {
            lclTPar.u.sockParam.numOpts = 1;
            lclTPar.u.sockParam.sockOpts[0].option
               = CM_SOCKOPT_OPT_IPV6_TTL;
            lclTPar.u.sockParam.sockOpts[0].level
               = CM_SOCKOPT_LEVEL_IPV6;
            lclTPar.u.sockParam.sockOpts[0].optVal.value
               = hdrParm->u.hdrParmIpv6.ttl.val;
            ret = hiSetSockOpt(conCb, &lclTPar);
            if (ret == RNA  ||  ret == RFAILED)
               RETVALUE(RFAILED);

            conCb->ipTtl = hdrParm->u.hdrParmIpv6.ttl.val;
         }
      }
#endif /* CMINETFLATBUF */         

   }
#endif /* IPV6_SUPPORTED */


   RETVALUE(ROK);
} /* hiProcHdrParm() */


/*
*
*       Fun:    hiProcRxHdr
*
*       Desc:   Process the application header in received TCP
*               data.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_proto.c
*
*/
#ifdef ANSI
PRIVATE S16 hiProcRxHdr
(
HiConCb         *conCb,         /* connection for this message */
Buffer          *mBuf           /* message */
)
#else
PRIVATE S16 hiProcRxHdr(conCb, mBuf)
HiConCb         *conCb;         /* connection for this message */
Buffer          *mBuf;          /* message */
#endif
{
   U16          i, l1, l2;
   U8           arr[HI_MAX_HDR_LEN];
   HiHdrInfo    *hdr;
   HiAlarmInfo  alInfo;
   MsgLen       mLen;
   U8           tcpHdrIdx; /* KW fixes for acc compilation  */


   TRC2(hiProcRxHdr);


   l1 = l2 = 0;

   /* hi018.201 : mLen is initialized to zero */
   mLen = 0;
   /* get the length of the message */
   if (SFndLenMsg(mBuf, &mLen) != ROK)
   {
      HI_INC_ERRSTS(hiCb.errSts.rxMsgVerErr);
      alInfo.spId = conCb->sap->spId;
      alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
      hiSendAlarm(LCM_CATEGORY_PROTOCOL, LCM_EVENT_PI_INV_EVT,
                  LCM_CAUSE_DECODE_ERR, &alInfo); 
      HI_FREE_BUF(mBuf);

      RETVALUE(RFAILED);
   }


   /* check what kind of processing we have to do */
   if (conCb->srvcType == HI_SRVC_TCP_TPKT_HDR
       ||  conCb->srvcType == HI_SRVC_UDP_TPKT_HDR)
   {
      /* if the message header has not come, wait for it */
      if (mLen < HI_TPKT_HDR_LEN)
      {
         conCb->awaitHdr = TRUE;
         conCb->pendLen = 0;

         RETVALUE(ROK);
      }
      conCb->awaitHdr = FALSE;

      /* extract the header */
      SRemPreMsgMult(arr, HI_TPKT_HDR_LEN, mBuf);
      if (arr[0] != HI_TPKT_HDR_VERSION)
      {
         HI_INC_ERRSTS(hiCb.errSts.rxMsgVerErr);
         HI_FREE_BUF(mBuf);
         alInfo.spId = conCb->sap->spId;
         alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
         hiSendAlarm(LCM_CATEGORY_PROTOCOL, LCM_EVENT_PI_INV_EVT,
                     LCM_CAUSE_DECODE_ERR, &alInfo);

         RETVALUE(RFAILED);
      }

      /* obtain the packet length from the header */
      l1 = PutHiByte(l1, arr[2]);
      l1 = PutLoByte(l1, arr[3]);

      /* initialize the length variables in conCb */
      conCb->pendLen = l1 - HI_TPKT_HDR_LEN;
      conCb->rxLen -= HI_TPKT_HDR_LEN;
   }


   /* other header types */
   else
   {
      /* KW fixes for acc compilation : Start */
      tcpHdrIdx = (conCb->srvcType >> HI_SRVCTYPE_MASK) - 1;
      if(tcpHdrIdx >= LHI_MAX_HDR_TYPE)
      {
         HI_FREE_BUF(mBuf);
         alInfo.type = LHI_ALARMINFO_MEM_ID;
         alInfo.inf.mem.region = conCb->sap->uiPst.region;
         alInfo.inf.mem.pool = conCb->sap->uiPst.pool;
         hiSendAlarm(LCM_CATEGORY_PROTOCOL, LCM_EVENT_PI_INV_EVT,
               LCM_CAUSE_DECODE_ERR, &alInfo);
         RETVALUE(RFAILED); 
      }
      hdr = &conCb->sap->cfg.hdrInf[tcpHdrIdx];
      /* KW fixes for acc compilation: End  */
      if ((U32)mLen < hdr->hdrLen)
      {
         conCb->awaitHdr = TRUE;
         conCb->pendLen = 0;

         RETVALUE(ROK);
      }
      conCb->awaitHdr = FALSE;

      /* extract the header */
      SRemPreMsgMult(arr, (S16)hdr->hdrLen, mBuf);

      /* obtain the packet length from the header */
      if (hdr->lenLen == 1)
      {
         l2 = arr[hdr->offLen];
         conCb->pendLen = l2;
      }
      else if (hdr->lenLen == 2)
      {
         l1 = PutHiByte(l1, arr[hdr->offLen]);
         l1 = PutLoByte(l1, arr[hdr->offLen+1]);
         conCb->pendLen = l1;
      }
      else 
      {
         l1 = PutHiByte(l1, arr[hdr->offLen]);
         l1 = PutLoByte(l1, arr[hdr->offLen + 1]);
         /*hi028.201: Fix for Klockworks issue*/
         l2  =(U16)PutHiWord(l2, l1);
         l1 = PutHiByte(l1, arr[hdr->offLen + 2]);
         l1 = PutLoByte(l1, arr[hdr->offLen + 3]);
         l2  = (U16)PutLoWord(l2, l1);

         if (hdr->lenLen == 3)
            l2 >>= 8;

         conCb->pendLen = l2;
      }

      if (!(hdr->flag & LHI_LEN_INCL_HDR))
         conCb->pendLen += hdr->hdrLen;

      /* put back the header */
      /*hi028.201: Fix for Klockworks issue*/
      for (i = (U16)hdr->hdrLen;  i > 0;  i--)
      {
         if (SAddPreMsg(arr[i-1], mBuf) != ROK)
         {
            HI_FREE_BUF(mBuf);
            alInfo.type = LHI_ALARMINFO_MEM_ID;
            alInfo.inf.mem.region = conCb->sap->uiPst.region;
            alInfo.inf.mem.pool = conCb->sap->uiPst.pool;
            hiSendAlarm(LCM_CATEGORY_PROTOCOL, LCM_EVENT_PI_INV_EVT,
                        LCM_CAUSE_DECODE_ERR, &alInfo);
            RETVALUE(RFAILED);
         }
      }
   }


   RETVALUE(ROK);
} /* hiProcRxHdr() */


/*
*
*       Fun:    hiHndlTcpData
*
*       Desc:   Process the received TCP octet stream. This takes
*               care of the cases when a TPKT is received in
*               multiple fragments, or when multiple TPKTs are
*               received in a single fragment. When the full
*               packet is received, a data indication is issued.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_proto.c
*
*/
#ifdef ANSI
PRIVATE S16 hiHndlTcpData
(
HiConCb         *conCb,         /* connection block */
Buffer          *mBuf,          /* received message */
U32             mLen            /* actual length of the data received */
)
#else
PRIVATE S16 hiHndlTcpData(conCb, mBuf, mLen)
HiConCb         *conCb;         /* connection block */
Buffer          *mBuf;          /* received message */
U32             mLen;           /* actual length of the data received */
#endif
{
   S16          ret;
   /* hi018.201:  tBuf is initialized to NULLP */
   Buffer       *tBuf = NULLP;
   MsgLen       tLen;
   Queue        rxQ;
   QLen         qLen;
   HiAlarmInfo  alInfo;


   TRC2(hiHndlTcpData);


   /* initialize the receive queue */
   ret = SInitQueue(&rxQ);
   if (ret != ROK)
   {
      HI_FREE_BUF(mBuf);
      RETVALUE(RFAILED);
   }

   /* get any previously received data */
   if (conCb->rxBuf != NULLP)
   {
      ret = SCatMsg(mBuf, conCb->rxBuf, M2M1);
      if (ret != ROK)
      {
         HI_FREE_BUF(mBuf);
         alInfo.type = LHI_ALARMINFO_MEM_ID;
         alInfo.inf.mem.region = conCb->sap->uiPst.region;
         alInfo.inf.mem.pool = conCb->sap->uiPst.pool;
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                     LCM_CAUSE_UNKNOWN, &alInfo);
         RETVALUE(RFAILED);
      }

      HI_FREE_BUF(conCb->rxBuf);
      conCb->rxBuf = NULLP;
   }

   /* no previously received data, we're awaiting the header still */
   else
      conCb->awaitHdr = TRUE;


   /* iterate over received data, breaking out TPKTs */
   tLen = mLen;
   for (; ;)
   {
      /* initialize received length */
      conCb->rxLen += tLen;

      /* we process the header only if waiting for it */
      if (conCb->awaitHdr)
      {
         if (hiProcRxHdr(conCb, mBuf) != ROK)
         {
            ret = RFAILED;
            break;
         }
      }

      /* If the full header or message has not arrived, queue the
       * data.
       */
      if (conCb->awaitHdr  ||  conCb->pendLen > conCb->rxLen)
      {
         conCb->rxBuf = mBuf;
         break;
      }

      /* received a full packet? */
      if (conCb->pendLen == conCb->rxLen)
      {
         conCb->rxLen = conCb->pendLen = 0;

         /* queue up the TPKT */
         SQueueLast(mBuf, &rxQ);
         break;
      }

      /* received more than one packet? */
      else if (conCb->rxLen > conCb->pendLen)
      {  
         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
         HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
                "SSegMsg(mBuf1(%p), idx(%ld), mBuf2(%p))\n",
                (Ptr)mBuf, conCb->pendLen, (Ptr)tBuf));
#else
         HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
                "SSegMsg(mBuf1(%p), idx(%d), mBuf2(%p))\n",
                (Ptr)mBuf, conCb->pendLen, (Ptr)tBuf));
#endif

         /* segment the message */
         ret = SSegMsg(mBuf, (U16)conCb->pendLen, &tBuf);
         if (ret != ROK)
         {
            HI_FREE_BUF(mBuf);
            alInfo.inf.mem.region = conCb->sap->uiPst.region;
            alInfo.inf.mem.pool = conCb->sap->uiPst.pool;
            hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                        LCM_CAUSE_UNKNOWN, &alInfo);
            ret = ROUTRES;
            break;
         }

         /* queue up the TPKT */
         SQueueLast(mBuf, &rxQ);

         /* record how many bytes remain */
         /*hi028.201: Fix for Klockworks issue*/
         tLen = (S16)(conCb->rxLen - conCb->pendLen);

         /* set up to work on the remainder */
         conCb->rxLen = conCb->pendLen = 0;
         conCb->awaitHdr = TRUE;
         mBuf = tBuf;

         /* if there's no more data, done for now */
         if (!tLen)
            break;
      }
   }

   /* hi018.201 : qLen is initialized to zero */
   qLen = 0;
   /* if we queued up any TPKTs, send them to the service user */
   SFndLenQueue(&rxQ, &qLen);
   while (qLen)
   {
      qLen--;
      SDequeueFirst(&tBuf, &rxQ);
      HI_DATIND(conCb, tBuf);
   }


   RETVALUE(ROK);
} /* hiHndlTcpData() */


/*
*
*       Fun:    hiHndlUdpData
*
*       Desc:   Process UDP datagrams received from the peer. This
*               takes care of cases when a single packet is
*               received or when multiple TPKTs are received in a
*               single datagram (a TPKT cannot arrive in more than
*               one datagram).
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_proto.c
*
*/
#ifdef ANSI
PRIVATE Void hiHndlUdpData
(
HiConCb         *conCb,         /* connection */
Buffer          *mBuf,          /* received message */
MsgLen          mLen,           /* message length */
CmTptAddr       *srcAddr,       /* source address */
CmTptAddr       *destAddr,      /* destination address */
CmIpHdrParm     *hdrParm,       /* IP header */
HiLocalInf      *lif            /* local i/f on which pkt arrived */
)
#else
PRIVATE Void hiHndlUdpData(conCb, mBuf, mLen, srcAddr, destAddr,
                          hdrParm, lif)
HiConCb         *conCb;         /* connection */
Buffer          *mBuf;          /* received message */
MsgLen          mLen;           /* message length */
CmTptAddr       *srcAddr;       /* source address */
CmTptAddr       *destAddr;      /* destination address */
CmIpHdrParm     *hdrParm;       /* IP header */
HiLocalInf      *lif;           /* local i/f on which pkt arrived */
#endif
{
   S16          ret;
   Queue        rxQ;
   QLen         qLen;
   /* hi018.201 : tBuf is initialized to NULLP */
   Buffer       *tBuf = NULLP;
   HiAlarmInfo  alInfo;


   TRC2(hiHndlUdpData);


   /* initialize the receive queue */
   ret = SInitQueue(&rxQ);
   if (ret != ROK)
   {
      HI_FREE_BUF(mBuf);
      RETVOID;
   }


   /* iterate over received data, breaking out TPKTs */
   for (; ;)
   {
      conCb->rxLen = mLen;

      /* process the IP header */
      if (hiProcRxHdr(conCb, mBuf) != ROK)
         break;

      /* received a full TPKT? */
      if (conCb->pendLen == conCb->rxLen)
      {
         conCb->pendLen = conCb->rxLen = 0;
         SQueueLast(mBuf, &rxQ);
         break;
      }

      /* If the full header or message has not arrived yet, for
       * UDP this is treated as a decode error.
       */
      else if (conCb->awaitHdr  ||  conCb->pendLen > conCb->rxLen)
      {
         HI_FREE_BUF(mBuf);
         alInfo.spId = conCb->sap->spId;
         alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
         hiSendAlarm(LCM_CATEGORY_PROTOCOL, LCM_EVENT_PI_INV_EVT,
                     LCM_CAUSE_DECODE_ERR, &alInfo);
         break;
      }

      /* received more than one packet */
      else
      {
         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
         HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
                "SSegMsg(mBuf1(%p), idx(%ld), mBuf2(%p))\n",
                 (Ptr)mBuf, conCb->pendLen, (Ptr)tBuf));
#else
         HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
                "SSegMsg(mBuf1(%p), idx(%d), mBuf2(%p))\n",
                 (Ptr)mBuf, conCb->pendLen, (Ptr)tBuf));
#endif

         /* segment the message */
         ret = SSegMsg(mBuf, (U16)conCb->pendLen, &tBuf);
         if(ret !=ROK)
         {
            HI_FREE_BUF(mBuf);
            alInfo.spId = conCb->sap->spId;
            alInfo.type = LHI_ALARMINFO_MEM_ID;
            alInfo.inf.mem.region = conCb->sap->uiPst.region;
            alInfo.inf.mem.pool = conCb->sap->uiPst.pool;
            hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                        LCM_CAUSE_UNKNOWN, &alInfo);
            break;
         }

         /* queue up the TPKT */
         SQueueLast(mBuf, &rxQ);

         /* record how many bytes remain */
         mLen -= conCb->pendLen;

         /* set up to work on the remainder */
         conCb->pendLen = 0;
         mBuf = tBuf;

         /* if there's no more data, done for now */
         if (!mLen)
            break;
      }
   }

   /* hi018.201 : qLen is initialized to zero */
   qLen = 0;

   /* if we queued up any TPKTs, send them to the service user */
   SFndLenQueue(&rxQ, &qLen);
   while (qLen)
   {
      qLen--;
      SDequeueFirst(&tBuf, &rxQ);

#ifdef H323_PERF
      TAKE_TIMESTAMP("L/T Rcvd TCP Pkt on UDP, in HI");
#endif

      HI_UDATIND(conCb, srcAddr, destAddr, hdrParm, lif, tBuf);
   }


   RETVOID; 
} /* hiHndlUdpData() */


/*
*
*       Fun:    hiHndlRawMsg
*
*       Desc:   Process raw IPv4 packets received from the peer.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy3.c
*
*/
#ifdef ANSI
PRIVATE S16 hiHndlRawMsg
(
HiConCb         *conCb,         /* connection */
Buffer          *mBuf,          /* received message buffer */
U32             mLen,           /* message length */
HiLocalInf      *lif            /* local i/f on which pkt arrived */
)
#else
PRIVATE S16 hiHndlRawMsg(conCb, mBuf, mLen, lif)
HiConCb         *conCb;         /* connection */
Buffer          *mBuf;          /* received message buffer */
U32             mLen;           /* message length */
HiLocalInf      *lif;           /* local i/f on which pkt arrived */
#endif
{
   S16          ret;
   CmIpv4Hdr    ipHdr;
   CmIpHdrParm  hdrParm;
   CmTptAddr    srcAddr, destAddr;


   TRC2(hiHndlRawMsg);

   /* hi002.105 (hi028.104) - make len unused */
   UNUSED(mLen);

   /* initialize locals */
   HI_ZERO(&ipHdr, sizeof (CmIpv4Hdr));
   HI_ZERO(&hdrParm, sizeof (CmIpHdrParm));


   /* a raw packet must contain an IP header */
   ret = hiUnpkIpv4Hdr(mBuf, &ipHdr, &hdrParm);

#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
      HI_FREE_BUF(mBuf);
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "hiHndlRawMsg(): could not unpack IPv4 header\n"));
      RETVALUE(RFAILED);
   }
#endif

   
   /* set up the IPv4 header parameters */
   hdrParm.type = CM_HDRPARM_IPV4;

   hdrParm.u.hdrParmIpv4.proto.pres = TRUE;
   hdrParm.u.hdrParmIpv4.proto.val  = ipHdr.proto;

   if (ipHdr.off & CM_DF_MASK)
   {
      hdrParm.u.hdrParmIpv4.dfBit.pres = TRUE;
      hdrParm.u.hdrParmIpv4.dfBit.val = 1;
   }
   else 
      hdrParm.u.hdrParmIpv4.dfBit.pres = FALSE;

   hdrParm.u.hdrParmIpv4.tos.pres = TRUE;
   hdrParm.u.hdrParmIpv4.tos.val = ipHdr.tos;

   hdrParm.u.hdrParmIpv4.ttl.pres = TRUE; 
   hdrParm.u.hdrParmIpv4.ttl.val = ipHdr.ttl;

   srcAddr.type = destAddr.type = CM_TPTADDR_IPV4;

   /* ports are not relevant in a raw socket */
   srcAddr.u.ipv4TptAddr.port = destAddr.u.ipv4TptAddr.port = 0;

   srcAddr.u.ipv4TptAddr.address = ipHdr.srcAddr;
   destAddr.u.ipv4TptAddr.address = ipHdr.destAddr;

   HI_UDATIND(conCb, &srcAddr, &destAddr, &hdrParm, lif, mBuf);


   RETVALUE(ROK);
} /* hiHndlRawMsg() */

#ifdef IPV6_SUPPORTED
/*
*
*       Fun:    hiHndlIpv6RawMsg
*
*       Desc:   Process raw IPv6 messages received from the peer.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy3.c
*
*/
#ifdef ANSI
PRIVATE S16 hiHndlIpv6RawMsg
(
HiConCb         *conCb,         /* connection */
Buffer          *mBuf,          /* received message buffer */
U32             mLen,           /* message length */
CmIpHdrParm     *hdrParm,       /* IPv6 header parameters */
HiLocalInf      *lif            /* local i/f on which pkt arrived */
)
#else
PRIVATE S16 hiHndlIpv6RawMsg(conCb, mBuf, mLen, hdrParm, lif)
HiConCb         *conCb;         /* connection */
Buffer          *mBuf;          /* received message buffer */
U32             mLen;           /* message length */
CmIpHdrParm     *hdrParm;       /* IPv6 header parameters */
HiLocalInf      *lif;           /* local i/f on which pkt arrived */
#endif
{
   TRC2(hiHndlRawMsg);

   /* hi002.105 removing compiler warning */
   UNUSED(mLen); 
   /* send the received packet to the user */
   HI_UDATIND(conCb, &conCb->peerAddr, &conCb->locTptAddr,
              hdrParm, lif, mBuf);


   RETVALUE(ROK);
} /* hiHndlIpv6RawMsg */

#endif /* IPV6_SUPPORTED */



/* hi032.201: Modified function to support filteration of ICMP messages 
 * as per user request and protected this changes under CM_ICMP_FILTER_SUPPORT flag */


/*
*
*       Fun:    hiRecvIcmpMsg
*
*       Desc:   Receive an incoming ICMP message and distribute it
*               to all interested listeners.
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_bdy3.c
*
*/
#ifndef CM_ICMP_FILTER_SUPPORT
#ifdef ANSI
PRIVATE Void hiRecvIcmpMsg
(
Void
)
#else
PRIVATE Void hiRecvIcmpMsg()
#endif
#else /* CM_ICMP_FILTER_SUPPORT */
#ifdef ANSI
PRIVATE Void hiRecvIcmpMsg
(
HiConCb      *con
)
#else
PRIVATE Void hiRecvIcmpMsg(con)
HiConCb      *con;
#endif
#endif /* CM_ICMP_FILTER_SUPPORT */
{
   S16          ret;
   U16          idx;
   Buffer       *mBuf;
   /* hi018.201 : Initialized tBuf to NULLP */
   Buffer       *tBuf = NULLP;
   MsgLen       mLen, count;
   HiConCb      *conCb;
   HiAlarmInfo  alInfo;
   CmLList      *l;
   CmTptAddr    srcAddr, destAddr;
   CmIpHdrParm  hdrParm;
   CmIpv4Hdr    ipv4Hdr;
   CmIcmpv4Hdr  icmpHdr;
   U8           msgType, msgCode, protocol;
   Bool         sendflag;
   HiThrMsg     tMsg;
   HiLocalInf   *lif;

#ifdef LOCAL_INTF
   HiLocalInf   locIf;

   lif = &locIf;
   HI_ZERO(lif, sizeof (CmTptLocalInf));

#else

   lif = NULLP;

#endif


   TRC2(hiRecvIcmpMsg);


   /* initialize locals */
   alInfo.spId = -1;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
   HI_ZERO(&hdrParm, sizeof (CmIpHdrParm));


#ifdef HI_MULTI_THREADED
   HI_LOCKICMP(CM_NETADDR_IPV4);
#endif


   /* If there are no ICMP listeners, the ICMP fd is closed, so do
    * nothing.
    */
#ifndef CM_ICMP_FILTER_SUPPORT 
   if (hiCb.icmpUsers == 0)
#else
      if(hiCb.icmpInfo[con->idx].icmpUsers == 0)
#endif /* CM_ICMP_FILTER_SUPPORT */
   {
#ifdef HI_MULTI_THREADED
      HI_UNLOCKICMP(CM_NETADDR_IPV4);
#endif
      RETVOID;
   }


   /* read the available data on this socket */
   mLen = CM_INET_READ_ANY;
   /* hi016.201 : Typecasting lif  with CmInetLocalInf */
#ifndef CM_ICMP_FILTER_SUPPORT
   HI_RECVMSG(&hiCb.icmpConFd, &srcAddr, &mBuf, &mLen, NULLP, (CmInetLocalInf *)lif, ret);
#else
   HI_RECVMSG(&hiCb.icmpInfo[con->idx].icmpConFd, &srcAddr, &mBuf, &mLen, NULLP, (CmInetLocalInf *)lif, ret);
#endif



   /* check for receive errors */
   if (ret != ROK)
   {
      HI_INC_ERRSTS(hiCb.errSts.sockRxErr);
      tMsg.type = HI_THR_DELCON_DISCIND;
      if (ret == ROUTRES)
      {
         alInfo.type = LHI_ALARMINFO_MEM_ID;
         alInfo.inf.mem.region = hiCb.init.region;
         alInfo.inf.mem.pool = hiCb.init.pool;
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                     LHI_CAUSE_SOCK_RECV_ERR, &alInfo);
         tMsg.disc.reason = HI_OUTOF_RES;
      }
      else
      {
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_INET_ERR,
                     LHI_CAUSE_SOCK_RECV_ERR, &alInfo);
         tMsg.disc.reason = HI_SOCK_ICMP_RECV_ERR;
      }

      /* disconnect the connections in the ICMP list */
#ifndef CM_ICMP_FILTER_SUPPORT
      for (conCb = (HiConCb *)CM_LLIST_FIRST_NODE(&hiCb.icmpLstCp, l);
            conCb;
            conCb = (HiConCb *)CM_LLIST_NEXT_NODE(&hiCb.icmpLstCp, l))
#else
         for (conCb = (HiConCb *)CM_LLIST_FIRST_NODE(&hiCb.icmpInfo[con->idx].icmpLstCp, l);
              conCb;
              conCb = (HiConCb *)CM_LLIST_NEXT_NODE(&hiCb.icmpInfo[con->idx].icmpLstCp, l))
#endif /* CM_ICMP_FILTER_SUPPORT */

      {
         tMsg.spId = conCb->sap->spId;
         tMsg.spConId = conCb->spConId;
         hiSendThrMsg(conCb->fdGrpNum, &tMsg);
      }

#ifdef HI_MULTI_THREADED
      HI_UNLOCKICMP(CM_NETADDR_IPV4);
#endif

      RETVOID;
   }


   /* update statistics */
   hiCb.fdGrps[0]->genRxSts.numRxBytes += mLen;

   /* hi018.201 : Initialized ipv4Hdr */
   cmMemset((U8*)&ipv4Hdr, 0, sizeof(CmIpv4Hdr));
   /* unpack the IPv4 header from this packet */
   if (NULLP != mBuf)
   {
      ret = hiUnpkIpv4Hdr(mBuf, &ipv4Hdr, &hdrParm);
   }
   else
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "hiRecvIcmpMsg(): mBuf is NULL\n"));
      /* Klock work fix ccpu00147991 */
#ifdef HI_MULTI_THREADED
      HI_UNLOCKICMP(CM_NETADDR_IPV4);
#endif
      RETVOID;
   }
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
      HI_FREE_BUF(mBuf);
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "hiRecvIcmpMsg(): could not unpack IPv4 header\n"));

#ifdef HI_MULTI_THREADED
      HI_UNLOCKICMP(CM_NETADDR_IPV4);
#endif

      RETVOID;
   }
#endif


   /* set up the parameters for the unit data indication(s) */
   hdrParm.type = CM_HDRPARM_IPV4;

   hdrParm.u.hdrParmIpv4.proto.pres = TRUE;
   hdrParm.u.hdrParmIpv4.proto.val = ipv4Hdr.proto;

   hdrParm.u.hdrParmIpv4.dfBit.pres
      = (ipv4Hdr.off & CM_DF_MASK ? TRUE : FALSE);

   hdrParm.u.hdrParmIpv4.tos.pres = TRUE;
   hdrParm.u.hdrParmIpv4.tos.val = ipv4Hdr.tos;
   hdrParm.u.hdrParmIpv4.ttl.pres = TRUE; 
   hdrParm.u.hdrParmIpv4.ttl.val = ipv4Hdr.ttl;

   /* extract the ICMP header */
   /* hi018.201 : Initialized icmpHdr */
   cmMemset((U8 *)&icmpHdr, 0, sizeof(CmIcmpv4Hdr));
   if (NULLP != mBuf)
   SCpyMsgFix(mBuf, 0, sizeof (CmIcmpv4Hdr), (Data *)&icmpHdr, &count);

   msgType = icmpHdr.icmpType;
   msgCode = icmpHdr.icmpCode;
   protocol = icmpHdr.u3.icmpIpHdr.proto;
   
   srcAddr.type = destAddr.type = CM_TPTADDR_IPV4;

   /* port is not relevant in a raw socket */
   srcAddr.u.ipv4TptAddr.port = destAddr.u.ipv4TptAddr.port = 0;

   srcAddr.u.ipv4TptAddr.address = ipv4Hdr.srcAddr;
   destAddr.u.ipv4TptAddr.address = ipv4Hdr.destAddr;


   /* Iterate through all the connections in the ICMP listeners
    * list. Deliver this message to each interested connection.
    */
#ifndef CM_ICMP_FILTER_SUPPORT
   for (conCb = (HiConCb *)CM_LLIST_FIRST_NODE(&hiCb.icmpLstCp, l);
         conCb;
         conCb = (HiConCb *)CM_LLIST_NEXT_NODE(&hiCb.icmpLstCp, l))
#else
      for (conCb = (HiConCb *)CM_LLIST_FIRST_NODE(&hiCb.icmpInfo[con->idx].icmpLstCp, l);
            conCb;
            conCb = (HiConCb *)CM_LLIST_NEXT_NODE(&hiCb.icmpInfo[con->idx].icmpLstCp, l))
#endif

   {
      sendflag = FALSE;

      /* only connected blocks */
      if (conCb->state != HI_ST_CONNECTED
          &&  conCb->state != HI_ST_CONNECTED_NOWR)
         continue;

      /* check if this connection is interested */
      if (conCb->icmpMask & ALL_ICMP_MSG)
         sendflag = TRUE;
      else if (conCb->icmpMask & ALL_PROTO_SPEC_MSG)
      {
         if (protocol == conCb->filterProtocol)
            sendflag = TRUE;
      }
      else if (conCb->icmpMask & ALL_FLTRD_ICMP_MSG)
      {
         for (idx = 0;  idx < conCb->numFilters;  idx++)
         { 
            if (conCb->icmpError[idx].errType != msgType)
               continue;

            if (conCb->icmpError[idx].errCodeMask & (1 << msgCode))
               sendflag = TRUE;

            break;
         }
      }
      else if (conCb->icmpMask & FLTRD_PROTO_SPEC_MSG)
      {
         if (protocol == conCb->filterProtocol)
         {
            for (idx = 0;  idx < conCb->numFilters;  idx++)
            {
               if (conCb->icmpError[idx].errType != msgType)
                  continue;

#ifndef CM_ICMP_FILTER_SUPPORT
               if (conCb->icmpError[idx].errCodeMask & (1 << msgCode))
#else
               if (conCb->icmpError[idx].errCodeMask == msgCode)
#endif

                  {
                  sendflag = TRUE;
                  break;
               }
            }
         }
      }

      /* do we send the message to this connection? */
      if (sendflag)
      {
         /* add a reference to the message */
         ret = SAddMsgRef(mBuf, conCb->sap->uiPst.region,
                          conCb->sap->uiPst.pool, &tBuf);
         if (ret != ROK)
         {
            alInfo.type = LHI_ALARMINFO_MEM_ID;
            alInfo.inf.mem.region = conCb->sap->uiPst.region;
            alInfo.inf.mem.pool = conCb->sap->uiPst.pool;
            hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                        LHI_CAUSE_SOCK_RECV_ERR, &alInfo);
            continue;
         }

         /* issue the unit data indication */
         HI_UDATIND(conCb, &srcAddr, &destAddr, &hdrParm, lif, tBuf);
      }
   }


   /* done with the message */
   HI_FREE_BUF(mBuf);


#ifdef HI_MULTI_THREADED
   HI_UNLOCKICMP(CM_NETADDR_IPV4);
#endif


   RETVOID;
} /* hiRecvIcmpMsg() */


/* hi032.201: Modified function to support filteration of ICMP messages 
 * as per user request and protected this changes under CM_ICMP_FILTER_SUPPORT flag */

#ifdef IPV6_SUPPORTED
/*
*
*       Fun:    hiErrHndlIcmp6Msg
*
*       Desc:   Perform error handling on processing of incoming ICMPv6 message
*               and distribute it to all interested listeners.
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_bdy3.c
*
*/
#ifdef ANSI
PRIVATE Void hiErrHndlIcmp6Msg
(
HiAlarmInfo  *alInfo,
S16          ret
)
#else
PRIVATE Void hiErrHndlIcmp6Msg(alInfo, ret)
HiAlarmInfo  *alInfo;
S16           ret;
#endif
{
   HiThrMsg     tMsg;
   HiConCb      *conCb;
   CmLList      *l;

      HI_INC_ERRSTS(hiCb.errSts.sockRxErr);
      tMsg.type = HI_THR_DELCON_DISCIND;
      if (ret == ROUTRES)
      {
         alInfo->type = LHI_ALARMINFO_MEM_ID;
         alInfo->inf.mem.region = hiCb.init.region;
         alInfo->inf.mem.pool = hiCb.init.pool;
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                     LHI_CAUSE_SOCK_RECV_ERR, alInfo);
         tMsg.disc.reason = HI_OUTOF_RES;
      }
      else
      {
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_INET_ERR,
                     LHI_CAUSE_SOCK_RECV_ERR, alInfo);
         tMsg.disc.reason = HI_SOCK_ICMP_RECV_ERR;
      }

      /* disconnect the connections in the ICMP list */
#ifndef CM_ICMP_FILTER_SUPPORT
      for (conCb = (HiConCb *)CM_LLIST_FIRST_NODE(&hiCb.icmp6LstCp, l);
            conCb;
            conCb = (HiConCb *)CM_LLIST_NEXT_NODE(&hiCb.icmp6LstCp, l))
#else
         for (conCb = (HiConCb *)CM_LLIST_FIRST_NODE(&hiCb.icmpInfo[con->idx].icmp6LstCp, l);
              conCb;
              conCb = (HiConCb *)CM_LLIST_NEXT_NODE(&hiCb.icmpInfo[con->idx].icmp6LstCp, l))
#endif /* CM_ICMP_FILTER_SUPPORT */
      {
         tMsg.spId = conCb->sap->spId;
         tMsg.spConId = conCb->spConId;
         hiSendThrMsg(conCb->fdGrpNum, &tMsg);
      }

#ifdef HI_MULTI_THREADED
      HI_UNLOCKICMP(CM_NETADDR_IPV6);
#endif

      RETVOID;
}


/*
*
*       Fun:    hiRecvIcmp6Msg
*
*       Desc:   Receive an incoming ICMPv6 message and distribute
*               it to all interested listeners.
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_bdy3.c
*
*/
#ifndef CM_ICMP_FILTER_SUPPORT
#ifdef ANSI
PRIVATE Void hiRecvIcmp6Msg
(
Void
)
#else
PRIVATE Void hiRecvIcmp6Msg()
#endif
#else /* CM_ICMP_FILTER_SUPPORT */
#ifdef ANSI
PRIVATE Void hiRecvIcmp6Msg
(
HiConCb      *con
)
#else
PRIVATE Void hiRecvIcmp6Msg(con)
HiConCb      *con;
#endif
#endif /* CM_ICMP_FILTER_SUPPORT */

{
   S16          ret;
   U16          idx;
   Buffer       *mBuf, *tBuf;
   MsgLen       mLen, count;
   CmTptAddr    srcAddr, destAddr;
   HiConCb      *conCb; 
   HiAlarmInfo  alInfo;
   CmIpHdrParm  hdrParm;
   CmIcmpv6Hdr  icmp6Hdr;
   U8           msgType, msgCode;
   Bool         sendflag;
   HiLocalInf   *lif;
   /* hi001.105 - Fix compile error for IPv6 */
   CmLList      *l;

#ifdef LOCAL_INTF
   HiLocalInf   locIf;

   lif = &locIf;
   HI_ZERO(lif, sizeof (CmTptLocalInf));

#else

   lif = NULLP;

#endif


   TRC2(hiRecvIcmp6Msg);


   /* initialize locals */
   alInfo.spId = -1;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
   HI_ZERO(&hdrParm, sizeof (CmIpHdrParm));


#ifdef HI_MULTI_THREADED
   HI_LOCKICMP(CM_NETADDR_IPV6);
#endif


   /* If there are no ICMP listeners, the ICMP fd is closed, so do
    * nothing.
    */
#ifndef CM_ICMP_FILTER_SUPPORT
   if (hiCb.icmp6Users == 0)
#else
    if (hiCb.icmpInfo[con->idx].icmp6Users == 0)
#endif /* CM_ICMP_FILTER_SUPPORT */
   {
#ifdef HI_MULTI_THREADED
      HI_UNLOCKICMP(CM_NETADDR_IPV6);
#endif
      RETVOID;
   }


   /* read the available data on this socket */
   mLen = CM_INET_READ_ANY;
   /* hi016.201 : Typecasting lif  with CmInetLocalInf */
#ifndef CM_ICMP_FILTER_SUPPORT
   HI_RECVMSG(&hiCb.icmp6ConFd, &srcAddr, &mBuf, &mLen, NULLP, (CmInetLocalInf *)lif, ret);
#else
   HI_RECVMSG(&hiCb.icmpInfo[con->idx].icmp6ConFd, &srcAddr, &mBuf, &mLen, NULLP, (CmInetLocalInf *)lif, ret);
#endif

   /* check for receive errors */
   if (ret != ROK)
   {
      /*Perform Error handling*/
      hiErrHndlIcmp6Msg(&alInfo, ret);
      RETVOID;
   }


   /* update statistics */
   hiCb.fdGrps[0]->genRxSts.numRxBytes += mLen;


   /* set up the parameters for the unit data indication(s) */
   hdrParm.type = CM_HDRPARM_ICMP6;

   /* extract the ICMPv6 header */
   SCpyMsgFix(mBuf, 0, sizeof (CmIcmpv6Hdr), (Data *)&icmp6Hdr, &count);

   msgType = icmp6Hdr.icmp6_type;
   msgCode = icmp6Hdr.icmp6_code;
   
   srcAddr.type = destAddr.type = CM_TPTADDR_IPV6;
   srcAddr.u.ipv6TptAddr.port = destAddr.u.ipv6TptAddr.port = 0;


   /* Iterate through all the connections in the ICMPv6 listeners
    * list. Deliver this message to each interested connection.
    */
#ifndef CM_ICMP_FILTER_SUPPORT
   for (conCb = (HiConCb *)CM_LLIST_FIRST_NODE(&hiCb.icmp6LstCp, l);
         conCb;
         conCb = (HiConCb *)CM_LLIST_NEXT_NODE(&hiCb.icmp6LstCp, l))
#else
      for (conCb = (HiConCb *)CM_LLIST_FIRST_NODE(&hiCb.icmpInfo[con->idx].icmp6LstCp, l);
           conCb;
           conCb = (HiConCb *)CM_LLIST_NEXT_NODE(&hiCb.icmpInfo[con->idx].icmp6LstCp, l))
#endif

   {
      sendflag = FALSE;

      /* only connected blocks */
      if (conCb->state != HI_ST_CONNECTED
          &&  conCb->state != HI_ST_CONNECTED_NOWR)
         continue;

      /* check if this connection is interested */
      if (conCb->icmp6Mask & ALL_ICMP_MSG)
         sendflag = TRUE;
      else if (conCb->icmp6Mask & ALL_FLTRD_ICMP_MSG)
      {
         for (idx = 0;  idx < conCb->numFilters;  idx++)
         { 
            if (conCb->icmpError[idx].errType != msgType)
               continue;

#ifndef CM_ICMP_FILTER_SUPPORT
            if (conCb->icmpError[idx].errCodeMask & (1 << msgCode))
#else
            if (conCb->icmpError[idx].errCodeMask == msgCode)
#endif

            {
               sendflag = TRUE;
               break;
            }
         }
      }

      if (sendflag)
      {
         /* add a reference to the message */
         ret = SAddMsgRef(mBuf, conCb->sap->uiPst.region,
                          conCb->sap->uiPst.pool, &tBuf);
         if (ret != ROK)
         {
            alInfo.type = LHI_ALARMINFO_MEM_ID;
            alInfo.inf.mem.region = conCb->sap->uiPst.region;
            alInfo.inf.mem.pool = conCb->sap->uiPst.pool;
            hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                        LHI_CAUSE_SOCK_RECV_ERR, &alInfo);
            continue;
         }

         /* issue the unit data indication */
         HI_UDATIND(conCb, &srcAddr, &destAddr, &hdrParm, lif, tBuf);
      }

      /* If no connections are interested in this, update the
       * filter.
       */
/* hi010.201 : since windows doesn't has icmpv6 filter so the icmpv6 filter 
               feature is supported under the flag ICMPV6_FILTER_SUPPORTED.
					User has to enable the above flag to get the feature */
#ifndef CM_ICMP_FILTER_SUPPORT
#ifdef ICMPV6_FILTER_SUPPORTED
      else
         CM_INET_ICMP6_FILTER_SETBLOCK(msgType, hiCb.icmp6Filter);
#endif /* ICMPV6_FILTER_SUPPORTED */
#endif
   }


   /* release the message */
   HI_FREE_BUF(mBuf);


#ifdef HI_MULTI_THREADED
      HI_UNLOCKICMP(CM_NETADDR_IPV6);
#endif


   RETVOID;
} /* hiRecvIcmp6Msg() */

#endif /* IPV6_SUPPORTED */




/* TLS related functionality.
 */



/* Message I/O.
 */


/*
*
*       Fun:    hiTxMsg
*
*       Desc:   Send the specified message on the specified
*               connection.
*
*       Ret:    ROK             - ok
*               RWOULDBLOCK     - ok, incomplete
*               RFAILED         - failed
*
*       Notes:  None
*
*       File:   hi_bdy3.c
*
*/
#ifdef ANSI
PUBLIC S16 hiTxMsg
(
HiConCb         *conCb,         /* connection block */
Buffer          *mBuf,          /* message to send */
MsgLen          *txLen,         /* filled with bytes transmitted */
Buffer          **qBuf,         /* untransmitted portion */
HiThrMsg        *tMsg           /* filled with terminate message */
)
#else
PUBLIC S16 hiTxMsg(conCb, mBuf, txLen, qBuf, tMsg)
HiConCb         *conCb;         /* connection block */
Buffer          *mBuf;          /* message to send */
MsgLen          *txLen;         /* filled with bytes transmitted */
Buffer          **qBuf;         /* untransmitted portion */
HiThrMsg        *tMsg;          /* filled with terminate message */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiAlarmInfo  alInfo;


   TRC2(hiTxMsg);


   *qBuf = NULLP;
   HI_ZERO(tMsg, sizeof (HiThrMsg));
   /* hi006.105 : Initialized the alarm info with zero */
   HI_ZERO(&alInfo, sizeof (HiAlarmInfo));
   sap = conCb->sap;


#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T Before DatReq/cmInetSendMsg(), in HI");
#endif




   HI_SENDMSG(&conCb->conFd, &conCb->peerAddr, mBuf, txLen, NULLP, ret);


#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T After DatReq/cmInetSendMsg(), in HI");
#endif


   /* if the message was transmitted, we're done! */
   if (ret == ROK)
   {
/*hi014.105  1. Modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
      conCb->numTxBytes += *txLen;
#endif /*LHI_THR_STS */
      HI_ADD_TXSTS(sap, sap->txSts.numTxBytes, *txLen);
      HI_INC_TXSTSMSG(sap, conCb);
      if (sap->trc)
         hiTrcBuf(sap, LHI_TCP_TXED, mBuf);
   }


   /* If the send was partial, we have to queue the untransmitted
    * portion of the message for the group thread to send.
    */
   else if (ret == RWOULDBLOCK)
   {
      /* If there was any transmitted portion, we update
       * statistics to record it, trace it and then remove it.
       */
      if (*txLen)
      {
/*hi014.105  1. Modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
         conCb->numTxBytes += *txLen;
#endif /*LHI_THR_STS */
         HI_ADD_TXSTS(sap, sap->txSts.numTxBytes, *txLen);
         HI_INC_TXSTSMSG(sap, conCb);

         if (sap->trc)
            hiTrcBuf(sap, LHI_TCP_TXED, mBuf);

         SRemPreMsgMult(NULLP, *txLen, mBuf);
      }
      /* hi006.105: Corrected the issue of returning of NULL buffer pointer
                    when none of the data is transmitted */
      *qBuf = mBuf; 
      mBuf = NULLP;
   }


   /* Here, the message send has failed. We send an alarm and
    * prepare the terminate connection message for the caller.
    */
   else
   {
      tMsg->type = HI_THR_DELCON_DISCIND;
      tMsg->spId = sap->spId;
      tMsg->spConId = conCb->spConId;
      switch (ret)
      {
         case RFAILED:
            HI_INC_ERRSTS(hiCb.errSts.sockTxErr);
            hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_INET_ERR,
                        LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
            tMsg->disc.reason = HI_SOCK_SEND_ERR;
            break;

         case RCLOSED:
            tMsg->disc.reason = HI_CON_CLOSED_BY_PEER;
            break;

         case ROUTRES:
            HI_INC_ERRSTS(hiCb.errSts.sockTxErr);
            alInfo.type = LHI_ALARMINFO_MEM_ID;
            alInfo.inf.mem.region = hiCb.init.region;
            alInfo.inf.mem.pool = hiCb.init.pool;
            hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                        LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
            tMsg->disc.reason = HI_OUTOF_RES;
            break;

         default:
            hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_DATREQ,
                        LCM_CAUSE_UNKNOWN, &alInfo);
            tMsg->disc.reason = HI_INTERNAL_ERR;
            break;
      }
   }


   /* release the message buffer */
   if (mBuf)
      HI_FREE_BUF(mBuf);


   RETVALUE(ret);
} /* hiTxMsg() */


/*
*
*       Fun:    hiSendTxQ
*
*       Desc:   Send all the messages in a connection's transmit
*               queue.
*
*       Ret:    ROK             - ok
*               RWOULDBLOCK     - ok, incomplete
*               RFAILED         - failed
*
*       Notes:  None
*
*       File:   hi_bdy3.c
*
*/
#ifdef ANSI
PRIVATE S16 hiSendTxQ
(
HiConCb         *conCb          /* connection to process */
)
#else
PRIVATE S16 hiSendTxQ(conCb)
HiConCb         *conCb;         /* connection to process */
#endif
{
   S16          ret;
   HiSap        *sap;
   QLen         qLen;
   Buffer       *mBuf, *qBuf;
   MsgLen       txLen;
   HiThrMsg     tMsg;
   HiAlarmInfo  alInfo;


   TRC2(hiSendTxQ);


   /* initialize locals */
   sap = conCb->sap;
   alInfo.spId = sap->spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


#ifdef HI_MULTI_THREADED
   HI_LOCK(&conCb->txQLock);
#endif


   /* hi018.201 : qLen is initialized to zero */
   qLen = 0;
   /* get the transmit queue length */
   ret = SFndLenQueue(&conCb->txQ, &qLen);


   /* iterate through the transmit queue */
   while (qLen)
   {
      /* get the first queued message */
      SDequeueFirst(&mBuf, &conCb->txQ);
      qLen--;


      /* transmit it */
      ret = hiTxMsg(conCb, mBuf, &txLen, &qBuf, &tMsg);


      /* if something got sent, check flow control */
      if (txLen)
      {
         hiChkFlc(conCb, 0, txLen);
         conCb->txQSize -= txLen;
      }


      /* if there was a failure, stop */
      if (ret != ROK)
      {
         /* if partial send, queue up the untransmitted part */
         if (ret == RWOULDBLOCK)
            SQueueFirst(qBuf, &conCb->txQ);

         break;
      }
   }


#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&conCb->txQLock);
#endif


   RETVALUE(ret);
} /* hiSendTxQ() */


/*
*
*       Fun:    hiAcceptTcpCon
*
*       Desc:   Accept a new connection from a TCP client.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy3.c
*
*/
#ifdef ANSI
PRIVATE S16 hiAcceptTcpCon
(
HiConCb         *conCb,         /* server connection */
HiConCb         **newCon        /* filled with new connection */
)
#else
PRIVATE S16 hiAcceptTcpCon(conCb, newCon)
HiConCb         *conCb;         /* server connection */
HiConCb         **newCon;       /* filled with new connection */
#endif
{
   S16          ret;
   U8           type;
   HiSap        *sap;
   HiConCb      *newConCb;
   CmInetFd     fd;
   CmTptAddr    peerAddr;
   HiAlarmInfo  alInfo;


   TRC2(hiAcceptTcpCon);
   

   /* initialize locals */
   sap = conCb->sap; 
   alInfo.spId = sap->spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;

   
   /* accept the connection on this socket */
   ret = HI_ACCEPT(&conCb->conFd, &peerAddr, &fd);

   /* if the connection didn't complete, come back later */
   if (ret == ROKDNA)
      RETVALUE(ROKDNA);

   /* error accepting new connection, issue an alarm */
   else if (ret != ROK)
   {
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_INET_ERR,
                  LHI_CAUSE_SOCK_ACPT_ERR, &alInfo);
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "hiAcceptTcpCon(): failed to accept connection\n"));
      HI_CLOSE_SOCKET(&fd);
      RETVALUE(RFAILED);
   }


   /* allocate and initialize a new conCb for this connection */
   ret = hiAllocConCb(sap, conCb->suConId, conCb->srvcType,
                      &type, &newConCb);
   if (ret != ROK)
   {  
      HI_CLOSE_SOCKET(&fd);
      RETVALUE(RFAILED);
   }

   newConCb->flag = conCb->flag;
   newConCb->state = HI_ST_AW_CON_RSP;

   /* suConId is obtained in connect response */

#ifndef IPV6_SUPPORTED
   /* If IPV6_SUPPORTED is defined, then the peer address type is
    * filled in cmInetAccept(). For IPv4, we have to fill it.
    */
   peerAddr.type = CM_TPTADDR_IPV4;
#endif

   cmMemcpy((U8 *)&newConCb->peerAddr, (U8 *)&peerAddr,
            sizeof (CmTptAddr));
   cmMemcpy((U8 *)&newConCb->conFd, (U8 *)&fd, sizeof (CmInetFd));


   
   /* hi002.105(hi023.105) - Set The TOS for the new socket */

   if((conCb->flag & HI_FL_TCP)&& (conCb->ipTos != 0xFF))
      {
              U32 optVal = conCb->ipTos;

              ret = cmInetSetOpt(&fd,CM_INET_LEVEL_IP, CM_INET_OPT_TOS, (Void*)&optVal);
              if ( ret != ROK )
              {  
                      /* close the new socket */
                      HI_CLOSE_SOCKET(&fd);

                      /* deallocate the connection block */
                      HI_FREE(sizeof(HiConCb), newConCb);

                      /* fill up the alarm information */
                      hiSendAlarm(LCM_CATEGORY_INTERNAL,LCM_EVENT_INV_EVT,
                      LHI_CAUSE_SOCK_ACPT_ERR, &alInfo);
                      RETVALUE(RFAILED);
              }
      }


   /* complete the connection control block */
   ret = hiCompleteConCb(newConCb);
   if (ret != ROK)
   {
      HI_CLOSE_SOCKET(&fd);
      HI_FREECONCB(newConCb);
      RETVALUE(RFAILED);
   }


   /* return new connection control block */
   *newCon = newConCb;


   RETVALUE(ROK);
} /* hiAcceptTcpCon() */


/*
*
*       Fun:    hiAcceptCon
*
*       Desc:   Accept a new connection.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy3.c
*
*/
#ifdef ANSI
PRIVATE S16 hiAcceptCon
(
HiConCb         *conCb,         /* connection to accept */
HiThrMsg        *tMsg           /* filled in case of error */
)
#else
PRIVATE S16 hiAcceptCon(conCb, tMsg)
HiConCb         *conCb;         /* connection to accept */
HiThrMsg        *tMsg;          /* filled in case of error */
#endif
{
   S16          ret;
   U8           maxCons;
   HiConCb      *newConCb;
   HiAlarmInfo  alInfo;

   TRC2(hiAcceptCon);


   /* initialize alarm information */
   alInfo.spId = conCb->sap->spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;



   /* accept configured number of TCP connections */
   ret = ROK;
   maxCons = hiCb.cfg.numClToAccept;
   while (maxCons)
   {
      maxCons--;

      ret = hiAcceptTcpCon(conCb, &newConCb);
      if (ret != ROK)
         RETVALUE(ret);



      /* assign the new connection to an fd group */
      ret = hiAssignConCb(newConCb, HI_THR_ADDCON);
      if (ret != ROK)
      {
         /* issue an alarm and discard this connection */
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,
                     LHI_CAUSE_INTPRIM_ERR, &alInfo);
         HI_FREECONCB(newConCb);
         break;
      }

      /* connection is ready */
      HI_INC_TXSTS(conCb->sap, conCb->sap->txSts.numCons);

      /* issue a connect indication if ready */
      if (newConCb->state == HI_ST_AW_CON_RSP)
         HI_CONIND(newConCb);
   }


   RETVALUE(ret);
} /* end of hiAcceptCon() */



/*
*
*       Fun:    hiRecvMsg
*
*       Desc:   Receive a message on a ready fd.
*            
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy3.c
*
*/
#ifdef ANSI
PRIVATE S16 hiRecvMsg
(
HiConCb         *conCb,         /* connection control block */
HiThrMsg        *tMsg           /* filled with disconnect reason */
)
#else
PRIVATE S16 hiRecvMsg(conCb, tMsg)
HiConCb         *conCb;         /* connection control block */
HiThrMsg        *tMsg;          /* filled with disconnect reason */
#endif
{
   S16          ret;
   U8           usrSrvc;
   U8           numMsg;
   HiSap        *sap;
   HiFdGrp      *fdGrp;
   HiAlarmInfo  alInfo;
   Buffer       *mBuf;
   MsgLen       mLen;
   CmTptAddr    srcAddr, destAddr;
   CmIpHdrParm  hdrParm;
   HiLocalInf   *lif;

#ifdef LOCAL_INTF
   HiLocalInf   locIf;

   lif = &locIf;
   HI_ZERO(lif, sizeof (CmTptLocalInf));

#else

   lif = NULLP;

#endif


   TRC2(hiRecvMsg);



   /* initialize locals */
   HI_ZERO(&hdrParm, sizeof (CmIpHdrParm));
   sap = conCb->sap;
   fdGrp = hiCb.fdGrps[conCb->fdGrpNum];
   usrSrvc = conCb->srvcType & 0xf0;


   /* how many messages to read at once? */
#ifdef TUCL_TTI_RCV
   numMsg = 8;
#else
   numMsg = 1;
#endif
   if (conCb->priority)
   {
      if (conCb->srvcType == HI_SRVC_RAW_SCTP)
         numMsg = hiCb.cfg.numRawMsgsToRead;
      else
         numMsg = hiCb.cfg.numUdpMsgsToRead;
   }


   /* read the chosen number of messages */
   ret = ROK;
   while (ret != ROKDNA  &&  numMsg)
   {
      numMsg--;

      mLen = CM_INET_READ_ANY;

#ifdef H323_PERF
      TAKE_TIMESTAMP("Before hiRecvMsg()/cmInetRecvMsg(), in HI");
#endif



      /* hi016.201 : Typecasting lif  with CmInetLocalInf */
      /* receive a message */
      HI_RECVMSG(&conCb->conFd, &srcAddr, &mBuf, &mLen,
                 ((conCb->locTptAddr.type == CM_TPTADDR_IPV6
                  &&  conCb->conFd.type != CM_INET_STREAM)
                 ? &hdrParm : NULLP),
                 (CmInetLocalInf *)lif, ret);


#ifdef H323_PERF
      TAKE_TIMESTAMP("L/T After hiRecvMsg()/cmInetRecvMsg(), in HI");
#endif


      /* check for errors on receive */
      if (ret != ROK)
      {
         /* connection closed by peer; this is not an error */
         if (ret == RCLOSED)
         {
            tMsg->type = HI_THR_DELCON_DISCIND;
            tMsg->spId = sap->spId;
            tMsg->spConId = conCb->spConId;
            tMsg->disc.reason = HI_CON_CLOSED_BY_PEER;
            RETVALUE(RCLOSED);
         }

         /* no data; this is not an error */
         else if (ret == ROKDNA)
            RETVALUE(ROKDNA); 

         /* out of resources! send an alarm */
         else if (ret == ROUTRES)
         {
            HI_INC_ERRSTS(hiCb.errSts.sockRxErr);
            alInfo.spId = sap->spId;
            alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
            hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                        LHI_CAUSE_SOCK_RECV_ERR, &alInfo);
            RETVALUE(ROKDNA);
         }

         /* all others */
         else
         {
            HI_INC_ERRSTS(hiCb.errSts.sockRxErr);
            tMsg->type = HI_THR_DELCON_DISCIND;
            tMsg->spId = sap->spId;
            tMsg->spConId = conCb->spConId;
            tMsg->disc.reason = HI_SOCK_RECV_ERR;
            alInfo.spId = sap->spId;
            alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
            hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_INET_ERR,
                        LHI_CAUSE_SOCK_RECV_ERR, &alInfo);
            RETVALUE(RFAILED);
         }
      }


      /* update statistics */
      fdGrp->genRxSts.numRxBytes += mLen;
      fdGrp->rxSts[sap->spId].numRxBytes += mLen;
      HI_INC_RXSTSMSG(fdGrp, conCb);
/*hi014.105  1. Modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
      conCb->numRxBytes += mLen;
#endif /*LHI_THR_STS */


#ifndef IPV6_SUPPORTED 
      /* set source address type for non-IPv6 */
      srcAddr.type = CM_TPTADDR_IPV4;
#endif



      /* store source address as peer address */
      cmMemcpy((U8 *)&conCb->peerAddr, (U8 *)&srcAddr,
               sizeof (CmTptAddr));


      /* Perform connection service type specific handling. Handle
       * raw connections.
       */
      if (conCb->flag & HI_FL_RAW)
      {
         /* trace the data received */
         if (sap->trc && mBuf != NULLP)
            hiTrcBuf(sap, LHI_RAW_RXED, mBuf);


#ifdef IPV6_SUPPORTED
         if (conCb->flag & HI_FL_RAW_IPV6)
            hiHndlIpv6RawMsg(conCb, mBuf, mLen, &hdrParm, lif);
         else /* execute statement below */
#endif
         if (mBuf != NULLP)
         hiHndlRawMsg(conCb, mBuf, mLen, lif); 
      }


      /* handle UDP connections */
      else if (conCb->flag & HI_FL_UDP)
      {
         /* trace the data received */
         if (sap->trc && mBuf != NULLP)
            hiTrcBuf(sap, LHI_UDP_RXED, mBuf);

#ifdef H323_PERF
         TAKE_TIMESTAMP("L/T UDatInd Rcvd HI->HC, in HI");
#endif

         /* If we have to process the packet, do so, otherwise
          * issue the unit data indication.
          */
         destAddr.type = CM_TPTADDR_NOTPRSNT;
         if ((usrSrvc  ||  conCb->srvcType == HI_SRVC_UDP_TPKT_HDR) && mBuf !=NULLP)
            hiHndlUdpData(conCb, mBuf, mLen, &srcAddr, &destAddr,
                          &hdrParm, lif);
         else
            HI_UDATIND(conCb, &srcAddr, &destAddr, &hdrParm,
                       lif, mBuf);
      }


      /* handle TCP */
      else
      {
         /* trace the data received */
         if (sap->trc && mBuf != NULLP)
            hiTrcBuf(sap, LHI_TCP_RXED, mBuf);

         /* an in-progress connection is now connected */
         if (conCb->state == HI_ST_CLT_CONNECTING)
         {
            conCb->state = HI_ST_CONNECTED;

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#endif /*HITV2*/
               /* issue a connect confirm */
               HI_CONCFM(conCb);
/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#endif /*HITV2*/
         }

         /* If we have to process the packet, do so, otherwise
          * issue the data indication.
          */
         if ((usrSrvc  ||  conCb->srvcType == HI_SRVC_TCP_TPKT_HDR) && (mBuf != NULLP))
         {
            ret = hiHndlTcpData(conCb, mBuf, mLen);
            if (ret != ROK)
               RETVALUE(ret);
         }
         else
         {
            if (mLen > 0)
            {
               HI_DATIND (conCb, mBuf);
            }
         }
      }
   }


   RETVALUE(ROK);
} /* hiRecvMsg() */


/*
*
*       Fun:    hiProcTx
*
*       Desc:   Process a connection whose fd is ready for
*               transmission.
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE Void hiProcTx
(
HiFdGrp         *fdGrp,         /* fd group */
HiConCb         *conCb,         /* connection to process */
CmInetFdSet     *selRdFdSet,    /* read set returned from select() */
S16             *setFds         /* total number of fds set */
)
#else
PRIVATE Void hiProcTx(fdGrp, conCb, selRdFdSet, setFds)
HiFdGrp         *fdGrp;         /* fd group */
HiConCb         *conCb;         /* connection to process */
CmInetFdSet     *selRdFdSet;    /* read set returned from select() */
S16             *setFds;        /* total number of fds set */
#endif
{
   S16          ret;
   HiThrMsg     tMsg;


   TRC2(hiProcTx);


#ifdef HI_MULTI_THREADED
   HI_LOCK(&conCb->lock);
#endif


   /* check if a connection was pending */
   ret = ROK;
   if (conCb->state == HI_ST_CLT_CONNECTING)
   {
      /* get the local transport address */
      HI_GET_SOCKNAME(&conCb->conFd, &conCb->locTptAddr);

      /* check if this fd is also set for reading */
      if (CM_INET_FD_ISSET(&conCb->conFd, selRdFdSet))
      {
         (*setFds)--;
         CM_INET_FD_CLR(&conCb->conFd, selRdFdSet);

         /* There are two possibilities:
          * 1. The connection has completed and data has arrived.
          *    In this case, a connect confirm is issued and then
          *    a data indication.
          * 2. There was an error connecting. In this case, a
          *    disconnect indication is issued.
          */
         ret = hiRecvMsg(conCb, &tMsg);
         if (ret != ROK  &&  ret != ROKDNA)
            goto hiProcTxDone;

      }


      /* fd is set for write only */
      else
      {

         /* the connection is completed */
         conCb->state = HI_ST_CONNECTED;

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#endif /*HITV2*/

            /* issue a connect confirm */
            HI_CONCFM(conCb);

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
/* hi024.201 :  Added 'ifdef HI_TLS' as opening brace of 'elseif' is under this flag */
#endif /*HITV2*/

      }
   }


   /* connection was not in process so there might be data to transmit */
   else if (conCb->state == HI_ST_CONNECTED
            ||  conCb->state == HI_ST_CONNECTED_NORD)
   {
      ret = hiSendTxQ(conCb);
      if (ret != ROK  &&  ret != RWOULDBLOCK)
      {
         /* There was an error so we close this connection. Remove it
          * from the read fd set if it was there.
          */
         if (CM_INET_FD_ISSET(&conCb->conFd, selRdFdSet))
         {
            (*setFds)--;
            CM_INET_FD_CLR(&conCb->conFd, selRdFdSet);
         }

         tMsg.type = HI_THR_DELCON_DISCIND;
         tMsg.spId = conCb->sap->spId;
         tMsg.spConId = conCb->spConId;
         tMsg.disc.reason = HI_SOCK_RECV_ERR;
      }
   }


   /* If we're done with transmits on this connection we remove it
    * from the write fd hash list and set.
    */
   if (ret != RWOULDBLOCK)
   {
      cmHashListDelete(&fdGrp->wrFdHlCp, (PTR)conCb);
      CM_INET_FD_CLR(&conCb->conFd, &fdGrp->writeFdSet);
      /* hi006.105 : Decreamented the numWrFds in fdGrp after deleting from
                     write hash list */
      if (fdGrp->numWrFds)
      {
         fdGrp->numWrFds--;
      }
   }


hiProcTxDone:

#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&conCb->lock);
#endif


   /* on error, close this connection */
   if (ret != ROK  &&  ret != ROKDNA  &&  ret != RWOULDBLOCK)
      hiProcThrDelCon(fdGrp, &tMsg, NULLP, NULLP, NULLP);


   RETVOID;
} /* hiProcTx() */


/*
*
*       Fun:    hiProcRx
*
*       Desc:   Process a connection whose fd is ready for
*               reception.
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE Void hiProcRx
(
HiFdGrp         *fdGrp,         /* fd group */
HiConCb         *conCb          /* connection to process */
)
#else
PRIVATE Void hiProcRx(fdGrp, conCb)
HiFdGrp         *fdGrp;         /* fd group */
HiConCb         *conCb;         /* connection to process */
#endif
{
   S16          ret;
   HiThrMsg     tMsg;
   /* hi031.201: Added new local variables */
#ifndef HI_NO_CHK_RES
   Bool         timerRun = FALSE;
   U8           numTmr;
#endif
   /* hi017.105 svp  1. Flushing data from receive buffer in case of Drop congestion
      if CM_INET_FLUSH_RECV_BUF enabled */
#ifdef CM_INET_FLUSH_RECV_BUF
   MsgLen          len;           /* number of octects to be flushed */
#endif /*CM_INET_FLUSH_RECV_BUF*/


   TRC2(hiProcRx);


   /* initialize locals */
   ret = ROK;
   tMsg.type = 0;


#ifdef HI_MULTI_THREADED
   HI_LOCK(&conCb->lock);
#endif

      /* if this is a listening server, accept the new connection */
      if (conCb->state == HI_ST_SRV_LISTEN)
      {
         /* handle this only if the SAP is not under resource congestion */
         if (!conCb->sap->resCongStrt)
            ret = hiAcceptCon(conCb, &tMsg);
      }
      /* process only connected fds */
      else if (conCb->state == HI_ST_CONNECTED
            ||  conCb->state == HI_ST_CONNECTED_NOWR)
      {
#ifndef HI_NO_CHK_RES
            /* only deal with this if we don't have resource congestion */
            /* hi031.201: Do not call hiChkRes, if timer already running and 
             * resource congestion is in Yellow Zone. Flushing data from receive
             * buffer in case of Drop congestion if CM_INET_FLUSH_RECV_BUF enabled*/
            if (conCb->sap->resCongStrt == TRUE)
            {
               for(numTmr = 0; numTmr < HICONGTMRS ; numTmr++)
               {
                  if(conCb->sap->congTimers[numTmr].tmrEvnt == HI_TMR_CONG)
                  {
                     timerRun = TRUE;
                  }
               }
               if (timerRun && (conCb->sap->resCongDrop != TRUE))
               {
                  ret = hiRecvMsg(conCb, &tMsg);
               }
               else
               {
#ifdef CM_INET_FLUSH_RECV_BUF
                  if((conCb->srvcType == HI_SRVC_UDP) ||
                        (conCb->srvcType == HI_SRVC_UDP_PRIOR) ||
                        (conCb->srvcType == HI_SRVC_UDP_TPKT_HDR) ||
                        (conCb->srvcType == HI_SRVC_RAW_SCTP) ||
                        (conCb->srvcType == HI_SRVC_RAW_SCTP_PRIOR))
                  {
                     len = CM_INET_READ_THROW;
                     ret = cmInetFlushRecvBuf(&conCb->conFd, &len, CM_INET_NO_FLAG);
                  }
#endif /*CM_INET_FLUSH_RECV_BUF */
               }
            }
            else if (hiChkRes(conCb->sap) == ROK)
            {
               ret = hiRecvMsg(conCb, &tMsg);
            }
            else
            {
               /* hi017.105 svp  1. Flushing data from receive buffer in case of Drop congestion
                  if CM_INET_FLUSH_RECV_BUF enabled */
               /* Flush the data present in the receive buffer in kernel when the congestion */
#ifdef CM_INET_FLUSH_RECV_BUF
               if((conCb->srvcType == HI_SRVC_UDP) ||
                     (conCb->srvcType == HI_SRVC_UDP_PRIOR) ||
                     (conCb->srvcType == HI_SRVC_UDP_TPKT_HDR) ||
                     (conCb->srvcType == HI_SRVC_RAW_SCTP) ||
                     (conCb->srvcType == HI_SRVC_RAW_SCTP_PRIOR))
               {
                  len = CM_INET_READ_THROW;
                  ret = cmInetFlushRecvBuf(&conCb->conFd, &len, CM_INET_NO_FLAG);
               }
#endif /*CM_INET_FLUSH_RECV_BUF */
            }
#else
            ret = hiRecvMsg(conCb, &tMsg);
#endif /* HI_NO_CHK_RES */
      }

#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&conCb->lock);
#endif


   /* on error, close this connection */
   if (ret != ROK  &&  ret != ROKDNA  &&  tMsg.type)
      hiProcThrDelCon(fdGrp, &tMsg, NULLP, NULLP, NULLP);


   RETVOID;
} /* hiProcRx() */




/* hi032.201: Modified function to support filteration of ICMP messages 
 * as per user request and protected this changes under CM_ICMP_FILTER_SUPPORT flag */

/*
*
*       Fun:    hiProcFds
*
*       Desc:   Called for an fd group when select() indicates
*               that some fds are set. Handles messages to the
*               group and I/O for the group's fds.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE S16 hiProcFds
(
HiFdGrp         *fdGrp,         /* fd group */
CmInetFdSet     *selRdFdSet,    /* read set returned from select() */
CmInetFdSet     *selWrFdSet,    /* write set returned from select() */
S16             setFds          /* total number of fds set */
)
#else
PRIVATE S16 hiProcFds(fdGrp, selRdFdSet, selWrFdSet, setFds)
HiFdGrp         *fdGrp;         /* fd group */
CmInetFdSet     *selRdFdSet;    /* read set returned from select() */
CmInetFdSet     *selWrFdSet;    /* write set returned from select() */
S16             setFds;         /* total number of fds set */
#endif
{
   S16          ret;
   CmInetFdType fd;
   HiConCb      *conCb;
#ifdef CM_ICMP_FILTER_SUPPORT
   U16           idx;
   HiConCb      *prevConCb;
#endif



   TRC2(hiProcFds);

   
   /* process messages to the fd group */
   if (CM_INET_FD_ISSET(&fdGrp->servFd, selRdFdSet))
   {
      setFds--;
      CM_INET_FD_CLR(&fdGrp->servFd, selRdFdSet);
      ret = hiProcThrMsg(fdGrp, selRdFdSet, selWrFdSet, &setFds);
      if (ret == RCLOSED)
         RETVALUE(RCLOSED);
   }


#ifndef CM_ICMP_FILTER_SUPPORT
   /* handle ICMP first */
   if (fdGrp->procIcmp
       &&  CM_INET_FD_ISSET(&hiCb.icmpConFd, selRdFdSet))
   {
      setFds--;
      CM_INET_FD_CLR(&hiCb.icmpConFd, selRdFdSet);
      hiRecvIcmpMsg();
   }
#else
   for (idx = 0; idx < CM_MAX_ICMP_SOCKET; idx++)
   {
      if(hiCb.icmpInfo[idx].usedFlag == TRUE)
      {
         if (hiCb.icmpInfo[idx].procIcmp && CM_INET_FD_ISSET(&hiCb.icmpInfo[idx].icmpConFd, selRdFdSet))
         {
            conCb = prevConCb = NULLP;
            while ((ret = cmHashListGetNext(&hiCb.icmpInfo[idx].conCbHlCp, (PTR)prevConCb,
                        (PTR *)&conCb)) == ROK)
            {

               hiRecvIcmpMsg(conCb);
               prevConCb = conCb;
            }
            setFds--;
            CM_INET_FD_CLR(&hiCb.icmpInfo[idx].icmpConFd, selRdFdSet);
            break;
         }
         else
            continue;
      }
   }
#endif /* CM_ICMP_FILTER_SUPPORT */



#ifdef IPV6_SUPPORTED
#ifndef CM_ICMP_FILTER_SUPPORT
   /* handle ICMPv6 */
   if (fdGrp->procIcmp6
       &&  CM_INET_FD_ISSET(&hiCb.icmp6ConFd, selRdFdSet))
   {
      setFds--;
      CM_INET_FD_CLR(&hiCb.icmp6ConFd, selRdFdSet);
      hiRecvIcmp6Msg();
   }

#else
   for (idx = 0; idx < CM_MAX_ICMP_SOCKET; idx++)
   {
      if(hiCb.icmpInfo[idx].usedFlag == TRUE)
      {
         if (hiCb.icmpInfo[idx].procIcmp6 && CM_INET_FD_ISSET(&hiCb.icmpInfo[idx].icmp6ConFd, selRdFdSet))
         {
            conCb = prevConCb = NULLP;
            while ((ret = cmHashListGetNext(&hiCb.icmpInfo[idx].conCbHlCp, (PTR)prevConCb,
                        (PTR *)&conCb)) == ROK)
            {

               hiRecvIcmp6Msg(conCb);
               prevConCb = conCb;
            }
            setFds--;
            CM_INET_FD_CLR(&hiCb.icmpInfo[idx].icmp6ConFd, selRdFdSet);
            break;
         }
         else
            continue;
      }
   }
#endif /* CM_ICMP_FILTER_SUPPORT */
#endif


   /* handle the fds ready for writing */
   if (fdGrp->numWrFds)
   {
      CM_INET_FDSETINFO_RESET((&fdGrp->fdSetInfo));
      while (setFds)
      {
         /* get the next fd that is set in the write fd set */
         HI_ZERO(&fd, sizeof(CmInetFdType));
         ret = cmInetGetFd(&fdGrp->fdSetInfo, selWrFdSet, &fd);
         if (ret != ROK)
            break;

         /* look for the connection in the write hash list */
         ret = cmHashListFind(&fdGrp->wrFdHlCp, (U8 *)&fd,
                              sizeof (CmInetFdType), 0, (PTR *)&conCb);
         if (ret != ROK)
         {
            HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
               "hiProcFds(): could not find fd in hash list\n"));
            continue;
         }

         /* process this connection */
         setFds--;
         hiProcTx(fdGrp, conCb, selRdFdSet, &setFds);
      }
   }


   /* handle the fds ready for reading */
   CM_INET_FDSETINFO_RESET((&fdGrp->fdSetInfo));
   while (setFds)
   {
      /* get the next fd that is set in the read fd set */
      HI_ZERO(&fd, sizeof(CmInetFdType));
      ret = cmInetGetFd(&fdGrp->fdSetInfo, selRdFdSet, &fd);
      if (ret == ROKDNA)
         break;
      else if (ret != ROK)
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "hiProcFds(): could not get next set fd\n"));
         break;
      }

      /* look for the connection in the read hash list */
      ret = cmHashListFind(&fdGrp->rdFdHlCp, (U8 *)&fd,
                           sizeof (CmInetFdType), 0, (PTR *)&conCb);
      if (ret != ROK)
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "hiProcFds(): could not find fd in hash list\n"));
         continue;
      }

      setFds--;
      hiProcRx(fdGrp, conCb);
   }


   RETVALUE(ROK);
} /* hiProcFds() */


/*
*
*       Fun:    hiRecvTsk
*
*       Desc:   Handles I/O for the fds in a group. When running
*               multi-threaded, this function does not return
*               until TUCL is shut down; it issues a blocking
*               select() call. In single-threaded mode, this
*               function is invoked periodically; it issues a
*               non-blocking select() on each iteration.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiRecvTsk
(
Pst             *pst,           /* post */
Buffer          *mBuf           /* message buffer */
)
#else
PUBLIC S16 hiRecvTsk(pst, mBuf) 
Pst             *pst;           /* post */
Buffer          *mBuf;          /* message buffer */
#endif
{
   S16          ret, fdGrpNum, setFds;
   Bool         loop;
   HiFdGrp      *fdGrp;
   CmInetFdSet  selRdFdSet, selWrFdSet;
   HiAlarmInfo  alInfo;
#ifndef HI_MULTI_THREADED
   U32          timeout;
#endif


   TRC2(hiRecvTsk);

   /* release the message buffer, if one was provided */
   if (mBuf)
      HI_FREE_BUF(mBuf);


   /* get our fd group */
#ifdef HI_MULTI_THREADED
   fdGrpNum = pst->dstInst - hiCb.init.inst - 1;
#else
   fdGrpNum = 0;
#endif

   fdGrp = hiCb.fdGrps[fdGrpNum];


   /* select() loop */
   loop = TRUE;
   while (loop)
   {
      /* make copies of the read and write fd sets */
      cmMemcpy((U8 *)&selRdFdSet, (U8 *)&fdGrp->readFdSet,
               sizeof (CmInetFdSet));
      if (fdGrp->numWrFds)
         cmMemcpy((U8 *)&selWrFdSet, (U8 *)&fdGrp->writeFdSet,
                  sizeof (CmInetFdSet));


      /* call select() correctly, depending on mode */
#ifdef HI_MULTI_THREADED
      ret = cmInetSelect(&selRdFdSet,
                         (fdGrp->numWrFds ? &selWrFdSet : NULLP),
                         NULLP, &setFds);
#else
      timeout = hiCb.cfg.selTimeout;
      ret = cmInetSelect(&selRdFdSet,
                         (fdGrp->numWrFds ? &selWrFdSet : NULLP),
                         &timeout, &setFds);
      if (ret == RTIMEOUT)
         break;
#endif

      /*hi027.201 : if cmInetSelect() returns ROKDNA then
       * continue from begining the loop*/
      if (ret == ROKDNA)
      {
         continue;
      }
      /* handle select() failure */
      if (ret != ROK)
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "hiRecvTsk: select() failure\n"));
         alInfo.spId = -1;
         alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,
                     LHI_CAUSE_SOCK_SLCT_ERR, &alInfo);
         RETVALUE(RFAILED);
      }


      /* if any fds are set, process them */
      if (setFds)
      {
         ret = hiProcFds(fdGrp, &selRdFdSet, &selWrFdSet, setFds);
         if (ret == RCLOSED)
            break;
      }

#ifndef HI_MULTI_THREADED
      loop = FALSE;
#endif
   }


   RETVALUE(ROK);
} /* hiRecvTsk() */


/********************************************************************30**

         End of file:     tl_bdy3.c@@/main/tenb_5.0_SIB_KNOWNSENSE/5 - Tue Feb  9 11:15:43 2016

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
----------- -------- ---- -----------------------------------------------
1.1          ---      asa  1. initial release.
1.1+         hi002.11 asa  1. changed TCP clients reconnection method.
                          2. added processing for TCP application 
                             specific header.
                          3. miscellaneous bug fixes.
/main/2       ---      cvp  1. changed the hiScanConLst and hiScanPermTsk
                             functions to support multiple file 
                             descriptor sets.
                          2. removed write file descriptor set from 
                             select function parameters.
                          3. added check for ROUTRES return value from 
                             cmInetRecvMsg functions.
                          4. changed the copyright header.
/main/4      ---      sb   1. changes for receiving Raw messages, 
                              distributing Raw ICMP messages.
                          2. changes for packing/unpacking of IP header.
                          3. added backward compatibility flag.
                     cvp  4. changed the hiHndlTcpData function.
                          5. added hiHndlUdpData function.
/main/4+    hi001.13 cvp  1. Check received TPKT header only once. 
                          2. Miscellaneous bug fixes.
/main/4+    hi003.13 cvp  1. Added a UDP priority service type.
                          2. Accept multiple messages for the server.
                          3. Removed call to SAddMsgRef function in 
                             hiHndlTcpData.
/main/4+    hi005.13 cvp  1. Changes for peeking into the file descriptor
                             set.
                          2. Checking for RCLOSED from cmInetConnect. 
                             This error may be returned if the connection 
                             was actively refused or if the server is 
                             dead.
                          3. Added a change to set the timeout value for
                             select depending on the general 
                             configuration option.
                          4. Number of UDP messages to be read is now a 
                             general configuration option.
                          5. Number of RAW messages to be read is now a 
                             general configuration option.
                          6. Number of clients to accept for a TCP server 
                             is now a configuration option.
/main/4      ---      cvp  1. Multi-threaded related changes.
                          2. IPV6 related changes.
                          3. changed the copyright header.
/main/4+    hi001.104 mmh  1. In function hiRecvMsg(): Prevent closing of 
                              socket when cmInetRecvMsg returns ROUTRES.
/main/4+    hi002.104 mmh 1. In function hiPollSockets(): Removing conCb
                             from write hashlist after pending connection is
                             completed.
                          2. In function hiPollSockets(): Using a new macro
                             to clear file descriptors from fd_sets.
/main/4+    hi005.104 mmh 1. Correctly calculated numRxUdpMsg and
                             numRxTcpMsg in each sap in hiRecvMsg function.
                          2. Fix the problem of memory congestion handling.
/main/4+    hi006.104 mmh 1. peerAddr.type = CM_TPTADDR_IPV4 will be assigned
                             only when IPV6_SUPPORTED is not defined.
/main/4+    hi009.104 mmh 1. added new argument localIf in functions - 
                             hiHndlUdpData, hiHndlIpv6RawMsg, HiUiHitUDatInd.
                          2. initialize new structures & vars to all 0's.
                          3. pass 2 new arguments ipHdrParam & localIf
                             in cmInetRecvMsg and ipHdrParm in cmInetSendMsg.
                          4. added new arg CmIpHdrParm in func hiUnpkIpv4Hdr.
                          5. extract IPv4 IP OPTIONS in function hiUnpkIpv4Hdr
                          6. added Rolling Upgrade Support
                              - init all local struc var to all zeros in the
                                function hiAcceptTcpCon and hiRecvMsg
                          7. init structures for binding gen sockets in func
                             hiSockInit() and call cmInetBind under the flag
                             HI_SPECIFY_GENSOCK_ADDR.
/main/4+    hi010.104 bdu 1. Fix the problem of packing Ipv4 header on some 
                             BSD similiar core. On those core, the ip_len 
                             field and ip_off field is in host byte order
                             when passed into kernel.
                          2. Miscellous fix.
/main/4+    hi012.104 bdu 1. Change the ipHdrParm.type from NOTPRSNT to
                             CM_HDRPARM_ICMP6 in hiRecvIcmp6Msg function.
                          2. Miscellous fix.
/main/4+    hi014.104 bdu 1. fix some problem in hiRecvIcmpMsg function.
/main/4+    hi015.104 zmc 1. reset the counter
/main/4+    hi018.104 rs  1. Sending disconnect Indication in case of
                             select call failure.
/main/4+    hi021.104 rs  1. Warnings Removed.
/main/4+    hi022.104 rs  1. Send disconnect indication only for raw socket.
/main/5      ---       kp  1. Updated for release 1.5.
/main/5+    hi001.105 sg  1. Fix compile errors for IPv6.
/main/5+    hi002.105 jc  1. Loading certificate(s) for TLS - made optional
                      ss  2. Removed compiler warnings
                          3. Added check for CM_TPTPARAM_NOTPRSNT
/main/5+    hi004.105 ss  1. Corrected checking of caPath not NULL.
/main/5+    hi005.105 ss  1. Removed invalid checking for SSL_CTX_set_timeout.
/main/5+    hi006.105 ss  1. Resolved the issue of returning of null buffer
                             pointer when none of the data is transmitted in 
                             hiTxMsg. 
                          2. Corrected the return value in hiSendTLS function
                             when SSL_write returns SSL_ERROR_WANT_WRITE or 
                             SSL_ERROR_WANT_READ error.
                          3. Initialized the alarm info with zero.
/main/5+    hi008.105 ss  1. Set fd in correct fd_set according to error 
                             returned by SSL_connect.
                          2. Added functionality to call hiConnectTLS function 
                             from hiProcRx when connection is in progress. 
                          3. Added some more callback for informational 
                             message.
                          4. moved function hiOSSLVerifyCb from hi_bdy3.c 
                             file to hi_ex_pt.c file.
                          5. Intialized the SSL context to NULLP.
                          6. Made TLS method as configurable parameter.
/main/5+    hi010.105 ss  1. Modified for not to send Disconnect Indication
                             in case of hiAcceptTLSCon failure.
                          2. Solved the issue of delay in receiving message 
                             over TLS connection.
                          3. Copy message to fix buffer before sending over
                             TLS connection in windows operating system.

/main/5+    hi011.105 svp  1.Removed Fd from read fd set before giving 
                             connection indication to upper layer. Otherwise
                             it may cause tight loop in TUCL if some data
                             comes before getting connection response from 
                             upper layer

/main/5+    hi013.105 svp  1. Added two new HIT primitives.
                              HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().
/main/5+    hi014.105 svp  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread 
                           2. done perfomance optimization
/main/5+    hi015.105 svp  1. Guarded SGetEntInst() outside SS_MULTIPLE_PROCS
/main/5+    hi017.105 svp  1. Flushing data from receive buffer in case of Drop congestion
                              if CM_INET_FLUSH_RECV_BUF enabled 
/main/6      ---       hs   1. Updated for release of 2.1
/main/7     hi002.201  cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                               Max retransmissions (Init, Path, Association)
/main/7+    hi006.201  hsingh   1. assigning of assocConCb for incoming assoc is removed from NtfyComUp
/main/7+    hi010.201  rss   1. since windows doesn't has icmpv6 filter so the icmpv6 filter 
										  feature is supported under the flag ICMPV6_FILTER_SUPPORTED.
										  User has to enable the above flag to get the feature
/main/7+    hi012.201  rcs  1. Setting max incoming stream .
/main/7+    hi016.201  rcs   1. Typecasting with CmInetLocalInf to 
                                lif in HI_RECVMSG.
/main/7+    hi018.201  rcs   1. Klockwork error fix.
/main/7+    hi019.201  rcs   1. Included protId parameter in status indication.
                             2. Removed the deletion part of ConCb and assocMap when 
                                CantStrAssoc Notification is received. 
                             3. Added SctStaInd in hiSctpSndMsg function.
/main/7+    hi023.201  rcs   1. GCC warning fix for KSCTP. 
                             2. Multiple SCTP ports support on solaris 10 
                                platform under HI_SOL10_MULTIPORT flag.
                             3. Added Trace Indication support for KSCTP.
/main/7+   hi024.201 rshekar 1. ret check changed to RFAILED from -1 after 
                                HI_SCTP_GET_PADDRS.
                             2. If the count is not zero, give status indication to 
                                the user, else if count is zero give TermInd to user
                                and delete the assoc CB in CantStrAssoc handling.
                             3. Added 'ifdef HI_TLS' as opening brace of 'elseif' is 
                                under this flag in hiProcTx function.
/main/7+   hi025.201   rss   1. ccpu00106682 Give term indication if peel of failed.
/main/7+   hi026.201   rss   1. Added Ipv6 support to kernel SCTP 
/main/7+   hi027.201  ragrawal  1. If if cmInetSelect() returns ROKDNA then 
                                   continue from starting the while loop.
/main/7+   hi028.201  ragrawal  1. Removed the validation of assocConCb->state 
                                   and changed the type depending on the status 
                                   in hiSctpTermAssoc().
                                2. Added new local variable and sending alarm 
                                   indication to LM when TUCL receives the 
                                   LKSCTP notification with SCTP_CANT_STR_ASSOC 
                                   in hiProcessSctpNtfyCantStrAssoc().
                                3. Made the peeled off socket as non blocking
                                   in hiProcessSctpNtfyComUp() function and 
                                   protected inside CM_LKSCTP_NONBLOCK flag. 
                                3. Fix for Klockworks issue.
                                4. Removed unused variable cnt in function
                                   hiProcessSctpNtfyComUp().
/main/6+   hi029.201  ragrawal 1. Fix for 64 bit compilation warnings.
/main/6+   hi031.201  ragrawal 1. Added new local variable and also added
                                  code to not call hiChkRes, if timer already 
                                  running and resource congestion is in Yellow
                                  Zone in function hiProcRx().
/main/6+  hi032.201  ragrawal  1. Added support for filteration of ICMP messages 
                                  as per user request and protected this changes 
                                  under CM_ICMP_FILTER_SUPPORT flag.
                               2. Added new header file inclusion.
/main/6+ hi033.201  ragrawal   1. Added new function hiProcessSctpNtfyPeerAddrChange()
                                  and protected under HI_LKSCTP flag.
*********************************************************************91*/

