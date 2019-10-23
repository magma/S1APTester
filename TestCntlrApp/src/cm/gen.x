
/********************************************************************20**
  
     Name:     general layer
  
     Type:     C include file
  
     Desc:     Structures, variables and typedefs required by two
               or more layer service user interfaces.
   
     File:     gen.x
  
     Sid:      gen.x@@/main/96 - Wed Dec 23 15:55:40 2009
  
     Prg:      na
  
*********************************************************************21*/

#ifndef __GENX__
#define __GENX__

#ifdef __cplusplus
extern "C" {
#endif
 
  
/*
*     The structures and variables declared in this file
*     correspond to structures and variables used by
*     the following TRILLIUM software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000001     Physical Layer - SCC
*     1000002     Data Link Layer - LAPB
*     1000003     Data Link Layer - LAPD
*     1000005     Data Link Layer - LAPB & LAPD
*     1000006     Network Layer - X.25 Intermediate System
*     1000007     Network Layer - X.25 End System
*     1000008     Network Layer - X.75
*     1000009     Network Layer - Q.930/Q.931
*     1000010     Application Layer - Asynchronous PAD
*     1000011     Multiprocessor Operating System (MOS)
*     1000014     Network Layer - X.25 End & Intermediate System
*     1000017     Data Link Layer - Basic Frame Relay
*     1000018     Data Link Layer - Extended Frame Relay
*     1000019     Data Link Layer - Logical Link Control 1
*     1000020     Data Link Layer - Logical Link Control 2
*     1000021     Data Link Layer - Logical Link Control 3
*     1000023     Network Layer - X.31
*     1000024     Signalling System 7
*     1000025     SDLC
*     1000026     TCP/IP
*     1000027     Signalling System 7 - MTP Level 2
*     1000028     Signalling System 7 - MTP Level 3
*     1000029     Signalling System 7 - ISUP
*     1000031     Signalling System 7 - TCAP
*     1000033     Data Link Layer - ADCCP-NRM
*     1000034     Physical Layer - ISAC-S
*     1000035     68302 MOS/SCC
*     1000036     SNMP Agent
*     1000037     SNMP Tools
*     1000038     SNMP Package
*     1000039     Physical Layer - SCARF
*     1000040     UDP/IP
*     1000041     ESCC
*
*/
  
/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000001     Physical Layer - SCC
*     1000002     Data Link Layer - LAPB
*     1000003     Data Link Layer - LAPD
*     1000005     Data Link Layer - LAPB & LAPD
*     1000006     Network Layer - X.25 Intermediate System
*     1000007     Network Layer - X.25 End System
*     1000008     Network Layer - X.75
*     1000009     Network Layer - Q.930/Q.931
*     1000010     Application Layer - Asynchronous PAD
*     1000011     Multiprocessor Operating System (MOS)
*     1000014     Network Layer - X.25 End & Intermediate System
*     1000017     Data Link Layer - Basic Frame Relay
*     1000018     Data Link Layer - Extended Frame Relay
*     1000019     Data Link Layer - Logical Link Control 1
*     1000020     Data Link Layer - Logical Link Control 2
*     1000021     Data Link Layer - Logical Link Control 3
*     1000023     Network Layer - X.31
*     1000024     Signalling System 7
*     1000025     SDLC
*     1000026     TCP/IP
*     1000027     Signalling System 7 - MTP Level 2
*     1000028     Signalling System 7 - MTP Level 3
*     1000029     Signalling System 7 - ISUP
*     1000031     Signalling System 7 - TCAP
*     1000033     Data Link Layer - ADCCP-NRM
*     1000034     Physical Layer - ISAC-S
*     1000035     68302 MOS/SCC
*     1000036     SNMP Agent
*     1000037     SNMP Tools
*     1000038     SNMP Package
*     1000039     Physical Layer - SCARF
*     1000040     UDP/IP
*     1000041     ESCC
*
*/


/* typedefs */

typedef S8 Txt;                   /* text */

typedef U8 Ent;                   /* entity */

typedef U8 Inst;                  /* instance */

typedef struct entityId           /* entity id */
{
   Ent ent;                       /* entity */
   Inst inst;                     /* instance */
} EntityId;

/* element id */
 
typedef S16 Elmnt;                /* element */
 
typedef S16 ElmntInst1;           /* element instance 1 */
 
typedef S16 ElmntInst2;           /* element instance 2 */
 
typedef S16 ElmntInst3;           /* element instance 3 */
  
typedef struct elmntId            /* element id */
{
   Elmnt elmnt;                   /* element */
   ElmntInst1 elmntInst1;         /* element instance 1 */
   ElmntInst2 elmntInst2;         /* element instance 2 */
   ElmntInst3 elmntInst3;         /* element instance 3 */
} ElmntId;

typedef U8 Region;                /* region */

typedef U8 Pool;                  /* pool */

typedef U8 Prior;                 /* priority */

typedef Prior Priority;           /* priority */

typedef U8 Route;                 /* route */

typedef U8 Data;                  /* data */

typedef U8 Selector;              /* selector */

typedef S16 Reason;               /* reason */

typedef U16 ProcId;               /* processor id */

typedef U8 Event;                 /* event */

typedef U32 TranId;               /* transaction Id */

typedef S16 IntNum;               /* Interface Number */

typedef U16 TranNum;              /* Transaction Number */

typedef U16     CmIntfId;         /* Interface identifier       */
typedef U16     CmIntfVer;        /* Interface version          */

#ifdef TDS_ROLL_UPGRADE_SUPPORT
typedef struct  cmIntf            /* Attributes of an interface */
{
   CmIntfId     intfId;           /* Interface identifier       */
   CmIntfVer    intfVer;          /* Interface version          */
} CmIntf;
#endif

/* post structure *** ALIGNED & ORDERED *** */
typedef struct pst                /* parameters for SPstTsk */
{
   ProcId dstProcId;              /* destination processor id (U16) */
   ProcId srcProcId;              /* source processor id      (U16) */

   Ent dstEnt;                    /* destination entity       (U8)  */
   Inst dstInst;                  /* destination instance     (U8)  */
   Ent srcEnt;                    /* source entity            (U8)  */
   Inst srcInst;                  /* source instance          (U8)  */

   Prior prior;                   /* priority                 (U8)  */   
   Route route;                   /* route                    (U8)  */
   Event event;                   /* event                    (U8)  */
   Region region;                 /* region                   (U8)  */

   Pool pool;                     /* pool                     (U8)  */
   Selector selector;             /* selector                 (U8)  */
   CmIntfVer intfVer;             /* interface version        (U16) */
} Pst;

/* systemId structure */
  
typedef struct systemId           /* system id */
{
   S16 mVer;                      /* main version */
   S16 mRev;                      /* main revision */
   S16 bVer;                      /* branch version */
   S16 bRev;                      /* branch revision */
   Txt *ptNmb;                    /* part number */
} SystemId;

/* Protocol Address Structure */
/* Note: The Order of variables should not be changed as it breaks MPC/MPS
 *       code in PLOA
 */
typedef struct protAddr
{
   U16      protType;                  /* Protocol Type */
   U8       len;                       /* Protocol Address Length in bytes */
   U8       preLen;                    /* prefix length in bits */
   U8       address[MAX_PROTADDR_LEN]; /* Protocol Address */ 
#ifdef CM_ARI2
   Bool     autoSysIdPres;         /* Is Autonomous System Id Present */
   U32      autoSysId;                 /* Autonomous System Id */
#endif /* CM_ARI2 */

}ProtAddr;

typedef struct protAddrTbl
{
   U8         count;                 /* Number of addresses */
   ProtAddr   addr[MAX_PROT_ADDRS];  /* Protocol Address List */
}ProtAddrTbl;

/* addrs structure */

typedef struct addrs              /* address */
{
   U8 length;                     /* length (bytes or nibbles) */
   U8 strg[ADRLEN];               /* address */
} Addrs;

typedef struct shrtAddr           /* short address */
{
   U8 length;                     /* length bytes */
   U8 strg[SHRTADRLEN];           /* address */
} ShrtAddrs;

typedef struct lngAddr            /* long address */
{
   U8 length;                     /* length bytes */
   U8 strg[LNGADRLEN];            /* address */
} LngAddrs;

/* bndCfg structure */

typedef struct bndCfg             /* bind configuration */
{
   Txt *usrId;                    /* user id */
   U8 bufOwnshp;                  /* buffer ownership */
   U8 flcTyp;                     /* flow control type */
   U8 wdw;                        /* window */
   Ent ent;                       /* entity */
   Inst inst;                     /* instance */
   Region region;                 /* region */
   Pool pool;                     /* pool */
   Prior prior;                   /* priority */
   Route route;                   /* route */
   Addrs sapAdr;                  /* SAP Address */
   Selector selector;             /* selector */
} BndCfg;

/* gen_x_001.main_91 : Added Definition of Circular Buffer Structure */
/* Circular Buffer Structure */
#ifdef CBUF_ENABLE
typedef struct cb {
   U32 cBufIdx;
   U32 cBufSize;
   U8 *cBufPtr;
   S8 tmpBuf[CBUFPRNTSZE];
}cBuffer;
#endif /* CBUF_ENABLE */

/* tskInit structure */

typedef struct tskInit            /* task initialization */
{
#ifdef SS_MULTIPLE_PROCS
   ProcId proc;                   /* processor */
#endif /* SS_MULTIPLE_PROCS */
   Ent ent;                       /* entity */
   Inst inst;                     /* instance */
   Region region;                 /* static region */
   Pool pool;                     /* static pool */
   Reason reason;                 /* reason */
   Bool cfgDone;                  /* configuration done */
   Bool acnt;                     /* accounting */ 
   Bool usta;                     /* unsolicited status */
   Bool trc;                      /* trace */
#ifdef DEBUGP
   U32 dbgMask;                   /* debug mask */
   Txt prntBuf[PRNTSZE];          /* print buffer */
#endif
   Txt *prntCirBuf; /* print buffer for each system task */
#ifdef SS_DIAG
   /* gen_x_001.main_96 :Added logmask */
   U32 logMask;                   /* Logging mask */
#endif
   BndCfg lmBnd;                  /* layer management bind */
   ProcId procId;                 /* processor id */
   Pst lmPst;                     /* layer management post */
   /* gen_x_001.main_91 : Added cBuffer in task initialisation strucutre */
#ifdef CBUF_ENABLE
   cBuffer cBuf;                  /* Circular Buffer */
#endif /* CBUF_ENABLE */
   /* gen_x_001.main_92 : Added timestamp related parameter */
   /* gen_x_001.main_93 : Guarding the Timestamp related changes in the compile time flag*/
#ifdef DBG_TIMESTAMP
   SLockId dbgLock;               /* write lock for the log files */
   Bool lyrMtFlag;                /* Layer is Multithreaded or not flag */
#endif
   
} TskInit;


typedef S32 Cntr;                 /* counter */
 
typedef U32 StsCntr;              /* Statistics counter */

typedef S16 LnkNmb;               /* link number */

typedef S8 VBit;                      /*V Bit */

typedef S16 SuId;                 /* service user sap id */

typedef S16 SpId;                 /* service provider sap id */

typedef S16 SuInstId;             /* service user instance id */

typedef S16 SpInstId;             /* service provider instance id */

typedef U16 PortId;               /* port id */

typedef U8 Sapi;                  /* service access point id */
 
typedef U8 Tei;                   /* terminal endpoint id */

typedef U8 Ces;                   /* connection endpoint suffix */

typedef U32 Dlci;                 /* data link control identifier */ 

typedef U16 CalRef;               /* call Reference */

typedef S16 Origin;               /* origin */

typedef U16 NwId;                 /* Network Identifier */

typedef S16 Swtch;                /* switch */

typedef U8 Cause;                 /* cause code */

typedef U8 Dgn;                   /* diagnostic code */

typedef S16 Action;               /* action */

typedef S16 SeqS16;               /* signed 16 bit sequence number */
 
typedef U16 SeqU16;               /* unsigned 16 bit sequence number */
 
typedef S32 SeqS24;               /* signed 24 bit sequence number */
 
typedef U32 SeqU24;               /* unsigned 24 bit sequence number */
 
typedef U8 SetUpArb;              /* set up arbitration (PASSIVE/ACTIVE) */
 
typedef U8 EvntType;              /* event type */

typedef U8 State;                 /* state */

typedef U8 Mode;                  /* mode */

typedef S32 ConnId;               /* connection id */

typedef U32 UConnId;              /* unsigned connection id */

typedef U16 ProtId;               /* protocol id */

typedef U16 ChannelId;            /* channel id */

typedef U8  Arr64U8[64];            /* Array of 64 of type U8*/

typedef U16 Efa;                  /* Envelope Address Function */

typedef U32 BitState;             /* Sa Bit ID and Value */

typedef U8  CChanId;               /* V5UA Channel ID */

typedef U16 MibOpCode;            /* Op code for Mib Request MIB_REQUEST_GET,
                                     MIB_REQUEST_GET_FIRST, MIB_REQUEST */

typedef U16 MibStatus;            /* Status returned in Mib Cfm */

typedef U16 MibTblType;           /* table type */

typedef S32 MibReqId;             /* request identifier */

typedef U8  UstaType;             /* unsolicited status type */
typedef S8  ChannelNo;            /* Channel Number */

/* ATM typedefs */

#ifndef CMFILE_REORG_1

typedef U16 AtmVpci;              /* ATM virtual path connection id */
typedef U16 AtmVpi;               /* ATM virtual path id */


typedef U16 AtmVci;               /* ATM virtual channel id */

typedef U8 AtmLp;                 /* ATM loss priority */

typedef U8 AtmCi;                 /* ATM congestion indication */

typedef U8 AtmRs;                 /* ATM reception status */

typedef U8 AtmUu;                 /* ATM user-to-user field in CPCS PDUs */

typedef U32 AtmUui;               /* ATM user-to-user indication field in SSCOP PDUs */

typedef U8 AtmPt;                 /* ATM cell payload type */

typedef struct atmQos             /* ATM quality of service */
{
   U8 qosFwd;                     /* qos in forward  direction */
   U8 qosBwd;                     /* qos in backward direction */
} AtmQos;

/* Vitual channel structure */
 
typedef struct amVccId             /* virtual channel connection identifier */
{
   AtmVpci  vpci;                  /* virtual path connection identifier */
   AtmVci   vci;                   /* virtual channel identifier */
} AmVccId;

/* VCC id */
typedef struct atmVccId         /* VCC id */
{
   AtmVpi   vpi;                /* VPI */
   AtmVci   vci;                /* VCI */
} AtmVccId;

/* VCC table */
typedef struct atmVccTbl                  /* VCC table */
{
   U16        count;                      /* number of VCCs */
   AtmVccId   tbl[MAX_ATMVCCTBL_SZ];      /* VCC list */
} AtmVccTbl;

/* Generic ATM address */
typedef struct atmAddr
{
   U8    type;                  /* type of Address (AESA or E.164) */
   U8    len;                   /* length (bytes) */
   U8    strg[ADRLEN];          /* address string */
} AtmAddr;

/* ATM address table */
typedef struct atmAddrTbl            /* ATM address table */
{
   U16      count;                   /* number of ATM addresses */
   AtmAddr  tbl[MAX_ATMADDRTBL_SZ];  /* ATM address list */
} AtmAddrTbl;

typedef struct atmTfcDesc         /* ATM traffic descriptor */
{
   U32  fwdPeakCellRate0;         /* forward  peak  cell rate, CLP = 0   */
   U32  bwdPeakCellRate0;         /* backward peak  cell rate, CLP = 0   */
   U32  fwdPeakCellRate1;         /* forward  peak  cell rate, CLP = 0+1 */
   U32  bwdPeakCellRate1;         /* backward peak  cell rate, CLP = 0+1 */
   U32  fwdSustCellRate0;         /* forward  sust. cell rate, CLP = 0   */
   U32  bwdSustCellRate0;         /* backward sust. cell rate, CLP = 0   */
   U32  fwdSustCellRate1;         /* forward  sust. cell rate, CLP = 0+1 */
   U32  bwdSustCellRate1;         /* backward sust. cell rate, CLP = 0+1 */
   U32  fwdMeanBurstSize0;        /* forward  mean burst size, CLP = 0   */
   U32  bwdMeanBurstSize0;        /* backward mean burst size, CLP = 0   */
   U32  fwdMeanBurstSize1;        /* forward  mean burst size, CLP = 0+1 */
   U32  bwdMeanBurstSize1;        /* backward mean burst size, CLP = 0+1 */
   Bool bstEffortReq;             /* best effort requested */
   Bool fwdTagReq;                /* tagging requested in forward  direction */
   Bool bwdTagReq;                /* tagging requested in backward direction */
} AtmTfcDesc;

#endif /* CMFILE_REORG_1 */


/* scc typedefs */

typedef S16 Baud;                 /* baud */

typedef S16 PhysIntType;          /* physical interface type */

typedef S16 PathConnType;         /* path connection type */

typedef S16 Parity;               /* parity */

typedef S16 CharLength;           /* character length */

typedef S16 StopBits;             /* stop bits */

/* tcp/ip typedefs */

typedef U32 IpAddr;               /* IP address */

typedef U16 Port;                 /* TCP/UDP port */

typedef U8 Cmd;                   /* command */

typedef U8 Flags;                 /* TCP/UDP flags */

typedef U8 Ttl;                   /* time to live */

typedef U8 Prec;                  /* TCP/UDP precedence */

typedef U32 Window;               /* TCP/UDP window */

typedef U8 MtpStatus;             /* MTP status */

typedef U8 Credit;                /* credit */

/* ISUP typedefs */

typedef U32 CirId;                /* circuit Id */

typedef U16 Cic;                  /* cic */

typedef U32 SiInstId;             /* instance id */

/* B-ISUP typedefs */

typedef U32 BiInstId;             /* instance id */

/* TUP typedefs */

typedef U32 TpInstId;             /* instance id */

/* LLC/SNAP definitions */

typedef U32 Oui;                 /* 3-octet OUI in SNAP header */
typedef U16 Pid;                 /* 2-octet protocol id in SNAP header */
typedef U32 LlcId;               /* LLC id */


#ifndef CMFILE_REORG_1

/* q.93b typedefs */
 
typedef S32 AmInstId;             /* service user/provider instance id */
typedef U16 AmEndptRefType;       /* endpoint reference */
typedef U32 AmSeqNmb;             /* sequence number */
 
/* q.saal typedefs */
 
typedef U16 AsErrorCode;          /* q.saal error code (Q.SAAL1 Appendix 1) */

/* ume typedefs */

typedef U32 UmInteger;            /* ume integer */
 
typedef struct umObjId            /* ume object identifier */
{
   Data length;                   /* length of string */
   UmInteger strg[UM_MAXLEN_OBJ_ID]; /* string of sub-identifiers */
} UmObjId;

typedef struct umMib UmMib;       /* ume mib */


/* 
 * LAN Emulation typedefs 
 */

/* general typedefs */

typedef U16 LecId;               /* LEC Id */
typedef U8  Protocol;            /* protocol */
typedef U8  Version;             /* version */
typedef U16 OpCode;              /* op code in control frames */
typedef U16 LaneStatus;          /* status in control frames */
typedef U32 TransId;             /* transaction id */
typedef U16 LaneFlags;           /* flags in control frames */
typedef U8  LanType;             /* LAN type */
typedef U8  MtuIdx;              /* max frame size - index */
typedef U16 MtuVal;              /* max frame size - value */
typedef U16 Tag;                 /* tag indicating LAN destination type */
typedef U8  VccNature;           /* VCC nature - SVC, PVC, etc. */
typedef U8  VccType;             /* VCC type - control, data, etc */
typedef U8  ProfileId;           /* HCC profile id */


typedef struct lanName          /* LAN name */
{
   U8 length;                   /* length of string */
   U8 strg[MAX_LANNAME];        /* name string */
} LanName;

/* LAN destination typedefs */

typedef struct macAddr          /* MAC address */
{
   U8 strg[MACADDRLEN];         /* address string */
} MacAddr;

typedef struct macAddrTblEntry  /* entry in table of MAC addresses */
{
   U8 proxyClass;               /* proxy class - local, learned */
   MacAddr macAddr;             /* MAC address */
} MacAddrTblEntry;

typedef struct macAddrTbl       /* table of MAC addresses */
{
   U8 count;                    /* number of entries */
   MacAddrTblEntry tbl[MAX_MACADDRTBL]; /* table of MAC addresses */
} MacAddrTbl;

typedef struct rd               /* route designator */
{
   U16 lanId;                   /* LAN id, segment id - 12 bits */
   U8  bridgeId;                /* bridge id - 4 bits */
} Rd;

typedef struct rdTblEntry       /* entry in table of route designators */
{
   Rd rd;                       /* route designator */
} RdTblEntry;

typedef struct rdTbl            /* table of route designators */
{
   U8 count;                    /* number of entries */
   RdTblEntry tbl[MAX_RDTBL];/* table of route designator */
} RdTbl;

typedef struct lanDst           /* LAN destination - MAC addr, route desg */
{
   Tag tag;                     /* LAN destination type */
   union
   {
      MacAddr macAddr;          /* MAC address */
      Rd rd;                    /* route designator */
   } ld;
} LanDst;


/* control frame typedefs */

typedef struct laneCtrlHdr      /* control frame header */
{
   LecId      marker;           /* control frame marker */
   Protocol   protocol;         /* LANE protocol */
   Version    version;          /* LANE version */
   OpCode     opCode;           /* operation code */
   LaneStatus status;           /* request status */
   TransId    transId;          /* transaction id */
   LecId      reqLecId;         /* requestor LEC id */
   LaneFlags  flags;            /* bit flags */
   LanDst     srcLanDst;        /* source LAN destination */
   LanDst     dstLanDst;        /* target LAN destination */
   Addrs      srcAtmAddr;       /* source ATM address */
   Addrs      dstAtmAddr;       /* target ATM address */
   LanType    lanType;          /* LAN type */
   MtuIdx     mtuIdx;           /* MTU */
   U8         nmbTLV;           /* number of TLV entries in list */
   LanName    lanName;          /* LAN name */
} LaneCtrlHdr;

typedef struct laneTLVEnt       /* type-length-value entry */
{
   U32 type;                    /* type of value */
   U8  length;                  /* length of value */
   U8  value[MAX_TLV_LEN];      /* value */
} LaneTLVEnt;

typedef struct laneCfg          /* configuration frame */
{
   LaneTLVEnt  tlvTbl[MAX_TLV_TBL]; /* list of TLV entries */
} LaneCfg;

typedef struct laneCtrlFrame    /* all control frames */
{
   LaneCtrlHdr  hdr;            /* frame header */
   union                        /* remainder of frame */
   {
      LaneCfg   cfg;            /* configuration frame */
   } m;
} LaneCtrlFrame;

/* PNNI typedefs */

/* pnni port id */
typedef U32 PnPortId;

/* pnni node Id */
typedef struct pnNodeId
{
   U8 id[PN_NODEID_LEN];
} PnNodeId;

#endif /* CMFILE_REORG_1 */



/* header typedefs */

typedef struct octStrg            /* octet string */
{
   S32 length;                    /* length */
   U8 val[MF_SIZE_TKNSTR];        /* value */
} OctStrg;

typedef struct tknHdr             /* token header */
{
   U8   pres;                     /* present */
   U8   spare1;                   /* for 16 bit alignment */
   U16  spare2;                   /* for 32 bit alignment */
#ifdef ALIGN_64BIT
   U32  spare3;                   /* for 64 bit alignment */
#endif
} TknHdr;

typedef struct elmtHdr            /* element header */
{
   U8   pres;                     /* present */
   U8   actnInd;                  /* action indicator */
   U16  compInd;                  /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare;                    /* for 64 bit alignment */
#endif
} ElmtHdr;

/* token typedefs */

typedef struct tknU8              /* token U8 */
{
   U8   pres;                     /* present flag */
   U8   val;                      /* value */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
#endif
} TknU8;

typedef struct tknS8              /* token S8 */
{
   U8   pres;                     /* present flag */
   S8   val;                      /* value */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
#endif
} TknS8;

typedef struct tknU16             /* token U16 */
{
   U8   pres;                     /* present flag */
   U8   spare1;                   /* for alignment */
   U16  val;                      /* value */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
#endif
} TknU16;

typedef struct tknU32             /* token U32 */
{
   U8   pres;                     /* present flag */
   U8   spare1;                   /* for alignment */
   U16  spare2;                   /* for alignment */
   U32  val;                      /* value */
} TknU32;

typedef struct tknS32             /* token S32 */
{
   U8   pres;                     /* present flag */
   U8   spare1;                   /* for alignment */
   U16  spare2;                   /* for alignment */
   S32  val;                      /* value */
} TknS32;

typedef struct tknStrS            /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
   U8   val[(MF_SIZE_TKNSTRS + 7) & 0xff8]; /* string value */
#else
   U8   val[(MF_SIZE_TKNSTRS + 3) & 0xffc]; /* string value */
#endif
} TknStrS;

typedef struct tknStrM            /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
   U8   val[(MF_SIZE_TKNSTRM + 7) & 0xff8]; /* string value */
#else
   U8   val[(MF_SIZE_TKNSTRM + 3) & 0xffc]; /* string value */
#endif
} TknStrM;

typedef struct tknStr             /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
   U8   val[(MF_SIZE_TKNSTR + 7) & 0xff8]; /* string value */
#else
   U8   val[(MF_SIZE_TKNSTR + 3) & 0xffc]; /* string value */
#endif
} TknStr;

typedef struct tknStrE            /* token string extended */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
   U8   val[(MF_SIZE_TKNSTRE + 7) & 0xff8]; /* string value */
#else
   U8   val[(MF_SIZE_TKNSTRE + 3) & 0xffc]; /* string value */
#endif
} TknStrE;

typedef struct tknStrXL           /* token string extra long */
{
   U16  len;                      /* length */
   U8   pres;                     /* present flag */
   U8   spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
#endif
   U8   *val;                     /* string value (use allocated memory) */
} TknStrXL;
 
typedef struct tknStr4            /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
   U8   val[8];                   /* string value - 8 byte alligned */
#else
   U8   val[4];                   /* string value - 4 byte alligned */
#endif /* ALIGN_64BIT */
} TknStr4;

typedef struct tknStr12           /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
   U8   val[16];                  /* string value - 8 byte alligned */
#else
   U8   val[12];                  /* string value - 4 byte alligned */
#endif /* ALIGN_64BIT */
} TknStr12;

typedef struct tknStr32           /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
#endif
   U8   val[32];                  /* string value - 4 byte alligned */
} TknStr32;

typedef struct tknStr64           /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
#endif
   U8   val[64];                  /* string value - 4 byte alligned */
} TknStr64;

typedef struct tknStr132          /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
   U8   val[136];                 /* string value - 8 byte alligned */
#else
   U8   val[132];                 /* string value - 4 byte alligned */
#endif /* ALIGN_64BIT */
} TknStr132;

typedef struct tknStr256          /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
#endif
   U8   val[256];                 /* string value - 4 byte alligned */
} TknStr256;

typedef struct tknOid             /* Object Identifier */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
#endif
   /* gen_x_001.main_81 : changed val from U32 to U16 with comilation flag
    * TKNOID_U16 */
#ifndef TKNOID_U16
   U32  val[32];                  /* max 32 integers of less than 64k value */
#else
   U16  val[32];                  /* max 32 integers of less than 64k value */
#endif
} TknOid;

typedef struct tknBits            /* token bits */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* for alignment */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
   U8   val[(MF_SIZE_TKNBITS + 7) & 0xff8]; /* string value */
#else
   U8   val[(MF_SIZE_TKNBITS + 3) & 0xffc]; /* string value */
#endif
} TknBits;

typedef struct elmtStr            /* element string */
{
   ElmtHdr eh;                    /* element header */
   TknStr str;                    /* network specific information */
} ElmtStr;

typedef struct cdPtyNmb           /* called party number tokens */
{
   ElmtHdr eh;                    /* element header */
   TknU8 nmbPlanId;               /* numbering plan identification */
   TknU8 typeNmb0;                /* type of number */
#ifdef CDPTYNMB_32DIGIT
   TknStrM nmbDigits;             /* number digits */
#else
   TknStrS nmbDigits;             /* number digits */
#endif /* CDPTYNMB_32DIGIT */
} CdPtyNmb;

typedef struct redirNmb           /* redirecting number tokens */
{
   ElmtHdr eh;                    /* element header */
   TknU8 nmbPlanId;               /* numbering plan identification */
   TknU8 typeNmb;                 /* type of number */
   TknU8 screenInd;               /* screening indicator */
   TknU8 presInd;                 /* presentation indicator */
   TknU8 rsnRedirect;             /* reason for redirection */
   TknStrS nmbDigits;             /* number digits */
} RedirNmb;

typedef struct srvClass           /* service class */          
{                                                       
   U8 type;                       /* type */                 
   union                                                
   {                                                    
      struct                      /* frame relay */                                
      {                                                 
         Bool cr;                 /* command response bit */
         Bool de;                 /* discard eligibility bit */ 
      } fr;                                             
      struct                      /* mac */
      {                                                 
         Prior prior;             /* priority */            
      } ma;                                             
   } s;                                                 
} SrvClass;                                              

/* ip header, without options */

typedef struct _ip           /* ip header */
{
   U8     ip_hl;            /* header length */
   Prec   ip_tos;           /* type of service */
   U16    ip_len;           /* total length */
   U16    ip_id;            /* identification */
   U16    ip_off;           /* fragment offset field */
   Ttl    ip_ttl;           /* time to live */
   U8     ip_p;             /* protocol */
   U16    ip_sum;           /* checksum */
   IpAddr ip_src;           /* source address */
   IpAddr ip_dst;           /* dest address */
} Ip;
 

/* ATM structures */
 
#ifndef CMFILE_REORG_1

/* info elements that can be used for routing calls */
 
typedef struct amCdPtySad       /* Called Party Sub Address Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   oddEvenInd;          /* odd/even indicator */
   TknU8   typeSad;             /* type of sub address */
   TknStrS  sadInfo;            /* address/number information */
} AmCdPtySad;
 
typedef struct amBHiLyrInfo     /* Broadband High Layer Information Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   hiLyrInfoType;       /* high layer information type */
   TknStrS  hiLyrInfo;          /* high layer information */
} AmBHiLyrInfo;
 
typedef struct amBBearCap       /* Broadband Bearer Capability Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   bearClass;           /* bearer class */
   TknU8   timingReq;           /* timing requirement */
   TknU8   tfcType;             /* traffic type */
   TknU8   atmTfrCap;           /* ATM transfer capability */
   TknU8   usrPlaneConCfg;      /* user plane connection configuration */
   TknU8   suscClip;            /* susceptability to clipping */
} AmBBearCap;

typedef struct amQosParam       /* Quality of Service Parameter Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   qosClassFwd;         /* quality of service class forward */
   TknU8   qosClassBwd;         /* quality of service class backward */
} AmQosParam;

typedef struct amEtoeDly        /* End To End Transit Delay Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   cumTransDlyId;       /* cumulative transit delay id */
   TknU16  cumTransDly;         /* cumulative transit delay value */
   TknU8   reqTransDlyId;       /* requested max end to end transit delay id */
   TknU16  reqTransDly;         /* maximum end to end transit delay value */
   TknU8   pnniAccFMCTDId;      /* PNNI acceptable forward max. CTD ID */
   TknU32  pnniAccFMCTD;        /* PNNI acceptable forward max. CTD */
   TknU8   pnniCumFMCTDId;      /* PNNI acceptable forward max. CTD ID */
   TknU32  pnniCumFMCTD;        /* PNNI acceptable forward max. CTD */
   TknU8   netGenInd;           /* network generated indicator */
} AmEtoeDly;

typedef struct amOamTfcDesc     /* OAM Traffic Descriptor Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   usrNetFaultMgmt;     /* user network fault management indicator */
   TknU8   compInd;             /* compliance indicator */
   TknU8   shapingInd;          /* shaping indicator */
   TknU8   bwdEtoeOamF5FlInd;   /* backward e-to-e OAM F5 flow indicator */
   TknU8   fwdEtoeOamF5FlInd;   /* forward e-to-e OAM F5 flow indicator */
} AmOamTfcDesc;

typedef struct amEndptRef       /* Endpoint Reference Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   endptRefType;        /* endpoint reference type */
   TknU16  endptRefVal;         /* endpoint reference value */
} AmEndptRef;

typedef struct amAalParam       /* AAL Parameters Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   aalType;             /* AAL type */

   /* Token definition for AAL-1 */
   TknU8   subTypeId;           /* Subtype Identifier */
   TknU8   subType;             /* Subtype */
   TknU8   cbrRateId;           /* CBR Rate Identifier */
   TknU8   cbrRate;             /* CBR Rate */
   TknU8   multId;              /* Multiplier Identifier */
   TknU16  multVal;             /* Multiplier value */
   TknU8   srcClkFreqMetId;     /* Source clock Frequency method identifier */
   TknU8   srcClkFreqMet;       /* Source Clock frequency method */
   TknU8   errCrMetId;          /* Error correction method identifier */
   TknU8   errCrMet;            /* Error correction method */
   TknU8   strDatTxBlkszId;     /* Structured data transfer blocksize Id. */
   TknU8   strDatTxBlksz0;      /* Structured data transfer blocksize - oct 1*/

   /* Token definition for AAL-1, except in UNI 3.0 */
   TknU8   strDatTxBlksz1;      /* Structured data transfer blocksize - oct 2*/

   /* Token definition for AAL-1 */
   TknU8   prtFillCellId;       /* Partially filled cells Identifier */
   TknU8   prtFillCellMet;      /* Partially filled cells method */

   /* Token definition for AAL-3/4 and AAL-5 */
   TknU8   fwdMaxCpcsSduSzId;   /* Forward maximum CPCS-SDU size identifier */
   TknU16  fwdMaxCpcsSduSz;     /* Forward maximum CPCS-SDU size */
   TknU8   bwdMaxCpcsSduSzId;   /* Forward maximum CPCS-SDU size identifier */
   TknU16  bwdMaxCpcsSduSz;     /* Forward maximum CPCS-SDU size */

   /* Token definition for AAL-3/4 only */
   TknU8   midRangeId;          /* MID Range identifier */
   TknU16  loMidRange;          /* MID Range value */

   /* Token definition for AAL-3/4 only, except in UNI 3.0 */
   TknU16  hiMidRange;          /* MID Range value */

   /* Token definition for AAL-3/4 and AAL-5 and only for UNI 3.0 */
   TknU8   modeId;              /* Mode identifier */
   TknU8   mode;                /* Mode - Streaming/Message */

   /* Token definition for AAL-3/4 and AAL-5 */
   TknU8   sscsTypeId;          /* SSCS Type Identifier */
   TknU8   sscsType;            /* SSCS Type */

   /* Token definition for User defined AAL */
   TknU32  usrDefAalInfo;       /* User defined AAL information */
} AmAalParam;

typedef struct amBLoLyrInfo     /* Broadband Low Layer Information Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   usrInfoLyr1Prot;     /* user information layer 1 protocol */
   TknU8   lyr1Id;              /* Layer 1 id */
   TknU8   usrInfoLyr2Prot;     /* user information layer 2 protocol */
   TknU8   lyr2Id;              /* Layer 2 id */
   TknU8   q933Use;             /* Q.933 use */
   TknU8   lyr2OprMode;         /* Mode of operation */
   TknU8   winSize;             /* Window size */
   TknU8   usrSpecLyr2ProtInfo; /* User specified layer 2 protocol info */
   TknU8   usrInfoLyr3Prot;     /* user information layer 3 protocol */
   TknU8   lyr3Id;              /* Layer 3 id */
   TknU8   lyr3OprMode;         /* Mode of operation */
   TknU8   defPktSize;          /* Default packet size */
   TknU8   pktWinSize;          /* Default packet size */
   TknU8   usrSpecLyr3ProtInfo; /* User specified layer 3 protocol info */
   TknU8   initProtId;          /* Initial protocol Identifier bits 8-2 */
   TknU8   snapId;              /* SNAP identifier */
   TknU32  oui;                 /* Organisation unique identifier */
   TknU16  protId;              /* Protocol identifier */
} AmBLoLyrInfo;

typedef struct amAtmTfcDesc     /* ATM Traffic Descriptor Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   fwdPeakCellRateId0;  /* forward  peak  cell rate id, CLP = 0 */
   TknU32  fwdPeakCellRate0;    /* forward  peak  cell rate,    CLP = 0   */
   TknU8   bwdPeakCellRateId0;  /* backward peak  cell rate id, CLP = 0 */
   TknU32  bwdPeakCellRate0;    /* backward peak  cell rate,    CLP = 0   */
   TknU8   fwdPeakCellRateId1;  /* forward  peak  cell rate id, CLP = 0+1 */
   TknU32  fwdPeakCellRate1;    /* forward  peak  cell rate,    CLP = 0+1 */
   TknU8   bwdPeakCellRateId1;  /* backward peak  cell rate id, CLP = 0+1 */
   TknU32  bwdPeakCellRate1;    /* backward peak  cell rate,    CLP = 0+1 */
   TknU8   fwdSustCellRateId0;  /* forward  sust. cell rate id, CLP = 0 */
   TknU32  fwdSustCellRate0;    /* forward  sust. cell rate,    CLP = 0   */
   TknU8   bwdSustCellRateId0;  /* backward sust. cell rate id, CLP = 0 */
   TknU32  bwdSustCellRate0;    /* backward sust. cell rate,    CLP = 0   */
   TknU8   fwdSustCellRateId1;  /* forward  sust. cell rate id, CLP = 0+1 */
   TknU32  fwdSustCellRate1;    /* forward  sust. cell rate,    CLP = 0+1 */
   TknU8   bwdSustCellRateId1;  /* backward sust. cell rate id, CLP = 0+1 */
   TknU32  bwdSustCellRate1;    /* backward sust. cell rate,    CLP = 0+1 */
   TknU8   fwdMeanBurstSizeId0; /* forward  mean burst size id, CLP = 0 */
   TknU32  fwdMeanBurstSize0;   /* forward  mean burst size,    CLP = 0   */
   TknU8   bwdMeanBurstSizeId0; /* backward mean burst size id, CLP = 0 */
   TknU32  bwdMeanBurstSize0;   /* backward mean burst size,    CLP = 0   */
   TknU8   fwdMeanBurstSizeId1; /* forward  mean burst size id, CLP = 0+1 */
   TknU32  fwdMeanBurstSize1;   /* forward  mean burst size,    CLP = 0+1 */
   TknU8   bwdMeanBurstSizeId1; /* backward mean burst size id, CLP = 0+1 */
   TknU32  bwdMeanBurstSize1;   /* backward mean burst size,    CLP = 0+1 */
   TknU8   bstEffortReq;        /* best effort requested */
   TknU8   tfcMgmtOptId;        /* traffic management options identifier */
   TknU8   fwdTagReq;           /* tagging requested in forward  direction */
   TknU8   bwdTagReq;           /* tagging requested in backward direction */
   TknU8   bwdFrmDisc;          /* frame discard in backward direction */
   TknU8   fwdFrmDisc;          /* frame discard in forward  direction */
   TknU8   fwdAbrMinCellRateId; /* forward  ABR min. cell rate id, CLP = 0+1 */
   TknU32  fwdAbrMinCellRate;   /* forward  ABR min. cell rate,    CLP = 0+1 */
   TknU8   bwdAbrMinCellRateId; /* backward ABR min. cell rate id, CLP = 0+1 */
   TknU32  bwdAbrMinCellRate;   /* backward ABR min. cell rate,    CLP = 0+1 */
} AmAtmTfcDesc;

typedef struct amCauseDgn       /* Cause and Diagnostics Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   location;            /* location */
   TknU8   causeVal;            /* cause value */
   TknStrM  dgnVal;              /* Diagnostics value */
} AmCauseDgn;

typedef struct amCgPtyNmb       /* Calling Party Number Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   nmbPlanId;           /* address/numbering plan identification */
   TknU8   typeNmb;             /* type of number */
   TknU8   screenInd;           /* screening indicator */
   TknU8   presInd;             /* presentation indicator */
   TknStrS nmbDigits;           /* address/number information */
} AmCgPtyNmb;

typedef struct amCgPtySad       /* Calling Party Sub Address Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   oddEvenInd;          /* odd/even indicator */
   TknU8   typeSad;             /* type of sub address */
   TknStrS sadInfo;             /* address/number information */
} AmCgPtySad;

typedef struct amNBearCap       /* Narrowband Bearer Capability Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8 infoTranCap;           /* information transfer capability */
   TknU8 codingStd;             /* coding standard */
   TknU8 infoTranRate0;         /* information transfer rate */
   TknU8 tranMode;              /* transfer mode */
   TknU8 establish;             /* establishment */
   TknU8 cfg;                   /* configuration */
   TknU8 chanStruct;            /* structure */
   TknU8 infoTranRate1;         /* information transfer rate */
   TknU8 symmetry;              /* symmetry */
   TknU8 usrInfoLyr1Prot;       /* usr information layer 1 protocol */
   TknU8 lyr1Ident;             /* layer 1 identity */
   TknU8 usrRate;               /* user rate */
   TknU8 negot;                 /* negotiation */
   TknU8 syncAsync;             /* synchronous/asynchronous */
/*------------------------------------------------------------------------*/
/* The following six tokens represent a uinon of octets 5b.1 and 5b.2 of  */
/* the Narrow Band Bearer Capability.                                     */
/*------------------------------------------------------------------------*/
   TknU8 FlcRx_BandNeg;         /* flow control on reception or 
                                   inband/outband negotiation */
   TknU8 FlcTx_Assgn;           /* flow control on transmission or 
                                   assignor/assignee*/
   TknU8 NicRx_LLINeg;          /* network independent clock on reception or 
                                   logical link identifier negotiation */
   TknU8 NicTx_Mode;            /* network independent clock on transmission or
                                   mode of operation */
   TknU8 Rate_MFrm;             /* intermediate rate (low bit) or Multi 
                                   frame support */
   TknU8 Rate_Hdr;              /* intermediate rate (high bit) or rate 
                                   adaptation Hdr/ no Headr */
   TknU8 parity;                /* parity information */
   TknU8 nmbDatBits;            /* number of data bits excluding parity bit */
   TknU8 nmbStopBits;           /* number of stop bits */
   TknU8 modemType;             /* modem type */
   TknU8 duplexMode;            /* duplex mode */
   TknU8 usrInfoLyr2Prot;       /* user information layer 2 protocol */
   TknU8 lyr2Ident;             /* layer 2 identity */
   TknU8 usrInfoLyr3Prot;       /* user information layer 3 protocol */
   TknU8 lyr3Ident0;            /* layer 3 identity */
} AmNBearCap;

typedef struct amNLoLyrComp     /* Narrowband Low Layer Compatibility Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8 infoTranCap;           /* information transfer capability */
   TknU8 codingStd;             /* coding standard */
   TknU8 negInd;                /* negotiation indicator */
   TknU8 infoTranRate0;         /* information transfer rate */
   TknU8 tranMode;              /* transfer mode */
   TknU8 establish;             /* establishment */
   TknU8 cfg;                   /* configuration */
   TknU8 chanStruct;            /* structure */
   TknU8 infoTranRate1;         /* information transfer rate */
   TknU8 symmetry;              /* symmetry */
   TknU8 usrInfoLyr1Prot;       /* usr information layer 1 protocol */
   TknU8 lyr1Ident;             /* layer 1 identity */
   TknU8 usrRate;               /* user rate */
   TknU8 negot;                 /* negotiation */
   TknU8 syncAsync;             /* synchronous/asynchronous */
/*------------------------------------------------------------------------*/
/* The following six tokens represent a uinon of octets 5b.1 and 5b.2 of  */
/* the Narrow Band Lower Layer Compatibility                              */
/*------------------------------------------------------------------------*/
   TknU8 FlcRx_BandNeg;         /* flow control on reception or 
                                   inband/outband negotiation */
   TknU8 FlcTx_Assgn;           /* flow control on transmission or 
                                   assignor/assignee*/
   TknU8 NicRx_LLINeg;          /* network independent clock on reception or 
                                   logical link identifier negotiation */
   TknU8 NicTx_Mode;            /* network independent clock on transmission or
                                   mode of operation */
   TknU8 Rate_MFrm;             /* intermediate rate (low bit) or Multi 
                                   frame support */
   TknU8 Rate_Hdr;              /* intermediate rate (high bit) or rate 
                                   adaptation Hdr/ no Headr */
   TknU8 parity;                /* parity information */
   TknU8 nmbDatBits;            /* number of data bits excluding parity bit */
   TknU8 nmbStopBits;           /* number of stop bits */
   TknU8 modemType;             /* modem type */
   TknU8 duplexMode;            /* duplex mode */
   TknU8 usrInfoLyr2Prot;       /* user information layer 2 protocol */
   TknU8 lyr2Ident;             /* layer 2 identity */
   TknU8 optLyr2ProtInfo;       /* optional layer 2 protocol information */
   TknU8 usrInfoLyr3Prot;       /* user information layer 3 protocol */
   TknU8 lyr3Ident1;            /* layer 3 identity */
   TknU8 optLyr3ProtInfo;       /* optional layer 3 protocol information */
} AmNLoLyrComp;

typedef struct amNHiLyrComp     /* Narrowband High Layer Compatibility Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8 presMethod;            /* presentation method */
   TknU8 interpretation;        /* interpretation */
   TknU8 codingStd;             /* coding standard */
   TknU8 highLyrCharId;         /* high layer characteristics identification */
   TknU8 extHighLyrCharId;      /* extended high layer characteristics id */
} AmNHiLyrComp;

typedef struct amProgInd        /* Progress Indicator Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8 progLocation;          /* location */
   TknU8 codingStd;             /* coding standard */
   TknU8 progDesc;              /* progress description */
} AmProgInd;

#if (DEF_SIG_PNNI | DEF_SIG_AINI)
typedef struct amCrankback      /* Crankback Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   cbLevel;             /* crankback level */
   TknU8   blkTransType;        /* blocked transit type */
#ifdef SIG_PNNI
   TknStrS blkNodeId;           /* blocked node id */
   TknStrS blkLinkPreNodeId;    /* blocked link's preceeding node id */
   TknU32  blkLinkPortId;       /* blocked link port id */
   TknStrS blkLinkSuccNodeId;   /* blocked link's succeding node id */
#endif /* SIG_PNNI */
   TknU8   cbCause;             /* crankback cause */
#ifdef SIG_PNNI
   TknStrM cbDgn;               /* crankback cause diagnostics */
#endif /* SIG_PNNI */
} AmCrankback;

typedef struct amCdPtySoftPvc   /* Called Party Soft PVPC/PVCC Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   selType;             /* VPI/VCI selection Type */
   TknU8   vpiId;               /* VPI id */
   TknU16  vpi;                 /* VPI */
   TknU8   vciId;               /* VCI id */
   TknU16  vci;                 /* VCI */
#ifdef SPVC_FR
   TknU8   dlciId;              /* DLCI Identifer */
   TknU32  dlci;                /* Dlci Value */
#endif /* SPVC_FR */
} AmCdPtySoftPvc;

typedef struct amCgPtySoftPvc   /* Calling Party Soft PVPC/PVCC Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   vpiId;               /* VPI id */
   TknU16  vpi;                 /* VPI */
   TknU8   vciId;               /* VCI id */
   TknU16  vci;                 /* VCI */
#ifdef SPVC_FR
   TknU8   dlciId;              /* DLCI Identifer */
   TknU32  dlci;                /* Dlci Value */
#endif /* SPVC_FR */
} AmCgPtySoftPvc;
#endif /* DEF_SIG_PNNI | DEF_SIG_AINI */

typedef struct amConnNmb        /* Connected Number Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   nmbPlanId;           /* address/numbering plan identification */
   TknU8   typeNmb;             /* type of number */
   TknU8   screenInd;           /* screening indicator */
   TknU8   presInd;             /* presentation indicator */
   TknStrS nmbDigits;           /* address/number information */
} AmConnNmb;

#if (DEF_SIG_PNNI | DEF_SIG_AINI | DEF_UNI40)
typedef struct amConnSad        /* Calling Party Sub Address Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   oddEvenInd;          /* odd/even indicator */
   TknU8   typeSad;             /* type of sub address */
   TknStrS sadInfo;             /* address/number information */
} AmConnSad;

typedef struct amGenIdTrans     /* Generic Identifier Transport Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknStrM genId;               /* generic identifier */
} AmGenIdTrans;

typedef AmAtmTfcDesc   AmAltAtmTfcDesc;  /* Alternative ATM Traffic Desc. */

typedef struct amMinAccAtmTfcDesc  /* Minimum acceptable ATM Traffic Desc. */
{
   ElmtHdr eh;                     /* element header */
   TknU8   fwdPeakCellRateId0;     /* forward  peak  cell rate id, CLP = 0 */
   TknU32  fwdPeakCellRate0;       /* forward  peak  cell rate,    CLP = 0   */
   TknU8   bwdPeakCellRateId0;     /* backward peak  cell rate id, CLP = 0 */
   TknU32  bwdPeakCellRate0;       /* backward peak  cell rate,    CLP = 0   */
   TknU8   fwdPeakCellRateId1;     /* forward  peak  cell rate id, CLP = 0+1 */
   TknU32  fwdPeakCellRate1;       /* forward  peak  cell rate,    CLP = 0+1 */
   TknU8   bwdPeakCellRateId1;     /* backward peak  cell rate id, CLP = 0+1 */
   TknU32  bwdPeakCellRate1;       /* backward peak  cell rate,    CLP = 0+1 */
} AmMinAccAtmTfcDesc;

typedef struct amExtQosParam       /* Extended QOS parameter */
{
   ElmtHdr eh;                     /* element header */
   TknU8   origin;                 /* origin of this IE */
   TknU8   accFwdPpCDVId;          /* acceptable forward  peak-to-peak cell 
                                    * delay variation identifier */
   TknU32  accFwdPpCDV;            /* acceptable forward  peak-to-peak cell
                                    * delay variation */
   TknU8   accBwdPpCDVId;          /* acceptable backward peak-to-peak cell
                                    * delay variation identifier */
   TknU32  accBwdPpCDV;            /* acceptable backward peak-to-peak cell
                                    * delay variation */
   TknU8   cumFwdPpCDVId;          /* cumulative forward  peak-to-peak cell
                                    * delay variation identifier */
   TknU32  cumFwdPpCDV;            /* cumulative forward  peak-to-peak cell
                                    * delay variation */
   TknU8   cumBwdPpCDVId;          /* cumulative backward peak-to-peak cell
                                    * delay variation identifier */
   TknU32  cumBwdPpCDV;            /* cumulative backward peak-to-peak cell
                                    * delay variation */
   TknU8   accFwdCLRId;            /* acceptable forward  cell loss ratio
                                    * identifier */
   TknU8   accFwdCLR;              /* acceptable forward  cell loss ratio */
   TknU8   accBwdCLRId;            /* acceptable backward cell loss ratio 
                                    * identifier */
   TknU8   accBwdCLR;              /* acceptable backward cell loss ratio */
} AmExtQosParam;

typedef struct amAbrAddParam       /* ABR additional parameters */
{
   ElmtHdr eh;                     /* element header */
   TknU8   fwdAddParamRecId;       /* forward  additional parameters record identifier */
   TknU32  fwdAddParamRec;         /* forward  additional parameters record */
   TknU8   bwdAddParamRecId;       /* backward additional parameters record identifier */
   TknU32  bwdAddParamRec;         /* backward additional parameters record */
} AmAbrAddParam;

typedef struct amAbrSetupParam     /* ABR Setup parameters */
{
   ElmtHdr eh;                     /* element header */
   TknU8   fwdAbrICRId;            /* forward  ABR initial cell rate identifier */
   TknU32  fwdAbrICR;              /* forward  ABR initial cell rate */
   TknU8   bwdAbrICRId;            /* backward ABR initial cell rate identifier */
   TknU32  bwdAbrICR;              /* backward ABR initial cell rate */
   TknU8   fwdAbrTBEId;            /* forward  ABR transient buffer exposure identifier */
   TknU32  fwdAbrTBE;              /* forward  ABR transient buffer exposure */
   TknU8   bwdAbrTBEId;            /* backward ABR transient buffer exposure identifier */
   TknU32  bwdAbrTBE;              /* backward ABR transient buffer exposure */
   TknU8   cumRmFRTTId;            /* cumulative RM fixed round trip time identifier */
   TknU32  cumRmFRTT;              /* cumulative RM fixed round trip time */
   TknU8   fwdRIFId;               /* forward  rate increment factor identifier */
   TknU8   fwdRIF;                 /* forward  rate increment factor */
   TknU8   bwdRIFId;               /* backward rate increment factor identifier */
   TknU8   bwdRIF;                 /* backward rate increment factor */
   TknU8   fwdRDFId;               /* forward  rate decrement factor identifier */
   TknU8   fwdRDF;                 /* forward  rate decrement factor */
   TknU8   bwdRDFId;               /* backward rate decrement factor identifier */
   TknU8   bwdRDF;                 /* backward rate decrement factor */
} AmAbrSetupParam;
#endif /* DEF_SIG_PNNI | DEF_SIG_AINI | DEF_UNI40 */

#if (DEF_Q2931 | DEF_SIG_PNNI | DEF_SIG_AINI | DEF_UNI40)
typedef struct amNotInd         /* Notification Indicator Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknStrE notDesc;             /* notification description */
} AmNotInd;
#endif /* DEF_Q2931 | DEF_SIG_PNNI | DEF_SIG_AINI | DEF_UNI40 */


/* AAL structure */

typedef struct aalConParam        /* connection parameters for AAL */
{
   AmAalParam     aalParam;       /* AAL Parameters */
   AmAtmTfcDesc   atmTfcDesc;     /* ATM Traffic Descriptor */
   AmBBearCap     bBearCap;       /* Broadband Bearer Capability */
   AmQosParam     qosParam;       /* Qos parameters */
   AmEtoeDly      etoeDly;        /* End to End Transit Delay */
   AmOamTfcDesc   oamTfcDesc;     /* OAM Traffic Descriptor */
} AalConParam;

typedef struct amCdPtyNmb       /* Called Party Number Tokens */
{
   ElmtHdr eh;                  /* element header */
   TknU8   nmbPlanId;           /* address/numbering plan identification */
   TknU8   typeNmb;             /* type of number */
   TknStrS  nmbDigits;           /* address/number information */
} AmCdPtyNmb;

#endif /* CMFILE_REORG_1 */

 

/* management structures */

typedef struct smCfg            /* stack manager */
{
   Ent ent;                     /* entity */
   Inst inst;                   /* instance */
   Region region;               /* region */
   Pool pool;                   /* pool */
   Priority prior;              /* priority */
   Route route;                 /* route */
   Selector selector;           /* selector */
} SmCfg;

typedef struct mem                /* memory */
{
   Region region;                 /* region */
   Pool pool;                     /* pool */
   U16 spare;                     /* spare for alignment */
} Mem;  
   
typedef Mem MemoryId;             /* memory id */


typedef struct resp
{
   Selector selector;           /* selector */
   Priority prior;              /* priority */
   Route route;                 /* route */
   MemoryId mem;                /* memory */
}Resp;

typedef struct tds_header       /* header */
{
   U16 msgLen;                  /* message length   - optional */
   U8 msgType;                  /* message type     - mandatory */
   U8 version;                  /* version          - optional */
   U16 seqNmb;                  /* sequence number  - optional */
   EntityId entId;              /* entity id        - mandatory */
   ElmntId elmId;               /* element id       - mandatory */
#ifdef LMINT3
   TranId transId;              /* transaction Id - mandatory */
   Resp response;               /* response parameters - mandatory */
#endif /* LMINT3 */
} Header;

typedef struct tmrCfg           /* timer configuration structure */
{
   Bool enb;                    /* enable */
   U16 val;                     /* value */
} TmrCfg;

typedef struct asyncCfg         /* asynchronous configuration */
{
   StopBits stopBits;           /* stop bits */
   CharLength charLength;       /* character length */
   Parity rxParity;             /* receive parity */
   Parity txParity;             /* transmit parity */
} AsyncCfg;


/* dateTime structure */
  
typedef struct dateTime           /* date and time */
{
   U8 month;                      /* month */
   U8 day;                        /* day */
   U8 year;                       /* year */
   U8 hour;                       /* hour - 24 hour clock */
   U8 min;                        /* minute */
   U8 sec;                        /* second */
   U8 tenths;                     /* tenths of second */
   /*-- gen_x_001.main_90 - Added variable for microseconds in DateTime--*/
#ifdef SS_DATETIME_USEC
   U32 usec;                      /* micro seconds */
#endif /*-- SS_DATETIME_USEC --*/
} DateTime;
/* gen_x_001.main_94: Additions */
/* gen_x_001.main_95: Modifications */
typedef U64 EpcTime;

/* common status */
typedef struct cmStatus
{
   U16 status;       /* status of request */
   U16 reason;       /* failure reason */
}CmStatus;    

/* common alarm */
typedef struct cmAlarm
{
   DateTime dt;      /* data and time */
   U16 category;     /* alarm category*/
   U16 event;        /* alarm event */
   U16 cause;        /* alarm cause */
}CmAlarm;    
  
/* duration structure */
  
typedef struct duration           /* duration */
{
   U8 days;                       /* days */
   U8 hours;                      /* hours */
   U8 mins;                       /* minutes */
   U8 secs;                       /* seconds */
   U8 tenths;                     /* tenths of seconds */
} Duration;





#ifdef CMFILE_REORG_1

#ifdef SS
typedef struct ssmsgb Buffer;

#ifdef FLAT_BUFFER_OPT
typedef struct _flatBuffer
{
   U8* startAddr;
   U8* ptr;
   U32 len;
}FlatBuffer;
#endif

#else /* SS */

#ifdef WINNT_IATM                 /* Windows NT Integrated ATM */
#ifndef CFG_APP                   /* Don't include ndis.h for config app. */ 
#include "ndis.h"                 /* to support NDIS calls (listed above) */
#endif /* CFG_APP */

typedef struct _NDIS_PACKET Buffer; /* forward definition - buffer */
#else
typedef struct ss_buffer Buffer;  /* forward definition - buffer */

#endif /* WINNT_IATM */
#endif /* SS */

typedef struct tknBuf
{
   U8      pres;                  /* Present Flag */
   U8      spare1;                /* for alignment */
   U16     spare2;                /* for 32 bit alignment */
#ifdef ALIGN_64BIT
   U32     spare3;                /* for 64 bit alignment */
#endif
   Buffer  *val;                  /* Buffer type (use allocated memory) */
} TknBuf;

/* defining the CmIpAddr and CmIpAddr6 */
/* socket typedefs and structs */
typedef U32 CmIpAddr;        /* 4 byte IP address */
#ifdef IPV6_SUPPORTED
typedef U8  CmIpAddr6[16];   /* 16 byte IPV6 address */
#endif /* IPV6_SUPPORTED */

/* common packing functions */

/* system services structures */
EXTERN S16 cmPkDateTime ARGS((DateTime *dateTime, Buffer *mBuf));
EXTERN S16 cmPkDuration ARGS((Duration *duration, Buffer *mBuf));
EXTERN S16 cmPkPtr ARGS((PTR ptr, Buffer *mBuf));
EXTERN S16 cmPkEntityId ARGS((EntityId *entityId, Buffer *mBuf));
EXTERN S16 cmPkElmntId  ARGS((ElmntId  *elmntId,  Buffer *mBuf));
EXTERN S16 cmPkMemoryId ARGS((MemoryId *memoryId, Buffer *mBuf));

/* general structures */
EXTERN S16 cmPkSystemId ARGS((SystemId *systemId, Buffer *mBuf));
EXTERN S16 cmPkAddrs    ARGS((Addrs    *addrs,    Buffer *mBuf));
EXTERN S16 cmPkProtAddr ARGS((ProtAddr *protAddr, Buffer *mBuf));
EXTERN S16 cmPkProtAddrTbl ARGS((ProtAddrTbl *protAddr, Buffer *mBuf));
EXTERN S16 cmPkShrtAddrs ARGS((ShrtAddrs    *addrs,    Buffer *mBuf));
EXTERN S16 cmPkAddrMask ARGS((U8    *mask,    Buffer *mBuf));
EXTERN S16 cmPkBndCfg   ARGS((BndCfg   *bndCfg,   Buffer *mBuf));
EXTERN S16 cmPkPst      ARGS((Pst      *pst,      Buffer *mBuf));
EXTERN S16 cmPkElmtHdr  ARGS((ElmtHdr  *m,        Buffer *mBuf));
EXTERN S16 cmPkTknU8    ARGS((TknU8    *tknU8,    Buffer *mBuf));
EXTERN S16 cmPkTknS8    ARGS((TknS8    *tknS8,    Buffer *mBuf));
EXTERN S16 cmPkTknU16   ARGS((TknU16   *tknU16,   Buffer *mBuf));
EXTERN S16 cmPkTknU32   ARGS((TknU32   *tknU32,   Buffer *mBuf));
EXTERN S16 cmPkTknStr   ARGS((TknStr   *tknStr,   Buffer *mBuf));                              
EXTERN S16 cmPkTknStrM  ARGS((TknStrM  *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStrS  ARGS((TknStrS  *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStrE  ARGS((TknStrE  *tknStr,   Buffer *mBuf));

EXTERN S16 cmPkTknStr4   ARGS((TknStr4   *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStr12  ARGS((TknStr12  *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStr32  ARGS((TknStr32  *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStr64  ARGS((TknStr64  *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStr132 ARGS((TknStr132 *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStr256 ARGS((TknStr256 *tknStr,   Buffer *mBuf));

PUBLIC  S16  cmPkTknS32    ARGS((TknS32 *tknS32, Buffer *mBuf));
PUBLIC  S16  cmPkTknOid    ARGS((TknOid *tknOid, Buffer *mBuf));
PUBLIC  S16  cmPkTknBuf    ARGS((TknBuf *tknBuf, Buffer *mBuf));

#ifdef TDS_ROLL_UPGRADE_SUPPORT
PUBLIC  S16  cmPkIntf      ARGS((CmIntf *intf, Buffer *mBuf));
#endif

/* layer management structures */
EXTERN S16 cmPkHeader   ARGS((Header   *header,   Buffer *mBuf));
EXTERN S16 cmPkSmCfg    ARGS((SmCfg    *smCfg,    Buffer *mBuf));
EXTERN S16 cmPkTmrCfg   ARGS((TmrCfg   *tmrCfg,   Buffer *mBuf));
EXTERN S16 cmPkCmStatus ARGS((CmStatus *status,   Buffer *mBuf));
EXTERN S16 cmPkCmAlarm  ARGS((CmAlarm  *alrm,     Buffer *mBuf));


/* common unpacking functions */

/* system services structures */
EXTERN S16 cmUnpkDateTime ARGS((DateTime *dateTime, Buffer *mBuf));
EXTERN S16 cmUnpkDuration ARGS((Duration *duration, Buffer *mBuf));
EXTERN S16 cmUnpkPtr ARGS((PTR *ptr, Buffer *mBuf));
EXTERN S16 cmUnpkEntityId ARGS((EntityId *entityId, Buffer *mBuf));
EXTERN S16 cmUnpkElmntId  ARGS((ElmntId  *elmntId,  Buffer *mBuf));
EXTERN S16 cmUnpkMemoryId ARGS((MemoryId *memoryId, Buffer *mBuf));

/* general structures */
EXTERN S16 cmUnpkSystemId ARGS((SystemId *systemId, Buffer *mBuf));
EXTERN S16 cmUnpkAddrs    ARGS((Addrs    *addrs,    Buffer *mBuf));
EXTERN S16 cmUnpkProtAddr ARGS((ProtAddr *protAddr, Buffer *mBuf));
EXTERN S16 cmUnpkProtAddrTbl ARGS((ProtAddrTbl *protAddr, Buffer *mBuf));
EXTERN S16 cmUnpkShrtAddrs ARGS((ShrtAddrs    *addrs,    Buffer *mBuf));
EXTERN S16 cmUnpkAddrMask ARGS((U8    *mask,    Buffer *mBuf));
EXTERN S16 cmUnpkBndCfg   ARGS((BndCfg   *bndCfg,   Buffer *mBuf));
EXTERN S16 cmUnpkPst      ARGS((Pst      *pst,      Buffer *mBuf));
EXTERN S16 cmUnpkElmtHdr  ARGS((ElmtHdr  *m,        Buffer *mBuf));
EXTERN S16 cmUnpkTknU8    ARGS((TknU8    *tknU8,    Buffer *mBuf));
EXTERN S16 cmUnpkTknS8    ARGS((TknS8    *tknS8,    Buffer *mBuf));
EXTERN S16 cmUnpkTknU16   ARGS((TknU16   *tknU16,   Buffer *mBuf));
EXTERN S16 cmUnpkTknU32   ARGS((TknU32   *tknU32,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStr   ARGS((TknStr   *tknStr,   Buffer *mBuf));                              
EXTERN S16 cmUnpkTknStrM  ARGS((TknStrM  *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStrS  ARGS((TknStrS  *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStrE  ARGS((TknStrE  *tknStr,   Buffer *mBuf));

EXTERN S16 cmUnpkTknStr4   ARGS((TknStr4   *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStr12  ARGS((TknStr12  *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStr32  ARGS((TknStr32  *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStr64  ARGS((TknStr64  *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStr132 ARGS((TknStr132 *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStr256 ARGS((TknStr256 *tknStr,   Buffer *mBuf));

PUBLIC  S16  cmUnpkTknS32  ARGS((TknS32 *tknS32, Buffer *mBuf));
PUBLIC  S16  cmUnpkTknOid  ARGS((TknOid *tknOid, Buffer *mBuf));
PUBLIC  S16  cmUnpkTknBuf  ARGS((TknBuf *tknBuf, Buffer **mBuf));

#ifdef TDS_ROLL_UPGRADE_SUPPORT
PUBLIC  S16  cmUnpkIntf    ARGS((CmIntf *intf, Buffer *mBuf));
#endif

/* layer management structures */
EXTERN S16 cmUnpkHeader   ARGS((Header   *header,   Buffer *mBuf));
EXTERN S16 cmUnpkSmCfg    ARGS((SmCfg    *smCfg,    Buffer *mBuf));
EXTERN S16 cmUnpkTmrCfg   ARGS((TmrCfg   *tmrCfg,   Buffer *mBuf));
EXTERN S16 cmUnpkCmStatus ARGS((CmStatus *status,   Buffer *mBuf));
EXTERN S16 cmUnpkCmAlarm  ARGS((CmAlarm  *alrm,     Buffer *mBuf));

#endif /* CMFILE_REORG_1 */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __GENX__ */

  
/********************************************************************30**
  
         End of file:     gen.x@@/main/96 - Wed Dec 23 15:55:40 2009
    
*********************************************************************31*/


/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************70**
  
  version    initials                   description
-----------  ---------  ------------------------------------------------
1.1.0.0         jrl     1. initial release.

1.2.0.0         jrl     1. miscellaneous changes.

1.3.0.0         jrl     1. add structure for octet string used by isdn
                            network layer

1.4.0.0         jrl     1. remove structure for octet string and add
                            typedef for CalRef

1.5.0.0         jrl     1. add switch, token and header typedefs

1.6.0.0         jkm     1. add ElmtStr typedef

1.7.0.0         jkm     1. add TknBits typedef

1.8             lc      1. add CdPtyNmb structure
                lc      2. add RedirNmb structure
                lc      3. add names after struct for some typedefs
                jrl     4. trillium development system checkpoint (dvs)
                           at version: 1.7.0.0
                gp      5. add srvClass typedef
                jrl     6. add octStrg typedef from envdep.h

2.1             jkm     1. change token structures to save memory

2.2             jrl     1. add IpAddr, Port, Cmd, Flags typedefs for
                           TCP/IP
                        2. add Selector typedef for new interface

2.3             nkk     1. add Ttl, Prec, Window typedefs for TCP/IP

2.4             rk      1. change Dlci from U16 to U32 to support 2, 3, 4
                           bytes DLCIs

2.5             lc      1. added MtpStatus, LnkSetId, Dpc, SrvInfo,
                           LnkSel and Credit types for MTP Level 3

2.6             gp      1. changed ptNmb from a pointer to U8 to a pointer
                           to char in structure SystemId, to correct
                           several warnings

2.7             gp      1. change TknBits structure to add back len field

2.8             jrl     1. changed ptNmb from pointer to char to pointer to
                           S8
                jrl     2. changed usrId from pointer to U8 to pointer to
                           S8

2.9             bn      1. added isup typedefs "CirId" and "Cic".
                nkk     2. added ScrMode, DmFrame, DmScreen types
                           for display manager
                nkk     3. delete the following products from the "combined 
                           with" list: 
                              Multilink, Spanning Tree, ISO IP (End System),
                              and ISO IP (Intermediate System).
                nkk     4. add the following products to the "combined 
                           with" list: 
                              MOS, SDLC, MTP Level 2, 
                              MTP Level 3, ISUP, TCAP, ADCCP-NRM, 
                              SNMP Agent, SNMP Tools, SNMP Package, 
                              SCARF, UDP/IP and ESCC.
                nkk     5. add "typedef U8 Ssn;" for SCCP.
                nkk     6. add missing struct name "tknU16" to typedef 
                           TknU16;
                nkk     7. add "typedef U32 SiInstId;" for ISUP.
                jrl     8. text changes
    
*********************************************************************71*/

/********************************************************************80**

  version    pat  init                   description
----------- ----- ----  ------------------------------------------------
2.10         ---  jrl   1. text changes
             ---  jrl   2. remove display manager typedefs

2.11         ---  fmg   1. add LngAddrs struct
             ---  fmg   2. add typedefs for SCCP.

2.12         ---  jrl   1. change S8 to Txt for usrId in BndCfg

2.13         ---  fmg   1. change U16 to U32 for Dpc

2.14         ---  jrl   1. text changes

2.15         ---  nkk   1. move typedef Ip from tc.x to gen.x

2.16         ---  lc    1. text changes

2.17         ---  bn    1. add typedef TpInstId

2.18         ---  bn    1. add typedef tknStrE

2.19         ---  rg    1. added typedefs for q.93b.
             ---  nkk   2. added cpcs and atm support to service class 
                           structure.
             ---  nkk   3. added q.saal typedefs.

2.20         ---  nkk   1. upgraded reception status (cpcs.rs) storage from 
                           U8 to Status.

2.21         ---  nkk   1. moved SeqS24, SeqU24 and SetUpArb from q.saal to 
                           common section.
             ---  nkk   2. renamed AmVpci and AmVci to Vpci and Vci (and
                           moved to common section).
             ---  nkk   3. added SeqS16, SeqU16, and Vpi to common section.
             ---  nkk   4. used Vpi and Vci typedefs in SrvClass structure.
             ---  nkk   5. downgraded reception status (cpcs.rs) storage from 
                           Status to U8.
             ---  rg    6. prefixed Vpi, Vci and Vpci by Atm. 
             ---  rg    7. added SpId, AtmCi, AtmRs, AtmLp, AtmUu, AtmUui,
                           AtmQos and AtmCellRate.
             ---  nkk   8. removed cpcs and atm variants from srvClass union.
             ---  jrl   9. change ptNmb from S8 to Txt
             ---  fmg   10. change RetCause to RCause
             ---  fmg   11. add NIInd typedef
             ---  fmg   10. add ShrtAddrs typedef

2.22         ---  mma   1. moved glbTi structure from spt.x to gen.x
             ---  mma   2. moved spAddr structure from spt.x to gen.x

2.23         ---  nkk   1. replaced Priority with Prior.
             ---  nkk   2. move Selector to ss_??.x


2.24         ---  jrl   1. move Event typedef to ss_??.x

2.25         ---  bn    1. add typedef tknStrS
             ---  bn    2. changed definition of CdPtyNmb and RedirNmb

2.26         ---  nkk   1. changed TskInit to use new Pst instead of
                           old BndCfg. 
             ---  nkk   2. added procId field to TskInit.

2.27         ---  ak    1. added SmCfg, TmrCfg, AsnycCfg from
                           lm_pt.x

3.1          ---  ak    1. add LMINT2
             ---  rg    2. renamed AtmCellRate to AtmTfcDesc.

3.2          ---  jrl   1. move some typedefs from ssi.x to support
                           reordering of ssi and gen includes
             ---  rg    1. moved Q.93B typedefs from lm_pt.x.
             ---  rg    2. added prototype for smActvTsk, smActvInit, smInitExt.
             ---  rg    3. removed typedefs: AmInstId, AmCallRef, AmEndptRefType.
             ---  nkk   3. removed SscfState and SscopState.
             ---  nkk   4. added UmInteger and UmObjId.
             ---  nkk   5. removed AsDatIntState and AsMacIntState.
             ---  nkk   7. added Mode typedef.

3.3          ---  jrl   1. remove LMINT2

3.4          ---  nkk   1. remove AtmUui.

3.5          ---  rg    1. added typedefs for LAN Emulation.
             ---  rg    2. added typedef for TknStrM.
             ---  rg    3. replaced TknStr with TknStrM in Q.93B structures.

3.6          ---  rg    1. add AtmUui

3.7          ---  rg    1. changed "class" to "proxyClass" in MacAddrTblEntry.
             ---  rg    2. deleted "class" from RdTblEntry.

3.8          ---  ak    1. added StStr typedef
             ---  fmg   2. changed struct buffer to struct ss_buffer
                           and struct queue to struct ss_queue to avoid
                           conflicts with system include for other
                           operating systems (i.e. UNIX )
                        3. fixed alignment for Pst structure under SSINT2

3.9          ---  nkk   1. added forward definition of UmMib.

3.10         ---  vk    1. added new connection handle typedef ConnId.
             ---  vk    2. added AtmPt typedef for payload type.
             ---  nkk   3. removed unnecessary restriction in EvntType
                           comment.
             ---  rg    4. added AmInstId and AmEndptRefType from amt.x.
             ---  fmg   5. Aligned and Ordered Pst structure for SSINT

3.11         ---  ak    1. added PN port Id typedef.

3.12         ---  rg    1. changed TknHdr.pres from Bool to U8 to map more
                           accurately to the TknU*.pres field.
 
3.13         ---  rrb   1. Added definition of ATM Traffic Descriptor IE.
             ---  rrb   2. Added definition of Crankback IE.
             ---  rrb   3. Added a new IE definition called AmCdPtySoftPvc.
             ---  rrb   4. Added IE definition AmConnNmb and AmConnSad for
                           connected number and connected sunaddress res-
                           pectively.
             ---  rrb   5. Changed AtmVpi from U8 to U16 as PNNI refers to
                           VPI as 12 bits.
             ---  ak    6. removed ifdef SIG_PNNI from amBBearCap fields.
             ---  vk    7. changed AtmVpi from U8 to U16 
 
3.14         ---  rrb   1. modified use of TknStrM & TknStrS in Q.93B
                           IE structures.
      
3.15         ---  bn    1. added structures for B-ISUP.
             ---  fmg   2. changed struct header to struct tds_header
                           to avoid conflict with hpux kernel include
             ---  san   3. changed typedef tags for Buffer inside #ifdef WINNT.
             ---  bn    4. moved AmCauseDgn, AmCgPtySad, AmNBearCap,
                           AmNLoLyrComp, AmNHiLyrComp, AmProgInd from amt.x

3.16         ---  bn    1. changed typedef of CirId from U16 to U32.
3.17         ---  aa    1. Added typedef for StOctet (used by TCAP and MAP)

3.18         ---  fmg   1. Added InstId to SCCP section

3.19         ---  bn    1. added typedef for PortId for V5.1 PSTN.

3.20         ---  rrb   1. added structure definitions and typedefs specific
                           to UNI 4.0.
             ---  rrb   2. changed "spare1" field in ElmtHdr structure to
                           "actnInd".
             ---  rrb   3. Moved endpoint reference IE definition from amt.x
                           to gen.x
             ---  rg    4. Removed #ifdef ATM_BISUP from ElmtHdr.

3.21         ---  bw    1. added struct TknStrXL for PNNI unknown IG 
                           decode/encode
             ---  bw    2. change copyright header

3.22         ---  mg    1. added struct AmCgPtyNmb definition. (It was in
                           amt.x, previously.)
             ---  dm    2. removed #ifdef's surrounding AmConnNmb 

3.23         ---  bn    1. changed PortId from S16 to U16.
             ---  rrb   2. moved PnNodeId definition from lpn.x.
             ---  mb    3. moved Buffer and Queue def to ssi.x
             ---  aa    4. Moved the typedefs used by multiple SS7 portable
                           layers to cm_ss7.x

3.24         ---  mc    1. moved MtpStatus and Credit back from cm_ss7.x

3.25    es003.15  sa    1. modified flag type in LaneCtrlHdr to LaneFlags.

3.26    es003.15  rg    1. somehow the change listed above for 3.25 never
                           made it in the code, hence this is a repeat.

********************************************************************81*/

/********************************************************************90**
 
    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
3.27         ---      kvm  1. Added typedefs ProfileId, LlcId, AtmAddr,
                              AtmAddrTbl, AtmVccId, and AtmVccTbl
                           2. Added dbgMask and prntBuf to TskInit to support
                              debug printing

3.28         ---      sg   1. Added typedefs for TknStr4, TknStr12, TknStr32
                              TknStr64, TknStr132, TknStr256

3.29         ---      kvm  1. added CMATM2
             ---      kvm  2. merged in cm_gen.x
             ---      kvm  3. moved in typedefs DateTime, Duration, Mem,
                              and MemoryId from gen.x
             ---      kvm  4. moved out cmPkPnNodeId and cmUnpkPnNodeId
                              to cm_atm.x
             ---      kvm  5. moved in forward definition of Buffer from ssi.x
             ---      rb   6. Added typedef for MibOpCode and MibStatus to
                              support MIB request at LM interface.

3.30         ---      kvm  1. renamed CMATM2 as CMFILE_REORG_1

3.31         ---      sg   1. added token types for signed integer, oid
                              and message buffer

3.32         ---      rrb  1. added MibTblType and MibReqId definition to be
                              used in MibReq/MibCfm primitive. 
             ---      rrb  2. added UstaType definitions.
             ---      bbk  3. Added ProtAddr and ProtAddrTbl structures.
                              The structures right now cater to IP only
             ---      bbk  4. Added cmPkProtAddrTbl and cmUnpkProtAddrTbl
             ---      mg   5. Changes to pass through chksrc
3.33         ---      bbk  1. Changed copyright header date.

3.34         ---      nj   1. Added packing/unpacking routines for S32 and
                              Object identifiers.
3.35         ---      mk   1. Added declarations for functions cmPkPtr
                              and cmUnpkPtr.
3.36         ---      ag   1. WINNT section excluded for NTSS (ifndef NS)
             ---      ag   2. Added Buffer type prototype for Common
                              System Services (#ifdef SS)
             ---      sg   3. Added an additional token for S8 values.
                              Added packing/unpacking routines for it.

3.37         ---      ash  1. added support for LMINT3
                           2. added decleration for CmStatus and CmAlarm
                              packing/unpacking functions
             ---      ao   3. added unsigned connection id (UConnId)
3.38         ---      sg   1. Aligned TknU8, TknU16, TknStr4, TknStr12,
                              TknStr32, TknStr64, TknStr132, TknStr256,
                              TknStrXL, TknOid, TknBuf to 64 bit boundaries.
             ---      nj   2. Aligned rest of the token structures to the
                              64 bit boundary. 
             ---      rm   3. Added a new datatype 'StsCntr' of type U32
             ---      mp   4. TranNum and IntNum type definitions added.
             ---      bsr  5. Changed WINNT to WINNT_IATM and rearranged
                              Buffer typedef.

3.39         ---      ns   1. Added extern "C" for making this file C++
                              compatible 

3.41         ---      ada  1. Removed tab from file

3.42         ---      kp   1. Removed warning when compiling on Solaris
                              2.6 with POSIX compliance

3.43         ---      rs   1. Changed ElmtHdr for 64 bit alignment.

3.44         ---      tej  1. Change in header
3.45         ---      ag   1. Added cmPkProtAddr and cmUnpkProtAddr
3.46         ---      mb   1. Added Prototypes cmPkTknBuf, cmUnpkTknBuf
                      ao   2. Modified the definition of CdPtyNmb to
                              allow up to 32 digits depending on the 
                              CDPTYNMB_32DIGIT compile time option.
/main/75        ---      vb   1. Added defines for NwId

/main/77     ---      pss  1. Added autoSysIdPres and autoSysId to
                              ProtAddr structure, required for mpls
                              (cr-ldp) module.

/main/78     ---      mj   1. Changes for the implementation of SPVC addendum.
/main/79     ---      cvp  1. changed the copyright header date.
/main/80     ---      ns   1. Changes for rolling upgrade feature. New
                              typedefs added for the interface ID and version
/main/81     ---      wjs  1. Added support for AINI signalling.
/main/82     ---      wh   1. Changed val from U32 to U16 with comilation flag
                              TKNOID_U16. This is to hold some object identifier
                              value larger than 64k.
/main/84     ---      rk   1. IUA Rel 1.3 updates
                      bn   2. added VBIT  for DPNSS/DASS2
/main/85     ---      bn   1. Added Arr64U8
/main/86     ---      kkj  1. ProcId added to tskInit for multiple procId
                              support
/main/87     ---      st   1. Update for MAP Release 2.3
/main/89     ---      gs   1. Recovered Last correct version during MAC 1.3 RTR
/main/90     ---      sal  1. defining the CmIpAddr and CmIpAddr6.
/main/91     ---      gen_x_001.main_90      ss   1. Added variable for microseconds in DateTime
gen_x_001.main_91 ---  rs  1. Added new cBuffer structure for circular buffer
                              implementation.
                           2. Modifed TskInit structure for circular buffer.
gen_x_001.main_92 ---  sal 1. Modifed TskInit structure for Timestamp in DbgPrints.
gen_x_001.main_93 ---  sal 1. TimeStamp changes put under the 
                              compiletime flag DBG_TIMESTAMP.
/main/95     ---  gen_x_001.main_94 schandra1 1. Additions for SSI-Phase 2 features
/main/96     ---  gen_x_001.main_95 pmacharla 1. BIT_64 has been removed for EpcTime
                                                 long long doesn't require BIT_64
$SID$      ---  gen_x_001.main_96 akaranth 1. Added logmask
$SID$      ---  gen_x_001.main_97 sasahni  1. Added pointer for logging.
*********************************************************************91*/
