
/********************************************************************20**
  
     Name:     TCP UDP Convergence Layer acceptance tests
  
     Type:     C include file
  
     Desc:     Environment dependent defines required for TUCL
               acceptance tests.
  
     File:     hi_accen.h
  
     Sid:      hi_accen.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:55 2015
  
     Prg:      asa
  
*********************************************************************21*/

#ifndef __HIACCENH__
#define __HIACCENH__



/* Specify the IP Address of the machine in hex */
#define  HI_ACC_SERV_ADDR      0x7f000001

/* Any Class D address */
#define  HI_ACC_MCAST_IPV4ADDR 0xe0000129  /* "224.1.1.41" */

/* port number of the server */
#define  HI_ACC_SERV_PORT      12435

#ifdef IPV6_SUPPORTED
/* Specify the IPV6 loopback address */
#define  HI_ACC_SERV_V6ADDR      CM_INET_INADDR6_ANY 

/* All nodes multicast address */
#define  HI_ACC_MCAST_IPV6ADDR   "ff02::1"
#ifdef SS_LINUX
#define  HI_ACC_IPV6_MCAST_LOCINF    1
#else
#define  HI_ACC_IPV6_MCAST_LOCINF    0
#endif /* SS_LINUX */
#endif /* IPV6_SUPPORTED */

#ifdef HI_TLS
#define HI_ACC_TLSCLIENT_REMPORT       12457
#define HI_ACC_TLSCLIENT_CAFILE        "rootcert.pem"
#define HI_ACC_TLSCLIENT_CAPATH        NULL
#define HI_ACC_TLSCLIENT_CERTFILE      "client.pem"
#define HI_ACC_TLSCLIENT_PRIVKEYFILE   "client.pem"
#define HI_ACC_TLSCLIENT_CIPHERS       "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"

#define HI_ACC_TLSSERVER_LOCPORT       12458
#define HI_ACC_TLSSERVER_CAFILE        "rootcert.pem"
#define HI_ACC_TLSSERVER_CAPATH        NULL
#define HI_ACC_TLSSERVER_CERTFILE      "server.pem"
#define HI_ACC_TLSSERVER_PRIVKEYFILE   "server.pem"
#define HI_ACC_TLSSERVER_CIPHERS       "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
#endif /* HI_TLS */

#endif /* __HIACCENH__ */


/********************************************************************30**
 
         End of file:     hi_accen.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:55 2015

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
----------- --------- ---- -----------------------------------------------
1.1         ---       asa  1. initial release.
/main/2     ---       cvp  1. changed the copyright header.
/main/3     ---       cvp  1. Changes for IPV6 support.
                           2. Changed the copyright header.
/main/3+    hi012.104 bdu  1. Define the MCAST6 interface as
                              1 on Linux.
/main/4      ---       kp   1. Updated for release 1.5.
/main/5      ---       hs   1. Updated for release of 2.1
*********************************************************************91*/
