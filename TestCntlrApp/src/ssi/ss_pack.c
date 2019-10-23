

/********************************************************************20**
 
     Name:     System Services -- packing
 
     Type:     C source file
 
     Desc:     Source code for System Services packing functions.
 
     File:     ss_pack.c
 
     Sid:      sm_pack.c@@/main/1 - Mon Nov 17 15:54:36 2008
 
     Prg:      kp
  
*********************************************************************21*/


/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
  
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

#include "ss_err.h"        /* errors */
#include "ss_dep.h"        /* implementation-specific */
#include "ss_queue.h"      /* queues */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */



/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */

#include "ss_dep.x"        /* implementation-specific */
#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */
#include "cm_lib.x"

  
/*
*
*       Fun:   SPkS8
*
*       Desc:  This function packs a signed 8 bit value into a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/

#ifdef ANSI
PUBLIC S16 SPkS8
(
S8 val,                     /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkS8(val, mBuf)
S8 val;                     /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;                 /* return code */
   TRC1(SPkS8)
   ret = SAddPreMsg((Data) val, mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_ADD_RES, ESS242, (ErrVal)ret, "SAddPreMsg() failed");
#endif
   RETVALUE(ret);
} /* end of SPkS8 */
  

  
/*
*
*       Fun:   SPkU8
*
*       Desc:  This function packs an unsigned 8 bit value into a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPkU8
(
U8 val,                     /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkU8(val, mBuf)
U8 val;                     /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;                 /* return code */
   TRC1(SPkU8)
   ret = SAddPreMsg((Data) val, mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_ADD_RES, ESS243, (ErrVal)ret, "SAddPreMsg() failed");
#endif
   RETVALUE(ret);
} /* end of SPkU8 */
  
/*
*
*       Fun:   SPkS16
*
*       Desc:  This function packs a signed 16 bit value into a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPkS16
(
S16 val,                    /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkS16(val, mBuf)
S16 val;                    /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   Data pkArray[2];         /* array for packing */
   S16 ret;                 /* return code */

   TRC1(SPkS16)
#ifndef FCSPKINT            /* backward compatibility, packing order */
   pkArray[0] = (Data) GetHiByte(val);
   pkArray[1] = (Data) GetLoByte(val);
#else                   /* forward compatibility, packing order */
   pkArray[1] = (Data) GetHiByte(val);
   pkArray[0] = (Data) GetLoByte(val);
#endif
   ret = SAddPreMsgMult(pkArray, (MsgLen) 2, mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_ADD_RES, ESS244, (ErrVal)ret, "SAddPreMsgMult() failed");
#endif
   RETVALUE(ret);
} /* end of SPkS16 */
  
  
/*
*
*       Fun:   SPkU16
*
*       Desc:  This function packs an unsigned 16 bit value into a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPkU16
(
U16 val,                    /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkU16(val, mBuf)
U16 val;                    /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   Data pkArray[2];         /* array for packing */
   S16 ret;                 /* return code */

   TRC1(SPkU16)
#ifndef FCSPKINT            /* backward compatibility, packing order */
   pkArray[0] = (Data) GetHiByte(val);
   pkArray[1] = (Data) GetLoByte(val);
#else                       /* forward compatibility, packing order */
   pkArray[1] = (Data) GetHiByte(val);
   pkArray[0] = (Data) GetLoByte(val);
#endif
   ret = SAddPreMsgMult(pkArray, (MsgLen) 2, mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_ADD_RES, ESS245, (ErrVal)ret, "SAddPreMsgMult() failed");
#endif
   RETVALUE(ret);
} /* end of SPkU16 */
  
  
/*
*
*       Fun:   SPkS32
*
*       Desc:  This function packs a signed 32 bit value into a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPkS32
(
S32 val,                    /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkS32(val, mBuf)
S32 val;                    /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   U16 tmp;                 /* temporary value */
   Data pkArray[4];         /* packing array */
   S16 ret;                 /* return code */
  
   TRC1(SPkS32)
#ifndef FCSPKINT        /* backward compatibility, packing order */
   tmp = (U16) GetHiWord(val);
   pkArray[0] = (Data) GetHiByte(tmp);
   pkArray[1] = (Data) GetLoByte(tmp);
   tmp = (U16) GetLoWord(val);
   pkArray[2] = (Data) GetHiByte(tmp);
   pkArray[3] = (Data) GetLoByte(tmp);
#else                   /* forward compatibility, packing order */
   tmp = (U16) GetHiWord(val);
   pkArray[3] = (Data) GetHiByte(tmp);
   pkArray[2] = (Data) GetLoByte(tmp);
   tmp = (U16) GetLoWord(val);
   pkArray[1] = (Data) GetHiByte(tmp);
   pkArray[0] = (Data) GetLoByte(tmp);
#endif
   ret = SAddPreMsgMult(pkArray, (MsgLen) 4, mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_ADD_RES, ESS246, (ErrVal)ret, "SAddPreMsgMult() failed");
#endif
   RETVALUE(ret);
} /* end of SPkS32 */
  
  
/*
*
*       Fun:   SPkU32
*
*       Desc:  This function packs an unsigned 32 bit value into a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPkU32
(
U32 val,                    /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkU32(val, mBuf)
U32 val;                    /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   U16 tmp;                 /* temporary value */
   Data pkArray[4];         /* packing array */
   S16 ret;                 /* return code */
  
   TRC1(SPkU32)
#ifndef FCSPKINT        /* backward compatibility, packing order */
   tmp = (U16) GetHiWord(val);
   pkArray[0] = (Data) GetHiByte(tmp);
   pkArray[1] = (Data) GetLoByte(tmp);
   tmp = (U16) GetLoWord(val);
   pkArray[2] = (Data) GetHiByte(tmp);
   pkArray[3] = (Data) GetLoByte(tmp);
#else                   /* forward compatibility, packing order */
   tmp = (U16) GetHiWord(val);
   pkArray[3] = (Data) GetHiByte(tmp);
   pkArray[2] = (Data) GetLoByte(tmp);
   tmp = (U16) GetLoWord(val);
   pkArray[1] = (Data) GetHiByte(tmp);
   pkArray[0] = (Data) GetLoByte(tmp);
#endif
   ret = SAddPreMsgMult(pkArray, (MsgLen) 4, mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_ADD_RES, ESS247, (ErrVal)ret, "SAddPreMsgMult() failed");
#endif
   RETVALUE(ret);
} /* end of SPkU32 */

/*ss038.103  1. Added Floating point support*/
#ifdef SS_FLOAT
/*
*
*       Fun:   SPkF32
*
*       Desc:  This function packs an 32 bit ieee-754 format float value into a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPkF32
(
F32 val,                    /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkF32(val, mBuf)
F32 val;                    /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16  ret;                /* return code */
   S8   tmpArray[15];       /* temporary array */
#ifdef FCSPKINT             /* backward compatibility, packing order */
   S32  tIdx = 14;          /* counters */
   S32  kIdx = 0;           /* counters */
   S8   pkArray[15];        /* packing array */
#endif /*FCSPKINT*/
  
   TRC1(SPkF32)

   sprintf(tmpArray, "%.7e", val);

#ifndef FCSPKINT            /* backward compatibility, packing order */
   ret = SAddPreMsgMult((Data*)tmpArray, (MsgLen) 15, mBuf);
#else
   while(tIdx >= 0)
   {
      pkArray[kIdx] = tmpArray[tIdx];
      tIdx--; kIdx++;
   }
   ret = SAddPreMsgMult((Data*)pkArray, (MsgLen) 15, mBuf);
#endif


#if (ERRCLASS & ERRCLS_ADD_RES)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_ADD_RES, ESS248, (ErrVal)ret, "SAddPreMsgMult() failed");
#endif
   RETVALUE(ret);
} /* end of SPkF32 */

/*
*
*       Fun:   SPkF64
*
*       Desc:  This function packs an 64 bit ieee-754 format float value into a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPkF64
(
F64 val,                    /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkF64(val, mBuf)
F64 val;                    /* value */
Buffer *mBuf;               /* message buffer */
#endif
{

   S16  ret;                /* return code */
   S8   tmpArray[25];       /* temporary array */
#ifdef FCSPKINT             /* backward compatibility, packing order */
   S32  tIdx = 24;          /* counters */
   S32  kIdx = 0;           /* counters */
   S8   pkArray[25];        /* packing array */
#endif /*FCSPKINT*/
  
   TRC1(SPkF64)

   sprintf(tmpArray, "%.16le", val);

#ifndef FCSPKINT            /* backward compatibility, packing order */
   ret = SAddPreMsgMult((Data*)tmpArray, (MsgLen) 25, mBuf);
#else
   while(tIdx >= 0)
   {
      pkArray[kIdx] = tmpArray[tIdx];
      tIdx--; kIdx++;
   }
   ret = SAddPreMsgMult((Data*)pkArray, (MsgLen) 25, mBuf);
#endif


#if (ERRCLASS & ERRCLS_ADD_RES)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_ADD_RES, ESS249, (ErrVal)ret, "SAddPreMsgMult() failed");
#endif
   RETVALUE(ret);

} /* end of SPkF64 */
#endif /* SS_FLOAT */
  
/*
*
*       Fun:   SUnpkS8
*
*       Desc:  This function unpacks a signed 8 bit value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SUnpkS8
(
S8 *val,                    /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkS8(val, mBuf)
S8 *val;                    /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   Data tmp;                /* temporary value */
   S16 ret;                 /* return code */
   TRC1(SUnpkS8)

/* ss021.103 - Addition of data pointer check */
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!val)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS250, ERRZERO, "SUnpkS8 : Null value");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   ret = SRemPreMsg(&tmp, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_DEBUG, ESS251, (ErrVal)ret, "SRemPreMsg() failed");
#endif
   *val = (S8) tmp;
   RETVALUE(ret);
} /* end of SUnpkS8 */
  
  
/*
*
*       Fun:   SUnpkU8
*
*       Desc:  This function unpacks an unsigned 8 bit value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SUnpkU8
(
U8 *val,                    /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkU8(val, mBuf)
U8 *val;                    /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   Data tmp;                /* temporary value */
   S16 ret;                 /* return code */
   TRC1(SUnpkU8)

/* ss021.103 - Addition of data pointer check */
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!val)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS252, ERRZERO, "SUnpkU8 : Null value");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   ret = SRemPreMsg(&tmp, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_DEBUG, ESS253, (ErrVal)ret, "SRemPreMsg() failed");
#endif
   *val = (U8) tmp;
   RETVALUE(ret);
} /* end of SUnpkU8 */
  
/*
*
*       Fun:   SUnpkS16
*
*       Desc:  This function unpacks a signed 16 bit value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SUnpkS16
(
S16 *val,                   /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkS16(val, mBuf)
S16 *val;                   /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   U16 tmp16;               /* temporary value */
   Data unpkArray[2];       /* unpacking array */
   S16 ret;                 /* return code */
   TRC1(SUnpkS16)

/* ss021.103 - Addition of data pointer check */
   cmMemset((U8 *)unpkArray, 0, 2 * sizeof(Data));

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!val)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS254, ERRZERO, "SUnpkS16 : Null value");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   ret = SRemPreMsgMult(unpkArray, (MsgLen) 2, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_DEBUG, ESS255, (ErrVal)ret, "SRemPreMsgMult() failed");
#endif
   tmp16 = 0; 
#ifndef FCSPKINT            /* backward compatibility, packing order */
   tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[1]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[0]);
#else                       /* forward compatibility, packing order */
   tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[0]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[1]);
#endif
   *val = (S16) tmp16;
   RETVALUE(ret);
} /* end of SUnpkS16 */
  
  
/*
*
*       Fun:   SUnpkU16
*
*       Desc:  This function unpacks an unsigned 16 bit value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SUnpkU16
(
U16 *val,                   /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkU16(val, mBuf)
U16 *val;                   /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   U16 tmp16;               /* temporary value */
   Data unpkArray[2];       /* unpacking array */
   S16 ret;                 /* return code */
   TRC1(SUnpkU16)

/* ss021.103 - Addition of data pointer check */
   cmMemset((U8 *)unpkArray, 0, 2 * sizeof(Data));

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!val)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS256, ERRZERO, "SUnpkU16 : Null value");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   ret = SRemPreMsgMult(unpkArray, (MsgLen) 2, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_DEBUG, ESS257, (ErrVal)ret, "SRemPreMsgMult failed");
#endif
   tmp16 = 0; 
#ifndef FCSPKINT            /* backward compatibility, packing order */
   tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[1]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[0]);
#else                       /* forward compatibility, packing order */
   tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[0]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[1]);
#endif
   *val = tmp16;
   RETVALUE(ret);
} /* end of SUnpkU16 */
  
  
/*
*
*       Fun:   SUnpkS32
*
*       Desc:  This function unpacks a signed 32 bit value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SUnpkS32
(
S32 *val,                   /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkS32(val, mBuf)
S32 *val;                   /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   U16 tmp16;               /* temporary value */
   U32 tmp32;               /* temporary value */
   Data unpkArray[4];       /* unpacking array */
   S16 ret;                 /* return code */
   TRC1(SUnpkS32)

/* ss021.103 - Addition of data pointer check */
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!val)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS258, ERRZERO, "SUnpkS32 : Null value");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   ret = SRemPreMsgMult(unpkArray, (MsgLen) 4, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_DEBUG, ESS259, (ErrVal)ret, "SRemPreMsgMult() failed");
#endif
   tmp16 = 0;
   tmp32 = 0; 
#ifndef FCSPKINT            /* backward compatibility, packing order */
   tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[3]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[2]);
   tmp32 = (U32) PutHiWord(tmp32, (U16) tmp16);
   tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[1]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[0]);
   tmp32 = (U32) PutLoWord(tmp32, (U16) tmp16);
#else                       /* forward compatibility, packing order */
   tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[0]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[1]);
   tmp32 = (U32) PutHiWord(tmp32, (U16) tmp16);
   tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[2]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[3]);
   tmp32 = (U32) PutLoWord(tmp32, (U16) tmp16);
#endif
   *val = (S32) tmp32;
   RETVALUE(ret);
} /* end of SUnpkS32 */
  
  
/*
*
*       Fun:   SUnpkU32
*
*       Desc:  This function unpacks an unsigned 32 bit value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SUnpkU32
(
U32 *val,                   /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkU32(val, mBuf)
U32 *val;                   /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   U16 tmp16;               /* temporary value */
   U32 tmp32;               /* temporary value */
   Data unpkArray[4];       /* unpacking array */
#ifdef ERRCLASS
   S16 ret;                 /* return code */
#endif /* ERRCLASS */
   TRC1(SUnpkU32)

/* ss021.103 - Addition of data pointer check */
   cmMemset((U8 *)unpkArray, 0, 4 * sizeof(Data));

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!val)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS260, ERRZERO, "SUnpkU32 : Null value");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   ret = SRemPreMsgMult(unpkArray, (MsgLen) 4, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_DEBUG, ESS261, (ErrVal)ret, "SRemPreMsgMult() failed");
#endif

   tmp16 = 0;
   tmp32 = 0; 
#ifndef FCSPKINT            /* backward compatibility, packing order */
   tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[3]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[2]);
   tmp32 = (U32) PutHiWord(tmp32, (U16) tmp16);
   tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[1]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[0]);
   tmp32 = (U32) PutLoWord(tmp32, (U16) tmp16);
#else                       /* forward compatibility, packing order */
   tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[0]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[1]);
   tmp32 = (U32) PutHiWord(tmp32, (U16) tmp16);
   tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[2]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[3]);
   tmp32 = (U32) PutLoWord(tmp32, (U16) tmp16);
#endif
   *val = tmp32;
   RETVALUE(ret);
} /* end of SUnpkU32 */

/*ss038.103  1. Added Floating point support*/
#ifdef SS_FLOAT
/*
*
*       Fun:   SUnpkF32
*
*       Desc:  This function unpacks an 32 bit ieee-754 format float value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SUnpkF32
(
F32 *val,                   /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkF32(val, mBuf)
F32 *val;                   /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;                 /* return code */
   S8 tmpArray[15];         /* temporary array */
#ifndef FCSPKINT            /* backward compatibility, packing order */
   S32 tIdx = 14;           /* temparory array index */
   S32 kIdx = 0;            /* unpacking array index */
   S8 unpkArray[15];        /* unpacking array */
#endif /* FCSPKINT */

   TRC1(SUnpkF32)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!val)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS262, ERRZERO, "SUnpkF32 : Null value");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   ret = SRemPreMsgMult((Data*)tmpArray, (MsgLen) 15, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_DEBUG, ESS263, (ErrVal)ret, "SRemPreMsgMult() failed");
#endif

#ifndef FCSPKINT            /* backward compatibility, packing order */
   while(tIdx >= 0)
   {
      unpkArray[kIdx] = tmpArray[tIdx];
      tIdx--; kIdx++;
   }
   sscanf(unpkArray, "%f", val);
#else
   sscanf(tmpArray, "%f", val);
#endif

   RETVALUE(ret);

} /* end of SUnpkF32 */

/*
*
*       Fun:   SUnpkF64
*
*       Desc:  This function unpacks an 64 bit ieee-754 format float value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SUnpkF64
(
F64 *val,                   /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkF64(val, mBuf)
F64 *val;                   /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{

   S16 ret;                 /* return code */
   S8 tmpArray[25];         /* temporary array */
#ifndef FCSPKINT            /* backward compatibility, packing order */
   S32 tIdx = 24;           /* temparory array index */
   S32 kIdx = 0;            /* unpacking array index */
   S8 unpkArray[25];        /* unpacking array */
#endif /* FCSPKINT */

   TRC1(SUnpkF64)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!val)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS264, ERRZERO, "SUnpkF64 : Null value");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   ret = SRemPreMsgMult((Data*)tmpArray, (MsgLen) 25, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_DEBUG, ESS265, (ErrVal)ret, "SRemPreMsgMult() failed");
#endif

#ifndef FCSPKINT            /* backward compatibility, packing order */
   while(tIdx >= 0)
   {
      unpkArray[kIdx] = tmpArray[tIdx];
      tIdx--; kIdx++;
   }
   sscanf(unpkArray, "%lf", val);
#else
   sscanf(tmpArray, "%lf", val);
#endif

   RETVALUE(ret);

} /* end of SUnpkF64 */
#endif /* SS_FLOAT */

/********************************************************************30**
  
         End of file:     sm_pack.c@@/main/1 - Mon Nov 17 15:54:36 2008
  
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
1.1          ---      kp   1. initial release

1.2          ---      bsr  1. Regenerated the error codes
1.3+        ss021.103 bjp  1. Added valid data check for unpacking functions
1.3+        ss029.103 kkj  1. Errcodes changes
1.3+        ss038.103 svp  1. Added Floating point support. 
/main/1      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/
