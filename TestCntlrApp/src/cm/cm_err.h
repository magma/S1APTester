

/********************************************************************20**
  
     Name:     common functions
  
     Type:     C include file
  
     Desc:     Error defines required by common functions.
  
     File:     cm_err.h

     Sid:      cm_err.h@@/main/18 - Fri Sep 16 02:55:52 2005
  
     Prg:      na
  
*********************************************************************21*/

#ifndef __CMERRH__
#define __CMERRH__
  
  
/*
*   The defines declared in this file correspond to defines
*   used by the following TRILLIUM software:
*
*    part no.                   description
*    --------   ----------------------------------------------
*
*/

/* defines */

#define  ECMBASE    (ERRCM + 0)   /* reserved */
#define  ECMXXX     (ECMBASE)     /* reserved */

/* error id's */

#define  ECM001 (ERRCM + 1)      /*  */
#define  ECM002 (ERRCM + 2)      /*  */
#define  ECM003 (ERRCM + 3)      /*  */
#define  ECM004 (ERRCM + 4)      /*  */
#define  ECM005 (ERRCM + 5)      /* cmPkSpConEvnt */
#define  ECM006 (ERRCM + 6)      /* cmUnpkSpConEvnt */
#define  ECM007 (ERRCM + 7)      /* cmPrcTmr */
#define  ECM008 (ERRCM + 8)      /* cmPlcCbTq */
#define  ECM009 (ERRCM + 9)      /* cmPlcCbTq */
#define  ECM010 (ERRCM + 10)     /* cmRmvCbTq */
#define  ECM011 (ERRCM + 11)     /* cmAddrCpy */
#define  ECM012 (ERRCM + 12)     /* cmAddrCpy */
#define  ECM013 (ERRCM + 13)     /* cmAddrCpy */
#define  ECM014 (ERRCM + 14)     /* cmAddrSet */
#define  ECM015 (ERRCM + 15)     /* cmAddrSet */
#define  ECM016 (ERRCM + 16)     /* cmPlcCbTq */
#define  ECM017 (ERRCM + 17)     /* cmAtmQosCpy */
#define  ECM018 (ERRCM + 18)     /* cmAtmQosCpy */
#define  ECM019 (ERRCM + 19)     /* cmAtmCellRateCpy */
#define  ECM020 (ERRCM + 20)     /* cmAtmCellRateCpy */
#define  ECM021 (ERRCM + 21)     /* cmPkAtmCellRate */
#define  ECM022 (ERRCM + 22)     /* cmPkAtmQos */
#define  ECM023 (ERRCM + 23)     /* cmPkBndCfg */
#define  ECM024 (ERRCM + 24)     /* cmPkBndCfg */
#define  ECM025 (ERRCM + 25)     /* cmUnpkAtmCellRate */
#define  ECM026 (ERRCM + 26)     /* cmUnpkAtmCellRate */
#define  ECM027 (ERRCM + 27)     /* cmUnpkAtmQos */
#define  ECM028 (ERRCM + 28)     /* cmUnpkAtmQos */
#define  ECM029 (ERRCM + 29)     /* cmUnpkBndCfg */
#define  ECM030 (ERRCM + 30)     /* cmUnpkBndCfg */
#define  ECM031 (ERRCM + 31)     /* cmUnpkSystemId */
#define  ECM032 (ERRCM + 32)     /* cmUnpkSystemId */
#define  ECM033 (ERRCM + 33)     /* cmDateTimeCmp */
#define  ECM034 (ERRCM + 34)     /* cmDateTimeCmp */
#define  ECM035 (ERRCM + 35)     /* cmUmObjIdSet */
#define  ECM036 (ERRCM + 36)     /* cmUmObjIdSet */


#define  ECM037 (ERRCM + 37)     /* cm_ss.c */
#define  ECM038 (ERRCM + 38)     /* cm_ss.c */
#define  ECM039 (ERRCM + 39)     /* cm_ss.c */
#define  ECM040 (ERRCM + 40)     /* cm_ss.c */
#define  ECM041 (ERRCM + 41)     /* cm_ss.c */
#define  ECM042 (ERRCM + 42)     /* cm_ss.c */
#define  ECM043 (ERRCM + 43)     /* cm_ss.c */
#define  ECM044 (ERRCM + 44)     /* cm_ss.c */
#define  ECM045 (ERRCM + 45)     /* cm_ss.c */
#define  ECM046 (ERRCM + 46)     /* cm_ss.c */
#define  ECM047 (ERRCM + 47)     /* cm_ss.c */
#define  ECM048 (ERRCM + 48)     /* cm_ss.c */
#define  ECM049 (ERRCM + 49)     /* cm_ss.c */
#define  ECM050 (ERRCM + 50)     /* cm_ss.c */
#define  ECM051 (ERRCM + 51)     /* cm_ss.c */
#define  ECM052 (ERRCM + 52)     /* cm_ss.c */
#define  ECM053 (ERRCM + 53)     /* cm_ss.c */
#define  ECM054 (ERRCM + 54)     /* cm_ss.c */
#define  ECM055 (ERRCM + 55)     /* cm_ss.c */
#define  ECM056 (ERRCM + 56)     /* cm_ss.c */
#define  ECM057 (ERRCM + 57)     /* cm_ss.c */
#define  ECM058 (ERRCM + 58)     /* cm_ss.c */
#define  ECM059 (ERRCM + 59)     /* cm_ss.c */
#define  ECM060 (ERRCM + 60)     /* cm_ss.c */
#define  ECM061 (ERRCM + 61)     /* cm_ss.c */
#define  ECM062 (ERRCM + 62)     /* cm_ss.c */
#define  ECM063 (ERRCM + 63)     /* cm_ss.c */
#define  ECM064 (ERRCM + 64)     /* cm_ss.c */
#define  ECM065 (ERRCM + 65)     /* cm_ss.c */
#define  ECM066 (ERRCM + 66)     /* cm_ss.c */
#define  ECM067 (ERRCM + 67)     /* cm_ss.c */
#define  ECM068 (ERRCM + 68)     /* cm_ss.c */
#define  ECM069 (ERRCM + 69)     /* cm_ss.c */
#define  ECM070 (ERRCM + 70)     /* cm_ss.c */
#define  ECM071 (ERRCM + 71)     /* cm_ss.c */
#define  ECM072 (ERRCM + 72)     /* cm_ss.c */
#define  ECM073 (ERRCM + 73)     /* cm_ss.c */
#define  ECM074 (ERRCM + 74)     /* cm_ss.c */
#define  ECM075 (ERRCM + 75)     /* cm_ss.c */
#define  ECM076 (ERRCM + 76)     /* cm_ss.c */
#define  ECM077 (ERRCM + 77)     /* cm_ss.c */
#define  ECM078 (ERRCM + 78)     /* cm_ss.c */
#define  ECM079 (ERRCM + 79)     /* cm_ss.c */
#define  ECM080 (ERRCM + 80)     /* cm_ss.c */
#define  ECM081 (ERRCM + 81)     /* cm_ss.c */
#define  ECM082 (ERRCM + 82)     /* cm_ss.c */
#define  ECM083 (ERRCM + 83)     /* cm_ss.c */
#define  ECM084 (ERRCM + 84)     /* cm_ss.c */
#define  ECM085 (ERRCM + 85)     /* cm_ss.c */
#define  ECM086 (ERRCM + 86)     /* cm_ss.c */
#define  ECM087 (ERRCM + 87)     /* cm_ss.c */
#define  ECM088 (ERRCM + 88)     /* cm_ss.c */
#define  ECM089 (ERRCM + 89)     /* cm_ss.c */
#define  ECM090 (ERRCM + 90)     /* cm_ss.c */
#define  ECM091 (ERRCM + 91)     /* cm_ss.c */
#define  ECM092 (ERRCM + 92)     /* cm_ss.c */
#define  ECM093 (ERRCM + 93)     /* cm_ss.c */
#define  ECM094 (ERRCM + 94)     /* cm_ss.c */
#define  ECM095 (ERRCM + 95)     /* cm_ss.c */
#define  ECM096 (ERRCM + 96)     /* cm_ss.c */
#define  ECM097 (ERRCM + 97)     /* cm_ss.c */
#define  ECM098 (ERRCM + 98)     /* cm_ss.c */
#define  ECM099 (ERRCM + 99)     /* cm_ss.c */
#define  ECM100 (ERRCM + 100)    /* cm_ss.c */
#define  ECM101 (ERRCM + 101)    /* cm_ss.c */
#define  ECM102 (ERRCM + 102)    /* cm_ss.c */
#define  ECM103 (ERRCM + 103)    /* cm_ss.c */
#define  ECM104 (ERRCM + 104)    /* cm_ss.c */
#define  ECM105 (ERRCM + 105)    /* cm_ss.c */
#define  ECM106 (ERRCM + 106)    /* cm_ss.c */
#define  ECM107 (ERRCM + 107)    /* cm_ss.c */
#define  ECM108 (ERRCM + 108)    /* cm_ss.c */
#define  ECM109 (ERRCM + 109)    /* cm_ss.c */
#define  ECM110 (ERRCM + 110)    /* cm_ss.c */
#define  ECM111 (ERRCM + 111)    /* cm_ss.c */
#define  ECM112 (ERRCM + 112)    /* cm_ss.c */
#define  ECM113 (ERRCM + 113)    /* cm_ss.c */
#define  ECM114 (ERRCM + 114)    /* cm_ss.c */
#define  ECM115 (ERRCM + 115)    /* cm_ss.c */
#define  ECM116 (ERRCM + 116)    /* cm_ss.c */
#define  ECM117 (ERRCM + 117)    /* cm_ss.c */
#define  ECM118 (ERRCM + 118)    /* cm_ss.c */
#define  ECM119 (ERRCM + 119)    /* cm_ss.c */
#define  ECM120 (ERRCM + 120)    /* cm_ss.c */
#define  ECM121 (ERRCM + 121)    /* cm_ss.c */
#define  ECM122 (ERRCM + 122)    /* cm_ss.c */
#define  ECM123 (ERRCM + 123)    /* cm_ss.c */
#define  ECM124 (ERRCM + 124)    /* cm_ss.c */
#define  ECM125 (ERRCM + 125)    /* cm_ss.c */
#define  ECM126 (ERRCM + 126)    /* cm_ss.c */
#define  ECM127 (ERRCM + 127)    /* cm_ss.c */
#define  ECM128 (ERRCM + 128)    /* cm_ss.c */
#define  ECM129 (ERRCM + 129)    /* cm_ss.c */
#define  ECM130 (ERRCM + 130)    /* cm_ss.c */
#define  ECM131 (ERRCM + 131)    /* cm_ss.c */
#define  ECM132 (ERRCM + 132)    /* cm_ss.c */
#define  ECM133 (ERRCM + 133)    /* cm_ss.c */
#define  ECM134 (ERRCM + 134)    /* cm_ss.c */
#define  ECM135 (ERRCM + 135)    /* cm_ss.c */
#define  ECM136 (ERRCM + 136)    /* cm_ss.c */
#define  ECM137 (ERRCM + 137)    /* cm_ss.c */
#define  ECM138 (ERRCM + 138)    /* cm_ss.c */
#define  ECM139 (ERRCM + 139)    /* cm_ss.c */
#define  ECM140 (ERRCM + 140)    /* cm_ss.c */
#define  ECM141 (ERRCM + 141)    /* cm_ss.c */
#define  ECM142 (ERRCM + 142)    /* cm_ss.c */
#define  ECM143 (ERRCM + 143)    /* cm_ss.c */
#define  ECM144 (ERRCM + 144)    /* cm_ss.c */
#define  ECM145 (ERRCM + 145)    /* cm_ss.c */
#define  ECM146 (ERRCM + 146)    /* cm_ss.c */
#define  ECM147 (ERRCM + 147)    /* cm_ss.c */
#define  ECM148 (ERRCM + 148)    /* cm_ss.c */
#define  ECM149 (ERRCM + 149)    /* cm_ss.c */
#define  ECM150 (ERRCM + 150)    /* cm_ss.c */
#define  ECM151 (ERRCM + 151)    /* cm_ss.c */
#define  ECM152 (ERRCM + 152)    /* cm_ss.c */
#define  ECM153 (ERRCM + 153)    /* cm_ss.c */
#define  ECM154 (ERRCM + 154)    /* cm_ss.c */
#define  ECM155 (ERRCM + 155)    /* cm_ss.c */
#define  ECM156 (ERRCM + 156)    /* cm_ss.c */
#define  ECM157 (ERRCM + 157)    /* cm_ss.c */
#define  ECM158 (ERRCM + 158)    /* cm_ss.c */
#define  ECM159 (ERRCM + 159)    /* cm_ss.c */
#define  ECM160 (ERRCM + 160)    /* cm_ss.c */
#define  ECM161 (ERRCM + 161)    /* cm_ss.c */
#define  ECM162 (ERRCM + 162)    /* cm_ss.c */
#define  ECM163 (ERRCM + 163)    /* cm_ss.c */
#define  ECM164 (ERRCM + 164)    /* cm_ss.c */
#define  ECM165 (ERRCM + 165)    /* cm_ss.c */
#define  ECM166 (ERRCM + 166)    /* cm_ss.c */
#define  ECM167 (ERRCM + 167)    /* cm_ss.c */
#define  ECM168 (ERRCM + 168)    /* cm_ss.c */
#define  ECM169 (ERRCM + 169)    /* cm_ss.c */
#define  ECM170 (ERRCM + 170)    /* cm_ss.c */
#define  ECM171 (ERRCM + 171)    /* cm_ss.c */
#define  ECM172 (ERRCM + 172)    /* cm_ss.c */
#define  ECM173 (ERRCM + 173)    /* cm_ss.c */
#define  ECM174 (ERRCM + 174)    /* cm_ss.c */
#define  ECM175 (ERRCM + 175)    /* cm_ss.c */
#define  ECM176 (ERRCM + 176)    /* cm_ss.c */


#endif

  
/********************************************************************30**
  
         End of file:     cm_err.h@@/main/18 - Fri Sep 16 02:55:52 2005
  
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
1.1          ---  bn    1. text changes
             ---  jrl   2. trillium development system checkpoint (dvs)
                           at version: 1.0.0.0

1.2          ---  jrl   1. text changes

1.3          ---  jrl   1. text changes

1.4          ---  fmg   1. added more error codes for cm_bdy2.c, 
                           and cm_bdy3.c

1.5          ---  nkk   1. added more error codes for cm_bdy4.c

1.6          ---  fmg   1. add error code
             ---  nkk   2. add error codes

1.7          ---  nkk   1. add error codes

1.8          ---  mb    1. added new error codes for new file cm_ss.c.

*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.9          ---      kvm  1. defined ECMATMXXX error codes for cm_atm.c
             ---      kvm  2. change copyright header

1.10         ---      mc   1. added ECMATM528.

1.11         ---      ada  1. New copyright header and cosmetic changes.

1.12         ---      rb   1. Modified ECMATM error codes.
             ---      rb   2. Formatted changelog.

1.13         ---      bbk  1. Changed copyright header date.

1.14         ---      ada  1. Added error codes ECM for SCompressMsg

1.15         ---      tej  1. Changed copyright header date.

1.16         ---      mk   1. removed the cm_atm specific error defines

/main/18     ---      st   1. Update for MAP Release 2.3
*********************************************************************91*/
