
/**********************************************************************
     Name:    Lower layer interface - TFU

     Type:    C header file

     Desc:    Constants needed for TFU interface

     File:    tfu.h

     Sid:      tfu.h@@/main/8 - Wed Jul 27 12:10:24 2011

     Prg:      

*********************************************************************21*/

/**
  @file tfu.h
  @brief Defines for TFU interface.
  */

#ifndef __TFU_H__
#define __TFU_H__

/* Define for the block size for memory allocation */
/** @name TFU_TDD */
/** @{ */
#define TFU_MAX_HQ_RES        4     /*!< n^1 Pucch resources for
                                                    HARQ feedback */

#ifdef TFU_TDD
#define TFU_BLKSZ                 2048  /*!< Block size for memory allocations. */
#else
/* tfu_h_001.main_3  Changing from 4096 to 1500 to align with max bucket-max 
 * packet sizes - optimization*/
#define TFU_BLKSZ                 1500  /*!< Block size for memory allocations. */
#endif
/* tfu_h_001.main_6. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
#define TFU_MAX_UL_RB             110   /*!< Maximum number of RBs in UL */
#define TFU_MAX_CQI_BYTES         9     /*!< Maximum number of CQI Bytes length */
#define TFU_MAX_PHY_ANTENNA       4     /*!<  Maximum number of Physical Antennas */
#endif /* TFU_UPGRADE */

#define TFU_MAX_RAPID_IN_SUBFRAME 64    /*!< Maximum number of Random access preambes in a subframe. */
#define TFU_MAX_UL_SUBBAND        110   /*!< Maxiumum number of Uplink Subbands.*/
#define TFU_MAX_DL_SUBBAND        110   /*!< Maxiumum number of Downlink Subbands.*/
#define TFU_MAX_TB                2    /*!< Maximum number of Transport blocks per UE. */
#ifdef L2_OPTMZ
#define TFU_MAX_PDU               4    /*!< This No is mapped to RGU_MAX_PDU*/
#define TFU_MAX_LC                10    /*!< This No is mapped to RGU_MAX_LC*/
#endif
#define TFU_MAX_M                 4    /*!< Maximum value of "M" for HARQ Feedback multiplexing. */
#define TFU_MAX_2BIT_TPC          16   /*!< Maximum number of 2 bit TPC commands. */
#define TFU_MAX_1BIT_TPC          32   /*!< Maximum number of 1 bit TPC commands. */
/*tfu_h_001.main_5 - Added support for SPS*/
/* Tunable parameter */
#define TFU_MAX_MEMBLK_SIZE       1500 /* tfu_h_001.main_3 Changing from 2048 to 1500 
                                          for alignment and optimization */

#define TFU_UBNDREQ_MNGMT         1    /*!< TFU sap unbind reason */

#ifdef LTE_ADV
#define TFU_MAX_HARQ_FDBKS       20 /*For Rel10 UE
                                     Considering 10 bit requirement of PUCCH Format 3*/
#else
#define TFU_MAX_HARQ_FDBKS       TFU_MAX_TB /*For Rel8/Rel9 UE*/
#endif/*LTE_ADV*/

/* Event corresponding to each primitive at this interface */
#define EVTTFUBNDREQ            1     /*!< Bind Request */
#define EVTTFUBNDCFM            2     /*!< Bind Confirm */
#define EVTTFUUBNDREQ           3     /*!< Unbind Request */
#define EVTTFUSCHBNDREQ         4     /*!< Bind Request */
#define EVTTFUSCHBNDCFM         5     /*!< Bind Confirm */
#define EVTTFUSCHUBNDREQ        6     /*!< Unbind Request */
#define EVTTFURAREQIND          7     /*!< Random access request indication. */
#define EVTTFURECPREQ           8     /*!< Reception Request. */
#define EVTTFUULCQIIND          9     /*!< Uplink CQI indication.*/
#define EVTTFUHQIND             10    /*!< HARQ Feedback indication. */
#define EVTTFUDLCQIIND          11    /*!< Downlink CQI indication. */
#define EVTTFUSRIND             12    /*!< Scheduling Request indication.*/
#define EVTTFUDATIND            13    /*!< Data indication.*/
#define EVTTFUCRCIND            14    /*!< CRC indication. */
#define EVTTFUTIMINGADVIND      15    /*!< Timing advance indication.*/
#define EVTTFUDATREQ            16    /*!< Data Request.*/
#define EVTTFUTTIIND            17    /*!< TTI indication.*/
#define EVTTFUSCHTTIIND         18    /*!< TTI indication for scheduler.*/
#define EVTTFUCNTRLREQ          19    /*!< Control Request.*/
#define EVTTFUPUCCHDELPWR       20    /*!< PUCCH Delta power. */
#define EVTTFUDOAIND            21    /*!< PUCCH Delta power. */
/* tfu_h_001.main_6. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
#define EVTTFURAWCQIIND         22
#define EVTTFUSRSIND            23
#endif
#if defined(TENB_T2K3K_SPECIFIC_CHANGES) && defined(LTE_TDD)
#define EVTTFUNONRTIND          24    /*!< Non-RT indication.*/
#endif
#define EVTTFUERRIND            25    /*!< TFU Error Indication */
/** @} */

#define EVTTFUREADL1DATA        26
#define EVTTFUENCODEL1DATA 	27

/* selector(coupling) values */
#define TFU_SEL_TC              1    /*!< Selector for Tight coupling. */
#define TFU_SEL_LC              0    /*!< Selector for Loose coupling. */
#define TFU_SEL_LWLC            2    /*!< Selector for Light-weight loose coupling. */
#define TFU_MAX_ALLOC_BYTES     4
/* pack unpack error code */
#define ETFUXXX                 0
#define ERRTFU                  0
/* tfu_h_001.main_2 - ccpu00110457 DTX Changes Start */
#define TFU_HQFDB_NACK          FALSE
#define TFU_HQFDB_ACK           TRUE
/* tfu_h_001.main_6. Added changes of TFU_UPGRADE */
#define TFU_HQFDB_DTX           4
#define TFU_HQFDB_INVALID       0xFF

/*tfu_h_001.main_7 - DEL - ERR Codes*/
#define   ETFU001      (ERRTFU +    1)    /*        tfu.c: 162 */
#define   ETFU002      (ERRTFU +    2)    /*        tfu.c: 170 */
#define   ETFU003      (ERRTFU +    3)    /*        tfu.c: 179 */
#define   ETFU004      (ERRTFU +    4)    /*        tfu.c: 232 */
#define   ETFU005      (ERRTFU +    5)    /*        tfu.c: 241 */
#define   ETFU006      (ERRTFU +    6)    /*        tfu.c: 290 */
#define   ETFU007      (ERRTFU +    7)    /*        tfu.c: 298 */
#define   ETFU008      (ERRTFU +    8)    /*        tfu.c: 307 */
#define   ETFU009      (ERRTFU +    9)    /*        tfu.c: 360 */
#define   ETFU010      (ERRTFU +   10)    /*        tfu.c: 369 */
#define   ETFU011      (ERRTFU +   11)    /*        tfu.c: 418 */
#define   ETFU012      (ERRTFU +   12)    /*        tfu.c: 426 */
#define   ETFU013      (ERRTFU +   13)    /*        tfu.c: 435 */
#define   ETFU014      (ERRTFU +   14)    /*        tfu.c: 488 */
#define   ETFU015      (ERRTFU +   15)    /*        tfu.c: 497 */
#define   ETFU016      (ERRTFU +   16)    /*        tfu.c: 546 */
#define   ETFU017      (ERRTFU +   17)    /*        tfu.c: 554 */
#define   ETFU018      (ERRTFU +   18)    /*        tfu.c: 563 */
#define   ETFU019      (ERRTFU +   19)    /*        tfu.c: 616 */
#define   ETFU020      (ERRTFU +   20)    /*        tfu.c: 625 */
#define   ETFU021      (ERRTFU +   21)    /*        tfu.c: 674 */
#define   ETFU022      (ERRTFU +   22)    /*        tfu.c: 682 */
#define   ETFU023      (ERRTFU +   23)    /*        tfu.c: 691 */
#define   ETFU024      (ERRTFU +   24)    /*        tfu.c: 744 */
#define   ETFU025      (ERRTFU +   25)    /*        tfu.c: 753 */
#define   ETFU026      (ERRTFU +   26)    /*        tfu.c: 802 */
#define   ETFU027      (ERRTFU +   27)    /*        tfu.c: 810 */
#define   ETFU028      (ERRTFU +   28)    /*        tfu.c: 819 */
#define   ETFU029      (ERRTFU +   29)    /*        tfu.c: 872 */
#define   ETFU030      (ERRTFU +   30)    /*        tfu.c: 881 */
#define   ETFU031      (ERRTFU +   31)    /*        tfu.c: 934 */
#define   ETFU032      (ERRTFU +   32)    /*        tfu.c: 944 */
#define   ETFU033      (ERRTFU +   33)    /*        tfu.c: 956 */
#define   ETFU034      (ERRTFU +   34)    /*        tfu.c:1018 */
#define   ETFU035      (ERRTFU +   35)    /*        tfu.c:1030 */
#define   ETFU036      (ERRTFU +   36)    /*        tfu.c:1045 */
#define   ETFU037      (ERRTFU +   37)    /*        tfu.c:1108 */
#define   ETFU038      (ERRTFU +   38)    /*        tfu.c:1118 */
#define   ETFU039      (ERRTFU +   39)    /*        tfu.c:1130 */
#define   ETFU040      (ERRTFU +   40)    /*        tfu.c:1202 */
#define   ETFU041      (ERRTFU +   41)    /*        tfu.c:1214 */
#define   ETFU042      (ERRTFU +   42)    /*        tfu.c:1229 */
#define   ETFU043      (ERRTFU +   43)    /*        tfu.c:1283 */
#define   ETFU044      (ERRTFU +   44)    /*        tfu.c:1293 */
#define   ETFU045      (ERRTFU +   45)    /*        tfu.c:1305 */
#define   ETFU046      (ERRTFU +   46)    /*        tfu.c:1368 */
#define   ETFU047      (ERRTFU +   47)    /*        tfu.c:1380 */
#define   ETFU048      (ERRTFU +   48)    /*        tfu.c:1396 */
#define   ETFU049      (ERRTFU +   49)    /*        tfu.c:1450 */
#define   ETFU050      (ERRTFU +   50)    /*        tfu.c:1460 */
#define   ETFU051      (ERRTFU +   51)    /*        tfu.c:1472 */
#define   ETFU052      (ERRTFU +   52)    /*        tfu.c:1534 */
#define   ETFU053      (ERRTFU +   53)    /*        tfu.c:1546 */
#define   ETFU054      (ERRTFU +   54)    /*        tfu.c:1562 */
#define   ETFU055      (ERRTFU +   55)    /*        tfu.c:1615 */
#define   ETFU056      (ERRTFU +   56)    /*        tfu.c:1625 */
#define   ETFU057      (ERRTFU +   57)    /*        tfu.c:1637 */
#define   ETFU058      (ERRTFU +   58)    /*        tfu.c:1698 */
#define   ETFU059      (ERRTFU +   59)    /*        tfu.c:1710 */
#define   ETFU060      (ERRTFU +   60)    /*        tfu.c:1726 */
#define   ETFU061      (ERRTFU +   61)    /*        tfu.c:1777 */
#define   ETFU062      (ERRTFU +   62)    /*        tfu.c:1787 */
#define   ETFU063      (ERRTFU +   63)    /*        tfu.c:1799 */
#define   ETFU064      (ERRTFU +   64)    /*        tfu.c:1857 */
#define   ETFU065      (ERRTFU +   65)    /*        tfu.c:1869 */
#define   ETFU066      (ERRTFU +   66)    /*        tfu.c:1885 */
#define   ETFU067      (ERRTFU +   67)    /*        tfu.c:1944 */
#define   ETFU068      (ERRTFU +   68)    /*        tfu.c:1954 */
#define   ETFU069      (ERRTFU +   69)    /*        tfu.c:2014 */
#define   ETFU070      (ERRTFU +   70)    /*        tfu.c:2026 */
#define   ETFU071      (ERRTFU +   71)    /*        tfu.c:2082 */
#define   ETFU072      (ERRTFU +   72)    /*        tfu.c:2092 */
#define   ETFU073      (ERRTFU +   73)    /*        tfu.c:2151 */
#define   ETFU074      (ERRTFU +   74)    /*        tfu.c:2163 */
#define   ETFU075      (ERRTFU +   75)    /*        tfu.c:2221 */
#define   ETFU076      (ERRTFU +   76)    /*        tfu.c:2231 */
#define   ETFU077      (ERRTFU +   77)    /*        tfu.c:2243 */
#define   ETFU078      (ERRTFU +   78)    /*        tfu.c:2304 */
#define   ETFU079      (ERRTFU +   79)    /*        tfu.c:2316 */
#define   ETFU080      (ERRTFU +   80)    /*        tfu.c:2332 */
#define   ETFU081      (ERRTFU +   81)    /*        tfu.c:2389 */
#define   ETFU082      (ERRTFU +   82)    /*        tfu.c:2399 */
#define   ETFU083      (ERRTFU +   83)    /*        tfu.c:2411 */
#define   ETFU084      (ERRTFU +   84)    /*        tfu.c:2476 */
#define   ETFU085      (ERRTFU +   85)    /*        tfu.c:2488 */
#define   ETFU086      (ERRTFU +   86)    /*        tfu.c:2504 */
#define   ETFU087      (ERRTFU +   87)    /*        tfu.c:2558 */
#define   ETFU088      (ERRTFU +   88)    /*        tfu.c:2568 */
#define   ETFU089      (ERRTFU +   89)    /*        tfu.c:2580 */
#define   ETFU090      (ERRTFU +   90)    /*        tfu.c:2642 */
#define   ETFU091      (ERRTFU +   91)    /*        tfu.c:2654 */
#define   ETFU092      (ERRTFU +   92)    /*        tfu.c:2670 */
#define   ETFU093      (ERRTFU +   93)    /*        tfu.c:2726 */
#define   ETFU094      (ERRTFU +   94)    /*        tfu.c:2736 */
#define   ETFU095      (ERRTFU +   95)    /*        tfu.c:2748 */
#define   ETFU096      (ERRTFU +   96)    /*        tfu.c:2812 */
#define   ETFU097      (ERRTFU +   97)    /*        tfu.c:2824 */
#define   ETFU098      (ERRTFU +   98)    /*        tfu.c:2840 */
#define   ETFU099      (ERRTFU +   99)    /*        tfu.c:2897 */
#define   ETFU100      (ERRTFU +  100)    /*        tfu.c:2907 */
#define   ETFU101      (ERRTFU +  101)    /*        tfu.c:2919 */
#define   ETFU102      (ERRTFU +  102)    /*        tfu.c:2984 */
#define   ETFU103      (ERRTFU +  103)    /*        tfu.c:2996 */
#define   ETFU104      (ERRTFU +  104)    /*        tfu.c:3012 */
#define   ETFU105      (ERRTFU +  105)    /*        tfu.c:3065 */
#define   ETFU106      (ERRTFU +  106)    /*        tfu.c:3075 */
#define   ETFU107      (ERRTFU +  107)    /*        tfu.c:3087 */
#define   ETFU108      (ERRTFU +  108)    /*        tfu.c:3098 */
#define   ETFU109      (ERRTFU +  109)    /*        tfu.c:3155 */
#define   ETFU110      (ERRTFU +  110)    /*        tfu.c:3164 */
#define   ETFU111      (ERRTFU +  111)    /*        tfu.c:3179 */
#define   ETFU112      (ERRTFU +  112)    /*        tfu.c:3231 */
#define   ETFU113      (ERRTFU +  113)    /*        tfu.c:3241 */
#define   ETFU114      (ERRTFU +  114)    /*        tfu.c:3253 */
#define   ETFU115      (ERRTFU +  115)    /*        tfu.c:3264 */
#define   ETFU116      (ERRTFU +  116)    /*        tfu.c:3320 */
#define   ETFU117      (ERRTFU +  117)    /*        tfu.c:3329 */
#define   ETFU118      (ERRTFU +  118)    /*        tfu.c:3344 */
#define   ETFU119      (ERRTFU +  119)    /*        tfu.c:3396 */
#define   ETFU120      (ERRTFU +  120)    /*        tfu.c:3406 */
#define   ETFU121      (ERRTFU +  121)    /*        tfu.c:3418 */
#define   ETFU122      (ERRTFU +  122)    /*        tfu.c:3477 */
#define   ETFU123      (ERRTFU +  123)    /*        tfu.c:3489 */
#define   ETFU124      (ERRTFU +  124)    /*        tfu.c:3504 */
#define   ETFU125      (ERRTFU +  125)    /*        tfu.c:10783 */
#define   ETFU126      (ERRTFU +  126)    /*        tfu.c:10793 */
#define   ETFU127      (ERRTFU +  127)    /*        tfu.c:10850 */
#define   ETFU128      (ERRTFU +  128)    /*        tfu.c:10862 */

#define TFU_PERIODIC_CQI_TYPE  0
#define TFU_APERIODIC_CQI_TYPE 1

#define TFU_FREE_MSG(_buf)\
{\
   if (NULLP != (_buf)) \
   { \
      SPutMsg((_buf)); \
      _buf = NULLP; \
   } \
}

#define TFU_FREE_MEM(_mem)\
{\
   if (NULLP != (_mem)) \
   { \
      cmFreeMem((_mem)); \
      _mem = NULLP; \
   } \
}


#endif /* __TFU_H__ */

/********************************************************************30**

         End of file:     tfu.h@@/main/8 - Wed Jul 27 12:10:24 2011

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
/main/1      ---   apany 1. Initial release.
/main/2      ---   apany 1. LTE MAC 2.1 release
/main/3      ---        tfu_h_001.main_2   ms    1. DL DTX Handling
/main/4      ---        tfu_h_001.main_3   sm    1. Changing from 2048 to 1500 
/main/5      ---        tfu_h_001.main_4   ap    1. Added support for MIMO
/main/6      ---        tfu_h_001.main_5 rsharon    1. Added support for SPS.
/main/7      ---        tfu_h_001.main_6   dv    1. Added support for TFU
                                                    Upgrade.
/main/8      ---        tfu_h_001.main_7   gj    1. LTE MAC 3.1 Release.        *********************************************************************91*/
