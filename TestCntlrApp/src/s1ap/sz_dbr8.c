

/**********************************************************************

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C source code for DB

     File:     sq_dbr8.c

     Sid:      sq_dbr8.c@@/main/1 - Mon Jan 10 22:16:53 2011

     Prg:      hsingh

**********************************************************************/
 
#ifdef SZ_ACC_TST_ESC_FUNC
/* sz008.301: support for Source RNC to Target RNC Transparent container */
PRIVATE  U32 flagSz3O = CM_PASN_ELM_OPT | CM_PASN_POST_DECODE_ESC_CALL;
PRIVATE  U32 flagSz3M = CM_PASN_ELM_MAND | CM_PASN_POST_DECODE_ESC_CALL;
PRIVATE  U32 flagSz3D = CM_PASN_ELM_DEF | CM_PASN_POST_DECODE_ESC_CALL;
#else
PRIVATE  U32 flagSz3O = CM_PASN_ELM_OPT | CM_PASN_PRE_ENCODE_ESC_CALL |CM_PASN_POST_DECODE_ESC_CALL;
PRIVATE  U32 flagSz3M = CM_PASN_ELM_MAND | CM_PASN_PRE_ENCODE_ESC_CALL | CM_PASN_POST_DECODE_ESC_CALL;
PRIVATE  U32 flagSz3D = CM_PASN_ELM_DEF | CM_PASN_PRE_ENCODE_ESC_CALL | CM_PASN_POST_DECODE_ESC_CALL;
#endif

#define SZ_CRIT_REJECT 0
#define SZ_CRIT_IGNORE 1
#define SZ_CRIT_NOTIFY 2

#define SZ_MAX_NUM_IES 32

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
   
typedef struct _szProtIEs
{
   TknPres pres;
   TknU32 id;
   TknU32 criticality;
} SzProtIEs;

typedef struct _szMsgIeInf
{
   U32 procId;
   U32 criticality;
   U32 presFlag;
} SzMsgIeInf;

typedef struct _szMsgConInf
{
   SzMsgIeInf infArr[SZ_MAX_NUM_IES];
   U16 maxIes;
   U16 minIes;
} SzMsgConInf;

#ifdef SZ_ENC_DEC
EXTERN SzCb szCb;
#endif /* SZ_ENC_DEC */

EXTERN S16 szValidateProtIes ARGS((SzMsgConInf *conInf, CmPAsnMsgCp *msgCp, Void *iePtr, U32 ieSize, U8 numIes));
EXTERN S16 szProtIE_Cont_HovrReqdIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_HovrCmmdIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_HovrPrepFailIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_HovrRqstIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_HovrRqstAckgIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_HovrFailIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_HovrNtfyIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_PathSwRqstIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_PathSwRqstAckgIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_PathSwRqstFailIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_HovrCancelIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_HovrCancelAckgIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_E_RABSetupRqstIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_E_RABSetupRespIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_E_RABMdfyRqstIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_E_RABMdfyRespIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_E_RABRlsCmmdIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_E_RABRlsRespIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_E_RABRlsIndIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_InitCntxtSetupRqstIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_InitCntxtSetupRespIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_InitCntxtSetupFailIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_PagIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_UECntxtRlsRqst_IEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_UECntxtRlsCmmd_IEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_UECntxtRlsComplete_IEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_UECntxtModificationRqstIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_UECntxtModificationRespIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_UECntxtModificationFailIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_DlnkNASTport_IEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_InitUEMsg_IEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_UlnkNASTport_IEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_NASNonDlvryInd_IEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_ResetIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_ResetAckgIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_ErrIndIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_S1SetupRqstIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_S1SetupRespIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_S1SetupFailIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_ENBConfigUpdIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_ENBConfigUpdAckgIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_ENBConfigUpdFailIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_MMEConfigUpdIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_MMEConfigUpdAckgIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_MMEConfigUpdFailIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_DlnkS1cdma2000tunnelingIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_UlnkS1cdma2000tunnelingIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_UECapbltyInfoIndIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_ENBStatusTfrIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_MMEStatusTfrIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_TraceStartIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_TraceFailIndIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_DeactvTraceIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_CellTrafficTraceIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_LocRprtngCntrlIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_LocRprtngFailIndIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_LocReportIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_OverloadStartIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_OverloadStopIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_WriteReplaceWarningRqstIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_WriteReplaceWarningRespIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_ENBDirectInformTfrIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_MMEDirectInformTfrIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_ENBConfigTfrIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szProtIE_Cont_MMEConfigTfrIEsValidate ARGS((CmPAsnMsgCp *msgCp));
EXTERN S16 szPrivIE_Cont_PrivMsgIEsValidate ARGS((CmPAsnMsgCp *msgCp));

#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifdef ANSI
PUBLIC S16 szValidateProtIes
(
SzMsgConInf *conInf,
CmPAsnMsgCp *msgCp,
Void *iePtr,
U32 ieSize,
U8 numIes
)
#else
PUBLIC S16 szValidateProtIes (conInf, msgCp, iePtr, ieSize, numIes)
SzMsgConInf *conInf;
CmPAsnMsgCp *msgCp;
Void *iePtr;
U32 ieSize;
U8 numIes;
#endif
{
   U8 idx = 0;
   U8 furIdx = 0;
   S8 evntIdx = 0;
   Bool idExists = FALSE;
   U32 memPtr = 0;

   S8 iesLeft;
   TknU32 *fieldIe = NULLP;
   SzMsgIeInf *array = conInf->infArr;
   TknU32 *fieldCrit = NULLP;
   S16        ret = ROK;
#ifdef CM_PASN_CRIT_HANDL
   CmPAsnErr  *err = NULLP;
#endif /* CM_PASN_CRIT_HANDL */

   TRC2(szValidateProtIes);

   if(conInf->maxIes == 0)
   {
      RETVALUE(ROK);
   }

  /* get the mandatory no of Ies */
  iesLeft = conInf->minIes;
  /* Get the error structure to store the error IEs */
#ifdef CM_PASN_CRIT_HANDL
   err = msgCp->err;
   err->ieCount = 0;
    /* sz001.301: Initialize the already set error code */
   err->errCode = 0;
#endif /* CM_PASN_CRIT_HANDL */

   /* Loop through the received elements for validation */
   for(evntIdx = 0; evntIdx < numIes; evntIdx++)
   {
      /* appropriate bytes to point to the next member */
      memPtr = (ieSize * evntIdx);

      /* get the protocol Ie and criticality address */
      fieldIe = &((SzProtIEs *)((U8 *)iePtr + memPtr))->id;
      fieldCrit = &((SzProtIEs *)((U8 *)iePtr + memPtr))->criticality;

      /* Check if idx has moved out of array limit */
      if(idx < conInf->maxIes)
      {
         if(fieldIe->val != array[idx].procId)
         {
            /* search further in the static table if exists */
            furIdx = (idx + 1);
            idExists = FALSE;

            while(furIdx < conInf->maxIes)
            {
               if(fieldIe->val == array[furIdx].procId)
               {
                  /* Mark the present as true */
                  idExists = TRUE;
                  break;
               }
               else
               {
                  furIdx++;
               }
            }/* end of while */

            /* check the presence of the Ie */
            if(idExists)
            {
               /* return failure if Ie is present in the array since message
                * is not in order */
               if (((array[idx].presFlag == CM_PASN_ELM_MAND) &&
                   (array[idx].criticality & SZ_CRIT_IGNORE)) ||
                   (array[idx].presFlag == CM_PASN_ELM_OPT))
               {
                  /* if Ie is found, make the count to point next Ie and 
                   * decrement ies left */
                  idx = furIdx + 1;
                  if(iesLeft)
                  {
                     iesLeft--;
                  }
                  continue;

               }
               else
               {
#ifdef CM_PASN_CRIT_HANDL
                  err->ieCount = 0;
                  err->errCause = CM_PASN_CAUSE_ABS_SNTX_ERR_FLSLY_CONS_MSG;
#endif /* CM_PASN_CRIT_HANDL */
                  RETVALUE(RFAILED);
               }
            }
            else
            {
               /* Verify is the IE present in the DB before the current
                * index, furIdx is set to zero to start the search from
                * starting If so, it is falsely constructed message */
               furIdx = 0;
               idExists = FALSE;
               while(furIdx < conInf->maxIes)
               {
                  if(fieldIe->val == array[furIdx].procId)
                  {
                     /* Mark the present as true */
                     idExists = TRUE;
                     break;
                  }
                  else
                  {
                     furIdx++;
                  }
               }/* end of while */

               /* Report an error if IE is present */
               if(idExists)
               {
#ifdef CM_PASN_CRIT_HANDL
                  err->ieCount = 0;
                  err->errCause = CM_PASN_CAUSE_ABS_SNTX_ERR_FLSLY_CONS_MSG;
#endif /* CM_PASN_CRIT_HANDL */
                  RETVALUE(RFAILED);
               }
               /* IE is not present in the message at our end */
               else
               {
                  /* take the action depending on the criticality. The output
                   *  of & operation will be TRUE only if the criticality is 
                   *  ignore and its FALSE in other cases */
#ifdef CM_PASN_CRIT_HANDL
                  if((fieldCrit->val & SZ_CRIT_IGNORE))
                  {
                     /* ignore the Ie since its criticality is ignore and mark 
                      * the presence as not present */
                     fieldIe->pres = NOTPRSNT;
                     continue;
                  }
                  else
                  {
                     if(err->ieCount < CM_PASN_MAX_ERR_IE)
                     {
                        err->ieInfo[err->ieCount].ieId = fieldIe->val;
                        err->ieInfo[err->ieCount].criticality = fieldCrit->val;
                        err->ieInfo[err->ieCount].errType=
                           CM_PASN_ERR_TYPE_NOT_UNDRSTD;
                        err->ieCount++;
                     }
                     continue;
                  }
#else
              RETVALUE(RFAILED);
#endif /* CM_PASN_CRIT_HANDL */
               }
            }
         }
         /* value of Ie matches, go for the next Ie */
         else
         {
            /* Decrement the mandatory iesLeft */
            if((array[idx].presFlag == CM_PASN_ELM_MAND) && (iesLeft))
            {
               iesLeft--;
            }
            idx++;
         }
      }
      else
      {
         furIdx = 0;
         idExists = FALSE;
         while(furIdx < conInf->maxIes)
         {
            if(fieldIe->val == array[furIdx].procId)
            {
               /* Mark the present as true */
               idExists = TRUE;
               break;
            }
            else
            {
               furIdx++;
            }
         }/* end of while */
         /* the Ie is not present in the array, so take the action 
          * depending on the criticality. The output
          * of & operation will be TRUE only if the criticality is 
          * ignore and its FALSE in other cases */
         if(idExists)
         {
            /* Return failer as the message received out of order */
#ifdef CM_PASN_CRIT_HANDL
            err->ieCount = 0;
            err->errCause = CM_PASN_CAUSE_ABS_SNTX_ERR_FLSLY_CONS_MSG;
#endif /* CM_PASN_CRIT_HANDL */
            RETVALUE(RFAILED);
         }
         else
         {
#ifdef CM_PASN_CRIT_HANDL
            if((fieldCrit->val & SZ_CRIT_IGNORE))
            {
               /* ignore the Ie since its criticality is ignore and mark the 
                * presence as not present */
               fieldIe->pres = NOTPRSNT;
               continue;
            }
            else
            {
               /* Keep the not understood Ies and its criticality */
               if(err->ieCount < CM_PASN_MAX_ERR_IE)
               {
                  err->ieInfo[err->ieCount].ieId = fieldIe->val;
                  err->ieInfo[err->ieCount].criticality = fieldCrit->val;
                  err->ieInfo[err->ieCount].errType=
                                        CM_PASN_ERR_TYPE_NOT_UNDRSTD;
                  err->ieCount++;
               }
               continue;
            }
#endif /* CM_PASN_CRIT_HANDL */
         }
      }
   }/* End of for */

#ifdef CM_PASN_CRIT_HANDL
   if(err->ieCount)
   {
      err->errCause = CM_PASN_CAUSE_ABS_SNTX_ERR_REJ;
      RETVALUE(RFAILED);
   }

   /* verify mand. params are missing */
   else if(iesLeft > 0)
#else
   if(iesLeft > 0)
#endif /* CM_PASN_CRIT_HANDL */
   {
      while((iesLeft > 0) && (idx < conInf->maxIes))
      {
         /* Ignore the Ie if its criticality is IGNORE, else list the 
          * missing Ies with its criticality */
         if((array[idx].presFlag == CM_PASN_ELM_MAND) &&
            (array[idx].criticality & SZ_CRIT_IGNORE))
         {
            idx++;
            iesLeft--;
         }
         else if(array[idx].presFlag == CM_PASN_ELM_MAND)
         {
#ifdef CM_PASN_CRIT_HANDL
            /* List the missing mandatory parameter */
            if(err->ieCount < CM_PASN_MAX_ERR_IE)
            {
               err->ieInfo[err->ieCount].ieId = array[idx].procId;
               err->ieInfo[err->ieCount].criticality = array[idx].criticality;
               err->ieInfo[err->ieCount].errType = CM_PASN_ERR_TYPE_MISSING;
               err->ieCount++;
            }
#endif /* CM_PASN_CRIT_HANDL */
#ifdef DEBUGP
#ifdef ALIGN_64BIT
            SZDBGP(DBGMASK_LYR, (szCb.init.prntBuf,
                  "szValidateProtIes: Mandatory IE missing: %d \n",
                  array[idx].procId));
#else
            SZDBGP(DBGMASK_LYR, (szCb.init.prntBuf,
                  "szValidateProtIes: Mandatory IE missing: %ld \n",
                  array[idx].procId));
#endif /* ALIGN_64BIT */
#endif /* DEBUGP */
            idx++;
            iesLeft--;
            ret = RFAILED;
         }
         else
         {
            idx++;
         }
      }

      /* return failure */
#ifdef CM_PASN_CRIT_HANDL
      if(err->ieCount)
      {
         err->errCause = CM_PASN_CAUSE_ABS_SNTX_ERR_REJ;
         RETVALUE(RFAILED);
      }
#endif /* CM_PASN_CRIT_HANDL */
   }

   RETVALUE(ret);
} /* szValidateProtIes */
CmPAsnElmDef szConstTerm =
{
#ifdef CM_PASN_DBG
   " szConstTerm (Set-Sequence Terminator) ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SETSEQ_TERM,
   CM_PASN_EXT_MKR_ABS,
   0,
   &flagSz3M,    
   CM_PASN_ESC_FUNC_NULLP,
   /* sz006.301: DB Warning fixes. */
   NULLP, 
   NULLP 
}; 
PUBLIC CmPAsnElmDef szNull =
{
#ifdef CM_PASN_DBG
   " szNull ",
#endif /* CM_PASN_DEBUG */
  CM_PASN_TET_NULL,
  CM_PASN_EXT_MKR_ABS,
  0,        
  &flagSz3M,
  CM_PASN_ESC_FUNC_NULLP,
  NULLP, 
  NULLP
}; 
CmPAsnElmDef szExtMkr =
{  
#ifdef CM_PASN_DBG
  " szExtMkr(Extension Marker) ",
#endif /* CM_PASN_DEBUG */
  CM_PASN_TET_EXT_MKR,
  CM_PASN_EXT_MKR_ABS,
  0,
  &flagSz3M,
  CM_PASN_ESC_FUNC_NULLP,
  NULLP, 
  NULLP
};
/* Element ----- Criticality ------- */
CmPAsnTknEnum szCriticalityLst[4] =
{
   3,
   SztCriticalityrejectEnum,
   SztCriticalityignoreEnum,
   SztCriticalitynotifyEnum
};
CmPAsnEnumDef szCriticalityspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szCriticalityLst,
   NULLP
};
CmPAsnElmDef szOptCriticality =
{
#ifdef CM_PASN_DBG
   " szCriticality ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCriticality),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCriticalityspec),
   NULLP
};
CmPAsnElmDef szCriticality =
{
#ifdef CM_PASN_DBG
   " szCriticality ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCriticality),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCriticalityspec),
   NULLP
};

/* Element ----- Presence ------- */
CmPAsnTknEnum szPresenceLst[4] =
{
   3,
   SztPresenceoptionalEnum,
   SztPresenceconditionalEnum,
   SztPresencemandatoryEnum
};
CmPAsnEnumDef szPresencespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szPresenceLst,
   NULLP
};
CmPAsnElmDef szPresence =
{
#ifdef CM_PASN_DBG
   " szPresence ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztPresence),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szPresencespec),
   NULLP
};

/* Element ----- local ------- */
CmPAsnUIntDef szPrivIE_IDlocalspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   65535UL
};
CmPAsnElmDef szPrivIE_IDlocal =
{
#ifdef CM_PASN_DBG
   " szPrivIE_IDlocal ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztPrivIE_IDlocal),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szPrivIE_IDlocalspec),
   NULLP
};

PUBLIC CmPAsnElmDef *szPrivIE_IDTkn[] =
{
   &szPrivIE_IDlocal,
   /* &szglobal,*/
   &szConstTerm
};
CmPAsnChoiceDef szPrivIE_IDspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   2,
   0,
   &szPrivIE_IDTkn[0]  /* Token List */
};
CmPAsnElmDef szPrivIE_ID =
{
#ifdef CM_PASN_DBG
   " szPrivIE_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztPrivIE_ID),
   &flagSz3M,
   NULLP,
   (U8 *)(&szPrivIE_IDspec),
   NULLP
};
/* Element ----- ProcedureCode ------- */
CmPAsnUIntDef szProcedureCodespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   255UL
};
CmPAsnElmDef szProcedureCode =
{
#ifdef CM_PASN_DBG
   " szProcedureCode ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProcedureCode),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProcedureCodespec),
   NULLP
};
CmPAsnElmDef szOptProcedureCode =
{
#ifdef CM_PASN_DBG
   " szProcedureCode ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProcedureCode),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProcedureCodespec),
   NULLP
};

/* Element ----- ProtocolExtensionID ------- */
CmPAsnUIntDef szProtExtnIDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   65535UL
};
CmPAsnElmDef szProtExtnID =
{
#ifdef CM_PASN_DBG
   " szProtExtnID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnIDspec),
   NULLP
};

/* Element ----- ProtocolIE-ID ------- */
CmPAsnUIntDef szProtIE_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   65535UL
};
CmPAsnElmDef szProtIE_ID =
{
#ifdef CM_PASN_DBG
   " szProtIE_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_IDspec),
   NULLP
};

/* Element ----- TriggeringMessage ------- */
CmPAsnTknEnum szTrgMsgLst[4] =
{
   3,
   SztTrgMsginitiating_messageEnum,
   SztTrgMsgsuccessful_outcomeEnum,
   SztTrgMsgunsuccessfull_outcomeEnum
};
CmPAsnEnumDef szTrgMsgspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szTrgMsgLst,
   NULLP
};
CmPAsnElmDef szOptTrgMsg =
{
#ifdef CM_PASN_DBG
   " szTrgMsg ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTrgMsg),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTrgMsgspec),
   NULLP
};

/* Element ----- PriorityLevel ------- */
CmPAsnUIntDef szPriorityLvlspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   15UL
};
CmPAsnElmDef szPriorityLvl =
{
#ifdef CM_PASN_DBG
   " szPriorityLvl ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztPriorityLvl),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szPriorityLvlspec),
   NULLP
};

/* Element ----- Pre-emptionCapability ------- */
CmPAsnTknEnum szPre_emptionCapbltyLst[3] =
{
   2,
   SztPre_emptionCapbltyshall_not_trigger_pre_emptionEnum,
   SztPre_emptionCapbltymay_trigger_pre_emptionEnum
};
CmPAsnEnumDef szPre_emptionCapbltyspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szPre_emptionCapbltyLst,
   NULLP
};
CmPAsnElmDef szPre_emptionCapblty =
{
#ifdef CM_PASN_DBG
   " szPre_emptionCapblty ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztPre_emptionCapblty),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szPre_emptionCapbltyspec),
   NULLP
};

/* Element ----- Pre-emptionVulnerability ------- */
CmPAsnTknEnum szPre_emptionVulnerabilityLst[3] =
{
   2,
   SztPre_emptionVulnerabilitynot_pre_emptableEnum,
   SztPre_emptionVulnerabilitypre_emptableEnum
};
CmPAsnEnumDef szPre_emptionVulnerabilityspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szPre_emptionVulnerabilityLst,
   NULLP
};
CmPAsnElmDef szPre_emptionVulnerability =
{
#ifdef CM_PASN_DBG
   " szPre_emptionVulnerability ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztPre_emptionVulnerability),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szPre_emptionVulnerabilityspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz_ExtnAllocnAndRetentionPriority_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnAllocnAndRetentionPriority_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnAllocnAndRetentionPriority_ExtIEsClsInfo =
{
   0,
   &sz_ExtnAllocnAndRetentionPriority_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnAllocnAndRetentionPriority_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnAllocnAndRetentionPriority_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnAllocnAndRetentionPriority_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnAllocnAndRetentionPriority_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnAllocnAndRetentionPriority_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnAllocnAndRetentionPriority_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_AllocnAndRetentionPriority_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnAllocnAndRetentionPriority_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_AllocnAndRetentionPriority_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_AllocnAndRetentionPriority_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_AllocnAndRetentionPriority_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_AllocnAndRetentionPriority_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_AllocnAndRetentionPriority_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_AllocnAndRetentionPriority_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_AllocnAndRetentionPriority_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_AllocnAndRetentionPriority_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_AllocnAndRetentionPriority_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_AllocnAndRetentionPriority_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_AllocnAndRetentionPriority_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_AllocnAndRetentionPriority_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_AllocnAndRetentionPriority_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szAllocnAndRetentionPriorityTkn[] =
{
   &szPriorityLvl,
   &szPre_emptionCapblty,
   &szPre_emptionVulnerability,
   &szOptProtExtnCont_AllocnAndRetentionPriority_ExtIEs,
      &szProtExtnField_AllocnAndRetentionPriority_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szAllocnAndRetentionPriorityspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szAllocnAndRetentionPriorityTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szAllocnAndRetentionPriority =
{
#ifdef CM_PASN_DBG
   " szAllocnAndRetentionPriority ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztAllocnAndRetentionPriority),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szAllocnAndRetentionPriorityspec),
   NULLP
};
/* Element ----- E-RAB-ID ------- */
CmPAsnUIntDef szE_RAB_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   15UL
};
CmPAsnElmDef szE_RAB_ID =
{
#ifdef CM_PASN_DBG
   " szE_RAB_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RAB_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RAB_IDspec),
   NULLP
};

/* Element ----- PDCP-SN ------- */
CmPAsnUIntDef szPDCP_SNspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   4095UL
};
CmPAsnElmDef szPDCP_SN =
{
#ifdef CM_PASN_DBG
   " szPDCP_SN ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztPDCP_SN),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szPDCP_SNspec),
   NULLP
};

/* Element ----- HFN ------- */
CmPAsnUIntDef szHFNspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   1048575UL
};
CmPAsnElmDef szHFN =
{
#ifdef CM_PASN_DBG
   " szHFN ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztHFN),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szHFNspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz_ExtnCOUNTvalue_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnCOUNTvalue_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnCOUNTvalue_ExtIEsClsInfo =
{
   0,
   &sz_ExtnCOUNTvalue_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCOUNTvalue_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnCOUNTvalue_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnCOUNTvalue_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnCOUNTvalue_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnCOUNTvalue_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnCOUNTvalue_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnCOUNTvalue_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_COUNTvalue_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnCOUNTvalue_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_COUNTvalue_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_COUNTvalue_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_COUNTvalue_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_COUNTvalue_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_COUNTvalue_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_COUNTvalue_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_COUNTvalue_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_COUNTvalue_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_COUNTvalue_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_COUNTvalue_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_COUNTvalue_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_COUNTvalue_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_COUNTvalue_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_COUNTvalue_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_COUNTvalue_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szCOUNTvalueTkn[] =
{
   &szPDCP_SN,
   &szHFN,
   &szOptProtExtnCont_COUNTvalue_ExtIEs,
      &szProtExtnField_COUNTvalue_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szCOUNTvaluespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szCOUNTvalueTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szCOUNTvalue =
{
#ifdef CM_PASN_DBG
   " szCOUNTvalue ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCOUNTvalue),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCOUNTvaluespec),
   NULLP
};
CmPAsnBitStrDef szReceiveStatusofULPDCPSDUsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTRXL,
#endif /* CM_PASN_DEBUG */
   4096,
   4096
};
CmPAsnElmDef szOptReceiveStatusofULPDCPSDUs =
{
#ifdef CM_PASN_DBG
   " szReceiveStatusofULPDCPSDUs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztReceiveStatusofULPDCPSDUs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szReceiveStatusofULPDCPSDUsspec),
   NULLP
};
CmPAsnElmDef szReceiveStatusofULPDCPSDUs =
{
#ifdef CM_PASN_DBG
   " szReceiveStatusofULPDCPSDUs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztReceiveStatusofULPDCPSDUs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szReceiveStatusofULPDCPSDUsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsInfo =
{
   0,
   &sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_Brs_SubjToStatusTfr_ItemExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_Brs_SubjToStatusTfr_ItemExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_Brs_SubjToStatusTfr_ItemExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_Brs_SubjToStatusTfr_ItemExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szBrs_SubjToStatusTfr_ItemTkn[] =
{
   &szE_RAB_ID,
   &szCOUNTvalue,
   &szCOUNTvalue,
   &szOptReceiveStatusofULPDCPSDUs,
   &szOptProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs,
      &szProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szBrs_SubjToStatusTfr_Itemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   2,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szBrs_SubjToStatusTfr_ItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szBrs_SubjToStatusTfr_Item =
{
#ifdef CM_PASN_DBG
   " szBrs_SubjToStatusTfr_Item ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztBrs_SubjToStatusTfr_Item),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szBrs_SubjToStatusTfr_Itemspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueBrs_SubjToStatusTfr_ItemIEsClsInst[] =
{
   &szBrs_SubjToStatusTfr_Item
};
PUBLIC U32 sz_ValueBrs_SubjToStatusTfr_ItemIEsClsInstId[] =
{
   Sztid_Brs_SubjToStatusTfr_Item
};
SzMsgConInf szBrs_SubjToStatusTfr_ItemIEsConInf =
{
   {
      { Sztid_Brs_SubjToStatusTfr_Item, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueBrs_SubjToStatusTfr_ItemIEsClsInfo =
{
   1,
   &sz_ValueBrs_SubjToStatusTfr_ItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueBrs_SubjToStatusTfr_ItemIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueBrs_SubjToStatusTfr_ItemIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueBrs_SubjToStatusTfr_ItemIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueBrs_SubjToStatusTfr_ItemIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueBrs_SubjToStatusTfr_ItemIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueBrs_SubjToStatusTfr_ItemIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_Brs_SubjToStatusTfr_ItemIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueBrs_SubjToStatusTfr_ItemIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_Brs_SubjToStatusTfr_ItemIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_Brs_SubjToStatusTfr_ItemIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_Brs_SubjToStatusTfr_ItemIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_Brs_SubjToStatusTfr_ItemIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_Brs_SubjToStatusTfr_ItemIEsspec),
   NULLP
};
#define szProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs szProtIE_Field_Brs_SubjToStatusTfr_ItemIEs
CmPAsnSetSeqOfDef szBrs_SubjToStatusTfrLstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szBrs_SubjToStatusTfrLst =
{
#ifdef CM_PASN_DBG
   " szBrs_SubjToStatusTfrLst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztBrs_SubjToStatusTfrLst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szBrs_SubjToStatusTfrLstspec),
   NULLP
};
/* Element ----- BitRate ------- */
CmPAsnUIntXLDef szBitRatespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINTXL,
#endif /* CM_PASN_DEBUG */
   {
      1,
      {0} 
   },
   {
      5,
      {2, 84, 11, 228, 0} 
   }
};
CmPAsnElmDef szBitRate =
{
#ifdef CM_PASN_DBG
   " szBitRate ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINTXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztBitRate),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szBitRatespec),
   NULLP
};

CmPAsnOctStrDef szTBCD_STRINGspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   3,
   3
};
CmPAsnElmDef szTBCD_STRING =
{
#ifdef CM_PASN_DBG
   " szTBCD_STRING " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTBCD_STRING),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szTBCD_STRINGspec),
   NULLP
};
#define szPLMNidentity szTBCD_STRING
CmPAsnSetSeqOfDef szBPLMNsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofBPLMNs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szBPLMNs =
{
#ifdef CM_PASN_DBG
   " szBPLMNs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztBPLMNs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szBPLMNsspec),
   NULLP
};
CmPAsnBitStrDef szCellIdentityspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTR,
#endif /* CM_PASN_DEBUG */
   28,
   28
};
CmPAsnElmDef szCellIdentity =
{
#ifdef CM_PASN_DBG
   " szCellIdentity ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCellIdentity),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCellIdentityspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnEUTRAN_CGI_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnEUTRAN_CGI_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnEUTRAN_CGI_ExtIEsClsInfo =
{
   0,
   &sz_ExtnEUTRAN_CGI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnEUTRAN_CGI_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnEUTRAN_CGI_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnEUTRAN_CGI_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnEUTRAN_CGI_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnEUTRAN_CGI_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnEUTRAN_CGI_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnEUTRAN_CGI_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_EUTRAN_CGI_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnEUTRAN_CGI_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_EUTRAN_CGI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_EUTRAN_CGI_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_EUTRAN_CGI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_EUTRAN_CGI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_EUTRAN_CGI_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_EUTRAN_CGI_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_EUTRAN_CGI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_EUTRAN_CGI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_EUTRAN_CGI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_EUTRAN_CGI_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_EUTRAN_CGI_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_EUTRAN_CGI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_EUTRAN_CGI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_EUTRAN_CGI_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_EUTRAN_CGI_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szEUTRAN_CGITkn[] =
{
   &szTBCD_STRING,
   &szCellIdentity,
   &szOptProtExtnCont_EUTRAN_CGI_ExtIEs,
      &szProtExtnField_EUTRAN_CGI_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szEUTRAN_CGIspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szEUTRAN_CGITkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szEUTRAN_CGI =
{
#ifdef CM_PASN_DBG
   " szEUTRAN_CGI ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztEUTRAN_CGI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szEUTRAN_CGIspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnCellID_Broadcast_Item_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnCellID_Broadcast_Item_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnCellID_Broadcast_Item_ExtIEsClsInfo =
{
   0,
   &sz_ExtnCellID_Broadcast_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCellID_Broadcast_Item_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnCellID_Broadcast_Item_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnCellID_Broadcast_Item_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnCellID_Broadcast_Item_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnCellID_Broadcast_Item_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnCellID_Broadcast_Item_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnCellID_Broadcast_Item_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_CellID_Broadcast_Item_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnCellID_Broadcast_Item_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CellID_Broadcast_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_CellID_Broadcast_Item_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_CellID_Broadcast_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_CellID_Broadcast_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_CellID_Broadcast_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_CellID_Broadcast_Item_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_CellID_Broadcast_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_CellID_Broadcast_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CellID_Broadcast_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CellID_Broadcast_Item_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CellID_Broadcast_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_CellID_Broadcast_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CellID_Broadcast_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CellID_Broadcast_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CellID_Broadcast_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szCellID_Broadcast_ItemTkn[] =
{
   &szEUTRAN_CGI,
   &szOptProtExtnCont_CellID_Broadcast_Item_ExtIEs,
      &szProtExtnField_CellID_Broadcast_Item_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szCellID_Broadcast_Itemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szCellID_Broadcast_ItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szCellID_Broadcast_Item =
{
#ifdef CM_PASN_DBG
   " szCellID_Broadcast_Item ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCellID_Broadcast_Item),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCellID_Broadcast_Itemspec),
   NULLP
};
CmPAsnSetSeqOfDef szCellID_Broadcastspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofCellID,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szCellID_Broadcast =
{
#ifdef CM_PASN_DBG
   " szCellID_Broadcast ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCellID_Broadcast),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCellID_Broadcastspec),
   NULLP
};
CmPAsnOctStrDef szTACspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTR,
#endif /* CM_PASN_DEBUG */
   2,
   2
};
CmPAsnElmDef szTAC =
{
#ifdef CM_PASN_DBG
   " szTAC " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTAC),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szTACspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnTAI_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnTAI_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnTAI_ExtIEsClsInfo =
{
   0,
   &sz_ExtnTAI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTAI_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnTAI_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnTAI_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnTAI_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnTAI_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnTAI_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnTAI_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_TAI_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnTAI_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TAI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_TAI_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_TAI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_TAI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_TAI_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_TAI_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_TAI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_TAI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TAI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TAI_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TAI_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_TAI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TAI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TAI_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TAI_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szTAITkn[] =
{
   &szTBCD_STRING,
   &szTAC,
   &szOptProtExtnCont_TAI_ExtIEs,
      &szProtExtnField_TAI_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szTAIspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szTAITkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szTAI =
{
#ifdef CM_PASN_DBG
   " szTAI ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTAI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTAIspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnCompletedCellinTAI_Item_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnCompletedCellinTAI_Item_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnCompletedCellinTAI_Item_ExtIEsClsInfo =
{
   0,
   &sz_ExtnCompletedCellinTAI_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCompletedCellinTAI_Item_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnCompletedCellinTAI_Item_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnCompletedCellinTAI_Item_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnCompletedCellinTAI_Item_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnCompletedCellinTAI_Item_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnCompletedCellinTAI_Item_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_CompletedCellinTAI_Item_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnCompletedCellinTAI_Item_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CompletedCellinTAI_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_CompletedCellinTAI_Item_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_CompletedCellinTAI_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_CompletedCellinTAI_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_CompletedCellinTAI_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_CompletedCellinTAI_Item_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_CompletedCellinTAI_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_CompletedCellinTAI_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CompletedCellinTAI_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CompletedCellinTAI_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_CompletedCellinTAI_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CompletedCellinTAI_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CompletedCellinTAI_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szCompletedCellinTAI_ItemTkn[] =
{
   &szEUTRAN_CGI,
   &szOptProtExtnCont_CompletedCellinTAI_Item_ExtIEs,
      &szProtExtnField_CompletedCellinTAI_Item_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szCompletedCellinTAI_Itemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szCompletedCellinTAI_ItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szCompletedCellinTAI_Item =
{
#ifdef CM_PASN_DBG
   " szCompletedCellinTAI_Item ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCompletedCellinTAI_Item),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCompletedCellinTAI_Itemspec),
   NULLP
};
CmPAsnSetSeqOfDef szCompletedCellinTAIspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofCellinTAI,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szCompletedCellinTAI =
{
#ifdef CM_PASN_DBG
   " szCompletedCellinTAI ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCompletedCellinTAI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCompletedCellinTAIspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnTAI_Broadcast_Item_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnTAI_Broadcast_Item_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnTAI_Broadcast_Item_ExtIEsClsInfo =
{
   0,
   &sz_ExtnTAI_Broadcast_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTAI_Broadcast_Item_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnTAI_Broadcast_Item_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnTAI_Broadcast_Item_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnTAI_Broadcast_Item_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnTAI_Broadcast_Item_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnTAI_Broadcast_Item_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnTAI_Broadcast_Item_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_TAI_Broadcast_Item_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnTAI_Broadcast_Item_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TAI_Broadcast_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_TAI_Broadcast_Item_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_TAI_Broadcast_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_TAI_Broadcast_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_TAI_Broadcast_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_TAI_Broadcast_Item_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_TAI_Broadcast_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_TAI_Broadcast_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TAI_Broadcast_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TAI_Broadcast_Item_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TAI_Broadcast_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_TAI_Broadcast_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TAI_Broadcast_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TAI_Broadcast_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TAI_Broadcast_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szTAI_Broadcast_ItemTkn[] =
{
   &szTAI,
   &szCompletedCellinTAI,
      &szCompletedCellinTAI_Item,
      &szConstTerm,
   &szOptProtExtnCont_TAI_Broadcast_Item_ExtIEs,
      &szProtExtnField_TAI_Broadcast_Item_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szTAI_Broadcast_Itemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szTAI_Broadcast_ItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szTAI_Broadcast_Item =
{
#ifdef CM_PASN_DBG
   " szTAI_Broadcast_Item ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTAI_Broadcast_Item),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTAI_Broadcast_Itemspec),
   NULLP
};
CmPAsnSetSeqOfDef szTAI_Broadcastspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofTAIforWarning,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szTAI_Broadcast =
{
#ifdef CM_PASN_DBG
   " szTAI_Broadcast ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTAI_Broadcast),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szTAI_Broadcastspec),
   NULLP
};
CmPAsnOctStrDef szEmergencyAreaIDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   3,
   3
};
CmPAsnElmDef szEmergencyAreaID =
{
#ifdef CM_PASN_DBG
   " szEmergencyAreaID " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztEmergencyAreaID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szEmergencyAreaIDspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnCompletedCellinEAI_Item_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnCompletedCellinEAI_Item_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnCompletedCellinEAI_Item_ExtIEsClsInfo =
{
   0,
   &sz_ExtnCompletedCellinEAI_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCompletedCellinEAI_Item_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnCompletedCellinEAI_Item_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnCompletedCellinEAI_Item_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnCompletedCellinEAI_Item_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnCompletedCellinEAI_Item_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnCompletedCellinEAI_Item_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_CompletedCellinEAI_Item_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnCompletedCellinEAI_Item_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CompletedCellinEAI_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_CompletedCellinEAI_Item_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_CompletedCellinEAI_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_CompletedCellinEAI_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_CompletedCellinEAI_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_CompletedCellinEAI_Item_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_CompletedCellinEAI_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_CompletedCellinEAI_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CompletedCellinEAI_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CompletedCellinEAI_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_CompletedCellinEAI_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CompletedCellinEAI_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CompletedCellinEAI_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szCompletedCellinEAI_ItemTkn[] =
{
   &szEUTRAN_CGI,
   &szOptProtExtnCont_CompletedCellinEAI_Item_ExtIEs,
      &szProtExtnField_CompletedCellinEAI_Item_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szCompletedCellinEAI_Itemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szCompletedCellinEAI_ItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szCompletedCellinEAI_Item =
{
#ifdef CM_PASN_DBG
   " szCompletedCellinEAI_Item ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCompletedCellinEAI_Item),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCompletedCellinEAI_Itemspec),
   NULLP
};
CmPAsnSetSeqOfDef szCompletedCellinEAIspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofCellinEAI,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szCompletedCellinEAI =
{
#ifdef CM_PASN_DBG
   " szCompletedCellinEAI ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCompletedCellinEAI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCompletedCellinEAIspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsInfo =
{
   0,
   &sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szEmergencyAreaID_Broadcast_ItemTkn[] =
{
   &szEmergencyAreaID,
   &szCompletedCellinEAI,
      &szCompletedCellinEAI_Item,
      &szConstTerm,
   &szOptProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs,
      &szProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szEmergencyAreaID_Broadcast_Itemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szEmergencyAreaID_Broadcast_ItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szEmergencyAreaID_Broadcast_Item =
{
#ifdef CM_PASN_DBG
   " szEmergencyAreaID_Broadcast_Item ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztEmergencyAreaID_Broadcast_Item),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szEmergencyAreaID_Broadcast_Itemspec),
   NULLP
};
CmPAsnSetSeqOfDef szEmergencyAreaID_Broadcastspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofEmergencyAreaID,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szEmergencyAreaID_Broadcast =
{
#ifdef CM_PASN_DBG
   " szEmergencyAreaID_Broadcast ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztEmergencyAreaID_Broadcast),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szEmergencyAreaID_Broadcastspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szBroadcastCompletedAreaLstTkn[] =
{
   &szCellID_Broadcast,
      &szCellID_Broadcast_Item,
      &szConstTerm,
   &szTAI_Broadcast,
      &szTAI_Broadcast_Item,
      &szConstTerm,
   &szEmergencyAreaID_Broadcast,
      &szEmergencyAreaID_Broadcast_Item,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szBroadcastCompletedAreaLstspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   3,
   0,
   &szBroadcastCompletedAreaLstTkn[0]  /* Token List */
};
CmPAsnElmDef szBroadcastCompletedAreaLst =
{
#ifdef CM_PASN_DBG
   " szBroadcastCompletedAreaLst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztBroadcastCompletedAreaLst),
   &flagSz3M,
   NULLP,
   (U8 *)(&szBroadcastCompletedAreaLstspec),
   NULLP
};
/* Element ----- CauseRadioNetwork ------- */
CmPAsnTknEnum szCauseRadioNwExtLst[3] =
{
   2,
   SztCauseRadioNwredirection_towards_1xRTTEnum,
   SztCauseRadioNwnot_supported_QCI_valueEnum
};
CmPAsnTknEnum szCauseRadioNwLst[37] =
{
   36,
   SztCauseRadioNwunspecifiedEnum,
   SztCauseRadioNwtx2relocoverall_expiryEnum,
   SztCauseRadioNwsuccessful_handoverEnum,
   SztCauseRadioNwrelease_due_to_eutran_generated_reasonEnum,
   SztCauseRadioNwhandover_cancelledEnum,
   SztCauseRadioNwpartial_handoverEnum,
   SztCauseRadioNwho_failure_in_target_EPC_eNB_or_target_systemEnum,
   SztCauseRadioNwho_target_not_allowedEnum,
   SztCauseRadioNwtS1relocoverall_expiryEnum,
   SztCauseRadioNwtS1relocprep_expiryEnum,
   SztCauseRadioNwcell_not_availableEnum,
   SztCauseRadioNwunknown_targetIDEnum,
   SztCauseRadioNwno_radio_resources_available_in_target_cellEnum,
   SztCauseRadioNwunknown_mme_ue_s1ap_idEnum,
   SztCauseRadioNwunknown_enb_ue_s1ap_idEnum,
   SztCauseRadioNwunknown_pair_ue_s1ap_idEnum,
   SztCauseRadioNwhandover_desirable_for_radio_reasonEnum,
   SztCauseRadioNwtime_critical_handoverEnum,
   SztCauseRadioNwresource_optimisation_handoverEnum,
   SztCauseRadioNwreduce_load_in_serving_cellEnum,
   SztCauseRadioNwuser_inactivityEnum,
   SztCauseRadioNwradio_connection_with_ue_lostEnum,
   SztCauseRadioNwload_balancing_tau_requiredEnum,
   SztCauseRadioNwcs_fallback_triggeredEnum,
   SztCauseRadioNwue_not_available_for_ps_serviceEnum,
   SztCauseRadioNwradio_resources_not_availableEnum,
   SztCauseRadioNwfailure_in_radio_interface_procedureEnum,
   SztCauseRadioNwinvalid_qos_combinationEnum,
   SztCauseRadioNwinterrat_redirectionEnum,
   SztCauseRadioNwinteraction_with_other_procedureEnum,
   SztCauseRadioNwunknown_E_RAB_IDEnum,
   SztCauseRadioNwmultiple_E_RAB_ID_instancesEnum,
   SztCauseRadioNwencryption_and_or_integrity_protection_algorithms_not_supportedEnum,
   SztCauseRadioNws1_intra_system_handover_triggeredEnum,
   SztCauseRadioNws1_inter_system_handover_triggeredEnum,
   SztCauseRadioNwx2_handover_triggeredEnum
};
CmPAsnEnumDef szCauseRadioNwspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szCauseRadioNwLst,
   szCauseRadioNwExtLst
};
CmPAsnElmDef szCauseRadioNw =
{
#ifdef CM_PASN_DBG
   " szCauseRadioNw ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCauseRadioNw),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCauseRadioNwspec),
   NULLP
};

/* Element ----- CauseTransport ------- */
CmPAsnTknEnum szCauseTportLst[3] =
{
   2,
   SztCauseTporttransport_resource_unavailableEnum,
   SztCauseTportunspecifiedEnum
};
CmPAsnEnumDef szCauseTportspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szCauseTportLst,
   NULLP
};
CmPAsnElmDef szCauseTport =
{
#ifdef CM_PASN_DBG
   " szCauseTport ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCauseTport),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCauseTportspec),
   NULLP
};

/* Element ----- CauseNas ------- */
CmPAsnTknEnum szCauseNasLst[5] =
{
   4,
   SztCauseNasnormal_releaseEnum,
   SztCauseNasauthentication_failureEnum,
   SztCauseNasdetachEnum,
   SztCauseNasunspecifiedEnum
};
CmPAsnEnumDef szCauseNasspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szCauseNasLst,
   NULLP
};
CmPAsnElmDef szCauseNas =
{
#ifdef CM_PASN_DBG
   " szCauseNas ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCauseNas),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCauseNasspec),
   NULLP
};

/* Element ----- CauseProtocol ------- */
CmPAsnTknEnum szCauseProtLst[8] =
{
   7,
   SztCauseProttransfer_syntax_errorEnum,
   SztCauseProtabstract_syntax_error_rejectEnum,
   SztCauseProtabstract_syntax_error_ignore_and_notifyEnum,
   SztCauseProtmessage_not_compatible_with_receiver_stateEnum,
   SztCauseProtsemantic_errorEnum,
   SztCauseProtabstract_syntax_error_falsely_constructed_messageEnum,
   SztCauseProtunspecifiedEnum
};
CmPAsnEnumDef szCauseProtspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szCauseProtLst,
   NULLP
};
CmPAsnElmDef szCauseProt =
{
#ifdef CM_PASN_DBG
   " szCauseProt ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCauseProt),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCauseProtspec),
   NULLP
};

/* Element ----- CauseMisc ------- */
CmPAsnTknEnum szCauseMiscLst[7] =
{
   6,
   SztCauseMisccontrol_processing_overloadEnum,
   SztCauseMiscnot_enough_user_plane_processing_resourcesEnum,
   SztCauseMischardware_failureEnum,
   SztCauseMiscom_interventionEnum,
   SztCauseMiscunspecifiedEnum,
   SztCauseMiscunknown_PLMNEnum
};
CmPAsnEnumDef szCauseMiscspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szCauseMiscLst,
   NULLP
};
CmPAsnElmDef szCauseMisc =
{
#ifdef CM_PASN_DBG
   " szCauseMisc ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCauseMisc),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCauseMiscspec),
   NULLP
};

PUBLIC CmPAsnElmDef *szCauseTkn[] =
{
   &szCauseRadioNw,
   &szCauseTport,
   &szCauseNas,
   &szCauseProt,
   &szCauseMisc,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szCausespec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   5,
   0,
   &szCauseTkn[0]  /* Token List */
};
CmPAsnElmDef szCause =
{
#ifdef CM_PASN_DBG
   " szCause ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCause),
   &flagSz3M,
   NULLP,
   (U8 *)(&szCausespec),
   NULLP
};
CmPAsnOctStrDef szCdma2000PDUspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szCdma2000PDU =
{
#ifdef CM_PASN_DBG
   " szCdma2000PDU " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCdma2000PDU),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCdma2000PDUspec),
   NULLP
};
/* Element ----- Cdma2000RATType ------- */
CmPAsnTknEnum szCdma2000RATTypLst[3] =
{
   2,
   SztCdma2000RATTyphRPDEnum,
   SztCdma2000RATTyponexRTTEnum
};
CmPAsnEnumDef szCdma2000RATTypspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szCdma2000RATTypLst,
   NULLP
};
CmPAsnElmDef szCdma2000RATTyp =
{
#ifdef CM_PASN_DBG
   " szCdma2000RATTyp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCdma2000RATTyp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCdma2000RATTypspec),
   NULLP
};

CmPAsnOctStrDef szCdma2000SectorIDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szCdma2000SectorID =
{
#ifdef CM_PASN_DBG
   " szCdma2000SectorID " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCdma2000SectorID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCdma2000SectorIDspec),
   NULLP
};
/* Element ----- Cdma2000HOStatus ------- */
CmPAsnTknEnum szCdma2000HOStatusLst[3] =
{
   2,
   SztCdma2000HOStatushOSuccessEnum,
   SztCdma2000HOStatushOFailEnum
};
CmPAsnEnumDef szCdma2000HOStatusspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szCdma2000HOStatusLst,
   NULLP
};
CmPAsnElmDef szCdma2000HOStatus =
{
#ifdef CM_PASN_DBG
   " szCdma2000HOStatus ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCdma2000HOStatus),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCdma2000HOStatusspec),
   NULLP
};

/* Element ----- Cdma2000HORequiredIndication ------- */
CmPAsnTknEnum szCdma2000HOReqdIndLst[2] =
{
   1,
   SztCdma2000HOReqdIndtrueEnum
};
CmPAsnEnumDef szCdma2000HOReqdIndspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szCdma2000HOReqdIndLst,
   NULLP
};
CmPAsnElmDef szCdma2000HOReqdInd =
{
#ifdef CM_PASN_DBG
   " szCdma2000HOReqdInd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCdma2000HOReqdInd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCdma2000HOReqdIndspec),
   NULLP
};

CmPAsnOctStrDef szCdma2000OneXMEIDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szCdma2000OneXMEID =
{
#ifdef CM_PASN_DBG
   " szCdma2000OneXMEID " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCdma2000OneXMEID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCdma2000OneXMEIDspec),
   NULLP
};
CmPAsnOctStrDef szCdma2000OneXMSIspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szCdma2000OneXMSI =
{
#ifdef CM_PASN_DBG
   " szCdma2000OneXMSI " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCdma2000OneXMSI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCdma2000OneXMSIspec),
   NULLP
};
CmPAsnOctStrDef szCdma2000OneXPilotspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szCdma2000OneXPilot =
{
#ifdef CM_PASN_DBG
   " szCdma2000OneXPilot " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCdma2000OneXPilot),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCdma2000OneXPilotspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsInfo =
{
   0,
   &sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szCdma2000OneXSRVCCInfoTkn[] =
{
   &szCdma2000OneXMEID,
   &szCdma2000OneXMSI,
   &szCdma2000OneXPilot,
   &szOptProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs,
      &szProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szCdma2000OneXSRVCCInfospec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szCdma2000OneXSRVCCInfoTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szCdma2000OneXSRVCCInfo =
{
#ifdef CM_PASN_DBG
   " szCdma2000OneXSRVCCInfo ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCdma2000OneXSRVCCInfo),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCdma2000OneXSRVCCInfospec),
   NULLP
};
CmPAsnOctStrDef szCdma2000OneXRANDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szCdma2000OneXRAND =
{
#ifdef CM_PASN_DBG
   " szCdma2000OneXRAND " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCdma2000OneXRAND),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCdma2000OneXRANDspec),
   NULLP
};
/* Element ----- Cell-Size ------- */
CmPAsnTknEnum szCell_SizeLst[5] =
{
   4,
   SztCell_SizeverysmallEnum,
   SztCell_SizesmallEnum,
   SztCell_SizemediumEnum,
   SztCell_SizelargeEnum
};
CmPAsnEnumDef szCell_Sizespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szCell_SizeLst,
   NULLP
};
CmPAsnElmDef szCell_Size =
{
#ifdef CM_PASN_DBG
   " szCell_Size ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCell_Size),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCell_Sizespec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz_ExtnCellTyp_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnCellTyp_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnCellTyp_ExtIEsClsInfo =
{
   0,
   &sz_ExtnCellTyp_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCellTyp_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnCellTyp_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnCellTyp_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnCellTyp_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnCellTyp_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnCellTyp_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnCellTyp_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_CellTyp_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnCellTyp_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CellTyp_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_CellTyp_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_CellTyp_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_CellTyp_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_CellTyp_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_CellTyp_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_CellTyp_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_CellTyp_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CellTyp_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CellTyp_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CellTyp_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_CellTyp_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CellTyp_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CellTyp_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CellTyp_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szCellTypTkn[] =
{
   &szCell_Size,
   &szOptProtExtnCont_CellTyp_ExtIEs,
      &szProtExtnField_CellTyp_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szCellTypspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szCellTypTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szCellTyp =
{
#ifdef CM_PASN_DBG
   " szCellTyp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCellTyp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCellTypspec),
   NULLP
};
CmPAsnOctStrDef szLACspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTR,
#endif /* CM_PASN_DEBUG */
   2,
   2
};
CmPAsnElmDef szLAC =
{
#ifdef CM_PASN_DBG
   " szLAC " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztLAC),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szLACspec),
   NULLP
};
CmPAsnOctStrDef szCIspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTR,
#endif /* CM_PASN_DEBUG */
   2,
   2
};
CmPAsnElmDef szCI =
{
#ifdef CM_PASN_DBG
   " szCI " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCIspec),
   NULLP
};
CmPAsnOctStrDef szRACspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTR,
#endif /* CM_PASN_DEBUG */
   1,
   1
};
CmPAsnElmDef szOptRAC =
{
#ifdef CM_PASN_DBG
   " szRAC " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztRAC),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szRACspec),
   NULLP
};
CmPAsnElmDef szRAC =
{
#ifdef CM_PASN_DBG
   " szRAC " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztRAC),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szRACspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnCGI_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnCGI_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnCGI_ExtIEsClsInfo =
{
   0,
   &sz_ExtnCGI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCGI_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnCGI_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnCGI_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnCGI_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnCGI_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnCGI_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnCGI_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_CGI_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnCGI_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CGI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_CGI_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_CGI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_CGI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_CGI_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_CGI_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_CGI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_CGI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CGI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CGI_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CGI_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_CGI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CGI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CGI_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CGI_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szCGITkn[] =
{
   &szTBCD_STRING,
   &szLAC,
   &szCI,
   &szOptRAC,
   &szOptProtExtnCont_CGI_ExtIEs,
      &szProtExtnField_CGI_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szCGIspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   2,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szCGITkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szCGI =
{
#ifdef CM_PASN_DBG
   " szCGI ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCGI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCGIspec),
   NULLP
};
/* Element ----- CNDomain ------- */
CmPAsnTknEnum szCNDomainLst[3] =
{
   2,
   SztCNDomainpsEnum,
   SztCNDomaincsEnum
};
CmPAsnEnumDef szCNDomainspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szCNDomainLst,
   NULLP
};
CmPAsnElmDef szCNDomain =
{
#ifdef CM_PASN_DBG
   " szCNDomain ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCNDomain),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCNDomainspec),
   NULLP
};

/* Element ----- CSFallbackIndicator ------- */
CmPAsnTknEnum szCSFallbackIndicatorExtLst[2] =
{
   1,
   SztCSFallbackIndicatorcs_fallback_high_priorityEnum
};
CmPAsnTknEnum szCSFallbackIndicatorLst[2] =
{
   1,
   SztCSFallbackIndicatorcs_fallback_requiredEnum
};
CmPAsnEnumDef szCSFallbackIndicatorspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szCSFallbackIndicatorLst,
   szCSFallbackIndicatorExtLst
};
CmPAsnElmDef szCSFallbackIndicator =
{
#ifdef CM_PASN_DBG
   " szCSFallbackIndicator ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCSFallbackIndicator),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCSFallbackIndicatorspec),
   NULLP
};

CmPAsnBitStrDef szCSG_Idspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTR,
#endif /* CM_PASN_DEBUG */
   27,
   27
};
CmPAsnElmDef szCSG_Id =
{
#ifdef CM_PASN_DBG
   " szCSG_Id ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCSG_Id),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCSG_Idspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnCSG_IdLst_Item_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnCSG_IdLst_Item_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnCSG_IdLst_Item_ExtIEsClsInfo =
{
   0,
   &sz_ExtnCSG_IdLst_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCSG_IdLst_Item_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnCSG_IdLst_Item_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnCSG_IdLst_Item_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnCSG_IdLst_Item_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnCSG_IdLst_Item_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnCSG_IdLst_Item_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnCSG_IdLst_Item_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_CSG_IdLst_Item_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnCSG_IdLst_Item_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CSG_IdLst_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_CSG_IdLst_Item_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_CSG_IdLst_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_CSG_IdLst_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_CSG_IdLst_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_CSG_IdLst_Item_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_CSG_IdLst_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_CSG_IdLst_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CSG_IdLst_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CSG_IdLst_Item_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CSG_IdLst_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_CSG_IdLst_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CSG_IdLst_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CSG_IdLst_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CSG_IdLst_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szCSG_IdLst_ItemTkn[] =
{
   &szCSG_Id,
   &szOptProtExtnCont_CSG_IdLst_Item_ExtIEs,
      &szProtExtnField_CSG_IdLst_Item_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szCSG_IdLst_Itemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szCSG_IdLst_ItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szCSG_IdLst_Item =
{
#ifdef CM_PASN_DBG
   " szCSG_IdLst_Item ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCSG_IdLst_Item),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCSG_IdLst_Itemspec),
   NULLP
};
CmPAsnSetSeqOfDef szCSG_IdLstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfCSGs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szCSG_IdLst =
{
#ifdef CM_PASN_DBG
   " szCSG_IdLst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCSG_IdLst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCSG_IdLstspec),
   NULLP
};
/* Element ----- TypeOfError ------- */
CmPAsnTknEnum szTypOfErrLst[3] =
{
   2,
   SztTypOfErrnot_understoodEnum,
   SztTypOfErrmissingEnum
};
CmPAsnEnumDef szTypOfErrspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szTypOfErrLst,
   NULLP
};
CmPAsnElmDef szTypOfErr =
{
#ifdef CM_PASN_DBG
   " szTypOfErr ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTypOfErr),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTypOfErrspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsInfo =
{
   0,
   &sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnCriticalityDiag_IE_Item_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnCriticalityDiag_IE_Item_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_CriticalityDiag_IE_Item_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnCriticalityDiag_IE_Item_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CriticalityDiag_IE_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_CriticalityDiag_IE_Item_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_CriticalityDiag_IE_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_CriticalityDiag_IE_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_CriticalityDiag_IE_Item_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_CriticalityDiag_IE_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_CriticalityDiag_IE_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CriticalityDiag_IE_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CriticalityDiag_IE_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_CriticalityDiag_IE_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CriticalityDiag_IE_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CriticalityDiag_IE_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szCriticalityDiag_IE_ItemTkn[] =
{
   &szCriticality,
   &szProtIE_ID,
   &szTypOfErr,
   &szOptProtExtnCont_CriticalityDiag_IE_Item_ExtIEs,
      &szProtExtnField_CriticalityDiag_IE_Item_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szCriticalityDiag_IE_Itemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szCriticalityDiag_IE_ItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szCriticalityDiag_IE_Item =
{
#ifdef CM_PASN_DBG
   " szCriticalityDiag_IE_Item ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCriticalityDiag_IE_Item),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCriticalityDiag_IE_Itemspec),
   NULLP
};
CmPAsnSetSeqOfDef szCriticalityDiag_IE_Lstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfErrs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptCriticalityDiag_IE_Lst =
{
#ifdef CM_PASN_DBG
   " szCriticalityDiag_IE_Lst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCriticalityDiag_IE_Lst),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szCriticalityDiag_IE_Lstspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnCriticalityDiag_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnCriticalityDiag_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnCriticalityDiag_ExtIEsClsInfo =
{
   0,
   &sz_ExtnCriticalityDiag_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCriticalityDiag_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnCriticalityDiag_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnCriticalityDiag_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnCriticalityDiag_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnCriticalityDiag_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnCriticalityDiag_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnCriticalityDiag_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_CriticalityDiag_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnCriticalityDiag_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CriticalityDiag_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_CriticalityDiag_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_CriticalityDiag_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_CriticalityDiag_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_CriticalityDiag_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_CriticalityDiag_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_CriticalityDiag_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_CriticalityDiag_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CriticalityDiag_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CriticalityDiag_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CriticalityDiag_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_CriticalityDiag_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_CriticalityDiag_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CriticalityDiag_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_CriticalityDiag_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szCriticalityDiagTkn[] =
{
   &szOptProcedureCode,
   &szOptTrgMsg,
   &szOptCriticality,
   &szOptCriticalityDiag_IE_Lst,
      &szCriticalityDiag_IE_Item,
      &szConstTerm,
   &szOptProtExtnCont_CriticalityDiag_ExtIEs,
      &szProtExtnField_CriticalityDiag_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szCriticalityDiagspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   5,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szCriticalityDiagTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szCriticalityDiag =
{
#ifdef CM_PASN_DBG
   " szCriticalityDiag ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCriticalityDiag),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCriticalityDiagspec),
   NULLP
};
CmPAsnBitStrDef szDataCodingSchemespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTR,
#endif /* CM_PASN_DEBUG */
   8,
   8
};
CmPAsnElmDef szDataCodingScheme =
{
#ifdef CM_PASN_DBG
   " szDataCodingScheme ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztDataCodingScheme),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szDataCodingSchemespec),
   NULLP
};
/* Element ----- DL-Forwarding ------- */
CmPAsnTknEnum szDL_FwdingLst[2] =
{
   1,
   SztDL_FwdingdL_Fwding_proposedEnum
};
CmPAsnEnumDef szDL_Fwdingspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szDL_FwdingLst,
   NULLP
};
CmPAsnElmDef szOptDL_Fwding =
{
#ifdef CM_PASN_DBG
   " szDL_Fwding ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztDL_Fwding),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szDL_Fwdingspec),
   NULLP
};

/* Element ----- Direct-Forwarding-Path-Availability ------- */
CmPAsnTknEnum szDirect_Fwding_Path_AvlbltyLst[2] =
{
   1,
   SztDirect_Fwding_Path_AvlbltydirectPathAvailableEnum
};
CmPAsnEnumDef szDirect_Fwding_Path_Avlbltyspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szDirect_Fwding_Path_AvlbltyLst,
   NULLP
};
CmPAsnElmDef szDirect_Fwding_Path_Avlblty =
{
#ifdef CM_PASN_DBG
   " szDirect_Fwding_Path_Avlblty ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztDirect_Fwding_Path_Avlblty),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szDirect_Fwding_Path_Avlbltyspec),
   NULLP
};

CmPAsnSetSeqOfDef szECGILstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofCellID,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szECGILst =
{
#ifdef CM_PASN_DBG
   " szECGILst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztECGILst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szECGILstspec),
   NULLP
};
CmPAsnSetSeqOfDef szEmergencyAreaIDLstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofEmergencyAreaID,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szEmergencyAreaIDLst =
{
#ifdef CM_PASN_DBG
   " szEmergencyAreaIDLst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztEmergencyAreaIDLst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szEmergencyAreaIDLstspec),
   NULLP
};
CmPAsnBitStrDef szENB_IDmacroENB_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTR,
#endif /* CM_PASN_DEBUG */
   20,
   20
};
CmPAsnElmDef szENB_IDmacroENB_ID =
{
#ifdef CM_PASN_DBG
   " szENB_IDmacroENB_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztENB_IDmacroENB_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szENB_IDmacroENB_IDspec),
   NULLP
};
CmPAsnBitStrDef szENB_IDhomeENB_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTR,
#endif /* CM_PASN_DEBUG */
   28,
   28
};
CmPAsnElmDef szENB_IDhomeENB_ID =
{
#ifdef CM_PASN_DBG
   " szENB_IDhomeENB_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztENB_IDhomeENB_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szENB_IDhomeENB_IDspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szENB_IDTkn[] =
{
   &szENB_IDmacroENB_ID,
   &szENB_IDhomeENB_ID,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szENB_IDspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   2,
   0,
   &szENB_IDTkn[0]  /* Token List */
};
CmPAsnElmDef szENB_ID =
{
#ifdef CM_PASN_DBG
   " szENB_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztENB_ID),
   &flagSz3M,
   NULLP,
   (U8 *)(&szENB_IDspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnLAI_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnLAI_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnLAI_ExtIEsClsInfo =
{
   0,
   &sz_ExtnLAI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnLAI_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnLAI_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnLAI_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnLAI_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnLAI_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnLAI_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnLAI_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_LAI_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnLAI_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_LAI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_LAI_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_LAI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_LAI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_LAI_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_LAI_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_LAI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_LAI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_LAI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_LAI_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_LAI_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_LAI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_LAI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_LAI_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_LAI_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szLAITkn[] =
{
   &szTBCD_STRING,
   &szLAC,
   &szOptProtExtnCont_LAI_ExtIEs,
      &szProtExtnField_LAI_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szLAIspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szLAITkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szLAI =
{
#ifdef CM_PASN_DBG
   " szLAI ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztLAI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szLAIspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnGERAN_Cell_ID_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnGERAN_Cell_ID_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnGERAN_Cell_ID_ExtIEsClsInfo =
{
   0,
   &sz_ExtnGERAN_Cell_ID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnGERAN_Cell_ID_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnGERAN_Cell_ID_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnGERAN_Cell_ID_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnGERAN_Cell_ID_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnGERAN_Cell_ID_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnGERAN_Cell_ID_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnGERAN_Cell_ID_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_GERAN_Cell_ID_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnGERAN_Cell_ID_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_GERAN_Cell_ID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_GERAN_Cell_ID_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_GERAN_Cell_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_GERAN_Cell_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_GERAN_Cell_ID_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_GERAN_Cell_ID_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_GERAN_Cell_ID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_GERAN_Cell_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_GERAN_Cell_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_GERAN_Cell_ID_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_GERAN_Cell_ID_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_GERAN_Cell_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_GERAN_Cell_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_GERAN_Cell_ID_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_GERAN_Cell_ID_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szGERAN_Cell_IDTkn[] =
{
   &szLAI,
   &szRAC,
   &szCI,
   &szOptProtExtnCont_GERAN_Cell_ID_ExtIEs,
      &szProtExtnField_GERAN_Cell_ID_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szGERAN_Cell_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szGERAN_Cell_IDTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szGERAN_Cell_ID =
{
#ifdef CM_PASN_DBG
   " szGERAN_Cell_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztGERAN_Cell_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szGERAN_Cell_IDspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnGlobalENB_ID_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnGlobalENB_ID_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnGlobalENB_ID_ExtIEsClsInfo =
{
   0,
   &sz_ExtnGlobalENB_ID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnGlobalENB_ID_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnGlobalENB_ID_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnGlobalENB_ID_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnGlobalENB_ID_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnGlobalENB_ID_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnGlobalENB_ID_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnGlobalENB_ID_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_GlobalENB_ID_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnGlobalENB_ID_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_GlobalENB_ID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_GlobalENB_ID_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_GlobalENB_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_GlobalENB_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_GlobalENB_ID_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_GlobalENB_ID_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_GlobalENB_ID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_GlobalENB_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_GlobalENB_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_GlobalENB_ID_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_GlobalENB_ID_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_GlobalENB_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_GlobalENB_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_GlobalENB_ID_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_GlobalENB_ID_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szGlobal_ENB_IDTkn[] =
{
   &szTBCD_STRING,
   &szENB_ID,
   &szOptProtExtnCont_GlobalENB_ID_ExtIEs,
      &szProtExtnField_GlobalENB_ID_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szGlobal_ENB_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szGlobal_ENB_IDTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szGlobal_ENB_ID =
{
#ifdef CM_PASN_DBG
   " szGlobal_ENB_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztGlobal_ENB_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szGlobal_ENB_IDspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsInfo =
{
   0,
   &sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnENB_StatusTfr_TprntCont_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnENB_StatusTfr_TprntCont_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_ENB_StatusTfr_TprntCont_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnENB_StatusTfr_TprntCont_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_ENB_StatusTfr_TprntCont_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_ENB_StatusTfr_TprntCont_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_ENB_StatusTfr_TprntCont_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szENB_StatusTfr_TprntContTkn[] =
{
   &szBrs_SubjToStatusTfrLst,
      &szProtIE_Field_Brs_SubjToStatusTfr_ItemIEs,
      &szConstTerm,
   &szOptProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs,
      &szProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szENB_StatusTfr_TprntContspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szENB_StatusTfr_TprntContTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szENB_StatusTfr_TprntCont =
{
#ifdef CM_PASN_DBG
   " szENB_StatusTfr_TprntCont ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztENB_StatusTfr_TprntCont),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szENB_StatusTfr_TprntContspec),
   NULLP
};
/* Element ----- ENB-UE-S1AP-ID ------- */
CmPAsnUIntDef szENB_UE_S1AP_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   16777215UL
};
CmPAsnElmDef szENB_UE_S1AP_ID =
{
#ifdef CM_PASN_DBG
   " szENB_UE_S1AP_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztENB_UE_S1AP_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szENB_UE_S1AP_IDspec),
   NULLP
};
CmPAsnElmDef szOptENB_UE_S1AP_ID =
{
#ifdef CM_PASN_DBG
   " szENB_UE_S1AP_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztENB_UE_S1AP_ID),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szENB_UE_S1AP_IDspec),
   NULLP
};

U32 szENBnameAlpLst[] = {74 , ' ', '\'', '(', ')', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', '=', '?', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
CmPAsnMulStrDef szENBnamespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_PRNSTRXL,
#endif /* CM_PASN_DEBUG */
   szENBnameAlpLst,
   150,
   1,
   122,
   32
};
CmPAsnElmDef szENBname =
{
#ifdef CM_PASN_DBG
   " szENBname " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_PRNSTRXL,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztENBname),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szENBnamespec),
   NULLP
};
CmPAsnBitStrDef szTportLyrAddrspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTRXL,
#endif /* CM_PASN_DEBUG */
   1,
   160
};
CmPAsnElmDef szOptTportLyrAddr =
{
#ifdef CM_PASN_DBG
   " szTportLyrAddr ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTRXL,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTportLyrAddr),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szTportLyrAddrspec),
   NULLP
};
CmPAsnElmDef szTportLyrAddr =
{
#ifdef CM_PASN_DBG
   " szTportLyrAddr ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTRXL,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTportLyrAddr),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szTportLyrAddrspec),
   NULLP
};
CmPAsnSetSeqOfDef szENBX2TLAsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofeNBX2TLAs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szENBX2TLAs =
{
#ifdef CM_PASN_DBG
   " szENBX2TLAs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztENBX2TLAs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szENBX2TLAsspec),
   NULLP
};
CmPAsnBitStrDef szEncryptionAlgorithmsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTR,
#endif /* CM_PASN_DEBUG */
   16,
   16
};
CmPAsnElmDef szEncryptionAlgorithms =
{
#ifdef CM_PASN_DBG
   " szEncryptionAlgorithms ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTR,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztEncryptionAlgorithms),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szEncryptionAlgorithmsspec),
   NULLP
};
CmPAsnSetSeqOfDef szEPLMNsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofEPLMNs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptEPLMNs =
{
#ifdef CM_PASN_DBG
   " szEPLMNs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztEPLMNs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szEPLMNsspec),
   NULLP
};
/* Element ----- EventType ------- */
CmPAsnTknEnum szEventTypLst[4] =
{
   3,
   SztEventTypdirectEnum,
   SztEventTypchange_of_serve_cellEnum,
   SztEventTypstop_change_of_serve_cellEnum
};
CmPAsnEnumDef szEventTypspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szEventTypLst,
   NULLP
};
CmPAsnElmDef szEventTyp =
{
#ifdef CM_PASN_DBG
   " szEventTyp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztEventTyp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szEventTypspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz_ExtnE_RABInformLstItem_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABInformLstItem_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABInformLstItem_ExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABInformLstItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABInformLstItem_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABInformLstItem_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABInformLstItem_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABInformLstItem_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABInformLstItem_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABInformLstItem_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABInformLstItem_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABInformLstItem_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABInformLstItem_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABInformLstItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABInformLstItem_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABInformLstItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABInformLstItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABInformLstItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABInformLstItem_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABInformLstItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABInformLstItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABInformLstItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABInformLstItem_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABInformLstItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABInformLstItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABInformLstItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABInformLstItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABInformLstItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABInformLstItemTkn[] =
{
   &szE_RAB_ID,
   &szOptDL_Fwding,
   &szOptProtExtnCont_E_RABInformLstItem_ExtIEs,
      &szProtExtnField_E_RABInformLstItem_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABInformLstItemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   2,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABInformLstItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABInformLstItem =
{
#ifdef CM_PASN_DBG
   " szE_RABInformLstItem ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABInformLstItem),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABInformLstItemspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABInformLstIEsClsInst[] =
{
   &szE_RABInformLstItem
};
PUBLIC U32 sz_ValueE_RABInformLstIEsClsInstId[] =
{
   Sztid_E_RABInformLstItem
};
SzMsgConInf szE_RABInformLstIEsConInf =
{
   {
      { Sztid_E_RABInformLstItem, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABInformLstIEsClsInfo =
{
   1,
   &sz_ValueE_RABInformLstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABInformLstIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABInformLstIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABInformLstIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABInformLstIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABInformLstIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABInformLstIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABInformLstIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABInformLstIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABInformLstIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABInformLstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABInformLstIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABInformLstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABInformLstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABInformLstIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABInformLstIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABInformLstIEs szProtIE_Field_E_RABInformLstIEs
CmPAsnSetSeqOfDef szE_RABInformLstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptE_RABInformLst =
{
#ifdef CM_PASN_DBG
   " szE_RABInformLst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztE_RABInformLst),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szE_RABInformLstspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABItem_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABItem_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABItem_ExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABItem_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABItem_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABItem_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABItem_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABItem_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABItem_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABItem_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABItem_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABItem_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABItem_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABItem_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABItem_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABItemTkn[] =
{
   &szE_RAB_ID,
   &szCause,
   &szOptProtExtnCont_E_RABItem_ExtIEs,
      &szProtExtnField_E_RABItem_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABItemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABItem =
{
#ifdef CM_PASN_DBG
   " szE_RABItem ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABItem),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABItemspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABItemIEsClsInst[] =
{
   &szE_RABItem
};
PUBLIC U32 sz_ValueE_RABItemIEsClsInstId[] =
{
   Sztid_E_RABItem
};
SzMsgConInf szE_RABItemIEsConInf =
{
   {
      { Sztid_E_RABItem, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABItemIEsClsInfo =
{
   1,
   &sz_ValueE_RABItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABItemIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABItemIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABItemIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABItemIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABItemIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABItemIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABItemIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABItemIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABItemIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABItemIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABItemIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABItemIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABItemIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABItemIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABItemIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABItemIEs szProtIE_Field_E_RABItemIEs
CmPAsnSetSeqOfDef szE_RABLstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szE_RABLst =
{
#ifdef CM_PASN_DBG
   " szE_RABLst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztE_RABLst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szE_RABLstspec),
   NULLP
};
/* Element ----- QCI ------- */
CmPAsnUIntDef szQCIspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   255UL
};
CmPAsnElmDef szQCI =
{
#ifdef CM_PASN_DBG
   " szQCI ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztQCI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szQCIspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz_ExtnGBR_QosInform_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnGBR_QosInform_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnGBR_QosInform_ExtIEsClsInfo =
{
   0,
   &sz_ExtnGBR_QosInform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnGBR_QosInform_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnGBR_QosInform_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnGBR_QosInform_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnGBR_QosInform_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnGBR_QosInform_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnGBR_QosInform_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnGBR_QosInform_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_GBR_QosInform_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnGBR_QosInform_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_GBR_QosInform_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_GBR_QosInform_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_GBR_QosInform_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_GBR_QosInform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_GBR_QosInform_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_GBR_QosInform_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_GBR_QosInform_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_GBR_QosInform_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_GBR_QosInform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_GBR_QosInform_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_GBR_QosInform_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_GBR_QosInform_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_GBR_QosInform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_GBR_QosInform_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_GBR_QosInform_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szGBR_QosInformTkn[] =
{
   &szBitRate,
   &szBitRate,
   &szBitRate,
   &szBitRate,
   &szOptProtExtnCont_GBR_QosInform_ExtIEs,
      &szProtExtnField_GBR_QosInform_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szGBR_QosInformspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szGBR_QosInformTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szGBR_QosInform =
{
#ifdef CM_PASN_DBG
   " szGBR_QosInform ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztGBR_QosInform),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szGBR_QosInformspec),
   NULLP
};
PUBLIC CmPAsnElmDef szOptGBR_QosInform =
{
#ifdef CM_PASN_DBG
   " szGBR_QosInform ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztGBR_QosInform),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szGBR_QosInformspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABQoSParams_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABQoSParams_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABQoSParams_ExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABQoSParams_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABQoSParams_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABQoSParams_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABQoSParams_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABQoSParams_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABQoSParams_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABQoSParams_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABQoSParams_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABQoSParams_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABQoSParams_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABQoSParams_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABQoSParams_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABQoSParams_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABQoSParams_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABQoSParams_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABQoSParams_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABQoSParams_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABQoSParams_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABQoSParams_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABQoSParams_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABQoSParams_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABQoSParams_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABQoSParams_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABQoSParams_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABQoSParams_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABLvlQoSParamsTkn[] =
{
   &szQCI,
   &szAllocnAndRetentionPriority,
   &szOptGBR_QosInform,
   &szOptProtExtnCont_E_RABQoSParams_ExtIEs,
      &szProtExtnField_E_RABQoSParams_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABLvlQoSParamsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   2,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABLvlQoSParamsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABLvlQoSParams =
{
#ifdef CM_PASN_DBG
   " szE_RABLvlQoSParams ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABLvlQoSParams),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABLvlQoSParamsspec),
   NULLP
};
/* Element ----- ExtendedRNC-ID ------- */
CmPAsnUIntDef szExtendedRNC_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   4096,
   65535UL
};
CmPAsnElmDef szOptExtendedRNC_ID =
{
#ifdef CM_PASN_DBG
   " szExtendedRNC_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztExtendedRNC_ID),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szExtendedRNC_IDspec),
   NULLP
};

/* Element ----- ForbiddenInterRATs ------- */
CmPAsnTknEnum szForbiddenInterRATsLst[5] =
{
   4,
   SztForbiddenInterRATsallEnum,
   SztForbiddenInterRATsgeranEnum,
   SztForbiddenInterRATsutranEnum,
   SztForbiddenInterRATscdma2000Enum
};
CmPAsnEnumDef szForbiddenInterRATsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szForbiddenInterRATsLst,
   NULLP
};
CmPAsnElmDef szOptForbiddenInterRATs =
{
#ifdef CM_PASN_DBG
   " szForbiddenInterRATs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztForbiddenInterRATs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szForbiddenInterRATsspec),
   NULLP
};

CmPAsnSetSeqOfDef szForbiddenTACsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofForbTACs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szForbiddenTACs =
{
#ifdef CM_PASN_DBG
   " szForbiddenTACs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztForbiddenTACs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szForbiddenTACsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnForbiddenTAs_Item_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnForbiddenTAs_Item_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnForbiddenTAs_Item_ExtIEsClsInfo =
{
   0,
   &sz_ExtnForbiddenTAs_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnForbiddenTAs_Item_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnForbiddenTAs_Item_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnForbiddenTAs_Item_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnForbiddenTAs_Item_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnForbiddenTAs_Item_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnForbiddenTAs_Item_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnForbiddenTAs_Item_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_ForbiddenTAs_Item_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnForbiddenTAs_Item_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_ForbiddenTAs_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_ForbiddenTAs_Item_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_ForbiddenTAs_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_ForbiddenTAs_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_ForbiddenTAs_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_ForbiddenTAs_Item_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_ForbiddenTAs_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_ForbiddenTAs_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_ForbiddenTAs_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_ForbiddenTAs_Item_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_ForbiddenTAs_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_ForbiddenTAs_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_ForbiddenTAs_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_ForbiddenTAs_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_ForbiddenTAs_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szForbiddenTAs_ItemTkn[] =
{
   &szTBCD_STRING,
   &szForbiddenTACs,
      &szTAC,
      &szConstTerm,
   &szOptProtExtnCont_ForbiddenTAs_Item_ExtIEs,
      &szProtExtnField_ForbiddenTAs_Item_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szForbiddenTAs_Itemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szForbiddenTAs_ItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szForbiddenTAs_Item =
{
#ifdef CM_PASN_DBG
   " szForbiddenTAs_Item ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztForbiddenTAs_Item),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szForbiddenTAs_Itemspec),
   NULLP
};
CmPAsnSetSeqOfDef szForbiddenTAsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofEPLMNsPlusOne,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptForbiddenTAs =
{
#ifdef CM_PASN_DBG
   " szForbiddenTAs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztForbiddenTAs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szForbiddenTAsspec),
   NULLP
};
CmPAsnSetSeqOfDef szForbiddenLACsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofForbLACs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szForbiddenLACs =
{
#ifdef CM_PASN_DBG
   " szForbiddenLACs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztForbiddenLACs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szForbiddenLACsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnForbiddenLAs_Item_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnForbiddenLAs_Item_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnForbiddenLAs_Item_ExtIEsClsInfo =
{
   0,
   &sz_ExtnForbiddenLAs_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnForbiddenLAs_Item_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnForbiddenLAs_Item_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnForbiddenLAs_Item_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnForbiddenLAs_Item_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnForbiddenLAs_Item_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnForbiddenLAs_Item_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnForbiddenLAs_Item_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_ForbiddenLAs_Item_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnForbiddenLAs_Item_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_ForbiddenLAs_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_ForbiddenLAs_Item_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_ForbiddenLAs_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_ForbiddenLAs_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_ForbiddenLAs_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_ForbiddenLAs_Item_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_ForbiddenLAs_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_ForbiddenLAs_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_ForbiddenLAs_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_ForbiddenLAs_Item_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_ForbiddenLAs_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_ForbiddenLAs_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_ForbiddenLAs_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_ForbiddenLAs_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_ForbiddenLAs_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szForbiddenLAs_ItemTkn[] =
{
   &szTBCD_STRING,
   &szForbiddenLACs,
      &szLAC,
      &szConstTerm,
   &szOptProtExtnCont_ForbiddenLAs_Item_ExtIEs,
      &szProtExtnField_ForbiddenLAs_Item_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szForbiddenLAs_Itemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szForbiddenLAs_ItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szForbiddenLAs_Item =
{
#ifdef CM_PASN_DBG
   " szForbiddenLAs_Item ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztForbiddenLAs_Item),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szForbiddenLAs_Itemspec),
   NULLP
};
CmPAsnSetSeqOfDef szForbiddenLAsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofEPLMNsPlusOne,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptForbiddenLAs =
{
#ifdef CM_PASN_DBG
   " szForbiddenLAs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztForbiddenLAs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szForbiddenLAsspec),
   NULLP
};
CmPAsnOctStrDef szGTP_TEIDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   4,
   4
};
CmPAsnElmDef szOptGTP_TEID =
{
#ifdef CM_PASN_DBG
   " szGTP_TEID " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztGTP_TEID),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szGTP_TEIDspec),
   NULLP
};
CmPAsnElmDef szGTP_TEID =
{
#ifdef CM_PASN_DBG
   " szGTP_TEID " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztGTP_TEID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szGTP_TEIDspec),
   NULLP
};
CmPAsnOctStrDef szMME_Group_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTR,
#endif /* CM_PASN_DEBUG */
   2,
   2
};
CmPAsnElmDef szMME_Group_ID =
{
#ifdef CM_PASN_DBG
   " szMME_Group_ID " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztMME_Group_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szMME_Group_IDspec),
   NULLP
};
CmPAsnOctStrDef szMME_Codespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTR,
#endif /* CM_PASN_DEBUG */
   1,
   1
};
CmPAsnElmDef szMME_Code =
{
#ifdef CM_PASN_DBG
   " szMME_Code " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztMME_Code),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szMME_Codespec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnGUMMEI_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnGUMMEI_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnGUMMEI_ExtIEsClsInfo =
{
   0,
   &sz_ExtnGUMMEI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnGUMMEI_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnGUMMEI_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnGUMMEI_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnGUMMEI_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnGUMMEI_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnGUMMEI_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnGUMMEI_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_GUMMEI_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnGUMMEI_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_GUMMEI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_GUMMEI_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_GUMMEI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_GUMMEI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_GUMMEI_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_GUMMEI_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_GUMMEI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_GUMMEI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_GUMMEI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_GUMMEI_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_GUMMEI_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_GUMMEI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_GUMMEI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_GUMMEI_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_GUMMEI_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szGUMMEITkn[] =
{
   &szTBCD_STRING,
   &szMME_Group_ID,
   &szMME_Code,
   &szOptProtExtnCont_GUMMEI_ExtIEs,
      &szProtExtnField_GUMMEI_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szGUMMEIspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szGUMMEITkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szGUMMEI =
{
#ifdef CM_PASN_DBG
   " szGUMMEI ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztGUMMEI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szGUMMEIspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnHovrRestrnLst_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnHovrRestrnLst_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnHovrRestrnLst_ExtIEsClsInfo =
{
   0,
   &sz_ExtnHovrRestrnLst_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnHovrRestrnLst_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnHovrRestrnLst_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnHovrRestrnLst_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnHovrRestrnLst_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnHovrRestrnLst_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnHovrRestrnLst_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnHovrRestrnLst_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_HovrRestrnLst_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnHovrRestrnLst_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_HovrRestrnLst_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_HovrRestrnLst_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_HovrRestrnLst_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_HovrRestrnLst_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_HovrRestrnLst_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_HovrRestrnLst_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_HovrRestrnLst_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_HovrRestrnLst_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_HovrRestrnLst_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_HovrRestrnLst_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_HovrRestrnLst_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_HovrRestrnLst_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_HovrRestrnLst_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_HovrRestrnLst_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_HovrRestrnLst_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szHovrRestrnLstTkn[] =
{
   &szTBCD_STRING,
   &szOptEPLMNs,
      &szTBCD_STRING,
      &szConstTerm,
   &szOptForbiddenTAs,
      &szForbiddenTAs_Item,
      &szConstTerm,
   &szOptForbiddenLAs,
      &szForbiddenLAs_Item,
      &szConstTerm,
   &szOptForbiddenInterRATs,
   &szOptProtExtnCont_HovrRestrnLst_ExtIEs,
      &szProtExtnField_HovrRestrnLst_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szHovrRestrnLstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   5,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szHovrRestrnLstTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szHovrRestrnLst =
{
#ifdef CM_PASN_DBG
   " szHovrRestrnLst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztHovrRestrnLst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szHovrRestrnLstspec),
   NULLP
};
/* Element ----- HandoverType ------- */
CmPAsnTknEnum szHovrTypLst[6] =
{
   5,
   SztHovrTypintralteEnum,
   SztHovrTypltetoutranEnum,
   SztHovrTypltetogeranEnum,
   SztHovrTyputrantolteEnum,
   SztHovrTypgerantolteEnum
};
CmPAsnEnumDef szHovrTypspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szHovrTypLst,
   NULLP
};
CmPAsnElmDef szHovrTyp =
{
#ifdef CM_PASN_DBG
   " szHovrTyp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztHovrTyp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szHovrTypspec),
   NULLP
};

CmPAsnOctStrDef szIMSIspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   3,
   8
};
CmPAsnElmDef szIMSI =
{
#ifdef CM_PASN_DBG
   " szIMSI " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztIMSI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szIMSIspec),
   NULLP
};
CmPAsnBitStrDef szIntegrityProtectionAlgorithmsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTR,
#endif /* CM_PASN_DEBUG */
   16,
   16
};
CmPAsnElmDef szIntegrityProtectionAlgorithms =
{
#ifdef CM_PASN_DBG
   " szIntegrityProtectionAlgorithms ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTR,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztIntegrityProtectionAlgorithms),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szIntegrityProtectionAlgorithmsspec),
   NULLP
};
CmPAsnBitStrDef szIntfsToTracespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTR,
#endif /* CM_PASN_DEBUG */
   8,
   8
};
CmPAsnElmDef szIntfsToTrace =
{
#ifdef CM_PASN_DBG
   " szIntfsToTrace ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztIntfsToTrace),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szIntfsToTracespec),
   NULLP
};
/* Element ----- Time-UE-StayedInCell ------- */
CmPAsnUIntDef szTime_UE_StayedInCellspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   4095UL
};
CmPAsnElmDef szTime_UE_StayedInCell =
{
#ifdef CM_PASN_DBG
   " szTime_UE_StayedInCell ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTime_UE_StayedInCell),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTime_UE_StayedInCellspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInfo =
{
   0,
   &sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnLastVisitedEUTRANCellInform_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnLastVisitedEUTRANCellInform_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_LastVisitedEUTRANCellInform_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnLastVisitedEUTRANCellInform_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_LastVisitedEUTRANCellInform_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_LastVisitedEUTRANCellInform_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_LastVisitedEUTRANCellInform_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_LastVisitedEUTRANCellInform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_LastVisitedEUTRANCellInform_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_LastVisitedEUTRANCellInform_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_LastVisitedEUTRANCellInform_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_LastVisitedEUTRANCellInform_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szLastVisitedEUTRANCellInformTkn[] =
{
   &szEUTRAN_CGI,
   &szCellTyp,
   &szTime_UE_StayedInCell,
   &szOptProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs,
      &szProtExtnField_LastVisitedEUTRANCellInform_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szLastVisitedEUTRANCellInformspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szLastVisitedEUTRANCellInformTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szLastVisitedEUTRANCellInform =
{
#ifdef CM_PASN_DBG
   " szLastVisitedEUTRANCellInform ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztLastVisitedEUTRANCellInform),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szLastVisitedEUTRANCellInformspec),
   NULLP
};
CmPAsnOctStrDef szLastVisitedUTRANCellInformspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szLastVisitedUTRANCellInform =
{
#ifdef CM_PASN_DBG
   " szLastVisitedUTRANCellInform " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztLastVisitedUTRANCellInform),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szLastVisitedUTRANCellInformspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szLastVisitedGERANCellInformTkn[] =
{
   &szNull,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szLastVisitedGERANCellInformspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   1,
   0,
   &szLastVisitedGERANCellInformTkn[0]  /* Token List */
};
CmPAsnElmDef szLastVisitedGERANCellInform =
{
#ifdef CM_PASN_DBG
   " szLastVisitedGERANCellInform ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztLastVisitedGERANCellInform),
   &flagSz3M,
   NULLP,
   (U8 *)(&szLastVisitedGERANCellInformspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szLastVisitedCell_ItemTkn[] =
{
   &szLastVisitedEUTRANCellInform,
   &szLastVisitedUTRANCellInform,
   &szLastVisitedGERANCellInform,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szLastVisitedCell_Itemspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   3,
   0,
   &szLastVisitedCell_ItemTkn[0]  /* Token List */
};
CmPAsnElmDef szLastVisitedCell_Item =
{
#ifdef CM_PASN_DBG
   " szLastVisitedCell_Item ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztLastVisitedCell_Item),
   &flagSz3M,
   NULLP,
   (U8 *)(&szLastVisitedCell_Itemspec),
   NULLP
};
CmPAsnOctStrDef szL3_Informspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szL3_Inform =
{
#ifdef CM_PASN_DBG
   " szL3_Inform " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztL3_Inform),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szL3_Informspec),
   NULLP
};
CmPAsnBitStrDef szMsgIdentifierspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTR,
#endif /* CM_PASN_DEBUG */
   16,
   16
};
CmPAsnElmDef szMsgIdentifier =
{
#ifdef CM_PASN_DBG
   " szMsgIdentifier ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztMsgIdentifier),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szMsgIdentifierspec),
   NULLP
};
U32 szMMEnameAlpLst[] = {74 , ' ', '\'', '(', ')', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', '=', '?', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
CmPAsnMulStrDef szMMEnamespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_PRNSTRXL,
#endif /* CM_PASN_DEBUG */
   szMMEnameAlpLst,
   150,
   1,
   122,
   32
};
CmPAsnElmDef szMMEname =
{
#ifdef CM_PASN_DBG
   " szMMEname " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_PRNSTRXL,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztMMEname),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szMMEnamespec),
   NULLP
};
/* Element ----- MME-UE-S1AP-ID ------- */
CmPAsnUIntDef szMME_UE_S1AP_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   4294967295UL
};
CmPAsnElmDef szMME_UE_S1AP_ID =
{
#ifdef CM_PASN_DBG
   " szMME_UE_S1AP_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztMME_UE_S1AP_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szMME_UE_S1AP_IDspec),
   NULLP
};
CmPAsnElmDef szOptMME_UE_S1AP_ID =
{
#ifdef CM_PASN_DBG
   " szMME_UE_S1AP_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztMME_UE_S1AP_ID),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szMME_UE_S1AP_IDspec),
   NULLP
};

CmPAsnOctStrDef szM_TMSIspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   4,
   4
};
CmPAsnElmDef szM_TMSI =
{
#ifdef CM_PASN_DBG
   " szM_TMSI " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztM_TMSI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szM_TMSIspec),
   NULLP
};
CmPAsnOctStrDef szMSClassmark2spec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szMSClassmark2 =
{
#ifdef CM_PASN_DBG
   " szMSClassmark2 " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztMSClassmark2),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szMSClassmark2spec),
   NULLP
};
CmPAsnOctStrDef szMSClassmark3spec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szMSClassmark3 =
{
#ifdef CM_PASN_DBG
   " szMSClassmark3 " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztMSClassmark3),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szMSClassmark3spec),
   NULLP
};
CmPAsnOctStrDef szNAS_PDUspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szOptNAS_PDU =
{
#ifdef CM_PASN_DBG
   " szNAS_PDU " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztNAS_PDU),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szNAS_PDUspec),
   NULLP
};
CmPAsnElmDef szNAS_PDU =
{
#ifdef CM_PASN_DBG
   " szNAS_PDU " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztNAS_PDU),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szNAS_PDUspec),
   NULLP
};
CmPAsnOctStrDef szNASSecurParamsfromE_UTRANspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szNASSecurParamsfromE_UTRAN =
{
#ifdef CM_PASN_DBG
   " szNASSecurParamsfromE_UTRAN " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztNASSecurParamsfromE_UTRAN),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szNASSecurParamsfromE_UTRANspec),
   NULLP
};
CmPAsnOctStrDef szNASSecurParamstoE_UTRANspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szNASSecurParamstoE_UTRAN =
{
#ifdef CM_PASN_DBG
   " szNASSecurParamstoE_UTRAN " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztNASSecurParamstoE_UTRAN),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szNASSecurParamstoE_UTRANspec),
   NULLP
};
/* Element ----- NumberofBroadcastRequest ------- */
CmPAsnUIntDef szNumberofBroadcastRqstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   65535UL
};
CmPAsnElmDef szNumberofBroadcastRqst =
{
#ifdef CM_PASN_DBG
   " szNumberofBroadcastRqst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztNumberofBroadcastRqst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szNumberofBroadcastRqstspec),
   NULLP
};

/* Element ----- NumberofBroadcast ------- */
CmPAsnUIntDef szNumberofBroadcastspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   65535UL
};

CmPAsnOctStrDef szOldBSS_ToNewBSS_Informspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szOldBSS_ToNewBSS_Inform =
{
#ifdef CM_PASN_DBG
   " szOldBSS_ToNewBSS_Inform " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztOldBSS_ToNewBSS_Inform),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szOldBSS_ToNewBSS_Informspec),
   NULLP
};
/* Element ----- OverloadAction ------- */
CmPAsnTknEnum szOverloadActionLst[4] =
{
   3,
   SztOverloadActionreject_non_emergency_mo_dtEnum,
   SztOverloadActionreject_all_rrc_cr_signallingEnum,
   SztOverloadActionpermit_emergency_sessions_onlyEnum
};
CmPAsnEnumDef szOverloadActionspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szOverloadActionLst,
   NULLP
};
CmPAsnElmDef szOverloadAction =
{
#ifdef CM_PASN_DBG
   " szOverloadAction ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztOverloadAction),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szOverloadActionspec),
   NULLP
};

PUBLIC CmPAsnElmDef *szOverloadRespTkn[] =
{
   &szOverloadAction,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szOverloadRespspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   1,
   0,
   &szOverloadRespTkn[0]  /* Token List */
};
CmPAsnElmDef szOverloadResp =
{
#ifdef CM_PASN_DBG
   " szOverloadResp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztOverloadResp),
   &flagSz3M,
   NULLP,
   (U8 *)(&szOverloadRespspec),
   NULLP
};
/* Element ----- PagingDRX ------- */
CmPAsnTknEnum szPagDRXLst[5] =
{
   4,
   SztPagDRXv32Enum,
   SztPagDRXv64Enum,
   SztPagDRXv128Enum,
   SztPagDRXv256Enum
};
CmPAsnEnumDef szPagDRXspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szPagDRXLst,
   NULLP
};
CmPAsnElmDef szPagDRX =
{
#ifdef CM_PASN_DBG
   " szPagDRX ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztPagDRX),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szPagDRXspec),
   NULLP
};

/* Element ----- RelativeMMECapacity ------- */
CmPAsnUIntDef szRelativeMMECapacityspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   255UL
};
CmPAsnElmDef szRelativeMMECapacity =
{
#ifdef CM_PASN_DBG
   " szRelativeMMECapacity ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztRelativeMMECapacity),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szRelativeMMECapacityspec),
   NULLP
};

/* Element ----- ReportArea ------- */
CmPAsnTknEnum szReportAreaLst[2] =
{
   1,
   SztReportAreaecgiEnum
};
CmPAsnEnumDef szReportAreaspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szReportAreaLst,
   NULLP
};
CmPAsnElmDef szReportArea =
{
#ifdef CM_PASN_DBG
   " szReportArea ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztReportArea),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szReportAreaspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz_ExtnRqstTyp_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnRqstTyp_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnRqstTyp_ExtIEsClsInfo =
{
   0,
   &sz_ExtnRqstTyp_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnRqstTyp_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnRqstTyp_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnRqstTyp_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnRqstTyp_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnRqstTyp_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnRqstTyp_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnRqstTyp_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_RqstTyp_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnRqstTyp_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_RqstTyp_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_RqstTyp_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_RqstTyp_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_RqstTyp_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_RqstTyp_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_RqstTyp_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_RqstTyp_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_RqstTyp_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_RqstTyp_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_RqstTyp_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_RqstTyp_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_RqstTyp_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_RqstTyp_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_RqstTyp_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_RqstTyp_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szRqstTypTkn[] =
{
   &szEventTyp,
   &szReportArea,
   &szOptProtExtnCont_RqstTyp_ExtIEs,
      &szProtExtnField_RqstTyp_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szRqstTypspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szRqstTypTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szRqstTyp =
{
#ifdef CM_PASN_DBG
   " szRqstTyp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztRqstTyp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szRqstTypspec),
   NULLP
};
CmPAsnOctStrDef szRIMInformspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szRIMInform =
{
#ifdef CM_PASN_DBG
   " szRIMInform " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztRIMInform),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szRIMInformspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szRIMRoutingAddrTkn[] =
{
   &szGERAN_Cell_ID,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szRIMRoutingAddrspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   1,
   0,
   &szRIMRoutingAddrTkn[0]  /* Token List */
};
CmPAsnElmDef szRIMRoutingAddr =
{
#ifdef CM_PASN_DBG
   " szRIMRoutingAddr ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztRIMRoutingAddr),
   &flagSz3M,
   NULLP,
   (U8 *)(&szRIMRoutingAddrspec),
   NULLP
};
CmPAsnElmDef szOptRIMRoutingAddr =
{
#ifdef CM_PASN_DBG
   " szRIMRoutingAddr ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztRIMRoutingAddr),
   &flagSz3O,
   NULLP,
   (U8 *)(&szRIMRoutingAddrspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnRIMTfr_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnRIMTfr_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnRIMTfr_ExtIEsClsInfo =
{
   0,
   &sz_ExtnRIMTfr_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnRIMTfr_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnRIMTfr_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnRIMTfr_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnRIMTfr_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnRIMTfr_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnRIMTfr_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnRIMTfr_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_RIMTfr_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnRIMTfr_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_RIMTfr_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_RIMTfr_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_RIMTfr_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_RIMTfr_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_RIMTfr_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_RIMTfr_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_RIMTfr_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_RIMTfr_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_RIMTfr_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_RIMTfr_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_RIMTfr_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_RIMTfr_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_RIMTfr_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_RIMTfr_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_RIMTfr_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szRIMTfrTkn[] =
{
   &szRIMInform,
   &szOptRIMRoutingAddr,
   &szOptProtExtnCont_RIMTfr_ExtIEs,
      &szProtExtnField_RIMTfr_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szRIMTfrspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   2,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szRIMTfrTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szRIMTfr =
{
#ifdef CM_PASN_DBG
   " szRIMTfr ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztRIMTfr),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szRIMTfrspec),
   NULLP
};
/* Element ----- RepetitionPeriod ------- */
CmPAsnUIntDef szRepetitionPeriodspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   4095UL
};
CmPAsnElmDef szRepetitionPeriod =
{
#ifdef CM_PASN_DBG
   " szRepetitionPeriod ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztRepetitionPeriod),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szRepetitionPeriodspec),
   NULLP
};

/* Element ----- RNC-ID ------- */
CmPAsnUIntDef szRNC_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   4095UL
};
CmPAsnElmDef szRNC_ID =
{
#ifdef CM_PASN_DBG
   " szRNC_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztRNC_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szRNC_IDspec),
   NULLP
};

CmPAsnOctStrDef szRRC_Contspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szRRC_Cont =
{
#ifdef CM_PASN_DBG
   " szRRC_Cont " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztRRC_Cont),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szRRC_Contspec),
   NULLP
};
/* Element ----- RRC-Establishment-Cause ------- */
CmPAsnTknEnum szRRC_Establishment_CauseLst[6] =
{
   5,
   SztRRC_Establishment_CauseemergencyEnum,
   SztRRC_Establishment_CausehighPriorityAccessEnum,
   SztRRC_Establishment_Causemt_AccessEnum,
   SztRRC_Establishment_Causemo_SignallingEnum,
   SztRRC_Establishment_Causemo_DataEnum
};
CmPAsnEnumDef szRRC_Establishment_Causespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szRRC_Establishment_CauseLst,
   NULLP
};
CmPAsnElmDef szRRC_Establishment_Cause =
{
#ifdef CM_PASN_DBG
   " szRRC_Establishment_Cause ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztRRC_Establishment_Cause),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szRRC_Establishment_Causespec),
   NULLP
};

CmPAsnBitStrDef szSecurKeyspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTRXL,
#endif /* CM_PASN_DEBUG */
   256,
   256
};
CmPAsnElmDef szSecurKey =
{
#ifdef CM_PASN_DBG
   " szSecurKey ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSecurKey),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szSecurKeyspec),
   NULLP
};
/* Element ----- nextHopChainingCount ------- */
CmPAsnUIntDef szSecurCntxtnextHopChainingCountspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   7UL
};
CmPAsnElmDef szSecurCntxtnextHopChainingCount =
{
#ifdef CM_PASN_DBG
   " szSecurCntxtnextHopChainingCount ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSecurCntxtnextHopChainingCount),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSecurCntxtnextHopChainingCountspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz_ExtnSecurCntxt_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnSecurCntxt_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnSecurCntxt_ExtIEsClsInfo =
{
   0,
   &sz_ExtnSecurCntxt_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSecurCntxt_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnSecurCntxt_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnSecurCntxt_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnSecurCntxt_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnSecurCntxt_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnSecurCntxt_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnSecurCntxt_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_SecurCntxt_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnSecurCntxt_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SecurCntxt_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_SecurCntxt_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_SecurCntxt_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_SecurCntxt_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_SecurCntxt_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_SecurCntxt_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_SecurCntxt_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_SecurCntxt_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SecurCntxt_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SecurCntxt_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SecurCntxt_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_SecurCntxt_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SecurCntxt_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SecurCntxt_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SecurCntxt_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szSecurCntxtTkn[] =
{
   &szSecurCntxtnextHopChainingCount,
   &szSecurKey,
   &szOptProtExtnCont_SecurCntxt_ExtIEs,
      &szProtExtnField_SecurCntxt_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szSecurCntxtspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szSecurCntxtTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szSecurCntxt =
{
#ifdef CM_PASN_DBG
   " szSecurCntxt ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztSecurCntxt),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSecurCntxtspec),
   NULLP
};
CmPAsnBitStrDef szSerialNumberspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTR,
#endif /* CM_PASN_DEBUG */
   16,
   16
};
CmPAsnElmDef szSerialNumber =
{
#ifdef CM_PASN_DBG
   " szSerialNumber ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSerialNumber),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szSerialNumberspec),
   NULLP
};
/* Element ----- SONInformationRequest ------- */
CmPAsnTknEnum szSONInformRqstLst[2] =
{
   1,
   SztSONInformRqstx2TNL_Config_InfoEnum
};
CmPAsnEnumDef szSONInformRqstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szSONInformRqstLst,
   NULLP
};
CmPAsnElmDef szSONInformRqst =
{
#ifdef CM_PASN_DBG
   " szSONInformRqst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztSONInformRqst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSONInformRqstspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz_ExtnX2TNLConfigInfo_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnX2TNLConfigInfo_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnX2TNLConfigInfo_ExtIEsClsInfo =
{
   0,
   &sz_ExtnX2TNLConfigInfo_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnX2TNLConfigInfo_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnX2TNLConfigInfo_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnX2TNLConfigInfo_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnX2TNLConfigInfo_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnX2TNLConfigInfo_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnX2TNLConfigInfo_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnX2TNLConfigInfo_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_X2TNLConfigInfo_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnX2TNLConfigInfo_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_X2TNLConfigInfo_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_X2TNLConfigInfo_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_X2TNLConfigInfo_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_X2TNLConfigInfo_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_X2TNLConfigInfo_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_X2TNLConfigInfo_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_X2TNLConfigInfo_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_X2TNLConfigInfo_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_X2TNLConfigInfo_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_X2TNLConfigInfo_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_X2TNLConfigInfo_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_X2TNLConfigInfo_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_X2TNLConfigInfo_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_X2TNLConfigInfo_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_X2TNLConfigInfo_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szX2TNLConfigInfoTkn[] =
{
   &szENBX2TLAs,
      &szTportLyrAddr,
      &szConstTerm,
   &szOptProtExtnCont_X2TNLConfigInfo_ExtIEs,
      &szProtExtnField_X2TNLConfigInfo_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szX2TNLConfigInfospec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szX2TNLConfigInfoTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szX2TNLConfigInfo =
{
#ifdef CM_PASN_DBG
   " szX2TNLConfigInfo ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztX2TNLConfigInfo),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szX2TNLConfigInfospec),
   NULLP
};
PUBLIC CmPAsnElmDef szOptX2TNLConfigInfo =
{
#ifdef CM_PASN_DBG
   " szX2TNLConfigInfo ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztX2TNLConfigInfo),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szX2TNLConfigInfospec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnSONInformReply_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnSONInformReply_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnSONInformReply_ExtIEsClsInfo =
{
   0,
   &sz_ExtnSONInformReply_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSONInformReply_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnSONInformReply_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnSONInformReply_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnSONInformReply_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnSONInformReply_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnSONInformReply_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnSONInformReply_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_SONInformReply_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnSONInformReply_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SONInformReply_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_SONInformReply_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_SONInformReply_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_SONInformReply_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_SONInformReply_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_SONInformReply_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_SONInformReply_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_SONInformReply_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SONInformReply_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SONInformReply_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SONInformReply_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_SONInformReply_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SONInformReply_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SONInformReply_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SONInformReply_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szSONInformReplyTkn[] =
{
   &szOptX2TNLConfigInfo,
   &szOptProtExtnCont_SONInformReply_ExtIEs,
      &szProtExtnField_SONInformReply_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szSONInformReplyspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   2,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szSONInformReplyTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szSONInformReply =
{
#ifdef CM_PASN_DBG
   " szSONInformReply ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztSONInformReply),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSONInformReplyspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szSONInformTkn[] =
{
   &szSONInformRqst,
   &szSONInformReply,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szSONInformspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   2,
   0,
   &szSONInformTkn[0]  /* Token List */
};
CmPAsnElmDef szSONInform =
{
#ifdef CM_PASN_DBG
   " szSONInform ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztSONInform),
   &flagSz3M,
   NULLP,
   (U8 *)(&szSONInformspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnTgeteNB_ID_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnTgeteNB_ID_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnTgeteNB_ID_ExtIEsClsInfo =
{
   0,
   &sz_ExtnTgeteNB_ID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTgeteNB_ID_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnTgeteNB_ID_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnTgeteNB_ID_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnTgeteNB_ID_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnTgeteNB_ID_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnTgeteNB_ID_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnTgeteNB_ID_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_TgeteNB_ID_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnTgeteNB_ID_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TgeteNB_ID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_TgeteNB_ID_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_TgeteNB_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_TgeteNB_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_TgeteNB_ID_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_TgeteNB_ID_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_TgeteNB_ID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_TgeteNB_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TgeteNB_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TgeteNB_ID_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TgeteNB_ID_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_TgeteNB_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TgeteNB_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TgeteNB_ID_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TgeteNB_ID_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szTgeteNB_IDTkn[] =
{
   &szGlobal_ENB_ID,
   &szTAI,
   &szOptProtExtnCont_TgeteNB_ID_ExtIEs,
      &szProtExtnField_TgeteNB_ID_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szTgeteNB_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szTgeteNB_IDTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szTgeteNB_ID =
{
#ifdef CM_PASN_DBG
   " szTgeteNB_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTgeteNB_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTgeteNB_IDspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnSrceNB_ID_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnSrceNB_ID_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnSrceNB_ID_ExtIEsClsInfo =
{
   0,
   &sz_ExtnSrceNB_ID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSrceNB_ID_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnSrceNB_ID_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnSrceNB_ID_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnSrceNB_ID_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnSrceNB_ID_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnSrceNB_ID_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnSrceNB_ID_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_SrceNB_ID_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnSrceNB_ID_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SrceNB_ID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_SrceNB_ID_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_SrceNB_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_SrceNB_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_SrceNB_ID_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_SrceNB_ID_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_SrceNB_ID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_SrceNB_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SrceNB_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SrceNB_ID_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SrceNB_ID_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_SrceNB_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SrceNB_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SrceNB_ID_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SrceNB_ID_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szSrceNB_IDTkn[] =
{
   &szGlobal_ENB_ID,
   &szTAI,
   &szOptProtExtnCont_SrceNB_ID_ExtIEs,
      &szProtExtnField_SrceNB_ID_ExtIEs,
      &szConstTerm,
   &szConstTerm
};
CmPAsnSetSeqDef szSrceNB_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szSrceNB_IDTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szSrceNB_ID =
{
#ifdef CM_PASN_DBG
   " szSrceNB_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSrceNB_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSrceNB_IDspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnSONConfigTfr_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnSONConfigTfr_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnSONConfigTfr_ExtIEsClsInfo =
{
   0,
   &sz_ExtnSONConfigTfr_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSONConfigTfr_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnSONConfigTfr_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnSONConfigTfr_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnSONConfigTfr_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnSONConfigTfr_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnSONConfigTfr_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnSONConfigTfr_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_SONConfigTfr_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnSONConfigTfr_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SONConfigTfr_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_SONConfigTfr_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_SONConfigTfr_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_SONConfigTfr_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_SONConfigTfr_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_SONConfigTfr_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_SONConfigTfr_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_SONConfigTfr_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SONConfigTfr_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SONConfigTfr_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SONConfigTfr_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_SONConfigTfr_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SONConfigTfr_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SONConfigTfr_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SONConfigTfr_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szSONConfigTfrTkn[] =
{
   &szTgeteNB_ID,
   &szSrceNB_ID,
   &szSONInform,
   &szOptProtExtnCont_SONConfigTfr_ExtIEs,
      &szProtExtnField_SONConfigTfr_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szSONConfigTfrspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szSONConfigTfrTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szSONConfigTfr =
{
#ifdef CM_PASN_DBG
   " szSONConfigTfr ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztSONConfigTfr),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSONConfigTfrspec),
   NULLP
};
CmPAsnOctStrDef szSrc_ToTget_TprntContspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szSrc_ToTget_TprntCont =
{
#ifdef CM_PASN_DBG
   " szSrc_ToTget_TprntCont " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSrc_ToTget_TprntCont),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szSrc_ToTget_TprntContspec),
   NULLP
};
CmPAsnOctStrDef szSrcBSS_ToTgetBSS_TprntContspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szSrcBSS_ToTgetBSS_TprntCont =
{
#ifdef CM_PASN_DBG
   " szSrcBSS_ToTgetBSS_TprntCont " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSrcBSS_ToTgetBSS_TprntCont),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szSrcBSS_ToTgetBSS_TprntContspec),
   NULLP
};
/* Element ----- SRVCCOperationPossible ------- */
CmPAsnTknEnum szSRVCCOperationPossibleLst[2] =
{
   1,
   SztSRVCCOperationPossiblepossibleEnum
};
CmPAsnEnumDef szSRVCCOperationPossiblespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szSRVCCOperationPossibleLst,
   NULLP
};
CmPAsnElmDef szSRVCCOperationPossible =
{
#ifdef CM_PASN_DBG
   " szSRVCCOperationPossible ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztSRVCCOperationPossible),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSRVCCOperationPossiblespec),
   NULLP
};

/* Element ----- SRVCCHOIndication ------- */
CmPAsnTknEnum szSRVCCHOIndLst[3] =
{
   2,
   SztSRVCCHOIndpSandCSEnum,
   SztSRVCCHOIndcSonlyEnum
};
CmPAsnEnumDef szSRVCCHOIndspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szSRVCCHOIndLst,
   NULLP
};
CmPAsnElmDef szSRVCCHOInd =
{
#ifdef CM_PASN_DBG
   " szSRVCCHOInd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztSRVCCHOInd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSRVCCHOIndspec),
   NULLP
};

/* Element ----- SubscriberProfileIDforRFP ------- */
CmPAsnUIntDef szSubscriberProfileIDforRFPspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   1,
   256UL
};
CmPAsnElmDef szSubscriberProfileIDforRFP =
{
#ifdef CM_PASN_DBG
   " szSubscriberProfileIDforRFP ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSubscriberProfileIDforRFP),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSubscriberProfileIDforRFPspec),
   NULLP
};
CmPAsnElmDef szOptSubscriberProfileIDforRFP =
{
#ifdef CM_PASN_DBG
   " szSubscriberProfileIDforRFP ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSubscriberProfileIDforRFP),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSubscriberProfileIDforRFPspec),
   NULLP
};

CmPAsnSetSeqOfDef szUE_HistoryInformspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofCells,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szUE_HistoryInform =
{
#ifdef CM_PASN_DBG
   " szUE_HistoryInform ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztUE_HistoryInform),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szUE_HistoryInformspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsInfo =
{
   0,
   &sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szSrceNB_ToTgeteNB_TprntContTkn[] =
{
   &szRRC_Cont,
   &szOptE_RABInformLst,
      &szProtIE_Field_E_RABInformLstIEs,
      &szConstTerm,
   &szEUTRAN_CGI,
   &szOptSubscriberProfileIDforRFP,
   &szUE_HistoryInform,
      &szLastVisitedCell_Item,
      &szConstTerm,
   &szOptProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs,
      &szProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szSrceNB_ToTgeteNB_TprntContspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   3,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szSrceNB_ToTgeteNB_TprntContTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szSrceNB_ToTgeteNB_TprntCont =
{
#ifdef CM_PASN_DBG
   " szSrceNB_ToTgeteNB_TprntCont ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztSrceNB_ToTgeteNB_TprntCont),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSrceNB_ToTgeteNB_TprntContspec),
   NULLP
};
CmPAsnOctStrDef szSrcRNC_ToTgetRNC_TprntContspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szSrcRNC_ToTgetRNC_TprntCont =
{
#ifdef CM_PASN_DBG
   " szSrcRNC_ToTgetRNC_TprntCont " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSrcRNC_ToTgetRNC_TprntCont),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szSrcRNC_ToTgetRNC_TprntContspec),
   NULLP
};
CmPAsnSetSeqOfDef szSrvdPLMNsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofPLMNsPerMME,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szSrvdPLMNs =
{
#ifdef CM_PASN_DBG
   " szSrvdPLMNs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSrvdPLMNs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szSrvdPLMNsspec),
   NULLP
};
CmPAsnSetSeqOfDef szSrvdGroupIDsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofGroupIDs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szSrvdGroupIDs =
{
#ifdef CM_PASN_DBG
   " szSrvdGroupIDs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSrvdGroupIDs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szSrvdGroupIDsspec),
   NULLP
};
CmPAsnSetSeqOfDef szSrvdMMECsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofMMECs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szSrvdMMECs =
{
#ifdef CM_PASN_DBG
   " szSrvdMMECs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSrvdMMECs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szSrvdMMECsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnSrvdGUMMEIsItem_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnSrvdGUMMEIsItem_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnSrvdGUMMEIsItem_ExtIEsClsInfo =
{
   0,
   &sz_ExtnSrvdGUMMEIsItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSrvdGUMMEIsItem_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnSrvdGUMMEIsItem_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnSrvdGUMMEIsItem_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnSrvdGUMMEIsItem_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnSrvdGUMMEIsItem_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnSrvdGUMMEIsItem_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_SrvdGUMMEIsItem_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnSrvdGUMMEIsItem_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SrvdGUMMEIsItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_SrvdGUMMEIsItem_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_SrvdGUMMEIsItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_SrvdGUMMEIsItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_SrvdGUMMEIsItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_SrvdGUMMEIsItem_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_SrvdGUMMEIsItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_SrvdGUMMEIsItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SrvdGUMMEIsItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SrvdGUMMEIsItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_SrvdGUMMEIsItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SrvdGUMMEIsItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SrvdGUMMEIsItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szSrvdGUMMEIsItemTkn[] =
{
   &szSrvdPLMNs,
      &szTBCD_STRING,
      &szConstTerm,
   &szSrvdGroupIDs,
      &szMME_Group_ID,
      &szConstTerm,
   &szSrvdMMECs,
      &szMME_Code,
      &szConstTerm,
   &szOptProtExtnCont_SrvdGUMMEIsItem_ExtIEs,
      &szProtExtnField_SrvdGUMMEIsItem_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szSrvdGUMMEIsItemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szSrvdGUMMEIsItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szSrvdGUMMEIsItem =
{
#ifdef CM_PASN_DBG
   " szSrvdGUMMEIsItem ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztSrvdGUMMEIsItem),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSrvdGUMMEIsItemspec),
   NULLP
};
CmPAsnSetSeqOfDef szSrvdGUMMEIsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofRATs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szSrvdGUMMEIs =
{
#ifdef CM_PASN_DBG
   " szSrvdGUMMEIs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSrvdGUMMEIs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szSrvdGUMMEIsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnSuppTAs_Item_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnSuppTAs_Item_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnSuppTAs_Item_ExtIEsClsInfo =
{
   0,
   &sz_ExtnSuppTAs_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSuppTAs_Item_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnSuppTAs_Item_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnSuppTAs_Item_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnSuppTAs_Item_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnSuppTAs_Item_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnSuppTAs_Item_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnSuppTAs_Item_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_SuppTAs_Item_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnSuppTAs_Item_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SuppTAs_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_SuppTAs_Item_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_SuppTAs_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_SuppTAs_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_SuppTAs_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_SuppTAs_Item_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_SuppTAs_Item_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_SuppTAs_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SuppTAs_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SuppTAs_Item_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SuppTAs_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_SuppTAs_Item_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_SuppTAs_Item_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SuppTAs_Item_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_SuppTAs_Item_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szSuppTAs_ItemTkn[] =
{
   &szTAC,
   &szBPLMNs,
      &szTBCD_STRING,
      &szConstTerm,
   &szOptProtExtnCont_SuppTAs_Item_ExtIEs,
      &szProtExtnField_SuppTAs_Item_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szSuppTAs_Itemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szSuppTAs_ItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szSuppTAs_Item =
{
#ifdef CM_PASN_DBG
   " szSuppTAs_Item ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztSuppTAs_Item),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSuppTAs_Itemspec),
   NULLP
};
CmPAsnSetSeqOfDef szSuppTAsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofTACs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szSuppTAs =
{
#ifdef CM_PASN_DBG
   " szSuppTAs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSuppTAs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szSuppTAsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnS_TMSI_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnS_TMSI_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnS_TMSI_ExtIEsClsInfo =
{
   0,
   &sz_ExtnS_TMSI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnS_TMSI_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnS_TMSI_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnS_TMSI_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnS_TMSI_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnS_TMSI_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnS_TMSI_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnS_TMSI_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_S_TMSI_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnS_TMSI_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_S_TMSI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_S_TMSI_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_S_TMSI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_S_TMSI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_S_TMSI_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_S_TMSI_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_S_TMSI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_S_TMSI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_S_TMSI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_S_TMSI_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_S_TMSI_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_S_TMSI_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_S_TMSI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_S_TMSI_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_S_TMSI_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szS_TMSITkn[] =
{
   &szMME_Code,
   &szM_TMSI,
   &szOptProtExtnCont_S_TMSI_ExtIEs,
      &szProtExtnField_S_TMSI_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szS_TMSIspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szS_TMSITkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szS_TMSI =
{
#ifdef CM_PASN_DBG
   " szS_TMSI ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztS_TMSI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szS_TMSIspec),
   NULLP
};
CmPAsnSetSeqOfDef szTAILstforWarningspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofTAIforWarning,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szTAILstforWarning =
{
#ifdef CM_PASN_DBG
   " szTAILstforWarning ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTAILstforWarning),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szTAILstforWarningspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnTgetRNC_ID_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnTgetRNC_ID_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnTgetRNC_ID_ExtIEsClsInfo =
{
   0,
   &sz_ExtnTgetRNC_ID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTgetRNC_ID_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnTgetRNC_ID_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnTgetRNC_ID_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnTgetRNC_ID_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnTgetRNC_ID_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnTgetRNC_ID_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnTgetRNC_ID_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_TgetRNC_ID_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnTgetRNC_ID_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TgetRNC_ID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_TgetRNC_ID_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_TgetRNC_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_TgetRNC_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_TgetRNC_ID_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_TgetRNC_ID_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_TgetRNC_ID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_TgetRNC_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TgetRNC_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TgetRNC_ID_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TgetRNC_ID_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_TgetRNC_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TgetRNC_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TgetRNC_ID_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TgetRNC_ID_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szTgetRNC_IDTkn[] =
{
   &szLAI,
   &szOptRAC,
   &szRNC_ID,
   &szOptExtendedRNC_ID,
   &szOptProtExtnCont_TgetRNC_ID_ExtIEs,
      &szProtExtnField_TgetRNC_ID_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szTgetRNC_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   3,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szTgetRNC_IDTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szTgetRNC_ID =
{
#ifdef CM_PASN_DBG
   " szTgetRNC_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTgetRNC_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTgetRNC_IDspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szTgetIDTkn[] =
{
   &szTgeteNB_ID,
   &szTgetRNC_ID,
   &szCGI,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szTgetIDspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   3,
   0,
   &szTgetIDTkn[0]  /* Token List */
};
CmPAsnElmDef szTgetID =
{
#ifdef CM_PASN_DBG
   " szTgetID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTgetID),
   &flagSz3M,
   NULLP,
   (U8 *)(&szTgetIDspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsInfo =
{
   0,
   &sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szTgeteNB_ToSrceNB_TprntContTkn[] =
{
   &szRRC_Cont,
   &szOptProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs,
      &szProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szTgeteNB_ToSrceNB_TprntContspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szTgeteNB_ToSrceNB_TprntContTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szTgeteNB_ToSrceNB_TprntCont =
{
#ifdef CM_PASN_DBG
   " szTgeteNB_ToSrceNB_TprntCont ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTgeteNB_ToSrceNB_TprntCont),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTgeteNB_ToSrceNB_TprntContspec),
   NULLP
};
CmPAsnOctStrDef szTget_ToSrc_TprntContspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szTget_ToSrc_TprntCont =
{
#ifdef CM_PASN_DBG
   " szTget_ToSrc_TprntCont " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTget_ToSrc_TprntCont),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szTget_ToSrc_TprntContspec),
   NULLP
};
CmPAsnOctStrDef szTgetRNC_ToSrcRNC_TprntContspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szTgetRNC_ToSrcRNC_TprntCont =
{
#ifdef CM_PASN_DBG
   " szTgetRNC_ToSrcRNC_TprntCont " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTgetRNC_ToSrcRNC_TprntCont),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szTgetRNC_ToSrcRNC_TprntContspec),
   NULLP
};
CmPAsnOctStrDef szTgetBSS_ToSrcBSS_TprntContspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szTgetBSS_ToSrcBSS_TprntCont =
{
#ifdef CM_PASN_DBG
   " szTgetBSS_ToSrcBSS_TprntCont " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTgetBSS_ToSrcBSS_TprntCont),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szTgetBSS_ToSrcBSS_TprntContspec),
   NULLP
};
/* Element ----- TimeToWait ------- */
CmPAsnTknEnum szTimeToWaitLst[7] =
{
   6,
   SztTimeToWaitv1sEnum,
   SztTimeToWaitv2sEnum,
   SztTimeToWaitv5sEnum,
   SztTimeToWaitv10sEnum,
   SztTimeToWaitv20sEnum,
   SztTimeToWaitv60sEnum
};
CmPAsnEnumDef szTimeToWaitspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szTimeToWaitLst,
   NULLP
};
CmPAsnElmDef szTimeToWait =
{
#ifdef CM_PASN_DBG
   " szTimeToWait ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTimeToWait),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTimeToWaitspec),
   NULLP
};

CmPAsnOctStrDef szE_UTRAN_Trace_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   8,
   8
};
CmPAsnElmDef szE_UTRAN_Trace_ID =
{
#ifdef CM_PASN_DBG
   " szE_UTRAN_Trace_ID " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztE_UTRAN_Trace_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szE_UTRAN_Trace_IDspec),
   NULLP
};
/* Element ----- TraceDepth ------- */
CmPAsnTknEnum szTraceDepthLst[7] =
{
   6,
   SztTraceDepthminimumEnum,
   SztTraceDepthmediumEnum,
   SztTraceDepthmaximumEnum,
   SztTraceDepthminimumWithoutVendorSpecificExtnEnum,
   SztTraceDepthmediumWithoutVendorSpecificExtnEnum,
   SztTraceDepthmaximumWithoutVendorSpecificExtnEnum
};
CmPAsnEnumDef szTraceDepthspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szTraceDepthLst,
   NULLP
};
CmPAsnElmDef szTraceDepth =
{
#ifdef CM_PASN_DBG
   " szTraceDepth ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTraceDepth),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTraceDepthspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz_ExtnTraceActvn_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnTraceActvn_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnTraceActvn_ExtIEsClsInfo =
{
   0,
   &sz_ExtnTraceActvn_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTraceActvn_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnTraceActvn_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnTraceActvn_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnTraceActvn_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnTraceActvn_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnTraceActvn_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnTraceActvn_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_TraceActvn_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnTraceActvn_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TraceActvn_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_TraceActvn_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_TraceActvn_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_TraceActvn_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_TraceActvn_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_TraceActvn_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_TraceActvn_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_TraceActvn_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TraceActvn_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TraceActvn_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TraceActvn_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_TraceActvn_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TraceActvn_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TraceActvn_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TraceActvn_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szTraceActvnTkn[] =
{
   &szE_UTRAN_Trace_ID,
   &szIntfsToTrace,
   &szTraceDepth,
   &szTportLyrAddr,
   &szOptProtExtnCont_TraceActvn_ExtIEs,
      &szProtExtnField_TraceActvn_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szTraceActvnspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szTraceActvnTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szTraceActvn =
{
#ifdef CM_PASN_DBG
   " szTraceActvn ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTraceActvn),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTraceActvnspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnUEAgg_MaxBitrates_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnUEAgg_MaxBitrates_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnUEAgg_MaxBitrates_ExtIEsClsInfo =
{
   0,
   &sz_ExtnUEAgg_MaxBitrates_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnUEAgg_MaxBitrates_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnUEAgg_MaxBitrates_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnUEAgg_MaxBitrates_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnUEAgg_MaxBitrates_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnUEAgg_MaxBitrates_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnUEAgg_MaxBitrates_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_UEAgg_MaxBitrates_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnUEAgg_MaxBitrates_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_UEAgg_MaxBitrates_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_UEAgg_MaxBitrates_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_UEAgg_MaxBitrates_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_UEAgg_MaxBitrates_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_UEAgg_MaxBitrates_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_UEAgg_MaxBitrates_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_UEAgg_MaxBitrates_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_UEAgg_MaxBitrates_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_UEAgg_MaxBitrates_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_UEAgg_MaxBitrates_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_UEAgg_MaxBitrates_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_UEAgg_MaxBitrates_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_UEAgg_MaxBitrates_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUEAggMaxBitrateTkn[] =
{
   &szBitRate,
   &szBitRate,
   &szOptProtExtnCont_UEAgg_MaxBitrates_ExtIEs,
      &szProtExtnField_UEAgg_MaxBitrates_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szUEAggMaxBitratespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUEAggMaxBitrateTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUEAggMaxBitrate =
{
#ifdef CM_PASN_DBG
   " szUEAggMaxBitrate ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUEAggMaxBitrate),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUEAggMaxBitratespec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnUE_S1AP_ID_pair_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnUE_S1AP_ID_pair_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnUE_S1AP_ID_pair_ExtIEsClsInfo =
{
   0,
   &sz_ExtnUE_S1AP_ID_pair_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnUE_S1AP_ID_pair_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnUE_S1AP_ID_pair_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnUE_S1AP_ID_pair_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnUE_S1AP_ID_pair_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnUE_S1AP_ID_pair_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnUE_S1AP_ID_pair_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_UE_S1AP_ID_pair_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnUE_S1AP_ID_pair_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_UE_S1AP_ID_pair_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_UE_S1AP_ID_pair_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_UE_S1AP_ID_pair_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_UE_S1AP_ID_pair_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_UE_S1AP_ID_pair_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_UE_S1AP_ID_pair_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_UE_S1AP_ID_pair_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_UE_S1AP_ID_pair_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_UE_S1AP_ID_pair_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_UE_S1AP_ID_pair_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_UE_S1AP_ID_pair_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_UE_S1AP_ID_pair_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_UE_S1AP_ID_pair_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUE_S1AP_ID_pairTkn[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szOptProtExtnCont_UE_S1AP_ID_pair_ExtIEs,
      &szProtExtnField_UE_S1AP_ID_pair_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szUE_S1AP_ID_pairspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUE_S1AP_ID_pairTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUE_S1AP_ID_pair =
{
#ifdef CM_PASN_DBG
   " szUE_S1AP_ID_pair ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUE_S1AP_ID_pair),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUE_S1AP_ID_pairspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUE_S1AP_IDsTkn[] =
{
   &szUE_S1AP_ID_pair,
   &szMME_UE_S1AP_ID,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szUE_S1AP_IDsspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   2,
   0,
   &szUE_S1AP_IDsTkn[0]  /* Token List */
};
CmPAsnElmDef szUE_S1AP_IDs =
{
#ifdef CM_PASN_DBG
   " szUE_S1AP_IDs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUE_S1AP_IDs),
   &flagSz3M,
   NULLP,
   (U8 *)(&szUE_S1AP_IDsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnUE_assocLogS1_ConItemExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnUE_assocLogS1_ConItemExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnUE_assocLogS1_ConItemExtIEsClsInfo =
{
   0,
   &sz_ExtnUE_assocLogS1_ConItemExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnUE_assocLogS1_ConItemExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnUE_assocLogS1_ConItemExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnUE_assocLogS1_ConItemExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnUE_assocLogS1_ConItemExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnUE_assocLogS1_ConItemExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnUE_assocLogS1_ConItemExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnUE_assocLogS1_ConItemExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_UE_assocLogS1_ConItemExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnUE_assocLogS1_ConItemExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_UE_assocLogS1_ConItemExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_UE_assocLogS1_ConItemExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_UE_assocLogS1_ConItemExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_UE_assocLogS1_ConItemExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_UE_assocLogS1_ConItemExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_UE_assocLogS1_ConItemExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_UE_assocLogS1_ConItemExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_UE_assocLogS1_ConItemExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_UE_assocLogS1_ConItemExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_UE_assocLogS1_ConItemExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_UE_assocLogS1_ConItemExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_UE_assocLogS1_ConItemExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_UE_assocLogS1_ConItemExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_UE_assocLogS1_ConItemExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_UE_assocLogS1_ConItemExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUE_assocLogS1_ConItemTkn[] =
{
   &szOptMME_UE_S1AP_ID,
   &szOptENB_UE_S1AP_ID,
   &szOptProtExtnCont_UE_assocLogS1_ConItemExtIEs,
      &szProtExtnField_UE_assocLogS1_ConItemExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szUE_assocLogS1_ConItemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   3,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUE_assocLogS1_ConItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUE_assocLogS1_ConItem =
{
#ifdef CM_PASN_DBG
   " szUE_assocLogS1_ConItem ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUE_assocLogS1_ConItem),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUE_assocLogS1_ConItemspec),
   NULLP
};
CmPAsnBitStrDef szUEIdentityIdxValuespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTR,
#endif /* CM_PASN_DEBUG */
   10,
   10
};
CmPAsnElmDef szUEIdentityIdxValue =
{
#ifdef CM_PASN_DBG
   " szUEIdentityIdxValue ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztUEIdentityIdxValue),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szUEIdentityIdxValuespec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUEPagIDTkn[] =
{
   &szS_TMSI,
   &szIMSI,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szUEPagIDspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   2,
   0,
   &szUEPagIDTkn[0]  /* Token List */
};
CmPAsnElmDef szUEPagID =
{
#ifdef CM_PASN_DBG
   " szUEPagID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUEPagID),
   &flagSz3M,
   NULLP,
   (U8 *)(&szUEPagIDspec),
   NULLP
};
CmPAsnOctStrDef szUERadioCapbltyspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef szUERadioCapblty =
{
#ifdef CM_PASN_DBG
   " szUERadioCapblty " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztUERadioCapblty),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szUERadioCapbltyspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnUESecurCapabilities_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnUESecurCapabilities_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnUESecurCapabilities_ExtIEsClsInfo =
{
   0,
   &sz_ExtnUESecurCapabilities_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnUESecurCapabilities_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnUESecurCapabilities_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnUESecurCapabilities_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnUESecurCapabilities_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnUESecurCapabilities_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnUESecurCapabilities_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnUESecurCapabilities_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_UESecurCapabilities_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnUESecurCapabilities_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_UESecurCapabilities_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_UESecurCapabilities_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_UESecurCapabilities_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_UESecurCapabilities_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_UESecurCapabilities_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_UESecurCapabilities_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_UESecurCapabilities_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_UESecurCapabilities_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_UESecurCapabilities_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_UESecurCapabilities_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_UESecurCapabilities_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_UESecurCapabilities_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_UESecurCapabilities_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_UESecurCapabilities_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_UESecurCapabilities_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUESecurCapabilitiesTkn[] =
{
   &szEncryptionAlgorithms,
   &szIntegrityProtectionAlgorithms,
   &szOptProtExtnCont_UESecurCapabilities_ExtIEs,
      &szProtExtnField_UESecurCapabilities_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szUESecurCapabilitiesspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUESecurCapabilitiesTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUESecurCapabilities =
{
#ifdef CM_PASN_DBG
   " szUESecurCapabilities ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUESecurCapabilities),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUESecurCapabilitiesspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szWarningAreaLstTkn[] =
{
   &szECGILst,
      &szEUTRAN_CGI,
      &szConstTerm,
   &szTAILstforWarning,
      &szTAI,
      &szConstTerm,
   &szEmergencyAreaIDLst,
      &szEmergencyAreaID,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szWarningAreaLstspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   3,
   0,
   &szWarningAreaLstTkn[0]  /* Token List */
};
CmPAsnElmDef szWarningAreaLst =
{
#ifdef CM_PASN_DBG
   " szWarningAreaLst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztWarningAreaLst),
   &flagSz3M,
   NULLP,
   (U8 *)(&szWarningAreaLstspec),
   NULLP
};
CmPAsnOctStrDef szWarningTypspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTR,
#endif /* CM_PASN_DEBUG */
   2,
   2
};
CmPAsnElmDef szWarningTyp =
{
#ifdef CM_PASN_DBG
   " szWarningTyp " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztWarningTyp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szWarningTypspec),
   NULLP
};
CmPAsnOctStrDef szWarningSecurInfospec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   50,
   50
};
CmPAsnElmDef szWarningSecurInfo =
{
#ifdef CM_PASN_DBG
   " szWarningSecurInfo " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztWarningSecurInfo),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szWarningSecurInfospec),
   NULLP
};
CmPAsnOctStrDef szWarningMsgContentsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   1,
   9600
};
CmPAsnElmDef szWarningMsgContents =
{
#ifdef CM_PASN_DBG
   " szWarningMsgContents " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztWarningMsgContents),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szWarningMsgContentsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueHovrReqdIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szHovrTyp,
   &szCause,
   &szTgetID,
   &szDirect_Fwding_Path_Avlblty,
   &szSRVCCHOInd,
   &szSrc_ToTget_TprntCont,
   &szSrc_ToTget_TprntCont,
   &szMSClassmark2,
   &szMSClassmark3
};
PUBLIC U32 sz_ValueHovrReqdIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_HovrTyp,
   Sztid_Cause,
   Sztid_TgetID,
   Sztid_Direct_Fwding_Path_Avlblty,
   Sztid_SRVCCHOInd,
   Sztid_Src_ToTget_TprntCont,
   Sztid_Src_ToTget_TprntCont_Secondary,
   Sztid_MSClassmark2,
   Sztid_MSClassmark3
};
SzMsgConInf szHovrReqdIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_HovrTyp, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_TgetID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_Direct_Fwding_Path_Avlblty, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_SRVCCHOInd, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_Src_ToTget_TprntCont, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_Src_ToTget_TprntCont_Secondary, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_MSClassmark2, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_MSClassmark3, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   11,
   6
}; 
PUBLIC CmPAsnClassInfo sz_ValueHovrReqdIEsClsInfo =
{
   11,
   &sz_ValueHovrReqdIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrReqdIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueHovrReqdIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueHovrReqdIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueHovrReqdIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueHovrReqdIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueHovrReqdIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueHovrReqdIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_HovrReqdIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueHovrReqdIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrReqdIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_HovrReqdIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_HovrReqdIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_HovrReqdIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_HovrReqdIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_HovrReqdIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_HovrReqdIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_HovrReqdIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_HovrReqdIEs *protIe = NULLP;
   SztProtIE_Field_HovrReqdIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_HovrReqdIEsValidate);
   
   protIe = (SztProtIE_Cont_HovrReqdIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_HovrReqdIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szHovrReqdIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrReqdIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_HovrReqdIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_HovrReqdIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_HovrReqdIEs),
   &flagSz3M,
   szProtIE_Cont_HovrReqdIEsValidate,
   (U8 *) (&szProtIE_Cont_HovrReqdIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szHovrReqdTkn[] =
{
   &szProtIE_Cont_HovrReqdIEs,
      &szProtIE_Field_HovrReqdIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szHovrReqdspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szHovrReqdTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szHovrReqd =
{
#ifdef CM_PASN_DBG
   " szHovrReqd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztHovrReqd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szHovrReqdspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABDataFwdingItem_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABDataFwdingItem_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABDataFwdingItem_ExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABDataFwdingItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABDataFwdingItem_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABDataFwdingItem_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABDataFwdingItem_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABDataFwdingItem_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABDataFwdingItem_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABDataFwdingItem_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABDataFwdingItem_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABDataFwdingItem_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABDataFwdingItem_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABDataFwdingItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABDataFwdingItem_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABDataFwdingItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABDataFwdingItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABDataFwdingItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABDataFwdingItem_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABDataFwdingItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABDataFwdingItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABDataFwdingItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABDataFwdingItem_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABDataFwdingItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABDataFwdingItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABDataFwdingItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABDataFwdingItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABDataFwdingItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABDataFwdingItemTkn[] =
{
   &szE_RAB_ID,
   &szOptTportLyrAddr,
   &szOptGTP_TEID,
   &szOptTportLyrAddr,
   &szOptGTP_TEID,
   &szOptProtExtnCont_E_RABDataFwdingItem_ExtIEs,
      &szProtExtnField_E_RABDataFwdingItem_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABDataFwdingItemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   5,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABDataFwdingItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABDataFwdingItem =
{
#ifdef CM_PASN_DBG
   " szE_RABDataFwdingItem ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABDataFwdingItem),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABDataFwdingItemspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABDataFwdingItemIEsClsInst[] =
{
   &szE_RABDataFwdingItem
};
PUBLIC U32 sz_ValueE_RABDataFwdingItemIEsClsInstId[] =
{
   Sztid_E_RABDataFwdingItem
};
SzMsgConInf szE_RABDataFwdingItemIEsConInf =
{
   {
      { Sztid_E_RABDataFwdingItem, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABDataFwdingItemIEsClsInfo =
{
   1,
   &sz_ValueE_RABDataFwdingItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABDataFwdingItemIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABDataFwdingItemIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABDataFwdingItemIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABDataFwdingItemIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABDataFwdingItemIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABDataFwdingItemIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABDataFwdingItemIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABDataFwdingItemIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABDataFwdingItemIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABDataFwdingItemIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABDataFwdingItemIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABDataFwdingItemIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABDataFwdingItemIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABDataFwdingItemIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABDataFwdingItemIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABDataFwdingItemIEs szProtIE_Field_E_RABDataFwdingItemIEs
CmPAsnSetSeqOfDef szProtIE_ContLst_E_RABDataFwdingItemIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_ContLst_E_RABDataFwdingItemIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_ContLst_E_RABDataFwdingItemIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_ContLst_E_RABDataFwdingItemIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtIE_ContLst_E_RABDataFwdingItemIEsspec),
   NULLP
};
#define szE_RAB_IE_ContLst_E_RABDataFwdingItemIEs szProtIE_ContLst_E_RABDataFwdingItemIEs
#define szE_RABSubjtoDataFwdingLst szE_RAB_IE_ContLst_E_RABDataFwdingItemIEs
PUBLIC CmPAsnElmDef *sz_ValueHovrCmmdIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szHovrTyp,
   &szNASSecurParamsfromE_UTRAN,
   &szProtIE_ContLst_E_RABDataFwdingItemIEs,
      &szProtIE_SingleCont_E_RABDataFwdingItemIEs,
      &szConstTerm,
   &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      &szConstTerm,
   &szTget_ToSrc_TprntCont,
   &szTget_ToSrc_TprntCont,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueHovrCmmdIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_HovrTyp,
   Sztid_NASSecurParamsfromE_UTRAN,
   Sztid_E_RABSubjtoDataFwdingLst,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_E_RABtoRlsLstHOCmd,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_Tget_ToSrc_TprntCont,
   Sztid_Tget_ToSrc_TprntCont_Secondary,
   Sztid_CriticalityDiag
};
SzMsgConInf szHovrCmmdIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_HovrTyp, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_NASSecurParamsfromE_UTRAN, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_E_RABSubjtoDataFwdingLst, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_E_RABtoRlsLstHOCmd, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_Tget_ToSrc_TprntCont, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_Tget_ToSrc_TprntCont_Secondary, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   9,
   4
}; 
PUBLIC CmPAsnClassInfo sz_ValueHovrCmmdIEsClsInfo =
{
   13,
   &sz_ValueHovrCmmdIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrCmmdIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueHovrCmmdIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueHovrCmmdIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueHovrCmmdIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueHovrCmmdIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueHovrCmmdIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueHovrCmmdIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_HovrCmmdIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueHovrCmmdIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrCmmdIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_HovrCmmdIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_HovrCmmdIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_HovrCmmdIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_HovrCmmdIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_HovrCmmdIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_HovrCmmdIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_HovrCmmdIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_HovrCmmdIEs *protIe = NULLP;
   SztProtIE_Field_HovrCmmdIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_HovrCmmdIEsValidate);
   
   protIe = (SztProtIE_Cont_HovrCmmdIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_HovrCmmdIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szHovrCmmdIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrCmmdIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_HovrCmmdIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_HovrCmmdIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_HovrCmmdIEs),
   &flagSz3M,
   szProtIE_Cont_HovrCmmdIEsValidate,
   (U8 *) (&szProtIE_Cont_HovrCmmdIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szHovrCmmdTkn[] =
{
   &szProtIE_Cont_HovrCmmdIEs,
      &szProtIE_Field_HovrCmmdIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szHovrCmmdspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szHovrCmmdTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szHovrCmmd =
{
#ifdef CM_PASN_DBG
   " szHovrCmmd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztHovrCmmd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szHovrCmmdspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueHovrPrepFailIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szCause,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueHovrPrepFailIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_Cause,
   Sztid_CriticalityDiag
};
SzMsgConInf szHovrPrepFailIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   4,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueHovrPrepFailIEsClsInfo =
{
   4,
   &sz_ValueHovrPrepFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrPrepFailIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueHovrPrepFailIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueHovrPrepFailIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueHovrPrepFailIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueHovrPrepFailIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueHovrPrepFailIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueHovrPrepFailIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_HovrPrepFailIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueHovrPrepFailIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrPrepFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_HovrPrepFailIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_HovrPrepFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_HovrPrepFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_HovrPrepFailIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_HovrPrepFailIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_HovrPrepFailIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_HovrPrepFailIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_HovrPrepFailIEs *protIe = NULLP;
   SztProtIE_Field_HovrPrepFailIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_HovrPrepFailIEsValidate);
   
   protIe = (SztProtIE_Cont_HovrPrepFailIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_HovrPrepFailIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szHovrPrepFailIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrPrepFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_HovrPrepFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_HovrPrepFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_HovrPrepFailIEs),
   &flagSz3M,
   szProtIE_Cont_HovrPrepFailIEsValidate,
   (U8 *) (&szProtIE_Cont_HovrPrepFailIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szHovrPrepFailTkn[] =
{
   &szProtIE_Cont_HovrPrepFailIEs,
      &szProtIE_Field_HovrPrepFailIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szHovrPrepFailspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szHovrPrepFailTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szHovrPrepFail =
{
#ifdef CM_PASN_DBG
   " szHovrPrepFail ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztHovrPrepFail),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szHovrPrepFailspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABToBeSetupItemHOReq_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABToBeSetupItemHOReq_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABToBeSetupItemHOReq_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABToBeSetupItemHOReq_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABToBeSetupItemHOReqTkn[] =
{
   &szE_RAB_ID,
   &szTportLyrAddr,
   &szGTP_TEID,
   &szE_RABLvlQoSParams,
   &szOptProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs,
      &szProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABToBeSetupItemHOReqspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABToBeSetupItemHOReqTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABToBeSetupItemHOReq =
{
#ifdef CM_PASN_DBG
   " szE_RABToBeSetupItemHOReq ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABToBeSetupItemHOReq),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABToBeSetupItemHOReqspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABToBeSetupItemHOReqIEsClsInst[] =
{
   &szE_RABToBeSetupItemHOReq
};
PUBLIC U32 sz_ValueE_RABToBeSetupItemHOReqIEsClsInstId[] =
{
   Sztid_E_RABToBeSetupItemHOReq
};
SzMsgConInf szE_RABToBeSetupItemHOReqIEsConInf =
{
   {
      { Sztid_E_RABToBeSetupItemHOReq, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABToBeSetupItemHOReqIEsClsInfo =
{
   1,
   &sz_ValueE_RABToBeSetupItemHOReqIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABToBeSetupItemHOReqIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABToBeSetupItemHOReqIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABToBeSetupItemHOReqIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABToBeSetupItemHOReqIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABToBeSetupItemHOReqIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABToBeSetupItemHOReqIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABToBeSetupItemHOReqIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABToBeSetupItemHOReqIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABToBeSetupItemHOReqIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABToBeSetupItemHOReqIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABToBeSetupItemHOReqIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABToBeSetupItemHOReqIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABToBeSetupItemHOReqIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABToBeSetupItemHOReqIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABToBeSetupItemHOReqIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs szProtIE_Field_E_RABToBeSetupItemHOReqIEs
CmPAsnSetSeqOfDef szProtIE_ContLst_E_RABToBeSetupItemHOReqIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_ContLst_E_RABToBeSetupItemHOReqIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_ContLst_E_RABToBeSetupItemHOReqIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtIE_ContLst_E_RABToBeSetupItemHOReqIEsspec),
   NULLP
};
#define szE_RAB_IE_ContLst_E_RABToBeSetupItemHOReqIEs szProtIE_ContLst_E_RABToBeSetupItemHOReqIEs
#define szE_RABToBeSetupLstHOReq szE_RAB_IE_ContLst_E_RABToBeSetupItemHOReqIEs
PUBLIC CmPAsnElmDef *sz_ValueHovrRqstIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szHovrTyp,
   &szCause,
   &szUEAggMaxBitrate,
   &szProtIE_ContLst_E_RABToBeSetupItemHOReqIEs,
      &szProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs,
      &szConstTerm,
   &szSrc_ToTget_TprntCont,
   &szUESecurCapabilities,
   &szHovrRestrnLst,
   &szTraceActvn,
   &szRqstTyp,
   &szSRVCCOperationPossible,
   &szSecurCntxt,
   &szNASSecurParamstoE_UTRAN
};
PUBLIC U32 sz_ValueHovrRqstIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_HovrTyp,
   Sztid_Cause,
   Sztid_uEaggregateMaxBitrate,
   Sztid_E_RABToBeSetupLstHOReq,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_Src_ToTget_TprntCont,
   Sztid_UESecurCapabilities,
   Sztid_HovrRestrnLst,
   Sztid_TraceActvn,
   Sztid_RqstTyp,
   Sztid_SRVCCOperationPossible,
   Sztid_SecurCntxt,
   Sztid_NASSecurParamstoE_UTRAN
};
SzMsgConInf szHovrRqstIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_HovrTyp, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_uEaggregateMaxBitrate, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_E_RABToBeSetupLstHOReq, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_Src_ToTget_TprntCont, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_UESecurCapabilities, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_HovrRestrnLst, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_TraceActvn, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_RqstTyp, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_SRVCCOperationPossible, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_SecurCntxt, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_NASSecurParamstoE_UTRAN, SZ_CRIT_REJECT, CM_PASN_ELM_OPT }
   },
   13,
   8
}; 
PUBLIC CmPAsnClassInfo sz_ValueHovrRqstIEsClsInfo =
{
   15,
   &sz_ValueHovrRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrRqstIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueHovrRqstIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueHovrRqstIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueHovrRqstIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueHovrRqstIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueHovrRqstIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueHovrRqstIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_HovrRqstIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueHovrRqstIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_HovrRqstIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_HovrRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_HovrRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_HovrRqstIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_HovrRqstIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_HovrRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_HovrRqstIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_HovrRqstIEs *protIe = NULLP;
   SztProtIE_Field_HovrRqstIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_HovrRqstIEsValidate);
   
   protIe = (SztProtIE_Cont_HovrRqstIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_HovrRqstIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szHovrRqstIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_HovrRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_HovrRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_HovrRqstIEs),
   &flagSz3M,
   szProtIE_Cont_HovrRqstIEsValidate,
   (U8 *) (&szProtIE_Cont_HovrRqstIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szHovrRqstTkn[] =
{
   &szProtIE_Cont_HovrRqstIEs,
      &szProtIE_Field_HovrRqstIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szHovrRqstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szHovrRqstTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szHovrRqst =
{
#ifdef CM_PASN_DBG
   " szHovrRqst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztHovrRqst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szHovrRqstspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABAdmtdItem_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABAdmtdItem_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABAdmtdItem_ExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABAdmtdItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABAdmtdItem_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABAdmtdItem_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABAdmtdItem_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABAdmtdItem_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABAdmtdItem_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABAdmtdItem_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABAdmtdItem_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABAdmtdItem_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABAdmtdItem_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABAdmtdItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABAdmtdItem_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABAdmtdItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABAdmtdItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABAdmtdItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABAdmtdItem_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABAdmtdItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABAdmtdItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABAdmtdItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABAdmtdItem_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABAdmtdItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABAdmtdItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABAdmtdItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABAdmtdItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABAdmtdItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABAdmtdItemTkn[] =
{
   &szE_RAB_ID,
   &szTportLyrAddr,
   &szGTP_TEID,
   &szOptTportLyrAddr,
   &szOptGTP_TEID,
   &szOptTportLyrAddr,
   &szOptGTP_TEID,
   &szOptProtExtnCont_E_RABAdmtdItem_ExtIEs,
      &szProtExtnField_E_RABAdmtdItem_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABAdmtdItemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   5,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABAdmtdItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABAdmtdItem =
{
#ifdef CM_PASN_DBG
   " szE_RABAdmtdItem ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABAdmtdItem),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABAdmtdItemspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABAdmtdItemIEsClsInst[] =
{
   &szE_RABAdmtdItem
};
PUBLIC U32 sz_ValueE_RABAdmtdItemIEsClsInstId[] =
{
   Sztid_E_RABAdmtdItem
};
SzMsgConInf szE_RABAdmtdItemIEsConInf =
{
   {
      { Sztid_E_RABAdmtdItem, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABAdmtdItemIEsClsInfo =
{
   1,
   &sz_ValueE_RABAdmtdItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABAdmtdItemIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABAdmtdItemIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABAdmtdItemIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABAdmtdItemIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABAdmtdItemIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABAdmtdItemIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABAdmtdItemIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABAdmtdItemIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABAdmtdItemIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABAdmtdItemIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABAdmtdItemIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABAdmtdItemIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABAdmtdItemIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABAdmtdItemIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABAdmtdItemIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABAdmtdItemIEs szProtIE_Field_E_RABAdmtdItemIEs
CmPAsnSetSeqOfDef szProtIE_ContLst_E_RABAdmtdItemIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_ContLst_E_RABAdmtdItemIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_ContLst_E_RABAdmtdItemIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_ContLst_E_RABAdmtdItemIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtIE_ContLst_E_RABAdmtdItemIEsspec),
   NULLP
};
#define szE_RAB_IE_ContLst_E_RABAdmtdItemIEs szProtIE_ContLst_E_RABAdmtdItemIEs
#define szE_RABAdmtdLst szE_RAB_IE_ContLst_E_RABAdmtdItemIEs
PUBLIC CmPAsnElmDef *sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABFailedToSetupItemHOReqAckTkn[] =
{
   &szE_RAB_ID,
   &szCause,
   &szOptProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs,
      &szProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABFailedToSetupItemHOReqAckspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABFailedToSetupItemHOReqAckTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABFailedToSetupItemHOReqAck =
{
#ifdef CM_PASN_DBG
   " szE_RABFailedToSetupItemHOReqAck ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABFailedToSetupItemHOReqAck),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABFailedToSetupItemHOReqAckspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsInst[] =
{
   &szE_RABFailedToSetupItemHOReqAck
};
PUBLIC U32 sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsInstId[] =
{
   Sztid_E_RABFailedtoSetupItemHOReqAck
};
SzMsgConInf szE_RABFailedtoSetupItemHOReqAckIEsConInf =
{
   {
      { Sztid_E_RABFailedtoSetupItemHOReqAck, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsInfo =
{
   1,
   &sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABFailedtoSetupItemHOReqAckIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABFailedtoSetupItemHOReqAckIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABFailedtoSetupItemHOReqAckIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABFailedtoSetupItemHOReqAckIEs szProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs
CmPAsnSetSeqOfDef szProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEsspec),
   NULLP
};
#define szE_RAB_IE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs szProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs
#define szE_RABFailedtoSetupLstHOReqAck szE_RAB_IE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs
PUBLIC CmPAsnElmDef *sz_ValueHovrRqstAckgIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szProtIE_ContLst_E_RABAdmtdItemIEs,
      &szProtIE_SingleCont_E_RABAdmtdItemIEs,
      &szConstTerm,
   &szProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs,
      &szProtIE_SingleCont_E_RABFailedtoSetupItemHOReqAckIEs,
      &szConstTerm,
   &szTget_ToSrc_TprntCont,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueHovrRqstAckgIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_E_RABAdmtdLst,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_E_RABFailedToSetupLstHOReqAck,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_Tget_ToSrc_TprntCont,
   Sztid_CriticalityDiag
};
SzMsgConInf szHovrRqstAckgIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_E_RABAdmtdLst, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_E_RABFailedToSetupLstHOReqAck, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_Tget_ToSrc_TprntCont, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   6,
   4
}; 
PUBLIC CmPAsnClassInfo sz_ValueHovrRqstAckgIEsClsInfo =
{
   10,
   &sz_ValueHovrRqstAckgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrRqstAckgIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueHovrRqstAckgIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueHovrRqstAckgIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueHovrRqstAckgIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueHovrRqstAckgIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueHovrRqstAckgIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueHovrRqstAckgIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_HovrRqstAckgIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueHovrRqstAckgIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrRqstAckgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_HovrRqstAckgIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_HovrRqstAckgIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_HovrRqstAckgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_HovrRqstAckgIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_HovrRqstAckgIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_HovrRqstAckgIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_HovrRqstAckgIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_HovrRqstAckgIEs *protIe = NULLP;
   SztProtIE_Field_HovrRqstAckgIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_HovrRqstAckgIEsValidate);
   
   protIe = (SztProtIE_Cont_HovrRqstAckgIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_HovrRqstAckgIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szHovrRqstAckgIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrRqstAckgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_HovrRqstAckgIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_HovrRqstAckgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_HovrRqstAckgIEs),
   &flagSz3M,
   szProtIE_Cont_HovrRqstAckgIEsValidate,
   (U8 *) (&szProtIE_Cont_HovrRqstAckgIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szHovrRqstAckgTkn[] =
{
   &szProtIE_Cont_HovrRqstAckgIEs,
      &szProtIE_Field_HovrRqstAckgIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szHovrRqstAckgspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szHovrRqstAckgTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szHovrRqstAckg =
{
#ifdef CM_PASN_DBG
   " szHovrRqstAckg ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztHovrRqstAckg),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szHovrRqstAckgspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueHovrFailIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szCause,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueHovrFailIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_Cause,
   Sztid_CriticalityDiag
};
SzMsgConInf szHovrFailIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   3,
   2
}; 
PUBLIC CmPAsnClassInfo sz_ValueHovrFailIEsClsInfo =
{
   3,
   &sz_ValueHovrFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrFailIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueHovrFailIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueHovrFailIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueHovrFailIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueHovrFailIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueHovrFailIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueHovrFailIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_HovrFailIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueHovrFailIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_HovrFailIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_HovrFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_HovrFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_HovrFailIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_HovrFailIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_HovrFailIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_HovrFailIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_HovrFailIEs *protIe = NULLP;
   SztProtIE_Field_HovrFailIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_HovrFailIEsValidate);
   
   protIe = (SztProtIE_Cont_HovrFailIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_HovrFailIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szHovrFailIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_HovrFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_HovrFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_HovrFailIEs),
   &flagSz3M,
   szProtIE_Cont_HovrFailIEsValidate,
   (U8 *) (&szProtIE_Cont_HovrFailIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szHovrFailTkn[] =
{
   &szProtIE_Cont_HovrFailIEs,
      &szProtIE_Field_HovrFailIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szHovrFailspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szHovrFailTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szHovrFail =
{
#ifdef CM_PASN_DBG
   " szHovrFail ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztHovrFail),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szHovrFailspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueHovrNtfyIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szEUTRAN_CGI,
   &szTAI
};
PUBLIC U32 sz_ValueHovrNtfyIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_EUTRAN_CGI,
   Sztid_TAI
};
SzMsgConInf szHovrNtfyIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_EUTRAN_CGI, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_TAI, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   4,
   4
}; 
PUBLIC CmPAsnClassInfo sz_ValueHovrNtfyIEsClsInfo =
{
   4,
   &sz_ValueHovrNtfyIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrNtfyIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueHovrNtfyIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueHovrNtfyIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueHovrNtfyIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueHovrNtfyIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueHovrNtfyIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueHovrNtfyIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_HovrNtfyIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueHovrNtfyIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrNtfyIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_HovrNtfyIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_HovrNtfyIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_HovrNtfyIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_HovrNtfyIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_HovrNtfyIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_HovrNtfyIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_HovrNtfyIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_HovrNtfyIEs *protIe = NULLP;
   SztProtIE_Field_HovrNtfyIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_HovrNtfyIEsValidate);
   
   protIe = (SztProtIE_Cont_HovrNtfyIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_HovrNtfyIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szHovrNtfyIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrNtfyIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_HovrNtfyIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_HovrNtfyIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_HovrNtfyIEs),
   &flagSz3M,
   szProtIE_Cont_HovrNtfyIEsValidate,
   (U8 *) (&szProtIE_Cont_HovrNtfyIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szHovrNtfyTkn[] =
{
   &szProtIE_Cont_HovrNtfyIEs,
      &szProtIE_Field_HovrNtfyIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szHovrNtfyspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szHovrNtfyTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szHovrNtfy =
{
#ifdef CM_PASN_DBG
   " szHovrNtfy ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztHovrNtfy),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szHovrNtfyspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABToBeSwedDLItem_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABToBeSwedDLItem_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABToBeSwedDLItem_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABToBeSwedDLItem_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABToBeSwedDLItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABToBeSwedDLItem_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABToBeSwedDLItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABToBeSwedDLItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABToBeSwedDLItem_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABToBeSwedDLItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABToBeSwedDLItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABToBeSwedDLItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABToBeSwedDLItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABToBeSwedDLItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABToBeSwedDLItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABToBeSwedDLItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABToBeSwedDLItemTkn[] =
{
   &szE_RAB_ID,
   &szTportLyrAddr,
   &szGTP_TEID,
   &szOptProtExtnCont_E_RABToBeSwedDLItem_ExtIEs,
      &szProtExtnField_E_RABToBeSwedDLItem_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABToBeSwedDLItemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABToBeSwedDLItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABToBeSwedDLItem =
{
#ifdef CM_PASN_DBG
   " szE_RABToBeSwedDLItem ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABToBeSwedDLItem),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABToBeSwedDLItemspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABToBeSwedDLItemIEsClsInst[] =
{
   &szE_RABToBeSwedDLItem
};
PUBLIC U32 sz_ValueE_RABToBeSwedDLItemIEsClsInstId[] =
{
   Sztid_E_RABToBeSwedDLItem
};
SzMsgConInf szE_RABToBeSwedDLItemIEsConInf =
{
   {
      { Sztid_E_RABToBeSwedDLItem, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABToBeSwedDLItemIEsClsInfo =
{
   1,
   &sz_ValueE_RABToBeSwedDLItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABToBeSwedDLItemIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABToBeSwedDLItemIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABToBeSwedDLItemIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABToBeSwedDLItemIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABToBeSwedDLItemIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABToBeSwedDLItemIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABToBeSwedDLItemIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABToBeSwedDLItemIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABToBeSwedDLItemIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABToBeSwedDLItemIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABToBeSwedDLItemIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABToBeSwedDLItemIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABToBeSwedDLItemIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABToBeSwedDLItemIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABToBeSwedDLItemIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABToBeSwedDLItemIEs szProtIE_Field_E_RABToBeSwedDLItemIEs
CmPAsnSetSeqOfDef szProtIE_ContLst_E_RABToBeSwedDLItemIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_ContLst_E_RABToBeSwedDLItemIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_ContLst_E_RABToBeSwedDLItemIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_ContLst_E_RABToBeSwedDLItemIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtIE_ContLst_E_RABToBeSwedDLItemIEsspec),
   NULLP
};
#define szE_RAB_IE_ContLst_E_RABToBeSwedDLItemIEs szProtIE_ContLst_E_RABToBeSwedDLItemIEs
#define szE_RABToBeSwedDLLst szE_RAB_IE_ContLst_E_RABToBeSwedDLItemIEs
PUBLIC CmPAsnElmDef *sz_ValuePathSwRqstIEsClsInst[] =
{
   &szENB_UE_S1AP_ID,
   &szProtIE_ContLst_E_RABToBeSwedDLItemIEs,
      &szProtIE_SingleCont_E_RABToBeSwedDLItemIEs,
      &szConstTerm,
   &szMME_UE_S1AP_ID,
   &szEUTRAN_CGI,
   &szTAI,
   &szUESecurCapabilities
};
PUBLIC U32 sz_ValuePathSwRqstIEsClsInstId[] =
{
   Sztid_eNB_UE_S1AP_ID,
   Sztid_E_RABToBeSwedDLLst,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_SrcMME_UE_S1AP_ID,
   Sztid_EUTRAN_CGI,
   Sztid_TAI,
   Sztid_UESecurCapabilities
};
SzMsgConInf szPathSwRqstIEsConInf =
{
   {
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_E_RABToBeSwedDLLst, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_SrcMME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_EUTRAN_CGI, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_TAI, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_UESecurCapabilities, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   6,
   6
}; 
PUBLIC CmPAsnClassInfo sz_ValuePathSwRqstIEsClsInfo =
{
   8,
   &sz_ValuePathSwRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValuePathSwRqstIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValuePathSwRqstIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValuePathSwRqstIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValuePathSwRqstIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValuePathSwRqstIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValuePathSwRqstIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValuePathSwRqstIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_PathSwRqstIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValuePathSwRqstIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_PathSwRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_PathSwRqstIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_PathSwRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_PathSwRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_PathSwRqstIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_PathSwRqstIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_PathSwRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_PathSwRqstIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_PathSwRqstIEs *protIe = NULLP;
   SztProtIE_Field_PathSwRqstIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_PathSwRqstIEsValidate);
   
   protIe = (SztProtIE_Cont_PathSwRqstIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_PathSwRqstIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szPathSwRqstIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_PathSwRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_PathSwRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_PathSwRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_PathSwRqstIEs),
   &flagSz3M,
   szProtIE_Cont_PathSwRqstIEsValidate,
   (U8 *) (&szProtIE_Cont_PathSwRqstIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szPathSwRqstTkn[] =
{
   &szProtIE_Cont_PathSwRqstIEs,
      &szProtIE_Field_PathSwRqstIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szPathSwRqstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szPathSwRqstTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szPathSwRqst =
{
#ifdef CM_PASN_DBG
   " szPathSwRqst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztPathSwRqst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szPathSwRqstspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABToBeSwedULItem_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABToBeSwedULItem_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABToBeSwedULItem_ExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABToBeSwedULItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABToBeSwedULItem_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABToBeSwedULItem_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABToBeSwedULItem_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABToBeSwedULItem_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABToBeSwedULItem_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABToBeSwedULItem_ExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABToBeSwedULItem_ExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABToBeSwedULItem_ExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABToBeSwedULItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABToBeSwedULItem_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABToBeSwedULItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABToBeSwedULItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABToBeSwedULItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABToBeSwedULItem_ExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABToBeSwedULItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABToBeSwedULItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABToBeSwedULItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABToBeSwedULItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABToBeSwedULItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABToBeSwedULItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABToBeSwedULItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABToBeSwedULItemTkn[] =
{
   &szE_RAB_ID,
   &szTportLyrAddr,
   &szGTP_TEID,
   &szOptProtExtnCont_E_RABToBeSwedULItem_ExtIEs,
      &szProtExtnField_E_RABToBeSwedULItem_ExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABToBeSwedULItemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABToBeSwedULItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABToBeSwedULItem =
{
#ifdef CM_PASN_DBG
   " szE_RABToBeSwedULItem ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABToBeSwedULItem),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABToBeSwedULItemspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABToBeSwedULItemIEsClsInst[] =
{
   &szE_RABToBeSwedULItem
};
PUBLIC U32 sz_ValueE_RABToBeSwedULItemIEsClsInstId[] =
{
   Sztid_E_RABToBeSwedULItem
};
SzMsgConInf szE_RABToBeSwedULItemIEsConInf =
{
   {
      { Sztid_E_RABToBeSwedULItem, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABToBeSwedULItemIEsClsInfo =
{
   1,
   &sz_ValueE_RABToBeSwedULItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABToBeSwedULItemIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABToBeSwedULItemIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABToBeSwedULItemIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABToBeSwedULItemIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABToBeSwedULItemIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABToBeSwedULItemIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABToBeSwedULItemIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABToBeSwedULItemIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABToBeSwedULItemIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABToBeSwedULItemIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABToBeSwedULItemIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABToBeSwedULItemIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABToBeSwedULItemIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABToBeSwedULItemIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABToBeSwedULItemIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABToBeSwedULItemIEs szProtIE_Field_E_RABToBeSwedULItemIEs
CmPAsnSetSeqOfDef szProtIE_ContLst_E_RABToBeSwedULItemIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_ContLst_E_RABToBeSwedULItemIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_ContLst_E_RABToBeSwedULItemIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_ContLst_E_RABToBeSwedULItemIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtIE_ContLst_E_RABToBeSwedULItemIEsspec),
   NULLP
};
#define szE_RAB_IE_ContLst_E_RABToBeSwedULItemIEs szProtIE_ContLst_E_RABToBeSwedULItemIEs
#define szE_RABToBeSwedULLst szE_RAB_IE_ContLst_E_RABToBeSwedULItemIEs
PUBLIC CmPAsnElmDef *sz_ValuePathSwRqstAckgIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szUEAggMaxBitrate,
   &szProtIE_ContLst_E_RABToBeSwedULItemIEs,
      &szProtIE_SingleCont_E_RABToBeSwedULItemIEs,
      &szConstTerm,
   &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      &szConstTerm,
   &szSecurCntxt,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValuePathSwRqstAckgIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_uEaggregateMaxBitrate,
   Sztid_E_RABToBeSwedULLst,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_E_RABToBeRlsdLst,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_SecurCntxt,
   Sztid_CriticalityDiag
};
SzMsgConInf szPathSwRqstAckgIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_uEaggregateMaxBitrate, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_E_RABToBeSwedULLst, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_E_RABToBeRlsdLst, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_SecurCntxt, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   7,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValuePathSwRqstAckgIEsClsInfo =
{
   11,
   &sz_ValuePathSwRqstAckgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValuePathSwRqstAckgIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValuePathSwRqstAckgIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValuePathSwRqstAckgIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValuePathSwRqstAckgIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValuePathSwRqstAckgIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValuePathSwRqstAckgIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValuePathSwRqstAckgIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_PathSwRqstAckgIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValuePathSwRqstAckgIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_PathSwRqstAckgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_PathSwRqstAckgIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_PathSwRqstAckgIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_PathSwRqstAckgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_PathSwRqstAckgIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_PathSwRqstAckgIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_PathSwRqstAckgIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_PathSwRqstAckgIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_PathSwRqstAckgIEs *protIe = NULLP;
   SztProtIE_Field_PathSwRqstAckgIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_PathSwRqstAckgIEsValidate);
   
   protIe = (SztProtIE_Cont_PathSwRqstAckgIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_PathSwRqstAckgIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szPathSwRqstAckgIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_PathSwRqstAckgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_PathSwRqstAckgIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_PathSwRqstAckgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_PathSwRqstAckgIEs),
   &flagSz3M,
   szProtIE_Cont_PathSwRqstAckgIEsValidate,
   (U8 *) (&szProtIE_Cont_PathSwRqstAckgIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szPathSwRqstAckgTkn[] =
{
   &szProtIE_Cont_PathSwRqstAckgIEs,
      &szProtIE_Field_PathSwRqstAckgIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szPathSwRqstAckgspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szPathSwRqstAckgTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szPathSwRqstAckg =
{
#ifdef CM_PASN_DBG
   " szPathSwRqstAckg ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztPathSwRqstAckg),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szPathSwRqstAckgspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValuePathSwRqstFailIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szCause,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValuePathSwRqstFailIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_Cause,
   Sztid_CriticalityDiag
};
SzMsgConInf szPathSwRqstFailIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   4,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValuePathSwRqstFailIEsClsInfo =
{
   4,
   &sz_ValuePathSwRqstFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValuePathSwRqstFailIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValuePathSwRqstFailIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValuePathSwRqstFailIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValuePathSwRqstFailIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValuePathSwRqstFailIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValuePathSwRqstFailIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValuePathSwRqstFailIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_PathSwRqstFailIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValuePathSwRqstFailIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_PathSwRqstFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_PathSwRqstFailIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_PathSwRqstFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_PathSwRqstFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_PathSwRqstFailIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_PathSwRqstFailIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_PathSwRqstFailIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_PathSwRqstFailIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_PathSwRqstFailIEs *protIe = NULLP;
   SztProtIE_Field_PathSwRqstFailIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_PathSwRqstFailIEsValidate);
   
   protIe = (SztProtIE_Cont_PathSwRqstFailIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_PathSwRqstFailIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szPathSwRqstFailIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_PathSwRqstFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_PathSwRqstFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_PathSwRqstFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_PathSwRqstFailIEs),
   &flagSz3M,
   szProtIE_Cont_PathSwRqstFailIEsValidate,
   (U8 *) (&szProtIE_Cont_PathSwRqstFailIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szPathSwRqstFailTkn[] =
{
   &szProtIE_Cont_PathSwRqstFailIEs,
      &szProtIE_Field_PathSwRqstFailIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szPathSwRqstFailspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szPathSwRqstFailTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szPathSwRqstFail =
{
#ifdef CM_PASN_DBG
   " szPathSwRqstFail ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztPathSwRqstFail),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szPathSwRqstFailspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueHovrCancelIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szCause
};
PUBLIC U32 sz_ValueHovrCancelIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_Cause
};
SzMsgConInf szHovrCancelIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   3,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueHovrCancelIEsClsInfo =
{
   3,
   &sz_ValueHovrCancelIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrCancelIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueHovrCancelIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueHovrCancelIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueHovrCancelIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueHovrCancelIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueHovrCancelIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueHovrCancelIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_HovrCancelIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueHovrCancelIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrCancelIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_HovrCancelIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_HovrCancelIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_HovrCancelIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_HovrCancelIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_HovrCancelIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_HovrCancelIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_HovrCancelIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_HovrCancelIEs *protIe = NULLP;
   SztProtIE_Field_HovrCancelIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_HovrCancelIEsValidate);
   
   protIe = (SztProtIE_Cont_HovrCancelIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_HovrCancelIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szHovrCancelIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrCancelIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_HovrCancelIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_HovrCancelIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_HovrCancelIEs),
   &flagSz3M,
   szProtIE_Cont_HovrCancelIEsValidate,
   (U8 *) (&szProtIE_Cont_HovrCancelIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szHovrCancelTkn[] =
{
   &szProtIE_Cont_HovrCancelIEs,
      &szProtIE_Field_HovrCancelIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szHovrCancelspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szHovrCancelTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szHovrCancel =
{
#ifdef CM_PASN_DBG
   " szHovrCancel ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztHovrCancel),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szHovrCancelspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueHovrCancelAckgIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueHovrCancelAckgIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_CriticalityDiag
};
SzMsgConInf szHovrCancelAckgIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   3,
   2
}; 
PUBLIC CmPAsnClassInfo sz_ValueHovrCancelAckgIEsClsInfo =
{
   3,
   &sz_ValueHovrCancelAckgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrCancelAckgIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueHovrCancelAckgIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueHovrCancelAckgIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueHovrCancelAckgIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueHovrCancelAckgIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueHovrCancelAckgIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueHovrCancelAckgIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_HovrCancelAckgIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueHovrCancelAckgIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrCancelAckgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_HovrCancelAckgIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_HovrCancelAckgIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_HovrCancelAckgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_HovrCancelAckgIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_HovrCancelAckgIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_HovrCancelAckgIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_HovrCancelAckgIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_HovrCancelAckgIEs *protIe = NULLP;
   SztProtIE_Field_HovrCancelAckgIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_HovrCancelAckgIEsValidate);
   
   protIe = (SztProtIE_Cont_HovrCancelAckgIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_HovrCancelAckgIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szHovrCancelAckgIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrCancelAckgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_HovrCancelAckgIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_HovrCancelAckgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_HovrCancelAckgIEs),
   &flagSz3M,
   szProtIE_Cont_HovrCancelAckgIEsValidate,
   (U8 *) (&szProtIE_Cont_HovrCancelAckgIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szHovrCancelAckgTkn[] =
{
   &szProtIE_Cont_HovrCancelAckgIEs,
      &szProtIE_Field_HovrCancelAckgIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szHovrCancelAckgspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szHovrCancelAckgTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szHovrCancelAckg =
{
#ifdef CM_PASN_DBG
   " szHovrCancelAckg ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztHovrCancelAckg),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szHovrCancelAckgspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABToBeSetupItemBrSUReqExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABToBeSetupItemBrSUReqExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABToBeSetupItemBrSUReqExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABToBeSetupItemBrSUReqExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABToBeSetupItemBrSUReqTkn[] =
{
   &szE_RAB_ID,
   &szE_RABLvlQoSParams,
   &szTportLyrAddr,
   &szGTP_TEID,
   &szNAS_PDU,
   &szOptProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs,
      &szProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABToBeSetupItemBrSUReqspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABToBeSetupItemBrSUReqTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABToBeSetupItemBrSUReq =
{
#ifdef CM_PASN_DBG
   " szE_RABToBeSetupItemBrSUReq ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABToBeSetupItemBrSUReq),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABToBeSetupItemBrSUReqspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABToBeSetupItemBrSUReqIEsClsInst[] =
{
   &szE_RABToBeSetupItemBrSUReq
};
PUBLIC U32 sz_ValueE_RABToBeSetupItemBrSUReqIEsClsInstId[] =
{
   Sztid_E_RABToBeSetupItemBrSUReq
};
SzMsgConInf szE_RABToBeSetupItemBrSUReqIEsConInf =
{
   {
      { Sztid_E_RABToBeSetupItemBrSUReq, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABToBeSetupItemBrSUReqIEsClsInfo =
{
   1,
   &sz_ValueE_RABToBeSetupItemBrSUReqIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABToBeSetupItemBrSUReqIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABToBeSetupItemBrSUReqIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABToBeSetupItemBrSUReqIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABToBeSetupItemBrSUReqIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABToBeSetupItemBrSUReqIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABToBeSetupItemBrSUReqIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABToBeSetupItemBrSUReqIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABToBeSetupItemBrSUReqIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABToBeSetupItemBrSUReqIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABToBeSetupItemBrSUReqIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABToBeSetupItemBrSUReqIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABToBeSetupItemBrSUReqIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABToBeSetupItemBrSUReqIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABToBeSetupItemBrSUReqIEs szProtIE_Field_E_RABToBeSetupItemBrSUReqIEs
CmPAsnSetSeqOfDef szE_RABToBeSetupLstBrSUReqspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szE_RABToBeSetupLstBrSUReq =
{
#ifdef CM_PASN_DBG
   " szE_RABToBeSetupLstBrSUReq ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztE_RABToBeSetupLstBrSUReq),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szE_RABToBeSetupLstBrSUReqspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABSetupRqstIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szUEAggMaxBitrate,
   &szE_RABToBeSetupLstBrSUReq,
      &szProtIE_Field_E_RABToBeSetupItemBrSUReqIEs,
      &szConstTerm,
   
};
PUBLIC U32 sz_ValueE_RABSetupRqstIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_uEaggregateMaxBitrate,
   Sztid_E_RABToBeSetupLstBrSUReq,
      Sztid_Invalid,
      Sztid_Invalid
};
SzMsgConInf szE_RABSetupRqstIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_uEaggregateMaxBitrate, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_E_RABToBeSetupLstBrSUReq, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   4,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABSetupRqstIEsClsInfo =
{
   6,
   &sz_ValueE_RABSetupRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABSetupRqstIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABSetupRqstIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABSetupRqstIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABSetupRqstIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABSetupRqstIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABSetupRqstIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABSetupRqstIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABSetupRqstIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABSetupRqstIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABSetupRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABSetupRqstIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABSetupRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABSetupRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABSetupRqstIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABSetupRqstIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_E_RABSetupRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_E_RABSetupRqstIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_E_RABSetupRqstIEs *protIe = NULLP;
   SztProtIE_Field_E_RABSetupRqstIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_E_RABSetupRqstIEsValidate);
   
   protIe = (SztProtIE_Cont_E_RABSetupRqstIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_E_RABSetupRqstIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szE_RABSetupRqstIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABSetupRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_E_RABSetupRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_E_RABSetupRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_E_RABSetupRqstIEs),
   &flagSz3M,
   szProtIE_Cont_E_RABSetupRqstIEsValidate,
   (U8 *) (&szProtIE_Cont_E_RABSetupRqstIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABSetupRqstTkn[] =
{
   &szProtIE_Cont_E_RABSetupRqstIEs,
      &szProtIE_Field_E_RABSetupRqstIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABSetupRqstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABSetupRqstTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABSetupRqst =
{
#ifdef CM_PASN_DBG
   " szE_RABSetupRqst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABSetupRqst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABSetupRqstspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABSetupItemBrSUResExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABSetupItemBrSUResExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABSetupItemBrSUResExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABSetupItemBrSUResExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABSetupItemBrSUResExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABSetupItemBrSUResExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABSetupItemBrSUResExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABSetupItemBrSUResExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABSetupItemBrSUResExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABSetupItemBrSUResExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABSetupItemBrSUResExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABSetupItemBrSUResExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABSetupItemBrSUResExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABSetupItemBrSUResExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABSetupItemBrSUResExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABSetupItemBrSUResExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABSetupItemBrSUResExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABSetupItemBrSUResExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABSetupItemBrSUResExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABSetupItemBrSUResExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABSetupItemBrSUResExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABSetupItemBrSUResExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABSetupItemBrSUResExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABSetupItemBrSUResExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABSetupItemBrSUResExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABSetupItemBrSUResExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABSetupItemBrSUResExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABSetupItemBrSUResExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABSetupItemBrSUResTkn[] =
{
   &szE_RAB_ID,
   &szTportLyrAddr,
   &szGTP_TEID,
   &szOptProtExtnCont_E_RABSetupItemBrSUResExtIEs,
      &szProtExtnField_E_RABSetupItemBrSUResExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABSetupItemBrSUResspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABSetupItemBrSUResTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABSetupItemBrSURes =
{
#ifdef CM_PASN_DBG
   " szE_RABSetupItemBrSURes ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABSetupItemBrSURes),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABSetupItemBrSUResspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABSetupItemBrSUResIEsClsInst[] =
{
   &szE_RABSetupItemBrSURes
};
PUBLIC U32 sz_ValueE_RABSetupItemBrSUResIEsClsInstId[] =
{
   Sztid_E_RABSetupItemBrSURes
};
SzMsgConInf szE_RABSetupItemBrSUResIEsConInf =
{
   {
      { Sztid_E_RABSetupItemBrSURes, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABSetupItemBrSUResIEsClsInfo =
{
   1,
   &sz_ValueE_RABSetupItemBrSUResIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABSetupItemBrSUResIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABSetupItemBrSUResIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABSetupItemBrSUResIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABSetupItemBrSUResIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABSetupItemBrSUResIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABSetupItemBrSUResIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABSetupItemBrSUResIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABSetupItemBrSUResIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABSetupItemBrSUResIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABSetupItemBrSUResIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABSetupItemBrSUResIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABSetupItemBrSUResIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABSetupItemBrSUResIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABSetupItemBrSUResIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABSetupItemBrSUResIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABSetupItemBrSUResIEs szProtIE_Field_E_RABSetupItemBrSUResIEs
CmPAsnSetSeqOfDef szE_RABSetupLstBrSUResspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szE_RABSetupLstBrSURes =
{
#ifdef CM_PASN_DBG
   " szE_RABSetupLstBrSURes ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztE_RABSetupLstBrSURes),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szE_RABSetupLstBrSUResspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABSetupRespIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szE_RABSetupLstBrSURes,
      &szProtIE_Field_E_RABSetupItemBrSUResIEs,
      &szConstTerm,
   &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      &szConstTerm,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueE_RABSetupRespIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_E_RABSetupLstBrSURes,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_E_RABFailedToSetupLstBrSURes,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_CriticalityDiag
};
SzMsgConInf szE_RABSetupRespIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_E_RABSetupLstBrSURes, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_E_RABFailedToSetupLstBrSURes, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   5,
   2
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABSetupRespIEsClsInfo =
{
   9,
   &sz_ValueE_RABSetupRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABSetupRespIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABSetupRespIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABSetupRespIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABSetupRespIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABSetupRespIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABSetupRespIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABSetupRespIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABSetupRespIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABSetupRespIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABSetupRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABSetupRespIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABSetupRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABSetupRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABSetupRespIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABSetupRespIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_E_RABSetupRespIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_E_RABSetupRespIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_E_RABSetupRespIEs *protIe = NULLP;
   SztProtIE_Field_E_RABSetupRespIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_E_RABSetupRespIEsValidate);
   
   protIe = (SztProtIE_Cont_E_RABSetupRespIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_E_RABSetupRespIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szE_RABSetupRespIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABSetupRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_E_RABSetupRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_E_RABSetupRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_E_RABSetupRespIEs),
   &flagSz3M,
   szProtIE_Cont_E_RABSetupRespIEsValidate,
   (U8 *) (&szProtIE_Cont_E_RABSetupRespIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABSetupRespTkn[] =
{
   &szProtIE_Cont_E_RABSetupRespIEs,
      &szProtIE_Field_E_RABSetupRespIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABSetupRespspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABSetupRespTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABSetupResp =
{
#ifdef CM_PASN_DBG
   " szE_RABSetupResp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABSetupResp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABSetupRespspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABToBeMdfyItemBrModReqExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABToBeMdfyItemBrModReqExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABToBeMdfyItemBrModReqExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABToBeMdfyItemBrModReqExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABToBeMdfdItemBrModReqTkn[] =
{
   &szE_RAB_ID,
   &szE_RABLvlQoSParams,
   &szNAS_PDU,
   &szOptProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs,
      &szProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABToBeMdfdItemBrModReqspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABToBeMdfdItemBrModReqTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABToBeMdfdItemBrModReq =
{
#ifdef CM_PASN_DBG
   " szE_RABToBeMdfdItemBrModReq ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABToBeMdfdItemBrModReq),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABToBeMdfdItemBrModReqspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABToBeMdfdItemBrModReqIEsClsInst[] =
{
   &szE_RABToBeMdfdItemBrModReq
};
PUBLIC U32 sz_ValueE_RABToBeMdfdItemBrModReqIEsClsInstId[] =
{
   Sztid_E_RABToBeMdfdItemBrModReq
};
SzMsgConInf szE_RABToBeMdfdItemBrModReqIEsConInf =
{
   {
      { Sztid_E_RABToBeMdfdItemBrModReq, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABToBeMdfdItemBrModReqIEsClsInfo =
{
   1,
   &sz_ValueE_RABToBeMdfdItemBrModReqIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABToBeMdfdItemBrModReqIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABToBeMdfdItemBrModReqIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABToBeMdfdItemBrModReqIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABToBeMdfdItemBrModReqIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABToBeMdfdItemBrModReqIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABToBeMdfdItemBrModReqIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABToBeMdfdItemBrModReqIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABToBeMdfdItemBrModReqIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABToBeMdfdItemBrModReqIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABToBeMdfdItemBrModReqIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABToBeMdfdItemBrModReqIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABToBeMdfdItemBrModReqIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABToBeMdfdItemBrModReqIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABToBeMdfdItemBrModReqIEs szProtIE_Field_E_RABToBeMdfdItemBrModReqIEs
CmPAsnSetSeqOfDef szE_RABToBeMdfdLstBrModReqspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szE_RABToBeMdfdLstBrModReq =
{
#ifdef CM_PASN_DBG
   " szE_RABToBeMdfdLstBrModReq ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztE_RABToBeMdfdLstBrModReq),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szE_RABToBeMdfdLstBrModReqspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABMdfyRqstIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szUEAggMaxBitrate,
   &szE_RABToBeMdfdLstBrModReq,
      &szProtIE_Field_E_RABToBeMdfdItemBrModReqIEs,
      &szConstTerm,
   
};
PUBLIC U32 sz_ValueE_RABMdfyRqstIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_uEaggregateMaxBitrate,
   Sztid_E_RABToBeMdfdLstBrModReq,
      Sztid_Invalid,
      Sztid_Invalid
};
SzMsgConInf szE_RABMdfyRqstIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_uEaggregateMaxBitrate, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_E_RABToBeMdfdLstBrModReq, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   4,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABMdfyRqstIEsClsInfo =
{
   6,
   &sz_ValueE_RABMdfyRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABMdfyRqstIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABMdfyRqstIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABMdfyRqstIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABMdfyRqstIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABMdfyRqstIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABMdfyRqstIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABMdfyRqstIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABMdfyRqstIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABMdfyRqstIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABMdfyRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABMdfyRqstIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABMdfyRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABMdfyRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABMdfyRqstIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABMdfyRqstIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_E_RABMdfyRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_E_RABMdfyRqstIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_E_RABMdfyRqstIEs *protIe = NULLP;
   SztProtIE_Field_E_RABMdfyRqstIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_E_RABMdfyRqstIEsValidate);
   
   protIe = (SztProtIE_Cont_E_RABMdfyRqstIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_E_RABMdfyRqstIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szE_RABMdfyRqstIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABMdfyRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_E_RABMdfyRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_E_RABMdfyRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_E_RABMdfyRqstIEs),
   &flagSz3M,
   szProtIE_Cont_E_RABMdfyRqstIEsValidate,
   (U8 *) (&szProtIE_Cont_E_RABMdfyRqstIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABMdfyRqstTkn[] =
{
   &szProtIE_Cont_E_RABMdfyRqstIEs,
      &szProtIE_Field_E_RABMdfyRqstIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABMdfyRqstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABMdfyRqstTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABMdfyRqst =
{
#ifdef CM_PASN_DBG
   " szE_RABMdfyRqst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABMdfyRqst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABMdfyRqstspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABMdfyItemBrModResExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABMdfyItemBrModResExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABMdfyItemBrModResExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABMdfyItemBrModResExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABMdfyItemBrModResExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABMdfyItemBrModResExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABMdfyItemBrModResExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABMdfyItemBrModResExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABMdfyItemBrModResExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABMdfyItemBrModResExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABMdfyItemBrModResExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABMdfyItemBrModResExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABMdfyItemBrModResExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABMdfyItemBrModResExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABMdfyItemBrModResExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABMdfyItemBrModResExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABMdfyItemBrModResExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABMdfyItemBrModResExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABMdfyItemBrModResExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABMdfyItemBrModResExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABMdfyItemBrModResExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABMdfyItemBrModResExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABMdfyItemBrModResExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABMdfyItemBrModResExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABMdfyItemBrModResExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABMdfyItemBrModResExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABMdfyItemBrModResExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABMdfyItemBrModResExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABMdfyItemBrModResTkn[] =
{
   &szE_RAB_ID,
   &szOptProtExtnCont_E_RABMdfyItemBrModResExtIEs,
      &szProtExtnField_E_RABMdfyItemBrModResExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABMdfyItemBrModResspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABMdfyItemBrModResTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABMdfyItemBrModRes =
{
#ifdef CM_PASN_DBG
   " szE_RABMdfyItemBrModRes ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABMdfyItemBrModRes),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABMdfyItemBrModResspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABMdfyItemBrModResIEsClsInst[] =
{
   &szE_RABMdfyItemBrModRes
};
PUBLIC U32 sz_ValueE_RABMdfyItemBrModResIEsClsInstId[] =
{
   Sztid_E_RABMdfyItemBrModRes
};
SzMsgConInf szE_RABMdfyItemBrModResIEsConInf =
{
   {
      { Sztid_E_RABMdfyItemBrModRes, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABMdfyItemBrModResIEsClsInfo =
{
   1,
   &sz_ValueE_RABMdfyItemBrModResIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABMdfyItemBrModResIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABMdfyItemBrModResIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABMdfyItemBrModResIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABMdfyItemBrModResIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABMdfyItemBrModResIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABMdfyItemBrModResIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABMdfyItemBrModResIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABMdfyItemBrModResIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABMdfyItemBrModResIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABMdfyItemBrModResIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABMdfyItemBrModResIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABMdfyItemBrModResIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABMdfyItemBrModResIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABMdfyItemBrModResIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABMdfyItemBrModResIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABMdfyItemBrModResIEs szProtIE_Field_E_RABMdfyItemBrModResIEs
CmPAsnSetSeqOfDef szE_RABMdfyLstBrModResspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szE_RABMdfyLstBrModRes =
{
#ifdef CM_PASN_DBG
   " szE_RABMdfyLstBrModRes ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztE_RABMdfyLstBrModRes),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szE_RABMdfyLstBrModResspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABMdfyRespIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szE_RABMdfyLstBrModRes,
      &szProtIE_Field_E_RABMdfyItemBrModResIEs,
      &szConstTerm,
   &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      &szConstTerm,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueE_RABMdfyRespIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_E_RABMdfyLstBrModRes,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_E_RABFailedToMdfyLst,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_CriticalityDiag
};
SzMsgConInf szE_RABMdfyRespIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_E_RABMdfyLstBrModRes, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_E_RABFailedToMdfyLst, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   5,
   2
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABMdfyRespIEsClsInfo =
{
   9,
   &sz_ValueE_RABMdfyRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABMdfyRespIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABMdfyRespIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABMdfyRespIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABMdfyRespIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABMdfyRespIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABMdfyRespIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABMdfyRespIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABMdfyRespIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABMdfyRespIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABMdfyRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABMdfyRespIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABMdfyRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABMdfyRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABMdfyRespIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABMdfyRespIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_E_RABMdfyRespIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_E_RABMdfyRespIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_E_RABMdfyRespIEs *protIe = NULLP;
   SztProtIE_Field_E_RABMdfyRespIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_E_RABMdfyRespIEsValidate);
   
   protIe = (SztProtIE_Cont_E_RABMdfyRespIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_E_RABMdfyRespIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szE_RABMdfyRespIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABMdfyRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_E_RABMdfyRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_E_RABMdfyRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_E_RABMdfyRespIEs),
   &flagSz3M,
   szProtIE_Cont_E_RABMdfyRespIEsValidate,
   (U8 *) (&szProtIE_Cont_E_RABMdfyRespIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABMdfyRespTkn[] =
{
   &szProtIE_Cont_E_RABMdfyRespIEs,
      &szProtIE_Field_E_RABMdfyRespIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABMdfyRespspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABMdfyRespTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABMdfyResp =
{
#ifdef CM_PASN_DBG
   " szE_RABMdfyResp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABMdfyResp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABMdfyRespspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABRlsCmmdIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szUEAggMaxBitrate,
   &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      &szConstTerm,
   &szNAS_PDU
};
PUBLIC U32 sz_ValueE_RABRlsCmmdIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_uEaggregateMaxBitrate,
   Sztid_E_RABToBeRlsdLst,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_NAS_PDU
};
SzMsgConInf szE_RABRlsCmmdIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_uEaggregateMaxBitrate, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_E_RABToBeRlsdLst, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_NAS_PDU, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   5,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABRlsCmmdIEsClsInfo =
{
   7,
   &sz_ValueE_RABRlsCmmdIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABRlsCmmdIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABRlsCmmdIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABRlsCmmdIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABRlsCmmdIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABRlsCmmdIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABRlsCmmdIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABRlsCmmdIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABRlsCmmdIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABRlsCmmdIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABRlsCmmdIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABRlsCmmdIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABRlsCmmdIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABRlsCmmdIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABRlsCmmdIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABRlsCmmdIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_E_RABRlsCmmdIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_E_RABRlsCmmdIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_E_RABRlsCmmdIEs *protIe = NULLP;
   SztProtIE_Field_E_RABRlsCmmdIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_E_RABRlsCmmdIEsValidate);
   
   protIe = (SztProtIE_Cont_E_RABRlsCmmdIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_E_RABRlsCmmdIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szE_RABRlsCmmdIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABRlsCmmdIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_E_RABRlsCmmdIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_E_RABRlsCmmdIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_E_RABRlsCmmdIEs),
   &flagSz3M,
   szProtIE_Cont_E_RABRlsCmmdIEsValidate,
   (U8 *) (&szProtIE_Cont_E_RABRlsCmmdIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABRlsCmmdTkn[] =
{
   &szProtIE_Cont_E_RABRlsCmmdIEs,
      &szProtIE_Field_E_RABRlsCmmdIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABRlsCmmdspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABRlsCmmdTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABRlsCmmd =
{
#ifdef CM_PASN_DBG
   " szE_RABRlsCmmd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABRlsCmmd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABRlsCmmdspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABRlsItemBrRelCompExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABRlsItemBrRelCompExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABRlsItemBrRelCompExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABRlsItemBrRelCompExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABRlsItemBrRelCompExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABRlsItemBrRelCompExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABRlsItemBrRelCompExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABRlsItemBrRelCompExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABRlsItemBrRelCompExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABRlsItemBrRelCompExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABRlsItemBrRelCompExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABRlsItemBrRelCompExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABRlsItemBrRelCompExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABRlsItemBrRelCompExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABRlsItemBrRelCompExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABRlsItemBrRelCompExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABRlsItemBrRelCompExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABRlsItemBrRelCompExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABRlsItemBrRelCompExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABRlsItemBrRelCompExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABRlsItemBrRelCompExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABRlsItemBrRelCompExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABRlsItemBrRelCompExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABRlsItemBrRelCompExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABRlsItemBrRelCompExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABRlsItemBrRelCompTkn[] =
{
   &szE_RAB_ID,
   &szOptProtExtnCont_E_RABRlsItemBrRelCompExtIEs,
      &szProtExtnField_E_RABRlsItemBrRelCompExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABRlsItemBrRelCompspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABRlsItemBrRelCompTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABRlsItemBrRelComp =
{
#ifdef CM_PASN_DBG
   " szE_RABRlsItemBrRelComp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABRlsItemBrRelComp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABRlsItemBrRelCompspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABRlsItemBrRelCompIEsClsInst[] =
{
   &szE_RABRlsItemBrRelComp
};
PUBLIC U32 sz_ValueE_RABRlsItemBrRelCompIEsClsInstId[] =
{
   Sztid_E_RABRlsItemBrRelComp
};
SzMsgConInf szE_RABRlsItemBrRelCompIEsConInf =
{
   {
      { Sztid_E_RABRlsItemBrRelComp, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABRlsItemBrRelCompIEsClsInfo =
{
   1,
   &sz_ValueE_RABRlsItemBrRelCompIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABRlsItemBrRelCompIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABRlsItemBrRelCompIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABRlsItemBrRelCompIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABRlsItemBrRelCompIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABRlsItemBrRelCompIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABRlsItemBrRelCompIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABRlsItemBrRelCompIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABRlsItemBrRelCompIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABRlsItemBrRelCompIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABRlsItemBrRelCompIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABRlsItemBrRelCompIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABRlsItemBrRelCompIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABRlsItemBrRelCompIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABRlsItemBrRelCompIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABRlsItemBrRelCompIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABRlsItemBrRelCompIEs szProtIE_Field_E_RABRlsItemBrRelCompIEs
CmPAsnSetSeqOfDef szE_RABRlsLstBrRelCompspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szE_RABRlsLstBrRelComp =
{
#ifdef CM_PASN_DBG
   " szE_RABRlsLstBrRelComp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztE_RABRlsLstBrRelComp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szE_RABRlsLstBrRelCompspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABRlsRespIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szE_RABRlsLstBrRelComp,
      &szProtIE_Field_E_RABRlsItemBrRelCompIEs,
      &szConstTerm,
   &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      &szConstTerm,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueE_RABRlsRespIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_E_RABRlsLstBrRelComp,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_E_RABFailedToRlsLst,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_CriticalityDiag
};
SzMsgConInf szE_RABRlsRespIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_E_RABRlsLstBrRelComp, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_E_RABFailedToRlsLst, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   5,
   2
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABRlsRespIEsClsInfo =
{
   9,
   &sz_ValueE_RABRlsRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABRlsRespIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABRlsRespIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABRlsRespIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABRlsRespIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABRlsRespIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABRlsRespIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABRlsRespIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABRlsRespIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABRlsRespIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABRlsRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABRlsRespIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABRlsRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABRlsRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABRlsRespIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABRlsRespIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_E_RABRlsRespIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_E_RABRlsRespIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_E_RABRlsRespIEs *protIe = NULLP;
   SztProtIE_Field_E_RABRlsRespIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_E_RABRlsRespIEsValidate);
   
   protIe = (SztProtIE_Cont_E_RABRlsRespIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_E_RABRlsRespIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szE_RABRlsRespIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABRlsRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_E_RABRlsRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_E_RABRlsRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_E_RABRlsRespIEs),
   &flagSz3M,
   szProtIE_Cont_E_RABRlsRespIEsValidate,
   (U8 *) (&szProtIE_Cont_E_RABRlsRespIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABRlsRespTkn[] =
{
   &szProtIE_Cont_E_RABRlsRespIEs,
      &szProtIE_Field_E_RABRlsRespIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABRlsRespspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABRlsRespTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABRlsResp =
{
#ifdef CM_PASN_DBG
   " szE_RABRlsResp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABRlsResp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABRlsRespspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABRlsIndIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      &szConstTerm,
   
};
PUBLIC U32 sz_ValueE_RABRlsIndIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_E_RABRlsdLst,
      Sztid_Invalid,
      Sztid_Invalid
};
SzMsgConInf szE_RABRlsIndIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_E_RABRlsdLst, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   3,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABRlsIndIEsClsInfo =
{
   5,
   &sz_ValueE_RABRlsIndIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABRlsIndIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABRlsIndIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABRlsIndIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABRlsIndIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABRlsIndIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABRlsIndIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABRlsIndIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABRlsIndIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABRlsIndIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABRlsIndIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABRlsIndIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABRlsIndIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABRlsIndIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABRlsIndIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABRlsIndIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_E_RABRlsIndIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_E_RABRlsIndIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_E_RABRlsIndIEs *protIe = NULLP;
   SztProtIE_Field_E_RABRlsIndIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_E_RABRlsIndIEsValidate);
   
   protIe = (SztProtIE_Cont_E_RABRlsIndIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_E_RABRlsIndIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szE_RABRlsIndIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABRlsIndIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_E_RABRlsIndIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_E_RABRlsIndIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_E_RABRlsIndIEs),
   &flagSz3M,
   szProtIE_Cont_E_RABRlsIndIEsValidate,
   (U8 *) (&szProtIE_Cont_E_RABRlsIndIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABRlsIndTkn[] =
{
   &szProtIE_Cont_E_RABRlsIndIEs,
      &szProtIE_Field_E_RABRlsIndIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABRlsIndspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABRlsIndTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABRlsInd =
{
#ifdef CM_PASN_DBG
   " szE_RABRlsInd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABRlsInd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABRlsIndspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABToBeSetupItemCtxtSUReqTkn[] =
{
   &szE_RAB_ID,
   &szE_RABLvlQoSParams,
   &szTportLyrAddr,
   &szGTP_TEID,
   &szOptNAS_PDU,
   &szOptProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs,
      &szProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABToBeSetupItemCtxtSUReqspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   2,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABToBeSetupItemCtxtSUReqTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABToBeSetupItemCtxtSUReq =
{
#ifdef CM_PASN_DBG
   " szE_RABToBeSetupItemCtxtSUReq ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABToBeSetupItemCtxtSUReq),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABToBeSetupItemCtxtSUReqspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsInst[] =
{
   &szE_RABToBeSetupItemCtxtSUReq
};
PUBLIC U32 sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsInstId[] =
{
   Sztid_E_RABToBeSetupItemCtxtSUReq
};
SzMsgConInf szE_RABToBeSetupItemCtxtSUReqIEsConInf =
{
   {
      { Sztid_E_RABToBeSetupItemCtxtSUReq, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsInfo =
{
   1,
   &sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABToBeSetupItemCtxtSUReqIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABToBeSetupItemCtxtSUReqIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABToBeSetupItemCtxtSUReqIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABToBeSetupItemCtxtSUReqIEs szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs
CmPAsnSetSeqOfDef szE_RABToBeSetupLstCtxtSUReqspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szE_RABToBeSetupLstCtxtSUReq =
{
#ifdef CM_PASN_DBG
   " szE_RABToBeSetupLstCtxtSUReq ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztE_RABToBeSetupLstCtxtSUReq),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szE_RABToBeSetupLstCtxtSUReqspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueInitCntxtSetupRqstIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szUEAggMaxBitrate,
   &szE_RABToBeSetupLstCtxtSUReq,
      &szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs,
      &szConstTerm,
   &szUESecurCapabilities,
   &szSecurKey,
   &szTraceActvn,
   &szHovrRestrnLst,
   &szUERadioCapblty,
   &szSubscriberProfileIDforRFP,
   &szCSFallbackIndicator,
   &szSRVCCOperationPossible
};
PUBLIC U32 sz_ValueInitCntxtSetupRqstIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_uEaggregateMaxBitrate,
   Sztid_E_RABToBeSetupLstCtxtSUReq,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_UESecurCapabilities,
   Sztid_SecurKey,
   Sztid_TraceActvn,
   Sztid_HovrRestrnLst,
   Sztid_UERadioCapblty,
   Sztid_SubscriberProfileIDforRFP,
   Sztid_CSFallbackIndicator,
   Sztid_SRVCCOperationPossible
};
SzMsgConInf szInitCntxtSetupRqstIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_uEaggregateMaxBitrate, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_E_RABToBeSetupLstCtxtSUReq, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_UESecurCapabilities, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_SecurKey, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_TraceActvn, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_HovrRestrnLst, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_UERadioCapblty, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_SubscriberProfileIDforRFP, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_CSFallbackIndicator, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_SRVCCOperationPossible, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   12,
   6
}; 
PUBLIC CmPAsnClassInfo sz_ValueInitCntxtSetupRqstIEsClsInfo =
{
   14,
   &sz_ValueInitCntxtSetupRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueInitCntxtSetupRqstIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueInitCntxtSetupRqstIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueInitCntxtSetupRqstIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueInitCntxtSetupRqstIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueInitCntxtSetupRqstIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueInitCntxtSetupRqstIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueInitCntxtSetupRqstIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_InitCntxtSetupRqstIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueInitCntxtSetupRqstIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_InitCntxtSetupRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_InitCntxtSetupRqstIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_InitCntxtSetupRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_InitCntxtSetupRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_InitCntxtSetupRqstIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_InitCntxtSetupRqstIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_InitCntxtSetupRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_InitCntxtSetupRqstIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_InitCntxtSetupRqstIEs *protIe = NULLP;
   SztProtIE_Field_InitCntxtSetupRqstIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_InitCntxtSetupRqstIEsValidate);
   
   protIe = (SztProtIE_Cont_InitCntxtSetupRqstIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_InitCntxtSetupRqstIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szInitCntxtSetupRqstIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_InitCntxtSetupRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_InitCntxtSetupRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_InitCntxtSetupRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_InitCntxtSetupRqstIEs),
   &flagSz3M,
   szProtIE_Cont_InitCntxtSetupRqstIEsValidate,
   (U8 *) (&szProtIE_Cont_InitCntxtSetupRqstIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szInitCntxtSetupRqstTkn[] =
{
   &szProtIE_Cont_InitCntxtSetupRqstIEs,
      &szProtIE_Field_InitCntxtSetupRqstIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szInitCntxtSetupRqstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szInitCntxtSetupRqstTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szInitCntxtSetupRqst =
{
#ifdef CM_PASN_DBG
   " szInitCntxtSetupRqst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztInitCntxtSetupRqst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szInitCntxtSetupRqstspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsInfo =
{
   0,
   &sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnE_RABSetupItemCtxtSUResExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnE_RABSetupItemCtxtSUResExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_E_RABSetupItemCtxtSUResExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnE_RABSetupItemCtxtSUResExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABSetupItemCtxtSUResExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_E_RABSetupItemCtxtSUResExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_E_RABSetupItemCtxtSUResExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_E_RABSetupItemCtxtSUResExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_E_RABSetupItemCtxtSUResExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABSetupItemCtxtSUResExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_E_RABSetupItemCtxtSUResExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABSetupItemCtxtSUResExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABSetupItemCtxtSUResExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_E_RABSetupItemCtxtSUResExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_E_RABSetupItemCtxtSUResExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_E_RABSetupItemCtxtSUResExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szE_RABSetupItemCtxtSUResTkn[] =
{
   &szE_RAB_ID,
   &szTportLyrAddr,
   &szGTP_TEID,
   &szOptProtExtnCont_E_RABSetupItemCtxtSUResExtIEs,
      &szProtExtnField_E_RABSetupItemCtxtSUResExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szE_RABSetupItemCtxtSUResspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szE_RABSetupItemCtxtSUResTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szE_RABSetupItemCtxtSURes =
{
#ifdef CM_PASN_DBG
   " szE_RABSetupItemCtxtSURes ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztE_RABSetupItemCtxtSURes),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szE_RABSetupItemCtxtSUResspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueE_RABSetupItemCtxtSUResIEsClsInst[] =
{
   &szE_RABSetupItemCtxtSURes
};
PUBLIC U32 sz_ValueE_RABSetupItemCtxtSUResIEsClsInstId[] =
{
   Sztid_E_RABSetupItemCtxtSURes
};
SzMsgConInf szE_RABSetupItemCtxtSUResIEsConInf =
{
   {
      { Sztid_E_RABSetupItemCtxtSURes, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueE_RABSetupItemCtxtSUResIEsClsInfo =
{
   1,
   &sz_ValueE_RABSetupItemCtxtSUResIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABSetupItemCtxtSUResIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueE_RABSetupItemCtxtSUResIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueE_RABSetupItemCtxtSUResIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueE_RABSetupItemCtxtSUResIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueE_RABSetupItemCtxtSUResIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueE_RABSetupItemCtxtSUResIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueE_RABSetupItemCtxtSUResIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_E_RABSetupItemCtxtSUResIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueE_RABSetupItemCtxtSUResIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABSetupItemCtxtSUResIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_E_RABSetupItemCtxtSUResIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_E_RABSetupItemCtxtSUResIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_E_RABSetupItemCtxtSUResIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_E_RABSetupItemCtxtSUResIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_E_RABSetupItemCtxtSUResIEsspec),
   NULLP
};
#define szProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs szProtIE_Field_E_RABSetupItemCtxtSUResIEs
CmPAsnSetSeqOfDef szE_RABSetupLstCtxtSUResspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfE_RABs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szE_RABSetupLstCtxtSURes =
{
#ifdef CM_PASN_DBG
   " szE_RABSetupLstCtxtSURes ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztE_RABSetupLstCtxtSURes),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szE_RABSetupLstCtxtSUResspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueInitCntxtSetupRespIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szE_RABSetupLstCtxtSURes,
      &szProtIE_Field_E_RABSetupItemCtxtSUResIEs,
      &szConstTerm,
   &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      &szConstTerm,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueInitCntxtSetupRespIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_E_RABSetupLstCtxtSURes,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_E_RABFailedToSetupLstCtxtSURes,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_CriticalityDiag
};
SzMsgConInf szInitCntxtSetupRespIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_E_RABSetupLstCtxtSURes, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_E_RABFailedToSetupLstCtxtSURes, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   5,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueInitCntxtSetupRespIEsClsInfo =
{
   9,
   &sz_ValueInitCntxtSetupRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueInitCntxtSetupRespIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueInitCntxtSetupRespIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueInitCntxtSetupRespIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueInitCntxtSetupRespIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueInitCntxtSetupRespIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueInitCntxtSetupRespIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueInitCntxtSetupRespIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_InitCntxtSetupRespIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueInitCntxtSetupRespIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_InitCntxtSetupRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_InitCntxtSetupRespIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_InitCntxtSetupRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_InitCntxtSetupRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_InitCntxtSetupRespIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_InitCntxtSetupRespIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_InitCntxtSetupRespIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_InitCntxtSetupRespIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_InitCntxtSetupRespIEs *protIe = NULLP;
   SztProtIE_Field_InitCntxtSetupRespIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_InitCntxtSetupRespIEsValidate);
   
   protIe = (SztProtIE_Cont_InitCntxtSetupRespIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_InitCntxtSetupRespIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szInitCntxtSetupRespIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_InitCntxtSetupRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_InitCntxtSetupRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_InitCntxtSetupRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_InitCntxtSetupRespIEs),
   &flagSz3M,
   szProtIE_Cont_InitCntxtSetupRespIEsValidate,
   (U8 *) (&szProtIE_Cont_InitCntxtSetupRespIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szInitCntxtSetupRespTkn[] =
{
   &szProtIE_Cont_InitCntxtSetupRespIEs,
      &szProtIE_Field_InitCntxtSetupRespIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szInitCntxtSetupRespspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szInitCntxtSetupRespTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szInitCntxtSetupResp =
{
#ifdef CM_PASN_DBG
   " szInitCntxtSetupResp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztInitCntxtSetupResp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szInitCntxtSetupRespspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueInitCntxtSetupFailIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szCause,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueInitCntxtSetupFailIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_Cause,
   Sztid_CriticalityDiag
};
SzMsgConInf szInitCntxtSetupFailIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   4,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueInitCntxtSetupFailIEsClsInfo =
{
   4,
   &sz_ValueInitCntxtSetupFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueInitCntxtSetupFailIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueInitCntxtSetupFailIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueInitCntxtSetupFailIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueInitCntxtSetupFailIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueInitCntxtSetupFailIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueInitCntxtSetupFailIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueInitCntxtSetupFailIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_InitCntxtSetupFailIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueInitCntxtSetupFailIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_InitCntxtSetupFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_InitCntxtSetupFailIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_InitCntxtSetupFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_InitCntxtSetupFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_InitCntxtSetupFailIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_InitCntxtSetupFailIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_InitCntxtSetupFailIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_InitCntxtSetupFailIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_InitCntxtSetupFailIEs *protIe = NULLP;
   SztProtIE_Field_InitCntxtSetupFailIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_InitCntxtSetupFailIEsValidate);
   
   protIe = (SztProtIE_Cont_InitCntxtSetupFailIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_InitCntxtSetupFailIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szInitCntxtSetupFailIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_InitCntxtSetupFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_InitCntxtSetupFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_InitCntxtSetupFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_InitCntxtSetupFailIEs),
   &flagSz3M,
   szProtIE_Cont_InitCntxtSetupFailIEsValidate,
   (U8 *) (&szProtIE_Cont_InitCntxtSetupFailIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szInitCntxtSetupFailTkn[] =
{
   &szProtIE_Cont_InitCntxtSetupFailIEs,
      &szProtIE_Field_InitCntxtSetupFailIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szInitCntxtSetupFailspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szInitCntxtSetupFailTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szInitCntxtSetupFail =
{
#ifdef CM_PASN_DBG
   " szInitCntxtSetupFail ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztInitCntxtSetupFail),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szInitCntxtSetupFailspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ExtnTAIItemExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ExtnTAIItemExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz_ExtnTAIItemExtIEsClsInfo =
{
   0,
   &sz_ExtnTAIItemExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTAIItemExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ExtnTAIItemExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz_ExtnTAIItemExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ExtnTAIItemExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ExtnTAIItemExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnTAIItemExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ExtnTAIItemExtIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtExtnField_TAIItemExtIEsTkn[] =
{
   &szProtExtnID,
   &szCriticality,
   &sz_ExtnTAIItemExtIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TAIItemExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtExtnField_TAIItemExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtExtnField_TAIItemExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnField_TAIItemExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_TAIItemExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtExtnField_TAIItemExtIEsspec),
   NULLP
};
CmPAsnSetSeqOfDef szProtExtnCont_TAIItemExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szOptProtExtnCont_TAIItemExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TAIItemExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TAIItemExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TAIItemExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef szProtExtnCont_TAIItemExtIEs =
{
#ifdef CM_PASN_DBG
   " szProtExtnCont_TAIItemExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TAIItemExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szProtExtnCont_TAIItemExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szTAIItemTkn[] =
{
   &szTAI,
   &szOptProtExtnCont_TAIItemExtIEs,
      &szProtExtnField_TAIItemExtIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szTAIItemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szTAIItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szTAIItem =
{
#ifdef CM_PASN_DBG
   " szTAIItem ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTAIItem),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTAIItemspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueTAIItemIEsClsInst[] =
{
   &szTAIItem
};
PUBLIC U32 sz_ValueTAIItemIEsClsInstId[] =
{
   Sztid_TAIItem
};
SzMsgConInf szTAIItemIEsConInf =
{
   {
      { Sztid_TAIItem, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueTAIItemIEsClsInfo =
{
   1,
   &sz_ValueTAIItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueTAIItemIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueTAIItemIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueTAIItemIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueTAIItemIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueTAIItemIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueTAIItemIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueTAIItemIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_TAIItemIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueTAIItemIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_TAIItemIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_TAIItemIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_TAIItemIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_TAIItemIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_TAIItemIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_TAIItemIEsspec),
   NULLP
};
#define szProtIE_SingleCont_TAIItemIEs szProtIE_Field_TAIItemIEs
CmPAsnSetSeqOfDef szTAILstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxnoofTAIs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szTAILst =
{
#ifdef CM_PASN_DBG
   " szTAILst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTAILst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szTAILstspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValuePagIEsClsInst[] =
{
   &szUEIdentityIdxValue,
   &szUEPagID,
   &szPagDRX,
   &szCNDomain,
   &szTAILst,
      &szProtIE_Field_TAIItemIEs,
      &szConstTerm,
   &szCSG_IdLst,
      &szCSG_IdLst_Item,
      &szConstTerm,
   
};
PUBLIC U32 sz_ValuePagIEsClsInstId[] =
{
   Sztid_UEIdentityIdxValue,
   Sztid_UEPagID,
   Sztid_pagingDRX,
   Sztid_CNDomain,
   Sztid_TAILst,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_CSG_IdLst,
      Sztid_Invalid,
      Sztid_Invalid
};
SzMsgConInf szPagIEsConInf =
{
   {
      { Sztid_UEIdentityIdxValue, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_UEPagID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_pagingDRX, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_CNDomain, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_TAILst, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_CSG_IdLst, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   6,
   4
}; 
PUBLIC CmPAsnClassInfo sz_ValuePagIEsClsInfo =
{
   10,
   &sz_ValuePagIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValuePagIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValuePagIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValuePagIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValuePagIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValuePagIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValuePagIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValuePagIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_PagIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValuePagIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_PagIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_PagIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_PagIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_PagIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_PagIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_PagIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_PagIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_PagIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_PagIEs *protIe = NULLP;
   SztProtIE_Field_PagIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_PagIEsValidate);
   
   protIe = (SztProtIE_Cont_PagIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_PagIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szPagIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_PagIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_PagIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_PagIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_PagIEs),
   &flagSz3M,
   szProtIE_Cont_PagIEsValidate,
   (U8 *) (&szProtIE_Cont_PagIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szPagTkn[] =
{
   &szProtIE_Cont_PagIEs,
      &szProtIE_Field_PagIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szPagspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szPagTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szPag =
{
#ifdef CM_PASN_DBG
   " szPag ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztPag),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szPagspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueUECntxtRlsRqst_IEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szCause
};
PUBLIC U32 sz_ValueUECntxtRlsRqst_IEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_Cause
};
SzMsgConInf szUECntxtRlsRqst_IEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   3,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueUECntxtRlsRqst_IEsClsInfo =
{
   3,
   &sz_ValueUECntxtRlsRqst_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECntxtRlsRqst_IEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueUECntxtRlsRqst_IEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueUECntxtRlsRqst_IEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueUECntxtRlsRqst_IEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueUECntxtRlsRqst_IEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueUECntxtRlsRqst_IEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueUECntxtRlsRqst_IEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_UECntxtRlsRqst_IEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueUECntxtRlsRqst_IEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECntxtRlsRqst_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_UECntxtRlsRqst_IEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_UECntxtRlsRqst_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_UECntxtRlsRqst_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_UECntxtRlsRqst_IEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_UECntxtRlsRqst_IEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_UECntxtRlsRqst_IEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_UECntxtRlsRqst_IEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_UECntxtRlsRqst_IEs *protIe = NULLP;
   SztProtIE_Field_UECntxtRlsRqst_IEs *member = NULLP;
   
   TRC2(szProtIE_Cont_UECntxtRlsRqst_IEsValidate);
   
   protIe = (SztProtIE_Cont_UECntxtRlsRqst_IEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_UECntxtRlsRqst_IEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szUECntxtRlsRqst_IEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECntxtRlsRqst_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_UECntxtRlsRqst_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_UECntxtRlsRqst_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_UECntxtRlsRqst_IEs),
   &flagSz3M,
   szProtIE_Cont_UECntxtRlsRqst_IEsValidate,
   (U8 *) (&szProtIE_Cont_UECntxtRlsRqst_IEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUECntxtRlsRqstTkn[] =
{
   &szProtIE_Cont_UECntxtRlsRqst_IEs,
      &szProtIE_Field_UECntxtRlsRqst_IEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szUECntxtRlsRqstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUECntxtRlsRqstTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUECntxtRlsRqst =
{
#ifdef CM_PASN_DBG
   " szUECntxtRlsRqst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUECntxtRlsRqst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUECntxtRlsRqstspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueUECntxtRlsCmmd_IEsClsInst[] =
{
   &szUE_S1AP_IDs,
   &szCause
};
PUBLIC U32 sz_ValueUECntxtRlsCmmd_IEsClsInstId[] =
{
   Sztid_UE_S1AP_IDs,
   Sztid_Cause
};
SzMsgConInf szUECntxtRlsCmmd_IEsConInf =
{
   {
      { Sztid_UE_S1AP_IDs, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   2,
   2
}; 
PUBLIC CmPAsnClassInfo sz_ValueUECntxtRlsCmmd_IEsClsInfo =
{
   2,
   &sz_ValueUECntxtRlsCmmd_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECntxtRlsCmmd_IEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueUECntxtRlsCmmd_IEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueUECntxtRlsCmmd_IEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueUECntxtRlsCmmd_IEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueUECntxtRlsCmmd_IEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueUECntxtRlsCmmd_IEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueUECntxtRlsCmmd_IEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_UECntxtRlsCmmd_IEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueUECntxtRlsCmmd_IEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECntxtRlsCmmd_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_UECntxtRlsCmmd_IEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_UECntxtRlsCmmd_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_UECntxtRlsCmmd_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_UECntxtRlsCmmd_IEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_UECntxtRlsCmmd_IEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_UECntxtRlsCmmd_IEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_UECntxtRlsCmmd_IEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_UECntxtRlsCmmd_IEs *protIe = NULLP;
   SztProtIE_Field_UECntxtRlsCmmd_IEs *member = NULLP;
   
   TRC2(szProtIE_Cont_UECntxtRlsCmmd_IEsValidate);
   
   protIe = (SztProtIE_Cont_UECntxtRlsCmmd_IEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_UECntxtRlsCmmd_IEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szUECntxtRlsCmmd_IEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECntxtRlsCmmd_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_UECntxtRlsCmmd_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_UECntxtRlsCmmd_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_UECntxtRlsCmmd_IEs),
   &flagSz3M,
   szProtIE_Cont_UECntxtRlsCmmd_IEsValidate,
   (U8 *) (&szProtIE_Cont_UECntxtRlsCmmd_IEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUECntxtRlsCmmdTkn[] =
{
   &szProtIE_Cont_UECntxtRlsCmmd_IEs,
      &szProtIE_Field_UECntxtRlsCmmd_IEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szUECntxtRlsCmmdspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUECntxtRlsCmmdTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUECntxtRlsCmmd =
{
#ifdef CM_PASN_DBG
   " szUECntxtRlsCmmd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUECntxtRlsCmmd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUECntxtRlsCmmdspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueUECntxtRlsComplete_IEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueUECntxtRlsComplete_IEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_CriticalityDiag
};
SzMsgConInf szUECntxtRlsComplete_IEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   3,
   2
}; 
PUBLIC CmPAsnClassInfo sz_ValueUECntxtRlsComplete_IEsClsInfo =
{
   3,
   &sz_ValueUECntxtRlsComplete_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECntxtRlsComplete_IEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueUECntxtRlsComplete_IEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueUECntxtRlsComplete_IEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueUECntxtRlsComplete_IEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueUECntxtRlsComplete_IEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueUECntxtRlsComplete_IEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueUECntxtRlsComplete_IEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_UECntxtRlsComplete_IEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueUECntxtRlsComplete_IEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECntxtRlsComplete_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_UECntxtRlsComplete_IEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_UECntxtRlsComplete_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_UECntxtRlsComplete_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_UECntxtRlsComplete_IEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_UECntxtRlsComplete_IEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_UECntxtRlsComplete_IEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_UECntxtRlsComplete_IEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_UECntxtRlsComplete_IEs *protIe = NULLP;
   SztProtIE_Field_UECntxtRlsComplete_IEs *member = NULLP;
   
   TRC2(szProtIE_Cont_UECntxtRlsComplete_IEsValidate);
   
   protIe = (SztProtIE_Cont_UECntxtRlsComplete_IEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_UECntxtRlsComplete_IEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szUECntxtRlsComplete_IEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECntxtRlsComplete_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_UECntxtRlsComplete_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_UECntxtRlsComplete_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_UECntxtRlsComplete_IEs),
   &flagSz3M,
   szProtIE_Cont_UECntxtRlsComplete_IEsValidate,
   (U8 *) (&szProtIE_Cont_UECntxtRlsComplete_IEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUECntxtRlsCompleteTkn[] =
{
   &szProtIE_Cont_UECntxtRlsComplete_IEs,
      &szProtIE_Field_UECntxtRlsComplete_IEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szUECntxtRlsCompletespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUECntxtRlsCompleteTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUECntxtRlsComplete =
{
#ifdef CM_PASN_DBG
   " szUECntxtRlsComplete ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUECntxtRlsComplete),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUECntxtRlsCompletespec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueUECntxtModificationRqstIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szSecurKey,
   &szSubscriberProfileIDforRFP,
   &szUEAggMaxBitrate,
   &szCSFallbackIndicator
};
PUBLIC U32 sz_ValueUECntxtModificationRqstIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_SecurKey,
   Sztid_SubscriberProfileIDforRFP,
   Sztid_uEaggregateMaxBitrate,
   Sztid_CSFallbackIndicator
};
SzMsgConInf szUECntxtModificationRqstIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_SecurKey, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_SubscriberProfileIDforRFP, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_uEaggregateMaxBitrate, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_CSFallbackIndicator, SZ_CRIT_REJECT, CM_PASN_ELM_OPT }
   },
   6,
   2
}; 
PUBLIC CmPAsnClassInfo sz_ValueUECntxtModificationRqstIEsClsInfo =
{
   6,
   &sz_ValueUECntxtModificationRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECntxtModificationRqstIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueUECntxtModificationRqstIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueUECntxtModificationRqstIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueUECntxtModificationRqstIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueUECntxtModificationRqstIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueUECntxtModificationRqstIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueUECntxtModificationRqstIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_UECntxtModificationRqstIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueUECntxtModificationRqstIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECntxtModificationRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_UECntxtModificationRqstIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_UECntxtModificationRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_UECntxtModificationRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_UECntxtModificationRqstIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_UECntxtModificationRqstIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_UECntxtModificationRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_UECntxtModificationRqstIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_UECntxtModificationRqstIEs *protIe = NULLP;
   SztProtIE_Field_UECntxtModificationRqstIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_UECntxtModificationRqstIEsValidate);
   
   protIe = (SztProtIE_Cont_UECntxtModificationRqstIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_UECntxtModificationRqstIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szUECntxtModificationRqstIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECntxtModificationRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_UECntxtModificationRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_UECntxtModificationRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_UECntxtModificationRqstIEs),
   &flagSz3M,
   szProtIE_Cont_UECntxtModificationRqstIEsValidate,
   (U8 *) (&szProtIE_Cont_UECntxtModificationRqstIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUECntxtModificationRqstTkn[] =
{
   &szProtIE_Cont_UECntxtModificationRqstIEs,
      &szProtIE_Field_UECntxtModificationRqstIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szUECntxtModificationRqstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUECntxtModificationRqstTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUECntxtModificationRqst =
{
#ifdef CM_PASN_DBG
   " szUECntxtModificationRqst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUECntxtModificationRqst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUECntxtModificationRqstspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueUECntxtModificationRespIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueUECntxtModificationRespIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_CriticalityDiag
};
SzMsgConInf szUECntxtModificationRespIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   3,
   2
}; 
PUBLIC CmPAsnClassInfo sz_ValueUECntxtModificationRespIEsClsInfo =
{
   3,
   &sz_ValueUECntxtModificationRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECntxtModificationRespIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueUECntxtModificationRespIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueUECntxtModificationRespIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueUECntxtModificationRespIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueUECntxtModificationRespIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueUECntxtModificationRespIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueUECntxtModificationRespIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_UECntxtModificationRespIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueUECntxtModificationRespIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECntxtModificationRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_UECntxtModificationRespIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_UECntxtModificationRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_UECntxtModificationRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_UECntxtModificationRespIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_UECntxtModificationRespIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_UECntxtModificationRespIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_UECntxtModificationRespIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_UECntxtModificationRespIEs *protIe = NULLP;
   SztProtIE_Field_UECntxtModificationRespIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_UECntxtModificationRespIEsValidate);
   
   protIe = (SztProtIE_Cont_UECntxtModificationRespIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_UECntxtModificationRespIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szUECntxtModificationRespIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECntxtModificationRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_UECntxtModificationRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_UECntxtModificationRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_UECntxtModificationRespIEs),
   &flagSz3M,
   szProtIE_Cont_UECntxtModificationRespIEsValidate,
   (U8 *) (&szProtIE_Cont_UECntxtModificationRespIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUECntxtModificationRespTkn[] =
{
   &szProtIE_Cont_UECntxtModificationRespIEs,
      &szProtIE_Field_UECntxtModificationRespIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szUECntxtModificationRespspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUECntxtModificationRespTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUECntxtModificationResp =
{
#ifdef CM_PASN_DBG
   " szUECntxtModificationResp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUECntxtModificationResp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUECntxtModificationRespspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueUECntxtModificationFailIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szCause,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueUECntxtModificationFailIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_Cause,
   Sztid_CriticalityDiag
};
SzMsgConInf szUECntxtModificationFailIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   4,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueUECntxtModificationFailIEsClsInfo =
{
   4,
   &sz_ValueUECntxtModificationFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECntxtModificationFailIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueUECntxtModificationFailIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueUECntxtModificationFailIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueUECntxtModificationFailIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueUECntxtModificationFailIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueUECntxtModificationFailIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueUECntxtModificationFailIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_UECntxtModificationFailIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueUECntxtModificationFailIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECntxtModificationFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_UECntxtModificationFailIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_UECntxtModificationFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_UECntxtModificationFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_UECntxtModificationFailIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_UECntxtModificationFailIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_UECntxtModificationFailIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_UECntxtModificationFailIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_UECntxtModificationFailIEs *protIe = NULLP;
   SztProtIE_Field_UECntxtModificationFailIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_UECntxtModificationFailIEsValidate);
   
   protIe = (SztProtIE_Cont_UECntxtModificationFailIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_UECntxtModificationFailIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szUECntxtModificationFailIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECntxtModificationFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_UECntxtModificationFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_UECntxtModificationFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_UECntxtModificationFailIEs),
   &flagSz3M,
   szProtIE_Cont_UECntxtModificationFailIEsValidate,
   (U8 *) (&szProtIE_Cont_UECntxtModificationFailIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUECntxtModificationFailTkn[] =
{
   &szProtIE_Cont_UECntxtModificationFailIEs,
      &szProtIE_Field_UECntxtModificationFailIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szUECntxtModificationFailspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUECntxtModificationFailTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUECntxtModificationFail =
{
#ifdef CM_PASN_DBG
   " szUECntxtModificationFail ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUECntxtModificationFail),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUECntxtModificationFailspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueDlnkNASTport_IEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szNAS_PDU,
   &szHovrRestrnLst
};
PUBLIC U32 sz_ValueDlnkNASTport_IEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_NAS_PDU,
   Sztid_HovrRestrnLst
};
SzMsgConInf szDlnkNASTport_IEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_NAS_PDU, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_HovrRestrnLst, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   4,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueDlnkNASTport_IEsClsInfo =
{
   4,
   &sz_ValueDlnkNASTport_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueDlnkNASTport_IEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueDlnkNASTport_IEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueDlnkNASTport_IEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueDlnkNASTport_IEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueDlnkNASTport_IEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueDlnkNASTport_IEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueDlnkNASTport_IEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_DlnkNASTport_IEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueDlnkNASTport_IEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_DlnkNASTport_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_DlnkNASTport_IEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_DlnkNASTport_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_DlnkNASTport_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_DlnkNASTport_IEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_DlnkNASTport_IEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_DlnkNASTport_IEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_DlnkNASTport_IEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_DlnkNASTport_IEs *protIe = NULLP;
   SztProtIE_Field_DlnkNASTport_IEs *member = NULLP;
   
   TRC2(szProtIE_Cont_DlnkNASTport_IEsValidate);
   
   protIe = (SztProtIE_Cont_DlnkNASTport_IEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_DlnkNASTport_IEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szDlnkNASTport_IEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_DlnkNASTport_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_DlnkNASTport_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_DlnkNASTport_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_DlnkNASTport_IEs),
   &flagSz3M,
   szProtIE_Cont_DlnkNASTport_IEsValidate,
   (U8 *) (&szProtIE_Cont_DlnkNASTport_IEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szDlnkNASTportTkn[] =
{
   &szProtIE_Cont_DlnkNASTport_IEs,
      &szProtIE_Field_DlnkNASTport_IEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szDlnkNASTportspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szDlnkNASTportTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szDlnkNASTport =
{
#ifdef CM_PASN_DBG
   " szDlnkNASTport ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztDlnkNASTport),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szDlnkNASTportspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueInitUEMsg_IEsClsInst[] =
{
   &szENB_UE_S1AP_ID,
   &szNAS_PDU,
   &szTAI,
   &szEUTRAN_CGI,
   &szRRC_Establishment_Cause,
   &szS_TMSI,
   &szCSG_Id,
   &szGUMMEI
};
PUBLIC U32 sz_ValueInitUEMsg_IEsClsInstId[] =
{
   Sztid_eNB_UE_S1AP_ID,
   Sztid_NAS_PDU,
   Sztid_TAI,
   Sztid_EUTRAN_CGI,
   Sztid_RRC_Establishment_Cause,
   Sztid_S_TMSI,
   Sztid_CSG_Id,
   Sztid_GUMMEI_ID
};
SzMsgConInf szInitUEMsg_IEsConInf =
{
   {
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_NAS_PDU, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_TAI, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_EUTRAN_CGI, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_RRC_Establishment_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_S_TMSI, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_CSG_Id, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_GUMMEI_ID, SZ_CRIT_REJECT, CM_PASN_ELM_OPT }
   },
   8,
   5
}; 
PUBLIC CmPAsnClassInfo sz_ValueInitUEMsg_IEsClsInfo =
{
   8,
   &sz_ValueInitUEMsg_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueInitUEMsg_IEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueInitUEMsg_IEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueInitUEMsg_IEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueInitUEMsg_IEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueInitUEMsg_IEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueInitUEMsg_IEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueInitUEMsg_IEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_InitUEMsg_IEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueInitUEMsg_IEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_InitUEMsg_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_InitUEMsg_IEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_InitUEMsg_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_InitUEMsg_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_InitUEMsg_IEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_InitUEMsg_IEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_InitUEMsg_IEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_InitUEMsg_IEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_InitUEMsg_IEs *protIe = NULLP;
   SztProtIE_Field_InitUEMsg_IEs *member = NULLP;
   
   TRC2(szProtIE_Cont_InitUEMsg_IEsValidate);
   
   protIe = (SztProtIE_Cont_InitUEMsg_IEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_InitUEMsg_IEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szInitUEMsg_IEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_InitUEMsg_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_InitUEMsg_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_InitUEMsg_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_InitUEMsg_IEs),
   &flagSz3M,
   szProtIE_Cont_InitUEMsg_IEsValidate,
   (U8 *) (&szProtIE_Cont_InitUEMsg_IEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szInitUEMsgTkn[] =
{
   &szProtIE_Cont_InitUEMsg_IEs,
      &szProtIE_Field_InitUEMsg_IEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szInitUEMsgspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szInitUEMsgTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szInitUEMsg =
{
#ifdef CM_PASN_DBG
   " szInitUEMsg ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztInitUEMsg),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szInitUEMsgspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueUlnkNASTport_IEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szNAS_PDU,
   &szEUTRAN_CGI,
   &szTAI
};
PUBLIC U32 sz_ValueUlnkNASTport_IEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_NAS_PDU,
   Sztid_EUTRAN_CGI,
   Sztid_TAI
};
SzMsgConInf szUlnkNASTport_IEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_NAS_PDU, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_EUTRAN_CGI, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_TAI, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   5,
   5
}; 
PUBLIC CmPAsnClassInfo sz_ValueUlnkNASTport_IEsClsInfo =
{
   5,
   &sz_ValueUlnkNASTport_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUlnkNASTport_IEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueUlnkNASTport_IEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueUlnkNASTport_IEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueUlnkNASTport_IEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueUlnkNASTport_IEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueUlnkNASTport_IEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueUlnkNASTport_IEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_UlnkNASTport_IEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueUlnkNASTport_IEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UlnkNASTport_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_UlnkNASTport_IEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_UlnkNASTport_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_UlnkNASTport_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_UlnkNASTport_IEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_UlnkNASTport_IEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_UlnkNASTport_IEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_UlnkNASTport_IEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_UlnkNASTport_IEs *protIe = NULLP;
   SztProtIE_Field_UlnkNASTport_IEs *member = NULLP;
   
   TRC2(szProtIE_Cont_UlnkNASTport_IEsValidate);
   
   protIe = (SztProtIE_Cont_UlnkNASTport_IEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_UlnkNASTport_IEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szUlnkNASTport_IEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UlnkNASTport_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_UlnkNASTport_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_UlnkNASTport_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_UlnkNASTport_IEs),
   &flagSz3M,
   szProtIE_Cont_UlnkNASTport_IEsValidate,
   (U8 *) (&szProtIE_Cont_UlnkNASTport_IEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUlnkNASTportTkn[] =
{
   &szProtIE_Cont_UlnkNASTport_IEs,
      &szProtIE_Field_UlnkNASTport_IEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szUlnkNASTportspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUlnkNASTportTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUlnkNASTport =
{
#ifdef CM_PASN_DBG
   " szUlnkNASTport ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUlnkNASTport),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUlnkNASTportspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueNASNonDlvryInd_IEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szNAS_PDU,
   &szCause
};
PUBLIC U32 sz_ValueNASNonDlvryInd_IEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_NAS_PDU,
   Sztid_Cause
};
SzMsgConInf szNASNonDlvryInd_IEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_NAS_PDU, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   4,
   4
}; 
PUBLIC CmPAsnClassInfo sz_ValueNASNonDlvryInd_IEsClsInfo =
{
   4,
   &sz_ValueNASNonDlvryInd_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueNASNonDlvryInd_IEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueNASNonDlvryInd_IEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueNASNonDlvryInd_IEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueNASNonDlvryInd_IEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueNASNonDlvryInd_IEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueNASNonDlvryInd_IEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueNASNonDlvryInd_IEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_NASNonDlvryInd_IEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueNASNonDlvryInd_IEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_NASNonDlvryInd_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_NASNonDlvryInd_IEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_NASNonDlvryInd_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_NASNonDlvryInd_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_NASNonDlvryInd_IEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_NASNonDlvryInd_IEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_NASNonDlvryInd_IEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_NASNonDlvryInd_IEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_NASNonDlvryInd_IEs *protIe = NULLP;
   SztProtIE_Field_NASNonDlvryInd_IEs *member = NULLP;
   
   TRC2(szProtIE_Cont_NASNonDlvryInd_IEsValidate);
   
   protIe = (SztProtIE_Cont_NASNonDlvryInd_IEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_NASNonDlvryInd_IEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szNASNonDlvryInd_IEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_NASNonDlvryInd_IEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_NASNonDlvryInd_IEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_NASNonDlvryInd_IEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_NASNonDlvryInd_IEs),
   &flagSz3M,
   szProtIE_Cont_NASNonDlvryInd_IEsValidate,
   (U8 *) (&szProtIE_Cont_NASNonDlvryInd_IEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szNASNonDlvryIndTkn[] =
{
   &szProtIE_Cont_NASNonDlvryInd_IEs,
      &szProtIE_Field_NASNonDlvryInd_IEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szNASNonDlvryIndspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szNASNonDlvryIndTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szNASNonDlvryInd =
{
#ifdef CM_PASN_DBG
   " szNASNonDlvryInd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztNASNonDlvryInd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szNASNonDlvryIndspec),
   NULLP
};
/* Element ----- ResetAll ------- */
CmPAsnTknEnum szResetAllLst[2] =
{
   1,
   SztResetAllreset_allEnum
};
CmPAsnEnumDef szResetAllspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   szResetAllLst,
   NULLP
};
CmPAsnElmDef szResetAll =
{
#ifdef CM_PASN_DBG
   " szResetAll ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztResetAll),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szResetAllspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz_ValueUE_assocLogS1_ConItemResClsInst[] =
{
   &szUE_assocLogS1_ConItem
};
PUBLIC U32 sz_ValueUE_assocLogS1_ConItemResClsInstId[] =
{
   Sztid_UE_assocLogS1_ConItem
};
SzMsgConInf szUE_assocLogS1_ConItemResConInf =
{
   {
      { Sztid_UE_assocLogS1_ConItem, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueUE_assocLogS1_ConItemResClsInfo =
{
   1,
   &sz_ValueUE_assocLogS1_ConItemResClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUE_assocLogS1_ConItemResClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueUE_assocLogS1_ConItemResClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueUE_assocLogS1_ConItemResClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueUE_assocLogS1_ConItemResCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueUE_assocLogS1_ConItemResCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueUE_assocLogS1_ConItemResCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueUE_assocLogS1_ConItemResClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_UE_assocLogS1_ConItemResTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueUE_assocLogS1_ConItemResCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UE_assocLogS1_ConItemResspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_UE_assocLogS1_ConItemResTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_UE_assocLogS1_ConItemRes =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_UE_assocLogS1_ConItemRes ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_UE_assocLogS1_ConItemRes),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_UE_assocLogS1_ConItemResspec),
   NULLP
};
#define szProtIE_SingleCont_UE_assocLogS1_ConItemRes szProtIE_Field_UE_assocLogS1_ConItemRes
CmPAsnSetSeqOfDef szUE_assocLogS1_ConLstResspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfIvdualS1ConsToReset,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szUE_assocLogS1_ConLstRes =
{
#ifdef CM_PASN_DBG
   " szUE_assocLogS1_ConLstRes ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztUE_assocLogS1_ConLstRes),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szUE_assocLogS1_ConLstResspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szResetTypTkn[] =
{
   &szResetAll,
   &szUE_assocLogS1_ConLstRes,
      &szProtIE_Field_UE_assocLogS1_ConItemRes,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szResetTypspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   2,
   0,
   &szResetTypTkn[0]  /* Token List */
};
CmPAsnElmDef szResetTyp =
{
#ifdef CM_PASN_DBG
   " szResetTyp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztResetTyp),
   &flagSz3M,
   NULLP,
   (U8 *)(&szResetTypspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueResetIEsClsInst[] =
{
   &szCause,
   &szResetTyp
};
PUBLIC U32 sz_ValueResetIEsClsInstId[] =
{
   Sztid_Cause,
   Sztid_ResetTyp
};
SzMsgConInf szResetIEsConInf =
{
   {
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_ResetTyp, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   2,
   2
}; 
PUBLIC CmPAsnClassInfo sz_ValueResetIEsClsInfo =
{
   2,
   &sz_ValueResetIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueResetIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueResetIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueResetIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueResetIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueResetIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueResetIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueResetIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_ResetIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueResetIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ResetIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_ResetIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_ResetIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_ResetIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_ResetIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_ResetIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_ResetIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_ResetIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_ResetIEs *protIe = NULLP;
   SztProtIE_Field_ResetIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_ResetIEsValidate);
   
   protIe = (SztProtIE_Cont_ResetIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_ResetIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szResetIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ResetIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_ResetIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_ResetIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_ResetIEs),
   &flagSz3M,
   szProtIE_Cont_ResetIEsValidate,
   (U8 *) (&szProtIE_Cont_ResetIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szResetTkn[] =
{
   &szProtIE_Cont_ResetIEs,
      &szProtIE_Field_ResetIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szResetspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szResetTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szReset =
{
#ifdef CM_PASN_DBG
   " szReset ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztReset),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szResetspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueUE_assocLogS1_ConItemResAckClsInst[] =
{
   &szUE_assocLogS1_ConItem
};
PUBLIC U32 sz_ValueUE_assocLogS1_ConItemResAckClsInstId[] =
{
   Sztid_UE_assocLogS1_ConItem
};
SzMsgConInf szUE_assocLogS1_ConItemResAckConInf =
{
   {
      { Sztid_UE_assocLogS1_ConItem, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueUE_assocLogS1_ConItemResAckClsInfo =
{
   1,
   &sz_ValueUE_assocLogS1_ConItemResAckClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUE_assocLogS1_ConItemResAckClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueUE_assocLogS1_ConItemResAckClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueUE_assocLogS1_ConItemResAckClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueUE_assocLogS1_ConItemResAckCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueUE_assocLogS1_ConItemResAckCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueUE_assocLogS1_ConItemResAckCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueUE_assocLogS1_ConItemResAckClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_UE_assocLogS1_ConItemResAckTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueUE_assocLogS1_ConItemResAckCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UE_assocLogS1_ConItemResAckspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_UE_assocLogS1_ConItemResAckTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_UE_assocLogS1_ConItemResAck =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_UE_assocLogS1_ConItemResAck ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_UE_assocLogS1_ConItemResAck),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_UE_assocLogS1_ConItemResAckspec),
   NULLP
};
#define szProtIE_SingleCont_UE_assocLogS1_ConItemResAck szProtIE_Field_UE_assocLogS1_ConItemResAck
CmPAsnSetSeqOfDef szUE_assocLogS1_ConLstResAckspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfIvdualS1ConsToReset,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szUE_assocLogS1_ConLstResAck =
{
#ifdef CM_PASN_DBG
   " szUE_assocLogS1_ConLstResAck ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztUE_assocLogS1_ConLstResAck),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&szUE_assocLogS1_ConLstResAckspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueResetAckgIEsClsInst[] =
{
   &szUE_assocLogS1_ConLstResAck,
      &szProtIE_Field_UE_assocLogS1_ConItemResAck,
      &szConstTerm,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueResetAckgIEsClsInstId[] =
{
   Sztid_UE_assocLogS1_ConLstResAck,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_CriticalityDiag
};
SzMsgConInf szResetAckgIEsConInf =
{
   {
      { Sztid_UE_assocLogS1_ConLstResAck, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   2,
   0
}; 
PUBLIC CmPAsnClassInfo sz_ValueResetAckgIEsClsInfo =
{
   4,
   &sz_ValueResetAckgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueResetAckgIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueResetAckgIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueResetAckgIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueResetAckgIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueResetAckgIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueResetAckgIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueResetAckgIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_ResetAckgIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueResetAckgIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ResetAckgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_ResetAckgIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_ResetAckgIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_ResetAckgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_ResetAckgIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_ResetAckgIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_ResetAckgIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_ResetAckgIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_ResetAckgIEs *protIe = NULLP;
   SztProtIE_Field_ResetAckgIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_ResetAckgIEsValidate);
   
   protIe = (SztProtIE_Cont_ResetAckgIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_ResetAckgIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szResetAckgIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ResetAckgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_ResetAckgIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_ResetAckgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_ResetAckgIEs),
   &flagSz3M,
   szProtIE_Cont_ResetAckgIEsValidate,
   (U8 *) (&szProtIE_Cont_ResetAckgIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szResetAckgTkn[] =
{
   &szProtIE_Cont_ResetAckgIEs,
      &szProtIE_Field_ResetAckgIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szResetAckgspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szResetAckgTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szResetAckg =
{
#ifdef CM_PASN_DBG
   " szResetAckg ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztResetAckg),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szResetAckgspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueErrIndIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szCause,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueErrIndIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_Cause,
   Sztid_CriticalityDiag
};
SzMsgConInf szErrIndIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   4,
   0
}; 
PUBLIC CmPAsnClassInfo sz_ValueErrIndIEsClsInfo =
{
   4,
   &sz_ValueErrIndIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueErrIndIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueErrIndIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueErrIndIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueErrIndIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueErrIndIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueErrIndIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueErrIndIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_ErrIndIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueErrIndIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ErrIndIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_ErrIndIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_ErrIndIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_ErrIndIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_ErrIndIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_ErrIndIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_ErrIndIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_ErrIndIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_ErrIndIEs *protIe = NULLP;
   SztProtIE_Field_ErrIndIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_ErrIndIEsValidate);
   
   protIe = (SztProtIE_Cont_ErrIndIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_ErrIndIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szErrIndIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ErrIndIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_ErrIndIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_ErrIndIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_ErrIndIEs),
   &flagSz3M,
   szProtIE_Cont_ErrIndIEsValidate,
   (U8 *) (&szProtIE_Cont_ErrIndIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szErrIndTkn[] =
{
   &szProtIE_Cont_ErrIndIEs,
      &szProtIE_Field_ErrIndIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szErrIndspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szErrIndTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szErrInd =
{
#ifdef CM_PASN_DBG
   " szErrInd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztErrInd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szErrIndspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueS1SetupRqstIEsClsInst[] =
{
   &szGlobal_ENB_ID,
   &szENBname,
   &szSuppTAs,
      &szSuppTAs_Item,
      &szConstTerm,
   &szPagDRX,
   &szCSG_IdLst,
      &szCSG_IdLst_Item,
      &szConstTerm,
   
};
PUBLIC U32 sz_ValueS1SetupRqstIEsClsInstId[] =
{
   Sztid_Global_ENB_ID,
   Sztid_eNBname,
   Sztid_SuppTAs,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_DefaultPagDRX,
   Sztid_CSG_IdLst,
      Sztid_Invalid,
      Sztid_Invalid
};
SzMsgConInf szS1SetupRqstIEsConInf =
{
   {
      { Sztid_Global_ENB_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNBname, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_SuppTAs, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_DefaultPagDRX, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_CSG_IdLst, SZ_CRIT_REJECT, CM_PASN_ELM_OPT }
   },
   5,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueS1SetupRqstIEsClsInfo =
{
   9,
   &sz_ValueS1SetupRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueS1SetupRqstIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueS1SetupRqstIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueS1SetupRqstIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueS1SetupRqstIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueS1SetupRqstIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueS1SetupRqstIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueS1SetupRqstIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_S1SetupRqstIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueS1SetupRqstIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_S1SetupRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_S1SetupRqstIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_S1SetupRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_S1SetupRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_S1SetupRqstIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_S1SetupRqstIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_S1SetupRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_S1SetupRqstIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_S1SetupRqstIEs *protIe = NULLP;
   SztProtIE_Field_S1SetupRqstIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_S1SetupRqstIEsValidate);
   
   protIe = (SztProtIE_Cont_S1SetupRqstIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_S1SetupRqstIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szS1SetupRqstIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_S1SetupRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_S1SetupRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_S1SetupRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_S1SetupRqstIEs),
   &flagSz3M,
   szProtIE_Cont_S1SetupRqstIEsValidate,
   (U8 *) (&szProtIE_Cont_S1SetupRqstIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szS1SetupRqstTkn[] =
{
   &szProtIE_Cont_S1SetupRqstIEs,
      &szProtIE_Field_S1SetupRqstIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szS1SetupRqstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szS1SetupRqstTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szS1SetupRqst =
{
#ifdef CM_PASN_DBG
   " szS1SetupRqst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztS1SetupRqst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szS1SetupRqstspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueS1SetupRespIEsClsInst[] =
{
   &szMMEname,
   &szSrvdGUMMEIs,
      &szSrvdGUMMEIsItem,
      &szConstTerm,
   &szRelativeMMECapacity,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueS1SetupRespIEsClsInstId[] =
{
   Sztid_MMEname,
   Sztid_SrvdGUMMEIs,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_RelativeMMECapacity,
   Sztid_CriticalityDiag
};
SzMsgConInf szS1SetupRespIEsConInf =
{
   {
      { Sztid_MMEname, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_SrvdGUMMEIs, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_RelativeMMECapacity, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   4,
   2
}; 
PUBLIC CmPAsnClassInfo sz_ValueS1SetupRespIEsClsInfo =
{
   6,
   &sz_ValueS1SetupRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueS1SetupRespIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueS1SetupRespIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueS1SetupRespIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueS1SetupRespIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueS1SetupRespIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueS1SetupRespIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueS1SetupRespIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_S1SetupRespIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueS1SetupRespIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_S1SetupRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_S1SetupRespIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_S1SetupRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_S1SetupRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_S1SetupRespIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_S1SetupRespIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_S1SetupRespIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_S1SetupRespIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_S1SetupRespIEs *protIe = NULLP;
   SztProtIE_Field_S1SetupRespIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_S1SetupRespIEsValidate);
   
   protIe = (SztProtIE_Cont_S1SetupRespIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_S1SetupRespIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szS1SetupRespIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_S1SetupRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_S1SetupRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_S1SetupRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_S1SetupRespIEs),
   &flagSz3M,
   szProtIE_Cont_S1SetupRespIEsValidate,
   (U8 *) (&szProtIE_Cont_S1SetupRespIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szS1SetupRespTkn[] =
{
   &szProtIE_Cont_S1SetupRespIEs,
      &szProtIE_Field_S1SetupRespIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szS1SetupRespspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szS1SetupRespTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szS1SetupResp =
{
#ifdef CM_PASN_DBG
   " szS1SetupResp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztS1SetupResp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szS1SetupRespspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueS1SetupFailIEsClsInst[] =
{
   &szCause,
   &szTimeToWait,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueS1SetupFailIEsClsInstId[] =
{
   Sztid_Cause,
   Sztid_TimeToWait,
   Sztid_CriticalityDiag
};
SzMsgConInf szS1SetupFailIEsConInf =
{
   {
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_TimeToWait, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   3,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueS1SetupFailIEsClsInfo =
{
   3,
   &sz_ValueS1SetupFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueS1SetupFailIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueS1SetupFailIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueS1SetupFailIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueS1SetupFailIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueS1SetupFailIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueS1SetupFailIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueS1SetupFailIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_S1SetupFailIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueS1SetupFailIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_S1SetupFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_S1SetupFailIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_S1SetupFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_S1SetupFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_S1SetupFailIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_S1SetupFailIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_S1SetupFailIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_S1SetupFailIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_S1SetupFailIEs *protIe = NULLP;
   SztProtIE_Field_S1SetupFailIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_S1SetupFailIEsValidate);
   
   protIe = (SztProtIE_Cont_S1SetupFailIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_S1SetupFailIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szS1SetupFailIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_S1SetupFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_S1SetupFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_S1SetupFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_S1SetupFailIEs),
   &flagSz3M,
   szProtIE_Cont_S1SetupFailIEsValidate,
   (U8 *) (&szProtIE_Cont_S1SetupFailIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szS1SetupFailTkn[] =
{
   &szProtIE_Cont_S1SetupFailIEs,
      &szProtIE_Field_S1SetupFailIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szS1SetupFailspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szS1SetupFailTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szS1SetupFail =
{
#ifdef CM_PASN_DBG
   " szS1SetupFail ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztS1SetupFail),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szS1SetupFailspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueENBConfigUpdIEsClsInst[] =
{
   &szENBname,
   &szSuppTAs,
      &szSuppTAs_Item,
      &szConstTerm,
   &szCSG_IdLst,
      &szCSG_IdLst_Item,
      &szConstTerm,
   &szPagDRX
};
PUBLIC U32 sz_ValueENBConfigUpdIEsClsInstId[] =
{
   Sztid_eNBname,
   Sztid_SuppTAs,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_CSG_IdLst,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_DefaultPagDRX
};
SzMsgConInf szENBConfigUpdIEsConInf =
{
   {
      { Sztid_eNBname, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_SuppTAs, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_CSG_IdLst, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_DefaultPagDRX, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   4,
   0
}; 
PUBLIC CmPAsnClassInfo sz_ValueENBConfigUpdIEsClsInfo =
{
   8,
   &sz_ValueENBConfigUpdIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueENBConfigUpdIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueENBConfigUpdIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueENBConfigUpdIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueENBConfigUpdIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueENBConfigUpdIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueENBConfigUpdIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueENBConfigUpdIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_ENBConfigUpdIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueENBConfigUpdIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ENBConfigUpdIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_ENBConfigUpdIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_ENBConfigUpdIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_ENBConfigUpdIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_ENBConfigUpdIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_ENBConfigUpdIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_ENBConfigUpdIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_ENBConfigUpdIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_ENBConfigUpdIEs *protIe = NULLP;
   SztProtIE_Field_ENBConfigUpdIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_ENBConfigUpdIEsValidate);
   
   protIe = (SztProtIE_Cont_ENBConfigUpdIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_ENBConfigUpdIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szENBConfigUpdIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ENBConfigUpdIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_ENBConfigUpdIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_ENBConfigUpdIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_ENBConfigUpdIEs),
   &flagSz3M,
   szProtIE_Cont_ENBConfigUpdIEsValidate,
   (U8 *) (&szProtIE_Cont_ENBConfigUpdIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szENBConfigUpdTkn[] =
{
   &szProtIE_Cont_ENBConfigUpdIEs,
      &szProtIE_Field_ENBConfigUpdIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szENBConfigUpdspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szENBConfigUpdTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szENBConfigUpd =
{
#ifdef CM_PASN_DBG
   " szENBConfigUpd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztENBConfigUpd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szENBConfigUpdspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueENBConfigUpdAckgIEsClsInst[] =
{
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueENBConfigUpdAckgIEsClsInstId[] =
{
   Sztid_CriticalityDiag
};
SzMsgConInf szENBConfigUpdAckgIEsConInf =
{
   {
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   1,
   0
}; 
PUBLIC CmPAsnClassInfo sz_ValueENBConfigUpdAckgIEsClsInfo =
{
   1,
   &sz_ValueENBConfigUpdAckgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueENBConfigUpdAckgIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueENBConfigUpdAckgIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueENBConfigUpdAckgIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueENBConfigUpdAckgIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueENBConfigUpdAckgIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueENBConfigUpdAckgIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueENBConfigUpdAckgIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_ENBConfigUpdAckgIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueENBConfigUpdAckgIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ENBConfigUpdAckgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_ENBConfigUpdAckgIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_ENBConfigUpdAckgIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_ENBConfigUpdAckgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_ENBConfigUpdAckgIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_ENBConfigUpdAckgIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_ENBConfigUpdAckgIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_ENBConfigUpdAckgIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_ENBConfigUpdAckgIEs *protIe = NULLP;
   SztProtIE_Field_ENBConfigUpdAckgIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_ENBConfigUpdAckgIEsValidate);
   
   protIe = (SztProtIE_Cont_ENBConfigUpdAckgIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_ENBConfigUpdAckgIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szENBConfigUpdAckgIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ENBConfigUpdAckgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_ENBConfigUpdAckgIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_ENBConfigUpdAckgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_ENBConfigUpdAckgIEs),
   &flagSz3M,
   szProtIE_Cont_ENBConfigUpdAckgIEsValidate,
   (U8 *) (&szProtIE_Cont_ENBConfigUpdAckgIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szENBConfigUpdAckgTkn[] =
{
   &szProtIE_Cont_ENBConfigUpdAckgIEs,
      &szProtIE_Field_ENBConfigUpdAckgIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szENBConfigUpdAckgspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szENBConfigUpdAckgTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szENBConfigUpdAckg =
{
#ifdef CM_PASN_DBG
   " szENBConfigUpdAckg ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztENBConfigUpdAckg),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szENBConfigUpdAckgspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueENBConfigUpdFailIEsClsInst[] =
{
   &szCause,
   &szTimeToWait,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueENBConfigUpdFailIEsClsInstId[] =
{
   Sztid_Cause,
   Sztid_TimeToWait,
   Sztid_CriticalityDiag
};
SzMsgConInf szENBConfigUpdFailIEsConInf =
{
   {
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_TimeToWait, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   3,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueENBConfigUpdFailIEsClsInfo =
{
   3,
   &sz_ValueENBConfigUpdFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueENBConfigUpdFailIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueENBConfigUpdFailIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueENBConfigUpdFailIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueENBConfigUpdFailIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueENBConfigUpdFailIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueENBConfigUpdFailIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueENBConfigUpdFailIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_ENBConfigUpdFailIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueENBConfigUpdFailIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ENBConfigUpdFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_ENBConfigUpdFailIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_ENBConfigUpdFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_ENBConfigUpdFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_ENBConfigUpdFailIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_ENBConfigUpdFailIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_ENBConfigUpdFailIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_ENBConfigUpdFailIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_ENBConfigUpdFailIEs *protIe = NULLP;
   SztProtIE_Field_ENBConfigUpdFailIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_ENBConfigUpdFailIEsValidate);
   
   protIe = (SztProtIE_Cont_ENBConfigUpdFailIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_ENBConfigUpdFailIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szENBConfigUpdFailIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ENBConfigUpdFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_ENBConfigUpdFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_ENBConfigUpdFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_ENBConfigUpdFailIEs),
   &flagSz3M,
   szProtIE_Cont_ENBConfigUpdFailIEsValidate,
   (U8 *) (&szProtIE_Cont_ENBConfigUpdFailIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szENBConfigUpdFailTkn[] =
{
   &szProtIE_Cont_ENBConfigUpdFailIEs,
      &szProtIE_Field_ENBConfigUpdFailIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szENBConfigUpdFailspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szENBConfigUpdFailTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szENBConfigUpdFail =
{
#ifdef CM_PASN_DBG
   " szENBConfigUpdFail ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztENBConfigUpdFail),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szENBConfigUpdFailspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueMMEConfigUpdIEsClsInst[] =
{
   &szMMEname,
   &szSrvdGUMMEIs,
      &szSrvdGUMMEIsItem,
      &szConstTerm,
   &szRelativeMMECapacity
};
PUBLIC U32 sz_ValueMMEConfigUpdIEsClsInstId[] =
{
   Sztid_MMEname,
   Sztid_SrvdGUMMEIs,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_RelativeMMECapacity
};
SzMsgConInf szMMEConfigUpdIEsConInf =
{
   {
      { Sztid_MMEname, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_SrvdGUMMEIs, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_RelativeMMECapacity, SZ_CRIT_REJECT, CM_PASN_ELM_OPT }
   },
   3,
   0
}; 
PUBLIC CmPAsnClassInfo sz_ValueMMEConfigUpdIEsClsInfo =
{
   5,
   &sz_ValueMMEConfigUpdIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueMMEConfigUpdIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueMMEConfigUpdIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueMMEConfigUpdIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueMMEConfigUpdIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueMMEConfigUpdIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueMMEConfigUpdIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueMMEConfigUpdIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_MMEConfigUpdIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueMMEConfigUpdIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_MMEConfigUpdIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_MMEConfigUpdIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_MMEConfigUpdIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_MMEConfigUpdIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_MMEConfigUpdIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_MMEConfigUpdIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_MMEConfigUpdIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_MMEConfigUpdIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_MMEConfigUpdIEs *protIe = NULLP;
   SztProtIE_Field_MMEConfigUpdIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_MMEConfigUpdIEsValidate);
   
   protIe = (SztProtIE_Cont_MMEConfigUpdIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_MMEConfigUpdIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szMMEConfigUpdIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_MMEConfigUpdIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_MMEConfigUpdIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_MMEConfigUpdIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_MMEConfigUpdIEs),
   &flagSz3M,
   szProtIE_Cont_MMEConfigUpdIEsValidate,
   (U8 *) (&szProtIE_Cont_MMEConfigUpdIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szMMEConfigUpdTkn[] =
{
   &szProtIE_Cont_MMEConfigUpdIEs,
      &szProtIE_Field_MMEConfigUpdIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szMMEConfigUpdspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szMMEConfigUpdTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szMMEConfigUpd =
{
#ifdef CM_PASN_DBG
   " szMMEConfigUpd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztMMEConfigUpd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szMMEConfigUpdspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueMMEConfigUpdAckgIEsClsInst[] =
{
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueMMEConfigUpdAckgIEsClsInstId[] =
{
   Sztid_CriticalityDiag
};
SzMsgConInf szMMEConfigUpdAckgIEsConInf =
{
   {
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   1,
   0
}; 
PUBLIC CmPAsnClassInfo sz_ValueMMEConfigUpdAckgIEsClsInfo =
{
   1,
   &sz_ValueMMEConfigUpdAckgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueMMEConfigUpdAckgIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueMMEConfigUpdAckgIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueMMEConfigUpdAckgIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueMMEConfigUpdAckgIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueMMEConfigUpdAckgIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueMMEConfigUpdAckgIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueMMEConfigUpdAckgIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_MMEConfigUpdAckgIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueMMEConfigUpdAckgIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_MMEConfigUpdAckgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_MMEConfigUpdAckgIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_MMEConfigUpdAckgIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_MMEConfigUpdAckgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_MMEConfigUpdAckgIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_MMEConfigUpdAckgIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_MMEConfigUpdAckgIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_MMEConfigUpdAckgIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_MMEConfigUpdAckgIEs *protIe = NULLP;
   SztProtIE_Field_MMEConfigUpdAckgIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_MMEConfigUpdAckgIEsValidate);
   
   protIe = (SztProtIE_Cont_MMEConfigUpdAckgIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_MMEConfigUpdAckgIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szMMEConfigUpdAckgIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_MMEConfigUpdAckgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_MMEConfigUpdAckgIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_MMEConfigUpdAckgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_MMEConfigUpdAckgIEs),
   &flagSz3M,
   szProtIE_Cont_MMEConfigUpdAckgIEsValidate,
   (U8 *) (&szProtIE_Cont_MMEConfigUpdAckgIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szMMEConfigUpdAckgTkn[] =
{
   &szProtIE_Cont_MMEConfigUpdAckgIEs,
      &szProtIE_Field_MMEConfigUpdAckgIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szMMEConfigUpdAckgspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szMMEConfigUpdAckgTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szMMEConfigUpdAckg =
{
#ifdef CM_PASN_DBG
   " szMMEConfigUpdAckg ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztMMEConfigUpdAckg),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szMMEConfigUpdAckgspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueMMEConfigUpdFailIEsClsInst[] =
{
   &szCause,
   &szTimeToWait,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueMMEConfigUpdFailIEsClsInstId[] =
{
   Sztid_Cause,
   Sztid_TimeToWait,
   Sztid_CriticalityDiag
};
SzMsgConInf szMMEConfigUpdFailIEsConInf =
{
   {
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_TimeToWait, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   3,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueMMEConfigUpdFailIEsClsInfo =
{
   3,
   &sz_ValueMMEConfigUpdFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueMMEConfigUpdFailIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueMMEConfigUpdFailIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueMMEConfigUpdFailIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueMMEConfigUpdFailIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueMMEConfigUpdFailIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueMMEConfigUpdFailIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueMMEConfigUpdFailIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_MMEConfigUpdFailIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueMMEConfigUpdFailIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_MMEConfigUpdFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_MMEConfigUpdFailIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_MMEConfigUpdFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_MMEConfigUpdFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_MMEConfigUpdFailIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_MMEConfigUpdFailIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_MMEConfigUpdFailIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_MMEConfigUpdFailIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_MMEConfigUpdFailIEs *protIe = NULLP;
   SztProtIE_Field_MMEConfigUpdFailIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_MMEConfigUpdFailIEsValidate);
   
   protIe = (SztProtIE_Cont_MMEConfigUpdFailIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_MMEConfigUpdFailIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szMMEConfigUpdFailIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_MMEConfigUpdFailIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_MMEConfigUpdFailIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_MMEConfigUpdFailIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_MMEConfigUpdFailIEs),
   &flagSz3M,
   szProtIE_Cont_MMEConfigUpdFailIEsValidate,
   (U8 *) (&szProtIE_Cont_MMEConfigUpdFailIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szMMEConfigUpdFailTkn[] =
{
   &szProtIE_Cont_MMEConfigUpdFailIEs,
      &szProtIE_Field_MMEConfigUpdFailIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szMMEConfigUpdFailspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szMMEConfigUpdFailTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szMMEConfigUpdFail =
{
#ifdef CM_PASN_DBG
   " szMMEConfigUpdFail ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztMMEConfigUpdFail),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szMMEConfigUpdFailspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueDlnkS1cdma2000tunnelingIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szProtIE_ContLst_E_RABDataFwdingItemIEs,
      &szProtIE_SingleCont_E_RABDataFwdingItemIEs,
      &szConstTerm,
   &szCdma2000HOStatus,
   &szCdma2000RATTyp,
   &szCdma2000PDU
};
PUBLIC U32 sz_ValueDlnkS1cdma2000tunnelingIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_E_RABSubjtoDataFwdingLst,
      Sztid_Invalid,
      Sztid_Invalid,
   Sztid_cdma2000HOStatus,
   Sztid_cdma2000RATTyp,
   Sztid_cdma2000PDU
};
SzMsgConInf szDlnkS1cdma2000tunnelingIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_E_RABSubjtoDataFwdingLst, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_cdma2000HOStatus, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_cdma2000RATTyp, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_cdma2000PDU, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   6,
   4
}; 
PUBLIC CmPAsnClassInfo sz_ValueDlnkS1cdma2000tunnelingIEsClsInfo =
{
   8,
   &sz_ValueDlnkS1cdma2000tunnelingIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueDlnkS1cdma2000tunnelingIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueDlnkS1cdma2000tunnelingIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueDlnkS1cdma2000tunnelingIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueDlnkS1cdma2000tunnelingIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueDlnkS1cdma2000tunnelingIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueDlnkS1cdma2000tunnelingIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueDlnkS1cdma2000tunnelingIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_DlnkS1cdma2000tunnelingIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueDlnkS1cdma2000tunnelingIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_DlnkS1cdma2000tunnelingIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_DlnkS1cdma2000tunnelingIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_DlnkS1cdma2000tunnelingIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_DlnkS1cdma2000tunnelingIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_DlnkS1cdma2000tunnelingIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_DlnkS1cdma2000tunnelingIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_DlnkS1cdma2000tunnelingIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_DlnkS1cdma2000tunnelingIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs *protIe = NULLP;
   SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_DlnkS1cdma2000tunnelingIEsValidate);
   
   protIe = (SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_DlnkS1cdma2000tunnelingIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szDlnkS1cdma2000tunnelingIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_DlnkS1cdma2000tunnelingIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_DlnkS1cdma2000tunnelingIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_DlnkS1cdma2000tunnelingIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs),
   &flagSz3M,
   szProtIE_Cont_DlnkS1cdma2000tunnelingIEsValidate,
   (U8 *) (&szProtIE_Cont_DlnkS1cdma2000tunnelingIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szDlnkS1cdma2000tunnelingTkn[] =
{
   &szProtIE_Cont_DlnkS1cdma2000tunnelingIEs,
      &szProtIE_Field_DlnkS1cdma2000tunnelingIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szDlnkS1cdma2000tunnelingspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szDlnkS1cdma2000tunnelingTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szDlnkS1cdma2000tunneling =
{
#ifdef CM_PASN_DBG
   " szDlnkS1cdma2000tunneling ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztDlnkS1cdma2000tunneling),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szDlnkS1cdma2000tunnelingspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueUlnkS1cdma2000tunnelingIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szCdma2000RATTyp,
   &szCdma2000SectorID,
   &szCdma2000HOReqdInd,
   &szCdma2000OneXSRVCCInfo,
   &szCdma2000OneXRAND,
   &szCdma2000PDU
};
PUBLIC U32 sz_ValueUlnkS1cdma2000tunnelingIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_cdma2000RATTyp,
   Sztid_cdma2000SectorID,
   Sztid_cdma2000HOReqdInd,
   Sztid_cdma2000OneXSRVCCInfo,
   Sztid_cdma2000OneXRAND,
   Sztid_cdma2000PDU
};
SzMsgConInf szUlnkS1cdma2000tunnelingIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_cdma2000RATTyp, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_cdma2000SectorID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_cdma2000HOReqdInd, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_cdma2000OneXSRVCCInfo, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_cdma2000OneXRAND, SZ_CRIT_REJECT, CM_PASN_ELM_OPT },
      { Sztid_cdma2000PDU, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   8,
   5
}; 
PUBLIC CmPAsnClassInfo sz_ValueUlnkS1cdma2000tunnelingIEsClsInfo =
{
   8,
   &sz_ValueUlnkS1cdma2000tunnelingIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUlnkS1cdma2000tunnelingIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueUlnkS1cdma2000tunnelingIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueUlnkS1cdma2000tunnelingIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueUlnkS1cdma2000tunnelingIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueUlnkS1cdma2000tunnelingIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueUlnkS1cdma2000tunnelingIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueUlnkS1cdma2000tunnelingIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_UlnkS1cdma2000tunnelingIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueUlnkS1cdma2000tunnelingIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UlnkS1cdma2000tunnelingIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_UlnkS1cdma2000tunnelingIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_UlnkS1cdma2000tunnelingIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_UlnkS1cdma2000tunnelingIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_UlnkS1cdma2000tunnelingIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_UlnkS1cdma2000tunnelingIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_UlnkS1cdma2000tunnelingIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_UlnkS1cdma2000tunnelingIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs *protIe = NULLP;
   SztProtIE_Field_UlnkS1cdma2000tunnelingIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_UlnkS1cdma2000tunnelingIEsValidate);
   
   protIe = (SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_UlnkS1cdma2000tunnelingIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szUlnkS1cdma2000tunnelingIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UlnkS1cdma2000tunnelingIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_UlnkS1cdma2000tunnelingIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_UlnkS1cdma2000tunnelingIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs),
   &flagSz3M,
   szProtIE_Cont_UlnkS1cdma2000tunnelingIEsValidate,
   (U8 *) (&szProtIE_Cont_UlnkS1cdma2000tunnelingIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUlnkS1cdma2000tunnelingTkn[] =
{
   &szProtIE_Cont_UlnkS1cdma2000tunnelingIEs,
      &szProtIE_Field_UlnkS1cdma2000tunnelingIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szUlnkS1cdma2000tunnelingspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUlnkS1cdma2000tunnelingTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUlnkS1cdma2000tunneling =
{
#ifdef CM_PASN_DBG
   " szUlnkS1cdma2000tunneling ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUlnkS1cdma2000tunneling),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUlnkS1cdma2000tunnelingspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueUECapbltyInfoIndIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szUERadioCapblty
};
PUBLIC U32 sz_ValueUECapbltyInfoIndIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_UERadioCapblty
};
SzMsgConInf szUECapbltyInfoIndIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_UERadioCapblty, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   3,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueUECapbltyInfoIndIEsClsInfo =
{
   3,
   &sz_ValueUECapbltyInfoIndIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECapbltyInfoIndIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueUECapbltyInfoIndIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueUECapbltyInfoIndIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueUECapbltyInfoIndIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueUECapbltyInfoIndIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueUECapbltyInfoIndIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueUECapbltyInfoIndIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_UECapbltyInfoIndIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueUECapbltyInfoIndIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECapbltyInfoIndIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_UECapbltyInfoIndIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_UECapbltyInfoIndIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_UECapbltyInfoIndIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_UECapbltyInfoIndIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_UECapbltyInfoIndIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_UECapbltyInfoIndIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_UECapbltyInfoIndIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_UECapbltyInfoIndIEs *protIe = NULLP;
   SztProtIE_Field_UECapbltyInfoIndIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_UECapbltyInfoIndIEsValidate);
   
   protIe = (SztProtIE_Cont_UECapbltyInfoIndIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_UECapbltyInfoIndIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szUECapbltyInfoIndIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECapbltyInfoIndIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_UECapbltyInfoIndIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_UECapbltyInfoIndIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_UECapbltyInfoIndIEs),
   &flagSz3M,
   szProtIE_Cont_UECapbltyInfoIndIEsValidate,
   (U8 *) (&szProtIE_Cont_UECapbltyInfoIndIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUECapbltyInfoIndTkn[] =
{
   &szProtIE_Cont_UECapbltyInfoIndIEs,
      &szProtIE_Field_UECapbltyInfoIndIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szUECapbltyInfoIndspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUECapbltyInfoIndTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUECapbltyInfoInd =
{
#ifdef CM_PASN_DBG
   " szUECapbltyInfoInd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztUECapbltyInfoInd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUECapbltyInfoIndspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueENBStatusTfrIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szENB_StatusTfr_TprntCont
};
PUBLIC U32 sz_ValueENBStatusTfrIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_eNB_StatusTfr_TprntCont
};
SzMsgConInf szENBStatusTfrIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_StatusTfr_TprntCont, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   3,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueENBStatusTfrIEsClsInfo =
{
   3,
   &sz_ValueENBStatusTfrIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueENBStatusTfrIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueENBStatusTfrIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueENBStatusTfrIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueENBStatusTfrIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueENBStatusTfrIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueENBStatusTfrIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueENBStatusTfrIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_ENBStatusTfrIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueENBStatusTfrIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ENBStatusTfrIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_ENBStatusTfrIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_ENBStatusTfrIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_ENBStatusTfrIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_ENBStatusTfrIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_ENBStatusTfrIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_ENBStatusTfrIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_ENBStatusTfrIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_ENBStatusTfrIEs *protIe = NULLP;
   SztProtIE_Field_ENBStatusTfrIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_ENBStatusTfrIEsValidate);
   
   protIe = (SztProtIE_Cont_ENBStatusTfrIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_ENBStatusTfrIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szENBStatusTfrIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ENBStatusTfrIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_ENBStatusTfrIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_ENBStatusTfrIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_ENBStatusTfrIEs),
   &flagSz3M,
   szProtIE_Cont_ENBStatusTfrIEsValidate,
   (U8 *) (&szProtIE_Cont_ENBStatusTfrIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szENBStatusTfrTkn[] =
{
   &szProtIE_Cont_ENBStatusTfrIEs,
      &szProtIE_Field_ENBStatusTfrIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szENBStatusTfrspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szENBStatusTfrTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szENBStatusTfr =
{
#ifdef CM_PASN_DBG
   " szENBStatusTfr ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztENBStatusTfr),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szENBStatusTfrspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueMMEStatusTfrIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szENB_StatusTfr_TprntCont
};
PUBLIC U32 sz_ValueMMEStatusTfrIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_eNB_StatusTfr_TprntCont
};
SzMsgConInf szMMEStatusTfrIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_StatusTfr_TprntCont, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   3,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueMMEStatusTfrIEsClsInfo =
{
   3,
   &sz_ValueMMEStatusTfrIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueMMEStatusTfrIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueMMEStatusTfrIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueMMEStatusTfrIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueMMEStatusTfrIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueMMEStatusTfrIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueMMEStatusTfrIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueMMEStatusTfrIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_MMEStatusTfrIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueMMEStatusTfrIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_MMEStatusTfrIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_MMEStatusTfrIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_MMEStatusTfrIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_MMEStatusTfrIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_MMEStatusTfrIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_MMEStatusTfrIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_MMEStatusTfrIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_MMEStatusTfrIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_MMEStatusTfrIEs *protIe = NULLP;
   SztProtIE_Field_MMEStatusTfrIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_MMEStatusTfrIEsValidate);
   
   protIe = (SztProtIE_Cont_MMEStatusTfrIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_MMEStatusTfrIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szMMEStatusTfrIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_MMEStatusTfrIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_MMEStatusTfrIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_MMEStatusTfrIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_MMEStatusTfrIEs),
   &flagSz3M,
   szProtIE_Cont_MMEStatusTfrIEsValidate,
   (U8 *) (&szProtIE_Cont_MMEStatusTfrIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szMMEStatusTfrTkn[] =
{
   &szProtIE_Cont_MMEStatusTfrIEs,
      &szProtIE_Field_MMEStatusTfrIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szMMEStatusTfrspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szMMEStatusTfrTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szMMEStatusTfr =
{
#ifdef CM_PASN_DBG
   " szMMEStatusTfr ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztMMEStatusTfr),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szMMEStatusTfrspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueTraceStartIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szTraceActvn
};
PUBLIC U32 sz_ValueTraceStartIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_TraceActvn
};
SzMsgConInf szTraceStartIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_TraceActvn, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   3,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueTraceStartIEsClsInfo =
{
   3,
   &sz_ValueTraceStartIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueTraceStartIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueTraceStartIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueTraceStartIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueTraceStartIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueTraceStartIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueTraceStartIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueTraceStartIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_TraceStartIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueTraceStartIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_TraceStartIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_TraceStartIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_TraceStartIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_TraceStartIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_TraceStartIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_TraceStartIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_TraceStartIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_TraceStartIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_TraceStartIEs *protIe = NULLP;
   SztProtIE_Field_TraceStartIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_TraceStartIEsValidate);
   
   protIe = (SztProtIE_Cont_TraceStartIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_TraceStartIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szTraceStartIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_TraceStartIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_TraceStartIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_TraceStartIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_TraceStartIEs),
   &flagSz3M,
   szProtIE_Cont_TraceStartIEsValidate,
   (U8 *) (&szProtIE_Cont_TraceStartIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szTraceStartTkn[] =
{
   &szProtIE_Cont_TraceStartIEs,
      &szProtIE_Field_TraceStartIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szTraceStartspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szTraceStartTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szTraceStart =
{
#ifdef CM_PASN_DBG
   " szTraceStart ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTraceStart),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTraceStartspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueTraceFailIndIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szE_UTRAN_Trace_ID,
   &szCause
};
PUBLIC U32 sz_ValueTraceFailIndIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_E_UTRAN_Trace_ID,
   Sztid_Cause
};
SzMsgConInf szTraceFailIndIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_E_UTRAN_Trace_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   4,
   4
}; 
PUBLIC CmPAsnClassInfo sz_ValueTraceFailIndIEsClsInfo =
{
   4,
   &sz_ValueTraceFailIndIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueTraceFailIndIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueTraceFailIndIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueTraceFailIndIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueTraceFailIndIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueTraceFailIndIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueTraceFailIndIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueTraceFailIndIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_TraceFailIndIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueTraceFailIndIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_TraceFailIndIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_TraceFailIndIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_TraceFailIndIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_TraceFailIndIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_TraceFailIndIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_TraceFailIndIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_TraceFailIndIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_TraceFailIndIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_TraceFailIndIEs *protIe = NULLP;
   SztProtIE_Field_TraceFailIndIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_TraceFailIndIEsValidate);
   
   protIe = (SztProtIE_Cont_TraceFailIndIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_TraceFailIndIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szTraceFailIndIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_TraceFailIndIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_TraceFailIndIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_TraceFailIndIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_TraceFailIndIEs),
   &flagSz3M,
   szProtIE_Cont_TraceFailIndIEsValidate,
   (U8 *) (&szProtIE_Cont_TraceFailIndIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szTraceFailIndTkn[] =
{
   &szProtIE_Cont_TraceFailIndIEs,
      &szProtIE_Field_TraceFailIndIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szTraceFailIndspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szTraceFailIndTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szTraceFailInd =
{
#ifdef CM_PASN_DBG
   " szTraceFailInd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTraceFailInd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szTraceFailIndspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueDeactvTraceIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szE_UTRAN_Trace_ID
};
PUBLIC U32 sz_ValueDeactvTraceIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_E_UTRAN_Trace_ID
};
SzMsgConInf szDeactvTraceIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_E_UTRAN_Trace_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   3,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueDeactvTraceIEsClsInfo =
{
   3,
   &sz_ValueDeactvTraceIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueDeactvTraceIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueDeactvTraceIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueDeactvTraceIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueDeactvTraceIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueDeactvTraceIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueDeactvTraceIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueDeactvTraceIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_DeactvTraceIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueDeactvTraceIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_DeactvTraceIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_DeactvTraceIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_DeactvTraceIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_DeactvTraceIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_DeactvTraceIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_DeactvTraceIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_DeactvTraceIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_DeactvTraceIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_DeactvTraceIEs *protIe = NULLP;
   SztProtIE_Field_DeactvTraceIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_DeactvTraceIEsValidate);
   
   protIe = (SztProtIE_Cont_DeactvTraceIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_DeactvTraceIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szDeactvTraceIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_DeactvTraceIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_DeactvTraceIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_DeactvTraceIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_DeactvTraceIEs),
   &flagSz3M,
   szProtIE_Cont_DeactvTraceIEsValidate,
   (U8 *) (&szProtIE_Cont_DeactvTraceIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szDeactvTraceTkn[] =
{
   &szProtIE_Cont_DeactvTraceIEs,
      &szProtIE_Field_DeactvTraceIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szDeactvTracespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szDeactvTraceTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szDeactvTrace =
{
#ifdef CM_PASN_DBG
   " szDeactvTrace ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztDeactvTrace),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szDeactvTracespec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueCellTrafficTraceIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szE_UTRAN_Trace_ID,
   &szEUTRAN_CGI,
   &szTportLyrAddr
};
PUBLIC U32 sz_ValueCellTrafficTraceIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_E_UTRAN_Trace_ID,
   Sztid_EUTRAN_CGI,
   Sztid_TraceCollectionEntityIPAddr
};
SzMsgConInf szCellTrafficTraceIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_E_UTRAN_Trace_ID, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_EUTRAN_CGI, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_TraceCollectionEntityIPAddr, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   5,
   5
}; 
PUBLIC CmPAsnClassInfo sz_ValueCellTrafficTraceIEsClsInfo =
{
   5,
   &sz_ValueCellTrafficTraceIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueCellTrafficTraceIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueCellTrafficTraceIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueCellTrafficTraceIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueCellTrafficTraceIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueCellTrafficTraceIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueCellTrafficTraceIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueCellTrafficTraceIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_CellTrafficTraceIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueCellTrafficTraceIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_CellTrafficTraceIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_CellTrafficTraceIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_CellTrafficTraceIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_CellTrafficTraceIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_CellTrafficTraceIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_CellTrafficTraceIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_CellTrafficTraceIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_CellTrafficTraceIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_CellTrafficTraceIEs *protIe = NULLP;
   SztProtIE_Field_CellTrafficTraceIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_CellTrafficTraceIEsValidate);
   
   protIe = (SztProtIE_Cont_CellTrafficTraceIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_CellTrafficTraceIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szCellTrafficTraceIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_CellTrafficTraceIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_CellTrafficTraceIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_CellTrafficTraceIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_CellTrafficTraceIEs),
   &flagSz3M,
   szProtIE_Cont_CellTrafficTraceIEsValidate,
   (U8 *) (&szProtIE_Cont_CellTrafficTraceIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szCellTrafficTraceTkn[] =
{
   &szProtIE_Cont_CellTrafficTraceIEs,
      &szProtIE_Field_CellTrafficTraceIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szCellTrafficTracespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szCellTrafficTraceTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szCellTrafficTrace =
{
#ifdef CM_PASN_DBG
   " szCellTrafficTrace ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCellTrafficTrace),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szCellTrafficTracespec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueLocRprtngCntrlIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szRqstTyp
};
PUBLIC U32 sz_ValueLocRprtngCntrlIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_RqstTyp
};
SzMsgConInf szLocRprtngCntrlIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_RqstTyp, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   3,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueLocRprtngCntrlIEsClsInfo =
{
   3,
   &sz_ValueLocRprtngCntrlIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueLocRprtngCntrlIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueLocRprtngCntrlIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueLocRprtngCntrlIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueLocRprtngCntrlIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueLocRprtngCntrlIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueLocRprtngCntrlIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueLocRprtngCntrlIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_LocRprtngCntrlIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueLocRprtngCntrlIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_LocRprtngCntrlIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_LocRprtngCntrlIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_LocRprtngCntrlIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_LocRprtngCntrlIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_LocRprtngCntrlIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_LocRprtngCntrlIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_LocRprtngCntrlIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_LocRprtngCntrlIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_LocRprtngCntrlIEs *protIe = NULLP;
   SztProtIE_Field_LocRprtngCntrlIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_LocRprtngCntrlIEsValidate);
   
   protIe = (SztProtIE_Cont_LocRprtngCntrlIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_LocRprtngCntrlIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szLocRprtngCntrlIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_LocRprtngCntrlIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_LocRprtngCntrlIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_LocRprtngCntrlIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_LocRprtngCntrlIEs),
   &flagSz3M,
   szProtIE_Cont_LocRprtngCntrlIEsValidate,
   (U8 *) (&szProtIE_Cont_LocRprtngCntrlIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szLocRprtngCntrlTkn[] =
{
   &szProtIE_Cont_LocRprtngCntrlIEs,
      &szProtIE_Field_LocRprtngCntrlIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szLocRprtngCntrlspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szLocRprtngCntrlTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szLocRprtngCntrl =
{
#ifdef CM_PASN_DBG
   " szLocRprtngCntrl ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztLocRprtngCntrl),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szLocRprtngCntrlspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueLocRprtngFailIndIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szCause
};
PUBLIC U32 sz_ValueLocRprtngFailIndIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_Cause
};
SzMsgConInf szLocRprtngFailIndIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_Cause, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   3,
   3
}; 
PUBLIC CmPAsnClassInfo sz_ValueLocRprtngFailIndIEsClsInfo =
{
   3,
   &sz_ValueLocRprtngFailIndIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueLocRprtngFailIndIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueLocRprtngFailIndIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueLocRprtngFailIndIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueLocRprtngFailIndIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueLocRprtngFailIndIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueLocRprtngFailIndIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueLocRprtngFailIndIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_LocRprtngFailIndIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueLocRprtngFailIndIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_LocRprtngFailIndIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_LocRprtngFailIndIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_LocRprtngFailIndIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_LocRprtngFailIndIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_LocRprtngFailIndIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_LocRprtngFailIndIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_LocRprtngFailIndIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_LocRprtngFailIndIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_LocRprtngFailIndIEs *protIe = NULLP;
   SztProtIE_Field_LocRprtngFailIndIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_LocRprtngFailIndIEsValidate);
   
   protIe = (SztProtIE_Cont_LocRprtngFailIndIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_LocRprtngFailIndIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szLocRprtngFailIndIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_LocRprtngFailIndIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_LocRprtngFailIndIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_LocRprtngFailIndIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_LocRprtngFailIndIEs),
   &flagSz3M,
   szProtIE_Cont_LocRprtngFailIndIEsValidate,
   (U8 *) (&szProtIE_Cont_LocRprtngFailIndIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szLocRprtngFailIndTkn[] =
{
   &szProtIE_Cont_LocRprtngFailIndIEs,
      &szProtIE_Field_LocRprtngFailIndIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szLocRprtngFailIndspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szLocRprtngFailIndTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szLocRprtngFailInd =
{
#ifdef CM_PASN_DBG
   " szLocRprtngFailInd ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztLocRprtngFailInd),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szLocRprtngFailIndspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueLocReportIEsClsInst[] =
{
   &szMME_UE_S1AP_ID,
   &szENB_UE_S1AP_ID,
   &szEUTRAN_CGI,
   &szTAI,
   &szRqstTyp
};
PUBLIC U32 sz_ValueLocReportIEsClsInstId[] =
{
   Sztid_MME_UE_S1AP_ID,
   Sztid_eNB_UE_S1AP_ID,
   Sztid_EUTRAN_CGI,
   Sztid_TAI,
   Sztid_RqstTyp
};
SzMsgConInf szLocReportIEsConInf =
{
   {
      { Sztid_MME_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_eNB_UE_S1AP_ID, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_EUTRAN_CGI, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_TAI, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND },
      { Sztid_RqstTyp, SZ_CRIT_IGNORE, CM_PASN_ELM_MAND }
   },
   5,
   5
}; 
PUBLIC CmPAsnClassInfo sz_ValueLocReportIEsClsInfo =
{
   5,
   &sz_ValueLocReportIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueLocReportIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueLocReportIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueLocReportIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueLocReportIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueLocReportIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueLocReportIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueLocReportIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_LocReportIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueLocReportIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_LocReportIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_LocReportIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_LocReportIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_LocReportIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_LocReportIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_LocReportIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_LocReportIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_LocReportIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_LocReportIEs *protIe = NULLP;
   SztProtIE_Field_LocReportIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_LocReportIEsValidate);
   
   protIe = (SztProtIE_Cont_LocReportIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_LocReportIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szLocReportIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_LocReportIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_LocReportIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_LocReportIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_LocReportIEs),
   &flagSz3M,
   szProtIE_Cont_LocReportIEsValidate,
   (U8 *) (&szProtIE_Cont_LocReportIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szLocReportTkn[] =
{
   &szProtIE_Cont_LocReportIEs,
      &szProtIE_Field_LocReportIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szLocReportspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szLocReportTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szLocReport =
{
#ifdef CM_PASN_DBG
   " szLocReport ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztLocReport),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szLocReportspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueOverloadStartIEsClsInst[] =
{
   &szOverloadResp
};
PUBLIC U32 sz_ValueOverloadStartIEsClsInstId[] =
{
   Sztid_OverloadResp
};
SzMsgConInf szOverloadStartIEsConInf =
{
   {
      { Sztid_OverloadResp, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueOverloadStartIEsClsInfo =
{
   1,
   &sz_ValueOverloadStartIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueOverloadStartIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueOverloadStartIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueOverloadStartIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueOverloadStartIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueOverloadStartIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueOverloadStartIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueOverloadStartIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_OverloadStartIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueOverloadStartIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_OverloadStartIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_OverloadStartIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_OverloadStartIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_OverloadStartIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_OverloadStartIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_OverloadStartIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_OverloadStartIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_OverloadStartIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_OverloadStartIEs *protIe = NULLP;
   SztProtIE_Field_OverloadStartIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_OverloadStartIEsValidate);
   
   protIe = (SztProtIE_Cont_OverloadStartIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_OverloadStartIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szOverloadStartIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_OverloadStartIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_OverloadStartIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_OverloadStartIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_OverloadStartIEs),
   &flagSz3M,
   szProtIE_Cont_OverloadStartIEsValidate,
   (U8 *) (&szProtIE_Cont_OverloadStartIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szOverloadStartTkn[] =
{
   &szProtIE_Cont_OverloadStartIEs,
      &szProtIE_Field_OverloadStartIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szOverloadStartspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szOverloadStartTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szOverloadStart =
{
#ifdef CM_PASN_DBG
   " szOverloadStart ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztOverloadStart),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szOverloadStartspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueOverloadStopIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ValueOverloadStopIEsClsInstId[] =
{
   Sztid_Invalid
};
SzMsgConInf szOverloadStopIEsConInf =
{
   {
      { Sztid_Invalid, CM_PASN_ELM_INV }
   },
   0,
   0
}; 
PUBLIC CmPAsnClassInfo sz_ValueOverloadStopIEsClsInfo =
{
   0,
   &sz_ValueOverloadStopIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueOverloadStopIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueOverloadStopIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueOverloadStopIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueOverloadStopIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueOverloadStopIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueOverloadStopIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueOverloadStopIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_OverloadStopIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueOverloadStopIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_OverloadStopIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_OverloadStopIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_OverloadStopIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_OverloadStopIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_OverloadStopIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_OverloadStopIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_OverloadStopIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_OverloadStopIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_OverloadStopIEs *protIe = NULLP;
   SztProtIE_Field_OverloadStopIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_OverloadStopIEsValidate);
   
   protIe = (SztProtIE_Cont_OverloadStopIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_OverloadStopIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szOverloadStopIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_OverloadStopIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_OverloadStopIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_OverloadStopIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_OverloadStopIEs),
   &flagSz3M,
   szProtIE_Cont_OverloadStopIEsValidate,
   (U8 *) (&szProtIE_Cont_OverloadStopIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szOverloadStopTkn[] =
{
   &szProtIE_Cont_OverloadStopIEs,
      &szProtIE_Field_OverloadStopIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szOverloadStopspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szOverloadStopTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szOverloadStop =
{
#ifdef CM_PASN_DBG
   " szOverloadStop ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztOverloadStop),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szOverloadStopspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueWriteReplaceWarningRqstIEsClsInst[] =
{
   &szMsgIdentifier,
   &szSerialNumber,
   &szWarningAreaLst,
   &szRepetitionPeriod,
   &szNumberofBroadcastRqst,
   &szWarningTyp,
   &szWarningSecurInfo,
   &szDataCodingScheme,
   &szWarningMsgContents
};
PUBLIC U32 sz_ValueWriteReplaceWarningRqstIEsClsInstId[] =
{
   Sztid_MsgIdentifier,
   Sztid_SerialNumber,
   Sztid_WarningAreaLst,
   Sztid_RepetitionPeriod,
   Sztid_NumberofBroadcastRqst,
   Sztid_WarningTyp,
   Sztid_WarningSecurInfo,
   Sztid_DataCodingScheme,
   Sztid_WarningMsgContents
};
SzMsgConInf szWriteReplaceWarningRqstIEsConInf =
{
   {
      { Sztid_MsgIdentifier, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_SerialNumber, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_WarningAreaLst, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_RepetitionPeriod, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_NumberofBroadcastRqst, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_WarningTyp, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_WarningSecurInfo, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_DataCodingScheme, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_WarningMsgContents, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   9,
   4
}; 
PUBLIC CmPAsnClassInfo sz_ValueWriteReplaceWarningRqstIEsClsInfo =
{
   9,
   &sz_ValueWriteReplaceWarningRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueWriteReplaceWarningRqstIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueWriteReplaceWarningRqstIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueWriteReplaceWarningRqstIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueWriteReplaceWarningRqstIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueWriteReplaceWarningRqstIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueWriteReplaceWarningRqstIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueWriteReplaceWarningRqstIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_WriteReplaceWarningRqstIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueWriteReplaceWarningRqstIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_WriteReplaceWarningRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_WriteReplaceWarningRqstIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_WriteReplaceWarningRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_WriteReplaceWarningRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_WriteReplaceWarningRqstIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_WriteReplaceWarningRqstIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_WriteReplaceWarningRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_WriteReplaceWarningRqstIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_WriteReplaceWarningRqstIEs *protIe = NULLP;
   SztProtIE_Field_WriteReplaceWarningRqstIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_WriteReplaceWarningRqstIEsValidate);
   
   protIe = (SztProtIE_Cont_WriteReplaceWarningRqstIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_WriteReplaceWarningRqstIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szWriteReplaceWarningRqstIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_WriteReplaceWarningRqstIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_WriteReplaceWarningRqstIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_WriteReplaceWarningRqstIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_WriteReplaceWarningRqstIEs),
   &flagSz3M,
   szProtIE_Cont_WriteReplaceWarningRqstIEsValidate,
   (U8 *) (&szProtIE_Cont_WriteReplaceWarningRqstIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szWriteReplaceWarningRqstTkn[] =
{
   &szProtIE_Cont_WriteReplaceWarningRqstIEs,
      &szProtIE_Field_WriteReplaceWarningRqstIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szWriteReplaceWarningRqstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szWriteReplaceWarningRqstTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szWriteReplaceWarningRqst =
{
#ifdef CM_PASN_DBG
   " szWriteReplaceWarningRqst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztWriteReplaceWarningRqst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szWriteReplaceWarningRqstspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueWriteReplaceWarningRespIEsClsInst[] =
{
   &szMsgIdentifier,
   &szSerialNumber,
   &szBroadcastCompletedAreaLst,
   &szCriticalityDiag
};
PUBLIC U32 sz_ValueWriteReplaceWarningRespIEsClsInstId[] =
{
   Sztid_MsgIdentifier,
   Sztid_SerialNumber,
   Sztid_BroadcastCompletedAreaLst,
   Sztid_CriticalityDiag
};
SzMsgConInf szWriteReplaceWarningRespIEsConInf =
{
   {
      { Sztid_MsgIdentifier, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_SerialNumber, SZ_CRIT_REJECT, CM_PASN_ELM_MAND },
      { Sztid_BroadcastCompletedAreaLst, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT },
      { Sztid_CriticalityDiag, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   4,
   2
}; 
PUBLIC CmPAsnClassInfo sz_ValueWriteReplaceWarningRespIEsClsInfo =
{
   4,
   &sz_ValueWriteReplaceWarningRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueWriteReplaceWarningRespIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueWriteReplaceWarningRespIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueWriteReplaceWarningRespIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueWriteReplaceWarningRespIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueWriteReplaceWarningRespIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueWriteReplaceWarningRespIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueWriteReplaceWarningRespIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_WriteReplaceWarningRespIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueWriteReplaceWarningRespIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_WriteReplaceWarningRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_WriteReplaceWarningRespIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_WriteReplaceWarningRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_WriteReplaceWarningRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_WriteReplaceWarningRespIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_WriteReplaceWarningRespIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_WriteReplaceWarningRespIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_WriteReplaceWarningRespIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_WriteReplaceWarningRespIEs *protIe = NULLP;
   SztProtIE_Field_WriteReplaceWarningRespIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_WriteReplaceWarningRespIEsValidate);
   
   protIe = (SztProtIE_Cont_WriteReplaceWarningRespIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_WriteReplaceWarningRespIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szWriteReplaceWarningRespIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_WriteReplaceWarningRespIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_WriteReplaceWarningRespIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_WriteReplaceWarningRespIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_WriteReplaceWarningRespIEs),
   &flagSz3M,
   szProtIE_Cont_WriteReplaceWarningRespIEsValidate,
   (U8 *) (&szProtIE_Cont_WriteReplaceWarningRespIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szWriteReplaceWarningRespTkn[] =
{
   &szProtIE_Cont_WriteReplaceWarningRespIEs,
      &szProtIE_Field_WriteReplaceWarningRespIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szWriteReplaceWarningRespspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szWriteReplaceWarningRespTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szWriteReplaceWarningResp =
{
#ifdef CM_PASN_DBG
   " szWriteReplaceWarningResp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztWriteReplaceWarningResp),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szWriteReplaceWarningRespspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szInter_SystemInformTfrTypTkn[] =
{
   &szRIMTfr,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szInter_SystemInformTfrTypspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   1,
   0,
   &szInter_SystemInformTfrTypTkn[0]  /* Token List */
};
CmPAsnElmDef szInter_SystemInformTfrTyp =
{
#ifdef CM_PASN_DBG
   " szInter_SystemInformTfrTyp ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztInter_SystemInformTfrTyp),
   &flagSz3M,
   NULLP,
   (U8 *)(&szInter_SystemInformTfrTypspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueENBDirectInformTfrIEsClsInst[] =
{
   &szInter_SystemInformTfrTyp
};
PUBLIC U32 sz_ValueENBDirectInformTfrIEsClsInstId[] =
{
   Sztid_Inter_SystemInformTfrTypEDT
};
SzMsgConInf szENBDirectInformTfrIEsConInf =
{
   {
      { Sztid_Inter_SystemInformTfrTypEDT, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueENBDirectInformTfrIEsClsInfo =
{
   1,
   &sz_ValueENBDirectInformTfrIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueENBDirectInformTfrIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueENBDirectInformTfrIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueENBDirectInformTfrIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueENBDirectInformTfrIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueENBDirectInformTfrIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueENBDirectInformTfrIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueENBDirectInformTfrIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_ENBDirectInformTfrIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueENBDirectInformTfrIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ENBDirectInformTfrIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_ENBDirectInformTfrIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_ENBDirectInformTfrIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_ENBDirectInformTfrIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_ENBDirectInformTfrIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_ENBDirectInformTfrIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_ENBDirectInformTfrIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_ENBDirectInformTfrIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_ENBDirectInformTfrIEs *protIe = NULLP;
   SztProtIE_Field_ENBDirectInformTfrIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_ENBDirectInformTfrIEsValidate);
   
   protIe = (SztProtIE_Cont_ENBDirectInformTfrIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_ENBDirectInformTfrIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szENBDirectInformTfrIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ENBDirectInformTfrIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_ENBDirectInformTfrIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_ENBDirectInformTfrIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_ENBDirectInformTfrIEs),
   &flagSz3M,
   szProtIE_Cont_ENBDirectInformTfrIEsValidate,
   (U8 *) (&szProtIE_Cont_ENBDirectInformTfrIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szENBDirectInformTfrTkn[] =
{
   &szProtIE_Cont_ENBDirectInformTfrIEs,
      &szProtIE_Field_ENBDirectInformTfrIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szENBDirectInformTfrspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szENBDirectInformTfrTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szENBDirectInformTfr =
{
#ifdef CM_PASN_DBG
   " szENBDirectInformTfr ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztENBDirectInformTfr),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szENBDirectInformTfrspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueMMEDirectInformTfrIEsClsInst[] =
{
   &szInter_SystemInformTfrTyp
};
PUBLIC U32 sz_ValueMMEDirectInformTfrIEsClsInstId[] =
{
   Sztid_Inter_SystemInformTfrTypMDT
};
SzMsgConInf szMMEDirectInformTfrIEsConInf =
{
   {
      { Sztid_Inter_SystemInformTfrTypMDT, SZ_CRIT_REJECT, CM_PASN_ELM_MAND }
   },
   1,
   1
}; 
PUBLIC CmPAsnClassInfo sz_ValueMMEDirectInformTfrIEsClsInfo =
{
   1,
   &sz_ValueMMEDirectInformTfrIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueMMEDirectInformTfrIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueMMEDirectInformTfrIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueMMEDirectInformTfrIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueMMEDirectInformTfrIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueMMEDirectInformTfrIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueMMEDirectInformTfrIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueMMEDirectInformTfrIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_MMEDirectInformTfrIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueMMEDirectInformTfrIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_MMEDirectInformTfrIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_MMEDirectInformTfrIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_MMEDirectInformTfrIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_MMEDirectInformTfrIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_MMEDirectInformTfrIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_MMEDirectInformTfrIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_MMEDirectInformTfrIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_MMEDirectInformTfrIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_MMEDirectInformTfrIEs *protIe = NULLP;
   SztProtIE_Field_MMEDirectInformTfrIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_MMEDirectInformTfrIEsValidate);
   
   protIe = (SztProtIE_Cont_MMEDirectInformTfrIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_MMEDirectInformTfrIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szMMEDirectInformTfrIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_MMEDirectInformTfrIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_MMEDirectInformTfrIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_MMEDirectInformTfrIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_MMEDirectInformTfrIEs),
   &flagSz3M,
   szProtIE_Cont_MMEDirectInformTfrIEsValidate,
   (U8 *) (&szProtIE_Cont_MMEDirectInformTfrIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szMMEDirectInformTfrTkn[] =
{
   &szProtIE_Cont_MMEDirectInformTfrIEs,
      &szProtIE_Field_MMEDirectInformTfrIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szMMEDirectInformTfrspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szMMEDirectInformTfrTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szMMEDirectInformTfr =
{
#ifdef CM_PASN_DBG
   " szMMEDirectInformTfr ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztMMEDirectInformTfr),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szMMEDirectInformTfrspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueENBConfigTfrIEsClsInst[] =
{
   &szSONConfigTfr
};
PUBLIC U32 sz_ValueENBConfigTfrIEsClsInstId[] =
{
   Sztid_SONConfigTfrECT
};
SzMsgConInf szENBConfigTfrIEsConInf =
{
   {
      { Sztid_SONConfigTfrECT, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   1,
   0
}; 
PUBLIC CmPAsnClassInfo sz_ValueENBConfigTfrIEsClsInfo =
{
   1,
   &sz_ValueENBConfigTfrIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueENBConfigTfrIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueENBConfigTfrIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueENBConfigTfrIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueENBConfigTfrIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueENBConfigTfrIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueENBConfigTfrIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueENBConfigTfrIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_ENBConfigTfrIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueENBConfigTfrIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ENBConfigTfrIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_ENBConfigTfrIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_ENBConfigTfrIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_ENBConfigTfrIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_ENBConfigTfrIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_ENBConfigTfrIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_ENBConfigTfrIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_ENBConfigTfrIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_ENBConfigTfrIEs *protIe = NULLP;
   SztProtIE_Field_ENBConfigTfrIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_ENBConfigTfrIEsValidate);
   
   protIe = (SztProtIE_Cont_ENBConfigTfrIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_ENBConfigTfrIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szENBConfigTfrIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ENBConfigTfrIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_ENBConfigTfrIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_ENBConfigTfrIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_ENBConfigTfrIEs),
   &flagSz3M,
   szProtIE_Cont_ENBConfigTfrIEsValidate,
   (U8 *) (&szProtIE_Cont_ENBConfigTfrIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szENBConfigTfrTkn[] =
{
   &szProtIE_Cont_ENBConfigTfrIEs,
      &szProtIE_Field_ENBConfigTfrIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szENBConfigTfrspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szENBConfigTfrTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szENBConfigTfr =
{
#ifdef CM_PASN_DBG
   " szENBConfigTfr ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztENBConfigTfr),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szENBConfigTfrspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValueMMEConfigTfrIEsClsInst[] =
{
   &szSONConfigTfr
};
PUBLIC U32 sz_ValueMMEConfigTfrIEsClsInstId[] =
{
   Sztid_SONConfigTfrMCT
};
SzMsgConInf szMMEConfigTfrIEsConInf =
{
   {
      { Sztid_SONConfigTfrMCT, SZ_CRIT_IGNORE, CM_PASN_ELM_OPT }
   },
   1,
   0
}; 
PUBLIC CmPAsnClassInfo sz_ValueMMEConfigTfrIEsClsInfo =
{
   1,
   &sz_ValueMMEConfigTfrIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueMMEConfigTfrIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValueMMEConfigTfrIEsClsInfo,
   (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
   &sz_ValueMMEConfigTfrIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValueMMEConfigTfrIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValueMMEConfigTfrIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValueMMEConfigTfrIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValueMMEConfigTfrIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szProtIE_Field_MMEConfigTfrIEsTkn[] =
{
   &szProtIE_ID,
   &szCriticality,
   &sz_ValueMMEConfigTfrIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_MMEConfigTfrIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szProtIE_Field_MMEConfigTfrIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szProtIE_Field_MMEConfigTfrIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Field_MMEConfigTfrIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Field_MMEConfigTfrIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szProtIE_Field_MMEConfigTfrIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szProtIE_Cont_MMEConfigTfrIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szProtIE_Cont_MMEConfigTfrIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztProtIE_Cont_MMEConfigTfrIEs *protIe = NULLP;
   SztProtIE_Field_MMEConfigTfrIEs *member = NULLP;
   
   TRC2(szProtIE_Cont_MMEConfigTfrIEsValidate);
   
   protIe = (SztProtIE_Cont_MMEConfigTfrIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztProtIE_Field_MMEConfigTfrIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szMMEConfigTfrIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_MMEConfigTfrIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   0,        /* start of the size */
   SztmaxProtIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szProtIE_Cont_MMEConfigTfrIEs =
{
#ifdef CM_PASN_DBG
   " szProtIE_Cont_MMEConfigTfrIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtIE_Cont_MMEConfigTfrIEs),
   &flagSz3M,
   szProtIE_Cont_MMEConfigTfrIEsValidate,
   (U8 *) (&szProtIE_Cont_MMEConfigTfrIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szMMEConfigTfrTkn[] =
{
   &szProtIE_Cont_MMEConfigTfrIEs,
      &szProtIE_Field_MMEConfigTfrIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szMMEConfigTfrspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szMMEConfigTfrTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szMMEConfigTfr =
{
#ifdef CM_PASN_DBG
   " szMMEConfigTfr ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztMMEConfigTfr),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szMMEConfigTfrspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_ValuePrivMsgIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz_ValuePrivMsgIEsClsInstId[] =
{
   Sztid_Invalid
};
SzMsgConInf szPrivMsgIEsConInf =
{
   {
      { Sztid_Invalid, CM_PASN_ELM_INV }
   },
   0,
   0
}; 
PUBLIC CmPAsnClassInfo sz_ValuePrivMsgIEsClsInfo =
{
   0,
   &sz_ValuePrivMsgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValuePrivMsgIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_ValuePrivMsgIEsClsInfo,
   0,
   &sz_ValuePrivMsgIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_ValuePrivMsgIEsCls =
{
#ifdef CM_PASN_DBG
   " sz_ValuePrivMsgIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ValuePrivMsgIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_ValuePrivMsgIEsClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szPrivIE_Field_PrivMsgIEsTkn[] =
{
   &szPrivIE_ID,
   &szCriticality,
   &sz_ValuePrivMsgIEsCls,
   &szConstTerm
};
CmPAsnSetSeqDef szPrivIE_Field_PrivMsgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szPrivIE_Field_PrivMsgIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szPrivIE_Field_PrivMsgIEs =
{
#ifdef CM_PASN_DBG
   " szPrivIE_Field_PrivMsgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztPrivIE_Field_PrivMsgIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szPrivIE_Field_PrivMsgIEsspec),
   NULLP
};

#ifdef ANSI
PUBLIC S16 szPrivIE_Cont_PrivMsgIEsValidate
(
CmPAsnMsgCp *msgCp
)
#else
PUBLIC S16 szPrivIE_Cont_PrivMsgIEsValidate(msgCp)
CmPAsnMsgCp *msgCp;
#endif
{
   U8 numIes = 0;
   U32 sizeIe = 0;
   
   S16 ret = ROK;
   SztPrivIE_Cont_PrivMsgIEs *protIe = NULLP;
   SztPrivIE_Field_PrivMsgIEs *member = NULLP;
   
   TRC2(szPrivIE_Cont_PrivMsgIEsValidate);
   
   protIe = (SztPrivIE_Cont_PrivMsgIEs *)(msgCp->evntStr);
   numIes = protIe->noComp.val;
   
   sizeIe = sizeof(SztPrivIE_Field_PrivMsgIEs);
   
   member = &protIe->member[0];
   
   ret = szValidateProtIes(&szPrivMsgIEsConInf, msgCp, member, sizeIe, numIes);
   
   RETVALUE(ret);
}
CmPAsnSetSeqOfDef szPrivIE_Cont_PrivMsgIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxPrivIEs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef szPrivIE_Cont_PrivMsgIEs =
{
#ifdef CM_PASN_DBG
   " szPrivIE_Cont_PrivMsgIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztPrivIE_Cont_PrivMsgIEs),
   &flagSz3M,
   szPrivIE_Cont_PrivMsgIEsValidate,
   (U8 *) (&szPrivIE_Cont_PrivMsgIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szPrivMsgTkn[] =
{
   &szPrivIE_Cont_PrivMsgIEs,
      &szPrivIE_Field_PrivMsgIEs,
      &szConstTerm,
   &szExtMkr,
   &szConstTerm
};
CmPAsnSetSeqDef szPrivMsgspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szPrivMsgTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szPrivMsg =
{
#ifdef CM_PASN_DBG
   " szPrivMsg ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztPrivMsg),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szPrivMsgspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_InitiatingMsgClsInst[] =
{
   &szHovrReqd,
   &szHovrRqst,
   &szPathSwRqst,
   &szE_RABSetupRqst,
   &szE_RABMdfyRqst,
   &szE_RABRlsCmmd,
   &szInitCntxtSetupRqst,
   &szHovrCancel,
   &szReset,
   &szS1SetupRqst,
   &szUECntxtModificationRqst,
   &szUECntxtRlsCmmd,
   &szENBConfigUpd,
   &szMMEConfigUpd,
   &szWriteReplaceWarningRqst,
   &szHovrNtfy,
   &szE_RABRlsInd,
   &szPag,
   &szDlnkNASTport,
   &szInitUEMsg,
   &szUlnkNASTport,
   &szErrInd,
   &szNASNonDlvryInd,
   &szUECntxtRlsRqst,
   &szDlnkS1cdma2000tunneling,
   &szUlnkS1cdma2000tunneling,
   &szUECapbltyInfoInd,
   &szENBStatusTfr,
   &szMMEStatusTfr,
   &szDeactvTrace,
   &szTraceStart,
   &szTraceFailInd,
   &szCellTrafficTrace,
   &szLocRprtngCntrl,
   &szLocRprtngFailInd,
   &szLocReport,
   &szOverloadStart,
   &szOverloadStop,
   &szENBDirectInformTfr,
   &szMMEDirectInformTfr,
   &szENBConfigTfr,
   &szMMEConfigTfr,
   &szPrivMsg
};
PUBLIC U32 sz_InitiatingMsgClsInstId[] =
{
   Sztid_HovrPrep,
   Sztid_HovrResourceAllocn,
   Sztid_PathSwRqst,
   Sztid_E_RABSetup,
   Sztid_E_RABMdfy,
   Sztid_E_RABRls,
   Sztid_InitCntxtSetup,
   Sztid_HovrCancel,
   Sztid_Reset,
   Sztid_S1Setup,
   Sztid_UECntxtModification,
   Sztid_UECntxtRls,
   Sztid_ENBConfigUpd,
   Sztid_MMEConfigUpd,
   Sztid_WriteReplaceWarning,
   Sztid_HovrNotification,
   Sztid_E_RABRlsInd,
   Sztid_Pag,
   Sztid_downlinkNASTport,
   Sztid_initialUEMsg,
   Sztid_uplinkNASTport,
   Sztid_ErrInd,
   Sztid_NASNonDlvryInd,
   Sztid_UECntxtRlsRqst,
   Sztid_DlnkS1cdma2000tunneling,
   Sztid_UlnkS1cdma2000tunneling,
   Sztid_UECapbltyInfoInd,
   Sztid_eNBStatusTfr,
   Sztid_MMEStatusTfr,
   Sztid_DeactvTrace,
   Sztid_TraceStart,
   Sztid_TraceFailInd,
   Sztid_CellTrafficTrace,
   Sztid_LocRprtngCntrl,
   Sztid_LocRprtngFailInd,
   Sztid_LocReport,
   Sztid_OverloadStart,
   Sztid_OverloadStop,
   Sztid_eNBDirectInformTfr,
   Sztid_MMEDirectInformTfr,
   Sztid_eNBConfigTfr,
   Sztid_MMEConfigTfr,
   Sztid_PrivMsg
};
PUBLIC CmPAsnClassInfo sz_InitiatingMsgClsInfo =
{
   43,
   &sz_InitiatingMsgClsInstId[0]
};
CmPAsnClassIEDef sz_InitiatingMsgClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_InitiatingMsgClsInfo,
   (sizeof(SztProcedureCode) + sizeof(SztCriticality)),
   &sz_InitiatingMsgClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_InitiatingMsgCls =
{
#ifdef CM_PASN_DBG
   " sz_InitiatingMsgCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_InitiatingMsgCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_InitiatingMsgClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szInitiatingMsgTkn[] =
{
   &szProcedureCode,
   &szCriticality,
   &sz_InitiatingMsgCls,
   &szConstTerm
};
CmPAsnSetSeqDef szInitiatingMsgspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szInitiatingMsgTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szInitiatingMsg =
{
#ifdef CM_PASN_DBG
   " szInitiatingMsg ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztInitiatingMsg),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szInitiatingMsgspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_SuccessfulOutcomeClsInst[] =
{
   &szHovrCmmd,
   &szHovrRqstAckg,
   &szPathSwRqstAckg,
   &szE_RABSetupResp,
   &szE_RABMdfyResp,
   &szE_RABRlsResp,
   &szInitCntxtSetupResp,
   &szHovrCancelAckg,
   &szResetAckg,
   &szS1SetupResp,
   &szUECntxtModificationResp,
   &szUECntxtRlsComplete,
   &szENBConfigUpdAckg,
   &szMMEConfigUpdAckg,
   &szWriteReplaceWarningResp
};
PUBLIC U32 sz_SuccessfulOutcomeClsInstId[] =
{
   Sztid_HovrPrep,
   Sztid_HovrResourceAllocn,
   Sztid_PathSwRqst,
   Sztid_E_RABSetup,
   Sztid_E_RABMdfy,
   Sztid_E_RABRls,
   Sztid_InitCntxtSetup,
   Sztid_HovrCancel,
   Sztid_Reset,
   Sztid_S1Setup,
   Sztid_UECntxtModification,
   Sztid_UECntxtRls,
   Sztid_ENBConfigUpd,
   Sztid_MMEConfigUpd,
   Sztid_WriteReplaceWarning
};
PUBLIC CmPAsnClassInfo sz_SuccessfulOutcomeClsInfo =
{
   15,
   &sz_SuccessfulOutcomeClsInstId[0]
};
CmPAsnClassIEDef sz_SuccessfulOutcomeClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_SuccessfulOutcomeClsInfo,
   (sizeof(SztProcedureCode) + sizeof(SztCriticality)),
   &sz_SuccessfulOutcomeClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_SuccessfulOutcomeCls =
{
#ifdef CM_PASN_DBG
   " sz_SuccessfulOutcomeCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_SuccessfulOutcomeCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_SuccessfulOutcomeClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szSuccessfulOutcomeTkn[] =
{
   &szProcedureCode,
   &szCriticality,
   &sz_SuccessfulOutcomeCls,
   &szConstTerm
};
CmPAsnSetSeqDef szSuccessfulOutcomespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szSuccessfulOutcomeTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szSuccessfulOutcome =
{
#ifdef CM_PASN_DBG
   " szSuccessfulOutcome ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSuccessfulOutcome),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szSuccessfulOutcomespec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz_UnsuccessfulOutcomeClsInst[] =
{
   &szHovrPrepFail,
   &szHovrFail,
   &szPathSwRqstFail,
   &szInitCntxtSetupFail,
   &szS1SetupFail,
   &szUECntxtModificationFail,
   &szENBConfigUpdFail,
   &szMMEConfigUpdFail
};
PUBLIC U32 sz_UnsuccessfulOutcomeClsInstId[] =
{
   Sztid_HovrPrep,
   Sztid_HovrResourceAllocn,
   Sztid_PathSwRqst,
   Sztid_InitCntxtSetup,
   Sztid_S1Setup,
   Sztid_UECntxtModification,
   Sztid_ENBConfigUpd,
   Sztid_MMEConfigUpd
};
PUBLIC CmPAsnClassInfo sz_UnsuccessfulOutcomeClsInfo =
{
   8,
   &sz_UnsuccessfulOutcomeClsInstId[0]
};
CmPAsnClassIEDef sz_UnsuccessfulOutcomeClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz_UnsuccessfulOutcomeClsInfo,
   (sizeof(SztProcedureCode) + sizeof(SztCriticality)),
   &sz_UnsuccessfulOutcomeClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz_UnsuccessfulOutcomeCls =
{
#ifdef CM_PASN_DBG
   " sz_UnsuccessfulOutcomeCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_UnsuccessfulOutcomeCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz_UnsuccessfulOutcomeClsSpec),
   NULLP
};
PUBLIC CmPAsnElmDef *szUnsuccessfulOutcomeTkn[] =
{
   &szProcedureCode,
   &szCriticality,
   &sz_UnsuccessfulOutcomeCls,
   &szConstTerm
};
CmPAsnSetSeqDef szUnsuccessfulOutcomespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &szUnsuccessfulOutcomeTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef szUnsuccessfulOutcome =
{
#ifdef CM_PASN_DBG
   " szUnsuccessfulOutcome ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztUnsuccessfulOutcome),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&szUnsuccessfulOutcomespec),
   NULLP
};
PUBLIC CmPAsnElmDef *szS1AP_PDUTkn[] =
{
   &szInitiatingMsg,
   &szSuccessfulOutcome,
   &szUnsuccessfulOutcome,
   &szExtMkr,
   &szConstTerm
};
CmPAsnChoiceDef szS1AP_PDUspec = 
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CHOICE,
#endif
   3,
   0,
   &szS1AP_PDUTkn[0]  /* Token List */
};
CmPAsnElmDef szS1AP_PDU =
{
#ifdef CM_PASN_DBG
   " szS1AP_PDU ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CHOICE,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztS1AP_PDU),
   &flagSz3M,
   NULLP,
   (U8 *)(&szS1AP_PDUspec),
   NULLP
};
PUBLIC CmPAsnElmDef *szMsgDb[] =
{
   &szS1AP_PDU,
   NULLP
};

#ifdef SZ_ENC_DEC
PUBLIC CmPAsnElmDef *szMsgIEDb[][4] = 
{
   {
      &szMME_UE_S1AP_ID,
      NULLP,
      NULLP,
      NULLP
   }, /* 0 */
   {
      &szHovrTyp,
      NULLP,
      NULLP,
      NULLP
   }, /* 1 */
   {
      &szCause,
      NULLP,
      NULLP,
      NULLP
   }, /* 2 */
   /* szSrcID is Not used */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 3 */
   {
      &szTgetID,
      NULLP,
      NULLP,
      NULLP
   }, /* 4 */
   /* Following 3 IE's not present in sepc */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 5 */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 6 */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 7 */
   {
      &szENB_UE_S1AP_ID,
      NULLP,
      NULLP,
      NULLP
   }, /* 8 */
   /* Following 3 IE's not present in sepc */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 9 */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 10 */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 11 */
   {
      &szE_RABSubjtoDataFwdingLst,
      &szProtIE_SingleCont_E_RABDataFwdingItemIEs,
      &szConstTerm,
      NULLP
   }, /* 12 */
   {
      &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      &szConstTerm,
      NULLP
   }, /* 13 */
   {
      &szE_RABDataFwdingItem,
      NULLP,
      NULLP,
      NULLP
   }, /* 14 */
   {
      &szE_RABRlsItemBrRelComp,
      NULLP,
      NULLP,
      NULLP
   }, /* 15 */
   {
      &szE_RABToBeSetupLstBrSUReq,
      &szProtIE_Field_E_RABToBeSetupItemBrSUReqIEs,
      NULLP,
      NULLP
   }, /* 16 */
   {
      &szE_RABToBeSetupItemBrSUReq,
      NULLP,
      NULLP,
      NULLP
   }, /* 17 */
   {
      &szProtIE_ContLst_E_RABAdmtdItemIEs,
      &szProtIE_SingleCont_E_RABAdmtdItemIEs,
      &szConstTerm,
      NULLP, 
   }, /* 18 */
   {
      &szProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs,
      &szProtIE_SingleCont_E_RABFailedtoSetupItemHOReqAckIEs,
      NULLP,
      NULLP
   }, /* 19 */
   {
      &szE_RABAdmtdItem,
      NULLP,
      NULLP,
      NULLP
   }, /* 20 */
   {
      &szE_RABFailedToSetupItemHOReqAck,
      NULLP,
      NULLP,
      NULLP
   }, /* 21 */
   {
      &szE_RABToBeSwedDLLst,
      &szProtIE_SingleCont_E_RABToBeSwedDLItemIEs,
      NULLP,
      NULLP
   }, /* 22 */
   {
      &szE_RABToBeSwedDLItem,
      NULLP,
      NULLP,
      NULLP
   }, /* 23 */
   {
      &szE_RABToBeSetupLstCtxtSUReq,
      &szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs,
      NULLP,
      NULLP
   }, /* 24 */
   {
      &szTraceActvn,
      NULLP,
      NULLP,
      NULLP
   }, /* 25 */
   {
      &szNAS_PDU,
      NULLP,
      NULLP,
      NULLP
   }, /* 26 */
   {
      &szE_RABToBeSetupItemHOReq,
      NULLP,
      NULLP,
      NULLP
   }, /* 27 */
   {
      &szE_RABSetupLstBrSURes,
      NULLP,
      NULLP,
      NULLP
   }, /* 28 */
   {
      &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      NULLP,
      NULLP
   }, /* 29 */
   {
      &szE_RABToBeMdfdLstBrModReq,
      &szProtIE_Field_E_RABToBeMdfdItemBrModReqIEs,
      NULLP,
      NULLP
   }, /* 30 */
   {
      &szE_RABMdfyLstBrModRes,
      &szProtIE_Field_E_RABMdfyItemBrModResIEs,
      NULLP,
      NULLP
   }, /* 31 */
   {
      &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      NULLP,
      NULLP
   }, /* 32 */
   {
      &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      NULLP,
      NULLP
   }, /* 33 */
   {
      &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      NULLP,
      NULLP
   }, /* 34 */
   {
      &szE_RABItem,
      NULLP,
      NULLP,
      NULLP
   }, /* 35 */
   {
      &szE_RABToBeMdfdItemBrModReq,
      NULLP,
      NULLP,
      NULLP
   }, /* 36 */
   {
      &szE_RABMdfyItemBrModRes,
      NULLP,
      NULLP,
      NULLP
   }, /* 37 */
   /* szE_RABRlsItem is Not used */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 38 */
   {
      &szE_RABSetupItemBrSURes,
      NULLP,
      NULLP,
      NULLP
   }, /* 39 */
   {
      &szSecurCntxt,
      NULLP,
      NULLP,
      NULLP
   }, /* 40 */
   {
      &szHovrRestrnLst,
      NULLP,
      NULLP,
      NULLP
   }, /* 41 */
   /* Following IE is not present in spec */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 42 */
   {
      &szUEPagID,
      NULLP,
      NULLP,
      NULLP
   }, /* 43 */
   {
      &szPagDRX,
      NULLP,
      NULLP,
      NULLP
   }, /* 44 */
   /* Following IE is not present in spec */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 45 */
   {
      &szTAILst,
      &szProtIE_Field_TAIItemIEs,
      NULLP,
      NULLP
   }, /* 46 */
   {
      &szTAIItem,
      NULLP,
      NULLP,
      NULLP
   }, /* 47 */
   {
      &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      NULLP,
      NULLP
   }, /* 48 */
   /* szE_RABRlsItemHOCmd is Not used */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 49 */
   {
      &szE_RABSetupItemCtxtSURes,
      &szProtIE_Field_E_RABSetupItemCtxtSUResIEs,
      NULLP,
      NULLP
   }, /* 50 */
   {
      &szE_RABSetupLstCtxtSURes,
      &szProtIE_Field_E_RABSetupItemCtxtSUResIEs,
      NULLP,
      NULLP
   }, /* 51 */
   {
      &szE_RABToBeSetupItemCtxtSUReq,
      NULLP,
      NULLP,
      NULLP
   }, /* 52 */
   {
      &szProtIE_ContLst_E_RABToBeSetupItemHOReqIEs,
      &szProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs,
      NULLP,
      NULLP
   }, /* 53 */
   /* Following IE is not present in spec */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 54 */
   /* szGERANtoLTEHOInformRes is Not used */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 55 */
   /* Following IE is not present in spec */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 56 */
   /* szUTRANtoLTEHOInformRes is Not used */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 57 */
   {
      &szCriticalityDiag,
      NULLP,
      NULLP,
      NULLP
   }, /* 58 */
   { 
      &szGlobal_ENB_ID,
      NULLP,
      NULLP,
      NULLP
   }, /* 59 */
   {
      &szENBname,
      NULLP,
      NULLP,
      NULLP
   }, /* 60 */
   {
      &szMMEname,
      NULLP,
      NULLP,
      NULLP
   }, /* 61 */
   /* Following IE is not present in spec */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 62 */
   {
      &szSrvdPLMNs,
      &szTBCD_STRING,
      NULLP,
      NULLP
   }, /* 63 */
   {
      &szSuppTAs,
      &szSuppTAs_Item,
      NULLP,
      NULLP
   }, /* 64 */
   {
      &szTimeToWait,
      NULLP,
      NULLP,
      NULLP
   }, /* 65 */
   {
      &szUEAggMaxBitrate,
      NULLP,
      NULLP,
      NULLP
   }, /* 66 */
   {
      &szTAI,
      NULLP,
      NULLP,
      NULLP
   }, /* 67 */
   /* Following IE is not present in spec */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 68 */
   {
      &szE_RABRlsLstBrRelComp,
      &szProtIE_Field_E_RABRlsItemBrRelCompIEs,
      NULLP,
      NULLP
   }, /* 69 */
   {
      &szCdma2000PDU,
      NULLP,
      NULLP,
      NULLP
   }, /* 70 */
   {
      &szCdma2000RATTyp,
      NULLP,
      NULLP,
      NULLP
   }, /* 71 */
   {
      &szCdma2000SectorID,
      NULLP,
      NULLP,
      NULLP
   }, /* 72 */
   {
      &szSecurKey,
      NULLP,
      NULLP,
      NULLP
   }, /* 73 */
   {
      &szUERadioCapblty,
      NULLP,
      NULLP,
      NULLP
   }, /* 74 */
   {
      &szGUMMEI,
      NULLP,
      NULLP,
      NULLP
   }, /* 75 */
   /* Following 2 IEs is not present in spec */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 76 */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 77 */
   {
      &szE_RABInformLstItem,
      NULLP,
      NULLP,
      NULLP
   }, /* 78 */
   {
      &szDirect_Fwding_Path_Avlblty,
      NULLP,
      NULLP,
      NULLP
   }, /* 79 */
   {
      &szUEIdentityIdxValue,
      NULLP,
      NULLP,
      NULLP
   }, /* 80 */
   /* Following 2 IEs is not present in spec */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 81 */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 82 */
   {
      &szCdma2000HOStatus,
      NULLP,
      NULLP,
      NULLP
   }, /* 83 */
   {
      &szCdma2000HOReqdInd,
      NULLP,
      NULLP,
      NULLP
   }, /* 84 */
   /* Following IE is not present in spec */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 85 */
   {
      &szE_UTRAN_Trace_ID,
      NULLP,
      NULLP,
      NULLP
   }, /* 86 */
   {
      &szRelativeMMECapacity,
      NULLP,
      NULLP,
      NULLP
   }, /* 87 */
   {
      &szMME_UE_S1AP_ID,
      NULLP,
      NULLP,
      NULLP
   }, /* 88 */
   {
      &szBrs_SubjToStatusTfr_Item,
      NULLP,
      NULLP,
      NULLP
   }, /* 89 */
   {
      &szENB_StatusTfr_TprntCont,
      NULLP,
      NULLP,
      NULLP
   }, /* 90 */
   {
      &szUE_assocLogS1_ConItem,
      NULLP,
      NULLP,
      NULLP
   }, /* 91 */
   {
      &szResetTyp,
      NULLP,
      NULLP,
      NULLP
   }, /* 92 */
   {
      &szUE_assocLogS1_ConLstResAck,
      &szProtIE_Field_UE_assocLogS1_ConItemResAck,
      NULLP,
      NULLP
   }, /* 93 */
   {
      &szE_RABToBeSwedULItem,
      NULLP,
      NULLP,
      NULLP
   }, /* 94 */
   {
      &szE_RABToBeSwedULLst,
      &szProtIE_SingleCont_E_RABToBeSwedULItemIEs,
      NULLP,
      NULLP
   }, /* 95 */
   {
      &szS_TMSI,
      NULLP,
      NULLP,
      NULLP
   }, /* 96 */
   {
      &szCdma2000OneXRAND,
      NULLP,
      NULLP,
      NULLP
   }, /* 97 */
   {
      &szRqstTyp,
      NULLP,
      NULLP,
      NULLP
   }, /* 98 */
   {
      &szUE_S1AP_IDs,
      NULLP,
      NULLP,
      NULLP
   }, /* 99 */
   {
      &szEUTRAN_CGI,
      NULLP,
      NULLP,
      NULLP
   }, /* 100 */
   {
      &szOverloadResp,
      NULLP,
      NULLP,
      NULLP
   }, /* 101 */
   {
      &szCdma2000OneXSRVCCInfo,
      NULLP,
      NULLP,
      NULLP
   }, /* 102 */
   /* szE_RABFailedToBeRlsdLst is Not used */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 103 */
   {
      &szSrc_ToTget_TprntCont,
      NULLP,
      NULLP,
      NULLP
   }, /* 104 */
   {
      &szSrvdGUMMEIs,
      &szSrvdGUMMEIsItem,
      NULLP,
      NULLP
   }, /* 105 */
   {
      &szSubscriberProfileIDforRFP,
      NULLP,
      NULLP,
      NULLP
   }, /* 106 */
   {
      &szUESecurCapabilities,
      NULLP,
      NULLP,
      NULLP
   }, /* 107 */
   {
      &szCSFallbackIndicator,
      NULLP,
      NULLP,
      NULLP
   }, /* 108 */
   {
      &szCNDomain,
      NULLP,
      NULLP,
      NULLP
   }, /* 109 */
   {
      &szE_RABLst,
      &szProtIE_Field_E_RABItemIEs,
      NULLP,
      NULLP
   }, /* 110 */
   {
      &szMsgIdentifier,
      NULLP,
      NULLP,
      NULLP
   }, /* 111 */
   {
      &szSerialNumber,
      NULLP,
      NULLP,
      NULLP
   }, /* 112 */
   {
      &szWarningAreaLst,
      NULLP,
      NULLP,
      NULLP
   }, /* 113 */
   {
      &szRepetitionPeriod,
      NULLP,
      NULLP,
      NULLP
   }, /* 114 */
   {
      &szNumberofBroadcastRqst,
      NULLP,
      NULLP,
      NULLP
   }, /* 115 */
   {
      &szWarningTyp,
      NULLP,
      NULLP,
      NULLP
   }, /* 116 */
   {
      &szWarningSecurInfo,
      NULLP,
      NULLP,
      NULLP
   }, /* 117 */
   {
      &szDataCodingScheme,
      NULLP,
      NULLP,
      NULLP
   }, /* 118 */
   {
      &szWarningMsgContents,
      NULLP,
      NULLP,
      NULLP
   }, /* 119 */
   {
      &szBroadcastCompletedAreaLst,
      NULLP,
      NULLP,
      NULLP
   }, /* 120 */
   {
      &szInter_SystemInformTfrTyp,
      NULLP,
      NULLP,
      NULLP
   }, /* 121 */
   {
      &szInter_SystemInformTfrTyp,
      NULLP,
      NULLP,
      NULLP
   }, /* 122 */
   {
      &szTget_ToSrc_TprntCont,
      NULLP,
      NULLP,
      NULLP
   }, /* 123 */
   {
      &szSRVCCOperationPossible,
      NULLP,
      NULLP,
      NULLP
   }, /* 124 */
   {
      &szSRVCCHOInd,
      NULLP,
      NULLP,
      NULLP
   }, /* 125 */
   /* szNAS_DlnkCount is Not used */
   {
      NULLP,
      NULLP,
      NULLP,
      NULLP
   }, /* 126 */
   {
      &szCSG_Id,
      NULLP,
      NULLP,
      NULLP
   }, /* 127 */
   {
      &szCSG_IdLst,
      &szCSG_IdLst_Item,
      NULLP,
      NULLP
   }, /* 128 */
   {
      &szSONConfigTfr,
      NULLP,
      NULLP,
      NULLP
   }, /* 129 */
   {
      &szSONConfigTfr,
      NULLP,
      NULLP,
      NULLP
   }, /* 130 */
   {
      &szTportLyrAddr,
      NULLP,
      NULLP,
      NULLP
   }, /* 131 */
   {
      &szMSClassmark2,
      NULLP,
      NULLP,
      NULLP
   }, /* 132 */
   {
      &szMSClassmark3,
      NULLP,
      NULLP,
      NULLP
   }, /* 133 */
   {
      &szRRC_Establishment_Cause,
      NULLP,
      NULLP,
      NULLP
   }, /* 134 */
   {
      &szNASSecurParamsfromE_UTRAN,
      NULLP,
      NULLP,
      NULLP
   }, /* 135 */
   {
      &szNASSecurParamstoE_UTRAN,
      NULLP,
      NULLP,
      NULLP
   }, /* 136 */
   {
      &szPagDRX,
      NULLP,
      NULLP,
      NULLP
   }, /* 137 */
   {
      &szSrc_ToTget_TprntCont,
      NULLP,
      NULLP,
      NULLP
   }, /* 138 */
   {
      &szTget_ToSrc_TprntCont,
      NULLP,
      NULLP,
      NULLP
   }, /* 139 */
};
#endif


/**********************************************************************

         End of file:     sq_dbr8.c@@/main/1 - Mon Jan 10 22:16:53 2011

**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---        pkaX   1. Updated for S1AP release 3.1
/main/1     sz001.301   pkaX   1. Initialize the error code in user escape 
                                  function.
/main/1     sz006.301   ve     1. DB Warning fixes.
/main/1     sz008.301 akaranth 1. support for Source RNC to Target RNC Transparent container.
*********************************************************************91*/
