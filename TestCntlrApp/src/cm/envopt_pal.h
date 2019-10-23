
/********************************************************************20**
  
     Name:     environment options
  
     Type:     C include file
  
     Desc:     Environment options specifies defines required by the
               by TRILLIUM software. The defines in this file need to be
               changed by the customer to reflect the software architecture
               needed to run under the target system hardware architecture.
  
     File:     envopt.h
  
     Sid:      envopt.h@@/main/367 - Tue Mar 13 16:57:02 2012
    
     Prg:      na
  
*********************************************************************21*/

#ifndef __ENVOPTH__
#define __ENVOPTH__
  
  
/*
*     this software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000001     Physical Layer - SCC
*     1000002     Data Link Layer - LAPB
*     1000003     Data Link Layer - LAPD
*     1000005     Data Link Layer - LAPB & LAPD
*     1000006     Network Layer - X.25 Intermediate System
*     1000007     Network Layer - X.25 End System
*     1000008     Network Layer - X.75
*     1000009     Network Layer - Q.930/Q.931
*     1000010     Application Layer - Asynchronous PAD
*     1000011     Multiprocessor Operating System (MOS)
*     1000014     Network Layer - X.25 End & Intermediate System
*     1000017     Data Link Layer - Basic Frame Relay
*     1000018     Data Link Layer - Extended Frame Relay
*     1000019     Data Link Layer - Logical Link Control 1
*     1000020     Data Link Layer - Logical Link Control 2
*     1000021     Data Link Layer - Logical Link Control 3
*     1000023     Network Layer - X.31
*     1000024     Signalling System 7
*     1000026     TCP/IP
*     1000027     Signalling System 7 - MTP Level 2
*     1000028     Signalling System 7 - MTP Level 3
*     1000029     Signalling System 7 - ISUP
*     1000030     Signalling System 7 - SCCP
*     1000031     Signalling System 7 - TCAP
*     1000034     Physical Layer - ISAC-S
*     1000035     68302 MOS/SCC
*     1000040     UDP/IP
*     1000041     ESCC
*     1000042     Signalling System 7 - TUP
*     1000043     Network Layer - Q.93B
*     1000044     Data Link Layer - Q.SAAL
*     1000048     UNI Management Entity (UME)
*     1000049     Frame Relay Network (Q.933)
*     1000050     LAN Emulation Client (LEC)
*     1000053     Physical Layer - Fujitsu ALC
*     1000054     Data Link Layer - Q.2140
*     1000064     Broadband ISUP
*     1000066     LAN Emulation Services (LE Services)
*     1000074     V5.X LAPV5-DL 
*     1000075     V5.X PSTN Network Layer 
*     1000094     V5.X Control Protocol 
*     1000095     V5.X Bearer Channel Connection Protocol 
*     1000096     V5.X Protection Protocol 
*     1000098     V5.X Link Control Protocol 
*     1000084     V5.X Envelope Function
*     1000086     FR-ATM Inteworking Layer
*     1000088     Frame Relay Data Link Layer(Q.922)
*     1000096     V5.X Protection Protocol 
*     1000128     X.25/X.75 Packet Level Protocol 
*     1000135     Windows NT -- Multithreaded system services
*     1000139     MPC860SAR driver
*     1000163     MPC8260 driver
*     1000237     LDF-ISUP 
*     1000241     3GPP-MAC
*     1000243     3GPP-NBAP
*     1000348     MAC-HS
*     1000361     S1AP
*
*/

 
/* defines */
/**************************************************************************
   general parameters
**************************************************************************/

/* error checking, choose none or one */

#ifdef NOERRCHK
#else
#define ERRCHK       /* error checking */
#endif /* NOERRCHK */

#undef CM_PASN_DBG

/**************************************************************************
   unix - multi-threaded system services
**************************************************************************/
/* Multi threaded solaris/linux operating system */
#ifdef MT       /* unix - multi-threaded */
#define MT_SOL  /* Solaris Thread Architecture */
#endif

#ifndef SS_MT
#define SS_MT
#endif

/* Flags that apply for the entire product are defined here */
/* The legacy and the system services defintions are here   */
#define USE_LINUX
#define CMINET_BSDCOMPAT
/* #define SS_TICKS_SEC        100 */
#define CMFILE_REORG_1
#define CMFILE_REORG_2
#define CM_INET2
#define SSINT2
#undef HI_MULTI_THREADED 
#define SS_PERF
#define SS_WL_REGION        1
#define SS_FLOAT
#define SS_MT_TMR
#define SS_M_PROTO_REGION
#define SLES9_PLUS
#undef SS_TSKLOG_ENABLE
#define SS_MULTICORE_SUPPORT
#undef  SS_USE_ICC_MEMORY
#define SS_LOCKLESS_MEMORY
#define SS_USE_ZBC_MEMORY
#define SS_THR_REG_MAP
#undef  SS_RBUF
#undef  SS_LICENSE_CHECK
#undef  SS_ROUTE_MSG_CORE1
#undef  SS_DBUF_REFLOCK_DISABLE

#undef  SSI_MEM_CORR_PREVENTION
#undef  MS_MBUF_CORRUPTION

#define TENB_MULT_CELL_SUPPRT

/* LTE product specific definitions are here */
#define TUCL_TTI_RCV
#define LTE_PAL_ENB
#define LTE_ENB_PAL
#define TENB_RTLIN_CHANGES
#define TENB_SPLIT_ARCH_SUPPORT
#define TENB_SPLIT_ARCH
#undef TENB_T2K3K_SPECIFIC_CHANGES
#undef  MLOG_ENABLED
#undef MSPD_DBG_ENABLE
#undef  MSPD_MLOG_NEW
#define TTI_PROC_FIRST
#undef FLAT_BUFFER_OPT
#undef  NTL_LIB
#undef TENB_UL_FP
#define TENB_AS_SECURITY
#undef LTE_L2_MEAS 

#undef LTEPHY_MSPD

#undef DAM_PDCP_OPT

#define REL_850
#define TA_NEW
#undef TENB_FP
#if defined(MODE) && (MODE==TDD)
#define LTE_TDD 1
#define TFU_TDD
#undef MSPD_TDD_LTE
#undef MSPD_TDD
#undef MSPD_TDD_DBG
#define PHY_3828
#define PHY_3829
#define SPLIT_RLC_DL_TASK
#undef RG_SCH_DYNDLDELTA
#else
#undef LTE_TDD
#undef LA_VER3
#undef TFU_TDD
#define T2200_FDD_CPU_OVRLD
#undef  MSPD_PHY_NEW
#define T2200_2GB_DDR_CHANGES
#define BEST_EFFORT_2_UE_PER_TTI
#define KWSELFPSTDLCLEAN
#define BATCH_PROCESSING_DL
#define BATCH_PROCESSING_UL
#define TL_ALLOC_ICC_MEM
#undef YS_MS_UL_ZBC
#endif

#define SS_DRVR_SUPPORT

#if defined(BOARD) && (BOARD==T33H)
#define L2_L3_SPLIT 1
#define SS_DRVR_SUPPORT
#define ICC_RECV_TSK_RBUF
#define YSMS_RLF_DETCT

#if  defined(MODE) && (MODE==TDD)
#else
#define TFU_ALLOC_EVENT_NO_INIT
#define  RLC_NO_HDR_CPY
#endif
#else
#undef PDCP_RLC_DL_RBUF
#undef MAC_RLC_UL_RBUF
#undef NTL_LIB_DIS_FOR_UL
#undef TFU_ALLOC_EVENT_NO_INIT
#if defined(MODE) && (MODE==TDD)
#define KWSELFPSTDLCLEAN
#else
#define YSMS_RLF_DETCT
#define LA_VER2
#endif
#endif


#if defined(CA_ENABLE) && (CA_ENABLE==YES)
#define TENB_MULT_CELL_SUPPRT
#define LTE_ADV
#define CA_PHY  1
#define LTE_ADV_UECAP
#if defined(BOARD) && (BOARD==T33H)
#define UL_RLC_NET_CLUSTER
#define MAC_FREE_RING_BUF
#define RLC_FREE_RING_BUF
#define UL_DL_SPLIT
#endif
#define CA_DBG
#define NTL_LIB_DIS_FOR_UL
#ifndef SPLIT_RLC_DL_TASK
#define SPLIT_RLC_DL_TASK
#endif
#endif

#ifdef SPLIT_RLC_DL_TASK
#define MAC_RLC_HARQ_STA_RBUF
#define RLC_MAC_STA_RSP_UL_RBUF
#endif
#define TENB_STATS


/* Interface flags - The interface flags are shared by more than */
/* one layer and hence need to be defined in a common place.     */

/* KWU interface definition */
#define CCPU_OPT

/* SZT interface (App<->S1AP) flags */
#define SZTV1
#define SZTV2
#define SZTV3

/* CZT interface (App<->X2AP) flags */
#define CZTV1

/* LSZ interface (SM<->S1AP) flags */
#define LSZV1

/* LEG interface (SM<->EGTP) flags */
#define LEGV2

/* CTF interface (App<->CL) flags */
#define CTF_VER3
#undef CTF_V3

/* CPJ interface (RRC<->PDCP) flags */
#define CPJ_V2

/* TFU interface flags */
#ifdef LTE_TDD
#define TFU_TDD
#else
#undef TFU_TDD
#endif

#define TFU_UPGRADE 1
#define TFU_VER_2

/* RGR interface (APP<->SCH) flags */
#define RGR_V1
#define RGR_V2
#define RGR_CQI_REPT
#define RGR_SI_SCH
#define RGR_RRM_TICK

/* RRM related interface flags */
#define RM_INTF

/* LSB interface flags */
#define LSB4
#define LSB8
#define SB_CHECKSUM   /* Define to include trillium supplied function */
#define SB_CHECKSUM_CRC 

/**************************************************************************
   Layer manager interface version definition
**************************************************************************/
#define LMINT3       /* interface 3 */

#ifdef SS       /* Common System Services */
/**************************************************************************
   Common System Services parameters
**************************************************************************/
/* product specific options */
#define SS_RTR_SUPPORT        /* for supporting router tasks */

#ifdef SS_DRVR_SUPPORT
/* for backward compatibility */
#define ENB_RELAY
/* for forward compatibility */
#define RYINT1
#endif /* SS_DRVR_SUPPORT */

/* post format, choose none or one */
#define FCSPOSTINT      /* forward compatibility, post format */

#endif /* SS */

/**************************************************************************
   MTSS-Solaris parameters
**************************************************************************/
#ifdef SS_MT    /* MTSS-Solaris */
#ifndef CONAVL
#define CONAVL          /* console availability option */
#endif
#define STDIO_INCLD
#endif

/******************************************************************/
/*                  SCTP Layer                                    */
/******************************************************************/
#ifdef SB

/* List of other layers interacting with SCTP and in the same binary */
#ifndef SM
#define SM
#endif

#ifndef SZ
#define SZ
#endif

#ifndef CZ
#define CZ
#endif

#ifndef HI
#define HI
#endif

/* Coupling with other layers */
#define LCSBUISCT 
#define LCSBLIHIT
#define LCSBMILSB

/* new TUCL layer */
#ifndef HI_REL_1_4
#define HI_REL_1_4
#endif

#ifdef IPV6_SUPPORTED
#define SB_IPV6_SUPPORTED
#endif

/* Checksum */
/* needed dependencies */
#ifdef LCSBUISCT
#ifndef LCSCT
#define LCSCT 1
#endif
#endif

#ifdef LCSBMILSB
#ifndef LCLSB
#define LCLSB 1
#endif
#endif

#ifdef LCSBLIHIT
#ifndef LCHIT
#define LCHIT 1
#endif
#endif

/*----- SCTP have dependencies in LSB and SCT ------*/
#ifdef LCLSB
#ifndef LCSCT
#define LCSCT
#endif
#endif

/*----- SCTP have dependencies in LSB and SCT ------*/
#ifdef LCSCT
#ifndef LCLSB
#define LCLSB
#endif
#endif

#endif /* SB */

/**************************************************************************
                      S1AP Section
**************************************************************************/
#ifdef SZ
#undef SZ
#define SZ 1

/* Define the layers that coexist with S1AP.                */
#ifndef SB
#define SB
#endif

#ifndef UZ
#define UZ
#endif

#ifndef SM
#define SM
#endif

/* product options */
#define SZ_ENB
#define CM_PASN_CRIT_HANDL
#undef  M_PASN_DBG
#undef S1AP_REL851
#define SZ_DYNAMIC_PEER
#define SZ_USTA

/* interface options */
#define LCSZUISZT     /* loosely coupled, SZ upper layer SZT interface */
#define LCSZMILSZ     /* loosely coupled, SZ manegement  LSZ interface */
#define LCSZLISCT     /* loosely coupled, SZ lower layer SCT interface */

/* Based on the selection of coupling above the section below  */
/* defines enabling/disabling of loose coupling on the         */
/* respective interfaces                                       */
/* ****** THIS SECTION REQUIRES NO FURTHER CHANGES. ********** */
/* Interface between S1AP and Application */
#ifdef LCSZUISZT
#ifndef LCSZT
#define LCSZT    1
#endif
#endif

/* Interface between S1AP and management (SM) */
#ifdef LCSZMILSZ
#ifndef LCLSZ
#define LCLSZ    1
#endif
#endif

/* Interface between S1AP and Application */
#ifdef LWLCSZUISZT
#ifndef LWLCSZT
#define LWLCSZT
#endif
#endif

/* Interface between SCTP and S1AP */
#ifdef LCSZLISCT
#ifndef LCSCT
#define LCSCT
#endif
#endif

#endif          /* SZ */

/******************************************************************/
/* EGTP Layer                                                     */
/******************************************************************/
#ifdef EG

/* Product flags */
#define  EGTP_U    1        /* LTE Evolved GTP User Plane Protocol */


/* All the layers that this layer interacts with and are part of */
/* the binary are to be included here.                           */
#ifndef EU
#define EU
#endif

#ifndef HI
#define HI
#endif

#ifndef SM
#define SM
#endif

#ifdef IPV6_SUPPORTED
#define EG_IPV6_SUPPORTED
#endif

/* EGTP does not use loose coupling towards higher layers and does */
/* not talk to TUCL on HIT in the latest TeNB. However if it were  */
/* to use TUCL, it would be loosely coupled as TUCL is multi-      */
/* threaded.                                                       */
/* TODO - LCEGUIEGT should not be needed.                          */
#define LCSMEGMILEG
#define LCEGLIHIT
#define LCEGUIEGT
#define LCEGMILEG

/* Managing the loose coupling definitions on the interface based   */
/* how the interface is coupled from E-GTP layer.                   */
/* ****** THIS SECTION REQUIRES NO FURTHER CHANGES. ********** */
#if defined(LCEGMILEG)
#ifndef LCLEG
#define LCLEG 1
#endif
#endif

#if defined(LCEGLIHIT)
#ifndef LCHIT
#define LCHIT 1
#endif
#endif

#ifdef LCEGUIEGT
#ifndef LCEGT
#define LCEGT
#endif
#endif
#endif /* EG */

/*************************************************************************/
/*                     LTE-RRC Section                                   */
/*************************************************************************/
#ifdef NH
#undef NH
#define NH 1

/* Define other layers that are part of the same binary */
/* Along with RRC, we have application(NX,WR) and stack */
/* manager (SM).                                        */
#ifndef SM
#define SM
#endif

/* TODO - We need either WR or NX and not necessarily   */
/* both of them. See if we can remove one of it.        */
#ifndef NX
#define NX
#endif

#ifndef WR
#define WR
#endif


/* RRC layer functionality flags */
#define DISABLE_RRCSEC

/* Interface coupling related flags */
/* TODO - LCNHUINHU should not be needed.              */
/* TODO - LCWRLINHU should not be needed.              */
#define LWLCNHUINHU
#define LCNHUINHU 
#define LCNHLICPJ
#define LCNHLIPJU
#define LCNHLICKW
#define LCNHLIKWU
#define LCNHLICTF
#define LCNHMILNH
#define LCWRLINHU 

/* CRG interface between MAC and RRC should be loosely coupled  */
#define LCNHLICRG

/* Loose coupled NHU */
#ifdef LCNHUINHU
#ifndef LCNHU
#define LCNHU 1
#endif
#endif

/* Light weight loose coupled NHU */
#ifdef LWLCNHUINHU
#ifndef LWLCNHU
#define LWLCNHU 1
#endif
#endif

/* Loosely coupled CPJ */
#ifdef LCNHLICPJ
#ifndef LCCPJ
#define LCCPJ 1
#endif
#endif

/* Loosely coupled PJU */
#ifdef LCNHLIPJU
#ifndef LCPJU
#define LCPJU 1
#endif
#endif

/* Loosely coupled CRG */
#ifdef LCNHLICRG
#ifndef LCCRG
#define LCCRG 1   /* loosely coupled CRG interface */
#endif
#endif

/* Loosely coupled CTF */
#ifdef LCNHLICTF
#ifndef LCCTF
#define LCCTF 1   /* loosely coupled CTF interface */
#endif /* LCCTF */
#endif /* LCNHLICTF */

#ifdef LCNHLICKW
#ifndef LCCKW
#define LCCKW 1   /* loosely coupled CKW interface */
#endif
#endif
#define LCNHLIKWU
#ifdef LCNHLIKWU
#ifndef LCKWU
#define LCKWU 1   /* loosely coupled KWU interface */
#endif
#endif

/* TODO These flags should move to SM definitions */
#define LCSMNHMILNH

/* Define flags related to loosely coupled LNH interface */
#ifdef LCNHMILNH
#ifndef LCLNH
#define LCLNH 1
#endif 
#endif

/* Release 9 related flags */
#ifdef LTERRC_REL9
#define S1AP_REL9A6
#ifndef LNH_VER1
#define LNH_VER1
#endif
#ifndef NHU_VER1
#define NHU_VER1
#endif
#endif /* LTERRC_REL9 */

#ifdef RRC_PHY_CFG_SUPP
#define CTF_VER1
#endif 

#define RNC_INTEG_CCPU

#endif /* NH */

/****************************************************************************
                     CL section
****************************************************************************/
#if (defined(TF) || defined(YS))

/* Self entity definitions */
#ifndef TF
#define TF
#endif

#ifndef YS
#define YS
#endif


/* Other entity definitions */
#ifndef RG
#define RG
#endif

/* Selection of interface coupling flags */
#define LCTFUITFU
#define LCTFUICTF
#define LCYSUICTF
#define LCYSUITFU
#define LCYSMILYS

#if defined(MODE) && (MODE == TDD)
#define TFU_TDD
#else
#undef TFU_TDD
#endif

/* The handling of enabling LC based on coupling enabled  */
/* between CL and other layers.                           */
/* ****** THIS SECTION REQUIRES NO FURTHER CHANGES. ********** */
#ifdef LCTFUITFU
#ifndef LCTFU
#define LCTFU
#endif
#endif

#ifdef LCTFUICTF
#ifndef LCCTF
#define LCCTF
#endif
#endif

#ifdef LCYSUICTF
#ifndef LCCTF
#define LCCTF
#endif
#endif

#ifdef LCYSMILYS
#ifndef LCLYS
#define LCLYS
#endif
#endif

#define TFU_WRR_2
#endif  /* YS/TF */

/****************************************************************************
                     LTE-MAC Section
****************************************************************************/
#ifdef RG 
#undef RG 
#define RG 1

/* Product options */
#define RG_PHASE2_SCHED 1
#undef RG_DEBUG
#undef TTI_PROC
#undef PROC_DL
#undef SCH_TTI_PROC
#undef TOM
#undef PAL_MAC_PROC
#undef UL_PROC_MAC
#define LTEMAC_RGU_PAD 1
#define LTEMAC_MIMO 1
#define LTEMAC_DRX 1
#define UL_LA 1
#define DL_LA 1
#define LTEMAC_SPS 1
#define LTEMAC_DLUE_TMGOPTMZ
#define RG_DL_DELTA_CHANGE 
#define RG_CMNCH_SCHDELTA_CHANGE 
#undef RG_ULSCHED_AT_CRC 
#define TFU_RECPREQ_DELTA_CHANGE 
#define TFU_DL_DELTA_CHANGE 
#define TFU_UL_DELTA_CHANGE 
#define TFU_DLHQFBK_DELTA_CHANGE 
#define SCH_STATS

/* Define all the layers that are colocated with the MAC layer  */
/* RRC is located on a different binary on a different CPU. RRC */
/* should not be included here. SM should also not be defined   */
/* as it is also located on a different CPU.                    */
#ifndef UR
#define UR
#endif

#ifndef KW
#define KW
#endif


/* This section selects the coupling for each interface related to  */
/* MAC. The section below enabling the coupling code appropriately. */
/* CCPU_OPT flag enables additional information between MAC and RLC */
/* that aids in better selection of transport block size.           */
/* TODO - We should delete LWLC for RGM interface.                  */
#define LCRGUICRG
#define LCRGUIRGU
#define LWLCRGUIRGU
#define LCRGMILRG
#define LCRGUIRGR
#define LCRGLITFU
#define LCRGUIRGM
#define LWLCRGUIRGM

/* Managing the loose coupling definitions on the interface based   */
/* how the interface is coupled from MAC layer.                     */
/* ****** THIS SECTION REQUIRES NO FURTHER CHANGES. ********** */
#ifdef LCRGUICRG
#ifndef LCCRG
#define LCCRG
#endif
#endif

#ifdef LCRGUIRGU
#ifndef LCRGU
#define LCRGU
#endif
#endif

#ifdef LCRGMILRG
#ifndef LCLRG
#define LCLRG
#endif
#endif

#ifdef LCRGUIRGR
#ifndef LCRGR
#define LCRGR
#endif
#endif

#ifdef LCRGLITFU
#ifndef LCTFU
#define LCTFU
#endif
#endif

#ifdef LCRGUIRGM
#ifndef RGM_LC
#define RGM_LC
#endif
#endif

#ifdef LWLCRGUIRGM
#ifndef RGM_LWLC
#define RGM_LWLC
#endif
#endif
/******************* section to be changed by CUSTOMERS ******************/

#define RG_SC1 1
/* 
 * Introduced timing deltas in FDD for DL control, DL data, 
 * Reception Request, CRC Indication, HARQ feedback Indication.
 */
#ifdef LTEMAC_DLUE_TMGOPTMZ
/* Delta used between MAC and RLC to recieve data from RLC*/
#define RGU_DELTA 0
#else
#define RGU_DELTA 1
#endif

#if defined(DLHQ_RTT_OPT) && defined(LOWLATENCY)
#define TFU_DELTA 2
#else
#define TFU_DELTA 2
#endif
#define TFU_RECPREQ_DLDELTA   2

#ifdef LTE_TDD
#define RG_ENV_DL_DELTA (TFU_DELTA + RGU_DELTA)

#define TFU_DLDATA_DLDELTA  (TFU_DELTA)
#define TFU_CRCIND_ULDELTA   2
#define TFU_ULCNTRL_DELTA  (4 - TFU_CRCIND_ULDELTA)

#ifdef MSPD
/* Number of subframes in advance UL control (DCI-0/PHICH) should be sent from SCH */
#define TFU_ULCNTRL_DLDELTA        2
#else
#define TFU_ULCNTRL_DLDELTA        1
#endif

#ifdef DLHQ_RTT_OPT
/* Number of subframes later DL HARQ feedback reaches MAC from PHY */
#define TFU_ENV_HQFBKIND_ULDELTA  2
#else
#define TFU_ENV_HQFBKIND_ULDELTA  3
#endif

/* Number of subframes in  Advance the Downlink control is 
   given from  MAC to PHY */
#define TFU_DLCNTRL_DLDELTA TFU_DELTA

#else /* LTE_TDD */
/* Number of subframes in advance UL control (DCI/PHICH) should be sent from SCH */
#define TFU_ULCNTRL_DLDELTA  (RG_SCH_CMN_HARQ_INTERVAL - TFU_CRCIND_ULDELTA)

#ifdef LTEPHY_MSPD

/* Number of subframes for UL CRC to reach SCH after reception of data at PHY */
#define TFU_CRCIND_ULDELTA    2

#else /* LTEPHY_MSPD */

/* Number of subframes in advance DL control should be sent from SCH */
#define TFU_DLCNTRL_DLDELTA   2
/* Number of subframes in advance DL data should be sent from MAC */
#define TFU_DLDATA_DLDELTA    2

/* Number of subframes for UL CRC to reach SCH after reception of data at PHY */
#define TFU_CRCIND_ULDELTA    2
/* Number of subframes later DL HARQ feedback reaches SCH from PHY */
#define TFU_ENV_HQFBKIND_ULDELTA  2

#endif /* LTEPHY_MSPD */
/* The number of frames ahead that RLC may require a STA IND */
/* Seperated DL control and DL data timing deltas in FDD     */
#if (TFU_DLDATA_DLDELTA > TFU_DLCNTRL_DLDELTA)
#define RG_ENV_DL_DELTA (TFU_DLDATA_DLDELTA + RGU_DELTA)
#else
#define RG_ENV_DL_DELTA (TFU_DLCNTRL_DLDELTA + RGU_DELTA)
#endif

#endif /* LTE_TDD */

/* Delta between Random Access Response and Msg-3*/
#define RGSCH_RARSP_MSG3_DELTA    6

/* PUSCH data reception delta after the PDCCH for uplink(DCI-0) is sent*/
#define RGSCH_PDCCH_PUSCH_DELTA   4

#ifdef LTEMAC_HDFDD
#define RG_SCH_HDFDD_DELTA   10
#endif
#define RG_ENV_SCH_CMN_DL_DELTA                RG_ENV_DL_DELTA  /* This parameter should not be less than RG_ENV_DL_DELTA */

#define RG_SCH_NO_DELTA 0  /*Consider no delta */
/* ccpu00117459 - ADD - Added check if incompatible falgs are enabled*/
/* HDFDD and TDD cannot be enabled at the same time. */
#if defined(LTEMAC_HDFDD) && (defined(LTE_TDD) || defined(TFU_TDD))
#error "Enabling LTEMAC_HDFDD along with LTE_TDD or TFU_TDD is not a valid combination."
#endif

/* LTE_TDD and TFU_TDD must be enabled for TDD mode */
#if (defined(LTE_TDD) && (!defined(TFU_TDD))) || (defined(TFU_TDD) && (!defined(LTE_TDD)))
#error "Both LTE_TDD and TFU_TDD must be enabled for TDD mode of operation."
#endif
#endif /* RG */

/****************************************************************************
                     LTE-RLC Section
****************************************************************************/
#ifdef KW

/* Only PDCP and MAC are in the same binary. RRC runs on a different */
/* CPU and should not be defined here.                               */
#ifndef RG
#define RG
#endif

#ifndef PJ
#define PJ
#endif

/* -------- LKW Interface ------*/
/* This is the interface between RLC and the stack manager */
/* This should support loosely coupling as they dont run   */
/* in the same thread                                      */
#define LCKWMILKW

/* -------- CKW Interface ------*/
/* CKW interface is loosely coupled as RRC and RLC reside */
/* on two different CPUs running in different threads     */
#define LCKWUICKW

/* -------- KWU Interface ------*/
/* KWU interface exists between RRC/PDCP and RLC. Since RRC is */
/* is loosely coupled with RLC, loosely coupled interface is   */
/* enabled.                                                    */
/* CCPU_OPT carries additional information on the interface to */
/* assit better scheduling at MAC                              */
#define LCKWUIKWU

/* RGU interface between RLC and MAC should be light weight   */
/* loosely coupled for performance.                           */
/* TODO - Do we also need loose coupled interface             */
#define LWLCKWLIRGU
#define LCKWLIRGU
#define CCPU_OPT

/* The management of enabling of loose coupling code based     */
/* on the selection of coupling choice between RLC and other   */
/* modules is below.                                           */

/* Other RLC product flags */
#undef RLC_STATUS_GEN
#undef UL_PROC_MAC

/* ****** THIS SECTION REQUIRES NO FURTHER CHANGES. ********** */
#ifdef LCKWUICKW
#ifndef LCCKW
#define LCCKW
#endif
#endif

#ifdef LCKWMILKW
#ifndef LCLKW
#define LCLKW
#endif
#endif

#ifdef LCKWUIKWU
#ifndef LCKWU
#define LCKWU
#endif
#endif

#endif   /* KW */

/****************************************************************************
                     LTE-PDCP Section
****************************************************************************/
#ifdef PJ

#ifndef PX
#define PX
#endif

#define LCPJMILPJ
#define LCPJUICPJ
#define LCPJUIPJU

/* Other PDCP product flags */
#define LTE_HENB
#undef CIPH_BATCH_PROC

/* The handling of enabling LC based on whether PDCP enabled   */
/* loose coupling when PDCP is acting as the source.           */
/* ****** THIS SECTION REQUIRES NO FURTHER CHANGES. ********** */
#ifdef LCPJMILPJ
#ifndef LCLPJ
#define LCLPJ
#endif
#endif 

#ifdef LCPJUICPJ
#ifndef LCCPJ
#define LCCPJ
#endif
#endif

#ifdef LCKWUIKWU
#ifndef LCKWU
#define LCKWU
#endif
#endif

#ifdef LCPJUIPJU
#ifndef LCPJU
#define LCPJU
#endif
#endif

#undef SPACC_NONBLOCKING
#undef INTEL_NATIVE_SPACC
#undef INTEL_SPACC_IV_OPTIMIZATION
#undef  SPACC_THREADED
#endif  /* PJ */

/****************************************************************************
                     TOTALeNodeB Application section
****************************************************************************/
#ifdef WR

/* Since application is many different layers to the lower layers */
/* it must define multiple entities as self entities.             */
#ifndef EU
#define EU
#endif

#ifndef EG
#define EG
#endif

/* RRC user */
#ifndef NX
#define NX
#endif

/* S1AP user */
#ifndef UZ
#define UZ
#endif

/* X2AP user */
#ifndef RS
#define RS
#endif

/* Include all the layers that are part of the same binary.    */
/* We have stack manager (SM), S1AP (SZ), X2AP (CZ), RRM (RM), */
/* RRC(NH) within the same binary.                             */
#ifndef SM
#define SM
#endif

#ifndef SZ
#define SZ
#endif

#ifndef CZ
#define CZ
#endif

#ifndef NH
#define NH
#endif

#ifndef RM
#define RM
#endif

#ifndef PX
#define PX
#endif

/* Coupling choices between application and other layers */
/* TODO - LWLCWRLIRGR should not be needed.              */
/* TODO - LCEULIEGT should not be needed.                */
/* TODO - LCNXLINHU should not be needed.                */
#define LCWRMILWR
#define LWLCWRMILWR
#define LCWRLIEGT
#define LCPXLIPJU
#define LCWRLICTF
#define LWLCNXLINHU
#define LCUZLISZT
#define LWLCUZLISZT
#define LCWRLIRGR
#define LWLCWRLIRGR
#define LCEULIEGT
#define LCNXLINHU
#define LCRSLICZT
#define LWLCRSLICZT
#define LCSZUISZT

/* Coupling choices between stack manager and the layers */
/* TODO LCSMSBMILSB should be replaced with LCSMMILSB.   */
/* TODO LCSMHIMILHI should be replaced with LCSMMILHI.   */
#define LCSMMILEG
#define LCSMMILCZ
#define LCSMMILSZ
#define LCSMSBMILSB
#define LCSMMILHI
#define LCSMHIMILHI

/* TODO LCKWMILKW should be changed to LCSMMILKW in SMM  */
/*      LCKWMILKW should be used only in RLC product     */
#define LCSMMILRG
#define LCSMMILNH
#define LCSMNHMILNH
#define LCKWMILKW
#define LCSMMILPJ
#define LCSMMILRM
#define LCSMMILYS 
#define LWLCSMMILWR
#define LCSMMILWR
#define LWLCSMMILWR
#define LCSMYSMILYS
#define LCYSMILYS

/* Application functionality related flags */
#define SI_NEW
#define LTE_HO_SUPPORT
#define WR_SIBS_ENBLD
//#define WR_DETECT_RLF
#define WR_DL_CQI
#define WR_RSYS_KPI
#define WR_WATCHDOG
#define WR_IPV6_OAM_WORKAROUND

#undef WR_GRPPWR_CNTRL
/* #undef ENB_OVRLOAD */
/* The handling of enabling LC based on whether TeNB enabled   */
/* loose coupling when PDCP is acting as the source.           */
/* ****** THIS SECTION REQUIRES NO FURTHER CHANGES. ********** */
#ifdef LCWRMILWR
#ifndef LCLWR
#define LCLWR
#endif
#endif

#ifdef LCWRLINHU
#ifndef LCNHU
#define LCNHU
#endif
#endif

#ifdef LCSZUISZT
#ifndef LCSZT
#define LCSZT
#endif
#endif
#ifdef LCNXLINHU
#ifndef LCNHU
#define LCNHU
#endif
#endif

#ifdef LWLCNXLINHU
#ifndef LWLCNHU
#define LWLCNHU
#endif
#endif

#ifdef LCWRLIEGT
#ifndef LCEGT
#define LCEGT
#endif
#endif

#ifdef LCPXLIPJU
#ifndef LCPJU
#define LCPJU
#endif
#endif


#ifdef LCWRLICTF
#ifndef LCCTF
#define LCCTF
#endif
#endif

#ifdef LCWRLIRGR
#ifndef LCRGR
#define LCRGR
#endif
#endif

#ifdef LCRSLICZT
#ifndef LCCZT
#define LCCZT
#endif
#endif

#ifdef LWLCRSLICZT
#ifndef LWLCCZT
#define LWLCCZT
#endif
#endif

/* *************  SM and layer interaction flags **************** */
#ifdef LCSMMILWR
#ifndef LCLWR
#define LCLWR
#endif
#endif

#ifdef LWLCSMMILWR
#ifndef LWLCLWR
#define LWLCLWR
#endif
#endif

#ifdef LCSMMILRG
#ifndef LCLRG
#define LCLRG
#endif
#endif

#ifdef LCSMMILEG
#ifndef LCLEG
#define LCLEG
#endif
#endif

#ifdef LCSMMILNH
#ifndef LCLNH
#define LCLNH
#endif
#endif

#ifdef LWLCSMMILWR
#ifndef LWLCLWR
#define LWLCLWR
#endif
#endif

#ifdef LCSMMILPJ
#ifndef LCLPJ
#define LCLPJ
#endif
#endif

#ifdef LCKWMILKW
#ifndef LCLKW
#define LCLKW
#endif
#endif

#ifdef LCSMYSMILYS
#ifndef LCLYS
#define LCLYS
#endif
#endif

#ifdef LCYSMILYS
#ifndef LCLYS
#define LCLYS
#endif
#endif

/* TODO - This definition does not follow naming conventions and  */
/* also is a duplicate of the above macro. This should be removed */
/* from the code and then from this make file.                    */
#ifdef LCSMNHMILNH
#ifndef LCLNH
#define LCLNH
#endif
#endif

#endif  /* WR */
/* ************** End of TeNB Application section  *************** */

/****************************************************************************
                     X2AP section
****************************************************************************/
#ifdef CZ
#undef CZ
#define CZ 1

/* Define the layers that coexist with X2AP. They are SCTP (SB), */
/* X2AP user (RS/WR), stack manager (SM).                        */
#ifndef SB
#define SB
#endif

#ifndef RS
#define RS
#endif

#ifndef SM
#define SM
#endif

/* product options */
#define CZ_ENB
#define CZ_DYNAMIC_PEER
#define CZ_USTA

/* interface options */
#define LCCZUICZT     /* loosely coupled, CZ upper layer CZT interface */
#define LCCZLISCT     /* loosely coupled, CZ lower layer SCT interface */
#define LCCZMILCZ     /* loosely coupled, CZ manegement  LCZ interface */

/* Based on the selection of coupling above the section below  */
/* defines enabling/disabling of loose coupling on the         */
/* respective interfaces                                       */
/* ****** THIS SECTION REQUIRES NO FURTHER CHANGES. ********** */
/* Interface between S1AP and Application */
#ifdef LCCZUICZT
#ifndef LCCZT
#define LCCZT    1
#endif
#endif

/* Interface between X2AP and management (SM) */
#ifdef LCCZMILCZ
#ifndef LCLCZ
#define LCLCZ    1
#endif
#endif

/* Interface between X2AP and Application */
#ifdef LWLCCZUICZT
#ifndef LWLCCZT
#define LWLCCZT
#endif
#endif

/* Interface between SCTP and X2AP */
#ifdef LCCZLISCT
#ifndef LCSCT
#define LCSCT
#endif
#endif

#endif /* CZ */

/* ******************************************************************* */
/*                          TUCL section                               */
/* ******************************************************************* */
#ifdef HI

/* Define the products that TUCL directly talks to and are part of the */
/* same binary.                                                        */
#ifndef SB
#define SB
#endif

#ifndef EG
#define EG
#endif

#ifndef SM
#define SM
#endif

/* We need to define LCHIUIHIT if there is at least one layer talking */
/* to TUCL in a loosely coupled fashion.                              */
#define LCHIUIHIT
#define LCHIMILHI

/* The section below should not be edited normally.                   */
#ifdef LCHIUIHIT
#ifndef LCHIT
#define LCHIT
#endif
#endif

#ifdef LCHIMILHI
#ifndef LCLHI
#define LCLHI
#endif
#endif
#endif /* HI */

/****************************************************************************
                     SON section
****************************************************************************/
#ifdef NL
#define LWLCSMSONILNL 
#define TCSMSONILNL
#define LCSMSONILNL 


#ifdef LWLCSMSONILNL
#define NLU_LWLC 
#endif 

#ifdef LCSMSONILNL 
#define NLU_LC
#endif

#ifdef TCSMSONILNL
#define NLU_TC 
#endif

#endif
/****************************************************************************
                     RRM section
****************************************************************************/
#ifdef RM

#define LCRMLIRGM
#define LWLCRMLIRGM
#define LWLCRMUIRMU
#define LWLCSMRMMILRM
#define LCSMRMMILRM
#define PTSMMILRM
#define LCRMMILRM

#ifdef LCRMLIRGM
#ifndef RGM_LC
#define RGM_LC
#endif
#endif

#ifdef LWLCRMLIRGM
#ifndef RGM_LWLC
#define RGM_LWLC
#endif
#endif



/* TODO: By conventions we should have this name LCRMU instead of RMU_LC */
#ifdef LCRMUIRMU
#ifndef RMU_LC
#define RMU_LC
#endif
#endif

#ifdef LWLCRMUIRMU
#ifndef RMU_LWLC
#define RMU_LWLC
#endif
#endif

#ifdef LCRMMILRM
#ifndef LCLRM
#define LCLRM
#endif
#endif
#endif

#endif /* __ENVOPTH__ */

  
/********************************************************************30**
  
         End of file:     envopt.h@@/main/367 - Tue Mar 13 16:57:02 2012
     
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
1.1             jrl     1. initial release.
 
*********************************************************************91*/
