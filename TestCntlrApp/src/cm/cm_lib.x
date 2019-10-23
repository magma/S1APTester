
/********************************************************************20**

     Name:     common library functions
  
     Type:     C include file
  
     Desc:     Prototypes for common functions that are implemented in
               both a portable and a performance-efficient manner. These
               functions are selected based on the operating system.

     File:     cm_lib.x

     Sid:      cm_lib.x@@/main/9 - Wed Jan 27 20:18:04 2010

     Prg:      ak

*********************************************************************21*/



#ifndef __CMLIBX__
#define __CMLIBX__

#ifdef __cplusplus
extern "C" {
#endif

PUBLIC U8 *cmMemcpy      ARGS((U8 *tgt, CONSTANT U8 *src, PTR len));
PUBLIC S16 cmMemcmp      ARGS((CONSTANT U8 *s1, CONSTANT U8 *s2, PTR len));
PUBLIC U8 *cmMemset      ARGS((U8 *src, U8 val, PTR len));

PUBLIC S16 cmStrcmp      ARGS((CONSTANT U8 *s1, CONSTANT U8 *s2));
/* cm_lib_x_001.main_8:Changing from S16 to MsgLen.*/
PUBLIC S16 cmStrncmp     ARGS((CONSTANT U8 *s1, CONSTANT U8 *s2, MsgLen len));
PUBLIC MsgLen cmStrlen   ARGS((CONSTANT U8 *s));

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif   /* __CMLIBX__ */

  
/********************************************************************30**
  
         End of file:     cm_lib.x@@/main/9 - Wed Jan 27 20:18:04 2010
  
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

*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      ak   1. initial release
 
1.2          ---      mk   2. Modified the function prototype declaration
                              for cmMemcpy, cmMemcmp, cmMemset, for the
                              data type of parameter 'len' from S16 to PTR
             ---      mg   3. Changes to pass through chksrc.
1.3          ---      bbk  1. Changed copyright header date.

1.4          ---      ns   1. Added extern "C" for making this file C++
                              compatible

1.5          ---      tej  1. Change in header
/main/7      ---       mj   1. MPLS release 1.2 changes.
/main/8      ---      st   1. Update for MAP Release 2.3
/main/9      ---  cm_lib_x_001.main_8    ve   1. Changing from S16 to MsgLen.
*********************************************************************91*/
