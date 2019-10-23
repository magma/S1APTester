
/**********************************************************************

     Name:     Ue application layer structure declarations

     Type:     C include file

     Desc:     Structures and Function Signatures required by 
               Ue Application Layer

     File:     ue.x

     Sid:      

     Prg:       

**********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus  */ 

typedef enum _uestatus
{
  UE_APP_CONFIG = 0,
  UE_APP_CONFIG_COMPLETE = 1,
  UE_CONFIG,
  UE_CONFIG_COMPLETE,
  UE_ATTACH_REQUEST,
  UE_AUTH_REQUEST,
  UE_AUTH_RESPONSE,
  UE_SEC_MODE_CMD_REQUEST,
  UE_SEC_MODE_CMD_COMPLETE,
  UE_ATTACH_ACCEPT,
  UE_ATTACH_COMPLETE,
  UE_ATTACH_FAIL,
  UE_DETACH_REQUST,
  UE_DETACH_COMPLETE,
  UE_SERVICE_REQUEST
}enumUeStatus;

/*************** prototypes **********/

PUBLIC S16 ueActvTsk 
(
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
);

PUBLIC S16 ueActvInit
(
Ent ent,                      /* entity */
Inst inst,                    /* instance */
Region region,                /* region */
Reason reason                 /* reason */
);

EXTERN Data* ueAlloc(Size);
EXTERN S16 ueFree(Data*, Size);

#ifdef __cplusplus
}
#endif /* __cplusplus */
