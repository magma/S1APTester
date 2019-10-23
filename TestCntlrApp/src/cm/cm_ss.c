

/********************************************************************20**
 
     Name:     common system services
 
     Type:     C source file
 
     Desc:     Common C source code for System Services
 
     File:     cm_ss.c
 
     Sid:      cm_ss.c@@/main/17 - Tue May 31 13:34:03 2005
 
     Prg:      mb
  
*********************************************************************21*/
  
  
/*
  
System services are the functions required by the protocol
layer for buffer management, timer management, date/time
management, resource checking and initialization.
  
The following functions are in provided in this file:

     SPkS8          Pack signed 8 bit
     SPkU8          Pack unsigned 8 bit
     SPkS16         Pack signed 16 bit
     SPkU16         Pack unsigned 16 bit
     SPkS32         Pack signed 32 bit
     SPkU32         Pack unsigned 32 bit
     SUnpkS8        Unpack signed 8 bit
     SUnpkU8        Unpack unsigned 8 bit  
     SUnpkS16       Unpack signed 16 bit
     SUnpkU16       Unpack unsigned 16 bit
     SUnpkS32       Unpack signed 32 bit
     SUnpkU32       Unpack unsigned 32 bit
     SPrint         Print
     SPrntMsg       Print Message
   
     SInitQueue     Initialize Queue
     SQueueFirst    Queue to First Place
     SQueueLast     Queue to Last Place
     SDequeueFirst  Dequeue from First Place
     SDequeueLast   Dequeue from Last Place
     SFlushQueue    Flush Queue
     SCatQueue      Concatenate Queue
     SFndLenQueue   Find Length of Queue
     SExamQueue     Examine Queue
     SAddQueue      Add Queue
     SRemQueue      Remove Queue
  
     SGetMsg        Get Message
     SPutMsg        Put Message
     SInitMsg       Initialize Message
  
     SAddPreMsg     Add Pre Message
     SAddPstMsg     Add Post Message
     SRemPreMsg     Remove Pre Message
     SRemPstMsg     Remove Post Message
     SAddPreMsgMult Add Pre Message Multiple
     SAddPstMsgMult Add Post Message Multiple
     SGetPstMsgMult Get Post Message Multiple
     SRemPreMsgMult Remove Pre Message Multiple
     SRemPstMsgMult Remove Post Message Multiple
     SRepMsg        Replace Message
     SExamMsg       Examine Message
     SFndLenMsg     Find Length of Message
     SCatMsg        Concatenate Message
     SSegMsg        Segment Message
  
     SCpyFixMsg     Copy from Fixed Buffer to Message
     SCpyMsgFix     Copy from Message to Fixed Buffer
     SCpyMsgMsg     Copy from Message to Message
     SCompressMsg   Compress Message into the minimum number of Data buffers

  
     SRegInit       Register Initialization routine


     SAddDBufPst    Add Data Buffer to End of Message
     SAddDBufPre    Add Data Buffer to Front of Message
     SRemDBufPst    Remove Data Buffer from End of Message
     SRemDBufPre    Remove Data Buffer from Front of Message
     SGetDataRx     Get Data Pointer and Length (receive)
     SGetDataTx     Get Data Pointer and Length (transmit)
     SUpdMsg        Update Message with New Data Buffer
     SAlignDBufEven Align Data Buffer on Even Boundary
     SInitNxtDBuf   Initialize a Message's Next Data Buffer Pointer
     SGetNxtDBuf    Get the Next Data Buffer in a Message
     SChkNxtDBuf    Check the Next Data Buffer in a Message
     SChkMsg        Check that the first buffer in a message contains at least two bytes
     SAddMsgRef     Make a reference message

It should be noted that not all of these functions may be required
by a particular system services service user.

It is assumed that the following functions are provided in the
system services service user (ss_ptsu.c) file:
  
     SActvInit      Activate layer - initialize
     SActvTmr       Activate layer - timer
     SActvTsk       Activate layer - task (old)
     SActvTask      Activate layer - task (new)
  
*/
  
  
/*
*     this software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*
*/
  
/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
  

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#ifndef CMFILE_REORG_1
#include "cm_gen.h"        /* common pack/unpack functions */
#endif
#include "cm_err.h"        /* error */

#ifdef WIN32
#include <stdio.h>         /* win32 - standard io */
#else
#ifdef DOS                 /* dos environment */
#include <stdio.h>         /* dos - standard io */
#else
#ifdef UNIX                /* unix environment */
#include <stdio.h>         /* unix - standard io */
#endif /* WIN32 */
#endif /* DOS */
#endif /* UNIX */

/* header/extern include files (.x) */
  

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#ifndef CMFILE_REORG_1
#include "cm_gen.x"        /* common */
#endif


  
/* Macro for logging error */
#define CMLOGERROR(errCls, errCode, errVal, errDesc) \
   SLogError( ENTNC, INSTNC, SFndProcId(), __FILE__, __LINE__, \
              errCls, errCode, errVal, errDesc )

  
/* forward references */
 
PUBLIC S16   cmInitDat ARGS((Data data, Region region, Pool pool, 
                                   S16 itype, Buffer **dbufPtr));
 
  
/*
*     support functions
*/
 
  
/*
*
*       Fun:   cmInitDat
*
*       Desc:  This function initializes a data buffer and places a
*              byte of data at the start or end of the buffer.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general
*              ROUTRES  - failed, out of resources
*
*       Notes: None
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmInitDat
(
Data data,                  /* data */
Region region,              /* region */
Pool pool,                  /* pool */
S16 itype,                  /* initialization type */
Buffer **dbufPtr            /* pointer to data buffer */
)
#else
PUBLIC S16 cmInitDat(data, region, pool, itype, dbufPtr)
Data data;                  /* data */
Region region;              /* region */
Pool pool;                  /* pool */
S16 itype;                  /* initialization type */
Buffer **dbufPtr;           /* pointer to data buffer */
#endif
{
   Buffer *dbuf;            /* data buffer */
   S16 ret;                 /* return code */
   S16 strtIdx;             /* Start Index */
   S16 endIdx;              /* End Index */
   S16 size;                /* Data Size */
   S16 pad;                 /* Pad */
  
   TRC0(cmInitDat)
 
   ret = SGetDBuf(region, pool, &dbuf);
   if (ret != ROK)
   {
      RETVALUE(ret);
   }
 
   /* initialize chain pointer of data buffer */
   SS_INITDCHN(&dbuf->dChn);
   
   SGetStrtIdx(region, pool, &strtIdx);
   SGetEndIdx(region, pool, &endIdx);
   SGetDBufSiz(region, pool, &size);
   SGetStrtPad(region, pool, &pad);

   /* check initialization type */
   switch(itype)
   {
      case PREBUF:   /* add data pre buffer */
         dbuf->t.dat.strtIdx = endIdx;
         dbuf->t.dat.endIdx = endIdx;
         /* store data in data buffer */
         dbuf->t.dat.data[endIdx] = data;
         break;
      case PSTBUF:   /* add data post buffer */
         dbuf->t.dat.strtIdx = strtIdx+pad;
         dbuf->t.dat.endIdx = strtIdx+pad;
         /* store data in data buffer */
         dbuf->t.dat.data[strtIdx+pad] = data;
         break;
      default:       /* add data unknown */
#if (ERRCLASS & ERRCLS_INT_PAR)
         CMLOGERROR(ERRCLS_INT_PAR, ECM166, (ErrVal)itype, "Wrong itype");
#endif /* ERRCLASS */
         RETVALUE(RFAILED);
   }
   /* set buffer type to data buffer */
   dbuf->bufType = BDATA;
   /* set buffer size */
   dbuf->t.dat.size = size;
   *dbufPtr = dbuf;
   RETVALUE(ROK);
} /* end of cmInitDat */


/*
*     system services
*/
  
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
*       File:  cm_ss.c
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
      CMLOGERROR(ERRCLS_ADD_RES, ECM037, (ErrVal)ret, "SAddPreMsg() Failed");
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
*       File:  cm_ss.c
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
      CMLOGERROR(ERRCLS_ADD_RES, ECM038, (ErrVal)ret, "SAddPreMsg() Failed");
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
*       File:  cm_ss.c
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
      CMLOGERROR(ERRCLS_ADD_RES, ECM039, (ErrVal)ret, "SAddPreMsgMult() Failed");
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
*       File:  cm_ss.c
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
      CMLOGERROR(ERRCLS_ADD_RES, ECM040, (ErrVal)ret, "SAddPreMsgMult() failed");
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
*       File:  cm_ss.c
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
      CMLOGERROR(ERRCLS_ADD_RES, ECM041, (ErrVal)ret, "SAddPreMsgMult() failed");
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
*       File:  cm_ss.c
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
      CMLOGERROR(ERRCLS_ADD_RES, ECM042, (ErrVal)ret, "SAddPreMsgMult() failed");
#endif
   RETVALUE(ret);
} /* end of SPkU32 */

  
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
*       File:  cm_ss.c
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
   ret = SRemPreMsg(&tmp, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      CMLOGERROR(ERRCLS_DEBUG, ECM043, (ErrVal)ret, "SRemPreMsg() Failed");
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
*       File:  cm_ss.c
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
   ret = SRemPreMsg(&tmp, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      CMLOGERROR(ERRCLS_DEBUG, ECM044, (ErrVal)ret, "SRemPreMsg() Failed");
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
*       File:  cm_ss.c
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
   ret = SRemPreMsgMult(unpkArray, (MsgLen) 2, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      CMLOGERROR(ERRCLS_DEBUG, ECM045, (ErrVal)ret, "SRemPreMsgMult() Failed");
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
*       File:  cm_ss.c
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
   ret = SRemPreMsgMult(unpkArray, (MsgLen) 2, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      CMLOGERROR(ERRCLS_DEBUG, ECM046, (ErrVal)ret, "SRemPreMsgMult Failed");
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
*       File:  cm_ss.c
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
   ret = SRemPreMsgMult(unpkArray, (MsgLen) 4, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      CMLOGERROR(ERRCLS_DEBUG, ECM047, (ErrVal)ret, "SRemPreMsgMult() Failed");
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
*       File:  cm_ss.c
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

   ret = SRemPreMsgMult(unpkArray, (MsgLen) 4, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      CMLOGERROR(ERRCLS_DEBUG, ECM048, (ErrVal)ret, "SRemPreMsgMult() Failed");
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

  
/*
*     interface functions to system services
*/

  
/*
*
*       Fun:   SPrint
*
*       Desc:  This function prints a string.
*
*              This function should be used for debugging only.
*
*       Ret:   ROK      - ok
*
*       Notes: Buffer should be null terminated.
*
*              SDisplay will replace SPrint.
*
*              Typical usage consists of a call to sprintf to
*              format the string into a buffer followed by a
*              call to SPrint
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPrint
(
Txt *buf                  /* buffer */
)
#else
PUBLIC S16 SPrint(buf)
Txt *buf;                 /* buffer */
#endif
{
   TRC1(SPrint)
   SDisplay(0, buf);
   RETVALUE(ROK);
} /* end of SPrint */


  
/*
*
*       Fun:   SPrntMsg
*
*       Desc:  This function prints the contents of a message. The
*              following information is printed: queue length,
*              message length, direction, hexadecimal and ASCII
*              (if appropriate) values of all bytes in the message.
*
*              This function should be used for debugging only.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPrntMsg
(
Buffer *mBuf,               /* message buffer */
S16 src,                    /* source id */
S16 dst                     /* destination id */
)
#else
PUBLIC S16 SPrntMsg(mBuf, src, dst)
Buffer *mBuf;               /* message buffer */
S16 src;                    /* source id */
S16 dst;                    /* destination id */
#endif
{
   QLen qlen;               /* queue length */
   MsgLen mlen;             /* message length */
   S16 i;                   /* counter */
   S16 j;                   /* counter */
   S16 k;                   /* counter */
   U8 data;                 /* data */
   U8 tdata[16];            /* temporary data */
   S8 prntBuf[256];         /* print buffer */


   TRC1(SPrntMsg)

   if (mBuf == NULLP)
   {
      sprintf(prntBuf,"\nmsg: empty\n");
      SPrint(prntBuf);
      SPrint( "\n\n");
      RETVALUE(ROK);
   }

   qlen = SS_QLEN(&mBuf->t.msg.bufQ);
   mlen = SS_MLEN(mBuf);

   sprintf(prntBuf,"\nmsg: qlen: %d mlen: %ld   %d-->%d\n",
           (U16)qlen,(S32)mlen,src,dst);
   SPrint( prntBuf);
   SPrint( "dat: ");
   if (qlen == 0)
      SPrint( "empty");
   else
   {
      j = 0;
      for (i = 0;;i++,j++)
      {
         if (SExamMsg(&data, mBuf, i) == ROK)
         {
            /* not end of message */
            /* check if 16 bytes printed */
            if (j == 16)
            {
               /* 16 bytes printed */
               SPrint( " ");
               k = 0;
               /* print ascii for row */
               for (k = 0; k < 16; k++)
               {
                  if (AIsAscii(tdata[k]))
                  {
                     /* print character if printable */
                     sprintf(prntBuf,"%c",tdata[k]);
                     SPrint( prntBuf);
                  }
                  else
                     /* print . if non printable */
                     SPrint( ".");
               }
               SPrint( "\n     ");
               j = 0;
            }
            tdata[j] = data;
            /* print hex value */
            sprintf(prntBuf,"%02x ",(U16) data);
            SPrint( prntBuf);
         }
         else
         {
            /* end of message */
            k = 0;
            for (k = 0; k < (S16) ((16 - j) * 3); k++)
            {
               SPrint( " ");
            }
            SPrint( " ");
            k = 0;
            /* print ascii for row */
            for (k = 0; k < j; k++)
            {
               if (AIsAscii(tdata[k]))
               {
                  /* print character if printable */
                  sprintf(prntBuf,"%c",tdata[k]);
                  SPrint( prntBuf);
               }
               else
                  /* print . if non printable */
                  SPrint( ".");
            }
            break;
         }
      }
   }
   SPrint( "\n\n");
   RETVALUE(ROK);
} /* end of SPrntMsg */

  
/*
*
*       Fun:   SInitQueue
*
*       Desc:  This function initializes a queue.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: no assumptions are made about the previous state
*              of the queue.
*
*              queue size is set to zero.
*
*       File:  cm_ss.c
*
*/

#ifdef ANSI
PUBLIC S16 SInitQueue
(
Queue *q               /* queue */
)
#else
PUBLIC S16 SInitQueue(q)
Queue *q;              /* queue */
#endif
{
   TRC1(SInitQueue)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check queue pointer */
   if (!q)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM049, ERRZERO, "Null Ptr");
      RETVALUE(RFAILED);
   }
#endif
   SS_INITQUE(q);
   
   RETVALUE(ROK);
} /* end of SInitQueue */

  
/*
*
*       Fun:   SQueueFirst
*
*       Desc:  This function queues a data or message buffer to the
*              front of the specified queue.
*
*       Ret:   ROK     - ok
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: buffer is placed in the queue. queue
*              length is incremented.
*              
*              if queue is not empty: buffer is placed in front of all
*              other buffers in queue. queue length is incremented.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SQueueFirst
(
Buffer *buf,                /* buffer */
Queue *q                    /* queue */
)
#else
PUBLIC INLINE S16 SQueueFirst(buf, q)
Buffer *buf;                /* buffer */
Queue *q;                   /* queue */
#endif
{
  
   TRC1(SQueueFirst)

   /* check queue */
   if (q == NULLP)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      CMLOGERROR(ERRCLS_INT_PAR, ECM050, ERRZERO, "Null Ptr");
#endif /* ERRCLASS */
      RETVALUE(RFAILED);
   }

   if (q->crntSize == 0)
   {
      q->dChn.next = buf;
      q->dChn.prev = buf;
      q->crntSize++;
      RETVALUE(ROK);
   }

   buf->dChn.next = q->dChn.next;
   buf->dChn.next->dChn.prev = buf;
   q->dChn.next = buf;
   q->crntSize++;

   RETVALUE(ROK);
} /* end of SQueueFirst */

  
/*
*
*       Fun:   SQueueLast
*
*       Desc:  This function queues a data or message buffer to the
*              back of the specified queue.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: if queue is empty: buffer is placed in the queue.
*              queue length is incremented.
*              
*              if queue is not empty: buffer is placed behind all
*              other buffers in queue. queue length is incremented.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SQueueLast
(
Buffer *buf,                /* buffer */
Queue *q                    /* queue */
)
#else
PUBLIC INLINE S16 SQueueLast(buf, q)
Buffer *buf;                /* buffer */
Queue *q;                   /* queue */
#endif
{

   TRC1(SQueueLast)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check queue */
   if (q == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM051, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
   /* check queue */
   if (buf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM052, ERRZERO, "Null Buf Ptr");
      RETVALUE(RFAILED);
   }
#endif

   if (q->crntSize == 0)
   {
      q->dChn.next = buf;
      q->dChn.prev = buf;
      q->crntSize++;
      RETVALUE(ROK);
   }
   
   q->dChn.prev->dChn.next = buf;
   buf->dChn.prev = q->dChn.prev;
   q->dChn.prev = buf;
   q->crntSize++;


   RETVALUE(ROK);
} /* end of SQueueLast */

  
/*
*
*       Fun:   SDequeueFirst
*
*       Desc:  This function dequeues a data or message buffer from
*              the front of the specified queue.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*              
*              if queue is not empty: pointer to buffer is set to first
*              buffer in queue, first buffer in queue is removed and
*              return is ok. queue length is decremented.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SDequeueFirst
(
Buffer **bufPtr,            /* pointer to buffer */
Queue *q                    /* queue */
)
#else
PUBLIC INLINE  S16 SDequeueFirst(bufPtr, q)
Buffer **bufPtr;            /* pointer to buffer */
Queue *q;                   /* queue */
#endif
{
   Buffer *tBuf;
  
   TRC2(SDequeueFirst)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (bufPtr == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM053, ERRZERO, "Null Buf Ptr");
      RETVALUE(RFAILED);
   }
   /* check queue */
   if (q == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM054, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
#endif

   if (q->crntSize == 0)
   {
      *bufPtr = (Buffer*)NULLP;
      RETVALUE(ROKDNA);
   }
 
   tBuf = q->dChn.next;
   if (q->crntSize == 1)
   {
      q->dChn.prev = (Buffer*)NULLP;
      q->dChn.next = (Buffer*)NULLP;
   }
   else
   {
      q->dChn.next = tBuf->dChn.next;
      q->dChn.next->dChn.prev = (Buffer*)NULLP;
   }
 
   tBuf->dChn.next = (Buffer*)NULLP;
   tBuf->dChn.prev = (Buffer*)NULLP;
   
   q->crntSize--;
   *bufPtr = tBuf;

   RETVALUE(ROK);
} /* end of SDequeueFirst */

  
/*
*
*       Fun:   SDequeueLast
*
*       Desc:  This function dequeues a data or message buffer from the
*              back of the specified queue.
*
*       Ret:   ROK     - ok
*              ROKDNA  - ok, data not available
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*              
*              if queue is not empty: pointer to buffer is set to last
*              buffer in queue, last buffer in queue is removed and
*              return is ok. queue length is decremented.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SDequeueLast
(
Buffer **bufPtr,            /* pointer to buffer */
Queue *q                    /* queue */
)
#else
PUBLIC INLINE  S16 SDequeueLast(bufPtr, q)
Buffer **bufPtr;            /* pointer to buffer */
Queue *q;                   /* queue */
#endif
{
   Buffer *tBuf;
  
   TRC2(SDequeueLast)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (!bufPtr)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM055, ERRZERO, "Null Buf Ptr");
      RETVALUE(RFAILED);
   }
   /* check queue */
   if (!q)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM056, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
#endif

   if (q->crntSize == 0)
   {
      *bufPtr = NULLP;
      RETVALUE(ROKDNA);
   }
 
   tBuf = q->dChn.prev;
   if (q->crntSize == 1)
   {
      q->dChn.prev = (Buffer*)NULLP;
      q->dChn.next = (Buffer*)NULLP;
   }
   else
   {
      q->dChn.prev = tBuf->dChn.prev;
      q->dChn.prev->dChn.next = (Buffer*)NULLP;
   }
 
   tBuf->dChn.next = (Buffer*)NULLP;
   tBuf->dChn.prev = (Buffer*)NULLP;
   
   q->crntSize--;
   *bufPtr = tBuf;

   RETVALUE(ROK);
} /* end of SDequeueLast */

  
/*
*
*       Fun:   SFlushQueue
*
*       Desc:  This function will release all of the data or message
*              buffers on the specified queue.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: if queue is empty: no action is taken.
*
*              if queue is not empty: all buffers in queue are returned
*              to memory. queue length is set to zero.
*
*              if dequeud buffer is a message buffer, all data buffers
*              associated with the message buffer are returned to memory
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SFlushQueue
(
Queue *q                    /* queue */
)
#else
PUBLIC S16 SFlushQueue(q)
Queue *q;                   /* queue */
#endif
{
   Buffer *tBuf;
  
   TRC2(SFlushQueue)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check queue */
   if (!q)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM057, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
#endif

   /* return each message to the appropriate buffer pool */
   while (SDequeueFirst(&tBuf, q) != ROKDNA)
   {
      if (tBuf->bufType == BMSG)
      {
         SPutMsg(tBuf);
      }
      else if (tBuf->bufType == BDATA)
      {
         SPutDBuf(DFLT_REGION, tBuf->t.dat.pool, tBuf);
      }
      else
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         CMLOGERROR(ERRCLS_DEBUG, ECM058, ERRZERO, "Wrong Buf Type");
#endif /* ERRCLASS */
         RETVALUE(RFAILED);
      }
   }
 
   SInitQueue(q);
 
   RETVALUE(ROK);
} /* end of SFlushQueue */

  
/*
*
*       Fun:   SCatQueue
*
*       Desc:  This function will concatenate the two specified queues
*              into one queue.
*
*       Ret:   ROK     - ok
*              RFAILED - failed, general (optional)
*
*       Notes: if order equals Q1Q2: all buffers attached to queue 2 are
*              moved to the end of queue 1. queue 2 is set to empty.
*              queue 1 length is increased by length of queue 2. queue
*              2 length is set to zero. return is ok.
*
*              if order equals Q2Q1: all buffers attached to queue 2 are
*              moved to the front of queue 1. queue 2 is set to empty.
*              queue 1 length is increased by length of queue 2. queue
*              2 length is set to zero. return is ok.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SCatQueue
(
Queue *q1,                  /* queue 1 */
Queue *q2,                  /* queue 2 */
Order order                 /* order */
)
#else
PUBLIC S16 SCatQueue(q1, q2, order)
Queue *q1;                  /* queue 1 */
Queue *q2;                  /* queue 2 */
Order order;                /* order */
#endif
{
   TRC2(SCatQueue)
 
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!q1)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM059, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
 
   if (!q2)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM060, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS */
   
   if (q1->crntSize == 0)
   {
      q1->dChn.next = q2->dChn.next;
      q1->dChn.prev = q2->dChn.prev;
      q1->crntSize = q2->crntSize;
      SInitQueue(q2);
      RETVALUE(ROK);
   }

   if (q2->crntSize == 0)
      RETVALUE(ROK);
 
   switch(order)
   {
      case Q1Q2:
         /*
          * all buffers attached to queue 2 are
          * moved to the end of queue 1. queue 2 is set to empty.
          * queue 1 length is increased by length of queue 2. queue
          * 2 length is set to zero. return is ok.
          */
#if (ERRCLASS & ERRCLS_DEBUG)
         if ((!q1->dChn.prev) || (!q2->dChn.next))
         {
            CMLOGERROR(ERRCLS_DEBUG, ECM061, ERRZERO, "");
            RETVALUE(RFAILED);
         }
#endif /* ERRCLASS */
         {
            Buffer *left;
            Buffer *right;
         
            left = q1->dChn.prev;
            right = q2->dChn.next;
 
            left->dChn.next = right;
            right->dChn.prev = left;
            q1->dChn.prev = q2->dChn.prev;
            
            /* adjust q2 length */
            q1->crntSize += q2->crntSize;         
            /* reinitialize q2 */
            SInitQueue(q2);
         }
         break;
      case Q2Q1:
         /*
          * all buffers attached to queue 2 are
          * moved to the front of queue 1. queue 2 is set to empty.
          * queue 1 length is increased by length of queue 2. queue
          * 2 length is set to zero. return is ok.
          */
#if (ERRCLASS & ERRCLS_DEBUG)
         if ((!q2->dChn.prev) || (!q1->dChn.next))
         {
            CMLOGERROR(ERRCLS_DEBUG, ECM062, ERRZERO, "");
            RETVALUE(RFAILED);
         }
#endif /* ERRCLASS */
         {
            Buffer *left;
            Buffer *right;
         
            left = q2->dChn.prev;
            right = q1->dChn.next;
 
            left->dChn.next = right;
            right->dChn.prev = left;
            q1->dChn.next = q2->dChn.next;
            
            /* adjust q2 length */
            q1->crntSize += q2->crntSize;         
            /* reinitialize q2 */
            SInitQueue(q2);
         }
         break;
      default:
#if ( ERRCLASS & ERRCLS_DEBUG)         
         CMLOGERROR(ERRCLS_DEBUG, ECM063, ERRZERO, "Wrong Concatenation Order");
#endif /* ERRCLASS */
         RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);
} /* end of SCatQueue */


  
/*
*
*       Fun:   SFndLenQueue
*
*       Desc:  This function determines the length of a queue.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: length of queue is determined, queue is unchanged
*              and length is returned via pointer to length. return is ok.
*              
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SFndLenQueue
(
Queue *q,                   /* queue */
QLen *lngPtr                /* pointer to length */
)
#else
PUBLIC S16 SFndLenQueue(q, lngPtr)
Queue *q;                   /* queue */
QLen *lngPtr;               /* pointer to length */
#endif
{
   TRC1(SFndLenQueue)
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check queue */
   if (!q)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM064, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
   /* check length */
   if (!lngPtr)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM065, ERRZERO, "Null Q Len Ptr");
      RETVALUE(RFAILED);
   }
#endif

   *lngPtr = SS_QLEN(q);

   RETVALUE(ROK);
} /* end of SFndLenQueue */


/*
*
*       Fun:   Examine Queue
*
*       Desc:  This function examines the queue at the desired index.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: index is 0 based and indicates location in queue.
*
*              if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*
*              if queue is not empty: pointer to buffer is set to indexed
*              buffer in queue. return is ok. queue length is unchanged.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SExamQueue
(
Buffer **bufPtr,            /* pointer to buffer */
Queue *q,                   /* queue */
QLen idx                    /* index */
)
#else
PUBLIC S16 SExamQueue(bufPtr, q, idx)
Buffer **bufPtr;            /* pointer to buffer */
Queue *q;                   /* queue */
QLen idx;                   /* index */
#endif
{
   REG1 QLen qCnt;
 
   TRC2(SExamQueue)
 
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (!bufPtr)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM066, ERRZERO, "Null Buf Ptr");
      RETVALUE(RFAILED);
   }
 
   /* check index */
   if ((S32)idx < 0)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM067, ERRZERO, "-ve index ");
      RETVALUE(RFAILED);
   }
 
   /* check queue */
   if (!q)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM068, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS */
 
   /* check if queue is empty */
   if ( (q->crntSize == 0) || (idx >= q->crntSize) )
   {
      /* queue empty */
      *bufPtr = NULLP;
      RETVALUE(ROKDNA);
   }
 
   /* check queue length */
   if ( (S32)q->crntSize < 0 )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      CMLOGERROR(ERRCLS_DEBUG, ECM069, ERRZERO, "Check Queue Length");
#endif /* ERRCLASS */
      RETVALUE(RFAILED);
   }
 
   if (idx == 0)
   {
      *bufPtr = q->dChn.next;
   }
   else if (idx == q->crntSize -1)
   {
      *bufPtr = q->dChn.prev;
   } 
   else
   {
      *bufPtr = q->dChn.next;
      for (qCnt = idx; qCnt; qCnt--)
      {
         *bufPtr = (*bufPtr)->dChn.next;
#if (ERRCLASS & ERRCLS_DEBUG)
         if (*bufPtr == (Buffer*)NULLP)
         {
            CMLOGERROR(ERRCLS_DEBUG, ECM070, ERRZERO, "Null Buffer");
            RETVALUE(RFAILED);
         }
#endif /* ERRCLASS */
      }
   }
   
   RETVALUE(ROK);

} /* end of SExamQueue */


/*
*
*       Fun:   SAddQueue
*
*       Desc:  This function inserts into the queue before the desired index.
*
*       Ret:   ROK     - ok
*              RFAILED - failed, general (optional)
*
*       Notes: index is 0 based and indicates location in queue.
*
*              if queue is empty: buffer is placed in the queue.
*              queue length is incremented.
*
*              if queue is not empty: if index is less than the queue length, 
*              buffer is inserted before the desired index;
*              otherwise, buffer is placed behind all other buffers in queue.
*              queue length is incremented.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SAddQueue
(
Buffer *buf,                /* buffer */
Queue *q,                   /* queue */
QLen idx                    /* index */
)
#else
PUBLIC S16 SAddQueue(buf, q, idx)
Buffer *buf;                /* buffer */
Queue *q;                   /* queue */
QLen idx;                   /* index */
#endif
{
   TRC1(SAddQueue)
 
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check queue */
   if (q == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM071, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
 
   if (buf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM072, ERRZERO, "Null Buf Ptr");
      RETVALUE(RFAILED);
   }
 
   if ((S32)idx < 0)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM073, ERRZERO, "-ve index");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS */
 
   /* if queue is empty, or idx is zero, prepend */
   if ( (q->crntSize == 0) || (idx == 0))
      RETVALUE(SQueueFirst(buf,q));
 
   if (idx == q->crntSize -1)   /* last buffer in queue */
   {
      q->dChn.prev->dChn.prev->dChn.next = buf;
      buf->dChn.prev = q->dChn.prev->dChn.prev;
      buf->dChn.next = q->dChn.prev;
      q->dChn.prev->dChn.prev = buf;
      q->crntSize++;
      RETVALUE(ROK);
   }
 
   if (idx >= q->crntSize)      /* append buffer to queue */
      RETVALUE(SQueueLast(buf, q));
               
 
   /* okay we have to look for the insertion point */
   {
      Buffer *tBuf;
      S16 i;
         
      tBuf = q->dChn.next;      /* first buffer */
      for (i = idx; i; i--)
      {
         tBuf = tBuf->dChn.next;
#if (ERRCLASS & ERRCLS_DEBUG)
         if (tBuf == NULLP)
         {
            CMLOGERROR(ERRCLS_DEBUG, ECM074, ERRZERO, "Null Buffer");
            RETVALUE(RFAILED);
         }
#endif /* ERRCLASS */
            
      }
 
      tBuf->dChn.prev->dChn.next = buf;
      buf->dChn.prev = tBuf->dChn.prev;
      buf->dChn.next = tBuf;
      tBuf->dChn.prev = buf;
      /* increment queue size */
      q->crntSize++;
   }
      
   RETVALUE(ROK);

} /* end of SAddQueue */


/*
*
*       Fun:   SRemQueue
*
*       Desc:  This function removes from the queue at the desired index.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: index is 0 based and indicates location in queue.
*
*              if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*
*              if queue is not empty: pointer to buffer is set to indexed
*              buffer in queue. return is ok. queue length is decremented.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRemQueue
(
Buffer **bufPtr,            /* pointer to buffer */
Queue *q,                   /* queue */
QLen idx                    /* index */
)
#else
PUBLIC S16 SRemQueue(bufPtr, q, idx)
Buffer **bufPtr;            /* pointer to buffer */
Queue *q;                   /* queue */
QLen idx;                   /* index */
#endif
{
   TRC1(SRemQueue)
 
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (bufPtr == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM075, ERRZERO, "Null Buf Ptr");
      RETVALUE(RFAILED);
   }
 
   /* check queue */
   if (q == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM076, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
 
   if ((S32)idx < 0)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM078, ERRZERO, "-ve Index");
      RETVALUE(RFAILED);
   }      
#endif /* ERRCLASS */   
 
   /* check if queue is empty */
   if ( (q->crntSize == 0) || (idx >= q->crntSize) )
   {
      /* queue empty */
      *bufPtr = NULLP;
      RETVALUE(ROKDNA);
   }
 
   if (idx == 0)
   {
      RETVALUE(SDequeueFirst(bufPtr, q));
   }
   else if (idx == q->crntSize -1)
   {
      RETVALUE(SDequeueLast(bufPtr, q));
   } 

   
   /* okay, we have to look */
 
   {
      Buffer *tBuf;
      S16 i;
 
      tBuf = q->dChn.next;
      for(i = idx; i; i--)    /* count till idx */
      {
         tBuf = tBuf->dChn.next;
         if (tBuf == NULLP)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            CMLOGERROR(ERRCLS_DEBUG, ECM079, ERRZERO, "Null Buffer");
#endif /* ERRCLASS */
            RETVALUE(RFAILED);
         }
 
      }
      tBuf->dChn.prev->dChn.next = tBuf->dChn.next;
      tBuf->dChn.next->dChn.prev = tBuf->dChn.prev;
      tBuf->dChn.next = NULLP;
      tBuf->dChn.prev = NULLP;
      *bufPtr = tBuf;
      q->crntSize--;
   }
   
   RETVALUE(ROK);

} /* end of SRemQueue */

  
/*
*
*       Fun:   SInitMsg
*
*       Desc:  This function deallocates a message back and then
*              reinitializes the message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: all data attached to message is returned to memory.
*              message is set to empty. message is not returned to
*              memory. return is ok.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SInitMsg
(
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SInitMsg(mBuf)
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC1(SInitMsg)
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM083, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif
   /* return all data buffers */
   SFlushQueue(&mBuf->t.msg.bufQ);

   /* initialize chain pointer of message */
   SS_INITDCHN(&mBuf->dChn);

   /* initialize buffer queue of message */
   SS_INITQUE(&mBuf->t.msg.bufQ);
   
   /* set length of message back to zero */
   mBuf->t.msg.msgLen = 0;
   RETVALUE(ROK);
} /* end of SInitMsg */

  
/*
*
*       Fun:   SAddPreMsg
*
*       Desc:  This function copies one byte of data to the
*              beginning of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*              
*              if message is not empty: data is placed in front of all
*              other data in message. message length is incremented.
*              return is ok.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SAddPreMsg
(
Data data,                  /* data */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SAddPreMsg(data, mBuf)
Data data;                  /* data */
Buffer *mBuf;               /* message buffer */
#endif
{
   Buffer *dbuf;            /* data buffer */
   S16 ret;                 /* return code */
   Buffer *first;           /* first buffer in chain */
   S16 strtIdx;

   TRC1(SAddPreMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (!mBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM084, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif

   if (mBuf->t.msg.msgLen)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      if (mBuf->t.msg.bufQ.dChn.next == NULLP)
      {
         CMLOGERROR(ERRCLS_DEBUG, ECM085, ERRZERO, "Null Buffer");
         RETVALUE(RFAILED);
      }
#endif
      first = mBuf->t.msg.bufQ.dChn.next;

      /* check if data buffer full */

      SGetStrtIdx(DFLT_REGION , mBuf->t.msg.pool, &strtIdx);
      if (first->t.dat.strtIdx != (MsgLen) strtIdx)
      {
         /* data buffer not full */
         first->t.dat.strtIdx--;
         first->t.dat.data[first->t.dat.strtIdx] = data;
      }
      else
      {
         /* data buffer full */
         ret = cmInitDat(data, DFLT_REGION, mBuf->t.msg.pool, PREBUF, &dbuf);
         if (ret != ROK)
            RETVALUE(ret);
         SAddDBufPre(mBuf, dbuf);
      }

   }
   else
   {
      /* message empty */
      ret = cmInitDat(data, DFLT_REGION, mBuf->t.msg.pool, PREBUF, &dbuf);
      if (ret != ROK)
         RETVALUE(ret);
      SAddDBufPre(mBuf, dbuf);
   }

   /* increment message length */
   mBuf->t.msg.msgLen++;
   RETVALUE(ROK);
} /* end of SAddPreMsg */

  
/*
*
*       Fun:   SAddPstMsg 
*
*       Desc:  This function copies one byte of data to the
*              end of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*              
*              if message is not empty: data is placed in back of all
*              other data in message. message length is incremented.
*              return is ok.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SAddPstMsg 
(
Data data,                  /* data */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SAddPstMsg (data, mBuf)
Data data;                  /* data */
Buffer *mBuf;               /* message buffer */
#endif
{
   Buffer *dbuf;            /* data buffer */
   S16 ret;                 /* return code */
   Buffer *last;
   S16 endIdx;
   
   TRC1(SAddPstMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM086, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif

   SGetEndIdx( DFLT_REGION, mBuf->t.msg.pool, &endIdx);
   if (mBuf->t.msg.msgLen)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      if (mBuf->t.msg.bufQ.dChn.prev == NULLP)
      {
         CMLOGERROR(ERRCLS_DEBUG, ECM087, ERRZERO, "Null Buffer");
         RETVALUE(RFAILED);
      }
#endif
      last = mBuf->t.msg.bufQ.dChn.prev;
      if (last->t.dat.endIdx != (MsgLen) endIdx)
      {
         last->t.dat.endIdx++;
         last->t.dat.data[last->t.dat.endIdx] = data;
      }
      else
      {
         /* data buffer full */
         ret = cmInitDat(data, DFLT_REGION, mBuf->t.msg.pool, PSTBUF, &dbuf);
         if (ret != ROK)
            RETVALUE(ret);
         SAddDBufPst(mBuf, dbuf);
      }
   }
   else
   {
      /* message empty */
      ret = cmInitDat(data, DFLT_REGION, mBuf->t.msg.pool, PSTBUF, &dbuf);
      if (ret != ROK)
         RETVALUE(ret);
      SAddDBufPst(mBuf, dbuf);
   }
   mBuf->t.msg.msgLen++;

   RETVALUE(ROK);
} /* end of SAddPstMsg */

  
/*
*
*       Fun:   SRemPreMsg
*
*       Desc:  This function copies and then removes one byte of
*              data from the beginning of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*              
*              if message is not empty: data is removed from front of
*              message, data is returned via pointer to data. message
*              length is decremented. return is ok.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRemPreMsg
(
Data *dataPtr,              /* pointer to data */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SRemPreMsg(dataPtr, mBuf)
Data *dataPtr;              /* pointer to data */
Buffer *mBuf;               /* message buffer */
#endif
{
   Buffer *tdbuf;           /* temporary data buffer */
   Buffer *dbuf;            /* data buffer */
   MsgLen tmpStrtIdx;       /* temporary start index */
   MsgLen tmpEndIdx;        /* temporary end index */

   TRC1(SRemPreMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!dataPtr)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM088, ERRZERO, "Null data ptr");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (!mBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM089, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif

   /* check if message empty */
   if (mBuf->t.msg.msgLen < 1)
      RETVALUE(ROKDNA);

   /* message not empty */
#if (ERRCLASS & ERRCLS_DEBUG)
   if (mBuf->t.msg.bufQ.dChn.next == NULLP)
   {
      CMLOGERROR(ERRCLS_DEBUG, ECM090, ERRZERO, "Null Buffer");
      RETVALUE(RFAILED);
   }
#endif

   tdbuf = mBuf->t.msg.bufQ.dChn.next;
   tmpStrtIdx = tdbuf->t.dat.strtIdx;
   tmpEndIdx = tdbuf->t.dat.endIdx;
   /* check if data buffer empty */
   if (tmpStrtIdx == tmpEndIdx)
   {
      /* data buffer empty */
      *dataPtr = tdbuf->t.dat.data[tmpStrtIdx];
      SRemDBufPre(mBuf, &dbuf);
      SPutDBuf(DFLT_REGION, dbuf->t.dat.pool, dbuf);
   }
   else
   {
      /* data buffer not empty */
      *dataPtr = tdbuf->t.dat.data[tmpStrtIdx];
      tdbuf->t.dat.strtIdx = tmpStrtIdx + 1;
   }

   /* decrement message length */
   mBuf->t.msg.msgLen--;
   RETVALUE(ROK);
} /* end of SRemPreMsg */

  
/*
*
*       Fun:   SRemPstMsg
*
*       Desc:  This function copies and then removes one byte of
*              data from the end of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*              
*              if message is not empty: data is removed from back of
*              message, data is returned via pointer to data. message
*              length is decremented. return is ok.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRemPstMsg
(
Data *dataPtr,              /* pointer to data */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SRemPstMsg(dataPtr, mBuf)
Data *dataPtr;              /* pointer to data */
Buffer *mBuf;               /* message buffer */
#endif
{
   Buffer *dbuf;            /* data buffer */
   Buffer *tdbuf;           /* temporary data buffer */
   MsgLen tmpStrtIdx;       /* temporary start index */
   MsgLen tmpEndIdx;        /* temporary end index */
   
   TRC1(SRemPstMsg)
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (dataPtr == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM091, ERRZERO, "Null dataptr");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (mBuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM092, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif
   /* check if message empty */
   if (!mBuf->t.msg.msgLen)
   {
      /* message empty */
      *dataPtr = 0;
      RETVALUE(ROKDNA);
   }
   /* message not empty */
#if (ERRCLASS & ERRCLS_DEBUG)
   if (mBuf->t.msg.bufQ.dChn.prev == NULLP)
   {
      CMLOGERROR(ERRCLS_DEBUG, ECM093, ERRZERO, "Null buf");
      RETVALUE(RFAILED);
   }
#endif
   tdbuf = mBuf->t.msg.bufQ.dChn.prev;
   tmpStrtIdx = tdbuf->t.dat.strtIdx;
   tmpEndIdx = tdbuf->t.dat.endIdx;
   /* check if data buffer empty */
   if (tmpStrtIdx == tmpEndIdx)
   {
      /* data buffer empty */
      *dataPtr = tdbuf->t.dat.data[tmpEndIdx];
      SRemDBufPst(mBuf, &dbuf);
      SPutDBuf(DFLT_REGION, dbuf->t.dat.pool, dbuf);
   }
   else
   {
      /* data buffer not empty */
      *dataPtr = tdbuf->t.dat.data[tmpEndIdx];
      tmpEndIdx--;
      tdbuf->t.dat.endIdx = tmpEndIdx;
   }
   /* decrement message length */
   mBuf->t.msg.msgLen--;
   RETVALUE(ROK);
} /* end of SRemPstMsg */

  
/*
*
*       Fun:   SAddPreMsgMult
*
*       Desc:  This function copies consecutive bytes of data to the
*              beginning of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*              
*              if message is not empty: data is read by source pointer, 
*              data is placed in front of all other data in message.
*              message length is incremented. return is ok.
*
*              the first byte of data pointed to by the source pointer will
*              be placed at the front of the message first, the last byte of
*              data pointed to by the source pointer will be placed at the
*              front of the message last (i.e. it will become the first
*              byte of the message).
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SAddPreMsgMult
(
Data *src,                  /* source */
MsgLen cnt,                 /* count */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SAddPreMsgMult(src, cnt, mBuf)
Data *src;                  /* source */
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   Buffer *dbuf;            /* data buffer */
   S16 i;                   /* count */
   MsgLen tmpStrtIdx;       /* temporary start index */
   S16 ret;                 /* return code */
   S16 strtIdx;
  
   TRC1(SAddPreMsgMult)
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM094, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
   /* check source */
   if (src == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM095, ERRZERO, "Null Ptr");
      RETVALUE(RFAILED);
   }
   /* check count */
   if (cnt == 0)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM096, ERRZERO, "zero cnt");
      RETVALUE(RFAILED);
   }
#endif
   i = 0;
   /* check if message empty */   
   dbuf = mBuf->t.msg.bufQ.dChn.next;
   if (dbuf == NULLP)
   {
      /* message empty */
      ret = cmInitDat(src[i++], DFLT_REGION, mBuf->t.msg.pool, PREBUF, &dbuf);
      if (ret != ROK)
         RETVALUE(ret);
      SAddDBufPre(mBuf, dbuf);
   }

   SGetStrtIdx(DFLT_REGION , mBuf->t.msg.pool, &strtIdx);
   /* message not empty */
   tmpStrtIdx = dbuf->t.dat.strtIdx;
   for (; i < cnt; i++)
   {
      /* check if data buffer full */
      if (tmpStrtIdx == (MsgLen) strtIdx)
      {
         /* data buffer full */
         dbuf->t.dat.strtIdx = tmpStrtIdx;
         ret = cmInitDat(src[i], DFLT_REGION, mBuf->t.msg.pool, PREBUF, &dbuf);
         if (ret != ROK)
            RETVALUE(ret);
         SAddDBufPre(mBuf, dbuf);
         tmpStrtIdx = dbuf->t.dat.strtIdx;
      }
      else
      {
         /* data buffer not full */
         tmpStrtIdx--;
         dbuf->t.dat.data[tmpStrtIdx] = src[i];
      }
   }
   dbuf->t.dat.strtIdx = tmpStrtIdx;
   /* increment message length */
   mBuf->t.msg.msgLen += cnt;
   RETVALUE(ROK);
} /* end of SAddPreMsgMult */

  
/*
*
*       Fun:   SAddPstMsgMult
*
*       Desc:  This function copies consecutive bytes of data to the
*              end of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*              
*              if message is not empty: data is read by source pointer, 
*              data is placed in back of all other data in message.
*              message length is incremented. return is ok.
*
*              the first byte of data pointed to by the source pointer will
*              be placed at the back of the message first, the last byte of
*              data pointed to by the source pointer will be placed at the
*              back of the message last (i.e. it will become the last
*              byte of the message).
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SAddPstMsgMult
(
Data *src,                  /* source */
MsgLen cnt,                 /* count */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SAddPstMsgMult(src, cnt, mBuf)
Data *src;                  /* source */
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   Buffer *dbuf;            /* data buffer */
   S16 i;                   /* count */
   MsgLen tmpEndIdx;        /* temporary end index */
   S16 ret;                 /* return code */
   S16 endIdx;
  
   TRC1(SAddPstMsgMult)
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM097, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
   /* check source */
   if (src == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM098, ERRZERO, "Null Ptr");
      RETVALUE(RFAILED);
   }
   /* check count */
   if (cnt == 0)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM099, ERRZERO, "zero cnt");
      RETVALUE(RFAILED);
   }
#endif
   i = 0;
   /* check if message not empty */
   if (mBuf->t.msg.msgLen)
   {
      /* message not empty */
#if (ERRCLASS & ERRCLS_DEBUG)
      if (mBuf->t.msg.bufQ.dChn.prev == NULLP)
      {
         CMLOGERROR(ERRCLS_DEBUG, ECM100, ERRZERO, "Null buf");
         RETVALUE(RFAILED);
      }
#endif
      dbuf = mBuf->t.msg.bufQ.dChn.prev;
   }
   else
   {
      /* message empty */
      ret = cmInitDat(src[i++], DFLT_REGION, mBuf->t.msg.pool, PSTBUF, &dbuf);
      if (ret != ROK)
         RETVALUE(ret);
      SAddDBufPst(mBuf, dbuf);
   }
   SGetEndIdx( DFLT_REGION, mBuf->t.msg.pool, &endIdx);
   tmpEndIdx = dbuf->t.dat.endIdx;
   for (; i < cnt; i++)
   {
      /* check if data buffer full */
      if (tmpEndIdx == (MsgLen) endIdx)
      {
         /* data buffer full */
         dbuf->t.dat.endIdx = tmpEndIdx;
         ret = cmInitDat(src[i], 0, mBuf->t.msg.pool, PSTBUF, &dbuf);
         if (ret != ROK)
            RETVALUE(ret);
         SAddDBufPst(mBuf, dbuf);
         tmpEndIdx = dbuf->t.dat.endIdx;
      }
      else
      {
         /* data buffer not full */
         tmpEndIdx++;
         dbuf->t.dat.data[tmpEndIdx] = src[i];
      }
   }
   dbuf->t.dat.endIdx = tmpEndIdx;
   /* increment message length */
   mBuf->t.msg.msgLen += cnt;
   RETVALUE(ROK);
} /* end of SAddPstMsgMult */

  
/*
*
*       Fun:   SGetPstMsgMult
*
*       Desc:  This function allocates consecutive bytes of data at the
*              end of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: message length is incremented. 
*              return is ok.
*              
*              if message is not empty: space is allocated in back of 
*              all other data in message.  message length is incremented. 
*              return is ok.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetPstMsgMult
(
MsgLen cnt,                 /* count */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SGetPstMsgMult(cnt, mBuf)
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   Buffer *dbuf;            /* data buffer */
   S16 i;                   /* all purpose variable */
   S16 ret;                 /* return code */
   S16 endIdx;
   S16 dSize;
  
   TRC1(SGetPstMsgMult)
#if ( ERRCLASS & ERRCLS_INT_PAR )
   /* check message buffer */
   if (mBuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM101, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
   /* check count */
   if (cnt == 0)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM102, ERRZERO, "zero cnt");
      RETVALUE(RFAILED);
   }
#endif
   SGetEndIdx(DFLT_REGION, mBuf->t.msg.pool, &endIdx);
   SGetDBufSiz(DFLT_REGION, mBuf->t.msg.pool, &dSize);
   /* check if given message is not empty */
   if (mBuf->t.msg.msgLen)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      if (mBuf->t.msg.bufQ.dChn.prev == NULLP)
      {
         CMLOGERROR(ERRCLS_DEBUG, ECM103, ERRZERO, "Null buf");
         RETVALUE(RFAILED);
      }
#endif
      dbuf = mBuf->t.msg.bufQ.dChn.prev;
      i = endIdx - dbuf->t.dat.endIdx;
      if (i)
      {
         dbuf->t.dat.endIdx = endIdx;
         mBuf->t.msg.msgLen += i;
         cnt -= i;
      }
   }

   /* add full buffers to end of given message, if necessary */
   for (i = cnt / dSize; i; i--)
   {
      ret = cmInitDat('\0', DFLT_REGION, mBuf->t.msg.pool, PSTBUF, &dbuf);
      if (ret != ROK)
         RETVALUE(ret);
      SAddDBufPst(mBuf, dbuf);
      dbuf->t.dat.endIdx = endIdx;
   }

   /* add partial buffers, if necessary */
   i = cnt % dSize;
   if (i)
   {
      ret = cmInitDat('\0', DFLT_REGION, mBuf->t.msg.pool, PSTBUF, &dbuf);
      if (ret != ROK)
         RETVALUE(ret);
      SAddDBufPst(mBuf, dbuf);
      dbuf->t.dat.endIdx = i - 1;
   }
   mBuf->t.msg.msgLen += cnt;
   RETVALUE(ROK);
} /* end of SGetPstMsgMult */

  
/*
*
*       Fun:   SRemPreMsgMult
*
*       Desc:  This function copies and then removes consecutive bytes of
*              data from the beginning of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*              
*              if message is not empty: data is removed from front of
*              message, data is returned by destination pointer. message
*              length is decremented. return is ok.
*
*              the first byte of data read from the message will be placed 
*              in the destination buffer first (i.e. this was the first byte
*              of the message), the last byte of data read from the message
*              will be placed in the destination buffer last.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRemPreMsgMult
(
Data *dst,                  /* destination */
MsgLen cnt,                 /* count */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SRemPreMsgMult(dst, cnt, mBuf)
Data *dst;                  /* destination */
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   MsgLen msgLen;           /* message length */
   Buffer *tdbuf;           /* temporary data buffer */
   Buffer *dbuf;
   MsgLen tmpStrtIdx;       /* temporary start index */
   MsgLen tmpEndIdx;        /* temporary end index */
   MsgLen i;                /* count */
  
   TRC1(SRemPreMsgMult)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check destination */
   if (!dst)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM104, ERRZERO, "Null Ptr");
      RETVALUE(RFAILED);
   }
   /* check count */
   if (!cnt)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM105, ERRZERO, "zero cnt");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (!mBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM106, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif
   /* check message length */
   msgLen = mBuf->t.msg.msgLen;
   if (msgLen < 1 || cnt > msgLen)
   {
      /* message empty */
      RETVALUE(ROKDNA);
   }
   /* message not empty */
   tdbuf = mBuf->t.msg.bufQ.dChn.next;
#if (ERRCLASS & ERRCLS_DEBUG)
   if (tdbuf == NULLP)
   {
      CMLOGERROR(ERRCLS_DEBUG, ECM107, ERRZERO, "Null buf");
      RETVALUE(RFAILED);
   }
#endif
   tmpStrtIdx = tdbuf->t.dat.strtIdx;
   tmpEndIdx  = tdbuf->t.dat.endIdx;
   for (i = 0; i < cnt; i++)
   {
      /* check if not at end-of-buffer */
      if (tmpStrtIdx != tmpEndIdx)
      {
         /* end-of-buffer not reached */
         dst[i] = tdbuf->t.dat.data[tmpStrtIdx++];
         continue;
      }

      /* end-of-buffer reached */
      /* dequeue first buffer and put it away */
      dst[i] = tdbuf->t.dat.data[tmpStrtIdx];
      /* check if at end-of-message */
      SRemDBufPre(mBuf, &dbuf);
      SPutDBuf(DFLT_REGION, dbuf->t.dat.pool, dbuf);
      
      tdbuf = mBuf->t.msg.bufQ.dChn.next;
      if (tdbuf == NULLP)
         break;
      
      /* message not empty */
      /* get next data buffer */
      tmpStrtIdx = tdbuf->t.dat.strtIdx;
      tmpEndIdx = tdbuf->t.dat.endIdx;
   }
   if (tdbuf)
      tdbuf->t.dat.strtIdx = tmpStrtIdx;
   /* decrement message length */
   mBuf->t.msg.msgLen -= cnt;
   RETVALUE(ROK);
} /* end of SRemPreMsgMult */

  
/*
*
*       Fun:   SRemPstMsgMult
*
*       Desc:  This function copies and then removes consecutive bytes of
*              data from the end of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*              
*              if message is not empty: data is removed from front of
*              message, data is returned by destination pointer. message
*              length is decremented. return is ok.
*
*              the first byte of data read from the message will be placed 
*              in the destination buffer first (i.e. this was the last byte
*              of the message), the last byte of data read from the message
*              will be placed in the destination buffer last.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRemPstMsgMult
(
Data *dst,                  /* destination */
MsgLen cnt,                 /* count */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SRemPstMsgMult(dst, cnt, mBuf)
Data *dst;                  /* destination */
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   Buffer *dbuf;            /* data buffer */
   Buffer *tdbuf;           /* temporary data buffer */
   MsgLen tmpStrtIdx;       /* temporary start index */
   MsgLen tmpEndIdx;        /* temporary end index */
   S16 i;                   /* count */ 
   Bool empty;              /* empty */
   
   TRC1(SRemPstMsgMult)
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check destination */
   if (dst == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM108, ERRZERO, "Null Ptr");
      RETVALUE(RFAILED);
   }
   /* check count */
   if (cnt == 0)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM109, ERRZERO, "zero cnt");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (mBuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM110, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif
   /* check if message empty */
   if (!mBuf->t.msg.msgLen)
   {
      /* message empty */
      *dst = 0;
      RETVALUE(ROKDNA);
   }
   /* message not empty */
#if (ERRCLASS & ERRCLS_DEBUG)
   if (mBuf->t.msg.bufQ.dChn.prev == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM111, ERRZERO, "Null Ptr");
      RETVALUE(RFAILED);
   }
#endif
   tdbuf = mBuf->t.msg.bufQ.dChn.prev;
   tmpStrtIdx = tdbuf->t.dat.strtIdx;
   tmpEndIdx = tdbuf->t.dat.endIdx;
   empty = FALSE;
   for (i = 0; i < cnt; i++)
   {
      if (empty == TRUE)
      {
         /* message empty */
         *dst = 0;
         RETVALUE(ROKDNA);
      }
      /* check if data buffer empty */ 
      if (tmpStrtIdx == tmpEndIdx)
      {
         /* data buffer empty */
         dst[i] = tdbuf->t.dat.data[tmpEndIdx];
         /* decrement message length */
         mBuf->t.msg.msgLen--;
         SRemDBufPst(mBuf, &dbuf);
         SPutDBuf(DFLT_REGION, dbuf->t.dat.pool, dbuf);
         /* check if message empty */
         if (!mBuf->t.msg.msgLen)
         {
            /* message empty */
            empty =TRUE;
         }
         else
         {
            /* message not empty */
            /* get back data buffer */
#if (ERRCLASS & ERRCLS_DEBUG)
            if (mBuf->t.msg.bufQ.dChn.prev == NULLP)
            {
               CMLOGERROR(ERRCLS_DEBUG, ECM112, ERRZERO, "Null Ptr");
               RETVALUE(RFAILED);
            }
#endif
            tdbuf = mBuf->t.msg.bufQ.dChn.prev;
            tmpStrtIdx = tdbuf->t.dat.strtIdx;
            tmpEndIdx = tdbuf->t.dat.endIdx;
         }
      }
      else
      {
         /* data buffer not empty */
         dst[i] = tdbuf->t.dat.data[tmpEndIdx];
         /* decrement message length */
         mBuf->t.msg.msgLen--;
         tmpEndIdx--;
      }
   }
   tdbuf->t.dat.endIdx = tmpEndIdx;
   RETVALUE(ROK);
} /* end of SRemPstMsgMult */
  
  
/*
*
*       Fun:   SRepMsg
*
*       Desc:  This function replaces one byte of data in a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: index is 0 based and indicates location in message
*
*               if index is less than the length of the message:
*              data is replaced at specified index. message length
*              is unchanged. return is ok.
*
*              if index is greater than or equal to
*              the length of the message: message is unchanged.
*              return is ok, data not available.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRepMsg
(
Data data,                  /* data */
Buffer *mBuf,               /* message buffer */
MsgLen idx                  /* index */
)
#else
PUBLIC S16 SRepMsg(data, mBuf, idx)
Data data;                  /* data */
Buffer *mBuf;               /* message buffer */
MsgLen idx;                 /* index */
#endif
{
   MsgLen len1;             /* length 1 */
   MsgLen len2;             /* length 2 */
   MsgLen tidx;             /* temporary index */
   BufQLen i;                /* count */
   Buffer *tdbuf;           /* temporary data buffer */
  
   TRC1(SRepMsg)
#if ( ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM113, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif
   len1 = len2 = tidx = 0;
   tdbuf   = mBuf->t.msg.bufQ.dChn.next;
   for (i = 0; i < mBuf->t.msg.bufQ.crntSize; i++)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      if (tdbuf == NULLP)
      {
         CMLOGERROR(ERRCLS_DEBUG, ECM114, ERRZERO, "Null Ptr");
         RETVALUE(RFAILED);
      }
#endif
      len1 = len1 + (tdbuf->t.dat.endIdx - tdbuf->t.dat.strtIdx + 1);
      /* check if index within data buffer */
      if (len1 > idx)
      {
         /* index within data buffer */
         tidx = idx - len2 + tdbuf->t.dat.strtIdx;
         tdbuf->t.dat.data[tidx] = data;
         RETVALUE(ROK);
      }
      len2 = len1;
      tdbuf = tdbuf->dChn.next;
   }
   /* index not found */
   RETVALUE(ROKDNA);
} /* end of SRepMsg */

  
/*
*
*       Fun:   SExamMsg
*
*       Desc:  This function copies one byte of data from a message
*              without modifying the message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: index is 0 based and indicates location in message
*
*              if index is less than the length of the message:
*              message is unchanged and data is examined at specified
*              index and returned via pointer to data. message length
*              is unchanged. return is ok.
*
*              if index is greater than or equal to
*              the length of the message: message is unchanged and 0
*              is returned via pointer to data. return is ok, data
*              not available.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SExamMsg
(
Data *dataPtr,              /* pointer to data */
Buffer *mBuf,               /* message buffer */
MsgLen idx                  /* index */
)
#else
PUBLIC S16 SExamMsg(dataPtr, mBuf, idx)
Data *dataPtr;              /* pointer to data */
Buffer *mBuf;               /* message buffer */
MsgLen idx;                 /* index */
#endif
{
   REG1 MsgLen strtIdx;          /* start index */
   REG2 MsgLen endIdx;           /* end index */
   REG3 Buffer *tBuf;            /* temporary data buffer */
   REG4 QLen qLen;               /* buffer queue length */
  
   TRC1(SExamMsg)
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!dataPtr)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM115, ERRZERO, "Null data ptr");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if ((!mBuf) || ((S32)mBuf->t.msg.bufQ.crntSize < 0))
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM116, ERRZERO, "Check mBuf");
      RETVALUE(RFAILED);
   }
   /* check index */
   if (idx < 0)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM117, ERRZERO, "-ve index");
      RETVALUE(RFAILED);
   }
#endif
   /* check if anything queued */
   if(idx >= mBuf->t.msg.msgLen)
      RETVALUE(ROKDNA);

   /* message is not empty */
   qLen = SS_QLEN(&mBuf->t.msg.bufQ);
   strtIdx = 0;
   tBuf = mBuf->t.msg.bufQ.dChn.next;
#if (ERRCLASS & ERRCLS_DEBUG)
   if (tBuf == NULLP)
   {
      CMLOGERROR(ERRCLS_DEBUG, ECM118, ERRZERO, "Null buf");
      RETVALUE(RFAILED);
   }
#endif
   for (;qLen;qLen--)
   {
      endIdx = (tBuf->t.dat.endIdx - tBuf->t.dat.strtIdx) +1;
      /* check if index within data buffer */
      if (idx < strtIdx + endIdx)
      {
         *dataPtr = tBuf->t.dat.data[idx - strtIdx + tBuf->t.dat.strtIdx];
         RETVALUE(ROK);
      }

      strtIdx += endIdx;

      tBuf = tBuf->dChn.next;
#if (ERRCLASS & ERRCLS_DEBUG)
      if (tBuf == NULLP)
      {
         CMLOGERROR(ERRCLS_DEBUG, ECM119, ERRZERO, "Null buf");
         RETVALUE(RFAILED);
      }
#endif
   }
   RETVALUE(ROKDNA);
} /* end of SExamMsg */

  
/*
*
*       Fun:   SFndLenMsg
*
*       Desc:  This function determines the length of data within
*              a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: length of message is determined, message is unchanged
*              and length is returned via pointer to length. return is ok.
*              
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SFndLenMsg
(
REG1 Buffer *mBuf,          /* message buffer */
MsgLen *lngPtr              /* pointer to length */
)
#else
PUBLIC S16 SFndLenMsg(mBuf, lngPtr)
REG1 Buffer *mBuf;          /* message buffer */
MsgLen *lngPtr;             /* pointer to length */
#endif
{

   TRC1(SFndLenMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM120, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
   /* check length pointer */
   if (lngPtr == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM121, ERRZERO, "Null len Ptr");
      RETVALUE(RFAILED);
   }
#endif
   *lngPtr = mBuf->t.msg.msgLen;
   RETVALUE(ROK);
} /* end of SFndLenMsg */

  
/*
*
*       Fun:   SCatMsg
*
*       Desc:  This function will concatenate the two specified messages
*              into one message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: if order equal M1M2: all data attached to message 2 is
*              moved to the end of message 1. message 2 is set to empty.
*              message 1 length is increased by length of message 2.
*              message 2 length is set to zero. message 2 is not returned
*              to memory. return is ok.
*
*              if order equal M2M1: all data attached to message 2 is
*              moved to the front of message 1. message 2 is set to empty.
*              message 1 length is increased by length of message 2.
*              message 2 length is set to zero. message 2 is not returned
*              to memory. return is ok.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SCatMsg
(
Buffer *mBuf1,              /* message 1 */
Buffer *mBuf2,              /* message 2 */
Order order                 /* order */
)
#else
PUBLIC S16 SCatMsg(mBuf1, mBuf2, order)
Buffer *mBuf1;              /* message 1 */
Buffer *mBuf2;              /* message 2 */
Order order;                /* order */
#endif
{
   Queue *bufQ1;                /* buffer queue 1 */
   Queue *bufQ2;                /* buffer queue 2 */
  
   TRC1(SCatMsg)
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer 1 */
   if (mBuf1 == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM122, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
   /* check message buffer 2 */
   if (mBuf2 == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM123, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif
   bufQ1 = &mBuf1->t.msg.bufQ;
   bufQ2 = &mBuf2->t.msg.bufQ;
   switch (order)
   {
      case M1M2:
         /* place message 1 in front of message 2 */
         SCatQueue(bufQ1, bufQ2, Q1Q2);
         /* add message 2 length to message 1 length */
         mBuf1->t.msg.msgLen += mBuf2->t.msg.msgLen;
         /* set message 2 length to 0 */
         mBuf2->t.msg.msgLen = 0;
         break;
      case M2M1:
         /* place message 2 in front of message 1 */
         SCatQueue(bufQ1, bufQ2, Q2Q1);
         /* add message 2 length to message 1 length */
         mBuf1->t.msg.msgLen += mBuf2->t.msg.msgLen;
         /* set message 2 length to 0 */
         mBuf2->t.msg.msgLen = 0;
         break;
      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         CMLOGERROR(ERRCLS_DEBUG, ECM124, ERRZERO, "Wrong Order");
#endif /* ERRCLASS */
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
} /* end of SCatMsg */

  
/*
*
*       Fun:   SSegMsg
*
*       Desc:  This function will segment one specified message into two
*              messages.
*
*       Ret:   ROK     - ok
*              ROKDNA  - ok, data not available
*              RFAILED - failed, general (optional)
*              ROUTRES - failed, out of resources (optional)
*
*       Notes: message 1 is the original message.
*
*              message 2 is the new message.
*
*              index is 0 based and indicates location in message 1
*              from which message 2 will be created.
*
*              if index is equal to 0: message 2 is created and all data
*              attached to message 1 is moved to message 2. message 1
*              is not returned to memory. return is ok.
*
*              if index is not equal to 0 and less than the length of
*              the message minus 1: message 2 is created, all data
*              attached to message 1 from index (inclusive) is moved to
*              message 2. message 1 contains data from index 0 to index
*              minus 1. return is ok.
*
*              if index is not equal to 0 and greater than or equal to
*              the length of the message minus 1: message 1 is unchanged.
*              message 2 is set to null. return is ok, data not available.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SSegMsg
(
Buffer *mBuf1,              /* message 1 */
MsgLen idx,                 /* index */
Buffer **mBuf2              /* message 2 */
)
#else
PUBLIC S16 SSegMsg(mBuf1, idx, mBuf2)
Buffer *mBuf1;              /* message 1 */
MsgLen idx;                 /* index */
Buffer **mBuf2;             /* message 2 */
#endif
{
   MsgLen len1;             /* length 1 */
   MsgLen len2;             /* length 2 */
   U16 i;                   /* count */
   S16 j;                   /* count */
   Buffer *tdbuf;           /* temporary data buffer */
   Buffer *tmbuf;           /* temporary message buffer */
   Buffer *dbuf;            /* data buffer */
   Buffer *tdbuf2;          /* temporary data buffer */
   Buffer *tdbuf3;          /* temporary data buffer */
   MsgLen tidx;             /* temporary index */
   BufQLen bufQLen1;        /* buffer queue length */
   BufQLen bufQLen2;        /* buffer queue length */
   Bool found;              /* found */
   S16 ret;                 /* return code */
   MsgLen msgLen;           /* length of message */
   S16 strtIdx;
 
 
 
   TRC1(SSegMsg)
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer 1 */
   if (mBuf1 == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM167, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
   /* check message buffer 2 */
   if (mBuf2 == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM168, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif
   /* check if index 0 */
   if (idx == 0)
   {
      /* index 0 */
      ret = SGetMsg(DFLT_REGION, mBuf1->t.msg.pool, &tmbuf);
      if (ret != ROK)
         RETVALUE(ret);
      SCatQueue(&tmbuf->t.msg.bufQ, &mBuf1->t.msg.bufQ, Q1Q2);
      *mBuf2 = tmbuf;
      (*mBuf2)->t.msg.msgLen = mBuf1->t.msg.msgLen;
      mBuf1->t.msg.msgLen = 0;
      RETVALUE(ROK);
   }
 
   /* index not 0 */
 
   /* check if index is >= to the length of the message minus 1 */
   msgLen = SS_MLEN(mBuf1);
   if(idx > msgLen - 1)
   {
      *mBuf2 = NULLP;
      RETVALUE(ROKDNA);
   }
 
   /* index is less than to the length of the message minus 1 */
   len1 = len2 = 0;
   tidx = 0;
   bufQLen1 = SS_QLEN(&mBuf1->t.msg.bufQ);
   bufQLen2 = 0;
   found = FALSE;
   tdbuf = mBuf1->t.msg.bufQ.dChn.next;
   for (i = 0; i < bufQLen1; i++)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      if (tdbuf == NULLP)
      {
         CMLOGERROR(ERRCLS_DEBUG, ECM169, ERRZERO, "Null buf");
         RETVALUE(RFAILED);
      }
#endif
      
      bufQLen2++;
      len1 = len1 + (tdbuf->t.dat.endIdx - tdbuf->t.dat.strtIdx + 1);
      /* check if index within data buffer */
      if (len1 > idx)
      {
         /* index within data buffer */
         tidx = idx - len2 + tdbuf->t.dat.strtIdx;
         found = TRUE;
         break;
      }
      len2 = len1;
      tdbuf = tdbuf->dChn.next;
  }
 
   /* check if index found */
   if (!found)
   {
      /* index not found */
      *mBuf2 = NULLP;
      RETVALUE(ROKDNA);
   }
 
   /* index found */
   ret = SGetMsg(DFLT_REGION, mBuf1->t.msg.pool, &tmbuf);
   if (ret != ROK)
      RETVALUE(ret);
 
   /* check if beginning of data buffer */
   SGetStrtIdx(DFLT_REGION, mBuf1->t.msg.pool, &strtIdx);
   if (tidx == (MsgLen) strtIdx)
   {
      /* beginning of data buffer */
#if (ERRCLASS & ERRCLS_DEBUG)
      if (tdbuf->dChn.prev == NULLP)
      {
         CMLOGERROR(ERRCLS_DEBUG, ECM170, ERRZERO, "Null buf");
         RETVALUE(RFAILED);
      }
#endif
      tdbuf2 = tdbuf->dChn.prev;
#if (ERRCLASS & ERRCLS_DEBUG)
      if (mBuf1->t.msg.bufQ.dChn.prev == NULLP)
      {
         CMLOGERROR(ERRCLS_DEBUG, ECM171, ERRZERO, "Null prev buf");
         RETVALUE(RFAILED);
      }
#endif
      tdbuf3 = mBuf1->t.msg.bufQ.dChn.prev;
 
      mBuf1->t.msg.bufQ.dChn.prev = tdbuf2;
      mBuf1->t.msg.bufQ.crntSize = bufQLen2 - 1;
      tdbuf2->dChn.next = NULLP;
 
      tmbuf->t.msg.bufQ.dChn.prev = tdbuf3;
      tdbuf3->dChn.next = NULLP;
      tmbuf->t.msg.bufQ.crntSize = bufQLen1 - bufQLen2 + 1;
      tmbuf->t.msg.bufQ.dChn.next = tdbuf;
      tdbuf->dChn.prev = NULLP;
   }
   else
   {
      /* not beginning of data buffer */
      ret = cmInitDat( tdbuf->t.dat.data[tidx], DFLT_REGION, mBuf1->t.msg.pool, PSTBUF, &dbuf);
      if (ret != ROK)
         RETVALUE(ret);
      SAddDBufPst(tmbuf, dbuf);
      i = tidx + 1;
      j = strtIdx + 1;
      for (; i <= tdbuf->t.dat.endIdx; i++, j++)
         dbuf->t.dat.data[j] = tdbuf->t.dat.data[i];
      dbuf->t.dat.endIdx = j - 1;
 
      if (tdbuf->dChn.next == NULLP)
      {
         /* update mBuf1 */
         mBuf1->t.msg.msgLen = idx;
         tdbuf->t.dat.endIdx = tidx - 1;
 
         /* update mBuf2 */
         tmbuf->t.msg.msgLen = len1 - idx;
         *mBuf2 = tmbuf;
         RETVALUE(ROK);
      }
      tdbuf2 = tdbuf->dChn.next;
#if (ERRCLASS & ERRCLS_DEBUG)
      if (mBuf1->t.msg.bufQ.dChn.prev == NULLP)
      {
         CMLOGERROR(ERRCLS_DEBUG, ECM172, ERRZERO, "Null prev buf");
         RETVALUE(RFAILED);
      }
#endif
      tdbuf3 = mBuf1->t.msg.bufQ.dChn.prev;
      tdbuf->t.dat.endIdx = tidx - 1;
      mBuf1->t.msg.bufQ.dChn.prev = tdbuf;
      mBuf1->t.msg.bufQ.crntSize = bufQLen2;
      tdbuf->dChn.next = NULLP;
 
      if (bufQLen1 != bufQLen2)
      {
         tmbuf->t.msg.bufQ.dChn.prev = tdbuf3;
         tmbuf->t.msg.bufQ.crntSize = bufQLen1 - bufQLen2 + 1;
         dbuf->dChn.next = tdbuf2;
         tdbuf2->dChn.prev = dbuf;
         tdbuf3->dChn.next = NULLP;
      }
   }
   *mBuf2 = tmbuf;
   (*mBuf2)->t.msg.msgLen = mBuf1->t.msg.msgLen - idx;
   mBuf1->t.msg.msgLen = idx;
   RETVALUE(ROK);
} /* end of SSegMsg */

  
/*
*
*       Fun:   SCpyMsgFix
*
*       Desc:  This function copies data from a message
*              into a fixed buffer.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: None
*
*       File:  cm_ss.c
*
*/

#ifdef ANSI
PUBLIC S16 SCpyMsgFix
(
Buffer *srcMbuf,            /* source message buffer */
MsgLen srcIdx,              /* source index */
MsgLen cnt,                 /* count */
Data *dstBuf,               /* destination buffer */
MsgLen *cCnt                /* copied count */
)
#else
PUBLIC S16 SCpyMsgFix(srcMbuf, srcIdx, cnt, dstBuf, cCnt)
Buffer *srcMbuf;            /* source message buffer */
MsgLen srcIdx;              /* source index */
MsgLen cnt;                 /* count */
Data *dstBuf;               /* destination buffer */
MsgLen *cCnt;               /* copied count */
#endif
{
   REG1 U16 i;               /* counter */
   REG2 S16 curIdx;          /* current index */
   REG3 S16 j;               /* counter */
   REG4 S16 nBytes;          /* nBytes */
   Data *srcPtr;             /* source pointer */
   Data *dstPtr;             /*  */
   Buffer *dBuf;
#if (ERRCLASS & ERRCLS_INT_PAR)
   MsgLen mLen;              /* message length */
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

  
   TRC1(SCpyMsgFix)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check source message buffer */
   if (srcMbuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM131, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
   /* check destination message buffer */
   if (dstBuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM132, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }

   /* make sure srcIdx and cnt are in bounds */
   mLen = srcMbuf->t.msg.msgLen;
   if (srcIdx > mLen)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM133, ERRZERO, "Wrong srcIdx");
      RETVALUE(RFAILED);
   }

   if (cnt < 0)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM134, ERRZERO, "Wrong cnt");
      RETVALUE(RFAILED);
   }

   if (srcIdx < 0)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM135, ERRZERO, "-ve srcIdx");
      RETVALUE(RFAILED);
   }

   if ((srcIdx + cnt) > mLen)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM136, ERRZERO, "srcIdx+cnt > mLen");
      RETVALUE(RFAILED);
   }
      
#endif /* ERRCLASS */

   /* initialize */

   /* 
    * get the first dbuf
    */
   dBuf = srcMbuf->t.msg.bufQ.dChn.next;
   /* 
    * dstPtr points to beginning of dstBuf 
    */
   dstPtr = dstBuf;

   /* 
    * zero out these counters 
    */
   *cCnt = 0;                   /* return val */
   curIdx = 0;                  /* current index */
   nBytes = 0;                  /* n bytes */
   
   /*
    * foreach dBuf in chain
    */
   for (i = 0; i < srcMbuf->t.msg.bufQ.crntSize; i++)
   {
      /* 
       * source pointer starts at strtIdx 
       */
      srcPtr = &dBuf->t.dat.data[dBuf->t.dat.strtIdx];
    
      /*
       * loop through data
       */
      for (j = dBuf->t.dat.strtIdx; j <= dBuf->t.dat.endIdx; j++)
      {
         /*
          * if we haven't reached the starting index yet,
          * increment what we must, and continue
          */
         if (curIdx < srcIdx)
         {
            curIdx++;
            srcPtr++;
            continue;
         }
         
         /* copy the bytes */
         *dstPtr++ = *srcPtr++;
         nBytes++;

         /*
          * if the current index is equal the requested count
          * we're done
          */
         if (nBytes == cnt)
         {
            *cCnt = nBytes;
            RETVALUE(ROK);
         }
      }
      dBuf = dBuf->dChn.next;
      srcPtr = &dBuf->t.dat.data[dBuf->t.dat.strtIdx];
   }

   if (nBytes != cnt)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      CMLOGERROR(ERRCLS_DEBUG, ECM137, ERRZERO, "nBytes != cnt");
#endif /* ERRCLASS */
      RETVALUE(RFAILED);
   }
   
   *cCnt = nBytes;

   RETVALUE(ROK);
} /* end of SCpyMsgFix */

  
/*
*
*       Fun:   SCpyFixMsg
*
*       Desc:  This function copies data from a fixed buffer to a
*              message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: None
*
*       File:  cm_ss.c
*
*/

#ifdef ANSI
PUBLIC S16 SCpyFixMsg
(
Data *srcBuf,               /* source buffer */
Buffer *dstMbuf,            /* destination message buffer */
MsgLen dstIdx,              /* destination index */
MsgLen cnt,                 /* count */
MsgLen *cCnt                /* copied count */
)
#else
PUBLIC S16 SCpyFixMsg(srcBuf, dstMbuf, dstIdx, cnt, cCnt)
Data *srcBuf;               /* source buffer */
Buffer *dstMbuf;            /* destination message buffer */
MsgLen dstIdx;              /* destination index */
MsgLen cnt;                 /* count */
MsgLen *cCnt;               /* copied count */
#endif
{
   Buffer *right;           /* right buffer */
   S16 ret;
  
   TRC1(SCpyFixMsg)
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check source message buffer */
   if (srcBuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM138, ERRZERO, "Null srcBuf");
      RETVALUE(RFAILED);
   }
   /* check destination message buffer */
   if (dstMbuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM138, ERRZERO, "Null dstBuf");
      RETVALUE(RFAILED);
   }
#endif
   if (dstIdx == 0)  /* prepend data buffer */
   {
      SAddPreMsgMult(srcBuf, cnt, dstMbuf);
      /* update count */
      *cCnt = cnt;
      RETVALUE(ROK);
   }
 
   /* segment message at index */
   if ((ret = SSegMsg(dstMbuf, dstIdx, &right)) == ROKDNA)
   {
      *cCnt = 0;
      return (ret);
   }
 
   /* postpend  buffer at index */
   SAddPstMsgMult(srcBuf, cnt, dstMbuf);

   /* cat them back together */
   SCatMsg(dstMbuf, right, M1M2);
   /* return right to message pool */
   SPutMsg(right);
   /* update count */
   *cCnt = cnt;
 
   RETVALUE(ROK);
} /* end of SCpyFixMsg */


  
/*
*
*       Fun:   SCpyMsgMsg
*
*       Desc:  This function is used to copy a message into
*              a new region and or pool of memory.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SCpyMsgMsg
(
Buffer *srcBuf,                   /* source message */
Region dstRegion,                 /* destination region */
Pool dstPool,                     /* destination pool */
Buffer **dstBuf                   /* pointer to destination message */
)
#else
PUBLIC S16 SCpyMsgMsg(srcBuf, dstRegion, dstPool, dstBuf)
Buffer *srcBuf;                   /* source message */
Region dstRegion;                 /* destination region */
Pool dstPool;                     /* destination pool */
Buffer **dstBuf;                  /* pointer to destination message */
#endif
{
   BufQLen size;                  /* current size */
   MsgLen i;                      /* counter */
   Buffer *dBuf;                  /* destination buffer */
   Buffer *sBuf;                  /* source buffer */
   S16 ret;                       /* return code */
  
   TRC1(SCpyMsgMsg)

   ret = SGetMsg(dstRegion,dstPool,dstBuf);
   if (ret != ROK)
   {
      RETVALUE(ret);
   }
   /* initialize destination buffer queue */
   SS_INITQUE(&(*dstBuf)->t.msg.bufQ);
   

   /* initialize variables to read source buffer queue */
   size = SS_QLEN(&srcBuf->t.msg.bufQ);
   sBuf =  srcBuf->t.msg.bufQ.dChn.next;

   /* copy data from source to destination message */
   for(; size; size--)
   {
      ret = SGetDBuf(dstRegion, dstPool, &dBuf);
      if (ret != ROK)
      {
         SPutMsg(*dstBuf);
         RETVALUE(ret);
      }
      /* initialize chain pointer of data buffer */
      SS_INITDCHN(&dBuf->dChn);

      SAddDBufPst(*dstBuf, dBuf);

      /* fetch next source buffer */
#if (ERRCLASS & ERRCLS_DEBUG)
      if (sBuf == NULLP)
      {
         SPutMsg(*dstBuf);
         CMLOGERROR(ERRCLS_DEBUG, ECM142, ERRZERO, "Null buf");
         RETVALUE(RFAILED);
      }
#endif
      dBuf->t.dat.strtIdx = sBuf->t.dat.strtIdx;
      dBuf->t.dat.endIdx  = sBuf->t.dat.endIdx;
      for(i=sBuf->t.dat.strtIdx;i<=sBuf->t.dat.endIdx;i++)
         dBuf->t.dat.data[i] = sBuf->t.dat.data[i];
      sBuf = sBuf->dChn.next;
   } 

   (*dstBuf)->bufType      = srcBuf->bufType;
   (*dstBuf)->t.msg.msgLen = srcBuf->t.msg.msgLen;

   RETVALUE(ROK);
} /* end of SCpyMsgMsg */


/*
*
*       Fun:   SCompressMsg
*
*       Desc:  This function is used to compress a message into
*              the minimum number of data buffers needed.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SCompressMsg
(
Buffer *mBuf                     /* message buffer */
)
#else
PUBLIC S16 SCompressMsg(mBuf)
Buffer *mBuf;                    /* message buffer */
#endif
{
   Buffer *srcBuf;               /* source buffer */
   Data *srcGet;                 /* source get pointer */
   Data *srcEnd;                 /* source end pointer */

   Buffer *dstBuf;               /* destination buffer */
   Data *dstPut;                 /* destination put pointer */
   Data *dstEnd;                 /* destination end pointer */

   MsgLen ithByte;               /* i-th byte of message */
   MsgLen msgLen;                /* length of message */
   BufQLen bufQLen;              /* buffer queue length */
   BufQLen n;                    /* loop control variable */
   S16 ret;                      /* return value from system service calls */
   
   TRC1(SCompressMsg)
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check for null message */
   if (!mBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM173, ERRZERO, "Null Ptr Passed");
      RETVALUE(RFAILED);
   }
#endif
   /* check if message empty */
   msgLen = SS_MLEN(mBuf);

   if(!msgLen)
      RETVALUE(ROK);

   /* since msgLen > 0, the msg requires at least one data buffer */
   n = 1;

   /* initialize the source buffer control variables */
#if (ERRCLASS & ERRCLS_DEBUG)
   if (mBuf->t.msg.bufQ.dChn.next == NULLP)
   {
      CMLOGERROR(ERRCLS_DEBUG, ECM174, ERRZERO, "mbuf Length is not okay");
      RETVALUE(RFAILED);
   }
#endif

   srcBuf = mBuf->t.msg.bufQ.dChn.next;
   srcGet = srcBuf->t.dat.data + srcBuf->t.dat.strtIdx;
   srcEnd = srcBuf->t.dat.data + srcBuf->t.dat.endIdx;
   /* initialize the destination buffer control variables */
   dstBuf = srcBuf;
   dstPut = dstBuf->t.dat.data + DSTRTIDX;
   dstEnd = dstBuf->t.dat.data + DENDIDX;

   /* adjust data to start on "DSTRTIDX" */
   for(ithByte = 0; ithByte < msgLen; ithByte++)
   {
      /* copy one byte of data */
      *dstPut = *srcGet;

      /* fetch next source buffer if at end-of-buffer */
      if( srcGet == srcEnd && srcBuf->dChn.next != NULLP)
      {
         srcBuf = srcBuf->dChn.next;
         srcGet = srcBuf->t.dat.data + srcBuf->t.dat.strtIdx;
         srcEnd = srcBuf->t.dat.data + srcBuf->t.dat.endIdx;
      }
      else
      {
         srcGet++;
      }

      /* fetch next destination buffer if at end-of-buffer */
      if( dstPut == dstEnd && dstBuf->dChn.next != NULLP)
      {
         dstBuf->t.dat.strtIdx = DSTRTIDX;
         dstBuf->t.dat.endIdx  = DENDIDX;
         dstBuf = dstBuf->dChn.next;
         dstPut = dstBuf->t.dat.data + DSTRTIDX;
         dstEnd = dstBuf->t.dat.data + DENDIDX;
         if(ithByte < (msgLen - 1))
         {
            n++;
         }
      }
      else
      {
         dstPut++;
      }
   } 

   /* adjust indices in last data buffer */
   dstBuf->t.dat.strtIdx = DSTRTIDX;
   dstBuf->t.dat.endIdx  = DSTRTIDX + ((msgLen-1) % DSIZE);

   /* put away extra source buffers */
   bufQLen = SS_QLEN(&mBuf->t.msg.bufQ);
   for(n = bufQLen - n; n; n--)
   {
      ret = SRemDBufPst(mBuf, &srcBuf);
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         CMLOGERROR(ERRCLS_DEBUG, ECM175, (ErrVal)ret, "SRemDBufPst failed");
#endif
         RETVALUE(ret);
      }
#if (ERRCLASS & ERRCLS_DEBUG)
      ret = SPutDBuf(DFLT_REGION, DFLT_POOL, srcBuf);
      if (ret != ROK)
      {
         CMLOGERROR(ERRCLS_DEBUG, ECM176, (ErrVal)ret, "SPutDBuf failed");
         RETVALUE(ret);
      }
#else
      SPutDBuf(DFLT_REGION, DFLT_POOL, srcBuf);
#endif
   }
   RETVALUE(ROK);
}  /* end of SCompressMsg */

  
/*
*
*       Fun:   SGetSysTime
*
*       Desc:  This function is used to determine the system
*              time. This information may be used for
*              some management functions.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: None
*
*       File:  cm_ss.c
*
*/
  
  
/*
*
*       Fun:   SRegInit
*
*       Desc:  This function is used to register an initialization function
*              for the layer. The system services will invoke the function
*              passed to it one time. The initialization function will be
*              used by the layer to initilize the layer.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: None
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRegInit
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
PAIFS16 initFnct            /* initialization function, */
                            /* typically SActvInit */
)
#else
PUBLIC S16 SRegInit(ent, inst, initFnct)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
PAIFS16 initFnct;           /* initialization function, */
                            /* typically SActvInit */
#endif
{
#ifdef MSDBG2
   Txt prntBuf[PRNTSZE];    /* data buffer */
#endif
 
   TRC1(SRegInit)
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check initialization function */
   if (initFnct == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM143, ERRZERO, "initFnct Null");
      RETVALUE(RFAILED);
   }
#endif

   /* activate initialization function */
   (Void) (*initFnct)(ent, inst, DFLT_REGION, PWR_UP);

#ifdef MSDBG2
   sprintf(prntBuf,"%s: registered init tsk for entity: %02d inst: %02d\n",
   msPrgNme, ent, inst);
   SDisplay(0, prntBuf);
#endif
   RETVALUE(ROK);
} /* end of SRegInit */

  
  
/*
*
*       Fun:   SAddDBufPre
*
*       Desc:  This function queues a data buffer to the
*              front of the specified message buffer.
*
*       Ret:   ROK     - ok
*              RFAILED - failed, general (optional)
*
*       Notes: if buffer queue is empty: buffer is placed in the queue. queue
*              length is incremented.
*              
*              if buffer queue is not empty: buffer is placed in front of all
*              other buffers in queue. queue length is incremented.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SAddDBufPre
(
Buffer *mBuf,                   /* message buffer */
Buffer *dBuf                    /* data buffer */
)
#else
PUBLIC INLINE S16 SAddDBufPre(mBuf, dBuf)
Buffer *mBuf;                    /* message buffer */
Buffer *dBuf;                   /* data buffer */
#endif
{
   TRC1(SAddDBufPre)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer queue */
   if (!mBuf || !dBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM144, ERRZERO, "Null mBuf/dBuf");
      RETVALUE(RFAILED);
   }
#endif
   dBuf->bufType = BDATA;
   RETVALUE(SQueueFirst(dBuf, &mBuf->t.msg.bufQ));

} /* end of SAddDBufPre */

  
/*
*
*       Fun:   SAddDBufPst
*
*       Desc:  This function queues a data buffer to the
*              back of the specified message buffer .
*
*       Ret:   ROK     - ok
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: buffer is placed in the queue.
*              queue length is incremented.
*              
*              if queue is not empty: buffer is placed behind all
*              other buffers in queue. queue length is incremented.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SAddDBufPst
(
Buffer *mBuf,                   /* message buffer */
Buffer *dBuf                    /* data buffer */
)
#else
PUBLIC INLINE S16 SAddDBufPst(mBuf, dBuf)
Buffer *mBuf;                   /* message buffer */
Buffer *dBuf;                   /* data buffer */
#endif
{

   TRC1(SAddDBufPst)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer queue */
   if (!mBuf || !dBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM145, ERRZERO, "Null mBuf/dBuf");
      RETVALUE(RFAILED);
   }
#endif
   dBuf->bufType = BDATA;
   RETVALUE(SQueueLast(dBuf, &mBuf->t.msg.bufQ));
   
} /* end of SAddDBufPst */

  
/*
*
*       Fun:   SRemDBufPre
*
*       Desc:  This function dequeues a data buffer from
*              the front of the specified message buffer.
*
*       Ret:   ROK     - ok
*              ROKDNA  - ok, data not available
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*              
*              if queue is not empty: pointer to buffer is set to first
*              buffer in queue, first buffer in queue is removed and
*              return is ok. queue length is decremented.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SRemDBufPre
(
Buffer *mBuf,                   /* message buffer */
Buffer **dBufPtr                /* pointer to data buffer */
)
#else
PUBLIC INLINE S16 SRemDBufPre(mBuf, dBufPtr)
Buffer *mBuf;                   /* message buffer */
Buffer **dBufPtr;               /* pointer to data buffer */
#endif
{
   TRC1(SRemDBufPre)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (dBufPtr == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM146, ERRZERO, "Null Buf Ptr");
      RETVALUE(RFAILED);
   }
   /* check queue */
   if (mBuf == NULLP)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM147, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE(SDequeueFirst(dBufPtr, &mBuf->t.msg.bufQ));
   
} /* end of SRemDBufPre */

  
/*
*
*       Fun:   SRemDBufPst
*
*       Desc:  This function dequeues a data or message buffer from the
*              back of the specified message buffer.
*
*       Ret:   ROK     - ok
*              ROKDNA  - ok, data not available
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*              
*              if queue is not empty: pointer to buffer is set to last
*              buffer in queue, last buffer in queue is removed and
*              return is ok. queue length is decremented.
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SRemDBufPst
(
Buffer *mBuf,                   /* message buffer */
Buffer **dBufPtr                /* pointer to data buffer */
)
#else
PUBLIC INLINE S16 SRemDBufPst(mBuf, dBufPtr)
Buffer *mBuf;                   /* message buffer */
Buffer **dBufPtr;               /* pointer to data buffer */
#endif
{

   TRC1(SRemDBufPst)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (!dBufPtr)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM148, ERRZERO, "Null Buf Ptr");
      RETVALUE(RFAILED);
   }
   /* check message */
   if (!mBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM149, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE(SDequeueLast(dBufPtr, &mBuf->t.msg.bufQ));
   
} /* end of SRemDBufPst */


/*
*
*       Fun:   SInitNxtDBuf
*
*       Desc:  Initialize next Data Buffer Id
*
*       Ret:   ROK/RFAILED
*
*       Notes: Must be called prior to SGetNxtDBuf
*
*       File:  cm_ss.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SInitNxtDBuf
(
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC INLINE S16 SInitNxtDBuf(mBuf)
Buffer *mBuf;                   /* message buffer */
#endif
{
 
   TRC1(SInitNxtDBuf)
 
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!mBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM150, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif
   mBuf->t.msg.nxtDBuf = mBuf->t.msg.bufQ.dChn.next;
 
   RETVALUE(ROK);
} /* end of SInitNxtDBuf */


/*
*
*       Fun:   SGetNxtDBuf
*
*       Desc:  Get next dBuf in message chain
*
*       Ret:   ROK/RFAILED
*
*       Notes: Must be called after SInitNxtDBuf
*
*       File:  cm_ss.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SGetNxtDBuf
(
Buffer *mBuf,                   /* message buffer */
Buffer **dBuf                   /* data buffer return */
)
#else
PUBLIC INLINE S16 SGetNxtDBuf(mBuf, dBuf)
Buffer *mBuf;                   /* message buffer */
Buffer **dBuf;                  /* data buffer return */
#endif
{
   TRC1(SGetNxtDBuf)
   
#if (ERRCLASS & ERRCLASS_INT_PAR)
   if (!mBuf || !dBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM152, ERRZERO, "Null mBuf/dBuf");
      RETVALUE(RFAILED);
   }
#endif

   if (mBuf->t.msg.nxtDBuf == NULLP)
   {
      *dBuf = (Buffer*)NULLP;
      RETVALUE(ROKDNA);
   }
   
   /* get next data buffer */
   *dBuf = mBuf->t.msg.nxtDBuf;
   /* update next data buffer */
   mBuf->t.msg.nxtDBuf = (*dBuf)->dChn.next;
   

   RETVALUE(ROK);
} /* end of SGetNxtDBuf */


/*
*
*       Fun:   SAlignDBufEven
*
*       Desc:  align data portion of a data buffer on an even
*              byte boundary.
*
*       Ret:   ROK/RFAILED
*
*       Notes: required for SS7 microcode on the 68302
*
*       File:  cm_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SAlignDBufEven
(
Buffer *dBuf                      /* data buffer */
)
#else
PUBLIC S16 SAlignDBufEven(dBuf)
Buffer *dBuf;                   /* data buffer  */
#endif
{
   REG1 Data *src;
   REG2 Data *dst;
#if (ERRCLASS & ERRCLS_DEBUG)
   S16 strtIdx;
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   TRC1(SAlignDBufEven)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!dBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM153, ERRZERO, "Null dBuf");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS */

   src = &dBuf->t.dat.data[dBuf->t.dat.strtIdx];

   if (!((U32)src % (U32)2))
      RETVALUE(ROK);            /* we're already even */

#if (ERRCLASS & ERRCLS_DEBUG)
   SGetStrtIdx(DFLT_REGION, dBuf->t.dat.pool, &strtIdx);
   if (dBuf->t.dat.strtIdx <= strtIdx)
   {
      /* no room to shift bytes */
      CMLOGERROR(ERRCLS_DEBUG, ECM154, ERRZERO, "can't shift bytes");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS  */

   for (dst = (src - 1); src <= &dBuf->t.dat.data[dBuf->t.dat.endIdx];)
      *dst++ = *src++;
   
   /* subtract one for each index */
   dBuf->t.dat.strtIdx--;
   dBuf->t.dat.endIdx--;
   
   RETVALUE(ROK);
} /* end of SAlignDBufEven */


/*
*
*       Fun:   SGetDataRx
*
*       Desc:  Given a data buffer, return a pointer to the
*              data payload, and the length of the payload
*
*
*       Ret:   ROK ok
*              RFAILED error
*
*       Notes: This assumes an uninitialized dBuf
*
*       File:  cm_ss.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SGetDataRx
(
Buffer *dBuf,                   /* data buffer */
MsgLen pad,                     /* pad */
Data **retDatPtr,               /* return data pointer */
MsgLen *retDatLen               /* return data length */
)
#else
PUBLIC INLINE S16 SGetDataRx(dBuf, pad, retDatPtr, retDatLen)
Buffer *dBuf;                   /* data buffer */
MsgLen pad;                     /* pad */
Data **retDatPtr;               /* return data pointer */
MsgLen *retDatLen;              /* return data length */
#endif
{
   S16 idx;
   S16 dSize;
 
   TRC1(SGetDataRx)
   
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!dBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM159, ERRZERO, "Null dBuf");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS */
 
   dBuf->bufType = BDATA;

   SGetStrtIdx(DFLT_REGION, dBuf->t.dat.pool,  &idx);
   SGetDBufSiz(DFLT_REGION, dBuf->t.dat.pool, &dSize);
   dBuf->t.dat.strtIdx = idx + pad;
   dBuf->t.dat.size = dSize;
 
   *retDatPtr = &dBuf->t.dat.data[dBuf->t.dat.strtIdx];
   *retDatLen = dBuf->t.dat.size - dBuf->t.dat.strtIdx;
 
   RETVALUE(ROK);
} /* end of SGetDataRx */
 

/*
*
*       Fun:   SGetDataTx
*
*       Desc:  Given a data buffer, return a pointer to the
*              data payload, and the length of the payload
*
*
*       Ret:   ROK ok
*              RFAILED error
*
*       Notes: This assumes an initialized dBuf
*
*       File:  cm_ss.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SGetDataTx
(
Buffer *dBuf,                   /* data buffer */
Data **retDatPtr,               /* return data pointer */
MsgLen *retDatLen               /* return data length */
)
#else
PUBLIC INLINE S16 SGetDataTx(dBuf, retDatPtr, retDatLen)
Buffer *dBuf;                   /* data buffer */
Data **retDatPtr;               /* return data pointer */
MsgLen *retDatLen;              /* return data length */
#endif
{
 
   TRC1(SGetDataTx)
  
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!dBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM160, ERRZERO, "Null dBuf");
      RETVALUE(RFAILED);
   }
#endif
 
 
   *retDatPtr = &dBuf->t.dat.data[dBuf->t.dat.strtIdx];
   *retDatLen = dBuf->t.dat.endIdx - dBuf->t.dat.strtIdx +1;
 
   RETVALUE(ROK);
 
} /* end of SGetDataTx */
 

/*
*
*       Fun:   SUpdMsg
*
*       Desc:  Update a message with a new dBuf
*
*       Ret:   ROK/RFAILED
*
*       Notes:
*
*       File:  cm_ss.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SUpdMsg
(
Buffer *mBuf,                   /* message buffer */
Buffer *dBuf,                   /* data buffer */
MsgLen dLen                     /* data length */
)
#else
PUBLIC INLINE S16 SUpdMsg(mBuf, dBuf, dLen)
Buffer *mBuf;                   /* message buffer */
Buffer *dBuf;                   /* data buffer */
MsgLen dLen;                    /* data length */
#endif
{
 
   TRC1(SUpdMsg)
 
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!mBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM161, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
   if (!dBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM162, ERRZERO, "Null dBuf");
      RETVALUE(RFAILED);
   }
 
#endif /* ERRCLASS */
 
   /* first update the dBuf */
   dBuf->t.dat.endIdx = dBuf->t.dat.strtIdx + dLen -1;
 
   /* now update the mBuf */
   SAddDBufPst(mBuf, dBuf);     /* append data buffer to message */
   mBuf->t.msg.msgLen += dLen;  /* increment message length */
 
   RETVALUE(ROK);
} /* end of SUpdMsg */



/*
*
*       Fun:   SChkNxtDBuf
*
*       Desc:  check if next data buffer exists.
*
*       Ret:   ROK/ROKDNA/RFAILED
*
*       Notes: doesn't modify nxtDBuf
*
*       File:  cm_ss.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SChkNxtDBuf
(
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC INLINE S16 SChkNxtDBuf(mBuf)
Buffer *mBuf;                   /* message buffer */
#endif
{

   TRC2(SChkNxtDBuf)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!mBuf)
   {
      CMLOGERROR(ERRCLS_INT_PAR, ECM155, ERRZERO, "Null mBuf");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS */
   if (mBuf->t.msg.nxtDBuf == NULLP)
      RETVALUE(ROKDNA);
   
   RETVALUE(ROK);
} /* end of SChkNxtDBuf */


/*
*
*       Fun:   SChkMsg
*
*       Desc:  Check Message
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: Check that the first buffer in a message
*              contains at least two bytes. This check is required
*              by 68302/68360 processors to insure accurate fisu 
*              generation.
*
*       File:  cm_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SChkMsg
(
Buffer *mBuf
)
#else
PUBLIC S16 SChkMsg(mBuf)
Buffer *mBuf;
#endif
{
   Buffer *first;
   Buffer *next;
#if (ERRCLASS & ERRCLS_DEBUG)
   S16 strtIdx;
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   TRC2(SChkMsg)
   
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (mBuf->t.msg.bufQ.dChn.next == NULLP)
      CMLOGERROR(ERRCLS_INT_PAR, ECM156, ERRZERO, "Null next ptr");
#endif /* ERRCLASS */

   first = mBuf->t.msg.bufQ.dChn.next;
   /* 
    * If there is more than one byte in the first dBuf, return
    */
   if (first->t.dat.strtIdx != first->t.dat.endIdx) 
      RETVALUE(ROK);

#if (ERRCLASS & ERRCLS_DEBUG)
   if (first->dChn.next == NULLP)
      CMLOGERROR(ERRCLS_DEBUG, ECM157, ERRZERO, "Null next ptr");
   SGetStrtIdx(DFLT_REGION, mBuf->t.msg.pool, &strtIdx);
   if (first->t.dat.strtIdx-3 < strtIdx)
      CMLOGERROR(ERRCLS_INT_PAR, ECM158, ERRZERO, "");
#endif
   next = first->dChn.next;

   /* shift bytes */

   /* 
    * Shift bytes.
    * 
    * Move first byte of second dBuf into second byte of first dBuf
    */
   
   /* shift the first byte of dBuf 1 to in by 3 positions
    * this should insure even byte alignment as well
    * as space from the second buffer
    */
   first->t.dat.data[first->t.dat.strtIdx -3] = 
      first->t.dat.data[first->t.dat.strtIdx];

   /*
    * move the first byte of dBuf 2 to dBuf 1
    */
   first->t.dat.data[first->t.dat.strtIdx -2] = 
      next->t.dat.data[next->t.dat.strtIdx];

   /*
    * move the second byte of dBuf 2 to to dBuf 1
    * this should insure alignment in the second dBuf
    * as well.
    */
   first->t.dat.data[first->t.dat.strtIdx -1] =
      next->t.dat.data[next->t.dat.strtIdx+1];

   /* adjust indecies */
   first->t.dat.strtIdx-= 3;
   first->t.dat.endIdx--;
   next->t.dat.strtIdx += 2;

   RETVALUE(ROK);
} /* end of SChkMsg */

  
/*
*
*       Fun:   SAddMsgRef
*
*       Desc:  This function is used to copy a message into
*              a new region and or pool of memory.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  cm_ss.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SAddMsgRef
(
Buffer *srcBuf,                   /* source message */
Region dstRegion,                 /* destination region */
Pool dstPool,                     /* destination pool */
Buffer **dstBuf                   /* pointer to destination message */
)
#else
PUBLIC S16 SAddMsgRef(srcBuf, dstRegion, dstPool, dstBuf)
Buffer *srcBuf;                   /* source message */
Region dstRegion;                 /* destination region */
Pool dstPool;                     /* destination pool */
Buffer **dstBuf;                  /* pointer to destination message */
#endif
{
   BufQLen size;                  /* current size */
   MsgLen i;                      /* counter */
   Buffer *dBuf;                  /* destination buffer */
   Buffer *sBuf;                  /* source buffer */
   S16 ret;                       /* return code */
  
   TRC1(SAddMsgRef)

   ret = SGetMsg(dstRegion,dstPool,dstBuf);
   if (ret != ROK)
   {
      RETVALUE(ret);
   }
   /* initialize destination buffer queue */
   SS_INITQUE(&(*dstBuf)->t.msg.bufQ);
   

   /* initialize variables to read source buffer queue */
   size = SS_QLEN(&srcBuf->t.msg.bufQ);
   sBuf =  srcBuf->t.msg.bufQ.dChn.next;

   /* copy data from source to destination message */
   for(; size; size--)
   {
      ret = SGetDBuf(dstRegion, dstPool, &dBuf);
      if (ret != ROK)
      {
         SPutMsg(*dstBuf);
         RETVALUE(ret);
      }
      /* initialize chain pointer of data buffer */
      SS_INITDCHN(&dBuf->dChn);

      SAddDBufPst(*dstBuf, dBuf);

      /* fetch next source buffer */
#if (ERRCLASS & ERRCLS_DEBUG)
      if (sBuf == NULLP)
      {
         SPutMsg(*dstBuf);
         CMLOGERROR(ERRCLS_DEBUG, ECM142, ERRZERO, "Null buf");
         RETVALUE(RFAILED);
      }
#endif
      dBuf->t.dat.strtIdx = sBuf->t.dat.strtIdx;
      dBuf->t.dat.endIdx  = sBuf->t.dat.endIdx;
      for(i=sBuf->t.dat.strtIdx;i<=sBuf->t.dat.endIdx;i++)
         dBuf->t.dat.data[i] = sBuf->t.dat.data[i];
      sBuf = sBuf->dChn.next;
   } 

   (*dstBuf)->bufType      = srcBuf->bufType;
   (*dstBuf)->t.msg.msgLen = srcBuf->t.msg.msgLen;

   RETVALUE(ROK);
} /* end of SAddMsgRef */


/********************************************************************30**
  
         End of file:     cm_ss.c@@/main/17 - Tue May 31 13:34:03 2005
  
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
1.1          ---  mb    1. initial release

1.2          ---  mb    1. change copyright header
             ---  mb    2. miscellaneous changes

1.3          ---  fmg   1. removed #include <stdio.h>

1.4          ---  fmg   1. changed RETVALUE(ROK) to RETVALUE(ret)
                           in SUnpkU32().

1.5          ---  fmg   1. changed ERRCLS to ERRCLASS

1.6          ---  mb    1. patched problem in SRemPstMsgMult

1.7          ---  fmg   1. fixed compile time warnings when ERRCLASS
                           is disabled
             ---  mb    2. fixed problem in SCpyMsgMsg

             ---  mb    3. fixed problem in SUnpkU32

             ---  mb    4. Added SAddMsgRef.

1.8          ---  mb    1. Modified SRemQueue to return ROKDNA
                           if idx >= q->crntsize.

1.9          ---  ada   1. Added SCompressMsg
             ---  ada   2. Cosmetic changes and new copyright changes

1.10         ---  rb    1. Added CMFILE_REORG_1 flag.

*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.11         ---      bbk  1. Changed copyright header date.

1.12         ---      ada  1. Replaced ECMXXX in SCompressMsg with error
                              codes

1.13         ---      ada  1. Changed type mismatches
             ---      ada  2. Include file stdio.h for DOS, UNIX, WIN32
                              enviroments
  
1.14         ---      tej  1. Change in header

/main/17     ---      rk   1. Updated for Release of IUA v1.3
*********************************************************************91*/
