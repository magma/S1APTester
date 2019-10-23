EXTERN S16 nbAppRouteInit(U32, S8*);
EXTERN Void nbAppHndlIPPkt(CONSTANT U8*, U32);
EXTERN S16 nbAppCfgrPdnAssignedAddr(U8, U32);
EXTERN Void *nbAppPktReceiver(Void*);
EXTERN U16 nbAppCalcIPChecksum(U8*, U32);
EXTERN S16 nbAppFrwdIpPkt(U8*, U32);
EXTERN Void nbRelCntxtInTrafficHandler(U8);
