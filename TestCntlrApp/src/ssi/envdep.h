
/********************************************************************20**
  
     Name:     environment dependent
  
     Type:     C include file
  
     Desc:     Environment dependent defines required by the
               by TRILLIUM software. The defines in this file need to
               be changed by the customer to reflect the
               processor family under which the TRILLIUM software
               will run.
  
     File:     envdep.h
  
     Sid:      envdep.h@@/main/79 - Thu Apr 18 15:23:54 2013
  
     Prg:      na
  
*********************************************************************21*/

#ifndef __ENVDEPH__
#define __ENVDEPH__

  
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
*     1000024     Signalling System 7 (SS7)
*     1000025     SDLC
*     1000026     TCP/IP
*     1000027     Signalling System 7 - MTP Level 2
*     1000028     Signalling System 7 - MTP Level 3
*     1000029     Signalling System 7 - ISUP
*     1000030     Signalling System 7 - SCCP
*     1000031     Signalling System 7 - TCAP
*     1000033     Data Link Layer - ADCCP-NRM
*     1000034     Physical Layer - ISAC-S
*     1000035     68302 MOS/SCC
*     1000040     UDP/IP
*     1000041     ESCC
*     1000042     Signalling System 7 - TUP
*     1000043     Network Layer - Q.93B
*     1000044     Data Link Layer - Q.SAAL
*
*/


#ifdef __cplusplus
extern "C" {
#endif

/* envdep_h_001.main_70: Additions */
/* envdep_h_001.main_73: Not required for SUNOS */
#ifdef SS_LINUX
#ifndef _GNU_SOURCE
#include <stdint.h>
#define __USE_UNIX98
#endif /* _GNU_SOURCE */
#endif /* SS_LINUX */
/*envdep_h_001.main_75 : RMIOS related changes*/
#ifdef SS_RMIOS
#include "printk.h"
#endif


/* conversion of MSCDOS and MSCUNIX for backwards compatibility */

#ifdef MSCDOS              /* microsoft, dos */
#define ANSI               /* ansi */
#define DOS                /* dos */
#define MSC51              /* microsoft */
#else                      /* not microsoft, dos */
#ifdef MSCUNIX             /* microsoft, unix */
#define ANSI               /* ansi */
#define UNIX               /* unix */
#define MSC51              /* microsoft */
#else                      /* not microsoft, dos or unix */
#endif
#endif

/* ensure microsoft 7.0 backwards compatible with microsoft 5.1 */

#ifdef MSC70
#define MSC51
#endif

/* ensure microsoft 6.0 backwards compatible with microsoft 5.1 */

#ifdef MSC60
#define MSC51
#endif

/* default to sunos 5.1 for sunos */

#ifdef SUNOS
#define SUNOS51
#endif

/* ensure sunos 4.1 backwards compatible with sunos */

#ifdef SUNOS41
#ifndef SUNOS
#define SUNOS
#endif
#endif

/* ensure sunos 5.1 backwards compatible with sunos */

#ifdef SUNOS51
#ifndef SUNOS
#define SUNOS
#endif
#endif

/* ensure elvis backwards compatible with sunos */
#ifdef ELVIS_STACK
#ifndef SUNOS
#define SUNOS
#endif
#endif

#ifdef ELVIS_APP
#ifndef SUNOS
#define SUNOS
#endif
#endif

#ifdef POWER_STACK
#define UNIX
#define AIX
#define PROC_PPC
#endif /* POWER_STACK */

/* Fujitsu ALC evalutation board */
#ifdef ALC_EVAL              
#define PROC_68349
#define PROC_68XXX
#define SOLMRI43
#endif /* ALC_EVAL */

/* argument manipulation for ansi or non ansi function prototypes */

#ifdef ANSI                /* ansi */
#define ARGS(m)            m
#else                      /* non ansi */
#define ARGS(m)            ()
#endif

/* type definition for ansi or non ansi pointers */
#ifdef ANSI
typedef void *Ptr; /* ANSI vanilla pointer type definition */
#else
typedef char *Ptr; /* K&R vanilla pointer type definition */
#endif


/**********************************************************************
   memory models
**********************************************************************/

/*
   these defines are arranged first by environment (DOS, UNIX, SUNOS or
   embedded) followed by compiler (microsoft c, borland, unix or
   microtec c) as appropriate.
*/
/*envdep_h_001.main_77 SSI-4GMX specfic changes*/
#ifndef SS_4GMX_LCORE
/* envdep_h_001.main_76  Force definition of WIN32 when detecting WIN64 */
#if  defined(_WIN32) || defined(_WIN64)                     /* dos, nt win32 */
#ifndef WIN32
  #define WIN32
#endif
#endif
#endif

#ifdef  WIN32                     /* dos, nt win32 */
#define INTERRPT                    /* interrupt */
#define ASM                       /* in-line assembly code */
#define ISR_PUSH_ENV              /* isr push environment */
#define ISR_POP_ENV               /* isr pop environment */
 
#define M_I86CM                     /* Intel 80x86 compact model */
 
#define BIOSKEY _bios_keybrd
#define BIOSTOD _bios_timeofday
#define DOSKEEP _dos_keep
#define DOSGETDATE _dos_getdate
#define DOSGETTIME _dos_gettime
#define DOSDATE dosdate_t
#define DOSTIME dostime_t
#define DOSSIZE size_t
#define DOSENABLE _enable
#define DOSDISABLE _disable
#define DOSGETVECT _dos_getvect
#define DOSSETVECT _dos_setvect
#define DOSINT86 int86
#define DOSINT86X int86x
#define DOSMALLOC malloc
#define DOSEXIT _exit
#define NEAR _NEAR
 
#define KEYBRD_READY  _KEYBRD_READY
#define KEYBRD_READ   _KEYBRD_READ
#define TIME_GETCLOCK _TIME_GETCLOCK
#endif /* WIN32 */
 
/*envdep_h_001.main_75 : RMIOS related changes*/
#ifdef SS_RMIOS
#define INTERRPT                 /* interrupt */
#define ASM                       /* in-line assembly code */
#define ISR_PUSH_ENV              /* isr push environment */
#define ISR_POP_ENV               /* isr pop environment */
#endif

#if (defined(VXWORKS_PENTIUM) || defined(VXWORKS_DIAB))
#define INTERRPT                    /* interrupt */
#define ASM                       /* in-line assembly code */
#define ISR_PUSH_ENV              /* isr push environment */
#define ISR_POP_ENV               /* isr pop environment */

#define M_I86CM                     /* Intel 80x86 compact model */

#define BIOSKEY _bios_keybrd
#define BIOSTOD _bios_timeofday
#define DOSKEEP _dos_keep
#define DOSGETDATE _dos_getdate
#define DOSGETTIME _dos_gettime
#define DOSDATE dosdate_t
#define DOSTIME dostime_t
#define DOSSIZE size_t
#define DOSENABLE _enable
#define DOSDISABLE _disable
#define DOSGETVECT _dos_getvect
#define DOSSETVECT _dos_setvect
#define DOSINT86 int86
#define DOSINT86X int86x 
#define DOSMALLOC malloc
#define DOSEXIT _exit
#define NEAR _NEAR

#define KEYBRD_READY  _KEYBRD_READY
#define KEYBRD_READ   _KEYBRD_READ
#define TIME_GETCLOCK _TIME_GETCLOCK
#endif /* VXWORKS_PENTIUM */


#ifdef DOS                        /* dos */
#ifdef MSC51                      /* dos, microsoft c */
#ifdef M_I86HM                    /* Intel 80x86 huge model */
#define INTERRPT _interrupt      /* interrupt */
#else
#define INTERRPT _interrupt far  /* interrupt */
#endif /* M_I86HM */
#define ASM                       /* in-line assembly code */
#define ISR_PUSH_ENV              /* isr push environment */
#define ISR_POP_ENV               /* isr pop environment */
#define BIOSKEY _bios_keybrd
#define BIOSTOD _bios_timeofday
#define DOSGETDATE _dos_getdate
#define DOSGETTIME _dos_gettime
#define DOSDATE dosdate_t
#define DOSTIME dostime_t
#define DOSENABLE _enable
#define DOSDISABLE _disable
#define DOSGETVECT _dos_getvect
#define DOSSETVECT _dos_setvect
#define DOSEXIT _exit
#define NEAR _NEAR
#define KEYBRD_READY  _KEYBRD_READY
#define KEYBRD_READ   _KEYBRD_READ
#define TIME_GETCLOCK _TIME_GETCLOCK

#ifdef M_I86SM                    /* Intel 80x86 small model */
#define I86SM
#endif /* M_I86SM */

#ifdef M_I86MM                    /* Intel 80x86 medium model */
#define I86MM
#endif /* M_I86MM */

#ifdef M_I86CM                    /* Intel 80x86 compact model */
#define I86CM
#endif /* M_I86CM */

#ifdef M_I86LM                    /* Intel 80x86 large model */
#define I86LM
#endif /* M_I86LM */

#ifdef M_I86HM                    /* Intel 80x86 huge model */
#define I86HM
#endif /* M_I86HM */
#else  /* not MSC51*/ 
#ifdef BOR31                      /* dos, borland c */
#define INTERRPT _interrupt far  /* interrupt */
#define ASM                       /* in-line assembly code */
#define ISR_PUSH_ENV              /* isr push environment */
#define ISR_POP_ENV               /* isr pop environment */

#define I86LM                     /* Intel 80x86 large model */

#define BIOSKEY _bios_keybrd
#define BIOSTOD _bios_timeofday
#define DOSKEEP _dos_keep
#define DOSGETDATE _dos_getdate
#define DOSGETTIME _dos_gettime
#define DOSDATE dosdate_t
#define DOSTIME dostime_t
#define DOSSIZE size_t
#define DOSENABLE _enable
#define DOSDISABLE _disable
#define DOSGETVECT _dos_getvect
#define DOSSETVECT _dos_setvect
#define DOSINT86 int86
#define DOSINT86X int86x
#define DOSMALLOC malloc
#define DOSEXIT _exit
#define NEAR _NEAR

#define KEYBRD_READY  _KEYBRD_READY
#define KEYBRD_READ   _KEYBRD_READ
#define TIME_GETCLOCK _TIME_GETCLOCK
#else  /* not BOR31 */
#endif /* BOR31 */
#endif /* MSC51 */
#else  /* not DOS */
#ifdef UNIX                       /* unix */
#define INTERRPT                 /* interrupt */
#define ASM                       /* in-line assembly code */
#define ISR_PUSH_ENV              /* isr push environment */
#define ISR_POP_ENV               /* isr pop environment */


#ifdef __alpha                    /* alpha */
#define ALPHA
#undef OTHMOD
#endif /* __alpha */
#else /* not UNIX */
#ifdef SUNOS                      /* sun os */
#define PROC_SPARC                /* sparc model */
#define UNIX                      /* unix */

#define INTERRPT                 /* interrupt */
#define ASM                       /* in-line assembly code */
#define ISR_PUSH_ENV              /* isr push environment */
#define ISR_POP_ENV               /* isr pop environment */
#else /* not SUNOS */
#ifdef HPOS                       /* HP os */
#define PROC_PARISC               /* HP PA model */
#define UNIX                      /* unix */

#define INTERRPT                  /* interrupt */
#define ASM                       /* in-line assembly code */
#define ISR_PUSH_ENV              /* isr push environment */
#define ISR_POP_ENV               /* isr pop enviroment */
#else /* not HPOS */
#ifdef MOTADS                     /* embedded, motorola ads */
#define PROC_68302                /* enable 68302 specific defines */
#define M68                       /* motorola 68000 */

#ifdef DOSMRI42D                  /* DOS microtec c cross-compiler */
#define MRI68K                    /* microtec 68K c compiler */
#define INTERRPT interrupt       /* interrupt */
#define ASM asm                   /* in-line assembly code */
#define ISR_PUSH_ENV ASM(" movem.l d2-d7/a2-a6,-(a7)") /* isr push environment */
#define ISR_POP_ENV  ASM(" movem.l (a7)+,d2-d7/a2-a6") /* isr pop environment */
#endif /* DOSMRI42D */

#ifdef SOLMRI43                   /* solaris microtec c cross-compiler */
#define MRI68K                    /* microtec 68K c compiler */
#define INTERRPT interrupt       /* interrupt */
#define ASM asm                   /* in-line assembly code */
#define ISR_PUSH_ENV ASM(" movem.l d2-d7/a2-a6,-(a7)") /* isr push environment */
#define ISR_POP_ENV  ASM(" movem.l (a7)+,d2-d7/a2-a6") /* isr pop environment */
#endif /* SOLMRI43 */

#ifdef SOLOAS186                  /* solaris oasys c cross-compiler */
#define INTERRPT                 /* interrupt */
#ifdef ANSI
#define ASM __asm                 /* in-line assembly code */
#else /* not ANSI */
#define ASM asm                   /* in-line assembly code */
#endif /* ANSI */
#define ISR_PUSH_ENV              /* isr push environment */
#define ISR_POP_ENV               /* isr pop environment */
#endif /* SOLOAS186 */

#else /* not MOTADS */
#ifdef ELVIS                      /* elvis specific (not sun os) */
#define M68                       /* motorola 68000 */

#ifdef DOSMRI42D                  /* DOS microtec c cross-compiler */
#define MRI68K                    /* microtec 68K c compiler */
#define INTERRPT interrupt       /* interrupt */
#define ASM asm                   /* in-line assembly code */
#define ISR_PUSH_ENV ASM(" movem.l d2-d7/a2-a6,-(a7)") /* isr push environment */
#define ISR_POP_ENV  ASM(" movem.l (a7)+,d2-d7/a2-a6") /* isr pop environment */
#endif /* DOSMRI42D */

#ifdef SOLMRI43                   /* solaris microtec c cross-compiler */
#define MRI68K                    /* microtec 68K c compiler */
#define INTERRPT interrupt       /* interrupt */
#define ASM asm                   /* in-line assembly code */
#define ISR_PUSH_ENV ASM(" movem.l d2-d7/a2-a6,-(a7)") /* isr push environment */
#define ISR_POP_ENV  ASM(" movem.l (a7)+,d2-d7/a2-a6") /* isr pop environment */
#endif /* SOLMRI43 */

#ifdef SOLOAS186                  /* solaris oasys c cross-compiler */
#define INTERRPT                 /* interrupt */
#ifdef ANSI
#define ASM __asm                 /* in-line assembly code */
#else /* not ANSI */
#define ASM asm                   /* in-line assembly code */
#endif /* ANSI */
#define ISR_PUSH_ENV              /* isr push environment */
#define ISR_POP_ENV               /* isr pop environment */
#endif /* SOLOAS186 */

#else /* not ELVIS */

#ifdef MSC51                      /* embedded, microsoft c */
#ifdef M_I86HM                    /* Intel 80x86 huge model */
#define INTERRPT _interrupt      /* interrupt */
#else /* not M_I86HM */
#define INTERRPT _interrupt far  /* interrupt */
#endif /* M_I86HM */
#define ASM                       /* in-line assembly code */
#define ISR_PUSH_ENV              /* isr push environment */
#define ISR_POP_ENV               /* isr pop environment */
#define BIOSKEY _bios_keybrd
#define BIOSTOD _bios_timeofday
#define DOSGETDATE _dos_getdate
#define DOSGETTIME _dos_gettime
#define DOSDATE dosdate_t
#define DOSTIME dostime_t
#define DOSENABLE _enable
#define DOSDISABLE _disable
#define DOSGETVECT _dos_getvect
#define DOSSETVECT _dos_setvect
#define DOSEXIT _exit
#define NEAR _NEAR

#define KEYBRD_READY  _KEYBRD_READY
#define KEYBRD_READ   _KEYBRD_READ
#define TIME_GETCLOCK _TIME_GETCLOCK

#ifdef M_I86SM                    /* Intel 80x86 small model */
#define I86SM
#endif /* M_I86SM */

#ifdef M_I86MM                    /* Intel 80x86 medium model */
#define I86MM
#endif /* M_I86MM */

#ifdef M_I86CM                    /* Intel 80x86 compact model */
#define I86CM
#endif /* M_I86CM */

#ifdef M_I86LM                    /* Intel 80x86 large model */
#define I86LM
#endif /* M_I86CM */

#ifdef M_I86HM                    /* Intel 80x86 huge model */
#define I86HM
#endif /* M_I86HM */
#else  /* not MSC51 */
#ifdef BOR31                      /* embedded, borland c */
#define INTERRPT                 /* interrupt */
#define ASM                       /* in-line assembly code */
#define ISR_PUSH_ENV              /* isr push environment */
#define ISR_POP_ENV               /* isr pop environment */
#define I86LM                     /* Intel 80x86 large model */

#define BIOSKEY _bios_keybrd
#define BIOSTOD _bios_timeofday
#define DOSKEEP _dos_keep
#define DOSGETDATE _dos_getdate
#define DOSGETTIME _dos_gettime
#define DOSDATE dosdate_t
#define DOSTIME dostime_t
#define DOSSIZE size_t
#define DOSENABLE _enable
#define DOSDISABLE _disable
#define DOSGETVECT _dos_getvect
#define DOSSETVECT _dos_setvect
#define DOSINT86 int86
#define DOSINT86X int86x
#define DOSMALLOC malloc
#define DOSEXIT _exit
#define NEAR _NEAR

#define KEYBRD_READY  _KEYBRD_READY
#define KEYBRD_READ   _KEYBRD_READ
#define TIME_GETCLOCK _TIME_GETCLOCK
#else  /* not BOR31 */
#ifdef DOSMRI42D                  /* dos microtec c cross-compiler */
#define MRI68K                    /* microtec 68K c compiler */
#define INTERRPT interrupt       /* interrupt */
#define ASM asm                   /* in-line assembly code */
#define ISR_PUSH_ENV ASM(" movem.l d2-d7/a2-a6,-(a7)") /* isr push environment */
#define ISR_POP_ENV  ASM(" movem.l (a7)+,d2-d7/a2-a6") /* isr pop environment */
#ifdef _M68
#define M68                       /* motorola 68000 */
#endif /* _M68 */
#else  /* DOSMRI42D */
#ifdef SOLMRI43                   /* solaris microtec c cross-compiler */
#define MRI68K                    /* microtec 68K c compiler */
#define INTERRPT interrupt       /* interrupt */
#define ASM asm                   /* in-line assembly code */
#define ISR_PUSH_ENV ASM(" movem.l d2-d7/a2-a6,-(a7)") /* isr push environment */
#define ISR_POP_ENV  ASM(" movem.l (a7)+,d2-d7/a2-a6") /* isr pop environment */
#ifdef _M68
#define M68                       /* motorola 68000 */
#endif /* _M68 */
#else  /* not SOLMRI43 */
#ifdef SOLOAS186                  /* solaris oasys c cross-compiler */
#define INTERRPT                 /* interrupt */
#ifdef ANSI
#define ASM __asm                 /* in-line assembly code */
#else /* not ANSI */
#define ASM asm                   /* in-line assembly code */
#endif /* ANSI */
#define ISR_PUSH_ENV              /* isr push environment */
#define ISR_POP_ENV               /* isr pop environment */
#ifdef m68k                       /* motorola 68000 series */
#define M68                       /* motorola 68000 */
#endif /* m68k */
#else  /* not SOLOAS186 */
#ifdef MOTDCI_68360
#define M68
#define PROC_68XXX
#define PROC_68360
#ifdef __GNUC__
#define INTERRPT
#define ASM __asm__                /* in-line assembly code */
#define ISR_PUSH_ENV               /* isr push environment */
#define ISR_POP_ENV                /* isr pop environment */
#else
#ifdef _MCC68K
#define INTERRPT interrupt
#define ASM asm                    /* in-line assembly code */
#define ISR_PUSH_ENV ASM(" movem.l d2-d7/a2-a6,-(a7)") /* isr push env */
#define ISR_POP_ENV  ASM(" movem.l (a7)+,d2-d7/a2-a6") /* isr pop env */
#endif /* _MCC68K */
#endif /* __GNUCC__ */
#else
#ifdef QUICCADS
#define M68
#define PROC_68XXX
#define PROC_68360
#ifdef __GNUC__
#define INTERRPT
#define ASM __asm__                /* in-line assembly code */
#define ISR_PUSH_ENV               /* isr push environment */
#define ISR_POP_ENV                /* isr pop environment */
#else /* not gnu cc */
#ifdef _MCC68K
#define INTERRPT interrupt
#define ASM asm                    /* in-line assembly code */
#define ISR_PUSH_ENV ASM(" movem.l d2-d7/a2-a6,-(a7)") /* isr push env */
#define ISR_POP_ENV  ASM(" movem.l (a7)+,d2-d7/a2-a6") /* isr pop env */
#endif /* _MCC68K */
#endif /* __GNUCC__ */
#else
#ifdef ALC_EVAL
#ifdef SOLMRI43
#define MRI68K                    /* microtec 68K c compiler */
#define INTERRPT interrupt        /* interrupt */
#define ASM asm                   /* in-line assembly code */
#define ISR_PUSH_ENV ASM(" movem.l d2-d7/a2-a6,-(a7)") /* isr push environment */
#define ISR_POP_ENV  ASM(" movem.l (a7)+,d2-d7/a2-a6") /* isr pop environment */
#ifdef _M68
#define M68                       /* motorola 68000 */
#endif /* _M68 */
#endif /* SOLMRI43 */
#else
#ifdef GSIP302
#define M68
#define PROC_68XXX
#define PROC_68302
#ifdef __GNUC__
#define INTERRPT
#define ASM __asm__                /* in-line assembly code */
#define ISR_PUSH_ENV               /* isr push environment */
#define ISR_POP_ENV                /* isr pop environment */
#else /* not gnu cc */
#ifdef _MCC68K
#define INTERRPT interrupt
#define ASM asm                    /* in-line assembly code */
#define ISR_PUSH_ENV ASM(" movem.l d2-d7/a2-a6,-(a7)") /* isr push env */
#define ISR_POP_ENV  ASM(" movem.l (a7)+,d2-d7/a2-a6") /* isr pop env */
#endif /* _MCC68K */
#endif /* __GNUCC__ */
#else  /* not GSIP302 */
#ifdef VB_360
#define M68
#define PROC_68XXX
#define PROC_68360
#ifdef __GNUC__
#define INTERRPT
#define ASM __asm__                /* in-line assembly code */
#define ISR_PUSH_ENV               /* isr push environment */
#define ISR_POP_ENV                /* isr pop environment */
#else
#ifdef _MCC68K
#define INTERRPT interrupt
#define ASM asm                    /* in-line assembly code */
#define ISR_PUSH_ENV ASM(" movem.l d2-d7/a2-a6,-(a7)") /* isr push env */
#define ISR_POP_ENV  ASM(" movem.l (a7)+,d2-d7/a2-a6") /* isr pop env */
#endif /* _MCC68K */
#endif /* __GNUCC__ */
#else  /* not VB_360 */
#ifdef PQ_PPC860                   /* Force PowerQUICC board */
#define PROC_PPC                   /* any PowerPC processor */
#define PROC_PPC860                /* MPC860 processor */
#ifdef __GNUC__                    /* gnu C compiler */
#define INTERRPT
#define ASM __asm__                /* in-line assembly code */
#define ISR_PUSH_ENV               /* isr push environment */
#define ISR_POP_ENV                /* isr pop environment */
#else
#ifdef _MCCPPC                     /* micortech C compiler */
#define INTERRPT
#define ASM asm                    /* in-line assembly code */
#define ISR_PUSH_ENV               /* isr push env */
#define ISR_POP_ENV                /* isr pop env */
#endif /* _MCC68K */
#endif /* __GNUCC__ */
#else  /* NOT PQ_PPC860 */
#ifdef PCORE
#define PROC_PPC
#define PROC_PPC604
#ifdef __GNUC__
#define INTERRPT
#define ASM __asm__                /* in-line assembly code */
#define ISR_PUSH_ENV               /* isr push environment */
#define ISR_POP_ENV                /* isr pop environment */
#else
#ifdef _MCCPPC
#define INTERRPT
#define ASM asm                    /* in-line assembly code */
#define ISR_PUSH_ENV               /* isr push env */
#define ISR_POP_ENV                /* isr pop env */
#endif /* _MCC68K */
#endif /* __GNUCC__ */
#else  /* PCORE */
#ifdef SS_PS                       /* pSOS RTOS */
#define INTERRPT 
#define ASM  __asm                 /* in-line assembly code */
#define ISR_PUSH_ENV               /* isr push env */
#define ISR_POP_ENV                /* isr pop env */
#else /* not SS_PS */
#define OTHMOD                     /* other model */
#endif /* SS_PS */
#endif /* PCORE */
#endif /* PQ_PPC860 */
#endif /* VB_360 */
#endif /* GSIP302 */
#endif /* ALC_EVAL */
#endif /* QUICCADS */
#endif /* MOTDCI_68360 */
#endif /* SOLOAS186 */
#endif /* SOLMRI43 */
#endif /* DOSMRI42D */
#endif /* BOR31 */
#endif /* MSC51 */
#endif /* ELVIS */
#endif /* MOTADS */
#endif /* HPOS */
#endif /* SUNOS */
#endif /* UNIX */
#endif /* DOS */

  
/**********************************************************************
   typedefs
**********************************************************************/

/*
   these typedefs are arranged first by environment (DOS, UNIX or
   embedded) followed by compiler (microsoft c, borland c, unix or
   microtec c) as appropriate.
*/

#ifdef DOS                        /* dos */
#ifdef MSC51                      /* dos, microsoft c */

typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef int             S16;      /* signed - 16 bits */
typedef unsigned int    U16;      /* unsigned - 16 bits */

typedef long            S32;      /* signed - 32 bits */
typedef unsigned long   U32;      /* unsigned - 32 bits */
/* envdep_h_001.main_71 */
typedef __int64			 S64;     /* signed - 64 bits */
typedef unsigned __int64 U64;     /* unsigned - 64 bits */

/*
   void

   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/

/* envdep_h_001.main_78 Change typedef void to #define void*/
#define Void void               

typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning Void */
typedef Void (INTERRPT *PIF) ARGS((void ));     /* pointer to interrupt function */

#else /* not MSC51 */
#ifdef BOR31                      /* dos, borland c */

typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef int             S16;      /* signed - 16 bits */
typedef unsigned int    U16;      /* unsigned - 16 bits */

typedef long            S32;      /* signed - 32 bits */
typedef unsigned long   U32;      /* unsigned - 32 bits */

/*
   void

   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/

typedef void Void;                /* void */

typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning Void */
typedef Void (INTERRPT far *PIF) ARGS((void )); /* pointer to interrupt function */

#else /* not BOR31 */
#endif /* BOR31 */
#endif /* MSC51 */
#else  /* not DOS */
#ifdef UNIX                       /* unix */

typedef unsigned char   Bool;     /* boolean */
/*envdep_h_001.main_77 SSI-4GMX specfic changes*/
#if !(defined(SS_4GMX_LCORE) || defined(SS_4GMX_UCORE))
typedef char            S8;       /* signed - 8 bits */
#else
/*envdep_h_001.main_78 :removed signed to supress sprintf' differ in signedness warnings */
typedef char     S8;       /* signed - 8 bits*/
#endif
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef short           S16;      /* signed - 16 bits */
typedef unsigned short  U16;      /* unsigned - 16 bits */

#if !(defined(ALPHA) || defined(BIT_64))
typedef long            S32;      /* signed - 32 bits */
typedef unsigned long   U32;      /* unsigned - 32 bits */
/* envdep_h_001.main_71 */
#ifdef SS_LINUX
/* envdep_h_001.main_72: Support for C89 standard */
__extension__ typedef long long       S64;      /* signed - 64 bits */
__extension__ typedef unsigned long long U64;   /* unsigned - 64 bits */
#else
typedef long long       S64;      /* signed - 64 bits */
typedef unsigned long long U64;   /* unsigned - 64 bits */
#endif /* SS_LINUX */
#else /* ALPHA  & BIT_64 */
typedef int             S32;      /* signed - 32 bits */
typedef unsigned int    U32;      /* unsigned - 32 bits */
/* envdep_h_001.main_71 */
typedef long            S64;      /* signed - 64 bits */
typedef unsigned long   U64;      /* unsigned - 64 bits */
#endif /* ALPHA  & BIT_64 */
/* 1. Added F32 and F64 */
#ifdef SS_FLOAT
typedef float           F32;      /* float - 32 bits */
typedef double          F64;      /* double - 64 bits */
#endif /* SS_FLOAT */

/*
   void

   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/

#ifdef __cplusplus
#define Void void
#else
typedef void Void;                /* void */
#endif

typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning VOID */
typedef Void (INTERRPT *PIF) ARGS((void ));    /* pointer to interrupt function */

#else /* not UNIX */
#ifdef PROC_68302                 /* embedded, motorola ads */
#ifdef DOSMRI42D                  /* dos microtec c cross-compiler */

typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef short           S16;      /* signed - 16 bits */
typedef unsigned short  U16;      /* unsigned - 16 bits */

typedef int             S32;      /* signed - 32 bits */
typedef unsigned int    U32;      /* unsigned - 32 bits */

#ifndef ANSI
/* size_t is not defined, for some odd reason, in mcc68k's stddef.h */
typedef unsigned size_t;          /* size_t */
#endif /* not ANSI */

/*
   void

   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/

typedef void  Void;               /* void */
typedef Void  VOID;               /* void */

typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning Void */
typedef Void (*PIF) ARGS((void )); /* pointer to interrupt function */

#else /* not DOSMRI42D */
#ifdef SOLMRI43                   /* solaris microtec c cross-compiler */

typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef short           S16;      /* signed - 16 bits */
typedef unsigned short  U16;      /* unsigned - 16 bits */

typedef int             S32;      /* signed - 32 bits */
typedef unsigned int    U32;      /* unsigned - 32 bits */

/*
   void

   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/

typedef void  Void;               /* void */
typedef Void  VOID;               /* void */

typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning Void */
typedef Void (*PIF) ARGS((void ));    /* pointer to interrupt function */

#else  /* not SOLMRI43 */
#ifdef SOLOAS186                  /* solaris oasys c cross-compiler */

typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef short           S16;      /* signed - 16 bits */
typedef unsigned short  U16;      /* unsigned - 16 bits */

typedef int             S32;      /* signed - 32 bits */
typedef unsigned int    U32;      /* unsigned - 32 bits */

/*
   void

   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/

typedef void  Void;               /* void */
typedef Void  VOID;               /* void */

typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning Void */
typedef Void (INTERRPT *PIF) ARGS((void )); /* pointer to interrupt function */

#else /* not SOLOAS186 */
#ifdef __GNUC__    /* if  GNUC cross compiler */

typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef short           S16;      /* signed - 16 bits */
typedef unsigned short  U16;      /* unsigned - 16 bits */

typedef int             S32;      /* signed - 32 bits */
typedef unsigned int    U32;      /* unsigned - 32 bits */
/* envdep_h_001.main_71 */
typedef long long       S64;      /* signed - 64 bits */
typedef unsigned long long U64;   /* unsigned - 64 bits */
/* 1. Added F32 and F64 types  */
#ifdef SS_FLOAT
typedef float           F32;      /* float - 32 bits */
typedef double          F64;      /* double - 64 bits */
#endif /* SS_FLOAT */

/*
   void

   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/

typedef void  Void;               /* void */
typedef Void  VOID;               /* void */

typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning Void */
typedef Void (INTERRPT *PIF) ARGS((void )); /* pointer to interrupt function */

#else /* not __GNUC__ */
#endif /* __GNUC */
#endif /* SOLOAS186 */
#endif /* SOLMRI43 */
#endif /* DOSMRI42D */
#else  /* not PROC_68302 */
#ifdef PROC_68040

#ifdef SOLMRI43                   /* solaris microtec c cross-compiler */
typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef short           S16;      /* signed - 16 bits */
typedef unsigned short  U16;      /* unsigned - 16 bits */

typedef int             S32;      /* signed - 32 bits */
typedef unsigned int    U32;      /* unsigned - 32 bits */

/*
   void

   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/

typedef void  Void;               /* void */
typedef Void  VOID;               /* void */

typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning Void */
typedef INTERRPT Void (*PIF) ARGS((void)); /* pointer to interrupt function */
#endif /* SOLMRI43 */
#else /* not PROC_68040 */
#ifdef PROC_68360

typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef short           S16;      /* signed - 16 bits */
typedef unsigned short  U16;      /* unsigned - 16 bits */

typedef long            S32;      /* signed - 32 bits */
typedef unsigned long   U32;      /* unsigned - 32 bits */

/*
   void

   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/

typedef void Void;                /* void */

typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning Void */
typedef INTERRPT Void (*PIF) ARGS((void )); /* pointer to interrupt function */

#else /* not PROC_68360 */

#ifdef WIN32
typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef short           S16;      /* signed - 16 bits */
typedef unsigned short  U16;      /* unsigned - 16 bits */
 
typedef int             S32;      /* signed - 32 bits */
typedef unsigned int    U32;      /* unsigned - 32 bits */
/* envdep_h_001.main_76  Take care of the windows compiler non compliance
 * to ANSI-C for data type ranges
*/ 
typedef long long          S64;      /* signed - 64 bits */
typedef unsigned long long U64;   /* unsigned - 64 bits */

/* 1. Added F32 and F64 types  */
#ifdef SS_FLOAT
typedef float           F32;      /* float - 32 bits */
typedef double          F64;      /* double - 64 bits */
#endif /* SS_FLOAT */
/*
   void
 
   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/
 
typedef void Void;                /* void */
 
typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning Void */
typedef Void (INTERRPT *PIF) ARGS((void )); /* pointer to interrupt function */

#else /* not WIN32 */
#ifdef PROC_68349
typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef short           S16;      /* signed - 16 bits */
typedef unsigned short  U16;      /* unsigned - 16 bits */

typedef long            S32;      /* signed - 32 bits */
typedef unsigned long   U32;      /* unsigned - 32 bits */

/*
   void

   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/

typedef void Void;                /* void */

typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning Void */
typedef INTERRPT Void (*PIF) ARGS((void )); /* pointer to interrupt function */

#else  /* not PROC_68349 */

#ifdef PROC_PPC
typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */
 
typedef short           S16;      /* signed - 16 bits */
typedef unsigned short  U16;      /* unsigned - 16 bits */
#ifndef BIT_64
typedef long            S32;      /* signed - 32 bits */
typedef unsigned long   U32;      /* unsigned - 32 bits */

/* envdep_h_001.main_74 - additions */
typedef long long          S64;		/* signed - 64 bits */
typedef unsigned long long U64;   /* unsigned - 64 bits */
#else /* BIT_64 */
typedef int             S32;      /* signed - 32 bits */
typedef unsigned int    U32;      /* unsigned - 32 bits */
typedef long            S64;      /* signed - 64 bits */
typedef unsigned long   U64;      /* unsigned - 64 bits */
#endif /* BIT_64 */

/* 1. Added F32 and F64 types  */
#ifdef SS_FLOAT
typedef float           F32;      /* float - 32 bits */
typedef double          F64;      /* double - 64 bits */
#endif /* SS_FLOAT */
/*
   void
 
   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/

typedef void Void;                /* void */
 
typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning Void */
typedef INTERRPT Void (*PIF) ARGS((void )); /* pointer to interrupt function */
 
#else /* not PROC_PPC */

#ifdef SS_PS
typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */
 
typedef short           S16;      /* signed - 16 bits */
typedef unsigned short  U16;      /* unsigned - 16 bits */
 
#ifndef BIT_64
typedef long            S32;      /* signed - 32 bits */
typedef unsigned long   U32;      /* unsigned - 32 bits */

/* envdep_h_001.main_71 - additions */
typedef int64_t         S64;		/* signed - 64 bits */
typedef uint64_t        U64;   /* unsigned - 64 bits */
#else /* BIT_64 */
typedef int             S32;      /* signed - 32 bits */
typedef unsigned int    U32;      /* unsigned - 32 bits */
typedef long            S64;      /* signed - 64 bits */
typedef unsigned long   U64;      /* unsigned - 64 bits */
#endif /* BIT_64 */

/*
   void
 
   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/
 
typedef void Void;                /* void */
 
typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning Void */
typedef Void (INTERRPT *PIF) ARGS((void )); /* pointer to interrupt function */
 
#else /* not SS_PS */

typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef int             S16;      /* signed - 16 bits */
typedef unsigned int    U16;      /* unsigned - 16 bits */

typedef long            S32;      /* signed - 32 bits */
typedef unsigned long   U32;      /* unsigned - 32 bits */

/*
   void

   note: if typedef Void is set to S16 then RETVOID must be set
   to: return(ROK). if typedef Void is set to void then RETVOID
   must be set to: return
*/

typedef void Void;                /* void */

typedef S8   (*PFS8) ARGS((void ));   /* pointer to function returning S8 */
typedef S16  (*PFS16) ARGS((void ));  /* pointer to function returning S16 */
typedef S32  (*PFS32) ARGS((void ));  /* pointer to function returning S32 */
typedef Void (*PFVOID) ARGS((void )); /* pointer to function returning Void */
typedef Void (INTERRPT *PIF) ARGS((void )); /* pointer to interrupt function */

#endif /* SS_PS */
#endif /* PROC_PPC */
#endif /* PROC_68349 */
#endif /* WIN32 */
#endif /* PROC_68360 */
#endif /* PROC_68040 */
#endif /* PROC_68302 */
#endif /* UNIX */
#endif /* DOS */


/* scope control keywords */
  
#ifdef PUBLIC
#undef PUBLIC
#define PUBLIC                    /* public is c default scope */
#else /* not PUBLIC */
#define PUBLIC
#endif /* PUBLIC */

#if 0
#ifndef DSC_UT
   #ifdef PRIVATE
      #undef PRIVATE
      #define PRIVATE       static      /* private is c static scope */
   #else /* not PRIVATE */
      #define PRIVATE       static      /* private is c static scope */
   #endif /* PRIVATE */
#else
   #define PRIVATE 
#endif

#ifndef USGT_UT
   #ifdef PRIVATE
      #undef PRIVATE
      #define PRIVATE       static      /* private is c static scope */
   #else /* not PRIVATE */
      #define PRIVATE       static      /* private is c static scope */
   #endif /* PRIVATE */
#else
   #ifdef PRIVATE
      #undef PRIVATE
      #define PRIVATE 
   #endif /* PRIVATE */
#endif
#endif

#if defined(DSC_UT) || defined (USGT_UT)
   #ifdef PRIVATE
      #undef PRIVATE
      #define PRIVATE 
   #else
      #define PRIVATE
   #endif
#else
   #ifdef PRIVATE
      #undef PRIVATE
      #define PRIVATE       static      /* private is c static scope */
   #else /* not PRIVATE */
      #define PRIVATE       static      /* private is c static scope */
   #endif /* PRIVATE */
#endif




#ifdef EXTERN
#undef EXTERN
#define EXTERN  extern
#else /* not EXTERN */
#define EXTERN  extern
#endif /* EXTERN */


#ifdef ANSI
#define CONSTANT const            /* constant */
#else
#define CONSTANT
#endif /* ANSI */

#ifdef _MCC68K                    /* microtec 68K cross compiler */

#ifdef VOLATILE
#undef VOLATILE
#define VOLATILE     volatile     /* volatile */
#else
#define VOLATILE    volatile
#endif

#if _STR_CMP(_VERSION,"4.4") >= 0  /* MCC68K only, check version */
#ifdef INLINE
#undef INLINE
#define INLINE       inline       /* inline */
#else /* not INLINE */
#define INLINE       inline       /* inline */
#endif /* INLINE */
#else
#define INLINE                    /* no inline */
#endif /* __STR_CMP */
#else /* not _MCC68K */
#ifdef __GNUC__
#ifndef __STRICT_ANSI__
#ifdef INLINE
#undef INLINE
#define INLINE __inline__
#else /* not inline */
#define INLINE __inline__
#endif /* INLINE */
#else /* not strict ansi */
#ifdef INLINE
#undef INLINE
#define INLINE
#else /* not inline */
#define INLINE
#endif /* INLINE */
#endif /* __STRICT_ANSI */
#ifdef VOLATILE
#undef VOLATILE
#define VOLATILE     volatile     /* volatile */
#else /* volatile */
#define VOLATILE    volatile
#endif
#else /* not gnuc */
#ifdef WIN32
#ifdef VOLATILE
#undef VOLATILE
#define VOLATILE  volatile
#else /* VOLATILE */
#define VOLATILE  volatile
#endif /* VOLATILE */

#ifdef INLINE
#undef INLINE
#define INLINE
#else
#define INLINE
#endif /* INLINE */
#else /* not WIN32 */

#ifdef VOLATILE
#undef VOLATILE
#define VOLATILE                  /* volatile */
#else
#define VOLATILE                  /* volatile */
#endif /* VOLATILE */

#ifdef INLINE
#undef INLINE
#define INLINE
#else
#define INLINE
#endif /* INLINE */

#endif /* WIN32 */
#endif /* __GNUC__ */
#endif /* _MCC68K */

/*envdep_h_001.main_77 SSI-4GMX specfic changes*/
/*envdep_h_001.main_78 : removed SSI-4GMX specfic changes*/
#ifdef VOLATILE
#undef VOLATILE
#define VOLATILE volatile
#else
#define VOLATILE volatile
#endif

#ifdef __cplusplus
#ifdef INLINE
#undef INLINE
#endif
#define INLINE
#endif


/**********************************************************************
   prototypes for sprintf
**********************************************************************/

/*envdep_h_001.main_75 : RMIOS related changes*/
#ifndef SS_RMIOS
#ifndef STDIO_INCLD

#ifdef SUNOS41
EXTERN  S8 *sprintf ARGS((S8 *buffer, CONSTANT S8 *format, /* args */ ...));
#else
#ifdef SUNOS51
EXTERN int sprintf ARGS((S8 *s, CONSTANT S8 *format, /* args */ ... ));
#else /* not SUNOS51 */
#ifdef HPOS 
EXTERN int sprintf ARGS((S8 *s, CONSTANT S8 *format, /* args */ ... ));
#else
#ifdef _MCC68K
EXTERN Void sprintf ARGS((S8 *outbuf, S8 *fmt, /* args */ ...)); /* td68k.x */
#else
/* other os */
#ifdef WIN32
EXTERN  int sprintf ARGS((S8 *buffer,CONSTANT S8 *format, /* args */ ...)); 
#else
#ifdef VW
EXTERN  int sprintf ARGS((S8 *buffer,CONSTANT S8 *format, /* args */ ...)); 
#else
#ifdef SS_PS
EXTERN  int sprintf ARGS((S8 *buffer,CONSTANT S8 *format, /* args */ ...)); 
#endif /* SS_PS */
#endif /* VW */
#endif /* WIN32 */
#endif /* _MCC68K */
#endif /* HPOS */
#endif /* SUNOS51 */
#endif /* SUNOS41 */
#endif /* STDIO_INCLD */
#endif /*SS_RMIOS*/


/**********************************************************************
   defines for pointers, pointer sizes, stack alignment and registers
**********************************************************************/

/*
   defines are provided for: intel 80x86 small, intel 80x86 medium,
   intel 80x86 compact, intel 80x86 large, intel huge, motorola 68000,
   sparc, vax and other processors.
*/
 
#ifdef I86SM          /* Intel 80x86 small model */

#define NULLP         0           /* null pointer */
#define NULLD         0L          /* null data */
#define PTR           U16         /* pointer */
#define PTRSIZE       sizeof(U16) /* pointer size */
#define STKALIGN      2           /* stack alignment */

#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3                      /* register 3 */
#define REG4                      /* register 4 */
#define REG5                      /* register 5 */
#define REG6                      /* register 6 */
#define REG7                      /* register 7 */
#define REG8                      /* register 8 - lowest priority */

#define FAR                       /* for small model */
#define PTRSTRIDE     1           /* stride */
#define MEM_SEG                   /* memory - segmented */
#endif /* I86SM */

#ifdef I86MM          /* Intel 80x86 medium model */

#define NULLP         0           /* null pointer */
#define NULLD         0L          /* null data */
#define PTR           U16         /* pointer */
#define PTRSIZE       sizeof(U16) /* pointer size */
#define STKALIGN      2           /* stack alignment */

#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3                      /* register 3 */
#define REG4                      /* register 4 */
#define REG5                      /* register 5 */
#define REG6                      /* register 6 */
#define REG7                      /* register 7 */
#define REG8                      /* register 8 - lowest priority */

#define FAR                       /* for medium model */
#define PTRSTRIDE     1           /* stride */
#define MEM_SEG                   /* memory - segmented */
#endif /* I86MM */

#ifdef I86CM          /* Intel 80x86 compact model */

#define NULLP         0L          /* null pointer */
#define NULLD         0L          /* null data */
#ifndef BIT_64
#define PTR           U32         /* pointer */
#define PTRSIZE       sizeof(U32) /* pointer size */
/* #define PTRFAR                     pointer far */
#define STKALIGN      4           /* stack alignment */
#else /* BIT_64 */
#define PTR           U64         /* pointer */
/* envdep_h_001.main_78:Warning fix*/
#define PTRSIZE       sizeof(U64) /* pointer size */
/* #define PTRFAR                     pointer far */
#define STKALIGN      8           /* stack alignment */
#endif /* BIT_64 */


#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3                      /* register 3 */
#define REG4                      /* register 4 */
#define REG5                      /* register 5 */
#define REG6                      /* register 6 */
#define REG7                      /* register 7 */
#define REG8                      /* register 8 - lowest priority */

#define FAR           far         /* for compact model */
#define PTRSTRIDE     1           /* stride */
#define MEM_SEG                   /* memory - segmented */
#endif /* I86CM */


#ifdef I86LM          /* Intel 80x86 large model */

#define NULLP         0L          /* null pointer */
#define NULLD         0L          /* null data */
#ifndef BIT_64
#define PTR           U32         /* pointer */
#define PTRSIZE       sizeof(U32) /* pointer size */
#define PTRFAR                    /* pointer far */
#define STKALIGN      4           /* stack alignment */
#else /* BIT_64 */
#define PTR           U64         /* pointer */
/* envdep_h_001.main_78:Warning fix*/
#define PTRSIZE       sizeof(U64) /* pointer size */
/* #define PTRFAR                     pointer far */
#define STKALIGN      8           /* stack alignment */
#endif /* BIT_64 */

#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3                      /* register 3 */
#define REG4                      /* register 4 */
#define REG5                      /* register 5 */
#define REG6                      /* register 6 */
#define REG7                      /* register 7 */
#define REG8                      /* register 8 - lowest priority */

#define FAR           far         /* for large model */
#define PTRSTRIDE     1           /* stride */
#define MEM_SEG                   /* memory - segmented */
#endif /* I86LM */

#ifdef I86HM          /* Intel 80x86 huge model */

#define NULLP         0L          /* null pointer */
#define NULLD         0L          /* null data */
#ifndef BIT_64
#define PTR           U32         /* pointer */
#define PTRSIZE       sizeof(U32) /* pointer size */
#define PTRFAR                    /* pointer far */
#define STKALIGN      4           /* stack alignment */
#else  /* BIT_64 */
#define PTR           U64         /* pointer */
#define PTRSIZE       sizeof(U64) /* pointer size */
#define PTRFAR                    /* pointer far */
#define STKALIGN      8           /* stack alignment */
#endif  /* BIT_64 */

#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3                      /* register 3 */
#define REG4                      /* register 4 */
#define REG5                      /* register 5 */
#define REG6                      /* register 6 */
#define REG7                      /* register 7 */
#define REG8                      /* register 8 - lowest priority */

#define FAR           far         /* for huge model */
#define PTRSTRIDE     1           /* stride */
#define MEM_SEG                   /* memory - segmented */
#endif /* I86HM */

#ifdef PROC_68XXX                 /* Motorola 68040 model */

#define NULLP         0L          /* null pointer */
#define NULLD         0L          /* null data */
#define PTR           U32         /* pointer */
#define PTRSIZE       sizeof(U32) /* pointer size */
/* #define PTRFAR                     pointer far */
#define STKALIGN      4           /* stack alignment */

#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3          register    /* register 3 */
#define REG4          register    /* register 4 */
#define REG5          register    /* register 5 */
#define REG6          register    /* register 6 */
#define REG7          register    /* register 7 */
#define REG8          register    /* register 8 - lowest priority */

#define FAR                       /* for large model */

#ifdef PROC_68302
#define PTRSTRIDE     2           /* stride (simulation case: e.g. for elvis) */
#else
#ifdef PROC_68040
#define PTRSTRIDE     4           /* stride (simulation case: e.g. for elvis) */
#else /* other */
#define PTRSTRIDE     4           /* stride (simulation case: e.g. for elvis) */
#endif /* PROC_68040 */
#endif /* PROC_68302 */

#define MEM_NONSEG                /* memory - non-segmented */
#endif /* PROC_68XXX */


#ifdef PROC_SPARC                 /* SPARC */

#define NULLP         0L          /* null pointer */
#define NULLD         0L          /* null data */
#ifndef BIT_64
#define PTR           U32         /* pointer */
#define PTRSIZE       sizeof(U32) /* pointer size */
/* #define PTRFAR                     pointer far */
#define STKALIGN      4           /* stack alignment */
#else  /* BIT_64 */
#define PTR           U64         /* pointer */
#define PTRSIZE       sizeof(U64) /* pointer size */
/* #define PTRFAR                     pointer far */
#define STKALIGN      8           /* stack alignment */
#endif /* BIT_64 */

#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3          register    /* register 3 */
#define REG4          register    /* register 4 */
#define REG5          register    /* register 5 */
#define REG6          register    /* register 6 */
#define REG7          register    /* register 7 */
/*envdep_h_001.main_77 SSI-4GMX specfic changes*/
#ifndef SS_4GMX_LCORE
#define REG8          register    /* register 8 - lowest priority */
#endif

#define FAR                       /* for large model */
#define PTRSTRIDE     4           /* stride */
#define MEM_NONSEG                /* memory - non-segmented */
#endif /* PROC_SPARC */
#ifdef PROC_PARISC                /* HP PA RISC */

#define NULLP         0L          /* null pointer */
#define NULLD         0L          /* null data */
#ifndef BIT_64
#define PTR           U32         /* pointer */
#define PTRSIZE       sizeof(U32) /* pointer size */
/* #define PTRFAR                     pointer far */
#define STKALIGN      4           /* stack alignment */
#else
#define PTR           U64         /* pointer */
#define PTRSIZE       sizeof(U64) /* pointer size */
/* #define PTRFAR                     pointer far */
#define STKALIGN      8           /* stack alignment */
#endif /* BIT_64 */

#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3          register    /* register 3 */
#define REG4          register    /* register 4 */
#define REG5          register    /* register 5 */
#define REG6          register    /* register 6 */
#define REG7          register    /* register 7 */
#define REG8          register    /* register 8 - lowest priority */

#define FAR                       /* for large model */
#define PTRSTRIDE     4           /* stride */
#define MEM_NONSEG                /* memory - non-segmented */
#endif /* PROC_PARISC */

/*envdep_h_001.main_75 : RMIOS related changes*/
#ifdef SS_RMIOS
#define SPtr2l(ptr)		((unsigned long)(ptr))
#define SPtr2ll(ptr)	((unsigned long long)(unsigned long)(ptr))
#define SL2Ptr(l)		((PTR)(l))
#define SLL2Ptr(ll)		((PTR)(ll & 0xFFFFFFFF))

#define NULLP         0L          /* null pointer */
#define NULLD         0L          /* null data */
#ifndef BIT_64
#define PTR           U32         /* pointer */
#define PTRSIZE       sizeof(U32) /* pointer size */
#define STKALIGN      4           /* stack alignment */
#else  /* BIT_64 */
#define PTR           U64         /* pointer */
#define PTRSIZE       sizeof(U64) /* pointer size */
#define STKALIGN      8           /* stack alignment */
#endif /* BIT_64 */

#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3          register    /* register 3 */
#define REG4          register    /* register 4 */
#define REG5          register    /* register 5 */
#define REG6          register    /* register 6 */
#define REG7          register    /* register 7 */
#define REG8          register    /* register 8 - lowest priority */
#endif

#ifdef VAX            /* VAX */

#define NULLP         0L          /* null pointer */
#define NULLD         0L          /* null data */
#define PTR           U32         /* pointer */
#define PTRSIZE       sizeof(U32) /* pointer size */
/* #define PTRFAR                     pointer far */
#define STKALIGN      4           /* stack alignment */

#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3          register    /* register 3 */
#define REG4          register    /* register 4 */
#define REG5          register    /* register 5 */
#define REG6          register    /* register 6 */
#define REG7          register    /* register 7 */
#define REG8          register    /* register 8 - lowest priority */

#define FAR                       /* for large model */
#define PTRSTRIDE     2           /* stride */
#define MEM_NONSEG                /* memory - non-segmented */
#endif


#ifdef ALPHA          /* ALPHA */

#define NULLP         0L          /* null pointer */
#define NULLD         0L          /* null data */
#define PTR           U64         /* pointer */
#define PTRSIZE       sizeof(U64) /* pointer size */
/* #define PTRFAR                     pointer far */
#define STKALIGN      8           /* stack alignment */

#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3          register    /* register 3 */
#define REG4          register    /* register 4 */
#define REG5          register    /* register 5 */
#define REG6          register    /* register 6 */
#define REG7          register    /* register 7 */
#define REG8          register    /* register 8 - lowest priority */

#define FAR                       /* for large model */
#define PTRSTRIDE     2           /* stride */
#define MEM_NONSEG                /* memory - non-segmented */
#endif

#ifdef PROC_68360                 /* Motorola 68040 model */

#define NULLP         0L          /* null pointer */
#define NULLD         0L          /* null data */
#define PTR           U32         /* pointer */
#define PTRSIZE       sizeof(U32) /* pointer size */
/* #define PTRFAR                     pointer far */
#define STKALIGN      4           /* stack alignment */

#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3          register    /* register 3 */
#define REG4          register    /* register 4 */
#define REG5          register    /* register 5 */
#define REG6          register    /* register 6 */
#define REG7          register    /* register 7 */
#define REG8          register    /* register 8 - lowest priority */

#define FAR                       /* for large model */

#define PTRSTRIDE     4           /* stride (simulation case: e.g. for elvis) */
#define MEM_NONSEG                /* memory - non-segmented */
#endif /* PROC_68360 */


#ifdef PROC_PPC                   /* SPARC */

#define NULLP         0L          /* null pointer */
#define NULLD         0L          /* null data */
#ifndef BIT_64
#define PTR           U32         /* pointer */
#define PTRSIZE       sizeof(U32) /* pointer size */
/* #define PTRFAR                     pointer far */
#define STKALIGN      4           /* stack alignment */
#else  /* BIT_64 */
#define PTR           U64         /* pointer */
#define PTRSIZE       sizeof(U64) /* pointer size */
/* #define PTRFAR                     pointer far */
#define STKALIGN      8           /* stack alignment */
#endif /* BIT_64 */

#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3          register    /* register 3 */
#define REG4          register    /* register 4 */
#define REG5          register    /* register 5 */
#define REG6          register    /* register 6 */
#define REG7          register    /* register 7 */
#define REG8          register    /* register 8 - lowest priority */

#define FAR                       /* for large model */
#define PTRSTRIDE     4           /* stride */
#define MEM_NONSEG                /* memory - non-segmented */
#endif /* PROC_PPC */


#ifdef SS_PS                      /* 32-bit pSOS */
#define NULLP         0L          /* null pointer */
#define NULLD         0L          /* null data */
#ifndef BIT_64
#define PTR           U32         /* pointer */
#define PTRSIZE       sizeof(U32) /* pointer size */
#define STKALIGN      4           /* stack alignment */
#else  /* BIT_64 */
#define PTR           U64         /* pointer */
#define PTRSIZE       sizeof(U64) /* pointer size */
#define STKALIGN      8           /* stack alignment */
#endif /* BIT_64 */


#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3          register    /* register 3 */
#define REG4          register    /* register 4 */
#define REG5          register    /* register 5 */
#define REG6          register    /* register 6 */
#define REG7          register    /* register 7 */
#define REG8          register    /* register 8 - lowest priority */

#define FAR                       /* for large model */
#define PTRSTRIDE     4           /* stride */
#endif /* SS_PS */


#ifdef OTHMOD         /* All other models */

#define NULLP         0L          /* null pointer */
#define NULLD         0L          /* null data */
/* envdep_h_001.main_76    WIN32 and WIN64 falls here, so be sure PTR is correctly defined
 * when compiling 64bits 
 */
/*envdep_h_001.main_77 SSI-4GMX specfic changes*/
#ifndef SS_4GMX_LCORE
#ifdef _WIN64
#define PTR           U64         /* pointer */
#define PTRSIZE       sizeof(U64) /* pointer size */
#define STKALIGN      8           /* stack alignment */
#else /* _WIN64 */
#define PTR           U32         /* pointer */
#define PTRSIZE       sizeof(U32) /* pointer size */
#define STKALIGN      4           /* stack alignment */
#endif
#else
#define PTR           U32         /* pointer */
#define PTRSIZE       sizeof(U32) /* pointer size */
#define STKALIGN      4           /* stack alignment */
#endif

#define REG1          register    /* register 1 - highest priority */
#define REG2          register    /* register 2 */
#define REG3          register    /* register 3 */
#define REG4          register    /* register 4 */
#define REG5          register    /* register 5 */
#define REG6          register    /* register 6 */
#define REG7          register    /* register 7 */
#define REG8          register    /* register 8 - lowest priority */

#define FAR                       /* for large model */
#define PTRSTRIDE     2           /* stride */
#define MEM_NONSEG                /* memory - non-segmented */
#endif


/* pointer alignment macro */

#define PTRALIGN(s) ((PTR)(s) % PTRSTRIDE ? ((PTR)(s) + (PTRSTRIDE - ((PTR)(s) % PTRSTRIDE))) : (PTR)(s))
/*
 * This macro (DATAALIGN) should only be used in our
 * static memory algorithms (SGetSBuf). 
 *
 * Otherwise, use at your own risk!
 */
#define DATAALIGN(s) ((Size)(s) % PTRSTRIDE ? ((Size)(s) - (PTRSTRIDE - ((Size)(s) % PTRSTRIDE))) : (Size)(s))


/* message function type macro */

typedef U32 MFTYPE;


/* typedef and defines for argument manipulation */
  
typedef S8               *ARGTYPE;

#define ARG(argp,type)     *((type*)argp)

#define ARGINC(argp,type)  argp=(ARGTYPE)(argp + (sizeof(type) < STKALIGN ? STKALIGN : sizeof(type)))

/* Unused function parameter macro */

#ifdef UNUSED
#undef UNUSED
#define UNUSED(x) (x=x)
#else
#define UNUSED(x) (x=x)
#endif /* UNUSED */


/**********************************************************************
   defines for trace
**********************************************************************/

/*
   trace macros are at the beginning of each function. they may
   be used for debugging purposes. the trace macros are turned on
   by the following command line option:

   TRACE0  - trace mos support functions
   TRACE1  - trace mos interface functions
   TRACE2  - trace layer support functions
   TRACE3  - trace layer interface functions
   TRACE4  - trace interrupt service functions

   there is one additional trace macro which turns on trace macros 0 - 4
   and pushes the text within trace macros 0 - 4 onto a stack. the text
   is popped of of the stack upon RETVOID or RETVALUE. this macro is:

   TRACE5  - trace call stack

*/
  
#ifdef TRACE5           /* trace 5 - call stack */
#define TRACE0          /* trace 0 - mos support functions */
#define TRACE1          /* trace 1 - mos interface functions */
#define TRACE2          /* trace 2 - layer support functions */
#define TRACE3          /* trace 3 - layer interface functions */
#define TRACE4          /* trace 4 - interrupt service functions */

#define T5M 64          /* trace 5 - maximum call stack height */
extern S8 *t5s[];       /* trace 5 - call stack */
extern S16 t5t;         /* trace 5 - top of call stack */
#ifdef ERRCHK
extern Void FAR exit(int);
#endif
#endif

#ifdef TRACE5           /* trace 5 - call stack */
#ifdef ERRCHK
#define TRC0(a)         if(t5t>=0&&t5t<T5M-1) t5s[t5t++] = #a; else exit(0); 
#else
#define TRC0(a)         t5s[t5t++] = #a;
#endif
#else
#ifdef TRACE0           /* trace 0 - mos support functions */
#ifdef ANSI             /* ansi */
#define TRC0(a)         printf(#a "\n");
#else                   /* not ansi */
#define TRC0(a);
#endif
#else
#define TRC0(a);
#endif
#endif
  
#ifdef TRACE5           /* trace 5 - call stack */
#ifdef ERRCHK
#define TRC1(a)         if(t5t>=0&&t5t<T5M-1) t5s[t5t++] = #a; else exit(0); 
#else
#define TRC1(a)         t5s[t5t++] = #a;
#endif
#else
#ifdef TRACE1           /* trace 1 - mos interface functions */
#ifdef ANSI             /* ansi */
#define TRC1(a)         printf(#a "\n");
#else                   /* not ansi */
#define TRC1(a)         ; 
#endif
#else
#define TRC1(a);
#endif
#endif
  
#ifdef TRACE5           /* trace 5 - call stack */
#ifdef ERRCHK
#define TRC2(a)         if(t5t>=0&&t5t<T5M-1) t5s[t5t++] = #a; else exit(0); 
#else
#define TRC2(a)         t5s[t5t++] = #a;
#endif
#else
#ifdef TRACE2           /* trace 2 - layer support functions */
#ifdef ANSI             /* ansi */
/* envdep_h_001.main_68  Corrected the macro */
#define TRC2(a)         printf(#a "\n"); 
#else                   /* not ansi */
#define TRC2(a)         ; 
#endif
#else
#define TRC2(a);
#endif
#endif
  
#ifdef TRACE5           /* trace 5 - call stack */
#ifdef ERRCHK
#define TRC3(a)         if(t5t>=0&&t5t<T5M-1) t5s[t5t++] = #a; else exit(0); 
#else
#define TRC3(a)         t5s[t5t++] = #a;
#endif
#else
#ifdef TRACE3           /* trace 3 - layer interface functions */
#ifdef ANSI             /* ansi */
/* envdep_h_001.main_68  Corrected the macro */
#define TRC3(a)         printf(#a "\n");
#else                   /* not ansi */
#define TRC3(a)         ; 
#endif
#else
#define TRC3(a);
#endif
#endif

#ifdef TRACE5           /* trace 5 - call stack */
#ifdef ERRCHK
#define TRC4(a)         if(t5t>=0&&t5t<T5M-1) t5s[t5t++] = #a; else exit(0); 
#else
#define TRC4(a)         t5s[t5t++] = #a;
#endif
#else
#ifdef TRACE4           /* trace 4 - interrupt service functions */
#ifdef ANSI             /* ansi */
#define TRC4(a)         printf(#a "\n");
#else                   /* not ansi */
#define TRC4(a);
#endif
#else
#define TRC4(a);
#endif
#endif

  
/**********************************************************************
   returns
**********************************************************************/

/*
   these returns are arranged first by environment (DOS, UNIX or
   embedded) followed by compiler (microsoft c, borland c, unix or
   microtec c) as appropriate.
*/

#ifdef DOS                        /* dos */
#ifdef MSC51                      /* dos, microsoft c */
#ifdef TRACE5
#define RETVOID     return(--t5t?(Void) 0 :(Void) 0)  /* return void */
/* envdep_h_001.main_76: Removed void type casting */
#define RETVALUE(v) return(--t5t?(v):(v)) /* return value */
#else
#define RETVOID     return        /* void */
#define RETVALUE(v) return(v)     /* return value */
#endif
#else                             /* not microsoft c */
#ifdef BOR31                      /* dos, borland c */
#ifdef TRACE5
#define RETVOID     return(--t5t?(Void) 0 :(Void) 0)  /* return void */
/* envdep_h_001.main_76: Removed void type casting */
#define RETVALUE(v) return(--t5t?(v):(v)) /* return value */
#else
#define RETVOID     return        /* void */
#define RETVALUE(v) return(v)     /* return value */
#endif
#else                             /* not borland c */
#endif
#endif
#else                             /* not dos */
#ifdef UNIX                       /* unix */
#ifdef TRACE5
#define RETVOID     return(--t5t?(Void) 0 :(Void) 0)  /* return void */
/* envdep_h_001.main_76: Removed void type casting */
#define RETVALUE(v) return(--t5t?(v):(v)) /* return value */

#else
#define RETVOID     return        /* void */
#define RETVALUE(v) return(v)     /* return value */
#endif
#else                             /* not unix */
#ifdef MOTADS                     /* embedded, motorola ads */
#ifdef DOSMRI42D                  /* dos microtec c cross-compiler */
#ifdef TRACE5
#define RETVOID     return(--t5t?(Void) 0 :(Void) 0)  /* return void */
/* envdep_h_001.main_76: Removed void type casting */
#define RETVALUE(v) return(--t5t?(v):(v)) /* return value */
#else
#define RETVOID     return        /* void */
#define RETVALUE(v) return(v)     /* return value */
#endif
#else                             /* not dos microtec c */
#ifdef SOLMRI43                   /* solaris microtec c cross-compiler */
#ifdef TRACE5
#define RETVOID     return(--t5t?(Void) 0 :(Void) 0)  /* return void */
/* envdep_h_001.main_76: Removed void type casting */
#define RETVALUE(v) return(--t5t?(v):(v)) /* return value */
#else
#define RETVOID     return        /* void */
#define RETVALUE(v) return(v)     /* return value */
#endif
#else                             /* not solaris microtec c cross-compiler */
#ifdef SOLOAS186                  /* solaris oasys c cross-compiler */
#ifdef TRACE5
#define RETVOID     return(--t5t?(Void) 0 :(Void) 0)  /* return void */
/* envdep_h_001.main_76: Removed void type casting */
#define RETVALUE(v) return(--t5t?(v):(v)) /* return value */
#else
#define RETVOID     return        /* void */
#define RETVALUE(v) return(v)     /* return value */
#endif
#else                             /* not microtec c, not oasys c */
#endif
#endif
#endif
#else                             /* not motorola ads */
#ifdef TRACE5
#define RETVOID     return(--t5t?(Void) 0 :(Void) 0)  /* return void */
/* envdep_h_001.main_76: Removed void type casting */
#define RETVALUE(v) return(--t5t?(v):(v)) /* return value */
#else
#define RETVOID     return        /* void */
#define RETVALUE(v) return(v)     /* return value */
#endif
#endif                            /* motorola ads */
#endif                            /* unix */
#endif                            /* dos */


/* General Macros - Moved from envind.h */
#ifndef HPOS
#ifdef MIN
#undef MIN
#define MIN(x, y) ((x) > (y) ? (y) : (x))            /* get minimum value */
#else
#define MIN(x, y) ((x) > (y) ? (y) : (x))            /* get minimum value */
#endif /* MIN */

#ifdef MAX
#undef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))            /* get maximum value */
#else
#define MAX(x, y) ((x) > (y) ? (x) : (y))            /* get maximum value */
#endif /* MAX */
#endif /* HPOS */



/*

   The following defines are used as switches throughout the
   TRILLIUM software 

   PORTVER   Portable version
   MOSVER    MOS version

   LCINT     Loosely coupled - isdn network layer
   TCINT     Tightly coupled - isdn network layer 
   LCXNT     Loosely coupled - x.25 network layer
   TCXNT     Tightly coupled - x.25 network layer 
   LCDAT     Loosely coupled - data link layer
   TCDAT     Tightly coupled - data link layer 
   LCMAC     Loosely coupled - mac layer
   TCMAC     Tightly coupled - mac layer
   LCLM      Loosely coupled - layer management
   TCLM      Tightly coupled - layer management

   ANSI      ansi

   DOS       dos environment
   UNIX      unix environment
 
   MSC51     microsoft c 5.1 compiler
   MSC60     microsoft c 6.0 compiler
   MSC70     microsoft c 7.0 compiler
   DOSMRI42D dos microtec c 4.2D cross-compiler
   SOLMRI43  solaris microtec c 4.3 cross-compiler
   SOLOAS186 solaris oasys 1.8.6 cross-compiler
   BOR31     borland c 3.1 compiler

   SUNOS     sun os environment
   SUNOS41   sun os 4.1 environment and compiler
   SUNOS51   sun os 5.1 environment and compiler
  
   MSCDOS    microsoft c, DOS environment - being phased out
   MSCUNIX   microsoft c, UNIX environment - being phased out

   UC2       Franklin UC2A interface
   WT3       Retix WT-330 interface
   FUT       Dassault AT-FUT interface
   MDP       Dassault MOS/Driver interface

   ERRCHK    Error check

   TRC0      Trace 0 - MOS support functions
   TRC1      Trace 1 - MOS interface functions
   TRC2      Trace 2 - layer support functions
   TRC3      Trace 3 - layer interface functions
   TRC4      Trace 4 - interrupt service functions

   X28X29    X.28 and X.29 support

*/
    

#ifdef __cplusplus
}
#endif


#endif /* __ENVDEPH__ */

  
/********************************************************************30**
  
         End of file:     envdep.h@@/main/79 - Thu Apr 18 15:23:54 2013
  
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
1.1.0.0         jrl     1. initial release.

1.2.0.0         jrl     2. miscellaneous changes.

1.3.0.0         jrl     1. add stringizing operator to trace macros.
                        2. remove elif to improve portability

1.4.0.0         jrl     1. add support for Borland Turbo C
                        2. make defines for various memory models
                            generic to improve portability

1.5.0.0         jrl     1. add microsoft unix support
                        2. text changes

1.6.0.0         jrl     1. add typedefs for UNIX support
                        2. add PTRFAR for UNIX support
                        3. text changes

1.7.0.0         jrl     1. add argument manipulation for ansi or
                           non ansi function prototypes
                        2. separate MSCDOS and MSCUNIX into consituent
                           parts, __MSC__, DOS, UNIX and add usage of
                           ANSI to make protocol layers independent of
                           __MSC__, DOS and UNIX. Protocol layers will
                           be dependent on ANSI or non ANSI. MOS will
                           be dependent DOS, UNIX and ANSI or non ANSI.
                           improves portability.
                        3. text changes
                        4. remove Borland Turbo C support
 
1.8             mma     1. add FAR define for memory models
                mma     3. support of GNU compiler (define EXTERN), and
                           MSC60 define
                jrl     4. trillium development system checkpoint (dvs)
                           at version: 1.7.0.0
                jrl     5. remove octStrg typedef and move to gen.x

1.9             gp      1. created Void typedef (in addition to VOID)
                gp      2. unix case, replaced typedef void VOID with
                           typedef S16 VOID
                jrl     3. text changes
                jrl     4. add RETVOID define
                jrl     5. add CONSTANT define

1.10            kgi     1. add environment define for Motorola ADS and 
                           microtec compiler
                mma     2. eliminate nesting of MSC51 over UNIX so that
                           UNIX alone will suffice

1.11            jrl     1. added Void for MOTADS

1.12            jrl     1. add MSC51 to other case for model section

1.13            nkk     1. changed the unordered pair of lines from:
                              typedef void VOID;
                              typedef void Void;
                           to the ordered pair of lines:
                              typedef void Void;
                              typedef Void VOID;
                           as well as the comments which refered to them.
                nkk     2. delete the following products from the "combined 
                           with" list: 
                              Multilink, Spanning Tree, ISO IP (End System),
                              and ISO IP (Intermediate System).
                nkk     3. add the following products to the "combined 
                           with" list: 
                              MOS, SDLC, MTP Level 2, 
                              MTP Level 3, ISUP, TCAP, ADCCP-NRM, 
                              SNMP Agent, SNMP Tools, SNMP Package, 
                              SCARF, and ESCC.
                mma     4. use "far" in INTERRUPT macro only when I86LM
                           is defined.
                nkk     5. define "I86LM" when BOR31.
                jrl     6. add compatibility for MSC70 and BOR31
                jrl     7. text changes

*********************************************************************71*/

/********************************************************************80**

  version    pat  init                   description
----------- ----- ----  ------------------------------------------------
1.14         ---  jrl   1. text changes

1.15         ---  jrl   1. add support for sun os, sparc and borland c.
                           borland c not fully tested yet.

1.16         ---  jrl   1. add INTERRUPT to PIF typedefs
             ---  jrl   2. change void to Void for PIF typedefs
             ---  jrl   3. add INTERRUPT to BOR31
             ---  jrl   4. change S16 to void and return(ROK) to
                           return for embedded not motorola

1.17         ---  nkk   1. remove INTERRUPT from MOTADS PIF typedef.
             ---  mma   2. add MS_STRIDE for pointer boundary alignment

1.18         ---  nkk   1. remove "#define ANSI" after "#ifdef MOTADS".
             ---  nkk   2. move MRI68K and PROC_68302 defines from after
                           "backward compatibility" section to the
                           "memory models" section.
             ---  jrl   3. add SUNOS41 and SUNOS51 backward compatibility

1.19         ---  jrl   1. text changes

1.20         ---  nkk   1. add ISR_PUSH_ENV and ISR_POP_ENV macros
             ---  jrl   2. add PTRALIGN macro
             ---  jrl   3. change MS_STRIDE to PTRSTRIDE

1.21         ---  jrl   1. add MEM_SEG and MEM_NONSEG for segmented and
                           non-segmented processors

1.22         ---  nkk   1. change I86LM to I86HM for MSC51 for PIF
                           typedef

1.23         ---  nkk   1. move I86HM from typedef to INTERRUPT define

1.24         ---  lc    1. text changes

1.25         ---  nkk   1. added support for solaris MRI and solaris
                           oasys c-compilers.

1.26         ---  nkk   1. added TRC4 for interrupt service routines

1.27         ---  nkk   1. remove (again, see 1.17) INTERRUPT from MOTADS 
                           PIF typedefs (DOSMRI42D and SOLMRI43).
             ---  nkk   2. define unconditionally M68 if MOTADS is defined.

1.28         ---  nkk   1. define MRI68K when SOLMRI43 or DOSMRI42D.

1.29         ---  nkk   1. added TRACE5 for call stack debugging.
             ---  nkk   2. removed size_t typedef.
             ---  nkk   3. changed return(ROK) to return and Void to void
                           for UNIX.
             ---  jrl   4. add VAX processor

1.30         ---  jrl   5. add prototype for sprintf

1.31         ---  jrl   1. default SUNOS to SUNOS51

1.32         ---  jrl   1. add support for ALPHA processor

1.33         ---  fmg   1. add VOLATILE

1.34         ---  fmg   1. add and change defines for Borland C

1.35         ---  jrl   1. remove PTRFAR from SPARC, VAX, M68, ALPHA

1.36         ---  nkk   1. add elvis support for sparc, 68040 and 68302
                           processors.
             ---  nkk   2. made M68 and SPARC exclusive over PTRSTRIDE
             ---  nkk   3. added M68-SUNOS-PTRSTRIDE (with a value 4)
                           to allow simulation of M68 processor on
                           the sun.
             ---  nkk   4. defined PTRFAR only for DOS large/huge models.

1.37         ---  fmg   1. wrapped sprintf declaration within 
                           #ifndef STDIO_INCLD #endif
             ---  jrl   2. add DATAALIGN define
             ---  bn    3. add MFTYPE typdef
             ---  bn    4. remove interrupt for Microtec 68k
             ---  mc    5. renamed SPARC to be SPARC_MOD. 
             ---  mc    6. added "#ifdef VW" surrounding "typedef Void
                           VOID" and "prototype for sprintf".

1.38         ---  jrl   1. add interrupt for Microtec 68k

1.39         ---  fmg   1. changed SPARC_MOD to PROC_SPARC for
                           consistency with ELVIS.
             ---  fmg   2. removed typedef VOID
             ---  fmg   3. updated for ELVIS compatibility
             ---  fmg   4. changed INTERRUPT to INTERRPT for
                           compatibility with RMX environment
             ---  fmg   5. changed 680X0 to 68XXX

1.40         ---  fmg   1. added typedef for ALPHA S32,U32,S64, and U64
                           (Change Log Id: ENVDEPH1_39ID000)

1.41         ---  nkk   1. added ANSI/K&R Ptr typedef.
             ---  fmg   2. added UNUSED macro

1.42         ---  fmg   1. added support for 68360

1.43         ---  fmg   1. added support for QUICCADS

1.44         ---  vk    1. WIN32 changes

1.45         ---  rg    1. added "#undef OTHMOD" to #ifdef ALPHA.

1.46         ---  fmg   1. added INLINE defines

1.47         ---  fmg   1. added comments around __GNUC__

1.48         ---  fmg   1. changes to vxworks prototypes

1.49         ---  fmg   1. added support for POWER_STACK --
                           UNIX,AIX,PROC_PPC

1.50         ---  sa    1. corrected nested comments.

1.51         ---  fmg   1. added ARGS around sprintf for SUNOS

1.52         ---  fmg   1. added support for ALC_EVAL and PROC_68349

1.53         ---  kr    1. added VOLATILE and __INLINE__ macros for WIN32
             ---  kr    2. changed typedefs of S16 and S32 for WIN32
             ---  kr    3. added VOLATILE macro for GNUC

*********************************************************************81*/

/********************************************************************90**
 
    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
1.54         ---      fmg  1. fixed DATAALIGN macro (it was broken).
             ---      ash  2. added support for GSIP302
             ---      ash  3. added support for GNUC compiler in PROC_68302
             ---      ash  4. correction in ifdef sequence just after 
                             PROC_68302
 
1.55         ---      apr  1. miscellaneous changes.

1.56         ---      skr  1. introduced PROC_PPC & PQUICCADS for MPC860 
1.57         ---      bbk  1. Changed copyright header date.

1.58         ---      ada  1. Added Voiceboard (VB_360) and PowerQUICC
                             (PQ_PPC860, PROC_PPC680) sections
             ---      ada  2. Removed define for ELVIS_PPC
             ---      mb   3. Added section for PCORE

1.59         ---      kp   1. Added extern "C" for making this file C++
                              compilable

1.61         ---      ada  1. Added comments

1.62         ---      ada  1. Added pSOS (SS_PS) section

1.63         ---      tej  1. Change in header

1.64         ---      bsr  1. Added U64 and S64 for WIN32

1.65         ---      vrp  1. added the inline assembly macro in SS_PS 
                              section and removed the I_ENTER/I_RETURN 
                              macros in SS_PS section.

/main/60     ---      sa   1. corrected compilation problem for ALPHA
/main/61     ---      jjn  1. Added a new flag BIT_64 for 64 Bit support
                              for unix, win32, power pc and pSOS 
                              environments.
/main/62     ---      bdu  1. Added HP Unix and PROC_PARISC section.
                      cvp  2. Moved definitions of MIN and MAX from 
                              envind.h. 
                           3. changed the copyright header
/main/63     ---      bdu  1. Bug fix for sprintf definition.
/main/64     ---      pk   1. Added support for VXWORKS_PENTIUM
/main/65     ---      sal  1. Created for Release of 2.1(RFC 3868 Support)
/main/66     ---      sal  1. Corrected the TRC2 and TRC3 macros.
/main/67     ---      sk       1. Updated for PSF-SIP 1.1 Release
/main/68     ---      svp  1. Added F32 and F64 types 
envdep_h_001.main_68  sal  1. Corrected the TRC2 and TRC3 macros.
/main/70     ---      ch   1. Updated copyright SSI Multicore Support release.
/main/71     ---      envdep_h_001.main_70 rss 1. __USE_UNIX98 defined for using readwrite locks
/main/72     ---      envdep_h_001.main_71 pmacharla  1. U64 and S64 added for UNIX and DOS/MSC51
/main/73     ---      envdep_h_001.main_72 pmacharla  1. Addition Support for C89 standard 
/main/74     ---      envdep_h_001.main_73 rss        1. stdint.h and _USE_UNIX98 are required
                                                         only for SS_LINUX, not required for SUNOS
/main/75     ---      envdep_h_001.main_74 pmacharla  1.VXWORKS_DIAB is added for Diab compiler
                                                      2.__USE_UNIX98 is guarded under _GNU_SOURCE 
/main/76     ---      envdep_h_001.main_75 ssahniX  1. RMIOS related changes
/main/77     ---      envdep_h_001.main_76 rk         1. Removed void type casting for RETVALUE
                                           ssahniX    2. Fix for 64_bit Windows
/main/78     ---      envdep_h_001.main_77 ssahniX    1. SSI-4GMX specific changes
/main/79     ---      envdep_h_001.main_78 akaranth   1. removed SSI-4GMX specfic changes
                                                      2. Warning fix
*********************************************************************91*/

