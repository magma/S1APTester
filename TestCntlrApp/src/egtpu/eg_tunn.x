

/********************************************************************20**
  
     Name:     e-GTP layer
  
     Type:     C include file
  
     Desc:     Interface for tunnel management module.
  
     File:     eg_tunn.x
  
     Sid:      eg_tunn.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:52 2015
     
     Prg:      mm
  
*********************************************************************21*/

#ifndef __EG_TUNN_X__
#define __EG_TUNN_X__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**@file eg_tunn.x
    @brief Tunnel Management Module for EGTP
*/

/******************************************************************************
 *  Tunnel Manamgement local structures                                       *
 ******************************************************************************/
/**
  @ingroup TUNNMNGMT
    @struct _egTunnEvent
    @brief Enumerates Tunnel events
 */
typedef enum _egTunnEvent
{
   EG_TUN_EVENT_INCSESSREQ,  /**< A Create Session request is received */
   EG_TUN_EVENT_OUTSESSREQ,  /**< A Create Session Request is being sent */
   EG_TUN_EVENT_INCSESSRSP,  /**< A Create Session Response is received */
   EG_TUN_EVENT_OUTSESSRSP,  /**< A Create Session Response is being sent */
   EG_TUN_EVENT_ERR_IND,     /**< An Error Inidication is received from 
                                other module */
   EG_TUN_EVENT_INC_MSG,     /**< A GTP-C message is received on the tunnel */
   EG_TUN_EVENT_OUT_MSG,     /**< A GTP-C message is being sent on the tunnel */
   EG_TUN_EVENT_MAX
}EgTunnEvent;



#ifdef __cplusplus
}
#endif

#endif /* __EG_TUNN_X__ */


  
/********************************************************************30**
  
         End of file:     eg_tunn.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:52 2015
    
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
/main/1      ---      mm                1. Created for Initial Release 1.1
/main/2      ---      rsharon           1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
/main/3      eg004.201 magnihotri       1. Modified for eGTP-C PSF Upgarde:function prototype qualifier
                                           changed from PUBLIC to EXTERN
                                        2. Modified for eGTP-C PSF Upgarde:function prototype qualifier
                                           changed from PUBLIC to PRIVATE
                                        3. Modified for eGTP-C PSF Upgarde:function prototype qualifier
                                           changed from EXTERN to PUBLIC
*********************************************************************91*/
