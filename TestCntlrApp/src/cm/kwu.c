

/********************************************************************20**
  
        Name:    KWU Interface
    
        Type:    C file
  
        Desc:    This file Contains the packing and unpacking functions for
                 KWU Interface
 
        File:    kwu.c

        Sid:      kwu.c@@/main/4 - Fri Sep  2 18:27:18 2011
  
        Prg:     chakrapani
  
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#ifdef TENB_SPLIT_ARCH
#include "ss_queue.h"
#include "ss_task.h"
#include "ss_msg.h"
#endif
#include "kwu.h"           /* KWU defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#ifdef TENB_SPLIT_ARCH
#include "ss_queue.x"
#include "ss_task.x"
#include "ss_msg.x"
#endif
#ifdef SS_RBUF
#include "ss_rbuf.h"
#include "ss_rbuf.x"
#endif /*SS_RBUF*/
#include "kwu.x"           /* KWU */

#ifdef LCKWU

/****************************************************************************
 *                      Packing Functions
 ***************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkKwuBndReq
(
Pst * pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkKwuBndReq(pst, suId, spId)
Pst * pst;
SuId suId;
SpId spId;
#endif
{
   S16    ret1;
   Buffer *mBuf;

   TRC3(cmPkKwuBndReq)

   mBuf = NULLP;

   if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      if(ret1 != ROK)
      {
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EKWU001, (ErrVal)0, "SGetMsg() failed");
      }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }
   CMCHKPKLOG(SPkS16, spId, mBuf, EKWU002, pst);
   CMCHKPKLOG(SPkS16, suId, mBuf, EKWU003, pst);
   pst->event = (Event) KWU_EVT_BND_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


#ifdef ANSI
PUBLIC S16 cmPkKwuBndCfm
(
Pst * pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkKwuBndCfm(pst, suId, status)
Pst * pst;
SuId suId;
U8 status;
#endif
{
   S16    ret1;
   Buffer *mBuf;

   TRC3(cmPkKwuBndCfm)

   mBuf = NULLP;

   if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      if(ret1 != ROK)
      {
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EKWU004, (ErrVal)0, "SGetMsg() failed");
      }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   CMCHKPKLOG(SPkU8, status, mBuf, EKWU005, pst);
   CMCHKPKLOG(SPkS16, suId, mBuf, EKWU006, pst);
   pst->event = (Event) KWU_EVT_BND_CFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


#ifdef ANSI
PUBLIC S16 cmPkKwuUbndReq
(
Pst * pst,
SuId suId,
Reason reason
)
#else
PUBLIC S16 cmPkKwuUbndReq(pst, suId, reason)
Pst * pst;
SuId suId;
Reason reason;
#endif
{
   S16 ret1;
   Buffer *mBuf;

   TRC3(cmPkKwuUbndReq)

   mBuf = NULLP;

   if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      if(ret1 != ROK)
      {
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EKWU007, (ErrVal)0, "SGetMsg() failed");
      }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }
   CMCHKPKLOG(SPkS16, reason, mBuf, EKWU008, pst);
   CMCHKPKLOG(SPkS16, suId, mBuf, EKWU009, pst);

   pst->event = (Event) KWU_EVT_UBND_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
} /* cmPkKwuUbndReq */

#ifdef ANSI
PUBLIC S16 cmPkKwuDatReqInfo
(
KwuDatReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkKwuDatReqInfo(param, mBuf)
KwuDatReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkKwuDatReqInfo);

#ifdef CCPU_OPT
   switch(param->lcType) {
      case CM_LTE_LCH_CCCH:
         CMCHKPK(cmPkLteRnti, param->tm.rnti, mBuf);
         break;
      case CM_LTE_LCH_BCCH:
      case  CM_LTE_LCH_PCCH:
         CMCHKPK(cmPkLteTimingInfo, &param->tm.tmg, mBuf);
         break;
      case CM_LTE_LCH_DTCH:
      case CM_LTE_LCH_DCCH:
         break;
      default :
         RETVALUE(RFAILED);
   }
   CMCHKPK(cmPkLteLcType, param->lcType, mBuf);

#endif
   CMCHKPK(SPkU32, param->sduId, mBuf);
   CMCHKPK(cmPkLteRlcId, &param->rlcId, mBuf);
   RETVALUE(ROK);
} /* cmPkKwuDatReqInfo */


#ifdef ANSI
PUBLIC S16 cmPkKwuDatReq
(
Pst * pst,
SpId spId,
KwuDatReqInfo* datReq,
Buffer * mBuf
)
#else
PUBLIC S16 cmPkKwuDatReq(pst, spId, datReq, mBuf)
Pst * pst;
SpId spId;
KwuDatReqInfo* datReq;
Buffer * mBuf;
#endif
{
#ifdef LCKWU
#if (ERRCLASS & ERRCLS_ADD_RES)
#endif
#endif /* LCKWU */
   S16 ret1 = ROK;
#ifndef SS_RBUF
   KwuDatReqInfo* datReqInfo;
#endif
    TRC3(cmPkKwuDatReq)
#ifndef SS_RBUF
   switch(pst->selector)
   {
     case KWU_SEL_LWLC:
        {
           if(pst->srcEnt == ENTPJ)
           {
             /* When the Selector is LWLC, we need to allocate memory, copy
              * the contents and pass the pointer of the allocated memory. The
              * subsequent free would be done during the Unpack function of the
              * primitive. */
            if((ret1 = SGetStaticBuffer(pst->region, pst->pool, (Data **)&datReqInfo,
                        sizeof(KwuDatReqInfo),SS_SHARABLE_MEMORY)) != ROK)
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
               if(ret1 != ROK)
               {
                  SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                        __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                        (ErrVal)EKWU028, (ErrVal)0, "SGetMsg() failed");
               }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
               RETVALUE(ret1);
            }
            cmMemcpy((U8*)datReqInfo,(U8*)datReq,sizeof(KwuDatReqInfo));
            CMCHKPK(cmPkPtr,(PTR)datReqInfo, mBuf);
           }
           else
           {
            CMCHKPK(cmPkPtr,(PTR)datReq, mBuf);
           }
        }
        break;
     case KWU_SEL_LC:
        {
#if (ERRCLASS & ERRCLS_ADD_RES)
           ret1 = cmPkKwuDatReqInfo( (datReq), mBuf);
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                    (ErrVal)EKWU010, (ErrVal)ret1, "Packing failure");
              RETVALUE( ret1 );
           }
#else
           cmPkKwuDatReqInfo( (datReq), mBuf);
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
           if(pst->srcEnt == ENTNH)
           {
              if (SPutStaticBuffer(pst->region, pst->pool, (Data *)datReq,
                       sizeof(KwuDatReqInfo),SS_SHARABLE_MEMORY) != ROK)
              {
                 SPutMsg(mBuf);
                 RETVALUE(RFAILED);
              }
           }
        }
        break;
     default:
          SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRKWU, (ErrVal)ret1, "pst->selector is invalid\n");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
          RETVALUE(RFAILED);
   }

    CMCHKPKLOG(SPkS16, spId, mBuf, EKWU011, pst);
#ifdef L2_L3_SPLIT
    if(datReq->rlcId.rbType == CM_LTE_SRB)
    {
       pst->event = (Event) KWU_EVT_CPLANE_DAT_REQ;
    }
    else
    {
       pst->event = (Event) KWU_EVT_UPLANE_DAT_REQ;
    }
#else
    pst->event = (Event) KWU_EVT_DAT_REQ;
#endif
    RETVALUE(SPstTsk(pst,mBuf));
#else
   if (pst->srcEnt == ENTPJ)
   {
      Void *elem = NULLP;
      KwuDatReqDetl *kwuDatReqDetl = NULLP;
      elem = SRngGetWIndx(SS_RNG_BUF_DLPDCP_TO_DLRLC);
      if (NULLP != elem)
      {
         kwuDatReqDetl = (KwuDatReqDetl *) elem;
         kwuDatReqDetl->spId = spId;
         kwuDatReqDetl->lcType = datReq->lcType;
         kwuDatReqDetl->sduId = datReq->sduId;
         kwuDatReqDetl->rlcId = datReq->rlcId;
         kwuDatReqDetl->mBuf = mBuf;
         SRngIncrWIndx(SS_RNG_BUF_DLPDCP_TO_DLRLC);
         SsRngInfoTbl[SS_RNG_BUF_DLPDCP_TO_DLRLC].pktRate++;
         ret1 = ROK;
      }
      else
      {
         SsRngInfoTbl[SS_RNG_BUF_DLPDCP_TO_DLRLC].pktDrop++;
         SPutMsg(mBuf);
         ret1 = RFAILED;
      }
   }
   else
   {
      switch(pst->selector)
      {
#ifdef LCKWU
         case KWU_SEL_LC:
            {
               ret1 = cmPkKwuDatReqInfo( (datReq), mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
               if(ret1 != ROK)
               {
                  SPutMsg(mBuf);
                  SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                        __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                        (ErrVal)EKWU010, (ErrVal)ret1, "Packing failure");
                  RETVALUE( ret1 );
               }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
            }
            break;
         case KWU_SEL_LWLC:
            {
               CMCHKPK(cmPkPtr,(PTR)datReq, mBuf);
            }
            break;
#endif /* LCKWU */
      }

      CMCHKPKLOG(SPkS16, spId, mBuf, EKWU011, pst);
      pst->event = (Event) KWU_EVT_DAT_REQ;
      ret1 = SPstTsk(pst,mBuf);
      if(pst->selector == KWU_SEL_LC)
      {
         if (SPutStaticBuffer(pst->region, pst->pool, (Data *)datReq,
                  sizeof(KwuDatReqInfo),SS_SHARABLE_MEMORY) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
   }
   RETVALUE(ret1);
#endif
} /* cmPkKwuDatReq */


#ifdef ANSI
PUBLIC S16 cmPkKwuDatIndInfo
(
KwuDatIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkKwuDatIndInfo(param, mBuf)
KwuDatIndInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkKwuDatIndInfo);

   CMCHKPK(SPkU8, param->isOutOfSeq, mBuf);
#ifdef CCPU_OPT
   CMCHKPK(cmPkLteRnti, param->tCrnti, mBuf);
#endif
   CMCHKPK(cmPkLteRlcId, &param->rlcId, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkKwuDatInd
(
Pst * pst,
SuId suId,
KwuDatIndInfo* datInd,
Buffer * mBuf
)
#else
PUBLIC S16 cmPkKwuDatInd(pst, suId, datInd, mBuf)
Pst * pst;
SuId suId;
KwuDatIndInfo* datInd;
Buffer * mBuf;
#endif
{
#ifdef LCKWU
    S16 ret1 = ROK;
#endif /* LCKWU */
#ifdef TENB_SPLIT_ARCH
#ifdef SS_LOCKLESS_MEMORY
    SsMsgInfo   *mInfo; 
#endif
#endif
    KwuDatIndInfo *datIndInfo = NULLP;

    TRC3(cmPkKwuDatInd)

#ifdef TENB_SPLIT_ARCH
    /* SSI_CHANGES: */
#ifdef SS_LOCKLESS_MEMORY
    mInfo = (SsMsgInfo *)mBuf->b_rptr;
    mInfo->region = pst->region;
#endif /* SS_LOCKLESS_MEMORY */
#endif

    switch(pst->selector)
    {
       case KWU_SEL_LWLC:
          {
             /* When the Selector is LWLC, we need to allocate memory, copy
              * the contents and pass the pointer of the allocated memory. The
              * subsequent free would be done during the Unpack function of the
              * primitive. */
            if((ret1 = SGetStaticBuffer(pst->region, pst->pool, (Data **)&datIndInfo,
                        sizeof(KwuDatIndInfo),SS_SHARABLE_MEMORY)) != ROK)
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
               if(ret1 != ROK)
               {
                  SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                        __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                        (ErrVal)EKWU028, (ErrVal)0, "SGetMsg() failed");
               }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
               RETVALUE(ret1);
            }

            cmMemcpy((U8*)datIndInfo,(U8*)datInd,sizeof(KwuDatIndInfo));
            CMCHKPK(cmPkPtr,(PTR)datIndInfo, mBuf);
          }
          break;
       case KWU_SEL_LC:
          {
#if (ERRCLASS & ERRCLS_ADD_RES)
             ret1 = cmPkKwuDatIndInfo( (datInd), mBuf);
             if(ret1 != ROK)
             {
                SPutMsg(mBuf);
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                      (ErrVal)EKWU012, (ErrVal)ret1, "Packing failure");
                RETVALUE( ret1 );
             }
#else
             cmPkKwuDatIndInfo( (datInd), mBuf);
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
#if 0
             /*Commenting out the below block as no Memory Allocation happens 
              * in Protocol. This code will be removed once testing is done */
             if (SPutStaticBuffer(pst->region, pst->pool, (Data *)datInd,
                      sizeof(KwuDatIndInfo),SS_SHARABLE_MEMORY) != ROK)
             {
                SPutMsg(mBuf);
                RETVALUE(RFAILED);
             }
#endif
          }
          break;
       default:
          SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRKWU, (ErrVal)ret1, "pst->selector is invalid\n");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
          RETVALUE(RFAILED);
    }

    CMCHKPKLOG(SPkS16, suId, mBuf, EKWU013, pst);
    pst->event = (Event) KWU_EVT_DAT_IND;

    RETVALUE(SPstTsk(pst,mBuf));
} /* cmPkKwuDatInd */


#ifdef ANSI
PUBLIC S16 cmPkKwuDatCfmInfo
(
KwuDatCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkKwuDatCfmInfo(param, mBuf)
KwuDatCfmInfo *param;
Buffer *mBuf;
#endif
{
   register U32 iter;

   TRC3(cmPkKwuDatCfmInfo);
   for(iter = 0; iter < param->numSduIds; iter++)
   {
      CMCHKPK(SPkU32, param->sduIds[iter], mBuf);
   }
   CMCHKPK(SPkU32, param->numSduIds, mBuf);
   CMCHKPK(cmPkLteRlcId, &param->rlcId, mBuf);
   RETVALUE(ROK);
} /* cmPkKwuDatCfmInfo */


#ifdef ANSI
PUBLIC S16 cmPkKwuDatCfm
(
Pst * pst,
SuId suId,
KwuDatCfmInfo* datCfm
)
#else
PUBLIC S16 cmPkKwuDatCfm(pst, suId, datCfm)
Pst * pst;
SuId suId;
KwuDatCfmInfo* datCfm;
#endif
{
#if (ERRCLASS & ERRCLS_ADD_RES)
   S16 ret1= ROK;
#endif 
   Buffer *mBuf;

   TRC3(cmPkKwuDatCfm)

   mBuf = NULLP;

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }

   switch(pst->selector)
   {
      case KWU_SEL_LWLC:
         {
            CMCHKPK(cmPkPtr,(PTR)datCfm, mBuf);
         }
         break;
      case KWU_SEL_LC:
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            ret1 = cmPkKwuDatCfmInfo( (datCfm), mBuf);
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                     (ErrVal)EKWU014, (ErrVal)ret1, "Packing failure");
               RETVALUE( ret1 );
            }
#else
            cmPkKwuDatCfmInfo( (datCfm), mBuf);
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
            if (SPutStaticBuffer(pst->region, pst->pool, (Data *)datCfm,
                     sizeof(KwuDatCfmInfo),SS_SHARABLE_MEMORY) != ROK)
            {
               SPutMsg(mBuf);
               RETVALUE(RFAILED);
            }
         }
         break;
      default:
          SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRKWU, (ErrVal)ret1, "pst->selector is invalid\n");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
          RETVALUE(RFAILED);
   }

    CMCHKPKLOG(SPkS16, suId, mBuf, EKWU015, pst);
    pst->event = (Event) KWU_EVT_DAT_CFM;

    RETVALUE(SPstTsk(pst,mBuf));
} /* cmPkKwuDatCfm */


#ifdef ANSI
PUBLIC S16 cmPkKwuDiscSduReq
(
Pst * pst,
SpId spId,
KwuDiscSduInfo* discSdu
)
#else
PUBLIC S16 cmPkKwuDiscSduReq(pst, spId, discSdu)
Pst * pst;
SpId spId;
KwuDiscSduInfo* discSdu;
#endif
{
#ifdef LCKWU
   S16 ret1;
#endif /* LCKWU */
   Buffer *mBuf;
   KwuDiscSduInfo* discSduInfo = NULLP;

   TRC3(cmPkKwuDiscSduReq)
   mBuf = NULLP;

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }

   switch(pst->selector)
   {
      case KWU_SEL_LWLC:
         {
            /* When the Selector is LWLC, we need to allocate memory, copy
             * the contents and pass the pointer of the allocated memory. The
             * subsequent free would be done during the Unpack function of the
             * primitive. */
           if((ret1 = SGetStaticBuffer(pst->region, pst->pool, (Data **)&discSduInfo,
                       sizeof(KwuDiscSduInfo),SS_SHARABLE_MEMORY)) != ROK)
           {
#if (ERRCLASS & ERRCLS_ADD_RES)
              if(ret1 != ROK)
              {
                 SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                       __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                        (ErrVal)EKWU028, (ErrVal)0, "SGetMsg() failed");
              }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
              RETVALUE(ret1);
           }
            
           cmMemcpy((U8*)discSduInfo,(U8*)discSdu,sizeof(KwuDiscSduInfo));
           CMCHKPK(cmPkPtr,(PTR)discSduInfo, mBuf);
         }
         break;
      case KWU_SEL_LC:
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            ret1 = cmPkKwuDiscSduInfo( (discSdu), mBuf);
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                     (ErrVal)EKWU016, (ErrVal)ret1, "Packing failure");
               RETVALUE( ret1 );
            }
#else
            cmPkKwuDiscSduInfo( (discSdu), mBuf);
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
#if 0
             if (SPutSBuf(pst->region, pst->pool, (Data *)discSdu,
                      sizeof(KwuDiscSduInfo)) != ROK)
             {
                SPutMsg(mBuf);
                RETVALUE(RFAILED);
             }
#endif 
             break;
          }
    }

    CMCHKPKLOG(SPkS16, spId, mBuf, EKWU017, pst);
    pst->event = (Event) KWU_EVT_DISC_SDU_REQ;

    RETVALUE(SPstTsk(pst,mBuf));
} /* cmPkKwuDiscSduReq */


#ifdef ANSI
PUBLIC S16 cmPkKwuStaIndInfo
(
KwuStaIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkKwuStaIndInfo(param, mBuf)
KwuStaIndInfo *param;
Buffer *mBuf;
#endif
{
   S16 i;

   TRC3(cmPkKwuStaIndInfo);

   for (i = (param->numSdu - 1); i >= 0; i--)
   {
      CMCHKPK(SPkU32, param->sduId[(U16)i], mBuf);
   }
   CMCHKPK(SPkU32, param->numSdu, mBuf);
   CMCHKPK(cmPkLteRlcId, &param->rlcId, mBuf);
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkKwuFlowCntrlIndInfo
(
KwuFlowCntrlIndInfo *param,
Buffer              *mBuf
)
#else
PUBLIC S16 cmPkKwuFlowCntrlIndInfo(param, mBuf)
KwuFlowCntrlIndInfo  *param;
Buffer               *mBuf;
#endif
{
   TRC3(cmPkKwuFlowCntrlIndInfo);

   CMCHKPK(SPkU32, param->pktAdmitCnt, mBuf);   
   CMCHKPK(cmPkLteRlcId, &param->rlcId, mBuf);

   RETVALUE(ROK);
} /* cmPkKwuFlowCntrlIndInfo */

#ifdef ANSI
PUBLIC S16 cmUnpkKwuFlowCntrlIndInfo
(
KwuFlowCntrlIndInfo *param,
Buffer              *mBuf
)
#else
PUBLIC S16 cmUnpkKwuFlowCntrlIndInfo(param, mBuf)
KwuFlowCntrlIndInfo  *param;
Buffer               *mBuf;
#endif
{
   TRC3(cmUnpkKwuFlowCntrlIndInfo);
   
   CMCHKUNPK(cmUnpkLteRlcId, &param->rlcId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->pktAdmitCnt, mBuf);
  
   RETVALUE(ROK);
} /* cmUnpkKwuFlowCntrlIndInfo */


#ifdef ANSI
PUBLIC S16 cmPkKwuStaInd
(
Pst * pst,
SuId suId,
KwuStaIndInfo* staInd
)
#else
PUBLIC S16 cmPkKwuStaInd(pst, suId, staInd)
Pst * pst;
SuId suId;
KwuStaIndInfo* staInd;
#endif
{
#ifdef LCKWU
#if (ERRCLASS & ERRCLS_ADD_RES)
   S16 ret1 = ROK;
#endif
#endif /* LCKWU */
   Buffer *mBuf;

   TRC3(cmPkKwuStaInd)

   mBuf = NULLP;

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }

    switch(pst->selector)
    {
       case KWU_SEL_LWLC:
          {
             CMCHKPK(cmPkPtr,(PTR) staInd, mBuf);
          }
          break;
       case KWU_SEL_LC:
          {
#if (ERRCLASS & ERRCLS_ADD_RES)
             ret1 = cmPkKwuStaIndInfo( (staInd), mBuf);
             if(ret1 != ROK)
             {
                SPutMsg(mBuf);
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                      (ErrVal)EKWU018, (ErrVal)ret1, "Packing failure");
                RETVALUE( ret1 );
             }
#else
             cmPkKwuStaIndInfo( (staInd), mBuf);
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
             if (SPutStaticBuffer(pst->region, pst->pool, (Data *)staInd,
                      sizeof(KwuStaIndInfo),SS_SHARABLE_MEMORY) != ROK)
             {
                SPutMsg(mBuf);
                RETVALUE(RFAILED);
             }
          }
          break;
       default:
          SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRKWU, (ErrVal)ret1, "pst->selector is invalid\n");
#endif
          RETVALUE(RFAILED);
    }

    CMCHKPKLOG(SPkS16, suId, mBuf, EKWU019, pst);
    pst->event = (Event) KWU_EVT_STA_IND;

    RETVALUE(SPstTsk(pst,mBuf));
} /* cmPkKwuStaInd */


#ifdef ANSI
PUBLIC S16 cmPkKwuReEstCmpInd
(
Pst * pst,
SuId suId,
CmLteRlcId rlcId
)
#else
PUBLIC S16 cmPkKwuReEstCmpInd(pst, suId, rlcId)
Pst * pst;
SuId suId;
CmLteRlcId rlcId;
#endif
{
#ifdef LCKWU
   S16 ret1;
#endif /* LCKWU */
   Buffer *mBuf;

   TRC3(cmPkKwuReEstCmpInd)

   mBuf = NULLP;

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }

    switch(pst->selector)
    {
#ifdef LCKWU
       case KWU_SEL_LC:
          {
             ret1 = cmPkLteRlcId( &rlcId, mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
             if(ret1 != ROK)
             {
                SPutMsg(mBuf);
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                      (ErrVal)EKWU018, (ErrVal)ret1, "Packing failure");
                RETVALUE( ret1 );
             }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
             break;
          }
#endif /* LCKWU */
    }

    CMCHKPKLOG(SPkS16, suId, mBuf, EKWU019, pst);
    pst->event = (Event) KWU_EVT_REEST_CMP_IND;

    RETVALUE(SPstTsk(pst,mBuf));
} /* cmPkKwuReEstCmpInd */

/* kwu_c_001.main_3 added support for L2 Measurement */
#ifdef ANSI
PUBLIC S16 cmPkKwuDiscSduCfm
(
Pst            *pst,
SpId           spId,
KwuDiscSduInfo *discCfmSdu
)
#else
PUBLIC S16 cmPkKwuDiscSduCfm(pst, spId, discCfmSdu)
Pst            *pst;
SpId           spId;
KwuDiscSduInfo *discCfmSdu;
#endif
{
#if (ERRCLASS & ERRCLS_ADD_RES)
   S16 ret1 = ROK;
#endif
   Buffer *mBuf;

   TRC3(cmPkKwuDiscSduCfm)

   mBuf = NULLP;

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }

   switch(pst->selector)
   {
      case KWU_SEL_LWLC:
         {
            CMCHKPK(cmPkPtr,(PTR)discCfmSdu, mBuf);
         }
         break;
      case KWU_SEL_LC:
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            ret1 = cmPkKwuDiscSduInfo((discCfmSdu), mBuf);
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                     (ErrVal)ERRKWU, (ErrVal)ret1, "Packing failure");
               RETVALUE( ret1 );
            }
#else
            cmPkKwuDiscSduInfo((discCfmSdu), mBuf);
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
            if (SPutStaticBuffer(pst->region, pst->pool, (Data *)discCfmSdu,
                     sizeof(KwuDiscSduInfo),SS_SHARABLE_MEMORY) != ROK)
            {
               SPutMsg(mBuf);
               RETVALUE(RFAILED);
            }
         }
         break;
      default:
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRKWU, (ErrVal)ret1, "pst->selector is invalid\n");
#endif
          RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkS16, spId, mBuf, ERRKWU, pst);
   pst->event = (Event) KWU_EVT_DISC_SDU_CFM;

   RETVALUE(SPstTsk(pst,mBuf));
} /* cmPkKwuDiscSduCfm */

#ifdef ANSI
PUBLIC S16 cmPkKwuFlowCntrlInd
(
Pst            *pst,
SuId           suId,
KwuFlowCntrlIndInfo *flowCntrlIndInfo
)
#else
PUBLIC S16 cmPkKwuFlowCntrlInd(pst, suId, flowCntrlIndInfo)
Pst            *pst;
SuId           suId;
KwuFlowCntrlIndInfo *flowCntrlIndInfo;
#endif
{
   Buffer *mBuf;

   TRC3(cmPkKwuFlowCntrlInd)

   mBuf = NULLP;

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      SPutStaticBuffer(pst->region, 
               pst->pool, 
               (Data *)flowCntrlIndInfo,
               sizeof(KwuFlowCntrlIndInfo),0);
      RETVALUE(RFAILED);
   }
#ifdef LCKWU
   switch(pst->selector)
   {
      case KWU_SEL_LC:
      {
         cmPkKwuFlowCntrlIndInfo((flowCntrlIndInfo), mBuf);

         if (SPutStaticBuffer(pst->region, 
                      pst->pool, 
                      (Data *)flowCntrlIndInfo,
                      sizeof(KwuFlowCntrlIndInfo),0) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
      break;
      
      case KWU_SEL_LWLC:
      {
         CMCHKPK(cmPkPtr,(PTR) flowCntrlIndInfo, mBuf);
      }
      break;
   }
#endif

   CMCHKPKLOG(SPkS16, suId, mBuf, ERRKWU, pst);
   pst->event = (Event) KWU_EVT_FLOW_CNTRL_IND;

   RETVALUE(SPstTsk(pst,mBuf));
} /* cmPkKwuFlowCntrlInd */

#ifdef LTE_L2_MEAS
#ifdef ANSI
PUBLIC S16 cmPkKwuDatAckInfo
(
KwuDatAckInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkKwuDatAckInfo(param, mBuf)
KwuDatAckInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkKwuDatAckIndInfo);

   CMCHKPK(cmPkLteRlcId, &param->rlcId, mBuf);
   CMCHKPK(SPkU32, param->sduId, mBuf);
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkKwuDatAckInd
(
Pst * pst,
SuId suId,
KwuDatAckInfo* datInd
)
#else
PUBLIC S16 cmPkKwuDatAckInd(pst, suId, datInd)
Pst * pst;
SuId suId;
KwuDatAckInfo* datInd;
#endif
{
    S16 ret1;

   Buffer *mBuf;

   TRC3(cmPkKwuDatAckInd);

   mBuf = NULLP;

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }

   ret1 = cmPkKwuDatAckInfo( (datInd), mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
   if(ret1 != ROK)
   {
      SPutMsg(mBuf);
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERRKWU, (ErrVal)ret1, "Packing failure");
      RETVALUE( ret1 );
   }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
   if (SPutStaticBuffer(pst->region, pst->pool, (Data *)datInd,
            sizeof(KwuDatAckInfo),SS_SHARABLE_MEMORY) != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkS16, suId, mBuf, ERRKWU, pst);
   pst->event = (Event) KWU_EVT_DAT_ACK_IND;

   RETVALUE(SPstTsk(pst,mBuf));
} /* cmPkKwuDatAckInd */
#endif /* LTE_L2_MEAS */


#ifdef ANSI
PUBLIC S16 cmUnpkKwuBndReq
(
KwuBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuBndReq(func, pst, mBuf)
KwuBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId = 0;
   SpId spId = 0;

   TRC3(cmUnpkKwuBndReq)

   CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, EKWU020, pst);
   CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, EKWU021, pst);
   SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, spId));
}


#ifdef ANSI
PUBLIC S16 cmUnpkKwuBndCfm
(
KwuBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuBndCfm(func, pst, mBuf)
KwuBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId = 0;
   U8 status = 0;

   TRC3(cmUnpkKwuBndCfm)

   CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, EKWU022, pst);
   CMCHKUNPKLOG(SUnpkU8, &status, mBuf, EKWU023, pst);
   SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, status));
}


#ifdef ANSI
PUBLIC S16 cmUnpkKwuUbndReq
(
KwuUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuUbndReq(func, pst, mBuf)
KwuUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId = 0;
   Reason reason = 0;
   
   TRC3(cmUnpkKwuUbndReq)

   CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, EKWU024, pst);
   CMCHKUNPKLOG(SUnpkS16, &reason, mBuf, EKWU025, pst);
   SPutMsg(mBuf);

   RETVALUE((*func)(pst, spId, reason));
} /* cmUnpkKwuUbndReq */


#ifdef ANSI
PUBLIC S16 cmUnpkKwuDatReqInfo
(
KwuDatReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuDatReqInfo(param, mBuf)
KwuDatReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkKwuDatReqInfo);

   CMCHKUNPK(cmUnpkLteRlcId, &param->rlcId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->sduId, mBuf);

#ifdef CCPU_OPT
   CMCHKUNPK(cmUnpkLteLcType, &param->lcType, mBuf);
   switch(param->lcType) {
      case CM_LTE_LCH_BCCH:
      case  CM_LTE_LCH_PCCH:
         CMCHKUNPK(cmUnpkLteTimingInfo, &param->tm.tmg, mBuf);
         break;
      case CM_LTE_LCH_CCCH:
         CMCHKUNPK(cmUnpkLteRnti, &param->tm.rnti, mBuf);
         break;
      case CM_LTE_LCH_DTCH:
      case CM_LTE_LCH_DCCH:
         break;
      default :
         RETVALUE(RFAILED);
   }
#endif
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkKwuDatReq
(
KwuDatReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuDatReq(func, pst, mBuf)
KwuDatReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16 ret1 = ROK, retVal;
   SpId          spId = 0;
   KwuDatReqInfo *datReq = NULLP;
   KwuDatReqInfo datReqTmp;

   TRC3(cmUnpkKwuDatReq)


      CMCHKUNPK(SUnpkS16, &(spId), mBuf);

   switch(pst->selector)
   {
      case KWU_SEL_LWLC:
         {
            CMCHKUNPK(cmUnpkPtr,(PTR *) &datReq, mBuf);
         }
         break;
      case KWU_SEL_LC:
         {
#if 0
        /*This will be removed once the testing is done on all platforms */
            if((ret1 = SGetStaticBuffer(pst->region, pst->pool, (Data **)&datReq,\
                        sizeof(KwuDatReqInfo),SS_SHARABLE_MEMORY)) != ROK)
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
               /*MBUF_FIXX*/
               SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                     (ErrVal)EKWU026, (ErrVal)0, "SGetMsg() failed");

#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
               RETVALUE(ret1);
            }

#endif
            /* Allocate the memory statically  as there is no free 
             * in RLC */
            datReq = &datReqTmp;
            cmMemset((U8 *)datReq, 0, sizeof(KwuDatReqInfo));
            ret1 = cmUnpkKwuDatReqInfo( (datReq), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)EKWU027, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /* ERRCLASS & ERRCLS_DEBUG */
         }
         break;
      default:
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRKWU, (ErrVal)ret1, "pst->selector is invalid\n");
#endif
         RETVALUE(RFAILED);
   }

   retVal = (*func)(pst, spId, datReq, mBuf);
   /* If LWLC is configured, we need to
    * free the memory here. */
   if(pst->selector == KWU_SEL_LWLC)
   {
      retVal = SPutStaticBuffer(pst->region, pst->pool, (Data *)datReq,
            sizeof(KwuDatReqInfo),SS_SHARABLE_MEMORY);
   }
   RETVALUE(retVal);
} /* cmUnpkKwuDatReq */


#ifdef ANSI
PUBLIC S16 cmUnpkKwuDatIndInfo
(
KwuDatIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuDatIndInfo(param, mBuf)
KwuDatIndInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkKwuDatIndInfo);

   CMCHKUNPK(cmUnpkLteRlcId, &param->rlcId, mBuf);

#ifdef CCPU_OPT
   CMCHKUNPK(cmUnpkLteRnti, &param->tCrnti, mBuf);
#endif
   CMCHKUNPK(SUnpkU8, &param->isOutOfSeq, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkKwuDatInd
(
KwuDatInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuDatInd(func, pst, mBuf)
KwuDatInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1 = ROK, retVal;
    SuId          suId = 0;
    KwuDatIndInfo *datInd = NULLP;
    KwuDatIndInfo datIndTmp;
    
    TRC3(cmUnpkKwuDatInd)

    CMCHKUNPK(SUnpkS16, &(suId), mBuf);
    
    switch(pst->selector)
    {
      case KWU_SEL_LWLC:
         {
            CMCHKUNPK(cmUnpkPtr,(PTR *) &datInd, mBuf);
         }
         break;
      case KWU_SEL_LC:
         {
            /*SGetStaticBuffer used as RRC has an equivalent free but PDCP
             * doesn't free any memory */
            if(pst->dstEnt != ENTPJ)
            {
               if((ret1 = SGetStaticBuffer(pst->region, pst->pool, (Data **)&datInd,
                           sizeof(KwuDatIndInfo),SS_SHARABLE_MEMORY)) != ROK)
               {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EKWU028, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
                  RETVALUE(ret1);
               }
            }
            else
            {
               datInd = &datIndTmp;
            }

            ret1 = cmUnpkKwuDatIndInfo( (datInd), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)EKWU029, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
         }
         break;
      default:
         SPutMsg(mBuf);
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRKWU, (ErrVal)ret1, "pst->selector is invalid\n");
         RETVALUE(RFAILED);
    }
    retVal = (*func)(pst, suId, datInd, mBuf);
    /* If LWLC is configured and the destination entity is PDCP, we need to
     * free the memory here. */
    if((pst->selector == KWU_SEL_LWLC) && (pst->dstEnt == ENTPJ))
    {
       retVal = SPutStaticBuffer(pst->region, pst->pool, (Data *)datInd,
                sizeof(KwuDatIndInfo),SS_SHARABLE_MEMORY);
    }
    RETVALUE(retVal);
} /* cmUnpkKwuDatInd */


#ifdef ANSI
PUBLIC S16 cmUnpkKwuDatCfmInfo
(
KwuDatCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuDatCfmInfo(param, mBuf)
KwuDatCfmInfo *param;
Buffer *mBuf;
#endif
{
   register S32 iter;
   TRC3(cmUnpkKwuDatCfmInfo);

   CMCHKUNPK(cmUnpkLteRlcId, &param->rlcId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numSduIds, mBuf);

#ifdef L2_L3_SPLIT /*Work Around */
   if (param->numSduIds >= KWU_MAX_DAT_CFM)
      param->numSduIds = KWU_MAX_DAT_CFM;
#endif
   for(iter = param->numSduIds -1; iter >= 0 ; iter--)
   {
      CMCHKUNPK(SUnpkU32, &param->sduIds[iter], mBuf);
   }
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmUnpkKwuDatCfm
(
KwuDatCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuDatCfm(func, pst, mBuf)
KwuDatCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16 ret1 = ROK;
   SuId          suId = 0;
   KwuDatCfmInfo *datCfm = NULLP;

   TRC3(cmUnpkKwuDatCfm)

   CMCHKUNPK(SUnpkS16, &(suId), mBuf);

   switch(pst->selector)
   {
      case KWU_SEL_LWLC:
         {
            CMCHKUNPK(cmUnpkPtr,(PTR *) &datCfm, mBuf);
         }
         break;
      case KWU_SEL_LC:
         {
            if((ret1 = SGetStaticBuffer(pst->region, pst->pool, (Data **)&datCfm,\
                        sizeof(KwuDatCfmInfo),SS_SHARABLE_MEMORY)) != ROK)
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EKWU030, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
               RETVALUE(ret1);
            }

            cmMemset((U8 *)datCfm, 0, sizeof(KwuDatCfmInfo));
            ret1 = cmUnpkKwuDatCfmInfo( (datCfm), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)EKWU031, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
         }
         break;
      default:
#if (ERRCLASS & ERRCLS_ADD_RES)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRKWU, (ErrVal)ret1, "pst->selector is invalid\n");
#endif
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, datCfm));
} /* cmUnpkKwuDatCfm */


#ifdef ANSI
PUBLIC S16 cmUnpkKwuDiscSduReq
(
KwuDiscSduReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuDiscSduReq(func, pst, mBuf)
KwuDiscSduReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16 ret1 = ROK;
   SpId          spId = 0;
   KwuDiscSduInfo *discSdu = NULLP;


   CMCHKUNPK(SUnpkS16, &(spId), mBuf);
   switch(pst->selector)
   {
      case KWU_SEL_LWLC:
         {
            CMCHKUNPK(cmUnpkPtr,(PTR *) &discSdu, mBuf);
         }
         break;
      case KWU_SEL_LC:
         {
            if((ret1 = SGetStaticBuffer(pst->region, pst->pool, (Data **)&discSdu,\
                        sizeof(KwuDiscSduInfo),SS_SHARABLE_MEMORY)) != ROK)
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
               /*MBUF_FIXX*/
               SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                     (ErrVal)EKWU032, (ErrVal)0, "SGetMsg() failed");

#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
               RETVALUE(ret1);
            }

            cmMemset((U8 *)discSdu, 0, sizeof(KwuDiscSduInfo));
            ret1 = cmUnpkKwuDiscSduInfo( (discSdu), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)EKWU033, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /* ERRCLASS & ERRCLS_DEBUG */
            break;
         }
      default:
#if (ERRCLASS & ERRCLS_ADD_RES)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRKWU, (ErrVal)ret1, "pst->selector is invalid\n");
#endif
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);

   RETVALUE((*func)(pst, spId, discSdu));
} /* cmUnpkKwuDiscSduReq */


#ifdef ANSI
PUBLIC S16 cmUnpkKwuStaIndInfo
(
KwuStaIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuStaIndInfo(param, mBuf)
KwuStaIndInfo *param;
Buffer *mBuf;
#endif
{
   U32 i;

   TRC3(cmUnpkKwuStaIndInfo);

   CMCHKUNPK(cmUnpkLteRlcId, &param->rlcId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numSdu, mBuf);
   for (i = 0; i < param->numSdu; i++)
   {
      CMCHKUNPK(SUnpkU32, &param->sduId[i], mBuf);
   }

   RETVALUE(ROK);
} /* cmUnpkKwuStaIndInfo */


#ifdef ANSI
PUBLIC S16 cmUnpkKwuStaInd
(
KwuStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuStaInd(func, pst, mBuf)
KwuStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16 ret1 = ROK;
   SuId          suId = 0;
   KwuStaIndInfo *staInd = NULLP;

   TRC3(cmUnpkKwuStaInd)

   CMCHKUNPK(SUnpkS16, &(suId), mBuf);
   
   switch(pst->selector)
   {
      case KWU_SEL_LWLC:
         {
            CMCHKUNPK(cmUnpkPtr,(PTR *)&staInd, mBuf);
         }
         break;
      case KWU_SEL_LC:
         {
            if((ret1 = SGetStaticBuffer(pst->region, pst->pool, (Data **)&staInd,\
                        sizeof(KwuStaIndInfo),SS_SHARABLE_MEMORY)) != ROK)
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
               if(ret1 != ROK)
               {
                  SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                        __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                        (ErrVal)EKWU034, (ErrVal)0, "SGetMsg() failed");
               }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
               RETVALUE(ret1);
            }

            cmMemset((U8 *)staInd, 0, sizeof(KwuStaIndInfo));

            ret1 = cmUnpkKwuStaIndInfo( (staInd), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)EKWU035, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /* ERRCLASS & ERRCLS_DEBUG */
         }
         break;
      default:
          SPutMsg(mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRKWU, (ErrVal)ret1, "pst->selector is invalid\n");
#endif
          RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, staInd));
} /* cmUnpkKwuStaInd */


#ifdef ANSI
PUBLIC S16 cmUnpkKwuReEstCmpInd
(
KwuReEstCmpInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuReEstCmpInd(func, pst, mBuf)
KwuReEstCmpInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16 ret1;
   SuId          suId = 0;
   CmLteRlcId    rlcId;

   TRC3(cmUnpkKwuReEstCmpInd)

   cmMemset((U8 *)&rlcId, 0, sizeof(CmLteRlcId));

   CMCHKUNPK(SUnpkS16, &(suId), mBuf);
   switch(pst->selector)
   {
#ifdef LCKWU
      case KWU_SEL_LC:
         {
            ret1 = cmUnpkLteRlcId( &rlcId, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)EKWU035, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /* ERRCLASS & ERRCLS_DEBUG */
            break;
         }
#endif /* LCKWU */
   }
   SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, rlcId));
} /* cmUnpkKwuReEstCmpInd */

/* kwu_c_001.main_3 added support for L2 Measurement */
#ifdef ANSI
PUBLIC S16 cmUnpkKwuDiscSduCfm
(
KwuDiscSduCfm  func,
Pst            *pst,
Buffer         *mBuf
)
#else
PUBLIC S16 cmUnpkKwuDiscSduCfm(func, pst, mBuf)
KwuDiscSduCfm  func;
Pst            *pst;
Buffer         *mBuf;
#endif
{
   S16 ret1 = ROK;
   SpId          spId = 0;
   KwuDiscSduInfo *discSdu = NULLP;

   TRC3(cmUnpkKwuDiscSduCfm);

   CMCHKUNPK(SUnpkS16, &(spId), mBuf);

   switch(pst->selector)
   {
      case KWU_SEL_LWLC:
         {
            CMCHKUNPK(cmUnpkPtr,(PTR *) &discSdu, mBuf);
         }
         break;
      case KWU_SEL_LC:
         {
            if((ret1 = SGetStaticBuffer(pst->region, pst->pool, (Data **)&discSdu,\
                        sizeof(KwuDiscSduInfo),SS_SHARABLE_MEMORY)) != ROK)
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
      if(ret1 != ROK)
      {
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRKWU, (ErrVal)0, "SGetMsg() failed");
      }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
               RETVALUE(ret1);
            }
            cmMemset((U8 *)discSdu, 0, sizeof(KwuDiscSduInfo));

   ret1 = cmUnpkKwuDiscSduInfo( (discSdu), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                     (ErrVal)ERRKWU, (ErrVal)0, "SGetMsg() failed");
            }
#endif /* ERRCLASS & ERRCLS_DEBUG */
         }
         break;
      default:
          SPutMsg(mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRKWU, (ErrVal)ret1, "pst->selector is invalid\n");
#endif
          RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);

   RETVALUE((*func)(pst, spId, discSdu));
} /* cmUnpkKwuDiscSduCfm */
#ifdef ANSI
PUBLIC S16 cmUnpkKwuFlowCntrlInd
(
KwuFlowCntrlInd  func,
Pst            *pst,
Buffer         *mBuf
)
#else
PUBLIC S16 cmUnpkKwuFlowCntrlInd(func, pst, mBuf)
KwuFlowCntrlInd  func;
Pst            *pst;
Buffer         *mBuf;
#endif
{
   SuId   suId;
   KwuFlowCntrlIndInfo *flowCntrlInfo = NULLP;

   TRC3(cmUnpkKwuFlowCntrlInd);
   
   CMCHKUNPK(SUnpkS16, &(suId), mBuf);
   switch(pst->selector)
   {
#ifdef LCKWU
      case KWU_SEL_LC:
      {
         if(SGetStaticBuffer(pst->region, 
                     pst->pool, 
                     (Data **)&flowCntrlInfo,
                     sizeof(KwuFlowCntrlIndInfo),0) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }

         cmUnpkKwuFlowCntrlIndInfo(flowCntrlInfo, mBuf);
      }
      break;

      case KWU_SEL_LWLC:
      {
         CMCHKUNPK(cmUnpkPtr,(PTR *) &flowCntrlInfo, mBuf);
      }
      break;
#endif
   }

   SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, flowCntrlInfo));
} /* cmUnpkKwuFlowCntrlInd */
#ifdef LTE_L2_MEAS

#ifdef ANSI
PUBLIC S16 cmUnpkKwuDatAckInfo
(
KwuDatAckInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuDatAckInfo(param, mBuf)
KwuDatAckInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkKwuDatAckInfo);

   CMCHKUNPK(SUnpkU32, &param->sduId, mBuf);
   CMCHKUNPK(cmUnpkLteRlcId, &param->rlcId, mBuf);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkKwuDatAckInd
(
KwuDatAckInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkKwuDatAckInd(func, pst, mBuf)
KwuDatAckInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    SuId          suId = 0;
    KwuDatAckInfo *datInd = NULLP;
    
    TRC3(cmUnpkKwuDatAckInd);

    if((ret1 = SGetStaticBuffer(pst->region, pst->pool, (Data **)&datInd,\
                sizeof(KwuDatAckInfo),SS_SHARABLE_MEMORY)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ERRKWU, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    cmMemset((U8 *)datInd, 0, sizeof(KwuDatAckInfo));

    CMCHKUNPK(SUnpkS16, &(suId), mBuf);
    ret1 = cmUnpkKwuDatAckInfo( (datInd), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
             (ErrVal)ERRKWU, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /* ERRCLASS & ERRCLS_DEBUG */

    RETVALUE((*func)(pst, suId, datInd));
} /* cmUnpkKwuDatAckInd */
#endif /* LTE_L2_MEAS */
#endif /* LCKWU */

/********************************************************************30**

         End of file:     kwu.c@@/main/4 - Fri Sep  2 18:27:18 2011

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
/main/1      ---       cp  1. initial release.
/main/3      ---      gk   1. LTERLC Release 2.1.
/main/4     kwu_c_001.main_3 ap 1. Added support for L2 Measurement.
*********************************************************************91*/

