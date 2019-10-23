
/********************************************************************20**
  
     Name:     common PER asn.1
  
     Type:     C Source file
  
     Desc:     C source code for common PER ASN.1 decoding 
               routines
  
     File:     cm_pasn4.c
  
     Sid:      cm_pasn4.c@@/main/21 - Thu Jun 30 18:32:18 2011
  
     Prg:      mp
  
*********************************************************************21*/


/************************************************************************
 
     Note: 
 
     This file has been extracted to support the following options:
 
     Option             Description
     ------    ------------------------------

************************************************************************/
 

/* header include files (.h) */
  
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_pasn.h"       /* PER ASN header file */
#include "cm_pint.h"       /* PER ASN Internal header file */
#include "cm_tkns.h"       /* Common token structure file */
#include "cm_perr.h"       /* Error header file */

/* header/extern include files (.x) */
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_lib.x"        /* Common Library */
#include "cm_mblk.x"        /* Memory Link list library */
#include "cm_tkns.x"       /* Common token structure file */
#include "cm_pasn.x"       /* common per asn.1 encoding/decoding */
#include "cm_pint.x"       /* PER ASN Internal header file */

/* Function declaration */


/*
*
*       Fun:   cmPAsnDecBitField
*
*       Desc:  This function Decodes a Bit Field 
*              for the specified number of bits
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnDecBitField
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U8 *value,              /* Location to place the bits decoded */
U8 size                 /* Number of bits to decode */
)
#else
PUBLIC S16 cmPAsnDecBitField (msgCp,value, size)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U8 *value;             /* Location to place the bits decoded */
U8 size;               /* Number of bits to decode */
#endif
{
   U8  byte;                   /* One octet value */
   U8  initByte;               /* Initialisation byte */

   TRC2 (cmPAsnDecBitField)
 
   *value = CM_PASN_VAL_NULL;

   /* If bits to read exceed 8, return error */
   if( size > CM_PASN_BF_SIZE8)
      RETVALUE(RFAILED);

   /* Check if bit position is 8 */
   /* If so, take next byte from Message buffer */
   /* cm_pasn4_c_001.main_16 Decode the byte only when the size requested 
    * is non-zero */
   if( (msgCp->bhldr.nxtBitPos == CM_PASN_NXTBITPOS_EIGHT) &&
       (size != 0))
   {
      CM_PASN_DEC_BYTE(msgCp, msgCp->bhldr.byte);
   }
       
   /* 
    * If number of bits to decode is less than number 
    * of bits available in the current byte 
    */

   if( size <= (U8)msgCp->bhldr.nxtBitPos)
   {
      /* Read the required bits from top */
      byte = msgCp->bhldr.byte;
      *value = (byte >> (msgCp->bhldr.nxtBitPos - size));

      /* Get initialisation byte to put extra bits in */
      /* begining of *value to zero */
      initByte = CM_PASN_GET_DECINITBYTE(size);
      *value = (*value) & initByte; 

      if( size != msgCp->bhldr.nxtBitPos)
      {
         msgCp->bhldr.nxtBitPos = msgCp->bhldr.nxtBitPos - size;
      }
      else
         msgCp->bhldr.nxtBitPos = CM_PASN_NXTBITPOS_EIGHT;
   }

   else
   {
      /* If number of bits to read exceed the unread bits */
      /* available in present byte value */
      initByte = CM_PASN_GET_DECINITBYTE(msgCp->bhldr.nxtBitPos);
      *value = msgCp->bhldr.byte & initByte;

      *value = (*value) << (size - msgCp->bhldr.nxtBitPos);
  
      size = size - msgCp->bhldr.nxtBitPos;
      msgCp->bhldr.nxtBitPos = CM_PASN_NXTBITPOS_EIGHT;

      /* Get next byte in the message buffer */
      CM_PASN_DEC_BYTE(msgCp, msgCp->bhldr.byte);

      initByte = CM_PASN_GET_DECINITBYTE(size);
      byte = msgCp->bhldr.byte >> (msgCp->bhldr.nxtBitPos - size);
      *value = (*value) | ( byte & initByte); 
     
      msgCp->bhldr.nxtBitPos = msgCp->bhldr.nxtBitPos - size;
   } 

   RETVALUE(ROK);

} /* cmPAsnDecBitField */



/*
*
*       Fun:   cmPAsnSkipMsgBits
*
*       Desc:  This function skips bits in message buffer 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnSkipMsgBits
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          noBits     /* number of bits to skip */
)
#else
PUBLIC S16 cmPAsnSkipMsgBits (msgCp, noBits)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          noBits;   /* Number of bits to skip */
#endif
{
  U8      ctr;         /* Loop variable */
  U8      padBits;     /* Number of pad bits */
  U8      noExtBits;   /* Number of extra bits */
  U8      noBytes;     /* Number of complete octets */
  U8      byte;        /* To store bit field */
  S16     ret;         /* Return value */

  TRC2 (cmPAsnSkipMsgBits)
 
  /*
   * Algorithm: If bits to skip is less than
   * those availabe in bit handler, just decode
   * them and ignore, else, skip first the ones
   * in bit handler, then swallow number of octets
   * from message, and finally decode left number
   * of bits and ignore
   */

  if( noBits <= (U32)msgCp->bhldr.nxtBitPos)
  {
     /* Extract noBits and ignore */
     /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = cmPAsnDecBitField(msgCp, &byte, 
                                   (U8)noBits);
     if(ret != ROK)
        RETVALUE(RFAILED);
  }
  else
  {
     padBits = msgCp->bhldr.nxtBitPos;
     /* Skip available bit handler bits as pad bits */
     CM_PASN_SKIP_PADBITS(msgCp);
     /* Find number of bytes in remaining bits to skip */
     noBytes = (noBits - (U32)padBits) / CM_PASN_VAL_EIGHT;
     noExtBits = (noBits - (U32)padBits) % CM_PASN_VAL_EIGHT;

     /* Swallow noBytes */
     for(ctr =0; ctr < noBytes; ctr++)
     {
        CM_PASN_DEC_BYTE(msgCp, byte);
     }

     /* Finally swallow noExtBits from mBuf */
     /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = cmPAsnDecBitField(msgCp, &byte,noExtBits);
     if(ret!= ROK)
        RETVALUE(RFAILED); 
     
  } 

  RETVALUE(ROK);
} /* End of cmPAsnSkipMsgBits */



/*
*
*       Fun:   cmPAsnDecUnconLen
*
*       Desc:  This function Decodes an Unconstrained Length 
*              field in the message buffer 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnDecUnconLen
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          *len,      /* Location to return length value */
Bool         *fragFlag  /* If fragmentation is done */   
)
#else
PUBLIC S16 cmPAsnDecUnconLen (msgCp,len, fragFlag)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          *len;     /* Location to return length value */
Bool         *fragFlag; /* If fragmentation is done */ 
#endif
{

  U8  val = 0;            /* to store bit field values */ 
  U8  secVal = 0 ;         /* Another octet to store bit field */
  U8  m;              /* To find the no. of Fragmentation of length 16k */ 

  S16 ret;
  TRC2(cmPAsnDecUnconLen)

  *len = CM_PASN_VAL_NULL;
  *fragFlag = FALSE;
  if (msgCp->perType == CM_PASN_USE_UALIGN)
  {
     /* vikas First get to next octet boundary */
/* cm_pasn4_c_001.main_15 This is an Unallign case, so no need to call
 * CM_PASN_SKIP_PADBITS & it is also inconsistent with the encoding */

     /* Read the first length byte */ 
     /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = cmPAsnDecBitField(msgCp,&val,CM_PASN_VAL_EIGHT);
     if(ret!= ROK)
          RETVALUE(RFAILED);
  }
  else
  {
     /* First get to next octet boundary */
     CM_PASN_SKIP_PADBITS(msgCp);

     /* Read the first length byte */
     CM_PASN_DEC_BYTE(msgCp, val);
  }
  /* If First bit is 0 */
  if( !(val & CM_PASN_BYTE_MSBONE) )
     *len = (U32)val;

  else
  {
     /* If first bit is 1 */
     /* Check if second bit is 0 */ 
     if( !(val & CM_PASN_FRAG_CONST2) )
     {
        /* Decode next byte */
        if (msgCp->perType == CM_PASN_USE_UALIGN)
        {
     /* cm_pasn4_c_001.main_21 : kwork fix */
        ret = cmPAsnDecBitField(msgCp,&secVal,CM_PASN_VAL_EIGHT);
        if(ret!= ROK)
        RETVALUE(RFAILED);
        }
        else
        {
           CM_PASN_DEC_BYTE(msgCp, secVal);
        }
        *len = (U32)( (val & CM_PASN_FRAG_CONST3)  
                             << CM_PASN_VAL_EIGHT);
        *len |= (U32)secVal;

     }
     else
     {
        /* Fragmentation case */
        /* return in length the entire octet */
/* cm_pasn4_c_001.main_15 This is a fragmented case.According to Spec 
 * X.691-0207 section 10.9, the value of  m should be between 1 to 4
 * both inclusive */
        m = (val & CM_PASN_FRAG_CONST3);
#ifdef CM_PASN_DBG
        CM_PASN_DBGP(msgCp,
           (msgCp->prntBuf,"Decoded number of fragmentation  %d\n",
            m) );
#endif

        if(m < 1 || m > 4)
         {
            RETVALUE(RFAILED);
         }

        *len = val;
        *fragFlag = TRUE;
     }
  }

  RETVALUE(ROK);

} /* End of cmPAsnDecUnconLen */ 



/*
*
*       Fun:   cmPAsnDecSmallInt
*
*       Desc:  This function Decodes Normally Small
*              Integer
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnDecSmallInt
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
S32          *val       /* Location to return Integer value */
)
#else
PUBLIC S16 cmPAsnDecSmallInt (msgCp,val)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
S32          *val;     /* Location to return integer value */
#endif
{
  Bool  fragFlag;     /* Fragmentation Flag */
  U8    byte;         /* To store bit field */
  U8    octet;        /* One octet value */
  S16   ret;          /* Return value */
  U32   len;          /* Length Determinant */

  TRC2(cmPAsnDecSmallInt)

  fragFlag = FALSE;

  /* Check the first bit */
     /* cm_pasn4_c_001.main_21 : kwork fix */
  ret = cmPAsnDecBitField(msgCp, &byte, CM_PASN_VAL_ONE);
  if(ret!= ROK)
     RETVALUE(RFAILED);

  if(!(byte & CM_PASN_BYTE_LSBONE))
  {
     /* Read next 6 bits */
     /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = cmPAsnDecBitField(msgCp, &octet, CM_PASN_VAL_SIX);
     if(ret!= ROK)
        RETVALUE(RFAILED);

     *val = (S32)octet;
  }
  else
  {
     /* Decode Unconstrained length len */
     /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag);
     if(ret!= ROK)
        RETVALUE(RFAILED);

     /* Decode integer as Semi Constrained Integer, with lb 0 */
     /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = cmPAsnDecSemiConInt(msgCp,len , CM_PASN_VAL_NULL, 
                                    (U32 *)val,FALSE);
     if(ret!= ROK)
        RETVALUE(RFAILED);
  }

  RETVALUE(ROK);

} /* End of cmPAsnDecSmallInt */



/*
*
*       Fun:   cmPAsnDecNormSmallLen
*
*       Desc:  This function Decodes Normally Small
*              Length field in the message buffer 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnDecNormSmallLen
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          *len       /* Location to return length value */
)
#else
PUBLIC S16 cmPAsnDecNormSmallLen (msgCp,len)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          *len;     /* Location to return length value */
#endif
{
  U8    byte;         /* To store bit field */
  U8    octet;        /* One octet value */
  Bool  frag;         /* Fragmentation Flag */
  S16   ret;          /* Return value */

  TRC2(cmPAsnDecNormSmallLen)

  /* Check the first bit */
     /* cm_pasn4_c_001.main_21 : kwork fix */
  ret = cmPAsnDecBitField(msgCp, &byte, CM_PASN_VAL_ONE);
  if(ret != ROK)
     RETVALUE(RFAILED);

  if(!(byte & CM_PASN_BYTE_LSBONE))
  {
     /* Read next 6 bits */
     /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = cmPAsnDecBitField(msgCp, &octet, CM_PASN_VAL_SIX);
     if(ret != ROK)
        RETVALUE(RFAILED);

     *len = (U32)(octet +1);
  }
  else
  {
     /* Further encoding is as Unconstrained length */
     /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = cmPAsnDecUnconLen(msgCp, len, &frag);
     if(ret != ROK)
        RETVALUE(RFAILED);
  }

  RETVALUE(ROK);

} /* End of cmPAsnDecNormSmallLen */



/*
*
*       Fun:   cmPAsnDecConLen
*
*       Desc:  This function Decodes Constrained Length 
*              field in the message buffer 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnDecConLen
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          *len,      /* Location to return length value */
U32          lb,        /* Lower Bound on length */
U32          ub,        /* Upper Bound on length */ 
Bool         *fragFlag  /* If fragmentation is done */   
)
#else
PUBLIC S16 cmPAsnDecConLen (msgCp,len, lb, ub,fragFlag)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          *len;     /* Location to return length value */
U32          lb;       /* Lower bound on length */
U32          ub;       /* Lower bound on length */
Bool         *fragFlag; /* If fragmentation is done */ 
#endif
{
  U8      byte = 0;        /* To store bit field value */
  U8      bfSize;      /* Bit Field Size */
  U32     range;       /* Range of length */
  S32     ret;         /* Return value */

  U8     i;                 /* Loop variable */ 
  U8 N;                     /* To store number of bits */
  U32 v;       /* To store value */
  U8 pos;                   /* To store value */
  U8 noBytes;
  U8 noBits;
  U8     unPkArray[4];      /* To store integer value */
  U32    intVal;            /* Decoded value of integer */

  TRC2(cmPAsnDecConLen)

  *fragFlag = FALSE;
  *len = 0;
  range = ub - lb +1;

  if (msgCp->perType == CM_PASN_USE_UALIGN)
  {
v=range;
   N=CM_PASN_VAL_NULL;
   v=v-1;
CM_PASN_FIND_NOBITS(v,N);
pos=msgCp->bhldr.nxtBitPos;

if(N<=pos )
{
   /* cm_pasn4_c_001.main_21 : kwork fix */
   ret=cmPAsnDecBitField(msgCp, &unPkArray[0],N);
   if(ret != ROK)
      RETVALUE(RFAILED);
   intVal=(U32)(unPkArray[0]);                
}
else
{
   /* cm_pasn4_c_001.main_21 : kwork fix */
   ret=cmPAsnDecBitField(msgCp, &unPkArray[0],pos);
   if(ret!= ROK)
      RETVALUE(RFAILED);

   intVal=(U32)(unPkArray[0]);
   noBits=(N-pos)%CM_PASN_VAL_EIGHT;
   noBytes=(N-pos)/CM_PASN_VAL_EIGHT;
   for(i=0; i< noBytes; i++) 
   {
      CM_PASN_DEC_BYTE(msgCp,unPkArray[i]);
      intVal <<=8;
      intVal|=(U32)(unPkArray[i]);
   }

   if(noBits)
   {
      /* cm_pasn4_c_001.main_21 : kwork fix */
      ret=cmPAsnDecBitField(msgCp, &unPkArray[0],noBits);     
      if(ret != ROK)
         RETVALUE(RFAILED);
      intVal <<=noBits;
      intVal|=(U32)(unPkArray[0]);
   }
}   


*len = (U32)(intVal + lb);

RETVALUE(ROK);     

  }

  if( ub < CM_PASN_VAL_64K)
  {
     if( range == 1)
        RETVALUE(ROK);

     if( (range >= CM_PASN_RANGE_TWO) &&
         (range <= CM_PASN_RANGE_255) ) 
     {
        /* Length should be decoded as bit field */
        bfSize = cmPAsnGetBFSize(range); 
      /* cm_pasn4_c_001.main_21 : kwork fix */
        ret = cmPAsnDecBitField(msgCp, &byte, bfSize);
        if(ret!= ROK)
           RETVALUE(RFAILED);
  
        *len = (U32)byte + lb;
        /* Validate that the decoded value is within expected range */
        if (*len > ub)
        {
           CM_PASN_ERR(msgCp, CM_PASN_OUT_RANGE);
           RETVALUE(RFAILED);
        } 
        else 
           RETVALUE(ROK);
     }

     if( range == CM_PASN_RANGE_256)
     {
        /* Read next byte of information */
        if (msgCp->perType == CM_PASN_USE_UALIGN)
        {
      /* cm_pasn4_c_001.main_21 : kwork fix */
         ret=(S32)cmPAsnDecBitField(msgCp,&byte,CM_PASN_VAL_EIGHT);
         if(ret!= ROK)
         RETVALUE(RFAILED);
        }
        else
        {
   /* Skip pad bits and reach to next octet boundary */
   CM_PASN_SKIP_PADBITS(msgCp);
   CM_PASN_DEC_BYTE(msgCp, byte);
        }

        *len = (U32)byte + lb;
        /* Validate that the decoded value is within expected range */
        if (*len > ub)
        {
           CM_PASN_ERR(msgCp, CM_PASN_OUT_RANGE);
           RETVALUE(RFAILED);
        } 
        else
           RETVALUE(ROK);
     }

     if( (range > CM_PASN_RANGE_256 )&&
         ( range <= CM_PASN_VAL_64K) )
     {
        /* Value is stored in 2 octets */
        
        if (msgCp->perType == CM_PASN_USE_UALIGN)
        {
      /* cm_pasn4_c_001.main_21 : kwork fix */
        ret=(S32)cmPAsnDecBitField(msgCp,&byte,CM_PASN_VAL_EIGHT);
   if(ret != ROK)
     RETVALUE(RFAILED);
        }
        else
        {
   /* Skip pad bits and reach to next octet boundary */
   CM_PASN_SKIP_PADBITS(msgCp);
   CM_PASN_DEC_BYTE(msgCp, byte);
        }
        *len = ((U32)byte << 8);
        if (msgCp->perType == CM_PASN_USE_UALIGN)
        {
      /* cm_pasn4_c_001.main_21 : kwork fix */
          ret=cmPAsnDecBitField(msgCp,&byte,CM_PASN_VAL_EIGHT);
   if(ret!= ROK)
     RETVALUE(RFAILED);
        }
        else
        {
           CM_PASN_DEC_BYTE(msgCp, byte);
        }
        *len = (*len | (U32)byte);
        *len = *len + lb;
        /* Validate that the decoded value is within expected range */
        if (*len > ub)
        {
           CM_PASN_ERR(msgCp, CM_PASN_OUT_RANGE);
           RETVALUE(RFAILED);
        } 
        else 
           RETVALUE(ROK);
    } 
  }
  else
  {
     /* Length determinant has ub more than 64K */
     /* Length determinant would have been encoded */
     /* as Unconstrained length */
      /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = cmPAsnDecUnconLen(msgCp, len, fragFlag);
     if( ret != ROK)
        RETVALUE(RFAILED);
  } 

  RETVALUE(ROK);

} /* End of cmPAsnDecConLen */



/*
*
*       Fun:   cmPAsnDecConInt
*
*       Desc:  This function Decodes Constrained Integer bit 
*              field in the message buffer 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnDecConInt
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          min,       /* Minimum Integer value */
U32          max,       /* Maximum Integer value */
U32          *val,      /* Location to place decoded value */
Bool         isSigned   /* Is the integer signed */
)
#else
PUBLIC S16 cmPAsnDecConInt (msgCp, min, max, val,isSigned)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          min;      /* Minimum Integer value */
U32          max;      /* Maximum Integer value */
U32          *val;     /* Location to place decoded value */ 
Bool         isSigned;  /* Is the integer signed */ 
#endif
{
  Bool   fragFlag;          /* Fragmentation Flag */
  U8     ub;                /* upper bound on length determinant */ 
  U8     i;                 /* Loop variable */ 
  U8     unPkArray[4]={0};   /* To store integer value */
  S16    ret;               /* Return value */
  U32    range;             /* Range of the integer */
  U32    intVal;            /* Decoded value of integer */
  U32    len;               /* Value of length determinant */
  
  U8 N;                     /* To store number of bits */
  U32 v;       /* To store value */
  U8 pos;                   /* To store value */
  U8 noBytes;
  U8 noBits;
  TRC2(cmPAsnDecConInt)

  /* check if mBuf is NULL */
  if(msgCp->mBuf == NULLP)
  {
#ifdef CM_PASN_DBG
     CM_PASN_DBGP(msgCp, (msgCp->prntBuf,"mBuf is NULL while decoding\n"));
#endif /* CM_PASN_DBG */
  
     RETVALUE(RFAILED);
  }

  /* init intVal */
  intVal = 0;

  fragFlag = FALSE;

  if( !isSigned)
     range = (U32)(max - min +1);
  else
     range = (U32)((S32)max - (S32)min +1);

  if (msgCp->perType == CM_PASN_USE_UALIGN)
  {
v=range;
   N=CM_PASN_VAL_NULL;
   v=v-1;
CM_PASN_FIND_NOBITS(v,N);
pos=msgCp->bhldr.nxtBitPos;

if(N <=pos )
{
      /* cm_pasn4_c_001.main_21 : kwork fix */
	ret=cmPAsnDecBitField(msgCp, &unPkArray[0],N);

if(ret!= ROK)
RETVALUE(RFAILED);
intVal=(U32)(unPkArray[0]);                
}
else
{
      /* cm_pasn4_c_001.main_21 : kwork fix */
    ret=cmPAsnDecBitField(msgCp, &unPkArray[0],pos);
	 if(ret!= ROK)
       RETVALUE(RFAILED);

intVal=(U32)(unPkArray[0]);
   noBits=(N-pos)%CM_PASN_VAL_EIGHT;
 noBytes=(N-pos)/CM_PASN_VAL_EIGHT;
for(i=0; i< noBytes; i++) 
{
CM_PASN_DEC_BYTE(msgCp,unPkArray[i]);
intVal <<=8;
intVal|=(U32)(unPkArray[i]);
}
        
if(noBits)
{
      /* cm_pasn4_c_001.main_21 : kwork fix */
  ret=cmPAsnDecBitField(msgCp, &unPkArray[0],noBits);    
if(ret!= ROK)
RETVALUE(RFAILED);
intVal <<=noBits;
intVal|=(U32)(unPkArray[0]);
}
}   


if(!isSigned)
*val = (U32)(intVal + min);
else 
*val = (U32)((S32)intVal + (S32)min);

RETVALUE(ROK);     

  }

  /* If max and min are equal */ 
  if( range == 1)
     intVal = CM_PASN_VAL_NULL;

  else
  if( (range >= CM_PASN_RANGE_TWO) &&
      (range <= CM_PASN_RANGE_255) ) 
  {

      /* cm_pasn4_c_001.main_21 : kwork fix */
     ret = cmPAsnDecBitField(msgCp, &unPkArray[0], 
                   (U8)cmPAsnGetBFSize(range) );
	  if(ret!= ROK)
        RETVALUE(RFAILED);
  
     intVal = (U32)(unPkArray[0]);
  }

  else
  if( range == CM_PASN_RANGE_256)
  {
     /* Skip pad bits and reach to next octet boundary */
     CM_PASN_SKIP_PADBITS(msgCp);

     /* Read next byte of information */
     CM_PASN_DEC_BYTE(msgCp, unPkArray[0]);

     intVal = (U32)(unPkArray[0]);
  }
  else
  if( (range > CM_PASN_RANGE_256 )&&
      ( range <= CM_PASN_VAL_64K) )
  {
     /* Value is stored in 2 octets */
     /* Skip pad bits and reach to next octet boundary */
     CM_PASN_SKIP_PADBITS(msgCp);

     for( i=0; i<= CM_PASN_VAL_ONE; i++)
     {
        CM_PASN_DEC_BYTE(msgCp, unPkArray[i]);
     }

     /* Get the integer value */
     intVal = (U32)(unPkArray[0]);
     intVal = (U32)( (intVal << CM_PASN_VAL_EIGHT) | unPkArray[1]);
       
  } 
  else
  {
     /* range exceeds 64K */
     /* Find "len" as contrained length determinant */
     /* "ub" is equal to the number of octets need */
     /* to hold the range of Integer value */

     /* range will be zero for 0-0xFFFFFFFF case */
     /* Otherwise range is non-zero */
     if( range)
     {
        CM_PASN_FIND_NOOCTET(range,ub); 
     }
     else
        ub = CM_PASN_FOUR_OCTETS;
      /* cm_pasn4_c_001.main_21 : kwork fix */
     ret = cmPAsnDecConLen(msgCp, &len, CM_PASN_VAL_ONE, ub , 
                      &fragFlag);
     if(ret!= ROK)
        RETVALUE(RFAILED); 

     if( !fragFlag)
     {
        /* Fragmentation not found */
        /* Skip pad bits to reach next octet boundary */
        CM_PASN_SKIP_PADBITS(msgCp);

        /* Read "len" number of bytes from message buffer */
        for( i=0; i < len; i++)
        {
           CM_PASN_DEC_BYTE(msgCp,unPkArray[i]);
        } 

        intVal = (U32)(unPkArray[0]); 
        for( i=1; i< len; i++)
           intVal = (U32)((intVal << CM_PASN_VAL_EIGHT) | unPkArray[i]);

     }
  }

  /* Find the actual integer value */
  if(!isSigned)
     *val = (U32)(intVal + min);
  else 
     *val = (U32)((S32)intVal + (S32)min);

  /* Validate that the decoded value is within expected range */
  if (((!isSigned) && ((*val < min) || (*val > max))) || 
        ((isSigned) && (((S32)(*val) < (S32)min) || ((S32)(*val) > (S32)max))))
  {
      CM_PASN_ERR(msgCp, CM_PASN_OUT_RANGE);
      RETVALUE(RFAILED);
  } 

  RETVALUE(ROK);

} /* End of cmPAsnDecConInt */ 


/* cm_pasn4_c_001.main_17 */
/*
*
*       Fun:   cmPAsnDecConIntXL
*
*       Desc:  This function Decodes Constrained Integer bit 
*              field in the message buffer 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnDecConIntXL
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U8           *lBound,   /* Lower Bound on the integer value */
U8           lbLen,     /* Length of the Lower Bound */
U8           *uBound,   /* Upper Bound on the integer value */
U8           ubLen,     /* Length of the Upper Bound */
U8           *value,    /* Decoded Integer value */
U8           *len       /* Length of the decoded Integer value */
)
#else
PUBLIC S16 cmPAsnDecConIntXL (msgCp, lBound, lbLen, uBound, ubLen, value, len)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U8           *lBound;   /* Lower Bound on the integer value */
U8           lbLen;     /* Length of the Lower Bound */
U8           *uBound;   /* Upper Bound on the integer value */
U8           ubLen;     /* Length of the Upper Bound */
U8           *value;    /* Decoded Integer value */
U8           *len;      /* Length of the decoded Integer value */
#endif
{
   Bool   fragFlag;    /* Fragmentation Flag */
   U8     idx;         /* Loop variable */ 
   S16    ret;         /* Return value */
   U8     range[CM_PASN_UINTXL_SIZE]; /* Range of values */ 
   U8     rangeLen;    /* Length of the range */ 
   U8     numBits;     /* To store number of bits PU*/ 
   U8     nBits;     
   U8     nBytes;   
   U8     minResult, maxResult;

   TRC2(cmPAsnDecConIntXL)

   fragFlag = FALSE;

   {
      U8          diff[CM_PASN_UINTXL_SIZE];
      U8          difflen;
      U8          byte[CM_PASN_VAL_ONE];

      byte[0] = CM_PASN_VAL_ONE;
      cmPAsnSubtractUIntXL(uBound, ubLen, lBound, lbLen, diff, &difflen);
      cmPAsnAddUIntXL(diff, difflen, byte, CM_PASN_VAL_ONE, range, &rangeLen);

#if 0 /* TODO remove */
      CM_PASN_SUBTRACT_INTXL(uBound, ubLen, lBound, lbLen, diff, difflen);
      CM_PASN_ADD_INTXL(diff, difflen, byte, CM_PASN_VAL_ONE, range, rangeLen);
#endif
   }

	if (msgCp->perType == CM_PASN_USE_UALIGN)
	{
      U8    v[CM_PASN_UINTXL_SIZE];
      U8    vLen;
      U8    byte[CM_PASN_VAL_ONE];

      byte[0] = CM_PASN_VAL_ONE;
      cmPAsnSubtractUIntXL(range, rangeLen, byte, CM_PASN_VAL_ONE, v, &vLen);
#if 0 /* TODO remove */
      CM_PASN_SUBTRACT_INTXL(range, rangeLen, byte, CM_PASN_VAL_ONE, v, vLen);
#endif

      numBits = CM_PASN_VAL_NULL;
		CM_PASN_FIND_NOBITS(v[0], numBits);
      numBits = numBits + ((vLen - 1) * CM_PASN_VAL_EIGHT);

      nBytes = numBits / CM_PASN_VAL_EIGHT;
      nBits  = numBits % CM_PASN_VAL_EIGHT;

      idx = 0;
      if (nBits)
      {
      /* cm_pasn4_c_001.main_21 : kwork fix */
         ret = cmPAsnDecBitField(msgCp, &value[idx], nBits);
			if (ret!= ROK)
            RETVALUE(RFAILED);
         idx++;
      }

      for (; idx < nBytes; idx++)
      {
         CM_PASN_DEC_BYTE(msgCp, value[idx]);
      }

      *len = idx;

      CM_PASN_REMOVE_NULLBYTES(value, *len);

#if 0
		pos=msgCp->bhldr.nxtBitPos;

		if(N <=pos )
		{
			if( (ret=cmPAsnDecBitField(msgCp, &unPkArray[0],N)) != ROK)
				RETVALUE(RFAILED);
			intVal=(U32)(unPkArray[0]);                
		}
		else
		{
			if( (ret=cmPAsnDecBitField(msgCp, &unPkArray[0],pos)) != ROK)
				RETVALUE(RFAILED);

			intVal=(U32)(unPkArray[0]);
			noBits=(N-pos)%CM_PASN_VAL_EIGHT;
			noBytes=(N-pos)/CM_PASN_VAL_EIGHT;
			for(i=0; i< noBytes; i++) 
			{
				CM_PASN_DEC_BYTE(msgCp,unPkArray[i]);
				intVal <<=8;
				intVal|=(U32)(unPkArray[i]);
			}

			if(noBits)
			{

				if( (ret=cmPAsnDecBitField(msgCp, &unPkArray[0],noBits)) != ROK)
					RETVALUE(RFAILED);
				intVal <<=noBits;
				intVal|=(U32)(unPkArray[0]);
			}
		}   
#endif

      {
         U8          bytes[CM_PASN_UINTXL_SIZE];
         U8          bLen;

         bLen = *len;
         for (idx = 0; idx < bLen; idx++)
            bytes[idx] = value[idx];

         cmPAsnAddUIntXL(bytes, bLen, lBound, lbLen, value, len);
#if 0 /* TODO remove */
         CM_PASN_ADD_INTXL(bytes, bLen, lBound, lbLen, value, *len);
#endif
      }

		RETVALUE(ROK);     
	}

	/* If max and min are equal */ 
	if ((rangeLen == 1) && (range[0] == CM_PASN_RANGE_ONE))
   {
      *len = 0;
   }

   /* range is less than or equal to 255 */
   else if (rangeLen == 1)
   {
      /* cm_pasn4_c_001.main_21 : kwork fix */
      ret = cmPAsnDecBitField(msgCp, &value[0], 
							(U8)cmPAsnGetBFSize(range[0]));
		if (ret!= ROK)
         RETVALUE(RFAILED);

      *len = CM_PASN_VAL_ONE;
   }

   /* range is exactly 256 */
   else if ((rangeLen == 2) && (range[0] == 0x01) && (range[1] == 0x00))
   {
      /* Skip pad bits and reach to next octet boundary */
      CM_PASN_SKIP_PADBITS(msgCp);

      /* Read next byte of information */
      CM_PASN_DEC_BYTE(msgCp, value[0]);

      *len = CM_PASN_VAL_ONE;
   }

   /* range is greater than 256 and less than or equal to 64K */
   else if ((rangeLen == 2) && !((range[0] == 0x01) && (range[1] == 0x00)))
   {
      /* Skip pad bits and reach to next octet boundary */
      CM_PASN_SKIP_PADBITS(msgCp);

      for (idx = 0; idx < CM_PASN_VAL_TWO; idx++)
      {
         CM_PASN_DEC_BYTE(msgCp, value[idx]);
      }

      *len = CM_PASN_VAL_TWO;
   } 
   /* range exceeds 64K */
   else
   {
      U32 decLen;
      /* cm_pasn4_c_001.main_21 : kwork fix */
      ret = cmPAsnDecConLen(msgCp, &decLen, CM_PASN_VAL_ONE, rangeLen, 
									      &fragFlag);
      if (ret != ROK)
         RETVALUE(RFAILED); 

      *len = (U8)decLen;

      if (!fragFlag)
      {
         /* Fragmentation not found */
         /* Skip pad bits to reach next octet boundary */
         CM_PASN_SKIP_PADBITS(msgCp);

         /* Read "len" number of bytes from message buffer */
         for (idx = 0; idx < *len; idx++)
         {
            CM_PASN_DEC_BYTE(msgCp, value[idx]);
         } 
      }
   }

   {
      U8          v[CM_PASN_UINTXL_SIZE];
      U8          vLen;

      vLen = *len;
      for (idx = 0; idx < vLen; idx++)
         v[idx] = value[idx];

      cmPAsnAddUIntXL(v, vLen, lBound, lbLen, value, len);
#if 0 /* TODO remove */
      CM_PASN_ADD_INTXL(v, vLen, lBound, lbLen, value, *len);
#endif
   }

	/* Validate that the decoded value is within expected range */
   CM_PASN_COMPARE_UINTXL(value, *len, lBound, lbLen, minResult);
   CM_PASN_COMPARE_UINTXL(value, *len, uBound, ubLen, maxResult);

   if ((minResult == CM_PASN_UINTXL_VAL_SMALL) || 
       (maxResult == CM_PASN_UINTXL_VAL_LARGE))
	{
		CM_PASN_ERR(msgCp, CM_PASN_OUT_RANGE);
		RETVALUE(RFAILED);
	} 

	RETVALUE(ROK);

} /* End of cmPAsnDecConIntXL */ 



/*
*
*       Fun:   cmPAsnValIntValue
*
*       Desc:  This function validates Integer Value
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnValIntValue
(
CmPAsnMsgCp  *msgCp,     /* Message Control Point */
U32          value,      /* Integer value */
U8           type,       /* Integer type */
Bool         isSigned      /* Is it a signed integer */
)
#else
PUBLIC S16 cmPAsnValIntValue (msgCp, value, type,isSigned)
CmPAsnMsgCp   *msgCp;    /* Message Control Point */
U32           value;     /* Integer value */
U8            type;      /* Integer type */
Bool          isSigned;    /* is it a signed integer */
#endif
{
 
  S32    sValue;      /* signed integer value */
  U32    tmpVal;

  TRC2(cmPAsnValIntValue)

  tmpVal = 0;
  sValue = 0;

  if (isSigned)
  {
     sValue = (S32)value;

     if (value & CM_PASN_MSB_ONE)
        tmpVal = ~value;
     else
        tmpVal = value; 
  }

  switch(type)
  {
     case CM_PASN_TET_SINT8:
        if( tmpVal & CM_PASN_SIGNED_ONEBYTE)
           RETVALUE(RFAILED);
        
        /* Convert S32 value into S8 and place it in event str */
        ((TknS8 *)(msgCp->evntStr))->pres = PRSNT_NODEF;
        ((TknS8 *)(msgCp->evntStr))->val = (S8)sValue;
        break;

     case CM_PASN_TET_SINT16:
        if( tmpVal & CM_PASN_SIGNED_TWOBYTE)
           RETVALUE(RFAILED);
        
        /* Convert S32 value into S16 and place it in event str */
        ((TknS16 *)(msgCp->evntStr))->pres = PRSNT_NODEF;
        ((TknS16 *)(msgCp->evntStr))->val = (S16)sValue;
        break;

     case CM_PASN_TET_SINT32:
        ((TknS32 *)(msgCp->evntStr))->pres = PRSNT_NODEF;
        ((TknS32 *)(msgCp->evntStr))->val = sValue;
        break;
     
    case CM_PASN_TET_UINT8:
        if( value & CM_PASN_UNSIGNED_ONEBYTE) 
           RETVALUE(RFAILED);

        ((TknU8 *)(msgCp->evntStr))->pres = PRSNT_NODEF;
        ((TknU8 *)(msgCp->evntStr))->val = (U8)value;
        break;

     case CM_PASN_TET_UINT16:
        if( value > CM_PASN_UNSINGED_TWOBYTE)
           RETVALUE(RFAILED);

        ((TknU16 *)(msgCp->evntStr))->pres = PRSNT_NODEF;
        ((TknU16 *)(msgCp->evntStr))->val = (U16)value;
        break;

     case CM_PASN_TET_UINT32:
        ((TknU32 *)(msgCp->evntStr))->pres = PRSNT_NODEF;
        ((TknU32 *)(msgCp->evntStr))->val = value;
        break;

     default:
        break;
  }

  RETVALUE(ROK);

} /* End of cmPAsnValIntValue */


/*
*
*       Fun:   cmPAsnDecUnconInt
*
*       Desc:  This function Decodes Unconstrained Integer Value
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnDecUnconInt
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          len,       /* Number of octets */ 
U32          *val,      /* Return integer value */
Bool         *negVal
)
#else
PUBLIC S16 cmPAsnDecUnconInt (msgCp, len, val, negVal)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          len;      /* Number of octets */
U32          *val;     /* Return integer value */
Bool         *negVal;
#endif
{

  U8    unPkArray[CM_PASN_FOUR_OCTETS]={0};      /* To store octets */
  U8    i;                                   /* index */ 
  U32   value;                               /* Integer Value */
  U8    tmpLen;

  TRC2(cmPAsnDecUnconInt)

  /* Read "len" number of octets as value */
  for( i=0; i < (U8)len; i++)
  {
     if (msgCp->perType == CM_PASN_USE_UALIGN)
     {
      /* cm_pasn4_c_001.main_21 : kwork fix */
       S16 ret;
		 ret = cmPAsnDecBitField(msgCp,&unPkArray[i],CM_PASN_VAL_EIGHT);
       if(ret != ROK)
       RETVALUE(RFAILED);
     }
     else
     {
        CM_PASN_DEC_BYTE(msgCp,unPkArray[i]);
     }
  } 

  value  = CM_PASN_VAL_NULL;
  i=0;
  tmpLen= len;

  if(unPkArray[0] &0x80)
  {
     *negVal = TRUE;
     unPkArray[0] &= 0x7f;
  }
  else
     *negVal = FALSE;

  while(len)
  {
     value =  (value << CM_PASN_VAL_EIGHT) | (unPkArray[i]);
     i++; len--;
  }

  if(*negVal)
     *val = (0x01 << (8*tmpLen - 1)) - value;
  else
     *val = value;

  RETVALUE(ROK);

} /* End of cmPAsnDecUnconInt */


/*
*
*       Fun:   cmPAsnDecUnconIntXL
*
*       Desc:  This function Decodes Unconstrained Integer Value
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnDecUnconIntXL
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U8           len,       /* Number of octets */ 
U8           *val       /* Return integer value */
)
#else
PUBLIC S16 cmPAsnDecUnconIntXL (msgCp, len, val)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U8           len;      /* Number of octets */
U8           *val;     /* Return integer value */
#endif
{

  U8    idx;           /* index */ 
  S16   ret;

  TRC2(cmPAsnDecUnconIntXL)

  /* Read "len" number of octets as value */
  for (idx = 0; idx < len; idx++)
  {
     if (msgCp->perType == CM_PASN_USE_UALIGN)
     {
      /* cm_pasn4_c_001.main_21 : kwork fix */
       ret = cmPAsnDecBitField(msgCp, &val[idx], CM_PASN_VAL_EIGHT);
       if (ret != ROK)
          RETVALUE(RFAILED);
     }
     else
     {
        CM_PASN_DEC_BYTE(msgCp, val[idx]);
     }
  } 

  RETVALUE(ROK);
} /* End of cmPAsnDecUnconIntXL */



/*
*
*       Fun:   cmPAsnDecSemiConInt
*
*       Desc:  This function Decodes Semi Constrained Integer Value
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnDecSemiConInt
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          len,       /* Number of octets */ 
U32          min,       /* Lower bound on value */
U32          *val,      /* Location to place integer value */
Bool         isSigned   /* Is the integer signed */    
)
#else
PUBLIC S16 cmPAsnDecSemiConInt (msgCp, len, min, val,isSigned)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          len;      /* Number of octets */
U32          min;      /* Lower Bound on value */
U32          *val;     /* Location to place integer value */
Bool         isSigned; /* Is the integer signed */
#endif
{

  U8    unPkArray[CM_PASN_FOUR_OCTETS]={0};       /* To store octets */
  U8    i;                                    /* index */ 
  U32   value;                                /* Integer Value */

  TRC2(cmPAsnDecSemiConInt)

  /* Patch - cm_pasn4_c_001.main_13 */
  /* Verify the size of unPkArray */
  if (len > 4)
     RETVALUE(RFAILED);

  /* Read "len" number of octets as value */
  for( i=0; i < (U8)len; i++)
  {
     if (msgCp->perType == CM_PASN_USE_UALIGN)
     {
      /* cm_pasn4_c_001.main_21 : kwork fix */
       S16 ret;
		 ret = cmPAsnDecBitField(msgCp,&unPkArray[i],CM_PASN_VAL_EIGHT);
       if(ret!= ROK)
       RETVALUE(RFAILED);
     }
     else
     {
        CM_PASN_DEC_BYTE(msgCp,unPkArray[i]);
     }
  } 

  value = (U32)(unPkArray[0]); 
  for( i=1; i< (U8)len; i++)
      value = (U32)((value << CM_PASN_VAL_EIGHT) | unPkArray[i]);

  /* Add min to it to get exact integer value */
  if( !isSigned)
     *val = (U32)(value + min);
  else
     *val = (U32)((S32)value + (S32)min);
   
  /* Validate that the decoded value is within expected range */
  if (((!isSigned) && (*val < min)) || 
        ((isSigned) && ((S32)(*val) < (S32)min)))
  {
      CM_PASN_ERR(msgCp, CM_PASN_OUT_RANGE);
      RETVALUE(RFAILED);
  } 

  RETVALUE(ROK);

} /* End of cmPAsnDecSemiConInt */


/*
*
*       Fun:   cmPAsnDecSemiConIntXL
*
*       Desc:  This function Decodes Semi Constrained Integer Value
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnDecSemiConIntXL
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U8           *lBound,   /* Lower bound on value */
U8           lbLen,     /* Length of the lower bound */ 
U8           *val,      /* Decoded value */
U8           *len       /* Length of the decoded value */ 
)
#else
PUBLIC S16 cmPAsnDecSemiConIntXL (msgCp, lBound, lbLen, val, len)
CmPAsnMsgCp  *msgCp;    /* message control pointer */
U8           *lBound;   /* Lower bound on value */
U8           lbLen;     /* Length of the lower bound */ 
U8           *val;      /* Decoded value */
U8           *len;      /* Length of the decoded value */ 
#endif
{

   U8    idx;            /* index */ 
   S16   ret;

   TRC2(cmPAsnDecSemiConIntXL)

   /* Read "len" number of octets as value */
   for (idx = 0; idx < *len; idx++)
   {
      if (msgCp->perType == CM_PASN_USE_UALIGN)
      {
      /* cm_pasn4_c_001.main_21 : kwork fix */
          ret = cmPAsnDecBitField(msgCp, &val[idx], CM_PASN_VAL_EIGHT);
			 if (ret!= ROK)
          RETVALUE(RFAILED);
      }
      else
      {
         CM_PASN_DEC_BYTE(msgCp, val[idx]);
      }
   } 

   {
      U8          v[CM_PASN_UINTXL_SIZE];
      U8          vLen;

      vLen = *len;
      for (idx = 0; idx < vLen; idx++)
         v[idx] = val[idx];

      cmPAsnAddUIntXL(v, vLen, lBound, lbLen, val, len);
#if 0 /* TODO remove */
      CM_PASN_ADD_INTXL(v, vLen, lBound, lbLen, val, *len);
#endif
   }

  RETVALUE(ROK);

} /* End of cmPAsnDecSemiConIntXL*/



/*
*
*       Fun:   cmPAsnChkMandMis 
*
*       Desc:  This function checks whether an element is mandatory. 
*
*       Ret:   TRUE (if element is mandatory)
*              FALSE (if element invalid or optional)
*
*       Notes: None 
*
*       File:  cm_pasn4.c
*
*/
  
#ifdef ANSI
PUBLIC Bool cmPAsnChkMandMis
(
CmPAsnMsgCp  *msgCp  /* message control pointer */
)
#else
PUBLIC Bool cmPAsnChkMandMis (msgCp)
CmPAsnMsgCp  *msgCp; /* message control pointer */
#endif
{
   CmPAsnElmDef   *elmDef;     /* pointer to element defintion */
   U8           flag;          /* flag */

   TRC2 (cmPAsnChkMandMis)
  
   /* Look for any mandatory IE in the remaining database */
 
   while(*(msgCp->elmDef) != (CmPAsnElmDef*) NULLP)
   {
      /* get the element defintion for this element */
      elmDef = *msgCp->elmDef;

      /* Check the element as Mandatory/Optional/Invalid */
      flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);

      /* if element is mandatory, return true */
      /* treat ignorable mandatory elements as mandatory elements during 
      * the decode */
      if ((flag == CM_PASN_ELM_MAND) || (flag == CM_PASN_ELM_MANDIGN))
         RETVALUE(TRUE);

      /* Skip to the next element */ 
      CM_PASN_SKIP_ELM(msgCp);
   
   }
 
   RETVALUE(FALSE);

} /* End of cmPAsnChkMandMis */



/*
*
*      Fun:   cmPAsnDecChkFlag
*
*      Desc:  This routine checks if an element is defined for the
*             protocol being defined.
*
*      Ret:   ROK       - element defined by the protocol
*             RFAILED   - element is not defined for the protocol. 
*
*      Notes: None
*
*      File:  cm_pasn4.c
*
*/
 
#ifdef ANSI
PUBLIC S16 cmPAsnDecChkFlag
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PUBLIC S16 cmPAsnDecChkFlag(msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
   CmPAsnElmDef   *elmDef;      /* element definition */
   U8             flag;           /* protocol flag */

   TRC2(cmPAsnDecChkFlag)

   elmDef = *msgCp->elmDef;        /* get the element defintion */ 

   /* Check the element as Mandatory/Optional/Invalid */
   flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);

   /* check if the element is defined for this protocol */ 
   if (flag == CM_PASN_ELM_INV)
      RETVALUE(RSKIP);
   
   RETVALUE(ROK);

} /* end of cmPAsnDecChkFlag */

/*cm_pasn4_c_001.main_18*/
/*
*
*       Fun:   cmPAsnUpdDefVal
*
*       Desc:  This function gets the default value. 
*
*       Ret:   ROK
*
*       Notes: 
*
*       File:  cm_pasn2.c
*
*/

#ifdef ANSI
PUBLIC Void cmPAsnUpdDefVal
(
TknU8         *evntStr,
CmPAsnElmDef  *temp_elm
)
#else
PUBLIC Void cmPAsnUpdDefVal (evntStr, temp_elm)
TknU8         *evntStr;
CmPAsnElmDef  *temp_elm;
#endif
{
   TRC2(cmPAsnUpdDefVal)

   switch(temp_elm->type)
   {
      /*Update value*/
     /* cm_pasn4_c_001.main_19 - Correcting typecast issues */
     case CM_PASN_TET_SINT8 :
        ((TknS8 *)(evntStr))->val = (PTR)((S8 *)(temp_elm->defVal));
        break;

     case CM_PASN_TET_SINT16 :
        ((TknS16 *)(evntStr))->val = (PTR)((S16 *)(temp_elm->defVal));
        break;

     case CM_PASN_TET_SINT32 :
        ((TknS32 *)(evntStr))->val = (PTR)((S32 *)(temp_elm->defVal));
        break;

     case CM_PASN_TET_BOOL :
     case CM_PASN_TET_UINT8 :
        ((TknU8 *)(evntStr))->val = (PTR)((U8 *)(temp_elm->defVal));
        break;

     case CM_PASN_TET_UINT16 :
        ((TknU16 *)(evntStr))->val = (PTR)((U16 *)(temp_elm->defVal));
        break;

     case CM_PASN_TET_UINT32 :
        ((TknU32 *)(evntStr))->val = (PTR)(U32 *)(temp_elm->defVal);
        break;
     case CM_PASN_TET_ENUM:
        ((TknU32 *)(evntStr))->val = (PTR)(U32 *)(temp_elm->defVal);
        break;
     default:
        evntStr->pres = NOTPRSNT;
        break;
   }
}


/*
*
*      Fun:   cmPAsnDecSeqComp
*
*      Desc:  This routine decodes Sequence/Set Data
*             type components in extension root 
*
*      Ret:   ROK       - element defined by the protocol
*             RFAILED   - element is not defined for the protocol. 
*
*      Notes: None
*
*      File:  cm_pasn4.c
*
*/
 
#ifdef ANSI
PUBLIC S16 cmPAsnDecSeqComp
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          preAmLen   /* Preamble length */
)
#else
PUBLIC S16 cmPAsnDecSeqComp(msgCp, preAmLen)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          preAmLen; /* Preamble Length */
#endif
{
   U8               flag;        /* Flag */
   U8               byte;        /* One byte value */
   S16              ret;         /* return value */
   CmPAsnElmDef     *elmDef;     /* Element definition */ 
   TknU8            *savEvntPtr; /* Saved event ptr */
   CmPAsnElmDef     **savElmPtr; /* Saved elm def ptr */ 

   TRC2(cmPAsnDecSeqComp)

      elmDef = *msgCp->elmDef;
   savElmPtr = msgCp->elmDef;
   savEvntPtr = msgCp->evntStr;

   if( preAmLen <= CM_PASN_VAL_64K)
   {
      /* No fragmentation */
      while( (elmDef->type != CM_PASN_TET_SETSEQ_TERM) &&
            (elmDef->type != CM_PASN_TET_EXT_MKR) )
      {
         /* Find what type of element is it */
         flag = CM_PASN_GET_FLAGS(elmDef->flagp, 
               msgCp->protType);
         if( (flag ==  CM_PASN_ELM_OPT) ||
               (flag == CM_PASN_ELM_DEF) )
         {
            /* Read corresponding bit in preamble */
				ret = cmPAsnDecBitField(msgCp, &byte,
                        CM_PASN_VAL_ONE);
            if(ret!= ROK)
               RETVALUE(RFAILED);

            if( byte & CM_PASN_BYTE_LSBONE)
               /* Set present flag */
               msgCp->evntStr->pres = PRSNT_NODEF;
            else
               msgCp->evntStr->pres = NOTPRSNT;
         }

         /* Skip to next element  */
         CM_PASN_SKIP_ELM(msgCp);
         elmDef = *msgCp->elmDef;
      } /* End while */

      /* Reset elmDef, evntStr pointers to start of */
      /* components */
      CM_PASN_RESET_MSGCP_PTR(msgCp, savElmPtr, savEvntPtr); 
      elmDef = *msgCp->elmDef; 

      /* Begin decoding each component */
      while( (elmDef->type != CM_PASN_TET_SETSEQ_TERM) &&
            (elmDef->type != CM_PASN_TET_EXT_MKR) )
      {
         /* Find what type of element is it */
         flag = CM_PASN_GET_FLAGS(elmDef->flagp, 
               msgCp->protType);
         if( (flag ==  CM_PASN_ELM_OPT) ||
               (flag == CM_PASN_ELM_DEF) )
         {
            /* Check it's present flag */
            if( msgCp->evntStr->pres != PRSNT_NODEF)
            {
               /* RRC2.0
                * fill in default value */
               if(CM_PASN_ELM_OPT == flag)
               {
                  CM_PASN_SKIP_ELM(msgCp); 
               }
               else
               {
                  /* Check the value Decode the default value */
                  CmPAsnElmDef *temp_elm;

#ifdef CM_PASN_DBG
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoding Element %s\n",
               elmDef->str) );
#endif /* CM_PASN_DBG */
  
                  /* Set present flag */
                  msgCp->evntStr->pres = PRSNT_NODEF;
                  temp_elm = *msgCp->elmDef;
                  /*cm_pasn4_c_001.main_18*/
                  cmPAsnUpdDefVal(msgCp->evntStr, temp_elm);
                  CM_PASN_SKIP_ELM(msgCp); 
               }
            }
            else
            {
               if( (ret = cmPAsnDecElm(msgCp) )!= ROK)
                  RETVALUE(RFAILED);
            }
         }
         else
         { 
            /* Mandatory or Invalid element */
            /* Check on Invalid is made in elment Decoding*/
      /* cm_pasn4_c_001.main_21 : kwork fix */
				ret = cmPAsnDecElm(msgCp);
            if(ret!= ROK)
               RETVALUE(RFAILED);
         }
         
         /* Skip to next element  */
        /* CM_PASN_SKIP_ELM(msgCp);*/
         elmDef = *msgCp->elmDef;
      } /* End while */

   } /* End if preamble is less than 64K */ 

   RETVALUE(ROK);

} /* End of cmPAsnDecSeqComp */



/*
*
*      Fun:   cmPAsnDecSeqExt
*
*      Desc:  This routine decodes Sequence/Set Data
*             type components in extension range
*
*      Ret:   ROK       - element defined by the protocol
*             RFAILED   - element is not defined for the protocol. 
*
*      Notes: None
*
*      File:  cm_pasn4.c
*
*/
 
#ifdef ANSI
PUBLIC S16 cmPAsnDecSeqExt
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          noEncExt,  /* Number of encoded extensions */
U32          noDBExt    /* Number of ext in database */
)
#else
PUBLIC S16 cmPAsnDecSeqExt(msgCp, noEncExt, noDBExt)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          noEncExt; /* Number of extensions */
U32          noDBExt;  /* NUmber of ext in database */
#endif
{
  U8         byte;          /* To store bit fields */
  S16        ret;           /* Return value */
  U32        ctr;           /* Loop variable */
  U32        noDecExt;      /* Number of extensions to decode */
  CmPAsnElmDef **savElmDef; /* saved Element definition */
  TknU8      *savEvntPtr;   /* Saved event str */ 
  U32        noActEncExt;   /* no.of actual encoded extensions */
  /* cm_pasn4_c_001.main_20:Added support for extension addition
   *  groups for unaligned PER*/ 
  U8         flag;          /* Flag */
  CmPAsnElmDef *eDef;       /* Element definition */

  TRC2(cmPAsnDecSeqExt)

  savElmDef = msgCp->elmDef;
  savEvntPtr = msgCp->evntStr;
  noActEncExt = 0;

  if(noEncExt >= noDBExt)
     /* Decode only database extensions */
     noDecExt = noDBExt; 
  else
     /* Decode only encoded extensions */
     noDecExt = noEncExt; 

  /* code changes to handle extra extensions */
  for( ctr=0; ctr < noEncExt; ctr++)
  {
     /* Read presence/absence bit in bit field */
      /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = cmPAsnDecBitField(msgCp, &byte, CM_PASN_VAL_ONE);
     if(ret != ROK)
        RETVALUE(RFAILED);
 
     if( byte & CM_PASN_BYTE_LSBONE)
     {
        noActEncExt++;
        if (ctr < noDecExt)
        {
           msgCp->evntStr->pres = PRSNT_NODEF;
        }
     }
     else
     {
        if (ctr < noDecExt)
        {
           /* cm_pasn4_c_001.main_20:Added support for extension addition
            *  groups for unaligned PER*/ 
           eDef = *msgCp->elmDef;

           flag = CM_PASN_GET_FLAGS(eDef->flagp, msgCp->protType);
           if ((flag != CM_PASN_ELM_OPT) && (flag != CM_PASN_ELM_DEF))
           {
              CM_PASN_ERR(msgCp, CM_PASN_MAND_MIS);
              RETVALUE(RFAILED);
           }
 
           msgCp->evntStr->pres = NOTPRSNT;
        }
     }

     if (ctr < noDecExt)
     {
        /* Skip over to next element */ 
        CM_PASN_SKIP_ELM(msgCp);
     }
  }

  if (noDBExt > noDecExt)
  {
     /* we need to set the pres field to false for the rest of the 
      * elements if the no.of extensions received in the incoming msg 
      * is less than what we have in the database */
     for (ctr = 0; ctr < (noDBExt - noDecExt); ctr ++)
     {
        msgCp->evntStr->pres = NOTPRSNT;
        /* Skip over to next element */ 
        CM_PASN_SKIP_ELM(msgCp);
     }
  }

  /* Reset elmDef and evntStr to start of extension */
  /* Components */
  CM_PASN_RESET_MSGCP_PTR(msgCp, savElmDef, savEvntPtr);

  /* Begin decoding encoded components */
  for( ctr =0; ctr < noDecExt; ctr++)
  {
     if(msgCp->evntStr->pres == PRSNT_NODEF)
     {
        /* Decode the element as Open Type */
        /* Element is skipped there itself */
        /* after decode */
      /* cm_pasn4_c_001.main_21 : kwork fix */
		  ret = cmPAsnDecOTElm(msgCp);
        if(ret!= ROK)
           RETVALUE(RFAILED);
        noActEncExt--;
     }
     else
        /* Skip the element */
        CM_PASN_SKIP_ELM(msgCp);
  }

  if( noActEncExt > 0)
  {
     /* Skip encodings of excess extensions as open */
     /* types from mBuf for elements which are not */
     /* supported in DB as extension additions */
     for( ctr =0; ctr < noActEncExt; ctr++)
     {
      /* cm_pasn4_c_001.main_21 : kwork fix */
        ret = cmPAsnSkipOTVal(msgCp);
		  if(ret != ROK)
           RETVALUE(RFAILED); 
     }
  }

  RETVALUE(ROK);

} /* End of cmPAsnDecSeqExt */
 


/*
*
*      Fun:   cmPAsnDecChComp
*
*      Desc:  This routine decodes a choice alternative in 
*             extension root 
*
*      Ret:   ROK       - element defined by the protocol
*             RFAILED   - element is not defined for the protocol. 
*
*      Notes: None
*
*      File:  cm_pasn4.c
*
*/
 
#ifdef ANSI
PUBLIC S16 cmPAsnDecChComp
(
CmPAsnMsgCp  *msgCp   /* message control pointer */
)
#else
PUBLIC S16 cmPAsnDecChComp(msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  S16               ret;        /* return value */
  U32               val;        /* Choice Index */
  U16               ctr;        /* Counter value */
  TknU8             *evntStr;   /* Event structure ptr */
  CmPAsnElmDef      *elmDef;    /* Element definition */  
  CmPAsnChoiceDef   *specDef;   /* Choice specific define */

  TRC2(cmPAsnDecChComp)

  elmDef = *msgCp->elmDef;
  specDef = (CmPAsnChoiceDef *)elmDef->typeSpecDef;
  evntStr = (TknU8 *)msgCp->evntStr;

  /* check if mBuf is NULL */
  if(msgCp->mBuf == NULLP)
  {
#ifdef CM_PASN_DBG
     CM_PASN_DBGP(msgCp, 
                 (msgCp->prntBuf,"mBuf while decoding %s is Null\n",
                  elmDef->str) );
#endif /* CM_PASN_DBG */
  
     RETVALUE(RFAILED);
  }

  /* Decode choice index encoded as Constrained integer */
  /* choice index is not encoded if only one alternative */ 
  if( specDef->nmbAltRoot != CM_PASN_VAL_ONE)
  {
      /* cm_pasn4_c_001.main_21 : kwork fix */
     ret = cmPAsnDecConInt(msgCp, CM_PASN_VAL_NULL, 
                   (specDef->nmbAltRoot - 1), &val, FALSE);
	  if(ret != ROK)
     RETVALUE(RFAILED);
  }
  else
     /* Choice index is 0 */
     val = CM_PASN_VAL_NULL;

  /* Update choice index in event structure */
  CM_PASN_FILL_EVNT(evntStr, (U8)val);

#ifdef CM_PASN_DBG
  /* cm_pasn4_c_001.main_19 - correcting compilation issues */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded overall Choice Index Value %d\n",
               val) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded overall Choice Index Value %ld\n",
               val) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

  /* Increment to first alt definition  */
  msgCp->elmDef = specDef->ft;
  
  /* Increment event structure pointer over choiceIdx */
  msgCp->evntStr = (TknU8 *)((PTR) msgCp->evntStr +
                                    sizeof(TknU8));
  evntStr = msgCp->evntStr;

  /* Skip to the DB and event definition of the alternative */
  for( ctr =0; ctr < (U8)val; ctr++) 
  {
     CM_PASN_SKIP_ELM(msgCp);
     /* Reset  event structure ptr as it is a union */
     msgCp->evntStr = evntStr;
  }

  /* Now decode the alternative */
      /* cm_pasn4_c_001.main_21 : kwork fix */
  ret = cmPAsnDecElm(msgCp);
  if(ret != ROK)
     RETVALUE(RFAILED);

  RETVALUE(ROK);

} /* End of cmPAsnDecChComp */


/*
*
*      Fun:   cmPAsnDecChExt
*
*      Desc:  This routine decodes a choice alternative in 
*             extension range 
*
*      Ret:   ROK       - element defined by the protocol
*             RFAILED   - element is not defined for the protocol. 
*
*      Notes: None
*
*      File:  cm_pasn4.c
*
*/
 
#ifdef ANSI
PUBLIC S16 cmPAsnDecChExt
(
CmPAsnMsgCp  *msgCp   /* message control pointer */
)
#else
PUBLIC S16 cmPAsnDecChExt(msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  U16            ctr;         /* Loop variable */
  S16            ret;         /* Return value */
  S32            val;         /* Integer value */
  TknU8          *evntStr;    /* Event structure  */ 
  CmPAsnElmDef   *elmDef;     /* Element definition */
  CmPAsnChoiceDef *specDef;   /* Choice specific definition */

  TRC2(cmPAsnDecChExt)

  evntStr = (TknU8 *)msgCp->evntStr;
  elmDef = *msgCp->elmDef;
  specDef = (CmPAsnChoiceDef *)elmDef->typeSpecDef;

  /* Decode choiceIdx encoded as Normally Small */
      /* cm_pasn4_c_001.main_21 : kwork fix */
  ret = cmPAsnDecSmallInt(msgCp, &val);
  if(ret != ROK)
     RETVALUE(RFAILED); 

#ifdef CM_PASN_DBG
  /* cm_pasn4_c_001.main_19 - correcting compilation issues */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded overall ChoiceIndex Value %d\n",
               (val + specDef->nmbAltRoot)) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded overall ChoiceIndex Value %ld\n",
               (val + specDef->nmbAltRoot)) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

  /* Check if our database supports this extension */
  if( val >= specDef->nmbAltExt)
  {
     /* Skip Open Type value in mBuf */
      /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = cmPAsnSkipOTVal(msgCp);
     if(ret!= ROK)
         RETVALUE(RFAILED);

     RETVALUE(ROK);
  }

  /* Find the offset from the beginining for choice Idx */
  CM_PASN_FILL_EVNT(evntStr, (U8)(val+ specDef->nmbAltRoot));

  /* Increment event structure pointer over choiceIdx */
  msgCp->evntStr = (TknU8 *)((PTR) msgCp->evntStr +
                                    sizeof(TknU8));
  evntStr = msgCp->evntStr;

  /* Increment DB defiition to point to first alt */
  /* Over choice DB */
  msgCp->elmDef = specDef->ft;

  /* Skip elements DB to reach the encoded alternative DB */
  /* Also need to skip extension marker DB definition */ 
  for( ctr =0; ctr <= (U16)(val+specDef->nmbAltRoot); ctr++)
  {
     /* Skip element */
     CM_PASN_SKIP_ELM(msgCp);

     /* Revert eventstr pointer as it is a union */
     msgCp->evntStr = evntStr; 
  }

  /* Decode the reached element as Open Type */
      /* cm_pasn4_c_001.main_21 : kwork fix */
  ret = cmPAsnDecOTElm(msgCp);
  if(ret != ROK)
     RETVALUE(RFAILED);

 RETVALUE(ROK);

} /* End of cmPAsnDecChExt */ 



/*
*
*      Fun:   cmPAsnSkipOTVal
*
*      Desc:  This routine skips open type 
*             extension values in Message Buffer
*
*      Ret:   ROK       - element defined by the protocol
*             RFAILED   - element is not defined for the protocol. 
*
*      Notes: None
*
*      File:  cm_pasn4.c
*
*/
 
#ifdef ANSI
PUBLIC S16 cmPAsnSkipOTVal
(
CmPAsnMsgCp  *msgCp   /* message control pointer */
)
#else
PUBLIC S16 cmPAsnSkipOTVal(msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  U8   fragFlag;     /* Fragmentation */
  U8   byte;         /* To store bit field */
  S16  ret;          /* Return value */
  U32  ctr;          /* Loop variable */ 
  U32  len;          /* Length determinant value */

  TRC2(cmPAsnSkipOTVal)

  fragFlag = FALSE;

  /* Find unconstrained length determinant */
      /* cm_pasn4_c_001.main_21 : kwork fix */
  ret = cmPAsnDecUnconLen(msgCp, &len,&fragFlag);
  if(ret!= ROK)
     RETVALUE(RFAILED);

  if( !fragFlag)
  {
     /* No fragmentation */
     if (msgCp->perType == CM_PASN_USE_ALIGN)
     { 
     /* Get to next octet boundary for start of */
     /* open type value */
     CM_PASN_SKIP_PADBITS(msgCp);
     }
     /* Now skip len number of octets */ 
     for( ctr =0; ctr < len; ctr++)
     {
       if (msgCp->perType == CM_PASN_USE_UALIGN)
       {
      /* cm_pasn4_c_001.main_21 : kwork fix */
       ret = cmPAsnDecBitField(msgCp,&byte,CM_PASN_VAL_EIGHT);
       if(ret != ROK)
       RETVALUE(RFAILED);
       }
       else
       {
          CM_PASN_DEC_BYTE(msgCp, byte);
       }
     }
  }
  else
  {
     /* Open type value is fragmented */
     /* Skip len*16K octets first */
     for( ctr =0; ctr < (len * CM_PASN_VAL_16K); ctr++)
     {
       if (msgCp->perType == CM_PASN_USE_UALIGN)
       {
  if( (ret = cmPAsnDecBitField(msgCp,&byte,CM_PASN_VAL_EIGHT)) != ROK)
     RETVALUE(RFAILED);
       }
       else
       {
          CM_PASN_DEC_BYTE(msgCp, byte);
       }
     }

    /* Call this function recursively till */
    /* fragment with less than 16K items is */
    /* reached */ 
      /* cm_pasn4_c_001.main_21 : kwork fix */
	 ret = cmPAsnSkipOTVal(msgCp);
    if(ret != ROK)
        RETVALUE(RFAILED);

  }

 RETVALUE(ROK);

} /* End of cmPAsnSkipOTVal */



/*
*
*       Fun:   cmPAsnDecStrLen
*
*       Desc:  This function Decodes Bit and Octet 
*              string  Data Types Length field 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnDecStrLen
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          min,       /* Minimum length */
U32          max,       /* Maximum Length */
U32          *len,      /* Location to place length */
Bool         *frag      /* Fragmentation Flag */
)
#else
PUBLIC S16 cmPAsnDecStrLen(msgCp, min, max, len, frag)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          min;      /* Minimum length */
U32          max;      /* Maximum Length */
U32          *len;     /* Location to place length */
Bool         *frag;    /* Fragmentation Flag */
#endif
{
  U8                 byte;     /* To store bit field */
  S16                ret;      /* Return value */
  CmPAsnElmDef       *elmDef;  /* Element definition */

  TRC2(cmPAsnDecStrLen)

  elmDef = *msgCp->elmDef;

  /* cm_pasn4_c_001.main_19 - Moving the len update to this function. */
  /* Initialize the len variable */
  *len = 0;

  if(elmDef->extMkr)
  {
    /* Decode extension bit */
      /* cm_pasn4_c_001.main_21 : kwork fix */
	 ret = cmPAsnDecBitField(msgCp, &byte, CM_PASN_VAL_ONE);
    if(ret != ROK)
      RETVALUE(RFAILED);
  
    if( byte & CM_PASN_BYTE_LSBONE)
    {
      /* Decode length encoded as Semi Constrained Number */
      /* i.e as Section 10.9.3.5 of ITU X-691 */ 
      /* cm_pasn4_c_001.main_21 : kwork fix */
		ret = cmPAsnDecUnconLen(msgCp, len, frag);
      if(ret != ROK)
         RETVALUE(RFAILED);

       RETVALUE(ROK);
    }
  }

  /* If extension bit is 0 or no extension bit */
  /* Decode length for cases it is encoded */ 
  if((max != min) && ( max ))
  {
     if((max != CM_PASN_PLUS_INF) &&
                 (max < CM_PASN_VAL_64K) )
     {
        /* Decode length as Constrained Integer */
      /* cm_pasn4_c_001.main_21 : kwork fix */
		  ret = cmPAsnDecConLen(msgCp,len,min,
                            max, frag);
        if(ret != ROK)
           RETVALUE(RFAILED); 
        if (msgCp->perType == CM_PASN_USE_ALIGN)
        {
   /* Octet align for further decoding */
   CM_PASN_SKIP_PADBITS(msgCp);
        }
     }
     else
     {
        /* Decode length as Unconstrained Integer */
      /* cm_pasn4_c_001.main_21 : kwork fix */
		  ret = cmPAsnDecUnconLen(msgCp, len, frag);
        if(ret != ROK)
           RETVALUE(RFAILED);
     }
  }
  
  /* cm_pasn4_c_001.main_19 - Moving the len update to this function. */
  /* Update length in event structure */
  else if((min == max) || ( !max) )
  {
     *len = max; 
  }

  /* Validate the received octet string length */
  if( (max != CM_PASN_PLUS_INF) && (*len > (U16)max) ) 
  {
     RETVALUE(RFAILED);
  }

  RETVALUE(ROK);

} /* End of cmPAsnDecStrLen */



/*
*
*       Fun:   cmPAsnDecStrVal
*
*       Desc:  This function Decodes Bit and Octet 
*              string  Data Types value 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn4.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnDecStrVal
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          len,       /* Length of string */
U32          min,       /* Minimum length */
U32          max,       /* Maximum Length */
U8           strType    /* string type */
)
#else
PUBLIC S16 cmPAsnDecStrVal(msgCp, len,min, max,strType)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          len;      /* Length of the string */ 
U32          min;      /* Minimum length */
U32          max;      /* Maximum Length */
U8           strType;  /* string type */
#endif
{
  Bool         octAlign;   /* If octet alignment done */
  Bool         isXlStr;    /* Is it an extra large string */ 
  U8           multiplier; /* Number of bits per byte */
  U8           byte;       /* To store bit field */
  U8           noBits;     /* Number of bits */
  S16          ret;        /* Return value */
  U16          noBytes;    /* Number of bytes */
  U16          memSize;    /* Memory size in bytes */
  U16          i;          /* Loop variable */
  TknStr4      *evntStr;   /* Event structure */
  TknStrOSXL   *xlStr;     /* Extra Large OS/BS event */
  CmPAsnElmDef *elmDef;    /* Element definition */

  TRC2(cmPAsnDecStrVal)

  isXlStr = FALSE;
  elmDef = *msgCp->elmDef;
  evntStr = (TknStr4 *)msgCp->evntStr;
  xlStr = (TknStrOSXL *)msgCp->evntStr;
  noBits = 0;

  if( (elmDef->type == CM_PASN_TET_OCTSTRXL) ||
      (elmDef->type == CM_PASN_TET_BITSTRXL) )
     isXlStr = TRUE;
 
  if (msgCp->perType == CM_PASN_USE_UALIGN)
  {
     multiplier = CM_PASN_VAL_ONE;
  }
  else
  {
     if( strType == CM_PASN_BITSTR_TYPE)
multiplier = CM_PASN_VAL_ONE;
     else 
multiplier = CM_PASN_VAL_EIGHT; 
  }

  if( !max)
     /* No encoding */
     RETVALUE(ROK);
  
  if (msgCp->perType == CM_PASN_USE_UALIGN)
  {
     if( strType == CM_PASN_BITSTR_TYPE)
     {
/* obtain noBytes by dividing with 8 */ 
noBytes = (U16)(len >> CM_PASN_VAL_THREE);
noBits = len % CM_PASN_VAL_EIGHT; 

if( noBits)
   memSize = noBytes+1;
else
   memSize = noBytes;
     }
     else 
     {
noBytes = len;
memSize = len;
     }
     if(isXlStr)
     {
/* Event structure needs to be allocated for this */
      /* cm_pasn4_c_001.main_21 : kwork fix */
ret = cmGetMem((Ptr)msgCp->memCp,(Size)memSize,(Ptr *)&(xlStr->val));

if(ret != ROK)
   RETVALUE(RFAILED);
     }
    
     for( i =0; i < noBytes; i++)
     {
     if( isXlStr)
     {
      /* cm_pasn4_c_001.main_21 : kwork fix */
     ret = cmPAsnDecBitField(msgCp,&(xlStr->val[i]),CM_PASN_VAL_EIGHT);
if(ret != ROK)
  RETVALUE(RFAILED);
     }
     else
     {
      /* cm_pasn4_c_001.main_21 : kwork fix */
     ret = cmPAsnDecBitField(msgCp,&(evntStr->val[i]),CM_PASN_VAL_EIGHT);
     if(ret!= ROK)
      RETVALUE(RFAILED);
     }

      }

     /* Fix done by vikas  for test cases 020 */

     if( strType == CM_PASN_BITSTR_TYPE && (noBits > 0) )
     {
/* Now decode the remaining bits */
/* Bit Field function expects these bits as LSB */
      /* cm_pasn4_c_001.main_21 : kwork fix */
ret = cmPAsnDecBitField(msgCp, &byte,noBits);
if(ret != ROK)
     RETVALUE(RFAILED); 
    
/* Move these bits at MSB for continuous Bit Str */
if( !isXlStr)
   evntStr->val[noBytes] = (byte << (CM_PASN_VAL_EIGHT - noBits)); 
else
   xlStr->val[noBytes] = (byte << (CM_PASN_VAL_EIGHT - noBits));

     }
  }
  else
  {
     if(max == min)
     {
/* len is already set to max */
if( max * multiplier <= CM_PASN_VAL_SIXTEEN) 
   octAlign = FALSE;
else
{
   /* Do Octet allign */
   CM_PASN_SKIP_PADBITS(msgCp);
   octAlign = TRUE;
}
     }
     else
/* Octet alignment already done */
octAlign = TRUE; 

     /* Begin decoding bit/byte into message buffer */
     if( strType == CM_PASN_BITSTR_TYPE)
     {
/* obtain noBytes by dividing with 8 */ 
noBytes = (U16)(len >> CM_PASN_VAL_THREE);
noBits = len % CM_PASN_VAL_EIGHT; 

if( noBits)
   memSize = noBytes+1;
else
   memSize = noBytes;
     }
     else 
     {
noBytes = len;
memSize = len;
     }

     if(isXlStr)
     {
/* Event structure needs to be allocated for this */
      /* cm_pasn4_c_001.main_21 : kwork fix */
ret = cmGetMem((Ptr)msgCp->memCp,(Size)memSize, 
 (Ptr *)&(xlStr->val));

if(ret!= ROK)
{ 
    CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
    RETVALUE(RFAILED);
}
     }
    
     for( i =0; i < noBytes; i++)
     {
/* If no octet allignment, add as bit field */
if( !octAlign)
{
   /* This is the case for octet strings of */
   /* fixed size less than or equal to 2 octets */ 
      /* cm_pasn4_c_001.main_21 : kwork fix */
	ret = cmPAsnDecBitField(msgCp, &(evntStr->val[i]),CM_PASN_VAL_EIGHT);
   if(ret != ROK)
       RETVALUE(RFAILED);
}
else
{
   /* Buffer is already octet alligned */
   /* Bytes can directly be decoded from mBuf */
  if( isXlStr)
  {
     CM_PASN_DEC_BYTE(msgCp, xlStr->val[i]);
  }
  else
  {
     CM_PASN_DEC_BYTE(msgCp, evntStr->val[i]);
  }

       }
     } 

     if( strType == CM_PASN_BITSTR_TYPE)
     {
/* Now decode the remaining bits */
/* Bit Field function expects these bits as LSB */
/* Added condition for noBits not qual to zero */
if (noBits != 0)
{
      /* cm_pasn4_c_001.main_21 : kwork fix */
	ret = cmPAsnDecBitField(msgCp, &byte,noBits);
	if(ret  != ROK)
     RETVALUE(RFAILED); 
       
   /* Move these bits at MSB for continuous Bit Str */
   if( !isXlStr)
      evntStr->val[noBytes] = (byte << (CM_PASN_VAL_EIGHT - noBits)); 
   else
      xlStr->val[noBytes] = (byte << (CM_PASN_VAL_EIGHT - noBits));
}

     }
  }

  RETVALUE(ROK);

} /* End of cmPAsnDecStrVal */



/*
*
*       Fun:   cmPAsnDecRChLen
*
*       Desc:  This function decodes Restricted Character string 
*              Length 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn4.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnDecRChLen
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          *len,      /* Character string length */
U8           b,         /* Number of bits */
U32          aub,       /* pointer to Upper bound */ 
U32          alb        /* Pointer to Lower bound */
)
#else
PUBLIC S16 cmPAsnDecRChLen (msgCp, len,b, aub, alb)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          *len;     /* Character string length */
U8           b;        /* Number of bits */
U32          aub;      /* Upper Bound */
U32          alb;      /* Lower Bound */
#endif
{
  Bool frag;      /* Fragmentation Flag */ 
  S16  ret;       /* Return value */

  TRC2(cmPAsnDecRChLen)

  if( (aub != alb) || ( aub >= CM_PASN_VAL_64K) )
  {
     if(aub < CM_PASN_VAL_64K)
     {
        /* Decode length as Constrained Integer */
      /* cm_pasn4_c_001.main_21 : kwork fix */
		  ret = cmPAsnDecConLen(msgCp,len,
                            alb, aub, &frag);
        if(ret != ROK)
           RETVALUE(RFAILED);
if (msgCp->perType == CM_PASN_USE_ALIGN)
{
   /* Octet allign if b*aub is more than 16 */
   if( (b * aub) >= CM_PASN_VAL_SIXTEEN )
   {
      CM_PASN_SKIP_PADBITS(msgCp);
   }
}
     }
     else
     {
         /* Decode length as Uncon Length */
      /* cm_pasn4_c_001.main_21 : kwork fix */
			ret = cmPAsnDecUnconLen(msgCp, 
                              len, &frag);
         if(ret != ROK)
             RETVALUE(RFAILED); 
         
         if (msgCp->perType == CM_PASN_USE_ALIGN)
         {
     /* Octet allign since b*aub is more than 16 */
     CM_PASN_SKIP_PADBITS(msgCp);
         }
     }
  }
  else
  {
     /* aub is same as alb and is less than 64K */
     /* No length encoding , check for octet allign */
     *len = aub;
     if (msgCp->perType == CM_PASN_USE_ALIGN)
     {
if( (b * aub) >= CM_PASN_VAL_SIXTEEN)
{
  CM_PASN_SKIP_PADBITS(msgCp);
} 
     }
  }

 RETVALUE(ROK);

} /* End of cmPAsnDecRChStrLen */



/*
*
*       Fun:   cmPAsnDecChVal
*
*       Desc:  This function decodes Character value 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn4.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnDecChVal
(
CmPAsnMsgCp        *msgCp,  /* message control pointer */
U8                 b,       /* Number of bits */
U32                len,     /* Length of string  */
CmPAsnMulStrDef    specDef  /* Specific definition */ 
)
#else
PUBLIC S16 cmPAsnDecChVal (msgCp, b, len,specDef)
CmPAsnMsgCp      *msgCp;   /* message control pointer */
U8               b;        /* Number of bits */
U32              len;      /* Length of string */
CmPAsnMulStrDef  specDef;  /* Specific definition */
#endif
{
  U16      i;             /* Loop variable */
  U8      ctr;           /* Loop variable */ 
  U8      noBytes;       /* Number of bytes */
  U8      noBits;        /* Number of bits */
  U8      byte;          /* To store bit fields */ 
  S16     ret;           /* Return value */ 
  U32     v;             /* value of the character */ 
  U32     ubMax;         /* Max limit on upper bound */
  U32     *effAlp;       /* Effective alphabet */
  TknStr4 *evntStr;      /* Event structure */
  CmPAsnElmDef *elmDef;  /* Element definition */
  
  TRC2(cmPAsnDecChVal)
 
  elmDef = *msgCp->elmDef;
  evntStr = (TknStr4 *)msgCp->evntStr;
  noBytes = 0;
  noBits = 0;
  v = 0;

  /* Allocate memory for val in XL event structures */
  switch(elmDef->type)
  {
     case CM_PASN_TET_BMPSTRXL:
        /* Need to allocate memory for val */
        /* Event structure needs to be allocated for this */
      /* cm_pasn4_c_001.main_21 : kwork fix */
		  ret = cmGetMem((Ptr)msgCp->memCp,(Size)(len * sizeof(U16)), 
                   (Ptr *)&( ((TknStrBMPXL *)evntStr)->val));
        if(ret != ROK)
        { 
            CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
            RETVALUE(RFAILED);
        }
        break;
    
    case CM_PASN_TET_UNISTRXL:
       /* Need to allocate memory for val */
      /* cm_pasn4_c_001.main_21 : kwork fix */
		 ret = cmGetMem((Ptr)msgCp->memCp,(Size)(len * sizeof(U32)), 
                   (Ptr *)&( ((TknStrUNIXL *)evntStr)->val));
       if(ret!= ROK)
       { 
           CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
           RETVALUE(RFAILED);
       }
       break;
    
    case CM_PASN_TET_PRNSTRXL:
    case CM_PASN_TET_NUMSTRXL:
    case CM_PASN_TET_IA5STRXL:
    case CM_PASN_TET_VISSTRXL:
    case CM_PASN_TET_GENSTRXL:
       /* Need to allocate memory for val */
      /* cm_pasn4_c_001.main_21 : kwork fix */
		 ret = cmGetMem((Ptr)msgCp->memCp,(Size)len , 
                   (Ptr *)&( ((TknStrOSXL *)evntStr)->val));
       if(ret!= ROK)
       { 
           CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
           RETVALUE(RFAILED);
       }
       break;

    default:
       break;
  }

  if( b > CM_PASN_VAL_EIGHT)
  {
     noBytes = b/CM_PASN_VAL_EIGHT;
     noBits = b % CM_PASN_VAL_EIGHT;
  }

  /* Decode the value v in b bits each */
  for( i=0; i< (U16)len; i++)
  {
     if( b <= CM_PASN_VAL_EIGHT)
     {
        if( (ret = cmPAsnDecBitField(msgCp, 
                                 &byte, b)) != ROK)
           RETVALUE(RFAILED);

        v = (U32)byte;
     }
     else
     {
        for(ctr = 0; ctr < noBytes; ctr++)
        {
      /* cm_pasn4_c_001.main_21 : kwork fix */
           ret = cmPAsnDecBitField(msgCp,
                               &byte, 8);
			  if(ret!= ROK)
              RETVALUE(RFAILED);

           v = ((v << CM_PASN_VAL_EIGHT) | (U32)byte);
        }
  
        if( noBits)
        {         
      /* cm_pasn4_c_001.main_21 : kwork fix */
            ret = cmPAsnDecBitField(msgCp,
                            &byte, noBits);
			  if(ret!= ROK)
              RETVALUE(RFAILED);

           v = ((v << noBits) | (U32)byte);
        }
     }
  
     /* Find the value of 2^b - 1 */
     ubMax = (CM_PASN_VAL_ONE << b) - 1;
  
     if( specDef.ub <= ubMax ) 
     {
        /* Fill the above computed v in event structure */ 
        CM_PASN_UPDATE_RCHVAL(evntStr,elmDef->type,v,i);
     }
     else
     {
        /* v represents index in effective alphabet */
        /* Read actual character value from alphabet */
        /* Find effective alphabet first */
        if( specDef.effAlp != NULLP)
        {
           effAlp = (U32 *)specDef.effAlp;

           /* Fill the character value in event structure */ 
           /* Read character at location v+1, as first one is count */ 
           CM_PASN_UPDATE_RCHVAL(evntStr,elmDef->type, effAlp[v+1],i);
        }
        else
        {
           /* Fill the character value in event structure */ 
           /* Add lb character value to get actual value */  
           CM_PASN_UPDATE_RCHVAL(evntStr,elmDef->type, (v + specDef.lb),
                                 i); 
        }
     } 
        
  }  /* End of loop */
  
  RETVALUE(ROK);

} /* End of cmPAsnDecChVal */

       

/*
*
*       Fun:   cmPAsnFindFragLen
*
*       Desc:  This function Finds Total Length  of 
*              fragmented octet and bit strings 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn4.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnFindFragLen
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          lenVal,    /* length determinant value */
U8           itemLen,   /* length in bits of each item */ 
U32          *totalLen  /* Total Length */
)
#else
PUBLIC S16 cmPAsnFindFragLen (msgCp, lenVal,itemLen,totalLen )
CmPAsnMsgCp  *msgCp;     /* message control pointer */
U32          lenVal;     /* Length determinant value */ 
U8           itemLen;    /* length in bits of each item */
U32          *totalLen;  /* Total Length */ 
#endif
{
  U8    m;             /* value of "m" */
  U8    itemBits;      /* Number of bits to contain itemLen */
  U8    lenOct;        /* Length octet */
  U8    secVal = 0;        /* second unfragmented length */
  U8    noBits;        /* Number of bits */
  MsgLen   idx;           /* Index variable */
  MsgLen   pIdx = 0;          /* Previously used Index variable */
  MsgLen   noBytes;       /* Number of bytes to store items */
  MsgLen   maxOct;        /* Maximum number of octets */ 
  MsgLen   strLen;        /* Total String length */
  MsgLen   nextLen;       /* Next fragment total length */
  MsgLen   unFragLen;     /* Length of last fragment */

  TRC2(cmPAsnFindFragLen)

  itemBits = 0;
  nextLen = 0; 
  strLen = 0;

  /* For Bits, itemLen is 1, so 8K octets contain 64K items */
  /* For octets, itemLen is 8, so 64K octets contain 64k items */
  unFragLen = 0;
  noBits = 0;

  CM_PASN_FIND_ITEMBITS(itemLen,itemBits);

  m = lenVal & CM_PASN_FRAG_CONST3;
  maxOct =  (m * (CM_PASN_VAL_2K << itemBits) );
  strLen = maxOct;
  lenOct = lenVal;

/* cm_pasn4_c_001.main_15 the logic of the below for loop is to check the length
 * field after m*2048 bytes or m*16k bits incase of bit string. For this no
 * need to loop again . So removing the while loop condition.  */ 
  
  {
     idx = maxOct + nextLen;

     /* Patch - cm_pasn4_c_001.main_14 */
     if (idx == pIdx)
     {
#ifdef CM_PASN_DBG
       CM_PASN_DBGP(msgCp,
                   (msgCp->prntBuf,"Leading to Infinite loop path \n"));
#endif /* CM_PASN_DBG */

        RETVALUE(RFAILED);
     }

     strLen += nextLen; 
     CM_PASN_EXAM_BYTE(msgCp, idx, lenOct);
     pIdx = idx;

     idx++;
  } ;
    
  /* Decode the last part of the fragment */
  /* If First bit is 0 */
  if( !(lenOct & CM_PASN_BYTE_MSBONE) )
     unFragLen = lenOct;

  else
  {
     /* If first bit is 1 */
     /* Second bit should be 0 */ 
     if( !(lenOct & CM_PASN_FRAG_CONST2) )
     {
        /* Examine next byte */
        CM_PASN_EXAM_BYTE(msgCp, idx, secVal);
        
        unFragLen = ( (lenOct & CM_PASN_FRAG_CONST3)  
                             << CM_PASN_VAL_EIGHT);
        unFragLen |= (U32)secVal;

     }
  }

  if( itemLen == CM_PASN_VAL_EIGHT)
     noBytes = unFragLen;
  else
  {
     /* obtain noBytes by dividing with 8 */ 
     noBytes = (U16)(unFragLen >> CM_PASN_VAL_THREE);
     noBits = unFragLen % CM_PASN_VAL_EIGHT; 
  }

  /* If BitString, and some spill over bits */
  /* add one more byte */  
  if( (noBits) &&
      (itemLen == CM_PASN_VAL_ONE) )
     noBytes++;

  /* Increment string length */
  strLen += noBytes;

  *totalLen = strLen;

  RETVALUE(ROK);

} /* End of cmPAsnFindFragLen */

       

/*
*
*       Fun:   cmPAsnDecFragVal
*
*       Desc:  This function Decodes Fragmented Length 
*              Determinant and associated values according 
*              to 10.9.3.8 of ITU-T REC X-691 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn4.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnDecFragVal
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          lenVal,    /* length determinant value */
U8           itemLen    /* length in bits of each item */ 
)
#else
PUBLIC S16 cmPAsnDecFragVal (msgCp, lenVal,itemLen )
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          lenVal;   /* Length determinant value */ 
U8           itemLen;  /* length in bits of each item */
#endif
{
  U8    m;             /* value of "m" */
  U8    itemBits;      /* Number of bits to contain itemLen */
  U8    lenOct;        /* Length octet */
  U8    secVal = 0;        /* second unfragmented length */
  U8    noBits;        /* Number of bits */
  U8    byte;          /* One octet long value */
  S16   ret;           /* return value */
  U32   j;             /* 4 octet counter */
  U32   noBytes;       /* Number of bytes to store items */
      /* cm_pasn4_c_001.main_21 : kwork fix */
  U32   maxOct;        /* Maximum number of octets */ 
  U32   totalLen;      /* Total String length */
  U32   nextLen;       /* Length of next fragment */
  U32   unFragLen;     /* Length of last fragment */
  TknStrOSXL  *evntStr; /* Event Structure */ 

  TRC2(cmPAsnDecFragVal)

  unFragLen = 0;
  noBits = 0;
 
  j = 0;
  itemBits = 0;
  nextLen = 0; 
  evntStr = (TknStrOSXL *)msgCp->evntStr;

  /* Calculate the total length of the string */
      /* cm_pasn4_c_001.main_21 : kwork fix */
  ret = cmPAsnFindFragLen(msgCp, lenVal, itemLen,
                              &totalLen );
  if(ret!= ROK )
     RETVALUE(RFAILED);

/* cm_pasn4_c_001.main_15 Adding the Pasn Debg Print for the length field */
#ifdef CM_PASN_DBG
  /* cm_pasn4_c_001.main_19 - correcting compilation issues */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp,
              (msgCp->prntBuf,"Decoded total String of length %d bytes\n",
               totalLen) );
#else
  CM_PASN_DBGP(msgCp,
              (msgCp->prntBuf,"Decoded total String of length %ld bytes\n",
               totalLen) );
#endif /* ALIGN_64BIT */
#endif

  /* Allocate mmemory for the event structure */
      /* cm_pasn4_c_001.main_21 : kwork fix */
  ret = cmGetMem((Ptr)msgCp->memCp,(Size)totalLen, 
							  (Ptr *)&(evntStr->val));

  if(ret != ROK)
  { 
     CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
     RETVALUE(RFAILED);
  }

  /* For Bits, itemLen is 1, so 8K octets contain 64K items */
  /* For octets, itemLen is 8, so 64K octets contain 64k items */

  CM_PASN_FIND_ITEMBITS(itemLen,itemBits);
      /* cm_pasn4_c_001.main_21 : kwork fix */

  m = lenVal & CM_PASN_FRAG_CONST3;
  maxOct =  (m * (CM_PASN_VAL_2K << itemBits) );
  lenOct = lenVal;

  while( lenOct & CM_PASN_FRAG_CONST2)
  {
     for(; j < (U32) (maxOct + nextLen); j++)
     {
        if (msgCp->perType == CM_PASN_USE_UALIGN)
        {
      /* cm_pasn4_c_001.main_21 : kwork fix */
        ret=cmPAsnDecBitField(msgCp,
    &evntStr->val[j],CM_PASN_VAL_EIGHT);
   if(ret!= ROK)
     RETVALUE(RFAILED);
        }
        else
        {
           CM_PASN_DEC_BYTE(msgCp, evntStr->val[j]);
        }
     }

     if (msgCp->perType == CM_PASN_USE_UALIGN)
     {
      /* cm_pasn4_c_001.main_21 : kwork fix */
        ret = cmPAsnDecBitField(msgCp,&lenOct,CM_PASN_VAL_EIGHT);
		  if (ret!= ROK)
           RETVALUE(RFAILED);
     }
     else
     {
        /* Decode next length octet */
         CM_PASN_DEC_BYTE(msgCp,lenOct);
     }
     nextLen += ( (lenOct & CM_PASN_FRAG_CONST3) *
                           (CM_PASN_VAL_2K << itemBits) ); 
  }
 
  /* Decode the last part of the fragment */
  /* If First bit is 0 */
  if( !(lenOct & CM_PASN_BYTE_MSBONE) )
     unFragLen = (U32)lenOct;

  else
  {
     /* If first bit is 1 */
     /* Second bit should be 0 */ 
     if( !(lenOct & CM_PASN_FRAG_CONST2) )
     {
        /* Decode next byte */
        CM_PASN_DEC_BYTE(msgCp, secVal);
        
        unFragLen = (U32)( (lenOct & CM_PASN_FRAG_CONST3)  
                             << CM_PASN_VAL_EIGHT);
        unFragLen |= (MsgLen)secVal;

     }
  }

  if( itemLen == CM_PASN_VAL_EIGHT)
     noBytes = unFragLen;
  else
  {
     /* obtain noBytes by dividing with 8 */ 
     noBytes = (U16)(unFragLen >> CM_PASN_VAL_THREE);
     noBits = unFragLen % CM_PASN_VAL_EIGHT; 
  }
  
  /* Decode noBytes */  
  nextLen = j; 
  for(; j< (nextLen + noBytes); j++)
  {
      CM_PASN_DEC_BYTE(msgCp, evntStr->val[j]); 
  }

  if( (noBits) &&
      (itemLen == CM_PASN_VAL_ONE) )
  {
      /* Decode the remaining bits of bitstring */
     /* Bit Field function expects these bits as LSB */
      /* cm_pasn4_c_001.main_21 : kwork fix */
		ret = cmPAsnDecBitField(msgCp, &byte, 
                                         noBits);
     if(ret != ROK)
          RETVALUE(RFAILED); 
 
     /* Move these bits at MSB for continuous Bit Str */
     evntStr->val[j] = (byte << (CM_PASN_VAL_EIGHT - noBits)); 
     
  }

 RETVALUE(ROK);

} /* End of cmPAsnDecFragVal */


/*
*
*       Fun:   cmPAsnCollateFrag
*
*       Desc:  This function Collates Fragment for a CLASS IE/OpenType
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn4.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnCollateFrag
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          lenVal,    /* length determinant value */
U32          *totalLen  /* Total fragment length */
)
#else
PUBLIC S16 cmPAsnCollateFrag (msgCp, lenVal, totalLen)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          lenVal;   /* Length determinant value */
U32          *totalLen; /* Total fragment length */ 
#endif
{
  S16   ret;
  U8    m;
  U8    m1;
  U32   numComp;
  U32   newNumComp;
  U32   tLen;
  U32   tmpLen;
  Buffer *tBuf;

  TRC3(cmPAsnCollateFrag)

  /* This function will remove the length determinants */
  /* which are spread across fragments and collate */
  /* the fragments together so that subsequently DecElm() */
  /* call can be made to decode a fragmented OpenType */
  /* element */

  m = (U8)(GetLoByte(GetLoWord(lenVal)));

  /* Check that the very first octet has first two bits as 11 */
  if( (m & CM_PASN_FRAG_CONST1) != CM_PASN_FRAG_CONST1)
    RETVALUE(RFAILED);

  newNumComp = 0;
  tLen = 0;
  tmpLen = 0;
 
  while( (m & CM_PASN_FRAG_CONST1) == CM_PASN_FRAG_CONST1)
  {
     /* Get the number of fragments as 64k, 48k, 32k or 16k */
     /* by reading the last 6 bits of the length value */
     numComp = (U32)(m & CM_PASN_FRAG_CONST3);
     numComp = numComp * CM_PASN_VAL_16K;

     /* Increment the total length */
     tLen += numComp;

     /* We will now skip the above number of octets */
     /* by segmenting the mBuf at the index = numComp */
     newNumComp += numComp;
      /* cm_pasn4_c_001.main_21 : kwork fix */
     ret = SSegMsg(msgCp->mBuf, (MsgLen)newNumComp, 
                       &tBuf);
     if(ret == RFAILED || tBuf == NULLP) 
         RETVALUE(RFAILED);

     /* Now the first byte of tBuf contains length of */
     /* next fragment */ 
     if( (SRemPreMsg( (Data *)&m, tBuf)) != ROK)
        RETVALUE(RFAILED);

     /* If the first 2 bits of m are 10 */
     /* we need to remove another octet from tBuf as */
     /* it also represents the 2nd byte of length */
     /* determinant */
     if( (m &  CM_PASN_FRAG_CONST1) ==  CM_PASN_BYTE_MSBONE)
     {
        if( (SRemPreMsg( (Data *)&m1, tBuf)) != ROK)
           RETVALUE(RFAILED);

        /* Increment the total length */
        tmpLen = (U32)( (m & CM_PASN_FRAG_CONST3)  
                             << CM_PASN_VAL_EIGHT);
        tmpLen |= (U32)m1;
        tLen += tmpLen;
     }
     /* Else if the first bit of m is 0 then last fragment */
     else if( !(m & CM_PASN_BYTE_MSBONE))
     {
        tLen += (U32)m;
     }

     /* Now concatenate the tBuf with original mBuf */
      /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = SCatMsg(msgCp->mBuf, tBuf, M1M2);
     if(ret != ROK)
        RETVALUE(RFAILED);
  }

  /* Also return the total length of the fragmented encode */
  *totalLen = tLen;

  RETVALUE(ROK); 
} /* End of cmPAsnCollateFrag */


/*
*
*       Fun:   cmPAsnDecFragSeqOfComp
*
*       Desc:  This function decodes a  fragmented SeqOf IE
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnDecFragSeqOfComp
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          fragComp,   /* Number of components */
U8           **retPtr   /* Return Pointer */ 
)
#else
PUBLIC S16 cmPAsnDecFragSeqOfComp(msgCp,fragComp,retPtr)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          fragComp;  /* Number of components */
U8           **retPtr;  /* Return Pointer */ 
#endif
{
  S16        ret;
  U32        ctr;
  U8         **ptr;
  TknU8      *allocPtr;
  CmPAsnElmDef **compDef; /* Component element define */

  TRC3(cmPAsnDecFragSeqOfComp)
  
  compDef = msgCp->elmDef;
  ctr = 0;
  allocPtr = NULLP;
     
  /* Run the loop to decode fragComp number of Components */ 
  /* Allocate memory for SetOf/SeqOf array */
  if( (  ((*msgCp->elmDef)->type == CM_PASN_TET_SET) ||
         ((*msgCp->elmDef)->type == CM_PASN_TET_SEQ) ) && 
         ( ((CmPAsnSetSeqDef *)((*msgCp->elmDef)->typeSpecDef))->allocEvnt) )
  {
      /* Event structure needs to be allocated for this */
      ret = SGetSBuf( ((CmMemListCp *)msgCp->memCp)->memCb.sMem.region,
                       ((CmMemListCp *)msgCp->memCp)->memCb.sMem.pool,
                       (Data **)&allocPtr,
                       (Size)(fragComp * sizeof(PTR)) );
      if(ret != ROK)
      {
         CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
         RETVALUE(RFAILED);
      }
  }

  else
  {
      /* Event structure needs to be allocated for this */
      ret = SGetSBuf( ((CmMemListCp *)msgCp->memCp)->memCb.sMem.region,
                      ((CmMemListCp *)msgCp->memCp)->memCb.sMem.pool,
                      (Data **)&allocPtr,
                      (Size)(fragComp * ((*msgCp->elmDef)->evSize)) );
      if(ret != ROK)
      {
         CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
         RETVALUE(RFAILED);
      }

  }
    
  /* Update allocated memory pointer in event structure */
  /* This needs to be done so that subsequent DecElm() calls reference */
  /* event pointers correctly */
  ptr = (U8 **)msgCp->evntStr;
  *ptr = (U8 *)allocPtr;

  /* Update event structure pointer in msgCp to point */
  /* to allocated memory for constituents */
  msgCp->evntStr = (TknU8 *)allocPtr;
  
  /* Now decode fragComp number of components */
  for( ctr = 0; ctr < (U32)fragComp; ctr++)
  {
      /* cm_pasn4_c_001.main_21 : kwork fix */
     ret = cmPAsnDecElm(msgCp);
	  if(ret!= ROK)
        RETVALUE(RFAILED);

     /* Reset Element definition of the component */
     msgCp->elmDef = compDef;
  }

  /* Return the allocated pointer which contains */
  /* Decoded SeqOf components information  */ 
  *retPtr = (U8 *)allocPtr;

  RETVALUE(ROK);

} /* End of cmPAsnDecFragSeqOfComp */



/*
*
*       Fun:   cmPAsnDecFragSeqOf
*
*       Desc:  This function decodes a  fragmented SeqOf IE
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnDecFragSeqOf
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          numComp,   /* Number of components */
U32          *totalComp /* Total Components */
)
#else
PUBLIC S16 cmPAsnDecFragSeqOf(msgCp,numComp,totalComp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          numComp;  /* Number of components */
U32          *totalComp; /* Total Components */
#endif
{
  S16        ret;
  U8         m;  
  U32        fragComp;
  U32        tComp;
  U8         *retPtr;
  U8         m1;
  Ptr        ptrArray[10];
  U32        fragArray[10];
  U32        tmpLen; 
  U8         i;
  U8         j;
  TknU8      *allocPtr;  /* Allocated pointer */
  Size       size;
  TknU8      *savedEvnt;
  TknU8      *copyPtr; /* By Amit*/
  U8         **ptr;

  TRC3(cmPAsnFragDecSeqOf)
  /* cm_pasn4_c_001.main_10 */
  tmpLen = 0;

  i = 0;
  tComp = 0;
  fragComp = 0;
  retPtr = NULLP;
  savedEvnt = (TknU8 *)msgCp->evntStr;

  /* Get the first length determinant octet */ 
  m = (U8)(GetLoByte(GetLoWord(numComp)));

  /* Check that the very first octet has first two bits as 11 */
  if( (m & CM_PASN_FRAG_CONST1) != CM_PASN_FRAG_CONST1)
    RETVALUE(RFAILED);

  while( (m & CM_PASN_FRAG_CONST1) == CM_PASN_FRAG_CONST1)
  {
     /* Get the number of fragments as 64k, 48k, 32k or 16k */
     /* by reading the last 6 bits of the length value */
     fragComp = (U32)(m & CM_PASN_FRAG_CONST3);
     fragComp = fragComp * CM_PASN_VAL_16K;

     /* Increment the total length */
     tComp += fragComp;

     /* Call the function to decode fragComp number of */
     /* components in a locally allocated memory */
     ret = cmPAsnDecFragSeqOfComp(msgCp,fragComp,(U8 **)&retPtr);
     if( ret != ROK)
        RETVALUE(RFAILED);

     ptrArray[i] = (Ptr)retPtr;
     fragArray[i++] = fragComp; 

     /* Now the first byte of mBuf contains length of */
     /* next fragment */ 
     if( (SRemPreMsg( (Data *)&m, msgCp->mBuf)) != ROK)
        RETVALUE(RFAILED);

     /* If the first 2 bits of m are 10 */
     /* we need to remove another octet from mBuf as */
     /* it also represents the 2nd byte of length */
     /* determinant */
     if( (m &  CM_PASN_FRAG_CONST1) ==  CM_PASN_BYTE_MSBONE)
     {
        if( (SRemPreMsg( (Data *)&m1, msgCp->mBuf)) != ROK)
           RETVALUE(RFAILED);

        /* Increment the total length */
        tmpLen = (U32)( (m & CM_PASN_FRAG_CONST3)  
                             << CM_PASN_VAL_EIGHT);
        tmpLen |= (U32)m1;
        tComp += tmpLen;
     }

     /* Else if the first bit of m is 0 then last fragment */
     else if( !(m & CM_PASN_BYTE_MSBONE))
     {
        tmpLen = (U32)m;
        tComp += (U32)m;
     }
  }

  /* Decode the last fragments */
  ret = cmPAsnDecFragSeqOfComp(msgCp,tmpLen,(U8 **)&retPtr);
  if( ret != ROK)
     RETVALUE(RFAILED);
 
  ptrArray[i] = (Ptr)retPtr;
  fragArray[i++] = tmpLen;

  /* Now process the various decoded fragmets as stored in ptrArray */

  /* Allocate memory for SetOf/SeqOf array */
  if( (  ((*msgCp->elmDef)->type == CM_PASN_TET_SET) ||
         ((*msgCp->elmDef)->type == CM_PASN_TET_SEQ) ) && 
      ( ((CmPAsnSetSeqDef *)((*msgCp->elmDef)->typeSpecDef))->allocEvnt) )
  {
     /* Event structure needs to be allocated for this */
      /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = cmGetMem((Ptr)msgCp->memCp,(Size)(tComp * sizeof(PTR)), 
                      (Ptr *)&allocPtr);
     if(ret != ROK)
     {
         CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
         RETVALUE(RFAILED);
     }

     copyPtr = allocPtr;

     /* Copy the pointers as stored in fragments local copy */
     for(j=0; j< i; j++)
     {
        size = fragArray[i] * sizeof(PTR);
        cmMemcpy((U8 *)copyPtr, (U8 *)ptrArray[i], size);
        copyPtr = (TknU8 *)((PTR)copyPtr + size);
        /* Release the memory associated with local fragments */
        SPutSBuf( ((CmMemListCp *)msgCp->memCp)->memCb.sMem.region,
                   ((CmMemListCp *)msgCp->memCp)->memCb.sMem.pool,
                   (Data *)ptrArray[i],size);
     }
  }
    
  else
  {
     /* Event structure needs to be allocated for this */
      /* cm_pasn4_c_001.main_21 : kwork fix */
	  ret = cmGetMem((Ptr)msgCp->memCp,(Size)(tComp *((*msgCp->elmDef)->evSize)), 
                      (Ptr *)&allocPtr);
     if(ret != ROK)
     {
        CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
        RETVALUE(RFAILED);
     }
     
     copyPtr = allocPtr;
     /* Copy the pointers as stored in fragments local copy */
     for(j=0; j< i; j++)
     {
        size = (fragArray[i] * ((*msgCp->elmDef)->evSize));
        cmMemcpy((U8 *)copyPtr, (U8 *)ptrArray[i], size); 
        copyPtr = (TknU8 *)((PTR)copyPtr + size); 
        /* Release the memory associated with local fragments */
        /* Release the memory associated with local fragments */
        SPutSBuf( ((CmMemListCp *)msgCp->memCp)->memCb.sMem.region,
                   ((CmMemListCp *)msgCp->memCp)->memCb.sMem.pool,
                   (Data *)ptrArray[i],size);
     }
  }

  msgCp->evntStr = savedEvnt;    
  /* Update allocated memory pointer in event structure */
  ptr = (U8 **)msgCp->evntStr;
  *ptr = (U8 *)allocPtr;

  msgCp->evntStr = (TknU8 *)allocPtr;

  RETVALUE(ROK);

} /* End of cmPAsnEncFragSeqOf */

  
/********************************************************************30**
  
         End of file:     cm_pasn4.c@@/main/21 - Thu Jun 30 18:32:18 2011
   
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
 
 
*********************************************************************81*/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      mp   1. initial release.

1.1+         hc004.11 bsr  1. code changes in cmPAsnDecSeqExt to handle
                              extra extensions
/main/2        ---      asa  1. Updated for rel 1.2
/main/4      --       bsr  1. returning CM_PASN_RES_ERR in resource 
                              allocation failure cases. (hc007.11)
                           2. Fixed decoding problem in cmPAsnDecSeqExt
/main/5      --       sgr  1. Fixed decoding problem in bit strings
/main/6      ---      sgr   1. Accomodated the patch in main_2
/main/7      ---      an   1. Changes to fix warnings about comparing unsigned
                            and signed integers. 
/main/8      ---      mp   1. Merged patches of /main/2
                           2. Fragmentation  Support added
/main/9      ---      sgr 1. Added range validation checks while decoding
/main/10     ---      rbabu 1. Updated for NBAP software release 1.2
/main/11     ---        vsr 1. Fixed the compiler warnings for RANAP release 2.3.
/main/12     ---       rbabu 1. Added Unaligned Support .
/main/13     ---      rbhat 1. Added Default value handling.
/main/14     ---      nm    1. Added verification of unpkArray size in 
                               cmPAsnDecSemiConInt function
/main/15     ---      cm_pasn4_c_001.main_14 nm 1. Updated FindFragLen to handle Infinite loop path.
/main/16     ---      ds    1.  cm_pasn4_c_001.main_15  Updated FindFragLen &
                            DecUnConLen to handle the correct fragmented case 
                            according to spec X.691-0207 clause 10.9.
/main/17     ---      ds    1. cm_pasn4_c_001.main_16 Modified in the
                            cmPAsnDecBitField so that the next byte will 
                            be decoded only when the size requested is 
                            non-zero and nextBitPos is equal to eight.
/main/18     --- cm_pasn4_c_001.main_17      mos   1. Updated for S1AP Release 2.1 
/main/19     ---    chebli 1. (cm_pasn4_c_001.main_18) Dereferencing issue fixed.
/main/20     ---      cm_pasn4_c_001.main_19  vkulkarni  1. Moving the len update to this function. 
                                              2. Correcting typecast issues.
                                              3. Correcting compilation issues.
/main/21     ---    cm_pasn4_c_001.main_20       mpatel  1. Update for LTE RRC 3.1 release
                                                         Added support of extention addition groups   
$SID$       ----    cm_pasn4_c_001.main_21 akaranth 1.kwork fix.
*********************************************************************91*/
