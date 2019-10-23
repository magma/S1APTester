
/********************************************************************20**
  
     Name:     solaris library
  
     Type:     C include file
  
     Desc:     Structures, variables and typedefs required by the
               solaris library.
  
     File:     cm_os.x
  
     Sid:      cm_os.x 1.5  -  09/28/98 09:56:35
  
     Prg:      fmg
  
*********************************************************************21*/

#ifndef __CMOSX__
#define __CMOSX__

#ifdef __cplusplus
extern "C" {
#endif 


/* typedefs */

/* os */

/* keys */
typedef struct keys 
{
   U8  kw[SLEN];         /* keyword */
   S32 kv;               /* key value */
}Keys;

/* doubly linked list */
typedef struct dLList
{
   S8 *node;           /* node */
   struct dLList *next;  /* next */
   struct dLList *prev;  /* previous */
}DLList;

#ifndef CONST
#ifdef ANSI
#define CONST const
#else
#define CONST
#endif
#endif

#ifdef ANSI
typedef void OsVoid;
#else
typedef char OsVoid;
#endif /* ANSI */

typedef unsigned int OsSize;  /* Size */
typedef OsVoid *     OsFile;  /* File */
typedef int          OsInt;   /* Integer */
typedef long         OsLong;  /* Long Integer */
typedef void         *(*TFN) ARGS((void *));  /* Thread function */

/* variables */
EXTERN S8 *OsOptArg;
EXTERN OsInt OsOptInd;
EXTERN OsInt OsOptErr;
EXTERN OsInt OsOptOpt;

/* EXTERN functions */
EXTERN S32 osMatchKeyword ARGS((Keys *keys, S8 *tkn));
EXTERN S8 *osGetWord ARGS((S8* line, S8* word));
EXTERN OsFile *osFopen ARGS((CONST S8 *fName, CONST S8* flags));
EXTERN OsInt osFclose ARGS((OsFile *file));
EXTERN OsLong osStrtol ARGS((CONST S8 *str, S8 **ptr, OsInt base));
EXTERN S8 *osFgets ARGS((S8* buf, OsInt len, OsFile *file));
/*  : warning fix */
EXTERN S8 *osGets ARGS((S8* buf,S32 maxBufLen));
EXTERN OsInt osStrcmp ARGS((CONST S8 *s1, CONST S8 *s2));
EXTERN OsInt osStrncmp ARGS((CONST S8 *s1, CONST S8 *s2, OsSize size));
EXTERN OsVoid *osCalloc ARGS((OsSize nelem, OsSize size));
EXTERN S8 *osStrcpy ARGS((S8 *s1, CONST S8 *s2));
EXTERN OsInt osReadAccess ARGS((CONST S8 *file));
EXTERN OsVoid *osMemcpy ARGS((OsVoid *s1, CONST OsVoid *s2, OsSize len));
EXTERN OsSize osFread ARGS((OsVoid *ptr, OsSize, OsSize, OsFile *));
EXTERN OsSize osFwrite ARGS((CONST OsVoid *ptr, OsSize, OsSize, OsFile *)); 
EXTERN OsSize osStrlen ARGS((CONST S8 *str));
EXTERN S8    *osStrcat ARGS((S8 *dst, CONST S8 *src));
EXTERN OsInt osFseek ARGS((OsFile *fp, OsLong offset, OsInt whence));
EXTERN OsInt osGetopt ARGS((OsInt argc, S8 * CONST *argv, CONST S8 *optStr));
EXTERN Void osSprintf ARGS((S8 *s, CONST S8 *fmt, ...));
EXTERN Void osPrintf ARGS((CONST S8 *fmt, ...));
EXTERN Void osFree ARGS((OsVoid *ptr));
EXTERN OsInt osIsascii ARGS((OsInt c));
EXTERN OsInt osIsprint ARGS((OsInt c));
EXTERN OsInt osIsspace ARGS((OsInt c));
EXTERN Txt *osTmpnam ARGS((void));
EXTERN Void osUnlink ARGS((CONST S8 *fName));
EXTERN Void osSleep ARGS((U32 seconds));
EXTERN Void osMsSleep ARGS((U32 mSeconds));
EXTERN S8 *osMmap ARGS((S8 *addr, OsSize len, OsInt prot, OsInt flags,
   OsInt fildes, OsLong off));
EXTERN OsInt osFileno ARGS((OsFile *file));
EXTERN OsInt osMunmap ARGS((S8 *addr, OsSize len));
EXTERN Void osBzero ARGS((OsVoid *ptr, OsSize size));
EXTERN OsVoid *osMemset ARGS((OsVoid *s, OsInt c, OsSize len));
EXTERN Void osExit ARGS ((OsInt code));
EXTERN Void osPerror ARGS ((Txt *msg));
EXTERN S16 osAdd2LList ARGS(( DLList **dlList, Txt *node));
EXTERN Txt *osDelFrmLList ARGS(( DLList **dlList, DLList *nodePtr));
EXTERN DLList *osNextDLList ARGS(( DLList *dlList));
EXTERN DLList *osPrevDLList ARGS(( DLList *dlList));
EXTERN Txt  *osNodeDLList ARGS(( DLList *dlList));
EXTERN OsInt osRand ARGS((void));
EXTERN OsInt osGetchar ARGS((void));
EXTERN S16   osInitCon ARGS((void));
EXTERN S16   osRdCon   ARGS((Data *dataPtr));
EXTERN S16   osGetTimeOfDay   ARGS((U32 *tmSec, U32 *tmUsec));
EXTERN S16   osOpen   ARGS((S8 *path, S32 oflag, U32 mode, S32 *fd));
EXTERN S16   osFtruncate   ARGS((S32 fd, U32 length));
EXTERN S16   osMlockall   ARGS((S32 flags));
EXTERN S16   osMunlockall   ARGS((void));
EXTERN S16   osGeteuid   ARGS((S32 *euid));
EXTERN S16   osClose    ARGS((S32 fd));
PUBLIC OsSize osRead    ARGS((S32 fd, Data *data, OsSize nitems));
PUBLIC OsSize osWrite   ARGS((S32 fd, Data *data, OsSize nitems));
PUBLIC S32    osSeekStart ARGS((S32 fd));

/* error */

EXTERN Void osErrQuit ARGS((CONST S8 *fmt, ...));
EXTERN Void osErrSys ARGS((CONST S8 *fmt, ...));
EXTERN Void osErrRet ARGS((CONST S8 *fmt, ...));
EXTERN Void osErrDump ARGS((CONST S8 *fmt, ...));

/* ipc */

/* sessage structure  */
typedef struct mesg
{
   U32 mesg_len;                /* length of message  */
   S32 mesg_type;               /* message type */
   Pst pst;                     /* post structure */
   S32 sIdx;                    /* start indext */
   Txt mesg_data[MAXMESGDATA];  /* message data */
}Mesg;

EXTERN S32 osMsgSend ARGS((S32 id, Mesg *mPtr));
EXTERN S32 osMsgRecv ARGS((S32 id, Mesg *mPtr, Bool wFlag)); 
EXTERN S32 osMsgCreate ARGS((S32 key, S32 *id)); 
EXTERN S32 osMsgGet ARGS((S32 key, S32 *id));

EXTERN S32 osStripBlanks ARGS((S8 *rawStr));

/* file locking */
EXTERN S16 osOpenLockFile ARGS((Txt *file, S32 *fd));
EXTERN S16 osTryLockFile  ARGS((S32 fd));
EXTERN S16 osLockFile     ARGS((S32 fd));
EXTERN S16 osUnlockFile   ARGS((S32 fd));

EXTERN U8  osSystem      ARGS((Txt *command));

/* cms */
EXTERN Void osCmsInit  ARGS((Void));
EXTERN Void osCmsLog   ARGS((Txt *logMsg));

#ifdef SUNOS51
/* MT os wrappers */
EXTERN S16 osThrCreate ARGS((void *stackBase, U32 stackSize, \
                             TFN startRoutine, void *arg,    \
                             U32 thrFlags, U32 *newThread));
EXTERN S16 osThrSuspend ARGS((U32 targetThread));
EXTERN S16 osThrSelf    ARGS((U32 *threadId));
#endif /* SUNOS51 */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CMOSX__ */


/********************************************************************30**

         End of file: cm_os.x 1.5  -  09/28/98 09:56:35

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
----------- -------- ---- -----------------------------------------------
 
*********************************************************************91*/

/*********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- -----------------------------------------------
1.1            ---    fmg  1. initial release.

1.2            ---    fl   1. renamed os_lib.* to cm_os.*

1.3            ---    mb   1. Release for Integ ss7

1.4            ---    ns   1. Added extern "C" for making this file C++
                              compatible
               ---    ns   2. Removed OsOptArg, OsOptInd, OsOptErr and 
                              OsOptOpt and added into cm_os.c

1.5            ---    kr   1. Moved OsOptArg, OsOptInd, OsOptErr and
                              OsOptOpt back her
1.6            ---    avenugop 1. modified function prototype for osGets
**********************************************************************91*/
