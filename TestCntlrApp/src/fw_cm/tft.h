/**
 ** Copyright (c) Facebook, Inc. and its affiliates.
 ** All rights reserved.
 **
 ** This source code is licensed under the BSD-style license found in the
 ** LICENSE file in the root directory of this source tree.
 **/
#define CM_MAX_PKT_FILTERS 10

#define IPV4_REM_ADDR_PKT_FLTR_MASK 0x0001  /* IPv4 remote address type*/
#define PROTO_ID_PKT_FLTR_MASK 0x0002       /* Protocol id/Nxt header  */
#define SNGL_LOC_PORT_PKT_FLTR_MASK 0x0004  /* Single local port type  */
#define LOC_PORT_RNG_PKT_FLTR_MASK 0x0008   /* Local port range type   */
#define SNGL_REM_PORT_PKT_FLTR_MASK 0x0010  /* Single remote port type */
#define REM_PORT_RNG_PKT_FLTR_MASK 0x0020   /* Remote port range type  */
#define SECURITY_PARAM_PKT_FLTR_MASK 0x0040 /* Security parameter index*/
#define SERV_N_CLASS_PKT_FLTR_MASK 0x0080   /* Type of service/Traffic */
#define IPV6_REM_ADDR_PKT_FLTR_MASK 0x0100  /* IPv6 remote address type*/
