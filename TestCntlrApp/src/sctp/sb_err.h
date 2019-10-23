


/********************************************************************20**

     Name:     sb_err.h - Error Defines for  SCTP layer.

     Type:     C include file

     Desc:     defines for the SLogError type errors

     File:     sb_err.h

     Sid:      sb_err.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:14 2015

     Prg:      mrw

*********************************************************************21*/

#ifndef __SBERRH__
#define __SBERRH__

/*

*   sb_err.h -
*
*   Defines declared in this file correspond to defines used by the
*   following TRILLIUM software:
*     part no.                      description
*     --------    ----------------------------------------------
*     1000191                   SCTP
*/


/* macros */

#define SBLOGINVSEL \
        SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,            \
                  __FILE__, __LINE__,                                   \
                  ERRCLS_DEBUG, ESB312,                                 \
                  0, "Invalid selector");

#define SBLOGERROR(errCls, errCode, errVal, errDesc)                    \
        SLogError(sbGlobalCb.sbInit.ent, sbGlobalCb.sbInit.inst,        \
                  sbGlobalCb.sbInit.procId, __FILE__, __LINE__,         \
                  (ErrCls)errCls, (ErrCode)errCode,                     \
                  (ErrVal)errVal, errDesc)


/* defines */
#define   ESBBASE     0

/* sb003.103: SATELLITE SCTP feature */
#define   ESBXXX     0

#define   ERRSB       ESBBASE           /* RFC 4460 -- RTR   */
#define   ESB000      (ESBBASE   +0)    /* reserved          */

#define   ESB001      (ERRSB +    1)    /*    sb_bdy1.c: 402 */
#define   ESB002      (ERRSB +    2)    /*    sb_bdy1.c: 525 */
#define   ESB003      (ERRSB +    3)    /*    sb_bdy1.c: 541 */
#define   ESB004      (ERRSB +    4)    /*    sb_bdy1.c: 602 */
#define   ESB005      (ERRSB +    5)    /*    sb_bdy1.c: 662 */
#define   ESB006      (ERRSB +    6)    /*    sb_bdy1.c: 732 */
#define   ESB007      (ERRSB +    7)    /*    sb_bdy1.c: 822 */
#define   ESB008      (ERRSB +    8)    /*    sb_bdy1.c: 915 */
#define   ESB009      (ERRSB +    9)    /*    sb_bdy1.c:1265 */
#define   ESB010      (ERRSB +   10)    /*    sb_bdy1.c:1360 */
#define   ESB011      (ERRSB +   11)    /*    sb_bdy1.c:1375 */
#define   ESB012      (ERRSB +   12)    /*    sb_bdy1.c:1405 */
#define   ESB013      (ERRSB +   13)    /*    sb_bdy1.c:1419 */
#define   ESB014      (ERRSB +   14)    /*    sb_bdy1.c:1515 */
#define   ESB015      (ERRSB +   15)    /*    sb_bdy1.c:1591 */
#define   ESB016      (ERRSB +   16)    /*    sb_bdy1.c:1673 */
#define   ESB017      (ERRSB +   17)    /*    sb_bdy1.c:1686 */
#define   ESB018      (ERRSB +   18)    /*    sb_bdy1.c:1726 */
#define   ESB019      (ERRSB +   19)    /*    sb_bdy1.c:1739 */
#define   ESB020      (ERRSB +   20)    /*    sb_bdy1.c:1769 */
#define   ESB021      (ERRSB +   21)    /*    sb_bdy1.c:1850 */
#define   ESB022      (ERRSB +   22)    /*    sb_bdy1.c:1892 */
#define   ESB023      (ERRSB +   23)    /*    sb_bdy1.c:1941 */
#define   ESB024      (ERRSB +   24)    /*    sb_bdy1.c:2053 */
#define   ESB025      (ERRSB +   25)    /*    sb_bdy1.c:2101 */
#define   ESB026      (ERRSB +   26)    /*    sb_bdy1.c:2126 */
#define   ESB027      (ERRSB +   27)    /*    sb_bdy1.c:2155 */
#define   ESB028      (ERRSB +   28)    /*    sb_bdy1.c:2313 */
#define   ESB029      (ERRSB +   29)    /*    sb_bdy1.c:2368 */
#define   ESB030      (ERRSB +   30)    /*    sb_bdy1.c:2436 */
#define   ESB031      (ERRSB +   31)    /*    sb_bdy1.c:2466 */
#define   ESB032      (ERRSB +   32)    /*    sb_bdy1.c:2481 */
#define   ESB033      (ERRSB +   33)    /*    sb_bdy1.c:2499 */
#define   ESB034      (ERRSB +   34)    /*    sb_bdy1.c:2609 */
#define   ESB035      (ERRSB +   35)    /*    sb_bdy1.c:2627 */
#define   ESB036      (ERRSB +   36)    /*    sb_bdy1.c:2773 */
#define   ESB037      (ERRSB +   37)    /*    sb_bdy1.c:2803 */
#define   ESB038      (ERRSB +   38)    /*    sb_bdy1.c:2821 */
#define   ESB039      (ERRSB +   39)    /*    sb_bdy1.c:2838 */
#define   ESB040      (ERRSB +   40)    /*    sb_bdy1.c:2858 */
#define   ESB041      (ERRSB +   41)    /*    sb_bdy1.c:2873 */
#define   ESB042      (ERRSB +   42)    /*    sb_bdy1.c:2889 */
#define   ESB043      (ERRSB +   43)    /*    sb_bdy1.c:2987 */
#define   ESB044      (ERRSB +   44)    /*    sb_bdy1.c:3207 */
#define   ESB045      (ERRSB +   45)    /*    sb_bdy1.c:3236 */
#define   ESB046      (ERRSB +   46)    /*    sb_bdy1.c:3389 */
#define   ESB047      (ERRSB +   47)    /*    sb_bdy1.c:3418 */
#define   ESB048      (ERRSB +   48)    /*    sb_bdy1.c:3435 */
#define   ESB049      (ERRSB +   49)    /*    sb_bdy1.c:3466 */
#define   ESB050      (ERRSB +   50)    /*    sb_bdy1.c:3495 */
#define   ESB051      (ERRSB +   51)    /*    sb_bdy1.c:3552 */
#define   ESB052      (ERRSB +   52)    /*    sb_bdy1.c:3566 */
#define   ESB053      (ERRSB +   53)    /*    sb_bdy1.c:3705 */
#define   ESB054      (ERRSB +   54)    /*    sb_bdy1.c:3897 */
#define   ESB055      (ERRSB +   55)    /*    sb_bdy1.c:3925 */
#define   ESB056      (ERRSB +   56)    /*    sb_bdy1.c:3938 */
#define   ESB057      (ERRSB +   57)    /*    sb_bdy1.c:4003 */
#define   ESB058      (ERRSB +   58)    /*    sb_bdy1.c:4022 */
#define   ESB059      (ERRSB +   59)    /*    sb_bdy1.c:4224 */
#define   ESB060      (ERRSB +   60)    /*    sb_bdy1.c:4252 */
#define   ESB061      (ERRSB +   61)    /*    sb_bdy1.c:4267 */
#define   ESB062      (ERRSB +   62)    /*    sb_bdy1.c:4285 */
#define   ESB063      (ERRSB +   63)    /*    sb_bdy1.c:4380 */
#define   ESB064      (ERRSB +   64)    /*    sb_bdy1.c:4409 */
#define   ESB065      (ERRSB +   65)    /*    sb_bdy1.c:4424 */
#define   ESB066      (ERRSB +   66)    /*    sb_bdy1.c:4448 */
#define   ESB067      (ERRSB +   67)    /*    sb_bdy1.c:4595 */
#define   ESB068      (ERRSB +   68)    /*    sb_bdy1.c:4623 */
#define   ESB069      (ERRSB +   69)    /*    sb_bdy1.c:4640 */
#define   ESB070      (ERRSB +   70)    /*    sb_bdy1.c:4661 */
#define   ESB071      (ERRSB +   71)    /*    sb_bdy1.c:4743 */
#define   ESB072      (ERRSB +   72)    /*    sb_bdy1.c:4977 */
#define   ESB073      (ERRSB +   73)    /*    sb_bdy1.c:5005 */
#define   ESB074      (ERRSB +   74)    /*    sb_bdy1.c:5024 */
#define   ESB075      (ERRSB +   75)    /*    sb_bdy1.c:5042 */
#define   ESB076      (ERRSB +   76)    /*    sb_bdy1.c:5149 */
#define   ESB077      (ERRSB +   77)    /*    sb_bdy1.c:5220 */
#define   ESB078      (ERRSB +   78)    /*    sb_bdy1.c:5239 */
#define   ESB079      (ERRSB +   79)    /*    sb_bdy1.c:5258 */
#define   ESB080      (ERRSB +   80)    /*    sb_bdy1.c:5295 */
#define   ESB081      (ERRSB +   81)    /*    sb_bdy1.c:5342 */
#define   ESB082      (ERRSB +   82)    /*    sb_bdy1.c:5426 */
#define   ESB083      (ERRSB +   83)    /*    sb_bdy1.c:5583 */
#define   ESB084      (ERRSB +   84)    /*    sb_bdy1.c:5648 */
#define   ESB085      (ERRSB +   85)    /*    sb_bdy1.c:5686 */
#define   ESB086      (ERRSB +   86)    /*    sb_bdy1.c:5711 */
#define   ESB087      (ERRSB +   87)    /*    sb_bdy1.c:5732 */
#define   ESB088      (ERRSB +   88)    /*    sb_bdy1.c:5748 */
#define   ESB089      (ERRSB +   89)    /*    sb_bdy1.c:5786 */
#define   ESB090      (ERRSB +   90)    /*    sb_bdy1.c:5801 */
#define   ESB091      (ERRSB +   91)    /*    sb_bdy1.c:5834 */
#define   ESB092      (ERRSB +   92)    /*    sb_bdy1.c:5932 */
#define   ESB093      (ERRSB +   93)    /*    sb_bdy1.c:6020 */
#define   ESB094      (ERRSB +   94)    /*    sb_bdy1.c:6049 */
#define   ESB095      (ERRSB +   95)    /*    sb_bdy1.c:6068 */
#define   ESB096      (ERRSB +   96)    /*    sb_bdy1.c:6217 */
#define   ESB097      (ERRSB +   97)    /*    sb_bdy1.c:6285 */
#define   ESB098      (ERRSB +   98)    /*    sb_bdy1.c:6324 */
#define   ESB099      (ERRSB +   99)    /*    sb_bdy1.c:6348 */
#define   ESB100      (ERRSB +  100)    /*    sb_bdy1.c:6542 */
#define   ESB101      (ERRSB +  101)    /*    sb_bdy1.c:6564 */
#define   ESB102      (ERRSB +  102)    /*    sb_bdy1.c:6580 */
#define   ESB103      (ERRSB +  103)    /*    sb_bdy1.c:6609 */
#define   ESB104      (ERRSB +  104)    /*    sb_bdy1.c:6629 */

#define   ESB105      (ERRSB +  105)    /*    sb_bdy2.c: 255 */
#define   ESB106      (ERRSB +  106)    /*    sb_bdy2.c: 304 */
#define   ESB107      (ERRSB +  107)    /*    sb_bdy2.c: 433 */
#define   ESB108      (ERRSB +  108)    /*    sb_bdy2.c: 441 */
#define   ESB109      (ERRSB +  109)    /*    sb_bdy2.c: 473 */
#define   ESB110      (ERRSB +  110)    /*    sb_bdy2.c: 569 */
#define   ESB111      (ERRSB +  111)    /*    sb_bdy2.c: 590 */
#define   ESB112      (ERRSB +  112)    /*    sb_bdy2.c: 644 */
#define   ESB113      (ERRSB +  113)    /*    sb_bdy2.c: 664 */
#define   ESB114      (ERRSB +  114)    /*    sb_bdy2.c: 688 */
#define   ESB115      (ERRSB +  115)    /*    sb_bdy2.c: 745 */
#define   ESB116      (ERRSB +  116)    /*    sb_bdy2.c: 753 */
#define   ESB117      (ERRSB +  117)    /*    sb_bdy2.c: 771 */
#define   ESB118      (ERRSB +  118)    /*    sb_bdy2.c: 799 */
#define   ESB119      (ERRSB +  119)    /*    sb_bdy2.c: 823 */
#define   ESB120      (ERRSB +  120)    /*    sb_bdy2.c: 842 */
#define   ESB121      (ERRSB +  121)    /*    sb_bdy2.c: 862 */
#define   ESB122      (ERRSB +  122)    /*    sb_bdy2.c: 917 */
#define   ESB123      (ERRSB +  123)    /*    sb_bdy2.c: 929 */
#define   ESB124      (ERRSB +  124)    /*    sb_bdy2.c: 958 */
#define   ESB125      (ERRSB +  125)    /*    sb_bdy2.c: 968 */
#define   ESB126      (ERRSB +  126)    /*    sb_bdy2.c:1047 */
#define   ESB127      (ERRSB +  127)    /*    sb_bdy2.c:1054 */
#define   ESB128      (ERRSB +  128)    /*    sb_bdy2.c:1174 */
#define   ESB129      (ERRSB +  129)    /*    sb_bdy2.c:1232 */
#define   ESB130      (ERRSB +  130)    /*    sb_bdy2.c:1239 */
#define   ESB131      (ERRSB +  131)    /*    sb_bdy2.c:1393 */
#define   ESB132      (ERRSB +  132)    /*    sb_bdy2.c:1467 */
#define   ESB133      (ERRSB +  133)    /*    sb_bdy2.c:1474 */
#define   ESB134      (ERRSB +  134)    /*    sb_bdy2.c:1485 */
#define   ESB135      (ERRSB +  135)    /*    sb_bdy2.c:1644 */
#define   ESB136      (ERRSB +  136)    /*    sb_bdy2.c:1713 */
#define   ESB137      (ERRSB +  137)    /*    sb_bdy2.c:1720 */
#define   ESB138      (ERRSB +  138)    /*    sb_bdy2.c:1792 */
#define   ESB139      (ERRSB +  139)    /*    sb_bdy2.c:1799 */
#define   ESB140      (ERRSB +  140)    /*    sb_bdy2.c:1816 */
#define   ESB141      (ERRSB +  141)    /*    sb_bdy2.c:1828 */
#define   ESB142      (ERRSB +  142)    /*    sb_bdy2.c:1849 */
#define   ESB143      (ERRSB +  143)    /*    sb_bdy2.c:1867 */
#define   ESB144      (ERRSB +  144)    /*    sb_bdy2.c:1892 */
#define   ESB145      (ERRSB +  145)    /*    sb_bdy2.c:1908 */
#define   ESB146      (ERRSB +  146)    /*    sb_bdy2.c:1966 */
#define   ESB147      (ERRSB +  147)    /*    sb_bdy2.c:1973 */
#define   ESB148      (ERRSB +  148)    /*    sb_bdy2.c:2030 */
#define   ESB149      (ERRSB +  149)    /*    sb_bdy2.c:2096 */
#define   ESB150      (ERRSB +  150)    /*    sb_bdy2.c:2220 */
#define   ESB151      (ERRSB +  151)    /*    sb_bdy2.c:2232 */
#define   ESB152      (ERRSB +  152)    /*    sb_bdy2.c:2258 */
#define   ESB153      (ERRSB +  153)    /*    sb_bdy2.c:2353 */
#define   ESB154      (ERRSB +  154)    /*    sb_bdy2.c:2360 */
#define   ESB155      (ERRSB +  155)    /*    sb_bdy2.c:2500 */
#define   ESB156      (ERRSB +  156)    /*    sb_bdy2.c:2507 */
#define   ESB157      (ERRSB +  157)    /*    sb_bdy2.c:2569 */
#define   ESB158      (ERRSB +  158)    /*    sb_bdy2.c:2581 */
#define   ESB159      (ERRSB +  159)    /*    sb_bdy2.c:2619 */
#define   ESB160      (ERRSB +  160)    /*    sb_bdy2.c:2710 */
#define   ESB161      (ERRSB +  161)    /*    sb_bdy2.c:2743 */
#define   ESB162      (ERRSB +  162)    /*    sb_bdy2.c:2769 */
#define   ESB163      (ERRSB +  163)    /*    sb_bdy2.c:2804 */
#define   ESB164      (ERRSB +  164)    /*    sb_bdy2.c:2845 */
#define   ESB165      (ERRSB +  165)    /*    sb_bdy2.c:2877 */
#define   ESB166      (ERRSB +  166)    /*    sb_bdy2.c:2910 */
#define   ESB167      (ERRSB +  167)    /*    sb_bdy2.c:2973 */
#define   ESB168      (ERRSB +  168)    /*    sb_bdy2.c:2983 */
#define   ESB169      (ERRSB +  169)    /*    sb_bdy2.c:3018 */
#define   ESB170      (ERRSB +  170)    /*    sb_bdy2.c:3037 */
#define   ESB171      (ERRSB +  171)    /*    sb_bdy2.c:3579 */
#define   ESB172      (ERRSB +  172)    /*    sb_bdy2.c:3607 */
#define   ESB173      (ERRSB +  173)    /*    sb_bdy2.c:3671 */
#define   ESB174      (ERRSB +  174)    /*    sb_bdy2.c:3722 */
#define   ESB175      (ERRSB +  175)    /*    sb_bdy2.c:3808 */
#define   ESB176      (ERRSB +  176)    /*    sb_bdy2.c:3818 */
#define   ESB177      (ERRSB +  177)    /*    sb_bdy2.c:3841 */
#define   ESB178      (ERRSB +  178)    /*    sb_bdy2.c:4096 */
#define   ESB179      (ERRSB +  179)    /*    sb_bdy2.c:4106 */
#define   ESB180      (ERRSB +  180)    /*    sb_bdy2.c:4171 */
#define   ESB181      (ERRSB +  181)    /*    sb_bdy2.c:4208 */
#define   ESB182      (ERRSB +  182)    /*    sb_bdy2.c:4295 */
#define   ESB183      (ERRSB +  183)    /*    sb_bdy2.c:4305 */
#define   ESB184      (ERRSB +  184)    /*    sb_bdy2.c:4518 */
#define   ESB185      (ERRSB +  185)    /*    sb_bdy2.c:4579 */
#define   ESB186      (ERRSB +  186)    /*    sb_bdy2.c:4589 */
#define   ESB187      (ERRSB +  187)    /*    sb_bdy2.c:4693 */
#define   ESB188      (ERRSB +  188)    /*    sb_bdy2.c:4703 */
#define   ESB189      (ERRSB +  189)    /*    sb_bdy2.c:4715 */
#define   ESB190      (ERRSB +  190)    /*    sb_bdy2.c:4727 */
#define   ESB191      (ERRSB +  191)    /*    sb_bdy2.c:4804 */
#define   ESB192      (ERRSB +  192)    /*    sb_bdy2.c:4906 */
#define   ESB193      (ERRSB +  193)    /*    sb_bdy2.c:4978 */
#define   ESB194      (ERRSB +  194)    /*    sb_bdy2.c:5743 */
#define   ESB195      (ERRSB +  195)    /*    sb_bdy2.c:5768 */
#define   ESB196      (ERRSB +  196)    /*    sb_bdy2.c:6749 */
#define   ESB197      (ERRSB +  197)    /*    sb_bdy2.c:6805 */

#define   ESB198      (ERRSB +  198)    /*    sb_bdy3.c: 256 */
#define   ESB199      (ERRSB +  199)    /*    sb_bdy3.c:1413 */
#define   ESB200      (ERRSB +  200)    /*    sb_bdy3.c:1438 */
#define   ESB201      (ERRSB +  201)    /*    sb_bdy3.c:1492 */
#define   ESB202      (ERRSB +  202)    /*    sb_bdy3.c:1509 */
#define   ESB203      (ERRSB +  203)    /*    sb_bdy3.c:1534 */
#define   ESB204      (ERRSB +  204)    /*    sb_bdy3.c:1902 */
#define   ESB205      (ERRSB +  205)    /*    sb_bdy3.c:1942 */
#define   ESB206      (ERRSB +  206)    /*    sb_bdy3.c:1987 */
#define   ESB207      (ERRSB +  207)    /*    sb_bdy3.c:2009 */
#define   ESB208      (ERRSB +  208)    /*    sb_bdy3.c:2092 */
#define   ESB209      (ERRSB +  209)    /*    sb_bdy3.c:3014 */
#define   ESB210      (ERRSB +  210)    /*    sb_bdy3.c:3055 */
#define   ESB211      (ERRSB +  211)    /*    sb_bdy3.c:3482 */
#define   ESB212      (ERRSB +  212)    /*    sb_bdy3.c:3852 */
#define   ESB213      (ERRSB +  213)    /*    sb_bdy3.c:3897 */
#define   ESB214      (ERRSB +  214)    /*    sb_bdy3.c:3922 */
#define   ESB215      (ERRSB +  215)    /*    sb_bdy3.c:3955 */
#define   ESB216      (ERRSB +  216)    /*    sb_bdy3.c:3976 */
#define   ESB217      (ERRSB +  217)    /*    sb_bdy3.c:4005 */
#define   ESB218      (ERRSB +  218)    /*    sb_bdy3.c:4299 */
#define   ESB219      (ERRSB +  219)    /*    sb_bdy3.c:4333 */
#define   ESB220      (ERRSB +  220)    /*    sb_bdy3.c:4473 */
#define   ESB221      (ERRSB +  221)    /*    sb_bdy3.c:4672 */
#define   ESB222      (ERRSB +  222)    /*    sb_bdy3.c:4966 */
#define   ESB223      (ERRSB +  223)    /*    sb_bdy3.c:6288 */
#define   ESB224      (ERRSB +  224)    /*    sb_bdy3.c:6328 */
#define   ESB225      (ERRSB +  225)    /*    sb_bdy3.c:8648 */
#define   ESB226      (ERRSB +  226)    /*    sb_bdy3.c:10073 */
#define   ESB227      (ERRSB +  227)    /*    sb_bdy3.c:10124 */
#define   ESB228      (ERRSB +  228)    /*    sb_bdy3.c:10160 */
#define   ESB229      (ERRSB +  229)    /*    sb_bdy3.c:11897 */
#define   ESB230      (ERRSB +  230)    /*    sb_bdy3.c:12381 */
#define   ESB231      (ERRSB +  231)    /*    sb_bdy3.c:12516 */
#define   ESB232      (ERRSB +  232)    /*    sb_bdy3.c:12713 */
#define   ESB233      (ERRSB +  233)    /*    sb_bdy3.c:12910 */
#define   ESB234      (ERRSB +  234)    /*    sb_bdy3.c:12958 */
#define   ESB235      (ERRSB +  235)    /*    sb_bdy3.c:12970 */
#define   ESB236      (ERRSB +  236)    /*    sb_bdy3.c:13092 */
#define   ESB237      (ERRSB +  237)    /*    sb_bdy3.c:13228 */
#define   ESB238      (ERRSB +  238)    /*    sb_bdy3.c:13537 */
#define   ESB239      (ERRSB +  239)    /*    sb_bdy3.c:13894 */
#define   ESB240      (ERRSB +  240)    /*    sb_bdy3.c:13969 */
#define   ESB241      (ERRSB +  241)    /*    sb_bdy3.c:14502 */
#define   ESB242      (ERRSB +  242)    /*    sb_bdy3.c:14544 */
#define   ESB243      (ERRSB +  243)    /*    sb_bdy3.c:14581 */
#define   ESB244      (ERRSB +  244)    /*    sb_bdy3.c:14675 */
#define   ESB245      (ERRSB +  245)    /*    sb_bdy3.c:14988 */
#define   ESB246      (ERRSB +  246)    /*    sb_bdy3.c:15150 */
#define   ESB247      (ERRSB +  247)    /*    sb_bdy3.c:15305 */
#define   ESB248      (ERRSB +  248)    /*    sb_bdy3.c:15435 */
#define   ESB249      (ERRSB +  249)    /*    sb_bdy3.c:15646 */

#define   ESB250      (ERRSB +  250)    /*    sb_bdy4.c: 235 */
#define   ESB251      (ERRSB +  251)    /*    sb_bdy4.c: 244 */
#define   ESB252      (ERRSB +  252)    /*    sb_bdy4.c: 252 */
#define   ESB253      (ERRSB +  253)    /*    sb_bdy4.c: 261 */
#define   ESB254      (ERRSB +  254)    /*    sb_bdy4.c: 268 */
#define   ESB255      (ERRSB +  255)    /*    sb_bdy4.c: 275 */
#define   ESB256      (ERRSB +  256)    /*    sb_bdy4.c: 282 */
#define   ESB257      (ERRSB +  257)    /*    sb_bdy4.c: 289 */
#define   ESB258      (ERRSB +  258)    /*    sb_bdy4.c: 296 */
#define   ESB259      (ERRSB +  259)    /*    sb_bdy4.c: 303 */
#define   ESB260      (ERRSB +  260)    /*    sb_bdy4.c: 310 */
#define   ESB261      (ERRSB +  261)    /*    sb_bdy4.c: 362 */
#define   ESB262      (ERRSB +  262)    /*    sb_bdy4.c: 716 */
#define   ESB263      (ERRSB +  263)    /*    sb_bdy4.c: 724 */
#define   ESB264      (ERRSB +  264)    /*    sb_bdy4.c: 732 */
#define   ESB265      (ERRSB +  265)    /*    sb_bdy4.c: 739 */
#define   ESB266      (ERRSB +  266)    /*    sb_bdy4.c: 746 */
#define   ESB267      (ERRSB +  267)    /*    sb_bdy4.c: 753 */
#define   ESB268      (ERRSB +  268)    /*    sb_bdy4.c: 766 */
#define   ESB269      (ERRSB +  269)    /*    sb_bdy4.c: 774 */
#define   ESB270      (ERRSB +  270)    /*    sb_bdy4.c: 783 */
#define   ESB271      (ERRSB +  271)    /*    sb_bdy4.c: 792 */
#define   ESB272      (ERRSB +  272)    /*    sb_bdy4.c: 800 */
#define   ESB273      (ERRSB +  273)    /*    sb_bdy4.c: 807 */
#define   ESB274      (ERRSB +  274)    /*    sb_bdy4.c: 815 */
#define   ESB275      (ERRSB +  275)    /*    sb_bdy4.c: 823 */
#define   ESB276      (ERRSB +  276)    /*    sb_bdy4.c: 875 */
#define   ESB277      (ERRSB +  277)    /*    sb_bdy4.c: 956 */
#define   ESB278      (ERRSB +  278)    /*    sb_bdy4.c: 963 */
#define   ESB279      (ERRSB +  279)    /*    sb_bdy4.c: 971 */
#define   ESB280      (ERRSB +  280)    /*    sb_bdy4.c: 979 */
#define   ESB281      (ERRSB +  281)    /*    sb_bdy4.c: 992 */
#define   ESB282      (ERRSB +  282)    /*    sb_bdy4.c: 999 */
#define   ESB283      (ERRSB +  283)    /*    sb_bdy4.c:1126 */
#define   ESB284      (ERRSB +  284)    /*    sb_bdy4.c:1649 */
#define   ESB285      (ERRSB +  285)    /*    sb_bdy4.c:1785 */
#define   ESB286      (ERRSB +  286)    /*    sb_bdy4.c:1980 */
#define   ESB287      (ERRSB +  287)    /*    sb_bdy4.c:1999 */
#define   ESB288      (ERRSB +  288)    /*    sb_bdy4.c:2018 */
#define   ESB289      (ERRSB +  289)    /*    sb_bdy4.c:2039 */
#define   ESB290      (ERRSB +  290)    /*    sb_bdy4.c:2070 */
#define   ESB291      (ERRSB +  291)    /*    sb_bdy4.c:2165 */
#define   ESB292      (ERRSB +  292)    /*    sb_bdy4.c:2342 */
#define   ESB293      (ERRSB +  293)    /*    sb_bdy4.c:2386 */
#define   ESB294      (ERRSB +  294)    /*    sb_bdy4.c:2443 */
#define   ESB295      (ERRSB +  295)    /*    sb_bdy4.c:2457 */
#define   ESB296      (ERRSB +  296)    /*    sb_bdy4.c:2471 */
#define   ESB297      (ERRSB +  297)    /*    sb_bdy4.c:2481 */
#define   ESB298      (ERRSB +  298)    /*    sb_bdy4.c:2569 */
#define   ESB299      (ERRSB +  299)    /*    sb_bdy4.c:2583 */
#define   ESB300      (ERRSB +  300)    /*    sb_bdy4.c:2670 */
#define   ESB301      (ERRSB +  301)    /*    sb_bdy4.c:2684 */
#define   ESB302      (ERRSB +  302)    /*    sb_bdy4.c:2699 */
#define   ESB303      (ERRSB +  303)    /*    sb_bdy4.c:2993 */
#define   ESB304      (ERRSB +  304)    /*    sb_bdy4.c:3010 */
#define   ESB305      (ERRSB +  305)    /*    sb_bdy4.c:3023 */
#define   ESB306      (ERRSB +  306)    /*    sb_bdy4.c:3447 */
#define   ESB307      (ERRSB +  307)    /*    sb_bdy4.c:3766 */
#define   ESB308      (ERRSB +  308)    /*    sb_bdy4.c:3973 */
#define   ESB309      (ERRSB +  309)    /*    sb_bdy4.c:4102 */
#define   ESB310      (ERRSB +  310)    /*    sb_bdy4.c:4127 */
#define   ESB311      (ERRSB +  311)    /*    sb_bdy4.c:4193 */

#define   ESB312      (ERRSB +  312)    /*     sb_err.h: 110 */

#define   ESB313      (ERRSB +  313)    /*   sb_ex_ms.c: 217 */
#define   ESB314      (ERRSB +  314)    /*   sb_ex_ms.c: 300 */
#define   ESB315      (ERRSB +  315)    /*   sb_ex_ms.c: 351 */
#define   ESB316      (ERRSB +  316)    /*   sb_ex_ms.c: 391 */
#define   ESB317      (ERRSB +  317)    /*   sb_ex_ms.c: 414 */
#define   ESB318      (ERRSB +  318)    /*   sb_ex_ms.c: 427 */

#define   ESB319      (ERRSB +  319)    /*     sb_mtu.c: 183 */
#define   ESB320      (ERRSB +  320)    /*     sb_mtu.c: 189 */
#define   ESB321      (ERRSB +  321)    /*     sb_mtu.c: 249 */
#define   ESB322      (ERRSB +  322)    /*     sb_mtu.c: 267 */
#define   ESB323      (ERRSB +  323)    /*     sb_mtu.c: 273 */
#define   ESB324      (ERRSB +  324)    /*     sb_mtu.c: 279 */
#define   ESB325      (ERRSB +  325)    /*     sb_mtu.c: 285 */
#define   ESB326      (ERRSB +  326)    /*     sb_mtu.c: 306 */
#define   ESB327      (ERRSB +  327)    /*     sb_mtu.c: 369 */
#define   ESB328      (ERRSB +  328)    /*     sb_mtu.c: 376 */
#define   ESB329      (ERRSB +  329)    /*     sb_mtu.c: 383 */
#define   ESB330      (ERRSB +  330)    /*     sb_mtu.c: 389 */
#define   ESB331      (ERRSB +  331)    /*     sb_mtu.c: 420 */
#define   ESB332      (ERRSB +  332)    /*     sb_mtu.c: 459 */
#define   ESB333      (ERRSB +  333)    /*     sb_mtu.c: 520 */
#define   ESB334      (ERRSB +  334)    /*     sb_mtu.c: 527 */
#define   ESB335      (ERRSB +  335)    /*     sb_mtu.c: 539 */
#define   ESB336      (ERRSB +  336)    /*     sb_mtu.c: 601 */
#define   ESB337      (ERRSB +  337)    /*     sb_mtu.c: 608 */
#define   ESB338      (ERRSB +  338)    /*     sb_mtu.c: 615 */
#define   ESB339      (ERRSB +  339)    /*     sb_mtu.c: 621 */
#define   ESB340      (ERRSB +  340)    /*     sb_mtu.c: 627 */
#define   ESB341      (ERRSB +  341)    /*     sb_mtu.c: 640 */
#define   ESB342      (ERRSB +  342)    /*     sb_mtu.c: 702 */
#define   ESB343      (ERRSB +  343)    /*     sb_mtu.c: 716 */
#define   ESB344      (ERRSB +  344)    /*     sb_mtu.c: 723 */
#define   ESB345      (ERRSB +  345)    /*     sb_mtu.c: 729 */
#define   ESB346      (ERRSB +  346)    /*     sb_mtu.c: 736 */
#define   ESB347      (ERRSB +  347)    /*     sb_mtu.c: 749 */
#define   ESB348      (ERRSB +  348)    /*     sb_mtu.c: 811 */
#define   ESB349      (ERRSB +  349)    /*     sb_mtu.c: 823 */
#define   ESB350      (ERRSB +  350)    /*     sb_mtu.c: 850 */
#define   ESB351      (ERRSB +  351)    /*     sb_mtu.c: 867 */
#define   ESB352      (ERRSB +  352)    /*     sb_mtu.c: 922 */
#define   ESB353      (ERRSB +  353)    /*     sb_mtu.c: 934 */
#define   ESB354      (ERRSB +  354)    /*     sb_mtu.c: 997 */
#define   ESB355      (ERRSB +  355)    /*     sb_mtu.c:1009 */
#define   ESB356      (ERRSB +  356)    /*     sb_mtu.c:1080 */
#define   ESB357      (ERRSB +  357)    /*     sb_mtu.c:1092 */
#define   ESB358      (ERRSB +  358)    /*     sb_mtu.c:1098 */
#define   ESB359      (ERRSB +  359)    /*     sb_mtu.c:1111 */
#define   ESB360      (ERRSB +  360)    /*     sb_mtu.c:1130 */
#define   ESB361      (ERRSB +  361)    /*     sb_mtu.c:1375 */

#define   ESB362      (ERRSB +  362)    /*    sb_ptli.c: 546 */
#define   ESB363      (ERRSB +  363)    /*    sb_ptli.c: 597 */
#define   ESB364      (ERRSB +  364)    /*    sb_ptli.c: 678 */
#define   ESB365      (ERRSB +  365)    /*    sb_ptli.c: 734 */

#define   ESB366      (ERRSB +  366)    /*    sb_ptmi.c: 631 */
#define   ESB367      (ERRSB +  367)    /*    sb_ptmi.c: 670 */
#define   ESB368      (ERRSB +  368)    /*    sb_ptmi.c: 709 */
#define   ESB369      (ERRSB +  369)    /*    sb_ptmi.c: 749 */
#define   ESB370      (ERRSB +  370)    /*    sb_ptmi.c: 789 */
#define   ESB371      (ERRSB +  371)    /*    sb_ptmi.c: 828 */
#define   ESB372      (ERRSB +  372)    /*    sb_ptmi.c: 869 */

#define   ESB373      (ERRSB +  373)    /*    sb_ptui.c:1939 */
#define   ESB374      (ERRSB +  374)    /*    sb_ptui.c:1974 */
#define   ESB375      (ERRSB +  375)    /*    sb_ptui.c:2010 */
#define   ESB376      (ERRSB +  376)    /*    sb_ptui.c:2046 */
#define   ESB377      (ERRSB +  377)    /*    sb_ptui.c:2119 */
#define   ESB378      (ERRSB +  378)    /*    sb_ptui.c:2168 */
#define   ESB379      (ERRSB +  379)    /*    sb_ptui.c:2205 */
#define   ESB380      (ERRSB +  380)    /*    sb_ptui.c:2241 */
#define   ESB381      (ERRSB +  381)    /*    sb_ptui.c:2282 */
#define   ESB382      (ERRSB +  382)    /*    sb_ptui.c:2323 */
#define   ESB383      (ERRSB +  383)    /*    sb_ptui.c:2366 */
#define   ESB384      (ERRSB +  384)    /*    sb_ptui.c:2411 */
#define   ESB385      (ERRSB +  385)    /*    sb_ptui.c:2448 */
/* sb028.103: Added new error code */

#define   ESB386      (ERRSB +  386)    /*    sb_bdy1.c:10537 */
#define   ESB387      (ERRSB +  387)    /*    sb_bdy2.c:10552 */
/* sb033.103 : Added new error code */
#define   ESB388      (ERRSB +  388)    /*    sb_bdy3.c:14882 */

#endif /* __SBERRH__ */

/********************************************************************30**

         End of file:     sb_err.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:14 2015

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

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/3      ---      mrw   1.Initial version
 /main/3     ---      sb    1. Modified for SCTP release based on 
                             RFC-2960 'Oct 2000.
           sb031.102  hm    1. IPV6 Support Added
           sb057.102  pr    1. Error code for multiple procs added.
/main/4      ---   rsr/ag   1. Updated for Release of 1.3
           sb003.103  ag    1. Satellite SCTP feature (under compile-time flags
                             SB_ECN & SB_SATELLITE).
/main/4    sb028.103 ajainx 1. Added new error code.
/main/4    sb033.103 sdey    1. Added new error code
*********************************************************************91*/
