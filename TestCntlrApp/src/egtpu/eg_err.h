
/********************************************************************20**

     Name:    EGTP - 

     Type:    C source file

     Desc:    

     File:    eg_err.h

     Sid:      eg_err.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:44 2015

     Prg:    ad  

*********************************************************************21*/
#ifndef __EGERRH__
#define __EGERRH__

#define EGLOGINVSEL \
        SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,            \
                 (Txt *) __FILE__, __LINE__,                                   \
                  ERRCLS_DEBUG, EEGXXX,                                 \
                  0, (Txt *)"Invalid selector");


#define EGLOGERROR(errCls, errCode, errVal, errDesc) \
        SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, \
                 (Txt *) __FILE__, __LINE__, errCls, errCode, errVal,\
                 (Txt *)errDesc);

#define EEGBASE       0
#define EEGXXX        (EEGBASE + 0)    /* reserved */
#define ERREG         (EEGBASE + 0)    /* reserved */

#define   EEG001      (ERREG +    1)    /*         eg.h: 207 */
#define   EEG002      (ERREG +    2)    /*         eg.h: 928 */

#define   EEG003      (ERREG +    3)    /*     eg_edm.h: 354 */

#define   EEG004      (ERREG +    4)    /*    eg_ptli.c: 589 */
#define   EEG005      (ERREG +    5)    /*    eg_ptli.c: 627 */
#define   EEG006      (ERREG +    6)    /*    eg_ptli.c: 674 */
#define   EEG007      (ERREG +    7)    /*    eg_ptli.c: 727 */
#define   EEG008      (ERREG +    8)    /*    eg_ptli.c: 775 */

#define   EEG009      (ERREG +    9)    /*    eg_ptmi.c: 510 */
#define   EEG010      (ERREG +   10)    /*    eg_ptmi.c: 546 */
#define   EEG011      (ERREG +   11)    /*    eg_ptmi.c: 582 */
#define   EEG012      (ERREG +   12)    /*    eg_ptmi.c: 618 */
#define   EEG013      (ERREG +   13)    /*    eg_ptmi.c: 654 */
#define   EEG014      (ERREG +   14)    /*    eg_ptmi.c: 692 */

#define   EEG015      (ERREG +   15)    /*    eg_ptui.c: 983 */
#define   EEG016      (ERREG +   16)    /*    eg_ptui.c:1028 */
#define   EEG017      (ERREG +   17)    /*    eg_ptui.c:1077 */
#define   EEG018      (ERREG +   18)    /*    eg_ptui.c:1118 */
#define   EEG019      (ERREG +   19)    /*    eg_ptui.c:1159 */
#define   EEG020      (ERREG +   20)    /*    eg_ptui.c:1201 */
#define   EEG021      (ERREG +   21)    /*    eg_ptui.c:1246 */

#define   EEG022      (ERREG +   22)    /*    eg_util.c:1132 */
#define   EEG023      (ERREG +   23)    /*    eg_util.c:1189 */
#define   EEG024      (ERREG +   24)    /*    eg_util.c:1279 */
#define   EEG025      (ERREG +   25)    /*    eg_util.c:1460 */
#define   EEG026      (ERREG +   26)    /*    eg_util.c:1471 */
#define   EEG027      (ERREG +   27)    /*    eg_util.c:1619 */
#define   EEG028      (ERREG +   28)    /*    eg_util.c:1659 */
#define   EEG029      (ERREG +   29)    /*    eg_util.c:1752 */
#define   EEG030      (ERREG +   30)    /*    eg_util.c:1847 */
#define   EEG031      (ERREG +   31)    /*    eg_util.c:1965 */
#define   EEG032      (ERREG +   32)    /*    eg_util.c:1986 */
#define   EEG033      (ERREG +   33)    /*    eg_util.c:2020 */
#define   EEG034      (ERREG +   34)    /*    eg_util.c:2074 */
#define   EEG035      (ERREG +   35)    /*    eg_util.c:2096 */
#define   EEG036      (ERREG +   36)    /*    eg_util.c:2237 */
#define   EEG037      (ERREG +   37)    /*    eg_util.c:2302 */
#define   EEG038      (ERREG +   38)    /*    eg_util.c:2317 */
#define   EEG039      (ERREG +   39)    /*    eg_util.c:2399 */
#define   EEG040      (ERREG +   40)    /*    eg_util.c:2418 */
#define   EEG041      (ERREG +   41)    /*    eg_util.c:2485 */
#define   EEG042      (ERREG +   42)    /*    eg_util.c:2867 */
#define   EEG043      (ERREG +   43)    /*    eg_util.c:2951 */
#define   EEG044      (ERREG +   44)    /*    eg_util.c:2965 */
#define   EEG045      (ERREG +   45)    /*    eg_util.c:3174 */
#define   EEG046      (ERREG +   46)    /*    eg_util.c:3193 */
#define   EEG047      (ERREG +   47)    /*    eg_util.c:4235 */
#define   EEG048      (ERREG +   48)    /*    eg_util.c:4340 */
#define   EEG049      (ERREG +   49)    /*    eg_util.c:4351 */
#define   EEG050      (ERREG +   50)    /*    eg_util.c:4369 */
#define   EEG051      (ERREG +   51)    /*    eg_util.c:4379 */
#define   EEG052      (ERREG +   52)    /*    eg_util.c:4514 */
#define   EEG053      (ERREG +   53)    /*    eg_util.c:4553 */
#define   EEG054      (ERREG +   54)    /*    eg_util.c:4570 */
#define   EEG055      (ERREG +   55)    /*    eg_util.c:4600 */
#define   EEG056      (ERREG +   56)    /*    eg_util.c:4610 */
#define   EEG057      (ERREG +   57)    /*    eg_util.c:4677 */
#define   EEG058      (ERREG +   58)    /*    eg_util.c:4749 */
#define   EEG059      (ERREG +   59)    /*    eg_util.c:4759 */
#define   EEG060      (ERREG +   60)    /*    eg_util.c:4769 */
#define   EEG061      (ERREG +   61)    /*    eg_util.c:4836 */
#define   EEG062      (ERREG +   62)    /*    eg_util.c:5030 */
#define   EEG063      (ERREG +   63)    /*    eg_util.c:5096 */
#define   EEG064      (ERREG +   64)    /*    eg_util.c:5172 */
#define   EEG065      (ERREG +   65)    /*    eg_util.c:5253 */
#define   EEG066      (ERREG +   66)    /*    eg_util.c:5309 */
#define   EEG067      (ERREG +   67)    /*    eg_util.c:5388 */
#define   EEG068      (ERREG +   68)    /*    eg_util.c:5472 */
#define   EEG069      (ERREG +   69)    /*    eg_util.c:5488 */
#define   EEG070      (ERREG +   70)    /*    eg_util.c:5729 */
#define   EEG071      (ERREG +   71)    /*    eg_util.c:5881 */
#define   EEG072      (ERREG +   72)    /*    eg_util.c:5950 */
#define   EEG073      (ERREG +   73)    /*    eg_util.c:5960 */

#define   EEG074      (ERREG +   74)    /*   eu_ex_ms.c: 282 */
#define   EEG075      (ERREG +   75)    /*   eu_ex_ms.c: 376 */

#define   EEG076      (ERREG +   76)    /*    eu_ptli.c: 822 */
#define   EEG077      (ERREG +   77)    /*    eu_ptli.c: 862 */

#define   EEG078      (ERREG +   78)    /*     pg_cpm.c:3763 */

#define   EEG079      (ERREG +   79)    /*     pg_edm.c: 539 */
#define   EEG080      (ERREG +   80)    /*     pg_edm.c: 557 */
#define   EEG081      (ERREG +   81)    /*     pg_edm.c:2521 */
#define   EEG082      (ERREG +   82)    /*     pg_edm.c:2915 */
#define   EEG083      (ERREG +   83)    /*     pg_edm.c:3430 */
#define   EEG084      (ERREG +   84)    /*     pg_edm.c:3508 */
#define   EEG085      (ERREG +   85)    /*     pg_edm.c:3664 */
#define   EEG086      (ERREG +   86)    /*     pg_edm.c:3691 */
#define   EEG087      (ERREG +   87)    /*     pg_edm.c:3706 */
#define   EEG088      (ERREG +   88)    /*     pg_edm.c:3793 */
#define   EEG089      (ERREG +   89)    /*     pg_edm.c:3822 */
#define   EEG090      (ERREG +   90)    /*     pg_edm.c:3845 */
#define   EEG091      (ERREG +   91)    /*     pg_edm.c:3882 */
#define   EEG092      (ERREG +   92)    /*     pg_edm.c:4195 */
#define   EEG093      (ERREG +   93)    /*     pg_edm.c:4764 */

#define   EEG094      (ERREG +   94)    /*   pg_ex_ms.c: 181 */
#define   EEG095      (ERREG +   95)    /*   pg_ex_ms.c: 200 */
#define   EEG096      (ERREG +   96)    /*   pg_ex_ms.c: 276 */
#define   EEG097      (ERREG +   97)    /*   pg_ex_ms.c: 387 */
#define   EEG098      (ERREG +   98)    /*   pg_ex_ms.c: 450 */
#define   EEG099      (ERREG +   99)    /*   pg_ex_ms.c: 468 */
#define   EEG100      (ERREG +  100)    /*   pg_ex_ms.c: 499 */
#define   EEG101      (ERREG +  101)    /*   pg_ex_ms.c: 513 */
#define   EEG102      (ERREG +  102)    /*   pg_ex_ms.c: 574 */
#define   EEG103      (ERREG +  103)    /*   pg_ex_ms.c: 594 */
#define   EEG104      (ERREG +  104)    /*   pg_ex_ms.c: 608 */
#define   EEG105      (ERREG +  105)    /*   pg_ex_ms.c: 679 */
#define   EEG106      (ERREG +  106)    /*   pg_ex_ms.c: 714 */
#define   EEG107      (ERREG +  107)    /*   pg_ex_ms.c: 735 */
#define   EEG108      (ERREG +  108)    /*   pg_ex_ms.c: 751 */

#define   EEG109      (ERREG +  109)    /*      pg_li.c: 194 */
#define   EEG110      (ERREG +  110)    /*      pg_li.c: 311 */
#define   EEG111      (ERREG +  111)    /*      pg_li.c: 502 */
#define   EEG112      (ERREG +  112)    /*      pg_li.c: 699 */
#define   EEG113      (ERREG +  113)    /*      pg_li.c: 940 */
#define   EEG114      (ERREG +  114)    /*      pg_li.c:1092 */

#define   EEG115      (ERREG +  115)    /*      pg_mi.c: 909 */
#define   EEG116      (ERREG +  116)    /*      pg_mi.c: 946 */
#define   EEG117      (ERREG +  117)    /*      pg_mi.c:1127 */
#define   EEG118      (ERREG +  118)    /*      pg_mi.c:1220 */
#define   EEG119      (ERREG +  119)    /*      pg_mi.c:1230 */
#define   EEG120      (ERREG +  120)    /*      pg_mi.c:1241 */
#define   EEG121      (ERREG +  121)    /*      pg_mi.c:1250 */
#define   EEG122      (ERREG +  122)    /*      pg_mi.c:1260 */
#define   EEG123      (ERREG +  123)    /*      pg_mi.c:1270 */
#define   EEG124      (ERREG +  124)    /*      pg_mi.c:1281 */
#define   EEG125      (ERREG +  125)    /*      pg_mi.c:1290 */
#define   EEG126      (ERREG +  126)    /*      pg_mi.c:1300 */
#define   EEG127      (ERREG +  127)    /*      pg_mi.c:1309 */
#define   EEG128      (ERREG +  128)    /*      pg_mi.c:1319 */
#define   EEG129      (ERREG +  129)    /*      pg_mi.c:1328 */
#define   EEG130      (ERREG +  130)    /*      pg_mi.c:1337 */
#define   EEG131      (ERREG +  131)    /*      pg_mi.c:1346 */
#define   EEG132      (ERREG +  132)    /*      pg_mi.c:1355 */
#define   EEG133      (ERREG +  133)    /*      pg_mi.c:1364 */
#define   EEG134      (ERREG +  134)    /*      pg_mi.c:1373 */
#define   EEG135      (ERREG +  135)    /*      pg_mi.c:1382 */
#define   EEG136      (ERREG +  136)    /*      pg_mi.c:1392 */
#define   EEG137      (ERREG +  137)    /*      pg_mi.c:1401 */
#define   EEG138      (ERREG +  138)    /*      pg_mi.c:1461 */
#define   EEG139      (ERREG +  139)    /*      pg_mi.c:1481 */
#define   EEG140      (ERREG +  140)    /*      pg_mi.c:1538 */
#define   EEG141      (ERREG +  141)    /*      pg_mi.c:1557 */
#define   EEG142      (ERREG +  142)    /*      pg_mi.c:1590 */
#define   EEG143      (ERREG +  143)    /*      pg_mi.c:1608 */
#define   EEG144      (ERREG +  144)    /*      pg_mi.c:1645 */
#define   EEG145      (ERREG +  145)    /*      pg_mi.c:1795 */
#define   EEG146      (ERREG +  146)    /*      pg_mi.c:1818 */
#define   EEG147      (ERREG +  147)    /*      pg_mi.c:1836 */
#define   EEG148      (ERREG +  148)    /*      pg_mi.c:1856 */
#define   EEG149      (ERREG +  149)    /*      pg_mi.c:1873 */
#define   EEG150      (ERREG +  150)    /*      pg_mi.c:1934 */
#define   EEG151      (ERREG +  151)    /*      pg_mi.c:1953 */
#define   EEG152      (ERREG +  152)    /*      pg_mi.c:2052 */
#define   EEG153      (ERREG +  153)    /*      pg_mi.c:2071 */
#define   EEG154      (ERREG +  154)    /*      pg_mi.c:2121 */
#define   EEG155      (ERREG +  155)    /*      pg_mi.c:2134 */
#define   EEG156      (ERREG +  156)    /*      pg_mi.c:2178 */
#define   EEG157      (ERREG +  157)    /*      pg_mi.c:2182 */
#define   EEG158      (ERREG +  158)    /*      pg_mi.c:2235 */
#define   EEG159      (ERREG +  159)    /*      pg_mi.c:2244 */
#define   EEG160      (ERREG +  160)    /*      pg_mi.c:2254 */
#define   EEG161      (ERREG +  161)    /*      pg_mi.c:2263 */
#define   EEG162      (ERREG +  162)    /*      pg_mi.c:2321 */
#define   EEG163      (ERREG +  163)    /*      pg_mi.c:2334 */
#define   EEG164      (ERREG +  164)    /*      pg_mi.c:2479 */
#define   EEG165      (ERREG +  165)    /*      pg_mi.c:2504 */
#define   EEG166      (ERREG +  166)    /*      pg_mi.c:2526 */
#define   EEG167      (ERREG +  167)    /*      pg_mi.c:2545 */
#define   EEG168      (ERREG +  168)    /*      pg_mi.c:2555 */
#define   EEG169      (ERREG +  169)    /*      pg_mi.c:2577 */
#define   EEG170      (ERREG +  170)    /*      pg_mi.c:2596 */
#define   EEG171      (ERREG +  171)    /*      pg_mi.c:2610 */
#define   EEG172      (ERREG +  172)    /*      pg_mi.c:2630 */
#define   EEG173      (ERREG +  173)    /*      pg_mi.c:2646 */
#define   EEG174      (ERREG +  174)    /*      pg_mi.c:2676 */
#define   EEG175      (ERREG +  175)    /*      pg_mi.c:2708 */
#define   EEG176      (ERREG +  176)    /*      pg_mi.c:2746 */
#define   EEG177      (ERREG +  177)    /*      pg_mi.c:2770 */
#define   EEG178      (ERREG +  178)    /*      pg_mi.c:2784 */
#define   EEG179      (ERREG +  179)    /*      pg_mi.c:2813 */
#define   EEG180      (ERREG +  180)    /*      pg_mi.c:2853 */
#define   EEG181      (ERREG +  181)    /*      pg_mi.c:2866 */
#define   EEG182      (ERREG +  182)    /*      pg_mi.c:2885 */
#define   EEG183      (ERREG +  183)    /*      pg_mi.c:2904 */
#define   EEG184      (ERREG +  184)    /*      pg_mi.c:2924 */
#define   EEG185      (ERREG +  185)    /*      pg_mi.c:2995 */
#define   EEG186      (ERREG +  186)    /*      pg_mi.c:3020 */
#define   EEG187      (ERREG +  187)    /*      pg_mi.c:3046 */
#define   EEG188      (ERREG +  188)    /*      pg_mi.c:3069 */
#define   EEG189      (ERREG +  189)    /*      pg_mi.c:3148 */
#define   EEG190      (ERREG +  190)    /*      pg_mi.c:3237 */
#define   EEG191      (ERREG +  191)    /*      pg_mi.c:3347 */
#define   EEG192      (ERREG +  192)    /*      pg_mi.c:3363 */
#define   EEG193      (ERREG +  193)    /*      pg_mi.c:3403 */
#define   EEG194      (ERREG +  194)    /*      pg_mi.c:3417 */
#define   EEG195      (ERREG +  195)    /*      pg_mi.c:3432 */
#define   EEG196      (ERREG +  196)    /*      pg_mi.c:3444 */
#define   EEG197      (ERREG +  197)    /*      pg_mi.c:3492 */
#define   EEG198      (ERREG +  198)    /*      pg_mi.c:3501 */
#define   EEG199      (ERREG +  199)    /*      pg_mi.c:3515 */
#define   EEG200      (ERREG +  200)    /*      pg_mi.c:3536 */
#define   EEG201      (ERREG +  201)    /*      pg_mi.c:3547 */
#define   EEG202      (ERREG +  202)    /*      pg_mi.c:3570 */
#define   EEG203      (ERREG +  203)    /*      pg_mi.c:3590 */
#define   EEG204      (ERREG +  204)    /*      pg_mi.c:3635 */
#define   EEG205      (ERREG +  205)    /*      pg_mi.c:3652 */
#define   EEG206      (ERREG +  206)    /*      pg_mi.c:3683 */
#define   EEG207      (ERREG +  207)    /*      pg_mi.c:3697 */
#define   EEG208      (ERREG +  208)    /*      pg_mi.c:3742 */
#define   EEG209      (ERREG +  209)    /*      pg_mi.c:3752 */
#define   EEG210      (ERREG +  210)    /*      pg_mi.c:3810 */
#define   EEG211      (ERREG +  211)    /*      pg_mi.c:3878 */
#define   EEG212      (ERREG +  212)    /*      pg_mi.c:4009 */
#define   EEG213      (ERREG +  213)    /*      pg_mi.c:4064 */
#define   EEG214      (ERREG +  214)    /*      pg_mi.c:4080 */
#define   EEG215      (ERREG +  215)    /*      pg_mi.c:4095 */
#define   EEG216      (ERREG +  216)    /*      pg_mi.c:4103 */
#define   EEG217      (ERREG +  217)    /*      pg_mi.c:4110 */
#define   EEG218      (ERREG +  218)    /*      pg_mi.c:4143 */
#define   EEG219      (ERREG +  219)    /*      pg_mi.c:4322 */
#define   EEG220      (ERREG +  220)    /*      pg_mi.c:4377 */
#define   EEG221      (ERREG +  221)    /*      pg_mi.c:4400 */
#define   EEG222      (ERREG +  222)    /*      pg_mi.c:4479 */
#define   EEG223      (ERREG +  223)    /*      pg_mi.c:4548 */
#define   EEG224      (ERREG +  224)    /*      pg_mi.c:4555 */
#define   EEG225      (ERREG +  225)    /*      pg_mi.c:4622 */
#define   EEG226      (ERREG +  226)    /*      pg_mi.c:4630 */
#define   EEG227      (ERREG +  227)    /*      pg_mi.c:4637 */
#define   EEG228      (ERREG +  228)    /*      pg_mi.c:4644 */
#define   EEG229      (ERREG +  229)    /*      pg_mi.c:4695 */
#define   EEG230      (ERREG +  230)    /*      pg_mi.c:4704 */
#define   EEG231      (ERREG +  231)    /*      pg_mi.c:4754 */
#define   EEG232      (ERREG +  232)    /*      pg_mi.c:4804 */
#define   EEG233      (ERREG +  233)    /*      pg_mi.c:4875 */
#define   EEG234      (ERREG +  234)    /*      pg_mi.c:4895 */
#define   EEG235      (ERREG +  235)    /*      pg_mi.c:4984 */
#define   EEG236      (ERREG +  236)    /*      pg_mi.c:5154 */
#define   EEG237      (ERREG +  237)    /*      pg_mi.c:5163 */
#define   EEG238      (ERREG +  238)    /*      pg_mi.c:5225 */
#define   EEG239      (ERREG +  239)    /*      pg_mi.c:5232 */
#define   EEG240      (ERREG +  240)    /*      pg_mi.c:5240 */
#define   EEG241      (ERREG +  241)    /*      pg_mi.c:5563 */
#define   EEG242      (ERREG +  242)    /*      pg_mi.c:5725 */
#define   EEG243      (ERREG +  243)    /*      pg_mi.c:6265 */
#define   EEG244      (ERREG +  244)    /*      pg_mi.c:6270 */
#define   EEG245      (ERREG +  245)    /*      pg_mi.c:6395 */
#define   EEG246      (ERREG +  246)    /*      pg_mi.c:6416 */
#define   EEG247      (ERREG +  247)    /*      pg_mi.c:6448 */
#define   EEG248      (ERREG +  248)    /*      pg_mi.c:6483 */
#define   EEG249      (ERREG +  249)    /*      pg_mi.c:6518 */
#define   EEG250      (ERREG +  250)    /*      pg_mi.c:6599 */
#define   EEG251      (ERREG +  251)    /*      pg_mi.c:6654 */
#define   EEG252      (ERREG +  252)    /*      pg_mi.c:6675 */
#define   EEG253      (ERREG +  253)    /*      pg_mi.c:6739 */
#define   EEG254      (ERREG +  254)    /*      pg_mi.c:6751 */
#define   EEG255      (ERREG +  255)    /*      pg_mi.c:6818 */
#define   EEG256      (ERREG +  256)    /*      pg_mi.c:6829 */
#define   EEG257      (ERREG +  257)    /*      pg_mi.c:6842 */
#define   EEG258      (ERREG +  258)    /*      pg_mi.c:6910 */
#define   EEG259      (ERREG +  259)    /*      pg_mi.c:6920 */
#define   EEG260      (ERREG +  260)    /*      pg_mi.c:6940 */
#define   EEG261      (ERREG +  261)    /*      pg_mi.c:6957 */
#define   EEG262      (ERREG +  262)    /*      pg_mi.c:6973 */
#define   EEG263      (ERREG +  263)    /*      pg_mi.c:7034 */
#define   EEG264      (ERREG +  264)    /*      pg_mi.c:7041 */
#define   EEG265      (ERREG +  265)    /*      pg_mi.c:7048 */
#define   EEG266      (ERREG +  266)    /*      pg_mi.c:7055 */
#define   EEG267      (ERREG +  267)    /*      pg_mi.c:7125 */
#define   EEG268      (ERREG +  268)    /*      pg_mi.c:7133 */
#define   EEG269      (ERREG +  269)    /*      pg_mi.c:7146 */
#define   EEG270      (ERREG +  270)    /*      pg_mi.c:7225 */
#define   EEG271      (ERREG +  271)    /*      pg_mi.c:7233 */
#define   EEG272      (ERREG +  272)    /*      pg_mi.c:7242 */
#define   EEG273      (ERREG +  273)    /*      pg_mi.c:7249 */
#define   EEG274      (ERREG +  274)    /*      pg_mi.c:7298 */
#define   EEG275      (ERREG +  275)    /*      pg_mi.c:7310 */
#define   EEG276      (ERREG +  276)    /*      pg_mi.c:7319 */
#define   EEG277      (ERREG +  277)    /*      pg_mi.c:7381 */
#define   EEG278      (ERREG +  278)    /*      pg_mi.c:7393 */
#define   EEG279      (ERREG +  279)    /*      pg_mi.c:7411 */
#define   EEG280      (ERREG +  280)    /*      pg_mi.c:7484 */
#define   EEG281      (ERREG +  281)    /*      pg_mi.c:7624 */
#define   EEG282      (ERREG +  282)    /*      pg_mi.c:7652 */
#define   EEG283      (ERREG +  283)    /*      pg_mi.c:7680 */
#define   EEG284      (ERREG +  284)    /*      pg_mi.c:7705 */
#define   EEG285      (ERREG +  285)    /*      pg_mi.c:7726 */
#define   EEG286      (ERREG +  286)    /*      pg_mi.c:7802 */
#define   EEG287      (ERREG +  287)    /*      pg_mi.c:7861 */
#define   EEG288      (ERREG +  288)    /*      pg_mi.c:8021 */
#define   EEG289      (ERREG +  289)    /*      pg_mi.c:8037 */
#define   EEG290      (ERREG +  290)    /*      pg_mi.c:8077 */
#define   EEG291      (ERREG +  291)    /*      pg_mi.c:8091 */
#define   EEG292      (ERREG +  292)    /*      pg_mi.c:8106 */
#define   EEG293      (ERREG +  293)    /*      pg_mi.c:8149 */
#define   EEG294      (ERREG +  294)    /*      pg_mi.c:8196 */
#define   EEG295      (ERREG +  295)    /*      pg_mi.c:8250 */
#define   EEG296      (ERREG +  296)    /*      pg_mi.c:8256 */
#define   EEG297      (ERREG +  297)    /*      pg_mi.c:8311 */
#define   EEG298      (ERREG +  298)    /*      pg_mi.c:8326 */
#define   EEG299      (ERREG +  299)    /*      pg_mi.c:8344 */
#define   EEG300      (ERREG +  300)    /*      pg_mi.c:8367 */
#define   EEG301      (ERREG +  301)    /*      pg_mi.c:8400 */
#define   EEG302      (ERREG +  302)    /*      pg_mi.c:8453 */
#define   EEG303      (ERREG +  303)    /*      pg_mi.c:8501 */
#define   EEG304      (ERREG +  304)    /*      pg_mi.c:8523 */
#define   EEG305      (ERREG +  305)    /*      pg_mi.c:8558 */
#define   EEG306      (ERREG +  306)    /*      pg_mi.c:8605 */
#define   EEG307      (ERREG +  307)    /*      pg_mi.c:8614 */
#define   EEG308      (ERREG +  308)    /*      pg_mi.c:8623 */
#define   EEG309      (ERREG +  309)    /*      pg_mi.c:8706 */
#define   EEG310      (ERREG +  310)    /*      pg_mi.c:8768 */
#define   EEG311      (ERREG +  311)    /*      pg_mi.c:8779 */
#define   EEG312      (ERREG +  312)    /*      pg_mi.c:8811 */
#define   EEG313      (ERREG +  313)    /*      pg_mi.c:8818 */
#define   EEG314      (ERREG +  314)    /*      pg_mi.c:8904 */
#define   EEG315      (ERREG +  315)    /*      pg_mi.c:8995 */
#define   EEG316      (ERREG +  316)    /*      pg_mi.c:9014 */
#define   EEG317      (ERREG +  317)    /*      pg_mi.c:9039 */
#define   EEG318      (ERREG +  318)    /*      pg_mi.c:9056 */
#define   EEG319      (ERREG +  319)    /*      pg_mi.c:9128 */
#define   EEG320      (ERREG +  320)    /*      pg_mi.c:9145 */
#define   EEG321      (ERREG +  321)    /*      pg_mi.c:9164 */
#define   EEG322      (ERREG +  322)    /*      pg_mi.c:9256 */
#define   EEG323      (ERREG +  323)    /*      pg_mi.c:9283 */
#define   EEG324      (ERREG +  324)    /*      pg_mi.c:9386 */

#define   EEG325      (ERREG +  325)    /*     pg_tmr.c: 193 */
#define   EEG326      (ERREG +  326)    /*     pg_tmr.c: 270 */
#define   EEG327      (ERREG +  327)    /*     pg_tmr.c: 321 */
#define   EEG328      (ERREG +  328)    /*     pg_tmr.c: 332 */
#define   EEG329      (ERREG +  329)    /*     pg_tmr.c: 390 */
#define   EEG330      (ERREG +  330)    /*     pg_tmr.c: 399 */
#define   EEG331      (ERREG +  331)    /*     pg_tmr.c:1166 */

#define   EEG332      (ERREG +  332)    /*      pg_ui.c: 239 */
#define   EEG333      (ERREG +  333)    /*      pg_ui.c: 260 */
#define   EEG334      (ERREG +  334)    /*      pg_ui.c: 381 */
#define   EEG335      (ERREG +  335)    /*      pg_ui.c: 408 */
#define   EEG336      (ERREG +  336)    /*      pg_ui.c: 443 */
#define   EEG337      (ERREG +  337)    /*      pg_ui.c: 460 */
#define   EEG338      (ERREG +  338)    /*      pg_ui.c: 498 */
#define   EEG339      (ERREG +  339)    /*      pg_ui.c: 609 */
#define   EEG340      (ERREG +  340)    /*      pg_ui.c: 631 */
#define   EEG341      (ERREG +  341)    /*      pg_ui.c: 657 */
#define   EEG342      (ERREG +  342)    /*      pg_ui.c: 684 */
#define   EEG343      (ERREG +  343)    /*      pg_ui.c: 731 */
#define   EEG344      (ERREG +  344)    /*      pg_ui.c: 759 */
#define   EEG345      (ERREG +  345)    /*      pg_ui.c: 773 */
#define   EEG346      (ERREG +  346)    /*      pg_ui.c: 798 */
#define   EEG347      (ERREG +  347)    /*      pg_ui.c: 871 */
#define   EEG348      (ERREG +  348)    /*      pg_ui.c: 894 */
#define   EEG349      (ERREG +  349)    /*      pg_ui.c: 920 */
#define   EEG350      (ERREG +  350)    /*      pg_ui.c: 933 */
#define   EEG351      (ERREG +  351)    /*      pg_ui.c: 961 */
#define   EEG352      (ERREG +  352)    /*      pg_ui.c:1029 */
#define   EEG353      (ERREG +  353)    /*      pg_ui.c:1050 */
#define   EEG354      (ERREG +  354)    /*      pg_ui.c:1075 */
#define   EEG355      (ERREG +  355)    /*      pg_ui.c:1085 */
#define   EEG356      (ERREG +  356)    /*      pg_ui.c:1156 */
#define   EEG357      (ERREG +  357)    /*      pg_ui.c:1177 */
#define   EEG358      (ERREG +  358)    /*      pg_ui.c:1197 */
#define   EEG359      (ERREG +  359)    /*      pg_ui.c:1364 */
#define   EEG360      (ERREG +  360)    /*      pg_ui.c:1391 */
#define   EEG361      (ERREG +  361)    /*      pg_ui.c:1419 */
#define   EEG362      (ERREG +  362)    /*      pg_ui.c:1516 */
#define   EEG363      (ERREG +  363)    /*      pg_ui.c:1537 */
#define   EEG364      (ERREG +  364)    /*      pg_ui.c:1562 */
#define   EEG365      (ERREG +  365)    /*      pg_ui.c:1642 */
#define   EEG366      (ERREG +  366)    /*      pg_ui.c:1663 */
#define   EEG367      (ERREG +  367)    /*      pg_ui.c:1740 */

#endif /* end of _EGTH_ */

/********************************************************************30**

         End of file:     eg_err.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:44 2015

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
/main/1      ---      ad                1. Created for Initial Release 1.1
/main/2      ---      rkumar            1. Initial for eGTP 1.2 Release

/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
*********************************************************************91*/
