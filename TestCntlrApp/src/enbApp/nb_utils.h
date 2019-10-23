/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

     Type:     C include file

    Desc:  C source code for ENODEB Application

     File:     nb_utils.h

    Sid:   

     Prg:       

**********************************************************************/
#ifndef __NB_UTILS_H__
#define __NB_UTILS_H__


#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */


EXTERN S16 nbCpyCmTptAddr(CmTptAddr *dst, CmTptAddr *src);
EXTERN S16 nbFillTknU8(TknU8 *encParam, U8 val);
EXTERN S16 nbFillTknU16(TknU16 *encParam, U16 val);
EXTERN S16 nbFillTknU32(TknU32 *encParam, U32 val);
EXTERN S16 nbFill2TknStr4(TknStr4 *ptr, U8 len, U8 *val);
EXTERN Bool nbUtlPlmnsEqual(NbPlmnId *plmnId1, NbPlmnId *plmnId2);
EXTERN S16 nbUtlGetPlmnId (NbPlmnId *plmnId, SztPLMNidentity *plmnIe);
EXTERN S16 nbUtlGetTportAddr(TknStrBSXL *ie, CmTptAddr *addr);
EXTERN U32 nbUtlGetTeid(TknStrOSXL *ie);
EXTERN S16 nbUtlFillPlmn(NbPlmnId *plmnId, SztPLMNidentity *plmnIe);
EXTERN S16 nbUtlCopyPlmnId (NbPlmnId *plmn1, NbPlmnId *plmn2);
EXTERN S16 nbFillTknS32(TknS32 *encParam,S32 val);

EXTERN S16 nbGetUeIdFromS1apId
(
 U32 enbUeS1apId,
 U32 mmeUeS1apId,
 U8 *ueId
);

EXTERN S16 nbFillTknStrOSXL(
TknStrOSXL                   *ptr,
U16                          len,
Data                         *val,
CmMemListCp                  *mem
);
EXTERN S16 nbGetU32FrmTknStr4
(
   U32                       *val,
   TknStr4                   *ie
);
EXTERN S16 nbGetU16FrmTknStr4
(
   U16                       *val,
   TknStr4                   *ie
);
EXTERN S16 nbUtlFillPlmnId
(
NbPlmnId                     *plmnId,
SztPLMNidentity              *plmnIe
);
EXTERN S16 nbSztFillS1eNBId
(
 S1apPdu                      *pdu,
 U32                          enbType,
 U32                          cgi,
 NbPlmnId                     *plmnId,
 SztGlobal_ENB_ID             *enbIe
 );
PUBLIC S16  nbSztFillPLMNId 
(
 S1apPdu                      *pdu,
 NbPlmnId                     *plmnId,
 SztPLMNidentity              *plmnIe
 );
PUBLIC Void  nbFillTknBStr32
(
 TknBStr32                    *ptr,
 U16                          len,
 U32                          val
 );
EXTERN Void  nbFillTknBStr32
(
 TknBStr32                    *ptr,
 U16                          len,
 U32                          val
 );
EXTERN S16 nbSzGetIE
(
 SztS1AP_PDU                  *pdu,
 U32                          id,
 TknU8                        **ie
 );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __NB_UTILS_H__ */
