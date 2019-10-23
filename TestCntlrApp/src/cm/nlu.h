

/********************************************************************20**

     Name:     ESON layer management

     Type:     

     Desc:     This file contains the 
               

     File:     nlu.h

     Sid:      nlu.h@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:11:18 2014

     Prg:      subhamay 

*********************************************************************21*/
#ifndef __NLUH__
#define __NLUH__

#define NLU_SEL_LC                             0
#define NLU_SEL_TC                             1
#define NLU_SEL_LWLC                           2 

#define EVTNLUBNDREQ                           1
#define EVTNLUBNDCFM                           2
#define EVTNLUNHBRREQ                          3
#define EVTNLUPCIMODINDCFM                     4
#define EVTNLUPERCELLSRCHRSP                   5
#define EVTNLUUEMEASRPTIND                     6
#define EVTNLUUECQIRPTIND                      7
#define EVTNLUUEIND                            8

#define NLU_MAX_NGH_CELL_INFO                  16
#define NLU_MAX_REPORTS                        8
#define NLU_MAX_NGH_NGH_CELL_INFO              16
#define NLU_MAX_NGH_ENB_CFG                    16
/* Periodic REM for TPM */
#define NLU_REM_MAX_CELL_SEARCH                16                
/* Periodic REM for TPM End */
#ifdef LTE_UNLICENSED
#define LWR_LTEU_MAX_EARFCN   10
#endif
#endif /* __NLUH__ */
/********************************************************************30**

           End of file:     nlu.h@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:11:18 2014

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
*********************************************************************91*/
