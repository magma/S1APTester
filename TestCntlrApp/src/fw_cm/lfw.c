PUBLIC S16 cmPkLfwCfgReq
(
   Pst         *pst,
   FwMngmt     *cfg
)
{
   Buffer *mBuf = NULLP;

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ENAXXX, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if (pst->selector == LFW_SEL_LWLC)
   {
      if (cmPkPtr((PTR)cfg, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENAXXX, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ENAXXX, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) LFW_MNGMT_CFG_READ_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

PUBLIC S16 cmUnpkLfwCfgReq
(
 LfwCfgReq   func,
 Pst         *pst,
 Buffer      *mBuf
)
{
   FwMngmt *cfg;

   if (pst->selector != LFW_SEL_LWLC)
   {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfg,
                  sizeof(FwMngmt))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ENAXXX, (ErrVal)0, "Unpacking failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == LFW_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&cfg, mBuf) != ROK)
      {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfg));
}

PUBLIC S16 cmPkLfwCfgCfm
(
   Pst     * pst,
   FwMngmt * cfm
)
#else
PUBLIC S16 cmPkLfwCfgCfm(pst, cfm)
Pst     * pst;
FwMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ENAXXX, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LFW_SEL_LWLC)
   {
      if (cmPkPtr((PTR)cfm, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENAXXX, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
else
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ENAXXX, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Even)LFW_MNGMT_CFG_READ_CFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLfwCfgCfm
(
   LfwCfgCfm func,
   Pst *pst,
   Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLfwCfgCfm(func, pst, mBuf)
LfwCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   FwMngmt *cfm;

   if (pst->selector != LFW_SEL_LWLC)
   {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfm,
                    sizeof(FwMngmt))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENAXXX, (ErrVal)0, "Unpacking failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == LFW_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&cfm, mBuf) != ROK)
      {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}
