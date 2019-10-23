/********************************************************************20**
  
        Name:    LTE PDCP Interface  
    
        Type:    C file
  
        Desc:    This file contains the pack/unpack functions for the
                 data structures at CPJ Interface.
 
        File:    cpj.c

        Sid:      cpj.c@@/main/5 - Fri Sep  2 18:46:48 2011
  
        Prg:     Dinesh 
  
*********************************************************************21*/

/* header include files (.h) */
  
#include "envopt.h"             /* Environment options */  
#include "envdep.h"             /* Environment dependent */
#include "envind.h"             /* Environment independent */
#include "gen.h"                /* General */
#include "ssi.h"                /* System services interface */
#include "cm_lte.h"             /* Common LTE header file */
#include "cm_llist.h"           /* Linked List header file */
#include "cm_tkns.h"            /* Common tokens header file */
#include "cm_hash.h"            /* Hash List header file */
#include "cm_gen.h"             /* Common General tokens header file */
#include "cpj.h"                /* CPJ Interface header file */



/* header/extern include files (.x) */

#include "gen.x"                /* General */
#include "ssi.x"                /* System services interface */
#include "cm_lib.x"             /* Common lib header file */
#include "cm_hash.x"            /* Hash List header file */
#include "cm_llist.x"           /* Linked List header file */
#include "cm_tkns.x"            /* Common tokens header file */
#include "cm_lte.x"             /* Common LTE header file */
#include "cpj.x"                /* CPJ Interface header file */


/* Packing/Unpacking Macros */

#if(defined(LCCPJ) || defined(LWLCCPJ))

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */

#ifdef ANSI
PUBLIC S16 cmPkCpjBndReq
(
Pst * pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkCpjBndReq(pst, suId, spId)
Pst * pst;
SuId suId;
SpId spId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjBndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ001, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ002, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ003, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCPJBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjBndReq
(
CpjBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjBndReq(func, pst, mBuf)
CpjBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   SpId spId;
   
   TRC3(cmUnpkCpjBndReq)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ004, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ005, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, spId));
}

#ifdef ANSI
PUBLIC S16 cmPkCpjBndCfm
(
Pst * pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkCpjBndCfm(pst, suId, status)
Pst * pst;
SuId suId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjBndCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ006, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ007, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ008, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCPJBNDCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjBndCfm
(
CpjBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjBndCfm(func, pst, mBuf)
CpjBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U8 status;
   
   TRC3(cmUnpkCpjBndCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ009, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&status, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ010, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, status));
}

#ifdef ANSI
PUBLIC S16 cmPkCpjUbndReq
(
Pst * pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkCpjUbndReq(pst, spId, reason)
Pst * pst;
SpId spId;
Reason reason;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjUbndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ011, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(reason, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ012, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ013, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCPJUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjUbndReq
(
CpjUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjUbndReq(func, pst, mBuf)
CpjUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   Reason reason;
   
   TRC3(cmUnpkCpjUbndReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ014, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&reason, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ015, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, reason));
}

#ifdef ANSI
PUBLIC S16 cmPkCpjCfgReq
(
Pst * pst,
SpId spId,
CpjCfgReqInfo * cfgReq
)
#else
PUBLIC S16 cmPkCpjCfgReq(pst, spId, cfgReq)
Pst * pst;
SpId spId;
CpjCfgReqInfo * cfgReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ016, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReq, sizeof(CpjCfgReqInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjCfgReqInfo(pst, cfgReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ017, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)cfgReq, sizeof(CpjCfgReqInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ019, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReq, sizeof(CpjCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Request Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)cfgReq, sizeof(CpjCfgReqInfo));

   pst->event = (Event) EVTCPJCFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjCfgReq
(
CpjCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjCfgReq(func, pst, mBuf)
CpjCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SpId spId;
   CpjCfgReqInfo *cfgReq;
   
   TRC3(cmUnpkCpjCfgReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ021, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&cfgReq,\
               sizeof(CpjCfgReqInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjCfgReqInfo(pst, cfgReq, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReq, sizeof(CpjCfgReqInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ023, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, cfgReq));
}

#ifdef ANSI
PUBLIC S16 cmPkCpjCfgCfm
(
Pst * pst,
SuId suId,
CpjCfgCfmInfo * cfgCfm
)
#else
PUBLIC S16 cmPkCpjCfgCfm(pst, suId, cfgCfm)
Pst * pst;
SuId suId;
CpjCfgCfmInfo * cfgCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ024, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgCfm, sizeof(CpjCfgCfmInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjCfgCfmInfo(cfgCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ025, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)cfgCfm, sizeof(CpjCfgCfmInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ027, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgCfm, sizeof(CpjCfgCfmInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* cpj_c_001.main_3 */
   /* Free Confirm Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)cfgCfm, sizeof(CpjCfgCfmInfo));

   pst->event = (Event) EVTCPJCFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjCfgCfm
(
CpjCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjCfgCfm(func, pst, mBuf)
CpjCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SuId suId;
   CpjCfgCfmInfo *cfgCfm;
   
   TRC3(cmUnpkCpjCfgCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ029, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&cfgCfm,\
               sizeof(CpjCfgCfmInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjCfgCfmInfo(cfgCfm, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)cfgCfm, sizeof(CpjCfgCfmInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ031, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, cfgCfm));
}

#ifdef ANSI
PUBLIC S16 cmPkCpjReEstReq
(
Pst * pst,
SpId spId,
CpjReEstReqInfo * reEstReq
)
#else
PUBLIC S16 cmPkCpjReEstReq(pst, spId, reEstReq)
Pst * pst;
SpId spId;
CpjReEstReqInfo * reEstReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjReEstReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ032, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)reEstReq, sizeof(CpjReEstReqInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjReEstReqInfo(reEstReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ033, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)reEstReq, sizeof(CpjReEstReqInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ035, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)reEstReq, sizeof(CpjReEstReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Request Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)reEstReq, sizeof(CpjReEstReqInfo));

   pst->event = (Event) EVTCPJREESTREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjReEstReq
(
CpjReEstReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjReEstReq(func, pst, mBuf)
CpjReEstReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SpId spId;
   CpjReEstReqInfo *reEstReq;
   
   TRC3(cmUnpkCpjReEstReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ037, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&reEstReq,\
               sizeof(CpjReEstReqInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjReEstReqInfo(reEstReq, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)reEstReq, sizeof(CpjReEstReqInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ039, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, reEstReq));
}

#ifdef ANSI
PUBLIC S16 cmPkCpjReEstCfm
(
Pst * pst,
SuId suId,
CpjReEstCfmInfo * reEstCfm
)
#else
PUBLIC S16 cmPkCpjReEstCfm(pst, suId, reEstCfm)
Pst * pst;
SuId suId;
CpjReEstCfmInfo * reEstCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjReEstCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ040, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)reEstCfm, sizeof(CpjReEstCfmInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjReEstCfmInfo(reEstCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ041, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)reEstCfm, sizeof(CpjReEstCfmInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ043, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)reEstCfm, sizeof(CpjReEstCfmInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Confirm Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)reEstCfm, sizeof(CpjReEstCfmInfo));

   pst->event = (Event) EVTCPJREESTCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjReEstCfm
(
CpjReEstCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjReEstCfm(func, pst, mBuf)
CpjReEstCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SuId suId;
   CpjReEstCfmInfo *reEstCfm;
   
   TRC3(cmUnpkCpjReEstCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ045, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&reEstCfm,\
               sizeof(CpjReEstCfmInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjReEstCfmInfo(reEstCfm, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)reEstCfm, sizeof(CpjReEstCfmInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ047, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, reEstCfm));
}

#ifdef ANSI
PUBLIC S16 cmPkCpjSecCfgReq
(
Pst * pst,
SpId spId,
CpjSecCfgReqInfo * secCfgReq
)
#else
PUBLIC S16 cmPkCpjSecCfgReq(pst, spId, secCfgReq)
Pst * pst;
SpId spId;
CpjSecCfgReqInfo * secCfgReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjSecCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ048, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)secCfgReq, sizeof(CpjSecCfgReqInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjSecCfgReqInfo(secCfgReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ049, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)secCfgReq, sizeof(CpjSecCfgReqInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ051, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)secCfgReq, sizeof(CpjSecCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Request Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)secCfgReq, sizeof(CpjSecCfgReqInfo));

   pst->event = (Event) EVTCPJSECCFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjSecCfgReq
(
CpjSecCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjSecCfgReq(func, pst, mBuf)
CpjSecCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SpId spId;
   CpjSecCfgReqInfo *secCfgReq;
   
   TRC3(cmUnpkCpjSecCfgReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ053, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&secCfgReq,\
               sizeof(CpjSecCfgReqInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjSecCfgReqInfo(secCfgReq, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)secCfgReq, sizeof(CpjSecCfgReqInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ055, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, secCfgReq));
}

#ifdef ANSI
PUBLIC S16 cmPkCpjSecCfgCfm
(
Pst * pst,
SuId suId,
CpjSecCfgCfmInfo * secCfgCfm
)
#else
PUBLIC S16 cmPkCpjSecCfgCfm(pst, suId, secCfgCfm)
Pst * pst;
SuId suId;
CpjSecCfgCfmInfo * secCfgCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjSecCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ056, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)secCfgCfm, sizeof(CpjSecCfgCfmInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjSecCfgCfmInfo(secCfgCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ057, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)secCfgCfm, sizeof(CpjSecCfgCfmInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ059, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)secCfgCfm, sizeof(CpjSecCfgCfmInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Confirm Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)secCfgCfm, sizeof(CpjSecCfgCfmInfo));

   pst->event = (Event) EVTCPJSECCFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjSecCfgCfm
(
CpjSecCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjSecCfgCfm(func, pst, mBuf)
CpjSecCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SuId suId;
   CpjSecCfgCfmInfo *secCfgCfm;
   
   TRC3(cmUnpkCpjSecCfgCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ061, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&secCfgCfm,\
               sizeof(CpjSecCfgCfmInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjSecCfgCfmInfo(secCfgCfm, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)secCfgCfm, sizeof(CpjSecCfgCfmInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ063, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, secCfgCfm));
}

#ifdef ANSI
PUBLIC S16 cmPkCpjUeIdChgReq
(
Pst * pst,
SpId spId,
U32 transId,
CpjUeInfo * oldUeInfo,
CpjUeInfo * newUeInfo
)
#else
PUBLIC S16 cmPkCpjUeIdChgReq(pst, spId, transId, oldUeInfo, newUeInfo)
Pst * pst;
SpId spId;
U32 transId;
CpjUeInfo * oldUeInfo;
CpjUeInfo * newUeInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjUeIdChgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ064, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)oldUeInfo, sizeof(CpjUeInfo));
      SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CpjUeInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjUeInfo(newUeInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ065, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)oldUeInfo, sizeof(CpjUeInfo));
         SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CpjUeInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (cmPkCpjUeInfo(oldUeInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ067, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)oldUeInfo, sizeof(CpjUeInfo));
         SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CpjUeInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkU32(transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ069, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)oldUeInfo, sizeof(CpjUeInfo));
      SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CpjUeInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ070, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)oldUeInfo, sizeof(CpjUeInfo));
      SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CpjUeInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Request Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)oldUeInfo, sizeof(CpjUeInfo));
   SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CpjUeInfo));

   pst->event = (Event) EVTCPJUEIDCHGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjUeIdChgReq
(
CpjUeIdChgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjUeIdChgReq(func, pst, mBuf)
CpjUeIdChgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16 ret1;
   SpId spId;
   U32 transId;
   CpjUeInfo *oldUeInfo;
   CpjUeInfo *newUeInfo;
   
   TRC3(cmUnpkCpjUeIdChgReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ073, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU32(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ074, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

    if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&oldUeInfo,\
                sizeof(CpjUeInfo))) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

   if (cmUnpkCpjUeInfo(oldUeInfo, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)oldUeInfo, sizeof(CpjUeInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ076, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&newUeInfo,\
               sizeof(CpjUeInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjUeInfo(newUeInfo, mBuf) != ROK)
   {
      SPutSBuf(pst->region, pst->pool, (Data *)oldUeInfo, sizeof(CpjUeInfo));
      SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CpjUeInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ078, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, transId, oldUeInfo, newUeInfo));
}

#ifdef ANSI
PUBLIC S16 cmPkCpjUeIdChgCfm
(
Pst * pst,
SuId suId,
U32 transId,
CpjUeInfo  * ueInfo,
CmStatus status
)
#else
PUBLIC S16 cmPkCpjUeIdChgCfm(pst, suId, transId, ueInfo, status)
Pst * pst;
SuId suId;
U32 transId;
CpjUeInfo  * ueInfo;
CmStatus status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjUeIdChgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ079, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CpjUeInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCmStatus(&status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ080, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CpjUeInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkCpjUeInfo(ueInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ081, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CpjUeInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkU32(transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ083, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CpjUeInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ084, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CpjUeInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Confirm Structure after packing */
#if 0
   SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CpjUeInfo));
#else
   SPutStaticBuffer(pst->region, pst->pool, (Data *)ueInfo, sizeof(CpjUeInfo),SS_SHARABLE_MEMORY); 
#endif
   pst->event = (Event) EVTCPJUEIDCHGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjUeIdChgCfm
(
CpjUeIdChgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjUeIdChgCfm(func, pst, mBuf)
CpjUeIdChgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SuId suId;
   U32 transId;
   CpjUeInfo *ueInfo;
   CmStatus status;
   
   TRC3(cmUnpkCpjUeIdChgCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ086, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU32(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ087, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&ueInfo,\
               sizeof(CpjUeInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjUeInfo(ueInfo, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CpjUeInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ089, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkCmStatus(&status, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CpjUeInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ090, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, transId, ueInfo, status));
}

#ifdef ANSI
PUBLIC S16 cmPkCpjCountReq
(
Pst * pst,
SpId spId,
CpjCountReqInfo * countReq
)
#else
PUBLIC S16 cmPkCpjCountReq(pst, spId, countReq)
Pst * pst;
SpId spId;
CpjCountReqInfo * countReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjCountReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ091, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)countReq, sizeof(CpjCountReqInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjCountReqInfo(countReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ092, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)countReq, sizeof(CpjCountReqInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ094, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)countReq, sizeof(CpjCountReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Request Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)countReq, sizeof(CpjCountReqInfo));

   pst->event = (Event) EVTCPJCOUNTREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjCountReq
(
CpjCountReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjCountReq(func, pst, mBuf)
CpjCountReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SpId spId;
   CpjCountReqInfo *countReq;
   
   TRC3(cmUnpkCpjCountReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ096, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&countReq,\
               sizeof(CpjCountReqInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjCountReqInfo(countReq, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)countReq, sizeof(CpjCountReqInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ098, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, countReq));
}

#ifdef ANSI
PUBLIC S16 cmPkCpjCountCfm
(
Pst * pst,
SuId suId,
CpjCountCfmInfo * countCfm
)
#else
PUBLIC S16 cmPkCpjCountCfm(pst, suId, countCfm)
Pst * pst;
SuId suId;
CpjCountCfmInfo * countCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjCountCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ099, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)countCfm, sizeof(CpjCountCfmInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjCountCfmInfo(countCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ100, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)countCfm, sizeof(CpjCountCfmInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ102, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)countCfm, sizeof(CpjCountCfmInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Confirm Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)countCfm, sizeof(CpjCountCfmInfo));

   pst->event = (Event) EVTCPJCOUNTCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjCountCfm
(
CpjCountCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjCountCfm(func, pst, mBuf)
CpjCountCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SuId suId;
   CpjCountCfmInfo *countCfm;
   
   TRC3(cmUnpkCpjCountCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ104, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&countCfm,\
               sizeof(CpjCountCfmInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjCountCfmInfo(countCfm, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)countCfm, sizeof(CpjCountCfmInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ106, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, countCfm));
}

/****************************************************************/
/* Data Forwarding func */
#ifdef ANSI
PUBLIC S16 cmPkCpjStartDataFwdReq
(
Pst * pst,
SpId spId,
CpjDataFwdReqInfo * dataFwdReq
)
#else
PUBLIC S16 cmPkCpjStartDataFwdReq(pst, spId, dataFwdReq)
Pst * pst;
SpId spId;
CpjDataFwdReqInfo *dataFwdReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjStartDataFwdReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ107, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)dataFwdReq, sizeof(CpjDataFwdReqInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjStartDataFwdReqInfo(dataFwdReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ108, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)dataFwdReq, sizeof(CpjDataFwdReqInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ110, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)dataFwdReq, sizeof(CpjDataFwdReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Request Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)dataFwdReq, sizeof(CpjDataFwdReqInfo));

   pst->event = (Event) EVTCPJSTARTDATAFWDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjStartDataFwdReq
(
CpjDataFwdReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjStartDataFwdReq(func, pst, mBuf)
CpjDataFwdReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SpId spId;
   CpjDataFwdReqInfo *dataFwdReq;
   
   TRC3(cmUnpkCpjStartDataFwdReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ112, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&dataFwdReq,\
               sizeof(CpjDataFwdReqInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjStartDataFwdReqInfo(dataFwdReq, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)dataFwdReq, sizeof(CpjDataFwdReqInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ114, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, dataFwdReq));
}

/* Data Resume func */

#ifdef ANSI
PUBLIC S16 cmPkCpjDatResumeReq
(
Pst * pst,
SpId spId,
CpjDatResumeReqInfo * dataResReq
)
#else
PUBLIC S16 cmPkCpjDatResumeReq(pst, spId, dataResReq)
Pst * pst;
SpId spId;
CpjDatResumeReqInfo *dataResReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjDatResumeReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ107, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)dataResReq, sizeof(CpjDatResumeReqInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjDatResumeReqInfo(dataResReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ108, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)dataResReq, sizeof(CpjDatResumeReqInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ110, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)dataResReq, sizeof(CpjDatResumeReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Request Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)dataResReq, sizeof(CpjDatResumeReqInfo));

   pst->event = (Event) EVTCPJDATRESUMEREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


#ifdef ANSI
PUBLIC S16 cmUnpkCpjDatResumeReq
(
CpjDatResumeReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjDatResumeReq(func, pst, mBuf)
CpjDatResumeReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SpId spId;
   CpjDatResumeReqInfo *dataResReq;
   
   TRC3(cmUnpkCpjDatResumeReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ112, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&dataResReq,\
               sizeof(CpjDatResumeReqInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjDatResumeReqInfo(dataResReq, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)dataResReq, sizeof(CpjDatResumeReqInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ114, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, dataResReq));
}
/****************************************************************/

#ifdef ANSI
PUBLIC S16 cmPkCpjSduStaReq
(
Pst * pst,
SpId spId,
CpjSduStaReqInfo * staReq
)
#else
PUBLIC S16 cmPkCpjSduStaReq(pst, spId, staReq)
Pst * pst;
SpId spId;
CpjSduStaReqInfo * staReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjSduStaReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ107, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)staReq, sizeof(CpjSduStaReqInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjSduStaReqInfo(staReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ108, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)staReq, sizeof(CpjSduStaReqInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ110, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)staReq, sizeof(CpjSduStaReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Request Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)staReq, sizeof(CpjSduStaReqInfo));

   pst->event = (Event) EVTCPJSDUSTAREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjSduStaReq
(
CpjSduStaReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjSduStaReq(func, pst, mBuf)
CpjSduStaReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SpId spId;
   CpjSduStaReqInfo *staReq;
   
   TRC3(cmUnpkCpjSduStaReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ112, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&staReq,\
               sizeof(CpjSduStaReqInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjSduStaReqInfo(staReq, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)staReq, sizeof(CpjSduStaReqInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ114, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, staReq));
}

#ifdef ANSI
PUBLIC S16 cmPkCpjSduStaCfm
(
Pst * pst,
SuId suId,
CpjSduStaCfmInfo * staCfm
)
#else
PUBLIC S16 cmPkCpjSduStaCfm(pst, suId, staCfm)
Pst * pst;
SuId suId;
CpjSduStaCfmInfo * staCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjSduStaCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ115, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)staCfm, sizeof(CpjSduStaCfmInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjSduStaCfmInfo(pst, staCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ116, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)staCfm, sizeof(CpjSduStaCfmInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ118, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)staCfm, sizeof(CpjSduStaCfmInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Confirm Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)staCfm, sizeof(CpjSduStaCfmInfo));

   pst->event = (Event) EVTCPJSDUSTACFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjSduStaCfm
(
CpjSduStaCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjSduStaCfm(func, pst, mBuf)
CpjSduStaCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SuId suId;
   CpjSduStaCfmInfo *staCfm;
   
   TRC3(cmUnpkCpjSduStaCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ120, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&staCfm,\
               sizeof(CpjSduStaCfmInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjSduStaCfmInfo(pst, staCfm, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)staCfm, sizeof(CpjSduStaCfmInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ122, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, staCfm));
}

/* Data Resume Confirm */

#ifdef ANSI
PUBLIC S16 cmPkCpjDatResumeCfm
(
Pst * pst,
SuId suId,
CpjDatResumeCfmInfo * dataResCfm
)
#else
PUBLIC S16 cmPkCpjDatResumeCfm(pst, suId, dataResCfm)
Pst * pst;
SuId suId;
CpjDatResumeCfmInfo * dataResCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjDatResumeCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ115, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)dataResCfm, sizeof(CpjDatResumeCfmInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCpjDataResCfmInfo(pst, dataResCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ116, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)dataResCfm, sizeof(CpjDatResumeCfmInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ118, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)dataResCfm, sizeof(CpjDatResumeCfmInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Confirm Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)dataResCfm, sizeof(CpjDatResumeCfmInfo));

   pst->event = (Event) EVTCPJDATRESUMECFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCpjDatResumeCfm
(
CpjDatResumeCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjDatResumeCfm(func, pst, mBuf)
CpjDatResumeCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SuId suId;
   CpjDatResumeCfmInfo *dataResCfm;
   
   TRC3(cmUnpkCpjSduStaCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ120, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&dataResCfm,\
               sizeof(CpjDatResumeCfmInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cmUnpkCpjDatResumeCfmInfo(pst, dataResCfm, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)dataResCfm, sizeof(CpjDatResumeCfmInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ122, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, dataResCfm));
}


/***********************************************************
*
*     Func : cmPkCpjRlcAm
*
*
*     Desc :  * RLC parameter information in AM mode.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjRlcAm
(
CpjRlcAm *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjRlcAm(param, mBuf)
CpjRlcAm *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjRlcAm)

   CMCHKPK(SPkU8, param->statusRepReqd, mBuf);
   CMCHKPK(SPkU8, param->pdcpSNSize, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjRlcAm
*
*
*     Desc :  * RLC parameter information in AM mode.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjRlcAm
(
CpjRlcAm *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjRlcAm(param, mBuf)
CpjRlcAm *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjRlcAm)

   CMCHKUNPK(SUnpkU8, &param->pdcpSNSize, mBuf);
   CMCHKUNPK(SUnpkU8, &param->statusRepReqd, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjRlcUm
*
*
*     Desc : * RLC parameter information in UM mode.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjRlcUm
(
CpjRlcUm *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjRlcUm(param, mBuf)
CpjRlcUm *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjRlcUm)

   CMCHKPK(SPkU8, param->pdcpSNSize, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjRlcUm
*
*
*     Desc : * RLC parameter information in UM mode.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjRlcUm
(
CpjRlcUm *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjRlcUm(param, mBuf)
CpjRlcUm *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjRlcUm)

   CMCHKUNPK(SUnpkU8, &param->pdcpSNSize, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjRlcInfo
*
*
*     Desc : * Mapped RLC entity information in RLC for the PDCP entity
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjRlcInfo
(
CpjRlcInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjRlcInfo(param, mBuf)
CpjRlcInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjRlcInfo)

      switch(param->mode) {
         case CM_LTE_MODE_UM:
            CMCHKPK(cmPkCpjRlcUm, &param->m.rlcUm, mBuf);
            break;
         case CM_LTE_MODE_AM:
            CMCHKPK(cmPkCpjRlcAm, &param->m.rlcAm, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->mode, mBuf);
   CMCHKPK(SPkU8, param->dir, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjRlcInfo
*
*
*     Desc : * Mapped RLC entity information in RLC for the PDCP entity
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjRlcInfo
(
CpjRlcInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjRlcInfo(param, mBuf)
CpjRlcInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjRlcInfo)

   CMCHKUNPK(SUnpkU8, &param->dir, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mode, mBuf);
      switch(param->mode) {
         case CM_LTE_MODE_AM:
            CMCHKUNPK(cmUnpkCpjRlcAm, &param->m.rlcAm, mBuf);
            break;
         case CM_LTE_MODE_UM:
            CMCHKUNPK(cmUnpkCpjRlcUm, &param->m.rlcUm, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjCipherInfo
*
*
*     Desc : * Ciphering information to be configured per UE in PDCP.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjCipherInfo
(
CpjCipherInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjCipherInfo(param, mBuf)
CpjCipherInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkCpjCipherInfo);

   CMCHKPK(SPkU8, param->algoType, mBuf);
   for (i=CPJ_CIPHER_KEY_LEN-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->usrplnKey[i], mBuf);
   }
   for (i=CPJ_CIPHER_KEY_LEN-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->ctrlplnKey[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjCipherInfo
*
*
*     Desc : * Ciphering information to be configured per UE in PDCP.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjCipherInfo
(
CpjCipherInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjCipherInfo(param, mBuf)
CpjCipherInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkCpjCipherInfo)

   for (i=0; i<CPJ_CIPHER_KEY_LEN; i++) {
      CMCHKUNPK(SUnpkU8, &param->ctrlplnKey[i], mBuf);
   }
   for (i=0; i<CPJ_CIPHER_KEY_LEN; i++) {
      CMCHKUNPK(SUnpkU8, &param->usrplnKey[i], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->algoType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjIntegInfo
*
*
*     Desc : * Integrity protection paramater information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjIntegInfo
(
CpjIntegInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjIntegInfo(param, mBuf)
CpjIntegInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkCpjIntegInfo)

   for (i=CPJ_INTG_KEY_LEN-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->intKey[i], mBuf);
   }
   CMCHKPK(SPkU8, param->algoType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjIntegInfo
*
*
*     Desc : * Integrity protection paramater information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjIntegInfo
(
CpjIntegInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjIntegInfo(param, mBuf)
CpjIntegInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkCpjIntegInfo)

   CMCHKUNPK(SUnpkU8, &param->algoType, mBuf);
   for (i=0; i<CPJ_INTG_KEY_LEN; i++) {
      CMCHKUNPK(SUnpkU8, &param->intKey[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjSecCfg
*
*
*     Desc : * PDCP Security configuration parameter.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjSecCfg
(
CpjSecCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjSecCfg(param, mBuf)
CpjSecCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjSecCfg)

   CMCHKPK(cmPkCpjCipherInfo, &param->cipherInfo, mBuf);
   CMCHKPK(cmPkCpjIntegInfo, &param->integInfo, mBuf);
   CMCHKPK(SPkU8, param->selSecAct, mBuf);
   CMCHKPK(SPkU8, param->isHo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjSecCfg
*
*
*     Desc : * PDCP Security configuration parameter.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjSecCfg
(
CpjSecCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjSecCfg(param, mBuf)
CpjSecCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjSecCfg)

   CMCHKUNPK(SUnpkU8, &param->isHo, mBuf);
   CMCHKUNPK(SUnpkU8, &param->selSecAct, mBuf);
   CMCHKUNPK(cmUnpkCpjIntegInfo, &param->integInfo, mBuf);
   CMCHKUNPK(cmUnpkCpjCipherInfo, &param->cipherInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjRohcInfo
*
*
*     Desc : * ROHC compression protocol information structure.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjRohcInfo
(
CpjRohcInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjRohcInfo(param, mBuf)
CpjRohcInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkCpjRohcInfo)

   for (i=CPJ_MAX_ROHC_PROF_LIST-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->profLst[i], mBuf);
   }
   CMCHKPK(SPkU16, param->maxCid, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjRohcInfo
*
*
*     Desc : * ROHC compression protocol information structure.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjRohcInfo
(
CpjRohcInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjRohcInfo(param, mBuf)
CpjRohcInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkCpjRohcInfo)

   CMCHKUNPK(SUnpkU16, &param->maxCid, mBuf);
   for (i=0; i<CPJ_MAX_ROHC_PROF_LIST; i++) {
      CMCHKUNPK(SUnpkU8, &param->profLst[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjHdrCompCfg
*
*
*     Desc : * ROHC configuration information for PDCP entity.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjHdrCompCfg
(
CpjHdrCompCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjHdrCompCfg(param, mBuf)
CpjHdrCompCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjHdrCompCfg)

   CMCHKPK(cmPkCpjRohcInfo, &param->rohcInfo, mBuf);
   CMCHKPK(SPkU8, param->hdrCompUsed, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjHdrCompCfg
*
*
*     Desc : * ROHC configuration information for PDCP entity.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjHdrCompCfg
(
CpjHdrCompCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjHdrCompCfg(param, mBuf)
CpjHdrCompCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjHdrCompCfg)

   CMCHKUNPK(SUnpkU8, &param->hdrCompUsed, mBuf);
   CMCHKUNPK(cmUnpkCpjRohcInfo, &param->rohcInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjHoInfo
*
*
*     Desc : * Handover Information for RB.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjHoInfo
(
Pst *pst,
CpjHoInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjHoInfo(pst, param, mBuf)
   Pst *pst;
   CpjHoInfo *param;
   Buffer *mBuf;
#endif
{
   S16   cnt, idx;

   TRC3(cmPkCpjHoInfo)

      cnt = param->numBits/8;
   if (cnt % 8)
   {
      cnt++;
   }
   for (idx = cnt-1; idx >= 0; idx--)
   {
      CMCHKPK(SPkU8, param->ulBitMap[idx], mBuf);
   }

   /* Free ulBitMap after packing */
   if (cnt)
      SPutSBuf(pst->region, pst->pool, (Data *)param->ulBitMap, cnt * sizeof(U8));

   CMCHKPK(SPkU16, param->numBits, mBuf);
   CMCHKPK(SPkU32, param->ulCount, mBuf);
   CMCHKPK(SPkU32, param->dlCount, mBuf);
   CMCHKPK(SPkU8, param->snLen, mBuf);
   CMCHKPK(SPkU8, param->isHoPres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
 *
 *     Func : cmUnpkCpjHoInfo
 *
 *
 *     Desc : * Handover Information for RB.
 *
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjHoInfo
(
Pst *pst,
CpjHoInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjHoInfo(pst, param, mBuf)
Pst *pst;
CpjHoInfo *param;
Buffer *mBuf;
#endif
{
   S16   cnt, idx;
   S16   ret1 = ROK;

   TRC3(cmUnpkCpjHoInfo)

   CMCHKUNPK(SUnpkU8, &param->isHoPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->snLen, mBuf);
   CMCHKUNPK(SUnpkU32, &param->dlCount, mBuf);
   CMCHKUNPK(SUnpkU32, &param->ulCount, mBuf);
   CMCHKUNPK(SUnpkU16, &param->numBits, mBuf);
   if (param->numBits % 8 == 0)
      cnt = param->numBits/8;
   else
      cnt = param->numBits/8 + 1;
   if(cnt && (ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&param->ulBitMap,\
               cnt * sizeof(U8))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cnt == 0)
      param->ulBitMap = NULLP;

   for (idx = 0; idx < cnt; idx++)
   {
      CMCHKUNPK(SUnpkU8, &param->ulBitMap[idx], mBuf);
   }

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjCfgEnt
*
*
*     Desc : * Configuration structure for PDCP entity.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjCfgEnt
(
Pst *pst,
CpjCfgEnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjCfgEnt(pst, param, mBuf)
Pst *pst;
CpjCfgEnt *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkCpjCfgEnt)

      switch(param->cfgType) {
         case CPJ_CFG_MODIFY:
            if (cmPkCpjModCfgEnt(pst, &param->m.modCfg, mBuf) != ROK)
               RETVALUE(RFAILED);
            break;
         case CPJ_CFG_ADD:
            CMCHKPK(cmPkCpjAddCfgEnt, &param->m.addCfg, mBuf);
            break;
      }
   CMCHKPK(SPkU8, param->cfgType, mBuf);
   CMCHKPK(SPkU8, param->rbType, mBuf);
   CMCHKPK(SPkU8, param->rbId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjCfgEnt
*
*
*     Desc : * Configuration structure for PDCP entity.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjCfgEnt
(
Pst *pst,
CpjCfgEnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjCfgEnt(pst, param, mBuf)
Pst *pst;
CpjCfgEnt *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkCpjCfgEnt)

   CMCHKUNPK(SUnpkU8, &param->rbId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rbType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cfgType, mBuf);
      switch(param->cfgType) {
         case CPJ_CFG_ADD:
            CMCHKUNPK(cmUnpkCpjAddCfgEnt, &param->m.addCfg, mBuf);
            break;
         case CPJ_CFG_MODIFY:
            if (cmUnpkCpjModCfgEnt(pst, &param->m.modCfg, mBuf) != ROK)
               RETVALUE(RFAILED);
            break;
      }
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkCpjAddCfgEnt
(
CpjAddCfgEnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjAddCfgEnt(param, mBuf)
CpjAddCfgEnt *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjAddCfgEnt)

   CMCHKPK(cmPkCpjHdrCompCfg, &param->hdrCompCfg, mBuf);
   CMCHKPK(SPkS16, param->discardTmr, mBuf);
   CMCHKPK(cmPkCpjRlcInfo, &param->rlcInfo, mBuf);
   /* cpj_c_001.main_4 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   CMCHKPK(SPkU8, param->qci, mBuf);
#endif /* LTE_L2_MEAS */
   CMCHKPK(SPkU8, param->cfmReqd, mBuf);
   CMCHKPK(SPkU8, param->discReqd, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkCpjAddCfgEnt
(
CpjAddCfgEnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjAddCfgEnt(param, mBuf)
CpjAddCfgEnt *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjAddCfgEnt)

   CMCHKUNPK(SUnpkU8, &param->discReqd, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cfmReqd, mBuf);
   /* cpj_c_001.main_4 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   CMCHKUNPK(SUnpkU8, &param->qci, mBuf);
#endif /* LTE_L2_MEAS */
   CMCHKUNPK(cmUnpkCpjRlcInfo, &param->rlcInfo, mBuf);
   CMCHKUNPK(SUnpkS16, &param->discardTmr, mBuf);
   CMCHKUNPK(cmUnpkCpjHdrCompCfg, &param->hdrCompCfg, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkCpjModCfgEnt
(
Pst *pst,
CpjModCfgEnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjModCfgEnt(pst, param, mBuf)
Pst *pst;
CpjModCfgEnt *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkCpjModCfgEnt)

   if (cmPkCpjHoInfo(pst, &param->hoInfo, mBuf) != ROK)
      RETVALUE(RFAILED);
   CMCHKPK(cmPkCpjHdrCompCfg, &param->hdrCompCfg, mBuf);
   CMCHKPK(SPkU8, param->cfmReqd, mBuf);
   CMCHKPK(SPkU8, param->discReqd, mBuf);
   CMCHKPK(SPkU8, param->bitFlag, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkCpjModCfgEnt
(
Pst *pst,
CpjModCfgEnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjModCfgEnt(pst, param, mBuf)
Pst *pst;
CpjModCfgEnt *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkCpjModCfgEnt)

   CMCHKUNPK(SUnpkU8, &param->bitFlag, mBuf);
   CMCHKUNPK(SUnpkU8, &param->discReqd, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cfmReqd, mBuf);
   CMCHKUNPK(cmUnpkCpjHdrCompCfg, &param->hdrCompCfg, mBuf);
   if (cmUnpkCpjHoInfo(pst, &param->hoInfo, mBuf) != ROK)
      RETVALUE(RFAILED);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjCfgReqInfo
*
*
*     Desc : * PDCP Configuration structure. Parameters are filled by RRC 
   layer while configuring the PDCP layer.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjCfgReqInfo
(
Pst *pst,
CpjCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjCfgReqInfo(pst, param, mBuf)
Pst *pst;
CpjCfgReqInfo *param;
Buffer *mBuf;
#endif
{
   S32 i;

   TRC3(cmPkCpjCfgReqInfo)

   for (i=param->numEnt-1; i >= 0; i--) {
      if (cmPkCpjCfgEnt(pst, &param->cfgEnt[i], mBuf) != ROK)
         RETVALUE(RFAILED);
   }
#ifdef TENB_MULT_CELL_SUPPRT
   CMCHKPK(SPkS16, param->rlcUlSapId, mBuf);
   CMCHKPK(SPkS16, param->rlcDlSapId, mBuf);
#endif /* TENB_MULT_CELL_SUPPRT */

   CMCHKPK(SPkU8, param->isHo, mBuf);
   CMCHKPK(SPkU8, param->numEnt, mBuf);
   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjCfgReqInfo
*
*
*     Desc : * PDCP Configuration structure. Parameters are filled by RRC 
   layer while configuring the PDCP layer.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjCfgReqInfo
(
Pst *pst,
CpjCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjCfgReqInfo(pst, param, mBuf)
Pst *pst;
CpjCfgReqInfo *param;
Buffer *mBuf;
#endif
{
   S32 i;

   TRC3(cmUnpkCpjCfgReqInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numEnt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isHo, mBuf);

#ifdef TENB_MULT_CELL_SUPPRT
   CMCHKUNPK(SUnpkS16, &param->rlcDlSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->rlcUlSapId, mBuf);
#endif /* TENB_MULT_CELL_SUPPRT */

   for (i=0; i<param->numEnt; i++) {
      if (cmUnpkCpjCfgEnt(pst, &param->cfgEnt[i], mBuf) != ROK)
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjCfmEnt
*
*
*     Desc : * PDCP confirm parameter structure for PDCP entity.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjCfmEnt
(
CpjCfmEnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjCfmEnt(param, mBuf)
CpjCfmEnt *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjCfmEnt)

   CMCHKPK(SPkS16, param->reason, mBuf);
   CMCHKPK(SPkS16, param->status, mBuf);
   CMCHKPK(SPkU8, param->rbType, mBuf);
   CMCHKPK(SPkU8, param->rbId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjCfmEnt
*
*
*     Desc : * PDCP confirm parameter structure for PDCP entity.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjCfmEnt
(
CpjCfmEnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjCfmEnt(param, mBuf)
CpjCfmEnt *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjCfmEnt)

   CMCHKUNPK(SUnpkU8, &param->rbId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rbType, mBuf);
   CMCHKUNPK(SUnpkS16, &param->status, mBuf);
   CMCHKUNPK(SUnpkS16, &param->reason, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjCfgCfmInfo
*
*
*     Desc : * PDCP configuration confirm structure.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjCfgCfmInfo
(
CpjCfgCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjCfgCfmInfo(param, mBuf)
CpjCfgCfmInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkCpjCfgCfmInfo)

   for (i=param->numEnt-1; i >= 0; i--) {
      CMCHKPK(cmPkCpjCfmEnt, &param->cfmEnt[i], mBuf);
   }
   CMCHKPK(SPkU8, param->numEnt, mBuf);
   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjCfgCfmInfo
*
*
*     Desc : * PDCP configuration confirm structure.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjCfgCfmInfo
(
CpjCfgCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjCfgCfmInfo(param, mBuf)
CpjCfgCfmInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkCpjCfgCfmInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numEnt, mBuf);
   for (i=0; i<param->numEnt; i++) {
      CMCHKUNPK(cmUnpkCpjCfmEnt, &param->cfmEnt[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjReEstReqInfo
*
*
*     Desc : * Reestabishment request structure for SRB1 of an UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjReEstReqInfo
(
CpjReEstReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjReEstReqInfo(param, mBuf)
CpjReEstReqInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkCpjReEstReqInfo)

   for (i=CPJ_CIPHER_KEY_LEN-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->usrplnKey[i], mBuf);
   }
   for (i=CPJ_CIPHER_KEY_LEN-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->ctrlplnKey[i], mBuf);
   }
   for (i=CPJ_INTG_KEY_LEN-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->intKey[i], mBuf);
   }
   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLtePdcpId, &param->pdcpId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjReEstReqInfo
*
*
*     Desc : * Reestabishment request structure for SRB1 of an UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjReEstReqInfo
(
CpjReEstReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjReEstReqInfo(param, mBuf)
CpjReEstReqInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkCpjReEstReqInfo)

   CMCHKUNPK(cmUnpkLtePdcpId, &param->pdcpId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   for (i=0; i<CPJ_INTG_KEY_LEN; i++) {
      CMCHKUNPK(SUnpkU8, &param->intKey[i], mBuf);
   }
   for (i=0; i<CPJ_CIPHER_KEY_LEN; i++) {
      CMCHKUNPK(SUnpkU8, &param->ctrlplnKey[i], mBuf);
   }
   for (i=0; i<CPJ_CIPHER_KEY_LEN; i++) {
      CMCHKUNPK(SUnpkU8, &param->usrplnKey[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjReEstCfmInfo
*
*
*     Desc : * Reestablishment confirmation structure for an UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjReEstCfmInfo
(
CpjReEstCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjReEstCfmInfo(param, mBuf)
CpjReEstCfmInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjReEstCfmInfo)

   CMCHKPK(SPkS16, param->status, mBuf);
   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjReEstCfmInfo
*
*
*     Desc : * Reestablishment confirmation structure for an UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjReEstCfmInfo
(
CpjReEstCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjReEstCfmInfo(param, mBuf)
CpjReEstCfmInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjReEstCfmInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->status, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjSecCfgReqInfo
*
*
*     Desc : * PDCP Security Configuration structure. Parameters are filled by RRC
 * while configuring the security parameters.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjSecCfgReqInfo
(
CpjSecCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjSecCfgReqInfo(param, mBuf)
CpjSecCfgReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjSecCfgReqInfo)

   CMCHKPK(cmPkCpjSecCfg, &param->secCfg, mBuf);
   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjSecCfgReqInfo
*
*
*     Desc : * PDCP Security Configuration structure. Parameters are filled by RRC
 * while configuring the security parameters.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjSecCfgReqInfo
(
CpjSecCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjSecCfgReqInfo(param, mBuf)
CpjSecCfgReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjSecCfgReqInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   CMCHKUNPK(cmUnpkCpjSecCfg, &param->secCfg, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjSecCfgCfmInfo
*
*
*     Desc : * PDCP Security configuration confirm structure.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjSecCfgCfmInfo
(
CpjSecCfgCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjSecCfgCfmInfo(param, mBuf)
CpjSecCfgCfmInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjSecCfgCfmInfo)

   CMCHKPK(SPkS16, param->reason, mBuf);
   CMCHKPK(SPkS16, param->status, mBuf);
   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjSecCfgCfmInfo
*
*
*     Desc : * PDCP Security configuration confirm structure.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjSecCfgCfmInfo
(
CpjSecCfgCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjSecCfgCfmInfo(param, mBuf)
CpjSecCfgCfmInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjSecCfgCfmInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->status, mBuf);
   CMCHKUNPK(SUnpkS16, &param->reason, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjUeInfo
*
*
*     Desc : *  UE ID information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjUeInfo
(
CpjUeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjUeInfo(param, mBuf)
CpjUeInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjUeInfo)

   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjUeInfo
*
*
*     Desc : *  UE ID information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjUeInfo
(
CpjUeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjUeInfo(param, mBuf)
CpjUeInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjUeInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjCountReqInfo
*
*
*     Desc : *  PDCP Count Request Information from RRC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjCountReqInfo
(
CpjCountReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjCountReqInfo(param, mBuf)
CpjCountReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjCountReqInfo)

   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjCountReqInfo
*
*
*     Desc : *  PDCP Count Request Information from RRC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjCountReqInfo
(
CpjCountReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjCountReqInfo(param, mBuf)
CpjCountReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjCountReqInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjCountInfo
*
*
*     Desc : *  PDCP Count Information for a DRB.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjCountInfo
(
CpjCountInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjCountInfo(param, mBuf)
CpjCountInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjCountInfo)

   CMCHKPK(SPkU32, param->dlCount, mBuf);
   CMCHKPK(SPkU32, param->ulCount, mBuf);
   CMCHKPK(SPkU8, param->dir, mBuf);
   CMCHKPK(SPkU8, param->rbId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjCountInfo
*
*
*     Desc : *  PDCP Count Information for a DRB.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjCountInfo
(
CpjCountInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjCountInfo(param, mBuf)
CpjCountInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjCountInfo)

   CMCHKUNPK(SUnpkU8, &param->rbId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dir, mBuf);
   CMCHKUNPK(SUnpkU32, &param->ulCount, mBuf);
   CMCHKUNPK(SUnpkU32, &param->dlCount, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjCountCfmInfo
*
*
*     Desc : *  PDCP Count Request Confirmation to RRC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjCountCfmInfo
(
CpjCountCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjCountCfmInfo(param, mBuf)
CpjCountCfmInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkCpjCountCfmInfo)

   CMCHKPK(SPkS16, param->reason, mBuf);
   CMCHKPK(SPkS16, param->status, mBuf);
   for (i=param->numRb-1; i >= 0; i--) {
      CMCHKPK(cmPkCpjCountInfo, &param->countInfo[i], mBuf);
   }
   CMCHKPK(SPkU8, param->numRb, mBuf);
   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjCountCfmInfo
*
*
*     Desc : *  PDCP Count Request Confirmation to RRC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjCountCfmInfo
(
CpjCountCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjCountCfmInfo(param, mBuf)
CpjCountCfmInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkCpjCountCfmInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numRb, mBuf);
   for (i=0; i<param->numRb; i++) {
      CMCHKUNPK(cmUnpkCpjCountInfo, &param->countInfo[i], mBuf);
   }
   CMCHKUNPK(SUnpkS16, &param->status, mBuf);
   CMCHKUNPK(SUnpkS16, &param->reason, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjSduStaReqInfo
*
*
*     Desc : *  PDCP SDU Status Request Information from RRC - Used for reestablishment
 *  during handover.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjSduStaReqInfo
(
CpjSduStaReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjSduStaReqInfo(param, mBuf)
CpjSduStaReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjSduStaReqInfo)

   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjSduStaReqInfo
*
*
*     Desc : *  PDCP SDU Status Request Information from RRC - Used for reestablishment
 *  during handover.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjSduStaReqInfo
(
CpjSduStaReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjSduStaReqInfo(param, mBuf)
CpjSduStaReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjSduStaReqInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkCpjStartDataFwdReqInfo
*
*
*     Desc : *  PDCP Data Forward Request Information from RRC -
 *  during handover.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjStartDataFwdReqInfo
(
CpjDataFwdReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjStartDataFwdReqInfo(param, mBuf)
CpjDataFwdReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjStartDataFwdReqInfo)

   CMCHKPK(cmPkBool, param->isUlDatFwdReq, mBuf);
   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   RETVALUE(ROK);
}
/***********************************************************
*
*     Func : cmUnpkCpjStartDataFwdReqInfo
*
*
*     Desc : *  PDCP Data Forwarding Information from RRC - Used for HO
 *  during handover.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjStartDataFwdReqInfo
(
CpjDataFwdReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjStartDataFwdReqInfo(param, mBuf)
CpjDataFwdReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjStartDataFwdReqInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   CMCHKUNPK(cmUnpkBool, &param->isUlDatFwdReq, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmPkCpjDatResumeReqInfo
*
*
*     Desc : *  PDCP Data Resume Request Information from RRC -
 *  during handover.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjDatResumeReqInfo
(
CpjDatResumeReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjDatResumeReqInfo(param, mBuf)
CpjDatResumeReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjDatResumeReqInfo)

   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   RETVALUE(ROK);
}
/***********************************************************
*
*     Func : cmUnpkCpjDatResumeReqInfo
*
*
*     Desc : *  PDCP Data Resume Information from RRC - Used for HO
 *  during handover.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjDatResumeReqInfo
(
CpjDatResumeReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjDatResumeReqInfo(param, mBuf)
CpjDatResumeReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjDatResumeReqInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkCpjUlSduStaInfo
*
*
*     Desc : *  PDCP UL SDU Status Information for a DRB mapped to RLC AM.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjUlSduStaInfo
(
Pst *pst,
CpjUlSduStaInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjUlSduStaInfo(pst, param, mBuf)
Pst *pst;
CpjUlSduStaInfo *param;
Buffer *mBuf;
#endif
{
   S16   cnt, idx;

   TRC3(cmPkCpjUlSduStaInfo)

   CMCHKPK(SPkU32, param->count, mBuf);
   if (param->numBits % 8 == 0)
      cnt = param->numBits/8;
   else
      cnt = param->numBits/8 + 1;
   for (idx = cnt-1; idx >= 0; idx--)
   {
      CMCHKPK(SPkU8, param->ulBitMap[idx], mBuf);
   }

   /* Free ulBitMap after packing */
   if (cnt)
      SPutSBuf(pst->region, pst->pool, (Data *)param->ulBitMap, cnt * sizeof(U8));

   CMCHKPK(SPkU16, param->numBits, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjUlSduStaInfo
*
*
*     Desc : *  PDCP UL SDU Status Information for a DRB mapped to RLC AM.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjUlSduStaInfo
(
Pst *pst,
CpjUlSduStaInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjUlSduStaInfo(pst, param, mBuf)
Pst *pst;
CpjUlSduStaInfo *param;
Buffer *mBuf;
#endif
{
   S16   cnt, idx;
   S16   ret1 = ROK;

   TRC3(cmUnpkCpjUlSduStaInfo)

   CMCHKUNPK(SUnpkU16, &param->numBits, mBuf);
   if (param->numBits % 8 == 0)
      cnt = param->numBits/8;
   else
      cnt = param->numBits/8 + 1;

   if(cnt && (ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&param->ulBitMap,\
               cnt * sizeof(U8))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }

   if (cnt == 0)
      param->ulBitMap = NULLP;

   for (idx = 0; idx < cnt; idx++)
   {
      CMCHKUNPK(SUnpkU8, &param->ulBitMap[idx], mBuf);
   }

   CMCHKUNPK(SUnpkU32, &param->count, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjDlSduStaInfo
*
*
*     Desc : *  PDCP DL SDU Status Information for a DRB mapped to RLC AM.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjDlSduStaInfo
(
CpjDlSduStaInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjDlSduStaInfo(param, mBuf)
CpjDlSduStaInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjDlSduStaInfo)

   CMCHKPK(SPkU32, param->count, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjDlSduStaInfo
*
*
*     Desc : *  PDCP DL SDU Status Information for a DRB mapped to RLC AM.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjDlSduStaInfo
(
CpjDlSduStaInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjDlSduStaInfo(param, mBuf)
CpjDlSduStaInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjDlSduStaInfo)

   CMCHKUNPK(SUnpkU32, &param->count, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjSduStaInfo
*
*
*     Desc : *  PDCP SDU Status Information for a DRB mapped to RLC AM.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjSduStaInfo
(
Pst *pst,
CpjSduStaInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjSduStaInfo(pst, param, mBuf)
Pst *pst;
CpjSduStaInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkCpjSduStaInfo)

   CMCHKPK(cmPkCpjDlSduStaInfo, &param->dlSduStaInfo, mBuf);
   if (cmPkCpjUlSduStaInfo(pst, &param->ulSduStaInfo, mBuf) != ROK)
      RETVALUE(RFAILED);
   CMCHKPK(SPkU8, param->snLen, mBuf);
   CMCHKPK(SPkU8, param->dir, mBuf);
   CMCHKPK(SPkU8, param->rbId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjSduStaInfo
*
*
*     Desc : *  PDCP SDU Status Information for a DRB mapped to RLC AM.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjSduStaInfo
(
Pst *pst,
CpjSduStaInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjSduStaInfo(pst, param, mBuf)
Pst *pst;
CpjSduStaInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkCpjSduStaInfo)

   CMCHKUNPK(SUnpkU8, &param->rbId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dir, mBuf);
   CMCHKUNPK(SUnpkU8, &param->snLen, mBuf);
   if (cmUnpkCpjUlSduStaInfo(pst, &param->ulSduStaInfo, mBuf) != ROK)
      RETVALUE(RFAILED);
   CMCHKUNPK(cmUnpkCpjDlSduStaInfo, &param->dlSduStaInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCpjSduStaCfmInfo
*
*
*     Desc : *  PDCP SDU Status Request Confirmation for an UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjSduStaCfmInfo
(
Pst *pst,
CpjSduStaCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjSduStaCfmInfo(pst, param, mBuf)
Pst *pst;
CpjSduStaCfmInfo *param;
Buffer *mBuf;
#endif
{
   S32 i;

   TRC3(cmPkCpjSduStaCfmInfo)

   CMCHKPK(SPkS16, param->reason, mBuf);
   CMCHKPK(SPkS16, param->status, mBuf);
   for (i=param->numRb-1; i >= 0; i--) {
      if (cmPkCpjSduStaInfo(pst, &param->sduStaInfo[i], mBuf) != ROK)
         RETVALUE(RFAILED);
   }
   CMCHKPK(SPkU8, param->numRb, mBuf);
   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCpjSduStaCfmInfo
*
*
*     Desc : *  PDCP SDU Status Request Confirmation for an UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjSduStaCfmInfo
(
Pst *pst,
CpjSduStaCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjSduStaCfmInfo(pst, param, mBuf)
Pst *pst;
CpjSduStaCfmInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkCpjSduStaCfmInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numRb, mBuf);
   for (i=0; i<param->numRb; i++) {
      if (cmUnpkCpjSduStaInfo(pst, &param->sduStaInfo[i], mBuf) != ROK)
         RETVALUE(RFAILED);
   }
   CMCHKUNPK(SUnpkS16, &param->status, mBuf);
   CMCHKUNPK(SUnpkS16, &param->reason, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmPkCpjDataResCfmInfo
*
*
*     Desc : *  PDCP Data Resume Request Confirmation for an UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjDataResCfmInfo
(
Pst *pst,
CpjDatResumeCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjDataResCfmInfo(pst, param, mBuf)
Pst *pst;
CpjDatResumeCfmInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkCpjDataResCfmInfo)

   CMCHKPK(SPkS16, param->reason, mBuf);
   CMCHKPK(SPkS16, param->status, mBuf);
   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   RETVALUE(ROK);
}
/***********************************************************
*
*     Func : cmUnpkCpjDatResumeCfmInfo
*
*
*     Desc : *  PDCP Data Resume Request Confirmation for an UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjDatResumeCfmInfo
(
Pst *pst,
CpjDatResumeCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjDatResumeCfmInfo(pst, param, mBuf)
Pst *pst;
CpjDatResumeCfmInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkCpjDatResumeCfmInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->status, mBuf);
   CMCHKUNPK(SUnpkS16, &param->reason, mBuf);
   RETVALUE(ROK);
}
/***********************************************************
*
*     Func: cmPkCpjKenbCfgInfo
*
*
*     Desc:   Key derivation funtion Input Information
 * @details This funtion packs the the CpjKenbCfgInfo structure
 *           which contains the eNodeB key and Algorithm Type for
 *           deriving AS security keys.
 *
 *
 *     Ret : S16
 *
 *     Notes:
 *
 *     File:
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjNhKeyCfmInfo
(
CpjNhKeyCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjNhKeyCfmInfo(param, mBuf)
CpjNhKeyCfmInfo *param;
Buffer *mBuf;
#endif
{

   U8  idx;

   TRC3(cmUnpkCpjNhKeyCfmInfo)
         
   for(idx=0; idx<CPJ_SEC_KEY_LEN; idx++)
   {
      CMCHKUNPK(SUnpkU8,&param->secKey[idx],mBuf);
   }
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmPkCpjKenbCfgInfo
*
*
*     Desc:   Key derivation funtion Input Information
 * @details This funtion packs the the CpjKenbCfgInfo structure
 *           which contains the eNodeB key and Algorithm Type for
 *           deriving AS security keys.
 *
 *
 *     Ret : S16
 *
 *     Notes:
 *
 *     File:
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjKenbStarCfmInfo
(
CpjKenbStarCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjKenbStarCfmInfo(param, mBuf)
CpjKenbStarCfmInfo *param;
Buffer *mBuf;
#endif
{

   U8  idx;

   TRC3(cmUnpkCpjKenbStarCfmInfo)
         
   for(idx=0; idx<CPJ_SEC_KEY_LEN; idx++)
   {
      CMCHKUNPK(SUnpkU8,&param->secKey[idx],mBuf);
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func: cmPkCpjKenbCfgInfo
*
*
*     Desc:   Key derivation funtion Input Information
 * @details This funtion packs the the CpjKenbCfgInfo structure
 *           which contains the eNodeB key and Algorithm Type for
 *           deriving AS security keys.
 *
 *
 *     Ret : S16
 *
 *     Notes:
 *
 *     File:
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjAskeyCfmInfo
(
CpjAskeyCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjAskeyCfmInfo(param, mBuf)
CpjAskeyCfmInfo *param;
Buffer *mBuf;
#endif
{

   U8  idx;

   TRC3(cmUnpkCpjCpjAskeyCfmInfo)
         
   for(idx=0; idx<CPJ_SEC_KEY_LEN; idx++)
   {
      CMCHKUNPK(SUnpkU8,&param->intKey[idx],mBuf);
   }
   for(idx=0; idx<CPJ_SEC_KEY_LEN; idx++)
   {
      CMCHKUNPK(SUnpkU8,&param->upCiphKey[idx],mBuf);
   }
   for(idx=0; idx<CPJ_SEC_KEY_LEN; idx++)
   {
      CMCHKUNPK(SUnpkU8,&param->cpCiphKey[idx],mBuf);
   }
   RETVALUE(ROK);
}

/***********************************************************
 *
 *    Func: cmPkCpjKenbCfgInfo
 *
 *
 *    Desc:   Key derivation funtion Input Information
 * @details This funtion packs the the CpjKenbCfgInfo structure
 *           which contains the eNodeB key and Algorithm Type for
 *           deriving AS security keys.
 *
 *
 *     Ret : S16
 *
 *     Notes:
 *
 *     File:
 *
 *  **********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjKdfCfmInfo
(
CpjKdfCfmInfo *param,
Buffer *mBuf
 )
#else
PUBLIC S16 cmUnpkCpjKdfCfmInfo(param, mBuf)
CpjKdfCfmInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjKdfCfmInfo)

    CMCHKUNPK(SUnpkU8, &param->keyDerType, mBuf);
   switch (param->keyDerType)
    {
         case CPJ_KDF_TYPE1:
             CMCHKUNPK(cmUnpkCpjAskeyCfmInfo, &param->u.kEnbInf, mBuf);
             break;
         case CPJ_KDF_TYPE2:
            CMCHKUNPK(cmUnpkCpjKenbStarCfmInfo, &param->u.kEnbStarInf, mBuf);
            break;
         case CPJ_KDF_TYPE3:
            CMCHKUNPK(cmUnpkCpjNhKeyCfmInfo, &param->u.nhKeyInf, mBuf);
             break;
         default :
            RETVALUE(RFAILED);
    }
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmUnpkCpjCfgTransId
*
*
*     Desc: Transaction ID between CTF and RRC.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjCfgTransId
(
CpjCfgTransId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjCfgTransId(param, mBuf)
CpjCfgTransId *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkCpjCfgTransId)

   for (i=0; i<CPJ_CFG_TRANSID_SIZE; i++) {
      CMCHKUNPK(SUnpkU8, &param->trans[i], mBuf);
   }
   RETVALUE(ROK);
}

/**
* @brief Configuration Confirm from PHY to RRC.
*
* @details
*
*     Function: cmUnpkCpjKdfCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   CpjCfgTransId  transId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjKdfCfm
(
CpjKdfCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjKdfCfm(func, pst, mBuf)
CpjKdfCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId = 0;
   CpjCfgTransId transId;
   U8 status;
   CpjKdfCfmInfo kdfCfmInfo;
   
   TRC3(cmUnpkCpjKdfCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ030, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkCpjCfgTransId(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ031, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkCpjKdfCfmInfo(&kdfCfmInfo, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ031, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if (SUnpkU8(&status, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ032, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, transId,&kdfCfmInfo, status));
}
/***********************************************************
*
*     Func: cmPkCpjNhKeyInfo
*
*
*     Desc:   Pack keNB* input parameter information
 * @details This is one of the main structure in the KDF request primitive.
 *    -# This structure contains the configuration information as given by 
 *       the Application to trigger key derivation at PHY layer for generation of kENB*.
 *    -# It take Next Hop key, DL Frequency and Physical cell Id as input.
 *    -# The result of configuration is indicated in KdfCfgCfm.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjNhKeyInfo
(
CpjNhKeyInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjNhKeyInfo(param, mBuf)
CpjNhKeyInfo *param;
Buffer *mBuf;
#endif
{

   S16  idx;

   TRC3(cmPkCpjNhKeyInfo)
         
   for(idx = (CPJ_SEC_KEY_LEN - 1); idx>=0; idx--)
   {
      CMCHKPK(SPkU8,param->secKey[idx],mBuf);
   }
   CMCHKPK(SPkU16, param->physCellId, mBuf);
   CMCHKPK(SPkU16, param->dlCarrFreq, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmPkCpjKenbStarInfo
*
*
*     Desc:   Pack keNB* input parameter information
 * @details This is one of the main structure in the KDF request primitive.
 *    -# This structure contains the configuration information as given by 
 *       the Application to trigger key derivation at PHY layer for generation of kENB*.
 *    -# It take existing kENB, DL Frequency and Physical cell Id as input.
 *    -# The result of configuration is indicated in KdfCfgCfm.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjKenbStarInfo
(
CpjKenbStarInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjKenbStarInfo(param, mBuf)
CpjKenbStarInfo *param;
Buffer *mBuf;
#endif
{

   S16  idx;

   TRC3(cmPkCpjKenbStarInfo)
         
   for(idx = (CPJ_SEC_KEY_LEN - 1); idx>=0; idx--)
   {
      CMCHKPK(SPkU8,param->secKey[idx],mBuf);
   }
   CMCHKPK(SPkU16, param->physCellId, mBuf);
   CMCHKPK(SPkU16, param->dlCarrFreq, mBuf);
   
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func: cmPkCpjAskeyInfo
*
*
*     Desc:   Pack AS key generation input parameter information.
 * @details This is one of the main structure in the KDF request primitive.
 *    -# This structure contains the configuration information as given by 
 *       the Application to trigger key derivation at PHY layer for generation of AS Security keys.
 *    -# It take existing kENB, and integrity/cipherig Algorithm as input.
 *    -# The result of configuration is indicated in KdfCfgCfm.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjAskeyInfo
(
CpjAsKeyInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjAskeyInfo(param, mBuf)
CpjAsKeyInfo *param;
Buffer *mBuf;
#endif
{

   S16  idx;

   TRC3(cmPkCpjAskeyInfo)

         
   for(idx = (CPJ_SEC_KEY_LEN - 1); idx>=0; idx--)
   {
      CMCHKPK(SPkU8,param->secKey[idx],mBuf);
   }
   CMCHKPK(SPkU8, param->ciphAlgoType, mBuf);
   CMCHKPK(SPkU8, param->intgAlgoType, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmPkCpjKdfReqInfo
*
*
*     Desc:   Pack one of the 3 Key Derivation types.
 * @details This is the encompassing structure in the KDF request primitive.
 *    -# This structure contains the configuration information as given by 
 *       the Application to trigger key derivation at PHY layer for generation of keys.
 *    -# It takes key derivation type as input.
 *    -# The result of configuration is indicated in KdfCfgCfm.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjKdfReqInfo
(
CpjKdfReqInfo *param,
Buffer *mBuf
 )
#else
PUBLIC S16 cmPkCpjKdfReqInfo(param, mBuf)
CpjKdfReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjKdfReqInfo)

   switch (param->keyDerType)
    {
         case CPJ_KDF_TYPE1:
             CMCHKPK(cmPkCpjAskeyInfo, &param->u.kEnbInf, mBuf);
             break;
         case CPJ_KDF_TYPE2:
            CMCHKPK(cmPkCpjKenbStarInfo, &param->u.kEnbStarInf, mBuf);
            break;
         case CPJ_KDF_TYPE3:
            CMCHKPK(cmPkCpjNhKeyInfo , &param->u.nhKeyInf, mBuf);
             break;
         default :
            RETVALUE(RFAILED);
    }
    CMCHKPK(SPkU8, param->keyDerType, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmPkCpjCfgTransId
*
*
*     Desc: Transaction ID between CPJ and RRC.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjCfgTransId
(
CpjCfgTransId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjCfgTransId(param, mBuf)
CpjCfgTransId *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkCpjCfgTransId)

   for (i=CPJ_CFG_TRANSID_SIZE-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->trans[i], mBuf);
   }
   RETVALUE(ROK);
}

/**
* @brief Primitive Request from Application to PHY for 
 * security key derivation.
*
* @details
*
*     Function: cmPkCpjKdfReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   CpjCfgTransId  transId
*  @param[in]   CpjCfgReqInfo*  cfgReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCpjKdfReq
(
Pst* pst,
SpId spId,
CpjCfgTransId transId,
CpjKdfReqInfo* kdfReqInfo
)
#else
PUBLIC S16 cmPkCpjKdfReq(pst, spId, transId, kdfReqInfo)
Pst* pst;
SpId spId;
CpjCfgTransId transId;
CpjKdfReqInfo* kdfReqInfo;
#endif
{
   Buffer *mBuf = NULLP;


   TRC3(cmPkCpjKdfReq)
   
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ016, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)kdfReqInfo, sizeof(CpjKdfReqInfo));
      RETVALUE(RFAILED);
   }
   if (pst->selector == CPJ_SEL_LC) {
      if (cmPkCpjKdfReqInfo(kdfReqInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ017, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)kdfReqInfo, sizeof(CpjKdfReqInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (cmPkCpjCfgTransId(&transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ019, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)kdfReqInfo, sizeof(CpjKdfReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ020, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)kdfReqInfo, sizeof(CpjKdfReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
      if (SPutSBuf(pst->region, pst->pool, (Data *)kdfReqInfo, sizeof(CpjKdfReqInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ021, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   pst->event = (Event) EVTCPJKDFREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

/***********************************************************
*
*     Func: cmPkCpjKenbCfgInfo
*
*
*     Desc:   Key derivation funtion Input Information
 * @details This funtion packs the the CpjKenbCfgInfo structure
 *           which contains the eNodeB key and Algorithm Type for
 *           deriving AS security keys.
 *
 *
 *     Ret : S16
 *
 *     Notes:
 *
 *     File:
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjNhKeyInfo
(
CpjNhKeyInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjNhKeyInfo(param, mBuf)
CpjNhKeyInfo *param;
Buffer *mBuf;
#endif
{

   U8  idx;

   TRC3(cmUnpkCpjNhKeyInfo)
         
   CMCHKUNPK(SUnpkU16, &param->dlCarrFreq, mBuf);
   CMCHKUNPK(SUnpkU16, &param->physCellId, mBuf);
   for(idx=0; idx<CPJ_SEC_KEY_LEN; idx++)
   {
      CMCHKUNPK(SUnpkU8,&param->secKey[idx],mBuf);
   }
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmPkCpjKenbCfgInfo
*
*
*     Desc:   Key derivation funtion Input Information
 * @details This funtion packs the the CpjKenbCfgInfo structure
 *           which contains the eNodeB key and Algorithm Type for
 *           deriving AS security keys.
 *
 *
 *     Ret : S16
 *
 *     Notes:
 *
 *     File:
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjKenbStarInfo
(
CpjKenbStarInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjKenbStarInfo(param, mBuf)
CpjKenbStarInfo *param;
Buffer *mBuf;
#endif
{

   U8  idx;

   TRC3(cmUnpkCpjKenbStarInfo)
         
   CMCHKUNPK(SUnpkU16, &param->dlCarrFreq, mBuf);
   CMCHKUNPK(SUnpkU16, &param->physCellId, mBuf);
   for(idx=0; idx<CPJ_SEC_KEY_LEN; idx++)
   {
      CMCHKUNPK(SUnpkU8,&param->secKey[idx],mBuf);
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func: cmPkCpjKenbCfgInfo
*
*
*     Desc:   Key derivation funtion Input Information
 * @details This funtion packs the the CpjKenbCfgInfo structure
 *           which contains the eNodeB key and Algorithm Type for
 *           deriving AS security keys.
 *
 *
 *     Ret : S16
 *
 *     Notes:
 *
 *     File:
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjAskeyInfo
(
CpjAsKeyInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjAskeyInfo(param, mBuf)
CpjAskeyInfo *param;
Buffer *mBuf;
#endif
{

   U8  idx;

   TRC3(cmUnpkCpjAskeyInfo)

   CMCHKUNPK(SUnpkU8, &param->intgAlgoType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ciphAlgoType, mBuf);
   for(idx=0; idx<CPJ_SEC_KEY_LEN; idx++)
   {
      CMCHKUNPK(SUnpkU8,&param->secKey[idx],mBuf);
   }
   RETVALUE(ROK);
}

/***********************************************************
 *
 *    Func: cmPkCpjKenbCfgInfo
 *
 *
 *    Desc:   Key derivation funtion Input Information
 * @details This funtion packs the the CpjKenbCfgInfo structure
 *           which contains the eNodeB key and Algorithm Type for
 *           deriving AS security keys.
 *
 *
 *     Ret : S16
 *
 *     Notes:
 *
 *     File:
 *
 *  **********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjKdfReqInfo
(
CpjKdfReqInfo *param,
Buffer *mBuf
 )
#else
PUBLIC S16 cmUnpkCpjKdfReqInfo(param, mBuf)
CpjKdfReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCpjKdfReqInfo)

    CMCHKUNPK(SUnpkU8, &param->keyDerType, mBuf);
     switch (param->keyDerType)
    {
       case CPJ_KDF_TYPE1:
           CMCHKUNPK(cmUnpkCpjAskeyInfo, &param->u.kEnbInf, mBuf);
           break;
       case CPJ_KDF_TYPE2:
          CMCHKUNPK(cmUnpkCpjKenbStarInfo, &param->u.kEnbStarInf, mBuf);
          break;
       case CPJ_KDF_TYPE3:
          CMCHKUNPK(cmUnpkCpjNhKeyInfo, &param->u.nhKeyInf, mBuf);
           break;
       default :
          RETVALUE(RFAILED);
    }
   RETVALUE(ROK);
}

/**
* @brief Configuration Request from RRC to PHY for 
 * cell or dedicated configuration.
*
* @details
*
*     Function: cmUnpkCpjCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   CpjCfgTransId  transId
*  @param[in]   CpjCfgReqInfo*  cfgReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCpjKdfReq
(
CpjKdfReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCpjKdfReq(func, pst, mBuf)
CpjKdfReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId = 0;
   CpjCfgTransId transId;
   CpjKdfReqInfo *kdfReqInfo = NULLP;

   TRC3(cmUnpkCpjKdfReq)

      if (SUnpkS16(&spId, mBuf) != ROK) {
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECPJ022, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         RETVALUE(RFAILED);
      }

   if (cmUnpkCpjCfgTransId(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ023, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&kdfReqInfo, sizeof(CpjKdfReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ024, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }


   if (cmUnpkCpjKdfReqInfo(kdfReqInfo, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)kdfReqInfo, sizeof(CpjKdfReqInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECPJ025, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, transId, kdfReqInfo));
}

/***********************************************************
*
*     Func: cmPkCpjKenbCfgInfo
*
*
*     Desc:   Key derivation funtion Input Information
 * @details This funtion packs the the CpjKenbCfgInfo structure
 *           which contains the eNodeB key and Algorithm Type for
 *           deriving AS security keys.
 *
 *
 *     Ret : S16
 *
 *     Notes:
 *
 *     File:
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjNhKeyCfmInfo
(
CpjNhKeyCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjNhKeyCfmInfo(param, mBuf)
CpjNhKeyCfmInfo *param;
Buffer *mBuf;
#endif
{

   S16  idx;

   TRC3(cmPkCpjNhKeyCfmInfo)
         
   for(idx = (CPJ_SEC_KEY_LEN - 1); idx>=0; idx--)
   {
      CMCHKPK(SPkU8,param->secKey[idx],mBuf);
   }
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmPkCpjKenbCfgInfo
*
*
*     Desc:   Key derivation funtion Input Information
 * @details This funtion packs the the CpjKenbCfgInfo structure
 *           which contains the eNodeB key and Algorithm Type for
 *           deriving AS security keys.
 *
 *
 *     Ret : S16
 *
 *     Notes:
 *
 *     File:
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjKenbStarCfmInfo
(
CpjKenbStarCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjKenbStarCfmInfo(param, mBuf)
CpjKenbStarCfmInfo *param;
Buffer *mBuf;
#endif
{

   S16  idx;

   TRC3(cmPkCpjKenbStarCfmInfo)
         
   for(idx = (CPJ_SEC_KEY_LEN - 1);idx>=0;idx--)
   {
      CMCHKPK(SPkU8,param->secKey[idx],mBuf);
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func: cmPkCpjKenbCfgInfo
*
*
*     Desc:   Key derivation funtion Input Information
 * @details This funtion packs the the CpjKenbCfgInfo structure
 *           which contains the eNodeB key and Algorithm Type for
 *           deriving AS security keys.
 *
 *
 *     Ret : S16
 *
 *     Notes:
 *
 *     File:
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjAskeyCfmInfo
(
CpjAskeyCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCpjAskeyCfmInfo(param, mBuf)
CpjAskeyCfmInfo *param;
Buffer *mBuf;
#endif
{

   S16  idx;

   TRC3(cmPkCpjCpjAskeyCfmInfo)

   for(idx = (CPJ_SEC_KEY_LEN - 1); idx>=0; idx--)
   {
      CMCHKPK(SPkU8,param->cpCiphKey[idx],mBuf);
   }
   for(idx = (CPJ_SEC_KEY_LEN - 1); idx>=0; idx--)
   {
      CMCHKPK(SPkU8,param->upCiphKey[idx],mBuf);
   }
   for(idx = (CPJ_SEC_KEY_LEN - 1); idx>=0; idx--)
   {
      CMCHKPK(SPkU8,param->intKey[idx],mBuf);
   }
   RETVALUE(ROK);
}

/***********************************************************
 *
 *    Func: cmPkCpjKenbCfgInfo
 *
 *
 *    Desc:   Key derivation funtion Input Information
 * @details This funtion packs the the CpjKenbCfgInfo structure
 *           which contains the eNodeB key and Algorithm Type for
 *           deriving AS security keys.
 *
 *
 *     Ret : S16
 *
 *     Notes:
 *
 *     File:
 *
 *  **********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCpjKdfCfmInfo
(
CpjKdfCfmInfo *param,
Buffer *mBuf
 )
#else
PUBLIC S16 cmPkCpjKdfCfmInfo(param, mBuf)
CpjKdfCfmInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCpjKdfCfmInfo)

   switch (param->keyDerType)
    {
         case CPJ_KDF_TYPE1:
             CMCHKPK(cmPkCpjAskeyCfmInfo, &param->u.kEnbInf, mBuf);
             break;
         case CPJ_KDF_TYPE2:
            CMCHKPK(cmPkCpjKenbStarCfmInfo, &param->u.kEnbStarInf, mBuf);
            break;
         case CPJ_KDF_TYPE3:
            CMCHKPK(cmPkCpjNhKeyCfmInfo, &param->u.nhKeyInf, mBuf);
             break;
         default :
            RETVALUE(RFAILED);
    }
    CMCHKPK(SPkU8, param->keyDerType, mBuf);
   RETVALUE(ROK);
}

/**
* @brief Configuration Confirm from PHY to RRC.
*
* @details
*
*     Function: cmPkCpjCfgCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   CpjCfgTransId  transId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCpjKdfCfm
(
Pst* pst,
SuId suId,
CpjCfgTransId transId,
CpjKdfCfmInfo *kdfCfmInfo,
U8 status
)
#else
PUBLIC S16 cmPkCpjKdfCfm(pst, suId, transId, status)
Pst* pst;
SuId suId;
CpjCfgTransId transId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCpjKdfCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ026, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)kdfCfmInfo, sizeof(CpjKdfCfmInfo));
      RETVALUE(RFAILED);
   }

   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ027, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)kdfCfmInfo, sizeof(CpjKdfCfmInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (cmPkCpjKdfCfmInfo(kdfCfmInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ028, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)kdfCfmInfo, sizeof(CpjKdfCfmInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (cmPkCpjCfgTransId(&transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ028, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)kdfCfmInfo, sizeof(CpjKdfCfmInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECPJ029, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)kdfCfmInfo, sizeof(CpjKdfCfmInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPutSBuf(pst->region, pst->pool, (Data *)kdfCfmInfo, sizeof(CpjKdfCfmInfo)) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
   SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
      (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
      (ErrVal)ECPJ021, (ErrVal)0, (Txt*)&"Packing failed");
#endif
     SPutMsg(mBuf);
     RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTCPJKDFCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end of #if(defined(LCCPJ) || defined(LWLCCPJ)) */

/********************************************************************30**
  
         End of file:     cpj.c@@/main/5 - Fri Sep  2 18:46:48 2011
  
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
/main/1      ---      dm   1. LTE RRC Initial Release.
/main/3      ---      gk   1. LTE PDCP Release 2.1.
/main/4      ---      cpj_c_001.main_3 nm   1. Updated the size for cfgCfm.
/main/5      ---      cpj_c_001.main_4 ap   1. Added support for L2 Measurement.
*********************************************************************91*/

