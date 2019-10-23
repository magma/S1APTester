
/********************************************************************20**
  
     Name:    TCP UDP Convergence Layer (TUCL)
 
     Type:    C source file
  
     Desc:    C source Code used for testing TCP UDP Convergence
              Layer in Trillium Development environment.
              
              
     File:    hi_acc2.c
  
     Sid:      tl_acc2.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:54 2015

     Prg:     asa
  
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

/* external headers */
/* hi028.201: Fix for compilation warning*/
#include <unistd.h>

#include "cm_inet.h"       /* common sockets */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm_err.h"        /* common error */
#include "cm5.h"           /* common timer */
#ifdef FTHA
#include "sht.h"           /* SHT Interface header files */
#endif
#include "lhi.h"           /* layer management */
#include "cm_tpt.h"        /* common transport defines */
#include "hit.h"           /* HIT interface */
#include "hi.h"            /* TUCL internal defines */
#include "hi_acc.h"        /* TUCL acceptance test defines */
#include "hi_accen.h"      /* environment dependent */

/*hi028.201: Included ss_task.h file*/
#ifdef HI_ACC_GEN_RECONFIG
#include "ss_task.h"
#endif
 
/* header/extern include files (.x) */
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_inet.x"       /* common sockets */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common hashing */
#include "cm5.x"           /* common timer */
#include "cm_tpt.x"        /* common transport typedefs */
#ifdef FTHA
#include "sht.x"           /* SHT Interface defines */
#endif
#include "lhi.x"           /* layer management, HI layer */
#include "hit.x"           /* HIT interface */
#include "hi.x"            /* TUCL internal structures */
#include "hi_acc.x"        /* TUCL acceptance test structures */
 
#ifndef WIN32
#include <signal.h> 
#endif

/* Global Variable */

#ifdef HI_RUG
PRIVATE U16 checkMsg;
#endif /* HI_RUG */


/* Public variable declarations */


/* hi028.201: Modified test case hiAccTst0 */
/*
*
*       Fun:   hiAccTst0 
*
*       Desc:  Test Case 0: Set up a TCP server in TUCL and send
*              data to it from a dummy client created in the ACC
*              envelope. The server loops back the data received. The
*              client checks the integrity of the received data.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst0
(
Void
)
#else
PUBLIC S16 hiAccTst0(Void)
#endif
{

   CmInetFdSet  writeFdS;
   CmInetFdSet  readFdS;
   MsgLen       msgLen;
   U32          timeout;
   S16          numFdS;
   Buffer       *msg;
   Buffer       *echo;  
   S16          ret;
   CmIcmpFilter nullFilter;

   TRC2(hiAccTst0)
  
   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Initialize the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;

         /* Initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV4;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.address =  HI_ACC_SERV_ADDR;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                          HI_ACC_SERV_PORT+hiAccCb.curTst.id +
                                          4;

         /* Initialize transport parameters */
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 0;
#ifdef WIN32
         hiAccCb.curTst.tPar.u.sockParam.listenQSize = 1;
#else
         hiAccCb.curTst.tPar.u.sockParam.listenQSize = 5;
#endif /* WIN32 */

         /* Request HI to open a TCP Server */
         HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
         nullFilter.type = CM_ICMP_NO_FILTER;

         HIACC_OPEN_TCP_SRV(HIACC_SERV_SUCON_ID, &hiAccCb.curTst.remAddr, 
                            &hiAccCb.curTst.tPar, &nullFilter, 
                            HI_SRVC_TCP_TPKT_HDR);
         hiAccCb.curTst.state++;
         HIACCPRINT((hiAccCb.prntBuf, "Case 0\n"))
         break;

      case 1:  /* HitConCfm */
         break;      

      case 2:
         /* Open a TCP Client */

         /* Open a new socket */
#ifdef IPV6_SUPPORTED
         ret = cmInetSocket(CM_INET_STREAM, &hiAccCb.curTst.fd1, 0,
                            CM_INET_IPV4_DOMAIN);
#else
         ret = cmInetSocket(CM_INET_STREAM, &hiAccCb.curTst.fd1, 0);
#endif /* IPV6_SUPPORTED */
         if (ret != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, 
                         "hiAccTst0: Failed to Open client Socket\n"))
            HI_ACC_TST_FAILED();
         }

         /* Connect to the server */
#ifdef IPV6_SUPPORTED
         ret = cmInetConnect(&hiAccCb.curTst.fd1, 
                             (CmInetAddr *)&hiAccCb.curTst.remAddr);
#else
         ret = cmInetConnect(&hiAccCb.curTst.fd1, 
                             &hiAccCb.curTst.remAddr.u.ipv4TptAddr);
#endif /* IPV6_SUPPORTED */
         if(ret == RFAILED)
         {
            HIACCPRNERR((hiAccCb.prntBuf, 
                   "hiAccTst0: Failed to connect client Socket\n"))
            cmInetClose(&hiAccCb.curTst.fd1);
            HI_ACC_TST_FAILED();
         }

         /* Wait until connection is established */
         while(1)
         {
            timeout = 0;
            CM_INET_FD_ZERO(&writeFdS);
            CM_INET_FD_ZERO(&readFdS);
            CM_INET_FD_SET(&hiAccCb.curTst.fd1, &writeFdS);
            CM_INET_FD_SET(&hiAccCb.curTst.fd1, &readFdS);
            ret = cmInetSelect(&readFdS, &writeFdS, &timeout, &numFdS);
            if (ret == ROKDNA)
            {
               continue;
            }
            else if (ret == RFAILED)
            {
               HIACCPRNERR((hiAccCb.prntBuf, 
                        "hiAccTst0: select called failed \n"))
                  cmInetClose(&hiAccCb.curTst.fd1);
               HI_ACC_TST_FAILED();
            }
            if (CM_INET_FD_ISSET(&hiAccCb.curTst.fd1, &writeFdS))
            {
               if(CM_INET_FD_ISSET(&hiAccCb.curTst.fd1, &readFdS))
               {
                  /* both readable and writable */
                  /* ERROR case */
                  HIACCPRNERR((hiAccCb.prntBuf, 
                        "hiAccTst0: Failed to connect client Socket\n"))
                  cmInetClose(&hiAccCb.curTst.fd1);
                  HI_ACC_TST_FAILED();                  
               }
               break;
            }
         }
         hiAccCb.curTst.state++;
         break;

      case 3:  /* HitConInd */
         break;

      case 4:
         /* Send message */
         msg =  hiAccCb.tstMsgs[hiAccCb.curTst.msgIdx].msg;
         
         msgLen = hiAccCb.tstMsgs[hiAccCb.curTst.msgIdx].len;
         
#ifdef IPV6_SUPPORTED
#ifdef IPV6_OPTS_SUPPORTED
         if (cmInetSendMsg(&hiAccCb.curTst.fd1, 
                           (CmInetAddr *)&hiAccCb.curTst.remAddr, 
                           &hiAccCb.info, msg, &hiAccCb.curTst.sentLen, 
                           NULLP, CM_INET_NO_FLAG) != ROK)
#else            
         if (cmInetSendMsg(&hiAccCb.curTst.fd1, 
                           (CmInetAddr *)&hiAccCb.curTst.remAddr, 
                           &hiAccCb.info, msg, &hiAccCb.curTst.sentLen, 
                           CM_INET_NO_FLAG) != ROK)
#endif /* IPV6_OPTS_SUPPORTED */            
#else
         if (cmInetSendMsg(&hiAccCb.curTst.fd1, 
                           &hiAccCb.curTst.remAddr.u.ipv4TptAddr, 
                           &hiAccCb.info, msg, &hiAccCb.curTst.sentLen, 
                           CM_INET_NO_FLAG) != ROK)
#endif /* IPV6_SUPPORTED */
            
         {
            HIACCPRNERR((hiAccCb.prntBuf, 
                "hiAccTst0: Failed to send message on client Socket\n"))
            cmInetClose(&hiAccCb.curTst.fd1);
            HI_ACC_TST_FAILED();
         }

         if (hiAccCb.curTst.sentLen != msgLen)
         {
            HIACCPRNERR((hiAccCb.prntBuf, 
              "hiAccTst0: Not entire message sent on client Socket\n"))
            cmInetClose(&hiAccCb.curTst.fd1);
            HI_ACC_TST_FAILED();
         }

         HIACCPRINT((hiAccCb.prntBuf, 
                    "CLT: msgIdx(%d):wrote %d octets ...\n ", 
                    hiAccCb.curTst.msgIdx, hiAccCb.curTst.sentLen));
         hiAccCb.curTst.state++;
         break;

      case 5:  /* HitDatInd */
         break;

      case 6:
         echo = NULLP;
         /* Call cmInetRecvMsg only if data is to be read */ 
         timeout = 0;
         numFdS = 0;
         CM_INET_FD_ZERO(&readFdS);
         CM_INET_FD_SET(&hiAccCb.curTst.fd1, &readFdS);
         ret = cmInetSelect(&readFdS, NULLP, &timeout, &numFdS);
         if (ret == RFAILED)
         {
            HIACCPRNERR((hiAccCb.prntBuf, 
                "hiAccTst0: select called failed \n"))
            cmInetClose(&hiAccCb.curTst.fd1);
            HI_ACC_TST_FAILED();
         }
         
         /* If the socket is not set try again later */
         if (!numFdS)
            break;

         if (CM_INET_FD_ISSET(&hiAccCb.curTst.fd1, &readFdS))
         {
#ifdef IPV6_SUPPORTED
            if ((ret = cmInetRecvMsg(&hiAccCb.curTst.fd1, 
                                     (CmInetAddr *)&hiAccCb.curTst.remAddr,
                                     &hiAccCb.info, &echo, 
                                     &hiAccCb.curTst.sentLen, 
#ifdef IPV6_OPTS_SUPPORTED
                                     NULLP, 
#endif
#ifdef LOCAL_INTF
                                     NULLP,
#endif
                                     CM_INET_NO_FLAG)) != ROK)
#else
            if ((ret = cmInetRecvMsg(&hiAccCb.curTst.fd1, 
                                     &hiAccCb.curTst.remAddr.u.ipv4TptAddr, 
                                     &hiAccCb.info, &echo, 
                                     &hiAccCb.curTst.sentLen, 
#ifdef LOCAL_INTF                                     
                                     NULLP,
#endif                                     
                                     CM_INET_NO_FLAG)) != ROK)
#endif /* IPV6_SUPPORTED */
            {
               /* rokdna or rfailed */
               if (ret != ROKDNA)
               { 
                  /* ERROR CASE */ 
                  if (echo != NULLP)
                  SPutMsg(echo);  
                  HIACCPRNERR((hiAccCb.prntBuf, "read error!\n"))
                  cmInetClose(&hiAccCb.curTst.fd1);
                  HI_ACC_TST_FAILED();
               }
               else
                  /* wait for the entire packet */
                  break;
            }
            else /* rok */
            {
               /* Check message */
               if (hiAccChkMsg(hiAccCb.tstMsgs[(hiAccCb.curTst.msgIdx)].msg,
                               echo) == ROK)
               { 
                  HIACCPRINT((hiAccCb.prntBuf, "Received Echo\n"))
               }
               else
               {
                  HIACCPRNERR((hiAccCb.prntBuf, 
                     "hiAccTst0: clt rx corrupt echo from the server\n"))
                  cmInetClose(&hiAccCb.curTst.fd1);
                  HI_ACC_TST_FAILED();
               }  
            }   
         }     
      
         /* cleanup */       
         if (echo != NULLP)
            SPutMsg(echo);  
         if(!hiAccCb.curTst.errFlag)
         {
            hiAccCb.curTst.msgIdx++;
            if(hiAccCb.curTst.msgIdx==HI_ACC_NUM_TST_MSGS)
            {
               hiAccCb.curTst.state++;
            }
            else
            {
               hiAccCb.curTst.state = 4;
            }
         }
         break;

      case 7:
         {
#ifdef LHI_THR_STS
         HiMngmt mgt;
         Action action = ZEROSTS; 
         mgt.hdr.elmId.elmnt = STHITHR;
#endif /*LHI_THR_STS*/
         hiAccCb.curTst.state++;
/*hi014.105 1. Modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
         SmMiLhiStsReq(&hiAccCb.smPst,action, &mgt );
#endif /*LHI_THR_STS*/
         HIACCPRINT((hiAccCb.prntBuf, "Case 7\n"))
 
         break;
         }
      case 8:
         /* Close the server socket */
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                        HI_USER_CON_ID, HIACC_SERV_SUCON_ID, HI_CLOSE,
                        &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state++;
         break;

      case 9:
         /* Wait for a disconnect confirm */
         break;

      case 10:
         /* Close the new connection */
         HcLiHitDiscReq(&hiAccCb.uiPst,
                        HI_ACC_SAP_0, HI_USER_CON_ID,
                        HIACC_NEW_SUCON_ID, HI_CLOSE,
                        &hiAccCb.curTst.tPar);
         cmInetClose(&hiAccCb.curTst.fd1);
         HIACCPRINT((hiAccCb.prntBuf, "socket closed\n"))
         hiAccCb.curTst.state++;
         break;

      case 11:
         /* Wait for disconnect confirm */
         break;

      case 12:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         HIACCPRNERR((hiAccCb.prntBuf, "TST0:invalid acc state\n"))
         HI_ACC_TST_FAILED();
         break;
   }/* end of switch */

   if(hiAccCb.curTst.errFlag)
   {
      HcLiHitDiscReq(&hiAccCb.uiPst, 
                     HI_ACC_SAP_0, HI_USER_CON_ID, HIACC_SERV_SUCON_ID,
                     HI_CLOSE,&hiAccCb.curTst.tPar);

      if(hiAccCb.curTst.state >=2)
         HcLiHitDiscReq(&hiAccCb.uiPst, 
                        HI_ACC_SAP_0, 
                        HI_USER_CON_ID,
                        HIACC_NEW_SUCON_ID,
                        HI_CLOSE,
                        &hiAccCb.curTst.tPar);
   }
   RETVALUE(ROK);  
}/* end of hiAccTst0() */


/*
*
*       Fun:   hiAccTst1 
*
*       Desc:  This test case sets up a TCP client in TUCL and send
*              data to it from a dummy server created in the ACC
*              envelope. The client loops back the data received. The
*              server checks the integrity of the received data.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst1
(
Void
)
#else
PUBLIC S16 hiAccTst1(Void)
#endif
{

  Buffer       *msg;
  Buffer       *echo;
  MsgLen       msgLen;
  S16          ret;
  U32          optVal;
  CmInetFdSet  readFdS;
  U32          timeout;
  S16          numFdS;

  TRC2(hiAccTst1)

  switch(hiAccCb.curTst.state)
  {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;

         /* initialize the server's listening address */
         hiAccCb.curTst.locAddr.type = CM_TPTADDR_IPV4;
         hiAccCb.curTst.locAddr.u.ipv4TptAddr.address= HI_ACC_SERV_ADDR;
         hiAccCb.curTst.locAddr.u.ipv4TptAddr.port= 
                                        HI_ACC_SERV_PORT+hiAccCb.curTst.id;

         /* Start the ACC server */
#ifdef IPV6_SUPPORTED
         ret = cmInetSocket(CM_INET_STREAM, &hiAccCb.curTst.fd1, 0,
                            CM_INET_IPV4_DOMAIN);
#else
         ret = cmInetSocket(CM_INET_STREAM, &hiAccCb.curTst.fd1, 0);
#endif /* IPV6_SUPPORTED */
         if (ret != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst1: open failed \n"))
            HI_ACC_TST_FAILED();
         }

         optVal = CM_SOCKOPT_ENABLE;
         ret = cmInetSetOpt(&hiAccCb.curTst.fd1, CM_SOCKOPT_LEVEL_SOCKET, 
                            CM_SOCKOPT_OPT_REUSEADDR, (Ptr)&optVal);
         if(ret != ROK)
         { 
            HIACCPRNERR((hiAccCb.prntBuf, 
              "hiAccTst1: failed to set options \n"))
            cmInetClose(&hiAccCb.curTst.fd1);

            hiAccCb.curTst.state = HI_ACC_ST_END;
            hiAccCb.curTst.result = HI_TST_FAILED;
            hiAccCb.curTst.errFlag = TRUE;
            RETVALUE(RFAILED);
         }
/* hi002.105 (hi029.104) */
#ifdef HIACC_PRIVILEDGED_MODE

         optVal = CM_SOCKOPT_ENABLE;
         ret = cmInetSetOpt(&hiAccCb.curTst.fd1, CM_SOCKOPT_LEVEL_SOCKET, 
                            CM_SOCKOPT_OPT_TCP_NODELAY, (Ptr)&optVal);
         if(ret != ROK)
         { 
            HIACCPRNERR((hiAccCb.prntBuf, 
              "hiAccTst1: failed to set options \n"))
            cmInetClose(&hiAccCb.curTst.fd1);

            hiAccCb.curTst.state = HI_ACC_ST_END;
            hiAccCb.curTst.result = HI_TST_FAILED;
            hiAccCb.curTst.errFlag = TRUE;
            RETVALUE(RFAILED);
         }
#endif /* ifdef PRIVILEDGED MODE */
#ifdef IPV6_SUPPORTED
         ret = cmInetBind(&hiAccCb.curTst.fd1, 
                          (CmInetAddr *)&hiAccCb.curTst.locAddr);
#else
         ret = cmInetBind(&hiAccCb.curTst.fd1, 
                          &hiAccCb.curTst.locAddr.u.ipv4TptAddr);
#endif /* IPV6_SUPPORTED */
         if (ret != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst1 : bind failed\n"))
            cmInetClose(&hiAccCb.curTst.fd1);

            hiAccCb.curTst.state = HI_ACC_ST_END;
            hiAccCb.curTst.result = HI_TST_FAILED;
            hiAccCb.curTst.errFlag = TRUE;
            RETVALUE(RFAILED);
         }
#ifdef WIN32
         ret = cmInetListen(&hiAccCb.curTst.fd1, 1);
#else
         ret = cmInetListen(&hiAccCb.curTst.fd1, 5);
#endif /* WIN32 */
         if (ret != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst1 : listen failed\n"))
            cmInetClose(&hiAccCb.curTst.fd1);

            hiAccCb.curTst.state = HI_ACC_ST_END;
            hiAccCb.curTst.result = HI_TST_FAILED;
            hiAccCb.curTst.errFlag = TRUE;
            RETVALUE(RFAILED);
         }
         hiAccCb.curTst.state++;
         break;
         
      case 1:
         /* Request HI to open a TCP Client */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_NOTPRSNT;
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 0;
         HIACC_OPEN_TCP_CLT(HIACC_CLT_SUCON_ID,
                            &hiAccCb.curTst.locAddr,
                            &hiAccCb.curTst.remAddr, 
                            &hiAccCb.curTst.tPar,
                            HI_SRVC_TCP_TPKT_HDR);

         hiAccCb.curTst.state++;
         break;

      case 2:
         /* Client wait for connection */
         /* State incremented on getting ConCfm */
         /* to give scheduling to hiScanPermTsk */
         break;

      case 3:
         /* Wait for Client connection */
         while(1)
         {      
#ifdef IPV6_SUPPORTED
            if (cmInetAccept(&hiAccCb.curTst.fd1, 
                             (CmInetAddr *)&hiAccCb.curTst.remAddr, 
                             &hiAccCb.curTst.fd2) == ROK)
#else
            if (cmInetAccept(&hiAccCb.curTst.fd1, 
                             &hiAccCb.curTst.remAddr.u.ipv4TptAddr, 
                             &hiAccCb.curTst.fd2) == ROK)
#endif /* IPV6_SUPPORTED */
            {
               hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV4;
               break;
            }
            else
            {
               HIACCPRINT((hiAccCb.prntBuf, "hiAccTst1: wait"))
            }
         }

         HIACCPRINT((hiAccCb.prntBuf, "hiAccTst1: connection established\n"))

   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
         HIACCPRINT((hiAccCb.prntBuf, 
           "hiAccTst1: connection from : adr(0x%lx) port(%d)\n", 
           hiAccCb.curTst.remAddr.u.ipv4TptAddr.address, 
           hiAccCb.curTst.remAddr.u.ipv4TptAddr.port));
#else
         HIACCPRINT((hiAccCb.prntBuf, 
           "hiAccTst1: connection from : adr(0x%x) port(%d)\n", 
           hiAccCb.curTst.remAddr.u.ipv4TptAddr.address, 
           hiAccCb.curTst.remAddr.u.ipv4TptAddr.port));
#endif

         hiAccCb.curTst.state++;
        /* FALL THRU */

      case 4:
         /* send message */
         msg =  hiAccCb.tstMsgs[hiAccCb.curTst.msgIdx].msg;

         /* Send Data to the HI client */
#ifdef IPV6_SUPPORTED
#ifdef IPV6_OPTS_SUPPORTED
         if (cmInetSendMsg(&hiAccCb.curTst.fd2, 
                           (CmInetAddr *)&hiAccCb.curTst.remAddr,
                           &hiAccCb.info, msg, &hiAccCb.curTst.sentLen, 
                           NULLP, CM_INET_NO_FLAG) != ROK)
#else
         if (cmInetSendMsg(&hiAccCb.curTst.fd2, 
                           (CmInetAddr *)&hiAccCb.curTst.remAddr,
                           &hiAccCb.info, msg, &hiAccCb.curTst.sentLen, 
                           CM_INET_NO_FLAG) != ROK)
#endif /* IPV6_OPTS_SUPPORTED */            
#else
         if (cmInetSendMsg(&hiAccCb.curTst.fd2, 
                           &hiAccCb.curTst.remAddr.u.ipv4TptAddr,
                           &hiAccCb.info, msg, &hiAccCb.curTst.sentLen, 
                           CM_INET_NO_FLAG) != ROK)
#endif /* IPV6_SUPPORTED */
         {
            HIACCPRNERR((hiAccCb.prntBuf, 
              "hiAccTst1: Failed to send message on server Socket\n"))
            cmInetClose(&hiAccCb.curTst.fd1);
            cmInetClose(&hiAccCb.curTst.fd2);
            HI_ACC_TST_FAILED();
         }

         /* Check the sent length */
         msgLen = hiAccCb.tstMsgs[hiAccCb.curTst.msgIdx].len;
         if (hiAccCb.curTst.sentLen != msgLen)
         {
            HIACCPRNERR((hiAccCb.prntBuf, 
              "hiAccTst1: Not entire message sent on server Socket\n"))
            cmInetClose(&hiAccCb.curTst.fd1);
            cmInetClose(&hiAccCb.curTst.fd2);
            HI_ACC_TST_FAILED();
         }
         hiAccCb.curTst.state++;
         break;

      case 5:
         /* state incrmented on getting DatInd in the HI CLT */
         break;

      case 6: 
         /* Receive the Client's echo */
         echo = NULLP;

         /* Call cmInetRecvMsg only if data is to be read */ 
         timeout = 0;
         numFdS = 0;
         CM_INET_FD_ZERO(&readFdS);
         CM_INET_FD_SET(&hiAccCb.curTst.fd2, &readFdS);
         ret = cmInetSelect(&readFdS, NULLP, &timeout, &numFdS);
         if (ret == RFAILED)
         {
            HIACCPRNERR((hiAccCb.prntBuf, 
                "hiAccTst1: select called failed \n"))
            cmInetClose(&hiAccCb.curTst.fd1);
            HI_ACC_TST_FAILED();
         }
         
         /* If the socket is not set try again later */
         if (!numFdS)
            break;
         
         if (CM_INET_FD_ISSET(&hiAccCb.curTst.fd2, &readFdS))
         {
#ifdef IPV6_SUPPORTED          
            if ((ret = cmInetRecvMsg(&hiAccCb.curTst.fd2, 
                                     (CmInetAddr *)&hiAccCb.curTst.remAddr,
                                     &hiAccCb.info, &echo, 
                                     &hiAccCb.curTst.sentLen,
#ifdef IPV6_OPTS_SUPPORTED                                       
                                     NULLP, 
#endif
#ifdef LOCAL_INTF                                     
                                     NULLP,
#endif                                     
                                     CM_INET_NO_FLAG)) != ROK)
               
#else
            if ((ret = cmInetRecvMsg(&hiAccCb.curTst.fd2, 
                                     &hiAccCb.curTst.remAddr.u.ipv4TptAddr, 
                                     &hiAccCb.info, &echo, 
                                     &hiAccCb.curTst.sentLen, 
#ifdef LOCAL_INTF                                     
                                     NULLP,
#endif                                     
                                     CM_INET_NO_FLAG)) != ROK)
#endif /* IPV6_SUPPORTED */
            {
               /* rokdna or rfailed */
               if (ret != ROKDNA)
               { 
                 /* ERROR CASE */ 
                 if (echo != NULLP)
                   SPutMsg(echo);  

                 HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst1: READ ERROR!\n"))
                 cmInetClose(&hiAccCb.curTst.fd1);
                 cmInetClose(&hiAccCb.curTst.fd2);
                 HI_ACC_TST_FAILED();
               }
               else
                  break;
            }
            else /* rok*/
            {
               if (hiAccChkMsg(hiAccCb.tstMsgs[(hiAccCb.curTst.msgIdx)].msg,
                    echo) == ROK)
               { 
                  HIACCPRINT((hiAccCb.prntBuf, "Received Echo\n"))
               }
               else
               {
                  HIACCPRNERR((hiAccCb.prntBuf, 
                    "hiAccTst1: clt rx CoRrUpT echo from the server\n"))
                  cmInetClose(&hiAccCb.curTst.fd1);
                  cmInetClose(&hiAccCb.curTst.fd2);
                  HI_ACC_TST_FAILED();
               }  

            }/* end else */
         }/* end while */     

            /* cleanup */       
         if (echo != NULLP)
            SPutMsg(echo);  

         if(!hiAccCb.curTst.errFlag)
         {
            hiAccCb.curTst.msgIdx++;
            if(hiAccCb.curTst.msgIdx == HI_ACC_NUM_TST_MSGS)
            {
               hiAccCb.curTst.state++;
            }
            else
            {
               /* send the next message */
               hiAccCb.curTst.state = 4;
            }
         }
         break;

      case 7:
         /* Close the HI client */
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                        HI_USER_CON_ID, HIACC_CLT_SUCON_ID,
                        HI_CLOSE, &hiAccCb.curTst.tPar);             

         cmInetClose(&hiAccCb.curTst.fd1);
         cmInetClose(&hiAccCb.curTst.fd2);

         HIACCPRINT((hiAccCb.prntBuf, "hiAccTst1 :socket closed\n"))

         /* Initialize transport parameters */
         hiAccCb.curTst.state++;
         break;

      case 8:
         /* Wait for either DiscCfm or DiscInd */
         break;

      case 9:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst1: invalid acc state\n"))
         HI_ACC_TST_FAILED();
         break;

   }/* end of switch */

   if(hiAccCb.curTst.errFlag)
   {
      HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                     HI_USER_CON_ID, HIACC_CLT_SUCON_ID,
                     HI_CLOSE, &hiAccCb.curTst.tPar);
      cmInetClose(&hiAccCb.curTst.fd1);
      cmInetClose(&hiAccCb.curTst.fd2);
   }

   RETVALUE(ROK);  
}/* end of hiAccTst1 */


/* hi028.201: Modified test case hiAccTst2*/
/*
*
*       Fun:   hiAccTst2
*
*       Desc:  This test case opens HIACC_UDP_MAX_SERV number of TUCL
*              UDP servers. It then sends a message to each of these
*              servers from tstTbl array. The data received by the
*              servers is compared in HcLiHitUDatInd (in layer3.c). In
*              case all the messages received are correct, the test case
*              closes all TUCL servers.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst2
(
Void
)
#else
PUBLIC S16 hiAccTst2()
#endif
{

   Buffer         *msg, *msg1;
   U32            i;
   static U8      cnt = 0;
   CmTptAddr      nullAddr;
   CmIcmpFilter   nullFilter;
   CmIpHdrParm    nullHdr;
   CmTptParam     tPar;

   TRC2(hiAccTst2)

   HI_ZERO((U8*)&nullAddr, sizeof(CmTptAddr));
   HI_ZERO((U8*)&nullFilter, sizeof(CmIcmpFilter));
   HI_ZERO((U8*)&nullHdr, sizeof(CmIpHdrParm));
   HI_ZERO((U8*)&tPar, sizeof(CmTptParam));
   
   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;

         /* Initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV4;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.address =  HI_ACC_SERV_ADDR;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_2;

         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
         /*hi002.105 (hi029.104) */
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 1;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option = 
                                            CM_SOCKOPT_OPT_REUSEADDR;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level  = 
                                            CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
#ifdef SS_LINUX
#ifdef LOCAL_INTF         
         /* this is to test the getting of intf addr for UDP IPv4 socket */ 
         hiAccCb.curTst.tPar.u.sockParam.numOpts++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].option =
                                             CM_SOCKOPT_OPT_IPV4_PKTINFO;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].level  =
                                              CM_SOCKOPT_LEVEL_IP;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].optVal.value =
                                              CM_SOCKOPT_ENABLE;
#endif         
#endif /* SS_LINUX */


         for(i = 0; i < HIACC_UDP_MAX_SERV; i++)
         {
            HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
            nullFilter.type = CM_ICMP_NO_FILTER;
            HcLiHitServOpenReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                               i, &hiAccCb.curTst.remAddr, 
                               &hiAccCb.curTst.tPar, &nullFilter, 
                               HI_SRVC_UDP);
            hiAccCb.curTst.remAddr.u.ipv4TptAddr.port += 1;
         }

         hiAccCb.curTst.state++;
         break;

      case 1:
         break;

      case 2:
         cnt++;
         if (cnt <  HIACC_UDP_MAX_SERV)
         {
            hiAccCb.curTst.state--;
         }
         else
         {
            hiAccCb.curTst.state++;
            cnt =0;
         }
         break;

      case 3:
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_2;
         /* Send data */
         for(i=0; i< HIACC_UDP_MAX_SERV; i++)
         {
            msg =  hiAccCb.tstMsgs[i].msg;
            if(SAddMsgRef(msg, hiAccCb.init.region, 
                          hiAccCb.init.pool, &msg1) != ROK)
            {
               HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst2: mem error!\n"))
               HI_ACC_TST_FAILED();
            }
            HITST_ZERO(&nullAddr, sizeof(CmTptAddr));
            nullAddr.type = CM_TPTADDR_NOTPRSNT;

            HITST_ZERO(&nullHdr, sizeof(CmIpHdrParm));
            nullHdr.type = CM_HDRPARM_NOTPRSNT;
            tPar.type = CM_TPTPARAM_NOTPRSNT;
            HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 0, 
                           &hiAccCb.curTst.remAddr, &nullAddr, 
                           &nullHdr, &tPar, msg1);
            hiAccCb.curTst.remAddr.u.ipv4TptAddr.port += 1;
         }
         hiAccCb.curTst.state++;
         break;

      case 4:
         /*Waiting for DatInd */
         SThreadYield();
         break;

      case 5:
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_2;
         /* Disconnect all the servers */
         for(i=0; i<HIACC_UDP_MAX_SERV; i++)
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                        "hiAccTst2:Disconnecting UDP servers\n"))
            hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
            HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                           HI_USER_CON_ID, i, HI_CLOSE, &hiAccCb.curTst.tPar);
            hiAccCb.curTst.remAddr.u.ipv4TptAddr.port += 1;
         }
         hiAccCb.curTst.state++;
         break;

      case 6:
         break;

      case 7:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;

      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_2;
         for(i=0; i<HIACC_UDP_MAX_SERV; i++)
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                        "hiAccTst2:Disconnecting UDP servers\n"))
            hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
            HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                           HI_USER_CON_ID, i, HI_CLOSE, &hiAccCb.curTst.tPar);
            hiAccCb.curTst.remAddr.u.ipv4TptAddr.port += 1;
         }
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;

   }/* end switch */

   RETVALUE(ROK);  
}/* end of hiAccTst2 */


/*
*
*       Fun:   hiAccTst3
*
*       Desc:  This function open a TUCL multicast listener, open two
*              ACC clients. Each client sends data to the server. First
*              client sends data on server's mulitcast address and the
*              second client sends data on the server's unicast address.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst3
(
Void
)
#else
PUBLIC S16 hiAccTst3()
#endif
{

#ifdef HI_ACC_MCAST_ENB

   Buffer *msg;
   MsgLen  msgLen;
   CmTptAddr      nullAddr;
   CmIcmpFilter   nullFilter;
   CmIpHdrParm    nullHdr;
   CmTptParam     tPar;

   TRC2(hiAccTst3)

   HI_ZERO((U8*)&nullAddr, sizeof(CmTptAddr));
   HI_ZERO((U8*)&nullFilter, sizeof(CmIcmpFilter));
   HI_ZERO((U8*)&nullHdr, sizeof(CmIpHdrParm));
   HI_ZERO((U8*)&tPar, sizeof(CmTptParam));

   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;

         /* initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV4;

         hiAccCb.curTst.remAddr.u.ipv4TptAddr.address = CM_INADDR_ANY;
         
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                     (HI_ACC_SERV_PORT+ hiAccCb.curTst.id+
                                     HIACC_UDP_MAX_SERV);

         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 2;

         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level =
                                             CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option =
                                             CM_SOCKOPT_OPT_TX_BUF_SIZE;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.value = 1000;

         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].level =
                                             CM_SOCKOPT_LEVEL_IP;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].option =
                                             CM_SOCKOPT_OPT_ADD_MCAST_MBR;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].optVal.mCastInfo.
                                               mCastAddr.type = CM_NETADDR_IPV4;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].optVal.mCastInfo.
                                mCastAddr.u.ipv4NetAddr = HI_ACC_MCAST_IPV4ADDR;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].optVal.mCastInfo.
                                               localAddr.type = CM_NETADDR_IPV4;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].optVal.mCastInfo.
                                   localAddr.u.ipv4NetAddr = CM_INET_INADDR_ANY;

         /* Create a UDP HI Server */
         HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
         nullFilter.type = CM_ICMP_NO_FILTER;
         
         HcLiHitServOpenReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                            HIACC_SERV_SUCON_ID, 
                            &hiAccCb.curTst.remAddr, 
                            &hiAccCb.curTst.tPar, &nullFilter, 
                            HI_SRVC_UDP_PRIOR);
         hiAccCb.curTst.state++;
         break;

      case 1:
         /* wait for  HitConCfm */
         break;

      case 2:
         msgLen = hiAccCb.tstMsgs[hiAccCb.curTst.msgIdx].len;

         if(SAddMsgRef(hiAccCb.tstMsgs[hiAccCb.curTst.msgIdx].msg, 
             hiAccCb.init.region, hiAccCb.init.pool, &msg) != ROK)
         {
               HIACCPRNERR((hiAccCb.prntBuf, 
                  "hiAccTst3: memory error!\n"))
               HI_ACC_TST_FAILED();
         }

         /* send the message to server mCast address */
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.address = 
                                              HI_ACC_MCAST_IPV4ADDR;

         /* send data */
         HITST_ZERO(&nullAddr, sizeof(CmTptAddr));
         nullAddr.type = CM_TPTADDR_NOTPRSNT;

         HITST_ZERO(&nullHdr, sizeof(CmIpHdrParm));
         nullHdr.type = CM_HDRPARM_NOTPRSNT;
        
         tPar.type = CM_TPTPARAM_SOCK;
         tPar.u.sockParam.numOpts = 0;
         tPar.u.sockParam.sockOpts[0].level = CM_INET_LEVEL_IP; 
         tPar.u.sockParam.sockOpts[0].option = CM_SOCKOPT_OPT_MCAST_TTL;
         tPar.u.sockParam.sockOpts[0].optVal.value = 3;

         HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                        hiAccCb.curTst.cltSpConId,
                        &hiAccCb.curTst.remAddr, &nullAddr, 
                        &nullHdr, &tPar, msg);

         if(hiAccCb.curTst.prntFlag)
         {
            sprintf(hiAccCb.prntBuf, 
                    "hiAccTst3: msgIdx(%d):wrote %d octets ...\n ", 
                     hiAccCb.curTst.msgIdx, msgLen);
            SPrint(hiAccCb.prntBuf);
         }

         hiAccCb.curTst.remAddr.u.ipv4TptAddr.address = 
                                              HI_ACC_MCAST_IPV4ADDR;
         if(SAddMsgRef(hiAccCb.tstMsgs[hiAccCb.curTst.msgIdx].msg, 
             hiAccCb.init.region, hiAccCb.init.pool, &msg) != ROK)
         {
               HIACCPRNERR((hiAccCb.prntBuf, 
                  "hiAccTst3: memory error!\n"))
               HI_ACC_TST_FAILED();
         }

         HITST_ZERO(&nullAddr, sizeof(CmTptAddr));
         nullAddr.type = CM_TPTADDR_NOTPRSNT;

         HITST_ZERO(&nullHdr, sizeof(CmIpHdrParm));
         nullHdr.type = CM_HDRPARM_NOTPRSNT;
         
         tPar.type = CM_TPTPARAM_NOTPRSNT;
         HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                        0, &hiAccCb.curTst.remAddr, &nullAddr, 
                        &nullHdr, &tPar, msg);

         if(hiAccCb.curTst.prntFlag)
         {
            sprintf(hiAccCb.prntBuf, 
                    "hiAccTst3: msgIdx(%d):wrote %d octets ...\n ", 
                    hiAccCb.curTst.msgIdx, msgLen);
            SPrint(hiAccCb.prntBuf);
         }
         hiAccCb.curTst.state++;
         break;

      case 3: /* wait for first UDatInd in layer3.c */
         break;

      case 4: /* wait for second UDatInd in layer3.c */
         break;

      case 5:
         if(!hiAccCb.curTst.errFlag)
         {
            hiAccCb.curTst.msgIdx++;
            if(hiAccCb.curTst.msgIdx==HI_ACC_NUM_TST_MSGS)
            {
               hiAccCb.curTst.state++;
            }
            else
            {
               hiAccCb.curTst.state = 2;
            }
         }
         break;

      case 6:

         /* leave the mcast group for the server */
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 1;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level =
                                             CM_SOCKOPT_LEVEL_IP;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option =
                                             CM_SOCKOPT_OPT_DRP_MCAST_MBR;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.mCastInfo.
                                               mCastAddr.type = CM_NETADDR_IPV4;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.mCastInfo.
                                mCastAddr.u.ipv4NetAddr = HI_ACC_MCAST_IPV4ADDR;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.mCastInfo.
                                               localAddr.type = CM_NETADDR_IPV4;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.mCastInfo.
                                   localAddr.u.ipv4NetAddr = CM_INET_INADDR_ANY;
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_USER_CON_ID,
                        HIACC_SERV_SUCON_ID, HI_LEAVE_MCAST_GROUP, 
                        &hiAccCb.curTst.tPar);

         /* Close the server */
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_USER_CON_ID,
                        HIACC_SERV_SUCON_ID, HI_CLOSE, &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state++;
         break;

      case 7:
         break;

      case 8:
         break;

      case 9: 
         hiAccCb.curTst.result = HI_TST_OK;
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;

      default:
         HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst3:invalid acc state\n"))
         HI_ACC_TST_FAILED();
         break;
   }

   if(hiAccCb.curTst.errFlag)
   {
      hiAccCb.curTst.state = HI_ACC_ST_END;
      HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_USER_CON_ID,
                     HIACC_SERV_SUCON_ID, HI_CLOSE, &hiAccCb.curTst.tPar);
   }
#endif /* HI_ACC_MCAST_ENB */

   RETVALUE(ROK);  
}/* end of hiAccTst3() */


/*
*
*       Fun:   hiAccTst4
*
*       Desc:  This test case opens a TUCL TCP server and transfers data
*              from the server to the ACC client. The data transmitted
*              is TCP octet stream.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None 
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst4
(
Void
)
#else
PUBLIC S16 hiAccTst4()
#endif
{

   Buffer       *msg;
   Buffer       *echo;  
   S16          ret;

   /* select related definitions */
   CmInetFdSet  readFdS;
   U32          timeout;
   S16          numFdS;
   CmIcmpFilter nullFilter;

   TRC2(hiAccTst4)

   HI_ZERO((U8*)&readFdS, sizeof(CmInetFdSet));   
   HI_ZERO((U8*)&nullFilter, sizeof(CmIcmpFilter));
      
   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;

         /* Initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV4;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.address =  HI_ACC_SERV_ADDR;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                      (HI_ACC_SERV_PORT+hiAccCb.curTst.id+
                                      HIACC_UDP_MAX_SERV+5);

         /* Initialize transport parameters */
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 1;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option = 
                                            CM_SOCKOPT_OPT_REUSEADDR;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level  = 
                                            CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.value = 
                                            CM_SOCKOPT_ENABLE;

#ifdef WIN32
         hiAccCb.curTst.tPar.u.sockParam.listenQSize = 1;
#else
         hiAccCb.curTst.tPar.u.sockParam.listenQSize = 5;
#endif /* WIN32 */

         /* Request HI to open a TCP Server */
         HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
         nullFilter.type = CM_ICMP_NO_FILTER;

         HIACC_OPEN_TCP_SRV(HIACC_SERV_SUCON_ID, &hiAccCb.curTst.remAddr, 
                            &hiAccCb.curTst.tPar, &nullFilter, 
                            HI_SRVC_TCP_NO_HDR);

         hiAccCb.curTst.state++;
         break;

      case 1:
         break;

      case 2:
         /* Open a TCP Client */

         /* Open a new socket */
#ifdef IPV6_SUPPORTED
         ret = cmInetSocket(CM_INET_STREAM, &hiAccCb.curTst.fd1, 0,
                            CM_INET_IPV4_DOMAIN);
#else
         ret = cmInetSocket(CM_INET_STREAM, &hiAccCb.curTst.fd1, 0);
#endif /* IPV6_SUPPORTED */
         if (ret != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, 
                         "hiAccTst4: Failed to Open Socket\n"))
            HI_ACC_TST_FAILED();
         }

#ifdef IPV6_SUPPORTED
         ret = cmInetConnect(&hiAccCb.curTst.fd1, 
                             (CmInetAddr *)&hiAccCb.curTst.remAddr);
#else
         ret = cmInetConnect(&hiAccCb.curTst.fd1, 
                             &hiAccCb.curTst.remAddr.u.ipv4TptAddr);
#endif /* IPV6_SUPPORTED */
         if((ret != ROK) && (ret != RINPROGRESS) && (ret!= ROKDNA))
         {
            HIACCPRNERR((hiAccCb.prntBuf, 
                         "hiAccTst4: Failed to connect\n"))
            cmInetClose(&hiAccCb.curTst.fd1);
            HI_ACC_TST_FAILED();
         }
         hiAccCb.curTst.state++;
         break;

      case 3:
         break;

      case 4:
         if(SAddMsgRef(hiAccCb.tstMsgs[hiAccCb.curTst.msgIdx].msg, 
                 hiAccCb.init.region, hiAccCb.init.pool, &msg) != ROK)
         {
               HIACCPRNERR((hiAccCb.prntBuf, 
                  "hiAccTst4: memory error!\n"))
               cmInetClose(&hiAccCb.curTst.fd1);
               HI_ACC_TST_FAILED();
         }

         HcLiHitDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                       hiAccCb.curTst.newSpConId, msg);

         hiAccCb.curTst.state++;
         break;

      case 5:
         echo = NULLP;
         /* Call cmInetRecvMsg only if data is to be read */ 
         timeout = 0;
         numFdS = 0;
         CM_INET_FD_ZERO(&readFdS);
         CM_INET_FD_SET(&hiAccCb.curTst.fd1, &readFdS);
         ret = cmInetSelect(&readFdS, NULLP, &timeout, &numFdS);
         if (ret == RFAILED)
         {
            HIACCPRNERR((hiAccCb.prntBuf, 
                "hiAccTst4: select called failed \n"))
            cmInetClose(&hiAccCb.curTst.fd1);
            HI_ACC_TST_FAILED();
         }
         
         /* If the socket is not set try again later */
         if (!numFdS)
            break;

         if (CM_INET_FD_ISSET(&hiAccCb.curTst.fd1, &readFdS))
         {
#ifdef IPV6_SUPPORTED 
            if ((ret = cmInetRecvMsg(&hiAccCb.curTst.fd1, 
                                     (CmInetAddr *)&hiAccCb.curTst.remAddr,
                                     &hiAccCb.info, &echo, 
                                &(hiAccCb.tstMsgs[hiAccCb.curTst.msgIdx].len),
#ifdef IPV6_OPTS_SUPPORTED                                
                                     NULLP, 
#endif
#ifdef LOCAL_INTF                                     
                                     NULLP,
#endif                                      
                                     CM_INET_NO_FLAG)) != ROK)
               
#else
            if ((ret = cmInetRecvMsg(&hiAccCb.curTst.fd1, 
                                     &hiAccCb.curTst.remAddr.u.ipv4TptAddr, 
                                     &hiAccCb.info, &echo, 
                                 &(hiAccCb.tstMsgs[hiAccCb.curTst.msgIdx].len),
#ifdef LOCAL_INTF                                 
                                     NULLP,
#endif                                     
                                     CM_INET_NO_FLAG)) != ROK)
#endif /* IPV6_SUPPORTED */
            {
               /* rokdna or rfailed */
               if (ret != ROKDNA)
               { 
                  /* ERROR CASE */ 
                  if (echo != NULLP)
                     SPutMsg(echo);  

                  HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst4:read error!\n"))
                  cmInetClose(&hiAccCb.curTst.fd1);
                  HI_ACC_TST_FAILED();
               }
               else
                  break;
            }
            else /* rok */
            {
               if (hiAccChkMsg(hiAccCb.tstMsgs[(hiAccCb.curTst.msgIdx)].msg, 
                               echo) == ROK)
               { 
                  HIACCPRINT((hiAccCb.prntBuf, 
                              "hiAccTst4: Rx Echo:msgIdx(%d)\n", 
                               hiAccCb.curTst.msgIdx));
               }
               else
               {
                  HIACCPRNERR((hiAccCb.prntBuf, 
                               "hiAccTst4: Rx CoRrUpT echo \n"))
                  cmInetClose(&hiAccCb.curTst.fd1);
                  HI_ACC_TST_FAILED();
               }  
            }   
         }     
        
         /* cleanup */       
         if (echo != NULLP)
            SPutMsg(echo);  
        
         if(!hiAccCb.curTst.errFlag)
         {
            hiAccCb.curTst.msgIdx++;
            if(hiAccCb.curTst.msgIdx==HI_ACC_NUM_TST_MSGS)
            {
               hiAccCb.curTst.state++;
            }
            else
            {
               hiAccCb.curTst.state = 4;
            }
         }
         break;

     case 6:
         /* Close the new connection */
         HIACCPRINT((hiAccCb.prntBuf, "socket closed\n"))
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                        HI_PROVIDER_CON_ID,
                        hiAccCb.curTst.newSpConId, 
                        HI_CLOSE,
                        &hiAccCb.curTst.tPar);
         /* Close the server socket */
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_USER_CON_ID,
                        HIACC_SERV_SUCON_ID, HI_CLOSE, 
                          &hiAccCb.curTst.tPar);
         cmInetClose(&hiAccCb.curTst.fd1);
         hiAccCb.curTst.state++;
         break;

     case 7:
         break;

     case 8:
         break;

     case 9:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

     default:
         HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst4:invalid acc state\n"))
         HI_ACC_TST_FAILED();
         break;

   }/* end of switch */

   if(hiAccCb.curTst.errFlag)
   {
      HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_USER_CON_ID,
                     HIACC_SERV_SUCON_ID, HI_CLOSE,
                     &hiAccCb.curTst.tPar);

      if(hiAccCb.curTst.state >=3)
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_USER_CON_ID,
                        HIACC_NEW_SUCON_ID, HI_CLOSE,
                        &hiAccCb.curTst.tPar);
   }

   RETVALUE(ROK);  
}/* end of hiAccTst4 */

/* hi026.201 1. Fixed the Test case5 */

/*
*
*       Fun:   hiAccTst5
*
*       Desc:  Open a TCP client and a TCP server and transfer data.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst5
(
Void
)
#else
PUBLIC S16 hiAccTst5()
#endif
{

   S16    i;
   Buffer *msg, *msg1;
   CmIcmpFilter nullFilter;

   TRC2(hiAccTst5)

   HI_ZERO((U8*)&nullFilter, sizeof(CmIcmpFilter));
   
   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;

         /* Initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV4;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.address = HI_ACC_SERV_ADDR;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                  HI_ACC_SERV_PORT + hiAccCb.curTst.id;

         hiAccCb.curTst.locAddr.type = CM_TPTADDR_IPV4;
         hiAccCb.curTst.locAddr.u.ipv4TptAddr.address = HI_ACC_SERV_ADDR;
         hiAccCb.curTst.locAddr.u.ipv4TptAddr.port = 
                                  HI_ACC_SERV_PORT + hiAccCb.curTst.id+1;

         /* Initialize transport parameters */
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 1;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option = 
                                            CM_SOCKOPT_OPT_REUSEADDR;

         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level  = 
                                            CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
/*hi002.105 (hi029.104) */
#ifdef HIACC_PRIVILEDGED_MODE

         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].option = 
                                            CM_SOCKOPT_OPT_TCP_NODELAY;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].level  = 
                                            CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 2;
#endif 
#ifdef WIN32
         hiAccCb.curTst.tPar.u.sockParam.listenQSize = 1;
#else
         hiAccCb.curTst.tPar.u.sockParam.listenQSize = 5;
#endif /* WIN32 */

         /* Request HI to open a TCP Server */
         HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
         nullFilter.type = CM_ICMP_NO_FILTER;
         HIACC_OPEN_TCP_SRV(HIACC_SERV_SUCON_ID, &hiAccCb.curTst.remAddr, 
                            &hiAccCb.curTst.tPar, &nullFilter, 
                            HI_SRVC_TCP_TPKT_HDR);

         /* Open a TCP Client */
        hiAccCb.curTst.locAddr.type = CM_TPTADDR_NOTPRSNT;

 
        HIACC_OPEN_TCP_CLT((HIACC_CLT_SUCON_ID),
                            &hiAccCb.curTst.remAddr,
                            &hiAccCb.curTst.locAddr,
                            &hiAccCb.curTst.tPar,
                            HI_SRVC_TCP_TPKT_HDR);
         hiAccCb.curTst.state++;
         break;

      case 1:
         /* wait here for two conCfm */
         break;

      case 2:
         break;

      case 3:
         break;
         /* HitConInd in layer3.c gives back HitConRsp with 
          * suConId = HIACC_NEW_SUCON_ID
          */
         /* Data tx is now possible */

      case 4:
         /* Pump messages on the new accepted connection */
         for (i=0; i< HI_ACC_NUM_TST_MSGS; i++)
         {
            msg1 = hiAccCb.bigMsg.msg;
            if(SAddMsgRef(msg1, hiAccCb.init.region, 
                          hiAccCb.init.pool, &msg) != ROK)
            {
               HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst5: mem error!\n"))
               HI_ACC_TST_FAILED();
            }
            hiAccCb.curTst.msgIdx++;
            HcLiHitDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                          hiAccCb.curTst.newSpConId, msg);
         }
         hiAccCb.curTst.state++;
         break;

      case 5:
         /* Wait for messages to be looped back to the server */
         break;

      case 6:
         /* Close all connections */
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                        HI_USER_CON_ID, HIACC_SERV_SUCON_ID, HI_CLOSE,
                        &hiAccCb.curTst.tPar);
         
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                        HI_USER_CON_ID, HIACC_CLT_SUCON_ID, HI_CLOSE,
                        &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state++;
         break;

      case 7:
         break;

      case 8:
         break;

      case 9:
         hiAccCb.curTst.state++;
         break;

      case 10:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         break;
   }

   if(hiAccCb.curTst.errFlag)
   {
      HcLiHitDiscReq(&hiAccCb.uiPst, 
                     HI_ACC_SAP_0, HI_USER_CON_ID, 
                     HIACC_SERV_SUCON_ID,
                     HI_CLOSE, &hiAccCb.curTst.tPar);
      
      HcLiHitDiscReq(&hiAccCb.uiPst, 
                     HI_ACC_SAP_0, 
                     HI_USER_CON_ID,
                     HIACC_CLT_SUCON_ID,
                     HI_CLOSE,&hiAccCb.curTst.tPar);

      HcLiHitDiscReq(&hiAccCb.uiPst, 
                     HI_ACC_SAP_0, 
                     HI_USER_CON_ID,
                     HIACC_NEW_SUCON_ID,
                     HI_CLOSE,&hiAccCb.curTst.tPar);
   }
   RETVALUE(ROK);  
}/* end of hiAccTst5 */


/*
*
*       Fun:   hiAccTst6
*
*       Desc:  This test case opens a UDP server with TPKT service type.
*              A TPKT message is sent to the UDP server. This tests the 
*              TPKT processing in the TUCL layer. This also tests the 
*              ConReq primitive for UDP sockets.
*              
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst6
(
Void
)
#else
PUBLIC S16 hiAccTst6()
#endif
{
   Buffer         *msg, *msg1;
   CmTptAddr      nullAddr;
   CmIcmpFilter   nullFilter;
   CmIpHdrParm    nullHdr;
   CmTptParam     tPar;

   TRC2(hiAccTst6)

   HI_ZERO((U8*)&nullAddr, sizeof(CmTptAddr));
   HI_ZERO((U8*)&nullFilter, sizeof(CmIcmpFilter));
   HI_ZERO((U8*)&nullHdr, sizeof(CmIpHdrParm));
   HI_ZERO((U8*)&tPar, sizeof(CmTptParam));

   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;

         /* Initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV4;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.address = HI_ACC_SERV_ADDR;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_6;

         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 1;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option = 
                                            CM_SOCKOPT_OPT_REUSEADDR;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level  = 
                                            CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.value = 
                                            CM_SOCKOPT_ENABLE;

         HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
         nullFilter.type = CM_ICMP_NO_FILTER;
         HcLiHitServOpenReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                            HIACC_SERV_SUCON_ID, 
                            &hiAccCb.curTst.remAddr, 
                            &hiAccCb.curTst.tPar, &nullFilter, 
                            HI_SRVC_UDP_TPKT_HDR);
         hiAccCb.curTst.state++;
         break;

      case 1:
         /* Wait for Server ConCfm */
         break;

      case 2:
         /* Connect a UDP client to the server */

         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV4;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.address = HI_ACC_SERV_ADDR;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_6;

         hiAccCb.curTst.locAddr.type = CM_TPTADDR_IPV4;
         hiAccCb.curTst.locAddr.u.ipv4TptAddr.address = HI_ACC_SERV_ADDR;
         hiAccCb.curTst.locAddr.u.ipv4TptAddr.port = 5005;
                                     /* TODO HI_ACC_SERV_PORT + HI_TSTID_6 + 1; */

         HcLiHitConReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                       HIACC_CLT_SUCON_ID,
                       &hiAccCb.curTst.remAddr,
                       &hiAccCb.curTst.locAddr,
                       &hiAccCb.curTst.tPar,
                       HI_SRVC_UDP_TPKT_HDR);

         hiAccCb.curTst.state++;
         break;
         
      case 3:
         /* Wait for Client ConCfm */
         break;

      case 4:
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_6;
         hiAccCb.curTst.msgIdx = 0;

         msg =  hiAccCb.tstMsgs[hiAccCb.curTst.msgIdx].msg;
         if(SAddMsgRef(msg, hiAccCb.init.region, 
                       hiAccCb.init.pool, &msg1) != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst6: mem error!\n"))
                         HI_ACC_TST_FAILED();
         }
         
         HITST_ZERO(&nullAddr, sizeof(CmTptAddr));
         nullAddr.type = CM_TPTADDR_NOTPRSNT;

         HITST_ZERO(&nullHdr, sizeof(CmIpHdrParm));
         nullHdr.type = CM_HDRPARM_NOTPRSNT;

         /* Send the data out on the server to the client */
         tPar.type = CM_TPTPARAM_NOTPRSNT;
         HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                        hiAccCb.curTst.servSpConId, 
                        &hiAccCb.curTst.locAddr, &nullAddr, 
                        &nullHdr, &tPar, msg1);

         hiAccCb.curTst.state++;
         break;

      case 5:
         /* Wait for data*/
         break;

      case 6:
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_6;
         /* Disconnect the server */
         HIACCPRINT((hiAccCb.prntBuf, 
                     "hiAccTst6:Disconnecting UDP TPKT server\n"))
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                        HI_PROVIDER_CON_ID, 
                        hiAccCb.curTst.servSpConId, 
                        HI_CLOSE, &hiAccCb.curTst.tPar);
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                        HI_PROVIDER_CON_ID, 
                        hiAccCb.curTst.cltSpConId, 
                        HI_CLOSE, &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state++;
         break;

      case 7:
         break;

      case 8:
         break;
   
      case 9:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_6;
         HIACCPRINT((hiAccCb.prntBuf, 
                     "hiAccTst6:Disconnecting UDP servers\n"))
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                        HI_PROVIDER_CON_ID, 
                        hiAccCb.curTst.servSpConId, 
                        HI_CLOSE, &hiAccCb.curTst.tPar);
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                        HI_PROVIDER_CON_ID, 
                        hiAccCb.curTst.cltSpConId, 
                        HI_CLOSE, &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_FAILED;
         break;
   }/* end switch */

   RETVALUE(ROK);  
}/* end of hiAccTst6 */


/*
*
*       Fun:   hiAccTst7
*
*       Desc:  This test case opens  a Raw socket with no options & a valid 
*              filter type then it will send Raw data on it & compares 
*              the data after receving it.
*              This socket will also listen ICMP error messages.
*              
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst7
(
Void
)
#else
PUBLIC S16 hiAccTst7()
#endif
{

   Buffer    *msg, *msg1;
   U32       i;
   static U8 cnt = 0;
   CmTptAddr    nullAddr;
   CmIcmpFilter nullFilter;
   CmIpHdrParm  nullHdr;
   CmTptParam   tPar;

   TRC2(hiAccTst7)

   HI_ZERO((U8*)&nullAddr, sizeof(CmTptAddr));
   HI_ZERO((U8*)&nullFilter, sizeof(CmIcmpFilter));
   HI_ZERO((U8*)&nullHdr, sizeof(CmIpHdrParm));
   HI_ZERO((U8*)&tPar, sizeof(CmTptParam));

   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;

         /* Initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV4;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.address =  HI_ACC_SERV_ADDR;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 0;

         for(i = 0; i < 2; i++)
         {
            hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
            hiAccCb.curTst.tPar.u.sockParam.numOpts = 0;
            if(i == 0)
            {
               hiAccCb.curTst.tPar.u.sockParam.numOpts = 1;
               hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option = 
                                                   CM_SOCKOPT_OPT_HDRINCLD;
               hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level  = 
                                                   CM_SOCKOPT_LEVEL_IP;
               hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.value = 
                                                     CM_SOCKOPT_ENABLE;
            }
           
            HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
            if(i==0)
               nullFilter.type = CM_ICMPVER4_FILTER;
            else 
               nullFilter.type = CM_ICMP_NO_FILTER;

            nullFilter.u.icmpv4Filter.icmpMsgFlag = TRUE;
            nullFilter.u.icmpv4Filter.allMsg = TRUE;
            nullFilter.u.icmpv4Filter.protocol = CM_PROTOCOL_RAW;
            nullFilter.u.icmpv4Filter.num = 0;
            nullFilter.u.icmpv4Filter.icmpError[0].errType =
                                             CM_ICMP_ET_DEST_UNREACHBLE;
            nullFilter.u.icmpv4Filter.icmpError[0].errCodeMask = 
                                                      CM_ALL_CODES_MASK; 
            nullFilter.u.icmpv4Filter.icmpError[1].errType = 
                                                      CM_ICMP_ET_REDRCT;
            nullFilter.u.icmpv4Filter.icmpError[1].errCodeMask = 
                                                      CM_ALL_CODES_MASK;
        
            HcLiHitServOpenReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                               (HIACC_RAW_SUCON_ID + i), 
                               &hiAccCb.curTst.remAddr,
                               &hiAccCb.curTst.tPar, 
                               &nullFilter, HI_SRVC_RAW_SCTP);
         }
         hiAccCb.curTst.state++;
         break;

      case 1:    /* HitConfirm */
         break;

      case 2:
         cnt++;
         if (cnt < 2)
         {
            hiAccCb.curTst.state--;
         }
         else
         {
            hiAccCb.curTst.state++;
            cnt = 0;
         }
         break;

      case 3:
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 0;
         
         /* Send data */
         for(i = 0; i < 2; i++)
         {
            msg =  hiAccCb.tstMsgs[i].msg;
            if(SAddMsgRef(msg, hiAccCb.init.region, 
                          hiAccCb.init.pool, &msg1) != ROK)
            {
               HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst7: mem error!\n"))
               HI_ACC_TST_FAILED();
            }
            
            HITST_ZERO(&nullAddr, sizeof(CmTptAddr));
            nullAddr.type = CM_TPTADDR_NOTPRSNT;

            HITST_ZERO(&nullHdr, sizeof(CmIpHdrParm));
            nullHdr.type = CM_HDRPARM_NOTPRSNT;
            nullHdr.u.hdrParmIpv4.proto.pres = FALSE;
            nullHdr.u.hdrParmIpv4.dfBit.pres = FALSE;
            nullHdr.u.hdrParmIpv4.ttl.pres   = FALSE;
            nullHdr.u.hdrParmIpv4.tos.pres   = FALSE;

#ifdef IPV4_OPTS_SUPPORTED
            nullHdr.u.hdrParmIpv4.ipv4HdrOpt.pres=FALSE; 
#endif /* IPV4_OPTS_SUPPORTED */
            if(i == 0)
            {
               nullHdr.type = CM_HDRPARM_IPV4;
               nullHdr.u.hdrParmIpv4.ttl.pres = TRUE;
               nullHdr.u.hdrParmIpv4.ttl.val = 80;

               tPar.type = CM_TPTPARAM_NOTPRSNT;
               HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                              hiAccCb.curTst.servSpConId, 
                              &hiAccCb.curTst.remAddr,
                              &nullAddr, &nullHdr, &tPar, msg1);
            }
            else
            {
               tPar.type = CM_TPTPARAM_NOTPRSNT;
               HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                              hiAccCb.curTst.cltSpConId, 
                              &hiAccCb.curTst.remAddr,
                              &nullAddr, &nullHdr, &tPar, msg1);
            }
         }
         hiAccCb.curTst.state++;
         break;

      case 4:
      case 5:
         /* Wait for 2 data indications */
         break;
      

      case 6:
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 0;
         
         /* Disconnect the servers */
         for(i=0; i<2; i++)
         {
            HIACCPRINT((hiAccCb.prntBuf,
                        "hiAccTst7:Disconnecting Raw Socket\n"))

            hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;

            HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                           HI_USER_CON_ID, (HIACC_RAW_SUCON_ID + i), 
                           HI_CLOSE, &hiAccCb.curTst.tPar);
         } 
         hiAccCb.curTst.state ++;
         break;
   
      case 7:
      case 8:
         break;
      
      case 9:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 0;
         
         for(i=0; i<2; i++)
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                        "hiAccTst7:Disconnecting Raw Socket\n"))
            hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
            HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_USER_CON_ID,
                           (HIACC_RAW_SUCON_ID + i), HI_CLOSE, 
                           &hiAccCb.curTst.tPar);
         }
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;

   }/* end switch */

   RETVALUE(ROK);  
} /* end of hiAccTst7 */

#if (defined(IPV4_OPTS_SUPPORTED) && defined(HI_RSVP_SUPPORT))

/*
*
*       Fun:   hiAccTst8
*
*       Desc:  This test case opens a RSVP socket with no options & a valid
*              filter type. Then it sends 2 RSVP packets on it. First RSVP 
*              packet has Router Alert Option set & the second packet without 
*              Router Alert option. It then checks the data after receving it.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst8
(
Void
)
#else
PUBLIC S16 hiAccTst8()
#endif
{

   Buffer    *msg, *msg1;
   CmTptAddr    nullAddr;
   CmIcmpFilter nullFilter;
   CmIpHdrParm  ipv4HdrParam;
   CmTptParam     tPar;
   
   TRC2(hiAccTst8)

   HI_ZERO((U8*)&nullAddr, sizeof(CmTptAddr));
   HI_ZERO((U8*)&nullFilter, sizeof(CmIcmpFilter));
   HI_ZERO((U8*)&ipv4HdrParam, sizeof(CmIpHdrParm));
   HI_ZERO((U8*)&tPar, sizeof(CmTptParam));
      
   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);
         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;
       
         /* Initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV4;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.address =  HI_ACC_SERV_ADDR;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 0;
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
 
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 2;

         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option =
                                              CM_SOCKOPT_OPT_HDRINCLD;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level  =
                                              CM_SOCKOPT_LEVEL_IP;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.value =
                                              CM_SOCKOPT_ENABLE;

         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].option =
                                              CM_SOCKOPT_OPT_HDRINCLD;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].level  =
                                              CM_SOCKOPT_LEVEL_IP;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].optVal.value =
                                              CM_SOCKOPT_ENABLE;
#ifdef SS_LINUX
         hiAccCb.curTst.tPar.u.sockParam.numOpts++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[2].option =
                                             CM_SOCKOPT_OPT_IP_ROUTER_ALERT;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[2].level  =
                                              CM_SOCKOPT_LEVEL_IP;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[2].optVal.value =
                                              CM_SOCKOPT_ENABLE;
#ifdef LOCAL_INTF
         hiAccCb.curTst.tPar.u.sockParam.numOpts++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[3].option =
                                             CM_SOCKOPT_OPT_IPV4_PKTINFO;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[3].level  =
                                              CM_SOCKOPT_LEVEL_IP;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[3].optVal.value =
                                              CM_SOCKOPT_ENABLE;
#endif         
#endif /* SS_LINUX */
         
         HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
         nullFilter.type = CM_ICMP_NO_FILTER;

         /* Open RSVP server with Service Type = HI_SRVC_RAW_RSVP */
         HcLiHitServOpenReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                               (HIACC_RAW_SUCON_ID),
                               &hiAccCb.curTst.remAddr,
                               &hiAccCb.curTst.tPar,
                               &nullFilter, HI_SRVC_RAW_RSVP);
         hiAccCb.curTst.state++;
         break;

      case 1:    /* Wait here for the HitConfirm from TUCL*/
         break;

      case 2:
         /* Send first packet with Router Alert */
         msg =  hiAccCb.tstMsgs[0].msg;
         if(SAddMsgRef(msg, hiAccCb.init.region,
                       hiAccCb.init.pool, &msg1) != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst8: mem error!\n"))
            HI_ACC_TST_FAILED();
         }
 
         HITST_ZERO(&nullAddr, sizeof(CmTptAddr));
         nullAddr.type = CM_TPTADDR_NOTPRSNT;
 
         HITST_ZERO(&ipv4HdrParam, sizeof(CmIpHdrParm));
         ipv4HdrParam.type = CM_HDRPARM_IPV4;
         ipv4HdrParam.u.hdrParmIpv4.proto.pres = FALSE;
         ipv4HdrParam.u.hdrParmIpv4.dfBit.pres = FALSE;
         ipv4HdrParam.u.hdrParmIpv4.tos.pres   = FALSE;
         ipv4HdrParam.u.hdrParmIpv4.ttl.pres = TRUE;
         ipv4HdrParam.u.hdrParmIpv4.ttl.val = 80;

         ipv4HdrParam.u.hdrParmIpv4.ipv4HdrOpt.pres=TRUE;
         ipv4HdrParam.u.hdrParmIpv4.ipv4HdrOpt.len=4;
 
         ipv4HdrParam.u.hdrParmIpv4.ipv4HdrOpt.val[0]=0x94;
         ipv4HdrParam.u.hdrParmIpv4.ipv4HdrOpt.val[1]=0x04;
         ipv4HdrParam.u.hdrParmIpv4.ipv4HdrOpt.val[2]=0x00;
         ipv4HdrParam.u.hdrParmIpv4.ipv4HdrOpt.val[3]=0x00;

         tPar.type = CM_TPTPARAM_NOTPRSNT;
         HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                         hiAccCb.curTst.servSpConId,
                         &hiAccCb.curTst.remAddr,
                         &nullAddr, &ipv4HdrParam, &tPar, msg1);
         hiAccCb.curTst.state++;
         break;

      case 3:
         /* Wait for a data indication */
         HIACCPRINT((hiAccCb.prntBuf, 
                    "hiAccTst8/case3: Waiting for UDatInd\n"))
         SThreadYield();
         break;
 
      case 4:
         /* Send 2nd packet without Router Alert */
         msg =  hiAccCb.tstMsgs[0].msg;
         if(SAddMsgRef(msg, hiAccCb.init.region,
                       hiAccCb.init.pool, &msg1) != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst8: mem error!\n"))
            HI_ACC_TST_FAILED();
         }

          HITST_ZERO(&nullAddr, sizeof(CmTptAddr));
         nullAddr.type = CM_TPTADDR_NOTPRSNT;
 
         HITST_ZERO(&ipv4HdrParam, sizeof(CmIpHdrParm));
         ipv4HdrParam.type = CM_HDRPARM_NOTPRSNT;
         ipv4HdrParam.u.hdrParmIpv4.proto.pres = FALSE;
         ipv4HdrParam.u.hdrParmIpv4.dfBit.pres = FALSE;
         ipv4HdrParam.u.hdrParmIpv4.ttl.pres   = FALSE;
         ipv4HdrParam.u.hdrParmIpv4.tos.pres   = FALSE;
 
         ipv4HdrParam.type = CM_HDRPARM_IPV4;
          ipv4HdrParam.u.hdrParmIpv4.ttl.pres = TRUE;
         ipv4HdrParam.u.hdrParmIpv4.ttl.val = 80;
 
         /* Fill up the Router Alert Option */
         ipv4HdrParam.u.hdrParmIpv4.ipv4HdrOpt.pres = FALSE;
         ipv4HdrParam.u.hdrParmIpv4.ipv4HdrOpt.len=0;

         tPar.type = CM_TPTPARAM_NOTPRSNT;
         HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                         hiAccCb.curTst.servSpConId,
                         &hiAccCb.curTst.remAddr,
                         &nullAddr, &ipv4HdrParam, &tPar, msg1);
         hiAccCb.curTst.state++;
         break;

      case 5:
         HIACCPRINT((hiAccCb.prntBuf, 
                    "hiAccTst8/case5: Waiting for UDatInd\n"))
         SThreadYield();
         break;

      case 6:
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 0;

         /* Disconnect the servers */
         HIACCPRINT((hiAccCb.prntBuf,
                    "hiAccTst8 : Disconnecting RSVP Socket\n"))

         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;

         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                        HI_USER_CON_ID, HIACC_RAW_SUCON_ID,
                           HI_CLOSE, &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state ++;
         break;

      case 7:
         break;

      case 8:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */

         HIACCPRINT((hiAccCb.prntBuf,
                        "hiAccTst8:Disconnecting Raw Socket\n"))
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_USER_CON_ID,
                        (HIACC_RAW_SUCON_ID), HI_CLOSE,
                        &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;

   }/* end switch */

   RETVALUE(ROK);
} /* end of hiAccTst8 */

#endif /* IPV4_OPTS_SUPPORTED */

#ifdef IPV6_SUPPORTED
/*
*
*       Fun:   hiAccTst9
*
*       Desc:  This test case opens a IPV6 UDP server with TPKT service type.
*              
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst9
(
Void
)
#else
PUBLIC S16 hiAccTst9()
#endif
{
   Buffer            *msg, *msg1;
   CmTptAddr         srcAddr;
   CmIcmpFilter      nullFilter;
   CmIpHdrParm       ipv6HdrParam;
   struct in6_addr   lpBkAddr;
   MsgLen            msgLen;
   struct in6_addr   tempAddr;
   CmTptParam        tPar;
      
   TRC2(hiAccTst9)

   HI_ZERO((U8*)&srcAddr, sizeof(CmTptAddr));
   HI_ZERO((U8*)&nullFilter, sizeof(CmIcmpFilter));
   HI_ZERO((U8*)&ipv6HdrParam, sizeof(CmIpHdrParm));
   HI_ZERO((U8*)&tPar, sizeof(CmTptParam));

   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;

         /* Initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV6;
         
         lpBkAddr = in6addr_loopback;

         cmMemcpy((U8 *)&hiAccCb.curTst.remAddr.u.ipv6TptAddr.ipv6NetAddr,
                  (U8 *)&lpBkAddr, sizeof(lpBkAddr));

         hiAccCb.curTst.remAddr.u.ipv6TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_9;

         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 1;

         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option = 
                                            CM_SOCKOPT_OPT_REUSEADDR;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level  = 
                                            CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.value = 
                                            CM_SOCKOPT_ENABLE;

#ifdef LOCAL_INTF
         /* this is to test the getting of PKTINFO for IPv6 UDP socket */
         hiAccCb.curTst.tPar.u.sockParam.numOpts++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].option = 
                                            CM_SOCKOPT_OPT_IPV6_PKTINFO;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].level  = 
                                            CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
#endif /* LOCAL_INTF */

         /* this is to test the getting of HOPLIMIT for IPv6 UDP socket */
#ifdef IPV6_OPTS_SUPPORTED         
         {
         /* hi001.105 - counter numOpts */
         U8                numOpts;
         hiAccCb.curTst.tPar.u.sockParam.numOpts++;
         numOpts= hiAccCb.curTst.tPar.u.sockParam.numOpts;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[numOpts].option = 
                                            CM_SOCKOPT_OPT_RECVIPV6_HOPLIM;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[numOpts].level  = 
                                            CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[numOpts].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
         }
#endif

         HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
         nullFilter.type = CM_ICMP_NO_FILTER;
         HcLiHitServOpenReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                            HIACC_SERV_SUCON_ID, 
                            &hiAccCb.curTst.remAddr, 
                            &hiAccCb.curTst.tPar, &nullFilter, 
                            HI_SRVC_UDP_TPKT_HDR);
         hiAccCb.curTst.state++;
         break;

      case 1:
         /* Wait for Server ConCfm */
         break;

      case 2:
         /* Connect a UDP client to the server */

         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV6;
         lpBkAddr = in6addr_loopback;
         cmMemcpy((U8 *)&hiAccCb.curTst.remAddr.u.ipv6TptAddr.ipv6NetAddr,
                  (U8 *)&lpBkAddr, sizeof(lpBkAddr));
         hiAccCb.curTst.remAddr.u.ipv6TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_9;
        
         hiAccCb.curTst.locAddr.type = CM_TPTADDR_IPV6;
         cmMemcpy((U8 *)&hiAccCb.curTst.locAddr.u.ipv6TptAddr.ipv6NetAddr,
                  (U8 *)&lpBkAddr, sizeof(lpBkAddr));
         hiAccCb.curTst.locAddr.u.ipv6TptAddr.port =
                                         HI_ACC_SERV_PORT + HI_TSTID_9 + 1;

         HcLiHitConReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                       HIACC_CLT_SUCON_ID,
                       &hiAccCb.curTst.remAddr,
                       &hiAccCb.curTst.locAddr,
                       &hiAccCb.curTst.tPar,
                       HI_SRVC_UDP_TPKT_HDR);

         hiAccCb.curTst.state++;
         break;
         
      case 3:
         /* Wait for Client ConCfm */
         break;

      case 4:
         hiAccCb.curTst.remAddr.u.ipv6TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_9;
         hiAccCb.curTst.msgIdx = 0;

         msgLen = hiAccCb.tstMsgs[hiAccCb.curTst.msgIdx].len;

         msg =  hiAccCb.tstMsgs[hiAccCb.curTst.msgIdx].msg;
         if(SAddMsgRef(msg, hiAccCb.init.region, 
                       hiAccCb.init.pool, &msg1) != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst9 : mem error!\n"))
                         HI_ACC_TST_FAILED();
         }
                  
         HITST_ZERO(&ipv6HdrParam, sizeof(CmIpHdrParm));
         ipv6HdrParam.type = CM_HDRPARM_IPV6;

         ipv6HdrParam.u.hdrParmIpv6.ttl.pres = TRUE;
         ipv6HdrParam.u.hdrParmIpv6.ttl.val = 100;

         HITST_ZERO(&srcAddr, sizeof(CmTptAddr));
         srcAddr.type = CM_TPTADDR_NOTPRSNT;

         /* Set the source address to set on outgoing pkt. TUCL
          * doesn't verify the outgoing source address! */
         HITST_ZERO(&srcAddr, sizeof(CmTptAddr));
         srcAddr.type = CM_TPTADDR_IPV6;

         tempAddr = in6addr_any;
       
         cmMemcpy((U8 *)&srcAddr.u.ipv6TptAddr.ipv6NetAddr,
                  (U8 *)&tempAddr, sizeof(tempAddr));
        
         /* Send the data out on the server to the client */
         tPar.type = CM_TPTPARAM_NOTPRSNT;
         HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                        hiAccCb.curTst.cltSpConId, 
                        &hiAccCb.curTst.locAddr, &srcAddr, 
                        &ipv6HdrParam, &tPar, msg1);

         if(hiAccCb.curTst.prntFlag)
         {
            sprintf(hiAccCb.prntBuf, 
                     "hiAccTst9: msgIdx(%d):wrote %d octets ...\n ", 
                     hiAccCb.curTst.msgIdx, msgLen);
            SPrint(hiAccCb.prntBuf);
         }
         hiAccCb.curTst.state++;
         break;

      case 5:
         /* Wait for data*/
         break;

      case 6:
         /* Disconnect the server */
         HIACCPRINT((hiAccCb.prntBuf, 
                     "hiAccTst9 : Disconnecting IPV6  UDP TPKT server\n"))
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                        HI_PROVIDER_CON_ID, 
                        hiAccCb.curTst.servSpConId, 
                        HI_CLOSE, &hiAccCb.curTst.tPar);
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                        HI_PROVIDER_CON_ID, 
                        hiAccCb.curTst.cltSpConId, 
                        HI_CLOSE, &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state++;
         break;

      case 7:
         /* Wait for two disconnect confirms */
         break;

      case 8:
         break;
   
      case 9:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */
         hiAccCb.curTst.remAddr.u.ipv6TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_9;
         HIACCPRINT((hiAccCb.prntBuf, 
                     "hiAccTst9 : Disconnecting IPV6  UDP servers\n"))
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                        HI_PROVIDER_CON_ID, 
                        hiAccCb.curTst.servSpConId, 
                        HI_CLOSE, &hiAccCb.curTst.tPar);
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                        HI_PROVIDER_CON_ID, 
                        hiAccCb.curTst.cltSpConId, 
                        HI_CLOSE, &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_FAILED;
         break;
   }/* end switch */

   RETVALUE(ROK);  
}/* end of hiAccTst9 */

#ifdef HI_ACC_MCAST_ENB

/*
*
*       Fun:   hiAccTst10
*
*       Desc:  This function open a TUCL IPV6 multicast listener, opens two
*              ACC clients. Each client sends data to the server. First
*              client sends data on server's mulitcast address and the
*              second client sends data on the server's unicast address.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst10
(
Void
)
#else
PUBLIC S16 hiAccTst10()
#endif
{

   Buffer *msg;
   MsgLen  msgLen;

   CmTptAddr      nullAddr;
   CmIcmpFilter   nullFilter;
   CmIpHdrParm    nullHdr;
   struct in6_addr   lpBkAddr;
   S16            ret;
   U8             numMsgToSend;
   CmTptParam     tPar;

   TRC2(hiAccTst10)

   HI_ZERO((U8*)&nullAddr, sizeof(CmTptAddr));
   HI_ZERO((U8*)&nullFilter, sizeof(CmIcmpFilter));
   HI_ZERO((U8*)&nullHdr, sizeof(CmIpHdrParm));
   HI_ZERO((U8*)&tPar, sizeof(CmTptParam));
   
   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;

         /* initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV6;
         
         lpBkAddr = in6addr_any;
       
         cmMemcpy((U8 *)&hiAccCb.curTst.remAddr.u.ipv6TptAddr.ipv6NetAddr,
                  (U8 *)&lpBkAddr, sizeof(lpBkAddr));
        
         hiAccCb.curTst.remAddr.u.ipv6TptAddr.port = 
                                     (HI_ACC_SERV_PORT+ hiAccCb.curTst.id +
                                     HIACC_UDP_MAX_SERV);
         
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 2;

         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level =
                                             CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option =
                                             CM_SOCKOPT_OPT_ADD_MCAST6_MBR;
         ret = cmInetPton6(
                           &hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.
                           mCastInfo6.mCastAddr, HI_ACC_MCAST_IPV6ADDR);
         if (ret != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, 
               "hiAccTst10: Could not convert multicast addr to IPV6 addr!\n"))
               HI_ACC_TST_FAILED();
         }
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.mCastInfo6.localInf
                                           = HI_ACC_IPV6_MCAST_LOCINF;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].level =
                                             CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].option =
                                             CM_SOCKOPT_OPT_TX_BUF_SIZE;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].optVal.value = 1000;

         /* Create a UDP HI Server */
         HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
         nullFilter.type = CM_ICMP_NO_FILTER;
         
         HcLiHitServOpenReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                            HIACC_SERV_SUCON_ID, 
                            &hiAccCb.curTst.remAddr, 
                            &hiAccCb.curTst.tPar, &nullFilter, 
                            HI_SRVC_UDP);
         hiAccCb.curTst.state++;
         break;

      case 1:
         /* wait for  HitConCfm */
         break;

      case 2:
         HITST_ZERO(&nullAddr, sizeof(CmTptAddr));
         nullAddr.type = CM_TPTADDR_NOTPRSNT;

         HITST_ZERO(&nullHdr, sizeof(CmIpHdrParm));
         nullHdr.type = CM_HDRPARM_NOTPRSNT;
        
         /* send the message to server mCast address */
         CM_INET_COPY_IPV6ADDR(&hiAccCb.curTst.remAddr.u.ipv6TptAddr.ipv6NetAddr
                               , &hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].
                                 optVal.mCastInfo6.mCastAddr);
         
         msgLen = hiAccCb.tstMsgs[0].len;


         for (numMsgToSend = 0; numMsgToSend < 2; numMsgToSend ++)
         {
            if(SAddMsgRef(hiAccCb.tstMsgs[0].msg, 
                          hiAccCb.init.region, hiAccCb.init.pool, &msg) != ROK)
            {
               HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst10: memory error!\n"))
               HI_ACC_TST_FAILED();
            }

            /* send data */
            tPar.type = CM_TPTPARAM_NOTPRSNT;
            tPar.type = CM_TPTPARAM_SOCK;
            tPar.u.sockParam.numOpts = 1;
            tPar.u.sockParam.sockOpts[0].level = CM_INET_LEVEL_IPV6; 
            tPar.u.sockParam.sockOpts[0].option = CM_SOCKOPT_OPT_MCAST6_HOPS;
            tPar.u.sockParam.sockOpts[0].optVal.value = 3;

            HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                           hiAccCb.curTst.servSpConId,
                           &hiAccCb.curTst.remAddr, &nullAddr, 
                           &nullHdr, &tPar, msg);
         
            if(hiAccCb.curTst.prntFlag)
            {
               sprintf(hiAccCb.prntBuf, 
                        "hiAccTst10: msgIdx(%d):wrote %d octets ...\n ", 
                        hiAccCb.curTst.msgIdx, msgLen);
               SPrint(hiAccCb.prntBuf);
            }
         }
         hiAccCb.curTst.state++;
         break;

      case 3: /* wait for first UDatInd in layer3.c */
         break;

      case 4: /* wait for second UDatInd in layer3.c */
         break;

      case 5:

         /* leave the mcast group for the server */
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 1;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level =
                                             CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option =
                                             CM_SOCKOPT_OPT_DRP_MCAST6_MBR;

         /* Remove membership from the multicast group */
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_USER_CON_ID,
                        HIACC_SERV_SUCON_ID, HI_LEAVE_MCAST_GROUP, 
                        &hiAccCb.curTst.tPar);

         /* Close the server */
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_USER_CON_ID,
                        HIACC_SERV_SUCON_ID, HI_CLOSE, &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state++;
         break;

      case 6:
         break;

      case 7:
         break;

      case 8: 
         hiAccCb.curTst.result = HI_TST_OK;
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;

      default:
         HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst10 : invalid acc state\n"))
         HI_ACC_TST_FAILED();
         break;
   }

   if(hiAccCb.curTst.errFlag)
   {
      hiAccCb.curTst.state = HI_ACC_ST_END;
      HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_USER_CON_ID,
                     HIACC_SERV_SUCON_ID, HI_CLOSE, &hiAccCb.curTst.tPar);
   }

   RETVALUE(ROK);  
}/* end of hiAccTst10() */

#endif /* HI_ACC_MCAST_ENB */

/*
*
*       Fun:   hiAccTst11
*
*       Desc:  Open a IPV6 TCP client and a IPV6 TCP server and 
*              transfer data.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst11
(
Void
)
#else
PUBLIC S16 hiAccTst11()
#endif
{

   S16          i;
   Buffer       *msg, *msg1;
   CmIcmpFilter nullFilter;
   struct in6_addr   lpBkAddr;

   TRC2(hiAccTst11)


   HI_ZERO((U8*)&nullFilter, sizeof(CmIcmpFilter));
   
   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;

         /* Initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV6;

        /* hi010.201  1. Removing ipv6 compilation error in windows */
         lpBkAddr = in6addr_loopback;
         cmMemcpy((U8 *)&hiAccCb.curTst.remAddr.u.ipv6TptAddr.ipv6NetAddr,
                  (U8 *)&lpBkAddr, sizeof(lpBkAddr));
         hiAccCb.curTst.remAddr.u.ipv6TptAddr.port = 
                                  HI_ACC_SERV_PORT + hiAccCb.curTst.id;

         /* Initialize transport parameters */
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 1;
         
         /* enable reuse address option */
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option = 
                                            CM_SOCKOPT_OPT_REUSEADDR;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level  = 
                                            CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
         
        
         /*hi002.105 (hi029.104) */
#ifdef HIACC_PRIVILEDGED_MODE

         /* enable TCP no delay */

         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].option = 
                                            CM_SOCKOPT_OPT_TCP_NODELAY;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].level  = 
                                            CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 2;
#endif 

#ifdef IPV6_OPTS_SUPPORTED          
         /* this is to test the getting of HOPLIMIT for IPv6 UDP socket */
         /* mmh: to set the hoplimit val, it must be supplied as ipHdrParm */
         hiAccCb.curTst.tPar.u.sockParam.numOpts++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[2].option = 
                                            CM_SOCKOPT_OPT_RECVIPV6_HOPLIM;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[2].level  = 
                                            CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[2].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
#endif         
#ifdef WIN32
         hiAccCb.curTst.tPar.u.sockParam.listenQSize = 1;
#else
         hiAccCb.curTst.tPar.u.sockParam.listenQSize = 5;
#endif /* WIN32 */

         /* Request TUCL to open a TCP Server */
         HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
         nullFilter.type = CM_ICMP_NO_FILTER;
         HIACC_OPEN_TCP_SRV(HIACC_SERV_SUCON_ID, &hiAccCb.curTst.remAddr, 
                            &hiAccCb.curTst.tPar, &nullFilter, 
                            HI_SRVC_TCP_TPKT_HDR);

         hiAccCb.curTst.state++;
         break;

      case 1:
         /* wait here for the server conCfm */
         break;

      case 2:
         /* Open a TCP Client */
			/* hi024.105 For Ipv6 Testing the hiAccCb.curTst.locAddr.type shuold be
			 * CM_TPTADDR_IPV6 */
         hiAccCb.curTst.locAddr.type = CM_TPTADDR_IPV6;
         HIACC_OPEN_TCP_CLT((HIACC_CLT_SUCON_ID),
                            &hiAccCb.curTst.remAddr,
                            &hiAccCb.curTst.locAddr,
                            &hiAccCb.curTst.tPar,
                            HI_SRVC_TCP_TPKT_HDR);
         hiAccCb.curTst.state++;
         break;

      case 3:
         /* Wait here for a connection confirm and connection indication 
          */
         break;

      case 4:
         break;
         /* HitConInd in layer3.c gives back HitConRsp with 
          * suConId = HIACC_NEW_SUCON_ID
          */
         /* Data tx is now possible */


      case 5:
         /* Pump messages on the new accepted connection */
         for (i = 0; i < HI_ACC_NUM_TST_MSGS; i++)
         {             
            msg1 = hiAccCb.bigMsg.msg;
            if(SAddMsgRef(msg1, hiAccCb.init.region, 
                          hiAccCb.init.pool, &msg) != ROK)
            {
               HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst11 : mem error!\n"))
               HI_ACC_TST_FAILED();
            }
            hiAccCb.curTst.msgIdx++;
            HcLiHitDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                          hiAccCb.curTst.newSpConId, msg);
         }
         hiAccCb.curTst.state++;
         break;

      case 6:
         /* Wait for messages to be looped back to the server */
         break;

      case 7:
         /* Close the server and client */
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                        HI_USER_CON_ID, HIACC_SERV_SUCON_ID, HI_CLOSE,
                        &hiAccCb.curTst.tPar);
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                        HI_PROVIDER_CON_ID, hiAccCb.curTst.cltSpConId, 
                        HI_CLOSE, &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state++;
         break;

      case 8:
         /* Wait for two disconnect confirms and a disconnect indication */
         break;

      case 9:
         break;

      case 10:
         hiAccCb.curTst.state++;
         break;

      case 11:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         break;
   }

   if(hiAccCb.curTst.errFlag)
   {
      HcLiHitDiscReq(&hiAccCb.uiPst, 
                     HI_ACC_SAP_0, HI_USER_CON_ID, 
                     HIACC_SERV_SUCON_ID,
                     HI_CLOSE, &hiAccCb.curTst.tPar);
      
      HcLiHitDiscReq(&hiAccCb.uiPst, 
                     HI_ACC_SAP_0, 
                     HI_USER_CON_ID,
                     HIACC_CLT_SUCON_ID,
                     HI_CLOSE,&hiAccCb.curTst.tPar);

      HcLiHitDiscReq(&hiAccCb.uiPst, 
                     HI_ACC_SAP_0, 
                     HI_USER_CON_ID,
                     HIACC_NEW_SUCON_ID,
                     HI_CLOSE,&hiAccCb.curTst.tPar);
   }

   RETVALUE(ROK);  
}/* end of hiAccTst11 */

#if (defined(IPV6_OPTS_SUPPORTED) && defined(HI_RSVP_SUPPORT))
/*
*
*       Fun:   hiAccTst12
*
*       Desc:  This test case opens a RSVP socket with no options & a valid
*              filter type. Then it sends 1 RSVP packet with IPV6 Extension 
*              header on it. The RSVP packet has Router Alert Option set. 
*              It then checks the data after receving.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst12
(
Void
)
#else
PUBLIC S16 hiAccTst12()
#endif
{

   Buffer          *msg;
   Buffer          *msg1;
   struct in6_addr lpBkAddr;
   CmTptAddr       srcAddr;
   CmIcmpFilter    nullFilter;
   CmIpHdrParm     ipv6HdrParam;
   U8              num;
   U8              idx;
   struct in6_addr tempAddr;
   CmTptParam      tPar;
   S32 ret;

   TRC2(hiAccTst12)

   HI_ZERO((U8*)&srcAddr, sizeof(CmTptAddr));
   HI_ZERO((U8*)&nullFilter, sizeof(CmIcmpFilter));
   HI_ZERO((U8*)&ipv6HdrParam, sizeof(CmIpHdrParm));
   HI_ZERO((U8*)&tPar, sizeof(CmTptParam));

   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;

         /* Initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV6;
#ifdef SS_LINUX         
         lpBkAddr = /*in6addr_any;*/ in6addr_loopback;
#else
         lpBkAddr = /*in6addr_any; */in6addr_loopback;
#endif /* SS_LINUX */         
         cmMemcpy((U8 *)&hiAccCb.curTst.remAddr.u.ipv6TptAddr.ipv6NetAddr,
                  (U8 *)&lpBkAddr, sizeof(lpBkAddr));


         hiAccCb.curTst.remAddr.u.ipv6TptAddr.port = 0; 
                                        
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK; 

         hiAccCb.curTst.tPar.u.sockParam.numOpts = 0;
         idx = 0;

#ifdef IPV6_OPTS_SUPPORTED         
         idx++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].option = 
                                            CM_SOCKOPT_OPT_RECVIPV6_HOPLIM;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].level  = 
                                            CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
#endif
         idx++;
         hiAccCb.curTst.tPar.u.sockParam.numOpts++; 
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].option = 
                                            CM_SOCKOPT_OPT_RECVIPV6_HBHOPT;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].level  = 
                                            CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
 
         idx++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].option = 
                                            CM_SOCKOPT_OPT_RECVIPV6_DSTOPTS;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].level  = 
                                            CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].optVal.value = 
                                            CM_SOCKOPT_ENABLE;

         idx++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].option = 
                                            CM_SOCKOPT_OPT_RECVIPV6_RTHDR;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].level  = 
                                            CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].optVal.value = 
                                            CM_SOCKOPT_ENABLE;

#ifdef LOCAL_INTF
         idx++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].option = 
                                            CM_SOCKOPT_OPT_IPV6_PKTINFO;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].level  = 
                                            CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
#endif /* LOCAL_INTF */

         hiAccCb.curTst.tPar.u.sockParam.numOpts = idx;

         HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
         nullFilter.type = CM_ICMP_NO_FILTER;

         HcLiHitServOpenReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                               HIACC_RAW_SUCON_ID,
                               &hiAccCb.curTst.remAddr,
                               &hiAccCb.curTst.tPar,
                               &nullFilter, HI_SRVC_RAW_RSVP);
         hiAccCb.curTst.state++;
         break;

      case 1:    /* Wait here for the HitConfirm from TUCL*/
         break;

         /* send data with HBH extension header ONLY */
      case 2:         
         msg =  hiAccCb.tstMsgs[0].msg;
         if(SAddMsgRef(msg, hiAccCb.init.region,
                        hiAccCb.init.pool, &msg1) != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst12: mem error!\n"))
            HI_ACC_TST_FAILED();
         }
         HITST_ZERO(&tPar, sizeof(tPar));
         tPar.type = CM_TPTPARAM_NOTPRSNT;

         /* set the source address to set on outgoing pkt. TUCL doesn't verify 
          * the outgoing source address! */

         HITST_ZERO(&srcAddr, sizeof(CmTptAddr));
         srcAddr.type = CM_TPTADDR_IPV6;

         tempAddr = in6addr_any;
       
         cmMemcpy((U8 *)&srcAddr.u.ipv6TptAddr.ipv6NetAddr,
                  (U8 *)&tempAddr, sizeof(tempAddr));

#ifdef SS_LINUX         
         lpBkAddr = in6addr_loopback;
#else
         lpBkAddr = in6addr_loopback;
#endif /* SS_LINUX */

         HITST_ZERO(&ipv6HdrParam, sizeof(CmIpHdrParm));

         ipv6HdrParam.type = CM_HDRPARM_IPV6;

         ipv6HdrParam.u.hdrParmIpv6.ttl.pres = TRUE;
         ipv6HdrParam.u.hdrParmIpv6.ttl.val = 80;

         ipv6HdrParam.u.hdrParmIpv6.srcAddr6.type = 0;

         /* Fill up the HBH Option */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhHdrPrsnt = TRUE;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.numHBHOpts = 1;
         
         /* allocate memory for structure CmIpv6HBHHdr */
         /* after allocation of memory, initialize type, length & value */
         ret = SGetSBuf(hiAccCb.init.region, hiAccCb.init.pool, 
             (Data **)&ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.hbhOpts,
             (Size)sizeof(CmIpv6HBHHdr)); 
         if (ret != ROK)
         {
            RETVALUE(ROUTRES);
         }

         /* TLV is filled up according to RFC which says the bytes value */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.hbhOpts[0].type = 
                                                                         0x05;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.hbhOpts[0].length = 
                                                                         0x02;
         /* allocate memory for value */
         ret = SGetSBuf(hiAccCb.init.region, hiAccCb.init.pool, 
                     (Data **)&ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.
                     hbhOpts[0].value, (Size)2);  
         if (ret != ROK)
         {
            RETVALUE(ROUTRES);
         }
       
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.hbhOpts[0].value[0] =
                                                                          0x01;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.hbhOpts[0].value[1] =
                                                                          0x00;
         /* Fill up the Dest Option */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsPrsnt = FALSE;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.numDestOpts = 0;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts = NULLP;

         /* Fill up the Route Hdr Option */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOptsPrsnt = FALSE;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.numAddrs = 0;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.ipv6Addrs = NULLP; 

         HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                        hiAccCb.curTst.servSpConId,
                        &hiAccCb.curTst.remAddr,
                        &srcAddr, &ipv6HdrParam, &tPar, msg1);
         hiAccCb.curTst.state++;
         break;

      case 3:
         /* Wait for a data indication */
         HIACCPRINT((hiAccCb.prntBuf, 
                    "hiAccTst12/case3: Waiting for UDatInd\n"))
         SThreadYield();
         break;
         
         /* send data with Destination Opt extension header ONLY */
      case 4:
         msg =  hiAccCb.tstMsgs[0].msg;
         if(SAddMsgRef(msg, hiAccCb.init.region,
                        hiAccCb.init.pool, &msg1) != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst12: mem error!\n"))
            HI_ACC_TST_FAILED();
         }
         HITST_ZERO(&tPar, sizeof(tPar));
         tPar.type = CM_TPTPARAM_NOTPRSNT;

         HITST_ZERO(&srcAddr, sizeof(CmTptAddr));
         srcAddr.type = CM_TPTADDR_NOTPRSNT;

         HITST_ZERO(&ipv6HdrParam, sizeof(CmIpHdrParm));

         ipv6HdrParam.type = CM_HDRPARM_IPV6;

         ipv6HdrParam.u.hdrParmIpv6.ttl.pres = TRUE;
         ipv6HdrParam.u.hdrParmIpv6.ttl.val = 90;

         ipv6HdrParam.u.hdrParmIpv6.srcAddr6.type = 0;

         /* Fill up the HBH Option */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhHdrPrsnt = FALSE;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.numHBHOpts = 0;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.hbhOpts = NULLP;
 
         /* Fill up the Dest Option */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsPrsnt = TRUE;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.numDestOpts = 1;
         
         ret = SGetSBuf(hiAccCb.init.region, hiAccCb.init.pool, 
                 (Data **)&ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.
                        destOpts, (Size)sizeof(CmIpv6DestOptsHdr)); 
         if (ret != ROK)
         {
            RETVALUE(ROUTRES);
         }
         /* No Dest option proposed/supported yet. So we are testing with padN 
          * option of size 6 bytes. For padN type = 1, length = no of bytes in
          * value field and value bytes are all 0 */         
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts[0].type = 
                                                                          0x01; 
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts[0].length =
                                                                          0x04;
         ret = SGetSBuf(hiAccCb.init.region, hiAccCb.init.pool, 
              (Data **)&ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.
                       destOpts[0].value, (Size)4);  
         if (ret != ROK)
         {
            RETVALUE(ROUTRES);
         }
         
         /* 4 bytes value field of 6-byte padding is 0 always! */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts[0].
                                                               value[0] = 0x00;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts[0].
                                                               value[1] = 0x00;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts[0].
                                                               value[2] = 0x00;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts[0].
                                                               value[3] = 0x00; 

         /* Fill up the Route Hdr Option */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOptsPrsnt = FALSE;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.numAddrs = 0;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.ipv6Addrs = NULLP;

         HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                        hiAccCb.curTst.servSpConId,
                        &hiAccCb.curTst.remAddr,
                        &srcAddr, &ipv6HdrParam, &tPar, msg1);
         hiAccCb.curTst.state++;
         break;
         
      case 5:
         /* Wait for a data indication */
         HIACCPRINT((hiAccCb.prntBuf, 
                    "hiAccTst12/case5: Waiting for UDatInd\n"))
         SThreadYield();
         break;         
        
      case 6:
         msg =  hiAccCb.tstMsgs[0].msg;
         if(SAddMsgRef(msg, hiAccCb.init.region,
                        hiAccCb.init.pool, &msg1) != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst12: mem error!\n"))
            HI_ACC_TST_FAILED();
         }
         HITST_ZERO(&tPar, sizeof(tPar));
         tPar.type = CM_TPTPARAM_NOTPRSNT;

         HITST_ZERO(&srcAddr, sizeof(CmTptAddr));
         srcAddr.type = CM_TPTADDR_NOTPRSNT;

         HITST_ZERO(&ipv6HdrParam, sizeof(CmIpHdrParm));

         ipv6HdrParam.type = CM_HDRPARM_IPV6;

         ipv6HdrParam.u.hdrParmIpv6.ttl.pres = TRUE;
         ipv6HdrParam.u.hdrParmIpv6.ttl.val = 100;

         /* Fill up the HBH Option */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhHdrPrsnt = FALSE;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.numHBHOpts = 0;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.hbhOpts = NULLP;
         
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsPrsnt = FALSE;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.numDestOpts = 0;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts = NULLP;         
 
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOptsPrsnt = TRUE;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.numAddrs = 2;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.slMap = 0x00c00000;
         
         lpBkAddr = in6addr_loopback;

         /* allocate memory required to hold all IPv6 addresses in the Route
          * Header here */
         num = ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.numAddrs;
         ret = SGetSBuf(hiAccCb.init.region, hiAccCb.init.pool, 
                        (Data **)&ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.
                        rtOpts.ipv6Addrs, (Size)(num * sizeof(CmIpv6NetAddr))); 
         if (ret != ROK)
         {
            RETVALUE(ROUTRES);
         }

         /* now copy IPv6 adresses one by one to the alloacated mem space */
         cmMemcpy((U8 *)ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.
                  ipv6Addrs[0], (U8 *)&lpBkAddr, sizeof(lpBkAddr));
         
         cmMemcpy((U8 *)ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.
                  ipv6Addrs[1], (U8 *)&lpBkAddr, sizeof(lpBkAddr));
         HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                        hiAccCb.curTst.servSpConId,
                        &hiAccCb.curTst.remAddr,
                        &srcAddr, &ipv6HdrParam, &tPar, msg1);
         hiAccCb.curTst.state++;         
         
         break;

      case 7:
         /* Wait for a data indication */
         HIACCPRINT((hiAccCb.prntBuf, 
                    "hiAccTst12/case7: Waiting for UDatInd\n"))
         SThreadYield();
         break;         
         
      case 8:
         hiAccCb.curTst.remAddr.u.ipv6TptAddr.port = 0;

         /* Disconnect the servers */
         HIACCPRINT((hiAccCb.prntBuf,
                        "hiAccTst12 : Disconnecting RSVP Socket\n"))

         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;

         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                        HI_USER_CON_ID, HIACC_RAW_SUCON_ID,
                           HI_CLOSE, &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state ++;
         break;

      case 9:
         break;

      case 10:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */

         HIACCPRINT((hiAccCb.prntBuf,
                        "hiAccTst12:Disconnecting Raw Socket\n"))
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_USER_CON_ID,
                        (HIACC_RAW_SUCON_ID), HI_CLOSE,
                        &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;

   }/* end switch */

   RETVALUE(ROK);
} /* end of hiAccTst12 */
/*
*
*       Fun:   hiAccTst13
*
*       Desc:  This test case opens a RSVP socket with no options & a valid
*              filter type. Then it sends 1 RSVP packet with IPV6 Extension 
*              header on it. The RSVP packet has Router Alert Option set. 
*              It then checks the data after receving.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst13
(
Void
)
#else
PUBLIC S16 hiAccTst13()
#endif
{

   Buffer    *msg, *msg1;
   struct in6_addr   lpBkAddr;
   CmTptAddr    nullAddr;
   CmIcmpFilter nullFilter;
   CmIpHdrParm  ipv6HdrParam;
   U8           num;
   S32          ret;
   U8           idx;
   CmTptParam   tPar;

   TRC2(hiAccTst13)

   HI_ZERO((U8*)&nullAddr, sizeof(CmTptAddr));
   HI_ZERO((U8*)&nullFilter, sizeof(CmIcmpFilter));
   HI_ZERO((U8*)&ipv6HdrParam, sizeof(CmIpHdrParm));
   HI_ZERO((U8*)&tPar, sizeof(CmTptParam));
      
   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;

         /* Initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV6;
#ifdef SS_LINUX         
         lpBkAddr = /*in6addr_any; */in6addr_loopback;
#else
         lpBkAddr = /*in6addr_any; */in6addr_loopback;
#endif /* SS_LINUX */          
         cmMemcpy((U8 *)&hiAccCb.curTst.remAddr.u.ipv6TptAddr.ipv6NetAddr,
                  (U8 *)&lpBkAddr, sizeof(lpBkAddr));
         hiAccCb.curTst.remAddr.u.ipv6TptAddr.port = 0; 
                                         
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK; 
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 0;

         /* set related IPv6 socket options */
         hiAccCb.curTst.tPar.u.sockParam.numOpts++;
         idx = 0;

#ifdef IPV6_OPTS_SUPPORTED         
         idx++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].option = 
                                            CM_SOCKOPT_OPT_RECVIPV6_HOPLIM;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].level  = 
                                            CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
#endif
         idx++;
         hiAccCb.curTst.tPar.u.sockParam.numOpts++; 
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].option = 
                                            CM_SOCKOPT_OPT_RECVIPV6_HBHOPT;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].level  = 
                                            CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
 
         idx++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].option = 
                                            CM_SOCKOPT_OPT_RECVIPV6_DSTOPTS;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].level  = 
                                            CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].optVal.value = 
                                            CM_SOCKOPT_ENABLE;

         idx++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].option = 
                                            CM_SOCKOPT_OPT_RECVIPV6_RTHDR;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].level  = 
                                            CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].optVal.value = 
                                            CM_SOCKOPT_ENABLE;

#ifdef LOCAL_INTF
         idx++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].option = 
                                            CM_SOCKOPT_OPT_IPV6_PKTINFO;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].level  = 
                                            CM_SOCKOPT_LEVEL_IPV6;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[idx - 1].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
#endif /* LOCAL_INTF */

         hiAccCb.curTst.tPar.u.sockParam.numOpts = idx;
         
         HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
         nullFilter.type = CM_ICMP_NO_FILTER;

         HcLiHitServOpenReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                               HIACC_RAW_SUCON_ID,
                               &hiAccCb.curTst.remAddr,
                               &hiAccCb.curTst.tPar,
                               &nullFilter, HI_SRVC_RAW_RSVP);
         hiAccCb.curTst.state++;
         break;

      case 1:    /* Wait here for the HitConfirm from TUCL*/
         break;

      case 2:
         /* Send data */
         msg =  hiAccCb.tstMsgs[0].msg;
         if(SAddMsgRef(msg, hiAccCb.init.region,
                        hiAccCb.init.pool, &msg1) != ROK)
         {
            HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst13: mem error!\n"))
            HI_ACC_TST_FAILED();
         }
         HITST_ZERO(&tPar, sizeof(tPar));
         tPar.type = CM_TPTPARAM_NOTPRSNT;

         HITST_ZERO(&nullAddr, sizeof(CmTptAddr));
         nullAddr.type = CM_TPTADDR_NOTPRSNT;

         HITST_ZERO(&ipv6HdrParam, sizeof(CmIpHdrParm));
         ipv6HdrParam.type = CM_HDRPARM_NOTPRSNT;  
         ipv6HdrParam.type = CM_HDRPARM_IPV6;

         ipv6HdrParam.u.hdrParmIpv6.ttl.pres = TRUE;
         ipv6HdrParam.u.hdrParmIpv6.ttl.val = 110;

         /* Fill up the HBH Option */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhHdrPrsnt = TRUE; 
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.numHBHOpts = 1;
         
         /* allocate memory for structure CmIpv6HBHHdr */
         /* after allocation of memory, initialize type, length & value */
         ret = SGetSBuf(hiAccCb.init.region, hiAccCb.init.pool, 
                        (Data **)&ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.
                                 hbhOptsArr.hbhOpts, 
                        (Size)sizeof(CmIpv6HBHHdr)); 
         if (ret != ROK)
         {
            RETVALUE(ROUTRES);
         }
        
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.hbhOpts[0].type =
                                                                        0x05;   
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.hbhOpts[0].length = 
                                                                        0x02;
         ret = SGetSBuf(hiAccCb.init.region, hiAccCb.init.pool, 
                        (Data **)&ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.
                                 hbhOptsArr.hbhOpts[0].value, (Size)2);
         if (ret != ROK)
         {
            RETVALUE(ROUTRES);
         }        
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.hbhOpts[0].value[0] =
                                                                         0x01;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.hbhOptsArr.hbhOpts[0].value[1] =
                                                                         0x00;
         /* Fill up the Dest Option */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsPrsnt = TRUE;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.numDestOpts = 1;

         /* right now we are unable to send all ext hdrs in the same packet.
          * may be due to a bug in Solaris implementation to handle IPV6 ext
          * hdrs. so this portion is under ifdef 0. this part be opened when
          * it is possible to send all IPV6 ext hdrs together in same sendmsg
          */
         ret = SGetSBuf(hiAccCb.init.region, hiAccCb.init.pool, 
                        (Data **)&ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.
                                 destOptsArr.destOpts, 
                        (Size)sizeof(CmIpv6DestOptsHdr)); 
         if (ret != ROK)
         {
            RETVALUE(ROUTRES);
         }
         /* Threre is NO Dest option proposed/supported yet. So we are testing
          * with padN option of size 6 bytes. For padN type 1, length is how 
          * many bytes are 0 and value bytes are 0 */         
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts[0].type =
                                                                        0x01;   
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts[0].length =
                                                                        0x04;
         ret = SGetSBuf(hiAccCb.init.region, hiAccCb.init.pool, 
                        (Data **)&ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.
                                 destOptsArr.destOpts[0].value, (Size)4);  
         if (ret != ROK)
         {
            RETVALUE(ROUTRES);
         }
         
         /* 4 bytes value field of 6-byte padding is 0 always! */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts[0].
                                                             value[0] = 0x00;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts[0].
                                                             value[1] = 0x00;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts[0].
                                                             value[2] = 0x00;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.destOptsArr.destOpts[0].
                                                             value[3] = 0x00;
         
         /* Fill up the Route Hdr Option */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOptsPrsnt = TRUE;
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.numAddrs = 2;
                 
         /* mention here which nodes needs to be strictly/loosely a neighbor
          * of each other. If bit 0 is 1 then first IPV6 addr in route hdr
          * must be a neighbor of original source. if this bit is 0 then 
          * originator may send the initial packet to anybody & later the 
          * packet arrives in IPV6 addr1 of route hdr. If bit1 of sl map
          * is 1 then IPV6 addr1 & addr2 in route hdr MUST be neighbor */

         /* first byte is always 0 as it is reserved!! */
         ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.slMap = 0x00c00000;
         
         lpBkAddr = in6addr_loopback;

         /* allocate memory required to hold all IPv6 addresses in the Route
          * Header here */
         num = ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.numAddrs;
         ret = SGetSBuf(hiAccCb.init.region, hiAccCb.init.pool, 
                        (Data **)&ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.
                        rtOpts.ipv6Addrs, (Size)(num * sizeof(CmIpv6NetAddr))); 
         if (ret != ROK)
         {
            RETVALUE(ROUTRES);
         }

         /* now copy IPv6 adresses one by one to the alloacated mem space */
         cmMemcpy((U8 *)ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.
                  ipv6Addrs[0], (U8 *)&lpBkAddr, sizeof(lpBkAddr));
         
         cmMemcpy((U8 *)ipv6HdrParam.u.hdrParmIpv6.ipv6ExtHdr.rtOpts.
                  ipv6Addrs[1], (U8 *)&lpBkAddr, sizeof(lpBkAddr));
                  
         HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                        hiAccCb.curTst.servSpConId,
                        &hiAccCb.curTst.remAddr,
                        &nullAddr, &ipv6HdrParam, &tPar, msg1);
         hiAccCb.curTst.state++;
         break;

      case 3:
         HIACCPRINT((hiAccCb.prntBuf, 
                    "hiAccTst13/case3: Waiting for UDatInd\n"))
         SThreadYield();
         break;

      case 4:
         hiAccCb.curTst.remAddr.u.ipv6TptAddr.port = 0;

         /* Disconnect the servers */
         HIACCPRINT((hiAccCb.prntBuf,
                        "hiAccTst13 : Disconnecting RSVP Socket\n"))

         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;

         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0,
                        HI_USER_CON_ID, HIACC_RAW_SUCON_ID,
                           HI_CLOSE, &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state ++;
         break;

      case 5:
         break;

      case 6:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */

         HIACCPRINT((hiAccCb.prntBuf,
                        "hiAccTst13:Disconnecting Raw Socket\n"))
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_USER_CON_ID,
                        (HIACC_RAW_SUCON_ID), HI_CLOSE,
                        &hiAccCb.curTst.tPar);
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;

   }/* end switch */

   RETVALUE(ROK);
} /* end of hiAccTst13 */
#endif /* IPV6_OPTS_SUPPORTED */
#endif /* IPV6_SUPPORTED */

#ifdef HI_RUG
/*
*
*       Fun:   hiAccTst14
*
*       Desc:  This test case verifies that the TUCL can handle the system
*              Agent SHT control request primitives for getting the Interface 
*              Version implemented by TUCL correctly. The version info that
*              will be retrieved by the request is the one that was stored 
*              during general configuration.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst14
(
Void
)
#else
PUBLIC S16 hiAccTst14()
#endif
{
   HiShMsg    shMsg;
   S16        ret;   
   
   TRC2(hiAccTst14)

   HI_ZERO((U8*)&shMsg, sizeof(HiShMsg));

   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         HIACCPRINT((hiAccCb.prntBuf, "\tPurpose: Get stored ver info during genCfg and verify\n"))
         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;
         
         /* remove whatever is in the queue before starting this test case */
         /* hiEmptyQ(); */
         HIACCPRINT((hiAccCb.prntBuf, "\tFlushing the Queue .....\n"))
         SFlushQueue(&shRxQ);
         
         /* make call to TUCL. Once TUCL gets this request via hi_ex_ms.c,
          * it will process this request by function HiMiShtCntrlReq. Then
          * from HiMiShtCntrlReq, TUCL will call hiGetVer() to get the version
          * stored and return to SH by HiMiShtCntrlCfm. The shActvTsk() in
          * hi_accsh.c will get this ShtCntrlCfm & write the version info it
          * gets from this ShtCntrlCfm to common Q which will be read by this
          * test function */
        
         HIACCPRINT((hiAccCb.prntBuf, "\t===> Send Control Request to Get Version Info\n"))
         hiAccSendShCntrl(SHT_REQTYPE_GETVER, 0, 0, 0, 0, 0, 0);
         
         checkMsg = 0;
         hiAccCb.curTst.state ++;
         break;
         
      case 1:
         
         /* deQueue the version info and verify */
         if ((ret = hiShDeq(&shMsg)) != ROK)
         {
            HIACCPRINT((hiAccCb.prntBuf, "\tWaiting for control confm .....\n"))
            if (checkMsg > HI_ACC_MAX_NUM_OF_SH_MSG)
               HIACCPRINT((hiAccCb.prntBuf, "\tNo response from TUCL: There are no ver info in Q\n"))
            checkMsg++;

            /* no need to go to next state until there is something in the Q */
         }
         else 
         {
            HIACCPRINT((hiAccCb.prntBuf, "\t<=== Control confm received!!\n"))
            /* there is something in the Q! */
            if (shMsg.event != EVTSHTCNTRLCFM)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid event present\n"))

            if (shMsg.t.s.cfmInfo.transId != HI_ACC_TRANSID)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid trans id!\n"))

            if (shMsg.t.s.cfmInfo.status.status != LCM_REASON_NOT_APPL)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid confirm status!\n"))

            /* validate interface version informations */
            if ((shMsg.t.s.cfmInfo.t.gvCfm.numUif != 1) ||
                (shMsg.t.s.cfmInfo.t.gvCfm.uifList[0].intfId != HITIF) ||
                (shMsg.t.s.cfmInfo.t.gvCfm.uifList[0].intfVer != HITIFVER)) 
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid interface version info returned\n"))
            else
               HIACCPRINT((hiAccCb.prntBuf, "\tReceived version Info is Correct\n"))

            /* move to next test state */
            hiAccCb.curTst.state ++;                  
         }
         break;

      case 2:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */

         HIACCPRINT((hiAccCb.prntBuf, "\thiAccTst14: Error state has been reached!! \n"))
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;
   }      

   RETVALUE(ROK);
} /* hiAccTst14 */

/*
*
*       Fun:   hiAccTst15
*
*       Desc:  This test case ensures that TUCL layer support configuration
*       of remote interface version in SAP by Layer Manager.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst15
(
Void
)
#else
PUBLIC S16 hiAccTst15()
#endif
{
   HiShMsg    shMsg;
   S16        ret; 

   HiMngmt    sta;

   TRC2(hiAccTst15)
      
   /* clear the config structure first */
   HI_ZERO((U8 *)&sta, sizeof(HiMngmt));   
   HI_ZERO((U8*)&shMsg, sizeof(HiShMsg));

   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         HIACCPRINT((hiAccCb.prntBuf, "\tPurpose: TUCL layer support config of ver info by LM\n"))
         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;
         
         /* remove whatever is in the queue before starting this test case */
         /* hiEmptyQ(); */
         HIACCPRINT((hiAccCb.prntBuf, "\tFlushing the Queue\n"))
         SFlushQueue(&shRxQ);
         
         /* configure 2nd sap without valid intf ver. We also set 
          * invalid version info on 1st sap inside tst() before calling 
          * hiAccSapCfg() to configure the first sap */

         remIntfValid = FALSE;
         remHitIntfVer = HITIFVER - 1;
         
#ifdef HI_LKSCTP
#else
         hiAccSapCfg(HI_ACC_SAP_1);
#endif
   
         remIntfValid = TRUE;
         remHitIntfVer = HITIFVER;
         
         HIACCPRINT((hiAccCb.prntBuf, "\t====> Send New SAP Config req with spId 1\n"))
         checkMsg = 0;
         hiAccCb.curTst.state ++;
         break;
         
      case 1:
         
         HIACCPRINT((hiAccCb.prntBuf, "\t<==== Sap got configured \n"))
         /* deQueue the version info and verify */

         /* the sap confirmation info will be printed from hiAccProcCfgCfm()
          * function of hi_acc1.c file. So No need to verify here! */

         /* same applies for sap bind request */
            
         /* move to next test state */
         hiAccCb.curTst.state ++;                  
         
         break;
      case 2:
         sta.hdr.elmId.elmnt = STTSAP;
#ifdef LCHIMILHI
         sta.hdr.response.selector = LHI_LC;
#else
         sta.hdr.response.selector = LHI_TC;
#endif
         /* use the spId which we used in hiAccSapCfg call in case 0 */
         sta.t.ssta.s.sapSta.spId = 1; 
                                         
         /* set HIT interface version info in smPst */
         hiAccCb.smPst.intfVer = LHIIFVER;
        
         HIACCPRINT((hiAccCb.prntBuf, "\t====> Send Status Req for the new SAP\n"))
         /* send a status request for the above sap we configured */
         ret = SmMiLhiStaReq(&hiAccCb.smPst, &sta);
         
         /* status confirmation will be printed from hiAccProcStaCfm()
          * function of hi_acc1.c */
         
         /* move to next test state */
         hiAccCb.curTst.state ++;
         
      case 3:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */

         HIACCPRINT((hiAccCb.prntBuf, "\thiAccTst15: Error state has been reached!! \n"))
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;
   }      

   RETVALUE(ROK);
} /* hiAccTst15 */

/*
*
*       Fun:   hiAccTst16
*
*       Desc:  This test case ensures that TUCL layer supports configuration
*       of interface version number to be used in generating alarm and trace
*       indication and uses this version number to generate these indication
*       primitives.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst16
(
Void
)
#else
PUBLIC S16 hiAccTst16()
#endif
{
   HiShMsg    shMsg;
   S16        ret; 

   HiMngmt    sta;

   TRC2(hiAccTst16)
      
   /* clear the config structure first */
   HI_ZERO((U8 *)&sta, sizeof(HiMngmt));   
   HI_ZERO((U8*)&shMsg, sizeof(HiShMsg));

   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         HIACCPRINT((hiAccCb.prntBuf, 
                 "\tPurpose: Verify that TUCL support config of ver num to\n"))
         HIACCPRINT((hiAccCb.prntBuf, "\t\tbe used in generating alarms and "))
         HIACCPRINT((hiAccCb.prntBuf, "uses that ver num in alarms\n"))
         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;
         
         /* remove whatever is in the queue before starting this test case */
         /* hiEmptyQ(); */
         HIACCPRINT((hiAccCb.prntBuf, "\tFlushing the Queue .....\n"))
         SFlushQueue(&shRxQ);
         
         /* do a general configuration */
         /* we don't allow reconfiguration of general configuration */
         /* so this step will be done automatically at the beginning */
         
         HIACCPRINT((hiAccCb.prntBuf, "\tGeneral config done automatic at start\n"))
         checkMsg = 0;
         hiAccCb.curTst.state ++;
         break;
         
      case 1:
         
         HIACCPRINT((hiAccCb.prntBuf, "\tVerify that product data structure updated \n"))
         /* now verify that the product data structures got updated */
         hiAccSendShCntrl(SHT_REQTYPE_GETVER, 0, 0, 0, 0, 0, 0);         
         /* move to next test state */
         hiAccCb.curTst.state ++;                  
         
         break;
         
      case 2:
         /* deQueue the version info and verify */
         if ((ret = hiShDeq(&shMsg)) != ROK)
         {
            HIACCPRINT((hiAccCb.prntBuf, "\tWaiting for control confm\n"))
            if (checkMsg > HI_ACC_MAX_NUM_OF_SH_MSG)
               HIACCPRINT((hiAccCb.prntBuf, "\tNo response from TUCL: There are no ver info in Q\n"))
            checkMsg++;

            /* no need to go to next state until there is something in the Q */
         }
         else 
         {
            HIACCPRINT((hiAccCb.prntBuf, "\t<=== Control confm received!!\n"))
            /* there is something in the Q! */
            if (shMsg.event != EVTSHTCNTRLCFM)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid event present\n"))

            if (shMsg.t.s.cfmInfo.transId != HI_ACC_TRANSID)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid trans id!\n"))

            if (shMsg.t.s.cfmInfo.status.status != LCM_REASON_NOT_APPL)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid confirm status!\n"))

            /* validate interface version informations */
            if ((shMsg.t.s.cfmInfo.t.gvCfm.numUif != 1) ||
                (shMsg.t.s.cfmInfo.t.gvCfm.uifList[0].intfId != HITIF) ||
                (shMsg.t.s.cfmInfo.t.gvCfm.uifList[0].intfVer != HITIFVER)) 
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid interface version info returned\n"))
            else
            {
               HIACCPRINT((hiAccCb.prntBuf, 
                          "\tReceived version Info is Correct!\n"))
               HIACCPRINT((hiAccCb.prntBuf, 
                          "\tProduct data structures got updated correctly!\n"))
            }

            /* move to next test state */
            hiAccCb.curTst.state ++;                  
         }
         break;
         
      case 3:
         
         /* send a bind request to an invalid sap */
         /* this will cause TUCL to generate an alarm to LM and the version
          * number in the generated alarm is LHIIFVER - 1 */
        
         HIACCPRINT((hiAccCb.prntBuf, 
                    "\t===> Send a bind request to an invalid sap\n"))
         HIACCPRINT((hiAccCb.prntBuf, 
                    "\t2 Alarms will be generated to LM!!!\n"))

         /* set HIT interface version info in uiPst */
         hiAccCb.uiPst.intfVer = HITIFVER;
         
         /* trying to bind to invalid sap by sending incorrect spId */
         HcLiHitBndReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_ACC_NUMBSAPS + 10); 
         
         /* move to next test state */
         hiAccCb.curTst.state ++;
         
      case 4:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */

         HIACCPRINT((hiAccCb.prntBuf, "\thiAccTst16: Error state has been reached!! \n"))
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;
   }      

   RETVALUE(ROK);
} /* hiAccTst16 */

/*
*
*       Fun:   hiAccTst17
*
*       Desc:  This test case ensures that TUCL layer can handle the system
*       agent SHT control request primitives for setting the interface version
*       implemented by TUCL.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst17
(
Void
)
#else
PUBLIC S16 hiAccTst17()
#endif
{
   HiShMsg    shMsg;
   S16        ret; 

   HiMngmt    sta;

   HiSap      *sap;  /* transport SAP */
   U16        i;     /* loop counter */

   TRC2(hiAccTst17)
      
   /* clear the config structure first */
   HI_ZERO((U8 *)&sta, sizeof(HiMngmt));   
   HI_ZERO((U8*)&shMsg, sizeof(HiShMsg));

   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         HIACCPRINT((hiAccCb.prntBuf, 
                 "\tPurpose: Verify thar TUCL Sets Version Info correctly\n"))
         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;
         
         /* remove whatever is in the queue before starting this test case */
         /* hiEmptyQ(); */
         HIACCPRINT((hiAccCb.prntBuf, "\tFlushing the Queue ....\n"))
         SFlushQueue(&shRxQ);
         
         /* do a general configuration */
         /* we don't allow reconfiguration of general configuration */
         /* so this step will be done automatically at the beginning */
         checkMsg = 0;
         hiAccCb.curTst.state++;
         break;
         
      case 1:
         
         HIACCPRINT((hiAccCb.prntBuf, "\t====> Send control req to setVer\n"))
         /* now verify that the product data structures got updated */
         hiAccSendShCntrl(SHT_REQTYPE_SETVER, SHT_GRPTYPE_ALL, SFndProcId(),
                          ENTHC, 0, HITIF, HITIFVER);         
         /* move to next test state */
         hiAccCb.curTst.state ++;                  
         
         break;
         
      case 2:
         /* deQueue the version info and verify */
         if ((ret = hiShDeq(&shMsg)) != ROK)
         {
            HIACCPRINT((hiAccCb.prntBuf, "\tWaiting for control confm\n"))
            if (checkMsg > HI_ACC_MAX_NUM_OF_SH_MSG)
               HIACCPRINT((hiAccCb.prntBuf, "\tNo response from TUCL\n"))
            checkMsg++;

            /* no need to go to next state until there is something in the Q */
         }
         else 
         {
            HIACCPRINT((hiAccCb.prntBuf, "\t<==== Control confm received!!\n"))
            /* there is something in the Q! */
            if (shMsg.event != EVTSHTCNTRLCFM)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid event present\n"))

            if (shMsg.t.s.cfmInfo.transId != HI_ACC_TRANSID)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid trans id!\n"))

            if (shMsg.t.s.cfmInfo.status.status != LCM_REASON_NOT_APPL)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid confirm status!\n"))

            /* validate interface version informations */
            if ((hiCb.numIntfInfo != 1) ||
                (hiCb.intfInfo[0].grpType      != SHT_GRPTYPE_ALL) ||
                (hiCb.intfInfo[0].dstProcId    != SFndProcId()) ||
                (hiCb.intfInfo[0].dstEnt.ent   != ENTHC) ||
                (hiCb.intfInfo[0].dstEnt.inst  != TSTINST) ||
                (hiCb.intfInfo[0].intf.intfId  != HITIF) ||
                (hiCb.intfInfo[0].intf.intfVer != HITIFVER)) 
               HIACCPRINT((hiAccCb.prntBuf, "\tFailed to set Version Info\n"))
            else
               HIACCPRINT((hiAccCb.prntBuf, 
                          "\tVersion Info is Set Correctly in hiCb!\n"))

            /* move to next test state */
            hiAccCb.curTst.state ++;                  
         }
         break;
         
      case 3:
         /* verify that the validity of interface version is still Invalid as
          * the sap is not yet bound. Not calling getVet directly access sap
          * and hiCb structures. */
         for (i = 1; i < hiCb.cfg.numSaps; i++)
         {
            sap = hiCb.saps[i];

            if (!sap)
               continue;

            if(sap->remIntfValid == FALSE)
               HIACCPRINT((hiAccCb.prntBuf, 
                          "\tInvalid Version Info on sap %d. This is correct as sap is not bound yet!!\n", i))
            else
               HIACCPRINT((hiAccCb.prntBuf, 
                       "\tVersion Info Valid on sap %d!. This is WRONG!\n", i))
         }
         
         /* move to next test state */
         hiAccCb.curTst.state ++;

         /* repeating the above three steps with SHT_GRPTYPE_ENT */
      case 4:
         
         /* send a bind request to the second sap just configured */
        
         HIACCPRINT((hiAccCb.prntBuf, 
                    "\t===> Send a bind request to the second sap\n"))

         hiAccCb.uiPst.srcEnt = ENTHC;
         hiAccCb.uiPst.srcProcId = SFndProcId();/* source processor id */

         /* set HIT interface version info in uiPst */
         hiAccCb.uiPst.intfVer = HITIFVER;
         
         /* trying to bind to invalid sap by sending incorrect spId */
         HcLiHitBndReq(&hiAccCb.uiPst, (SuId)HI_ACC_SAP_1, (SpId)HI_ACC_SAP_1); 
         
         /* move to next test state */
         hiAccCb.curTst.state ++;

         break;

      case 5:
         sap = hiCb.saps[1];

         if((sap->remIntfValid == FALSE) &&
            (sap->uiPst.intfVer != HITIFVER))
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                       "\tIntfVer is NOT set on 2nd sap on Bind Req! Wrong!\n"))
         }
         else
               HIACCPRINT((hiAccCb.prntBuf, 
                       "\tVersion Info Valid on sap 1. Correct!\n"))

         /* move to next test state */
         hiAccCb.curTst.state ++;
         break;

      case 6:
         /* configure 3rd sap without valid intf ver. We also set 
          * invalid version info on 1st sap inside tst() before calling 
          * hiAccSapCfg() to configure the first sap */

         remIntfValid = FALSE;
         remHitIntfVer = HITIFVER - 1;
         
#ifdef HI_LKSCTP
#else
         hiAccSapCfg(HI_ACC_SAP_2);
#endif
   
         remIntfValid = TRUE;
         remHitIntfVer = HITIFVER;
         
         HIACCPRINT((hiAccCb.prntBuf, 
               "\t====> Send New SAP Config req with spId 1\n"))
         checkMsg = 0;
         hiAccCb.curTst.state ++;
         
         break;
         
      case 7:
         HIACCPRINT((hiAccCb.prntBuf, "\t<==== Sap got configured \n"))
         HIACCPRINT((hiAccCb.prntBuf, "\t====> Send control req to setVer\n"))
         /* now verify that the product data structures got updated */
         hiAccSendShCntrl(SHT_REQTYPE_SETVER, SHT_GRPTYPE_ALL, 
                          (ProcId)(SFndProcId() + 1), ENTHC, 0, 
                          HITIF, HITIFVER - 1);         
         /* move to next test state */
         hiAccCb.curTst.state ++;                  
         
         break;

      case 8:
         /* deQueue the version info and verify */
         if ((ret = hiShDeq(&shMsg)) != ROK)
         {
            HIACCPRINT((hiAccCb.prntBuf, "\tWaiting for control confm\n"))
            if (checkMsg > HI_ACC_MAX_NUM_OF_SH_MSG)
               HIACCPRINT((hiAccCb.prntBuf, "\tNo response from TUCL\n"))
            checkMsg++;

            /* no need to go to next state until there is something in the Q */
         }
         else 
         {
            HIACCPRINT((hiAccCb.prntBuf, "\t<==== Control confm received!!\n"))
            /* there is something in the Q! */
            if (shMsg.event != EVTSHTCNTRLCFM)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid event present\n"))

            if (shMsg.t.s.cfmInfo.transId != HI_ACC_TRANSID)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid trans id!\n"))

            if (shMsg.t.s.cfmInfo.status.status != LCM_REASON_NOT_APPL)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid confirm status!\n"))

            /* validate interface version informations */
            if ((hiCb.numIntfInfo != 2) ||
                (hiCb.intfInfo[1].grpType      != SHT_GRPTYPE_ALL) ||
                (hiCb.intfInfo[1].dstProcId    != (SFndProcId() + 1)) ||
                (hiCb.intfInfo[1].dstEnt.ent   != ENTHC) ||
                (hiCb.intfInfo[1].dstEnt.inst  != TSTINST) ||
                (hiCb.intfInfo[1].intf.intfId  != HITIF) ||
                (hiCb.intfInfo[1].intf.intfVer != HITIFVER - 1)) 
               HIACCPRINT((hiAccCb.prntBuf, "\tFailed to set Version Info\n"))
            else
               HIACCPRINT((hiAccCb.prntBuf, 
                          "\tVersion Info is Set Correctly in hiCb!\n"))

            /* move to next test state */
            hiAccCb.curTst.state ++;                  
         }         
         break;

      case 9:
         /* verify that the validity of interface version is still Invalid on
          * the 3rd sap as it is not yet bound. But other sap's ver info still
          * remains unchanged */
         sap = hiCb.saps[1];

         if((sap->remIntfValid == TRUE) &&
            ((sap->uiPst.intfVer == HITIFVER)))
            HIACCPRINT((hiAccCb.prntBuf, 
                       "\tVersion Info unaffected on sap 1. Correct!\n"))
         else
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                      "\tVersion Info affected sap 1. Failure!!\n"))
         }
         
         sap = hiCb.saps[2];

         if(sap->remIntfValid == TRUE)
         {
            HIACCPRINT((hiAccCb.prntBuf, 
               "\tVersion Info set on sap 2. Wrong as it is not bound!\n"))
         }
         else
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                      "\tVersion Info invalid on sap 2. Correct!!\n"))
         }
         
         /* move to next test state */
         hiAccCb.curTst.state ++;
         break;

      case 10:

         HIACCPRINT((hiAccCb.prntBuf, 
                    "\t===> Send a bind request to the third sap\n"))

         hiAccCb.uiPst.srcEnt = ENTHC;
         hiAccCb.uiPst.srcProcId = SFndProcId();/* + 1; source processor id */

         /* trying to bind to the third sap*/
         HcLiHitBndReq(&hiAccCb.uiPst, (SuId)HI_ACC_SAP_2, (SpId)HI_ACC_SAP_2); 
         
         /* move to next test state */
         hiAccCb.curTst.state ++;
         break;

      case 11:
         /* verifying that the 3rd sap got updated with ver info */
         HIACCPRINT((hiAccCb.prntBuf, 
                    "\tVerify Version Info on third sap\n"))
         sap = hiCb.saps[2];

         if((sap->remIntfValid == TRUE) &&
            ((sap->uiPst.intfVer == HITIFVER - 1)))
            HIACCPRINT((hiAccCb.prntBuf, 
                       "\tVersion Info updated on the third sap. Correct!\n"))
         else
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                      "\tVersion Info non-affected on third sap. Failure!!\n"))
         }
         hiAccCb.curTst.state ++;
         break;

      case 12:
         HIACCPRINT((hiAccCb.prntBuf, 
                    "\t===> Send a Unbind Disable Cntrl req to the 2nd sap\n"))
         hiAccCntrlReq(1, (Elmnt)STTSAP, (U8)AUBND_DIS, (U8)SAELMNT, (U32)0);
         HIACCPRINT((hiAccCb.prntBuf, 
                  "\t===> Send a Unbind Disable Cntrl req to the third sap\n"))
         hiAccCntrlReq(2, (Elmnt)STTSAP, (U8)AUBND_DIS, (U8)SAELMNT, (U32)0);
         hiAccCb.curTst.state ++;
         break;         

      case 13:
         break;
         
      case 14:
         break;
         
      case 15:
         HIACCPRINT((hiAccCb.prntBuf, 
                    "\t<===  Cntrl Cfm recvd for the 2nd sap\n"))
         HIACCPRINT((hiAccCb.prntBuf, 
                    "\t<=== Cntrl Cfm recvd for the 3rd sap \n"))
         hiAccCb.curTst.state ++;
         break;
         
      case 16:
         HIACCPRINT((hiAccCb.prntBuf, 
                    "\tVerify that saps are unbound and ver info Invalid\n"))
         /* get the 2nd sap */
         sap = hiCb.saps[1];

         if((sap->remIntfValid == FALSE) &&
            (sap->state == HI_ST_UBND))
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                       "\tVersion Info on 2nd sap Invalid. Correct!  "))
            HIACCPRINT((hiAccCb.prntBuf, 
                       "\t2nd sap is Unbound. Also Correct!\n"))
         }
         else 
         {
            if(sap->remIntfValid == TRUE)         
               HIACCPRINT((hiAccCb.prntBuf, 
                      "\tVersion Info on 2nd sap Valid. Wrong!!  "))
                  
            if(sap->state != HI_ST_UBND)         
               HIACCPRINT((hiAccCb.prntBuf, 
                      "\t2nd sap is still Bound! Wrong!!\n"))
         }
         
         /* get the 3rd sap */
         sap = hiCb.saps[2];

         if((sap->remIntfValid == FALSE) &&
            (sap->state == HI_ST_UBND))
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                       "\tVersion Info on 3rd sap Invalid. Correct!  "))
            HIACCPRINT((hiAccCb.prntBuf, 
                       "\t3rd sap is Unbound. Also Correct!\n"))
         }
         else 
         {
            if(sap->remIntfValid == TRUE)         
               HIACCPRINT((hiAccCb.prntBuf, 
                      "\tVersion Info on 3rd sap Valid. Wrong!!  "))
                  
            if(sap->state != HI_ST_UBND)         
               HIACCPRINT((hiAccCb.prntBuf, 
                      "\t3rd Sap is still Bound! Wrong!!\n"))
         }
         
         /* move to next test state */
         hiAccCb.curTst.state++;         
         break;

      case 17:
         HIACCPRINT((hiAccCb.prntBuf, "\t====> Send control req to setVer\n"))
         /* now verify that the product data structures got updated */
         hiAccSendShCntrl(SHT_REQTYPE_SETVER, SHT_GRPTYPE_ALL, 
                          (ProcId)(SFndProcId() + 1), ENTHC, 0, 
                          HITIF, HITIFVER);         
         /* move to next test state */
         hiAccCb.curTst.state++;                  
         
         break;

      case 18:
         /* deQueue the version info and verify */
         if ((ret = hiShDeq(&shMsg)) != ROK)
         {
            HIACCPRINT((hiAccCb.prntBuf, "\tWaiting for control confm\n"))
            if (checkMsg > HI_ACC_MAX_NUM_OF_SH_MSG)
               HIACCPRINT((hiAccCb.prntBuf, "\tNo response from TUCL\n"))
            checkMsg++;

            /* no need to go to next state until there is something in the Q */
         }
         else 
         {
            HIACCPRINT((hiAccCb.prntBuf, "\t<==== Control confm received!!\n"))
            /* there is something in the Q! */
            if (shMsg.event != EVTSHTCNTRLCFM)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid event present\n"))

            if (shMsg.t.s.cfmInfo.transId != HI_ACC_TRANSID)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid trans id!\n"))

            if (shMsg.t.s.cfmInfo.status.status != LCM_REASON_NOT_APPL)
               HIACCPRINT((hiAccCb.prntBuf, "\tInvalid confirm status!\n"))

            /* validate interface version informations */
            if ((hiCb.numIntfInfo != 2) ||
                (hiCb.intfInfo[1].grpType      != SHT_GRPTYPE_ALL) ||
                (hiCb.intfInfo[1].dstProcId    != (SFndProcId() + 1)) ||
                (hiCb.intfInfo[1].dstEnt.ent   != ENTHC) ||
                (hiCb.intfInfo[1].dstEnt.inst  != TSTINST) ||
                (hiCb.intfInfo[1].intf.intfId  != HITIF) ||
                (hiCb.intfInfo[1].intf.intfVer != HITIFVER)) 
               HIACCPRINT((hiAccCb.prntBuf, "\tFailed to set Version Info\n"))
            else
               HIACCPRINT((hiAccCb.prntBuf, 
                          "\tVersion Info is Set Correctly in hiCb!\n"))

            /* move to next test state */
            hiAccCb.curTst.state++;                  
         }         
         break;

      case 19:

         /* verify that existing stored info is updated and no new entry
          * created for this cntrlReq */
          if (hiCb.numIntfInfo > 2)
             HIACCPRINT((hiAccCb.prntBuf, 
                        "\tNew Entry created for intfInfo. Wrong!!\n"))
          else if (hiCb.numIntfInfo == 2)
             HIACCPRINT((hiAccCb.prntBuf, 
                        "\tNew Entry NOT created for intfInfo. Correct!!\n"))
          
         /* verify that the validity of interface version is still Invalid on
          * the 2nd and 3rd sap as they are not yet bound. */
         sap = hiCb.saps[1];

         if(sap->remIntfValid == FALSE)
            HIACCPRINT((hiAccCb.prntBuf, 
                     "\tVersion Info Invalid on Unbound 2nd sap. Correct!\n"))
         else
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                     "\tVersion Info Valid on Unbound 2nd sap. Wrong.!\n"))
         }
         
         sap = hiCb.saps[2];

         if(sap->remIntfValid == FALSE)
            HIACCPRINT((hiAccCb.prntBuf, 
                     "\tVersion Info Invalid on Unbound 3rd sap. Correct!\n"))
         else
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                     "\tVersion Info Valid on Unbound 3rd sap. Wrong!\n"))
         }
         
         /* move to next test state */
         hiAccCb.curTst.state++;
         break;         

      case 20:

         HIACCPRINT((hiAccCb.prntBuf, 
                    "\t===> Send a bind request to the 2nd sap\n"))

         hiAccCb.uiPst.srcEnt = ENTHC;
         hiAccCb.uiPst.srcProcId = SFndProcId() + 1;

         /* trying to bind to the third sap*/
         HcLiHitBndReq(&hiAccCb.uiPst, (SuId)HI_ACC_SAP_1, (SpId)HI_ACC_SAP_1); 
         /* move to next test state */
         hiAccCb.curTst.state++;
         break;

      case 21:
         /* verifying that the 2nd sap got updated with ver info */
         HIACCPRINT((hiAccCb.prntBuf, 
                    "\tVerify Version Info on 2nd sap\n"))
         sap = hiCb.saps[1];

         if((sap->remIntfValid == TRUE) &&
            ((sap->uiPst.intfVer == HITIFVER)))
            HIACCPRINT((hiAccCb.prntBuf, 
                       "\tVersion Info updated on the 2nd sap. Correct!\n"))
         else
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                      "\tVersion Info non-affected on 2nd sap. Failure!!\n"))
         }
         hiAccCb.curTst.state++;
         break;
         
      case 22:

         HIACCPRINT((hiAccCb.prntBuf, 
                    "\t===> Send a bind request to the 3rd sap\n"))

         hiAccCb.uiPst.srcEnt = ENTHC;
         hiAccCb.uiPst.srcProcId = SFndProcId() + 1;

         /* trying to bind to the third sap*/
         HcLiHitBndReq(&hiAccCb.uiPst, (SuId)HI_ACC_SAP_2, (SpId)HI_ACC_SAP_2); 
         
         /* move to next test state */
         hiAccCb.curTst.state++;
         break;

      case 23:
         /* verifying that the 2nd sap got updated with ver info */
         HIACCPRINT((hiAccCb.prntBuf, 
                    "\tVerify Version Info on 3rd sap\n"))
         sap = hiCb.saps[2];

         if((sap->remIntfValid == TRUE) &&
            ((sap->uiPst.intfVer == HITIFVER)))
            HIACCPRINT((hiAccCb.prntBuf, 
                       "\tVersion Info updated on the 3rd sap. Correct!\n"))
         else
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                      "\tVersion Info non-affected on 3rd sap. Failure!!\n"))
         }
         hiAccCb.curTst.state++;
         break;

      case 24:
         hiAccCntrlReq(1, (Elmnt)STTSAP, (U8)ADEL, (U8)SAELMNT, (U32)0);
         hiAccCntrlReq(2, (Elmnt)STTSAP, (U8)ADEL, (U8)SAELMNT, (U32)0);
         hiAccCb.curTst.state++;
         break;

      case 25:
         break;

      case 26:
         break;
         
      case 27:
         /* need to set this variable to zero */
         hiCb.numIntfInfo = 0;

         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;
         
      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */

         HIACCPRINT((hiAccCb.prntBuf, 
                    "\thiAccTst17: Error state has been reached!! \n"))
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;
   }      

   RETVALUE(ROK);
} /* hiAccTst17 */
#endif /* HI_RUG */



/* hi002.105 (hi029.104) -Addition hiAccTst20 */
/*
*
*       Fun:   hiAccTst20
*
*       Desc:  This test case ensures that TUCL layer support deletion of TSAP
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst20
(
Void
)
#else
PUBLIC S16 hiAccTst20()
#endif
{
   S16        ret; 
   S16        i; 
   PRIVATE S16 cnt;
   HiMngmt    cntrl;
   CmIcmpFilter nullFilter;

   TRC2(hiAccTst20)
      
   /* clear the config structure first */
   HI_ZERO((U8 *)&cntrl, sizeof(HiMngmt));   

   switch(hiAccCb.curTst.state)
   {
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);
         HIACCPRINT((hiAccCb.prntBuf, "\tPurpose: TUCL : T-SAP deletion \n"))

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;
         
         /* configure Second SAP */ 
         HIACCPRINT((hiAccCb.prntBuf, "\t====> Send New SAP Config req with spId 1\n"))
#ifdef HI_LKSCTP
#else
         hiAccSapCfg(HI_ACC_SAP_1);
#endif
         hiAccCb.curTst.state ++;
         break;
         
      case 1:
         
         HIACCPRINT((hiAccCb.prntBuf, "\t<==== Sap got configured \n"))

         hiAccCb.curTst.state ++;                  
         
         break;
       
      case 2:
         
         /* send a bind request to the second sap just configured */
        
         HIACCPRINT((hiAccCb.prntBuf, 
                    "\t===> Send a bind request to the second sap\n"))

         hiAccCb.uiPst.srcEnt = ENTHC;
         hiAccCb.uiPst.srcProcId = SFndProcId();/* source processor id */

         /* trying to bind to invalid sap by sending incorrect spId */
         HcLiHitBndReq(&hiAccCb.uiPst, (SuId)HI_ACC_SAP_1, (SpId)HI_ACC_SAP_1); 
         
         /* move to next test state */
         hiAccCb.curTst.state ++;

         break;
     case 3:
         HIACCPRINT((hiAccCb.prntBuf, "\t<==== Second Sap bound \n"))
         /* deQueue the version info and verify */

         hiAccCb.curTst.state ++;                  
         break;

     case 4:
         HIACCPRINT((hiAccCb.prntBuf, 
                    "\t===> Send a ServOpenReq on Second Sap\n"))
          
         /* Initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV4;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.address =  HI_ACC_SERV_ADDR;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_2;

         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
         hiAccCb.curTst.tPar.u.sockParam.numOpts = 1;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option = 
                                            CM_SOCKOPT_OPT_REUSEADDR;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level  = 
                                            CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.value = 
                                            CM_SOCKOPT_ENABLE;
         for(i = 0; i < HIACC_UDP_MAX_SERV; i++)
         {
            HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
            nullFilter.type = CM_ICMP_NO_FILTER;
            HcLiHitServOpenReq(&hiAccCb.uiPst, HI_ACC_SAP_1, 
                               i, &hiAccCb.curTst.remAddr, 
                               &hiAccCb.curTst.tPar, &nullFilter, 
                               HI_SRVC_UDP);

            hiAccCb.curTst.remAddr.u.ipv4TptAddr.port += 1;
         }
         cnt =0;
         hiAccCb.curTst.state++;
         break;

      case 5:
         break;

      case 6:
         HIACCPRINT((hiAccCb.prntBuf, 
                    "\t<=== Received Connection Cfm \n"))
         cnt++;
         if (cnt <  HIACC_UDP_MAX_SERV)
         {
            hiAccCb.curTst.state--;
         }
         else
         {
            hiAccCb.curTst.state++;
            cnt =0;
         }
         break;
      case 7:
         cntrl.hdr.elmId.elmnt = STTSAP;
         cntrl.hdr.entId.ent   = ENTHI;           /* entity */
         cntrl.hdr.entId.inst  = TSTINST;         /* instance */
         cntrl.hdr.transId     = HI_ACC_TRANSID;  /* transaction identifier */

#ifdef LCHIMILHI
         cntrl.hdr.response.selector = LHI_LC;
#else
         cntrl.hdr.response.selector = LHI_TC;
#endif
         /* use the spId which we used in hiAccSapCfg call in case 0 */
         cntrl.t.cntrl.ctlType.sapId= 1;
         cntrl.t.cntrl.action = ADEL;
         cntrl.t.cntrl.subAction = SAELMNT;
                                         
         HIACCPRINT((hiAccCb.prntBuf, "\t====> Send Del Req for the new SAP\n"))

         /* send SAP delete request */
         ret = SmMiLhiCntrlReq(&hiAccCb.smPst, &cntrl);
         
         /* move to next test state */
         hiAccCb.curTst.state ++;
         
      case 8:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */

         HIACCPRINT((hiAccCb.prntBuf, "\thiAccTst20: Error state has been reached!! \n"))
         hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;
   }      

   RETVALUE(ROK);
} /* hiAccTst20 */






/*hi005.201 Added timer based resource checking in case of conjestion*/ 
#ifdef HI_CONG_CHECK_TMR 

/*
*
*       Fun:   hiAccTst45
*
*       Desc:  This test case opens HIACC_UDP_MAX_SERV number of TUCL
*              UDP servers. It then sends a message to each of these
*              servers from tstTbl array. The messages received by the
*              servers  HcLiHitUDatInd (in layer5.c)are not freed to creat
*              the resource conjestion. once the conjestion happened 
*              depending on the conjestionStatus, memory is freed
*              and again data transfer begins for some more times and closes
*              all TUCL servers.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccTst45
(
Void
)
#else
PUBLIC S16 hiAccTst45()
#endif
{

   Buffer         *msg, *msg1;
   U32            i = 0;
   static U8      cnt = 0;
   CmTptAddr      nullAddr;
   CmIcmpFilter   nullFilter;
   CmIpHdrParm    nullHdr;
   CmTptParam     tPar;
   S16            ret = 0;

   TRC2(hiAccTst45)

   HI_ZERO((U8*)&nullAddr, sizeof(CmTptAddr));
   HI_ZERO((U8*)&nullFilter, sizeof(CmIcmpFilter));
   HI_ZERO((U8*)&nullHdr, sizeof(CmIpHdrParm));
   HI_ZERO((U8*)&tPar, sizeof(CmTptParam));
   
#ifndef HI_NO_CHK_RES
   switch(hiAccCb.curTst.state)
   {

/* If Kernel SCTP is enabled then start the test case with general configuration */
#ifdef HI_LKSCTP
#else /* HI_LKSCTP */
      /* If Kernel SCTP is not enabled then start the test case with server 
		 * open request */
      case 0:
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);

         /* Init the test case */
         hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;
#endif /* HI_LKSCTP */
         /* Initialize the server's listening address */
         hiAccCb.curTst.remAddr.type = CM_TPTADDR_IPV4;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.address =  HI_ACC_SERV_ADDR;
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_45;

         hiAccCb.curTst.tPar.type = CM_TPTPARAM_SOCK;
   	   hiAccCb.curTst.tPar.u.sockParam.numOpts = 3;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].option = 
                                            CM_SOCKOPT_OPT_REUSEADDR;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].level  = 
                                            CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[0].optVal.value = 
                                            CM_SOCKOPT_ENABLE;

         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].level =
                                             CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].option =
                                             CM_SOCKOPT_OPT_TX_BUF_SIZE;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[1].optVal.value = 50000;

         hiAccCb.curTst.tPar.u.sockParam.sockOpts[2].level =
                                             CM_SOCKOPT_LEVEL_SOCKET;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[2].option =
                                             CM_SOCKOPT_OPT_RX_BUF_SIZE;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[2].optVal.value = 50000;

#ifdef SS_LINUX
#ifdef LOCAL_INTF         
         /* this is to test the getting of intf addr for UDP IPv4 socket */ 
         hiAccCb.curTst.tPar.u.sockParam.numOpts++;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[3].option =
                                             CM_SOCKOPT_OPT_IPV4_PKTINFO;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[3].level  =
                                              CM_SOCKOPT_LEVEL_IP;
         hiAccCb.curTst.tPar.u.sockParam.sockOpts[3].optVal.value =
                                              CM_SOCKOPT_ENABLE;
#endif         
#endif /* SS_LINUX */

         for(i = 0; i < HIACC_UDP_MAX_SERV; i++)
         {
            HITST_ZERO(&nullFilter, sizeof(CmIcmpFilter));
            nullFilter.type = CM_ICMP_NO_FILTER;
            HcLiHitServOpenReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                                i, &hiAccCb.curTst.remAddr, 
                               &hiAccCb.curTst.tPar, &nullFilter, 
                               HI_SRVC_UDP);
            hiAccCb.curTst.remAddr.u.ipv4TptAddr.port += 1;
         }

         hiAccCb.curTst.state = 3;
         break;

      case 3:
         break;

      case 4:
         cnt++;
         if (cnt <  HIACC_UDP_MAX_SERV)
         {
            hiAccCb.curTst.state--;
         }
         else
         {
            hiAccCb.curTst.state++;
            cnt =0;
         }
         break;

      case 5:

         /* Send data in a loop to create the conjestion */
				if ((hiAccCb.conjestionStatus == NO_CONJESTION) || 
													(hiAccCb.conjestionStatus == CONJESTION_START))
				{

				  if (hiAccCb.conjestionStatus == CONJESTION_START)
				  {
				   HIACCPRINT((hiAccCb.prntBuf,
					                          "conjestion started\n"))
				  }
              msg =  hiAccCb.tstMsgs[0].msg;
              if(SAddMsgRef(msg, hiAccCb.init.region, 
                            hiAccCb.init.pool, &msg1) != ROK)
              {
                 HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst45: mem error!\n"))
                 HI_ACC_TST_FAILED();
              }
              HITST_ZERO(&nullAddr, sizeof(CmTptAddr));
              nullAddr.type = CM_TPTADDR_NOTPRSNT;

              HITST_ZERO(&nullHdr, sizeof(CmIpHdrParm));
              nullHdr.type = CM_HDRPARM_NOTPRSNT;
              tPar.type = CM_TPTPARAM_NOTPRSNT;
				  if( (cnt % 2) == 0 )
				  {
                  hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                               HI_ACC_SERV_PORT + HI_TSTID_45;
                  HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0, hiAccCb.curTst.cltSpConId, 
                                 &hiAccCb.curTst.remAddr, &nullAddr, 
                                 &nullHdr, &tPar, msg1);
						cnt = 1;
				  }
				  else 
				  {
                  hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                               HI_ACC_SERV_PORT + HI_TSTID_45 + 1;
				  	   HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0, hiAccCb.curTst.servSpConId,
					                 &hiAccCb.curTst.remAddr, &nullAddr,
					                 &nullHdr, &tPar, msg1);
						cnt = 0;
			     }

				}
				else 
				{
					 HIACCPRINT((hiAccCb.prntBuf,
					                     "conjestion is extrem drop the packets\n"))
					 hiAccCb.curTst.state = 6;
				}
         break;

      case 6:
		   if ( hiAccCb.conjestionStatus == CONJESTION_DROP )
			{
			    SPutMsg ( (hiAccCb.conjBuffer) );
				 hiAccCb.conjBuffer = NULLP;
				 hiAccCb.curTst.state++;
			}
         break;

      case 7:
		   if (hiAccCb.conjestionStatus == NO_CONJESTION ) 
			{
           /*SGetMsg( hiAccCb.init.region, hiAccCb.init.pool, &(hiAccCb.conjBuffer) );*/
	        for (i = 0; i < HIACC_UDP_MAX_SERV; i++) 
	        {
              msg =  hiAccCb.tstMsgs[0].msg;
              if(SAddMsgRef(msg, hiAccCb.init.region, 
                            hiAccCb.init.pool, &msg1) != ROK)
              {
                 HIACCPRNERR((hiAccCb.prntBuf, "hiAccTst45: mem error!\n"))
                 HI_ACC_TST_FAILED();
              }
              HITST_ZERO(&nullAddr, sizeof(CmTptAddr));
              nullAddr.type = CM_TPTADDR_NOTPRSNT;

              HITST_ZERO(&nullHdr, sizeof(CmIpHdrParm));
              nullHdr.type = CM_HDRPARM_NOTPRSNT;
              tPar.type = CM_TPTPARAM_NOTPRSNT;

			     if (i == 0)
			     { 
                   hiAccCb.curTst.remAddr.u.ipv4TptAddr.port =
                                           HI_ACC_SERV_PORT + HI_TSTID_45;

                   HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0, hiAccCb.curTst.cltSpConId,
	                           &hiAccCb.curTst.remAddr, &nullAddr,
	                           &nullHdr, &tPar, msg1);
              }
      	     else 
		        {          
			        hiAccCb.curTst.remAddr.u.ipv4TptAddr.port =
					                             HI_ACC_SERV_PORT + HI_TSTID_45 + 1;
														
				     HcLiHitUDatReq(&hiAccCb.uiPst, HI_ACC_SAP_0, hiAccCb.curTst.servSpConId,                                                                    &hiAccCb.curTst.remAddr, &nullAddr,                                                                                          &nullHdr, &tPar, msg1);
				   }		
    			}
				hiAccCb.curTst.state++;
			}
			
         break;
			
		case 8:
			   hiAccCb.curTst.state++;
			break;

		case 9:
			   hiAccCb.curTst.state++;
			break;

      case 10:
		    if ((hiAccCb.conjBuffer) != NULLP )
			       SPutMsg ( (hiAccCb.conjBuffer) );
		
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_45;
         /* Disconnect all the servers */
         for(i=0; i<HIACC_UDP_MAX_SERV; i++)
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                        "hiAccTst45:Disconnecting UDP servers\n"))
            hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
            HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                           HI_USER_CON_ID, i, HI_CLOSE, &hiAccCb.curTst.tPar);
            hiAccCb.curTst.remAddr.u.ipv4TptAddr.port += 1;
         }
         hiAccCb.curTst.state++;
         break;

      case 11:
         break;

      case 12:
         break;

       case 13:
         hiAccCb.curTst.state = HI_ACC_ST_END;
			hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */
         hiAccCb.curTst.remAddr.u.ipv4TptAddr.port = 
                                         HI_ACC_SERV_PORT + HI_TSTID_45;
         for(i=0; i<HIACC_UDP_MAX_SERV; i++)
         {
            HIACCPRINT((hiAccCb.prntBuf, 
                        "hiAccTst21:Disconnecting UDP servers\n"))
            hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
            HcLiHitDiscReq(&hiAccCb.uiPst, HI_ACC_SAP_0, 
                           HI_USER_CON_ID, i, HI_CLOSE, &hiAccCb.curTst.tPar);
            hiAccCb.curTst.remAddr.u.ipv4TptAddr.port += 1;
         }
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;

   }/* end switch */
#else 
	/* hi025.201 Check Resource is gaurded under HI_NO_CHK_RES flag */
   HIACCPRINT((hiAccCb.prntBuf, 
                 "hiAccTst45:Enable HI_NO_CHK_RES FLAG \n"))
   hiAccCb.curTst.state = HI_ACC_ST_END;
	hiAccCb.curTst.result = HI_TST_OK;
#endif /* HI_NO_CHK_RES */

   RETVALUE(ROK);  
}/* end of hiAccTst45 */
#endif /*HI_CONG_CHECK_TMR*/

/* hi012.201: test case 46 and 47 Outstream handling testcases */

/* hi023.201: test case 48 to test trace indication for KSCTP */

/*hi028.201: Added new test case hiAccTst57 and protected under
 *  HI_ACC_GEN_RECONFIG flag*/
#ifdef HI_ACC_GEN_RECONFIG
/*
*
*       Fun:   hiAccTst57
*
*       Desc:  This test case ensures that TUCL layer support reconfiguration of
*              lmPst during General Configuration.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_acc2.c
*
*/

#ifdef ANSI
PUBLIC S16 hiAccTst57
(
 Void
 )
#else
PUBLIC S16 hiAccTst57()
#endif
{
   HiMngmt    cntrl;
   S32        spId;

      spId = HI_ACC_SAP_1;

   TRC2(hiAccTst57)

      /* clear the config structure first */
      HI_ZERO((U8 *)&cntrl, sizeof(HiMngmt));

   switch(hiAccCb.curTst.state)
   {
      case 0:
         sleep(2);
         /* Display the Information about the test case */
         hiDispTstInfo(hiAccCb.curTst.id);
         HIACCPRINT((hiAccCb.prntBuf, "\tPurpose: TUCL : reconfiguration of lmPst in general configuration \n"))
            /* Init the test case */
            hiAccCb.curTst.msgIdx = 0;
         hiAccCb.curTst.errFlag = FALSE;


#ifdef SS_MULTIPLE_PROCS
         if ( SDetachTTsk( HI_ACC_PROC_ID0, ENTSM, TSTINST ) != ROK )
#else
            if ( SDetachTTsk( ENTSM, TSTINST ) != ROK)
#endif
            {
               HCLOGERROR(ERRCLS_DEBUG, EHC013, (ErrVal)0, "hiAccTst57: SDeatach failed");
            }
#ifdef SS_MULTIPLE_PROCS
         if ( SDeregTTsk ( HI_ACC_PROC_ID0, ENTSM, TSTINST ) != ROK)
#else
            if ( SDeregTTsk ( ENTSM, TSTINST ) != ROK)
#endif
            {
               HCLOGERROR(ERRCLS_DEBUG, EHC013, (ErrVal)0, "hiAccTst57: SDeatach failed");
            }
#ifdef MSVER2
         if(SRegInit((Ent)ENTSM,(Inst) 1, smActvInit) != ROK)
         {
            HCLOGERROR(ERRCLS_DEBUG, EHC006, (ErrVal)0, "hiAccTst57: SRegInit failed");
         }
         if(SRegActvTsk(ENTSM, 1, TTNORM, PRIOR0, smActvTsk) != ROK)
         {
            HCLOGERROR(ERRCLS_DEBUG, EHC007, (ErrVal)0, "hiAccTst57: SRegActvTsk failed");
         }
#else /*MSVER2*/
#ifdef SS_MULTIPLE_PROCS
         if( (SRegTTsk (HI_ACC_PROC_ID0, ENTSM, 1, TTNORM, PRIOR0,(PAIFS16)smActvInit, smActvTsk))!= ROK )
#else
            if ( (SRegTTsk (ENTSM, 1, TTNORM, PRIOR0, smActvInit, smActvTsk))!= ROK )
#endif
            {
               HCLOGERROR(ERRCLS_DEBUG, EHC013, (ErrVal)0, "hiAccTst57: SRegTTsk failed");
            }
#ifdef SS_MULTIPLE_PROCS
         if ( SAttachTTsk (HI_ACC_PROC_ID0, ENTSM, 1, (sysTskId))!= ROK )
#else
            if ( SAttachTTsk (ENTSM, 1, (sysTskId)) != ROK )
#endif
            {
               SDestroySTsk((sysTskId));
               HCLOGERROR(ERRCLS_DEBUG, EHC020, (ErrVal)0, "hiAccTst57: SAttachTTsk failed");
               RETVALUE(RFAILED);
            }
#endif /*MSVER2*/
         /* configure new layer manager */
         HIACCPRINT((hiAccCb.prntBuf, "\t====> Send general configuration with new lmPst \n"))
            hiAccGenCfg_1(ENTHI, TSTINST, 1);
         hiAccCb.cfgDone = TRUE;
         hiAccCb.curTst.state ++;
         break;

      case 1:
         /* shutdown the TUCL layer */
         hiAccCntrlReq(spId, STGEN, ASHUTDOWN, 0, 0);

         HIACCPRINT((hiAccCb.prntBuf, "Layer shutdown request sent\n"))

            hiAccCb.curTst.state++;
         break;

      case 2:
         /* waiting for layer shutdown */
         break;

      case 3:
         hiAccCb.curTst.state = HI_ACC_ST_END;
         hiAccCb.curTst.result = HI_TST_OK;
         break;

      default:
         /* Should not come here  - ERROR case */
         /* Disconnect all the servers */
         HIACCPRINT((hiAccCb.prntBuf, "\thiAccTst57: Error state has been reached!!! \n"))
            hiAccCb.curTst.tPar.type = CM_TPTPARAM_NOTPRSNT;
         hiAccCb.curTst.state = HI_ACC_ST_END;
         break;
   }
   RETVALUE(ROK);
}
#endif


/********************************************************************30*
         End of file:     tl_acc2.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:54 2015

*********************************************************************31*/
 
/********************************************************************40**
 
        Notes:
 
*********************************************************************41*/
 
/********************************************************************50**
 
*********************************************************************51*/
 
/********************************************************************60**
 
        Revision history:
 
*********************************************************************61*/
/********************************************************************70**
  
  version    initials                   description
-----------  ---------  ------------------------------------------------
 
*********************************************************************71*/
 
/********************************************************************80**
 
*********************************************************************81*/
/********************************************************************90**
 
    ver       pat     init                  description
----------- --------- ---- ----------------------------------------------
1.1         ---       asa  1. initial release.
1.1+        hi002.11  asa  1. changes for loopback mode.
                           2. added spConId to HitDatReq primitive.
                           3. modified hiAccTst3() to test HitConReq
                              procedure for UDP clients.
/main/2     ---       cvp  1. removed HitConReq from hiAccTst3()
                           2. added HI_ACC_MCAST_ENB flag to enable
                              multicast test case.
                           3. set max listen queue size for windows NT 
                              to 1.
                           4. miscallaneoous bug fixes.
                           5. changed the copyright header.
/main/4     ---       sb   1. testcase added for Raw socket hiAccTst7(). 
                           2. flag added for backward compatibility.
                      cvp  3. Added hiAccTst6().
                           4. Included sht header files.
/main/4     ---       cvp  1. Added IPV6 testcases.
                           2. Changed the copyright header.
/main/4+    hi009.104 mmh  1. changed calling of cmInetSendMsg & cmInetRecvMsg
                              with new arguments.                        
                           2. init tPar to all 0's in test case3
                           3. added test case 8 to test IPv4 Router Alert 
                              IP_OPTIONS.
                           4. added test cases 12 & 13 to test IPv6 extension
                              headers and related socket options.
                           5. renumbering IPv6 test cases 8, 9 & 10 to 9, 10
                              and 11 respectively.
                           6. added the line hiAccCb.curTst.result = 
                              HI_TST_OK in hiAccTst0()
                           7. remove semicolon from end of all MACRO call
                           8. init all local structures to all zeros.
                           9. Added Roling Upgrade related changes
                              - added new test cases 14 and higher under 
                                HI_RUG flag
                              - declare global variable checkMsg
/main/4+    hi012.104 bdu  1. Take care of the coupling when issuing StaReq
/main/5      ---       kp   1. Updated for release 1.5.
/main/5+    hi001.105 sg    1. Resolved issues related to IPV6 Support
/main/5+    hi002.105 ss   1. Added testcase for Sap deletion
/main/5+    hi014.105 svp  1. Modified statistics req to include messages
                              Tx/Rx in bytes per con per thread 
/main/6      ---       hs   1. Updated for release of 2.1
/main/6+     hi002.201  cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                               Max retransmissions (Init, Path, Association)
/main/6+    hi005.201  rss  1. hiAccTst45 Test case is added to check the conjestion timer changes.
/main/6+    hi010.201  rss  1. Removing ipv6 compilation error in windows
/main/6+    hi012.201  rcs 1. Test case 46 and 47 for handling outstream socket option 
                               in AssocReq.
/main/6+    hi023.201  rcs 1. Test case 48 added for testing trace
                              indication for KSCTP.
/main/6+    hi025.201  rss  1. ccpu00107195  changes
/main/6+    hi026.201  rss  1. Fxed the Test case5
/main/6+    hi028.201 ragrawal 1. Added new test case hiAccTst55, hiAccTst56 
                                  and hiAccTst57.
                               2. Included ss_task.h file.
                               3. Modified test case hiAccTst0 and hiAccTst2 
                                  and hiAccTst35.
                               4. Fix for compilation warning.
/main/6+   hi029.201  ragrawal 1. Fix for 64 bit compilation warnings.
*********************************************************************91*/
