
/********************************************************************20**
  
     Name:     stack manager error
  
     Type:     C include file
  
     Desc:     Error defines required by the stack manager.
   
     File:     sm_err.h
  
     Sid:      sm_err.h 1.2  -  05/17/99 12:44:42
  
     Prg:      nkk
  
*********************************************************************21*/

#ifndef __SMERRH__
#define __SMERRH__


/* defines */
  
#define  ESMBASE     (ERRSM + 0)    /* reserved */
/* 
 * ERRSM = 29000
 * Each layer that uses this file need to "reserve" a range
 * These errnos are only used in stack management packing/unpaking 
 * routines, therefore each product shouldn't need too many....I hope.
 * Remeber, errnos are S16 so our real limit here is 32767 and we're
 * starting at 29000
 */
#define  ESMXXX      (ESMBASE + 0)   /*   SM gets   0 - 49  */
#define  ESMSTX      (ESMBASE + 50)  /* TCAP gets  50 - 99  */
#define  ESMSPX      (ESMBASE + 100) /* SCCP gets 100 - 149 */
#define  ESMSNX      (ESMBASE + 150) /* MTP3 gets 150 - 199 */
#define  ESMSDX      (ESMBASE + 200) /* MTP2 gets 200 - 249 */

#endif /* __SMERRH__ */


/********************************************************************30**

         End of file: sm_err.h 1.2  -  05/17/99 12:44:42

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

  version    pat  init                   description
----------- ----- ----  ------------------------------------------------
1.1          ---  fmg   1. initial release

*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.2          ---      mb   1. Changed copyright Header
 
*********************************************************************91*/
