
/**********************************************************************
     Name:    Upper Layer Interface - RLC

     Type:    C header file

     Desc:    Structures, variables and typedefs required by 
              RGU interface

     File:    rgu.h

     Sid:      rgu.h@@/main/6 - Wed Jul 27 14:03:29 2011

     Prg:      

*********************************************************************21*/


#ifndef __RGUH__
#define __RGUH__
#ifdef __cplusplus
extern "C" {
#endif

/** 
  @file rgu.h 
  @brief Defines for RGU interface.
 */


/***********************************************************************
                         Macro Definitions 
 ***********************************************************************/
#ifdef LTE_L2_MEAS
#define RGU_INVALID_TBID    64    /*!< Invalid TBID that is set by RLC for DL TPT 
                                Calculations in Dat Req to MAC. */
#endif
/* rgu_h_001.main_3   Changing from 10 to 5 for optimization */
#define RGU_MAX_PDU    4    /*!< Maximum number of PDUs that can be received in a datreq. */
#define RGU_RESID_SIZE 6     /*!< Size of Contention resolution ID in bytes.*/
/*  rgu_h_001.main_4 - Adding RGU_MAX_TB*/
#define RGU_MAX_TB     2     /*!< Maximum of 2 TB's per DDat Req */

/* rgu_h_001.main_3  Changing from 20 to 10 for optimization */
#define RGU_MAX_LC     10    /*!< Maximum Number of dedicated Logical Channels.*/

/* Event corresponding to each primitive at this interface */
#define EVTRGUBNDREQ   1     /*!< Bind Request */
#define EVTRGUUBNDREQ  2     /*!< Un-Bind Request */
#define EVTRGUBNDCFM   3     /*!< Bind Confirm */
#define EVTRGUCDATREQ  4     /*!< Common Channel Data Request */
#define EVTRGUCDATIND  5     /*!< Common Channel Data Indication */
#define EVTRGUDDATREQ  6     /*!< Dedicated Channel Data Request */
#define EVTRGUDDATIND  7     /*!< Dedicated Channel Data Indication */
#define EVTRGUCSTARSP  8     /*!< Common Channel status response */
#define EVTRGUCSTAIND  9     /*!< Common Channel status Indication */
#define EVTRGUDSTARSP  10    /*!< Dedicated Channel status response */
#define EVTRGUDSTAIND  11    /*!< Dedicated Channel status Indication */
   /*rgu_h_001.main_5 - ADD - L2M Support */
#ifdef LTE_L2_MEAS
#define EVTRGUHQSTAIND  12    /*!< HARQ status Indication */
#define EVTRGUL2MULTHRPMEASREQ  13    /*!< L2M LCID On/Off Status Response */
#define 	RGU_L2M_UL_BURST_START 0  /*!< Data Burst Start in Uplink DTCH */
#define 	RGU_L2M_UL_BURST_END   1  /*!< Data Burst End in Uplink DTCH */
#endif
#define   EVTRGUFLOWCNTRLIND    14
/* If you change the value of below macro then you have to change value of 
 * RG_MAX_NUM_UE_PER_TTI in file rg_env.h */  
#define RGU_MAX_NUM_UE_PER_TTI  8  /*!< Max UEs Per Tti */ 
/* selector(coupling) values */
#define RGU_SEL_TC              1
#define RGU_SEL_LC              0
#define RGU_SEL_LWLC            2

/* pack unpack error code */
#define ERGUXXX                 0
#define ERRRGU                  0

#define   ERGU001      (ERRRGU +    1)    /*        rgu.c: 155 */
#define   ERGU002      (ERRRGU +    2)    /*        rgu.c: 163 */
#define   ERGU003      (ERRRGU +    3)    /*        rgu.c: 172 */
#define   ERGU004      (ERRRGU +    4)    /*        rgu.c: 218 */
#define   ERGU005      (ERRRGU +    5)    /*        rgu.c: 227 */
#define   ERGU006      (ERRRGU +    6)    /*        rgu.c: 271 */
#define   ERGU007      (ERRRGU +    7)    /*        rgu.c: 279 */
#define   ERGU008      (ERRRGU +    8)    /*        rgu.c: 288 */
#define   ERGU009      (ERRRGU +    9)    /*        rgu.c: 334 */
#define   ERGU010      (ERRRGU +   10)    /*        rgu.c: 343 */
#define   ERGU011      (ERRRGU +   11)    /*        rgu.c: 388 */
#define   ERGU012      (ERRRGU +   12)    /*        rgu.c: 396 */
#define   ERGU013      (ERRRGU +   13)    /*        rgu.c: 405 */
#define   ERGU014      (ERRRGU +   14)    /*        rgu.c: 452 */
#define   ERGU015      (ERRRGU +   15)    /*        rgu.c: 461 */
#define   ERGU016      (ERRRGU +   16)    /*        rgu.c: 506 */
#define   ERGU017      (ERRRGU +   17)    /*        rgu.c: 515 */
#define   ERGU018      (ERRRGU +   18)    /*        rgu.c: 525 */
#define   ERGU019      (ERRRGU +   19)    /*        rgu.c: 535 */
#define   ERGU020      (ERRRGU +   20)    /*        rgu.c: 582 */
#define   ERGU021      (ERRRGU +   21)    /*        rgu.c: 596 */
#define   ERGU022      (ERRRGU +   22)    /*        rgu.c: 642 */
/*rgu_h_001.main_5 - ADD - L2M Support */
#define   ERGU023      (ERRRGU +   23)    /*        rgu.c: 656 */
#define   ERGU024      (ERRRGU +   24)    /*        rgu.c: 666 */
#define   ERGU025      (ERRRGU +   25)    /*        rgu.c: 676 */
#define   ERGU026      (ERRRGU +   26)    /*        rgu.c: 723 */
#define   ERGU027      (ERRRGU +   27)    /*        rgu.c: 742 */
#define   ERGU028      (ERRRGU +   28)    /*        rgu.c: 788 */
#define   ERGU029      (ERRRGU +   29)    /*        rgu.c: 797 */
#define   ERGU030      (ERRRGU +   30)    /*        rgu.c: 807 */
#define   ERGU031      (ERRRGU +   31)    /*        rgu.c: 817 */
#define   ERGU032      (ERRRGU +   32)    /*        rgu.c: 864 */
#define   ERGU033      (ERRRGU +   33)    /*        rgu.c: 873 */
#define   ERGU034      (ERRRGU +   34)    /*        rgu.c: 882 */
#define   ERGU035      (ERRRGU +   35)    /*        rgu.c: 928 */
#define   ERGU036      (ERRRGU +   36)    /*        rgu.c: 937 */
#define   ERGU037      (ERRRGU +   37)    /*        rgu.c: 947 */
#define   ERGU038      (ERRRGU +   38)    /*        rgu.c: 957 */
#define   ERGU039      (ERRRGU +   39)    /*        rgu.c:1004 */
#define   ERGU040      (ERRRGU +   40)    /*        rgu.c:1013 */
#define   ERGU041      (ERRRGU +   41)    /*        rgu.c:1022 */
#define   ERGU042      (ERRRGU +   42)    /*        rgu.c:1068 */
#define   ERGU043      (ERRRGU +   43)    /*        rgu.c:1077 */
#define   ERGU044      (ERRRGU +   44)    /*        rgu.c:1087 */
#define   ERGU045      (ERRRGU +   45)    /*        rgu.c:1097 */
#define   ERGU046      (ERRRGU +   46)    /*        rgu.c:1144 */
#define   ERGU047      (ERRRGU +   47)    /*        rgu.c:1153 */
#define   ERGU048      (ERRRGU +   48)    /*        rgu.c:1162 */
#define   ERGU049      (ERRRGU +   49)    /*        rgu.c:1372 */
#define   ERGU050      (ERRRGU +   50)    /*        rgu.c:1381 */
#define   ERGU051      (ERRRGU +   51)    /*        rgu.c:1391 */
#define   ERGU052      (ERRRGU +   52)    /*        rgu.c:1401 */
#define   ERGU053      (ERRRGU +   53)    /*        rgu.c:1449 */
#define   ERGU054      (ERRRGU +   54)    /*        rgu.c:1458 */
#define   ERGU055      (ERRRGU +   55)    /*        rgu.c:1467 */
#define   ERGU056      (ERRRGU +   56)    /*        rgu.c:1517 */
#define   ERGU057      (ERRRGU +   57)    /*        rgu.c:1526 */
#define   ERGU058      (ERRRGU +   58)    /*        rgu.c:1536 */
#define   ERGU059      (ERRRGU +   59)    /*        rgu.c:1546 */
#define   ERGU060      (ERRRGU +   60)    /*        rgu.c:1593 */
#define   ERGU061      (ERRRGU +   61)    /*        rgu.c:1602 */
#define   ERGU062      (ERRRGU +   62)    /*        rgu.c:1611 */
#define   ERGU063      (ERRRGU +   63)    /*        rgu.c:1659 */
#define   ERGU064      (ERRRGU +   64)    /*        rgu.c:1668 */
#define   ERGU065      (ERRRGU +   65)    /*        rgu.c:1678 */
#define   ERGU066      (ERRRGU +   66)    /*        rgu.c:1688 */
#define   ERGU067      (ERRRGU +   67)    /*        rgu.c:1737 */
#define   ERGU068      (ERRRGU +   68)    /*        rgu.c:1746 */
#define   ERGU069      (ERRRGU +   69)    /*        rgu.c:1755 */
#define   ERGU070      (ERRRGU +   70)    /*        rgu.c:1878 */
#define   ERGU071      (ERRRGU +   71)    /*        rgu.c:1901 */
#define   ERGU072      (ERRRGU +   72)    /*        rgu.c:1913 */
#define   ERGU073      (ERRRGU +   73)    /*        rgu.c:2033 */
#define   ERGU074      (ERRRGU +   74)    /*        rgu.c:2043 */
#define   ERGU075      (ERRRGU +   75)    /*        rgu.c:2059 */
#define   ERGU076      (ERRRGU +   76)    /*        rgu.c:2114 */
#define   ERGU077      (ERRRGU +   77)    /*        rgu.c:2123 */
#define   ERGU078      (ERRRGU +   78)    /*        rgu.c:2133 */
#define   ERGU079      (ERRRGU +   79)    /*        rgu.c:2143 */
#define   ERGU080      (ERRRGU +   80)    /*        rgu.c:2192 */
#define   ERGU081      (ERRRGU +   81)    /*        rgu.c:2201 */
#define   ERGU082      (ERRRGU +   82)    /*        rgu.c:2210 */
#define   ERGU083      (ERRRGU +   83)    /*        rgu.c:2708 */


#ifdef __cplusplus
}
#endif
#endif /* __RGUH__ */

/********************************************************************30**

         End of file:     rgu.h@@/main/6 - Wed Jul 27 14:03:29 2011

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
/main/1      ---     sm  1. initial release.
/main/2      ---     st    1. Added Error Codes.
/main/4      ---     rgu_h_001.main_3   sv  1. Changing number of PDUs and LCs
                                              to minimal value for optimization
/main/5      ---      rgu_h_001.main_4   ap 1. Added RGU_MAX_TB macro
/main/6      ---      rgu_h_001.main_5  gvj 1. Updated for LTE MAC Rel 3.1
*********************************************************************91*/
