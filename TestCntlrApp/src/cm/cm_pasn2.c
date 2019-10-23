
/********************************************************************20**
  
     Name:     common PER asn.1
  
     Type:     C Source file
  
     Desc:     C source code for common PER ASN.1 encoding
               routines
  
     File:     cm_pasn2.c
  
     Sid:      cm_pasn2.c@@/main/22 - Mon Feb 20 16:38:18 2012
  
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
#include "cm_pint.h"       /* PER ASN internal header file */
#include "cm_tkns.h"       /* Common token structure file */
#include "cm_perr.h"       /* Error header file */

/* header/extern include files (.x) */
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_mblk.x"        /* Memory Link list library */
#include "cm_tkns.x"       /* Common token structure file */
#include "cm_pasn.x"       /* common per asn.1 encoding/decoding */
#include "cm_pint.x"       /* PER ASN internal header file */

/* Function declaration */

/* Constant declaration */
/* Character set for various restricted character */
/* string data types */


/*
*
*       Fun:   cmPAsnEncChVal
*
*       Desc:  This function encodes Character value 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncChVal
(
CmPAsnMsgCp        *msgCp,  /* message control pointer */
U8                 b,       /* Number of bits */
CmPAsnMulStrDef    specDef, /* Specific definition */ 
U16                len      /* String length */
)
#else
PUBLIC S16 cmPAsnEncChVal (msgCp, b, specDef,len)
CmPAsnMsgCp      *msgCp;   /* message control pointer */
U8               b;        /* Number of bits */
CmPAsnMulStrDef  specDef;  /* Specific definition */
U16              len;      /* String Length */
#endif
{
  U32     i;             /* Loop variable */ 
  S16     ret;           /* Return value */ 
  U32     j;             /* Loop variable */
  U32     v;             /* value of the character */ 
  U32     ubMax;         /* Max limit on upper bound */
  U32     count;         /* count of number of chars */
  U32     *effAlp;       /* Effective alphabet */
  TknStr4 *evntStr;      /* Event structure pointer */
  CmPAsnElmDef *elmDef;  /* Element definition */
  
  TRC2(cmPAsnEncChVal)
  /*  cm_pasn2_c_001.main_10 */
  v = 0;
 
  elmDef = *msgCp->elmDef;
  evntStr = (TknStr4 *)msgCp->evntStr; 

  /* Find the value of 2^b - 1 */
  ubMax = (CM_PASN_VAL_ONE << b) - 1;
  if( specDef.ub <= ubMax ) 
  {
     /* Encode the value v as is in b bits each */
     for( i=0; i< len; i++)
     {
        /* Get each character value */
        CM_PASN_GET_CHARVAL(evntStr, elmDef->type, i, v);

        /* Extract b bits in value and encode */
        if( b <= CM_PASN_VAL_EIGHT)
        {
  /* cm_pasn2_c_001.main_22 : kwork fix */
           ret = cmPAsnEncBitField(msgCp, (U8)v, b);
           if(ret != ROK) 
           {
              RETVALUE(RFAILED);
           }
        }
        else
        {
           /* b is more than 8 */
  /* cm_pasn2_c_001.main_22 : kwork fix */
           ret = cmPAsnEncByteField(msgCp,  v, b);
           if(ret != ROK)
           {
               RETVALUE(RFAILED);
           }
        }
  
     } /* End for loop */

  } /* if ub <= ubMax */

  else
  {
     /* Index of character is encoded than the value itself */
    
     if( specDef.effAlp != NULLP)
     {
        /* Defined constrained permitted alphabet set */
        effAlp = (U32 *)specDef.effAlp;

        /* Search the character value in effective constraint */
        count = effAlp[0];
        for( i =0; i< len; i++)
        {
           /* Get each character value */
           CM_PASN_GET_CHARVAL(evntStr, elmDef->type, i, v);

           for( j=0; j< count; j++)
           {
              if( v == (U32)effAlp[j+1])
              {
                 /* Encode idx j in b bits */
                 if( b <= CM_PASN_VAL_EIGHT)
                 {
                  /* cm_pasn2_c_001.main_22 : kwork fix */
                    ret = cmPAsnEncBitField(msgCp,(U8)j, b);
                    if(ret != ROK)
                    {
                       RETVALUE(RFAILED);
                    }
                 }
                 else
                 {
                  /* cm_pasn2_c_001.main_22 : kwork fix */
                    ret = cmPAsnEncByteField(msgCp, (U32)j, b);
                    if(ret != ROK)
                    {
                       RETVALUE(RFAILED);
                    }
                 }
               
                 /* Come out of inner loop */
                 break;
              }  /* End if */ 
            } /* End for on j */
         } /* End for on i */
      } /* If permitted alphabet is constrained */
 
      else
      {
         /* effAlp is the complete character set */
         for( i = 0; i< len; i++)
         {
             /* Get each character value idx */
             CM_PASN_GET_CHARVAL(evntStr, elmDef->type,i, v);

             /* Find the offset of character value from min */
             j = (v - specDef.lb); 

             /* Encode idx j in b bits */
             if( b <= CM_PASN_VAL_EIGHT)
             {
                  /* cm_pasn2_c_001.main_22 : kwork fix */
                 ret = cmPAsnEncBitField(msgCp, (U8)j, b);
                 if(ret != ROK)
                 {
                    RETVALUE(RFAILED);
                 }
             }
             else
             {
                  /* cm_pasn2_c_001.main_22 : kwork fix */
                ret = cmPAsnEncByteField(msgCp, (U32)j, b);
                if(ret != ROK)
                {
                   RETVALUE(RFAILED);
                }
             }
         } 
      }
  } /* if ub is more than ubMax */
 
  RETVALUE(ROK);

} /* End of cmPAsnEncChVal */




/*
*
*       Fun:   cmPAsnEncByteField
*
*       Desc:  This function encodes  U32 value in certain 
*              number of bits 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncByteField
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          val,       /* Value to encode */
U8           b          /* Number of bits */
)
#else
PUBLIC S16 cmPAsnEncByteField (msgCp, val,b)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          val;      /* value to encode */
U8           b;        /* Number of bits */
#endif
{
  U8     noBytes;    /* Number of bytes */
  U8     noBits;     /* Number of bits */
  S16    ret;        /* Return value */
  U32    v;          /* To store value */

  /* Local variables to be used for the Unaligned per */
  U8 pos;            /* To store position value */ 
  U32 val4bytes;     /* To store value */ 
  U8 i;              /* Loop variable */ 
  U8 val1byte;   /* To store value */


  TRC2(cmPAsnEncByteField)
 
   /* Encode val in b bits */
   if( b <= CM_PASN_VAL_EIGHT) 
   {
      /* cm_pasn2_c_001.main_22 : kwork fix */
      ret = cmPAsnEncBitField(msgCp, 
                 (U8)(GetLoByte(GetLoWord(val))), b);
      if(ret != ROK)
      {
          RETVALUE(RFAILED);
      }
   }
   else
   {
      /* PER UNALIGNED VARIANT */
   
     if (msgCp->perType == CM_PASN_USE_UALIGN)
     {
        /* cm_pasn2_c_001.main_22 : kwork fix */
        if(msgCp->bhldr.nxtBitPos != CM_PASN_VAL_EIGHT)
        {
           pos=msgCp->bhldr.nxtBitPos;
           if(b <= pos)
           {
              ret = cmPAsnEncBitField(msgCp,(U8)val,b);
              if(ret != ROK)
              {
                 RETVALUE(RFAILED);
              }
              RETVALUE(ROK);
           }
           else
           {
              val4bytes=val>>(b-pos);
              ret = cmPAsnEncBitField(msgCp,(U8)val4bytes,pos);
              if(ret != ROK)
              {
                 RETVALUE(RFAILED);
              }
              b -= pos;
           }
        }
        /* place last b of 32 bits in mBuf */ 
        /* Calculate number of bytes in b */
        noBytes = (b)/CM_PASN_VAL_EIGHT;
        /* Calculate number of bits over bytes in b */
        noBits = (b)%CM_PASN_VAL_EIGHT;

        /* cm_pasn2_c_001.main_22 : kwork fix */
        val4bytes = val&(CM_PASN_WORD_ALLONE>>(32-b));
        if(noBytes)
        {
           val4bytes >>= noBits;
           ret = cmPAsnEncMinOct(msgCp,val4bytes,noBytes);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
        }
        if( noBits)
        { 
           val1byte = CM_PASN_VAL_NULL;
           for(i = 0; i < noBits; i++)
           {
              val1byte <<= 1;
              val1byte |= 1;
           }
           val4bytes=val&val1byte;
           ret = cmPAsnEncBitField(msgCp,(U8)val4bytes,noBits);
           if(ret != ROK) 
           {
              RETVALUE(RFAILED);
           }
        }

        RETVALUE(ROK);

     }
     else
     {
        /* cm_pasn2_c_001.main_22 : kwork fix */
        /* place last b of 32 bits in mBuf */ 
        /* Calculate number of bytes in b */
        noBytes = b/CM_PASN_VAL_EIGHT;

        /* Calculate number of bits over bytes in b */
        noBits = b % CM_PASN_VAL_EIGHT;

        v = val;
        /* Shift right v by noBits */
        /* This will bring msb to an octet boundary */
        v >>= noBits;

        /* Encode noBytes of v */
        ret = cmPAsnEncMinOct(msgCp, v, noBytes);
        if(ret != ROK)
        {
           RETVALUE(RFAILED);
        }

        /* Now encode the remaining LSB bits over octets */
        if( noBits)
        { 
           ret = cmPAsnEncBitField(msgCp,
                       (Data)(GetLoByte(GetLoWord(val))), noBits);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
        }
     }
   }      
  RETVALUE(ROK);
} /* End of cmPAsnEncByteField */


/* cm_pasn2_c_001.main_14 Updated for S1AP release 2.1 */
/*
*
*       Fun:   cmPAsnEncByteFieldXL
*
*       Desc:  This function encodes integer value in certain 
*              number of bits 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncByteFieldXL
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U8           *val,      /* Value to encode */
U8           valLen,    /* length of value in bytes*/
U8           nBits      /* Number of bits */
)
#else
PUBLIC S16 cmPAsnEncByteFieldXL (msgCp, val, valLen, nBits)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U8           *val;     /* value to encode */
U8           valLen;   /* length of value in bytes*/
U8           nBits;    /* Number of bits */
#endif
{
	U8     msbBits;    /* Number of bits in MSB of value */
	U8     numBits;    /* Number of bits */
	U8     padBits;    /* Number of padding bits */
	U8     padBytes;   /* Number of padding bytes */
   U8     byte;
   U32    idx;
	S16    ret;        /* Return value */

	TRC2(cmPAsnEncByteFieldXL)

   msbBits = CM_PASN_VAL_NULL;
   CM_PASN_FIND_NOBITS(val[0], msbBits);
   numBits = msbBits + ((valLen - 1) * CM_PASN_VAL_EIGHT);

   if (nBits < numBits)
      RETVALUE(RFAILED);

   padBytes = (nBits - numBits) / CM_PASN_VAL_EIGHT;
   padBits  = (nBits - numBits) % CM_PASN_VAL_EIGHT;

	/* Encode val in nBits bits */
	if (nBits <= CM_PASN_VAL_EIGHT) 
	{
  /* cm_pasn2_c_001.main_22 : kwork fix */
		ret = cmPAsnEncBitField(msgCp, val[0], nBits);
		if (ret != ROK)
			RETVALUE(RFAILED);
	}
   else
   {
      byte = 0;

      /* fill zero bits for padding */
      for (idx = 0; idx < padBytes; idx++)
      {
  /* cm_pasn2_c_001.main_22 : kwork fix */
         ret = cmPAsnEncMinOct(msgCp, byte, CM_PASN_ONE_OCTET);
         if (ret != ROK)
            RETVALUE(RFAILED);
      }

      if (padBits > 0)
      {
  /* cm_pasn2_c_001.main_22 : kwork fix */
         ret = cmPAsnEncBitField(msgCp, byte, padBits);
         if (ret != ROK)
            RETVALUE(RFAILED);
      }

      byte = val[0];

  /* cm_pasn2_c_001.main_22 : kwork fix */
         ret = cmPAsnEncBitField(msgCp, byte, msbBits);
         if (ret != ROK)
             RETVALUE(RFAILED);

      for (idx = 1; idx < valLen; idx++)
      {
  /* cm_pasn2_c_001.main_22 : kwork fix */
         ret = cmPAsnEncBitField(msgCp, val[idx], CM_PASN_VAL_EIGHT);
         if (ret != ROK)
            RETVALUE(RFAILED);
      }
   }

#if 0
   else
   {
      if (msgCp->perType == CM_PASN_USE_UALIGN)
      {
         if (msgCp->bhldr.nxtBitPos != CM_PASN_VAL_EIGHT)
         {
            pos = msgCp->bhldr.nxtBitPos;
            if (b <= pos)
            {
               if (cmPAsnEncBitField(msgCp, val[0], b) != ROK)
                  RETVALUE(RFAILED);

               RETVALUE(ROK);
            }
            else
            {
               CM_PASN_FIND_NOBITS(val[0], numBits);

               if (numBits <= pos)
                  val4bytes=val>>(b-pos);
               if (cmPAsnEncBitField(msgCp,(U8)val4bytes,pos) != ROK)
                  RETVALUE(RFAILED);
               b -= pos;
            }
         }
         /* place last b of 32 bits in mBuf */ 
         /* Calculate number of bytes in b */
         noBytes=(b)/CM_PASN_VAL_EIGHT;
         /* Calculate number of bits over bytes in b */
         noBits=(b)%CM_PASN_VAL_EIGHT;

         val4bytes= val&(CM_PASN_WORD_ALLONE>>(32-b));
         if(noBytes)
         {
            val4bytes >>= noBits;
            if(cmPAsnEncMinOct(msgCp,val4bytes,noBytes) != ROK)
               RETVALUE(RFAILED);
         }
         if( noBits)
         { 
            val1byte=CM_PASN_VAL_NULL;
            for(i=0;i<noBits;i++)
            {
               val1byte <<= 1;
               val1byte |= 1;
            }
            val4bytes=val&val1byte;
            if(cmPAsnEncBitField(msgCp,(U8)val4bytes,noBits) != ROK) 
               RETVALUE(RFAILED);
         }
         RETVALUE(ROK);
      }
      else
      {
         /* Calculate number of bytes in b */
         noBytes = b/CM_PASN_VAL_EIGHT;

         /* Calculate number of bits over bytes in b */
         noBits = b % CM_PASN_VAL_EIGHT;

         v = val;
         /* Shift right v by noBits */
         /* This will bring msb to an octet boundary */
         v >>= noBits;

         /* Encode noBytes of v */
         if(cmPAsnEncMinOct(msgCp, v, noBytes) != ROK)
            RETVALUE(RFAILED);

         /* Now encode the remaining LSB bits over octets */
         if( noBits)
         { 
            if(cmPAsnEncBitField(msgCp,
                        (Data)(GetLoByte(GetLoWord(val))), noBits) != ROK)
               RETVALUE(RFAILED);
         }
      }
   }      
#endif
	RETVALUE(ROK);
} /* End of cmPAsnEncByteField */



/*
*
*       Fun:   cmPAsnEncRChLen
*
*       Desc:  This function encodes Restricted Character string 
*              Length 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncRChLen
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U8           b,         /* Number of bits */
U32          len,       /* Length of string */
U32          aub,       /* pointer to Upper bound */ 
U32          alb        /* Pointer to Lower bound */
)
#else
PUBLIC S16 cmPAsnEncRChLen (msgCp, b, len, aub, alb)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U8           b;        /* Number of bits */
U32          len;      /* Length of string */ 
U32          aub;      /* Upper Bound */
U32          alb;      /* Lower Bound */
#endif
{
  S16  ret;       /* Return value */

  TRC2(cmPAsnEncRChLen)

  if( (aub != alb) || ( aub >= CM_PASN_VAL_64K) )
  {
     if(aub < CM_PASN_VAL_64K)
     {
      /* cm_pasn2_c_001.main_22 : kwork fix */
        /* Encode length as Constrained Integer */
        ret = cmPAsnEncConInt(msgCp, (U32)len, alb, aub, FALSE);
        if(ret != ROK)
        {
           RETVALUE(RFAILED);
        }

        if (msgCp->perType == CM_PASN_USE_ALIGN)
        {
           /* Octet allign if b*aub is more than 16 */
           if( (b * aub) >= CM_PASN_VAL_SIXTEEN )
           {
              CM_PASN_OCTET_ALIGN(msgCp);
           }
        }
     }
     else
     {
        if (len <= CM_PASN_VAL_16K)
        {
           /* Encode length as Uncon Int, without */
           /* fragmentation */
           ret = cmPAsnEncUnconLen(msgCp, len);
           if(ret != ROK)
           {
              RETVALUE(RFAILED); 
           }

           if (msgCp->perType == CM_PASN_USE_ALIGN)
           {
              /* Octet allign since b*aub is more than 16 */
              CM_PASN_OCTET_ALIGN(msgCp);
           }
        }
     }
  }
  else
  {
     if (msgCp->perType == CM_PASN_USE_ALIGN)
     {
        /* aub is same as alb and is less than 64K */
        /* No length encoding , check for octet allign */
        if( (b * aub) >= CM_PASN_VAL_SIXTEEN)
        {
           CM_PASN_OCTET_ALIGN(msgCp);
        }
     }
  }
  RETVALUE(ROK);
} /* End of cmPAsnEncRChStrLen */



/*
*
*       Fun:   cmPAsnEncRChStrExt
*
*       Desc:  This function encodes Restricted Character string 
*               extension bit
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncRChStrExt
(
CmPAsnMsgCp  *msgCp,     /* message control pointer */
CmPAsnMulStrDef *strDef, /* String constraints */
U16          len         /* String length */ 
)
#else
PUBLIC S16 cmPAsnEncRChStrExt (msgCp, strDef, len)
CmPAsnMsgCp  *msgCp;      /* message control pointer */
CmPAsnMulStrDef *strDef;  /* String constraints */
U16          len;         /* String length */
#endif
{
 U8            found;       /* Flag */
 S16           ret;         /* Return value */
 U32           i;           /* Loop variable */
 U32           j;           /* Loop variable */
 U32           v;           /* value of character */
 U32           count;       /* Count of number of alphabets */
 U32           *effAlpCons; /* Effective alphabet Constraint array*/
 CmPAsnElmDef  *elmDef;     /* Element definition */
 TknStr4       *evntStr;    /* Event structure */

 TRC2(cmPAsnEncRChStrExt)
 /* cm_pasn2_c.main_009 */
 v = 0;
 
 elmDef = *msgCp->elmDef;
 effAlpCons = strDef->effAlp;
 evntStr = (TknStr4 *)msgCp->evntStr;

#if (ERRCLASS & ERRCLS_DEBUG)
 /* Permitted alphabet should not be null */
 if( !effAlpCons )
 {
    CMPASNLOGERROR(ERRCLS_INT_PAR, ECMPASN011, (ErrVal)0,
          "cmPAsnEncRChStrExt() failed,NULL permitted alphabet ");

    RETVALUE(RFAILED);
 }
#endif /* ERRCLASS & ERRCLS_DEBUG */

 /* Find the count of characters in permitted alphabet */
 count = (U32)(effAlpCons[0]); 

 /* Check if each character in string value */
 found = FALSE;

 /* is present in permitted alphabet */
 for( i =0; i < len; i++ )
 {
    found = FALSE;
    /* Get each character value */
    CM_PASN_GET_CHARVAL(evntStr, elmDef->type, i, v);

    for( j = 1; j <= count; j++)
    {
       if( v == (U32)effAlpCons[j] )
          found = TRUE;
    }

    if( !found)
       /* Break from loop */
       break;
 } 
    
 /* If found flag is FALSE, set extension bit */
 if( !found)
 {
    /* Encode extension bit as 1 */
    ret = cmPAsnEncBitField(msgCp,CM_PASN_VAL_ONE, CM_PASN_VAL_ONE);
    if (ret != ROK)
       RETVALUE(RFAILED);
    /* Also Unset upper bound, lower bound to zero */
    /* Also  make effective alphabet constraint NULL */
    strDef->max = CM_PASN_MAX_NA;
    strDef->min = CM_PASN_VAL_NULL;
    strDef->effAlp = NULLP;
    strDef->ub = CM_PASN_MAX_NA;
    strDef->lb = CM_PASN_VAL_NULL;  
 }
 else
 {
    /* Extension bit is 0 */
    ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_NULL, CM_PASN_VAL_ONE);
    if(ret != ROK)
    {
       RETVALUE(RFAILED);
    }
 }
 RETVALUE(ROK);
} /* End of cmPAsnEncRChStrExt */



/*
*
*       Fun:   cmPAsnChkCharVal
*
*       Desc:  This function checks for a character to be
*       present in a specific character type. 
*
*       Ret:   ROK : If character is found in character set
*              RFAILED: If character is not found. 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnChkCharVal
(
CmPAsnMsgCp *msgCp,      /* Message Control Point */
U16         len          /* String length */ 
)
#else
PUBLIC S16 cmPAsnChkCharVal ( msgCp, len)
CmPAsnMsgCp *msgCp;     /* Message Control Point */
U16         len;        /* String length */
#endif
{

  Bool      found;           /* Flag */ 
  U16       i;               /* Loop variable */
  U32       j;               /* Loop variable */
  U32       v;               /* Character value */
  U32       count;           /* Number of chars values */
  TknStr4   *evntStr;        /* Event structure */
  CmPAsnMulStrDef *specDef;  /* Specific definition */
  CmPAsnElmDef *elmDef;      /* Element definition */ 

  TRC2(cmPAsnChkCharVal)
  /* cm_pasn2_c_001.main_10 */
  v = 0;

  elmDef = *msgCp->elmDef;
  specDef = (CmPAsnMulStrDef *)elmDef->typeSpecDef;
  evntStr = (TknStr4 *)msgCp->evntStr;

  /*
   * If extension marker is present, each char should
   * belong to built in type char set, there should also
   * be a defined effective alphabet constraint 
   * Otherwise, if effective alphabet present, char
   * should belong to it and if effective alphabet
   * is not present, it should belong to the char set
   * of built in type, otherwise it is an error 
   */ 

   if( (elmDef->extMkr) && ( !specDef->effAlp) )
      RETVALUE(RFAILED);

   if( (elmDef->extMkr) ||
       ( (!elmDef->extMkr) && ( !specDef->effAlp)) )
   {
      /* Check that each char value belongs to built-in */
      /* type */
      for( i=0; i < len; i++)
      {
         /* Get each character value */
         CM_PASN_GETCHK_CHARVAL(evntStr, elmDef->type, i, v);
      }
   }

   if( (!elmDef->extMkr) && ( specDef->effAlp))
   {
      /* Each character should belong to permitted */
      /* Alphabet constraint only */
      count = specDef->effAlp[0];

      for( i=0; i < len; i++)
      {
         found = FALSE;
         /* Get each character value */
         CM_PASN_GET_CHARVAL(evntStr, elmDef->type, i, v);

         for( j = 1; j <= count; j++)
         {
            if( v == (U32)specDef->effAlp[j] )
               found = TRUE;
         }
         if( !found)
            RETVALUE(RFAILED);
      }
    }
   
 RETVALUE(ROK);

} /* End of cmPAsnChkCharVal */



/*
*
*       Fun:   cmPAsnFindNoBit
*
*       Desc:  This function calculates number of bits 
*              required to encode  each character in
*              string value 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC U8 cmPAsnFindNoBit
(
CmPAsnMsgCp  *msgCp,      /* Message Control Point */
U32          *effAlp,   /* Effective alphabet */
U8           type       /* String type */
)
#else
PUBLIC U8 cmPAsnFindNoBit (msgCp, effAlp, type)
CmPAsnMsgCp  *msgCp;     /* Message Control Point */
U32          *effAlp;  /* Effective alphabet */
U8           type;     /* String type */
#endif
{

   U8   b;        /* Return value */
   U8   x;        /* power of 2 so that 2^x >= B */  
   U8   B;        /* power of 2 so that 2^B >= N */
   U32  N;        /* Number of chars in permitted set */ 

   TRC2(cmPAsnFindNoBit)
      /* cm_pasn2_c_001.main_10 */
      b = 0;

   /* 
    * Let N be number of characters in effective alphabet 
    * if effAlp is NULL, then N denotes number of chars in
    * built in type char set. In this case since N is fixed
    * return value b can be pre computed as per the algo
    * below and just returned based on the string type. 
    * else effAlp[0] gives the count N
    * Find B as smallest integer so that 2 to power B >= N
    * Find x as smallest power of 2 >= B
    * b : the return valus is equal to 2^B2
    */ 
   if (msgCp->perType == CM_PASN_USE_UALIGN)
   {
      if( !effAlp)
      {
         b = 7; 
         RETVALUE(b);
      }
   }
   else
   {
      if( !effAlp)
      {
         /* Effective alphabet is implicitly the character
            set of built in type */
         switch( type)
         {
            case CM_PASN_TET_IA5STR:
            case CM_PASN_TET_PRNSTR:
            case CM_PASN_TET_NUMSTR:
            case CM_PASN_TET_VISSTR:
            case CM_PASN_TET_GENSTR:
            case CM_PASN_TET_IA5STRXL:
            case CM_PASN_TET_PRNSTRXL:
            case CM_PASN_TET_NUMSTRXL:
            case CM_PASN_TET_VISSTRXL:
            case CM_PASN_TET_GENSTRXL:

               b = CM_PASN_VAL_EIGHT;
               break;
            case CM_PASN_TET_BMPSTR:
            case CM_PASN_TET_BMPSTRXL:

               b = CM_PASN_VAL_SIXTEEN;
               break;
            case CM_PASN_TET_UNISTR:
            case CM_PASN_TET_UNISTRXL:

               b = CM_PASN_VAL_THREETWO;
               break;
            default:
#if (ERRCLASS & ERRCLS_DEBUG)
               CMPASNLOGERROR(ERRCLS_INT_PAR, ECMPASN012, (ErrVal)type,
                     "cmPAsnFindNoBit failed,Invalid String type ");
#endif  /* ERRCLASS & ERRCLS_DEBUG */
               break;
         }

         RETVALUE(b);
      } /* If NULL effAlp */
   }

   N = effAlp[0];
   B = CM_PASN_VAL_NULL;

   /* apply the loop on value N-1 to get B */ 
   N = N-1; 
   while ( N )
   {
      N = N/2;
      B++;
   }

   /* In the case of PER unaligned variant each character 
      shall encode in B bits */
   if (msgCp->perType == CM_PASN_USE_UALIGN)
   {
      RETVALUE(B);
   }


   /* Apply the loop on B-1 to get log(x) */

   B = B-1;
   x =CM_PASN_VAL_NULL;
   while ( B)
   {
      B = B/2;
      x++; 
   }

   /* Return value is 2^x */ 
   b = CM_PASN_VAL_ONE;
   while(x)
   {
      b = b*2;
      x--;
   }

   RETVALUE(b);

} /* end of cmPAsnFindNoBit */


/*
*
*       Fun:   cmPAsnChkEncElmnt
*
*       Desc:  This function Checks before encoding an ASN.1 element type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnChkEncElmnt
(
U8 flag,
CmPAsnMsgCp  *msgCp,    /* message control pointer */
TknU8 *evntStr
)
#else
PUBLIC S16 cmPAsnChkEncElmnt (flag,msgCp,evntStr)
U8 flag;
CmPAsnMsgCp  *msgCp;   /* message control pointer */
TknU8 *evntStr;
#endif
{
   U8  pres;

   TRC2(cmPAsnChkEncElmnt)

   /* cm_pasn2_c_001.main_17 - Removed un-necessary check in ChkEncElmnt.
      Any such validation shall happen in the calling function. */
	pres = evntStr->pres;

   /* check if the element is defined for this protocol */ 
   if (flag == CM_PASN_ELM_INV)
   {
      /* element not defined for this protocol */

      /* check if the element is present in the event structure */
      if (pres)
      {
         /* parameter is not defined for the protocol */
         CM_PASN_ERR(msgCp, CM_PASN_UNDEF_PARAM);  
         RETVALUE(RFAILED);
      }
      else
      {
         /* element not present. Skip the element in event structure and 
            increments the data base pointer appropriately */
         RETVALUE(RSKIP);
      }

   } /* end if */  

   /* if element not present and is mandatory or Default */
   /* return error */
   if (!pres)
   {
      /* check if element is mandatory */
      if (flag == CM_PASN_ELM_MAND)
      {
         /* mandatory element is missing */
         CM_PASN_ERR(msgCp, CM_PASN_MAND_MIS);  
         RETVALUE(RFAILED);
      }
      else if( flag == CM_PASN_ELM_MANDIGN)
      {
         /* Mandatory ignorable element */
         if(!msgCp->igExtMand)
         {
            /* If user does not want to ignore these IEs */
            CM_PASN_ERR(msgCp, CM_PASN_MAND_MIS);  
            RETVALUE(RFAILED);
         }
      }

      /* element is Optional or Mandatory Ignorable, skip it */
      RETVALUE(RSKIP);

   } /* end if */

   RETVALUE(ROK);
} /* End of cmPAsnChkEncElmnt */


/*
*
*       Fun:   cmPAsnEncBitField
*
*       Desc:  This function Encodes a byte into Bit Field 
*
*       Ret:   ROK 
*
*       Notes: This function accepts a single byte
*       value for encoding as a bit field and the
*       size can at the most be 8.
*
*       File:  cm_pasn2.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnEncBitField
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U8 value,               /* Value to encode */
U8 size                 /* Number of bits to encode */
)
#else
PUBLIC S16 cmPAsnEncBitField (msgCp,value, size)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U8 value;              /* Value to encode */
U8 size;               /* Number of bits to encode */
#endif
{
   U8 initByte;                /* Byte value */ 
   U8 locValue;                /* Local byte value */

   TRC2 (cmPAsnEncBitField)

   /* If bits to add exceed 8, return error */
   /* If value can not come in requested bits, flag error */
#if (ERRCLASS & ERRCLS_DEBUG)
   if( (size > CM_PASN_BF_SIZE8) ||
       ( value >= (U32)(CM_PASN_BYTE_LSBONE << size)) )
   {
      CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN013, (ErrVal)size,
        "cmPAsnEncBitField failed, invalid size specified ");
      RETVALUE(RFAILED);
   }
#endif  /* (ERRCLASS & ERRCLS_DEBUG) */

   /* 
    * If number of bits to be added is less than space
    * available in Bit handler 
    */

   if( size <= (U8)msgCp->bhldr.nxtBitPos)
   {
      /* Get Byte value to initialise the bithandler */
      initByte = CM_PASN_GET_INITBYTE(msgCp);
      msgCp->bhldr.byte &= initByte;
      msgCp->bhldr.byte |= ( value << (U8)(msgCp->bhldr.nxtBitPos -
                                         size) );
      if( size != msgCp->bhldr.nxtBitPos)
         msgCp->bhldr.nxtBitPos = msgCp->bhldr.nxtBitPos - size;

      else
      {
         msgCp->bhldr.nxtBitPos = CM_PASN_NXTBITPOS_EIGHT;
         CM_PASN_ENC_BYTE(msgCp, msgCp->bhldr.byte);
      }

   } /* end if number of bits are small */
   else
   {
      /* Number of bits exceed space in bit handler */
      /* Obtain the bits that can fit into the left space */
      initByte = CM_PASN_GET_INITBYTE(msgCp);
      msgCp->bhldr.byte &= initByte;
      locValue = value;
      locValue >>= (size - msgCp->bhldr.nxtBitPos);
      msgCp->bhldr.byte |= locValue;

      /* Modify the size value */
      size = size - msgCp->bhldr.nxtBitPos;
      msgCp->bhldr.nxtBitPos = CM_PASN_NXTBITPOS_EIGHT;

      /* Byte in bit handler is full, encode it */
      CM_PASN_ENC_BYTE(msgCp, msgCp->bhldr.byte);

      msgCp->bhldr.byte = CM_PASN_VAL_NULL;
      msgCp->bhldr.byte = value << (msgCp->bhldr.nxtBitPos - size);
      msgCp->bhldr.nxtBitPos = msgCp->bhldr.nxtBitPos - size;
   } /* End if number of bits are large */

   RETVALUE(ROK);

} /* cmPAsnEncBitField */


/*cm_pasn2_c_001.main_20:Added support for extension addition
*groups for unaligned PER
*
*       Fun:   cmPAsnRepAndEncBitField
*
*       Desc:  In case of aligned PER, this function replaces an octet with the 
*              supplied value and in case of unaligned PER, as per bitPos it 
*              replaces 8 bits with the supplied U8 value.
*
*       Ret:   ROK 
*
*       Notes: This function accepts a single byte value for encoding 
*              as a bit field
*
*       File:  cm_pasn2.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPAsnRepAndEncBitField
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
MsgLen lenIdx,          /* length index of the byte need to be replaced */
U8 bitPos,              /* bit position of the byte handler, applicable for uper only */
U8 value                /* Value to encode */
)
#else
PUBLIC S16 cmPAsnRepAndEncBitField (msgCp, lenIdx, bitPos, value)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
MsgLen lenIdx;         /* length index of the byte need to be replaced */
U8 bitPos;             /* bit position of the byte handler, applicable for uper only */
U8 value;              /* Value to encode */
#endif
{
   U8     octetVal;
   U8     byte = 0;
   MsgLen len;

   TRC2 (cmPAsnRepAndEncBitField)

   if (msgCp->perType == CM_PASN_USE_ALIGN)
   {
      bitPos = 8;
   }

   if (msgCp->mMgmt == CM_PASN_USE_MBUF)
   {
      if (ROK != SExamMsg(&byte, msgCp->mBuf, lenIdx))
      {
         RETVALUE(RFAILED);
      }
   }
   else if (msgCp->mMgmt == CM_PASN_USE_SBUF)
   {
      byte = msgCp->fBuf.bufP[lenIdx];
   }
   else
   {
      RETVALUE(RFAILED);
   }

   octetVal = (byte & (0xff << bitPos)) | (value >> (8 - bitPos));

   if (msgCp->mMgmt == CM_PASN_USE_MBUF)
   {
      SRepMsg(octetVal, msgCp->mBuf, lenIdx);
   }
   else if (msgCp->mMgmt == CM_PASN_USE_SBUF)
   {
      msgCp->fBuf.bufP[lenIdx] = octetVal;
   }

   if (bitPos != 8)
   {
      if (msgCp->mMgmt == CM_PASN_USE_MBUF)
         SFndLenMsg(msgCp->mBuf, &len);
      else
         len = msgCp->fBuf.crntIdx;
         
      if ((lenIdx + 1) == len)
      {
         msgCp->bhldr.byte = (msgCp->bhldr.byte & (0xff >> (8 - bitPos))) | (value << bitPos);
      }
      else
      {
         if (msgCp->mMgmt == CM_PASN_USE_MBUF)
         {
            if (ROK != SExamMsg(&byte, msgCp->mBuf, (lenIdx + 1)))
            {
               RETVALUE(RFAILED);
            }
         }
         else if (msgCp->mMgmt == CM_PASN_USE_SBUF)
         {
            byte = msgCp->fBuf.bufP[lenIdx + 1];
         }

         octetVal = (byte & (0xff >> (8 - bitPos))) | (value << bitPos);

         if (msgCp->mMgmt == CM_PASN_USE_MBUF)
         {
            SRepMsg(octetVal, msgCp->mBuf, (lenIdx + 1));
         }
         else if (msgCp->mMgmt == CM_PASN_USE_SBUF)
         {
            msgCp->fBuf.bufP[lenIdx + 1] = octetVal;
         }
      }
   }


   RETVALUE(ROK);
} /* cmPAsnRepAndEncBitField */


/*
*
*       Fun:   cmPAsnEncMinOct
*
*       Desc:  This function Encodes a 4 octet long value in
*              minimum number of specified octets
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncMinOct
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32  value,             /* Integer value to encode */
U8   lenVal             /* Number of octets to encode */ 
)
#else
PUBLIC S16 cmPAsnEncMinOct (msgCp,value, lenVal)
CmPAsnMsgCp  *msgCp;    /* message control pointer */
U32  value;             /* Integer value to encode */
U8   lenVal;            /* Number of cotets to encode */
#endif
{

  S16 ret;
  TRC2(cmPAsnEncMinOct)

  switch( lenVal)
  {
     case CM_PASN_ONE_OCTET:
        /* Get the least significant byte */
        if (msgCp->perType == CM_PASN_USE_UALIGN)
        {
  /* cm_pasn2_c_001.main_22 : kwork fix */
           ret = cmPAsnEncBitField(msgCp,
                    (U8)(GetLoByte(GetLoWord(value))),CM_PASN_VAL_EIGHT);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
        }
        else
        {
           CM_PASN_ENC_BYTE(msgCp, (U8)(GetLoByte(GetLoWord(value))) );
        }
        break;
        
     case CM_PASN_TWO_OCTETS:
        /* Encode last 2 octets in message buffer */
        if (msgCp->perType == CM_PASN_USE_UALIGN)
        {
  /* cm_pasn2_c_001.main_22 : kwork fix */
           ret = cmPAsnEncBitField(msgCp,
                    (U8)(GetHiByte(GetLoWord(value))),CM_PASN_VAL_EIGHT);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }

           ret = cmPAsnEncBitField(msgCp,
                    (U8)(GetLoByte(GetLoWord(value))),CM_PASN_VAL_EIGHT);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
        }
        else
        {
           if( msgCp->mMgmt == CM_PASN_USE_MBUF)
           {
              CM_PASN_ENC_BYTE(msgCp,(U8)(GetHiByte(GetLoWord(value))) );
              CM_PASN_ENC_BYTE(msgCp,(U8)(GetLoByte(GetLoWord(value))) );
           }
           else
           {
              if( msgCp->mMgmt == CM_PASN_USE_SBUF)
              {
                 msgCp->fBuf.bufP[msgCp->fBuf.crntIdx++] = 
                    (U8)(GetHiByte(GetLoWord(value)));
                 msgCp->fBuf.bufP[msgCp->fBuf.crntIdx++] = 
                    (U8)(GetLoByte(GetLoWord(value)));
              }
           }
        }
        break;

     case CM_PASN_THREE_OCTETS:
        /* Encode last 3 octets in message buffer */
        if (msgCp->perType == CM_PASN_USE_UALIGN)
        {
         /* cm_pasn2_c_001.main_22 : kwork fix */
           ret = cmPAsnEncBitField(msgCp, 
                    (U8)(GetLoByte(GetHiWord(value))),CM_PASN_VAL_EIGHT);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
           ret = cmPAsnEncBitField(msgCp,
                    (U8)(GetHiByte(GetLoWord(value))),CM_PASN_VAL_EIGHT);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
           ret = cmPAsnEncBitField(msgCp,
                    (U8)(GetLoByte(GetLoWord(value))),CM_PASN_VAL_EIGHT);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
        }
        else
        {
           if( msgCp->mMgmt == CM_PASN_USE_MBUF)
           {
              CM_PASN_ENC_BYTE(msgCp, (U8)(GetLoByte(GetHiWord(value))) );
              CM_PASN_ENC_BYTE(msgCp,(U8)(GetHiByte(GetLoWord(value))) );
              CM_PASN_ENC_BYTE(msgCp,(U8)(GetLoByte(GetLoWord(value))) );
           }
           else
           {
              if( msgCp->mMgmt == CM_PASN_USE_SBUF)
              {
                 msgCp->fBuf.bufP[msgCp->fBuf.crntIdx++] = 
                    (U8)(GetLoByte(GetHiWord(value)));
                 msgCp->fBuf.bufP[msgCp->fBuf.crntIdx++] = 
                    (U8)(GetHiByte(GetLoWord(value)));
                 msgCp->fBuf.bufP[msgCp->fBuf.crntIdx++] = 
                    (U8)(GetLoByte(GetLoWord(value)));
              }
           }
        }
        break;

     case CM_PASN_FOUR_OCTETS:
        /* Encode the 4 octets in message buffer */
         /* cm_pasn2_c_001.main_22 : kwork fix */
        if (msgCp->perType == CM_PASN_USE_UALIGN)
        {
           ret = cmPAsnEncBitField(msgCp,
                       (U8)(GetHiByte(GetHiWord(value))),CM_PASN_VAL_EIGHT);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
           ret = cmPAsnEncBitField(msgCp,
                       (U8)(GetLoByte(GetHiWord(value))),CM_PASN_VAL_EIGHT);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
           ret = cmPAsnEncBitField(msgCp,
                       (U8)(GetHiByte(GetLoWord(value))),CM_PASN_VAL_EIGHT);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
           ret = cmPAsnEncBitField(msgCp,
                       (U8)(GetLoByte(GetLoWord(value))),CM_PASN_VAL_EIGHT);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
        } 
        else
        {
           if( msgCp->mMgmt == CM_PASN_USE_MBUF)
           {
         /* cm_pasn2_c_001.main_22 : Aligining lines  */
              CM_PASN_ENC_BYTE(msgCp,(U8)(GetHiByte(GetHiWord(value))) );
              CM_PASN_ENC_BYTE(msgCp,(U8)(GetLoByte(GetHiWord(value))) );
              CM_PASN_ENC_BYTE(msgCp,(U8)(GetHiByte(GetLoWord(value))) );
              CM_PASN_ENC_BYTE(msgCp,(U8)(GetLoByte(GetLoWord(value))) );
           }
           else
           {
              if( msgCp->mMgmt == CM_PASN_USE_SBUF)
              {
                 msgCp->fBuf.bufP[msgCp->fBuf.crntIdx++] = 
                    (U8)(GetHiByte(GetHiWord(value)));
                 msgCp->fBuf.bufP[msgCp->fBuf.crntIdx++] = 
                    (U8)(GetLoByte(GetHiWord(value)));
                 msgCp->fBuf.bufP[msgCp->fBuf.crntIdx++] = 
                    (U8)(GetHiByte(GetLoWord(value)));
                 msgCp->fBuf.bufP[msgCp->fBuf.crntIdx++] = 
                    (U8)(GetLoByte(GetLoWord(value)));
              }
           }
        }
        break;

     case CM_PASN_XL_OCTETS:
       {
          U8     len;
          U8     *bytes;
          U32    idx;
   
          len   = (U8)(((TknStrOSXL *)(msgCp->evntStr))->len);
          bytes = (U8*)(((TknStrOSXL *)(msgCp->evntStr))->val);

          if (msgCp->perType == CM_PASN_USE_UALIGN)
          {
             for (idx = 0; idx < len; idx++)
             {
                ret = cmPAsnEncBitField(msgCp, bytes[idx], 
                                             CM_PASN_VAL_EIGHT);
                if(ret != ROK)
                {
                   RETVALUE(RFAILED);
                }
             }
          }
          else
          {
             for (idx = 0; idx < len; idx++)
             {
                if( msgCp->mMgmt == CM_PASN_USE_MBUF)
                {
                   CM_PASN_ENC_BYTE(msgCp,(U8)bytes[idx]);
                }
                else if (msgCp->mMgmt == CM_PASN_USE_SBUF)
                {
                   msgCp->fBuf.bufP[msgCp->fBuf.crntIdx++] = (U8)bytes[idx];
                }
             }
          }
       }
       break;

     default:
       break;
  } /* End switch */
  RETVALUE( ROK);
} /* End of cmPAsnEncMinOct */




/*
*
*       Fun:   cmPAsnEncConInt
*
*       Desc:  This function Encodes a constrained integer 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncConInt
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32  value,             /* Integer value to encode */
U32  lBound,            /* Lower Bound on the integer value */
U32  uBound,             /* Upper Bound on the integer value */
Bool isSigned           /* Is the value signed */
)
#else
PUBLIC S16 cmPAsnEncConInt (msgCp,value,lBound, uBound, isSigned)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32  value;             /* Integer value to encode */
U32  lBound;            /* Lower Bound on the integer value */
U32  uBound;            /* Upper Bound on the integer value */
Bool isSigned;          /* Is the value signed */
#endif
{
   U8             lenUb;       /* Length of Upper Bound */
   U8             lenVal;      /* Length of value */ 
   S16            ret;         /* Return Value */
   U32            val4bytes;   /* 4 octet long value */
   U32            range;       /* Range of values */ 
   U8 N;                       /* To store number of bits PU*/ 
   U32 v;                      /* To store value */

   TRC2 (cmPAsnEncConInt)

   /* cm_pasn2_c_001.main_19 - Fix for compilation warnings */
   lenUb = 0;
   lenVal = 0;

   if (msgCp->perType == CM_PASN_USE_UALIGN)
   {
      UNUSED(lenUb);
      UNUSED(lenVal);
   }
   /* Encoding based on the range of values */
   if( isSigned)
   {
      range = (U32)((S32)uBound - (S32)lBound +1); 
      val4bytes = (U32)((S32)value - (S32)lBound);
   }
   else
   {
      range = (uBound - lBound +1); 
      /* range will be 0 when uBound is maximum U32 */
      val4bytes = (U32)(value - lBound);
   }

   /*                   PER UNALIGNED VARIANT            */ 
   if (msgCp->perType == CM_PASN_USE_UALIGN)
   {
      if( range == CM_PASN_RANGE_ONE)
         /* encoding should be an empty bit field */
         RETVALUE(ROK);

      N = CM_PASN_VAL_NULL;
      v = range;
      v = v - 1;
      CM_PASN_FIND_NOBITS(v,N);
      ret = cmPAsnEncByteField(msgCp,val4bytes,N);
      if(ret != ROK)
      {
         RETVALUE( RFAILED);
      }

      RETVALUE(ROK);   
   }
   else
   {
      if( range == CM_PASN_RANGE_ONE)
         /* encoding should be an empty bit field */
         RETVALUE(ROK);

      if( (range >= CM_PASN_RANGE_TWO) &&
            (range <= CM_PASN_RANGE_255) )
      {
         ret = cmPAsnEncBitField(msgCp,(U8)val4bytes, cmPAsnGetBFSize(range));
         if(ret != ROK)
         {
            RETVALUE(RFAILED);
         }

         RETVALUE(ROK);
      }

      if( range == CM_PASN_RANGE_256)
      {
         /* Octet allign the present buffer */
         CM_PASN_OCTET_ALIGN(msgCp);

         /* Encode least significant byte of val4bytes */
         /* cm_pasn2_c_001.main_22 : kwork fix */
         ret = cmPAsnEncMinOct(msgCp, val4bytes, 1);
         if(ret != ROK)
         {
            RETVALUE(RFAILED); 
         }

         RETVALUE(ROK);
      }

      if( (range > CM_PASN_RANGE_256) &&
            (range <= CM_PASN_RANGE_64K) )
      {
         /* Octet allign the existing buffer */
         CM_PASN_OCTET_ALIGN(msgCp);

         /* Encode the value in 2 octets */
         /* cm_pasn2_c_001.main_22 : kwork fix */
         ret = cmPAsnEncMinOct(msgCp, val4bytes, CM_PASN_TWO_OCTETS);
         if(ret != ROK)
         {
            RETVALUE(RFAILED); 
         }

         RETVALUE(ROK);
      }

      /* Indefinite Length case */
      /* 
       * "len" needs to be encoded first as
       * a constrained integer value with lb =1
       * The ub will not be more than 4 because
       * we are encoding an integer 
       * and so according to range, len should
       * get encoded in bit-field according to
       * sections10.5.3 to 10.5.7.1
       */

      /* Obtain the "ub" for encoding "len" */
      /* "ub" is equal to the number of octets need */
      /* to hold the range of Integer value */

      /* range will be zero when bounds are 0-0xFFFFFFFF */
      /* For all other cases, range will be non zero */
      if( range)
      {
         CM_PASN_FIND_NOOCTET(range,lenUb);
      }
      else
         lenUb = CM_PASN_FOUR_OCTETS;

      /* Find the number of octets needed to encode */
      /* the actual integer value offset from lb */
      CM_PASN_FIND_NOOCTET(val4bytes,lenVal);

      /* Encode "len" as Constrained Integer */
         /* cm_pasn2_c_001.main_22 : kwork fix */
      ret = cmPAsnEncConInt(msgCp, (U32)lenVal, CM_PASN_VAL_ONE, 
                  (U32)lenUb, FALSE);
      if(ret != ROK)
      {
         RETVALUE(RFAILED);
      }

      /* Octet allign the message buffer now */
      CM_PASN_OCTET_ALIGN(msgCp);

      /* 
       * Minimum octet encoding. No leading zeros
       * except when value to encode is zero
       */

         /* cm_pasn2_c_001.main_22 : kwork fix */
      ret = cmPAsnEncMinOct(msgCp, val4bytes, lenVal);
      if(ret != ROK)
      {
         RETVALUE(RFAILED);
      }

      RETVALUE(ROK);
   }
} /* cmPAsnEncConInt */


/*
*
*       Fun:   cmPAsnEncConIntXL
*
*       Desc:  This function Encodes a constrained integer 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncConIntXL
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U8           *value,    /* Integer value to encode */
U8           len,       /* Length of the Integer value to encode */
U8           *lBound,   /* Lower Bound on the integer value */
U8           lbLen,     /* Length of the Lower Bound */
U8           *uBound,   /* Upper Bound on the integer value */
U8           ubLen      /* Length of the Upper Bound */
)
#else
PUBLIC S16 cmPAsnEncConIntXL (msgCp, value, len, lBound, lbLen, uBound, ubLen)
CmPAsnMsgCp  *msgCp;    /* message control pointer */
U8           *value;    /* Integer value to encode */
U8           len;       /* Length of the Integer value to encode */
U8           *lBound;   /* Lower Bound on the integer value */
U8           lbLen;     /* Length of the Lower Bound */
U8           *uBound;   /* Upper Bound on the integer value */
U8           ubLen;     /* Length of the Upper Bound */
#endif
{
   U8             valToEnc[CM_PASN_UINTXL_SIZE]; /* value to encode */ 
   U8             valLen;                        /* Length of the value */ 
   U8             range[CM_PASN_UINTXL_SIZE];    /* Range of values */ 
   U8             rangeLen;                      /* Length of the range */ 
   U8             numBits;                       /* To store number of bits PU*/ 
   S16            ret;                           /* Return Value */

   TRC2 (cmPAsnEncConIntXL)

   /* Encoding based on the range of values */
   {
      U8          diff[CM_PASN_UINTXL_SIZE];
      U8          difflen;
      U8          byte[CM_PASN_VAL_ONE];

      byte[0] = CM_PASN_VAL_ONE;
      cmPAsnSubtractUIntXL(uBound, ubLen, lBound, lbLen, diff, &difflen);
      cmPAsnAddUIntXL(diff, difflen, byte, CM_PASN_VAL_ONE, range, &rangeLen);
      cmPAsnSubtractUIntXL(value, len, lBound, lbLen, valToEnc, &valLen);
   }

   if (msgCp->perType == CM_PASN_USE_UALIGN)
   {
      U8    v[CM_PASN_UINTXL_SIZE];
      U8    vLen;
      U8    byte[CM_PASN_VAL_ONE];

      /* encoding should be an empty bit field */
      if ((rangeLen == 1) && (range[0] == CM_PASN_RANGE_ONE))
         RETVALUE(ROK);
  
      byte[0] = CM_PASN_VAL_ONE;
      cmPAsnSubtractUIntXL(range, rangeLen, byte, CM_PASN_VAL_ONE, v, &vLen);

      numBits = CM_PASN_VAL_NULL;
      CM_PASN_FIND_NOBITS(v[0], numBits);
      numBits = numBits + ((vLen - 1) * CM_PASN_VAL_EIGHT);

      /* cm_pasn2_c_001.main_22 : kwork fix */
      ret = cmPAsnEncByteFieldXL(msgCp, valToEnc, valLen, numBits);
      if (ret != ROK)
         RETVALUE( RFAILED);
  
      RETVALUE(ROK);   
   }
   else
   {
      /* range is 1 then encoding should be an empty bit field */
      if ((rangeLen == 1) && (range[0] == CM_PASN_RANGE_ONE))
         RETVALUE(ROK);

      /* range is less than or equal to 255 */
      if (rangeLen == 1)
      {
         ret = cmPAsnEncBitField(msgCp,(U8)valToEnc[0],
                                      (U32)cmPAsnGetBFSize(range[0]));
         if(ret != ROK)
         {
            RETVALUE(RFAILED);
         }

         RETVALUE(ROK);
      }

      /* range is exactly 256 */
      if ((rangeLen == 2) && (range[0] == 0x01) && (range[1] == 0x00))
      {
         /* Octet allign the present buffer */
         CM_PASN_OCTET_ALIGN(msgCp);

         /* Encode least significant byte of val4bytes */
         /* cm_pasn2_c_001.main_22 : kwork fix */
         ret = cmPAsnEncMinOct(msgCp, (U32)valToEnc[0], 1);
         if(ret != ROK)
         {
            RETVALUE(RFAILED); 
         }

         RETVALUE(ROK);
      }

      /* range is greater than 256 and less than or equal to 64K */
      if ((rangeLen == 2) && !((range[0] == 0x01) && (range[1] == 0x00)))
      {
         U16  *v;

         v = (U16*)&valToEnc;

         /* Octet allign the existing buffer */
         CM_PASN_OCTET_ALIGN(msgCp);

         /* Encode the value in 2 octets */
         /* cm_pasn2_c_001.main_22 : kwork fix */
         ret = cmPAsnEncMinOct(msgCp, (U32)*v, CM_PASN_TWO_OCTETS);
         if (ret != ROK)
            RETVALUE(RFAILED); 

         RETVALUE(ROK);
      }
      /* Indefinite Length case */
      /* 
       * "len" needs to be encoded first as a constrained integer with value
       * lb = 1. The ub will not be more than 4 because we are encoding an 
       * integer and so according to range, len should get encoded in bit-field 
       * according to sections10.5.3 to 10.5.7.1
       */
 
      /* Encode "len" as Constrained Integer */
      /* cm_pasn2_c_001.main_22 : kwork fix */
      ret = cmPAsnEncConInt(msgCp, (U32)valLen, CM_PASN_VAL_ONE, 
                                 (U32)rangeLen, FALSE);
      if(ret != ROK)
      {
         RETVALUE(RFAILED);
      }
 
      /* Octet allign the message buffer now */
      CM_PASN_OCTET_ALIGN(msgCp);
      /* 
       * Minimum octet encoding. No leading zeros
       * except when value to encode is zero
       */
      /* cm_pasn2_c_001.main_22 : kwork fix */
      ret = cmPAsnEncMinOct(msgCp, CM_PASN_VAL_NULL, CM_PASN_XL_OCTETS);
      if(ret != ROK)
      {
         RETVALUE(RFAILED);
      }

      RETVALUE(ROK);
   }
} /* cmPAsnEncConIntXL */



/*
*
*       Fun:   cmPAsnEncSemiConInt
*
*       Desc:  This function Encodes a Semi Constrained 
*              Whole number 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncSemiConInt
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32  value,             /* Integer value to encode */
U32  lBound,            /* Lower Bound */
Bool  isSigned          /* Is the value signed */
)
#else
PUBLIC S16 cmPAsnEncSemiConInt (msgCp,value,lBound,isSigned)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32  value;            /* Integer value to encode */
U32  lBound;           /* Lower Bound */
Bool isSigned;         /* Is the value signed */
#endif
{
 U32  lenVal;         /* length of value */ 
 S16  ret;            /* Return value */
 U32  val4bytes;      /* 4 octet long field */  

 TRC2(cmPAsnEncSemiConInt)

 if (msgCp->perType == CM_PASN_USE_ALIGN)
 {
    /* Octet allign the existing buffer */
    CM_PASN_OCTET_ALIGN(msgCp);
 }
 /* Find the offset to encode */
 if( !isSigned)
    val4bytes = (value - lBound);
 else
    val4bytes = ((S32)value - (S32)lBound); 

 /* Find the number of octets needed to encode */
 /* the actual integer value offset from lb */
 CM_PASN_FIND_NOOCTET(val4bytes,lenVal);

 /* Non-fragmented encoding if len less than 16K */
 if( lenVal < CM_PASN_UNCON_LEN2)
 {
    /* Encode "len" as an Unconstrained length determinant */
    ret = cmPAsnEncUnconLen(msgCp, lenVal);
    if(ret != ROK)
    {
       RETVALUE(RFAILED);
    }

    /* Encode the bytes containing the value  minimum octets */
    ret = cmPAsnEncMinOct(msgCp, val4bytes, (U8)lenVal);
    if(ret != ROK)
    {
       RETVALUE(RFAILED);
    }
 } /* Non-fragmentation case */
 else
 {
    /* Fragmentation procedure of 10.9.3.8 to be applied */
    ret = cmPAsnEncFragVal(msgCp, lenVal, 8);
    if(ret != ROK)
    {
       RETVALUE(RFAILED);
    }
 } 
 RETVALUE(ROK);
} /* End of cmPAsnEncSemiConInt */



/*
*
*       Fun:   cmPAsnEncSemiConIntXL
*
*       Desc:  This function Encodes a Semi Constrained 
*              Whole number 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncSemiConIntXL
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U8           *value,    /* Integer value to encode */
U8           len,       /* Length of the Integer value to encode */
U8           *lBound,   /* Lower Bound on the integer value */
U8           lbLen      /* Length of the Lower Bound */
)
#else
PUBLIC S16 cmPAsnEncSemiConIntXL (msgCp ,value, len, lBound, lbLen)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U8           *value;    /* Integer value to encode */
U8           len;       /* Length of the Integer value to encode */
U8           *lBound;   /* Lower Bound on the integer value */
U8           lbLen;     /* Length of the Lower Bound */
#endif
{
   S16  ret;            /* Return value */
   U32  idx;
   U8   valToEnc[CM_PASN_UINTXL_SIZE];  /* value to encode */  
   U8   valLen;                         /* length of value */ 

   TRC2(cmPAsnEncSemiConIntXL)

   if (msgCp->perType == CM_PASN_USE_ALIGN)
   {
      /* Octet allign the existing buffer */
      CM_PASN_OCTET_ALIGN(msgCp);
   }
   cmPAsnSubtractUIntXL(value, len, lBound, lbLen, valToEnc, &valLen);
   {
      /* Encode "len" as an Unconstrained length determinant */
      /* cm_pasn2_c_001.main_22 : kwork fix */
      ret = cmPAsnEncUnconLen(msgCp, (U32)valLen);
      if (ret != ROK)
         RETVALUE(RFAILED);

      /* Encode the bytes containing the value minimum octets */
      for (idx = 0; idx < valLen; idx++)
      {
      /* cm_pasn2_c_001.main_22 : kwork fix */
         ret = cmPAsnEncMinOct(msgCp, valToEnc[idx], CM_PASN_ONE_OCTET);
         if (ret != ROK)
            RETVALUE(RFAILED);
      }
   }
   RETVALUE(ROK);
} /* End of cmPAsnEncSemiConIntXL */



/*
*
*       Fun:   cmPAsnEncUnconInt
*
*       Desc:  This function Encodes Unconstrained Whole 
*              Number  according to 10.8 of ITU-T
*              REC X-691 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncUnconInt
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          value,     /* Integer value to encode */
Bool         isSigned   /* Is the integer signed type */
)
#else
PUBLIC S16 cmPAsnEncUnconInt (msgCp,value,isSigned)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          value;    /* Integer value to encode */
Bool         isSigned; /* Is the integer signed type */
#endif
{
   U8   length;         /* length of value */ 
   S16  ret;            /* Return value */ 
   U32  intVal;         /* temporary integer value */ 

   TRC2(cmPAsnEncUnconInt)
      /* End of cmPAsnEncUnconInt */
      if (msgCp->perType == CM_PASN_USE_ALIGN)
      {
         /* Octet allign the existing buffer */
         CM_PASN_OCTET_ALIGN(msgCp);
      }
   /* Find the number of octets needed to encode */
   /* this integer value */ 
   intVal = value;
   CM_PASN_FIND_UNCONINTLEN(intVal,length,isSigned);

   /* The "len" should not exceed 4 octets here as */
   /* encoding an Integer value */ 
   /* length to be encoded as Unconstrained , nonfragmented*/
   if (msgCp->perType == CM_PASN_USE_UALIGN)
   {
      ret = cmPAsnEncBitField(msgCp,length,CM_PASN_VAL_EIGHT);
      if(ret != ROK)
      {
         RETVALUE(RFAILED);
      }
   }
   else
   {
      CM_PASN_ENC_BYTE(msgCp,length);
   }
   /* Encode the bytes containing the value */
   ret = cmPAsnEncMinOct(msgCp,(U32)value,length);
   if(ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* End of cmPAsnEncUnconInt */
 

/*
*
*       Fun:   cmPAsnEncUnconIntXL
*
*       Desc:  This function Encodes Unconstrained Whole 
*              Number  according to 10.8 of ITU-T
*              REC X-691 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncUnconIntXL
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U8           *value,    /* Integer value as byte stream */
U8           len        /* length of byte stream */
 )
#else
PUBLIC S16 cmPAsnEncUnconIntXL (msgCp, value, len)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U8           *value;   /* Integer value as byte stream */
U8           len;      /* length of byte stream */
#endif
{
	S16  ret;            /* Return value */ 

	TRC2(cmPAsnEncUnconIntXL)

   if (msgCp->perType == CM_PASN_USE_ALIGN)
   {
      /* Octet allign the existing buffer */
      CM_PASN_OCTET_ALIGN(msgCp);
   }

	/* length to be encoded as Unconstrained, nonfragmented */
	if (msgCp->perType == CM_PASN_USE_UALIGN)
	{
      /* cm_pasn2_c_001.main_22 : kwork fix */
		ret = cmPAsnEncBitField(msgCp, len, CM_PASN_VAL_EIGHT);
		if (ret != ROK)
			RETVALUE(RFAILED);
	}
	else
	{
		CM_PASN_ENC_BYTE(msgCp, len);
	}

      /* cm_pasn2_c_001.main_22 : kwork fix */
	ret = cmPAsnEncMinOct(msgCp, CM_PASN_VAL_NULL, CM_PASN_XL_OCTETS);
	if (ret != ROK)
		RETVALUE(RFAILED);

	RETVALUE(ROK);
} /* End of cmPAsnEncUnconIntXL */



/*
*
*       Fun:   cmPAsnEncUnconLen
*
*       Desc:  This function Encodes Unconstrained Length 
*              Determinant according to 10.9.3.5, 10.9.3.6
*               and 10.9.3.7 of ITU-T
*              REC X-691 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncUnconLen
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32  lenVal             /* Length value to encode */
)
#else
PUBLIC S16 cmPAsnEncUnconLen (msgCp,lenVal)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32  lenVal;            /* Length value to encode */
#endif
{

 S16 ret;         /* Return value */
 U16 val2bytes;  /* Two byte value */

 TRC2(cmPAsnEncUnconLen)

 /*cm_pasn2_c_001.main_15*/
 if (msgCp->perType == CM_PASN_USE_ALIGN)
 { 
    CM_PASN_OCTET_ALIGN(msgCp);
 }

 /* First case: lenVal is less than or equal to 127 */ 
 if( lenVal <= CM_PASN_UNCON_LEN1)
 {
    /* encode the last byte of lenVal */ 
      /* cm_pasn2_c_001.main_22 : kwork fix */
    ret = cmPAsnEncMinOct(msgCp, lenVal, 1);
    if(ret != ROK)
    {
       RETVALUE(RFAILED);
    }
 }

 else
 {
    if( (lenVal > CM_PASN_UNCON_LEN1) && 
          (lenVal < CM_PASN_UNCON_LEN2))
    {
       /* Length is between 127 and 16k */
       val2bytes = (U16)(GetLoWord(lenVal));
       /* Make most significant two bits as 10 */

       /* Set the first two bits (Prefix) of length determinant as 10; OR it
        * instead of AND */ 
       /* val2bytes &= CM_PASN_UNCONLEN_CONST; */
       val2bytes |= 0x8000; 

       if( msgCp->mMgmt == CM_PASN_USE_MBUF)
       { 
          if (msgCp->perType == CM_PASN_USE_UALIGN)
          {
             /* Get the most significant byte */
             ret = cmPAsnEncBitField(msgCp,
                         (U8)GetHiByte(val2bytes),CM_PASN_VAL_EIGHT);
             if(ret != ROK)
             {
                RETVALUE(RFAILED);
             }
             /* Encode least significant byte  */
             ret = cmPAsnEncBitField(msgCp,
                         (U8)GetLoByte(val2bytes),CM_PASN_VAL_EIGHT);
             if(ret != ROK)
             {
                RETVALUE(RFAILED);
             }
          }
          else
          {
             /* Get the most significant byte   */
             CM_PASN_ENC_BYTE(msgCp, (U8)(GetHiByte(val2bytes)) );
             /* Encode least significant byte  */
             CM_PASN_ENC_BYTE(msgCp, (U8)(GetLoByte(val2bytes)) );
          }
       }
       else
       {
          if( msgCp->mMgmt == CM_PASN_USE_SBUF)
          {
             if (msgCp->perType == CM_PASN_USE_UALIGN)
             {
                ret = cmPAsnEncBitField(msgCp,
                            (U8)GetHiByte(val2bytes),CM_PASN_VAL_EIGHT);
                if(ret != ROK)
                {
                   RETVALUE(RFAILED);
                }
                ret = cmPAsnEncBitField(msgCp,
                            (U8)GetLoByte(val2bytes),CM_PASN_VAL_EIGHT);
                if(ret != ROK)
                {
                   RETVALUE(RFAILED);
                }
             }
             else
             {
                msgCp->fBuf.bufP[msgCp->fBuf.crntIdx++] = 
                   (U8)(GetHiByte(val2bytes));
                msgCp->fBuf.bufP[msgCp->fBuf.crntIdx++] = 
                   (U8)(GetLoByte(val2bytes));
             }
          }
       }
    }
 }
 RETVALUE(ROK);
} /* End of cmPAsnEncUnconLen */



/*
*
*       Fun:   cmPAsnEncFragVal
*
*       Desc:  This function Encodes Fragmented Length 
*              Determinant and associated values according 
*              to 10.9.3.8 of ITU-T REC X-691 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncFragVal
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32   lenVal,           /* length determinant value */
U8    itemLen           /* length in bits of each item */ 
)
#else
PUBLIC S16 cmPAsnEncFragVal (msgCp, lenVal,itemLen )
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32   lenVal;          /* Length determinant value */ 
U8    itemLen;         /* length in bits of each item */
#endif
{
  U8    m;             /* value of "m" */
  U8    i;             /* One octet counter */
  U8    itemBits;      /* Number of bits to contain itemLen */
  S16   ret;           /* return value */
  U16   noItems;       /* Number of unfragmented items */
  U32   j;             /* 4 octet counter */
  U32   noBytes;       /* Number of bytes to store items */
  U32   noOctet;       /* Octets to store items */ 
  U32   maxOct;        /* Maximum number of octets */ 
  U32   itemOct;       /* Octets for unfragmented part */ 
  U8    no64KComp;     /* Number of 64K components */

  TRC2(cmPAsnEncFragVal)

  j = 0;
  itemBits = 0;
  maxOct = 0;

  /* For Bits, itemLen is 1, so 8K octets contain 64K items */
  /* For octets, itemLen is 8, so 64K octets contain 64k items */

  CM_PASN_FIND_ITEMBITS(itemLen,itemBits);
  noOctet = (CM_PASN_VAL_8K << itemBits);

  if (msgCp->perType == CM_PASN_USE_ALIGN)
  {
     /* Octet allign the message buffer */
     CM_PASN_OCTET_ALIGN(msgCp);
  }
  /* length and value will appear in fragments */
  if( lenVal > CM_PASN_VAL_64K)
  {
     /* length determinant is more than 64K */
     /* Encode length+value for each of 64k items */

     /* Find number of 64k chunks */
     no64KComp = (U8)(lenVal >> CM_PASN_VAL_SIXTEEN);

     for( i = CM_PASN_VAL_ONE; i<=no64KComp; i++)
     {
       if (msgCp->perType == CM_PASN_USE_UALIGN)
       {
      /* cm_pasn2_c_001.main_22 : kwork fix */
          ret = cmPAsnEncBitField(msgCp,
                   (Data)CM_PASN_FRAG_CONST,CM_PASN_VAL_EIGHT);
          if(ret != ROK)
          {
             RETVALUE(RFAILED);
          }
       }
       else
       {
          CM_PASN_ENC_BYTE(msgCp, (Data)CM_PASN_FRAG_CONST);
       }
        /* Encode 64k value items */
        /* itemLen is the length of single item in Bits */
        for(; j < ( noOctet * i ); j++)
        {
           if (msgCp->perType == CM_PASN_USE_UALIGN)
           {
              ret = cmPAsnEncBitField(msgCp,
                       (Data)(((TknStrOSXL *)(msgCp->evntStr))->val[j]),
                       CM_PASN_VAL_EIGHT);
              if(ret != ROK)
              {
                 RETVALUE(RFAILED);
              }
           }
           else
           { 
              CM_PASN_ENC_BYTE(msgCp, 
                    (Data)(((TknStrOSXL *)(msgCp->evntStr))->val[j]) );
           }
        }
     }
     /* Find value of "m" (between 0 - 3) for next fragment */
     /* lenVal shift right by 14 bits give division by 16K */
 
     m = (lenVal >> CM_PASN_VAL_FOURTEEN) - 
             (CM_PASN_VAL_FOUR * no64KComp);

     if(m)
     {
        /* encode another fragment of length "m*16K" */
        /* encode length first and then value items*/
         if (msgCp->perType == CM_PASN_USE_UALIGN)
         {
      /* cm_pasn2_c_001.main_22 : kwork fix */
            ret = cmPAsnEncBitField(msgCp,
                     (Data)(m | CM_PASN_FRAG_CONST1),CM_PASN_VAL_EIGHT);
            if (ret != ROK)
               RETVALUE(RFAILED);
         }
         else
         {
            CM_PASN_ENC_BYTE(msgCp, (Data)(m | CM_PASN_FRAG_CONST1) );
         }
         /* Encode further "m*16K" items */
         maxOct = ((i - 1) * noOctet) +   
                (m * (CM_PASN_VAL_2K << itemBits) );

        for(; j < (U32) maxOct; j++)
        {
           if (msgCp->perType == CM_PASN_USE_UALIGN)
           {
              ret = cmPAsnEncBitField(msgCp,
                          (Data)(((TknStrOSXL *)(msgCp->evntStr))->val[j]), 
                          CM_PASN_VAL_EIGHT);
              if (ret != ROK)
                 RETVALUE(RFAILED);
           }
           else
           {
              CM_PASN_ENC_BYTE(msgCp, 
                    (Data)(((TknStrOSXL *)(msgCp->evntStr))->val[j]) );
           }
        }
     }

     /* Find the number of items to be encoded in last */
     /* fragment */
     noItems = (lenVal % CM_PASN_VAL_16K);
     if( noItems) 
     {
        ret = cmPAsnEncUnconLen(msgCp, noItems);
        if(ret != ROK)
        {
           RETVALUE(RFAILED);
        }

        /* Find these items will fit in how many bytes */
        itemOct = (noItems << itemBits);

        if( ! (itemOct % CM_PASN_VAL_EIGHT) )
           noBytes = itemOct >> CM_PASN_VAL_THREE;
        else
           noBytes = (itemOct >> CM_PASN_VAL_THREE ) + CM_PASN_VAL_ONE; 
              
        /* Encode these many items */
        for(; j < (U32)( maxOct + noBytes); j++)
        {
           if (msgCp->perType == CM_PASN_USE_UALIGN)
           {
              ret = cmPAsnEncBitField(msgCp,
                          (Data)(((TknStrOSXL *)(msgCp->evntStr))->val[j]),
                          CM_PASN_VAL_EIGHT);
              if(ret != ROK)
              {
                 RETVALUE(RFAILED);
              }
           }
           else
           {
              CM_PASN_ENC_BYTE(msgCp, 
                    (Data)(((TknStrOSXL *)(msgCp->evntStr))->val[j]) );
           }
        }
     }
     else
     {
        /* Last fragment had multiple of 16K items, add a NULL */
        /* byte */
        if (msgCp->perType == CM_PASN_USE_UALIGN)
        {
      /* cm_pasn2_c_001.main_22 : kwork fix */
           ret = cmPAsnEncBitField(msgCp,CM_PASN_VAL_NULL,
                       CM_PASN_VAL_EIGHT);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
        }
        else
        {
           CM_PASN_ENC_BYTE(msgCp, CM_PASN_VAL_NULL);
        }
     }

  } /* End if lenVal is more than 64K */ 

  else
  {
     /* lenVal is between 16K and 64K, inclusive */
     /* Find "m" for the first fragment */

     m = lenVal >> CM_PASN_VAL_FOURTEEN;

     /* encode fragment of length "m*16K" */
     /* encode length first and then value items*/
     if (msgCp->perType == CM_PASN_USE_UALIGN)
     {
        ret = cmPAsnEncBitField(msgCp,
                    (Data)(m | CM_PASN_FRAG_CONST1),CM_PASN_VAL_EIGHT);
        if (ret != ROK)
           RETVALUE(RFAILED);
     }
     else
     {
        CM_PASN_ENC_BYTE(msgCp, (Data)(m | CM_PASN_FRAG_CONST1) );
     }
     /* Encode "m*16K" items */
     maxOct = m * ( CM_PASN_VAL_2K << itemBits);

     for(j = 0; j < maxOct; j++) 
     {
        if (msgCp->perType == CM_PASN_USE_UALIGN)
        {
           ret = cmPAsnEncBitField(msgCp,
                       (Data)(((TknStrOSXL *)(msgCp->evntStr))->val[j]),
                       CM_PASN_VAL_EIGHT);
           if (ret != ROK)
              RETVALUE(RFAILED);
        }
        else
        {
           CM_PASN_ENC_BYTE(msgCp, 
                 (Data)(((TknStrOSXL *)(msgCp->evntStr))->val[j]) );
        }
     }


     /* Find the number of items to be encoded in last */
     /* fragment */
     noItems = (lenVal % CM_PASN_VAL_16K);
     if( noItems != CM_PASN_VAL_NULL) 
     {
        ret = cmPAsnEncUnconLen(msgCp, noItems);
        if(ret != ROK)
        {
           RETVALUE(RFAILED);
        }

        /* Find these items will fit in how many bytes */
        itemOct = noItems << itemBits;

        if( ! (itemOct % CM_PASN_VAL_EIGHT))
           noBytes = (itemOct >> CM_PASN_VAL_THREE);
        else
           noBytes = (itemOct >> CM_PASN_VAL_THREE ) +
              CM_PASN_VAL_ONE; 

        /* Encode these many items */
        for(; j < (U32)( maxOct + noBytes); j++)
        {
           if (msgCp->perType == CM_PASN_USE_UALIGN)
           {
      /* cm_pasn2_c_001.main_22 : kwork fix */
              ret = cmPAsnEncBitField(msgCp,
                          (Data)(((TknStrOSXL *)(msgCp->evntStr))->val[j]),
                          CM_PASN_VAL_EIGHT);
              if (ret != ROK)
                 RETVALUE(RFAILED);
           }
           else
           {
              CM_PASN_ENC_BYTE( msgCp,
                    (Data)(((TknStrOSXL *)(msgCp->evntStr))->val[j]) );
           }
        }
     }
     else
     {
        /* Last fragment had multiple of 16K items, add a NULL */
        /* byte */
        if (msgCp->perType == CM_PASN_USE_UALIGN)
        {
           ret = cmPAsnEncBitField(msgCp,CM_PASN_VAL_NULL,
                       CM_PASN_VAL_EIGHT);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
        }
        else
        {
           CM_PASN_ENC_BYTE(msgCp, CM_PASN_VAL_NULL);
        }
     }
  } /* End else */
  RETVALUE(ROK);
} /* End of cmPAsnEncFragVal */



/*
*
*       Fun:   cmPAsnEncSmallInt
*
*       Desc:  This function Encodes a Normally Small
*              Non-Negative Integer 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncSmallInt
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32  value              /* Integer value to encode */
)
#else
PUBLIC S16 cmPAsnEncSmallInt (msgCp,value)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32  value;             /* Integer value to encode */
#endif
{
 S16 ret;     /* Return value */

  TRC2(cmPAsnEncSmallInt)

  if( (value >= CM_PASN_VAL_NULL) && 
      (value <= CM_PASN_SMALLINT_VAL))
  {
     /* Add a single bit bit-field with value 0 */
     ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_NULL, CM_PASN_VAL_ONE);
     if(ret != ROK)
     {
        RETVALUE(RFAILED);
     }

     /* Encode value in 6 bit long bit field */
     ret = cmPAsnEncBitField(msgCp, (U8)value, (U8)CM_PASN_VAL_SIX);
     if(ret != ROK)
     {
        RETVALUE(RFAILED);
     }
  }
  else
  {
     /* value is more than 63 */ 
     /* Encode a single bit bit field with value 1 */
     /* cm_pasn2_c_001.main_22 : kwork fix */
     ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_ONE, CM_PASN_VAL_ONE);
     if(ret != ROK)
     {
        RETVALUE(RFAILED);
     }

     /* Encode the value as semi-constrained integer */
     /* Lower Bound to be equal to 0 */
     ret = cmPAsnEncSemiConInt(msgCp, value, CM_PASN_VAL_NULL, FALSE);
     if(ret != ROK)
     {
        RETVALUE(RFAILED);
     }
  } 
  RETVALUE(ROK);
} /* End of cmPAsnEncSmallInt */




/*
*
*       Fun:   cmPAsnEncSmallLen
*
*       Desc:  This function Encodes a Normally Small
*              length according to 10.9.3.4 of ITU X-691 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncSmallLen
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32  lenValue           /* Lenght value to encode */
)
#else
PUBLIC S16 cmPAsnEncSmallLen (msgCp,lenValue)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32  lenValue;         /* Length value to encode */
#endif
{

  S16  ret;  /* Return Value */ 

  TRC2(cmPAsnEncSmallLen)

  if( (lenValue > CM_PASN_VAL_NULL) && 
      (lenValue <= CM_PASN_SMALLINT_LEN))
  {
     /* Add a single bit bit-field with value 0 */
   /* cm_pasn2_c_001.main_22 : kwork fix */
     ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_NULL, CM_PASN_VAL_ONE);
     if(ret != ROK)
     {
        RETVALUE(RFAILED);
     }

     /* Encode value in 6 bit long bit field */
   /* cm_pasn2_c_001.main_22 : kwork fix */
     ret = cmPAsnEncBitField(msgCp, (U8)(lenValue-1), (U8)CM_PASN_VAL_SIX);
     if(ret != ROK)
     {
        RETVALUE(RFAILED);
     }
  }
  else
  {
     /* value is more than 64 */ 
     /* Encode a single bit bit field with value 1 */
   /* cm_pasn2_c_001.main_22 : kwork fix */
     ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_ONE, CM_PASN_VAL_ONE);
     if(ret != ROK)
     {
        RETVALUE(RFAILED);
     }

     /* Unfragmenetd length encoding if less than 16K */
     if( lenValue < CM_PASN_UNCON_LEN2)
     {
        ret = cmPAsnEncUnconLen(msgCp, lenValue);
        if(ret != ROK)
        {
           RETVALUE(RFAILED);
        }
     }
     /* Fragmenetd case should be handled within the function */
     /* which is calling this function */
  } 
  RETVALUE(ROK);
} /* End of cmPAsnEncSmallLen */


/*
*
*       Fun:   cmPAsnGetBFSize
*
*       Desc:  This function returns the bit-field size  
*
*       Ret:   ROK 
*
*       Notes: This function is called by for
*       Constrained Integer. This function returns the size
*       of bit field for encoding integer values, constrained
*       by range that is less than 256.
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC U8 cmPAsnGetBFSize
(
U32 range         /* Range of integer values */
)
#else
PUBLIC U8 cmPAsnGetBFSize (range)
U32 range;         /* Range of integer values */
#endif
{
  U8 bfSize;    /* Bit Field size */
  U8 value;     /* value derived from range */ 
  U8 idx;       /* loop idx */

  TRC2(cmPAsnGetBFSize)

#if (ERRCLASS & ERRCLS_DEBUG)
  /* Check that range must be at least 2 */
  if( range < CM_PASN_VAL_TWO)
  {  
     CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN014, (ErrVal) range,
        "cmPAsnGetBFSize Failed, requested range is less than two");
     RETVALUE(RFAILED);
  } 
#endif /* ERRCLASS & ERRCLS_DEBUG */

  bfSize = 0;
  value = (U8)range -1; 

  for(idx=0; idx < CM_PASN_VAL_EIGHT; idx++)
  {
     if( value & CM_PASN_BYTE_MSBONE)
     {
        bfSize =  CM_PASN_VAL_EIGHT - idx;
        break;
     }
  
     value = value << CM_PASN_VAL_ONE;
  }
 
  RETVALUE(bfSize);
 
} /* End of cmPAsnGetBFSize */

/*
*
*       Fun:   cmPAsnEncSeqPreAmb
*
*       Desc:  This function Encodes Sequence ASN.1 data type 
*              preamble bit field
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncSeqPreAmb
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PUBLIC S16 cmPAsnEncSeqPreAmb (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
   U8             elmType;     /* Element as Optional, Mandatory */
   S16            ret;         /* Return Value */
   CmPAsnElmDef   *seqElmDef;  /* pointer to Sequence element defintion */
   CmPAsnElmDef   *elmDef;     /* pointer for element def of components */
   CmPAsnSetSeqDef *pElmSpec;  /* Element specific definition */

   TRC2(cmPAsnEncSeqPreAmb)

   seqElmDef = *msgCp->elmDef;
   pElmSpec = (CmPAsnSetSeqDef *)seqElmDef->typeSpecDef; 

   if( pElmSpec->preAmLen < CM_PASN_VAL_64K)
   {
      /* Go through each component of Sequence type */
      /* in it's extension root and if Optional, encode */
      /* Bit field of size 1 with value 0 or 1 */

      /* initialise elmDef and evntStr to point to the */
      /* first component of the Sequence type */  
      msgCp->elmDef = pElmSpec->ft; 
      elmDef = *msgCp->elmDef;

      /* Increment Eventstructure over Present token */
      msgCp->evntStr = (TknU8 *)((PTR) msgCp->evntStr +
            sizeof(TknPres));

      /* Scan through all components in extension root */
      while ( (elmDef->type != CM_PASN_TET_SETSEQ_TERM) &&
            (elmDef->type != CM_PASN_TET_EXT_MKR) )
      {
         /* If element is default or optional */
         elmType = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);
         if( (elmType == CM_PASN_ELM_OPT) ||
               (elmType == CM_PASN_ELM_DEF) )
         {
            /* If value is equal to default value then skip encoding */
            if(elmType == CM_PASN_ELM_DEF)
            {
               CmPAsnElmDef *temp_elm;
               U8 type;
               U8 pres;

               temp_elm = *msgCp->elmDef;
               type = temp_elm->type;
               pres = PRSNT_NODEF;
               /*cm_pasn2_c_001.main_15*/
               if(msgCp->evntStr->pres == NOTPRSNT)
               {
                   msgCp->evntStr->pres = PRSNT_NODEF;
                   cmPAsnUpdDefVal(msgCp->evntStr, temp_elm); 
               }
               else
               {
                  /* Set present flag */
                  msgCp->evntStr->pres = PRSNT_NODEF;
               }
               
               /* Find if it's value is present */
               if( msgCp->evntStr->pres == PRSNT_NODEF)
               {
                  switch(type)
                  {
                     /* cm_pasn2_c_001.main_17 - corrected typecast */
                     case CM_PASN_TET_SINT8 :
                        /* cm_pasn2_c_001.main_21: Fixed warning for g++ compilation on Linux */
                        if((((TknS8 *)(msgCp->evntStr))->val) > 0)
                        { 
                           if((U8)(((TknS8 *)(msgCp->evntStr))->val) == (PTR)((S8 *)(temp_elm->defVal)))
                           {
                              (((TknS8 *)(msgCp->evntStr))->pres) = NOTPRSNT;
                              pres = NOTPRSNT;
                           }
                        }
                        break;

                     case CM_PASN_TET_SINT16 :
                        /* cm_pasn2_c_001.main_21: Fixed warning for g++ compilation on Linux */
                        if((((TknS8 *)(msgCp->evntStr))->val) > 0)
                        {
                           if((U8)(((TknS16 *)(msgCp->evntStr))->val) == (PTR)((S16 *)(temp_elm->defVal)))
                           {
                              (((TknS16 *)(msgCp->evntStr))->pres) = NOTPRSNT;
                              pres = NOTPRSNT;
                           }
                        }

                        break;

                     case CM_PASN_TET_SINT32 :
                        /* cm_pasn2_c_001.main_21: Fixed warning for g++ compilation on Linux */
                        if((((TknS8 *)(msgCp->evntStr))->val) > 0)
                        {               
                           if((U8)(((TknS32 *)(msgCp->evntStr))->val) == (PTR)((S32 *)(temp_elm->defVal)))
                           {
                              (((TknS32 *)(msgCp->evntStr))->pres) = NOTPRSNT;
                              pres = NOTPRSNT;
                           }
                        }

                        break;

                     case CM_PASN_TET_BOOL :
                     case CM_PASN_TET_UINT8 :
                        /* cm_pasn2_c_001.main_21: Fixed warning for g++ compilation on Linux */
                        if((((TknS8 *)(msgCp->evntStr))->val) > 0)
                        {
                           if((U8)(((TknU8 *)(msgCp->evntStr))->val) == (PTR)((U8 *)(temp_elm->defVal)))
                           {
                              (((TknU8 *)(msgCp->evntStr))->pres) = NOTPRSNT;
                              pres = NOTPRSNT;
                           }
                        }

                        break;
                     case CM_PASN_TET_UINT16 :
                        /* cm_pasn2_c_001.main_21: Fixed warning for g++ compilation on Linux */
                        if((((TknS8 *)(msgCp->evntStr))->val) > 0)
                        {
                           if((U8)(((TknU16 *)(msgCp->evntStr))->val) == (PTR)((U16 *)(temp_elm->defVal)))
                           {
                              (((TknU16 *)(msgCp->evntStr))->pres) = NOTPRSNT;
                              pres = NOTPRSNT;
                           }
                        }
                        break;

                     case CM_PASN_TET_UINT32 :
                        /* cm_pasn2_c_001.main_21: Fixed warning for g++ compilation on Linux */
                        if((((TknS8 *)(msgCp->evntStr))->val) > 0)
                        {
                           if((U8)(((TknU32 *)(msgCp->evntStr))->val) == (PTR)((U32 *)(temp_elm->defVal)))
                           {
                              msgCp->evntStr->pres = NOTPRSNT;
                              pres = NOTPRSNT;
                           }
                        }

                        break;
                  }
                  if(pres)
                  {
                     /* Encode a single bit BF with value 1 */
                     /* cm_pasn2_c_001.main_22 : kwork fix */
                     ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_ONE, 
                              CM_PASN_VAL_ONE);
                     if (ret != ROK)
                        RETVALUE(RFAILED);
                  }
                  else
                  {
                     /* Encode a single bit BF with value 0 */
                     /* cm_pasn2_c_001.main_22 : kwork fix */
                     ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_NULL, 
                              CM_PASN_VAL_ONE);
                     if (ret != ROK)
                        RETVALUE(RFAILED);
                  }
               }
               else
               {
                  /* IE with default is mandatory */
                  RETVALUE(RFAILED);
               }
            }
            else
            {
               /* Find if it's value is present */
               if( msgCp->evntStr->pres == PRSNT_NODEF)
               {
                  /* Encode a single bit BF with value 1 */
                  /* cm_pasn2_c_001.main_22 : kwork fix */
                  ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_ONE, 
                           CM_PASN_VAL_ONE);
                  if (ret != ROK)
                     RETVALUE(RFAILED);
               }
               else
               {
                  /* Encode a single bit BF with value 0 */
                  /* cm_pasn2_c_001.main_22 : kwork fix */
                  ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_NULL, 
                           CM_PASN_VAL_ONE);
                  if (ret != ROK)
                     RETVALUE(RFAILED);
               }
            }
         }

         /* Increment the pointers to skip to next element */
         CM_PASN_SKIP_ELM(msgCp);
         elmDef = *msgCp->elmDef;
         /* Since we are skipping elements, the extension marker */
         /* or sequence terminator of only outermost sequence type */
         /* should be encountered */

      }
   } /* End of preamble length is less than 64K */

   else
   {
      /* Preamble is greater or equal to 64 K */
      /* Encode preamble using fragmentation */
   } 
   RETVALUE(ROK);
} /* End of cmPAsnEncSeqPreAmb */



/*
*
*       Fun:   cmPAsnEncSeqExt
*
*       Desc:  This function Encodes Sequence ASN.1 data type 
*              extension additions presence bit field and
*              extension additions as open types 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncSeqExt
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          nmbExtMkrs /* Number of extension additions */
)
#else
PUBLIC S16 cmPAsnEncSeqExt (msgCp, nmbExtMkrs)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          nmbExtMkrs;   /* Number of extension additions */
#endif
{
   U32           idx;           /* Loop variable */
   S16           ret;             /* Return Value */
   CmPAsnElmDef  **savElmDef;     /* Saved element definition */
   TknU8         *savEvntStr;     /* Saved event structure */ 
 
   TRC2(cmPAsnEncSeqExt)

   /* Definition pointing to first extension addition */
   savElmDef = msgCp->elmDef;
   savEvntStr = msgCp->evntStr;
 
   /* Scan through all extension additions */
   for( idx=0; idx < nmbExtMkrs; idx++)
   {
      /* Find if extension addition value is present */
      if( msgCp->evntStr->pres == PRSNT_NODEF)
      {
         /* Encode a single bit BF with value 1 */
         /* cm_pasn2_c_001.main_22 : kwork fix */
         ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_ONE, CM_PASN_VAL_ONE);
         if(ret != ROK)
         {
             RETVALUE(RFAILED);
         }
      }
      else
      {
         /* Encode a single bit BF with value 0 */
         /* cm_pasn2_c_001.main_22 : kwork fix */
         ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_NULL, CM_PASN_VAL_ONE);
         if(ret != ROK)
         {
             RETVALUE(RFAILED);
         }
      }
      /* Increment the pointers to skip to next element */
      CM_PASN_SKIP_ELM(msgCp);
  }

  /* Reset element definition and event to first extension */ 
  CM_PASN_RESET_MSGCP_PTR(msgCp, savElmDef, savEvntStr);

  /* Now encode the present additions as Open types */
  for( idx = 0; idx < nmbExtMkrs; idx++)
  {
     if(msgCp->evntStr->pres == PRSNT_NODEF)
     {
         /* cm_pasn2_c_001.main_22 : kwork fix */
        ret = cmPAsnEncOTElm(msgCp);
        if(ret != ROK)
        {
           RETVALUE(RFAILED);
        }
     }
     else
        /* Simply skip the element in event and database */
       CM_PASN_SKIP_ELM(msgCp);
  }
  RETVALUE(ROK);
} /* End of cmPAsnEncSeqExt */



/*
*
*       Fun:   cmPAsnEncSeqComp
*
*       Desc:  This function Encodes Sequence ASN.1 data type 
*              component types 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncSeqComp
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PUBLIC S16 cmPAsnEncSeqComp (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
   S16            ret;         /* Return Value */
   CmPAsnElmDef   *elmDef;     /* pointer for element def of components */
   CmPAsnSetSeqDef *pElmSpec;  /* Sequence specific definition */

   TRC2(cmPAsnEncSeqComp)
 
   elmDef = *msgCp->elmDef; 
   pElmSpec = (CmPAsnSetSeqDef *)elmDef->typeSpecDef;

   /* Increment element definition to point to first component */
   msgCp->elmDef = pElmSpec->ft;
   elmDef = *msgCp->elmDef;

   /* Increment event structure over Present token */
   msgCp->evntStr = (TknU8 *)((PTR) msgCp->evntStr +
                                    sizeof(TknPres));

   while( (elmDef->type != CM_PASN_TET_SETSEQ_TERM) &&
          (elmDef->type != CM_PASN_TET_EXT_MKR))
   {
      /* Encode the element depending on element type */
   /* cm_pasn2_c_001.main_22 : kwork fix */
      ret = cmPAsnEncElm(msgCp);
      if(ret != ROK)
      {
         RETVALUE(RFAILED);
      }
      
      elmDef = *msgCp->elmDef;
   }
   RETVALUE(ROK);
} /* End of cmPAsnEncSeqComp */
      


/*
*
*       Fun:   cmPAsnEncSeqExtBit
*
*       Desc:  This function Encodes Sequence ASN.1 data type 
*              extension bit 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncSeqExtBit
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
Bool         *extFlag   /* Extension Bit Flag */
)
#else
PUBLIC S16 cmPAsnEncSeqExtBit (msgCp, extFlag)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
Bool         *extFlag; /* extenstion bit flag */ 
#endif
{
   U8             flag;        /* Flag */
   U32            idx;         /* Loop variable */ 
   S16            ret;         /* Return Value */
   CmPAsnElmDef   *elmDef;     /* pointer for element def of components */
   CmPAsnElmDef   *seqElmDef;  /* pointer to begining of sequence */
   CmPAsnSetSeqDef *pElmSpec;  /* pointer to element specific define */
 
   TRC2(cmPAsnEncSeqExtBit)
 
   *extFlag = FALSE; 
   seqElmDef = *msgCp->elmDef;
   pElmSpec = (CmPAsnSetSeqDef *)seqElmDef->typeSpecDef;

   /* Get pointers to begining of extension addition */
   msgCp->elmDef = pElmSpec->ft; 
   msgCp->elmDef = (CmPAsnElmDef **)((PTR)msgCp->elmDef +
                                     pElmSpec->extMkrDbOff);
   msgCp->evntStr = (TknU8 *)((PTR)msgCp->evntStr + pElmSpec->extMkrEvOff);
 
   /* Find if there are any extension additions with values */
   for( idx=0; idx < (U32)pElmSpec->nmbExtMkrs; 
                                         idx++)
   {
      /* Get element definition of extension addition */
      elmDef = *msgCp->elmDef;

#if (ERRCLASS & ERRCLS_DEBUG)
      /* Check that end of sequence type is not encountered */
      if( elmDef->type == CM_PASN_TET_SETSEQ_TERM)
      {  
         CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN015, (ErrVal) ERRZERO,
              "cmPAsnEncSeq Failed, wrong number of extension members");
         RETVALUE(RFAILED);
      } 
#endif /* ERRCLASS & ERRCLS_DEBUG */

      if( msgCp->evntStr->pres == PRSNT_NODEF)
      {
         if( !(*extFlag) )
         {
            /* Set extension bit in encoding to 1 only once */
            /* cm_pasn2_c_001.main_22 : kwork fix */
            ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_ONE,
                     CM_PASN_VAL_ONE);
            if(ret != ROK)
            {
               RETVALUE(RFAILED);
            }
         }

         /* Set extension bit set flag */
         *extFlag = TRUE;
      }
      else
      {
         flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);
         /* check if element is mandatory */
         if (flag == CM_PASN_ELM_MAND)
         {
            /* mandatory element is missing */
            CM_PASN_ERR(msgCp, CM_PASN_MAND_MIS);  
            RETVALUE(RFAILED);
         }
         /* ignore ignorable mandatory only if the flag igExtMand is set */
         else if( flag == CM_PASN_ELM_MANDIGN)
         {
            /* Mandatory ignorable element */
            if(!msgCp->igExtMand)
            {
               /* If user does not want to ignore these IEs */
               CM_PASN_ERR(msgCp, CM_PASN_MAND_MIS);  
               RETVALUE(RFAILED);
            }
         }
      } 

      /* Skip to next element */
      CM_PASN_SKIP_ELM(msgCp);

   }

   if( !(*extFlag))
   {
      /* No extension addition values are present */
      /* Encode extension bit with value 0 */
      /* cm_pasn2_c_001.main_22 : kwork fix */
      ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_NULL, CM_PASN_VAL_ONE);
      if(ret != ROK)
      {
          RETVALUE(RFAILED);
      }
   }
   RETVALUE(ROK);
} /* End of cmPAsnEncSeqExtBit */



/*
*
*       Fun:   cmPAsnEncSeqOfNoComp
*
*       Desc:  This function encodes Number of components in 
*              Set, Sequence of ASN.1 data type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncSeqOfNoComp
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
Bool         *fragFlag  /* Fragmentation Flag */
)
#else
PUBLIC S16 cmPAsnEncSeqOfNoComp (msgCp, fragFlag)
CmPAsnMsgCp  *msgCp;    /* message control pointer */
Bool         *fragFlag; /* Fragmentation Flag */
#endif
{

  S16               ret;         /* Return Value */
  U16               numComp;      /* Number of components */
  U32               min;         /* Minimum componenets */
  CmPAsnElmDef      *elmDef;     /* Element definition */
  CmPAsnSetSeqOfDef *elmSpecDef; /* Element specific definition */

  TRC2(cmPAsnEncSeqOfNoComp)

  elmDef = *msgCp->elmDef; 
  *fragFlag = FALSE;

  elmSpecDef = (CmPAsnSetSeqOfDef *)(elmDef->typeSpecDef);
 
  /* Set the lower bound to zero if not set */
  if( elmSpecDef->min == CM_PASN_MINUS_INF)
     min = 0;
  else
     min = elmSpecDef->min;

  /* Find actual number of components to encode */
  numComp = ((TknU16 *)msgCp->evntStr)->val; 

  /* Extension Marker present in Sequence Of definition */
  if(elmDef->extMkr)
  {
     /* Number of components are beyond the range */
     if( (numComp > elmSpecDef->max) ||
         (numComp < min) )
     {
        /* Encode extension bit as 1 */
        /* cm_pasn2_c_001.main_22 : kwork fix */
        ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_ONE, CM_PASN_VAL_ONE);
        if(ret != ROK)
        {
           RETVALUE(RFAILED);
        }

        /* Encode numComp as Semi Constrained Number */
        /* according to 10.9.6.5 of ITU X-691 */
        if(numComp < CM_PASN_VAL_16K)
        {
           ret = cmPAsnEncUnconLen(msgCp, numComp);
           if(ret != ROK)
           {
              RETVALUE(RFAILED); 
           }
        }
        else
           /* Fragmentation Required */
           *fragFlag = TRUE;

        /* Return from the function */
        RETVALUE(ROK);
     }
     else
     {
        /* Number of components within range */
        /* Encode extension bit as 0 */
        /* cm_pasn2_c_001.main_22 : kwork fix */
        ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_NULL, CM_PASN_VAL_ONE);
        if(ret != ROK)
        {
           RETVALUE(RFAILED);
        }

        /* Continue as if extension mkr is absent */

     } /* numComp with in range */
  } /* Extension marker present */

  /* Extension marker is absent */
/* cm_pasn2_c_002.main_13 */
  if ((numComp < elmSpecDef->min) || (numComp >  elmSpecDef->max))
  {
     RETVALUE(RFAILED);
  }

  if( (elmSpecDef->max != CM_PASN_PLUS_INF) &&
      (elmSpecDef->max < CM_PASN_VAL_64K)) 
  {
     if(elmSpecDef->max != min)
     {
        /* Encode numComp as Constrained Integer */
        /* cm_pasn2_c_001.main_22 : kwork fix */
        ret = cmPAsnEncConInt(msgCp, (U32)numComp ,
                 min, elmSpecDef->max, FALSE);
        if(ret != ROK)
          RETVALUE(RFAILED);
     }
  }
  else
  {
     /* Encode numComp as Semi Constrained */
     /* according to 10.9.6.5 of ITU X-691 */
     if( numComp < CM_PASN_VAL_16K)
     {
        ret = cmPAsnEncUnconLen(msgCp, numComp);
        if(ret != ROK)
        {
           RETVALUE(RFAILED); 
        }
     }
     else
        *fragFlag = TRUE;
  }
  RETVALUE(ROK);
} /* End of cmPAsnEncSeqOfNoComp */ 



/*
*
*       Fun:   cmPAsnEncStrLen
*
*       Desc:  This function encodes length of 
*              Bit and octet String ASN.1 data type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncStrLen
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          length,    /* String length */
U32          min,       /* lower bound */
U32          max,       /* upper Bound */ 
Bool         *fragFlag,  /* Fragmentation Flag */
U8           strType    /* String type */
)
#else
PUBLIC S16 cmPAsnEncStrLen (msgCp,length,min,max, fragFlag,strType)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          length;   /* Length value */
U32          min;      /* Lower Bound */
U32          max;      /* Upper Bound */
Bool         *fragFlag; /* Fragmentation Flag */
U8           strType;  /* String Type */
#endif
{
  U8                multiplier;  /* 8 bits per byte */
  S16               ret;         /* Return Value */
  CmPAsnElmDef      *elmDef;     /* Element definition */

  TRC2(cmPAsnEncStrLen)

  elmDef = *msgCp->elmDef;
  *fragFlag = FALSE;
  multiplier = CM_PASN_VAL_ONE;

  if (msgCp->perType == CM_PASN_USE_ALIGN)
  {
     if( strType == CM_PASN_OCTSTR_TYPE)
        multiplier = CM_PASN_VAL_EIGHT;
  }

  /* Extension Marker present in String definition */
  if(elmDef->extMkr)
  {
     /* Number of components are beyond the range */
     if( (length > max) ||
         (length < min) )
     {
        /* Encode extension bit as 1 */
        /* cm_pasn2_c_001.main_22 : kwork fix */
        ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_ONE, CM_PASN_VAL_ONE);
        if(ret != ROK)
        {
           RETVALUE(RFAILED);
        }

        /* Encode length as Semi Constrained Number */
        /* according to 10.9.3.5 of ITU X-691 */
        if( length < CM_PASN_VAL_16K)
        {
        /* cm_pasn2_c_001.main_22 : kwork fix */
           ret = cmPAsnEncUnconLen(msgCp, (U32)length);
           if(ret != ROK)
           {
              RETVALUE(RFAILED); 
           }
        }
        else
           /* Fragmentation Required */
           *fragFlag = TRUE;

        /* Return from the function */
        RETVALUE(ROK);
     }
     else
     {
        /* Number of components within range */
        /* Encode extension bit as 0 */
        /* cm_pasn2_c_001.main_22 : kwork fix */
        ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_NULL, CM_PASN_VAL_ONE);
        if(ret != ROK)
        {
           RETVALUE(RFAILED);
        }

        /* Continue as if extension mkr is absent */

     } /* length with in range */
  } /* Extension marker present */

  /* Extension marker is absent */
  /* length to be encoded if ub is not equal to lb */
  
  if(!max)
     /* ub is zero, so no length encode */
     RETVALUE(ROK);

  if( ( max == min) && ((U32)length <= CM_PASN_VAL_64K-1))
  {
     /* No length encode here */
     if( length * multiplier >  CM_PASN_VAL_SIXTEEN)
     {
  if (msgCp->perType == CM_PASN_USE_ALIGN)
  {
        /* Octet allign the buffer */
        CM_PASN_OCTET_ALIGN(msgCp);
  }
     }
 
     RETVALUE(ROK);
  }
  
  if(max != min)
  {
     if( (max != CM_PASN_PLUS_INF) &&
         (max < CM_PASN_VAL_64K)) 
     {
         /* Encode length as Constrained Integer */
         /* cm_pasn2_c_001.main_22 : kwork fix */
         ret = cmPAsnEncConInt(msgCp, (U32)length, min, max,FALSE);
         if(ret != ROK)
         {
             RETVALUE(RFAILED);
         }

         if (msgCp->perType == CM_PASN_USE_ALIGN)
         {
            /* Octet allign the buffer */
            CM_PASN_OCTET_ALIGN(msgCp);
         }
     }
     else
     {
        /* Encode length as Semi Constrained */
        /* according to 10.9.3.5 of ITU X-691 */ 
        if( length < CM_PASN_VAL_16K)
        {
           ret = cmPAsnEncUnconLen(msgCp, (U32)length);
           if(ret != ROK)
           {
              RETVALUE(RFAILED); 
           }
        }
        else
           /* Fragmentation Required */ 
           *fragFlag = TRUE;
     }
  }
  RETVALUE(ROK);
} /* End of cmPAsnEncStrLen */ 


/*
*
*       Fun:   cmPAsnEncStrVal
*
*       Desc:  This function encodes value of 
*              Bit and octet String ASN.1 data type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncStrVal
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U16          length,    /* String length */
Bool         fragFlag,  /* Fragmentation Flag */
U8           strType    /* String type */
)
#else
PUBLIC S16 cmPAsnEncStrVal (msgCp,length, fragFlag, strType)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U16          length;   /* Length value */
Bool         fragFlag; /* Fragmentation Flag */
U8           strType;  /* String Type */
#endif
{
  Bool              bufOctAlignFlg;  /* Octet align flag */ 
  Bool              isXlStr;       /* Is it an extra large string */
  U8                bitVal;      /* Bit value */
  U8                noBits;      /* Number of bits */
  U8                multiplier;  /* Number of bits per byte */
  U16               i;           /* Loop variable */
  U16               noBytes;     /* Number of bytes */
  S16               ret;         /* Return Value */
  CmPAsnElmDef      *elmDef;     /* Element definition */
  TknStr4           *evntStr;    /* Event structure */
  TknStrOSXL        *xlStr;      /* Extra Large event structure */

  TRC2(cmPAsnEncStrVal)

  noBits = 0;
  isXlStr = FALSE;
  bufOctAlignFlg = FALSE; 
  elmDef = *msgCp->elmDef;
  evntStr = (TknStr4 *)msgCp->evntStr;
  xlStr = (TknStrOSXL *)msgCp->evntStr;

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

 if( (elmDef->type == CM_PASN_TET_OCTSTRXL) ||
     (elmDef->type == CM_PASN_TET_BITSTRXL) )
    isXlStr = TRUE;

  if(fragFlag)
  {
     /* If fragmentation is required */
     /* cm_pasn2_c_001.main_22 : kwork fix */
     ret = cmPAsnEncFragVal(msgCp, length, multiplier);
     if(ret != ROK)
     {
        RETVALUE(RFAILED);
     }
   
     RETVALUE(ROK);
  }

  /* If fragmentation is not required */
  /* Message buffer was alligned while encoding length */
  /* wherever necessary */
  /* Check if buffer is octet alligned */
  if (msgCp->perType == CM_PASN_USE_UALIGN)
  {
      /* Begin encoding bit/byte into message buffer */
      if( strType == CM_PASN_BITSTR_TYPE)
      {
         noBytes = length / CM_PASN_VAL_EIGHT;
         noBits = length % CM_PASN_VAL_EIGHT; 
      }
      else
         noBytes = length;
      for( i =0; i < noBytes; i++)
      {
     
         if( isXlStr)
         {
            /* Extra Large String */
            /* cm_pasn2_c_001.main_22 : kwork fix */
            ret = cmPAsnEncBitField(msgCp,
                          (Data)(xlStr->val[i]),CM_PASN_VAL_EIGHT);
            if(ret != ROK)
            {
               RETVALUE(RFAILED);
            }
         }
         else
         { 
            ret = cmPAsnEncBitField(msgCp, evntStr->val[i],
                     CM_PASN_VAL_EIGHT);
            if(ret != ROK)
            {
               RETVALUE(RFAILED);
            }
         }  
      }         
      if( strType == CM_PASN_BITSTR_TYPE)
      {
         /* Now encode the remaining bits */
         /* Bit Field function expects these bits as LSB */
         if( isXlStr)
            bitVal = xlStr->val[noBytes];
         else
            bitVal = evntStr->val[noBytes];

         bitVal = (bitVal >> (CM_PASN_VAL_EIGHT - noBits)); 

         ret = cmPAsnEncBitField(msgCp, bitVal, noBits);
         if(ret != ROK)
         {
               RETVALUE(RFAILED); 
         }
      }
  }
  else
  {
     if( msgCp->bhldr.nxtBitPos == CM_PASN_NXTBITPOS_EIGHT)
        /* Set buffer octet align flag */
        bufOctAlignFlg = TRUE;

     /* Begin encoding bit/byte into message buffer */
     if( strType == CM_PASN_BITSTR_TYPE)
     {
        noBytes = length / CM_PASN_VAL_EIGHT;
        noBits = length % CM_PASN_VAL_EIGHT; 
     }
     else
        noBytes = length;

     for( i =0; i < noBytes; i++)
     {
        /* If no octet allignment, add as bit field */
        if( !bufOctAlignFlg)
        {
           /* This will be the case only when size is fixed */
           /* and is less than or equal to 2 octets */ 
           /* Note: No typecasting is needed for event structures */
           /* as all tokens used for octet/bit strings have */
           /* same offset for val */ 
            /* cm_pasn2_c_001.main_22 : kwork fix */
           ret = cmPAsnEncBitField(msgCp, evntStr->val[i],
                       CM_PASN_VAL_EIGHT);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }
        }
        else
        {
           /* Buffer is already octet alligned */
           /* SAddPstMsg can be done to add Bit String */
           if( isXlStr)
           {
              /* Extra Large String */
              CM_PASN_ENC_BYTE(msgCp, (Data)(xlStr->val[i]));
           }
           else
           {
              CM_PASN_ENC_BYTE(msgCp, (Data)(evntStr->val[i]));
           }   
        }
     } 

     if( noBits > 0 && (strType == CM_PASN_BITSTR_TYPE)  )
     {
        /* Now encode the remaining bits */
        /* Bit Field function expects these bits as LSB */
        /* cm_pasn2_c_001.main_13 : fix for correct index  */
        if( isXlStr)
           bitVal = xlStr->val[noBytes];
        else
           bitVal = evntStr->val[noBytes];

        bitVal = (bitVal >> (CM_PASN_VAL_EIGHT - noBits)); 

        /* cm_pasn2_c_001.main_22 : kwork fix */
        ret = cmPAsnEncBitField(msgCp, bitVal, noBits);
        if(ret != ROK)
        {
           RETVALUE(RFAILED); 
        }
     }

  }
  RETVALUE(ROK);
} /* End of cmPAsnEncStrVal */ 


/*
*
*       Fun:   cmPAsnFragEnc
*
*       Desc:  This function fragments an encoded field list  which
*              is Octets. It inserts the fragment length bytes in the
*              stream 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnFragEnc
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          len        /* Total length of encoded field list */
)
#else
PUBLIC S16 cmPAsnFragEnc(msgCp,len)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          len;      /* Total length of encoded field list */
#endif
{
  S16        ret;
  U32        m;    
  U8         i;   
  U8         a;       /* Number of 64K components */
  U8         b;       /* Number of 48K components */ 
  U8         c;       /* Number of 32K components */ 
  U8         d;       /* Number of 16K components */ 
  U8         encByte; /* Byte to encode */
  MsgLen     msgLen;  /* Message Length */
  MsgLen     msgIdx;  /* Index in the message */
  MsgLen     cCnt;
  U8         pkArray[2];  /* Pack array */
  Bool       firstTime;

  TRC3(cmPAsnFragEnc)

  m = len;
  a = 0;
  b = 0;
  c = 0;
  d = 0;
  msgLen = 0;
  firstTime = TRUE; 

  /* Determine how many 64k components */
  if(m >= CM_PASN_VAL_64K)
  {
     a = m >> 16;

     /* Get the left over value */
     m = m - (a << 16 );
  }

  /* Determine if any 48k component */
  if( m >= CM_PASN_VAL_48K )
  {
    b = 1;
    m = (m - CM_PASN_VAL_48K);
  }
  else
  {
     /* If no 48K component, then check for 32k component */
     if( m >= CM_PASN_VAL_32K )
     {
        c = 1;
        m = (m - CM_PASN_VAL_32K);
     }
     /* Else check for any 16k component */
     else if( m >= CM_PASN_VAL_16K )
     {
        d = 1;
        m = (m - CM_PASN_VAL_16K);
     }
  }

  /* Get the present lenght of the mBuf */
/* cm_pasn2_c_001.main_22 : kwork fix */
  ret = SFndLenMsg(msgCp->mBuf, &msgLen);
  if (ret != ROK)
     RETVALUE(RFAILED);

  /* Find the idx in the message where we will put the
     first fragment lenght field: Subtract from the present
     message length, the length of the this particular IE */
  msgIdx = msgLen - (MsgLen)len;

  for(i=0; i< a; i++)
  {
    encByte = 0xc4; /* 1100 0100 */

    if( firstTime)
    {
       /* FirstTime */
       /* Replace the place holder length byte */
       SRepMsg(encByte, msgCp->mBuf, msgIdx - 1); 
       /* Increment the msgIdx by 64K octets */
       msgIdx += (MsgLen)CM_PASN_VAL_64K;
       firstTime = FALSE; 
    }
    else 
    { 
       /* Insert 64k segment length byte here */
       /* cm_pasn2_c_001.main_22 : kwork fix */
       ret = SCpyFixMsg((Data *)&encByte, msgCp->mBuf,
                           msgIdx, (MsgLen)CM_PASN_VAL_ONE, &cCnt);
       if(ret != ROK)
       {
          RETVALUE(RFAILED);
       }
       /* Increment the msgIdx by 64K octets */
       msgIdx += ((MsgLen)CM_PASN_VAL_64K+1);
    }
  }

  /* Add any 48K fragment */
  if(b)
  {
     encByte = 0xc3; /* 1100 0011 */

     if(firstTime)
     {
       /* Replace the place holder length byte */
       SRepMsg(encByte, msgCp->mBuf, msgIdx - 1); 
       /* Increment the msgIdx by 64K octets */
       msgIdx += CM_PASN_VAL_48K;
       firstTime = FALSE; 
     }
     else
     {
        /* Insert 48k segment length byte here */
        /* cm_pasn2_c_001.main_22 : kwork fix */
        ret = SCpyFixMsg((Data *)&encByte, msgCp->mBuf,
                           msgIdx, (MsgLen)CM_PASN_VAL_ONE, &cCnt);
        if(ret != ROK)
        {
          RETVALUE(RFAILED);
        }
        /* Increment the msgIdx by 48K octets */
        msgIdx += (CM_PASN_VAL_48K+1);
     }
  }
  else
  {
     /* Check if any 32k component */
     if(c)
     {
        encByte = 0xc2; /* 1100 0010 */
     
        if(firstTime)
        {
           /* Replace the place holder length byte */
           SRepMsg(encByte, msgCp->mBuf, msgIdx - 1); 
           /* Increment the msgIdx by 64K octets */
           msgIdx += CM_PASN_VAL_32K;
           firstTime = FALSE; 
        }
        else
        {
           /* Insert 32k segment length byte here */
       /* cm_pasn2_c_001.main_22 : kwork fix */
           ret = SCpyFixMsg((Data *)&encByte, msgCp->mBuf,
                              msgIdx, (MsgLen)CM_PASN_VAL_ONE, &cCnt);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }

           /* Increment the msgIdx by 32K octets */
           msgIdx += (CM_PASN_VAL_32K+1);
        }
     }

     else if(d)
     {
        /* Encode the length for 16K components */
        encByte = 0xc1; /* 1100 0001 */
        if(firstTime)
        {
           /* Replace the place holder length byte */
           SRepMsg(encByte, msgCp->mBuf, msgIdx - 1); 
           /* Increment the msgIdx by 64K octets */
           msgIdx += CM_PASN_VAL_16K;
           firstTime = FALSE; 
        }
        else
        {
           /* Insert 16k segment length byte here */
       /* cm_pasn2_c_001.main_22 : kwork fix */
           ret = SCpyFixMsg((Data *)&encByte, msgCp->mBuf,
                              msgIdx, (MsgLen)CM_PASN_VAL_ONE, &cCnt);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }

           /* Increment the msgIdx by 16K octets + the above length octet */
           msgIdx += (CM_PASN_VAL_16K+1);
        }
     }
  }

  /* Now encode the length determinant for the left over components */ 
  if( m <= CM_PASN_UNCON_LEN1)
  {
     encByte = (U8)(GetLoByte(GetLoWord(m)));
     /* Insert this segment length byte here */
     /* cm_pasn2_c_001.main_22 : kwork fix */
     ret = SCpyFixMsg((Data *)&encByte, msgCp->mBuf,
                           msgIdx, (MsgLen)CM_PASN_VAL_ONE, &cCnt);
     if(ret != ROK)
     {
       RETVALUE(RFAILED);
     }
  }

  else
  {
     if( (m > CM_PASN_UNCON_LEN1) && 
           (m < CM_PASN_UNCON_LEN2))
     {
        /* SCpyFixMsg reverses the byte order */
        pkArray[0] = ( (GetHiByte(GetLoWord(m))) & CM_PASN_BYTE_SIXF) |
           CM_PASN_BYTE_MSBONE;
        pkArray[1] = GetLoByte(GetLoWord(m));

        /* Insert this segment length byte here */
        ret = SCpyFixMsg((Data *)&pkArray[0], msgCp->mBuf,
                    msgIdx, (MsgLen)CM_PASN_VAL_TWO, &cCnt);
        if(ret != ROK)
        {
           RETVALUE(RFAILED);
        }
     }
  }
  RETVALUE(ROK);
} /* End of cmPAsnFragEnc */


/*
*
*       Fun:   cmPAsnEncFragSeqOf
*
*       Desc:  This function fragments an encoded field list  which
*              is Components. 
*              stream 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn2.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncFragSeqOf
(
CmPAsnMsgCp  *msgCp,    /* message control pointer */
U32          numComp    /* Number of components */
)
#else
PUBLIC S16 cmPAsnEncFragSeqOf(msgCp,numComp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
U32          numComp;  /* Number of components */
#endif
{  
  S16        ret;
  U32        m;  
  /* cm_pasn2_c_001.main_10 */
  U32        i;
  U8         a;       /* Number of 64K components */
  U8         b;       /* Number of 48K components */ 
  U8         c;       /* Number of 32K components */ 
  U8         d;       /* Number of 16K components */ 
  /* cm_pasn2_c_001.main_22 : kwork fix */
  CmPAsnElmDef      **pElmDef;   /* Ptr to Element definition */

  TRC3(cmPAsnFragEnc)

  m = numComp;
  a = 0;
  b = 0;
  c = 0;
  d = 0;

  pElmDef = msgCp->elmDef;

  /* Determine how many 64k components */
  if(m >= CM_PASN_VAL_64K)
  {
     a = m >> 16;

     /* Get the left over value */
     m = m - (a << 16 );
  }

  /* Determine if any 48k component */
  if( m >= CM_PASN_VAL_48K )
  {
    b = 1;
    m = (m - CM_PASN_VAL_48K);
  }
  else
  {
     /* If no 48K component, then check for 32k component */
     if( m >= CM_PASN_VAL_32K )
     {
        c = 1;
        m = (m - CM_PASN_VAL_32K);
     }
     /* Else check for any 16k component */
     else if( m >= CM_PASN_VAL_16K )
     {
        d = 1;
        m = (m - CM_PASN_VAL_16K);
     }
  }

  /* Octet Align the message buffer */
  CM_PASN_OCTET_ALIGN(msgCp);

  for(i=0; i< a; i++)
  {
     /* Encode the length determinant byte for 64k components */ 
     /* 0xc4 = 1100 0100 */ 
     CM_PASN_ENC_BYTE(msgCp, 0xc4);

     for(i=0; i < CM_PASN_VAL_64K; i++)
     {
        /* Call encode function */
        /* cm_pasn2_c_001.main_22 : kwork fix */
        ret = cmPAsnEncElm(msgCp);
        if(ret != ROK)
        {
           RETVALUE(RFAILED);
        }

        /* Reset element definition pointer */
        msgCp->elmDef = pElmDef;
     }
  }

  /* Add any 48K fragment */
  if(b)
  {
     /* Encode the length determinant byte for 64k components */ 
     /* 0xc3 = 1100 0011 */ 
     CM_PASN_ENC_BYTE(msgCp, 0xc3);

     for(i=0; i < CM_PASN_VAL_48K; i++)
     {
        /* Call encode function */
        /* cm_pasn2_c_001.main_22 : kwork fix */
        ret = cmPAsnEncElm(msgCp);
        if(ret != ROK)
        {
           RETVALUE(RFAILED);
        }

        /* Reset element definition pointer */
        msgCp->elmDef = pElmDef;
     }
  }
  else
  {
     /* Check if any 32k component */
     if(c)
     {
        /* Encode the length determinant byte for 64k components */ 
        /* 0xc2 = 1100 0010 */ 
        CM_PASN_ENC_BYTE(msgCp, 0xc2);

        for(i=0; i < CM_PASN_VAL_32K; i++)
        {
           /* Call encode function */
        /* cm_pasn2_c_001.main_22 : kwork fix */
           ret = cmPAsnEncElm(msgCp);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }

           /* Reset element definition pointer */
           msgCp->elmDef = pElmDef;
        }
     }

     else if(d)
     {
        /* Encode the length determinant byte for 16k components */ 
        /* 0xc1 = 1100 0001 */ 
        CM_PASN_ENC_BYTE(msgCp, 0xc1);

        for(i=0; i < CM_PASN_VAL_16K; i++)
        {
           /* Call encode function */
        /* cm_pasn2_c_001.main_22 : kwork fix */
           ret = cmPAsnEncElm(msgCp);
           if(ret != ROK)
           {
              RETVALUE(RFAILED);
           }

           /* Reset element definition pointer */
           msgCp->elmDef = pElmDef;
        }
     }
  }

  /* Now encode the length determinant for the left over components */ 
  /* cm_pasn2_c_001.main_22 : kwork fix */
  ret = cmPAsnEncUnconLen(msgCp, m);
  if(ret != ROK)
  {
     RETVALUE(RFAILED); 
  }

  /* Encode the left over components */
  for( i =0; i< m; i++)
  {
     /* Call encode function */
  /* cm_pasn2_c_001.main_22 : kwork fix */
     ret = cmPAsnEncElm(msgCp);
     if(ret != ROK)
     {
        RETVALUE(RFAILED);
     }

     /* Reset element definition pointer */
     msgCp->elmDef = pElmDef;
  }
  RETVALUE(ROK);
} /* End of cmPAsnEncFragSeqOf */


#ifdef CM_PASN_DBG
/* cm_pasn2_c_001.main_18: Functions added */
/*
 *
 *       Fun:   cmPAsnPrintBitStr
 *
 *       Desc:  This function print bit string value
 *
 *       Ret:   Void
 *
 *       Notes:
 *
 *       File:  cm_pasn2.c
 *
 */

#ifdef ANSI
PUBLIC Void cmPAsnPrintBitStr
(
 CmPAsnMsgCp  *msgCp,    /* message control pointer */
 U8           *val,      /* Value of bit string */
 U32          len        /* Length of string */
 )
#else
PUBLIC Void cmPAsnPrintBitStr (msgCp, val, len)
   CmPAsnMsgCp  *msgCp;   /* message control pointer */
   U8           *val;      /* Value of bit string */
   U32          len;       /* Length of string */
#endif
{
   U16 indx=0;
   U8  bitIndx = 0;
   S8  binVal[CM_PASN_PRNT_SIZE]={0};
   U16 lenByte = (len >> CM_PASN_VAL_THREE);      /* No of Bytes */
   S16 lenBit  = len % CM_PASN_VAL_EIGHT;         /* No of bits  */
   U8  lineIdx=0;

   TRC2(cmPAsnPrintBitStr)

   /* Do not print if dbgFlag is not enabled */
   if(!msgCp->dbgFlag)
      RETVOID;

   CM_PASN_DBGP(msgCp,
            (msgCp->prntBuf,"Bit String value=\n"));

   /* converting byte to bits */
   for(indx = 0; indx < lenByte; indx++)
   {
      for(bitIndx = CM_PASN_OSLEN_128; bitIndx > 0; bitIndx >>= 1)
      {
         strcat(binVal, ((val[indx]) & bitIndx)? "1" : "0");
         lineIdx++;
      }
      /* print once number of bits reached 80 character */
      if(lineIdx == 80)
      {
         SPrint(binVal);
         SPrint("\n");
         binVal[0]='\0';
         lineIdx = 0;
      }
   }
   if(lineIdx)
   {
      SPrint(binVal);
      binVal[0]='\0';
   }

   /* print remaining bits */
   if(lenBit)
   {
      U8 valBits = val[indx];
      for(bitIndx = CM_PASN_OSLEN_128; lenBit > 0; bitIndx >>= 1, lenBit--)
      {
         strcat(binVal, (valBits & bitIndx)?"1" : "0");
      }
      SPrint(binVal);
   }
   SPrint("\n");

   RETVOID;
} /* End of cmPAsnPrintBitStr */

/*
 *
 *       Fun:   cmPAsnPrintOctetStr
 *
 *       Desc:  This function print octet string
 *
 *       Ret:   ROK 
 *
 *       Notes: This function is called by for
 *
 *       File:  cm_pasn2.c
 *
 */

#ifdef ANSI
PUBLIC Void cmPAsnPrintOctetStr
(
 CmPAsnMsgCp  *msgCp,    /* message control pointer */
 U8           *val,      /* Value of bit string */
 U32          len        /* Length of string */
 )
#else
PUBLIC Void cmPAsnPrintOctetStr (msgCp, val, len)
   CmPAsnMsgCp  *msgCp;   /* message control pointer */
   U8           *val;      /* Value of bit string */
   U32          len;       /* Length of string */
#endif
{
   U32 valIndx;
   S8  octVal[CM_PASN_PRNT_SIZE]={0};
   S8  buf[CM_PASN_OSLEN_8]={0};
   U8  lineIdx = 0;

   TRC2(cmPAsnPrintOctetStr)

   /* Do not print if dbgFlag is not enabled */
   if(!msgCp->dbgFlag)
      RETVOID;

   CM_PASN_DBGP(msgCp,
            (msgCp->prntBuf,"Octet String value in hexadecimal: \n"));
   /* converting byte to octet */
   for(valIndx=0; valIndx < len; valIndx++)
   {
      sprintf(buf, "%02x ", val[valIndx]);
      strcat(octVal, buf);
      lineIdx +=3;
      /* print once number of bits reached 78 character */
      if(lineIdx >= 78)
      {
         SPrint(octVal);
         SPrint("\n");
         octVal[0]='\0';
         lineIdx = 0;
      }
   }
   if(lineIdx)
   {
      SPrint(octVal);
      SPrint("\n");
   }

   RETVOID;
} /* End of cmPAsnPrintOctetStr */
#endif

  
/********************************************************************30**
  
         End of file:     cm_pasn2.c@@/main/22 - Mon Feb 20 16:38:18 2012
   
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
/main/2      ---      asa  1. Updated for rel 1.2
/main/4      ---      bsr  1. changed lenVal from U8 to U32 
                              to remove warnings
/main/5      ---      dw   1. Fix for unconstrained octet string processing
/main/6      ---      sgr  1. Accomodated the patch in main_2
/main/7      ---      lrb  1. Changed variable name from "index" to "idx"
                            to remove warnings on VxWorks 
/main/8      ---      sgr  3. Added Pre/Pst Enc/Dec Esc calls
/main/9      ---       bg  1. Corrected the encoding of remaining bits in 
                              cmPAsnEncStrVal()
/main/10     ---     rbabu 1. Fix for windows compilation warnings
/main/11     ---      vsr  1. Fixed the compiler warnings for RANAP release 2.3. 
/main/12     ---     rbabu 1. Added Unaligned Support.
/main/13     ---      rbhat 1. Added support for default value handling.
/main/14     ---     rbhat 1. Corrected the encoding of remaing bits
                                in cmPAsnEncStrVal in case of bitstring
                                aligned.
                           2. Add validation of noComp value.
/main/15     ---  cm_pasn2_c_001.main_14   mos  1. Updated for S1AP 2.1 Release                           
/main/16     ---  chebli  1. (cm_pasn2_c_001.main_15)Aligning octet only in Aligned PER case.
                          2. Updating default value if pres for default element is zero.
/main/17     ---  rsharon  1. (cm_pasn2_c_001.main_16) Added check for the 
                                                evntStr to protect core dump.
/main/18     ---      cm_pasn2_c_001.main_17 vkulkarni  1. Corrected typecast issues.
                                          2. Removed un-necessary check in ChkEncElmnt
/main/19     ---      cm_pasn2_c_001.main_18 rk  1. Added code to print Bit and Octet String
/main/20     cm_pasn2_c_001.main_19 spoovalingam 1. Fix for compilation warnings 
/main/21     ---      cm_pasn2_c_001.main_20 mpatel       1. Update for LTE RRC 3.1 release 
/main/22     ---      cm_pasn2_c_001.main_21 pbyadgi  1. Fixed warning for g++ compilation on Linux. 
$SID$       ---      cm_pasn2_c_001.main_22 akaranth  1. kwork fixes. 
 *********************************************************************91*/
