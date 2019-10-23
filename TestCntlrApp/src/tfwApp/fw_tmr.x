/********************************************************************20**

 
    Name:  LTE S1 SIM - Test FW Module 
 
    Type:  C include file
 
    Desc:  C header file for Test FW timers 
 
    File:  fw_tmr.x 
 
    Sid:      
 
    Prg:    
 
**********************************************************************/

#ifndef __FW_TMR_X__
#define __FW_TMR_X__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
   FW_TMR_INV,
   FW_TMR_ATTACH,
   FW_PERIODIC_TAU,
   FW_TMR_MAX
}FwTmrType;

/* Public function declaration */
typedef Void (*FwTmrExpHndlr)(PTR Cb);
EXTERN S16 fwRegInitTmr(FwCb *fwCb);
PUBLIC S16 fwDeregTmr(FwCb *fwCb);
EXTERN S16 fwStartTmr(FwCb* fwCb, UeIdCb *ueIdCb, FwTmrExpHndlr waitTmrFun,
                      U32 delay);
EXTERN Void fwStopTmr(FwCb  *fwCb, UeIdCb *ueIdCb);
EXTERN S16 fwTmrMemAlloc(Data **ptr, Size size);
EXTERN S16 fwTmrMemFree(Data *ptr, Size size);
EXTERN Void fwHndlAttachTmrExp(PTR cb);
EXTERN Void fwHndlTauTmrExp(PTR cb);
EXTERN Void fwHndlPdnTmrExp(PTR  cb);

#ifdef __cplusplus
}
#endif

#endif
