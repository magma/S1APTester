/********************************************************************20**
  
     Name:     environment options
  
     Type:     C include file
  
     Desc:     Environment options specifies defines required by the
               by TRILLIUM software. The defines in this file need to be
               changed by the customer to reflect the software architecture
               needed to run under the target system hardware architecture.
  
     File:     envopt_t2k.h
  
     Sid:      envopt_t2k.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:05:04 2014
    
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

/* layer manager interface, choose one */

/* #define LMINT1       interface 1 */
/* #define LMINT2       interface 2 */
#define LMINT3       /* interface 3 */

/* NOTE : LMINT3 flag MUST be turned-on if using PSF (FT/HA) for a protocol layer */

#define TDS_CORE2                   /*Trillium DFT/HA CORE architecture enabled */
/* #define TDS_ROLL_UPGRADE_SUPPORT    Rolling upgrade feature support enabled  */
                                    /*in Trillium DFT/HA CORE architecture   */

/* #define TDS_FTHA_CUST_PKUNPK  If using a heterogenous system in a DFT/HA env */


/* packing order, choose none or one */

/* #define FCSPKINT      forward compatibility, packing order */

/* operating system version, choose one */

/* #define PORTVER              portable version */
/* #define MOSVER               mos version 1 */
/* #define MSVER2               mos version 2 */
/* #define SSLIB                system services library */
/* #define PS                   psos */
/* #define VX                   vrtxsa */
/* #define VW                   vxworks */
/* #define WINNT_IATM  1        Windows NT */
/* #define MT                   unix - multi-threaded */
/* #define NS                   Windows NT SSI - multi-threaded */
/* #define SS_SK                SSI-SDK */
/* #define SS_MT                MTSS-Solaris 2.1 */
/* #define SS_PS                pSOS/pRISM+ System Services */
/* #define SS_VW                VxWorks System Services 2.1 */

/* if one of the above options SS_PS, SS_MT, SS_SK, NS or SS_VW is enabled,
 * uncomment the following lines 
 */
#if  (defined(SS_PS) \
      || defined(SS_MT) \
      || defined(SS_SK) \
      || defined(NS)    \
      || defined(SS_VW)) 
#ifndef SS
#define SS              /* enable common system services */
#endif
#endif   /* SS_PS || SS_MT || SS_SK || NS || SS_VW */

#ifndef NS
#ifdef WINNT
#define WINNT_IATM 1    /* for backward compatibility with Integrated ATM */
#endif/* NS */
#endif /* WINNT */

/* layer management, choose none or one */

/* #define TCLM         tightly coupled, layer management */
/* #define LCLM          loosely coupled, layer management */

/* debug flag */

/* #define DEBUGP            enable debug printing */

/* #define INT2
   #define DAT2 */

/* common SS7 stack defines */

#define CMSS7_SPHDROPT     
/* spHdrOpt option. Enable this flag for  the upper layers of SCCP as well.  */

/**************************************************************************
   elvis/imp parameters
**************************************************************************/

/* elvis, choose none */

#ifdef ELVIS_68302
#define ELVIS                   /* turn on elvis */
#define PROC_68302              /* proc 68302 */
#define PROC_68XXX              /* proc class 68K */
#define ENB_RELAY               /* enable relay */
#ifdef RY_ENBRAW
#undef RY_ENBRAW
#endif /* RY_ENBRAW */
#define RY_ENBRAW               /* enable raw channels */
#define SS7_MICROCODE           /* ss7 microcode */
#define SOLMRI43                /* solaris MRI 4.3 */
#ifdef MSVER2                   /* mos version 2 */
#undef MSVER2
#define MSVER2
#else
#define MSVER2
#endif /* MSVER2 */

#define GS_IPCOMM302
#define GS_IPCOMM3XX
 
#else /* not elvis 68302 */

#ifdef ELVIS_PPC860
#ifdef MS
#ifdef MSVER2                   /* mos version 2 */
#undef MSVER2
#define MSVER2
#else
#define MSVER2
#endif /* MSVER2 */
#endif /* MS */

#define ELVIS_PPC          /* Flag for the architecture */
#define PROC_PPC860        /* Denotes the processor type */
#define PROC_PPC           /* General Power PC */
#define ENB_RELAY          /* enable relay */
   
#ifdef RY_ENBRAW
#undef RY_ENBRAW
#endif /* RY_ENBRAW */
#define RY_ENBRAW           /* enable raw channels */
#define SS7_MICROCODE       /* ss7 microcode */
#define CCPPC               /* Denotes which compiler is used */
   
#define PQ_PPC860           /* Force Power Quicc 860 Board */
#define PQ_PPC8XX           /* Force Power Quicc 8XX Board */
 
#else /* not elvis PPC860*/

#ifdef ELVIS_68360
#define ELVIS                   /* turn on elvis */
#define PROC_68360              /* proc 68360 */
#define PROC_68XXX              /* proc class 68K */
#define ENB_RELAY               /* enable relay */

#ifdef RY_ENBRAW
#undef RY_ENBRAW
#endif /* RY_ENBRAW */

#define RY_ENBRAW               /* enable raw channels */
#define SS7_MICROCODE           /* ss7 microcode */
#define SOLMRI43                /* solaris MRI 4.3 */

#ifdef MSVER2                   /* mos version 2 */
#undef MSVER2
#define MSVER2
#else
#define MSVER2
#endif /* MS_VER2 */

#define GS_IPCOMM360
#define GS_IPCOMM3XX
 
#else /* not elvis 68360 */
#ifdef ELVIS_68040
#define ELVIS
#define PROC_68040
#define PROC_68XXX
#define ENB_RELAY
#ifdef RY_ENBRAW
#undef RY_ENBRAW
#endif /* RY_ENBRAW */
#define RY_ENBRAW
#define SOLMRI43
#ifdef MSVER2
#undef MSVER2
#define MSVER2
#else
#endif /* MSVER2 */

/* uncomment one of the following */
#define MVME162_1
 
#else /* not elvis 68040 */
#ifdef ELVIS_STACK
#define ELVIS
#ifdef PPC   /* Stack talking to Power PC board */
#undef ELVIS
#define ELVIS_PPC
#endif /* PPC */
#define PROC_SPARC
/* uncomment one of the following */
#define SUNOS51
#define ENB_RELAY      /* enable relay */

#ifdef ELVIS_BIT3
#ifdef RY_ENBBIT3
#undef RY_ENBBIT3
#endif /* RY_ENBBIT3 */
#define RY_ENBBIT3     /* enable bit-3 interface */
#else
#ifdef ELVIS_IMP
#ifdef RY_ENBIMP
#undef RY_ENBIMP
#endif /* RY_ENBIMP */
#define RY_ENBIMP     /* enable bit-3 interface */
#else
#ifdef ELVIS_FORCE
#ifdef RY_ENBHST
#undef RY_ENBHST
#endif /* RY_ENBHST */
#define RY_ENBHST
#endif /* ELVIS_FORCE */
#endif /* ELVIS_IMP */
#endif /* ELVIS_BIT3 */

#ifdef RY_ENBS5MSG
#undef RY_ENBS5MSG
#endif /* RY_ENBS5MSG */

#define RY_ENBS5MSG    /* enable system 5 message queues interface */
#define RY_ENBMMAP     /* enable shared memory interface */

#ifdef MSVER2
#undef MSVER2
#define MSVER2
#else
#define MSVER2
#endif /* MSVER2 */

#else /* not elvis host */
#ifdef ELVIS_APP
#define ELVIS
#define PROC_SPARC
#define SUNOS51
#define ENB_RELAY

#ifdef MSVER2
#undef MSVER2
#endif /* MSVER2 */

#ifdef SSLIB
#undef SSLIB
#define SSLIB
#else
#ifdef SSRYLIB
#undef SSRYLIB
#define SSRYLIB
#else
#define SSLIB
#endif /* SSRYLIB */
#endif /* SSLIB */

#define ENB_RELAY               /* enable relay */
#ifdef SSLIB
#define RY_ENBS5MSG    /* enable system 5 message queues interface */
#endif
#ifdef SSRYLIB
#define RY_ENBMMAP     /* enable shared memory interface */
#endif

#else /* ELVIS_APP */

#ifdef ELVIS_PPC604
#define PCORE          /* Force Board 603/4         */
#define ELVIS_PPC      /* General Architecture Flag */
#define ELVIS_PPC60X   /* 60X flag for this architecture */
#define ELVIS_PPCXXX   /* XXX flag for this architecture */

#define PROC_PPC604    /* 604 Power PC */
#define PROC_PPC60X    /* 60X Power PC */
#define PROC_PPC       /* Power PC */

#define ENB_RELAY
#ifdef RY_ENBRAW
#undef RY_ENBRAW
#endif /* RY_ENBRAW */
#define RY_ENBRAW

#define CCPPC            /* GNU Compiler */
#define PC_PPC604        /* FORCE Power Core 604 Board */
#define PC_PPC60X        /* FORCE Power Core 60X Board */
 

#endif /* ELVIS_PPC604 */
#endif /* ELVIS_APP */
#endif /* ELVIS_STACK */
#endif /* ELVIS_68040 */
#endif /* ELVIS_68360 */
#endif /* ELVIS_PPC860 */
#endif /* ELVIS_68302 */

#ifdef QUICCADS
#define PROC_68360
#endif /* QUICCADS */

#ifdef PQUICCADS
#define ELVIS_PPC          /* Flag for the architecture */
#define PROC_PPC860        /* Denotes the processor type */
#define PROC_PPC
#define CCPPC               /* Denotes which compiler is used */
#define PQ_PPC860           /* Force Power Quicc 860 Board */
#endif /* PQUICCADS */
 

#ifdef INTNT_PMC860
/**************************************************************************
   Integrated Windows NT SS7/PMC860 Platform 
**************************************************************************/
#define STKID_INTNT_PMC860_KERNEL  0x01  /* stack id for the kernel stack */
#define MAX_USER_SPACE_STKS        0x06  /* six user space stks are possible */
#define MAX_USER_SPACE_APPS        0x0f  /* 15 applications are possible */

#define SS7_NTUK_DEV_NAME   "td_ss7_uk"
#define SS7_NTKH_DEV_NAME   "td_ss7_kh"
#define DEV_NAMELEN          10

#ifdef INTNT_PMC860_USER
#define NS                   /* System services provider */
#define NU                   /* NTSS user space */
#define SS                   /* Common system servies */
#define RY_ENBNTUK        1  /* relay user-kernel */
#define RY_ENBNTUK_SLV       /* user space is slave */
#define RY_ENBNTMMAP         /* enable user-app relay */
#define RYDEBUG              /* enable relay debugging */

#define USER_UK_RELAY_CHANID        0x0
#define USER_UA_RELAY_LOW_CHANID    (USER_UK_RELAY_CHANID + 1)
#define USER_UA_RELAY_HIGH_CHANID   (USER_UA_RELAY_LOW_CHANID + \
                                     + MAX_USER_SPACE_APPS)
#endif /* INTNT_PMC860_USER */

#ifdef INTNT_PMC860_APP
#define NTSSLIB              /* System services provider */
#define ENB_RELAY            /* enable relay */
#define RYDEBUG              /* enable relay debugging */
#define RY_ENBNTMMAP         /* enable user-app relay */
#define RYINT1               /* relay new interface */
#define SSRYLIB              /* mmap relay */

/* duplicated here from hw.h */
#define VC_CS_LEN       0xA000     /* run checksum on 1st 40k of vcm image */
#define IP_CS_LEN       0xA000     /* run checksum on 1st 40k of ipm image */

#define APP_UA_RELAY_LOW_CHANID   0x0
#define APP_UA_RELAY_HIGH_CHANID  MAX_USER_SPACE_STKS
#endif /* INTNT_PMC860_APP */

#ifdef INTNT_PMC860_KERNEL
#define NS                   /* System services provider */
#define NK                   /* NTSS kernel space */
#define SS                   /* Common system servies */
#define RYDEBUG              /* enable relay debugging */
#define RY_ENBNTUK        1  /* enable use-kernel relay */
#define RY_ENBNTUK_MST       /* user space is slave */
#define RY_ENBNTKH        1  /* relay kernel-hardware */

/* 
 * select this option only if the software has already 
 * been burnt in 
 */
#define PMC860_BOOTABLE          /* software is already loaded */
#define FRC_PMC860          1    /* enable the hardware defines */
#define KERNEL_RYREGION     1    /* kernel relay region */
#define INTNT_PMC860_BOARD0 0    /* Force PMC860 board-0 */
#define INTNT_PMC860_BOARD1 1    /* Force PMC860 board-1 */

/* The following are the channel ranges reserved */
#define KERNEL_KH_RELAY_LOW_CHANID    1 
#define KERNEL_KH_RELAY_HIGH_CHANID   MAXBRDS  
#define KERNEL_UK_RELAY_LOW_CHANID    (KERNEL_KH_RELAY_HIGH_CHANID + 1)
#define KERNEL_UK_RELAY_HIGH_CHANID   (KERNEL_UK_RELAY_LOW_CHANID + \
                                       MAX_USER_SPACE_STKS)

#undef WINNT_IATM             /* don't include older defines */

#endif /* INTNT_PMC860_KERNEL */

#ifdef INTNT_PMC860_IP
#define MSVER2             /* System services provider */
#define RYINT1             /* relay new interface */
#define ENB_RELAY          /* enable relay */
#define RY_ENBRAW          /* relay user-kernel */
#define RYDEBUG              /* enable relay debugging */
#define PROC_PPC860        /* Denotes the processor type */
#define PROC_PPC           /* General Power PC */
#define PQ_PPC860          /* Force Power Quicc 860 Board */
#define FRC_PMC860          1    /* enable the hardware defines */

#endif /* INTNT_PMC860_IP */

#endif /* INTNT_PMC860 */

#ifdef MT       /* unix - multi-threaded */
/**************************************************************************
   unix - multi-threaded system services
**************************************************************************/

/* product version, choose one */
#define MT_SOL                  /* Solaris Thread Architecture */
/* #define MT_AIX                AIX Thread Architecture */
/* #define MT_WNT                Windows NT Thread Architecture */
/* ...                           any others? */

#endif /* MT */


#ifdef AP       /* asynchronous pad */
/**************************************************************************
   asynchronous pad parameters
**************************************************************************/

/* product version, choose one */
 
#ifndef APVER2
#define APVER2         /* asynchronous pad, version 2.x */
#endif
 
#define L3VER2         /* isdn, version 2.x */

/* interfaces */

#define MACVER2        /* in order to include mac.x file */

/* lower interface, x.25 network, choose none or more */

/* #define LCAPLIXNT     loosely coupled, x.25 network layer */
/* #define BCLIXNT       backward compatibility, x.25 network layer */

/* lower interface, mac, choose none or more */

/* #define LCAPLIMAC     loosely coupled, mac layer */
/* #define BCLIMAC       backward compatibility, mac layer */

/* upper interface, application, choose none or more for host PAD only */

/* #define LCAPUIAPL     loosely coupled, application */
/* #define BCUIAPL       backward compatibility, application */

/* layer management options */
/* #define LCAPMILAP          loosely coupled, layer management */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCAPLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCAPLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCAPLM          /* tightly coupled, layer management */
/* #define LCAPLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* pad type, choose one */

#define TPAD         /* terminal pad */
/* #define HPAD          host pad */

#endif


#ifdef IN       /* Q.93x */
/**************************************************************************
   q.930/q.931 parameters
**************************************************************************/

/* product version, choose one */

#define ISDN_3_8_PLUS  /* Code version 3.10 & above */

/* enable ISDN_3_8_PLUS if INT2 is enabled */
#ifdef INT2 
#ifndef ISDN_3_8_PLUS
#define ISDN_3_8_PLUS 
#endif 
#endif /* INT2 */

/*#define INT_OLD_DEFINES      use old defines in int.h */
/*#define LIN_OLD_DEFINES      use old defines in lin.h */

#define BDVER2

#define INVER2         /* isdn, version 2.x */
 
#define ANVER2         /* isdn, version 2.x */

#define L3VER2         /* isdn, version 2.x */

/* #define IN_OLD_BIND  Use Old Method for Binding */

#define IN_LMINT3      /* If this flag is enabled also enable
                            SMIN_LMINT3 under ifdef SM */
/* interfaces */

/* upper interface, isdn network, choose none or more */
/* #define LCINUIINT      loosely coupled, isdn network layer */

/* lower interface, data link, choose none or more */
/* #define LCINLIDAT      loosely coupled, data link layer */

/* layer management interface */
/* #define LCINMILIN      loosely coupled, layer manager */

/* Q.931 upper interface */
#ifdef LCINUIINT
#ifndef LCINT
#define LCINT  1
#endif /* LCINT */
#endif /* LCINUIINT */

/* Q.931 lower interface */
#ifdef LCINLIDAT
#ifndef LCDAT
#define LCDAT  1
#endif /* LCDAT */
#endif /* LCINLIDAT */

/* Q.931 layer manager interface */
#ifdef LCINMILIN
#ifndef LCLIN
#define LCLIN  1
#endif /* LCLIN */
#endif /* LCINMILIN */

#ifdef IN_LMINT3
#undef IN_LMINT3
#define IN_LMINT3 1
#endif /* IN_LMINT3 */

/* product specific options */

/* side, choose one or more */
/* must agree with options delivered */

#define USRSIDE       /*user side, option 1 or option 3 */
#define NETSIDE       /*network side, option 2 or option 3 */

/* Option for ITUT-88 standard - used in bearcapability encoding/decoding */
 
/* #define ITUT88      ITU-T 88 - for Bearer Capability */

/* switch variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with x.31, isup switch variants */

/*#define ATT            att 4ess and 5ess, option 11 */
/*#define NT             northern telecomm dms-100, option 12 */
/*#define VN             vn 2 and vn 3, france, option 13 */
/*#define ETSI           etsi, europe, option 14 */ 
/*#define AUS            AUS, australian, option 15 */ 
/*#define NI1            national isdn 1, north america, option 16 */ 
/*#define NTT            ins net, japan, option 17 */
/*#define INTR6          1 - TR6, german, option 18 */
/*#define ATT5E          att 5ess, option 19 */
/*#define ATT4E          att 4ess, option 20 */
/*#define VN2            vn 2, france, option 21 */
/*#define VN3            vn 3, france, option 22 */
/*#define NTDMS250       northern telecom dms-250, option 23 */
/*#define BC303          bellcore tr-303, tmc and csc, option 24 */
/*#define BC303TMC       bellcore tr-303, tmc , option 25 */
/*#define BC303CSC       bellcore tr-303, csc, option 26 */
/*#define Q932           q.932 option, option 27 */
/*#define NI2            national isdn 2, north america, option 28 */ 
/*#define QSIG           etsi qsig, option 29 */
/*#define NTNI           nt ni, option 31 */
/*#define NTMCI          nt mci, option 32 */
/*#define NTSPRINT       nt dms-250 sprint */

/* variant, choose all */

#ifdef ATT              /* att */
#define ATT5E           /* att 5ess, option 19 */
#define ATT4E           /* att 4ess, option 20 */
#endif

#ifdef VN3              /* vn 3 */
#define VN              /* vn 2 and vn 3, france, option 13 */
#endif

#ifdef VN               /* vn */
#define VN2             /* vn 2, france, option 21 */
#define VN3             /* vn 3, france, option 22 */
#endif

#ifdef BC303            /* bellcore tr-303 */
#define BC303TMC        /* bellcore tr-303, tmc , option 25 */
#define BC303CSC        /* bellcore tr-303, csc, option 26 */
#endif

/* features, choose none or more */

/*#define ISDN_SEGMENT  1   message segmentation and reassembly option */
/*#define ISDN_BRI      1   basic rate interface option */
#define ISDN_PRI      1   /* primary rate interface option */
/*#define ISDN_ROUTE    1   routing procedures provided */
/*#define ISDN_OVERLAP  1   overlap sending/receiving provided */
/*#define ISDN_UTU      1   user to user procedures provided */
/*#define ISDN_FACILITY 1   facility procedures provided */
/*#define ISDN_SRV      1   service procedures provided */
/*#define ISDN_NFAS     1   nfas procedures provided */
/*#define ISDN_SUSPEND  1   suspend/resume procedures provided */
/*#define ISDN_HOLD     1   hold/retrieve procedures provided */
/*#define DECODCDSET    1   decode network and user specific codeset 6 and 7 */
                         /* elements into individual elements vs. string */
#define MF_IN         1  /* For MF purposes */

#ifdef NETSIDE 
#define ISDN_PTMPT    1  /* ISDN Point to Multipoint. */
#endif /* NETSIDE */

#ifdef Q932
#ifndef ISDN_HOLD
#define ISDN_HOLD     1  /* hold procedures provided */
#endif
#ifndef ISDN_FACILITY
#define ISDN_FACILITY 1  /* facility procedures provided */
#endif
#endif

#ifdef NI2
/*#define NI2_BCAS          NI2 B channel service procedure */
/*#define NI2_TREST         NI2 TREST timer */
/*#define IN_NW_NMB         pass network number (station id) to call control */
#endif 

/*#define ISDN_RLNK         send STATENQ msg after date link reestablishment */
/*#define ISDN_SNDRSTIND    send IntRstInd to layer 4 after recving RST msg */
/*#define IN_RSCIND         send resource indication to QW */
/*#define IN_INSRV_ALARM    send alarm to LM when a D chan becomes IN SRV */

/*#define IN_FTHA           Enables SHT interface for Q.930/Q.931 */

/* data link interface type, choose one */
/* if applicable, must agree with lapb, lapd, lapb and lapd, basic frame
   relay or extended frame relay data link interface type */

#define DATINT1      /* data link interface 1 */
/* #define DATINT2       data link interface 2 */

#endif /* IN */

#ifdef ZQ       /* PSF - Q.931 (FT/HA) */
/**************************************************************************
   PSF - Q.931 parameters
**************************************************************************/

#define ISDN_3_10_PLUS      /* Q.930/Q.931 code version 3.11 and above */
/* management interface, lzq */

/* #define LCZQMILZQ        PSF-ISDN loosely coupled to stack manager */

#endif /*ZQ*/


#ifdef FN       /* Q.933/LMI */
/**************************************************************************
   Q.933/LMI parameters
**************************************************************************/

/* product version, choose one */
 

/* interfaces */

/* upper interface, Q.933 network, choose none or both */

/* #define LCUICMINT      loosely coupled, Q.933/Q.930 common functions */
/* #define LCFNUIFNT      loosely coupled, Q933 network layer */
#ifdef LCFNUIFNT
#define LCANLIFNT        /* Loosely coupled layer4 to FN */
#endif

/* lower interface, data link, choose none or more */

/* Select one or both */
/* #define LCFRLIFRD      loosely coupled, any layer to FR layer, 
                          common functions */
/* #define LCFRUIFRD      loosely coupled, layer 2 to any layer */

#ifdef LCFRUIFRD
#ifndef LCFR
#define LCFR              /* enable LCFR - loosely coupled flag */
#endif
#endif /* #ifdef LCFRUIFRD */

#ifdef LCFRLIFRD
#ifndef LCFR
#define LCFR              /* enable LCFR - loosely coupled flag */
#endif
#endif /* #ifdef LCFRLIFRD */

/* layer management options */

#define FN_LMINT3         /* FN uses LMINT3 code 
                           * If this flag is enabled, enable SMFN_LMINT3 
                           * in #ifdef SM section 
                           * If this flag is disabled, disable SMFN_LMINT3 
                           * in #ifdef SM section 
                           */
 
#ifdef LMINT3
#ifdef FN_LMINT3
#undef FN_LMINT3
#define FN_LMINT3 1
#endif /* FN_LMINT3 */
#endif /* LMINT3 */

/* #define LCFNMILFN      loosely coupled, layer management */
/* Also enable LCSMFNMILFN under #ifdef SM if SM to FN is to
 * be loosely coupled 
 */

/* Options chosen must be consistent with product delivered */


/* PVC MANAGEMENT PRODUCT SPECIFIC OPTIONS */
/* Select only if LMI procedures are to be enabled */
/* #define  FN_LMI         enable LMI product operation */
#ifdef FN_LMI
/* Enable procedures at the switch */
#ifndef NETSIDE
#define NETSIDE          /* network side options */
#endif /* #ifndef NETSIDE */
#ifdef NETSIDE
/* Select only if PVC multicast operation required */
#define FN_MCAST         /* Multcast procedures */
/* Enable the flag FN_MULTIPLE_LMI_ENTITIES if using PVCs that switch 
   across multiple cards */
#define FN_MULTIPLE_LMI_ENTITIES 
#endif /* #ifdef NETSIDE */
#endif /* #ifdef FN_LMI */


/* SIGNALLING PRODUCT SPECIFIC OPTIONS */
/* #define  FN_SIG        enable signalling product operation */
#ifdef FN_SIG

/* Select UNI signalling */
/* #define FN_UNI         Enable UNI signalling */
#ifdef FN_UNI

/* Select Q933 Case and Case B signalling procedures */
#define  FN_Q933SW     /* Enable Q.933 procedures */
#ifdef FN_Q933SW
/* Select NFAS procedures */
/* #define  FN_NFAS       Enable NFAS operation */
#define Q933 1
#endif /* #ifdef FN_Q933SW */

/* Select X36 signalling procedures */
#define  FN_X36     /* Enable X36 procedures */

#ifdef FN_X36
#define X36 1
#endif /* #ifdef FN_X36 */

/* Select FRF4 signalling procedures */
#define  FN_FRF4     /* Enable FRF4 procedures */
#ifdef FN_FRF4
#define FRF4 1
#endif /* #ifdef FN_FRF4 */

#endif /* #ifdef FN_UNI */
 
/* Select NNI signalling */
/* #define FN_NNI         Enable NNI signalling */
#ifdef FN_NNI
 
/* Select X76 signalling procedures */
#define  FN_X76        /* Enable X76 procedures */
#ifdef FN_X76
#define X76 1
#endif /* #ifdef FN_X76 */
 
/* Select FRF10 signalling procedures */
#define  FN_FRF10      /* Enable FRF10 procedures */
#ifdef FN_FRF10
#define FRF10 1
#endif /* #ifdef FN_FRF10 */
 
#endif /* #ifdef FN_NNI */

/* Enable User side procedures of UNI */
/* #define USRSIDE        user side */
/* Enable Network side procedures of UNI */
#ifndef NETSIDE
/* #define NETSIDE        network side */
#endif /* #ifndef NETSIDE */

/* Select to enable SAP routing procedures */
/* #define FN_ROUTE       routing used */

/* Select to enable call Accounting procedures */
/* #define FN_ACNT        Enable accounting code compilation */
#endif /* #ifdef FN_SIG */

/* Select following Debug option to enable message display */
/* #define FN_DBGMSGDSPLY  Enable outgoing and incoming message display */

/* Select Debug option to enable message decode or encode error display */
/* #define FN_DBGMSGERR    Enable message decode or encode error display */

#endif /* #ifdef FN */

#ifdef VF       /* V5 Integrated Layer 3 */
/**************************************************************************
   V5 Integrated Layer 3
**************************************************************************/

/* interfaces */

/* upper interface, choose none or more */

/* #define LCVFUIVFT     loosely coupled, v5 Integarted Layer 3*/

/* lower interface, data link, choose none or more */

/* #define LCVFLILVT    loosely coupled, data link layer */ 

/* management interface, lvf , choose none or more */

/* #define LCVFMILVF     loosely coupled, layer management */

/* product specific options */

/* side, choose one or more */

#define ACCESS_NETWORK      /* access network side */
#define LOCAL_EXCHANGE      /* local exchange side */

/* Variant Type */
#define V5_1                /* V5.1 Interface */
#define V5_2                /* V5.2 Interface */

#define V5_VER2             /* V5 Version 2 */
 
#endif  /* VF */


#ifdef NV       /* V5.X PSTN Network Layer */
/**************************************************************************
   V5.X PSTN Network Layer
**************************************************************************/

/* interfaces */

/* upper interface, isdn network, choose none or more */

/* #define LCNVUINVT    loosely coupled, v5.1 pstn network layer */

/* lower interface, data link, choose none or more */

/* #define LCNVLILVT    loosely coupled, data link layer */

/* management interface, llv , choose none or more */

/* #define LCNVMILNV    loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCNVLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCNVLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCNVLM          /* tightly coupled, layer management */
#define LCNVLM          /* loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* side, choose one or more */
/* must agree with options delivered */

#define ANSIDE      /* access network side */
/* #define LESIDE       local exchange side */

#define MF_NV        1 /* For MF purposes */
#define V5X            /* For MF purposes */
 
#endif


#ifdef CV       /* V5.X Control Protocol Layer */
/**************************************************************************
   V5.X Control Protocol Layer
**************************************************************************/

/* interfaces */

/* lower interface, data link, choose none or more */

/* #define LCCVLILVT     loosely coupled, data link layer */

/* management interface, llv , choose none or more */

/* #define LCCVMILCV     loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCNVLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCNVLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCNVLM          /* tightly coupled, layer management */
#define LCNVLM          /* loosely coupled, layer management */
#endif
#endif

/* product specific options */

#define V5_2            /* V5.2 */

/* side, choose one or more */
/* must agree with options delivered */

#define V5X            /* For MF purposes */
#define MF_NV        1 /* For MF purposes */
 
#endif /* CV */


#ifdef BV       /* V5.X BCC Protocol Layer */
/**************************************************************************
   V5.X BCC Protocol Layer
**************************************************************************/

/* interfaces */


/* layer management options */

/* Access Netwwork or a Local Exchange options */
/* Choose either one of both. */
/* #define LOCAL_EXCHANGE   The BCC should be compiled for Local Exchange */
/* #define ACCESS_NETWORK   The BCC should be compiled for Access Network */

/* #define LCBVUIBVT    loosely coupled, layer 3  BV -> Layer 4 */
/* #define LCBVLILVT    loosely coupled, data link layer BV -> LV*/
/* #define LCBVMILBV    loosely coupled, layer management */ 

/* product specific options */

#define V5_2            /* V5.2 */

/* side, choose one or more */
/* must agree with options delivered */

#define V5X            /* For MF purposes */
#define MF_NV        1 /* For MF purposes */
 
#endif /* BV */

#ifdef LK       /* V5.2 Link Control Protocol */

/* Interfaces */
/* Layer Management options */

/* #define LCLKLILVT     Loosely coupled data link layer lk->lk */
/* #define LCLKMILLK     Loosely coupled layer management. */

#endif /* LK */



#ifdef PV       /* V5.X Protection Protocol Layer */
/**************************************************************************
   V5.X Protection Protocol Layer
**************************************************************************/

/* interfaces */


/* layer management options */

/* Access Netwwork or a Local Exchange options */
/* Choose either one of both. */
#define LOCAL_EXCHANGE   /* The Protection should be compiled for Local Exchange */
#define ACCESS_NETWORK   /* The Protection should be compiled for Access Network */

/* #define LCPVLILVT     loosely coupled, data link layer PV -> LV*/
/* #define LCPVMILPV    loosely coupled, layer management */ 

/* product specific options */

#define V5_2            /* V5.2 */

/* side, choose one or more */
/* must agree with options delivered */

#define V5X            /* For MF purposes */
#define MF_PV        1 /* For MF purposes */
 
#endif /* PV */


#ifdef LV       /* LAPV5-DL Data Link Layer */
/**************************************************************************
   LAPV5-DL Data Link Layer
**************************************************************************/

/* interfaces */

/* upper interface, data link, choose none or more */

/* #define LCLVUILVT     loosely coupled, data link layer */

/* lower interface, evt, choose none or more */

/* #define LCLVLIEVT     loosely coupled, evt layer */

/* management interface, llv , choose none or more */

/* #define LCLVMILLV     loosely coupled, layer management */

/* debug mngmt interface, choose one or none, default is debug output disabled */

/* #define DBLVMILLV     debug output enabled for mngmt interface */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCLVLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCLVLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCLVLM          /* tightly coupled, layer management */
/* #define LCLVLM        loosely coupled, layer management */
#endif
#endif

/* product specific options */

#endif


#ifdef EV       /* LAPV5 Envelope Function Layer */
/**************************************************************************
   LAPV5 Envelope Function Layer
**************************************************************************/

/* interfaces */

#define BDVER2         /* in order to include mac.x file */

/* upper interface, evt , choose none or more */

/* #define LCEVUIEVT     loosely coupled, evt layer */

/* lower interface, mac, choose none or more */

/* #define LCEVLIMAC     loosely coupled, mac layer */

/* management interface, lev , choose none or more */

/* #define LCEVMILEV     loosely coupled, layer management */

/* debug mngmt interface, choose one or none, default is debug output disabled */

/* #define DBEVMILEV     debug output enabled for mngmt interface */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCLVLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCLVLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCLVLM          /* tightly coupled, layer management */
/* #define LCLVLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* #define EV_ISDN           isdn signalling is supported */
/* #define EV_TST_ISDN       isdn signalling acceptance test */

/* mac interface type, choose one */
/* if applicable, must agree with driver mac interface type */

#define MACINT1      /* mac link interface 1 */
/* #define MACINT5         mac link interface 5 */

#endif


#ifdef VM       /* V5 interface mac Layer */
/**************************************************************************
   V5 interface mac Layer
**************************************************************************/

/* interfaces */

#define MACVER2         /* in order to include mac.x file */

/* upper interface, mac , choose none or more */

/* #define LCVMUIMAC        loosely coupled, mac layer */

/* management interface, lmv , choose none or more */

/* #define LCVMMILVM        loosely coupled, layer management */

/* debug mngmt interface, choose one or none, default is debug output disabled */

/* #define DBVMMILVM       debug output enabled for mngmt interface */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCMVLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCVMLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCVMLM          /* tightly coupled, layer management */
/* #define LCVMLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* mac interface type, choose one */
/* if applicable, must agree with driver mac interface type */

#define MACINT1      /* mac link interface 1 */
/* #define MACINT5         mac link interface 5 */

#endif



#ifdef MV       /* V5 System Management  */
/**************************************************************************
   V5 System Management 
**************************************************************************/
 
/* interfaces */
 
/* interface to control protocol, lmv, choose none or more */
 
/* #define LCMVMILMV       loosely coupled, lmv layer */
 
/* interface to control protocol, lcv, choose none or more */
 
/* #define LCMVMILCV       loosely coupled, lcv layer */
 
/* interface to pstn, lnv, choose none or more */
 
/* #define LCMVMILNV       loosely coupled, lnv layer */
 
/* interface to bcc, lbv, choose none or more */
 
/* #define LCMVMILBV       loosely coupled, lbv layer */
 
/* interface to bcc, lpv, choose none or more */
 
/* #define LCMVMILPV       loosely coupled, lpv layer */
 
/* interface to bcc, llk, choose none or more */
 
/* #define LCMVMILLK       loosely coupled, llk layer */
 
/* interface to envelop function, lev, choose none or more */
 
/* #define LCMVMILEV       loosely coupled, lev layer */
 
/* management interface, ll1, choose none or more */
 
/* #define LCMVMILL1       loosely coupled, layer management */
 
/* layer management options */
 
/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */
 
/* product specific options */
 
/* Whether V5.1 system or V5.2 system. Choose one or both */
#define V5_1            /* V5.1 */
#define V5_2            /* V5.2 */
 
/* Whether AN side system or LE side system. Choose one or both */
#define V5_AN           /* V5.1 */
#define V5_LE           /* V5.2 */
 
#endif


#ifdef AS       /* q.saal */

/**************************************************************************
   ATM Q.SAAL parameters
**************************************************************************/

/* interfaces */

/* Q.SAAL Upper Interface */
/* #define ASD2     1       ASD (Q.2130) interface with bind confirm */
/* #define ASI2     1       ASI (Q.2140) interface with bind confirm */

/* AAL Upper Interface */
/* #define AALINT3  1       AAL upper interface with bind confirm*/

/* layer management options, choose none */
 
#ifndef LMINT2
#define LMINT2          /* layer management interface 2 */
#endif

/* #define AS_LMINT3       layer management interface 3.
                           If this flag is enabled, enable SMAS_LMINT3 
                           in #ifdef SM section 
                           If this flag is disabled, disable SMAS_LMINT3 
                           in #ifdef SM section.
                           This flag should be turned off for pre LMINT3
                           interface.
                         */

/* upper interface, data link, choose none or more */

/* #define LCASUIASD 1      loosely coupled, data link layer */

/* upper interface, Q.2110, choose none or more */

/* #define LCASUIASI 1      loosely coupled, Q.2110 layer */

/* lower interface, aal, choose none or more */

/* #define LCASLIAAL 1      loosely coupled, aal layer */

/* management interface, las, choose none or more */

/* #define LCASMILAS 1      loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCASLM 1        /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCASLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

/* #define TCASLM           tightly coupled, layer management */
/* #define LCASLM 1         loosely coupled, layer management */
#endif
#endif

/* interface flags, chosen automatically */

#ifdef LCASUIASD

#ifndef LCASD
#define LCASD 1            /* define LC flag for ASD interface */
#endif

#endif /* LCASUIASD */

#ifdef LCASUIASI

#ifndef LCASI
#define LCASI 1            /* define LC flag for ASI interface */
#endif

#endif /* LCASUIASI */

#ifdef LCASLIAAL

#ifndef LCAAL
#define LCAAL 1            /* define LC flag for AAL interface */
#endif

#endif /* LCASLIAAL */

#ifdef LCASMILAS
#ifndef LCLAS
#define LCLAS 1            /* define LC flag for layer management interface */
#endif
#endif /* LCASLILAS */

#if (LCASD || LCASI || LCAAL || LCASLM)

#ifndef LCATM
#define LCATM 1            /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* q.saal option to expose Q.2110 interface, choose one or none */

#define ASOPT_EXPOSE_Q2110 1 /* q.saal option to expose Q.2110 interface */

/* q.saal option to allow power-up robustness as defined in atmf/97-0216 */

#define AS_POWER_UP_ROBUST 1

/* q.saal option to compile UNI3.0 code*/
 
#define ASOPT_QSAAL1_2 1   /*   q.saal option to compile UNI3.0 code*/
 
/* q.saal option to compile UNI3.1 code*/
 
#define ASOPT_Q21x0 1     /*   q.saal option to compile UNI3.1 code*/
 
/* q.saal option to compile IDLE state of dlc */

#define ASOPT_IDLE_LINK 1 /* q.saal option to compile IDLE state of dlc */

/* type, chosen automatically */

#ifndef ATM
#define ATM 1              /* ATM stack */
#endif

#ifdef LMINT3
#ifdef AS_LMINT3
#undef AS_LMINT3
#define AS_LMINT3   1
#endif /* AS_LMINT3 */
#endif /* LMINT3 */

/*#define AS_FTHA        SHT interface flag. */

/*#define AS_RUG         product AS rolling upgrade enabled */

/* Rolling Upgrade compliance */

#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#error "Rolling upgrade feature available in CORE II only."
#endif /* TDS_CORE2 */ 
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

#ifdef AS_RUG
#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "AS_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
#endif /* AS_RUG */

#ifdef AS_RUG
#ifndef AS_FTHA
#error "AS_FTHA flag is mandatory for Rolling Upgrade. Please enable"
#endif /* AS_FTHA */
#endif /* AS_RUG */

#ifdef AS_RUG
#ifndef AS_LMINT3
#error "AS_LMINT3 flag is mandatory for Rolling Upgrade. Please enable"
#endif /* AS_LMINT3 */
#endif /* AS_RUG */

#ifdef AS_RUG
#ifndef ASD2
#error "ASD2 flag is mandatory for rolling upgrade. Please enable"
#endif /* ASD2 */
#endif /* AS_RUG */

#ifdef AS_RUG
#ifndef ASI2
#error "ASI2 flag is mandatory for rolling upgrade. Please enable"
#endif /* ASI2 */
#endif /* AS_RUG */

#ifdef AS_RUG
#ifndef ASDV1
#define ASDV1        /* Upper interface version 1.0 */ 
#endif
#ifndef ASIV1
#define ASIV1        /* Upper interface version 1.0 */ 
#endif
#endif /* AS_RUG */

/* use old bind method */
/* #define AS_OLD_BIND   1*/

#endif /* AS */

#ifdef PN       /* PNNI */

/**************************************************************************
   ATM PNNI parameters
**************************************************************************/
#undef PN
#define PN 1

/* Q.93B Upper Interface */
/* #define AMT2 1          AMT2 interface with bind confirm */

/* PNNI Upper Interface */
/* #define PCI2 1          PCI2 interface with bind confirm  */

/* AAL Upper Interface */
/* #define AALINT3  1       AAL upper interface with bind confirm*/

/*** Interface Backward Compatibility Options ***/
/* #define PN_LMINT3       PN uses LMINT3 code  */
                        /* If this flag is enabled, enable SMPN_LMINT3 
                         * in #ifdef SM section 
                         * If this flag is disabled, disable SMPN_LMINT3 
                         * in #ifdef SM section 
                         *
                         * This flag should be turned off for pre LMINT3
                         * interface.
                         */

#ifdef LMINT3
#ifdef PN_LMINT3
#undef PN_LMINT3
#define PN_LMINT3 1
#endif /* PN_LMINT3 */
#endif /* LMINT3 */

/* layer management options, choose none */
 
#ifndef LMINT2
#define LMINT2          /* layer management interface 2 */
#endif

/* PGL capable pnni */

/* #define PGLCAPABLE   1    PGL capable pnni */

/* Border Node capable pnni */

/* #define BORDERNODE   1    Border Node capable pnni */

/* Specify Port number in DTL or not */

/* #define SPEC_PORT_IN_DTL   1   Specify port in DTL ?? */

/* lower interface, amt, choose none or more */

/* #define LCPNLIAMT 1     loosely coupled, amt layer */

/* lower interface, aal, choose none or more */

/* #define LCPNLIAAL 1     loosely coupled, aal layer */

/* upper interface, pci, choose none or more */

/* #define LCPNUIPCI 1      loosely coupled, pci layer */

/* management interface, lpn, choose none or more */

/* #define LCPNMILPN 1      loosely coupled, layer management */

/* interface flags, chosen automatically */

#ifdef LCPNLIAMT

#ifndef LCAMT
#define LCAMT 1            /* define LC flag for AMT interface */
#endif

#endif /* LCPNLIAMT */

#ifdef LCPNLIAAL

#ifndef LCAAL
#define LCAAL 1            /* define LC flag for AAL interface */
#endif

#endif /* LCPNLIAAL */

#ifdef LCPNUIPCI

#ifndef LCPCI
#define LCPCI 1            /* define LC flag for PCI interface */
#endif

#endif /* LCPNLIPCI */

#ifdef LCPNMILPN
#ifndef LCLPN
#define LCLPN 1            /* define LC flag for AAL interface */
#endif

#endif /* LCPNLILPN */

#if (LCAMT || LCAAL || LCLPN || LCPCI)

#ifndef LCATM
#define LCATM 1            /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* debugging flags: compiles in dump functions */
/* #define DBGTDSPN  1       */            

/* type, chosen automatically */

/* #define HASH_OPEN_ADDRESSING 1     use hash function with open addressing */

#ifndef ATM
#define ATM 1              /* ATM stack (Q.93B, Q.SAAL, UME, AAL) */
#endif

#ifndef SIG_PNNI
#define SIG_PNNI       1 
#define DEF_SIG_PNNI      1
#endif

#endif /* PN */


#ifdef PU       /* ATM PNNI User */
/**************************************************************************
   ATM PNNI User parameters
**************************************************************************/
#undef PU
#define PU 1

/* interfaces */

/* lower interface, AMT, choose none or more */
 
/* #define LCPULIAMT     loosely coupled, signalling lower layer */
 
/* lower interface, data link, choose none or more */
 
#ifdef LCPULIAMT
 
#ifndef LCAMT
#define LCAMT 1
#endif
 
#endif  /* LCPULIAMT */

/* lower interface, data link, choose none or more */

/* #define LCPULIPCI     loosely coupled, dummy pnni user lower layer */

#ifdef LCPULIPCI

#ifndef LCPCI
#define LCPCI 1
#endif

#endif  /* LCPULIPCI */

#if (LCPCI)

#ifndef LCATM
#define LCATM 1
#endif

#endif  /* LCPCI */

/* type, chosen automatically */

#ifndef ATM
#define ATM             /* for message functions */
#endif

#ifndef SIG_PNNI
#define SIG_PNNI       1 
#define DEF_SIG_PNNI      1
#endif

#endif


#ifdef AM       /* Q.93B */
/**************************************************************************
   Q.93B parameters
**************************************************************************/

/* switch variants, choose none or more, default is ATM Forum UNI v3.0/1 */
/* must agree with options delivered */

/* Q.2931 option */
 
/* #define Q2931                  ITU-T Q.2931 & Q.2971 code enabled */

#ifndef Q2931
#define DEF_Q2931         0
#else
#define DEF_Q2931         1
#endif /* Q2931 */
 
/* PNNI Signalling options */
 
/* #define SIG_PNNI               PNNI Signalling code enabled */

#ifndef SIG_PNNI
#define DEF_SIG_PNNI      0
#else
#define DEF_SIG_PNNI      1
#endif /* SIG_PNNI */

/* AINI Signalling options */
 
/* #define SIG_AINI               AINI Signalling code enabled */

#ifndef SIG_AINI
#define DEF_SIG_AINI      0
#else
#define DEF_SIG_AINI      1
#endif /* SIG_AINI */

/* UNI 4.0 option */

/* #define UNI40                  ATM Forum UNI ver 4.0 enabled */
 
#ifndef UNI40
#define DEF_UNI40      0
#else
#define DEF_UNI40      1

/* #define LIJ             Leaf Initiated Join capabiltity */

#ifndef LIJ
#define DEF_LIJ          0
#else
#define DEF_LIJ          1
#endif /* LIJ */

#endif /* UNI40 */

/* IISP - UNI 3.0 options */

/* #define IISP_UNI30             IISP based on UNI 3.0 */

#ifndef IISP_UNI30
#define DEF_IISP_UNI30    0
#else
#define DEF_IISP_UNI30    1
#endif /* IISP_UNI30 */

/* IISP - UNI 3.1 options */

/* #define IISP_UNI31             IISP based on UNI 3.1 */

#ifndef IISP_UNI31
#define DEF_IISP_UNI31    0
#else
#define DEF_IISP_UNI31    1
#endif /* IISP_UNI31 */


/* layer management options, choose none */
 
#ifndef LMINT2
#define LMINT2          /* layer management interface 2 */
#endif

/* upper interface, choose one or none, default is tightly coupled */

/* #define LCAMUIAMT       loosely coupled upper layer */

/* lower interface, choose one or none, default is tightly coupled */

/* #define LCAMLIASD       loosely coupled data link layer */

/* management interface, lam, choose none or more */

/* #define LCAMMILAM       loosely coupled, layer management */

#ifdef LCAMMILAM
#ifdef LCLAM
#undef LCLAM
#endif
#define LCLAM 1         /* define LC flag for LAM interface */
#endif /* LCAMMILAM */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */
#ifndef LCLAM
#define LCLAM     1    /* loosely coupled, layer management */
#endif
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* Nothing to choose in Q.93B for TC flag!  */
#endif
#endif

/* interface flags, chosen automatically */

#ifdef LCAMUIAMT

#ifndef LCAMT    
#define LCAMT      1    /* define LC flag for AMT interface */
#endif

#endif /* LCAMUIAMT */

#ifdef LCAMLIASD

#ifndef LCASD
#define LCASD  1    /* define LC flag for ASD interface */
#endif

#endif /* LCAMLIASD */

#if (LCAMT || LCASD || LCLAM)

#ifndef LCATM
#define LCATM      1    /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* side, choose one or more */
/* must agree with options delivered */

#define USRSIDE      /*user side,    option 1 or option 3 */
#define NETSIDE      /*network side, option 2 or option 3 */


/* Option to support Signalling of AAL2 Parameters for Q2931, UNI40
   or PNNI (One of these must be selected for this option) */

/* #define AMOPT_AAL2    Option to support Signalling of AAL2 Parameters */


/* Option to support MDCR for UNI40, PNNI or AINI (One of these must be
 * selected for this option) */

/* #define DEF_ADD_MDCR      1    Option to support MDCR */


/* Option to support Trillium CORE2 FT/HA */

/* #define AM_FTHA           1    Option to support CORE2 FT/HA */

/* Option to support soft PVC for PNNI or AINI (One of these must be
 * selected for this option) */

/* #define SPVC_FR           1    Option to support soft PVC */

/* Option to send STATUS on optional IE error */
/* #define AMOPT_STAT_ON_OPT_ELEM_ERR 1  Send STATUS on optional IE error */
 
#ifdef AMOPT_STAT_ON_OPT_ELEM_ERR
/* #define AM_STAT_ON_OPT_ELEM_ERR 1  Send STATUS on optional IE error */
#endif /* AMOPT_STAT_ON_OPT_ELEM_ERR */



/* type, chosen automatically */

#ifndef ATM
#define ATM 1              /* ATM stack */
#endif



/* defines for message partial decoding */
/* #define AMOPT_PART_MSG_DEC  1  Enable partial decoding */

#ifdef AMOPT_PART_MSG_DEC
#define AM_PART_MSG_DEC  1  /* Enable partial decoding */
#else
#define AM_PART_MSG_DEC  0  /* Disable partial decoding */
#endif /* AMOPT_PART_MSG_DEC */


/* accounting enable option */
/* #define AM_ACNT         enable accounting by Q.93B */
 
#ifndef AM_ACNT
#define DEF_AM_ACNT      0
#else
#define DEF_AM_ACNT      1
#endif /* AM_ACNT */


/* Option to enable routing feature between SAPs */
/* #define AMOPT_ROUTING */
 
#ifdef AMOPT_ROUTING 
#define DEF_AMOPT_ROUTING     1
#else /* AMOPT_ROUTING */
#define DEF_AMOPT_ROUTING     0
#endif /* AMOPT_ROUTING */ 


/* Option to enable calling party number insertion feature */
/* #define AMOPT_CPTYINS     */

#ifdef AMOPT_CPTYINS 
#define DEF_AMOPT_CPTYINS     1
#else /* AMOPT_CPTYINS */
#define DEF_AMOPT_CPTYINS     0
#endif /* AMOPT_CPTYINS */ 


/* Option to avoid copying of message buffer before
 * decoding incoming message, if message buffer implementation
 * is such that whole message can be accessed same as contiguous
 * array of U8
 * Same is also true for encode side
 */
/* #define AMOPT_SINGLE_DBUF_MSG    */
 
#ifdef AMOPT_SINGLE_DBUF_MSG
#define DEF_AMOPT_SINGLE_DBUF_MSG  1
#else /* AMOPT_SINGLE_DBUF_MSG */
#define DEF_AMOPT_SINGLE_DBUF_MSG  0
#endif /* AMOPT_SINGLE_DBUF_MSG */
 

/* Option to avoid following checks for outgoing calls 
 * (AmtXXXReq, AmtXXXRsp primitives)
 * You can turn this flag on if you are sure that the
 * layer 4 is reliable enough to avoid following error
 * checks
 * 1. Skip checking enumerated value associated with
 *    each token in AmAllPdu received from layer4.
 * 2. Check if there is mismatch in pres flag of token
 *    and token's default value.
 */

/* #define AMOPT_XTRACHECKS     */
 
#ifdef AMOPT_XTRACHECKS
#define DEF_AMOPT_XTRACHECKS 1
#else
#define DEF_AMOPT_XTRACHECKS 0
#endif /* AMOPT_XTRACHECKS */
 

/* Option to use SAddMsgRef system service call instead of
 * SCpyMsgMsg call to make a copy of SETUP message for 
 * retransmission purpose when timer T303 expires.
 *
 * For details, refer System Services Service Definition 
 * documentation
 *
 * WARNING :- Please make 100% sure that your SAddMsgRef
 * implementation does not do another copy before turning
 * on this flag, otherwise performance will degrade.
 */
/* #define AMOPT_MSGREFIMPLTD  */
 

/* Optional status handling, call not released on implementation 
 * dependent conditions. It  gives status confirm to Service user, 
 * irrespective of the cause. Service user is responsible to decide
 * whether to release the call if optional Ie is not implemented down
 * the line.
 */
/* #define AMOPT_EXPOSE_STATHNDL  Optional status handling, call not released 
                                * on implementation dependent conditions 
                                */


 /* Option to enable the IISP user
 * side also to allocate a VCC. If not
 * enabled then only the network
 * side for the IISP can allocate the
 * VCC, as per the specifications
 */

/* #define AMOPT_IISP_USRALLOCVCC  */


/* interfaces */


/* LAM Interface options */
/*#define AM_LMINT3 */              /* AM uses LMINT3 code                         * 
                                    * If this flag is enabled, enable SMAM_LMINT3 * 
                                    * in #ifdef SM section                        */
#ifdef LMINT3
#ifdef AM_LMINT3
#undef AM_LMINT3
#define AM_LMINT3         1
#endif 
#endif


/* AMT Interface options */


/* Option to share memory between service user and
 * service provider (Q.93B)
 */
/*  #define AMTOPT_ALLPDUSHM   */


/* Option to implement Restart Response at the
 * AMT Interface, The Layer4 will have to generate
 * AmtRstRsp if this flag is turned on
 */
/*  #define AMTOPT_RSTRSP  */


/* AMT2 flag needs to be defined to enable
 * the bind confirm primitive at AMT interface
 * This enables acknowledgement of AmtBndReq
 * Primitive
 * Also with this option an additional parameter
 * is needed for the AmtStaReq and AmtStaCfm
 * Primitives to implement local status enquiry.
 */
/* #define AMT2    1 */


/* ASD Interface Options */
/* #define ASD2  1 */                   /* Use ASD Interface with Bind Confirm implemented */
 
#endif /* AM */


#ifdef ZM       /* PSF - Q.93B (FT/HA) */
/**************************************************************************
   PSF - Q.93B parameters
**************************************************************************/
#undef ZM
#define ZM 1

/******************* section to be changed by CUSTOMERS ******************/

/* management interface, lzm */

/* #define LCZMMILZM           loosely coupled, layer management */

/* The following flag must be turned-on if the customer chooses to
   implement it's own packing-unpacking functions for update messages */

/* #define CUSTENV */

/* Note : Make sure that the flag AM_LMINT3 in #ifdef AM section 
          and SMAM_LMINT3 in #ifdef SM section above as well as
          flag LMINT3 above are also turned-on */

#endif /* ZM */


#ifdef EC       /* ATM LAN Emulation Client (LEC) */

/**************************************************************************
   ATM LAN Emulation Client (LEC) parameters
**************************************************************************/

/* interfaces */

/* layer management options, choose none */
 
#ifndef LMINT2
#define LMINT2          /* layer management interface 2 */
#endif

/* upper interface, choose one or none, default is tightly coupled */

/* #define LCECUIECM        loosely coupled upper layer */

/* debug upper interface, choose one or none, default is disabled */

/* #define DBECUIECM     debug output enabled for upper interface */

/* lower Q.93B interface, choose one or none, default is tightly coupled */

/* #define LCECLIAMT     loosely coupled data link layer */

/* debug lower Q.93B interface, choose one or none, default is disabled */

/* #define DBECLIAMT     debug output enabled for lower interface */

/* lower AAL interface, choose one or none, default is tightly coupled */

/* #define LCECLIAAL     loosely coupled data link layer */

/* debug lower AAL interface, choose one or none, default is disabled */

/* #define DBECLIAAL     debug output enabled for lower interface */

/* management interface, lec, choose none or more */

/* #define LCECMILEC     loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCECLM     1    /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCECLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

/* #define TCECLM           tightly coupled, layer management */
#define LCECLM  1       /* loosely coupled, layer management */
#endif
#endif

/* debug mngmt interface, choose one or none, default is debug output disabled */

/* #define DBECMILEC     debug output enabled for mngmt interface */

/* interface flags, chosen automatically */

#ifdef LCECUIECM

#ifndef LCECM    
#define LCECM      1    /* define LC flag for ECM interface */
#endif

#endif /* LCECUIECM */

#ifdef LCECLIAMT

#ifndef LCAMT    
#define LCAMT      1    /* define LC flag for AMT interface */
#endif

#endif /* LCECLIAMT */

#ifdef LCECLIAAL

#ifndef LCAAL
#define LCAAL  1    /* define LC flag for AAL interface */
#endif

#endif /* LCECLIAAL */

#if (LCECM || LCAMT || LCAAL || LCECLM)

#ifndef LCATM
#define LCATM      1    /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* type, chosen automatically */

#ifndef ATM
#define ATM 1              /* ATM stack */
#endif

/* #define EC_PROXY               enable proxy interface */

/* #define EC_SRC_ROUTE           enable source routing */

/* #define EC_SRC_LEARN           enable source learning */

/* #define EC_GEN_NARPREQ         enable NARP request generation */

#endif /* EC */

#ifdef ES       /* ATM LAN Emulation Services (LE Services) */

/**************************************************************************
   ATM LAN Emulation Services (LE Services) parameters
**************************************************************************/

/* interfaces */

/* layer management options, choose none */
 
#ifndef LMINT2
#define LMINT2          /* layer management interface 2 */
#endif

/* lower Q.93B interface, choose one or none, default is tightly coupled */

/* #define LCESLIAMT     loosely coupled Q.93B layer */

/* debug lower Q.93B interface, choose one or none, default is disabled */

/* #define DBESLIAMT     debug output enabled for lower Q.93B interface */

/* lower AAL interface, choose one or none, default is tightly coupled */

/* #define LCESLIAAL     loosely coupled AAL layer */

/* debug lower AAL interface, choose one or none, default is disabled */

/* #define DBESLIAAL     debug output enabled for lower AAL interface */

/* management interface, les, choose none or more */

/* #define LCESMILES     loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCESLM     1    /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCESLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

/* #define TCESLM           tightly coupled, layer management */
#define LCESLM  1       /* loosely coupled, layer management */
#endif
#endif

/* debug mngmt interface, choose one or none, default is debug output disabled */

/* #define DBESMILES     debug output enabled for mngmt interface */

/* interface flags, chosen automatically */

#ifdef LCESLIAMT

#ifndef LCAMT    
#define LCAMT      1    /* define LC flag for AMT interface */
#endif

#endif /* LCESLIAMT */

#ifdef LCESLIAAL

#ifndef LCAAL
#define LCAAL  1    /* define LC flag for AAL interface */
#endif

#endif /* LCESLIAAL */

#if (LCAMT || LCAAL || LCESLM)

#ifndef LCATM
#define LCATM      1    /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* type, chosen automatically */

#ifndef ATM
#define ATM 1              /* ATM stack */
#endif

#endif /* ES */

#ifdef UM       /* ume */

/**************************************************************************
   ATM UME layer parameters
**************************************************************************/

/* interfaces */

/* layer management options, choose none */
 
#ifndef LMINT2
#define LMINT2          /* layer management interface 2 */
#endif

/* upper interface, ume, choose none or more */

/* #define LCUMUIUME 1      loosely coupled, ume layer */

/* lower interface, aal, choose none or more */

/* #define LCUMLIAAL 1      loosely coupled, aal layer */

/* management interface, lum, choose none or more */

/* #define LCUMMILUM 1      loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCUMLM 1        /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCUMLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

/* #define TCUMLM           tightly coupled, layer management */
/* #define LCUMLM 1         loosely coupled, layer management */
#endif
#endif

/* interface flags, chosen automatically */

#ifdef LCUMUIUME

#ifndef LCUME    
#define LCUME 1         /* define LC flag for UME interface */
#endif

#endif /* LCUMUIUME */

#ifdef LCUMLIAAL

#ifndef LCAAL
#define LCAAL 1         /* define LC flag for AAL interface */
#endif

#endif /* LCUMLIAAL */

#if (LCUME || LCAAL || LCUMLM)

#ifndef LCATM
#define LCATM 1         /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* debug upper interface, choose one or none */

/* #define DBUMUIUME 1         debug ume upper interface */

/* debug lower interface, choose one or none */

/* #define DBUMLIAAL 1         debug ume lower interface */

/* ume option to poll remote (ATMF 3.0, 4.7.7), choose one or none */

/* #define UMOPT_POLL_REMOTE   ume option to poll remote (ATMF 3.0, 4.7.7) */

/* type, chosen automatically */

#ifndef ATM
#define ATM 1              /* ATM stack */
#endif

#endif /* UM */

#ifdef MU       /* ume user */

/**************************************************************************
   UME User parameters
**************************************************************************/

/* interfaces */

/* layer management options, choose none */
 
#ifndef LMINT2
#define LMINT2          /* layer management interface 2 */
#endif

/* lower interface, ume, choose none or more */

/* #define LCMULIUME 1      loosely coupled, ume service interface */

/* interface, choose one or none */
 
/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCMULM 1        /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCMULM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCMULM          /* tightly coupled, layer management */
/* #define LCMULM 1         loosely coupled, layer management */
#endif
#endif

/* interface flags, chosen automatically */

#ifdef LCMULIUME

#ifndef LCUME     
#define LCUME 1         /* define LC flag for UME interface */
#endif

#endif /* LCMULIUME */

#if (LCUME)

#ifndef LCATM
#define LCATM 1         /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* debug lower interface, choose one or none */

/* #define DBMULIUME 1      debug stack manager lower interface */

/* type, chosen automatically */

#ifndef ATM
#define ATM 1           /* ATM stack */
#endif

#endif /* MU */

#ifdef IM       /* ime */

/**************************************************************************
   ATM IME layer parameters
**************************************************************************/

/* interfaces */

/* layer management options, choose none */
 
#ifndef LMINT2
#define LMINT2          /* layer management interface 2 */
#endif

/* AAL Upper Interface */
/* #define AALINT3  1       AAL upper interface with bind confirm*/

/* lower interface, aal, choose none or more */

/* #define LCIMLIAAL 1      loosely coupled, aal layer */

/* management interface, lim, choose none or more */

/* #define LCIMMILIM 1      loosely coupled, layer management */

/* #define IM_LMINT3        new management interface. turning off 
                            requires SMIM_LMINT3 flag also to be 
                            turned off in #ifdef SM section */


/* product specific options */

/* #define IMOPTS_AUTOCFG_OPTION 1   Auto-Configuration feature */
     
/* #define IMOPTS_SEL_ADDR_REG   1   Selective Address Reg feature */

/* #define IMOPTS_ADDR_AUTH      1   Address Authentication feature */

/* interface flags, chosen automatically
 */
#ifdef LCIMLIAAL
#ifdef LCAAL
#undef LCAAL
#endif
#define LCAAL 1         /* define LC flag for AAL interface */
#endif /* LCIMLIAAL */

#ifdef LCIMMILIM
#ifdef LCLIM
#undef LCLIM
#endif
#define LCLIM 1         /* define LC flag for LIM interface */
#endif /* LCIMMILIM */

#ifdef LMINT3
#ifdef IM_LMINT3
#undef IM_LMINT3
#define IM_LMINT3 1     /* define LMINT3 flag for LIM interface */
#endif /* IM_LMINT3 */
#endif /* LMINT3 */

#if (LCLIM || LCAAL)
#ifdef LCATM
#undef LCATM
#endif
#define LCATM 1         /* define LC flag for ATM stack */
#endif

/* type, chosen automatically */

#ifndef ATM
#define ATM 1              /* ATM stack */
#endif

#endif /* IM */




#ifdef PA

/**************************************************************************
   Protocol Layers Over ATM (PLOA) parameters
**************************************************************************/

/* interfaces */

/* upper interface, choose one or none, default is tightly coupled */

/* #define LCPAUICIP     loosely coupled upper layer (CIP user) */

/* #define LCPAUIECM     loosely coupled upper layer (ECM user) */

/* #define LCPAUIMPA     loosely coupled upper layer (MPA user) */

/* lower Q.93B interface, choose one or none, default is tightly coupled */

/* #define LCPALIAMT     loosely coupled data link layer */

/* lower AAL interface, choose one or none, default is tightly coupled */

/* #define LCPALIAAL     loosely coupled data link layer */

/* lower PXY interface, choose one or none, default is tightly coupled */

/* #define LCPALIPXY      loosely coupled proxy provider */

/* management interface, lec, choose none or more */

/* #define LCPAMILPA     loosely coupled, layer management */

/* ARI interface, choose none or more */

/* #define LCPALIARI     loosely coupled, layer management */

/* interface flags, chosen automatically */

#ifdef LCPAUICIP

#ifndef LCCIP    
#define LCCIP      1    /* define LC flag for CIP interface */
#endif

#endif /* LCPAUICIP */

#ifdef LCPAUIECM

#ifndef LCECM    
#define LCECM      1    /* define LC flag for ECM interface */
#endif

#endif /* LCPAUIECM */

#ifdef LCPAUIMPA
 
#ifndef LCMPA
#define LCMPA      1    /* define LC flag for MPA interface */
#endif

#endif /* LCPAUIMPA */

#ifdef LCPALIAMT

#ifndef LCAMT    
#define LCAMT      1    /* define LC flag for AMT interface */
#endif

#endif /* LCPALIAMT */

#ifdef LCPALIAAL

#ifndef LCAAL
#define LCAAL  1    /* define LC flag for AAL interface */
#endif

#endif /* LCPALIAAL */

#ifdef LCPALIPXY

#ifndef LCPXY
#define LCPXY  1    /* define LC flag for PXY interface */
#endif

#endif /* LCPALIPXY */

#ifdef LCPALIARI
#ifndef LCARI
#define LCARI  1    /* define LC flag for ARI interface */
#endif
#endif /* LCPALIARI */

#ifdef LCPAMILPA

#ifndef LCLPA
#define LCLPA  1    /* define LC flag for LPA interface */
#endif

#endif /* LCPAMILPA */

#if (LCCIP || LCECM || LCAMT || LCAAL || LCLPA)

#ifndef LCATM
#define LCATM      1    /* define LC flag for ATM stack */
#endif

#endif

/* Debug Flags ...Off by default */

/* #define DBPAUICIP         1       Debug Flag at CIP Interface */
/* #define DBPALIAMT         1       Debug Flag at AMT Interface */
/* #define DBPALIAAL         1       Debug Flag at AAL Interface */
/* #define DBPALIPXY         1       Debug Flag at PXY Interface */
/* #define DBPALIARI         1       Debug Flag at ARI Interface */
/* #define DBPAMILPA         1       Debug Flag at Management Interface */

/* product specific options */

/* type, chosen automatically */

#ifndef ATM
#define ATM 1              /* ATM stack */
#endif

/* Compile Time Flags for BndCfm at AMT and AAL Interface */
/* #define AMT2    1       Bind Confirm at AMT Interface */
/* #define AALINT3 1       Bind Confirm at AAL Interface */

/* PLOA modules */

/* enable if CIP module is included */
#ifdef PACP
#define PACP                      1     /* CIP module */
#endif /* PACP */

#ifdef PACP

#define PACP_CLIENT                  1     /* CIP Client */
/* #define PACP_SERVER               1     CIP Server */
/* #define PACP_CLIENT_SERVER        1     CIP Client Server */

#endif /* PACP */

/* enable if LEC module is included */
#ifdef PAEC
#define PAEC                      1     /* LEC module */
#endif /* PAEC */

/* enable if LES module is included */
#ifdef PAES
#define PAES                      1     /* LES module */
#endif /* PAES */

#ifdef PAES

#define PAES_LECS              1      /* Lan Emulation Configuration Server */
#define PAES_LES               1      /* Lan Emulation Server */
#define PAES_BUS               1      /* Broadcast & Unknown Server */
#define PAES_SMS               1      /* Selective Multicast Server */
#define PAES_COLOCATE_BUS      1      /* BUS is colocated with LES */

/* if PAES_SMS is defined and PAES_LES is not, define PAES_LES */
#ifdef PAES_SMS

#ifndef PAES_LES
#define PAES_LES                  1     /* With SMS..LES has to be there */
#endif /* PAES_LES */

#endif /* PAES_SMS */

#ifdef PAES_COLOCATE_BUS

#ifndef PAES_LES
#define PAES_LES                  1
#endif /* PAES_LES */

#ifndef PAES_BUS
#define PAES_BUS                  1     /* BUS has to be defined */
#endif /* PAES_BUS */

#endif /* PAES_COLOCATE_BUS */

#endif /* PAES */

/* enable if PPPoA module is included */
#ifdef PAMA
#define PAMA                1     /* PPPoA module */
#endif /* PAMA */

/* enable if MPC module is included */
#ifdef PAMC
#define PAMC                1     /* MPC module */
#endif /* PAMC */

/* enable if MPS module is included */
#ifdef PAMS
#define PAMS                1     /* MPS module */
#endif /* PAMS */

/* enable if NHS module is included */
#ifdef PANS
#define PANS                1     /* NHS module */

/* #define PAMP_PRC_VEN_EXTNS  1    Vendor Extension Processing */

#endif /* PANS */

/* enable if LLC module is included */
#ifdef PALC
#define PALC                1     /* LLC module */
#endif /* PALC */

#if (PAMS || PANS)

/* #define DPAMP_ENB_ASYNC_RTE_UPDATES     1  Asynchronous Route Updated */

#endif /* (PAMS || PANS) */

/* CIP components - enable one if PACP is enabled */

/* enable PAEC for PAMC */
#ifdef PAMC

#ifndef PAEC
#define PAEC                   1     /* LEC module */
#endif  /* PAEC */

#endif /* PAMC */

/* LEC components - enable as many if PAEC is enabled */

#ifdef PAEC

#define PAEC_SRC_ROUTE           /* enable source routing */

#define PAEC_SRC_LEARN           /* enable source learning */

#define PAEC_GEN_NARPREQ         /* enable NARP request generation */

#endif /* PAEC */


/* MPS Options */
#ifdef PAMS
#define PAMS_RTEUPD_OPT 1        /* Routing update option */
#endif /* PAMS */


/* signalling variants */

/* Q.2931 option */
 
/* #define Q2931                   ITU-T Q.2931 & Q.2971 code enabled */

#ifndef Q2931
#define DEF_Q2931         0
#else
#define DEF_Q2931         1
#endif /* Q2931 */
 
/* PNNI Signalling options */
 
/* #define SIG_PNNI               PNNI Signalling code enabled */

#ifndef SIG_PNNI
#define DEF_SIG_PNNI      0
#else
#define DEF_SIG_PNNI      1
#endif /* SIG_PNNI */

/* AINI Signalling options */
 
/* #define SIG_AINI               AINI Signalling code enabled */

#ifndef SIG_AINI
#define DEF_SIG_AINI      0
#else
#define DEF_SIG_AINI      1
#endif /* SIG_AINI */

/* UNI 4.0 option */

/* #define UNI40                  ATM Forum UNI ver 4.0 enabled */
 
#ifndef UNI40
#define DEF_UNI40         0
#else
#define DEF_UNI40         1

/* #define LIJ             Leaf Initiated Join capabiltity */

#ifndef LIJ
#define DEF_LIJ           0
#else
#define DEF_LIJ           1
#endif /* LIJ */

#endif /* UNI40 */

#endif /* PA */


#ifdef AL

/**************************************************************************
   Application layer - CIP interface service user
**************************************************************************/

/* interfaces */


/* lower interface, choose one or none, default is tightly coupled */

/* #define LCALLICIP      loosely coupled CIP interface */

/* interface flags, chosen automatically */

#ifdef LCALLICIP

#ifndef LCCIP    
#define LCCIP      1    /* define LC flag for CIP interface */
#endif

#endif /* LCALLICIP */

#if (LCCIP) 

#ifndef LCATM
#define LCATM      1    /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* type, chosen automatically */

#ifndef ATM
#define ATM 1           /* ATM stack */
#endif

#endif /* AL */



#ifdef EU

/**************************************************************************
   Application layer - ECM interface service user
**************************************************************************/

/* interfaces */


/* lower interface, choose one or none, default is tightly coupled */

/* #define LCEULIECM      loosely coupled ECM interface */

/* debug lower ECM interface, choose none or more */

/* #define DBEULIECM                debug lower ECM interface */

/* interface flags, chosen automatically */

#ifdef LCEULIECM

#ifndef LCECM    
#define LCECM      1    /* define LC flag for ECM interface */
#endif

#endif /* LCEULIECM */

#if (LCECM) 

#ifndef LCATM
#define LCATM      1    /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* type, chosen automatically */

#ifndef ATM
#define ATM 1           /* ATM stack */
#endif

#endif /* EU */



#ifdef MU

/**************************************************************************
   Application layer - MPA interface service user
**************************************************************************/

/* interfaces */


/* lower interface, choose one or none, default is tightly coupled */

/* #define LCMULIMPA     loosely coupled MPA interface */

/* interface flags, chosen automatically */

#ifdef LCMULIMPA

#ifndef LCMPA    
#define LCMPA      1    /* define LC flag for MPA interface */
#endif

#endif /* LCMULIMPA */

#if (LCMPA) 

#ifndef LCATM
#define LCATM      1    /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* type, chosen automatically */

#ifndef ATM
#define ATM 1           /* ATM stack */
#endif

#endif /* MU */


#ifdef SA       /* q.2140 */

/**************************************************************************
   Q.2140 SSCF parameters
**************************************************************************/

/* interfaces */

/* upper interface, sdt , choose none or more */

/*#define LCSAUISDT 1         loosely coupled, data link layer */

/* lower interface, asi, choose none or more */

/*#define LCSALIASI 1         loosely coupled, asi layer */

/* management interface, lsa, choose none or more */

/*#define LCSAMILSA 1         loosely coupled, layer management ,
                              turning off requires LCSMSAMILSA to be turned
                              off too */


/* flags should be turned off for backward compatibility */


#define SA_LMINT3          /* new management interface. turning off
                              requires SMSA_LMINT3 flag also to be
                              turned off in #ifdef SM section */


#define SDT2             /* new upper interface */

#define ASI2             /* new lower interface */

/*#define SA_OLD_BIND         use old bind method ( bind at config time) */

/*#define SA_USTA           enable unsolicited status gen by default */

/*#define SA_DEBUG          enable debug print generation by default */

/*#define SA_FTHA         enable FTHA support, requires ASI2 and SDT2 */



/************** section NOT to be changed by CUSTOMERS **********/

/* product specific options */

#ifdef LMINT3
#ifdef SA_LMINT3
#undef SA_LMINT3
#define SA_LMINT3 1
#endif
#endif

#ifdef LCSAUISDT

#ifndef LCSDT
#define LCSDT 1            /* define LC flag for SDT interface */
#endif

#endif /* LCSAUISDT */

#ifdef LCSALIASI

#ifndef LCASI
#define LCASI 1            /* define LC flag for ASI interface */
#endif

#endif /* LCSALIASI */

#if LCASI

#ifndef LCATM
#define LCATM 1            /* define LC flag for ATM stack */
#endif

#endif /* LCASI */

#ifdef LCSAMILSA

#ifndef LCLSA
#define LCLSA 1
#endif /* LCLSA */

#endif /* LCSAMILSA */


#endif /* SA */

#ifdef SM       /* stack manager */

/**************************************************************************
   Stack Manager parameters
**************************************************************************/

/* interfaces */

/* interface, choose one or none */

/* #define LCSMMSMILMS     stack manager loosely coupled to MOS */ 

/* #define LCSMNSMILNS     stack manager loosely coupled to NTSS */ 

/* #define LCSMRYMILRY     stack manager loosely coupled to relay */

/* #define LCSMAMMILAM     stack manager loosely coupled to Q.93B */ 

/* #define LCSMASMILAS     stack manager loosely coupled to Q.SAAL */ 

/* #define LCSMPNMILPN     stack manager loosely coupled to PNNI */ 

/* #define LCSMACMILAC     stack manager loosely coupled to AC */

/* #define LCSMECMILEC     stack manager loosely coupled to LEC */ 

/* #define LCSMESMILES     stack manager loosely coupled to LE Services */ 

/* #define LCSMUMMILUM     stack manager loosely coupled to UME */ 

/* #define LCSMIMMILIM     stack manager loosely coupled to IME */ 

/* #define LCSMSAMILSA     stack manager loosely coupled to Q.2140 */ 

/* #define LCSMSEMILSE     stack manager loosely coupled to SE */

/* #define LCSMSEMILSE     stack manager loosely coupled to SE */

/* #define LCSMISMILIS     stack manager loosely coupled to IS */

/* #define LCSMQIMILQI     stack manager loosely coupled to QI */

/* #define LCSMPQMILPQ     stack manager loosely coupled to PQ */

/* #define LCSMSDMILSD      stack manager loosely coupled to MTP-2 */

/* #define LCSMSNMILSN      stack manager loosely coupled to MTP-3 */

/* #define LCSMSPMILSP      stack manager loosely coupled to SCCP  */


/* #define LCSMSTMILST     stack manager loosely coupled to TCAP  */

/* #define LCSMIEMILIE     stack manager loosely coupled to INAP  */

/* #define LCSMQCMILQC     stack manager loosely coupled to CAP   */

/* #define LCSMTTMILTT     stack manager loosely coupled to TCAP over TCP/IP */

/* #define LCSMMAMILMA     stack manager loosely coupled to MAP  */

/* #define LCSMSIMILSI     stack manager loosely coupled to ISUP  */

/* #define LCSMTPMILTP     stack manager loosely coupled to TUP  */

/* #define LCSMSRMILSR     stack manager loosely coupled to MTP-3 Simple Router */

/* #define LCSMINMILIN     stack manager loosely coupled to Q.930/Q.931 */

/* #define LCSMXNMILXN     stack manager loosely coupled to network layer - XG, EI, XI, XE */

/* #define LCSMDAMILBD     stack manager loosely coupled to data link layer - ER, BR, BD, LD, LB */

/*#define LCSMD2MILD2     stack manager loosely coupled to data link layer - D2 */

/* #define LCSMAPMILAP     stack manager loosely coupled to APAD */

/* #define LCSMFRMILFR     stack manager loosely coupled to Frame Relay */

/* #define LCSMMEMILME     stack manager loosely coupled to data link layer - message exchange */

/* #define LCSMWDMILWD     stack manager loosely coupled to MTP-2 Wrapper */

/* #define LCSMWNMILWN     stack manager loosely coupled to MTP-3 Wrapper */

/* #define LCSMWIMILWI     stack manager loosely coupled to ISUP Wrapper */

/* #define LCSMWUMILWU     stack manager loosely coupled to TUP Wrapper */

/* #define LCSMWSMILWS     stack manager loosely coupled to SCCP Wrapper */

/* #define LCSMWCMILWC     stack manager loosely coupled to TCAP Wrapper */

/* #define LCSMBIMILBI     stack manager loosely coupled to B-ISUP  */

/* #define LCSMFMMILFM     stack manager loosely coupled to fault manager */

/* #define LCSMFNMILFN     stack manager loosely coupled to Q933 */

/* #define LCSMEVMILEV     stack manager loosely coupled to V5 Envelope Function */

/* #define LCSMLVMILLV     stack manager loosely coupled to LAPV */

/* #define LCSMNVMILNV     stack manager loosely coupled to V5.1 PSTN */

/* #define LCSMVFMILVF     stack manager loosely coupled to VF Layer  */

/* #define LCSMIXMILIX    stack manager loosely coupled to X.31 */

/* #define LCSMFAMILFA     stack manager loosely coupled to Fujitsu ALC/NTC/ATC  driver */

/* #define LCSMPLMILPL     stack manager loosely coupled to PMC Sierra LASAR driver */

/* #define LCSMAFMILAF     stack manager loosely coupled to FR-ATM interworking */

/* #define LCSMCVMILCV     stack manager loosely coupled to V5.X Control Protocol */

/* #define LCSMMVMILMV     stack manager loosely coupled to V5.X System Manager */

/* #define LCSMBVMILBV     stack manager loosely coupled to V5.X BCC Protocol */

/* #define LCSMLKMILLK         Stack manager loosely coupled to V5.2 Link 
                              Control protocol.  */

/* #define LCSMPVMILPV     stack manager loosely coupled to V5.X Protection Protocol */

/* #define LCSMCCMILCC      stack manager loosely coupled to CC  */

/* #define LCSMZCMILZC      stack manager loosely coupled to ZC  */

/* #define LCSMRMMILRM      stack manager loosely coupled to RM  */

/* #define LCSMZRMILZR      stack manager loosely coupled to ZR  */

/* #define LCSMRTMILRT      stack manager loosely coupled to RT  */

/* #define LCSMZSMILZS      stack manager loosely coupled to ZS  */

/* #define LCSMSFMILSF      stack manager loosely coupled to SF  */

/* #define LCSMXMMILXM      stack manager loosely coupled to XM  */

/* #define LCSMBWMILBW      stack manager loosely coupled to PSIF - B-ISUP */

/* #define LCSMIWMILIW      stack manager loosely coupled to PSIF - ISUP */
/* #define LCSMQWMILQW      stack manager loosely coupled to PSIF - ISDN */
/* #define LCSMAWMILAW      stack manager loosely coupled to PSIF - Q.93B */


/* #define LCSMZTMILZT         stack manager loosely coupled to PSF - TCAP */

/* #define LCSMZPMILZP         stack manager loosely coupled to PSF - SCCP */

/* #define LCSMZLMILZL          stack manager loosely coupled to PSF - AAL2 */

/* #define LCSMZNMILZN         stack manager loosely coupled to PSF-MTP3 (FT/HA) */

/* #define LCSMZVMILZV          stack manager loosely coupled to PSF-M3UA (FT/HA) */

/* #define LCSMDTMILDT         stack manager loosely coupled to LDF - TCAP */
 
/* #define LCSMDNMILDN          stack manager loosely coupled to MTP-3 LDF */

/* #define LCSMDPMILDP          stack manager loosely coupled to LDF-SCCP */

/* #define LCSMDVMILDV          stack manager loosely coupled to M3UA LDF */

/* #define LCSMZAMILZA      stack manager loosely coupled to PSF - RANAP */

/* #define LCSMZBMILZB      stack manager loosely coupled to PSF - GTP */

/* #define LCSMZIMILZI      stack manager loosely coupled to PSF-ISUP (FT/HA) */ 

/* #define LCSMZQMILZQ      stack manager loosely coupled to PSF-ISDN (FT/HA) */

/* #define LCSMZMMILZM      stack manager loosely coupled to PSF-Q.93B (FT/HA) */

/* #define LCSMSGMILSG      stack manager loosely coupled to System Manager */

/* #define LCSMSHMILSH      stack manager loosely coupled to System Agent */

/* #define LCSMMRMILMR      stack manager loosely coupled to Message Router */

/* #define LCSMPRMILPR      stack manager loosely coupled to MPC860SAR driver */

/* #define LCSMGNMILGN      stack manager loosely coupled to network service */
/* #define LCSMGTMILGT      stack manager loosely coupled to GTP */
/* #define LCSMGLMILGL      stack manager loosely coupled to GPRS LLC */
/* #define LCSMGGMILGG      stack manager loosely coupled to GPRS-BSSGP */
/* #define LCSMGSMILGS      stack manager loosely coupled to SNDCP */

/* #define LCSMHCMILHC      stack manager loosely coupled to H.323 Control */

/* #define LCSMHIMILHI      stack manager loosely coupled to TUCL */

/* #define LCSMHRMILHR      stack manager loosely coupled to RTP/RTCP */

/* #define LCSMIQMILIQ      stack manager loosely coupled to ISDN-Q.SAAL
                            Convergence Layer */

/* #define LCSMMGMILMG      stack manager loosely coupled to GCP stack */
/* #define LCSMZGMILZG      stack manager loosely coupled to PSF-GCP stack */
/* #define LCSMDGMILDG      stack manager loosely coupled to LDF-GCP stack */
/* #define LCSMDIMILDI      stack manager loosely coupled to LDF-ISUP */

/* #define LCSMLNMILLN      stack manager loosely coupled to MPLS-LDP(+CR) */

/* #define LCSMPAMILPA      stack manager loosely coupled to PLOA */ 

/* #define LCSMALMILAL      stack manager loosely coupled to AAL2 Signaling */

/* #define LCSMSBMILSB      stack manager loosley coupled to SCTP */

/* #define LCSMSOMILSO      stack manager loosley coupled to SIP */

/* #define LCSMITMILIT      stack manager loosley coupled to M3UA */

/* #define LCSMFPMILFP      stack manager loosley coupled to FP */

/* #define LCSMNFMILNF      stack manager loosley coupled to M3UA-NIF */

/* #define LCSMIDMILID      stack manager loosley coupled to IUA */

/* #define LCSMNDMILND      stack manager loosley coupled to IUA-NIF */

/* #define LCSMMZMILMZ      stack manager loosley coupled to M1UA-NIF */

/* #define LCSMSUMILSU      stack manager loosley coupled to SUA */
/* #define LCSMNPMILNP      stack manager loosley coupled to SUA-NIF */

/* #define LCSMMWMILMW      stack manager loosley coupled to M2UA */

/* #define LCSMNWMILNW      stack manager loosley coupled to M2UA-NIF */

/* #define LCSMMXMILMX      stack manager loosely coupled to M2PA */

/* #define LCSMRAMILRA      stack manager loosely coupled to RANAP */

/* #define LCSMGAMILGA      stack manager loosly coupled to BSSAP+ */

/* #define LCSMMKMILMK      stack manager loosly coupled to 3GPP-MAC */
/* #define LCSMMDMILMD      stack manager loosly coupled to MAC-HS */

/* #define LCSMRLMILRL      stack manager loosly coupled to 3GPP-RLC */

/* #define LCSMIBMILIB      stack manager loosly coupled to 3GPP-NBAP */

/* #define LCSMRRMILRR      stack manager loosly coupled to 3GPP-RRC */

/* #define LCSMRNMILRN      stack manager loosely coupled to RNSAP */

/* product specific options */

/* debug management interface, q.93b, choose none or more */

/* #define DBSMMILAM       debug output enabled, q.93b management interface */

/* debug management interface, q.saal, choose none or more */

/* #define DBSMMILAS       debug output enabled, q.saal management interface */

/* debug management interface, ume, choose none or more */

/* #define DBSMMILUM       debug output enabled, ume management interface */

/* debug management interface, LEC, choose none or more */

/* #define DBSMMILEC       debug output enabled, LEC management interface */

/* debug management interface, LE Services, choose none or more */
 
/* #define DBSMMILES       debug output enabled, LE Services management interface */

#ifdef LCSMINMILIN
#ifndef LCLIN
#define LCLIN  1    /* Define LC flag for LIN (Q.931 LM) interface */
#endif /* LCLIN */
#endif /* LCSMINMILIN */

#ifdef LCSMAMMILAM
#ifndef LCLAM
#define LCLAM  1    /* Define LC flag for LAM (Q.93B LM ) interface */
#endif 
#endif /* LCSMAMMILAM */

#ifdef LCSMPAMILPA
#ifndef LCLPA
#define LCLPA  1    /* define LC flag for LPA interface */
#endif
#endif /* LCSMPAMILPA */

#ifdef LCSMSTMILST
#ifdef LCLST
#undef LCLST
#endif
#define LCLST 1
#endif  /* LCSMSTMILST */

/* loosely coupled PNNI interface */
#ifdef LCSMPNMILPN
#ifdef LCLPN
#undef LCLPN
#endif
#define LCLPN 1
#endif  /* LCSMPNMILPN */

/* loosely coupled Q.SAAL interface */
#ifdef LCSMASMILAS
#ifdef LCLAS
#undef LCLAS
#endif
#define LCLAS 1
#endif  /* LCSMASMILAS */

/* loosely coupled Q.2140 interface */
#ifdef LCSMSAMILSA
#ifdef LCLSA
#undef LCLSA
#endif
#define LCLSA 1
#endif  /* LCSMSAMILSA */

/* loosely coupled LASAR management interface */
#ifdef LCSMPLMILPL
#ifdef LCLPL
#undef LCLPL
#endif
#define LCLPL 1
#endif /* LCSMPLMILPL */

/* loosely coupled IME interface */
#ifdef LCSMIMMILIM
#ifdef LCLIM
#undef LCLIM
#endif
#define LCLIM 1
#endif  /* LCSMIMMILIM */

#if (LCLPN || LCLSA || LCLPL || LCLIM)
#ifdef LCATM
#undef LCATM
#endif
#define LCATM 1
#endif

#if (LCLST)
#ifdef LCSS7
#undef LCSS7
#endif
#define LCSS7 1
#endif  /* LCLST */

#if (LCLSI)
#ifdef LCSS7
#undef LCSS7
#endif
#define LCSS7 1
#endif  /* LCLSI */

#if (defined(LCSMCCMILCC) || defined(LCSMRMMILRM) || defined(LCSMRTMILRT) || defined(LCSMSFMILSF) || defined(LCSMBWMILBW) || defined(LCSMIWMILIW) || defined(LCSMQWMILQW) || defined(LCSMAWMILAW))
#ifndef LCCMCC
#define LCCMCC        1
#endif
#ifndef LCATM
#define LCATM         1
#endif
#endif

/* loosely coupled LDF-MTP3 management interface */
#ifdef LCSMDNMILDN
#ifdef LCLDN
#undef LCLDN
#endif
#ifdef LCCM_ZNDN
#undef LCCM_ZNDN
#endif
#define LCLDN    1
#define LCCM_ZNDN 1
#endif  /* LCSMIMMILIM */


/* loosely coupled LDF-M3UA management interface */
#ifdef LCSMDVMILDV
#ifdef LCLDV
#undef LCLDV
#endif
#define LCLDV    1
#endif  /* LCSMDVMILDV */

/* product specific LMINT3 options */
/* enabled by default, can be turned off for backward compatibility
 * if SMXX_LMINT3 flag is turned off then XX_LMINT3 flag in #ifdef XX
 * section should also be turned off */

#define SMSD_LMINT3          /* LMINT3 interface flag for mtp2 */

#define SMSA_LMINT3          /* LMINT3 interface flag for Q.2140 */

#define SMSN_LMINT3          /* LMINT3 interface flag for mtp3 */

#define SMSP_LMINT3          /* LMINT3 interface flag for sccp */

#define SMST_LMINT3          /* LMINT3 interface flag for tcap */

#define SMSI_LMINT3          /* LMINT3 interface flag for isup */

/*#define SMAM_LMINT3           LMINT3 interface flag for Q.93B */

/* Note : The SMXX_LMINT3 flag MUST be turned-on, if using PSF (FT/HA) for a protocol
          layer. XX is the two letter prefix for the protocol layer product */

#define SMIA_LMINT3          /* LMINT3 interface flag for IS41 */

#define SMMA_LMINT3          /* LMINT3 interface flag for MAP GSM */

#define SMFN_LMINT3          /* LMINT3 interface flag for frame relay
                              * control protocol layer */

/* #define SMPN_LMINT3          LMINT3 interface flag for pnni */

/* #define SMIM_LMINT3          LMINT3 interface flag for IME */

/* #define SMAS_LMINT3           LMINT3 interface flag for qsaal */

#define SMIQ_LMINT3          /* LMINT3 flag for ISDN-Q.SAAL Convergence Layer */

#define SMIN_LMINT3    /* Stack manager uses LMINT3 code for IN */
                        /* If this flag is enabled, enable IN_LMINT3
                           in the #ifdef IN section */

/* #define SMBD_LMINT3     LMINT3 interface for LAPD */

/* internal defines - do not change */

#ifdef LMINT3

#ifdef SMBD_LMINT3
#undef SMBD_LMINT3
#define SMBD_LMINT3  1
#endif

#ifdef SMSD_LMINT3
#undef SMSD_LMINT3
#define SMSD_LMINT3  1
#endif


#ifdef SMSA_LMINT3
#undef SMSA_LMINT3
#define SMSA_LMINT3  1
#endif

#ifdef SMSN_LMINT3
#undef SMSN_LMINT3
#define SMSN_LMINT3  1
#endif

#ifdef SMSP_LMINT3
#undef SMSP_LMINT3
#define SMSP_LMINT3  1
#endif

#ifdef SMST_LMINT3
#undef SMST_LMINT3
#define SMST_LMINT3  1
#endif

#ifdef SMSI_LMINT3
#undef SMSI_LMINT3
#define SMSI_LMINT3  1
#endif

#ifdef SMIA_LMINT3
#undef SMIA_LMINT3
#define SMIA_LMINT3  1
#endif

#ifdef SMMA_LMINT3
#undef SMMA_LMINT3
#define SMMA_LMINT3  1
#endif

#ifdef SMFN_LMINT3
#undef SMFN_LMINT3
#define SMFN_LMINT3  1
#endif

#ifdef SMPN_LMINT3
#undef SMPN_LMINT3
#define SMPN_LMINT3  1
#endif

#ifdef SMAS_LMINT3
#undef SMAS_LMINT3
#define SMAS_LMINT3  1
#endif

#ifdef SMIM_LMINT3
#undef SMIM_LMINT3
#define SMIM_LMINT3  1
#endif

#ifdef SMAM_LMINT3
#undef SMAM_LMINT3
#define SMAM_LMINT3  1
#endif
 
#ifdef SMIQ_LMINT3
#undef SMIQ_LMINT3
#define SMIQ_LMINT3  1
#endif

#ifdef SMIN_LMINT3
#undef SMIN_LMINT3
#define SMIN_LMINT3  1
#endif
#endif /* LMINT3 */

#ifdef LCSMSDMILSD

#ifndef LCLSD
#define LCLSD 1
#endif /* LCLSD */

#endif /* LCSMSDMILSD */

#ifdef LCSMSNMILSN

#ifndef LCLSN
#define LCLSN 1
#endif /* LCLSN */

#endif /* LCSMSNMILSN */

#ifdef LCSMZNMILZN

#ifndef LCLZN
#define LCLZN 1
#endif /* LCLZN */

#endif /* LCSMZNMILZN */

#ifdef LCSMZVMILZV

#ifndef LCLZV
#define LCLZV 1
#endif /* LCLZV */

#endif /* LCSMZVMILZV */

#ifdef LCSMSPMILSP

#ifndef LCLSP
#define LCLSP 1
#endif /* LCLSP */

#endif /* LCSMSPMILSP */

#ifdef LCSMZPMILZP

#ifndef LCLZP
#define LCLZP 1
#endif /* LCLZP */

#endif /* LCSMZPMILZP */


#ifdef LCSMZLMILZL

#ifndef LCLZL
#define LCLZL 1
#endif /* LCLZL */

#endif /* LCSMZLMILZL */

#ifdef LCSMZAMILZA

#ifndef LCLZA
#define LCLZA 1
#endif /* LCLZA */

#endif /* LCSMZAMILZA */

#ifdef LCSMZBMILZB

#ifndef LCLZB
#define LCLZB 1
#endif /* LCLZB */

#endif /* LCSMZBMILZB */

#ifdef LCSMSTMILST

#ifndef LCLST
#define LCLST 1
#endif /* LCLST */

#endif /* LCSMSTMILST */

#ifdef LCSMSIMILSI

#ifndef LCLSI
#define LCLSI 1
#endif /* LCLSI */

#endif /* LCSMSIMILSI */

#ifdef LCSMHCMILHC

#ifndef LCLHC
#define LCLHC
#endif  /* LCLHC */

#ifdef CM_AAL
#ifndef LCATM
#define LCATM
#endif /* LCATM */
#endif /* CM_AAL */

#endif  /* LCSMHCMILHC */

/* accounting enable option */
/*#define LHC_ACNT*/

#ifdef LCSMHGMILHG

#ifndef LCLHG
#define LCLHG
#endif  /* LCLHG */

#endif  /* LCSMHGMILHG */

#ifdef LCSMHIMILHI

#ifndef LCLHI
#define LCLHI
#endif  /* LCLHI */

#endif  /* LCSMHIMILHI */

#ifdef LCSMGSMILGS

#ifndef LCLGS
#define LCLGS 1
#endif /* LCLGS */

#endif /* LCSMGSMILGS */

#ifdef LCSMGLMILGL

#ifndef LCLGL
#define LCLGL 1
#endif

#endif /* LCSMGLMILGL */

#ifdef LCSMHRMILHR

#ifndef LCLHR
#define LCLHR
#endif /* LCLHR */

#ifdef CM_AAL
#ifndef LCATM
#define LCATM
#endif /* LCATM */
#endif /* CM_AAL */

#endif /* LCSMHRMILHR */

#ifdef LCSMALMILAL     /* loosely coupled Stack manager with AAL2 Signaling */

#ifndef LCLAL
#define LCLAL 1
#endif  /* LCLAL */

#endif  /* LCSMALMILAL */

#ifdef LCSMIBMILIB
#ifndef LCLIB
#define LCLIB  1    /* Define LC flag for LIB (NBAP LM ) interface */
#endif
#endif /* LCSMIBMILIB */


#endif /* SM */

#ifdef LU       /* loader service user */

/**************************************************************************
   Loader service user layer parameters
**************************************************************************/

/* interfaces */

/* lower interface, loader service user, choose none or more */

/* #define LCLULILDR           loosely coupled, loader service interface */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCLULM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCLULM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCLULM          /* tightly coupled, layer management */
/* #define LCLULM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* debug upper interface, choose one or none */

#define DBLUUILDU          /* debug loader service user upper interface */

/* debug lower interface, choose one or none */

#define DBLULILDR          /* debug loader service user lower interface */

#endif

#ifdef LR       /* loader */

/**************************************************************************
   Loader layer parameters
**************************************************************************/

/* interfaces */

/* upper interface, loader, choose none or more */

/* #define LCLRUILDR           loosely coupled, loader service interface */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCLRLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCLRLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCLRLM          /* tightly coupled, layer management */
/* #define LCLRLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* debug upper interface, choose one or none */

#define DBLRUILDR          /* debug loader upper interface */

#endif /* LR */

#ifdef RY       /* relay */

/**************************************************************************
   relay layer parameters
**************************************************************************/

/* interfaces */

/* external interface */

/* #define LCRYEIRYT           loosely coupled, loader service interface */

/* layer management options */

/* management interface, lry , choose none or more */

/* #define LCRYMILRY       loosely coupled, layer management */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCRYLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCRYLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCRYLM          /* tightly coupled, layer management */
/* #define LCRYLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* #define RY_ENBTCPSOCK        TCP Relay */
/* #define RY_ENBUDPSOCK        UDP Relay */
/* #define RY_ENBS5SHM          System V Shared memory relay */
/* #define RY_TU_BLK            TCP/UDP Relay : Blocking mode */
/* #define RY_MULTI_THREADED    multi-threaded relay */
/* #define SWAP_ENABLED         swap when reading from shared mem */
#endif /* RY */

#ifdef FM       /* fault manager */

/**************************************************************************
   fault manager layer parameters
**************************************************************************/

/* interfaces */

/* #define LCFMMILFM       loosely coupled, layer management */

/* product specific options */

#endif /* FM */



#ifdef ME       /* relay */

/**************************************************************************
   relay layer parameters
**************************************************************************/

/* interfaces */

/* management interface, lme , choose none or more */

/* #define LCMEMILME       loosely coupled, layer management */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCMELM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCMELM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCMELM          /* tightly coupled, layer management */
/* #define LCMELM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

#endif /* ME */


#ifdef XN       /* x.25/x.75 */
/**************************************************************************
   x.25/x.75 parameters
**************************************************************************/

/* interfaces */

/* upper interface, x.25 network, choose none or more */

/* #define LCXNUIXNT       loosely coupled, x.25 network layer */

/* lower interface, data link, choose none or more */

/* #define LCXNLIDAT        loosely coupled, data link layer */

/* management interface, lxn , choose none or more */

/* #define LCXNMILXN        loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCXGLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCXGLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCXGLM          /* tightly coupled, layer management */
/* #define LCXGLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* pvc variant, choose none or one */

#define PVC          /* permanent virtual circuit */

/* defense department network variant, choose none or one */

/* #define DDN           defense department netowrk */

/* data link interface type, choose one */
/* if applicable, must agree with lapb, lapd, lapb and lapd, basic frame
   relay or extended frame relay data link interface type */

#define DATINT1      /* data link interface 1 */
/* #define DATINT2       data link interface 2 */

/* type, choose all */

#define X75           /* x.75 */
#define ENDSYS       /* end system */
#define ITMSYS       /* intermediate system */

#endif /* x.25/x.75 */



#ifdef XG       /* x.75 */
/**************************************************************************
   x.75 parameters
**************************************************************************/

/* product version, choose one */
 
/* #define XGVER1          X.75, version 1.x */
#define XGVER2         /* X.75, version 2.x */
#define L3VER2         /* X.75, version 2.x */
 
/* interfaces */

/* upper interface, x.25 network, choose none or more */

/* #define LCXNUIXNT     loosely coupled, x.25 network layer */
/* #define BCXNUIXNT     backward compatibility, x.25 network layer */

/* lower interface, data link, choose none or more */

/* #define LCXNLIDAT     loosely coupled, data link layer */
/* #define BCXNLIDAT     backward compatibility, data link layer */

/* management interface, lxn , choose none or more */

/* #define LCXNMILXN       loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCXGLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCXGLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCXGLM          /* tightly coupled, layer management */
/* #define LCXGLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* pvc variant, choose none or one */

#define PVC          /* permanent virtual circuit */

/* defense department network variant, choose none or one */

/* #define DDN           defense department netowrk */

/* data link interface type, choose one */
/* if applicable, must agree with lapb, lapd, lapb and lapd, basic frame
   relay or extended frame relay data link interface type */

#define DATINT1      /* data link interface 1 */
/* #define DATINT2       data link interface 2 */

/* type, choose all */

#define X75          /* x.75 */
#define ENDSYS       /* end system */
#define ITMSYS       /* intermediate system */

#endif


#ifdef EI       /* x.25 end and intermediate system */
/**************************************************************************
   x.25 end and intermediate system parameters
**************************************************************************/

/* product version, choose one */
 
/* #define EIVER1          X.25, version 1.x */
#define EIVER2         /* X.25, version 2.x */
#define L3VER2         /* X.25, version 2.x */
 
/* interfaces */

/* upper interface, x.25 network, choose none or more */

/* #define LCXNUIXNT     loosely coupled, x.25 network layer */
/* #define BCXNUIXNT     backward compatibility, x.25 network layer */

/* lower interface, data link, choose none or more */

/* #define LCXNLIDAT     loosely coupled, data link layer */
/* #define BCXNLIDAT     backward compatibility, data link layer */

/* management interface, lxn , choose none or more */

/* #define LCXNMILXN       loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCEILM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCEILM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCEILM          /* tightly coupled, layer management */
/* #define LCEILM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* pvc variant, choose none or one */

#define PVC          /* permanent virtual circuit */

/* defense department network variant, choose none or one */

/* #define DDN           defense department netowrk */

/* data link interface type, choose one */
/* if applicable, must agree with lapb, lapd, lapb and lapd, basic frame
   relay or extended frame relay data link interface type */

#define DATINT1      /* data link interface 1 */
/* #define DATINT2       data link interface 2 */

/* type, choose all */

#define ENDSYS       /* end system */
#define ITMSYS       /* intermediate system */

#endif


#ifdef XE       /* x.25 end system */
/**************************************************************************
   x.25 end system parameters
**************************************************************************/

/* product version, choose one */
 
/* #define XEVER1          x25, version 1.x */
#define XEVER2         /* x25, version 2.x */
#define L3VER2         /* x25, version 2.x */

/* interfaces */

/* upper interface, x.25 network, choose none or more */

/* #define LCXNUIXNT     loosely coupled, x.25 network layer */
/* #define BCXNUIXNT     backward compatibility, x.25 network layer */

/* lower interface, data link, choose none or more */

/* #define LCXNLIDAT     tighly coupled, data link layer */
/* #define BCXNLIDAT     tighly coupled, data link layer */

/* management interface, lxn , choose none or more */

/* #define LCXNMILXN       loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCXELM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCXELM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCXELM          /* tightly coupled, layer management */
/* #define LCXELM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* pvc variant, choose none or one */

#define PVC          /* permanent virtual circuit */

/* defense department network variant, choose none or one */

/* #define DDN           defense department netowrk */

/* data link interface type, choose one */
/* if applicable, must agree with lapb, lapd, lapb and lapd, basic frame
   relay or extended frame relay data link interface type */

#define DATINT1      /* data link interface 1 */
/* #define DATINT2       data link interface 2 */

/* type, choose all */

#define ENDSYS       /* end system */

#endif


#ifdef XI       /* x.25 intermediate system */
/**************************************************************************
   x.25 intermediate system parameters
**************************************************************************/

/* product version, choose one */
 
/* #define XIVER1          X.25, version 1.x */
#define XIVER2         /* X.25, version 2.x */
#define L3VER2         /* X.25, version 2.x */
 
/* interfaces */

/* lower interface, data link, choose none or more */

/* #define LCXNLIDAT     tighly coupled, data link layer */
/* #define BCXNLIDAT     tighly coupled, data link layer */

/* management interface, lxn , choose none or more */

/* #define LCXNMILXN       loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCXILM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCXILM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCXILM          /* tightly coupled, layer management */
/* #define LCXILM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* pvc variant, choose none or one */

#define PVC          /* permanent virtual circuit */

/* defense department network variant, choose none or one */

/* #define DDN           defense department netowrk */

/* data link interface type, choose one */
/* if applicable, must agree with lapb, lapd, lapb and lapd, basic frame
   relay or extended frame relay data link interface type */

#define DATINT1      /* data link interface 1 */
/* #define DATINT2       data link interface 2 */

/* type, choose all */

#define ITMSYS       /* intermediate system */

#endif
 

#ifdef IX       /*  X.31 */
/**************************************************************************
   x.31 parameters
**************************************************************************/

/* product version, choose one */
 
/* #define IXVER1          X.31, version 1.x */
#define IXVER2           /*X.31, version 2.x */
 
/* interfaces */

/* upper interface, data link, choose none or more */

/* #define LCIXUIDAT     loosely coupled, data link layer */
/* #define BCIXUIDAT     backward compatibility, data link layer */

/* lower interface, isdn network, choose none or more */

/* #define LCIXLIINT     loosely coupled, isdn network layer */
/* #define BCIXLIINT     backward compatibility, isdn network layer */

/* lower interface, data link, choose none or more */

/* #define LCIXLIDAT     loosely coupled, data link layer */
/* #define BCIXLIDAT     backward compatibility, data link layer */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

/*#ifdef LCLM             backward compatilbility, layer management */
/* choose all */

/*#define LCIXLM         loosely coupled, layer management */
/*#else*/
/*#ifdef TCLM            backward compatilbility, layer management */
/* choose all */

/*#define TCIXLM           tightly coupled, layer management */
/*#else                    tightly or loosely coupled, layer management */
/* choose none or one */

/*#define TCIXLM          tightly coupled, layer management */
/*#define LCIXLM         loosely coupled, layer management */
/*#endif */
/*#endif*/

#define BDVER2
#define INVER2
/* product specific options */

/* switch variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with q.93x/q.931 switch variants */

/* #define ATT           att 4ess and 5ess, option 11 */
/* #define NT            northern telecomm dms-100, option 12 */
/* #define VN            vn 2 and vn 3, france, option 13 */
/* #define ETSI          etsi, europe, option 14 */ 
/* #define AUS           AUS, australian, option 15 */ 
/* #define NI1           national isdn 1, north america, option 16 */ 
/* #define NTT           ins net, japan, option 17 */
/* #define TR6           1 - TR6, german, option 18 */
/* #define ATT5E         att 5ess, option 19 */
/* #define ATT4E         att 4ess, option 20 */
/* #define VN2           vn 2, france, option 21 */
/* #define VN3           vn 3, france, option 22 */
/* #define NTDMS250      northern telecom dms-250, option 23 */
/* #define BC303         bellcore tr-303, tmc and csc, option 24 */
/* #define BC303TMC      bellcore tr-303, tmc , option 25 */
/* #define BC303CSC      bellcore tr-303, csc, option 26 */
/* #define Q932          q.932 option, option 27 */

/* variant, choose all */

#ifdef ATT              /* att */
#define ATT5E           /* att 5ess, option 19 */
#define ATT4E           /* att 4ess, option 20 */
#endif

#ifdef VN3              /* vn 3 */
#define VN              /* vn 2 and vn 3, france, option 13 */
#endif

#ifdef VN               /* vn */
#define VN2             /* vn 2, france, option 21 */
#define VN3             /* vn 3, france, option 22 */
#endif

#ifdef BC303            /* bellcore tr-303 */
#define BC303TMC        /* bellcore tr-303, tmc , option 25 */
#define BC303CSC        /* bellcore tr-303, csc, option 26 */
#endif

/* features, choose none or more */

/* #define DECODCDSET   1   decode network and user specific codeset 6 and 7 */
                           /* elements into individual elements vs. string */

/* data link interface type, choose one */
/* if applicable, must agree with x.75, x.25 end and intermediate
   system, x.25 intermediate system or x.25 end system, lapb, lapd,
   lapb and lapd, basic frame relay or extended frame relay data
   link interface type */

#define DATINT1      /* data link interface 1 */
/* #define DATINT2       data link interface 2 */

#endif


#ifdef BR       /* basic frame relay */
/**************************************************************************
   basic frame relay parameters
**************************************************************************/

/* product version, choose one */

/* #define BDVER1         basic frame relay, version 1.x */
#define BDVER2         /* basic frame relay, version 2.x */

/* interfaces */

/* upper interface, data link, choose none or more */

/* #define LCDAUIDAT     loosely coupled, data link layer */
/* #define BCDAUIDAT     backward compatibility, data link layer */

/* lower interface, mac, choose none or more */

/* #define LCDALIMAC     loosely coupled, mac layer */
/* #define BCDALIMAC     backward compatibility, mac layer */

/* management interface, lbd , choose none or more */

/* #define LCDAMILBD     loosely coupled, layer management */

/* debug mngmt interface, choose one or none, default is debug output disabled */
 
/* #define DBLDMILBD     debug output enabled for mngmt interface */

/* layer management options */

/* product specific options */

/* data link interface type, choose one */
/* if applicable, must agree with x.75, x.25 end and intermediate
   system, x.25 intermediate system, x.25 end system or x.31 data link
   interface type */

/* #define DATINT1       data link interface 1 */
#define DATINT2  1   /* data link interface 2 */

/* mac interface type, choose one */
/* if applicable, must agree with scc or isac-s mac interface type */

#define MACINT1      /* mac link interface 1 */
/* #define MACINT2       mac interface 2 */

#define MACVER2

#define FR_BR    1      /* basic frame relay */

#define FR       1      /* frame relay interface */

#endif


#ifdef ER       /* extended frame relay */
/**************************************************************************
   extended frame relay parameters
**************************************************************************/

/* product version, choose one */

/* #define BDVER1          extended frame relay, version 1.x */
#define BDVER2         /* extended frame relay, version 2.x */

/* interfaces */

/* upper interface, data link, choose none or more */

/* #define LCDAUIDAT     loosely coupled, data link layer */
/* #define BCDAUIDAT     backward compatibility, data link layer */

/* lower interface, mac, choose none or more */

/* #define LCDALIMAC     loosely coupled, mac layer */
/* #define BCDALIMAC     backward compatibility, mac layer */

/* management interface, lbd , choose none or more */

/* #define LCDAMILBD     loosely coupled, layer management */

/* debug mngmt interface, choose one or none, default is debug output disabled */

/* #define DBLDMILBD     debug output enabled for mngmt interface */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCERLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCERLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCERLM          /* tightly coupled, layer management */
/* #define LCERLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* data link interface type, choose one */
/* if applicable, must agree with x.75, x.25 end and intermediate
   system, x.25 intermediate system, x.25 end system or x.31 data link
   interface type */

/* #define DATINT1 1     data link interface 1 */
/* #define DATINT2 1     data link interface 2 */
#define DATINT4 1    /* data link interface 2 */

/* mac interface type, choose one */
/* if applicable, must agree with scc or isac-s mac interface type */

#define MACINT1      /* mac interface 1 */
/* #define MACINT2       mac interface 2 */

#define MACVER2

#define FR_ER    1

#endif



#ifdef FR       /* Frame Relay Data Link*/
/**************************************************************************
   Frame Relay Data Link parameters
**************************************************************************/

/* product version, choose one */

/* interfaces */

/* MAC specific defines */
#define DATVER2      /* data link interface 2 */
#define MACINT1      /* mac link interface 1 */
#define MACVER2      /* mac version 2 */

/* MAC interface */
/* #define LCFRLIMAC     loosely coupled, Q.922 to MAC layer */

#ifdef LCFRLIMAC
#ifndef LCISUIMAC
#define LCISUIMAC     /* loosely coupled MAC to Q.922 layer */
#endif /* #ifndef LCISUIMAC */
#endif /* #ifdef LCFRLIMAC */

/* FRD interface */
/* #define LCFRUIFRD     loosely coupled, frame data link layer to layer 3 */
#ifdef LCFRUIFRD
#ifndef LCFR
#define LCFR 
#endif /* #ifndef LCFR */
#endif /* #ifdef LCFRUIFRD */

/* upper interface, choose none or more */

/* #define LCFRLIFRD     loosely coupled, any layer to frame link layer */

#ifdef LCFRLIFRD
#ifndef LCFR
#define LCFR 
#endif /* #ifndef LCFR */
#endif /* #ifdef LCFRLIFRD */

/* layer management options */

/* #define LCFRMILFR            loosely coupled, layer management */

/* product specific options */

/* choose none or one or more */
/* must agree with options delivered */

/* Enable following only if NETSIDE operations required */
#ifndef FR_SWITCHING
/* #define FR_SWITCHING           network side procedures */
#endif /* #ifndef FR_SWITCHING */

/* Enable following only if USRSIDE operations required */
#ifndef USRSIDE
/* #define USRSIDE           user side procedures */
#endif /* #ifndef USRSIDE */

/* Enable following only for LAPF procedures */
/* #define LAPF                 extended configuration */

/* Enable the following only if NETSIDE procedures are enabled */
#ifdef FR_SWITCHING
/* #define FR_MCAST          Multicast: 1-way, 2-way & N-way */
#endif /* #ifdef FR_SWITCHING */

/* Enable following to avoid use of HASH lists */ 
/* #define FR_NOHASH        No hash list to be used */

/*** Start of Fragmentation related flags ***/

/* Enable the following flag to use end to end fragmentation */
/* #define FR_FRAGMENT */

/* Enable the following flag to use interface fragmentation */
/* #define FR_IF_FRAGMENT */

/* Enable the flag FR_ANY_FRAGMENTATION to use either of the fragmentation
   procedures, end to end or interface fragmentation */
#ifdef FR_FRAGMENT
#ifndef FR_ANY_FRAGMENTATION
#define FR_ANY_FRAGMENTATION
#endif
#endif /* #ifdef FR_FRAGMENT */

#ifdef FR_IF_FRAGMENT
#ifndef FR_ANY_FRAGMENTATION
#define FR_ANY_FRAGMENTATION
#endif
#endif /* #ifdef FR_IF_FRAGMENT */

/* Enable the following flag to enable FRF.12 specific fragmentation /
   re-assembly procedures */
/* #define FR_FRF12 */

/*** End of Fragmentation related flags ***/

/* Enable the following flag for prioritization of outgoing data */
/* #define FR_PRIORITIZE_TRAFFIC */

/* Enable the following in case the upper layer is a fault tolerant layer
   and wants to use the Bind Confirmation and Congestion Status Confirmation
   primitives */
/* #define FRD2 */

/* Enable following to use CIR traffic monitoring*/
/* #define FR_TRAFFFIC_MONITOR */

/* Use following to enable debug printing of incoming and outgoing frames */
/* #define FR_DBGDISPLAY       Enable debug printing */
#endif /* #ifdef FR */


#ifdef BD       /* lapb and lapd */
/**************************************************************************
   lapb and lapd parameters
**************************************************************************/

/* product version, choose one */

/* #define BDVER1          lapb/d, version 1.x */
#define BDVER2         /* lapb/d , version 2.x */

/* interfaces */

/* upper interface, data link, choose none or more */

/* #define LCDAUIDAT     loosely coupled, data link layer */
/* #define BCDAUIDAT     backward compatibility, data link layer */

/* lower interface, mac, choose none or more */

/* #define LCDALIMAC     loosely coupled, mac layer */
/* #define BCDALIMAC     backward compatibility, mac layer */

/* management interface, lbd , choose none or more */

/* #define LCDAMILBD     loosely coupled, layer management */

/* debug mngmt interface, choose one or none, default is debug output disabled */

/* #define DBBDMILBD     debug output enabled for mngmt interface */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCBDLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCBDLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCBDLM          /* tightly coupled, layer management */
/* #define LCBDLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* tei management, choose none or one */
/* must agree with options delivered */

/* #define LMLD          tei management, option 11 */

/* data link interface type, choose one */
/* if applicable, must agree with x.75, x.25 end and intermediate
   system, x.25 intermediate system, x.25 end system or x.31 data link
   interface type */
  
#define DATINT1      /* data link interface 1 */
/* #define DATINT2       data link interface 2 */

/* mac interface type */
/* if applicable, must agree with scc or isac-s mac interface type */
  
/* #define MACINT1       mac interface 1 */
#define MACINT2      /* mac interface 2 */

#endif


#ifdef LD       /* lapd */
/**************************************************************************
   lapd parameters
**************************************************************************/

/* product version, choose one */

/* #define BDVER1          lapd, version 1.x */
#define BDVER2          /* lapd , version 2.x */
#define L3VER2          /* layer 3 */
/* interfaces */

/* upper interface, data link, choose none or more */

/* #define LCDAUIDAT     loosely coupled, data link layer */

/* lower interface, mac, choose none or more */

/* #define LCDALIMAC     loosely coupled, mac layer */

/* management interface, lbd , choose none or more */

/* #define LCDAMILBD     loosely coupled, layer management */

/* debug mngmt interface, choose one or none, default is debug output disabled */

/* #define BD_LMINT3        layer management interface 3. If this flag
                         is enabled, enable SMBD_LMINT3 flag in the
                         ifdef SM section. If this flag is disabled,G++ W #
                         disable SMBD_LMINT3 flag in the #ifdef SM
                         section. This flag should be turned OFF for
                         pre LMINT3 interface */

#ifdef LMINT3
#ifdef BD_LMINT3
#undef BD_LMINT3
#define BD_LMINT3 1
#endif /* BD_LMINT3 */
#endif /* BD_LMINT3 */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCLDLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCLDLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCLDLM          /* tightly coupled, layer management */
/* #define LCLDLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* tei management, choose none or one */
/* must agree with options delivered */

/* #define LMLD          tei management, option 11 */

/* data link interface type, choose one */
/* if applicable, must agree with x.75, x.25 end and intermediate
   system, x.25 intermediate system, x.25 end system or x.31 data link
   interface type */
  
#define DATINT1       /* data link interface 1 */
/* #define DATINT2       data link interface 2 */

/* mac interface type, choose one */
/* if applicable, must agree with scc or isac-s mac interface type */

#define MACINT1       /* mac interface 1 */
/* #define MACINT2       mac interface 2 */
/* #define MACINT4       mac interface 4 */
/* #define MACINTN       mac interface N */

#ifdef LCDAMILBD
#ifndef LCLBD
#define LCLBD 1
#endif /* LCLBD */
#endif /* LCDAMILBD */

#ifdef LCDAUIDAT
#ifndef LCDAT
#define LCDAT 1
#endif /* LCDAT */
#endif /* LCDAUIDAT */

#ifdef LCDALIMAC
#ifndef LCMAC
#define LCMAC 1
#endif /* LCMAC */
#endif /* LCDALIMAC */

/*#define BD_FTHA           Enables SHT interface for LAPD */

#endif

#ifdef D2       /* D2 */
/**************************************************************************
   D2 parameters
**************************************************************************/

/* product version, choose one */

/* interfaces */

/* upper interface, data link, choose none or more */

/* #define LCD2UIDDT   loosely coupled, data link layer */

/* lower interface, mac, choose none or more */

/* #define LCD2LIMAC    loosely coupled, mac layer */

/* management interface, lbd , choose none or more */

/* #define LCD2MILD2   loosely coupled, layer management */

#define MACINTN      /* mac interface N */

#ifdef LCD2MILD2
#ifndef LCLD2
#define LCLD2 1
#endif /* LCLBD */
#endif /* LCDAMILBD */

#ifdef LCD2UIDDT
#ifndef LCDDT
#define LCDDT 1
#endif /* LCDAT */
#endif /* LCDAUIDAT */

#ifdef LCD2LIMAC
#ifndef LCMAC
#define LCMAC 1
#endif /* LCMAC */
#endif /* LCDALIMAC */

#endif


#ifdef LB       /* lapb */
/**************************************************************************
   lapb parameters
**************************************************************************/

/* product version, choose one */

/* #define BDVER1          lapb , version 1.x */
#define BDVER2         /* lapb, version 2.x */

/* upper interface, data link, choose none or more */

/* #define LCDAUIDAT     loosely coupled, data link layer */
/* #define BCDAUIDAT     backward compatibility, data link layer */

/* lower interface, mac, choose none or more */

/* #define LCDALIMAC     loosely coupled, mac layer */
/* #define BCDALIMAC     backward compatibility, mac layer */

/* management interface, lbd , choose none or more */

/* #define LCDAMILBD     loosely coupled, layer management */

/* debug mngmt interface, choose one or none, default is debug output disabled */

/* #define DBLBMILBD     debug output enabled for mngmt interface */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCLBLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCLBLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCLBLM          /* tightly coupled, layer management */
/* #define LCLBLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* data link interface type, choose one */
/* if applicable, must agree with x.75, x.25 end and intermediate
   system, x.25 intermediate system, x.25 end system or x.31 data link
   interface type */

#define DATINT1      /* data link interface 1 */
/* #define DATINT2       data link interface 2 */

/* mac interface type, choose one */
/* if applicable, must agree with scc or isac-s mac interface type */

#define MACINT1      /* mac interface 1 */
/* #define MACINT2       mac interface 2 */

#endif


#ifdef SC       /* scc */
/**************************************************************************
   scc parameters
**************************************************************************/

/* interfaces */
  
/* upper interface, mac, choose none or more */

/* #define LCSCUIMAC     loosely coupled, mac layer */
/* #define BCSCUIMAC     backward compatibility, mac layer */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCSCLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCSCLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCSCLM          /* tightly coupled, layer management */
/* #define LCSCLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* mac interface type, choose one */
/* if applicable, must agree with asynchronous pad, lapb, lapd, lapb
   and lapd, basic frame relay or extended frame relay mac interface type */

#define MACINT1      /* mac interface 1 */
/* #define MACINT2       mac interface 2 */

#endif


#ifdef IS       /* isac-s */
/**************************************************************************
   isac-s parameters
**************************************************************************/

/* product version, choose one */

#define MACVER1         /* isac , version 1.x */
/* #define MACVER2          isac, version 2.x */

/* interfaces */

/* upper interface, mac, choose none or more */

/* #define LCISUIMAC     loosely coupled, mac */
/* #define BCISUIMAC     backward compatibility, mac */

/* layer management options */

/* #define LCISMILIS     loosely coupled, layer management */
 
/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCISLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCISLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCISLM          /* tightly coupled, layer management */
/* #define LCISLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* mac interface type, choose one */
/* if applicable, must agree with asynchronous pad, lapb, lapd, lapb
   and lapd, basic frame relay or extended frame relay mac interface type */

#define MACINT1      /* mac interface 1 */
/* #define MACINT2       mac interface 2 */

#endif


#ifdef SE       /* sec */
/**************************************************************************
   sec parameters
**************************************************************************/

/* product version, choose one */

/* #define SEVER1          sec, version 1.x */
#define SEVER2         /* sec, version 2.x */

/* interfaces */
  
/* upper interface, mac, choose none or more */

/* #define LCSEUIMAC     loosely coupled, mac layer */

/* layer management options */

/* #define LCSEMILSE     loosely coupled, layer management */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCSELM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCSELM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCSELM          /* tightly coupled, layer management */
/* #define LCSELM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* mac interface type, choose one */
/* if applicable, must agree with asynchronous pad, lapb, lapd, lapb
   and lapd, basic frame relay, extended frame relay or mtp level 2
   mac interface type */

/* #define MACINT1       mac interface 1 */
/* #define MACINT2       mac interface 2 */

/* ASYNC support on 68302 or 68360, choose none or one */

/* #define ASYNC_SUPPORT       configure SCC for ASYNC */
 
/* Tx BD 4, 5, 6, and 7 available to SCC3, choose none or one */

#define TXBD_4567          /* configure Tx BD 4-7 for SCC3 */
 
/* SS7 microcode on 68302 or 68360, choose none or one */

#define SS7_MICROCODE      /* configure SCC for SS7 */
/* #define MACINT5            maci interface 5 */
/* MACINT4 substitutes ConReq and DatCfm primitives */
#define MACINT4          /* mac interface 4 */

/* debug upper mac interface, choose one or none */

/* #define DBSEUIMAC           debug dummy upper mac interface */
 
#endif /* SE */



#ifdef QI       /* 68360 QUICC */
/**************************************************************************
   360 parameters
**************************************************************************/

/* product version, choose one */

#define QIVER2         /* QUICC uses version 2 */

/* interfaces */
  
/* upper interface, mac, choose none or more */

/* #define LCQIUIMAC     loosely coupled, mac layer */

/* layer management options */
/* #define LCQIMILQI     loosely coupled, layer management */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCQILM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCQILM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCQILM          /* tightly coupled, layer management */
/* #define LCSELM           loosely coupled, layer management */
#endif
#endif /* TCQILM */

#define SS7_MICROCODE   /* use ss7 microcode */
/* #define MACINT5         mtp-2 interface */
/* MACINT4 substitutes ConReq and DatCfm primitives */
#define MACINT4          /* mac interface 4 */

#endif /* QI */


#ifdef PQ       /* MPC860 PQUICC */
/**************************************************************************
   860 parameters
**************************************************************************/

/* product version, choose one */

#define PQVER2         /* PQUICC uses version 2 */

/* interfaces */
  
/* upper interface, mac, choose none or more */

/* #define LCPQUIMAC     loosely coupled, mac layer */

/* layer management options */
/* #define LCPQMILPQ     loosely coupled, layer management */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCPQLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCPQLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCPQLM          /* tightly coupled, layer management */
/* #define LCSELM           loosely coupled, layer management */
#endif
#endif /* TCPQLM */

#define SS7_MICROCODE   /* use ss7 microcode */
/* #define MACINT5         mtp-2 interface */
/* MACINT4 substitutes ConReq and DatCfm primitives */
#define MACINT4          /* mac interface 4 */

#endif /* PQ */

#ifdef VO       /* MPC8260 PowerQUICC II "VOyager" */
/**************************************************************************
 *   8260 parameters
 ***************************************************************************/

/* product version, choose one */

#define VOVER2         /* VO uses version 2 */

/* interfaces */

/* upper interface, mac + aal, choose none or more */

/* layer management options */
#define LCVOMILVO       /* loose coupling in the driver */
#define LCSMVOMILVO     /* loose coupling in the layer manager */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCVOLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCVOLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCVOLM          /* tightly coupled, layer management */
/* #define LCSELM           loosely coupled, layer management */
#endif
#endif /* TCVOLM */

/* Product specific options */

#if (VOPROT_HDLC)
#ifdef VOPROT_NBAND
#undef VOPROT_NBAND
#endif
#define VOPROT_NBAND 1
#endif

#ifndef ATM
#define ATM  1             /* ATM stack */
#endif

#ifndef UNI40
#define DEF_UNI40      0
#else
#define DEF_UNI40      1
#endif

/* #define SS7_MICROCODE   use ss7 microcode */
/* #define MACINT5         mtp-2 interface */
/* MACINT4 substitutes ConReq and DatCfm primitives */
/* #define MACINT4         mac interface 4 */

#endif /* VO */

#ifdef MS       /* mos */
/**************************************************************************
   mos parameters
**************************************************************************/

/* interfaces */

/* management interface, lms , choose none or more */

/* #define LCMSMILMS       loosely coupled, layer management */

/* product version, choose one */

/* selected at top of file */


/* layer management options, choose none */

#ifndef LMINT2
#define LMINT2          /* layer management interface 2 */
#endif

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCMSLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCMSLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCMSLM          /* tightly coupled, layer management */
/* #define LCMSLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* pre-emptive, choose none or one */

/* #define PREMOS        pre-emptive */

/* uniprocessor mode, choose none or one */

/* #define UOS_MODE         uniprocessor mode */

/* enable random number generator, choose none or one */

#define ENB_RANDOM      /* random number generator */

/* post format, choose none or one */

#define FCSPOSTINT      /* forward compatibility, post format */

/* elvis, choose none */

#ifdef ELVIS
#ifdef ELVIS_68302
#define MALLOC_UNAVAIL    /* malloc unavaliable */
#define NOCMDLINE         /* no command line available */
#define NOFILESYS         /* no filesystem available (FILE *) */
#define MOS_TMR 1         /* mos uses interrupt timers */
/* #define SS_NIC          system service no interrupt control */
#define STDIO_INCLD       /*stdio.h included */
#else /* ELVIS_68302 */
#ifdef ELVIS_68040
#define MALLOC_UNAVAIL    /* malloc unavaliable */
#define NOCMDLINE         /* no command line available */
#define NOFILESYS         /* no filesystem available (FILE *) */
#define MOS_TMR 1         /* mos uses interrupt timers */
/* #define SS_NIC          system service no interrupt control */
#define STDIO_INCLD       /* stdio.h included */
#else
#ifdef ELVIS_68360
#define MALLOC_UNAVAIL    /* malloc unavaliable */
#define NOCMDLINE         /* no command line available */
#define NOFILESYS         /* no filesystem available (FILE *) */
#define MOS_TMR 1         /* mos uses interrupt timers */
/* #define SS_NIC          system service no interrupt control */
#define STDIO_INCLD       /* stdio.h included */
#else
#ifdef ELVIS_STACK
/* #define MALLOC_UNAVAIL  malloc unavaliable */
/* #define NOCMDLINE       no command line available */
/* #define NOFILESYS       no filesystem available (FILE *) */
#define MOS_TMR 1         /* mos uses interrupt timers */
#define SS_NIC            /* system service no interrupt control */
#define STDIO_INCLD       /* stdio.h included */
#endif /* ELVIS_STACK */
#endif /* ELVIS_68360 */
#endif /* ELVIS_68040 */
#endif /* ELVIS_68302 */
#else  /* not ELVIS */
#ifdef ELVIS_PPC
#ifdef ELVIS_PPC860
#define MALLOC_UNAVAIL    /* malloc unavaliable */
#define NOCMDLINE         /* no command line available */
#define NOFILESYS         /* no filesystem available (FILE *) */
#define MOS_TMR 1         /* mos uses interrupt timers */
/* #define SS_NIC          system service no interrupt control */
#define STDIO_INCLD       /* stdio.h included */
#else  /* ELVIS_PPC860 */
#endif /* ELVIS_PPC860 */
#else /* not ELVIS_PPC */
#ifdef SUNOS
#define STDIO_INCLD       /* stdio.h included */
#define SS_NIC            /* system service no interrupt control */
/* #define MALLOC_UNAVAIL  malloc unavaliable */
/* #define NOCMDLINE       no command line available */
/* #define NOFILESYS       no filesystem available (FILE *) */
#else  /* not SUNOS */
#ifdef QUICCADS
#define MALLOC_UNAVAIL    /* malloc unavaliable */
#define NOCMDLINE         /* no command line available */
#define NOFILESYS         /* no filesystem available (FILE *) */
#define MOS_TMR 1         /* mos uses interrupt timers */
/* #define SS_NIC          system service no interrupt control */
#define STDIO_INCLD       /* stdio.h included */
#else
#ifdef PQUICCADS
#define MALLOC_UNAVAIL    /* malloc unavaliable */
#define NOCMDLINE         /* no command line available */
#define NOFILESYS         /* no filesystem available (FILE *) */
#define MOS_TMR 1         /* mos uses interrupt timers */
/* #define SS_NIC          system service no interrupt control */
#define STDIO_INCLD       /* stdio.h included */
#else
#ifdef ALC_EVAL
#define MALLOC_UNAVAIL    /* malloc unavaliable */
#define NOCMDLINE         /* no command line available */
#define NOFILESYS         /* no filesystem available (FILE *) */
#define MOS_TMR 1         /* mos uses interrupt timers */
#else
#ifdef VB_360             /* VoiceBoard with 68360 */
#define MALLOC_UNAVAIL    /* malloc unavaliable */
#define NOCMDLINE         /* no command line available */
#define NOFILESYS         /* no filesystem available (FILE *) */
#define MOS_TMR 1         /* mos uses interrupt timers */
/* #define SS_NIC          system service no interrupt control */
#else
#ifdef PQ_PPC860          /* Force PMC860 board */
#define MALLOC_UNAVAIL    /* malloc unavaliable */
#define NOCMDLINE         /* no command line available */
#define NOFILESYS         /* no filesystem available (FILE *) */
#define MOS_TMR 1         /* mos uses interrupt timers */
/* #define SS_NIC          system service no interrupt control */
#else
#endif /* PQ_PPC860 */
#endif /* VB_360 */
#endif /* ALC_EVAL */
#endif /* PQUICCADS */
#endif /* QUICCADS */
#endif /* SUNOS */
#endif /* ELVIS_PPC */
#endif /* ELVIS */
/* #define NOPRNTMEM         disable prntMem */
/* #define MOS_IS_GUEST      mos operates as guest os */
/* #define PORTSERV          mos portable services */

/* define the console port to be used on the PMC860 */
#ifdef PQ_PPC860          /* Force PMC860 board */
/* choose only one console port */
/* #define CONSOLE_SCC1          SCC1 used as console port */
#define CONSOLE_SMC1          /* SMC1 used as console port */
#endif /* PQ_PPC860 */

#endif /* MS */

#ifdef AU       /* SS7 MAP User */
/**************************************************************************
   SS7 MAP User parameters
**************************************************************************/
#undef AU
#define AU 1

/* interfaces */

/* upper interface, choose none or more */

/* #define LCAUUIMAU     loosely coupled, MAP User upper layer */

/* lower interface, data link, choose none or more */

/* #define LCAULIMAT      loosely coupled, MAP User lower layer */
/* #define LWLCAULIMAT    light weight loosely coupled,MAP user lower layer*/

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCAULM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCAULM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCAULM          /* tightly coupled, layer management */
/* #define LCAULM           loosely coupled, layer management */
#endif
#endif

#ifdef LCAUUIMAU
#ifndef LCMAU
#define LCMAU 1
#endif
#endif  /* LCAUUIMAU */

#ifdef LCAULIMAT
#ifndef LCMAT
#define LCMAT 1
#endif
#endif  /* LCAULIMAT */

#ifdef LWLCAULIMAT
#ifndef LWLCMAT
#define LWLCMAT 1
#endif
#endif  /* LWLCAULIMAT */


#ifdef LCAUMILAU

#ifndef LCLAU
#define LCLAU 1
#endif

#endif  /* LCAULIMAT */

#if (LCMAT || LCAU || LCLMA)

#ifndef LCSS7
#define LCSS7 1
#endif

#endif  /* LCSTU || LCTCU || LCLTU */

/* product specific options */

#define MSC        /* MAP MSC */
#define VLR        /* MAP_VLR */
#define HLR        /* MAP_HLR */
#define GSN        /* MAP_GSN */
#define MLC        /* MAP_MLC */
#define REL98      /* MAP_R98 */
/*#define REL99       MAP_R99 */

/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif

#endif /* AU */

#ifdef MA       /* SS7 MAP */
/**************************************************************************
   SS7 MAP parameters
**************************************************************************/
#undef MA
#define MA 1

/* interfaces */

/* upper interface, choose none or more */

/* #define LCMAUIMAT       loosely coupled, MAP  upper layer */
/* #define LWLCMAUIMAT     loosely coupled, MAP  upper layer */

/* lower interface, data link, choose none or more */

/* #define LCMALISTU       loosely coupled, TCAP lower layer */

/* management interface, lma , choose none or more */

/* #define LCMAMILMA       loosely coupled, layer management */

#define STU2               /* new lower interface */
 
#define MAT_INTF2          /* new upper interface */
 
#define MA_LMINT3          /* new management interface. turning off
                              requires SMMA_LMINT3 flag also to be
                              turned off in #ifdef SM section */
 
/****************************** Interfaces Version Flags ******************/

/* Upper interface */
#define MATV1      1       /* Upper interface version 1.0 */
#define MATV2    1       /*Upper interface version 2.0 */
/* #define MATV3    1       Upper interface version 3.0 */

/* Lower interface */
/* #define STUV1      1        Lower interface version 1.0 */
/* #define STUV2    1          Lower interface version 2.0 */

/* layer management options */
/* #define LMAV1    1          Layer Management interface version 1.0 */
/* #define LMAV2      1        Layer Management interface version 2.0 */
/* #define LMAV3      1        Layer Management interface version 3.0 */


/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCMALM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCMALM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCMALM          /* tightly coupled, layer management */
/* #define LCMALM           loosely coupled, layer management */
#endif
#endif

#ifdef LCMAUIMAT
#ifndef LCMAT
#define LCMAT 1
#endif
#endif /* LCMAUIMAT */

#ifdef LWLCMAUIMAT
#ifndef LWLCMAT
#define LWLCMAT 1
#endif
#endif /* LWLCMAUIMAT */


#ifdef LCMALISTU
#ifndef LCSTU
#define LCSTU 1
#endif
#endif /* LCMALISTU */

#ifdef LCMAMILMA
#ifndef LCLMA
#define LCLMA 1
#endif
#endif /* LCMAMILMA */

#if (LCSTU || LCLMA || LCLAU)
#ifndef LCSS7
#define LCSS7 1
#endif
#endif /* LCSTU || LCLMA || LCLAU*/

#ifdef LMINT3
#ifdef MA_LMINT3
#undef MA_LMINT3
#define MA_LMINT3 1
#define LMA_LMINT3
#endif /* MA_LMINT3 */
#endif /* LMINT3 */
 
/* product specific options */
#define MSC     /* MAP MSC */
#define VLR     /* MAP_VLR */
#define HLR     /* MAP_HLR */
#define GSN     /* MAP_GSN */
#define MLC     /* MAP_MLC */
#define REL98   /* MAP_R98 */
/*#define REL99    MAP_R99 */

/* product specific flags introduced in MAP-GSM release 1.6 */
/*#define MAP_REL4   1         MAP release 4 database */
/*#define MAP_SEC    1         MAPsec */
/*#define MAP_REL5   1         MAP release 5 data base */
/*#define MAP_REL6   1         MAP release 6 data base */
/*#define MAP_REL7   1         MAP release 7 data base */
/*#define MAP_REL7V15   1      MAP release 7.15.0 data base */
/*#define MAP_REL8   1         MAP release 8 data base */
/*#define MAP_REL9   1         MAP release 9 data base */

/* #define MA_CUSTOM_HOOK       customer hook for security function */
/* #define MA_SECPDU_BUILD      Dialogure PDU in secure mode */

#define MA_STATIC_EVT_STRUCT /* Static/Dynamic memory scheme   */

/* Following flags are MAP segmentation related flags */
/* #define MA_SEG               enable MAP segmentation feature */
/* #define MA_MULT_SEG_DECODE   all operation message segments are queued */

/* Following flags are introduced only for the upper layer interface changes*/
/* #define MA_REF_NMB_CHANGE */

/* The following flag is used to testing early operation response in MAP 
** acceptance test */
/* #define MA_ACC_OPRRSP_CHANGE */

/* The following flag is used for testing the exception handling in MAP */
/* #define MAACC_EXCEPTION_TST   */

/* Enable the MA_FTHA flag when operating MAP  in a 
** distributed/ fault tolerant  mode or when any MAP  provider or user
** (Trillium supplied) is distributed/fault tolerant 
*/
/* #define MA_FTHA         SHT interface flag. */

/* #define MA_RUG        Rolling upgrade support enabled */

/* In a fault tolerant environment, to prevent system manager from
** binding and enabling the lower saps uncomment the following flag 
*/
/* #define MA_DIS_SAP      Disable lower saps */

/* MAP-GSM Debug flag to enable all debug printing from the start */
#define MA_DEBUG 1

/* MAP-GSM Alarm flag to enable alarms from the beginning */
#define MA_USTA 1


/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif

/* Compile time define dependency checks */

#ifdef MAP_REL7
#ifndef MAP_REL7_V15
#error "MAP_REL7 requires MAP_REL7_V15 flag"
#endif /* MAP_REL7_V15 */
#endif /* MAP_REL7 */

/* Check for LMAV2 */
#ifdef LMAV2
#ifndef MAP_SEC
#error "LMAV2 interface requires MAP_SEC flag"
#endif /* MAP_SEC */
#endif /* LMAV2 */

/* Check for MAP_SEC */
#ifdef MAP_SEC
#ifndef LMAV2
#error "MAPsec Feature requires LMAV2 interface flag"
#endif /* LMAV2 */
#endif /* MAP_SEC */

/* Check for MAP_REL99 */
#ifdef MAP_SEC
#ifndef REL99
#error "MAPsec Feature is available for REL99 only"
#endif /* REL99 */
#endif /* MAP_SEC */

#ifdef MAP_REL4
#ifndef REL99
#error "MAP_REL4 cannot be defined without REL99"
#endif /* REL99 */
#endif /* MAP_REL4 */

#ifdef MAP_REL5
#ifndef MAP_REL4
#define RAM_REL4
#endif /* MAP_REL4 */
#endif /* MAP_REL5 */

#ifdef MAP_REL6
#ifndef MAP_REL5
#define MAP_REL5
#endif /* MAP_REL5 */
#endif /* MAP_REL6 */

#ifdef MAP_REL7
#ifndef MAP_REL6
#define MAP_REL6
#endif /* MAP_REL6 */
#ifndef MAP_R7_SEC_SUPP
#undef MAP_SEC
#endif /* MAP_R7_SEC_SUPP */
#endif /* MAP_REL7 */

#ifdef MAP_REL8
#ifndef MAP_REL7
#define MAP_REL7
#endif /* MAP_REL7 */
#endif /* MAP_REL8 */

#ifdef MAP_REL9
#ifndef MAP_REL8
#define MAP_REL8
#endif /* MAP_REL8 */
#endif /* MAP_REL9 */
/* Rolling Upgrade compliance */

/* Check for TDS_CORE2 */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#error "Rolling Upgrade Feature is available in CORE II only"
#endif /* TDS_CORE2 */
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

/* Check for TDS_ROLL_UPGRADE_SUPPORT */
#ifdef MA_RUG
#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "MA_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
#endif /* MA_RUG */

/* Check for MA_FTHA  */
#ifdef MA_RUG
#ifndef MA_FTHA
#error "MA_FTHA flag is mandatory for Rolling Upgrade. Please enable"
#endif /* MA_FTHA */
#endif /* MA_RUG */

/* Check for MAT_INTF2  */
#ifdef MA_RUG
#ifndef MAT_INTF2
#error "MAT_INTF2 flag is mandatory for Rolling Upgrade.Please enable"
#endif /* MAT_INTF2 */
#endif /* MA_RUG */

/* Check for STU2  */
#ifdef MA_RUG
#ifndef STU2
#error "STU2 flag is mandatory for Rolling Upgrade.Please enable"
#endif /* STU2 */
#endif /* MA_RUG */

/* Check for ST_LMINT3 */
#ifdef MA_RUG
#ifndef MA_LMINT3
#error "MA_LMINT3 flag is mandatory for Rolling Upgrade. Please enable"
#endif /* MA_LMINT3 */
#endif /* MA_RUG */

/* Check for SMMA_LMINT3 */
#ifdef MA_RUG
#ifndef SMMA_LMINT3
#error "SMMA_LMINT3 flag is mandatory for Rolling Upgrade. Please enable"
#endif /* SMMA_LMINT3 */
#endif /* MA_RUG */

/* Check for LMA_LMINT3 */
#ifdef MA_RUG
#ifndef LMA_LMINT3
#error "LMA_LMINT3 flag is mandatory for Rolling Upgrade. Please enable"
#endif /* LMA_LMINT3 */
#endif /* MA_RUG */

/* End of dependency checking for Rolling Upgrade */

#endif /* MA */


#ifdef LM       /* LAPDm */
/**************************************************************************
  GSM LAPDm parameters
**************************************************************************/
#undef LM
#define LM 1

/* interfaces */

/* upper interface, choose none or more */

#define LCLMUILMU   /*     loosely coupled, LAPDm  upper layer */

/* lower interface, data link, choose none or more */

#define LCLMLILML   /*     loosely coupled, L1 lower layer */

/* management interface, llm , choose none or more */

#define LCLMMILLM    /*    loosely coupled, layer management */

/****************************** Interfaces Version Flags ******************/

/* Upper interface */
/* #define LMUV1      1        Upper interface version 1.0 */

/* Lower interface */
/* #define LMLV1      1        Lower interface version 1.0 */

/* layer management options */
/* #define LLMV1    1          Layer Management interface version 1.0 */

#define LMINT3       /* interface 3 */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCLMLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCLMLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCLMLM          /* tightly coupled, layer management */
/* #define LCLMLM           loosely coupled, layer management */
#endif
#endif

#ifdef LCLMUILMU
#ifndef LCLMU
#define LCLMU 1
#endif
#endif /* LCLMUILMU */

#ifdef LCLMLILML
#ifndef LCLML
#define LCLML 1
#endif
#endif /* LCLMLILML */

#ifdef LCLMMILLM
#ifndef LCLLM
#define LCLLM 1
#endif
#endif /* LCLMMILLM */

/* #define LMACC_EXCEPTION_TST   */

/* LAPDm Debug flag to enable all debug printing from the start */
#define LM_DEBUG 1

/* MAP-GSM Alarm flag to enable alarms from the beginning */
#define LM_USTA 1

/* Compile time define dependency checks */

#endif /* LM */


/**************************************************************************
   PSF-MAP (FT/HA) parameters
**************************************************************************/
#ifdef ZJ       /* SS7 PSF-TCAP (FT/HA) */

#undef ZJ
#define ZJ 1

/* Options to enable alarms/debug mask during compile time */
#define ZJ_USTA           /* Uncomment to enable alarms by default */
#define ZJ_DEBUG          /* Uncomment to enable all debug prints by default */

/* interfaces */

/* management interface, lzt , choose none or more */
#define LCZJMILZJ         /* loosely coupled, layer management */

/* The following flag must be turned-on if the customer chooses to 
** implement their own packing-unpacking functions for update messages 
*/
/* #define TDS_FTHA_CUST_PKUNPK */

/****************************** Interfaces Version Flags ******************/

/* Peer interface */
#define ZJPV1              /* Upper interface version 1.0 */

/* Layer management interface */
#define LZJV1              /* Layer Management interface version 1.0 */

/* dependency of ZJ and MA_FTHA */
#ifndef MA_FTHA
#define MA_FTHA
#endif

/* dependency of TDS_CORE2 and ZJ_DFTHA */
#ifndef TDS_CORE2
#ifdef ZJ
#error "Please define TDS_CORE2 in make file"
#endif /* ZJ */
#endif /* TDS_CORE2 */

/* These flags must not be turned-off for PSF-TCAP */

#ifdef LCZJMILZJ
#ifdef LCLZJ
#undef LCLZJ
#endif
#define LCLZJ    1
#endif /* LCZJMILZJ */

#ifndef STU2
#define STU2               /* new lower interface */
#endif /* STU2 */

#ifndef MAT2
#define MAT2               /* new upper interface */
#endif /* MAT2 */

/* Note : Make sure that the flag SMST_LMINT3 in #ifdef SM 
** section above and flag LMINT3 above are also turned-on 
*/
#ifdef MA_LMINT3
#undef MA_LMINT3  
#endif /* ST_LMINT3 */
#define MA_LMINT3  1

#ifndef LMA_LMINT3
#define LMA_LMINT3
#endif /* LMA_LMINT3 */

/* 1. Check for old MAT interface */
#ifndef MAT2
#warning "Please define MAT22 in #ifdef MA section of envopt.h if no backward compatibility concerns"
#if (ZJ && MA_FTHA)
#error "FTHA architechture requires MAT2. Please define it in the #ifdef MA section of envopt.h"
#endif /* (ZJ && MA_FTHA) */
#endif /* STU2 */

/* 2. Check for old STU interface */

#ifndef STU2
#warning "Please define STU2 in #ifdef MA section of envopt.h if no backward compatibility concerns"
#if (ZJ && MA_FTHA)
#error "FTHA architechture requires STU2. Please define it in the #ifdef MA section of envopt.h"
#endif /* (ZT && ST_FTHA) */
#endif /* STU2 */

#endif /* ZJ */


#ifdef IA       /* SS7 MAP IS-41 */
/**************************************************************************
   SS7 MAP parameters
**************************************************************************/
#undef IA
#define IA 1

/* interfaces */

/* upper interface, choose none or more */

/* #define LCIAUIIAT      loosely coupled, MAP User upper layer */

/* lower interface, data link, choose none or more */

/* #define LCIALISTU      loosely coupled, TCAP lower layer */

/* management interface, lma , choose none or more */

/* #define LCIAMILIA      loosely coupled, layer management */

/*** Interface Backward Compatiblity Options ***/

/* flags should be turned off for backward compatibility */

/*#define STU2                new lower interface */

/*#define IAT2                new upper interface */

/* #define STUV2           Upper interface version 2.0 */
/* #define IATV2           Upper interface version 2.0 */

#define IA_LMINT3          /* new management interface. turning off 
                              requires SMIA_LMINT3 flag also to be 
                              turned off in #ifdef SM section */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCIALM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCIALM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCIALM          /* tightly coupled, layer management */
/* #define LCIALM       loosely coupled, layer management */
#endif
#endif

#ifdef LCIAUIIAT

#ifndef LCIAT
#define LCIAT 1
#endif

#endif /* LCIAUIIAT */

#ifdef LCIALISTU

#ifndef LCSTU
#define LCSTU 1
#endif

#endif /* LCIALISTU */

#if (defined(LCIAMILIA) || defined(LCSMIAMILIA))
#ifndef LCLIA
#define LCLIA 1
#endif
#endif /* LCIAMILIA || LCSMIAMILIA */

#if (LCSTU || LCLIA || LCLAU)

#ifndef LCSS7
#define LCSS7 1
#endif

#endif /* LCSTU || LCLIA || LCLAU*/

#ifdef LMINT3
#ifdef IA_LMINT3
#undef IA_LMINT3
#define IA_LMINT3 1
#endif /* IA_LMINT3 */
#endif /* LMINT3 */

/* product specific options */
#define MSC        /* IA_MSC */
#define VLR        /* IA_VLR */
#define HLR        /* IA_HLR */
#define SCP        /* IA_SCP */

/*Feature options */
/*#define IA_OLD_BND_FLAG  old bind request handling */
/*#define IA_BROADCAST_SUPPORT SMS broadcast support  */
/*#define SS7_IS41F        TIA/EIA - 41F */
/*#define SS7_IS41E        TIA/EIA - 41E */
/*#define SS7_IS41D        TIA/EIA - 41D */
/*#define WIN_IS771        WIN IS771 feature */
/*#define WIN_IS826        WIN IS826 feature */
/*#define WIN_IS848        WIN IS848 feature */
/*#define IA_PREPAID_SUP   Prepaid support */
/*#define IA_FTHA          Enable if IS41 is run in distributed fault
                           tolerant mode */
/*#define IA_SS7_ANS88     ansi option */
/*#define ASN1_INCOMPATIBLE not compatible with ansi standards */
/*#define IA_DIS_SAP       Stack manager controlling entity */
/*#define IA_CLOSE_REQ     close req */

#define ANS88            /* ansi, option 12 */
#define ANS92            /* ansi, option 12 */

/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif

/* Check for SS7_IS41F */
#ifdef IA_BROADCAST_SUPPORT
#ifndef SS7_IS41F
#define SS7_IS41F
#endif /* SS7_IS41F */
#endif /* IA_BROADCAST_SUPPORT */

/* Check for SS7_IS41E */
#ifdef SS7_IS41F
#ifndef SS7_IS41E
#define SS7_IS41E
#endif /* SS7_IS41E */
#endif /* SS7_IS41F */

/* Check for WIN_IS771, WIN_IS826 & WIN_IS826 */
#ifdef SS7_IS41E
#ifndef WIN_IS771
#define WIN_IS771
#endif /* WIN_IS771 */
#ifndef WIN_IS826
#define WIN_IS826
#endif /* WIN_IS826 */
#ifndef WIN_IS848
#define WIN_IS848
#endif /* WIN_IS848 */
#endif /* SS7_IS41E */

/* Check for IA_PREPAID_SUP */
#if (defined(WIN_IS771) || defined(WIN_IS826) || defined(WIN_IS848))
#ifndef IA_PREPAID_SUP
#define IA_PREPAID_SUP
#endif /* IA_PREPAID_SUP */
#endif /* (defined(WIN_IS771) || defined(WIN_IS826) || defined(WIN_IS848)) */

/* Check for SS7_IS41D */
#ifdef IA_PREPAID_SUP
#ifndef SS7_IS41D
#define SS7_IS41D 
#endif /* SS7_IS41D */
#endif /* IA_PREPAID_SUP */

#endif /* IA */

#ifdef IU       /* SS7 MAP User */
/**************************************************************************
   SS7 MAP User parameters
**************************************************************************/
#undef IU
#define IU 1

/* interfaces */

/* upper interface, choose none or more */

/* #define LCIUUIMIU     loosely coupled, MAP User upper layer */

/* lower interface, data link, choose none or more */

/* #define LCIULIIAT    loosely coupled, MAP lower layer */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCIULM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCIULM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCIULM          /* tightly coupled, layer management */
/* #define LCIULM           loosely coupled, layer management */
#endif
#endif

#ifdef LCIUUIMIU

#ifndef LCMIU
#define LCMIU 1
#endif

#endif  /* LCIUUIMIU */

#ifdef LCIULIIAT

#ifndef LCIAT
#define LCIAT 1
#endif

#endif  /* LCIULIIAT */

#ifdef LCIUMILIU

#ifndef LCLIU
#define LCLIU 1
#endif

#endif  /* LCIULIIAT */

#if (LCIAT || LCIU || LCLIA)

#ifndef LCSS7
#define LCSS7 1
#endif

#endif  /* LCSTU || LCTCU || LCLTU */

/* product specific options */

#define MSC        /* IA_MSC */
#define VLR        /* IA_VLR */
#define HLR        /* IA_HLR */
#define SCP        /* IA_SCP */
/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif

#endif /* IU */


#ifdef IE       /* INAP */
/**************************************************************************
   INAP parameters
**************************************************************************/
#undef IE
#define IE 1

/* product version, choose one */

/* interfaces */

/* upper interface, choose none or more */

/* #define LCIEUIIET       loosely coupled, INAP User upper layer */

/* lower interface, data link, choose none or more */

/* #define LCIELISTU       loosely coupled, TCAP lower layer */

/* management interface, lst , choose none or more */

/* #define LCIEMILIE       loosely coupled, INAP layer management */

/*** Interface Backward Compatiblity Options ***/

/* flags should be turned off for backward compatibility */

#define STU2               /* new lower interface */

#define IET2               /* new upper interface */

#define LIE_LMINT3         /* new management interface. */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCIELM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCIELM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCIELM          /* tightly coupled, layer management */
/* #define LCIELM           loosely coupled, layer management */
#endif
#endif

#ifdef LCIEUIIET

#ifndef LCIET
#define LCIET 1
#endif

#endif /* LCIEUIIET */

#ifdef LCIELISTU

#ifndef LCSTU
#define LCSTU 1
#endif

#endif /* LCIELISTU */

#ifdef LCIEMILIE

#ifndef LCLIE
#define LCLIE 1
#endif

#endif /* LCIEMILIE */

#if (LCIET || LCSTU || LCLIE)

#ifndef LCSS7
#define LCSS7 1
#endif

#endif /* LCIET || LCSTU || LCLIE */

/* product specific options */

/* variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with TCAP variant */

/* #define ITU_SS7           ccitt/itu */
/* #define ETSI_SS7          etsi */
/* #define AIN_SCP           Bellcore AINGR SSP-SCP Interface */
/* #define AIN_IP            Bellcore AINGR SSP-IP Interface */

/* TCAP variants, choose none or more */
/* must agree with TCAP option being used */
/* #define ANS88         ansi, option 12 */
/* #define ANS92         ansi, option 12 */
/* #define ANS96         ansi, option 12 */
/* #define ETSI_SS7      etsi, option 17 */

/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif

#endif


/**************************************************************************
                                CAP parameters
**************************************************************************/
#ifdef QC       /* CAP */ 
#undef QC
#define QC 1

/*
 ************************** Interfaces Coupling Options ******************
 */

/* enable following options depending upon coupling requirements */
/* #define LCQCLISTU    loosely coupled, lower i/f of CAP with TCAP */ 
/* #define LCSTUISTU    loosely coupled, upper i/f of TCAP with user */
/* #define LCQCMILQC    loosely coupled, management i/f of CAP */ 
/* #define LCSMQCMILQC  loosely coupled, SM i/f */
/* #define LCCULICAP    loosely coupled, lower i/f of user with CAP */ 
/* #define LCQCUICAP    loosely coupled, upper i/f of CAP with user */ 
/* #define LWLCCAP      light weight loosely coupled */ 
/* #define LWLCCULICAP  light weight loosley coupled, lower i/f of user 
                        with CAP, to be enabled with LWLCCAP only */
/*
 ************************** Interface Version ****************************
 */

/************************* Upper  Interfaces ****************************/
/* enable the required CAP upper interface version */
#define CAPV2     /* CAP version 2 */
#define CAPV3     /* CAP version 3 */
#define CAPV4     /* CAP version 4 */
#define CAPV5     /* CAP version 5 */
#define CAPV6     /* CAP version 6 */

/************************* Lower  Interfaces *****************************/
/* enable the required CAP lower interface version */
#define STUV2   /* TCAP Version 2 */

/********************** Management Interfaces ***************************/
#define LQCV1    /* Version 1 on management i/f */
#define LQCV2    /* Version 1 on management i/f: for CAMEL Phase 4 */

/*************** Rolling Upgrades: All must be enabled *****************/
/* #define QC_RUG    * To Support rolling updgrades */


/* 
 ************************* Layer Manager Options *************************
 */ 
/* #define QC_USTA          *  Enable alarms at initialization */

/* Select one of the following for backward compatibility */
/* #define LCLM      */
/* #define TCLM      */
/* #define LCQLM     */
/* #define TCQLM     */

/************************ Do not modify following ***********************/
#ifdef LCLM

/* choose all */
#define LCQCLM          /* loosely coupled, layer management */

#else

#ifdef TCLM             /* backward compatilbility, layer management */

/* choose all */
#define TCQCLM          /* tightly coupled, layer management */

#endif /* TCLM */

#endif /* LCLM */


/* 
 ********************** Product Features Options *************************
 */ 
/* CAMEL Functionality: select any one or more */
#define GSMSCF       /* Service Control Function */
/* #define GSMSRF     * Specialized Resouce Function */
/* #define GSMSSF     * Service Switching Function */ 
/* #define GPRSSSF    * GPRS Service Switching Function, to be enabled with
                        QC_JUNE01 option only */

/* Various comppatibility options */
#define QC_PH1PH2    /*  Enable for phase1 and phase2 compatibility */
#define QC_JUNE01    /*  Enable for phase3 compatibility */
#define QC_DEC01     /*  To increase the mobile station radio access
                      *  capability size from 32 to 64 */
#define QC_SEP02     /*  To comply with TS 29.078 v 4.6.0*/
#define QC_PH4       /*  To comply with TS 29.078 v 5.9.0, v 6.4.0
                      *  and 29.278 v 5.4.0, v 6.1.0 */

/************************ Do not modify following ***********************/
/* enable appropriate flags for GSM SCF */
#ifdef GSMSCF
#define QC_FE_GSMSRF
#define QC_FE_GSMSSF
#define QC_FE_GPRSSSF

#ifdef QC_PH4
#define QC_FE_IMSSF
#endif /* QC_PH4 */

#endif  /* GSMSCF */

/* enable appropriate flags for GSM SRF */
#ifdef GSMSRF
#define QC_FE_GSMSRF
#endif /* GSMSRF */

/* enable appropriate flags for GSM SSF */
#ifdef GSMSSF 
#define QC_FE_GSMSSF
#endif /* GSMSSF */

/* enable appropriate flags for GPRS SSF */
#ifdef GPRSSSF
#define QC_FE_GPRSSSF
#endif /* GPRSSSF */


/*
 **************************** General Options ****************************
 */ 
/* #define QC_FTHA              * Enables FT/HA, TDS_CORE2 must be enabled */
/* #define QC_DEBUG             * Enable debug at initialization */
/* #define CM_ASN_DBG           * Enable ASN debugging */
/* #define DEBUGP               * Enable debug printing */
/* #define CM_ASN_NO_INDEF_LEN  * ASN.1 indefinate length */

/* 
 *************************** Local defines *******************************
 */
#ifndef LCSMQCMILQC
#define PTSMQCMILQC   1      /* portable QC LM interface */
#else
#ifndef QC
#define PTSMQCMILQC   1      /* portable QC LM interface */
#else
#ifndef LWLCSMQCMILQC
#define PTSMQCMILQC   1      /* portable QC LM interface */
#endif
#endif
#endif

/************************** qc_ptui.c defines ***************************/
#ifndef LCQCUICAP
#define PTQCUICAP 1     /* portable UI interface */
#else
#ifndef CU
#define PTQCUICAP 1     /* portable UI interface */
#else
#ifndef LWLCCAP
#define PTQCUICAP 1     /* portable UI interface */
#endif
#endif
#endif

/************************** qc_ptli.c defines ***************************/
#ifndef LCQCLISTU
#define PTQCLISTU   1      /* portable LI interface */
#else
#ifndef ST
#define PTQCLISTU   1      /* portable LI interface */
#else
#ifndef LWLCQCLISTU
#define PTQCLISTU   1      /* portable LI interface */
#endif
#endif
#endif

/************************** qc_ptmi.c defines ***************************/
#ifndef LCQCMILQC
#define PTQCMILQC   1      /* portable LM interface */
#else
#ifndef SM
#define PTQCMILQC   1      /* portable LM interface */
#else
#ifndef LWLCQCMILQC
#define PTQCMILQC   1      /* portable LM interface */
#endif
#endif
#endif

#ifdef LCQCUICAP

#ifndef LCCAP
#define LCCAP 1
#endif

#endif /* LCQCUICAP */

#ifdef LCQCLISTU

#ifndef LCSTU
#define LCSTU 1
#endif

#endif /* LCQCLISTU */

#ifdef LCQCMILQC

#ifndef LCLQC
#define LCLQC 1
#endif

#endif /* LCQCMILQC */

#if (LCCAP || LCSTU || LCLQC)

#ifndef LCSS7
#define LCSS7 1
#endif

#endif /* LCCAP || LCSTU || LCLQC */

/*
 ***************** Do not change following definitions *******************
 */
#define SS7
#define SM_SS7
#define STATIC_SM
#define CM_ASN_NO_INDEF_LEN /* ASN no indefinate lenght */ 
#define QC_SHT_GRPTYPE_ALL 

/*
 ************** Define dependency checks (DO NOT CHANGE!!) ***************
 */

#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#error "Rolling upgrade feature available in CORE II only."
#endif
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

#ifdef QC_RUG

#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "QC_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif

#ifndef QC_FTHA
#error "QC_RUG cannot be defined without QC_FTHA"
#endif

#endif /* QC_RUG */

/* Dependency of GPRSSSF and QC_JUNE01 */
#ifdef GPRSSSF

#ifndef QC_JUNE01
#error "Please define QC_JUNE01 for GPRSSSF"
#endif /* QC_JUNE01 */

#endif /* GPRSSSF */

/* dependencies of QC_PH4 */
#ifdef QC_PH4

#if !defined(QC_PH1PH2) || !defined(QC_JUNE01) || !defined(QC_DEC01) || \
    !defined(QC_SEP02)  || !defined(GSMSCF)    || !defined(CAPV2)    || \
    !defined(CAPV3)     || !defined(CAPV4)     || !defined(CAPV5)    || \
    !defined(CAPV6)     || !defined(LQCV2)     || !defined(STUV2)
#error "Please define QC_PH1PH2, QC_JUNE01, QC_DEC01, QC_SEP02, GSMSCF, \
CAPV2, CAPV3, CAPV4, CAPV5, CAPV6, LQCV2 and STUV2 for QC_PH4"

#endif /* dependencies of QC_PH4 */

#endif /* QC_PH4 */

/* dependency of QC_FE_IMSSF */
#ifdef QC_FE_IMSSF

#ifndef QC_PH4
#error "Please define QC_PH4 for QC_FE_IMSSF"
#endif /* QC_PH4 */

#endif /* QC_FE_IMSSF */

#endif /* QC */


/**************************************************************************
                        PSF-CAP (FT/HA) parameters
**************************************************************************/
#ifdef ZF      /* PSF-CAP */ 
#undef ZF
#define ZF 1

/*
 ************************** Interfaces Coupling Options ******************
 */

/* enable following options depending upon coupling requirements */
/* #define LCZFMILZF    loosely coupled, management i/f of CAP */ 
/* #define LCSMZFMILZF  loosely coupled, SM i/f */

/*
 ************************** Interface Version ****************************
 */
/* #define LZFV1     * Layer manager interface version */
/* #define ZFPV1     * Peer interface version */

/*
 ************************** LM Configuration  ***************************
 */

/* #define ZF_USTA      * enable alarms by default */
/* #define ZD_DEBUG     * enable debug prints by deault (only for debugging) */

/*
 ************************** Miscleneous Flags ****************************
 */

/* #define TDS_FTHA_CUST_PKUNPK    Enable, if pack/unpack functionality
                                   is provided by the customer */

/*
 ********************* INTERNAL FLAGS (Do not modify!) *******************
 */

#ifdef LCZFMILZF
#ifdef LCLZF
#undef LCLZF
#endif
#define LCLZF 1
#endif /* LCZFMILZF */

#ifndef QC_FTHA
#define QC_FTHA
#endif

#ifndef CAPV5
#define CAPV5
#endif

#ifndef TDS_CORE2
#error "Please define TDS_CORE2 in make file"
#endif

#ifndef CAPV5
#error "Please define CAPV5 in #ifdef QC section"
#endif

#ifndef QC_FTHA
#error "Please define QC_FTHA in #ifdef QC section"
#endif

#endif /* ZF */


/**************************************************************************
   SS7 TCAP parameters
**************************************************************************/
#ifdef ST       /* SS7 TCAP */

#undef ST
#define ST 1

/* Enable the ST_FTHA flag when operating TCAP  in a 
** distributed/ fault tolerant  mode or when any TCAP  provider or user
** (Trillium supplied) is distributed/fault tolerant 
*/
/* #define ST_FTHA         SHT interface flag. */

/* In a fault tolerant environment, to prevent system manager from
** binding and enabling the lower saps uncomment the following flag 
*/
/* #define ST_DIS_SAP       Disable lower saps */

/* Options to enable alarms/debug mask during compile time */
/* #define ST_USTA           Uncomment to enable alarms by default */
/* #define ST_DEBUG          Uncomment to enable all debug prints by default */

/* Option to enable Duplicate invoke ids when they are originated 
** from different entities(user/provider)
*/ 
/* #define INVOKE_ID_FLAG    Uncomment to enable duplicate invoke ids */

/* interfaces */

/* upper interface, choose none or more */
/* #define LCSTUISTU       loosely coupled, TCAP User upper layer */

/* lower interface, data link, choose none or more */
/* #define LCSTLISPT       loosely coupled, SCCP lower layer */

/* management interface, lst , choose none or more */
/* #define LCSTMILST       loosely coupled, layer management */

/*** Bind Confirm Interface Backward Compatiblity Options ***/
/* flags should be turned off for backward compatibility */
#define SPT2               /* new lower interface */
/*#define STU2                new upper interface */

/* New layer manager interface-3 flag for the TCAP product 
** Turning off this flag requires SMST_LMINT3 flag also to be
** turned off in SM section
*/
#define ST_LMINT3          /* new management interface. */

/* #define ST_RUG        Rolling upgrade support enabled */
/****************************** Interfaces Version Flags ******************/

/* Upper interface */
/*#define STUV1              Upper interface version 1.0 */
/* #define STUV2           Upper interface version 2.0 */

/* Lower interface */
/* #define SPTV1              Lower interface version 1.0 */
/* #define SPTV2               Lower interface version 2.0 */

/* Layer management interface */
#define LSTV1              /* Layer Management interface version 1.0 */

/* If LCSTUISTU is defined then define LCSTU to 1 */
#ifdef LCSTUISTU
#ifdef LCSTU
#undef LCSTU 
#endif /* LCSTU */
#define LCSTU 1
#endif /* LCSTUISTU */

/* If LCSTLISPT is defined, then define LCSPT to 1 */
#ifdef LCSTLISPT
#ifdef LCSPT
#undef LCSPT 
#endif /* LCSPT */
#define LCSPT 1
#endif /* LCSTLISPT */

#ifdef LCSTMILST
#ifdef LCLST
#undef LCLST 
#endif /* LCLST */
#define LCLST 1
#endif /* LCSTMILST */

/* If anyone of LCSTU/LCSPT/LCLST defined then define LCSS7 to 1*/
#if (LCSTU || LCSPT || LCLST)
#ifdef LCSS7
#undef LCSS7 
#endif /* LCSS7 */
#define LCSS7 1
#endif /* LCSTU || LCSPT || LCLST */

/* If LMINT3 and ST_LMINT3 defined then define ST_LMINT3 to 1 */
#ifdef LMINT3
#ifdef ST_LMINT3
#undef ST_LMINT3
#endif /* ST_LMINT3 */
#define ST_LMINT3 1
#endif /* LMINT3 */

/* If ST_LMINT3 or SMST_LMINT3 defined, then define LST_LMINT3*/
#if (ST_LMINT3 || SMST_LMINT3)
#ifndef LST_LMINT3
#define LST_LMINT3
#endif /* LST_LMINT3 */
#endif /* ST_LMINT3 || SMST_LMINT3) */

/* product specific options */
/* variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with mtp 3 variant */
/* #define BELL          bellcore, option 11 */
/* #define ANS88         ansi, option 12 */
/* #define ANS92         ansi, option 12 */
/* #define ANS96         ansi, option 12 */
/* #define ETSI_SS7      etsi, option 17 */
/* #define TTC           ttc, japan, option 13 */

/* type, chosen automatically */
#ifndef SS7
#define SS7             /* for message functions */
#endif /* SS7 */

#endif /* ST */


/**************************************************************************
   SS7 PSF-TCAP (FT/HA) parameters
**************************************************************************/
#ifdef ZT       /* SS7 PSF-TCAP (FT/HA) */

#undef ZT
#define ZT 1

/* #define ZT_DFTHA     distributed PSF - MTP3 environment */

/* Options to enable alarms/debug mask during compile time */
/* #define ZT_USTA           Uncomment to enable alarms by default */
/* #define ZT_DEBUG          Uncomment to enable all debug prints by default */

/* interfaces */

/* management interface, lzt , choose none or more */
/* #define LCZTMILZT       loosely coupled, layer management */

/* The following flag must be turned-on if the customer chooses to 
** implement their own packing-unpacking functions for update messages 
*/
/* #define TDS_FTHA_CUST_PKUNPK */

/****************************** Interfaces Version Flags ******************/

/* Peer interface */
#define ZTPV1              /* Upper interface version 1.0 */

/* Layer management interface */
#define LZTV1              /* Layer Management interface version 1.0 */

/* dependency of ZT and ST_FTHA */
#ifndef ST_FTHA
#define ST_FTHA
#endif

/* dependency of TDS_CORE2 and ZT_DFTHA */
#ifndef TDS_CORE2
#ifdef ZT_DFTHA
#error "Please define TDS_CORE2 in make file"
#endif /* ZT_DFTHA */
#endif /* TDS_CORE2 */

/* These flags must not be turned-off for PSF-TCAP */

#ifdef LCZTMILZT
#ifdef LCLZT
#undef LCLZT
#endif
#define LCLZT    1
#endif /* LCZTMILZT */

#ifndef SPT2
#define SPT2               /* new lower interface */
#endif /* SPT2 */

#ifndef STU2
#define STU2               /* new upper interface */
#endif /* STU2 */

/* Note : Make sure that the flag SMST_LMINT3 in #ifdef SM 
** section above and flag LMINT3 above are also turned-on 
*/
#ifdef ST_LMINT3
#undef ST_LMINT3  
#endif /* ST_LMINT3 */
#define ST_LMINT3  1

#ifndef LST_LMINT3
#define LST_LMINT3
#endif /* LST_LMINT3 */


#endif /* ZT */

/****************************************************************************
                         LDF - TCAP section 
****************************************************************************/
#ifdef DT  /* LDF-TCAP  */
#undef DT
#define DT 1
 
#define DT_ULDF  1       /* LDF acts as Upper load distribution function */
#define DT_LLDF  1       /* LDF acts as Lower load distribution function */
/* #define LCDTMILDT        Loosed coupled management interface */

/* Options to enable alarms/debug mask during compile time */
/* #define DT_USTA           Uncomment to enable alarms by default */
/* #define DT_DEBUG          Uncomment to enable all debug prints by default */
/* #define DT_PT_HOOK       Portable Hooks */
/*
** DT_CUSTENV should not be defined when the acceptance tests for protable 
** functions are executed. In that case dummy customer functions defined in 
** dtacclib.c file is used.
** In all other cases when the DT_PT_HOOK is defined , DT_CUSTENV also
** has to be defined. 
*/
/* #define DT_CUSTENV       Customer environment */

/* #define DT_RUG           Rolling upgrade support enabled */ 
/****************************** Interfaces Version Flags ******************/

/* TCAP Upper interface */
#define STUV1              /* Upper interface version 1.0 */

/* SCCP upper interface */
/* #define SPTV1              Lower interface version 1.0 */
#ifndef SPTV2
#define SPTV2              /* Lower interface version 2.0 */
#endif

/* Layer management interface */
#define LDTV1              /* Layer Management interface version 1.0 */
 
/******************* section not to be changed by CUSTOMERS ******************/ 
#ifdef LCDTMILDT
#ifdef LCLDT
#undef LCLDT
#endif
#define LCLDT    1
#endif /* LCDTMILDT */

/*
** By Default LDF assumes that the service user and provider 
** are present in the same processor.
** i.e. LDF interface is assumed to be BOTH ULDF and LLDF. 
** 
*/
#ifndef DT_ULDF
#ifndef DT_LLDF
#define DT_ULDF  1       /* LDF acts as Upper load distribution function */
#define DT_LLDF  1       /* LDF acts as Lower load distribution function */
#endif /* DT_LLDF */
#endif /* DT_ULDF */

#ifdef LCSTU
#undef LCSTU
#endif /* LCSTU */
#define LCSTU 1           /* Loose coupled STU interface */

#ifdef LCSPT
#undef LCSPT
#endif /* LCSPT */
#define LCSPT 1           /* Loose coupled SPT interface */

#ifndef STU2
#define STU2             /* STU bind confirm interface */
#endif /* STU2 */

#ifndef SPT2
#define SPT2             /* SPT bind confirm interface */
#endif /* SPT2 */

#ifndef LCDTLISTU
#define LCDTLISTU        /* loose coupled STU interface from DT */
#endif /* LCDTLISTU */

#ifndef LCDTUISPT
#define LCDTUISPT        /* loose coupled SPT interface from DT */
#endif /* LCDTUISPT */

#endif     /* TCAP LDF section */


#ifdef TT       /* TCAP over TCP/IP */
/**************************************************************************
   TCAP over TCP/IP parameters
**************************************************************************/
#undef TT
#define TT 1

/* product version, choose one */

/* protocol variant, choose one */

/* #define TT_SR3511       SR-3511 variant of TCAP-over-TCP/IP protocol */

/* interfaces */

/* upper interface, choose none or more */

/* #define LCTTUISPT       loosely coupled, TCAP over TCP/IP upper layer */

/* management interface, ltt , choose none or more */

/* #define LCTTMILTT       loosely coupled, TCAP over TCP/IP layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCTTLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCTTLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCTTLM          /* tightly coupled, layer management */
/* #define LCTTLM           loosely coupled, layer management */
#endif
#endif

#ifdef LCTTUISPT

#ifndef LCSPT
#define LCSPT 1
#endif

#endif /* LCTTUISPT */

#ifdef LCTTMILTT

#ifndef LCLTT
#define LCLTT 1
#endif

#endif /* LCTTMILTT */

#if (LCSPT || LCLTT)

#ifndef LCSS7
#define LCSS7 1
#endif

#endif /* LCSPT || LCLTT */

/* product specific options */

/* variants, choose none or more */
/* must agree with options delivered */
/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif

#endif /* TT - TCAP over TCP/IP */


#ifdef WS       /* SCCP wrapper */
/**************************************************************************
   SCCP Wrapper parameters
**************************************************************************/
 
/* interfaces */
   
/* management interface, lws , choose none or more */

#define LCWSMILWS       loosely coupled, layer management 

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */
 
#ifdef LCLM             /* backward compatilbility, layer management */
#define LCWSLM          /* loosely coupled, layer management */
#else

#ifdef TCLM             /* backward compatilbility, layer management */
#define TCWSLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */

#define TCWSLM          /* tightly coupled, layer management */
/* #define LCWSLM           loosely coupled, layer management */
#endif
#endif
 
/* product specific options */
/* selected in SCCP parameter section */

#endif


#ifdef SP       /* SCCP */
/**************************************************************************
   SCCP parameters
**************************************************************************/
#undef SP
#define SP 1


/****************************** Interfaces Coupling Options ******************/

/* #define LCSPUISPT    loosely coupled, SCCP upper layer */
/* #define LCSPLISNT    loosely coupled, MTP Level 3 interface */
/* #define LCSPMILSP    loosely coupled,/ layer management */
#define TDS_CORE2
#define TDS_ROLL_UPGRADE_SUPPORT

#define SP_RUG     /*   Rolling upgrade support enabled */
/****************************** Interfaces Version Flags ******************/

/* Upper interface */
/* #define SPTV1              Upper interface version 1.0 */
#ifndef SPTV2
#define SPTV2              /* Upper interface version 2.0 */
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

/* Lower interface */
#define SNTV1              /* Lower interface version 1.0 */

/* Layer management interface */
/* Release 3.2 allows only LSPV2 and higher to be uncommented */
/* #define LSPV1                 Layer Management interface version 1.0 */
#define LSPV2_8              /* Layer Management interface version 2.8 */

/********************** Interface Backward Compatibility Options *************/

/* flags should be turned off for backward compatibility ONLY */

#define SNT2               /* new lower interface */

#define SPT2               /* new upper interface */

#define SP_LMINT3          /* new management interface. turning off 
                            * requires SMSP_LMINT3 flag also to be 
                            * turned off in #ifdef SM section */

/* flags should be turned on for backward compatibility */

/* #define SP_OLD_BIND     SCCP will start bind procedure with mtp3
                           at NSAP config time */


/* flags for preserving the address */
 

#define SP_PRESERVE_ADDR   /* preserve address */


/********************** Product Specific Options *****************************/

/* connection oriented. Must agree with options delivered */
#ifndef SPCO
#define SPCO        /* connection oriented, option 02 --*/
#endif

/* Variants. Must agree with options delivered */
/* if applicable, must agree with mtp 3, isup variants */

/* #define ANS88             ansi, option 12 */
/* #define ANS92             ansi, option 12 */
/* #define SS7_ANS88   1     ansi, option 12 */
/* #define SS7_ANS92   1     ansi, option 12 */
/* #define SS7_ANS96   1     ansi, option 12 */
/* #define SS7_BELL05  1     Bell core GR246 Issue 5, option 12 */
/* #define SS7_JAPAN   1     japan, option 13 */
/* #define SS7_ITU96         ITU-T 96 */

/* #define SP_GNP            Generic numbering plan support */

/* If SCCP is used with Trillium DFTHA architechture */
#define SP_FTHA 

/* SCCP management, choose none or more */
/* #define SP_CFGMG          SCCP management */

/* #define SP_DEBUG          Enable debug at initialization */
/* #define SP_USTA           Enable alarms at initialization */

/* uncomment following flag to mark remote subsystem available on
 * receiving MTP Resume, else SST timer is started for remote SSN
 */
/* #define SP_SSA_AVAILABLE  mark remote SSN available */

/* In a fault tolerant environment, to prevent system manager from
 * binding and enabling the lower saps uncomment the following flag.
 * If this flag is uncommented, only stack manager is allowed to
 * bind and enable lower saps.
 */
/* #define SP_DIS_SAP        Disable lower saps */

/* uncomment following flag to compute traffic limitation data
 * through customized function
 */
/* #define SP_PTTRFCOMP   portable function to compute traffic lim data */

/* class 1 implementation. uncomment for old implementation.
 * SP_OLD_CLASS1 is no longer supported in sccp release 3.2 onwards */
/* #define SP_OLD_CLASS1    old class1 */
 
/* if possible, SCCP should transmit XUDT or UDT */
/* #define SP_TX_XUDT       tranmission of XUDT by default */

/* #define SP_SEG_RETOPT    set no return on error in non-first segmented
                            * XUDTs in Bellcore network */

/******************* Test case option ***************************************/
/* #define SP_CHINA_DEFINED   1  for china test cases */
/* #define SP_JAPAN_DEFINED   1  for japan test cases */

/******************** Internal Defines (DO NOT CHANGE!!!)*********************/

#ifdef LCSPLISNT

#ifdef LCSNT
#undef LCSNT
#endif
#define LCSNT 1

#endif /* LCSPLISNT */

#ifdef LCSPUISPT

#ifdef LCSPT
#undef LCSPT
#endif
#define LCSPT 1

#endif /* LCSPUISPT */

#ifdef LCSPMILSP

#ifdef LCLSP
#undef LCLSP
#endif
#define LCLSP 1

#endif /* LCSPMILSP */

#if (LCSPT || LCSNT || LCLSP)

#ifndef LCSS7
#define LCSS7 1
#endif

#endif /* LCSPT || LCSNT || LCLSP */

#ifdef LMINT3
#ifdef SP_LMINT3
#undef SP_LMINT3
#define SP_LMINT3 1
#endif
#endif

#ifndef SS7
#define SS7             /* for message functions */
#endif

/**************** Define dependency checks (DO NOT CHANGE!!) *****************/

#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#error "Rolling upgrade feature available in CORE II only."
#endif
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

#ifdef SU_RUG

#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "SU_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif
#endif /* SU_RUG */

#ifdef SP_RUG

#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "SP_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif

#ifndef SP_FTHA
#error "SP_RUG cannot be defined without SP_FTHA"
#endif

#ifndef SPT2
#error "SPT2 flag is mandatory for rolling upgrade. Please enable"
#endif

#ifndef SNT2
#error "SNT2 flag is mandatory for rolling upgrade. Please enable"
#endif

#ifndef SP_LMINT3
#error "SP_LMINT3 flag is mandatory for rolling upgrade. Please enable"
#endif

#ifdef SP_OLD_BIND
#error "SP_OLD_BIND cannot be defined for rolling upgrade. Please disable"
#endif

#ifdef SP_OLD_CLASS1
#error "SP_OLD_CLASS1 cannot be defined for rolling upgrade. Please disable"
#endif

#endif /* SP_RUG */


/* 1. Dependency of ZP and SP_FTHA */
#ifdef ZP
#ifndef SP_FTHA                
#error "Please define SP_FTHA in #ifdef SP section of envopt.h"
#endif /* SP_FTHA */
#endif /* ZP */

/* 2. Dependency of  SP_PRESERVE_ADDR and CMSS7_SPHDROPT*/
#ifdef SP_PRESERVE_ADDR
#ifndef CMSS7_SPHDROPT
#error "Please define CMSS7_SPHDROPT if using SP_PRESERVE_ADDR in #ifdef SP \
section of envopt.h"
#endif /*  CMSS7_SPHDROPT */
#endif /* SP_PRESERVE_ADDR */

/* 3. Check for old SPT interface */
#ifndef SPT2
#if (ZP && SP_FTHA)
#error "FTHA architechture requires SPT2. Please define it in the #ifdef SP \
section of envopt.h"
#endif /* (ZP && SP_FTHA) */
#endif /* SPT2 */

/* 4. Check for old SNT interface */
#ifndef SNT2
#if (ZP && SP_FTHA)
#error "FTHA architechture requires SNT2. Please define it in \
the #ifdef SP section of envopt.h"
#endif /* (ZP && SP_FTHA) */
#endif /* SPT2 */

/* 5. Check for Core1 and for ZP_DFTHA */
#ifndef TDS_CORE2
#ifdef ZP_DFTHA
#error "ZP_DFTHA cannot be define without TDS_CORE2"
#endif /* ZP_DFTHA */
#endif /* TDS_CORE2 */

#endif /* SP */


#ifdef ZP       /* SS7 PSF-SCCP (FT/HA) */
/**************************************************************************
   SS7 PSF-SCCP (FT/HA) parameters
**************************************************************************/
#undef ZP
#define ZP 1

/*********************************interfaces******************************/

/* #define LCZPMILZP       loosely coupled, layer management interface */

/****************************** Interfaces Version Flags ******************/

/* Peer interface */
/* Release 2.2 allows only ZPPV2 and higher to be uncommented */
/* #define ZPPV1                 Peer interface version 1.0 */
#define ZPPV2              /* Peer interface version 2.0 */

/* Layer management interface */
#define LZPV1              /* Layer Management interface version 1.0 */

/*********************************Misc Flags******************************/

/* #define ZP_USTA       enable alarms by default */
/* #define ZP_DEBUG      enable debug prints by deault (only for debugging) */
/* #define ZP_DFTHA      enable for operation in distributed env */


/***********************INTERNAL FLAGS (Do not modify!)********************/

#ifndef SPT2
#define SPT2
#endif /* SPT2 */

#ifndef SNT2
#define SNT2
#endif /* SNT2 */

#ifndef SP_LMINT3
#define SP_LMINT3  1
#endif /* SP_LMINT3 */

#ifdef LCZPMILZP
#ifdef LCLZP
#undef LCLZP
#endif
#define LCLZP 1
#endif /* LCZPMILZP */

#endif /* ZP */


#ifdef DP  /* LDF - SCCP */
/****************************************************************************
   LDF - SCCP flags
****************************************************************************/
#undef DP
#define DP 1

#define CMSS7_SPHDROPT   /* header option. Enable this flag for
                          * the upper layers of SCCP  as well.
                          */

/* #define LCDPMILDP        Loosed coupled management interface */

#define DP_ULDF   1      /* LDF acts as Upper load distribution function */

#define DP_LLDF   1      /* LDF acts as Lower load distribution function */

/* #define SPCO             Connection oriented services required */

/* #define ANS88            ansi, option 12 */
/* #define ANS92            ansi, option 12 */
/* #define SS7_ANS96   1    ansi, option 12 */
/* #define SS7_BELL05  1    Bell core GR246, Issue 5, option 12 */
/* #define SS7_JAPAN   1    japan, option 13 */
/* #define ITU96            ITU-T 96 */

/* #define DP_DEBUG      Enable debug at initialization */

/* #define DP_USTA       Enable alarms at initialization */

/* #define DP_PT_HOOK    Portable Hooks */

/* #define DP_RUG        Rolling upgrade support enabled */
/****************************** Interfaces Version Flags ******************/

/* SCCP Upper interface */
/* #define SPTV1                 Upper interface version 1.0 */
/* #define SPTV2                 Upper interface version 2.0 */

/* MTP3 upper interface */
#define SNTV1              /* Lower interface version 1.0 */

/* Layer management interface */
#define LDPV1              /* Layer Management interface version 1.0 */

/******************* Test case option ***************************************/
/* #define DP_CHINA_DEFINED   1  for china test cases */
/* #define DP_JAPAN_DEFINED   1  for japan test cases */

/******************* section not to be changed by CUSTOMERS ******************/

#ifdef ITU96
#define SS7_ITU96   
#endif

#ifndef SS7
#define SS7
#endif

#define LCDPLISPT        /* Loosely coupled SPT interface */
#define LCDPUISNT        /* Loosely coupled SNT interface */

#ifdef LCDPMILDP
#ifdef LCLDP
#undef LCLDP
#endif
#define LCLDP    1
#endif /* LCDPMILDP */

/*
* MUST define DP_ULDF and/or DP_LLDF.
* If (DP_ULDF not defined) and (DP_LLDF not defined)
* then LDF assumes that it acts as both ULDF and LLDF
*/

#ifndef DP_ULDF
#ifndef DP_LLDF
#define DP_ULDF  1       /* LDF acts as Upper load distribution function */
#define DP_LLDF  1       /* LDF acts as Lower load distribution function */
#endif /* DP_LLDF */
#endif /* DP_ULDF */

#ifndef SNT2
#define SNT2
#endif /* SNT2 */

#ifndef SPT2
#define SPT2
#endif /* SPT2 */

#ifndef LCSNT
#define LCSNT     1
#endif /* LCSNT */

#ifndef LCSPT
#define LCSPT     1
#endif /* LCSPT */

/**************** Define dependency checks (DO NOT CHANGE!!) *****************/

#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#error "Rolling upgrade feature available in CORE II only."
#endif
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

#ifdef DP_RUG

#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "DP_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif

#endif /* DP_RUG */

#endif /* DP */


#ifdef TU       /* SS7 TCAP User */
/**************************************************************************
   SS7 TCAP User parameters
**************************************************************************/
#undef TU
#define TU 1

/* interfaces */

/* upper interface, choose none or more */

/* #define LCTUUITCU     loosely coupled, TCAP User upper layer */

/* lower interface, data link, choose none or more */

/* #define LCTULISTU     loosely coupled, TCAP lower layer */

/* #define TU_RUG        Rolling upgrade support enabled */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCSTLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCTULM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCTULM          /* tightly coupled, layer management */
/* #define LCSTLM           loosely coupled, layer management */
#endif
#endif

#ifdef LCTUUITCU

#ifndef LCTCU
#define LCTCU 1
#endif

#endif  /* LCTUUITCU */

#ifdef LCTULISTU

#ifndef LCSTU
#define LCSTU 1
#endif

#endif  /* LCTULISTU */

#ifdef LCTUMILTU

#ifndef LCLTU
#define LCLTU 1
#endif

#endif  /* LCTULISTU */

#if (LCSTU || LCTCU || LCLTU)

#ifndef LCSS7
#define LCSS7 1
#endif

#endif  /* LCSTU || LCTCU || LCLTU */

/* product specific options */

/* variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with mtp 3 variant */

/* #define BELL          bellcore, option 11 */
/* #define ANS88         ansi, option 12 */
/* #define ANS92         ansi, option 12 */
/* #define TTC           ttc, japan, option 13 */

/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif

#endif


#ifdef TP        /* tup */
/**************************************************************************
   tup parameters
**************************************************************************/

/* product version, choose one */
 
/* #define TPVER1          tup, version 1.x */
#define TPVER2         /* tup, version 2.x */
 
/* interfaces */
 
/* upper interface, choose none or more */
 
/* #define LCTPUITPT               loosely coupled, TUP User upper layer */
 
/* lower interface, choose none or more */
 
/* #define LCTPLISNT               loosely coupled, mtp - level 3 */

/* management interface, ltp , choose none or more */

/* #define LCTPMILTP       loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCTPLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCTPLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCTPLM          /* tightly coupled, layer management */
/* #define LCTPLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */
 
/* variants, choose none or more */
/* must agree with options delivered */
/* must agree with mtp 3 variants */
 
/* #define CHINA         china */

/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif

#endif


#ifdef WN       /* MTP Level 3 wrapper */
/**************************************************************************
   MTP Level 3 Wrapper parameters
**************************************************************************/
 
/* interfaces */
   
/* management interface, lwp , choose none or more */

/* #define LCWNMILWN       loosely coupled, layer management */

/* debug mngmt interface, choose one or none, default is debug output disabled */

/* #define DBWNMILWN     debug output enabled for mngmt interface */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */
 
#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */
 
#define LCWNLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */
 
#define TCWNLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */
 
#define TCWNLM          /* tightly coupled, layer management */
/* #define LCWNLM           loosely coupled, layer management */
#endif
#endif
 
/* product specific options */

/* variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with q.930, mtp 3, sccp variants */
 
/* #define BELL          bellcore, option 11 */
/* #define ANS88         ansi, option 12 */
/* #define ANS92         ansi, option 12 */
/* #define TTC           ttc, japan, option 13 */
/* #define CHINA         china, option 15 */
 
/* type, chosen automatically */
 
#ifndef SS7
#define SS7             /* for message functions */
#endif
 
#endif


#ifdef SR       /* MTP Level 3 Simple Router */
/**************************************************************************
   MTP Level 3 Simple Router parameters
**************************************************************************/

/* product version, choose none */

#ifndef SNVER2
#define SNVER2         /* mtp level 3, version 2.x */
#endif

#ifndef SDVER2
#define SDVER2         /* mtp level 2, version 2.x */
#endif

/* interfaces */

/* upper interface, choose none or more */

/* #define LCSRUISNT     loosely coupled, MTP 3 Simple Router upper layer */

/* #define LCSRUISDT     loosely coupled, MTP 3 Simple Router upper layer */

/* lower interface, choose none or more */

/* #define LCSRLISDT     loosely coupled, MTP 3 Simple Router lower layer */

/* management interface, lsr , choose none or more */

/* #define LCSRMILSR     loosely coupled, layer management */

/* product specific options */

/* variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with q.930, mtp 3, sccp variants */
/* old style options (backward compatibility only */
 
/* #define BELL          bellcore, option 11 */
/* #define ANS88         ansi, option 12 */
/* #define ANS92         ansi, option 12 */
/* #define ANS96         ansi, option 12 */
/* #define TTC           ttc, japan, option 13 */
/* #define CHINA         china, option 15 */

/* new style options */

/* type, chosen automatically */
 
#ifndef SS7
#define SS7             /* for message functions */
#endif
 
#endif


#ifdef SN       /* MTP Level 3 */
/**************************************************************************
   MTP Level 3 parameters
**************************************************************************/
#undef SN
#define SN 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCSNUISNT        loosely coupled, MTP upper layer */

/* lower interface, data link, choose none or more */

/* #define LCSNLISDT        loosely coupled, data link layer */

/* management interface, lsn , choose none or more */

/* #define LCSNMILSN        loosely coupled, layer management */


/*** Interface Backward Compatiblity Options: flags should be turned
     off for backward comatibility  ***/

#define SN_LMINT3          /* new management interface. turning off 
                              requires SMSN_LMINT3 flag also to be 
                              turned off in #ifdef SM section */

#define SNT2           /* new upper interface */

#define SDT2           /* new lower interface */


/* #define SN_RUG       Rolling upgrade support enabled */
/****************************** Interfaces Version Flags ******************/

/* Upper interface */
#define SNTV1              /* Upper interface version 1.0 */

/* Lower interface */
#define SDTV1              /* Lower interface version 1.0 */

/* Layer management interface */
#define LSNV1              /* Layer Management interface version 1.0 */

/* old bind request generation flag */
/* #define SN_OLD_BIND     Old bind request handling: MTP3 starts
                             bind procedure with layer 2 when DLSAPs
                             are configured */


/* product specific options */

/* Enable the SN_FTHA flag when operating MTP3 in a 
 * distributed/ fault tolerant  mode or when any MTP3 user 
 * (Trillium supplied) is distributed/fault tolerant */

/* #define SN_FTHA         SHT interface flag. */

/* product specific options */
/* Options to enable alarms/debug mask during compile time */
/* #define SN_USTA           Uncomment to enable alarms by default */
/* #define SN_DEBUG          Uncomment to enable all debug prints by default */

/* uncomment following hash define to enable loopback of all the messages
 * received from the links by MTP3 */
/* #define SN_L3_LOOPBACK   Uncomment to enable loopback */

/* In a fault tolerant environment, to prevent system manager from
 * binding and enabling the lower saps uncomment the following flag */
/* #define SN_DIS_SAP       Disable lower saps */

/* variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with q.930, mtp 3, sccp variants */
/* old style options (backward compatibility only */
/* variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with q.930, mtp 3, sccp variants */
/* old style options (backward compatibility only */

/*#define ANS92          ansi, option 12 */
/*#define ANS96          ansi, option 12 */
/*#define CHINA          china, option 15 */
#define BICI           bici, option 17 
/*#define TTC            ttc, japan, option 13 */        
/*#define NTT            ntt, Japan, option 25 */
/*#define SN_SG          signalling gateway */
/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif

#ifdef LCSNMILSN

#ifndef LCLSN
#define LCLSN 1
#endif /* LCLSN */

#endif /* LCLSNMILSN */


#ifdef LCSNUISNT

#ifndef LCSNT
#define LCSNT 1
#endif /* LCSNT */

#endif /* LCSNUISNT */


#ifdef LCSNLISDT

#ifndef LCSDT
#define LCSDT 1
#endif /* LCSDT */

#endif /* LCSNLISDT */


#if (LCLSN || LCSNT || LCSDT)

#ifndef LCSS7
#define LCSS7 1
#endif

#endif /* LCLSN || LCSNT || LCSDT */

#ifdef SN_LMINT3
#undef SN_LMINT3
#define SN_LMINT3   1
#endif /* SN_LMINT3 */

#ifdef SN_SG
#ifndef SNTIWF
#define SNTIWF 1
#endif
#endif

#endif /* SN */


#ifdef ZN       /* PSF - MTP Level 3 (FT/HA) */
/**************************************************************************
   PSF parameters
**************************************************************************/
#undef ZN
#define ZN 1

/******************* section to be changed by CUSTOMERS ******************/

/* management interface, lzn */

/* #define LCZNMILZN        loosely coupled, layer management */

/* The following flag must be turned-on if the customer chooses to implement it's
   own packing-unpacking functions for update messages */

/* #define CUSTENV */

/* #define ZN_DFTHA     distributed PSF - MTP3 environment */
/* #define ZN_USTA      enable alarms by default */
/* #define ZN_DEBUG     enable debug prints by deault (only for debugging) */

/****************************** Interfaces Version Flags ******************/

/* Peer interface */
#define ZNPV1              /* Upper interface version 1.0 */

/* Layer management interface */
#define LZNV1              /* Layer Management interface version 1.0 */

/************** section NOT to be changed by CUSTOMERS **********/


/* Note : Make sure that the flag SMSN_LMINT3 in #ifdef SM section above and
          flag LMINT3 above are also turned-on */

#ifndef SN_LMINT3
#define SN_LMINT3 1
#endif /* SN_LMINT3 */


#ifndef SNT2
#define SNT2
#endif /* SNT2 */


#ifndef SDT2
#define SDT2
#endif /* SDT2 */


#ifdef ZN_ACCEPT_TEST
#ifndef SN_OLD_BIND
#define SN_OLD_BIND
#endif /* SN_OLD_BIND */
#endif /* ZN_ACCEPT_TEST */

#ifdef LCZNMILZN

#ifndef LCLZN
#define LCLZN 1
#endif /* LCLZN */

#endif /* LCLZNMILZN */

/* dependency of ZN and SN_FTHA */
#ifndef SN_FTHA
#define SN_FTHA
#endif

/* ZN_DFTHA should be enabled if PSF-MTP3 is compiled for distributed 
 * environment */
/* #define  ZN_DFTHA     distributed PSF - MTP3 environment */

/* dependency of TDS_CORE2 and ZN_DFTHA */
#ifndef TDS_CORE2
#ifdef ZN_DFTHA
#error "Please define TDS_CORE2"
#endif /* ZN_DFTHA */
#endif /* TDS_CORE2 */
#endif /* ZN */


#ifdef SD       /* SD */
/**************************************************************************
   SS7 MTP level 2 parameters
**************************************************************************/

/*** Product Version, choose one ***/
 
/* #define SDVER1          mtp level 2, version 1.x */
#define SDVER2         /* mtp level 2, version 2.x */


/* #define SD_RUG    1       Rolling upgrade support enabled */ 
/****************************** Interfaces Version Flags ******************/

/* MTP2 upper interface */
#define SDTV1              /* Lower interface version 1.0 */

/* Layer management interface */
#define LSDV1              /* Layer Management interface version 1.0 */

/*** Interface Coupling Options ***/

/* upper interface, data link, choose none or more */

/* #define LCSDUISDT     loosely coupled, data link layer */
/* #define BCSDUISDT     backward compatibility, data link layer */

/* lower interface, mac, choose none or more */

#define LCSDLIMAC     /* loosely coupled, mac layer */
/* #define BCSDLIMAC     backward compatibility, mac layer */
 
/* management interface, lsd , choose none or more */

/* #define LCSDMILSD       loosely coupled, layer management */



/*** Interface Backward Compatibility Options ***/


/* mac interface type, choose one */
/* if applicable, must agree with scc or isac-s mac interface type or
   68302 or 68360 or MPC860 driver */

/* #define MACINT1       mac interface 1 */

#define MACINT4          /* mac interface 4 */

/* #define MACINT5       mac interface 5 */

/* flags should be turned off for backward compatibility */

#define SDT2               /* new upper interface */

#define SD_LMINT3          /* new management interface. turning off 
                              requires SMSD_LMINT3 flag also to be 
                              turned off in #ifdef SM section */



/*** Layer Management Options ***/

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCSDLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCSDLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCSDLM          /* tightly coupled, layer management */
/* #define LCSDLM           loosely coupled, layer management */
#endif
#endif

/*** Product Specific Options ***/

/* variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with mtp 3 variants */

/* #define TTC           ttc, japan, option 13 */        

/* #define NTT           ntt, japan, option 25 */        


/*** Internal defines - do not change ***/

#ifdef LCSDLIMAC

#ifdef LCMAC
#undef LCMAC
#endif

#define LCMAC 1

#endif /* LCSDLIMAC */

#ifdef LCSDUISDT

#ifdef LCSDT
#undef LCSDT
#endif

#define LCSDT 1

#endif /* LCSDUISDT */

#ifdef LCSDMILSD

#ifdef LCLSD
#undef LCLSD
#endif

#define LCLSD 1

#endif /* LCSDMILSD */


#ifdef LMINT3
#ifdef SD_LMINT3
#undef SD_LMINT3
#define SD_LMINT3 1
#endif
#endif

#endif /* SD */


#ifdef TC       /* tcp/ip */
/**************************************************************************
   tcp/ip parameters
**************************************************************************/

/* interfaces */

/* upper interface, choose none or more */

/* #define LCTUUITUT               loosely coupled, tcp/ip */

/* lower interface, choose none or more */

/* #define LCTULILLC               loosely coupled, llc */
/* #define LCTULIMAC               loosely coupled, mac */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCTCLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCTCLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCTCLM          /* tightly coupled, layer management */
/* #define LCTCLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* directed broadcast, choose none or one */

/* #define DIRECTED_BROADCAST   directed broadcast */

/* compatibility, choose none or one */

/* #define TCP_COMPAT_42        compatibility */

/* llc interface type, choose one or none */
 
/* #define LLCINT1       llc interface 1 */
 
/* mac interface type, choose one */
 
#define MACINT1      /* mac interface 1 */
/* #define MACINT2       mac interface 2 */
/* #define MACINT3       mac interface 3 */

#endif


#ifdef UD       /* udp/ip */
/**************************************************************************
   udp/ip parameters
**************************************************************************/

/* interfaces */

/* upper interface, choose none or more */

/* #define LCTUUITUT               loosely coupled, tcp/ip */

/* lower interface, choose none or more */

/* #define LCTULILLC               loosely coupled, llc */
/* #define LCTULIMAC               loosely coupled, mac */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCUDLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCUDLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCUDLM          /* tightly coupled, layer management */
/* #define LCUDLM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* llc interface type, choose one or none */
 
/* #define LLCINT1       llc interface 1 */
 
/* mac interface type, choose one */
 
#define MACINT1      /* mac interface 1 */
/* #define MACINT2       mac interface 2 */
/* #define MACINT3       mac interface 3 */

#endif


#ifdef LC       /* llc */
/**************************************************************************
   llc parameters
**************************************************************************/

/* interfaces */

/* upper interface, choose none or more */

/* #define LCLCUILLC               loosely coupled llc, upper interface (llc.x) */

/* lower interface, choose none or more */

/* #define LCLCLIMAC               loosely coupled llc, lower interface (mac.x) */

/* lower ECM interface, choose none or more */
 
#define LCLCLIECM               /* loosely coupled lower ECM interface */

/* debug lower ECM interface, choose none or more */

#define DBLCLIECM               /* debug lower ECM interface */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCLCLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCLCLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCLCLM          /* tightly coupled, layer management */
/* #define LCLCLM           loosely coupled, layer management */
#endif
#endif

/* interface flags, chosen automatically */

#ifdef LCLCLIECM

#ifndef LCECM    
#define LCECM      1    /* define LC flag for ECM interface */
#endif

#endif /* LCLCLIECM */

#if (LCECM) 

#ifndef LCATM
#define LCATM      1    /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* llc interface type, choose one */
 
/* #define LLCINT1       llc interface 1 */
/* #define LLCINT2       llc interface 2 */
 
/* mac interface type, choose one */
 
/* #define MACINT1       mac interface 1 */
/* #define MACINT2       mac interface 2 */
/* #define MACINT3       mac interface 3 */

/* type, chosen automatically */

#ifndef ATM
#define ATM 1           /* ATM stack */
#endif

#endif
 

#ifdef M1        /* dummy mac (MACINT1) */
/**************************************************************************
   mac parameters
**************************************************************************/
 
/* interfaces */
 
/* upper interface, choose none or more */
 
/* #define LCM1UIMAC               loosely coupled mac, upper interface (mac.x)
 
 layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCM1LM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCM1LM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCM1LM          /* tightly coupled, layer management */
/* #define LCM1LM           loosely coupled, layer management */
#endif
#endif
 
/* product specific options */
 
/* mac interface type, choose one */

#define MACINT1      /* mac interface 1 */

#endif


#ifdef M2        /* dummy mac (MACINT2) */
/**************************************************************************
   mac parameters
**************************************************************************/
 
/* interfaces */
 
/* upper interface, choose none or more */
 
/* #define LCM2UIMAC               loosely coupled mac, upper interface (mac.x)
 
 layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCM2LM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCM2LM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCM2LM          /* tightly coupled, layer management */
/* #define LCM2LM           loosely coupled, layer management */
#endif
#endif
 
/* product specific options */
 
/* mac interface type, choose one */

#define MACINT2      /* mac interface 2 */

#endif


#ifdef M3        /* dummy mac (MACINT3) */
/**************************************************************************
   mac parameters
**************************************************************************/
 
/* interfaces */
 
/* upper interface, choose none or more */
 
/* #define LCM3UIMAC               loosely coupled mac, upper interface (mac.x) */
 
/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCM3LM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCM3LM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCM3LM          /* tightly coupled, layer management */
/* #define LCM3LM           loosely coupled, layer management */
#endif
#endif
 
/* product specific options */
 
/* mac interface type, choose one */

#define MACINT3      /* mac interface 3 */

#endif


#ifdef AR            /* Authentication and Routing Module */
/**************************************************************************
   ARI If Parameters
**************************************************************************/
 
/* interfaces */

/* layer management options, choose none */

#ifndef LMINT2
#define LMINT2          /* layer management interface 2 */
#endif

/* upper interface, choose none or more */
 
/* #define LCARUIARI 1      loosely coupled AR, upper interface (ari.x) */
 
/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

/* interface flags, chosen automatically */

#ifdef LCARUIARI

#ifndef LCARI
#define LCARI 1     /* define LC flag for ARI interface */
#endif

#endif /* LCARUIARI */

/* product specific options */

/* debug upper ari interface, choose one or none */
 
/* #define DBARUIARI 1        debug dummy upper ari interface */

/* type, chosen automatically */

#endif /* AR */


#ifdef M6        /* AAL5 cpcs */
/**************************************************************************
   AAL5 CPCS parameters
**************************************************************************/
 
/* interfaces */

/* layer management options, choose none */

#ifndef LMINT2
#define LMINT2          /* layer management interface 2 */
#endif

/* upper interface, choose none or more */
 
/* #define LCM6UIAAL 1      loosely coupled mac, upper interface (mac.x) */
 
/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCM6LM 1        /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCM6LM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

/* #define TCM6LM           tightly coupled, layer management */
/* #define LCM6LM 1         loosely coupled, layer management */
#endif
#endif
 
/* interface flags, chosen automatically */

#ifdef LCM6UIAAL

#ifndef LCAAL
#define LCAAL 1     /* define LC flag for AAL interface */
#endif

#endif /* LCM6UIAAL */

#if (LCAAL || LCM6LM)

#ifndef LCATM
#define LCATM 1         /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* debug upper aal interface, choose one or none */
 
/* #define DBM6UIAAL 1        debug dummy upper aal interface */

/* type, chosen automatically */

#ifndef ATM
#define ATM 1              /* ATM stack */
#endif

#endif


#ifdef P1        /* PXY */
/**************************************************************************
   PXY parameters
**************************************************************************/
/* upper interface, choose none or more */
 
/* #define LCP1UIPXY 1       loosely coupled PXY lower interface (pxy.x) */
 
/* layer management options */

/* interface flags, chosen automatically */

#ifdef LCP1UIPXY

#ifndef LCPXY
#define LCPXY 1     /* define LC flag for PXY interface */
#endif /* LCPXY */

#endif /* LCP1UIPXY */

/* product specific options */

/* debug upper pxy interface, choose one or none */
 
/* #define DBP1UIPXY 1        debug dummy upper pxy interface */

/* type, chosen automatically */
#endif /* P1 */


#ifdef AC        /* AAL5 cpcs */
/**************************************************************************
   AAL5 CPCS parameters - ATM convergence layer
**************************************************************************/
 
/* interfaces */

/* layer management options, choose none */

#ifndef LMINT2
#define LMINT2          /* layer management interface 2 */
#endif

/* upper interface, choose none or more */
 
/* #define LCACUIAAL 1      loosely coupled mac, upper interface (mac.x) */
/* #define LCACMILAC 1      loosely coupled LAC, management interface */ 
/* #define TDS_ATM_BS 1     use berkeley sockets */

/* AAL SAP mode options: define at least one*/
#define AC_ATM_LPBK     0    /* Loopback */
/*#define AC_ATM_HARDWARE 1     Actual Hardware */
 
/* Physical SAP mode options: define at least one if AALSAP mode is Hardware*/
/*#define AC_ATM_SUN   1       SUNP ADAPTER */
/*#define AC_ATM_FORE  2       Fore Adapter */
/*#define AC_ATM_SOCK    3     Sockets */
 
#define AC_ATM_NMB_PMODES  4    /* Number of Physical Modes */

 
/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCACLM 1        /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCACLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

/* #define TCACLM           tightly coupled, layer management */
/* #define LCACLM 1         loosely coupled, layer management */
#endif
#endif
 
/* interface flags, chosen automatically */

#ifdef LCACUIAAL

#ifndef LCAAL
#define LCAAL 1     /* define LC flag for AAL interface */
#endif

#endif /* LCACUIAAL */

#if (LCAAL || LCACLM)

#ifndef LCATM
#define LCATM 1         /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* debug upper aal interface, choose one or none */
 
/* #define DBACUIAAL 1        debug dummy upper aal interface */

/* type, chosen automatically */

#ifndef ATM
#define ATM 1              /* ATM stack */
#endif

#endif   /* AC */


#ifdef AF       /* Atm-Fr Interworking Layer */

/**************************************************************************
   FR-ATM parameters
**************************************************************************/

/* interfaces */

#ifndef LMINT2     
/* 
 * layer management interface 2 
 */
#define LMINT2     
#endif  /* LMINT2 */

#ifndef MACINT1
#define MACINT1 1
#endif  /* MACINT */

#ifndef DATINT1
#define DATINT1 1
#endif  /* DATINT1 */

#ifndef MACVER2
#define MACVER2 1
#endif  /* MACVER2 */

#ifndef DATVER2
#define DATVER2 1
#endif  /* DATVER2 */

/* upper interface(for AF_NI only), MAC, data link, 
 * enable for loosely coupled operation
 */
/* #define LCAFUIMAC 1     loosely coupled, data link layer */

/* lower interface, AAL(for both AF_NI and AF_SI)
 * enable for loosely coupled operation
 */

/* #define LCAFLIAAL 1     loosely coupled, aal layer */

/* lower interface(for AF_SI only), FRD, 
 * enable for loosely coupled operation
 */

/* #define LCAFLIFRD 1     loosely coupled, frd layer */

#ifdef LCAFLIFRD
#ifndef LCFR
#define LCFR              /* enable LCFR - loosely coupled flag */
#endif
#endif /* #ifdef LCAFUIFRD */

/* management interface, LAF, enable for loosely
 * coupled interface from Layer Manager to AF module
 */
/* #define LCAFMILAF 1     loosely coupled, layer management */

/* interface flags, chosen automatically */

#ifdef LCAFLIAAL

#ifndef LCAAL
#define LCAAL 1            /* define LC flag for AAL interface */
#endif

#endif /* LCAFLIAAL */

#if (LCAAL || LCSMAFMILAF || LCAFMILAF)

#ifndef LCATM
#define LCATM 1            /* define LC flag for ATM stack */
#endif

#endif

/* Chose interworking type - network interworking ,
 * service interworking or both
 */
#define AF_NI 1             /* choose network interworking */
#define AF_SI 1             /* choose service interworking */

/*
 * option to choose between hashing or base indexed array table
 * for DLCI control blocks. For hashing to be enabled uncomment
 * the section below.
 */
/* #define HASH_ENABLE  1 Enable DLCI Hashing */

#endif /* AF */


#ifdef PL        /* PMC - Sierra LASAR driver */
/**************************************************************************
   PMC - Sierra LASAR driver parameters
**************************************************************************/
 
/* interfaces */

/* layer management options, choose none */

#ifndef LMINT2
#define LMINT2           /* layer management interface 2 */
#endif

/* upper interface, choose one or none */
 
/* #define LCPLUIAAL           loosely coupled aal, upper interface (aal.x) */

/* debug upper interface, choose one or none */

/* #define DBPLUIAAL           debug output enabled for upper interface */


/* management interface, lpl, choose none or more */

/* #define LCPLMILPL           loosely coupled, layer management */

/* debug mngmt interface, choose one or none */

/* #define DBPLMILPL           debug output enabled for mngmt interface */

/* interface flags, chosen automatically */

#ifdef LCPLUIAAL

#ifndef LCAAL
#define LCAAL 1            /* define LC flag for AAL interface */
#endif

#endif /* LCPLUIAAL */

#ifdef LCPLMILPL

#ifndef LCLPL
#define LCLPL 1            /* define LC flag for LPL interface */
#endif

#endif /* LCPLMILPL */

#if (LCAAL || LCLPL)

#ifndef LCATM
#define LCATM 1            /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* type, chosen automatically */

#ifndef ATM
#define ATM  1             /* ATM stack */
#endif

/* UNI 4.0 option */

/* #define UNI40                 ATM Forum UNI ver 4.0 enabled */
 
#ifndef UNI40
#define DEF_UNI40      0
#else
#define DEF_UNI40      1
#endif

/* deferred processing, chosen automatically */

#ifdef WINNT_KERN
#define DPR_ENB  1              /* enable deferred processing */
#endif

#define LSR_PCIH_MASTER         /* PCI Host is the master */
/* #define LSR_MP_MASTER            Local Microprocessor is the master */
#define ENABLE_RX_OAM_CELLS     /* enable reception of OAM cells*/
#define LSR_REVD_BUG2_4         /* related to diagnostic loop back */
#define LSR_REVD_BUG2_10        /* related to SOE_E bit in REG_PCID_CNTRL */
#define LSR_REVD_BUG2_11        /* related to dataLen in transmit direction */
#define LSR_REVD_BUG2_12        /* related to latency timer in PCID config space */
#define LSR_REVD_BUG2_13        /* related to parity error */

/* Disconnect Check flag */
/* #define PL_DISC_CHK             check for pending transmission before  */

#endif /* PL */


#ifdef FA        /* Fujitsu ALC driver */
/**************************************************************************
   Fujitsu ALC driver parameters
**************************************************************************/
 
/* interfaces */

/* layer management options, choose none */

#ifndef LMINT2
#define LMINT2          /* layer management interface 2 */
#endif

/* upper interface, choose none or more */
 
/* #define LCFAUIAAL 1       loosely coupled aal, upper interface (aal.x) */

/* management interface, lfa, choose none or more */

/* #define LCFAMILFA           loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCFALM 1        /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCFALM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCFALM           tightly coupled, layer management 
/* #define LCFALM 1         loosely coupled, layer management */
#endif
#endif
 
/* interface flags, chosen automatically */

#ifdef LCFAUIAAL

#ifndef LCAAL
#define LCAAL 1            /* define LC flag for AAL interface */
#endif

#endif /* LCFAUIAAL */

#if (LCAAL || LCFALM)

#ifndef LCATM
#define LCATM 1            /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* debug upper aal interface, choose one or none */
 
/* #define DBFAUIAAL 1          debug dummy upper aal interface */

/*#define DBFAMILFA 1          debug stack manager interface */

/* type, chosen automatically */

#ifndef ATM
#define ATM 1              /* ATM stack */
#endif

/* UNI 4.0 option */

/* #define UNI40                 ATM Forum UNI ver 4.0 enabled */

#ifndef UNI40
#define DEF_UNI40      0
#else
#define DEF_UNI40      1
#endif

/* #define FAPOLLINTR       ALC Polled Interrupts */
/* #define FAALCEVAL        Fujitsu Evaluation board */ 
/* #define FARXATCPRES      Receive ATC is present */
/* #define FATXATCPRES      Transmit ATC is present */
/* #define FANTCPRES        NTC is present */

#ifdef FAALCEVAL
#ifndef ALC_EVAL
#define ALC_EVAL
#endif /* ALC_EVAL */
#endif /* FAALCEVAL */

#ifdef FAPOLLINTR
#ifndef ALC_POLLED_INTR
#define ALC_POLLED_INTR
#endif /* ALC_POLLED_INTR */
#endif /* FAPOLLINTR */

#endif /* FA */


#ifdef OD        /* ODI mac (assuming MACINT3) */
/**************************************************************************
   mac parameters
**************************************************************************/
 
/* interfaces */
 
/* upper interface, choose none or more */
 
/* #define LCODUIMAC               loosely coupled mac, upper interface (mac.x) */
 
/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCODLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCODLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCODLM          /* tightly coupled, layer management */
/* #define LCODLM           loosely coupled, layer management */
#endif
#endif
 
/* product specific options */
 
#endif


#ifdef SI        /* isup */
/**************************************************************************
   isup parameters
**************************************************************************/
#undef SI
#define SI 1

/* product version, choose one */
 
/* #define SIVER1          isup, version 1.x */
#define SIVER2         /* isup, version 2.x */


/* interfaces */

/* upper interface, choose none or more */

/* #define LCSIUISIT               loosely coupled isup, upper interface (sit.x) */

/* lower interface, choose none or more */

/* #define LCSILISNT               loosely coupled, mtp - level 3 */
/* #define LCSILISPT               loosely coupled, sccp */

/* management interface, lsi , choose none or more */

/* #define LCSIMILSI       loosely coupled, layer management */

/* layer management options */
#define SIT2               /* new upper interface */

#define SNT2               /* new lower interface(MTP-3) */

#define SPT2               /* new lower interface(SCCP) */

#define SI_LMINT3          /* new management interface. turning off requires
                              SMSN_LMINT3 flag also to be turned off in #ifdef
                              SM section */
/* flags should be turned on for backward compatibility */
/* #define SI_218_COMP        Backward compatibility flag for 219 release. If 
                              enabled LSI and SIT interface conforms to 2.18.
                              This flag will be phased out in the next release
                              of ISUP that is the behaviour if flag is enabled 
                              will be removed in the next release */
/* #define SIT_OLD_DEFINES    Some defines in SIT interface are prefixed with
                              SIT_ to avoid conflicts with other layers. This
                              option enables the old defines (without SIT_)
                              This option will be phased out in the next 
                              release of ISUP */

#define SI_INFINITETRY 1   /* maintenance timers should run forever */
                              
/* #define SI_RUG       Rolling upgrade support enabled */
/****************************** Interfaces Version Flags ******************/

/* Upper interface */
/* #define SITV1           Upper interface version 1.0 */
#define SITV2              /* Upper interface version 2.0 */

/* Lower interface */
#define SNTV1              /* Lower interface version 1.0 */

/* Layer management interface */
#define LSIV1              /* Layer Management interface version 1.0 */


/* product specific options */

/* variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with q.930, mtp 3, sccp variants */

/* #define BELL          bellcore, option 11 */
/* #define ANS88         ansi, option 12 */
/* #define ANS92         ansi, option 12 */
/* #define TTC           ttc, japan, option 13 */
/* #define SINGTEL       singapore telecom, option 19 */
/* #define Q767          q.767, option 17 */
/* #define Q767IT        q.767 italy, option 20 */
/* #define ETSI_SS7      ETSI, option 22 */
/* #define GT_FTZ        GT_FTZ, option 23 */
/* #define RUSSIA_SS7    RUSSIA option 24 */
/* #define NTT           NTT option 25 */
/* #define ANS95         ANSI 95 option 18 */
/* #define ITU97         ITU 97 option 27 */
/* #define ETSIV3        ETSI version 3 option 28 */

/* ISUP layer specific compile options */
/* #define SI_NEW_COT_PROC 1 New continuity behaviour                      */
/* #define SI_USTA      1    Alarms enabled                                */
/* #define SI_ACNT      1    Enables accounting feature in ISUP            */
/* #define SI_INDBLK    1    Individual blk/unblk tmrs on group msg        */
/* #define SI_INDBLO_ON_GRS 1 Indiv. blo msg on getting grs for lclyblk cir*/
/* #define SI_NEW_PARAM_COMP_HNDL 1 using tknstr for extended instruction
                                    and support for 5 parameters in IE     */
/* #define SI_NOENUMCHK 1     Enables the validation against enums in DB   */
/* #define SI_ONEIND_CKTGRP 1 For ANS92/BELL one indication given for GRS
                              and CGB 's second message                    */
/* #define SI_RESET_RMTUNEQSTATE 1  Resets the rmt uneq.state on rcving
                              msg from peer                                */
/* #define SI_SLSCIC    1     Uses last few bits of CIC as linksel         */
/* #define SLS_8BIT     1     8 bit SLS field is used                      */
/* #define SI_FTHA      1     Enables SHT interface for ISUP               */
/* #define SI_CMHASH_CHK 1    Check next and prev hash list pointers       */
/* #define SI_BELL246_PARMS 1 Stops support for certain parameter in db    */

/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif

#ifdef Q767IT
#define Q767            /* q.767, option 17 */
#endif

#define SI_ANSILNP  1            /* Support of ANSI local number portability */

#ifdef BELL
#ifndef SI_ANSILNP
#define SI_ANSILNP              /* Support of ANSI local number portability */
#endif
#endif

/* #define SI_SPT        include SCCP support */

#ifdef LCSIMILSI

#ifndef LCLSI
#define LCLSI 1
#endif /* LCLSI */

#endif /* LCLSIMILSI */


#ifdef LCSIUISIT

#ifndef LCSIT
#define LCSIT 1
#endif /* LCSIT */

#endif /* LCSIUISIT */
/*

#define  SIT_PARAMETER 1
*/

#ifdef LCSILISNT

#ifndef LCSNT
#define LCSNT 1
#endif /* LCSNT */

#endif /* LCSILISNT */

#ifdef LCSILISPT

#ifndef LCSPT
#define LCSPT 1
#endif /* LCSPT */

#endif /* LCSILISPT */

#if (LCLSI || LCSIT || LCSNT || LCSPT)

#ifndef LCSS7
#define LCSS7 1
#endif

#endif /* LCLSN || LCSNT || LCSDT || LCSPT */

#ifdef SI_LMINT3
#undef SI_LMINT3
#define SI_LMINT3   1
#endif /* SI_LMINT3 */

#endif /* SI */


#ifdef ZI       /* PSF - ISUP (FT/HA) */
/**************************************************************************
   PSF parameters
**************************************************************************/
#undef ZI
#define ZI 1

/******************* section to be changed by CUSTOMERS ******************/

/* management interface, lzi */

/* #define LCZIMILZI        loosely coupled, layer management */
#ifdef TDS_CORE2
#define ZI_TST_NEW_MSGHDR 1  /* new msg hdr for psf acceptance tests */
#endif


/* The following flag must be turned-on if the customer chooses to implement it's
   own packing-unpacking functions for update messages */

/* #define CUSTENV */


/************** section NOT to be changed by CUSTOMERS **********/


/* Note : Make sure that the flag SMSI_LMINT3 in #ifdef SM section above and
          flag LMINT3 above are also turned-on */

#ifndef SI_LMINT3
#define SI_LMINT3 1
#endif /* SI_LMINT3 */

#ifndef SIT2
#define SIT2
#endif /* SIT2 */

#ifndef SNT2
#define SNT2
#endif /* SNT2 */


#ifndef SPT2
#define SPT2
#endif /* SPT2 */

#ifdef SI_OLD_BIND      /* PSF-ISUP testcases require SI_OLD_BIND disabled */
#undef SI_OLD_BIND
#endif

#endif /* ZI */


#ifdef WI       /* ISUP wrapper */
/**************************************************************************
   ISUP Wrapper parameters
**************************************************************************/
 
/* interfaces */
   
/* management interface, lwp , choose none or more */

/* #define LCWIMILWI       loosely coupled, layer management */

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */
 
#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */
 
#define LCWILM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */
 
#define TCWILM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */
 
#define TCWILM          /* tightly coupled, layer management */
/* #define LCWILM           loosely coupled, layer management */
#endif
#endif
 
/* product specific options */

/* variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with q.930, mtp 3, sccp variants */
 
/* #define BELL          bellcore, option 11 */
/* #define ANS88         ansi, option 12 */
/* #define ANS92         ansi, option 12 */
/* #define TTC           ttc, japan, option 13 */
/* #define SINGTEL       singapore telecom, option 19 */
/* #define Q767          q.767, option 17 */
/* #define Q767IT        q.767 italy, option 20 */
 
/* type, chosen automatically */
 
#ifndef SS7
#define SS7             /* for message functions */
#endif

#ifdef Q767IT
#define Q767            /* q.767, option 17 */
#endif
 
#endif /* WI */



#ifdef WU       /* TUP wrapper */
/**************************************************************************
   TUP Wrapper parameters
**************************************************************************/
 
/* interfaces */
 
/* management interface, lwu , choose none or more */
 
#define LCWUMILWU      /* loosely coupled, layer management */
 
/* debug mngmt interface, choose one or none, default is debug output disabled */
 
#define DBWUMILWU    /* debug output enabled for mngmt interface */
 
/* layer management options */
 
/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */
 
#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */
 
#define LCWULM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */
 
#define TCWULM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */
#define TCWULM          /* tightly coupled, layer management */
/* #define LCWULM           loosely coupled, layer management */
#endif
#endif
 
/* product specific options */
 
/* variants, choose none or more */
/* must agree with options delivered */
/* product specific options */
 
/* #define CHINA         china */

/* type, chosen automatically */
 
#ifndef SS7
#define SS7             /* for message functions */
#endif
 
#endif
 


#ifdef BI        /* b-isup */
/**************************************************************************
   b-isup parameters
**************************************************************************/

/* product version, choose one */
 
/* interfaces */

/* upper interface, choose none or more */

/* #define LCBIUIBIT               loosely coupled b-isup, upper interface (bit.x) */

/* lower interface, choose none or more */

/* #define LCBILISNT               loosely coupled, mtp - level 3 */

/* management interface, lsi , choose none or more */

/* #define LCBIMILBI       loosely coupled, layer management */

#ifdef LCBIUIBIT      /* loosely coupled, upper interface */
#ifndef LCATM
#define LCATM     
#endif
#define DEF_LCATM     1
#endif

/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCBILM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCBILM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCBILM          /* tightly coupled, layer management */
/* #define LCBILM           loosely coupled, layer management */
#endif
#endif

/* product specific options */

/* variants, choose none or more */
/* must agree with options delivered */

/* #define ATF2           ATM-Forum, option 13 */

/* snt interface type, choose one */
/* if applicable, must agree with MTP Level 3 snt interface type */


/* type, chosen automatically */


#endif


#ifdef BW        /* b-isup protocol specific interface function */
/**************************************************************************
   b-isup protocol specific interface function parameters
**************************************************************************/
 
/* interfaces */
/* #define ICC_1_5_REORG   1       ICC 1.5 file reorganization */

#ifdef ICC_1_5_REORG
#ifndef ICC_1_4_REORG
#define ICC_1_4_REORG   1       /* ICC 1.4 file reorganization */
#endif
#endif

/* #define CCT_VER_2       1       CCT interface version 2 */
/* #define RMT_VER_2       1       RMT interface version 2 */
/* #define CC_RMTFCDESC_VER_2  1   Version 2 RM Traffic Descriptor */
/* #define ICC_AUDIT  1            ICC auditing enabled */
 
/* upper interface, choose none or more */
/*  #define LCBWUICCT   loosely coupled upper interface (call control) */
 
/* lower interface, choose none or more */
/* Always tightly coupled to b-isup */
/* #define LCBWLIRMT       resource manager */
 
/* management interface, lbw , choose none or more */
/* #define LCBWMILBW       loosely coupled, layer management */

#ifdef LCBWUICCT
#define LCCCT 1
#endif

#if (defined(LCBWUICCT) || defined(LCBWLIRMT))
#ifndef LCCMCC
#define LCCMCC        1
#endif
#ifndef LCATM
#define LCATM         1
#endif
#endif

#endif  /* BW */
 

#ifdef IW        /* isup protocol specific interface function */
/**************************************************************************
   isup protocol specific interface function parameters
**************************************************************************/
 
/* interfaces */
/* #define ICC_1_5_REORG   1       ICC 1.5 file reorganization */

#ifdef ICC_1_5_REORG
#ifndef ICC_1_4_REORG
#define ICC_1_4_REORG   1       /* ICC 1.4 file reorganization */
#endif
#endif

#define CCT_VER_2       1       /* CCT interface version 2 */
#define RMT_VER_2       1       /* RMT interface version 2 */
/* #define CC_RMTFCDESC_VER_2  1   Version 2 RM Traffic Descriptor */
#define ICC_AUDIT  1            /* ICC auditing enabled */
#define RMT_CICGRP_STATUS 1     /* Status enabled in circuit group procedures
                                 * on RMT interface */

#if (CCT_VER_2 || RMT_VER_2 || IW_COT_NEW)

#ifndef IW_COT_NEW
#define IW_COT_NEW 1
#endif /* IW_COT_NEW */

#ifndef RMT_VER_2
#define RMT_VER_2       1 /* RMT interface version 2 */
#endif /* RMT_VER_2 */

#ifndef CCT_VER_2
#define CCT_VER_2       1 /* CCT interface version 2 */
#endif /* CCT_VER_2 */

#endif /* (CCT_VER_2 || RMT_VER_2 || IW_COT_NEW) */
 
/* upper interface, choose none or more */
/*   #define LCIWUICCT   loosely coupled upper interface (call control) */
 
#ifdef LCIWUICCT
#define LCSIT 1
#define LCCCT 1
#endif
/* lower interface, choose none or more */
/* Always tightly coupled to isup */
/* #define LCIWLIRMT      resource manager */
 
/* management interface, liw , choose none or more */
/* #define LCIWMILIW      loosely coupled, layer management */
 
#ifdef LCIWUICCT           /* If CCT is Loosely coupled then define LCSIT to
                           enable the packing/unpacking utility functions
                           in interface files of SIT */
#ifndef LCSIT
#define LCSIT 1 
#endif
#endif

#if (defined(LCIWUICCT) || defined(LCIWLIRMT))
#ifndef LCCMCC
#define LCCMCC        1
#endif
#ifndef LCATM
#define LCATM         1
#endif
#endif

#endif  /* IW */


#ifdef QW        /* isdn protocol specific interface function */
/**************************************************************************
   isdn protocol specific interface function parameters
**************************************************************************/
#define ISDN_3_8_PLUS           /* Code version 3.10 & above */
#define ISDN_3_10_PLUS          /* Q.930/Q.931 code version 3.11 and above */
#define CDPTYNMB_32DIGIT        /* Called Part Number 32 digit */
/* #define QW_COT_NEW              New prototype definition of RMT */
 
/* interfaces */
/* #define ICC_1_5_REORG   1       ICC 1.5 file reorganization */

#ifdef ICC_1_5_REORG
#ifndef ICC_1_4_REORG
#define ICC_1_4_REORG   1       /* ICC 1.4 file reorganization */
#endif
#endif

/* #define CCT_VER_2       1       CCT interface version 2 */
/* #define RMT_VER_2       1       RMT interface version 2 */
/* #define CC_RMTFCDESC_VER_2  1   Version 2 RM Traffic Descriptor */
/* #define ICC_AUDIT  1            ICC auditing enabled */
 
/* upper interface, choose none or more */
/*   #define LCQWUICCT   loosely coupled upper interface (call control) */
 
#ifdef LCQWUICCT
#define LCINUIINT
#define LCUICMINT
#define LCCCT 1
#endif

/* lower interface, choose none or more */
/* Always tightly coupled to isdn */
/* #define LCQWLIRMT      resource manager */
 
/* management interface, liw , choose none or more */
/* #define LCQWMILQW     loosely coupled, layer management */
 
#if (defined(LCQWUICCT) || defined(LCQWLIRMT))
#ifndef LCCMCC
#define LCCMCC        1
#endif
#ifndef LCATM
#define LCATM         1
#endif
#endif
 
#endif  /* QW */


#ifdef AW        /* Q.93B protocol specific interface function */
/**************************************************************************
   Q.93B protocol specific interface function parameters
**************************************************************************/
 
/* interfaces */
/* #define ICC_1_5_REORG   1       ICC 1.5 file reorganization */

#ifdef ICC_1_5_REORG
#ifndef ICC_1_4_REORG
#define ICC_1_4_REORG   1       /* ICC 1.4 file reorganization */
#endif
#endif

/* #define CCT_VER_2       1       CCT interface version 2 */
/* #define RMT_VER_2       1       RMT interface version 2 */
/* #define CC_RMTFCDESC_VER_2  1   Version 2 RM Traffic Descriptor */
/* #define ICC_AUDIT  1            ICC auditing enabled */
 
/* upper interface, choose none or more */
/* #define LCAWUICCT   loosely coupled upper interface (call control) */
 
/* lower interface, choose none or more */
/* Always tightly coupled to isdn */
/* #define LCAWLIRMT      resource manager */
 
/* management interface, liw , choose none or more */
/* #define LCAWMILAW     loosely coupled, layer management */
 
#if (defined(LCAWUICCT) || defined(LCAWLIRMT) || defined(LCAWMILAW))
#ifndef LCCMCC
#define LCCMCC        1
#endif
#ifndef LCCCT
#define LCCCT          1
#endif
#ifndef LCATM
#define LCATM         1
#endif
#ifndef LCAMT
#define LCAMT         1
#endif
#endif
#endif /* AW */


#ifdef RM            /* resource management */
/**************************************************************************
   resource management parameters
**************************************************************************/
 
/* interfaces */
/* #define ICC_1_5_REORG   1  ICC 1.5 file reorganization */

#ifdef ICC_1_5_REORG
#ifndef ICC_1_4_REORG
#define ICC_1_4_REORG   1       /* ICC 1.4 file reorganization */
#endif
#endif

/* #define RMT_VER_2  1            RMT version 2 */
/* #define ICC_AUDIT  1            ICC auditing enabled */
/* #define CC_RMTFCDESC_VER_2  1   Version 2 RM Traffic Descriptor */
/* #define ICC_IN_AUD_ENA   1      Enable auditing for ISDN resources */
/* #define ICC_ATM_AUD_ENA  1      Enable auditing for ATM resources */
 
/* upper interface, choose none or more */
/* #define LCRMUIRMT   loosely coupled, call control */
 
/* management interface */
/* #define LCRMMILRM   loosely coupled, layer management */
 
#ifdef LCRMUIRMT
#ifndef LCRMT
#define LCRMT 1
#endif
#endif

#ifdef LCRMUIRMT
#ifndef LCCMCC
#define LCCMCC        1    
#endif
#ifndef LCATM
#define LCATM         1
#endif
#endif

/* #define PNNI_ROUTING_ENABLED    1 Enable PNNI routing in RM */

#ifdef LCRMMILRM
#ifdef PNNI_ROUTING_ENABLED
#ifndef LCLPN
#define LCLPN 1
#endif
#endif /* PNNI_ROUTING_ENABLED */
#endif

#endif /* RM */


#ifdef RT           /* router */
/**************************************************************************
   router parameters
**************************************************************************/
 
/* interfaces */
/* #define ICC_1_5_REORG   1  ICC 1.5 file reorganization */

#ifdef ICC_1_5_REORG
#ifndef ICC_1_4_REORG
#define ICC_1_4_REORG   1       /* ICC 1.4 file reorganization */
#endif
#endif

/* #define RTT_VER_2  1            RTT interface version 2 */
/* #define ICC_AUDIT  1            ICC auditing enabled */
/* #define CC_RMTFCDESC_VER_2  1   Version 2 RM Traffic Descriptor */
 
/* upper interface, choose none or more */
/* #define LCRTUIRTT   loosely coupled, call control */
 
/* management interface */
/*   #define LCRTMILRT   loosely coupled, layer management */
 
#ifdef LCRTUIRTT
#ifndef LCRTT
#define LCRTT  1
#endif
#endif

#if (defined (LCRTUIRTT) || defined(LCRTMILRT))
#ifndef LCCMCC
#define LCCMCC        1
#endif
#ifndef LCATM
#define LCATM         1
#endif
#endif

#endif /* RT */


#ifdef SF           /* switching fabric manager */
/**************************************************************************
   switching fabric manager parameters
**************************************************************************/
 
/* interfaces */
/* #define ICC_1_5_REORG   1  ICC 1.5 file reorganization */

#ifdef ICC_1_5_REORG
#ifndef ICC_1_4_REORG
#define ICC_1_4_REORG   1       /* ICC 1.4 file reorganization */
#endif
#endif

/* #define SFT_VER_2  1            SFT interface version 2 */
/* #define ICC_AUDIT  1            ICC auditing enabled */
/* #define CC_RMTFCDESC_VER_2  1   Version 2 RM Traffic Descriptor */
/* #define CC_SWTCHIDX_VER_2  1    Version 2 Switch Index */
 
/* upper interface, choose none or more */
/* #define LCSFUISFT   loosely coupled, call control */
 
/* management interface */
/*   #define LCSFMILSF   loosely coupled, layer management */

#ifdef LCSFUISFT
#ifndef LCSFT
#define LCSFT 1
#endif
#endif

#ifdef LCSFUISFT
#ifndef LCCMCC
#define LCCMCC        1
#endif
#ifndef LCATM
#define LCATM         1
#endif
#endif
 
#endif  /* SF */
 

#ifdef XM        /* Connection Manager interface function */
/**************************************************************************
   Connection interface function parameters
**************************************************************************/

/* interfaces */
/* #define ICC_1_5_REORG   1  ICC 1.5 file reorganization */

#ifdef ICC_1_5_REORG
#ifndef ICC_1_4_REORG
#define ICC_1_4_REORG   1       /* ICC 1.4 file reorganization */
#endif
#endif

/* #define RMT_VER_2 1       RMT interface version 2 */
/* #define CCT_VER_2 1       RMT interface version 2 */
/* #define CC_RMTFCDESC_VER_2  1   Version 2 RM Traffic Descriptor */

/* upper interface, choose none or more */
/* #define LCXMUICCT     loosely coupled upper interface (call control) */
/* #define LCXMUIRMT     loosely coupled, call control */

/* management interface, lxm , choose none or more */
/*   #define LCXMMILXM   loosely coupled, layer management */
/* #define XM_FEATTRP_SI  1 */
/* #define XM_FEATTRP_IN  1 */
/* #define XM_PH1_TK  1     Phase 1 Trunking */
/* Product variants specific options */

#if ((defined LCXMUICCT) || (defined LCXMUIRMT))
#ifndef LCCMCC
#define LCCMCC        1
#endif
#endif

#ifdef LCXMUICCT
#ifndef LCCCT
#define LCCCT         1
#endif
#endif

#ifdef LCXMUIRMT
#ifndef LCRMT
#define LCRMT         1
#endif
#endif

#ifdef XM_FEATTRP_SI
/**************************************************************************
   isup feature transparancy parameters required for XM
**************************************************************************/

/* interfaces */
#if (defined (LCXMUICCT) || defined (LCXMMILXM))
#define LCSIT 1              /* if loosely coupled wrapper then define */
#endif

/* variants, choose none or more */
/* must agree with options delivered */

/* ISUP protocol variants */

/* #define BELL          bellcore, option 11 */
/* #define ANS88         ansi, option 12 */
/* #define ANS92         ansi, option 12 */
/* #define TTC           ttc, japan, option 13 */
/* #define SINGTEL       singapore telecom, option 19 */
/* #define Q767          q.767, option 17 */
/* #define Q767IT        q.767 italy, option 20 */
/* #define ETSI_SS7      ETSI, option 22 */
/* #define GT_FTZ        GT_FTZ, option 23 */
/* #define RUSSIA_SS7    RUSSIA option 24 */

/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif

#ifdef Q767IT
#define Q767            /* q.767, option 17 */
#endif

#ifdef BELL
#define SI_ANSILNP              /* Support of ANSI local number portability */
#endif

#endif /* XM_FEATTRP_SI */

#ifdef XM_FEATTRP_IN
/**************************************************************************
   isdn feature transparancy parameters required for XM
**************************************************************************/

#ifdef LCXMUICCT
#define LCINUIINT               /* if loosely coupled wrapper then define */
                                /* loosely coupled ISDN */
#define LCUICMINT               /* loosely coupled common functions. */
#endif

/* variants, choose none or more */
/* must agree with options delivered */
/* ISDN protocol variants */

/* Option for ITUT-88 standard - used in bearcapability encoding/decoding */

/* #define ITUT88      ITU-T 88 - for Bearer Capability */

/* switch variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with x.31, isup switch variants */

/* #define ATT           att 4ess and 5ess, option 11 */
/* #define NT            northern telecomm dms-100, option 12 */
/* #define VN            vn 2 and vn 3, france, option 13 */
/* #define ETSI         etsi, europe, option 14 */
/* #define AUS           AUS, australian, option 15 */
/* #define NI1           national isdn 1, north america, option 16 */
/* #define NTT           ins net, japan, option 17 */
/* #define TR6           1 - TR6, german, option 18 */
/* #define ATT5E         att 5ess, option 19 */
/* #define ATT4E         att 4ess, option 20 */
/* #define VN2           vn 2, france, option 21 */
/* #define VN3           vn 3, france, option 22 */
/* #define NTDMS250      northern telecom dms-250, option 23 */
/* #define BC303         bellcore tr-303, tmc and csc, option 24 */
/* #define BC303TMC      bellcore tr-303, tmc , option 25 */
/* #define BC303CSC      bellcore tr-303, csc, option 26 */
/* #define Q932          q.932 option, option 27 */
/* #define NI2          national isdn 2, north america, option 28 */
/* #define QSIG         etsi qsig, option 29 */
/* #define NTNI          nt ni, option 31 */
/* #define NTMCI         nt mci, option 32 */

/* variant, choose all */

#ifdef ATT              /* att */
#define ATT5E           /* att 5ess, option 19 */
#define ATT4E           /* att 4ess, option 20 */
#endif

#ifdef VN3              /* vn 3 */
#define VN              /* vn 2 and vn 3, france, option 13 */
#endif

#ifdef VN               /* vn */
#define VN2             /* vn 2, france, option 21 */
#define VN3             /* vn 3, france, option 22 */
#endif

#ifdef BC303            /* bellcore tr-303 */
#define BC303TMC        /* bellcore tr-303, tmc , option 25 */
#define BC303CSC        /* bellcore tr-303, csc, option 26 */
#endif

/* features, choose none or more */

/* #define ISDN_SEGMENT  1  message segmentation and reassembly option */
/* #define ISDN_BRI      1  basic rate interface option */
/* #define ISDN_PRI      1  primary rate interface option */
/* #define ISDN_ROUTE    1  routing procedures provided */
/* #define ISDN_OVERLAP  1  overlap sending/receiving provided */
/* #define ISDN_UTU      1  user to user procedures provided */
/* #define ISDN_FACILITY 1  facility procedures provided */
/* #define ISDN_SRV      1  service procedures provided */
/* #define ISDN_NFAS     1  nfas procedures provided */
/* #define ISDN_SUSPEND  1  suspend/resume procedures provided */
/* #define ISDN_HOLD     1  hold/retrieve procedures provided */
/* #define DECODCDSET    1  decode network and user specific codeset 6 and 7 */
                            /* elements into individual elements vs. string */
#define MF_IN            1  /* For MF purposes */

#ifdef NETSIDE
#define ISDN_PTMPT   1  /* ISDN Point to Multipoint. */
#endif /* NETSIDE */

#ifdef Q932
#ifndef ISDN_HOLD
#define ISDN_HOLD      1 /* hold procedures provided */
#endif
#ifndef ISDN_FACILITY
#define ISDN_FACILITY  1 /* facility procedures provided */
#endif
#endif

#endif /* XM_FEATTRP_IN */

#if (XM_PH1_TK) || (XM__PH2_TK)
/**************************************************************************
    phase1/2 trunking parameters required for XM
**************************************************************************/

#ifdef LCXMUICCT
#define LCAMUIAMT               /* if loosely coupled wrapper then define */
                                 /* loosely coupled Q.93B */
#endif

/* variants, choose none or more */
/* must agree with options delivered */

/* Q.93B protocol variants */
/* Q.2931 option */
/* #define Q2931                   ITU-T Q.2931 & Q.2971 code enabled */

#ifndef Q2931
#define DEF_Q2931         0
#else
#define DEF_Q2931         1
#endif /* Q2931 */

/* PNNI Signalling options */

#ifndef SIG_PNNI
#define SIG_PNNI               /* PNNI Signalling code enabled */
#endif /* SIG_PNNI */

#ifndef SIG_PNNI
#define DEF_SIG_PNNI      0
#else
#define DEF_SIG_PNNI      1
#endif /* SIG_PNNI */

/* AINI Signalling options */
 
/* #define SIG_AINI               AINI Signalling code enabled */

#ifndef SIG_AINI
#define DEF_SIG_AINI      0
#else
#define DEF_SIG_AINI      1
#endif /* SIG_AINI */

/* UNI 4.0 option */

#define UNI40                  /* ATM Forum UNI ver 4.0 enabled */
#ifndef UNI40
#define DEF_UNI40      0
#else
#define DEF_UNI40      1
/* #define LIJ             Leaf Initiated Join capabiltity */

#ifndef LIJ
#define DEF_LIJ          0
#else
#define DEF_LIJ          1
#endif /* LIJ */

#endif /* UNI40 */

#endif /* (XM__PH1_TK) || (XM__PH2_TK) */

#endif  /* XM */


#ifdef ICC      /* Interworking call control */
/**************************************************************************
   Call Control parameters for interworking
**************************************************************************/
 
/* product version, choose one */
 
/* interfaces */
/* #define ICC_1_5_REORG   1  ICC 1.5 file reorganization */

#ifdef ICC_1_5_REORG
#ifndef ICC_1_4_REORG
#define ICC_1_4_REORG   1       /* ICC 1.4 file reorganization */
#endif
#endif

/* #define CCT_VER_2       1       CCT version 2 */
/* #define CC_GEN_OBS_TRC  1       Generate Obesrvation trace */
/* #define CC_RMTFCDESC_VER_2  1   Version 2 RM Traffic Descriptor */
/* #define CC_SWTCHIDX_VER_2  1    Version 2 Switch Index */
/* #define ICC_AUDIT  1            ICC auditing enabled */

#ifndef RTT_VER_2 
/* #define RTT_VER_2       1       RTT version 2 */
#endif

#ifndef RMT_VER_2 
/* #define RMT_VER_2       1       RMT version 2 */
#endif

#ifndef SFT_VER_2 
/* #define SFT_VER_2       1       SFT version 2 */
#endif
 
/* lower interface, choose none or more */
/* #define LCCCLICCT            loosely coupled, PSIF */
/* #define LCCCLIRMT            loosely coupled, resource management */
/* #define LCCCLIRTT            loosely coupled, router */
/* #define LCCCLISFT            loosely coupled, switching fabric */
 
#ifdef LCCCLICCT
#ifndef LCCCT
#define LCCCT 1
#endif
#endif

#ifdef LCCCLIRMT
#ifndef LCRMT
#define LCRMT 1
#endif
#endif


#ifdef LCCCLIRTT
#ifndef LCRTT
#define LCRTT 1
#endif
#endif

#ifdef LCCCLISFT
#ifndef LCSFT
#define LCSFT 1
#endif
#endif

/* management interface, */
/* #define LCCCMILCC            loosely coupled, layer management */
 
#if (defined(LCCCLICCT) || defined(LCCCLIRTT) || defined(LCCCLIRMT) || defined(LCCCLISFT) || defined(LCCCMILCC))
#ifndef LCCMCC
#define LCCMCC        1
#endif
#ifndef LCATM
#define LCATM         1
#endif
#ifndef DEF_LCATM
#define DEF_LCATM     1
#endif
#endif
 
/* Interworkings */

/* #define CCSIBIIWF 1                 ISUP - BISUP interworking */ 
/* #define CCINSIIWF 1                 ISDN - ISUP  interworking */ 
/* #define CCAMSIIWF 1                 Q.93B - ISUP interworking */ 

/* #define SS7_BIITU2BIITU     1        BB ITU to BB ITU interworking */ 
/* #define SS7_SIITU2BIITU     1        NB ITU to BB ITU interworking */
/* #define SS7_SI7672BIITU     1        NB Q767 to BB ITU interworking */
/* #define SS7_SIANS2BIITUN    1        NB ANSI-92 to BB ITU interworking */

/* #define ICC_SIITU2INITU     1        NB ITU-92 to ISDN ITU interworking */ 
/* #define CC_INITU2SIITU      1        ITU ISDN to ITU ISUP mapping */
/* #define CC_INETSI2SIITU     1        ETSI ISDN to ITU ISUP mapping */
/* #define CC_INQSIG2SIITU     1        QSIG ISDN to ITU ISUP mapping */

/* #define CC_INNI22SIANS      1        NI2 ISDN to ANSI ISUP mapping */

/* #define CC_INETSI2SIETSI    1        ETSI ISDN to ETSI ISUP mapping */
/* #define CC_INQSIG2SIETSI    1        QSIG ISDN to ETSI ISUP mapping */

/* #define CC_INQSIG2SI767     1        QSIG ISDN to Q767 ISUP mapping */
/* #define CC_INETSI2SI767     1        ETSI ISDN to Q767 ISUP mapping */

/* #define CC_SIITU2SI767      1        ITU ISUP to Q767 ISUP mapping */
/* #define CC_SIETSI2SI767     1        ETSI ISUP to Q767 ISUP mapping */
/* #define CC_SIETSI2SIITU     1        ETSI ISUP to ITU ISUP mapping */

/* #define CC_INQSIG2INETSI    1        Q.SIG ISDN to ETSI ISDN mapping */

/* #define CC_SIITU2AMPNNI     1        ITU ISUP to Q.93B-PNNI mapping */

#ifdef CCSI
/**************************************************************************
   isup parameters required for ICC
**************************************************************************/
 
/* interfaces */
 
#ifdef LCCCLICCT
#define LCSIUISIT               /* if loosely coupled wrapper then define */
#endif
 
/* variants, choose none or more */
/* must agree with options delivered */
 
/* ISUP protocol variants */
 
/* #define ANS92                ansi, option 12 */
/* #define Q767                 q.767, option 17 */
/* #define ETSI_SS7             ETSI, option 22 */
 

#ifndef SS7
/* #define SS7                  for message functions */
 
#endif

#ifndef SIT_PARAMETER
/* #define SIT_PARAMETER 1 */
#endif

#endif  /* CCSI */
 
#ifdef CCBI        /* b-isup */
/**************************************************************************
   b-isup parameters required for ICC
**************************************************************************/
 
#ifdef LCCCLICCT
 #define LCBIUIBIT               /* if loosely coupled wrapper then define */
                                 /* loosely coupled BISUP */
#endif
 
/* variants, choose none or more */
/* must agree with options delivered */
 
/* B-ISUP protocol variants */
 
/* #define ATF2             ATM-Forum, option 13 */
 
#ifdef LCBIUIBIT
#ifndef ATM_BISUP
/* #define ATM_BISUP     1   b-isup */
#endif
#endif
 
#endif /* CCBI */

#ifdef CCIN
/**************************************************************************
   isdn parameters required for ICC
**************************************************************************/
 
/* #define INVER2                 isdn, version 2.x */
/* #define ANVER2                 isdn, version 2.x */
/* #define ISDN_3_8_PLUS          Code version 3.10 & above */
/* #define CDPTYNMB_32DIGIT       Called party number is 32 digits */

#ifdef LCCCLICCT
#define LCINUIINT               /* if loosely coupled wrapper then define */
                                /* loosely coupled ISDN */
#define LCUICMINT               /* loosely coupled common functions. */
#endif

/* variants, choose none or more */
/* must agree with options delivered */

/* ISDN protocol variants */

/* #define ETSI           etsi, europe, option 14 */
/* #define Q932           q.932 option, option 27 */
/* #define QSIG           etsi qsig, option 29 */
/* #define NI2            National ISDN 2 */

/* #define ISDN_BRI     1       basic rate interface option */
/* #define ISDN_PRI     1       primary rate interface option */
/* #define ISDN_OVERLAP 1       overlap sending/receiving provided */
/* #define ISDN_UTU     1       user to user procedures provided */
/* #define ISDN_NFAS    1       nfas procedures provided */
/* #define ISDN_SUSPEND 1       suspend/resume procedures provided */
/* #define ISDN_HOLD    1       hold/retrieve procedures provided */
/* #define ISDN_FACILITY 1      facility procedures provided */

/* Option for ITUT-88 standard - used in bearcapability encoding/decoding */
/* #define ITUT88               ITU-T 88 - for Bearer Capability */

#endif /* CCIN */

#ifdef CCAM        /* Q.93B */
/**************************************************************************
   Q.93B parameters required for ICC
**************************************************************************/

#if (defined(LCCCLICCT) | defined(LCAWUICCT))
#define LCAMUIAMT               /* if loosely coupled wrapper then define */
                                 /* loosely coupled Q.93B */
#endif

/* variants, choose none or more */
/* must agree with options delivered */
 
/* Q.93B protocol variants */
 
/* Q.2931 option */
 
/* #define Q2931                   ITU-T Q.2931 & Q.2971 code enabled */
 
#ifndef Q2931
#define DEF_Q2931         0
#else
#define DEF_Q2931         1
#endif /* Q2931 */
 
/* PNNI Signalling options */
 
#ifndef SIG_PNNI
#define SIG_PNNI               /* PNNI Signalling code enabled */
#endif /* SIG_PNNI */
 
#ifndef SIG_PNNI
#define DEF_SIG_PNNI      0
#else
#define DEF_SIG_PNNI      1
#endif /* SIG_PNNI */
 
/* AINI Signalling options */
 
/* #define SIG_AINI               AINI Signalling code enabled */

#ifndef SIG_AINI
#define DEF_SIG_AINI      0
#else
#define DEF_SIG_AINI      1
#endif /* SIG_AINI */

/* UNI 4.0 option */
 
#define UNI40                  /* ATM Forum UNI ver 4.0 enabled */
 
#ifndef UNI40
#define DEF_UNI40      0
#else
#define DEF_UNI40      1
 
/* #define LIJ             Leaf Initiated Join capabiltity */
 
#ifndef LIJ
#define DEF_LIJ          0
#else
#define DEF_LIJ          1
#endif /* LIJ */
 
#endif /* UNI40 */

#endif /* CCAM */

#ifdef CCPN
/**************************************************************************
   PNNI parameters required for ICC
**************************************************************************/
 
/* interfaces */

/* #define LCPULIPCI     loosely coupled, dummy pnni user lower layer */

#ifdef LCPULIPCI
#ifndef LCPCI
#define LCPCI 1
#endif
#endif  /* LCPULIPCI */

#if (LCPCI)
#ifndef LCATM
#define LCATM 1
#endif
#endif  /* LCPCI */

/* type, chosen automatically */
#ifndef ATM
#define ATM             /* for message functions */
#endif

#ifndef SIG_PNNI
#define SIG_PNNI       1 
#define DEF_SIG_PNNI      1
#endif
 
/* #define PNNI_ROUTING_ENABLED    1 Enable PNNI routing in CC */

#endif /* CCPN */


#ifdef CCXM        /* Connection Manager interface function */
/**************************************************************************
   Connection interface function parameters
**************************************************************************/

/* interfaces */

#ifdef LCCCLICCT
#define LCXMUICCT      /* loosely coupled upper interface (call control) */
#endif

#ifdef LCCCLIRMT
#define LCXMUIRMT      /* loosely coupled, call control */
#endif

/* Product variants specific options */
/* #define LCXMMILXM   loosely coupled, layer management */
/* #define XM_FEATTRP_SI 1 */
/* #define XM_FEATTRP_IN 1 */
/* #define XM_PH1_TK 1      Phase 1 Trunking */
/* Product variants specific options */

#if ((defined LCXMUICCT) || (defined LCXMUIRMT))

#ifndef LCCMCC
#define LCCMCC        1
#endif

#if XM_FEATTRP_SI
#define LCSIUISIT               /* if loosely coupled wrapper then define */
#ifndef LCSIT
#define LCSIT 1
#endif /* LCSIT */
#ifndef LCSS7
#define LCSS7 1
#endif
#ifndef SIT_PARAMETER
/* #define SIT_PARAMETER 1 */
#endif
#endif /* XM_FEATTRP_SI */

#if XM_FEATTRP_IN
#ifndef LCINUIINT
#define LCINUIINT               /* if loosely coupled wrapper then define */
#endif
                                /* loosely coupled ISDN */
#ifndef LCUICMINT
#define LCUICMINT               /* loosely coupled common functions. */
#endif

#endif /* XM_FEATTRP_IN */

#if (XM__PH1_TK) || (XM__PH2_TK)
#ifndef LCAMUIAMT               /* if loosely coupled wrapper then define */
#define LCAMUIAMT
#endif
                                 /* loosely coupled Q.93B */
#ifndef LCAMT
#define LCAMT      1    /* define LC flag for AMT interface */
#endif
#endif /* (XM__PH1_TK) || (XM__PH2_TK) */

#endif /* ((defined LCXMUICCT) || (defined LCXMUIRMT)) */

#endif  /* CCXM */

#endif  /* ICC */

#ifdef ZC       /* PSF - ICC (FT/HA) */
/**************************************************************************
   PSF parameters
**************************************************************************/

#undef ZC
#define ZC 1

/* management interface, lzc */
/* #define LCZCMILZC         loosely coupled, layer management */

/* The following flag must be turned-on if the customer chooses to implement */ 
/* his own packing-unpacking functions for update messages */

/* #define CUSTENV */
#endif /* ZC */

#ifdef ZR       /* PSF - ICC (FT/HA) */
/**************************************************************************
   PSF parameters
**************************************************************************/

#undef ZR
#define ZR 1

/* management interface, lzr */
/* #define LCZRMILZR         loosely coupled, layer management */

/* The following flag must be turned-on if the customer chooses to implement */ 
/* his own packing-unpacking functions for update messages */

/* #define CUSTENV */
#endif /* ZR */

#ifdef ZS       /* PSF - RT (FT/HA) */
/**************************************************************************
   PSF parameters
**************************************************************************/

#undef ZS
#define ZS 1

/* management interface, lzs */
/* #define LCZSMILZS         loosely coupled, layer management */

/* The following flag must be turned-on if the customer chooses to implement */ 
/* his own packing-unpacking functions for update messages */

/* #define CUSTENV */
#endif /* ZS */


#ifdef CC
#ifdef CCSI
/**************************************************************************
   isup parameters
**************************************************************************/

/* product version, choose one */
 
/* #define CCVER1          isup, version 1.x */
#define CCVER2         /* isup, version 2.x */

/* interfaces */

/* upper interface, choose none or more */

/* #define LCCCLISIT               loosely coupled isup, upper interface (sit.x) */

/* product specific options */

/* variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with q.930, mtp 3, sccp variants */

/*
#ifndef BELL 
#define BELL            bellcore, option 11
#define SI_ANSILNP      Support of ANSI local number portability
#endif 
*/
/*
#ifndef ANS88
#define ANS88         ansi, option 12 
#endif 
*/
/*
#ifndef ANS92
#define ANS92          ansi, option 12 
#endif 
*/
/*
#ifndef TTC
#define TTC           ttc, japan, option 13
#endif 
*/

/*
#ifndef SINGTEL
#define SINGTEL        singapore telecom, option 19
#endif 
*/
/*
#ifndef Q767
#define Q767          q.767, option 17 
#endif 
*/
/* 
#ifndef Q767IT
#define Q767IT        q.767 italy, option 20
#endif 
*/
/* 
#ifndef ETSI_SS7
#define ETSI_SS7         ETSI, option 22
#endif 
*/
/* 
#ifndef GT_FTZ
#define GT_FTZ        GT_FTZ, option 23 
#endif
*/

/* 
#ifndef RUSSIA_SS7
#define RUSSIA_SS7     RUSSIA_SS7, option 24 
#endif
*/


/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif

#ifdef Q767IT
#define Q767            /* q.767, option 17 */
#endif

#ifdef LCCCLISIT

#ifndef LCSIT
#define LCSIT 1
#endif /* LCSIT */

#endif /* LCCCLISIT */

#endif  /* CCSI */

#ifdef CCTP        /* tup */
/**************************************************************************
   tup parameters
**************************************************************************/

/* product version, choose one */
 
/* #define CCVER1          tup, version 1.x */
#define CCVER2         /* tup, version 2.x */
 
/* variants, choose none or more */
/* must agree with options delivered */
/* must agree with tup variants */
 
/* 
#ifndef CHINA
#define CHINA         china
#endif 
*/

/* interfaces */
 
/* upper interface, choose none or more */
 
/* #define LCCCLITPT               loosely coupled, TUP User upper layer */
 
/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif
#endif /* CCTP */

#ifdef CCBI        /* b-isup */
/**************************************************************************
   b-isup parameters
**************************************************************************/

/* product version, choose one */
 
/* interfaces */

/* upper interface, choose none or more */

/* #define LCCCLIBIT               loosely coupled b-isup, upper interface (bit.x) */

#ifdef LCCCLIBIT      /* loosely coupled, upper interface */
#ifndef LCATM
#define LCATM     
#endif
#define DEF_LCATM     1
#ifndef ATM_BISUP
#define ATM_BISUP  1  /* b-isup */
#endif
#endif

/* product specific options */

/* variants, choose none or more */
/* must agree with options delivered */

/* #define ATF2              ATM-Forum, option 13 */


#endif /* CCBI */

#endif /* CC */


#ifdef CF        /* configurator */
/**************************************************************************
   configurator parameters
**************************************************************************/

/* product specific options */

/* variants, choose none or more */

/* #define CF_SE 1   configure MOS/68302 */

/* #define CF_QI 1   configure MOS/68360 */

/* #define CF_PQ 1   configure MOS/MPC860 */

/* #define CF_SD 1   configure MTP2 */

/* #define CF_SN 1   configure MTP3 */

/* #define CF_SR 1   configure Simple Router */

/* #define CF_SP 1   configure SCCP */

/* #define CF_ST 1   configure TCAP */

/* #define CF_TP 1   configure TUP */

/* #define CF_SI 1   configure ISUP */

/* #define CF_IN 1   configure ISDN */

/* #define CF_BD 1   configure LAPD */

/* #define CF_SG 1  Sys Mgr */
/* #define CF_SH 1  Sys Agent */
/* #define CF_MR 1  Msg Rtr */
/* #define CF_HC 1  H.323 */
/* #define CF_HZ 1        */
/* #define CF_HI 1  TUCL */
/* #define CF_HU 1  HU    */

#ifdef ELVIS_BIT3
#define CF_ENB_BIT3
#else
#ifdef ELVIS_IMP
#define CF_ENB_IMP
#endif /* ELVIS_IMP */
#endif /* ELVIS_BIT3 */

/* must agree with options delivered */
/* if applicable, must agree with q.930, mtp 3, sccp variants */

/* #define BELL          bellcore, option 11 */
/* #define ANS88         ansi, option 12 */
/* #define ANS92         ansi, option 12 */
/* #define TTC           ttc, japan, option 13 */
/* #define SPCO             connection oriented SCCP */

/* type, chosen automatically */

#ifndef SS7
#define SS7             /* for message functions */
#endif

#endif



#ifdef SS       /* Common System Services */
/**************************************************************************
   Common System Services parameters
**************************************************************************/

/* interfaces */

/* management interface, lns , choose none or more */

/* product specific options */

/* #define SS_DRVR_SUPPORT        for supporting driver tasks */
#define SS_RTR_SUPPORT        /* for supporting router tasks */
/* #define SS_SINGLE_THREADED     for single threaded execution */
/* #define SS_OLD_THREAD          for backward compatibility */

#ifdef SS_DRVR_SUPPORT
/* for backward compatibility */
#define ENB_RELAY
/* for forward compatibility */
#define RYINT1
#endif /* SS_DRVR_SUPPORT */


/* post format, choose none or one */

#define FCSPOSTINT      /* forward compatibility, post format */

#endif /* SS */


#ifdef SS_MT    /* MTSS-Solaris */
/**************************************************************************
   MTSS-Solaris parameters
**************************************************************************/
#ifndef CONAVL
/* fix for ccpu00139543 */
#ifndef NOCONAVL
#define CONAVL          /* console availability option */
#endif
#endif
#define STDIO_INCLD

#endif /* SS_MT */


#ifdef NS       /* NTSS */
/**************************************************************************
   NTSS parameters
**************************************************************************/

/* Choose the module */
#define  NU                  /* choose UNTSS */
/* #define  NK                  choose KNTSS */

#ifdef NU
#define STDIO_INCLD

/* product specific options */
#define _WIN32_WINNT  0x400    /* for using Windows NT 4.0 calls */

#ifndef CONAVL
#ifndef NOCONAVL
#define CONAVL                 /* console availability option */
#endif
#endif
#endif /* NU */

#ifdef NK
#endif /* NK */

/* interfaces */
/* management interface, lns , choose none or more */

/* #define NS_ENB_MGMT         for enabling management interface */

#ifdef NS_ENB_MGMT

/* loose coupled management interface, choose one or none */

/* #define LCNSMILNS        loosely coupled, layer management */

/* debug mngmt interface, choose one or none */

/* #define DBNSMILNS           debug output enabled for mgmt interface */

#endif /* NS_ENB_MGMT */

#endif /* NS */


#ifdef BS        /* Berkeley Sockets Layer 1*/
/**************************************************************************
   BS parameters
**************************************************************************/
 
/* interfaces */
 
/* upper interface, choose none or more */
 
/* #define LCBSUIBST               loosely coupled bs upper interface */
/* #define BCBSUIMAC               backward compatibility, mac */
 
/* layer management options */

/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* backward compatilbility, layer management */
/* choose all */

#define LCBSLM          /* loosely coupled, layer management */
#else
#ifdef TCLM             /* backward compatilbility, layer management */
/* choose all */

#define TCBSLM          /* tightly coupled, layer management */
#else                   /* tightly or loosely coupled, layer management */
/* choose none or one */

#define TCBSLM          /* tightly coupled, layer management */
/* #define LCBSLM           loosely coupled, layer management */
#endif
#endif
 
/* product specific options */
 
#endif /* BS */


#ifdef SG       /* System Manager */
/**************************************************************************
   System Manager parameters
**************************************************************************/

#ifdef TDS_CORE2

/*** Interfaces Coupling Options ***/

/* #define LCSGMILSG    loosely coupled, layer management */

/*** Product feature flags  ***/

/* #define SG_DFTHA     for compiling SG in distributed env */

/* #define SG_USTA      enable alarms at compile time  */

/* #define SG_DEBUG     enable all debug print masks at compile time  */

#define SG_PRESERVE_STANDBY   /* preserve standby in dedicated configuration */

/* #define SG_RUG           Rolling upgrade support enabled */ 
/****************************** Interfaces Version Flags ******************/

/* MR Management interface */
#define LMRV1              /* MR LM interface version 2.0 */

/* SH Management interface */
#define LSHV1              /* SH LM interface version 1.0 */

/* SG Peer interface */
#define SGPIFV1              /* SG Peer interface version 1.0 */

/* Layer management interface */
#define LSGV1              /* Layer Management interface version 1.0 */

#else /* TDS_CORE2 */

/* for CORE release 1.1 */

/*** Interfaces Coupling Options ***/

/* #define LCSGMILSG    loosely coupled, layer management */

/* #define LCSGPI       loosely coupled, System Manager peer interface */

/* #define TCSGPI       tightly coupled, System Manager peer interface */

/* #define LCSGMILSH    loosely coupled, System Agent
                        Enable the LCSMSHMILSH under #ifdef SM */

/* #define LCSGMILMR    loosely coupled, Message Router
                        Enable the LCSMMRMILMR under #ifdef SM */
#endif /* TDS_CORE2 */

#endif /* SG */


#ifdef SH       /* System Agent */
/**************************************************************************
   System Agent parameters
**************************************************************************/

#ifdef TDS_CORE2

/*** Interfaces Coupling Options ***/

/* #define LCSHMILSH    loosely coupled, layer management */

/*** Product feature flags  ***/

/* #define SH_DFTHA     for compiling SH in distributed env */

/* #define SH_USTA      enable alarms at compile time  */

/* #define SH_DEBUG     enable all debug print masks at compile time  */

/* #define SH_RUG           Rolling upgrade support enabled */ 
/****************************** Interfaces Version Flags ******************/

/* SH Peer interface */
#define SHPIFV1              /* SH peer interface version 1.0 */

/* Layer management interface */
#define LSHV1               /* Layer Management interface version 1.0 */

#else /* TDS_CORE2 */

/* for CORE release 1.1 */

/*** Interfaces Coupling Options ***/

/* #define LCSHMILSH    loosely coupled, layer management */

/* #define LCSHPI       loosely coupled, System Agent peer interface */
/*
#error "ERROR - Compile time flag SH has been erroneously defined. There can be two reasons for this - 1) You are using DFT/HA and have not enabled the global flag TDS_CORE2 or 2) You are using a version of Tornado, which enables an internal flag called SH. If point 1 is TRUE, please enable TDS_CORE2. If point 2 is TRUE, please add #undef SH in the files in which compilation error is reported (mostly sm_bdy1.c and sm_ex_ms.c), and remove this line."
*/
#endif /* TDS_CORE2 */

#endif /* SH */


#ifdef MR       /* Message Router */
/**************************************************************************
   Message Router parameters
**************************************************************************/

#ifdef TDS_CORE2

/*** Interfaces Coupling Options ***/

/* #define LCMRMILMR    loosely coupled, layer management */

/*** Product feature flags  ***/

/* #define MR_DFTHA     for compiling MR in distributed env */

/* #define MR_USTA      enable alarms at compile time  */

/* #define MR_DEBUG     enable all debug print masks at compile time  */

/* #define MR_PORT_MCAST     for customer defined portable multicast fns */

/* #define MR_RUG            Rolling upgrade support enabled */ 
/****************************** Interfaces Version Flags ******************/

/* MR Peer interface */
#define MRPIFV1              /* MR peer interface version 1.0 */


/* Layer management interface */
#define LMRV1              /* Layer Management interface version 1.0 */

#else /* TDS_CORE2 */

/* for CORE release 1.1 */

/*** Interfaces Coupling Options ***/

/* #define LCMRMILMR    loosely coupled, layer management */

/* #define LCMRPI       loosely coupled, Message Router peer interface */

#endif /* TDS_CORE2 */

#endif /* MR */


#ifdef PR   /* MPC860SAR Driver */
/****************************************************************************
 *    MPC860SAR Driver parameters
****************************************************************************/

/*** Interfaces Coupling Options ***/

/* #define LCPRMILPR    loosely coupled, layer management */

/* #define LCPRUIAAL    loosely coupled, AAL interface */

/* interface flags, chosen automatically */

#ifdef LCPRUIAAL

#ifndef LCAAL
#define LCAAL 1            /* define LC flag for AAL interface */
#endif

#endif /* LCPRUIAAL */

#ifdef LCPRMILPR

#ifndef LCLPR
#define LCLPR 1            /* define LC flag for LPR interface */
#endif

#endif /* LCPRMILPR */

#if (LCAAL || LCLPR)

#ifndef LCATM
#define LCATM 1            /* define LC flag for ATM stack */
#endif

#endif

/* product specific options */

/* type, chosen automatically */

#ifndef ATM
#define ATM  1             /* ATM stack */
#endif

/* #define UNI40                  ATM Forum UNI ver 4.0 enabled */
 
#ifndef UNI40
#define DEF_UNI40      0
#else
#define DEF_UNI40      1
#endif /* UNI40 */

/* #define SIG_PNNI               PNNI Signalling code enabled */

#ifndef SIG_PNNI
#define DEF_SIG_PNNI   0
#else
#define DEF_SIG_PNNI   1
#endif /* SIG_PNNI */

/* #define Q2931                  ITU-T Q.2931 & Q.2971 code enabled */

#ifndef Q2931
#define DEF_Q2931         0
#else
#define DEF_Q2931         1
#endif /* Q2931 */
 
/*** Following options must be defined ***/

#define SAR          /* Use the SAR section in hardware header files */
#define PQ_PPC860    /* Define processor type PowerPC MPC860 */

#endif /* PR - MPC860SAR Driver */


/**************************************************************************
                              GPRS stack
 **************************************************************************/
/**************************************************************************
                             Network Services (GN) 
 **************************************************************************/
#ifdef GN

/*** Interface Coupling Options ***/

/* upper interface, GNS, choose none or more */

/* #define LCGNUIGNS   loosely coupled, upper interface */

/* lower interface, frd, choose none or more */

/* #define LCGNLIFRD   loosely coupled, frd layer */
 
/* management interface, lgn, choose none or more */

/* #define LCGNMILGN    loosely coupled, layer management */


/* flags should be turned off for backward compatibility */
#define FRD2               /* new lower interface */

/*** Layer Management Options ***/
/* LCLM or TCLM chosen above, if LCLM or TCLM not chosen */
/* then choose none or one within else */

#ifdef LCLM             /* layer management */
/* #define LCGNLM          loosely coupled, layer management */
#endif


/*** Internal defines - do not change ***/
#ifdef LCGNLIFRD
#ifdef LCFRD
#undef LCFRD
#endif
#define LCFRD 1
#endif /* LCGNLIFRD */

#ifdef LCGNUIGNS
#ifdef LCGNS
#undef LCGNS
#endif
#define LCGNS 1
#endif /* LCGNUIGNS */

#ifdef LCGNMILGN
#ifdef LCLGN
#undef LCLGN
#endif
#define LCLGN 1
#endif /* LCGNMILGN */

#endif /* GN */

/**************************************************************************
                             GTP (GT) 
 **************************************************************************/
#ifdef GT

#undef GT
#define GT 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interface Coupling Options ***/

/* upper interface, GGU, choose none or more */

/* #define LCGTUIGGU       loosely coupled, GTP upper interface */

/* lower interface, choose none or more */

/* #define LCGTLIHIT       loosely coupled, GTP lower layer */

/* management interface, lgn, choose none or more */

/* #define LCGTMILGT      loosely coupled, layer management */

/* product specific options */

/* variants, choose none or more */
/* must agree with options delivered */

/*#define GTP_C_2G 1*/   /* GTP-GPRS, control plane option */
/*#define GTP_C_3G 1*/   /* GTP-3G, control plane option */
/*#define GTP_U 1 */      /* GTP-user plane option */
/*#define GTP_U_2G 1 */   /* GTP_2G user plane */
#ifdef GTP_U_2G
#ifndef GTP_U
#define GTP_U 1
#endif
#endif
/*#define GTP_U_3G 1 */   /* GTP_3G user plane */
#ifdef GTP_U_3G
#ifndef GTP_U
#define GTP_U 1
#endif
#endif
/*#define GTP_CHRG 1 */  /* GTP charging option */
/*#define GTP_CHRG_ASN1 1 */  /* GTP ASN.1 charging option */
/*#define GTP_COMPOSED 1 */  /* Option to enable GTP-U and GTP-C running
                              together , only available for GTP - 2G */

/*#define GTP_GGSN_DSTRB 1 */ /* GGSN Distribution option */

/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */

/* upper interface */
#ifdef LCGTUIGGU 
#ifdef LCGGU
#undef LCGGU
#endif
#define LCGGU 1
#endif 

/* lower interface */
#ifdef LCGTLIHIT 
#ifdef LCHIT
#undef LCHIT
#endif
#define LCHIT 1
#endif 

/* layer management interface */
#ifdef LCGTMILGT
#ifdef LCLGT
#undef LCLGT
#endif
#define LCLGT 1
#endif /* LCGTMILGT */

/* 1. Dependency of ZB and GT_FTHA */
#ifdef ZB
#ifndef GT_FTHA 
#define GT_FTHA   1
#endif /* GT_FTHA */
#endif /* ZB */

/* Rolling upgrade support */
/*#define GT_RUG 1 */ /* Rolling upgrade support */
/*#define TDS_ROLL_UPGRADE_SUPPORT 1 */ /* Rolling upgrade support */
#endif /* GT */

#ifdef ZB       /* GPRS PSF-GTP (FT/HA) */
/**************************************************************************
   GPRS PSF-GTP (FT/HA) parameters
**************************************************************************/
#undef ZB
#define ZB 1

/*********************************interfaces******************************/

/* #define LCZBMILZB       loosely coupled, layer management interface */

/****************************** Interfaces Version Flags ******************/

/* Layer management interface */
/* #define LZBV1              Layer Management interface version 1.0 */
/* Peer interface */
/* #define ZBPV1              Layer Management interface version 1.0 */

/*********************************Misc Flags******************************/

/* #define ZB_USTA       enable alarms by default */
/* #define ZB_DEBUG      enable debug prints by deault (only for debugging) */

/* #define ZB_UPD_TPDU   enable updation of TPDU at sby during RT */
/* #define ZB_REORD_PDU_UDP   enable updation of Re-odering TPDU during RT */

/***********************INTERNAL FLAGS (Do not modify!)********************/

#ifdef LCZBMILZB
#ifdef LCLZB
#undef LCLZB
#endif
#define LCLZB 1
#endif /* LCZBMILZB */

#endif /* ZB */

#ifdef GL       /* Logical Link Control (LLC) for GPRS */
/**************************************************************************
   Logical Link Control (LLC) parameters
**************************************************************************/

/* product specific options */
#define GPRS_SOLSA         /* Backward Compatibility - Enable Support of LSA */
/* #define GL_FTHA         FTHA flag */ 


/* product version, choose one or both */
/* Enable following when code supports SGSN  */
/* #define SGSN         Code for SGSN */
 
/* Enable following when code supports MS */
/* #define MST           Code for MS */

/* #ifndef SGSN */
/* #undef GG                       BSSGP not supported */
/* #endif  SGSN */
 
/* #ifndef MST */
/* #undef GZ                       RLC/MAC not supported */
/* #endif  MST */
 

/* interfaces */

/* lower GBR interface */
/* #define LCGLLIGBR              loosely coupled, LLC to BSSGP/RLC layer */

/* upper GLS interface, choose none or more */
/* #define LCGLUIGLS              loosely coupled, LLC to layer 3         */

/* layer management options */
/* #define LCGLMILGL              loosely coupled, layer management */

/* acceptance test flags */
#ifdef GL_ACCEPT_TEST

#ifdef LCGLLIGBR
#ifdef GZ
#define LCGZUIGBR
#endif /* #ifdef GZ */
#endif /* #ifdef LCGLLIGBR */
 
/* acceptance test flags */
#ifdef LCGLUIGLS
#ifdef GM
#define LCGMLIGLS
#endif
#ifdef GY
#define LCGYLIGLS
#endif
#endif

#endif /* #ifdef GL_ACCEPT_TEST */


/* loosely coupled GLS interface */
#ifdef LCGLUIGLS
#ifndef LCGLS
#define LCGLS 1
#endif
#endif

/* loosely coupled GBR interface */
#ifdef LCGLLIGBR
#ifndef LCGBR
#define LCGBR 1
#endif
#endif

#ifdef LCGLMILGL

#ifndef LCLGL
#define LCLGL 1
#endif /* LCLGL */

#endif /* LCGLMILGL */

#endif /* #ifdef GL */


/**************************************************************************
                             BSSGP (GG) 
 **************************************************************************/

#ifdef GG

#undef GG
#define GG 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCGGUIGBR         loosely coupled, BSSGP upper layer */

/* lower interface, choose none or more */

/* #define LCGGLIGNS         loosely coupled, BSSGP lower layer */

/* layer manager interface, choose none or more */

/* #define LCGGMILGG         loosely coupled, layer management */


/* product specific options */
#define GPRS_SOLSA         /* Backward Compatibility - Enable Support of LSA */
#define GPRS_3DIGIT_MNC    /* Backward Compatibility - Enable 3 Digit MNC */
/* #define GG_FTHA            FTHA flag */

/* variants, choose none or more */
/* must agree with options delivered */

/* #define SGSN         ETSI SGSN */
/* #define BSS          ETSI BSS */

/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */

#ifdef LCGGMILGG
#ifdef LCLGG
#undef LCLGG
#endif /* LCLGG */
#define LCLGG 1
#endif /* LCGGMILGG */

#ifdef LCGGUIGBR
#ifdef LCGBR
#undef LCGBR
#endif /* LCGBR */
#define LCGBR 1
#endif /* LCGGUIGBR */

#ifdef LCGGLIGNS
#ifdef LCGNS
#undef LCGNS
#endif /* LCGNS */
#define LCGNS 1
#endif /* LCGGLIGNS */

#endif /* GG */


#ifdef GS       /* SNDCP */
/**************************************************************************
   SNDCP parameters
**************************************************************************/
#undef GS 
#define GS 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCGSUIGSP         loosely coupled, SNDCP upper layer */

/* lower interface, choose none or more */

/* #define LCGSLIGLS     loosely coupled, lower layer */

/* management interface, lsn , choose none or more */

/* #define LCGSMILGS        loosely coupled, layer management */


/* product specific options */
/* #define GS_FTHA          FTHA interface flag */

/* variants, choose none or more */
/* must agree with options delivered */

/* #define SGSN         ETSI SGSN */
/* #define MST          ETSI MS */

/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */


#ifdef LCGSMILGS

#ifndef LCLGS
#define LCLGS 1
#endif /* LCLGS */

#endif /* LCGSMILGS */


#ifdef LCGSUIGSP

#ifndef LCGSP
#define LCGSP 1
#endif /* LCGSP */

#endif /* LCGSUIGSP */


#ifdef LCGSLIGLS

#ifndef LCGLS
#define LCGLS 1
#endif /* LCGLS */

#endif /* LCGSLIGLS */


#endif /* GS */

#ifdef GR       /* SGSN Relay */
/**************************************************************************
   SGSN Relay parameters
**************************************************************************/
#undef GR 
#define GR 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCGRLIGSP         loosely coupled, SNDCP upper layer */

/* #define LCGRLIGGU         loosely coupled, Relay -> GTP i/f */

/* #define LCGRLIGAP         loosely coupled, Relay -> BSSAP+ interface */

#ifdef LCGRLIGSP

#ifndef LCGSP
#define LCGSP 1
#endif /* LCGSP */

#endif /* LCGRLIGSP */

#ifdef LCGRLIGGU
#ifndef LCGGU
#define LCGGU 1
#endif /* LCGGU */
#endif /* LCGRLIGGU */

#ifdef LCGRLIGAP
#ifndef LCGAP
#define LCGAP 1
#endif /* LCGAP */
#endif /* LCGRLIGAP */


#endif /* GR */


#ifdef GW       /* Interworking  Function at GGSN */
/**************************************************************************
   Inerworking Function (IWF) parameters
**************************************************************************/
#undef GW 
#define GW 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* interface, choose none or more */

/* #define LCGWLIGGU         loosely coupled, IWF -> GTP i/f */

#ifdef LCGWLIGGU
#ifndef LCGGU
#define LCGGU 1
#endif /* LCGGU */
#endif /* LCGWLIGGU */


#endif /* GW */

#ifdef GU       /* Relay on IU interface at SGSN/RNC */
/**************************************************************************
   SGSN/RNC Relay parameters
**************************************************************************/
#undef GU 
#define GU 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* interface, choose none or more */

/* #define LCGULIGGU         loosely coupled, Relay at SGSN/RNC -> GTP i/f */

#ifdef LCGULIGGU
#ifndef LCGGU
#define LCGGU 1
#endif /* LCGGU */
#endif /* LCGULIGGU */


#endif /* GU */

#ifdef GM       /* GMM/SM */
/**************************************************************************
   GMM/SM parameters
**************************************************************************/
#undef GM 
#define GM 1

/******************* section to be changed by CUSTOMERS ******************/ 
/*** Product options ***/
#define GMMSM_UMTS     1    /* to enable UMTS */
#define GMMSM_GSM      1    /* to enable GSM */

/** general flags **/
#define SGSN_CNTRL_DISTRIBUTED  /* if SGSN control is distributed */ 
#define GMMSM_WITH_TRACE        /* to enable trace */
#define GM_USTA                 /* to enable alarms */
#define GM_RUG                  /* for rolling upgrade */
#define GM_FTHA                 /* for FTHA environment */
#define GPRS_SOLSA              /* TBD */
#define GPRS_3DIGIT_MNC         /* enable if the MNC digit is of 3 digits */
#define GM_DEBUG                /* debug flag */

/** GSM flags: distribution **/
#define GMMSM_LLC_TLLI_DISTRIBUTION    /* to enable TLLI distribution at LLC */
#define GMMSM_BSSGP_TLLI_DISTRIBUTION  /* to enable TLLI distribution at 
                                          BSSGP */
#define LLC_ENHANCEMENT                /* to support LLC enhancements */

/** GSM flags: Specification conformance **/
#define GMMSM_GSM_R98      /* to support R98 */ 
#define GMMSM_GSM_R99      /* to support R99 */ 
#define GMMSM_GSM_R4       /* to support R4 */

/** UMTS flags: distribution **/
/* #define GMMSM_RANAP_DISTRIBUTED  * enable if RANAP is distributed */ 

/** UMTS flags: release **/
#define GMMSM_UMTS_R99     /* to support R99 */
#define GMMSM_UMTS_R4      /* to support R4 */
#define GMMSM_R5           /* to enable R5 at LM interface */ 
#define GMMSM_REL5         /* to enable R5 at GMU interface */

/** layer manager flag **/
#define SMGM_LMINT3        /* layer manager i/f version 3 */


/** interface flags **/
#define GMUV2              /* to enable GMUINTERFACE V2 */
#define RPT_REL5           /* to enable RANAP REL5 */ 
#define RPTV2              /* to enable RPTV2 */
#define GBRV1              /* to enable BSSGP (GBR) version 1 */
#define GLSV1              /* to enable LLC (GLS) version 1 */ 

/*** Interfaces Coupling Options ***/
#define LCGMUIGMU    1 /* upper interface LC */
#define LWLCGMUIGMU  1 /* upper interface LW LC */ 

/** lower interface **/
/* BSSGP */
#define LCGMLIGBR    1 /* lower interface LC GMM -> BSSGP */ 
#define LCGGUIGBR    1 /* lower interface LC BSSGP -> GMM */

/* LLC */
#define LCGMLIGLS    1 /* lower interface LC GMM -> LLC */
#define LCGLUIGLS    1 /* lower interface LC LLC -> GMM */ 

/* RANAP interface: select none or either of them */
#define LCGMLIRPT    1 /* lower interface LC GMM -> RANAP */
#define LCRAUIRPT    1 /* lower interface LC RANAP -> GMM */
#define LWLCGMLIRPT  1 /* lower interface LW LC GMM -> RANAP */
#define LWLCRAUIRPT  1 /* lower interface LW LC RANAP -> GMM */ 

/** management interface **/
#define LCGMMILGM    1 /*  loosely coupled, layer management */
#define LCSMGMMILGM  1 /*  loosely coupled, layer management */

/************** section NOT to be changed by CUSTOMERS **********/
/** upper interface: various applications **/
#ifdef LCGMUIGMU
#define LCGELIGMU    1
#define LCGDLIGMU    1
#define LCGFLIGMU    1
#define LCGXLIGMU    1
#define LCGYLIGMU    1
#endif /* LCGMUIGMU */

#ifdef LWLCGMUIGMU
#define LWLCGELIGMU  1
#define LWLCGDLIGMU  1
#define LWLCGFLIGMU  1
#define LWLCGXLIGMU  1
#define LWLCGYLIGMU  1
#endif /* LWLCGMUIGMU */

/* type, chosen automatically */

/* upper interface loose coupled */
#if LCGMUIGMU
#ifdef LCGMU
#undef LCGMU
#endif /* LCGMU */
#define LCGMU 1
#endif /* LCGMUIGMU */

/* upper interface light weight loose */
#if LWLCGMUIGMU
#ifdef LWLCGMU
#undef LWLCGMU
#endif /* LWLCGMU */
#define LWLCGMU 1
#endif /* LWLCGMUIGMU */

/* lower interface BSSGP */
#if LCGMLIGBR
#ifdef LCGBR
#undef LCGBR
#endif /* LCGBR */
#define LCGBR 1
#endif /* LCGMLIGBR */

/* lower interface LLC */
#if LCGMLIGLS
#ifdef LCGLS
#undef LCGLS
#endif /* LCGLS */
#define LCGLS 1
#endif /* LCGMLIGLS */

/* lower interface RANAP */
#if LCGMLIRPT
#ifdef LCRPT
#undef LCRPT
#endif /* LCRPT */
#define LCRPT 1
#endif /* LCGMLIRPT */

/* lower interface RANAP light weight loose */
#if LWLCGMLIRPT
#ifdef LWLCRPT
#undef LWLCRPT
#endif /* LWLCRPT */
#define LWLCRPT 1
#endif /* LWLCGMLIRPT */

/* layer manager interface */
#if LCGMMILGM
#ifdef LCLGM
#undef LCLGM
#endif /* LCLGM */
#define LCLGM 1
#endif /* LCGMMILGM */

#define GMMSM

#ifdef GM_RUG

#ifndef GM_FTHA
#error "GM_FTHA should be defined if GM_RUG is defined"
#endif 

#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "Please enable TDS_ROLL_UPGRADE_SUPPORT in make file"
#endif

#endif /* GM_RUG */

#ifndef TDS_CORE2
#error "Please enable TDS_CORE2 flag in make file"
#endif

#endif /* GM */


/**************************************************************************
                        PSF-GMM/SM (FT/HA) parameters
**************************************************************************/
#ifdef ZK      /* PSF-GMMSM */ 
#undef ZK
#define ZK 1

/*
 ************************** Interfaces Coupling Options ******************
 */

/* enable following options depending upon coupling requirements */
#define LCZKMILZK    /* loosely coupled, management i/f of GMMSM */ 
#define LCSMZKMILZK  /* loosely coupled, SM i/f */

/*
 ************************** Interface Version ****************************
 */
#define LZKV1     /* Layer manager interface version */
#define ZKPV1     /* Peer interface version */

/*
 ************************** LM Configuration  ***************************
 */

#define ZK_USTA      /* enable alarms by default */
#define ZK_DEBUG     /* enable debug prints by deault (only for debugging) */

/*
 ********************* INTERNAL FLAGS (Do not modify!) *******************
 */

#ifndef CM_PSF_MBUF_USAGE
#define CM_PSF_MBUF_USAGE  /* Common PSF usage */
#endif

#ifndef CMPSF_EARLY_CFM_IN_GO_ACTIVE
#define CMPSF_EARLY_CFM_IN_GO_ACTIVE
#endif

#ifdef ZK_DFTHA

#ifndef CMPSF_DFTHA
#define CMPSF_DFTHA
#endif

#endif /* ZK_DFTHA */


#ifdef LCZKMILZK
#ifdef LCLZK
#undef LCLZK
#endif
#define LCLZK 1
#endif /* LCZKMILZK */

#ifndef GM_FTHA
#error "Define GM_FTHA in GM section of envopt.h"
#endif

#ifndef TDS_CORE2
#error "Please define TDS_CORE2 in make file"
#endif

#endif /* ZK */


#ifdef GO       /* Location Management for GTP */
/**************************************************************************
   GO parameters
**************************************************************************/
#undef GO 
#define GO 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCGOLIGGU         loosely coupled, GO -> GTP i/f */


/* GO -> GTP i/f */
#ifdef LCGOLIGGU 
#ifndef LCGGU
#define LCGGU 1
#endif /* LCGGU */
#endif /* LCGOLIGGU */

#endif /* GO */


#ifdef GH       /* Charging for GTP */
/**************************************************************************
   GH parameters
**************************************************************************/
#undef GH 
#define GH 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCGHLIGGU         loosely coupled, GH -> GTP i/f */


/* GH -> GTP i/f */
#ifdef LCGHLIGGU 
#ifndef LCGGU
#define LCGGU 1
#endif /* LCGGU */
#endif /* LCGHLIGGU */

#endif /* GH */


#ifdef GI       /* CC entity on IU interface for GTP */
/**************************************************************************
   GI parameters
**************************************************************************/
#undef GI 
#define GI 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCGILIGGU         loosely coupled, GI -> GTP i/f */


/* GI -> GTP i/f */
#ifdef LCGILIGGU 
#ifndef LCGGU
#define LCGGU 1
#endif /* LCGGU */
#endif /* LCGILIGGU */

#endif /* GI */


#ifdef NM       /* NM */
/**************************************************************************
   NM parameters
**************************************************************************/
#undef NM 
#define NM 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* lower interface, choose none or more */

/* #define LCNMLIGBR         loosely coupled, NM -> BSSGP i/f */

#ifdef LCNMLIGBR

#ifndef LCGBR
#define LCGBR 1
#endif /* LCGBR */

#endif /* LCNMLIGBR */

#endif /* NM */


#ifdef GB       /* BSS Relay */
/**************************************************************************
   GB parameters
**************************************************************************/
#undef GB 
#define GB 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* lower interface, choose none or more */

/* #define LCGBLIGBR         loosely coupled, BSS Relay -> BSSGP i/f */

#ifdef LCGBLIGBR

#ifndef LCGBR
#define LCGBR 1
#endif /* LCGBR */

#endif /* LCGBLIGBR */

#endif /* GB */

/**************************************************************************
                             BSSAP+ (GA)
 **************************************************************************/

#ifdef GA

#undef GA
#define GA 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCGAUIGAP         loosely coupled, BSSAP+ upper layer */

/* lower interface, choose none or more */

/* #define LCGALISPT         loosely coupled, BSSAP+ lower layer */

/* layer manager interface, choose none or more */

/* #define LCGAMILGA         loosely coupled, layer management */


/* product specific options */
/* #define GPRS_3DIGIT_MNC    Backward Compatibility - Enable 3 Digit MNC */
/* #define GA_FTHA            FTHA flag */

/* variants, choose none or more */
/* must agree with options delivered */

/* #define SGSN         ETSI SGSN */
/* #define VLR          ETSI VLR */

/************** section NOT to be changed by CUSTOMERS **********/

#ifndef SPT2
#define SPT2
#endif


/* type, chosen automatically */
#ifdef LCGAMILGA
#ifdef LCLGA
#undef LCLGA
#endif /* LCLGA */
#define LCLGA 1
#endif /* LCGAMILGA */

#ifdef LCGAUIGAP
#ifdef LCGAP
#undef LCGAP
#endif /* LCGAP */
#define LCGAP 1
#endif /* LCGAUIGAP */

#ifdef LCGALISPT
#ifdef LCSPT
#undef LCSPT
#endif /* LCSPT */
#define LCSPT 1
#endif /* LCGALISPT */

#ifdef SGSN
#define GA_SGSN 1
#endif /* SGSN */

#ifdef VLR
#define GA_VLR 1
#endif /* VLR */

#endif /* GA */


#ifdef MM

/**************************************************************************
                             Mobility Management (MM)
 **************************************************************************/

#undef MM
#define MM 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* lower interface, choose none or more */
/* #define LCMMLIGAP         loosely coupled, MM -> BSSAP+ lower layer */

/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */

#ifdef LCMMLIGAP
#ifdef LCGAP
#undef LCGAP
#endif /* LCGAP */
#define LCGAP 1
#endif /* LCMMLIGAP */

#endif /* MM */

#ifdef GE

/**************************************************************************
                             GMM Application at SGSN (GE)
 **************************************************************************/

#undef GE
#define GE 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* lower interface, choose none or more */
/* #define LCGELIGAP         loosely coupled, GE -> BSSAP+ lower layer */

/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */

#ifdef LCGELIGAP
#ifdef LCGAP
#undef LCGAP
#endif /* LCGAP */
#define LCGAP 1
#endif /* LCGELIGAP */

#endif /* GE */

/****************************************************************************
                        End of GPRS stack                                    
****************************************************************************/

/* variants, choose none or more */
/* must agree with options delivered */
/**************************************************************************
                        RNSAP
 **************************************************************************/
#ifdef RN

#undef RN
#define RN 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interface Coupling Options ***/

/* #define LWLCRNUIRPT      light weight loosely coupled, upper interface */
/* #define LCRDLIRNT        loosely coupled, lower layer */
/* #define LCRNUIRNT        loosely coupled, upper interface */
/* #define LCRNLISPT        loosely coupled, lower layer */
/* #define LCRNMILRN        loosely coupled, layer management */

#define RN_AUDIT     1   /* RNSAP audit control */
#define RNSAP_FDD    1   /* RNSAP FDD case */
#define RNSAP_TDD    1   /* RNSAP TDD case */

/**** Upper Interface flags *****/
#define RNT_AUDIT      1 /* Audit support at upper interface */
/* #define RNSAP_REL4  1    Upper interface compliant to 25.413 ver 410 */

/**** Lower Interface Flags  *****/
/* #define SPTV1          1    Lower Interface compliant to SCCP ITU-92 */
/* #define SPTV2          1    Lower Interface compliant to SCCP ITU-96 */

#define RN_USTA 
#define RN_DEBUG

/* variants, choose none or more */
/* must agree with options delivered */


/************** section NOT to be changed by CUSTOMERS **********/

#ifdef  RNSAP_FDD
#ifndef RNSAP_TDD
#define RNSAP_TDD    1   /* RNSAP TDD case */
#endif 
#endif


#ifndef SPCO
#define SPCO
#endif

#ifndef SPT2
#define SPT2
#endif

#ifndef SPTV1
#ifndef SPTV2
#define SPTV2
#endif /* SPTV2 */
#endif /* SPTV1 */

#ifdef SPTV1
#ifdef SPTV2
#undef SPTV1
#endif /* SPTV2 */
#endif /* SPTV1 */

/* upper interface */
#ifdef LCRNUIRNT 
#ifdef LCRNT
#undef LCRNT
#endif
#define LCRNT 1
#endif 

#ifdef LWLCRNUIRNT
#ifdef LWLCRNT
#undef LWLCRNT
#endif
#define LWLCRNT 1
#endif /* LWLCRNUIRNT */


/* lower interface */
#ifdef LCRNLISPT 
#ifdef LCSPT
#undef LCSPT
#endif
#define LCSPT 1
#endif 

/* layer management interface */
#ifdef LCRNMILRN
#ifdef LCLRN
#undef LCLRN
#endif
#define LCLRN 1
#endif /* LCRNMILRN */

/* Dependancy over common files flags */
#ifndef CM_PASN_ESC_SUPPORT
#define CM_PASN_ESC_SUPPORT
#endif /* CM_PASN_ESC_SUPPORT */

#ifndef CM_PASN_CLASS_IDTYPE
#define CM_PASN_CLASS_IDTYPE
#endif /* CM_PASN_ESC_SUPPORT */

#ifndef TDS_ROLL_UPGRADE_SUPPORT
#ifdef RN_RUG
#undef RN_RUG
#endif /* RN_RUG */
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

#ifndef RNT_AUDIT
#ifndef SPTV2
#ifdef RN_AUDIT
#undef RN_AUDIT
#endif /* RA_AUDIT */
#endif /* SPTV2 */
#endif /* RNT_AUDIT */

#endif /* RN */

/**************************************************************************
                        RANAP
 **************************************************************************/
#ifdef RA

#undef RA
#define RA 1

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interface Coupling Options ***/

/* #define LCRAUIRPT        loosely coupled, upper interface */
/* #define LWLCRAUIRPT      light weight loosely coupled, upper interface */
/* #define LCRALISPT        loosely coupled, lower layer */
/* #define LCRAMILRA        loosely coupled, layer management */
/* #define LCRALIRUT        loosely coupled, lower layer */

/* product specific options */
/* #define RA_CN        1    core network part */
/* #define RA_UTRAN     1    radio network controller part */
/* #define RA_AUDIT     1    RANAP audit control */
/* #define RA_RUG       1    RANAP Rolling Upgrade support */
/* #define RA_FTHA      1    RANAP Fault Tolerant support */
/* #define RA_HNB       1    RANAP RUA support */
/* #define HM_HNBGW     1    RANAP RUA support */
/* #define RA_HNBGW     1    RANAP RUA support */

/**** Upper Interface flags *****/
/* #define RPT_AUDIT      1    Audit support at upper interface */
/* #define RPT_REL4       1    Upper interface compliant to 25.413 ver 400 */
/* #defined RPT_REL5      1    Upper interface compliant to 25.413 ver 540 */
/* #define RPT_REL99_3C0  1    Upper interface compliant to 25.413 ver rel99 */
/**** Lower Interface Flags  *****/
/* #define SPTV1          1    Lower Interface compliant to SCCP ITU-92 */
/* #define SPTV2          1    Lower Interface compliant to SCCP ITU-96 */

#define RA_USTA
/* #define RA_DEBUG */

/* variants, choose none or more */
/* must agree with options delivered */


/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */
/*****************************************************************
 * Must define one of RA_CN or RA_UTRAN or RA_HNB                *
 * or RA_HNBGW+HM_HNBGW+RA_UTRAN.                                *
 * If nothing defined, assumed RA_HNBGW+HM_HNBGW+RA_UTRAN        *
 ****************************************************************/
#ifndef RA_CN
#ifndef RA_UTRAN
#ifndef RA_HNB
#define RA_HNBGW     1   
#define HM_HNBGW     1   
#define RA_UTRAN      1   
#endif 
#endif 
#endif 

#ifndef SPCO
#define SPCO
#endif

#ifndef SPT2
#define SPT2
#endif

#ifndef SPTV1
#ifndef SPTV2
#define SPTV2
#endif /* SPTV2 */
#endif /* SPTV1 */

#ifdef SPTV1
#ifdef SPTV2
#undef SPTV1
#endif /* SPTV2 */
#endif /* SPTV1 */

/* upper interface */
#ifdef LCRAUIRPT 
#ifdef LCRPT
#undef LCRPT
#endif
#define LCRPT 1
#endif 

#ifdef LWLCRAUIRPT
#ifdef LWLCRPT
#undef LWLCRPT
#endif
#define LWLCRPT 1
#endif /* LWLCRAUIRPT */

#ifdef RPT_REL9
#if (defined(RA_HNB) || defined(RA_HNBGW))
#ifndef HM_REL9
#define HM_REL9
#endif /* HM_REL9 */
#endif /* RA_HNB || RA_HNBGW */
#ifndef RPT_REL8
#define RPT_REL8
#endif /* RPT_REL8 */
#endif /* RPT_REL9 */

#ifdef RPT_REL8
#ifndef RPT_REL7
#define RPT_REL7
#endif /* RPT_REL7 */
#endif /* RPT_REL8 */

#ifdef RPT_REL7
#ifndef RPT_REL6
#define RPT_REL6
#endif /*RPT_REL6*/
#ifndef RPT_REL5
#define RPT_REL5
#endif /*RPT_REL5*/
#endif /*RPT_REL7*/

#ifdef RPT_REL6
#ifndef RPT_REL5
#define RPT_REL5
#endif /*RPT_REL5*/
#endif /*RPT_REL6*/

#ifdef RPT_REL5
#ifndef RPT_REL5_5C0_LOC_REP_IE
#define RPT_REL5_5C0_LOC_REP_IE
#endif /*RPT_REL5_5C0_LOC_REP_IE*/
#ifdef RPT_REL99_3C0
#undef RPT_REL99_3C0
#endif /* RPT_REL99_3C0 */
#endif /* RPT_REL5 */

#ifdef RPT_REL5
#ifdef RPT_REL4
#undef RPT_REL4
#endif /* RPT_REL4 */
#endif /* RPT_REL5 */
#ifdef RPT_REL4_480
#ifndef RPT_REL4
#define RPT_REL4
#endif /* RPT_REL4 */
#ifdef RPT_REL99_3C0
#undef RPT_REL99_3C0
#endif /* RPT_REL99_3C0 */
#endif /* RPT_REL4_480 */

#ifdef RPT_REL4_450
#ifndef RPT_REL4
#define RPT_REL4
#endif /* RPT_REL4 */
#ifdef RPT_REL99_3C0
#undef RPT_REL99_3C0
#endif /* RPT_REL99_3C0 */
#endif /* RPT_REL4_450 */


#ifdef RPT_REL4
#ifdef RPT_REL99_3C0
#undef RPT_REL99_3C0
#endif /* RPT_REL99_3C0 */
#endif /* RPT_REL4 */

#ifdef RPT_REL5
#ifdef RPT_REL4
#undef RPT_REL4
#endif /* RPT_REL4 */
#endif /* RPT_REL5 */

#ifdef RPT_REL5
#ifndef RPT_REL5_5C0_LOC_REP_IE
#define RPT_REL5_5C0_LOC_REP_IE
#endif /*RPT_REL5_5C0_LOC_REP_IE*/
#ifdef RPT_REL99_3C0
#undef RPT_REL99_3C0
#endif /* RPT_REL99_3C0 */
#endif /* RPT_REL5 */

#ifdef RPT_REL6
#ifndef RPT_REL5
#define RPT_REL5
#endif /*RPT_REL5*/
#endif /*RPT_REL6*/

#ifdef RPT_REL7
#ifndef RPT_REL6
#define RPT_REL6
#endif /*RPT_REL6*/
#ifndef RPT_REL5
#define RPT_REL5
#endif /*RPT_REL5*/
#endif /*RPT_REL7*/

/* lower interface */
#ifdef LCRALISPT 
#ifdef LCSPT
#undef LCSPT
#endif
#define LCSPT 1
#endif 

/* layer management interface */
#ifdef LCRAMILRA
#ifdef LCLRA
#undef LCLRA
#endif
#define LCLRA 1
#endif /* LCRAMILRA */

/* Dependancy over common files flags */
#ifndef CM_PASN_ESC_SUPPORT
#define CM_PASN_ESC_SUPPORT
#endif /* CM_PASN_ESC_SUPPORT */

#ifndef CM_PASN_CLASS_IDTYPE
#define CM_PASN_CLASS_IDTYPE
#endif /* CM_PASN_ESC_SUPPORT */

#ifndef TDS_ROLL_UPGRADE_SUPPORT
#ifdef RA_RUG
#undef RA_RUG
#endif /* RA_RUG */
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

#ifndef RPT_AUDIT
#ifndef SPTV2
#ifdef RA_AUDIT
#undef RA_AUDIT
#endif /* RA_AUDIT */
#endif /* SPTV2 */
#endif /* RPT_AUDIT */

/* 1. Dependency of ZA and RA_FTHA */
#ifdef ZA
#ifndef RA_FTHA 
#define RA_FTHA   1
#endif /* RA_FTHA */
#endif /* ZA */


#endif /* RA */
/**************************************************************************
                        End of RANAP
 **************************************************************************/

#ifdef ZA       /* GPRS PSF-RANAP (FT/HA) */
/**************************************************************************
   GPRS PSF-RANAP (FT/HA) parameters
**************************************************************************/
#undef ZA
#define ZA 1

/*********************************interfaces******************************/

/* #define LCZAMILZA       loosely coupled, layer management interface */

/****************************** Interfaces Version Flags ******************/

/* Layer management interface */
/* #define LZAV1              Layer Management interface version 1.0 */
/* Peer interface */
/* #define ZAPV1              Layer Management interface version 1.0 */

/*********************************Misc Flags******************************/

/* #define ZA_USTA       enable alarms by default */
/* #define ZA_DEBUG      enable debug prints by deault (only for debugging) */

/***********************INTERNAL FLAGS (Do not modify!)********************/

#ifdef LCZAMILZA
#ifdef LCLZA
#undef LCLZA
#endif
#define LCLZA 1
#endif /* LCZAMILZA */

#endif /* ZA */


/****************************************************************************
                        H.323 Stack
****************************************************************************/

#ifdef HI       /* TCP UDP Convergence Layer (TUCL) */

/**************************************************************************
     TCP UDP Convergence Layer
**************************************************************************/

/* product version, choose one */

/* interfaces */

/* upper interface (HIT), choose none or more */

/* #define LCHIUIHIT     loosely coupled, upper layer */

/* #define LCHIUISCT     loosely coupled, upper layer */

/* management interface (LHI) , choose none or more */

/* #define LCHIMILHI     loosely coupled, layer management */

/* #define SCT_ENDP_MULTI_IPADDR  Multiple endpoint support in TUCL  per IP addr */

/* #define HI_LKSCTP  Kernel SCTP support in TUCL  */

/* #define HI_MULTI_THREADED Multithreaded support in TUCL */


#ifdef CM_INET_LARGE_FDSETSIZE
#ifdef FD_SETSIZE
#undef FD_SETSIZE
#endif
#define FD_SETSIZE 65000
#endif /* CM_INET_LARGE_FDSETSIZE */

#ifdef HI_MULTI_THREADED
#ifndef LCHIUIHIT
#define LCHIUIHIT
#endif /* LCHIUIHIT */
#ifndef LCHIUISCT
#define LCHIUISCT
#endif /* LCHIUISCT */
#ifndef LCHIMILHI
#define LCHIMILHI 
#endif /* LCHIMILHI */
#endif /* HI_MULTI_THREADED */

#ifdef LCHIUIHIT
#ifndef LCHIT
#define LCHIT
#endif /* LCHIT */
#endif /* LCHIUIHIT */

#ifdef LCHIMILHI
#ifndef LCLHI
#define LCLHI 
#endif
#endif /* LCHIMILHI */

#ifdef LCHIUISCT
#ifndef LCSCT
#define LCSCT
#endif /* LCSCT */
#endif /* LCHIUISCT */

#ifndef CM_INET2
#define CM_INET2
#endif /* CM_INET2 */

#ifdef HI_LKSCTP
#ifndef CM_LKSCTP
#define CM_LKSCTP
#endif 
#endif 

#ifdef HI_TLS
#ifndef CM_TLS
#define CM_TLS
#endif /* CM_TLS */
#endif /* HI_TLS */

#ifdef CM_AAL
#ifdef LCHIT
#ifndef LCATM
#define LCATM
#endif /* LCATM */
#endif /* LCHIT */
#endif /* CM_AAL */

#ifdef MSVER2
#define HI_CMPTBL_FLAG  /* compatibility with old system services versions */
#endif /* MSVER2 */

#endif /* HI */



#ifdef HC       /* H.323 Control */

/**************************************************************************
   H.323 Control Parameters
**************************************************************************/

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCHCUIHCT           loosely coupled, HC upper layer */

/* #define LWLCHCUIHCT         light weight loosely coupled, HC upper layer */

/* #define LCHCUICCT           loosely coupled with CC */

/* #define LWLCHCUICCT         light weight loosely coupled with CC */

/* lower interface, data link, choose none or more */

/* #define LCHCLIHIT           loosely coupled, Transport provider interface */

/* management interface, lhc */

/* #define LCHCMILHC           loosely coupled, layer management */


/******************* section not to be changed by CUSTOMERS ******************/ 
#ifdef LCHCUIHCT

#ifndef LCHCT
#define LCHCT
#endif /* LCHCT */

#endif /* LCHCUIHCT */

#ifdef LWLCHCUIHCT

#ifndef LWLCHCT
#define LWLCHCT
#endif /* LWLCHCT */

#endif /* LWLCHCUIHCT */

#if (defined(CC) || defined(LCHCUICCT) || defined(LWLCHCUICCT))

#ifndef HCCC
#define HCCC
#endif /* HCC */ 

#endif /* CC || LCHCUICCT || LWLCHCUICCT */

#ifdef LCHCLIHIT

#ifndef LCHIT
#define LCHIT
#endif /* LCHIT */

#endif /* LCHCLIHIT */


#ifdef LCHCMILHC

#ifndef LCLHC
#define LCLHC
#endif  /* LCLHC */

#endif  /* LCHCMILHC */

#ifdef CM_AAL
#if (defined(LCHCT) || defined(LCHIT))
#ifndef LCATM
#define LCATM
#endif /* LCATM */
#endif
#endif /* CM_AAL */

/* #define H323_GK        compile option for GW  functionality */
/* #define H323_GW        compile option for GK  functionality */
/* #define H323_GR        compile option for GR  functionality */
/* #define H323_V3        compile option for H.323 V3 functionality */
/* #define H323_450       compile option for H.450* functionality */
/* #define H323_ANXE      compile option for Annex E functionality */

#if (defined(H323_GW) || defined(H323_GK) || defined(H323_GR))
#define H323_RAS         /* compile option for RAS functionality */
#define H323_225         /* compile option for 225 functionality */
#define H323_245         /* compile option for 245 functionality */
#endif

#if (defined(H323_V3) || defined(H323_450) || defined(H323_ANXE) || \
     defined(H323_GR))
#ifndef HC_REL_1_2
#define HC_REL_1_2
#endif /* HC_REL_1_2 */
#endif /* defined(H323_V3) ... */

/* #define LHC_ACNT       compile option to enable accounting indications */
/* #define HC_MF_DEBUG    compile option to enable MF debugging prints */
/* #define NOERRCLASS     compile option to disable error checking */
/*
#ifdef H323_GW
#define  LHC_VIDEO_CAPS_REQD
#define  LHC_DATA_CAPS_REQD
#endif
*/

#endif /* HC */


#ifdef HG       /* H.225 Annex G */

/**************************************************************************
   H.225 Annex G Parameters
**************************************************************************/

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCHGUIHGT           loosely coupled, HG upper layer */

/* #define LWLCHGUIHGT         light weight loosely coupled, HG upper layer */

/* lower interface, data link, choose none or more */

/* #define LCHGLIHIT           loosely coupled, Transport provider interface */

/* management interface, lhg */

/* #define LCHGMILHG           loosely coupled, layer management */

/* active mode */
/* #define HG_ACTIVE_MODE      active mode */


/******************* section not to be changed by CUSTOMERS ******************/ 
#ifdef LCHGUIHGT

#ifndef LCHGT
#define LCHGT
#endif /* LCHGT */

#endif /* LCHGUIHGT */

#ifdef LWLCHGUIHGT

#ifndef LWLCHGT
#define LWLCHGT
#endif /* LWLCHGT */

#endif /* LWLCHGUIHGT */

#ifdef LCHGLIHIT

#ifndef LCHIT
#define LCHIT
#endif /* LCHIT */

#endif /* LCHGLIHIT */


#ifdef LCHGMILHG

#ifndef LCLHG
#define LCLHG
#endif  /* LCLHG */

#endif  /* LCHGMILHG */

#endif /* HC */


#ifdef HU       /* H.323 User */

/**************************************************************************
   H.323 User Parameters
**************************************************************************/

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* lower interface, HCT */

/* #define LCHULIHCT               loosely coupled */

/* #define LWLCHULIHCT             light weight loosely coupled */

#if (defined(H323_GW) || defined(H323_GK) || defined(H323_GR))
#define H323_RAS         /* compile option for RAS functionality */
#define H323_225         /* compile option for 225 functionality */
#define H323_245         /* compile option for 245 functionality */
#endif

/* lower interface, HRT */
/* #define LCHULIHRT               loosely coupled */

/******************* section not to be changed by CUSTOMERS ******************/

#ifdef LCHULIHCT

#ifndef LCHCT
#define LCHCT
#endif /* LCHCT */

#endif /* LCHULIHCT */

#ifdef LWLCHULIHCT

#ifndef LWLCHCT
#define LWLCHCT
#endif /* LWLCHCT */

#endif /* LWLCHULIHCT */

#ifdef LCHULIHRT

#ifndef LCHRT
#define LCHRT
#endif /* LCHRT */

#endif /* LCHULIHRT */

#ifdef CM_AAL
#if (defined(LCHCT) || defined(LCHRT))
#ifndef LCATM
#define LCATM
#endif /* LCATM */
#endif
#endif /* CM_AAL */

#endif /* HU */

/******************************************************************/
/* IuUP Layer                                                     */
/******************************************************************/
#ifdef LX

/******************* section to be changed by CUSTOMERS ******************/
/* These options can be enabled in the make file also */

/* #define LCLXUILXT        loosely coupled LXT Interface User */
/* #define LWLCLXUILXT      lightweight loosely coupled LXT interface */
/* #define LCLXLIHRT        loosely coupled transport layer HRT Interface */
/* #define LCLXLIGGU        loosely coupled transport layer GGU Interface */
/* #define LCLXMILLX        loosely coupled IuUP to stack manager 
                              Also enable LCSMLXMILLX under #ifdef SM */

/* #define  DEBUGP          enable to turn ON debug support */
/* #define  NO_ERRCLS       enable to compile out error class checking */

/*************** section not to be changed by CUSTOMERS ******************/
/* needed dependencies */


#if (defined(LCLXUILXT) || defined(LCXULILXT))
#ifndef LCLXT
#define LCLXT 1
#endif
#endif

#if (defined(LWLCLXUILXT) || defined(LWLCXULILXT))
#ifndef LWLCLXT
#define LWLCLXT 1
#endif
#endif


#if (defined(LCLXMILLX) || defined(LCSMLXMILLX))
#ifndef LCLLX
#define LCLLX 1
#endif
#endif


#if (defined(LCLXLIHRT) || defined(LCHRUIHRT))
#ifndef LCHRT
#define LCHRT 1
#endif
#endif

#if (defined(LCLXLIGGU) || defined(LCGTUIGGU))
#ifndef LCGGU
#define LCGGU 1
#endif
#endif

/* Define LX_RTP if HR is defined but not other way round */
#if (defined(HR) || defined(DHR))
#ifndef LX_RTP
#define LX_RTP
#endif
#endif

/* Define LX_GTP if GT is defined but not other way round */
#if (defined(GT) || defined(DGT))
#ifndef LX_GTP
#define LX_GTP
#endif
#endif

#ifdef DAL
#ifndef LX_AAL2
#define LX_AAL2
#endif
#endif

#endif /* LX */

#ifdef XU       /* IuUP User */

/**************************************************************************
   IuUP User Parameters
**************************************************************************/

/******************* section to be changed by CUSTOMERS ******************/

/*** Interfaces Coupling Options ***/

/* lower interface, LXT */

/* #define LCXULILXT               loosely coupled */

/* #define LWLCXULILXT             light weight loosely coupled */

/*************** section not to be changed by CUSTOMERS ******************/

#ifdef LCXULILXT

#ifndef LCLXT
#define LCLXT
#endif /* LCLXT */

#endif /* LCXULILXT */

#ifdef LWLCXULILXT

#ifndef LWLCLXT
#define LWLCLXT
#endif /* LWLCLXT */

#endif /* LWLCXULILXT */

#if (defined(LCLXUILXT) || defined(LCXULILXT))
#ifndef LCLXT
#define LCLXT 1
#endif
#endif

#if (defined(LWLCLXUILXT) || defined(LWLCXULILXT))
#ifndef LWLCLXT
#define LWLCLXT 1
#endif
#endif

#if (defined(LCXULIGGU) || defined(LCGTUIGGU))
#ifndef LCGGU
#define LCGGU 1
#endif
#endif

#if (defined(LCXULIHRT) || defined(LCHRUIHRT))
#ifndef LCHRT
#define LCHRT 1
#endif
#endif

#endif /* XU */


#ifdef HR       /* RTP/RTCP */

/**************************************************************************
   RTP/RTCP Parameters
**************************************************************************/

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCHRUIHRT               loosely coupled, HR upper layer */


/* lower interface, data link, choose none or more */

/* #define LCHRLIHIT               loosely coupled, HIT */
/* #define LCHRLIAAL               loosely coupled, AAL */


/* management interface, lhc */

/* #define LCHRMILHR               loosely coupled, layer management */


/*** Session Identifier Type ***/

/* #define CM_RTP_SESSID_ARRAY     HrSessionId is an array of U8 */

#ifdef CM_RTP_SESSID_ARRAY
#define CM_RTP_SESSID_SIZE 4    /* Size of the array */
#endif


/*** SDES Item Type ***/

/* #define CM_RTP_SDES_BUF         SDES items are mBufs */


/******************* section not to be changed by CUSTOMERS ******************/ 

#ifdef LCHRUIHRT

#ifndef LCHRT
#define LCHRT
#endif /* LCHRT */

#endif /* LCHRUIHRT */


#ifdef LCHRMILHR

#ifndef LCLHR
#define LCLHR
#endif /* LCLHR */

#endif /* LCHRMILHR */

#ifdef LCHRLIHIT

#ifndef LCHIT
#define LCHIT
#endif /* LCHIT */

#endif /* LCHRLIHIT */

#ifdef LCHRLIAAL

#ifndef LCAAL
#define LCAAL
#endif /* LCATM */

#endif /* LCHRLIAAL */

#ifdef CM_AAL
#if (defined(LCHRT) || defined(LCLHR) || defined(LCHIT) || defined(LCAAL))
#ifndef LCATM
#define LCATM
#endif /* LCATM */
#endif
#endif /* CM_AAL */

#endif /* HR */

/****************************************************************************
                        End of H.323 Stack
****************************************************************************/

#ifdef IQ        /* ISDN-Q.SAAL Convergence Layer */
/**************************************************************************
   ISDN-Q.SAAL Convergence Layer parameters
**************************************************************************/
#undef IQ
#define IQ 1
 
/* product version, choose one */
 
/* #define IQVER1           ISDN-Q.SAAL Convergence Layer, version 1.x */
 
/* #define L3VER2           isdn, version 2.x */
 
/* #define BDVER2           lapb/d , version 2.x */
 
/* interfaces */
 
/* upper interface, choose none or more */
 
/* #define LCIQUIDAT        loosely coupled, upper interface (dat.x) */
 
/* #define LCINLIDAT        loosely coupled, data link layer */
 
/* lower interface, choose none or more */
 
/* #define LCIQLIASD        loosely coupled, Q.SAAL */
 
/* loosely coupled IQ-Q.SAAL */
 
/* #define LCASUIASD 1       loosely coupled, data link layer */
 
#ifdef LCASUIASD
 
#ifndef LCASD
#define LCASD 1         /* define LC flag for ASD interface */
#endif
 
#ifndef LCATM
#define LCATM 1         /* define LC flag for ATM stack */
#endif
 
#endif /* LCASUIASD */
 
/* management interface, liq , choose none or more */
 
/* #define LCIQMILIQ        loosely coupled, layer management */
 
#ifdef LCIQMILIQ
 
#ifndef LCLIQ
#define LCLIQ 1        /* loosely coupled, layer manager */
#endif
 
#endif /* LCIQMILIQ */
/* layer management options */
 
#define IQ_LMINT3          /* new management interface. turning off requires
                              SMIQ_LMINT3 flag also to be turned off in #ifdef
                              SM section */
 
/* #define DAT2                new upper interface */
/* #define ASD2                new lower interface */
 
/* flags should be turned on for backward compatibility */
 
 
/* product specific options */
 
/* variants, choose none or more */
/* must agree with options delivered */
/* if applicable, must agree with q.930, mtp 3, sccp variants */
 
 
/* type, chosen automatically */
 
#ifdef IQ_LMINT3
#undef IQ_LMINT3
#define IQ_LMINT3   1
#endif /* IQ_LMINT3 */
 
#endif /* IQ */


/* switch type backwards compatibility */

/* isdn */

#ifdef ATT            /* att 4ess and 5ess, option 11 */
#define ISDN_ATT   1  /* att 4ess and 5ess, option 11 */
#endif
#ifdef NT             /* northern telecomm dms-100, option 12 */
#define ISDN_NT    1  /* northern telecomm dms-100, option 12 */
#endif
#ifdef VN             /* vn 2 and vn 3, france, option 13 */
#define ISDN_VN    1  /* vn 2 and vn 3, france, option 13 */
#endif
#ifdef ETSI           /* etsi, europe, option 14 */ 
#define ISDN_ETSI  1  /* etsi, europe, option 14 */ 
#endif
#ifdef AUS            /* AUS, australian, option 15 */ 
#define ISDN_AUS   1  /* AUS, australian, option 15 */ 
#endif
#ifdef NI1            /* national isdn 1, north america, option 16 */ 
#define ISDN_NI1   1  /* national isdn 1, north america, option 16 */ 
#endif
#ifdef NTT            /* ins net, japan, option 17 */
#define ISDN_NTT   1  /* ins net, japan, option 17 */
#endif
#ifdef INTR6          /* 1 - TR6, german, option 18 */
#define ISDN_TR6   1  /* 1 - TR6, german, option 18 */
#endif
#ifdef ATT5E          /* att 5ess, option 19 */
#define ISDN_ATT5E 1  /* att 5ess, option 19 */
#endif
#ifdef ATT4E          /* att 4ess, option 20 */
#define ISDN_ATT4E 1  /* att 4ess, option 20 */
#endif
#ifdef VN2            /* vn 2, france, option 21 */
#define ISDN_VN2   1  /* vn 2, france, option 21 */
#endif
#ifdef VN3            /* vn 3, france, option 22 */
#define ISDN_VN3   1  /* vn 3, france, option 22 */
#endif
#ifdef NTDMS250       /* northern telecom dms-250, option 23 */
#define ISDN_NTDMS250 1 /* northern telecom dms-250, option 23 */
#endif
#ifdef NTSPRINT       /* northern telecom dms-250 sprint , option 33 */
#define ISDN_NTSPRINT 1 /* northern telecom dms-250 sprint, option 33 */
#ifndef NTDMS250      /* we need to define NTDMS250 for NTSPRINT */
#define NTDMS250
#define ISDN_NTDMS250 1 /* northern telecom dms-250, option 23 */
#endif 
#endif /* NTSPRINT */
#ifdef BC303          /* bellcore tr-303, tmc and csc, option 24 */
#define ISDN_303    1 /* bellcore tr-303, tmc and csc, option 24 */
#endif
#ifdef BC303TMC       /* bellcore tr-303, tmc , option 25 */
#define ISDN_303TMC 1 /* bellcore tr-303, tmc , option 25 */
#define ISDN_BC303TMC 1 /* Bellcore TR-303 TMC */
#endif
#ifdef BC303CSC       /* bellcore tr-303, csc, option 26 */
#define ISDN_303CSC 1 /* bellcore tr-303, csc, option 26 */
#define ISDN_BC303CSC 1 /* Bellcore TR-303 CSC.  */
#endif
#ifdef Q932           /* q.932, option 27 */
#define ISDN_Q932   1 /* q.932, option 27 */
#endif
#ifdef NI2           /* national isdn 2, north america, option 28 */
#define ISDN_NI2    1 /* national isdn 2, north america, option 28 */
#endif
#ifdef QSIG           /* etsi qsig, option 29 */
#define ISDN_QSIG   1 /* etsi qsig, option 29 */
#endif
#ifdef NTNI           /* nt ni, option 31 */
#define ISDN_NTNI   1 /* nt ni, option 31 */
#endif
#ifdef NTMCI          /* nt mci, option 32 */
#define ISDN_NTMCI  1 /* nt mci, option 32 */
#endif

/* ss7 */

#ifdef BELL           /* bellcore, option 11 */
#define SS7_BELL   1  /* bellcore, option 11 */
#endif
#ifdef ANS88          /* ansi, option 12 */
#define SS7_ANS88  1  /* ansi, option 12 */
#endif
#ifdef ANS92          /* ansi, option 12 */
#define SS7_ANS92  1  /* ansi, option 12 */
#endif
#ifdef ANS95          /* ansi, option 18 */
#define SS7_ANS95  1  /* ansi, option 18 */
#endif
#ifdef ANS96          /* ansi, option 12 */
#define SS7_ANS96  1  /* ansi, option 12 */
#endif
#ifdef TTC            /* ttc, japan, option 13 */
#define SS7_TTC    1  /* ttc, japan, option 13 */
#endif
#ifdef NTT            /* ntt, japan, option 25 */
#define SS7_NTT    1  /* ntt, japan, option 25 */
#endif
#ifdef CHINA          /* china, option 15 */
#define SS7_CHINA  1  /* china, option 15 */
#endif
#ifdef SINGTEL        /* singapore telecom, option 19 */
#define SS7_SINGTEL 1 /* singapore telecom, option 19 */
#endif
#ifdef BICI           /* bici, option 17 */
#define SS7_BICI   1  /* bici, option 17 */
#endif
#ifdef Q767           /* q767, option 17  */
#define SS7_Q767    1 /* q767, option 17  */
#endif
#ifdef Q767IT         /* q767 italy, option 20 */
#define SS7_Q767IT  1 /* q767 italy, option 20 */
#endif
#ifdef ETSI_SS7       /* ETSI, option 22 */
#define SS7_ETSI   1  /* ETSI, option 22 */
#endif
#ifdef GT_FTZ         /* German Telecom, option 23 */
#define SS7_FTZ     1 /* German Telecom, option 23 */
#endif
#ifdef RUSSIA_SS7       /* RUSSIA, option 24 */
#define SS7_RUSSIA   1  /* RUSSIA, option 24 */
#endif
#ifdef ITU97          /* itu97, option 27 */
#define SS7_ITU97  1  /* itu97, option 27 */
#endif
#ifdef ETSIV3          /* ETSI version 3, option 28 */
#define SS7_ETSIV3  1  /* ETSI version 3, option 28 */
#endif

#ifdef BI
#define ATM_BISUP  1  /* b-isup */
#endif
#ifdef MSC             /* MAP Options */
#define MAP_MSC   1    /* MAP Options  */
#define IA_MSC    1    /* IS MAP Options  */
#else
#define MAP_MSC   0
#define IA_MSC    0    /* IS MAP Options  */
#endif
#ifdef VLR             /* MAP Options */
#define MAP_VLR   1    /* MAP Options  */
#define IA_VLR    1    /* IS MAP Options  */
#else
#define MAP_VLR   0
#define IA_VLR    0    /* IS MAP Options  */
#endif
#ifdef HLR             /* MAP Options */
#define MAP_HLR   1    /* MAP Options  */
#define IA_HLR    1    /* IS MAP Options  */
#else
#define MAP_HLR   0
#define IA_HLR    0    /* IS MAP Options  */
#endif
#ifdef SCP
#define IA_SCP 1   /* IS MAP options */
#else
#define IA_SCP 0
#endif
#ifdef GSN             /* MAP Options */
#define MAP_GSN   1    /* MAP Options  */
#else
#define MAP_GSN   0
#endif
#ifdef REL99             /* MAP Options */
#define MAP_REL99   1    /* MAP Options  */
#else
#define MAP_REL99   0
#endif

#ifdef REL98             /* MAP Options */
#define MAP_REL98   1    /* MAP Options  */
#else
#define MAP_REL98   0
#endif

#ifdef MLC             /* MAP Options */
#define MAP_MLC   1    /* MAP Options  */
#else
#define MAP_MLC   0
#endif

/* dat layer */

#ifdef SDVER2         /* new mtp level 2 */
#define DATVER2       /* new layer2 */
#endif

/* mac layer */

#ifdef SEVER2         /* new sec */
#define MACVER2       /* new mac layer */
#endif

#ifdef QIVER2         /* new quicc */
#define MACVER2       /* new mac layer */
#endif

#ifdef PQVER2        /* new PowerQUICC */
#define MACVER2      /* new MAC layer */
#endif               /* PQVER2 */

/* INAP */

#ifdef AIN_SCP       /* Bellcore AINGR : SSP-SCP Interface */
#define SS7_AIN_SCP 1
#define SS7_AIN     1
#endif

#ifdef AIN_IP        /* Bellcore AINGR : SSP-IP Interface */
#define SS7_AIN_IP  1
#define SS7_AIN     1
#endif

#ifdef ITU_SS7      /* ITU */
#define SS7_ITU     1
#endif

#ifdef SGSN
#define GPRS_ETSI_SGSN 1  /* ETSI SGSN */
#endif

#ifdef GGSN
#define GPRS_ETSI_GGSN 1  /* ETSI GGSN */
#endif

#ifdef BSS
#define GPRS_ETSI_BSS  1  /* ETSI BSS */
#endif

#ifdef MST
#define GPRS_ETSI_MS   1  /* ETSI MS */
#endif

#ifdef GTPGNGP
#define GTP_GNGP       1  /* GNGP interface */
#endif

#ifdef GTPGA
#define GTP_GA         1  /* GA(Charging) interface */
#endif

#ifdef GTPIU
#define GTP_IU         1  /* 3G(IU) interface between SGSN and RNC */
#endif


/****************************************************************************
                         MGCP Stack
****************************************************************************/
#ifdef MG

/*#define GCP_MGCP */                  /* MGCP */
/*#define GCP_MGCO */                  /* MEGACO */

/*#define GCP_MG  */                   /* Gateway Side */
/*#define GCP_MGC */                   /* Gateway Controller Side */

/* 
 * Feature Support Flags  - MGCP Only
 */

/*#define GCP_2705BIS */               /* Support for RFC 2705 BIS */
/*#define GCP_MGCP_PARSE_DIG_MAP */    /* Pass Digit Map as String for MGCP */

/* 
 * Feature Support Flags  - MEGACO Only
 */

/*#define GCP_MGCO_PARSE_DIG_MAP */    /* Pass Digit Map as String for Megaco */
/* #define GCP_USE_AH */               /* Use AH hdr / Not */
/* #define GCP_MGCO_SHORT_TOKEN  */    /* Use Short Tokens while Transmitting */


/* 
 * Feature Support Flags  - Common to MGCP/Megaco
 */


/*#define GCP_USER_RETX_CNTRL */       /* User controlled retransmission
                                        * behaviour */

/*#define CM_ABNF_V_1_2    */          /* Common ABNF Library */
/*#define CM_ABNF_DBG      */          /* Common ABNF Library Debug */
/*#define CM_ABNF_DBGP     */          /* Common ABNF Library Debug Printing */
/*#define CM_ABNF_MT_LIB   */          /* Multi-threaded ABNF Library for SMP */

/*#define CM_SDP_V_3       */          /* Latest SDP Version */
/*#define CM_SDP_ATM_SUPPORT */        /* Support for SDP ATM */
/*#define CM_SDP_OPAQUE    */          /* Pass SDP as string to User */

/*#define IPV6_SUPPORTED   */          /* IPV6 Support */

/*#define CM_DNS_LIB       */          /* Use Common DNS Library */
/*#define CM_AAAA          */          /* IPV6 Support - Quad A DNS Records */


/* Interface Flags */

/* #define LCMGUIMGT        loosely coupled MGT Interface User */
/* #define LWLCMGUIMGT      lightweight loosely coupled MGT interface */
/* #define LCMGLIHIT        loosely coupled transport layer Interface */
/* #define LCMGMILMG        loosely coupled MGCP to stack manager */


/* Interface flags chosen automatically */

#ifndef MGT_MGCO_V2
#define MGT_MGCO_V2
#endif /* MGT_MGCO_V2 */

/* Loosely Coupled Upper Interface */
#ifdef LCMGUIMGT

#ifndef LCMGT
#define LCMGT              /* Loose coupling for MGT Interface */
#endif /* LCMGT */

#ifndef LCCMSDP
#define LCCMSDP            /* SDP Information at MGT Interface */
#endif /* LCCMSDP */

#endif /* LCMGUIMGT */

#ifdef LWLCMGUIMGT

#ifndef LWLCMGT
#define LWLCMGT              /* light weight Loose coupling for MGT Interface */
#endif /* LWLCMGT */

#ifndef LCCMSDP
#define LCCMSDP            /* SDP Information at MGT Interface */
#endif /* LCCMSDP */

#endif /* LWLCMGUIMGT */

/* Loosely Coupled HIT Interface */
#ifdef LCMGLIHIT

#ifndef LCHIT
#define LCHIT              /* Loose coupling for HIT Interface */ 
#endif /* LCHIT */

#endif /* LCMGLIHIT */

/* Loosely Coupled Layer Manager Interface */
#ifdef LCMGMILMG

#ifndef LCLMG
#define LCLMG
#endif /* LCLMG */

#endif /* LCMGMILMG */

       /******************************************************
                          RUG Specific Flags 
       ******************************************************/
       
/* #define MG_RUG  */          /* product MG rolling upgrade enabled */
#ifdef MG_RUG
#define MGT1                  /* base release version of MGT intf */
#define LMG1                  /* base release version of LMG intf */
#define MGT2                   /* new upper interface */
#endif /* MG_RUG */

#ifdef MG_RUG

#ifndef TDS_ROLL_UPGRADE_SUPPORT
#define TDS_ROLL_UPGRADE_SUPPORT
#endif /* ifndef TDS_ROLL_UPGRADE_SUPPORT */

#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#define TDS_CORE2
#endif /* ifndef TDS_CORE2 */
#endif /* ifndef TDS_ROLL_UPGRADE_SUPPORT */

#endif /* MG_RUG */

 

/**************** Define dependency checks (DO NOT CHANGE!!) *****************/

/*
 * Feature Specific Dependency Checks
 */

#ifdef GCP_MGCO_PARSE_DIG_MAP 
#ifndef GCP_MGCO
#error "GCP_MGCO_PARSE_DIG_MAP is a megaco feature. Enable GCP_MGCO"
#endif
#endif /* GCP_MGCO_PARSE_DIG_MAP  */

#ifdef GCP_USE_AH
#ifndef GCP_MGCO
#error "GCP_USE_AH is a megaco feature. Enable GCP_MGCO"
#endif
#endif /* GCP_USE_AH */

#ifdef GCP_MGCO_SHORT_TOKEN 
#ifndef GCP_MGCO
#error "GCP_MGCO_SHORT_TOKEN is a megaco feature. Enable GCP_MGCO"
#endif
#endif /* GCP_MGCO_SHORT_TOKEN  */


#ifdef GCP_MGCP_PARSE_DIG_MAP

#ifndef GCP_MGCP
#error "MGCP Digit Map Parse is MGCP Feature. Enable GCP_MGCP."
#endif 

#endif /* GCP_MGCP_PARSE_DIG_MAP */


#ifdef GCP_2705BIS

#ifndef GCP_MGCP
#error "2705BIS is MGCP Feature. Enable GCP_MGCP"
#endif

#endif /* GCP_2705BIS */

#ifdef IPV6_SUPPORTED

#ifndef CM_AAAA
#define CM_AAAA
#endif 

#endif /* IPV6_SUPPORTED */


/*
 *   Either CM_SDP_OPAQUE flag OR the rest of the SDP flags
 *   should be defined i.e. these flags are mutually exclusive
 */
#ifdef    CM_SDP_OPAQUE

#ifdef    CM_SDP_V_2
#undef    CM_SDP_V_2
#endif /* CM_SDP_V_2 */

#ifdef    CM_SDP_V_3
#undef    CM_SDP_V_3
#endif /* CM_SDP_V_3 */

#ifdef    CM_SDP_ATM_SUPPORT
#undef    CM_SDP_ATM_SUPPORT
#endif /* CM_SDP_ATM_SUPPORT */

#endif /* CM_SDP_OPAQUE */


#ifdef CM_SDP_V_3
#ifndef CM_SDP_V_2
#define CM_SDP_V_2
#endif /* CM_SDP_V_2 */
#endif /* CM_SDP_V_3 */

#ifndef CM_INET2
#define CM_INET2
#endif /* CM_INET2 */

#ifndef HI_REL_1_3
#define HI_REL_1_3
#endif /* HI_REL_1_3 */

#ifndef HI_REL_1_4
#define HI_REL_1_4
#endif /* HI_REL_1_4 */

/* MEGACO specific flags */
#ifdef GCP_MGCO

/*
 * Packages Added in GCP 1.2 Release
 */

/* #define GCP_PKG_MGCO_GENERIC */     /* Included Generic(g) package */
/* #define GCP_PKG_MGCO_ROOT */        /* Include root package */
/* #define GCP_PKG_MGCO_TONEGEN */     /* Include tonegen package */
/* #define GCP_PKG_MGCO_TONEDET */     /* Include tonedet package */
/* #define GCP_PKG_MGCO_DTMFGEN */     /* Include dtmfgen package */
/* #define GCP_PKG_MGCO_DTMFDET */     /* Include dtmfdet package */
/* #define GCP_PKG_MGCO_CPGEN */       /* Include cpgen(cg) package */
/* #define GCP_PKG_MGCO_CPDET */       /* Include cpdet(cd) package */
/* #define GCP_PKG_MGCO_ANALOG */      /* Include analog(al) package */
/* #define GCP_PKG_MGCO_CONT */        /* Include continuity(ct) package */
/* #define GCP_PKG_MGCO_NETWORK */     /* Include network(nt) package */
/* #define GCP_PKG_MGCO_RTP */         /* Include RTP(rtp) package */
/* #define GCP_PKG_MGCO_TDMC */        /* Include TDM circuit(tdmc) package */
/* #define GCP_PKG_MGCO_NAS_SUPPORT */ /* Include NAS package */
/* #define GCP_MGCO_SHORT_TOKEN */     /* Use short tokens for encoding */

/*
 * Packaged added in GCP 1.3 Release
 */

/* #define GCP_PKG_MGCO_ANCILLARYINPUT */  /* Ancillary Input Package */
/* #define GCP_PKG_MGCO_CALLTYPDISCR   */  /* Call Type Discrimnator Package */
/* #define GCP_PKG_MGCO_DISPLAY        */  /* Display Package */
/* #define GCP_PKG_MGCO_FAX            */  /* Fax Package */
/* #define GCP_PKG_MGCO_FAXTONEDET     */  /* Fax Tone Detection package */
/* #define GCP_PKG_MGCO_FUNCKEY        */  /* Function Key Package */
/* #define GCP_PKG_MGCO_GENANNC        */  /* Generic Announcement Package */
/* #define GCP_PKG_MGCO_INDICATOR      */  /* Indicator package */
/* #define GCP_PKG_MGCO_IPFAX          */  /* IP Fax Package */
/* #define GCP_PKG_MGCO_KEY            */  /* Key Package */
/* #define GCP_PKG_MGCO_KEYPAD         */  /* Key Pad */
/* #define GCP_PKG_MGCO_LABELKEY       */  /* Label Key */
/* #define GCP_PKG_MGCO_SOFTKEY        */  /* Soft Key */
/* #define GCP_PKG_MGCO_TXTCNVR        */  /* Text Conversation */
/* #define GCP_PKG_MGCO_TXTTELPHONE    */  /* Text Telephone */
/* #define GCP_PKG_MGCO_ADVAUSRVRBASE  */  /* Advanced Audio Server Package */
/* #define GCP_PKG_MGCO_AASDIGCOLLECT  */  /* Advanced Digit Collection Pkg */
/* #define GCP_PKG_MGCO_AASRECODING    */  /* Advanced Audio Server Recording Pkg */
/* #define GCP_PKG_MGCO_ADVAUSRVRSEGMNGMT*/  /* Advanced Audion Server Segment Mgmt */

/*
 * Packages added in GCP 1.4 Release
 */

/* #define GCP_PKG_MGCO_GEN_BRR_CON    */  /* Generic Bearer Connection Package */
/* #define GCP_PKG_MGCO_TRI_GUP        */  /* 3GUP User Plane Package */
/* #define GCP_PKG_MGCO_INACTTIMER     */  /* Inactivity Timer Package */
/* #define GCP_PKG_MGCO_BNCT           */  /* Bearer Network Connection Cut Through Package */
/* #define GCP_PKG_MGCO_TRI_GCTM       */  /* Cellular Text Telephone Modem Text Transport Package */
/* #define GCP_PKG_MGCO_TRI_GMLC       */  /* Modification of Link characteristics Bearer Capability Package */
/* #define GCP_PKG_MGCO_OSES           */  /* Operator Services and Emergency Services Package */
/* #define GCP_PKG_MGCO_QT_TM_LTC      */  /* Quiet Termination Line Test Component Package */
/* #define GCP_PKG_MGCO_RBS            */  /* Robbed Bit Signaling Package */
/* #define GCP_PKG_MGCO_BCAS           */  /* Basic CAS Package */
/* #define GCP_PKG_MGCO_RI             */  /* Reuse Idle Package */
/* #define GCP_PKG_MGCO_TRI_GCSD       */  /* Circuit Switched Data Package */
/* #define GCP_PKG_MGCO_CHP            */  /* Media Gateway Resource Congestion Handling Package */
/* #define GCP_PKG_MGCO_LP_BK_LTR      */  /* Loop back Line Test Response Package */
/* #define GCP_PKG_MGCO_ITU_LT_DIST    */  /* ITU-T 2100Hz Disable Tone Line Test Package */
/* #define GCP_PKG_MGCO_ITU_LT_DSEC    */  /* ITU-T 2100Hz Disable echo canceller tone line test Package */
/* #define GCP_PKG_MGCO_ITU_LT_NTT     */  /* ITU-T Noise test tone line test Package */
/* #define GCP_PKG_MGCO_ITU_LT_DPRT    */  /* ITU-T Digital pseudo random test tone line test Package */
/* #define GCP_PKG_MGCO_ANSI_LT_TR     */  /* ANSI Test responder line test Package */
/* #define GCP_PKG_MGCO_ANSI_LT_DTS    */  /* ANSI Digital test signal line test Package */
/* #define GCP_PKG_MGCO_ANSI_IN_LTR    */  /* ANSI Inverting loopback line test response Package */
/* #define GCP_PKG_MGCO_ITU_LT_404     */  /* ITU-T 404Hz Line Test Package */
/* #define GCP_PKG_MGCO_ITU_LT_816     */  /* ITU-T 816Hz Line Test Package */
/* #define GCP_PKG_MGCO_ITU_LT_1020    */  /* ITU-T 1020Hz Line Test Package */
/* #define GCP_PKG_MGCO_ITU_LT_2804    */  /* ITU-T 2804Hz Tone Line Test Package */
/* #define GCP_PKG_MGCO_ANSI_LT_1004   */  /* ANSI 1004 Hz Test tone line test Package */
/* #define GCP_PKG_MGCO_ANSI_LT_2225   */  /* ANSI 2225 Hz Test progress tone line test Package */
/* #define GCP_PKG_MGCO_TRI_GTFO       */  /* TFO Package */
/* #define GCP_PKG_MGCO_ITU_LT_ATME2   */  /* ITU-T ATME No 2 test line response Package */
/* #define GCP_PKG_MGCO_TRI_GIPTRA     */  /* IP Transport Package */
/* #define GCP_PKG_MGCO_BRR_CTL_TN     */  /* Bearer Control Tunneling Package */
/* #define GCP_PKG_MGCO_BRR_CHAR       */  /* Bearer Characteristic Package */
/* #define GCP_PKG_MGCO_BSNS_TNGN      */  /* Business Tone Generation Package */
/* #define GCP_PKG_MGCO_XD_SRV_TNGN    */  /* Expanded Services Tone Generation Package */
/* #define GCP_PKG_MGCO_BSC_SRV_TN     */  /* Basic Services Tone Generator Package */
/* #define GCP_PKG_MGCO_OSEXT          */  /* Operator Service and Extension Package */
/* #define GCP_PKG_MGCO_XD_CALPG_TNGN  */  /* Expanded Call Progress Tones Generator Package */
/* #define GCP_PKG_MGCO_TRIG_FLEX_TN   */  /* Flexible Tone Generator Package */
/* #define GCP_PKG_MGCO_TRIG_XD_CALPG_TNGN */  /* 3G Expanded Call Progress Tones Generator Package */
/* #define GCP_PKG_MGCO_BSC_CAL_TN     */  /* Basic Call Progress Tones Generator with Directionality Package */
/* #define GCP_PKG_MGCO_BCASADDR       */  /* Basic CAS Addressing Package */
/* #define GCP_PKG_MGCO_INT_TNGN       */  /* Intrusion Tone Generation Package */

/*
 * [TEL2]: Packages added in GCP 1.5 Release
 */

 /* #define GCP_PKG_MGCO_OCP            */  /* Media Gateway Overload Control package */ 
 /* #define GCP_PKG_MGCO_FLR_CTL        */  /* Floor Control package */
 /* #define GCP_PKG_MGCO_IND_VIEW       */  /* Indication of being viewed package */
 /* #define GCP_PKG_MGCO_VOL_CTL        */  /* Volume Control package */
 /* #define GCP_PKG_MGCO_VOL_DET        */  /* Volume Detection package */
 /* #define GCP_PKG_MGCO_VOL_LEV_MIX    */  /* Volume Level Mixing package */
 /* #define GCP_PKG_MGCO_VOI_ACT_VID_SW */  /* Voice Activated Video Switch package */
 /* #define GCP_PKG_MGCO_LEC_VID_MOD    */  /* Lecture Video Mode package */
 /* #define GCP_PKG_MGCO_CON_VID_SRC    */  /* Contributing Video Source package */
 /* #define GCP_PKG_MGCO_PROF           */  /* Profile package */
 /* #define GCP_PKG_MGCO_SEM_PER        */  /* Semi-permanent connection package */
 /* #define GCP_PKG_MGCO_VID_WIN        */  /* Video Window package */
 /* #define GCP_PKG_MGCO_TIL_WIN        */  /* Tiled Window package */
 /* #define GCP_PKG_MGCO_EN_ALERT       */  /* Enhanced Alerting package */
 /* #define GCP_PKG_MGCO_SH_RISK        */  /* Shared Risk Group package */
 /* #define GCP_PKG_MGCO_MIX_VOL_CTL    */  /* Mixing Volume Level Control package */
 /* #define GCP_PKG_MGCO_CAS_BLK        */  /* CAS Blocking package */
 /* #define GCP_PKG_MGCO_CONF_TN        */  /* Conferencing Tones Generation package */
 /* #define GCP_PKG_MGCO_TEST           */  /* Diagnostic Tones Generation package */
 /* #define GCP_PKG_MGCO_CARR_TN        */  /* Carrier Tones Generation package */
 /* #define GCP_PKG_MGCO_AN_DISP        */  /* Analog Display Signalling package */
 /* #define GCP_PKG_MGCO_EXT_ALG        */  /* Extended Analog Line Supervision package */
 /* #define GCP_PKG_MGCO_AUT_MET        */  /* Automatic Metering package */
 /* #define GCP_PKG_MGCO_H_324          */  /* H.324 package */
 /* #define GCP_PKG_MGCO_H_245_COM      */  /* H.245 Command package */
 /* #define GCP_PKG_MGCO_H_245_IND      */  /* H.245 Indication package */
 /* #define GCP_PKG_MGCO_H245_COM_EXT   */  /* Extended H.245 Command package */
 /* #define GCP_PKG_MGCO_H245_IND_EXT   */  /* Extended H.245 Indication package */
 /* #define GCP_PKG_MGCO_QTY_ALT        */  /* Quality Alert Ceasing package */
 /* #define GCP_PKG_MGCO_H324_EXT       */  /* Extended H.324 package */
 /* #define GCP_PKG_MGCO_AD_JIT_BUFF    */  /* Adaptive Jitter Buffer package */
 /* #define GCP_PKG_MGCO_ICAS           */  /* International CAS package */
 /* #define GCP_PKG_MGCO_MFQ_TN_GEN     */  /* Multi-Frequency Tone Generation package */
 /* #define GCP_PKG_MGCO_MFQ_TN_DET     */  /* Multi-Frequency Tone Detection package */
 /* #define GCP_PKG_MGCO_EXT_DTMF       */  /* Extended DTMF Detection package */
 /* #define GCP_PKG_MGCO_ENH_DTMF       */  /* Enhanced DTMF Detection package */

/* [TEL2]: To enable default including of base pkgs for extended packages */

#if (defined (GCP_PKG_MGCO_EXT_ALG))
#ifndef GCP_PKG_MGCO_ANALOG
#define GCP_PKG_MGCO_ANALOG
#endif /* GCP_PKG_MGCO_ANALOG */
#endif 

#if (defined (GCP_PKG_MGCO_AN_DISP))
#ifndef GCP_PKG_MGCO_EN_ALERT
#define GCP_PKG_MGCO_EN_ALERT
#endif /* GCP_PKG_MGCO_EN_ALERT */
#endif 

#if (defined (GCP_PKG_MGCO_ENH_DTMF))
#ifndef GCP_PKG_MGCO_EXT_DTMF
#define GCP_PKG_MGCO_EXT_DTMF
#endif /* GCP_PKG_MGCO_EXT_DTMF */
#endif 

#if (defined (GCP_PKG_MGCO_EXT_DTMF))
#ifndef GCP_PKG_MGCO_DTMFDET
#define GCP_PKG_MGCO_DTMFDET
#endif /* GCP_PKG_MGCO_DTMFDET */
#endif 

#if (defined (GCP_PKG_MGCO_H245_IND_EXT))
#ifndef GCP_PKG_MGCO_H_245_IND
#define GCP_PKG_MGCO_H_245_IND
#endif /* GCP_PKG_MGCO_H_245_IND */
#endif 

#if (defined (GCP_PKG_MGCO_H245_COM_EXT))
#ifndef GCP_PKG_MGCO_H_245_COM
#define GCP_PKG_MGCO_H_245_COM
#endif /* GCP_PKG_MGCO_H_245_COM */
#endif 

#if (defined (GCP_PKG_MGCO_H324_EXT))
#ifndef GCP_PKG_MGCO_H_324
#define GCP_PKG_MGCO_H_324
#endif /* GCP_PKG_MGCO_H_324 */
#endif 

#if (defined (GCP_PKG_MGCO_TRIG_FLEX_TN))
#ifndef GCP_PKG_MGCO_TRIG_XD_CALPG_TNGN
#define GCP_PKG_MGCO_TRIG_XD_CALPG_TNGN
#endif /* GCP_PKG_MGCO_TRIG_XD_CALPG_TNGN */
#endif 

#if (defined (GCP_PKG_MGCO_TRIG_XD_CALPG_TNGN))
#ifndef GCP_PKG_MGCO_XD_CALPG_TNGN
#define GCP_PKG_MGCO_XD_CALPG_TNGN
#endif /* GCP_PKG_MGCO_XD_CALPG_TNGN */
#endif 

/* For Packages extending Operator Services Package */
#if (defined (GCP_PKG_MGCO_OSEXT))
#ifndef GCP_PKG_MGCO_OSES
#define GCP_PKG_MGCO_OSES
#endif /* GCP_PKG_MGCO_OSES */
#endif 

/* For Packages extending BCAS Package */
#if (defined (GCP_PKG_MGCO_BCASADDR) || defined (GCP_PKG_MGCO_ICAS))
#ifndef GCP_PKG_MGCO_BCAS
#define GCP_PKG_MGCO_BCAS
#endif /* GCP_PKG_MGCO_BCAS */
#endif 

/* For Packages extending Advanced Audio Server Base Package */
#if (defined (GCP_PKG_MGCO_AASDIGCOLLECT) || defined (GCP_PKG_MGCO_AASRECODING))
#ifndef GCP_PKG_MGCO_ADVAUSRVRBASE
#define GCP_PKG_MGCO_ADVAUSRVRBASE
#endif /* GCP_PKG_MGCO_ADVAUSRVRBASE */
#endif 

/* For Packages extending LabelKey Package */
#if (defined (GCP_PKG_MGCO_FUNCKEY) || defined (GCP_PKG_MGCO_SOFTKEY))
#ifndef GCP_PKG_MGCO_LABELKEY
#define GCP_PKG_MGCO_LABELKEY
#endif /* GCP_PKG_MGCO_LABELKEY */
#endif 

/* For Packages extending Key Package */
#if (defined (GCP_PKG_MGCO_KEYPAD) || defined (GCP_PKG_MGCO_LABELKEY))
#ifndef GCP_PKG_MGCO_KEY
#define GCP_PKG_MGCO_KEY
#endif /* GCP_PKG_MGCO_KEY */
#endif 

/* For Packages extending Tonegen Package */
#if (defined (GCP_PKG_MGCO_DTMFGEN) || defined (GCP_PKG_MGCO_CPGEN) || \
     defined (GCP_PKG_MGCO_FAXTONEDET) || defined (GCP_PKG_MGCO_BSC_CAL_TN) || \
     defined (GCP_PKG_MGCO_BSC_SRV_TN) || defined (GCP_PKG_MGCO_BSNS_TNGN) || \
     defined (GCP_PKG_MGCO_XD_CALPG_TNGN) || defined (GCP_PKG_MGCO_XD_SRV_TNGN) || \
     defined (GCP_PKG_MGCO_INT_TNGN) || defined (GCP_PKG_MGCO_MFQ_TN_GEN) || \
     defined (GCP_PKG_MGCO_CONF_TN) || defined (GCP_PKG_MGCO_TEST) || \
     defined (GCP_PKG_MGCO_CARR_TN))
#ifndef GCP_PKG_MGCO_TONEGEN
#define GCP_PKG_MGCO_TONEGEN
#endif /* GCP_PKG_MGCO_TONEGEN */
#endif 

/* For Packages extending Tonedet Package */
#if (defined (GCP_PKG_MGCO_DTMFDET) || defined (GCP_PKG_MGCO_CPDET) || \
     defined (GCP_PKG_MGCO_FAXTONEDET) || defined (GCP_PKG_MGCO_MFQ_TN_DET))
#ifndef GCP_PKG_MGCO_TONEDET
#define GCP_PKG_MGCO_TONEDET
#endif /* GCP_PKG_MGCO_TONEDET */
#endif 

/* For Packages extending Network Package */
#if (defined (GCP_PKG_MGCO_RTP) || defined (GCP_PKG_MGCO_TDMC) || \
     defined (GCP_PKG_MGCO_QTY_ALT) || defined (GCP_PKG_MGCO_AD_JIT_BUFF))
#ifndef GCP_PKG_MGCO_NETWORK
#define GCP_PKG_MGCO_NETWORK
#endif /* GCP_PKG_MGCO_NETWORK */
#endif 

#endif /* GCP_MGCO */

/*
 * MGCP Package Flags - Define these for deeper decoded Packages
 */
#ifdef GCP_MGCP

/* #define GCP_PKG_MGCP_GENERIC_MEDIA      */   /* Generic Media */
/* #define GCP_PKG_MGCP_ATM                */   /* MGCP ATM */
/* #define GCP_PKG_MGCP_DTMF               */   /* DTMF */
/* #define GCP_PKG_MGCP_TRUNK              */   /* Trunk */
/* #define GCP_PKG_MGCP_LINE               */   /* Line */
/* #define GCP_PKG_MGCP_HANDSET_EMUL       */   /* Hanset Emulation */
/* #define GCP_PKG_MGCP_RTP                */   /* RTP */
/* #define GCP_PKG_MGCP_ANNC_SERVER        */   /* Announcement Server */
/* #define GCP_PKG_MGCP_SCRIPT             */   /* Script */
/* #define GCP_PKG_MGCP_SUPPL_SRVS_TONE    */   /* Supplementary Service Tone */
/* #define GCP_PKG_MGCP_CNTRY_SPEC_TONE    */   /* Country Specific Tone */
/* #define GCP_PKG_MGCP_SIGLST             */   /* Signal List */
/* #define GCP_PKG_MGCP_DTMF_DLPL_BASPBX   */   /* Dial Pulse Basic PBX */
/* #define GCP_PKG_MGCP_FXO_LSG_ANALOG     */   
/* #define GCP_PKG_MGCP_DTMF_DIAL_PULSE    */   /* DTMF Dial Pulse */
/* #define GCP_PKG_MGCP_NAM_MF_GRP_DE      */
/* #define GCP_PKG_MGCP_MF_WINKSTART       */   /* Multi Frequency Winkstart */
/* #define GCP_PKG_MGCP_RES_RESERV         */   /* Resource Reservation */
/* #define GCP_PKG_MGCP_MF                 */   /* Multi Frequency */
/* #define GCP_PKG_MGCP_BASIC_NAS          */   /* Basic NAS */
/* #define GCP_PKG_MGCP_ISUP_TRUNK         */   /* ISUP Trunk */
/* #define GCP_PKG_MGCP_MF_TERM_PROTO      */
/* #define GCP_PKG_MGCP_NAS_DATAOUT        */   /* NAS Dataout */
/* #define GCP_PKG_MGCP_FAX                */   /* MGCP Fax */
/* #define GCP_PKG_MGCP_FGD_OP_SR_SIGOUT   */
/* #define GCP_PKG_MGCP_ADSI               */   /* ADSI */

#endif /* GCP_MGCP */


#ifdef   GCP_PROV_SCTP

/* GCP SCTP support is provided only for MEGACO */
#ifndef   GCP_MGCO
#define   GCP_MGCO
#endif /* GCP_MGCO */


#ifndef    SCT2
#define    SCT2
#endif /* !SCT2 */

#ifndef    GCP_ENDP_SRCIPADDR_CFG
#define    GCP_ENDP_SRCIPADDR_CFG
#endif /* !GCP_ENDP_SRCIPADDR_CFG */

#ifdef SB

#ifndef   SB_CHECKSUM
#define   SB_CHECKSUM
#endif /* SB_CHECKSUM */

#ifndef    SCT2
#define    SCT2
#endif /* !SCT2 */

#ifndef    SCT3
#define    SCT3
#endif /* !SCT3 */

#ifndef    SCT4
#define    SCT4
#endif /* !SCT4 */

#endif /* If SB */
#endif /* GCP_PROV_SCTP */

#ifdef   GCP_PROV_MTP3

/* GCP MTP3 support is provided only for MEGACO */
#ifndef   GCP_MGCO
#define   GCP_MGCO
#endif /* GCP_MGCO */

#ifndef   SM_SS7
#define   SM_SS7
#endif /* SM_SS7 */

#ifndef    SNT2
#define    SNT2
#endif /* !SNT2 */

#ifdef L4
#undef L4   
#endif /* L4 */

#endif   /* GCP_PROV_MTP3 */

#ifdef GCP_CH
 
#ifndef GCP_MGCO
#define GCP_MGCO
#endif /*GCP_MGCO */

#endif /* GCP_CH */
 

#ifdef GCP_ASN

#ifndef MG_WRAP_ASN1_ENCDEC
#define MG_WRAP_ASN1_ENCDEC  
#endif /*MG_WRAP_ASN1_ENCDEC */

#ifndef GCP_PKG_MGCO_GENERIC
#define GCP_PKG_MGCO_GENERIC
#endif /*DGCP_PKG_MGCO_GENERIC*/

#endif /*GCP_ASN*/
  

#ifdef MG_ASN_TEST

#ifndef GCP_ASN
#define GCP_ASN
#endif

#ifdef MG_ASN_DBG

#ifndef CM_ABNF_DBG
#define CM_ABNF_DBG
#endif /*CM_ABNF_DBG */
#endif /*MG_ASN_DBG*/  

#endif /*MG_ASN_TEST*/

#ifdef GCP_MGCP
#ifndef GCP_MGCO
   
#ifdef GCP_ASN
#undef GCP_ASN
#endif /* GCP_ASN */

#ifdef GCP_CH
#undef GCP_CH
#endif /* GCP_CH */

#ifdef GCP_VER_2_1
#undef GCP_VER_2_1
#endif /* GCP_VER_2_1 */

#ifdef GCP_NTFY_AVL
#undef GCP_NTFY_AVL
#endif /* GCP_NTFY_AVL */

#endif /*not def GCP_MGCO */
#endif /*GCP_MGCP */      

#ifdef GCP_NTFY_AVL

#ifndef GCP_MGCO
#define GCP_MGCO
#endif /* !GCP_MGCO */

#ifndef GCP_VER_2_1
#define GCP_VER_2_1
#endif /* !GCP_VER_2_1 */

#endif /* !GCP_NTFY_AVL */


#ifdef GCP_VER_2_1
#ifndef GCP_MGCO
#define GCP_MGCO
#endif /* !GCP_MGCO */

#ifndef MGT_MGCO_V2
#define MGT_MGCO_V2
#endif /* MGT_MGCO_V2  */

#ifndef GCP_PKG_MGCO_ROOT
#define GCP_PKG_MGCO_ROOT   
#endif /*GCP_PKG_MGCO_ROOT */
#endif /* GCP_VER_2_1 */


#endif /* MG */


/****************************************************************************
                       End of MGCP Stack
****************************************************************************/


/****************************************************************************
                         PSF-GCP Stack
****************************************************************************/
#ifdef ZG

#ifdef MG_RUG
#define LZG1              /* base release version of LZG intf */
#define ZGP1              /* base release version of GCP peer intf */
#endif /* MG_RUG */

#ifndef MG
#error "GCP flag needs to be defined along with appropriate options."
#endif /* MG */

#ifdef MG
#ifndef MG_FTHA
#define MG_FTHA
#endif
#endif /* MG */

/* #define ZG_DFTHA */                 /* Enable Distribution */
/* #define ZG_TXN_LVL_UPD */           /* Transaction Level FTHA */

/* Layer Manager Interface Flags */
#ifndef LCZGMILZG

#define LCZGMILZG

#ifndef LCLZG
#define LCLZG
#endif 

#endif /* LCZGMILZG */

/* add dependency checks for the new CH flags added */
#ifdef ZG_CH_LVL_UPD

/* The GCP flag for CH should be defined */
#ifndef GCP_CH
#define GCP_CH
#endif /* GCP_CH */

/* CH (command) level updates make sense only if transaction
 * level updates are defined */
#ifndef ZG_TXN_LVL_UPD
#define ZG_TXN_LVL_UPD
#endif /* ZG_TXN_LVL_UPD */

/* CH updates require the latest MGT interface version.
 * Define the latest MGT interface version */
/* #define MGT2 */

#endif /* ZG_CH_LVL_UPD */

#ifdef GCP_VER_2_1
#ifndef   ZG_REF
#define   ZG_REF
#endif /* ZG_REF */
#endif /* GCP_VER_2_1 */


#ifdef   ZG_REF
#ifndef GCP_USE_PEERID
#define GCP_USE_PEERID
#endif

#ifndef GCP_VER_1_3
#define GCP_VER_1_3
#endif 

#ifndef MGT_GCP_VER_1_4
#define MGT_GCP_VER_1_4                /* Support for GCP Release 1.4 */
#endif /* GCP_VER_1_4 */

#ifndef   GCP_VER_1_5
#define   GCP_VER_1_5
#endif /* GCP_VER_1_5 */
#endif /* ZG_REF */

#endif /* ZG */

/****************************************************************************
                       End of PSF-GCP Stack
****************************************************************************/


/****************************************************************************
                         LDF-GCP Stack
****************************************************************************/
#ifdef DG

/* #define DG_RUG */

#ifdef DG_RUG
#define LDG1              /* base release version of LDG intf */
#endif /* DG_RUG */


/*
 * LDF Flags
 */

/* #define DG_LLDF */      /* LLDF Component */
/* #define DG_ULDF */      /* ULDF Component */
/* #define DG_MGC  */      /* MGC Component */
/* #define DG_MG   */      /* MG Component */


/*
 * Interface Flags 
 */

/* #define LCDGMILDG */    /* Layer Manager Loosely Coupled */
/* #define LCDGUIMGT */    /* MGT Interface */
/* #define LCDGLIMGT */    /* MGT Interface */
/* #define LWLCDGLIMGT */  /* LWLC at MGT Interface */
/* #define LCMULIMGT */    /* MGT Interface */
/* #define LCDGLIHIT  */   /* HIT Interface */
/* #define LCDGUIHIT  */   /* HIT Interface */

/* 
 * Multi-Threading Flags
 */

/* #define DG_MULTI_THREADED */
/* #define DG_USE_SEMA       */  /* Use Semaphores */

#ifdef HI_MULTI_THREADED

#ifndef DG_MULTI_THREADED
#define DG_MULTI_THREADED
#endif /* DG_MULTI_THREADED */

#endif /* HI_MULTI_THREADED */

/*
 * IPV6 Flags
 */

/*#define IPV6_SUPPORTED   */          /* IPV6 Support */
/*#define CM_AAAA          */          /* IPV6 Support - Quad A DNS Records */

#ifdef IPV6_SUPPORTED

#ifndef CM_AAAA
#define CM_AAAA
#endif 

#endif /* IPV6_SUPPORTED */

/*********************** Dependency Checks for Interface Flags ****************/

#ifdef LCDGMILDG
#ifndef LCLDG
#define LCLDG
#endif /* LCLDG */
#endif  /* LCDGMILDG */

#ifdef LCDGLIMGT

#ifndef LCMGT
#define LCMGT
#endif /* LCMGT */

#ifndef LCCMSDP
#define LCCMSDP
#endif /* LCCMSDP */

#endif /* LCDGLIMGT */

#ifdef LWLCDGLIMGT

#ifndef LCMGT
#define LCMGT
#endif /* LCMGT */

#ifndef LCCMSDP
#define LCCMSDP
#endif /* LCCMSDP */

#endif /* LWLCDGLIMGT */

/*********************** Dependency Checks for RUG ***************************/
#ifdef DG_RUG

#ifndef TDS_ROLL_UPGRADE_SUPPORT
#define TDS_ROLL_UPGRADE_SUPPORT
#endif /* ifndef TDS_ROLL_UPGRADE_SUPPORT */

#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#define TDS_CORE2
#endif /* ifndef TDS_CORE2 */
#endif /* ifndef TDS_ROLL_UPGRADE_SUPPORT */

#endif /* DG_RUG */

/************************* Dependency Checks for Feature Flags ****************/

#ifdef DG_MGCP
#ifndef GCP_MGCP
#error "MGCP Flag not defined"
#endif
#endif /* DG_MGCP */

#ifdef DG_MGCO
#ifndef GCP_MGCO
#error "MEGACO Flag not defined"
#endif
#endif /* DG_MGCO */

#ifdef DG_USE_SEMA
#ifndef DG_MULTI_THREADED
#error "DG_MULTI_THREADED Flag not defined"
#endif
#endif /* DG_USE_SEMA */

#endif /* DG */

/****************************************************************************
                       End of LDF-GCP Stack
****************************************************************************/

/****************************************************************************
                         LDF - MTP3 section 
****************************************************************************/
#ifdef DN  /* MTP-3 LDF  */
 
/* SN_SG should be enabled if LDF-MTP3 is used in Signalling Gateway */
/* #define SN_SG  1 */

#ifdef SN_SG
#ifndef SNTIWF
#define SNTIWF 1
#endif
#endif

#define DN_ULDF  1       /* LDF acts as Upper load distribution function */
#define DN_LLDF  1       /* LDF acts as Lower load distribution function */
/* #define DN_PT_HOOK     Portable Hooks */
/* #define LCDNMILDN      Loosed coupled management interface */
/* #define DN_DEBUG       debug flag   */
/* #define DN_USTA        usta flag   */

/* #define DN_RUG           Rolling upgrade support enabled */ 
/****************************** Interfaces Version Flags ******************/

/* MTP3 Upper interface */
#define SNTV1              /* Upper interface version 2.0 */

/* MTP2 upper interface */
#define SDTV1              /* Lower interface version 1.0 */

/* Layer management interface */
#define LDNV1              /* Layer Management interface version 1.0 */

/******************* section not to be changed by CUSTOMERS ******************/ 
#ifdef LCDNMILDN
#ifdef LCLDN
#undef LCLDN
#endif
#define LCLDN    1
#endif /* LCDNMILDN */

/*
** MUST define DN_ULDF and/or DN_LLDF.
** If (DN_ULDF not defined ) and (DN_LLDF not defined) 
** then LDF assumes that it acts as both ULDF and LLDF
** 
*/

#ifndef DN_ULDF
#ifndef DN_LLDF
#define DN_ULDF  1       /* LDF acts as Upper load distribution function */
#define DN_LLDF  1       /* LDF acts as Lower load distribution function */
#endif /* DN_LLDF */
#endif /* DN_ULDF */

#ifdef SNT2
#undef SNT2
#endif /* SNT2 */

#ifdef SDT2
#undef SDT2
#endif /* SDT2 */

#ifdef LCSNT
#undef LCSNT
#endif /* LCSNT */

#ifdef LCSDT
#undef LCSDT
#endif /* LCSDT */

#ifdef LCDNLISNT
#undef LCDNLISNT
#endif /* LCDNLISNT */

#ifdef LCDNUISDT
#undef LCDNUISDT
#endif /* LCDNUISDT */


#define SNT2             /* SNT bind confirm interface */
#define SDT2             /* SDT bind confirm interface */
#define LCDNLISNT        /* loose coupled SNT interface from DN */
#define LCDNUISDT        /* loose coupled SDT interface from DN */
#define LCSNT            /* Loose coupled SNT interface */
#define LCSDT            /* Loose coupled SDT interface */

#endif     /* MTP-3 LDF section */
/****************************************************************************
                       End of LDF-MTP3 Section
****************************************************************************/
/****************************************************************************
                         LDF - ISUP section 
****************************************************************************/
#ifdef DI  /* ISUP LDF  */
 
#define DI_ULDF  1       /* LDF acts as Upper load distribution function */
#define DI_LLDF  1       /* LDF acts as Lower load distribution function */
/* #define DI_RUG           Enable rolling upgrade support in LDF ISUP */
/* #define DI_USTA          flag to enable the alarm */
/* #define DI_DEBUG         flag to enable all debug mask */
/* #define GT_FTZ           GT_FTZ, option 23 - Genrman Variant */

/*************************** Interface coupling flags *********************/

/* #define LCDIMILDI        loose coupled LDI interface from DI */

/****************************** Interfaces Version Flags ******************/

/* ISUP Upper interface - define the latest version */
/* #define SITV1              Upper interface version 1.0 */ 
#define SITV2              /* Upper interface version 2.0 */ 

/* MTP3 upper interface - define the latest version */  
#define SNTV1              /* Lower interface version 1.0 */

/* Layer management interface - define the latest version */
#define LDIV1              /* Layer Management interface version 1.0 */
 
/**************** section not to be changed by CUSTOMERS *****************/ 

/*
** MUST define DI_ULDF and/or DI_LLDF.
** If (DI_ULDF not defined ) and (DI_LLDF not defined) 
** then LDF assumes that it acts as both ULDF and LLDF
** 
*/

#ifndef DI_ULDF
#ifndef DI_LLDF
#define DI_ULDF  1       /* LDF acts as Upper load distribution function */
#define DI_LLDF  1       /* LDF acts as Lower load distribution function */
#endif /* DI_LLDF */
#endif /* DI_ULDF */

/* Disable LCDILISIT and LCDIUISNT when it is portable compilation */
#ifndef PORTVER
#define LCDILISIT        /* loose coupled SIT interface from DI */
#define LCDIUISNT        /* loose coupled SNT interface from DI */
#endif

#ifndef SIT2
#define SIT2             /* SIT bind confirm interface */
#endif /* SIT2 */

#ifndef SNT2
#define SNT2             /* SNT bind confirm interface */
#endif /* SNT2 */


/* define dependency checks */ 
#ifdef LCDILISIT
#ifndef LCSIT
#define LCSIT 1
#endif
#endif

#ifdef LCDIUISNT
#ifndef LCSNT
#define LCSNT 1
#endif
#endif

#ifdef DI_RUG
#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "DI_RUG can not be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif
#endif

#endif     /* ISUP LDF section */
/****************************************************************************
                       End of LDF-ISUP Section
****************************************************************************/
/****************************************************************************
                       Start of SIGTRAN Stack Section
****************************************************************************/

/******************************************************************/
/*                  SCTP Layer                                    */
/******************************************************************/

#ifdef SB

/* for loosely coupled upper interface */
/* #define LCSBUISCT */

/* for loosely coupled lower interface */
/* #define LCSBLIHIT */

/* for loosely coupled layer manager interface */
/* #define LCSBMILSB */

/* tightly coupled layer manager */
/* #define SM */

/* tightly coupled upper interface */
/* #define IT */

/* tightly coupled lower interface */
/* #define HI */

/* new TUCL layer */
#ifndef HI_REL_1_3
#define HI_REL_1_3
#endif

#ifndef CM_INET2
#define CM_INET2
#endif

/* MD5 stuff */
#ifndef SB_MD5
/* #define SB_MD5        Define to include trillium supplied functions */
#endif

/* Checksum */
#ifndef SB_CHECKSUM
#define SB_CHECKSUM   /* Define to include trillium supplied function */
#endif

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



/*
 *   Either CM_SDP_OPAQUE flag OR the rest of the SDP flags
 *   should be defined i.e. these flags are mutually exclusive
 */
#ifdef    CM_SDP_OPAQUE
#ifdef    CM_SDP_V_2
#undef    CM_SDP_V_2
#endif /* CM_SDP_V_2 */

#ifdef    CM_SDP_V_3
#undef    CM_SDP_V_3
#endif /* CM_SDP_V_3 */

#ifdef    CM_SDP_ATM_SUPPORT
#undef    CM_SDP_ATM_SUPPORT
#endif /* CM_SDP_ATM_SUPPORT */
#endif /* CM_SDP_ATM_SUPPORT */

#ifdef CM_SDP_V_3
#ifdef    CM_SDP_OPAQUE
#undef CM_SDP_OPAQUE
#endif /* CM_SDP_OPAQUE */
#ifndef CM_SDP_V_2
#define CM_SDP_V_2
#endif /* CM_SDP_V_2 */
#endif /* CM_SDP_V_3 */


/******************************************************************/
/* SIP SDK                                                      */
/******************************************************************/

#ifdef SW_SDK
#ifdef SW_SDP

#ifdef CM_SDP_OPAQUE
#undef CM_SDP_OPAQUE
#endif

#ifndef CM_SDP_V_2
#define CM_SDP_V_2

#ifndef CM_SDP_V_3
#define CM_SDP_V_3
#endif

#endif
#ifndef  SOT_SIP_MSG
#define  SOT_SIP_MSG
#endif
#else  /* SW_SDP */

#ifndef    CM_SDP_OPAQUE
#ifndef    CM_SDP_V_2
#define    CM_SDP_V_2
#endif /* CM_SDP_V_2 */
#ifndef    CM_SDP_V_3
#define CM_SDP_V_3
#endif /* CM_SDP_V_3 */
#endif /* !CM_SDP_OPAQUE */

#endif /* SW_SDP */
#endif /* SW_SDK */
/******************************************************************/
/* SIP Layer                                                     */
/******************************************************************/
#ifdef SO

/******************* section to be changed by CUSTOMERS ******************/ 
/* These options can be enabled in the make file also */
/* #define LCSOUISOT        loosely coupled SOT Interface User */
/* #define LWLCSOUISOT      lightweight loosely coupled SOT interface */
/* #define LCSOLIHIT        loosely coupled transport layer Interface */
/* #define LCSOMILSO        loosely coupled SIP to stack manager 
                              Also enable LCSMSOMILSO under #ifdef SM */

/* #define  CM_SDP_V_2      enable to be compatable to SDP rel 2  */
/* #define  CM_ABNF_V_1_2   enable to be compatable to ABNF rel 1.2 */
/* #define  CM_ABNF_DBG     enable to turn ON ABNF debug support */
/* #define  CMINETDBG       enable socket debugging supprt */

/* #define  LSO_ACNT        enable to turn on Account Indications */
/* #define  SO_UA           enable to compile in User Agent support */
/* #define  SO_NS           enable to compile in Network Server support */
/* #define  SO_ABNF_MT_LIB  enable to turn multiThreaded Encoder/Decoder */

/* #define  DEBUGP          enable to turn ON debug support */
/* #define  NO_ERRCLS       enable to compile out error class checking */

/*************** section not to be changed by CUSTOMERS ******************/
/* needed dependencies */

#ifdef SO_NS_STATEFUL
#ifndef SO_NS
#define SO_NS
#endif
#endif

/*--- Automatic enabling of required feature flag in NS ----*/
#ifdef SO_NS
#ifndef SO_EVENT
#define SO_EVENT
#endif
#endif



#if !defined(SO_UA) && !defined(SO_NS)
#error "Please define either SO_UA or SO_NS"
#endif



#if (defined(LCSOUISOT) || defined(LCSVLISOT))
#ifndef LCSOT
#define LCSOT 1
#define LCCMSDP 1
#endif
#endif

#if (defined(LWLCSOUISOT) || defined(LWLCSVLISOT))
#ifndef LWLCSOT
#define LWLCSOT 1
#ifndef LCCMSDP
#define LCCMSDP 1
#endif
#endif
#endif

#if (defined(CM_TLS))
#ifndef SO_TLS
#define SO_TLS
#endif
#endif

#if (defined(SO_TLS))
#ifndef CM_TLS
#define CM_TLS
#endif
#endif

#if (defined(LCSOMILSO) || defined(LCSMSOMILSO))
#ifndef LCLSO
#define LCLSO 1
#endif
#endif

#if (defined(LCSOLIHIT) || defined(LCHIUIHIT))
#ifndef LCHIT
#define LCHIT 1
#endif
#endif

#if (defined(LCSOLISCT) || defined(LCSBUISCT))
#ifndef LCSCT
#define LCSCT 1
#endif
#endif

#ifdef SO_REFER

#ifndef SO_EVENT
#define SO_EVENT
#endif /* SO_EVENT */

#ifndef SO_REPLACES
#define SO_REPLACES
#endif /* SO_REPLACES */

#endif /* SO_REFER */

/* MultiThreaded Encoder/Decoder in SIP*/
#ifdef SS_SINGLE_THREADED
#undef SO_ABNF_MT_LIB
#undef CM_ABNF_MT_LIB
#else
#ifdef SO_ABNF_MT_LIB
#ifndef CM_ABNF_MT_LIB
#define CM_ABNF_MT_LIB
#endif
#endif
#endif

#if (defined(SO_AAAA) || defined(SO_ENUM))
#ifndef SO_DNS
#define SO_DNS
#endif
#endif


#ifdef SO_AAAA
#ifndef CM_AAAA
#define CM_AAAA
#endif /* CM_AAAA */
#endif /* SO_AAAA */

#ifdef SO_ENUM
#ifndef CM_NAPTR
#define CM_NAPTR
#endif /* CM_NAPTR */
#endif /* SO_ENUM */

#ifdef SO_DNS
#ifndef CM_NAPTR
#define CM_NAPTR
#endif /* CM_NAPTR */
#endif /* SO_DNS   */


#ifdef SO_INSTMSG
#ifndef CM_SDP_OPAQUE
#ifndef CM_SDP_SIP_IM_SUPPORT
#define CM_SDP_SIP_IM_SUPPORT
#endif /* CM_SDP_SIP_IM_SUPPORT */
#endif /* CM_SDP_OPAQUE*/ 
#endif /* SO_INSTMSG */

#ifdef SO_COMPRESS
#ifndef CM_COMPRESS
#define CM_COMPRESS
#endif 
#endif 


#ifdef SO_NAT
#ifndef SO_USE_UDP_SRVR
#define SO_USE_UDP_SRVR 
#endif
#endif

/* ---- Define SO_SCTP if SB is defined but not other way round */
#ifdef SB
#ifndef SO_SCTP
#define SO_SCTP
#endif
#endif

/*-- SCT interface definitions --*/
#ifdef SO_SCTP

#ifndef SCT_ENDP_MULTI_IPADDR
#define SCT_ENDP_MULTI_IPADDR
#endif

#ifndef SB_CHECKSUM
#define SB_CHECKSUM
#endif

#ifndef LSB5
#define LSB5
#endif

#ifndef SCT2
#define SCT2
#endif

#ifndef SCT3
#define SCT3
#endif

#endif   /* SO_SCTP*/


/*-- SIP Dependency on version of common ABNF Library --*/

/*-- SIP 2.2 works with CM_ABNF_V_1_3 and SIP 2.1 works with 
     CM_ABNF_V_1_2. We may use the SOT interface version to
     check which SIP version we are using. 
     
     Please note that this is not the best option if the 
     SIP product version is changed later while the SOT 
     interface remains the same. 
     
     Please update accordingly for any product and SOT 
     interface changes in the future --*/
#ifdef SOT2
#ifndef CM_ABNF_V_1_3
#define CM_ABNF_V_1_3
#endif /*-- CM_ABNF_V_1_3 --*/
#else
/*-- SIP 2.1, Disable CM_ABNF_V_1_3 if enabled --*/
#ifdef CM_ABNF_V_1_3
#undef CM_ABNF_V_1_3
#endif /*-- CM_ABNF_V_1_3 --*/
#endif /*-- SOT2 --*/

/* Check for TDS_ROLL_UPGRADE_SUPPORT */
#ifdef SO_RUG
#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "SO_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
#endif /* SO_RUG */

/* ---- Define CM_MULTIPLE_DNS_SERVER if SO_MULTIPLE_DNS_SERVER is defined but not other way round */
#ifdef SO_MULTIPLE_DNS_SERVER
#ifndef CM_MULTIPLE_DNS_SERVER
#define CM_MULTIPLE_DNS_SERVER
#endif
#endif

/* Check for SO_DMH */
#ifdef SO_DMH
#if (!defined(SO_NS_STATEFUL) || !defined(SO_UA))
#error "SO_DMH cannot be defined without SO_NS_STATEFUL SO_UA "
#endif /* SO_NS_STATEFUL and SO_UA */
#endif /* SO_DMH */

/* Check for SO_DLG_TGT_FREEZE and SO_DNS_RR_LDSHARE */
#if (defined(SO_DLG_TGT_FREEZE) || defined(SO_DNS_RR_LDSHARE))
#ifndef SO_DNS
#error "SO_DLG_TGT_FREEZE OR SO_DNS_RR_LDSHARE cannot be defined without SO_DNS"
#endif
#endif

#ifndef    CM_SDP_OPAQUE

#ifndef    CM_SDP_V_2
#define    CM_SDP_V_2
#endif /* CM_SDP_V_2 */
#ifndef    CM_SDP_V_3
#define CM_SDP_V_3
#endif /* CM_SDP_V_3 */

#endif /* !CM_SDP_OPAQUE */


#endif /* SO */


#ifdef SV       /* SIP User */

/**************************************************************************
   SIP User Parameters
**************************************************************************/

/******************* section to be changed by CUSTOMERS ******************/ 

/*** Interfaces Coupling Options ***/

/* lower interface, SOT */

/* #define LCSVLISOT               loosely coupled */

/* #define LWLCSVLISOT             light weight loosely coupled */

/*************** section not to be changed by CUSTOMERS ******************/

#ifdef LCSVLISOT

#ifndef LCSOT
#define LCSOT
#endif /* LCSOT */

#endif /* LCSVLISOT */

#ifdef LWLCSVLISOT

#ifndef LWLCSOT
#define LWLCSOT
#endif /* LWLCSOT */

#endif /* LWLCSVLISOT */

#if (defined(LCSOUISOT) || defined(LCSVLISOT))
#ifndef LCSOT
#define LCSOT 1
#define LCCMSDP 1
#endif
#endif

#if (defined(LWLCSOUISOT) || defined(LWLCSVLISOT))
#ifndef LWLCSOT
#define LWLCSOT 1
#ifndef LCCMSDP
#define LCCMSDP 1
#endif
#endif
#endif

#if (defined(LCSVLIHIT) || defined(LCHIUIHIT))
#ifndef LCHIT
#define LCHIT 1
#endif
#endif

#endif /* SV */


#ifdef ZO       /* PSF - SIP (FT/HA) */
/**************************************************************************
   PSF parameters
**************************************************************************/
#undef ZO
#define ZO 1

/******************* section to be changed by CUSTOMERS ******************/
/* #define LCZOMILZO       loosely coupled, layer management */

/* The following flag must be turned-on if the customer chooses to implement it's
   own packing-unpacking functions for update messages */

/* #define CUSTENV */

/* #define ZO_USTA      enable alarms by default */
/* #define ZO_DEBUG     enable debug prints by deault (only for debugging) */

/************** section NOT to be changed by CUSTOMERS **********/


#ifndef LCLZO
#define LCLZOA 1
#endif /* LCLZO */

#ifndef LCCMSDP
#define LCCMSDP            /* SDP flags required for SIP-FTHA */
#endif /* LCCMSDP */

#ifndef LCLZO
#define LCLZO 1
#endif

/* dependency of ZO and SO_FTHA */
#ifndef SO_FTHA
#define SO_FTHA
#endif

#ifndef CM_PSF_MBUF_USAGE
#define CM_PSF_MBUF_USAGE  /* Common PSF usage */
#endif

#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#error "Rolling upgrade feature available in CORE II only."
#endif
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

/* Check for TDS_ROLL_UPGRADE_SUPPORT */
#ifdef SO_RUG
#ifndef TDS_ROLL_UPGRADE_SUPPORT
#define TDS_ROLL_UPGRADE_SUPPORT
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
#endif /* SO_RUG */

#endif /* ZO */


/******************************************************************/
/*                    M3UA Layer                                  */
/******************************************************************/

#ifdef IT
#undef IT
#define IT 1

/******************* section to be changed by CUSTOMERS ******************/

/* Product options, choose one or more depending on the license agreement.
 * Please check your license agreement before enabling any of the following
 * flags.
 */

/* #define ITASP   ASP function of M3UA */
/* #define ITSG    SG function of M3UA */
/* #define NF      NIF of M3UA */

/* For Fault Tolerant, High Availability interface support */
/* #define IT_FTHA */

/* Options to enable alarms/debug mask during compile time */
/* #define IT_USTA         Uncomment to enable alarms by default */
/* #define IT_DEBUG        Uncomment to enable all debug prints by default */

/* #define SCT_ENDP_MULTI_IPADDR  Multiple endpoint support in SCTP per IP addr */
/* #define SGVIEW  Applicable only at ASP, provides remote SG view for SGPs */

/* #define SNT_BACK_COMP_MERGED_NIF Backward compatibility for customer's own NIF */

/* M3UA Functionality specific defines */
/* #define IT_ABORT_ASSOC  * flexibility to LM for specifying whether to abort assoc or not */ 
/* #define OG_RTE_ON_LPS_STA  * Only at ASP, if enabled then outgoing route willdepend upon Local PS state (it has to be active) */

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCITUISNT        loosely coupled, MTP upper layer */

/* lower interface, data link, choose none or more */

/* #define LCITLISCT     loosely coupled, lower layer */

/* #define LCSNLISNT     loosely coupled, lower layer (MTP3) */

/* management interface, lit , choose none or more */

/* #define LCITMILIT       loosely coupled, layer management */

/* Interfaces Coupling Options required only for accepatnce tests and dummy
 * layers*/

/* #define LCSBUISCT       loosely coupled, upper interface for dummy SCTP*/
/* #define LCSNTLISNT       loosely coupled, lower interface for dummy user*/

/* Interface coupling options for MTP3 : Applicable only at SG */
/* Following define is to be used only when SNT_BACK_COMP_MERGED_NIF is not used
 */ 
/* #define LCITLISNT       loosely coupled, lower interface for dummy mtp3 */
/* #define LCSNUISNT       loosely coupled, MTP upper layer */


/* In a fault tolerant environment, to prevent system manager from
 * binding and enabling the lower saps uncomment the following flag */
/* #define IT_DIS_SAP  */

#define SNT2           /* new upper interface */

#ifdef ITSG
#ifndef SNTIWF
#define SNTIWF 1
#endif
#endif
/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */

#ifdef LCITMILIT
#ifndef LCLIT
#define LCLIT 1
#endif /* LCLIT */
#ifndef LCSCT
#define LCSCT 1
#endif /* LCSCT */
#endif /* LCLITMILIT */


#ifdef LCITUISNT
#ifndef LCSNT
#define LCSNT 1
#endif /* LCSNT */
#endif /* LCITUISNT */


#ifdef LCITLISCT
#ifndef LCSCT
#define LCSCT 1
#endif /* LCSCT */
#endif /* LCITLISCT */
/*
#ifdef SNT_BACK_COMP_MERGED_NIF
#ifndef LCL4LISNT
#define LCL4LISNT 1
#endif
#endif
*/

#ifdef LCITMILIT
#ifndef LCLIT
#define LCLIT
#endif /* LCLIT */
#ifndef LCSCT
#define LCSCT 1
#endif /* LCSCT */
#endif /* LCITMILIT */

#endif /* IT */

#ifdef ZV       /* PSF - M3UA (FT/HA) */
/**************************************************************************
   PSF parameters
**************************************************************************/
#undef ZV
#define ZV 1

/******************* section to be changed by CUSTOMERS ******************/

/* management interface, lzv */

/* #define LCZVMILZV        loosely coupled, layer management */

/* The following flag must be turned-on if the customer chooses to implement it's
   own packing-unpacking functions for update messages */

/* #define CUSTENV */

/* #define ZV_DFTHA     distributed PSF - M3UA environment */
/* #define ZV_USTA      enable alarms by default */
/* #define ZV_DEBUG     enable debug prints by deault (only for debugging) */

/****************************** Interfaces Version Flags ******************/

/* Peer interface */
#define ZVPV1              /* Upper interface version 1.0 */

/* Layer management interface */
#define LZVV1              /* Layer Management interface version 1.0 */

/************** section NOT to be changed by CUSTOMERS **********/


#ifndef SNT2
#define SNT2
#endif /* SNT2 */

#ifdef LCZVMILZV

#ifndef LCLZV
#define LCLZV 1
#endif /* LCLZV */

#endif /* LCLZVMILZV */

/* dependency of ZV and IT_FTHA */
#ifndef IT_FTHA
#define IT_FTHA
#endif

/* dependency of TDS_CORE2 and ZV_DFTHA */
#ifndef TDS_CORE2
#ifdef ZV_DFTHA
#error "Please define TDS_CORE2"
#endif /* ZV_DFTHA */
#endif /* TDS_CORE2 */
#endif /* ZV */

/******************************************************************/
/*                    LDF-M3UA Layer                              */
/******************************************************************/
#ifdef DV  /* M3UA LDF  */
 
/* SNTIWF should be enabled if LDF-M3UA is used in Signalling Gateway */
#ifndef SNTIWF
#define SNTIWF 1
#endif

#define DV_ULDF  1       /* LDF acts as Upper load distribution function */
#define DV_LLDF  1       /* LDF acts as Lower load distribution function */
/* #define DV_PT_HOOK     Portable Hooks */
/* #define LCDVMILDV      Loosed coupled management interface */
/* #define DV_DEBUG       debug flag   */
/* #define DV_USTA        usta flag   */

/* #define DV_RUG         Rolling upgrade support enabled */ 
/****************************** Interfaces Version Flags ******************/

/* M3UA Upper interface */
#define SNTV1            /* Upper interface version 2.0 */

/* M3UA lower interface */
#define SCTV1            /* Lower interface version 1.0 */

/* Layer management interface */
#define LDVV1            /* Layer Management interface version 1.0 */

/******************* section not to be changed by CUSTOMERS ******************/ 
#ifdef LCDVMILDV
#ifdef LCLDV
#undef LCLDV
#endif
#define LCLDV    1
#endif /* LCDVMILDV */

#if defined(TDS_ROLL_UPGRADE_SUPPORT) || defined(DV_RUG)
#if !defined(TDS_CORE2) || !defined(TDS_ROLL_UPGRADE_SUPPORT) || !defined(DV_RUG)
#error "Please enable TDS_CORE2, TDS_ROLL_UPGRADE_SUPPORT & DV_RUG flags"
#endif 
#endif

/*
** MUST define DV_ULDF and/or DV_LLDF.
** If (DV_ULDF not defined ) and (DV_LLDF not defined) 
** then LDF assumes that it acts as both ULDF and LLDF
** 
*/

#ifndef DV_ULDF
#ifndef DV_LLDF
#define DV_ULDF  1       /* LDF acts as Upper load distribution function */
#define DV_LLDF  1       /* LDF acts as Lower load distribution function */
#endif /* DV_LLDF */
#endif /* DV_ULDF */

#ifdef SNT2
#undef SNT2
#endif /* SNT2 */

#ifdef LCSNT
#undef LCSNT
#endif /* LCSNT */

#ifdef LCSCT
#undef LCSCT
#endif /* LCSCT */

#ifdef LCDVLISNT
#undef LCDVLISNT
#endif /* LCDVLISNT */

#ifdef LCDVUISNT
#undef LCDVUISNT
#endif /* LCDVUISNT */

#ifdef LCDVUISCT
#undef LCDVUISCT
#endif /* LCDVUISCT */

#define SNT2             /* SNT bind confirm interface */
#define LCDVUISNT        /* loose coupled SNT interface from DV */
#define LCDVLISNT        /* loose coupled SNT interface from DV */
#define LCDVUISCT        /* loose coupled SCT interface from DV */
#define LCSNT            /* Loose coupled SNT interface */
#define LCSCT            /* Loose coupled SCT interface */

#endif     /* M3UA LDF section */
/******************************************************************/
/*                    NIF Layer                                   */
/******************************************************************/

#ifdef NF
#undef NF
#define NF 1

/******************* section to be changed by CUSTOMERS ******************/

/* For Fault Tolerant, High Availability interface support */
/* #define NF_FTHA */

/* Options to enable alarms/debug mask during compile time */
/* #define NF_USTA           Uncomment to enable alarms by default */
/* #define NF_DEBUG          Uncomment to enable all debug prints by default */

/*** Interfaces Coupling Options ***/

/* lower interface, SNT, choose none or more */

/* #define LCNFLISNT       loosely coupled */

/* management interface, lnf , choose none or more */

/* #define LCNFMILNF       loosely coupled, layer management */

/* Option required for NIF accepatnce tests. If this is set, ITSG must 
 * also be defined and ITASP must not be defined.*/

/* #define SN    */

#define SNT2           /* new lower interface */

#ifndef SNTIWF
#define SNTIWF 1       /* lower interface interworking functions */
#endif


/************** section NOT to be changed by CUSTOMERS **********/


#ifdef LCNFMILNF
#ifndef LCLNF
#define LCLNF 1
#endif /* LCLNF */
#endif /* LCLNFMILNF */


#ifdef LCNFLISNT
#ifndef LCSNT
#define LCSNT 1
#endif /* LCSNT */
#endif /* LCNFUISNT */
#endif /* NF */

/******************************************************************/
/*                      IUA Layer                                 */
/******************************************************************/

#ifdef ID
#undef ID
#define ID 1

/******************* section to be changed by CUSTOMERS ******************/

/* Product options, choose one or more depending on the license agreement.
 * Please check your license agreement before enabling any of the following
 * flags.
 */

/* #define IDASP   ASP function of IUA */

/* #define IDSG    SG function of IUA */

/* #define ND      NIF of IUA */

/* For Fault Tolerant, High Availability interface support */
/* #define ID_FTHA */
/*** Interfaces Coupling Options ***/


/* for loosely coupled upper interface at ASP side */
/* lower interface, data link, choose none or all */
/* #define LCIDUIDAT         loosely coupled, upper interface */
/* #define LCIDUILVT        loosely coupled, upper interface */
/* #define LCIDUIDDT        loosely coupled, upper interface DUA */

/* #define LCIDLISCT         loosely coupled, lower interface */

/* management interface, lsn , choose none or more */

/* #define LCIDMILID         loosely coupled, layer management */

/* this flags are  required for unit testing */
/* #define LCINLIDAT        loosely coupled Q.931 upper layer */
/* #define LCVFLILVT        loosely coupled V5L3  upper layer */
/* #define LCINLIDDT      loosely coupled, DPNSS/DASS2 L3 */
/* #define LCSBUISCT        SCTP flag kept here for easy access */
/* #define LCLDUIDAT        loosely coupled, at LAPD interface to NIF*/
/* #define LCLVUILVT        loosely coupled, at LAPD interface to NIF*/
/* #define LCD2UIDDT        loosely coupled, at LAPD interface to NIF*/
/* #define LCD3LIDDT        loosely coupled, at LAPD interface to NIF*/


#ifdef LVTVER2   /* The flag make the additional code dormat at the LVT 
                    interface for Disc Req and UDat API's  */
#undef LVTVER2
#endif 

#ifndef DAT2
#define DAT2  1
#endif

#ifndef L3VER2
#define L3VER2
#endif

#ifndef BDVER2
#define BDVER2
#endif

/*  Supported protocols */
/*#define IUA    1   ISDN Q.931 User Adoptation layer   */
/*#define V5UA   1  * V5.2 User Adoptation layer         */
/*#define DUA    1  * DPNSS/DASS2 User Adoptation layer  */
/* #define MULTUA *MULTIPLE protocol User adotation layer      
                    If MULTIUA is define make sure 
                    that all the supported protocol 
                    #defines are  also define          */

/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */


#ifdef LCIDMILID
#ifndef LCLID
#define LCLID 1
#endif /* LCLID */
#endif /* LCIDMILID */

#ifdef LCIDUIDAT
#ifndef LCDAT
#define LCDAT 1
#endif /* LCDAT */
#endif /* LCIDUIDAT */


#ifdef LCIDUILVT
#ifndef LCLVT
#define LCLVT 1
#endif /* LCLVT */
#endif /* LCIDUILVT */

#ifdef LCIDUIDDT
#ifndef LCDDT
#define LCDDT 1
#endif
#endif /* LCIDUDDT */

#ifdef LCD3LIDDT
#ifndef LCDDT
#define LCDDT  1
#endif /* LCDDT */
#endif /* LCD3LIDDT */

#ifdef LCIDLISCT
#ifndef LCSCT
#define LCSCT 1
#endif /* LCSCT */
#endif /* LCIDLISCT */

/*if any two protocols are aupported define MULTUA*/
#if   (defined(V5UA) &&  defined (DUA)) \
    ||(defined(IUA)  && defined (V5UA)) \
    ||(defined (IUA) &&  defined (DUA))
#ifndef MULTUA
#define MULTUA
#endif /*MULTUA*/
#endif/*Any two protocols supported*/


#endif /* ID */

/******************************************************************/
/*            IUA Layer Node Interworking Function               */
/******************************************************************/

#ifdef ND
#undef ND
#define ND 1

/******************* section to be changed by CUSTOMERS ******************/
/*** Interfaces Coupling Options ***/

/* lower interface, DAT, choose none or one */
/* #define LCNDLIDAT         loosely coupled DAT interface */
/* #define LCNDLILVT         loosely coupled NIF upper layer */
/* #define LCNDLIDDT         loosely coupled NIF upper layer */
/* management interface, lnf , choose none or one */
/* #define LCNDMILND       loosely coupled, layer management */


/* #define ND_FTHA         For Fault Tolerant, High Availability support */

#ifndef DAT2
#define DAT2  1
#endif

#ifndef L3VER2
#define L3VER2
#endif

/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */

#ifdef LCNDMILND
#ifndef LCLND
#define LCLND 1
#endif /* LCLND */
#endif /* LCNDMILND */


#ifdef LCNDLIDAT
#ifndef LCDAT
#define LCDAT 1
#endif /* LCDAT */
#endif /* LCNDLIDAT */

#ifdef LCNDLIDDT
#ifndef LCDDT
#define LCDDT 1
#endif /* LCDDT */
#endif /* LCNDLIDDT */
#ifdef LCNDLILVT
#ifndef LCLVT
#define LCLVT 1
#endif /* LCLVT */
#endif /* LCNDLILVT */

/*if any two protocols are aupported define MULTUA*/
#if   (defined(V5UA) &&  defined (DUA)) \
    ||(defined(IUA)  && defined (V5UA)) \
    ||(defined (IUA) &&  defined (DUA))
#ifndef MULTUA
#define MULTUA
#endif /*MULTUA*/
#endif/*Any two protocols supported*/

#endif /* ND */

/******************************************************************/
/*                    M1UA Layer                                  */
/******************************************************************/

#ifdef MZ
#undef MZ
#define MZ 1
/******************* section to be changed by CUSTOMERS ******************/
/*** Interfaces Coupling Options ***/

/* lower interface, SCT and MAC, choose none or one */
/* #define LCMZLISCT     loosely coupled SCT interface */
/* #define LCMZLIMAC     loosely coupled MAC interface */

/* management interface, lnf , choose none or one */
/* #define LCMZMILMZ     loosely coupled, layer management */


#ifndef MACINT4
#define MACINT4  1
#endif

#ifndef DATVER2 
#define DATVER2 1
#endif

/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */

#ifdef LCMZMILMZ
#ifndef LCLMZ
#define LCLMZ 1
#endif /* LCLMZ */
#endif /* LCMZMILMZ */


#ifdef LCMZLISCT
#ifndef LCSCT
#define LCSCT 1
#endif /* LCSCT */
#endif /* LCMZLISCT */

#ifdef LCMZLIMAC
#ifndef LCMAC
#define LCMAC 1
#endif /* LCMAC */
#endif /* LCMZLIMAC */

#endif /* MZ */


/***************************************************************************
                    End of IUA and IUA-NIF Section
 ****************************************************************************/

/******************************************************************/
/*                      M2UA Layer                                 */
/******************************************************************/

#ifdef MW
#undef MW
#define MW 1

/******************* section to be changed by CUSTOMERS ******************/

/* Product options, choose one or more depending on the license agreement.
 * Please check your license agreement before enabling any of the following
 * flags.
 */

/* #define MWASP  ASP function of M2UA */
/* #define MWSG   SG function of M2UA */
/* #define NW     NIF of M2UA */

/* For Fault Tolerant, High Availability interface support */
/* #define MW_FTHA */

/* Options to enable alarms debug mask during compile time */
/* #define MW_USTA       Uncomment to enable alarms by default */
/* #define MW_DEBUG      Uncomment to enable all debug prints by default */

/*** Interfaces Coupling Options ***/

/* for loosely coupled upper interface at ASP side */
/* #define LCMWUISDT       */

/* for loosely coupled upper interface at SGP side */
/* #define LCMWUIMWT       */

/* for loosely coupled lower interface */
/* #define LCMWLISCT       */

/* for loosely coupled layer manager interface */
/* #define LCMWMILMW       */

/* Interfaces Coupling Options required only for accepatnce tests and dummy
 * layers*/

/* #define LCSBUISCT       loosely coupled, upper interface for dummy SCTP*/
/* #define LCSNLISDT       loosely coupled, lower interface for dummy user*/

/* To enable command line option, otherwise all test case will be executed */
/* #define MWACC_CMD_LINE   */

/* In a fault tolerant environment, to prevent system manager from
 * binding and enabling the lower saps uncomment the following flag */
/* #define IT_DIS_SAP  */

/************** section NOT to be changed by CUSTOMERS **********/
/* needed dependencies */
#ifdef LCMWUISDT
#ifndef LCSDT
#define LCSDT 1
#endif
#endif

#ifdef LCMWUIMWT
#ifndef LCMWT
#define LCMWT 1
#endif
#endif

#ifdef LCMWMILMW
#ifndef LCLMW
#define LCLMW 1
#endif
#endif

#ifdef LCMWLISCT
#ifndef LCSCT
#define LCSCT 1
#endif
#endif

#endif /* MW */

/******************************************************************/
/*            M2UA Layer Node Interworking Function               */
/******************************************************************/

#ifdef NW
#undef NW
#define NW 1

/******************* section to be changed by CUSTOMERS ******************/
/* For Fault Tolerant, High Availability interface support */
/* #define NW_FTHA */

/* Options to enable alarms/debug mask during compile time */
/* #define NW_USTA      Uncomment to enable alarms by default */
/* #define NW_DEBUG     Uncomment to enable all debug prints by default */

/*** Interfaces Coupling Options ***/

/* lower interface, SDT, choose none or one */
/* #define LCNWLISDT     */

/* lower interface, MWT, choose none or one */
/* #define LCNWLIMWT     */

/* management interface, lnf , choose none or one */
/* #define LCNWMILNW     */

/* Interfaces Coupling Options required only for accepatnce tests and dummy
 * layers*/
/* #define LCSDUISDT     loosely coupled, upper interface for dummy MTP2*/

/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */

#ifdef LCNWMILNW
#ifndef LCLNW
#define LCLNW 1
#endif /* LCLNW */
#endif /* LCNWMILNW */


#ifdef LCNWLISDT
#ifndef LCSDT
#define LCSDT 1
#endif /* LCSDT */
#endif /* LCNWLISDT */

#ifdef LCNWLIMWT
#ifndef LCMWT
#define LCMWT 1
#endif /* LCMWT */
#endif /* LCNWLIMWT */

#endif /* NW */

#ifndef SDT2
#define SDT2
#endif

/***************************************************************************
                    End of M2UA and M2UA-NIF Section
 ****************************************************************************/

/**************************************************************************/
/*                      M2PA Layer                                        */
/**************************************************************************/

#ifdef MX
#undef MX
#define MX 1

/******************* section to be changed by CUSTOMERS ******************/

/* Product options, choose one or more depending on the license agreement.
 * Please check your license agreement before enabling any of the following
 * flags.
 */

/* For Fault Tolerant, High Availability interface support */
/* #define MX_FTHA */

/* Options to enable alarms debug mask during compile time */
/* #define MX_USTA       Uncomment to enable alarms by default */
/* #define MX_DEBUG      Uncomment to enable all debug prints by default */

/*** Interfaces Coupling Options ***/

/* for loosely coupled upper interface */
/* #define LCMXUISDT       */

/* for loosely coupled lower interface */
/* #define LCMXLISCT       */

/* for loosely coupled layer manager interface */
/* #define LCMXMILMX       */

/* Interfaces Coupling Options required only for accepatnce tests and dummy
 * layers*/

/* #define LCSBUISCT       loosely coupled, upper interface for dummy SCTP*/
/* #define LCSNLISDT       loosely coupled, lower interface for dummy user*/

/* To enable command line option, otherwise all test case will be executed */
/* #define MXACC_CMD_LINE   */

/* Product specific options */
/* #define SS7_TTC         TTC variant for M2PA */
/* In a fault tolerant environment, to prevent system manager from
 * binding and enabling the lower saps uncomment the following flag */
/* #define IT_DIS_SAP  */

/************** section NOT to be changed by CUSTOMERS **********/
/* needed dependencies */
#ifdef LCMXUISDT
#ifndef LCSDT
#define LCSDT 1
#endif
#endif

#ifdef LCMXMILMX
#ifndef LCLMX
#define LCLMX 1
#endif
#endif

#ifdef LCMXLISCT
#ifndef LCSCT
#define LCSCT 1
#endif
#endif

#endif /* MX */

/***************************************************************************
                         End of M2PA Section
 ****************************************************************************/

/****************************************************************************
                       End of SIGTRAN Stack Section
****************************************************************************/


/**************************************************************************
                       MPLS-LDP(+CR) Section
**************************************************************************/
#ifdef LN       /* MPLS - LDP(+CR)  */

/*** Interfaces Coupling Options ***/

/* upper interface,choose none or more */

/* #define LCLNUIRAI  1   loosely coupled with RAI layer */

/* lower interface,choose none or more */

/* #define LCLNLIHIT  1   loosely coupled with TUCL layer  */

/* #define LCLNLIIFP  1   loosely coupled with MPLS forwarder */

/* #define LCLNLIARI  1   loosely coupled with authentication,routing layer */

/* #define LCLNLIRLS  1  loosely coupled with Resource Manager layer */

/* Management interface , choose none or more */

/* #define LCLNMILLN  1  loosely coupled with layer manager */

/* interface flags, automatically chosen */

#ifdef LCLNMILLN
#ifndef LCLLN
#define LCLLN    1 /* loosely coupled, LLN interface */
#endif
#endif

#ifdef LCLNUIRAI
#ifndef LCRAI
#define LCRAI     1 /* loosely coupled, RAI interface */
#endif           /* LCRAI */
#endif           /* LCLNUIRAI */

#ifdef LCLNLIHIT
#ifndef LCHIT
#define LCHIT     1 /* loosely coupled, HIT interface */
#endif           /* LCHIT */
#endif           /* LCLNLIHIT */


#ifdef LCLNLIIFP
#ifndef LCIFP
#define LCIFP     1 /* loosely coupled, IFP interface */
#endif           /* LCIFP */
#endif           /* LCLNLIIFP */


#ifdef LCLNLIARI
#ifndef LCARI
#define LCARI     1 /* loosely coupled, ARI interface */
#endif           /* LCARI */
#endif           /* LCLNLIARI */


#ifdef LCLNLIRLS
#ifndef LCRLS
#define LCRLS     1 /* loosely coupled, RLS interface */
#endif           /* LCRLS */
#endif           /* LCLNLIRLS */

#if (defined(LCLLN) || defined(LCRAI) || defined(LCHIT) || defined(LCIFP) || defined(LCRLS) || defined(LCARI))
#ifndef LCATM
#define LCATM 1
#endif
#endif

#endif          /* LN */
/****************************************************************************
                       End of MPLS -LDP(+CR) Section
****************************************************************************/

/**************************************************************************
                      MPLS - Service User Layer Section
**************************************************************************/
#ifdef LA       /* MPLS - Service User */

/*** Interfaces Coupling Options ***/

/* lower interface,choose none or more */

/* #define LCLALIRAI  1   loosely coupled */

/* interface flags, automatically chosen */

#ifdef LCLALIRAI
#ifndef LCRAI
#define LCRAI    1
#endif
#endif

#endif          /* LA */
/****************************************************************************
                     End of MPLS -  Service User Section
****************************************************************************/

/**************************************************************************
                     MPLS Forwarder Section
**************************************************************************/
#ifdef FW       /* MPLS forwarder */

/*** Interfaces Coupling Options ***/

/* lower interface,choose none or more */

/* #define LCFWUIIFP  1   loosely coupled with MPLS forwarder */

/* interface flags, automatically chosen */

#ifdef LCFWUIIFP
#ifndef LCIFP
#define LCIFP   1
#endif
#endif
#endif          /* FW */

/****************************************************************************
                      End of MPLS Forwarder Section
****************************************************************************/

/**************************************************************************
                     MPLS Resource Manager Section
**************************************************************************/
#ifdef LT       /* MPLS Resource Manager */

/*** Interfaces Coupling Options ***/

/* lower interface,choose none or more */

/* #define LCLTUIRLS  1    loosely coupled with MPLS Resource Manager */

/* interface flags, automatically chosen */

#ifdef LCLTUIRLS
#ifndef LCRLS
#define LCRLS   1
#endif
#endif
#endif          /* LT */

/****************************************************************************
                      End of MPLS Resource Manager Section
****************************************************************************/

/**************************************************************************
                      3GPP-RLC Section
**************************************************************************/
#ifdef RL
#undef RL
#define RL 1


/******************* section to be changed by CUSTOMERS ******************/

/* interfaces */
/* upper interface, choose none or more */
#define LCRLUIRLU     /*loosely coupled, RLC upper layer RLU interface */
#define LCRLUICRL     /* loosely coupled, RLC upper layer CRL interface */

/* lower interface,  choose none or more */
#define LCRLLIMKU     /* loosely coupled, MAC lower layer */

/* Management interface choose none or more */
#define LCRLMILRL     /* loosely coupled with layer manager */
#define LCRRLIRLU     /*loosely coupled with RRC Lower Interface RLU */
#define LCRRLICRL     /*loosely coupled with RRC Lower Interface CRL */
#define RLC_R6   1        /* RLC release 6 */
#define RLC_R7   1        /* RLC release 7 */

/*#define MK_IUR_SUP        Need to enable if DRNC is enabled in MAC */

#ifndef LMINT3
#define LMINT3
#endif

/* #define RL_CUSTOM_HOOK       customer hook for ciphering function */

/* RLC Debug flag to enable all debug printing from the start */
#ifdef DEBUGP
#define RL_DEBUG 1
#endif

/* RLC Alarm flag to enable alarms from the beginning */
#define RL_USTA  1

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCRLMILRL
#ifndef LCLRL
#define LCLRL    1 /* loosely coupled, LRL interface */
#endif /* LCLRL */
#endif /* LCRLMILRL */

#ifdef LCRLUIRLU
#ifndef LCRLU
#define LCRLU     1 /* loosely coupled, RLU interface */
#endif           /* LCRLU */
#endif           /* LCRLUIRLU */

#ifdef LCRLUICRL
#ifndef LCCRL
#define LCCRL     1 /* loosely coupled, CRL interface */
#endif           /* LCCRL */
#endif           /* LCRLUICRL */

#ifdef LCRLLIMKU
#ifndef LCMKU
#define LCMKU     1 /* loosely coupled, MKU  interface */
#endif           /* LCMKU */
#endif           /* LCRLLIMKU */


#endif          /* RL */
/****************************************************************************
                     End of 3GPP-RLC Section
****************************************************************************/

/**************************************************************************
                      3GPP-RRC Section
**************************************************************************/
#ifdef RR
#undef RR
#define RR 1

/* #define RR_RNC 1 */

/******************* section to be changed by CUSTOMERS ******************/

/* interfaces */
/* upper interface, choose none or more */
/*  #define LCRRUIRRU   loosely coupled, RRC upper layer RRU interface */

/* lower interface,  choose none or more */

/* #define LCRRLICRL  loosely coupled, CRL lower layer */
/* #define LCRRLIRLU  loosely coupled, RLU lower layer */
/* #define LCRRLICTC  loosely coupled, CTC lower layer */
/* #define LCRRLICMK  loosely coupled, CMK lower layer */
/* #define LCRRLIMKU  loosely coupled, MKU lower layer */

/* Management interface , choose none or more */
/* #define LCRRMILRR     loosely coupled with layer manager */


/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCRRMILRR
#ifndef LCLRR
#define LCLRR 1
#endif
#endif


#ifdef LCRRUIRRU
#ifndef LCRRU
#define LCRRU 1
#endif
#endif


#ifdef LCRRLICRL
#ifndef LCCRL
#define LCCRL 1
#endif
#endif

#ifdef LCRRLICTC
#ifndef LCCTC
#define LCCTC 1
#endif
#endif

#ifdef LCRRLICMK
#ifndef LCCMK
#define LCCMK 1
#endif
#endif

#ifdef LCRRLIRLU
#ifndef LCRLU
#define LCRLU     1 /* loosely coupled, RLU interface */
#endif           /* LCRLU */
#endif           /* LCRRLIRLU */

#ifdef LCRRLIMKU
#ifndef LCMKU
#define LCMKU     1 /* loosely coupled, RLU interface */
#endif           /* LCMKU */
#endif           /* LCRRLIMKU */

#endif          /* RR */

/**************************************************************************
                      3GPP-TC Section
**************************************************************************/
#ifdef TC
#undef TC
#define TC 1


/******************* section to be changed by CUSTOMERS ******************/

#ifndef LMINT3
#define LMINT3
#endif

/* product specific flags introduced in RLC release 1.2 */

/* PDCP Debug flag to enable all debug printing from the start */
#define TC_DEBUG 1

/* PDCP Alarm flag to enable alarms from the beginning */
#define TC_USTA  1

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

/*#ifdef TCTCMILTC*/
#ifdef TC
#ifndef TC
#define TC    1 /* loosely coupled, LTC interface */
#endif /* LCLTC */
#endif /* LCTCMILTC */

#ifdef LCTCUITCU
#ifndef LCTCU
#define LCTCU     1 /* loosely coupled, TCU interface */
#endif           /* LCTCU */
#endif           /* LCTCUITCU */

#ifdef LCTCUICTC
#ifndef LCCTC
#define LCCTC     1 /* loosely coupled, CTC interface */
#endif           /* LCCTC */
#endif           /* LCTCUICTC */

#ifdef LCTCLIRLU
#ifndef LCTCU
#define LCTCU     1 /* loosely coupled, RLU  interface */
#endif           /* LCRLU */
#endif           /* LCTCLIRLU */


#endif          /* TC */
/****************************************************************************
                     End of 3GPP-PDCP Section
****************************************************************************/




/**************************************************************************
                      3GPP-XX Section
**************************************************************************/
#ifdef XX
#undef XX
#define XX 1

/******************* section to be changed by CUSTOMERS ******************/

/* interfaces */
/* upper interface, choose none or more */

/* lower interface,  choose none or more */
/* #define LCXXLIRRU  loosely coupled, XX lower layer */

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCXXLIRRU
#ifndef LCRRU
#define LCRRU 1
#endif
#endif

#endif          /* XX */

#ifdef RR_UE
/**************************************************************************
                      3GPP-PH Section
**************************************************************************/
#ifdef PH
#undef PH
#define PH 1

/******************* section to be changed by CUSTOMERS ******************/

/* interfaces */
/* upper interface, choose none or more */
/* #define LCPHUICPH  loosely coupled, CPH upper layer */

/* #define LCPHUIPHU  loosely coupled, PHU upper layer */

/* lower interface,  choose none or more */

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCPHUICPH
#ifndef LCCPH
#define LCCPH 1
#endif
#endif

#ifdef LCPHUIPHU
#ifndef LCPHU
#define LCPHU 1
#endif
#endif

#endif          /* PH */

/**************************************************************************
                      3GPP-UH Section : MAC-HS User 
**************************************************************************/
#ifdef UH
#undef UH
#define UH 1

/******************* section to be changed by CUSTOMERS ******************/

/* interfaces */
/* lower interface,  choose none or more */
/* #define LCUHLIMDU  loosely coupled, MDU lower layer */

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCUHLIMDU
#ifndef LCMDU
#define LCMDU 1
#endif
#endif

#endif          /* UH */

/**************************************************************************
                      3GPP-CH Section : Node-B Application 
**************************************************************************/
#ifdef CH
#undef CH
#define CH 1

/******************* section to be changed by CUSTOMERS ******************/

/* interfaces */
/* lower interface,  choose none or more */
/* #define LCCHLICMD  loosely coupled, MDU lower layer */

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCCHLICMD
#ifndef LCCMD
#define LCCMD 1
#endif
#endif

#endif          /* CH */
/**************************************************************************
                      3GPP-US Section
**************************************************************************/
#ifdef US
#undef US
#define US 1

/******************* section to be changed by CUSTOMERS ******************/

/* interfaces */
/* upper interface, choose none or more */
/* #define LCUSUICUS  loosely coupled, CPH upper layer */

/* lower interface,  choose none or more */

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCUSUICUS
#ifndef LCCUS
#define LCCUS 1
#endif
#endif

#endif          /* US */

#endif          /* RR_UE */ 
/**************************************************************************
                      3GPP-BM Section
**************************************************************************/
#ifdef BM
#undef BM
#define BM 1

/******************* section to be changed by CUSTOMERS ******************/

/* interfaces */
/* upper interface, choose none or more */
/* #define LCBMUICBM  loosely coupled, CPH upper layer */

/* lower interface,  choose none or more */

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCBMUICBM
#ifndef LCCBM
#define LCCBM 1
#endif
#endif

#endif          /* BM */

/**************************************************************************
                      3GPP-PD Section
**************************************************************************/
#ifdef PD
#undef PD
#define PD 1

/******************* section to be changed by CUSTOMERS ******************/

/* interfaces */
/* upper interface, choose none or more */
/* #define LCPDUICPD  loosely coupled, CPH upper layer */

/* lower interface,  choose none or more */

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCPDUICPD
#ifndef LCCPD
#define LCCPD 1
#endif
#endif

#endif          /* PD */

/**************************************************************************
                      S1AP Section
**************************************************************************/
#ifdef SZ
#undef SZ
#define SZ 1


/******************* section to be changed by CUSTOMERS ******************/

/* product options */
/* SZ_MME - MME variant of S1AP */
/* SZ_ENB - EnodeB variant of S1AP */

/* interfaces */
/* upper interface, choose none or more */
/* #define LCSZUISZT     loosely coupled, SZ upper layer SZT interface */
/* #define LCSZLISCT     loosely coupled, SZ lower layer SCT interface */
/* #define LCSZMILSZ     loosely coupled, SZ manegement layer LSZ interface */
/* #define LCSZLISCT     loosely coupled, SZ lower layer SCT interface */


/* #define LWLCSZT       light weight loosely coupled, SZ upper layer SZT interface */

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCSZUISZT
#ifndef LCSZT
#define LCSZT    1 /* loosely coupled, SZT interface */
#endif /* LCSZT */
#endif /* LCSZUISZT */

#ifdef LCSZMILSZ
#ifndef LCLSZ
#define LCLSZ    1 /* loosely coupled, LSZ interface */
#endif /* LCLSZ */
#endif /* LCSZMILSZ */

#endif          /* SZ */
/****************************************************************************
                     End of S1AP Section
****************************************************************************/

/**************************************************************************
                      PSF - S1AP Section
**************************************************************************/
#ifdef YT
#undef YT
#define YT 1

/******************* section to be changed by CUSTOMERS ******************/
/* Interface coupling flag */
/* #define LCYTMILYT loosely coupled, SZ to LM interface */
/* #define LCSMYTMILYT  lossely coupled, SZ to SM interface */

/* #define LYTV1 1  Layer manager interface version */

/******************* section NOT to be changed by CUSTOMERS ******************/
#ifdef LCYTMILYT
#ifdef LCLYT
#undef LCLYT
#endif /* LCLYT */
#define LCLYT 1
#endif /* LCYTMILYT */

#ifdef SZ_RUG

#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "SZ_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
#ifndef SZ_FTHA
#define SZ_FTHA 1
#endif /* ifndef SZ_FTHA */
#endif /* SZ_RUG */

#ifndef CM_PSF_MBUF_USAGE
#define CM_PSF_MBUF_USAGE  /* Common PSF usage */
#endif /* CM_PSF_MBUF_USAGE */

#endif /* YT */

/****************************************************************************
                     End of PSF - S1AP Section
****************************************************************************/

/**************************************************************************
                      Iuh Section
**************************************************************************/
#ifdef HM

/******************* section to be changed by CUSTOMERS ******************/ 
/* These options can be enabled in the make file also */
/* #define LCHMUIRUT        loosely coupled RUT Interface User */
/* #define LCHMUIHNT        loosely coupled HNT Interface User */
/* #define LCHMLISCT        loosely coupled transport layer Interface */
/* #define LCHMMILHM        loosely coupled Iuh to stack manager 
                              Also enable LCSMHMMILHM under #ifdef SM */

/* #define  CMINETDBG       enable socket debugging supprt */

/* #define  DEBUGP          enable to turn ON debug support */
/* #define  NO_ERRCLS       enable to compile out error class checking */

/*#define HM_HNB */
/*#define SCT7 */

#if (defined(LCHMMILHM) || defined(LCSMHMMILHM))
#ifndef LCLHM
#define LCLHM 1
#endif
#endif

#if (defined(LCHMLISCT) || defined(LCSBUISCT))
#ifndef LCSCT
#define LCSCT 1
#endif
#endif

#if (defined(LCHMUIRUT) || defined(LCRALIRUT))
#ifndef LCRUT
#define LCRUT 1
#endif
#endif

#if (defined(LCHMUIHNT) || defined(LCHXLIHNT))
#ifndef LCHNT
#define LCHNT 1
#endif
#endif


/*************** section not to be changed by CUSTOMERS ******************/

/****************************************************************************
                     End of Iuh Signaling Protocols Section
****************************************************************************/

#endif /* HM */
/****************************************************************************
                     End of S1AP Section
****************************************************************************/
/**************************************************************************
                     AAL2 Signaling Layer Parameters
**************************************************************************/
#ifdef AL       /* AAL Protocol  */

/*** Interfaces Coupling Options ***/

/* loosely coupled interface flags */

/* #define LCALUIALT         loosely coupled with AAL2 service user layer  */

/* #define LCALLIASD         loosely coupled with QSAAL layer  */

/* #define LCALLIASI         loosely coupled with QSAAL layer  */

/* #define LCALLISNT         loosely coupled with MTP3B layer  */

/* Management interface , choose none or more */

/* #define LCALMILAL       loosely coupled with layer manager */

/*#define SNT2                  SNT interface flag */
/*#define ASI2                  ASI interface flag */
/*#define ASD2                  ASD interface flag */ 
/****************************** Interfaces Version Flags ******************/

/* Upper interface */
/* #define ALTV1             Upper interface version 1.0 */

/* Lower interfaces */
/* #define SNTV1             Lower interface version 1.0 */
/* #define ASDV1             Lower interface version 1.0 */
/* #define ASIV1             Lower interface version 1.0 */

/* LM interface */
/* #define LALV1             Layer Management interface version 1.0 */



/* Product options */

/* STC-SSCOP */
/* #define    AL_OPTS_SSCOP              signaling converter for SSCOP */

/* STC-MTP3B */
/* #define    AL_OPTS_MTP3B              signaling converter for MTP3B */

/* Interface with QSAAL at Q.2110 interface (ASI) */
/* #define    AL_OPTS_ACCESS_Q2110       access q2110 interface */

/* Array indexing */
/* #define    AL_OPT_CONNCB_ARR          array indexing */

/* Capability set - only one can be defined */
/* #define AAL2_CS2 */
/* #define AAL2_CS3 */

/*#define AL_FTHA               FTHA */
/*#define AL_RUG                RUG */

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCALMILAL
#ifndef LCLAL
#define LCLAL    1 /* loosely coupled, LAL interface */
#endif
#endif

#ifdef LCALUIALT
#ifndef LCALT
#define LCALT     1 /* loosely coupled, ALT interface */
#endif           /* LCALT */ 
#endif           /* LCALUIALT */

#ifdef LCALLIASD
#ifndef LCASD
#define LCASD     1 /* loosely coupled, ASD interface */
#endif           /* LCASD */ 
#endif           /* LCALLIASD */

#ifdef LCALLIASI
#ifndef LCASI
#define LCASI     1 /* loosely coupled, ASI interface */
#endif           /* LCASI */ 
#endif           /* LCALLIASI */

#ifdef LCALLISNT
#ifndef LCSNT
#define LCSNT     1 /* loosely coupled, SNT interface */
#endif           /* LCSNT */ 
#endif           /* LCALLISNT */

#if (LCLAL || LCALT || LCASD || LCASI)
#ifndef LCATM
#define LCATM 1
#endif
#endif

/* Rolling Upgrade compliance */

/* Check for TDS_ROLL_UPGRADE_SUPPORT */
#ifdef AL_RUG
#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "AL_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
#endif /* AL_RUG */

/* Check for AL_FTHA  */
#ifdef AL_RUG
#ifndef AL_FTHA
#error "AL_FTHA flag is mandatory for Rolling Upgrade. Please enable"
#endif /* AL_FTHA */
#endif /* AL_RUG */

/* End of dependency checking for Rolling Upgrade */

#endif          /* AL */
/**************************************************************************
                  End of AAL2 Signaling Layer Parameters
**************************************************************************/


#ifdef ZL       /* PSF-AAL2 (FT/HA) */
/**************************************************************************
   PSF-AAL2 (FT/HA) parameters
**************************************************************************/
#undef ZL
#define ZL 1

/*********************************interfaces******************************/

/* #define LCZLMILZL       loosely coupled, layer management interface */

/*********************************Misc Flags******************************/

/* #define ZL_USTA       enable alarms by default */
/* #define ZL_DEBUG      enable debug prints by deault (only for debugging) */

/****************************** Interfaces Version Flags ******************/

/* Peer interface */
/*#define ZLPV1               Peer interface version 1.0 */

/* Layer management interface */
/*#define LZLV1               Layer Management interface version 1.0 */

/* dependency of ZL and AL_FTHA */
#ifndef AL_FTHA
#define AL_FTHA
#endif

/* These flags must not be turned-off for PSF-ALCAP */

#ifdef LCZLMILZL
#ifdef LCLZL
#undef LCLZL
#endif
#define LCLZL    1
#endif /* LCZLMILZL */

#endif /* ZL */

/**************************************************************************
                      AAL2 Signaling Service User
**************************************************************************/
#ifdef AA       /* Service User - AAL2 Signaling */

/*** Interfaces Coupling Options ***/

/* interface flags */

/* #define LCAALIALT       loosely coupled with Resource Manager */

/* interface flags, automatically chosen */

#ifdef LCAALIALT
#ifndef LCALT
#define LCALT    1
#endif
#endif

#endif          /* AA */
/****************************************************************************
                     End of AAL2 Signaling Service User
****************************************************************************/

/******************************************************************/
/* SUA Layer                                                     */
/******************************************************************/

#ifdef SU
#undef SU
#define SU 1

/******************* section to be changed by CUSTOMERS ******************/

/* Product options, choose one or more depending on the license agreement.
 * Please check your license agreement before enabling any of the following
 * flags.
 */

/* #define SUASP   ASP function of SUA */
/* #deifne SUSG    SG function of  SUA */
/* #define NP      NIF of SUA */

/* For Fault Tolerant, High Availability interface support */
#ifndef SU_FTHA
#define SU_FTHA 
#endif

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCSUUISPT        loosely coupled, SUA upper layer */

/* lower interface, data link, choose none or more */

/* #define LCSULISCT     loosely coupled, lower layer */

/* management interface, lit , choose none or more */

/* #define LCSUMILSU       loosely coupled, layer management */

/* #define SU_RUG        Rolling upgrade support enabled */

#ifndef SUAP_IPOPT
/*#define SUAP_IPOPT  */        /* To enable SuaAddr in cm_ss7.x */
#endif


/*** Interface Backward Compatiblity Options: flags should be turned
     off for backward comatibility  ***/

#ifndef SU_LMINT3
#define SU_LMINT3          /* new management interface. turning off
                              requires SMIT_LMINT3 flag also to be
                              turned off in #ifdef SM section */
#endif

#ifndef CM_INET2
#define CM_INET2           /* Support for latest internet support */
#endif

#ifndef SPCO
#define SPCO  1
#endif

#ifndef SPT2
#define SPT2  1
#endif

#ifndef L3VER2
#define L3VER2
#endif

#ifndef CMFILE_REORG_1
#define CMFILE_REORG_1
#endif

#ifndef CMFILE_REORG_2
#define CMFILE_REORG_2
#endif

/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */

/*  If the management interface is loosely coupled in any of the two 
 *  directions, then define the general loosely coupled 
 *  flag (LCLSU) 
 */

#ifdef LCSUMILSU

#ifndef LCLSU
#define LCLSU 1
#endif /* LCLSU */

#endif /* LCSUMILSU */

#ifdef LCSMSUMILSU

#ifndef LCLSU
#define LCLSU 1
#endif /* LCLSU */

#endif /* LCSMSUMILSU */

/* SUA NIF layer loosely coupled */
#ifdef LCNPMILNP

#ifndef LCLNP
#define LCLNP 1
#endif /* LCLNP */

#endif /* LCSUMILSU */

#ifdef LCSMNPMILNP

#ifndef LCLNP
#define LCLNP 1
#endif /* LCLNP */

#endif /* LCSMNPMILNP */


/*  If the upper interface is loosely coupled in any of the two 
 *  directions, then define the general loosely coupled 
 *  flag (LCSPT) 
 */

#ifdef LCSUUISPT

#ifndef LCSPT
#define LCSPT 1
#endif /* LCSNT */

#endif /* LCSUUISPT */

#ifdef LCNPLISPT

#ifndef LCSPT
#define LCSPT 1
#endif /* LCSNT */

#endif /* LCNPLISPT */

#ifdef LCRALISPT

#ifndef LCSPT
#define LCSPT 1
#endif /* LCSNT */

#endif /* LCRALISPT */

#ifdef LCSTLISPT

#ifndef LCSPT
#define LCSPT 1
#endif /* LCSNT */

#endif /* LCSTLISPT */

/*  If the lower interface is loosely coupled in any of the two 
 *  directions, then define the general loosely coupled 
 *  flag (LCSCT) 
 */
#ifdef LCSULISCT

#ifndef LCSCT
#define LCSCT 1
#endif /* LCSCT */

#endif /* LCSULISCT */

#ifdef LCSBUISCT

#ifndef LCSCT
#define LCSCT 1
#endif /* LCSCT */

#endif /* LCSBUISCT */



#ifdef SU_LMINT3
#undef SU_LMINT3
#define SU_LMINT3   1
#endif /* SU_LMINT3 */


#ifdef SU_RUG

#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "SU_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif
#ifndef SU_FTHA
#define SU_FTHA 1
#endif /* ifndef SU_FTHA */
#endif /* SU_RUG */

#endif /* SU */

#ifdef NP
#undef NP
#define NP 1

/******************* section to be changed by CUSTOMERS ******************/
/*** Interfaces Coupling Options ***/

/* lower interface SPT , choose none or one */
/*#define LCNPLISPT     loosely coupled SPT interface */

/* management interface, lnp , choose none or one */
/*#define LCNPMILNP     loosely coupled, layer management */

/* For Fault Tolerant, High Availability interface support */
/* #define NP_FTHA */

/* To be enabled when SCCP supports new interworking primitives on SPT
 * interface.
 * Note: SCCP ver 3.1 has old interworking primitives */
/* #define SPT_NM_IW */

/*** Interface Backward Compatiblity Options: flags should be turned
     off for backward comatibility  ***/

#ifndef NP_LMINT3
#define NP_LMINT3          /* new management interface. turning off
                              requires SMIT_LMINT3 flag also to be
                              turned off in #ifdef SM section */
#endif

#ifndef NP_FTHA
#define NP_FTHA            /* For Fault Tolerant, High Availability
                              support */
#endif

#ifndef SPT2
#define SPT2  1
#endif

#ifndef L3VER2
#define L3VER2
#endif

#ifndef CMFILE_REORG_1
#define CMFILE_REORG_1
#endif

#ifndef CMFILE_REORG_2
#define CMFILE_REORG_2
#endif

/************** section NOT to be changed by CUSTOMERS **********/

/*  If the layer manager  interface is loosely coupled in any of the two 
 *  directions, then define the general loosely coupled 
 *  flag (LCLNP) 
 */

#ifdef LCNPMILNP

#ifndef LCLNP
#define LCLNP 1
#endif /* LCLNP */

#endif /* LCNPMILNP */

#ifdef LCSMNPMILNP

#ifndef LCLNP
#define LCLNP 1
#endif /* LCLNP */

#endif /* LCSMNPMILNP */

/*  If the lower  interface is loosely coupled in any of the two 
 *  directions, then define the general loosely coupled 
 *  flag (LCSPT) 
 */

#ifdef LCNPLISPT

#ifndef LCSPT
#define LCSPT 1
#endif /* LCSPT */

#endif /* LCNPLISPT */

#ifdef LCRALISPT

#ifndef LCSPT
#define LCSPT 1
#endif /* LCSPT */

#endif /* LCNPLISPT */

#ifdef LCSTLISPT

#ifndef LCSPT
#define LCSPT 1
#endif /* LCSPT */

#endif /* LCNPLISPT */


#ifdef LCSUUISPT

#ifndef LCSPT
#define LCSPT 1
#endif /* LCSPT */

#endif /* LCSUUISPT */

#ifdef LCSPUISPT

#ifndef LCSPT
#define LCSPT 1
#endif /* LCSPT */

#endif /* LCSPUISPT */



#ifdef NP_LMINT3
#undef NP_LMINT3
#define NP_LMINT3   1
#endif /* NP_LMINT3 */

#ifndef SPTIWF
#define SPTIWF 1
#endif

#endif /* NP */

/****************************************************************************
                     End of SUA and SUA-NIF Section
****************************************************************************/

#ifdef AH  /* LDF - SUA */
/****************************************************************************
   LDF - SUA flags
****************************************************************************/
#undef AH
#define AH 1

#define CMSS7_SPHDROPT   /* header option. Enable this flag for
                          * the upper layers of SCCP  as well.
                          */
                          
/* #define  SUSG  1       SUA works as SGP */

#ifndef SPCO
#define SPCO 1
#endif                     /* Connection oriented services required */

/* #define AH_DEBUG      Enable debug at initialization */

/* #define AH_USTA       Enable alarms at initialization */

/* #define AH_PT_HOOK    Portable Hooks */

#undef AH_RUG        /* Rolling upgrade support enabled */

/****************************** Interfaces Version Flags ******************/

/* SUA Upper interface */
#ifndef SPTV2_1
#define SPTV2_1 1
#endif

/* SUA lower interface */
#ifndef SCTV2
#define SCTV2 1
#endif

/* Layer management interface */
#ifndef LAHV1
#define LAHV1
#endif

/******************* section not to be changed by CUSTOMERS ******************/
#ifndef SS7
#define SS7
#endif

/*
* MUST define AH_ULDF and/or AH_LLDF.
* If (AH_ULDF not defined) and (AH_LLDF not defined)
* then LDF assumes that it acts as both ULDF and LLDF
*/

#ifndef AH_ULDF
#ifndef AH_LLDF
#define AH_ULDF  1       /* LDF acts as Upper load distribution function */
#define AH_LLDF  1       /* LDF acts as Lower load distribution function */
#endif /* AH_LLDF */
#endif /* AH_ULDF */

#ifndef SCT2
#define SCT2
#endif /* SCT2 */

#ifndef SPT2
#define SPT2
#endif /* SPT2 */

/* Loosed coupled management interface */
#if (defined(LCAHMILAH) || defined(LCSMAHMILAH))
#ifndef LCLAH
#define LCLAH 1
#endif
#endif

/* Loosely coupled SPT interface */
#if (defined(LCAHLISPT) || defined(LCSPUISPT))
#ifndef LCSPT
#define LCSPT 1
#endif
#endif

/* Loosely coupled SCT interface */
#if (defined(LCAHUISCT) || defined(LCSCLISCT))
#ifndef LCSCT
#define LCSCT 1
#endif
#endif

/* SCT & SPT Loosely coupled Interface function are used */
#ifndef LCSCT
#define LCSCT 1
#endif

#ifndef LCSPT
#define LCSPT 1
#endif

/**************** Define dependency checks (DO NOT CHANGE!!) *****************/
#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#error "Rolling upgrade feature available in CORE II only."
#endif
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

#ifdef AH_RUG

#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "AH_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif

#endif /* AH_RUG */

#endif /* AH */


/**************************************************************************
                        PSF-SUA (DFT/HA) parameters
**************************************************************************/
#ifdef AE      /* PSF-SUA */
#undef AE
#define AE 1

/*
 ************************** Interfaces Coupling Options ******************
 */

/* enable following options depending upon coupling requirements */
/*   #define LCAEMILAE    loosely coupled, management i/f of SUA */
/*   #define LCSMAEMILAE  loosely coupled, SM i/f */

/*
 ************************** Interface Version ****************************
 */
#define LAEV1     /* Layer manager interface version */
#define AEPV1     /* Peer interface version */

/*
 ************************** LM Configuration  ***************************
 */

#define AE_USTA      /* enable alarms by default */
/*-- #define AE_DEBUG     enable debug prints by deault (only for debugging) */

/*
 ********************* INTERNAL FLAGS (Do not modify!) *******************
 */

#ifndef CM_PSF_MBUF_USAGE
#define CM_PSF_MBUF_USAGE  /* Common PSF usage */
#endif


#ifndef CMPSF_EARLY_CFM_IN_GO_ACTIVE
#define CMPSF_EARLY_CFM_IN_GO_ACTIVE
#endif

#ifdef AE_DFTHA

#ifndef CMPSF_DFTHA
#define CMPSF_DFTHA
#endif

#endif /* AE_DFTHA */

#ifdef LCAEMILAE
#ifdef LCLAE
#undef LCLAE
#endif
#define LCLAE 1
#endif /* LCAEMILAE */

/*
#ifndef SU_FTHA
#error "Define SU_FTHA in SU section of envopt.h"
#endif
*/

#ifndef TDS_CORE2
#error "Please define TDS_CORE2 in make file"
#endif

#endif /* AE */

/****************************************************************************
                     End of SUA and SUA-NIF Section
****************************************************************************/

/****************************************************************************
                     3GPP-MAC Section
****************************************************************************/
#ifdef MK 
#undef MK 
#define MK 1


/******************* section to be changed by CUSTOMERS ******************/

/* interfaces */
/* upper interface, choose none or more */
#define LCMKUIMKU        /*loosely coupled, MAC upper layer MKU interface */

#define LCMKUICMK       /* loosely coupled, MAC upper layer CMK interface */

#define LCMKUIMKD       /* loosely coupled, MAC upper layer MKD interface */

/* lower interface,  choose none or more */
#define LCMKLIPHU       /*loosely coupled, MAC lower layer PHU interface */
#define LCMKLIFPU       /* loosely coupled, MAC lower layer PHU interface */

#define LCFPUIFPU       /* loosely coupled, FP upper layer */

/* Management interface , choose none or more */
#define LCMKMILMK       /*loosely coupled, MAC layer manager LMK interface */
#define LCSMMKMILMK

/* #define MK_NODEB 1 */  /* To compile MAC on node B, else it is RNC */

#ifndef MK_NODEB

#define MK_HSDPA  1   /* Rel 5 feature */

#ifdef MK_HSDPA
#define MK_EHS  1       /* Rel 6/7 feature - requires MK_HSDPA */
#endif
#define MK_HSUPA  1  /* Rel 6/7 feature */
#define MK_MBMS   1      /* Rel 6/7 feature */

#define MK_IUR_SUP 1 /* IUR support */


#if defined(MK_EHS) || defined(MK_HSUPA) || defined(MK_IUR_SUP)
#define FP_RELEASE6 1    /* Use FP_RELEASE5 if no rel 6/7 feature used */
#else
#define FP_RELEASE5 1
#endif

#define CCPU_MAC_OPT 1
#define MK_SEL_TFC 1

#ifdef MK_IUR_SUP
#ifndef FP_IUR
#define FP_IUR
#endif
#endif

#endif /* not MK_NODEB */

/* Turn on MAC specific level 3 debug prints */
#ifdef DEBUGP
/*#define MKDBGL3 */  /* requires DEBUGP */
#endif


/* TCR20: Rolling Upgrade Support  */
#define CMKV1   /* CMK Upper interface version 1.0 */
#define MKUV1   /* MKU Upper interface version 1.0 */
#define FPUV1   /* FPU Lower interface version 1.0 */
#define PHUV1   /* PHU Lower interface version 1.0 */
#define LMKV1   /* Layer Management interface version 1.0 */


/**************** Define dependency checks (DO NOT CHANGE!!) *****************/
#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#error "Rolling upgrade feature available in CORE II only."
#endif
#endif

#ifdef MK_RUG
#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "MK_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif
#endif

#ifdef MK_RUG
#ifndef MKT2
#error "MKT2 flag is mandatory for rolling upgrade. Please enable"
#endif
#endif
   

#ifndef LMINT3
#define LMINT3
#endif

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCMKUIMKU
#ifndef LCMKU
#define LCMKU 1 /* loosely coupled, MKU interface */
#endif /* LCMKU */
#endif /* LCMKUIMKU */

#ifdef LCMKUICMK
#ifndef LCCMK
#define LCCMK 1 /* loosely coupled, CMK interface */
#endif /* LCCMK */
#endif /* LCMKUICMK */

#ifdef MK_IUR_SUP
#ifdef LCMKUIMKD
#ifndef LCMKD
#define LCMKD 1 /* loosely coupled, MKD interface */
#endif /* LCMKD */
#endif /* LCMKUIMKD */

#ifdef LWLCMKUIMKD
#ifndef LWLCMKD
#define LWLCMKD 1 /* light weight,loosely coupled, MKD interface */
#endif /* LWLCMKD */
#endif /* LWLCMKUIMKD */
#endif /* MK_IUR_SUP */

#ifdef LCMKLIPHU
#ifndef LCPHU
#define LCPHU 1 /* loosely coupled, PHU interface */
#endif /* LCPHU */
#endif /* LCMKLIPHU */

#ifdef LCMKLIFPU
#ifndef LCFPU
#define LCFPU 1 /* loosely coupled, FPU interface */
#endif /* LCFPU */
#ifndef LCAAL
#define LCAAL 1
#endif /* LCAAL */
#ifndef LCATM
#define LCATM 1
#endif /* LCATM */
#endif /* LCMKLIFPU */

#ifdef LCMKMILMK
#ifndef LCLMK
#define LCLMK 1 /* loosely coupled, LMK interface */
#endif /* LCLMK */
#endif /* LCMKMILMK */


#endif /* MK */

/****************************************************************************
                     End of 3GPP-MAC Section
****************************************************************************/
/****************************************************************************
                     MAC-HS Section
****************************************************************************/
#ifdef MD 
#undef MD 
#define MD 1
#define MD_MAC_EHS 1
#define MD_MAC_E 1
#define MD_T1_DELAY_TIMERS 1

/******************* section to be changed by CUSTOMERS ******************/

/* interfaces */
/* upper interface, choose none or more */
#define LCMDUIMDU        /*loosely coupled, MAC upper layer MDU interface */
#define LCUHLIMDU    /*loosely coupled, MAC lower layer */

#define LCMDUICMD       /* loosely coupled, MAC upper layer CMD interface */
#define LCCHLICMD    /*loosely coupled, MAC lower layer */


/* lower interface,  choose none or more */
#define LCMDLIPHU       /*loosely coupled, MAC lower layer PHU interface */
#define LCPHUIPHU       /*loosely coupled, MAC lower layer PHU interface */

/* Management interface , choose none or more */
 #define LCMDMILMD       /*loosely coupled, MAC layer manager LMD interface */

/* TCR20: Rolling Upgrade Support  */
#define CMDV1   /* CMD Upper interface version 1.0 */
#define MDUV1   /* MDU Upper interface version 1.0 */
#define PHUV1   /* PHU Lower interface version 1.0 */
#define LMDV1   /* Layer Management interface version 1.0 */

#ifndef LMINT3
#define LMINT3
#endif

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCMDUIMDU
#ifndef LCMDU
#define LCMDU 1 /* loosely coupled, MDU interface */
#endif /* LCMDU */
#endif /* LCMDUIMDU */

#ifdef LCMDUICMD
#ifndef LCCMD
#define LCCMD 1 /* loosely coupled, CMD interface */
#endif /* LCCMD */
#endif /* LCMDUICMD */

#ifdef LCMDLIPHU
#ifndef LCPHU
#define LCPHU 1 /* loosely coupled, PHU interface */
#endif /* LCPHU */
#endif /* LCMDLIPHU */

#ifdef LCMDMILMD
#ifndef LCLMD
#define LCLMD 1 /* loosely coupled, LMD interface */
#endif /* LCLMD */
#endif /* LCMDMILMD */


#endif /* MD */

/****************************************************************************
                     End of MAC-HS Section
****************************************************************************/

/******************************************************************/
/*                    FP Layer                                  */
/******************************************************************/

#ifdef FP
#undef FP
#define FP 1

/******************* section to be changed by CUSTOMERS ******************/

/* Product options, choose one or more depending on the license agreement.
 * Please check your license agreement before enabling any of the following
 * flags.
 */
/* TCR20: Rolling Upgrade Support  */
#define FPUV1   /* Upper interface version 1.0 */
#define LFPV1   /* Lower interface version 1.0 */


#ifdef TDS_ROLL_UPGRADE_SUPPORT 
#define FP_FTHA
#define FP_RUG
#define FPT2
#endif

/**************** Define dependency checks (DO NOT CHANGE!!) *****************/
#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#error "Rolling upgrade feature available in CORE II only."
#endif
#endif

#ifdef FP_RUG
#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "FP_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif
#endif

#ifdef FP_RUG
#ifndef FPT2
#error "FPT2 flag is mandatory for rolling upgrade. Please enable"
#endif
#endif


/* #define FP_NODEB * NODEB function of FP  */
/* #define FP_MULTI_THREADED * Multithreaded FP functionality*/

#ifndef HI
#define HI
#endif /* HI */

/*#define FP_MULTI_TSAP */ /* Multi TSAP */

/* Options to enable alarms/debug mask during compile time */
/* #define FP_USTA         Uncomment to enable alarms by default */
/* #define FP_DEBUG        Uncomment to enable all debug prints by default */

#define AALINT3  1       /* AAL upper interface with bind confirm*/

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LCFPUIFPU        loosely coupled, FP upper layer */

/* lower interface, data link, choose none or more */

/* #define LCFPLIAAL     loosely coupled, lower layer */

/* management interface, lfp , choose none or more */

/* #define LCFPMILFP       * loosely coupled, layer management */
/* #define LCSMFPMILFP     * stack manager loosley coupled to FP */

/* Interfaces Coupling Options required only for accepatnce tests and dummy
 * layers*/

/* #define LCAALUIAAL    * loosely coupled, upper interface for dummy AAL2 */
/* #define LCFPULIFPU    * loosely coupled, lower interface for dummy user*/
/* #define PERF_TEST     * Performance testing */

/* #define LCFPLIHIT  */
/* #define LCHIUIHIT  */

/* #define FP_IP_SUPPORT   * Support for FP over IP  */
/* #define FP_TDD          * TDD Support */
/* #define FP_RELEASE4     * Support to Release4 Specs */
/* #define FP_RELEASE5 1   * Support to Release5 Specs */
/* #define FP_IP_TESTING   * For IP testing */

/* #define FP_HSDSCH_OPT2  * For enabling HSDSCH Option 2 frame */

/* #ifndef FP_NODEB        */
/* #define FP_IUR          * Support to IUR Interface */
/* #endif */

#ifdef FP
#ifdef IPV6_SUPPORTED
#ifndef HI_REL_1_3
#define HI_REL_1_3
#endif /* HI_REL_1_3 */
#endif /* IPV6_SUPPORTED */

#ifdef HI_MULTI_THREADED
#ifndef HI_REL_1_3
#define HI_REL_1_3
#endif /* HI_REL_1_3 */
#endif /* HI_MULTI_THREADED */

#ifdef HI_REL_1_4
#ifndef HI_REL_1_3
#define HI_REL_1_3
#endif /* HI_REL_1_3 */
#endif  /* HI_REL_1_4 */

/* #define HI_REL_1_3    compile option to enable rel1.2 changes */
/* Define HI_REL_1_2 and CM_INET2 if HI_REL_1_3 is defined */
#ifdef HI_REL_1_3
#ifndef HI_REL_1_2
#define HI_REL_1_2
#endif /* HI_REL_1_2 */
#ifndef CM_INET2
#define CM_INET2
#endif /* CM_INET2 */
#endif /* HI_REL_1_3 */

#endif /* FP */
/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */
#ifdef SS_SINGLE_THREADED
#ifdef FP_MULTI_THREADED
#undef FP_MULTI_THREADED
#endif
#endif

#ifdef FP_MULTI_THREADED
#ifndef LCFPLIAAL
#define LCFPLIAAL
#endif
#ifndef LCAALUIAAL
#define LCAALUIAAL
#endif
#ifndef LCFPULIFPU
#define LCFPULIFPU
#endif
#ifndef LCFPUIFPU
#define LCFPUIFPU
#endif
#endif

#ifdef LCFPMILFP
#ifndef LCLFP
#define LCLFP 1
#endif /* LCLFP */
#endif /* LCLFPMILFP */


#ifdef LCFPUIFPU
#ifndef LCFPU
#define LCFPU 1
#endif /* LCFPU */
#endif /* LCFPUIFPU */


#ifdef LCFPLIAAL
#ifndef LCAAL
#define LCAAL 1
#endif /* LCAAL */
#ifndef LCATM
#define LCATM 1
#endif /* LCATM */
#endif /* LCFPLIATM */

#ifdef LWLCFPU
#ifdef LCFPU
#undef LCFPU
#endif
#endif

#ifdef FP_IP_SUPPORT
#ifdef LCFPLIHIT
#ifndef LCHIT
#define LCHIT 1
#endif /* LCHIT */
#endif /* LCFPLIHIT */
#endif /* FP_IP_SUPPORT */

#endif /* FP */

/****************************************************************************
                     End of FP Section
****************************************************************************/

/**************************************************************************
                     UMTS-NBAP Parameters
**************************************************************************/
#ifdef IB
#undef IB
#define IB 1

/******************* section to be changed by CUSTOMERS ******************/

/* loosely coupled upper interface flag */
/* #define LCIBUINBU       loosely coupled with NBAP service user layer  */

/* loosely coupled lower interface flag */
/* #define LCIBLIASD       loosely coupled with QSAAL layer  */

/* Management interface , choose none or more */
/* #define LCIBMILIB         loosely coupled with layer manager */


/*#define LCIBLISCT  loosely coupled  with sct layer */
/* #define LCSBUISCT */
/* product specific options */

/* #define IB_NODEB        Enable for NodeB NBAP implementation  */
/* #define IB_RNC           Enable for CRNC NBAP implementation */
/* #define IB_ENC_VALIDATE  Enable Encode validation for NBAP Msgs */

#ifndef LMINT3
#define LMINT3 
#endif

#ifndef SCT2
#define SCT2
#endif

#ifndef SCT3
#define SCT3
#endif

#ifndef ASD2
#define ASD2
#endif

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCIBMILIB
#ifndef LCLIB
#define LCLIB    1  /* loosely coupled, LIB interface */
#endif /* LCLIB */
#ifdef NBU_REL5_IP
#ifndef LCSCT   
#define LCSCT 1   /* To resuse packing/unpacking functions at layer inf */
#endif           /*  LCSCT   */
#endif           /* NBU_REL5_IP */
#endif              /* LCIBMILIB */

#ifdef LCIBUINBU
#ifndef LCNBU
#define LCNBU     1 /* loosely coupled, NBU interface */
#endif           /* LCNBU */ 
#endif           /* LCIBUINBU */

#ifdef LCIBLIASD
#ifndef LCASD
#define LCASD     1 /* loosely coupled, ASD interface */
#endif           /* LCASD */ 
#endif           /* LCIBLIASD */

#if (LCLIB || LCASD )
#ifndef LCATM
#define LCATM 1
#endif /* LCATM */
#endif /* LCLIB || LCASD */

#ifdef LCIBLISCT
#ifndef LCSCT
#define LCSCT     1 /* loosely coupled, ASD interface */
#endif           /* LCASD */ 
#endif           /* LCIBLIASD */


#ifdef IB_NODEB 
#ifdef NBU_REL5_ATM
#ifdef NBU_REL5_IP
#error "In Node-B if REL5 ATM enabled should not enable IP"
#endif /* NBU_REL5_IP */
#endif /* NBU_REL5_ATM */
#endif /* IB_NODEB */

#endif          /* IB */

/**************************************************************************
                  End of UMTS-NBAP Parameters
**************************************************************************/

/**************************************************************************
                     UMTS-NBAP User(Dummy) Parameters
**************************************************************************/
#ifdef UL 
#undef UL
#define UL 1

/******************* section to be changed by CUSTOMERS ******************/
/*** Interfaces Coupling Options ***/

/* loosely coupled interface flags */

/* #define LCULLINBU      loosely coupled with NBAP layer  */

#ifndef LMINT3
#define LMINT3
#endif

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCULLINBU
#ifndef LCNBU
#define LCNBU     1 /* loosely coupled, NBU interface */
#endif           /* LCNBU */ 
#endif           /* LCULLINBU */

#endif          /* UL */

/**************************************************************************
                  End of UMTS-NBAP User (Dummy) Parameters
**************************************************************************/


/****************************************************************************
                     3GPP-RRC Section
****************************************************************************/
/* #define IIPV1*/             /* Peer interface version */
/* #define IIPV1*/             /* Peer interface version */
/******************* section NOT to be changed by CUSTOMERS ******************/

/****************************************************************************
                     End of SS7 ISM Section
****************************************************************************/


/******************************************************************/
/* BCP Layer                                                     */
/******************************************************************/

#ifdef BP
#undef BP
#define BP 1

/******************* section to be changed by CUSTOMERS ******************/

/* Product options, choose one or more depending on the license agreement.
 * Please check your license agreement before enabling any of the following
 * flags.
 */

/* For Fault Tolerant, High Availability interface support */

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LWLCBPBPT        light weigh loosely coupled, BPT upper layer */

/*** Interface Backward Compatiblity Options: flags should be turned
     off for backward comatibility  ***/

/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */

/*  If the user interface is loosely coupled in any of the two 
 *  directions, then define the general loosely coupled 
 *  flag (LWLCBPT) 
 */

#ifdef LWLCBPBPT

#ifdef LWLCBPT
#undef LWLCBPT
#endif /* LWLCBPT */
#define LWLCBPT 1

#ifdef LCCMSDP
#undef LCCMSDP
#endif /* LCCMSDP */
#define LCCMSDP 1

#endif /* LWLCBPBPT */

#endif /* BP */


/******************************************************************/
/* BCP User Layer                                                     */
/******************************************************************/

#ifdef BU
#undef BU
#define BU 1

/******************* section to be changed by CUSTOMERS ******************/

/* Product options, choose one or more depending on the license agreement.
 * Please check your license agreement before enabling any of the following
 * flags.
 */

/* For Fault Tolerant, High Availability interface support */

/*** Interfaces Coupling Options ***/

/* upper interface, choose none or more */

/* #define LWLCBUBPT        light weight loosely coupled, BPT interface */

/*** Interface Backward Compatiblity Options: flags should be turned
     off for backward comatibility  ***/

/************** section NOT to be changed by CUSTOMERS **********/

/* type, chosen automatically */

/*  If the user interface is loosely coupled in any of the two 
 *  directions, then define the general loosely coupled 
 *  flag (LWLCBPT) 
 */

#ifdef LWLCBUBPT

#ifdef LWLCBPT
#undef LWLCBPT
#endif /* LWLCBPT */
#define LWLCBPT 1

#ifdef LCCMSDP
#undef LCCMSDP
#endif /* LCCMSDP */
#define LCCMSDP 1

#endif /* LWLCBUBPT */

#endif /* BU */


/****************************************************************************
   LDF - RANAP flags
****************************************************************************/
#ifdef RP  /* LDF - RANAP */
#undef RP
#define RP 1

/******************* section to be changed by CUSTOMERS ******************/
#define CMSS7_SPHDROPT   /* header option. Enable this flag for
                          * the upper layers of SCCP  as well.
                          */

/*#define LCRPMILRP */       /* loosely coupled, layer management */
/* #define LCSMRPMILRP */     /* loosely coupled, layer management */
/* #define LCDPMILDP        Loosed coupled management interface */

/*#define RP_ULDF   1 */     /* LDF acts as Upper load distribution function */

/*#define RP_LLDF   1  */    /* LDF acts as Lower load distribution function */

/* #define SPCO             Connection oriented services required */


/* #define RP_DEBUG      Enable debug at initialization */

/* #define RP_USTA       Enable alarms at initialization */

/****************************** Interfaces Version Flags ******************/

/* RANAP Lower interface */
/* #define SPTV1                 Upper interface version 1.0 */
#define SPTV2              /* Upper interface version 2.0 */

/* MTP3 upper interface */
/*#define SNTV1               Lower interface version 1.0 */


/******************* Test case option ***************************************/
/* #define DP_CHINA_DEFINED   1  for china test cases */
/* #define DP_JAPAN_DEFINED   1  for japan test cases */

/******************* section not to be changed by CUSTOMERS ******************/

#ifdef ITU96
#define SS7_ITU96   
#endif

#ifndef SS7
#define SS7
#endif

/* #define LCRPLIRPT        Loosely coupled RPT interface */
/*#define LCRPUISPT         Loosely coupled SRT interface */

#ifdef LCRPMILRP
#ifdef LCLRP
#undef LCLRP
#endif
#define LCLRP    1
#endif /* LCRPMILRP */

/*
* MUST define RP_ULDF and/or RP_LLDF.
* If (RP_ULDF not defined) and (RP_LLDF not defined)
* then LDF assumes that it acts as both ULDF and LLDF
*/

#ifndef RP_ULDF
#ifndef RP_LLDF
/*#define RP_ULDF  1        LDF acts as Upper load distribution function */
/*#define RP_LLDF  1        LDF acts as Lower load distribution function */
#endif /* RP_LLDF */
#endif /* RP_ULDF */

#ifndef SPT2
#define SPT2
#endif /* SPT2 */

#ifndef LCRPT
#define LCRPT     1
#endif /* LCRPT */

#ifndef LCSPT
#define LCSPT     1
#endif /* LCSPT */

/**************** Define dependency checks (DO NOT CHANGE!!) *****************/

#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#error "Rolling upgrade feature available in CORE II only."
#endif
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

#endif /* RP */


/****************************************************************************
   LDF - GMMSM flags
****************************************************************************/
#ifdef DK  /* LDF - GMMSM */
#undef DK
#define DK 1

/******************* section to be changed by CUSTOMERS ******************/

#define LCDKMILDK       /* loosely coupled, layer management */
#define LCSMDKMILDK     /* loosely coupled, layer management */
#define LCLDK           /*  Loosed coupled management interface */

#define DK_ULDF   1      /* LDF acts as Upper load distribution function */

#define DK_LLDF   1    /* LDF acts as Lower load distribution function */

/* #define DK_DEBUG      Enable debug at initialization */

/* #define DK_USTA       Enable alarms at initialization */

/****************************** Interfaces Version Flags ******************/

/* GMMSM Lower interface */

/* RPT */
#define RA        
#define RA_AUDIT       
#define RPT_AUDIT
#define RU

/* GLS */
#define GL        
#define LLC_ENHANCEMENT

/* GBR */
#define GG        


/******************* Test case option ***************************************/

/******************* section not to be changed by CUSTOMERS ******************/

#define GMMSM

#ifndef GMMSM_GSM
#define GMMSM_GSM   
#define GMMSM_GSM_R4  
#define GMMSM_R5   
#define GMMSM_REL5 
#endif /* GMMSM_GSM */

#ifndef GMMSM_UMTS
#define GMMSM_UMTS    
#define GMMSM_UMTS_R99    
#define GMMSM_UMTS_R4    
#endif /* GMMSM_UMTS */

#define LCDKLIGMU        /* Loosely coupled GMU interface */

#define LCDKUIGLS        /* Loosely coupled GLS interface */
#define LCDKUIRPT        /* Loosely coupled RPT interface */
#define LCDKUIGBR        /* Loosely coupled GBR interface */

#ifdef LCDKMILDK
#ifndef LCLDK
#define LCLDK
#endif /* LCLDK */
#endif /* LCDKMILDK */

/*
* MUST define DK_ULDF and/or DK_LLDF.
* If (DK_ULDF not defined) and (DK_LLDF not defined)
* then LDF assumes that it acts as both ULDF and LLDF
*/

#ifndef DK_ULDF
#ifndef DK_LLDF
#define DK_ULDF  1        /* LDF acts as Upper load distribution function */
#define DK_LLDF  1        /* LDF acts as Lower load distribution function */
#endif /* DK_LLDF */
#endif /* DK_ULDF */

#ifndef LCLDK
#define LCLDK     1
#endif /* LCLDK */

#ifndef LCGMU
#define LCGMU     1
#endif /* LCGMU */

#ifndef LCGLS
#define LCGLS     1
#endif /* LCGLS */

#ifndef LCRPT
#define LCRPT     1
#endif /* LCRPT */

#ifndef LCGBR
#define LCGBR     1
#endif /* LCGBR */

#ifndef DEBUGP
#define NO_ERRCLS
#endif /* DEBUGP */

#ifndef DK_MSG
#define DK_MSG
#endif /* DK_MSG */

/**************** Define dependency checks (DO NOT CHANGE!!) *****************/

#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#error "Rolling upgrade feature available in CORE II only."
#endif
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

#endif /* DK */

/******************************************************************/
/* Diameter Layer                                                     */
/******************************************************************/

#ifdef AQ

/******************* section to be changed by CUSTOMERS ******************/ 
/* These options can be enabled in the make file also */
/* #define LCAQUIAQU        loosely coupled AQU Interface User */
/* #define LCAQLIHIT        loosely coupled transport layer Interface */
/* #define LCAQMILAQ        loosely coupled Diameter to stack manager 
                              Also enable LCSMAQMILAQ under #ifdef SM */

/* #define  CMINETDBG       enable socket debugging supprt */

/* #define  DEBUGP          enable to turn ON debug support */
/* #define  NO_ERRCLS       enable to compile out error class checking */

/*************** section not to be changed by CUSTOMERS ******************/

#if (defined(LCAQUIAQU) || defined(LCABLIAQU))
#ifndef LCAQU
#define LCAQU 1
#endif
#endif

#if (defined(LCAQMILAQ) || defined(LCSMAQMILAQ))
#ifndef LCLAQ
#define LCLAQ 1
#endif
#endif

#if (defined(LWLCAQUIAQU) || defined(LWLCABLIAQU))
#ifndef LWLCAQU
#define LWLCAQU 1
#endif
#endif

#ifdef AQ_TLS
#ifndef CM_TLS
#define CM_TLS
#endif
#ifndef HI_TLS
#define HI_TLS
#endif
#ifndef HITV2
#define HITV2
#endif
#ifndef HI_TCP_TLS
#define HI_TCP_TLS
#endif
#ifndef HI_MULTI_THREADED
#define HI_MULTI_THREADED
#endif
#ifndef LCHIUIHIT
#define LCHIUIHIT
#endif
#ifndef LCHIMILHI
#define LCHIMILHI 
#endif
#ifdef SS_SINGLE_THREADED
#undef SS_SINGLE_THREADED
#endif
#ifndef HI_FLAT_BUF
#define HI_FLAT_BUF
#endif
#ifndef HI_TLS_METHOD
#define HI_TLS_METHOD
#endif
#ifndef HI_TLS_EXT_CALLBACK
#define HI_TLS_EXT_CALLBACK
#endif
#ifndef OPENSSL_NO_KRB5
#define OPENSSL_NO_KRB5
#endif
#endif

#if (defined(LCAQLIHIT) || defined(LCHIUIHIT))
#ifndef LCHIT
#define LCHIT 1
#endif
#endif

#if (defined(LCAQLISCT) || defined(LCSBUISCT))
#ifndef LCSCT
#define LCSCT 1
#endif
#endif

/* ---- Define AQ_SCTP if SB is defined but not other way round */
#ifdef SB
#ifndef AQ_SCTP
#define AQ_SCTP
#endif
#endif

/*-- SCT interface definitions --*/
#ifdef AQ_SCTP

#ifndef SCT_ENDP_MULTI_IPADDR
#define SCT_ENDP_MULTI_IPADDR
#endif

#ifndef SB_CHECKSUM
#define SB_CHECKSUM
#endif

#ifndef LSB5
#define LSB5
#endif

#ifndef SCT2
#define SCT2
#endif

#ifndef SCT3
#define SCT3
#endif

/* Make the SCT6 flag mandatory for AQ_SCTP, to use the
 * stream parameters in cookie chunk */
#ifndef SCT6
#define SCT6
#endif 
#endif   /* AQ_SCTP */



#ifdef LAQv2
#ifdef AQ_MULT_VEND_PER_APP
#undef AQ_MULT_VEND_PER_APP
#endif /* AQ_MULT_VEND_PER_APP */
#endif /* LAQv2 */

/* If LAQv2 is not defined, then define AQ_MULT_VEND_PER_APP flag */
#ifndef LAQv2
#ifndef AQ_MULT_VEND_PER_APP
#define AQ_MULT_VEND_PER_APP
#endif /* AQ_MULT_VEND_PER_APP */
#endif /* LAQv2 */ 

#if ( (defined SS || defined SS_MT) && defined(AQ))
#define SS_RDWR_LOCK_SUPPORT
#define SS_LOCK_SUPPORT

/* if AQ is working in multithreaded mode, then by default
 * enable the SS_MT_TMR
 */
#ifdef AQ_MT
#define SS_MT_TMR
#endif /* AQ_MT */

/* adding a macro related to CM-XTA, which is required to make the 1.2
 * testcases pass
 */
#ifndef CMXTA_RET_ERR_NONE
#define CMXTA_RET_ERR_NONE
#endif /* CMXTA_RET_ERR_NONE */
#endif /* SS_MT && AQ */ 

#endif /* AQ */

/**************************************************************************
                      PSF - DIAMETER Section
**************************************************************************/
#ifdef JC
#undef JC
#define JC 1

/******************* section to be changed by CUSTOMERS ******************/
/* Interface coupling flag */
/* #define LCJCMILJC loosely coupled, AQ to LM interface */
/* #define LCSMJCMILJC  lossely coupled, AQ to SM interface */

/* #define LJCV1 1  Layer manager interface version */

/******************* section NOT to be changed by CUSTOMERS ******************/
#ifdef LCJCMILJC
#ifdef LCLJC
#undef LCLJC
#endif /* LCLJC */
#define LCLJC 1
#endif /* LCJCMILJC */

#ifdef AQ_RUG

#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "AQ_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
#ifndef AQ_FTHA
#define AQ_FTHA 1
#endif /* ifndef AQ_FTHA */
#endif /* AQ_RUG */

#ifndef CM_PSF_MBUF_USAGE
#define CM_PSF_MBUF_USAGE  /* Common PSF usage */
#endif /* CM_PSF_MBUF_USAGE */

#endif /* JC */

/****************************************************************************
                     End of PSF - DIAMETER Section
****************************************************************************/

/******************************************************************/
/* EGTP Layer                                                     */
/******************************************************************/
#ifdef EG
/*#define  EGTP_C    1 */        /* LTE Evolved GTP Control Plane Protocol */
/*#define  EGTP_U    1 */        /* LTE Evolved GTP User Plane Protocol */
/*#define  EG_LOAD_DISTRIBUTE_1  1 *//* Load Distribution Algorithm type 1 */
/*#define  EG_LOAD_DISTRIBUTE_2  1 *//* Load Distribution Algorithm type 1 */
/*#define  EGTP_U_MULTI_THREADED 1 *//* Multithreading Feature  */
/*#define  SS_MT_TMR       1 */    /* SSI Timer for Multithreading */

/******************* section to be changed by CUSTOMERS ******************/ 
/* These options can be enabled in the make file also */
/* #define LCEGUIEGT        loosely coupled EGT Interface User */
/* #define LCEGLIHIT        loosely coupled transport layer Interface */
/* #define LCEGMILEG        loosely coupled EGTP to stack manager 
                              Also enable LCSMEGMILEG under #ifdef SM */

/* #define  CMINETDBG       enable socket debugging supprt */

/* #define  DEBUGP          enable to turn ON debug support */
/* #define  NO_ERRCLS       enable to compile out error class checking */


#if (defined(LCEGMILEG) || defined(LCSMEGMILEG))
#ifndef LCLEG
#define LCLEG 1
#endif
#endif

#if (defined(LCEGLIHIT) || defined(LCHIUIHIT))
#ifndef LCHIT
#define LCHIT 1
#endif
#endif




/*************** section not to be changed by CUSTOMERS ******************/


#endif /* EG */

/**************************************************************************
               eGTP-C PSF Section
**************************************************************************/

#ifdef HW                                    /* PSF-eGTP-C (FT/HA) */ 

#undef HW
#define HW 1                                 /* Re-define HW flag explicitly */
#define LEGV3                                /* LEG Interface version required for PSF */
#define CM_XTA_PSF                           /* Enable PSF related features in XTA*/
#define EG_FTHA                              /* Enable SH support in Product*/
#define LCLHW                                /* Enable Loose coupling*/
#define LCHWMILHW                            /*  Enable loose copupled MI interface*/
#define SS_RTR_SUPPORT                       /* Enable support for router tasks */
#define CM_PSF_MBUF_USAGE                    /* Common PSF usage */
#define CM_MIN_UPD_MSG                       /* Used to control Testcase execution*/
#define LCMPSF_MIN_UPD_MSG_SZ 100            /* Explicitly set Minimum update Message size*/
#define LCSMHWMILHW                          /* Enable Loose coupling */
#endif




/*************************************************************************/
/*                     LTE-RRC Section                                   */
/*************************************************************************/
#ifdef NH
#undef NH
#define NH 1

/******************* section to be changed by CUSTOMERS ******************/

/* interfaces */
/* upper interface, choose none or more */
/* NHU */
/* #define LCNHUINHU     loosely coupled interface, NH-->NX */
/* #define LCNXLINHU     loosely coupled interface, NX-->NH */

/* #define LWLCNHUINHU   light weight loosely coupled interface, NH-->NX */
/* #define LWLCNXLINHU   light weight loosely coupled interface, NX-->NH */

/* lower interface,  choose none or more */
/* CPJ */
/* #define LCNHLICPJ   loosely coupled interface, NH-->PJ */
/* #define LCPJUICPJ   loosely coupled interface, PJ-->NH */

/* PJU */
/* #define LCNHLIPJU   loosely coupled interface, NH-->PJ */
/* #define LCPJUIPJU   loosely coupled interface, PJ-->NH */

/* CKW */
/* #define LCNHLICKW   loosely coupled interface, NH-->KW */
/* #define LCKWUICKW   loosely coupled interfcae, KW-->NH */

/* KWU */
/* #define LCNHLIKWU   loosely coupled interface, NH-->KW */
/* #define LCKWUIKWU   loosely coupled interface, KW-->NH */

/* CRG */
/* #define LCNHLICRG   loosely coupled interface, NH-->RG */
/* #define LCRGUICRG   loosely coupled interface, RG-->NH */

/* CTF */
/* #define LCNHLICTF   loosely coupled interface, NH-->TF */
/* #define LCTFUICTF   loosely coupled interface, TF-->NH */

/* Management interface */
/* #define LCNHMILNH        loosely coupled with layer manager */
/* #define LCSMNHMILNH      stack manager loosely coupled to NH */ 

/******************* section NOT to be changed by CUSTOMERS ******************/
/* interface flags, automatically chosen */

#ifdef LCNHUINHU
#ifndef LCNHU
#define LCNHU 1   /* loosely coupled NHU interface */
#endif /* LCNHU */
#endif /* LCNHUINHU */

#ifdef LWLCNHUINHU
#ifndef LWLCNHU
#define LWLCNHU 1 /* light weight loosely coupled NHU interface */
#endif /* LWLCNHU */
#endif /* LWLCNHUINHU */

#ifdef LCNHLICPJ
#ifndef LCCPJ
#define LCCPJ 1   /* loosely coupled CPJ interface */
#endif /* LCCPJ */
#endif /* LCNHLICPJ */

#ifdef LCNHLIPJU
#ifndef LCPJU
#define LCPJU 1   /* loosely coupled PJU interface */
#endif /* LCPJU */
#endif /* LCNHLIPJU */

#ifdef LCNHLICRG
#ifndef LCCRG
#define LCCRG 1   /* loosely coupled CRG interface */
#endif /* LCCRG */
#endif /* LCNHLICRG */

#ifdef LCNHLICTF
#ifndef LCCTF
#define LCCTF 1   /* loosely coupled CTF interface */
#endif /* LCCTF */
#endif /* LCNHLICTF */

#ifdef LCNHLICKW
#ifndef LCCKW
#define LCCKW 1   /* loosely coupled CKW interface */
#endif /* LCCKW */
#endif /* LCNHLICKW */

#ifdef LCNHLIKWU
#ifndef LCKWU
#define LCKWU 1   /* loosely coupled KWU interface */
#endif /* LCKWU */
#endif /* LCNHLIKWU */

#ifdef LCNHMILNH
#ifndef LCLNH
#define LCLNH 1   /* loosely coupled LNH interface */
#endif /* LCLNH */
#endif /* LCNHMILNH */

#ifdef LTERRC_REL9

#ifndef LNH_VER1
#define LNH_VER1
#endif /* LNH_VER1*/

#ifndef NHU_VER1
#define NHU_VER1
#endif /*NHU_VER1*/

#ifdef RRC_PHY_CFG_SUPP
#define CTF_VER1
#endif /* RRC_PHY_CFG_SUPP */
#endif /* LTERRC_REL9 */

#endif /* NH */




/****************************************************************************
                     LTE-MAC Section
****************************************************************************/
#ifdef RG 
#undef RG 
#define RG 1


/******************* section to be changed by CUSTOMERS ******************/

#define RG_SC1 1

/* 
 * ADD-[ccpu00118351] Introduced timing deltas in FDD for DL control, DL data, 
 * Reception Request, CRC Indication, HARQ feedback Indication.
 */
#ifdef LTEMAC_DLUE_TMGOPTMZ
/* Delta used between MAC and RLC to recieve data from RLC*/
#define RGU_DELTA 0
#else
#define RGU_DELTA 1
#endif

#ifndef MSPD
/* Delta used between MAC/Scheduler and PHY to send/recieve control info, data*/
#define TFU_DELTA 2
#else
#if defined(LOWLATENCY)
#define TFU_DELTA 2
#else
#define TFU_DELTA 3
#endif
#ifdef TFU_RECPREQ_DELTA_CHANGE
/* Number of subframes in advance reception request should be sent from MAC */
#define TFU_RECPREQ_DLDELTA  1
#endif
#ifdef TFU_DL_DELTA_CHANGE
/* Number of subframes in advance DL data should be sent  from MAC */
#define TFU_DLDATA_DLDELTA  (TFU_DELTA)
/* Number of subframes in advance DL control should be sent from MAC */
#define TFU_DLCNTRL_DLDELTA  (TFU_DELTA)
#else
/* Number of subframes in advance DL control should be sent from SCH */
#define TFU_DLCNTRL_DLDELTA   3 

/* Number of subframes in advance DL data should be sent from MAC */
#define TFU_DLDATA_DLDELTA    3
#endif
#ifdef TFU_UL_DELTA_CHANGE
/* Number of subframes for UL CRC to reach MAC after reception of data at PHY */
#define TFU_CRCIND_ULDELTA   2
/* Number of subframes in advance UL control (DCI/PHICH) should be sent from MAC */
#define TFU_ULCNTRL_DELTA  (4 - TFU_CRCIND_ULDELTA)
#endif
#ifdef TFU_DLHQFBK_DELTA_CHANGE
/* Number of subframes later DL HARQ feedback reaches MAC from PHY */
/* HARQ_TMP: Workaround to achieve maximum DL rate in absence of HARQ re-transmissions */
#ifdef MSPD_DLHARQ_ENABLE
#ifdef DLHQ_RTT_OPT
#define TFU_ENV_HQFBKIND_ULDELTA 2
#else
#define TFU_ENV_HQFBKIND_ULDELTA  3
#endif
#else
#define TFU_ENV_HQFBKIND_ULDELTA  0
#endif

#endif
#endif /* end of MSPD */


#ifdef LTE_TDD
#define RG_ENV_DL_DELTA (TFU_DELTA + RGU_DELTA)

/* The number of frames after PHY delivers the frame */
#define TFU_DELTA 2
/* Number of subframes in advance UL control (DCI-0/PHICH) should be sent from SCH */
#define TFU_ULCNTRL_DLDELTA        1

/* Number of subframes later DL HARQ feedback reaches MAC from PHY */
#define TFU_ENV_HQFBKIND_ULDELTA  2

/* Number of subframes in advance reception request should be sent from SCH to PHY */
#define TFU_RECPREQ_DLDELTA   2

/* Number of subframes in  Advance the Downlink control is 
   given from  MAC to PHY */
#define TFU_DLCNTRL_DLDELTA TFU_DELTA

#else /* LTE_TDD */
/* Number of subframes in advance UL control (DCI/PHICH) should be sent from SCH */
#define TFU_ULCNTRL_DLDELTA  (RG_SCH_CMN_HARQ_INTERVAL - TFU_CRCIND_ULDELTA)

#ifdef LTEPHY_MSPD

/* Number of subframes in advance reception request should be sent from SCH to PHY */
#define TFU_RECPREQ_DLDELTA   1

/* Number of subframes for UL CRC to reach SCH after reception of data at PHY */
#define TFU_CRCIND_ULDELTA    2

#else /* LTEPHY_MSPD */

/* Number of subframes in advance DL control should be sent from SCH */
#define TFU_DLCNTRL_DLDELTA   2
/* Number of subframes in advance DL data should be sent from MAC */
#define TFU_DLDATA_DLDELTA    2
/* Number of subframes in advance reception request should be sent from SCH to PHY */
#define TFU_RECPREQ_DLDELTA   2

/* Number of subframes for UL CRC to reach SCH after reception of data at PHY */
#define TFU_CRCIND_ULDELTA    2
/* Number of subframes later DL HARQ feedback reaches SCH from PHY */
#define TFU_ENV_HQFBKIND_ULDELTA  2

#endif /* LTEPHY_MSPD */
/* The number of frames ahead that RLC may require a STA IND */
/* Seperated DL control and DL data timing deltas
 * in FDD */
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
#define RG_UL_SCHED_DELTA 2 /* <= RGU_DELTA, DL sched to happen first */
/* RG_UL_SCHED_DELTA + 2 * TFU_DELTA should be <= 3 */

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

/*SIGTRAN Monitoring Stack Code(VN)*/
#ifdef VN
#ifdef SP_RUG
#undef SP_RUG
#endif /*SP_RUG*/

#ifdef SP_FTHA
#undef SP_FTHA
#endif /*SP_FTHA*/
#endif /*VN*/
/****************************************************************************
                     End of LTE-MAC Section
****************************************************************************/


/****************************************************************************
                     RELEASE FLAG SECTION
****************************************************************************/
#ifdef RELS_MS_0_1_6
/*#define RB_4GMX_OLD_LOCK*/
/*#define LIMIT_DL_UL_CQI*/
#endif

/****************************************************************************
                     End of RELEASE FLAG SECTION
****************************************************************************/

/****************************************************************************
                     Start of LTE_ADV FLAG SECTION
****************************************************************************/
#if (defined(LTE_ADV) && (!defined(TENB_MULT_CELL_SUPPRT)))
#error "Both LTE_ADV and TENB_MULT_CELL_SUPPRT must be enabled for CA operation."
#endif
/****************************************************************************
                     End of LTE_ADV SECTION
****************************************************************************/
#endif /* __ENVOPTH__ */

  
/********************************************************************30**
  
         End of file:     envopt_t2k.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:05:04 2014
     
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
                jrl     2. trillium development system checkpoint (dvs)
                           at version: 1.0.0.0

1.2             jrl     1. changed options for ap, xg, xe, xi, ei, is

1.3             jrl     1. changed options for tc

1.4             jrl     1. changed options for ms

1.5             mma     1. added options for sd

1.6             lc      1. added options for sn

1.7             nkk     1. added options for ud

1.8             bn      1. added option for 1 TR6 switches for ISDN and X.31

1.9             nkk     1. added options for lc
                nkk     2. added options for ma
                bn      3. added options for AUS switches for ISDN and X.31
                kgi     4. added options for sec
                lc      5. added options for AP

1.10            nkk     1. added options for gc

1.11            nkk     1. delete the following products from the "combined 
                           with" list: 
                              Multilink, Spanning Tree, ISO IP (End System),
                              and ISO IP (Intermediate System).
                nkk     2. add the following products to the "combined 
                           with" list: 
                              MOS, SDLC, ISUP, TCAP, ADCCP-NRM, 
                              SNMP Agent, SNMP Package, SCARF, and ESCC.
                mma     3. added options for tp
                nkk     4. copied LCLM into "general parameters" section.
                nkk     5. renamed each product (xx) specific LCLM to
                           LCxxLM.
                nkk     6. added options for si.
                nkk     7. text changes
                jrl     8. added options for q.930 and x.31 for NI1

*********************************************************************71*/

/********************************************************************80**

  version    pat  init                   description
----------- ----- ----  ------------------------------------------------
1.12         ---  jrl   1. text changes

1.13         ---  jrl   1. remove XE, EI and SC defines from AP, should
                           normally be provided in makefile command line

1.14         ---  lc    1. add defines for the SCCP product 
             ---  lc    2. remove comments for ST

1.15         ---  jrl   1. add data link interface type to lapb/lapd

1.16         ---  jrl   1. change TP to ST for TCAP

1.17         ---  jrl   1. text changes
             ---  jrl   2. add variants for SN

1.18         ---  jrl   1. text changes

1.19         ---  jrl   1. add etsi define

1.20         ---  jrl   1. add tcap user
             ---  jrl   2. add define ANS88
             ---  jrl   3. add define ANS92

1.21         ---  nkk   1. add SS7_MICROCODE define (SS7 microcode on 68302).
             ---  nkk   2. change ARP to MACINT3.
             ---  nkk   3. replace MA with OD for ODI.
             ---  nkk   4. add M1, M2, and M3 for MACINT1, MACINT2, 
                           and MACINT3 dummy layers.

1.22         ---  jrl   1. remove ANS define for ss7, replaced by
                           ANS88 and/or ANS92

1.23         ---  lc    1. changed DAT to SDT for MTP 2 interface

1.24         ---  fmg   1. added Berkeley Sockets interface

1.25         ---  mc    1. comment out #define LCDAUIDAT for LD
             ---  mc    2. comment out LMLD for LD AND BD

1.26         ---  bn    1. add TUP support

1.27         ---  bn    1. add VN3 and DECODCDSET
             ---  mma   2. add MACINT5 for ss7

1.28         ---  bn    1. add VN2, ATT4E and ATT5E defines for q.930
                           and x.31
             ---  lc    2. add product specific LCLM's to every product
             ---  lc    3. delete multilink

1.29         ---  rg    1. added support for Q.93B (AM).
             ---  nkk   1. added LCTULIMAC to tcp and udp sections.
             ---  nkk   2. added LLCINT and MACINT to tcp and udp 
                           sections.
             ---  nkk   4. added support for Q.SAAL (AS).
             ---  nkk   5. added support for CPCS  (AC).
             ---  nkk   6. added support for ATM (AT).
             ---  nkk   7. added support for dummy MACINT6 (M6).
             ---  nkk   8. removed superfluous BC defines for SE.
             ---  nkk   9. added BCSPKINT for packing compatility

1.30         ---  jrl   1. add product specific LCLM

1.31         ---  nkk   1. defined MACINTx for Mx, for x = 1, 2, 3, 6.
             ---  nkk   2. change default interface for TCP and UDP
                           to MACINT1
             ---  nkk   3. remove BCSEUIMAC define

1.32         ---  nkk   1. text changes.
             ---  nkk   2. undefine BCSPKINT, LCATLIMAC, LCODUIMAC and 
                           LCBSUIBST (defaults are "undefined").

1.33         ---  nkk   1. text changes

1.34         ---  nkk   1. text changes
             ---  nkk   2. added DBAS_TIMER to debug q.saal timer logic.
             ---  nkk   3. added DBAS_STATE to debug q.saal sscop state.
             ---  nkk   4. add DBACUIMAC and DBACLIMAC defines

1.35         ---  mma   1. add choose SS7 automatically
             ---  mc    2. add CHINA variant for MTP 3

1.36         ---  jrl   1. add ss7 and isdn switch type backward
                           compatibility

1.37         ---  nkk   1. eliminate service user flags M6_CPCS and M6_ATM.
             ---  nkk   2. added define for ATM stack flag in Q.SAAL, UME,
                           MACINT6, and Q.93B.
             ---  fmg   3. add SPCO for sccp.
             ---  nkk   4. add UME and SM parameters

1.38         ---  jrl   1. change BCSPKINT to FCSPKINT

1.39         ---  jrl   1. text changes

1.40         ---  jrl   1. remove ATM from q.93b

1.41         ---  jrl   1. add MACINT5 to se

1.42         ---  jrl   1. add FCSPOSTINT for mos

1.43         ---  nkk   1. add loader service user and loader support.

1.44         ---  nkk   1. add EVTEXT for event code extension

1.45         ---  nkk   1. remove MACINT5 and MACINT6 from 68302 section.
             ---  nkk   2. add options for debugging M6 software loopback.
             ---  bn    3. add BC303, BC303TMC, BC303CSC

1.46         ---  bn    1. define ISDN_303TMC, ISDN_NTDMS250 and ISDN_303TMC 1.

1.47         ---  bn    1. add wrapper (WP)

1.48         ---  bn    1. add Q.932 option for Q.930
             ---  bn    2. add SEGMENT option for Q.930

2.1          ---  ak    1. added SxVER2.
             ---  nkk   2. added MSVER2.
             ---  nkk   3. removed EVTEXT.
             ---  mc    4. added SEVER2 and turned on DATVER2 or MACVER2
                           automatically if SDVER2 or SEVER2 is uncommented.

2.2          ---  rg    1. added LC flags: LCATM, LCAMT, LCASD, LCAAL, LCUME.
             ---  rg    2. removed the use of DATINT3 and MACINT6; replaced
                           them with ASD and AAL, respectively.
             ---  rg    3. removed AC and AT sections; split SM section into
                           MU and SM sections.
             ---  nkk   4. move FCSPKINT outside of MOS section into head 
                           of file.

2.3          ---  jrl   1. add SSINT2 and LMINT2 for M6 and MU

2.4          ---  nkk   1. change LC for atm

2.5          ---  mc    1. added LCXXMILXX to AM, AS, UM, ST, SP, TP, SN, WP, 
                           SD, and MS sections.
             ---  mc    2. added LCSMXXMILXX to SM section.
             ---  bn    3. added new defines for Q.930 pertaining to specific
                           software options to included/excluded from the
                           compilation for the purpose of generating more 
                           compact code.

2.6          ---  bn    1. miscellaneous changes.

2.7          ---  bn    1. add SSINT2 for sd, sn, st, si, sp

2.8          ---  mc    1. set xxVER2 for sd, sn, st, si, sp

2.9          ---  fmg   1. add elvis defines

2.10         ---  bn    1. add isup defines
             ---  jrl   2. remove gdmoc defines

2.11         ---  bn    1. add LCSIMILSN define
             ---  bn    2. change LCSMSIMILST to LCSMSIMILSI

2.12         ---  scc   1. add SP_CFGMG for sccp

2.13         ---  rg    1. added section for LEC (EC).
             ---  rg    2. updated section for LLC (LC) as LEC user.

2.14         ---  mc    1. add section for mtp 3 simple router (SR)

2.15         ---  mc    1. add SSINT2 for IS

2.16         ---  bn    1. add SSINT2 and other defines to x.31 (ix)

2.17         ---  nkk   1. removed DBAS_TIMER and DBAS_STATE defines.
             ---  nkk   2. Q.SAAL, UME text changes.
             ---  nkk   3. removed DBAS_TIMER and DBAS_STATE defines.

2.18         ---  rh    1. renamed TRIL_SYM_UNI to IISP
             ---  nkk   2. defined M6, AS, UM, and MU loosely coupled
                           flags as "1" (for ansi preprocessing).
             ---  nkk   3. text changes.

2.19         ---  mc    1. add SSINT2, SDVER2, SNVER2 to SR

2.20         ---  nkk   1. added Fujitsu ALC support.
             ---  nkk   2. defined M6, AS, UM, and MU debugging
                           flags as "1" (for ansi preprocessing).
             ---  nkk   3. added support for Q.SAAL's Q.2110 interface.
             ---  nkk   4. defined ATM as "1".
             ---  nkk   5. added ASOPT_DISC_NO_CRED option to disconnect 
                           when tx credit exceeded.

2.21         ---  bn    1. add NI2 and QSIG for Q.930
             ---  bn    2. add INVER2 for Q.930

2.22         ---  bn    1. add ANVER2 for Q.930

2.23         ---  rg    1. added section for LES (ES).
             ---  mc    2. added BDVER2, SSINT2, and LCDAMILBD to er, br, 
                           bd, ld, and lb.  
             ---  mc    3. added LCSMDAMILBD to SM.
             ---  mc    4. added MACVER2 to IS and XEVER2 to XE.

2.24         ---  rg    1. added flags: LCECMILEC, LCESMILES, LCSMESMILES. 
             ---  rg    2. added LCATM and ATM flags for all ATM products.
             ---  rg    3. updated some comments.
             ---  fmg   4. removed SSINT2 define from backward compatible
                           layers
             ---  fmg   5. readded LCSMSEMILSE to #ifdef SM section
             ---  fmg   6. added STDIO_INCLD to mos under SUNOS

2.25         ---  jrl   1. changed default from MSVER2 to PORTVER

2.26         ---  mc    1. add DBBDMILBD, DBLDMILBD and DBLBMILBD in BD, LD,
                           and LB for management interface debugging.

2.27         ---  rg    1. added section for BUS (BS) and LECS (CS).
             ---  bn    2. added defines for ISDN_NI2 and ISDN_QSIG.
             ---  fmg   3. miscellaneous changes to bring back to
                           minimal portable configuration

2.28         ---  jrl   1. enable MACINT5 for SD and SE

2.29         ---  rg    1. merged sections for BUS (BS) and LES (ES) 
                           into LES/BUS (ES).
             ---  rg    2. removed section for LECS (CS) 
             ---  bn    3. change TPVER1 to TPVER2

2.30         ---  mc    1. add XGVER2, EIVER2, XIVER2, IXVER2 and L3VER2 to 
                           XG, EI, XI, and IX sections. 
             ---  mc    2. add APVER2 for AP.
             ---  mc    3. add LCSMXNMILXN for network layer.
             ---  fmg   4. added ME section...
             ---  mc    5. add snt interface type 1 SNTINT1 in SP, SI, TP, and
                           SN sections.

2.31         ---  bn    1. added SINGTEL and Q767 for isup

2.32         ---  rma   1. added support for 68360 (QI)
             ---  mc    2. replace WP with WN (MTP 3 Wrapper)
             ---  mc    3. add LCSMW?MILW? in SM section for ss7 stack wrapper.

2.33         ---  mc    1. define APVER2 for async pad

2.34         ---  jrl   1. add support for ISAC-S

2.35         ---  rrb   1. define Q2931, DEF_Q2931, SIG_PNNI, DEF_SIG_PNNI
                           and AM_ACNT added for Q.93B.

2.36         ---  ak    1. added sections for PN and PU. Also, added LC
                           flags for SMPN in the SM section.

2.37         ---  jrl   1. comment out Q2931

2.38         ---  jrl   1. add Q767IT for SI

2.39         ---  jrl   1. text change

2.40         ---  jrl   1. changes to FA and SM

2.41         ---  fmg   1. added Fault Manager (FM)
             ---  ssa   2. renamed LES/BUS to LE Services
             ---  mc    3. add section for Q.2140 (SA).
             ---  mc    4. add BICI option for MTP 3.
             ---  mc    5. add LC flags for Q.2140 and B_ISUP in the SM section.
             ---  bn    6. add B-ISUP

2.42         ---  fmg   1. add DATINT4 to ER

2.43         ---  bn    1. add CC.
             ---  mc    2. changed BICI option to 17.

2.44         ---  bn    1. add missing ifdef CC

2.45         ---  bn    1. add SI_SPT flag for SCCP support for SI.
             ---  bn    2. add #ifdef WI section.

2.46         ---  sg    1. add #ifdef AC section

2.47         ---  krp   1. changes to ifdef BR and ER sections

2.48         ---  krp   1. Removed backward compatibility Layer Management 
                           options for BR
             ---  krp   2. Added #define FR(to ensure management compilation)

2.49         ---  krp   1. Added Frame Relay Network - Q.933 - FN product 
                           options

2.50         ---  bn    1. change LC to TC for SI

2.51         ---  kss   1. change LCSMSIMILTP define to LCSMTPMILTP
             ---  kss   2. add 68360 subsection to EL section
             ---  kss   3. text changes
             ---  kss   4. add CF_QI define

2.52         ---  bn    1. add LCSMEVMILEV, LCSMLVMILLV, LCSMNVMILNV
                           defines
             ---  bn    2. add NV, LV and EV sections

2.53         ---  rrb   1. added UNI40, DEF_UNI40, LIJ & DEF_LIJ definitions.
             ---  rrb   2. removed IISP and added IISP_UNI30, DEF_IISP_UNI30
                           IISP_UNI31 and DEF_IISP_UNI31 definitions.
             ---  mc    3. removed SNTINT1 option from SP, SI, TP, BI, and SN.
 
2.54         ---  sa    1. added EC product specific compile flags.
             ---  dm    2. Added ATM_BISUP
             ---  ak    3. added DEF_SIG_PNNI in PN and PU sections
             ---  ak    4. added LCSMACMILAC in the SM section
             ---  ak    5. added LCACMILAC and TDS_ATM_BS in AC section
             ---  ak    6. change copyright header

2.55         ---  sa    1. corrected nested comments.

2.56         ---  mc    1. added MV section for V5 interface.
             ---  bn    2. added MF_IN and MF_NV flags defines.

2.57         ---  rrb   1. turn off loosely coupled and debug for q.93b

2.58         ---  sg    1. Added support for Atm-Frame Relay Interworking (AF)
             ---  rrb   2. Included LIJ option within "#ifdef UNI40".

2.59         ---  sg    1. turn off loosely coupled for AF

2.60         ---  sg    1. add missing #endif in AF

2.61         ---  ada   1. added FR section
             ---  ada   2. added LCSMFRMILFR flag 
             ---  ak    3. added HASH_OPEN_ADDRESSING define in PNNI section

2.62         ---  bn    1. surrounded country options in #ifdef CC area by 
                           #ifndef coresponding flags to avoid macroredifiniton

2.63         ---  krp   1. Added FR product code in comments. 
             ---  krp   2. Changed some compile flags for FR

2.64         ---  krp   1. miscellaneous changes for LMI

2.65         ---  ks    1. added support for Fujitsu evaluation board

2.66         ---  aa    1. Added the section for MAP (MA) and MAP user (AU)
             ---  bn    2. Added flags for CHINA TUP.

2.67         ---  krp   1. Added Q933-LMI integrated product flags. 

2.68         ---  dm    1. Added ATF2 for B-ISUP.
             ---  dm    2. Added TUP wrapper section.
             ---  kr    3. Added support for PMC-Sierra LASAR driver (PL)
             ---  pc    4. added ETSI variant for SI

2.69         ---  ada   1. For AF added options to support FRD interface. 
             ---  ada   2. defined LCSMAFMILAF 
             ---  bn    3. added CV support for V5.X Control Protocol 
             ---  bn    4. added MV support for V5.X System Manager 
             ---  bn    5. miscellanious changes in NV section.

2.70         ---  dm    1. added support for GT_FTZ SI
             ---  mb    2. Removed SSINT stuff.

2.71         ---  dm    1. Text change

2.72         ---  krp   1. Made modifications for FN to support
                           new signalling options.

2.73         ---  ada   1. In AC section commented out LCACUIAAL and 
                           LCACMILAC. 

2.74         ---  krp   1. Modified the FR section for release 1.3. 
                          
2.75         ---  krp   1. commented LAPF in FR section.

2.76         ---  bn    1. changed default setting for CV as tightly coupled
                           interfaces with lapv and system manager.

2.77         ---  av    1. added #define V5_1 flag for MV section.
             ---  mc    2. added VM section.
             
2.78         ---  pm    1. added ANS96 define for mtp3.
*********************************************************************81*/
 
 
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
2.78         ---      ak   1. added IM section.

2.79         ---      bn   1. added BV section.

2.80         ---      ash  1. MACINT4 added for SD/QI/SE and enabled by 
                              default.

2.81         ---      apr  1. RY_ENBMMAP is added for ELVIS_STACK
             ---      kvm  2. Added PA (PLOA)
             ---      kvm  3. Added DEBUGP for debugging
             ---      sa   4. Added AL (Application Layer)
             ---      mg   5. Added V5.x PV section
             ---      sb   6. Added V5.2 LK.

2.82         ---      kvm  1. Enabled PLOA definitions

2.83         ---      av   1. Added support in MV section for Link and
                              Protection protocol.

2.84         ---      mc   1. added BDVER2, EV_ISDN, EV_TST_ISDN, and MACINT 
                              defines in EV section.
             ---      mc   2. added MACVER2 and MACINT1 defines to VM section.
             ---      mc   3. change MACINT1 as default in the LD section.
             ---      mc   4. replaced MVT with MAC.

2.85         ---      sb   1. removed backward compatability for loosely
                              coupled interfaces.
                           2. Removed ANVER1, INVER1
 
2.86         ---      sb   1. Added flag LCUICMINT.

2.87         ---      sb   1. Added flags ISDN_BC303TMC, ISDN_BC303CSC.

2.88         ---      mjp  1. Added SCCP wrapper section

2.89         ---      sg   1. Added IA and IU section

2.90         ---      manb 1. Modified FRATM - AF section to add 
                              additional parameters.
             ---      kvm  2. added CMATM2
             ---      rb   3. Added DBASMILAS flag for debug option at
                              layer managerment interface.
             ---      rb   4. Added AS_POWER_UP_ROBUST flag for power-up
                              robustness option, as defined in atmf/97-0216.
             ---      rb   5. Removed ASOPT_DISC_NO_CRED flag.
             ---      sa   6. added flag for NARP request generation.

2.91         ---      kvm  1. removed CMATM2 flag
             ---      hrg  2. added flags PGLCAPABLE and BORDERNODE for pnni.
                           3. added options for the PNNI interface to AMT.
                           4. added flag SPEC_PORT_IN_DTL
             ---      manb 5. added flags for LCFR in Af section
             ---      bsr  6. Added FN_UNI, FN_NNI, FN_X76 and FN_FRF10
                              for FN.
             ---      rrp  7. Added flags FR_FRAGMENT, FR_TRAFFFIC_MONITOR
                              in the FR section.
             ---      rrp  8. Changed NETSIDE flag in FR section 
                              to FR_SWITCHING

2.92         ---      rb   1. Added DBASV3XIPE.
             ---      rb   2. added AM_STAT_ON_OPT_ELEM_ERR.
             ---      rb   3. added AMOPT_STS.

2.93         ---      rm   1. ADDED  UNI40 option for PL section
             ---      rm   2. ADDED  PL_DISC_CHK for PL section
             ---      ag   3. ADDED  UNI40 option for FA section

2.94         ---      pm   1. added ANS96 option. 
             ---      sb   2. Added flag ISDN_PTMPT for ISDN point
                              to Multipoint.
 
2.95         ---      aa   1. editted ac section.

2.96         ---      kr   1. added XN section
             ---      sn   2. Modified AP section to introduce
                             flags L3VER2 and MACVER2, and LCAPMILAP;
                             added flag LCSMAPMILAP under SM section

2.97         ---      skr  1. added PQ ,ELVIS_PPC860 & PQUICCADS section

2.98         ---      kvm  1. added LEC and MPC to PA section
             ---      kvm  2. added EU section (ECM interface User)
             ---      sj   3. Merged the old PLOA and new PLOA definitions
                             and removed redundent definitions.
             ---      bbk  4. Added CMDPT_DUP flag for PAMC
2.99         ---      sj   1. Disable Loosely coupled interface for PLOA 
3.1          ---      bbk  1. Changed copyright header date.
3.2          ---      mp   1. Enabled LocaExchange and Access Network
                              for BCC.

3.3          ---      nj   1. Added defines for TCAP variants (ANSI-96 and
                              ETSI).

3.4          ---      cg   1. Added flags ASOPT_QSAAL1_2 and ASOPT_Q21x0
                              for Q.SAAL.

3.5          ---      rb   1. Added code segment to define LCLAM and 
                              LCLAS based on compile flags LCSMAMMILAM
                              and LCSMASMILAS.
             ---      rb   2. Added compile time option AM_PART_MSG_DEC
                              to enable partial decoding.
             ---      rb   3. Added compile time options AMOPT_ROUTING,
                              AMOPT_CPTYINS, AMOPT_MSGREFIMPLTD,
             ---      rb   4. Added AMTOPT_ALLPDUSHM.

3.6          ---      sa   1. uncommented PORTVER and defined AS product
                              options
3.7          ---      bbk  1. Added DBPAUICIP, DBPALIAMT, DBPALIAAL and
                              DBPAMILPA flags under #ifdef PA

3.8          ---      pk   1. Added LCSMIXMILIX flag under #ifdef SM

             ---      pk.  2. Added BDVER2 and INVER2 under #ifdef IX
3.9          ---      pk   1. uncommented PORTVER and IXVER2           
3.10         ---      ag   1. Added #ifdef SS and #ifdef NS sections
                              for NTSS release
             ---      hrg  2. Added sections for INAP
3.11         ---      mb   1. Support For Force Power Core

3.12         ---      ao   1. Added sections for the Interworking Call
                              Control and Protocol Specific Interface
                              Functions for ISUP and B-ISUP.
             ---      mp   2. #ifdef VF section added. LCSMVFMILVF
                              define added for VF layer support.
             ---      bsr  3. Changed WINNT to WINNT_IATM
             ---      kr   4. Changed RY section

3.13         ---      rs   1. Modified section for the Interworking Call
                              Control. Also added CCBI and CCSI options.  

3.14         ---      dvs  1. Change Log Update

3.15         ---      dvs  1. Sync log history

3.16         ---      kp   1. SS_SK for SSI_SDK added.

3.17         ---      sam  1. Added flags ISDN_NTSPRINT, ISDN_NTMCI
                              and ISDN_NTNI for Nortel Sprint, MCI
                              and NI variants respectively.
                           2. Added define NTNI and NTMCI under #ifdef IN.
                           3. Added define ITUT88 under #ifdef IN.

3.18         ---      ash  1. Changes for SCCP and MTP2 release
             ---      nj   2. Modified to include PSF-TCAP section and
                              also changes for TCAP release.
             ---      pm   3. Changes for 2.12 release of MTP3.
             ---      ash  4. Changes for PSF-SCCP release

3.19         ---      apr  1. Added sections for System Manager(SG),
                              System Agent(SH), Message Router(MR)

3.20         ---      hrg  1. Added sections for TCAP over TCP/IP (TT).

3.21         ---      kr   1. Added section for Integrated NT platform

3.22         ---      ada  1. Added PQ_PPC860 (Force) and VB_360
                              (Voiceboard) sections

3.23         ---      ag   1. Added new section for QW (PSIF ISDN)
                           2. Restructured section on ICC (Interworking Call
                              Control)
                           3. Renamed ETSI to ETSI_SS7, as this was also 
                              being used for ISDN and resulted in conflict.
                              This caused SS7_ETSI to get defined even in 
                              case when ETSI was enabled only for ISDN product

3.24         ---      kp   1. Added SS_MT for MTSS-Solaris and checks for
                              MTSS-Solaris and pSOS/pRISM+ SS
                           2. Added in SS_RTR_SUPPORT define under SS

3.25         ---      cp   1. Changes for Japan MTP2

                      nct  2. Added PR (MPC860SAR driver) section.
                           3. Removed nested / * for mccXXX compilers.
 
3.26         ---      sr   1. changes for Japan MTP-3
3.27         ---      dvs  1. uncommented #PORTVER
3.28         ---      nj   1. Added define (AIN_SCP, AIN_IP) for AIN variant of INAP.
                      nj   2. Added defines (LIE_LMINT3, STU2, IET2) for new
                              interface of INAP.
3.29         ---      ssk  1. Added defines (SMIA_LMINT3, IA_LMINT3, STU2, 
                              IET2) for new interface of IS41 

3.30         ---      kp   1. Added support for VxWorks System Services 2.1

                      rs   2. Added RUSSIAN ISUP, PSF-ISUP and LMINT3 releated 
                              defines. 

3.31         ---      rs   1. Modified sections for the Interworking Call
                              Control. Added CCAM and CCPN options. Added
                              support for Q.93B PSIF (AW)

3.32         ---      mk   1. Added PSIF-Q.93B section. Added PSIF-Q.93B 
                              enviornment defines. Added Q.93B parameters 
                              required for ICC.
                             
3.33         ---      tej  1. Added options in FN section 
                      ash  2. Added more options for MTP2 (SD). Also 
                              added SS7_NTT

3.34         ---      sr   1. Added NTT option for SN.

3.35         ---      kvm  1. Updated PA section for PPPoA

3.36         ---      scc  1. Added defines (PN_LMINT3, SMPN_LMINT3, AALINT3,
                              AMT2 and PCI2 ) for new PNNI interface
             ---      scc  2. Got rid of STDIO defines in PNNI

3.37         ---      scc  1. PORTVER commented as it is defined in new
                              makefile.

3.38         ---      ash  1. Added the section for GN

3.39         ---      rm   1. Added defines in PA section for PLOA MPS,
                              LES and NHS.
3.40         ---      ssk  1. Added GSN option to MAP and MAP user (AU)
                              sections. Added LMINT3 flags for MAP GSM.

3.41         ---      dvs  1. Updated MA section for MAP-GSM

3.42         ---      dvs  1. Added GPRS Tunneling protocol (GTP) section
3.43         ---      bn   1. Added flag SI_ANSILNP in SI and CCSI 
                              sections

3.44         ---      dvs  1. Disable flag PORTVER                             
3.45         ---      dvs  1. Disable flag MSVER2
3.46         ---      sg   1. Added section for LLC (GL). Added stack
                              manager loose coupling flag for GPRS LLC.
3.47         ---      mb   1. Added support for H.323 stack
3.48         ---      mb   1. Updated with all flags for H.323 stack.
3.49         ---      mb   1. Changes for H.323 Portable Build
3.50         ---      nj   1. Added section for BSSGP
3.51         ---      bn   1. Updated ISUP flags.
3.52         ---      mr   1. Updated for QSAAL changes.
             ---      cg   2. Updated for IME changes.
             ---      sa   3. moved product interface flags to a common
                              section (AMT2, AALINT3, PCI2, ASD2, ASI2)

3.53         ---      mk   1. Added defines SMAM_LMINT3, AM_LMINT3, AMT2
                              and ASD2.
             ---      mk   2. Added code segment to define LCLAM 
                              based on compile flags LCSMAMMILAM, LCAMMILAM
             ---      mk   3. At AMT Interface, added compile time 
                              flag AMTOPT_RSTRSP for implementing AmtRstRsp 
             ---      mk   4. removed the debug flags DBAMUIAMT, DBAMLIASD
                              DBAMLILAM.
             ---      mk   5. Added flags AMOPT_AAL2, AMOPT_IISP_USRALLOCVCC,
                              AMOPT_EXPOSE_STATHNDL, for the Q.93B
             ---      mk   6. renamed flag AM_STAT_ON_OPT_ELEM_ERR
                              to AMOPT_STAT_ON_OPT_ELEM_ERR, in a backward
                              compatible manner.
             ---      mk   7. renamed flag AM_PART_MSG_DEC
                              to AMOPT_PART_MSG_DEC, in a backward
                              compatible manner.
             ---      sa   8. moved product interface flags back to product
                              sections.

3.54         ---      ss   1. Added section for PSF-Q.93B (ZM)
             ---      nct  2. Removed duplicate SEVER2 and SDVER2 sections.
             ---      nct  3. Reintroduced PQVER2 section to #define MACVER2.
             ---      pm   4. added support for SNDCP (GPRS).
             ---      pm   5. uncommented the LMINT3 flag.

3.55         ---      rm   1. Updated for PLOA 

3.56         ---      pm   1. Renamed the GPRS_SGSN_SUPPORTED flag to
                              GPRS_ETSI_SGSN and GPRS_MS_SUPPORTED flag 
                              to GPRS_ETSI_MS.

3.57         ---      bsp  1. Added SR 3511 variant definition in TCAP-
                              over-TCP/IP section.

3.58         ---      bbk  1. Added Module Options of CIP and LES in ifdef PA
                              section. Also Added AMT2 and AALINT3 flags for
                              PLOA

3.59         ---      ao   1. Added #define for Frame Relay Q.922 FRF.12
                              support.

3.60         ---      nj   1. Added sections for BSS-Relay, NM.
                           2. Modified sections for BSSGP and GMM.
                      rh   1. Modified the #ifdef GL and #ifdef SM sections
                              for LLC release 1.2

3.61         ---      kp   1. Added section for HR (RTP/RTCP).
                           2. Modified HU (H.323 user) section to include
                              RTP/RTCP flags.
                           3. Modified HI (TUCL) section to include ATM
                              flags when CM_AAL is on.
3.62         ---      ym   1. Added NTT variant option for ISUP section.
                           2. LCSIT is defined under IW section if LCIWUICCT
                              is defined.
3.63         ---      sam  1. Added ISDN-Q.SAAL Convergence Layer section.
                              Modified ifdef SM section to include LMINT3
                              related defines for IQ.
3.64         ---      mg   1. Updated ICC, CC, RM, RT, SF, IW, AW, QW 
                              sections for ICC1.4 release. Added XM section
                              for new release of ICC1.4
             ---      pk   2. Added ifdef ZQ section. 
                           3. Modified ifdef IN section for release 3.10
                              of Q.930/Q.931.
3.65         ---      dvs  1. opened ISDN_3_8_PLUS flag under #ifdef qw 
3.66         ---      mg   1. opened ISDN_3_8_PLUS, INVER2, CDPTYNMB_32DIGIT
                              flag under #ifdef CCIN 
3.67         ---      mg   1. Defined ANVER2 in #ifdef CCIN for suppressing
                              warnings in int.x
3.68         ---      rs   1. Added section for GW (Interworking function
                              at GGSN and changed GTP section.
3.69         ---      rs   1. Added sections for ZC, ZS and ZR. Update ICC,
                              RM, RT, SF and XM sections for ICC release 1.5

3.70         ---      pk   1. Opened flags ISDN_3_8_PLUS and CDPTYNMB_32DIGIT
                              under #ifdef qw
3.71         ---      ym   1. Protocol specific defines are added in #ifdef
                              SI section.
                           2. LSI_PARAMETER flag is removed from the #ifdef SI
                              section.
3.72         ---      bbk  1. Added section for MGCP under #ifdef MG
/main/220    ---      bsr  1. For non-ANSI compilation added STDIO_INCLD in 
                              sections SS_MT and NU
/main/221    ---      ssk  1. Added section for LDF-MTP3 under #ifdef DN
                           2. Added new flags in SP section for 
                              SCCP ITU-96 release
/main/223    ---      mrw  1. Added VO (MPC8260 driver) section

/main/225    ---      sa   1. removed redefinition of MSVER2 for compilation
                              with PORTVER
             ---      vrp  2. Added the extractable options for GTP(1.3)
                              release.Added user options(GH,GI,GO,GU)
/main/226    ---       sb  1. Added section for SIGTRAN stack.
                           2. Added section for SCTP under #ifdef SB
                           3. Added section for M3Ua under #ifdef IT
                           4. Added section for NIT layer under #ifdef NF
/main/227    ---      pss  1. Added sections for MPLS-LDP(+CR) (LN), MPLS
                              Forwarder (FW), MPLS Resource Manager (RL).
                           2. Added flag for loose coupling between Stack
                              Manager and MPLS.
/main/228    ---      jdb  1. Added Am_ACNT accounting enable by Q.93B.
/main/229    ---      sa   1. Added section for AAL2 Signaling (AL) 
                              AAL2 Signaling service uers (AA)
/main/230    ---      bsr  1. Added section for H.225 Annex G (HG)
/main/231    ---      cp   1. Modified SP and ZP sections.
/main/231    ---      vb   1. Added section for LDF-SCCP
/main/232    ---      ssk  1. Modification for LDF-MTP3 section
                              Added DN_DEBUG,DN_USTA and set of rules
                              undefine the mandatory flags if they are 
                              defined.
/main/233    ---      ash  1. Modified for SG, SH and MR changes for
                              distributed release
                           2. Modified ZP section to add ZP_DFTHA
                           3. added TDS_CORE2 flag globally
                           4. moved SP_HDROPT to global section
/main/234    ---      sr   1. MTP3 relavant flags added
/main/235    ---      ark  1. Modified SG/SH/MR section to have TDS_CORE2
/main/236    ---      uv   1. position of flags modified in  ZN section
/main/237    ---      nb   1. Added new options for Q.2140
/main/240    ---      ssk  1. Added new section for DT and updated the 
                              ST and ZT sections for DFT/HA TCAP release.

                      hl   2. Added new section for IUA and IUA-NIF and updated
                              the sections for SM and SCTP
/main/240    ---      nj   1. Added product options in IUA/M3UA section
/main/241    ---      ml   1. Added PLOA-PXY interface flags.
/main/242    ---      dw   1. Added new flags in #ifdef MG section for
                              MEGACO and MGCP 1.2 release
*********************************************************************91*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/243    ---      mr   1. Added new flags in #ifdef LD section for
                              3.4 release.
/main/244    ---      nj   1. Fixed the options in SCTP section  

/main/245    ---      bsr  1. Added a new section for SIP
/main/246    ---      hy   1. SITVER2, SI_OLD_BIND defines removed, 
                              SI_218_COMP, SI_FTHA , ANS95, ITU97, ETSIV3
                              and RMT_CICGRP_STATUS etc added as part of 
                              ISUP 2.19 , PSF-ISUP 1.3 and PSIF-ISUP 1.4 
                              release 
                           2. Comments inside comments warning is resolved
                              for entire file.
                           3. SS7_ANS95 option 18 is defined for ANS95.
                      sk   4. New msghdr option for psf acceptance tests
/main/248    ---      nb   1. Add Signalling Gateway option for MTP3
                           2. Modify #ifdef ZN section for psf-MTP3

/main/249    ---      dw   1. Change in #ifdef GT section 
/main/250    ---      nt   1. Section added for SUA and SUA-NIF
/main/251    ---      dw   1. For adding #ifdef RA section for RANAP
/main/252    ---      srg  1. BSSGP Backward compatibility flags GPRS_SOLSA, 
                              GPRS_3DIDIT_MNC and GG_FTHA are added.
/main/253    ---      as   1. Added a new section for CAP.
/main/255    ---      cy   1. Changes in IN, ZQ and QW sections.
/main/256    ---     srini 1. GS_FTHA flag is added for SNDCP.
/main/257    ---      brp  1. LLC Backward compatibility flags GL_FTHA is 
                              added.
/main/258    ---      jie  1. Updated MA/AU sections for MAP 1.5 release.
/main/259    ---      cvp  1. Updated HI section.
/main/260    ---      bsp  1. Updated SI section for ISUP 2.20 release
/main/261    ---      srg  1. Section added for BSSAP+.
                           2. Section added for MM only with loosely coupled
                              lower interface flag ( LCMMLIGAP ).
                           3. Sections GM, GR are modifed with appropriate 
                              coupling flags.
/main/262    ---      pk   1. Updated HC & HZ section.
                           2. Added new define FD_SETSIZE under 
                              CM_INET_LARGE_FDSETSIZE flag in the HI
                              section
/main/263    ---      nt   1. Section for M3UA updated.
/main/264    ---      hl   1. Added M2UA and its NIF
/main/265    ---      ck   1. Changed #if to #ifdef in GT section.
/main/266    ---      wjs  1. define SIG_AINI and DEF_SIG_AINI added for
                              Q.93B.
             ---      wjs  2. Removed the duplicated define AM_ACNT in Q.93B
                              section.
             ---      wjs  3. Corrected AM_PART_MSG_DEC.
             ---      wjs  4. Added two flags DEF_ADD_MDCR and SPVC_FR.
/main/267    ---      rc   1. flags added in SP, DP and ZP section for new
                              release
                           2. RUG and interface version flags added in SS7
                              product sections and CORE (SG, MR, SH) sections.
             ---      tz   1. Added LDF-ISUP section.
                           2. Added LCSMDIMILDI define for stack manager 
                              loose coupling to LDF-ISUP. 
/main/268    ---      sa   1. Added section for 3GPP MAC, RLC, NBAP and RRC
/main/269    ---      nb   1. Added section for ISM 
/main/270    ---      sgr  1. Modified RANAP section for RANAP 2.1 
/main/271    ---      ssp  1. Added section for 3GPP NBAP.
/main/272    ---      sm   1. GMM section addded
/main/273    ---      dw   1. Added new flags in RY section
/main/274    ---      rg   1. Added DG, ZG sections
                           2. Modified MG section
/main/275    ---      hl   1. Updated forIUA version 1.2
/main/276    ---      nj   1. Modified GT and ZB section for release GTP 2.1
/main/277    ---      jz   1. Modified MA section for MAP 1.6
/main/278    ---      tsm  1. Added Section for RRC
/main/279    ---      mj   1. Added LT, LA section for MPLS 1.2 release.
/main/281    ---      cy   1. Changes made for SIP release 1.2
/main/282    ---      jz   1. Modified MA section for MAP 1.7
/main/283    ---      rs   1. Modified RA section for RANAp 2.2
/main/284    ---      nt   1. Added PSF-M3UA section
/main/285    ---      rs   1. Added DFTHA-M3UA section
/main/286    ---      wh   1. SIP release 2.1 changes
/main/287    ---      bn   1. V5.X release 1.2 changes
/main/288    ---      jz   1. Added PSF-MAP section 
/main/289    ---      UD   Added WIN specific dependencies
/main/291    ---      vt   1. Added FP section 
/main/292    ---      kk   1. Added PSF-CAP section
/main/293    ---      vt   1. FP release 1.2
/main/294    ---     jz   1. RLC Release 1.2.
/main/295    ---     vt 1. MAC Release  1.2
/main/296    ---      up   1. BCP Release 1.1
/main/297    ---      cp   1. Added code to undefine SH when VxWorks is used.
/main/298    ---      kk   1. PSF-CAP rel 1.2 and CAP rel 2.2 changes
/main/299    ---      aj   1. PSF-AAL2 release changes.
/main/301    ---      pk   1. GCP 1.5 release
/main/302    ---      rb   1. QSAAL 2.13 release, FTHA and RUG related changes.
/main/303    ---      rk   1. M1UA 1.1 release
/main/304    ---      hr   1. M2PA release
/main/306    ---      rk   1. IUA Rel 1.3 Update
/main/308    ---      bn   2. DPNSS/DASS2
/main/309    ---      kk   1. CAP 2.3 release 
/main/310    ---      kp   1. TLS support in TUCL.
/main/311    ---      st   1. Update Rel 6 flag for MAP 2.3 Release.
/main/312    ---      yk   1. Modified IA section for MAP IS-41 1.4 relaese.
/main/313    ---     rbabu 1. Updated for NBAP Sfotware 1.2 release.   
/main/314    ---      vsr  1. Updated for LDF-RANAP 1.1 release.
/main/316    ---      sal  1. Created for Release of 2.1(RFC 3868 Support)
/main/317    ---      gs   1. Added new flags for MAC 1.3 release
/main/318    ---      kkj  1. Created for GMM 2.1 release, 
                           2. Correted FP section
/main/319    ---      yk   1. Created for GMM/SM LDF 1.1 Release
/main/321    ---      st   1. Updated for LAPDm 1.1 Release.
/main/323    ---     gs    1. MAC-HS Release 1.1
/main/324  ---   ad    1. SIP Rel 2.2
/main/325    ---  vsr    1. Diameter Release 1.2.
/main/326    ---      sk       1. Updated for PSF-SIP 1.1 Release
/main/327    ---      rce  1. Updated for LDF SUA 1.1 Release
/main/328    ---      rbabu 1. Update for PDCP Software release 1.1
/main/329    ---     rbhat 1. RRC Initial Release.
/main/330    ---     vk    1. Update for release of RANAP 3.1
/main/331    ----     sy   GCP 2.1 release
/main/333    ----     sy   ISUP  2.21 release
/main/334    ----     sy   ISUP  2.21 release Modification
/main/335    ----     sy   ISUP  2.21 release Modification
/main/336    ---     st    1. Updated for RRC Release 2.1
/main/337    ---       hs   1. Updated for release of TUCL 2.1
/main/338    ---      SN   MAC-HS release 2.1
/main/339    ---      gs    MAC Release 2.1
/main/340    ---      gs   Making TDS_CORE2 enabled default 
/main/341    ---      rs   Updated for IuUP 1.1 release.
/main/342    ---     sy       1. Updated for Release SIP 2.3
/main/344    ---     rer      1. Updated for Release RLC2.2 
/main/345    ---     sn 1. S1AP Initial Release
/main/346    ---     pc 1. Additions for IuUP 1.2 Release.
/main/347    ---     pc 1. Additions for eGTP 1.1 Release.
/main/348    ---     vk 1. Updated for Release of LTE RRC 1.1.
/main/349    ---     ap 1. Additions for LTE-MAC Release 1.1
/main/350    ---     ap 1. Iuh Initial Release 1.1
/main/351    ---     ak 1. Initial for Release eGTP 1.2
/main/352    ---     vk 1. Updated for Release of LTE RRC 2.1.
/main/353    ---   apany 1. LTE MAC 2.1 release
/main/354    ---   mmittal 1.Uncommented MAP version 1 and 2 for ptr1 build
/main/356    ---   mc  1. Updated for RANAP 5.1 Release 
/main/357    ---      pmacharla         Initial for eGTP release 2.1
/main/358    ---  djain 1. Updated for MAP 2.5 release.
/main/359    ---     hsingh 1. Updated for Release of LTE RRC 3.1.
/main/360    ---   gvj  1. Updated for LTE MAC Rel 2.2
/main/361    ---  ve    1. EGTP_U, EGTP_C and multithreading flags are
                           defined as per layer specific make files.
/main/362    ---      pka   1. Updated for PSF-S1AP 1.1 release.
/main/363    ---      rk   1. Updated for PSF-eGTP-C PSF 1.1 release.
/main/364    --- vvashishth 1. Updated for Diameter 1.3 release.
/main/365    ---      nh    1. Updated for PSF-DIAMETER 1.1 release.
/main/367    ---     nu      1. Updated for SIGTRAN Monitoring Stack release.
*********************************************************************91*/


