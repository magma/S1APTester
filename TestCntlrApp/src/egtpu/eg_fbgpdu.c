

/********************************************************************20**

     Name:    EGTP - Lower Interface

     Type:    C source file

     Desc:    This file implements interaction with Lower Interface

     File:    eg_li.c

     Sid:      eg_fbgpdu.c@@/main/TeNB_Main_BR/7 - Mon Aug 11 16:42:23 2014

     Prg:     ad

*********************************************************************21*/


/* header include files (.h) */
#include "envopt.h"        /* Environment options             */
#include "envdep.h"        /* Environment dependent options   */
#include "envind.h"        /* Environment independent options */
#include "gen.h"           /* General layer                   */
#include "ssi.h"           /* System service interface        */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tpt.h"        /* Common transport library        */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_dns.h"        /* Common DNS library              */
#include "cm_inet.h"       /* Common socket library           */
#include "hit.h"           /* HIT interface defines           */
/* eg004.201 Header files added for eGTP-C PSF */
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "hw.h"
#include "sht.h"
#endif

#include "egt.h"           /* EGTP Upper Interface Defines  */
#include "leg.h"           /* EGTP MI Interface Defines  */
#include "eg.h"            /* EGTP Defines  */
#include "eg_err.h"        /* EGTP Error Defines  */
#include "eg_edm.h"        /* EDM Module structures            */
#ifdef SS_MULTIPLE_PROCS
#endif /* SS_MULTIPLE_PROCS */
#ifdef TIME_MES
#include <time.h>
#endif


/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common linrary function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_tpt.x"        /* Common transport library        */
#include "cm_mblk.x"       /* Common memory allocation        */
#include "cm_dns.x"        /* Common DNS library              */
#include "cm_inet.x"       /* Common socket library           */
#include "hit.x"           /* HIT interface defines           */
/* eg004.201 Header files added for eGTP-C PSF */
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#endif

#include "egt.x"           /* EGTP Upper Interface Defines  */
#include "leg.x"           /* EGTP MI Interface Defines  */
#include "eg_edm.x"        /* EDM Module structures            */
#ifdef SS_MULTIPLE_PROCS
#endif /* SS_MULTIPLE_PROCS */
#include "eg.x"           /* EGTP Defines  */
#include "eg_tpt.x"       /* EGTP TPT Module */
/* eg004.201 Header files added for eGTP-C PSF */
#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC UA                       */
#endif
#ifdef LC_EGTP_THREAD
#include "ss_rbuf.h"
#include "ss_rbuf.h"
#include "ss_rbuf.x"
#endif
#ifdef FLAT_BUFFER_OPT
#ifdef DAM_PDCP_OPT
EXTERN S16 wrDamFbDatInd ARGS((U8 *tmpBuf,U8 *buf,U32 bufLen));
#endif
#ifdef LC_EGTP_THREAD
EXTERN S16 mtAddEgtpBufToRing(SsRngBufId ringId,U8 *tmpBuf,U8 *buf, U32 bufLen);
#endif
/*******************************************************************
 ********************** Local function definition ******************
 ********************************************************************/

/*******************************************************************
*
*       Fun:   EgLiHitUDatInd
*
*       Notes: This primitive is invoked by HIT service provider to
*              forward received datagram (UDP) to EGTP
*
*       Ret:   ROK on success.
*              RFAILED on error.
*
*       File:  eg_li.c
*
*******************************************************************/
#ifdef ANSI
PUBLIC S16 egHndlRecvFb
(
U8             *buf,        /* message buffer */
U32            bufLen       /* bufLen */
)
#else
PUBLIC S16 egHndlRecvFb(*buf, bufLen)
U8             *buf;        /* message buffer */
U32            bufLen;      /* bufLen */
#endif
{
   U8             *tmpBuf;
   U8              extPres;
   U16             msgLen;
   U8              msgType;
#ifndef  DAM_PDCP_OPT
   Pst             pst;
   U32             teId;
   FlatBuffer     fbuf;
#endif    

   EG_TRC3(egHndlRecvFb);


      if (bufLen > EG_MIN_MSG_LEN)
      {
         tmpBuf = &buf[0];
         extPres = tmpBuf[0] & 0x07;
         msgType = tmpBuf[1];
         if ((msgType != EGT_GTPU_MSG_GPDU) || (extPres > 0))
         {
            /*printf("Message Type not of type EGT_GTPU_MSG_GPDU, Type = %d and extPres is %d \n", msgType, extPres);*/
            RETVALUE(RFAILED);
         }
         tmpBuf += 2;
  
         msgLen =  (tmpBuf[0] << 8) |
                   (tmpBuf[1]); 
         tmpBuf += 2;

         if (bufLen != (msgLen + 8))
         {
            RETVALUE(RFAILED);
         }
#ifdef DAM_PDCP_OPT
#ifdef LC_EGTP_THREAD
         if( ROK  != (mtAddEgtpBufToRing(SS_RNG_BUF_EGTP_FREE_RING, tmpBuf,buf,bufLen)))
         {
           RETVALUE(RFAILED);
         }
#else
         if( ROK  != (wrDamFbDatInd(tmpBuf,buf,bufLen)))
         {
           RETVALUE(RFAILED);
         }
#endif
#else  
         teId   = (tmpBuf[0] << 24) |
                  (tmpBuf[1] << 16) |
                  (tmpBuf[2] << 8) |
                  (tmpBuf[3]);

         tmpBuf += 4;


         fbuf.startAddr = buf;
         fbuf.len       = bufLen - 8;
         fbuf.ptr       = tmpBuf;

      if(ROK  != (EuLiEgtEguDatIndFB(&pst, &fbuf, teId)))
      {
         EG_RETVALUE(RFAILED);
      }
#endif 
         EG_RETVALUE(ROK);
   }
   else
   {
      RETVALUE(RFAILED);
   }
} /* EgLiHitUDatInd */
#endif

/********************************************************************30**

         End of file:     eg_fbgpdu.c@@/main/TeNB_Main_BR/7 - Mon Aug 11 16:42:23 2014

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
/main/1      ---          ad                1. Created for Initial Release 1.1
/main/2      ---          rsharon           1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced.
                          rss               2. Multithreaded performance changes gaurded under SS_MT_CB flag.
/main/2      eg002.102    rss               1.  Used local pst structure and modify it locally
/main/2      eg003.102    rss               1.  Removed cm_xtree from the include list.
/main/3      ---      pmacharla         Initial for eGTP release 2.1
/main/3      eg003.201    psingh            1. Merged code from eg006.102 to Fix TRACE5 issue
                                            2. Fixed warning due to improper placement of EG_TRC3
                                            3. eg009.102: Handling for NULL IP value in address
                                            4. eg009.102: Handling for LEG_TSAP_WAIT_BNDDIS
/main/3      eg004.201    magnihotri        1. Header files added for eGTP-C PSF
                                            2. Run time update send when tsap cb bind conform received
                                            3. Update stable state of TSAP when tpt server opened
                                            4. Dispatch run time update for TSAP when tpt server opened
                                            5. Update stable state of tpt server when disconnected i.e
                                               when server connection id down
                                            6. Send run-time update when Data Indication received
                                            7. Send run-time update when disconnect conform received
                                            8. Update stable state of TSAP cb when TSAP state changed
                                               changed to BINDED state
/main/3      eg007.201    psingh            1. Refence TSapCb using suId as index to tSapLst array
/main/3      eg009.201    asaurabh          1. Handling for IP value as NULL
                                            2. Added TSapCb to function call of egGenTrcInd()
                                            3. Handling for LEG_TSAP_WAIT_BNDDIS
 *********************************************************************91*/
