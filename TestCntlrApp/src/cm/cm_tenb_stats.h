


/**********************************************************************
 
    Name:  
 
    Type:  
 
    Desc:  
 
    File:  cm_tenb_stats.h
 
    Sid:      cm_tenb_stats.h@@/main/tenb_5.0_RIB/3 - Tue Oct 27 14:21:19 2015
 
    Prg:   sm
 
**********************************************************************/
 
/** @file cm_tenb_stats.h
@brief This file contains .
*/

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*
*/
 
#ifdef TENB_STATS
#ifndef __TENBSTATSINFH__
#define __TENBSTATSINFH__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TENBSTATSINIT       0x7F

#ifdef BRDCM
#define CL_DSTENT_SELECTOR 0
#define STATS_SRCPROCID 1 
#define STATS_DSTPROCID 1 
#define STATS_DSTENT    ENTPJ
#define STATS_DSTINST   0        /* PDCP UL */
#else /* BRDCM */
#ifdef MSPD
#define CL_DSTENT_SELECTOR 0
#ifdef L2_L3_SPLIT
#define STATS_SRCPROCID 1
#define STATS_DSTPROCID 1 
#define STATS_DSTENT    ENTKW
#else
#define STATS_SRCPROCID 100
#define STATS_DSTPROCID 100 
#define STATS_DSTENT    ENTKW
#endif /* L2_L3_SPLIT */

#define STATS_DSTINST   0        /* PDCP UL */
#else /* MSPD */
#define CL_DSTENT_SELECTOR 0
#define STATS_SRCPROCID 0
#define STATS_DSTPROCID 0 
#define STATS_DSTENT    ENTPJ
#define STATS_DSTINST   0        /* PDCP UL */
#endif /* MSPD */
#endif

#define STATS_SRCENT    ENTTF

#define EVTTENBL2CELLSTATS  0xF1
#define EVTTENBL2UESTATS    0xF2

#endif
#endif /* TENB_STATS */
/**********************************************************************
         End of file:     cm_tenb_stats.h@@/main/tenb_5.0_RIB/3 - Tue Oct 27 14:21:19 2015
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------

*********************************************************************91*/
