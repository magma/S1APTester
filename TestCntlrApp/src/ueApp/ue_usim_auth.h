
/********************************************************************20**
  
     Name:     HSS Authentication Module
  
     Type:     C include file
  
     Desc:     C defines for authentication module.
   
     File:     vb_hss_auth.h
  
     Sid:      vb_hss_auth.h@@/main/1156 - Mon Nov 21 11:09:25 2011
   
     Prg:      sk
  
*********************************************************************21*/
#ifndef __UE_APP_USIM_H__
#define __UE_APP_USIM_H__ 1

/* HSS specific defines */
#define UE_USIM_SEQ_NMB_SIZE  6
#define UE_USIM_AK_SIZE       6
#define UE_USIM_MAC_SIZE      8
#define UE_USIM_CK_SIZE      16
#define UE_USIM_IK_SIZE      16
#define UE_USIM_SHARED_KEY_SIZE  16
#define UE_USIM_OP_KEY_SIZE   16
#define UE_USIM_RES_SIZE      16
#ifdef SQN_ALGO_TS33102
#define UE_USIM_SEQ_NMB_INDX  32
#define UE_USIM_TWOS_EXPONENT_FOR_DELTA 28
#define UE_USIM_AGE_LIMIT 10
#endif

#define UE_APP_USIM_MAC_FAILURE  0x14
#define UE_APP_USIM_SYNC_FAILURE 0x15
#define UE_APP_USIM_NON_EPS_AUTH_FAIL 0x1A

/* Common to HSS and MME */
#define UE_RES_SIZE          8
#define UE_AUTS_SIZE        14
#define UE_AUTN_SIZE        16
#define UE_RAND_SIZE        16
#define UE_KASME_SIZE       32

#define VB_HSS_AUTN_GET_XDOUT(_rand, _ak, _xdout)                    \
{                                                                    \
   U8    _index = 0;                                                 \
   for (_index = 0; _index < UE_USIM_SHARED_KEY_SIZE; _index++)      \
   {                                                                 \
      _xdout[_index] = _ak[_index] ^ _rand[_index];                  \
   }                                                                 \
}

/*AK[bits 0,1,47] = XDOUT[bits 24,25,,71]*/
#define VB_HSS_AUTN_GET_AK(_k, _rand, _ak) \
{ \
   U16 _indKey = 0;\
   U16 _indAk = 0;\
   for(_indKey = 3; _indKey <=8; _indKey++) \
   {\
      _ak[_indAk] = _k[_indKey] ^ _rand[_indKey]; \
      _indAk++; \
   }\
}

/*CK[bits 0,1,127] = XDOUT[bits 8,9,.,126,127,0,1,,6,7]*/
#define VB_HSS_AUTN_GET_CK(_k, _rand, _ck) \
{ \
   U16 _indKey = 0;\
   U16 _indCk = 0;\
   for(_indKey = 1; _indKey <=15; _indKey++) \
   {\
      _ck[_indCk] = _k[_indKey] ^ _rand[_indKey]; \
      _indCk++; \
   }\
   _ck[_indCk] = _k[0] ^ _rand[0]; \
}

/*RES[bits 0,1,127] = XDOUT[bits 0,1,.127]*/
/* Optimizing by calculating the CK and RES together */
#define VB_HSS_AUTN_GET_RES(_k, _rand, _res) \
{ \
   U16 _indKey = 0;\
   for(_indKey = 0; _indKey <= 15; _indKey++) \
   {\
      _res[_indKey] = _k[_indKey] ^ _rand[_indKey]; \
   }\
}

/*CK[bits 0,1,127] = XDOUT[bits 8,9,.,126,127,0,1,,6,7]*/
/*RES[bits 0,1,127] = XDOUT[bits 0,1,.127]*/
/* Optimizing by calculating the CK and RES together */
#define VB_HSS_AUTN_GET_CK_N_XRES(_k, _rand, _ck, _res) \
{ \
   U16 _indKey = 0;\
   U16 _indCk = 0;\
   for(_indKey = 1; _indKey <=15; _indKey++) \
   {\
      _ck[_indCk] = _k[_indKey] ^ _rand[_indKey]; \
      _res[_indKey] = _ck[_indCk];\
      _indCk++; \
   }\
   _ck[_indCk] = _k[0] ^ _rand[0]; \
   _res[0] = _ck[_indCk];\
}

/*IK[bits 0,1,127] = XDOUT[bits 16,17,.126,127,0,1,.14,15]*/
#define VB_HSS_AUTN_GET_IK(_k, _rand, _ik) \
{ \
   U16 _indKey = 0;\
   U16 _indIk = 0;\
   for(_indKey = 2; _indKey <=15; _indKey++) \
   {\
      _ik[_indIk] = _k[_indKey] ^ _rand[_indKey]; \
      _indIk++; \
   }\
   _ik[_indIk] = _k[0] ^ _rand[0]; \
   _indIk ++; \
   _ik[_indIk] = _k[1] ^ _rand[1]; \
}

/*	CDOUT[bits 0,1,62,63] = SQN[bits 0,1,46,47] || AMF[bits 0,1,14,15]*/
#define VB_HSS_AUTN_GET_CDOUT(_sqn, _amf, _cdOut) \
{ \
   U16 _indKey = 0;\
   for(_indKey = 0; _indKey <=5; _indKey++) \
   {\
      _cdOut[_indKey] = _sqn[_indKey]; \
   }\
   _cdOut[6] = _amf[0]; \
   _cdOut[7] = _amf[1]; \
}

/*MAC[bits 0,1,62,63] = XDOUT[bits 0,1,62,63] xor CDOUT[bits 0,1,63]*/
#define VB_HSS_AUTN_GET_MAC(_k, _rand, _cdOut, _mac) \
{ \
   U16 _indKey = 0;\
   for(_indKey = 0; _indKey <=7; _indKey++) \
   {\
      _mac[_indKey] = _k[_indKey] ^ _rand[_indKey]; \
   }\
   for(_indKey = 0; _indKey <=7; _indKey++) \
   {\
      _mac[_indKey] = _mac[_indKey] ^ _cdOut[_indKey]; \
   }\
}

/*Compute AUTN using the formula: (SQN xor AK) || AMF || MAC  */
#define VB_HSS_AUTN_GET_AUTN(_k, _rand, _ak, _sqn, _amf, _mac, _autn) \
{ \
   U16 _indKey = 0;\
   U16 _indAutn = 0;\
   for(_indKey = 0; _indKey <=5; _indKey++) \
   {\
      _autn[_indKey] = _sqn[_indKey] ^ _ak[_indKey]; \
   }\
   _autn[6] = _amf[0]; \
   _autn[7] = _amf[1]; \
   _indAutn = 8; \
   for(_indKey = 0; _indKey <=7; _indKey++) \
   {\
      _autn[_indAutn] = _mac[_indKey]; \
      _indAutn ++; \
   }\
}

#define VB_HSS_AUTN_GET_RAND(_rand) \
{ \
   U32 _randT = 0; \
   _randT = rand(); \
   _rand[0] = _randT; \
   _randT = _randT >> 8; \
   _rand[1] = _randT; \
   _randT = _randT >> 8; \
   _rand[2] = _randT; \
   _randT = _randT >> 8; \
   _rand[3] = _randT; \
   cmMemcpy((U8 *)(_rand + 4), (U8 *)_rand, 4); \
   cmMemcpy((U8 *)(_rand + 8), (U8 *)_rand, 4); \
   cmMemcpy((U8 *)(_rand + 12), (U8 *)_rand, 4); \
}

#if 0
/* SQN = SEQHE(43bits, ) || IND(5 bits) */
/* MSB 43 bits of SQN = SEQ, i.e. at 0th to 43rd bit
 *   SQN[5]  SQN[4]   SQN[3]  SQN[2]    SQN[1]  SQN[0]
 * 00000 111 11111111 11111111 11111111 11111111 11111111
 * ----- ------------------------------------------------
 *   |                          |                     
 *  IND                        SEQ = 0x07FFFFFFFFFF
 *  */
#define VB_HSS_AUTN_GET_SQN(_ueInfo) \
{ \
   U8 _cnt = 0; \
   Bool _incr = FALSE; \
   if(_ueInfo->ueSecInfo.sqnHE[5] & 0x7)\
   {\
      /* reached the maximum value in bits, reset to 0 \
       * increment in next higher bits */\
      _ueInfo->ueSecInfo.sqnHE[5] = 0;\
   }\
   else\
   {\
      /* incrementing in LSB
       * no need to go to the higher bits*/\
      _ueInfo->ueSecInfo.sqnHE[5]++;\
      _incr = TRUE;\
   }\
   for(_cnt = 5; (_cnt != 0) && (_incr == FALSE); _cnt--) \
   {\
      if((_ueInfo->ueSecInfo.sqnHE[_cnt-1] != 0xFF) && (_incr == FALSE)) \
      { \
         /* incrementing in this LSB
          * no need to go to the higher bits*/\
         _ueInfo->ueSecInfo.sqnHE[_cnt-1]++; \
         _incr = TRUE; \
      } \
      if ((_ueInfo->ueSecInfo.sqnHE[_cnt-1] == 0xFF) && (_incr == FALSE))\
      { \
         /* reached the maximum value in bits, reset to 0 \
          * increment in next higher bits */\
         _ueInfo->ueSecInfo.sqnHE[_cnt-1] = 0; \
      } \
   }\
}

/* LSB 5 bits of SQN = IND,  are at 44th to 48th bit
 *   SQN[5]    SQN[4]   SQN[3]  SQN[2]    SQN[1]  SQN[0]
 * 11111 000 00000000 00000000 00000000 00000000 00000000
 * ----- ------------------------------------------------
 *   |                          |                     
 *  IND(0xF8)                   SEQ                       
 *  */
#define VB_HSS_AUTN_GET_IND(_ueInfo) \
{\
   if(_ueInfo->ueSecInfo.sqnHE[5] == 0xF8) \
   { \
         /* Rollback to 0 */ \
         _ueInfo->ueSecInfo.sqnHE[5] = (_ueInfo->ueSecInfo.sqnHE[5] & 0X07); \
   } \
   else \
   { \
      if((_ueInfo->ueSecInfo.sqnHE[5] & 0xF0) == 0xF0)\
      {\
         /* The next higher bit has to be 0 since, it s not 0xF8 \
          * hence control reached here \
          * so to increment just set the next higher bit*/\
         _ueInfo->ueSecInfo.sqnHE[5] = _ueInfo->ueSecInfo.sqnHE[5] | 0x08;\
      }\
      else\
      {\
         /* the lower 4 bits have not yet reached 0XF
          * so just increment */\
         _ueInfo->ueSecInfo.sqnHE[5]++; \
      }\
   } \
}

#define VB_HSS_AUTN_GET_SQN_MS(_ueInfo, _rand, _sqn, _auts, _ak) \
{ \
   U16 _byte= 0;\
   for(_byte= 0; _byte < 6; _byte++) \
   {\
      _sqn[_byte] = _auts[_byte] ^ _ak[_byte]; \
   }\
}
#endif


/* CDOUT[bits 0,1,<85>62,63] = SQN[bits 0,1,<85>46,47] || AMF[bits 0,1,<85>14,15]*/
#define USIM_AUTN_GET_CDOUT(_sqn, _amf, _cdOut) \
{ \
   U16 _indKey = 0;\
   for(_indKey = 0; _indKey <=5; _indKey++) \
   {\
      _cdOut[_indKey] = _sqn[_indKey]; \
   }\
   _cdOut[6] = _amf[0]; \
   _cdOut[7] = _amf[1]; \
}

/*MAC[bits 0,1,<85>62,63] = XDOUT[bits 0,1,<85>62,63] xor CDOUT[bits 0,1,<85>63]*/
#define USIM_AUTN_GET_MAC(_k, _rand, _cdOut, _mac) \
{ \
   U16 _indKey = 0;\
   for(_indKey = 0; _indKey <=7; _indKey++) \
   {\
      _mac[_indKey] = _k[_indKey] ^ _rand[_indKey]; \
   }\
   for(_indKey = 0; _indKey <=7; _indKey++) \
   {\
      _mac[_indKey] = _mac[_indKey] ^ _cdOut[_indKey]; \
   }\
} 


/*AK[bits 0,1,<85>47] = XDOUT[bits 24,25,<85>,71]*/
#define USIM_AUTN_GET_AK(_k, _rand, _ak) \
{ \
   U16 _indKey = 0;\
   U16 _indAk = 0;\
   for(_indKey = 3; _indKey <=8; _indKey++) \
   {\
      _ak[_indAk] = _k[_indKey] ^ _rand[_indKey]; \
      _indAk++; \
   }\
}

/*CK[bits 0,1,<85>127] = XDOUT[bits 8,9,<85>.,126,127,0,1,<85>,6,7]*/
/*RES[bits 0,1,<85>127] = XDOUT[bits 0,1,<85>.127]*/
/* Optimizing by calculating the CK and RES together */
#define USIM_AUTN_GET_CK_N_RES(_k, _rand, _ck, _res) \
{ \
   U16 _indKey = 0;\
   U16 _indCk = 0;\
   for(_indKey = 1; _indKey <=15; _indKey++) \
   {\
      _ck[_indCk] = _k[_indKey] ^ _rand[_indKey]; \
      _res[_indKey] = _ck[_indCk];\
      _indCk++; \
   }\
   _ck[_indCk] = _k[0] ^ _rand[0]; \
   _res[0] = _ck[_indCk];\
}

/*IK[bits 0,1,<85>127] = XDOUT[bits 16,17,<85>.126,127,0,1,<85>.14,15]*/
#define USIM_AUTN_GET_IK(_k, _rand, _ik) \
{ \
   U16 _indKey = 0;\
   U16 _indIk = 0;\
   for(_indKey = 2; _indKey <=15; _indKey++) \
   {\
      _ik[_indIk] = _k[_indKey] ^ _rand[_indKey]; \
      _indIk++; \
   }\
   _ik[_indIk] = _k[0] ^ _rand[0]; \
   _indIk++; \
   _ik[_indIk] = _k[1] ^ _rand[1]; \
}


#endif /*__UE_USIM_AUTH_H__*/

