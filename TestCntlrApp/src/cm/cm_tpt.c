

/********************************************************************20**
  
     Name:     HCT Interface
  
     Type:     C file
  
     Desc:     This file contains the packing/unpacking functions
               for the H.225 primitives on hct interface

     File:     cm_tpt.c

     Sid:      cm_tpt.c@@/main/19 - Thu Mar 12 13:58:05 2009
  
     Prg:      mb
  
*********************************************************************21*/

/* header include files (.h) */

#include "envopt.h"        /* environment options */  
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */

#include "cm_tpt.h"

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system service interface */

/*#include "cm_tkns.x"*/
#include "cm_tpt.x"


/* local defines */

/* local typedefs */

/* local externs */
  
/* forward references */

/* local function definition */

/* functions in other modules */

/* public variable declarations */

/* control variables for testing */

/* private variable declarations */

/*
 * support functions
 */

/*  cm_tpt_c_001.main_17 - Guarded under LCEGT and LCLEG */
/*  cm_tpt_c_001.main_18 - Guarded under LWLCEGT */

#if    (   defined(LCHCT) || defined (LWLCHCT) || defined(LCHIT) \
        || defined(LCLHC) || defined(TRIL_HZ) \
        || defined(LCHRT) || defined(LCLHR)   \
        || defined(LCLMG) || defined(LCMGT)   \
        || defined(LCLHG) || defined(LCHGT)   \
        || defined(LCSCT) || defined(LCLSB)   \
        || defined(LCLNT) || defined(LCLLN)   \
        || defined(LCLSO) || defined(LCSOT)   \
        || defined(LCEGT) || defined(LCLEG)   || defined(LWLCEGT) \
        || defined(CM_COMPRESS)   \
       )

#ifdef __cplusplus
extern "C" {
#endif
   /* Add prototypes here  (MB) */

#ifdef __cplusplus
}
#endif

  

/*
 *      PACKING FUNCTIONS
 */
/* Moving IPv4 address packing functions from cm_inet.c */
/*
*
*       Fun:   cmPkCmIpv4TptAddr
*
*       Desc:  This function packs the IPv4 address 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmIpv4TptAddr
(
CmIpv4TptAddr            *pkParam,  /* IPv4 Address structure */
Buffer                   *mBuf      /* message buffer */
)
#else
PUBLIC S16 cmPkCmIpv4TptAddr (pkParam, mBuf)
CmIpv4TptAddr            *pkParam;  /* IPv4 Address structure */
Buffer                   *mBuf;     /* message buffer */
#endif
{
   TRC2(cmPkCmIpv4TptAddr)

   CMCHKPK(cmPkCmIpv4NetAddr, pkParam->address, mBuf);
   CMCHKPK(SPkU16, pkParam->port, mBuf);

   RETVALUE(ROK);
} /* cmPkCmIpv4TptAddr */

/*
*
*       Fun:   cmPkCmIpv6NetAddr
*
*       Desc:  This function packs the 16 bytes of IPv6 address 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkCmIpv6NetAddr
(
CmIpv6NetAddr            *pkParam,     
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkCmIpv6NetAddr (pkParam, mBuf)
CmIpv6NetAddr            *pkParam;     
Buffer                   *mBuf;        /* message buffer */
#endif
{
   U8 num;
   U8 *ptr = (U8*)pkParam;

   TRC3(cmPkCmIpv6NetAddr)

   for(num = 0; num < CM_IPV6ADDR_SIZE; num++)
   {
      CMCHKPK(SPkU8, *(ptr+num), mBuf);
   }

   RETVALUE(ROK);
} /* end of cmPkCmIpv6NetAddr */


/*
*
*       Fun:   cmPkCmIpv6TptAddr
*
*       Desc:  This function packs the IPv6 transport address
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkCmIpv6TptAddr
(
CmIpv6TptAddr            *pkParam,     /* IPv6 transport address */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkCmIpv6TptAddr (pkParam, mBuf)
CmIpv6TptAddr            *pkParam;     /* IPv6 transport address */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC3(cmPkCmIpv6TptAddr)

   CMCHKPK(cmPkCmIpv6NetAddr, &pkParam->ipv6NetAddr, mBuf);
   CMCHKPK(SPkU16, pkParam->port, mBuf);

   RETVALUE(ROK);
}   /* cmPkCmIpv6TptAddr */


/*
*
*       Fun:   cmPkCmNetAddrTbl
*
*       Desc:  This function packs the 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmNetAddrTbl
(
CmNetAddrTbl            *pkParam,      /* Network Address Table */
Buffer                  *mBuf          /* message buffer */
)
#else
PUBLIC S16 cmPkCmNetAddrTbl (pkParam, mBuf)
CmNetAddrTbl            *pkParam;      /* Network Address Table */
Buffer                  *mBuf;         /* message buffer */
#endif
{
   U16                  idx;           /* Loop Index */
   CmNetAddr            *netAddr;      /* Network Address */

   TRC2(cmPkCmNetAddrTbl)

   if (pkParam->count > CM_MAX_NET_ADDR)
      RETVALUE(RFAILED);

   /* Pack All the addresses */
   for (idx = pkParam->count; idx; idx--)
   {
      netAddr = &(pkParam->netAddr[idx - 1]);

      if ((cmPkCmNetAddr(netAddr, mBuf)) != ROK)
         RETVALUE(RFAILED);
   }

   /* Pack the total number of addresses present in the table */
   CMCHKPK(SPkU16, pkParam->count, mBuf);

   RETVALUE(ROK);

} /* end of cmPkCmNetAddrTbl() */

/*
*
*       Fun:   cmPkCmNetAddr
*
*       Desc:  This function packs the 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmNetAddr
(
CmNetAddr                *pkParam,     
Buffer                   *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmPkCmNetAddr (pkParam, mBuf)
CmNetAddr                *pkParam;     
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC3(cmPkCmNetAddr)

   switch (pkParam->type)
   {
      case CM_NETADDR_NOTPRSNT:
         break;

      case CM_NETADDR_IPV4:
         CMCHKPK(cmPkCmIpv4NetAddr, pkParam->u.ipv4NetAddr, mBuf);
         break;

      case CM_NETADDR_IPV6:
         CMCHKPK(cmPkCmIpv6NetAddr, &pkParam->u.ipv6NetAddr, mBuf);
         break;

      default:
         RETVALUE(RFAILED);
   }
   CMCHKPK(SPkU8, pkParam->type, mBuf);

   RETVALUE(ROK);
}   /* cmPkCmNetAddr */


/*
*
*       Fun:   cmPkCmTptAddr
*
*       Desc:  This function packs the 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmTptAddr
(
CmTptAddr                *pkParam,     
Buffer                   *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmPkCmTptAddr (pkParam, mBuf)
CmTptAddr                *pkParam;     
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC3(cmPkCmTptAddr)

   switch (pkParam->type)
   {
      case CM_TPTADDR_NOTPRSNT:
         break;

      case CM_TPTADDR_IPV4:
         CMCHKPK(cmPkCmIpv4TptAddr, &pkParam->u.ipv4TptAddr, mBuf);
         break;

      case CM_TPTADDR_IPV6:
         CMCHKPK(cmPkCmIpv6TptAddr, &pkParam->u.ipv6TptAddr, mBuf);
         break;
   
      default:
         RETVALUE(RFAILED);
   }
   CMCHKPK(SPkU8, pkParam->type, mBuf);

   RETVALUE(ROK);
}   /* cmPkCmTptAddr */

/* added new packing functions */
#ifdef LOCAL_INTF
/*
*
*       Fun:   cmPkCmTptLocalInf
*
*       Desc:  This function packs the local interface info on which IPV4/IPV6
*              packet was received on.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmTptLocalInf
(
CmTptLocalInf           *pkParam,   /* local interface info */
Buffer                  *mBuf       /* message buffer */
)
#else
PUBLIC S16 cmPkCmTptLocalInf (pkParam, mBuf)
CmTptLocalInf           *pkParam;   /* local interface info */
Buffer                  *mBuf;      /* message buffer */
#endif
{
   TRC3(cmPkCmTptLocalInf)

   if (pkParam->intfPrsnt == TRUE)
   {  
      /* pack the actual interface address */ 
      CMCHKPK(cmPkCmNetAddr, &pkParam->localIfAddr, mBuf); 
      /* pack the interface index value */
      CMCHKPK(SPkU32, pkParam->localIf, mBuf);
   }
   /* pack the boll which indicates if valid local intf is present or not */
   CMCHKPK(SPkU8, pkParam->intfPrsnt, mBuf);
   RETVALUE(ROK);
}   /* cmPkCmTptLocalInf */
#endif /* LOCAL_INTF */

/* Moving IPv6 multicast information packing functions from cm_inet.c */
#ifdef IPV6_SUPPORTED
/*
*
*       Fun:   cmPkCmNetMCastInf6
*
*       Desc:  This function packs the IPv6 multicast information 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmNetMCastInf6
(
CmNetMCastInf6            *pkParam,     /* IPv6 multicast information */
Buffer                    *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmPkCmNetMCastInf6(pkParam, mBuf)
CmNetMCastInf6            *pkParam;     /* IPv6 multicast information */
Buffer                    *mBuf;        /* message buffer */
#endif
{
   TRC3(cmPkCmNetMCastInf6)

   CMCHKPK(cmPkCmIpv6NetAddr, &pkParam->mCastAddr, mBuf);
   CMCHKPK(SPkU32, pkParam->localInf, mBuf);

   RETVALUE(ROK);
}   /* cmPkCmNetMCastInf6 */
#endif /* IPV6_SUPPORTED */


/*
*
*       Fun:   cmPkCmSockOpts
*
*       Desc:  This function packs the 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkCmSockOpts
(
CmSockOpts               *pkParam,     
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkCmSockOpts (pkParam, mBuf)
CmSockOpts               *pkParam;     
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC3(cmPkCmSockOpts)

   switch (pkParam->option)
   {
      case CM_SOCKOPT_OPT_ADD_MCAST_MBR:
      case CM_SOCKOPT_OPT_DRP_MCAST_MBR:
#ifdef CM_INET2
         CMCHKPK(cmPkCmNetAddr, &pkParam->optVal.mCastInfo.mCastAddr, mBuf);
         CMCHKPK(cmPkCmNetAddr, &pkParam->optVal.mCastInfo.localAddr, mBuf);
#else
         CMCHKPK(cmPkCmNetAddr, &pkParam->optVal.mCastAddr, mBuf);
#endif /* CM_INET2 */
         break;

      case CM_SOCKOPT_OPT_MCAST_IF:
         CMCHKPK(cmPkCmNetAddr, &pkParam->optVal.lclAddr, mBuf);
         break;

#ifdef IPV6_SUPPORTED
      case CM_SOCKOPT_OPT_ADD_MCAST6_MBR:
      case CM_SOCKOPT_OPT_DRP_MCAST6_MBR:
         CMCHKPK(cmPkCmNetMCastInf6, &pkParam->optVal.mCastInfo6, mBuf);
         break;

      case CM_SOCKOPT_OPT_MCAST6_IF:
         CMCHKPK(SPkU32, pkParam->optVal.infId, mBuf);
         break;

#endif /* IPV6_SUPPORTED */

      default:
         CMCHKPK(SPkU32, pkParam->optVal.value, mBuf);
         break;
   }
   CMCHKPK(SPkU32, pkParam->option, mBuf);
   CMCHKPK(SPkU32, pkParam->level, mBuf);

   RETVALUE(ROK);
}   /* cmPkCmSockOpts */


/*
*
*       Fun:   cmPkCmSockParam
*
*       Desc:  This function packs the 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkCmSockParam
(
CmSockParam              *pkParam,     
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkCmSockParam (pkParam, mBuf)
CmSockParam              *pkParam;     
Buffer                   *mBuf;        /* message buffer */
#endif
{
   U32 num;

   TRC3(cmPkCmSockParam)

   if( pkParam->numOpts > CM_MAX_SOCK_OPTS)
   {
      RETVALUE(RFAILED);
   }
   for(num = 0; num < pkParam->numOpts; num++)
   {
      CMCHKPK(cmPkCmSockOpts, &pkParam->sockOpts[num], mBuf);
   }
   CMCHKPK(SPkU8, pkParam->numOpts, mBuf);
   CMCHKPK(SPkU8, pkParam->listenQSize, mBuf);

   RETVALUE(ROK);
}   /* cmPkCmSockParam */


#ifdef CM_TLS
/*
*
*       Fun:   cmPkTlsTptParam
*
*       Desc:  This function packs the 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkTlsTptParam
(
TlsTptParam              *pkParam,     /**/
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkTlsTptParam(pkParam, mBuf)
TlsTptParam              *pkParam;     /**/
Buffer                   *mBuf;        /* message buffer */
#endif
{
   U32 num;

   TRC3(cmPkTlsTptParam)

   if( pkParam->numOpts > CM_MAX_SOCK_OPTS)
   {
      RETVALUE(RFAILED);
   }
   for(num = 0; num < pkParam->numOpts; num++)
   {
      CMCHKPK(cmPkCmSockOpts, &pkParam->sockOpts[num], mBuf);
   }
   CMCHKPK(SPkU8, pkParam->numOpts, mBuf);
   CMCHKPK(SPkU8, pkParam->listenQSize, mBuf);
   CMCHKPK(SPkS16, pkParam->ctxId, mBuf);

   RETVALUE(ROK);
}  /* cmPkTlsTptParam */

#endif  /* CM_TLS */


/*
*
*       Fun:   cmPkCmTptParam
*
*       Desc:  This function packs the 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmTptParam
(
CmTptParam               *pkParam,     
Buffer                   *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmPkCmTptParam (pkParam, mBuf)
CmTptParam               *pkParam;     
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC3(cmPkCmTptParam)

   switch (pkParam->type)
   {
      case CM_TPTPARAM_NOTPRSNT:
         break;

      case CM_TPTPARAM_SOCK:
         CMCHKPK(cmPkCmSockParam, &pkParam->u.sockParam, mBuf);
         break;

#ifdef CM_AAL
      case CM_TPTPARAM_AAL:
         CMCHKPK(cmPkAalConParam, &pkParam->u.aalParam, mBuf);
         break;
#endif

#ifdef CM_TLS
      case CM_TPTPARAM_TLS:
         CMCHKPK(cmPkTlsTptParam, &pkParam->u.tlsParam, mBuf);
         break;
#endif

      default:
         RETVALUE(RFAILED);
   }

   CMCHKPK(SPkU8, pkParam->type, mBuf);

   RETVALUE(ROK);
}   /* cmPkCmTptParam */

  
/*
 *      UNPACKING FUNCTIONS
 */

/* Moving IPv4 address un-packing functions from cm_inet.c file */

/*
*
*       Fun:   cmUnpkCmIpv4TptAddr
*
*       Desc:  This function unpacks the IPv4 address
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmIpv4TptAddr 
(
CmIpv4TptAddr            *unpkParam,     /* IPv4 Address */
Buffer                   *mBuf           /* message buffer */
)
#else
PUBLIC S16 cmUnpkCmIpv4TptAddr (unpkParam, mBuf)
CmIpv4TptAddr            *unpkParam;     /* IPv4 Address */
Buffer                   *mBuf;          /* message buffer */
#endif
{
   TRC2(cmUnpkCmIpv4TptAddr)

   CMCHKUNPK(SUnpkU16, &unpkParam->port, mBuf);
   CMCHKUNPK(cmUnpkCmIpv4NetAddr, &unpkParam->address, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkCmIpv4TptAddr */


/*
*
*       Fun:   cmUnpkCmIpv6NetAddr
*
*       Desc:  This function unpacks the 16 bytes of IPv6 address 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkCmIpv6NetAddr
(
CmIpv6NetAddr            *unpkParam,   /* IPv6 address */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkCmIpv6NetAddr (unpkParam, mBuf)
CmIpv6NetAddr            *unpkParam;   /* IPv6 address */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   U32 num;
   U8 *ptr = (U8*)unpkParam;

   TRC3(cmUnpkCmIpv6NetAddr)

   ptr += (CM_INET_IPV6ADDR_SIZE - 1);

   for(num = 0; num < CM_IPV6ADDR_SIZE; num++)
   {
      CMCHKUNPK(SUnpkU8, (ptr-num), mBuf);
   }

   RETVALUE(ROK);
} /* end of cmUnpkCmIpv6NetAddr */


/*
*
*       Fun:   cmUnpkCmIpv6TptAddr
*
*       Desc:  This function unpacks the IPv6 transport address
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkCmIpv6TptAddr
(
CmIpv6TptAddr            *unpkParam,   /* IPv6 transport address */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkCmIpv6TptAddr (unpkParam, mBuf)
CmIpv6TptAddr            *unpkParam;   /* IPv6 transport address */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC3(cmUnpkCmIpv6TptAddr)

   CMCHKUNPK(SUnpkU16, &unpkParam->port, mBuf);
   CMCHKUNPK(cmUnpkCmIpv6NetAddr, &unpkParam->ipv6NetAddr, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkCmIpv6TptAddr */


/*
*
*       Fun:   cmUnpkCmNetAddrTbl
*
*       Desc:  This function unpacks the 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmNetAddrTbl
(
CmNetAddrTbl            *unpkParam,    /* Network Address Table */
Buffer                  *mBuf          /* message buffer */
)
#else
PUBLIC S16 cmUnpkCmNetAddrTbl (unpkParam, mBuf )
CmNetAddrTbl            *unpkParam;    /* Network Address Table */
Buffer                  *mBuf;         /* message buffer */
#endif
{
   U16                  idx;           /* Loop Index */
   CmNetAddr            *netAddr;      /* Network Address */
   
   TRC2(cmUnpkCmNetAddrTbl)

   /* Unpack the count */
   CMCHKUNPK(SUnpkU16, &(unpkParam->count), mBuf);

   /* Unpack the addresses */
   for (idx = 0; idx < unpkParam->count; idx++)
   {
      netAddr = &(unpkParam->netAddr[idx]);

      if ((cmUnpkCmNetAddr(netAddr, mBuf)) != ROK)
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);

} /* end of cmUnpkCmNetAddrTbl() */


/*
*
*       Fun:   cmUnpkCmNetAddr
*
*       Desc:  This function unpacks the network address
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmNetAddr
(
CmNetAddr                *unpkParam,   
Buffer                   *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmUnpkCmNetAddr (unpkParam, mBuf )
CmNetAddr                *unpkParam;   
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC3(cmUnpkCmNetAddr)

   CMCHKUNPK(SUnpkU8, &unpkParam->type, mBuf);

   switch (unpkParam->type)
   {
      case CM_NETADDR_NOTPRSNT:
         break;

      case CM_NETADDR_IPV4:
         CMCHKUNPK(cmUnpkCmIpv4NetAddr, &unpkParam->u.ipv4NetAddr, mBuf);
         break;

      case CM_NETADDR_IPV6:
         CMCHKUNPK(cmUnpkCmIpv6NetAddr, &unpkParam->u.ipv6NetAddr, mBuf);
         break;

      default:
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}   /* cmUnpkCmNetAddr */


/*
*
*       Fun:   cmUnpkCmTptAddr
*
*       Desc:  This function unpacks the 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmTptAddr
(
CmTptAddr                *unpkParam,   
Buffer                   *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmUnpkCmTptAddr (unpkParam, mBuf)
CmTptAddr                *unpkParam;   
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC3(cmUnpkCmTptAddr)

   CMCHKUNPK(SUnpkU8, &unpkParam->type, mBuf);

   switch (unpkParam->type)
   {
      case CM_TPTADDR_NOTPRSNT:
         break;

      case CM_TPTADDR_IPV4:
         CMCHKUNPK(cmUnpkCmIpv4TptAddr, &unpkParam->u.ipv4TptAddr, mBuf);
         break;

      case CM_TPTADDR_IPV6:
         CMCHKUNPK(cmUnpkCmIpv6TptAddr, &unpkParam->u.ipv6TptAddr, mBuf);
         break;

      default:
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}   /* cmUnpkCmTptAddr */

/* Moving IPv6 multicast information unpacking functions from cm_inet.c */
#ifdef IPV6_SUPPORTED

/*
*
*       Fun:   cmUnpkCmNetMCastInf6
*
*       Desc:  This function unpacks the IPv6 multicast information 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmNetMCastInf6
(
CmNetMCastInf6            *unpkParam,   /* IPv6 multicast information */
Buffer                    *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmUnpkCmNetMCastInf6(unpkParam, mBuf)
CmNetMCastInf6            *unpkParam;   /* IPv6 multicast information */
Buffer                    *mBuf;        /* message buffer */
#endif
{
   TRC3(cmUnpkCmNetMCastInf6)

    CMCHKUNPK(SUnpkU32, &unpkParam->localInf, mBuf);
    CMCHKUNPK(cmUnpkCmIpv6NetAddr, &unpkParam->mCastAddr, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkCmNetMCastInf6 */
#endif /* IPV6_SUPPORTED */


/*
*
*       Fun:   cmUnpkCmSockOpts
*
*       Desc:  This function unpacks the socket options
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkCmSockOpts
(
CmSockOpts               *unpkParam,   /* socket options */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkCmSockOpts (unpkParam, mBuf)
CmSockOpts               *unpkParam;   /* socket options */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC3(cmUnpkCmSockOpts)

   CMCHKUNPK(SUnpkU32, &unpkParam->level, mBuf);
   CMCHKUNPK(SUnpkU32, &unpkParam->option, mBuf);

   switch (unpkParam->option)
   {
      case CM_SOCKOPT_OPT_ADD_MCAST_MBR:
      case CM_SOCKOPT_OPT_DRP_MCAST_MBR:
#ifdef CM_INET2
         CMCHKUNPK(cmUnpkCmNetAddr, &unpkParam->optVal.mCastInfo.localAddr, 
                   mBuf);
         CMCHKUNPK(cmUnpkCmNetAddr, &unpkParam->optVal.mCastInfo.mCastAddr, 
                   mBuf);
#else
         CMCHKUNPK(cmUnpkCmNetAddr, &unpkParam->optVal.mCastAddr, mBuf);
#endif /* CM_INET2 */
         break;

      case CM_SOCKOPT_OPT_MCAST_IF:
         CMCHKUNPK(cmUnpkCmNetAddr, &unpkParam->optVal.lclAddr, mBuf);
         break;

#ifdef IPV6_SUPPORTED
      case CM_SOCKOPT_OPT_ADD_MCAST6_MBR:
      case CM_SOCKOPT_OPT_DRP_MCAST6_MBR:
         CMCHKUNPK(cmUnpkCmNetMCastInf6, &unpkParam->optVal.mCastInfo6, mBuf);
         break;

      case CM_SOCKOPT_OPT_MCAST6_IF:
         CMCHKUNPK(SUnpkU32, &unpkParam->optVal.infId, mBuf);
         break;
#endif /* IPV6_SUPPORTED */

      default:
         CMCHKUNPK(SUnpkU32, &unpkParam->optVal.value, mBuf);
         break;
   }

   RETVALUE(ROK);
}   /* cmUnpkCmSockOpts */


/*
*
*       Fun:   cmUnpkCmSockParam
*
*       Desc:  This function unpacks the socket parameters
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkCmSockParam
(
CmSockParam              *unpkParam,   /* socket parameters */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkCmSockParam (unpkParam, mBuf)
CmSockParam              *unpkParam;   /* socket parameters */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   U32 num;

   TRC3(cmUnpkCmSockParam)

   CMCHKUNPK(SUnpkU8, &unpkParam->listenQSize, mBuf);
   CMCHKUNPK(SUnpkU8, &unpkParam->numOpts, mBuf);

   if( unpkParam->numOpts > CM_MAX_SOCK_OPTS)
   {
      RETVALUE(RFAILED);
   }

   for(num = 0; num < unpkParam->numOpts; num++)
   {
      CMCHKUNPK(cmUnpkCmSockOpts, &unpkParam->sockOpts[num], mBuf);
   }

   RETVALUE(ROK);
}   /* cmUnpkCmSockParam */


#ifdef CM_TLS
/*
*
*       Fun:   cmUnpkTlsTptParam
*
*       Desc:  This function unpacks the socket parameters
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkTlsTptParam
(
TlsTptParam              *unpkParam,   /* TLS parameters */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkTlsTptParam (unpkParam, mBuf)
TlsTptParam              *unpkParam;   /* TLS parameters */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   U32 num;

   TRC3(cmUnpkTlsTptParam)

   CMCHKUNPK(SUnpkS16, &unpkParam->ctxId, mBuf);
   CMCHKUNPK(SUnpkU8, &unpkParam->listenQSize, mBuf);
   CMCHKUNPK(SUnpkU8, &unpkParam->numOpts, mBuf);

   if( unpkParam->numOpts > CM_MAX_SOCK_OPTS)
   {
      RETVALUE(RFAILED);
   }

   for(num = 0; num < unpkParam->numOpts; num++)
   {
      CMCHKUNPK(cmUnpkCmSockOpts, &unpkParam->sockOpts[num], mBuf);
   }

   RETVALUE(ROK);
}  /* cmUnpkTlsTptParam */

#endif  /* CM_TLS */


/*
*
*       Fun:   cmUnpkCmTptParam
*
*       Desc:  This function unpacks the transport parameters 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmTptParam
(
CmTptParam               *unpkParam,   /* transport parameters */
Buffer                   *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmUnpkCmTptParam (unpkParam, mBuf)
CmTptParam               *unpkParam;   /* transport parameters */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC3(cmUnpkCmTptParam)

   CMCHKUNPK(SUnpkU8, &unpkParam->type, mBuf);

   switch (unpkParam->type)
   {
      case CM_TPTPARAM_NOTPRSNT:
         break;

      case CM_TPTPARAM_SOCK:
         CMCHKUNPK(cmUnpkCmSockParam, &unpkParam->u.sockParam, mBuf);
         break;

#ifdef CM_AAL
      case CM_TPTPARAM_AAL:
         CMCHKUNPK(cmUnpkAalConParam, &unpkParam->u.aalParam, mBuf);
         break;
#endif

#ifdef CM_TLS
      case CM_TPTPARAM_TLS:
         CMCHKUNPK(cmUnpkTlsTptParam, &unpkParam->u.tlsParam, mBuf);
         break;
#endif

      default:
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}   /* cmUnpkCmTptParam */


#ifdef CM_INET2  

/*
*
*       Fun:   cmPkCmIpHdrParm
*
*       Desc:  This function packs the the IP hedear parameters for both 
*              IPV4 and IPV6. 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmIpHdrParm
(
CmIpHdrParm             *pkParam,   /* IP hdr parameters */ 
Buffer                  *mBuf       /* message buffer */
)
#else
PUBLIC S16 cmPkCmIpHdrParm (pkParam, mBuf)
CmIpHdrParm             *pkParam;   /* IP hdr parameters */
Buffer                  *mBuf;      /* message buffer */
#endif
{
   TRC3(cmPkCmIpHdrParm)

   switch (pkParam->type)
   {
      case CM_HDRPARM_NOTPRSNT:
      case CM_HDRPARM_ICMP6:
         break;

      case CM_HDRPARM_IPV4:

         /* call to pack ipv4 options */
#ifdef IPV4_OPTS_SUPPORTED
         /* ipv4 IP options */
         CMCHKPK(cmPkTknStr64, &pkParam->u.hdrParmIpv4.ipv4HdrOpt, mBuf);
#endif /* IPV4_OPTS_SUPPORTED */
         
         CMCHKPK(cmPkTknU8, &pkParam->u.hdrParmIpv4.ttl, mBuf);
         CMCHKPK(cmPkTknU8, &pkParam->u.hdrParmIpv4.tos, mBuf);
         CMCHKPK(cmPkTknU8, &pkParam->u.hdrParmIpv4.dfBit, mBuf); 
         CMCHKPK(cmPkTknU8, &pkParam->u.hdrParmIpv4.proto, mBuf);
         break;

      case CM_HDRPARM_IPV6:
#ifdef IPV6_SUPPORTED    
         /* call to pack ipv6 extn hdrs */
#ifdef IPV6_OPTS_SUPPORTED 
         /* pack IPV6 extension headers */
         CMCHKPK(cmPkCmIpv6ExtHdr, &pkParam->u.hdrParmIpv6.ipv6ExtHdr, mBuf);
#endif /* IPV6_OPTS_SUPPORTED */
         CMCHKPK(cmPkCmNetAddr, &pkParam->u.hdrParmIpv6.srcAddr6, mBuf); 
         CMCHKPK(cmPkTknU8, &pkParam->u.hdrParmIpv6.ttl, mBuf);          
#endif /* IPV6_SUPPORTED */ 
         break;
   
      default:
         RETVALUE(RFAILED);
   }
   CMCHKPK(SPkU8, pkParam->type, mBuf);

   RETVALUE(ROK);
}   /* End of cmPkCmIpHdrParm */


/* added new unpack function for local interface */
#ifdef LOCAL_INTF
/*
*
*       Fun:   cmUnpkCmTptLocalInf
*
*       Desc:  This function unpacks the local interface info on which 
*              IPV4/IPV6 packet was received on.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmTptLocalInf
(
CmTptLocalInf           *unpkParam, /* local interface info */
Buffer                  *mBuf       /* message buffer */
)
#else
PUBLIC S16 cmUnpkCmTptLocalInf (unpkParam, mBuf)
CmTptLocalInf           *unpkParam; /* local interface info */
Buffer                  *mBuf;      /* message buffer */
#endif
{
   TRC3(cmUnpkCmTptLocalInf)

   /* first unpack the bool intfPrsnt value which is always packed */
   CMCHKUNPK(cmUnpkBool, &unpkParam->intfPrsnt, mBuf);
   
   /* if the above unpacked bool is TRUE then we have to unpack further
    * to get the local intf index and intf address */   
   if (unpkParam->intfPrsnt == TRUE)
   {   
      CMCHKUNPK(SUnpkU32, &unpkParam->localIf, mBuf);
      CMCHKUNPK(cmUnpkCmNetAddr, &unpkParam->localIfAddr, mBuf); 
   }
   RETVALUE(ROK);
}   /* cmUnpkCmTptLocalInf */
#endif /* LOCAL_INTF */


/* added new functions */
#ifdef IPV6_OPTS_SUPPORTED 
/*
*       Fun:   cmPkCmIpv6ExtHdr
*
*       Desc:  This function packs the IPV6 extension headers
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmIpv6ExtHdr
(
CmIpv6ExtHdr             *pkParam,   /* IPV6 extension hdrs */
Buffer                   *mBuf       /* message buffer */
)
#else
PUBLIC S16 cmPkCmIpv6ExtHdr (pkParam, mBuf)
CmIpv6ExtHdr             *pkParam;   /*IPV6 extension hdrs */
Buffer                   *mBuf;      /* message buffer */
#endif
{
   TRC3(cmPkCmIpv6ExtHdr)

   /* pack first Route hdr */   
   if (pkParam->rtOptsPrsnt)
      CMCHKPK(cmPkCmIpv6RtHdr, &pkParam->rtOpts, mBuf);  
   CMCHKPK(cmPkBool, pkParam->rtOptsPrsnt, mBuf);  

   /* pack Dest Opt hdr */
   if (pkParam->destOptsPrsnt)
      CMCHKPK(cmPkCmIpv6DestOptsArr, &pkParam->destOptsArr, mBuf);  
   CMCHKPK(cmPkBool, pkParam->destOptsPrsnt, mBuf);  

   /* pack HBH hdr */
   if (pkParam->hbhHdrPrsnt)
      CMCHKPK(cmPkCmIpv6HBHHdrArr, &pkParam->hbhOptsArr, mBuf);  
   CMCHKPK(cmPkBool, pkParam->hbhHdrPrsnt, mBuf);  

   RETVALUE(ROK);
} /* end of cmPkCmIpv6ExtHdr */


/*
*
*       Fun:   cmPkCmIpv6RtHdr
*
*       Desc:  This function packs the IPV6 route header
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmIpv6RtHdr
(
CmIpv6RtHdr             *pkParam,   /* IPV6 Route hdr */
Buffer                   *mBuf      /* message buffer */
)
#else
PUBLIC S16 cmPkCmIpv6RtHdr (pkParam, mBuf)
CmIpv6RtHdr             *pkParam;   /* IPV6 Route hdr */
Buffer                   *mBuf;     /* message buffer */
#endif
{
   U8 idx;
   
   TRC3(cmPkCmIpv6RtHdr);

   /* pack all IPV6 addrs in the route hdr */
   for(idx = 0; idx < pkParam->numAddrs; idx++)
   {
      CMCHKPK(cmPkCmIpv6NetAddr, &pkParam->ipv6Addrs[idx], mBuf);
   }
   /* pack reserve byte & strict/loose bit map */
   CMCHKPK(SPkU32, pkParam->slMap, mBuf);
   CMCHKPK(SPkU8, pkParam->numAddrs, mBuf);  

   RETVALUE(ROK);
} /* end of cmPkCmIpv6RtHdr */


/*
*
*       Fun:   cmUnpkCmIpv6RtHdr
*
*       Desc:  This function unpacks the IPV6 route header
*
*       Ret:   ROK
*              ROUTRES - out of resources
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmIpv6RtHdr
(
CmIpv6RtHdr             *unpkParam,  /* IPV6 Route hdr */
Buffer                  *mBuf,       /* message buffer */
Mem                     *memInfo     /* meminfo to allocate for Route hdr */
)
#else
PUBLIC S16 cmUnpkCmIpv6RtHdr (unpkParam, mBuf, memInfo)
CmIpv6RtHdr             *unpkParam;  /* IPV6 Route hdr */
Buffer                  *mBuf;       /* message buffer */
Mem                     *memInfo;    /* meminfo to allocate for Route hdr */
#endif
{
   U8 idx;  /* array index */
   S32 retVal; /* temporary return value */
   
   TRC3(cmUnpkCmIpv6RtHdr);
   
   CMCHKUNPK(SUnpkU8, &unpkParam->numAddrs, mBuf);
   
   /* unpack reserve byte & strict/loose bit map */
   CMCHKUNPK(SUnpkU32, &unpkParam->slMap, mBuf);
   
   retVal = SGetSBuf(memInfo->region,    
                  memInfo->pool,                     
                 (Data **)&unpkParam->ipv6Addrs, 
                 (unpkParam->numAddrs * 16));
      
   if (retVal != ROK)
   {
      RETVALUE(ROUTRES);
   }
   
   /* unpack all IPV6 addrs in the route hdr */
   for(idx = 0; idx < unpkParam->numAddrs; idx++)
   {
      CMCHKUNPK(cmUnpkCmIpv6NetAddr, &unpkParam->ipv6Addrs[idx], mBuf);
   }

   RETVALUE(ROK);
} /* end of cmUnpkCmIpv6RtHdr */


/*
*
*       Fun:   cmUnpkCmIpv6ExtHdr
*
*       Desc:  This function unpacks the IPv6 extension header
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmIpv6ExtHdr
(
CmIpv6ExtHdr             *unpkParam,  /* IPV6 extension hdrs */
Buffer                   *mBuf,       /* message buffer */
Mem                      *memInfo     /* meminfo to allocate for IPV6 ext hdr */
)
#else
PUBLIC S16 cmUnpkCmIpv6ExtHdr (unpkParam, mBuf, memInfo)
CmIpv6ExtHdr             *unpkParam; /* IPV6 extension hdrs */
Buffer                   *mBuf;      /* message buffer */
Mem                      *memInfo;   /* meminfo to allocate for IPV6 ext hdr */
#endif
{
   TRC3(cmUnpkCmIpv6ExtHdr)
      
   /* unpack HBH hdr first */
   CMCHKUNPK(cmUnpkBool, &unpkParam->hbhHdrPrsnt, mBuf); 
   if (unpkParam->hbhHdrPrsnt)
      cmUnpkCmIpv6HBHHdrArr(&unpkParam->hbhOptsArr, mBuf, memInfo);         
                                                         
   /* unpack DEST opt hdr */
   CMCHKUNPK(cmUnpkBool, &unpkParam->destOptsPrsnt, mBuf);
   if (unpkParam->destOptsPrsnt)
      cmUnpkCmIpv6DestOptsArr(&unpkParam->destOptsArr, mBuf, memInfo);   

   /* unpack Route hdr last */
   CMCHKUNPK(cmUnpkBool, &unpkParam->rtOptsPrsnt, mBuf); 
   if (unpkParam->rtOptsPrsnt)
      cmUnpkCmIpv6RtHdr(&unpkParam->rtOpts, mBuf, memInfo);  
                                                        
   RETVALUE(ROK);
} /* end of cmUnpkCmIpv6ExtHdr */


/*
*
*       Fun:   cmPkCmIpv6DestOptsArr
*
*       Desc:  This function packs the IPV6 Destination Option array
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmIpv6DestOptsArr
(
CmIpv6DestOptsArr       *pkParam,  /* IPV6 Dest hdr array */
Buffer                  *mBuf      /* message buffer */
)
#else
PUBLIC S16 cmPkCmIpv6DestOptsArr (pkParam, mBuf)
CmIpv6DestOptsArr       *pkParam;  /* IPV6 Dest hdr array */
Buffer                  *mBuf;     /* message buffer */
#endif
{

   U8 numOptions;

   TRC3(cmPkCmIpv6DestOptsArr);
   
   /* pack all HBH options */
   for(numOptions = 0; numOptions<pkParam->numDestOpts; numOptions++)  
      CMCHKPK(cmPkCmIpv6DestOptsHdr, &pkParam->destOpts[numOptions], mBuf);
   CMCHKPK(SPkU8, pkParam->numDestOpts, mBuf);  

   RETVALUE(ROK);
} /* end of cmPkCmIpv6DestOptsArr */


/*
*
*       Fun:   cmPkCmIpv6DestOptsHdr
*
*       Desc:  This function packs individua IPV6 Destination Option
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmIpv6DestOptsHdr
(
CmIpv6DestOptsHdr       *pkParam,  /* IPV6 Dest opt */
Buffer                  *mBuf      /* message buffer */
)
#else
PUBLIC S16 cmPkCmIpv6DestOptsHdr (pkParam, mBuf)
CmIpv6DestOptsHdr       *pkParam;  /* IPV6 Dest opt */
Buffer                  *mBuf;     /* message buffer */
#endif
{
   U8 optLen;
   
   TRC3(cmPkCmIpv6DestOptsHdr);

   for(optLen = 0; optLen < pkParam->length; optLen++)
   {
      CMCHKPK(SPkU8, pkParam->value[optLen], mBuf);
   }
   CMCHKPK(SPkU8, pkParam->length, mBuf);  
   CMCHKPK(SPkU8, pkParam->type, mBuf);  

   RETVALUE(ROK);
} /* end of cmPkCmIpv6DestOptsHdr */


/*
*
*       Fun:   cmUnpkCmIpv6DestOptsHdr
*
*       Desc:  This function unpacks individual IPV6 Dest Option
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmIpv6DestOptsHdr
(
CmIpv6DestOptsHdr       *unpkParam,/* IPV6 Dest Option */
Buffer                  *mBuf,     /* message buffer */
Mem                     *memInfo   /* meminfo to allocate mem for dest opt */
)
#else
PUBLIC S16 cmUnpkCmIpv6DestOptsHdr (unpkParam, mBuf, memInfo)
CmIpv6DestOptsHdr       *unpkParam;/* IPV6 Dest Option */
Buffer                  *mBuf;     /* message buffer */
Mem                     *memInfo;  /* meminfo to allocate mem for dest opt */
#endif
{
   S32 retVal;                        /* temporary return value */
   U8 optLen;                      /* length of value field */

   TRC3(cmUnpkCmIpv6DestOptsHdr);
  
   /* unpack type, length */
   CMCHKUNPK(SUnpkU8, &unpkParam->type, mBuf);  
   CMCHKUNPK(SUnpkU8, &unpkParam->length, mBuf);

   /* allocate static memory to hold the unpacked values */
   retVal = SGetSBuf(memInfo->region,                   
                  memInfo->pool,                     
                  (Data **)&unpkParam->value, (Size)unpkParam->length);
   if (retVal != ROK)
   {
      RETVALUE(ROUTRES);
   }
      
   /* unpack value fieldof this option */
   for(optLen = 0; optLen<unpkParam->length; optLen++)
   {
      CMCHKUNPK(SUnpkU8, &unpkParam->value[optLen], mBuf);  
   }    
   
   RETVALUE(ROK);
} /* end of cmUnpkCmIpv6DestOptsHdr */


/*
*
*       Fun:   cmUnpkCmIpv6DestOptsArr
*
*       Desc:  This function unpacks the IPV6 Destination Option array
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmIpv6DestOptsArr
(
CmIpv6DestOptsArr       *unpkParam, /* all IPV6 Destination Options */
Buffer                  *mBuf,      /* message buffer */
Mem                     *memInfo    /* meminfo to allocate mem for dest opts */
)
#else
PUBLIC S16 cmUnpkCmIpv6DestOptsArr (unpkParam, mBuf, memInfo)
CmIpv6DestOptsArr       *unpkParam; /* all IPV6 Destination Options */
Buffer                  *mBuf;      /* message buffer */
Mem                     *memInfo;   /* meminfo to allocate mem for dest opts */
#endif
{
   U8 numOptions;
   S16 retVal;
   
   TRC3(cmUnpkCmIpv6DestOptsArr);

   CMCHKUNPK(SUnpkU8, &unpkParam->numDestOpts, mBuf); 
   if (unpkParam->numDestOpts)
   {
      /* allocate mem to hold all dest options */
      retVal = SGetSBuf(memInfo->region,    
                     memInfo->pool,                     
                     (Data **)&unpkParam->destOpts, 
                     (unpkParam->numDestOpts * sizeof(CmIpv6DestOptsHdr)));
      
      if (retVal != ROK)
      {
         RETVALUE(ROUTRES);
      }
   
      /* unpack all dest options */
      for(numOptions = 0; numOptions<unpkParam->numDestOpts; numOptions++)
         if ((retVal = cmUnpkCmIpv6DestOptsHdr(&unpkParam->destOpts[numOptions],
                                            mBuf, memInfo)) != ROK)
            RETVALUE(RFAILED);   
   
   }                                             
   RETVALUE(ROK);
} /* end of cmUnpkCmIpv6DestOptsArr */


/*
*
*       Fun:   cmPkCmIpv6HBHHdrArr
*
*       Desc:  This function packs the all IPV6 HopByHop options
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmIpv6HBHHdrArr
(
CmIpv6HBHHdrArr         *pkParam,  /* all IPV6 HopByHop options */
Buffer                  *mBuf      /* message buffer */
)
#else
PUBLIC S16 cmPkCmIpv6HBHHdrArr (pkParam, mBuf)
CmIpv6HBHHdrArr         *pkParam;  /* IPV6 HopByHop options */
Buffer                  *mBuf;     /* message buffer */
#endif
{
   U8 numOptions;
   
   TRC3(cmPkCmIpv6HBHHdrArr);

   for(numOptions = 0; numOptions<pkParam->numHBHOpts; numOptions++)
      CMCHKPK(cmPkCmIpv6HBHHdr, &pkParam->hbhOpts[numOptions], mBuf);
                          
   CMCHKPK(SPkU8, pkParam->numHBHOpts, mBuf);  

   RETVALUE(ROK);
} /* end of cmPkCmIpv6HBHHdrArr */


/*
*
*       Fun:   cmPkCmIpv6HBHHdr
*
*       Desc:  This function packs individual IPV6 HBH options
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmIpv6HBHHdr
(
CmIpv6HBHHdr            *pkParam,  /* individual IPV6 HBH options */
Buffer                  *mBuf      /* message buffer */
)
#else
PUBLIC S16 cmPkCmIpv6HBHHdr (pkParam, mBuf)
CmIpv6HBHHdr            *pkParam;  /* individual IPV6 HBH options */
Buffer                  *mBuf;     /* message buffer */
#endif
{
   U8 optLen;

   TRC3(cmPkCmIpv6HBHHdr);

   /* pack value field */
   for(optLen = 0; optLen<pkParam->length; optLen++)
   {
      CMCHKPK(SPkU8, pkParam->value[optLen], mBuf);
   }

   /* pack type, length fields */
   CMCHKPK(SPkU8, pkParam->length, mBuf);  
   CMCHKPK(SPkU8, pkParam->type, mBuf);  

   RETVALUE(ROK);
} /* end of cmPkCmIpv6HBHHdr */


/*
*
*       Fun:   cmUnpkCmIpv6HBHHdr
*
*       Desc:  This function unpacks individual IPV6 HBH Option
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmIpv6HBHHdr
(
CmIpv6HBHHdr            *unpkParam,/* individual IPV6 HBH Option */
Buffer                  *mBuf,     /* message buffer */
Mem                     *memInfo   /* meminfo to allocate mem for HBH opt */
)
#else
PUBLIC S16 cmUnpkCmIpv6HBHHdr (unpkParam, mBuf, memInfo)
CmIpv6HBHHdr            *unpkParam;/* individual IPV6 HBH Option */
Buffer                  *mBuf;     /* message buffer */
Mem                     *memInfo;  /* meminfo to allocate mem for HBH opt */
#endif
{
   S32 retVal;                     /* temporary return value */
   U8 optLen;                      /* length of value field */
  
   TRC3(cmUnpkCmIpv6HBHHdr)
   
   CMCHKUNPK(SUnpkU8, &unpkParam->type, mBuf);   
   CMCHKUNPK(SUnpkU8, &unpkParam->length, mBuf);

   /* allocate static memory to hold the unpacked values */
   if (unpkParam->length)
   {
      retVal = SGetSBuf(memInfo->region,                   
                     memInfo->pool,                     
                     (Data **)&unpkParam->value, (Size)unpkParam->length); 
      if (retVal != ROK)
      {
         RETVALUE(ROUTRES);
      }

      for(optLen = 0; optLen<unpkParam->length; optLen++)
         CMCHKUNPK(SUnpkU8, &unpkParam->value[optLen], mBuf);  
   } 
      
   RETVALUE(ROK);
} /* end of cmUnpkCmIpv6HBHHdr */


/*
*
*       Fun:   cmUnpkCmIpv6HBHHdrArr
*
*       Desc:  This function unpacks all IPV6 HopByHop options
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmIpv6HBHHdrArr
(
CmIpv6HBHHdrArr       *unpkParam,  /* all HBH options */
Buffer                *mBuf,       /* message buffer */
Mem                   *memInfo     /* meminfo to allocate space for HBH opt */
)
#else
PUBLIC S16 cmUnpkCmIpv6HBHHdrArr (unpkParam, mBuf, memInfo)
CmIpv6HBHHdrArr       *unpkParam;  /*  all HBH options */
Buffer                *mBuf;       /* message buffer */
Mem                   *memInfo;    /* meminfo to allocate space for HBH opt */
#endif
{
   U8 numOptions; 
   S16 retVal;

   TRC3(cmUnpkCmIpv6HBHHdrArr);

   CMCHKUNPK(SUnpkU8, &unpkParam->numHBHOpts, mBuf);   
   if (unpkParam->numHBHOpts)
   {
      /*  allocate space for all HBH options */
      retVal = SGetSBuf(memInfo->region,    
                     memInfo->pool,                     
                     (Data **)&unpkParam->hbhOpts, 
                     (unpkParam->numHBHOpts * sizeof(CmIpv6HBHHdr)));
      
      if (retVal != ROK)
      {
         RETVALUE(ROUTRES);
      }

      for(numOptions = 0; numOptions<unpkParam->numHBHOpts; numOptions++)
         cmUnpkCmIpv6HBHHdr(&unpkParam->hbhOpts[numOptions], mBuf, memInfo);
   }                                              
   RETVALUE(ROK);
} /* end of cmUnpkCmIpv6HBHHdrArr */
#endif /* IPV6_OPTS_SUPPORTED */

  
/*
*
*       Fun:   cmUnpkCmIPHdrParm
*
*       Desc:  This function unpacks the IP header parameters
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
/* added */
#ifdef IPV6_OPTS_SUPPORTED
PUBLIC S16 cmUnpkCmIpHdrParm
(
CmIpHdrParm              *unpkParam,/* ip hdr parameters */
Buffer                   *mBuf,     /* message buffer */
Mem                      *memInfo   /* meminfo to allocate mem for ipHdrParam */
)
#else
PUBLIC S16 cmUnpkCmIpHdrParm
(
CmIpHdrParm              *unpkParam,/* ip hdr parameters */
Buffer                   *mBuf     /* message buffer */
)
#endif /* IPV6_OPTS_SUPPORTED */
#else
/* added */
#ifdef IPV6_OPTS_SUPPORTED
PUBLIC S16 cmUnpkCmIpHdrParm (unpkParam, mBuf, memInfo)
CmIpHdrParm              *unpkParam;/* ip hdr parameters */
Buffer                   *mBuf;     /* message buffer */
Mem                      *memInfo;  /* meminfo to allocate mem for ipHdrParam */
#else
PUBLIC S16 cmUnpkCmIpHdrParm (unpkParam, mBuf)
CmIpHdrParm              *unpkParam;/* ip hdr parameters */
Buffer                   *mBuf;     /* message buffer */
#endif /* IPV6_OPTS_SUPPORTED */
#endif
{
   TRC3(cmUnpkCmIpHdrParm)

   CMCHKUNPK(SUnpkU8, &unpkParam->type, mBuf);

   switch (unpkParam->type)
   {
      case CM_HDRPARM_NOTPRSNT:
      case CM_HDRPARM_ICMP6:
         break;

      case CM_HDRPARM_IPV4:
         CMCHKUNPK(cmUnpkTknU8, &unpkParam->u.hdrParmIpv4.proto, mBuf);
         CMCHKUNPK(cmUnpkTknU8, &unpkParam->u.hdrParmIpv4.dfBit, mBuf);
         CMCHKUNPK(cmUnpkTknU8, &unpkParam->u.hdrParmIpv4.tos, mBuf);
         CMCHKUNPK(cmUnpkTknU8, &unpkParam->u.hdrParmIpv4.ttl, mBuf);
#ifdef IPV4_OPTS_SUPPORTED
         CMCHKUNPK(cmUnpkTknStr64, &unpkParam->u.hdrParmIpv4.ipv4HdrOpt, mBuf);
#endif /* IPV4_OPTS_SUPPORTED */
         break;

      case CM_HDRPARM_IPV6:
#ifdef IPV6_SUPPORTED         
         CMCHKUNPK(cmUnpkTknU8, &unpkParam->u.hdrParmIpv6.ttl, mBuf);
   
         CMCHKUNPK(cmUnpkCmNetAddr, 
                   &unpkParam->u.hdrParmIpv6.srcAddr6, mBuf);
 
#ifdef IPV6_OPTS_SUPPORTED
         /* memInfo is passed forward to alloc mem to hold unpacked 
          * IPV6 etx hdr data */
         cmUnpkCmIpv6ExtHdr(&unpkParam->u.hdrParmIpv6.ipv6ExtHdr, 
                            mBuf, memInfo);
#endif /* IPV6_OPTS_SUPPORTED */         
#endif /* IPV6_SUPPORTED */
         break;
   
      default:
         RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);
}   /* End of cmUnpkCmIpHdrParm */


/*
*
*       Fun:   cmPkCmIcmpFilter
*
*       Desc:  This function packs the ICMP filter parameters
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmIcmpFilter
(
CmIcmpFilter             *pkParam,   
Buffer                   *mBuf       /* message buffer */
)
#else
PUBLIC S16 cmPkCmIcmpFilter (pkParam, mBuf)
CmIcmpFilter             *pkParam;   
Buffer                   *mBuf;      /* message buffer */
#endif
{
   /* Variable declaration */
   S16   idx;
  
   TRC3(cmPkCmIcmpFilter)

   switch (pkParam->type)
   {
      case CM_ICMP_NO_FILTER:
         break;

      case CM_ICMPVER4_FILTER:
         for(idx = (pkParam->u.icmpv4Filter.num-1); idx >= 0; idx--)
         {
            CMCHKPK(SPkU32, pkParam->u.icmpv4Filter.icmpError[idx].errCodeMask,
                    mBuf);
            CMCHKPK(SPkU8, pkParam->u.icmpv4Filter.icmpError[idx].errType,
                    mBuf);
         }
         CMCHKPK(SPkU8, pkParam->u.icmpv4Filter.num, mBuf);
         CMCHKPK(SPkU8, pkParam->u.icmpv4Filter.protocol, mBuf);
         CMCHKPK(SPkU8, pkParam->u.icmpv4Filter.allMsg, mBuf);
         CMCHKPK(SPkU8, pkParam->u.icmpv4Filter.icmpMsgFlag, mBuf);
         break;

      case CM_ICMPVER6_FILTER:
     /* The structure is yet to be decided */
     /* CMCHKPK(cmPkCmIpv6HdrParm, &pkParam->u.ipv6HdrParm, mBuf); */
#ifdef IPV6_SUPPORTED
         for(idx = (pkParam->u.icmpv6Filter.num - 1); idx >= 0; idx--)
         {
            CMCHKPK(SPkU32, pkParam->u.icmpv6Filter.icmpError[idx].errCodeMask,
                    mBuf);
            CMCHKPK(SPkU8, pkParam->u.icmpv6Filter.icmpError[idx].errType,
                    mBuf);
         }
         CMCHKPK(SPkU8, pkParam->u.icmpv6Filter.num, mBuf);
         CMCHKPK(SPkU8, pkParam->u.icmpv4Filter.allMsg, mBuf); 
         CMCHKPK(SPkU8, pkParam->u.icmpv4Filter.icmpMsgFlag, mBuf);
#endif /* IPV6_SUPPORTED */
         break;
   
      default:
         RETVALUE(RFAILED);
   }
   CMCHKPK(SPkU8, pkParam->type, mBuf);

   RETVALUE(ROK);
}

  
/*
*
*       Fun:   cmUnpkCmIcmpFilter
*
*       Desc:  This function unpacks the 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_tpt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCmIcmpFilter
(
CmIcmpFilter             *unpkParam,   
Buffer                   *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmUnpkCmIcmpFilter (unpkParam, mBuf)
CmIcmpFilter             *unpkParam;   
Buffer                   *mBuf;        /* message buffer */
#endif
{
   /* Variable declaration */ 
   S16     idx;

   TRC3(cmUnpkCmIcmpFilter)

   CMCHKUNPK(SUnpkU8, &unpkParam->type, mBuf);

   switch (unpkParam->type)
   {
      case CM_ICMP_NO_FILTER:
         break;

      case CM_ICMPVER4_FILTER:
         CMCHKUNPK(SUnpkU8, &unpkParam->u.icmpv4Filter.icmpMsgFlag, mBuf);
         CMCHKUNPK(SUnpkU8, &unpkParam->u.icmpv4Filter.allMsg, mBuf);
         CMCHKUNPK(SUnpkU8, &unpkParam->u.icmpv4Filter.protocol, mBuf);
         CMCHKUNPK(SUnpkU8, &unpkParam->u.icmpv4Filter.num, mBuf);

         for(idx = 0; idx < (unpkParam->u.icmpv4Filter.num); idx++)
         {
            CMCHKUNPK(SUnpkU8, 
                      &unpkParam->u.icmpv4Filter.icmpError[idx].errType, mBuf);
            CMCHKUNPK(SUnpkU32, 
                      &unpkParam->u.icmpv4Filter.icmpError[idx].errCodeMask, 
                      mBuf);
         }
         break;

      case CM_ICMPVER6_FILTER:
#ifdef IPV6_SUPPORTED
         CMCHKUNPK(SUnpkU8, &unpkParam->u.icmpv6Filter.icmpMsgFlag, mBuf);
         CMCHKUNPK(SUnpkU8, &unpkParam->u.icmpv6Filter.allMsg, mBuf); 
         CMCHKUNPK(SUnpkU8, &unpkParam->u.icmpv6Filter.num, mBuf);

         for(idx = 0; idx < (unpkParam->u.icmpv6Filter.num); idx++)
         {
            CMCHKUNPK(SUnpkU8, 
                      &unpkParam->u.icmpv6Filter.icmpError[idx].errType, mBuf);
            CMCHKUNPK(SUnpkU32, 
                      &unpkParam->u.icmpv6Filter.icmpError[idx].errCodeMask, 
                      mBuf);
         }
#endif /* IPV6_SUPPORTED */
         break;
   
      default:
         RETVALUE(RFAILED);

   }
   
   RETVALUE(ROK);
}   /* End of cmUnpkCmIcmpFilter */

#endif  /* CM_INET2 */ 

  
#endif /* if(LCHCT || LCHIT || LCLHC || LCHRT || LCLHR) */

  
/********************************************************************30**
  
         End of file:     cm_tpt.c@@/main/19 - Thu Mar 12 13:58:05 2009
  
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
1.1          ---      mb   1. initial release.

1.2          ---      kp   1. Added AAL support under CM_AAL.
                           2. Made functions available for LCLHR and
                              LCHRT.
                           3. Moved cm_inet includes to header files.
1.3          ---      bbk  1. Included defines for MGCP
/main/5      ---      sb   1. added packing/unpacking routines for header
                              parameters & filterparameters.
                      cvp  2. added CM_SOCKOPT_OPT_MCAST_IF parameter
                              packing.
                           3. Changed the copyright header.
/main/6      ---      nt   1. changed LCSBT to LCSCT. LCSBT was a typo. 
/main/7      ---      bsr  1. Added LCSOT and LCLSO
/main/8      ---      cvp  1. IPv6 Support related changes.
                           2. Changed the copyright header.
/main/9      ---      cvp  1. Moving cmIpv4TptAddr packing and unpacking 
                              functions from cm_inet.c file.
$(SID)$      ---      bbk  1. Added packing/unpacking functions for 
                              CmNetAddrTbl
/main/11     ---      vj   1. Merged IPV6 code with GCP 1.3 release
/main/12     ---      mmh  1. added new packing function cmPkCmTptLocalInf
                           2. added mising comments and changed other comments
                           3. call to pack ipv4 options in cmPkCmIpHdrParm()
                           4. pack IPV6 extension headers in cmPkCmIpHdrParm()
                           5. added new unpacking function cmUnpkCmTptLocalInf
                           6. added new packing/unpacking functions for IPv6
                              extension headers
                           7. call to unpack ipv4 options in cmUnpkCmIpHdrParm()
                           8. unpack IPV6 exten headers in cmUnpkCmIpHdrParm()
                          10. correct other miscellaneous code parts
/main/13     ---      bdu  1. Fix for MCAST6_IF option.
/main/14     ---      mj   1. MPLS release 1.2 changes.
/main/15     ---      bdu  1. ICMPv6 related changes.
/main/16     ---      wh   1. SIP 2.1 release changes.
/main/17     ---      kp   1. TUCL 1.5 release changes. Added TLS
                              parameter packing/unpacking functions.
/main/18     ---      cm_tpt_c_001.main_17  pc   1. Guarded under LCEGT/LCLEG.
/main/19     ---      cm_tpt_c_001.main_18  pc   1. Guarded under LWLCEGT.

*********************************************************************91*/
