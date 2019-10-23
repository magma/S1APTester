

/********************************************************************20**

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C Source code for error definitions

     File:     sz_err.h

     Sid:      sz_err.h@@/main/3 - Mon Jan 10 22:17:14 2011

     Prg:      rs

*********************************************************************21*/

#ifndef __SZERRH__
#define __SZERRH__

#ifndef SLOGERROR
#define SLOGERROR  SLogError
#endif

#ifdef SS_MULTIPLE_PROCS

#define SZLOGERROR(errCls, errCode, errVal, errDesc) \
        SLogError(szCbPtr->init.ent, szCbPtr->init.inst, szCbPtr->init.procId, \
                   __FILE__, __LINE__, errCls, errCode, errVal, errDesc)

#if (ERRCLASS & ERRCLS_DEBUG)    
#define SZLOGERROR_DEBUG(errCode, errVal, errDesc) \
        SLogError(szCbPtr->init.ent, szCbPtr->init.inst, szCbPtr->init.procId, \
                   __FILE__, __LINE__, ERRCLS_DEBUG, errCode, errVal, errDesc)
#else
#define SZLOGERROR_DEBUG(errCode, errVal, errDesc) 
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

#if (ERRCLASS & ERRCLS_INT_PAR)    
#define SZLOGERROR_INTFC(errCode, errVal, errDesc) \
        SLogError(szCbPtr->init.ent, szCbPtr->init.inst, szCbPtr->init.procId, \
                   __FILE__, __LINE__, ERRCLS_INT_PAR, errCode, errVal, errDesc)
#else
#define SZLOGERROR_INTFC(errCode, errVal, errDesc) 
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

#if (ERRCLASS & ERRCLS_ADD_RES)    
#define SZLOGERROR_ADD_RES(errCode, errVal, errDesc) \
        SLogError(szCbPtr->init.ent, szCbPtr->init.inst, szCbPtr->init.procId, \
                   __FILE__, __LINE__, ERRCLS_ADD_RES, errCode, errVal, errDesc)
#else
#define SZLOGERROR_ADD_RES(errCode, errVal, errDesc) 
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

#else /* SS_MULTIPLE_PROCS */

#define SZLOGERROR(errCls, errCode, errVal, errDesc) \
        SLogError(szCb.init.ent, szCb.init.inst, szCb.init.procId, \
                   __FILE__, __LINE__, errCls, errCode, errVal, errDesc)

#if (ERRCLASS & ERRCLS_DEBUG)    
#define SZLOGERROR_DEBUG(errCode, errVal, errDesc) \
        SLogError(szCb.init.ent, szCb.init.inst, szCb.init.procId, \
                   __FILE__, __LINE__, ERRCLS_DEBUG, errCode, errVal, errDesc)
#else
#define SZLOGERROR_DEBUG(errCode, errVal, errDesc) 
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

#if (ERRCLASS & ERRCLS_INT_PAR)    
#define SZLOGERROR_INTFC(errCode, errVal, errDesc) \
        SLogError(szCb.init.ent, szCb.init.inst, szCb.init.procId, \
                   __FILE__, __LINE__, ERRCLS_INT_PAR, errCode, errVal, errDesc)
#else
#define SZLOGERROR_INTFC(errCode, errVal, errDesc) 
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

#if (ERRCLASS & ERRCLS_ADD_RES)    
#define SZLOGERROR_ADD_RES(errCode, errVal, errDesc) \
        SLogError(szCb.init.ent, szCb.init.inst, szCb.init.procId, \
                   __FILE__, __LINE__, ERRCLS_ADD_RES, errCode, errVal, errDesc)
#else
#define SZLOGERROR_ADD_RES(errCode, errVal, errDesc) 
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

#endif /* SS_MULTIPLE_PROCS */

#define   ERRSZ       0
#define   ESZXXX      ERRSZ

#define   ESZ001      (ERRSZ +    1)    /*   sq_ex_ms.c: 222 */
#define   ESZ002      (ERRSZ +    2)    /*   sq_ex_ms.c: 259 */
#define   ESZ003      (ERRSZ +    3)    /*   sq_ex_ms.c: 334 */
#define   ESZ004      (ERRSZ +    4)    /*   sq_ex_ms.c: 339 */
#define   ESZ005      (ERRSZ +    5)    /*   sq_ex_ms.c: 394 */
#define   ESZ006      (ERRSZ +    6)    /*   sq_ex_ms.c: 405 */

#define   ESZ007      (ERRSZ +    7)    /*      sq_li.c: 347 */
#define   ESZ008      (ERRSZ +    8)    /*      sq_li.c: 364 */
#define   ESZ009      (ERRSZ +    9)    /*      sq_li.c: 381 */
#define   ESZ010      (ERRSZ +   10)    /*      sq_li.c: 533 */
#define   ESZ011      (ERRSZ +   11)    /*      sq_li.c: 642 */
#define   ESZ012      (ERRSZ +   12)    /*      sq_li.c: 660 */
#define   ESZ013      (ERRSZ +   13)    /*      sq_li.c: 803 */
#define   ESZ014      (ERRSZ +   14)    /*      sq_li.c: 854 */
#define   ESZ015      (ERRSZ +   15)    /*      sq_li.c: 872 */
#define   ESZ016      (ERRSZ +   16)    /*      sq_li.c: 883 */
#define   ESZ017      (ERRSZ +   17)    /*      sq_li.c: 894 */
#define   ESZ018      (ERRSZ +   18)    /*      sq_li.c: 907 */
#define   ESZ019      (ERRSZ +   19)    /*      sq_li.c:1007 */
#define   ESZ020      (ERRSZ +   20)    /*      sq_li.c:1025 */
#define   ESZ021      (ERRSZ +   21)    /*      sq_li.c:1037 */
#define   ESZ022      (ERRSZ +   22)    /*      sq_li.c:1052 */
#define   ESZ023      (ERRSZ +   23)    /*      sq_li.c:1146 */
#define   ESZ024      (ERRSZ +   24)    /*      sq_li.c:1168 */
#define   ESZ025      (ERRSZ +   25)    /*      sq_li.c:1179 */
#define   ESZ026      (ERRSZ +   26)    /*      sq_li.c:1262 */
#define   ESZ027      (ERRSZ +   27)    /*      sq_li.c:1280 */
#define   ESZ028      (ERRSZ +   28)    /*      sq_li.c:1291 */
#define   ESZ029      (ERRSZ +   29)    /*      sq_li.c:1303 */
#define   ESZ030      (ERRSZ +   30)    /*      sq_li.c:1341 */
#define   ESZ031      (ERRSZ +   31)    /*      sq_li.c:1359 */
#define   ESZ032      (ERRSZ +   32)    /*      sq_li.c:1377 */
#define   ESZ033      (ERRSZ +   33)    /*      sq_li.c:1514 */
#define   ESZ034      (ERRSZ +   34)    /*      sq_li.c:1532 */
#define   ESZ035      (ERRSZ +   35)    /*      sq_li.c:1544 */
#define   ESZ036      (ERRSZ +   36)    /*      sq_li.c:1566 */
#define   ESZ037      (ERRSZ +   37)    /*      sq_li.c:1636 */
#define   ESZ038      (ERRSZ +   38)    /*      sq_li.c:1654 */
#define   ESZ039      (ERRSZ +   39)    /*      sq_li.c:1666 */
#define   ESZ040      (ERRSZ +   40)    /*      sq_li.c:1719 */
#define   ESZ041      (ERRSZ +   41)    /*      sq_li.c:1819 */
#define   ESZ042      (ERRSZ +   42)    /*      sq_li.c:1841 */
#define   ESZ043      (ERRSZ +   43)    /*      sq_li.c:1853 */
#define   ESZ044      (ERRSZ +   44)    /*      sq_li.c:1870 */
#define   ESZ045      (ERRSZ +   45)    /*      sq_li.c:1950 */
#define   ESZ046      (ERRSZ +   46)    /*      sq_li.c:1968 */
#define   ESZ047      (ERRSZ +   47)    /*      sq_li.c:1980 */
#define   ESZ048      (ERRSZ +   48)    /*      sq_li.c:1993 */
#define   ESZ049      (ERRSZ +   49)    /*      sq_li.c:2009 */
#define   ESZ050      (ERRSZ +   50)    /*      sq_li.c:2072 */
#define   ESZ051      (ERRSZ +   51)    /*      sq_li.c:2090 */
#define   ESZ052      (ERRSZ +   52)    /*      sq_li.c:2102 */
#define   ESZ053      (ERRSZ +   53)    /*      sq_li.c:2117 */
#define   ESZ054      (ERRSZ +   54)    /*      sq_li.c:2152 */
#define   ESZ055      (ERRSZ +   55)    /*      sq_li.c:2374 */
#define   ESZ056      (ERRSZ +   56)    /*      sq_li.c:2396 */
#define   ESZ057      (ERRSZ +   57)    /*      sq_li.c:2408 */
#define   ESZ058      (ERRSZ +   58)    /*      sq_li.c:2425 */
#define   ESZ059      (ERRSZ +   59)    /*      sq_li.c:2492 */
#define   ESZ060      (ERRSZ +   60)    /*      sq_li.c:2817 */
#define   ESZ061      (ERRSZ +   61)    /*      sq_li.c:2827 */
#define   ESZ062      (ERRSZ +   62)    /*      sq_li.c:2862 */
#define   ESZ063      (ERRSZ +   63)    /*      sq_li.c:2950 */
#define   ESZ064      (ERRSZ +   64)    /*      sq_li.c:2984 */

#define   ESZ065      (ERRSZ +   65)    /*    sq_mgmt.c: 592 */
#define   ESZ066      (ERRSZ +   66)    /*    sq_mgmt.c: 713 */
#define   ESZ067      (ERRSZ +   67)    /*    sq_mgmt.c: 735 */
#define   ESZ068      (ERRSZ +   68)    /*    sq_mgmt.c: 778 */
#define   ESZ069      (ERRSZ +   69)    /*    sq_mgmt.c: 800 */
#define   ESZ070      (ERRSZ +   70)    /*    sq_mgmt.c:1292 */
#define   ESZ071      (ERRSZ +   71)    /*    sq_mgmt.c:1303 */
#define   ESZ072      (ERRSZ +   72)    /*    sq_mgmt.c:1359 */
#define   ESZ073      (ERRSZ +   73)    /*    sq_mgmt.c:1460 */
#define   ESZ074      (ERRSZ +   74)    /*    sq_mgmt.c:1480 */

#define   ESZ075      (ERRSZ +   75)    /*      sq_mi.c: 339 */
#define   ESZ076      (ERRSZ +   76)    /*      sq_mi.c: 359 */
#define   ESZ077      (ERRSZ +   77)    /*      sq_mi.c: 412 */
#define   ESZ078      (ERRSZ +   78)    /*      sq_mi.c: 473 */
#define   ESZ079      (ERRSZ +   79)    /*      sq_mi.c: 496 */
#define   ESZ080      (ERRSZ +   80)    /*      sq_mi.c: 539 */
#define   ESZ081      (ERRSZ +   81)    /*      sq_mi.c: 602 */
#define   ESZ082      (ERRSZ +   82)    /*      sq_mi.c: 626 */
#define   ESZ083      (ERRSZ +   83)    /*      sq_mi.c: 656 */
#define   ESZ084      (ERRSZ +   84)    /*      sq_mi.c: 672 */
#define   ESZ085      (ERRSZ +   85)    /*      sq_mi.c: 681 */
#define   ESZ086      (ERRSZ +   86)    /*      sq_mi.c: 742 */
#define   ESZ087      (ERRSZ +   87)    /*      sq_mi.c: 764 */
#define   ESZ088      (ERRSZ +   88)    /*      sq_mi.c: 814 */
#define   ESZ089      (ERRSZ +   89)    /*      sq_mi.c: 875 */
#define   ESZ090      (ERRSZ +   90)    /*      sq_mi.c: 948 */
#define   ESZ091      (ERRSZ +   91)    /*      sq_mi.c: 979 */
#define   ESZ092      (ERRSZ +   92)    /*      sq_mi.c: 991 */
#define   ESZ093      (ERRSZ +   93)    /*      sq_mi.c:1934 */
#define   ESZ094      (ERRSZ +   94)    /*      sq_mi.c:1958 */
#define   ESZ095      (ERRSZ +   95)    /*      sq_mi.c:1975 */
#define   ESZ096      (ERRSZ +   96)    /*      sq_mi.c:2396 */
#define   ESZ097      (ERRSZ +   97)    /*      sq_mi.c:2409 */
#define   ESZ098      (ERRSZ +   98)    /*      sq_mi.c:2653 */
#define   ESZ099      (ERRSZ +   99)    /*      sq_mi.c:2664 */
#define   ESZ100      (ERRSZ +  100)    /*      sq_mi.c:2675 */
#define   ESZ101      (ERRSZ +  101)    /*      sq_mi.c:3006 */
#define   ESZ102      (ERRSZ +  102)    /*      sq_mi.c:3015 */
#define   ESZ103      (ERRSZ +  103)    /*      sq_mi.c:3023 */
#define   ESZ104      (ERRSZ +  104)    /*      sq_mi.c:3174 */
#define   ESZ105      (ERRSZ +  105)    /*      sq_mi.c:3330 */

#define   ESZ106      (ERRSZ +  106)    /*   sq_msgfn.c: 283 */

#define   ESZ107      (ERRSZ +  107)    /*     sq_ndb.c: 169 */
#define   ESZ108      (ERRSZ +  108)    /*     sq_ndb.c: 186 */
#define   ESZ109      (ERRSZ +  109)    /*     sq_ndb.c: 197 */
#define   ESZ110      (ERRSZ +  110)    /*     sq_ndb.c: 540 */
#define   ESZ111      (ERRSZ +  111)    /*     sq_ndb.c: 551 */
#define   ESZ112      (ERRSZ +  112)    /*     sq_ndb.c: 563 */
#define   ESZ113      (ERRSZ +  113)    /*     sq_ndb.c: 685 */
#define   ESZ114      (ERRSZ +  114)    /*     sq_ndb.c: 696 */
#define   ESZ115      (ERRSZ +  115)    /*     sq_ndb.c: 708 */
#define   ESZ116      (ERRSZ +  116)    /*     sq_ndb.c: 721 */
#define   ESZ117      (ERRSZ +  117)    /*     sq_ndb.c:1223 */
#define   ESZ118      (ERRSZ +  118)    /*     sq_ndb.c:1253 */

#define   ESZ119      (ERRSZ +  119)    /*    sq_ptli.c:1865 */

#define   ESZ120      (ERRSZ +  120)    /*    sq_ptmi.c: 571 */
#define   ESZ121      (ERRSZ +  121)    /*    sq_ptmi.c: 609 */
#define   ESZ122      (ERRSZ +  122)    /*    sq_ptmi.c: 649 */
#define   ESZ123      (ERRSZ +  123)    /*    sq_ptmi.c: 690 */
#define   ESZ124      (ERRSZ +  124)    /*    sq_ptmi.c: 730 */
#define   ESZ125      (ERRSZ +  125)    /*    sq_ptmi.c: 769 */

#define   ESZ126      (ERRSZ +  126)    /*    sq_ptui.c: 932 */
#define   ESZ127      (ERRSZ +  127)    /*    sq_ptui.c: 969 */
#define   ESZ128      (ERRSZ +  128)    /*    sq_ptui.c:1006 */
#define   ESZ129      (ERRSZ +  129)    /*    sq_ptui.c:1043 */
#define   ESZ130      (ERRSZ +  130)    /*    sq_ptui.c:1080 */
#define   ESZ131      (ERRSZ +  131)    /*    sq_ptui.c:1117 */
#define   ESZ132      (ERRSZ +  132)    /*    sq_ptui.c:1154 */
#define   ESZ133      (ERRSZ +  133)    /*    sq_ptui.c:1191 */
#define   ESZ134      (ERRSZ +  134)    /*    sq_ptui.c:1228 */
#define   ESZ135      (ERRSZ +  135)    /*    sq_ptui.c:1265 */
#define   ESZ136      (ERRSZ +  136)    /*    sq_ptui.c:1304 */
#define   ESZ137      (ERRSZ +  137)    /*    sq_ptui.c:1341 */
#define   ESZ138      (ERRSZ +  138)    /*    sq_ptui.c:1379 */

#define   ESZ139      (ERRSZ +  139)    /*      sq_sm.c: 217 */
#define   ESZ140      (ERRSZ +  140)    /*      sq_sm.c: 315 */
#define   ESZ141      (ERRSZ +  141)    /*      sq_sm.c: 367 */
#define   ESZ142      (ERRSZ +  142)    /*      sq_sm.c: 554 */
#define   ESZ143      (ERRSZ +  143)    /*      sq_sm.c: 615 */
#define   ESZ144      (ERRSZ +  144)    /*      sq_sm.c: 628 */
#define   ESZ145      (ERRSZ +  145)    /*      sq_sm.c: 688 */
#define   ESZ146      (ERRSZ +  146)    /*      sq_sm.c: 701 */
#define   ESZ147      (ERRSZ +  147)    /*      sq_sm.c: 816 */
#define   ESZ148      (ERRSZ +  148)    /*      sq_sm.c: 831 */
#define   ESZ149      (ERRSZ +  149)    /*      sq_sm.c: 935 */
#define   ESZ150      (ERRSZ +  150)    /*      sq_sm.c:1147 */
#define   ESZ151      (ERRSZ +  151)    /*      sq_sm.c:1239 */
#define   ESZ152      (ERRSZ +  152)    /*      sq_sm.c:1285 */
#define   ESZ153      (ERRSZ +  153)    /*      sq_sm.c:1365 */
#define   ESZ154      (ERRSZ +  154)    /*      sq_sm.c:1442 */
#define   ESZ155      (ERRSZ +  155)    /*      sq_sm.c:1495 */
#define   ESZ156      (ERRSZ +  156)    /*      sq_sm.c:1637 */
#define   ESZ157      (ERRSZ +  157)    /*      sq_sm.c:1700 */

#define   ESZ158      (ERRSZ +  158)    /* sq_smlimme.c: 702 */
#define   ESZ159      (ERRSZ +  159)    /* sq_smlimme.c: 713 */

#define   ESZ160      (ERRSZ +  160)    /* sq_smuienb.c: 704 */
#define   ESZ161      (ERRSZ +  161)    /* sq_smuienb.c: 713 */

#define   ESZ162      (ERRSZ +  162)    /* sq_smuimme.c: 705 */

#define   ESZ163      (ERRSZ +  163)    /*     sq_tmr.c: 186 */
#define   ESZ164      (ERRSZ +  164)    /*     sq_tmr.c: 246 */
#define   ESZ165      (ERRSZ +  165)    /*     sq_tmr.c: 412 */

#define   ESZ166      (ERRSZ +  166)    /*      sq_ui.c: 178 */
#define   ESZ167      (ERRSZ +  167)    /*      sq_ui.c: 213 */
#define   ESZ168      (ERRSZ +  168)    /*      sq_ui.c: 292 */
#define   ESZ169      (ERRSZ +  169)    /*      sq_ui.c: 372 */
#define   ESZ170      (ERRSZ +  170)    /*      sq_ui.c: 559 */
#define   ESZ171      (ERRSZ +  171)    /*      sq_ui.c: 756 */
#define   ESZ172      (ERRSZ +  172)    /*      sq_ui.c: 909 */
#define   ESZ173      (ERRSZ +  173)    /*      sq_ui.c:1000 */
#define   ESZ174      (ERRSZ +  174)    /*      sq_ui.c:1012 */
#define   ESZ175      (ERRSZ +  175)    /*      sq_ui.c:1086 */
#define   ESZ176      (ERRSZ +  176)    /*      sq_ui.c:1216 */
#define   ESZ177      (ERRSZ +  177)    /*      sq_ui.c:1390 */
#define   ESZ178      (ERRSZ +  178)    /*      sq_ui.c:1568 */
#define   ESZ179      (ERRSZ +  179)    /*      sq_ui.c:1742 */
#define   ESZ180      (ERRSZ +  180)    /*      sq_ui.c:1792 */
#define   ESZ181      (ERRSZ +  181)    /*      sq_ui.c:1817 */
#define   ESZ182      (ERRSZ +  182)    /*      sq_ui.c:1954 */
#define   ESZ183      (ERRSZ +  183)    /*      sq_ui.c:2010 */
#define   ESZ184      (ERRSZ +  184)    /*      sq_ui.c:2067 */
#define   ESZ185      (ERRSZ +  185)    /*      sq_ui.c:2119 */
#define   ESZ186      (ERRSZ +  186)    /*      sq_ui.c:2175 */
#define   ESZ187      (ERRSZ +  187)    /*      sq_ui.c:2231 */
#define   ESZ188      (ERRSZ +  188)    /*      sq_ui.c:2287 */
#define   ESZ189      (ERRSZ +  189)    /*      sq_ui.c:2507 */
#define   ESZ190      (ERRSZ +  190)    /*      sq_ui.c:2529 */


#endif /* __SZERRH__ */

/**********************************************************************

         End of file:     sz_err.h@@/main/3 - Mon Jan 10 22:17:14 2011

**********************************************************************/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/3      ---      vvashishth  1. Updated for S1AP release 3.1
*********************************************************************91*/
