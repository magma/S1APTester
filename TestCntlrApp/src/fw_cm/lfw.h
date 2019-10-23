/**
 * @define used by Stack manager
 */
#define SM_INST_ID      0 /**< Stack Manager Instance Id */
#define FW_INST_ID      0 /**< TFW App Instance Id */
#define UE_INST_ID      0 /**< TFW App Instance Id */
#define NB_INST_ID      0 /**< TFW App Instance Id */

#define LFW_SEL_LWLC        0

#define LFW_CFG_READ    0 /**< General configuration */
#define LFW_CFG_PEER    1 /**< Peer Configuration */
#define LFW_CFG_DBG     2 /**< Debug Configuration */

#define LFW_CNTRL_GEN   3 /**< General control */
#define LFW_CNTRL_LOGIN 4 /**< Peer Control */

/** Defines Logging Levels */
#define LFW_LOGLVL_DISABLE  0
#define LFW_LOGLVL_FATAL    1
#define LFW_LOGLVL_ERROR    2
#define LFW_LOGLVL_WARN     3
#define LFW_LOGLVL_INFO     4
#define LFW_LOGLVL_DEBUG    5
#define LFW_LOGLVL_TRACE    6
#define LFW_ERR_INV_LOG_LVL 7
#define LFW_LOGLVL_ALL   LFW_LOGLVL_TRACE

#define LFW_MNGMT_CFG_READ_REQ       1
#define LFW_MNGMT_CFG_READ_CFM       2
#define LFW_MNGMT_CNTRL_REQ          3
#define LFW_MNGMT_CNTRL_CFM          4

#define LUE_MNGMT_CFG_REQ       1
#define LUE_MNGMT_CFG_CFM       2
#define LUE_MNGMT_CNTRL_REQ     3
#define LUE_MNGMT_CNTRL_CFM     4
