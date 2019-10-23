
/********************************************************************20**

     Name:     S1AP Layer 
  
     Type:     C include file
  
     Desc:     Defines required by the S1AP layer manager interface

     File:     lsz.h

     Sid:      lsz.h@@/main/6 - Thu Apr 26 19:04:28 2012

     Prg:      nm

*********************************************************************21*/

#ifndef __LSZH__
#define __LSZH__


/*
 *     The defines in this file
 *     correspond to structures and variables used by
 *     the following TRILLIUM software:
 *
 *     part no.             description
 *     --------     ----------------------------------------------
 *     1000361      S1AP 
 *
*/



/********************************************************************SZ**
 Event types
*********************************************************************SZ*/
#define EVTLSZCFGREQ          1     /* configuration request */
#define EVTLSZCFGCFM          2     /* configuration confirm */
#define EVTLSZCNTRLREQ        3     /* control request */
#define EVTLSZCNTRLCFM        4     /* control confirm */
#define EVTLSZSTAREQ          5     /* status request */
#define EVTLSZSTACFM          6     /* status confirm */
#define EVTLSZSTSREQ          7     /* statistics request */
#define EVTLSZSTSCFM          8     /* statistics confirm */
#define EVTLSZSTAIND          9     /* status indication */
#define EVTLSZTRCIND          10    /* trace indicattion */

/********************************************************************SZ**
 Node types
*********************************************************************SZ*/

/* lsz_h_001.main_5: Updated for  avtecs fixes */
/* lsz_h_001.main_4: Updated for S1AP Release 3.1 */
#define LSZ_NODE_MME           1   /* MME Node */
#define LSZ_NODE_ENB           2   /* eNB Node */
#define LSZ_NODE_GW            3   /* Gate Way node */

/********************************************************************SZ**
 SAP States
*********************************************************************SZ*/

#define LSZ_SAP_CFG           1     /* SAP Configured but not not bound */
#define LSZ_SAP_ISBOUND       2     /* SAP Bound */
#define LSZ_SAP_BINDING       3     /* SAP Bind initiated */
#define LSZ_SAP_UBND          4     /* SAP Unbind */

/********************************************************************SZ**
 Selector Values
*********************************************************************SZ*/

#define LSZ_SEL_LC            0     /* Loose coupling */
#define LSZ_SEL_LWLC          1     /* Light weight loose coupling - */
                                    /* applicable only on upper interface */
#define LSZ_SEL_TC_UZ         2     /* Tight coupling S1AP User */
#define LSZ_SEL_TC_SB         1     /* Tight coupling SCTP */

#define LSZ_SEL_TC_SM         1     /* Tight coupling SM */

/********************************************************************SZ**
 Element values
*********************************************************************SZ*/

#define STSZGEN               1           /* General */
#define STSZPROT              2           /* Protocol */
#define STSZSZTSAP            3           /* SZT SAP */
#define STSZSCTSAP            4           /* SCT SAP */
#define STSZPEER              5           /* Peer */
#define STSZSID               6           /* System Identifier */

/********************************************************************SZ**
 Trace defines
*********************************************************************SZ*/

#define LSZ_MAX_TRC_LEN       256   /* Maximum trace length */
 
#define LSZ_TRC_PNODE         1     /* Trace the peer node */
#define LSZ_TRC_LSAP_IN       2     /* Trace the lower sap in */
#define LSZ_TRC_LSAP_OUT      4     /* Trace the lower sap out */
#define LSZ_TRC_PNODE_IN      8     /* Trace the peer node in */
#define LSZ_TRC_PNODE_OUT     16    /* Trace the peer node out */

/********************************************************************SZ**
 Usta defines
*********************************************************************SZ*/
#define LSZ_USTA_DGNVAL_NONE     1   /* None */
#define LSZ_USTA_DGNVAL_MEM      2   /* Memory */
#define LSZ_USTA_DGNVAL_SAPID    3   /* Sap Id */
#define LSZ_USTA_DGNVAL_DATA     4   /* Data */
#define LSZ_USTA_DGNVAL_PEER     5   /* Peer */ 
#define LSZ_USTA_DGNVAL_CONID    6   /* Connection Id */
#define LSZ_USTA_MAX_DGNVAL      256 /* Maximum value */

/********************************************************************SZ**
 Specific reason values
*********************************************************************SZ*/

#define LSZ_REASON_PROTCFG_NOT_DONE    (LCM_REASON_LYR_SPECIFIC + 1)
#define LSZ_REASON_HASHINIT_FAIL       (LCM_REASON_LYR_SPECIFIC + 3)
#define LSZ_REASON_SAP_ASSOC_EXISTS    (LCM_REASON_LYR_SPECIFIC + 4)
#define LSZ_REASON_LSAPCFG_NOT_DONE    (LCM_REASON_LYR_SPECIFIC + 5)
#define LSZ_REASON_DUP_AUDIT_REQ       (LCM_REASON_LYR_SPECIFIC + 6)

/********************************************************************SZ**
 Specific event values
*********************************************************************SZ*/
#define LSZ_EVENT_LI_BND_CFM        (LCM_EVENT_LYR_SPECIFIC + 1)
#define LSZ_EVENT_LI_ENDP_OPEN_CFM  (LCM_EVENT_LYR_SPECIFIC + 2)
#define LSZ_EVENT_LI_ENDP_CLOSE_CFM (LCM_EVENT_LYR_SPECIFIC + 3)
#define LSZ_EVENT_LI_ASSOC_IND      (LCM_EVENT_LYR_SPECIFIC + 4)
#define LSZ_EVENT_LI_ASSOC_CFM      (LCM_EVENT_LYR_SPECIFIC + 5)
#define LSZ_EVENT_LI_TERM_IND       (LCM_EVENT_LYR_SPECIFIC + 6)
#define LSZ_EVENT_LI_TERM_CFM       (LCM_EVENT_LYR_SPECIFIC + 7)
#define LSZ_EVENT_LI_FLC_IND        (LCM_EVENT_LYR_SPECIFIC + 8)
/* lsz_h_001.main_2 for dynamic peer configuration */
#define LSZ_EVENT_LI_DAT_IND        (LCM_EVENT_LYR_SPECIFIC + 9)
#define LSZ_EVENT_LI_STA_IND        (LCM_EVENT_LYR_SPECIFIC + 10)
#define LSZ_EVENT_LI_SEND_FAIL      (LCM_EVENT_LYR_SPECIFIC + 11)
#ifdef SZ_MME
/* lsz_h_001.main_1 for dynamic peer configuration */
#define LSZ_EVENT_UI_PEERASSOC_RSP  (LCM_EVENT_LYR_SPECIFIC + 12)
#define LSZ_CAUSE_DYNAM_PEERCFG_OK  (LCM_CAUSE_LYR_SPECIFIC + 13)
#define LSZ_CAUSE_DYNAM_PEERCFG_NOK (LCM_CAUSE_LYR_SPECIFIC + 14)
#endif /* SZ_MME */

/********************************************************************SZ**
 Specific cause values
*********************************************************************SZ*/
#define LSZ_CAUSE_CONGESTION_RECV  (LCM_CAUSE_LYR_SPECIFIC + 1)
#define LSZ_CAUSE_ASSOC_UP         (LCM_CAUSE_LYR_SPECIFIC + 2)
#define LSZ_CAUSE_ASSOC_DOWN       (LCM_CAUSE_LYR_SPECIFIC + 3)
#define LSZ_CAUSE_PEER_DELETED     (LCM_CAUSE_LYR_SPECIFIC + 4)
#define LSZ_CAUSE_ENDP_OPEN        (LCM_CAUSE_LYR_SPECIFIC + 5)
#define LSZ_CAUSE_EXCEED_CONF_VAL  (LCM_CAUSE_LYR_SPECIFIC + 6)
#define LSZ_CAUSE_OUTRES           (LCM_CAUSE_LYR_SPECIFIC + 7)
#define LSZ_CAUSE_SCT_ENPOPEN_SUCC (LCM_CAUSE_LYR_SPECIFIC + 8)
#define LSZ_CAUSE_INV_PAR_VAL      (LCM_CAUSE_LYR_SPECIFIC + 9)
#define LSZ_CAUSE_EPCLOSE_OK       (LCM_CAUSE_LYR_SPECIFIC + 10)

/********************************************************************SZ**
 Other general defines
*********************************************************************SZ*/

#define LSZ_ZEROSTS           0        /* Reset the statistics counters */
#define LSZ_NOZEROSTS         1        /* no reset of statistics counters */

#define LSZ_MAX_PLMN_SIZE     3        /* maximum number of plmn octets */
#define LSZ_MME_GROUP         2        /* MME group */ 
#define LSZ_MME_CODE          1        /* MME code*/
#define LSZ_MAX_NUM_OF_PEERS  16000    /* Maximum no of peer nodes */

#define LSZ_PART_NUM_STR_LEN  32       /* String length */

/* database debug defines */
#define LSZ_DBGMASK_MF       (DBGMASK_LYR << 0)
#define LSZ_DBGMASK_DB       (DBGMASK_LYR << 1)
#define LSZ_DBGMASK_ASN      (DBGMASK_LYR << 2)

#define LSZ_DBGMASK_TMR      (DBGMASK_LYR << 3)



/********************************************************************SZ**
 Error defines
*********************************************************************SZ*/

#define   ERRLSZ       0                  /*  base     */
#define   ELSZ042      ERRLSZ             /*  reserved */  
/* lsz_h_001.main_4: Updated for S1AP Release 3.1 */

#define   ELSZ001      (ERRLSZ +    1)    /*        lsz.c: 672 */
#define   ELSZ002      (ERRLSZ +    2)    /*        lsz.c: 990 */
#define   ELSZ003      (ERRLSZ +    3)    /*        lsz.c:1054 */
#define   ELSZ004      (ERRLSZ +    4)    /*        lsz.c:1330 */
#define   ELSZ005      (ERRLSZ +    5)    /*        lsz.c:1570 */
#define   ELSZ006      (ERRLSZ +    6)    /*        lsz.c:1666 */
#define   ELSZ007      (ERRLSZ +    7)    /*        lsz.c:2146 */
#define   ELSZ008      (ERRLSZ +    8)    /*        lsz.c:2313 */
#define   ELSZ009      (ERRLSZ +    9)    /*        lsz.c:2386 */
#define   ELSZ010      (ERRLSZ +   10)    /*        lsz.c:3455 */
#define   ELSZ011      (ERRLSZ +   11)    /*        lsz.c:3465 */
#define   ELSZ012      (ERRLSZ +   12)    /*        lsz.c:3512 */
#define   ELSZ013      (ERRLSZ +   13)    /*        lsz.c:3522 */
#define   ELSZ014      (ERRLSZ +   14)    /*        lsz.c:3568 */
#define   ELSZ015      (ERRLSZ +   15)    /*        lsz.c:3578 */
#define   ELSZ016      (ERRLSZ +   16)    /*        lsz.c:3625 */
#define   ELSZ017      (ERRLSZ +   17)    /*        lsz.c:3635 */
#define   ELSZ018      (ERRLSZ +   18)    /*        lsz.c:3683 */
#define   ELSZ019      (ERRLSZ +   19)    /*        lsz.c:3693 */
#define   ELSZ020      (ERRLSZ +   20)    /*        lsz.c:3699 */
#define   ELSZ021      (ERRLSZ +   21)    /*        lsz.c:3742 */
#define   ELSZ022      (ERRLSZ +   22)    /*        lsz.c:3752 */
#define   ELSZ023      (ERRLSZ +   23)    /*        lsz.c:3798 */
#define   ELSZ024      (ERRLSZ +   24)    /*        lsz.c:3811 */
#define   ELSZ025      (ERRLSZ +   25)    /*        lsz.c:3858 */
#define   ELSZ026      (ERRLSZ +   26)    /*        lsz.c:3871 */
#define   ELSZ027      (ERRLSZ +   27)    /*        lsz.c:3917 */
#define   ELSZ028      (ERRLSZ +   28)    /*        lsz.c:3930 */
#define   ELSZ029      (ERRLSZ +   29)    /*        lsz.c:3978 */
#define   ELSZ030      (ERRLSZ +   30)    /*        lsz.c:3992 */
#define   ELSZ031      (ERRLSZ +   31)    /*        lsz.c:4045 */
#define   ELSZ032      (ERRLSZ +   32)    /*        lsz.c:4094 */
#define   ELSZ033      (ERRLSZ +   33)    /*        lsz.c:4143 */
#define   ELSZ034      (ERRLSZ +   34)    /*        lsz.c:4192 */
#define   ELSZ035      (ERRLSZ +   35)    /*        lsz.c:4237 */
#define   ELSZ036      (ERRLSZ +   36)    /*        lsz.c:4246 */
#define   ELSZ037      (ERRLSZ +   37)    /*        lsz.c:4297 */
#define   ELSZ038      (ERRLSZ +   38)    /*        lsz.c:4349 */
#define   ELSZ039      (ERRLSZ +   39)    /*        lsz.c:4403 */
#define   ELSZ040      (ERRLSZ +   40)    /*        lsz.c:4454 */
#define   ELSZ041      (ERRLSZ +   41)    /*        lsz.c:4504 */


#endif /* __LSZH__ */

/*********************************************************************

         End of file:     lsz.h@@/main/6 - Thu Apr 26 19:04:28 2012

**********************************************************************/

/**********************************************************************

        Notes:

**********************************************************************/

/**********************************************************************

**********************************************************************/

/********************************************************************

        Revision history:

**********************************************************************/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     nm   Initial release
/main/1+     lsz_h_001.main_1 sn Dynamic peer addition feature added
/main/3      ---     ng   lsz_h_001.main_2 1. Updated for S1AP Release 2.1
/main/4      ---     ajainx lsz_h_001.main_3 1. Updated for S1AP Release 2.2.
/main/5     lsz_h_001.main_4 pkaX Updated for S1AP Release 3.1.
/main/6      ---      lsz_h_001.main_5 va 1. Updated for S1AP Release 4.1.
*********************************************************************91*/
