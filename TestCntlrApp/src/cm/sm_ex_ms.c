
/********************************************************************20**
  
     Name:     layer management - external interface - mos 
  
     Type:     C source file
  
     Desc:     Entry point for scheduling layer manager in loosely 
               coupled systems.

     File:     sm_ex_ms.c
  
     Sid:      sm_ex_ms.c@@/main/132 - Wed Nov 30 17:39:51 2011
  
     Prg:      rg
  
*********************************************************************21*/
  
  
/*
*     this software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000001     Physical Layer - SCC
*     1000002     Data Link Layer - LAPB
*     1000003     Data Link Layer - LAPD
*     1000004     Data Link Layer - Multilink
*     1000005     Data Link Layer - LAPB & LAPD
*     1000006     Network Layer - X.25 Intermediate System
*     1000007     Network Layer - X.25 End System
*     1000008     Network Layer - X.75
*     1000009     Network Layer - Q.930/Q.931
*     1000010     Application Layer - Asynchronous PAD
*     1000012     Spanning Tree
*     1000014     Network Layer - X.25 End & Intermediate System
*     1000016     Network Layer - ISO Internet Protocol - End System
*     1000017     Data Link Layer - Basic Frame Relay
*     1000018     Data Link Layer - Extended Frame Relay
*     1000019     Data Link Layer - Logical Link Control 1
*     1000020     Data Link Layer - Logical Link Control 2
*     1000021     Data Link Layer - Logical Link Control 3
*     1000022     Network Layer - ISO Internet Protocol - Intermediate System
*     1000023     Network Layer - X.31
*     1000024     Signalling System 7
*     1000026     TCP/IP
*     1000034     Physical Layer - ISAC-S
*     1000035     68302 MOS/SCC
*     1000040     UDP/IP
*     1000043     Network Layer - Q.93B
*     1000044     Data Link Layer - Q.SAAL
*     1000048     UNI Management Entity (UME)
*     1000049     Frame Relay Network - Q.933 Entity
*     1000050     LAN Emulation Client (LEC)
*     1000053     Physical Layer - Fujitsu ALC
*     1000054     Data Link Layer - Q.2140
*     1000063     Service Specific Coordination Funtion - Q.2140
*     1000066     LAN Emulation Services (LEServices)
*     1000074     Data Link Layer - LAPV5-DL 
*     1000075     V5.1 PSTN Network Layer 
*     1000096     V5.x Protection Protocol Network Layer 
*     1000139     MPC860SAR driver
*     1000156     SIP Session Initiation Protocol
*     1000163     MPC8260 driver
*     1000241     3GPP-MAC
*     1000243     3GPP-NBAP
*     1000342     D2 DL layer
*     1000347     LAPDm
*     1000349     Diameter Layer
*     1000206     RRC 2.0
*
*/
  
  
/* header include files (.h) */
  
#include "envopt.h"        /* environment options */  
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

#ifdef SM_ATM
#include "cm_atm.h"        /* common ATM defines */
#endif

#ifdef SM_SS7
#include "cm_ss7.h"        /* common ss7 defines */
#endif

#ifdef AP       
#include "lap.h"           /* async pad management interface */           
#endif
#ifdef IN       
#include "lin.h"           /* Q.930/Q.931 management interface */
#endif
#ifdef AM       
#include "lam.h"           /* Q.93B management interface */
#endif
#ifdef AS       
#include "las.h"           /* Q.SAAL management interface */
#endif
#ifdef AC       
#include "lac.h"           /* AC driver management interface */
#endif
#ifdef PN       
#include "lpn.h"           /* PNNI management interface */
#endif
#ifdef UM       
#include "lum.h"           /* UME management interface */
#endif
#ifdef IM       
#include "cm_snmp.h"       /* common snmp encode/decode library */
#include "lim.h"           /* IME management interface */
#endif
#ifdef XG       
#include "lxn.h"           /* x.75 management interface */
#endif
#ifdef EI       
#include "lxn.h"           /* x.25 end and intermediate system management interface */
#endif
#ifdef XE       
#include "lxn.h"           /* x.25 end system management interface */
#endif
#ifdef XI       
#include "lxn.h"           /* x.25 intemediate system management interface */
#endif
#ifdef XN       
#include "lxn.h"           /* x.25/x.75 system management interface */
#endif
#ifdef BD       
#include "lbd.h"           /* lapb and lapd management interface */
#endif
#ifdef LD       
#include "lbd.h"           /* lapd management interface */
#endif
#ifdef LB       
#include "lbd.h"           /* lapb management interface */
#endif
#ifdef D2       
#include "ld2.h"           /* D2 management interface */
#endif
#ifdef BR       
#include "lfr.h"           /* basic frame relay management interface */
#endif
#ifdef FR       
#include "frd.h"           /* frame data link layer */
#include "lfr.h"           /* frame relay management interface */
#endif
#ifdef ER       
#include "frd.h"           /* frame data link layer */
#include "lfr.h"           /* extended frame relay management interface */
#endif
#ifdef SC       
#include "lsc.h"           /* scc management interface */
#endif
#ifdef IS       
#include "lis.h"           /* isac-s management interface */
#endif
#ifdef SE       
#include "lse.h"           /* sec management interface */
#endif
#ifdef IX       
#include "lix.h"           /* x.31 management interface */
#endif
#ifdef TC       
#include "cm_umts.h"       /* sm_ex_ms_c_001.main_110 */
#include "ltc.h"           /* TCP/IP management interface */
#endif
#ifdef UD       
#include "lud.h"           /* UDP/IP management interface */
#endif
#ifdef MS       
#include "lms.h"           /* mos management interface */
#endif
#ifdef NS
#include "lns.h"           /* NTSS management interface */
#endif
#ifdef SD       
#include "lsd.h"           /* MTP level 2 management interface */
#endif
#ifdef SI       
#include "lsi.h"           /* ISUP management interface */
#endif
#ifdef TP       
#include "ltp.h"           /* TUP management interface */
#endif
#ifdef SP       
#include "lsp.h"           /* SCCP management interface */
#endif
#ifdef RA       
#include "lra.h"           /* RANAP management interface */
#endif
/* sm_ex_ms_c_001.main_128: LDF-RANAP removed duplicate include of header files */
#ifdef GM       
#include "cm_gprs.h"      
#include "lgm.h"           /* GMM management interface */
#endif
#ifdef ST       
#include "lst.h"           /* TCAP management interface */
#endif
#ifdef SN       
#include "lsn.h"           /* MTP Level 3 management interface */
#endif
#ifdef EC
#include "lec.h"           /* LEC management interface */
#endif
#ifdef ES
#include "les.h"           /* LES management interface */
#endif
#ifdef WD       
#include "cm_wp.h"         /* ss7 wrapper common */
#include "lwd.h"           /* MTP Level 2 wrapper management interface */
#endif
#ifdef WN       
#include "cm_wp.h"         /* ss7 wrapper common */
#include "lwn.h"           /* MTP Level 3 wrapper management interface */
#endif
#ifdef WI       
#include "cm_wp.h"         /* ss7 wrapper common */
#include "lwi.h"           /* ISUP wrapper management interface */
#endif
#ifdef WU       
#include "cm_wp.h"         /* ss7 wrapper common */
#include "lwu.h"           /* TUP wrapper management interface */
#endif
#ifdef WS       
#include "cm_wp.h"         /* ss7 wrapper common */
#include "lws.h"           /* SCCP wrapper management interface */
#endif
#ifdef WC       
#include "cm_wp.h"         /* ss7 wrapper common */
#include "lwc.h"           /* TCAP wrapper management interface */
#endif
#ifdef QI       
#include "lqi.h"           /* QI management interface */
#endif
#ifdef PQ       
#include "cm_ldrvr.h"      /* Common Driver Manmt. i/f */
#include "lpq.h"           /* PQ management interface */
#endif
#ifdef ME       
#include "lme.h"           /* ME management interface */
#endif
#ifdef IS       
#include "lis.h"           /* IS management interface */
#endif
#ifdef FM       
#include "lfm.h"           /* FM management interface */
#endif
#ifdef RY       
#include "lry.h"           /* RY management interface */
#endif
#ifdef FA       
#include "lfa.h"           /* FA management interface */
#endif
#ifdef BI       
#include "lbi.h"           /* BI management interface */
#endif
#ifdef SA       
#include "cm_atm.h"        /* common atm */
#include "lsa.h"           /* Q.2140 management interface */
#endif
#ifdef FN
#include "cm_isdn.h"
#include "fnt.h"
#include "lfn.h"           /* Q.933 management interface */
#endif
#ifdef EV
#include "lev.h"           /* V5 Envelope Function management interface */
#endif
#ifdef LV
#include "llv.h"           /* lapv management interface */
#endif
#ifdef NV
#include "lnv.h"           /* v5.1 PSTN management interface */
#endif
#ifdef MA
#include "lma.h"           /* MAP management interface */
#endif
#ifdef IA
#include "lia.h"           /* map is41 management interface */
#endif
#ifdef PL
#include "lpl.h"           /* LASAR driver management interface */
#endif
#ifdef AF
#include "laf.h"           /* FR-ATM management interface */
#endif
#ifdef CV
#include "lcv.h"           /* v5.X Control Protocol management interface */
#endif
#ifdef BV
#include "bvt.h"
#include "lbv.h"           /* v5.X BCC Protocol management interface */
#endif
#ifdef MV
#include "lmv.h"           /* v5.X System Manager management interface */
#endif
#ifdef ICC
#include "cm_cc.h"         /* call control common */
#ifdef CCSI
#include "sit.h"                /* PSIF interface*/
#endif
#ifdef CCBI
#include "bit.h"                /* PSIF interface*/
#endif
#ifdef CCIN
#include "int.h"                /* PSIF interface*/
#endif
#if (defined(CCAM) || defined(PNNI_ROUTING_ENABLED))
#include "amt.h"                /* PSIF interface*/
#endif
#ifdef PNNI_ROUTING_ENABLED
#include "pci.h"                /* PNNI interface*/
#endif /* PNNI_ROUTING_ENABLED */
#include "cct.h"                /* PSIF interface*/
#include "rtt.h"                /* router interface */
#include "rmt.h"                /* Resource Manager interface */
#include "sft.h"                /* Switching Fabric Manager interface */
#include "lcc.h"           /* call control */
#endif 
#ifdef LK 
#include "llk.h"           /* V5.2 LC Protocol.  */
#endif /* LK */
#ifdef IE
#include "lie.h"           /* INAP management interface */           
#endif
#ifdef TT
#include "cm_inet.h"       /* common sockets */
#include "ltt.h"           /* TCAP over TCP/IP management interface */
#endif



#ifdef PA
#include "lpa.h"           /* PLOA - Protocol Layers Over ATM */
#endif

#ifdef PV 
#include "lpv.h"           /* V5.2 Protection Protocol.  */
#endif /* PV */

#ifdef RT
#include "cm_cc.h"         /* Common call control */
#include "lrt.h"           /* Router */
#endif
 
#if 0
#ifdef RM
#include "cm_cc.h"         /* Common call control */
#include "rm.h"
#ifdef PNNI_ROUTING_ENABLED
#include "lpn.h"
#endif /* PNNI_ROUTING_ENABLED */
#include "lrm.h"           /* Resource Manager */
#endif
#endif

#ifdef XM
#include "lxm.h"           /* Connection Manager */
#endif

#ifdef SF
#include "cm_cc.h"         /* Common call control */
#include "lsf.h"           /* Switching Fabric Manager */
#endif

#ifdef VF
#include "lvf.h"           /* Integrated V5 Layer3 */
#endif

#ifdef VW_COMPILE
#undef SH
#endif

#ifdef SH
#ifdef TDS_CORE2
#include "cm_ftha.h"       /* Common - FT/HA */
#else
#include "cm_cftha.h"      /* Common Core - FT/HA */
#endif /* TDS_CORE2 */    
#include "lsh.h"           /* System Agent */
#endif

#ifdef MR
#ifdef TDS_CORE2
#include "cm_ftha.h"       /* Common - FT/HA */
#else
#include "cm_cftha.h"      /* Common Core - FT/HA */
#endif /* TDS_CORE2 */    
#include "lmr.h"           /* Message Router */
#endif

#ifdef SG
#ifdef TDS_CORE2
#include "cm_ftha.h"       /* Common - FT/HA */
#else
#include "cm_cftha.h"      /* Common Core - FT/HA */
#endif /* TDS_CORE2 */    
#include "lsh.h"           /* System Agent */
#include "lmr.h"           /* Message Router */
#include "lsg.h"           /* System Manager */
#endif

#ifdef PR
#include "cm_atm.h"
#include "aal.h"
#include "mpc860sr.h"
#include "lpr.h"            /* MPC860SAR driver */
#endif

#ifdef GN
#include "cm_gprs.h"       /* common gprs */
#include "lgn.h"           /* Network Service  */
#endif

#ifdef GT
#include "cm_gprs.h"       /* common gprs */
#include "cm_inet.h"       /* Common Socket  */
#include "cm_tpt.h"       /* Common transport  */
#include "lgt.h"           /* GTP  */
#endif

#ifdef GL
#include "cm_gprs.h"
#include "lgl.h"           /* GPRS Logical Link Control (LLC) */
#endif

#ifdef GG
#include "cm_gprs.h"       /* common gprs */
#include "lgg.h"           /* BSS GPRS Protocol (BSSGP) */
#endif

#ifdef HC
#include "cm_mblk.h"        /* memory management */
#include "cm_tkns.h"        /* common tokens */
#include "cm_inet.h"        /* common sockets */
#include "cm32x.h"          /* common H.323 */
#ifdef TRIL_HZ
#include "cm_ftha.h"       /* Common FTHA file */
#include "cm_psfft.h"      /* Common PSF file */
#endif /* TRIL_HZ */
#include "cm_tpt.h"         /* common transport */

#ifdef TRIL_HZ
#include "cm_ftha.h"       /* Common FTHA file */
#include "cm_psfft.h"      /* Common PSF file */
#endif /* TRIL_HZ */

#ifdef H323_ANXE
#include "cm5.h"            /* Timer Library */
#include "cm_hash.h"        /* Hash List Library */
#include "cm_llist.h"       /* Link List Library */
#include "cm_nxe.h"         /* Annex E header file */
#endif /* H323_ANXE */
#include "lhc.h"            /* H.323 */
#endif

#ifdef HI
#include "lhi.h"            /*  TUCL management defines */
#endif

#ifdef HG
#include "cm_mblk.h"        /* memory management */
#include "cm_tkns.h"        /* common tokens */
#include "cm_inet.h"        /* common sockets */
#include "cm32x.h"          /* common H.323 */
#include "cm_tpt.h"         /* common transport */
#include "lhgt.h"
#include "lhg.h"            /* Annex G */
#endif

#ifdef GS
#include "cm_gprs.h"        /* common gprs */
#include "lgs.h"            /* SNDCP */
#endif

#ifdef HR
#include "cm_tpt.h"         /* common transport */
#include "cm_rtp.h"         /* common RTP/RTCP */
#include "lhr.h"            /* RTP/RTCP */
#endif

#ifdef IQ                  /* Q.930/931-Q.SAAL Convergence Layer */
#include "cm_atm.h"        /* common atm */
#include "liq.h"           /* Q.930/931-Q.SAAL Convergence Layer management
                              interface */
#endif

#ifdef DG
#include "cm_ftha.h"       /* Common FTHA Defines */
#include "cm_inet.h"        /* common sockets */
#include "cm_tpt.h"         /* common transport */
#include "ldg.h"           /* LDF-GCP Layer Manager Interface */
#endif /* DG */


#ifdef DN
#include "cm_hash.h"        /* common to Hashing */
#include "cm_ftha.h"        /* common to DFT/HA */
#include "cmzndn.h"         /* common to PSF and LDF MTP3 */
#include "cmzndnlb.h"       /* common to PSF and LDF MTP3 */
#include "ldn.h"            /* LDF-MTP3 layer management */
#endif /* DN */

#ifdef DI
#include "cm_hash.h"        /* common to Hashing */
#include "cm_ftha.h"        /* common to DFT/HA */
#include "ldi.h"            /* LDF-ISUP layer management */
#endif /* DI */

#ifdef VO
#include "cm_atm.h"        /* ATM specific defines */
#include "vo_hw.h"         /* hardware defines */
#include "vo_tune.h"       /* parameters tunable by the user */
#include "lvo.h"           /* MPC8260 driver management interface */
#endif

#ifdef SB
#include "cm_tpt.h"        /* Transport address specific */
#include "cm_dns.h"        /* Transport address specific */
#include "sct.h"           /* SCT Interface specific */
#include "lsb.h"           /* SCTP LM */
#endif /* SB */

#if (defined(MG) && !(defined(DG_ACC)))
#ifdef ZG
#include "cm_ftha.h"
#include "cm_psfft.h"
#endif /* ZG */
#include "cm_mblk.h"        /* memory management */
#include "cm_tkns.h"        /* common tokens */
#include "cm_inet.h"        /* common sockets */
#include "cm_tpt.h"         /* common transport */
#include "cm_dns.h"         /* common DNS libraru defines */
#include "cm_sdp.h"        /* Session Description Protocol Defines */
#include "mgt.h"            /* MGCP layer */
#include "lmg.h"            /* MGCP layer */
#endif /* (defined(MG) && !(defined(DG_ACC))) */

#ifdef SO                  /* SIP */
#include "cm_tpt.h"        /* common transport */
#include "cm_tkns.h"       /* common tokens */
#include "cm_sdp.h"        /* common SDP */
#include "cm_mblk.h"       /* common memory allocation */
#include "sot.h"
#include "sct.h"           /* SCT interface defines           */
#include "lso.h"
#endif

#ifdef IT
#include "cm_tpt.h"        /* Transport address specific */
#include "sct.h"           /* SCT Interface specific */
#include "lit.h"           /* M3UA LM */
#include "smit_err.h"        /* M3UA Stack Manager error */
#endif /* IT */

#ifdef NF
#include "lnf.h"           /* NIF LM */
#endif /* NF */

#ifdef LN
#include "cm_inet.h"
#include "cm_tpt.h"
#include "cm_atm.h"
#include "cm_mpls.h"
#include "lln.h"           /* MPLS-LDP(+CR) management defines */
#endif

#ifdef AL
#include "gen.h"
#include "cm_hash.h"
#include "cm_llist.h"
#include "cm_rdx.h"
#include "cm_ptree.h"
#include "cm_atm.h"
#include "lal.h"           /* AAL2 Layer Manager defines */
#endif /* AL */

#ifdef DP
#include "spt.h"            /* SPT interface */
#include "cm_hash.h"        /* common to Hashing */
#include "cm_ftha.h"        /* common to DFT/HA */
#include "cmzpdp.h"         /* common to PSF and LDF SCCP */
#include "ldp.h"            /* LDF-SCCP layer management */
#endif /* DP */

/* sm_ex_ms_c_001.main_109: LDF-SUA 1.1 REL */
#ifdef AH
#include "spt.h"            /* SPT interface */
#include "cm_hash.h"        /* common to Hashing */
#include "cm_ftha.h"        /* common to DFT/HA */
#include "cmaeah.h"         /* common to PSF and LDF SCCP */
#include "lah.h"            /* LDF-SUA layer management */
#endif /* AH */

#ifdef DT
#include "cm_ftha.h"        /* common to DFT/HA */
#include "stu.h"            /* stu interface */
#include "cmztdt.h"         /* common to PSF and LDF TCAP */
#include "cmztdtlb.h"       /* common to PSF and LDF TCAP */
#include "ldt.h"            /* LDF-TCAP layer management */
#endif /* DT */

#ifdef ID                  /* SIGTRAN - IUA */
#include "cm_tpt.h"
#include "sct.h"
#include "lid.h"
#endif

#ifdef ND                  /* IUA - NIF */
#include "lnd.h"
#endif

#ifdef SU 
#include "cm_tpt.h"        /* Transport address specific */
#include "sct.h"           /* SCT Interface specific */
#include "cm_hash.h"
#include "cm_spgtt.h"
#include "lsu.h"           /* SUA LM */
#endif /* SU */

#ifdef NP
#include "lnp.h"           /* SUA - NIF LM */
#endif /* NP */
#ifdef QC                  /* CAP */
#include "lqc.h"
#endif

#ifdef GA
#include "cm_gprs.h"       /* common gprs */
#include "lga.h"           /* BSS Application Part (BSSAP+) */
#endif

#ifdef MW                  /* M2UA */
#include "cm_tpt.h"
#include "sdt.h"
#include "mwt.h"
#include "sct.h"
#include "lmw.h"
#endif

#ifdef NW                  /* M2UA-NIF */
#include "sdt.h"
#include "mwt.h"
#include "lnw.h"
#endif

#ifdef MX                  /* M2PA */
#include "cm_tpt.h"
#include "sdt.h"
#include "sct.h"
#include "lmx.h"
#endif

#ifdef MK
#include "cm_umts.h"
#include "lmk.h"           /* 3G MAC management interface */
#endif

#ifdef MD
#include "cm_umts.h"
#include "lmd.h"           /* 3G MAC-HS management interface */
#endif


#ifdef RL
#include "cm_umts.h"
#include "lrl.h"           /* 3G RLC management interface */
#endif

#ifdef IB
#include "cm_tpt.h"
#include "cm_atm.h"        /* 3G NBAP management interface */
#include "sct.h"           /* SCT interface */
#include "lib.h"
#endif

/* sm_ex_ms_c_001.main_111: RRC 2.0 */
#ifdef RR
#include "lrr.h"           /* 3G RRC management interface */
#endif

#ifdef RG
#include "lrg.h"           /* LTE MAC management interface */
#endif

/* sm_ex_ms_c_001.main_122 - LTE RLC 1.1 */
#ifdef KW 
#include "cm_lte.h"           /* LTE RLC management interface */
#include "lkw.h"           /* LTE RLC management interface */
#endif


#ifdef RN
#include "lrn.h"        /* RNSAP   management interface */
#endif

#ifdef FP
#include "lfp.h"        /* FP management interface */
#endif

#ifdef VU
#include "lvu.h"        /* VU management interface */
#endif

#ifdef DV
#include "cm_hash.h"        /* common to Hashing */
#include "cm_ftha.h"        /* common to DFT/HA */
#include "cmzvdv.h"         /* common to PSF and LDF-M3UA */
#include "cmzvdvlb.h"       /* common to PSF and LDF-M3UA */
#include "ldv.h"            /* LDF-M3UA layer management */
#endif /* DV */

#ifdef MC
#include "lmc.h"
#endif

#ifdef MZ                   /* M1UA - NIF */
#include "cm_tpt.h"         /* Transport Layer defines */
#include "sct.h"            /* Relay lwer Interface */
#include "mac.h"            /* Relay lwer Interface */
#include "lmz.h"
#endif

#ifdef RP
#include "cm_ftha.h"        /* common to DFT/HA */
#include "cmzarp.h"         /* common to PSF and LDF-RANAP */
#include "lrp.h"            /* LDF-RANAP layer management */
#endif

/* sm_ex_ms_c_001.main_108: Addition */
#ifdef AQ                  /* Diameter */
#include "cm_tpt.h"        /* common transport */
#include "cm_tkns.h"       /* common tokens */
#include "cm_mblk.h"       /* common memory allocation */
#include "cm_inet.h"       /* common memory allocation */
#include "cm_llist.h"       /* common memory allocation */
#include "cm_hash.h"       /* common memory allocation */
#include "cm_tpt.h"       /* common memory allocation */
#include "cm_dns.h"       /* common memory allocation */
#include "cm5.h"       /* common memory allocation */
/* sm_ex_ms_c_001.main_131: Updated for psf-Diameter. */
#ifdef JC
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#endif /* JC */
#include "aqu.h"
#include "sct.h"           /* SCT interface defines           */
#ifdef AQ_FTHA
#include "sht.h"           /* SHT interface defines           */
#endif /* AQ_FTHA */
#include "laq.h"
#include "aq_util.h"
#include "aq.h"
/* sm_ex_ms_c_001.main_131: Updated for psf-Diameter. */
#ifdef JC
#include "ljc.h"
#include "jc.h"
#endif /* JC */

#endif

/* sm_ex_ms_c_001.main_118 Updated for S1AP release 1.1 */
#ifdef SZ
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "sct.h"           /* SB (SCTP) layer */
/* sm_ex_ms_c_001.main_130: Added SHT file header include as lsz.x
 * uses the SHT releated structures */
#ifdef SZ_FTHA            
#include "sht.h"           /* SHT Interface header file */
#endif /* SZ_FTHA */
#include "lsz.h"           /* layer management defines for S1AP */
#endif

/* sm_ex_ms_c_001.main_123 - LTE X2AP 1.1 */
#ifdef CZ
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "sct.h"           /* SB (SCTP) layer */
#include "lcz.h"           /* layer management defines for S1AP */
#endif


#ifdef EG
#include "cm_tpt.h"        /* common transport */
#include "cm_tkns.h"       /* common tokens */
#include "cm_mblk.h"       /* common memory allocation */
#include "cm_inet.h"       /* common memory allocation */
#include "cm_llist.h"       /* common memory allocation */
#include "cm_hash.h"       /* common memory allocation */
#include "cm_tpt.h"       /* common memory allocation */
#include "leg.h"
#endif

#ifdef HM
#include "cm_dns.h"        /* Common hash library             */
#include "cm_tpt.h"        /* Common transport library        */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_inet.h"       /* Common socket library           */
#include "sct.h"           /* SCT interface defines           */
#include "hnt.h"           /* HNT interface defines           */
#include "rut.h"           /* RUT interface defines           */
#include "lhm.h"        /* Iuh Signaling   management interface */
#endif

/* sm_ex_ms_c_001.main_126: LTE eNodeB and LTE convergence layer release */
#ifdef PJ
#include "lpj.h"
#endif

#ifdef VE
/* sm_ex_ms_c_001.main_127: Updated for LTE eNodeB */ 
#include "cm_tpt.h"
#include "cm_inet.h"
#include "lve.h"
#endif

#ifdef NH 
#include "lnh.h"
#endif

#ifdef YS
#include "lys.h"
#endif

/* header/extern include files (.x) */
  
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */

#ifdef SM_ATM
#include "cm_atm.x"        /* common ATM typedefs */
#endif

#ifdef SM_SS7
/* sm_ex_ms_c_001.main_100 - Addition - protected cm_inet.h inclusion
 *                           in SUAP_IPOPT flag */
#ifdef SUAP_IPOPT
#include "cm_inet.x"
#endif
#include "cm_ss7.x"        /* common ss7 typedef */
#endif

#ifdef AP       
#include "lap.x"           /* async pad management interface */           
#endif
#ifdef IN       
#include "lin.x"           /* Q.930/Q.931 management interface */
#endif
#ifdef AM       
#include "lam.x"           /* Q.93B management interface */
#endif
#ifdef AS       
#include "las.x"           /* Q.SAAL management interface */
#endif
#ifdef AC       
#include "lac.x"           /* AC driver management interface */
#endif
#ifdef PN       
#include "lpn.x"           /* PNNI management interface */
#endif
#ifdef UM       
#include "lum.x"           /* UME management interface */
#endif
#ifdef IM       
#include "cm_snmp.x"       /* common snmp encode/decode library */
#include "lim.x"           /* IME management interface */
#endif
#ifdef XG       
#include "lxn.x"           /* x.75 management interface */
#endif
#ifdef EI       
#include "lxn.x"           /* x.25 end and intermediate system management interface */
#endif
#ifdef XE       
#include "lxn.x"           /* x.25 end system management interface */
#endif
#ifdef XI       
#include "lxn.x"           /* x.25 intemediate system management interface */
#endif
#ifdef XN       
#include "lxn.x"           /* x.25/x.75 system management interface */
#endif
#ifdef BD       
#include "lbd.x"           /* lapb and lapd management interface */
#endif
#ifdef LD       
#include "lbd.x"           /* lapd management interface */
#endif
#ifdef LB       
#include "lbd.x"           /* lapb management interface */
#endif
#ifdef D2       
#include "ld2.x"           /* D2 management interface */
#endif
#ifdef BR       
#include "lfr.x"           /* basic frame relay management interface */
#endif
#ifdef FR       
#include "frd.x"           /* frame data link layer */
#include "lfr.x"           /* basic frame relay management interface */
#endif
#ifdef ER       
#include "frd.x"           /* frame data link layer */
#include "lfr.x"           /* extended frame relay management interface */
#endif
#ifdef SC       
#include "lsc.x"           /* scc management interface */
#endif
#ifdef IS       
#include "lis.x"           /* isac-s management interface */
#endif
#ifdef SE       
#include "lse.x"           /* sec management interface */
#endif
#ifdef IX       
#include "lix.x"           /* x.31 management interface */
#endif
#ifdef TC       
#include "cm_umts.x"       /* sm_ex_ms_c_001.main_110 */
#include "ltc.x"           /* TCP/IP management interface */
#endif
#ifdef UD       
#include "lud.x"           /* UDP/IP management interface */
#endif
#ifdef MS       
#include "lms.x"           /* mos management interface */
#endif
#ifdef NS
#include "lns.x"           /* NTSS management interface */
#endif
#ifdef SD       
#include "lsd.x"           /* MTP level 2 management interface */
#endif
#ifdef SI       
#include "lsi.x"           /* ISUP management interface */
#endif
#ifdef TP       
#include "ltp.x"           /* TUP management interface */
#endif
#ifdef SP       
#include "lsp.x"           /* SCCP management interface */
#endif
#ifdef RA       
#include "lra.x"           /* RANAP management interface */
#endif
/* sm_ex_ms_c_001.main_128: LDF-RANAP removed duplicate include of header files */
#ifdef GM       
#include "cm_gprs.x"       
#include "lgm.x"           /* GMM management interface */
#endif
#ifdef ST       
#include "lst.x"           /* TCAP management interface */
#endif
#ifdef SN       
#include "lsn.x"           /* MTP Level 3 management interface */
#endif
#ifdef EC
#include "lec.x"           /* LEC management interface */
#endif
#ifdef ES
#include "les.x"           /* LES management interface */
#endif
#ifdef WD       
#include "cm_wp.x"         /* ss7 wrapper common */
#include "lwd.x"           /* MTP Level 2 wrapper management interface */
#endif
#ifdef WN       
#include "cm_wp.x"         /* ss7 wrapper common */
#include "lwn.x"           /* MTP Level 3 wrapper management interface */
#endif
#ifdef WI       
#include "cm_wp.x"         /* ss7 wrapper common */
#include "lwi.x"           /* ISUP wrapper management interface */
#endif
#ifdef WU       
#include "cm_wp.x"         /* ss7 wrapper common */
#include "lwu.x"           /* TUP wrapper management interface */
#endif
#ifdef WS       
#include "cm_wp.x"         /* ss7 wrapper common */
#include "lws.x"           /* SCCP wrapper management interface */
#endif
#ifdef WC       
#include "cm_wp.x"         /* ss7 wrapper common */
#include "lwc.x"           /* TCAP wrapper management interface */
#endif
#ifdef QI       
#include "lqi.x"           /* QI management interface */
#endif
#ifdef PQ       
#include "cm_ldrvr.x"      /* Common driver management interface */
#include "lpq.x"           /* PQ management interface */
#endif
#ifdef ME       
#include "lme.x"           /* ME management interface */
#endif
#ifdef IS       
#include "lis.x"           /* IS management interface */
#endif
#ifdef FM       
#include "lfm.x"           /* FM management interface */
#endif
#ifdef RY       
#include "lry.x"           /* RY management interface */
#endif
#ifdef FA       
#include "lfa.x"           /* FA management interface */
#endif
#ifdef BI       
#include "lbi.x"           /* BI management interface */
#endif
#ifdef SA       
#include "cm_atm.x"        /* common atm */
#include "lsa.x"           /* Q.2140 management interface */
#endif
#ifdef FN
#include "cm_isdn.x"
#include "fnt.x"
#include "lfn.x"           /* Q.933 management interface */
#endif
#ifdef EV
#include "lev.x"           /* V5 Envelope Function management interface */
#endif
#ifdef LV
#include "llv.x"           /* lapv management interface */
#endif
#ifdef NV
#include "lnv.x"           /* v5.1 PSTN management interface */
#endif
#ifdef MA
#include "lma.x"           /* MAP  management interface */
#endif
#ifdef IA
#include "lia.x"           /* map is41  management interface */
#endif
#ifdef PL
#include "lpl.x"           /* LASAR  management interface */
#endif
#ifdef CV
#include "lcv.x"           /* v5.X Control Protocol management interface */
#endif
#ifdef BV
#include "bvt.x"
#include "lbv.x"           /* v5.X BCC Protocol management interface */
#endif
#ifdef MV
#include "lmv.x"           /* v5.X System Manager management interface */
#endif
#ifdef ICC
#include "cm_cc.x"          /* call control common */
#ifdef CCSI
#include "sit.x"                /* PSIF interface*/
#endif
#ifdef CCBI
#include "bit.x"                /* PSIF interface*/
#endif
#ifdef CCIN
#include "int.x"                /* PSIF interface*/
#endif
#if (defined(CCAM) || defined(PNNI_ROUTING_ENABLED))
#include "amt.x"                /* PSIF interface*/
#endif
#ifdef PNNI_ROUTING_ENABLED
#include "pci.x"                /* PNNI interface*/
#endif /* PNNI_ROUTING_ENABLED */
#ifdef CCXM
#include "xmt.x"                /* PSIF Interface */
#endif /* CCXM */
#include "cct.x"                /* PSIF Interface */
#include "rtt.x"                /* router interface */
#include "rmt.x"                /* Resource Manager interface */
#include "sft.x"                /* Switching Fabric Manager interface */
#include "lcc.x"           /* call control */
#endif 

#ifdef LK
#include "llk.x"           /* V5.2 LC Protocol. */ 
#endif /* LK */
#ifdef IE
#include "lie.x"           /* INAP management interface */           
#endif
#ifdef TT
#include "cm_inet.x"       /* common sockets */
#include "ltt.x"           /* TCAP over TCP/IP management interface */
#endif



#ifdef PA
#include "lpa.x"           /* PLOA - Protocol Layers Over ATM */
#endif

#ifdef PV 
#include "lpv.x"           /* V5.2 Protection Protocol. */
#endif /* PV */

#ifdef RT
#include "cm_cc.x"         /* Common call control */
#include "lrt.x"           /* Router */
#endif
 
#if 0
#ifdef RM
#include "cm_cc.x"         /* Common call control */
#ifdef PNNI_ROUTING_ENABLED
#include "lpn.x"
#endif /* PNNI_ROUTING_ENABLED */
#include "lrm.x"           /* Resource Manager */
#endif
#endif
 
#ifdef XM
#include "lxm.x"           /* Connection Manager */
#endif

#ifdef SF
#include "cm_cc.x"         /* Common call control */
#include "lsf.x"           /* Switching Fabric Manager */
#endif


#ifdef VF
#include "lvf.x"          /* Integrated V5 Layer 3 */
#endif /* VF */ 

#ifdef VW_COMPILE
#undef SH
#endif

#ifdef SH
#ifdef TDS_CORE2
#include "cm_ftha.x"       /* Common - FT/HA */
#endif    /* TDS_CORE2 */
#include "lsh.x"           /* System Agent */
#endif

#ifdef MR
#ifdef TDS_CORE2
#include "cm_ftha.x"       /* Common - FT/HA */
#endif    /* TDS_CORE2 */
#include "lmr.x"           /* Message Router */
#endif

#ifdef SG
#ifdef TDS_CORE2
#include "cm_ftha.x"       /* Common - FT/HA */
#endif    /* TDS_CORE2 */
#include "lsh.x"           /* System Agent */
#include "lmr.x"           /* Message Router */
#include "lsg.x"           /* System Manager */
#endif

#ifdef DL
#include "ldl.x"          /* Dummy Layer    - SWFT */
#endif

#ifdef PR
#include "cm_atm.x"
#include "aal.x"
#include "mpc860sr.x"
#include "lpr.x"            /* MPC860SAR driver */
#endif

#ifdef GN
#include "cm_gprs.x"       /* common gprs */
#include "lgn.x"           /* Network Service  */
#endif

#ifdef GT
#include "cm_gprs.x"       /* common gprs */
#include "cm_inet.x"       /* Common Socket  */
#include "cm_tpt.x"        /* Common transport  */
#include "lgt.x"           /* GTP  */
#endif

#ifdef GL
#include "cm_gprs.x"
#include "lgl.x"          /* GPRS Logical Link Control (LLC) */
#endif

#ifdef GG
#include "cm_gprs.x"       /* common gprs */
#include "lgg.x"           /* BSS GPRS Protocol (BSSGP) */
#endif

#ifdef HC
#include "cm_mblk.x"        /* memory management */
#include "cm_tkns.x"        /* common tokens */
#include "cm_inet.x"        /* common sockets */
#include "cm32x.x"          /* common H.323 */
#ifdef TRIL_HZ
#include "cm_ftha.x"       /* Common FTHA file */
#include "cm_psfft.x"      /* Common PSF file */
#endif /* TRIL_HZ */
#include "cm_tpt.x"         /* common transport */

#ifdef TRIL_HZ
#include "cm_ftha.x"       /* Common FTHA file */
#include "cm_psfft.x"      /* Common PSF file */
#endif /* TRIL_HZ */

#ifdef H323_ANXE
#include "cm5.x"           /* Timer Library */
#include "cm_hash.x"       /* Hash List Library */ 
#include "cm_llist.x"      /* Link List library */
#include "cm_nxe.x"        /* Annex E header file */
#endif /* H323_ANXE */
#include "lhc.x"            /* H.323 */
#endif

#ifdef HI
#include "lhi.x"           /* TUCL management typedefs */
#endif

#ifdef HG
#include "cm_mblk.x"        /* memory management */
#include "cm_tkns.x"        /* common tokens */
#include "cm_inet.x"        /* common sockets */
#include "cm32x.x"          /* common H.323 */
#include "cm_tpt.x"         /* common transport */
#include "lhgt.x"
#include "lhg.x"            /* Annex G */
#endif

#ifdef GS
#include "cm_gprs.x"        /* common gprs */
#include "lgs.x"            /* SNDCP */
#endif

#ifdef HR
#include "cm_tpt.x"         /* common transport */
#include "cm_rtp.x"         /* common RTP/RTCP */
#include "lhr.x"            /* RTP/RTCP */
#endif

#ifdef IQ                  /* Q.930/931-Q.SAAL Convergence Layer */
#include "cm_atm.x"        /* common atm */
#include "liq.x"           /* Q.930/931-Q.SAAL Convergence Layer management
                              interface */
#endif

#ifdef DG
#include "cm_ftha.x"        /* common to DFT/HA */
#include "cm_tpt.x"         /* common transport */
#include "cm_inet.x"        /* common sockets */
#include "ldg.x"           /* LDF-GCP Layer Manager Interface */
#endif /* DG */

#ifdef DN
#include "cm_hash.x"        /* common to hashing */
#include "cm_ftha.x"        /* common to DFT/HA */
#include "cmzndn.x"         /* common to PSF and LDF MTP3 */
#include "cmzndnlb.x"       /* common to PSF and LDF MTP3 */
#include "ldn.x"            /* LDF-MTP3 layer management */
#endif /* DN */

#ifdef DI
#include "cm_hash.x"        /* common to hashing */
#include "cm_ftha.x"        /* common to DFT/HA */
#include "ldi.x"            /* LDF-ISUP layer management */
#endif /* DI */

#ifdef VO
#include "cm_atm.x"        /* ATM specific typedefs */
#include "vo_hw.x"         /* hardware typedefs */
#include "lvo.x"           /* MPC8260 driver management interface */
#endif

#ifdef SB
#include "cm_tpt.x"        /* Transport address specific */
#include "cm_dns.x"        /* Transport address specific */
#include "sct.x"           /* SCT Interface specific  */
#include "lsb.x"           /* SCTP LM */
#endif /* SB */

#if (defined(MG) && !(defined(DG_ACC)))
#ifdef ZG
#include "cm_ftha.x"
#include "cm_psfft.x"
#endif /* ZG */
#include "cm_mblk.x"        /* memory management */
#include "cm_tkns.x"        /* common tokens */
#include "cm_inet.x"        /* common sockets */
#include "cm_tpt.x"         /* common transport */
#include "cm_sdp.x"        /* Session Description Protocol Defines */
#include "mgt.x"            /* MGCP layer */
#include "lmg.x"           /* MGCP layer */
#endif /* (defined(MG) && !(defined(DG_ACC))) */

#ifdef SO                  /* SIP */
#include "cm_tpt.x"        /* common transport */
#include "cm_tkns.x"       /* common tokens */
#include "cm_sdp.x"        /* common SDP */
#include "cm_mblk.x"       /* common memory allocation */
#include "sot.x"
#include "sct.x"           /* SCT interface defines           */
#include "lso.x"
#include "sot.x"
#endif

#ifdef IT
#include "cm_tpt.x"        /* Transport address specific */
#include "sct.x"           /* SCT Interface specific */
#ifdef IT_FTHA            
#include "sht.x"           /* SHT Interface header file */
#endif /* IT_FTHA */
#include "lit.x"           /* M3UA LM */
#endif /* IT */

#ifdef NF
#include "lnf.x"           /* NIF LM */
#endif /* NF */

#ifdef LN
#include "cm_inet.x"
#include "cm_tpt.x"
#include "cm_atm.x"
#include "cm_mpls.x"
#include "lln.x"           /* MPLS-LDP(+CR) management typedefs */
#endif

#ifdef AL
#include "gen.x"
#include "cm_hash.x"
#include "cm_llist.x"
#include "cm_rdx.x"
#include "cm_ptree.x"
#include "cm_atm.x"
#include "cm_ss7.x"
#include "cm_aal2.x"
#include "lal.x"           /* AAL2 management typedefs */
#endif /* AL */  

#ifdef DP
#include "spt.x"            /* SPT interface */
#include "cm_hash.x"        /* common to hashing */
#include "cm_ftha.x"        /* common to DFT/HA */
#include "cmzpdp.x"         /* common to PSF and LDF SCCP */
#include "ldp.x"            /* LDF-SCCP layer management */
#endif /* DP */

/* sm_ex_ms_c_001.main_109: LDF-SUA 1.1 REL */
#ifdef AH
#include "spt.x"            /* SPT interface */
#include "cm_hash.x"        /* common to hashing */
#include "cm_ftha.x"        /* common to DFT/HA */
#include "cmaeah.x"         /* common to PSF and LDF SCCP */
#include "lah.x"            /* LDF-SUA layer management */
#endif /* AH */

#ifdef DT
#include "cm_ftha.x"        /* common to DFT/HA */
#include "stu.x"            /* stu interface */
#include "cmztdt.x"         /* common to PSF and LDF TCAP */
#include "cmztdtlb.x"       /* common to PSF and LDF TCAP */
#include "ldt.x"            /* LDF-TCAP layer management */
#endif /* DT */

#ifdef ID                  /* SIGTRAN - IUA */
#include "cm_tpt.x"
#include "sct.x"
#include "lid.x"
#endif

#ifdef ND                  /* IUA - NIF */
#include "lnd.x"
#endif

#ifdef SU                  /* SUA */ 
#include "cm_tpt.x"        /* Transport address specific */
#include "sct.x"           /* SCT Interface specific */
#include "cm_hash.x"
#include "cm_spgtt.x"
#include "lsu.x"           /* SUA LM */
#endif /* SU */

#ifdef NP
#include "lnp.x"           /* SUA - NIF LM */
#endif /* NP */
#ifdef QC                  /* CAP */
#include "lqc.x"
#endif

#ifdef GA
#include "cm_gprs.x"       /* common gprs */
#include "lga.x"           /* BSS Application Part (BSSAP+) */
#endif

#ifdef MW                  /* M2UA */
#include "cm_tpt.x"
#include "sdt.x"
#include "mwt.x"
#include "sct.x"
#include "lmw.x"
#endif

#ifdef NW                  /* M2UA-NIF */
#include "sdt.x"
#include "mwt.x"
#include "lnw.x"
#endif

#ifdef MX                  /* M2PA */
#include "cm_tpt.x"
#include "sdt.x"
#include "sct.x"
#include "lmx.x"
#endif

#ifdef MK
#include "cm_umts.x"
#include "lmk.x"           /* 3G MAC management interface */
#endif

#ifdef MD
#include "cm_umts.x"
#include "lmd.x"           /* 3G MAC management interface */
#endif


#ifdef RL
#include "cm_umts.x"
#include "lrl.x"           /* 3G RLC management interface */
#endif

#ifdef IB
#include "cm_tpt.x"
#include "cm_atm.x"        /* 3G NBAP management interface */
#include "sct.x"           /* SCT interface */
#include "lib.x"
#endif

/* sm_ex_ms_c_001.main_111: RRC 2.0 */
#ifdef RR
#include "lrr.x"           /* 3G RRC management interface */
#endif

#ifdef RG
/* Combine compilation fixes */
/* sm_ex_ms_c_001.main_129 - ADD - Compilation Fixes */
#include "cm_lte.x"
#include "lrg.x"           /* LTE MAC management interface */
#endif

/* sm_ex_ms_c_001.main_122 - LTE RLC 1.1 */
#ifdef KW 
#include "cm_lte.x"           /* LTE RLC management interface */
#include "lkw.x"           /* LTE RLC management interface */
#endif


#ifdef NL
#include "lnl.h"
#include "lnl.x"
#endif 

#ifdef RN
#include "lrn.x"        /* RNSAP management interface */
#endif

#ifdef FP
#include "lfp.x"        /* FP management interface */
#endif

#ifdef VU
#include "lvu.x"        /* VU management interface */
#endif

#ifdef DV
#include "cm_hash.x"        /* common to hashing */
#include "cm_ftha.x"        /* common to DFT/HA */
#include "cmzvdv.x"         /* common to PSF and LDF-M3UA */
#include "cmzvdvlb.x"       /* common to PSF and LDF-M3UA */
#include "ldv.x"            /* LDF-M3UA layer management */
#endif /* DV */

#ifdef MZ                   /* M1UA - NIF */
#include "cm_tpt.x"         /* Transport Layer defines */
#include "sct.x"            /* Relay lwer Interface */
#include "mac.x"            /* Relay lwer Interface */
#include "lmz.x"
#endif

#ifdef RP
#include "cm_ftha.x"        /* common to DFT/HA */
#include "cmzarp.x"         /* common to PSF and LDF-RANAP */
#include "lrp.x"            /* LDF-RANAP layer management */
#endif

#ifdef LM
#include "llm.h"           /* LAPDm  management interface */
#include "llm.x"           /* LAPDm  management interface */
#endif

/* sm_ex_ms_c_001.main_108: Addition */
/* sm_ex_ms_c_001.main_112: addition of cm_dns.[hx] for dns */
#ifdef AQ                  /* Diameter */
#include "cm_tpt.x"        /* common transport */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_inet.x"       /* common memory allocation */
#include "cm_llist.x"       /* common memory allocation */
#include "cm_hash.x"       /* common memory allocation */
#include "cm_tpt.x"       /* common memory allocation */
#include "cm_dns.x"       /* common memory allocation */
#include "cm5.x"       /* common memory allocation */
/* sm_ex_ms_c_001.main_131: Updated for psf-Diameter. */
#ifdef JC
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif /* JC */
#include "sct.x"           /* SCT interface defines           */
/* sm_ex_ms_c_001.main_131: Updated for psf-Diameter. */
#ifdef AQ_FTHA
#include "sht.x"           /* SHT interface defines           */
#endif
#include "aq_util.x"
#include "aqu.x"
#include "laq.x"
#include "aq.x"
/* sm_ex_ms_c_001.main_131: Updated for psf-Diameter. */
#ifdef JC
#include "ljc.x"
#include "jc.x"
#endif /* JC */

#endif
/* sm_ex_ms_c_001.main_118 Updated for S1AP release 1.1 */
#ifdef SZ
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */


#include "sct.x"           /* SCT interface defines           */
/* sm_ex_ms_c_001.main_130: Added SHT file header include as lsz.x
 * uses the SHT releated structures */
#ifdef SZ_FTHA            
#include "sht.x"           /* SHT Interface header file */
#endif /* SZ_FTHA */
#include "lsz.x"           /* S1AP management interface */
#endif
#ifdef CZ
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */


#include "sct.x"           /* SCT interface defines           */
#include "lcz.x"           /* S1AP management interface */
#endif


#ifdef LX
#include "llx.x"
#endif

#ifdef EG
#include "cm_tpt.x"        /* common transport */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_inet.x"       /* common memory allocation */
#include "cm_llist.x"       /* common memory allocation */
#include "cm_hash.x"       /* common memory allocation */
#include "cm_tpt.x"       /* common memory allocation */
#include "leg.x"
#endif

#ifdef HM
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_tpt.x"        /* Common transport library        */
#include "cm_mblk.x"       /* Common memory allocation        */
#include "cm_inet.x"       /* Common socket library           */
#include "sct.x"           /* SCT interface defines           */
#include "hnt_asn.x"       /* HNT interface structures        */
#include "hnt.x"           /* HNT interface structures        */
#include "rut_asn.x"       /* RUT interface structures        */
#include "rut.x"           /* RUT interface structures        */
#include "lhm.x"        /* Iuh Signaling management interface */
#endif
/* sm_ex_ms_c_001.main_126: LTE eNodeB and LTE convergence layer release */
#ifdef NH
#include "lnh.x"
#endif

#ifdef PJ 
#include "lpj.x"
#endif

#ifdef YS
#include "lys.x"
#endif

#ifdef VE
/* sm_ex_ms_c_001.main_127: Updated for LTE eNodeB */ 
#include "cm_tpt.x"
#include "lve.x"
#endif

  
/* local defines */
  
/* local typedefs */
  
/* local externs */
  
/* forward references */
/* ccpu00125353: warning fix */
#ifdef WR
PUBLIC S16 smWrActvTsk (Pst *pst,/* post */ Buffer *mBuf/* message buffer */);
#endif
#ifdef RM_INTF
EXTERN S16 smRmActvTsk (Pst *pst, Buffer *mBuf);
#endif

EXTERN S16 smEuActvTsk(Pst *pst,Buffer *mBuf);

/*
 *
 *      Fun:    smInitExt
 *
 *      Desc:   Initializes external variables 
 *
 *      Ret:    ROK  - ok
 *
 *      Notes:  None
 *
        File:   sm_ex_ms.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 smInitExt
(
void
)
#else
PUBLIC S16 smInitExt()
#endif
{
   TRC2(smInitExt)

   RETVALUE(ROK);
} /* smInitExt */

   
/*
 *
 *      Fun:    smActvTsk
 *
 *      Desc:   Processes a received event 
 *
 *      Ret:    ROK - ok
 *
 *      Notes:  None
 *
        File:   sm_ex_ms.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 smActvTsk
(
Pst    *post,               /* post structure */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smActvTsk(post, mBuf)
Pst    *post;               /* post structure */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC3(smActvTsk)

   /* process event based on source entitiy */
   switch(post->srcEnt)
   {
#ifdef AP       /* async pad */
      case ENTAP:
         smApActvTsk(post, mBuf);
         break;
#endif

#ifdef IN       /* Q.930/Q.931 */
      case ENTIN:
         smInActvTsk(post, mBuf);
         break;
#endif

#ifdef AM       /* Q.93B */
      case ENTAM:
         smAmActvTsk(post, mBuf);
         break;
#endif

#ifdef AS       /* Q.SAAL */
      case ENTAS:
         smAsActvTsk(post, mBuf);
         break;
#endif

#ifdef PN       /* PNNI */
      case ENTPN:
         smPnActvTsk(post, mBuf);
         break;
#endif

#ifdef UM       /* UME */
      case ENTUM:
         smUmActvTsk(post, mBuf);
         break;
#endif

#ifdef IM       /* IME */
      case ENTIM:
         smImActvTsk(post, mBuf);
         break;
#endif

#ifdef XG       /* x.75 */
      case ENTXN:
         smXnActvTsk(post, mBuf);
         break;
#endif

#ifdef EI       /* x.25 end and intermediate system */
      case ENTXN:
         smXnActvTsk(post, mBuf);
         break;
#endif

#ifdef XE       /* x.25 end system */
      case ENTXN:
         smXnActvTsk(post, mBuf);
         break;
#endif

#ifdef XI       /* x.25 intemediate system */
      case ENTXN:
         smXnActvTsk(post, mBuf);
         break;
#endif

#ifdef XN       /* x.25/x.75 system */
      case ENTXN:
         smXnActvTsk(post, mBuf);
         break;
#endif

#ifdef BD       /* lapb and lapd */
      case ENTBD:
         smBdActvTsk(post, mBuf);
         break;
#endif

#ifdef LD       /* lapd */
      case ENTLD:
         smLdActvTsk(post, mBuf);
         break;
#endif

#ifdef LB       /* lapb */
      case ENTLB:
         smLbActvTsk(post, mBuf);
         break;
#endif

#ifdef D2       /* D2 */
      case ENTD2:
         smD2ActvTsk(post, mBuf);
         break;
#endif

#ifdef BR       /* basic frame relay */
      case ENTBR:
         smFrActvTsk(post, mBuf);
         break;
#endif

#ifdef FR       /* basic frame relay */
      case ENTFR:
         smFrActvTsk(post, mBuf);
         break;
#endif

#ifdef ER       /* extended frame relay */
      case ENTER:
         smFrActvTsk(post, mBuf);
         break;
#endif

#ifdef SC       /* scc */
      case ENTSC:
         smScActvTsk(post, mBuf);
         break;
#endif

#ifdef IS       /* isac-s */
      case ENTIS:
         smIsActvTsk(post, mBuf);
         break;
#endif

#ifdef SE       /* sec */
      case ENTSE:
         smSeActvTsk(post, mBuf);
         break;
#endif

#ifdef IX       /* x.31 */
      case ENTIX:
         smIxActvTsk(post, mBuf);
         break;
#endif

#ifdef TC       /* TCP/IP */
      case ENTTC:
         smTcActvTsk(post, mBuf);
         break;
#endif

#ifdef UD       /* UDP/IP */
      case ENTUD:
         smUdActvTsk(post, mBuf);
         break;
#endif

#ifdef MS       /* mos */
      case ENTMS:
         smMsActvTsk(post, mBuf);
         break;
#endif

#ifdef NS        /* NTSS */
      case  ENTNS:
         smNsActvTsk(post, mBuf);
         break;
#endif

#ifdef SD       /* MTP level 2 */
      case ENTSD:
         smSdActvTsk(post, mBuf);
         break;
#endif

#ifdef SI       /* ISUP */
      case ENTSI:
         smSiActvTsk(post, mBuf);
         break;
#endif

#ifdef TP       /* TUP */
      case ENTTP:
         smTpActvTsk(post, mBuf);
         break;
#endif

#ifdef SP       /* SCCP */
      case ENTSP:
         smSpActvTsk(post, mBuf);
         break;
#endif

#ifdef RA       /* RANAP */
      case ENTRA:
         smRaActvTsk(post, mBuf);
         break;
#endif

#ifdef RP       /* RANAP LDF*/
      case ENTRP:
         smRpActvTsk(post, mBuf);
         break;
#endif

#ifdef LM       /* LAPDm */
      case ENTLM:
         smLmActvTsk(post, mBuf);
         break;
#endif

#ifdef DK       /* GMM/SM LDF*/
      case ENTDK:
         smDkActvTsk(post, mBuf);
         break;
#endif

#ifdef GM       /* GMM */
      case ENTGM:
         smGmActvTsk(post, mBuf);
         break;
#endif
#ifdef NM       /* NM */
      case ENTNM:
         smGmActvTsk(post, mBuf);
         break;
#endif
#ifdef ST       /* TCAP */
      case ENTST:
         smStActvTsk(post, mBuf);
         break;
#endif

#ifdef SN       /* MTP Level 3 */
      case ENTSN:
         smSnActvTsk(post, mBuf);
         break;
#endif

#ifdef EC       /* LEC */
      case ENTEC:
         smEcActvTsk(post, mBuf);
         break;
#endif

#ifdef ES       /* LES */
      case ENTES:
         smEsActvTsk(post, mBuf);
         break;
#endif

#ifdef WD       /* MTP Level 2 Wrapper */
      case ENTWD:
         smWdActvTsk(post, mBuf);
         break;
#endif

#ifdef WN       /* MTP Level 3 Wrapper */
      case ENTWN:
         smWnActvTsk(post, mBuf);
         break;
#endif

#ifdef WI       /* ISUP Wrapper */
      case ENTWI:
         smWiActvTsk(post, mBuf);
         break;
#endif

#ifdef WU       /* TUP Wrapper */
      case ENTWU:
         smWuActvTsk(post, mBuf);
         break;
#endif

#ifdef WS       /* SCCP Wrapper */
      case ENTWS:
         smWsActvTsk(post, mBuf);
         break;
#endif

#ifdef WC       /* TCAP Wrapper */
      case ENTWC:
         smWcActvTsk(post, mBuf);
         break;
#endif

#ifdef QI       /* 68360 driver */
      case ENTQI:
         smQiActvTsk(post, mBuf);
         break;
#endif

#ifdef PQ       /* MPC860 driver */
      case ENTPQ:
         smPqActvTsk(post, mBuf);
         break;
#endif

#ifdef ME       /* Message exchange */
      case ENTME:
         smMeActvTsk(post, mBuf);
         break;
#endif

#ifdef IS       /* ISAC-S */
      case ENTIS:
         smIsActvTsk(post, mBuf);
         break;
#endif
#ifdef FM       /* ISAC-S */
      case ENTFM:
         smFmActvTsk(post, mBuf);
         break;
#endif
#ifdef RY       /* Relay */
      case ENTRY:
         smRyActvTsk(post, mBuf);
         break;
#endif
#ifdef FA       /* Fujitsu ALC */
      case ENTFA:
         smFaActvTsk(post, mBuf);
         break;
#endif
#ifdef BI       /* BISUP */
      case ENTBI:
         smBiActvTsk(post, mBuf);
         break;
#endif
#ifdef SA       /* Q.2140 */
      case ENTSA:
         smSaActvTsk(post, mBuf);
         break;
#endif
#ifdef FN       /* Q.933 */
      case ENTFN:
         smFnActvTsk(post, mBuf);
         break;
#endif
#ifdef EV       /* V5 Envelope Function */
      case ENTEV:
         smEvActvTsk(post, mBuf);
         break;
#endif
#ifdef LV       /* LAPV */
      case ENTLV:
         smLvActvTsk(post, mBuf);
         break;
#endif
#ifdef NV       /* V5.X PSTN */
      case ENTNV:
         smNvActvTsk(post, mBuf);
         break;
#endif
#ifdef CV       /* V5.X CP */
      case ENTCV:
         smCvActvTsk(post, mBuf);
         break;
#endif
#ifdef BV       /* V5.X BCC */
      case ENTBV:
         smBvActvTsk(post, mBuf);
         break;
#endif
#ifdef MV       /* V5.X System manager */
      case ENTMV:
         smMvActvTsk(post, mBuf);
         break;
#endif
#ifdef MA       /* MAP */
      case ENTMA:
         smMaActvTsk(post, mBuf);
         break;
#endif
#ifdef IA       /* map is41 */
      case ENTIA:
         smIaActvTsk(post, mBuf);
         break;
#endif
#ifdef AF       /* Frame Relay - ATM InterWorking */
      case ENTAF:
         smAfActvTsk(post, mBuf);
         break;
#endif
#ifdef PL       /* LASAR driver */
      case ENTPL:
         smPlActvTsk(post, mBuf);
         break;
#endif
#ifdef ICC       /* Call control */
      case ENTCC:
         smCcActvTsk(post, mBuf);
         break;
#endif

#ifdef LK
      case ENTLK:
         smLkActvTsk (post, mBuf);
         break;
#endif /* LK */

#ifdef IE       /* INAP */
      case ENTIE:
         smIeActvTsk(post, mBuf);
         break;
#endif

#ifdef TT       /* TCAP over TCP/IP management interface */
      case ENTTT:
         smTtActvTsk(post, mBuf);
         break;
#endif

#ifdef PA
      case ENTPA:
         smPaActvTsk(post, mBuf);
         break;
#endif

#ifdef PV
      case ENTPV:
         smPvActvTsk (post, mBuf);
         break;
#endif /* PV */

#ifdef RT       /* Route management */
      case ENTRT:
         smRtActvTsk(post, mBuf);
         break;
#endif
#ifdef AC
      case ENTAC: /* ATM Convergence */
         smAcActvTsk(post, mBuf);
         break;
#endif
#ifdef RM_INTF       /* Resource management */
      case ENTRM:
         smRmActvTsk(post, mBuf);
         break;
#endif
#ifdef NL
      case ENTNL:
         smNlActvTsk(post, mBuf);
         break;
#endif
#ifdef XM       /* Call control  Connection Manager */
      case ENTXM:
         smXmActvTsk(post, mBuf);
         break;
#endif
#ifdef SF       /* Switching Fabric management */
      case ENTSF:
         smSfActvTsk(post, mBuf);
         break;
#endif
#ifdef VF
      case ENTVF: /* VF Layer */
         smVfActvTsk(post, mBuf);
         break;
#endif
#ifdef SG
      case ENTSG: /* System Manager */
         smSgActvTsk(post, mBuf);
         break;
#endif

#ifdef VW_COMPILE
#undef SH
#endif
  
#ifdef SH
      case ENTSH: /* System Agent */
         smShActvTsk(post, mBuf);
         break;
#endif
#ifdef MR
      case ENTMR: /* Message Router */
         smMrActvTsk(post, mBuf);
         break;
#endif
#ifdef DL       /* Dummy Layer(s)  - FT/HA */
      case ENTDL:
      case ENTDL1:
      case ENTDL2:
      case ENTDL3:
      case ENTDL4:
      case ENTDL5:
         smDlActvTsk(post, mBuf);
         break;
#endif

#ifdef PR     /* MPC860SAR driver */
      case ENTPR:
         smPrActvTsk(post, mBuf);
         break;
#endif

#ifdef GN     /* Network Service */
      case ENTGN:
         smGnActvTsk(post, mBuf);
         break;
#endif

#ifdef GT     /* GTP */
      case ENTGT:
         smGtActvTsk(post, mBuf);
         break;
#endif

#ifdef GL
      case ENTGL:
         smGlActvTsk(post, mBuf);
         break;
#endif

#ifdef GG     /* BSSGP */
      case ENTGG:
         smGgActvTsk(post, mBuf);
         break;
#endif

#ifdef HC     /* H.323 */
      case ENTHC:
         smHcActvTsk(post, mBuf);
         break;
#endif

#ifdef HI     /* TUCL */
      case ENTHI:
         smHiActvTsk(post, mBuf);
         break;
#endif

#ifdef HG     /* 225 Annex G */
      case ENTHG:
         smHgActvTsk(post, mBuf);
         break;
#endif

#ifdef GS     /* SNDCP */
      case ENTGS:
         smGsActvTsk(post, mBuf);
         break;
#endif

#ifdef HR     /* RTP/RTCP */
      case ENTHR:
         smHrActvTsk(post, mBuf);
         break;
#endif

#ifdef IQ       /* Q.930/931-Q.SAAL Convergence Layer */
      case ENTIQ:
         smIqActvTsk(post, mBuf);
         break;
#endif

#ifdef MG
#ifndef DG
      case ENTMG:
         smMgActvTsk(post, mBuf);
         break;
#endif /* ifndef DG */
#endif /* MG */

#ifdef DN
      case ENTDN:
         smDnActvTsk(post, mBuf);
         break;
#endif /* DN */

#ifdef DI
      case ENTDI:
         smDiActvTsk(post, mBuf);
         break;
#endif /* DI */

#ifdef VO     /* MPC8260 driver */
      case ENTVO:
         smVoActvTsk(post, mBuf);
         break;
#endif /* VO */

#ifdef SB     /* SCTP */
      case ENTSB:
         smSbActvTsk(post, mBuf);
         break;
#endif /* SB */

#ifdef SO       /* SIP */
      case ENTSO:
         smSoActvTsk(post, mBuf);
         break;
#endif

#ifdef IT     /* M3UA */
      case ENTIT:
         smItActvTsk(post, mBuf);
         break;
#endif /* IT */

#ifdef NF     /* NIF */
      case ENTNF:
         smNfActvTsk(post, mBuf);
         break;
#endif /* NF */

#ifdef LN     /* MPLS - LDP(+CR) */
      case ENTLN:
         smLnActvTsk(post, mBuf);
         break;
#endif

#ifdef FW       /* MPLS Forwarder */
      case ENTFW:
         smFwActvTsk(post, mBuf);
         break;
#endif
 
#ifdef RL       /* MPLS - Resource Mgmt. */
      case ENTRL:
         smRlActvTsk(post, mBuf);
         break;
#endif

/* sm_ex_ms_c_001.main_111: RRC 2.0 */
#ifdef RR       /* RRC */
      case ENTRR:
         smRrActvTsk(post, mBuf);
         break;
#endif

/* sm_ex_ms_c_001.main_121 Updated for LTE-RLC release 1.1 and LTE MAC 1.1 */
#ifdef RG       /* LTE-MAC */
      case ENTRG:
         smRgActvTsk(post, mBuf);
         break;
#endif

         
#ifdef AR       /* Routing Module */
      case ENTAR:
         smArActvTsk(post, mBuf);
         break;
#endif

#ifdef AL      /* AAL2 Signaling */
      case ENTAL2:
         smAlActvTsk(post, mBuf);
         break;
#endif /* AL */

#ifdef DP
      case ENTDP:
         smDpActvTsk(post, mBuf);
         break;
#endif /* DP */

/* sm_ex_ms_c_001.main_109: LDF-SUA 1.1 REL */
#ifdef AH
      case ENTAH:
         smAhActvTsk(post, mBuf);
         break;
#endif /* AH */

#ifdef DT /* TCAP - LDF */
      case ENTDT:
         smDtActvTsk(post, mBuf);
         break;
#endif /* DT */

#ifdef ID /* IUA */
      case ENTID:
#ifdef SM
         smIdActvTsk(post, mBuf);
#endif
         break;
#endif /* ID */

#ifdef ND /* IUA-NIF */
      case ENTND:
#ifdef LD
         smNdActvTsk(post, mBuf);
#endif
         break;
#endif /* ND */

#ifdef SU /* SUA */
      case ENTSU:
         smSuActvTsk(post, mBuf);
         break;
#endif  /* SUA */

#ifdef NP /* SUA NIF */
      case ENTNP:
         smNpActvTsk(pst, mBuf);
         break;
#endif  /* SUA - NIF */

#ifdef QC       /* CAP */
      case ENTQC:
         smQcActvTsk(post, mBuf);
         break;
#endif /* QC */

#ifdef GA     /* BSSAP+ */
      case ENTGA:
         smGaActvTsk(post, mBuf);
         break;
#endif

#ifdef MW       /* M2UA */
      case ENTMW:
         smMwActvTsk(post, mBuf);
         break;
#endif /* M2UA */

#ifdef NW       /* M2UA NIF */
      case ENTNW:
         smNwActvTsk(post, mBuf);
         break;
#endif /* M2UA NIF */

#ifdef MX       /* M2PA */
      case ENTMX:
         smMxActvTsk(post, mBuf);
         break;
#endif

#ifdef MK       /* 3GPP MAC */
      case ENTMK:
         smMkActvTsk(post, mBuf);
         break;
#endif

#ifdef MD       /* MAC-HS */
      case ENTHS:
         smMdActvTsk(post, mBuf);
         break;
#endif

#ifdef IB       /* 3GPP NBAP */
      case ENTIB:
         smIbActvTsk(post, mBuf);
         break;
#endif  /* NBAP */

#ifdef DG
      case ENTDG:
         smDgActvTsk(post, mBuf);
         break;
#endif /* DG */


#ifdef RN
      case ENTRN:
         smRnActvTsk(post, mBuf);
         break;
#endif /* RN */

#ifdef DV
      case ENTDV:
         smDvActvTsk(post, mBuf);
         break;
#endif /* DV */

#ifdef FP
      case ENTFP:
         smFpActvTsk(post, mBuf);
         break;
#endif /* FP */

#ifdef VU
      case ENTVU:
         smVuActvTsk(post, mBuf);
         break;
#endif /* VU */

#ifdef MZ /*M1UA */
      case ENTMZ:
         smMzActvTsk(post, mBuf);
         break;
#endif /* MZ */

#ifdef MC /*M1UA */
      case ENTMC:
         smMcActvTsk(post, mBuf);
         break;
#endif /* MC */
/* sm_ex_ms_c_001.main_128: LDF-RANAP removed duplicate case ENTRP */

/* sm_ex_ms_c_001.main_108: Addition */
#ifdef AQ       /* Diameter */
      case ENTAQ:
         smAqActvTsk(post, mBuf);
         break;
#endif

/*-- sm_ex_ms_c_001.main_114 : for IuUP --*/
#ifdef LX
      case ENTLX:
         smLxActvTsk (post, mBuf);
         break;
#endif
/* sm_ex_ms_c_001.main_118 Updated for S1AP release 1.1 */
#ifdef SZ       /* S1AP */
      case ENTSZ:
         smSzActvTsk(post, mBuf);
         break;
#endif
/*  Updated for X2AP release 1.1 */
#ifdef CZ       /* S1AP */
      case ENTCZ:
          smCzActvTsk(post, mBuf);
         break;
#endif

/* sm_ex_ms_c_001.main_119: Addition */
#ifdef EG       /* EGTP */
      case ENTEG:
         smEgActvTsk(post, mBuf);
         break;
#endif

/* sm_ex_ms_c_001.main_120 Updated for LTE-RRC release 1.1 */
#ifdef NH       /* LTE-RRC */
      case ENTNH:
         smNhActvTsk(post, mBuf);
         break;
#endif

/* sm_ex_ms_c_001.main_121 Updated for LTE-RLC release 1.1 and LTE MAC 1.1 */
#ifdef KW
      case ENTKW:
         smKwActvTsk(post, mBuf);
         break;

#ifdef KW_PDCP
      case ENTPJ:
         smKwActvTsk(post, mBuf);
         break;
#endif /* KW_PDCP */

#endif /* KW */
#ifdef PJ
      case ENTPJ:
         smPjActvTsk(post, mBuf);
         break;
#endif /* PJ  */

#ifdef HM
      case ENTHM:
         smHmActvTsk(post, mBuf);
         break;
#endif /* HM  */

/* sm_ex_ms_c_001.main_126: LTE eNodeB and LTE convergence layer release */
#ifdef VE
      case ENTVE:
         smVeActvTsk(post, mBuf);
         break;
#endif

#ifdef WR
      case ENTVE:
      case ENTWR:
         smWrActvTsk(post, mBuf);
         break;
#endif /* WR */

      case ENTEU:
         smEuActvTsk(post, mBuf);
         break;

#ifdef YS
      case ENTTF:
      case ENTYS:
         smYsActvTsk(post, mBuf);
         break;

#endif /* YS */
#ifdef VE_CUST_CHNG
#ifdef VE_DG_OAM
      case ENTSM:
         {
          smSockActvTsk(post, mBuf);
         }
         break;
#endif
#endif /* VE_CUST_CHNG */
#ifdef WR_DG_OAM
      case ENTOAMSOCK:
      case ENTOAMSTAT:
         smSockActvTsk(post, mBuf);
         break;
#endif
      default:
         /* sm_ex_ms_c_001.main_128: Memory leak fix, 
            moved SPutMsg outside of #if statement */
         (Void) SPutMsg(mBuf);
/* sm_ex_ms_c_001.main_116 removed printfs  */
#if (ERRCLASS & ERRCLS_DEBUG)
         SLogError(post->dstEnt, post->dstInst, post->dstProcId, __FILE__,
                   __LINE__, (ErrCls) ERRCLS_DEBUG, (ErrVal)ESM001, 
                   (ErrVal)post->srcEnt, "smActvTsk () Failed");
#endif
         break;
   }

   SExitTsk();

   RETVALUE(ROK);
} /* end of smActvTsk */
/* sm_ex_ms_c_001.main_107 */
/* sm_ex_ms_c_001.main_117 Removed smRractvTsk function definition */

  
/********************************************************************30**
  
         End of file:     sm_ex_ms.c@@/main/132 - Wed Nov 30 17:39:51 2011
  
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
1.1          ---  rg    1. initial release

1.2          ---  ak    1. added TU (TCAP User -- really a dummy layer)

1.3          ---  rg    1. added include files and entry point for LEC.

1.4          ---  mc    1. changed include files for BD, LD, LB, BR, ER.

1.5          ---  rg    1. added include files and entry point for LES.
             ---  ak    2. added PN (ATM-PNNI)

1.6          ---  rg    1. combined LES and BUS.

1.7          ---  mc    1. changed include files and entry points for XG, EI,
                           XE, and XI.
             ---  mc    2. replace ENTXG, ENTEI, ENTXE, and ENTXI with ENTXN.

1.8          ---  mc    1. added ss7 stack wrapper (WD, WN, WI, WU, WS, and WC)
             ---  fmg   2. added QI

1.9          ---  fmg   1. added ME

1.10         ---  jrl   1. added IS

1.11         ---  fmg   1. added FM
             ---  vk    2. added FA

1.12         ---  ssa   1. renamed LES/BUS to LEServices.
             ---  bn    2. added BI for B-ISUP
             ---  mc    3. added Q.2140 (SA)

1.13         ---  bn    1. added #include "lbi.h".

1.14         ---  mc    1. added break in case ENTSA in smActvTsk.

1.15         ---  krp   1. Modified the include and function call for 
                           Basic and Extended frame relay.
1.16         ---  krp   1. Added include and function call for 
                           Frame Relay Network Layer - Q.933.

1.17         ---  mc    1. added LAPV and V5.1 PSTN

1.18         ---  mc    1. replaced SError with SLogError.

1.19         ---  amit  1. added case ENTMA in smActvTsk
             ---  mc    2. added V5 Envelope Function    
             ---  mc    3. change copyright header

1.20         ---  ada   1. add FR section

1.21         ---  sg    1. Added ENTAF to smActvTsk

1.22         ---  ks    1. added support for all management primitivies

1.23         ---  kr    1. added PMC-Sierra LASAR (PL) section

1.24         ---  fmg   1. removed '\' SLogError in smActvTsk

1.25         ---  aa    1. Added cm_ss[hx] under SM_SS7 flag
             ---  aa    2. Removed the TCAP user section
             ---  ada   3. defined laf.h and laf.x
             ---  bn    4. added CV and MV suuport.

1.26         ---  aa    1. Removed the  TU Section form smActvTsk function
*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.27         ---      ak   1. added IME
 
1.28         ---      sb   1. added V5.2 BCC support.

1.29         ---      sb   1. added V5.2 LCP support.
             ---      kvm  2. added PLOA (PA)
             ---      mg   3. added V5 Protection Protocol (PV).

1.30         ---      sg   1. added MAP IS41 (IA)

1.31         ---      mb   1. Integrated SS7 release.

1.32         ---      kvm  1. included cm_atm.[hx] within SM_ATM 
                             compile flag 

1.33         ---      pm   1. included  cm_atm.[hx] files within SA flag.

1.34         ---      apr  1. added Entities RT and AC
             ---      bsr  1. included cm_isdn.[hx] files within FN flag

1.35         ---      kr   1. added ENTXN section

1.36         ---      skr  1. added PQ section

1.37         ---      mg   1. Changed copyright header date.

1.38         ---      ag   1. Added code for NTSS
             ---      hrg  2. Added sections for INAP.

1.39         ---      ao   1. Added Resource Manager(RM), Router(RT),
                              and switching Fabric(SF)
             ---      mp   1. Added header files and activation task
                              function for V5 layer 3. 
1.40         ---      rs   1. Added include file for interworking call
                              control
1.41         ---      apr  1. Added System Manager(SG), System Agent(SH)
                              and Message Router(MR)
             ---      hrg  2. Added sections for TCAP over TCP/IP (TT).

1.42         ---      rs   1. Changed #ifdef CC to #ifdef ICC.

1.43         ---      nct  1. Added PR (MPC860SAR driver).

1.44         ---      ao   1. Added includes for AC (AC driver)

1.45         ---      dvs  1. Sync SCCS rev

1.46         ---      ark  1. Added includes for GPRS Network Service

1.47         ---      aa   1. Added includes for GPRS Tunneling Protocol

1.48         ---      sg   1. Added includes for GPRS Logical Link Control

1.49         ---      mb   1. Additions for H.323 ( HC and HI )

1.50         ---      nj   1. Made changes for BSSGP

1.51         ---      nj   1. Corrected warnings for cm_gprs

1.52         ---      pm   1. Additions for SNDCP (GPRS).

1.53         ---      kp   1. Additions for RTP/RTCP.

1.54         ---      sam  1. Added include for Q.930/931-Q.SAAL
                              Convergence Layer
1.55         ---      mg   1. Modifications for ICC 1.4 release

1.56         ---      rs   1. Modifications for GTP 1.2 release

1.57         ---      rs   1. Modifications for ICC 1.5 release
1.58         ---      bbk  1. Modifications for MGCP Release
1.59         ---      bbk  1. Fixed C++ compilation warnings
/main/60        ---      asa  1. Annex E additions for H.323 Control.
/main/61        ---      ssk  1. Modifications for LDF-MTP3 release. 
/main/63     ---      mrw  1. Added VO (MPC8260 driver)
/main/64     ---       sb  1. Modification done for SCTP, M3UA and NIF layer.
/main/65     ---      sa   1. Modification for AAL2 Signaling
                           2. Added sections for MPLS-LDP(+CR) (LN), 
                              MPLS forwarder (FW), MPLS resource manager (RL)
                              and routing module (AR).
/main/66     ---      bsr  1. Added section H.225 Annex G
/main/66     ---      vb   1. Added section for LDF-SCCP
/main/67     ---      ssk  1. Modifications for LDF-MTP3
                              cm_zndn includes are changed to cmzndn
                              and cmzndnlb includes
                              cm_pftha includes are removed. 
/main/68     ---      ash  1. Changes for SG, SH and MR                              
/main/69     ---      ssk  1. Changes for DT                                         
/main/70     ---      hl   2. Added section for IUA and IUA-NIF
/main/71     ---      dw   1. For adding cm_sdp.[hx] and mgt.[hx] 
                              as dependencies. 
/main/72     ---      sb   1. Files cm_dns.[hx] added for SCTP.
             /main/73                 ms   1. Added section for SIP
/main/74     ---      nt   1. Added section for SUA and SUA NIF.
/main/75     ---      dw   1. Added section for RANAP
/main/76     ---      as   1. Added sectoin for CAP. 
/main/77     ---      srg  1. Added section for BSSAP+
/main/78     ---    lb   1. Added section for H323-psf 
/main/79     ---      nt   1. sht.[hx] added for M3UA.
                           2. smit_err.h added for M3UA.
/main/80     ---       hl  1. Added M2UA and its NIF   
/main/81     ---      tz   1. Added sections for LDF-ISUP
/main/82     ---      sa   1. Added section for 3GPP-MAC.
/main/83     ---      vr   1. Added section for 3GPP-RLC.
/main/84     ---      ssp  1. Added section for 3GPP-NBAP.
/main/85     ---      sm   1. Added section for GMM/SM
/main/86     ---      rg   1. Modifications for GCP 1.3 release
/main/87     ---      hl   1. Updated for IUA version 1.2
/main/88     ---     ssk   1. Added section for RNSAP 
/main/89     ---      rs   1. Added section for LDF-M3UA 
/main/91     ---     ps    1. FP & VU changes for rel 1.1
/main/92     ---     rk    1. M1UA release 1.1
/main/93     ---     hr    1. M2PA changes
 /main/94    ---     bn    1. DPNSS/DASS2 changes
/main/95     ---      st   1. Update for MAP Release 2.3
/main/96     ---     rbabu 1. Updated for NBAP Software Release 1.2
/main/97     ---      vsr  1. Updated for LDF-RANAP 1.1 release.
/main/98     ---      vsr  1. Updated for PSF-RANAP 1.2 release.
/main/100    ---      sal  1. Created for Release of 2.1(RFC 3868 Support)
/main/101    ---       sm  1. Protected cm_inet.h inclusion in
                              SUAP_IPOPT flag.
/main/103    ---      gs   1. REcovered last correct version during MAC 1.3 RTR
/main/104    ---       kkj 1. GMM 2.1 release
/main/105    ---      yk   1. GMM/SM LDF 1.1 Release
/main/106    ---      ad   1. Updated for Release SIP 2.2 Beta
/main/107    ---      st   1. Updated for LAPDm
/main/107+    sm_ex_ms_c_001.main_107 gs   1. Updated for MAC-HS Release 1.1
/main/108    ---      gs   1. Updated for MAC-HS Release 1.1
sm_ex_ms_c_001.main_108 dv 1. Updated for Diameter Release 1.2
/main/110    ---      sm_ex_ms_c_001.main_109 rce  1. Updated for LDF SUA 1.1 Release
/main/111    ---    sm_ex_ms_c_001.main_110  rbabu 1. Modified for PDCP Software release 1.1
/main/112    ---    sm_ex_ms_c_001.main_111 rbhat   1.RRC 2.0 Release
/main/113    ---    sm_ex_ms_c_001.main_112 pc   1.Diameter SDK Release,included                                                   DNS in AQ.
/main/114    ---      rer  1. RRC 2.1 support.
/main/115    ---    sm_ex_ms_c_001.main_114 ss   1. Added code for IuUP 1.1
/main/116    ---    sm_ex_ms_c_001.main_115 ds   1. Correcting the errorneous
                                                    value in printf
                                                    rrActvTsk-default case.
/main/117    ---    sm_ex_ms_c_001.main_116 ds   1. Replaced printfs with
                                                    SLogError.
/main/118    ---    sm_ex_ms_c_001.main_117 ds   1. Removed smRractvTsk function
                                                    definition.
/main/119    ---    sm_ex_ms_c_001.main_118 hsingh   1.Updated for S1AP release 1.1 
/main/120    ---   sm_ex_ms_c_001.main_119 pc 1. Additions for eGTP protocol.
/main/121    ---   sm_ex_ms_c_001.main_120 vk 1. Updated for Release of LTE RRC 1.1.
/main/121    ---   sm_ex_ms_c_001.main_121 nm 1. Updated for Release of LTE RLC 1.1 
                                                 and LTE MAC 1.1
/main/121    ---   sm_ex_ms_c_001.main_122 nm 1. Updated for Release of LTE RLC 1.1 
/main/125    ---   sm_ex_ms_c_001.main_123 mm 1. Updated for Release of LTE X2AP 1.1 
/main/127          sm_ex_ms_c_001.main_126 pkaX 1. Updated for LTE eNodeB and LTE 
                                                   convergence layer.
/main/128          sm_ex_ms_c_001.main_127 sv 1. Updated for LTE eNodeB.
/main/129    ---      sm_ex_ms_c_001.main_128 rk 1. Memory leak fix in smActvTsk.
                                              2  Updated for RANAP-LDF release 1.1 
/main/130    ---      sm_ex_ms_c_001.main_129    gj 1. Updated for Release of LTE MAC 3.1
/main/131    ---      sm_ex_ms_c_001.main_130   pka   1. Added SHT file header include as lsz.x
                                               uses the SHT releated structures
/main/132    ----     sm_ex_ms_c_001.main_131   jj 1. Updated for Psf-Diameter 1.1
                                                     release
*********************************************************************91*/
