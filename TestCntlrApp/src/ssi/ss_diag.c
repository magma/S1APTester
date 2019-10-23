

/********************************************************************20**
 
     Name:     System Services -- Logging functions
 
     Type:     C source file
 
     Desc:     Source code for System Services Logging.
 
     File:     
 
     Sid:      ss_diag.c@@/main/TeNB_Main_BR/3 - Mon Aug 11 16:43:46 2014
 
     Prg:      pakumar
  
*********************************************************************21*/


/* header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "mt_ss.h"

/* header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */
#include "ss_diag.h"        /* Common log file */
 
/**
 *  @brief Private functions forward declarations 
 */
PRIVATE Void ssDiagInitBufEntMap ARGS((Void));
PRIVATE S16 ssGetLogBufIdx ARGS((SsDiagCirBuf *bufPtr, SsDiagBuf **trgBufPtr));

/** 
 * @brief Global declarations 
 */
PUBLIC U8  ssDiagBufEntMap[SS_MAX_ENT][SS_MAX_INST];
PUBLIC     SsDiagCirBuf ssDiagCirLogBuf[SS_DIAG_MAX_CIRC_BUF];
PUBLIC U32 numTti = 0;
PUBLIC     SsDiagCirBuf ssDiagCirVarBuf[SS_DIAG_NUM_CIRBUF_UARM]; 

/**
 *  @brief  This function initializes the log buffer with respect to
 *  entity and instance. 
 *
 *  @details  This function initializes the log buffer with respect to
 *  entity and instance. 
 *
 *  Function:ssDiagInitBufEntMap
 *
 *  @param[in]  Void      
 *
 *  @return S16          
 *        -# ROK     - successful.
 *        -# RFAILED - failure.
 */
#ifdef ANSI
PRIVATE Void ssDiagInitBufEntMap
(
 Void
)
#else
PRIVATE Void ssDiagInitBufEntMap(Void)
#endif
{
   TRC1(ssDiagInitBufEntMap);


#ifdef MSPD
   ssDiagBufEntMap[ENTSZ][SS_DIAG_INST0] = SS_DIAG_BUF1;
   ssDiagBufEntMap[ENTSB][SS_DIAG_INST0] = SS_DIAG_BUF2;
   ssDiagBufEntMap[ENTNH][SS_DIAG_INST0] = SS_DIAG_BUF1;
   ssDiagBufEntMap[ENTSM][SS_DIAG_INST0] = SS_DIAG_BUF3;
   ssDiagBufEntMap[ENTCZ][SS_DIAG_INST0] = SS_DIAG_BUF1;
   ssDiagBufEntMap[ENTHI][SS_DIAG_INST0] = SS_DIAG_BUF4;
   ssDiagBufEntMap[ENTEG][SS_DIAG_INST0] = SS_DIAG_BUF1;
   ssDiagBufEntMap[ENTWR][SS_DIAG_INST0] = SS_DIAG_BUF1;

   ssDiagBufEntMap[ENTYS][SS_DIAG_INST0] = SS_DIAG_BUF5;
   ssDiagBufEntMap[ENTTF][SS_DIAG_INST0] = SS_DIAG_BUF6;
   ssDiagBufEntMap[ENTRG][SS_DIAG_INST1] = SS_DIAG_BUF6;
   ssDiagBufEntMap[ENTRG][SS_DIAG_INST0] = SS_DIAG_BUF5;
   ssDiagBufEntMap[ENTKW][SS_DIAG_INST0] = SS_DIAG_BUF5;
   ssDiagBufEntMap[ENTPJ][SS_DIAG_INST0] = SS_DIAG_BUF5;
#else
   ssDiagBufEntMap[ENTSZ][SS_DIAG_INST0] = SS_DIAG_BUF1;
   ssDiagBufEntMap[ENTSB][SS_DIAG_INST0] = SS_DIAG_BUF2;
   ssDiagBufEntMap[ENTNH][SS_DIAG_INST0] = SS_DIAG_BUF1;
   ssDiagBufEntMap[ENTSM][SS_DIAG_INST0] = SS_DIAG_BUF3;
   ssDiagBufEntMap[ENTCZ][SS_DIAG_INST0] = SS_DIAG_BUF1;
   ssDiagBufEntMap[ENTHI][SS_DIAG_INST0] = SS_DIAG_BUF4;
   ssDiagBufEntMap[ENTEG][SS_DIAG_INST0] = SS_DIAG_BUF5;
   ssDiagBufEntMap[ENTWR][SS_DIAG_INST0] = SS_DIAG_BUF1;
 
   ssDiagBufEntMap[ENTYS][SS_DIAG_INST0] = SS_DIAG_BUF6;
   ssDiagBufEntMap[ENTTF][SS_DIAG_INST0] = SS_DIAG_BUF6;
   ssDiagBufEntMap[ENTRG][SS_DIAG_INST0] = SS_DIAG_BUF6;
   ssDiagBufEntMap[ENTRG][SS_DIAG_INST1] = SS_DIAG_BUF6;
   ssDiagBufEntMap[ENTKW][SS_DIAG_INST0] = SS_DIAG_BUF6;
   ssDiagBufEntMap[ENTPJ][SS_DIAG_INST0] = SS_DIAG_BUF6;
#endif

   RETVOID;
}/* end of ssDiagInitBufEntMap */
 
/**
 *    @brief  This function initializes SSI logging Fix circular buffers.
 *    @details  This function initializes SSI logging circular buffers.
 *
 *    Function:ssDiagInitCircBuf
 *
 *    @param[in]  ssSysTstId
 *    @param[in]  maxBufLen
 *
 *    @return S16
 *         -# ROK     - successful.
 *         -# RFAILED - failure.
 */
#ifdef ANSI
PUBLIC S16 ssDiagInitFixCircBuf
(
U32          ssSysTstId,
U16          maxBufLen
)
#else
PUBLIC S16 ssDiagInitFixCircBuf(ssSysTstId, maxBufLen)
U32          ssSysTstId;
U16          maxBufLen;
#endif
{
SsDiagCirBuf *bufPtr;
   TRC1(ssDiagInitCircBuf);

   /* Initialize the entity buffer ID mapping  */
   ssDiagInitBufEntMap();
   if(ssSysTstId >= SS_DIAG_MAX_CIRC_BUF)
   {
      RETVALUE(RFAILED);
   }
   bufPtr = &ssDiagCirLogBuf[ssSysTstId];
   bufPtr->rear = 0;
   bufPtr->front = 0;
   bufPtr->nLen = maxBufLen;
   bufPtr->logLostState = 0;
   bufPtr->logBuf = NULLP;

   /* allocate Buffer for storing logging information */
   SGetSBuf(DFLT_REGION, DFLT_POOL, (Data **)&(bufPtr->logBuf), 
            (sizeof(SsDiagBuf) * maxBufLen));
   if(bufPtr->logBuf == NULLP)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* end of ssDiagInitCircBuf */ 

/**
 *    @brief  This function initializes SSI logging Var circular buffers.
 *    @details  This function initializes SSI logging circular buffers.
 *
 *    Function:ssDiagInitCircBuf
 *
 *    @param[in]  ssSysTstId
 *    @param[in]  maxBufLen
 *
 *    @return S16
 *         -# ROK     - successful.
 *         -# RFAILED - failure.
 */
#ifdef ANSI
PUBLIC S16 ssDiagInitVarCircBuf
(
U32          ssSysTstId,
U16          maxBufLen
)
#else
PUBLIC S16 ssDiagInitVarCircBuf(ssSysTstId, maxBufLen)
U32          ssSysTstId;
U16          maxBufLen;
#endif
{
   SsDiagCirBuf *bufPtr;
   TRC1(ssDiagInitCircBuf);

   /* Initialize the entity buffer ID mapping  */
   ssDiagInitBufEntMap();
   if(ssSysTstId >= SS_DIAG_NUM_CIRBUF_UARM)
   {
      RETVALUE(RFAILED);
   }
   bufPtr = &ssDiagCirVarBuf[ssSysTstId];
   bufPtr->rear = 0;
   bufPtr->front = 0;
   bufPtr->nLen = maxBufLen;
   bufPtr->logLostState = 0;
   bufPtr->logBuf = NULLP;

   /* allocate Buffer for storing logging information */
   SGetSBuf(DFLT_REGION, DFLT_POOL, (Data **)&(bufPtr->logBuf), 
            (sizeof(SsDiagVarBuf) * maxBufLen));
   if(bufPtr->logBuf == NULLP)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* end of ssDiagInitCircBuf */
 
/**
 *   @brief  This function provides the index to place the log in the circular
 *           buffer.
 *
 *   @details This function provides the index to place the log in the circular
 *            buffer.
 *    Function:ssGetLogBufIdx
 *
 *   @param[in]  bufPtr
 *   @param[in]  trgBufPtr
 *
 *   @return S16
 *        -# ROK     - successful.
 *        -# RFAILED - failure.
 */
#ifdef ANSI
PRIVATE S16 ssGetLogBufIdx
(
 SsDiagCirBuf *bufPtr,
 SsDiagBuf    **trgBufPtr
)
#else
PRIVATE S16 ssGetLogBufIdx (bufPtr, trgBufPtr)
SsDiagCirBuf *bufPtr;
SsDiagBuf    **trgBufPtr;
#endif
{
   TRC1(ssGetLogBufIdx);
   
   /* Check for space in Circular Buffer */
   if(bufPtr->front == ((bufPtr->rear + SS_DIAG_MIN_BUF_DIFF) % bufPtr->nLen))
   {
      bufPtr->logLostState = SS_DIAG_RPTPEND;
      bufPtr->noLogLost++;
      RETVALUE(RFAILED);
   }

   /* Check and report if any logs lost */
   if(bufPtr->noLogLost > 0)
   {
      bufPtr->rear = ((++bufPtr->rear) % bufPtr->nLen);
      bufPtr->logBuf[bufPtr->rear].type = SS_DIAG_MSG_TYPE_NOLOGLOST;
      bufPtr->logBuf[bufPtr->rear].arg1 = bufPtr->noLogLost;
      SS_DIAG_GET_TIME_STAMP(bufPtr->logBuf[bufPtr->rear].timRef);

      bufPtr->noLogLost = 0;
      bufPtr->logLostState = SS_DIAG_REPORTED;
      if(bufPtr->front == ((bufPtr->rear + SS_DIAG_MIN_BUF_DIFF) % bufPtr->nLen))
      {
         bufPtr->noLogLost++;
         RETVALUE(RFAILED);
      }
   }

   /* Get the log record for pointed by the rear pointer */
   *trgBufPtr = &(bufPtr->logBuf[bufPtr->rear]);
   bufPtr->rear = ((++bufPtr->rear) % bufPtr->nLen);

   if(bufPtr->logLostState == SS_DIAG_REPORTED)
   {
      bufPtr->logLostState = SS_DIAG_NORMAL;
   }
 
   RETVALUE(ROK);
} /* end of ssGetLogBufIdx */
 
/**
 *    @brief  This function stores log information in the index pointed by the rear
 *            pointer in Circular Buffer.
 *
 *    @details  This function stores log information in the index pointed by the rear
 *              pointer in Circular Buffer.
 *    Function: ssDiagFix
 *
 *    @param[in]  tknId
 *    @param[in]  splArgEnum
 *    @param[in]  entId
 *    @param[in]  instId
 *    @param[in]  logLvl
 *    @param[in]  logType
 *    @param[in]  splArg
 *    @param[in]  arg1
 *    @param[in]  arg2
 *    @param[in]  arg3
 *    @param[in]  arg4
 *    @param[in]  *string
 *
 *    @return Void
 */
#ifdef ANSI
PUBLIC Void ssDiagFix 
(
U32   tknId,
U32   splArgEnum,
U32   entId,
U32   instId,
U32   logLvl,
U32   logType,
U32   splArg,
U32   arg1,
U32   arg2,
U32   arg3,
U32   arg4,
S8    *string
)
#else
PUBLIC Void ssDiagFix(tknId, splArgEnum, entId, instId, logLvl, logType, splArg, arg1, arg2, arg3, arg4, *string)
U32   tknId;
U32   splArgEnum,
U32   entId;
U32   instId;
U32   logLvl;
U32   logType;
U32   splArg;
U32   arg1;
U32   arg2;
U32   arg3;
U32   arg4;
S8    *string;
#endif
{
   TRC1(ssDiagFix);

   SsDiagBuf    *tmpRecBuf = NULLP;
   SsDiagCirBuf *bufPtr = &ssDiagCirLogBuf[ssDiagBufEntMap[entId][instId]];
   S16         ret;

   /* Get the index for the log placing in the circular Q */
   ret = ssGetLogBufIdx(bufPtr, &tmpRecBuf);
   if((ret != ROK) || (tmpRecBuf == NULLP))
   {
      /* Return by dropping the log if we don't have any place to hold log */
      RETVOID;
   }

   /* Get the time stamp or time reference */
   SS_DIAG_GET_TIME_STAMP(tmpRecBuf->timRef);

   /* Store the logs in the index pointed by the rear pointer */
   tmpRecBuf->tknId   = tknId;
   tmpRecBuf->entInstId   = entId;
   tmpRecBuf->entInstId <<= 16;
   tmpRecBuf->entInstId  = (tmpRecBuf->entInstId | instId);
   tmpRecBuf->level   = logLvl;
   tmpRecBuf->type    = logType;
   tmpRecBuf->splArg  = splArg;
   tmpRecBuf->arg1    = arg1;
   tmpRecBuf->arg2    = arg2;
   tmpRecBuf->arg3    = arg3;
   tmpRecBuf->arg4    = arg4;
   tmpRecBuf->isValid = TRUE;

   RETVOID;
} /* end of ssDiagFix */
 
/**
 *    @brief  This function stores Varible log information in the index pointed by the rear
 *            pointer in Circular Buffer.
 *
 *    @details This function stores Varible log information in the index pointed by the rear
 *             pointer in Circular Buffer.
 *
 *    Function: ssDiagVarible
 *
 *    @param[in]  entId
 *    @param[in]  instId
 *    @param[in]  logLvl
 *    @param[in]  logType
 *    @param[in]  tknId
 *    @param[in]  splArg
 *    @param[in]  string[]
 *
 *    @return Void
 *        -# ROK     - success.
 *        -# RFAILED - failure.
 */
#ifdef ANSI
PUBLIC Void ssDiagVarible 
(
U32   entId,
U32   instId,
U32   logLvl,
U32   logType,
U32   tknId,
U32   splArg,
S8    string[]
)
#else
PUBLIC Void ssDiagVarible(entId, instId, logLvl, logType, tknId, splArg, string[])
U32   entId;
U32   instId;
U32   logLvl;
U32   logType;
U32   tknId;
U32   splArg;
S8    string[];
#endif
{
   TRC1(ssDiagVarible);

   SsDiagVarBuf *trgBufPtr;
   SsDiagCirBuf *bufPtr;
   U16          varLen = 0;

   bufPtr = &ssDiagCirVarBuf[ssDiagBufEntMap[entId][instId]];
   if(bufPtr->front == (((bufPtr->rear)+1) % bufPtr->nLen))
   {
      RETVOID;
   }


   /* Get the log record for pointed by the rear pointer */
   trgBufPtr = (SsDiagVarBuf *)(&(bufPtr->logBuf[bufPtr->rear]));
   bufPtr->rear = ((++bufPtr->rear) % bufPtr->nLen);


   if (trgBufPtr->isValid == FALSE)
   {
      varLen = strlen(string);
      if (varLen < SS_DIAG_VAR_BUF_LEN)
      {
         strcpy((char *)(trgBufPtr->varStr), string);
         trgBufPtr->isValid = TRUE;
      }

   }
   /* Insert information into fixed buffer so, writer thread can pick it up */
   ssDiagFix(tknId, 0, entId, instId, logLvl, logType, splArg, varLen, (U32)trgBufPtr, 0, 0, NULL);

} /* end of ssDiagVarible */ 

/*
 *   @brief  This function will unpack the buffer in the upper arm posted from
 *           lower arm.
 *
 *   @detail This function will be called at the upper arm whenever it will
 *           receive any buffer posted to it. Here it will unpack the buffer
 *           and put all the stuffs to the circular buffer.
 *   Function: ssDiagUnPackLogs        
 *
 *   @param[in]  mBuf 
 *
 *   @return S16
 *        -# ROK     - success.
 *        -# RFAILED - failure.
 */

#ifdef ANSI
PUBLIC S16 ssDiagUnPackLogs
(
 Buffer *mBuf
)
#else
PUBLIC S16 ssDiagUnPackLogs (mBuf)
Buffer *mBuf;
#endif
{
   TRC1(ssDiagUnPackLogs);

   U16          cnt = 0;
   U32          idx ;
   U16          bufType = 0;
   SsDiagCirBuf  *tmpLogBuf;
   S16          ret;
   U8           pkArray[4];
   U16          bytCnt = 0;

   /* Validate the buffer received by the SSI */
   if(mBuf == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /* Unpack the Circular Buffer Type */
   ret = SRemPreMsgMult(pkArray, sizeof(U16), mBuf);
   SS_UNPKU16(bufType);
   bytCnt = 0;

   /* Unpack the number of logs present in mBuf */
   ret = SRemPreMsgMult(pkArray, sizeof(U16), mBuf);
   SS_UNPKU16(cnt);
   if(cnt != 0)
   {
      tmpLogBuf = &(ssDiagCirLogBuf[bufType + SS_DIAG_NUM_CIRBUF_UARM]);
      for (idx = 0; idx < cnt; idx++)
      {
         /* Unpack the log information from mBuf. SRemPstMsgMult is used to
          * unpack the logs in the same format of log generation */
         ret = SRemPstMsgMult((Data*)&(tmpLogBuf->logBuf[tmpLogBuf->rear]),
                              (sizeof(SsDiagBuf) - sizeof(U32)), mBuf);
         if(ret != ROK)
         {
            RETVALUE(RFAILED);
         }
         /* Increment the CBuf rear pointer, after coping the log information 
          * into CBuf from mBuf */
         tmpLogBuf->rear = ((tmpLogBuf->rear + 1) % tmpLogBuf->nLen);
      }
   }

   /* Free the mBuf before returning */
   SPutMsg(mBuf);
   RETVALUE(ROK);
} /* end of ssDiagUnPackLogs */

