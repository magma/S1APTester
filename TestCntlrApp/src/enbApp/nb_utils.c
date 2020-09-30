/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file

    Desc:  C source code for ENODEB Application

    File:  nb_utils.c
               
    Sid:   

    Prg:   

**********************************************************************/

/* header include files (.h) */

#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_smm_init.h"
#include "nb_utils.h"
#include "nb_log.h"

PUBLIC S16 nbUtlGetPlmnId
(
NbPlmnId                     *plmnId,
SztPLMNidentity              *plmnIe
);
/**
 *  @brief This function fills the token and value for an tknU8 datatype
 *
 *      Function: nbFillTknU8
 *
 *          Processing steps:
 *          - update token present field as TRUE
 *          - update the value received
 *
 *
 *  @param[out] encParam : pointer the tokenparameter
 *  @param[in]  val      : value to be updated
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 */
PUBLIC S16  nbFillTknU8
(
TknU8                        *encParam,
U8                           val
)
{
   encParam->pres = PRSNT_NODEF;
   encParam->val  = val;
   RETVALUE(ROK);
} /* end of nbFillTknU8 */ 

/**
 *  @brief This function fills the token and value for  TknU16 structure
 *
 *      Function: nbFillTknU16
 *
 *          Processing steps:
 *          - update token present field as TRUE
 *          - update the value received
 *
 *
 *  @param[out] encParam : pointer the tokenparameter
 *  @param[in]  val      : value to be updated
 *  @return  ROK
 */
PUBLIC S16  nbFillTknU16
(
TknU16                       *encParam,
U16                          val
)
{
   encParam->pres = PRSNT_NODEF;
   encParam->val  = val;
   RETVALUE(ROK);
                                    
}/* end of nbFillTknU16 */

/**
 *  @brief This function fills the token and value for  TknS32 structure
 *
 *      Function: nbFillTknS32
 *
 *          Processing steps:
 *          - update token present field as TRUE
 *          - update the value received
 *
 *
 *  @param[out] encParam : pointer the tokenparameter
 *  @param[in]  val      : value to be updated
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 */

PUBLIC S16  nbFillTknS32
(
TknS32                         *encParam,
S32                            val
)
{
   encParam->pres = PRSNT_NODEF;
   encParam->val  = val;
   RETVALUE(ROK);
} /* end of nbFillTknS32 */

/**
 *  @brief This function fills the token and value for  TknU32 structure
 *
 *      Function: nbFillTknU32
 *
 *          Processing steps:
 *          - update token present field as TRUE
 *          - update the value received
 *
 *
 *  @param[out] encParam : pointer the tokenparameter
 *  @param[in]  val      : value to be updated
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 */

PUBLIC S16  nbFillTknU32
(
TknU32                         *encParam,
U32                            val
)
{
   encParam->pres = PRSNT_NODEF;
   encParam->val  = val;
   RETVALUE(ROK);
} /* end of nbFillTknU32 */

/**
 *  @brief This function fills the structure TknStrOSXL
 *
 *      Function: nbFillTknStrOSXL
 *
 *          Processing steps:
 *          - allocate memory to val in TknStrOSXL
 *          - update token present field as TRUE
 *          - update the memory with the value  received
 *
 *
 *  @param[out] ptr  : TknStrOSXL stucture pointer to be updated
 *  @param[in]  len  : length for which memory to allocated
 *  @param[in]  val  : value getting updated
 *  @param[in]  mem  : pointer to memCp
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 *          RFAILED
 */
PUBLIC S16 nbFillTknStrOSXL
(
TknStrOSXL                   *ptr,
U16                          len,
Data                         *val,
CmMemListCp                  *mem
)
{
   U16                       idx;

   /* make the element as present */
   ptr->pres = TRUE;
   ptr->len =  len;

   if (cmGetMem(mem, len * sizeof(U8), (Ptr *)&ptr->val) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmGetMem failed");
      RETVALUE(RFAILED);
   }

   for(idx = 0; idx < len; idx++)
   {
      ptr->val[idx] = val[idx];
   }

   RETVALUE(ROK);
}

/**
 *  @brief This function  Retrieve U32 from Str4 token string.
 *
 *      Function: nbGetU32FrmTknStr4
 *
 *          Processing steps:
 *           - Convert token str4 to U32
 *
 *  @param[out] val : pointer to value
 *  @param[in]  ie  : pointer to token srting
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED 
 */

PUBLIC S16 nbGetU32FrmTknStr4
(
   U32                       *val,
   TknStr4                   *ie
)
{
   U8           len = ie->len;
   U8           idx;

   if (len > 4)
   {
      RETVALUE(RFAILED);
   }

   *val = 0;
   for (idx = 0; idx < len; idx++)
   {
      *val = (*val<< 8) + ie->val[idx];
   }
   RETVALUE(ROK);
}

 /**
 *  @brief This function  Retrieve U16 from Str4 token string.
 *
 *      Function: nbGetU16FrmTknStr4
 *
 *          Processing steps:
 *           - Convert token str4 to U16
 *
 *  @param[out] val : pointer to value
 *  @param[in]  ie  : pointer to token srting
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED 
 */

PUBLIC S16 nbGetU16FrmTknStr4
(
   U16                       *val,
   TknStr4                   *ie
)
{
   U8           len = ie->len;
   U8           idx;

   if (len > 2)
   {
      RETVALUE(RFAILED);
   }

   *val = 0;
   for (idx = 0; idx < len; idx++)
   {
      *val = (*val<< 8) + ie->val[idx];
   }
   RETVALUE(ROK);
}
/**
 *  @brief This function fills the Octet string of length less than 4
 *
 *      Function: nbFill2TknStr4
 *
 *          Processing steps:
 *          - if number of bytes more than four reurn failure
 *          - update token present field as TRUE
 *          - fill Byte string of specified length
 *
 *  @param[out] ptr  : TknStr4 stucture pointer to be updated
 *  @param[in]  len  : length of message to be updated
 *  @param[in]  val  : value getting updated
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 */
PUBLIC S16 nbFill2TknStr4
(
TknStr4                      *ptr,
U8                           len,
U8                           *val
)
{
   U8                        idx;

   /* make the element as present */
   ptr->pres = TRUE;

   if (len > 4)
   {
      RETVALUE(RFAILED);
   }
   else
   {
      ptr->len = (U8) len;
   }

   for(idx = 0; idx < len; idx++)
   {
      ptr->val[idx] = val[idx];
   }

   RETVALUE(ROK);
} /* end of wrFillTknStr4 */

/**
 *  @brief This function validate the two PLMNs are equal or not
 *
 *      Function: wrUtlPlmnsEqual
 *
 *          Processing steps:
 *          -  validate MCC, MNC size and MNC
 *          -  if matches 
 *             - return TRUE
 *          - else 
 *             - return FALSE
 *
 *  @param[in]  plmnId1 : PLMN1 to be validated
 *  @param[in]  plmnId2 : PLMN2 to be validated
 *  @return Bool
 */
PUBLIC Bool nbUtlPlmnsEqual
(
NbPlmnId                     *plmnId1,
NbPlmnId                     *plmnId2
)
{
   if ((plmnId1->mcc[0] != plmnId2->mcc[0]) ||
       (plmnId1->mcc[1] != plmnId2->mcc[1]) ||
       (plmnId1->mcc[2] != plmnId2->mcc[2]))
   {
      RETVALUE(FALSE);
   }
   if (plmnId1->numMncDigits != plmnId2->numMncDigits)
   {
      RETVALUE(FALSE);
   }
   if ((plmnId1->mnc[0] != plmnId2->mnc[0]) ||
       (plmnId1->mnc[1] != plmnId2->mnc[1]))
   {
      RETVALUE(FALSE);
   }
   if (plmnId1->numMncDigits == 3)
   {
      if (plmnId1->mnc[2] != plmnId2->mnc[2])
      {
         RETVALUE(FALSE);
      }
   }
   RETVALUE(TRUE);
}

/**
 *  @brief This is an utility function to get NbPlmnID from the message
 *
 *      Function: nbUtlGetPlmnId
 *
 *          Processing steps:
 *          -  decode the PLMN from the message 
 *          - update it to the pointer provided
 *
 *  @param[out] plmnId : pointer to update the PLMN
 *  @param[in]  plmnIe : pointer to message containing PLMN IE
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 */
PUBLIC S16 nbUtlGetPlmnId
(
NbPlmnId                     *plmnId,
SztPLMNidentity              *plmnIe
)
{
    plmnId->mcc[0] = plmnIe->val[0] &0x0f;
    plmnId->mcc[1] = (plmnIe->val[0] &0xf0) >> 4;
    plmnId->mcc[2] = plmnIe->val[1] &0x0f;
    if ((plmnIe->val[1] & 0xf0) == 0xf0)
    {
       plmnId->numMncDigits = 2;
       plmnId->mnc[1]       = (plmnIe->val[2] & 0xf0) >> 4;
       plmnId->mnc[0]       = plmnIe->val[2] & 0x0f;
    }
    else
    {
       plmnId->numMncDigits = 3;
       plmnId->mnc[0]       = (plmnIe->val[1] & 0xf0) >> 4;
       plmnId->mnc[1]       = plmnIe->val[2] & 0x0f;
       plmnId->mnc[2]       = (plmnIe->val[2] & 0xf0) >> 4;
    }
  
    RETVALUE(ROK); 
}

PUBLIC S16 nbUtlFillPlmnId
(
NbPlmnId                     *plmnId,
SztPLMNidentity              *plmnIe
)
{
   U8      pLMNId[3];
   U16     idx;

   NB_ALLOC(&plmnIe->val, NB_PLMNID_IE_LEN * sizeof(U8));
   if (plmnIe->val == NULLP)
   {
      NB_LOG_ERROR(&nbCb,"Nb_ALLOC failed");
      RETVALUE(RFAILED);
   }

   plmnIe->pres = PRSNT_NODEF;
   plmnIe->len  = NB_PLMNID_IE_LEN;

   pLMNId[0] =(((plmnId->mcc[1])<<4) | (plmnId->mcc[0]));
   if (plmnId->numMncDigits == 2)
   {
      pLMNId[1] =((0xf0) | (plmnId->mcc[2]));
      pLMNId[2] =(((plmnId->mnc[1])<<4) | (plmnId->mnc[0]));
   }
   else
   {
      pLMNId[1] =(((plmnId->mnc[0])<<4) | (plmnId->mcc[2]));
      pLMNId[2] =(((plmnId->mnc[2])<<4) | (plmnId->mnc[1]));
   }

   for(idx = 0; idx < plmnIe->len; idx++)
   {
      plmnIe->val[idx] = pLMNId[idx];
   }

   RETVALUE(ROK);
}

PUBLIC U32 nbUtlGetTeid
(
TknStrOSXL                   *ie
)
{
   U32                       teid;

   teid = ie->val[0];
   teid = (teid << 8) | (ie->val[1]);
   teid = (teid << 8) | (ie->val[2]);
   teid = (teid << 8) | (ie->val[3]);

   RETVALUE(teid);
}

PUBLIC S16 nbUtlGetTportAddr
(
TknStrBSXL                   *ie,
CmTptAddr                    *addr
)
{
   U32                       idx;
   switch(ie->len)
   {
      case 32:
      {
         addr->u.ipv4TptAddr.address = 0;
         addr->type = CM_TPTADDR_IPV4;
         for (idx = 0; idx < 4; idx++)
         {
            addr->u.ipv4TptAddr.address <<= 8;
            addr->u.ipv4TptAddr.address |= (U32)ie->val[idx];
         }
         RETVALUE(ROK);
      }
   }
   RETVALUE(RFAILED);
}

/**
 *  @brief This function copies the plmn information
 *
 *      Function: nbUtlCopyPlmnId
 *
 *          Processing steps:
 *          - copy the values from plmn1 to plmn2
 *
 *  @param[in]   plmnId1 : source plmn id
 *  @param[out]  plmnId2 : target plmn id
 *  @return S16  ROK
 */
PUBLIC S16 nbUtlCopyPlmnId
(
NbPlmnId                     *plmn1,
NbPlmnId                     *plmn2
)
{
   plmn2->numMncDigits  = plmn1->numMncDigits;
   plmn2->mcc[0]  = plmn1->mcc[0];
   plmn2->mcc[1]  = plmn1->mcc[1];
   plmn2->mcc[2]  = plmn1->mcc[2];
   plmn2->mnc[0]  = plmn1->mnc[0];
   plmn2->mnc[1]  = plmn1->mnc[1];
   if(plmn1->numMncDigits > 2)
   {
      plmn2->mnc[2] = plmn1->mnc[2];
   }
   else
   {
      plmn2->mnc[2] = 0;
   }
   RETVALUE(ROK);
}
/** @brief This function fills the S1AP EnodeB Global ID IE.
 *  *
 *   * @details This function fills the S1AP:EnodeB Global ID IE.
 *    *
 *     *     Function: wrEmmMmeSztFillS1eNBId 
 *      *
 *       * @param[in]     pdu: S1AP PDU.
 *        * @param[in] enbType: EnodeB type.
      *         * @param[in]     cgi: CGI  
 *          * @param[in]  plmnId: PLMN ID IE.
 *           * @param[out]  enbIe: S1AP global eNodeB ID IE 
 *            * @return  S16
 *             *        -# Success : ROK
 *              */
PUBLIC S16 nbSztFillS1eNBId
(
 S1apPdu                      *pdu,
 U32                          enbType,
 U32                          cgi,
 NbPlmnId                     *plmnId,
 SztGlobal_ENB_ID             *enbIe
 )
{
   U32                       enbId = (cgi & 0x0fffffff);
   nbFillTknU8(&(enbIe->pres), PRSNT_NODEF);
   nbSztFillPLMNId(pdu,plmnId, &enbIe->pLMNidentity);
   nbFillTknU8(&(enbIe->eNB_ID.choice), enbType);
   switch(enbType)
   {
      case ENB_ID_HOMEENB_ID:
         {
            enbIe->eNB_ID.val.homeENB_ID.pres = PRSNT_NODEF;
            enbIe->eNB_ID.val.homeENB_ID.len = 28;
            nbFillTknBStr32(&(enbIe->eNB_ID.val.homeENB_ID), 28, enbId);
         }
         break;
      case ENB_ID_MACROENB_ID:
         {
            enbIe->eNB_ID.val.macroENB_ID.pres = PRSNT_NODEF;
            enbIe->eNB_ID.val.macroENB_ID.len = 20;
            nbFillTknBStr32(&(enbIe->eNB_ID.val.macroENB_ID), 20, enbId);
         }
         break;
      default:
         {
            NB_LOG_ERROR(&nbCb,"Invalid Enodeb Type");
         }
         break;
   }
   enbIe->iE_Extns.noComp.pres = NOTPRSNT;
   RETVALUE(ROK);
} /* end of nbSztFillS1eNBId */

/** @brief This function fills the S1AP PLMN ID IE.
 **
 * * @details This function fills the S1AP: PLMN ID IE.
 **
 **     Function: wrEmmMmeSztFillPLMNId
 * *
 *  * @param[in]     pdu: S1AP PDU.
 *   * @param[in]  plmnId: PLMN ID.
 *    * @param[out] plmnIe: S1AP PLMN ID IE. 
 *     * @return  S16
 *      *        -# Success : ROK
 **/

PUBLIC S16  nbSztFillPLMNId 
(
 S1apPdu                      *pdu,
 NbPlmnId                     *plmnId,
 SztPLMNidentity              *plmnIe
 )
{
   U8      pLMNId[3];

   NB_GET_MEM(pdu, NB_PLMNID_IE_LEN, &(plmnIe->val));
   plmnIe->pres = PRSNT_NODEF;
   plmnIe->len  = WR_PLMNID_IE_LEN;

   pLMNId[0] =(((plmnId->mcc[1])<<4) | (plmnId->mcc[0]));
   if (plmnId->numMncDigits == 2)
   {
      pLMNId[1] =((0xf0) | (plmnId->mcc[2]));
      pLMNId[2] =(((plmnId->mnc[1])<<4) | (plmnId->mnc[0]));
   }
   else
   {
      pLMNId[1] =(((plmnId->mnc[0])<<4) | (plmnId->mcc[2]));
      pLMNId[2] =(((plmnId->mnc[2])<<4) | (plmnId->mnc[1]));
   }

   /* make the element as present */
   nbFillTknStrOSXL(plmnIe, NB_PLMNID_IE_LEN, pLMNId, &(pdu->memCp));
   RETVALUE(ROK);
} 

/* end of nbEmmMmeSztFillPLMNId */
/**
 *  *  @brief This function fills the structure TknStr4U32
 *   *
 *    *      Function: nbFillTknStr32
 *     *
 *      *          Processing steps:
 *       *          - update token present field as TRUE
 *        *          - fill Bit string of specified length
 *         *
 *          *
 *           *  @param[out] ptr  : TknBStr32 stucture pointer to be updated
 *            *  @param[in]  len  : length of message to be updated
 *             *  @param[in]  val  : value getting updated
 *              *  @return S16
 *                  -# Success : ROK
 *                      -# Failure : RFAILED
 *                       *          RFAILED
 *                        */
PUBLIC Void  nbFillTknBStr32
(
 TknBStr32                    *ptr,
 U16                          len,
 U32                          val
 )
{
   U8                        idx;
   U8                        octets[4];

   /* make the element as present */
   if (len > 32)
   {
      return;
   }

   octets[0] = ((val << (32 - len)) & 0xff000000) >> 24;
   octets[1] = ((val << (32 - len)) & 0x00ff0000) >> 16;
   octets[2] = ((val << (32 - len)) & 0x0000ff00) >> 8;
   octets[3] = ((val << (32 - len)) & 0x000000ff);
   ptr->pres = TRUE;
   ptr->len  = len;
   for(idx = 0; idx < 4; idx++)
   {
      ptr->val[idx] = octets[idx];
   }

} /* end of nbFillTknBStr32 */

PUBLIC S16 nbCpyCmTptAddr 
(
 CmTptAddr                    *dst,
 CmTptAddr                    *src
 )
{
   if((src == NULLP) || (dst == NULLP))
   {
      NB_LOG_ERROR(&nbCb,"Src & Dst Invalid");
      RETVALUE(RFAILED);
   }

   dst->type = src->type;
   if(src->type == CM_INET_IPV4ADDR_TYPE)
   {
      dst->u.ipv4TptAddr.port = src->u.ipv4TptAddr.port;
      dst->u.ipv4TptAddr.address = src->u.ipv4TptAddr.address;
   }
   else if(src->type == CM_INET_IPV6ADDR_TYPE)
   {
      dst->u.ipv6TptAddr.port = src->u.ipv6TptAddr.port;
      cmMemcpy((U8*)dst->u.ipv6TptAddr.ipv6NetAddr, 
            (U8*)src->u.ipv6TptAddr.ipv6NetAddr, sizeof(CmInetIpAddr6));
   }

   RETVALUE( ROK);
} /* end of wrCpyCmTptAddr */ 

PUBLIC S16 nbSzGetIE
(
 SztS1AP_PDU                  *pdu,
 U32                          id,
 TknU8                        **ie
 )
{
   TknU8                     *currStr;
   TknU8                     *startStr;
   U8                        choiceType;
   U16                       numComp;
   U16                       recIdx;
   U32                       recId;
   U32                       procCode;
   U16                       size;

   /* Initialize the return pointer Tkn to NOTPRSNT */
   *ie     = NULLP;
   numComp = 0;
   recIdx  = 0; 

   if(pdu->choice.pres != PRSNT_NODEF)
   {
      RETVALUE(ROK);
   }

   choiceType = pdu->choice.val;

   /* Make start string point to the message in the PDU   */
   switch(choiceType)
   {
      case S1AP_PDU_INITIATINGMSG:
         {
            if (pdu->val.initiatingMsg.pres.pres != PRSNT_NODEF)
               RETVALUE(ROK);

            startStr  = (TknU8 *)(&(pdu->val.initiatingMsg.value.u));
            procCode  = pdu->val.initiatingMsg.procedureCode.val;
            break;
         }
      case S1AP_PDU_SUCCESSFULOUTCOME:
         {
            if (pdu->val.successfulOutcome.pres.pres != PRSNT_NODEF)
               RETVALUE(ROK);

            startStr  = (TknU8 *)(&(pdu->val.successfulOutcome.value.u));
            procCode  = pdu->val.successfulOutcome.procedureCode.val;
            break;
         }
      default: 
         {
            if ((pdu->val.unsuccessfulOutcome.pres.pres != PRSNT_NODEF) ||
                  (choiceType != S1AP_PDU_UNSUCCESSFULOUTCOME))
            {
               RETVALUE(ROK);
            }
            startStr  = (TknU8 *)(&(pdu->val.unsuccessfulOutcome.value.u));
            procCode  = pdu->val.unsuccessfulOutcome.procedureCode.val;
            break;
         }
   }

   if (((TknU8 *)startStr)->pres == PRSNT_NODEF)
   {
      /* Increment it by TknU8 for TknPres */
      currStr  = (TknU8 *) ((PTR)startStr + sizeof(TknU8));
   }
   else
   {
      RETVALUE(ROK);
   }

   if (((TknU16 *)(currStr))->pres == PRSNT_NODEF)
   {
      /* get the Number of IEs received : noComp */
      numComp = ((TknU16 *)(currStr))->val;
   }

   /*  Increment currStr by TknU16 for skipping noComp */
   currStr = (TknU8 *)((PTR)currStr + sizeof(TknU16));

   currStr = *(TknU8**)currStr;

   while (recIdx < numComp) 
   {
      startStr = currStr;

      if (((TknPres *)currStr)->pres == PRSNT_NODEF)
      {   
         /* Increment it by TknU8 for TknPres */
         currStr  = (TknU8 *) ((PTR)currStr + sizeof(TknPres));

         /* Get the received Id  */
         recId  = ((SztProtIE_ID *)currStr)->val; 

         /* Compare the two Ids */
         if (recId == id)
         {
            startStr = (TknU8 *) ((PTR)currStr + sizeof(SztProtIE_ID) 
                  + sizeof(SztCriticality));

            *ie = startStr;
            break;
         }
      }

      size = szElmSize[choiceType][procCode];
      currStr  = (TknU8 *) ((PTR)startStr + size);
      recIdx++;
   }

   RETVALUE(ROK);
} /* end of nbSzGetIE */
/**
 *  @brief This function fills the structure TknStrOSXL1
 *
 *      Function: wrFillTknStrOSXL1
 *
 *          Processing steps:
 *          - allocate memory to val in TknStrOSXL1
 *          - update token present field as TRUE
 *          - update the memory with the value  received
 *
 *
 *  @param[out] ptr : TknStrOSXL stucture pointer to be updated
 *  @param[in]  len : length for which memory to allocated
 *  @param[in]  val : value getting updated
 *  @param[in]  mem : pointer to memCp
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 *          RFAILED
 */

PUBLIC S16 nbFillTknStrOSXL1
(
TknStrOSXL                   *ptr,
U16                          len,
U32                          val,
CmMemListCp                  *mem
)
{
   U16                       idx;
   U8                        tmpVal;

   /* make the element as present */
   ptr->pres = TRUE;
   ptr->len =  len;

   if (cmGetMem(mem, len * sizeof(U8), (Ptr *)&ptr->val) != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to allocate memory. cmGetMem failed");
      RETVALUE(RFAILED);
   }

   for(idx = 0; idx < len; idx++)
   {
      tmpVal = (U8)(val >> (8 * idx));
      ptr->val[len - (idx + 1)] = tmpVal;

   }

   RETVALUE(ROK);
}

PUBLIC S16 nbGetUeIdFromS1apId
(
 U32 enbUeS1apId,
 U32 mmeUeS1apId,
 U32 *ueId
)
{
   U8 cnt = 0;
   NbUeCb * ueCb    = NULLP; 
   NbUeCb * prevUeCb = NULLP; 
#if 0
   for(cnt = 1; cnt < nbCb.crntUeIdx; cnt++)
   {
      if((nbCb.ueCbLst[cnt]->s1ConCb != NULLP) && 
            (nbCb.ueCbLst[cnt]->s1ConCb->enb_ue_s1ap_id == enbUeS1apId) && 
            (nbCb.ueCbLst[cnt]->s1ConCb->mme_ue_s1ap_id == mmeUeS1apId))
      {
         *ueId = cnt;
         RETVALUE(ROK);
      }
   }
#endif
   for(;((cmHashListGetNext(&(nbCb.ueCbLst),(PTR)prevUeCb,(PTR*)&ueCb)) == ROK);)
      {
         if ((ueCb->s1ConCb->enb_ue_s1ap_id == enbUeS1apId)&& 
             (ueCb->s1ConCb->mme_ue_s1ap_id == mmeUeS1apId))
         {
            *ueId = cnt;
            RETVALUE(ROK);
         }
         prevUeCb  = ueCb;
         ueCb = NULLP;
      }
   RETVALUE(RFAILED);
}/* nbGetUeIdFromS1apId */

/**
 * *  @brief This function fills the structure TknStrBSXL
 * *
 * *      Function: nbFillTknStrBSXL
 * *
 * *          Processing steps:
 * *          - allocate memory to val in TknStrBSXL
 * *          - update token present field as TRUE
 * *          - update the memory with the value  received
 * *
 * *
 * *  @param[out] ptr  : TknStrBSXL stucture pointer to be updated
 * *  @param[in]  len  : length for which memory to allocated
 * *  @param[in]  val  : value getting updated
 * *  @param[in]  mem  : pointer to memCp
 * *  @return S16
 *   -# Success : ROK
 *   -# Failure : RFAILED
 * *          RFAILED
 * */

 PUBLIC S16 nbFillTknStrBSXL
(
 TknStrBSXL                   *ptr,
 U16                          len,
 Data                         *val,
 CmMemListCp                  *mem
 )
{
   U16                       idx;

   /* make the element as present */
   ptr->pres = TRUE;
   ptr->len =  len;

   if (cmGetMem(mem, (len + 7)/8 , (Ptr *)&ptr->val) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   for(idx = 0; idx < (len + 7)/8; idx++)
   {
      ptr->val[idx] = val[idx];
   }

   RETVALUE(ROK);
}

PUBLIC Void printIpv6Addr(uint8_t *ipv6_addr) {

  uint8_t ip6_str[INET6_ADDRSTRLEN] = {0};
  sprintf(
      ip6_str,
      "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
      (int)(ipv6_addr[0]), (int)(ipv6_addr[1]), (int)(ipv6_addr[2]),
      (int)(ipv6_addr[3]), (int)(ipv6_addr[4]), (int)(ipv6_addr[5]),
      (int)(ipv6_addr[6]), (int)(ipv6_addr[7]), (int)(ipv6_addr[8]),
      (int)(ipv6_addr[9]), (int)(ipv6_addr[10]), (int)(ipv6_addr[11]),
      (int)(ipv6_addr[12]), (int)(ipv6_addr[13]), (int)(ipv6_addr[14]),
      (int)(ipv6_addr[15]));
  NB_LOG_DEBUG(&nbCb, "IPv6 address %s", ip6_str);
  RETVOID;
}
