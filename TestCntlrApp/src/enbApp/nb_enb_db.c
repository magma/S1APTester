
/********************************************************************20**

     Name:     ENB DB

     Type:     C source file

     Desc:     C source code for maitaining ENB Database.

     File:     nb_enb_db.c
  

*********************************************************************21*/

#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tpt.h"        /* Common transport library        */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_inet.h"       /* Common socket library           */
#include "cm_pasn.h"       /* Common ASN.1 library           */
#include "cm_os.h"

#include <stdlib.h>        /* For strtoul() */

#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm_os.x"
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common library function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_tpt.x"        /* Common transport library        */
#include "cm_mblk.x"       /* Common memory allocation        */
#include "cm_inet.x"       /* Common socket library           */
#include "cm_pasn.x"       /* Common ASN.1 Library           */

#include "nb_enb_db.x"
#include "nb_enb_db.h"

PUBLIC NbEnbDB nbEnbDB;

PRIVATE Keys nbEnbDB_kw[]=
{
   {"beginCfg",       NB_ENB_TKN_BEGIN_CFG },
   {"numENBEntries",  NB_ENB_TKN_NUM_ENB_ENTRIES },
   {"ENB_Entry",      NB_ENB_TKN_ENB_ENTRY },
   {"CELL_ID",        NB_ENB_TKN_CELL_ID },
   {"TAC",            NB_ENB_TKN_TAC },
   {"PLMN_ID",        NB_ENB_TKN_PLMN_ID },
   {"endCfg",         NB_ENB_TKN_END_CFG },
   {"",               MATCH_FAILED }
};

PRIVATE S16 nbLineToTkn ARGS((S8 *line, NbTkn *tkn));
PRIVATE S16 nbParseU32 ARGS((NbTkn *tkn, U32 low, U32 high, U32 *ret));
PRIVATE U32 nbStrtoul ARGS((CONSTANT S8 *str, S8 **ptr, S32 base));
PRIVATE S16 nbParseArr ARGS((NbTkn *tkn, U8 *ptr, U32 size, U32 nmbElem));
PRIVATE S16 nbParseStr ARGS((NbTkn *tkn, S8 *ptr, U8 size));

/**

   @brief Convert Line format to Token Format

   @param *line pointer to line
   @param *tkn  pointer to tkn of type NbTkn

   @return 
      - Number of arguments on success
      - RFAILED on Failure

 */
#ifdef ANSI
PRIVATE S16 nbLineToTkn
(
S8 *line,
NbTkn *tkn
)
#else
PRIVATE S16 nbLineToTkn(line, tkn)
S8 *line;
NbTkn *tkn;
#endif
{
   S8 *lPtr;
   S8 word[NB_ENB_DB_LINE_LEN];
   S32 i;

   lPtr = osGetWord(line, word);

   if (osStrlen(word) >= sizeof(tkn->tok.val)) /* make sure there's room */
      RETVALUE(-1);

   osStrcpy((S8*)tkn->tok.val, word);
   tkn->tok.pres = TRUE;
   tkn->tok.len = (U8) osStrlen((S8*)tkn->tok.val);
   tkn->nmbArgs = 0;

   for (i = 0; i < NB_ENB_DB_MAX_ARGS; i++)
   {
      lPtr = osGetWord(lPtr, word);

      if (osStrlen(word) >= sizeof(tkn->tok.val)) /* make sure there's room */
         RETVALUE(-1);

      if (*word == '\0' || *word == '#') /* end of line or comment */
      {
         tkn->args[i].pres = FALSE;
         break;
      }

      osStrcpy((S8*)tkn->args[i].val, word);
      tkn->args[i].pres = TRUE;
      tkn->args[i].len = (U8)osStrlen((S8*)tkn->args[i].val);
      tkn->nmbArgs++;
   }

   RETVALUE(tkn->nmbArgs);
} /* end of nbLineToTkn */



/**

   @brief Parse argument into U32

   @param *tkn
   @param low
   @param high
   @param *ret

   @return 
      - ROK on Success
      - RFAILED on Failure

 */
#ifdef ANSI
PRIVATE S16 nbParseU32
(
NbTkn *tkn,
U32 low,
U32 high,
U32 *ret
)
#else
PRIVATE S16 nbParseU32(tkn, low, high, ret)
NbTkn *tkn;
U32 low;
U32 high;
U32 *ret;
#endif
{
   if (!tkn->args[0].pres || *tkn->args[0].val != '=')
   {
      printf("nbParseU32: equals sign missing\n");
      RETVALUE(RFAILED);
   }

   if (!tkn->args[1].pres)
   {
      printf("nbParseU32: arg not present\n");
      RETVALUE(RFAILED);
   }

   *ret = (U32)nbStrtoul((S8*)tkn->args[1].val, NULLP, NULLP);

   if (*ret < low || *ret > high)
   {
      printf("nbParseU32() - value out of range\n");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);

} /* end of nbParseU32 */


/**

   @brief Wrapper for strtoul

   @param *str
   @param **ptr
   @param base

   @return 
      - ascii string to long value

 */
#ifdef ANSI
PRIVATE U32 nbStrtoul
(
CONSTANT S8 *str,
S8 **ptr,
S32 base
)
#else
PRIVATE U32 nbStrtoul(str, ptr, base)
CONSTANT S8 *str;
S8 **ptr;
S32 base;
#endif
{
   RETVALUE(strtoul(str, ptr, base));

} /* end of nbStrtoul */


/**

   @brief Parse an array

   @param *tkn
   @param *ptr
   @param size
   @param nmbElem

   @return 
      - ROK on Success
      - RFAILED on Failure

 */
#ifdef ANSI
PRIVATE S16 nbParseArr
(
NbTkn *tkn,
U8 *ptr,
U32 size,
U32 nmbElem
)
#else
PRIVATE S16 nbParseArr(tkn, ptr, size, nmbElem)
NbTkn *tkn;
U8 *ptr;
U32 size;
U32 nmbElem;
#endif
{
   U32 count;
   U32 val;
   

   if (nmbElem != tkn->nmbArgs)
   {
      printf("nbParseArr: Invalid No of Argument \n");
      RETVALUE(RFAILED);
   }
      
   for (count = 0; count < nmbElem; count++)
   {
      
      if (!tkn->args[count].pres)
      {
         printf("nbParseArr: Argument No not present\n");
         RETVALUE(RFAILED);
      }
      
      val = strtoul((S8*)tkn->args[count].val, NULLP, NULLP);
      switch (size)
      {
         case 1:
         {
            *(U8 *)(ptr+(count * 1)) = (U8) val;
            break;
         }
         case 2: 
         {
            *(U16 *)(ptr+(count * 2)) = (U16) val;
            break;
         }
         case 4:
         {
            *(U32 *)(ptr+(count * 4)) = (U32) val;
            break;
         }
         default:
         {
            break;
         }
      }
      switch (size)
      {
         case 1:
         {
            *(U8 *)(ptr+(count * size)) = (U8) val;
            break;
         }
         case 2: 
         {
            *(U16 *)(ptr+(count * size)) = (U16) val;
            break;
         }
         case 4:
         {
            *(U32 *)(ptr+(count * size)) = (U32) val;
            break;
         }
         default:
         {
            break;
         }
      }

   }/* End of for loop */

   RETVALUE(ROK);
   
}/* End of nbParseArr */

/**

   @brief Parse argument into String

   @param *tkn
   @param *address

   @return 
      - ROK on Success
      - RFAILED on Failure

 */
#ifdef ANSI
PRIVATE S16 nbParseStr
(
NbTkn *tkn,
S8 *str,
U8  size
)
#else
PRIVATE S16 nbParseStr(tkn,  str, size)
NbTkn *tkn;
S8     *str;
U8     size;
#endif
{
   U8 strLen;

   if (!tkn->args[0].pres || *tkn->args[0].val != '=')
   {
      printf("nbParseStr: equals sign missing\n");
      RETVALUE(RFAILED);
   }

   if (!tkn->args[1].pres)
   {
      printf("nbParseStr: arg not present\n");
      RETVALUE(RFAILED);
   }

   strLen = (U8)osStrlen((S8*)tkn->tok.val);

   if (strLen >= size)
   {
      printf("nbParseStr: Given string lenght is more \n");
      RETVALUE(RFAILED);
   }

   osStrcpy(str, (S8*)tkn->args[1].val);

   RETVALUE(ROK);

} /* end of nbParseStr */

/**

   @brief Reads file "enb_list.db" which is the database of ENBS supported. 
          Reading is based on the keywords. After reading, the data is parsed & 
          stored in *nbEnbDB.

   @param *nbEnbDB pointer to enbDB of type NbEnbDB which hold the information 
           related to all the ENBs configured

   @return 
      - ROK on Success
      - RFAILED on Failure

 */
#ifdef ANSI
PUBLIC S16 nbReadEnbDB
(
  Void
)
#else
PUBLIC S16 nbReadEnbDB(Void)
#endif
{
   NbEnbDB         *enbDB;
   U32               numCtxt = 0;
   NbTkn           tkn;
   S8               line[NB_ENB_DB_LINE_LEN + 1];
   OsFile           *fp = NULLP;
   S16              ret = ROK;
   S8               *ret1 = NULLP;
   U32              k = 0;
   S32              val;
   PRIVATE S32      lineNo = 0;
   U16              ueIdx;
   U8               imsiIndex;
   U8               nextOrder;
   U8               indx = 0;
   NbPlmn           plmnId = {0};

   enbDB = &nbEnbDB;
   printf("Reading ENB Database\n");

   if((fp = fopen("enb_list.db", "r")) == NULLP)
   {
            printf("FAILED : File Open Error, File enb_list.db\n");
      exit(0);
   }

   lineNo = 1;

   for (;;)
   {
      ret1 = osFgets(line, NB_ENB_DB_LINE_LEN, fp);
   
      if (ret1 == (S8*)-1 || ret1 == NULLD) /* eof or NULL */
      {
         printf("End Of File Reached, enb_list.db\n");
         break;
      }

      if (!osStripBlanks(line))
      {
         lineNo++;
         continue;   /* blank line */
      }

      if (*line == '#')
      {
         lineNo++;
         continue;   /* blank line */
      }

      /* convert line to tokens */
      if (nbLineToTkn(line, &tkn) == -1)
      {
#ifdef ALIGN_64BIT
         printf("Syntax Error Reading File. Line(%d)\n",lineNo);
#else
         printf("Syntax Error Reading File. Line(%ld)",lineNo);

#endif
			 if(fp) osFclose(fp);
         RETVALUE(RFAILED);
      }

      val = osMatchKeyword(nbEnbDB_kw, (S8*)tkn.tok.val);

      switch (val)
      {
         case NB_ENB_TKN_BEGIN_CFG: /* beginCfg */
            break;

         case NB_ENB_TKN_NUM_ENB_ENTRIES: /* numENBEntries */
         {
            ret = nbParseU32(&tkn, 0, NB_MAX_ENBS, &enbDB->numENBEntries);

            if (ret != ROK)
				{
					if(fp) osFclose(fp);
               RETVALUE(ret);
				}
            break;
         }
         case NB_ENB_TKN_ENB_ENTRY: /* ENB_Entry */
         {
            ret = nbParseU32(&tkn, 0, NB_MAX_ENBS,\
                  &enbDB->enbInfo[k].enbEntry);

            if (ret != ROK)
				{
					if(fp) osFclose(fp);
               RETVALUE(ret);
				}

				if (enbDB->enbInfo[k].enbEntry > enbDB->numENBEntries)
				{
					enbDB->enbInfo[k].enbEntry = 0;
					if(fp) osFclose(fp);
					RETVALUE(ROK);
				}


            /* Reset for new entry */
            numCtxt = 0;

            break;
         }
         case NB_ENB_TKN_CELL_ID: /* ENB Cell ID */
         {
            ret = nbParseU32(&tkn, 0, NB_MAX_ENBS, &enbDB->enbInfo[k].cell_id);

            if (ret != ROK)
	      {
	         if(fp) osFclose(fp);
                 RETVALUE(ret);
	      }
            break;
         }
         case NB_ENB_TKN_TAC: /* TAC */
         {
            ret = nbParseU32(&tkn, 0, NB_MAX_ENBS, &enbDB->enbInfo[k].tac);
            if (ret != ROK)
	      {
	         if(fp) osFclose(fp);
                 RETVALUE(ret);
	      }
            break;
         }

         case NB_ENB_TKN_PLMN_ID: /* MSISDN */
         {
            ret = nbParseArr(&tkn, (U8*)plmnId, sizeof(U8), 6);
            if (ret != ROK)
	      {
	         if(fp) osFclose(fp);
                 RETVALUE(ret);
	      }

            cmMemcpy(enbDB->enbInfo[k].plmn, plmnId, 6);
            k++; /* Increment after reading last entry for an ENB */
            break;
         }
         case NB_ENB_TKN_END_CFG: /* endCfg */
         {
            break;
         }
         default:
         {
            printf("Invalid keyword in enb_list.db\n");
            ret = RFAILED;
            break;
         }
      } /* End of switch(val) */

   } /* End of for loop */

   if(fp) osFclose(fp);


   RETVALUE(ret);

} /* End of nbReadEnbDB()  */

