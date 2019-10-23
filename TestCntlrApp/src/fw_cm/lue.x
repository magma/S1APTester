/**********************************************************************

     Name:     Ue application stuctures 

     Type:     C include file

     Desc:     Structures and Function Signatures required by Ue 
               Application Layer

     File:     ue_layer_manager.x

     Sid:      

     Prg:      snatra

**********************************************************************/
#ifndef __LUE__
#define __LUE__

#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus  */ 

#define LUE_MAX_STR_SIZE 101

typedef struct _labStr
{
   U16                  length;                             /* length of string */
   Data                 buff[LUE_MAX_STR_SIZE];             /* string value */
}LueStr; /* end of typedef struct _labStr */

/* General Configurations */
typedef struct _ueGenCfg
{
   U32             vendorId;      /* Vendor Identity */
   U32             appId;         /* Application Identity */
   U16             timeRes;      /* Timer Resolution Parameter */
   Status          memUpperThr;   /* Upper threshold of the memory pool */
   Status          memLowerThr;   /* Lower threshold of the memory pool*/
   Pst             lmPst;         /* Post structure for layer manager */
} UeGenCfg;/* end of typedef struct _ueGenCfg */

typedef struct _ueCfg
{
   union
   {
      UeGenCfg     gen;           /* General Configuration */
   }  u;
} UeCfg;/* end of typedef struct _ueCfg */

/* Ab Layer Debug Control Information*/

typedef struct _ueDbgCntrl
{
   U32             dbgMask;       /* Debug mask */
#ifdef LUE_FILE_LOG
   Bool            fileLogEnb;    /* To Enable/Disable file logging */
   Txt             filePath[LUE_MAX_FILE_PATH];/* Path to store log files */
   U32             nmbDbgLines;   /* Number of lines per Debug file */
#endif /* end of LAB FILE LOG */
} UeDbgCntrl;/* end of typedef struct _ueDbgCntrl */

typedef struct _ueCntrl
{
   DateTime        dt;            /* Date and Time */
   U8              action;        /* Action */
   U8              subAction;     /* Sub action */
   union
   {
      UeDbgCntrl   dbg;           /* Debug Control */
   } u; /* end of union */
} UeCntrl;/* end of typedef struct _ueCntrl */

typedef struct _ueMngmt
{
   Header               hdr;       /* Header */
   CmStatus             cfm;       /* Primitive.s status/conf. */
   union
   {
      UeCfg             cfg;       /* Configuration */
      UeCntrl           cntrl;     /* Control */
   } u;
} UeMngmt;/* end of typedef struct _ueMngmt */

/*****************************************************************************
 *                                                                           *
 *                              Interface Primitives                         *
 *                                                                           *
 *****************************************************************************/
typedef S16 (*LueCfgReq) ARGS((
                               Pst     *pst,      /* Post structure */
                               UeMngmt *cfgReq    /* management structure */
                             ));

typedef S16 (*LueCfgCfm) ARGS((
                               Pst     *pst,      /* Post structure */
                               UeMngmt *cfgCfm    /* management structure */
                             ));


typedef S16 (*LueCntrlReq) ARGS((
                               Pst     *pst,      /* Post structure */
                               UeMngmt *cntrlReq  /* management structure */
                             ));

typedef S16 (*LueCntrlCfm) ARGS((
                               Pst     *pst,      /* Post structure */
                               UeMngmt *cntrlCfm  /* management structure */
                             ));

PUBLIC S16 UeMiLueCfgReq ARGS((
                               Pst     *pst,      /* Post structure */
                               UeMngmt *cfgReq    /* management structure */
                             ));

PUBLIC S16 UeMiLueCfgCfm ARGS((
                               Pst     *pst,      /* Post structure */
                               UeMngmt *cfgCfm    /* management structure */
                             ));



PUBLIC S16 UeMiLueCntrlReq ARGS((
                               Pst     *pst,      /* Post structure */
                               UeMngmt *cntrlReq  /* management structure */
                             ));

PUBLIC S16 UeMiLueCntrlCfm ARGS((
                               Pst     *pst,      /* Post structure */
                               UeMngmt *cntrlCfm  /* management structure */
                             ));

PUBLIC S16 UeMiLueTrcInd ARGS((
                               Pst     *pst,      /* Post structure */
                               UeMngmt *trcInd,   /* management structure */
                               Buffer  *mBuf      /* trace buffer */
                             ));

#ifdef SM
PUBLIC S16 SmMiLueCfgReq ARGS((
                               Pst     *pst,            /* Post structure */
                               UeMngmt *cfgReq          /* management structure */
                             ));

PUBLIC S16 SmMiLueCfgCfm ARGS((
                               Pst     *pst,            /* Post structure */
                               UeMngmt *cfgCfm          /* management structure */
                             ));


PUBLIC S16 SmMiLueCntrlReq ARGS((
                               Pst     *pst,            /* Post structure */
                               UeMngmt *cntrlReq        /* management structure */
                             ));
PUBLIC S16 SmMiLueCntrlCfm ARGS((
                               Pst     *pst,            /* Post structure */
                               UeMngmt *cntrlCfm        /* management structure */
                             ));

#endif /* end of SM */


/*******************************************************************
 *                                                                 *
 *                     Primitive                      *
 *                                                                 *
 ******************************************************************/
PUBLIC S16 cmPkUeGenCfg
(
UeGenCfg    *ueGenCfg,   /* the general configuration to be packed */
Buffer      *mBuf        /* to hold the packed buffer */
);
PUBLIC S16 cmPkLueCfgReq
(
Pst *pst,                   /* post structure */
UeMngmt *ueMngmt            /* configuration */
);


PUBLIC S16 cmPkLueCntrlReq
(
Pst *pst,                   /* post structure */
UeMngmt *ueMngmt              /* control */
);

PUBLIC S16 cmPkLueCntrlCfm
(
Pst *pst,                 /* post structure */
UeMngmt *ueMngmt          /* confirm */
);

PUBLIC S16 cmUnpkUeGenCfg
(
UeGenCfg    *ueGenCfg,   /* to hold the general configuration that is unpacked */
Buffer      *mBuf        /* to hold the packed buffer */
);
PUBLIC S16 cmUnpkLueCfgReq
(
LueCfgReq func,             /* primitive pointer */
Pst *pst,                   /* post structure */
Buffer *mBuf                /* message buffer */
);

PUBLIC S16 cmUnpkLueCntrlReq
(
LueCntrlReq func,           /* primitive pointer */
Pst *pst,                   /* post structure */
Buffer *mBuf                /* message buffer */
);
PUBLIC S16 cmUnpkLueCfgCfm
(
LueCfgCfm func, /* primitive pointer */
Pst *pst,
Buffer *mBuf   /* message buffer */
);

PUBLIC S16 cmUnpkLueCntrlCfm
(
LueCntrlCfm func, /* primitive pointer */
Pst *pst,
Buffer *mBuf   /* message buffer */
);

#ifdef __cplusplus
} 
#endif /* extern "C" */

#endif /* __LUE__ */
