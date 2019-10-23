/********************************************************************20**
     Name:      Common Operating System Library
  
     Type:     C source file
  
     Desc:     C source code library
  
     File:     cm_os.c
  
     Sid:      cm_os.c@@/main/nodal_main/lp_crfix_branch/1 - Wed Jan 22 19:52:22 2014
  
     Prg:      fmg
  
*********************************************************************21*/


#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
 
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_os.h"         /* os library */
 
#include "gen.x"           /* general */
#include "cm_os.x"         /* os library */
#include "ssi.x"           /* system services */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#if !(DEF_NTSSLIB | DEF_NU)
#include <unistd.h>
#endif /* DEF_NTSSLIB */
#include <fcntl.h>
#ifdef ANSI
#include <stdarg.h>
#else
#include <varargs.h>
#endif /* ANSI */

/* cm_os_c_001.main_12: Including MSPD header file for 4GMX */
#ifdef SS_4GMX_LCORE
#include "basetypes.h"
#else
#include <sys/types.h>
#endif
/* cm_os_c_001.main_10: Added header file to remove TCGETS/TCSETS errors */
/* cm_os_c_001.main_12: Excluding header file for 4GMX */
#ifndef SS_4GMX_LCORE
#include <sys/ioctl.h>
#endif
#if !(DEF_NTSSLIB | DEF_NU)
/* cm_os_c_001.main_12: Excluding header files for 4GMX */
#ifndef SS_4GMX_LCORE
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#endif
#include <errno.h>


#ifdef AIX
#include <termio.h>
#endif /* AIX */

/* cm_os_c_001.main_12: Excluding header files for 4GMX */
#ifndef SS_4GMX_LCORE
#include <termios.h>
#include <stropts.h>
#include <poll.h>
#endif
#endif /* DEF_NTSSLIB */

/* cm_os_c_001.main_10: It should exclude SS_LINUX */
#ifndef SS_LINUX
#ifdef SUNOS51
#ifndef ANSI
EXTERN Void perror ARGS((S8 *));
EXTERN OsInt sigemptyset ARGS((sigset_t *));
EXTERN OsInt sigaddset ARGS((sigset_t *, OsInt));
EXTERN OsInt sigaction ARGS((OsInt, struct sigaction *, struct sigaction *));
#endif /* ANSI */
#endif /* SUNOS51 */

#ifdef SUNOS51
#include <thread.h>
#endif /* SUNOS51 */
#endif /* SS_LINUX */

/* local defines */

#ifndef CLIENT
#define CLIENT 1
#endif
 
#define CMSDEVFILE            "/dev/FTlog:cms"
#define MAX_MSGSEND_RETRIES   50000

#ifndef NULL
#define NULL ((void*)0)
#endif

/* functions in other modules */
#ifdef DBGMSG
EXTERN S32 perror ARGS((CONST S8 *));  
#endif /* DBGMSG */

/* forward references */
#ifdef __cplusplus
extern "C" {
#endif
/* cm_os_c_001.main_10: return type added */
EXTERN void* mmap ARGS((S8 *addr, OsSize len, OsInt prot, OsInt flags,OsInt fildes,
            OsLong off));
EXTERN OsInt munmap ARGS((S8 *addr, OsSize len));
EXTERN S32 mlockall(S32);
EXTERN S32 munlockall(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifndef SS_LINUX
/* cm_os_c_001.main_10: These are conflicting with definitions provided
   in standard header files */
EXTERN S32 sys_nerr;
EXTERN S8 *sys_errlist[];
#endif

PRIVATE Void INTERRPT msgClean ARGS((void));

PRIVATE Void myPerror ARGS((void));
PRIVATE S8 * sysErrStr ARGS((void));

/* public variable declarations */
 
PUBLIC Txt *pname = NULL;

/* variable declarations */
PUBLIC S8 *OsOptArg;
PUBLIC OsInt OsOptInd;
PUBLIC OsInt OsOptErr;
PUBLIC OsInt OsOptOpt;

PRIVATE S32 stkMsgId[MAXQUES] = { -1, -1, -1, -1 };
PRIVATE Bool MsgInit = FALSE;

PUBLIC Txt osPrgNme[] = "libos";            /* program name */
PUBLIC Txt osPrgVer[] = "1.3";              /* program version */

PUBLIC Bool soOptDebug = 8;                 /* debug */
PRIVATE int  conFd;
PRIVATE S32  cmsFd;                         /* cms files descriptor */

#if (DEF_NTSSLIB | DEF_NU)
PRIVATE HANDLE cInHdl;
PRIVATE HANDLE cOutHdl;
PRIVATE U8     optind=1;
#endif /* DEF_NTSSLIB */

/* local defines */
 
#define  EOSBASE     (ERROS   + 0)      /* reserved */
 
#define  EOS001      (EOSBASE + 1)      /*   */
#define  EOS002      (EOSBASE + 2)      /*   */
#define  EOS003      (EOSBASE + 3)      /*   */
#define  EOS004      (EOSBASE + 4)      /*   */
#define  EOS005      (EOSBASE + 5)      /*   */
#define  EOS006      (EOSBASE + 6)      /*   */
#define  EOS007      (EOSBASE + 7)      /*   */
#define  EOS008      (EOSBASE + 8)      /*   */
#define  EOS009      (EOSBASE + 9)      /*   */
#define  EOS010      (EOSBASE + 10)     /*   */
#define  EOS011      (EOSBASE + 11)     /*   */


/*
*
*       Fun:   osExit
*
*       Desc:  exit from system
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osExit
(
OsInt code           /* exit code */
)
#else
PUBLIC Void osExit(code)
OsInt code;
#endif
{
   TRC2(osExit)

#if (DEF_NTSSLIB | DEF_NU)
  ExitProcess(code);
#else
  exit(code);
#endif /* DEF_NTSSLIB */
  RETVOID;
}

/*
*
*       Fun:   osPerror
*
*       Desc:  print error message (to stderr) 
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osPerror
(
Txt *msg        /* error message */
)
#else
PUBLIC Void osPerror(msg)
Txt *msg; /*error message */
#endif
{
   TRC2(osPerror)

   perror(msg);
   RETVOID;
} /* end of osPerror */


/*
*
*       Fun:   osBzero
*
*       Desc:  zero memory
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osBzero
(
OsVoid *ptr,
OsSize size
)
#else
PUBLIC Void osBzero(ptr, size)
OsVoid *ptr;
OsSize size;
#endif
{
   TRC2(osBzero)
   osMemset((OsVoid *)ptr, 0, (OsSize)size);
   RETVOID;

} /* end of osBzero */


/*
*
*       Fun:   osMemset
*
*       Desc:  wrapper for memset 
*
*       Ret:   return from memset
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsVoid *osMemset
(
OsVoid *s,
OsInt c,
OsSize len
)
#else
PUBLIC OsVoid *osMemset(s, c, len)
OsVoid *s;
OsInt c;
OsSize len;
#endif
{
   TRC2(osMemset)
   RETVALUE(memset(s, c, (U32)len));
} /* end of osMemset */


/*
*
*       Fun:   osFopen
*
*       Desc:  wrapper for fopen
*
*       Ret:   return from fopen
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsFile *osFopen
(
CONST S8 *fName,                      /* file name */
CONST S8 *flags                       /* file type */
)
#else
PUBLIC OsFile *osFopen(fName, flags)
CONST S8 *fName;                      /* file name */
CONST S8 *flags;                      /* file type */
#endif
{
   TRC2(osFopen)
   RETVALUE((OsFile*)fopen(fName, flags));
} /* end of osFopenFile */


/*
*
*       Fun:   osFclose
*
*       Desc:  wrapper for fclose...
*
*       Ret:   return from flclose
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsInt osFclose
(
OsFile *fPtr            /* file pointer */
)
#else
PUBLIC OsInt osFclose(fPtr)
OsFile *fPtr;           /* file pointer */
#endif
{
   TRC2(osFclose)
   RETVALUE(fclose((FILE*)fPtr));
} /* end of osFclose */


/*
*
*       Fun:   osGetWord
*
*       Desc:  Extract the next word  from a buffer 
*
*       Ret:   value
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S8 *osGetWord
(
S8 *line,              /* line */
S8 *word               /* word */
)
#else
PUBLIC S8 *osGetWord(line, word)
S8 *line;              /* line */
S8 *word;              /* word */
#endif
{
   REG1 S32 i;
   REG2 S8 *lPtr;
   REG3 S8 *wPtr;

   TRC2(osGetWord)

   lPtr = line;                 /* line pointer */
   wPtr = word;                 /* word pointer */
   
   while ( lPtr && isspace((int)*lPtr) ) /* skip leading white space */
      lPtr++;
   
   /*
    * make sure we're not at end of line 
    */
   if ( !lPtr || *lPtr == '\n' || *lPtr == '\0' )
   {
      *word = '\0';
      RETVALUE(0);
   }
   
   if (*lPtr == '"') /* handle quoted words */
   {
      lPtr++;        /* munch first quote */
      i = 0;
      while ( *lPtr !=  '"')
      {
         if ( *lPtr == '\n' || *lPtr == '\0')
         {
            *word = '\0';
            RETVALUE(0);
         }
         *wPtr++ = *lPtr++;
         i++;
      }
      lPtr++;        /* munch last quote */
   }
   else /* handle unquoted words */
   {
      i = 0;
      while ( !isspace((int)*lPtr) && *lPtr != '\n' && *lPtr != '\0')
      {
         *wPtr++ = *lPtr++;
         i++;
      }
   }
   *wPtr = '\0';                /* null terminate */
   RETVALUE(lPtr);              /* return pointer to remainder of line */
} /* end of osGetWord */


/*
*
*       Fun:   osStrtol
*
*       Desc:  wrapper for strtol 
*
*       Ret:   long value of ascii string
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsLong osStrtol
(
CONST S8 *str,
S8 **ptr,
OsInt base
)
#else
PUBLIC OsLong osStrtol(str, ptr, base)
CONST S8 *str;
S8 **ptr;
OsInt base;
#endif
{
   TRC2(osStrtol)
   RETVALUE(strtol(str, ptr, base));

} /* end of osStrtol */


/*
*
*       Fun:   osFgets
*
*       Desc:  wrapper for fgets
*
*       Ret:   NULLP at end of file, other wise buffer pointer
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S8* osFgets
(
S8 *buf,
OsInt n,
OsFile *fp
)
#else
PUBLIC S8* osFgets(buf, n, fp)
S8 *buf;
OsInt n;
OsFile *fp;
#endif
{
   TRC2(osFgets)
   RETVALUE(fgets(buf, n, (FILE*)fp));

} /* end of osFgets */


/*
*
*       Fun:   osGets
*
*       Desc:  wrapper for gets
*
*       Ret:   NULLP at end of file, other wise buffer pointer
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S8* osGets
(
S8 *buf
)
#else
PUBLIC S8* osGets(buf)
S8 *buf;
#endif
{
   TRC2(osGets)
#ifndef SS_LINUX
   RETVALUE(gets(buf));
#else
   RETVALUE(fgets(buf, 8, stdin));
#endif

} /* end of osGets */

/*
*
*       Fun:   osStrcmp
*
*       Desc:  wrapper for strcmp
*
*       Ret:   return from strcmp
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsInt osStrcmp
(
CONST S8 *s1,
CONST S8 *s2
)
#else
PUBLIC OsInt osStrcmp(s1, s2)
CONST S8 *s1;
CONST S8 *s2;
#endif
{
   TRC2(osStrcmp)
   RETVALUE(strcmp(s1,s2));
} /* end of osStrcmp */


/*
*
*       Fun:   osStrncmp
*
*       Desc:  wrapper for strncmp
*
*       Ret:   return from strncmp
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsInt osStrncmp
(
CONST S8 *s1,
CONST S8 *s2,
OsSize size
)
#else
PUBLIC OsInt osStrncmp(s1, s2, size)
CONST S8 *s1;
CONST S8 *s2;
OsSize size;
#endif
{
   TRC2(osStrncmp)
   RETVALUE(strncmp(s1,s2, size));
} /* end of osStrncmp */


/*
*
*       Fun:   osCalloc
*
*       Desc:  allocate and zero buffer
*
*       Ret:   return from calloc
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsVoid *osCalloc
(
OsSize nelem,
OsSize size
)
#else
PUBLIC OsVoid *osCalloc(nelem, size)
OsSize nelem;
OsSize size;
#endif
{
   TRC2(osCalloc)
   RETVALUE((S8*)calloc((size_t)nelem, (size_t)size));
} /* end of osCalloc */


/*
*
*       Fun:   osMatchKeyword
*
*       Desc:  Match a Keyword 
*
*       Ret:   value
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S32 osMatchKeyword
(
Keys *keys,                     /* keyword list pointed */
S8 *tkn                         /* token */
)
#else
PUBLIC S32 osMatchKeyword(keys, tkn)
Keys *keys;                     /* keyword list id  */
S8 *tkn;                        /* token */
#endif
{
   Keys *ptr;

   TRC2(osMatchKeyword)
   ptr = keys;
   /* try to match the tkn with the keywords */
   for (ptr = keys; *ptr->kw != '\0'; ptr++)
   {
      if (!osStrncmp((CONST S8 *)ptr->kw, 
                      (CONST S8 *)tkn, 
                      osStrlen(tkn))) /* use the token length */
      {
         if (osStrlen((CONST S8 *)ptr->kw) != osStrlen((CONST S8 *)tkn))
            continue;
         RETVALUE(ptr->kv);
      }
      
   }
   /* return the value portion of the NULL case */
   RETVALUE(ptr->kv);
} /* end of osMatchKeyword */


/*
*
*       Fun:   osStrcpy
*
*       Desc:  wrapper for string copy 
*
*       Ret:   return from strcpy
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S8 *osStrcpy
(
S8 *dst,
CONST S8 *src
)
#else
PUBLIC S8 *osStrcpy(dst, src)
S8 *dst;
CONST S8 *src;
#endif
{
   TRC2(osStrcpy)
   RETVALUE((S8*)strcpy(dst, src));
} /* end of osStrcpy */


/*
*
*       Fun:   osReadAccess
*
*       Desc:  partial wrapper for access
*
*       Ret:   0 on success, -1 on error
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsInt osReadAccess
(
CONST S8 *file
)
#else
PUBLIC OsInt osReadAccess(file)
CONST S8 *file;
#endif
{

   TRC2(osReadAccess)
#if (DEF_NTSSLIB | DEF_NU)
   RETVALUE(ROK); 
#else
   RETVALUE(access(file, F_OK|ROK));
#endif

} /* end of osReadAccess */


/*
*
*       Fun:   osMemcpy
*
*       Desc:  wrapper for memcpy
*
*       Ret:   return from memcpy
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsVoid *osMemcpy
(
OsVoid *s1,
CONST OsVoid *s2,
OsSize len
)
#else
PUBLIC OsVoid *osMemcpy(s1, s2, len)
OsVoid *s1;
CONST OsVoid *s2;
OsSize len;
#endif
{
   TRC2(osMemcpy)

#ifdef ANSI
   RETVALUE(memcpy(s1, s2, (U32)len));
#else
   RETVALUE(memcpy(s1, s2, (S32)len));
#endif /* ANSI */
} /* end of osMemcpy */


/*
*
*       Fun:   osFread
*
*       Desc:  wrapper for fread
*
*       Ret:   size read
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsSize osFread
(
OsVoid *ptr,
OsSize size,
OsSize nitems,
OsFile *file
)
#else
PUBLIC OsSize osFread(ptr, size, nitems, file)
OsVoid *ptr;
OsSize size;
OsSize nitems;
OsFile *file;
#endif
{
   TRC2(osFread)
   RETVALUE(fread(ptr, size, nitems, (FILE*)file));
} /* end of osFread */


/*
*
*       Fun:   osRead
*
*       Desc:  wrapper for read
*
*       Ret:   size read
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsSize osRead
(
S32    fd,  
Data   *data,
OsSize nitems
)
#else
PUBLIC OsSize osRead(fd, data, nitems)
S32    fd;
Data   *data;
OsSize nitems;
#endif
{
#if (DEF_NTSSLIB | DEF_NU)
   U8 nRead;
#endif  /* DEF_NTSSLIB */

   TRC2(osRead)

#if (DEF_NTSSLIB | DEF_NU)
    if (!ReadFile((HANDLE)fd, data, nitems, (LPDWORD)&nRead,NULL))
        RETVALUE(0);
    else
       RETVALUE(nRead);
#else
   RETVALUE(read(fd, data, nitems));
#endif  /* DEF_NTSSLIB */

} /* end of osRead */


/*
*
*       Fun:   osFwrite
*
*       Desc:  wrapper for fWrite
*
*       Ret:   size Write
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsSize osFwrite
(
CONST OsVoid *ptr,
OsSize size,
OsSize nitems,
OsFile *file
)
#else
PUBLIC OsSize osFwrite(ptr, size, nitems, file)
CONST OsVoid *ptr;
OsSize size;
OsSize nitems;
OsFile *file;
#endif
{
   TRC2(osFwrite)
   RETVALUE(fwrite(ptr, size, nitems, (FILE*)file));
}


/*
*
*       Fun:   osWrite
*
*       Desc:  wrapper for write
*
*       Ret:   size write
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsSize osWrite
(
S32    fd,  
Data   *data,
OsSize nitems
)
#else
PUBLIC OsSize osWrite(fd, data, nitems)
S32    fd;
Data   *data;
OsSize nitems;
#endif
{
#if (DEF_NTSSLIB | DEF_NU)
   U8 nWr;
#endif /* DEF_NTSSLIB */

   TRC2(osWrite)

#if (DEF_NTSSLIB | DEF_NU)
   if (!WriteFile((HANDLE)fd, data, nitems, (LPDWORD)&nWr,NULL))
      RETVALUE(0);
   else
      RETVALUE(nWr);
#else
   RETVALUE(write(fd, data, nitems));
#endif /* DEF_NTSSLIB */

} /* end of osWrite */


/*
*
*       Fun:   osSeekStart
*
*       Desc:  wrapper for lseek
*
*       Ret:   size write
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S32 osSeekStart
(
S32    fd  
)
#else
PUBLIC S32 osSeekStart(fd)
S32    fd;
#endif
{
   TRC2(osSeekStart)
   RETVALUE(lseek(fd, 0,SEEK_SET));
} /* end of osSeekStart */


/*
*
*       Fun:   osStrlen
*
*       Desc:  wrapper for strlen
*
*       Ret:   return from strlen
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsSize osStrlen
(
CONST S8 *s
)
#else
PUBLIC OsSize osStrlen(s)
CONST S8 *s;
#endif
{
   TRC2(osStrlen)
   RETVALUE(strlen(s));
} /* end of osStrlen */


/*
*
*       Fun:   osStrcat
*
*       Desc:  wrapper for strcat
*
*       Ret:   return from strcat
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S8 *osStrcat
(
S8       *dst,
CONST S8 *src
)
#else
PUBLIC S8 *osStrcat(dst, src)
S8       *dst;
CONST S8 *src;
#endif
{
   TRC2(osStrcat)
   RETVALUE(strcat(dst, src));
} /* end of osStrcat */


/*
*
*       Fun:   osFseek
*
*       Desc:  wrapper for fseek
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsInt osFseek
(
OsFile *fp,
OsLong offset,
OsInt whence
)
#else
PUBLIC OsInt osFseek(fp, offset, whence)
OsFile *fp;
OsLong offset;
OsInt whence;
#endif
{
   OsInt dir;

   TRC2(osFseek)
   switch (whence)
   {
      case OS_SEEK_SET:
         dir = SEEK_SET;
         break;
      case OS_SEEK_CUR:
         dir = SEEK_CUR;
         break;
      case OS_SEEK_END:
         dir = SEEK_END;
         break;
      default:
         dir = 0;
         RETVALUE(RFAILED);
   }

   RETVALUE(fseek((FILE*)fp, offset, dir));
} /* end of osFseek */


/*
*
*       Fun:   osGetopt
*
*       Desc:  wrapper for getopt
*
*       Ret:   return from getopt
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsInt osGetopt
(
OsInt argc,
S8 * CONST *argv,
CONST S8 *optStr
)
#else
PUBLIC OsInt osGetopt(argc, argv, optStr)
OsInt argc;
S8 * CONST *argv;
CONST S8 *optStr;
#endif
{
#if (DEF_NTSSLIB | DEF_NU)
   S16 c;
   S8 *cp;
   S16 sp;

   TRC2(osGetopt)
   sp = 1;
   if (optind >= (S16) argc || argv[optind][0] == '\0')
      RETVALUE(EOF);
   else
   {
      if (!strcmp(argv[optind], "--"))
      {
         optind++;
         RETVALUE(EOF);
      }
      else if (argv[optind][0] != '-')
      {
         optind++;
         RETVALUE('?');
      }
   }
   OsOptOpt = c = argv[optind][sp];
   if ( c == ':' || (cp = strchr(optStr, c)) == (S16)NULLP )
   {
      if (argv[optind][++sp] == '\0')
      {
         optind++;
         sp = 1;
      }
      RETVALUE('?');
   }
   if (*++cp == ':')
   {
      if (argv[optind][sp+1] != '\0')
         OsOptArg = &argv[optind++][sp+1];
      else
      {
         if (++optind >= (S16) argc)
         {
            sp = 1;
            RETVALUE('?');
         }
         else
            OsOptArg = argv[optind++];

         sp = 1;
      }
   }
   else
   {
      if (argv[optind][++sp] == '\0')
      {
         sp = 1;
         optind++;
      }
      OsOptArg =NULLP;
   }
   RETVALUE(c);
#else

   extern char *optarg;
   extern int optind, opterr, optopt;
   OsInt retVal;

   TRC2(osGetopt)

   retVal = getopt(argc, argv, optStr);

   /* set our externs from system externs */
   OsOptArg = optarg;
   OsOptInd = optind;
   OsOptErr = opterr;
   OsOptOpt = optopt;

   RETVALUE(retVal);
#endif /* DEF_NTSSLIB */

} /* end of osGetopt */


/*
*
*       Fun:   osSprintf
*
*       Desc:  wrapper for sprintf
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osSprintf
(
S8 *s,
CONST S8 *fmt,
...
)
#else
PUBLIC Void osSprintf(s, fmt, va_alist)
S8 *s;
CONST S8 *fmt;
va_dcl
#endif
{
   va_list args;

   TRC2(osSprintf)
   
#ifdef ANSI
   va_start(args, fmt);
#else
   va_start(args);
#endif

   vsprintf(s, fmt, args);
   va_end(args);

   RETVOID;
} /* end of osSprintf */


/*
*
*       Fun:   osPrintf
*
*       Desc:  wrapper for printf
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osPrintf
(
CONST S8 *fmt,
...
)
#else
PUBLIC Void osPrintf(fmt, va_alist)
CONST S8 *fmt;
va_dcl
#endif
{
   va_list args;

   TRC2(osPrintf)
   
#ifdef ANSI
   va_start(args, fmt);
#else
   va_start(args);
#endif
   vprintf(fmt, args);
   va_end(args);
   fflush(stdout);

   RETVOID;
} /* end of osPrintf */


/*
*
*       Fun:   osFree
*
*       Desc:  wrapper for free
*
*       Ret:   none
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osFree
(
OsVoid *ptr
)
#else
PUBLIC Void osFree(ptr)
OsVoid *ptr;
#endif
{

   TRC2(osFree)
   free(ptr);
   RETVOID;
} /* end of osFree */


/*
*
*       Fun:   osIsprint
*
*       Desc:  wrapper for isprint 
*
*       Ret:   true or false
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsInt osIsprint
(
OsInt c
)
#else
PUBLIC OsInt osIsprint(c)
OsInt c;
#endif
{
   TRC2(osIsprint)
   if (isprint(c))
      RETVALUE(TRUE);
   else
      RETVALUE(FALSE);
} /* end of osIsprint */


/*
*
*       Fun:   osIsascii
*
*       Desc:  wrapper for isascii 
*
*       Ret:   true or false
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsInt osIsascii
(
OsInt c
)
#else
PUBLIC OsInt osIsascii(c)
OsInt c;
#endif
{
   TRC2(osIsascii)
   if (isascii(c))
      RETVALUE(TRUE);
   else
      RETVALUE(FALSE);
} /* end of osIsascii */


/*
*
*       Fun:   osIsspace
*
*       Desc:  wrapper for isspace 
*
*       Ret:   true or false
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsInt osIsspace
(
OsInt c
)
#else
PUBLIC OsInt osIsspace(c)
OsInt c;
#endif
{
   TRC2(osIsspace)
   if (isspace(c))
      RETVALUE(TRUE);
   else
      RETVALUE(FALSE);
} /* end of osIsspace */


/*
*
*       Fun:   osTmpnam
*
*       Desc:  wrapper for tmpnam
*
*       Ret:   return a pointer to a temporary file name
*
*       Notes: pointer is valid only until next call to osTmpname
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Txt *osTmpnam
(
void
)
#else
PUBLIC Txt *osTmpnam()
#endif
{
#if (DEF_NTSSLIB | DEF_NU)
   PRIVATE Txt tmpFile[MAX_PATH];
   Txt         tmpDir[MAX_PATH];
   U32         ret;
#endif

   TRC2(osTmpnam)

#if (DEF_NTSSLIB | DEF_NU)
   ret = GetTempPath(sizeof(tmpDir), tmpDir);

   if ((ret == 0) || (ret > sizeof(tmpDir)))
   {
      /* GetTempPath failed */
      RETVALUE((Txt*)tmpfile());
   }
   if (GetTempFileName(tmpDir, NULLP, 0, tmpFile) == 0)
      RETVALUE(NULLP);
   else
      RETVALUE(tmpFile);
#else
   RETVALUE((Txt*)tmpfile());
#endif /* DEF_NTSSLIB || DEF_NU */
} /* end of osTmpnam */


/*
*
*       Fun:   osUnlink
*
*       Desc:  wrapper for unlink
*
*       Ret:   RETVOID
*
*       Notes: removes a file
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osUnlink
(
CONST S8 *fName
)
#else
PUBLIC Void osUnlink(fName)
CONST S8 *fName;
#endif
{
   OsInt ret;

   TRC2(osUnlink)
   ret = unlink(fName);
   RETVOID;
} /* end of osUnlink */


/* Linked List functions */

/*
*
*       Fun:   osAdd2LList
*
*       Desc:  creates dlList if it doesn't exist. adds node to end of dlList.
*
*       Ret:   ROK   - ok
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osAdd2LList
(
DLList **dlList,
Txt *node
)
#else 
PUBLIC Void osAdd2LList(dlList, node)
DLList **dlList;
Txt *node;
#endif
{
   DLList *crnt;
   DLList *next;
   DLList *tmp;
 
   TRC2(osAdd2LList)
   tmp = (DLList *)osCalloc(1, sizeof(DLList));
   tmp->next = tmp->prev = NULL;
   tmp->node = node;
 
   if (*dlList == NULL)
   {
      *dlList = tmp;
      RETVOID;
   }
 
   for(crnt = *dlList, next = (*dlList)->next;
      next != NULL;
      crnt = next, next = crnt->next);
   crnt->next = tmp;
   tmp->prev = crnt;
   RETVOID;
} /* end of osAdd2LList */


/*
*
*       Fun:   osDelFrmLList
*
*       Desc:  remove node pointed to by nodePtr from list and return node.
*              nodePtr could be anywhere in the list.
*
*       Ret:   pointer
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Txt *osDelFrmLList
(
DLList **dlList,
DLList *nodePtr
)
#else 
PUBLIC Txt *osDelFrmLList(dlList, nodePtr)
DLList **dlList;
DLList *nodePtr;
#endif
{
   Txt *node;
  
   TRC2(osDelFrmLList)
   if (*dlList == (DLList *)NULLP)
   {
      RETVALUE(NULL);
   }
 
   if (nodePtr == *dlList)
   {
      (*dlList) = (*dlList)->next;
   }
 
   if(nodePtr->prev != (DLList *)NULLP)
      nodePtr->prev->next = nodePtr->next;
 
   if (nodePtr->next != (DLList *)NULLP)
      nodePtr->next->prev = nodePtr->prev;
    
   node = nodePtr->node;
   osFree((OsVoid *)nodePtr);
   RETVALUE(node);
} /* end of osDelFrmLList */


/*
*
*       Fun:   osNextDLList
*
*       Desc:  returns next node in a DLList
*
*       Ret:   next node or NULLP
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC DLList *osNextDLList
(
DLList *dlList
)
#else 
PUBLIC DLList *osNextDLList(dlList)
DLList *dlList;
#endif
{
   TRC2(osNextDLList)
   RETVALUE(dlList->next);
} /* end of osNextDLList */


/*
*
*       Fun:   osNodeDLList
*
*       Desc:  returns object of current node pointed tobydlList
*
*       Ret:   next node or NULLP
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Txt *osNodeDLList
(
DLList *dlList
)
#else 
PUBLIC Txt *osNodeDLList(dlList)
DLList *dlList;
#endif
{
   TRC2(osNodeDLList)
   RETVALUE(dlList->node);
} /* end of osNodeDLList */


/*
*
*       Fun:   osPrevDLList
*
*       Desc:  returns Previous node in a DLList
*
*       Ret:   next node or NULLP
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC DLList *osPrevDLList
(
DLList *dlList
)
#else 
PUBLIC DLList *osPrevDLList(dlList)
DLList *dlList;
#endif
{
   TRC2(osPrevDLList)
   RETVALUE (dlList->prev);
} /* end of osPrevDLList */


/*
*
*       Fun:   osSleep
*
*       Desc: 
*
*       Ret:  
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osSleep
(
U32 seconds
)
#else
PUBLIC Void osSleep(seconds)
U32 seconds;
#endif
{
   TRC2(osSleep)
#if (DEF_NTSSLIB | DEF_NU)
   Sleep(seconds * 1000);
#else
   sleep(seconds);
#endif
   RETVOID;
} /* end of osSleep */


/*
*
*       Fun:   osMsSleep
*
*       Desc: Millisecond sleep
*
*       Ret:  
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osMsSleep
(
U32 mSeconds
)
#else
PUBLIC Void osMsSleep(mSeconds)
U32 mSeconds;
#endif
{
#if !(DEF_NTSSLIB | DEF_NU)
   struct pollfd fds;
#endif
   
   TRC2(osMsSleep)
#if (DEF_NTSSLIB | DEF_NU)
  Sleep(mSeconds);
#else

   fds.fd     = -1;
   fds.events = 0;
   poll(&fds, 1, (int)mSeconds);
#endif
   RETVOID;
} /* end of osMsSleep */

#ifdef CLIENT   /* these all output to stderr */
  
/*
*
*       Fun:   osErrQuit
*
*       Desc:  Fatal error. Print message and terminate.
*              don't dump core, and don't print system error number
*
*       Ret:   RETVOID
*
*       Notes: The string "str" must contain the converions specification
*              for any args.
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osErrQuit
(
CONST S8 *fmt,
...
)
#else
PUBLIC Void osErrQuit(fmt, va_alist)
CONST S8 *fmt;
va_dcl
#endif
{
   va_list args;

   TRC2(osErrQuit)
#ifdef ANSI
   va_start(args, fmt);
#else
   va_start(args);
#endif
   if (pname != NULL)
      fprintf(stderr, "%s: ", pname);
   vfprintf(stderr, fmt, args);
   fputc('\n', stderr);
   va_end(args);
   exit(1);
   RETVOID;
} /* end of osErrQuit */

  
/*
*
*       Fun:   osErrSys
*
*       Desc:  Fatal error related to a system call. Print a message
*              and terminate. Don't dump core, but do print the system's
*              errono value and its associated message.
*
*       Ret:   RETVOID
*
*       Notes: The string "str" must contain the converions specification
*              for any args.
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osErrSys
(
CONST S8 *fmt,
...
)
#else
PUBLIC Void osErrSys(fmt, va_alist)
CONST S8 *fmt;
va_dcl
#endif
{
   va_list args;

   TRC2(osErrSys)
#ifdef ANSI
   va_start(args, fmt);
#else
   va_start(args);
#endif
   if (pname != NULL)
      fprintf(stderr, "%s: ", pname);
   vfprintf(stderr, fmt, args);
   va_end(args);

   myPerror();
   exit(1);
   RETVOID;
} /* end of osErrSys */

  
/*
*
*       Fun:   osErrRet
*
*       Desc:  recoverable error. Print message and return to caller.
*
*       Ret:   RETVOID
*
*       Notes: The string "str" must contain the converions specification
*              for any args.
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osErrRet
(
CONST S8 *fmt,
...
)
#else
PUBLIC Void osErrRet(fmt, va_alist)
CONST S8 *fmt;
va_dcl
#endif
{
   va_list args;

   TRC2(osErrRet)
#ifdef ANSI
   va_start(args, fmt);
#else
   va_start(args);
#endif

   if (pname != NULL)
      fprintf(stderr, "%s: ", pname);
   vfprintf(stderr, fmt, args);
   va_end(args);

   myPerror();
   fflush(stdout);
   fflush(stderr);
   RETVOID;
} /* end of osErrRet */

  
/*
*
*       Fun:   osErrDump
*
*       Desc:  Fatal error. Print a message, dump core, and terminate
*
*       Ret:   RETVOID
*
*       Notes: The string "str" must contain the converions specification
*              for any args.
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void osErrDump
(
CONST S8 *fmt,
...
)
#else
PUBLIC Void osErrDump(fmt, va_alist)
CONST S8 *fmt;
va_dcl
#endif
{
   va_list args;

   TRC2(osErrDump)
#ifdef ANSI
   va_start(args, fmt);
#else
   va_start(args);
#endif

   if (pname != NULL)
      fprintf(stderr, "%s: ", pname);
   vfprintf(stderr, fmt, args);
   va_end(args);

   myPerror();
   fflush(stdout);
   fflush(stderr);

   abort();
   exit(1);
   RETVOID;
} /* end of osErrDump */

  
/*
*
*       Fun:   myPerror
*
*       Desc:  print to standard error
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PRIVATE Void myPerror
(
void
)
#else
PRIVATE Void myPerror()
#endif
{
   fprintf(stderr, " %s\n", sysErrStr());
   RETVOID;
} /* end of myPerror */
#endif /* CLIENT */

  
/*
*
*       Fun:   sysErrStr
*
*       Desc:  system error string
*
*       Ret:   value
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PRIVATE S8 *sysErrStr
(
void
)
#else
PRIVATE S8 *sysErrStr()
#endif
{
   static S8 msgstr[200];

   if (errno != 0)
   {
      snprintf(msgstr, 200, "(%s)", strerror(errno));
   }
   else
      msgstr[0] = '\0';
   RETVALUE(msgstr);
} /* end of sysErrStr */


/*
*
*       Fun:   osMsgSend
*
*       Desc:  "post" a message to an ipc message queue
*
*       Ret:   ROK   - ok
*              RFAILED - error
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S32 osMsgSend
(
S32 id,                         /* message queue id  */
Mesg *mPtr                      /* message pointer */
)
#else
PUBLIC S32 osMsgSend(id, mPtr)
S32 id;                         /* message queue id  */
Mesg *mPtr;                     /* message pointer */
#endif
{

#if !(DEF_NTSSLIB | DEF_NU)
   S32 ret;
   U32 cntr; 
#endif

   TRC2(osMsgSend)

#if (DEF_NTSSLIB | DEF_NU)
   if (WriteFile ((HANDLE)id, (LPVOID) &mPtr->mesg_type,
                     mPtr->mesg_len, &mPtr->mesg_len,NULL) == 0)
      RETVALUE(RFAILED);
#else
   cntr = 0;
   /* send a message */
MSGSEND:
   ret = msgsnd(id, &(mPtr->mesg_type), mPtr->mesg_len, IPC_NOWAIT);
   if (ret == -1)
   {
      switch(errno)
      {
         case EINTR:            /* interrupt */
                    goto MSGSEND;
                    break; 
         case EAGAIN:           /* try again... */
            cntr++;
            if(cntr < MAX_MSGSEND_RETRIES)
            {
               goto MSGSEND;
            } else
            {
               printf("osMsgSend: %s:%d Failed\n", __FILE__, __LINE__);
               RETVALUE(RFAILED);
            }
            break;
         default:               /* plain old error */
#ifdef ERRCHK
            osErrQuit("msgsnd");
#endif /* ERRCHK */
            RETVALUE(RFAILED);
      }
   }
#endif /* DEF_NTSSLIB */

   RETVALUE(ROK);
} /* end of osMsgSend */


/*
*
*       Fun:   osMsgRecv
*
*       Desc:  receive a message from a ipc message queue
*
*       Ret:   ROK   - ok
*              ROKDNA - ok, data not available
*              RFAILED - error.
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S32 osMsgRecv
(
S32 id,
Mesg *mPtr,
Bool wFlag
)
#else
PUBLIC S32 osMsgRecv(id, mPtr, wFlag)
S32 id;
Mesg *mPtr;
Bool wFlag;
#endif
{
#if (DEF_NTSSLIB | DEF_NU)
   Bool bool;
   S32 nBytes;
#else
   S32 nBytes;
   OsInt flag;
#endif /* DEF_NTSSLIB */

   TRC2(osMsgRecv)

#if (DEF_NTSSLIB | DEF_NU)
   nBytes = 0;

   if (wFlag == FALSE)   /* no wait, return imm., if no data */
   {
      if (PeekNamedPipe((HANDLE) id,NULL, 0,NULL, &nBytes,NULL) == 0)
         RETVALUE(RFAILED);

      if (!nBytes)   /* No data */
         RETVALUE(ROKDNA);
   }
   bool = ReadFile ((HANDLE) id, (LPVOID) &mPtr->mesg_type, MAXMESGDATA,
                   &mPtr->mesg_len,NULL);
   if (!bool)
      RETVALUE(RFAILED);

#else
   if (!wFlag)
      flag = IPC_NOWAIT;
   else
      flag = 0;

   nBytes = msgrcv(id, &(mPtr->mesg_type), MAXMESGDATA, mPtr->mesg_type, flag);
   if ( nBytes < 0 )
   {
      switch(errno)
      {
         case ENOMSG:
         case EINTR:
         case EAGAIN:
            RETVALUE(ROKDNA);
            break;
         default:
            return(RFAILED);
      }
   }
   mPtr->mesg_len = nBytes;
#endif /* DEF_NTSSLIB */

   RETVALUE(ROK);

} /* end of osMsgRecv */


/*
*
*       Fun:   osMsgCreate
*
*       Desc:  create a message queue.
*
*       Ret:   ROK   - ok
*              RFAILED - error
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S32 osMsgCreate
(
S32 key,
S32 *id
)
#else
PUBLIC S32 osMsgCreate(key, id)
S32 key;
S32 *id;
#endif
{

#if (DEF_NTSSLIB | DEF_NU)

#else
   REG1 S32 i;
   Bool found;
   struct sigaction sigact;

   TRC2(osMsgCreate)

   *id = msgget(key, PERMS|IPC_CREAT|IPC_EXCL);
   if (*id < 0)
   {
      if (errno == EEXIST)
      {
         Mesg msg;
         *id   = msgget(key, PERMS);
         msg.mesg_type = SFndProcId();
         while(osMsgRecv(*id, &msg, FALSE) == ROK );
      }
      else
      {
#ifdef ERRCHK
         osErrSys("msgget");
#endif /* ERRCHK */
         RETVALUE(RFAILED);
      }
   }

   found = FALSE;
   for (i = 0; i < MAXQUES; i++) 
   {
      if (stkMsgId[i] == -1)
      {
         stkMsgId[i] = *id;
         found = TRUE;
         break;
      }
   }

   if (!found)
   {
#ifdef ERRCHK
      osErrQuit("MAXQUES exceeded");       
#endif
      RETVALUE(RFAILED);
   }

   if (!MsgInit)                   /* we only need to do this once */
   {
      /* We're going to install a signal handler to remove the
       * message queue if we receive a sigint (control-c)
       */

      /* clear signal mask */
      if (sigemptyset(&sigact.sa_mask) < 0)
      {
#ifdef ERRCHK
         osErrSys("sigemptyset");
#endif /* ERRCHK */
         RETVALUE(RFAILED);
      }
 
      /* Add SIGINT to the signal mask */
      if (sigaddset(&sigact.sa_mask, SIGINT) < 0)
      {
#ifdef ERRCHK
         osErrSys("sigaddset");
#endif /* ERRCHK */
         RETVALUE(RFAILED);;
      }

      /* Add SIGTERM to the signal mask */
      if (sigaddset(&sigact.sa_mask, SIGTERM) < 0)
      {
#ifdef ERRCHK
         osErrSys("sigaddset");
#endif /* ERRCHK */
         RETVALUE(RFAILED);;
      }
 
      /* Install SIGINT signal handler */

      /* TIC_ID:ccpu00117545 DEL:Fixed warning for gcc compilation on CentOS */      
      sigact.sa_handler = (void (*)(int))msgClean;

      if ( sigaction(SIGINT, &sigact, NULL) < 0)
      {
#ifdef ERRCHK
         osErrSys("sigaction");
#endif /* ERRCHK */
         RETVALUE(RFAILED);
      }

      if (sigaction(SIGTERM, &sigact, NULL) < 0)
      {
#ifdef ERRCHK
         osErrSys("sigaction");
#endif /* ERRCHK */
         RETVALUE(RFAILED);
      }

      MsgInit = TRUE;
   }
#endif /* DEF_NTSSLIB */

   RETVALUE(ROK);
} /* end of osMsgCreate */


/*
*
*       Fun:   osMsgGet
*
*       Desc:  get a message queue.
*
*       Ret:   ROK   - ok
*              RFAILED - error
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S32 osMsgGet
(
S32 key,
S32 *id
)
#else
PUBLIC S32 osMsgGet(key, id)
S32 key;
S32 *id;
#endif
{
   TRC2(osMsgGet)

#if (DEF_NTSSLIB | DEF_NU)

#else
   *id = msgget(key, 0);
   if (*id < 0)
   {
#ifdef ERRCHK
      osErrSys("msgget");
#endif /* ERRCHK */
      RETVALUE(RFAILED);
   }
#endif /* DEF_NTSSLIB */

   RETVALUE(ROK);
} /* end of osMsgGet */


/*
*
*       Fun:   msgClean
*
*       Desc:  
*
*       Ret:   ROK   - ok
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PRIVATE Void INTERRPT msgClean
(
void
)
#else
PRIVATE Void INTERRPT msgClean()
#endif
{

#if (DEF_NTSSLIB | DEF_NU)

#else
   REG1 S32 i;

   TRC2(msgClean)
 
   for (i = 0; i < MAXQUES; i++)
   {
      if (stkMsgId[i] != -1)
      {
         /* remove the queues */
         (Void)msgctl(stkMsgId[i], IPC_RMID, 0); /* we don't care */
         stkMsgId[i] = -1; 
      }
   }
   exit(0);
#endif /* DEF_NTSSLIB */

} /* end of msgClean */


/*
*
*       Fun:   msgRmv
*
*       Desc: 
*
*       Ret:  
*
*       Notes: None
*
*       File:  cm_os.c
*
*/
#if 0
#ifdef ANSI
PRIVATE Void msgRmv
(
S32 mid
)
#else
PRIVATE Void msgRmv(mid)
S32 mid;
#endif
{
#if (DEF_NTSSLIB | DEF_NU)

#else
   (Void)msgctl(mid, IPC_RMID, 0); /* we don't care */
#endif /* DEF_NTSSLIB */
   RETVOID;

} /* end of msgRmv */
#endif

/*
*
*       Fun:   osMmap
*
*       Desc: 
*
*       Ret:  
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S8 *osMmap
(
S8 *addr,
OsSize len,
OsInt prot,
OsInt flags,
OsInt fildes,
OsLong off
)
#else
PUBLIC S8 *osMmap(addr, len, prot, flags, fildes, off)
S8 *addr;
OsSize len;
OsInt prot;
OsInt flags;
OsInt fildes;
OsLong off;
#endif
{
#if (DEF_NTSSLIB | DEF_NU)
   HANDLE  mHdl;                 /* file mapping object handle */
   S32     flProtect;
#endif
   TRC2(osMmap)
   
#if (DEF_NTSSLIB | DEF_NU)
      flProtect = 0;

   if (prot & OS_PROT_READ == OS_PROT_READ)
   {
      flProtect = PAGE_READONLY;
  
      if (prot & OS_PROT_WRITE == OS_PROT_WRITE)
         flProtect |= PAGE_READWRITE;
   }
   if (prot & OS_PROT_WRITE == OS_PROT_WRITE)
      flProtect = PAGE_WRITECOPY;

   /* create a file mapping object first */
   mHdl = CreateFileMapping((HANDLE) fildes, NULL, flProtect, 0,  
                                                      (DWORD)len, NULL);
   if (mHdl == NULL)
   {
      RETVALUE(NULLP);
   }

   if (prot & OS_PROT_READ == OS_PROT_READ)
   {
      flProtect = FILE_MAP_READ;
  
      if (prot & OS_PROT_WRITE == OS_PROT_WRITE)
         flProtect |= FILE_MAP_WRITE;
   }
   if (prot & OS_PROT_WRITE == OS_PROT_WRITE)
      flProtect = FILE_MAP_WRITE;

   /* create a view of the file */
   RETVALUE(MapViewOfFile(mHdl, flProtect, 0, (DWORD)off, len));

#else
   /* cm_os_c_001.main_10: modified return type */
   RETVALUE((S8 *)mmap((caddr_t)addr, (size_t) len, (int) prot, (int) flags, 
             (int) fildes, (off_t) off));
#endif /* DEF_NTSSLIB */

} /* end of osMmap */

/*
*
*       Fun:   osMunmap
*
*       Desc: 
*
*       Ret:  
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsInt osMunmap
(
S8 *addr,
OsSize len
)
#else
PUBLIC OsInt osMunmap(addr, len)
S8 *addr;
OsSize len;
#endif
{
   TRC2(osMunmap)

#if (DEF_NTSSLIB | DEF_NU)
   if (FlushViewOfFile(addr, len) == 0)
      RETVALUE(RFAILED);

   if (UnmapViewOfFile(addr) == 0)
      RETVALUE(RFAILED);
 
   RETVALUE(ROK);
#else
   if (munmap((caddr_t)addr, (size_t)len) == -1)
      RETVALUE(RFAILED);
#endif /* DEF_NTSSLIB */

   RETVALUE(ROK);

} /* end of osMunmap */


/*
*
*       Fun:   osFileno
*
*       Desc: 
*
*       Ret:  
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsInt osFileno
(
OsFile *fp
)
#else
PUBLIC OsInt osFileno(fp)
OsFile *fp;
#endif
{
   TRC2(osFileno)

   RETVALUE(fileno((FILE*)fp));
} /* end of osFileno */


/*
*
*       Fun:   osRand
*
*       Desc:  generate a random number
*
*       Ret:   random number
*
*       Notes: wrapper for rand
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsInt osRand
(
void
)
#else
PUBLIC OsInt osRand()
#endif
{

   TRC2(osRand)
   
   RETVALUE((OsInt)rand());
} /* end of osRand */


/*
*
*       Fun:   osStripBlanks
*
*       Desc:  strip leading and trailing blanks from a string
*
*       Ret:   length of string
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S32 osStripBlanks
(
S8 *rawStr
)
#else
PUBLIC S32 osStripBlanks(rawStr)
S8 *rawStr;
#endif
{
   S8 *rawPtr;
   S8 *outPtr;
   S8 outStr[256];
   
   TRC2(osStripBlanks)

   osStrcpy(outStr, (CONST S8*)"\0");
   rawPtr = rawStr;
   outPtr = outStr;
 
   while (((isspace ((int)*rawPtr)) || (iscntrl ((int)*rawPtr))) 
            && (*rawPtr != '\0'))
      rawPtr++;      
 
   while (*rawPtr != '\0')
      *outPtr++ = *rawPtr++;
 
   while (((isspace (*(outPtr-1))) || (iscntrl (*(outPtr-1)))) && 
          (outPtr >= outStr))
      outPtr--;
 
   *outPtr = '\0';
 
   osStrcpy(rawStr, (CONST S8*)outStr);
 
   RETVALUE(strlen(rawStr));
} /* end of osStripBlanks */

/*
*
*       Fun:   osGetchar
*
*       Desc:  getcahr()
*
*       Ret:   next character from stdin
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC OsInt osGetchar
(
void
)
#else
PUBLIC OsInt osGetchar()
#endif
{

   TRC2(osGetchar)

   RETVALUE(getchar());

} /* end of osGetchar */

/*
*
*       Fun:   osInitCon
*
*       Desc:  osInitCon
*
*       Ret:   Initialize the console "/dev/tty"
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16   osInitCon
(
void
)
#else
PUBLIC S16   osInitCon()
#endif
{

#if !(DEF_NTSSLIB | DEF_NU)
   struct termios tio;
#endif

   TRC2(osInitCon)

#if (DEF_NTSSLIB | DEF_NU)
   cInHdl  = GetStdHandle(STD_INPUT_HANDLE);
   if (FlushConsoleInputBuffer(cInHdl) != TRUE)
   {
      RETVALUE(RFAILED);
   }
#else

   conFd = open("/dev/tty", O_RDWR | O_NDELAY);

   if(conFd < 0) 
   {
      RETVALUE(RFAILED);
   }

   /*
    * Get the current terminal settings
    */
   if(ioctl(conFd, TCGETS, &tio) < 0)
   {
      RETVALUE(RFAILED);
   }

   /* Disable canonical input processing */
   tio.c_lflag     &= ~ICANON;
   tio.c_cc[VMIN]  = 0;
   tio.c_cc[VTIME] = 0;

   if(ioctl(conFd, TCSETS, &tio) < 0)
   {
      RETVALUE(RFAILED);
   }
#endif /* DEF_NTSSLIB */
   RETVALUE(ROK);

}


/*
*
*       Fun:   osRdCon
*
*       Desc:  osRdCon
*
*       Ret:   Read a character from the console
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16   osRdCon
(
Data *dataPtr                      /* pointer to data */
)
#else
PUBLIC S16   osRdCon(dataPtr)
Data *dataPtr;                    /* pointer to data */
#endif
{
   Data data;
#if (DEF_NTSSLIB | DEF_NU)
   U8   numRead; 
#else
   S16  ret;
#endif /* DEF_NTSSLIB */

   TRC2(osRdCon)

#if (DEF_NTSSLIB | DEF_NU)
   if (ReadConsole(cInHdl, (Void *)&data, 1, (LPDWORD)&numRead,NULL))
   {
      if (numRead >0)
      {
         *dataPtr = data & 0xff;
         RETVALUE(ROK);
      }
   }
#else
   ret = (S16) read(conFd, &data, 1);

   if(ret > 0)
   {
      *dataPtr = data & 0xff;
      RETVALUE(ROK);
   }
#endif /* DEF_NTSSLIB */

   *dataPtr = 0;
   RETVALUE(ROKDNA);
}


/*
*
*       Fun:   osGetTimeOfDay
*
*       Desc:  osGetTimeOfDay
*
*       Ret:   Return system's notions of the current time
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16   osGetTimeOfDay
(
U32  *tmSec,       /* seconds since Jan.1, 1970 */
U32  *tmUsec       /* microseconds */
)
#else
PUBLIC S16   osGetTimeOfDay(tmSec, tmUsec)
U32 *tmSec;
U32 *tmUsec;
#endif
{
  
#if (DEF_NTSSLIB | DEF_NU)
   SYSTEMTIME t1;           /* Windows NT - time */
#else
   int   ret;
   struct timeval tp;
#endif /* DEF_NTSSLIB | DEF_NU */

   TRC2(osGetTimeOfDay)

#if (DEF_NTSSLIB | DEF_NU)
   GetLocalTime(&t1);
   *tmSec   = (U8) t1.wSecond;
   *tmUsec  = (U8) t1.wMilliseconds * 1000;
#else
#ifdef AIX
   ret = gettimeofday(&tp, NULLP);
#else

/* Solaris */
#ifdef _SVID_GETTOD /* USL */
   ret = gettimeofday(&tp);
#else               /* XSH4.2 */
   ret = gettimeofday(&tp, NULLP);
#endif /* _SVID_GETTOD */

#endif /* AIX */
   if(ret  < 0)
   {
      RETVALUE(RFAILED);
   }
   else
   {
      *tmSec  = tp.tv_sec;
      *tmUsec = tp.tv_usec;
   }
#endif /* DEF_NTSSLIB */

   RETVALUE(ROK);

} /* end of osGetTimeOfDay */


/*
*
*       Fun:   osOpen
*
*       Desc:  osOpen
*
*       Ret:   open a file 
*
*       Notes: change the semantics to reflect TAPA.
*              Return value is always ROK/RFAILED.
*              'fd' is returned through a parameter
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16   osOpen
(
S8 *path,          /* pathname to open */
S32 oflag,         /* open flags       */
U32 mode,          /* mode             */
S32 *fd            /* file descriptor  */
)
#else
PUBLIC S16   osOpen(path, oflag, mode, fd)
S8 *path;          /* pathname to open */
S32 oflag;         /* open flags       */
U32 mode;          /* mode             */
S32 *fd;           /* file descriptor  */
#endif
{
#if (DEF_NTSSLIB | DEF_NU)
   S32  dAccess;
#endif

   TRC2(osOpen)

#if (DEF_NTSSLIB | DEF_NU)
   if (oflag & OS_RDONLY == OS_RDONLY)
      dAccess = GENERIC_READ;

   if (oflag & OS_WRONLY == OS_WRONLY)
      dAccess = GENERIC_WRITE;

   if (oflag & OS_RDWR == OS_RDWR)
      dAccess = GENERIC_READ | GENERIC_WRITE;

   /* TBD : mode value */
   *fd = (S32)CreateFile((LPCTSTR)path, dAccess, 
                          FILE_SHARE_READ|FILE_SHARE_WRITE,
                          NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   if (((HANDLE)*fd) == INVALID_HANDLE_VALUE)
      RETVALUE(RFAILED);
#else
   if ((*fd = open((const char *)path, (int)oflag, (mode_t)mode)) == -1)
      RETVALUE(RFAILED);
#endif /* DEF_NTSSLIB */

   RETVALUE(ROK);

} /* end of osOpen */


/*
*
*       Fun:   osFtruncate
*
*       Desc:  Truncate a file to a given size
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16   osFtruncate
(
S32  fd,           /* file descriptor */
U32  length        /* length          */
)
#else
PUBLIC S16   osFtruncate(fd, length)
U32  fd;           /* file descriptor */
U32  length;       /* length          */
#endif
{
   TRC2(osFtruncate)

#if (DEF_NTSSLIB | DEF_NU)

#else
   if (ftruncate((int)fd, (off_t)length) == -1)
      RETVALUE(RFAILED);
#endif /* DEF_NTSSLIB */

   RETVALUE(ROK);

} /* osFtruncate */

#ifndef AIX

/*
*
*       Fun:   osMlockall
*
*       Desc:  lock the mmap'ed pages in memory
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16   osMlockall
(
S32 flags
)
#else
PUBLIC S16   osMlockall(flags)
S32 flags;
#endif
{
   TRC2(osMlockall)

#if (DEF_NTSSLIB | DEF_NU)

#else
   if (mlockall((int)flags) == -1)
      RETVALUE(RFAILED);
#endif /* DEF_NTSSLIB */

   RETVALUE(ROK);

} /* osMlockall */


/*
*
*       Fun:   osMunlockall
*
*       Desc:  unlock all the mmap'ed pages in memory
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16   osMunlockall
(
void
)
#else
PUBLIC S16   osMunlockall()
#endif
{
   TRC2(osMunlockall)

#if (DEF_NTSSLIB | DEF_NU)

#else
   if (munlockall() == -1)
      RETVALUE(RFAILED);
#endif /* DEF_NTSSLIB */

   RETVALUE(ROK);

} /* osMunlockall */
#endif /* not AIX */


/*
*
*       Fun:   osGeteuid
*
*       Desc:  returns the effective uid
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16   osGeteuid
(
S32 *euidPtr
)
#else
PUBLIC S16   osGeteuid(euidPtr)
S32 *euidPtr;
#endif
{
   TRC2(osGeteuid)

#if (DEF_NTSSLIB | DEF_NU)
   *euidPtr = 0;
#else
   *euidPtr = geteuid();
#endif /* DEF_NTSSLIB */

   RETVALUE(ROK);

} /* osGeteuid */


/*
*
*       Fun:   osClose
*
*       Desc:  closes the file
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16   osClose
(
S32 fd
)
#else
PUBLIC S16   osClose(fd)
S32 fd;
#endif
{
   TRC2(osClose)

#if (DEF_NTSSLIB | DEF_NU)

#else
   if (close((int)fd) == -1)
      RETVALUE(RFAILED);
#endif /* DEF_NTSSLIB */
   RETVALUE(ROK);
} /* osClose */

/*
*
*       Fun:   osCmsInit 
*
*       Desc:  opens the CMS 
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void  osCmsInit
(
   Void
)
#else
PUBLIC Void  osCmsInit()
#endif
{
   TRC2(osCmsInit)

   osOpen(CMSDEVFILE, O_WRONLY, 0, &cmsFd); 
   RETVOID;

} /* end of osCmsInit */

/*
*
*       Fun:   osOpenLockFile
*
*       Desc:  Open Lock file
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16  osOpenLockFile
(
   Txt *lockFile,            /* Lock file */
   S32 *fd                   /* file descriptor */
)
#else
PUBLIC S16   osOpenLockFile(lockFile, fd)
Txt *lockFile;    /* Lock file */
S32 *fd;          /* file descriptor */
#endif
{
   TRC2(osOpenLockFile)
   RETVALUE(osOpen(lockFile, O_CREAT | O_RDWR, 0666, fd));
} /* end of osOpenLockFile */


/*
*
*       Fun:   osTryLockFile
*
*       Desc:  Try locking the file
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16  osTryLockFile
(
   S32 fd        /* File descriptor */
)
#else
PUBLIC S16  osTryLockFile(fd)
S32 fd;         /* File descriptor */
#endif
{
   TRC2(osTryLockFile)

#if (DEF_NTSSLIB | DEF_NU)

#else
    if(lockf(fd, F_TLOCK, 0) == -1)
    {
       RETVALUE(RFAILED);
    }
#endif /* DEF_NTSSLIB */
    RETVALUE(ROK);

} /* end of osOpenLockFile */


/*
*
*       Fun:   osLockFile
*
*       Desc:  lock the file
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16  osLockFile
(
   S32 fd          /* File descriptor */
)
#else
PUBLIC S16  osLockFile(fd)
S32 fd;
#endif
{
#if (DEF_NTSSLIB | DEF_NU)
   S32 lfsize;
   S32 hfsize;
#endif /* DEF_NTSSLIB */

   TRC2(osLockFile)

#if (DEF_NTSSLIB | DEF_NU)
    lfsize = GetFileSize((HANDLE)fd, &hfsize);
    if (lfsize <= 0)
       RETVALUE(RFAILED);

    if (LockFile((HANDLE)fd, 0, 0, lfsize, hfsize) != TRUE)
       RETVALUE(RFAILED);
#else
    if(lockf(fd, F_LOCK, 0) == -1)
    {
       RETVALUE(RFAILED);
    }
#endif /* DEF_NTSSLIB */

    RETVALUE(ROK);

} /* end of osLockFile */


/*
*
*       Fun:   osUnlockFile
*
*       Desc:  unlock the file
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16  osUnlockFile
(
   S32 fd          /* File descriptor */
)
#else
PUBLIC S16  osUnlockFile(fd)
S32 fd;
#endif
{
#if (DEF_NTSSLIB | DEF_NU)
   S32 lfsize;
   S32 hfsize;
#endif /* DEF_NTSSLIB */

   TRC2(osUnlockFile)

#if (DEF_NTSSLIB | DEF_NU)
    lfsize = GetFileSize((HANDLE)fd, &hfsize);
    if (lfsize <= 0)
       RETVALUE(RFAILED);

    if (UnlockFile((HANDLE)fd, 0, 0, lfsize, hfsize)  != TRUE)
       RETVALUE(RFAILED);

#else
    if(lockf(fd, F_ULOCK, 0) == -1)
    {
       RETVALUE(RFAILED);
    }
#endif /* DEF_NTSSLIB */

    RETVALUE(ROK);

} /* end of osUnlockFile */


/*
*
*       Fun:   osSystem
*
*       Desc:  run an OS command
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC U8  osSystem
(
  Txt *command     /* System to be executed */
)
#else
PUBLIC U8 osSystem(command)
Txt *command;     /* System to be executed */
#endif
{
   TRC2(osSystem)

#if (DEF_NTSSLIB | DEF_NU)
   RETVALUE(ROK);
#else
   RETVALUE(system(command) >> 8);
#endif /* DEF_NTSSLIB */

} /* end of osLockFile */


/*
*
*       Fun:   osCmsWrite
*
*       Desc:  Write to CMS device 
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC Void  osCmsLog
(
Txt *logMsg
)
#else
PUBLIC Void  osCmsLog(logMsg)
Txt *logMsg;
#endif
{
   TRC2(osCmsLog)

   osWrite(cmsFd, (Data *)logMsg, osStrlen(logMsg));
   RETVOID;

} /* end of osCmsLog */

/* Multithreaded os wrappers */

/* cm_os_c_001.main_10: It should exclude SS_LINUX */
#ifndef SS_LINUX
#ifdef SUNOS51
/*
*
*       Fun:   osThrCreate
*
*       Desc:  Wrapper for thread create
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16   osThrCreate
(
   void *stackBase,
   U32   stackSize,
   TFN   startRoutine,
   void  *arg,
   U32   thrFlags,
   U32   *newThread
)
#else
PUBLIC S16  osThrCreate(stackBase, stackSize, startRoutine,
                         arg,       thrFlags,  newThread)
   void *stackBase;
   U32   stackSize;
   TFN   startRoutine;
   void  *arg;
   U32   thrFlags;
   U32   *newThread;
#endif
{
   thread_t new_thread;
   long     flags;

   TRC2(osThrCreate)

   if (thrFlags != OS_MT_THR_NOFLAGS)
   {
      /* gather flags */
      flags = 0;
      if (thrFlags & OS_MT_THR_SUSPENDED)
      {
         flags |= THR_SUSPENDED;
      }

      if (thrFlags & OS_MT_THR_DETACHED)
      {
         flags |= THR_DETACHED;
      }

      if (thrFlags & OS_MT_THR_BOUND)
      {
         flags |= THR_BOUND;
      }

      if (thrFlags & OS_MT_THR_NEW_LWP)
      {
         flags |= THR_NEW_LWP;
      }

      if (thrFlags & OS_MT_THR_DAEMON)
      {
         flags |= THR_DAEMON;
      }
   }
   else
   {
      flags = 0;
   }
   
   *newThread = (U32) 0;
   if(thr_create((void *) stackBase, (size_t)stackSize,
                 startRoutine, arg, flags,
                 &new_thread) == 0)
   {
      *newThread = (U32)new_thread;
      RETVALUE(ROK);
   }

   RETVALUE(RFAILED); 
}



/*
*
*       Fun:   osThrSuspend
*
*       Desc:  Wrapper for thread suspend
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16   osThrSuspend
(
   U32 targetThread
)
#else
PUBLIC S16  osThrSuspend(targetThread)
U32 targetThread;
#endif
{
   TRC2(osThrSuspend)

   if(thr_suspend((thread_t) targetThread) == 0)
   {
       RETVALUE(ROK);
   }
   RETVALUE(RFAILED);

}


/*
*
*       Fun:   osThrSelf
*
*       Desc:  Wrapper for thr_self
*
*       Ret:   
*
*       Notes: 
*
*       File:  cm_os.c
*
*/
#ifdef ANSI
PUBLIC S16   osThrSelf
(
   U32 *threadId
)
#else
PUBLIC S16  osThrSelf(threadId)
U32 *threadId;
#endif
{
   TRC2(osThrSelf)

   *threadId = (U32) thr_self();
   RETVALUE(ROK);
}

#endif /* SUNOS51 */
#endif /* SS_LINUX */




/********************************************************************30**

         End of file:     cm_os.c@@/main/nodal_main/lp_crfix_branch/1 - Wed Jan 22 19:52:22 2014

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      fl   1. 'commonised' libraries.

1.2          ---      fl   1. renamed os_lib.* to cm_os.*

1.3          ---      mb   1. Release for Integ ss7

1.4          ---      mb   1. Fixed gettimeofday call for Sol 2.5

1.5          ---      ag   1. Added changes for Windows NT
             ---      ag   2. Added TRC2 in all the osXXXX functions

1.6          ---      ns   1. Fixed compilation warnings

1.7          ---      ns   1. Added OsOptArg, OsOptInd, OsOptErr
                              and OsOptOpt. These variables have been
                              moved from cm_os.x

1.8          ---      kr   1. osTmpNam now creates the temporary file
                              in system temporary directory for 
                              Windows NT
             ---      kr   2. Changed variables OsOpt* from PRIVATE 
                              to PUBLIC
1.9          ---      ag   1. Fixed compilation warnings
/main/11     ---      cm_os_c_001.main_10      rk   1. Fixed compilation warnings
*********************************************************************91*/
