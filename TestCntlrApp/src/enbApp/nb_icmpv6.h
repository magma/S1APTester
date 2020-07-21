/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************


    Name:  LTE S1SIM - ENODEB Application Module

    Type:  C include file

    Desc:  C source code for ICMPV6

    File:  icmpv6.h

    Sid:

    Prg:

**********************************************************************/
#ifndef __ICMPV6H__
#define __ICMPV6H__

// RFC 4861
#define ICMPV6_TYPE_ROUTER_SOL 133
#define ICMPV6_TYPE_ROUTER_ADV 134
#define ROUTER_SOL_MSG_SIZE 8 // In bytes
#define ROUTER_MCAST_ADDR "ff02::2"
#define HOP_LIMIT 255

typedef struct _routerSolicit {
  uint8_t type;
  uint8_t code;
  uint16_t checksum;
  uint32_t reserved;
 } Icmpv6RouterSolicit;

#endif
