#include <stdlib.h>
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm_mblk.h"       /* common  */
#include "cm5.h"           /* common timer */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_inet.h"       /* common sockets */
#include "cm_dns.h"        /* common DNS Library */
#include "cm_tkns.h"
#include "ss_queue.h"      /* queues */
#include "ss_task.h"       /* tasking */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */
#include "rl_interface.h"
#include "rl_common.h"
#include "uet.h"
#include "nbt.h"
#include "lfw.h"
#include "fw.h"
#include "fw_tmr.h"

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_tpt.x"        /* common transport typedefs */
#include "cm_inet.x"       /* common sockets */
#include "cm_mblk.x"       /* common blk memory */
#include "cm_dns.x"        /* common DNS Library */
#include "cm_tkns.x"
#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */
#include "uet.x"
#include "nbt.x"
#include "fw_read_dflcfg.h"
#include "fw_api_int.x"
#include "fw.x"
#include "fw_tmr.x"
#include "fw_log.h"

EXTERN FwCb gfwCb;
char videoSrvrIp[20];

PUBLIC S8 *tfwAppCfgTagLst[MAX_TFW_CFG_PARAM] = {
   "TFW_IP_ADDR"
};

PUBLIC S8 *ueAppCfgTagLst[MAX_UE_APP_CFG_PARAM] = {
   "TRF_GEN_IP_ADDR",
   "NAS_PROC_GUARD_TIMER",
   "NUM_OF_UE"
};

PUBLIC S8 *nbAppCfgTagLst[MAX_NB_CFG_PARAM] = {
   "CELL_ID",
   "TAC",
   "ENB_IP_ADDR",
   "MME_ID",
   "MME_ADDR",
   "SCTP_IP_ADDR",
   "ENB_NAME",
   "PLMN_ID",
   "HEARTBEAT_INTERVAL",
   "RTO_INITIAL",
   "RTO_MIN",
   "RTO_MAX",
   "S1_PREP_TIMER_VAL",
   "S1_OVERALL_TIMER_VAL",
   "SCTP_UDP_SERVICE_TYPE",
   "INACTIVITY_TIMER_VAL",
   "MAX_EXPIRY",
   "S1_SETUP_TMR_VAL",
   "NO_OF_SCTP_IN_STREAMS",
   "NO_OF_SCTP_OUT_STREAMS",
   "UE_ETH_INTF",
   "VS_IP_ADDR"
};

PUBLIC S8 *ueCfgTagLst[MAX_UE_CFG_PARAM] = {
   "ALGO_TYPE",
   "OP_ID",
   "UE_NW_CAP",
   "AUTH_TYPE",
   "OP_KEY",
   "SHARED_KEY",
   "NAS_CYPH_CFG",
   "NAS_INT_PROT_CFG",
   "SRV_PLMN",
   "LAST_MCC",
   "LAST_MNC",
   "LAST_TAC",
   "MCC",
   "MNC",
   "MME_GRP_ID",
   "MME_CODE",
   "MTMSI",
   "PDN_TYPE",
   "PDN_APN",
   "UE_RAD_CAP_RRC_PDU_LEN",
   "UE_RAD_CAP_RRC_PDU"

};

/*
*        Fun:   tfwAppCfgGetTagNum
*
*        Desc:  Retrive the Tag number corresponds to the tag string.
*
*        Ret:   Void
* 
*        Notes: None
* 
*        File:  
* 
* 
*/
PRIVATE Void tfwAppCfgGetTagNum
(
 U8* tag, 
 U16* tagNum
)
{
   S16 loopCnt = 0; 
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);

   FW_LOG_ENTERFN(fwCb);

   for (loopCnt = 0; loopCnt < MAX_TFW_CFG_PARAM; loopCnt++)
   {
      if(tfwAppCfgTagLst[loopCnt] == NULLP)
      {
         break;
      }    
      if (0 == strcmp((S8 *)tag, tfwAppCfgTagLst[loopCnt]))
      {
         *tagNum = loopCnt;
         break;
      }
   } /*End of for */
   FW_LOG_EXITFNVOID(fwCb);
}

/*
*        Fun:   ueAppCfgGetTagNum
*
*        Desc:  Retrive the Tag number corresponds to the tag string.
*
*        Ret:   Void
* 
*        Notes: None
* 
*        File:  
* 
* 
*/
PRIVATE Void ueAppCfgGetTagNum
(
 U8* tag, 
 U16* tagNum
)
{
   S16 loopCnt = 0; 
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   for (loopCnt = 0; loopCnt < MAX_UE_APP_CFG_PARAM; loopCnt++)
   {
      if(ueAppCfgTagLst[loopCnt] == NULLP)
      {
         break;
      }    
      if (0 == strcmp((S8 *)tag,ueAppCfgTagLst[loopCnt]))
      {
         *tagNum = loopCnt;
         break;
      }
   } /*End of for */
   FW_LOG_EXITFNVOID(fwCb);
}

/*
*        Fun:   nbAppCfgGetTagNum
*
*        Desc:  Retrive the Tag number corresponds to the tag string.
*
*        Ret:   Void
* 
*        Notes: None
* 
*        File: 
* 
* 
*/
PRIVATE Void nbAppCfgGetTagNum
(
 U8* tag, 
 U16* tagNum
)
{
   S16 loopCnt = 0; 
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   for (loopCnt = 0; loopCnt < MAX_NB_CFG_PARAM; loopCnt++)
   {
      if(nbAppCfgTagLst[loopCnt] == NULLP)
      {
         break;
      }    
      if (0 == strcmp((S8 *)tag, nbAppCfgTagLst[loopCnt]))
      {
         *tagNum = loopCnt;
         break;
      }
   } /*End of for */
   FW_LOG_EXITFNVOID(fwCb);
}

/*
*        Fun:   ueCfgGetTagNum
*
*        Desc:  Retrive the Tag number corresponds to the tag string.
*
*        Ret:   Void
* 
*        Notes: None
* 
*        File:  
* 
*/
PRIVATE Void ueCfgGetTagNum
(
 U8* tag, 
 U16* tagNum
)
{
   S16 loopCnt = 0; 
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   for (loopCnt = 0; loopCnt < MAX_UE_CFG_PARAM; loopCnt++)
   {
      if(ueCfgTagLst[loopCnt] == NULLP)
      {
         break;
      }    
      if (0 == strcmp((S8 *)tag,ueCfgTagLst[loopCnt]))
      {
         *tagNum = loopCnt;
         break;
      }
   } /*End of for */
   FW_LOG_EXITFNVOID(fwCb);
}

PRIVATE S16 tfwAppReadConfigParams(Void)
{
   FILE  *fp;
   FwCb *fwCb = NULLP;
   U16 tagNum = 0;
   U8 tag[100];
   U8 tagVal[512];

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if((fp = fopen("tfwAppcfg.txt", "r")) == NULLP)
   {
      /* configuration file checking */
      FW_LOG_ERROR(fwCb, "FAILED to open the file tfwAppcfg.txt\n");
      FW_LOG_EXITFN(fwCb, RFAILED);
   } /* end of if statement */

   /* Read the file line by line */
   for(; !feof(fp);)
   {
      cmMemset(tagVal, 0, sizeof(tagVal));
      cmMemset(tag, 0, sizeof(tag));
      if (!fscanf(fp, "%100s %100s", tag, tagVal))
      {
         FW_LOG_ERROR(fwCb, "Error while reading configuration file");
         fclose(fp);
         FW_LOG_EXITFN(fwCb, RFAILED);
      }
      if(!strcmp("INVLD",(S8 *)tagVal))
         continue;

      if(!strcmp("CFGEND", (S8 *)tag))
         break;

      tfwAppCfgGetTagNum(tag, &tagNum);
      switch(tagNum)
      {
         case TFW_IP_ADDR:
            {
               FW_LOG_DEBUG(fwCb, "TFW_IP_ADDR: %s", tagVal);
               cmInetAddr((S8*)tagVal, &(fwCb->tfwCfgCb.tfwIpAddr));
               fwCb->tfwCfgCb.tfwIpAddr = CM_INET_HTON_U32(fwCb->tfwCfgCb.\
                     tfwIpAddr);
            }
            break;
      }/*End of switch */
      tagNum = MAX_TFW_CFG_PARAM;
   }/*End of For */
   FW_LOG_DEBUG(fwCb, "Read the tfwAppCfg.txt successfully");
   fclose(fp);

   FW_LOG_EXITFN(fwCb, ROK);
}

PRIVATE S16 ueAppReadConfigParams(Void)
{
   FILE  *fp;
   FwCb *fwCb = NULLP;
   U16 tagNum = 0;
   U8 tag[100];
   U8 tagVal[512];

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if((fp = fopen("ueAppCfg.txt", "r")) == NULL)
   {
      /* configuration file checking */
      FW_LOG_ERROR(fwCb, "FAILED to open the file ueAppConfig.txt");
      FW_LOG_EXITFN(fwCb, RFAILED);
   } /* end of if statement */

   /* Read the file line by line */
   for(; !feof(fp);)
   {
      cmMemset(tagVal, 0, sizeof(tagVal));
      cmMemset(tag, 0, sizeof(tag));
      if (!fscanf(fp, "%100s %100s", tag, tagVal))
      {
         FW_LOG_ERROR(fwCb, "Error in while reading configuration file");
         fclose(fp);
         FW_LOG_EXITFN(fwCb, RFAILED);
      }
      if (!strcmp("INVLD",(S8 *)tagVal))
         continue;

      if(!strcmp("CFGEND", (S8 *)tag))
         break;

      ueAppCfgGetTagNum(tag, &tagNum);
      switch(tagNum)
      {
         case TRF_GEN_IP_ADDR:
            {
               FW_LOG_DEBUG(fwCb, "TRF_GEN_IP_ADDR: %s", tagVal);
               cmInetAddr((S8*)tagVal,&(fwCb->ueAppCfgCb.trfGenIPAddr));
               fwCb->ueAppCfgCb.trfGenIPAddr = CM_INET_HTON_U32(fwCb->\
                     ueAppCfgCb.trfGenIPAddr);
            }
            break;
         case NAS_PROC_GUARD_TIMER:
            {
               FW_LOG_DEBUG(fwCb, "NAS_PROC_GUARD_TIMER: %s", tagVal);
               fwCb->ueAppCfgCb.NASProcGuardTimer = (U8)atoi((S8 *)tagVal);
            }
            break;
         case NUM_OF_UE:
            {
               FW_LOG_DEBUG(fwCb, "NUM_OF_UE: %s", tagVal);
               fwCb->ueAppCfgCb.numOfUE = (U8)atoi((S8 *)tagVal);
            }
            break;
      }/*End of switch */
      tagNum = MAX_UE_APP_CFG_PARAM;

   }/*End of For */
   FW_LOG_DEBUG(fwCb, "Read the ueAppCfg.txt successfully");
   fclose(fp);

   FW_LOG_EXITFN(fwCb, ROK);
}

PRIVATE S16 ueReadConfigParams(Void)
{
   FILE  *fp;
   FwCb *fwCb = NULLP;
   U16 tagNum = 0,counter = 0;
   U8 tag[100];
   U8 tagVal[512];
   U32 *tmpPtr = NULLP;
   /*U32 d = 0;*/

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if((fp = fopen("ueCfg.txt","r")) == NULL)
   {
      /* configuration file checking */
      FW_LOG_ERROR(fwCb, "FAILED to open the file ueCfg.txt");
      FW_LOG_EXITFN(fwCb, RFAILED);
   } /* end of if statement */

   /* Read the file line by line */
   for(; !feof(fp);)
   {
      cmMemset(tagVal, 0, sizeof(tagVal));
      cmMemset(tag, 0, sizeof(tag));
      if (!fscanf(fp, "%100s %100s",tag, tagVal))
      {
         FW_LOG_ERROR(fwCb, "Error in while reading configuration file");
         fclose(fp);
         FW_LOG_EXITFN(fwCb, RFAILED);
      }
      if (!strcmp("INVLD",(S8 *)tagVal))
         continue;

      if(!strcmp("CFGEND", (S8 *)tag))
         break;

      ueCfgGetTagNum(tag, &tagNum);
      switch (tagNum)
      {
         case NAS_CYPH_CFG:
            {
               FW_LOG_DEBUG(fwCb, "NAS_CYPH_CFG: %s", tagVal);
               fwCb->ueCfgCb.NASCyphCfg = (U8)atoi((S8 *)tagVal);
            }
            break;
         case NAS_INT_PROT_CFG:
            {
               FW_LOG_DEBUG(fwCb, "NAS_INT_PROT_CFG: %s", tagVal);
               fwCb->ueCfgCb.NASIntProtCfg = (U8)atoi((S8 *)tagVal);
            }
            break;
         case ALGO_TYPE:
            {
               FW_LOG_DEBUG(fwCb, "ALGO_TYPE: %s", tagVal);
               if(strcmp((S8*)tagVal,"AES") == 0)
                  fwCb->ueCfgCb.algoType= ALGO_TYPE_AES;
               else if(strcmp((S8*)tagVal,"SNOW3G") == 0)
                  fwCb->ueCfgCb.algoType = ALGO_TYPE_SNOW3G;
               else
                  printf("ALGO TYPE %s NOT SUPPORTED\n",tagVal);
            }
            break;
         case OP_ID:
            {
               FW_LOG_DEBUG(fwCb, "OP_ID: %s", tagVal);
               fwCb->ueCfgCb.opId = (U32)atoi((S8 *)tagVal);
            }
            break;
         case AUTH_TYPE:
            {
               FW_LOG_DEBUG(fwCb, "AUTH_TYPE: %s", tagVal);
               printf("tag: %s tagVal: %s\n",tag, tagVal);
               if(strcmp((S8*)tagVal,"XOR") == 0)
                  fwCb->ueCfgCb.authType = AUTH_TYPE_XOR;
               else if(strcmp((S8*)tagVal,"MILENAGE") == 0)
                  fwCb->ueCfgCb.authType = AUTH_TYPE_MILENAGE;
               else
                  printf("AUTHENTICATION TYPE %s NOT SUPPORTED\n",tagVal);
            }
            break;
         case OP_KEY:
            {
               FW_LOG_DEBUG(fwCb, "OP_KEY: %s", tagVal);
               fwCb->ueCfgCb.opKey[0] = (U32)atoi((S8*)tagVal);
               for(counter = 1; counter < MAX_OP_KEY_LEN; counter++){
                  fscanf(fp, "%u",&fwCb->ueCfgCb.opKey[counter]);
               }         
            }
            break;
         case SHARED_KEY:
            {
               FW_LOG_DEBUG(fwCb, "SHARED_KEY: %s", tagVal);
               fwCb->ueCfgCb.sharedKey[0] = (U16)atoi((S8*)tagVal);
               for(counter = 1; counter < MAX_SHARED_KEY_LEN; counter++){
                  fscanf(fp, "%u",&fwCb->ueCfgCb.sharedKey[counter]);
               }
            }
            break;
         case UE_NW_CAP:
            {
               cmMemset((U8 *)&fwCb->ueCfgCb.ueNwCap, 0, sizeof(UeNetwCap));
               FW_LOG_DEBUG(fwCb, "%s: %s", tag, tagVal);
               for( counter= 0 ;counter < MAX_UE_NW_CAP_SUPPORTED_ALGO;\
                      counter++)
               {
                  fscanf(fp, "%100s %100s", tag, tagVal);  
                  if( (strcmp((S8*)tag,"EEA0") == 0) &&\
                         (strcmp((S8*)tagVal,"TRUE") == 0))
                  {
                     fwCb->ueCfgCb.ueNwCap.eea0 = TRUE;
                  }
                  if( (strcmp((S8*)tag,"EEA1") == 0) &&\
                         (strcmp((S8*)tagVal,"TRUE") == 0))
                  {
                     fwCb->ueCfgCb.ueNwCap.eea1_128 = TRUE;
                  }
                  if( (strcmp((S8*)tag,"EEA2") == 0) &&\
                         (strcmp((S8*)tagVal,"TRUE") == 0))
                  {
                     fwCb->ueCfgCb.ueNwCap.eea2_128 = TRUE;
                  }
                  if( (strcmp((S8*)tag,"EIA0") == 0) &&\
                         (strcmp((S8*)tagVal,"TRUE") == 0))
                  {
                     fwCb->ueCfgCb.ueNwCap.eia0 = TRUE;
                  }
                  if( (strcmp((S8*)tag,"EIA1") == 0) &&\
                         (strcmp((S8*)tagVal,"TRUE") == 0))
                  {
                     fwCb->ueCfgCb.ueNwCap.eia1_128 = TRUE;
                  }
                  if( (strcmp((S8*)tag,"EIA2") == 0) &&\
                         (strcmp((S8*)tagVal,"TRUE") == 0))
                  {
                     fwCb->ueCfgCb.ueNwCap.eia2_128 = TRUE;
                  }
               }
            }
            break;
         case SRV_PLMN:
            {
               FW_LOG_DEBUG(fwCb, "SERVING PLMN: %s", tagVal);
               fwCb->ueCfgCb.srvPlmn[0] = (U8)atoi((S8*)tagVal);
               for(counter = 1; counter < 6 ; counter++)
               {
                  fscanf(fp, "%u",(U32*)&fwCb->ueCfgCb.srvPlmn[counter]);
               }
            }
            break;
         case LAST_MCC:
            {
               FW_LOG_DEBUG(fwCb, "LAST_MCC: %s", tagVal);
               strncpy((S8 *)fwCb->ueCfgCb.lastMcc, (S8 *)tagVal,3);
            }
            break;
         case LAST_MNC:
            {
               FW_LOG_DEBUG(fwCb, "LAST_MCC: %s", tagVal);
               strncpy((S8 *)fwCb->ueCfgCb.lastMnc, (S8 *)tagVal,3);
            }
            break;
         case LAST_TAC:
            {
               FW_LOG_DEBUG(fwCb, "LAST_TAC: %s", tagVal);
               fwCb->ueCfgCb.lastTac =(U16)atoi((S8 *)tagVal);
            }
            break;
         case MCC:
            {
               FW_LOG_DEBUG(fwCb, "MCC: %s", tagVal);
               strncpy((S8 *)fwCb->ueCfgCb.mcc, (S8 *)tagVal,3);
            }
            break;
         case MNC:
            {
               FW_LOG_DEBUG(fwCb, "MNC: %s", tagVal);
               strncpy((S8 *)fwCb->ueCfgCb.mnc, (S8 *)tagVal,3);
            }
            break;
         case MME_GRP_ID:
            {
               FW_LOG_DEBUG(fwCb, "MME_GRP_ID: %s", tagVal);
               fwCb->ueCfgCb.mmeGrpId = (U16)atoi((S8 *)tagVal);
            }
            break;
         case MME_CODE:
            {
               FW_LOG_DEBUG(fwCb, "MME_CODE: %s", tagVal);
               fwCb->ueCfgCb.mmeCode = (U8)atoi((S8 *)tagVal);
            }
            break;
         case MTMSI:
            {
               FW_LOG_DEBUG(fwCb, "MTMSI: %s", tagVal);
               fwCb->ueCfgCb.mTmsi = (U32)atoi((S8 *)tagVal);
            }
            break;
         case PDN_TYPE:
            {
               FW_LOG_DEBUG(fwCb, "PDN_TYPE: %s", tagVal);
               fwCb->ueCfgCb.pdnType = (U32)atoi((S8 *)tagVal);
            }
            break;
         case PDN_APN:
            {
               FW_LOG_DEBUG(fwCb, "PDN_APN: %s", tagVal);
               cmMemcpy(fwCb->ueCfgCb.pdnAPN, tagVal, APN_LEN);
            }
            break;
		case UE_RAD_CAP_RRC_PDU_LEN:
            {
               FW_LOG_DEBUG(fwCb, "UE_RAD_CAP_RRC_PDU_LEN: %s", tagVal);
               fwCb->ueCfgCb.ueRadCapRrcPduLen = (U16)atoi((S8 *)tagVal);
            }
            break;
      case UE_RAD_CAP_RRC_PDU:
            {
               FW_LOG_DEBUG(fwCb, "UE_RAD_CAP_RRC_PDU: %s", tagVal);
               if(fwCb->ueCfgCb.ueRadCapRrcPduLen <= 0)
               {
                  FW_LOG_ERROR(fwCb, "Invalid PDU Length");
                  fclose(fp);
                  FW_LOG_EXITFN(fwCb, RFAILED);
               }

               if(SGetSBuf(fwCb->init.region, fwCb->init.pool,
                        (Data **)&fwCb->ueCfgCb.ueRadCapRrcPdu,
                        (Size)((fwCb->ueCfgCb.ueRadCapRrcPduLen + 1) * sizeof(U32))) == ROK)
               {
                  cmMemset((U8 *)fwCb->ueCfgCb.ueRadCapRrcPdu, 0,
                        ((fwCb->ueCfgCb.ueRadCapRrcPduLen + 1) * sizeof(U32)));
               }
               else
               {
                  FW_LOG_ERROR(fwCb, "Failed to allocate memory");
                  fclose(fp);
                  FW_LOG_EXITFN(fwCb, RFAILED);
               }
               *(fwCb->ueCfgCb.ueRadCapRrcPdu) = atoi((S8 *)tagVal);
               tmpPtr = fwCb->ueCfgCb.ueRadCapRrcPdu + 1; 
               for(counter = 0; counter < fwCb->ueCfgCb.ueRadCapRrcPduLen;
                     counter++)
               {
                  fscanf(fp, "%x", (U32 *)tmpPtr);
                  tmpPtr = tmpPtr + 1;
               }
            }
            break;
      }/*End of switch */
      tagNum = MAX_UE_CFG_PARAM;
   }/*End of For */
   FW_LOG_DEBUG(fwCb, "Read the tfwAppCfg.txt successfully");
   fclose(fp);

   FW_LOG_EXITFN(fwCb, ROK);
}

PRIVATE S16 nbAppReadConfigParams(Void)
{
   FILE  *fp;
   FwCb *fwCb = NULLP;
   U16 tagNum = 0;
   U16 cnt = 0;
   U8 tag[100];
   U8 tagVal[512];

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if((fp = fopen("nbAppCfg.txt", "r")) == NULLP)
   {
      /* configuration file checking */
      FW_LOG_ERROR(fwCb, "FAILED to open the file nbAppcfg.txt");
      FW_LOG_EXITFN(fwCb, RFAILED);
   } /* end of if statement */

   /* Read the file line by line */
   for(; !feof(fp);)
   {
      cmMemset(tagVal, 0, sizeof(tagVal));
      cmMemset(tag, 0, sizeof(tag));
      if (!fscanf(fp, "%100s %100s", tag, tagVal))
      {
         FW_LOG_ERROR(fwCb, " Error in while reading configuration file \n");
         fclose(fp);
         FW_LOG_EXITFN(fwCb, RFAILED);
      }
      if (!strcmp("INVLD",(S8 *)tagVal))
      {
         continue;
      }

      if (!strcmp("CFGEND", (S8 *)tag))
      {
         break;
      }

      nbAppCfgGetTagNum(tag, &tagNum);
      switch (tagNum)
      {
         case CELL_ID:
            {
               FW_LOG_DEBUG(fwCb, "CELL_ID: %s", tagVal);
               fwCb->nbAppCfgCb.cellId = atoi((S8 *)tagVal);
            }
            break;
         case TAC:
            {
               FW_LOG_DEBUG(fwCb, "TAC: %s", tagVal);
               fwCb->nbAppCfgCb.tac = (U16)atoi((S8 *)tagVal);
            }
            break;
         case ENB_IP_ADDR:
            {
               FW_LOG_DEBUG(fwCb, "ENB_IP_ADDR: %s", tagVal);
               cmInetAddr((S8*)tagVal,&(fwCb->nbAppCfgCb.enbIPAddr));
               fwCb->nbAppCfgCb.enbIPAddr = CM_INET_HTON_U32(fwCb->nbAppCfgCb.\
                     enbIPAddr);
            }
            break;
         case MME_ID:
            {
               FW_LOG_DEBUG(fwCb, "MME_ID: %s", tagVal);
               fwCb->nbAppCfgCb.mmeId = atoi((S8 *)tagVal);
            }
            break;
         case MME_ADDR:
            {
               FW_LOG_DEBUG(fwCb, "MME_ADDR: %s", tagVal);
               cmInetAddr((S8*)tagVal,&(fwCb->nbAppCfgCb.mmeAddr));
               fwCb->nbAppCfgCb.mmeAddr = CM_INET_HTON_U32(fwCb->nbAppCfgCb.\
                     mmeAddr);
            }
            break;
         case SCTP_IP_ADDR:
            {
               FW_LOG_DEBUG(fwCb, "SCTP_IP_ADDR: %s", tagVal);
               cmInetAddr((S8*)tagVal, &(fwCb->nbAppCfgCb.sctpIPAddr));
               fwCb->nbAppCfgCb.sctpIPAddr = CM_INET_HTON_U32(fwCb->\
                     nbAppCfgCb.sctpIPAddr);
            }
            break;
         case ENB_NAME:
            {
               FW_LOG_DEBUG(fwCb, "ENB_NAME: %s", tagVal);
               cmMemcpy(fwCb->nbAppCfgCb.enbName,tagVal,MAX_ENB_NAME_LEN);
            }
            break;
         case PLMN_ID:
            {
               FW_LOG_DEBUG(fwCb, "PLMN_ID: %s", tagVal);
               cmMemcpy(fwCb->nbAppCfgCb.plmnId,tagVal, 6);
               /*---------NEED to INITIALIZE------------*/
            }
            break;
         case HEARTBEAT_INTERVAL:
            {
               FW_LOG_DEBUG(fwCb, "HEARTBEAT_INTERVAL: %s", tagVal);
               fwCb->nbAppCfgCb.heartBeatInterval = atoi((S8 *)tagVal);
            }
            break;
         case RTO_INITIAL:
            {
               FW_LOG_DEBUG(fwCb, "RTO_INITIAL: %s", tagVal);
               fwCb->nbAppCfgCb.rtoInitial = atoi((S8 *)tagVal);
            }
            break;
         case RTO_MIN:
            {
               FW_LOG_DEBUG(fwCb, "RTO_MIN: %s", tagVal);
               fwCb->nbAppCfgCb.rtoMin = atoi((S8 *)tagVal);
            }
            break;
         case RTO_MAX:
            {
               FW_LOG_DEBUG(fwCb, "RTO_MAX: %s", tagVal);
               fwCb->nbAppCfgCb.rtoMax = atoi((S8 *)tagVal);
            }
            break;
         case S1_PREP_TIMER_VAL:
            {
               FW_LOG_DEBUG(fwCb, "S1_PREP_TIMER_VAL: %s", tagVal);
               fwCb->nbAppCfgCb.s1PrepTimerVal = atoi((S8 *)tagVal);
            }
            break;
         case S1_OVERALL_TIMER_VAL:
            {
               FW_LOG_DEBUG(fwCb, "S1_OVERALL_TIMER_VAL: %s", tagVal);
               fwCb->nbAppCfgCb.s1OverallTimerVal = atoi((S8 *)tagVal);
            }
            break;
         case SCTP_UDP_SERVICE_TYPE:
            {
               FW_LOG_DEBUG(fwCb, "SCTP_UDP_SERVICE_TYPE: %s", tagVal);
               fwCb->nbAppCfgCb.sctpUdpServiceType = (U8)atoi((S8 *)tagVal);
            }
            break;
         case INACTIVITY_TIMER_VAL:
            {
               FW_LOG_DEBUG(fwCb, "INACTIVITY_TIMER_VAL: %s", tagVal);
               fwCb->nbAppCfgCb.inactvTmrVal  = atoi((S8 *)tagVal);
            }
            break;
         case MAX_EXPIRY:
            {
               FW_LOG_DEBUG(fwCb, "MAX_EXPIRY: %s", tagVal);
               fwCb->nbAppCfgCb.maxExpires = (U8)atoi((S8 *)tagVal);
            }
            break;
         case S1_SETUP_TMR_VAL:
            {
               FW_LOG_DEBUG(fwCb, "S1_SETUP_TMR_VAL: %s", tagVal);
               fwCb->nbAppCfgCb.s1SetupTmr = atoi((S8 *)tagVal);
            }
            break;
         case NO_OF_SCTP_IN_STREAMS:
            {
               FW_LOG_DEBUG(fwCb, "NO_OF_SCTP_IN_STREAMS: %s", tagVal);
               fwCb->nbAppCfgCb.noOfSctpInStreams = atoi((S8 *)tagVal);
            }
            break;
         case NO_OF_SCTP_OUT_STREAMS:
            {
               FW_LOG_DEBUG(fwCb, "NO_OF_SCTP_OUT_STREAMS: %s", tagVal);
               fwCb->nbAppCfgCb.noOfSctpOutStreams = atoi((S8 *)tagVal);
            }
            break;
         case UE_ETH_INTF:
            {
               FW_LOG_DEBUG(fwCb, "UE_ETH_INTF: %s", tagVal);
               cnt = 0;
               while(tagVal[cnt])
               {
                  fwCb->nbAppCfgCb.ueEthIntf[cnt] = tagVal[cnt];
                  cnt++;
               }
               fwCb->nbAppCfgCb.ueEthIntf[cnt] = '\0';
            }
            break;
         case VS_IP_ADDR:
            {
               FW_LOG_DEBUG(fwCb, "VS_IP_ADDR", tagVal);
               cnt = 0;
               while(tagVal[cnt])
               {
                  videoSrvrIp[cnt] = tagVal[cnt];
                  cnt++;
               }
               videoSrvrIp[cnt] = '\0';
            }
            break;
         default:
            {
               FW_LOG_ERROR(fwCb,"INVALID ENTRY");
            }
            break;
      }/*End of switch */
      tagNum = MAX_NB_CFG_PARAM;
   }/*End of For */
   FW_LOG_DEBUG(fwCb, "Read the nbAppCfg.txt successfully");
   fclose(fp);

   RETVALUE(ROK);
}

PUBLIC Void readDfltCfgs(Void)
{
   FwCb *fwCb = NULLP;
   FW_GET_CB(fwCb);

   FW_LOG_ENTERFN(fwCb);

   if (tfwAppReadConfigParams() == RFAILED)
   {
      FW_LOG_ERROR(fwCb, "Error in reading the TFW configs");
      FW_LOG_EXITFNVOID(fwCb);
   }
   if (ueAppReadConfigParams() == RFAILED)
   {
      FW_LOG_ERROR(fwCb, "Error in reading the UE APP configs");
      FW_LOG_EXITFNVOID(fwCb);
   }
   if (ueReadConfigParams() == RFAILED)
   {
      FW_LOG_ERROR(fwCb, "Error in reading the UE configs");
      FW_LOG_EXITFNVOID(fwCb);
   }
   if (nbAppReadConfigParams() == RFAILED)
   {
      FW_LOG_ERROR(fwCb, "Error in reading the NB APP configs");
      FW_LOG_EXITFNVOID(fwCb);
   }

   FW_LOG_EXITFNVOID(fwCb);
}
