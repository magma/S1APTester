

/********************************************************************20**

     Name:    EGTP - 

     Type:    C source file

     Desc:    

     File:    eg_edm.x

     Sid:      eg_edm.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:44 2015

     Prg:    ad  

*********************************************************************21*/

#ifndef __EGEDMX__
#define __EGEDMX__

#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus  */ 

/** @file eg_edm.x
    @brief Encoder-Decoder Module(eg_edm.x)
 */

   /**@struct _egIeEntry
      @brief GTP IE Entry Control Block */
typedef struct _egIeEntry
{
  U8                   ieCode;                    /**< IE Code */
  U8                   dataType;                  /**<  Data type of IE */
  U16                   minLen;                    /**< Min Length */
  U16                   maxLen;                    /**< Max Length */
#ifdef EGTP_U
  Bool                 tvType;                    /**< Is IE type TV? */
#endif
}EgIeEntry;

   

#ifdef EGTP_U
typedef struct _egUIeProperties EgUIeProperties;

/**@struct _egUIeProperties
   @brief Properties of IE */
struct _egUIeProperties
{
   U8                  ieType;                     /**< IE Code    */
   U8                  ieClass;                    /**< IE Class MANDATORY/OPTIONAL */ 
};

/**@struct _egUMsgEntry
 * @brief Message Entry in the DB */
typedef struct _egUMsgEntry
{
   U8                  msgType;                                   /**< Message Code  */
   U8                  nmbIe;                                   /**< Number of IE Properties */
   U8                  nmbMandIe;                           /**< Number of Mandatory IEs */
   EgUIeProperties     ieProperties[EGU_MAX_IES_PER_MSG];         /**< IE Properties List  */
}EgUMsgEntry;

/**@struct _egUGmCb
   @brief MSG Control Block */
typedef struct _egUGmCb
{
   U16                    posIdx[EGU_MAX_MSG];  /**< Position Index */
   EgUMsgEntry           gmEntry[EGU_SUP_MSGS]; /**< Message Entry */
}EgUGmCb;

/**@struct _egUIeCb
   @brief IE Contrl Block */
typedef struct _egUIeCb
{
   U16        posIdx[EGU_MAX_IE];    /**< Position Index */
   EgIeEntry ieEntry[EGU_SUP_IES];          /**< List of the IE Entries */
}EgUIeCb;

/**@struct _egUEdmCb
   @brief GTP-U EDM Control Block */
typedef struct _egUEdmCb
{
   EgUIeCb       egIeCb;                       /**< IE Control Block */
   EgUGmCb       egMsgCb;      /**< Msg Control Block */
}EgUEdmCb;

#endif /* End of EGTP_U */



#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* __LEGX__ */

/********************************************************************30**

         End of file:     eg_edm.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:44 2015

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
----------- -------- ---- -----------------------------------------------
/main/1      ---      ad                1. Created for Initial Release 1.1
/main/2      ---      kchaitanya        1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
*********************************************************************91*/


