

/********************************************************************20**

     Name:     MTSS
  
     Type:     C source file
  
     Desc:     Version information
 
     File:     mt_err.h

     Sid:      mt_err.h@@/main/3 - Mon Nov 17 15:54:10 2008
  
     Prg:      ada

*********************************************************************21*/


#ifndef __MTERRH__
#define __MTERRH__
  


/* log error macro */
#define MTLOGERROR(errCls, errCode, errVal, errDesc) \
   SLogError( ENTNC, INSTNC, 0, __FILE__, __LINE__, \
             (ErrCls)errCls, (ErrVal)errCode, (ErrVal)errVal, errDesc )


/* defines */

#define   ERRMT       0
#define   EMTBASE     (ERRMT + 0)    /* reserved */
#define   EMTXXX      (EMTBASE)      /* reserved */

#define   EMT001      (ERRMT +    1)    /*      mt_ss.c:1310 */
#define   EMT002      (ERRMT +    2)    /*      mt_ss.c:1351 */
#define   EMT003      (ERRMT +    3)    /*      mt_ss.c:1448 */
#define   EMT004      (ERRMT +    4)    /*      mt_ss.c:1469 */
#define   EMT005      (ERRMT +    5)    /*      mt_ss.c:1518 */
#define   EMT006      (ERRMT +    6)    /*      mt_ss.c:1532 */
#define   EMT007      (ERRMT +    7)    /*      mt_ss.c:1969 */
#define   EMT008      (ERRMT +    8)    /*      mt_ss.c:1996 */
#define   EMT009      (ERRMT +    9)    /*      mt_ss.c:2098 */
#define   EMT010      (ERRMT +   10)    /*      mt_ss.c:2129 */
#define   EMT011      (ERRMT +   11)    /*      mt_ss.c:2160 */
#define   EMT012      (ERRMT +   12)    /*      mt_ss.c:2226 */
#define   EMT013      (ERRMT +   13)    /*      mt_ss.c:2302 */
#define   EMT014      (ERRMT +   14)    /*      mt_ss.c:2329 */
#define   EMT015      (ERRMT +   15)    /*      mt_ss.c:2370 */
#define   EMT016      (ERRMT +   16)    /*      mt_ss.c:2473 */
#define   EMT017      (ERRMT +   17)    /*      mt_ss.c:2498 */
#define   EMT018      (ERRMT +   18)    /*      mt_ss.c:2535 */
#define   EMT019      (ERRMT +   19)    /*      mt_ss.c:2578 */
#define   EMT020      (ERRMT +   20)    /*      mt_ss.c:2747 */
#define   EMT021      (ERRMT +   21)    /*      mt_ss.c:2772 */
#define   EMT022      (ERRMT +   22)    /*      mt_ss.c:2882 */
#define   EMT023      (ERRMT +   23)    /*      mt_ss.c:2972 */
#define   EMT024      (ERRMT +   24)    /*      mt_ss.c:3022 */
#define   EMT025      (ERRMT +   25)    /*      mt_ss.c:3086 */
#define   EMT026      (ERRMT +   26)    /*      mt_ss.c:3092 */
#define   EMT027      (ERRMT +   27)    /*      mt_ss.c:3141 */
#define   EMT028      (ERRMT +   28)    /*      mt_ss.c:3144 */
#define   EMT029      (ERRMT +   29)    /*      mt_ss.c:3453 */
#define   EMT030      (ERRMT +   30)    /*      mt_ss.c:3533 */
#define   EMT031      (ERRMT +   31)    /*      mt_ss.c:3613 */
#define   EMT032      (ERRMT +   32)    /*      mt_ss.c:3685 */
/* mt033.201 - addition of error codes */
#define   EMT033      (ERRMT +   33)    /*      mt_ss.c:3902 */
#define   EMT034      (ERRMT +   34)    /*      mt_ss.c:3984 */
#define   EMT035      (ERRMT +   35)    /*      mt_ss.c:4217 */
/* multi-core support */
#define   EMT036      (ERRMT +   36)    /*      mt_ss.c:1689 */
#define   EMT037      (ERRMT +   37)    /*      mt_ss.c:1709 */
#define   EMT038      (ERRMT +   38)    /*      mt_ss.c:1821 */
#define   EMT039      (ERRMT +   39)    /*      mt_ss.c:5085 */
#define   EMT040      (ERRMT +   40)    /*      mt_ss.c:5099 */
#define   EMT041      (ERRMT +   41)    /*      mt_ss.c:5106 */
#define   EMT042      (ERRMT +   42)    /*      mt_ss.c:5126 */
#define   EMT043      (ERRMT +   43)    /*      mt_ss.c:5133 */
#define   EMT044      (ERRMT +   44)    /*      mt_ss.c:5148 */
#define   EMT045      (ERRMT +   45)    /*      mt_ss.c:5155 */
#define   EMT046      (ERRMT +   46)    /*      mt_ss.c:5175 */



#endif

  
/********************************************************************30**
  
         End of file:     mt_err.h@@/main/3 - Mon Nov 17 15:54:10 2008
   
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
1.1          ---  ada   1. initial release

*********************************************************************81*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.2          ---      kp   1. MTSS-Solaris release 2.1
1.2+        mt028.201 kkj  1. Multiple procIds related changes
1.2+        mt033.201 vk   1. Addition of error code for SGetRegInfo
/main/3      ---      rp   1. SSI enhancements for Multi-core 
                              architecture support
*********************************************************************91*/
