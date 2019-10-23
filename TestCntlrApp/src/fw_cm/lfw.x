#if 0
typedef struct
{
   /* TODO: */
}FwPeerCfg;

typedef struct
{
   /* TODO: */
}FwGenCfg;

typedef struct
{
   /* TODO: */
}FwDbgCfg;

typedef struct
{
   union
   {
      FwGenCfg    genCfg;  /**< General Configuration */
      FwPeerCfg   peerCfg; /**< Peer configuration */
      FwDbgCfg    dbgCfg;  /**< Debug Config Information */
   }u;
}FwCfg;

typedef struct
{
   /* TODO: */
}FwCntrl;

typedef struct
{
   /* TODO: */
}FwStats;

typedef struct
{
   Header     hdr;        /**< Management API Request/Response types
                           *  hdr.msgType Values:
                           *  - Configuration = TCFG
                           *  - Control       = TCNTRL
                           *  - Statistics    = TSTS
                           *  - Status        = TSTA
                           *  - Alarm         = TUSTA
                           */

   CmStatus   cfm;        /**< Management API's Status confirmation
                           *  Filled by Fw and sent to the API
                           *  initiator
                           */
   union
   {
      FwCfg       cfg;     /**< Fw Config Informations */
      FwCntrl     cntrl;   /**< Fw Control Operations */
   }u;
}FwMngmt;

/** Function pointer for Fw configuration Request */
typedef S16 (*LfwCfgReq)   (Pst *pst, FwMngmt *cfg);

/** Function pointer for Fw control Request */
typedef S16 (*LfwCntrlReq) (Pst *pst, FwMngmt *cntrl);

/** Function pointer for Fw configuration confirm */
typedef S16 (*LfwCfgCfm) (Pst *pst, FwMngmt *cfg);

/** Function pointer for Fw control confirm */
typedef S16 (*LfwCntrlCfm) (Pst *pst, FwMngmt *cfm);

PUBLIC S16 cmPkLfwCfgReq(Pst *pst, FwMngmt *cfg);

PUBLIC S16 cmUnpkLfwCfgReq(LfwCfgReq func, Pst *pst, Buffer *mBuf);

PUBLIC S16 cmPkLfwCntrlReq(Pst *pst, FwMngmt *cntrl);

PUBLIC S16 cmUnpkLfwCntrlReq(LfwCntrlReq func, Pst *pst, Buffer *mBuf);

PUBLIC S16 cmPkLfwCfgCfm(Pst *pst, FwMngmt *cfm);

PUBLIC S16 cmUnpkLfwCfgCfm(LfwCfgCfm func, Pst *pst, Buffer *mBuf);

PUBLIC S16 cmPkLfwCntrlCfm(Pst *pst, FwMngmt *cntrl);

EXTERN PUBLIC S16 SmMiLfwCfgReq(Pst *pst, FwMngmt *cfg);

EXTERN PUBLIC S16 SmMiLfwCfgCfm(Pst *pst, FwMngmt *cfg);

EXTERN PUBLIC S16 SmMiLfwCntrlReq(Pst *pst, FwMngmt *cntrl);

EXTERN PUBLIC S16 SmMiLfwCntrlCfm(Pst *pst, FwMngmt *cntrl);

EXTERN PUBLIC S16 cmUnpkLfwCntrlCfm(LfwCntrlCfm func, Pst *pst, Buffer *mBuf);
#endif
