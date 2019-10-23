
/********************************************************************20**
 
     Name:     Trillium EGT UTIL
  
     Type:     C include file
  
     Desc:    EGT UTIL Functions
  
     File:     egt_util.x 
  
     Sid:      egt_util.x@@/main/3 - Tue Sep  6 12:05:49 2011
  
     Prg:      sv
  
*********************************************************************21*/
#ifndef __EGT_UTIL_X__
#define __EGT_UTIL_X__

#ifdef __cplusplus
EXTERN "C" {
#endif




/*******************************************************/
/* All Utilities                                       */
/*******************************************************/



/* egt_util_x_001.main_2 Sequence number is 24bit width now */
#ifndef EG_REL_930
EXTERN Void  egUtlBuildEgHeader ARGS((EgMsgHdr  *egHdr,
                                      U32       teId,
                                      U8        msgType,
                                      U16       seqNumber));
#else
EXTERN Void  egUtlBuildEgHeader ARGS((EgMsgHdr  *egHdr,
                                      U32       teId,
                                      U8        msgType,
                                      U32       seqNumber));
#endif /* EG_REL_930 */

/* egt_util_x_001.main_2 FTIED structure changed */
#ifndef EG_REL_930
EXTERN S16 egUtlEgtAddFteid ARGS((EgMsg         *egMsg, 
                                  EgIeLevelInfo *egLvlInfo,
                                  U32            teId,
                                  U8             ebi, 
                                  U8            *ipAddr, 
                                  U8             intfType, 
                                  U8             inst));
#else
EXTERN S16 egUtlEgtAddFteid ARGS((EgMsg         *egMsg, 
                                  EgIeLevelInfo *egLvlInfo,
                                  U32            teId,
                                  U8            *ipAddr, 
                                  U8             intfType, 
                                  U8             inst));
#endif /* EG_REL_930 */

EXTERN S16 egUtlEgtAddEpsBId ARGS((EgMsg         *egMsg, 
                                   EgIeLevelInfo *egLvlInfo,
                                   U8             ebiVal, 
                                   U8             inst));
/* egt_util_x_001.main_1: Function added */
EXTERN S16 egUtilEgtAddTadIe ARGS ((EgMsg         *egMsg,
                                     EgIeLevelInfo *egLvlInfo,
                                     U8            inst,
                                     U8            *buf,
                                     U8            len));


EXTERN S16 egUtlEgtAddCause ARGS((EgMsg         *egMsg, 
                                  EgIeLevelInfo *egLvlInfo,
                                  U8             cause, 
                                  U8             inst));

/* egt_util_x_001.main_1: Functions added */
EXTERN S16 egUtlEgtAddPrivateExt ARGS((EgMsg         *egMsg, 
                                  EgIeLevelInfo *egLvlInfo,
                                  U8             entId, 
                                  U8             inst));

EXTERN S16  egUtilEgtAddFlowQosIe ARGS ((
EgIe       *egIe,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
U8               inst
));


PUBLIC S16  egUtilEgtAddPTidIe ARGS((
                              EgMsg      *egMsg,
                              U8         pTidValue,
                              EgIeLevelInfo *egLvlInfo,
                              U8               inst
                              ));

EXTERN S16 egUtlEgtAddBearerCxt ARGS((EgMsg           *egMsg, 
                                      EgIeLevelInfo *egLvlInfo,
                                      U8             nmbGrpIe, 
                                      TknU8         *bearerId,
                                      TknU8         *cause,
                                      U8             inst, 
                                      EgIe           egIe[],
                                      U8             fteIdCnt,
                                      EgBearQos     *bearerQos));

EXTERN S16  egUtilEgtAddBearerTft ARGS(( EgMsg      *egMsg,
                                     EgIeLevelInfo *egLvlInfo,
                                     U8         inst,
                                     U8         *buf,
                                     U32        len
                                  ));

EXTERN S16 egUtlEgtAddPdnType ARGS((EgMsg         *egMsg, 
                                    EgIeLevelInfo *egLvlInfo,
                                    U8             inst));

EXTERN S16 egUtlEgtAddSelMode ARGS((EgMsg         *egMsg,
                                    EgIeLevelInfo *egLvlInfo,
                                    U8             inst));

EXTERN S16 egUtlEgtAddApn ARGS((EgMsg         *egMsg, 
                                EgIeLevelInfo *egLvlInfo,
                                U8            *apn,
                                U8             inst));

EXTERN S16 egUtlEgtAddIndType ARGS((EgMsg *egMsg, 
                                    EgIeLevelInfo *egLvlInfo,
                                    U8 inst));

EXTERN S16 egUtlEgtAddIndTypeForRel ARGS((EgMsg *egMsg, 
                                    EgIeLevelInfo *egLvlInfo,
                                    U8 inst));

EXTERN S16 egUtlEgtAddRatType ARGS((EgMsg *egMsg, 
                                    EgIeLevelInfo *egLvlInfo,
                                    U8 ratType, U8 inst));

EXTERN S16 egUtlEgtAddSrvNwk ARGS((EgMsg         *egMsg, 
                                   EgIeLevelInfo *egLvlInfo,
                                   U8             inst,
                                   U8            *mcc,
                                   U8            *mnc));

EXTERN S16 egUtlEgtAddMsisdn ARGS((EgMsg         *egMsg,
                                   EgIeLevelInfo *egLvlInfo,
                                   U8            *msIsdn, 
                                   U8             msIsdnLen,
                                   U8             inst));

EXTERN S16 egUtlEgtAddImsi ARGS((EgMsg         *egMsg, 
                                 EgIeLevelInfo *egLvlInfo,
                                 U8            *imsi,
                                 U8            imsiLen,
                                 U8             inst));

EXTERN S16 egUtlEgtAddPAA ARGS((EgMsg         *egMsg, 
                                EgIeLevelInfo *egLvlInfo,
                                U8            *ipAddr,
                                U8             inst));

/* egt_util_x_001.main_2 IE Header changed */
#ifndef EG_REL_930
EXTERN S16 egUtlEgtBuildEgIeHeader ARGS((EgIe *egIe, 
                                         U8 ieType, 
                                         U8 ieInst,
                                         U8 ieCr, 
                                         U8 dataType));
#else
EXTERN S16 egUtlEgtBuildEgIeHeader ARGS((EgIe *egIe, 
                                         U8 ieType, 
                                         U8 ieInst,
                                         U8 dataType));
#endif /* EG_REL_930 */

EXTERN S16 egUtlAllocEgMsg ARGS((EgMsg **egMsg, 
                                 Mem   *memInfo));

EXTERN S16 egUtlEgtAddMaxApnRestrict ARGS((EgMsg           *egMsg,
                                           EgIeLevelInfo   *egLvlInfo,
                                           U8               inst));

EXTERN S16 egUtlEgtAddBearerQos ARGS((EgMsg            *egMsg,
                                      EgIeLevelInfo    *egLvlInfo,
                                      EgBearQos        *bearerQos,
                                      U8               inst));



#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /* __EGT_UTIL_X__ */

/**********************************************************************

         End of file:     egt_util.x@@/main/3 - Tue Sep  6 12:05:49 2011

**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
   /main/1   -       aj               1. EGT UTIL required for the CNE
/main/2      ---         egt_util_x_001.main_1  rk   1. Updated for eNodeB 2.1 release.
/main/3    egt_util_x_001.main_2    pmacharla  1. Upgraded for eGTP 2.1 release
                                                 (under EG_REL_930 flag)
*********************************************************************91*/
