
/********************************************************************20**
  
     Name:     MME NAS Security Module
  
     Type:     C include file
  
     Desc:     C structure for security module.
   
     File:     ue_app_sec.x
  
     Sid:      ue_app_sec.x@@/main/1156 - Mon Nov 21 11:09:25 2011
   
     Prg:      sk
  
*********************************************************************21*/

#ifndef __UE_APP_SEC_X__
#define __UE_APP_SEC_X__ 1

PUBLIC Void  ueAppSecHexDump ARGS((S8    *mod,
                                   S8    *name,
                                   S8    *file,
                                   U16   line,
                                   S8    *fun,
                                   U8    *buf,
                                   U16   len));

#ifdef LTE_UE_NAS_SEC
#define UE_APP_SEC_MOD_NAME "LTE-CNE-SEC" 

#define UE_APP_SEC_PRNT_INFO(args) \
  printf(" [%s] [%s:%d:%s] [INFO]: ", UE_APP_SEC_MOD_NAME, __FILE__, __LINE__, __tapa_fun_);\
  printf args;\
  printf("\n");

#define UE_APP_SEC_PRNT_ERR(args) \
  printf(" [%s] [%s:%d:%s] [ERROR]: ", UE_APP_SEC_MOD_NAME, __FILE__, __LINE__, __tapa_fun_); \
  printf args;\
  printf("\n");

#define UE_APP_SEC_PRNT_HEX(name, buf, len) \
  ueAppSecHexDump(UE_APP_SEC_MOD_NAME, name, __FILE__, __LINE__, __tapa_fun_, buf, len);

#define UE_APP_SEC_TRC1(arg)\
  S8 __tapa_fun_[100];\
  sprintf(__tapa_fun_, #arg); \
  printf(" [%s] [%s:%d:%s] [TRC1]: Entering ", UE_APP_SEC_MOD_NAME, __FILE__, __LINE__, __tapa_fun_); \
  printf(#arg); \
  printf("\n");
 
#define UE_APP_SEC_TRC2(arg) \
  S8 __tapa_fun_[100];\
  sprintf(__tapa_fun_, #arg); \
  printf(" [%s] [%s:%d:%s] [TRC2]: Entering ", UE_APP_SEC_MOD_NAME, __FILE__, __LINE__, __tapa_fun_); \
  printf(#arg); \
  printf("\n");
#else
#define UE_APP_SEC_MOD_NAME "" 

#define UE_APP_SEC_PRNT_INFO(args) 
#define UE_APP_SEC_PRNT_ERR(args) 

#define UE_APP_SEC_PRNT_HEX(name, buf, len) 

#define UE_APP_SEC_TRC1(arg)
 
#define UE_APP_SEC_TRC2(arg)
#endif

/*Encryption Algoritm Identifier */
typedef enum ueAppEncAlg
{
   UE_APP_EEA0 = 0,
   UE_APP_EEA1_128,
   UE_APP_EEA2_128,

   /* should be last member */
   UE_APP_EEA_MAX = 7
}UeAppEncAlg;

/*Integrity Algoritm Identifier */
typedef enum ueAppIntAlg
{
   UE_APP_EIA0_NULL = 0,
   UE_APP_EIA1_128,
   UE_APP_EIA2_128,

   /* should be last member */
   UE_APP_EIA_MAX = 7
}UeAppIntAlg;

typedef struct ueAppMsg
{
   U8     *val;
   U16    len;
}UeAppMsg;

/*NAS Security Hdr*/
typedef struct ueAppSecHdr
{
   U8  pd;
   U8  hdrType;
   U32 mac;
   U8  seqNmb;
}UeAppSecHdr;

/*NAS Sequence Number*/
typedef struct ueAppNasSeqNmb
{
   U8 seqNmb;
   U8 ovrflwCnt;
}UeAppNasSeqNmb;

/*Security Context In MME*/
typedef struct ueAppSecCtxtCb
{
   /*Inputs*/
   U8              kasme[UE_APP_SZ_KASME_KEY];
   U8              tsc;    /*Native or Non-Native */
   U8              status;  /*Current or Non Current*/
   U8              ksi;
   UeAppEncAlg     encAlg;
   UeAppIntAlg     intAlg;

   /*Outputs*/
   U8              encKey[UE_APP_SZ_NAS_ENC_KEY];
   U8              intKey[UE_APP_SZ_NAS_INT_KEY];
   U8              enbKey[UE_APP_SZ_ENB_KEY];
   U8              autn[16];
   U16             lstUsdCnt;

   /*Local Info*/
   UeAppNasSeqNmb  dlSeqNmb;
   UeAppNasSeqNmb  ulSeqNmb;
}UeAppSecCtxtCb;

/*Key Generation Interface in MME*/
EXTERN S16 ueAppGenerateNasKey ARGS((UeAppSecCtxtCb *secCtx));

EXTERN S16 ueAppGenerateEnbKey ARGS((UeAppSecCtxtCb *secCtx,
                                     U32            count));

/*UE NAS Security Interface*/
EXTERN S16 ueAppCmpUplnkSec ARGS((UeAppSecCtxtCb *secCtx, 
                                  U8             hdrType, 
                                  UeAppMsg       *srcMsg, 
                                  UeAppMsg       *dstMsg));

EXTERN S16 ueAppVldDwnlnkSec ARGS((UeAppSecCtxtCb *secCtx, 
                                   UeAppMsg       *srcMsg, 
                                   UeAppMsg       *dstMsg)); 
#endif /*__UE_APP_SEC_X__*/
