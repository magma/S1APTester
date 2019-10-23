
/*******************************************************************20**
 *   Name:     eGTP
 *
 *   Type:     C source file
 *
 *   Desc:     product id file
 *
 *   File:     eg_id.c
 *
 *   Sid:      eg_id.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:45 2015
 *
 *   Prg:      skv
 ********************************************************************21*/
/**********************************************************
 *   H E A D E R   I N C L U D E   F I L E S (.h)         *
 **********************************************************/
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System Services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_hash.h"       /* common structs 1 */
#include "cm_mblk.h"       /* common memory */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common structs 3 */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport */
#include "cm_dns.h"        /* common DNS library */
#include "hit.h"           /* TUCL Layer */
#include "egt.h"           /* eGTP Upper Interface */
#include "leg.h"           /* eGTP LM Interface */
#include "eg_edm.h"        /* EDM Defines */
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "sht.h"
#endif
#include "eg.h"            /* eGTP Layer */

/************************************************************************
 *          H E A D E R   I N C L U D E    F I L E S (.x)               *
 ************************************************************************/

#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common structs 3 */
#include "cm_inet.x"       /* common transport */
#include "cm_tpt.x"        /* common transport */
#include "cm_dns.x"        /* common DNS library */
#include "hit.x"           /* TUCL Layer */
#include "egt.x"           /* eGTP Upper Interface */
#include "leg.x"           /* eGTP LM Interface */
#include "eg_edm.x"        /* EDM Defines */
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#endif
#include "eg.x"            /* eGTP Layer */
#include "eg_tpt.x"        /* EGTP TPT module defines */


#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC UA                       */
#endif

/**********************************************************
 *   D E F I N E S   F O R  T H I S  M O D U L E          *
 **********************************************************/
#define EGSWMV 2                   /* eGTP - main version */
#define EGSWMR 1                  /* eGTP - main revision */
#define EGSWBV 0                 /* eGTP - branch version */
/*eg013.201 eGTP eg013.201 patch release*/
#define EGSWBR 13              /* eGTP - branch revision  */
#define EGSWPN "1000368"            /* eGTP - part number */

/**********************************************************
 *   F O R W A R D   R E F E R E N C E S                  *
 *********************************************************/

/***********************************************************
 * P U B L I C   V A R I A B L E   D E C L A R A T I O N S *
 ***********************************************************/
/******************************************
 * System Identification Information      *
 ******************************************/
PRIVATE CONSTANT SystemId sId ={
   EGSWMV,                /* main version */
   EGSWMR,               /* main revision */
   EGSWBV,              /* branch version */
   EGSWBR,             /* branch revision */
   EGSWPN,                 /* part number */
};

/**********************************************************
 *          S U P P O R T   F U N C T I O N S             *
 **********************************************************/

/****************************************************************************
 * Function:   get system id
 *
 * Description:  Get system id consisting of part number, main 
 *               version and revision and branch version and branch.
 * 
 * Return: TRUE - ok
 * 
 * Notes:  None 
 * 
 * File:  eg_id.c *
 ***************************************************************************/
#ifdef ANSI
PUBLIC S16 egGetSId
(
SystemId *sysId            /* system id */
)
#else
PUBLIC S16 egGetSId(sysId)
SystemId *sysId;           /* system id */
#endif
{
   TRC2(egGetSId);
   /*****************************************************
    * Copy the Systems Major Version, Minor Version,    *
    * Branch Verstion, Branch Revision and Patch Number *
    *****************************************************/
    sysId->mVer = sId.mVer;
    sysId->mRev = sId.mRev;
    sysId->bVer = sId.bVer;
    sysId->bRev = sId.bRev;
    sysId->ptNmb = sId.ptNmb;

   RETVALUE(TRUE);
}

/********************************************************************30**

         End of file:     eg_id.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:45 2015

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
/main/2      ---      kchaitanya        1. Initial for eGTP 1.2 Release
/main/2   eg001.102  rss               1. eGTP-U Performance enhancement
/main/2   eg002.102  rss               1. eGTP-U ccpu00107314 changes.
/main/2   eg003.102  rss               1. eGTP-U changes.
/main/2   eg004.102  rrm               1. Added changes for MME release 1.1.
/main/3      ---     pmacharla         1. Initial for eGTP 2.1 Release
/main/3  eg001.201   asaurabh          1. patch eg001.201.
/main/3  eg002.201   psingh            1. eGTP eg002.201 patch release
/main/3  eg003.201   psingh            1. eGTP eg003.201 patch release
/main/3  eg004.201   magnihotri        1. eGTP-C PSF eg004.201 patch release
/main/3  eg005.201   psingh            1. eGTP eg005.201 patch release
/main/3  eg006.201   psingh            1. eGTP eg006.201 patch release
/main/3  eg007.201   psingh            1. eGTP eg007.201 patch release
/main/3  eg008.201   asaurabh          1. eGTP eg008.201 patch release
/main/3  eg009.201   asaurabh          1. eGTP eg009.201 patch release
/main/3  eg010.201   asaurabh          1. eGTP eg010.201 patch release
/main/3  eg011.201   avenugop          1. eGTP eg011.201 patch release
/main/3  eg012.201   shpandey          1. eGTP eg012.201 patch release
/main/3  eg013.201   shpandey          1. eGTP eg013.201 patch release
*********************************************************************91*/

