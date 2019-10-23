/**********************************************************************

     Name:     stack manager - body 1
  
     Type:     C source file
  
     Desc:     C source code for stack manager supplied by TRILLIUM.

               

     File:     sm_bdy1.c
  
     Sid:    
  
     Prg:    
  
*********************************************************************21*/
  
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
 
#ifdef RM
#include "cm_atm.h"        /* common atm */
#include "cm_cc.h"         /* Common call control */
#include "rm.h"            /* common Resource Manager layer */
#ifdef PNNI_ROUTING_ENABLED
#include "lpn.h"           /* common file for PNNI */
#endif /* PNNI_ROUTING_ENABLED */
#include "lrm.h"           /* Resource Manager */
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
 
#ifdef RM
#include "cm_atm.x"        /* common atm */
#include "cm_cc.x"         /* Common call control */
#ifdef PNNI_ROUTING_ENABLED
#include "lpn.x"           /* PNNI defines */
#endif /* PNNI_ROUTING_ENABLED */
#include "lrm.x"           /* Resource Manager */
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


#ifdef HI
   smHiActvInit(ent, inst, region, reason);
#endif

#ifdef SB       /* SCTP */
      smSbActvInit(ent, inst, region, reason);
#endif /* SB */


      /* call external function for intialization */
   smInitExt();
#ifdef SS_MULTIPLE_PROCS
   *xxCb = NULLP;
#endif /* SS_MULTIPLE_PROCS */
   RETVALUE(ROK);
} /* end of smActvInit */
/*sm_bdy1_c_001.main_96*/
