


/**********************************************************************
 
    Name:  
 
    Type:  
 
    Desc:  
 
    File:  pj_tenb_stats.x 
 
    Sid:      pj_tenb_stats.x@@/main/tenb_5.0_RIB/3 - Tue Oct 27 14:21:17 2015
 
    Prg:   sm
 
**********************************************************************/
 
/** @file pj_tenb_stats.x
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
#ifndef __TENBSTATSL2X__
#define __TENBSTATSL2X__

#include "cm_tenb_stats.x"
#include "pj_tenb_stats.h"
 
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef TSInfL2CellStats TSL2CellStatsCb;

typedef struct tSL2UeStatsCb
{
   CmLList         lnk;
   U32             inUse;

   TSInfL2UeStats  stats;
}TSL2UeStatsCb;

EXTERN Void TSL2AllocStatsMem ARGS((
 Region region,
 Pool   pool
));
EXTERN TSL2UeStatsCb* TSL2AllocUeStatsBlk ARGS((
 U16   rnti
));
EXTERN Void TSL2DeallocUeStatsBlk ARGS((
 U16         rnti,
 TSL2UeStatsCb   *statsCb
));
EXTERN TSL2CellStatsCb* TSL2AllocCellStatsBlk ARGS((
 U32 cellId
));
EXTERN Void TSL2DeallocCellStatsBlk ARGS((
 U32 cellId
));
EXTERN Void TSL2SendStatsToApp ARGS((
 Pst    *pst,
 SuId   suId
));

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __TENBSTATSL2X__ */
#endif /* TENB_STATS */

/**********************************************************************
         End of file:     pj_tenb_stats.x@@/main/tenb_5.0_RIB/3 - Tue Oct 27 14:21:17 2015
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------

*********************************************************************91*/
