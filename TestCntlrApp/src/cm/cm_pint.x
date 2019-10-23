
/********************************************************************20**
  
     Name:     common asn.1 PER encoding/decoding Internal header file
  
     Type:     C include file
  
     Desc:     strutures and typedef's for encoding/decoding routines
               internal to PER ASN 
  
     File:     cm_pint.x
  
     Sid:      cm_pint.x@@/main/8 - Sat Apr 25 17:40:16 2009
  
     Prg:      mp
  
*********************************************************************21*/

#ifndef __CMPINTX__
#define __CMPINTX__
#ifdef __cplusplus
EXTERN "C" {
#endif /* _cplusplus */


typedef S16 (*CMPASNDECFUNC) ARGS(( CmPAsnMsgCp *msgCp));
typedef S16 (*CMPASNENCFUNC) ARGS(( CmPAsnMsgCp *msgCp));

/* Extern declarations internally used by ASN */ 

EXTERN  S16 cmPAsnEncElm      ARGS((CmPAsnMsgCp *msgCp));
EXTERN  S16 cmPAsnEncOTElm    ARGS((CmPAsnMsgCp *msgCp));
EXTERN  S16 cmPAsnDecElm      ARGS((CmPAsnMsgCp *msgCp));
EXTERN  S16 cmPAsnDecOTElm    ARGS((CmPAsnMsgCp *msgCp));

EXTERN  U8 cmPAsnGetInitByte  ARGS((CmPAsnMsgCp *msgCp));
EXTERN  S16 cmPAsnEncConInt   ARGS((CmPAsnMsgCp *msgCp,
                                    U32 value, U32 lBound, U32 uBound, 
                                    Bool isSigned));
/* cm_pint_x_001.main_7 */
EXTERN  S16 cmPAsnEncConIntXL ARGS((CmPAsnMsgCp *msgCp, U8 *value, U8 len, 
                                    U8 *lBound, U8 lbLen, 
                                    U8 *uBound, U8 ubLen));
EXTERN  S16 cmPAsnEncSemiConInt ARGS((CmPAsnMsgCp *msgCp,
                                    U32 value, U32 lBound, Bool isSigned));
EXTERN  S16 cmPAsnEncSemiConIntXL ARGS((CmPAsnMsgCp *msgCp, U8 *value, U8 len,
                                        U8 *lBound, U8 lbLen));
EXTERN  S16 cmPAsnEncUnconInt ARGS((CmPAsnMsgCp *msgCp, U32 value,
                                    Bool isSigned));
EXTERN  S16 cmPAsnEncUnconIntXL ARGS((CmPAsnMsgCp *msgCp, U8 *value, U8 len));

EXTERN  S16 cmPAsnFragEnc ARGS((CmPAsnMsgCp *msgCp,U32 len));
EXTERN  S16 cmPAsnCollateFrag ARGS((CmPAsnMsgCp  *msgCp,U32 lenVal,
                                    U32 *totalLen));
EXTERN  S16 cmPAsnDecFragSeqOfComp ARGS((CmPAsnMsgCp *msgCp,U32 fragComp,
                                         U8 **retPtr));
EXTERN  S16 cmPAsnDecFragSeqOf ARGS((CmPAsnMsgCp *msgCp,U32 numComp,
                                     U32 *totalComp));

EXTERN  S16 cmPAsnEncUnconLen ARGS((CmPAsnMsgCp *msgCp,U32 intVal));
EXTERN  S16 cmPAsnEncFragVal  ARGS((CmPAsnMsgCp *msgCp,U32 lenVal,
                                    U8 itemLen));
EXTERN  S16 cmPAsnEncSmallInt ARGS((CmPAsnMsgCp *msgCp,U32 value));
EXTERN  S16 cmPAsnEncSmallLen ARGS((CmPAsnMsgCp *msgCp,U32 lenValue));
EXTERN  U8 cmPAsnGetBFSize    ARGS((U32 range));
EXTERN  S16 cmPAsnEncSeqPreAmb ARGS((CmPAsnMsgCp *msgCp));
EXTERN  S16 cmPAsnEncSeqExt   ARGS((CmPAsnMsgCp *msgCp, U32 nmbExtMkrs));
EXTERN  S16 cmPAsnEncSeqComp  ARGS((CmPAsnMsgCp *msgCp));
EXTERN  S16 cmPAsnEncSeqExtBit ARGS((CmPAsnMsgCp *msgCp, Bool *extFlag));
EXTERN  S16 cmPAsnChkEncElmnt ARGS((U8 flag, CmPAsnMsgCp *msgCp, 
                                    TknU8 *evntStr));
EXTERN  Bool cmPAsnChkMandMis ARGS((CmPAsnMsgCp *msgCp));
EXTERN  S16 cmPAsnDecChkFlag  ARGS((CmPAsnMsgCp *msgCp));
EXTERN  S16 cmPAsnEncSeqOfNoComp ARGS((CmPAsnMsgCp *msgCp, 
                                    Bool *fragFlag));
/* cm_pint_x_001.main_4 */
EXTERN  S16 cmPAsnEncStrLen   ARGS((CmPAsnMsgCp *msgCp, U32 length,
                                    U32 min, U32 max, Bool *fragFlag,U8 strType));
EXTERN  S16 cmPAsnEncStrVal   ARGS((CmPAsnMsgCp *msgCp, U16 length,
                                    Bool fragFlag, U8 strType));
EXTERN  S16 cmPAsnEncMinOct   ARGS((CmPAsnMsgCp *msgCp, U32
                                    value, U8 lenVal));

EXTERN  S16 cmPAsnDecConInt   ARGS((CmPAsnMsgCp *msgCp, U32 min, U32 max,
                                    U32 *val, Bool isSigned)); 
EXTERN  S16 cmPAsnDecConIntXL ARGS((CmPAsnMsgCp *msgCp, U8 *lBound, U8 lbLen,
                                    U8 *uBound, U8 ubLen, U8 *value, U8 *len)); 
EXTERN  S16 cmPAsnValIntValue ARGS((CmPAsnMsgCp *msgCp, U32 value,
                                    U8 type, Bool isSigned)); 
EXTERN  S16 cmPAsnDecUnconInt ARGS((CmPAsnMsgCp *msgCp, U32 len,
                                    U32 *val, Bool *negVal));
EXTERN  S16 cmPAsnDecUnconIntXL ARGS((CmPAsnMsgCp *msgCp, U8 len, U8 *val));
EXTERN  S16 cmPAsnDecSmallInt ARGS((CmPAsnMsgCp *msgCp, S32 *val)); 
EXTERN  S16 cmPAsnDecSemiConInt ARGS((CmPAsnMsgCp *msgCp, U32 len,
                                    U32 min, U32 *val, Bool isSigned)); 
EXTERN  S16 cmPAsnDecSemiConIntXL ARGS((CmPAsnMsgCp *msgCp, U8 *lBound, 
                                        U8 lbLen, U8 *val, U8 *len)); 
EXTERN  S16 cmPAsnDecBitField ARGS((CmPAsnMsgCp *msgCp, U8 *value,
                                    U8 size)); 
EXTERN  S16 cmPAsnSkipMsgBits ARGS((CmPAsnMsgCp *msgCp,
                                    U32 noBits)); 
EXTERN  S16 cmPAsnDecUnconLen ARGS((CmPAsnMsgCp *msgCp, U32 *len,
                                    Bool *fragFlag));
EXTERN  S16 cmPAsnDecNormSmallLen ARGS((CmPAsnMsgCp *msgCp, 
                                    U32 *len));
EXTERN  S16 cmPAsnDecConLen   ARGS((CmPAsnMsgCp *msgCp, U32 *len,
                                    U32 lb, U32 ub, Bool *fragFlag)); 
EXTERN  S16 cmPAsnDecSeqComp  ARGS((CmPAsnMsgCp *msgCp, U32 preAmLen)); 
EXTERN  S16 cmPAsnSkipOTVal   ARGS((CmPAsnMsgCp *msgCp)); 
EXTERN  S16 cmPAsnDecChExt    ARGS((CmPAsnMsgCp *msgCp)); 
EXTERN  S16 cmPAsnDecChComp   ARGS((CmPAsnMsgCp *msgCp)); 
EXTERN  S16 cmPAsnDecSeqExt   ARGS((CmPAsnMsgCp *msgCp,
                                    U32 noEncExt, U32 noDBExt)); 
EXTERN  S16 cmPAsnDecStrLen   ARGS((CmPAsnMsgCp *msgCp, 
                                    U32 min, U32 max, U32 *len,
                                    Bool *frag)); 
EXTERN  S16 cmPAsnDecStrVal   ARGS((CmPAsnMsgCp *msgCp, 
                                    U32 len, U32 min, U32 max, U8 strType));
EXTERN  S16 cmPAsnDecRChLen   ARGS((CmPAsnMsgCp *msgCp, 
                                    U32 *len, U8 b,U32 aub, U32 alb));
EXTERN  S16 cmPAsnDecChVal    ARGS((CmPAsnMsgCp *msgCp,U8 b, 
                                    U32 len, CmPAsnMulStrDef specDef));
EXTERN  S16 cmPAsnFillRChVal  ARGS((CmPAsnMsgCp *msgCp,U8 type, 
                                    U8 idx, U32 cVal));
EXTERN  U8 cmPAsnFindNoBit    ARGS((CmPAsnMsgCp *msgCp, U32 *effAlp, U8 type));
EXTERN  S16 cmPAsnEncChVal    ARGS((CmPAsnMsgCp *msgCp, U8 b, 
                                    CmPAsnMulStrDef specDef,U16 len));
EXTERN  S16 cmPAsnEncByteField ARGS((CmPAsnMsgCp *msgCp, U32 val,
                                    U8 b));
EXTERN  S16 cmPAsnEncByteFieldXL ARGS((CmPAsnMsgCp *msgCp, U8 *val, U8 valLen,
                                       U8 nBits));
EXTERN  S16 cmPAsnEncRChLen   ARGS((CmPAsnMsgCp *msgCp, U8 b, 
                                    U32 len, U32 aub, U32 lb));
EXTERN  S16 cmPAsnEncRChStrExt ARGS((CmPAsnMsgCp *msgCp,
                                    CmPAsnMulStrDef *specDef,U16 len));
EXTERN  S16 cmPAsnChkCharVal  ARGS(( CmPAsnMsgCp *msgCp, U16 len));
EXTERN  S16 cmPAsnDecFragVal  ARGS((CmPAsnMsgCp *msgCp, U32 len,
                                    U8 itemLen));
EXTERN  S16 cmPAsnFindFragLen ARGS((CmPAsnMsgCp *msgCp, U32 len,
                                    U8 itemLen, U32 *totalLen));
EXTERN  S16 cmPAsnAddUIntXL ARGS((U8 *val1, U8 len1, U8 *val2, U8 len2, 
                                  U8 *result, U8 *reslen));
EXTERN  S16 cmPAsnSubtractUIntXL ARGS((U8 *val1, U8 len1, U8 *val2, U8 len2, 
                                       U8 *result, U8 *reslen));


EXTERN CONSTANT CMPASNDECFUNC  cmPAsnDecFuncMtx[];
EXTERN CONSTANT CMPASNENCFUNC  cmPAsnEncFuncMtx[];

EXTERN  S16 cmPAsnEncFragSeqOf ARGS((CmPAsnMsgCp *msgCp, U32 numComp));

#ifdef __cplusplus
}
#endif

#endif  /* __CMPINTX__ */

  
/********************************************************************30**
  
         End of file:     cm_pint.x@@/main/8 - Sat Apr 25 17:40:16 2009
   
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
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      mp   1. initial release
/main/3      ---     mp   1. Fragmentation Support Added
                          2. Encode the unconstrained length for a Class IE
                             which is encoded as Open Type IE. 
/main/4      ---     rbabu 1.Updated for NBAP software release 1.2
/main/5      ---      vsr  1. Fixed the compiler warnings for RANAP release 2.3.
/main/6      ---     rbabu 1. Modified no of parameters in function 
                              "cmPAsnFindNoBit"
/main/7      ---      rbhat 1. RRC initial release.
/main/8      --- cm_pint_x_001.main_7 mos   1. Updated for S1AP Release 2.1
*********************************************************************91*/
  
