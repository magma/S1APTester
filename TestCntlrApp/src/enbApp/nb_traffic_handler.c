/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <ifaddrs.h>

#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_lnb.h"
#include "nbt.h"
#include "nb_log.h"
#include "czt.h"
#include "czt.x"
#include "egt.h"
#include "egt.x"
#include "cm_lte.x"
#include "nbt.x"
#include "nb_dam.h"
#include "nb_traffic_handler.x"

#define NB_APP_PCAP_BUF_SIZE 65536
#define NB_APP_PCAP_TIMEOUT 10
#define NB_APP_ETH_TYPE_IP 0x0008
#define NB_APP_ETH_TYPE_IP6 0xDD86
#define NB_APP_ETH_TYPE_ARP 0x0608
#define NB_APP_MAX_ETH_PKT_LEN 1600
#define NB_APP_MAC_ADDR_LEN 6
#define NB_APP_MAX_IP_PKT 5000
#define NB_APP_MAX_IP_ADDR_LEN 4
#define NB_APP_DATA_SRVR_ADDR 0xAC1A0AB1
#define NB_APP_DATA_SRVR_PORT 0x2710
#define NB_APP_ARP_REQ 0x0100
#define NB_APP_ARP_RSP 0x0200
#define NB_APP_MAX_ARP_PKT_LEN 60
#define NB_MAX_UE_SUPPORT_FOR_DATA 250 /* MULTI_ENB_SUPPORT */

S8 ueIntf[10];

#define NBAPP_ALLOC(_buf, _size)                                        \
{                                                                       \
   if(SGetSBuf(0, 0, (Data **) _buf, (Size) _size) == ROK)             \
   {                                                                    \
      cmMemset((U8 *)(*_buf), 0, _size);                                \
   }                                                                    \
   else                                                                 \
   {                                                                    \
      (*_buf) = NULLP;                                                  \
   }                                                                    \
}

#define NBAPP_FREE(_buf, _size)                                         \
{                                                                       \
   (Void)SPutSBuf(0, 0, (Data *)_buf, (Size)_size);                     \
   (_buf) = NULLP;                                                      \
}

typedef struct nbAppDataRoutCb {
  U32 ipAddr;
  U8 ipAddrStr[NB_APP_MAX_IP_ADDR_LEN];
  U8 ip6AddrStr[NB_IPV6_ADDRESS_LEN];
  U8 macAddr[NB_APP_MAC_ADDR_LEN];
} NbAppDataRouteCb;

typedef struct _ueDataCb
{
   U32 ueId;
   NbAppDataRouteCb   *ipInfo[11];
   U8 noOfIpsAssigned;
}UeDataCb;

PRIVATE U16 ueCnt = 0;
PRIVATE UeDataCb *ueDataCbLst[NB_MAX_UE_SUPPORT_FOR_DATA] = {NULLP};

U8 ethPkt[NB_APP_MAX_ETH_PKT_LEN];
pcap_t *dataHdlr = NULLP;
S8 ethInf[20] = {0};
U8 arpPkt[NB_APP_MAX_ARP_PKT_LEN] = {0};
U32 nbAppIpAddr;
U8 nbAppIpAddrStr[NB_APP_MAX_IP_ADDR_LEN];
U8 lclMACAddr[NB_APP_MAC_ADDR_LEN];
S16 sockFd = 0;

PRIVATE S16 nbAppInitAdaptor
(
 U8 version 
)
{
   S8 errBuf[PCAP_ERRBUF_SIZE];

   /* Open the Ethernet Adaptor with LibPCAP  */
   dataHdlr = pcap_open_live(ethInf, NB_APP_PCAP_BUF_SIZE,
         TRUE, NB_APP_PCAP_TIMEOUT, errBuf);
   if(NULLP == dataHdlr)
   {
      NB_LOG_ERROR(&nbCb,"nbAppInitAdaptor: Error opening network adaptor");
      RETVALUE(RFAILED);
   }
   NB_LOG_DEBUG(&nbCb,"nbAppInitAdaptor: Initialized the Eth interface for capturing "\
         "packets");
   
   /*sockFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);*/
   //sockFd = socket(AF_INET6, SOCK_RAW, IPPROTO_RAW);
   //sockFd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
   printf("In nbAppInitAdaptor version=%d\n",version);
   sockFd = (version == 4) ? (socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) : (version == 6) ? (socket(AF_INET6, SOCK_RAW, IPPROTO_RAW)): -1;
   if(sockFd == -1)
   {
      printf("Failed to open socket\n");
      NB_LOG_ERROR(&nbCb,"Failed to open socket");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* nbAppInitAdaptor */

PRIVATE Void nbAppSendEthPkt
(
 U8 *ethPktSnd,
 U32 len
)
{
   S8 ipAddr[7];
   U16 uePort = 0;
   U16 ipPktLen = 0;
   struct sockaddr_in ueConn;

   cmMemset((U8 *)&ueConn, 0, sizeof(ueConn));
   ipAddr[0] = ethPkt[30];
   ipAddr[2] = ethPkt[31];
   ipAddr[4] = ethPkt[32];
   ipAddr[6] = ethPkt[33];

   ipAddr[1] = '.';
   ipAddr[3] = '.';
   ipAddr[5] = '.';

   uePort = (ethPkt[14 + ipPktLen + 2] << 8) + \
            ethPkt[14 + ipPktLen + 3];
   ueConn.sin_family = AF_INET;
   ueConn.sin_port = htons(uePort);

   inet_aton(ipAddr, &ueConn.sin_addr);
   if(sendto(sockFd, &ethPkt[14], len - 14, 0,
            (struct sockaddr *)&ueConn, sizeof(ueConn)) == -1)
   {
      perror("Failed to send socket nbAppSendEthPkt\n");
   }

   RETVOID;
}/* nbAppSendEthPkt */

PRIVATE Void nbAppSendEthPktIpv6
(
 U8 *ethPktSnd,
 U32 len
)
{
   S8 srcIp6Addr[16] = {0};
   S8 dstIp6Addr[16] = {0};
   char ip6Addr[100] = {0};
   U16 uePort = 0;
   U16 ipPktLen = 0;
   struct sockaddr_in6 ueConn;
   struct in6_addr temp_ipv6_addr;

   cmMemset((U8 *)&ueConn, 0, sizeof(ueConn));
   cmMemset((U8 *)&temp_ipv6_addr, 0, sizeof(struct in6_addr));
   cmMemcpy(srcIp6Addr, &ethPkt[22], 16);
   cmMemcpy(dstIp6Addr, &ethPkt[38], 16);

   sprintf(ip6Addr, "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
            (int)ethPkt[38], (int)ethPkt[39], (int)ethPkt[40], (int)ethPkt[41], (int)ethPkt[42], (int)ethPkt[43],
            (int)ethPkt[44], (int)ethPkt[45], (int)ethPkt[46], (int)ethPkt[47], (int)ethPkt[48], (int)ethPkt[49],
            (int)ethPkt[50], (int)ethPkt[51], (int)ethPkt[52], (int)ethPkt[53]);

   ueConn.sin6_family = AF_INET6;
   /* When using an IPv6 raw socket, sin6_port must be set to 0
    * to avoid an EINVAL ("Invalid Argument") error
    */
   //ueConn.sin6_port = htons(0);
   ueConn.sin6_port = 0;

   if(inet_pton(AF_INET6, ip6Addr, &ueConn.sin6_addr) != 1) {
     perror("inet_pton");
   }
   if(sendto(sockFd, &ethPkt[14], (len-14), 0,
            (const struct sockaddr *)&ueConn, sizeof(struct sockaddr_in6)) == -1)
   {
      perror("sendto\n");
   }
   RETVOID;
}/* nbAppSendEthPktIpv6 */

PRIVATE Void nbAppDlvrIpPkt
(
 const u_char *pktData,
 U32 bytesRcvd
)
{
   Buffer *mBuf = NULLP;
   Pst pst;

   TRC2(nbAppDlvrIpPkt)

   SGetMsg(DFLT_REGION, DFLT_POOL, &mBuf);
   if(mBuf == NULLP)
   {
      RETVOID;
   }

   if(SAddPstMsgMult((Data *)pktData + 14, bytesRcvd - 14, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      RETVOID;
   }

   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
   pst.dstEnt = ENTEU;
   pst.srcEnt = ENTEU;
   pst.srcInst = 0;
   pst.dstInst = 0;
   pst.route = RTESPEC;
   pst.prior = PRIOR0;
   pst.region = DFLT_REGION;
   pst.pool = DFLT_POOL;
   pst.event = EVTEUDATIND;
   
   SPstTsk(&pst, mBuf);

   RETVOID;
}/* nbAppDlvrIpPkt */

PRIVATE Void nbAppSendArpRspPkt
(
 CONSTANT U8  *arpReqPkt,
 U32          len
)
{
   U8 arpRspPkt[NB_APP_MAX_ETH_PKT_LEN]; /* ARP Response packet */

   U16 ethType = NB_APP_ETH_TYPE_ARP;
   U16 arpType = NB_APP_ARP_RSP;

   U8 idx = 0;

   TRC2(nbAppSendArpRspPkt)

   /* Fill Ethernet header */
   /* Collect sender MAC address from ARP request packet and 
      add it as destination MAC address in the Ethernet header */
   cmMemcpy(arpRspPkt, arpReqPkt + 8, NB_APP_MAC_ADDR_LEN);
   idx += NB_APP_MAC_ADDR_LEN;

   /* Add local MAC address as source MAC address */
   cmMemcpy(arpRspPkt + idx, lclMACAddr, NB_APP_MAC_ADDR_LEN);

   idx += NB_APP_MAC_ADDR_LEN;

   /* Set type of Ethernet packet to ARP packet (0x0806) */
   cmMemcpy(arpRspPkt + idx, (U8 *)&ethType, 2);
   idx += 2;

   /* Construct ARP response packet (Ethernet payload) */
   /* First 6 bytes are same for ARP request and response, hence
      copy from ARP request packet */
   cmMemcpy(arpRspPkt + idx, arpReqPkt, 6);
   idx += 6;

   /* Fill the ARP response code */
   cmMemcpy(arpRspPkt + idx, (U8 *)&arpType, 2);
   idx += 2;

   /* Fill local MAC address as the sender MAC address */
   cmMemcpy(arpRspPkt + idx, lclMACAddr, NB_APP_MAC_ADDR_LEN);
   idx += NB_APP_MAC_ADDR_LEN;

   /* Collect target IP address from ARP request packet and 
      add it as sender IP address */
   /* NOTE: We should not add local IP address as sender IP address because
      we are only responding to an ARP request directed at an IP address
      allocated to the UE */
   cmMemcpy(arpRspPkt + idx, arpReqPkt + 24, NB_APP_MAX_IP_ADDR_LEN);
   idx += NB_APP_MAX_IP_ADDR_LEN;

   /* Collect sender IP address and MAC address from ARP request packet 
      and add them as target IP and MAC addresses */
   cmMemcpy(arpRspPkt + idx, arpReqPkt + 8, 10);
   idx += 10;

   NB_LOG_DEBUG(&nbCb,"nbAppSendArpRspPkt: Sending the ARP Response Packet to %d.%d.%d.%d\n",
      arpRspPkt[38], arpRspPkt[39], arpRspPkt[40], arpRspPkt[41]);
   /* Send out ARP response packet */

   nbAppSendEthPkt(arpRspPkt, idx);

   RETVOID;
}/* nbAppSendArpRspPkt */

PRIVATE Void nbAppHndlARPRequest
(
 CONSTANT U8 *arpPktLcl,
 U32 bytesRcvd
)
{
   TRC2(nbAppHndlARPRequest)

   /* irrespective of the destination address,
    * we should pass the arp request to the PDN 
    * */
   nbAppSendArpRspPkt(arpPktLcl, bytesRcvd);

   RETVOID;
}/* nbAppHndlARPRequest */

PRIVATE Void nbAppHndlARPResponse
(
 CONSTANT U8 *arpPktLcl,
 U32 bytesRcvd
)
{
   U16 idx = 0;
   U16 idx1 = 0;
   U32 dstIPAddr = 0;
   U8 isFound = FALSE; 
   UeDataCb *ueDatCb = NULLP;

   TRC2(nbAppHndlARPResponse)

   NB_LOG_DEBUG(&nbCb,"nbAppHndlARPResponse: Received ARP Response");

   dstIPAddr = (arpPktLcl[14] << 24) + (arpPktLcl[15] << 16) + 
               (arpPktLcl[16] << 8) + arpPktLcl[17];

   /* Add the received sender MAC address and IP address to IP->MAC map. If
      this is the MAC address of gateway then store it in routeCb */
   for(idx = 0; idx < ueCnt; idx++)
   {
      ueDatCb = ueDataCbLst[idx];
      for(idx1 = 0; idx1 < ueDatCb->noOfIpsAssigned; idx1++)
      {
         if(dstIPAddr == (ueDatCb->ipInfo[idx1]->ipAddr))
      {
         NB_LOG_DEBUG(&nbCb,"nbAppHndlARPResponse: Received ARP Response for %d.%d.%d.%d\n",
               arpPktLcl[14],arpPktLcl[15], arpPktLcl[16], arpPktLcl[17]);
            cmMemcpy((U8 *)&(ueDatCb->ipInfo[idx1]->macAddr), arpPktLcl + 8,
               NB_APP_MAC_ADDR_LEN);
           isFound = TRUE;
           break;
         }
         if(isFound == TRUE)
           break;
      }
   }
   NB_LOG_DEBUG(&nbCb,"nbAppHndlARPResponse: Received ARP Response From Invalid Ip "\
         "Address %d.%d.%d.%d\n", arpPktLcl[14], arpPktLcl[15], arpPktLcl[16],
         arpPktLcl[17]);
   RETVOID;
}/* nbAppHndlARPResponse */

PRIVATE Void nbAppRcvdPktHndlr
(
 u_char *args,
 const struct pcap_pkthdr *hdr,
 const u_char *pktData
)
{
   U16 pktType;
   U32 bytesRcvd;

   bytesRcvd = hdr->caplen;

   /* Find out the type of Ethernet packet (bytes 12-13 in Ethernet header),
      handle IP and ARP packets */
   pktType = (pktData[13] << 8) + pktData[12];
   if(pktType == NB_APP_ETH_TYPE_IP || (pktType == NB_APP_ETH_TYPE_IP6))
   {
      /* Handle the IP packet */
      nbAppDlvrIpPkt(pktData, bytesRcvd);
   }
   else if(pktType == NB_APP_ETH_TYPE_ARP)
   {
      if(((U16)pktData[21] << 8 | pktData[20]) == NB_APP_ARP_RSP)
      {
         nbAppHndlARPResponse(pktData + 14, bytesRcvd);
      }
      else
      {
         nbAppHndlARPRequest(pktData + 14, bytesRcvd);
      }
   }
   else
   {
      /*NB_LOG_DEBUG(&nbCb," nbAppRcvdPktHndlr: Unknown packet type received");*/
   }

   RETVOID;
}/* nbAppRcvdPktHndlr */

PUBLIC Void *nbAppPktReceiver
(
 Void *arg
)
{
   /* Read packets from Ethernet interface and invoke nbAppRcvdPktHndlr
      callback function for every packet read */
   NB_LOG_DEBUG(&nbCb,"nbAppPktReceiver: Processing the received  Ethernet Packet");
   pcap_loop(dataHdlr, -1, nbAppRcvdPktHndlr, NULLP);

   RETVALUE(NULLP);
}/* nbAppPktReceiver */

PUBLIC Void nbAppHndlIPPkt
(
 CONSTANT U8 *pkt,
 U32 bytesRcvd
)
{
   RETVOID;
}/* nbAppHndlIPPkt */

PRIVATE S16 nbAppGetNwParam
(
 U32 selfIp
)
{
   struct ifreq       *ifr;
   struct ifconf      ifc;
   S32                sockfd;
   S32                ifclen;
   U8                 found = FALSE;

   struct ifaddrs *ifaddr;
   NB_LOG_DEBUG(&nbCb,"Getting the network parameters");

   if (getifaddrs(&ifaddr) == -1) {
     NB_LOG_ERROR(&nbCb,"getifaddrs failed");
     perror("getifaddrs");
     RETVALUE(RFAILED);
   }

   sockfd= socket( PF_INET, SOCK_DGRAM, 0 );
   if(sockfd < 0 ) {
     NB_LOG_ERROR(&nbCb,"Failed to open a socket");
     perror("socket");
     close(sockfd);
     RETVALUE(RFAILED);
   }

   /* Walk through linked list, maintaining head pointer so we
      can free list later. */

   for (struct ifaddrs *ifa = ifaddr; ifa != NULLP;
      ifa = ifa->ifa_next) {
     if (ifa->ifa_addr == NULLP) {
       continue;
     }
     printf("ifa->ifa_addr=%s, ueIntf=%s, ifa->ifa_name=%s\n",ifa->ifa_addr, ueIntf, ifa->ifa_name);
     if(!strcmp(ifa->ifa_name, ueIntf)) {
       strcpy(ethInf, ifa->ifa_name);
       struct ifreq req;
       strcpy(req.ifr_name, ifa->ifa_name );
       if(ioctl(sockfd, SIOCGIFHWADDR, &req ) != -1 ) {
          uint8_t* mac = (uint8_t*)req.ifr_ifru.ifru_hwaddr.sa_data;
          NB_LOG_DEBUG(&nbCb, "%s:MAC[%02X:%02X:%02X:%02X:%02X:%02X]\n",
                ifa->ifa_name,
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5] );
       }
       cmMemcpy(lclMACAddr, (U8 *)req.ifr_ifru.ifru_hwaddr.sa_data, NB_APP_MAC_ADDR_LEN);
       NB_LOG_DEBUG(&nbCb,"MAC address=%02X:%02X:%02X:%02X:%02X:%02X", lclMACAddr[0], lclMACAddr[1],lclMACAddr[2],lclMACAddr[3],lclMACAddr[4],lclMACAddr[5]);
       found = TRUE;
       break;
     }
   }
#if 0
   /* Open a socket for ioctl */
   if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)) < 0)
   {
      NB_LOG_ERROR(&nbCb,"Failed to open a socket"); 
      perror("socket");
      close(sockfd);
      RETVALUE(RFAILED);
   }

   /* Get the ethernet interface name and address matching the selfIp from
      all configured interfaces */
   for(ifr = ifc.ifc_req;
        (ifr && ((char *)ifr < (char *) ifc.ifc_req + ifc.ifc_len)); ++ifr)
   {

      if(!strcmp(ifr->ifr_name, ueIntf))
      {
         /* Found the interface matching selfIp, get other details */
         strcpy(ethInf, ifr->ifr_name);
         
         /* Get Ethernet (Hardware) Address */
         if(ioctl(sockfd, SIOCGIFHWADDR, ifr))
         {
            NB_LOG_ERROR(&nbCb,"Failed to get Ethernet address"); 
            perror("ioctl SIOCGIFHWADDR");
            NBAPP_FREE(ifc.ifc_req, ifclen);
            close(sockfd);
            RETVALUE(RFAILED);
         }
         cmMemcpy(lclMACAddr, (U8 *)ifr->ifr_addr.sa_data, NB_APP_MAC_ADDR_LEN);
         found = TRUE;
         break;
      }
   }

   NBAPP_FREE(ifc.ifc_req, ifclen);
   close(sockfd);
#endif
   if(FALSE == found)
   {
      NB_LOG_ERROR(&nbCb,"Failed to get network parameters"); 
      RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);
}/* nbAppGetNwParam */

PRIVATE S16 nbAppInitEthPkt(U8 version)
{
   U16 ethType = (version == 4) ? NB_APP_ETH_TYPE_IP : (version == 6) ? NB_APP_ETH_TYPE_IP6 : 0;
   if (ethType == 0) {
     NB_LOG_DEBUG(&nbCb,"nbAppInitEthPkt: Invalid version=%d", version);
     RETVALUE(RFAILED);
   }

   TRC2(nbAppInitEthPkt)

   NB_LOG_DEBUG(&nbCb,"nbAppInitEthPkt: Initializing the Ethernet Packet");

   /* Set the destination MAC address to broadcast address (all 0xff) */
   cmMemset(ethPkt, 0xff, NB_APP_MAC_ADDR_LEN);

   /* Set the source MAC address to local MAC address */
   cmMemcpy(ethPkt + NB_APP_MAC_ADDR_LEN, lclMACAddr, NB_APP_MAC_ADDR_LEN);

   /* Set the type of Ethernet packet to IP packet (0x0800) */
   cmMemcpy(ethPkt + (NB_APP_MAC_ADDR_LEN * 2), (U8 *)&ethType, 2);

   RETVALUE(ROK);
}/* nbAppInitEthPkt */

PRIVATE S16 nbAppInitArpPkt(Void)
{
   U16 ethType = NB_APP_ETH_TYPE_ARP;
   U16 ethProtocolType = NB_APP_ETH_TYPE_IP;
   U16 arpType = NB_APP_ARP_REQ;
   U16 arp_hardware_type_ethernet = 0x0100;
   U8  arp_hardware_size = 0x06;
   U8  arp_protocol_size = 0x04;
   U8 idx;

   TRC2(nbAppInitArpPkt)

   NB_LOG_DEBUG(&nbCb,"nbAppInitArpPkt: Initializing the ARP Packet");

   /* First Fill Ethenet Header */
   /* Set the destination MAC address to broadcast address and 
      set the source MAC address to local MAC address */
   cmMemcpy(arpPkt, ethPkt, NB_APP_MAC_ADDR_LEN * 2);
   idx = NB_APP_MAC_ADDR_LEN * 2;

   /* Set the type of Ethernet packet to ARP (0x0806) */
   cmMemcpy(arpPkt + idx, (U8 *)&ethType, 2);
   idx += 2;

   /* Fill ARP packet (Ethernet payload) */
   /* Set the hardware type to Ethernet (0x0001) */
   cmMemcpy(arpPkt + idx, (U8 *)&arp_hardware_type_ethernet, 2);
   idx += 2;

   /* Set the ethernet protocol type to IP (0x0800) */
   cmMemcpy(arpPkt + idx, (U8 *)&ethProtocolType, 2);
   idx += 2;

   /* Set hardware size to 6 for Ethernet */
   cmMemcpy(arpPkt + idx, &arp_hardware_size, 1);
   idx += 1;

   /* Set protocol size to 4 for IP */
   cmMemcpy(arpPkt + idx, &arp_protocol_size, 1);
   idx += 1;

   /* Set operation to ARP request (0x0001) */
   cmMemcpy(arpPkt + idx, (U8 *)&arpType, 2);
   idx += 2;

   /* Set the Sender Hardware Address to local MAC address */
   cmMemcpy(arpPkt + idx, lclMACAddr, NB_APP_MAC_ADDR_LEN);
   idx += NB_APP_MAC_ADDR_LEN;

   /* Set the Sender Protocol Address to local IP address */
   cmMemcpy(arpPkt + idx, nbAppIpAddrStr, NB_APP_MAX_IP_ADDR_LEN);
   idx += NB_APP_MAX_IP_ADDR_LEN;

   /* Initialise the Target Hardware Address and 
      Target Protocol Adress to 0xff */
   cmMemset(arpPkt + idx, 0xff, NB_APP_MAC_ADDR_LEN + NB_APP_MAX_IP_ADDR_LEN);

   RETVALUE(ROK);
}/* nbAppInitArpPkt */

PRIVATE Void nbAppBuildEthPkt
(
 U8   *ipPkt, 
 U32   len
)
{
   U16 idx = 0;
   U16 idx1 = 0;
   U32 dstIPAddr;
   U8 isFound = FALSE;
   UeDataCb *ueDatCb = NULLP;

   U8 *dstMACAddr = NULLP;

   TRC2(nbAppBuildEthPkt)
   
   /*NB_LOG_DEBUG(&nbCb,"nbAppBuildEthPkt: Encapsulating IP packet in a Eth packet");*/
   /* Copy IP packet into Ethernet payload */
   cmMemcpy(ethPkt + 14, ipPkt, len);

   /* Find out the destination MAC address using destination IP address */
   dstIPAddr = (ethPkt[30] << 24) + (ethPkt[31] << 16) + (ethPkt[32] << 8) + \
               ethPkt[33];
   //printf("dstIPAddr=%s\n", dstIPAddr);

   /* Search the MAC map for destination MAC address */
   for(idx = 0; idx < ueCnt; idx++)
   {
      if(ueDataCbLst[idx] != NULLP)
      {
         ueDatCb = ueDataCbLst[idx];
         for( idx1 = 0 ; idx1 < ueDatCb->noOfIpsAssigned ; idx1++)
      {
            if((ueDatCb->ipInfo[idx1] != NULLP) && (dstIPAddr == ueDatCb->ipInfo[idx1]->ipAddr))
            {
               dstMACAddr = ueDatCb->ipInfo[idx1]->macAddr;
               isFound = TRUE;
               break;
            }
         }
         if(isFound == TRUE)
            break;
      }
   }
   if(dstMACAddr == NULLP)
   {
      NB_LOG_ERROR(&nbCb,"nbAppBuildEthPkt: Could not find MAC address");
      RETVOID;
   }

   /* Copy the destination MAC address */
   cmMemcpy(ethPkt, dstMACAddr, NB_APP_MAC_ADDR_LEN);

   RETVOID;
}/* nbAppBuildEthPkt */


PRIVATE Void nbAppBuildEthPktIPv6
(
 U8   *ipPkt, 
 U32   len
)
{
   U16 idx = 0;
   U16 idx1 = 0;
   U32 dstIPAddr;
   U8 dstIP6Addr[NB_IPV6_ADDRESS_LEN] = {0};
   U8 isFound = FALSE;
   UeDataCb *ueDatCb = NULLP;

   U8 *dstMACAddr = NULLP;

   TRC2(nbAppBuildEthPkt)
   
   /*NB_LOG_DEBUG(&nbCb,"nbAppBuildEthPkt: Encapsulating IP packet in a Eth packet");*/
   /* Copy IP packet into Ethernet payload */
   cmMemcpy(ethPkt + 14, ipPkt, len);

   /* Find out the destination MAC address using destination IP address */
   /*dstIPAddr = (ethPkt[30] << 24) + (ethPkt[31] << 16) + (ethPkt[32] << 8) + \
               ethPkt[33];*/
   cmMemcpy(dstIP6Addr, &ethPkt[38], 16);
   //printf("dstIPAddr=%s\n", dstIPAddr);

   /* Search the MAC map for destination MAC address */
   for(idx = 0; idx < ueCnt; idx++)
   {
      if(ueDataCbLst[idx] != NULLP)
      {
         ueDatCb = ueDataCbLst[idx];
         for( idx1 = 0 ; idx1 < ueDatCb->noOfIpsAssigned ; idx1++)
      {
            if((ueDatCb->ipInfo[idx1] != NULLP) && (!cmMemcmp(dstIP6Addr, ueDatCb->ipInfo[idx1]->ip6AddrStr, 16)/*dstIPAddr == ueDatCb->ipInfo[idx1]->ipAddr*/ ))
            {
               dstMACAddr = ueDatCb->ipInfo[idx1]->macAddr;
               isFound = TRUE;
               break;
            }
         }
         if(isFound == TRUE)
            break;
      }
   }
   if(dstMACAddr == NULLP)
   {
      NB_LOG_ERROR(&nbCb,"nbAppBuildEthPkt: Could not find MAC address");
      RETVOID;
   }

   /* Copy the destination MAC address */
   cmMemcpy(ethPkt, dstMACAddr, NB_APP_MAC_ADDR_LEN);

   RETVOID;
}/* nbAppBuildEthPkt */

PUBLIC U16 nbAppCalcIPChecksum
(
 U8 *ipPkt, 
 U32 ipHdrLen
)
{
   U16 word;
   U16 idx;
   U32 chksum = 0;

   TRC2(nbAppCalcIPChecksum)

   NB_LOG_ERROR(&nbCb,"nbAppCalcIPChecksum: Calculating IP check sum");
   /* Make 16 bit words out of every two adjacent 8 bit octets in
      the packet and add them up */
   for(idx = 0; idx < ipHdrLen; idx += 2)
   {
      word = (((U16)ipPkt[idx] << 8) & 0xFF00) + (ipPkt[idx + 1] & 0xFF);
      chksum += (U32)word;
   }

   /* Take only 16 bits out of the 32 bit checksum */
   while(chksum >> 16)
   {
      chksum = (chksum & 0xFFFF) + (chksum >> 16);
   }

   /* One's complement the result */
   chksum = ~chksum;

   /* Return the 16 bit checksum */
   RETVALUE((U16)chksum);
}/* nbAppCalcIPChecksum */

PRIVATE Void nbAppFragmentIPPkt
(
 U8  *ipPkt, 
 U32  len
)
{
   U8  *ipHdr;
   U32 ipHdrLen;
   U32 bytesSent;
   U8  ipPacket[NB_APP_MAX_IP_PKT];
   U32 bytesRemaining;
   U32 maxIPDatSize;
   U32 fragOffset;
   U32 totLen;
   U32 dataSent;
   U16 ipChksum;

   TRC2(nbAppFragmentIPPkt)

   NB_LOG_ERROR(&nbCb,"nbAppFragmentIPPkt:Fragmenting IP packet of len %d", len);

   /* Initialise variables */
   ipHdr = ipPkt; /* Copy IP header pointer */
   ipHdrLen = (ipPkt[0] & 0xF) * 4;
   bytesSent = ipHdrLen;
   bytesRemaining = len - bytesSent;
   maxIPDatSize = NB_APP_MAX_IP_PKT - ipHdrLen;
   fragOffset = 0;

   /* Loop for fragmenting the IP packets */
   while(bytesRemaining > 0)
   {
      /* Copy the original IP header to IP fragment and modify 
         the header to reflect fragmentation */
      cmMemcpy(ipPacket, ipHdr, ipHdrLen); 

      /* Set more flag in the IP header if this is not the last IP fragment */
      if(bytesRemaining > maxIPDatSize)
      {
         ipPacket[6] |= (0x1 << 5);
      }
      
      /* Set fragment offset */
      ipPacket[6] |= (U8)((fragOffset >> 8) & 0x1F);
      ipPacket[7] = (U8)(fragOffset & 0xFF);

      if(bytesRemaining > maxIPDatSize)
      {
         totLen = NB_APP_MAX_IP_PKT;
      }
      else
      {
         totLen = bytesRemaining + ipHdrLen;
      }

      dataSent = totLen - ipHdrLen;
      if(bytesRemaining > maxIPDatSize)
      {
         U32 bytesToSend;

         /* If there are more fragments, send multiple of 8 octets as data */
         bytesToSend = dataSent % 8;
         dataSent -= bytesToSend;
         totLen -= bytesToSend;
      }

      /* Change total length */
      ipPacket[2] = (U8)((totLen >> 8) & 0xFF);
      ipPacket[3] = (U8)(totLen & 0xFF);

      /* Calculate the IP header checksum */
      ipChksum = nbAppCalcIPChecksum(ipPacket, ipHdrLen);

      /* Copy new IP header checksum */
      ipPacket[10] = (ipChksum >> 8) & 0xFF;
      ipPacket[11] = ipChksum & 0xFF;

      /* Copy the data to IP packet */
      cmMemcpy(ipPacket + ipHdrLen, ipHdr + bytesSent, dataSent);

      /* Encapsulate IP packet in an Ethernet packet */
      nbAppBuildEthPkt(ipPacket, totLen);

      NB_LOG_DEBUG(&nbCb,"nbAppFragmentIPPkt: Sending IP fragment from %d.%d.%d.%d to "\
          "%d.%d.%d.%d\n", ipPkt[12], ipPkt[13], ipPkt[14], ipPkt[15],
          ipPkt[16], ipPkt[17], ipPkt[18], ipPkt[19]);

      /* Send out Ethernet packet */
      nbAppSendEthPkt(ethPkt, (totLen + 14));
      
      /* Update variables */
      bytesSent += dataSent;
      bytesRemaining -= dataSent;
      fragOffset += ((dataSent + 7) / 8);
   }

   RETVOID;
}/* nbAppFragmentIPPkt */

PRIVATE S16 nbAppSendArpReqPkt
(
 U8  *ipAddr
)
{
   TRC2(nbAppSendArpReqPkt)
   NB_LOG_DEBUG(&nbCb,"nbAppSendArpReqPkt: Sending the ARP Request Packet");

   NB_LOG_DEBUG(&nbCb,"nbAppSendArpReqPkt: Sending the ARP Request Packet for "\
         "%d:%d:%d:%d\n", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);

   /* Take the default ARP packet and add the destination IP address */
   cmMemcpy(arpPkt + 38, ipAddr, NB_APP_MAX_IP_ADDR_LEN);
   /* Send out ARP request packet */

   RETVALUE(ROK);
}/* nbAppSendArpReqPkt */

PUBLIC S16 nbAppCfgrPdnAssignedAddr
(
 U32 ueId,
 U32 pdnAsgndAddr
)
{
   S16 ret;
   UeDataCb *ueDatCb = NULLP;
   U8 ipAddr[NB_APP_MAX_IP_ADDR_LEN];
   U32 idx = 0;
   U8 idx1 = 0;
   NbAppDataRouteCb *ipInfo = NULLP;

   for(idx = 0; idx < ueCnt; idx++)
   {
      if((ueDataCbLst[idx] != NULLP) &&(ueDataCbLst[idx]->ueId == ueId))
      {
         ueDatCb = ueDataCbLst[idx];
         for(idx1 = 0; idx1 < ueDatCb->noOfIpsAssigned; idx1++)
         {
            if((ueDatCb->ipInfo[idx1]!= NULLP) && \
                  (ueDatCb->ipInfo[idx1]->ipAddr == pdnAsgndAddr))
            {
               NB_LOG_ERROR(&nbCb,"nbAppCfgrPdnAssignedAddr: PDN Address is already assigned "\
                     "for UeId %d", ueId);
               RETVALUE(RFAILED);
            }
         }
         break;
      }
   }
   if((ueDatCb == NULLP) && (ueCnt < NB_MAX_UE_SUPPORT_FOR_DATA))
   {
      NBAPP_ALLOC(&ueDatCb, sizeof(UeDataCb));
      if(ueDatCb == NULLP)
      {
         NB_LOG_ERROR(&nbCb,"Failed to allocate memory for ueDatCb");
         RETVALUE(RFAILED);
      }
      cmMemset((U8 *)ueDatCb,0, sizeof(UeDataCb));
      ueDatCb->ueId = ueId;
      ueDataCbLst[ueCnt] = ueDatCb;
      ueCnt++;
   }

   NBAPP_ALLOC(&ipInfo,sizeof(NbAppDataRouteCb));
   if(ipInfo == NULLP)
   {
      NB_LOG_ERROR(&nbCb,"Failed to allocate memory for ipInfo");
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)ipInfo,0, sizeof(NbAppDataRouteCb));
   ipInfo->ipAddr = pdnAsgndAddr; 
   for(idx = 0; idx < NB_APP_MAX_IP_ADDR_LEN; idx++)
   {
      ipInfo->ipAddrStr[idx] = (pdnAsgndAddr >> (8 * (3 - idx)));
   }
   if(ueDatCb == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "ueDatCb is empty");
      RETVALUE(RFAILED);
   }
   ueDatCb->ipInfo[ueDatCb->noOfIpsAssigned] = ipInfo;
   ueDatCb->noOfIpsAssigned++;

   NB_LOG_DEBUG(&nbCb,"nbAppCfgrPdnAssignedAddr: Configuring the PDN assigned IP "\
         "Address");

   ipAddr[0] = (U8)((pdnAsgndAddr >> 24) & 0xff);
   ipAddr[1] = (U8)((pdnAsgndAddr >> 16) & 0xff);
   ipAddr[2] = (U8)((pdnAsgndAddr >> 8) & 0xff);
   ipAddr[3] = (U8)((pdnAsgndAddr & 0xff));

   NB_LOG_DEBUG(&nbCb,"nbAppCfgrPdnAssignedAddr: Sending the ARP Request Packet "\
         "for %d:%d:%d:%d\n", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);

#if 0
   if(middleEntry > 0)
   {
      ueDataCbLst[middleEntry] = ueDatCb;
      middleEntry = -1;
   }
   else if(ueCnt < NB_MAX_UE_SUPPORT_FOR_DATA - 1)
   {
      ueDataCbLst[ueCnt++] = ueDatCb;
   }
   else
   {
      printf("Failed to create context in Traffic handler");
      RETVALUE(RFAILED);
   }
#endif
   /* Send the ARP request */
   ret = nbAppSendArpReqPkt(ipAddr);

   RETVALUE(ret);
}/* nbAppCfgrPdnAssignedAddr */

PUBLIC S16 nbAppCfgrPdnAssignedAddrIpv6(U8 ueId, U8 *ipv6Addr) {
  UeDataCb *ueDatCb = NULLP;
  U8 idx = 0;
  U8 idx1 = 0;
  NbAppDataRouteCb *ipInfo = NULLP;

  for (idx = 0; idx < ueCnt; idx++) {
    if ((ueDataCbLst[idx] != NULLP) && (ueDataCbLst[idx]->ueId == ueId)) {
      ueDatCb = ueDataCbLst[idx];
      for (idx1 = 0; idx1 < ueDatCb->noOfIpsAssigned; idx1++) {
        if ((ueDatCb->ipInfo[idx1] != NULLP) &&
            (!cmMemcmp(ueDatCb->ipInfo[idx1]->ip6AddrStr, ipv6Addr,
                       NB_IPV6_ADDRESS_LEN))) {
          NB_LOG_ERROR(
              &nbCb,
              "nbAppCfgrPdnAssignedAddr: IPv6 PDN Address is already assigned "
              "for UeId %d",
              ueId);
          RETVALUE(RFAILED);
        }
      }
      break;
    }
  }
  if ((ueDatCb == NULLP) && (ueCnt < NB_MAX_UE_SUPPORT_FOR_DATA)) {
    NBAPP_ALLOC(&ueDatCb, sizeof(UeDataCb));
    if (ueDatCb == NULLP) {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory for ueDatCb");
      RETVALUE(RFAILED);
    }
    cmMemset((U8 *)ueDatCb, 0, sizeof(UeDataCb));
    ueDatCb->ueId = ueId;
    ueDataCbLst[ueCnt] = ueDatCb;
    ueCnt++;
  }

  NBAPP_ALLOC(&ipInfo, sizeof(NbAppDataRouteCb));
  if (ipInfo == NULLP) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory for ipInfo");
    RETVALUE(RFAILED);
  }
  cmMemset((U8 *)ipInfo, 0, sizeof(NbAppDataRouteCb));
  cmMemcpy(ipInfo->ip6AddrStr, ipv6Addr, NB_IPV6_ADDRESS_LEN);
  if (ueDatCb == NULLP) {
    NB_LOG_ERROR(&nbCb, "ueDatCb is empty");
    RETVALUE(RFAILED);
  }
  ueDatCb->ipInfo[ueDatCb->noOfIpsAssigned] = ipInfo;
  ueDatCb->noOfIpsAssigned++;

  RETVALUE(ROK);
}


PUBLIC Void nbRelCntxtInTrafficHandler
(
 U32 ueId
)
{
   U32 idx = 0;
   U8 idx1;
   UeDataCb *ueDatCb = NULLP;

   for(idx = 0; idx < ueCnt; idx++)
   {
      if((ueDataCbLst[idx] != NULLP)&& (ueDataCbLst[idx]->ueId == ueId))
      {
         ueDatCb = ueDataCbLst[idx];
         for(idx1 = 0 ; idx1 < ueDatCb->noOfIpsAssigned ; idx1 ++)
      {
            NBAPP_FREE(ueDatCb->ipInfo[idx1], sizeof(NbAppDataRouteCb));
         }
         printf("Deleting Ue Context from Traffic Handler\n");
         NBAPP_FREE(ueDatCb, sizeof(UeDataCb));
         ueCnt--;
         while(idx < ueCnt)
         {
            ueDataCbLst[idx] = ueDataCbLst[idx+1]; 
               idx++;
      }
         break;
   }
   }
}

PUBLIC S16 nbAppFrwdIpPkt
(
 U8 *ipPkt,
 U32 len,
 U8 version
)
{
   TRC2(nbAppFrwdIpPkt)

   /*NB_LOG_DEBUG(&nbCb,"nbAppFrwdIpPkt: Forwarding the IP packet to client");*/

   if(len > NB_APP_MAX_ETH_PKT_LEN)
   {
         NB_LOG_ERROR(&nbCb,"nbAppFrwdIpPkt: Failed to send the Packet as it exceeds Max"\
               " Ethernet Packet Size");
      RETVALUE(RFAILED);
   }

   /* Fragment the IP packet if its length is greater than the 
      Maximum data size */
   if(len < NB_APP_MAX_IP_PKT)
   {
      /* Encapsulate the IP packet in an Ethernet packet and
       * send out Ethernet packet
       */
      printf("nbAppFrwdIpPkt version=%d\n", version);
      if (version == 4) {
        nbAppBuildEthPkt(ipPkt, len);
        nbAppSendEthPkt(ethPkt, len + 14);
      } else {
        nbAppBuildEthPktIPv6(ipPkt, len);
        nbAppSendEthPktIpv6(ethPkt, len + 14);
      }

      /*NB_LOG_DEBUG(&nbCb,"nbAppFrwdIpPkt: Received IP packet from eNodeB: SRC from "\
           "%d.%d.%d.%d to %d.%d.%d.%d\n", ipPkt[12], ipPkt[13], ipPkt[14],
           ipPkt[15],ipPkt[16], ipPkt[17], ipPkt[18], ipPkt[19]);*/
   }
   else
   {
      /* Fragment IP packet */
      nbAppFragmentIPPkt(ipPkt, len);
   }

   RETVALUE(ROK);
}/* nbAppFrwdIpPkt */

PUBLIC S16 nbAppRouteInit
(
 U32 selfIp,
 S8 *ethIntf,
 U8 version
)
{
   S16 ret = ROK;
   U16 idx = 0;
   U8 cnt = 0;
#ifdef DEBUGP
   U8 *addr = NULLP;
#endif
   pthread_t pcapTid;

   NB_LOG_DEBUG(&nbCb,"Initializing the Route Parameters");
   nbAppIpAddr = selfIp;
   
   while(ethIntf[cnt])
   {
      ueIntf[cnt] = ethIntf[cnt];
      cnt++;
   }
   ueIntf[cnt] = '\0';

   for(idx = 0; idx < NB_APP_MAX_IP_ADDR_LEN; idx++)
   {
      nbAppIpAddrStr[idx] = nbAppIpAddr >> (8 * (3 - idx));
   }

   /* Initialize IP to MAC Mapping Table */
   /* cmMemset((U8 *)&ip2Mac, 0, sizeof(NbAppDataRouteCb)); */

   /* Get Network Parameters using self assigned IP Address */
   ret = nbAppGetNwParam(nbAppIpAddr);
   if(ROK != ret)
   {
      NB_LOG_ERROR(&nbCb,"Failed to get network parameters"); 
      RETVALUE(RFAILED);
   }
#ifdef DEBUGP
   addr = lclMACAddr;
#endif
   NB_LOG_DEBUG(&nbCb,"Ethernet address: %x:%x:%x:%x:%x:%x\n", addr[0],
      addr[1], addr[2], addr[3], addr[4], addr[5]);

#ifdef DEBUGP
   addr = nbAppIpAddrStr;
#endif
   NB_LOG_DEBUG(&nbCb,"App(Proxy) IP address: %d.%d.%d.%d\n", addr[0],
      addr[1], addr[2], addr[3]);

   /* Initialize Ethernet packet */
   ret = nbAppInitEthPkt(version);
   if(ret != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to initialise Ethernet Packet"); 
      RETVALUE(RFAILED);
   }

   /* Initialize ARP packet */
   ret = nbAppInitArpPkt();
   if(ret != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to initialise ARP Packet");
      RETVALUE(RFAILED);
   }

   /* Open the adaptor for capturing packets - LibPcap */
   ret = nbAppInitAdaptor(version);
   if(ret != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to initialise Adaptor"); 
      RETVALUE(RFAILED);
   }

   /* Create the thread for capturing the packets */
   if(pthread_create(&pcapTid, NULLP, nbAppPktReceiver, NULLP))
   {
      NB_LOG_ERROR(&nbCb,"nbAppPktReceiver thread creation failed"); 
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* nbAppRouteInit */
