

/********************************************************************20**
  
     Name:     TCP UDP Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for common packing and un-packing functions 
               for the Upper Interface(HIT) supplied by TRILLIUM
              
     File:    hit.c
  
     Sid:      hit.c@@/main/17 - Tue Apr 26 19:06:43 2011

     Prg:     asa
  
*********************************************************************21*/

/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*
*/


/* header include files (.h) */

#include "envopt.h"        /* environment options */  
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */
#include "cm_inet.h"       /* common sockets */
#include "cm_err.h"        /* common error */
#include "cm_tpt.h"        /* common transport defines */
#include "hit.h"           /* hit interface */


/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system service interface */
#include "cm_inet.x"       /* common sockets */
/*#include "cm_tkns.x"*/       /* common Token definitions */
#include "cm_tpt.x"        /* common transport typedefs */
#include "hit.x"           /* hit interface */

/* needed for cmMemset call */
#include "cm_lib.x"             /* lib library file */

/* local defines */

#define HI_GETMSG(_e, _p, _m) {                                         \
    S16     _ret;                                                       \
                                                                        \
    _ret = SGetMsg((_p)->region, (_p)->pool, &(_m));                    \
    if (_ret != ROK)                                                    \
    {                                                                   \
        /* hit_c_001.main_16: Fix for compilation warning*/        \
        SLogError(_p->srcEnt, _p->srcInst, _p->srcProcId,               \
                  __FILE__, (S32)__LINE__,                        \
                  (ErrCls)ERRCLS_ADD_RES, (ErrCode)_e, (ErrVal)_ret,    \
                  "Failed to allocate a message buffer");         \
        RETVALUE(_ret);                                                 \
    }                                                                   \
}


/* local typedefs */
  

/* local externs */
  
/* forward references */



/* functions in other modules */
  
/* public variable declarations */
  
/* private variable declarations */


 
#ifdef LCHIT
/*
 *     upper interface (HIT) packing functions
 */


/*
*
*       Fun:   Pack - Bind Request
*
*       Desc:  This function is used to pack the Bind Request primitive
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkHitBndReq
(
Pst       *pst,          /* Post structure */
SuId      suId,          /* service user sap id */
SpId      spId           /* service provider sap id */
)
#else
PUBLIC S16 cmPkHitBndReq(pst, suId, spId)
Pst      *pst;           /* Post structure */
SuId      suId;          /* service user sap id */
SpId      spId;          /* service provider sap id */
#endif
{
   Buffer  *mBuf;        /* message buffer */
   
   TRC3(cmPkHitBndReq)
   
   HI_GETMSG(EHIT001, pst, mBuf);
   CMCHKPKLOG(cmPkSpId, spId, mBuf, EHIT002, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, EHIT003, pst);

   pst->event = EVTHITBNDREQ;  /* event */
   RETVALUE(SPstTsk(pst, mBuf));
   
} /* end of cmPkHitBndReq */


/*
*
*       Fun:   Pack - Bind Confirmation
*
*       Desc:  This function is used to pack Bind Confirm 
*              primitive.
*              
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkHitBndCfm
(
Pst         *pst,         /* post structure */
SuId        suId,         /* Service User Id */
U8          status        /* status */
)
#else
PUBLIC S16 cmPkHitBndCfm(pst, suId, status)
Pst         *pst;         /* post structure */
SuId        suId;         /* Service User Id */
U8          status;       /* status */ 
#endif
{
   Buffer   *mBuf;        /* message buffer */

   TRC3(cmPkHitBndCfm)

   HI_GETMSG(EHIT004, pst, mBuf);
   CMCHKPKLOG(SPkU8,    status, mBuf, EHIT005, pst);
   CMCHKPKLOG(cmPkSuId, suId,   mBuf, EHIT006, pst);

   pst->event = EVTHITBNDCFM; /* event */

   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkHitBndCfm */


/*
*
*       Fun:   Pack - Un Bind Request
*
*       Desc:  This function is used to pack the Un Bind Request primitive
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkHitUbndReq
(
Pst *pst,              /* Post structure */
SpId spId,             /* Service provider Id */
Reason reason          /* cause for unbind operation */
)
#else
PUBLIC S16 cmPkHitUbndReq(pst, spId, reason)
Pst *pst;              /* Post structure */
SpId spId;             /* Service provider Id */
Reason reason;         /* cause for unbind operation */
#endif
{
   Buffer  *mBuf;        /* message buffer */

   TRC3(cmPkHitUBndReq)

   HI_GETMSG(EHIT007, pst, mBuf);
   CMCHKPKLOG(cmPkReason, reason, mBuf, EHIT008, pst);
   CMCHKPKLOG(cmPkSpId,   spId,   mBuf, EHIT009, pst);

   pst->event = EVTHITUBNDREQ;  /* event */
   RETVALUE(SPstTsk(pst, mBuf));
 
} /* end of cmPkHitUBndReq */


/*
*
*       Fun:   Pack - Server Open Request 
*
*       Desc:  This function is used to pack the Server Open Request primitive
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkHitServOpenReq
(
Pst *pst,               /* post stucture */
SpId spId,              /* service provider Id */
UConnId servConId,      /* service user's server connection Id */
CmTptAddr *servTAddr,   /* transport address of the server */ 
CmTptParam *tPar,       /* transport options */
CmIcmpFilter *icmpFilter, /*ICMP Filter parameter */
U8  srvcType            /* service type */
)
#else
PUBLIC S16 cmPkHitServOpenReq(pst, spId, servConId, servTAddr, tPar,
                              icmpFilter, srvcType)
Pst *pst;               /* post stucture */
SpId spId;              /* service provider Id */
UConnId servConId;      /* service user's server connection Id */
CmTptAddr  *servTAddr;  /* transport address of the server */ 
CmTptParam *tPar;       /* transport options */
CmIcmpFilter *icmpFilter; /*ICMP Filter parameter */
U8  srvcType;           /* service type */
#endif
{
   Buffer  *mBuf;        /* message buffer */

   TRC3(cmPkHitServOpenReq)

   HI_GETMSG(EHIT010, pst, mBuf);

   CMCHKPKLOG(cmPkCmIcmpFilter, icmpFilter, mBuf, EHIT011, pst);

   CMCHKPKLOG(SPkU8,          srvcType,  mBuf, EHIT012, pst);
   CMCHKPKLOG(cmPkCmTptParam, tPar,      mBuf, EHIT013, pst);
   CMCHKPKLOG(cmPkCmTptAddr,  servTAddr, mBuf, EHIT014, pst);

   CMCHKPKLOG(cmPkUConnId, servConId, mBuf, EHIT015, pst);
   CMCHKPKLOG(cmPkSpId,   spId,      mBuf, EHIT016, pst);

   pst->event = EVTHITSRVOPENREQ;  /* event */
   RETVALUE(SPstTsk(pst, mBuf));
 
} /* end of cmPkHitServOpenReq */


/*
*
*       Fun:   Pack - Connect Request
*
*       Desc:  This function is used to pack the Connect Request primitive
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkHitConReq
(
Pst *pst,              /* post structure */ 
SpId spId,             /* service provider id */ 
UConnId suConId,       /* service user's connection id */ 
CmTptAddr *remAddr,    /* address of the server */ 
CmTptAddr *localAddr,  /* local address */
CmTptParam *tPar,      /* transport parameters */
U8 srvcType            /* type of service */
)
#else
PUBLIC S16 cmPkHitConReq(pst, spId, suConId, remAddr, localAddr, tPar, 
                         srvcType) 
Pst *pst;              /* post structure */ 
SpId spId;             /* service provider id */ 
UConnId suConId;       /* service user's connection id */ 
CmTptAddr *remAddr;    /* address of the server */ 
CmTptAddr *localAddr;  /* local address */
CmTptParam *tPar;      /* transport parameters */
U8 srvcType;           /* type of service */
#endif
{
   Buffer  *mBuf;        /* message buffer */

   TRC3(cmPkHitConReq)

   HI_GETMSG(EHIT017, pst, mBuf);
   CMCHKPKLOG(SPkU8,          srvcType,  mBuf, EHIT018, pst);
   CMCHKPKLOG(cmPkCmTptParam, tPar,      mBuf, EHIT019, pst);
   CMCHKPKLOG(cmPkCmTptAddr,  localAddr, mBuf, EHIT020, pst);
   CMCHKPKLOG(cmPkCmTptAddr,  remAddr,   mBuf, EHIT021, pst);

   CMCHKPKLOG(cmPkUConnId, suConId, mBuf, EHIT022, pst);
   CMCHKPKLOG(cmPkSpId,   spId,    mBuf, EHIT023, pst);

   pst->event = EVTHITCONREQ;  /* event */
   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkHitConReq */


/*
*
*       Fun:   Pack - Connect Indication
*
*       Desc:  This function is used to pack connect Indication 
*              primitive.
*
*       Ret:   ROK
*
*       Notes: < none > 
*
*       File:  hit.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkHitConInd
(
Pst *pst,                 /* post stucture */
SpId suId,                /* service user Id */
UConnId servConId,        /* server's connection id */
UConnId spConId,          /* service provider's connection Id */
CmTptAddr *peerAddr       /* peer address */
)
#else
PUBLIC S16 cmPkHitConInd(pst, suId, servConId, spConId, peerAddr)
Pst *pst;                 /* post stucture */
SpId suId;                /* service user Id */
UConnId servConId;        /* server's connection id */
UConnId spConId;          /* service provider's connection Id */
CmTptAddr *peerAddr;      /* peer address */
#endif
{
   Buffer   *mBuf;        /* message buffer */

   TRC3(cmPkHitConInd)

   HI_GETMSG(EHIT024, pst, mBuf);
   CMCHKPKLOG(cmPkCmTptAddr, peerAddr,  mBuf, EHIT025, pst);
   CMCHKPKLOG(cmPkUConnId,      spConId,   mBuf, EHIT026, pst);
   CMCHKPKLOG(cmPkUConnId,      servConId, mBuf, EHIT027, pst);
   CMCHKPKLOG(cmPkSuId,        suId,      mBuf, EHIT028, pst);

   pst->event = EVTHITCONIND; /* event */

   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkHitConInd */


/*
*
*       Fun:   Pack - Connect Response
*
*       Desc:  This function is used to pack the Connect Response primitive
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkHitConRsp
(
Pst *pst,                /* post structure */ 
SpId spId,               /* service provider id */ 
UConnId suConId,         /* service user's connection id */ 
UConnId spConId          /* service provider's connection id */
)
#else
PUBLIC S16 cmPkHitConRsp(pst, spId, suConId, spConId)
Pst *pst;                /* post structure */ 
SpId spId;               /* service provider id */ 
UConnId suConId;         /* service user's connection id */ 
UConnId spConId;         /* service provider's connection id */
#endif
{
   Buffer  *mBuf;        /* message buffer */

   TRC3(cmPkHitConRsp)

   HI_GETMSG(EHIT029, pst, mBuf);
   CMCHKPKLOG(cmPkUConnId, spConId, mBuf, EHIT030, pst);
   CMCHKPKLOG(cmPkUConnId, suConId, mBuf, EHIT031, pst);
   CMCHKPKLOG(cmPkSpId,   spId,    mBuf, EHIT032, pst);

   pst->event = EVTHITCONRSP;  /* event */
   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkHitConRsp */


/*
*
*       Fun:   Pack - Connect Confirmation
*
*       Desc:  This function is used to pack connect confirm  
*              primitive.
*              
*       Ret:   ROK   - ok
*
*       Notes: < none > 
*
*       File:  hit.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkHitConCfm
(
Pst  *pst,                /* post structure */
SuId  suId,               /* Service User Id */
UConnId  suConId,         /* service user's connection Id */
UConnId  spConId,         /* service provider's connection Id */
CmTptAddr *localAddr      /* local transport address */
)
#else
PUBLIC S16 cmPkHitConCfm(pst, suId, suConId, spConId, localAddr)
Pst  *pst;                /* post structure */
SuId  suId;               /* Service User Id */
UConnId  suConId;         /* service user's connection Id */
UConnId  spConId;         /* service provider's connection Id */
CmTptAddr *localAddr;     /* local transport address */
#endif
{
   Buffer   *mBuf;        /* message buffer */

   TRC3(cmPkHitConCfm)

   HI_GETMSG(EHIT033, pst, mBuf);
   CMCHKPKLOG(cmPkCmTptAddr, localAddr, mBuf, EHIT034, pst);
   CMCHKPKLOG(cmPkUConnId,   spConId,   mBuf, EHIT035, pst);
   CMCHKPKLOG(cmPkUConnId,   suConId,   mBuf, EHIT036, pst);
   CMCHKPKLOG(cmPkSuId,      suId,      mBuf, EHIT037, pst);

   pst->event = EVTHITCONCFM; /* event */

   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkHitConCfm */


/*
*
*       Fun:   Pack - Data Request
*
*       Desc:  This function is used to pack the Data Request primitive
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkHitDatReq
(
Pst *pst,                /* post structure */ 
SpId spId,               /* service provider id */ 
UConnId spConId,         /* service provider's connection id */
Buffer *mBuf             /* message buffer */
)
#else
PUBLIC S16 cmPkHitDatReq(pst, spId, spConId, mBuf)
Pst *pst;                /* post structure */ 
SpId spId;               /* service provider id */ 
UConnId spConId;         /* service provider's connection id */
Buffer *mBuf;            /* message buffer */
#endif
{


   TRC3(cmPkHitDatReq)

   if(mBuf == NULLP)
   {
      HI_GETMSG(EHIT038, pst, mBuf);
   }

   CMCHKPKLOG(cmPkUConnId, spConId, mBuf, EHIT039, pst);
   CMCHKPKLOG(cmPkSpId,   spId,    mBuf, EHIT040, pst);

   pst->event = EVTHITDATREQ;  /* event */
   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkHitDatReq */


/*
*
*       Fun:   Pack - Data Indication
*
*       Desc:  This function is used to pack Data Indication 
*              primitive.
*
*       Ret:   ROK
*
*       Notes: < none > 
*
*       File:  hit.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkHitDatInd
(
Pst         *pst,         /* post structure */
SuId        suId,         /* service User Id */
UConnId      suConId,     /* service provider's connection id */ 
Buffer      *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmPkHitDatInd(pst, suId, suConId, mBuf)
Pst         *pst;         /* post structure */
SuId        suId;         /* service User Id */
UConnId     suConId;      /* service provider's connection id */ 
Buffer      *mBuf;        /* message buffer */
#endif
{
   TRC3(cmPkHitDatInd)

   if(mBuf == NULLP)
   {
      HI_GETMSG(EHIT041, pst, mBuf);
   }
   CMCHKPKLOG(cmPkUConnId, suConId, mBuf, EHIT042, pst);
   CMCHKPKLOG(cmPkSuId,   suId,    mBuf, EHIT043, pst);

   pst->event = EVTHITDATIND; /* event */
   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkHitDatInd */


/*
*
*       Fun:   Pack - Unit Data Request
*
*       Desc:  This function is used to pack the Unit Data Request primitive
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkHitUDatReq
(
Pst *pst,                /* post structure */ 
SpId spId,               /* service provider id */ 
UConnId spConId,         /* service provider connection id */
CmTptAddr *remAddr,      /* remote address */
CmTptAddr *srcAddr,      /* source Address */
CmIpHdrParm *ipHdrParm,  /* IP Header parameters */
CmTptParam *tPar,        /* transport parameters */
Buffer *mBuf             /* message buffer to be sent */
)
#else
PUBLIC S16 cmPkHitUDatReq(pst, spId, spConId, remAddr, srcAddr, 
                          ipHdrParm, tPar, mBuf)
Pst *pst;                /* post structure */ 
SpId spId;               /* service provider id */ 
UConnId spConId;         /* service provider connection id */
CmTptAddr *remAddr;      /* remote address */
CmTptAddr *srcAddr;      /* source Address */
CmIpHdrParm *ipHdrParm;  /* IP Header parameters */
CmTptParam *tPar;        /* transport parameters */
Buffer *mBuf;            /* message buffer to be sent */
#endif
{
   TRC3(cmPkHitUDatReq)

   if(mBuf == NULLP)
   {
      HI_GETMSG(EHIT044, pst, mBuf);
   }

   CMCHKPKLOG(cmPkCmTptParam, tPar,   mBuf, EHIT045, pst);
   CMCHKPKLOG(cmPkCmIpHdrParm, ipHdrParm, mBuf, EHIT046, pst);
   /* Free the ipHdrParam if necessary */
   /* added new macro to free memory allocated 
    *                    for IPv6 hdr parm */
#ifdef IPV6_OPTS_SUPPORTED
   CM_TPT_FREE_IPV6_HDRPARM(pst->region, pst->pool, ipHdrParm) 
#endif /* IPV6_OPTS_SUPPORTED */ 
   CMCHKPKLOG(cmPkCmTptAddr, srcAddr,  mBuf, EHIT047, pst);

   CMCHKPKLOG(cmPkCmTptAddr, remAddr,  mBuf, EHIT048, pst);
   CMCHKPKLOG(cmPkUConnId,   spConId,  mBuf, EHIT049, pst);
   CMCHKPKLOG(cmPkSpId,        spId,     mBuf, EHIT050, pst);

   pst->event = EVTHITUDATREQ;  /* event */
   RETVALUE(SPstTsk(pst, mBuf));
 
} /* end of cmPkHitUDatReq */


/*
*
*       Fun:   Pack - Unit Data Indication
*
*       Desc:  This function is used to pack Unit Data Indication 
*              primitive.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkHitUDatInd
(
Pst *pst,                 /* post stucture */
SuId suId,                /* service user Id */
UConnId suConId,          /* service user's connection Id */
CmTptAddr *srcAddr,       /* source transport address */
CmTptAddr *destAddr,      /* Destination Address */
CmIpHdrParm *ipHdrParm,   /* IP header parameters */
#ifdef LOCAL_INTF
CmTptLocalInf *localIf,   /* local intf on which pkt arrived */
#endif
Buffer *mBuf              /* message buffer */
)
#else
#ifdef LOCAL_INTF
PUBLIC S16 cmPkHitUDatInd(pst, suId, suConId, srcAddr, destAddr, 
                          ipHdrParm, localIf, mBuf)
Pst *pst;                 /* post stucture */
SuId suId;                /* service user Id */
UConnId suConId;          /* service user's connection Id */
CmTptAddr *srcAddr;       /* source transport address */
CmTptAddr *destAddr;      /* Destination Address */
CmIpHdrParm *ipHdrParm;   /* IP header parameters */
CmTptLocalInf *localIf;   /* local intf on which pkt arrived */
Buffer *mBuf;             /* message buffer */
#else
PUBLIC S16 cmPkHitUDatInd(pst, suId, suConId, srcAddr, destAddr, 
                          ipHdrParm, mBuf)
Pst *pst;                 /* post stucture */
SuId suId;                /* service user Id */
UConnId suConId;          /* service user's connection Id */
CmTptAddr *srcAddr;       /* source transport address */
CmTptAddr *destAddr;      /* Destination Address */
CmIpHdrParm *ipHdrParm;   /* IP header parameters */
Buffer *mBuf;             /* message buffer */
#endif /* LOCAL_INTF */
#endif /* ANSI */
{
   TRC3(cmPkHitUDatInd)

   if(mBuf == NULLP)
   {
      HI_GETMSG(EHIT051, pst, mBuf);
   }

   /* added new packing function for ip hdr parameters */
#ifdef LOCAL_INTF   
   CMCHKPKLOG(cmPkCmTptLocalInf, localIf, mBuf, EHIT052, pst);
#endif /* LOCAL_INTF */   
   CMCHKPKLOG(cmPkCmIpHdrParm, ipHdrParm, mBuf, EHIT053, pst);

   /* free here the memory used to hold all received ancillary data
    * in function cmInet6BuildRecvHopOptsArr(). */
#ifdef IPV6_OPTS_SUPPORTED   
   CM_TPT_FREE_IPV6_HDRPARM(pst->region, pst->pool, ipHdrParm);
#endif /* IPV6_OPTS_SUPPORTED */
   CMCHKPKLOG(cmPkCmTptAddr, destAddr,  mBuf, EHIT054, pst);

   CMCHKPKLOG(cmPkCmTptAddr, srcAddr,  mBuf, EHIT055, pst);
   CMCHKPKLOG(cmPkUConnId,      suConId,  mBuf, EHIT056, pst);
   CMCHKPKLOG(cmPkSuId,        suId,     mBuf, EHIT057, pst);

   pst->event = EVTHITUDATIND; /* event */
   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkHitUDatInd */


/*
*
*       Fun:   Pack - Disconnect Request
*
*       Desc:  This function is used to pack the Disconnect Request primitive
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkHitDiscReq
(
Pst *pst,                /* post structure */ 
SpId spId,               /* service provider id */ 
U8 choice,               /* choice of user or provider connection id */
UConnId conId,           /* connection id */
Action action,           /* action to be performed */
CmTptParam  *tPar        /* transport parameters */ 
)
#else
PUBLIC S16 cmPkHitDiscReq(pst, spId, choice, conId, action, tPar)
Pst *pst;                /* post structure */ 
SpId spId;               /* service provider id */ 
U8 choice;               /* choice of user or provider connection id */
UConnId conId;           /* connection id */
Action action;           /* action to be performed */
CmTptParam  *tPar;       /* transport parameters */ 
#endif
{
   Buffer  *mBuf;        /* message buffer */

   TRC3(cmPkHitDiscReq)

   HI_GETMSG(EHIT058, pst, mBuf);
   CMCHKPKLOG(cmPkCmTptParam, tPar,   mBuf, EHIT059, pst);
   CMCHKPKLOG(cmPkAction,       action, mBuf, EHIT060, pst);
   CMCHKPKLOG(cmPkUConnId,       conId,  mBuf, EHIT061, pst);
   CMCHKPKLOG(SPkU8,            choice, mBuf, EHIT062, pst);
   CMCHKPKLOG(cmPkSpId,         spId,   mBuf, EHIT063, pst);

   pst->event = EVTHITDISCREQ;  /* event */
   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkHitDiscReq */


/*
*
*       Fun:   Pack - Disconnect Indication
*
*       Desc:  This function is used to pack Disconnect Indication 
*              primitive.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkHitDiscInd
(
Pst *pst,                 /* post stucture */
SpId suId,                /* service user Id */
U8  choice,               /* choice parameter */
UConnId conId,            /* connection Id */
Reason reason             /* reason */
)
#else
PUBLIC S16 cmPkHitDiscInd(pst, suId, choice, conId, reason)
Pst *pst;                 /* post stucture */
SpId suId;                /* service user Id */
U8  choice;               /* choice parameter */
UConnId conId;            /* connection Id */
Reason reason;            /* reason */
#endif
{
   Buffer   *mBuf;        /* message buffer */

   TRC3(cmPkHitDiscInd)

   HI_GETMSG(EHIT064, pst, mBuf);
   CMCHKPKLOG(cmPkReason, reason,  mBuf, EHIT065, pst);
   CMCHKPKLOG(cmPkUConnId, conId,   mBuf, EHIT066, pst);
   CMCHKPKLOG(SPkU8,      choice,  mBuf, EHIT067, pst);
   CMCHKPKLOG(cmPkSuId,   suId,    mBuf, EHIT068, pst);

   pst->event = EVTHITDISCIND; /* event */
   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkHitDiscInd */


/*
*
*       Fun:   Pack - Disconnect Confirmation
*
*       Desc:  This function is used to pack Disconnect Confirm
*              primitive.
*
*       Ret:   ROK
*
*       Notes: < none > 
* 
*       File:  hit.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkHitDiscCfm
(
Pst *pst,                 /* post stucture */
SpId suId,                /* service user Id */
U8  choice,               /* choice parameter */
UConnId conId,            /* connection Id */
Action action             /* action type */
)
#else
PUBLIC S16 cmPkHitDiscCfm(pst, suId, choice, conId, action)       
Pst *pst;                 /* post stucture */
SpId suId;                /* service user Id */
U8  choice;               /* choice parameter */
UConnId conId;            /* connection Id */
Action action;            /* action type */
#endif
{
   Buffer   *mBuf;        /* message buffer */

   TRC3(cmPkHitDiscCfm)

   HI_GETMSG(EHIT069, pst, mBuf);
   
   CMCHKPKLOG(cmPkAction, action, mBuf, EHIT070, pst);
   CMCHKPKLOG(cmPkUConnId, conId,  mBuf, EHIT071, pst);
   CMCHKPKLOG(SPkU8,      choice, mBuf, EHIT072, pst);
   CMCHKPKLOG(cmPkSuId,   suId,   mBuf, EHIT073, pst);

   pst->event = EVTHITDISCCFM; /* event */
   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkHitDiscCfm */


/*
*
*       Fun:   Pack - Flow Control Indication 
*
*       Desc:  This function is used to pack Flow Control 
*              Indication primitive.
*
*       Ret:   ROK
*
*       Notes: < none > 
*
*       File:  hit.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkHitFlcInd 
(
Pst         *pst,         /* post structure */
SuId        suId,         /* Service User Id */
UConnId     suConId,      /* Service User Connection Id */
Reason      reason        /* reason for flow control */
)
#else
PUBLIC S16 cmPkHitFlcInd(pst, suId, suConId, reason)
Pst         *pst;         /* post structure */
SuId        suId;         /* Service User Id */
UConnId     suConId;      /* Service User Connection Id */
Reason      reason;       /* reason for flow control */
#endif /* ANSI */
{
   Buffer   *mBuf;        /* message buffer */

   TRC3(cmPkHitFlcInd)

   HI_GETMSG(EHIT074, pst, mBuf);

   CMCHKPKLOG(cmPkReason, reason,  mBuf, EHIT075, pst);
   CMCHKPKLOG(cmPkUConnId, suConId, mBuf, EHIT076, pst);
   CMCHKPKLOG(cmPkSuId,   suId,    mBuf, EHIT077, pst);

   pst->event = EVTHITFLCIND; /* event */
   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkHitFlcInd */

#ifdef HIT_MPLS

/*
*
*       Fun:   Pack - Pdu Length Range Request
*
*       Desc:  This function is used to pack the Pdu Length Range Request 
*              primitive
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkHitPduLenRngReq
(
Pst     *pst,     /* post structure      */ 
SpId    spId,     /* service provider id */ 
UConnId spConId,  /* service provider's connection id */ 
U32     minLen,   /* minimun PDU len     */
U32     maxLen    /* minimun PDU len     */
)
#else
PUBLIC S16 cmPkHitPduLenRngReq (pst, spId, spConId, minLen, maxLen) 
Pst     *pst;     /* post structure      */ 
SpId    spId;     /* service provider id */ 
UConnId spConId;  /* service provider's connection id */ 
U32     minLen;   /* minimun PDU len     */
U32     maxLen;   /* minimun PDU len     */
#endif
{
   Buffer  *mBuf;        /* message buffer */

   TRC3(cmPkHitPduLenRngReq)

   HI_GETMSG(EHIT078, pst, mBuf);

   CMCHKPKLOG(SPkU32,      maxLen,  mBuf, EHIT079, pst);
   CMCHKPKLOG(SPkU32,      minLen,  mBuf, EHIT080, pst);
   CMCHKPKLOG(cmPkUConnId, spConId, mBuf, EHIT081, pst);
   CMCHKPKLOG(cmPkSpId,    spId,    mBuf, EHIT082, pst);

   pst->event = EVTHITPDULENRNGREQ;  /* event */

   RETVALUE(SPstTsk(pst, mBuf));

} /* end of cmPkHitPduLenRngReq */

#endif /* HIT_MPLS */

/* hit_c_001.main_14 :         Added the following packing/unpacking functions 
                               cmPkHitTlsEstReq and cmUnpkHitTlsEstReq. */
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
/*
*
*       Fun:   Pack - Tls Establishment Request 
*
*       Desc:  This function is used to pack the Tls Establishment Request primitive
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkHitTlsEstReq
(
Pst *pst,               /* post stucture */
SpId spId,              /* service provider Id */
UConnId spConId,        /* service provider connection Id */
S16 ctxId,              /* Context Id */
U8  nodeType            /* node type */
)
#else
PUBLIC S16 cmPkHitTlsEstReq(pst, spId, spConId, ctxId, nodeType)
Pst *pst;               /* post stucture */
SpId spId;              /* service provider Id */
UConnId spConId;        /* service provider connection Id */
S16 ctxId;             /* Context Id */ 
U8 nodeType;           /* node type */
#endif
{
   Buffer  *mBuf;        /* message buffer */

   TRC3(cmPkHitTlsEstReq)

   HI_GETMSG(EHIT158, pst, mBuf);

   CMCHKPKLOG(SPkU8, nodeType,  mBuf, EHIT159, pst);
   CMCHKPKLOG(SPkS16, ctxId, mBuf, EHIT160, pst);
   CMCHKPKLOG(cmPkUConnId, spConId, mBuf, EHIT161, pst);
   CMCHKPKLOG(cmPkSpId, spId, mBuf, EHIT162, pst);

   pst->event = EVTHITTLSESTREQ;  /* event */
   RETVALUE(SPstTsk(pst, mBuf));
 
} /* end of cmPkHitTlsEstReq */

/*
*
*       Fun:   Pack - Tls Establishment Confirmation
*
*       Desc:  This function is used to pack Tls Establishment Confirm 
*              primitive.
*              
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkHitTlsEstCfm
(
Pst         *pst,         /* post structure */
SuId        suId,         /* Service User Id */
UConnId     suConId,       /* Service user connection Id */
U8          status,        /* status */
Reason      reason         /* reason */
)
#else
PUBLIC S16 cmPkHitTlsEstCfm(pst, suId, suConId, status, reason)
Pst         *pst;         /* post structure */
SuId        suId;         /* Service User Id */
UConnId     suConId;      /* Service user connection Id */
U8          status;       /* status */ 
Reason      reason;        /* reason */
#endif
{
   Buffer   *mBuf;        /* message buffer */

   TRC3(cmPkHitTlsEstCfm)

   HI_GETMSG(EHIT163, pst, mBuf);
   CMCHKPKLOG(cmPkReason, reason, mBuf, EHIT164, pst);
   CMCHKPKLOG(SPkU8, status, mBuf, EHIT165, pst);
   CMCHKPKLOG(cmPkUConnId, suConId, mBuf, EHIT166, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, EHIT167, pst);

   pst->event = EVTHITTLSESTCFM; /* event */

   RETVALUE(SPstTsk(pst, mBuf));

}/* end of cmPkHitTlsEstCfm */

#endif /* HI_TCP_TLS */
#endif /* HI_TLS */
#endif /* HITV2*/


/* ------------------------------------------------------------- */
/* HIT Interface UNPACK Functions */

/*
*
*       Fun:   cmUnpkHitBndReq
*
*       Desc:  unpack network bind request.
*
*       Ret:   ROK
*
*       File:  hit.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkHitBndReq
(
HitBndReq func,
Pst       *pst,                    /* post structure */
Buffer    *mBuf                    /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitBndReq(func, pst, mBuf)
HitBndReq func;
Pst    *pst;                    /* post structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SuId suId = 0;                   /* service user id */
   SpId spId = 0;                   /* service provider id */

   TRC3(cmUnpkHitBndReq)

      /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, EHIT083, pst);
   CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, EHIT084, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func)(pst, suId, spId);
   RETVALUE(ROK);
}  /* end of cmUnpkHitBndReq */



/*
*
*       Fun:   cmUnpkHitBndCfm
*
*       Desc:  unpack network bind confirm
*
*       Ret:   ROK
*
*       File:  hit.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkHitBndCfm
(
HitBndCfm func,                 /* function */
Pst    *pst,                    /* post structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitBndCfm(func, pst, mBuf)
HitBndCfm func;                 /* function */
Pst    *pst;                    /* post structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SuId suId = 0;                   /* service user id */
   U8   status;                 /* status */ 

   TRC3(cmUnpkHitBndCfm)
  
   /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSuId, &suId,   mBuf, EHIT085, pst);
   CMCHKUNPKLOG(SUnpkU8,   &status, mBuf, EHIT086, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func)(pst, suId, status);  
   RETVALUE(ROK);
}  /* end of cmUnpkHitBndCfm */


/*
*
*       Fun:   cmUnpkHitUbndReq
*
*       Desc:  Unpack Network Unbind Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkHitUbndReq
(
HitUbndReq func,
Pst    *pst,                    /* post structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitUbndReq(func, pst, mBuf)
HitUbndReq func;
Pst    *pst;                    /* post structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SpId   spId = 0;                 /* service provider id */
   Reason reason = 0;               /* reason */

   TRC3(cmUnpkHitUbndReq)
    /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSpId,   &spId,   mBuf, EHIT087, pst);
   CMCHKUNPKLOG(cmUnpkReason, &reason, mBuf, EHIT088, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */ 
   (*func)(pst, spId, reason);
   RETVALUE(ROK);
} /* end of cmUnpkHitUbndReq */


/*
*
*       Fun:   cmUnpkHitServOpenReq
*
*       Desc:  Unpack Server Open Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkHitServOpenReq
(
HitServOpenReq func,
Pst    *pst,                    /* post structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitServOpenReq(func, pst, mBuf)
HitServOpenReq func;
Pst    *pst;                    /* post structure */
Buffer *mBuf;                   /* message buffer */
#endif
{

   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SpId   spId = 0;                 /* service provider id */
   UConnId servConId = 0;         /* server connection id */
   CmTptAddr   servTAddr;     /* transport address of the server */ 
   CmTptParam  tPar;          /* transport options */
   U8  srvcType;              /* service type */
   CmIcmpFilter icmpFilter;   /* Icmp Filter structure */

   TRC3(cmUnpkHitServOpenReq)

   /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSpId,       &spId,      mBuf, EHIT089, pst);
   CMCHKUNPKLOG(cmUnpkUConnId,    &servConId, mBuf, EHIT090, pst);
   CMCHKUNPKLOG(cmUnpkCmTptAddr,  &servTAddr, mBuf, EHIT091, pst);
   CMCHKUNPKLOG(cmUnpkCmTptParam, &tPar,      mBuf, EHIT092, pst);
   CMCHKUNPKLOG(SUnpkU8,          &srvcType,  mBuf, EHIT093, pst);

   CMCHKUNPKLOG(cmUnpkCmIcmpFilter, &icmpFilter, mBuf, EHIT094, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func)(pst, spId, servConId, &servTAddr, &tPar, &icmpFilter, srvcType);

   RETVALUE(ROK);
} /* end of cmUnpkHitServOpenReq */


/*
*
*       Fun:   cmUnpkHitConReq
*
*       Desc:  Unpack Connect Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkHitConReq
(
HitConReq func,
Pst    *pst,                    /* post structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitConReq(func, pst, mBuf)
HitConReq func;
Pst    *pst;                    /* post structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SpId   spId = 0;                 /* service provider id */
   UConnId suConId = 0;       /* service user's connection id */ 
   CmTptAddr  remAddr;    /* address of the server */ 
   CmTptAddr  localAddr;  /* local address */
   CmTptParam tPar;       /* transport parameters */
   U8 srvcType;           /* service type */

   TRC3(cmUnpkHitConReq)
   
   /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSpId,       &spId,      mBuf, EHIT095, pst);
   CMCHKUNPKLOG(cmUnpkUConnId,    &suConId,   mBuf, EHIT096, pst);
   CMCHKUNPKLOG(cmUnpkCmTptAddr,  &remAddr,   mBuf, EHIT097, pst);
   CMCHKUNPKLOG(cmUnpkCmTptAddr,  &localAddr, mBuf, EHIT098, pst);
   CMCHKUNPKLOG(cmUnpkCmTptParam, &tPar,      mBuf, EHIT099, pst);
   CMCHKUNPKLOG(SUnpkU8,          &srvcType,  mBuf, EHIT100, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func)(pst, spId, suConId, &remAddr, &localAddr, &tPar, srvcType);

   RETVALUE(ROK);
} /* end of cmUnpkHitConReq */


/*
*
*       Fun:   cmUnpkHitConInd
*
*       Desc:  Unpack Connect Response
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkHitConInd
(
HitConInd func,                 /* function */
Pst    *pst,                    /* post structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitConInd(func, pst, mBuf)
HitConInd func;                 /* function */
Pst    *pst;                    /* post structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SuId suId = 0;                   /* service user id */
   UConnId servConId = 0;  /* server connection id */
   UConnId spConId = 0;    /* service provider's connection Id */
   CmTptAddr  peerAddr;    /* peer address */

   TRC3(cmUnpkHitConInd)

    /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSuId,        &suId,      mBuf, EHIT101, pst);
   CMCHKUNPKLOG(cmUnpkUConnId,      &servConId, mBuf, EHIT102, pst);
   CMCHKUNPKLOG(cmUnpkUConnId,      &spConId,   mBuf, EHIT103, pst);
   CMCHKUNPKLOG(cmUnpkCmTptAddr, &peerAddr,  mBuf, EHIT104, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func)(pst, suId, servConId, spConId, &peerAddr);
   RETVALUE(ROK);  
}


/*
*
*       Fun:   cmUnpkHitConRsp
*
*       Desc:  Unpack Connect Response
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkHitConRsp
(
HitConRsp func,
Pst    *pst,                    /* post structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitConRsp(func, pst, mBuf)
HitConRsp func;
Pst    *pst;                    /* post structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SpId   spId = 0;                 /* service provider id */
   UConnId suConId = 0;          /* service user's connection id */ 
   UConnId spConId = 0;          /* service provider's connection id */ 

   TRC3(cmUnpkHitConRsp)

    /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSpId,   &spId, mBuf, EHIT105, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suConId, mBuf, EHIT106, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &spConId, mBuf, EHIT107, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func)(pst, spId, suConId, spConId);

   RETVALUE(ROK);  
}


/*
*
*       Fun:   cmUnpkHitConCfm
*
*       Desc:  Unpack Connect Response
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkHitConCfm
(
HitConCfm func,                 /* function */
Pst    *pst,                    /* post structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitConCfm(func, pst, mBuf)
HitConCfm func;                 /* function */
Pst    *pst;                    /* post structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SuId suId = 0;                   /* service user id */
   UConnId suConId = 0;          /* service user's connection id */ 
   UConnId spConId = 0;          /* service provider's connection id */ 
   CmTptAddr localAddr;      /* local transport address */

   TRC3(cmUnpkHitConCfm)

    /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSuId,      &suId,      mBuf, EHIT108, pst);
   CMCHKUNPKLOG(cmUnpkUConnId,   &suConId,   mBuf, EHIT109, pst);
   CMCHKUNPKLOG(cmUnpkUConnId,   &spConId,   mBuf, EHIT110, pst);
   CMCHKUNPKLOG(cmUnpkCmTptAddr, &localAddr, mBuf, EHIT111, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func)(pst, suId, suConId, spConId, &localAddr);

   RETVALUE(ROK);  
}


/*
*
*       Fun:   cmUnpkHitDatReq
*
*       Desc:  Unpack Data Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkHitDatReq
(
HitDatReq func,
Pst    *pst,                    /* post structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitDatReq(func, pst, mBuf)
HitDatReq func;
Pst    *pst;                    /* post structure */
Buffer *mBuf;                   /* message buffer */
#endif
{

   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SpId   spId = 0;                 /* service provider id */
   UConnId spConId = 0;     /* service provider's connection id */

   TRC3(cmUnpkHitDatReq)
      /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSpId,   &spId, mBuf, EHIT112, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &spConId, mBuf, EHIT113, pst);

   /* call the primitive */
   (*func)(pst, spId, spConId, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkHitDatReq */


/*
*
*       Fun:   cmUnpkHitDatInd
*
*       Desc:  Unpack Data Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkHitDatInd
(
HitDatInd func,                 /* function */
Pst    *pst,                    /* post structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitDatInd(func, pst, mBuf)
HitDatInd func;                 /* function */
Pst    *pst;                    /* post structure */
Buffer *mBuf;                   /* message buffer */
#endif
{

   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SuId   suId = 0;             /* service User Id */
   UConnId suConId = 0;          /* service provider's connection id */ 

   TRC3(cmUnpkHitDatInd)
   /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSuId,   &suId, mBuf, EHIT114, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suConId, mBuf, EHIT115, pst);

   /* call the primitive */
   (*func)(pst, suId, suConId, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkHitDatInd */


/*
*
*       Fun:   cmUnpkHitUDatReq
*
*       Desc:  Unpack Unit Data Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
/* added new declaration */
#ifdef IPV6_OPTS_SUPPORTED
PUBLIC S16 cmUnpkHitUDatReq
(
HitUDatReq func,
Pst    *pst,    /* post structure */
Buffer *mBuf,   /* message buffer */
/* added new arg memInfo */
Mem    *memInfo /* meminfo for IPV6 extension headers */
)
#else
PUBLIC S16 cmUnpkHitUDatReq
(
HitUDatReq func,
Pst    *pst,    /* post structure */
Buffer *mBuf    /* message buffer */
)
#endif /* IPV6_OPTS_SUPPORTED */
#else
/* added new declaration */
#ifdef IPV6_OPTS_SUPPORTED
PUBLIC S16 cmUnpkHitUDatReq(func, pst, mBuf, memInfo)
HitUDatReq func;
Pst    *pst;    /* post structure */
Buffer *mBuf;   /* message buffer */
/* added new arg memInfo */
Mem    *memInfo;/* meminfo for IPV6 extension headers */
#else
PUBLIC S16 cmUnpkHitUDatReq(func, pst, mBuf)
HitUDatReq func;
Pst    *pst;    /* post structure */
Buffer *mBuf;   /* message buffer */
#endif /* IPV6_OPTS_SUPPORTED */
#endif
{

   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SpId   spId = 0;                 /* service provider id */
   CmTptAddr  remAddr;      /* remote address */
   UConnId  spConId = 0;        /* service provider's connection id */
   CmTptAddr  srcAddr;      /* source transport address */
   CmIpHdrParm ipHdrParm;   /* IP header parameters */

   /* added new var */
#ifdef IPV6_OPTS_SUPPORTED   
   S16 retVal;
#endif   
   CmTptParam  tPar;        /* transport parameters */

   TRC3(cmUnpkHitUDatReq)

   /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSpId,        &spId,     mBuf, EHIT116, pst);
   CMCHKUNPKLOG(cmUnpkUConnId,   &spConId,  mBuf, EHIT117, pst);
   CMCHKUNPKLOG(cmUnpkCmTptAddr, &remAddr,  mBuf, EHIT118, pst);

   CMCHKUNPKLOG(cmUnpkCmTptAddr, &srcAddr,  mBuf, EHIT119, pst);
   /* added new arg in func cmUnpkCmIpHdrParm */
#ifdef IPV6_OPTS_SUPPORTED
   /* replaced by direct func call rather than writing new macro */
   if ((retVal = cmUnpkCmIpHdrParm(&ipHdrParm, mBuf, memInfo)) != ROK)
   {
      SPutMsg(mBuf); 
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                (Txt*)__FILE__, (S32)__LINE__,
                (ErrCls)ERRCLS_ADD_RES, EHIT120, (ErrVal)retVal,
                (Txt*)"Unpacking of ipHdrParm fails");
      RETVALUE(retVal);
   }   
#else
   CMCHKUNPKLOG(cmUnpkCmIpHdrParm, &ipHdrParm, mBuf, EHIT121, pst);
#endif /* IPV6_OPTS_SUPPORTED */
   
   CMCHKUNPKLOG(cmUnpkCmTptParam, &tPar, mBuf, EHIT122, pst);

   /* call the primitive */

   (*func)(pst, spId, spConId, &remAddr, &srcAddr, &ipHdrParm, &tPar,
           mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkHitUDatReq */


/*
*
*       Fun:   cmUnpkHitUDatInd
*
*       Desc:  Unpack Unit Data Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
#ifdef IPV6_OPTS_SUPPORTED
PUBLIC S16 cmUnpkHitUDatInd
(
HitUDatInd func, /* function */ 
Pst    *pst,     /* post structure */
Buffer *mBuf,    /* message buffer */
/* added new arg memInfo */
Mem    *memInfo  /* meminfo to hold unpacked IPV6 extension hdr data */
)
#else
PUBLIC S16 cmUnpkHitUDatInd
(
HitUDatInd func, /* function */ 
Pst    *pst,     /* post structure */
Buffer *mBuf    /* message buffer */
)
#endif /* IPV6_OPTS_SUPPORTED */
#else
/* added new function decaration */
#ifdef IPV6_OPTS_SUPPORTED
PUBLIC S16 cmUnpkHitUDatInd(func, pst, mBuf, memInfo)
HitUDatInd func; /* function */ 
Pst    *pst;     /* post structure */
Buffer *mBuf;    /* message buffer */
Mem    *memInfo; /* meminfo to hold unpacked IPV6 extension hdr data */
#else
PUBLIC S16 cmUnpkHitUDatInd(func, pst, mBuf)
HitUDatInd func; /* function */ 
Pst    *pst;     /* post structure */
Buffer *mBuf;    /* message buffer */
#endif /* IPV6_OPTS_SUPPORTED */
#endif
{

   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SuId   suId = 0;             /* service User Id */
   UConnId suConId = 0;          /* service user's connection Id */
   CmTptAddr  srcAddr;       /* source transport address */
#ifdef IPV6_OPTS_SUPPORTED   
   S16 retVal;
#endif   
   CmTptAddr  destAddr;      /* source transport address */
   CmIpHdrParm ipHdrParm;    /* IP header parameters */
#ifdef LOCAL_INTF   
   CmTptLocalInf localIf;    /* local intf on which pkt arrived */
#endif /* LOCAL_INTF */   

   TRC3(cmUnpkHitUDatInd)

   /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSuId,        &suId,     mBuf, EHIT123, pst);
   CMCHKUNPKLOG(cmUnpkUConnId,    &suConId,  mBuf, EHIT124, pst);
   CMCHKUNPKLOG(cmUnpkCmTptAddr, &srcAddr,  mBuf, EHIT125, pst);

   CMCHKUNPKLOG(cmUnpkCmTptAddr, &destAddr,  mBuf, EHIT126, pst);

   /* init ipHdrParm structure to all 0 */
   cmMemset((U8 *)&ipHdrParm, 0, sizeof(ipHdrParm));

   /* added new arg memInfo */
#ifdef IPV6_OPTS_SUPPORTED   
   /* replaced by direct func call rather than writing new macro */
   if ((retVal = cmUnpkCmIpHdrParm(&ipHdrParm, mBuf, memInfo)) != ROK)
   {
      SPutMsg(mBuf); 
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                (Txt*)__FILE__, (S32)__LINE__,
                (ErrCls)ERRCLS_ADD_RES, EHIT127, (ErrVal)retVal,
                (Txt*)"Packing failure"); \
      RETVALUE(retVal);
   }
#else
   CMCHKUNPKLOG(cmUnpkCmIpHdrParm, &ipHdrParm, mBuf, EHIT128, pst);
#endif /* IPV6_OPTS_SUPPORTED */  
   
   /* added new unpacking function cmUnpkCmTptLocalInf */
#ifdef LOCAL_INTF
   /* init structure to all 0 */
   cmMemset((U8 *)&localIf, 0, sizeof(localIf));
   CMCHKUNPKLOG(cmUnpkCmTptLocalInf, &localIf, mBuf, EHIT129, pst);
#endif /* LOCAL_INTF */   
   
   /* call the primitive */
   /* pass new unpacked localIf */
#ifdef LOCAL_INTF  
   (*func)(pst, suId, suConId, &srcAddr, &destAddr, &ipHdrParm, &localIf, mBuf);
#else 
   (*func)(pst, suId, suConId, &srcAddr, &destAddr, &ipHdrParm, mBuf);
#endif /* LOCAL_INTF */ 

   RETVALUE(ROK);
} /* end of cmUnpkHitUDatInd */


/*
*
*       Fun:   cmUnpkHitDiscReq
*
*       Desc:  Unpack Disconnect Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkHitDiscReq
(
HitDiscReq func,
Pst    *pst,               /* post structure */
Buffer *mBuf               /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitDiscReq(func, pst, mBuf)
HitDiscReq func;
Pst    *pst;               /* post structure */
Buffer *mBuf;              /* message buffer */
#endif
{
   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SpId   spId = 0;                 /* service provider id */
   U8 choice;               /* choice of user or provider connection id */
   UConnId conId = 0;           /* connection id */
   Action action = 0;           /* action to be performed */
   CmTptParam   tPar;       /* transport parameters */  

   TRC3(cmUnpkHitDiscReq)

   /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSpId,       &spId,   mBuf, EHIT130, pst);
   CMCHKUNPKLOG(SUnpkU8,         &choice, mBuf, EHIT131, pst);
   CMCHKUNPKLOG(cmUnpkUConnId,     &conId,  mBuf, EHIT132, pst);
   CMCHKUNPKLOG(cmUnpkAction,     &action, mBuf, EHIT133, pst);
   CMCHKUNPKLOG(cmUnpkCmTptParam, &tPar,   mBuf, EHIT134, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func)(pst, spId, choice, conId, action, &tPar);
   RETVALUE(ROK);
} /* end of cmUnpkHitDiscReq */


/*
*
*       Fun:   Un pack - Disconnect Indication
*
*       Desc:  This function is used to pack Disconnect Indication 
*              primitive.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkHitDiscInd
(
HitDiscInd func,          /* function */
Pst *pst,                 /* post stucture */
Buffer   *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitDiscInd(func, pst, mBuf)
HitDiscInd func;          /* function */
Pst *pst;                 /* post stucture */
Buffer   *mBuf;           /* message buffer */
#endif
{
   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SuId   suId = 0;             /* service User Id */
   U8  choice;            /* choice parameter */
   UConnId conId = 0;         /* connection Id */
   Reason reason = 0;         /* reason */

   TRC3(cmUnpkHitDiscInd)
   
   CMCHKUNPKLOG(cmUnpkSuId,   &suId,    mBuf, EHIT135, pst);
   CMCHKUNPKLOG(SUnpkU8,      &choice,  mBuf, EHIT136, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &conId,   mBuf, EHIT137, pst);
   CMCHKUNPKLOG(cmUnpkReason, &reason,  mBuf, EHIT138, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func)(pst, suId, choice, conId, reason);
   RETVALUE(ROK);
} /* end of cmUnpkHitDiscInd */


/*
*
*       Fun:   Un pack - Disconnect Confirmation
*
*       Desc:  This function is used to pack Disconnect Confirm
*              primitive.
*
*       Ret:   ROK
*
*       Notes: < none > 
* 
*       File:  hit.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkHitDiscCfm
(
HitDiscCfm func,          /* function */
Pst *pst,                 /* post stucture */
Buffer   *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitDiscCfm(func, pst, mBuf)
HitDiscCfm func;          /* function */
Pst *pst;                 /* post stucture */
Buffer   *mBuf;           /* message buffer */
#endif
{

   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SuId   suId = 0;             /* service User Id */
   U8  choice;            /* choice parameter */
   UConnId conId = 0;         /* connection Id */
   Action action = 0;           /* action to be performed */

   TRC3(cmUnpkHitDiscCfm)
   
   CMCHKUNPKLOG(cmUnpkSuId,   &suId,   mBuf, EHIT139, pst);
   CMCHKUNPKLOG(SUnpkU8,      &choice, mBuf, EHIT140, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &conId,  mBuf, EHIT141, pst);
   CMCHKUNPKLOG(cmUnpkAction, &action, mBuf, EHIT142, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func)(pst, suId, choice, conId, action);
   RETVALUE(ROK);
} /* end of cmUnpkHitDiscCfm */


/*
*
*       Fun:   Un pack - Flow Control Indication 
*
*       Desc:  This function is used to pack Flow Control 
*              Indication primitive.
*
*       Ret:   ROK
*
*       Notes: < none > 
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkHitFlcInd 
(
HitFlcInd   func,         /* function */
Pst         *pst,         /* post structure */
Buffer      *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitFlcInd(func, pst, mBuf)
HitFlcInd   func;         /* function */
Pst         *pst;         /* post structure */
Buffer      *mBuf;        /* message buffer */
#endif
{

   /* hit_c_001.main_15: Fix for Klockworks issue*/
   SuId   suId = 0;             /* service User Id */
   Reason      reason = 0;    /* reason for flow control */
   UConnId     suConId = 0;   /* Service User Connection Id */

   TRC3(cmUnpkHitFlcInd)

   CMCHKUNPKLOG(cmUnpkSuId,   &suId,    mBuf, EHIT143, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suConId, mBuf, EHIT144, pst);
   CMCHKUNPKLOG(cmUnpkReason, &reason,  mBuf, EHIT145, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func)(pst, suId, suConId, reason);

   RETVALUE(ROK);
} /* end of cmUnpkHitFlcInd */

#ifdef HIT_MPLS
/*
*
*       Fun:   cmUnpkHitPduLenRngReq
*
*       Desc:  Unpack Pdu Length Range Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkHitPduLenRngReq
(
HitPduLenRngReq func,
Pst               *pst,  /* post structure */
Buffer            *mBuf  /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitPduLenRngReq (func, pst, mBuf)
HitPduLenRngReq func;
Pst               *pst;  /* post structure */
Buffer            *mBuf; /* message buffer */
#endif
{
   SpId      spId;     /* service provider id   */ 
   UConnId   spConId;  /* service provider's connection id */ 
   U32       minLen;   /* minimum length of PDU */ 
   U32       maxLen;   /* maximum length of PDU */

   TRC3(cmUnpkHitPduLenRngReq)
   
   /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSpId,       &spId,      mBuf, EHIT146, pst);
   CMCHKUNPKLOG(cmUnpkUConnId,    &spConId,   mBuf, EHIT147, pst);
   CMCHKUNPKLOG(SUnpkU32,         &minLen,    mBuf, EHIT148, pst);
   CMCHKUNPKLOG(SUnpkU32,         &maxLen,    mBuf, EHIT149, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func) (pst, spId, spConId, minLen, maxLen);

   RETVALUE (ROK);

} /* end of cmUnpkHitPduLenRngReq */

#endif /* HIT_MPLS */

/* hit_c_001.main_14 :         Added the following packing/unpacking functions 
                               cmPkHitTlsEstReq and cmUnpkHitTlsEstReq. */
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
/*
*
*       Fun:   cmUnpkHitTlsEstReq
*
*       Desc:  Unpack Tls establishment Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkHitTlsEstReq
(
HitTlsEstReq func,
Pst    *pst,                    /* post structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitTlsEstReq(func, pst, mBuf)
HitTlsEstReq func;
Pst    *pst;                    /* post structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
  
   SpId   spId;               /* service provider id */
   UConnId spConId;           /* service provider connection id */
   S16 ctxId;                 /* Context Id */ 
   U8 nodeType;               /* node type */

   TRC3(cmUnpkHitTlsEstReq)

   /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSpId,       &spId,      mBuf, EHIT150, pst);
   CMCHKUNPKLOG(cmUnpkUConnId,    &spConId,   mBuf, EHIT151, pst);
   CMCHKUNPKLOG(SUnpkS16,         &ctxId,     mBuf, EHIT152, pst);
   CMCHKUNPKLOG(SUnpkU8,          &nodeType,  mBuf, EHIT153, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func)(pst, spId, spConId, ctxId, nodeType);

   RETVALUE(ROK);

} /* end of cmUnpkHitTlsEstReq */

/*
*
*       Fun:   cmUnpkHitTlsEstCfm
*
*       Desc:  Unpack Tls Establishment confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hit.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkHitTlsEstCfm
(
HitTlsEstCfm func,                 /* function */
Pst    *pst,                    /* post structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 cmUnpkHitTlsEstCfm(func, pst, mBuf)
HitTlsEstCfm func;                 /* function */
Pst    *pst;                    /* post structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   SuId suId;                /* service user id */ 
   UConnId suConId;          /* service user's connection id */ 
   Reason reason;            /* reason*/
   U8 status;                /* status*/

   TRC3(cmUnpkHitTlsEstCfm)

    /* unpack parameters */
   CMCHKUNPKLOG(cmUnpkSuId,    &suId,    mBuf, EHIT154, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suConId, mBuf, EHIT155, pst);
   CMCHKUNPKLOG(SUnpkU8,       &status,  mBuf, EHIT156, pst);
   CMCHKUNPKLOG(cmUnpkReason,  &reason,  mBuf, EHIT157, pst);

   /* release the message buffer */
   (Void)SPutMsg(mBuf);

   /* call the primitive */
   (*func)(pst, suId, suConId, status, reason);

   RETVALUE(ROK);  

}/*cmUnpkHitTlsEstCfm */

#endif /* HI_TCP_TLS */
#endif /* HI_TLS */
#endif /* HITV2 */

#endif /* LCHIT */


/********************************************************************30**
 
         End of file:     hit.c@@/main/17 - Tue Apr 26 19:06:43 2011

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
----------- -------- ---- -----------------------------------------------
 1.1           ---    asa  1. initial release.
 1.1+       hi002.11  asa  1. added spConId to HitUDatReq primitive.
                           2. fixed a bug in cmUnpkHitFlcInd()
 /main/5                cvp  1. changed the copyright header.
             /main/7                 sb   1. changes in packing/unpacking routines of 
                              HiUiHitServOpenReq & HiUiHitUDatInd for Raw 
                              socket interface.
                           2. flag added for backward compatibility.   
/main/8      ---      sb   1. cm_gen.h not included any more.
/main/9      ---      cvp  1. Changes for packing/unpacking transport 
                              parameters in UDatReq.
                           2. changed the copyright header.
/main/10     ---      mmh  1. added new arg localIf in following functions - 
                              cmPkHitDatInd, cmPkHitUDatInd.
                           2. added new packing function cmPkCmTptLocalInf.
                           3. added new unpacking function cmUnpkCmTptLocalInf
                           4. calling new macro CM_TPT_FREE_IPV6_HDRPARM
                              in func cmPkHitUDatReq, cmPkHitUDatInd to 
                              free mem for ipHdrParm
                           5. added new arg *memInfo in func cmUnpkHitUDatReq
                           6. pass memInfo to cmUnpkCmIpHdrParm and 
                              cmUnpkHitUDatInd function.
                           7. included new hdr file cm_lib.x
/main/11     ---      cv309 1. Added MPLS 1.2 changes
/main/12     ---      ms   1. SIP release 2.1 changes
/main/13     ---      kp   1. Updated for TUCL release 1.5.
/main/14     ---      jc   1. Corrected packing/unpacking macro names.
hit_c_001.main_14     svp  1. Added the following packing/unpacking functions 
                              cmPkHitTlsEstReq and cmUnpkHitTlsEstReq.
/main/15  hit_c_001.main_15 ragrawal 1. Fix for Klockworks issue.
/main/16  hit_c_001.main_16 ragrawal 1. Fix for g++ compilation warning.
*********************************************************************91*/
