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

     Desc:     Defines required by the NBT layer service user

     File:     nbt.h

     Sid:      
     Prg:      

*********************************************************************21*/


/* selector(coupling) values */
#define NBT_SEL_LC     2     /*!< Macro for Light Coupling */
#define NBT_SEL_TC     1     /*!< Macro for Tight Coupling */
#define NBT_SEL_LWLC   0     /*!< Macro for Light Weight Loose Coupling */

#define MAX_ENB_NAME_LEN   20

#define NBT_MAX_PLMN_ID               6
#define NBT_MAX_NUM_BPLMNS            5
#define NBT_MAX_NUM_CSG_ID          256
#define NBT_MAX_NUM_TAC             256
#define NBT_MAX_NUM_OF_ENBS          5
/* eNodeB types */
#define NBT_ENODEB_TYPE_MACRO      0x00
#define NBT_ENODEB_TYPE_HOME       0x01

#define NBT_MAX_PLMNS_PER_MME        32
#define NBT_MAX_GRPS_PER_MME        256
#define NBT_MAX_CODES_PER_MME       256


/*Interface Events */
#define EVTNBTMSGREQ        1       /* Config request */
#define EVTNBTMSGRSP        2       /* Config Confirm */

#define ERRNBT                  0

#define ENBT001         (ERRNBT + 1)
#define ENBT002         (ERRNBT + 2)
#define ENBT003         (ERRNBT + 3)
#define ENBT004         (ERRNBT + 4)
#define ENBT005         (ERRNBT + 5)
#define ENBT006         (ERRNBT + 6)
#define ENBT007         (ERRNBT + 7)
#define ENBT008         (ERRNBT + 8)
#define ENBT009         (ERRNBT + 9)
#define ENBT010         (ERRNBT + 10)
#define ENBT011         (ERRNBT + 11)
#define ENBT012         (ERRNBT + 12)
#define ENBT013         (ERRNBT + 13)
#define ENBT014         (ERRNBT + 14)
#define ENBT015         (ERRNBT + 15)
#define ENBT016         (ERRNBT + 16)
#define ENBT017         (ERRNBT + 17)
#define ENBT018         (ERRNBT + 18)
#define ENBT019         (ERRNBT + 19)
#define ENBT020         (ERRNBT + 20)
#define ENBT021         (ERRNBT + 21)
#define ENBT022         (ERRNBT + 22)
#define ENBT023         (ERRNBT + 23)
#define ENBT024         (ERRNBT + 24)
#define ENBT025         (ERRNBT + 25)
#define ENBT026         (ERRNBT + 26)
#define ENBT027         (ERRNBT + 27)
#define ENBT028         (ERRNBT + 28)
#define ENBT029         (ERRNBT + 29)
#define ENBT030         (ERRNBT + 30)
#define ENBT031         (ERRNBT + 31)
#define ENBT032         (ERRNBT + 32)
#define ENBT033         (ERRNBT + 33)
#define ENBT034         (ERRNBT + 34)
#define ENBT035         (ERRNBT + 35)
#define ENBT036         (ERRNBT + 36)
#define ENBT037         (ERRNBT + 37)
#define ENBT038         (ERRNBT + 38)
#define ENBT039         (ERRNBT + 39)
#define ENBT040         (ERRNBT + 40)
#define ENBT041         (ERRNBT + 41)
#define ENBT042         (ERRNBT + 42)
#define ENBT043         (ERRNBT + 43)
#define ENBT044         (ERRNBT + 44)
#define ENBT045         (ERRNBT + 45)
#define ENBT046         (ERRNBT + 46)
#define ENBT047         (ERRNBT + 47)
#define ENBT048         (ERRNBT + 48)
#define ENBT049         (ERRNBT + 49)
#define ENBT050         (ERRNBT + 50)

/********************************************************************30**

         End of file:     

*********************************************************************31*/
