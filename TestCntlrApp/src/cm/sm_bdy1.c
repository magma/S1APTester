
/********************************************************************20**
  
     Name:     stack manager - body 1
  
     Type:     C source file
  
     Desc:     C source code for stack manager supplied by TRILLIUM.

               Part 1: Interface primitives.

     File:     sm_bdy1.c
  
     Sid:      sm_bdy1.c@@/main/106 - Fri Mar 26 22:34:02 2010
  
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
*     1000049     Frame Relay Network - Q.933
*     1000063     Service Specific Coordination Funtion - Q.2140
*     1000064     Broadband ISUP - B-ISUP
*     1000074     Data Link Layer - LAPV5-DL 
*     1000075     V5.1 PSTN Network Layer 
*     1000093     INAP
*     1000096     V5.x Protection Protocol Network Layer 
*     1000128     X.25/X.75 System
*     1000135     Windows NT -- Multithreaded system services
*     1000139     MPC860SAR driver
*     1000156     SIP Session Initiation Protocol
*     1000163     MPC8260 driver
*     1000241     3GPP-MAC
*     1000204     3GPP-RLC
*     1000243     3GPP-NBAP
*     1000342     Data Link Layer - D2
*     1000347     LAPDm 
*     1000349     Diameter
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
#include "cm_atm.h"
#endif

#ifdef SM_SS7
/* sm_bdy1_c_001.main_86 - Addition - protected cm_inet.h inclusion
 *                         in SUAP_IPOPT flag */
#ifdef SUAP_IPOPT
#include "cm_inet.h"
#endif
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
#include "lac.h"           /* AC management interface */
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
#ifdef AF       
#include "laf.h"           /* basic af layer management interface */
#endif 
#ifdef FR       
#include "frd.h"           /* frame data link layer */
#include "lfr.h"           /* basic frame relay management interface */
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
#include "cm_umts.h"       /* sm_bdy1_c_001.main_99 */
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
#ifdef TT
#include "cm_inet.h"       /* common sockets */
#include "ltt.h"           /* TCAP over TCP/IP management interface */
#endif
#ifdef ST       
#include "lst.h"           /* TCAP management interface */
#endif
#ifdef IA       
#include "lia.h"           /* MAP IS41 management interface */
#endif
#ifdef IE       
#include "lie.h"           /* INAP management interface */
#endif
#ifdef SN       
#include "lsn.h"           /* MTP Level 3 management interface */
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
#include "cm_ldrvr.h"      /* Common management i/f */
#include "lpq.h"           /* QI management interface */
#endif
#ifdef ME       
#include "lme.h"           /* ME management interface */
#endif
#ifdef IS       
#include "lis.h"           /* ISAC-S  management interface */
#endif
#ifdef SA       
#include "cm_atm.h"        /* common atm */
#include "lsa.h"           /* Q.2140 management interface */
#endif
#ifdef BI
#include "lbi.h"           /* B_ISUP management interface */
#endif
#ifdef RY
#include "lry.h"           /* Relay management interface */
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
#include "lnv.h"           /* v5.X PSTN management interface */
#endif
#ifdef VF
#include "lvf.h"           /* VF Layer Management Interface */
#endif
#ifdef CV
#include "lcv.h"           /* v5.X Control Protocol management interface */
#endif
#ifdef BV
#include "lbv.h"           /* v5.1 BCC management interface */
#endif
#ifdef MV
#include "lmv.h"           /* v5.X System Manager management interface */
#endif
#ifdef ICC
#include "cm_atm.h"        /* common atm */
#include "cm_cc.h"         /* Common call control */
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
#include "llk.h"           /* V5.2 Link Control Protocol. */
#endif /* LK */
   
#ifdef PV
#include "lpv.h"           /* V5.2 Protection Protocol management interface. */
#endif /* PV */

#ifdef PA
#include "lpa.h"           /* PLOA - Protocol Layers Over ATM */
#endif

#ifdef MC                  /* mac over sockets */
#include "lmc.h"
#endif
  
#ifdef XN
#include "lxn.h"           /* X.25/X.75 system */
#endif

#ifdef BW
#include "cm_atm.h"        /* common atm */
#include "cm_cc.h"         /* Common call control */
#include "lbw.h"           /* BISUP PSIF */
#endif
 
#ifdef IW
#include "cm_atm.h"        /* common atm */
#include "cm_cc.h"         /* Common call control */
#include "liw.h"           /* ISUP PSIF */
#endif
 
#ifdef QW
#include "cm_atm.h"        /* common atm */
#include "cm_cc.h"         /* Common call control */
#include "lqw.h"           /* ISDN PSIF */
#endif

#ifdef AW
#include "cm_cc.h"         /* Common call control */
#include "law.h"           /* Q.93B PSIF */
#endif

#ifdef RA
#include "lra.h"           /* resource manager interface */
#endif

#ifdef GM
#include "cm_gprs.h"        
#include "lgm.h"           /* resource manager interface */
#endif

#ifdef RT
#include "cm_atm.h"        /* common atm */
#include "cm_cc.h"         /* Common call control */
#include "lrt.h"           /* Router */
#endif
 
#if 0
#ifdef RM
#include "cm_atm.h"        /* common atm */
#include "cm_cc.h"         /* Common call control */
#include "rm.h"            /* common Resource Manager layer */
#ifdef PNNI_ROUTING_ENABLED
#include "lpn.h"           /* common file for PNNI */
#endif /* PNNI_ROUTING_ENABLED */
#include "lrm.h"           /* Resource Manager */
#endif
#endif

#ifdef XM
#include "lxm.h"           /* Connection Manager */
#endif
 
#ifdef SF
#include "cm_atm.h"        /* common atm */
#include "cm_cc.h"         /* Common call control */
#include "lsf.h"           /* Switching Fabric Manager */
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
#include "cm_gprs.h"
#include "lgn.h"           /* GPRS Network Service */
#endif

#ifdef GT       
#include "cm_gprs.h"
#include "cm_inet.h"
#include "cm_tpt.h"         /* common transport */
#include "lgt.h"           /* GPRS Tunneling Protocol */
#endif

#ifdef GL
#include "cm_gprs.h"
#include "lgl.h"           /* GPRS Logical Link Control (LLC) */
#endif

#ifdef GG
#include "cm_gprs.h"
#include "lgg.h"           /* BSS GPRS Protocol (BSSGP) */
#endif

#ifdef HC
#include "cm_mblk.h"        /* memory management */
#include "cm_tkns.h"        /* common tokens */
#include "cm_inet.h"        /* common sockets */
#include "cm32x.h"          /* common H.323 */
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
#include "lhi.h"            /* TUCL management defines */
#endif

#ifdef HG
#include "cm_mblk.h"        /* memory management */
#include "cm_tkns.h"        /* common tokens */
#include "cm_inet.h"        /* common sockets */
#include "cm32x.h"          /* common H.323 */
#include "cm_tpt.h"         /* common transport */
#include "lhgt.h"
#include "lhg.h"            /* H.323 */
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

#ifdef IQ
#include "cm_atm.h"        /* common atm */
#include "liq.h"           /* Q.930/931-Q.SAAL Convergence Layer management
                              interface */
#endif /* IQ */


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
#include "sct.h"           /* SCT Interface Specific */
#include "lit.h"           /* M3UA LM */
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
#include "cm_hash.h"
#include "cm_llist.h"
#include "cm_rdx.h"
#include "cm_ptree.h"
#include "cm_atm.h"
#include "lal.h"          /* AAL2 Management definitions */
#endif /* AL */            

#ifdef DP
#include "cm_ftha.h"        /* common to DFT/HA */
#include "spt.h"            /* spt interface */
#include "cmzpdp.h"         /* common to PSF and LDF SCCP */
#include "ldp.h"            /* LDF-SCCP layer management */
#endif /* DP */


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

#ifdef SU                  /* SUA */
#include "cm_tpt.h"
#include "spt.h"
#include "sct.h"
#include "cm_hash.h"
#include "cm_spgtt.h"
#include "lsu.h"
#endif

#ifdef NP                  /* SUA - NIF */
#include "lnp.h"
#endif
#ifdef QC       
#include "lqc.h"           /* CAP management interface */
#endif

#ifdef GA
#include "cm_gprs.h"
#include "lga.h"           /* BSS Application Part Plus (BSSAP+) */
#endif

#ifdef MW                  /* SIGTRAN-M2UA */
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

#ifdef MX                  /* SIGTRAN-M2PA */
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
#include "lmd.h"           /* 3G MAC HS management interface */
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

/* sm_bdy1_c_001.main_100 RRC 2.0 */
#ifdef RR
#include "lrr.h"           /* 3G RRC management interface */
#endif

/* sm_bdy1_c_001.main_103 LTE-RRC 1.1 */
#ifdef NH
#include "lnh.h"           /* LTE  RRC management interface */
#endif

/* sm_bdy1_c_001.main_104 LTE RLC 1.1 and LTE MAC 1.1 */
#ifdef RG
#include "cm_lte.h"
#include "lrg.h"           /* LTE MAC management interface */
#endif

#ifdef RN
#include "lrn.h"           /* RNSAP management interface */
#endif

#ifdef FP
#include "lfp.h"           /* FP management interface */
#endif

#ifdef LM
#include "llm.h"          /* LM management interface */
#endif

#ifdef VU
#include "lvu.h"           /* VU management interface */
#endif

#ifdef DV
#include "cm_hash.h"        /* common to Hashing */
#include "cm_ftha.h"        /* common to DFT/HA */
#include "cmzvdv.h"         /* common to PSF and LDF-M3UA */
#include "cmzvdvlb.h"       /* common to PSF and LDF-M3UA */
#include "ldv.h"            /* LDF-M3UA layer management */
#endif /* DV */

/* sm_bdy1_c_001.main_98: LDF-SUA 1.1 REL */
#ifdef AH
#include "cm_hash.h"        /* common to Hashing */
#include "cm_ftha.h"        /* common to DFT/HA */
#include "cm_ss7.h"         /* common to SS7 */
#include "spt.h"            /* SPT interface */
#include "cmaeah.h"         /* common to PSF and LDF-SUA */
#include "lah.h"            /* LDF-SUA layer management */
#endif /* AH */

#ifdef RP
#include "cm_ftha.h"        /* common to DFT/HA */
#include "cmzarp.h"         /* common to PSF and LDF-RANAP */
#include "lrp.h"            /* LDF-RANAP layer management */
#endif

/* sm_bdy1_c_001.main_97: Addition for Diameter */
/* sm_bdy1_c_001.main_102: Addition of cm_dns.[hx] */
#ifdef AQ                  /* Diameter */
#include "cm_tpt.h"        /* common transport */
#include "cm_dns.h"        /* Transport address specific */
#include "cm_tkns.h"       /* common tokens */
#include "cm_mblk.h"       /* common memory allocation */
#include "cm_inet.h"       /* common memory allocation */
#include "cm_tpt.h"       /* common memory allocation */
#include "cm_inet.h"       /* common memory allocation */
#include "cm_llist.h"       /* common memory allocation */
#include "cm_hash.h"       /* common memory allocation */
#include "cm_tpt.h"       /* common memory allocation */
#include "cm5.h"       /* common memory allocation */
#include "aqu.h"           /* Diameter Upper Interface */
#include "sct.h"           /* SCT interface defines           */
#include "laq.h"
#include "aq_util.h"
#include "aq.h"
#endif

/* sm_bdy1_c_001.main_104 LTE RLC 1.1 and LTE MAC 1.1 */
#ifdef KW                  /* LTE RLC */
#include "cm_lte.h"
#include "lkw.h"
#endif /* KW */

/* sm_bdy1_c_001.main_105: Added LTE eNodeB and LTE convergence layer */
#ifdef VE
#include "cm_tpt.h"
#include "lve.h"
#endif

#ifdef YS
#include "lys.h"
#endif

/* header/extern include files (.x) */
  
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */

#ifdef SM_ATM
#include "cm_atm.x"
#endif

#ifdef SM_SS7
/* sm_bdy1_c_001.main_86 - Addition - protected cm_inet.h inclusion
 *                         in SUAP_IPOPT flag */
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
#include "lac.x"           /* AC management interface */
#endif
#ifdef PN       
#include "lpn.x"           /* PNNI management interface */
#endif
#ifdef IM       
#include "cm_snmp.x"       /* common snmp encode/decode library */
#include "lim.x"           /* IME management interface */
#endif
#ifdef UM       
#include "lum.x"           /* UME management interface */
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
#ifdef AF       
#include "laf.x"           /* basic af layer management interface */
#endif /* AF */
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
#include "cm_umts.x"       /* sm_bdy1_c_001.main_99 */
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
#include "lra.x"            /* RANAP management interface */
#endif /* RA */
#ifdef GM
#include "cm_gprs.x"           
#include "lgm.x"            /* GMM management interface */
#endif /* GM */
#ifdef TT
#include "cm_inet.x"       /* common sockets */
#include "ltt.x"           /* TCAP over TCP/IP management interface */
#endif
#ifdef ST       
#include "lst.x"           /* TCAP management interface */
#endif
#ifdef IA       
#include "lia.x"           /* MAP IS41 management interface */
#endif
#ifdef IE       
#include "lie.x"           /* INAP management interface */
#endif
#ifdef SN       
#include "lsn.x"           /* MTP Level 3 management interface */
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
#include "cm_ldrvr.x"      /* Common management i/f */
#include "lpq.x"           /* QI management interface */
#endif
#ifdef ME       
#include "lme.x"           /* ME management interface */
#endif
#ifdef IS       
#include "lis.x"           /* ISAC-S management interface */
#endif
#ifdef SA       
#include "cm_atm.x"        /* common atm */
#include "lsa.x"           /* Q.2140 management interface */
#endif
#ifdef FM       
#include "lfm.x"           /* FM management interface */
#endif
#ifdef BI       
#include "lbi.x"           /* BISUP management interface */
#endif
#ifdef RY       
#include "lry.x"           /* Relay management interface */
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
#include "lnv.x"           /* v5.X PSTN management interface */
#endif
#ifdef VF
#include "lvf.x"           /* VF Layer Management Interface */
#endif 
#ifdef CV
#include "lcv.x"           /* v5.X Control Protocol management interface */
#ifdef BV
#include "bvt.x"           
#include "lbv.x"           /* v5.1 BCC management interface */
#endif

#endif
#ifdef MV
#include "lmv.x"           /* v5.X System Manager management interface */
#endif
#ifdef ICC
#include "cm_atm.x"        /* common atm */
#include "cm_cc.x"         /* Common call control */
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
#ifdef MC                  /* mac over sockets */
#include "lmc.x"
#endif

#ifdef LK
#include "llk.x"           /* V5.2 LCP management interface. */
#endif /* LK */

#ifdef PV
#include "lpv.x"           /* V5.2 Protection Protocol management interface. */
#endif /* PV */

#ifdef PA
#include "lpa.x"           /* PLOA - Protocol Layers Over ATM */
#endif

#ifdef XN
#include "lxn.x"           /* X.25/X.75 system */
#endif

#ifdef BW
#include "cm_atm.x"        /* common atm */
#include "cm_cc.x"         /* Common call control */
#include "lbw.x"           /* BISUP PSIF */
#endif
 
#ifdef IW
#include "cm_atm.x"        /* common atm */
#include "cm_cc.x"         /* Common call control */
#include "liw.x"           /* ISUP PSIF */
#endif
 
#ifdef QW
#include "cm_atm.x"        /* common atm */
#include "cm_cc.x"         /* Common call control */
#include "lqw.x"           /* ISDN PSIF */
#endif

#ifdef AW
#include "cm_cc.x"         /* Common call control */
#include "law.x"           /* Q.93B PSIF */
#endif

#ifdef RT
#include "cm_atm.x"        /* common atm */
#include "cm_cc.x"         /* Common call control */
#include "lrt.x"           /* Router */
#endif
 
#if 0
#ifdef RM
#include "cm_atm.x"        /* common atm */
#include "cm_cc.x"         /* Common call control */
#ifdef PNNI_ROUTING_ENABLED
#include "lpn.x"           /* PNNI defines */
#endif /* PNNI_ROUTING_ENABLED */
#include "lrm.x"           /* Resource Manager */
#endif
#endif

#ifdef NL
#include "lnl.h"
#include "lnl.x"
#endif

#ifdef XM
#include "lxm.x"           /* Connection Manager */
#endif
 
#ifdef SF
#include "cm_atm.x"        /* common atm */
#include "cm_cc.x"         /* Common call control */
#include "lsf.x"           /* Switching Fabric Manager */
#endif

#ifdef VW_COMPILE
#undef SH
#endif

#ifdef SH
#ifdef TDS_CORE2
#include "cm_ftha.x"       /* Common - FT/HA */
#endif /* TDS_CORE2 */    
#include "lsh.x"           /* System Agent */
#endif

#ifdef MR
#ifdef TDS_CORE2
#include "cm_ftha.x"       /* Common - FT/HA */
#endif /* TDS_CORE2 */    
#include "lmr.x"           /* Message Router */
#endif

#ifdef SG
#ifdef TDS_CORE2
#include "cm_ftha.x"       /* Common - FT/HA */
#endif /* TDS_CORE2 */    
#include "lsh.x"           /* System Agent */
#include "lmr.x"           /* Message Router */
#include "lsg.x"           /* System Manager */
#endif

#ifdef PR
#include "cm_atm.x"
#include "aal.x"
#include "mpc860sr.x"
#include "lpr.x"           /* MPC860SAR driver */
#endif

#ifdef GN 
#include "cm_gprs.x"      
#include "lgn.x"           /* GPRS Network Service */
#endif

#ifdef GT       
#include "cm_gprs.x"
#include "cm_inet.x"
#include "cm_tpt.x"         /* common transport */
#include "lgt.x"           /* GPRS Tunneling Protocol */
#endif

#ifdef GL
#include "cm_gprs.x"
#include "lgl.x"          /* GPRS Logical Link Control (LLC) */
#endif

#ifdef GG
#include "cm_gprs.x"
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
#ifdef H323_ANXE
#include "cm5.x"            /* Timer Library */
#include "cm_hash.x"        /* Hash List Library */ 
#include "cm_llist.x"       /* Link List library */
#include "cm_nxe.x"         /* Annex E header file */
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
#include "lhg.x"            /* H.323 */
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

#ifdef IQ
#include "cm_atm.x"        /* common atm */
#include "liq.x"           /* Q.930/931-Q.SAAL Convergence Layer management
                              interface */
#endif /* IQ */


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

#ifdef SO                  /* SIP */
#include "cm_tpt.x"        /* common transport */
#include "cm_tkns.x"       /* common tokens */
#include "cm_sdp.x"        /* common SDP */
#include "cm_mblk.x"       /* common memory allocation */
#include "sot.x"
#include "sct.x"           /* SCT interface defines           */
#include "lso.x"
#endif

#ifdef IT
#include "cm_tpt.x"        /* Transport address specific */
#include "sct.x"           /* SCT Interface Specific */
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
#include "cm_hash.x"
#include "cm_llist.x"
#include "cm_rdx.x"
#include "cm_ptree.x"
#include "cm_atm.x"
#include "cm_inet.x"
#include "cm_ss7.x"
#include "cm_aal2.x"
#include "lal.x"           /* AAL2 management typedefs */
#endif /* AL */

#ifdef DP
#include "cm_ftha.x"        /* common to DFT/HA */
#include "spt.x"            /* spt interface */
#include "cmzpdp.x"         /* common to PSF and LDF SCCP */
#include "ldp.x"            /* LDF-SCCP layer management */
#endif /* DP */

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
#include "cm_tpt.x"
#include "spt.x"
#include "sct.x"
#include "cm_hash.x"
#include "cm_spgtt.x"
#include "lsu.x"
#endif

#ifdef NP                  /* SUA - NIF */
#include "lnp.x"
#endif

#ifdef QC       
#include "lqc.x"           /* CAP management interface */
#endif

#ifdef GA
#include "cm_gprs.x"
#include "lga.x"           /* BSS Application Part Plus (BSSAP+) */
#endif

#ifdef MW                  /* SIGTRAN-M2UA */
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

#ifdef MX                  /* SIGTRAN-M2PA */
#include "cm_tpt.x"
#include "sdt.x"
#include "sct.x"
#include "lmx.x"
#endif 

#ifdef MK
#include "cm_umts.x"
#include "lmk.x"           /* 3G MAC management interface */
#endif

#ifdef RL
#include "cm_umts.x"
#include "lrl.x"           /* 3G RLC management interface */
#endif

#ifdef IB
#include "cm_tpt.x"        /* Transport address specific */
#include "cm_atm.x"        /* 3G NBAP management interface */
#include "sct.x"           /* SCT interface */
#include "lib.x"
#endif

/* sm_bdy1_c_001.main_100 RRC 2.0 */
#ifdef RR
#include "lrr.x"           /* 3G RRC management interface */
#endif

/* sm_bdy1_c_001.main_103 LTE RRC 1.1 */
#ifdef NH
#include "lnh.x"           /* LTE  RRC management interface */
#endif

/* sm_bdy1_c_001.main_104 LTE RLC 1.1 and LTE MAC 1.1 */
#ifdef RG
#include "cm_lte.x"
#include "lrg.x"           /* LTE MAC management interface */
#endif

#ifdef RN
#include "lrn.x"           /* RNSAP management interface */
#endif

#ifdef DV
#include "cm_hash.x"        /* common to hashing */
#include "cm_ftha.x"        /* common to DFT/HA */
#include "cmzvdv.x"         /* common to PSF and LDF-M3UA */
#include "cmzvdvlb.x"       /* common to PSF and LDF-M3UA */
#include "ldv.x"            /* LDF-M3UA layer management */
#endif /* DV */

/* sm_bdy1_c_001.main_98: LDF-SUA 1.1 REL */
#ifdef AH
#include "cm_hash.x"        /* common to hashing */
#include "cm_ftha.x"        /* common to DFT/HA */
#include "cm_ss7.x"         /* common to SS7 */
#include "spt.x"            /* SPT interface */
#include "cmaeah.x"         /* common to PSF and LDF-SUA */
#include "lah.x"            /* LDF-M3UA layer management */
#endif /* AH */

#ifdef FP
#include "lfp.x"           /* FP management interface */
#endif

#ifdef LM
#include "llm.x"            /* LM management interface */
#endif

#ifdef VU
#include "lvu.x"           /* VU management interface */
#endif

#ifdef RP
#include "cm_ftha.x"        /* common to DFT/HA */
#include "cmzarp.x"         /* common to PSF and LDF-RANAP */
#include "lrp.x"            /* LDF-RANAP layer management */
#endif

/* sm_bdy1_c_001.main_97: Addition for Diameter */
#ifdef AQ                  /* Diameter */
#include "cm_tpt.x"        /* common transport */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_inet.x"       /* common memory allocation */
#include "cm_llist.x"       /* common memory allocation */
#include "cm_hash.x"       /* common memory allocation */
#include "cm_dns.x"        /* Transport address specific */
#include "cm_tpt.x"       /* common memory allocation */
#include "cm5.x"       /* common memory allocation */
#include "sct.x"           /* SCT interface defines           */
#include "aq_util.x"
#include "aqu.x"
#include "laq.x"
#include "aq.x"
#endif

/* sm_bdy1_c_001.main_104 LTE RLC 1.1 and LTE MAC 1.1 */
#ifdef KW                  /* LTE RLC */
#include "cm_lte.x"
#include "lkw.x"
#endif /* KW */

/* sm_bdy1_c_001.main_105: Added LTE eNodeB and LTE convergence layer */
#ifdef VE
#include "cm_tpt.x"
#include "lve.x"
#endif
#ifdef YS
#include "lys.x"
#endif


  
/* local defines */
  
/* local typedefs */
  
/* local externs */
  
/* forward references */

   
/*
 *
 *      Fun:    smActvInit
 *
 *     Desc:    Invoked by system services to initialize the stack manager. 
 *              This is an entry point used by the stack manager to initialize 
 *              its global variables, before becoming operational.
 *
 *              The first and second parameters (entity, instance)
 *              specify the entity and instance id of the stack manager task.
 *
 *              The third parameter (region) specifies the memory region
 *              from which the stack manager should allocate structures and 
 *              buffers.
 *
 *              The fourth parameter (reason) specifies the reason for
 *              calling this initialization function.
 *
 *              Allowable values for parameters are specified in ssi.h.
 *
 *      Ret:    ROK - ok
 *
 *      Notes:  None
 *
        File:   sm_bdy1.c
 *
 */
#ifdef SS_MULTIPLE_PROCS  
#ifdef ANSI
PUBLIC S16 smActvInit
(
ProcId procId,              /* Processr */
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason,              /* reason */
Void   **xxCb               /* xxCb pointer */
)
#else
PUBLIC S16 smActvInit(procId, ent, inst, region, reason, xxCb)
ProcId procId;              /* Processor */
Ent    ent;                 /* entity */
Inst   inst;                /* instance */
Region region;              /* region */
Reason reason;              /* reason */
Void   **xxCb;              /* xxCb Pointer */
#endif

#else /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 smActvInit
(
Ent      ent,                 /* entity */
Inst     inst,                /* instance */
Region   region,              /* region */
Reason   reason               /* reason */
)
#else
PUBLIC S16 smActvInit(ent, inst, region, reason)
Ent      ent;                 /* entity */
Inst     inst;                /* instance */
Region   region;              /* region */
Reason   reason;              /* reason */
#endif /* ANSI */
#endif /* SS_MULTIPLE_PROCS */
{
   TRC3(smActvInit)

   /* call layer specific initialization functions */

#ifdef AP       /* async pad */
   smApActvInit(ent, inst, region, reason);
#endif

#ifdef IN       /* Q.930/Q.931 */
   smInActvInit(ent, inst, region, reason);
#endif

#ifdef AM       /* Q.93B */
   smAmActvInit(ent, inst, region, reason);
#endif

#ifdef AS       /* Q.SAAL */
   smAsActvInit(ent, inst, region, reason);
#endif

#ifdef AC       /* AC */
   smAcActvInit(ent, inst, region, reason);
#endif

#ifdef PN       /* PNNI */
   smPnActvInit(ent, inst, region, reason);
#endif

#ifdef IM       /* IME */
   smImActvInit(ent, inst, region, reason);
#endif

#ifdef UM       /* UME */
   smUmActvInit(ent, inst, region, reason);
#endif

#ifdef XG       /* x.75 */
   smXnActvInit(ent, inst, region, reason);
#endif

#ifdef EI       /* x.25 end and intermediate system */
   smXnActvInit(ent, inst, region, reason);
#endif

#ifdef XE       /* x.25 end system */
   smXnActvInit(ent, inst, region, reason);
#endif

#ifdef XI       /* x.25 intemediate system */
   smXnActvInit(ent, inst, region, reason);
#endif

#ifdef BD       /* lapb and lapd */
   smBdActvInit(ent, inst, region, reason);
#endif

#ifdef LD       /* lapd */
   smLdActvInit(ent, inst, region, reason);
#endif

#ifdef LB       /* lapb */
   smLbActvInit(ent, inst, region, reason);
#endif

#ifdef D2       /* D2 */
   smD2ActvInit(ent, inst, region, reason);
#endif

#ifdef BR       /* basic frame relay */
   smFrActvInit(ent, inst, region, reason);
#endif

#ifdef AF       /* FR/ATM interworking  */
   smAfActvInit(ent, inst, region, reason);
#endif

#ifdef FR       /* frame relay */
   smFrActvInit(ent, inst, region, reason);
#endif

#ifdef ER       /* extended frame relay */
   smFrActvInit(ent, inst, region, reason);
#endif

#ifdef SC       /* scc */
   smScActvInit(ent, inst, region, reason);
#endif

#ifdef IS       /* isac-s */
   smIsActvInit(ent, inst, region, reason);
#endif

#ifdef SE       /* sec */
   smSeActvInit(ent, inst, region, reason);
#endif

#ifdef IX       /* x.31 */
   smIxActvInit(ent, inst, region, reason);
#endif

#ifdef TC       /* TCP/IP */
   smTcActvInit(ent, inst, region, reason);
#endif

#ifdef UD       /* UDP/IP */
   smUdActvInit(ent, inst, region, reason);
#endif

#ifdef MS       /* mos */
   smMsActvInit(ent, inst, region, reason);
#endif

#ifdef NS       /* NTSS */
   smNsActvInit(ent, inst, region, reason);
#endif

#ifdef SD       /* MTP level 2 */
#ifdef SS_MULTIPLE_PROCS
   smSdActvInit(procId, ent, inst, region, reason, xxCb);
#else
   smSdActvInit(ent, inst, region, reason);
#endif /* SS_MULTIPLE_PROCS */
#endif

#ifdef SI       /* ISUP */
#ifdef SS_MULTIPLE_PROCS
   smSpActvInit(procId, ent, inst, region, reason, xxCb);
#else
   smSiActvInit(ent, inst, region, reason);
#endif /* SS_MULTIPLE_PROCS */
#endif

#ifdef TP       /* TUP */
   smTpActvInit(ent, inst, region, reason);
#endif

#ifdef SP       /* SCCP */
#ifdef SS_MULTIPLE_PROCS
   smSpActvInit(procId, ent, inst, region, reason, xxCb);
#else
   smSpActvInit(ent, inst, region, reason);
#endif /* SS_MULTIPLE_PROCS */
#endif

#ifdef RA       /* RANAP */
   smRaActvInit(ent, inst, region, reason);
#endif

#ifdef GM       /* GMM */
   smGmActvInit(ent, inst, region, reason);
#endif

#ifdef NM       /* NM */
   smGmActvInit(ent, inst, region, reason);
#endif

#ifdef ST       /* TCAP */
#ifdef SS_MULTIPLE_PROCS
   smStActvInit(procId, ent, inst, region, reason,xxCb);
#else
   smStActvInit(ent, inst, region, reason);
#endif
#endif

#ifdef TT       /* TCAP over TCP/IP */
   smTtActvInit(ent, inst, region, reason);
#endif

#ifdef IA       /* MAP IS41 */
   smIaActvInit(ent, inst, region, reason);
#endif

#ifdef IE       /* INAP */
   smIeActvInit(ent, inst, region, reason);
#endif

#ifdef SN       /* MTP Level 3 */
#ifdef SS_MULTIPLE_PROCS
   smSnActvInit(procId, ent, inst, region, reason, xxCb);
#else
   smSnActvInit(ent, inst, region, reason);
#endif /* SS_MULTIPLE_PROCS */
#endif

#ifdef WD       /* MTP Level 2 Wrapper */
   smWdActvInit(ent, inst, region, reason);
#endif

#ifdef WN       /* MTP Level 3 Wrapper */
   smWnActvInit(ent, inst, region, reason);
#endif

#ifdef WI       /* ISUP Wrapper */
   smWiActvInit(ent, inst, region, reason);
#endif

#ifdef WU       /* TUP Wrapper */
   smWuActvInit(ent, inst, region, reason);
#endif

#ifdef WS       /* SCCP Wrapper */
   smWsActvInit(ent, inst, region, reason);
#endif

#ifdef WC       /* TCAP Wrapper */
   smWcActvInit(ent, inst, region, reason);
#endif

#ifdef QI       /* QI */
   smQiActvInit(ent, inst, region, reason);
#endif

#ifdef PQ       /* PQ */
   smPqActvInit(ent, inst, region, reason);
#endif

#ifdef ME       /* ME */
   smMeActvInit(ent, inst, region, reason);
#endif

#ifdef IS       /* IS */
   smIsActvInit(ent, inst, region, reason);
#endif

#ifdef FM       /* FM */
   smFmActvInit(ent, inst, region, reason);
#endif

#ifdef RY       /* RY */
   smRyActvInit(ent, inst, region, reason);
#endif

#ifdef SA       /* Q.2140 */
   smSaActvInit(ent, inst, region, reason);
#endif

#ifdef BI       /* BI */
   smBiActvInit(ent, inst, region, reason);
#endif

#ifdef FN       /* Q933 */
   smFnActvInit(ent, inst, region, reason);
#endif

#ifdef EV       /* envelope function */
   smEvActvInit(ent, inst, region, reason);
#endif

#ifdef LV       /* lapv */
   smLvActvInit(ent, inst, region, reason);
#endif

#ifdef NV       /* v5.X PSTN */
   smNvActvInit(ent, inst, region, reason);
#endif
#ifdef VF       /* V5  Layer 3*/ 
   smVfActvInit(ent, inst, region, reason);
#endif
#ifdef CV       /* v5.X Control Protocol */
   smCvActvInit(ent, inst, region, reason);
#endif
#ifdef BV       /* v5.1 BCC */
   smBvActvInit(ent, inst, region, reason);
#endif

#ifdef MV       /* v5.X System Management */
   smMvActvInit(ent, inst, region, reason);
#endif

#ifdef ICC       /* call control */
   smCcActvInit(ent, inst, region, reason); 
#endif
#ifdef LK
   smLkActvInit(ent, inst, region, reason);
#endif /* LK */

#ifdef PV
   smPvActvInit(ent, inst, region, reason);
#endif /* PV */

#ifdef PA       /* PLOA */
   smPaActvInit(ent, inst, region, reason);
#endif
#ifdef MC       /* MSOC */
   smMcActvInit(ent, inst, region, reason);
#endif

#ifdef XN       /* X.25/X.75 */
   smXnActvInit(ent, inst, region, reason);
#endif

#ifdef AW
   smAwActvInit(ent, inst, region, reason);
#endif

#ifdef IW
   smIwActvInit(ent, inst, region, reason);
#endif
 
#ifdef SF
   smSfActvInit(ent, inst, region, reason);
#endif

#ifdef QW
   smQwActvInit(ent, inst, region, reason);
#endif

#ifdef RT
   smRtActvInit(ent, inst, region, reason);
#endif
 

#if 0
#ifdef RM
   smRmActvInit(ent, inst, region, reason);
#endif
#endif
 
#ifdef XM
   smXmActvInit(ent, inst, region, reason);
#endif
/* sm_bdy1_c_001.main_101: Added the support for FTHA Integration*/
#ifdef SG
   smSgActvInit(ent, inst, region, reason);
#endif

#ifdef VW_COMPILE
#undef SH
#endif

#ifdef SH
   smShActvInit(ent, inst, region, reason);
#endif

#ifdef MR
   smMrActvInit(ent, inst, region, reason);
#endif

#ifdef PR
   smPrActvInit(ent, inst, region, reason);
#endif

#ifdef GN
   smGnActvInit(ent, inst, region, reason);
#endif

#ifdef GT
   smGtActvInit(ent, inst, region, reason);
#endif

#ifdef GL
 smGlActvInit(ent, inst, region, reason);
#endif

#ifdef GG
   smGgActvInit(ent, inst, region, reason);
#endif

#ifdef HC
   smHcActvInit(ent, inst, region, reason);
#endif

#ifdef HI
   smHiActvInit(ent, inst, region, reason);
#endif

#ifdef HG
   smHgActvInit(ent, inst, region, reason);
#endif

#ifdef GS
   smGsActvInit(ent, inst, region, reason);
#endif

#ifdef HR
   smHrActvInit(ent, inst, region, reason);
#endif

#ifdef IQ  /* Q.930/931-Q.SAAL Convergence Layer */
   smIqActvInit(ent, inst, region, reason);
#endif

#ifdef DN  /* LDF - MTP3 */
   smDnActvInit(ent, inst, region, reason);
#endif /* DN */

#ifdef DI  /* LDF - ISUP */
   smDiActvInit(ent, inst, region, reason);
#endif /* DI */

#ifdef VO       /* MPC8260 driver */
      smVoActvInit(ent, inst, region, reason);
#endif /* VO */

#ifdef SB       /* SCTP */
      smSbActvInit(ent, inst, region, reason);
#endif /* SB */

#ifdef SO  /* SIP */
   smSoActvInit(ent, inst, region, reason);
#endif

#ifdef IT       /* M3UA */
      smItActvInit(ent, inst, region, reason);
#endif /* IT */

#ifdef NF       /* NIF */
      smNfActvInit(ent, inst, region, reason);
#endif /* NF */

#ifdef LN       /* MPLS-LDP(+CR) */
   smLnActvInit(ent, inst, region, reason);
#endif

#ifdef AL      /* AAL2 Signaling */
   smAlActvInit(ent, inst, region, reason);
#endif /* AL */

#ifdef DP  /* LDF - SCCP */
   smDpActvInit(ent, inst, region, reason);
#endif /* DP */

#ifdef DT  /* LDF - TCAP */
   smDtActvInit(ent, inst, region, reason);
#endif /* DT */

#ifdef ID  /* SIGTRAN - IUA */
#ifdef SM
   smIdActvInit(ent, inst, region, reason);
#endif
#endif /* ID */

#ifdef ND  /* SIGTRAN - IUA-NIF */
#ifdef LD
   smNdActvInit(ent, inst, region, reason);
#endif
#endif /* ND */

#ifdef SU  /* SUA */
   smSuActvInit(ent, inst, region, reason);
#endif

#ifdef NP  /* SUA - NIF */
   smNpActvInit(ent, inst, region, reason);
#endif
#ifdef QC  /* CAP */
   smQcActvInit(ent, inst, region, reason);
#endif /* QC */

#ifdef GA
   smGaActvInit(ent, inst, region, reason);
#endif

#ifdef MW  /* SIGTRAN-M2UA */
      smMwActvInit(ent, inst, region, reason);
#endif

#ifdef NW  /* M2UA-NIF  */
      smNwActvInit(ent, inst, region, reason);
#endif

#ifdef MX  /* SIGTRAN-M2PA */
       smMxActvInit(ent, inst, region, reason);
#endif

#ifdef MK       /* 3GPP MAC */
   smMkActvInit(ent, inst, region, reason);
#endif

#ifdef RL       /* 3GPP RLC */
   smRlActvInit(ent, inst, region, reason);
#endif

#ifdef IB       /* 3GPP NBAP  */
   smIbActvInit(ent, inst, region, reason);
#endif

/* sm_bdy1_c_001.main_100 RRC 2.0 */
#ifdef RR       /* 3GPP RRC */
   smRrActvInit(ent, inst, region, reason);
#endif

/* sm_bdy1_c_001.main_103 LTE RRC 1.1 */
#ifdef NH       /* LTE  RRC */
   smNhActvInit(ent, inst, region, reason);
#endif

#ifdef NL
   smNlActvInit(ent, inst, region, reason);
#endif

/* sm_bdy1_c_001.main_104 LTE RLC 1.1 and LTE MAC 1.1 */
#ifdef RG       /* LTE MAC */
   smRgActvInit(ent, inst, region, reason);
#endif

#ifdef RN       /* RNSAP      */
   smRnActvInit(ent, inst, region, reason);
#endif

#ifdef DV  /* LDF - M3UA */
   smDvActvInit(ent, inst, region, reason);
#endif /* DV */

/* sm_bdy1_c_001.main_98: LDF-SUA 1.1 REL */
#ifdef AH  /* LDF - SUA */
   smAhActvInit(ent, inst, region, reason);
#endif /* AH */

#ifdef FP       /* FP */
      smFpActvInit(ent, inst, region, reason);
#endif /* FP */

#ifdef VU       /* VU */
      smVuActvInit(ent, inst, region, reason);
#endif /* VU */

#ifdef RP       /* LDF - RANAP */
   smRpActvInit(ent, inst, region, reason);
#endif

#ifdef DK       /* LDF - GMM/SM */
   smDkActvInit(ent, inst, region, reason);
#endif

#ifdef LM        /* LAPDm */
   smLmActvInit(ent, inst, region, reason);
#endif

/* sm_bdy1_c_001.main_97: Addition for Diameter */
#ifdef AQ
#ifdef SS_MULTIPLE_PROCS
   smAqActvInit(procId, ent, inst, region, reason, xxCb);
#else
   smAqActvInit(ent, inst, region, reason);
#endif /* SS_MULTIPLE_PROCS */
#endif

/* sm_bdy1_c_001.main_104 LTE RLC 1.1 and LTE MAC 1.1 */
#ifdef KW
   smKwActvInit(ent, inst, region, reason);
#endif /* KW */

/* sm_bdy1_c_001.main_105: Added LTE eNodeB and LTE convergence layer */
#ifdef VE
   smVeActvInit(ent, inst, region, reason);
#endif 

#ifdef YS
   smYsActvInit(ent, inst, region, reason);
#endif
      /* call external function for intialization */
      /* call external function for intialization */
   smInitExt();
#ifdef SS_MULTIPLE_PROCS
   *xxCb = NULLP;
#endif /* SS_MULTIPLE_PROCS */
   RETVALUE(ROK);
} /* end of smActvInit */
/*sm_bdy1_c_001.main_96*/
  
/********************************************************************30**
  
         End of file:     sm_bdy1.c@@/main/106 - Fri Mar 26 22:34:02 2010
  
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

1.3          ---  mc    1. changed include files for BD, LD, LB, BR, and ER.

1.4          ---  ak    1. added PN (ATM-PNNI)

1.5          ---  mc    1. changed include files for XG, EI, XE and XI.
             ---  mc    2. replaced sm??ActvInit (Xg, Ei, Xe, and Xi) with 
                           smXnActvInit.

1.6          ---  mc    1. added ss7 stack wrapper (WD, WN, WI, WU, WS, and WC)
             ---  fmg   2. added QI

1.7          ---  fmg   1. added ME

1.8          ---  jrl   1. added IS

1.9          ---  fmg   1. added FM

1.10         ---  krp   1. added BI for BISUP
             ---  mc    2. added Q.2140 (SA)

1.11         ---  fmg   1. added Relay includes for function prototypes

1.12         ---  krp   1. added Frame Relay includes for function prototypes

1.13         ---  krp   1. added Frame Relay Network layer(FN) for Q.933 

1.14         ---  mc    1. added LAPV and V5.1 PSTN.

1.15         ---  mc    1. added V5 Envelope Function.
             ---  mc    2. change copyright header

1.16         ---  ada   1. add FR section
1.17         ---  aa    1. Added cm_ss[hx] under SM_SS7 flag
             ---  aa    2. Removed the TCAP user section
             ---  bn    3. added section for V5.X Control Protocol
             ---  bn    4. added section for V5.X System Manager

1.18         ---  aa    1. Removed the  TU Section form smActvInit function
1.19         ---  ak    1. added IME
1.20         ---  sb    1. Added V5 BCC. Protocol.
1.21         ---  sb    1. Added V5 LC Protocol.
             ---  mg    2. Added V5 Protection Protocol.
             ---  kvm   3. added PLOA (PA)

*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- -----------------------------------------------
1.22         ---      sg   1. Added MAP IS41 (IA).

1.23         ---      mb   1. Added AC
             ---      apr  2. Added CC

1.24         ---      kvm  1. included cm_atm.[hx] within SM_ATM 
                              compile flag 

1.25         ---      pm   1. included cm_atm.[hx] files for SA.

1.26         ---      bsr  1. included cm_isdn.[hx] for FN

             ---      manb 2. included laf.h, laf.x and afActvInit.

1.27         ---      kr   1. added X.25/X.75 system

1.28         ---      skr  1. Added PQ

1.29         ---      sj   1. endif AF is patched 
             ---      mg   2. Added PLOA include files lpa.x.

1.30         ---      mg   1. Changed copyright header date.

1.31         ---      hrg  1. Added sections for INAP.
             ---      kr   2. Added Windows-NTSS (NS) 

1.32         ---      ao   1. included header files for RT, RM, SF and BW
                              entities.
             ---      mp   1. included header files and activation init
                              function for V5 layer 3.
 
1.33         ---      rs   1. Changes for interworking call control

1.34         ---      apr  1. Added System Manager(SG), System Agent(SH)
                              and Message Router(MR)
             ---      hrg  2. Added TCAP over TCP/IP (TT) sections.

1.35         ---      rs   1. Changed #ifdef CC to #ifdef ICC. Added
                              include files for QW (ISDN PSIF)

1.36         ---      nct  1. Added PR (MPC860SAR driver).

1.37         ---      nj   1. Included header file for INAP

1.38         ---      rs   1. include files for AW (Q.93B PSIF)

1.39         ---      ark  1. include files for GN (GPRS:Network Service)

1.40         ---      rs   1. include files for GT (GPRS:Tunneling Protocol)

1.41         ---      sg   1. include files for GL (GPRS:Logical Link Control)

1.42         ---      mb   1. Additions for H.323

1.43         ---      nj   1. Made changes for GG (GPRS: BSSGP)

1.44         ---      nj   1. Corrected warnings for cm_gprs

1.45         ---      pm   1. Additions for SNDCP (GPRS).

1.46         ---      kp   1. Additions for RTP/RTCP.

1.47         ---      sam  1. include header files and activation init
                              function for Q.930/931-Q.SAAL Convergence
                              Layer.
1.48         ---      mg   1. Modifications for ICC 1.4 release

1.49         ---      rs   1. Modifications for GTP 1.2 release

1.50         ---      rs   1. Modifications for ICC 1.5 release
/main/51        ---      asa  1. Additions for Annex E
/main/52        ---      ssk  1. Modifications for LDF-MTP3 release
/main/54     ---      smrw  1. Added VO (MPC8260 driver)
/main/55     ---        sb  1. Modification done for SCTP,M3UA, and NIF layer 
/main/56     ---      sa   1. Modification for MPLS.
                           2. Modification for AAL2 Signaling.                           
/main/57     ---      bsr  1. Added section H.225 Annex G
/main/57     ---      vb   1. Added section for LDF-SCCP
/main/58     ---      ssk  1. Modifications for LDF-MTP3
                              cm_zndn includes are changed to 
                              cmzndn and cmzndnlb includes
                              cm_pftha includes are removed.
/main/59     ---      ash  1. Changes for SG, SH and MR                              
/main/61     ---      ssk  1. Changes for DT                                    
             ---      hl   2. Added section for IUA and IUA-NIF
/main/62     ---      sb   1. cm_dns.[xh] files added for SCTP. 
/main/63     ---      ms   1. Added section for SIP 
/main/64     ---      nt   1. Added section for SUA and SUA NIF
/main/65     ---      dw   1. Added call to smRaActvInit
/main/66     ---      as   1. Added section for CAP 
/main/67     ---      srg  1. Added section for BSSAP+
/main/68     ---      an   1. Added code for H.323-PSF
/main/69     ---      nt   1. sht.[hx] added for M3UA.
/main/70     ---       hl  1. Added M2UA and its NIF   
/main/71     ---      tz   1. Added sections for LDF-ISUP 
/main/72     ---      sa   1. Added section for 3GPP-MAC
/main/73     ---      vr   1. Added section for 3GPP-RLC
/main/74     ---      ak   1. Added section for 3GPP-NBAP
/main/75     ---      sm   1. Added section for GMM/SM
/main/76     ---      hl   1. Updated for IUA version 1.2
/main/77     ---     ssk   1. Added section for RNSAP 
/main/77 001.main_77 mkm   1.Added support for SS_MULTIPLE_PROCS   
/main/78     ---      rs   1. Added section for LDF-M3UA 
/main/79     ---     ps    1. FP & VU changes for rel 1.1
/main/80     ---     hr    1. Added M2PA 
 /main/81    ---     bn    1. Added DPNSS/DASS2
/main/82     ---      st   1. Update for MAP Release 2.3
/main/83     ---     rbabu 1. Updated for NBAP Release 1.2
/main/84     ---      vsr  1. Updated for LDF-RANAP 1.1 release.
/main/86     ---      sal  1. Created for Release of 2.1(RFC 3868 Support)
/main/87     ---       sm  1. Protected cm_inet.h inclusion in 
                              SUAP_IPOPT flag.
/main/89     ---      gs   1. REcovered last correct version during MAC 1.3 RTR
/main/90     ---      kkj  1. GMM 2.1 release
/main/91     ---      yk   1. GMM/SM LDF 1.1 Release
/main/92     ---      ad   1. Updated for Release SIP 2.2 Beta
/main/93     ---      sal  1. Multiple Proc Changes
/main/94     ---      st   1. Updated for LAPDm 1.1 Release.
/main/95     ---      mkm  1. Multiple Proc Changes for TCAP.
/main/96     ---      bsk  1. Fixed bug in Multi proc changes.
/main/96+     sm_bdy1_c_001.main_96 gs   1. Updated for MAC-HS Release 1.1
             ---      gs   1. Updated for MAC-HS 1.1 Release.
sm_bdy1_c_001.main_97 svp  1. Updated for Diameter 1.2 Release.
/main/99     ---      sm_bdy1_c_001.main_98 rce  1. Updated for LDF SUA 1.1 Release
/main/100    ---    sm_bdy1_c_001.main_99  rbabu 1. Update for PDCP Software release 1.1
/main/101    ---     sm_bdy1_c_001.main_100 rbhat   1. RRC 2.0 Release
/main/102    ---   sm_bdy1_c_001.main_101     aj  1. Added the support for FTHA Integration 
/main/103    ---   sm_bdy1_c_001.main_102     pc  1. Diameter SDK release, included                                                  cm_dns.[hx] under AQ
/main/104    ---   sm_bdy1_c_001.main_103     vk  1. Updated for Release of LTE RRC 1.1.
/main/104    ---   sm_bdy1_c_001.main_104     nm  1. Updated for Release of LTE RLC 1.1 
                                                     and LTE MAC 1.1
/main/106          sm_bdy1_c_001.main_105    pkaX 1. Updated for LTE eNodeB and LTE convergence
                                                     layer release.
*********************************************************************91*/
