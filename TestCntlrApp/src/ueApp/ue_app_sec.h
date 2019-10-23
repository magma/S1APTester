
/********************************************************************20**
  
     Name:     MME NAS Security Module
  
     Type:     C include file
  
     Desc:     C defines for security module.
   
     File:     ue_app_sec.h
  
     Sid:      ue_app_sec.h@@/main/1156 - Mon Nov 21 11:09:25 2011
   
     Prg:      sk
  
*********************************************************************21*/

#ifndef __UE_APP_SEC_H__
#define __UE_APP_SEC_H__


#define UE_APP_SEC_HT_PLAIN_NAS_MSG               0x00
#define UE_APP_SEC_HT_INT_PRTD                    0x01
#define UE_APP_SEC_HT_INT_PRTD_ENC                0x02
#define UE_APP_SEC_HT_INT_PRTD_NEW_SEC_CTXT       0x03
#define UE_APP_SEC_HT_INT_PRTD_ENC_NEW_SEC_CTXT   0x04
#define UE_APP_SEC_HT_SER_REQ                     0x0C

#define UE_APP_SZ_KASME_KEY      32
#define UE_APP_SZ_NAS_ENC_KEY    16
#define UE_APP_SZ_NAS_INT_KEY    16
#define UE_APP_SZ_ENB_KEY        32

#define UE_APP_ENC_MAX_ALG        7
#define UE_APP_INT_MAX_ALG        7

#define UE_APP_SEC_CTXT_NATV      0    
#define UE_APP_SEC_CTXT_NON_NATV  1
    
#define UE_APP_SEC_CTXT_NON_CRNT  0
#define UE_APP_SEC_CTXT_CRNT      1

#endif /*__UE_APP_SEC_H__*/
