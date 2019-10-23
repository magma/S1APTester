typedef struct
{
   TskInit           init;
} SmCb;

PUBLIC S16 smActvInit(Ent, Inst, Region, Reason);
EXTERN S16 fwActvInit(Ent, Inst, Region, Reason);
EXTERN S16 ueActvInit(Ent, Inst, Region, Reason);

EXTERN S16 smActvTsk(Pst *pst, Buffer *mBuf);
EXTERN S16 fwActvTsk(Pst *pst, Buffer *mBuf);
EXTERN S16 ueActvTsk(Pst *pst, Buffer *mBuf);
