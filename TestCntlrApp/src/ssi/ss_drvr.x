

/********************************************************************20**
 
     Name:     System Services -- Driver tasks
 
     Type:     C include file
 
     Desc:     Data structure definitions required for driver tasks.
 
     File:     ss_drvr.x
 
     Sid:      ss_drvr.x@@/main/3 - Mon Nov 17 15:54:15 2008
 
     Prg:      kp
 
*********************************************************************21*/


#ifndef __SSDRVRX__
#define __SSDRVRX__

#ifdef __cplusplus
extern "C" {
#endif


#ifdef SS_DRVR_SUPPORT

/* individual entry in the table of driver tasks */
typedef struct ssDrvrTskEntry
{
   /* Any implementation specific content */
   SsdDrvrTskEntry dep;


   /* Common content */
   Bool         used;                   /* entry is used or not */
   Inst         channel;                /* channel ID */
   ActvTsk      actvTsk;                /* activation function */
   ISTsk        isTsk;                  /* interrupt service task */
   ProcId       low;                    /* processor ID -- low */
   ProcId       high;                   /* processor ID -- high */

   SLockId      lock;                   /* to serialize calls to the
                                           activation function */

} SsDrvrTskEntry;

#endif  /* SS_DRVR_SUPPORT */


#ifdef __cplusplus
}
#endif

#endif  /*  __SSDRVRX__  */


  
/********************************************************************30**

         End of file:     ss_drvr.x@@/main/3 - Mon Nov 17 15:54:15 2008

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      kp   1. initial release

1.2          ---      kp   1. C++ compilable, cosmetic changes

/main/3      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/
