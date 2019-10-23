

/********************************************************************20**
 
     Name:     System Services -- Message manipulation functions
 
     Type:     C include file
 
     Desc:     Data structure definitions for message related functions.
 
     File:     ss_msg.x
 
     Sid:      ss_msg.x@@/main/3 - Mon Nov 17 15:54:20 2008
 
     Prg:      sn
 
*********************************************************************21*/

#ifndef __SSMSGX__
#define __SSMSGX__

#ifdef __cplusplus
extern "C" {
#endif


/* pool type -- dynamic or static */
typedef U8              SsPoolType;



/* dynamic pool */
typedef struct ssDPoolEntry
{
   SsdDPoolEntry        dep;                    /* implementation specific */
   Size                 size;                   /* to use for SAlloc() */
} SsDPoolEntry;


/* static pool */
typedef struct ssSPoolEntry
{
   SsdSPoolEntry        dep;                    /* implementation specific */
} SsSPoolEntry;


/* generic pool (includes dynamic and static) */
typedef struct ssPoolEntry
{
   SsdPoolEntry         dep;                    /* implementation specific */
   SsPoolType           type;                   /* dynamic or static */
   union 
   {
      SsSPoolEntry      spool;                  /* static pool */
      SsDPoolEntry      dpool;                  /* dynamic pool */
   } u;
} SsPoolEntry;


/* event information--what kind of message is this */
typedef struct ssEventInfo
{
   U8 event;                                    /* event type */
   union
   {
      struct
      {
         SsIdx tmrIdx;                          /* timer index */
         Bool  inUse;                           /* message in use? */
         Bool  dynBuf;                          /* dynamic buffer? */
      } tmr;                                    /* for timer events */
   } u;
} SsEventInfo;


/* Information stored in the control portion of a message.
 * The SGETBUFREGION, SGETBUFPOOL, SGetBufRegionPool macros
 * depend on the order of the first two elements of this
 * structure. Make sure the macros are consistent with the
 * definition here.
 */
typedef struct ssMsgInfo
{
   Region       region;                         /* region id of the msg chain */
   Pool         pool;                           /* pool id of the msg chain */
   MsgLen       len;                            /* num of bytes in the msg */
   Buffer       *endptr;                        /* ptr to last mblk in chain */
   Buffer       *next;                          /* for SInitNxtDBuf() */
   Pst          pst;                            /* post for this message */
   SsEventInfo  eventInfo;                      /* event information */
} SsMsgInfo;
 

#ifdef __cplusplus
}
#endif

#endif /* __SSMSGX__ */

 

/********************************************************************30**
 
         End of file:     ss_msg.x@@/main/3 - Mon Nov 17 15:54:20 2008
 
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
1.1          ---      sn   1. initial release
  
1.2          ---      kr   1. added a comment to reflect the dependency
                              of SGETBUFREGION, SGETBUFPOOL, 
                              SGetBufRegionPool on the order of fields
/main/3      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/
