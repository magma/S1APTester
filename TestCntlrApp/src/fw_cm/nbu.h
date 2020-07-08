/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/********************************************************************20**

     Name:     

     Type:     C source file

     Desc:     Defines required by the NBU layer service user

     File:     nbu.h

     Sid:      
     Prg:      

*********************************************************************21*/

#include <string.h>
/* selector(coupling) values */
#define NBU_SEL_LC     2     /*!< Macro for Light Coupling */
#define NBU_SEL_TC     1     /*!< Macro for Tight Coupling */
#define NBU_SEL_LWLC   0     /*!< Macro for Light Weight Loose Coupling */


/*Interface Events */
#define EVTNBUINITIALUEMSG         1  /* Attach Request */
#define EVTNBUULNASMSG             2  /* UL NAS Transport message */
#define EVTNBUDLNASMSG             3  /* DL NAS TransPort message */
#define EVTNBUERABSINFO            4
#define EVTNBUUEIPINFOREQ          5  /* UE IP Address and Ue Id */
#define EVTNBUUEIPINFORSP          6  /* UE IP Address and Ue Id */
#define EVTNBUUEINACTIVITYIND      7  /* ue Inactivity occurs indication */
#define EVTNBUS1RELIND             8  /* S1 Release Indication */
#define EVTNBUUERADCAPIND          9  /* ue capability indication message */
#define EVTNBUPAGINGMSG            10 /* Paging message */
#define EVTNBUERABRELIND           11 /* Erab Rel Indication*/
#define EVTNBUERABSRELINFO         12 /* Erab Rel Information Indication */
#define EVTNBUUPDATEPLMNINFO       13 /* Update Plmn Info */
#define EVTNBUUEIPINFOUPDT         14 /* Update IPv6 address */
#define ERRNBU                     0

#define ENBU001         (ERRNBU + 1)
#define ENBU002         (ERRNBU + 2)
#define ENBU003         (ERRNBU + 3)
#define ENBU004         (ERRNBU + 4)
#define ENBU005         (ERRNBU + 5)
#define ENBU006         (ERRNBU + 6)
#define ENBU007         (ERRNBU + 7)
#define ENBU008         (ERRNBU + 8)
#define ENBU009         (ERRNBU + 9)
#define ENBU010         (ERRNBU + 10)
#define ENBU011         (ERRNBU + 11)
#define ENBU012         (ERRNBU + 12)
#define ENBU013         (ERRNBU + 13)
#define ENBU014         (ERRNBU + 14)
#define ENBU015         (ERRNBU + 15)
#define ENBU016         (ERRNBU + 16)
#define ENBU017         (ERRNBU + 17)
#define ENBU018         (ERRNBU + 18)
#define ENBU019         (ERRNBU + 19)
#define ENBU020         (ERRNBU + 20)
#define ENBU021         (ERRNBU + 21)
#define ENBU022         (ERRNBU + 22)
#define ENBU023         (ERRNBU + 23)
#define ENBU024         (ERRNBU + 24)
#define ENBU025         (ERRNBU + 25)
#define ENBU026         (ERRNBU + 26)
#define ENBU027         (ERRNBU + 27)
#define ENBU028         (ERRNBU + 28)
#define ENBU029         (ERRNBU + 29)
#define ENBU030         (ERRNBU + 30)
#define ENBU031         (ERRNBU + 31)
#define ENBU032         (ERRNBU + 32)
#define ENBU033         (ERRNBU + 33)
#define ENBU034         (ERRNBU + 34)
#define ENBU035         (ERRNBU + 35)
#define ENBU036         (ERRNBU + 36)
#define ENBU037         (ERRNBU + 37)
#define ENBU038         (ERRNBU + 38)
#define ENBU039         (ERRNBU + 39)
#define ENBU040         (ERRNBU + 40)
#define ENBU041         (ERRNBU + 41)
#define ENBU042         (ERRNBU + 42)
#define ENBU043         (ERRNBU + 43)
#define ENBU044         (ERRNBU + 44)
#define ENBU045         (ERRNBU + 45)
#define ENBU046         (ERRNBU + 46)
#define ENBU047         (ERRNBU + 47)
#define ENBU048         (ERRNBU + 48)
#define ENBU049         (ERRNBU + 49)
#define ENBU050         (ERRNBU + 50)

/********************************************************************30**

         End of file:     

*********************************************************************31*/
