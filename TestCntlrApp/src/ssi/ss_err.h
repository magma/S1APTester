

/********************************************************************20**
  
     Name:     System Services - errors
  
     Type:     C include file
  
     Desc:     Error defines required by System Services.
  
     File:     ss_err.h
  
     Sid:      ss_err.h@@/main/4 - Mon Nov 17 15:54:15 2008
   
     Prg:      kp
  
*********************************************************************21*/

#ifndef __SSERRH__
#define __SSERRH__

#ifdef __cplusplus
extern "C" {
#endif



/* log error macro */
/* ss029.103: modification: SFndProcId is not supported with multiple procs */
#ifndef SS_MULTIPLE_PROCS
#define SSLOGERROR(errCls, errCode, errVal, errDesc) \
   SLogError((Ent)ENTSS, (Inst)0 , SFndProcId(), \
             (Txt *)__FILE__, __LINE__, \
             (ErrCls)errCls, (ErrVal)errCode, \
             (ErrVal)errVal, (Txt *)errDesc)
#else /* SS_MULTIPLE_PROCS */
#define SSLOGERROR(errCls, errCode, errVal, errDesc) \
   SLogError((Ent)ENTSS, (Inst)0 , PROCNC, \
             (Txt *)__FILE__, __LINE__, \
             (ErrCls)errCls, (ErrVal)errCode, \
             (ErrVal)errVal, (Txt *)errDesc)
#endif /* SS_MULTIPLE_PROCS */

/* defines */
#define   ERRSS       0
#define   ESSBASE     (ERRSS + 0)    /* reserved */
#define   ESSXXX      (ESSBASE)      /* reserved */

#define   ESS001      (ERRSS +    1)    /*    sm_drvr.c: 185 */
#define   ESS002      (ERRSS +    2)    /*    sm_drvr.c: 193 */
#define   ESS003      (ERRSS +    3)    /*    sm_drvr.c: 201 */
#define   ESS004      (ERRSS +    4)    /*    sm_drvr.c: 208 */
#define   ESS005      (ERRSS +    5)    /*    sm_drvr.c: 215 */
#define   ESS006      (ERRSS +    6)    /*    sm_drvr.c: 222 */
#define   ESS007      (ERRSS +    7)    /*    sm_drvr.c: 233 */
#define   ESS008      (ERRSS +    8)    /*    sm_drvr.c: 243 */

#define   ESS009      (ERRSS +    9)    /*     sm_gen.c: 269 */
#define   ESS010      (ERRSS +   10)    /*     sm_gen.c: 372 */
#define   ESS011      (ERRSS +   11)    /*     sm_gen.c: 397 */
#define   ESS012      (ERRSS +   12)    /*     sm_gen.c: 534 */
#define   ESS013      (ERRSS +   13)    /*     sm_gen.c: 551 */
#define   ESS014      (ERRSS +   14)    /*     sm_gen.c: 610 */
#define   ESS015      (ERRSS +   15)    /*     sm_gen.c: 622 */
#define   ESS016      (ERRSS +   16)    /*     sm_gen.c:1026 */
#define   ESS017      (ERRSS +   17)    /*     sm_gen.c:1036 */
#define   ESS018      (ERRSS +   18)    /*     sm_gen.c:1043 */
#define   ESS019      (ERRSS +   19)    /*     sm_gen.c:1087 */
#define   ESS020      (ERRSS +   20)    /*     sm_gen.c:1133 */
#define   ESS021      (ERRSS +   21)    /*     sm_gen.c:1143 */
#define   ESS022      (ERRSS +   22)    /*     sm_gen.c:1157 */
#define   ESS023      (ERRSS +   23)    /*     sm_gen.c:1164 */
#define   ESS024      (ERRSS +   24)    /*     sm_gen.c:1179 */
#define   ESS025      (ERRSS +   25)    /*     sm_gen.c:1293 */
#define   ESS026      (ERRSS +   26)    /*     sm_gen.c:1357 */
#define   ESS027      (ERRSS +   27)    /*     sm_gen.c:1372 */

#define   ESS028      (ERRSS +   28)    /*     sm_mem.c: 162 */
#define   ESS029      (ERRSS +   29)    /*     sm_mem.c: 169 */
#define   ESS030      (ERRSS +   30)    /*     sm_mem.c: 181 */
#define   ESS031      (ERRSS +   31)    /*     sm_mem.c: 195 */
#define   ESS032      (ERRSS +   32)    /*     sm_mem.c: 256 */
#define   ESS033      (ERRSS +   33)    /*     sm_mem.c: 268 */
#define   ESS034      (ERRSS +   34)    /*     sm_mem.c: 281 */
#define   ESS035      (ERRSS +   35)    /*     sm_mem.c: 349 */
#define   ESS036      (ERRSS +   36)    /*     sm_mem.c: 362 */
#define   ESS037      (ERRSS +   37)    /*     sm_mem.c: 383 */
#define   ESS038      (ERRSS +   38)    /*     sm_mem.c: 390 */
#define   ESS039      (ERRSS +   39)    /*     sm_mem.c: 417 */
#define   ESS040      (ERRSS +   40)    /*     sm_mem.c: 476 */
#define   ESS041      (ERRSS +   41)    /*     sm_mem.c: 483 */
#define   ESS042      (ERRSS +   42)    /*     sm_mem.c: 490 */
#define   ESS043      (ERRSS +   43)    /*     sm_mem.c: 504 */
#define   ESS044      (ERRSS +   44)    /*     sm_mem.c: 523 */
#define   ESS045      (ERRSS +   45)    /*     sm_mem.c: 530 */
#define   ESS046      (ERRSS +   46)    /*     sm_mem.c: 550 */

#define   ESS047      (ERRSS +   47)    /*     sm_msg.c: 203 */
#define   ESS048      (ERRSS +   48)    /*     sm_msg.c: 209 */
#define   ESS049      (ERRSS +   49)    /*     sm_msg.c: 216 */
#define   ESS050      (ERRSS +   50)    /*     sm_msg.c: 337 */
#define   ESS051      (ERRSS +   51)    /*     sm_msg.c: 342 */
#define   ESS052      (ERRSS +   52)    /*     sm_msg.c: 349 */
#define   ESS053      (ERRSS +   53)    /*     sm_msg.c: 363 */
#define   ESS054      (ERRSS +   54)    /*     sm_msg.c: 381 */
#define   ESS055      (ERRSS +   55)    /*     sm_msg.c: 387 */
#define   ESS056      (ERRSS +   56)    /*     sm_msg.c: 396 */
#define   ESS057      (ERRSS +   57)    /*     sm_msg.c: 408 */
#define   ESS058      (ERRSS +   58)    /*     sm_msg.c: 416 */
#define   ESS059      (ERRSS +   59)    /*     sm_msg.c: 422 */
#define   ESS060      (ERRSS +   60)    /*     sm_msg.c: 489 */
#define   ESS061      (ERRSS +   61)    /*     sm_msg.c: 494 */
#define   ESS062      (ERRSS +   62)    /*     sm_msg.c: 564 */
#define   ESS063      (ERRSS +   63)    /*     sm_msg.c: 569 */
#define   ESS064      (ERRSS +   64)    /*     sm_msg.c: 638 */
#define   ESS065      (ERRSS +   65)    /*     sm_msg.c: 643 */
#define   ESS066      (ERRSS +   66)    /*     sm_msg.c: 672 */
#define   ESS067      (ERRSS +   67)    /*     sm_msg.c: 742 */
#define   ESS068      (ERRSS +   68)    /*     sm_msg.c: 747 */
#define   ESS069      (ERRSS +   69)    /*     sm_msg.c: 761 */
#define   ESS070      (ERRSS +   70)    /*     sm_msg.c: 842 */
#define   ESS071      (ERRSS +   71)    /*     sm_msg.c: 848 */
#define   ESS072      (ERRSS +   72)    /*     sm_msg.c: 854 */
#define   ESS073      (ERRSS +   73)    /*     sm_msg.c: 860 */
#define   ESS074      (ERRSS +   74)    /*     sm_msg.c:1011 */
#define   ESS075      (ERRSS +   75)    /*     sm_msg.c:1017 */
#define   ESS076      (ERRSS +   76)    /*     sm_msg.c:1023 */
#define   ESS077      (ERRSS +   77)    /*     sm_msg.c:1029 */
#define   ESS078      (ERRSS +   78)    /*     sm_msg.c:1192 */
#define   ESS079      (ERRSS +   79)    /*     sm_msg.c:1198 */
#define   ESS080      (ERRSS +   80)    /*     sm_msg.c:1203 */
#define   ESS081      (ERRSS +   81)    /*     sm_msg.c:1276 */
#define   ESS082      (ERRSS +   82)    /*     sm_msg.c:1282 */
#define   ESS083      (ERRSS +   83)    /*     sm_msg.c:1287 */
#define   ESS084      (ERRSS +   84)    /*     sm_msg.c:1378 */
#define   ESS085      (ERRSS +   85)    /*     sm_msg.c:1385 */
#define   ESS086      (ERRSS +   86)    /*     sm_msg.c:1393 */
#define   ESS087      (ERRSS +   87)    /*     sm_msg.c:1498 */
#define   ESS088      (ERRSS +   88)    /*     sm_msg.c:1505 */
#define   ESS089      (ERRSS +   89)    /*     sm_msg.c:1510 */
#define   ESS090      (ERRSS +   90)    /*     sm_msg.c:1625 */
#define   ESS091      (ERRSS +   91)    /*     sm_msg.c:1631 */
#define   ESS092      (ERRSS +   92)    /*     sm_msg.c:1637 */
#define   ESS093      (ERRSS +   93)    /*     sm_msg.c:1642 */
#define   ESS094      (ERRSS +   94)    /*     sm_msg.c:1705 */
#define   ESS095      (ERRSS +   95)    /*     sm_msg.c:1711 */
#define   ESS096      (ERRSS +   96)    /*     sm_msg.c:1716 */
#define   ESS097      (ERRSS +   97)    /*     sm_msg.c:1795 */
#define   ESS098      (ERRSS +   98)    /*     sm_msg.c:1801 */
#define   ESS099      (ERRSS +   99)    /*     sm_msg.c:1806 */
#define   ESS100      (ERRSS +  100)    /*     sm_msg.c:1811 */
#define   ESS101      (ERRSS +  101)    /*     sm_msg.c:1829 */
#define   ESS102      (ERRSS +  102)    /*     sm_msg.c:1999 */
#define   ESS103      (ERRSS +  103)    /*     sm_msg.c:2005 */
#define   ESS104      (ERRSS +  104)    /*     sm_msg.c:2011 */
#define   ESS105      (ERRSS +  105)    /*     sm_msg.c:2017 */
#define   ESS106      (ERRSS +  106)    /*     sm_msg.c:2022 */
#define   ESS107      (ERRSS +  107)    /*     sm_msg.c:2033 */
#define   ESS108      (ERRSS +  108)    /*     sm_msg.c:2048 */
#define   ESS109      (ERRSS +  109)    /*     sm_msg.c:2059 */
#define   ESS110      (ERRSS +  110)    /*     sm_msg.c:2155 */
#define   ESS111      (ERRSS +  111)    /*     sm_msg.c:2161 */
#define   ESS112      (ERRSS +  112)    /*     sm_msg.c:2166 */
#define   ESS113      (ERRSS +  113)    /*     sm_msg.c:2172 */
#define   ESS114      (ERRSS +  114)    /*     sm_msg.c:2177 */
#define   ESS115      (ERRSS +  115)    /*     sm_msg.c:2182 */
#define   ESS116      (ERRSS +  116)    /*     sm_msg.c:2300 */
#define   ESS117      (ERRSS +  117)    /*     sm_msg.c:2305 */
#define   ESS118      (ERRSS +  118)    /*     sm_msg.c:2312 */
#define   ESS119      (ERRSS +  119)    /*     sm_msg.c:2319 */
#define   ESS120      (ERRSS +  120)    /*     sm_msg.c:2333 */
#define   ESS121      (ERRSS +  121)    /*     sm_msg.c:2349 */
#define   ESS122      (ERRSS +  122)    /*     sm_msg.c:2355 */
#define   ESS123      (ERRSS +  123)    /*     sm_msg.c:2365 */
#define   ESS124      (ERRSS +  124)    /*     sm_msg.c:2377 */
#define   ESS125      (ERRSS +  125)    /*     sm_msg.c:2445 */
#define   ESS126      (ERRSS +  126)    /*     sm_msg.c:2530 */
#define   ESS127      (ERRSS +  127)    /*     sm_msg.c:2535 */
#define   ESS128      (ERRSS +  128)    /*     sm_msg.c:2545 */
#define   ESS129      (ERRSS +  129)    /*     sm_msg.c:2613 */
#define   ESS130      (ERRSS +  130)    /*     sm_msg.c:2680 */
#define   ESS131      (ERRSS +  131)    /*     sm_msg.c:2686 */
#define   ESS132      (ERRSS +  132)    /*     sm_msg.c:2704 */
#define   ESS133      (ERRSS +  133)    /*     sm_msg.c:2792 */
#define   ESS134      (ERRSS +  134)    /*     sm_msg.c:2797 */
#define   ESS135      (ERRSS +  135)    /*     sm_msg.c:2804 */
#define   ESS136      (ERRSS +  136)    /*     sm_msg.c:2817 */
#define   ESS137      (ERRSS +  137)    /*     sm_msg.c:2836 */
#define   ESS138      (ERRSS +  138)    /*     sm_msg.c:2842 */
#define   ESS139      (ERRSS +  139)    /*     sm_msg.c:2852 */
#define   ESS140      (ERRSS +  140)    /*     sm_msg.c:2865 */
#define   ESS141      (ERRSS +  141)    /*     sm_msg.c:2998 */
#define   ESS142      (ERRSS +  142)    /*     sm_msg.c:3004 */
#define   ESS143      (ERRSS +  143)    /*     sm_msg.c:3010 */
#define   ESS144      (ERRSS +  144)    /*     sm_msg.c:3016 */
#define   ESS145      (ERRSS +  145)    /*     sm_msg.c:3029 */
#define   ESS146      (ERRSS +  146)    /*     sm_msg.c:3120 */
#define   ESS147      (ERRSS +  147)    /*     sm_msg.c:3242 */
#define   ESS148      (ERRSS +  148)    /*     sm_msg.c:3305 */
#define   ESS149      (ERRSS +  149)    /*     sm_msg.c:3311 */
#define   ESS150      (ERRSS +  150)    /*     sm_msg.c:3318 */
#define   ESS151      (ERRSS +  151)    /*     sm_msg.c:3323 */
#define   ESS152      (ERRSS +  152)    /*     sm_msg.c:3329 */
#define   ESS153      (ERRSS +  153)    /*     sm_msg.c:3350 */
#define   ESS154      (ERRSS +  154)    /*     sm_msg.c:3395 */
#define   ESS155      (ERRSS +  155)    /*     sm_msg.c:3471 */
#define   ESS156      (ERRSS +  156)    /*     sm_msg.c:3476 */
#define   ESS157      (ERRSS +  157)    /*     sm_msg.c:3481 */
#define   ESS158      (ERRSS +  158)    /*     sm_msg.c:3507 */
#define   ESS159      (ERRSS +  159)    /*     sm_msg.c:3564 */
#define   ESS160      (ERRSS +  160)    /*     sm_msg.c:3569 */
#define   ESS161      (ERRSS +  161)    /*     sm_msg.c:3574 */
#define   ESS162      (ERRSS +  162)    /*     sm_msg.c:3580 */
#define   ESS163      (ERRSS +  163)    /*     sm_msg.c:3603 */
#define   ESS164      (ERRSS +  164)    /*     sm_msg.c:3665 */
#define   ESS165      (ERRSS +  165)    /*     sm_msg.c:3671 */
#define   ESS166      (ERRSS +  166)    /*     sm_msg.c:3739 */
#define   ESS167      (ERRSS +  167)    /*     sm_msg.c:3745 */
#define   ESS168      (ERRSS +  168)    /*     sm_msg.c:3814 */
#define   ESS169      (ERRSS +  169)    /*     sm_msg.c:3820 */
#define   ESS170      (ERRSS +  170)    /*     sm_msg.c:3825 */
#define   ESS171      (ERRSS +  171)    /*     sm_msg.c:3892 */
#define   ESS172      (ERRSS +  172)    /*     sm_msg.c:3898 */
#define   ESS173      (ERRSS +  173)    /*     sm_msg.c:3903 */
#define   ESS174      (ERRSS +  174)    /*     sm_msg.c:3962 */
#define   ESS175      (ERRSS +  175)    /*     sm_msg.c:3967 */
#define   ESS176      (ERRSS +  176)    /*     sm_msg.c:4015 */
#define   ESS177      (ERRSS +  177)    /*     sm_msg.c:4020 */
#define   ESS178      (ERRSS +  178)    /*     sm_msg.c:4025 */
#define   ESS179      (ERRSS +  179)    /*     sm_msg.c:4074 */
#define   ESS180      (ERRSS +  180)    /*     sm_msg.c:4079 */
#define   ESS181      (ERRSS +  181)    /*     sm_msg.c:4133 */
#define   ESS182      (ERRSS +  182)    /*     sm_msg.c:4138 */
#define   ESS183      (ERRSS +  183)    /*     sm_msg.c:4143 */
#define   ESS184      (ERRSS +  184)    /*     sm_msg.c:4148 */
#define   ESS185      (ERRSS +  185)    /*     sm_msg.c:4157 */
#define   ESS186      (ERRSS +  186)    /*     sm_msg.c:4170 */
#define   ESS187      (ERRSS +  187)    /*     sm_msg.c:4216 */
#define   ESS188      (ERRSS +  188)    /*     sm_msg.c:4221 */
#define   ESS189      (ERRSS +  189)    /*     sm_msg.c:4227 */
#define   ESS190      (ERRSS +  190)    /*     sm_msg.c:4232 */
#define   ESS191      (ERRSS +  191)    /*     sm_msg.c:4246 */
#define   ESS192      (ERRSS +  192)    /*     sm_msg.c:4292 */
#define   ESS193      (ERRSS +  193)    /*     sm_msg.c:4298 */
#define   ESS194      (ERRSS +  194)    /*     sm_msg.c:4304 */
#define   ESS195      (ERRSS +  195)    /*     sm_msg.c:4314 */
#define   ESS196      (ERRSS +  196)    /*     sm_msg.c:4370 */
#define   ESS197      (ERRSS +  197)    /*     sm_msg.c:4375 */
#define   ESS198      (ERRSS +  198)    /*     sm_msg.c:4391 */
#define   ESS199      (ERRSS +  199)    /*     sm_msg.c:4777 */
#define   ESS200      (ERRSS +  200)    /*     sm_msg.c:4783 */
#define   ESS201      (ERRSS +  201)    /*     sm_msg.c:4861 */
#define   ESS202      (ERRSS +  202)    /*     sm_msg.c:4867 */
#define   ESS203      (ERRSS +  203)    /*     sm_msg.c:4962 */
#define   ESS204      (ERRSS +  204)    /*     sm_msg.c:4969 */
#define   ESS205      (ERRSS +  205)    /*     sm_msg.c:5023 */
#define   ESS206      (ERRSS +  206)    /*     sm_msg.c:5030 */
#define   ESS207      (ERRSS +  207)    /*     sm_msg.c:5041 */
#define   ESS208      (ERRSS +  208)    /*     sm_msg.c:5056 */
#define   ESS209      (ERRSS +  209)    /*     sm_msg.c:5062 */
#define   ESS210      (ERRSS +  210)    /*     sm_msg.c:5070 */
#define   ESS211      (ERRSS +  211)    /*     sm_msg.c:5125 */
#define   ESS212      (ERRSS +  212)    /*     sm_msg.c:5132 */
#define   ESS213      (ERRSS +  213)    /*     sm_msg.c:5139 */
#define   ESS214      (ERRSS +  214)    /*     sm_msg.c:5147 */
#define   ESS215      (ERRSS +  215)    /*     sm_msg.c:5155 */
#define   ESS216      (ERRSS +  216)    /*     sm_msg.c:5168 */
#define   ESS217      (ERRSS +  217)    /*     sm_msg.c:5190 */
#define   ESS218      (ERRSS +  218)    /*     sm_msg.c:5197 */
#define   ESS219      (ERRSS +  219)    /*     sm_msg.c:5232 */
#define   ESS220      (ERRSS +  220)    /*     sm_msg.c:5294 */
#define   ESS221      (ERRSS +  221)    /*     sm_msg.c:5301 */
#define   ESS222      (ERRSS +  222)    /*     sm_msg.c:5308 */
#define   ESS223      (ERRSS +  223)    /*     sm_msg.c:5316 */
#define   ESS224      (ERRSS +  224)    /*     sm_msg.c:5324 */
#define   ESS225      (ERRSS +  225)    /*     sm_msg.c:5337 */
#define   ESS226      (ERRSS +  226)    /*     sm_msg.c:5358 */
#define   ESS227      (ERRSS +  227)    /*     sm_msg.c:5365 */
#define   ESS228      (ERRSS +  228)    /*     sm_msg.c:5385 */
#define   ESS229      (ERRSS +  229)    /*     sm_msg.c:5446 */
#define   ESS230      (ERRSS +  230)    /*     sm_msg.c:5453 */
#define   ESS231      (ERRSS +  231)    /*     sm_msg.c:5460 */
#define   ESS232      (ERRSS +  232)    /*     sm_msg.c:5473 */
#define   ESS233      (ERRSS +  233)    /*     sm_msg.c:5493 */
#define   ESS234      (ERRSS +  234)    /*     sm_msg.c:5500 */
#define   ESS235      (ERRSS +  235)    /*     sm_msg.c:5507 */
#define   ESS236      (ERRSS +  236)    /*     sm_msg.c:5529 */
#define   ESS237      (ERRSS +  237)    /*     sm_msg.c:5584 */
#define   ESS238      (ERRSS +  238)    /*     sm_msg.c:5590 */
#define   ESS239      (ERRSS +  239)    /*     sm_msg.c:5595 */
#define   ESS240      (ERRSS +  240)    /*     sm_msg.c:5601 */
#define   ESS241      (ERRSS +  241)    /*     sm_msg.c:5609 */

#define   ESS242      (ERRSS +  242)    /*    sm_pack.c: 154 */
#define   ESS243      (ERRSS +  243)    /*    sm_pack.c: 194 */
#define   ESS244      (ERRSS +  244)    /*    sm_pack.c: 241 */
#define   ESS245      (ERRSS +  245)    /*    sm_pack.c: 289 */
#define   ESS246      (ERRSS +  246)    /*    sm_pack.c: 346 */
#define   ESS247      (ERRSS +  247)    /*    sm_pack.c: 403 */
#define   ESS248      (ERRSS +  248)    /*    sm_pack.c: 464 */
#define   ESS249      (ERRSS +  249)    /*    sm_pack.c: 524 */
#define   ESS250      (ERRSS +  250)    /*    sm_pack.c: 566 */
#define   ESS251      (ERRSS +  251)    /*    sm_pack.c: 574 */
#define   ESS252      (ERRSS +  252)    /*    sm_pack.c: 616 */
#define   ESS253      (ERRSS +  253)    /*    sm_pack.c: 624 */
#define   ESS254      (ERRSS +  254)    /*    sm_pack.c: 666 */
#define   ESS255      (ERRSS +  255)    /*    sm_pack.c: 674 */
#define   ESS256      (ERRSS +  256)    /*    sm_pack.c: 725 */
#define   ESS257      (ERRSS +  257)    /*    sm_pack.c: 733 */
#define   ESS258      (ERRSS +  258)    /*    sm_pack.c: 785 */
#define   ESS259      (ERRSS +  259)    /*    sm_pack.c: 793 */
#define   ESS260      (ERRSS +  260)    /*    sm_pack.c: 856 */
#define   ESS261      (ERRSS +  261)    /*    sm_pack.c: 864 */
#define   ESS262      (ERRSS +  262)    /*    sm_pack.c: 930 */
#define   ESS263      (ERRSS +  263)    /*    sm_pack.c: 938 */
#define   ESS264      (ERRSS +  264)    /*    sm_pack.c: 997 */
#define   ESS265      (ERRSS +  265)    /*    sm_pack.c:1005 */

#define   ESS266      (ERRSS +  266)    /*   sm_queue.c: 157 */
#define   ESS267      (ERRSS +  267)    /*   sm_queue.c: 211 */
#define   ESS268      (ERRSS +  268)    /*   sm_queue.c: 280 */
#define   ESS269      (ERRSS +  269)    /*   sm_queue.c: 286 */
#define   ESS270      (ERRSS +  270)    /*   sm_queue.c: 292 */
#define   ESS271      (ERRSS +  271)    /*   sm_queue.c: 299 */
#define   ESS272      (ERRSS +  272)    /*   sm_queue.c: 391 */
#define   ESS273      (ERRSS +  273)    /*   sm_queue.c: 397 */
#define   ESS274      (ERRSS +  274)    /*   sm_queue.c: 453 */
#define   ESS275      (ERRSS +  275)    /*   sm_queue.c: 460 */
#define   ESS276      (ERRSS +  276)    /*   sm_queue.c: 467 */
#define   ESS277      (ERRSS +  277)    /*   sm_queue.c: 548 */
#define   ESS278      (ERRSS +  278)    /*   sm_queue.c: 554 */
#define   ESS279      (ERRSS +  279)    /*   sm_queue.c: 560 */
#define   ESS280      (ERRSS +  280)    /*   sm_queue.c: 566 */
#define   ESS281      (ERRSS +  281)    /*   sm_queue.c: 575 */
#define   ESS282      (ERRSS +  282)    /*   sm_queue.c: 584 */
#define   ESS283      (ERRSS +  283)    /*   sm_queue.c: 673 */
#define   ESS284      (ERRSS +  284)    /*   sm_queue.c: 680 */
#define   ESS285      (ERRSS +  285)    /*   sm_queue.c: 686 */
#define   ESS286      (ERRSS +  286)    /*   sm_queue.c: 852 */
#define   ESS287      (ERRSS +  287)    /*   sm_queue.c: 858 */
#define   ESS288      (ERRSS +  288)    /*   sm_queue.c: 908 */
#define   ESS289      (ERRSS +  289)    /*   sm_queue.c: 914 */
#define   ESS290      (ERRSS +  290)    /*   sm_queue.c: 961 */
#define   ESS291      (ERRSS +  291)    /*   sm_queue.c: 985 */
#define   ESS292      (ERRSS +  292)    /*   sm_queue.c:1006 */
#define   ESS293      (ERRSS +  293)    /*   sm_queue.c:1050 */
#define   ESS294      (ERRSS +  294)    /*   sm_queue.c:1066 */
#define   ESS295      (ERRSS +  295)    /*   sm_queue.c:1087 */
#define   ESS296      (ERRSS +  296)    /*   sm_queue.c:1145 */
#define   ESS297      (ERRSS +  297)    /*   sm_queue.c:1151 */
#define   ESS298      (ERRSS +  298)    /*   sm_queue.c:1157 */
#define   ESS299      (ERRSS +  299)    /*   sm_queue.c:1163 */
#define   ESS300      (ERRSS +  300)    /*   sm_queue.c:1181 */
#define   ESS301      (ERRSS +  301)    /*   sm_queue.c:1227 */
#define   ESS302      (ERRSS +  302)    /*   sm_queue.c:1259 */
#define   ESS303      (ERRSS +  303)    /*   sm_queue.c:1320 */
#define   ESS304      (ERRSS +  304)    /*   sm_queue.c:1326 */
#define   ESS305      (ERRSS +  305)    /*   sm_queue.c:1332 */
#define   ESS306      (ERRSS +  306)    /*   sm_queue.c:1343 */
#define   ESS307      (ERRSS +  307)    /*   sm_queue.c:1359 */
#define   ESS308      (ERRSS +  308)    /*   sm_queue.c:1377 */
#define   ESS309      (ERRSS +  309)    /*   sm_queue.c:1440 */
#define   ESS310      (ERRSS +  310)    /*   sm_queue.c:1489 */
#define   ESS311      (ERRSS +  311)    /*   sm_queue.c:1507 */
#define   ESS312      (ERRSS +  312)    /*   sm_queue.c:1523 */
#define   ESS313      (ERRSS +  313)    /*   sm_queue.c:1542 */
#define   ESS314      (ERRSS +  314)    /*   sm_queue.c:1560 */
#define   ESS315      (ERRSS +  315)    /*   sm_queue.c:1588 */

#define   ESS316      (ERRSS +  316)    /*     sm_rtr.c: 167 */
#define   ESS317      (ERRSS +  317)    /*     sm_rtr.c: 175 */
#define   ESS318      (ERRSS +  318)    /*     sm_rtr.c: 185 */
#define   ESS319      (ERRSS +  319)    /*     sm_rtr.c: 198 */
#define   ESS320      (ERRSS +  320)    /*     sm_rtr.c: 264 */
#define   ESS321      (ERRSS +  321)    /*     sm_rtr.c: 271 */
#define   ESS322      (ERRSS +  322)    /*     sm_rtr.c: 286 */
#define   ESS323      (ERRSS +  323)    /*     sm_rtr.c: 299 */
#define   ESS324      (ERRSS +  324)    /*     sm_rtr.c: 309 */

#define   ESS325      (ERRSS +  325)    /*    sm_strm.c: 226 */
#define   ESS326      (ERRSS +  326)    /*    sm_strm.c: 395 */
#define   ESS327      (ERRSS +  327)    /*    sm_strm.c: 410 */
#define   ESS328      (ERRSS +  328)    /*    sm_strm.c: 468 */
#define   ESS329      (ERRSS +  329)    /*    sm_strm.c: 479 */
#define   ESS330      (ERRSS +  330)    /*    sm_strm.c: 538 */
#define   ESS331      (ERRSS +  331)    /*    sm_strm.c: 549 */
#define   ESS332      (ERRSS +  332)    /*    sm_strm.c: 567 */
#define   ESS333      (ERRSS +  333)    /*    sm_strm.c: 622 */
#define   ESS334      (ERRSS +  334)    /*    sm_strm.c: 633 */
#define   ESS335      (ERRSS +  335)    /*    sm_strm.c: 669 */
#define   ESS336      (ERRSS +  336)    /*    sm_strm.c: 680 */
#define   ESS337      (ERRSS +  337)    /*    sm_strm.c: 728 */
#define   ESS338      (ERRSS +  338)    /*    sm_strm.c: 746 */
#define   ESS339      (ERRSS +  339)    /*    sm_strm.c: 806 */
#define   ESS340      (ERRSS +  340)    /*    sm_strm.c: 818 */
#define   ESS341      (ERRSS +  341)    /*    sm_strm.c: 872 */
#define   ESS342      (ERRSS +  342)    /*    sm_strm.c: 896 */
#define   ESS343      (ERRSS +  343)    /*    sm_strm.c: 908 */
#define   ESS344      (ERRSS +  344)    /*    sm_strm.c: 919 */
#define   ESS345      (ERRSS +  345)    /*    sm_strm.c:1056 */
#define   ESS346      (ERRSS +  346)    /*    sm_strm.c:1176 */
#define   ESS347      (ERRSS +  347)    /*    sm_strm.c:1182 */
#define   ESS348      (ERRSS +  348)    /*    sm_strm.c:1356 */
#define   ESS349      (ERRSS +  349)    /*    sm_strm.c:1483 */

#define   ESS350      (ERRSS +  350)    /*    sm_task.c: 167 */
#define   ESS351      (ERRSS +  351)    /*    sm_task.c: 174 */
#define   ESS352      (ERRSS +  352)    /*    sm_task.c: 192 */
#define   ESS353      (ERRSS +  353)    /*    sm_task.c: 202 */
#define   ESS354      (ERRSS +  354)    /*    sm_task.c: 215 */
#define   ESS355      (ERRSS +  355)    /*    sm_task.c: 221 */
#define   ESS356      (ERRSS +  356)    /*    sm_task.c: 234 */
#define   ESS357      (ERRSS +  357)    /*    sm_task.c: 241 */
#define   ESS358      (ERRSS +  358)    /*    sm_task.c: 287 */
#define   ESS359      (ERRSS +  359)    /*    sm_task.c: 352 */
#define   ESS360      (ERRSS +  360)    /*    sm_task.c: 359 */
#define   ESS361      (ERRSS +  361)    /*    sm_task.c: 366 */
#define   ESS362      (ERRSS +  362)    /*    sm_task.c: 374 */
#define   ESS363      (ERRSS +  363)    /*    sm_task.c: 383 */
#define   ESS364      (ERRSS +  364)    /*    sm_task.c: 395 */
#define   ESS365      (ERRSS +  365)    /*    sm_task.c: 401 */
#define   ESS366      (ERRSS +  366)    /*    sm_task.c: 420 */
#define   ESS367      (ERRSS +  367)    /*    sm_task.c: 425 */
#define   ESS368      (ERRSS +  368)    /*    sm_task.c: 466 */
#define   ESS369      (ERRSS +  369)    /*    sm_task.c: 472 */
#define   ESS370      (ERRSS +  370)    /*    sm_task.c: 488 */
#define   ESS371      (ERRSS +  371)    /*    sm_task.c: 507 */
#define   ESS372      (ERRSS +  372)    /*    sm_task.c: 524 */
#define   ESS373      (ERRSS +  373)    /*    sm_task.c: 578 */
#define   ESS374      (ERRSS +  374)    /*    sm_task.c: 588 */
#define   ESS375      (ERRSS +  375)    /*    sm_task.c: 599 */
#define   ESS376      (ERRSS +  376)    /*    sm_task.c: 612 */
#define   ESS377      (ERRSS +  377)    /*    sm_task.c: 618 */
#define   ESS378      (ERRSS +  378)    /*    sm_task.c: 650 */
#define   ESS379      (ERRSS +  379)    /*    sm_task.c: 677 */
#define   ESS380      (ERRSS +  380)    /*    sm_task.c: 698 */
#define   ESS381      (ERRSS +  381)    /*    sm_task.c: 719 */
#define   ESS382      (ERRSS +  382)    /*    sm_task.c: 748 */
#define   ESS383      (ERRSS +  383)    /*    sm_task.c: 766 */
#define   ESS384      (ERRSS +  384)    /*    sm_task.c: 865 */
#define   ESS385      (ERRSS +  385)    /*    sm_task.c: 871 */
#define   ESS386      (ERRSS +  386)    /*    sm_task.c: 879 */
#define   ESS387      (ERRSS +  387)    /*    sm_task.c: 886 */
#define   ESS388      (ERRSS +  388)    /*    sm_task.c: 894 */
#define   ESS389      (ERRSS +  389)    /*    sm_task.c: 908 */
#define   ESS390      (ERRSS +  390)    /*    sm_task.c: 930 */
#define   ESS391      (ERRSS +  391)    /*    sm_task.c: 940 */
#define   ESS392      (ERRSS +  392)    /*    sm_task.c: 948 */
#define   ESS393      (ERRSS +  393)    /*    sm_task.c: 963 */
#define   ESS394      (ERRSS +  394)    /*    sm_task.c: 969 */
#define   ESS395      (ERRSS +  395)    /*    sm_task.c: 987 */
#define   ESS396      (ERRSS +  396)    /*    sm_task.c: 994 */
#define   ESS397      (ERRSS +  397)    /*    sm_task.c:1089 */
#define   ESS398      (ERRSS +  398)    /*    sm_task.c:1170 */
#define   ESS399      (ERRSS +  399)    /*    sm_task.c:1176 */
#define   ESS400      (ERRSS +  400)    /*    sm_task.c:1191 */
#define   ESS401      (ERRSS +  401)    /*    sm_task.c:1205 */
#define   ESS402      (ERRSS +  402)    /*    sm_task.c:1252 */
#define   ESS403      (ERRSS +  403)    /*    sm_task.c:1260 */
#define   ESS404      (ERRSS +  404)    /*    sm_task.c:1277 */
#define   ESS405      (ERRSS +  405)    /*    sm_task.c:1298 */
#define   ESS406      (ERRSS +  406)    /*    sm_task.c:1315 */
#define   ESS407      (ERRSS +  407)    /*    sm_task.c:1334 */
#define   ESS408      (ERRSS +  408)    /*    sm_task.c:1351 */
#define   ESS409      (ERRSS +  409)    /*    sm_task.c:1387 */
#define   ESS410      (ERRSS +  410)    /*    sm_task.c:1406 */
#define   ESS411      (ERRSS +  411)    /*    sm_task.c:1414 */
#define   ESS412      (ERRSS +  412)    /*    sm_task.c:1451 */
#define   ESS413      (ERRSS +  413)    /*    sm_task.c:1470 */
#define   ESS414      (ERRSS +  414)    /*    sm_task.c:1477 */
#define   ESS415      (ERRSS +  415)    /*    sm_task.c:1575 */
#define   ESS416      (ERRSS +  416)    /*    sm_task.c:1594 */
#define   ESS417      (ERRSS +  417)    /*    sm_task.c:1645 */
#define   ESS418      (ERRSS +  418)    /*    sm_task.c:1652 */
#define   ESS419      (ERRSS +  419)    /*    sm_task.c:1665 */
#define   ESS420      (ERRSS +  420)    /*    sm_task.c:1696 */
#define   ESS421      (ERRSS +  421)    /*    sm_task.c:1719 */
#define   ESS422      (ERRSS +  422)    /*    sm_task.c:1727 */
#define   ESS423      (ERRSS +  423)    /*    sm_task.c:1751 */
#define   ESS424      (ERRSS +  424)    /*    sm_task.c:1759 */
#define   ESS425      (ERRSS +  425)    /*    sm_task.c:1778 */
#define   ESS426      (ERRSS +  426)    /*    sm_task.c:1786 */
#define   ESS427      (ERRSS +  427)    /*    sm_task.c:1811 */
#define   ESS428      (ERRSS +  428)    /*    sm_task.c:1819 */
#define   ESS429      (ERRSS +  429)    /*    sm_task.c:1843 */
#define   ESS430      (ERRSS +  430)    /*    sm_task.c:1890 */
#define   ESS431      (ERRSS +  431)    /*    sm_task.c:1954 */
#define   ESS432      (ERRSS +  432)    /*    sm_task.c:2000 */
#define   ESS433      (ERRSS +  433)    /*    sm_task.c:2008 */
#define   ESS434      (ERRSS +  434)    /*    sm_task.c:2036 */
#define   ESS435      (ERRSS +  435)    /*    sm_task.c:2066 */
#define   ESS436      (ERRSS +  436)    /*    sm_task.c:2076 */
#define   ESS437      (ERRSS +  437)    /*    sm_task.c:2085 */
#define   ESS438      (ERRSS +  438)    /*    sm_task.c:2108 */
#define   ESS439      (ERRSS +  439)    /*    sm_task.c:2130 */
#define   ESS440      (ERRSS +  440)    /*    sm_task.c:2153 */
#define   ESS441      (ERRSS +  441)    /*    sm_task.c:2160 */
#define   ESS442      (ERRSS +  442)    /*    sm_task.c:2173 */
#define   ESS443      (ERRSS +  443)    /*    sm_task.c:2190 */
#define   ESS444      (ERRSS +  444)    /*    sm_task.c:2232 */
#define   ESS445      (ERRSS +  445)    /*    sm_task.c:2264 */
#define   ESS446      (ERRSS +  446)    /*    sm_task.c:2272 */
#define   ESS447      (ERRSS +  447)    /*    sm_task.c:2279 */
#define   ESS448      (ERRSS +  448)    /*    sm_task.c:2335 */
#define   ESS449      (ERRSS +  449)    /*    sm_task.c:2347 */
#define   ESS450      (ERRSS +  450)    /*    sm_task.c:2374 */
#define   ESS451      (ERRSS +  451)    /*    sm_task.c:2381 */
#define   ESS452      (ERRSS +  452)    /*    sm_task.c:2395 */
#define   ESS453      (ERRSS +  453)    /*    sm_task.c:2402 */
#define   ESS454      (ERRSS +  454)    /*    sm_task.c:2423 */
#define   ESS455      (ERRSS +  455)    /*    sm_task.c:2431 */
#define   ESS456      (ERRSS +  456)    /*    sm_task.c:2453 */
#define   ESS457      (ERRSS +  457)    /*    sm_task.c:2468 */
#define   ESS458      (ERRSS +  458)    /*    sm_task.c:2476 */
#define   ESS459      (ERRSS +  459)    /*    sm_task.c:2519 */
#define   ESS460      (ERRSS +  460)    /*    sm_task.c:2535 */
#define   ESS461      (ERRSS +  461)    /*    sm_task.c:2557 */
#define   ESS462      (ERRSS +  462)    /*    sm_task.c:2614 */
#define   ESS463      (ERRSS +  463)    /*    sm_task.c:2703 */
#define   ESS464      (ERRSS +  464)    /*    sm_task.c:2710 */
#define   ESS465      (ERRSS +  465)    /*    sm_task.c:2718 */
#define   ESS466      (ERRSS +  466)    /*    sm_task.c:2732 */
#define   ESS467      (ERRSS +  467)    /*    sm_task.c:2745 */
#define   ESS468      (ERRSS +  468)    /*    sm_task.c:2768 */
#define   ESS469      (ERRSS +  469)    /*    sm_task.c:2775 */
#define   ESS470      (ERRSS +  470)    /*    sm_task.c:2796 */
#define   ESS471      (ERRSS +  471)    /*    sm_task.c:2804 */
#define   ESS472      (ERRSS +  472)    /*    sm_task.c:2826 */
#define   ESS473      (ERRSS +  473)    /*    sm_task.c:2841 */
#define   ESS474      (ERRSS +  474)    /*    sm_task.c:2866 */
#define   ESS475      (ERRSS +  475)    /*    sm_task.c:2882 */
#define   ESS476      (ERRSS +  476)    /*    sm_task.c:2890 */
#define   ESS477      (ERRSS +  477)    /*    sm_task.c:2921 */
#define   ESS478      (ERRSS +  478)    /*    sm_task.c:2936 */
#define   ESS479      (ERRSS +  479)    /*    sm_task.c:2943 */
#define   ESS480      (ERRSS +  480)    /*    sm_task.c:2963 */
#define   ESS481      (ERRSS +  481)    /*    sm_task.c:2978 */
#define   ESS482      (ERRSS +  482)    /*    sm_task.c:3003 */
#define   ESS483      (ERRSS +  483)    /*    sm_task.c:3018 */
#define   ESS484      (ERRSS +  484)    /*    sm_task.c:3072 */
#define   ESS485      (ERRSS +  485)    /*    sm_task.c:3087 */
#define   ESS486      (ERRSS +  486)    /*    sm_task.c:3184 */
#define   ESS487      (ERRSS +  487)    /*    sm_task.c:3191 */
#define   ESS488      (ERRSS +  488)    /*    sm_task.c:3205 */
#define   ESS489      (ERRSS +  489)    /*    sm_task.c:3222 */
#define   ESS490      (ERRSS +  490)    /*    sm_task.c:3242 */
#define   ESS491      (ERRSS +  491)    /*    sm_task.c:3250 */
#define   ESS492      (ERRSS +  492)    /*    sm_task.c:3279 */
#define   ESS493      (ERRSS +  493)    /*    sm_task.c:3286 */
#define   ESS494      (ERRSS +  494)    /*    sm_task.c:3312 */
#define   ESS495      (ERRSS +  495)    /*    sm_task.c:3349 */
#define   ESS496      (ERRSS +  496)    /*    sm_task.c:3357 */
#define   ESS497      (ERRSS +  497)    /*    sm_task.c:3379 */
#define   ESS498      (ERRSS +  498)    /*    sm_task.c:3387 */
#define   ESS499      (ERRSS +  499)    /*    sm_task.c:3395 */
#define   ESS500      (ERRSS +  500)    /*    sm_task.c:3442 */
#define   ESS501      (ERRSS +  501)    /*    sm_task.c:3459 */
#define   ESS502      (ERRSS +  502)    /*    sm_task.c:3544 */
#define   ESS503      (ERRSS +  503)    /*    sm_task.c:3552 */
#define   ESS504      (ERRSS +  504)    /*    sm_task.c:3561 */
#define   ESS505      (ERRSS +  505)    /*    sm_task.c:3574 */
#define   ESS506      (ERRSS +  506)    /*    sm_task.c:3600 */
#define   ESS507      (ERRSS +  507)    /*    sm_task.c:3609 */
#define   ESS508      (ERRSS +  508)    /*    sm_task.c:3644 */
#define   ESS509      (ERRSS +  509)    /*    sm_task.c:3653 */
#define   ESS510      (ERRSS +  510)    /*    sm_task.c:3672 */
#define   ESS511      (ERRSS +  511)    /*    sm_task.c:3688 */
#define   ESS512      (ERRSS +  512)    /*    sm_task.c:3718 */
#define   ESS513      (ERRSS +  513)    /*    sm_task.c:3727 */
#define   ESS514      (ERRSS +  514)    /*    sm_task.c:3755 */
#define   ESS515      (ERRSS +  515)    /*    sm_task.c:3764 */
#define   ESS516      (ERRSS +  516)    /*    sm_task.c:3817 */
#define   ESS517      (ERRSS +  517)    /*    sm_task.c:3826 */
#define   ESS518      (ERRSS +  518)    /*    sm_task.c:3833 */
#define   ESS519      (ERRSS +  519)    /*    sm_task.c:3846 */
#define   ESS520      (ERRSS +  520)    /*    sm_task.c:3859 */
#define   ESS521      (ERRSS +  521)    /*    sm_task.c:3876 */
#define   ESS522      (ERRSS +  522)    /*    sm_task.c:3885 */
#define   ESS523      (ERRSS +  523)    /*    sm_task.c:3915 */
#define   ESS524      (ERRSS +  524)    /*    sm_task.c:3924 */
#define   ESS525      (ERRSS +  525)    /*    sm_task.c:3942 */
#define   ESS526      (ERRSS +  526)    /*    sm_task.c:3951 */
#define   ESS527      (ERRSS +  527)    /*    sm_task.c:3967 */

#define   ESS528      (ERRSS +  528)    /*   sm_timer.c: 430 */
#define   ESS529      (ERRSS +  529)    /*   sm_timer.c: 436 */
#define   ESS530      (ERRSS +  530)    /*   sm_timer.c: 444 */
#define   ESS531      (ERRSS +  531)    /*   sm_timer.c: 451 */
#define   ESS532      (ERRSS +  532)    /*   sm_timer.c: 458 */
#define   ESS533      (ERRSS +  533)    /*   sm_timer.c: 468 */
#define   ESS534      (ERRSS +  534)    /*   sm_timer.c: 480 */
#define   ESS535      (ERRSS +  535)    /*   sm_timer.c: 494 */
#define   ESS536      (ERRSS +  536)    /*   sm_timer.c: 499 */
#define   ESS537      (ERRSS +  537)    /*   sm_timer.c: 505 */
#define   ESS538      (ERRSS +  538)    /*   sm_timer.c: 519 */
#define   ESS539      (ERRSS +  539)    /*   sm_timer.c: 532 */
#define   ESS540      (ERRSS +  540)    /*   sm_timer.c: 539 */
#define   ESS541      (ERRSS +  541)    /*   sm_timer.c: 577 */
#define   ESS542      (ERRSS +  542)    /*   sm_timer.c: 646 */
#define   ESS543      (ERRSS +  543)    /*   sm_timer.c: 890 */
#define   ESS544      (ERRSS +  544)    /*   sm_timer.c: 897 */
#define   ESS545      (ERRSS +  545)    /*   sm_timer.c: 904 */
#define   ESS546      (ERRSS +  546)    /*   sm_timer.c: 911 */
#define   ESS547      (ERRSS +  547)    /*   sm_timer.c: 918 */
#define   ESS548      (ERRSS +  548)    /*   sm_timer.c: 928 */
#define   ESS549      (ERRSS +  549)    /*   sm_timer.c: 939 */
#define   ESS550      (ERRSS +  550)    /*   sm_timer.c: 953 */
#define   ESS551      (ERRSS +  551)    /*   sm_timer.c: 958 */
#define   ESS552      (ERRSS +  552)    /*   sm_timer.c: 964 */
#define   ESS553      (ERRSS +  553)    /*   sm_timer.c: 978 */
#define   ESS554      (ERRSS +  554)    /*   sm_timer.c:1022 */
#define   ESS555      (ERRSS +  555)    /*   sm_timer.c:1029 */
#define   ESS556      (ERRSS +  556)    /*   sm_timer.c:1067 */

#define   ESS557      (ERRSS +  557)    /*     ss_acc.c: 556 */
#define   ESS558      (ERRSS +  558)    /*     ss_acc.c: 607 */
#define   ESS559      (ERRSS +  559)    /*     ss_acc.c: 615 */
#define   ESS560      (ERRSS +  560)    /*     ss_acc.c: 623 */
#define   ESS561      (ERRSS +  561)    /*     ss_acc.c: 631 */
#define   ESS562      (ERRSS +  562)    /*     ss_acc.c: 670 */
#define   ESS563      (ERRSS +  563)    /*     ss_acc.c: 681 */
#define   ESS564      (ERRSS +  564)    /*     ss_acc.c: 690 */
#define   ESS565      (ERRSS +  565)    /*     ss_acc.c: 699 */
#define   ESS566      (ERRSS +  566)    /*     ss_acc.c: 708 */
#define   ESS567      (ERRSS +  567)    /*     ss_acc.c: 771 */
#define   ESS568      (ERRSS +  568)    /*     ss_acc.c: 781 */
#define   ESS569      (ERRSS +  569)    /*     ss_acc.c: 792 */
#define   ESS570      (ERRSS +  570)    /*     ss_acc.c: 813 */
#define   ESS571      (ERRSS +  571)    /*     ss_acc.c: 858 */
#define   ESS572      (ERRSS +  572)    /*     ss_acc.c: 868 */
#define   ESS573      (ERRSS +  573)    /*     ss_acc.c: 880 */
#define   ESS574      (ERRSS +  574)    /*     ss_acc.c: 901 */
#define   ESS575      (ERRSS +  575)    /*     ss_acc.c: 999 */
#define   ESS576      (ERRSS +  576)    /*     ss_acc.c:1282 */
#define   ESS577      (ERRSS +  577)    /*     ss_acc.c:1288 */
#define   ESS578      (ERRSS +  578)    /*     ss_acc.c:1291 */
#define   ESS579      (ERRSS +  579)    /*     ss_acc.c:1305 */
#define   ESS580      (ERRSS +  580)    /*     ss_acc.c:1356 */
#define   ESS581      (ERRSS +  581)    /*     ss_acc.c:1362 */
#define   ESS582      (ERRSS +  582)    /*     ss_acc.c:1365 */
#define   ESS583      (ERRSS +  583)    /*     ss_acc.c:1379 */
#define   ESS584      (ERRSS +  584)    /*     ss_acc.c:1420 */
#define   ESS585      (ERRSS +  585)    /*     ss_acc.c:1475 */
#define   ESS586      (ERRSS +  586)    /*     ss_acc.c:1486 */
#define   ESS587      (ERRSS +  587)    /*     ss_acc.c:1544 */
#define   ESS588      (ERRSS +  588)    /*     ss_acc.c:1699 */
#define   ESS589      (ERRSS +  589)    /*     ss_acc.c:1704 */
#define   ESS590      (ERRSS +  590)    /*     ss_acc.c:1712 */
#define   ESS591      (ERRSS +  591)    /*     ss_acc.c:1717 */
#define   ESS592      (ERRSS +  592)    /*     ss_acc.c:1722 */
#define   ESS593      (ERRSS +  593)    /*     ss_acc.c:1727 */
#define   ESS594      (ERRSS +  594)    /*     ss_acc.c:1739 */
#define   ESS595      (ERRSS +  595)    /*     ss_acc.c:1742 */
#define   ESS596      (ERRSS +  596)    /*     ss_acc.c:1746 */
#define   ESS597      (ERRSS +  597)    /*     ss_acc.c:1761 */
#define   ESS598      (ERRSS +  598)    /*     ss_acc.c:1768 */
#define   ESS599      (ERRSS +  599)    /*     ss_acc.c:1785 */
#define   ESS600      (ERRSS +  600)    /*     ss_acc.c:1792 */
#define   ESS601      (ERRSS +  601)    /*     ss_acc.c:1806 */
#define   ESS602      (ERRSS +  602)    /*     ss_acc.c:1824 */
#define   ESS603      (ERRSS +  603)    /*     ss_acc.c:1828 */
#define   ESS604      (ERRSS +  604)    /*     ss_acc.c:1851 */
#define   ESS605      (ERRSS +  605)    /*     ss_acc.c:1854 */
#define   ESS606      (ERRSS +  606)    /*     ss_acc.c:1857 */
#define   ESS607      (ERRSS +  607)    /*     ss_acc.c:1860 */
#define   ESS608      (ERRSS +  608)    /*     ss_acc.c:1868 */
#define   ESS609      (ERRSS +  609)    /*     ss_acc.c:1871 */
#define   ESS610      (ERRSS +  610)    /*     ss_acc.c:1874 */
#define   ESS611      (ERRSS +  611)    /*     ss_acc.c:1877 */
#define   ESS612      (ERRSS +  612)    /*     ss_acc.c:1898 */
#define   ESS613      (ERRSS +  613)    /*     ss_acc.c:1902 */
#define   ESS614      (ERRSS +  614)    /*     ss_acc.c:1919 */
#define   ESS615      (ERRSS +  615)    /*     ss_acc.c:1923 */
#define   ESS616      (ERRSS +  616)    /*     ss_acc.c:1936 */
#define   ESS617      (ERRSS +  617)    /*     ss_acc.c:1943 */
#define   ESS618      (ERRSS +  618)    /*     ss_acc.c:1957 */
#define   ESS619      (ERRSS +  619)    /*     ss_acc.c:1960 */
#define   ESS620      (ERRSS +  620)    /*     ss_acc.c:1964 */
#define   ESS621      (ERRSS +  621)    /*     ss_acc.c:1983 */
#define   ESS622      (ERRSS +  622)    /*     ss_acc.c:1986 */
#define   ESS623      (ERRSS +  623)    /*     ss_acc.c:1989 */
#define   ESS624      (ERRSS +  624)    /*     ss_acc.c:1992 */
#define   ESS625      (ERRSS +  625)    /*     ss_acc.c:1995 */
#define   ESS626      (ERRSS +  626)    /*     ss_acc.c:1998 */
#define   ESS627      (ERRSS +  627)    /*     ss_acc.c:2014 */
#define   ESS628      (ERRSS +  628)    /*     ss_acc.c:2023 */
#define   ESS629      (ERRSS +  629)    /*     ss_acc.c:2028 */
#define   ESS630      (ERRSS +  630)    /*     ss_acc.c:2035 */
#define   ESS631      (ERRSS +  631)    /*     ss_acc.c:2052 */
#define   ESS632      (ERRSS +  632)    /*     ss_acc.c:2060 */
#define   ESS633      (ERRSS +  633)    /*     ss_acc.c:2065 */
#define   ESS634      (ERRSS +  634)    /*     ss_acc.c:2071 */
#define   ESS635      (ERRSS +  635)    /*     ss_acc.c:2087 */
#define   ESS636      (ERRSS +  636)    /*     ss_acc.c:2091 */
#define   ESS637      (ERRSS +  637)    /*     ss_acc.c:2095 */
#define   ESS638      (ERRSS +  638)    /*     ss_acc.c:2120 */
#define   ESS639      (ERRSS +  639)    /*     ss_acc.c:2123 */
#define   ESS640      (ERRSS +  640)    /*     ss_acc.c:2127 */
#define   ESS641      (ERRSS +  641)    /*     ss_acc.c:2135 */
#define   ESS642      (ERRSS +  642)    /*     ss_acc.c:2138 */
#define   ESS643      (ERRSS +  643)    /*     ss_acc.c:2143 */
#define   ESS644      (ERRSS +  644)    /*     ss_acc.c:2168 */
#define   ESS645      (ERRSS +  645)    /*     ss_acc.c:2171 */
#define   ESS646      (ERRSS +  646)    /*     ss_acc.c:2179 */
#define   ESS647      (ERRSS +  647)    /*     ss_acc.c:2186 */
#define   ESS648      (ERRSS +  648)    /*     ss_acc.c:2191 */
#define   ESS649      (ERRSS +  649)    /*     ss_acc.c:2202 */
#define   ESS650      (ERRSS +  650)    /*     ss_acc.c:2207 */
#define   ESS651      (ERRSS +  651)    /*     ss_acc.c:2225 */
#define   ESS652      (ERRSS +  652)    /*     ss_acc.c:2231 */
#define   ESS653      (ERRSS +  653)    /*     ss_acc.c:2248 */
#define   ESS654      (ERRSS +  654)    /*     ss_acc.c:2254 */
#define   ESS655      (ERRSS +  655)    /*     ss_acc.c:2274 */
#define   ESS656      (ERRSS +  656)    /*     ss_acc.c:2294 */
#define   ESS657      (ERRSS +  657)    /*     ss_acc.c:2485 */
#define   ESS658      (ERRSS +  658)    /*     ss_acc.c:2498 */
#define   ESS659      (ERRSS +  659)    /*     ss_acc.c:2516 */
#define   ESS660      (ERRSS +  660)    /*     ss_acc.c:2528 */
#define   ESS661      (ERRSS +  661)    /*     ss_acc.c:2544 */
#define   ESS662      (ERRSS +  662)    /*     ss_acc.c:2567 */
#define   ESS663      (ERRSS +  663)    /*     ss_acc.c:2599 */
#define   ESS664      (ERRSS +  664)    /*     ss_acc.c:2628 */
#define   ESS665      (ERRSS +  665)    /*     ss_acc.c:2660 */
#define   ESS666      (ERRSS +  666)    /*     ss_acc.c:2676 */
#define   ESS667      (ERRSS +  667)    /*     ss_acc.c:2688 */
#define   ESS668      (ERRSS +  668)    /*     ss_acc.c:2702 */
#define   ESS669      (ERRSS +  669)    /*     ss_acc.c:2716 */
#define   ESS670      (ERRSS +  670)    /*     ss_acc.c:2745 */
#define   ESS671      (ERRSS +  671)    /*     ss_acc.c:2779 */
#define   ESS672      (ERRSS +  672)    /*     ss_acc.c:2781 */
#define   ESS673      (ERRSS +  673)    /*     ss_acc.c:2785 */
#define   ESS674      (ERRSS +  674)    /*     ss_acc.c:2787 */
#define   ESS675      (ERRSS +  675)    /*     ss_acc.c:2802 */
#define   ESS676      (ERRSS +  676)    /*     ss_acc.c:2804 */
#define   ESS677      (ERRSS +  677)    /*     ss_acc.c:2808 */
#define   ESS678      (ERRSS +  678)    /*     ss_acc.c:2810 */
#define   ESS679      (ERRSS +  679)    /*     ss_acc.c:2824 */
#define   ESS680      (ERRSS +  680)    /*     ss_acc.c:2833 */
#define   ESS681      (ERRSS +  681)    /*     ss_acc.c:2835 */
#define   ESS682      (ERRSS +  682)    /*     ss_acc.c:2850 */
#define   ESS683      (ERRSS +  683)    /*     ss_acc.c:2879 */
#define   ESS684      (ERRSS +  684)    /*     ss_acc.c:2881 */
#define   ESS685      (ERRSS +  685)    /*     ss_acc.c:2892 */
#define   ESS686      (ERRSS +  686)    /*     ss_acc.c:2911 */
#define   ESS687      (ERRSS +  687)    /*     ss_acc.c:2936 */
#define   ESS688      (ERRSS +  688)    /*     ss_acc.c:2948 */
#define   ESS689      (ERRSS +  689)    /*     ss_acc.c:2953 */
#define   ESS690      (ERRSS +  690)    /*     ss_acc.c:2960 */
#define   ESS691      (ERRSS +  691)    /*     ss_acc.c:2966 */
#define   ESS692      (ERRSS +  692)    /*     ss_acc.c:2986 */
#define   ESS693      (ERRSS +  693)    /*     ss_acc.c:2995 */
#define   ESS694      (ERRSS +  694)    /*     ss_acc.c:3000 */
#define   ESS695      (ERRSS +  695)    /*     ss_acc.c:3007 */
#define   ESS696      (ERRSS +  696)    /*     ss_acc.c:3030 */
#define   ESS697      (ERRSS +  697)    /*     ss_acc.c:3035 */
#define   ESS698      (ERRSS +  698)    /*     ss_acc.c:3041 */
#define   ESS699      (ERRSS +  699)    /*     ss_acc.c:3046 */
#define   ESS700      (ERRSS +  700)    /*     ss_acc.c:3094 */
#define   ESS701      (ERRSS +  701)    /*     ss_acc.c:3152 */
#define   ESS702      (ERRSS +  702)    /*     ss_acc.c:3185 */
#define   ESS703      (ERRSS +  703)    /*     ss_acc.c:3203 */
#define   ESS704      (ERRSS +  704)    /*     ss_acc.c:3215 */
#define   ESS705      (ERRSS +  705)    /*     ss_acc.c:3227 */
#define   ESS706      (ERRSS +  706)    /*     ss_acc.c:3240 */
#define   ESS707      (ERRSS +  707)    /*     ss_acc.c:3245 */
#define   ESS708      (ERRSS +  708)    /*     ss_acc.c:3251 */
#define   ESS709      (ERRSS +  709)    /*     ss_acc.c:3263 */
#define   ESS710      (ERRSS +  710)    /*     ss_acc.c:3276 */
#define   ESS711      (ERRSS +  711)    /*     ss_acc.c:3292 */
#define   ESS712      (ERRSS +  712)    /*     ss_acc.c:3296 */
#define   ESS713      (ERRSS +  713)    /*     ss_acc.c:3300 */
#define   ESS714      (ERRSS +  714)    /*     ss_acc.c:3304 */
#define   ESS715      (ERRSS +  715)    /*     ss_acc.c:3308 */
#define   ESS716      (ERRSS +  716)    /*     ss_acc.c:3325 */
#define   ESS717      (ERRSS +  717)    /*     ss_acc.c:3329 */
#define   ESS718      (ERRSS +  718)    /*     ss_acc.c:3333 */
#define   ESS719      (ERRSS +  719)    /*     ss_acc.c:3337 */
#define   ESS720      (ERRSS +  720)    /*     ss_acc.c:3341 */
#define   ESS721      (ERRSS +  721)    /*     ss_acc.c:3358 */
#define   ESS722      (ERRSS +  722)    /*     ss_acc.c:3362 */
#define   ESS723      (ERRSS +  723)    /*     ss_acc.c:3366 */
#define   ESS724      (ERRSS +  724)    /*     ss_acc.c:3370 */
#define   ESS725      (ERRSS +  725)    /*     ss_acc.c:3374 */
#define   ESS726      (ERRSS +  726)    /*     ss_acc.c:3378 */
#define   ESS727      (ERRSS +  727)    /*     ss_acc.c:3382 */
#define   ESS728      (ERRSS +  728)    /*     ss_acc.c:3398 */
#define   ESS729      (ERRSS +  729)    /*     ss_acc.c:3402 */
#define   ESS730      (ERRSS +  730)    /*     ss_acc.c:3406 */
#define   ESS731      (ERRSS +  731)    /*     ss_acc.c:3410 */
#define   ESS732      (ERRSS +  732)    /*     ss_acc.c:3430 */
#define   ESS733      (ERRSS +  733)    /*     ss_acc.c:3434 */
#define   ESS734      (ERRSS +  734)    /*     ss_acc.c:3438 */
#define   ESS735      (ERRSS +  735)    /*     ss_acc.c:3453 */
#define   ESS736      (ERRSS +  736)    /*     ss_acc.c:3457 */
#define   ESS737      (ERRSS +  737)    /*     ss_acc.c:3461 */
#define   ESS738      (ERRSS +  738)    /*     ss_acc.c:3477 */
#define   ESS739      (ERRSS +  739)    /*     ss_acc.c:3481 */
#define   ESS740      (ERRSS +  740)    /*     ss_acc.c:3485 */
#define   ESS741      (ERRSS +  741)    /*     ss_acc.c:3489 */
#define   ESS742      (ERRSS +  742)    /*     ss_acc.c:3493 */
#define   ESS743      (ERRSS +  743)    /*     ss_acc.c:3508 */
#define   ESS744      (ERRSS +  744)    /*     ss_acc.c:3512 */
#define   ESS745      (ERRSS +  745)    /*     ss_acc.c:3516 */
#define   ESS746      (ERRSS +  746)    /*     ss_acc.c:3531 */
#define   ESS747      (ERRSS +  747)    /*     ss_acc.c:3535 */
#define   ESS748      (ERRSS +  748)    /*     ss_acc.c:3539 */
#define   ESS749      (ERRSS +  749)    /*     ss_acc.c:3543 */
#define   ESS750      (ERRSS +  750)    /*     ss_acc.c:3547 */
#define   ESS751      (ERRSS +  751)    /*     ss_acc.c:3562 */
#define   ESS752      (ERRSS +  752)    /*     ss_acc.c:3566 */
#define   ESS753      (ERRSS +  753)    /*     ss_acc.c:3570 */
#define   ESS754      (ERRSS +  754)    /*     ss_acc.c:3574 */
#define   ESS755      (ERRSS +  755)    /*     ss_acc.c:3578 */
#define   ESS756      (ERRSS +  756)    /*     ss_acc.c:3593 */
#define   ESS757      (ERRSS +  757)    /*     ss_acc.c:3597 */
#define   ESS758      (ERRSS +  758)    /*     ss_acc.c:3601 */
#define   ESS759      (ERRSS +  759)    /*     ss_acc.c:3605 */
#define   ESS760      (ERRSS +  760)    /*     ss_acc.c:3609 */
#define   ESS761      (ERRSS +  761)    /*     ss_acc.c:3625 */
#define   ESS762      (ERRSS +  762)    /*     ss_acc.c:3629 */
#define   ESS763      (ERRSS +  763)    /*     ss_acc.c:3633 */
#define   ESS764      (ERRSS +  764)    /*     ss_acc.c:3637 */
#define   ESS765      (ERRSS +  765)    /*     ss_acc.c:3654 */
#define   ESS766      (ERRSS +  766)    /*     ss_acc.c:3658 */
#define   ESS767      (ERRSS +  767)    /*     ss_acc.c:3674 */
#define   ESS768      (ERRSS +  768)    /*     ss_acc.c:3680 */
#define   ESS769      (ERRSS +  769)    /*     ss_acc.c:3684 */
#define   ESS770      (ERRSS +  770)    /*     ss_acc.c:4059 */
#define   ESS771      (ERRSS +  771)    /*     ss_acc.c:4062 */
#define   ESS772      (ERRSS +  772)    /*     ss_acc.c:4066 */
#define   ESS773      (ERRSS +  773)    /*     ss_acc.c:4076 */
#define   ESS774      (ERRSS +  774)    /*     ss_acc.c:4083 */
#define   ESS775      (ERRSS +  775)    /*     ss_acc.c:4095 */
#define   ESS776      (ERRSS +  776)    /*     ss_acc.c:4102 */
#define   ESS777      (ERRSS +  777)    /*     ss_acc.c:4116 */
#define   ESS778      (ERRSS +  778)    /*     ss_acc.c:4130 */
#define   ESS779      (ERRSS +  779)    /*     ss_acc.c:4134 */
#define   ESS780      (ERRSS +  780)    /*     ss_acc.c:4154 */
#define   ESS781      (ERRSS +  781)    /*     ss_acc.c:4157 */
#define   ESS782      (ERRSS +  782)    /*     ss_acc.c:4160 */
#define   ESS783      (ERRSS +  783)    /*     ss_acc.c:4163 */
#define   ESS784      (ERRSS +  784)    /*     ss_acc.c:4171 */
#define   ESS785      (ERRSS +  785)    /*     ss_acc.c:4174 */
#define   ESS786      (ERRSS +  786)    /*     ss_acc.c:4177 */
#define   ESS787      (ERRSS +  787)    /*     ss_acc.c:4180 */
#define   ESS788      (ERRSS +  788)    /*     ss_acc.c:4197 */
#define   ESS789      (ERRSS +  789)    /*     ss_acc.c:4201 */
#define   ESS790      (ERRSS +  790)    /*     ss_acc.c:4214 */
#define   ESS791      (ERRSS +  791)    /*     ss_acc.c:4218 */
#define   ESS792      (ERRSS +  792)    /*     ss_acc.c:4231 */
#define   ESS793      (ERRSS +  793)    /*     ss_acc.c:4238 */
#define   ESS794      (ERRSS +  794)    /*     ss_acc.c:4302 */
#define   ESS795      (ERRSS +  795)    /*     ss_acc.c:4305 */
#define   ESS796      (ERRSS +  796)    /*     ss_acc.c:4309 */
#define   ESS797      (ERRSS +  797)    /*     ss_acc.c:4324 */
#define   ESS798      (ERRSS +  798)    /*     ss_acc.c:4327 */
#define   ESS799      (ERRSS +  799)    /*     ss_acc.c:4330 */
#define   ESS800      (ERRSS +  800)    /*     ss_acc.c:4333 */
#define   ESS801      (ERRSS +  801)    /*     ss_acc.c:4336 */
#define   ESS802      (ERRSS +  802)    /*     ss_acc.c:4339 */
#define   ESS803      (ERRSS +  803)    /*     ss_acc.c:4351 */
#define   ESS804      (ERRSS +  804)    /*     ss_acc.c:4360 */
#define   ESS805      (ERRSS +  805)    /*     ss_acc.c:4365 */
#define   ESS806      (ERRSS +  806)    /*     ss_acc.c:4372 */
#define   ESS807      (ERRSS +  807)    /*     ss_acc.c:4385 */
#define   ESS808      (ERRSS +  808)    /*     ss_acc.c:4393 */
#define   ESS809      (ERRSS +  809)    /*     ss_acc.c:4398 */
#define   ESS810      (ERRSS +  810)    /*     ss_acc.c:4404 */
#define   ESS811      (ERRSS +  811)    /*     ss_acc.c:4416 */
#define   ESS812      (ERRSS +  812)    /*     ss_acc.c:4420 */
#define   ESS813      (ERRSS +  813)    /*     ss_acc.c:4424 */
#define   ESS814      (ERRSS +  814)    /*     ss_acc.c:4445 */
#define   ESS815      (ERRSS +  815)    /*     ss_acc.c:4448 */
#define   ESS816      (ERRSS +  816)    /*     ss_acc.c:4453 */
#define   ESS817      (ERRSS +  817)    /*     ss_acc.c:4461 */
#define   ESS818      (ERRSS +  818)    /*     ss_acc.c:4464 */
#define   ESS819      (ERRSS +  819)    /*     ss_acc.c:4469 */
#define   ESS820      (ERRSS +  820)    /*     ss_acc.c:4487 */
#define   ESS821      (ERRSS +  821)    /*     ss_acc.c:4490 */
#define   ESS822      (ERRSS +  822)    /*     ss_acc.c:4498 */
#define   ESS823      (ERRSS +  823)    /*     ss_acc.c:4505 */
#define   ESS824      (ERRSS +  824)    /*     ss_acc.c:4510 */
#define   ESS825      (ERRSS +  825)    /*     ss_acc.c:4524 */
#define   ESS826      (ERRSS +  826)    /*     ss_acc.c:4529 */
#define   ESS827      (ERRSS +  827)    /*     ss_acc.c:4543 */
#define   ESS828      (ERRSS +  828)    /*     ss_acc.c:4549 */
#define   ESS829      (ERRSS +  829)    /*     ss_acc.c:4562 */
#define   ESS830      (ERRSS +  830)    /*     ss_acc.c:4568 */
#define   ESS831      (ERRSS +  831)    /*     ss_acc.c:4584 */
#define   ESS832      (ERRSS +  832)    /*     ss_acc.c:4645 */
#define   ESS833      (ERRSS +  833)    /*     ss_acc.c:4659 */
#define   ESS834      (ERRSS +  834)    /*     ss_acc.c:4666 */
#define   ESS835      (ERRSS +  835)    /*     ss_acc.c:4677 */
#define   ESS836      (ERRSS +  836)    /*     ss_acc.c:4738 */
#define   ESS837      (ERRSS +  837)    /*     ss_acc.c:4766 */
#define   ESS838      (ERRSS +  838)    /*     ss_acc.c:4791 */
#define   ESS839      (ERRSS +  839)    /*     ss_acc.c:4819 */
#define   ESS840      (ERRSS +  840)    /*     ss_acc.c:4872 */
#define   ESS841      (ERRSS +  841)    /*     ss_acc.c:4883 */
#define   ESS842      (ERRSS +  842)    /*     ss_acc.c:4955 */
#define   ESS843      (ERRSS +  843)    /*     ss_acc.c:4958 */
#define   ESS844      (ERRSS +  844)    /*     ss_acc.c:4961 */
#define   ESS845      (ERRSS +  845)    /*     ss_acc.c:4964 */
#define   ESS846      (ERRSS +  846)    /*     ss_acc.c:4972 */
#define   ESS847      (ERRSS +  847)    /*     ss_acc.c:4975 */
#define   ESS848      (ERRSS +  848)    /*     ss_acc.c:4978 */
#define   ESS849      (ERRSS +  849)    /*     ss_acc.c:4981 */
#define   ESS850      (ERRSS +  850)    /*     ss_acc.c:5041 */
#define   ESS851      (ERRSS +  851)    /*     ss_acc.c:5045 */
#define   ESS852      (ERRSS +  852)    /*     ss_acc.c:5104 */
#define   ESS853      (ERRSS +  853)    /*     ss_acc.c:5108 */
#define   ESS854      (ERRSS +  854)    /*     ss_acc.c:5121 */
#define   ESS855      (ERRSS +  855)    /*     ss_acc.c:5128 */
#define   ESS856      (ERRSS +  856)    /*     ss_acc.c:5276 */
#define   ESS857      (ERRSS +  857)    /*     ss_acc.c:5285 */
#define   ESS858      (ERRSS +  858)    /*     ss_acc.c:5305 */
#define   ESS859      (ERRSS +  859)    /*     ss_acc.c:5326 */
#define   ESS860      (ERRSS +  860)    /*     ss_acc.c:5336 */
#define   ESS861      (ERRSS +  861)    /*     ss_acc.c:5357 */
#define   ESS862      (ERRSS +  862)    /*     ss_acc.c:5378 */
#define   ESS863      (ERRSS +  863)    /*     ss_acc.c:5387 */
#define   ESS864      (ERRSS +  864)    /*     ss_acc.c:5408 */
#define   ESS865      (ERRSS +  865)    /*     ss_acc.c:5429 */
#define   ESS866      (ERRSS +  866)    /*     ss_acc.c:5438 */
#define   ESS867      (ERRSS +  867)    /*     ss_acc.c:5458 */
#define   ESS868      (ERRSS +  868)    /*     ss_acc.c:5479 */
#define   ESS869      (ERRSS +  869)    /*     ss_acc.c:5488 */
#define   ESS870      (ERRSS +  870)    /*     ss_acc.c:5508 */
#define   ESS871      (ERRSS +  871)    /*     ss_acc.c:5533 */
#define   ESS872      (ERRSS +  872)    /*     ss_acc.c:5549 */
#define   ESS873      (ERRSS +  873)    /*     ss_acc.c:5565 */
#define   ESS874      (ERRSS +  874)    /*     ss_acc.c:5581 */
#define   ESS875      (ERRSS +  875)    /*     ss_acc.c:5596 */
#define   ESS876      (ERRSS +  876)    /*     ss_acc.c:5646 */
#define   ESS877      (ERRSS +  877)    /*     ss_acc.c:5694 */
#define   ESS878      (ERRSS +  878)    /*     ss_acc.c:5742 */
#define   ESS879      (ERRSS +  879)    /*     ss_acc.c:5790 */
#define   ESS880      (ERRSS +  880)    /*     ss_acc.c:5838 */
#define   ESS881      (ERRSS +  881)    /*     ss_acc.c:6106 */


#ifdef __cplusplus
}
#endif

#endif  /* __SSERRH__ */


  
/********************************************************************30**
  
         End of file:     ss_err.h@@/main/4 - Mon Nov 17 15:54:15 2008
   
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

1.2          ---      bsr  1. Updated error codes
  
1.3          ---      ada  1. Added typecast in SLogError to remove
                              diab compile errors 
                      kp   1. Regenerated error codes
1.3+        ss029.103 kkj  1. Multiple proc ids support added
1.3+        ss038.103 svp  1. Added error codes for floating point support 
/main/4      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/
