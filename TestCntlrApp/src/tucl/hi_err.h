

/********************************************************************20**
 
     Name:     TCP UDP Convergence Layer error file.

     Type:     C include file

     Desc:     Error Hash Defines required by HI layer

     File:     hi_err.h

     Sid:      hi_err.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:39:00 2015

     Prg:      asa

*********************************************************************21*/
  
#ifndef __HIERRH__
#define __HIERRH__



#if (ERRCLASS & ERRCLS_DEBUG)
#define HILOGERROR_DEBUGPST(procId, ent, errCode, errVal, inst, errDesc)        \
        SLogError(ent, inst, procId,        \
                  __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,     \
                  (ErrCode)errCode, (ErrVal)errVal, errDesc)
#else
#define HILOGERROR_DEBUGPST(procId, ent, errCode, errVal, inst, errDesc)
#endif /* ERRCLS_DEBUG */

/* hi031.201: Fix for g++ compilation warning*/
#if (ERRCLASS & ERRCLS_DEBUG)
#define HILOGERROR_DEBUG(errCode, errVal, inst, errDesc)        \
        SLogError(hiCb.init.ent, inst, hiCb.init.procId,        \
                  __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,   \
                  (ErrCode)errCode, (ErrVal)errVal, errDesc)
#else
#define HILOGERROR_DEBUG(errCode, errVal, inst, errDesc)
#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
#define HILOGERROR_INT_PAR(errCode, errVal, inst, errDesc)      \
        SLogError(hiCb.init.ent, inst, hiCb.init.procId,        \
                  __FILE__, __LINE__, (ErrCls)ERRCLS_INT_PAR,   \
                  (ErrCode)errCode, (ErrVal)errVal, errDesc)
#else
#define HILOGERROR_INT_PAR(errCode, errVal, inst, errDesc)
#endif /* ERRCLS_INT_PAR */

#if (ERRCLASS & ERRCLS_ADD_RES)
#define HILOGERROR_ADD_RES(errCode, errVal, inst, errDesc)      \
        SLogError(hiCb.init.ent, inst, hiCb.init.procId,        \
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,   \
                  (ErrCode)errCode, (ErrVal)errVal, errDesc)
#else
#define HILOGERROR_ADD_RES(errCode, errVal, errDesc, inst)
#endif /* ERRCLS_ADD_RES */

#define   EHIBASE     0
#define   ERRHI       (EHIBASE   +0)    /* reserved */
 
#define   EHI001      (ERRHI +    1)    /*   hi_accsh.c: 203 */
#define   EHI002      (ERRHI +    2)    /*   hi_accsh.c: 288 */
#define   EHI003      (ERRHI +    3)    /*   hi_accsh.c: 290 */

#define   EHI004      (ERRHI +    4)    /*   hi_ex_ms.c: 204 */
#define   EHI005      (ERRHI +    5)    /*   hi_ex_ms.c: 242 */
#define   EHI006      (ERRHI +    6)    /*   hi_ex_ms.c: 394 */
#define   EHI007      (ERRHI +    7)    /*   hi_ex_ms.c: 414 */
#define   EHI008      (ERRHI +    8)    /*   hi_ex_ms.c: 422 */

#define   EHI009      (ERRHI +    9)    /*         hi.h: 357 */
#define   EHI010      (ERRHI +   10)    /*         hi.h: 372 */
#define   EHI011      (ERRHI +   11)    /*         hi.h: 382 */

#define   EHI012      (ERRHI +   12)    /*    tl_bdy1.c: 434 */
#define   EHI013      (ERRHI +   13)    /*    tl_bdy1.c: 532 */
#define   EHI014      (ERRHI +   14)    /*    tl_bdy1.c: 653 */
#define   EHI015      (ERRHI +   15)    /*    tl_bdy1.c: 698 */
#define   EHI016      (ERRHI +   16)    /*    tl_bdy1.c: 759 */
#define   EHI017      (ERRHI +   17)    /*    tl_bdy1.c: 811 */
#define   EHI018      (ERRHI +   18)    /*    tl_bdy1.c: 837 */
#define   EHI019      (ERRHI +   19)    /*    tl_bdy1.c: 896 */
#define   EHI020      (ERRHI +   20)    /*    tl_bdy1.c:1109 */
#define   EHI021      (ERRHI +   21)    /*    tl_bdy1.c:1183 */
#define   EHI022      (ERRHI +   22)    /*    tl_bdy1.c:1257 */
#define   EHI023      (ERRHI +   23)    /*    tl_bdy1.c:1374 */
#define   EHI024      (ERRHI +   24)    /*    tl_bdy1.c:1421 */
#define   EHI025      (ERRHI +   25)    /*    tl_bdy1.c:1435 */
#define   EHI026      (ERRHI +   26)    /*    tl_bdy1.c:1454 */
#define   EHI027      (ERRHI +   27)    /*    tl_bdy1.c:1668 */
#define   EHI028      (ERRHI +   28)    /*    tl_bdy1.c:1721 */
#define   EHI029      (ERRHI +   29)    /*    tl_bdy1.c:1755 */
#define   EHI030      (ERRHI +   30)    /*    tl_bdy1.c:1775 */
#define   EHI031      (ERRHI +   31)    /*    tl_bdy1.c:1960 */
#define   EHI032      (ERRHI +   32)    /*    tl_bdy1.c:2104 */
#define   EHI033      (ERRHI +   33)    /*    tl_bdy1.c:2149 */
#define   EHI034      (ERRHI +   34)    /*    tl_bdy1.c:2204 */
#define   EHI035      (ERRHI +   35)    /*    tl_bdy1.c:2225 */
#define   EHI036      (ERRHI +   36)    /*    tl_bdy1.c:2358 */
#define   EHI037      (ERRHI +   37)    /*    tl_bdy1.c:2408 */
#define   EHI038      (ERRHI +   38)    /*    tl_bdy1.c:2421 */
#define   EHI039      (ERRHI +   39)    /*    tl_bdy1.c:2435 */
#define   EHI040      (ERRHI +   40)    /*    tl_bdy1.c:2452 */
#define   EHI041      (ERRHI +   41)    /*    tl_bdy1.c:2560 */
#define   EHI042      (ERRHI +   42)    /*    tl_bdy1.c:2581 */
#define   EHI043      (ERRHI +   43)    /*    tl_bdy1.c:2596 */
#define   EHI044      (ERRHI +   44)    /*    tl_bdy1.c:2825 */
#define   EHI045      (ERRHI +   45)    /*    tl_bdy1.c:2864 */
#define   EHI046      (ERRHI +   46)    /*    tl_bdy1.c:2916 */
#define   EHI047      (ERRHI +   47)    /*    tl_bdy1.c:3027 */
#define   EHI048      (ERRHI +   48)    /*    tl_bdy1.c:3063 */
#define   EHI049      (ERRHI +   49)    /*    tl_bdy1.c:3077 */
#define   EHI050      (ERRHI +   50)    /*    tl_bdy1.c:3284 */
#define   EHI051      (ERRHI +   51)    /*    tl_bdy1.c:3316 */
#define   EHI052      (ERRHI +   52)    /*    tl_bdy1.c:3375 */
#define   EHI053      (ERRHI +   53)    /*    tl_bdy1.c:3482 */
#define   EHI054      (ERRHI +   54)    /*    tl_bdy1.c:3938 */
#define   EHI055      (ERRHI +   55)    /*    tl_bdy1.c:4240 */
#define   EHI056      (ERRHI +   56)    /*    tl_bdy1.c:4412 */
#define   EHI057      (ERRHI +   57)    /*    tl_bdy1.c:4618 */
#define   EHI058      (ERRHI +   58)    /*    tl_bdy1.c:4748 */
#define   EHI059      (ERRHI +   59)    /*    tl_bdy1.c:4888 */
#define   EHI060      (ERRHI +   60)    /*    tl_bdy1.c:4925 */
#define   EHI061      (ERRHI +   61)    /*    tl_bdy1.c:4940 */
#define   EHI062      (ERRHI +   62)    /*    tl_bdy1.c:4952 */
#define   EHI063      (ERRHI +   63)    /*    tl_bdy1.c:5077 */

#define   EHI064      (ERRHI +   64)    /*    tl_bdy2.c: 220 */
#define   EHI065      (ERRHI +   65)    /*    tl_bdy2.c: 243 */
#define   EHI066      (ERRHI +   66)    /*    tl_bdy2.c: 297 */
#define   EHI067      (ERRHI +   67)    /*    tl_bdy2.c: 310 */
#define   EHI068      (ERRHI +   68)    /*    tl_bdy2.c:1445 */
#define   EHI069      (ERRHI +   69)    /*    tl_bdy2.c:1545 */
#define   EHI070      (ERRHI +   70)    /*    tl_bdy2.c:1552 */
#define   EHI071      (ERRHI +   71)    /*    tl_bdy2.c:1559 */
#define   EHI072      (ERRHI +   72)    /*    tl_bdy2.c:1576 */
#define   EHI073      (ERRHI +   73)    /*    tl_bdy2.c:2119 */
#define   EHI074      (ERRHI +   74)    /*    tl_bdy2.c:2126 */
#define   EHI075      (ERRHI +   75)    /*    tl_bdy2.c:2191 */
#define   EHI076      (ERRHI +   76)    /*    tl_bdy2.c:2207 */
#define   EHI077      (ERRHI +   77)    /*    tl_bdy2.c:2221 */
#define   EHI078      (ERRHI +   78)    /*    tl_bdy2.c:2230 */
#define   EHI079      (ERRHI +   79)    /*    tl_bdy2.c:2301 */
#define   EHI080      (ERRHI +   80)    /*    tl_bdy2.c:2359 */
#define   EHI081      (ERRHI +   81)    /*    tl_bdy2.c:2411 */
#define   EHI082      (ERRHI +   82)    /*    tl_bdy2.c:3174 */
#define   EHI083      (ERRHI +   83)    /*    tl_bdy2.c:3188 */
#define   EHI084      (ERRHI +   84)    /*    tl_bdy2.c:3302 */
#define   EHI085      (ERRHI +   85)    /*    tl_bdy2.c:5146 */
#define   EHI086      (ERRHI +   86)    /*    tl_bdy2.c:5186 */
#define   EHI087      (ERRHI +   87)    /*    tl_bdy2.c:5321 */

#define   EHI088      (ERRHI +   88)    /*    tl_bdy3.c:1800 */
#define   EHI089      (ERRHI +   89)    /*    tl_bdy3.c:1815 */
#define   EHI090      (ERRHI +   90)    /*    tl_bdy3.c:1851 */
#define   EHI091      (ERRHI +   91)    /*    tl_bdy3.c:2531 */
#define   EHI092      (ERRHI +   92)    /*    tl_bdy3.c:4364 */
#define   EHI093      (ERRHI +   93)    /*    tl_bdy3.c:4377 */
#define   EHI094      (ERRHI +   94)    /*    tl_bdy3.c:4391 */
#define   EHI095      (ERRHI +   95)    /*    tl_bdy3.c:4425 */
#define   EHI096      (ERRHI +   96)    /*    tl_bdy3.c:4441 */
/* hi005.201 Introducing a new error macros for conjestion timer 
 *           changes */

#define   EHI097      (ERRHI +   97)    /*    tl_bdy2.c:5729 */
#define   EHI098      (ERRHI +   98)    /*    tl_bdy2.c:5735 */
#define   EHI099      (ERRHI +   99)    /*    tl_bdy2.c:5753 */
#define   EHI100      (ERRHI +   100)    /*    tl_bdy2.c:5753 */
/* hi009.201  rss   1. Added EHI101 macro */
#define   EHI101      (ERRHI +   101)    /*    tl_bdy2.c:5753 */
#endif /* __HIERRH__ */
 


/********************************************************************30**
 
         End of file:     hi_err.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:39:00 2015

*********************************************************************31*/
 

/********************************************************************40**
 
        Notes:
 
*********************************************************************41*/
 
/********************************************************************50**
 
*********************************************************************51*/
 

/********************************************************************60**
 
        Revision history:
 
*********************************************************************61*/
/********************************************************************70**
  
  version    initials                   description
-----------  ---------  ------------------------------------------------
 
*********************************************************************71*/
 
/********************************************************************80**
 
*********************************************************************81*/
/********************************************************************90**
 
    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
1.1         ---      asa  1. initial release.
/main/4     ---      cvp  1. updated error codes.
                          2. changed the copyright header.
/main/4     ---      cvp  1. updated error codes.
                          2. changed the copyright header.
/main/5     ---      kp   1. Updated for release 1.5.
/main/5    hi002.105 ss   1. error code for multiple process added.
/main/5+   hi013.105 svp  1. Added two new HIT primitives.
                             HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().
                          2. Updated the error codes.
/main/5+   hi014.105 svp  1. Modified statistics req to include messages
                              Tx/Rx in bytes per con per thread 
                           2. done perfomance optimization
/main/6      ---       hs   1. Updated for release of 2.1
/main/6+   hi005.201  rss 1. Introducing a new error macros for conjestion timer 
                              changes
/main/6    hi009.201  rss   1. Added EHI101 macro.
/main/6    hi031.201 ragrawal 1. Fix for g++ compilation warning.
*********************************************************************91*/

