/********************************************************************20**
  
     Name:     solaris library
  
     Type:     C include file
  
     Desc:     Defines required by the solaris library.
  
     File:     cm_os.h
  
     Sid:      cm_os.h 1.5  -  07/23/98 18:02:40
  
     Prg:      fmg
  
*********************************************************************21*/

#ifndef __CMOSH__
#define __CMOSH__


/* defines */

#ifdef NTSSLIB
#define DEF_NTSSLIB    1
#ifdef FAR
#undef FAR
#endif
#ifdef NEAR
#undef NEAR
#endif
#include <windows.h>
#include <io.h>
#endif /* NTSSLIB */

#ifdef NU
#define DEF_NU         1
#endif
/* os */

#define SLEN          64        /* string length */
#define WORD_LEN      40        /* word length */
#define FILE_NAME_LEN 80        /* file name length */
#define LINE_LEN      256       /* line length */
#define MATCH_FAILED  -1

#define OS_SEEK_SET   0
#define OS_SEEK_CUR   1
#define OS_SEEK_END   2

#define OS_RDONLY     0
#define OS_WRONLY     1
#define OS_RDWR       2
#define OS_CREAT      0x100   /* open with file create */


#define OS_PROT_NONE  0x0
#define OS_PROT_READ  0x1
#define OS_PROT_WRITE 0x2
#define OS_PROT_EXEC  0x4

#define OS_MAP_SHARED       1
#define OS_MAP_PRIVATE      2
#define OS_MAP_FIXED        0x10
#define OS_MAP_NORESERVER   0x40
#define OS_MAP_FAILED      ((Void *) -1)

/* thread types */
#define OS_MT_THR_NOFLAGS   0x00
#define OS_MT_THR_SUSPENDED 0x01
#define OS_MT_THR_DETACHED  0x02
#define OS_MT_THR_BOUND     0x04
#define OS_MT_THR_NEW_LWP   0x08
#define OS_MT_THR_DAEMON    0x10
 
/* thread priorities */
#define OS_MT_LOW_PRI          0
#define OS_MT_NORM_PRI         10
#define OS_MT_HIGH_PRI         20

/* error */

/* ipc */

/*
 *   Max total message is 8K.
 *   Max data is 8K - mesg_type - Pst (header)
 */
#define MAXMESGDATA (8192-(2*sizeof(S32))-sizeof(Pst))      
#define MESGHDRSIZE (sizeof (Mesg) - MAXMESGDATA)

#define STK_KEY_BASE 1234L      /* Stack Key Base */

#define PERMS        0666       /* Permissions */

#define MAXQUES      4

#endif /* __CMOSH__ */


/********************************************************************30**

         End of file: cm_os.h 1.5  -  07/23/98 18:02:40

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/


/*********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- -----------------------------------------------
1.1            ---    fl   1. 'commonised' libraries.

1.2            ---    fl   1. renamed os_lib.* to cm_os.*

1.3            ---    mb   1. Release for Integ ss7

1.4            ---    ap   1. SLEN is changed to 64.

1.5            ---    ag   1. Changed for Windows NT. Added DEF_NU
                              and DEF_NTSSLIB for compilation with 
                              UNTSS or with application
**********************************************************************91*/
