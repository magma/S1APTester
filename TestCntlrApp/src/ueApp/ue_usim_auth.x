
/********************************************************************20**
  
     Name:     MME NAS Security Module
  
     Type:     C include file
  
     Desc:     This file contains HSS authentication module C structure
   
     File:     ue_app_auth.x
  
     Sid:      ue_app_auth.x@@/main/1156 - Mon Mar 21 11:09:25 2011
   
     Prg:      sk
  
*********************************************************************21*/

#ifndef __UE_USIM_AUTH_X__
#define __UE_USIM_AUTH_X__ 1

PUBLIC Void  ueUsimAuthHexDump ARGS((S8    *mod,
                                       S8    *name,
                                       S8    *file,
                                       U16   line,
                                       S8    *fun,
                                       U8    *buf,
                                       U16   len));

#ifdef LTE_UE_NAS_SEC
#define UE_USIM_AUTH_MOD_NAME "LTE-CNE-AUTH" 

#define UE_USIM_AUTH_PRNT_INFO(args) \
  printf(" [%s] [%s:%d:%s] [INFO]: ", UE_USIM_AUTH_MOD_NAME, __FILE__, __LINE__, __tapa_fun_);\
  printf args;\
  printf("\n");

#define UE_USIM_AUTH_PRNT_ERR(args) \
  printf(" [%s] [%s:%d:%s] [ERROR]: ", UE_USIM_AUTH_MOD_NAME, __FILE__, __LINE__, __tapa_fun_); \
  printf args;\
  printf("\n");

#define UE_USIM_AUTH_PRNT_HEX(name, buf, len) \
  ueUsimAuthHexDump(UE_USIM_AUTH_MOD_NAME, name, __FILE__, __LINE__, __tapa_fun_, buf, len);

#define UE_USIM_AUTH_TRC1(arg)\
  S8 __tapa_fun_[100];\
  sprintf(__tapa_fun_, #arg); \
  printf(" [%s] [%s:%d:%s] [TRC1]: Entering ", UE_USIM_AUTH_MOD_NAME, __FILE__, __LINE__, __tapa_fun_); \
  printf(#arg); \
  printf("\n");

#define UE_USIM_AUTH_TRC2(arg) \
  S8 __tapa_fun_[100];\
  sprintf(__tapa_fun_, #arg); \
  printf(" [%s] [%s:%d:%s] [TRC2]: Entering ", UE_USIM_AUTH_MOD_NAME, __FILE__, __LINE__, __tapa_fun_); \
  printf(#arg); \
  printf("\n");
#else
#define UE_USIM_AUTH_MOD_NAME "" 

#define UE_USIM_AUTH_PRNT_INFO(args)

#define UE_USIM_AUTH_PRNT_ERR(args)

#define UE_USIM_AUTH_PRNT_HEX(name, buf, len)

#define UE_USIM_AUTH_TRC1(arg)

#define UE_USIM_AUTH_TRC2(arg)
 
#endif
/* MME Authentication Vector */
typedef struct ueAppAuthVec
{
   U8 rndNmb[UE_RAND_SIZE];
   U8 autn[UE_AUTN_SIZE];
   U8 xres[UE_RES_SIZE];
   U8 kasme[UE_KASME_SIZE];
}UeAppAuthVec;

/* HSS Authentication Vector */
typedef struct ueUsimAuthVec
{
   U8 ck[UE_USIM_CK_SIZE];
   U8 ik[UE_USIM_IK_SIZE];
   U8 ak[UE_USIM_AK_SIZE];
   UeAppAuthVec vec;
}UeUsimAuthVec;

typedef enum ueAppAuthAlg
{
   UE_APP_AUTH_XOR,
   UE_APP_AUTH_MILANAGE,
   UE_APP_AUTH_MAX
} UeAppAuthAlg;

typedef struct ueUsimUeAuthInfo
{
   U8  sharedKey[UE_USIM_SHARED_KEY_SIZE];
   U8  opKey[UE_USIM_OP_KEY_SIZE];
#ifdef SQN_ALGO_TS33102
   U8  seqNmb[UE_USIM_SEQ_NMB_INDX][UE_USIM_SEQ_NMB_SIZE];
#else
   U8  seqNmb[UE_USIM_SEQ_NMB_SIZE];
#endif
   UeAppAuthAlg   authAlg;
}UeUsimUeAuthInfo;

typedef struct ueUsimAuthKeys
{
   U8 ak[UE_USIM_AK_SIZE];
   U8 ck[UE_USIM_CK_SIZE];
   U8 ik[UE_USIM_IK_SIZE];
   U8 sqnRcvd[UE_USIM_SEQ_NMB_SIZE];
   U8 autn[CM_EMM_MAX_AUTN];
   U8 rnd[CM_EMM_MAX_RAND];
}UeUsimAuthKeys;

#ifndef SQN_ALGO_TS33102
EXTERN S16  ueUsimGenAuthVec ARGS((UeUsimUeAuthInfo    *ueInfo,
                                  UeUsimAuthVec       *authVec,
                                  U8                 *plmn));
#else
EXTERN S16  ueUsimGenAuthVec ARGS((UeUsimUeAuthInfo    *ueInfo,
                                  UeUsimAuthVec       *authVec,
                                  U8                 *plmn,
                                  U8                 *recvdSQN));
EXTERN Void ueUsimFndHighestSQNIndx(UeUsimUeAuthInfo *ueInfo, U8 * retIndx);
EXTERN Void ueUsimGetSqn(U8 *sqn, U64 seq, U8 ind);
EXTERN Void ueUsimGetSeqIndx(U8 *sqn, U64 *seq, U8 *indx);
#endif

EXTERN S16  ueUsimPrcsSyncFlr ARGS((UeUsimUeAuthInfo   *ueInfo,
                                   U8                *auts,
                                   U8                *rand,
                                   UeUsimAuthVec      *authVec,
                                   U8                *plmn));

EXTERN Void ueUsimCalcAndStoreAuthKeys ARGS((UeUsimUeAuthInfo *ueInfo,
                                             UeUsimAuthKeys* authKeys,
                                             U8              *res,
                                             U8              *autn,
                                             U8              *rnd));
EXTERN Void ueUsimCalcAuthKeys ARGS((UeUsimUeAuthInfo *ueInfo,
                                             UeUsimAuthKeys* authKeys,
                                             U8              *res,
                                             U8              *autn,
                                             U8              *rnd,
                                             U8              *ak,
                                             U8              *ck,
                                             U8              *ik));


EXTERN S16 ueUsimGenAuthRsp ARGS((UeUsimUeAuthInfo *ueInfo,
                                 UeUsimAuthKeys    *authKeys,
                                 UeSQN             sqnRcvd,
                                 U8                *plmn,
                                 U8                *res,
                                 U8                *kasme,
                                 U8                *cause,
                                 U8                *auts,
                                 UeSQN             maxSqnRcvd
                                 ));

EXTERN S16 ueUsimGenAuthRspTst ARGS
((
UeUsimUeAuthInfo *ueInfo, 
U8              *autn, 
U8              *rnd, 
U8              *plmn,
U8              *res, 
U8              *kasme,
U8              *cause, 
U8              *auts
));
EXTERN Void ueUsimGenAuthVect
(
 U8    *k, 
 U8    *rnd, 
 U8    *res, 
 U8    *ck, 
 U8    *ik, 
 U8    *ak 
 );

#endif /* __UE_USIM_AUTH_X__ */

