
/********************************************************************20**
  
     Name:     e-GTP utility API definition
  
     Type:     C source file
  
     Desc:     Definitions of the utility API
  
     File:     eg_util.c
  
     Sid:      eg_util.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:53 2015
  
     Prg:      kc
  
*********************************************************************21*/

/************************************************************************
 * H E A D E R     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System Services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_hash.h"       /* common structs 1 */
#include "cm_mblk.h"       /* common memory */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common structs 3 */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport */

#include "cm_dns.h"        /* common transport */
#include "hit.h"           /* TUCL Layer */
#include "leg.h"           /* eGTP Layer */
#include "eg.h"            /* eGTP Layer */
#include "eg_err.h"        /* eGTP Error Codes */
/* eg004.201 eGTPC PSF header files included*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "sht.h"
#endif
#include "egt.h"           /* GTP Upper Interface */
#include "eg_util.h"       /* GTP utilities header */
#include "eg_err.h"        /* Error codes */
#include "eg_edm.h"        /* Error codes */

/************************************************************************
 * E X T E R N     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common structs 3 */
#include "cm_inet.x"       /* common transport */
#include "cm_tpt.x"        /* common transport */
#include "cm_dns.x"        /* common transport */
#include "hit.x"           /* TUCL Layer */
#include "egt.x"           /* GTP Upper Interface */
#include "leg.x"           /* eGTP layer */
#include "eg_edm.x"        /* EDM Module structures            */
/* eg004.201 eGTPC PSF header files included*/
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#endif
#include "eg.x"           /* eGTP layer */
#include "eg_tpt.x"            /* EGTP TPT module defines */
#include "eg_util.x"       /* GTP Utility library */

/* eg004.201 eGTPC PSF header files included*/
#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC UA                       */
#endif

/********************************************************************
 * L O C A L     D E F I N E S                                      *
 *******************************************************************/

/********************************************************************
 * L O C A L     E X T E R N S                                      *
 *******************************************************************/

/********************************************************************
 * L O C A L     V A R I A B L E    D E C L A R A T I O N S         *
 *******************************************************************/

#ifdef __cplusplus
EXTERN "C" {
#endif


#ifdef EGTP_U

/********************************************************************
 * L O C A L     F U N C T I O N    D E C L A R A T I O N S        *
 *******************************************************************/

#ifdef EG_FILE_LOG
/**************************************
 * This method is used to GTPU Hdr    *
 **************************************/
PRIVATE S16 egUUtilDumpGmHdr ARGS (( EgUMsgHdr egGmHdr, FILE *fp,U16 *nmbLines));

/*******************************************
 * This method is used to dump the IE List *
 *******************************************/
PRIVATE S16 egUUtilDumpList ARGS (( CmLListCp *ieList, FILE *fp, U16 *nmbLines));

/**************************************
 * This method is used to dump the IE *
 **************************************/
PRIVATE S16 egUUtilDumpIe ARGS (( EgUIe *egIe,FILE *fp, U16 *nmbLines ));

#else
/**************************************
 * This method is used to GTPU Hdr    *
 **************************************/
PRIVATE S16 egUUtilDumpGmHdr ARGS (( EgUMsgHdr egGmHdr ));

/*******************************************
 * This method is used to dump the IE List *
 *******************************************/
PRIVATE S16 egUUtilDumpList ARGS (( CmLListCp *ieList ));

/**************************************
 * This method is used to dump the IE *
 **************************************/
PRIVATE S16 egUUtilDumpIe ARGS (( EgUIe *egIe ));

#endif

/********************************************
 * This method is used to get the target IE *
 ********************************************/
/* ccpu00136421:purecov fix:unused function */
#if 0
PRIVATE S16 egUUtilGetTrgtIe ARGS (( CmLListCp  *ieList, U8 ieType, 
                                     U8 occrCnt, EgUIe **egIe ));
#endif

/******************************************
 * This method is used to duplicate an IE *
 ******************************************/
PRIVATE S16 egUUtilDupIe ARGS ((CmMemListCp *memCp, EgUIe *oldIe, EgUIe **dupIe ));


#ifdef EG_PRNT_DATA
/***************************************************
 Utility functions for dumping ipv4 / ipv6 address *
 ***************************************************/
PRIVATE S16 egUUtilDumpIpAddr ARGS ((Txt *buff, EgUIpAddr *ipAddr));
#endif

#endif /* End of EGTP_U */

#ifdef __cplusplus
} /* end of EXTERN "C" */
#endif /* end of __cplusplus */



#ifdef EG_MULTI_IP
/**********************************************************************
*       Fun:  egTptGetTsapFrmAddr
*
*       Desc: This function is used to obtain TSapCb from a given IP addr
*
*       Ret:   ROK   on success
*              EGT_ERR_MSG_INVOVR_LEN_PBMSG on error
*
*       Notes: --
*              
*       File:  eg_tpt.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egTptGetTsapFrmAddr
(
 CmTptAddr   tptSrvAddr,                  /* Server Address --*/
 EgTSapCb**   tSapCb
)
#else
PUBLIC EgTSapCb* egTptGetTsapFrmAddr(tptSrvAddr, tSapCb)
 CmTptAddr   tptSrvAddr;                  /* Server Address  --*/
 EgTSapCb**   tSapCb;
#endif
{
   CmTptAddr   *localAddrPtr = NULLP;     /* Ptr to Local Address */
   Bool         addrMatch    = FALSE;
   U16          idx;

   for (idx = 0;idx < egCb.genCfg.maxNmbTSaps;idx++)
   {
      *tSapCb = egCb.tSapLst[idx]; 
      if ((*tSapCb) == NULL)
         continue;

      localAddrPtr= &(*tSapCb)->tSapIpAddr;

      egCmpTptAddr(localAddrPtr, &tptSrvAddr, &addrMatch);
      if (addrMatch )
      {
         /*-- Retrun TSapCb if the match is found --*/
         RETVALUE (ROK);
      }
   }

   EG_DBG_INFO(0,0, (egp, "\n TSapCb not found"));
   RETVALUE (RFAILED);
} /*egTptGetTsapFrmAddr*/
#endif /* EG_MULTI_IP */




#ifdef EGTP_U
/* 
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUUCmpTptAddr 
 *
 *  Description:  
 *
 *       Return:
 *
 * *****************************************************************************
 */
#ifdef ANSI
PUBLIC S16 egUUtilCmpTptAddr
(
CmTptAddr *srcAddr,
CmTptAddr *destAddr,
U16 *port
)
#else
PUBLIC S16 egUUtilCmpTptAddr(srcAddr, destAddr, port)
CmTptAddr *srcAddr;
CmTptAddr *destAddr;
U16 *port;
#endif
{
#ifdef IPV6_SUPPORTED
   S16 retVal = 0;
#endif

   if (srcAddr->type != destAddr->type)
   {
      RETVALUE (RFAILED);
   }

   if ((srcAddr->type != CM_TPTADDR_IPV4) && (srcAddr->type != CM_TPTADDR_IPV6))
   {
      RETVALUE (RFAILED);
   }

   if (srcAddr->type == CM_TPTADDR_IPV4)
   {
      if (srcAddr->u.ipv4TptAddr.address ^ destAddr->u.ipv4TptAddr.address)
         RETVALUE(RFAILED);
      else
         *port = destAddr->u.ipv4TptAddr.port;
   }
#ifdef IPV6_SUPPORTED
   else if (srcAddr->type == CM_TPTADDR_IPV6)
   {
      if ((retVal = cmMemcmp (srcAddr->u.ipv6TptAddr.ipv6NetAddr,
                              destAddr->u.ipv6TptAddr.ipv6NetAddr,
                              sizeof (CmIpv6NetAddr))))
         RETVALUE(retVal);
      else
         *port = destAddr->u.ipv6TptAddr.port;
   }
#endif

   RETVALUE(ROK);
}

/***********************************************************************************
 *
 *    Fun:    EgUUtilAllocGmMsg
 *
 *    Desc:   Allocate memory for the GTP-U message and initialize
 *
 *    Ret:    ROK  - if memory allocation and initialization is success
 *            EG_UTIL_ERR_MEM_ALLOC_FAILED - in case of memory allocation fails
 *            EG_UTIL_ERR_INV_PARAM - if the given message is invalid
 *
 *    Notes:  None
 *
 *    File:   eg_util.c
 *
 *************************************************************************************/
#ifdef ANSI
PUBLIC S16 EgUUtilAllocGmMsg
(
   EgUMsg **egMsg,    /* GTP-U Message */
   Mem    *memInfo    /* memory information */
 )
#else
PUBLIC S16 EgUUtilAllocGmMsg(egMsg, memInfo)
   EgUMsg **egMsg;    /* GTP-U Message */
   Mem    *memInfo;   /* memory information */
#endif
{
   /*-- eg002.201 : eg006.102 changes --*/
   EG_TRC2(EgUUtilAllocGmMsg) 

   /************************************************* 
    * eg009.201: Removed ERRCHK, as its supposed to *
    * suppress Error Logs, not Pointers checks.     *
    *************************************************/

   /****************
    * sanity check *
    ****************/
   if (!egMsg)
   {
      RETVALUE(EG_UTIL_ERR_INV_PARAM);
   }

   /******************************************************
    * allocate memory for the GTP-U message of size EgUMsg *
    ******************************************************/
   if (cmAllocEvnt(sizeof(EgUMsg), EG_UTIL_MEM_SIZE, memInfo, (Ptr* )egMsg) != ROK)
   {
      EGUTILLOGERROR(ERRCLS_DEBUG, EEG062, ERRZERO,
            "EgUUtilAllocGmMsg: Allocating memory for the GTP-U Message failed.\n");
      RETVALUE(EG_UTIL_ERR_MEM_ALLOC_FAILED);
   }

   /******************
    * return success *
    ******************/
   RETVALUE(ROK);
}

/***********************************************************************************
 *
 *    Fun:    EgUUtilDeAllocGmMsg
 *
 *    Desc:   De-Allocate memory for the GTP-U message and uninitialize
 *
 *    Ret:    ROK  - if memory de-allocation and initialization is success
 *            RFAILED - in case of memory de-allocation fails
 *            EG_UTIL_ERR_INV_PARAM - if the given message is invalid
 *            Return value of the child methods (if any)
 *
 *    Notes:  The GTP-U message will be destoryed in this method.  The
 *            memory allocated either for the message or for all the IEs
 *            inside the message (of any level) will be deallocated inside
 *            this method.
 *
 *    File:   eg_util.c
 *
 ***********************************************************************************/
#ifdef ANSI
PUBLIC S16 EgUUtilDeAllocGmMsg
(
   EgUMsg **egMsg     /* GTP-U Message */
 )
#else
PUBLIC S16 EgUUtilDeAllocGmMsg(egMsg)
   EgUMsg **egMsg;    /* GTP-U Message */
#endif
{
   EgUIe   *ie = NULLP;    /* temporary ie to hold the element in the list */
   CmLList *node = NULLP;  /* temporary node to walk through the list */

   /*-- eg002.201 : eg006.102 changes --*/
   EG_TRC2(EgUUtilDeAllocGmMsg) 

   /************************************************* 
    * eg009.201: Removed ERRCHK, as its supposed to *
    * suppress Error Logs, not Pointers checks.     *
    *************************************************/

   if (!egMsg || !(*egMsg))
   {
      RETVALUE(EG_UTIL_ERR_INV_PARAM);
   }

   if((*egMsg)->msgHdr.msgType != EGT_GTPU_MSG_GPDU)
   {
      /***************************************************************
       * In a loop iterate through the list and then delete the node * 
       ***************************************************************/
      for (ie = (EgUIe* )CM_LLIST_FIRST_NODE(&(*egMsg)->u.egIeList, node); ie != NULLP;
            ie = (EgUIe* )CM_LLIST_NEXT_NODE(&(*egMsg)->u.egIeList, node))
      {
         /*********************************
          * delete the node from the list *
          *********************************/
         if (!cmLListDelFrm(&(*egMsg)->u.egIeList, node))
         {
            EGUTILLOGERROR(ERRCLS_DEBUG, EEG063, ERRZERO,
                  "EgUUtilDeAllocGmMsg: Deleting IE has failed....\
                  continuing with dropping the message.\n");
            break;
         }
      }
   }
   else
   {
      if((*egMsg)->u.mBuf)
      {
         SPutMsg((*egMsg)->u.mBuf);
      }
   }

   /*****************************************
    * De-allocate memory of the gtp message *
    *****************************************/
   cmFreeMem(&(*egMsg)->memCp);

   /************************************
    * Initialize the pointer with zero *
    ************************************/
   *egMsg = NULLP;

   RETVALUE(ROK);
}

/****************************************************************************************
 *
 *    Fun:    EgUUtilGmAppendIe
 *
 *    Desc:   Method is used to append an IE to the GTP-Umessage
 *
 *    Ret:    ROK - if the IE is appended successfully
 *            RFAILED - if appending IE fails
 *            EG_UTIL_ERR_MEM_ALLOC_FAILED - if memory allocation for the new IE fails
 *            EG_UTIL_ERR_INV_PARAM - if the given message or ie are invalid
 *            Return value of the child method (if any)
 *
 *    Notes:  This method will allocate memory separately for the new IE that is
 *            being inserted
 *
 *    File:   eg_util.c
 *
 *****************************************************************************************/
#ifdef ANSI
PUBLIC S16 EgUUtilGmAppendIe
(
   EgUMsg   *egMsg,        /* GTP-U message */
   EgUIe    *egIe          /* IE that has to be appended */
 )
#else
PUBLIC S16 EgUUtilGmAppendIe(egMsg, egIe)
   EgUMsg   *egMsg;        /* GTP-U message */
   EgUIe    *egIe;         /* IE that has to be appended */
#endif
{
   S16   retValue = ROK;   /* to hold the return value of sub methods */       
   EgUIe *ie = NULLP;      /* ie that has to be appended to the list */

   /*-- eg002.201 : eg006.102 changes --*/
   EG_TRC2(EgUUtilGmAppendIe) 

   /************************************************* 
    * eg009.201: Removed ERRCHK, as its supposed to *
    * suppress Error Logs, not Pointers checks.     *
    *************************************************/

   /****************
    * sanity check *
    ****************/
   if (!egMsg || !egIe)
   {
      RETVALUE(EG_UTIL_ERR_INV_PARAM);
   }

   /***********************************************************
    * make the new copy of the given IE to append to the list *
    ***********************************************************/
   if ( (retValue = egUUtilDupIe(&egMsg->memCp, egIe, &ie)) != ROK)
   {
      EGUTILLOGERROR(ERRCLS_DEBUG, EEG064, ERRZERO,
            "EgUUtilGmAppendIe: Making the new IE from the given IE failed.\n");
      RETVALUE(retValue);
   }

   /*****************************************
    * append the IE to the tail of the list *
    *****************************************/
   cmLListAdd2Tail(&egMsg->u.egIeList, &ie->node);

   RETVALUE(retValue);
}
/* ccpu00136421:purecov fix:unused function */
#if 0
/********************************************************************************************
 *
 *    Fun:    egUUtilGetTrgtIe
 *
 *    Desc:   This is used to get a particular IE from an IE list
 *
 *    Ret:    ROK - if the IE in IE is found successfully
 *            RFAILED -  if finding the IE in IE list fails
 *            EG_UTIL_ERR_INV_PARAM - if the given ielist or ie info or target ie are invalid
 *
 *    Notes:  n/a
 *
 *    File:   eg_util.c
 *
 ***********************************************************************************************/
#ifdef ANSI
PRIVATE S16 egUUtilGetTrgtIe
(
   CmLListCp  *ieList,       /* IE list from where to retreive the IE */
   U8       ieType,        /* Type of the IT tobe retreived */
   U8       occrCnt,       /* Occurance of the IE */
   EgUIe      **egIe        /* target IE */
)
#else
PRIVATE S16 egUUtilGetTrgtIe(ieList, ieType, occrCnt, egIe)
   CmLListCp   *ieList;      /* IE list from where to retreive the IE */
   U8        ieType;       /* Type of the IT tobe retreived */
   U8        occrCnt;      /* Occurance of the IE */
   EgUIe       **egIe;       /* target IE */
#endif
{
   U16      cnt = 0;          /* used to hold the occurrence count */
   CmLList  *node = NULLP;    /* used to hold the temporary node address */

   /*-- eg002.201 : eg006.102 changes --*/
   EG_TRC2(egUUtilGetTrgtIe) 

   /************************************************* 
    * eg009.201: Removed ERRCHK, as its supposed to *
    * suppress Error Logs, not Pointers checks.     *
    *************************************************/

   /****************
    * sanity check *
    ****************/
   if (!ieList || !occrCnt || (occrCnt > ieList->count))
   {
      RETVALUE(EG_UTIL_ERR_INV_PARAM);
   }

   /***************************************** 
    * iterate through the list and for each *
    * node increment the iePos value        *
    *****************************************/
   for (*egIe = (EgUIe* ) CM_LLIST_FIRST_NODE(ieList, node); (*egIe != NULLP);
         *egIe = (EgUIe* ) CM_LLIST_NEXT_NODE(ieList, node))
   {
      /**************************************************
       * if the IE type is matching, then increment cnt *
       **************************************************/
      if ((*egIe)->ieType == ieType)
      {
         cnt++;
         /********************************
          * occurrence count is matching *
          ********************************/
         if (cnt == occrCnt)
         {
            RETVALUE(ROK);
         }
      }

   }

   EGUTILLOGERROR(ERRCLS_DEBUG, EEG065, ERRZERO,
         "egUUtilGetTrgtIe: Targer IE is not found.\n");
   RETVALUE(EG_UTIL_ERR_INV_LEVEL_INFO);
}
#endif /* if 0 */

/*******************************************************************************************
 *
 *    Fun:    egUUtilDupIe
 *
 *    Desc:   Method is used to duplicate a GTP-U ie
 *
 *    Ret:    ROK - if the ie list is duplicated successfully
 *            EG_UTIL_ERR_MEM_ALLOC_FAILED - if memory allocation for the new ie fails
 *            EG_UTIL_ERR_INV_PARAM - if the given message or memory information are invalid
 *
 *    Notes:  N/A
 *
 *    File:   eg_util.c
 *
 *******************************************************************************************/
#ifdef ANSI
PRIVATE S16 egUUtilDupIe
(
   CmMemListCp    *memCp,          /* memory information */
   EgUIe          *oldIe,          /* original ie list */
   EgUIe          **dupIe          /* duplicated ie list */
 )
#else
PRIVATE S16 egUUtilDupIe(memCp, oldIe, dupIe)
   CmMemListCp    *memCp;          /* memory information */
   EgUIe          *oldIe;          /* original ie list */
   EgUIe          **dupIe;         /* duplicated ie list */
#endif
{
   PTR length = 0;                 /* to store the length of the IE */
   /*-- eg002.201 : eg006.102 changes --*/
   EG_TRC2(egUUtilDupIe) 

   /************************************************* 
    * eg009.201: Removed ERRCHK, as its supposed to *
    * suppress Error Logs, not Pointers checks.     *
    *************************************************/

   /****************
    * sanity check *
    ****************/
   if (!oldIe || !dupIe || !memCp)
   {
      RETVALUE(EG_UTIL_ERR_INV_PARAM);
   }

   /**************************************
    * Take the size of the IE to length  *
    **************************************/
   length = sizeof(EgUIe);

   /**********************************************************
    * allocate memory for the ie and then the local ie will  *
    * be appended to the list                                *
    **********************************************************/
   if (cmGetMem(memCp, length, (Ptr* )dupIe) != ROK)
   {
      EGUTILLOGERROR(ERRCLS_DEBUG, EEG066, ERRZERO,
            "egUUtilDupIe: Allocating the memory for the IE failed.\n");
      RETVALUE(EG_UTIL_ERR_MEM_ALLOC_FAILED);
   }

   /*************************************
    * Initialize the elements of new ie *
    *************************************/
   cmMemset( (U8* )(*dupIe), 0, length);

   /***********************
    * Duplicate IE header *
    ***********************/
   ( (EgUIe *)(*dupIe))->ieType = oldIe->ieType;
   ( (EgUIe *)(*dupIe))->dataType = oldIe->dataType;

   /*****************************************
    * Duplicate IE based on the IE datatype *
    *****************************************/
   switch (oldIe->dataType)
   {
      case EG_UNSIGNED_8:
         {
            ( (EgUIe *)(*dupIe))->t.valUnSgnd8 = oldIe->t.valUnSgnd8;
            break;
         }

      case EG_UNSIGNED_32:
         {
            ( (EgUIe *)(*dupIe))->t.valUnSgnd32 = oldIe->t.valUnSgnd32;
            break;
         }

      case EG_PVT_EXTN:
         {
            ( (EgUIe *)(*dupIe))->t.pvtExt.entId = oldIe->t.pvtExt.entId;
            ( (EgUIe *)(*dupIe))->t.pvtExt.propVal.length = oldIe->t.pvtExt.propVal.length;
            cmMemcpy(( (EgUIe *)(*dupIe))->t.pvtExt.propVal.val, 
                  oldIe->t.pvtExt.propVal.val, oldIe->t.pvtExt.propVal.length);
            break;
         }

      case EG_IP_ADDR:
         {
            ((EgUIe *)(*dupIe))->t.ipAddr.addrType = oldIe->t.ipAddr.addrType;

            if(oldIe->t.ipAddr.addrType == EG_IP_V4_TYPE)
            {
               cmMemcpy((U8*)&(((*dupIe))->t.ipAddr.u.ipv4), (U8*)&(oldIe->t.ipAddr.u.ipv4),
                        sizeof(CmIpAddr));
            }
#ifdef EG_IPV6_SUPPORTED
            else if(oldIe->t.ipAddr.addrType == EG_IP_V6_TYPE)
            {
               cmMemcpy((U8*)&(((*dupIe))->t.ipAddr.u.ipv6), (U8*)&(oldIe->t.ipAddr.u.ipv6), 
                        sizeof(CmIpAddr6));
            }
#endif /* EG_IPV6_SUPPORTED */

            break; 
         }

      case EG_EXT_HDR_TYPE_LST:
         {
            U16 cnt = 0;
            ((EgUIe *)(*dupIe))->t.extHdrTypeLst.noOfExtHdrs = oldIe->t.extHdrTypeLst.noOfExtHdrs;
            if(oldIe->t.extHdrTypeLst.noOfExtHdrs <= EGT_U_MAX_EXT_TYPES)
            {
              for (cnt = 0; cnt < oldIe->t.extHdrTypeLst.noOfExtHdrs; cnt++)
              {
                 ((EgUIe *)(*dupIe))->t.extHdrTypeLst.extType[cnt] = 
                    oldIe->t.extHdrTypeLst.extType[cnt];
              }
            }
            break;
         }

      default:
         {
            EGUTILLOGERROR(ERRCLS_DEBUG, EEG067, ERRZERO,
                  "egUUtilDupIe: Ie datatype is not valid.\n");
            RETVALUE(EG_UTIL_ERR_INV_IE_DATATYPE);
         }
   }

   /*********************************************
    * initialize the node address of the new IE *
    *********************************************/
   ( (EgUIe *)(*dupIe))->node.node = (PTR) (*dupIe);

   /******************
    * return success *
    ******************/
   RETVALUE(ROK);
}

/***************************************************************************************
 *
 *    Fun:    EgUUtilGmDump
 *
 *    Desc:   Method is used to dump the GTP-U message on
 *            console / Write to file
 *
 *    Ret:    ROK - if the ie list is duplicated successfully
 *            EG_UTIL_ERR_INV_PARAM - if the given message is invalid
 *
 *    Notes:  N/A
 *
 *    File:   eg_util.c
 *
 ***************************************************************************************/
#ifdef EG_FILE_LOG
#ifdef ANSI
PUBLIC S16 EgUUtilGmDump
(
   EgUMsg      *egMsg,        /* GTP-U message */
   FILE        *fp,           /* file pointer */
   U16         *nmbLines      /* number of lines */
 )
#else
PUBLIC S16 EgUUtilGmDump(egMsg , fp, nmbLines)
   EgUMsg      *egMsg;         /* GTP-U message */
   FILE        *fp;            /* file pointer */
   U16         *nmbLines;      /* number of lines */
#endif
#else 
#ifdef ANSI
PUBLIC S16 EgUUtilGmDump
(
    EgUMsg      *egMsg          /* GTP-U message */
)
#else
PUBLIC S16 EgUUtilGmDump(egMsg)
   EgUMsg      *egMsg;         /* GTP-U message */
#endif
#endif /* EG_FILE_LOG*/
{
   /* this is used to hold the return value of sub methods */
   S16 retValue = 0;

   /*-- eg002.201 : eg006.102 changes --*/
   EG_TRC2(EgUUtilGmDump) 

   /************************************************* 
    * eg009.201: Removed ERRCHK, as its supposed to *
    * suppress Error Logs, not Pointers checks.     *
    *************************************************/

   /****************
    * sanity check *
    ****************/
   if (!egMsg
#ifdef EG_FILE_LOG
         || !fp || !nmbLines
#endif /* end of EG_FILE_LOG */
      )
   {
      RETVALUE(EG_UTIL_ERR_INV_PARAM);
   }

   /*******************************
    * dump the GTP-U message header *
    *******************************/
   if ( (retValue = egUUtilDumpGmHdr(egMsg->msgHdr
#ifdef EG_FILE_LOG
               , fp, nmbLines
#endif /* end of EG_FILE_LOG */
               )) != ROK)
   {
      EGUTILLOGERROR(ERRCLS_DEBUG, EEG068, ERRZERO,
            "EgUUtilGmDump: Dumping the GTP-U header failed.\n");
      RETVALUE(retValue);
   }

   if(egMsg->msgHdr.msgType != EGT_GTPU_MSG_GPDU)
   {
   /********************
    * dump the ie list *
    ********************/
   if ( (retValue = egUUtilDumpList(&egMsg->u.egIeList
#ifdef EG_FILE_LOG
               , fp, nmbLines
#endif /* end of EG_FILE_LOG */
               )) != ROK)
   {
      EGUTILLOGERROR(ERRCLS_DEBUG, EEG069, ERRZERO,
            "EgUUtilGmDump: Dumping the ie list failed.\n");
      RETVALUE(retValue);
   }
   }
   else
   {
      SPrntMsg(egMsg->u.mBuf,0,0);
   }

   /******************
    * return success *
    ******************/
   RETVALUE(ROK);
}

/***************************************************************************************
 *
 *    Fun:    egUUtilDumpGmHdr
 *
 *    Desc:   Method is used to dump the GTP-U header
 *
 *    Ret:    ROK - if the GTP-U header is dumped successfully
 *            EG_UTIL_ERR_INV_PARAM - if the given message is invalid
 *
 *    Notes:  
 *
 *    File:   eg_util.c
 *
 ***************************************************************************************/
#ifdef EG_FILE_LOG
#ifdef ANSI
PRIVATE S16 egUUtilDumpGmHdr
(
   EgUMsgHdr      egGmHdr,   /* GTP header */
   FILE           *fp,       /* file pointer */
   U16            *nmbLines  /* number of lines */
 )
#else
PRIVATE S16 egUUtilDumpGmHdr(egGmHdr , fp, nmbLines)
   EgUMsgHdr      egGmHdr;         /* GTP header */
   FILE           *fp;             /* file pointer */
   U16            *nmbLines;       /* number of lines */
#endif
#else

#ifdef ANSI
PRIVATE S16 egUUtilDumpGmHdr
(
   EgUMsgHdr      egGmHdr          /* GTP header */
)
#else
PRIVATE S16 egUUtilDumpGmHdr(egGmHdr)
   EgUMsgHdr       egGmHdr;         /* GTP header */
#endif

#endif /* EG_FILE_LOG */
{
   Txt buff[EG_UTIL_PRNT_BUFF_SIZE];     /* Temp Buffer for Printing */
   Txt prnBuff[EG_UTIL_PRNT_BUFF_SIZE];  /* Actual Print Buffer */
   Txt newLine[EG_THREE];

   /*-- eg002.201 : eg006.102 changes --*/
   EG_TRC2(egUUtilDumpGmHdr) 

   cmMemset( (U8* )buff, 0, EG_UTIL_PRNT_BUFF_SIZE);
   cmMemset( (U8* )prnBuff, 0, EG_UTIL_PRNT_BUFF_SIZE);
   sprintf(newLine," \n");

   sprintf(buff, "   ********************* GTP-U Message *********************\n");

   /*******************************************
    * Dumping GTP-U Message Header Elements   *
    *******************************************/

   /************************
    * Dumping Message Type *
    ************************/
   sprintf(buff, "  MsgType    = %d\n", egGmHdr.msgType);
   EG_STRCAT(prnBuff, buff);

   /************************
    * Dumping TEID         *
    ************************/
#ifdef ALIGN_64BIT
   sprintf(buff, "  Teid  = %d\n", egGmHdr.teId);
   EG_STRCAT(prnBuff, buff);
#else
   sprintf(buff, "  Teid  = %ld\n", egGmHdr.teId);
   EG_STRCAT(prnBuff, buff);
#endif /* end of  ALIGN_64BIT */

   /****************************************
    * Dumping Sequence Number, if Present  *
    ****************************************/
   if(egGmHdr.seqNumber.pres)
   {
      /*-- eg005.201: Format specifier aligned to 32-bit val of Seq Num --*/
      sprintf(buff, "  Seq No    = %ld\n", egGmHdr.seqNumber.val);
      EG_STRCAT(prnBuff, buff);
   }

   /****************************************
    * Dumping N-PDU Number, if Present     *
    ****************************************/
   if(egGmHdr.nPduNmb.pres)
   {
      sprintf(buff, "  N-PDU Number    = %d\n", egGmHdr.nPduNmb.val);
      EG_STRCAT(prnBuff, buff);
   }

   /***************************************************
    * Dumping Extension Header - UDP Port, if Present *
    ***************************************************/
   if(egGmHdr.extHdr.udpPort.pres)
   {
      sprintf(buff, " Extension Header : UDP Port    = %d\n", egGmHdr.extHdr.udpPort.val);
      EG_STRCAT(prnBuff, buff);
   }

   /***************************************************
    * Dumping Extension Header - PDCP Num, if Present *
    ***************************************************/
   if(egGmHdr.extHdr.pdcpNmb.pres)
   {
      sprintf(buff, " Extension Header : PDCP Number  = %d\n", egGmHdr.extHdr.pdcpNmb.val);
      EG_STRCAT(prnBuff, buff);
   }

#ifdef EG_FILE_LOG
   fprintf(fp, "%s\n", prnBuff);
   nmbLines += 6;
#else
   SPrint(prnBuff);
   SPrint(newLine);
#endif /* end of EG_FILE_LOG */

   /******************
    * return success *
    ******************/
   RETVALUE(ROK);
}

/***************************************************************************************
 *
 *    Fun:    egUUtilDumpList
 *
 *    Desc:   Method is used to dump an ie list
 *
 *    Ret:    ROK - if the ie list is dumped successfully
 *            RFAILED - if the ie list dumping fails
 *            Return value of the child method (if any)
 *
 *    Notes:  
 *
 *    File:   eg_util.c
 *
 ***************************************************************************************/
#ifdef EG_FILE_LOG
#ifdef ANSI
PRIVATE S16 egUUtilDumpList
(
   CmLListCp      *ieList,    /* ie list */
   FILE           *fp,        /* file pointer */
   U16            *nmbLines   /* number of lines */
 )
#else
PRIVATE S16 egUUtilDumpList(ieList, fp, nmbLines)
   CmLListCp      *ieList;          /* ie list */
   FILE           *fp;              /* file pointer */
   U16            *nmbLines;        /* number of lines */
#endif

#else

#ifdef ANSI
PRIVATE S16 egUUtilDumpList
(
   CmLListCp      *ieList          /* ie list */
)
#else
PRIVATE S16 egUUtilDumpList(ieList)
   CmLListCp      *ieList;          /* ie list */
#endif

#endif /* EG_FILE_LOG */
{
   EgUIe *egIe = NULLP;          /* to hold the address of IE in the original list */
   S16 retValue = 0;              /* to hold the return value of sub methods */
   CmLList *node = NULLP;         /* to hold the temporary node address */

   /************************
    * to hold print buffer *
    ************************/
   Txt buff[EG_UTIL_PRNT_BUFF_SIZE];
   Txt prnBuff[EG_UTIL_PRNT_BUFF_SIZE];
   Txt newLine[EG_THREE];

   /*-- eg002.201 : eg006.102 changes --*/
   EG_TRC2(egUUtilDumpList) 

   /************************************************* 
    * eg009.201: Removed ERRCHK, as its supposed to *
    * suppress Error Logs, not Pointers checks.     *
    *************************************************/

   /****************
    * sanity check *
    ****************/
   if (!ieList)
   {
      RETVALUE(EG_UTIL_ERR_INV_PARAM);
   }

   cmMemset( (U8* )buff, 0, EG_UTIL_PRNT_BUFF_SIZE);
   cmMemset( (U8* )prnBuff, 0, EG_UTIL_PRNT_BUFF_SIZE);
   sprintf(newLine," \n");

   sprintf(buff, "           ******* IE list *******              \n");
   EG_STRCAT(prnBuff, buff);
#ifdef ALIGN_64BIT
   sprintf(buff, "  count = %d\n", ieList->count);
#else
   sprintf(buff, "  count = %ld\n", ieList->count);
#endif /* end of ALIGN_64BIT */
   EG_STRCAT(prnBuff, buff);

#ifdef EG_FILE_LOG
   fprintf(fp, "%s\n", prnBuff);
   nmbLines += 2;
#else
   SPrint(prnBuff);
   SPrint(newLine);
#endif /* end of EG_FILE_LOG */

   /***********************************************
    * iterate through the list and for each ie,   *
    * call egUUtilDumpIe to dump the IE.           *
    ***********************************************/
   for (egIe = (EgUIe* ) CM_LLIST_FIRST_NODE(ieList, node); egIe != NULLP;
         egIe = (EgUIe* ) CM_LLIST_NEXT_NODE(ieList, node))
   {
      /***************
       * dump the IE *
       ***************/
      if ( (retValue = egUUtilDumpIe(egIe
#ifdef EG_FILE_LOG
                  , fp, nmbLines
#endif /* end of EG_FILE_LOG */
                  )) != ROK)
      {
         EGUTILLOGERROR(ERRCLS_DEBUG, EEG070, ERRZERO,
               "egUUtilDumpList: Dumping the IE failed.\n");
         RETVALUE(retValue);
      }
   }

   /******************
    * return success *
    ******************/
   RETVALUE(ROK);
}

/***************************************************************************************
 *
 *    Fun:    egUUtilDumpIe
 *
 *    Desc:   Method is used to dump the IE
 *
 *    Ret:    ROK - if dumping IE succeeds
 *            RFAILED - if dumping IE fails
 *
 *    Notes:  N/A
 *
 *    File:   eg_util.c
 *
 ***************************************************************************************/
#ifdef EG_FILE_LOG

#ifdef ANSI
PRIVATE S16 egUUtilDumpIe
(
   EgUIe          *egIe,          /* IE that has to be dumped */
   FILE           *fp,            /* file pointer */
   U16            *nmbLines       /* number of lines */
 )
#else
PRIVATE S16 egUUtilDumpIe(egIe, fp, nmbLines)
   EgUIe          *egIe;          /* IE that has to be dumped */
   FILE           *fp;            /* file pointer */
   U16            *nmbLines;      /* number of lines */
#endif

#else
#ifdef ANSI
PRIVATE S16 egUUtilDumpIe
(
   EgUIe           *egIe           /* IE that has to be dumped */
)
#else
PRIVATE S16 egUUtilDumpIe(egIe)
   EgUIe           *egIe;          /* IE that has to be dumped */
#endif

#endif /* EG_FILE_LOG */
{
   Txt buff[EG_UTIL_PRNT_BUFF_SIZE];      /* to hold buffer (Ie data) */
   Txt prnBuff[EG_UTIL_PRNT_BUFF_SIZE];   /* to hold print buffer (Ie header and data)*/  
   Txt tmpBuff[EG_UTIL_PRNT_BUFF_SIZE-5];  /* to avoid the overflow */
   Txt tempBuff[EG_UTIL_PRNT_BUFF_SIZE-5]; /* to avoid the overflow */
   Txt newLine[EG_THREE];

   /*-- eg002.201 : eg006.102 changes --*/
   EG_TRC2(egUUtilDumpIe) 

   /************************************************* 
    * eg009.201: Removed ERRCHK, as its supposed to *
    * suppress Error Logs, not Pointers checks.     *
    *************************************************/

   /****************
    * sanity check *
    ****************/
   if (!egIe)
   {
      RETVALUE(EG_UTIL_ERR_INV_PARAM);
   }

   /*******************************
    * initialize the print buffer *
    *******************************/
   cmMemset( (U8* )buff, 0, EG_UTIL_PRNT_BUFF_SIZE);
   cmMemset( (U8* )prnBuff, 0, EG_UTIL_PRNT_BUFF_SIZE);
   cmMemset( (U8* )tmpBuff, 0, EG_UTIL_PRNT_BUFF_SIZE-5);
   cmMemset( (U8* )tempBuff, 0, EG_UTIL_PRNT_BUFF_SIZE-5);
   sprintf(newLine," \n");

   /*********************
    * Dumping IE header *
    *********************/
   sprintf(buff, "  ******* IE dump (%p) ********\n", (Ptr)egIe);
   EG_STRCAT(prnBuff, buff);
   sprintf(buff, "  IeType  = %d\n", egIe->ieType);
   EG_STRCAT(prnBuff, buff);
   sprintf(buff, "  IeDatatype = %d\n", egIe->dataType);
   EG_STRCAT(prnBuff, buff);

   EG_STRCAT(prnBuff, "\n");

#ifdef EG_PRNT_DATA
   cmMemset( (U8* )buff, 0, EG_UTIL_PRNT_BUFF_SIZE);
   /****************************
    * check the type of the IE *
    ****************************/
   switch(egIe->dataType)
   {
      case EG_UNSIGNED_8: 
         {
            sprintf(buff, "  value = %d\n",egIe->t.valUnSgnd8);
            break;
         }

      case EG_UNSIGNED_32: 
         {
#ifdef ALIGN_64BIT
            sprintf(buff, "  value = %d\n",egIe->t.valUnSgnd32);
#else
            sprintf(buff, "  value = %ld\n",egIe->t.valUnSgnd32);
#endif
            break;
         }

      case EG_PVT_EXTN:
         {
            sprintf(buff,"  entId: %d\n", egIe->t.pvtExt.entId);  

            sprintf(tmpBuff,"  propVal.length: %d\n", egIe->t.pvtExt.propVal.length);  
            EG_STRCAT(buff,tmpBuff);

            cmMemcpy( (U8* )tempBuff, egIe->t.pvtExt.propVal.val, egIe->t.pvtExt.propVal.length+1);
            sprintf(tmpBuff,"  propVal.val: %s\n", tempBuff);  
            EG_STRCAT(buff,tmpBuff);
            break; 
         }

      case EG_IP_ADDR:
         {
            sprintf(buff,"  addrType: %d\n", egIe->t.ipAddr.addrType);  
            egUUtilDumpIpAddr(buff,&egIe->t.ipAddr);
            break; 
         }

      case EG_EXT_HDR_TYPE_LST:
         {
            U16 loopCount = 0;
            sprintf(buff,"  no. of Ext Headers: %d\n", egIe->t.extHdrTypeLst.noOfExtHdrs);  

            for(loopCount=0; loopCount <  egIe->t.extHdrTypeLst.noOfExtHdrs; loopCount++)
            {
               sprintf(tmpBuff,"  Ext Header Type%d : %d\n", (loopCount+1), 
                     egIe->t.extHdrTypeLst.extType[loopCount]);  
               EG_STRCAT(buff,tmpBuff);
            }

            break;
         } 

      default:
         {
            EGUTILLOGERROR(ERRCLS_DEBUG, EEG071, ERRZERO,
                  "egUUtilDumpIe: Ie datatype is not valid.\n");
            RETVALUE(EG_UTIL_ERR_INV_IE_DATATYPE);
         }

   }
   EG_STRCAT(prnBuff, buff);
#endif /* EG_PRNT_DATA */

#ifdef EG_FILE_LOG
   fprintf(fp, "%s\n", prnBuff);
   nmbLines += 5;
#else
   SPrint(prnBuff);
   SPrint(newLine);
#endif /* end of EG_FILE_LOG */

   RETVALUE(ROK);
}
/* ccpu00136421:purecov fix:unused function */
#if 0
/************************************************************************************************
 *
 *    Fun:    EgUUtilGmDelIe
 *
 *    Desc:   Method is used to delete an IE from the GTP-U message
 *
 *    Ret:    ROK - if the IE is deleted successfully
 *            RFAILED - if deleting IE fails
 *            EG_UTIL_ERR_INV_LEVEL_INFO - if the given level information is invalid
 *            EG_UTIL_ERR_INV_PARAM - if the given message or Ie Type or Occurance Cnt is invalid
 *            Return value of the child method (if any)
 *
 *    Notes:  
 *
 *    File:   eg_util.c
 *
 ************************************************************************************************/
#ifdef ANSI
PUBLIC S16 EgUUtilGmDelIe
(
   EgUMsg   *egMsg,         /* eGtp message */
   U8       ieType,
   U8       occrCnt
 )
#else
PUBLIC S16 EgUUtilGmDelIe(egMsg, ieType, occrCnt)
   EgUMsg   *egMsg;         /* eGtp message */
   U8       ieType;
   U8       occrCnt;
#endif
{
   S16      retValue = 0;                 /* to hold the return value of sub methods */
   EgUIe    *egIe = NULLP;                /* this will hold the IE node address */

   /*-- eg002.201 : eg006.102 changes --*/
   EG_TRC2(EgUUtilGmDelIe) 

   /************************************************* 
    * eg009.201: Removed ERRCHK, as its supposed to *
    * suppress Error Logs, not Pointers checks.     *
    *************************************************/

   /****************
    * sanity check *
    ****************/
   if (!egMsg || !occrCnt)
   {
      RETVALUE(EG_UTIL_ERR_INV_PARAM);
   }

   /************************************************************
    * get the target IE from the list as per the given IE info *
    ************************************************************/
   if ( (retValue = egUUtilGetTrgtIe(&egMsg->u.egIeList, ieType, occrCnt, &egIe)) != ROK)
   {
      EGUTILLOGERROR(ERRCLS_DEBUG, EEG072, ERRZERO,
            "EgUUtilGmDelIe: Getting the target IE from the message failed.\n");
      RETVALUE(retValue);
   }

   /*********************************
    * delete the node from the list *
    *********************************/
   if (!cmLListDelFrm(&egMsg->u.egIeList, &egIe->node))
   {
      EGUTILLOGERROR(ERRCLS_DEBUG, EEG073, ERRZERO,
            "EgUUtilGmDelIe: Deleting node from the IE list failed.\n");
      RETVALUE(RFAILED);
   }

   /******************
    * return success *
    ******************/
   RETVALUE(ROK);
}
#endif /* if 0 */

/*
*
*    Fun:    EgUUtilGmGetIeOccrCnt
*
*    Desc:   Method is used to get the number of occurrences of an IE
*
*    Ret:    ROK - if the ie list is duplicated successfully
*            EG_UTIL_ERR_INV_PARAM - if the given message or level information are invalid
*
*    Notes:  N/A
*
*    File:   eg_util.c
*
*/
#ifdef ANSI
PUBLIC S16 EgUUtilGmGetIeOccrCnt
(
EgUMsg         *egMsg,       /* GTP-U message */
U8             *ieType,    /* IE Type */
U16            *ieOccrCnt     /* IE count */
)
#else
PUBLIC S16 EgUUtilGmGetIeOccrCnt(egMsg, ieType, ieOccrCnt)
EgUMsg      *egMsg;         /* GTP-U message */
U8             *ieType;    /* IE Type */
U16            *ieOccrCnt;    /* IE count */
#endif
{

	/* eg012.201 : klocwork fix - removed unnecessary variable initializations */
   EgUIe       *egIe; /* this is used to hold the temporary node address */
   CmLList     *node; /* initialize the occrrence count as zero initially */

   /* initialize the occrrence count as zero initially */
   *ieOccrCnt = 0;

   /*-- eg002.201 : eg006.102 changes --*/
   EG_TRC2(EgUUtilGmGetIeOccrCnt)

   /************************************************* 
    * eg009.201: Removed ERRCHK, as its supposed to *
    * suppress Error Logs, not Pointers checks.     *
    *************************************************/

   /* eg012.201 : klocwork fix - sanity check removed, egMsg is always verified in pack/unpack */

   /*****************************************************************
    * Iterate through the list of the IEs and if the IE code        *
    * is matching with the IE given, increment the count given.     *
    *****************************************************************/
      /* iterate through the list */
      for (egIe = (EgUIe* ) CM_LLIST_FIRST_NODE(&egMsg->u.egIeList, node);
           egIe != NULLP;
           egIe = (EgUIe* ) CM_LLIST_NEXT_NODE(&egMsg->u.egIeList, node))
      {
         /* if the IE code is matching, then increment
          * the occrrence count
          */
         if (egIe->ieType == *ieType)
         {
            (*ieOccrCnt)++;
         }
      } 

   RETVALUE(ROK);
} /* end of EgUtilGmGetIeOccrCnt */

#ifdef EG_PRNT_DATA
/***********************************************************************************
*
*    Fun:    egUtilDumpIpv4Addr
*
*    Desc:   Dump IPv4 address
*
*    Ret:    ROK  - if duplication is success
*            EG_UTIL_ERR_INV_PARAM - if the given message is invalid
*
*    Notes:  None
*
*    File:   eg_util.c
*
*************************************************************************************/
#ifdef ANSI
PRIVATE S16 egUUtilDumpIpAddr
(
Txt *buff,    /* To hold print buffer */
EgUIpAddr  *ipAddr  /* Source for dumping */
)
#else
PRIVATE S16 egUUtilDumpIpAddr(buff,ipAddr)
Txt *buff;    /* To hold print buffer */
EgUIpAddr  *ipAddr;    /* Source for dumping */
#endif
{
#ifdef EG_IPV6_SUPPORTED
   U8 idx = 0;
#endif
   Txt tmpBuff[EG_UTIL_PRNT_BUFF_SIZE-5];  /* to avoid the overflow */

   /*-- eg002.201 : eg006.102 changes --*/
   EG_TRC2(egUUtilDumpIpAddr)

   /************************************************* 
    * eg009.201: Removed ERRCHK, as its supposed to *
    * suppress Error Logs, not Pointers checks.     *
    *************************************************/

   /****************
    * sanity check *
    ****************/
   if ((!buff) || (!ipAddr))
   {
      RETVALUE(EG_UTIL_ERR_INV_PARAM);
   }

  /*******************************
   * initialize the print buffer *
   *******************************/
   cmMemset( (U8* )tmpBuff, 0, EG_UTIL_PRNT_BUFF_SIZE-5);

   if(ipAddr->addrType == EG_IP_V4_TYPE)
   {
      sprintf(tmpBuff,"  ipv4Addr:0x %lx \n",ipAddr->u.ipv4);
      EG_STRCAT(buff,tmpBuff);
   }
#ifdef EG_IPV6_SUPPORTED
   else if (ipAddr->addrType == EG_IP_V6_TYPE)
   {
      sprintf(tmpBuff,"  ipv6Addr: ");
      EG_STRCAT(buff,tmpBuff);

      /***************************
       * Copy IP address to buff *
       ***************************/
      for (idx = 0; idx < 16; idx++)
      {
         if(idx == 0)
         {
            sprintf(tmpBuff,"0x %x ", ipAddr->u.ipv6[idx]);  
         }
         else
         {
            sprintf(tmpBuff,"%x ", ipAddr->u.ipv6[idx]); 
         }
         EG_STRCAT(buff,tmpBuff);
      }

      EG_STRCAT(buff,"\n");
   }
#endif

   /******************
    * return success *
    ******************/
   RETVALUE(ROK);
}

#endif /* End of EG_PRNT_DATA */

#endif /* End of EGTP_U */

/********************************************************************30**

  End of file:     eg_util.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:53 2015

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**
 
*********************************************************************81*/
/********************************************************************90**
 
 ver           pat    init                  description
---------  --------   ---- ---------------------------------------
/main/1      ---        kc                1. Created for Initial Release 1.1
/main/2      ---      kchaitanya          1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
/main/3     eg002.201 psingh              1. Fixed warnings due to improper 
                                             placement of macro 
/main/3     eg003.201 psingh              1. Merged code from eg006.102 to Fix 
                                             TRACE5 macro related issue
                                          2. Merged code from eg008.102 to Fix 
                                             warning due to improper EG_TRC2 
                                             declaration                                             
/main/3     eg004.201 magnihotri          1.eGTPC PSF header files included
/main/3     eg005.201 psingh              1. Format specifier aligned to 32-bit val of Seq Num
/main/3     eg007.201 psingh              1. egTptGetTsapFrmAddr(): introduced to obtain TSapCb 
                                             from IP address
                                          2. EgUUtilDeAllocGmMsg: Moved Null ptr chk out
                                             of ERRCHK flag 
/main/3     eg009.201 asaurabh            1. Removed ERRCHK, as its supposed to suppress
                                             Error Logs, not Pointers checks.
                                          2. EgUtilDeAllocGmMsg(): check for NULL ptr.   
/main/3     eg012.201 shpandey            1. Added klocwork fixes
                                          2. In function egUtilDumpGmHdr:replaced sprintf with snprintf
                                          3. Added instance value check,fix for  ccpu00130411  
*********************************************************************91*/
