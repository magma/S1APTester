


/****************************************************************20**

     Name:     S1AP Layer 
  
     Type:     Message Function file
  
     Desc:     Message formatting/validation to be done  before 
               encoding, and after decoding. 

     File:     sz_msgfn.c

     Sid:      sq_msgfn.c@@/main/4 - Mon Jan 10 22:17:02 2011

     Prg:      rcs

*****************************************************************21*/




/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* common header 1 */
#include "cm_pasn.h"       /* common per asn.1 */
#include "cm_hash.h"       /* common header 1 */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common header 3 */
#include "cm_err.h"        /* common error */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport */
#include "sct.h"        /* common error */
#include "szt_asn.h"        /* asn */
#include "szt.h"           /* upper interface */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"           /* layer manager */
#include "sz.h"            /* s1ap */
#include "sz_err.h"        /* s1ap - error */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

/* header/extern include files (.x) */
  
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_mblk.x"       /* common header 1 */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_tkns.x"       /* common header 1 */
#include "cm_pasn.x"       /* common per asn.1 */
#include "cm_llist.x"      /* cm link list */
#include "cm_lib.x"        /* cm library */
#include "cm5.x"           /* common structs 3 */
#include "cm_inet.x"       /* common transport */
#include "cm_tpt.x"        /* common transport */
#include "sct.x"           /* common structs 3 */
#include "szt_asn.x"       /* asn structure */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* upper interface */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* layer manager */
#include "sz.x"            /* s1ap */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#ifdef __cplusplus
}
#endif /* __cplusplus */

EXTERN CmPAsnElmDef *szMsgDb[];

/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
EXTERN CmPAsnElmDef *szMsgDbIe[][2];
#endif /* SZTV1 */

#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
EXTERN CmPAsnElmDef *szMsg3gDbIe[][2];
#endif

/* Response for error handling - Unsuccessful msg or Error Indication */
U8 rspMsg[SZ_MSG_INDEX] = 
{
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_INIT_CXT_SETUP_FAIL,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_UE_CXT_MOD_FAIL,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_SETUP_FAIL,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG
#ifndef S1AP_REL8A0
,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG,
SZT_MSG_ID_NO_MSG
#endif /* S1AP_REL8A0 */
};

#ifdef DEBUGP
/*
 *  
 *   Fun: szPrntErrCode  
 *   
 *   Desc:  Used to print error code based on error code value 
 *   
 *   Ret:  ROK
 *   
 *   Notes:  
 *   
 *   File:  sz_msgfn.c
 *   
*/
#ifdef ANSI
PRIVATE S16 szPrntErrCode
(
 S16 errCode 
)
#else
PRIVATE S16 szPrntErrCode (errCode)
 S16 errCode;
#endif
{
   switch(errCode-1)
   {
      case 0 : 
      {
         SZDBGPN(LSZ_DBGMASK_MF, (szCb.init.prntBuf, PRNTSZE,
                "Transfer Syntax Error: Unexpected value(%d) \n", errCode));
         break;
      }
      case 1 : 
      {
         SZDBGPN(LSZ_DBGMASK_MF, (szCb.init.prntBuf, PRNTSZE,
                 "Transfer Syntax Error: Resources error (%d)\n", errCode));  
         break;
      }
      case 2 : 
      {
         SZDBGPN(LSZ_DBGMASK_MF, (szCb.init.prntBuf, PRNTSZE,"Transfer Syntax"
                " Error: Out of DB defined range (%d) \n", errCode));
         break;
      }
      case 3 : 
      {
         SZDBGPN(LSZ_DBGMASK_MF, (szCb.init.prntBuf, PRNTSZE,"Transfer Syntax"
                 " Error: Extra parameter at the end of msg (%d)\n", errCode));
         break;
      }
      case 4 : 
      {
         SZDBGPN(LSZ_DBGMASK_MF, (szCb.init.prntBuf, PRNTSZE,"Transfer Syntax"
                 " Error: Element index is bad for choice (%d)\n", errCode));  
         break;
      }
      case 5 : 
      {
         SZDBGPN(LSZ_DBGMASK_MF, (szCb.init.prntBuf, PRNTSZE,"Transfer Syntax"
                 " Error: Undefined parameter (%d)\n", errCode));  
         break;
      }
      case 6 : 
      {
         SZDBGPN(LSZ_DBGMASK_MF, (szCb.init.prntBuf, PRNTSZE,"Transfer Syntax"
                 " Error: Mandatory element missing (%d)\n", errCode));
         break;
      }
      case 7 : 
      {
         SZDBGPN(LSZ_DBGMASK_MF, (szCb.init.prntBuf, PRNTSZE,"Transfer Syntax"
                 " Error: Database error (%d)\n", errCode));
         break;
      }
      case 8 : 
      {
         SZDBGPN(LSZ_DBGMASK_MF, (szCb.init.prntBuf, PRNTSZE,"Transfer Syntax"
                 " Error: Default element missing (%d)\n", errCode));
         break;
      }
      case 9 : 
      {
         SZDBGPN(LSZ_DBGMASK_MF, (szCb.init.prntBuf, PRNTSZE,"Abstract Syntax"
                 " Error: User escape function failed (%d)\n", errCode));
         break;
      }
      default: 
      {
         SZDBGP(LSZ_DBGMASK_MF, (szCb.init.prntBuf," Invalid error code"
                        " value (%d) \n",errCode));
         break;
      }
   }
      RETVALUE(ROK);
}
#endif /*DEBUGP*/

/*
 *  
 *   Fun:  szEncode 
 *   
 *   Desc:  To encode the message as per ASN.1 PER. 
 *   
 *   Ret:   ROK/RFAILED
 *   
 *   Notes: Invoked thorugh non-database module. 
 *   
 *   File:  sz_msgfn.c
 *   
*/
#ifdef ANSI
PUBLIC S16 szEncode
(
 Mem *mem,
 S1apPdu **s1apPdu,
 Buffer **mBuf
)
#else
PUBLIC S16 szEncode (mem, s1apPdu, mBuf)
 Mem *mem;
 S1apPdu **s1apPdu; 
 Buffer  **mBuf;
#endif
{
   U8 dbgFlag;
   S16  ret;
   CmPAsnErr asnErr;
   U32 len=0;
   
   TRC2(szEncode)

   dbgFlag = FALSE;

#ifdef DEBUGP
   if (szCb.init.dbgMask & LSZ_DBGMASK_ASN)
      dbgFlag = TRUE;
#endif 

   if (*s1apPdu == NULLP)
   {
      RETVALUE(SZT_CAUSE_UNEXP_MSG);
   } 
       
   if ((SGetMsg(mem->region, mem->pool, mBuf)) != ROK)
   {
      SZLOGERROR_ADD_RES(ESZ106, 0, "Message Buffer Not allocated");

      SZ_FREE_SDU(*s1apPdu);

      RETVALUE(SZT_CAUSE_MEM_ALLOC_FAIL);
   }

   /* Initialize the PASN Error code */ 
   asnErr.errCode = 0;

   ret = cmPAsnEncMsg((TknU8 *)(&(*s1apPdu)->pdu), CM_PASN_USE_MBUF, 
                      (Void *)(*mBuf), SZ_PASN_VER_ZERO, 
                      (CmPAsnElmDef **)szMsgDb, 
                      (CmPAsnErr*)&asnErr,
                      &len, dbgFlag, FALSE );
  
   if (ret == RFAILED)
   {
      /* It's an ASN.1 Error */
      SZDBGP(LSZ_DBGMASK_MF, (szCb.init.prntBuf,
            " Encoding failed \n")); 
#ifdef DEBUGP
      szPrntErrCode(asnErr.errCode);
#endif /*DEBUGP*/
      SZ_FREE_SDU(*s1apPdu);

      SZ_FREE_BUF(*mBuf);

      if (asnErr.errCode == CM_PASN_ESC_FUNC_FLD)
         RETVALUE(SZT_CAUSE_PC_ABS_SYNTAX_ERR);
      else
         RETVALUE(SZT_CAUSE_PC_TX_SYNTAX_ERR);
  }

   RETVALUE(ROK);
} /* end of szEncode */

/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1

/*
 *  
 *   Fun:  szIeEncode 
 *   
 *   Desc:  To encode the IE message as per ASN.1 PER. 
 *   
 *   Ret:   ROK/RFAILED
 *   
 *   Notes: Invoked thorugh non-database module. 
 *   
 *   File:  sz_msgfn.c
 *   
*/
#ifdef ANSI
PUBLIC S16 szIeEncode
(
 Mem *mem,
 SztEncDecEvnt *sztEncDecEvnt
)
#else
PUBLIC S16 szIeEncode (mem, sztEncDecEvnt)
 Mem *mem;
 SztEncDecEvnt *sztEncDecEvnt;
#endif
{
   U8           dbgFlag;
   S16          ret;
   CmPAsnErr    asnErr;
   U32          len=0;
   TknU8        *event;
   CmPAsnElmDef **msgDb;
   Buffer       *mBuf;

   TRC2(szIeEncode)

   dbgFlag = FALSE;

#ifdef DEBUGP
   if (szCb.init.dbgMask & LSZ_DBGMASK_ASN)
      dbgFlag = TRUE;
#endif 
        
   if (sztEncDecEvnt->u.iePdu == NULLP)
   {
     RETVALUE(SZT_CAUSE_UNEXP_MSG);
   }

   if ((SGetMsg(mem->region, mem->pool, &mBuf)) != ROK)
   {
      SZLOGERROR_ADD_RES(ESZ106, 0, "Message Buffer Not allocated");

      SZ_FREE_SDU(sztEncDecEvnt->u.iePdu);

      RETVALUE(SZT_CAUSE_MEM_ALLOC_FAIL);
   }

   /* Initialize the PASN Error code */ 
   asnErr.errCode = 0;


   switch (sztEncDecEvnt->ieType.val)
   {
      case SZT_REQ_TYPE_ENCDEC_IE_SRCTGET:
      {
         event = (TknU8 *)(&sztEncDecEvnt->u.iePdu->u.srcToTget);
         msgDb = szMsgDbIe[SZT_REQ_TYPE_ENCDEC_IE_SRCTGET];

      }
      break;

      case SZT_REQ_TYPE_ENCDEC_IE_TGETSRC:
      {
         event = (TknU8 *)(&sztEncDecEvnt->u.iePdu->u.tgetToSrc);
         msgDb = szMsgDbIe[SZT_REQ_TYPE_ENCDEC_IE_TGETSRC];
      }
      break;
#ifdef SZTV3
    /* sz008.301 Support for Source RNC to Target RNC */
      case SZT_REQ_TYPE_ENCDEC_IE_SRCRNCTGETRNC:
         {
            event = (TknU8 *)(&sztEncDecEvnt->u.iePdu->u.srcRncToTgetRnc);
            msgDb = szMsg3gDbIe[SZT_REQ_TYPE_ENCDEC_IE_SRCRNCTGETRNC];
         }
         break;

      case SZT_REQ_TYPE_ENCDEC_IE_TGETRNCSRCRNC:
         {
            event = (TknU8 *)(&sztEncDecEvnt->u.iePdu->u.TgetRncToSrcRnc);
            msgDb = szMsg3gDbIe[SZT_REQ_TYPE_ENCDEC_IE_TGETRNCSRCRNC];
         }
         break;
#endif
      default:
      {
         RETVALUE(SZT_CAUSE_INV_TYPE);
      }
      break;
   }


   ret = cmPAsnEncMsg(event, CM_PASN_USE_MBUF, 
           (Void *)(mBuf), SZ_PASN_VER_ZERO, 
            (CmPAsnElmDef **) msgDb ,(CmPAsnErr*)&asnErr, 
            &len, dbgFlag, FALSE );

   if (ret == RFAILED)
   {
      /* It's an ASN.1 Error */
      SZDBGP(LSZ_DBGMASK_MF, (szCb.init.prntBuf,
            " Encoding failed \n")); 
#ifdef DEBUGP
      szPrntErrCode(asnErr.errCode);
#endif /*DEBUGP*/
      SZ_FREE_SDU(sztEncDecEvnt->u.iePdu);

      SZ_FREE_BUF(mBuf);

      if (asnErr.errCode == CM_PASN_ESC_FUNC_FLD)
         RETVALUE(SZT_CAUSE_PC_ABS_SYNTAX_ERR);
      else
         RETVALUE(SZT_CAUSE_PC_TX_SYNTAX_ERR);
  }

   SZ_FREE_SDU(sztEncDecEvnt->u.iePdu);
   sztEncDecEvnt->u.mBuf = mBuf;

   RETVALUE(ROK);
} /* end of szIeEncode */
#endif   /* SZTV1 */
 

/*
 *  
 *   Fun:  szDecode
 *   
 *   Desc:  To decode the message as per ASN.1 PER. 
 *   
 *   Ret:   ROK/RFAILED
 *   
 *   Notes: Invoked thorugh non-database module. 
 *   
 *   File:  sz_msgfn.c
 *   
*/
#ifdef ANSI
PUBLIC S16 szDecode
(
 Mem *mem,
 CmPAsnErr *err,
 S1apPdu **s1apPdu, 
 Buffer **mBuf
)
#else
PUBLIC S16 szDecode (mem, err, s1apPdu, mBuf)
 Mem *mem;
 CmPAsnErr *err;
 S1apPdu **s1apPdu; 
 Buffer **mBuf;
#endif
{
   U32          numDecOct; /* number of octets decoded */
   S16          ret;       /* return value from different procedures */
   U8           dbgFlag;
   U32          msgLen;
      

   TRC2(szDecode)
                   
   dbgFlag = FALSE;

#ifdef DEBUGP
   if (szCb.init.dbgMask & LSZ_DBGMASK_ASN)
      dbgFlag = TRUE;
#endif 
        
   /* Initialise memCp */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, mem, (Ptr *)s1apPdu); 
   if (ret != ROK)
   {
      SZDBGP(LSZ_DBGMASK_MF, (szCb.init.prntBuf,
            "Memory allocation failed in Decode \n")); 

      SZ_FREE_BUF(*mBuf);

      RETVALUE(SZT_CAUSE_MEM_ALLOC_FAIL);
   }
   /* Initialize the PASN Error code */ 

   err->errCode = 0;
   msgLen = 0;

   ret = (cmPAsnDecMsg((Void *)&((*s1apPdu)->pdu), CM_PASN_USE_MBUF, 
                  (Void **)mBuf, &numDecOct, SZ_PASN_VER_ZERO, 
                  (CmPAsnElmDef **)szMsgDb, CM_PASN_DROP_ELMNTS, 
                  (CmPAsnErr*)err, msgLen,
                  (CmMemListCp *)(&(*s1apPdu)->memCp), dbgFlag));
  
   /* sz001.301: Added the check for error code as in some cases the 
    * return value will be ROK, but error code set by CM PASN. When decode
    * is successful, the error code is set to zero */
   if ((ret == RFAILED) || (err->errCode != 0))
   {
      /* It's an ASN.1 Error */
      SZDBGP(LSZ_DBGMASK_MF, (szCb.init.prntBuf,
            " Decoding failed \n")); 
#ifdef DEBUGP
      szPrntErrCode(err->errCode);
#endif /*DEBUGP*/
      SZ_FREE_BUF(*mBuf);

      /* sz001.301: Out of range is also needs to be treated as 
       * abstract syntax error */
      if ((err->errCode == CM_PASN_ESC_FUNC_FLD) ||
          (err->errCode == CM_PASN_OUT_RANGE ))
      {
         RETVALUE(SZT_CAUSE_PC_ABS_SYNTAX_ERR);
      }
      else
      {
         SZ_FREE_SDU(*s1apPdu);
         RETVALUE(SZT_CAUSE_PC_TX_SYNTAX_ERR);
      }
   }

   RETVALUE(ROK);
} /* end of szDecode */

/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1 

/*
 *  
 *   Fun:  szIeDecode
 *   
 *   Desc:  To decode the IE message as per ASN.1 PER. 
 *   
 *   Ret:   ROK/RFAILED
 *   
 *   Notes: Invoked thorugh non-database module. 
 *   
 *   File:  sz_msgfn.c
 *   
*/
#ifdef ANSI
PUBLIC S16 szIeDecode
(
 Mem *mem,
 CmPAsnErr *err,
 SztEncDecEvnt *sztEncDecEvnt 
)
#else
PUBLIC S16 szIeDecode (mem, err, sztEncDecEvnt)
 Mem *mem;
 CmPAsnErr *err;
 SztEncDecEvnt *sztEncDecEvnt;
#endif
{
   U32          numDecOct; /* number of octets decoded */
   S16          ret;       /* return value from different procedures */
   U8           dbgFlag;
   U32          msgLen;
   Void         *event;
   CmPAsnElmDef **msgDb;
   Buffer       *mBuf;
   
   TRC2(szIeDecode)
                   
   dbgFlag = FALSE;

#ifdef DEBUGP
   if (szCb.init.dbgMask & LSZ_DBGMASK_ASN)
      dbgFlag = TRUE;
#endif 

   /* Copy the mBuf Pointer in to the local variable */
   mBuf = sztEncDecEvnt->u.mBuf;
        
   /* Initialise memCp */
   ret = cmAllocEvnt(sizeof(SzIePdu), SZ_MEM_SDU_SIZE, mem, (Ptr *) &(sztEncDecEvnt->u.iePdu)); 
   if (ret != ROK)
   {
      SZDBGP(LSZ_DBGMASK_MF, (szCb.init.prntBuf,
            "Memory allocation failed in Decode \n")); 

      RETVALUE(SZT_CAUSE_MEM_ALLOC_FAIL);
   }
   /* Initialize the PASN Error code */ 

   err->errCode = 0;
   msgLen = 0;

   switch (sztEncDecEvnt->ieType.val)
   {
      case SZT_REQ_TYPE_ENCDEC_IE_SRCTGET:
      {
         event = (Void *)(&sztEncDecEvnt->u.iePdu->u.srcToTget);
         msgDb = szMsgDbIe[SZT_REQ_TYPE_ENCDEC_IE_SRCTGET];
      }
      break;

      case SZT_REQ_TYPE_ENCDEC_IE_TGETSRC:
      {
         event = (Void *)(&sztEncDecEvnt->u.iePdu->u.tgetToSrc);
         msgDb = szMsgDbIe[SZT_REQ_TYPE_ENCDEC_IE_TGETSRC];
      }
      break;
#ifdef SZTV3
    /* sz008.301 Support for Source RNC to Target RNC */
      case SZT_REQ_TYPE_ENCDEC_IE_SRCRNCTGETRNC:
         {
            event = (TknU8 *)(&sztEncDecEvnt->u.iePdu->u.srcRncToTgetRnc);
            msgDb = szMsg3gDbIe[SZT_REQ_TYPE_ENCDEC_IE_SRCRNCTGETRNC];
         }
         break;

      case SZT_REQ_TYPE_ENCDEC_IE_TGETRNCSRCRNC:
         {
            event = (TknU8 *)(&sztEncDecEvnt->u.iePdu->u.TgetRncToSrcRnc);
            msgDb = szMsg3gDbIe[SZT_REQ_TYPE_ENCDEC_IE_TGETRNCSRCRNC];
         }
         break;
#endif
      default:
      {
         RETVALUE(SZT_CAUSE_INV_TYPE);
      }
      break;
   }

   ret = (cmPAsnDecMsg(event, CM_PASN_USE_MBUF, 
          (Void **)&(mBuf) , &numDecOct, SZ_PASN_VER_ZERO, 
            msgDb, CM_PASN_DROP_ELMNTS, 
            (CmPAsnErr*)err, msgLen,
            (CmMemListCp *)(&sztEncDecEvnt->u.iePdu->memCp), dbgFlag));

   if (ret == RFAILED)
   {
      /* It's an ASN.1 Error */
      SZDBGP(LSZ_DBGMASK_MF, (szCb.init.prntBuf,
            " Decoding failed \n")); 
#ifdef DEBUGP 
      szPrntErrCode(err->errCode);
#endif /*DEBUGP*/
      if (err->errCode == CM_PASN_ESC_FUNC_FLD)
      {
         RETVALUE(SZT_CAUSE_PC_ABS_SYNTAX_ERR);
      }
      else
      {
         SZ_FREE_SDU(sztEncDecEvnt->u.iePdu);
         RETVALUE(SZT_CAUSE_PC_TX_SYNTAX_ERR);
      }
   }

   SZ_FREE_BUF(mBuf);

   RETVALUE(ROK);
} /* end of szIeDecode */
#endif   /* SZTV1 */

/**********************************************************************
 
         End of file:     sq_msgfn.c@@/main/4 - Mon Jan 10 22:17:02 2011
 
**********************************************************************/

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
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/4      ---      vvashishth 1. Updated for S1AP release 3.1
/main/4   sz001.301   pkaX       1. In case of procedure code is out 
                                    of range, CM PASN sets the error
                                    code but returns ROK.
                                    Added the check for error code.
/main/4   sz003.301   pka        1. Updated for PSF-S1AP 1.1 release
/main/4   sz004.301   va         1. Updated for Transparent Container
                                    Enc/Dec
/main/4   sz008.301  akaranth    1. Support for source RNC to target RNC.
*********************************************************************91*/
