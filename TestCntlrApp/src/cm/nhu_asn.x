/**********************************************************************

     Name:     LTE RRC Layer

     Type:     C include file

     Desc:     Message structures required by RRC

     File:     nhu_asn.x

     Sid:      nhu_asn.x@@/main/3 - Thu Jun 30 17:23:38 2011

     Prg:      pparande

**********************************************************************/

#ifndef __NHUASNX__
#define __NHUASNX__ 

/* Element ----- phich-Duration ------- */
typedef enum enumNhuPHICH_Configphich_Duration
{
	NhuPHICH_Configphich_DurationnormalEnum,
	NhuPHICH_Configphich_DurationextendedEnum
} EnumNhuPHICH_Configphich_Duration;
typedef TknU32 NhuPHICH_Configphich_Duration;

/* Element ----- phich-Resource ------- */
typedef enum enumNhuPHICH_Configphich_Resource
{
	NhuPHICH_Configphich_ResourceoneSixthEnum,
	NhuPHICH_Configphich_ResourcehalfEnum,
	NhuPHICH_Configphich_ResourceoneEnum,
	NhuPHICH_Configphich_ResourcetwoEnum
} EnumNhuPHICH_Configphich_Resource;
typedef TknU32 NhuPHICH_Configphich_Resource;

typedef struct NhuPHICH_Config
{
	TknPres pres;
	NhuPHICH_Configphich_Duration phich_Duration;
	NhuPHICH_Configphich_Resource phich_Resource;
} NhuPHICH_Config;

/* Element ----- dl-Bandwidth ------- */
typedef enum enumNhuMasterInfoBlockdl_Bandwidth
{
	NhuMasterInfoBlockdl_Bandwidthn6Enum,
	NhuMasterInfoBlockdl_Bandwidthn15Enum,
	NhuMasterInfoBlockdl_Bandwidthn25Enum,
	NhuMasterInfoBlockdl_Bandwidthn50Enum,
	NhuMasterInfoBlockdl_Bandwidthn75Enum,
	NhuMasterInfoBlockdl_Bandwidthn100Enum
} EnumNhuMasterInfoBlockdl_Bandwidth;
typedef TknU32 NhuMasterInfoBlockdl_Bandwidth;

/* Element ---------- systemFrameNumber ----------- */
typedef TknStrBSXL NhuMasterInfoBlocksystemFrameNumber;
/* Element ---------- spare ----------- */
typedef TknStrBSXL NhuMasterInfoBlockspare;
typedef struct NhuMasterInfoBlock
{
	TknPres pres;
	NhuMasterInfoBlockdl_Bandwidth dl_Bandwidth;
	NhuPHICH_Config phich_Config;
	NhuMasterInfoBlocksystemFrameNumber systemFrameNumber;
	NhuMasterInfoBlockspare spare;
} NhuMasterInfoBlock;

/* Element ------------- BCCH-BCH-MessageType ------------ */
typedef NhuMasterInfoBlock  NhuBCCH_BCH_MsgTyp;
typedef struct NhuBCCH_BCH_Msg
{
	TknPres pres;
	NhuBCCH_BCH_MsgTyp message;
} NhuBCCH_BCH_Msg;

/* Element ----- ac-BarringFactor ------- */
typedef enum enumNhuAC_BarringConfigac_BarringFactor
{
	NhuAC_BarringConfigac_BarringFactorp00Enum,
	NhuAC_BarringConfigac_BarringFactorp05Enum,
	NhuAC_BarringConfigac_BarringFactorp10Enum,
	NhuAC_BarringConfigac_BarringFactorp15Enum,
	NhuAC_BarringConfigac_BarringFactorp20Enum,
	NhuAC_BarringConfigac_BarringFactorp25Enum,
	NhuAC_BarringConfigac_BarringFactorp30Enum,
	NhuAC_BarringConfigac_BarringFactorp40Enum,
	NhuAC_BarringConfigac_BarringFactorp50Enum,
	NhuAC_BarringConfigac_BarringFactorp60Enum,
	NhuAC_BarringConfigac_BarringFactorp70Enum,
	NhuAC_BarringConfigac_BarringFactorp75Enum,
	NhuAC_BarringConfigac_BarringFactorp80Enum,
	NhuAC_BarringConfigac_BarringFactorp85Enum,
	NhuAC_BarringConfigac_BarringFactorp90Enum,
	NhuAC_BarringConfigac_BarringFactorp95Enum
} EnumNhuAC_BarringConfigac_BarringFactor;
typedef TknU32 NhuAC_BarringConfigac_BarringFactor;

/* Element ----- ac-BarringTime ------- */
typedef enum enumNhuAC_BarringConfigac_BarringTime
{
	NhuAC_BarringConfigac_BarringTimes4Enum,
	NhuAC_BarringConfigac_BarringTimes8Enum,
	NhuAC_BarringConfigac_BarringTimes16Enum,
	NhuAC_BarringConfigac_BarringTimes32Enum,
	NhuAC_BarringConfigac_BarringTimes64Enum,
	NhuAC_BarringConfigac_BarringTimes128Enum,
	NhuAC_BarringConfigac_BarringTimes256Enum,
	NhuAC_BarringConfigac_BarringTimes512Enum
} EnumNhuAC_BarringConfigac_BarringTime;
typedef TknU32 NhuAC_BarringConfigac_BarringTime;

/* Element ---------- ac-BarringForSpecialAC ----------- */
typedef TknStrBSXL NhuAC_BarringConfigac_BarringForSpecialAC;
typedef struct NhuAC_BarringConfig
{
	TknPres pres;
	NhuAC_BarringConfigac_BarringFactor ac_BarringFactor;
	NhuAC_BarringConfigac_BarringTime ac_BarringTime;
	NhuAC_BarringConfigac_BarringForSpecialAC ac_BarringForSpecialAC;
} NhuAC_BarringConfig;

/* Element ----- powerRampingStep ------- */
typedef enum enumNhuPowerRampingParamspowerRampingStep
{
	NhuPowerRampingParamspowerRampingStepdB0Enum,
	NhuPowerRampingParamspowerRampingStepdB2Enum,
	NhuPowerRampingParamspowerRampingStepdB4Enum,
	NhuPowerRampingParamspowerRampingStepdB6Enum
} EnumNhuPowerRampingParamspowerRampingStep;
typedef TknU32 NhuPowerRampingParamspowerRampingStep;

/* Element ----- preambleInitialReceivedTargetPower ------- */
typedef enum enumNhuPowerRampingParamspreambleInitReceivedTgtPower
{
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_120Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_118Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_116Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_114Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_112Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_110Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_108Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_106Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_104Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_102Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_100Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_98Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_96Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_94Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_92Enum,
	NhuPowerRampingParamspreambleInitReceivedTgtPowerdBm_90Enum
} EnumNhuPowerRampingParamspreambleInitReceivedTgtPower;
typedef TknU32 NhuPowerRampingParamspreambleInitReceivedTgtPower;

typedef struct NhuPowerRampingParams
{
	TknPres pres;
	NhuPowerRampingParamspowerRampingStep powerRampingStep;
	NhuPowerRampingParamspreambleInitReceivedTgtPower preambleInitReceivedTgtPower;
} NhuPowerRampingParams;

/* Element ----- PreambleTransMax ------- */
typedef enum enumNhuPreambleTransMax
{
	NhuPreambleTransMaxn3Enum,
	NhuPreambleTransMaxn4Enum,
	NhuPreambleTransMaxn5Enum,
	NhuPreambleTransMaxn6Enum,
	NhuPreambleTransMaxn7Enum,
	NhuPreambleTransMaxn8Enum,
	NhuPreambleTransMaxn10Enum,
	NhuPreambleTransMaxn20Enum,
	NhuPreambleTransMaxn50Enum,
	NhuPreambleTransMaxn100Enum,
	NhuPreambleTransMaxn200Enum
} EnumNhuPreambleTransMax;
typedef TknU32 NhuPreambleTransMax;

/* Element ----- numberOfRA-Preambles ------- */
typedef enum enumNhuRACH_ConfigCmnpreambleInfonumberOfRA_Preambles
{
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn4Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn8Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn12Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn16Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn20Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn24Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn28Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn32Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn36Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn40Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn44Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn48Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn52Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn56Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn60Enum,
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn64Enum
} EnumNhuRACH_ConfigCmnpreambleInfonumberOfRA_Preambles;
typedef TknU32 NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preambles;

/* Element ----- sizeOfRA-PreamblesGroupA ------- */
typedef enum enumNhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupA
{
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn4Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn8Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn12Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn16Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn20Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn24Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn28Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn32Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn36Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn40Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn44Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn48Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn52Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn56Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupAn60Enum
} EnumNhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupA;
typedef TknU32 NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupA;

/* Element ----- messageSizeGroupA ------- */
typedef enum enumNhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessageSizeGroupA
{
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessageSizeGroupAb56Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessageSizeGroupAb144Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessageSizeGroupAb208Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessageSizeGroupAb256Enum
} EnumNhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessageSizeGroupA;
typedef TknU32 NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessageSizeGroupA;

/* Element ----- messagePowerOffsetGroupB ------- */
typedef enum enumNhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessagePowerOffsetGroupB
{
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessagePowerOffsetGroupBminusinfinityEnum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessagePowerOffsetGroupBdB0Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessagePowerOffsetGroupBdB5Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessagePowerOffsetGroupBdB8Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessagePowerOffsetGroupBdB10Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessagePowerOffsetGroupBdB12Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessagePowerOffsetGroupBdB15Enum,
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessagePowerOffsetGroupBdB18Enum
} EnumNhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessagePowerOffsetGroupB;
typedef TknU32 NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessagePowerOffsetGroupB;

typedef struct NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfig
{
	TknPres pres;
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigsizeOfRA_PreamblesGroupA sizeOfRA_PreamblesGroupA;
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessageSizeGroupA messageSizeGroupA;
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfigmessagePowerOffsetGroupB messagePowerOffsetGroupB;
} NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfig;

typedef struct NhuRACH_ConfigCmnpreambleInfo
{
	TknPres pres;
	NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preambles numberOfRA_Preambles;
	NhuRACH_ConfigCmnpreambleInfopreamblesGroupAConfig preamblesGroupAConfig;
} NhuRACH_ConfigCmnpreambleInfo;

/* Element ----- ra-ResponseWindowSize ------- */
typedef enum enumNhuRACH_ConfigCmnra_SupervisionInfora_RspWindowSize
{
	NhuRACH_ConfigCmnra_SupervisionInfora_RspWindowSizesf2Enum,
	NhuRACH_ConfigCmnra_SupervisionInfora_RspWindowSizesf3Enum,
	NhuRACH_ConfigCmnra_SupervisionInfora_RspWindowSizesf4Enum,
	NhuRACH_ConfigCmnra_SupervisionInfora_RspWindowSizesf5Enum,
	NhuRACH_ConfigCmnra_SupervisionInfora_RspWindowSizesf6Enum,
	NhuRACH_ConfigCmnra_SupervisionInfora_RspWindowSizesf7Enum,
	NhuRACH_ConfigCmnra_SupervisionInfora_RspWindowSizesf8Enum,
	NhuRACH_ConfigCmnra_SupervisionInfora_RspWindowSizesf10Enum
} EnumNhuRACH_ConfigCmnra_SupervisionInfora_RspWindowSize;
typedef TknU32 NhuRACH_ConfigCmnra_SupervisionInfora_RspWindowSize;

/* Element ----- mac-ContentionResolutionTimer ------- */
typedef enum enumNhuRACH_ConfigCmnra_SupervisionInfomac_ContentionResolutionTimer
{
	NhuRACH_ConfigCmnra_SupervisionInfomac_ContentionResolutionTimersf8Enum,
	NhuRACH_ConfigCmnra_SupervisionInfomac_ContentionResolutionTimersf16Enum,
	NhuRACH_ConfigCmnra_SupervisionInfomac_ContentionResolutionTimersf24Enum,
	NhuRACH_ConfigCmnra_SupervisionInfomac_ContentionResolutionTimersf32Enum,
	NhuRACH_ConfigCmnra_SupervisionInfomac_ContentionResolutionTimersf40Enum,
	NhuRACH_ConfigCmnra_SupervisionInfomac_ContentionResolutionTimersf48Enum,
	NhuRACH_ConfigCmnra_SupervisionInfomac_ContentionResolutionTimersf56Enum,
	NhuRACH_ConfigCmnra_SupervisionInfomac_ContentionResolutionTimersf64Enum
} EnumNhuRACH_ConfigCmnra_SupervisionInfomac_ContentionResolutionTimer;
typedef TknU32 NhuRACH_ConfigCmnra_SupervisionInfomac_ContentionResolutionTimer;

typedef struct NhuRACH_ConfigCmnra_SupervisionInfo
{
	TknPres pres;
	NhuPreambleTransMax preambleTransMax;
	NhuRACH_ConfigCmnra_SupervisionInfora_RspWindowSize ra_RspWindowSize;
	NhuRACH_ConfigCmnra_SupervisionInfomac_ContentionResolutionTimer mac_ContentionResolutionTimer;
} NhuRACH_ConfigCmnra_SupervisionInfo;

/* Element ----- maxHARQ-Msg3Tx ------- */
typedef TknU32 NhuRACH_ConfigCmnmaxHARQ_Msg3Tx;

typedef struct NhuRACH_ConfigCmn
{
	TknPres pres;
	NhuRACH_ConfigCmnpreambleInfo preambleInfo;
	NhuPowerRampingParams powerRampingParams;
	NhuRACH_ConfigCmnra_SupervisionInfo ra_SupervisionInfo;
	NhuRACH_ConfigCmnmaxHARQ_Msg3Tx maxHARQ_Msg3Tx;
} NhuRACH_ConfigCmn;

/* Element ----- modificationPeriodCoeff ------- */
typedef enum enumNhuBCCH_ConfigmodificationPeriodCoeff
{
	NhuBCCH_ConfigmodificationPeriodCoeffn2Enum,
	NhuBCCH_ConfigmodificationPeriodCoeffn4Enum,
	NhuBCCH_ConfigmodificationPeriodCoeffn8Enum,
	NhuBCCH_ConfigmodificationPeriodCoeffn16Enum
} EnumNhuBCCH_ConfigmodificationPeriodCoeff;
typedef TknU32 NhuBCCH_ConfigmodificationPeriodCoeff;

typedef struct NhuBCCH_Config
{
	TknPres pres;
	NhuBCCH_ConfigmodificationPeriodCoeff modificationPeriodCoeff;
} NhuBCCH_Config;

/* Element ----- defaultPagingCycle ------- */
typedef enum enumNhuPCCH_ConfigdefaultPagCycle
{
	NhuPCCH_ConfigdefaultPagCyclerf32Enum,
	NhuPCCH_ConfigdefaultPagCyclerf64Enum,
	NhuPCCH_ConfigdefaultPagCyclerf128Enum,
	NhuPCCH_ConfigdefaultPagCyclerf256Enum
} EnumNhuPCCH_ConfigdefaultPagCycle;
typedef TknU32 NhuPCCH_ConfigdefaultPagCycle;

/* Element ----- nB ------- */
typedef enum enumNhuPCCH_ConfignB
{
	NhuPCCH_ConfignBfourTEnum,
	NhuPCCH_ConfignBtwoTEnum,
	NhuPCCH_ConfignBoneTEnum,
	NhuPCCH_ConfignBhalfTEnum,
	NhuPCCH_ConfignBquarterTEnum,
	NhuPCCH_ConfignBoneEighthTEnum,
	NhuPCCH_ConfignBoneSixteenthTEnum,
	NhuPCCH_ConfignBoneThirtySecondTEnum
} EnumNhuPCCH_ConfignB;
typedef TknU32 NhuPCCH_ConfignB;

typedef struct NhuPCCH_Config
{
	TknPres pres;
	NhuPCCH_ConfigdefaultPagCycle defaultPagCycle;
	NhuPCCH_ConfignB nB;
} NhuPCCH_Config;

/* Element ----- prach-ConfigIndex ------- */
typedef TknU32 NhuPRACH_ConfigInfoprach_ConfigIdx;

/* Element ----- highSpeedFlag ------- */
typedef TknU8 NhuPRACH_ConfigInfohighSpeedFlag;

/* Element ----- zeroCorrelationZoneConfig ------- */
typedef TknU32 NhuPRACH_ConfigInfozeroCorrelationZoneConfig;

/* Element ----- prach-FreqOffset ------- */
typedef TknU32 NhuPRACH_ConfigInfoprach_FreqOffset;

typedef struct NhuPRACH_ConfigInfo
{
	TknPres pres;
	NhuPRACH_ConfigInfoprach_ConfigIdx prach_ConfigIdx;
	NhuPRACH_ConfigInfohighSpeedFlag highSpeedFlag;
	NhuPRACH_ConfigInfozeroCorrelationZoneConfig zeroCorrelationZoneConfig;
	NhuPRACH_ConfigInfoprach_FreqOffset prach_FreqOffset;
} NhuPRACH_ConfigInfo;

/* Element ----- rootSequenceIndex ------- */
typedef TknU32 NhuPRACH_ConfigSIBrootSequenceIdx;

typedef struct NhuPRACH_ConfigSIB
{
	TknPres pres;
	NhuPRACH_ConfigSIBrootSequenceIdx rootSequenceIdx;
	NhuPRACH_ConfigInfo prach_ConfigInfo;
} NhuPRACH_ConfigSIB;

/* Element ----- referenceSignalPower ------- */
typedef TknS32 NhuPDSCH_ConfigCmnreferenceSignalPower;

/* Element ----- p-b ------- */
typedef TknU32 NhuPDSCH_ConfigCmnp_b;

typedef struct NhuPDSCH_ConfigCmn
{
	TknPres pres;
	NhuPDSCH_ConfigCmnreferenceSignalPower referenceSignalPower;
	NhuPDSCH_ConfigCmnp_b p_b;
} NhuPDSCH_ConfigCmn;

/* Element ----- groupHoppingEnabled ------- */
typedef TknU8 NhuUL_ReferenceSignalsPUSCHgroupHoppingEnabled;

/* Element ----- groupAssignmentPUSCH ------- */
typedef TknU32 NhuUL_ReferenceSignalsPUSCHgroupAssignmentPUSCH;

/* Element ----- sequenceHoppingEnabled ------- */
typedef TknU8 NhuUL_ReferenceSignalsPUSCHsequenceHoppingEnabled;

/* Element ----- cyclicShift ------- */
typedef TknU32 NhuUL_ReferenceSignalsPUSCHcyclicShift;

typedef struct NhuUL_ReferenceSignalsPUSCH
{
	TknPres pres;
	NhuUL_ReferenceSignalsPUSCHgroupHoppingEnabled groupHoppingEnabled;
	NhuUL_ReferenceSignalsPUSCHgroupAssignmentPUSCH groupAssignmentPUSCH;
	NhuUL_ReferenceSignalsPUSCHsequenceHoppingEnabled sequenceHoppingEnabled;
	NhuUL_ReferenceSignalsPUSCHcyclicShift cyclicShift;
} NhuUL_ReferenceSignalsPUSCH;

/* Element ----- n-SB ------- */
typedef TknU32 NhuPUSCH_ConfigCmnpusch_ConfigBasicn_SB;

/* Element ----- hoppingMode ------- */
typedef enum enumNhuPUSCH_ConfigCmnpusch_ConfigBasichoppingMode
{
	NhuPUSCH_ConfigCmnpusch_ConfigBasichoppingModeinterSubFrameEnum,
	NhuPUSCH_ConfigCmnpusch_ConfigBasichoppingModeintraAndInterSubFrameEnum
} EnumNhuPUSCH_ConfigCmnpusch_ConfigBasichoppingMode;
typedef TknU32 NhuPUSCH_ConfigCmnpusch_ConfigBasichoppingMode;

/* Element ----- pusch-HoppingOffset ------- */
typedef TknU32 NhuPUSCH_ConfigCmnpusch_ConfigBasicpusch_HoppingOffset;

/* Element ----- enable64QAM ------- */
typedef TknU8 NhuPUSCH_ConfigCmnpusch_ConfigBasicenable64QAM;

typedef struct NhuPUSCH_ConfigCmnpusch_ConfigBasic
{
	TknPres pres;
	NhuPUSCH_ConfigCmnpusch_ConfigBasicn_SB n_SB;
	NhuPUSCH_ConfigCmnpusch_ConfigBasichoppingMode hoppingMode;
	NhuPUSCH_ConfigCmnpusch_ConfigBasicpusch_HoppingOffset pusch_HoppingOffset;
	NhuPUSCH_ConfigCmnpusch_ConfigBasicenable64QAM enable64QAM;
} NhuPUSCH_ConfigCmnpusch_ConfigBasic;

typedef struct NhuPUSCH_ConfigCmn
{
	TknPres pres;
	NhuPUSCH_ConfigCmnpusch_ConfigBasic pusch_ConfigBasic;
	NhuUL_ReferenceSignalsPUSCH ul_ReferenceSignalsPUSCH;
} NhuPUSCH_ConfigCmn;

/* Element ----- deltaPUCCH-Shift ------- */
typedef enum enumNhuPUCCH_ConfigCmndeltaPUCCH_Shift
{
	NhuPUCCH_ConfigCmndeltaPUCCH_Shiftds1Enum,
	NhuPUCCH_ConfigCmndeltaPUCCH_Shiftds2Enum,
	NhuPUCCH_ConfigCmndeltaPUCCH_Shiftds3Enum
} EnumNhuPUCCH_ConfigCmndeltaPUCCH_Shift;
typedef TknU32 NhuPUCCH_ConfigCmndeltaPUCCH_Shift;

/* Element ----- nRB-CQI ------- */
typedef TknU32 NhuPUCCH_ConfigCmnnRB_CQI;

/* Element ----- nCS-AN ------- */
typedef TknU32 NhuPUCCH_ConfigCmnnCS_AN;

/* Element ----- n1PUCCH-AN ------- */
typedef TknU32 NhuPUCCH_ConfigCmnn1PUCCH_AN;

typedef struct NhuPUCCH_ConfigCmn
{
	TknPres pres;
	NhuPUCCH_ConfigCmndeltaPUCCH_Shift deltaPUCCH_Shift;
	NhuPUCCH_ConfigCmnnRB_CQI nRB_CQI;
	NhuPUCCH_ConfigCmnnCS_AN nCS_AN;
	NhuPUCCH_ConfigCmnn1PUCCH_AN n1PUCCH_AN;
} NhuPUCCH_ConfigCmn;

/* Element ----- srs-BandwidthConfig ------- */
typedef enum enumNhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfig
{
	NhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfigbw0Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfigbw1Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfigbw2Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfigbw3Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfigbw4Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfigbw5Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfigbw6Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfigbw7Enum
} EnumNhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfig;
typedef TknU32 NhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfig;

/* Element ----- srs-SubframeConfig ------- */
typedef enum enumNhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfig
{
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc0Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc1Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc2Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc3Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc4Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc5Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc6Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc7Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc8Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc9Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc10Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc11Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc12Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc13Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc14Enum,
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc15Enum
} EnumNhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfig;
typedef TknU32 NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfig;

/* Element ----- ackNackSRS-SimultaneousTransmission ------- */
typedef TknU8 NhuSoundingRS_UL_ConfigCmnsetupackNackSRS_SimultaneousTransmission;

/* Element ----- srs-MaxUpPts ------- */
typedef enum enumNhuSoundingRS_UL_ConfigCmnsetupsrs_MaxUpPts
{
	NhuSoundingRS_UL_ConfigCmnsetupsrs_MaxUpPtstrueEnum
} EnumNhuSoundingRS_UL_ConfigCmnsetupsrs_MaxUpPts;
typedef TknU32 NhuSoundingRS_UL_ConfigCmnsetupsrs_MaxUpPts;

typedef struct NhuSoundingRS_UL_ConfigCmnsetup
{
	TknPres pres;
	NhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfig srs_BandwidthConfig;
	NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfig srs_SubfrmConfig;
	NhuSoundingRS_UL_ConfigCmnsetupackNackSRS_SimultaneousTransmission ackNackSRS_SimultaneousTransmission;
	NhuSoundingRS_UL_ConfigCmnsetupsrs_MaxUpPts srs_MaxUpPts;
} NhuSoundingRS_UL_ConfigCmnsetup;

typedef struct NhuSoundingRS_UL_ConfigCmn
{
	TknU8 choice;
	union {
		NhuSoundingRS_UL_ConfigCmnsetup setup;
	} val;
} NhuSoundingRS_UL_ConfigCmn;

/* Element ----- deltaF-PUCCH-Format1 ------- */
typedef enum enumNhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1
{
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1deltaF_2Enum,
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1deltaF0Enum,
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1deltaF2Enum
} EnumNhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1;
typedef TknU32 NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1;

/* Element ----- deltaF-PUCCH-Format1b ------- */
typedef enum enumNhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1b
{
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1bdeltaF1Enum,
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1bdeltaF3Enum,
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1bdeltaF5Enum
} EnumNhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1b;
typedef TknU32 NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1b;

/* Element ----- deltaF-PUCCH-Format2 ------- */
typedef enum enumNhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2
{
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2deltaF_2Enum,
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2deltaF0Enum,
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2deltaF1Enum,
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2deltaF2Enum
} EnumNhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2;
typedef TknU32 NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2;

/* Element ----- deltaF-PUCCH-Format2a ------- */
typedef enum enumNhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2a
{
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2adeltaF_2Enum,
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2adeltaF0Enum,
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2adeltaF2Enum
} EnumNhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2a;
typedef TknU32 NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2a;

/* Element ----- deltaF-PUCCH-Format2b ------- */
typedef enum enumNhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2b
{
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2bdeltaF_2Enum,
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2bdeltaF0Enum,
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2bdeltaF2Enum
} EnumNhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2b;
typedef TknU32 NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2b;

typedef struct NhuDeltaFLst_PUCCH
{
	TknPres pres;
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1 deltaF_PUCCH_Format1;
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format1b deltaF_PUCCH_Format1b;
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2 deltaF_PUCCH_Format2;
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2a deltaF_PUCCH_Format2a;
	NhuDeltaFLst_PUCCHdeltaF_PUCCH_Format2b deltaF_PUCCH_Format2b;
} NhuDeltaFLst_PUCCH;

/* Element ----- p0-NominalPUSCH ------- */
typedef TknS32 NhuUlnkPowerCntrlCmnp0_NominalPUSCH;

/* Element ----- alpha ------- */
typedef enum enumNhuUlnkPowerCntrlCmnalpha
{
	NhuUlnkPowerCntrlCmnalphaal0Enum,
	NhuUlnkPowerCntrlCmnalphaal04Enum,
	NhuUlnkPowerCntrlCmnalphaal05Enum,
	NhuUlnkPowerCntrlCmnalphaal06Enum,
	NhuUlnkPowerCntrlCmnalphaal07Enum,
	NhuUlnkPowerCntrlCmnalphaal08Enum,
	NhuUlnkPowerCntrlCmnalphaal09Enum,
	NhuUlnkPowerCntrlCmnalphaal1Enum
} EnumNhuUlnkPowerCntrlCmnalpha;
typedef TknU32 NhuUlnkPowerCntrlCmnalpha;

/* Element ----- p0-NominalPUCCH ------- */
typedef TknS32 NhuUlnkPowerCntrlCmnp0_NominalPUCCH;

/* Element ----- deltaPreambleMsg3 ------- */
typedef TknS32 NhuUlnkPowerCntrlCmndeltaPreambleMsg3;

typedef struct NhuUlnkPowerCntrlCmn
{
	TknPres pres;
	NhuUlnkPowerCntrlCmnp0_NominalPUSCH p0_NominalPUSCH;
	NhuUlnkPowerCntrlCmnalpha alpha;
	NhuUlnkPowerCntrlCmnp0_NominalPUCCH p0_NominalPUCCH;
	NhuDeltaFLst_PUCCH deltaFLst_PUCCH;
	NhuUlnkPowerCntrlCmndeltaPreambleMsg3 deltaPreambleMsg3;
} NhuUlnkPowerCntrlCmn;

/* Element ----- UL-CyclicPrefixLength ------- */
typedef enum enumNhuUL_CyclicPrefixLength
{
	NhuUL_CyclicPrefixLengthlen1Enum,
	NhuUL_CyclicPrefixLengthlen2Enum
} EnumNhuUL_CyclicPrefixLength;
typedef TknU32 NhuUL_CyclicPrefixLength;

/* Element ----- deltaF-PUCCH-Format3-r10 ------- */
typedef enum enumNhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10
{
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10deltaF_1Enum,
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10deltaF0Enum,
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10deltaF1Enum,
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10deltaF2Enum,
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10deltaF3Enum,
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10deltaF4Enum,
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10deltaF5Enum,
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10deltaF6Enum
} EnumNhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10;
typedef TknU32 NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10;

/* Element ----- deltaF-PUCCH-Format1bCS-r10 ------- */
typedef enum enumNhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format1bCS_r10
{
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format1bCS_r10deltaF1Enum,
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format1bCS_r10deltaF2Enum,
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format1bCS_r10spare2Enum,
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format1bCS_r10spare1Enum
} EnumNhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format1bCS_r10;
typedef TknU32 NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format1bCS_r10;

typedef struct NhuUlnkPowerCntrlCmn_v1020
{
	TknPres pres;
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10 deltaF_PUCCH_Format3_r10;
	NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format1bCS_r10 deltaF_PUCCH_Format1bCS_r10;
} NhuUlnkPowerCntrlCmn_v1020;

typedef struct NhuRadioResourceConfigCmnSIBextaddgrp_1
{
	TknPres pres;
	NhuUlnkPowerCntrlCmn_v1020 uplinkPowerCntrlCmn_v1020;
} NhuRadioResourceConfigCmnSIBextaddgrp_1;

typedef struct NhuRadioResourceConfigCmnSIB
{
	TknPres pres;
	NhuRACH_ConfigCmn rach_ConfigCmn;
	NhuBCCH_Config bcch_Config;
	NhuPCCH_Config pcch_Config;
	NhuPRACH_ConfigSIB prach_Config;
	NhuPDSCH_ConfigCmn pdsch_ConfigCmn;
	NhuPUSCH_ConfigCmn pusch_ConfigCmn;
	NhuPUCCH_ConfigCmn pucch_ConfigCmn;
	NhuSoundingRS_UL_ConfigCmn soundingRS_UL_ConfigCmn;
	NhuUlnkPowerCntrlCmn uplinkPowerCntrlCmn;
	NhuUL_CyclicPrefixLength ul_CyclicPrefixLength;
	NhuRadioResourceConfigCmnSIBextaddgrp_1 extaddgrp_1;
} NhuRadioResourceConfigCmnSIB;

/* Element ----- t300 ------- */
typedef enum enumNhuUE_TmrsAndConstst300
{
	NhuUE_TmrsAndConstst300ms100Enum,
	NhuUE_TmrsAndConstst300ms200Enum,
	NhuUE_TmrsAndConstst300ms300Enum,
	NhuUE_TmrsAndConstst300ms400Enum,
	NhuUE_TmrsAndConstst300ms600Enum,
	NhuUE_TmrsAndConstst300ms1000Enum,
	NhuUE_TmrsAndConstst300ms1500Enum,
	NhuUE_TmrsAndConstst300ms2000Enum
} EnumNhuUE_TmrsAndConstst300;
typedef TknU32 NhuUE_TmrsAndConstst300;

/* Element ----- t301 ------- */
typedef enum enumNhuUE_TmrsAndConstst301
{
	NhuUE_TmrsAndConstst301ms100Enum,
	NhuUE_TmrsAndConstst301ms200Enum,
	NhuUE_TmrsAndConstst301ms300Enum,
	NhuUE_TmrsAndConstst301ms400Enum,
	NhuUE_TmrsAndConstst301ms600Enum,
	NhuUE_TmrsAndConstst301ms1000Enum,
	NhuUE_TmrsAndConstst301ms1500Enum,
	NhuUE_TmrsAndConstst301ms2000Enum
} EnumNhuUE_TmrsAndConstst301;
typedef TknU32 NhuUE_TmrsAndConstst301;

/* Element ----- t310 ------- */
typedef enum enumNhuUE_TmrsAndConstst310
{
	NhuUE_TmrsAndConstst310ms0Enum,
	NhuUE_TmrsAndConstst310ms50Enum,
	NhuUE_TmrsAndConstst310ms100Enum,
	NhuUE_TmrsAndConstst310ms200Enum,
	NhuUE_TmrsAndConstst310ms500Enum,
	NhuUE_TmrsAndConstst310ms1000Enum,
	NhuUE_TmrsAndConstst310ms2000Enum
} EnumNhuUE_TmrsAndConstst310;
typedef TknU32 NhuUE_TmrsAndConstst310;

/* Element ----- n310 ------- */
typedef enum enumNhuUE_TmrsAndConstsn310
{
	NhuUE_TmrsAndConstsn310n1Enum,
	NhuUE_TmrsAndConstsn310n2Enum,
	NhuUE_TmrsAndConstsn310n3Enum,
	NhuUE_TmrsAndConstsn310n4Enum,
	NhuUE_TmrsAndConstsn310n6Enum,
	NhuUE_TmrsAndConstsn310n8Enum,
	NhuUE_TmrsAndConstsn310n10Enum,
	NhuUE_TmrsAndConstsn310n20Enum
} EnumNhuUE_TmrsAndConstsn310;
typedef TknU32 NhuUE_TmrsAndConstsn310;

/* Element ----- t311 ------- */
typedef enum enumNhuUE_TmrsAndConstst311
{
	NhuUE_TmrsAndConstst311ms1000Enum,
	NhuUE_TmrsAndConstst311ms3000Enum,
	NhuUE_TmrsAndConstst311ms5000Enum,
	NhuUE_TmrsAndConstst311ms10000Enum,
	NhuUE_TmrsAndConstst311ms15000Enum,
	NhuUE_TmrsAndConstst311ms20000Enum,
	NhuUE_TmrsAndConstst311ms30000Enum
} EnumNhuUE_TmrsAndConstst311;
typedef TknU32 NhuUE_TmrsAndConstst311;

/* Element ----- n311 ------- */
typedef enum enumNhuUE_TmrsAndConstsn311
{
	NhuUE_TmrsAndConstsn311n1Enum,
	NhuUE_TmrsAndConstsn311n2Enum,
	NhuUE_TmrsAndConstsn311n3Enum,
	NhuUE_TmrsAndConstsn311n4Enum,
	NhuUE_TmrsAndConstsn311n5Enum,
	NhuUE_TmrsAndConstsn311n6Enum,
	NhuUE_TmrsAndConstsn311n8Enum,
	NhuUE_TmrsAndConstsn311n10Enum
} EnumNhuUE_TmrsAndConstsn311;
typedef TknU32 NhuUE_TmrsAndConstsn311;

typedef struct NhuUE_TmrsAndConsts
{
	TknPres pres;
	NhuUE_TmrsAndConstst300 t300;
	NhuUE_TmrsAndConstst301 t301;
	NhuUE_TmrsAndConstst310 t310;
	NhuUE_TmrsAndConstsn310 n310;
	NhuUE_TmrsAndConstst311 t311;
	NhuUE_TmrsAndConstsn311 n311;
} NhuUE_TmrsAndConsts;

/* Element ----- ARFCN-ValueEUTRA ------- */
typedef TknU32 NhuARFCN_ValueEUTRA;

/* Element ----- AdditionalSpectrumEmission ------- */
typedef TknU32 NhuAdditionalSpectrumEmission;

/* Element ----- radioframeAllocationPeriod ------- */
typedef enum enumNhuMBSFN_SubfrmConfigradioframeAllocnPeriod
{
	NhuMBSFN_SubfrmConfigradioframeAllocnPeriodn1Enum,
	NhuMBSFN_SubfrmConfigradioframeAllocnPeriodn2Enum,
	NhuMBSFN_SubfrmConfigradioframeAllocnPeriodn4Enum,
	NhuMBSFN_SubfrmConfigradioframeAllocnPeriodn8Enum,
	NhuMBSFN_SubfrmConfigradioframeAllocnPeriodn16Enum,
	NhuMBSFN_SubfrmConfigradioframeAllocnPeriodn32Enum
} EnumNhuMBSFN_SubfrmConfigradioframeAllocnPeriod;
typedef TknU32 NhuMBSFN_SubfrmConfigradioframeAllocnPeriod;

/* Element ----- radioframeAllocationOffset ------- */
typedef TknU32 NhuMBSFN_SubfrmConfigradioframeAllocnOffset;

/* Element ---------- oneFrame ----------- */
typedef TknStrBSXL NhuMBSFN_SubfrmConfigsubframeAllocnoneFrame;
/* Element ---------- fourFrames ----------- */
typedef TknStrBSXL NhuMBSFN_SubfrmConfigsubframeAllocnfourFrames;
typedef struct NhuMBSFN_SubfrmConfigsubframeAllocn
{
	TknU8 choice;
	union {
		NhuMBSFN_SubfrmConfigsubframeAllocnoneFrame oneFrame;
		NhuMBSFN_SubfrmConfigsubframeAllocnfourFrames fourFrames;
	} val;
} NhuMBSFN_SubfrmConfigsubframeAllocn;

typedef struct NhuMBSFN_SubfrmConfig
{
	TknPres pres;
	NhuMBSFN_SubfrmConfigradioframeAllocnPeriod radioframeAllocnPeriod;
	NhuMBSFN_SubfrmConfigradioframeAllocnOffset radioframeAllocnOffset;
	NhuMBSFN_SubfrmConfigsubframeAllocn subframeAllocn;
} NhuMBSFN_SubfrmConfig;

typedef struct NhuMBSFN_SubfrmConfigLst
{
	TknU16 noComp;
	NhuMBSFN_SubfrmConfig *member;
}NhuMBSFN_SubfrmConfigLst;

/* Element ----- TimeAlignmentTimer ------- */
typedef enum enumNhuTimeAlignmentTimer
{
	NhuTimeAlignmentTimersf500Enum,
	NhuTimeAlignmentTimersf750Enum,
	NhuTimeAlignmentTimersf1280Enum,
	NhuTimeAlignmentTimersf1920Enum,
	NhuTimeAlignmentTimersf2560Enum,
	NhuTimeAlignmentTimersf5120Enum,
	NhuTimeAlignmentTimersf10240Enum,
	NhuTimeAlignmentTimerinfinityEnum
} EnumNhuTimeAlignmentTimer;
typedef TknU32 NhuTimeAlignmentTimer;

/* Element ----- ac-BarringForEmergency ------- */
typedef TknU8 NhuSysInfoBlockTyp2ac_BarringInfoac_BarringForEmergency;

typedef struct NhuSysInfoBlockTyp2ac_BarringInfo
{
	TknPres pres;
	NhuSysInfoBlockTyp2ac_BarringInfoac_BarringForEmergency ac_BarringForEmergency;
	NhuAC_BarringConfig ac_BarringForMO_Signalling;
	NhuAC_BarringConfig ac_BarringForMO_Data;
} NhuSysInfoBlockTyp2ac_BarringInfo;

/* Element ----- ul-Bandwidth ------- */
typedef enum enumNhuSysInfoBlockTyp2freqInfoul_Bandwidth
{
	NhuSysInfoBlockTyp2freqInfoul_Bandwidthn6Enum,
	NhuSysInfoBlockTyp2freqInfoul_Bandwidthn15Enum,
	NhuSysInfoBlockTyp2freqInfoul_Bandwidthn25Enum,
	NhuSysInfoBlockTyp2freqInfoul_Bandwidthn50Enum,
	NhuSysInfoBlockTyp2freqInfoul_Bandwidthn75Enum,
	NhuSysInfoBlockTyp2freqInfoul_Bandwidthn100Enum
} EnumNhuSysInfoBlockTyp2freqInfoul_Bandwidth;
typedef TknU32 NhuSysInfoBlockTyp2freqInfoul_Bandwidth;

typedef struct NhuSysInfoBlockTyp2freqInfo
{
	TknPres pres;
	NhuARFCN_ValueEUTRA ul_CarrierFreq;
	NhuSysInfoBlockTyp2freqInfoul_Bandwidth ul_Bandwidth;
	NhuAdditionalSpectrumEmission additionalSpectrumEmission;
} NhuSysInfoBlockTyp2freqInfo;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp2lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp2extaddgrp_1
{
	TknPres pres;
	NhuAC_BarringConfig ssac_BarringForMMTEL_Voice_r9;
	NhuAC_BarringConfig ssac_BarringForMMTEL_Video_r9;
} NhuSysInfoBlockTyp2extaddgrp_1;

typedef struct NhuSysInfoBlockTyp2extaddgrp_2
{
	TknPres pres;
	NhuAC_BarringConfig ac_BarringForCSFB_r10;
} NhuSysInfoBlockTyp2extaddgrp_2;

typedef struct NhuSysInfoBlockTyp2
{
	TknPres pres;
	NhuSysInfoBlockTyp2ac_BarringInfo ac_BarringInfo;
	NhuRadioResourceConfigCmnSIB radioResourceConfigCmn;
	NhuUE_TmrsAndConsts ue_TmrsAndConsts;
	NhuSysInfoBlockTyp2freqInfo freqInfo;
	NhuMBSFN_SubfrmConfigLst mbsfn_SubfrmConfigLst;
	NhuTimeAlignmentTimer timeAlignmentTimerCmn;
	NhuSysInfoBlockTyp2lateNonCriticalExtn lateNonCriticalExtn;
	NhuSysInfoBlockTyp2extaddgrp_1 extaddgrp_1;
	NhuSysInfoBlockTyp2extaddgrp_2 extaddgrp_2;
} NhuSysInfoBlockTyp2;

/* Element ----- t-Evaluation ------- */
typedef enum enumNhuMobilityStateParamst_Evaluation
{
	NhuMobilityStateParamst_Evaluations30Enum,
	NhuMobilityStateParamst_Evaluations60Enum,
	NhuMobilityStateParamst_Evaluations120Enum,
	NhuMobilityStateParamst_Evaluations180Enum,
	NhuMobilityStateParamst_Evaluations240Enum,
	NhuMobilityStateParamst_Evaluationspare3Enum,
	NhuMobilityStateParamst_Evaluationspare2Enum,
	NhuMobilityStateParamst_Evaluationspare1Enum
} EnumNhuMobilityStateParamst_Evaluation;
typedef TknU32 NhuMobilityStateParamst_Evaluation;

/* Element ----- t-HystNormal ------- */
typedef enum enumNhuMobilityStateParamst_HystNormal
{
	NhuMobilityStateParamst_HystNormals30Enum,
	NhuMobilityStateParamst_HystNormals60Enum,
	NhuMobilityStateParamst_HystNormals120Enum,
	NhuMobilityStateParamst_HystNormals180Enum,
	NhuMobilityStateParamst_HystNormals240Enum,
	NhuMobilityStateParamst_HystNormalspare3Enum,
	NhuMobilityStateParamst_HystNormalspare2Enum,
	NhuMobilityStateParamst_HystNormalspare1Enum
} EnumNhuMobilityStateParamst_HystNormal;
typedef TknU32 NhuMobilityStateParamst_HystNormal;

/* Element ----- n-CellChangeMedium ------- */
typedef TknU32 NhuMobilityStateParamsn_CellChangeMedium;

/* Element ----- n-CellChangeHigh ------- */
typedef TknU32 NhuMobilityStateParamsn_CellChangeHigh;

typedef struct NhuMobilityStateParams
{
	TknPres pres;
	NhuMobilityStateParamst_Evaluation t_Evaluation;
	NhuMobilityStateParamst_HystNormal t_HystNormal;
	NhuMobilityStateParamsn_CellChangeMedium n_CellChangeMedium;
	NhuMobilityStateParamsn_CellChangeHigh n_CellChangeHigh;
} NhuMobilityStateParams;

/* Element ----- ReselectionThreshold ------- */
typedef TknU32 NhuReselectionThreshold;

/* Element ----- CellReselectionPriority ------- */
typedef TknU32 NhuCellReselectionPriority;

/* Element ----- Q-RxLevMin ------- */
typedef TknS32 NhuQ_RxLevMin;

/* Element ----- P-Max ------- */
typedef TknS32 NhuP_Max;

/* Element ----- AllowedMeasBandwidth ------- */
typedef enum enumNhuAllowedMeasBandwidth
{
	NhuAllowedMeasBandwidthmbw6Enum,
	NhuAllowedMeasBandwidthmbw15Enum,
	NhuAllowedMeasBandwidthmbw25Enum,
	NhuAllowedMeasBandwidthmbw50Enum,
	NhuAllowedMeasBandwidthmbw75Enum,
	NhuAllowedMeasBandwidthmbw100Enum
} EnumNhuAllowedMeasBandwidth;
typedef TknU32 NhuAllowedMeasBandwidth;

/* Element ----- PresenceAntennaPort1 ------- */
typedef TknU8 NhuPresenceAntennaPort1;

/* Element ---------- NeighCellConfig ----------- */
typedef TknStrBSXL NhuNeighCellConfig;
/* Element ----- T-Reselection ------- */
typedef TknU32 NhuT_Reselection;

/* Element ----- sf-Medium ------- */
typedef enum enumNhuSpeedStateScaleFactorssf_Medium
{
	NhuSpeedStateScaleFactorssf_MediumoDot25Enum,
	NhuSpeedStateScaleFactorssf_MediumoDot5Enum,
	NhuSpeedStateScaleFactorssf_MediumoDot75Enum,
	NhuSpeedStateScaleFactorssf_MediumlDot0Enum
} EnumNhuSpeedStateScaleFactorssf_Medium;
typedef TknU32 NhuSpeedStateScaleFactorssf_Medium;

/* Element ----- sf-High ------- */
typedef enum enumNhuSpeedStateScaleFactorssf_High
{
	NhuSpeedStateScaleFactorssf_HighoDot25Enum,
	NhuSpeedStateScaleFactorssf_HighoDot5Enum,
	NhuSpeedStateScaleFactorssf_HighoDot75Enum,
	NhuSpeedStateScaleFactorssf_HighlDot0Enum
} EnumNhuSpeedStateScaleFactorssf_High;
typedef TknU32 NhuSpeedStateScaleFactorssf_High;

typedef struct NhuSpeedStateScaleFactors
{
	TknPres pres;
	NhuSpeedStateScaleFactorssf_Medium sf_Medium;
	NhuSpeedStateScaleFactorssf_High sf_High;
} NhuSpeedStateScaleFactors;

/* Element ----- ReselectionThresholdQ-r9 ------- */
typedef TknU32 NhuReselectionThresholdQ_r9;

/* Element ----- Q-QualMin-r9 ------- */
typedef TknS32 NhuQ_QualMin_r9;

/* Element ----- q-Hyst ------- */
typedef enum enumNhuSysInfoBlockTyp3cellReselectionInfoCmnq_Hyst
{
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB0Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB1Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB2Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB3Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB4Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB5Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB6Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB8Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB10Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB12Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB14Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB16Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB18Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB20Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB22Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB24Enum
} EnumNhuSysInfoBlockTyp3cellReselectionInfoCmnq_Hyst;
typedef TknU32 NhuSysInfoBlockTyp3cellReselectionInfoCmnq_Hyst;

/* Element ----- sf-Medium ------- */
typedef enum enumNhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_Medium
{
	NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_MediumdB_6Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_MediumdB_4Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_MediumdB_2Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_MediumdB0Enum
} EnumNhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_Medium;
typedef TknU32 NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_Medium;

/* Element ----- sf-High ------- */
typedef enum enumNhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_High
{
	NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_HighdB_6Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_HighdB_4Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_HighdB_2Enum,
	NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_HighdB0Enum
} EnumNhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_High;
typedef TknU32 NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_High;

typedef struct NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSF
{
	TknPres pres;
	NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_Medium sf_Medium;
	NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSFsf_High sf_High;
} NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSF;

typedef struct NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionPars
{
	TknPres pres;
	NhuMobilityStateParams mobilityStateParams;
	NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionParsq_HystSF q_HystSF;
} NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionPars;

typedef struct NhuSysInfoBlockTyp3cellReselectionInfoCmn
{
	TknPres pres;
	NhuSysInfoBlockTyp3cellReselectionInfoCmnq_Hyst q_Hyst;
	NhuSysInfoBlockTyp3cellReselectionInfoCmnspeedStateReselectionPars speedStateReselectionPars;
} NhuSysInfoBlockTyp3cellReselectionInfoCmn;

typedef struct NhuSysInfoBlockTyp3cellReselectionServingFreqInfo
{
	TknPres pres;
	NhuReselectionThreshold s_NonIntraSearch;
	NhuReselectionThreshold threshServingLow;
	NhuCellReselectionPriority cellReselectionPriority;
} NhuSysInfoBlockTyp3cellReselectionServingFreqInfo;

typedef struct NhuSysInfoBlockTyp3intraFreqCellReselectionInfo
{
	TknPres pres;
	NhuQ_RxLevMin q_RxLevMin;
	NhuP_Max p_Max;
	NhuReselectionThreshold s_IntraSearch;
	NhuAllowedMeasBandwidth allowedMeasBandwidth;
	NhuPresenceAntennaPort1 presenceAntennaPort1;
	NhuNeighCellConfig neighCellConfig;
	NhuT_Reselection t_ReselectionEUTRA;
	NhuSpeedStateScaleFactors t_ReselectionEUTRA_SF;
} NhuSysInfoBlockTyp3intraFreqCellReselectionInfo;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp3lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp3extaddgrp_1s_IntraSearch_v920
{
	TknPres pres;
	NhuReselectionThreshold s_IntraSearchP_r9;
	NhuReselectionThresholdQ_r9 s_IntraSearchQ_r9;
} NhuSysInfoBlockTyp3extaddgrp_1s_IntraSearch_v920;

typedef struct NhuSysInfoBlockTyp3extaddgrp_1s_NonIntraSearch_v920
{
	TknPres pres;
	NhuReselectionThreshold s_NonIntraSearchP_r9;
	NhuReselectionThresholdQ_r9 s_NonIntraSearchQ_r9;
} NhuSysInfoBlockTyp3extaddgrp_1s_NonIntraSearch_v920;

typedef struct NhuSysInfoBlockTyp3extaddgrp_1
{
	TknPres pres;
	NhuSysInfoBlockTyp3extaddgrp_1s_IntraSearch_v920 s_IntraSearch_v920;
	NhuSysInfoBlockTyp3extaddgrp_1s_NonIntraSearch_v920 s_NonIntraSearch_v920;
	NhuQ_QualMin_r9 q_QualMin_r9;
	NhuReselectionThresholdQ_r9 threshServingLowQ_r9;
} NhuSysInfoBlockTyp3extaddgrp_1;

typedef struct NhuSysInfoBlockTyp3extaddgrp_2
{
	TknPres pres;
	NhuQ_QualMin_r9 q_QualMinWB_r11;
} NhuSysInfoBlockTyp3extaddgrp_2;

typedef struct NhuSysInfoBlockTyp3
{
	TknPres pres;
	NhuSysInfoBlockTyp3cellReselectionInfoCmn cellReselectionInfoCmn;
	NhuSysInfoBlockTyp3cellReselectionServingFreqInfo cellReselectionServingFreqInfo;
	NhuSysInfoBlockTyp3intraFreqCellReselectionInfo intraFreqCellReselectionInfo;
	NhuSysInfoBlockTyp3lateNonCriticalExtn lateNonCriticalExtn;
	NhuSysInfoBlockTyp3extaddgrp_1 extaddgrp_1;
	NhuSysInfoBlockTyp3extaddgrp_2 extaddgrp_2;
} NhuSysInfoBlockTyp3;

/* Element ----- PhysCellId ------- */
typedef TknU32 NhuPhysCellId;

/* Element ----- Q-OffsetRange ------- */
typedef enum enumNhuQ_OffsetRange
{
	NhuQ_OffsetRangedB_24Enum,
	NhuQ_OffsetRangedB_22Enum,
	NhuQ_OffsetRangedB_20Enum,
	NhuQ_OffsetRangedB_18Enum,
	NhuQ_OffsetRangedB_16Enum,
	NhuQ_OffsetRangedB_14Enum,
	NhuQ_OffsetRangedB_12Enum,
	NhuQ_OffsetRangedB_10Enum,
	NhuQ_OffsetRangedB_8Enum,
	NhuQ_OffsetRangedB_6Enum,
	NhuQ_OffsetRangedB_5Enum,
	NhuQ_OffsetRangedB_4Enum,
	NhuQ_OffsetRangedB_3Enum,
	NhuQ_OffsetRangedB_2Enum,
	NhuQ_OffsetRangedB_1Enum,
	NhuQ_OffsetRangedB0Enum,
	NhuQ_OffsetRangedB1Enum,
	NhuQ_OffsetRangedB2Enum,
	NhuQ_OffsetRangedB3Enum,
	NhuQ_OffsetRangedB4Enum,
	NhuQ_OffsetRangedB5Enum,
	NhuQ_OffsetRangedB6Enum,
	NhuQ_OffsetRangedB8Enum,
	NhuQ_OffsetRangedB10Enum,
	NhuQ_OffsetRangedB12Enum,
	NhuQ_OffsetRangedB14Enum,
	NhuQ_OffsetRangedB16Enum,
	NhuQ_OffsetRangedB18Enum,
	NhuQ_OffsetRangedB20Enum,
	NhuQ_OffsetRangedB22Enum,
	NhuQ_OffsetRangedB24Enum
} EnumNhuQ_OffsetRange;
typedef TknU32 NhuQ_OffsetRange;

typedef struct NhuIntraFreqNeighCellInfo
{
	TknPres pres;
	NhuPhysCellId physCellId;
	NhuQ_OffsetRange q_OffsetCell;
} NhuIntraFreqNeighCellInfo;

typedef struct NhuIntraFreqNeighCellLst
{
	TknU16 noComp;
	NhuIntraFreqNeighCellInfo *member;
}NhuIntraFreqNeighCellLst;

/* Element ----- range ------- */
typedef enum enumNhuPhysCellIdRangerange
{
	NhuPhysCellIdRangerangen4Enum,
	NhuPhysCellIdRangerangen8Enum,
	NhuPhysCellIdRangerangen12Enum,
	NhuPhysCellIdRangerangen16Enum,
	NhuPhysCellIdRangerangen24Enum,
	NhuPhysCellIdRangerangen32Enum,
	NhuPhysCellIdRangerangen48Enum,
	NhuPhysCellIdRangerangen64Enum,
	NhuPhysCellIdRangerangen84Enum,
	NhuPhysCellIdRangerangen96Enum,
	NhuPhysCellIdRangerangen128Enum,
	NhuPhysCellIdRangerangen168Enum,
	NhuPhysCellIdRangerangen252Enum,
	NhuPhysCellIdRangerangen504Enum,
	NhuPhysCellIdRangerangespare2Enum,
	NhuPhysCellIdRangerangespare1Enum
} EnumNhuPhysCellIdRangerange;
typedef TknU32 NhuPhysCellIdRangerange;

typedef struct NhuPhysCellIdRange
{
	TknPres pres;
	NhuPhysCellId start;
	NhuPhysCellIdRangerange range;
} NhuPhysCellIdRange;

typedef struct NhuIntraFreqBlackCellLst
{
	TknU16 noComp;
	NhuPhysCellIdRange *member;
}NhuIntraFreqBlackCellLst;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp4lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp4
{
	TknPres pres;
	NhuIntraFreqNeighCellLst intraFreqNeighCellLst;
	NhuIntraFreqBlackCellLst intraFreqBlackCellLst;
	NhuPhysCellIdRange csg_PhysCellIdRange;
	NhuSysInfoBlockTyp4lateNonCriticalExtn lateNonCriticalExtn;
} NhuSysInfoBlockTyp4;

typedef struct NhuInterFreqNeighCellInfo
{
	TknPres pres;
	NhuPhysCellId physCellId;
	NhuQ_OffsetRange q_OffsetCell;
} NhuInterFreqNeighCellInfo;

typedef struct NhuInterFreqNeighCellLst
{
	TknU16 noComp;
	NhuInterFreqNeighCellInfo *member;
}NhuInterFreqNeighCellLst;

typedef struct NhuInterFreqBlackCellLst
{
	TknU16 noComp;
	NhuPhysCellIdRange *member;
}NhuInterFreqBlackCellLst;

typedef struct NhuInterFreqCarrierFreqInfoextaddgrp_1threshX_Q_r9
{
	TknPres pres;
	NhuReselectionThresholdQ_r9 threshX_HighQ_r9;
	NhuReselectionThresholdQ_r9 threshX_LowQ_r9;
} NhuInterFreqCarrierFreqInfoextaddgrp_1threshX_Q_r9;

typedef struct NhuInterFreqCarrierFreqInfoextaddgrp_1
{
	TknPres pres;
	NhuQ_QualMin_r9 q_QualMin_r9;
	NhuInterFreqCarrierFreqInfoextaddgrp_1threshX_Q_r9 threshX_Q_r9;
} NhuInterFreqCarrierFreqInfoextaddgrp_1;

typedef struct NhuInterFreqCarrierFreqInfoextaddgrp_2
{
	TknPres pres;
	NhuQ_QualMin_r9 q_QualMinWB_r11;
} NhuInterFreqCarrierFreqInfoextaddgrp_2;

typedef struct NhuInterFreqCarrierFreqInfo
{
	TknPres pres;
	NhuARFCN_ValueEUTRA dl_CarrierFreq;
	NhuQ_RxLevMin q_RxLevMin;
	NhuP_Max p_Max;
	NhuT_Reselection t_ReselectionEUTRA;
	NhuSpeedStateScaleFactors t_ReselectionEUTRA_SF;
	NhuReselectionThreshold threshX_High;
	NhuReselectionThreshold threshX_Low;
	NhuAllowedMeasBandwidth allowedMeasBandwidth;
	NhuPresenceAntennaPort1 presenceAntennaPort1;
	NhuCellReselectionPriority cellReselectionPriority;
	NhuNeighCellConfig neighCellConfig;
	NhuQ_OffsetRange q_OffsetFreq;	/* DEFAULT 0 */ 
	NhuInterFreqNeighCellLst interFreqNeighCellLst;
	NhuInterFreqBlackCellLst interFreqBlackCellLst;
	NhuInterFreqCarrierFreqInfoextaddgrp_1 extaddgrp_1;
	NhuInterFreqCarrierFreqInfoextaddgrp_2 extaddgrp_2;
} NhuInterFreqCarrierFreqInfo;

typedef struct NhuInterFreqCarrierFreqLst
{
	TknU16 noComp;
	NhuInterFreqCarrierFreqInfo *member;
}NhuInterFreqCarrierFreqLst;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp5lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp5
{
	TknPres pres;
	NhuInterFreqCarrierFreqLst interFreqCarrierFreqLst;
	NhuSysInfoBlockTyp5lateNonCriticalExtn lateNonCriticalExtn;
} NhuSysInfoBlockTyp5;

/* Element ----- ARFCN-ValueUTRA ------- */
typedef TknU32 NhuARFCN_ValueUTRA;

/* Element ----- q-RxLevMin ------- */
typedef TknS32 NhuCarrierFreqUTRA_FDDq_RxLevMin;

/* Element ----- p-MaxUTRA ------- */
typedef TknS32 NhuCarrierFreqUTRA_FDDp_MaxUTRA;

/* Element ----- q-QualMin ------- */
typedef TknS32 NhuCarrierFreqUTRA_FDDq_QualMin;

typedef struct NhuCarrierFreqUTRA_FDDextaddgrp_1threshX_Q_r9
{
	TknPres pres;
	NhuReselectionThresholdQ_r9 threshX_HighQ_r9;
	NhuReselectionThresholdQ_r9 threshX_LowQ_r9;
} NhuCarrierFreqUTRA_FDDextaddgrp_1threshX_Q_r9;

typedef struct NhuCarrierFreqUTRA_FDDextaddgrp_1
{
	TknPres pres;
	NhuCarrierFreqUTRA_FDDextaddgrp_1threshX_Q_r9 threshX_Q_r9;
} NhuCarrierFreqUTRA_FDDextaddgrp_1;

typedef struct NhuCarrierFreqUTRA_FDD
{
	TknPres pres;
	NhuARFCN_ValueUTRA carrierFreq;
	NhuCellReselectionPriority cellReselectionPriority;
	NhuReselectionThreshold threshX_High;
	NhuReselectionThreshold threshX_Low;
	NhuCarrierFreqUTRA_FDDq_RxLevMin q_RxLevMin;
	NhuCarrierFreqUTRA_FDDp_MaxUTRA p_MaxUTRA;
	NhuCarrierFreqUTRA_FDDq_QualMin q_QualMin;
	NhuCarrierFreqUTRA_FDDextaddgrp_1 extaddgrp_1;
} NhuCarrierFreqUTRA_FDD;

typedef struct NhuCarrierFreqLstUTRA_FDD
{
	TknU16 noComp;
	NhuCarrierFreqUTRA_FDD *member;
}NhuCarrierFreqLstUTRA_FDD;

/* Element ----- q-RxLevMin ------- */
typedef TknS32 NhuCarrierFreqUTRA_TDDq_RxLevMin;

/* Element ----- p-MaxUTRA ------- */
typedef TknS32 NhuCarrierFreqUTRA_TDDp_MaxUTRA;

typedef struct NhuCarrierFreqUTRA_TDD
{
	TknPres pres;
	NhuARFCN_ValueUTRA carrierFreq;
	NhuCellReselectionPriority cellReselectionPriority;
	NhuReselectionThreshold threshX_High;
	NhuReselectionThreshold threshX_Low;
	NhuCarrierFreqUTRA_TDDq_RxLevMin q_RxLevMin;
	NhuCarrierFreqUTRA_TDDp_MaxUTRA p_MaxUTRA;
} NhuCarrierFreqUTRA_TDD;

typedef struct NhuCarrierFreqLstUTRA_TDD
{
	TknU16 noComp;
	NhuCarrierFreqUTRA_TDD *member;
}NhuCarrierFreqLstUTRA_TDD;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp6lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp6
{
	TknPres pres;
	NhuCarrierFreqLstUTRA_FDD carrierFreqLstUTRA_FDD;
	NhuCarrierFreqLstUTRA_TDD carrierFreqLstUTRA_TDD;
	NhuT_Reselection t_ReselectionUTRA;
	NhuSpeedStateScaleFactors t_ReselectionUTRA_SF;
	NhuSysInfoBlockTyp6lateNonCriticalExtn lateNonCriticalExtn;
} NhuSysInfoBlockTyp6;

/* Element ----- ARFCN-ValueGERAN ------- */
typedef TknU32 NhuARFCN_ValueGERAN;

/* Element ----- BandIndicatorGERAN ------- */
typedef enum enumNhuBandIndicatorGERAN
{
	NhuBandIndicatorGERANdcs1800Enum,
	NhuBandIndicatorGERANpcs1900Enum
} EnumNhuBandIndicatorGERAN;
typedef TknU32 NhuBandIndicatorGERAN;

typedef struct NhuExplicitLstOfARFCNs
{
	TknU16 noComp;
	NhuARFCN_ValueGERAN *member;
}NhuExplicitLstOfARFCNs;

/* Element ----- arfcn-Spacing ------- */
typedef TknU32 NhuCarrierFreqsGERANfollowingARFCNsequallySpacedARFCNsarfcn_Spacing;

/* Element ----- numberOfFollowingARFCNs ------- */
typedef TknU32 NhuCarrierFreqsGERANfollowingARFCNsequallySpacedARFCNsnumberOfFollowingARFCNs;

typedef struct NhuCarrierFreqsGERANfollowingARFCNsequallySpacedARFCNs
{
	TknPres pres;
	NhuCarrierFreqsGERANfollowingARFCNsequallySpacedARFCNsarfcn_Spacing arfcn_Spacing;
	NhuCarrierFreqsGERANfollowingARFCNsequallySpacedARFCNsnumberOfFollowingARFCNs numberOfFollowingARFCNs;
} NhuCarrierFreqsGERANfollowingARFCNsequallySpacedARFCNs;

/* Element ---------- variableBitMapOfARFCNs ----------- */
typedef TknStrOSXL NhuCarrierFreqsGERANfollowingARFCNsvariableBitMapOfARFCNs;
typedef struct NhuCarrierFreqsGERANfollowingARFCNs
{
	TknU8 choice;
	union {
		NhuExplicitLstOfARFCNs explicitLstOfARFCNs;
		NhuCarrierFreqsGERANfollowingARFCNsequallySpacedARFCNs equallySpacedARFCNs;
		NhuCarrierFreqsGERANfollowingARFCNsvariableBitMapOfARFCNs variableBitMapOfARFCNs;
	} val;
} NhuCarrierFreqsGERANfollowingARFCNs;

typedef struct NhuCarrierFreqsGERAN
{
	TknPres pres;
	NhuARFCN_ValueGERAN startingARFCN;
	NhuBandIndicatorGERAN bandIndicator;
	NhuCarrierFreqsGERANfollowingARFCNs followingARFCNs;
} NhuCarrierFreqsGERAN;

/* Element ---------- ncc-Permitted ----------- */
typedef TknStrBSXL NhuCarrierFreqsInfoGERANcommonInfoncc_Permitted;
/* Element ----- q-RxLevMin ------- */
typedef TknU32 NhuCarrierFreqsInfoGERANcommonInfoq_RxLevMin;

/* Element ----- p-MaxGERAN ------- */
typedef TknU32 NhuCarrierFreqsInfoGERANcommonInfop_MaxGERAN;

typedef struct NhuCarrierFreqsInfoGERANcommonInfo
{
	TknPres pres;
	NhuCellReselectionPriority cellReselectionPriority;
	NhuCarrierFreqsInfoGERANcommonInfoncc_Permitted ncc_Permitted;
	NhuCarrierFreqsInfoGERANcommonInfoq_RxLevMin q_RxLevMin;
	NhuCarrierFreqsInfoGERANcommonInfop_MaxGERAN p_MaxGERAN;
	NhuReselectionThreshold threshX_High;
	NhuReselectionThreshold threshX_Low;
} NhuCarrierFreqsInfoGERANcommonInfo;

typedef struct NhuCarrierFreqsInfoGERAN
{
	TknPres pres;
	NhuCarrierFreqsGERAN carrierFreqs;
	NhuCarrierFreqsInfoGERANcommonInfo commonInfo;
} NhuCarrierFreqsInfoGERAN;

typedef struct NhuCarrierFreqsInfoLstGERAN
{
	TknU16 noComp;
	NhuCarrierFreqsInfoGERAN *member;
}NhuCarrierFreqsInfoLstGERAN;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp7lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp7
{
	TknPres pres;
	NhuT_Reselection t_ReselectionGERAN;
	NhuSpeedStateScaleFactors t_ReselectionGERAN_SF;
	NhuCarrierFreqsInfoLstGERAN carrierFreqsInfoLst;
	NhuSysInfoBlockTyp7lateNonCriticalExtn lateNonCriticalExtn;
} NhuSysInfoBlockTyp7;

/* Element ----- cdma-EUTRA-Synchronisation ------- */
typedef TknU8 NhuSysTimeInfoCDMA2000cdma_EUTRA_Synchronisation;

/* Element ---------- synchronousSystemTime ----------- */
typedef TknStrBSXL NhuSysTimeInfoCDMA2000cdma_SysTimesynchronousSysTime;
/* Element ---------- asynchronousSystemTime ----------- */
typedef TknStrBSXL NhuSysTimeInfoCDMA2000cdma_SysTimeasynchronousSysTime;
typedef struct NhuSysTimeInfoCDMA2000cdma_SysTime
{
	TknU8 choice;
	union {
		NhuSysTimeInfoCDMA2000cdma_SysTimesynchronousSysTime synchronousSysTime;
		NhuSysTimeInfoCDMA2000cdma_SysTimeasynchronousSysTime asynchronousSysTime;
	} val;
} NhuSysTimeInfoCDMA2000cdma_SysTime;

typedef struct NhuSysTimeInfoCDMA2000
{
	TknPres pres;
	NhuSysTimeInfoCDMA2000cdma_EUTRA_Synchronisation cdma_EUTRA_Synchronisation;
	NhuSysTimeInfoCDMA2000cdma_SysTime cdma_SysTime;
} NhuSysTimeInfoCDMA2000;

/* Element ----- PreRegistrationZoneIdHRPD ------- */
typedef TknU32 NhuPreRegistrationZoneIdHRPD;

typedef struct NhuSecondaryPreRegistrationZoneIdLstHRPD
{
	TknU16 noComp;
	NhuPreRegistrationZoneIdHRPD *member;
}NhuSecondaryPreRegistrationZoneIdLstHRPD;

/* Element ----- preRegistrationAllowed ------- */
typedef TknU8 NhuPreRegistrationInfoHRPDpreRegistrationAllowed;

typedef struct NhuPreRegistrationInfoHRPD
{
	TknPres pres;
	NhuPreRegistrationInfoHRPDpreRegistrationAllowed preRegistrationAllowed;
	NhuPreRegistrationZoneIdHRPD preRegistrationZoneId;
	NhuSecondaryPreRegistrationZoneIdLstHRPD secondaryPreRegistrationZoneIdLst;
} NhuPreRegistrationInfoHRPD;

/* Element ----- BandclassCDMA2000 ------- */
typedef enum enumNhuBandclassCDMA2000
{
	NhuBandclassCDMA2000bc0Enum,
	NhuBandclassCDMA2000bc1Enum,
	NhuBandclassCDMA2000bc2Enum,
	NhuBandclassCDMA2000bc3Enum,
	NhuBandclassCDMA2000bc4Enum,
	NhuBandclassCDMA2000bc5Enum,
	NhuBandclassCDMA2000bc6Enum,
	NhuBandclassCDMA2000bc7Enum,
	NhuBandclassCDMA2000bc8Enum,
	NhuBandclassCDMA2000bc9Enum,
	NhuBandclassCDMA2000bc10Enum,
	NhuBandclassCDMA2000bc11Enum,
	NhuBandclassCDMA2000bc12Enum,
	NhuBandclassCDMA2000bc13Enum,
	NhuBandclassCDMA2000bc14Enum,
	NhuBandclassCDMA2000bc15Enum,
	NhuBandclassCDMA2000bc16Enum,
	NhuBandclassCDMA2000bc17Enum,
	NhuBandclassCDMA2000bc18_v9a0Enum,
	NhuBandclassCDMA2000bc19_v9a0Enum,
	NhuBandclassCDMA2000bc20_v9a0Enum,
	NhuBandclassCDMA2000bc21_v9a0Enum,
	NhuBandclassCDMA2000spare10Enum,
	NhuBandclassCDMA2000spare9Enum,
	NhuBandclassCDMA2000spare8Enum,
	NhuBandclassCDMA2000spare7Enum,
	NhuBandclassCDMA2000spare6Enum,
	NhuBandclassCDMA2000spare5Enum,
	NhuBandclassCDMA2000spare4Enum,
	NhuBandclassCDMA2000spare3Enum,
	NhuBandclassCDMA2000spare2Enum,
	NhuBandclassCDMA2000spare1Enum
} EnumNhuBandclassCDMA2000;
typedef TknU32 NhuBandclassCDMA2000;

/* Element ----- threshX-High ------- */
typedef TknU32 NhuBandClassInfoCDMA2000threshX_High;

/* Element ----- threshX-Low ------- */
typedef TknU32 NhuBandClassInfoCDMA2000threshX_Low;

typedef struct NhuBandClassInfoCDMA2000
{
	TknPres pres;
	NhuBandclassCDMA2000 bandClass;
	NhuCellReselectionPriority cellReselectionPriority;
	NhuBandClassInfoCDMA2000threshX_High threshX_High;
	NhuBandClassInfoCDMA2000threshX_Low threshX_Low;
} NhuBandClassInfoCDMA2000;

typedef struct NhuBandClassLstCDMA2000
{
	TknU16 noComp;
	NhuBandClassInfoCDMA2000 *member;
}NhuBandClassLstCDMA2000;

/* Element ----- ARFCN-ValueCDMA2000 ------- */
typedef TknU32 NhuARFCN_ValueCDMA2000;

/* Element ----- PhysCellIdCDMA2000 ------- */
typedef TknU32 NhuPhysCellIdCDMA2000;

typedef struct NhuPhysCellIdLstCDMA2000
{
	TknU16 noComp;
	NhuPhysCellIdCDMA2000 *member;
}NhuPhysCellIdLstCDMA2000;

typedef struct NhuNeighCellsPerBandclassCDMA2000
{
	TknPres pres;
	NhuARFCN_ValueCDMA2000 arfcn;
	NhuPhysCellIdLstCDMA2000 physCellIdLst;
} NhuNeighCellsPerBandclassCDMA2000;

typedef struct NhuNeighCellsPerBandclassLstCDMA2000
{
	TknU16 noComp;
	NhuNeighCellsPerBandclassCDMA2000 *member;
}NhuNeighCellsPerBandclassLstCDMA2000;

typedef struct NhuNeighCellCDMA2000
{
	TknPres pres;
	NhuBandclassCDMA2000 bandClass;
	NhuNeighCellsPerBandclassLstCDMA2000 neighCellsPerFreqLst;
} NhuNeighCellCDMA2000;

typedef struct NhuNeighCellLstCDMA2000
{
	TknU16 noComp;
	NhuNeighCellCDMA2000 *member;
}NhuNeighCellLstCDMA2000;

typedef struct NhuCellReselectionParamsCDMA2000
{
	TknPres pres;
	NhuBandClassLstCDMA2000 bandClassLst;
	NhuNeighCellLstCDMA2000 neighCellLst;
	NhuT_Reselection t_ReselectionCDMA2000;
	NhuSpeedStateScaleFactors t_ReselectionCDMA2000_SF;
} NhuCellReselectionParamsCDMA2000;

/* Element ---------- sid ----------- */
typedef TknStrBSXL NhuCSFB_RegistrationParam1XRTTsid;
/* Element ---------- nid ----------- */
typedef TknStrBSXL NhuCSFB_RegistrationParam1XRTTnid;
/* Element ----- multipleSID ------- */
typedef TknU8 NhuCSFB_RegistrationParam1XRTTmultipleSID;

/* Element ----- multipleNID ------- */
typedef TknU8 NhuCSFB_RegistrationParam1XRTTmultipleNID;

/* Element ----- homeReg ------- */
typedef TknU8 NhuCSFB_RegistrationParam1XRTThomeReg;

/* Element ----- foreignSIDReg ------- */
typedef TknU8 NhuCSFB_RegistrationParam1XRTTforeignSIDReg;

/* Element ----- foreignNIDReg ------- */
typedef TknU8 NhuCSFB_RegistrationParam1XRTTforeignNIDReg;

/* Element ----- parameterReg ------- */
typedef TknU8 NhuCSFB_RegistrationParam1XRTTparameterReg;

/* Element ----- powerUpReg ------- */
typedef TknU8 NhuCSFB_RegistrationParam1XRTTpowerUpReg;

/* Element ---------- registrationPeriod ----------- */
typedef TknStrBSXL NhuCSFB_RegistrationParam1XRTTregistrationPeriod;
/* Element ---------- registrationZone ----------- */
typedef TknStrBSXL NhuCSFB_RegistrationParam1XRTTregistrationZone;
/* Element ---------- totalZone ----------- */
typedef TknStrBSXL NhuCSFB_RegistrationParam1XRTTtotalZone;
/* Element ---------- zoneTimer ----------- */
typedef TknStrBSXL NhuCSFB_RegistrationParam1XRTTzoneTimer;
typedef struct NhuCSFB_RegistrationParam1XRTT
{
	TknPres pres;
	NhuCSFB_RegistrationParam1XRTTsid sid;
	NhuCSFB_RegistrationParam1XRTTnid nid;
	NhuCSFB_RegistrationParam1XRTTmultipleSID multipleSID;
	NhuCSFB_RegistrationParam1XRTTmultipleNID multipleNID;
	NhuCSFB_RegistrationParam1XRTThomeReg homeReg;
	NhuCSFB_RegistrationParam1XRTTforeignSIDReg foreignSIDReg;
	NhuCSFB_RegistrationParam1XRTTforeignNIDReg foreignNIDReg;
	NhuCSFB_RegistrationParam1XRTTparameterReg parameterReg;
	NhuCSFB_RegistrationParam1XRTTpowerUpReg powerUpReg;
	NhuCSFB_RegistrationParam1XRTTregistrationPeriod registrationPeriod;
	NhuCSFB_RegistrationParam1XRTTregistrationZone registrationZone;
	NhuCSFB_RegistrationParam1XRTTtotalZone totalZone;
	NhuCSFB_RegistrationParam1XRTTzoneTimer zoneTimer;
} NhuCSFB_RegistrationParam1XRTT;

typedef struct NhuPhysCellIdLstCDMA2000_v920
{
	TknU16 noComp;
	NhuPhysCellIdCDMA2000 *member;
}NhuPhysCellIdLstCDMA2000_v920;

typedef struct NhuNeighCellsPerBandclassCDMA2000_v920
{
	TknPres pres;
	NhuPhysCellIdLstCDMA2000_v920 physCellIdLst_v920;
} NhuNeighCellsPerBandclassCDMA2000_v920;

typedef struct NhuNeighCellsPerBandclassLstCDMA2000_v920
{
	TknU16 noComp;
	NhuNeighCellsPerBandclassCDMA2000_v920 *member;
}NhuNeighCellsPerBandclassLstCDMA2000_v920;

typedef struct NhuNeighCellCDMA2000_v920
{
	TknPres pres;
	NhuNeighCellsPerBandclassLstCDMA2000_v920 neighCellsPerFreqLst_v920;
} NhuNeighCellCDMA2000_v920;

typedef struct NhuNeighCellLstCDMA2000_v920
{
	TknU16 noComp;
	NhuNeighCellCDMA2000_v920 *member;
}NhuNeighCellLstCDMA2000_v920;

typedef struct NhuCellReselectionParamsCDMA2000_v920
{
	TknPres pres;
	NhuNeighCellLstCDMA2000_v920 neighCellLst_v920;
} NhuCellReselectionParamsCDMA2000_v920;

/* Element ----- powerDownReg-r9 ------- */
typedef enum enumNhuCSFB_RegistrationParam1XRTT_v920powerDownReg_r9
{
	NhuCSFB_RegistrationParam1XRTT_v920powerDownReg_r9trueEnum
} EnumNhuCSFB_RegistrationParam1XRTT_v920powerDownReg_r9;
typedef TknU32 NhuCSFB_RegistrationParam1XRTT_v920powerDownReg_r9;

typedef struct NhuCSFB_RegistrationParam1XRTT_v920
{
	TknPres pres;
	NhuCSFB_RegistrationParam1XRTT_v920powerDownReg_r9 powerDownReg_r9;
} NhuCSFB_RegistrationParam1XRTT_v920;

/* Element ----- ac-Barring0to9-r9 ------- */
typedef TknU32 NhuAC_BarringConfig1XRTT_r9ac_Barring0to9_r9;

/* Element ----- ac-Barring10-r9 ------- */
typedef TknU32 NhuAC_BarringConfig1XRTT_r9ac_Barring10_r9;

/* Element ----- ac-Barring11-r9 ------- */
typedef TknU32 NhuAC_BarringConfig1XRTT_r9ac_Barring11_r9;

/* Element ----- ac-Barring12-r9 ------- */
typedef TknU32 NhuAC_BarringConfig1XRTT_r9ac_Barring12_r9;

/* Element ----- ac-Barring13-r9 ------- */
typedef TknU32 NhuAC_BarringConfig1XRTT_r9ac_Barring13_r9;

/* Element ----- ac-Barring14-r9 ------- */
typedef TknU32 NhuAC_BarringConfig1XRTT_r9ac_Barring14_r9;

/* Element ----- ac-Barring15-r9 ------- */
typedef TknU32 NhuAC_BarringConfig1XRTT_r9ac_Barring15_r9;

/* Element ----- ac-BarringMsg-r9 ------- */
typedef TknU32 NhuAC_BarringConfig1XRTT_r9ac_BarringMsg_r9;

/* Element ----- ac-BarringReg-r9 ------- */
typedef TknU32 NhuAC_BarringConfig1XRTT_r9ac_BarringReg_r9;

/* Element ----- ac-BarringEmg-r9 ------- */
typedef TknU32 NhuAC_BarringConfig1XRTT_r9ac_BarringEmg_r9;

typedef struct NhuAC_BarringConfig1XRTT_r9
{
	TknPres pres;
	NhuAC_BarringConfig1XRTT_r9ac_Barring0to9_r9 ac_Barring0to9_r9;
	NhuAC_BarringConfig1XRTT_r9ac_Barring10_r9 ac_Barring10_r9;
	NhuAC_BarringConfig1XRTT_r9ac_Barring11_r9 ac_Barring11_r9;
	NhuAC_BarringConfig1XRTT_r9ac_Barring12_r9 ac_Barring12_r9;
	NhuAC_BarringConfig1XRTT_r9ac_Barring13_r9 ac_Barring13_r9;
	NhuAC_BarringConfig1XRTT_r9ac_Barring14_r9 ac_Barring14_r9;
	NhuAC_BarringConfig1XRTT_r9ac_Barring15_r9 ac_Barring15_r9;
	NhuAC_BarringConfig1XRTT_r9ac_BarringMsg_r9 ac_BarringMsg_r9;
	NhuAC_BarringConfig1XRTT_r9ac_BarringReg_r9 ac_BarringReg_r9;
	NhuAC_BarringConfig1XRTT_r9ac_BarringEmg_r9 ac_BarringEmg_r9;
} NhuAC_BarringConfig1XRTT_r9;

typedef struct NhuNeighCellsPerBandclassCDMA2000_r11physCellIdLst_r11
{
	TknU16 noComp;
	NhuPhysCellIdCDMA2000 *member;
}NhuNeighCellsPerBandclassCDMA2000_r11physCellIdLst_r11;

typedef struct NhuNeighCellsPerBandclassCDMA2000_r11
{
	TknPres pres;
	NhuARFCN_ValueCDMA2000 arfcn;
	NhuNeighCellsPerBandclassCDMA2000_r11physCellIdLst_r11 physCellIdLst_r11;
} NhuNeighCellsPerBandclassCDMA2000_r11;

typedef struct NhuNeighCellCDMA2000_r11neighFreqInfoLst_r11
{
	TknU16 noComp;
	NhuNeighCellsPerBandclassCDMA2000_r11 *member;
}NhuNeighCellCDMA2000_r11neighFreqInfoLst_r11;

typedef struct NhuNeighCellCDMA2000_r11
{
	TknPres pres;
	NhuBandclassCDMA2000 bandClass;
	NhuNeighCellCDMA2000_r11neighFreqInfoLst_r11 neighFreqInfoLst_r11;
} NhuNeighCellCDMA2000_r11;

typedef struct NhuCellReselectionParamsCDMA2000_r11neighCellLst_r11
{
	TknU16 noComp;
	NhuNeighCellCDMA2000_r11 *member;
}NhuCellReselectionParamsCDMA2000_r11neighCellLst_r11;

typedef struct NhuCellReselectionParamsCDMA2000_r11
{
	TknPres pres;
	NhuBandClassLstCDMA2000 bandClassLst;
	NhuCellReselectionParamsCDMA2000_r11neighCellLst_r11 neighCellLst_r11;
	NhuT_Reselection t_ReselectionCDMA2000;
	NhuSpeedStateScaleFactors t_ReselectionCDMA2000_SF;
} NhuCellReselectionParamsCDMA2000_r11;

typedef struct NhuParamsCDMA2000_r11systemTimeInfo_r11
{
	TknU8 choice;
	union {
		NhuSysTimeInfoCDMA2000 explicitValue;
	} val;
} NhuParamsCDMA2000_r11systemTimeInfo_r11;

/* Element ----- searchWindowSize-r11 ------- */
typedef TknU32 NhuParamsCDMA2000_r11searchWindowSize_r11;

typedef struct NhuParamsCDMA2000_r11parametersHRPD_r11
{
	TknPres pres;
	NhuPreRegistrationInfoHRPD preRegistrationInfoHRPD_r11;
	NhuCellReselectionParamsCDMA2000_r11 cellReselectionParamsHRPD_r11;
} NhuParamsCDMA2000_r11parametersHRPD_r11;

/* Element ---------- longCodeState1XRTT-r11 ----------- */
typedef TknStrBSXL NhuParamsCDMA2000_r11parameters1XRTT_r11longCodeState1XRTT_r11;
/* Element ----- csfb-SupportForDualRxUEs-r11 ------- */
typedef TknU8 NhuParamsCDMA2000_r11parameters1XRTT_r11csfb_SupportForDualRxUEs_r11;

/* Element ----- csfb-DualRxTxSupport-r11 ------- */
typedef enum enumNhuParamsCDMA2000_r11parameters1XRTT_r11csfb_DualRxTxSupport_r11
{
	NhuParamsCDMA2000_r11parameters1XRTT_r11csfb_DualRxTxSupport_r11trueEnum
} EnumNhuParamsCDMA2000_r11parameters1XRTT_r11csfb_DualRxTxSupport_r11;
typedef TknU32 NhuParamsCDMA2000_r11parameters1XRTT_r11csfb_DualRxTxSupport_r11;

typedef struct NhuParamsCDMA2000_r11parameters1XRTT_r11
{
	TknPres pres;
	NhuCSFB_RegistrationParam1XRTT csfb_RegistrationParam1XRTT_r11;
	NhuCSFB_RegistrationParam1XRTT_v920 csfb_RegistrationParam1XRTT_Ext_r11;
	NhuParamsCDMA2000_r11parameters1XRTT_r11longCodeState1XRTT_r11 longCodeState1XRTT_r11;
	NhuCellReselectionParamsCDMA2000_r11 cellReselectionParams1XRTT_r11;
	NhuAC_BarringConfig1XRTT_r9 ac_BarringConfig1XRTT_r11;
	NhuParamsCDMA2000_r11parameters1XRTT_r11csfb_SupportForDualRxUEs_r11 csfb_SupportForDualRxUEs_r11;
	NhuParamsCDMA2000_r11parameters1XRTT_r11csfb_DualRxTxSupport_r11 csfb_DualRxTxSupport_r11;
} NhuParamsCDMA2000_r11parameters1XRTT_r11;

typedef struct NhuParamsCDMA2000_r11
{
	TknPres pres;
	NhuParamsCDMA2000_r11systemTimeInfo_r11 systemTimeInfo_r11;
	NhuParamsCDMA2000_r11searchWindowSize_r11 searchWindowSize_r11;
	NhuParamsCDMA2000_r11parametersHRPD_r11 parametersHRPD_r11;
	NhuParamsCDMA2000_r11parameters1XRTT_r11 parameters1XRTT_r11;
} NhuParamsCDMA2000_r11;

/* Element ----- plmn-Identity-r11 ------- */
typedef TknU32 NhuSIB8_PerPLMN_r11plmn_Identity_r11;

typedef struct NhuSIB8_PerPLMN_r11parametersCDMA2000_r11
{
	TknU8 choice;
	union {
		NhuParamsCDMA2000_r11 explicitValue;
	} val;
} NhuSIB8_PerPLMN_r11parametersCDMA2000_r11;

typedef struct NhuSIB8_PerPLMN_r11
{
	TknPres pres;
	NhuSIB8_PerPLMN_r11plmn_Identity_r11 plmn_Identity_r11;
	NhuSIB8_PerPLMN_r11parametersCDMA2000_r11 parametersCDMA2000_r11;
} NhuSIB8_PerPLMN_r11;

typedef struct NhuSIB8_PerPLMN_Lst_r11
{
	TknU16 noComp;
	NhuSIB8_PerPLMN_r11 *member;
}NhuSIB8_PerPLMN_Lst_r11;

/* Element ----- searchWindowSize ------- */
typedef TknU32 NhuSysInfoBlockTyp8searchWindowSize;

typedef struct NhuSysInfoBlockTyp8parametersHRPD
{
	TknPres pres;
	NhuPreRegistrationInfoHRPD preRegistrationInfoHRPD;
	NhuCellReselectionParamsCDMA2000 cellReselectionParamsHRPD;
} NhuSysInfoBlockTyp8parametersHRPD;

/* Element ---------- longCodeState1XRTT ----------- */
typedef TknStrBSXL NhuSysInfoBlockTyp8parameters1XRTTlongCodeState1XRTT;
typedef struct NhuSysInfoBlockTyp8parameters1XRTT
{
	TknPres pres;
	NhuCSFB_RegistrationParam1XRTT csfb_RegistrationParam1XRTT;
	NhuSysInfoBlockTyp8parameters1XRTTlongCodeState1XRTT longCodeState1XRTT;
	NhuCellReselectionParamsCDMA2000 cellReselectionParams1XRTT;
} NhuSysInfoBlockTyp8parameters1XRTT;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp8lateNonCriticalExtn;
/* Element ----- csfb-SupportForDualRxUEs-r9 ------- */
typedef TknU8 NhuSysInfoBlockTyp8extaddgrp_1csfb_SupportForDualRxUEs_r9;

/* Element ----- csfb-DualRxTxSupport-r10 ------- */
typedef enum enumNhuSysInfoBlockTyp8extaddgrp_2csfb_DualRxTxSupport_r10
{
	NhuSysInfoBlockTyp8extaddgrp_2csfb_DualRxTxSupport_r10trueEnum
} EnumNhuSysInfoBlockTyp8extaddgrp_2csfb_DualRxTxSupport_r10;
typedef TknU32 NhuSysInfoBlockTyp8extaddgrp_2csfb_DualRxTxSupport_r10;

typedef struct NhuSysInfoBlockTyp8extaddgrp_1
{
	TknPres pres;
	NhuSysInfoBlockTyp8extaddgrp_1csfb_SupportForDualRxUEs_r9 csfb_SupportForDualRxUEs_r9;
	NhuCellReselectionParamsCDMA2000_v920 cellReselectionParamsHRPD_v920;
	NhuCellReselectionParamsCDMA2000_v920 cellReselectionParams1XRTT_v920;
	NhuCSFB_RegistrationParam1XRTT_v920 csfb_RegistrationParam1XRTT_v920;
	NhuAC_BarringConfig1XRTT_r9 ac_BarringConfig1XRTT_r9;
} NhuSysInfoBlockTyp8extaddgrp_1;

typedef struct NhuSysInfoBlockTyp8extaddgrp_2
{
	TknPres pres;
	NhuSysInfoBlockTyp8extaddgrp_2csfb_DualRxTxSupport_r10 csfb_DualRxTxSupport_r10;
} NhuSysInfoBlockTyp8extaddgrp_2;

typedef struct NhuSysInfoBlockTyp8extaddgrp_3
{
	TknPres pres;
	NhuSIB8_PerPLMN_Lst_r11 sib8_PerPLMN_Lst_r11;
} NhuSysInfoBlockTyp8extaddgrp_3;

typedef struct NhuSysInfoBlockTyp8
{
	TknPres pres;
	NhuSysTimeInfoCDMA2000 systemTimeInfo;
	NhuSysInfoBlockTyp8searchWindowSize searchWindowSize;
	NhuSysInfoBlockTyp8parametersHRPD parametersHRPD;
	NhuSysInfoBlockTyp8parameters1XRTT parameters1XRTT;
	NhuSysInfoBlockTyp8lateNonCriticalExtn lateNonCriticalExtn;
	NhuSysInfoBlockTyp8extaddgrp_1 extaddgrp_1;
	NhuSysInfoBlockTyp8extaddgrp_2 extaddgrp_2;
	NhuSysInfoBlockTyp8extaddgrp_3 extaddgrp_3;
} NhuSysInfoBlockTyp8;

/* Element ---------- hnb-Name ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp9hnb_Name;
/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp9lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp9
{
	TknPres pres;
	NhuSysInfoBlockTyp9hnb_Name hnb_Name;
	NhuSysInfoBlockTyp9lateNonCriticalExtn lateNonCriticalExtn;
} NhuSysInfoBlockTyp9;

/* Element ---------- messageIdentifier ----------- */
typedef TknStrBSXL NhuSysInfoBlockTyp10messageId;
/* Element ---------- serialNumber ----------- */
typedef TknStrBSXL NhuSysInfoBlockTyp10serialNumber;
/* Element ---------- warningType ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp10warningTyp;
/* Element ---------- dummy ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp10dummy;
/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp10lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp10
{
	TknPres pres;
	NhuSysInfoBlockTyp10messageId messageId;
	NhuSysInfoBlockTyp10serialNumber serialNumber;
	NhuSysInfoBlockTyp10warningTyp warningTyp;
	NhuSysInfoBlockTyp10dummy dummy;
	NhuSysInfoBlockTyp10lateNonCriticalExtn lateNonCriticalExtn;
} NhuSysInfoBlockTyp10;

/* Element ---------- messageIdentifier ----------- */
typedef TknStrBSXL NhuSysInfoBlockTyp11messageId;
/* Element ---------- serialNumber ----------- */
typedef TknStrBSXL NhuSysInfoBlockTyp11serialNumber;
/* Element ----- warningMessageSegmentType ------- */
typedef enum enumNhuSysInfoBlockTyp11warningMsgSegmentTyp
{
	NhuSysInfoBlockTyp11warningMsgSegmentTypnotLastSegmentEnum,
	NhuSysInfoBlockTyp11warningMsgSegmentTyplastSegmentEnum
} EnumNhuSysInfoBlockTyp11warningMsgSegmentTyp;
typedef TknU32 NhuSysInfoBlockTyp11warningMsgSegmentTyp;

/* Element ----- warningMessageSegmentNumber ------- */
typedef TknU32 NhuSysInfoBlockTyp11warningMsgSegmentNumber;

/* Element ---------- warningMessageSegment ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp11warningMsgSegment;
/* Element ---------- dataCodingScheme ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp11dataCodingScheme;
/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp11lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp11
{
	TknPres pres;
	NhuSysInfoBlockTyp11messageId messageId;
	NhuSysInfoBlockTyp11serialNumber serialNumber;
	NhuSysInfoBlockTyp11warningMsgSegmentTyp warningMsgSegmentTyp;
	NhuSysInfoBlockTyp11warningMsgSegmentNumber warningMsgSegmentNumber;
	NhuSysInfoBlockTyp11warningMsgSegment warningMsgSegment;
	NhuSysInfoBlockTyp11dataCodingScheme dataCodingScheme;
	NhuSysInfoBlockTyp11lateNonCriticalExtn lateNonCriticalExtn;
} NhuSysInfoBlockTyp11;

/* Element ---------- messageIdentifier-r9 ----------- */
typedef TknStrBSXL NhuSysInfoBlockTyp12_r9messageId_r9;
/* Element ---------- serialNumber-r9 ----------- */
typedef TknStrBSXL NhuSysInfoBlockTyp12_r9serialNumber_r9;
/* Element ----- warningMessageSegmentType-r9 ------- */
typedef enum enumNhuSysInfoBlockTyp12_r9warningMsgSegmentTyp_r9
{
	NhuSysInfoBlockTyp12_r9warningMsgSegmentTyp_r9notLastSegmentEnum,
	NhuSysInfoBlockTyp12_r9warningMsgSegmentTyp_r9lastSegmentEnum
} EnumNhuSysInfoBlockTyp12_r9warningMsgSegmentTyp_r9;
typedef TknU32 NhuSysInfoBlockTyp12_r9warningMsgSegmentTyp_r9;

/* Element ----- warningMessageSegmentNumber-r9 ------- */
typedef TknU32 NhuSysInfoBlockTyp12_r9warningMsgSegmentNumber_r9;

/* Element ---------- warningMessageSegment-r9 ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp12_r9warningMsgSegment_r9;
/* Element ---------- dataCodingScheme-r9 ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp12_r9dataCodingScheme_r9;
/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp12_r9lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp12_r9
{
	TknPres pres;
	NhuSysInfoBlockTyp12_r9messageId_r9 messageId_r9;
	NhuSysInfoBlockTyp12_r9serialNumber_r9 serialNumber_r9;
	NhuSysInfoBlockTyp12_r9warningMsgSegmentTyp_r9 warningMsgSegmentTyp_r9;
	NhuSysInfoBlockTyp12_r9warningMsgSegmentNumber_r9 warningMsgSegmentNumber_r9;
	NhuSysInfoBlockTyp12_r9warningMsgSegment_r9 warningMsgSegment_r9;
	NhuSysInfoBlockTyp12_r9dataCodingScheme_r9 dataCodingScheme_r9;
	NhuSysInfoBlockTyp12_r9lateNonCriticalExtn lateNonCriticalExtn;
} NhuSysInfoBlockTyp12_r9;

/* Element ----- mbsfn-AreaId-r9 ------- */
typedef TknU32 NhuMBSFN_AreaInfo_r9mbsfn_AreaId_r9;

/* Element ----- non-MBSFNregionLength ------- */
typedef enum enumNhuMBSFN_AreaInfo_r9non_MBSFNregionLength
{
	NhuMBSFN_AreaInfo_r9non_MBSFNregionLengths1Enum,
	NhuMBSFN_AreaInfo_r9non_MBSFNregionLengths2Enum
} EnumNhuMBSFN_AreaInfo_r9non_MBSFNregionLength;
typedef TknU32 NhuMBSFN_AreaInfo_r9non_MBSFNregionLength;

/* Element ----- notificationIndicator-r9 ------- */
typedef TknU32 NhuMBSFN_AreaInfo_r9notificationIndicator_r9;

/* Element ----- mcch-RepetitionPeriod-r9 ------- */
typedef enum enumNhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_RepetitionPeriod_r9
{
	NhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_RepetitionPeriod_r9rf32Enum,
	NhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_RepetitionPeriod_r9rf64Enum,
	NhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_RepetitionPeriod_r9rf128Enum,
	NhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_RepetitionPeriod_r9rf256Enum
} EnumNhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_RepetitionPeriod_r9;
typedef TknU32 NhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_RepetitionPeriod_r9;

/* Element ----- mcch-Offset-r9 ------- */
typedef TknU32 NhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_Offset_r9;

/* Element ----- mcch-ModificationPeriod-r9 ------- */
typedef enum enumNhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_ModfnPeriod_r9
{
	NhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_ModfnPeriod_r9rf512Enum,
	NhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_ModfnPeriod_r9rf1024Enum
} EnumNhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_ModfnPeriod_r9;
typedef TknU32 NhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_ModfnPeriod_r9;

/* Element ---------- sf-AllocInfo-r9 ----------- */
typedef TknStrBSXL NhuMBSFN_AreaInfo_r9mcch_Config_r9sf_AllocInfo_r9;
/* Element ----- signallingMCS-r9 ------- */
typedef enum enumNhuMBSFN_AreaInfo_r9mcch_Config_r9signallingMCS_r9
{
	NhuMBSFN_AreaInfo_r9mcch_Config_r9signallingMCS_r9n2Enum,
	NhuMBSFN_AreaInfo_r9mcch_Config_r9signallingMCS_r9n7Enum,
	NhuMBSFN_AreaInfo_r9mcch_Config_r9signallingMCS_r9n13Enum,
	NhuMBSFN_AreaInfo_r9mcch_Config_r9signallingMCS_r9n19Enum
} EnumNhuMBSFN_AreaInfo_r9mcch_Config_r9signallingMCS_r9;
typedef TknU32 NhuMBSFN_AreaInfo_r9mcch_Config_r9signallingMCS_r9;

typedef struct NhuMBSFN_AreaInfo_r9mcch_Config_r9
{
	TknPres pres;
	NhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_RepetitionPeriod_r9 mcch_RepetitionPeriod_r9;
	NhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_Offset_r9 mcch_Offset_r9;
	NhuMBSFN_AreaInfo_r9mcch_Config_r9mcch_ModfnPeriod_r9 mcch_ModfnPeriod_r9;
	NhuMBSFN_AreaInfo_r9mcch_Config_r9sf_AllocInfo_r9 sf_AllocInfo_r9;
	NhuMBSFN_AreaInfo_r9mcch_Config_r9signallingMCS_r9 signallingMCS_r9;
} NhuMBSFN_AreaInfo_r9mcch_Config_r9;

typedef struct NhuMBSFN_AreaInfo_r9
{
	TknPres pres;
	NhuMBSFN_AreaInfo_r9mbsfn_AreaId_r9 mbsfn_AreaId_r9;
	NhuMBSFN_AreaInfo_r9non_MBSFNregionLength non_MBSFNregionLength;
	NhuMBSFN_AreaInfo_r9notificationIndicator_r9 notificationIndicator_r9;
	NhuMBSFN_AreaInfo_r9mcch_Config_r9 mcch_Config_r9;
} NhuMBSFN_AreaInfo_r9;

typedef struct NhuMBSFN_AreaInfoLst_r9
{
	TknU16 noComp;
	NhuMBSFN_AreaInfo_r9 *member;
}NhuMBSFN_AreaInfoLst_r9;

/* Element ----- notificationRepetitionCoeff-r9 ------- */
typedef enum enumNhuMBMS_NotificationConfig_r9notificationRepetitionCoeff_r9
{
	NhuMBMS_NotificationConfig_r9notificationRepetitionCoeff_r9n2Enum,
	NhuMBMS_NotificationConfig_r9notificationRepetitionCoeff_r9n4Enum
} EnumNhuMBMS_NotificationConfig_r9notificationRepetitionCoeff_r9;
typedef TknU32 NhuMBMS_NotificationConfig_r9notificationRepetitionCoeff_r9;

/* Element ----- notificationOffset-r9 ------- */
typedef TknU32 NhuMBMS_NotificationConfig_r9notificationOffset_r9;

/* Element ----- notificationSF-Index-r9 ------- */
typedef TknU32 NhuMBMS_NotificationConfig_r9notificationSF_Idx_r9;

typedef struct NhuMBMS_NotificationConfig_r9
{
	TknPres pres;
	NhuMBMS_NotificationConfig_r9notificationRepetitionCoeff_r9 notificationRepetitionCoeff_r9;
	NhuMBMS_NotificationConfig_r9notificationOffset_r9 notificationOffset_r9;
	NhuMBMS_NotificationConfig_r9notificationSF_Idx_r9 notificationSF_Idx_r9;
} NhuMBMS_NotificationConfig_r9;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp13_r9lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp13_r9
{
	TknPres pres;
	NhuMBSFN_AreaInfoLst_r9 mbsfn_AreaInfoLst_r9;
	NhuMBMS_NotificationConfig_r9 notificationConfig_r9;
	NhuSysInfoBlockTyp13_r9lateNonCriticalExtn lateNonCriticalExtn;
} NhuSysInfoBlockTyp13_r9;

/* Element ----- eab-Category-r11 ------- */
typedef enum enumNhuEAB_Config_r11eab_Category_r11
{
	NhuEAB_Config_r11eab_Category_r11aEnum,
	NhuEAB_Config_r11eab_Category_r11bEnum,
	NhuEAB_Config_r11eab_Category_r11cEnum
} EnumNhuEAB_Config_r11eab_Category_r11;
typedef TknU32 NhuEAB_Config_r11eab_Category_r11;

/* Element ---------- eab-BarringBitmap-r11 ----------- */
typedef TknStrBSXL NhuEAB_Config_r11eab_BarringBitmap_r11;
typedef struct NhuEAB_Config_r11
{
	TknPres pres;
	NhuEAB_Config_r11eab_Category_r11 eab_Category_r11;
	NhuEAB_Config_r11eab_BarringBitmap_r11 eab_BarringBitmap_r11;
} NhuEAB_Config_r11;

typedef struct NhuEAB_ConfigPLMN_r11
{
	TknPres pres;
	NhuEAB_Config_r11 eab_Config_r11;
} NhuEAB_ConfigPLMN_r11;

typedef struct NhuSysInfoBlockTyp14_r11eab_Param_r11eab_PerPLMN_Lst_r11
{
	TknU16 noComp;
	NhuEAB_ConfigPLMN_r11 *member;
}NhuSysInfoBlockTyp14_r11eab_Param_r11eab_PerPLMN_Lst_r11;

typedef struct NhuSysInfoBlockTyp14_r11eab_Param_r11
{
	TknU8 choice;
	union {
		NhuEAB_Config_r11 eab_Cmn_r11;
		NhuSysInfoBlockTyp14_r11eab_Param_r11eab_PerPLMN_Lst_r11 eab_PerPLMN_Lst_r11;
	} val;
} NhuSysInfoBlockTyp14_r11eab_Param_r11;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp14_r11lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp14_r11
{
	TknPres pres;
	NhuSysInfoBlockTyp14_r11eab_Param_r11 eab_Param_r11;
	NhuSysInfoBlockTyp14_r11lateNonCriticalExtn lateNonCriticalExtn;
} NhuSysInfoBlockTyp14_r11;

/* Element ----- MBMS-SAI-r11 ------- */
typedef TknU32 NhuMBMS_SAI_r11;

typedef struct NhuMBMS_SAI_Lst_r11
{
	TknU16 noComp;
	NhuMBMS_SAI_r11 *member;
}NhuMBMS_SAI_Lst_r11;

/* Element ----- ARFCN-ValueEUTRA-r9 ------- */
typedef TknU32 NhuARFCN_ValueEUTRA_r9;

typedef struct NhuMBMS_SAI_InterFreq_r11
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_r9 dl_CarrierFreq_r11;
	NhuMBMS_SAI_Lst_r11 mbms_SAI_Lst_r11;
} NhuMBMS_SAI_InterFreq_r11;

typedef struct NhuMBMS_SAI_InterFreqLst_r11
{
	TknU16 noComp;
	NhuMBMS_SAI_InterFreq_r11 *member;
}NhuMBMS_SAI_InterFreqLst_r11;

/* Element ----- FreqBandIndicator-r11 ------- */
typedef TknU32 NhuFreqBandIndicator_r11;

typedef struct NhuMultiBandInfoLst_r11
{
	TknU16 noComp;
	NhuFreqBandIndicator_r11 *member;
}NhuMultiBandInfoLst_r11;

typedef struct NhuMBMS_SAI_InterFreq_v1140
{
	TknPres pres;
	NhuMultiBandInfoLst_r11 multiBandInfoLst_r11;
} NhuMBMS_SAI_InterFreq_v1140;

typedef struct NhuMBMS_SAI_InterFreqLst_v1140
{
	TknU16 noComp;
	NhuMBMS_SAI_InterFreq_v1140 *member;
}NhuMBMS_SAI_InterFreqLst_v1140;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp15_r11lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp15_r11extaddgrp_1
{
	TknPres pres;
	NhuMBMS_SAI_InterFreqLst_v1140 mbms_SAI_InterFreqLst_v1140;
} NhuSysInfoBlockTyp15_r11extaddgrp_1;

typedef struct NhuSysInfoBlockTyp15_r11
{
	TknPres pres;
	NhuMBMS_SAI_Lst_r11 mbms_SAI_IntraFreq_r11;
	NhuMBMS_SAI_InterFreqLst_r11 mbms_SAI_InterFreqLst_r11;
	NhuSysInfoBlockTyp15_r11lateNonCriticalExtn lateNonCriticalExtn;
	NhuSysInfoBlockTyp15_r11extaddgrp_1 extaddgrp_1;
} NhuSysInfoBlockTyp15_r11;

/* Element ----- timeInfoUTC-r11 ------- */
typedef TknU32 NhuSysInfoBlockTyp16_r11timeInfo_r11timeInfoUTC_r11;

/* Element ---------- dayLightSavingTime-r11 ----------- */
typedef TknStrBSXL NhuSysInfoBlockTyp16_r11timeInfo_r11dayLightSavingTime_r11;
/* Element ----- leapSeconds-r11 ------- */
typedef TknS32 NhuSysInfoBlockTyp16_r11timeInfo_r11leapSeconds_r11;

/* Element ----- localTimeOffset-r11 ------- */
typedef TknS32 NhuSysInfoBlockTyp16_r11timeInfo_r11localTimeOffset_r11;

typedef struct NhuSysInfoBlockTyp16_r11timeInfo_r11
{
	TknPres pres;
	NhuSysInfoBlockTyp16_r11timeInfo_r11timeInfoUTC_r11 timeInfoUTC_r11;
	NhuSysInfoBlockTyp16_r11timeInfo_r11dayLightSavingTime_r11 dayLightSavingTime_r11;
	NhuSysInfoBlockTyp16_r11timeInfo_r11leapSeconds_r11 leapSeconds_r11;
	NhuSysInfoBlockTyp16_r11timeInfo_r11localTimeOffset_r11 localTimeOffset_r11;
} NhuSysInfoBlockTyp16_r11timeInfo_r11;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp16_r11lateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp16_r11
{
	TknPres pres;
	NhuSysInfoBlockTyp16_r11timeInfo_r11 timeInfo_r11;
	NhuSysInfoBlockTyp16_r11lateNonCriticalExtn lateNonCriticalExtn;
} NhuSysInfoBlockTyp16_r11;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfo_v8a0_IEslateNonCriticalExtn;
typedef struct NhuSysInfo_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuSysInfo_v8a0_IEsnonCriticalExtn;

typedef struct NhuSysInfo_v8a0_IEs
{
	TknPres pres;
	NhuSysInfo_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuSysInfo_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuSysInfo_v8a0_IEs;

typedef struct NhuSysInfo_r8_IEssib_TypAndInfoMember
{
	TknU8 choice;
	union {
		NhuSysInfoBlockTyp2 sib2;
		NhuSysInfoBlockTyp3 sib3;
		NhuSysInfoBlockTyp4 sib4;
		NhuSysInfoBlockTyp5 sib5;
		NhuSysInfoBlockTyp6 sib6;
		NhuSysInfoBlockTyp7 sib7;
		NhuSysInfoBlockTyp8 sib8;
		NhuSysInfoBlockTyp9 sib9;
		NhuSysInfoBlockTyp10 sib10;
		NhuSysInfoBlockTyp11 sib11;
		NhuSysInfoBlockTyp12_r9 sib12_v920;
		NhuSysInfoBlockTyp13_r9 sib13_v920;
		NhuSysInfoBlockTyp14_r11 sib14_v1130;
		NhuSysInfoBlockTyp15_r11 sib15_v1130;
		NhuSysInfoBlockTyp16_r11 sib16_v1130;
	} val;
} NhuSysInfo_r8_IEssib_TypAndInfoMember;

typedef struct NhuSysInfo_r8_IEssib_TypAndInfo
{
	TknU16 noComp;
	NhuSysInfo_r8_IEssib_TypAndInfoMember *member;
}NhuSysInfo_r8_IEssib_TypAndInfo;

typedef struct NhuSysInfo_r8_IEs
{
	TknPres pres;
	NhuSysInfo_r8_IEssib_TypAndInfo sib_TypAndInfo;
	NhuSysInfo_v8a0_IEs nonCriticalExtn;
} NhuSysInfo_r8_IEs;

typedef struct NhuSysInfocriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuSysInfocriticalExtnscriticalExtnsFuture;

typedef struct NhuSysInfocriticalExtns
{
	TknU8 choice;
	union {
		NhuSysInfo_r8_IEs systemInfo_r8;
		NhuSysInfocriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuSysInfocriticalExtns;

typedef struct NhuSysInfo
{
	TknPres pres;
	NhuSysInfocriticalExtns criticalExtns;
} NhuSysInfo;

/* Element ----- MCC-MNC-Digit ------- */
typedef TknU32 NhuMCC_MNC_Digit;

typedef struct NhuMCC
{
	TknU16 noComp;
	NhuMCC_MNC_Digit *member;
}NhuMCC;

typedef struct NhuMNC
{
	TknU16 noComp;
	NhuMCC_MNC_Digit *member;
}NhuMNC;

typedef struct NhuPLMN_Identity
{
	TknPres pres;
	NhuMCC mcc;
	NhuMNC mnc;
} NhuPLMN_Identity;

/* Element ----- cellReservedForOperatorUse ------- */
typedef enum enumNhuPLMN_IdentityInfocellReservedForOperatorUse
{
	NhuPLMN_IdentityInfocellReservedForOperatorUsereservedEnum,
	NhuPLMN_IdentityInfocellReservedForOperatorUsenotReservedEnum
} EnumNhuPLMN_IdentityInfocellReservedForOperatorUse;
typedef TknU32 NhuPLMN_IdentityInfocellReservedForOperatorUse;

typedef struct NhuPLMN_IdentityInfo
{
	TknPres pres;
	NhuPLMN_Identity plmn_Identity;
	NhuPLMN_IdentityInfocellReservedForOperatorUse cellReservedForOperatorUse;
} NhuPLMN_IdentityInfo;

typedef struct NhuPLMN_IdentityLst
{
	TknU16 noComp;
	NhuPLMN_IdentityInfo *member;
}NhuPLMN_IdentityLst;

/* Element ---------- TrackingAreaCode ----------- */
typedef TknStrBSXL NhuTrackingAreaCode;
/* Element ---------- CellIdentity ----------- */
typedef TknStrBSXL NhuCellIdentity;
/* Element ---------- CSG-Identity ----------- */
typedef TknStrBSXL NhuCSG_Identity;
/* Element ----- FreqBandIndicator ------- */
typedef TknU32 NhuFreqBandIndicator;

/* Element ----- SIB-Type ------- */
typedef enum enumNhuSIB_Typ
{
	NhuSIB_TypsibTyp3Enum,
	NhuSIB_TypsibTyp4Enum,
	NhuSIB_TypsibTyp5Enum,
	NhuSIB_TypsibTyp6Enum,
	NhuSIB_TypsibTyp7Enum,
	NhuSIB_TypsibTyp8Enum,
	NhuSIB_TypsibTyp9Enum,
	NhuSIB_TypsibTyp10Enum,
	NhuSIB_TypsibTyp11Enum,
	NhuSIB_TypsibTyp12_v920Enum,
	NhuSIB_TypsibTyp13_v920Enum,
	NhuSIB_TypsibTyp14_v1130Enum,
	NhuSIB_TypsibTyp15_v1130Enum,
	NhuSIB_TypsibTyp16_v1130Enum,
	NhuSIB_Typspare2Enum,
	NhuSIB_Typspare1Enum
} EnumNhuSIB_Typ;
typedef TknU32 NhuSIB_Typ;

typedef struct NhuSIB_MappingInfo
{
	TknU16 noComp;
	NhuSIB_Typ *member;
}NhuSIB_MappingInfo;

/* Element ----- si-Periodicity ------- */
typedef enum enumNhuSchedulingInfosi_Periodicity
{
	NhuSchedulingInfosi_Periodicityrf8Enum,
	NhuSchedulingInfosi_Periodicityrf16Enum,
	NhuSchedulingInfosi_Periodicityrf32Enum,
	NhuSchedulingInfosi_Periodicityrf64Enum,
	NhuSchedulingInfosi_Periodicityrf128Enum,
	NhuSchedulingInfosi_Periodicityrf256Enum,
	NhuSchedulingInfosi_Periodicityrf512Enum
} EnumNhuSchedulingInfosi_Periodicity;
typedef TknU32 NhuSchedulingInfosi_Periodicity;

typedef struct NhuSchedulingInfo
{
	TknPres pres;
	NhuSchedulingInfosi_Periodicity si_Periodicity;
	NhuSIB_MappingInfo sib_MappingInfo;
} NhuSchedulingInfo;

typedef struct NhuSchedulingInfoLst
{
	TknU16 noComp;
	NhuSchedulingInfo *member;
}NhuSchedulingInfoLst;

/* Element ----- subframeAssignment ------- */
typedef enum enumNhuTDD_ConfigsubframeAssignment
{
	NhuTDD_ConfigsubframeAssignmentsa0Enum,
	NhuTDD_ConfigsubframeAssignmentsa1Enum,
	NhuTDD_ConfigsubframeAssignmentsa2Enum,
	NhuTDD_ConfigsubframeAssignmentsa3Enum,
	NhuTDD_ConfigsubframeAssignmentsa4Enum,
	NhuTDD_ConfigsubframeAssignmentsa5Enum,
	NhuTDD_ConfigsubframeAssignmentsa6Enum
} EnumNhuTDD_ConfigsubframeAssignment;
typedef TknU32 NhuTDD_ConfigsubframeAssignment;

/* Element ----- specialSubframePatterns ------- */
typedef enum enumNhuTDD_ConfigspecialSubfrmPatterns
{
	NhuTDD_ConfigspecialSubfrmPatternsssp0Enum,
	NhuTDD_ConfigspecialSubfrmPatternsssp1Enum,
	NhuTDD_ConfigspecialSubfrmPatternsssp2Enum,
	NhuTDD_ConfigspecialSubfrmPatternsssp3Enum,
	NhuTDD_ConfigspecialSubfrmPatternsssp4Enum,
	NhuTDD_ConfigspecialSubfrmPatternsssp5Enum,
	NhuTDD_ConfigspecialSubfrmPatternsssp6Enum,
	NhuTDD_ConfigspecialSubfrmPatternsssp7Enum,
	NhuTDD_ConfigspecialSubfrmPatternsssp8Enum
} EnumNhuTDD_ConfigspecialSubfrmPatterns;
typedef TknU32 NhuTDD_ConfigspecialSubfrmPatterns;

typedef struct NhuTDD_Config
{
	TknPres pres;
	NhuTDD_ConfigsubframeAssignment subframeAssignment;
	NhuTDD_ConfigspecialSubfrmPatterns specialSubfrmPatterns;
} NhuTDD_Config;

/* Element ----- q-QualMinOffset-r9 ------- */
typedef TknU32 NhuCellSelectionInfo_v920q_QualMinOffset_r9;

typedef struct NhuCellSelectionInfo_v920
{
	TknPres pres;
	NhuQ_QualMin_r9 q_QualMin_r9;
	NhuCellSelectionInfo_v920q_QualMinOffset_r9 q_QualMinOffset_r9;
} NhuCellSelectionInfo_v920;

/* Element ----- specialSubframePatterns-v1130 ------- */
typedef enum enumNhuTDD_Config_v1130specialSubfrmPatterns_v1130
{
	NhuTDD_Config_v1130specialSubfrmPatterns_v1130ssp7Enum,
	NhuTDD_Config_v1130specialSubfrmPatterns_v1130ssp9Enum
} EnumNhuTDD_Config_v1130specialSubfrmPatterns_v1130;
typedef TknU32 NhuTDD_Config_v1130specialSubfrmPatterns_v1130;

typedef struct NhuTDD_Config_v1130
{
	TknPres pres;
	NhuTDD_Config_v1130specialSubfrmPatterns_v1130 specialSubfrmPatterns_v1130;
} NhuTDD_Config_v1130;

typedef struct NhuCellSelectionInfo_v1130
{
	TknPres pres;
	NhuQ_QualMin_r9 q_QualMinWB_r11;
} NhuCellSelectionInfo_v1130;

typedef struct NhuSysInfoBlockTyp1_v1130_IEsnonCriticalExtn
{
	TknPres pres;
} NhuSysInfoBlockTyp1_v1130_IEsnonCriticalExtn;

typedef struct NhuSysInfoBlockTyp1_v1130_IEs
{
	TknPres pres;
	NhuTDD_Config_v1130 tdd_Config_v1130;
	NhuCellSelectionInfo_v1130 cellSelectionInfo_v1130;
	NhuSysInfoBlockTyp1_v1130_IEsnonCriticalExtn nonCriticalExtn;
} NhuSysInfoBlockTyp1_v1130_IEs;

/* Element ----- ims-EmergencySupport-r9 ------- */
typedef enum enumNhuSysInfoBlockTyp1_v920_IEsims_EmergencySupport_r9
{
	NhuSysInfoBlockTyp1_v920_IEsims_EmergencySupport_r9trueEnum
} EnumNhuSysInfoBlockTyp1_v920_IEsims_EmergencySupport_r9;
typedef TknU32 NhuSysInfoBlockTyp1_v920_IEsims_EmergencySupport_r9;

typedef struct NhuSysInfoBlockTyp1_v920_IEs
{
	TknPres pres;
	NhuSysInfoBlockTyp1_v920_IEsims_EmergencySupport_r9 ims_EmergencySupport_r9;
	NhuCellSelectionInfo_v920 cellSelectionInfo_v920;
	NhuSysInfoBlockTyp1_v1130_IEs nonCriticalExtn;
} NhuSysInfoBlockTyp1_v920_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSysInfoBlockTyp1_v890_IEslateNonCriticalExtn;
typedef struct NhuSysInfoBlockTyp1_v890_IEs
{
	TknPres pres;
	NhuSysInfoBlockTyp1_v890_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuSysInfoBlockTyp1_v920_IEs nonCriticalExtn;
} NhuSysInfoBlockTyp1_v890_IEs;

/* Element ----- cellBarred ------- */
typedef enum enumNhuSysInfoBlockTyp1cellAccessRelatedInfocellBarred
{
	NhuSysInfoBlockTyp1cellAccessRelatedInfocellBarredbarredEnum,
	NhuSysInfoBlockTyp1cellAccessRelatedInfocellBarrednotBarredEnum
} EnumNhuSysInfoBlockTyp1cellAccessRelatedInfocellBarred;
typedef TknU32 NhuSysInfoBlockTyp1cellAccessRelatedInfocellBarred;

/* Element ----- intraFreqReselection ------- */
typedef enum enumNhuSysInfoBlockTyp1cellAccessRelatedInfointraFreqReselection
{
	NhuSysInfoBlockTyp1cellAccessRelatedInfointraFreqReselectionallowedEnum,
	NhuSysInfoBlockTyp1cellAccessRelatedInfointraFreqReselectionnotAllowedEnum
} EnumNhuSysInfoBlockTyp1cellAccessRelatedInfointraFreqReselection;
typedef TknU32 NhuSysInfoBlockTyp1cellAccessRelatedInfointraFreqReselection;

/* Element ----- csg-Indication ------- */
typedef TknU8 NhuSysInfoBlockTyp1cellAccessRelatedInfocsg_Ind;

typedef struct NhuSysInfoBlockTyp1cellAccessRelatedInfo
{
	TknPres pres;
	NhuPLMN_IdentityLst plmn_IdentityLst;
	NhuTrackingAreaCode trackingAreaCode;
	NhuCellIdentity cellIdentity;
	NhuSysInfoBlockTyp1cellAccessRelatedInfocellBarred cellBarred;
	NhuSysInfoBlockTyp1cellAccessRelatedInfointraFreqReselection intraFreqReselection;
	NhuSysInfoBlockTyp1cellAccessRelatedInfocsg_Ind csg_Ind;
	NhuCSG_Identity csg_Identity;
} NhuSysInfoBlockTyp1cellAccessRelatedInfo;

/* Element ----- q-RxLevMinOffset ------- */
typedef TknU32 NhuSysInfoBlockTyp1cellSelectionInfoq_RxLevMinOffset;

typedef struct NhuSysInfoBlockTyp1cellSelectionInfo
{
	TknPres pres;
	NhuQ_RxLevMin q_RxLevMin;
	NhuSysInfoBlockTyp1cellSelectionInfoq_RxLevMinOffset q_RxLevMinOffset;
} NhuSysInfoBlockTyp1cellSelectionInfo;

/* Element ----- si-WindowLength ------- */
typedef enum enumNhuSysInfoBlockTyp1si_WindowLength
{
	NhuSysInfoBlockTyp1si_WindowLengthms1Enum,
	NhuSysInfoBlockTyp1si_WindowLengthms2Enum,
	NhuSysInfoBlockTyp1si_WindowLengthms5Enum,
	NhuSysInfoBlockTyp1si_WindowLengthms10Enum,
	NhuSysInfoBlockTyp1si_WindowLengthms15Enum,
	NhuSysInfoBlockTyp1si_WindowLengthms20Enum,
	NhuSysInfoBlockTyp1si_WindowLengthms40Enum
} EnumNhuSysInfoBlockTyp1si_WindowLength;
typedef TknU32 NhuSysInfoBlockTyp1si_WindowLength;

/* Element ----- systemInfoValueTag ------- */
typedef TknU32 NhuSysInfoBlockTyp1systemInfoValueTag;

typedef struct NhuSysInfoBlockTyp1
{
	TknPres pres;
	NhuSysInfoBlockTyp1cellAccessRelatedInfo cellAccessRelatedInfo;
	NhuSysInfoBlockTyp1cellSelectionInfo cellSelectionInfo;
	NhuP_Max p_Max;
	NhuFreqBandIndicator freqBandIndicator;
	NhuSchedulingInfoLst schedulingInfoLst;
	NhuTDD_Config tdd_Config;
	NhuSysInfoBlockTyp1si_WindowLength si_WindowLength;
	NhuSysInfoBlockTyp1systemInfoValueTag systemInfoValueTag;
	NhuSysInfoBlockTyp1_v890_IEs nonCriticalExtn;
} NhuSysInfoBlockTyp1;

typedef struct NhuBCCH_DL_SCH_MsgTypc1
{
	TknU8 choice;
	union {
		NhuSysInfo systemInfo;
		NhuSysInfoBlockTyp1 systemInfoBlockTyp1;
	} val;
} NhuBCCH_DL_SCH_MsgTypc1;

typedef struct NhuBCCH_DL_SCH_MsgTypmessageClassExtn
{
	TknPres pres;
} NhuBCCH_DL_SCH_MsgTypmessageClassExtn;

typedef struct NhuBCCH_DL_SCH_MsgTyp
{
	TknU8 choice;
	union {
		NhuBCCH_DL_SCH_MsgTypc1 c1;
		NhuBCCH_DL_SCH_MsgTypmessageClassExtn messageClassExtn;
	} val;
} NhuBCCH_DL_SCH_MsgTyp;

typedef struct NhuBCCH_DL_SCH_Msg
{
	TknPres pres;
	NhuBCCH_DL_SCH_MsgTyp message;
} NhuBCCH_DL_SCH_Msg;

typedef struct NhuCmnSF_AllocPatternLst_r9
{
	TknU16 noComp;
	NhuMBSFN_SubfrmConfig *member;
}NhuCmnSF_AllocPatternLst_r9;

/* Element ----- sf-AllocEnd-r9 ------- */
typedef TknU32 NhuPMCH_Config_r9sf_AllocEnd_r9;

/* Element ----- dataMCS-r9 ------- */
typedef TknU32 NhuPMCH_Config_r9dataMCS_r9;

/* Element ----- mch-SchedulingPeriod-r9 ------- */
typedef enum enumNhuPMCH_Config_r9mch_SchedulingPeriod_r9
{
	NhuPMCH_Config_r9mch_SchedulingPeriod_r9rf8Enum,
	NhuPMCH_Config_r9mch_SchedulingPeriod_r9rf16Enum,
	NhuPMCH_Config_r9mch_SchedulingPeriod_r9rf32Enum,
	NhuPMCH_Config_r9mch_SchedulingPeriod_r9rf64Enum,
	NhuPMCH_Config_r9mch_SchedulingPeriod_r9rf128Enum,
	NhuPMCH_Config_r9mch_SchedulingPeriod_r9rf256Enum,
	NhuPMCH_Config_r9mch_SchedulingPeriod_r9rf512Enum,
	NhuPMCH_Config_r9mch_SchedulingPeriod_r9rf1024Enum
} EnumNhuPMCH_Config_r9mch_SchedulingPeriod_r9;
typedef TknU32 NhuPMCH_Config_r9mch_SchedulingPeriod_r9;

typedef struct NhuPMCH_Config_r9
{
	TknPres pres;
	NhuPMCH_Config_r9sf_AllocEnd_r9 sf_AllocEnd_r9;
	NhuPMCH_Config_r9dataMCS_r9 dataMCS_r9;
	NhuPMCH_Config_r9mch_SchedulingPeriod_r9 mch_SchedulingPeriod_r9;
} NhuPMCH_Config_r9;

/* Element ----- plmn-Index-r9 ------- */
typedef TknU32 NhuTMGI_r9plmn_Id_r9plmn_Idx_r9;

typedef struct NhuTMGI_r9plmn_Id_r9
{
	TknU8 choice;
	union {
		NhuTMGI_r9plmn_Id_r9plmn_Idx_r9 plmn_Idx_r9;
		NhuPLMN_Identity explicitValue_r9;
	} val;
} NhuTMGI_r9plmn_Id_r9;

/* Element ---------- serviceId-r9 ----------- */
typedef TknStrOSXL NhuTMGI_r9serviceId_r9;
typedef struct NhuTMGI_r9
{
	TknPres pres;
	NhuTMGI_r9plmn_Id_r9 plmn_Id_r9;
	NhuTMGI_r9serviceId_r9 serviceId_r9;
} NhuTMGI_r9;

/* Element ---------- sessionId-r9 ----------- */
typedef TknStrOSXL NhuMBMS_SessionInfo_r9sessionId_r9;
/* Element ----- logicalChannelIdentity-r9 ------- */
typedef TknU32 NhuMBMS_SessionInfo_r9logicalChannelIdentity_r9;

typedef struct NhuMBMS_SessionInfo_r9
{
	TknPres pres;
	NhuTMGI_r9 tmgi_r9;
	NhuMBMS_SessionInfo_r9sessionId_r9 sessionId_r9;
	NhuMBMS_SessionInfo_r9logicalChannelIdentity_r9 logicalChannelIdentity_r9;
} NhuMBMS_SessionInfo_r9;

typedef struct NhuMBMS_SessionInfoLst_r9
{
	TknU16 noComp;
	NhuMBMS_SessionInfo_r9 *member;
}NhuMBMS_SessionInfoLst_r9;

typedef struct NhuPMCH_Info_r9
{
	TknPres pres;
	NhuPMCH_Config_r9 pmch_Config_r9;
	NhuMBMS_SessionInfoLst_r9 mbms_SessionInfoLst_r9;
} NhuPMCH_Info_r9;

typedef struct NhuPMCH_InfoLst_r9
{
	TknU16 noComp;
	NhuPMCH_Info_r9 *member;
}NhuPMCH_InfoLst_r9;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuMBSFNAreaCfg_v930_IEslateNonCriticalExtn;
typedef struct NhuMBSFNAreaCfg_v930_IEsnonCriticalExtn
{
	TknPres pres;
} NhuMBSFNAreaCfg_v930_IEsnonCriticalExtn;

typedef struct NhuMBSFNAreaCfg_v930_IEs
{
	TknPres pres;
	NhuMBSFNAreaCfg_v930_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuMBSFNAreaCfg_v930_IEsnonCriticalExtn nonCriticalExtn;
} NhuMBSFNAreaCfg_v930_IEs;

/* Element ----- commonSF-AllocPeriod-r9 ------- */
typedef enum enumNhuMBSFNAreaCfg_r9commonSF_AllocPeriod_r9
{
	NhuMBSFNAreaCfg_r9commonSF_AllocPeriod_r9rf4Enum,
	NhuMBSFNAreaCfg_r9commonSF_AllocPeriod_r9rf8Enum,
	NhuMBSFNAreaCfg_r9commonSF_AllocPeriod_r9rf16Enum,
	NhuMBSFNAreaCfg_r9commonSF_AllocPeriod_r9rf32Enum,
	NhuMBSFNAreaCfg_r9commonSF_AllocPeriod_r9rf64Enum,
	NhuMBSFNAreaCfg_r9commonSF_AllocPeriod_r9rf128Enum,
	NhuMBSFNAreaCfg_r9commonSF_AllocPeriod_r9rf256Enum
} EnumNhuMBSFNAreaCfg_r9commonSF_AllocPeriod_r9;
typedef TknU32 NhuMBSFNAreaCfg_r9commonSF_AllocPeriod_r9;

typedef struct NhuMBSFNAreaCfg_r9
{
	TknPres pres;
	NhuCmnSF_AllocPatternLst_r9 commonSF_Alloc_r9;
	NhuMBSFNAreaCfg_r9commonSF_AllocPeriod_r9 commonSF_AllocPeriod_r9;
	NhuPMCH_InfoLst_r9 pmch_InfoLst_r9;
	NhuMBSFNAreaCfg_v930_IEs nonCriticalExtn;
} NhuMBSFNAreaCfg_r9;

typedef struct NhuCountingRqstInfo_r10
{
	TknPres pres;
	NhuTMGI_r9 tmgi_r10;
} NhuCountingRqstInfo_r10;

typedef struct NhuCountingRqstLst_r10
{
	TknU16 noComp;
	NhuCountingRqstInfo_r10 *member;
}NhuCountingRqstLst_r10;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuMBMSCountingRqst_r10lateNonCriticalExtn;
typedef struct NhuMBMSCountingRqst_r10nonCriticalExtn
{
	TknPres pres;
} NhuMBMSCountingRqst_r10nonCriticalExtn;

typedef struct NhuMBMSCountingRqst_r10
{
	TknPres pres;
	NhuCountingRqstLst_r10 countingRqstLst_r10;
	NhuMBMSCountingRqst_r10lateNonCriticalExtn lateNonCriticalExtn;
	NhuMBMSCountingRqst_r10nonCriticalExtn nonCriticalExtn;
} NhuMBMSCountingRqst_r10;

typedef struct NhuMCCH_MsgTypc1
{
	TknU8 choice;
	union {
		NhuMBSFNAreaCfg_r9 mbsfnAreaCfg_r9;
	} val;
} NhuMCCH_MsgTypc1;

typedef struct NhuMCCH_MsgTyplaterc2
{
	TknU8 choice;
	union {
		NhuMBMSCountingRqst_r10 mbmsCountingRqst_r10;
	} val;
} NhuMCCH_MsgTyplaterc2;

typedef struct NhuMCCH_MsgTyplatermessageClassExtn
{
	TknPres pres;
} NhuMCCH_MsgTyplatermessageClassExtn;

typedef struct NhuMCCH_MsgTyplater
{
	TknU8 choice;
	union {
		NhuMCCH_MsgTyplaterc2 c2;
		NhuMCCH_MsgTyplatermessageClassExtn messageClassExtn;
	} val;
} NhuMCCH_MsgTyplater;

typedef struct NhuMCCH_MsgTyp
{
	TknU8 choice;
	union {
		NhuMCCH_MsgTypc1 c1;
		NhuMCCH_MsgTyplater later;
	} val;
} NhuMCCH_MsgTyp;

typedef struct NhuMCCH_Msg
{
	TknPres pres;
	NhuMCCH_MsgTyp message;
} NhuMCCH_Msg;

/* Element ---------- MMEC ----------- */
typedef TknStrBSXL NhuMMEC;
/* Element ---------- m-TMSI ----------- */
typedef TknStrBSXL NhuS_TMSIm_TMSI;
typedef struct NhuS_TMSI
{
	TknPres pres;
	NhuMMEC mmec;
	NhuS_TMSIm_TMSI m_TMSI;
} NhuS_TMSI;

/* Element ----- IMSI-Digit ------- */
typedef TknU32 NhuIMSI_Digit;

typedef struct NhuIMSI
{
	TknU16 noComp;
	NhuIMSI_Digit *member;
}NhuIMSI;

typedef struct NhuPagUE_Identity
{
	TknU8 choice;
	union {
		NhuS_TMSI s_TMSI;
		NhuIMSI imsi;
	} val;
} NhuPagUE_Identity;

/* Element ----- cn-Domain ------- */
typedef enum enumNhuPagRecordcn_Domain
{
	NhuPagRecordcn_DomainpsEnum,
	NhuPagRecordcn_DomaincsEnum
} EnumNhuPagRecordcn_Domain;
typedef TknU32 NhuPagRecordcn_Domain;

typedef struct NhuPagRecord
{
	TknPres pres;
	NhuPagUE_Identity ue_Identity;
	NhuPagRecordcn_Domain cn_Domain;
} NhuPagRecord;

typedef struct NhuPagRecordLst
{
	TknU16 noComp;
	NhuPagRecord *member;
}NhuPagRecordLst;

/* Element ----- eab-ParamModification-r11 ------- */
typedef enum enumNhuPag_v1130_IEseab_ParamModfn_r11
{
	NhuPag_v1130_IEseab_ParamModfn_r11trueEnum
} EnumNhuPag_v1130_IEseab_ParamModfn_r11;
typedef TknU32 NhuPag_v1130_IEseab_ParamModfn_r11;

typedef struct NhuPag_v1130_IEsnonCriticalExtn
{
	TknPres pres;
} NhuPag_v1130_IEsnonCriticalExtn;

typedef struct NhuPag_v1130_IEs
{
	TknPres pres;
	NhuPag_v1130_IEseab_ParamModfn_r11 eab_ParamModfn_r11;
	NhuPag_v1130_IEsnonCriticalExtn nonCriticalExtn;
} NhuPag_v1130_IEs;

/* Element ----- cmas-Indication-r9 ------- */
typedef enum enumNhuPag_v920_IEscmas_Ind_r9
{
	NhuPag_v920_IEscmas_Ind_r9trueEnum
} EnumNhuPag_v920_IEscmas_Ind_r9;
typedef TknU32 NhuPag_v920_IEscmas_Ind_r9;

typedef struct NhuPag_v920_IEs
{
	TknPres pres;
	NhuPag_v920_IEscmas_Ind_r9 cmas_Ind_r9;
	NhuPag_v1130_IEs nonCriticalExtn;
} NhuPag_v920_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuPag_v890_IEslateNonCriticalExtn;
typedef struct NhuPag_v890_IEs
{
	TknPres pres;
	NhuPag_v890_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuPag_v920_IEs nonCriticalExtn;
} NhuPag_v890_IEs;

/* Element ----- systemInfoModification ------- */
typedef enum enumNhuPagsystemInfoModfn
{
	NhuPagsystemInfoModfntrueEnum
} EnumNhuPagsystemInfoModfn;
typedef TknU32 NhuPagsystemInfoModfn;

/* Element ----- etws-Indication ------- */
typedef enum enumNhuPagetws_Ind
{
	NhuPagetws_IndtrueEnum
} EnumNhuPagetws_Ind;
typedef TknU32 NhuPagetws_Ind;

typedef struct NhuPag
{
	TknPres pres;
	NhuPagRecordLst pagingRecordLst;
	NhuPagsystemInfoModfn systemInfoModfn;
	NhuPagetws_Ind etws_Ind;
	NhuPag_v890_IEs nonCriticalExtn;
} NhuPag;

typedef struct NhuPCCH_MsgTypc1
{
	TknU8 choice;
	union {
		NhuPag paging;
	} val;
} NhuPCCH_MsgTypc1;

typedef struct NhuPCCH_MsgTypmessageClassExtn
{
	TknPres pres;
} NhuPCCH_MsgTypmessageClassExtn;

typedef struct NhuPCCH_MsgTyp
{
	TknU8 choice;
	union {
		NhuPCCH_MsgTypc1 c1;
		NhuPCCH_MsgTypmessageClassExtn messageClassExtn;
	} val;
} NhuPCCH_MsgTyp;

typedef struct NhuPCCH_Msg
{
	TknPres pres;
	NhuPCCH_MsgTyp message;
} NhuPCCH_Msg;

/* Element ----- RRC-TransactionIdentifier ------- */
typedef TknU32 NhuRRC_TrnsxnId;

/* Element ----- T-PollRetransmit ------- */
typedef enum enumNhuT_PollRetransmit
{
	NhuT_PollRetransmitms5Enum,
	NhuT_PollRetransmitms10Enum,
	NhuT_PollRetransmitms15Enum,
	NhuT_PollRetransmitms20Enum,
	NhuT_PollRetransmitms25Enum,
	NhuT_PollRetransmitms30Enum,
	NhuT_PollRetransmitms35Enum,
	NhuT_PollRetransmitms40Enum,
	NhuT_PollRetransmitms45Enum,
	NhuT_PollRetransmitms50Enum,
	NhuT_PollRetransmitms55Enum,
	NhuT_PollRetransmitms60Enum,
	NhuT_PollRetransmitms65Enum,
	NhuT_PollRetransmitms70Enum,
	NhuT_PollRetransmitms75Enum,
	NhuT_PollRetransmitms80Enum,
	NhuT_PollRetransmitms85Enum,
	NhuT_PollRetransmitms90Enum,
	NhuT_PollRetransmitms95Enum,
	NhuT_PollRetransmitms100Enum,
	NhuT_PollRetransmitms105Enum,
	NhuT_PollRetransmitms110Enum,
	NhuT_PollRetransmitms115Enum,
	NhuT_PollRetransmitms120Enum,
	NhuT_PollRetransmitms125Enum,
	NhuT_PollRetransmitms130Enum,
	NhuT_PollRetransmitms135Enum,
	NhuT_PollRetransmitms140Enum,
	NhuT_PollRetransmitms145Enum,
	NhuT_PollRetransmitms150Enum,
	NhuT_PollRetransmitms155Enum,
	NhuT_PollRetransmitms160Enum,
	NhuT_PollRetransmitms165Enum,
	NhuT_PollRetransmitms170Enum,
	NhuT_PollRetransmitms175Enum,
	NhuT_PollRetransmitms180Enum,
	NhuT_PollRetransmitms185Enum,
	NhuT_PollRetransmitms190Enum,
	NhuT_PollRetransmitms195Enum,
	NhuT_PollRetransmitms200Enum,
	NhuT_PollRetransmitms205Enum,
	NhuT_PollRetransmitms210Enum,
	NhuT_PollRetransmitms215Enum,
	NhuT_PollRetransmitms220Enum,
	NhuT_PollRetransmitms225Enum,
	NhuT_PollRetransmitms230Enum,
	NhuT_PollRetransmitms235Enum,
	NhuT_PollRetransmitms240Enum,
	NhuT_PollRetransmitms245Enum,
	NhuT_PollRetransmitms250Enum,
	NhuT_PollRetransmitms300Enum,
	NhuT_PollRetransmitms350Enum,
	NhuT_PollRetransmitms400Enum,
	NhuT_PollRetransmitms450Enum,
	NhuT_PollRetransmitms500Enum,
	NhuT_PollRetransmitspare9Enum,
	NhuT_PollRetransmitspare8Enum,
	NhuT_PollRetransmitspare7Enum,
	NhuT_PollRetransmitspare6Enum,
	NhuT_PollRetransmitspare5Enum,
	NhuT_PollRetransmitspare4Enum,
	NhuT_PollRetransmitspare3Enum,
	NhuT_PollRetransmitspare2Enum,
	NhuT_PollRetransmitspare1Enum
} EnumNhuT_PollRetransmit;
typedef TknU32 NhuT_PollRetransmit;

/* Element ----- PollPDU ------- */
typedef enum enumNhuPollPDU
{
	NhuPollPDUp4Enum,
	NhuPollPDUp8Enum,
	NhuPollPDUp16Enum,
	NhuPollPDUp32Enum,
	NhuPollPDUp64Enum,
	NhuPollPDUp128Enum,
	NhuPollPDUp256Enum,
	NhuPollPDUpInfinityEnum
} EnumNhuPollPDU;
typedef TknU32 NhuPollPDU;

/* Element ----- PollByte ------- */
typedef enum enumNhuPollByte
{
	NhuPollBytekB25Enum,
	NhuPollBytekB50Enum,
	NhuPollBytekB75Enum,
	NhuPollBytekB100Enum,
	NhuPollBytekB125Enum,
	NhuPollBytekB250Enum,
	NhuPollBytekB375Enum,
	NhuPollBytekB500Enum,
	NhuPollBytekB750Enum,
	NhuPollBytekB1000Enum,
	NhuPollBytekB1250Enum,
	NhuPollBytekB1500Enum,
	NhuPollBytekB2000Enum,
	NhuPollBytekB3000Enum,
	NhuPollBytekBinfinityEnum,
	NhuPollBytespare1Enum
} EnumNhuPollByte;
typedef TknU32 NhuPollByte;

/* Element ----- maxRetxThreshold ------- */
typedef enum enumNhuUL_AM_RLCmaxRetxThreshold
{
	NhuUL_AM_RLCmaxRetxThresholdt1Enum,
	NhuUL_AM_RLCmaxRetxThresholdt2Enum,
	NhuUL_AM_RLCmaxRetxThresholdt3Enum,
	NhuUL_AM_RLCmaxRetxThresholdt4Enum,
	NhuUL_AM_RLCmaxRetxThresholdt6Enum,
	NhuUL_AM_RLCmaxRetxThresholdt8Enum,
	NhuUL_AM_RLCmaxRetxThresholdt16Enum,
	NhuUL_AM_RLCmaxRetxThresholdt32Enum
} EnumNhuUL_AM_RLCmaxRetxThreshold;
typedef TknU32 NhuUL_AM_RLCmaxRetxThreshold;

typedef struct NhuUL_AM_RLC
{
	TknPres pres;
	NhuT_PollRetransmit t_PollRetransmit;
	NhuPollPDU pollPDU;
	NhuPollByte pollByte;
	NhuUL_AM_RLCmaxRetxThreshold maxRetxThreshold;
} NhuUL_AM_RLC;

/* Element ----- T-Reordering ------- */
typedef enum enumNhuT_Reordering
{
	NhuT_Reorderingms0Enum,
	NhuT_Reorderingms5Enum,
	NhuT_Reorderingms10Enum,
	NhuT_Reorderingms15Enum,
	NhuT_Reorderingms20Enum,
	NhuT_Reorderingms25Enum,
	NhuT_Reorderingms30Enum,
	NhuT_Reorderingms35Enum,
	NhuT_Reorderingms40Enum,
	NhuT_Reorderingms45Enum,
	NhuT_Reorderingms50Enum,
	NhuT_Reorderingms55Enum,
	NhuT_Reorderingms60Enum,
	NhuT_Reorderingms65Enum,
	NhuT_Reorderingms70Enum,
	NhuT_Reorderingms75Enum,
	NhuT_Reorderingms80Enum,
	NhuT_Reorderingms85Enum,
	NhuT_Reorderingms90Enum,
	NhuT_Reorderingms95Enum,
	NhuT_Reorderingms100Enum,
	NhuT_Reorderingms110Enum,
	NhuT_Reorderingms120Enum,
	NhuT_Reorderingms130Enum,
	NhuT_Reorderingms140Enum,
	NhuT_Reorderingms150Enum,
	NhuT_Reorderingms160Enum,
	NhuT_Reorderingms170Enum,
	NhuT_Reorderingms180Enum,
	NhuT_Reorderingms190Enum,
	NhuT_Reorderingms200Enum,
	NhuT_Reorderingspare1Enum
} EnumNhuT_Reordering;
typedef TknU32 NhuT_Reordering;

/* Element ----- T-StatusProhibit ------- */
typedef enum enumNhuT_StatusProhibit
{
	NhuT_StatusProhibitms0Enum,
	NhuT_StatusProhibitms5Enum,
	NhuT_StatusProhibitms10Enum,
	NhuT_StatusProhibitms15Enum,
	NhuT_StatusProhibitms20Enum,
	NhuT_StatusProhibitms25Enum,
	NhuT_StatusProhibitms30Enum,
	NhuT_StatusProhibitms35Enum,
	NhuT_StatusProhibitms40Enum,
	NhuT_StatusProhibitms45Enum,
	NhuT_StatusProhibitms50Enum,
	NhuT_StatusProhibitms55Enum,
	NhuT_StatusProhibitms60Enum,
	NhuT_StatusProhibitms65Enum,
	NhuT_StatusProhibitms70Enum,
	NhuT_StatusProhibitms75Enum,
	NhuT_StatusProhibitms80Enum,
	NhuT_StatusProhibitms85Enum,
	NhuT_StatusProhibitms90Enum,
	NhuT_StatusProhibitms95Enum,
	NhuT_StatusProhibitms100Enum,
	NhuT_StatusProhibitms105Enum,
	NhuT_StatusProhibitms110Enum,
	NhuT_StatusProhibitms115Enum,
	NhuT_StatusProhibitms120Enum,
	NhuT_StatusProhibitms125Enum,
	NhuT_StatusProhibitms130Enum,
	NhuT_StatusProhibitms135Enum,
	NhuT_StatusProhibitms140Enum,
	NhuT_StatusProhibitms145Enum,
	NhuT_StatusProhibitms150Enum,
	NhuT_StatusProhibitms155Enum,
	NhuT_StatusProhibitms160Enum,
	NhuT_StatusProhibitms165Enum,
	NhuT_StatusProhibitms170Enum,
	NhuT_StatusProhibitms175Enum,
	NhuT_StatusProhibitms180Enum,
	NhuT_StatusProhibitms185Enum,
	NhuT_StatusProhibitms190Enum,
	NhuT_StatusProhibitms195Enum,
	NhuT_StatusProhibitms200Enum,
	NhuT_StatusProhibitms205Enum,
	NhuT_StatusProhibitms210Enum,
	NhuT_StatusProhibitms215Enum,
	NhuT_StatusProhibitms220Enum,
	NhuT_StatusProhibitms225Enum,
	NhuT_StatusProhibitms230Enum,
	NhuT_StatusProhibitms235Enum,
	NhuT_StatusProhibitms240Enum,
	NhuT_StatusProhibitms245Enum,
	NhuT_StatusProhibitms250Enum,
	NhuT_StatusProhibitms300Enum,
	NhuT_StatusProhibitms350Enum,
	NhuT_StatusProhibitms400Enum,
	NhuT_StatusProhibitms450Enum,
	NhuT_StatusProhibitms500Enum,
	NhuT_StatusProhibitspare8Enum,
	NhuT_StatusProhibitspare7Enum,
	NhuT_StatusProhibitspare6Enum,
	NhuT_StatusProhibitspare5Enum,
	NhuT_StatusProhibitspare4Enum,
	NhuT_StatusProhibitspare3Enum,
	NhuT_StatusProhibitspare2Enum,
	NhuT_StatusProhibitspare1Enum
} EnumNhuT_StatusProhibit;
typedef TknU32 NhuT_StatusProhibit;

typedef struct NhuDL_AM_RLC
{
	TknPres pres;
	NhuT_Reordering t_Reordering;
	NhuT_StatusProhibit t_StatusProhibit;
} NhuDL_AM_RLC;

/* Element ----- SN-FieldLength ------- */
typedef enum enumNhuSN_FieldLength
{
	NhuSN_FieldLengthsize5Enum,
	NhuSN_FieldLengthsize10Enum
} EnumNhuSN_FieldLength;
typedef TknU32 NhuSN_FieldLength;

typedef struct NhuUL_UM_RLC
{
	TknPres pres;
	NhuSN_FieldLength sn_FieldLength;
} NhuUL_UM_RLC;

typedef struct NhuDL_UM_RLC
{
	TknPres pres;
	NhuSN_FieldLength sn_FieldLength;
	NhuT_Reordering t_Reordering;
} NhuDL_UM_RLC;

typedef struct NhuRLC_Configam
{
	TknPres pres;
	NhuUL_AM_RLC ul_AM_RLC;
	NhuDL_AM_RLC dl_AM_RLC;
} NhuRLC_Configam;

typedef struct NhuRLC_Configum_Bi_Directional
{
	TknPres pres;
	NhuUL_UM_RLC ul_UM_RLC;
	NhuDL_UM_RLC dl_UM_RLC;
} NhuRLC_Configum_Bi_Directional;

typedef struct NhuRLC_Configum_Uni_Directional_UL
{
	TknPres pres;
	NhuUL_UM_RLC ul_UM_RLC;
} NhuRLC_Configum_Uni_Directional_UL;

typedef struct NhuRLC_Configum_Uni_Directional_DL
{
	TknPres pres;
	NhuDL_UM_RLC dl_UM_RLC;
} NhuRLC_Configum_Uni_Directional_DL;

typedef struct NhuRLC_Config
{
	TknU8 choice;
	union {
		NhuRLC_Configam am;
		NhuRLC_Configum_Bi_Directional um_Bi_Directional;
		NhuRLC_Configum_Uni_Directional_UL um_Uni_Directional_UL;
		NhuRLC_Configum_Uni_Directional_DL um_Uni_Directional_DL;
	} val;
} NhuRLC_Config;

/* Element ----- priority ------- */
typedef TknU32 NhuLogChannelConfigul_SpecificParamspriority;

/* Element ----- prioritisedBitRate ------- */
typedef enum enumNhuLogChannelConfigul_SpecificParamsprioritisedBitRate
{
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatekBps0Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatekBps8Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatekBps16Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatekBps32Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatekBps64Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatekBps128Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatekBps256Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRateinfinityEnum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatekBps512_v1020Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatekBps1024_v1020Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatekBps2048_v1020Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatespare5Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatespare4Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatespare3Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatespare2Enum,
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRatespare1Enum
} EnumNhuLogChannelConfigul_SpecificParamsprioritisedBitRate;
typedef TknU32 NhuLogChannelConfigul_SpecificParamsprioritisedBitRate;

/* Element ----- bucketSizeDuration ------- */
typedef enum enumNhuLogChannelConfigul_SpecificParamsbucketSizeDuration
{
	NhuLogChannelConfigul_SpecificParamsbucketSizeDurationms50Enum,
	NhuLogChannelConfigul_SpecificParamsbucketSizeDurationms100Enum,
	NhuLogChannelConfigul_SpecificParamsbucketSizeDurationms150Enum,
	NhuLogChannelConfigul_SpecificParamsbucketSizeDurationms300Enum,
	NhuLogChannelConfigul_SpecificParamsbucketSizeDurationms500Enum,
	NhuLogChannelConfigul_SpecificParamsbucketSizeDurationms1000Enum,
	NhuLogChannelConfigul_SpecificParamsbucketSizeDurationspare2Enum,
	NhuLogChannelConfigul_SpecificParamsbucketSizeDurationspare1Enum
} EnumNhuLogChannelConfigul_SpecificParamsbucketSizeDuration;
typedef TknU32 NhuLogChannelConfigul_SpecificParamsbucketSizeDuration;

/* Element ----- logicalChannelGroup ------- */
typedef TknU32 NhuLogChannelConfigul_SpecificParamslogicalChannelGroup;

typedef struct NhuLogChannelConfigul_SpecificParams
{
	TknPres pres;
	NhuLogChannelConfigul_SpecificParamspriority priority;
	NhuLogChannelConfigul_SpecificParamsprioritisedBitRate prioritisedBitRate;
	NhuLogChannelConfigul_SpecificParamsbucketSizeDuration bucketSizeDuration;
	NhuLogChannelConfigul_SpecificParamslogicalChannelGroup logicalChannelGroup;
} NhuLogChannelConfigul_SpecificParams;

/* Element ----- logicalChannelSR-Mask-r9 ------- */
typedef enum enumNhuLogChannelConfigextaddgrp_1logicalChannelSR_Mask_r9
{
	NhuLogChannelConfigextaddgrp_1logicalChannelSR_Mask_r9setupEnum
} EnumNhuLogChannelConfigextaddgrp_1logicalChannelSR_Mask_r9;
typedef TknU32 NhuLogChannelConfigextaddgrp_1logicalChannelSR_Mask_r9;

typedef struct NhuLogChannelConfigextaddgrp_1
{
	TknPres pres;
	NhuLogChannelConfigextaddgrp_1logicalChannelSR_Mask_r9 logicalChannelSR_Mask_r9;
} NhuLogChannelConfigextaddgrp_1;

typedef struct NhuLogChannelConfig
{
	TknPres pres;
	NhuLogChannelConfigul_SpecificParams ul_SpecificParams;
	NhuLogChannelConfigextaddgrp_1 extaddgrp_1;
} NhuLogChannelConfig;

/* Element ----- srb-Identity ------- */
typedef TknU32 NhuSRB_ToAddModsrb_Identity;

typedef struct NhuSRB_ToAddModrlc_Config
{
	TknU8 choice;
	union {
		NhuRLC_Config explicitValue;
	} val;
} NhuSRB_ToAddModrlc_Config;

typedef struct NhuSRB_ToAddModlogicalChannelConfig
{
	TknU8 choice;
	union {
		NhuLogChannelConfig explicitValue;
	} val;
} NhuSRB_ToAddModlogicalChannelConfig;

typedef struct NhuSRB_ToAddMod
{
	TknPres pres;
	NhuSRB_ToAddModsrb_Identity srb_Identity;
	NhuSRB_ToAddModrlc_Config rlc_Config;
	NhuSRB_ToAddModlogicalChannelConfig logicalChannelConfig;
} NhuSRB_ToAddMod;

typedef struct NhuSRB_ToAddModLst
{
	TknU16 noComp;
	NhuSRB_ToAddMod *member;
}NhuSRB_ToAddModLst;

/* Element ----- DRB-Identity ------- */
typedef TknU32 NhuDRB_Identity;

/* Element ----- discardTimer ------- */
typedef enum enumNhuPDCP_ConfigdiscardTimer
{
	NhuPDCP_ConfigdiscardTimerms50Enum,
	NhuPDCP_ConfigdiscardTimerms100Enum,
	NhuPDCP_ConfigdiscardTimerms150Enum,
	NhuPDCP_ConfigdiscardTimerms300Enum,
	NhuPDCP_ConfigdiscardTimerms500Enum,
	NhuPDCP_ConfigdiscardTimerms750Enum,
	NhuPDCP_ConfigdiscardTimerms1500Enum,
	NhuPDCP_ConfigdiscardTimerinfinityEnum
} EnumNhuPDCP_ConfigdiscardTimer;
typedef TknU32 NhuPDCP_ConfigdiscardTimer;

/* Element ----- statusReportRequired ------- */
typedef TknU8 NhuPDCP_Configrlc_AMstatusReportReqd;

typedef struct NhuPDCP_Configrlc_AM
{
	TknPres pres;
	NhuPDCP_Configrlc_AMstatusReportReqd statusReportReqd;
} NhuPDCP_Configrlc_AM;

/* Element ----- pdcp-SN-Size ------- */
typedef enum enumNhuPDCP_Configrlc_UMpdcp_SN_Size
{
	NhuPDCP_Configrlc_UMpdcp_SN_Sizelen7bitsEnum,
	NhuPDCP_Configrlc_UMpdcp_SN_Sizelen12bitsEnum
} EnumNhuPDCP_Configrlc_UMpdcp_SN_Size;
typedef TknU32 NhuPDCP_Configrlc_UMpdcp_SN_Size;

typedef struct NhuPDCP_Configrlc_UM
{
	TknPres pres;
	NhuPDCP_Configrlc_UMpdcp_SN_Size pdcp_SN_Size;
} NhuPDCP_Configrlc_UM;

/* Element ----- maxCID ------- */
typedef TknU32 NhuPDCP_ConfigheaderCompressionrohcmaxCID;

/* Element ----- profile0x0001 ------- */
typedef TknU8 NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0001;

/* Element ----- profile0x0002 ------- */
typedef TknU8 NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0002;

/* Element ----- profile0x0003 ------- */
typedef TknU8 NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0003;

/* Element ----- profile0x0004 ------- */
typedef TknU8 NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0004;

/* Element ----- profile0x0006 ------- */
typedef TknU8 NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0006;

/* Element ----- profile0x0101 ------- */
typedef TknU8 NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0101;

/* Element ----- profile0x0102 ------- */
typedef TknU8 NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0102;

/* Element ----- profile0x0103 ------- */
typedef TknU8 NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0103;

/* Element ----- profile0x0104 ------- */
typedef TknU8 NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0104;

typedef struct NhuPDCP_ConfigheaderCompressionrohcprofiles
{
	TknPres pres;
	NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0001 profile0x0001;
	NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0002 profile0x0002;
	NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0003 profile0x0003;
	NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0004 profile0x0004;
	NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0006 profile0x0006;
	NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0101 profile0x0101;
	NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0102 profile0x0102;
	NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0103 profile0x0103;
	NhuPDCP_ConfigheaderCompressionrohcprofilesprofile0x0104 profile0x0104;
} NhuPDCP_ConfigheaderCompressionrohcprofiles;

typedef struct NhuPDCP_ConfigheaderCompressionrohc
{
	TknPres pres;
	NhuPDCP_ConfigheaderCompressionrohcmaxCID maxCID;	/* DEFAULT 15 */ 
	NhuPDCP_ConfigheaderCompressionrohcprofiles profiles;
} NhuPDCP_ConfigheaderCompressionrohc;

typedef struct NhuPDCP_ConfigheaderCompression
{
	TknU8 choice;
	union {
		NhuPDCP_ConfigheaderCompressionrohc rohc;
	} val;
} NhuPDCP_ConfigheaderCompression;

/* Element ----- rn-IntegrityProtection-r10 ------- */
typedef enum enumNhuPDCP_Configextaddgrp_1rn_IntegrityProtection_r10
{
	NhuPDCP_Configextaddgrp_1rn_IntegrityProtection_r10enabledEnum
} EnumNhuPDCP_Configextaddgrp_1rn_IntegrityProtection_r10;
typedef TknU32 NhuPDCP_Configextaddgrp_1rn_IntegrityProtection_r10;

/* Element ----- pdcp-SN-Size-v1130 ------- */
typedef enum enumNhuPDCP_Configextaddgrp_2pdcp_SN_Size_v1130
{
	NhuPDCP_Configextaddgrp_2pdcp_SN_Size_v1130len15bitsEnum
} EnumNhuPDCP_Configextaddgrp_2pdcp_SN_Size_v1130;
typedef TknU32 NhuPDCP_Configextaddgrp_2pdcp_SN_Size_v1130;

typedef struct NhuPDCP_Configextaddgrp_1
{
	TknPres pres;
	NhuPDCP_Configextaddgrp_1rn_IntegrityProtection_r10 rn_IntegrityProtection_r10;
} NhuPDCP_Configextaddgrp_1;

typedef struct NhuPDCP_Configextaddgrp_2
{
	TknPres pres;
	NhuPDCP_Configextaddgrp_2pdcp_SN_Size_v1130 pdcp_SN_Size_v1130;
} NhuPDCP_Configextaddgrp_2;

typedef struct NhuPDCP_Config
{
	TknPres pres;
	NhuPDCP_ConfigdiscardTimer discardTimer;
	NhuPDCP_Configrlc_AM rlc_AM;
	NhuPDCP_Configrlc_UM rlc_UM;
	NhuPDCP_ConfigheaderCompression headerCompression;
	NhuPDCP_Configextaddgrp_1 extaddgrp_1;
	NhuPDCP_Configextaddgrp_2 extaddgrp_2;
} NhuPDCP_Config;

/* Element ----- eps-BearerIdentity ------- */
typedef TknU32 NhuDRB_ToAddModeps_BrIdentity;

/* Element ----- logicalChannelIdentity ------- */
typedef TknU32 NhuDRB_ToAddModlogicalChannelIdentity;

typedef struct NhuDRB_ToAddMod
{
	TknPres pres;
	NhuDRB_ToAddModeps_BrIdentity eps_BrIdentity;
	NhuDRB_Identity drb_Identity;
	NhuPDCP_Config pdcp_Config;
	NhuRLC_Config rlc_Config;
	NhuDRB_ToAddModlogicalChannelIdentity logicalChannelIdentity;
	NhuLogChannelConfig logicalChannelConfig;
} NhuDRB_ToAddMod;

typedef struct NhuDRB_ToAddModLst
{
	TknU16 noComp;
	NhuDRB_ToAddMod *member;
}NhuDRB_ToAddModLst;

typedef struct NhuDRB_ToRlsLst
{
	TknU16 noComp;
	NhuDRB_Identity *member;
}NhuDRB_ToRlsLst;

/* Element ----- onDurationTimer ------- */
typedef enum enumNhuDRX_ConfigsetuponDurationTimer
{
	NhuDRX_ConfigsetuponDurationTimerpsf1Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf2Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf3Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf4Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf5Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf6Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf8Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf10Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf20Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf30Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf40Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf50Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf60Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf80Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf100Enum,
	NhuDRX_ConfigsetuponDurationTimerpsf200Enum
} EnumNhuDRX_ConfigsetuponDurationTimer;
typedef TknU32 NhuDRX_ConfigsetuponDurationTimer;

/* Element ----- drx-InactivityTimer ------- */
typedef enum enumNhuDRX_Configsetupdrx_InactivityTimer
{
	NhuDRX_Configsetupdrx_InactivityTimerpsf1Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf2Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf3Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf4Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf5Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf6Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf8Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf10Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf20Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf30Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf40Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf50Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf60Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf80Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf100Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf200Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf300Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf500Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf750Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf1280Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf1920Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf2560Enum,
	NhuDRX_Configsetupdrx_InactivityTimerpsf0_v1020Enum,
	NhuDRX_Configsetupdrx_InactivityTimerspare9Enum,
	NhuDRX_Configsetupdrx_InactivityTimerspare8Enum,
	NhuDRX_Configsetupdrx_InactivityTimerspare7Enum,
	NhuDRX_Configsetupdrx_InactivityTimerspare6Enum,
	NhuDRX_Configsetupdrx_InactivityTimerspare5Enum,
	NhuDRX_Configsetupdrx_InactivityTimerspare4Enum,
	NhuDRX_Configsetupdrx_InactivityTimerspare3Enum,
	NhuDRX_Configsetupdrx_InactivityTimerspare2Enum,
	NhuDRX_Configsetupdrx_InactivityTimerspare1Enum
} EnumNhuDRX_Configsetupdrx_InactivityTimer;
typedef TknU32 NhuDRX_Configsetupdrx_InactivityTimer;

/* Element ----- drx-RetransmissionTimer ------- */
typedef enum enumNhuDRX_Configsetupdrx_ReTxTimer
{
	NhuDRX_Configsetupdrx_ReTxTimerpsf1Enum,
	NhuDRX_Configsetupdrx_ReTxTimerpsf2Enum,
	NhuDRX_Configsetupdrx_ReTxTimerpsf4Enum,
	NhuDRX_Configsetupdrx_ReTxTimerpsf6Enum,
	NhuDRX_Configsetupdrx_ReTxTimerpsf8Enum,
	NhuDRX_Configsetupdrx_ReTxTimerpsf16Enum,
	NhuDRX_Configsetupdrx_ReTxTimerpsf24Enum,
	NhuDRX_Configsetupdrx_ReTxTimerpsf33Enum
} EnumNhuDRX_Configsetupdrx_ReTxTimer;
typedef TknU32 NhuDRX_Configsetupdrx_ReTxTimer;

/* Element ----- sf10 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf10;

/* Element ----- sf20 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf20;

/* Element ----- sf32 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf32;

/* Element ----- sf40 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf40;

/* Element ----- sf64 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf64;

/* Element ----- sf80 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf80;

/* Element ----- sf128 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf128;

/* Element ----- sf160 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf160;

/* Element ----- sf256 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf256;

/* Element ----- sf320 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf320;

/* Element ----- sf512 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf512;

/* Element ----- sf640 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf640;

/* Element ----- sf1024 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf1024;

/* Element ----- sf1280 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf1280;

/* Element ----- sf2048 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf2048;

/* Element ----- sf2560 ------- */
typedef TknU32 NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf2560;

typedef struct NhuDRX_ConfigsetuplongDRX_CycleStartOffset
{
	TknU8 choice;
	union {
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf10 sf10;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf20 sf20;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf32 sf32;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf40 sf40;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf64 sf64;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf80 sf80;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf128 sf128;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf160 sf160;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf256 sf256;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf320 sf320;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf512 sf512;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf640 sf640;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf1024 sf1024;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf1280 sf1280;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf2048 sf2048;
		NhuDRX_ConfigsetuplongDRX_CycleStartOffsetsf2560 sf2560;
	} val;
} NhuDRX_ConfigsetuplongDRX_CycleStartOffset;

/* Element ----- shortDRX-Cycle ------- */
typedef enum enumNhuDRX_ConfigsetupshortDRXshortDRX_Cycle
{
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf2Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf5Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf8Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf10Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf16Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf20Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf32Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf40Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf64Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf80Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf128Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf160Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf256Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf320Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf512Enum,
	NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf640Enum
} EnumNhuDRX_ConfigsetupshortDRXshortDRX_Cycle;
typedef TknU32 NhuDRX_ConfigsetupshortDRXshortDRX_Cycle;

/* Element ----- drxShortCycleTimer ------- */
typedef TknU32 NhuDRX_ConfigsetupshortDRXdrxShortCycleTimer;

typedef struct NhuDRX_ConfigsetupshortDRX
{
	TknPres pres;
	NhuDRX_ConfigsetupshortDRXshortDRX_Cycle shortDRX_Cycle;
	NhuDRX_ConfigsetupshortDRXdrxShortCycleTimer drxShortCycleTimer;
} NhuDRX_ConfigsetupshortDRX;

typedef struct NhuDRX_Configsetup
{
	TknPres pres;
	NhuDRX_ConfigsetuponDurationTimer onDurationTimer;
	NhuDRX_Configsetupdrx_InactivityTimer drx_InactivityTimer;
	NhuDRX_Configsetupdrx_ReTxTimer drx_ReTxTimer;
	NhuDRX_ConfigsetuplongDRX_CycleStartOffset longDRX_CycleStartOffset;
	NhuDRX_ConfigsetupshortDRX shortDRX;
} NhuDRX_Configsetup;

typedef struct NhuDRX_Config
{
	TknU8 choice;
	union {
		NhuDRX_Configsetup setup;
	} val;
} NhuDRX_Config;

/* Element ----- STAG-Id-r11 ------- */
typedef TknU32 NhuSTAG_Id_r11;

typedef struct NhuSTAG_ToRlsLst_r11
{
	TknU16 noComp;
	NhuSTAG_Id_r11 *member;
}NhuSTAG_ToRlsLst_r11;

typedef struct NhuSTAG_ToAddMod_r11
{
	TknPres pres;
	NhuSTAG_Id_r11 stag_Id_r11;
	NhuTimeAlignmentTimer timeAlignmentTimerSTAG_r11;
} NhuSTAG_ToAddMod_r11;

typedef struct NhuSTAG_ToAddModLst_r11
{
	TknU16 noComp;
	NhuSTAG_ToAddMod_r11 *member;
}NhuSTAG_ToAddModLst_r11;

/* Element ----- drx-RetransmissionTimer-v1130 ------- */
typedef enum enumNhuDRX_Config_v1130drx_ReTxTimer_v1130
{
	NhuDRX_Config_v1130drx_ReTxTimer_v1130psf0_v1130Enum
} EnumNhuDRX_Config_v1130drx_ReTxTimer_v1130;
typedef TknU32 NhuDRX_Config_v1130drx_ReTxTimer_v1130;

/* Element ----- sf60-v1130 ------- */
typedef TknU32 NhuDRX_Config_v1130longDRX_CycleStartOffset_v1130sf60_v1130;

/* Element ----- sf70-v1130 ------- */
typedef TknU32 NhuDRX_Config_v1130longDRX_CycleStartOffset_v1130sf70_v1130;

typedef struct NhuDRX_Config_v1130longDRX_CycleStartOffset_v1130
{
	TknU8 choice;
	union {
		NhuDRX_Config_v1130longDRX_CycleStartOffset_v1130sf60_v1130 sf60_v1130;
		NhuDRX_Config_v1130longDRX_CycleStartOffset_v1130sf70_v1130 sf70_v1130;
	} val;
} NhuDRX_Config_v1130longDRX_CycleStartOffset_v1130;

/* Element ----- shortDRX-Cycle-v1130 ------- */
typedef enum enumNhuDRX_Config_v1130shortDRX_Cycle_v1130
{
	NhuDRX_Config_v1130shortDRX_Cycle_v1130sf4_v1130Enum
} EnumNhuDRX_Config_v1130shortDRX_Cycle_v1130;
typedef TknU32 NhuDRX_Config_v1130shortDRX_Cycle_v1130;

typedef struct NhuDRX_Config_v1130
{
	TknPres pres;
	NhuDRX_Config_v1130drx_ReTxTimer_v1130 drx_ReTxTimer_v1130;
	NhuDRX_Config_v1130longDRX_CycleStartOffset_v1130 longDRX_CycleStartOffset_v1130;
	NhuDRX_Config_v1130shortDRX_Cycle_v1130 shortDRX_Cycle_v1130;
} NhuDRX_Config_v1130;

/* Element ----- maxHARQ-Tx ------- */
typedef enum enumNhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Tx
{
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn1Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn2Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn3Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn4Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn5Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn6Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn7Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn8Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn10Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn12Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn16Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn20Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn24Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txn28Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txspare2Enum,
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Txspare1Enum
} EnumNhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Tx;
typedef TknU32 NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Tx;

/* Element ----- periodicBSR-Timer ------- */
typedef enum enumNhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timer
{
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf5Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf10Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf16Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf20Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf32Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf40Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf64Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf80Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf128Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf160Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf320Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf640Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf1280Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timersf2560Enum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_TimerinfinityEnum,
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timerspare1Enum
} EnumNhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timer;
typedef TknU32 NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timer;

/* Element ----- retxBSR-Timer ------- */
typedef enum enumNhuMAC_MainConfigul_SCH_ConfigretxBSR_Timer
{
	NhuMAC_MainConfigul_SCH_ConfigretxBSR_Timersf320Enum,
	NhuMAC_MainConfigul_SCH_ConfigretxBSR_Timersf640Enum,
	NhuMAC_MainConfigul_SCH_ConfigretxBSR_Timersf1280Enum,
	NhuMAC_MainConfigul_SCH_ConfigretxBSR_Timersf2560Enum,
	NhuMAC_MainConfigul_SCH_ConfigretxBSR_Timersf5120Enum,
	NhuMAC_MainConfigul_SCH_ConfigretxBSR_Timersf10240Enum,
	NhuMAC_MainConfigul_SCH_ConfigretxBSR_Timerspare2Enum,
	NhuMAC_MainConfigul_SCH_ConfigretxBSR_Timerspare1Enum
} EnumNhuMAC_MainConfigul_SCH_ConfigretxBSR_Timer;
typedef TknU32 NhuMAC_MainConfigul_SCH_ConfigretxBSR_Timer;

/* Element ----- ttiBundling ------- */
typedef TknU8 NhuMAC_MainConfigul_SCH_ConfigttiBundling;

typedef struct NhuMAC_MainConfigul_SCH_Config
{
	TknPres pres;
	NhuMAC_MainConfigul_SCH_ConfigmaxHARQ_Tx maxHARQ_Tx;
	NhuMAC_MainConfigul_SCH_ConfigperiodicBSR_Timer periodicBSR_Timer;
	NhuMAC_MainConfigul_SCH_ConfigretxBSR_Timer retxBSR_Timer;
	NhuMAC_MainConfigul_SCH_ConfigttiBundling ttiBundling;
} NhuMAC_MainConfigul_SCH_Config;

/* Element ----- periodicPHR-Timer ------- */
typedef enum enumNhuMAC_MainConfigphr_ConfigsetupperiodicPHR_Timer
{
	NhuMAC_MainConfigphr_ConfigsetupperiodicPHR_Timersf10Enum,
	NhuMAC_MainConfigphr_ConfigsetupperiodicPHR_Timersf20Enum,
	NhuMAC_MainConfigphr_ConfigsetupperiodicPHR_Timersf50Enum,
	NhuMAC_MainConfigphr_ConfigsetupperiodicPHR_Timersf100Enum,
	NhuMAC_MainConfigphr_ConfigsetupperiodicPHR_Timersf200Enum,
	NhuMAC_MainConfigphr_ConfigsetupperiodicPHR_Timersf500Enum,
	NhuMAC_MainConfigphr_ConfigsetupperiodicPHR_Timersf1000Enum,
	NhuMAC_MainConfigphr_ConfigsetupperiodicPHR_TimerinfinityEnum
} EnumNhuMAC_MainConfigphr_ConfigsetupperiodicPHR_Timer;
typedef TknU32 NhuMAC_MainConfigphr_ConfigsetupperiodicPHR_Timer;

/* Element ----- prohibitPHR-Timer ------- */
typedef enum enumNhuMAC_MainConfigphr_ConfigsetupprohibitPHR_Timer
{
	NhuMAC_MainConfigphr_ConfigsetupprohibitPHR_Timersf0Enum,
	NhuMAC_MainConfigphr_ConfigsetupprohibitPHR_Timersf10Enum,
	NhuMAC_MainConfigphr_ConfigsetupprohibitPHR_Timersf20Enum,
	NhuMAC_MainConfigphr_ConfigsetupprohibitPHR_Timersf50Enum,
	NhuMAC_MainConfigphr_ConfigsetupprohibitPHR_Timersf100Enum,
	NhuMAC_MainConfigphr_ConfigsetupprohibitPHR_Timersf200Enum,
	NhuMAC_MainConfigphr_ConfigsetupprohibitPHR_Timersf500Enum,
	NhuMAC_MainConfigphr_ConfigsetupprohibitPHR_Timersf1000Enum
} EnumNhuMAC_MainConfigphr_ConfigsetupprohibitPHR_Timer;
typedef TknU32 NhuMAC_MainConfigphr_ConfigsetupprohibitPHR_Timer;

/* Element ----- dl-PathlossChange ------- */
typedef enum enumNhuMAC_MainConfigphr_Configsetupdl_PathlossChange
{
	NhuMAC_MainConfigphr_Configsetupdl_PathlossChangedB1Enum,
	NhuMAC_MainConfigphr_Configsetupdl_PathlossChangedB3Enum,
	NhuMAC_MainConfigphr_Configsetupdl_PathlossChangedB6Enum,
	NhuMAC_MainConfigphr_Configsetupdl_PathlossChangeinfinityEnum
} EnumNhuMAC_MainConfigphr_Configsetupdl_PathlossChange;
typedef TknU32 NhuMAC_MainConfigphr_Configsetupdl_PathlossChange;

typedef struct NhuMAC_MainConfigphr_Configsetup
{
	TknPres pres;
	NhuMAC_MainConfigphr_ConfigsetupperiodicPHR_Timer periodicPHR_Timer;
	NhuMAC_MainConfigphr_ConfigsetupprohibitPHR_Timer prohibitPHR_Timer;
	NhuMAC_MainConfigphr_Configsetupdl_PathlossChange dl_PathlossChange;
} NhuMAC_MainConfigphr_Configsetup;

typedef struct NhuMAC_MainConfigphr_Config
{
	TknU8 choice;
	union {
		NhuMAC_MainConfigphr_Configsetup setup;
	} val;
} NhuMAC_MainConfigphr_Config;

/* Element ----- sr-ProhibitTimer-r9 ------- */
typedef TknU32 NhuMAC_MainConfigextaddgrp_1sr_ProhibitTimer_r9;

/* Element ----- sCellDeactivationTimer-r10 ------- */
typedef enum enumNhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10
{
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf2Enum,
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf4Enum,
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf8Enum,
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf16Enum,
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf32Enum,
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf64Enum,
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf128Enum,
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10spareEnum
} EnumNhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10;
typedef TknU32 NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10;

/* Element ----- extendedBSR-Sizes-r10 ------- */
typedef enum enumNhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020extendedBSR_Sizes_r10
{
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020extendedBSR_Sizes_r10setupEnum
} EnumNhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020extendedBSR_Sizes_r10;
typedef TknU32 NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020extendedBSR_Sizes_r10;

/* Element ----- extendedPHR-r10 ------- */
typedef enum enumNhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020extendedPHR_r10
{
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020extendedPHR_r10setupEnum
} EnumNhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020extendedPHR_r10;
typedef TknU32 NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020extendedPHR_r10;

typedef struct NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020
{
	TknPres pres;
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10 sCellDeactivationTimer_r10;
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020extendedBSR_Sizes_r10 extendedBSR_Sizes_r10;
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020extendedPHR_r10 extendedPHR_r10;
} NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020;

typedef struct NhuMAC_MainConfigextaddgrp_1
{
	TknPres pres;
	NhuMAC_MainConfigextaddgrp_1sr_ProhibitTimer_r9 sr_ProhibitTimer_r9;
} NhuMAC_MainConfigextaddgrp_1;

typedef struct NhuMAC_MainConfigextaddgrp_2
{
	TknPres pres;
	NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020 mac_MainConfig_v1020;
} NhuMAC_MainConfigextaddgrp_2;

typedef struct NhuMAC_MainConfigextaddgrp_3
{
	TknPres pres;
	NhuSTAG_ToRlsLst_r11 stag_ToRlsLst_r11;
	NhuSTAG_ToAddModLst_r11 stag_ToAddModLst_r11;
	NhuDRX_Config_v1130 drx_Config_v1130;
} NhuMAC_MainConfigextaddgrp_3;

typedef struct NhuMAC_MainConfig
{
	TknPres pres;
	NhuMAC_MainConfigul_SCH_Config ul_SCH_Config;
	NhuDRX_Config drx_Config;
	NhuTimeAlignmentTimer timeAlignmentTimerDedicated;
	NhuMAC_MainConfigphr_Config phr_Config;
	NhuMAC_MainConfigextaddgrp_1 extaddgrp_1;
	NhuMAC_MainConfigextaddgrp_2 extaddgrp_2;
	NhuMAC_MainConfigextaddgrp_3 extaddgrp_3;
} NhuMAC_MainConfig;

/* Element ---------- C-RNTI ----------- */
typedef TknStrBSXL NhuC_RNTI;
typedef TknU32 NhuN1PUCCH_AN_PersistentLstMember;

typedef struct NhuN1PUCCH_AN_PersistentLst
{
	TknU16 noComp;
	NhuN1PUCCH_AN_PersistentLstMember *member;
}NhuN1PUCCH_AN_PersistentLst;

/* Element ----- semiPersistSchedIntervalDL ------- */
typedef enum enumNhuSPS_ConfigDLsetupsemiPersistSchedIntervalDL
{
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLsf10Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLsf20Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLsf32Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLsf40Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLsf64Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLsf80Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLsf128Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLsf160Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLsf320Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLsf640Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLspare6Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLspare5Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLspare4Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLspare3Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLspare2Enum,
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDLspare1Enum
} EnumNhuSPS_ConfigDLsetupsemiPersistSchedIntervalDL;
typedef TknU32 NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDL;

/* Element ----- numberOfConfSPS-Processes ------- */
typedef TknU32 NhuSPS_ConfigDLsetupnumberOfConfSPS_Processes;

typedef struct NhuSPS_ConfigDLsetupextaddgrp_1twoAntennaPortActivated_r10setup
{
	TknPres pres;
	NhuN1PUCCH_AN_PersistentLst n1PUCCH_AN_PersistentLstP1_r10;
} NhuSPS_ConfigDLsetupextaddgrp_1twoAntennaPortActivated_r10setup;

typedef struct NhuSPS_ConfigDLsetupextaddgrp_1twoAntennaPortActivated_r10
{
	TknU8 choice;
	union {
		NhuSPS_ConfigDLsetupextaddgrp_1twoAntennaPortActivated_r10setup setup;
	} val;
} NhuSPS_ConfigDLsetupextaddgrp_1twoAntennaPortActivated_r10;

typedef struct NhuSPS_ConfigDLsetupextaddgrp_1
{
	TknPres pres;
	NhuSPS_ConfigDLsetupextaddgrp_1twoAntennaPortActivated_r10 twoAntennaPortActivated_r10;
} NhuSPS_ConfigDLsetupextaddgrp_1;

typedef struct NhuSPS_ConfigDLsetup
{
	TknPres pres;
	NhuSPS_ConfigDLsetupsemiPersistSchedIntervalDL semiPersistSchedIntervalDL;
	NhuSPS_ConfigDLsetupnumberOfConfSPS_Processes numberOfConfSPS_Processes;
	NhuN1PUCCH_AN_PersistentLst n1PUCCH_AN_PersistentLst;
	NhuSPS_ConfigDLsetupextaddgrp_1 extaddgrp_1;
} NhuSPS_ConfigDLsetup;

typedef struct NhuSPS_ConfigDL
{
	TknU8 choice;
	union {
		NhuSPS_ConfigDLsetup setup;
	} val;
} NhuSPS_ConfigDL;

/* Element ----- semiPersistSchedIntervalUL ------- */
typedef enum enumNhuSPS_ConfigULsetupsemiPersistSchedIntervalUL
{
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULsf10Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULsf20Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULsf32Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULsf40Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULsf64Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULsf80Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULsf128Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULsf160Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULsf320Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULsf640Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULspare6Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULspare5Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULspare4Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULspare3Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULspare2Enum,
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalULspare1Enum
} EnumNhuSPS_ConfigULsetupsemiPersistSchedIntervalUL;
typedef TknU32 NhuSPS_ConfigULsetupsemiPersistSchedIntervalUL;

/* Element ----- implicitReleaseAfter ------- */
typedef enum enumNhuSPS_ConfigULsetupimplicitRlsAfter
{
	NhuSPS_ConfigULsetupimplicitRlsAftere2Enum,
	NhuSPS_ConfigULsetupimplicitRlsAftere3Enum,
	NhuSPS_ConfigULsetupimplicitRlsAftere4Enum,
	NhuSPS_ConfigULsetupimplicitRlsAftere8Enum
} EnumNhuSPS_ConfigULsetupimplicitRlsAfter;
typedef TknU32 NhuSPS_ConfigULsetupimplicitRlsAfter;

/* Element ----- p0-NominalPUSCH-Persistent ------- */
typedef TknS32 NhuSPS_ConfigULsetupp0_Persistentp0_NominalPUSCH_Persistent;

/* Element ----- p0-UE-PUSCH-Persistent ------- */
typedef TknS32 NhuSPS_ConfigULsetupp0_Persistentp0_UE_PUSCH_Persistent;

typedef struct NhuSPS_ConfigULsetupp0_Persistent
{
	TknPres pres;
	NhuSPS_ConfigULsetupp0_Persistentp0_NominalPUSCH_Persistent p0_NominalPUSCH_Persistent;
	NhuSPS_ConfigULsetupp0_Persistentp0_UE_PUSCH_Persistent p0_UE_PUSCH_Persistent;
} NhuSPS_ConfigULsetupp0_Persistent;

/* Element ----- twoIntervalsConfig ------- */
typedef enum enumNhuSPS_ConfigULsetuptwoIntervalsConfig
{
	NhuSPS_ConfigULsetuptwoIntervalsConfigtrueEnum
} EnumNhuSPS_ConfigULsetuptwoIntervalsConfig;
typedef TknU32 NhuSPS_ConfigULsetuptwoIntervalsConfig;

typedef struct NhuSPS_ConfigULsetup
{
	TknPres pres;
	NhuSPS_ConfigULsetupsemiPersistSchedIntervalUL semiPersistSchedIntervalUL;
	NhuSPS_ConfigULsetupimplicitRlsAfter implicitRlsAfter;
	NhuSPS_ConfigULsetupp0_Persistent p0_Persistent;
	NhuSPS_ConfigULsetuptwoIntervalsConfig twoIntervalsConfig;
} NhuSPS_ConfigULsetup;

typedef struct NhuSPS_ConfigUL
{
	TknU8 choice;
	union {
		NhuSPS_ConfigULsetup setup;
	} val;
} NhuSPS_ConfigUL;

typedef struct NhuSPS_Config
{
	TknPres pres;
	NhuC_RNTI semiPersistSchedC_RNTI;
	NhuSPS_ConfigDL sps_ConfigDL;
	NhuSPS_ConfigUL sps_ConfigUL;
} NhuSPS_Config;

/* Element ----- p-a ------- */
typedef enum enumNhuPDSCH_ConfigDedicatedp_a
{
	NhuPDSCH_ConfigDedicatedp_adB_6Enum,
	NhuPDSCH_ConfigDedicatedp_adB_4dot77Enum,
	NhuPDSCH_ConfigDedicatedp_adB_3Enum,
	NhuPDSCH_ConfigDedicatedp_adB_1dot77Enum,
	NhuPDSCH_ConfigDedicatedp_adB0Enum,
	NhuPDSCH_ConfigDedicatedp_adB1Enum,
	NhuPDSCH_ConfigDedicatedp_adB2Enum,
	NhuPDSCH_ConfigDedicatedp_adB3Enum
} EnumNhuPDSCH_ConfigDedicatedp_a;
typedef TknU32 NhuPDSCH_ConfigDedicatedp_a;

typedef struct NhuPDSCH_ConfigDedicated
{
	TknPres pres;
	NhuPDSCH_ConfigDedicatedp_a p_a;
} NhuPDSCH_ConfigDedicated;

/* Element ----- repetitionFactor ------- */
typedef enum enumNhuPUCCH_ConfigDedicatedackNackRepetitionsetuprepetitionFactor
{
	NhuPUCCH_ConfigDedicatedackNackRepetitionsetuprepetitionFactorn2Enum,
	NhuPUCCH_ConfigDedicatedackNackRepetitionsetuprepetitionFactorn4Enum,
	NhuPUCCH_ConfigDedicatedackNackRepetitionsetuprepetitionFactorn6Enum,
	NhuPUCCH_ConfigDedicatedackNackRepetitionsetuprepetitionFactorspare1Enum
} EnumNhuPUCCH_ConfigDedicatedackNackRepetitionsetuprepetitionFactor;
typedef TknU32 NhuPUCCH_ConfigDedicatedackNackRepetitionsetuprepetitionFactor;

/* Element ----- n1PUCCH-AN-Rep ------- */
typedef TknU32 NhuPUCCH_ConfigDedicatedackNackRepetitionsetupn1PUCCH_AN_Rep;

typedef struct NhuPUCCH_ConfigDedicatedackNackRepetitionsetup
{
	TknPres pres;
	NhuPUCCH_ConfigDedicatedackNackRepetitionsetuprepetitionFactor repetitionFactor;
	NhuPUCCH_ConfigDedicatedackNackRepetitionsetupn1PUCCH_AN_Rep n1PUCCH_AN_Rep;
} NhuPUCCH_ConfigDedicatedackNackRepetitionsetup;

typedef struct NhuPUCCH_ConfigDedicatedackNackRepetition
{
	TknU8 choice;
	union {
		NhuPUCCH_ConfigDedicatedackNackRepetitionsetup setup;
	} val;
} NhuPUCCH_ConfigDedicatedackNackRepetition;

/* Element ----- tdd-AckNackFeedbackMode ------- */
typedef enum enumNhuPUCCH_ConfigDedicatedtdd_AckNackFeedbackMode
{
	NhuPUCCH_ConfigDedicatedtdd_AckNackFeedbackModebundlingEnum,
	NhuPUCCH_ConfigDedicatedtdd_AckNackFeedbackModemultiplexingEnum
} EnumNhuPUCCH_ConfigDedicatedtdd_AckNackFeedbackMode;
typedef TknU32 NhuPUCCH_ConfigDedicatedtdd_AckNackFeedbackMode;

typedef struct NhuPUCCH_ConfigDedicated
{
	TknPres pres;
	NhuPUCCH_ConfigDedicatedackNackRepetition ackNackRepetition;
	NhuPUCCH_ConfigDedicatedtdd_AckNackFeedbackMode tdd_AckNackFeedbackMode;
} NhuPUCCH_ConfigDedicated;

/* Element ----- betaOffset-ACK-Index ------- */
typedef TknU32 NhuPUSCH_ConfigDedicatedbetaOffset_ACK_Idx;

/* Element ----- betaOffset-RI-Index ------- */
typedef TknU32 NhuPUSCH_ConfigDedicatedbetaOffset_RI_Idx;

/* Element ----- betaOffset-CQI-Index ------- */
typedef TknU32 NhuPUSCH_ConfigDedicatedbetaOffset_CQI_Idx;

typedef struct NhuPUSCH_ConfigDedicated
{
	TknPres pres;
	NhuPUSCH_ConfigDedicatedbetaOffset_ACK_Idx betaOffset_ACK_Idx;
	NhuPUSCH_ConfigDedicatedbetaOffset_RI_Idx betaOffset_RI_Idx;
	NhuPUSCH_ConfigDedicatedbetaOffset_CQI_Idx betaOffset_CQI_Idx;
} NhuPUSCH_ConfigDedicated;

/* Element ----- FilterCoefficient ------- */
typedef enum enumNhuFilterCoefficient
{
	NhuFilterCoefficientfc0Enum,
	NhuFilterCoefficientfc1Enum,
	NhuFilterCoefficientfc2Enum,
	NhuFilterCoefficientfc3Enum,
	NhuFilterCoefficientfc4Enum,
	NhuFilterCoefficientfc5Enum,
	NhuFilterCoefficientfc6Enum,
	NhuFilterCoefficientfc7Enum,
	NhuFilterCoefficientfc8Enum,
	NhuFilterCoefficientfc9Enum,
	NhuFilterCoefficientfc11Enum,
	NhuFilterCoefficientfc13Enum,
	NhuFilterCoefficientfc15Enum,
	NhuFilterCoefficientfc17Enum,
	NhuFilterCoefficientfc19Enum,
	NhuFilterCoefficientspare1Enum
} EnumNhuFilterCoefficient;
typedef TknU32 NhuFilterCoefficient;

/* Element ----- p0-UE-PUSCH ------- */
typedef TknS32 NhuUlnkPowerCntrlDedicatedp0_UE_PUSCH;

/* Element ----- deltaMCS-Enabled ------- */
typedef enum enumNhuUlnkPowerCntrlDedicateddeltaMCS_Enabled
{
	NhuUlnkPowerCntrlDedicateddeltaMCS_Enableden0Enum,
	NhuUlnkPowerCntrlDedicateddeltaMCS_Enableden1Enum
} EnumNhuUlnkPowerCntrlDedicateddeltaMCS_Enabled;
typedef TknU32 NhuUlnkPowerCntrlDedicateddeltaMCS_Enabled;

/* Element ----- accumulationEnabled ------- */
typedef TknU8 NhuUlnkPowerCntrlDedicatedaccumulationEnabled;

/* Element ----- p0-UE-PUCCH ------- */
typedef TknS32 NhuUlnkPowerCntrlDedicatedp0_UE_PUCCH;

/* Element ----- pSRS-Offset ------- */
typedef TknU32 NhuUlnkPowerCntrlDedicatedpSRS_Offset;

typedef struct NhuUlnkPowerCntrlDedicated
{
	TknPres pres;
	NhuUlnkPowerCntrlDedicatedp0_UE_PUSCH p0_UE_PUSCH;
	NhuUlnkPowerCntrlDedicateddeltaMCS_Enabled deltaMCS_Enabled;
	NhuUlnkPowerCntrlDedicatedaccumulationEnabled accumulationEnabled;
	NhuUlnkPowerCntrlDedicatedp0_UE_PUCCH p0_UE_PUCCH;
	NhuUlnkPowerCntrlDedicatedpSRS_Offset pSRS_Offset;
	NhuFilterCoefficient filterCoefficient;	/* DEFAULT 0 */ 
} NhuUlnkPowerCntrlDedicated;

/* Element ----- indexOfFormat3 ------- */
typedef TknU32 NhuTPC_IdxindexOfFormat3;

/* Element ----- indexOfFormat3A ------- */
typedef TknU32 NhuTPC_IdxindexOfFormat3A;

typedef struct NhuTPC_Idx
{
	TknU8 choice;
	union {
		NhuTPC_IdxindexOfFormat3 indexOfFormat3;
		NhuTPC_IdxindexOfFormat3A indexOfFormat3A;
	} val;
} NhuTPC_Idx;

/* Element ---------- tpc-RNTI ----------- */
typedef TknStrBSXL NhuTPC_PDCCH_Configsetuptpc_RNTI;
typedef struct NhuTPC_PDCCH_Configsetup
{
	TknPres pres;
	NhuTPC_PDCCH_Configsetuptpc_RNTI tpc_RNTI;
	NhuTPC_Idx tpc_Idx;
} NhuTPC_PDCCH_Configsetup;

typedef struct NhuTPC_PDCCH_Config
{
	TknU8 choice;
	union {
		NhuTPC_PDCCH_Configsetup setup;
	} val;
} NhuTPC_PDCCH_Config;

/* Element ----- CQI-ReportModeAperiodic ------- */
typedef enum enumNhuCQI_ReportModeAperiodic
{
	NhuCQI_ReportModeAperiodicrm12Enum,
	NhuCQI_ReportModeAperiodicrm20Enum,
	NhuCQI_ReportModeAperiodicrm22Enum,
	NhuCQI_ReportModeAperiodicrm30Enum,
	NhuCQI_ReportModeAperiodicrm31Enum,
	NhuCQI_ReportModeAperiodicspare3Enum,
	NhuCQI_ReportModeAperiodicspare2Enum,
	NhuCQI_ReportModeAperiodicspare1Enum
} EnumNhuCQI_ReportModeAperiodic;
typedef TknU32 NhuCQI_ReportModeAperiodic;

/* Element ----- cqi-PUCCH-ResourceIndex ------- */
typedef TknU32 NhuCQI_ReportPeriodicsetupcqi_PUCCH_ResourceIdx;

/* Element ----- cqi-pmi-ConfigIndex ------- */
typedef TknU32 NhuCQI_ReportPeriodicsetupcqi_pmi_ConfigIdx;

/* Element ----- k ------- */
typedef TknU32 NhuCQI_ReportPeriodicsetupcqi_FormatIndicatorPeriodicsubbandCQIk;

typedef struct NhuCQI_ReportPeriodicsetupcqi_FormatIndicatorPeriodicsubbandCQI
{
	TknPres pres;
	NhuCQI_ReportPeriodicsetupcqi_FormatIndicatorPeriodicsubbandCQIk k;
} NhuCQI_ReportPeriodicsetupcqi_FormatIndicatorPeriodicsubbandCQI;

typedef struct NhuCQI_ReportPeriodicsetupcqi_FormatIndicatorPeriodic
{
	TknU8 choice;
	union {
		NhuCQI_ReportPeriodicsetupcqi_FormatIndicatorPeriodicsubbandCQI subbandCQI;
	} val;
} NhuCQI_ReportPeriodicsetupcqi_FormatIndicatorPeriodic;

/* Element ----- ri-ConfigIndex ------- */
typedef TknU32 NhuCQI_ReportPeriodicsetupri_ConfigIdx;

/* Element ----- simultaneousAckNackAndCQI ------- */
typedef TknU8 NhuCQI_ReportPeriodicsetupsimultaneousAckNackAndCQI;

typedef struct NhuCQI_ReportPeriodicsetup
{
	TknPres pres;
	NhuCQI_ReportPeriodicsetupcqi_PUCCH_ResourceIdx cqi_PUCCH_ResourceIdx;
	NhuCQI_ReportPeriodicsetupcqi_pmi_ConfigIdx cqi_pmi_ConfigIdx;
	NhuCQI_ReportPeriodicsetupcqi_FormatIndicatorPeriodic cqi_FormatIndicatorPeriodic;
	NhuCQI_ReportPeriodicsetupri_ConfigIdx ri_ConfigIdx;
	NhuCQI_ReportPeriodicsetupsimultaneousAckNackAndCQI simultaneousAckNackAndCQI;
} NhuCQI_ReportPeriodicsetup;

typedef struct NhuCQI_ReportPeriodic
{
	TknU8 choice;
	union {
		NhuCQI_ReportPeriodicsetup setup;
	} val;
} NhuCQI_ReportPeriodic;

/* Element ----- nomPDSCH-RS-EPRE-Offset ------- */
typedef TknS32 NhuCQI_ReportConfignomPDSCH_RS_EPRE_Offset;

typedef struct NhuCQI_ReportConfig
{
	TknPres pres;
	NhuCQI_ReportModeAperiodic cqi_ReportModeAperiodic;
	NhuCQI_ReportConfignomPDSCH_RS_EPRE_Offset nomPDSCH_RS_EPRE_Offset;
	NhuCQI_ReportPeriodic cqi_ReportPeriodic;
} NhuCQI_ReportConfig;

/* Element ----- srs-Bandwidth ------- */
typedef enum enumNhuSoundingRS_UL_ConfigDedicatedsetupsrs_Bandwidth
{
	NhuSoundingRS_UL_ConfigDedicatedsetupsrs_Bandwidthbw0Enum,
	NhuSoundingRS_UL_ConfigDedicatedsetupsrs_Bandwidthbw1Enum,
	NhuSoundingRS_UL_ConfigDedicatedsetupsrs_Bandwidthbw2Enum,
	NhuSoundingRS_UL_ConfigDedicatedsetupsrs_Bandwidthbw3Enum
} EnumNhuSoundingRS_UL_ConfigDedicatedsetupsrs_Bandwidth;
typedef TknU32 NhuSoundingRS_UL_ConfigDedicatedsetupsrs_Bandwidth;

/* Element ----- srs-HoppingBandwidth ------- */
typedef enum enumNhuSoundingRS_UL_ConfigDedicatedsetupsrs_HoppingBandwidth
{
	NhuSoundingRS_UL_ConfigDedicatedsetupsrs_HoppingBandwidthhbw0Enum,
	NhuSoundingRS_UL_ConfigDedicatedsetupsrs_HoppingBandwidthhbw1Enum,
	NhuSoundingRS_UL_ConfigDedicatedsetupsrs_HoppingBandwidthhbw2Enum,
	NhuSoundingRS_UL_ConfigDedicatedsetupsrs_HoppingBandwidthhbw3Enum
} EnumNhuSoundingRS_UL_ConfigDedicatedsetupsrs_HoppingBandwidth;
typedef TknU32 NhuSoundingRS_UL_ConfigDedicatedsetupsrs_HoppingBandwidth;

/* Element ----- freqDomainPosition ------- */
typedef TknU32 NhuSoundingRS_UL_ConfigDedicatedsetupfreqDomainPosition;

/* Element ----- duration ------- */
typedef TknU8 NhuSoundingRS_UL_ConfigDedicatedsetupduration;

/* Element ----- srs-ConfigIndex ------- */
typedef TknU32 NhuSoundingRS_UL_ConfigDedicatedsetupsrs_ConfigIdx;

/* Element ----- transmissionComb ------- */
typedef TknU32 NhuSoundingRS_UL_ConfigDedicatedsetuptransmissionComb;

/* Element ----- cyclicShift ------- */
typedef enum enumNhuSoundingRS_UL_ConfigDedicatedsetupcyclicShift
{
	NhuSoundingRS_UL_ConfigDedicatedsetupcyclicShiftcs0Enum,
	NhuSoundingRS_UL_ConfigDedicatedsetupcyclicShiftcs1Enum,
	NhuSoundingRS_UL_ConfigDedicatedsetupcyclicShiftcs2Enum,
	NhuSoundingRS_UL_ConfigDedicatedsetupcyclicShiftcs3Enum,
	NhuSoundingRS_UL_ConfigDedicatedsetupcyclicShiftcs4Enum,
	NhuSoundingRS_UL_ConfigDedicatedsetupcyclicShiftcs5Enum,
	NhuSoundingRS_UL_ConfigDedicatedsetupcyclicShiftcs6Enum,
	NhuSoundingRS_UL_ConfigDedicatedsetupcyclicShiftcs7Enum
} EnumNhuSoundingRS_UL_ConfigDedicatedsetupcyclicShift;
typedef TknU32 NhuSoundingRS_UL_ConfigDedicatedsetupcyclicShift;

typedef struct NhuSoundingRS_UL_ConfigDedicatedsetup
{
	TknPres pres;
	NhuSoundingRS_UL_ConfigDedicatedsetupsrs_Bandwidth srs_Bandwidth;
	NhuSoundingRS_UL_ConfigDedicatedsetupsrs_HoppingBandwidth srs_HoppingBandwidth;
	NhuSoundingRS_UL_ConfigDedicatedsetupfreqDomainPosition freqDomainPosition;
	NhuSoundingRS_UL_ConfigDedicatedsetupduration duration;
	NhuSoundingRS_UL_ConfigDedicatedsetupsrs_ConfigIdx srs_ConfigIdx;
	NhuSoundingRS_UL_ConfigDedicatedsetuptransmissionComb transmissionComb;
	NhuSoundingRS_UL_ConfigDedicatedsetupcyclicShift cyclicShift;
} NhuSoundingRS_UL_ConfigDedicatedsetup;

typedef struct NhuSoundingRS_UL_ConfigDedicated
{
	TknU8 choice;
	union {
		NhuSoundingRS_UL_ConfigDedicatedsetup setup;
	} val;
} NhuSoundingRS_UL_ConfigDedicated;

/* Element ----- transmissionMode ------- */
typedef enum enumNhuAntennaInfoDedicatedtransmissionMode
{
	NhuAntennaInfoDedicatedtransmissionModetm1Enum,
	NhuAntennaInfoDedicatedtransmissionModetm2Enum,
	NhuAntennaInfoDedicatedtransmissionModetm3Enum,
	NhuAntennaInfoDedicatedtransmissionModetm4Enum,
	NhuAntennaInfoDedicatedtransmissionModetm5Enum,
	NhuAntennaInfoDedicatedtransmissionModetm6Enum,
	NhuAntennaInfoDedicatedtransmissionModetm7Enum,
	NhuAntennaInfoDedicatedtransmissionModetm8_v920Enum
} EnumNhuAntennaInfoDedicatedtransmissionMode;
typedef TknU32 NhuAntennaInfoDedicatedtransmissionMode;

/* Element ---------- n2TxAntenna-tm3 ----------- */
typedef TknStrBSXL NhuAntennaInfoDedicatedcodebookSubsetRestrnn2TxAntenna_tm3;
/* Element ---------- n4TxAntenna-tm3 ----------- */
typedef TknStrBSXL NhuAntennaInfoDedicatedcodebookSubsetRestrnn4TxAntenna_tm3;
/* Element ---------- n2TxAntenna-tm4 ----------- */
typedef TknStrBSXL NhuAntennaInfoDedicatedcodebookSubsetRestrnn2TxAntenna_tm4;
/* Element ---------- n4TxAntenna-tm4 ----------- */
typedef TknStrBSXL NhuAntennaInfoDedicatedcodebookSubsetRestrnn4TxAntenna_tm4;
/* Element ---------- n2TxAntenna-tm5 ----------- */
typedef TknStrBSXL NhuAntennaInfoDedicatedcodebookSubsetRestrnn2TxAntenna_tm5;
/* Element ---------- n4TxAntenna-tm5 ----------- */
typedef TknStrBSXL NhuAntennaInfoDedicatedcodebookSubsetRestrnn4TxAntenna_tm5;
/* Element ---------- n2TxAntenna-tm6 ----------- */
typedef TknStrBSXL NhuAntennaInfoDedicatedcodebookSubsetRestrnn2TxAntenna_tm6;
/* Element ---------- n4TxAntenna-tm6 ----------- */
typedef TknStrBSXL NhuAntennaInfoDedicatedcodebookSubsetRestrnn4TxAntenna_tm6;
typedef struct NhuAntennaInfoDedicatedcodebookSubsetRestrn
{
	TknU8 choice;
	union {
		NhuAntennaInfoDedicatedcodebookSubsetRestrnn2TxAntenna_tm3 n2TxAntenna_tm3;
		NhuAntennaInfoDedicatedcodebookSubsetRestrnn4TxAntenna_tm3 n4TxAntenna_tm3;
		NhuAntennaInfoDedicatedcodebookSubsetRestrnn2TxAntenna_tm4 n2TxAntenna_tm4;
		NhuAntennaInfoDedicatedcodebookSubsetRestrnn4TxAntenna_tm4 n4TxAntenna_tm4;
		NhuAntennaInfoDedicatedcodebookSubsetRestrnn2TxAntenna_tm5 n2TxAntenna_tm5;
		NhuAntennaInfoDedicatedcodebookSubsetRestrnn4TxAntenna_tm5 n4TxAntenna_tm5;
		NhuAntennaInfoDedicatedcodebookSubsetRestrnn2TxAntenna_tm6 n2TxAntenna_tm6;
		NhuAntennaInfoDedicatedcodebookSubsetRestrnn4TxAntenna_tm6 n4TxAntenna_tm6;
	} val;
} NhuAntennaInfoDedicatedcodebookSubsetRestrn;

/* Element ----- setup ------- */
typedef enum enumNhuAntennaInfoDedicatedue_TransmitAntennaSelectionsetup
{
	NhuAntennaInfoDedicatedue_TransmitAntennaSelectionsetupclosedLoopEnum,
	NhuAntennaInfoDedicatedue_TransmitAntennaSelectionsetupopenLoopEnum
} EnumNhuAntennaInfoDedicatedue_TransmitAntennaSelectionsetup;
typedef TknU32 NhuAntennaInfoDedicatedue_TransmitAntennaSelectionsetup;

typedef struct NhuAntennaInfoDedicatedue_TransmitAntennaSelection
{
	TknU8 choice;
	union {
		NhuAntennaInfoDedicatedue_TransmitAntennaSelectionsetup setup;
	} val;
} NhuAntennaInfoDedicatedue_TransmitAntennaSelection;

typedef struct NhuAntennaInfoDedicated
{
	TknPres pres;
	NhuAntennaInfoDedicatedtransmissionMode transmissionMode;
	NhuAntennaInfoDedicatedcodebookSubsetRestrn codebookSubsetRestrn;
	NhuAntennaInfoDedicatedue_TransmitAntennaSelection ue_TransmitAntennaSelection;
} NhuAntennaInfoDedicated;

/* Element ----- sr-PUCCH-ResourceIndex ------- */
typedef TknU32 NhuSchedulingRqstConfigsetupsr_PUCCH_ResourceIdx;

/* Element ----- sr-ConfigIndex ------- */
typedef TknU32 NhuSchedulingRqstConfigsetupsr_ConfigIdx;

/* Element ----- dsr-TransMax ------- */
typedef enum enumNhuSchedulingRqstConfigsetupdsr_TransMax
{
	NhuSchedulingRqstConfigsetupdsr_TransMaxn4Enum,
	NhuSchedulingRqstConfigsetupdsr_TransMaxn8Enum,
	NhuSchedulingRqstConfigsetupdsr_TransMaxn16Enum,
	NhuSchedulingRqstConfigsetupdsr_TransMaxn32Enum,
	NhuSchedulingRqstConfigsetupdsr_TransMaxn64Enum,
	NhuSchedulingRqstConfigsetupdsr_TransMaxspare3Enum,
	NhuSchedulingRqstConfigsetupdsr_TransMaxspare2Enum,
	NhuSchedulingRqstConfigsetupdsr_TransMaxspare1Enum
} EnumNhuSchedulingRqstConfigsetupdsr_TransMax;
typedef TknU32 NhuSchedulingRqstConfigsetupdsr_TransMax;

typedef struct NhuSchedulingRqstConfigsetup
{
	TknPres pres;
	NhuSchedulingRqstConfigsetupsr_PUCCH_ResourceIdx sr_PUCCH_ResourceIdx;
	NhuSchedulingRqstConfigsetupsr_ConfigIdx sr_ConfigIdx;
	NhuSchedulingRqstConfigsetupdsr_TransMax dsr_TransMax;
} NhuSchedulingRqstConfigsetup;

typedef struct NhuSchedulingRqstConfig
{
	TknU8 choice;
	union {
		NhuSchedulingRqstConfigsetup setup;
	} val;
} NhuSchedulingRqstConfig;

/* Element ----- cqi-Mask-r9 ------- */
typedef enum enumNhuCQI_ReportConfig_v920cqi_Mask_r9
{
	NhuCQI_ReportConfig_v920cqi_Mask_r9setupEnum
} EnumNhuCQI_ReportConfig_v920cqi_Mask_r9;
typedef TknU32 NhuCQI_ReportConfig_v920cqi_Mask_r9;

/* Element ----- pmi-RI-Report-r9 ------- */
typedef enum enumNhuCQI_ReportConfig_v920pmi_RI_Report_r9
{
	NhuCQI_ReportConfig_v920pmi_RI_Report_r9setupEnum
} EnumNhuCQI_ReportConfig_v920pmi_RI_Report_r9;
typedef TknU32 NhuCQI_ReportConfig_v920pmi_RI_Report_r9;

typedef struct NhuCQI_ReportConfig_v920
{
	TknPres pres;
	NhuCQI_ReportConfig_v920cqi_Mask_r9 cqi_Mask_r9;
	NhuCQI_ReportConfig_v920pmi_RI_Report_r9 pmi_RI_Report_r9;
} NhuCQI_ReportConfig_v920;

/* Element ---------- n2TxAntenna-tm8-r9 ----------- */
typedef TknStrBSXL NhuAntennaInfoDedicated_v920codebookSubsetRestrn_v920n2TxAntenna_tm8_r9;
/* Element ---------- n4TxAntenna-tm8-r9 ----------- */
typedef TknStrBSXL NhuAntennaInfoDedicated_v920codebookSubsetRestrn_v920n4TxAntenna_tm8_r9;
typedef struct NhuAntennaInfoDedicated_v920codebookSubsetRestrn_v920
{
	TknU8 choice;
	union {
		NhuAntennaInfoDedicated_v920codebookSubsetRestrn_v920n2TxAntenna_tm8_r9 n2TxAntenna_tm8_r9;
		NhuAntennaInfoDedicated_v920codebookSubsetRestrn_v920n4TxAntenna_tm8_r9 n4TxAntenna_tm8_r9;
	} val;
} NhuAntennaInfoDedicated_v920codebookSubsetRestrn_v920;

typedef struct NhuAntennaInfoDedicated_v920
{
	TknPres pres;
	NhuAntennaInfoDedicated_v920codebookSubsetRestrn_v920 codebookSubsetRestrn_v920;
} NhuAntennaInfoDedicated_v920;

/* Element ----- transmissionMode-r10 ------- */
typedef enum enumNhuAntennaInfoDedicated_r10transmissionMode_r10
{
	NhuAntennaInfoDedicated_r10transmissionMode_r10tm1Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10tm2Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10tm3Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10tm4Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10tm5Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10tm6Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10tm7Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10tm8_v920Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10tm9_v1020Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10tm10_v1130Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10spare6Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10spare5Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10spare4Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10spare3Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10spare2Enum,
	NhuAntennaInfoDedicated_r10transmissionMode_r10spare1Enum
} EnumNhuAntennaInfoDedicated_r10transmissionMode_r10;
typedef TknU32 NhuAntennaInfoDedicated_r10transmissionMode_r10;

/* Element ---------- codebookSubsetRestriction-r10 ----------- */
typedef TknStrBSXL NhuAntennaInfoDedicated_r10codebookSubsetRestrn_r10;
/* Element ----- setup ------- */
typedef enum enumNhuAntennaInfoDedicated_r10ue_TransmitAntennaSelectionsetup
{
	NhuAntennaInfoDedicated_r10ue_TransmitAntennaSelectionsetupclosedLoopEnum,
	NhuAntennaInfoDedicated_r10ue_TransmitAntennaSelectionsetupopenLoopEnum
} EnumNhuAntennaInfoDedicated_r10ue_TransmitAntennaSelectionsetup;
typedef TknU32 NhuAntennaInfoDedicated_r10ue_TransmitAntennaSelectionsetup;

typedef struct NhuAntennaInfoDedicated_r10ue_TransmitAntennaSelection
{
	TknU8 choice;
	union {
		NhuAntennaInfoDedicated_r10ue_TransmitAntennaSelectionsetup setup;
	} val;
} NhuAntennaInfoDedicated_r10ue_TransmitAntennaSelection;

typedef struct NhuAntennaInfoDedicated_r10
{
	TknPres pres;
	NhuAntennaInfoDedicated_r10transmissionMode_r10 transmissionMode_r10;
	NhuAntennaInfoDedicated_r10codebookSubsetRestrn_r10 codebookSubsetRestrn_r10;
	NhuAntennaInfoDedicated_r10ue_TransmitAntennaSelection ue_TransmitAntennaSelection;
} NhuAntennaInfoDedicated_r10;

/* Element ----- transmissionModeUL-r10 ------- */
typedef enum enumNhuAntennaInfoUL_r10transmissionModeUL_r10
{
	NhuAntennaInfoUL_r10transmissionModeUL_r10tm1Enum,
	NhuAntennaInfoUL_r10transmissionModeUL_r10tm2Enum,
	NhuAntennaInfoUL_r10transmissionModeUL_r10spare6Enum,
	NhuAntennaInfoUL_r10transmissionModeUL_r10spare5Enum,
	NhuAntennaInfoUL_r10transmissionModeUL_r10spare4Enum,
	NhuAntennaInfoUL_r10transmissionModeUL_r10spare3Enum,
	NhuAntennaInfoUL_r10transmissionModeUL_r10spare2Enum,
	NhuAntennaInfoUL_r10transmissionModeUL_r10spare1Enum
} EnumNhuAntennaInfoUL_r10transmissionModeUL_r10;
typedef TknU32 NhuAntennaInfoUL_r10transmissionModeUL_r10;

/* Element ----- fourAntennaPortActivated-r10 ------- */
typedef enum enumNhuAntennaInfoUL_r10fourAntennaPortActivated_r10
{
	NhuAntennaInfoUL_r10fourAntennaPortActivated_r10setupEnum
} EnumNhuAntennaInfoUL_r10fourAntennaPortActivated_r10;
typedef TknU32 NhuAntennaInfoUL_r10fourAntennaPortActivated_r10;

typedef struct NhuAntennaInfoUL_r10
{
	TknPres pres;
	NhuAntennaInfoUL_r10transmissionModeUL_r10 transmissionModeUL_r10;
	NhuAntennaInfoUL_r10fourAntennaPortActivated_r10 fourAntennaPortActivated_r10;
} NhuAntennaInfoUL_r10;

/* Element ---------- trigger1-r10 ----------- */
typedef TknStrBSXL NhuCQI_ReportAperiodic_r10setupaperiodicCSI_Trigger_r10trigger1_r10;
/* Element ---------- trigger2-r10 ----------- */
typedef TknStrBSXL NhuCQI_ReportAperiodic_r10setupaperiodicCSI_Trigger_r10trigger2_r10;
typedef struct NhuCQI_ReportAperiodic_r10setupaperiodicCSI_Trigger_r10
{
	TknPres pres;
	NhuCQI_ReportAperiodic_r10setupaperiodicCSI_Trigger_r10trigger1_r10 trigger1_r10;
	NhuCQI_ReportAperiodic_r10setupaperiodicCSI_Trigger_r10trigger2_r10 trigger2_r10;
} NhuCQI_ReportAperiodic_r10setupaperiodicCSI_Trigger_r10;

typedef struct NhuCQI_ReportAperiodic_r10setup
{
	TknPres pres;
	NhuCQI_ReportModeAperiodic cqi_ReportModeAperiodic_r10;
	NhuCQI_ReportAperiodic_r10setupaperiodicCSI_Trigger_r10 aperiodicCSI_Trigger_r10;
} NhuCQI_ReportAperiodic_r10setup;

typedef struct NhuCQI_ReportAperiodic_r10
{
	TknU8 choice;
	union {
		NhuCQI_ReportAperiodic_r10setup setup;
	} val;
} NhuCQI_ReportAperiodic_r10;

/* Element ----- cqi-PUCCH-ResourceIndex-r10 ------- */
typedef TknU32 NhuCQI_ReportPeriodic_r10setupcqi_PUCCH_ResourceIdx_r10;

/* Element ----- cqi-PUCCH-ResourceIndexP1-r10 ------- */
typedef TknU32 NhuCQI_ReportPeriodic_r10setupcqi_PUCCH_ResourceIdxP1_r10;

/* Element ----- cqi-pmi-ConfigIndex ------- */
typedef TknU32 NhuCQI_ReportPeriodic_r10setupcqi_pmi_ConfigIdx;

/* Element ----- csi-ReportMode-r10 ------- */
typedef enum enumNhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10widebandCQI_r10csi_ReportMode_r10
{
	NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10widebandCQI_r10csi_ReportMode_r10submode1Enum,
	NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10widebandCQI_r10csi_ReportMode_r10submode2Enum
} EnumNhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10widebandCQI_r10csi_ReportMode_r10;
typedef TknU32 NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10widebandCQI_r10csi_ReportMode_r10;

typedef struct NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10widebandCQI_r10
{
	TknPres pres;
	NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10widebandCQI_r10csi_ReportMode_r10 csi_ReportMode_r10;
} NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10widebandCQI_r10;

/* Element ----- k ------- */
typedef TknU32 NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10subbandCQI_r10k;

/* Element ----- periodicityFactor-r10 ------- */
typedef enum enumNhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10subbandCQI_r10periodicityFactor_r10
{
	NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10subbandCQI_r10periodicityFactor_r10n2Enum,
	NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10subbandCQI_r10periodicityFactor_r10n4Enum
} EnumNhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10subbandCQI_r10periodicityFactor_r10;
typedef TknU32 NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10subbandCQI_r10periodicityFactor_r10;

typedef struct NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10subbandCQI_r10
{
	TknPres pres;
	NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10subbandCQI_r10k k;
	NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10subbandCQI_r10periodicityFactor_r10 periodicityFactor_r10;
} NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10subbandCQI_r10;

typedef struct NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10
{
	TknU8 choice;
	union {
		NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10widebandCQI_r10 widebandCQI_r10;
		NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10subbandCQI_r10 subbandCQI_r10;
	} val;
} NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10;

/* Element ----- ri-ConfigIndex ------- */
typedef TknU32 NhuCQI_ReportPeriodic_r10setupri_ConfigIdx;

/* Element ----- simultaneousAckNackAndCQI ------- */
typedef TknU8 NhuCQI_ReportPeriodic_r10setupsimultaneousAckNackAndCQI;

/* Element ----- cqi-Mask-r9 ------- */
typedef enum enumNhuCQI_ReportPeriodic_r10setupcqi_Mask_r9
{
	NhuCQI_ReportPeriodic_r10setupcqi_Mask_r9setupEnum
} EnumNhuCQI_ReportPeriodic_r10setupcqi_Mask_r9;
typedef TknU32 NhuCQI_ReportPeriodic_r10setupcqi_Mask_r9;

/* Element ----- cqi-pmi-ConfigIndex2-r10 ------- */
typedef TknU32 NhuCQI_ReportPeriodic_r10setupcsi_ConfigIdx_r10setupcqi_pmi_ConfigIdx2_r10;

/* Element ----- ri-ConfigIndex2-r10 ------- */
typedef TknU32 NhuCQI_ReportPeriodic_r10setupcsi_ConfigIdx_r10setupri_ConfigIdx2_r10;

typedef struct NhuCQI_ReportPeriodic_r10setupcsi_ConfigIdx_r10setup
{
	TknPres pres;
	NhuCQI_ReportPeriodic_r10setupcsi_ConfigIdx_r10setupcqi_pmi_ConfigIdx2_r10 cqi_pmi_ConfigIdx2_r10;
	NhuCQI_ReportPeriodic_r10setupcsi_ConfigIdx_r10setupri_ConfigIdx2_r10 ri_ConfigIdx2_r10;
} NhuCQI_ReportPeriodic_r10setupcsi_ConfigIdx_r10setup;

typedef struct NhuCQI_ReportPeriodic_r10setupcsi_ConfigIdx_r10
{
	TknU8 choice;
	union {
		NhuCQI_ReportPeriodic_r10setupcsi_ConfigIdx_r10setup setup;
	} val;
} NhuCQI_ReportPeriodic_r10setupcsi_ConfigIdx_r10;

typedef struct NhuCQI_ReportPeriodic_r10setup
{
	TknPres pres;
	NhuCQI_ReportPeriodic_r10setupcqi_PUCCH_ResourceIdx_r10 cqi_PUCCH_ResourceIdx_r10;
	NhuCQI_ReportPeriodic_r10setupcqi_PUCCH_ResourceIdxP1_r10 cqi_PUCCH_ResourceIdxP1_r10;
	NhuCQI_ReportPeriodic_r10setupcqi_pmi_ConfigIdx cqi_pmi_ConfigIdx;
	NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10 cqi_FormatIndicatorPeriodic_r10;
	NhuCQI_ReportPeriodic_r10setupri_ConfigIdx ri_ConfigIdx;
	NhuCQI_ReportPeriodic_r10setupsimultaneousAckNackAndCQI simultaneousAckNackAndCQI;
	NhuCQI_ReportPeriodic_r10setupcqi_Mask_r9 cqi_Mask_r9;
	NhuCQI_ReportPeriodic_r10setupcsi_ConfigIdx_r10 csi_ConfigIdx_r10;
} NhuCQI_ReportPeriodic_r10setup;

typedef struct NhuCQI_ReportPeriodic_r10
{
	TknU8 choice;
	union {
		NhuCQI_ReportPeriodic_r10setup setup;
	} val;
} NhuCQI_ReportPeriodic_r10;

/* Element ---------- subframePatternFDD-r10 ----------- */
typedef TknStrBSXL NhuMeasSubfrmPattern_r10subframePatternFDD_r10;
/* Element ---------- subframeConfig1-5-r10 ----------- */
typedef TknStrBSXL NhuMeasSubfrmPattern_r10subframePatternTDD_r10subframeConfig1_5_r10;
/* Element ---------- subframeConfig0-r10 ----------- */
typedef TknStrBSXL NhuMeasSubfrmPattern_r10subframePatternTDD_r10subframeConfig0_r10;
/* Element ---------- subframeConfig6-r10 ----------- */
typedef TknStrBSXL NhuMeasSubfrmPattern_r10subframePatternTDD_r10subframeConfig6_r10;
typedef struct NhuMeasSubfrmPattern_r10subframePatternTDD_r10
{
	TknU8 choice;
	union {
		NhuMeasSubfrmPattern_r10subframePatternTDD_r10subframeConfig1_5_r10 subframeConfig1_5_r10;
		NhuMeasSubfrmPattern_r10subframePatternTDD_r10subframeConfig0_r10 subframeConfig0_r10;
		NhuMeasSubfrmPattern_r10subframePatternTDD_r10subframeConfig6_r10 subframeConfig6_r10;
	} val;
} NhuMeasSubfrmPattern_r10subframePatternTDD_r10;

typedef struct NhuMeasSubfrmPattern_r10
{
	TknU8 choice;
	union {
		NhuMeasSubfrmPattern_r10subframePatternFDD_r10 subframePatternFDD_r10;
		NhuMeasSubfrmPattern_r10subframePatternTDD_r10 subframePatternTDD_r10;
	} val;
} NhuMeasSubfrmPattern_r10;

/* Element ----- nomPDSCH-RS-EPRE-Offset ------- */
typedef TknS32 NhuCQI_ReportConfig_r10nomPDSCH_RS_EPRE_Offset;

/* Element ----- pmi-RI-Report-r9 ------- */
typedef enum enumNhuCQI_ReportConfig_r10pmi_RI_Report_r9
{
	NhuCQI_ReportConfig_r10pmi_RI_Report_r9setupEnum
} EnumNhuCQI_ReportConfig_r10pmi_RI_Report_r9;
typedef TknU32 NhuCQI_ReportConfig_r10pmi_RI_Report_r9;

typedef struct NhuCQI_ReportConfig_r10csi_SubfrmPatternConfig_r10setup
{
	TknPres pres;
	NhuMeasSubfrmPattern_r10 csi_MeasSubfrmSet1_r10;
	NhuMeasSubfrmPattern_r10 csi_MeasSubfrmSet2_r10;
} NhuCQI_ReportConfig_r10csi_SubfrmPatternConfig_r10setup;

typedef struct NhuCQI_ReportConfig_r10csi_SubfrmPatternConfig_r10
{
	TknU8 choice;
	union {
		NhuCQI_ReportConfig_r10csi_SubfrmPatternConfig_r10setup setup;
	} val;
} NhuCQI_ReportConfig_r10csi_SubfrmPatternConfig_r10;

typedef struct NhuCQI_ReportConfig_r10
{
	TknPres pres;
	NhuCQI_ReportAperiodic_r10 cqi_ReportAperiodic_r10;
	NhuCQI_ReportConfig_r10nomPDSCH_RS_EPRE_Offset nomPDSCH_RS_EPRE_Offset;
	NhuCQI_ReportPeriodic_r10 cqi_ReportPeriodic_r10;
	NhuCQI_ReportConfig_r10pmi_RI_Report_r9 pmi_RI_Report_r9;
	NhuCQI_ReportConfig_r10csi_SubfrmPatternConfig_r10 csi_SubfrmPatternConfig_r10;
} NhuCQI_ReportConfig_r10;

/* Element ----- antennaPortsCount-r10 ------- */
typedef enum enumNhuCSI_RS_Config_r10csi_RS_r10setupantennaPortsCount_r10
{
	NhuCSI_RS_Config_r10csi_RS_r10setupantennaPortsCount_r10an1Enum,
	NhuCSI_RS_Config_r10csi_RS_r10setupantennaPortsCount_r10an2Enum,
	NhuCSI_RS_Config_r10csi_RS_r10setupantennaPortsCount_r10an4Enum,
	NhuCSI_RS_Config_r10csi_RS_r10setupantennaPortsCount_r10an8Enum
} EnumNhuCSI_RS_Config_r10csi_RS_r10setupantennaPortsCount_r10;
typedef TknU32 NhuCSI_RS_Config_r10csi_RS_r10setupantennaPortsCount_r10;

/* Element ----- resourceConfig-r10 ------- */
typedef TknU32 NhuCSI_RS_Config_r10csi_RS_r10setupresourceConfig_r10;

/* Element ----- subframeConfig-r10 ------- */
typedef TknU32 NhuCSI_RS_Config_r10csi_RS_r10setupsubframeConfig_r10;

/* Element ----- p-C-r10 ------- */
typedef TknS32 NhuCSI_RS_Config_r10csi_RS_r10setupp_C_r10;

typedef struct NhuCSI_RS_Config_r10csi_RS_r10setup
{
	TknPres pres;
	NhuCSI_RS_Config_r10csi_RS_r10setupantennaPortsCount_r10 antennaPortsCount_r10;
	NhuCSI_RS_Config_r10csi_RS_r10setupresourceConfig_r10 resourceConfig_r10;
	NhuCSI_RS_Config_r10csi_RS_r10setupsubframeConfig_r10 subframeConfig_r10;
	NhuCSI_RS_Config_r10csi_RS_r10setupp_C_r10 p_C_r10;
} NhuCSI_RS_Config_r10csi_RS_r10setup;

typedef struct NhuCSI_RS_Config_r10csi_RS_r10
{
	TknU8 choice;
	union {
		NhuCSI_RS_Config_r10csi_RS_r10setup setup;
	} val;
} NhuCSI_RS_Config_r10csi_RS_r10;

/* Element ---------- zeroTxPowerResourceConfigList-r10 ----------- */
typedef TknStrBSXL NhuCSI_RS_Config_r10zeroTxPowerCSI_RS_r10setupzeroTxPowerResourceConfigLst_r10;
/* Element ----- zeroTxPowerSubframeConfig-r10 ------- */
typedef TknU32 NhuCSI_RS_Config_r10zeroTxPowerCSI_RS_r10setupzeroTxPowerSubfrmConfig_r10;

typedef struct NhuCSI_RS_Config_r10zeroTxPowerCSI_RS_r10setup
{
	TknPres pres;
	NhuCSI_RS_Config_r10zeroTxPowerCSI_RS_r10setupzeroTxPowerResourceConfigLst_r10 zeroTxPowerResourceConfigLst_r10;
	NhuCSI_RS_Config_r10zeroTxPowerCSI_RS_r10setupzeroTxPowerSubfrmConfig_r10 zeroTxPowerSubfrmConfig_r10;
} NhuCSI_RS_Config_r10zeroTxPowerCSI_RS_r10setup;

typedef struct NhuCSI_RS_Config_r10zeroTxPowerCSI_RS_r10
{
	TknU8 choice;
	union {
		NhuCSI_RS_Config_r10zeroTxPowerCSI_RS_r10setup setup;
	} val;
} NhuCSI_RS_Config_r10zeroTxPowerCSI_RS_r10;

typedef struct NhuCSI_RS_Config_r10
{
	TknPres pres;
	NhuCSI_RS_Config_r10csi_RS_r10 csi_RS_r10;
	NhuCSI_RS_Config_r10zeroTxPowerCSI_RS_r10 zeroTxPowerCSI_RS_r10;
} NhuCSI_RS_Config_r10;

typedef TknU32 NhuN1PUCCH_AN_CS_r10Member;

typedef struct NhuN1PUCCH_AN_CS_r10
{
	TknU16 noComp;
	NhuN1PUCCH_AN_CS_r10Member *member;
}NhuN1PUCCH_AN_CS_r10;

typedef TknU32 NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10n3PUCCH_AN_Lst_r10Member;

typedef struct NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10n3PUCCH_AN_Lst_r10
{
	TknU16 noComp;
	NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10n3PUCCH_AN_Lst_r10Member *member;
}NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10n3PUCCH_AN_Lst_r10;

typedef TknU32 NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10twoAntennaPortActivatedPUCCH_Format3_r10setupn3PUCCH_AN_LstP1_r10Member;

typedef struct NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10twoAntennaPortActivatedPUCCH_Format3_r10setupn3PUCCH_AN_LstP1_r10
{
	TknU16 noComp;
	NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10twoAntennaPortActivatedPUCCH_Format3_r10setupn3PUCCH_AN_LstP1_r10Member *member;
}NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10twoAntennaPortActivatedPUCCH_Format3_r10setupn3PUCCH_AN_LstP1_r10;

typedef struct NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10twoAntennaPortActivatedPUCCH_Format3_r10setup
{
	TknPres pres;
	NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10twoAntennaPortActivatedPUCCH_Format3_r10setupn3PUCCH_AN_LstP1_r10 n3PUCCH_AN_LstP1_r10;
} NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10twoAntennaPortActivatedPUCCH_Format3_r10setup;

typedef struct NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10twoAntennaPortActivatedPUCCH_Format3_r10
{
	TknU8 choice;
	union {
		NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10twoAntennaPortActivatedPUCCH_Format3_r10setup setup;
	} val;
} NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10twoAntennaPortActivatedPUCCH_Format3_r10;

typedef struct NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10
{
	TknPres pres;
	NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10n3PUCCH_AN_Lst_r10 n3PUCCH_AN_Lst_r10;
	NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10twoAntennaPortActivatedPUCCH_Format3_r10 twoAntennaPortActivatedPUCCH_Format3_r10;
} NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10;

typedef struct NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10channelSelection_r10n1PUCCH_AN_CS_r10setupn1PUCCH_AN_CS_Lst_r10
{
	TknU16 noComp;
	NhuN1PUCCH_AN_CS_r10 *member;
}NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10channelSelection_r10n1PUCCH_AN_CS_r10setupn1PUCCH_AN_CS_Lst_r10;

typedef struct NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10channelSelection_r10n1PUCCH_AN_CS_r10setup
{
	TknPres pres;
	NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10channelSelection_r10n1PUCCH_AN_CS_r10setupn1PUCCH_AN_CS_Lst_r10 n1PUCCH_AN_CS_Lst_r10;
} NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10channelSelection_r10n1PUCCH_AN_CS_r10setup;

typedef struct NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10channelSelection_r10n1PUCCH_AN_CS_r10
{
	TknU8 choice;
	union {
		NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10channelSelection_r10n1PUCCH_AN_CS_r10setup setup;
	} val;
} NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10channelSelection_r10n1PUCCH_AN_CS_r10;

typedef struct NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10channelSelection_r10
{
	TknPres pres;
	NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10channelSelection_r10n1PUCCH_AN_CS_r10 n1PUCCH_AN_CS_r10;
} NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10channelSelection_r10;

typedef struct NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10
{
	TknU8 choice;
	union {
		NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10 format3_r10;
		NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10channelSelection_r10 channelSelection_r10;
	} val;
} NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10;

/* Element ----- twoAntennaPortActivatedPUCCH-Format1a1b-r10 ------- */
typedef enum enumNhuPUCCH_ConfigDedicated_v1020twoAntennaPortActivatedPUCCH_Format1a1b_r10
{
	NhuPUCCH_ConfigDedicated_v1020twoAntennaPortActivatedPUCCH_Format1a1b_r10trueEnum
} EnumNhuPUCCH_ConfigDedicated_v1020twoAntennaPortActivatedPUCCH_Format1a1b_r10;
typedef TknU32 NhuPUCCH_ConfigDedicated_v1020twoAntennaPortActivatedPUCCH_Format1a1b_r10;

/* Element ----- simultaneousPUCCH-PUSCH-r10 ------- */
typedef enum enumNhuPUCCH_ConfigDedicated_v1020simultaneousPUCCH_PUSCH_r10
{
	NhuPUCCH_ConfigDedicated_v1020simultaneousPUCCH_PUSCH_r10trueEnum
} EnumNhuPUCCH_ConfigDedicated_v1020simultaneousPUCCH_PUSCH_r10;
typedef TknU32 NhuPUCCH_ConfigDedicated_v1020simultaneousPUCCH_PUSCH_r10;

/* Element ----- n1PUCCH-AN-RepP1-r10 ------- */
typedef TknU32 NhuPUCCH_ConfigDedicated_v1020n1PUCCH_AN_RepP1_r10;

typedef struct NhuPUCCH_ConfigDedicated_v1020
{
	TknPres pres;
	NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10 pucch_Format_r10;
	NhuPUCCH_ConfigDedicated_v1020twoAntennaPortActivatedPUCCH_Format1a1b_r10 twoAntennaPortActivatedPUCCH_Format1a1b_r10;
	NhuPUCCH_ConfigDedicated_v1020simultaneousPUCCH_PUSCH_r10 simultaneousPUCCH_PUSCH_r10;
	NhuPUCCH_ConfigDedicated_v1020n1PUCCH_AN_RepP1_r10 n1PUCCH_AN_RepP1_r10;
} NhuPUCCH_ConfigDedicated_v1020;

/* Element ----- betaOffset-ACK-Index-MC-r10 ------- */
typedef TknU32 NhuPUSCH_ConfigDedicated_v1020betaOffsetMC_r10betaOffset_ACK_Idx_MC_r10;

/* Element ----- betaOffset-RI-Index-MC-r10 ------- */
typedef TknU32 NhuPUSCH_ConfigDedicated_v1020betaOffsetMC_r10betaOffset_RI_Idx_MC_r10;

/* Element ----- betaOffset-CQI-Index-MC-r10 ------- */
typedef TknU32 NhuPUSCH_ConfigDedicated_v1020betaOffsetMC_r10betaOffset_CQI_Idx_MC_r10;

typedef struct NhuPUSCH_ConfigDedicated_v1020betaOffsetMC_r10
{
	TknPres pres;
	NhuPUSCH_ConfigDedicated_v1020betaOffsetMC_r10betaOffset_ACK_Idx_MC_r10 betaOffset_ACK_Idx_MC_r10;
	NhuPUSCH_ConfigDedicated_v1020betaOffsetMC_r10betaOffset_RI_Idx_MC_r10 betaOffset_RI_Idx_MC_r10;
	NhuPUSCH_ConfigDedicated_v1020betaOffsetMC_r10betaOffset_CQI_Idx_MC_r10 betaOffset_CQI_Idx_MC_r10;
} NhuPUSCH_ConfigDedicated_v1020betaOffsetMC_r10;

/* Element ----- groupHoppingDisabled-r10 ------- */
typedef enum enumNhuPUSCH_ConfigDedicated_v1020groupHoppingDisabled_r10
{
	NhuPUSCH_ConfigDedicated_v1020groupHoppingDisabled_r10trueEnum
} EnumNhuPUSCH_ConfigDedicated_v1020groupHoppingDisabled_r10;
typedef TknU32 NhuPUSCH_ConfigDedicated_v1020groupHoppingDisabled_r10;

/* Element ----- dmrs-WithOCC-Activated-r10 ------- */
typedef enum enumNhuPUSCH_ConfigDedicated_v1020dmrs_WithOCC_Activated_r10
{
	NhuPUSCH_ConfigDedicated_v1020dmrs_WithOCC_Activated_r10trueEnum
} EnumNhuPUSCH_ConfigDedicated_v1020dmrs_WithOCC_Activated_r10;
typedef TknU32 NhuPUSCH_ConfigDedicated_v1020dmrs_WithOCC_Activated_r10;

typedef struct NhuPUSCH_ConfigDedicated_v1020
{
	TknPres pres;
	NhuPUSCH_ConfigDedicated_v1020betaOffsetMC_r10 betaOffsetMC_r10;
	NhuPUSCH_ConfigDedicated_v1020groupHoppingDisabled_r10 groupHoppingDisabled_r10;
	NhuPUSCH_ConfigDedicated_v1020dmrs_WithOCC_Activated_r10 dmrs_WithOCC_Activated_r10;
} NhuPUSCH_ConfigDedicated_v1020;

/* Element ----- sr-PUCCH-ResourceIndexP1-r10 ------- */
typedef TknU32 NhuSchedulingRqstConfig_v1020sr_PUCCH_ResourceIdxP1_r10;

typedef struct NhuSchedulingRqstConfig_v1020
{
	TknPres pres;
	NhuSchedulingRqstConfig_v1020sr_PUCCH_ResourceIdxP1_r10 sr_PUCCH_ResourceIdxP1_r10;
} NhuSchedulingRqstConfig_v1020;

/* Element ----- SRS-AntennaPort ------- */
typedef enum enumNhuSRS_AntennaPort
{
	NhuSRS_AntennaPortan1Enum,
	NhuSRS_AntennaPortan2Enum,
	NhuSRS_AntennaPortan4Enum,
	NhuSRS_AntennaPortspare1Enum
} EnumNhuSRS_AntennaPort;
typedef TknU32 NhuSRS_AntennaPort;

typedef struct NhuSoundingRS_UL_ConfigDedicated_v1020
{
	TknPres pres;
	NhuSRS_AntennaPort srs_AntennaPort_r10;
} NhuSoundingRS_UL_ConfigDedicated_v1020;

/* Element ----- srs-BandwidthAp-r10 ------- */
typedef enum enumNhuSRS_ConfigAp_r10srs_BandwidthAp_r10
{
	NhuSRS_ConfigAp_r10srs_BandwidthAp_r10bw0Enum,
	NhuSRS_ConfigAp_r10srs_BandwidthAp_r10bw1Enum,
	NhuSRS_ConfigAp_r10srs_BandwidthAp_r10bw2Enum,
	NhuSRS_ConfigAp_r10srs_BandwidthAp_r10bw3Enum
} EnumNhuSRS_ConfigAp_r10srs_BandwidthAp_r10;
typedef TknU32 NhuSRS_ConfigAp_r10srs_BandwidthAp_r10;

/* Element ----- freqDomainPositionAp-r10 ------- */
typedef TknU32 NhuSRS_ConfigAp_r10freqDomainPositionAp_r10;

/* Element ----- transmissionCombAp-r10 ------- */
typedef TknU32 NhuSRS_ConfigAp_r10transmissionCombAp_r10;

/* Element ----- cyclicShiftAp-r10 ------- */
typedef enum enumNhuSRS_ConfigAp_r10cyclicShiftAp_r10
{
	NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs0Enum,
	NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs1Enum,
	NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs2Enum,
	NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs3Enum,
	NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs4Enum,
	NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs5Enum,
	NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs6Enum,
	NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs7Enum
} EnumNhuSRS_ConfigAp_r10cyclicShiftAp_r10;
typedef TknU32 NhuSRS_ConfigAp_r10cyclicShiftAp_r10;

typedef struct NhuSRS_ConfigAp_r10
{
	TknPres pres;
	NhuSRS_AntennaPort srs_AntennaPortAp_r10;
	NhuSRS_ConfigAp_r10srs_BandwidthAp_r10 srs_BandwidthAp_r10;
	NhuSRS_ConfigAp_r10freqDomainPositionAp_r10 freqDomainPositionAp_r10;
	NhuSRS_ConfigAp_r10transmissionCombAp_r10 transmissionCombAp_r10;
	NhuSRS_ConfigAp_r10cyclicShiftAp_r10 cyclicShiftAp_r10;
} NhuSRS_ConfigAp_r10;

/* Element ----- srs-ConfigIndexAp-r10 ------- */
typedef TknU32 NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setupsrs_ConfigIdxAp_r10;

typedef struct NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setupsrs_ConfigApDCI_Format4_r10
{
	TknU16 noComp;
	NhuSRS_ConfigAp_r10 *member;
}NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setupsrs_ConfigApDCI_Format4_r10;

typedef struct NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setupsrs_ActivateAp_r10setup
{
	TknPres pres;
	NhuSRS_ConfigAp_r10 srs_ConfigApDCI_Format0_r10;
	NhuSRS_ConfigAp_r10 srs_ConfigApDCI_Format1a2b2c_r10;
} NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setupsrs_ActivateAp_r10setup;

typedef struct NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setupsrs_ActivateAp_r10
{
	TknU8 choice;
	union {
		NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setupsrs_ActivateAp_r10setup setup;
	} val;
} NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setupsrs_ActivateAp_r10;

typedef struct NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setup
{
	TknPres pres;
	NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setupsrs_ConfigIdxAp_r10 srs_ConfigIdxAp_r10;
	NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setupsrs_ConfigApDCI_Format4_r10 srs_ConfigApDCI_Format4_r10;
	NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setupsrs_ActivateAp_r10 srs_ActivateAp_r10;
} NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setup;

typedef struct NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10
{
	TknU8 choice;
	union {
		NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10setup setup;
	} val;
} NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10;

/* Element ----- deltaTxD-OffsetPUCCH-Format1-r10 ------- */
typedef enum enumNhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1_r10
{
	NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1_r10dB0Enum,
	NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1_r10dB_2Enum
} EnumNhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1_r10;
typedef TknU32 NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1_r10;

/* Element ----- deltaTxD-OffsetPUCCH-Format1a1b-r10 ------- */
typedef enum enumNhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1a1b_r10
{
	NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1a1b_r10dB0Enum,
	NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1a1b_r10dB_2Enum
} EnumNhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1a1b_r10;
typedef TknU32 NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1a1b_r10;

/* Element ----- deltaTxD-OffsetPUCCH-Format22a2b-r10 ------- */
typedef enum enumNhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format22a2b_r10
{
	NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format22a2b_r10dB0Enum,
	NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format22a2b_r10dB_2Enum
} EnumNhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format22a2b_r10;
typedef TknU32 NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format22a2b_r10;

/* Element ----- deltaTxD-OffsetPUCCH-Format3-r10 ------- */
typedef enum enumNhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format3_r10
{
	NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format3_r10dB0Enum,
	NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format3_r10dB_2Enum
} EnumNhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format3_r10;
typedef TknU32 NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format3_r10;

typedef struct NhuDeltaTxD_OffsetLstPUCCH_r10
{
	TknPres pres;
	NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1_r10 deltaTxD_OffsetPUCCH_Format1_r10;
	NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1a1b_r10 deltaTxD_OffsetPUCCH_Format1a1b_r10;
	NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format22a2b_r10 deltaTxD_OffsetPUCCH_Format22a2b_r10;
	NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format3_r10 deltaTxD_OffsetPUCCH_Format3_r10;
} NhuDeltaTxD_OffsetLstPUCCH_r10;

/* Element ----- pSRS-OffsetAp-r10 ------- */
typedef TknU32 NhuUlnkPowerCntrlDedicated_v1020pSRS_OffsetAp_r10;

typedef struct NhuUlnkPowerCntrlDedicated_v1020
{
	TknPres pres;
	NhuDeltaTxD_OffsetLstPUCCH_r10 deltaTxD_OffsetLstPUCCH_r10;
	NhuUlnkPowerCntrlDedicated_v1020pSRS_OffsetAp_r10 pSRS_OffsetAp_r10;
} NhuUlnkPowerCntrlDedicated_v1020;

/* Element ----- CSI-RS-ConfigNZPId-r11 ------- */
typedef TknU32 NhuCSI_RS_ConfigNZPId_r11;

typedef struct NhuCSI_RS_ConfigNZPToRlsLst_r11
{
	TknU16 noComp;
	NhuCSI_RS_ConfigNZPId_r11 *member;
}NhuCSI_RS_ConfigNZPToRlsLst_r11;

/* Element ----- antennaPortsCount-r11 ------- */
typedef enum enumNhuCSI_RS_ConfigNZP_r11antennaPortsCount_r11
{
	NhuCSI_RS_ConfigNZP_r11antennaPortsCount_r11an1Enum,
	NhuCSI_RS_ConfigNZP_r11antennaPortsCount_r11an2Enum,
	NhuCSI_RS_ConfigNZP_r11antennaPortsCount_r11an4Enum,
	NhuCSI_RS_ConfigNZP_r11antennaPortsCount_r11an8Enum
} EnumNhuCSI_RS_ConfigNZP_r11antennaPortsCount_r11;
typedef TknU32 NhuCSI_RS_ConfigNZP_r11antennaPortsCount_r11;

/* Element ----- resourceConfig-r11 ------- */
typedef TknU32 NhuCSI_RS_ConfigNZP_r11resourceConfig_r11;

/* Element ----- subframeConfig-r11 ------- */
typedef TknU32 NhuCSI_RS_ConfigNZP_r11subframeConfig_r11;

/* Element ----- scramblingIdentity-r11 ------- */
typedef TknU32 NhuCSI_RS_ConfigNZP_r11scramblingIdentity_r11;

/* Element ----- qcl-ScramblingIdentity-r11 ------- */
typedef TknU32 NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11qcl_ScramblingIdentity_r11;

/* Element ----- crs-PortsCount-r11 ------- */
typedef enum enumNhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11crs_PortsCount_r11
{
	NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11crs_PortsCount_r11n1Enum,
	NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11crs_PortsCount_r11n2Enum,
	NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11crs_PortsCount_r11n4Enum,
	NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11crs_PortsCount_r11spare1Enum
} EnumNhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11crs_PortsCount_r11;
typedef TknU32 NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11crs_PortsCount_r11;

typedef struct NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11mbsfn_SubfrmConfigLst_r11setup
{
	TknPres pres;
	NhuMBSFN_SubfrmConfigLst subframeConfigLst;
} NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11mbsfn_SubfrmConfigLst_r11setup;

typedef struct NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11mbsfn_SubfrmConfigLst_r11
{
	TknU8 choice;
	union {
		NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11mbsfn_SubfrmConfigLst_r11setup setup;
	} val;
} NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11mbsfn_SubfrmConfigLst_r11;

typedef struct NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11
{
	TknPres pres;
	NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11qcl_ScramblingIdentity_r11 qcl_ScramblingIdentity_r11;
	NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11crs_PortsCount_r11 crs_PortsCount_r11;
	NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11mbsfn_SubfrmConfigLst_r11 mbsfn_SubfrmConfigLst_r11;
} NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11;

typedef struct NhuCSI_RS_ConfigNZP_r11
{
	TknPres pres;
	NhuCSI_RS_ConfigNZPId_r11 csi_RS_ConfigNZPId_r11;
	NhuCSI_RS_ConfigNZP_r11antennaPortsCount_r11 antennaPortsCount_r11;
	NhuCSI_RS_ConfigNZP_r11resourceConfig_r11 resourceConfig_r11;
	NhuCSI_RS_ConfigNZP_r11subframeConfig_r11 subframeConfig_r11;
	NhuCSI_RS_ConfigNZP_r11scramblingIdentity_r11 scramblingIdentity_r11;
	NhuCSI_RS_ConfigNZP_r11qcl_CRS_Info_r11 qcl_CRS_Info_r11;
} NhuCSI_RS_ConfigNZP_r11;

typedef struct NhuCSI_RS_ConfigNZPToAddModLst_r11
{
	TknU16 noComp;
	NhuCSI_RS_ConfigNZP_r11 *member;
}NhuCSI_RS_ConfigNZPToAddModLst_r11;

/* Element ----- CSI-RS-ConfigZPId-r11 ------- */
typedef TknU32 NhuCSI_RS_ConfigZPId_r11;

typedef struct NhuCSI_RS_ConfigZPToRlsLst_r11
{
	TknU16 noComp;
	NhuCSI_RS_ConfigZPId_r11 *member;
}NhuCSI_RS_ConfigZPToRlsLst_r11;

/* Element ---------- resourceConfigList-r11 ----------- */
typedef TknStrBSXL NhuCSI_RS_ConfigZP_r11resourceConfigLst_r11;
/* Element ----- subframeConfig-r11 ------- */
typedef TknU32 NhuCSI_RS_ConfigZP_r11subframeConfig_r11;

typedef struct NhuCSI_RS_ConfigZP_r11
{
	TknPres pres;
	NhuCSI_RS_ConfigZPId_r11 csi_RS_ConfigZPId_r11;
	NhuCSI_RS_ConfigZP_r11resourceConfigLst_r11 resourceConfigLst_r11;
	NhuCSI_RS_ConfigZP_r11subframeConfig_r11 subframeConfig_r11;
} NhuCSI_RS_ConfigZP_r11;

typedef struct NhuCSI_RS_ConfigZPToAddModLst_r11
{
	TknU16 noComp;
	NhuCSI_RS_ConfigZP_r11 *member;
}NhuCSI_RS_ConfigZPToAddModLst_r11;

/* Element ----- EPDCCH-SetConfigId-r11 ------- */
typedef TknU32 NhuEPDCCH_SetConfigId_r11;

typedef struct NhuEPDCCH_SetConfigToRlsLst_r11
{
	TknU16 noComp;
	NhuEPDCCH_SetConfigId_r11 *member;
}NhuEPDCCH_SetConfigToRlsLst_r11;

/* Element ----- PDSCH-RE-MappingQCL-ConfigId-r11 ------- */
typedef TknU32 NhuPDSCH_RE_MappingQCL_ConfigId_r11;

/* Element ----- transmissionType-r11 ------- */
typedef enum enumNhuEPDCCH_SetConfig_r11transmissionTyp_r11
{
	NhuEPDCCH_SetConfig_r11transmissionTyp_r11localisedEnum,
	NhuEPDCCH_SetConfig_r11transmissionTyp_r11distributedEnum
} EnumNhuEPDCCH_SetConfig_r11transmissionTyp_r11;
typedef TknU32 NhuEPDCCH_SetConfig_r11transmissionTyp_r11;

/* Element ----- numberPRB-Pairs-r11 ------- */
typedef enum enumNhuEPDCCH_SetConfig_r11resourceBlockAssignment_r11numberPRB_Pairs_r11
{
	NhuEPDCCH_SetConfig_r11resourceBlockAssignment_r11numberPRB_Pairs_r11n2Enum,
	NhuEPDCCH_SetConfig_r11resourceBlockAssignment_r11numberPRB_Pairs_r11n4Enum,
	NhuEPDCCH_SetConfig_r11resourceBlockAssignment_r11numberPRB_Pairs_r11n8Enum
} EnumNhuEPDCCH_SetConfig_r11resourceBlockAssignment_r11numberPRB_Pairs_r11;
typedef TknU32 NhuEPDCCH_SetConfig_r11resourceBlockAssignment_r11numberPRB_Pairs_r11;

/* Element ---------- resourceBlockAssignment-r11 ----------- */
typedef TknStrBSXL NhuEPDCCH_SetConfig_r11resourceBlockAssignment_r11resourceBlockAssignment_r11;
typedef struct NhuEPDCCH_SetConfig_r11resourceBlockAssignment_r11
{
	TknPres pres;
	NhuEPDCCH_SetConfig_r11resourceBlockAssignment_r11numberPRB_Pairs_r11 numberPRB_Pairs_r11;
	NhuEPDCCH_SetConfig_r11resourceBlockAssignment_r11resourceBlockAssignment_r11 resourceBlockAssignment_r11;
} NhuEPDCCH_SetConfig_r11resourceBlockAssignment_r11;

/* Element ----- dmrs-ScramblingSequenceInt-r11 ------- */
typedef TknU32 NhuEPDCCH_SetConfig_r11dmrs_ScramblingSequenceInt_r11;

/* Element ----- pucch-ResourceStartOffset-r11 ------- */
typedef TknU32 NhuEPDCCH_SetConfig_r11pucch_ResourceStartOffset_r11;

typedef struct NhuEPDCCH_SetConfig_r11
{
	TknPres pres;
	NhuEPDCCH_SetConfigId_r11 setConfigId_r11;
	NhuEPDCCH_SetConfig_r11transmissionTyp_r11 transmissionTyp_r11;
	NhuEPDCCH_SetConfig_r11resourceBlockAssignment_r11 resourceBlockAssignment_r11;
	NhuEPDCCH_SetConfig_r11dmrs_ScramblingSequenceInt_r11 dmrs_ScramblingSequenceInt_r11;
	NhuEPDCCH_SetConfig_r11pucch_ResourceStartOffset_r11 pucch_ResourceStartOffset_r11;
	NhuPDSCH_RE_MappingQCL_ConfigId_r11 re_MappingQCL_ConfigId_r11;
} NhuEPDCCH_SetConfig_r11;

typedef struct NhuEPDCCH_SetConfigToAddModLst_r11
{
	TknU16 noComp;
	NhuEPDCCH_SetConfig_r11 *member;
}NhuEPDCCH_SetConfigToAddModLst_r11;

typedef struct NhuEPDCCH_Config_r11config_r11setupsubframePatternConfig_r11setup
{
	TknPres pres;
	NhuMeasSubfrmPattern_r10 subframePattern_r11;
} NhuEPDCCH_Config_r11config_r11setupsubframePatternConfig_r11setup;

typedef struct NhuEPDCCH_Config_r11config_r11setupsubframePatternConfig_r11
{
	TknU8 choice;
	union {
		NhuEPDCCH_Config_r11config_r11setupsubframePatternConfig_r11setup setup;
	} val;
} NhuEPDCCH_Config_r11config_r11setupsubframePatternConfig_r11;

/* Element ----- startSymbol-r11 ------- */
typedef TknU32 NhuEPDCCH_Config_r11config_r11setupstartSymbol_r11;

typedef struct NhuEPDCCH_Config_r11config_r11setup
{
	TknPres pres;
	NhuEPDCCH_Config_r11config_r11setupsubframePatternConfig_r11 subframePatternConfig_r11;
	NhuEPDCCH_Config_r11config_r11setupstartSymbol_r11 startSymbol_r11;
	NhuEPDCCH_SetConfigToRlsLst_r11 setConfigToRlsLst_r11;
	NhuEPDCCH_SetConfigToAddModLst_r11 setConfigToAddModLst_r11;
} NhuEPDCCH_Config_r11config_r11setup;

typedef struct NhuEPDCCH_Config_r11config_r11
{
	TknU8 choice;
	union {
		NhuEPDCCH_Config_r11config_r11setup setup;
	} val;
} NhuEPDCCH_Config_r11config_r11;

typedef struct NhuEPDCCH_Config_r11
{
	TknPres pres;
	NhuEPDCCH_Config_r11config_r11 config_r11;
} NhuEPDCCH_Config_r11;

/* Element ----- scramblingIdentity-r11 ------- */
typedef TknU32 NhuDMRS_Config_r11setupscramblingIdentity_r11;

/* Element ----- scramblingIdentity2-r11 ------- */
typedef TknU32 NhuDMRS_Config_r11setupscramblingIdentity2_r11;

typedef struct NhuDMRS_Config_r11setup
{
	TknPres pres;
	NhuDMRS_Config_r11setupscramblingIdentity_r11 scramblingIdentity_r11;
	NhuDMRS_Config_r11setupscramblingIdentity2_r11 scramblingIdentity2_r11;
} NhuDMRS_Config_r11setup;

typedef struct NhuDMRS_Config_r11
{
	TknU8 choice;
	union {
		NhuDMRS_Config_r11setup setup;
	} val;
} NhuDMRS_Config_r11;

typedef struct NhuRE_MappingQCLConfigToRlsLst_r11
{
	TknU16 noComp;
	NhuPDSCH_RE_MappingQCL_ConfigId_r11 *member;
}NhuRE_MappingQCLConfigToRlsLst_r11;

/* Element ----- crs-PortsCount-r11 ------- */
typedef enum enumNhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11crs_PortsCount_r11
{
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11crs_PortsCount_r11n1Enum,
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11crs_PortsCount_r11n2Enum,
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11crs_PortsCount_r11n4Enum,
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11crs_PortsCount_r11spare1Enum
} EnumNhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11crs_PortsCount_r11;
typedef TknU32 NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11crs_PortsCount_r11;

/* Element ----- crs-FreqShift-r11 ------- */
typedef TknU32 NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11crs_FreqShift_r11;

typedef struct NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11mbsfn_SubfrmConfigLst_r11setup
{
	TknPres pres;
	NhuMBSFN_SubfrmConfigLst subframeConfigLst;
} NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11mbsfn_SubfrmConfigLst_r11setup;

typedef struct NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11mbsfn_SubfrmConfigLst_r11
{
	TknU8 choice;
	union {
		NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11mbsfn_SubfrmConfigLst_r11setup setup;
	} val;
} NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11mbsfn_SubfrmConfigLst_r11;

/* Element ----- pdsch-Start-r11 ------- */
typedef enum enumNhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11pdsch_Start_r11
{
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11pdsch_Start_r11reservedEnum,
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11pdsch_Start_r11n1Enum,
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11pdsch_Start_r11n2Enum,
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11pdsch_Start_r11n3Enum,
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11pdsch_Start_r11n4Enum,
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11pdsch_Start_r11assignedEnum
} EnumNhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11pdsch_Start_r11;
typedef TknU32 NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11pdsch_Start_r11;

typedef struct NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11
{
	TknPres pres;
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11crs_PortsCount_r11 crs_PortsCount_r11;
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11crs_FreqShift_r11 crs_FreqShift_r11;
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11mbsfn_SubfrmConfigLst_r11 mbsfn_SubfrmConfigLst_r11;
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11pdsch_Start_r11 pdsch_Start_r11;
} NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11;

typedef struct NhuPDSCH_RE_MappingQCL_Config_r11
{
	TknPres pres;
	NhuPDSCH_RE_MappingQCL_ConfigId_r11 pdsch_RE_MappingQCL_ConfigId_r11;
	NhuPDSCH_RE_MappingQCL_Config_r11optionalSetOfFields_r11 optionalSetOfFields_r11;
	NhuCSI_RS_ConfigZPId_r11 csi_RS_ConfigZPId_r11;
	NhuCSI_RS_ConfigNZPId_r11 qcl_CSI_RS_ConfigNZPId_r11;
} NhuPDSCH_RE_MappingQCL_Config_r11;

typedef struct NhuRE_MappingQCLConfigToAddModLst_r11
{
	TknU16 noComp;
	NhuPDSCH_RE_MappingQCL_Config_r11 *member;
}NhuRE_MappingQCLConfigToAddModLst_r11;

/* Element ----- qcl-Operation ------- */
typedef enum enumNhuPDSCH_ConfigDedicated_v1130qcl_Operation
{
	NhuPDSCH_ConfigDedicated_v1130qcl_OperationtypeAEnum,
	NhuPDSCH_ConfigDedicated_v1130qcl_OperationtypeBEnum
} EnumNhuPDSCH_ConfigDedicated_v1130qcl_Operation;
typedef TknU32 NhuPDSCH_ConfigDedicated_v1130qcl_Operation;

typedef struct NhuPDSCH_ConfigDedicated_v1130
{
	TknPres pres;
	NhuDMRS_Config_r11 dmrs_ConfigPDSCH_r11;
	NhuPDSCH_ConfigDedicated_v1130qcl_Operation qcl_Operation;
	NhuRE_MappingQCLConfigToRlsLst_r11 re_MappingQCLConfigToRlsLst_r11;
	NhuRE_MappingQCLConfigToAddModLst_r11 re_MappingQCLConfigToAddModLst_r11;
} NhuPDSCH_ConfigDedicated_v1130;

/* Element ----- CQI-ReportPeriodicProcExtId-r11 ------- */
typedef TknU32 NhuCQI_ReportPeriodicProcExtId_r11;

typedef struct NhuCQI_ReportPeriodicProcExtToRlsLst_r11
{
	TknU16 noComp;
	NhuCQI_ReportPeriodicProcExtId_r11 *member;
}NhuCQI_ReportPeriodicProcExtToRlsLst_r11;

/* Element ----- cqi-pmi-ConfigIndex-r11 ------- */
typedef TknU32 NhuCQI_ReportPeriodicProcExt_r11cqi_pmi_ConfigIdx_r11;

/* Element ----- csi-ReportMode-r11 ------- */
typedef enum enumNhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11widebandCQI_r11csi_ReportMode_r11
{
	NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11widebandCQI_r11csi_ReportMode_r11submode1Enum,
	NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11widebandCQI_r11csi_ReportMode_r11submode2Enum
} EnumNhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11widebandCQI_r11csi_ReportMode_r11;
typedef TknU32 NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11widebandCQI_r11csi_ReportMode_r11;

typedef struct NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11widebandCQI_r11
{
	TknPres pres;
	NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11widebandCQI_r11csi_ReportMode_r11 csi_ReportMode_r11;
} NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11widebandCQI_r11;

/* Element ----- k ------- */
typedef TknU32 NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11subbandCQI_r11k;

/* Element ----- periodicityFactor-r11 ------- */
typedef enum enumNhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11subbandCQI_r11periodicityFactor_r11
{
	NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11subbandCQI_r11periodicityFactor_r11n2Enum,
	NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11subbandCQI_r11periodicityFactor_r11n4Enum
} EnumNhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11subbandCQI_r11periodicityFactor_r11;
typedef TknU32 NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11subbandCQI_r11periodicityFactor_r11;

typedef struct NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11subbandCQI_r11
{
	TknPres pres;
	NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11subbandCQI_r11k k;
	NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11subbandCQI_r11periodicityFactor_r11 periodicityFactor_r11;
} NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11subbandCQI_r11;

typedef struct NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11
{
	TknU8 choice;
	union {
		NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11widebandCQI_r11 widebandCQI_r11;
		NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11subbandCQI_r11 subbandCQI_r11;
	} val;
} NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11;

/* Element ----- ri-ConfigIndex-r11 ------- */
typedef TknU32 NhuCQI_ReportPeriodicProcExt_r11ri_ConfigIdx_r11;

/* Element ----- cqi-pmi-ConfigIndex2-r11 ------- */
typedef TknU32 NhuCQI_ReportPeriodicProcExt_r11csi_ConfigIdx_r11setupcqi_pmi_ConfigIdx2_r11;

/* Element ----- ri-ConfigIndex2-r11 ------- */
typedef TknU32 NhuCQI_ReportPeriodicProcExt_r11csi_ConfigIdx_r11setupri_ConfigIdx2_r11;

typedef struct NhuCQI_ReportPeriodicProcExt_r11csi_ConfigIdx_r11setup
{
	TknPres pres;
	NhuCQI_ReportPeriodicProcExt_r11csi_ConfigIdx_r11setupcqi_pmi_ConfigIdx2_r11 cqi_pmi_ConfigIdx2_r11;
	NhuCQI_ReportPeriodicProcExt_r11csi_ConfigIdx_r11setupri_ConfigIdx2_r11 ri_ConfigIdx2_r11;
} NhuCQI_ReportPeriodicProcExt_r11csi_ConfigIdx_r11setup;

typedef struct NhuCQI_ReportPeriodicProcExt_r11csi_ConfigIdx_r11
{
	TknU8 choice;
	union {
		NhuCQI_ReportPeriodicProcExt_r11csi_ConfigIdx_r11setup setup;
	} val;
} NhuCQI_ReportPeriodicProcExt_r11csi_ConfigIdx_r11;

typedef struct NhuCQI_ReportPeriodicProcExt_r11
{
	TknPres pres;
	NhuCQI_ReportPeriodicProcExtId_r11 cqi_ReportPeriodicProcExtId_r11;
	NhuCQI_ReportPeriodicProcExt_r11cqi_pmi_ConfigIdx_r11 cqi_pmi_ConfigIdx_r11;
	NhuCQI_ReportPeriodicProcExt_r11cqi_FormatIndicatorPeriodic_r11 cqi_FormatIndicatorPeriodic_r11;
	NhuCQI_ReportPeriodicProcExt_r11ri_ConfigIdx_r11 ri_ConfigIdx_r11;
	NhuCQI_ReportPeriodicProcExt_r11csi_ConfigIdx_r11 csi_ConfigIdx_r11;
} NhuCQI_ReportPeriodicProcExt_r11;

typedef struct NhuCQI_ReportPeriodicProcExtToAddModLst_r11
{
	TknU16 noComp;
	NhuCQI_ReportPeriodicProcExt_r11 *member;
}NhuCQI_ReportPeriodicProcExtToAddModLst_r11;

/* Element ----- simultaneousAckNackAndCQI-Format3-r11 ------- */
typedef enum enumNhuCQI_ReportPeriodic_v1130simultaneousAckNackAndCQI_Format3_r11
{
	NhuCQI_ReportPeriodic_v1130simultaneousAckNackAndCQI_Format3_r11setupEnum
} EnumNhuCQI_ReportPeriodic_v1130simultaneousAckNackAndCQI_Format3_r11;
typedef TknU32 NhuCQI_ReportPeriodic_v1130simultaneousAckNackAndCQI_Format3_r11;

typedef struct NhuCQI_ReportPeriodic_v1130
{
	TknPres pres;
	NhuCQI_ReportPeriodic_v1130simultaneousAckNackAndCQI_Format3_r11 simultaneousAckNackAndCQI_Format3_r11;
	NhuCQI_ReportPeriodicProcExtToRlsLst_r11 cqi_ReportPeriodicProcExtToRlsLst_r11;
	NhuCQI_ReportPeriodicProcExtToAddModLst_r11 cqi_ReportPeriodicProcExtToAddModLst_r11;
} NhuCQI_ReportPeriodic_v1130;

/* Element ----- CSI-IM-ConfigId-r11 ------- */
typedef TknU32 NhuCSI_IM_ConfigId_r11;

typedef struct NhuCSI_IM_ConfigToRlsLst_r11
{
	TknU16 noComp;
	NhuCSI_IM_ConfigId_r11 *member;
}NhuCSI_IM_ConfigToRlsLst_r11;

/* Element ----- resourceConfig-r11 ------- */
typedef TknU32 NhuCSI_IM_Config_r11resourceConfig_r11;

/* Element ----- subframeConfig-r11 ------- */
typedef TknU32 NhuCSI_IM_Config_r11subframeConfig_r11;

typedef struct NhuCSI_IM_Config_r11
{
	TknPres pres;
	NhuCSI_IM_ConfigId_r11 csi_IM_ConfigId_r11;
	NhuCSI_IM_Config_r11resourceConfig_r11 resourceConfig_r11;
	NhuCSI_IM_Config_r11subframeConfig_r11 subframeConfig_r11;
} NhuCSI_IM_Config_r11;

typedef struct NhuCSI_IM_ConfigToAddModLst_r11
{
	TknU16 noComp;
	NhuCSI_IM_Config_r11 *member;
}NhuCSI_IM_ConfigToAddModLst_r11;

/* Element ----- CSI-ProcessId-r11 ------- */
typedef TknU32 NhuCSI_ProcessId_r11;

typedef struct NhuCSI_ProcessToRlsLst_r11
{
	TknU16 noComp;
	NhuCSI_ProcessId_r11 *member;
}NhuCSI_ProcessToRlsLst_r11;

/* Element ----- p-C-r11 ------- */
typedef TknS32 NhuP_C_AndCBSR_r11p_C_r11;

/* Element ---------- codebookSubsetRestriction-r11 ----------- */
typedef TknStrBSXL NhuP_C_AndCBSR_r11codebookSubsetRestrn_r11;
typedef struct NhuP_C_AndCBSR_r11
{
	TknPres pres;
	NhuP_C_AndCBSR_r11p_C_r11 p_C_r11;
	NhuP_C_AndCBSR_r11codebookSubsetRestrn_r11 codebookSubsetRestrn_r11;
} NhuP_C_AndCBSR_r11;

/* Element ----- pmi-RI-Report-r11 ------- */
typedef enum enumNhuCQI_ReportBothProc_r11pmi_RI_Report_r11
{
	NhuCQI_ReportBothProc_r11pmi_RI_Report_r11setupEnum
} EnumNhuCQI_ReportBothProc_r11pmi_RI_Report_r11;
typedef TknU32 NhuCQI_ReportBothProc_r11pmi_RI_Report_r11;

typedef struct NhuCQI_ReportBothProc_r11
{
	TknPres pres;
	NhuCSI_ProcessId_r11 ri_Ref_CSI_ProcessId_r11;
	NhuCQI_ReportBothProc_r11pmi_RI_Report_r11 pmi_RI_Report_r11;
} NhuCQI_ReportBothProc_r11;

/* Element ----- trigger01-r11 ------- */
typedef TknU8 NhuCQI_ReportAperiodicProc_r11trigger01_r11;

/* Element ----- trigger10-r11 ------- */
typedef TknU8 NhuCQI_ReportAperiodicProc_r11trigger10_r11;

/* Element ----- trigger11-r11 ------- */
typedef TknU8 NhuCQI_ReportAperiodicProc_r11trigger11_r11;

typedef struct NhuCQI_ReportAperiodicProc_r11
{
	TknPres pres;
	NhuCQI_ReportModeAperiodic cqi_ReportModeAperiodic_r11;
	NhuCQI_ReportAperiodicProc_r11trigger01_r11 trigger01_r11;
	NhuCQI_ReportAperiodicProc_r11trigger10_r11 trigger10_r11;
	NhuCQI_ReportAperiodicProc_r11trigger11_r11 trigger11_r11;
} NhuCQI_ReportAperiodicProc_r11;

typedef struct NhuCSI_Process_r11p_C_AndCBSRLst_r11
{
	TknU16 noComp;
	NhuP_C_AndCBSR_r11 *member;
}NhuCSI_Process_r11p_C_AndCBSRLst_r11;

/* Element ----- cqi-ReportPeriodicProcId-r11 ------- */
typedef TknU32 NhuCSI_Process_r11cqi_ReportPeriodicProcId_r11;

typedef struct NhuCSI_Process_r11
{
	TknPres pres;
	NhuCSI_ProcessId_r11 csi_ProcessId_r11;
	NhuCSI_RS_ConfigNZPId_r11 csi_RS_ConfigNZPId_r11;
	NhuCSI_IM_ConfigId_r11 csi_IM_ConfigId_r11;
	NhuCSI_Process_r11p_C_AndCBSRLst_r11 p_C_AndCBSRLst_r11;
	NhuCQI_ReportBothProc_r11 cqi_ReportBothProc_r11;
	NhuCSI_Process_r11cqi_ReportPeriodicProcId_r11 cqi_ReportPeriodicProcId_r11;
	NhuCQI_ReportAperiodicProc_r11 cqi_ReportAperiodicProc_r11;
} NhuCSI_Process_r11;

typedef struct NhuCSI_ProcessToAddModLst_r11
{
	TknU16 noComp;
	NhuCSI_Process_r11 *member;
}NhuCSI_ProcessToAddModLst_r11;

typedef struct NhuCQI_ReportBoth_r11
{
	TknPres pres;
	NhuCSI_IM_ConfigToRlsLst_r11 csi_IM_ConfigToRlsLst_r11;
	NhuCSI_IM_ConfigToAddModLst_r11 csi_IM_ConfigToAddModLst_r11;
	NhuCSI_ProcessToRlsLst_r11 csi_ProcessToRlsLst_r11;
	NhuCSI_ProcessToAddModLst_r11 csi_ProcessToAddModLst_r11;
} NhuCQI_ReportBoth_r11;

typedef struct NhuCQI_ReportConfig_v1130
{
	TknPres pres;
	NhuCQI_ReportPeriodic_v1130 cqi_ReportPeriodic_v1130;
	NhuCQI_ReportBoth_r11 cqi_ReportBoth_r11;
} NhuCQI_ReportConfig_v1130;

typedef TknU32 NhuPUCCH_ConfigDedicated_v1130n1PUCCH_AN_CS_v1130setupn1PUCCH_AN_CS_LstP1_r11Member;

typedef struct NhuPUCCH_ConfigDedicated_v1130n1PUCCH_AN_CS_v1130setupn1PUCCH_AN_CS_LstP1_r11
{
	TknU16 noComp;
	NhuPUCCH_ConfigDedicated_v1130n1PUCCH_AN_CS_v1130setupn1PUCCH_AN_CS_LstP1_r11Member *member;
}NhuPUCCH_ConfigDedicated_v1130n1PUCCH_AN_CS_v1130setupn1PUCCH_AN_CS_LstP1_r11;

typedef struct NhuPUCCH_ConfigDedicated_v1130n1PUCCH_AN_CS_v1130setup
{
	TknPres pres;
	NhuPUCCH_ConfigDedicated_v1130n1PUCCH_AN_CS_v1130setupn1PUCCH_AN_CS_LstP1_r11 n1PUCCH_AN_CS_LstP1_r11;
} NhuPUCCH_ConfigDedicated_v1130n1PUCCH_AN_CS_v1130setup;

typedef struct NhuPUCCH_ConfigDedicated_v1130n1PUCCH_AN_CS_v1130
{
	TknU8 choice;
	union {
		NhuPUCCH_ConfigDedicated_v1130n1PUCCH_AN_CS_v1130setup setup;
	} val;
} NhuPUCCH_ConfigDedicated_v1130n1PUCCH_AN_CS_v1130;

/* Element ----- nPUCCH-Identity-r11 ------- */
typedef TknU32 NhuPUCCH_ConfigDedicated_v1130nPUCCH_Param_r11setupnPUCCH_Identity_r11;

/* Element ----- n1PUCCH-AN-r11 ------- */
typedef TknU32 NhuPUCCH_ConfigDedicated_v1130nPUCCH_Param_r11setupn1PUCCH_AN_r11;

typedef struct NhuPUCCH_ConfigDedicated_v1130nPUCCH_Param_r11setup
{
	TknPres pres;
	NhuPUCCH_ConfigDedicated_v1130nPUCCH_Param_r11setupnPUCCH_Identity_r11 nPUCCH_Identity_r11;
	NhuPUCCH_ConfigDedicated_v1130nPUCCH_Param_r11setupn1PUCCH_AN_r11 n1PUCCH_AN_r11;
} NhuPUCCH_ConfigDedicated_v1130nPUCCH_Param_r11setup;

typedef struct NhuPUCCH_ConfigDedicated_v1130nPUCCH_Param_r11
{
	TknU8 choice;
	union {
		NhuPUCCH_ConfigDedicated_v1130nPUCCH_Param_r11setup setup;
	} val;
} NhuPUCCH_ConfigDedicated_v1130nPUCCH_Param_r11;

typedef struct NhuPUCCH_ConfigDedicated_v1130
{
	TknPres pres;
	NhuPUCCH_ConfigDedicated_v1130n1PUCCH_AN_CS_v1130 n1PUCCH_AN_CS_v1130;
	NhuPUCCH_ConfigDedicated_v1130nPUCCH_Param_r11 nPUCCH_Param_r11;
} NhuPUCCH_ConfigDedicated_v1130;

/* Element ----- nPUSCH-Identity-r11 ------- */
typedef TknU32 NhuPUSCH_ConfigDedicated_v1130pusch_DMRS_r11setupnPUSCH_Identity_r11;

/* Element ----- nDMRS-CSH-Identity-r11 ------- */
typedef TknU32 NhuPUSCH_ConfigDedicated_v1130pusch_DMRS_r11setupnDMRS_CSH_Identity_r11;

typedef struct NhuPUSCH_ConfigDedicated_v1130pusch_DMRS_r11setup
{
	TknPres pres;
	NhuPUSCH_ConfigDedicated_v1130pusch_DMRS_r11setupnPUSCH_Identity_r11 nPUSCH_Identity_r11;
	NhuPUSCH_ConfigDedicated_v1130pusch_DMRS_r11setupnDMRS_CSH_Identity_r11 nDMRS_CSH_Identity_r11;
} NhuPUSCH_ConfigDedicated_v1130pusch_DMRS_r11setup;

typedef struct NhuPUSCH_ConfigDedicated_v1130pusch_DMRS_r11
{
	TknU8 choice;
	union {
		NhuPUSCH_ConfigDedicated_v1130pusch_DMRS_r11setup setup;
	} val;
} NhuPUSCH_ConfigDedicated_v1130pusch_DMRS_r11;

typedef struct NhuPUSCH_ConfigDedicated_v1130
{
	TknPres pres;
	NhuPUSCH_ConfigDedicated_v1130pusch_DMRS_r11 pusch_DMRS_r11;
} NhuPUSCH_ConfigDedicated_v1130;

/* Element ----- deltaTxD-OffsetPUCCH-Format1bCS-r11 ------- */
typedef enum enumNhuDeltaTxD_OffsetLstPUCCH_v1130deltaTxD_OffsetPUCCH_Format1bCS_r11
{
	NhuDeltaTxD_OffsetLstPUCCH_v1130deltaTxD_OffsetPUCCH_Format1bCS_r11dB0Enum,
	NhuDeltaTxD_OffsetLstPUCCH_v1130deltaTxD_OffsetPUCCH_Format1bCS_r11dB_1Enum
} EnumNhuDeltaTxD_OffsetLstPUCCH_v1130deltaTxD_OffsetPUCCH_Format1bCS_r11;
typedef TknU32 NhuDeltaTxD_OffsetLstPUCCH_v1130deltaTxD_OffsetPUCCH_Format1bCS_r11;

typedef struct NhuDeltaTxD_OffsetLstPUCCH_v1130
{
	TknPres pres;
	NhuDeltaTxD_OffsetLstPUCCH_v1130deltaTxD_OffsetPUCCH_Format1bCS_r11 deltaTxD_OffsetPUCCH_Format1bCS_r11;
} NhuDeltaTxD_OffsetLstPUCCH_v1130;

/* Element ----- pSRS-Offset-v1130 ------- */
typedef TknU32 NhuUlnkPowerCntrlDedicated_v1130pSRS_Offset_v1130;

/* Element ----- pSRS-OffsetAp-v1130 ------- */
typedef TknU32 NhuUlnkPowerCntrlDedicated_v1130pSRS_OffsetAp_v1130;

typedef struct NhuUlnkPowerCntrlDedicated_v1130
{
	TknPres pres;
	NhuUlnkPowerCntrlDedicated_v1130pSRS_Offset_v1130 pSRS_Offset_v1130;
	NhuUlnkPowerCntrlDedicated_v1130pSRS_OffsetAp_v1130 pSRS_OffsetAp_v1130;
	NhuDeltaTxD_OffsetLstPUCCH_v1130 deltaTxD_OffsetLstPUCCH_v1130;
} NhuUlnkPowerCntrlDedicated_v1130;

typedef struct NhuPhysicalConfigDedicatedantennaInfo
{
	TknU8 choice;
	union {
		NhuAntennaInfoDedicated explicitValue;
	} val;
} NhuPhysicalConfigDedicatedantennaInfo;

typedef struct NhuPhysicalConfigDedicatedextaddgrp_2antennaInfo_r10
{
	TknU8 choice;
	union {
		NhuAntennaInfoDedicated_r10 explicitValue_r10;
	} val;
} NhuPhysicalConfigDedicatedextaddgrp_2antennaInfo_r10;

/* Element ----- cif-Presence-r10 ------- */
typedef TknU8 NhuPhysicalConfigDedicatedextaddgrp_2cif_Presence_r10;

typedef struct NhuPhysicalConfigDedicatedextaddgrp_3additionalSpectrumEmissionCA_r10setup
{
	TknPres pres;
	NhuAdditionalSpectrumEmission additionalSpectrumEmissionPCell_r10;
} NhuPhysicalConfigDedicatedextaddgrp_3additionalSpectrumEmissionCA_r10setup;

typedef struct NhuPhysicalConfigDedicatedextaddgrp_3additionalSpectrumEmissionCA_r10
{
	TknU8 choice;
	union {
		NhuPhysicalConfigDedicatedextaddgrp_3additionalSpectrumEmissionCA_r10setup setup;
	} val;
} NhuPhysicalConfigDedicatedextaddgrp_3additionalSpectrumEmissionCA_r10;

typedef struct NhuPhysicalConfigDedicatedextaddgrp_1
{
	TknPres pres;
	NhuCQI_ReportConfig_v920 cqi_ReportConfig_v920;
	NhuAntennaInfoDedicated_v920 antennaInfo_v920;
} NhuPhysicalConfigDedicatedextaddgrp_1;

typedef struct NhuPhysicalConfigDedicatedextaddgrp_2
{
	TknPres pres;
	NhuPhysicalConfigDedicatedextaddgrp_2antennaInfo_r10 antennaInfo_r10;
	NhuAntennaInfoUL_r10 antennaInfoUL_r10;
	NhuPhysicalConfigDedicatedextaddgrp_2cif_Presence_r10 cif_Presence_r10;
	NhuCQI_ReportConfig_r10 cqi_ReportConfig_r10;
	NhuCSI_RS_Config_r10 csi_RS_Config_r10;
	NhuPUCCH_ConfigDedicated_v1020 pucch_ConfigDedicated_v1020;
	NhuPUSCH_ConfigDedicated_v1020 pusch_ConfigDedicated_v1020;
	NhuSchedulingRqstConfig_v1020 schedulingRqstConfig_v1020;
	NhuSoundingRS_UL_ConfigDedicated_v1020 soundingRS_UL_ConfigDedicated_v1020;
	NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10 soundingRS_UL_ConfigDedicatedAperiodic_r10;
	NhuUlnkPowerCntrlDedicated_v1020 uplinkPowerCntrlDedicated_v1020;
} NhuPhysicalConfigDedicatedextaddgrp_2;

typedef struct NhuPhysicalConfigDedicatedextaddgrp_3
{
	TknPres pres;
	NhuPhysicalConfigDedicatedextaddgrp_3additionalSpectrumEmissionCA_r10 additionalSpectrumEmissionCA_r10;
} NhuPhysicalConfigDedicatedextaddgrp_3;

typedef struct NhuPhysicalConfigDedicatedextaddgrp_4
{
	TknPres pres;
	NhuCSI_RS_ConfigNZPToRlsLst_r11 csi_RS_ConfigNZPToRlsLst_r11;
	NhuCSI_RS_ConfigNZPToAddModLst_r11 csi_RS_ConfigNZPToAddModLst_r11;
	NhuCSI_RS_ConfigZPToRlsLst_r11 csi_RS_ConfigZPToRlsLst_r11;
	NhuCSI_RS_ConfigZPToAddModLst_r11 csi_RS_ConfigZPToAddModLst_r11;
	NhuEPDCCH_Config_r11 epdcch_Config_r11;
	NhuPDSCH_ConfigDedicated_v1130 pdsch_ConfigDedicated_v1130;
	NhuCQI_ReportConfig_v1130 cqi_ReportConfig_v1130;
	NhuPUCCH_ConfigDedicated_v1130 pucch_ConfigDedicated_v1130;
	NhuPUSCH_ConfigDedicated_v1130 pusch_ConfigDedicated_v1130;
	NhuUlnkPowerCntrlDedicated_v1130 uplinkPowerCntrlDedicated_v1130;
} NhuPhysicalConfigDedicatedextaddgrp_4;

typedef struct NhuPhysicalConfigDedicated
{
	TknPres pres;
	NhuPDSCH_ConfigDedicated pdsch_ConfigDedicated;
	NhuPUCCH_ConfigDedicated pucch_ConfigDedicated;
	NhuPUSCH_ConfigDedicated pusch_ConfigDedicated;
	NhuUlnkPowerCntrlDedicated uplinkPowerCntrlDedicated;
	NhuTPC_PDCCH_Config tpc_PDCCH_ConfigPUCCH;
	NhuTPC_PDCCH_Config tpc_PDCCH_ConfigPUSCH;
	NhuCQI_ReportConfig cqi_ReportConfig;
	NhuSoundingRS_UL_ConfigDedicated soundingRS_UL_ConfigDedicated;
	NhuPhysicalConfigDedicatedantennaInfo antennaInfo;
	NhuSchedulingRqstConfig schedulingRqstConfig;
	NhuPhysicalConfigDedicatedextaddgrp_1 extaddgrp_1;
	NhuPhysicalConfigDedicatedextaddgrp_2 extaddgrp_2;
	NhuPhysicalConfigDedicatedextaddgrp_3 extaddgrp_3;
	NhuPhysicalConfigDedicatedextaddgrp_4 extaddgrp_4;
} NhuPhysicalConfigDedicated;

/* Element ----- t301-r9 ------- */
typedef enum enumNhuRLF_TmrsAndConsts_r9setupt301_r9
{
	NhuRLF_TmrsAndConsts_r9setupt301_r9ms100Enum,
	NhuRLF_TmrsAndConsts_r9setupt301_r9ms200Enum,
	NhuRLF_TmrsAndConsts_r9setupt301_r9ms300Enum,
	NhuRLF_TmrsAndConsts_r9setupt301_r9ms400Enum,
	NhuRLF_TmrsAndConsts_r9setupt301_r9ms600Enum,
	NhuRLF_TmrsAndConsts_r9setupt301_r9ms1000Enum,
	NhuRLF_TmrsAndConsts_r9setupt301_r9ms1500Enum,
	NhuRLF_TmrsAndConsts_r9setupt301_r9ms2000Enum
} EnumNhuRLF_TmrsAndConsts_r9setupt301_r9;
typedef TknU32 NhuRLF_TmrsAndConsts_r9setupt301_r9;

/* Element ----- t310-r9 ------- */
typedef enum enumNhuRLF_TmrsAndConsts_r9setupt310_r9
{
	NhuRLF_TmrsAndConsts_r9setupt310_r9ms0Enum,
	NhuRLF_TmrsAndConsts_r9setupt310_r9ms50Enum,
	NhuRLF_TmrsAndConsts_r9setupt310_r9ms100Enum,
	NhuRLF_TmrsAndConsts_r9setupt310_r9ms200Enum,
	NhuRLF_TmrsAndConsts_r9setupt310_r9ms500Enum,
	NhuRLF_TmrsAndConsts_r9setupt310_r9ms1000Enum,
	NhuRLF_TmrsAndConsts_r9setupt310_r9ms2000Enum
} EnumNhuRLF_TmrsAndConsts_r9setupt310_r9;
typedef TknU32 NhuRLF_TmrsAndConsts_r9setupt310_r9;

/* Element ----- n310-r9 ------- */
typedef enum enumNhuRLF_TmrsAndConsts_r9setupn310_r9
{
	NhuRLF_TmrsAndConsts_r9setupn310_r9n1Enum,
	NhuRLF_TmrsAndConsts_r9setupn310_r9n2Enum,
	NhuRLF_TmrsAndConsts_r9setupn310_r9n3Enum,
	NhuRLF_TmrsAndConsts_r9setupn310_r9n4Enum,
	NhuRLF_TmrsAndConsts_r9setupn310_r9n6Enum,
	NhuRLF_TmrsAndConsts_r9setupn310_r9n8Enum,
	NhuRLF_TmrsAndConsts_r9setupn310_r9n10Enum,
	NhuRLF_TmrsAndConsts_r9setupn310_r9n20Enum
} EnumNhuRLF_TmrsAndConsts_r9setupn310_r9;
typedef TknU32 NhuRLF_TmrsAndConsts_r9setupn310_r9;

/* Element ----- t311-r9 ------- */
typedef enum enumNhuRLF_TmrsAndConsts_r9setupt311_r9
{
	NhuRLF_TmrsAndConsts_r9setupt311_r9ms1000Enum,
	NhuRLF_TmrsAndConsts_r9setupt311_r9ms3000Enum,
	NhuRLF_TmrsAndConsts_r9setupt311_r9ms5000Enum,
	NhuRLF_TmrsAndConsts_r9setupt311_r9ms10000Enum,
	NhuRLF_TmrsAndConsts_r9setupt311_r9ms15000Enum,
	NhuRLF_TmrsAndConsts_r9setupt311_r9ms20000Enum,
	NhuRLF_TmrsAndConsts_r9setupt311_r9ms30000Enum
} EnumNhuRLF_TmrsAndConsts_r9setupt311_r9;
typedef TknU32 NhuRLF_TmrsAndConsts_r9setupt311_r9;

/* Element ----- n311-r9 ------- */
typedef enum enumNhuRLF_TmrsAndConsts_r9setupn311_r9
{
	NhuRLF_TmrsAndConsts_r9setupn311_r9n1Enum,
	NhuRLF_TmrsAndConsts_r9setupn311_r9n2Enum,
	NhuRLF_TmrsAndConsts_r9setupn311_r9n3Enum,
	NhuRLF_TmrsAndConsts_r9setupn311_r9n4Enum,
	NhuRLF_TmrsAndConsts_r9setupn311_r9n5Enum,
	NhuRLF_TmrsAndConsts_r9setupn311_r9n6Enum,
	NhuRLF_TmrsAndConsts_r9setupn311_r9n8Enum,
	NhuRLF_TmrsAndConsts_r9setupn311_r9n10Enum
} EnumNhuRLF_TmrsAndConsts_r9setupn311_r9;
typedef TknU32 NhuRLF_TmrsAndConsts_r9setupn311_r9;

typedef struct NhuRLF_TmrsAndConsts_r9setup
{
	TknPres pres;
	NhuRLF_TmrsAndConsts_r9setupt301_r9 t301_r9;
	NhuRLF_TmrsAndConsts_r9setupt310_r9 t310_r9;
	NhuRLF_TmrsAndConsts_r9setupn310_r9 n310_r9;
	NhuRLF_TmrsAndConsts_r9setupt311_r9 t311_r9;
	NhuRLF_TmrsAndConsts_r9setupn311_r9 n311_r9;
} NhuRLF_TmrsAndConsts_r9setup;

typedef struct NhuRLF_TmrsAndConsts_r9
{
	TknU8 choice;
	union {
		NhuRLF_TmrsAndConsts_r9setup setup;
	} val;
} NhuRLF_TmrsAndConsts_r9;

typedef struct NhuMeasSubfrmPatternPCell_r10
{
	TknU8 choice;
	union {
		NhuMeasSubfrmPattern_r10 setup;
	} val;
} NhuMeasSubfrmPatternPCell_r10;

/* Element ----- antennaPortsCount-r11 ------- */
typedef enum enumNhuCRS_AssistanceInfo_r11antennaPortsCount_r11
{
	NhuCRS_AssistanceInfo_r11antennaPortsCount_r11an1Enum,
	NhuCRS_AssistanceInfo_r11antennaPortsCount_r11an2Enum,
	NhuCRS_AssistanceInfo_r11antennaPortsCount_r11an4Enum,
	NhuCRS_AssistanceInfo_r11antennaPortsCount_r11spare1Enum
} EnumNhuCRS_AssistanceInfo_r11antennaPortsCount_r11;
typedef TknU32 NhuCRS_AssistanceInfo_r11antennaPortsCount_r11;

typedef struct NhuCRS_AssistanceInfo_r11
{
	TknPres pres;
	NhuPhysCellId physCellId_r11;
	NhuCRS_AssistanceInfo_r11antennaPortsCount_r11 antennaPortsCount_r11;
	NhuMBSFN_SubfrmConfigLst mbsfn_SubfrmConfigLst_r11;
} NhuCRS_AssistanceInfo_r11;

typedef struct NhuCRS_AssistanceInfoLst_r11
{
	TknU16 noComp;
	NhuCRS_AssistanceInfo_r11 *member;
}NhuCRS_AssistanceInfoLst_r11;

typedef struct NhuNeighCellsCRS_Info_r11
{
	TknU8 choice;
	union {
		NhuCRS_AssistanceInfoLst_r11 setup;
	} val;
} NhuNeighCellsCRS_Info_r11;

typedef struct NhuRadioResourceConfigDedicatedmac_MainConfig
{
	TknU8 choice;
	union {
		NhuMAC_MainConfig explicitValue;
	} val;
} NhuRadioResourceConfigDedicatedmac_MainConfig;

typedef struct NhuRadioResourceConfigDedicatedextaddgrp_1
{
	TknPres pres;
	NhuRLF_TmrsAndConsts_r9 rlf_TmrsAndConsts_r9;
} NhuRadioResourceConfigDedicatedextaddgrp_1;

typedef struct NhuRadioResourceConfigDedicatedextaddgrp_2
{
	TknPres pres;
	NhuMeasSubfrmPatternPCell_r10 measSubfrmPatternPCell_r10;
} NhuRadioResourceConfigDedicatedextaddgrp_2;

typedef struct NhuRadioResourceConfigDedicatedextaddgrp_3
{
	TknPres pres;
	NhuNeighCellsCRS_Info_r11 neighCellsCRS_Info_r11;
} NhuRadioResourceConfigDedicatedextaddgrp_3;

typedef struct NhuRadioResourceConfigDedicated
{
	TknPres pres;
	NhuSRB_ToAddModLst srb_ToAddModLst;
	NhuDRB_ToAddModLst drb_ToAddModLst;
	NhuDRB_ToRlsLst drb_ToRlsLst;
	NhuRadioResourceConfigDedicatedmac_MainConfig mac_MainConfig;
	NhuSPS_Config sps_Config;
	NhuPhysicalConfigDedicated physicalConfigDedicated;
	NhuRadioResourceConfigDedicatedextaddgrp_1 extaddgrp_1;
	NhuRadioResourceConfigDedicatedextaddgrp_2 extaddgrp_2;
	NhuRadioResourceConfigDedicatedextaddgrp_3 extaddgrp_3;
} NhuRadioResourceConfigDedicated;

/* Element ----- NextHopChainingCount ------- */
typedef TknU32 NhuNextHopChainingCount;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuRRCConReestb_v8a0_IEslateNonCriticalExtn;
typedef struct NhuRRCConReestb_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuRRCConReestb_v8a0_IEsnonCriticalExtn;

typedef struct NhuRRCConReestb_v8a0_IEs
{
	TknPres pres;
	NhuRRCConReestb_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuRRCConReestb_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuRRCConReestb_v8a0_IEs;

typedef struct NhuRRCConReestb_r8_IEs
{
	TknPres pres;
	NhuRadioResourceConfigDedicated radioResourceConfigDedicated;
	NhuNextHopChainingCount nextHopChainingCount;
	NhuRRCConReestb_v8a0_IEs nonCriticalExtn;
} NhuRRCConReestb_r8_IEs;

typedef struct NhuRRCConReestbcriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuRRCConReestb_r8_IEs rrcConReestb_r8;
	} val;
} NhuRRCConReestbcriticalExtnsc1;

typedef struct NhuRRCConReestbcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuRRCConReestbcriticalExtnscriticalExtnsFuture;

typedef struct NhuRRCConReestbcriticalExtns
{
	TknU8 choice;
	union {
		NhuRRCConReestbcriticalExtnsc1 c1;
		NhuRRCConReestbcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuRRCConReestbcriticalExtns;

typedef struct NhuRRCConReestb
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuRRCConReestbcriticalExtns criticalExtns;
} NhuRRCConReestb;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuRRCConReestbRej_v8a0_IEslateNonCriticalExtn;
typedef struct NhuRRCConReestbRej_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuRRCConReestbRej_v8a0_IEsnonCriticalExtn;

typedef struct NhuRRCConReestbRej_v8a0_IEs
{
	TknPres pres;
	NhuRRCConReestbRej_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuRRCConReestbRej_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuRRCConReestbRej_v8a0_IEs;

typedef struct NhuRRCConReestbRej_r8_IEs
{
	TknPres pres;
	NhuRRCConReestbRej_v8a0_IEs nonCriticalExtn;
} NhuRRCConReestbRej_r8_IEs;

typedef struct NhuRRCConReestbRejcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuRRCConReestbRejcriticalExtnscriticalExtnsFuture;

typedef struct NhuRRCConReestbRejcriticalExtns
{
	TknU8 choice;
	union {
		NhuRRCConReestbRej_r8_IEs rrcConReestbRej_r8;
		NhuRRCConReestbRejcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuRRCConReestbRejcriticalExtns;

typedef struct NhuRRCConReestbRej
{
	TknPres pres;
	NhuRRCConReestbRejcriticalExtns criticalExtns;
} NhuRRCConReestbRej;

/* Element ----- deprioritisationType-r11 ------- */
typedef enum enumNhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTyp_r11
{
	NhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTyp_r11frequencyEnum,
	NhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTyp_r11e_utraEnum
} EnumNhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTyp_r11;
typedef TknU32 NhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTyp_r11;

/* Element ----- deprioritisationTimer-r11 ------- */
typedef enum enumNhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTimer_r11
{
	NhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTimer_r11min5Enum,
	NhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTimer_r11min10Enum,
	NhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTimer_r11min15Enum,
	NhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTimer_r11min30Enum
} EnumNhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTimer_r11;
typedef TknU32 NhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTimer_r11;

typedef struct NhuRRCConRej_v1130_IEsdeprioritisationReq_r11
{
	TknPres pres;
	NhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTyp_r11 deprioritisationTyp_r11;
	NhuRRCConRej_v1130_IEsdeprioritisationReq_r11deprioritisationTimer_r11 deprioritisationTimer_r11;
} NhuRRCConRej_v1130_IEsdeprioritisationReq_r11;

typedef struct NhuRRCConRej_v1130_IEsnonCriticalExtn
{
	TknPres pres;
} NhuRRCConRej_v1130_IEsnonCriticalExtn;

typedef struct NhuRRCConRej_v1130_IEs
{
	TknPres pres;
	NhuRRCConRej_v1130_IEsdeprioritisationReq_r11 deprioritisationReq_r11;
	NhuRRCConRej_v1130_IEsnonCriticalExtn nonCriticalExtn;
} NhuRRCConRej_v1130_IEs;

/* Element ----- extendedWaitTime-r10 ------- */
typedef TknU32 NhuRRCConRej_v1020_IEsextendedWaitTime_r10;

typedef struct NhuRRCConRej_v1020_IEs
{
	TknPres pres;
	NhuRRCConRej_v1020_IEsextendedWaitTime_r10 extendedWaitTime_r10;
	NhuRRCConRej_v1130_IEs nonCriticalExtn;
} NhuRRCConRej_v1020_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuRRCConRej_v8a0_IEslateNonCriticalExtn;
typedef struct NhuRRCConRej_v8a0_IEs
{
	TknPres pres;
	NhuRRCConRej_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuRRCConRej_v1020_IEs nonCriticalExtn;
} NhuRRCConRej_v8a0_IEs;

/* Element ----- waitTime ------- */
typedef TknU32 NhuRRCConRej_r8_IEswaitTime;

typedef struct NhuRRCConRej_r8_IEs
{
	TknPres pres;
	NhuRRCConRej_r8_IEswaitTime waitTime;
	NhuRRCConRej_v8a0_IEs nonCriticalExtn;
} NhuRRCConRej_r8_IEs;

typedef struct NhuRRCConRejcriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuRRCConRej_r8_IEs rrcConRej_r8;
	} val;
} NhuRRCConRejcriticalExtnsc1;

typedef struct NhuRRCConRejcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuRRCConRejcriticalExtnscriticalExtnsFuture;

typedef struct NhuRRCConRejcriticalExtns
{
	TknU8 choice;
	union {
		NhuRRCConRejcriticalExtnsc1 c1;
		NhuRRCConRejcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuRRCConRejcriticalExtns;

typedef struct NhuRRCConRej
{
	TknPres pres;
	NhuRRCConRejcriticalExtns criticalExtns;
} NhuRRCConRej;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuRRCConSetup_v8a0_IEslateNonCriticalExtn;
typedef struct NhuRRCConSetup_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuRRCConSetup_v8a0_IEsnonCriticalExtn;

typedef struct NhuRRCConSetup_v8a0_IEs
{
	TknPres pres;
	NhuRRCConSetup_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuRRCConSetup_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuRRCConSetup_v8a0_IEs;

typedef struct NhuRRCConSetup_r8_IEs
{
	TknPres pres;
	NhuRadioResourceConfigDedicated radioResourceConfigDedicated;
	NhuRRCConSetup_v8a0_IEs nonCriticalExtn;
} NhuRRCConSetup_r8_IEs;

typedef struct NhuRRCConSetupcriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuRRCConSetup_r8_IEs rrcConSetup_r8;
	} val;
} NhuRRCConSetupcriticalExtnsc1;

typedef struct NhuRRCConSetupcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuRRCConSetupcriticalExtnscriticalExtnsFuture;

typedef struct NhuRRCConSetupcriticalExtns
{
	TknU8 choice;
	union {
		NhuRRCConSetupcriticalExtnsc1 c1;
		NhuRRCConSetupcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuRRCConSetupcriticalExtns;

typedef struct NhuRRCConSetup
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuRRCConSetupcriticalExtns criticalExtns;
} NhuRRCConSetup;

typedef struct NhuDL_CCCH_MsgTypc1
{
	TknU8 choice;
	union {
		NhuRRCConReestb rrcConReestb;
		NhuRRCConReestbRej rrcConReestbRej;
		NhuRRCConRej rrcConRej;
		NhuRRCConSetup rrcConSetup;
	} val;
} NhuDL_CCCH_MsgTypc1;

typedef struct NhuDL_CCCH_MsgTypmessageClassExtn
{
	TknPres pres;
} NhuDL_CCCH_MsgTypmessageClassExtn;

typedef struct NhuDL_CCCH_MsgTyp
{
	TknU8 choice;
	union {
		NhuDL_CCCH_MsgTypc1 c1;
		NhuDL_CCCH_MsgTypmessageClassExtn messageClassExtn;
	} val;
} NhuDL_CCCH_MsgTyp;

typedef struct NhuDL_CCCH_Msg
{
	TknPres pres;
	NhuDL_CCCH_MsgTyp message;
} NhuDL_CCCH_Msg;

/* Element ---------- RAND-CDMA2000 ----------- */
typedef TknStrBSXL NhuRAND_CDMA2000;
/* Element ---------- MobilityParametersCDMA2000 ----------- */
typedef TknStrOSXL NhuMobilityParamsCDMA2000;
/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuCSFBParamsRspCDMA2000_v8a0_IEslateNonCriticalExtn;
typedef struct NhuCSFBParamsRspCDMA2000_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuCSFBParamsRspCDMA2000_v8a0_IEsnonCriticalExtn;

typedef struct NhuCSFBParamsRspCDMA2000_v8a0_IEs
{
	TknPres pres;
	NhuCSFBParamsRspCDMA2000_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuCSFBParamsRspCDMA2000_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuCSFBParamsRspCDMA2000_v8a0_IEs;

typedef struct NhuCSFBParamsRspCDMA2000_r8_IEs
{
	TknPres pres;
	NhuRAND_CDMA2000 rand;
	NhuMobilityParamsCDMA2000 mobilityParams;
	NhuCSFBParamsRspCDMA2000_v8a0_IEs nonCriticalExtn;
} NhuCSFBParamsRspCDMA2000_r8_IEs;

typedef struct NhuCSFBParamsRspCDMA2000criticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuCSFBParamsRspCDMA2000criticalExtnscriticalExtnsFuture;

typedef struct NhuCSFBParamsRspCDMA2000criticalExtns
{
	TknU8 choice;
	union {
		NhuCSFBParamsRspCDMA2000_r8_IEs csfbParamsRspCDMA2000_r8;
		NhuCSFBParamsRspCDMA2000criticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuCSFBParamsRspCDMA2000criticalExtns;

typedef struct NhuCSFBParamsRspCDMA2000
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuCSFBParamsRspCDMA2000criticalExtns criticalExtns;
} NhuCSFBParamsRspCDMA2000;

/* Element ---------- DedicatedInfoNAS ----------- */
typedef TknStrOSXL NhuDedicatedInfoNAS;
/* Element ---------- DedicatedInfoCDMA2000 ----------- */
typedef TknStrOSXL NhuDedicatedInfoCDMA2000;
/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuDLInfoTfr_v8a0_IEslateNonCriticalExtn;
typedef struct NhuDLInfoTfr_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuDLInfoTfr_v8a0_IEsnonCriticalExtn;

typedef struct NhuDLInfoTfr_v8a0_IEs
{
	TknPres pres;
	NhuDLInfoTfr_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuDLInfoTfr_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuDLInfoTfr_v8a0_IEs;

typedef struct NhuDLInfoTfr_r8_IEsdedicatedInfoTyp
{
	TknU8 choice;
	union {
		NhuDedicatedInfoNAS dedicatedInfoNAS;
		NhuDedicatedInfoCDMA2000 dedicatedInfoCDMA2000_1XRTT;
		NhuDedicatedInfoCDMA2000 dedicatedInfoCDMA2000_HRPD;
	} val;
} NhuDLInfoTfr_r8_IEsdedicatedInfoTyp;

typedef struct NhuDLInfoTfr_r8_IEs
{
	TknPres pres;
	NhuDLInfoTfr_r8_IEsdedicatedInfoTyp dedicatedInfoTyp;
	NhuDLInfoTfr_v8a0_IEs nonCriticalExtn;
} NhuDLInfoTfr_r8_IEs;

typedef struct NhuDLInfoTfrcriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuDLInfoTfr_r8_IEs dlInfoTfr_r8;
	} val;
} NhuDLInfoTfrcriticalExtnsc1;

typedef struct NhuDLInfoTfrcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuDLInfoTfrcriticalExtnscriticalExtnsFuture;

typedef struct NhuDLInfoTfrcriticalExtns
{
	TknU8 choice;
	union {
		NhuDLInfoTfrcriticalExtnsc1 c1;
		NhuDLInfoTfrcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuDLInfoTfrcriticalExtns;

typedef struct NhuDLInfoTfr
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuDLInfoTfrcriticalExtns criticalExtns;
} NhuDLInfoTfr;

/* Element ----- CDMA2000-Type ------- */
typedef enum enumNhuCDMA2000_Typ
{
	NhuCDMA2000_Typtype1XRTTEnum,
	NhuCDMA2000_TyptypeHRPDEnum
} EnumNhuCDMA2000_Typ;
typedef TknU32 NhuCDMA2000_Typ;

typedef struct NhuCarrierFreqCDMA2000
{
	TknPres pres;
	NhuBandclassCDMA2000 bandClass;
	NhuARFCN_ValueCDMA2000 arfcn;
} NhuCarrierFreqCDMA2000;

/* Element ----- dualRxTxRedirectIndicator-r10 ------- */
typedef enum enumNhuHovrFromEUTRAPrepRqst_v1020_IEsdualRxTxRedirectIndicator_r10
{
	NhuHovrFromEUTRAPrepRqst_v1020_IEsdualRxTxRedirectIndicator_r10trueEnum
} EnumNhuHovrFromEUTRAPrepRqst_v1020_IEsdualRxTxRedirectIndicator_r10;
typedef TknU32 NhuHovrFromEUTRAPrepRqst_v1020_IEsdualRxTxRedirectIndicator_r10;

typedef struct NhuHovrFromEUTRAPrepRqst_v1020_IEsnonCriticalExtn
{
	TknPres pres;
} NhuHovrFromEUTRAPrepRqst_v1020_IEsnonCriticalExtn;

typedef struct NhuHovrFromEUTRAPrepRqst_v1020_IEs
{
	TknPres pres;
	NhuHovrFromEUTRAPrepRqst_v1020_IEsdualRxTxRedirectIndicator_r10 dualRxTxRedirectIndicator_r10;
	NhuCarrierFreqCDMA2000 redirectCarrierCDMA2000_1XRTT_r10;
	NhuHovrFromEUTRAPrepRqst_v1020_IEsnonCriticalExtn nonCriticalExtn;
} NhuHovrFromEUTRAPrepRqst_v1020_IEs;

/* Element ----- concurrPrepCDMA2000-HRPD-r9 ------- */
typedef TknU8 NhuHovrFromEUTRAPrepRqst_v920_IEsconcurrPrepCDMA2000_HRPD_r9;

typedef struct NhuHovrFromEUTRAPrepRqst_v920_IEs
{
	TknPres pres;
	NhuHovrFromEUTRAPrepRqst_v920_IEsconcurrPrepCDMA2000_HRPD_r9 concurrPrepCDMA2000_HRPD_r9;
	NhuHovrFromEUTRAPrepRqst_v1020_IEs nonCriticalExtn;
} NhuHovrFromEUTRAPrepRqst_v920_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuHovrFromEUTRAPrepRqst_v890_IEslateNonCriticalExtn;
typedef struct NhuHovrFromEUTRAPrepRqst_v890_IEs
{
	TknPres pres;
	NhuHovrFromEUTRAPrepRqst_v890_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuHovrFromEUTRAPrepRqst_v920_IEs nonCriticalExtn;
} NhuHovrFromEUTRAPrepRqst_v890_IEs;

typedef struct NhuHovrFromEUTRAPrepRqst_r8_IEs
{
	TknPres pres;
	NhuCDMA2000_Typ cdma2000_Typ;
	NhuRAND_CDMA2000 rand;
	NhuMobilityParamsCDMA2000 mobilityParams;
	NhuHovrFromEUTRAPrepRqst_v890_IEs nonCriticalExtn;
} NhuHovrFromEUTRAPrepRqst_r8_IEs;

typedef struct NhuHovrFromEUTRAPrepRqstcriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuHovrFromEUTRAPrepRqst_r8_IEs handoverFromEUTRAPrepRqst_r8;
	} val;
} NhuHovrFromEUTRAPrepRqstcriticalExtnsc1;

typedef struct NhuHovrFromEUTRAPrepRqstcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuHovrFromEUTRAPrepRqstcriticalExtnscriticalExtnsFuture;

typedef struct NhuHovrFromEUTRAPrepRqstcriticalExtns
{
	TknU8 choice;
	union {
		NhuHovrFromEUTRAPrepRqstcriticalExtnsc1 c1;
		NhuHovrFromEUTRAPrepRqstcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuHovrFromEUTRAPrepRqstcriticalExtns;

typedef struct NhuHovrFromEUTRAPrepRqst
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuHovrFromEUTRAPrepRqstcriticalExtns criticalExtns;
} NhuHovrFromEUTRAPrepRqst;

/* Element ---------- (null) ----------- */
typedef TknStrOSXL NhuSysInfoLstGERANMember;
typedef struct NhuSysInfoLstGERAN
{
	TknU16 noComp;
	NhuSysInfoLstGERANMember *member;
}NhuSysInfoLstGERAN;

typedef struct NhuSI_OrPSI_GERAN
{
	TknU8 choice;
	union {
		NhuSysInfoLstGERAN si;
		NhuSysInfoLstGERAN psi;
	} val;
} NhuSI_OrPSI_GERAN;

/* Element ----- targetRAT-Type ------- */
typedef enum enumNhuHovrtargetRAT_Typ
{
	NhuHovrtargetRAT_TyputraEnum,
	NhuHovrtargetRAT_TypgeranEnum,
	NhuHovrtargetRAT_Typcdma2000_1XRTTEnum,
	NhuHovrtargetRAT_Typcdma2000_HRPDEnum,
	NhuHovrtargetRAT_Typspare4Enum,
	NhuHovrtargetRAT_Typspare3Enum,
	NhuHovrtargetRAT_Typspare2Enum,
	NhuHovrtargetRAT_Typspare1Enum
} EnumNhuHovrtargetRAT_Typ;
typedef TknU32 NhuHovrtargetRAT_Typ;

/* Element ---------- targetRAT-MessageContainer ----------- */
typedef TknStrOSXL NhuHovrtargetRAT_MsgCont;
/* Element ---------- nas-SecurityParamFromEUTRA ----------- */
typedef TknStrOSXL NhuHovrnas_SecParamFromEUTRA;
typedef struct NhuHovr
{
	TknPres pres;
	NhuHovrtargetRAT_Typ targetRAT_Typ;
	NhuHovrtargetRAT_MsgCont targetRAT_MsgCont;
	NhuHovrnas_SecParamFromEUTRA nas_SecParamFromEUTRA;
	NhuSI_OrPSI_GERAN systemInfo;
} NhuHovr;

/* Element ---------- networkColourCode ----------- */
typedef TknStrBSXL NhuPhysCellIdGERANnetworkColourCode;
/* Element ---------- baseStationColourCode ----------- */
typedef TknStrBSXL NhuPhysCellIdGERANbaseStationColourCode;
typedef struct NhuPhysCellIdGERAN
{
	TknPres pres;
	NhuPhysCellIdGERANnetworkColourCode networkColourCode;
	NhuPhysCellIdGERANbaseStationColourCode baseStationColourCode;
} NhuPhysCellIdGERAN;

typedef struct NhuCarrierFreqGERAN
{
	TknPres pres;
	NhuARFCN_ValueGERAN arfcn;
	NhuBandIndicatorGERAN bandIndicator;
} NhuCarrierFreqGERAN;

/* Element ----- t304 ------- */
typedef enum enumNhuCellChangeOrdert304
{
	NhuCellChangeOrdert304ms100Enum,
	NhuCellChangeOrdert304ms200Enum,
	NhuCellChangeOrdert304ms500Enum,
	NhuCellChangeOrdert304ms1000Enum,
	NhuCellChangeOrdert304ms2000Enum,
	NhuCellChangeOrdert304ms4000Enum,
	NhuCellChangeOrdert304ms8000Enum,
	NhuCellChangeOrdert304spare1Enum
} EnumNhuCellChangeOrdert304;
typedef TknU32 NhuCellChangeOrdert304;

/* Element ---------- networkControlOrder ----------- */
typedef TknStrBSXL NhuCellChangeOrdertargetRAT_TypgerannetworkCntrlOrder;
typedef struct NhuCellChangeOrdertargetRAT_Typgeran
{
	TknPres pres;
	NhuPhysCellIdGERAN physCellId;
	NhuCarrierFreqGERAN carrierFreq;
	NhuCellChangeOrdertargetRAT_TypgerannetworkCntrlOrder networkCntrlOrder;
	NhuSI_OrPSI_GERAN systemInfo;
} NhuCellChangeOrdertargetRAT_Typgeran;

typedef struct NhuCellChangeOrdertargetRAT_Typ
{
	TknU8 choice;
	union {
		NhuCellChangeOrdertargetRAT_Typgeran geran;
	} val;
} NhuCellChangeOrdertargetRAT_Typ;

typedef struct NhuCellChangeOrder
{
	TknPres pres;
	NhuCellChangeOrdert304 t304;
	NhuCellChangeOrdertargetRAT_Typ targetRAT_Typ;
} NhuCellChangeOrder;

typedef struct NhuMobilityFromEUTRACmd_v8d0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuMobilityFromEUTRACmd_v8d0_IEsnonCriticalExtn;

typedef struct NhuMobilityFromEUTRACmd_v8d0_IEs
{
	TknPres pres;
	NhuBandIndicatorGERAN bandIndicator;
	NhuMobilityFromEUTRACmd_v8d0_IEsnonCriticalExtn nonCriticalExtn;
} NhuMobilityFromEUTRACmd_v8d0_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuMobilityFromEUTRACmd_v8a0_IEslateNonCriticalExtn;
typedef struct NhuMobilityFromEUTRACmd_v8a0_IEs
{
	TknPres pres;
	NhuMobilityFromEUTRACmd_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuMobilityFromEUTRACmd_v8d0_IEs nonCriticalExtn;
} NhuMobilityFromEUTRACmd_v8a0_IEs;

/* Element ----- cs-FallbackIndicator ------- */
typedef TknU8 NhuMobilityFromEUTRACmd_r8_IEscs_FallbackIndicator;

typedef struct NhuMobilityFromEUTRACmd_r8_IEspurpose
{
	TknU8 choice;
	union {
		NhuHovr handover;
		NhuCellChangeOrder cellChangeOrder;
	} val;
} NhuMobilityFromEUTRACmd_r8_IEspurpose;

typedef struct NhuMobilityFromEUTRACmd_r8_IEs
{
	TknPres pres;
	NhuMobilityFromEUTRACmd_r8_IEscs_FallbackIndicator cs_FallbackIndicator;
	NhuMobilityFromEUTRACmd_r8_IEspurpose purpose;
	NhuMobilityFromEUTRACmd_v8a0_IEs nonCriticalExtn;
} NhuMobilityFromEUTRACmd_r8_IEs;

/* Element ---------- messageContCDMA2000-1XRTT-r9 ----------- */
typedef TknStrOSXL NhuE_CSFB_r9messageContCDMA2000_1XRTT_r9;
/* Element ----- mobilityCDMA2000-HRPD-r9 ------- */
typedef enum enumNhuE_CSFB_r9mobilityCDMA2000_HRPD_r9
{
	NhuE_CSFB_r9mobilityCDMA2000_HRPD_r9handoverEnum,
	NhuE_CSFB_r9mobilityCDMA2000_HRPD_r9redirectionEnum
} EnumNhuE_CSFB_r9mobilityCDMA2000_HRPD_r9;
typedef TknU32 NhuE_CSFB_r9mobilityCDMA2000_HRPD_r9;

/* Element ---------- messageContCDMA2000-HRPD-r9 ----------- */
typedef TknStrOSXL NhuE_CSFB_r9messageContCDMA2000_HRPD_r9;
typedef struct NhuE_CSFB_r9
{
	TknPres pres;
	NhuE_CSFB_r9messageContCDMA2000_1XRTT_r9 messageContCDMA2000_1XRTT_r9;
	NhuE_CSFB_r9mobilityCDMA2000_HRPD_r9 mobilityCDMA2000_HRPD_r9;
	NhuE_CSFB_r9messageContCDMA2000_HRPD_r9 messageContCDMA2000_HRPD_r9;
	NhuCarrierFreqCDMA2000 redirectCarrierCDMA2000_HRPD_r9;
} NhuE_CSFB_r9;

typedef struct NhuMobilityFromEUTRACmd_v960_IEsnonCriticalExtn
{
	TknPres pres;
} NhuMobilityFromEUTRACmd_v960_IEsnonCriticalExtn;

typedef struct NhuMobilityFromEUTRACmd_v960_IEs
{
	TknPres pres;
	NhuBandIndicatorGERAN bandIndicator;
	NhuMobilityFromEUTRACmd_v960_IEsnonCriticalExtn nonCriticalExtn;
} NhuMobilityFromEUTRACmd_v960_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuMobilityFromEUTRACmd_v930_IEslateNonCriticalExtn;
typedef struct NhuMobilityFromEUTRACmd_v930_IEs
{
	TknPres pres;
	NhuMobilityFromEUTRACmd_v930_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuMobilityFromEUTRACmd_v960_IEs nonCriticalExtn;
} NhuMobilityFromEUTRACmd_v930_IEs;

/* Element ----- cs-FallbackIndicator ------- */
typedef TknU8 NhuMobilityFromEUTRACmd_r9_IEscs_FallbackIndicator;

typedef struct NhuMobilityFromEUTRACmd_r9_IEspurpose
{
	TknU8 choice;
	union {
		NhuHovr handover;
		NhuCellChangeOrder cellChangeOrder;
		NhuE_CSFB_r9 e_CSFB_r9;
	} val;
} NhuMobilityFromEUTRACmd_r9_IEspurpose;

typedef struct NhuMobilityFromEUTRACmd_r9_IEs
{
	TknPres pres;
	NhuMobilityFromEUTRACmd_r9_IEscs_FallbackIndicator cs_FallbackIndicator;
	NhuMobilityFromEUTRACmd_r9_IEspurpose purpose;
	NhuMobilityFromEUTRACmd_v930_IEs nonCriticalExtn;
} NhuMobilityFromEUTRACmd_r9_IEs;

typedef struct NhuMobilityFromEUTRACmdcriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuMobilityFromEUTRACmd_r8_IEs mobilityFromEUTRACmd_r8;
		NhuMobilityFromEUTRACmd_r9_IEs mobilityFromEUTRACmd_r9;
	} val;
} NhuMobilityFromEUTRACmdcriticalExtnsc1;

typedef struct NhuMobilityFromEUTRACmdcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuMobilityFromEUTRACmdcriticalExtnscriticalExtnsFuture;

typedef struct NhuMobilityFromEUTRACmdcriticalExtns
{
	TknU8 choice;
	union {
		NhuMobilityFromEUTRACmdcriticalExtnsc1 c1;
		NhuMobilityFromEUTRACmdcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuMobilityFromEUTRACmdcriticalExtns;

typedef struct NhuMobilityFromEUTRACmd
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuMobilityFromEUTRACmdcriticalExtns criticalExtns;
} NhuMobilityFromEUTRACmd;

/* Element ----- MeasObjectId ------- */
typedef TknU32 NhuMeasObjectId;

typedef struct NhuMeasObjectToRemoveLst
{
	TknU16 noComp;
	NhuMeasObjectId *member;
}NhuMeasObjectToRemoveLst;

/* Element ----- CellIndex ------- */
typedef TknU32 NhuCellIdx;

typedef struct NhuCellIdxLst
{
	TknU16 noComp;
	NhuCellIdx *member;
}NhuCellIdxLst;

/* Element ----- cellIndex ------- */
typedef TknU32 NhuCellsToAddModcellIdx;

typedef struct NhuCellsToAddMod
{
	TknPres pres;
	NhuCellsToAddModcellIdx cellIdx;
	NhuPhysCellId physCellId;
	NhuQ_OffsetRange cellIvdualOffset;
} NhuCellsToAddMod;

typedef struct NhuCellsToAddModLst
{
	TknU16 noComp;
	NhuCellsToAddMod *member;
}NhuCellsToAddModLst;

/* Element ----- cellIndex ------- */
typedef TknU32 NhuBlackCellsToAddModcellIdx;

typedef struct NhuBlackCellsToAddMod
{
	TknPres pres;
	NhuBlackCellsToAddModcellIdx cellIdx;
	NhuPhysCellIdRange physCellIdRange;
} NhuBlackCellsToAddMod;

typedef struct NhuBlackCellsToAddModLst
{
	TknU16 noComp;
	NhuBlackCellsToAddMod *member;
}NhuBlackCellsToAddModLst;

/* Element ----- MeasCycleSCell-r10 ------- */
typedef enum enumNhuMeasCycleSCell_r10
{
	NhuMeasCycleSCell_r10sf160Enum,
	NhuMeasCycleSCell_r10sf256Enum,
	NhuMeasCycleSCell_r10sf320Enum,
	NhuMeasCycleSCell_r10sf512Enum,
	NhuMeasCycleSCell_r10sf640Enum,
	NhuMeasCycleSCell_r10sf1024Enum,
	NhuMeasCycleSCell_r10sf1280Enum,
	NhuMeasCycleSCell_r10spare1Enum
} EnumNhuMeasCycleSCell_r10;
typedef TknU32 NhuMeasCycleSCell_r10;

typedef struct NhuMeasSubfrmCellLst_r10
{
	TknU16 noComp;
	NhuPhysCellIdRange *member;
}NhuMeasSubfrmCellLst_r10;

typedef struct NhuMeasSubfrmPatternConfigNeigh_r10setup
{
	TknPres pres;
	NhuMeasSubfrmPattern_r10 measSubfrmPatternNeigh_r10;
	NhuMeasSubfrmCellLst_r10 measSubfrmCellLst_r10;
} NhuMeasSubfrmPatternConfigNeigh_r10setup;

typedef struct NhuMeasSubfrmPatternConfigNeigh_r10
{
	TknU8 choice;
	union {
		NhuMeasSubfrmPatternConfigNeigh_r10setup setup;
	} val;
} NhuMeasSubfrmPatternConfigNeigh_r10;

/* Element ----- widebandRSRQ-Meas-r11 ------- */
typedef TknU8 NhuMeasObjectEUTRAextaddgrp_2widebandRSRQ_Meas_r11;

typedef struct NhuMeasObjectEUTRAextaddgrp_1
{
	TknPres pres;
	NhuMeasCycleSCell_r10 measCycleSCell_r10;
	NhuMeasSubfrmPatternConfigNeigh_r10 measSubfrmPatternConfigNeigh_r10;
} NhuMeasObjectEUTRAextaddgrp_1;

typedef struct NhuMeasObjectEUTRAextaddgrp_2
{
	TknPres pres;
	NhuMeasObjectEUTRAextaddgrp_2widebandRSRQ_Meas_r11 widebandRSRQ_Meas_r11;
} NhuMeasObjectEUTRAextaddgrp_2;

typedef struct NhuMeasObjectEUTRA
{
	TknPres pres;
	NhuARFCN_ValueEUTRA carrierFreq;
	NhuAllowedMeasBandwidth allowedMeasBandwidth;
	NhuPresenceAntennaPort1 presenceAntennaPort1;
	NhuNeighCellConfig neighCellConfig;
	NhuQ_OffsetRange offsetFreq;	/* DEFAULT 0 */ 
	NhuCellIdxLst cellsToRemoveLst;
	NhuCellsToAddModLst cellsToAddModLst;
	NhuCellIdxLst blackCellsToRemoveLst;
	NhuBlackCellsToAddModLst blackCellsToAddModLst;
	NhuPhysCellId cellForWhichToReportCGI;
	NhuMeasObjectEUTRAextaddgrp_1 extaddgrp_1;
	NhuMeasObjectEUTRAextaddgrp_2 extaddgrp_2;
} NhuMeasObjectEUTRA;

/* Element ----- Q-OffsetRangeInterRAT ------- */
typedef TknS32 NhuQ_OffsetRangeInterRAT;

/* Element ----- PhysCellIdUTRA-FDD ------- */
typedef TknU32 NhuPhysCellIdUTRA_FDD;

/* Element ----- cellIndex ------- */
typedef TknU32 NhuCellsToAddModUTRA_FDDcellIdx;

typedef struct NhuCellsToAddModUTRA_FDD
{
	TknPres pres;
	NhuCellsToAddModUTRA_FDDcellIdx cellIdx;
	NhuPhysCellIdUTRA_FDD physCellId;
} NhuCellsToAddModUTRA_FDD;

typedef struct NhuCellsToAddModLstUTRA_FDD
{
	TknU16 noComp;
	NhuCellsToAddModUTRA_FDD *member;
}NhuCellsToAddModLstUTRA_FDD;

/* Element ----- PhysCellIdUTRA-TDD ------- */
typedef TknU32 NhuPhysCellIdUTRA_TDD;

/* Element ----- cellIndex ------- */
typedef TknU32 NhuCellsToAddModUTRA_TDDcellIdx;

typedef struct NhuCellsToAddModUTRA_TDD
{
	TknPres pres;
	NhuCellsToAddModUTRA_TDDcellIdx cellIdx;
	NhuPhysCellIdUTRA_TDD physCellId;
} NhuCellsToAddModUTRA_TDD;

typedef struct NhuCellsToAddModLstUTRA_TDD
{
	TknU16 noComp;
	NhuCellsToAddModUTRA_TDD *member;
}NhuCellsToAddModLstUTRA_TDD;

/* Element ----- range-r9 ------- */
typedef TknU32 NhuPhysCellIdRangeUTRA_FDD_r9range_r9;

typedef struct NhuPhysCellIdRangeUTRA_FDD_r9
{
	TknPres pres;
	NhuPhysCellIdUTRA_FDD start_r9;
	NhuPhysCellIdRangeUTRA_FDD_r9range_r9 range_r9;
} NhuPhysCellIdRangeUTRA_FDD_r9;

typedef struct NhuPhysCellIdRangeUTRA_FDDLst_r9
{
	TknU16 noComp;
	NhuPhysCellIdRangeUTRA_FDD_r9 *member;
}NhuPhysCellIdRangeUTRA_FDDLst_r9;

typedef struct NhuCSG_AllowedRprtngCells_r9
{
	TknPres pres;
	NhuPhysCellIdRangeUTRA_FDDLst_r9 physCellIdRangeUTRA_FDDLst_r9;
} NhuCSG_AllowedRprtngCells_r9;

typedef struct NhuMeasObjectUTRAcellsToAddModLst
{
	TknU8 choice;
	union {
		NhuCellsToAddModLstUTRA_FDD cellsToAddModLstUTRA_FDD;
		NhuCellsToAddModLstUTRA_TDD cellsToAddModLstUTRA_TDD;
	} val;
} NhuMeasObjectUTRAcellsToAddModLst;

typedef struct NhuMeasObjectUTRAcellForWhichToReportCGI
{
	TknU8 choice;
	union {
		NhuPhysCellIdUTRA_FDD utra_FDD;
		NhuPhysCellIdUTRA_TDD utra_TDD;
	} val;
} NhuMeasObjectUTRAcellForWhichToReportCGI;

typedef struct NhuMeasObjectUTRAextaddgrp_1
{
	TknPres pres;
	NhuCSG_AllowedRprtngCells_r9 csg_allowedRprtngCells_v930;
} NhuMeasObjectUTRAextaddgrp_1;

typedef struct NhuMeasObjectUTRA
{
	TknPres pres;
	NhuARFCN_ValueUTRA carrierFreq;
	NhuQ_OffsetRangeInterRAT offsetFreq;	/* DEFAULT 0 */ 
	NhuCellIdxLst cellsToRemoveLst;
	NhuMeasObjectUTRAcellsToAddModLst cellsToAddModLst;
	NhuMeasObjectUTRAcellForWhichToReportCGI cellForWhichToReportCGI;
	NhuMeasObjectUTRAextaddgrp_1 extaddgrp_1;
} NhuMeasObjectUTRA;

/* Element ---------- ncc-Permitted ----------- */
typedef TknStrBSXL NhuMeasObjectGERANncc_Permitted;
typedef struct NhuMeasObjectGERAN
{
	TknPres pres;
	NhuCarrierFreqsGERAN carrierFreqs;
	NhuQ_OffsetRangeInterRAT offsetFreq;	/* DEFAULT 0 */ 
	NhuMeasObjectGERANncc_Permitted ncc_Permitted;	/* DEFAULT 0 */ 
	NhuPhysCellIdGERAN cellForWhichToReportCGI;
} NhuMeasObjectGERAN;

/* Element ----- cellIndex ------- */
typedef TknU32 NhuCellsToAddModCDMA2000cellIdx;

typedef struct NhuCellsToAddModCDMA2000
{
	TknPres pres;
	NhuCellsToAddModCDMA2000cellIdx cellIdx;
	NhuPhysCellIdCDMA2000 physCellId;
} NhuCellsToAddModCDMA2000;

typedef struct NhuCellsToAddModLstCDMA2000
{
	TknU16 noComp;
	NhuCellsToAddModCDMA2000 *member;
}NhuCellsToAddModLstCDMA2000;

/* Element ----- searchWindowSize ------- */
typedef TknU32 NhuMeasObjectCDMA2000searchWindowSize;

typedef struct NhuMeasObjectCDMA2000
{
	TknPres pres;
	NhuCDMA2000_Typ cdma2000_Typ;
	NhuCarrierFreqCDMA2000 carrierFreq;
	NhuMeasObjectCDMA2000searchWindowSize searchWindowSize;
	NhuQ_OffsetRangeInterRAT offsetFreq;	/* DEFAULT 0 */ 
	NhuCellIdxLst cellsToRemoveLst;
	NhuCellsToAddModLstCDMA2000 cellsToAddModLst;
	NhuPhysCellIdCDMA2000 cellForWhichToReportCGI;
} NhuMeasObjectCDMA2000;

typedef struct NhuMeasObjectToAddModmeasObject
{
	TknU8 choice;
	union {
		NhuMeasObjectEUTRA measObjectEUTRA;
		NhuMeasObjectUTRA measObjectUTRA;
		NhuMeasObjectGERAN measObjectGERAN;
		NhuMeasObjectCDMA2000 measObjectCDMA2000;
	} val;
} NhuMeasObjectToAddModmeasObject;

typedef struct NhuMeasObjectToAddMod
{
	TknPres pres;
	NhuMeasObjectId measObjectId;
	NhuMeasObjectToAddModmeasObject measObject;
} NhuMeasObjectToAddMod;

typedef struct NhuMeasObjectToAddModLst
{
	TknU16 noComp;
	NhuMeasObjectToAddMod *member;
}NhuMeasObjectToAddModLst;

/* Element ----- ReportConfigId ------- */
typedef TknU32 NhuReportConfigId;

typedef struct NhuReportConfigToRemoveLst
{
	TknU16 noComp;
	NhuReportConfigId *member;
}NhuReportConfigToRemoveLst;

/* Element ----- RSRP-Range ------- */
typedef TknU32 NhuRSRP_Range;

/* Element ----- RSRQ-Range ------- */
typedef TknU32 NhuRSRQ_Range;

typedef struct NhuThresholdEUTRA
{
	TknU8 choice;
	union {
		NhuRSRP_Range threshold_RSRP;
		NhuRSRQ_Range threshold_RSRQ;
	} val;
} NhuThresholdEUTRA;

/* Element ----- Hysteresis ------- */
typedef TknU32 NhuHysteresis;

/* Element ----- TimeToTrigger ------- */
typedef enum enumNhuTimeToTrigger
{
	NhuTimeToTriggerms0Enum,
	NhuTimeToTriggerms40Enum,
	NhuTimeToTriggerms64Enum,
	NhuTimeToTriggerms80Enum,
	NhuTimeToTriggerms100Enum,
	NhuTimeToTriggerms128Enum,
	NhuTimeToTriggerms160Enum,
	NhuTimeToTriggerms256Enum,
	NhuTimeToTriggerms320Enum,
	NhuTimeToTriggerms480Enum,
	NhuTimeToTriggerms512Enum,
	NhuTimeToTriggerms640Enum,
	NhuTimeToTriggerms1024Enum,
	NhuTimeToTriggerms1280Enum,
	NhuTimeToTriggerms2560Enum,
	NhuTimeToTriggerms5120Enum
} EnumNhuTimeToTrigger;
typedef TknU32 NhuTimeToTrigger;

/* Element ----- ReportInterval ------- */
typedef enum enumNhuReportInterval
{
	NhuReportIntervalms120Enum,
	NhuReportIntervalms240Enum,
	NhuReportIntervalms480Enum,
	NhuReportIntervalms640Enum,
	NhuReportIntervalms1024Enum,
	NhuReportIntervalms2048Enum,
	NhuReportIntervalms5120Enum,
	NhuReportIntervalms10240Enum,
	NhuReportIntervalmin1Enum,
	NhuReportIntervalmin6Enum,
	NhuReportIntervalmin12Enum,
	NhuReportIntervalmin30Enum,
	NhuReportIntervalmin60Enum,
	NhuReportIntervalspare3Enum,
	NhuReportIntervalspare2Enum,
	NhuReportIntervalspare1Enum
} EnumNhuReportInterval;
typedef TknU32 NhuReportInterval;

typedef struct NhuReportConfigEUTRAtriggerTypeventeventIdeventA1
{
	TknPres pres;
	NhuThresholdEUTRA a1_Threshold;
} NhuReportConfigEUTRAtriggerTypeventeventIdeventA1;

typedef struct NhuReportConfigEUTRAtriggerTypeventeventIdeventA2
{
	TknPres pres;
	NhuThresholdEUTRA a2_Threshold;
} NhuReportConfigEUTRAtriggerTypeventeventIdeventA2;

/* Element ----- a3-Offset ------- */
typedef TknS32 NhuReportConfigEUTRAtriggerTypeventeventIdeventA3a3_Offset;

/* Element ----- reportOnLeave ------- */
typedef TknU8 NhuReportConfigEUTRAtriggerTypeventeventIdeventA3reportOnLeave;

typedef struct NhuReportConfigEUTRAtriggerTypeventeventIdeventA3
{
	TknPres pres;
	NhuReportConfigEUTRAtriggerTypeventeventIdeventA3a3_Offset a3_Offset;
	NhuReportConfigEUTRAtriggerTypeventeventIdeventA3reportOnLeave reportOnLeave;
} NhuReportConfigEUTRAtriggerTypeventeventIdeventA3;

typedef struct NhuReportConfigEUTRAtriggerTypeventeventIdeventA4
{
	TknPres pres;
	NhuThresholdEUTRA a4_Threshold;
} NhuReportConfigEUTRAtriggerTypeventeventIdeventA4;

typedef struct NhuReportConfigEUTRAtriggerTypeventeventIdeventA5
{
	TknPres pres;
	NhuThresholdEUTRA a5_Threshold1;
	NhuThresholdEUTRA a5_Threshold2;
} NhuReportConfigEUTRAtriggerTypeventeventIdeventA5;

/* Element ----- a6-Offset-r10 ------- */
typedef TknS32 NhuReportConfigEUTRAtriggerTypeventeventIdeventA6_r10a6_Offset_r10;

/* Element ----- a6-ReportOnLeave-r10 ------- */
typedef TknU8 NhuReportConfigEUTRAtriggerTypeventeventIdeventA6_r10a6_ReportOnLeave_r10;

typedef struct NhuReportConfigEUTRAtriggerTypeventeventIdeventA6_r10
{
	TknPres pres;
	NhuReportConfigEUTRAtriggerTypeventeventIdeventA6_r10a6_Offset_r10 a6_Offset_r10;
	NhuReportConfigEUTRAtriggerTypeventeventIdeventA6_r10a6_ReportOnLeave_r10 a6_ReportOnLeave_r10;
} NhuReportConfigEUTRAtriggerTypeventeventIdeventA6_r10;

typedef struct NhuReportConfigEUTRAtriggerTypeventeventId
{
	TknU8 choice;
	union {
		NhuReportConfigEUTRAtriggerTypeventeventIdeventA1 eventA1;
		NhuReportConfigEUTRAtriggerTypeventeventIdeventA2 eventA2;
		NhuReportConfigEUTRAtriggerTypeventeventIdeventA3 eventA3;
		NhuReportConfigEUTRAtriggerTypeventeventIdeventA4 eventA4;
		NhuReportConfigEUTRAtriggerTypeventeventIdeventA5 eventA5;
		NhuReportConfigEUTRAtriggerTypeventeventIdeventA6_r10 eventA6_r10;
	} val;
} NhuReportConfigEUTRAtriggerTypeventeventId;

typedef struct NhuReportConfigEUTRAtriggerTypevent
{
	TknPres pres;
	NhuReportConfigEUTRAtriggerTypeventeventId eventId;
	NhuHysteresis hysteresis;
	NhuTimeToTrigger timeToTrigger;
} NhuReportConfigEUTRAtriggerTypevent;

/* Element ----- purpose ------- */
typedef enum enumNhuReportConfigEUTRAtriggerTypperiodicalpurpose
{
	NhuReportConfigEUTRAtriggerTypperiodicalpurposereportStrongestCellsEnum,
	NhuReportConfigEUTRAtriggerTypperiodicalpurposereportCGIEnum
} EnumNhuReportConfigEUTRAtriggerTypperiodicalpurpose;
typedef TknU32 NhuReportConfigEUTRAtriggerTypperiodicalpurpose;

typedef struct NhuReportConfigEUTRAtriggerTypperiodical
{
	TknPres pres;
	NhuReportConfigEUTRAtriggerTypperiodicalpurpose purpose;
} NhuReportConfigEUTRAtriggerTypperiodical;

typedef struct NhuReportConfigEUTRAtriggerTyp
{
	TknU8 choice;
	union {
		NhuReportConfigEUTRAtriggerTypevent event;
		NhuReportConfigEUTRAtriggerTypperiodical periodical;
	} val;
} NhuReportConfigEUTRAtriggerTyp;

/* Element ----- triggerQuantity ------- */
typedef enum enumNhuReportConfigEUTRAtriggerQuantity
{
	NhuReportConfigEUTRAtriggerQuantityrsrpEnum,
	NhuReportConfigEUTRAtriggerQuantityrsrqEnum
} EnumNhuReportConfigEUTRAtriggerQuantity;
typedef TknU32 NhuReportConfigEUTRAtriggerQuantity;

/* Element ----- reportQuantity ------- */
typedef enum enumNhuReportConfigEUTRAreportQuantity
{
	NhuReportConfigEUTRAreportQuantitysameAsTriggerQuantityEnum,
	NhuReportConfigEUTRAreportQuantitybothEnum
} EnumNhuReportConfigEUTRAreportQuantity;
typedef TknU32 NhuReportConfigEUTRAreportQuantity;

/* Element ----- maxReportCells ------- */
typedef TknU32 NhuReportConfigEUTRAmaxReportCells;

/* Element ----- reportAmount ------- */
typedef enum enumNhuReportConfigEUTRAreportAmount
{
	NhuReportConfigEUTRAreportAmountr1Enum,
	NhuReportConfigEUTRAreportAmountr2Enum,
	NhuReportConfigEUTRAreportAmountr4Enum,
	NhuReportConfigEUTRAreportAmountr8Enum,
	NhuReportConfigEUTRAreportAmountr16Enum,
	NhuReportConfigEUTRAreportAmountr32Enum,
	NhuReportConfigEUTRAreportAmountr64Enum,
	NhuReportConfigEUTRAreportAmountinfinityEnum
} EnumNhuReportConfigEUTRAreportAmount;
typedef TknU32 NhuReportConfigEUTRAreportAmount;

/* Element ----- si-RequestForHO-r9 ------- */
typedef enum enumNhuReportConfigEUTRAextaddgrp_1si_RqstForHO_r9
{
	NhuReportConfigEUTRAextaddgrp_1si_RqstForHO_r9setupEnum
} EnumNhuReportConfigEUTRAextaddgrp_1si_RqstForHO_r9;
typedef TknU32 NhuReportConfigEUTRAextaddgrp_1si_RqstForHO_r9;

/* Element ----- ue-RxTxTimeDiffPeriodical-r9 ------- */
typedef enum enumNhuReportConfigEUTRAextaddgrp_1ue_RxTxTimeDiffPeriodical_r9
{
	NhuReportConfigEUTRAextaddgrp_1ue_RxTxTimeDiffPeriodical_r9setupEnum
} EnumNhuReportConfigEUTRAextaddgrp_1ue_RxTxTimeDiffPeriodical_r9;
typedef TknU32 NhuReportConfigEUTRAextaddgrp_1ue_RxTxTimeDiffPeriodical_r9;

/* Element ----- includeLocationInfo-r10 ------- */
typedef enum enumNhuReportConfigEUTRAextaddgrp_2includeLocInfo_r10
{
	NhuReportConfigEUTRAextaddgrp_2includeLocInfo_r10trueEnum
} EnumNhuReportConfigEUTRAextaddgrp_2includeLocInfo_r10;
typedef TknU32 NhuReportConfigEUTRAextaddgrp_2includeLocInfo_r10;

/* Element ----- reportAddNeighMeas-r10 ------- */
typedef enum enumNhuReportConfigEUTRAextaddgrp_2reportAddNeighMeas_r10
{
	NhuReportConfigEUTRAextaddgrp_2reportAddNeighMeas_r10setupEnum
} EnumNhuReportConfigEUTRAextaddgrp_2reportAddNeighMeas_r10;
typedef TknU32 NhuReportConfigEUTRAextaddgrp_2reportAddNeighMeas_r10;

typedef struct NhuReportConfigEUTRAextaddgrp_1
{
	TknPres pres;
	NhuReportConfigEUTRAextaddgrp_1si_RqstForHO_r9 si_RqstForHO_r9;
	NhuReportConfigEUTRAextaddgrp_1ue_RxTxTimeDiffPeriodical_r9 ue_RxTxTimeDiffPeriodical_r9;
} NhuReportConfigEUTRAextaddgrp_1;

typedef struct NhuReportConfigEUTRAextaddgrp_2
{
	TknPres pres;
	NhuReportConfigEUTRAextaddgrp_2includeLocInfo_r10 includeLocInfo_r10;
	NhuReportConfigEUTRAextaddgrp_2reportAddNeighMeas_r10 reportAddNeighMeas_r10;
} NhuReportConfigEUTRAextaddgrp_2;

typedef struct NhuReportConfigEUTRA
{
	TknPres pres;
	NhuReportConfigEUTRAtriggerTyp triggerTyp;
	NhuReportConfigEUTRAtriggerQuantity triggerQuantity;
	NhuReportConfigEUTRAreportQuantity reportQuantity;
	NhuReportConfigEUTRAmaxReportCells maxReportCells;
	NhuReportInterval reportInterval;
	NhuReportConfigEUTRAreportAmount reportAmount;
	NhuReportConfigEUTRAextaddgrp_1 extaddgrp_1;
	NhuReportConfigEUTRAextaddgrp_2 extaddgrp_2;
} NhuReportConfigEUTRA;

/* Element ----- utra-RSCP ------- */
typedef TknS32 NhuThresholdUTRAutra_RSCP;

/* Element ----- utra-EcN0 ------- */
typedef TknU32 NhuThresholdUTRAutra_EcN0;

typedef struct NhuThresholdUTRA
{
	TknU8 choice;
	union {
		NhuThresholdUTRAutra_RSCP utra_RSCP;
		NhuThresholdUTRAutra_EcN0 utra_EcN0;
	} val;
} NhuThresholdUTRA;

/* Element ----- ThresholdGERAN ------- */
typedef TknU32 NhuThresholdGERAN;

/* Element ----- ThresholdCDMA2000 ------- */
typedef TknU32 NhuThresholdCDMA2000;

typedef struct NhuReportConfigInterRATtriggerTypeventeventIdeventB1b1_Threshold
{
	TknU8 choice;
	union {
		NhuThresholdUTRA b1_ThresholdUTRA;
		NhuThresholdGERAN b1_ThresholdGERAN;
		NhuThresholdCDMA2000 b1_ThresholdCDMA2000;
	} val;
} NhuReportConfigInterRATtriggerTypeventeventIdeventB1b1_Threshold;

typedef struct NhuReportConfigInterRATtriggerTypeventeventIdeventB1
{
	TknPres pres;
	NhuReportConfigInterRATtriggerTypeventeventIdeventB1b1_Threshold b1_Threshold;
} NhuReportConfigInterRATtriggerTypeventeventIdeventB1;

typedef struct NhuReportConfigInterRATtriggerTypeventeventIdeventB2b2_Threshold2
{
	TknU8 choice;
	union {
		NhuThresholdUTRA b2_Threshold2UTRA;
		NhuThresholdGERAN b2_Threshold2GERAN;
		NhuThresholdCDMA2000 b2_Threshold2CDMA2000;
	} val;
} NhuReportConfigInterRATtriggerTypeventeventIdeventB2b2_Threshold2;

typedef struct NhuReportConfigInterRATtriggerTypeventeventIdeventB2
{
	TknPres pres;
	NhuThresholdEUTRA b2_Threshold1;
	NhuReportConfigInterRATtriggerTypeventeventIdeventB2b2_Threshold2 b2_Threshold2;
} NhuReportConfigInterRATtriggerTypeventeventIdeventB2;

typedef struct NhuReportConfigInterRATtriggerTypeventeventId
{
	TknU8 choice;
	union {
		NhuReportConfigInterRATtriggerTypeventeventIdeventB1 eventB1;
		NhuReportConfigInterRATtriggerTypeventeventIdeventB2 eventB2;
	} val;
} NhuReportConfigInterRATtriggerTypeventeventId;

typedef struct NhuReportConfigInterRATtriggerTypevent
{
	TknPres pres;
	NhuReportConfigInterRATtriggerTypeventeventId eventId;
	NhuHysteresis hysteresis;
	NhuTimeToTrigger timeToTrigger;
} NhuReportConfigInterRATtriggerTypevent;

/* Element ----- purpose ------- */
typedef enum enumNhuReportConfigInterRATtriggerTypperiodicalpurpose
{
	NhuReportConfigInterRATtriggerTypperiodicalpurposereportStrongestCellsEnum,
	NhuReportConfigInterRATtriggerTypperiodicalpurposereportStrongestCellsForSONEnum,
	NhuReportConfigInterRATtriggerTypperiodicalpurposereportCGIEnum
} EnumNhuReportConfigInterRATtriggerTypperiodicalpurpose;
typedef TknU32 NhuReportConfigInterRATtriggerTypperiodicalpurpose;

typedef struct NhuReportConfigInterRATtriggerTypperiodical
{
	TknPres pres;
	NhuReportConfigInterRATtriggerTypperiodicalpurpose purpose;
} NhuReportConfigInterRATtriggerTypperiodical;

typedef struct NhuReportConfigInterRATtriggerTyp
{
	TknU8 choice;
	union {
		NhuReportConfigInterRATtriggerTypevent event;
		NhuReportConfigInterRATtriggerTypperiodical periodical;
	} val;
} NhuReportConfigInterRATtriggerTyp;

/* Element ----- maxReportCells ------- */
typedef TknU32 NhuReportConfigInterRATmaxReportCells;

/* Element ----- reportAmount ------- */
typedef enum enumNhuReportConfigInterRATreportAmount
{
	NhuReportConfigInterRATreportAmountr1Enum,
	NhuReportConfigInterRATreportAmountr2Enum,
	NhuReportConfigInterRATreportAmountr4Enum,
	NhuReportConfigInterRATreportAmountr8Enum,
	NhuReportConfigInterRATreportAmountr16Enum,
	NhuReportConfigInterRATreportAmountr32Enum,
	NhuReportConfigInterRATreportAmountr64Enum,
	NhuReportConfigInterRATreportAmountinfinityEnum
} EnumNhuReportConfigInterRATreportAmount;
typedef TknU32 NhuReportConfigInterRATreportAmount;

/* Element ----- si-RequestForHO-r9 ------- */
typedef enum enumNhuReportConfigInterRATextaddgrp_1si_RqstForHO_r9
{
	NhuReportConfigInterRATextaddgrp_1si_RqstForHO_r9setupEnum
} EnumNhuReportConfigInterRATextaddgrp_1si_RqstForHO_r9;
typedef TknU32 NhuReportConfigInterRATextaddgrp_1si_RqstForHO_r9;

/* Element ----- reportQuantityUTRA-FDD-r10 ------- */
typedef enum enumNhuReportConfigInterRATextaddgrp_2reportQuantityUTRA_FDD_r10
{
	NhuReportConfigInterRATextaddgrp_2reportQuantityUTRA_FDD_r10bothEnum
} EnumNhuReportConfigInterRATextaddgrp_2reportQuantityUTRA_FDD_r10;
typedef TknU32 NhuReportConfigInterRATextaddgrp_2reportQuantityUTRA_FDD_r10;

/* Element ----- includeLocationInfo-r11 ------- */
typedef TknU8 NhuReportConfigInterRATextaddgrp_3includeLocInfo_r11;

typedef struct NhuReportConfigInterRATextaddgrp_1
{
	TknPres pres;
	NhuReportConfigInterRATextaddgrp_1si_RqstForHO_r9 si_RqstForHO_r9;
} NhuReportConfigInterRATextaddgrp_1;

typedef struct NhuReportConfigInterRATextaddgrp_2
{
	TknPres pres;
	NhuReportConfigInterRATextaddgrp_2reportQuantityUTRA_FDD_r10 reportQuantityUTRA_FDD_r10;
} NhuReportConfigInterRATextaddgrp_2;

typedef struct NhuReportConfigInterRATextaddgrp_3
{
	TknPres pres;
	NhuReportConfigInterRATextaddgrp_3includeLocInfo_r11 includeLocInfo_r11;
} NhuReportConfigInterRATextaddgrp_3;

typedef struct NhuReportConfigInterRAT
{
	TknPres pres;
	NhuReportConfigInterRATtriggerTyp triggerTyp;
	NhuReportConfigInterRATmaxReportCells maxReportCells;
	NhuReportInterval reportInterval;
	NhuReportConfigInterRATreportAmount reportAmount;
	NhuReportConfigInterRATextaddgrp_1 extaddgrp_1;
	NhuReportConfigInterRATextaddgrp_2 extaddgrp_2;
	NhuReportConfigInterRATextaddgrp_3 extaddgrp_3;
} NhuReportConfigInterRAT;

typedef struct NhuReportConfigToAddModreportConfig
{
	TknU8 choice;
	union {
		NhuReportConfigEUTRA reportConfigEUTRA;
		NhuReportConfigInterRAT reportConfigInterRAT;
	} val;
} NhuReportConfigToAddModreportConfig;

typedef struct NhuReportConfigToAddMod
{
	TknPres pres;
	NhuReportConfigId reportConfigId;
	NhuReportConfigToAddModreportConfig reportConfig;
} NhuReportConfigToAddMod;

typedef struct NhuReportConfigToAddModLst
{
	TknU16 noComp;
	NhuReportConfigToAddMod *member;
}NhuReportConfigToAddModLst;

/* Element ----- MeasId ------- */
typedef TknU32 NhuMeasId;

typedef struct NhuMeasIdToRemoveLst
{
	TknU16 noComp;
	NhuMeasId *member;
}NhuMeasIdToRemoveLst;

typedef struct NhuMeasIdToAddMod
{
	TknPres pres;
	NhuMeasId measId;
	NhuMeasObjectId measObjectId;
	NhuReportConfigId reportConfigId;
} NhuMeasIdToAddMod;

typedef struct NhuMeasIdToAddModLst
{
	TknU16 noComp;
	NhuMeasIdToAddMod *member;
}NhuMeasIdToAddModLst;

typedef struct NhuQuantityConfigEUTRA
{
	TknPres pres;
	NhuFilterCoefficient filterCoefficientRSRP;	/* DEFAULT 0 */ 
	NhuFilterCoefficient filterCoefficientRSRQ;	/* DEFAULT 0 */ 
} NhuQuantityConfigEUTRA;

/* Element ----- measQuantityUTRA-FDD ------- */
typedef enum enumNhuQuantityConfigUTRAmeasQuantityUTRA_FDD
{
	NhuQuantityConfigUTRAmeasQuantityUTRA_FDDcpich_RSCPEnum,
	NhuQuantityConfigUTRAmeasQuantityUTRA_FDDcpich_EcN0Enum
} EnumNhuQuantityConfigUTRAmeasQuantityUTRA_FDD;
typedef TknU32 NhuQuantityConfigUTRAmeasQuantityUTRA_FDD;

/* Element ----- measQuantityUTRA-TDD ------- */
typedef enum enumNhuQuantityConfigUTRAmeasQuantityUTRA_TDD
{
	NhuQuantityConfigUTRAmeasQuantityUTRA_TDDpccpch_RSCPEnum
} EnumNhuQuantityConfigUTRAmeasQuantityUTRA_TDD;
typedef TknU32 NhuQuantityConfigUTRAmeasQuantityUTRA_TDD;

typedef struct NhuQuantityConfigUTRA
{
	TknPres pres;
	NhuQuantityConfigUTRAmeasQuantityUTRA_FDD measQuantityUTRA_FDD;
	NhuQuantityConfigUTRAmeasQuantityUTRA_TDD measQuantityUTRA_TDD;
	NhuFilterCoefficient filterCoefficient;	/* DEFAULT 0 */ 
} NhuQuantityConfigUTRA;

/* Element ----- measQuantityGERAN ------- */
typedef enum enumNhuQuantityConfigGERANmeasQuantityGERAN
{
	NhuQuantityConfigGERANmeasQuantityGERANrssiEnum
} EnumNhuQuantityConfigGERANmeasQuantityGERAN;
typedef TknU32 NhuQuantityConfigGERANmeasQuantityGERAN;

typedef struct NhuQuantityConfigGERAN
{
	TknPres pres;
	NhuQuantityConfigGERANmeasQuantityGERAN measQuantityGERAN;
	NhuFilterCoefficient filterCoefficient;	/* DEFAULT 0 */ 
} NhuQuantityConfigGERAN;

/* Element ----- measQuantityCDMA2000 ------- */
typedef enum enumNhuQuantityConfigCDMA2000measQuantityCDMA2000
{
	NhuQuantityConfigCDMA2000measQuantityCDMA2000pilotStrengthEnum,
	NhuQuantityConfigCDMA2000measQuantityCDMA2000pilotPnPhaseAndPilotStrengthEnum
} EnumNhuQuantityConfigCDMA2000measQuantityCDMA2000;
typedef TknU32 NhuQuantityConfigCDMA2000measQuantityCDMA2000;

typedef struct NhuQuantityConfigCDMA2000
{
	TknPres pres;
	NhuQuantityConfigCDMA2000measQuantityCDMA2000 measQuantityCDMA2000;
} NhuQuantityConfigCDMA2000;

typedef struct NhuQuantityConfigUTRA_v1020
{
	TknPres pres;
	NhuFilterCoefficient filterCoefficient2_FDD_r10;	/* DEFAULT 0 */ 
} NhuQuantityConfigUTRA_v1020;

typedef struct NhuQuantityConfigextaddgrp_1
{
	TknPres pres;
	NhuQuantityConfigUTRA_v1020 quantityConfigUTRA_v1020;
} NhuQuantityConfigextaddgrp_1;

typedef struct NhuQuantityConfig
{
	TknPres pres;
	NhuQuantityConfigEUTRA quantityConfigEUTRA;
	NhuQuantityConfigUTRA quantityConfigUTRA;
	NhuQuantityConfigGERAN quantityConfigGERAN;
	NhuQuantityConfigCDMA2000 quantityConfigCDMA2000;
	NhuQuantityConfigextaddgrp_1 extaddgrp_1;
} NhuQuantityConfig;

/* Element ----- gp0 ------- */
typedef TknU32 NhuMeasGapConfigsetupgapOffsetgp0;

/* Element ----- gp1 ------- */
typedef TknU32 NhuMeasGapConfigsetupgapOffsetgp1;

typedef struct NhuMeasGapConfigsetupgapOffset
{
	TknU8 choice;
	union {
		NhuMeasGapConfigsetupgapOffsetgp0 gp0;
		NhuMeasGapConfigsetupgapOffsetgp1 gp1;
	} val;
} NhuMeasGapConfigsetupgapOffset;

typedef struct NhuMeasGapConfigsetup
{
	TknPres pres;
	NhuMeasGapConfigsetupgapOffset gapOffset;
} NhuMeasGapConfigsetup;

typedef struct NhuMeasGapConfig
{
	TknU8 choice;
	union {
		NhuMeasGapConfigsetup setup;
	} val;
} NhuMeasGapConfig;

/* Element ----- ARFCN-ValueEUTRA-v9e0 ------- */
typedef TknU32 NhuARFCN_ValueEUTRA_v9e0;

typedef struct NhuMeasObjectEUTRA_v9e0
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_v9e0 carrierFreq_v9e0;
} NhuMeasObjectEUTRA_v9e0;

typedef struct NhuMeasObjectToAddMod_v9e0
{
	TknPres pres;
	NhuMeasObjectEUTRA_v9e0 measObjectEUTRA_v9e0;
} NhuMeasObjectToAddMod_v9e0;

typedef struct NhuMeasObjectToAddModLst_v9e0
{
	TknU16 noComp;
	NhuMeasObjectToAddMod_v9e0 *member;
}NhuMeasObjectToAddModLst_v9e0;

typedef struct NhuMeasConfigspeedStateParssetup
{
	TknPres pres;
	NhuMobilityStateParams mobilityStateParams;
	NhuSpeedStateScaleFactors timeToTrigger_SF;
} NhuMeasConfigspeedStateParssetup;

typedef struct NhuMeasConfigspeedStatePars
{
	TknU8 choice;
	union {
		NhuMeasConfigspeedStateParssetup setup;
	} val;
} NhuMeasConfigspeedStatePars;

/* Element ----- allowInterruptions-r11 ------- */
typedef TknU8 NhuMeasConfigextaddgrp_2allowInterruptions_r11;

typedef struct NhuMeasConfigextaddgrp_1
{
	TknPres pres;
	NhuMeasObjectToAddModLst_v9e0 measObjectToAddModLst_v9e0;
} NhuMeasConfigextaddgrp_1;

typedef struct NhuMeasConfigextaddgrp_2
{
	TknPres pres;
	NhuMeasConfigextaddgrp_2allowInterruptions_r11 allowInterruptions_r11;
} NhuMeasConfigextaddgrp_2;

typedef struct NhuMeasConfig
{
	TknPres pres;
	NhuMeasObjectToRemoveLst measObjectToRemoveLst;
	NhuMeasObjectToAddModLst measObjectToAddModLst;
	NhuReportConfigToRemoveLst reportConfigToRemoveLst;
	NhuReportConfigToAddModLst reportConfigToAddModLst;
	NhuMeasIdToRemoveLst measIdToRemoveLst;
	NhuMeasIdToAddModLst measIdToAddModLst;
	NhuQuantityConfig quantityConfig;
	NhuMeasGapConfig measGapConfig;
	NhuRSRP_Range s_Measure;
	NhuPreRegistrationInfoHRPD preRegistrationInfoHRPD;
	NhuMeasConfigspeedStatePars speedStatePars;
	NhuMeasConfigextaddgrp_1 extaddgrp_1;
	NhuMeasConfigextaddgrp_2 extaddgrp_2;
} NhuMeasConfig;

typedef struct NhuCarrierFreqEUTRA
{
	TknPres pres;
	NhuARFCN_ValueEUTRA dl_CarrierFreq;
	NhuARFCN_ValueEUTRA ul_CarrierFreq;
} NhuCarrierFreqEUTRA;

/* Element ----- dl-Bandwidth ------- */
typedef enum enumNhuCarrierBandwidthEUTRAdl_Bandwidth
{
	NhuCarrierBandwidthEUTRAdl_Bandwidthn6Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthn15Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthn25Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthn50Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthn75Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthn100Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthspare10Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthspare9Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthspare8Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthspare7Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthspare6Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthspare5Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthspare4Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthspare3Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthspare2Enum,
	NhuCarrierBandwidthEUTRAdl_Bandwidthspare1Enum
} EnumNhuCarrierBandwidthEUTRAdl_Bandwidth;
typedef TknU32 NhuCarrierBandwidthEUTRAdl_Bandwidth;

/* Element ----- ul-Bandwidth ------- */
typedef enum enumNhuCarrierBandwidthEUTRAul_Bandwidth
{
	NhuCarrierBandwidthEUTRAul_Bandwidthn6Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthn15Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthn25Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthn50Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthn75Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthn100Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthspare10Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthspare9Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthspare8Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthspare7Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthspare6Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthspare5Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthspare4Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthspare3Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthspare2Enum,
	NhuCarrierBandwidthEUTRAul_Bandwidthspare1Enum
} EnumNhuCarrierBandwidthEUTRAul_Bandwidth;
typedef TknU32 NhuCarrierBandwidthEUTRAul_Bandwidth;

typedef struct NhuCarrierBandwidthEUTRA
{
	TknPres pres;
	NhuCarrierBandwidthEUTRAdl_Bandwidth dl_Bandwidth;
	NhuCarrierBandwidthEUTRAul_Bandwidth ul_Bandwidth;
} NhuCarrierBandwidthEUTRA;

/* Element ----- rootSequenceIndex ------- */
typedef TknU32 NhuPRACH_ConfigrootSequenceIdx;

typedef struct NhuPRACH_Config
{
	TknPres pres;
	NhuPRACH_ConfigrootSequenceIdx rootSequenceIdx;
	NhuPRACH_ConfigInfo prach_ConfigInfo;
} NhuPRACH_Config;

/* Element ----- antennaPortsCount ------- */
typedef enum enumNhuAntennaInfoCmnantennaPortsCount
{
	NhuAntennaInfoCmnantennaPortsCountan1Enum,
	NhuAntennaInfoCmnantennaPortsCountan2Enum,
	NhuAntennaInfoCmnantennaPortsCountan4Enum,
	NhuAntennaInfoCmnantennaPortsCountspare1Enum
} EnumNhuAntennaInfoCmnantennaPortsCount;
typedef TknU32 NhuAntennaInfoCmnantennaPortsCount;

typedef struct NhuAntennaInfoCmn
{
	TknPres pres;
	NhuAntennaInfoCmnantennaPortsCount antennaPortsCount;
} NhuAntennaInfoCmn;

typedef struct NhuRadioResourceConfigCmnextaddgrp_1
{
	TknPres pres;
	NhuUlnkPowerCntrlCmn_v1020 uplinkPowerCntrlCmn_v1020;
} NhuRadioResourceConfigCmnextaddgrp_1;

typedef struct NhuRadioResourceConfigCmnextaddgrp_2
{
	TknPres pres;
	NhuTDD_Config_v1130 tdd_Config_v1130;
} NhuRadioResourceConfigCmnextaddgrp_2;

typedef struct NhuRadioResourceConfigCmn
{
	TknPres pres;
	NhuRACH_ConfigCmn rach_ConfigCmn;
	NhuPRACH_Config prach_Config;
	NhuPDSCH_ConfigCmn pdsch_ConfigCmn;
	NhuPUSCH_ConfigCmn pusch_ConfigCmn;
	NhuPHICH_Config phich_Config;
	NhuPUCCH_ConfigCmn pucch_ConfigCmn;
	NhuSoundingRS_UL_ConfigCmn soundingRS_UL_ConfigCmn;
	NhuUlnkPowerCntrlCmn uplinkPowerCntrlCmn;
	NhuAntennaInfoCmn antennaInfoCmn;
	NhuP_Max p_Max;
	NhuTDD_Config tdd_Config;
	NhuUL_CyclicPrefixLength ul_CyclicPrefixLength;
	NhuRadioResourceConfigCmnextaddgrp_1 extaddgrp_1;
	NhuRadioResourceConfigCmnextaddgrp_2 extaddgrp_2;
} NhuRadioResourceConfigCmn;

/* Element ----- ra-PreambleIndex ------- */
typedef TknU32 NhuRACH_ConfigDedicatedra_PreambleIdx;

/* Element ----- ra-PRACH-MaskIndex ------- */
typedef TknU32 NhuRACH_ConfigDedicatedra_PRACH_MaskIdx;

typedef struct NhuRACH_ConfigDedicated
{
	TknPres pres;
	NhuRACH_ConfigDedicatedra_PreambleIdx ra_PreambleIdx;
	NhuRACH_ConfigDedicatedra_PRACH_MaskIdx ra_PRACH_MaskIdx;
} NhuRACH_ConfigDedicated;

typedef struct NhuCarrierFreqEUTRA_v9e0
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_r9 dl_CarrierFreq_v9e0;
	NhuARFCN_ValueEUTRA_r9 ul_CarrierFreq_v9e0;
} NhuCarrierFreqEUTRA_v9e0;

/* Element ----- t304 ------- */
typedef enum enumNhuMobilityCntrlInfot304
{
	NhuMobilityCntrlInfot304ms50Enum,
	NhuMobilityCntrlInfot304ms100Enum,
	NhuMobilityCntrlInfot304ms150Enum,
	NhuMobilityCntrlInfot304ms200Enum,
	NhuMobilityCntrlInfot304ms500Enum,
	NhuMobilityCntrlInfot304ms1000Enum,
	NhuMobilityCntrlInfot304ms2000Enum,
	NhuMobilityCntrlInfot304spare1Enum
} EnumNhuMobilityCntrlInfot304;
typedef TknU32 NhuMobilityCntrlInfot304;

/* Element ----- drb-ContinueROHC-r11 ------- */
typedef enum enumNhuMobilityCntrlInfoextaddgrp_2drb_ContinueROHC_r11
{
	NhuMobilityCntrlInfoextaddgrp_2drb_ContinueROHC_r11trueEnum
} EnumNhuMobilityCntrlInfoextaddgrp_2drb_ContinueROHC_r11;
typedef TknU32 NhuMobilityCntrlInfoextaddgrp_2drb_ContinueROHC_r11;

typedef struct NhuMobilityCntrlInfoextaddgrp_1
{
	TknPres pres;
	NhuCarrierFreqEUTRA_v9e0 carrierFreq_v9e0;
} NhuMobilityCntrlInfoextaddgrp_1;

typedef struct NhuMobilityCntrlInfoextaddgrp_2
{
	TknPres pres;
	NhuMobilityCntrlInfoextaddgrp_2drb_ContinueROHC_r11 drb_ContinueROHC_r11;
} NhuMobilityCntrlInfoextaddgrp_2;

typedef struct NhuMobilityCntrlInfo
{
	TknPres pres;
	NhuPhysCellId targetPhysCellId;
	NhuCarrierFreqEUTRA carrierFreq;
	NhuCarrierBandwidthEUTRA carrierBandwidth;
	NhuAdditionalSpectrumEmission additionalSpectrumEmission;
	NhuMobilityCntrlInfot304 t304;
	NhuC_RNTI newUE_Identity;
	NhuRadioResourceConfigCmn radioResourceConfigCmn;
	NhuRACH_ConfigDedicated rach_ConfigDedicated;
	NhuMobilityCntrlInfoextaddgrp_1 extaddgrp_1;
	NhuMobilityCntrlInfoextaddgrp_2 extaddgrp_2;
} NhuMobilityCntrlInfo;

/* Element ----- cipheringAlgorithm ------- */
typedef enum enumNhuSecAlgorithmConfigcipheringAlgorithm
{
	NhuSecAlgorithmConfigcipheringAlgorithmeea0Enum,
	NhuSecAlgorithmConfigcipheringAlgorithmeea1Enum,
	NhuSecAlgorithmConfigcipheringAlgorithmeea2Enum,
	NhuSecAlgorithmConfigcipheringAlgorithmeea3_v1130Enum,
	NhuSecAlgorithmConfigcipheringAlgorithmspare4Enum,
	NhuSecAlgorithmConfigcipheringAlgorithmspare3Enum,
	NhuSecAlgorithmConfigcipheringAlgorithmspare2Enum,
	NhuSecAlgorithmConfigcipheringAlgorithmspare1Enum
} EnumNhuSecAlgorithmConfigcipheringAlgorithm;
typedef TknU32 NhuSecAlgorithmConfigcipheringAlgorithm;

/* Element ----- integrityProtAlgorithm ------- */
typedef enum enumNhuSecAlgorithmConfigintegrityProtAlgorithm
{
	NhuSecAlgorithmConfigintegrityProtAlgorithmeia0_v920Enum,
	NhuSecAlgorithmConfigintegrityProtAlgorithmeia1Enum,
	NhuSecAlgorithmConfigintegrityProtAlgorithmeia2Enum,
	NhuSecAlgorithmConfigintegrityProtAlgorithmeia3_v1130Enum,
	NhuSecAlgorithmConfigintegrityProtAlgorithmspare4Enum,
	NhuSecAlgorithmConfigintegrityProtAlgorithmspare3Enum,
	NhuSecAlgorithmConfigintegrityProtAlgorithmspare2Enum,
	NhuSecAlgorithmConfigintegrityProtAlgorithmspare1Enum
} EnumNhuSecAlgorithmConfigintegrityProtAlgorithm;
typedef TknU32 NhuSecAlgorithmConfigintegrityProtAlgorithm;

typedef struct NhuSecAlgorithmConfig
{
	TknPres pres;
	NhuSecAlgorithmConfigcipheringAlgorithm cipheringAlgorithm;
	NhuSecAlgorithmConfigintegrityProtAlgorithm integrityProtAlgorithm;
} NhuSecAlgorithmConfig;

/* Element ----- keyChangeIndicator ------- */
typedef TknU8 NhuSecConfigHOhandoverTypintraLTEkeyChangeIndicator;

typedef struct NhuSecConfigHOhandoverTypintraLTE
{
	TknPres pres;
	NhuSecAlgorithmConfig securityAlgorithmConfig;
	NhuSecConfigHOhandoverTypintraLTEkeyChangeIndicator keyChangeIndicator;
	NhuNextHopChainingCount nextHopChainingCount;
} NhuSecConfigHOhandoverTypintraLTE;

/* Element ---------- nas-SecurityParamToEUTRA ----------- */
typedef TknStrOSXL NhuSecConfigHOhandoverTypinterRATnas_SecParamToEUTRA;
typedef struct NhuSecConfigHOhandoverTypinterRAT
{
	TknPres pres;
	NhuSecAlgorithmConfig securityAlgorithmConfig;
	NhuSecConfigHOhandoverTypinterRATnas_SecParamToEUTRA nas_SecParamToEUTRA;
} NhuSecConfigHOhandoverTypinterRAT;

typedef struct NhuSecConfigHOhandoverTyp
{
	TknU8 choice;
	union {
		NhuSecConfigHOhandoverTypintraLTE intraLTE;
		NhuSecConfigHOhandoverTypinterRAT interRAT;
	} val;
} NhuSecConfigHOhandoverTyp;

typedef struct NhuSecConfigHO
{
	TknPres pres;
	NhuSecConfigHOhandoverTyp handoverTyp;
} NhuSecConfigHO;

/* Element ----- proximityIndicationEUTRA-r9 ------- */
typedef enum enumNhuReportProximityConfig_r9proximityIndEUTRA_r9
{
	NhuReportProximityConfig_r9proximityIndEUTRA_r9enabledEnum
} EnumNhuReportProximityConfig_r9proximityIndEUTRA_r9;
typedef TknU32 NhuReportProximityConfig_r9proximityIndEUTRA_r9;

/* Element ----- proximityIndicationUTRA-r9 ------- */
typedef enum enumNhuReportProximityConfig_r9proximityIndUTRA_r9
{
	NhuReportProximityConfig_r9proximityIndUTRA_r9enabledEnum
} EnumNhuReportProximityConfig_r9proximityIndUTRA_r9;
typedef TknU32 NhuReportProximityConfig_r9proximityIndUTRA_r9;

typedef struct NhuReportProximityConfig_r9
{
	TknPres pres;
	NhuReportProximityConfig_r9proximityIndEUTRA_r9 proximityIndEUTRA_r9;
	NhuReportProximityConfig_r9proximityIndUTRA_r9 proximityIndUTRA_r9;
} NhuReportProximityConfig_r9;

/* Element ----- idc-Indication-r11 ------- */
typedef enum enumNhuIDC_Config_r11idc_Ind_r11
{
	NhuIDC_Config_r11idc_Ind_r11setupEnum
} EnumNhuIDC_Config_r11idc_Ind_r11;
typedef TknU32 NhuIDC_Config_r11idc_Ind_r11;

/* Element ----- autonomousDenialSubframes-r11 ------- */
typedef enum enumNhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialSubfrms_r11
{
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialSubfrms_r11n2Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialSubfrms_r11n5Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialSubfrms_r11n10Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialSubfrms_r11n15Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialSubfrms_r11n20Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialSubfrms_r11n30Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialSubfrms_r11spare2Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialSubfrms_r11spare1Enum
} EnumNhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialSubfrms_r11;
typedef TknU32 NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialSubfrms_r11;

/* Element ----- autonomousDenialValidity-r11 ------- */
typedef enum enumNhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialValidity_r11
{
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialValidity_r11sf200Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialValidity_r11sf500Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialValidity_r11sf1000Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialValidity_r11sf2000Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialValidity_r11spare4Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialValidity_r11spare3Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialValidity_r11spare2Enum,
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialValidity_r11spare1Enum
} EnumNhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialValidity_r11;
typedef TknU32 NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialValidity_r11;

typedef struct NhuIDC_Config_r11autonomousDenialParams_r11
{
	TknPres pres;
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialSubfrms_r11 autonomousDenialSubfrms_r11;
	NhuIDC_Config_r11autonomousDenialParams_r11autonomousDenialValidity_r11 autonomousDenialValidity_r11;
} NhuIDC_Config_r11autonomousDenialParams_r11;

typedef struct NhuIDC_Config_r11
{
	TknPres pres;
	NhuIDC_Config_r11idc_Ind_r11 idc_Ind_r11;
	NhuIDC_Config_r11autonomousDenialParams_r11 autonomousDenialParams_r11;
} NhuIDC_Config_r11;

/* Element ----- powerPrefIndicationTimer-r11 ------- */
typedef enum enumNhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11
{
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11s0Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11s0dot5Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11s1Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11s2Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11s5Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11s10Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11s20Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11s30Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11s60Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11s90Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11s120Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11s300Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11s600Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11spare3Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11spare2Enum,
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11spare1Enum
} EnumNhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11;
typedef TknU32 NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11;

typedef struct NhuPowerPrefIndConfig_r11setup
{
	TknPres pres;
	NhuPowerPrefIndConfig_r11setuppowerPrefIndTimer_r11 powerPrefIndTimer_r11;
} NhuPowerPrefIndConfig_r11setup;

typedef struct NhuPowerPrefIndConfig_r11
{
	TknU8 choice;
	union {
		NhuPowerPrefIndConfig_r11setup setup;
	} val;
} NhuPowerPrefIndConfig_r11;

/* Element ----- obtainLocation-r11 ------- */
typedef enum enumNhuObtainLocConfig_r11obtainLoc_r11
{
	NhuObtainLocConfig_r11obtainLoc_r11setupEnum
} EnumNhuObtainLocConfig_r11obtainLoc_r11;
typedef TknU32 NhuObtainLocConfig_r11obtainLoc_r11;

typedef struct NhuObtainLocConfig_r11
{
	TknPres pres;
	NhuObtainLocConfig_r11obtainLoc_r11 obtainLoc_r11;
} NhuObtainLocConfig_r11;

typedef struct NhuOtherConfig_r9extaddgrp_1
{
	TknPres pres;
	NhuIDC_Config_r11 idc_Config_r11;
	NhuPowerPrefIndConfig_r11 powerPrefIndConfig_r11;
	NhuObtainLocConfig_r11 obtainLocConfig_r11;
} NhuOtherConfig_r9extaddgrp_1;

typedef struct NhuOtherConfig_r9
{
	TknPres pres;
	NhuReportProximityConfig_r9 reportProximityConfig_r9;
	NhuOtherConfig_r9extaddgrp_1 extaddgrp_1;
} NhuOtherConfig_r9;

/* Element ----- SCellIndex-r10 ------- */
typedef TknU32 NhuSCellIdx_r10;

typedef struct NhuSCellToRlsLst_r10
{
	TknU16 noComp;
	NhuSCellIdx_r10 *member;
}NhuSCellToRlsLst_r10;

/* Element ----- p0-NominalPUSCH-r10 ------- */
typedef TknS32 NhuUlnkPowerCntrlCmnSCell_r10p0_NominalPUSCH_r10;

/* Element ----- alpha-r10 ------- */
typedef enum enumNhuUlnkPowerCntrlCmnSCell_r10alpha_r10
{
	NhuUlnkPowerCntrlCmnSCell_r10alpha_r10al0Enum,
	NhuUlnkPowerCntrlCmnSCell_r10alpha_r10al04Enum,
	NhuUlnkPowerCntrlCmnSCell_r10alpha_r10al05Enum,
	NhuUlnkPowerCntrlCmnSCell_r10alpha_r10al06Enum,
	NhuUlnkPowerCntrlCmnSCell_r10alpha_r10al07Enum,
	NhuUlnkPowerCntrlCmnSCell_r10alpha_r10al08Enum,
	NhuUlnkPowerCntrlCmnSCell_r10alpha_r10al09Enum,
	NhuUlnkPowerCntrlCmnSCell_r10alpha_r10al1Enum
} EnumNhuUlnkPowerCntrlCmnSCell_r10alpha_r10;
typedef TknU32 NhuUlnkPowerCntrlCmnSCell_r10alpha_r10;

typedef struct NhuUlnkPowerCntrlCmnSCell_r10
{
	TknPres pres;
	NhuUlnkPowerCntrlCmnSCell_r10p0_NominalPUSCH_r10 p0_NominalPUSCH_r10;
	NhuUlnkPowerCntrlCmnSCell_r10alpha_r10 alpha_r10;
} NhuUlnkPowerCntrlCmnSCell_r10;

/* Element ----- prach-ConfigIndex-r10 ------- */
typedef TknU32 NhuPRACH_ConfigSCell_r10prach_ConfigIdx_r10;

typedef struct NhuPRACH_ConfigSCell_r10
{
	TknPres pres;
	NhuPRACH_ConfigSCell_r10prach_ConfigIdx_r10 prach_ConfigIdx_r10;
} NhuPRACH_ConfigSCell_r10;

typedef struct NhuRACH_ConfigCmnSCell_r11ra_SupervisionInfo_r11
{
	TknPres pres;
	NhuPreambleTransMax preambleTransMax_r11;
} NhuRACH_ConfigCmnSCell_r11ra_SupervisionInfo_r11;

typedef struct NhuRACH_ConfigCmnSCell_r11
{
	TknPres pres;
	NhuPowerRampingParams powerRampingParams_r11;
	NhuRACH_ConfigCmnSCell_r11ra_SupervisionInfo_r11 ra_SupervisionInfo_r11;
} NhuRACH_ConfigCmnSCell_r11;

/* Element ----- deltaPreambleMsg3-r11 ------- */
typedef TknS32 NhuUlnkPowerCntrlCmnSCell_v1130deltaPreambleMsg3_r11;

typedef struct NhuUlnkPowerCntrlCmnSCell_v1130
{
	TknPres pres;
	NhuUlnkPowerCntrlCmnSCell_v1130deltaPreambleMsg3_r11 deltaPreambleMsg3_r11;
} NhuUlnkPowerCntrlCmnSCell_v1130;

/* Element ----- dl-Bandwidth-r10 ------- */
typedef enum enumNhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10dl_Bandwidth_r10
{
	NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10dl_Bandwidth_r10n6Enum,
	NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10dl_Bandwidth_r10n15Enum,
	NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10dl_Bandwidth_r10n25Enum,
	NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10dl_Bandwidth_r10n50Enum,
	NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10dl_Bandwidth_r10n75Enum,
	NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10dl_Bandwidth_r10n100Enum
} EnumNhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10dl_Bandwidth_r10;
typedef TknU32 NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10dl_Bandwidth_r10;

typedef struct NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10
{
	TknPres pres;
	NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10dl_Bandwidth_r10 dl_Bandwidth_r10;
	NhuAntennaInfoCmn antennaInfoCmn_r10;
	NhuMBSFN_SubfrmConfigLst mbsfn_SubfrmConfigLst_r10;
	NhuPHICH_Config phich_Config_r10;
	NhuPDSCH_ConfigCmn pdsch_ConfigCmn_r10;
	NhuTDD_Config tdd_Config_r10;
} NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10;

/* Element ----- ul-Bandwidth-r10 ------- */
typedef enum enumNhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10ul_Bandwidth_r10
{
	NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10ul_Bandwidth_r10n6Enum,
	NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10ul_Bandwidth_r10n15Enum,
	NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10ul_Bandwidth_r10n25Enum,
	NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10ul_Bandwidth_r10n50Enum,
	NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10ul_Bandwidth_r10n75Enum,
	NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10ul_Bandwidth_r10n100Enum
} EnumNhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10ul_Bandwidth_r10;
typedef TknU32 NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10ul_Bandwidth_r10;

typedef struct NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10
{
	TknPres pres;
	NhuARFCN_ValueEUTRA ul_CarrierFreq_r10;
	NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10ul_Bandwidth_r10 ul_Bandwidth_r10;
	NhuAdditionalSpectrumEmission additionalSpectrumEmissionSCell_r10;
} NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10;

typedef struct NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10
{
	TknPres pres;
	NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10 ul_FreqInfo_r10;
	NhuP_Max p_Max_r10;
	NhuUlnkPowerCntrlCmnSCell_r10 uplinkPowerCntrlCmnSCell_r10;
	NhuSoundingRS_UL_ConfigCmn soundingRS_UL_ConfigCmn_r10;
	NhuUL_CyclicPrefixLength ul_CyclicPrefixLength_r10;
	NhuPRACH_ConfigSCell_r10 prach_ConfigSCell_r10;
	NhuPUSCH_ConfigCmn pusch_ConfigCmn_r10;
} NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10;

typedef struct NhuRadioResourceConfigCmnSCell_r10extaddgrp_1
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_v9e0 ul_CarrierFreq_v1090;
} NhuRadioResourceConfigCmnSCell_r10extaddgrp_1;

typedef struct NhuRadioResourceConfigCmnSCell_r10extaddgrp_2
{
	TknPres pres;
	NhuRACH_ConfigCmnSCell_r11 rach_ConfigCmnSCell_r11;
	NhuPRACH_Config prach_ConfigSCell_r11;
	NhuTDD_Config_v1130 tdd_Config_v1130;
	NhuUlnkPowerCntrlCmnSCell_v1130 uplinkPowerCntrlCmnSCell_v1130;
} NhuRadioResourceConfigCmnSCell_r10extaddgrp_2;

typedef struct NhuRadioResourceConfigCmnSCell_r10
{
	TknPres pres;
	NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10 nonUL_Cfg_r10;
	NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10 ul_Cfg_r10;
	NhuRadioResourceConfigCmnSCell_r10extaddgrp_1 extaddgrp_1;
	NhuRadioResourceConfigCmnSCell_r10extaddgrp_2 extaddgrp_2;
} NhuRadioResourceConfigCmnSCell_r10;

/* Element ----- ServCellIndex-r10 ------- */
typedef TknU32 NhuServCellIdx_r10;

/* Element ----- cif-Presence-r10 ------- */
typedef TknU8 NhuCrossCarrierSchedulingConfig_r10schedulingCellInfo_r10own_r10cif_Presence_r10;

typedef struct NhuCrossCarrierSchedulingConfig_r10schedulingCellInfo_r10own_r10
{
	TknPres pres;
	NhuCrossCarrierSchedulingConfig_r10schedulingCellInfo_r10own_r10cif_Presence_r10 cif_Presence_r10;
} NhuCrossCarrierSchedulingConfig_r10schedulingCellInfo_r10own_r10;

/* Element ----- pdsch-Start-r10 ------- */
typedef TknU32 NhuCrossCarrierSchedulingConfig_r10schedulingCellInfo_r10other_r10pdsch_Start_r10;

typedef struct NhuCrossCarrierSchedulingConfig_r10schedulingCellInfo_r10other_r10
{
	TknPres pres;
	NhuServCellIdx_r10 schedulingCellId_r10;
	NhuCrossCarrierSchedulingConfig_r10schedulingCellInfo_r10other_r10pdsch_Start_r10 pdsch_Start_r10;
} NhuCrossCarrierSchedulingConfig_r10schedulingCellInfo_r10other_r10;

typedef struct NhuCrossCarrierSchedulingConfig_r10schedulingCellInfo_r10
{
	TknU8 choice;
	union {
		NhuCrossCarrierSchedulingConfig_r10schedulingCellInfo_r10own_r10 own_r10;
		NhuCrossCarrierSchedulingConfig_r10schedulingCellInfo_r10other_r10 other_r10;
	} val;
} NhuCrossCarrierSchedulingConfig_r10schedulingCellInfo_r10;

typedef struct NhuCrossCarrierSchedulingConfig_r10
{
	TknPres pres;
	NhuCrossCarrierSchedulingConfig_r10schedulingCellInfo_r10 schedulingCellInfo_r10;
} NhuCrossCarrierSchedulingConfig_r10;

/* Element ----- groupHoppingDisabled-r10 ------- */
typedef enum enumNhuPUSCH_ConfigDedicatedSCell_r10groupHoppingDisabled_r10
{
	NhuPUSCH_ConfigDedicatedSCell_r10groupHoppingDisabled_r10trueEnum
} EnumNhuPUSCH_ConfigDedicatedSCell_r10groupHoppingDisabled_r10;
typedef TknU32 NhuPUSCH_ConfigDedicatedSCell_r10groupHoppingDisabled_r10;

/* Element ----- dmrs-WithOCC-Activated-r10 ------- */
typedef enum enumNhuPUSCH_ConfigDedicatedSCell_r10dmrs_WithOCC_Activated_r10
{
	NhuPUSCH_ConfigDedicatedSCell_r10dmrs_WithOCC_Activated_r10trueEnum
} EnumNhuPUSCH_ConfigDedicatedSCell_r10dmrs_WithOCC_Activated_r10;
typedef TknU32 NhuPUSCH_ConfigDedicatedSCell_r10dmrs_WithOCC_Activated_r10;

typedef struct NhuPUSCH_ConfigDedicatedSCell_r10
{
	TknPres pres;
	NhuPUSCH_ConfigDedicatedSCell_r10groupHoppingDisabled_r10 groupHoppingDisabled_r10;
	NhuPUSCH_ConfigDedicatedSCell_r10dmrs_WithOCC_Activated_r10 dmrs_WithOCC_Activated_r10;
} NhuPUSCH_ConfigDedicatedSCell_r10;

/* Element ----- p0-UE-PUSCH-r10 ------- */
typedef TknS32 NhuUlnkPowerCntrlDedicatedSCell_r10p0_UE_PUSCH_r10;

/* Element ----- deltaMCS-Enabled-r10 ------- */
typedef enum enumNhuUlnkPowerCntrlDedicatedSCell_r10deltaMCS_Enabled_r10
{
	NhuUlnkPowerCntrlDedicatedSCell_r10deltaMCS_Enabled_r10en0Enum,
	NhuUlnkPowerCntrlDedicatedSCell_r10deltaMCS_Enabled_r10en1Enum
} EnumNhuUlnkPowerCntrlDedicatedSCell_r10deltaMCS_Enabled_r10;
typedef TknU32 NhuUlnkPowerCntrlDedicatedSCell_r10deltaMCS_Enabled_r10;

/* Element ----- accumulationEnabled-r10 ------- */
typedef TknU8 NhuUlnkPowerCntrlDedicatedSCell_r10accumulationEnabled_r10;

/* Element ----- pSRS-Offset-r10 ------- */
typedef TknU32 NhuUlnkPowerCntrlDedicatedSCell_r10pSRS_Offset_r10;

/* Element ----- pSRS-OffsetAp-r10 ------- */
typedef TknU32 NhuUlnkPowerCntrlDedicatedSCell_r10pSRS_OffsetAp_r10;

/* Element ----- pathlossReferenceLinking-r10 ------- */
typedef enum enumNhuUlnkPowerCntrlDedicatedSCell_r10pathlossReferenceLinking_r10
{
	NhuUlnkPowerCntrlDedicatedSCell_r10pathlossReferenceLinking_r10pCellEnum,
	NhuUlnkPowerCntrlDedicatedSCell_r10pathlossReferenceLinking_r10sCellEnum
} EnumNhuUlnkPowerCntrlDedicatedSCell_r10pathlossReferenceLinking_r10;
typedef TknU32 NhuUlnkPowerCntrlDedicatedSCell_r10pathlossReferenceLinking_r10;

typedef struct NhuUlnkPowerCntrlDedicatedSCell_r10
{
	TknPres pres;
	NhuUlnkPowerCntrlDedicatedSCell_r10p0_UE_PUSCH_r10 p0_UE_PUSCH_r10;
	NhuUlnkPowerCntrlDedicatedSCell_r10deltaMCS_Enabled_r10 deltaMCS_Enabled_r10;
	NhuUlnkPowerCntrlDedicatedSCell_r10accumulationEnabled_r10 accumulationEnabled_r10;
	NhuUlnkPowerCntrlDedicatedSCell_r10pSRS_Offset_r10 pSRS_Offset_r10;
	NhuUlnkPowerCntrlDedicatedSCell_r10pSRS_OffsetAp_r10 pSRS_OffsetAp_r10;
	NhuFilterCoefficient filterCoefficient_r10;	/* DEFAULT 0 */ 
	NhuUlnkPowerCntrlDedicatedSCell_r10pathlossReferenceLinking_r10 pathlossReferenceLinking_r10;
} NhuUlnkPowerCntrlDedicatedSCell_r10;

/* Element ----- nomPDSCH-RS-EPRE-Offset-r10 ------- */
typedef TknS32 NhuCQI_ReportConfigSCell_r10nomPDSCH_RS_EPRE_Offset_r10;

/* Element ----- pmi-RI-Report-r10 ------- */
typedef enum enumNhuCQI_ReportConfigSCell_r10pmi_RI_Report_r10
{
	NhuCQI_ReportConfigSCell_r10pmi_RI_Report_r10setupEnum
} EnumNhuCQI_ReportConfigSCell_r10pmi_RI_Report_r10;
typedef TknU32 NhuCQI_ReportConfigSCell_r10pmi_RI_Report_r10;

typedef struct NhuCQI_ReportConfigSCell_r10
{
	TknPres pres;
	NhuCQI_ReportModeAperiodic cqi_ReportModeAperiodic_r10;
	NhuCQI_ReportConfigSCell_r10nomPDSCH_RS_EPRE_Offset_r10 nomPDSCH_RS_EPRE_Offset_r10;
	NhuCQI_ReportPeriodic_r10 cqi_ReportPeriodicSCell_r10;
	NhuCQI_ReportConfigSCell_r10pmi_RI_Report_r10 pmi_RI_Report_r10;
} NhuCQI_ReportConfigSCell_r10;

typedef struct NhuPhysicalConfigDedicatedSCell_r10nonUL_Cfg_r10
{
	TknPres pres;
	NhuAntennaInfoDedicated_r10 antennaInfo_r10;
	NhuCrossCarrierSchedulingConfig_r10 crossCarrierSchedulingConfig_r10;
	NhuCSI_RS_Config_r10 csi_RS_Config_r10;
	NhuPDSCH_ConfigDedicated pdsch_ConfigDedicated_r10;
} NhuPhysicalConfigDedicatedSCell_r10nonUL_Cfg_r10;

typedef struct NhuPhysicalConfigDedicatedSCell_r10ul_Cfg_r10
{
	TknPres pres;
	NhuAntennaInfoUL_r10 antennaInfoUL_r10;
	NhuPUSCH_ConfigDedicatedSCell_r10 pusch_ConfigDedicatedSCell_r10;
	NhuUlnkPowerCntrlDedicatedSCell_r10 uplinkPowerCntrlDedicatedSCell_r10;
	NhuCQI_ReportConfigSCell_r10 cqi_ReportConfigSCell_r10;
	NhuSoundingRS_UL_ConfigDedicated soundingRS_UL_ConfigDedicated_r10;
	NhuSoundingRS_UL_ConfigDedicated_v1020 soundingRS_UL_ConfigDedicated_v1020;
	NhuSoundingRS_UL_ConfigDedicatedAperiodic_r10 soundingRS_UL_ConfigDedicatedAperiodic_r10;
} NhuPhysicalConfigDedicatedSCell_r10ul_Cfg_r10;

typedef struct NhuPhysicalConfigDedicatedSCell_r10extaddgrp_1
{
	TknPres pres;
	NhuCSI_RS_ConfigNZPToRlsLst_r11 csi_RS_ConfigNZPToRlsLst_r11;
	NhuCSI_RS_ConfigNZPToAddModLst_r11 csi_RS_ConfigNZPToAddModLst_r11;
	NhuCSI_RS_ConfigZPToRlsLst_r11 csi_RS_ConfigZPToRlsLst_r11;
	NhuCSI_RS_ConfigZPToAddModLst_r11 csi_RS_ConfigZPToAddModLst_r11;
	NhuEPDCCH_Config_r11 epdcch_Config_r11;
	NhuPDSCH_ConfigDedicated_v1130 pdsch_ConfigDedicated_v1130;
	NhuCQI_ReportConfig_v1130 cqi_ReportConfig_v1130;
	NhuPUSCH_ConfigDedicated_v1130 pusch_ConfigDedicated_v1130;
	NhuUlnkPowerCntrlDedicated_v1130 uplinkPowerCntrlDedicatedSCell_v1130;
} NhuPhysicalConfigDedicatedSCell_r10extaddgrp_1;

typedef struct NhuPhysicalConfigDedicatedSCell_r10
{
	TknPres pres;
	NhuPhysicalConfigDedicatedSCell_r10nonUL_Cfg_r10 nonUL_Cfg_r10;
	NhuPhysicalConfigDedicatedSCell_r10ul_Cfg_r10 ul_Cfg_r10;
	NhuPhysicalConfigDedicatedSCell_r10extaddgrp_1 extaddgrp_1;
} NhuPhysicalConfigDedicatedSCell_r10;

typedef struct NhuMAC_MainConfigSCell_r11
{
	TknPres pres;
	NhuSTAG_Id_r11 stag_Id_r11;
} NhuMAC_MainConfigSCell_r11;

typedef struct NhuRadioResourceConfigDedicatedSCell_r10extaddgrp_1
{
	TknPres pres;
	NhuMAC_MainConfigSCell_r11 mac_MainConfigSCell_r11;
} NhuRadioResourceConfigDedicatedSCell_r10extaddgrp_1;

typedef struct NhuRadioResourceConfigDedicatedSCell_r10
{
	TknPres pres;
	NhuPhysicalConfigDedicatedSCell_r10 physicalConfigDedicatedSCell_r10;
	NhuRadioResourceConfigDedicatedSCell_r10extaddgrp_1 extaddgrp_1;
} NhuRadioResourceConfigDedicatedSCell_r10;

typedef struct NhuSCellToAddMod_r10cellIdentification_r10
{
	TknPres pres;
	NhuPhysCellId physCellId_r10;
	NhuARFCN_ValueEUTRA dl_CarrierFreq_r10;
} NhuSCellToAddMod_r10cellIdentification_r10;

typedef struct NhuSCellToAddMod_r10extaddgrp_1
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_v9e0 dl_CarrierFreq_v1090;
} NhuSCellToAddMod_r10extaddgrp_1;

typedef struct NhuSCellToAddMod_r10
{
	TknPres pres;
	NhuSCellIdx_r10 sCellIdx_r10;
	NhuSCellToAddMod_r10cellIdentification_r10 cellIdentification_r10;
	NhuRadioResourceConfigCmnSCell_r10 radioResourceConfigCmnSCell_r10;
	NhuRadioResourceConfigDedicatedSCell_r10 radioResourceConfigDedicatedSCell_r10;
	NhuSCellToAddMod_r10extaddgrp_1 extaddgrp_1;
} NhuSCellToAddMod_r10;

typedef struct NhuSCellToAddModLst_r10
{
	TknU16 noComp;
	NhuSCellToAddMod_r10 *member;
}NhuSCellToAddModLst_r10;

/* Element ---------- systemInfomationBlockType1Dedicated-r11 ----------- */
typedef TknStrOSXL NhuRRCConRecfgn_v1130_IEssystemInfomationBlockTyp1Dedicated_r11;
typedef struct NhuRRCConRecfgn_v1130_IEsnonCriticalExtn
{
	TknPres pres;
} NhuRRCConRecfgn_v1130_IEsnonCriticalExtn;

typedef struct NhuRRCConRecfgn_v1130_IEs
{
	TknPres pres;
	NhuRRCConRecfgn_v1130_IEssystemInfomationBlockTyp1Dedicated_r11 systemInfomationBlockTyp1Dedicated_r11;
	NhuRRCConRecfgn_v1130_IEsnonCriticalExtn nonCriticalExtn;
} NhuRRCConRecfgn_v1130_IEs;

typedef struct NhuRRCConRecfgn_v1020_IEs
{
	TknPres pres;
	NhuSCellToRlsLst_r10 sCellToRlsLst_r10;
	NhuSCellToAddModLst_r10 sCellToAddModLst_r10;
	NhuRRCConRecfgn_v1130_IEs nonCriticalExtn;
} NhuRRCConRecfgn_v1020_IEs;

/* Element ----- fullConfig-r9 ------- */
typedef enum enumNhuRRCConRecfgn_v920_IEsfullConfig_r9
{
	NhuRRCConRecfgn_v920_IEsfullConfig_r9trueEnum
} EnumNhuRRCConRecfgn_v920_IEsfullConfig_r9;
typedef TknU32 NhuRRCConRecfgn_v920_IEsfullConfig_r9;

typedef struct NhuRRCConRecfgn_v920_IEs
{
	TknPres pres;
	NhuOtherConfig_r9 otherConfig_r9;
	NhuRRCConRecfgn_v920_IEsfullConfig_r9 fullConfig_r9;
	NhuRRCConRecfgn_v1020_IEs nonCriticalExtn;
} NhuRRCConRecfgn_v920_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuRRCConRecfgn_v890_IEslateNonCriticalExtn;
typedef struct NhuRRCConRecfgn_v890_IEs
{
	TknPres pres;
	NhuRRCConRecfgn_v890_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuRRCConRecfgn_v920_IEs nonCriticalExtn;
} NhuRRCConRecfgn_v890_IEs;

typedef struct NhuRRCConRecfgn_r8_IEsdedicatedInfoNASLst
{
	TknU16 noComp;
	NhuDedicatedInfoNAS *member;
}NhuRRCConRecfgn_r8_IEsdedicatedInfoNASLst;

typedef struct NhuRRCConRecfgn_r8_IEs
{
	TknPres pres;
	NhuMeasConfig measConfig;
	NhuMobilityCntrlInfo mobilityCntrlInfo;
	NhuRRCConRecfgn_r8_IEsdedicatedInfoNASLst dedicatedInfoNASLst;
	NhuRadioResourceConfigDedicated radioResourceConfigDedicated;
	NhuSecConfigHO securityConfigHO;
	NhuRRCConRecfgn_v890_IEs nonCriticalExtn;
} NhuRRCConRecfgn_r8_IEs;

typedef struct NhuRRCConRecfgncriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuRRCConRecfgn_r8_IEs rrcConRecfgn_r8;
	} val;
} NhuRRCConRecfgncriticalExtnsc1;

typedef struct NhuRRCConRecfgncriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuRRCConRecfgncriticalExtnscriticalExtnsFuture;

typedef struct NhuRRCConRecfgncriticalExtns
{
	TknU8 choice;
	union {
		NhuRRCConRecfgncriticalExtnsc1 c1;
		NhuRRCConRecfgncriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuRRCConRecfgncriticalExtns;

typedef struct NhuRRCConRecfgn
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuRRCConRecfgncriticalExtns criticalExtns;
} NhuRRCConRecfgn;

/* Element ----- ReleaseCause ------- */
typedef enum enumNhuRlsCause
{
	NhuRlsCauseloadBalancingTAUrequiredEnum,
	NhuRlsCauseotherEnum,
	NhuRlsCausecs_FallbackHighPriority_v1020Enum,
	NhuRlsCausespare1Enum
} EnumNhuRlsCause;
typedef TknU32 NhuRlsCause;

typedef struct NhuCarrierFreqLstUTRA_TDD_r10
{
	TknU16 noComp;
	NhuARFCN_ValueUTRA *member;
}NhuCarrierFreqLstUTRA_TDD_r10;

typedef struct NhuRedirectedCarrierInfo
{
	TknU8 choice;
	union {
		NhuARFCN_ValueEUTRA eutra;
		NhuCarrierFreqsGERAN geran;
		NhuARFCN_ValueUTRA utra_FDD;
		NhuARFCN_ValueUTRA utra_TDD;
		NhuCarrierFreqCDMA2000 cdma2000_HRPD;
		NhuCarrierFreqCDMA2000 cdma2000_1xRTT;
		NhuCarrierFreqLstUTRA_TDD_r10 utra_TDD_r10;
	} val;
} NhuRedirectedCarrierInfo;

typedef struct NhuFreqPriorityEUTRA
{
	TknPres pres;
	NhuARFCN_ValueEUTRA carrierFreq;
	NhuCellReselectionPriority cellReselectionPriority;
} NhuFreqPriorityEUTRA;

typedef struct NhuFreqPriorityLstEUTRA
{
	TknU16 noComp;
	NhuFreqPriorityEUTRA *member;
}NhuFreqPriorityLstEUTRA;

typedef struct NhuFreqsPriorityGERAN
{
	TknPres pres;
	NhuCarrierFreqsGERAN carrierFreqs;
	NhuCellReselectionPriority cellReselectionPriority;
} NhuFreqsPriorityGERAN;

typedef struct NhuFreqsPriorityLstGERAN
{
	TknU16 noComp;
	NhuFreqsPriorityGERAN *member;
}NhuFreqsPriorityLstGERAN;

typedef struct NhuFreqPriorityUTRA_FDD
{
	TknPres pres;
	NhuARFCN_ValueUTRA carrierFreq;
	NhuCellReselectionPriority cellReselectionPriority;
} NhuFreqPriorityUTRA_FDD;

typedef struct NhuFreqPriorityLstUTRA_FDD
{
	TknU16 noComp;
	NhuFreqPriorityUTRA_FDD *member;
}NhuFreqPriorityLstUTRA_FDD;

typedef struct NhuFreqPriorityUTRA_TDD
{
	TknPres pres;
	NhuARFCN_ValueUTRA carrierFreq;
	NhuCellReselectionPriority cellReselectionPriority;
} NhuFreqPriorityUTRA_TDD;

typedef struct NhuFreqPriorityLstUTRA_TDD
{
	TknU16 noComp;
	NhuFreqPriorityUTRA_TDD *member;
}NhuFreqPriorityLstUTRA_TDD;

typedef struct NhuBandClassPriorityHRPD
{
	TknPres pres;
	NhuBandclassCDMA2000 bandClass;
	NhuCellReselectionPriority cellReselectionPriority;
} NhuBandClassPriorityHRPD;

typedef struct NhuBandClassPriorityLstHRPD
{
	TknU16 noComp;
	NhuBandClassPriorityHRPD *member;
}NhuBandClassPriorityLstHRPD;

typedef struct NhuBandClassPriority1XRTT
{
	TknPres pres;
	NhuBandclassCDMA2000 bandClass;
	NhuCellReselectionPriority cellReselectionPriority;
} NhuBandClassPriority1XRTT;

typedef struct NhuBandClassPriorityLst1XRTT
{
	TknU16 noComp;
	NhuBandClassPriority1XRTT *member;
}NhuBandClassPriorityLst1XRTT;

/* Element ----- t320 ------- */
typedef enum enumNhuIdleModeMobilityCntrlInfot320
{
	NhuIdleModeMobilityCntrlInfot320min5Enum,
	NhuIdleModeMobilityCntrlInfot320min10Enum,
	NhuIdleModeMobilityCntrlInfot320min20Enum,
	NhuIdleModeMobilityCntrlInfot320min30Enum,
	NhuIdleModeMobilityCntrlInfot320min60Enum,
	NhuIdleModeMobilityCntrlInfot320min120Enum,
	NhuIdleModeMobilityCntrlInfot320min180Enum,
	NhuIdleModeMobilityCntrlInfot320spare1Enum
} EnumNhuIdleModeMobilityCntrlInfot320;
typedef TknU32 NhuIdleModeMobilityCntrlInfot320;

typedef struct NhuIdleModeMobilityCntrlInfo
{
	TknPres pres;
	NhuFreqPriorityLstEUTRA freqPriorityLstEUTRA;
	NhuFreqsPriorityLstGERAN freqPriorityLstGERAN;
	NhuFreqPriorityLstUTRA_FDD freqPriorityLstUTRA_FDD;
	NhuFreqPriorityLstUTRA_TDD freqPriorityLstUTRA_TDD;
	NhuBandClassPriorityLstHRPD bandClassPriorityLstHRPD;
	NhuBandClassPriorityLst1XRTT bandClassPriorityLst1XRTT;
	NhuIdleModeMobilityCntrlInfot320 t320;
} NhuIdleModeMobilityCntrlInfo;

typedef struct NhuCellInfoGERAN_r9
{
	TknPres pres;
	NhuPhysCellIdGERAN physCellId_r9;
	NhuCarrierFreqGERAN carrierFreq_r9;
	NhuSysInfoLstGERAN systemInfo_r9;
} NhuCellInfoGERAN_r9;

typedef struct NhuCellInfoLstGERAN_r9
{
	TknU16 noComp;
	NhuCellInfoGERAN_r9 *member;
}NhuCellInfoLstGERAN_r9;

/* Element ---------- utra-BCCH-Container-r9 ----------- */
typedef TknStrOSXL NhuCellInfoUTRA_FDD_r9utra_BCCH_Cont_r9;
typedef struct NhuCellInfoUTRA_FDD_r9
{
	TknPres pres;
	NhuPhysCellIdUTRA_FDD physCellId_r9;
	NhuCellInfoUTRA_FDD_r9utra_BCCH_Cont_r9 utra_BCCH_Cont_r9;
} NhuCellInfoUTRA_FDD_r9;

typedef struct NhuCellInfoLstUTRA_FDD_r9
{
	TknU16 noComp;
	NhuCellInfoUTRA_FDD_r9 *member;
}NhuCellInfoLstUTRA_FDD_r9;

/* Element ---------- utra-BCCH-Container-r9 ----------- */
typedef TknStrOSXL NhuCellInfoUTRA_TDD_r9utra_BCCH_Cont_r9;
typedef struct NhuCellInfoUTRA_TDD_r9
{
	TknPres pres;
	NhuPhysCellIdUTRA_TDD physCellId_r9;
	NhuCellInfoUTRA_TDD_r9utra_BCCH_Cont_r9 utra_BCCH_Cont_r9;
} NhuCellInfoUTRA_TDD_r9;

typedef struct NhuCellInfoLstUTRA_TDD_r9
{
	TknU16 noComp;
	NhuCellInfoUTRA_TDD_r9 *member;
}NhuCellInfoLstUTRA_TDD_r9;

/* Element ---------- utra-BCCH-Container-r10 ----------- */
typedef TknStrOSXL NhuCellInfoUTRA_TDD_r10utra_BCCH_Cont_r10;
typedef struct NhuCellInfoUTRA_TDD_r10
{
	TknPres pres;
	NhuPhysCellIdUTRA_TDD physCellId_r10;
	NhuARFCN_ValueUTRA carrierFreq_r10;
	NhuCellInfoUTRA_TDD_r10utra_BCCH_Cont_r10 utra_BCCH_Cont_r10;
} NhuCellInfoUTRA_TDD_r10;

typedef struct NhuCellInfoLstUTRA_TDD_r10
{
	TknU16 noComp;
	NhuCellInfoUTRA_TDD_r10 *member;
}NhuCellInfoLstUTRA_TDD_r10;

/* Element ----- extendedWaitTime-r10 ------- */
typedef TknU32 NhuRRCConRls_v1020_IEsextendedWaitTime_r10;

typedef struct NhuRRCConRls_v1020_IEsnonCriticalExtn
{
	TknPres pres;
} NhuRRCConRls_v1020_IEsnonCriticalExtn;

typedef struct NhuRRCConRls_v1020_IEs
{
	TknPres pres;
	NhuRRCConRls_v1020_IEsextendedWaitTime_r10 extendedWaitTime_r10;
	NhuRRCConRls_v1020_IEsnonCriticalExtn nonCriticalExtn;
} NhuRRCConRls_v1020_IEs;

typedef struct NhuRRCConRls_v920_IEscellInfoLst_r9
{
	TknU8 choice;
	union {
		NhuCellInfoLstGERAN_r9 geran_r9;
		NhuCellInfoLstUTRA_FDD_r9 utra_FDD_r9;
		NhuCellInfoLstUTRA_TDD_r9 utra_TDD_r9;
		NhuCellInfoLstUTRA_TDD_r10 utra_TDD_r10;
	} val;
} NhuRRCConRls_v920_IEscellInfoLst_r9;

typedef struct NhuRRCConRls_v920_IEs
{
	TknPres pres;
	NhuRRCConRls_v920_IEscellInfoLst_r9 cellInfoLst_r9;
	NhuRRCConRls_v1020_IEs nonCriticalExtn;
} NhuRRCConRls_v920_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuRRCConRls_v890_IEslateNonCriticalExtn;
typedef struct NhuRRCConRls_v890_IEs
{
	TknPres pres;
	NhuRRCConRls_v890_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuRRCConRls_v920_IEs nonCriticalExtn;
} NhuRRCConRls_v890_IEs;

typedef struct NhuRRCConRls_r8_IEs
{
	TknPres pres;
	NhuRlsCause releaseCause;
	NhuRedirectedCarrierInfo redirectedCarrierInfo;
	NhuIdleModeMobilityCntrlInfo idleModeMobilityCntrlInfo;
	NhuRRCConRls_v890_IEs nonCriticalExtn;
} NhuRRCConRls_r8_IEs;

typedef struct NhuRRCConRlscriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuRRCConRls_r8_IEs rrcConRls_r8;
	} val;
} NhuRRCConRlscriticalExtnsc1;

typedef struct NhuRRCConRlscriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuRRCConRlscriticalExtnscriticalExtnsFuture;

typedef struct NhuRRCConRlscriticalExtns
{
	TknU8 choice;
	union {
		NhuRRCConRlscriticalExtnsc1 c1;
		NhuRRCConRlscriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuRRCConRlscriticalExtns;

typedef struct NhuRRCConRls
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuRRCConRlscriticalExtns criticalExtns;
} NhuRRCConRls;

typedef struct NhuSecConfigSMC
{
	TknPres pres;
	NhuSecAlgorithmConfig securityAlgorithmConfig;
} NhuSecConfigSMC;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSecModeCmd_v8a0_IEslateNonCriticalExtn;
typedef struct NhuSecModeCmd_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuSecModeCmd_v8a0_IEsnonCriticalExtn;

typedef struct NhuSecModeCmd_v8a0_IEs
{
	TknPres pres;
	NhuSecModeCmd_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuSecModeCmd_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuSecModeCmd_v8a0_IEs;

typedef struct NhuSecModeCmd_r8_IEs
{
	TknPres pres;
	NhuSecConfigSMC securityConfigSMC;
	NhuSecModeCmd_v8a0_IEs nonCriticalExtn;
} NhuSecModeCmd_r8_IEs;

typedef struct NhuSecModeCmdcriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuSecModeCmd_r8_IEs securityModeCmd_r8;
	} val;
} NhuSecModeCmdcriticalExtnsc1;

typedef struct NhuSecModeCmdcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuSecModeCmdcriticalExtnscriticalExtnsFuture;

typedef struct NhuSecModeCmdcriticalExtns
{
	TknU8 choice;
	union {
		NhuSecModeCmdcriticalExtnsc1 c1;
		NhuSecModeCmdcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuSecModeCmdcriticalExtns;

typedef struct NhuSecModeCmd
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuSecModeCmdcriticalExtns criticalExtns;
} NhuSecModeCmd;

/* Element ----- RAT-Type ------- */
typedef enum enumNhuRAT_Typ
{
	NhuRAT_TypeutraEnum,
	NhuRAT_TyputraEnum,
	NhuRAT_Typgeran_csEnum,
	NhuRAT_Typgeran_psEnum,
	NhuRAT_Typcdma2000_1XRTTEnum,
	NhuRAT_Typspare3Enum,
	NhuRAT_Typspare2Enum,
	NhuRAT_Typspare1Enum
} EnumNhuRAT_Typ;
typedef TknU32 NhuRAT_Typ;

typedef struct NhuUE_CapRqst
{
	TknU16 noComp;
	NhuRAT_Typ *member;
}NhuUE_CapRqst;

typedef struct NhuUECapEnquiry_v1180_IEsrequestedFrequencyBands_r11
{
	TknU16 noComp;
	NhuFreqBandIndicator_r11 *member;
}NhuUECapEnquiry_v1180_IEsrequestedFrequencyBands_r11;

typedef struct NhuUECapEnquiry_v1180_IEsnonCriticalExtn
{
	TknPres pres;
} NhuUECapEnquiry_v1180_IEsnonCriticalExtn;

typedef struct NhuUECapEnquiry_v1180_IEs
{
	TknPres pres;
	NhuUECapEnquiry_v1180_IEsrequestedFrequencyBands_r11 requestedFrequencyBands_r11;
	NhuUECapEnquiry_v1180_IEsnonCriticalExtn nonCriticalExtn;
} NhuUECapEnquiry_v1180_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuUECapEnquiry_v8a0_IEslateNonCriticalExtn;
typedef struct NhuUECapEnquiry_v8a0_IEs
{
	TknPres pres;
	NhuUECapEnquiry_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuUECapEnquiry_v1180_IEs nonCriticalExtn;
} NhuUECapEnquiry_v8a0_IEs;

typedef struct NhuUECapEnquiry_r8_IEs
{
	TknPres pres;
	NhuUE_CapRqst ue_CapRqst;
	NhuUECapEnquiry_v8a0_IEs nonCriticalExtn;
} NhuUECapEnquiry_r8_IEs;

typedef struct NhuUECapEnquirycriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuUECapEnquiry_r8_IEs ueCapEnquiry_r8;
	} val;
} NhuUECapEnquirycriticalExtnsc1;

typedef struct NhuUECapEnquirycriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuUECapEnquirycriticalExtnscriticalExtnsFuture;

typedef struct NhuUECapEnquirycriticalExtns
{
	TknU8 choice;
	union {
		NhuUECapEnquirycriticalExtnsc1 c1;
		NhuUECapEnquirycriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuUECapEnquirycriticalExtns;

typedef struct NhuUECapEnquiry
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuUECapEnquirycriticalExtns criticalExtns;
} NhuUECapEnquiry;

/* Element ----- countMSB-Uplink ------- */
typedef TknU32 NhuDRB_CountMSB_InfocountMSB_Ulnk;

/* Element ----- countMSB-Downlink ------- */
typedef TknU32 NhuDRB_CountMSB_InfocountMSB_Dlnk;

typedef struct NhuDRB_CountMSB_Info
{
	TknPres pres;
	NhuDRB_Identity drb_Identity;
	NhuDRB_CountMSB_InfocountMSB_Ulnk countMSB_Ulnk;
	NhuDRB_CountMSB_InfocountMSB_Dlnk countMSB_Dlnk;
} NhuDRB_CountMSB_Info;

typedef struct NhuDRB_CountMSB_InfoLst
{
	TknU16 noComp;
	NhuDRB_CountMSB_Info *member;
}NhuDRB_CountMSB_InfoLst;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuCounterCheck_v8a0_IEslateNonCriticalExtn;
typedef struct NhuCounterCheck_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuCounterCheck_v8a0_IEsnonCriticalExtn;

typedef struct NhuCounterCheck_v8a0_IEs
{
	TknPres pres;
	NhuCounterCheck_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuCounterCheck_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuCounterCheck_v8a0_IEs;

typedef struct NhuCounterCheck_r8_IEs
{
	TknPres pres;
	NhuDRB_CountMSB_InfoLst drb_CountMSB_InfoLst;
	NhuCounterCheck_v8a0_IEs nonCriticalExtn;
} NhuCounterCheck_r8_IEs;

typedef struct NhuCounterCheckcriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuCounterCheck_r8_IEs counterCheck_r8;
	} val;
} NhuCounterCheckcriticalExtnsc1;

typedef struct NhuCounterCheckcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuCounterCheckcriticalExtnscriticalExtnsFuture;

typedef struct NhuCounterCheckcriticalExtns
{
	TknU8 choice;
	union {
		NhuCounterCheckcriticalExtnsc1 c1;
		NhuCounterCheckcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuCounterCheckcriticalExtns;

typedef struct NhuCounterCheck
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuCounterCheckcriticalExtns criticalExtns;
} NhuCounterCheck;

/* Element ----- connEstFailReportReq-r11 ------- */
typedef enum enumNhuUEInfoRqst_v1130_IEsconnEstFailReportReq_r11
{
	NhuUEInfoRqst_v1130_IEsconnEstFailReportReq_r11trueEnum
} EnumNhuUEInfoRqst_v1130_IEsconnEstFailReportReq_r11;
typedef TknU32 NhuUEInfoRqst_v1130_IEsconnEstFailReportReq_r11;

typedef struct NhuUEInfoRqst_v1130_IEsnonCriticalExtn
{
	TknPres pres;
} NhuUEInfoRqst_v1130_IEsnonCriticalExtn;

typedef struct NhuUEInfoRqst_v1130_IEs
{
	TknPres pres;
	NhuUEInfoRqst_v1130_IEsconnEstFailReportReq_r11 connEstFailReportReq_r11;
	NhuUEInfoRqst_v1130_IEsnonCriticalExtn nonCriticalExtn;
} NhuUEInfoRqst_v1130_IEs;

/* Element ----- logMeasReportReq-r10 ------- */
typedef enum enumNhuUEInfoRqst_v1020_IEslogMeasReportReq_r10
{
	NhuUEInfoRqst_v1020_IEslogMeasReportReq_r10trueEnum
} EnumNhuUEInfoRqst_v1020_IEslogMeasReportReq_r10;
typedef TknU32 NhuUEInfoRqst_v1020_IEslogMeasReportReq_r10;

typedef struct NhuUEInfoRqst_v1020_IEs
{
	TknPres pres;
	NhuUEInfoRqst_v1020_IEslogMeasReportReq_r10 logMeasReportReq_r10;
	NhuUEInfoRqst_v1130_IEs nonCriticalExtn;
} NhuUEInfoRqst_v1020_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuUEInfoRqst_v930_IEslateNonCriticalExtn;
typedef struct NhuUEInfoRqst_v930_IEs
{
	TknPres pres;
	NhuUEInfoRqst_v930_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuUEInfoRqst_v1020_IEs nonCriticalExtn;
} NhuUEInfoRqst_v930_IEs;

/* Element ----- rach-ReportReq-r9 ------- */
typedef TknU8 NhuUEInfoRqst_r9_IEsrach_ReportReq_r9;

/* Element ----- rlf-ReportReq-r9 ------- */
typedef TknU8 NhuUEInfoRqst_r9_IEsrlf_ReportReq_r9;

typedef struct NhuUEInfoRqst_r9_IEs
{
	TknPres pres;
	NhuUEInfoRqst_r9_IEsrach_ReportReq_r9 rach_ReportReq_r9;
	NhuUEInfoRqst_r9_IEsrlf_ReportReq_r9 rlf_ReportReq_r9;
	NhuUEInfoRqst_v930_IEs nonCriticalExtn;
} NhuUEInfoRqst_r9_IEs;

typedef struct NhuUEInfoRqst_r9criticalExtnsc1
{
	TknU8 choice;
	union {
		NhuUEInfoRqst_r9_IEs ueInfoRqst_r9;
	} val;
} NhuUEInfoRqst_r9criticalExtnsc1;

typedef struct NhuUEInfoRqst_r9criticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuUEInfoRqst_r9criticalExtnscriticalExtnsFuture;

typedef struct NhuUEInfoRqst_r9criticalExtns
{
	TknU8 choice;
	union {
		NhuUEInfoRqst_r9criticalExtnsc1 c1;
		NhuUEInfoRqst_r9criticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuUEInfoRqst_r9criticalExtns;

typedef struct NhuUEInfoRqst_r9
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuUEInfoRqst_r9criticalExtns criticalExtns;
} NhuUEInfoRqst_r9;

/* Element ---------- traceId-r10 ----------- */
typedef TknStrOSXL NhuTraceReference_r10traceId_r10;
typedef struct NhuTraceReference_r10
{
	TknPres pres;
	NhuPLMN_Identity plmn_Identity_r10;
	NhuTraceReference_r10traceId_r10 traceId_r10;
} NhuTraceReference_r10;

/* Element ---------- AbsoluteTimeInfo-r10 ----------- */
typedef TknStrBSXL NhuAbsoluteTimeInfo_r10;
typedef struct NhuCellGlobalIdEUTRA
{
	TknPres pres;
	NhuPLMN_Identity plmn_Identity;
	NhuCellIdentity cellIdentity;
} NhuCellGlobalIdEUTRA;

typedef struct NhuCellGlobalIdLst_r10
{
	TknU16 noComp;
	NhuCellGlobalIdEUTRA *member;
}NhuCellGlobalIdLst_r10;

typedef struct NhuTrackingAreaCodeLst_r10
{
	TknU16 noComp;
	NhuTrackingAreaCode *member;
}NhuTrackingAreaCodeLst_r10;

typedef struct NhuAreaCfg_r10
{
	TknU8 choice;
	union {
		NhuCellGlobalIdLst_r10 cellGlobalIdLst_r10;
		NhuTrackingAreaCodeLst_r10 trackingAreaCodeLst_r10;
	} val;
} NhuAreaCfg_r10;

/* Element ----- LoggingDuration-r10 ------- */
typedef enum enumNhuLoggingDuration_r10
{
	NhuLoggingDuration_r10min10Enum,
	NhuLoggingDuration_r10min20Enum,
	NhuLoggingDuration_r10min40Enum,
	NhuLoggingDuration_r10min60Enum,
	NhuLoggingDuration_r10min90Enum,
	NhuLoggingDuration_r10min120Enum,
	NhuLoggingDuration_r10spare2Enum,
	NhuLoggingDuration_r10spare1Enum
} EnumNhuLoggingDuration_r10;
typedef TknU32 NhuLoggingDuration_r10;

/* Element ----- LoggingInterval-r10 ------- */
typedef enum enumNhuLoggingInterval_r10
{
	NhuLoggingInterval_r10ms1280Enum,
	NhuLoggingInterval_r10ms2560Enum,
	NhuLoggingInterval_r10ms5120Enum,
	NhuLoggingInterval_r10ms10240Enum,
	NhuLoggingInterval_r10ms20480Enum,
	NhuLoggingInterval_r10ms30720Enum,
	NhuLoggingInterval_r10ms40960Enum,
	NhuLoggingInterval_r10ms61440Enum
} EnumNhuLoggingInterval_r10;
typedef TknU32 NhuLoggingInterval_r10;

typedef struct NhuPLMN_IdentityLst3_r11
{
	TknU16 noComp;
	NhuPLMN_Identity *member;
}NhuPLMN_IdentityLst3_r11;

typedef struct NhuTrackingAreaCodeLst_v1130plmn_Identity_perTAC_Lst_r11
{
	TknU16 noComp;
	NhuPLMN_Identity *member;
}NhuTrackingAreaCodeLst_v1130plmn_Identity_perTAC_Lst_r11;

typedef struct NhuTrackingAreaCodeLst_v1130
{
	TknPres pres;
	NhuTrackingAreaCodeLst_v1130plmn_Identity_perTAC_Lst_r11 plmn_Identity_perTAC_Lst_r11;
} NhuTrackingAreaCodeLst_v1130;

typedef struct NhuAreaCfg_v1130
{
	TknPres pres;
	NhuTrackingAreaCodeLst_v1130 trackingAreaCodeLst_v1130;
} NhuAreaCfg_v1130;

typedef struct NhuLoggedMeasurementCfg_v1130_IEsnonCriticalExtn
{
	TknPres pres;
} NhuLoggedMeasurementCfg_v1130_IEsnonCriticalExtn;

typedef struct NhuLoggedMeasurementCfg_v1130_IEs
{
	TknPres pres;
	NhuPLMN_IdentityLst3_r11 plmn_IdentityLst_r11;
	NhuAreaCfg_v1130 areaCfg_v1130;
	NhuLoggedMeasurementCfg_v1130_IEsnonCriticalExtn nonCriticalExtn;
} NhuLoggedMeasurementCfg_v1130_IEs;

/* Element ---------- lateNonCriticalExtension-r10 ----------- */
typedef TknStrOSXL NhuLoggedMeasurementCfg_v1080_IEslateNonCriticalExtn_r10;
typedef struct NhuLoggedMeasurementCfg_v1080_IEs
{
	TknPres pres;
	NhuLoggedMeasurementCfg_v1080_IEslateNonCriticalExtn_r10 lateNonCriticalExtn_r10;
	NhuLoggedMeasurementCfg_v1130_IEs nonCriticalExtn;
} NhuLoggedMeasurementCfg_v1080_IEs;

/* Element ---------- traceRecordingSessionRef-r10 ----------- */
typedef TknStrOSXL NhuLoggedMeasurementCfg_r10_IEstraceRecordingSessionRef_r10;
/* Element ---------- tce-Id-r10 ----------- */
typedef TknStrOSXL NhuLoggedMeasurementCfg_r10_IEstce_Id_r10;
typedef struct NhuLoggedMeasurementCfg_r10_IEs
{
	TknPres pres;
	NhuTraceReference_r10 traceReference_r10;
	NhuLoggedMeasurementCfg_r10_IEstraceRecordingSessionRef_r10 traceRecordingSessionRef_r10;
	NhuLoggedMeasurementCfg_r10_IEstce_Id_r10 tce_Id_r10;
	NhuAbsoluteTimeInfo_r10 absoluteTimeInfo_r10;
	NhuAreaCfg_r10 areaCfg_r10;
	NhuLoggingDuration_r10 loggingDuration_r10;
	NhuLoggingInterval_r10 loggingInterval_r10;
	NhuLoggedMeasurementCfg_v1080_IEs nonCriticalExtn;
} NhuLoggedMeasurementCfg_r10_IEs;

typedef struct NhuLoggedMeasurementCfg_r10criticalExtnsc1
{
	TknU8 choice;
	union {
		NhuLoggedMeasurementCfg_r10_IEs loggedMeasurementCfg_r10;
	} val;
} NhuLoggedMeasurementCfg_r10criticalExtnsc1;

typedef struct NhuLoggedMeasurementCfg_r10criticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuLoggedMeasurementCfg_r10criticalExtnscriticalExtnsFuture;

typedef struct NhuLoggedMeasurementCfg_r10criticalExtns
{
	TknU8 choice;
	union {
		NhuLoggedMeasurementCfg_r10criticalExtnsc1 c1;
		NhuLoggedMeasurementCfg_r10criticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuLoggedMeasurementCfg_r10criticalExtns;

typedef struct NhuLoggedMeasurementCfg_r10
{
	TknPres pres;
	NhuLoggedMeasurementCfg_r10criticalExtns criticalExtns;
} NhuLoggedMeasurementCfg_r10;

/* Element ---------- systemInformationBlockType1-r10 ----------- */
typedef TknStrOSXL NhuRN_SysInfo_r10systemInfoBlockTyp1_r10;
typedef struct NhuRN_SysInfo_r10
{
	TknPres pres;
	NhuRN_SysInfo_r10systemInfoBlockTyp1_r10 systemInfoBlockTyp1_r10;
	NhuSysInfoBlockTyp2 systemInfoBlockTyp2_r10;
} NhuRN_SysInfo_r10;

/* Element ---------- subframeConfigPatternFDD-r10 ----------- */
typedef TknStrBSXL NhuRN_SubfrmConfig_r10subframeConfigPattern_r10subframeConfigPatternFDD_r10;
/* Element ----- subframeConfigPatternTDD-r10 ------- */
typedef TknU32 NhuRN_SubfrmConfig_r10subframeConfigPattern_r10subframeConfigPatternTDD_r10;

typedef struct NhuRN_SubfrmConfig_r10subframeConfigPattern_r10
{
	TknU8 choice;
	union {
		NhuRN_SubfrmConfig_r10subframeConfigPattern_r10subframeConfigPatternFDD_r10 subframeConfigPatternFDD_r10;
		NhuRN_SubfrmConfig_r10subframeConfigPattern_r10subframeConfigPatternTDD_r10 subframeConfigPatternTDD_r10;
	} val;
} NhuRN_SubfrmConfig_r10subframeConfigPattern_r10;

/* Element ----- resourceAllocationType-r10 ------- */
typedef enum enumNhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceAllocnTyp_r10
{
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceAllocnTyp_r10type0Enum,
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceAllocnTyp_r10type1Enum,
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceAllocnTyp_r10type2LocalizedEnum,
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceAllocnTyp_r10type2DistributedEnum,
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceAllocnTyp_r10spare4Enum,
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceAllocnTyp_r10spare3Enum,
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceAllocnTyp_r10spare2Enum,
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceAllocnTyp_r10spare1Enum
} EnumNhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceAllocnTyp_r10;
typedef TknU32 NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceAllocnTyp_r10;

/* Element ---------- nrb6-r10 ----------- */
typedef TknStrBSXL NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10nrb6_r10;
/* Element ---------- nrb15-r10 ----------- */
typedef TknStrBSXL NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10nrb15_r10;
/* Element ---------- nrb25-r10 ----------- */
typedef TknStrBSXL NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10nrb25_r10;
/* Element ---------- nrb50-r10 ----------- */
typedef TknStrBSXL NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10nrb50_r10;
/* Element ---------- nrb75-r10 ----------- */
typedef TknStrBSXL NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10nrb75_r10;
/* Element ---------- nrb100-r10 ----------- */
typedef TknStrBSXL NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10nrb100_r10;
typedef struct NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10
{
	TknU8 choice;
	union {
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10nrb6_r10 nrb6_r10;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10nrb15_r10 nrb15_r10;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10nrb25_r10 nrb25_r10;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10nrb50_r10 nrb50_r10;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10nrb75_r10 nrb75_r10;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10nrb100_r10 nrb100_r10;
	} val;
} NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10;

/* Element ---------- nrb6-r10 ----------- */
typedef TknStrBSXL NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10nrb6_r10;
/* Element ---------- nrb15-r10 ----------- */
typedef TknStrBSXL NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10nrb15_r10;
/* Element ---------- nrb25-r10 ----------- */
typedef TknStrBSXL NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10nrb25_r10;
/* Element ---------- nrb50-r10 ----------- */
typedef TknStrBSXL NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10nrb50_r10;
/* Element ---------- nrb75-r10 ----------- */
typedef TknStrBSXL NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10nrb75_r10;
/* Element ---------- nrb100-r10 ----------- */
typedef TknStrBSXL NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10nrb100_r10;
typedef struct NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10
{
	TknU8 choice;
	union {
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10nrb6_r10 nrb6_r10;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10nrb15_r10 nrb15_r10;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10nrb25_r10 nrb25_r10;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10nrb50_r10 nrb50_r10;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10nrb75_r10 nrb75_r10;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10nrb100_r10 nrb100_r10;
	} val;
} NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10;

typedef struct NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10
{
	TknU8 choice;
	union {
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type01_r10 type01_r10;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10type2_r10 type2_r10;
	} val;
} NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10;

/* Element ----- interleaving-r10 ------- */
typedef enum enumNhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10interleaving_r10
{
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10interleaving_r10crsEnum
} EnumNhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10interleaving_r10;
typedef TknU32 NhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10interleaving_r10;

/* Element ----- noInterleaving-r10 ------- */
typedef enum enumNhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10noInterleaving_r10
{
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10noInterleaving_r10crsEnum,
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10noInterleaving_r10dmrsEnum
} EnumNhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10noInterleaving_r10;
typedef TknU32 NhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10noInterleaving_r10;

typedef struct NhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10
{
	TknU8 choice;
	union {
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10interleaving_r10 interleaving_r10;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10noInterleaving_r10 noInterleaving_r10;
	} val;
} NhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10;

/* Element ----- pdsch-Start-r10 ------- */
typedef TknU32 NhuRN_SubfrmConfig_r10rpdcch_Config_r10pdsch_Start_r10;

typedef TknU32 NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddchannelSelectionMultiplexingBundlingn1PUCCH_AN_Lst_r10Member;

typedef struct NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddchannelSelectionMultiplexingBundlingn1PUCCH_AN_Lst_r10
{
	TknU16 noComp;
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddchannelSelectionMultiplexingBundlingn1PUCCH_AN_Lst_r10Member *member;
}NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddchannelSelectionMultiplexingBundlingn1PUCCH_AN_Lst_r10;

typedef struct NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddchannelSelectionMultiplexingBundling
{
	TknPres pres;
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddchannelSelectionMultiplexingBundlingn1PUCCH_AN_Lst_r10 n1PUCCH_AN_Lst_r10;
} NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddchannelSelectionMultiplexingBundling;

/* Element ----- n1PUCCH-AN-P0-r10 ------- */
typedef TknU32 NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddfallbackForFormat3n1PUCCH_AN_P0_r10;

/* Element ----- n1PUCCH-AN-P1-r10 ------- */
typedef TknU32 NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddfallbackForFormat3n1PUCCH_AN_P1_r10;

typedef struct NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddfallbackForFormat3
{
	TknPres pres;
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddfallbackForFormat3n1PUCCH_AN_P0_r10 n1PUCCH_AN_P0_r10;
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddfallbackForFormat3n1PUCCH_AN_P1_r10 n1PUCCH_AN_P1_r10;
} NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddfallbackForFormat3;

typedef struct NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tdd
{
	TknU8 choice;
	union {
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddchannelSelectionMultiplexingBundling channelSelectionMultiplexingBundling;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddfallbackForFormat3 fallbackForFormat3;
	} val;
} NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tdd;

/* Element ----- n1PUCCH-AN-P0-r10 ------- */
typedef TknU32 NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10fddn1PUCCH_AN_P0_r10;

/* Element ----- n1PUCCH-AN-P1-r10 ------- */
typedef TknU32 NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10fddn1PUCCH_AN_P1_r10;

typedef struct NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10fdd
{
	TknPres pres;
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10fddn1PUCCH_AN_P0_r10 n1PUCCH_AN_P0_r10;
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10fddn1PUCCH_AN_P1_r10 n1PUCCH_AN_P1_r10;
} NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10fdd;

typedef struct NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10
{
	TknU8 choice;
	union {
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tdd tdd;
		NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10fdd fdd;
	} val;
} NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10;

typedef struct NhuRN_SubfrmConfig_r10rpdcch_Config_r10
{
	TknPres pres;
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceAllocnTyp_r10 resourceAllocnTyp_r10;
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceBlockAssignment_r10 resourceBlockAssignment_r10;
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10 demodulationRS_r10;
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10pdsch_Start_r10 pdsch_Start_r10;
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10 pucch_Config_r10;
} NhuRN_SubfrmConfig_r10rpdcch_Config_r10;

typedef struct NhuRN_SubfrmConfig_r10
{
	TknPres pres;
	NhuRN_SubfrmConfig_r10subframeConfigPattern_r10 subframeConfigPattern_r10;
	NhuRN_SubfrmConfig_r10rpdcch_Config_r10 rpdcch_Config_r10;
} NhuRN_SubfrmConfig_r10;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuRNRecfgn_r10_IEslateNonCriticalExtn;
typedef struct NhuRNRecfgn_r10_IEsnonCriticalExtn
{
	TknPres pres;
} NhuRNRecfgn_r10_IEsnonCriticalExtn;

typedef struct NhuRNRecfgn_r10_IEs
{
	TknPres pres;
	NhuRN_SysInfo_r10 rn_SysInfo_r10;
	NhuRN_SubfrmConfig_r10 rn_SubfrmConfig_r10;
	NhuRNRecfgn_r10_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuRNRecfgn_r10_IEsnonCriticalExtn nonCriticalExtn;
} NhuRNRecfgn_r10_IEs;

typedef struct NhuRNRecfgn_r10criticalExtnsc1
{
	TknU8 choice;
	union {
		NhuRNRecfgn_r10_IEs rnRecfgn_r10;
	} val;
} NhuRNRecfgn_r10criticalExtnsc1;

typedef struct NhuRNRecfgn_r10criticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuRNRecfgn_r10criticalExtnscriticalExtnsFuture;

typedef struct NhuRNRecfgn_r10criticalExtns
{
	TknU8 choice;
	union {
		NhuRNRecfgn_r10criticalExtnsc1 c1;
		NhuRNRecfgn_r10criticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuRNRecfgn_r10criticalExtns;

typedef struct NhuRNRecfgn_r10
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuRNRecfgn_r10criticalExtns criticalExtns;
} NhuRNRecfgn_r10;

typedef struct NhuDL_DCCH_MsgTypc1
{
	TknU8 choice;
	union {
		NhuCSFBParamsRspCDMA2000 csfbParamsRspCDMA2000;
		NhuDLInfoTfr dlInfoTfr;
		NhuHovrFromEUTRAPrepRqst handoverFromEUTRAPrepRqst;
		NhuMobilityFromEUTRACmd mobilityFromEUTRACmd;
		NhuRRCConRecfgn rrcConRecfgn;
		NhuRRCConRls rrcConRls;
		NhuSecModeCmd securityModeCmd;
		NhuUECapEnquiry ueCapEnquiry;
		NhuCounterCheck counterCheck;
		NhuUEInfoRqst_r9 ueInfoRqst_r9;
		NhuLoggedMeasurementCfg_r10 loggedMeasurementCfg_r10;
		NhuRNRecfgn_r10 rnRecfgn_r10;
	} val;
} NhuDL_DCCH_MsgTypc1;

typedef struct NhuDL_DCCH_MsgTypmessageClassExtn
{
	TknPres pres;
} NhuDL_DCCH_MsgTypmessageClassExtn;

typedef struct NhuDL_DCCH_MsgTyp
{
	TknU8 choice;
	union {
		NhuDL_DCCH_MsgTypc1 c1;
		NhuDL_DCCH_MsgTypmessageClassExtn messageClassExtn;
	} val;
} NhuDL_DCCH_MsgTyp;

typedef struct NhuDL_DCCH_Msg
{
	TknPres pres;
	NhuDL_DCCH_MsgTyp message;
} NhuDL_DCCH_Msg;

/* Element ---------- ShortMAC-I ----------- */
typedef TknStrBSXL NhuShortMAC_I;
typedef struct NhuReestabUE_Identity
{
	TknPres pres;
	NhuC_RNTI c_RNTI;
	NhuPhysCellId physCellId;
	NhuShortMAC_I shortMAC_I;
} NhuReestabUE_Identity;

/* Element ----- ReestablishmentCause ------- */
typedef enum enumNhuReestbCause
{
	NhuReestbCausereconfigurationFailEnum,
	NhuReestbCausehandoverFailEnum,
	NhuReestbCauseotherFailEnum,
	NhuReestbCausespare1Enum
} EnumNhuReestbCause;
typedef TknU32 NhuReestbCause;

/* Element ---------- spare ----------- */
typedef TknStrBSXL NhuRRCConReestbRqst_r8_IEsspare;
typedef struct NhuRRCConReestbRqst_r8_IEs
{
	TknPres pres;
	NhuReestabUE_Identity ue_Identity;
	NhuReestbCause reestablishmentCause;
	NhuRRCConReestbRqst_r8_IEsspare spare;
} NhuRRCConReestbRqst_r8_IEs;

typedef struct NhuRRCConReestbRqstcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuRRCConReestbRqstcriticalExtnscriticalExtnsFuture;

typedef struct NhuRRCConReestbRqstcriticalExtns
{
	TknU8 choice;
	union {
		NhuRRCConReestbRqst_r8_IEs rrcConReestbRqst_r8;
		NhuRRCConReestbRqstcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuRRCConReestbRqstcriticalExtns;

typedef struct NhuRRCConReestbRqst
{
	TknPres pres;
	NhuRRCConReestbRqstcriticalExtns criticalExtns;
} NhuRRCConReestbRqst;

/* Element ---------- randomValue ----------- */
typedef TknStrBSXL NhuInitUE_IdentityrandomValue;
typedef struct NhuInitUE_Identity
{
	TknU8 choice;
	union {
		NhuS_TMSI s_TMSI;
		NhuInitUE_IdentityrandomValue randomValue;
	} val;
} NhuInitUE_Identity;

/* Element ----- EstablishmentCause ------- */
typedef enum enumNhuEstablishmentCause
{
	NhuEstablishmentCauseemergencyEnum,
	NhuEstablishmentCausehighPriorityAccessEnum,
	NhuEstablishmentCausemt_AccessEnum,
	NhuEstablishmentCausemo_SignallingEnum,
	NhuEstablishmentCausemo_DataEnum,
	NhuEstablishmentCausedelayTolerantAccess_v1020Enum,
	NhuEstablishmentCausespare2Enum,
	NhuEstablishmentCausespare1Enum
} EnumNhuEstablishmentCause;
typedef TknU32 NhuEstablishmentCause;

/* Element ---------- spare ----------- */
typedef TknStrBSXL NhuRRCConRqst_r8_IEsspare;
typedef struct NhuRRCConRqst_r8_IEs
{
	TknPres pres;
	NhuInitUE_Identity ue_Identity;
	NhuEstablishmentCause establishmentCause;
	NhuRRCConRqst_r8_IEsspare spare;
} NhuRRCConRqst_r8_IEs;

typedef struct NhuRRCConRqstcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuRRCConRqstcriticalExtnscriticalExtnsFuture;

typedef struct NhuRRCConRqstcriticalExtns
{
	TknU8 choice;
	union {
		NhuRRCConRqst_r8_IEs rrcConRqst_r8;
		NhuRRCConRqstcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuRRCConRqstcriticalExtns;

typedef struct NhuRRCConRqst
{
	TknPres pres;
	NhuRRCConRqstcriticalExtns criticalExtns;
} NhuRRCConRqst;

typedef struct NhuUL_CCCH_MsgTypc1
{
	TknU8 choice;
	union {
		NhuRRCConReestbRqst rrcConReestbRqst;
		NhuRRCConRqst rrcConRqst;
	} val;
} NhuUL_CCCH_MsgTypc1;

typedef struct NhuUL_CCCH_MsgTypmessageClassExtn
{
	TknPres pres;
} NhuUL_CCCH_MsgTypmessageClassExtn;

typedef struct NhuUL_CCCH_MsgTyp
{
	TknU8 choice;
	union {
		NhuUL_CCCH_MsgTypc1 c1;
		NhuUL_CCCH_MsgTypmessageClassExtn messageClassExtn;
	} val;
} NhuUL_CCCH_MsgTyp;

typedef struct NhuUL_CCCH_Msg
{
	TknPres pres;
	NhuUL_CCCH_MsgTyp message;
} NhuUL_CCCH_Msg;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuCSFBParamsRqstCDMA2000_v8a0_IEslateNonCriticalExtn;
typedef struct NhuCSFBParamsRqstCDMA2000_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuCSFBParamsRqstCDMA2000_v8a0_IEsnonCriticalExtn;

typedef struct NhuCSFBParamsRqstCDMA2000_v8a0_IEs
{
	TknPres pres;
	NhuCSFBParamsRqstCDMA2000_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuCSFBParamsRqstCDMA2000_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuCSFBParamsRqstCDMA2000_v8a0_IEs;

typedef struct NhuCSFBParamsRqstCDMA2000_r8_IEs
{
	TknPres pres;
	NhuCSFBParamsRqstCDMA2000_v8a0_IEs nonCriticalExtn;
} NhuCSFBParamsRqstCDMA2000_r8_IEs;

typedef struct NhuCSFBParamsRqstCDMA2000criticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuCSFBParamsRqstCDMA2000criticalExtnscriticalExtnsFuture;

typedef struct NhuCSFBParamsRqstCDMA2000criticalExtns
{
	TknU8 choice;
	union {
		NhuCSFBParamsRqstCDMA2000_r8_IEs csfbParamsRqstCDMA2000_r8;
		NhuCSFBParamsRqstCDMA2000criticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuCSFBParamsRqstCDMA2000criticalExtns;

typedef struct NhuCSFBParamsRqstCDMA2000
{
	TknPres pres;
	NhuCSFBParamsRqstCDMA2000criticalExtns criticalExtns;
} NhuCSFBParamsRqstCDMA2000;

typedef struct NhuPLMN_IdentityLst2
{
	TknU16 noComp;
	NhuPLMN_Identity *member;
}NhuPLMN_IdentityLst2;

/* Element ----- csg-MemberStatus-r9 ------- */
typedef enum enumNhuAdditionalSI_Info_r9csg_MemberStatus_r9
{
	NhuAdditionalSI_Info_r9csg_MemberStatus_r9memberEnum
} EnumNhuAdditionalSI_Info_r9csg_MemberStatus_r9;
typedef TknU32 NhuAdditionalSI_Info_r9csg_MemberStatus_r9;

typedef struct NhuAdditionalSI_Info_r9
{
	TknPres pres;
	NhuAdditionalSI_Info_r9csg_MemberStatus_r9 csg_MemberStatus_r9;
	NhuCSG_Identity csg_Identity_r9;
} NhuAdditionalSI_Info_r9;

typedef struct NhuMeasResultEUTRAcgi_Info
{
	TknPres pres;
	NhuCellGlobalIdEUTRA cellGlobalId;
	NhuTrackingAreaCode trackingAreaCode;
	NhuPLMN_IdentityLst2 plmn_IdentityLst;
} NhuMeasResultEUTRAcgi_Info;

typedef struct NhuMeasResultEUTRAmeasResultextaddgrp_1
{
	TknPres pres;
	NhuAdditionalSI_Info_r9 additionalSI_Info_r9;
} NhuMeasResultEUTRAmeasResultextaddgrp_1;

typedef struct NhuMeasResultEUTRAmeasResult
{
	TknPres pres;
	NhuRSRP_Range rsrpResult;
	NhuRSRQ_Range rsrqResult;
	NhuMeasResultEUTRAmeasResultextaddgrp_1 extaddgrp_1;
} NhuMeasResultEUTRAmeasResult;

typedef struct NhuMeasResultEUTRA
{
	TknPres pres;
	NhuPhysCellId physCellId;
	NhuMeasResultEUTRAcgi_Info cgi_Info;
	NhuMeasResultEUTRAmeasResult measResult;
} NhuMeasResultEUTRA;

typedef struct NhuMeasResultLstEUTRA
{
	TknU16 noComp;
	NhuMeasResultEUTRA *member;
}NhuMeasResultLstEUTRA;

/* Element ---------- cellIdentity ----------- */
typedef TknStrBSXL NhuCellGlobalIdUTRAcellIdentity;
typedef struct NhuCellGlobalIdUTRA
{
	TknPres pres;
	NhuPLMN_Identity plmn_Identity;
	NhuCellGlobalIdUTRAcellIdentity cellIdentity;
} NhuCellGlobalIdUTRA;

typedef struct NhuMeasResultUTRAphysCellId
{
	TknU8 choice;
	union {
		NhuPhysCellIdUTRA_FDD fdd;
		NhuPhysCellIdUTRA_TDD tdd;
	} val;
} NhuMeasResultUTRAphysCellId;

/* Element ---------- locationAreaCode ----------- */
typedef TknStrBSXL NhuMeasResultUTRAcgi_InfolocationAreaCode;
/* Element ---------- routingAreaCode ----------- */
typedef TknStrBSXL NhuMeasResultUTRAcgi_InforoutingAreaCode;
typedef struct NhuMeasResultUTRAcgi_Info
{
	TknPres pres;
	NhuCellGlobalIdUTRA cellGlobalId;
	NhuMeasResultUTRAcgi_InfolocationAreaCode locationAreaCode;
	NhuMeasResultUTRAcgi_InforoutingAreaCode routingAreaCode;
	NhuPLMN_IdentityLst2 plmn_IdentityLst;
} NhuMeasResultUTRAcgi_Info;

/* Element ----- utra-RSCP ------- */
typedef TknS32 NhuMeasResultUTRAmeasResultutra_RSCP;

/* Element ----- utra-EcN0 ------- */
typedef TknU32 NhuMeasResultUTRAmeasResultutra_EcN0;

typedef struct NhuMeasResultUTRAmeasResultextaddgrp_1
{
	TknPres pres;
	NhuAdditionalSI_Info_r9 additionalSI_Info_r9;
} NhuMeasResultUTRAmeasResultextaddgrp_1;

typedef struct NhuMeasResultUTRAmeasResult
{
	TknPres pres;
	NhuMeasResultUTRAmeasResultutra_RSCP utra_RSCP;
	NhuMeasResultUTRAmeasResultutra_EcN0 utra_EcN0;
	NhuMeasResultUTRAmeasResultextaddgrp_1 extaddgrp_1;
} NhuMeasResultUTRAmeasResult;

typedef struct NhuMeasResultUTRA
{
	TknPres pres;
	NhuMeasResultUTRAphysCellId physCellId;
	NhuMeasResultUTRAcgi_Info cgi_Info;
	NhuMeasResultUTRAmeasResult measResult;
} NhuMeasResultUTRA;

typedef struct NhuMeasResultLstUTRA
{
	TknU16 noComp;
	NhuMeasResultUTRA *member;
}NhuMeasResultLstUTRA;

/* Element ---------- locationAreaCode ----------- */
typedef TknStrBSXL NhuCellGlobalIdGERANlocationAreaCode;
/* Element ---------- cellIdentity ----------- */
typedef TknStrBSXL NhuCellGlobalIdGERANcellIdentity;
typedef struct NhuCellGlobalIdGERAN
{
	TknPres pres;
	NhuPLMN_Identity plmn_Identity;
	NhuCellGlobalIdGERANlocationAreaCode locationAreaCode;
	NhuCellGlobalIdGERANcellIdentity cellIdentity;
} NhuCellGlobalIdGERAN;

/* Element ---------- routingAreaCode ----------- */
typedef TknStrBSXL NhuMeasResultGERANcgi_InforoutingAreaCode;
typedef struct NhuMeasResultGERANcgi_Info
{
	TknPres pres;
	NhuCellGlobalIdGERAN cellGlobalId;
	NhuMeasResultGERANcgi_InforoutingAreaCode routingAreaCode;
} NhuMeasResultGERANcgi_Info;

/* Element ----- rssi ------- */
typedef TknU32 NhuMeasResultGERANmeasResultrssi;

typedef struct NhuMeasResultGERANmeasResult
{
	TknPres pres;
	NhuMeasResultGERANmeasResultrssi rssi;
} NhuMeasResultGERANmeasResult;

typedef struct NhuMeasResultGERAN
{
	TknPres pres;
	NhuCarrierFreqGERAN carrierFreq;
	NhuPhysCellIdGERAN physCellId;
	NhuMeasResultGERANcgi_Info cgi_Info;
	NhuMeasResultGERANmeasResult measResult;
} NhuMeasResultGERAN;

typedef struct NhuMeasResultLstGERAN
{
	TknU16 noComp;
	NhuMeasResultGERAN *member;
}NhuMeasResultLstGERAN;

/* Element ---------- cellGlobalId1XRTT ----------- */
typedef TknStrBSXL NhuCellGlobalIdCDMA2000cellGlobalId1XRTT;
/* Element ---------- cellGlobalIdHRPD ----------- */
typedef TknStrBSXL NhuCellGlobalIdCDMA2000cellGlobalIdHRPD;
typedef struct NhuCellGlobalIdCDMA2000
{
	TknU8 choice;
	union {
		NhuCellGlobalIdCDMA2000cellGlobalId1XRTT cellGlobalId1XRTT;
		NhuCellGlobalIdCDMA2000cellGlobalIdHRPD cellGlobalIdHRPD;
	} val;
} NhuCellGlobalIdCDMA2000;

/* Element ----- pilotPnPhase ------- */
typedef TknU32 NhuMeasResultCDMA2000measResultpilotPnPhase;

/* Element ----- pilotStrength ------- */
typedef TknU32 NhuMeasResultCDMA2000measResultpilotStrength;

typedef struct NhuMeasResultCDMA2000measResult
{
	TknPres pres;
	NhuMeasResultCDMA2000measResultpilotPnPhase pilotPnPhase;
	NhuMeasResultCDMA2000measResultpilotStrength pilotStrength;
} NhuMeasResultCDMA2000measResult;

typedef struct NhuMeasResultCDMA2000
{
	TknPres pres;
	NhuPhysCellIdCDMA2000 physCellId;
	NhuCellGlobalIdCDMA2000 cgi_Info;
	NhuMeasResultCDMA2000measResult measResult;
} NhuMeasResultCDMA2000;

typedef struct NhuMeasResultLstCDMA2000
{
	TknU16 noComp;
	NhuMeasResultCDMA2000 *member;
}NhuMeasResultLstCDMA2000;

/* Element ----- preRegistrationStatusHRPD ------- */
typedef TknU8 NhuMeasResultsCDMA2000preRegistrationStatusHRPD;

typedef struct NhuMeasResultsCDMA2000
{
	TknPres pres;
	NhuMeasResultsCDMA2000preRegistrationStatusHRPD preRegistrationStatusHRPD;
	NhuMeasResultLstCDMA2000 measResultLstCDMA2000;
} NhuMeasResultsCDMA2000;

/* Element ----- ue-RxTxTimeDiffResult-r9 ------- */
typedef TknU32 NhuMeasResultForECID_r9ue_RxTxTimeDiffResult_r9;

/* Element ---------- currentSFN-r9 ----------- */
typedef TknStrBSXL NhuMeasResultForECID_r9currentSFN_r9;
typedef struct NhuMeasResultForECID_r9
{
	TknPres pres;
	NhuMeasResultForECID_r9ue_RxTxTimeDiffResult_r9 ue_RxTxTimeDiffResult_r9;
	NhuMeasResultForECID_r9currentSFN_r9 currentSFN_r9;
} NhuMeasResultForECID_r9;

/* Element ---------- ellipsoid-Point-r10 ----------- */
typedef TknStrOSXL NhuLocInfo_r10locationCoordinates_r10ellipsoid_Point_r10;
/* Element ---------- ellipsoidPointWithAltitude-r10 ----------- */
typedef TknStrOSXL NhuLocInfo_r10locationCoordinates_r10ellipsoidPointWithAltitude_r10;
/* Element ---------- ellipsoidPointWithUncertaintyCircle-r11 ----------- */
typedef TknStrOSXL NhuLocInfo_r10locationCoordinates_r10ellipsoidPointWithUncertaintyCircle_r11;
/* Element ---------- ellipsoidPointWithUncertaintyEllipse-r11 ----------- */
typedef TknStrOSXL NhuLocInfo_r10locationCoordinates_r10ellipsoidPointWithUncertaintyEllipse_r11;
/* Element ---------- ellipsoidPointWithAltitudeAndUncertaintyEllipsoid-r11 ----------- */
typedef TknStrOSXL NhuLocInfo_r10locationCoordinates_r10ellipsoidPointWithAltitudeAndUncertaintyEllipsoid_r11;
/* Element ---------- ellipsoidArc-r11 ----------- */
typedef TknStrOSXL NhuLocInfo_r10locationCoordinates_r10ellipsoidArc_r11;
/* Element ---------- polygon-r11 ----------- */
typedef TknStrOSXL NhuLocInfo_r10locationCoordinates_r10polygon_r11;
typedef struct NhuLocInfo_r10locationCoordinates_r10
{
	TknU8 choice;
	union {
		NhuLocInfo_r10locationCoordinates_r10ellipsoid_Point_r10 ellipsoid_Point_r10;
		NhuLocInfo_r10locationCoordinates_r10ellipsoidPointWithAltitude_r10 ellipsoidPointWithAltitude_r10;
		NhuLocInfo_r10locationCoordinates_r10ellipsoidPointWithUncertaintyCircle_r11 ellipsoidPointWithUncertaintyCircle_r11;
		NhuLocInfo_r10locationCoordinates_r10ellipsoidPointWithUncertaintyEllipse_r11 ellipsoidPointWithUncertaintyEllipse_r11;
		NhuLocInfo_r10locationCoordinates_r10ellipsoidPointWithAltitudeAndUncertaintyEllipsoid_r11 ellipsoidPointWithAltitudeAndUncertaintyEllipsoid_r11;
		NhuLocInfo_r10locationCoordinates_r10ellipsoidArc_r11 ellipsoidArc_r11;
		NhuLocInfo_r10locationCoordinates_r10polygon_r11 polygon_r11;
	} val;
} NhuLocInfo_r10locationCoordinates_r10;

/* Element ---------- horizontalVelocity-r10 ----------- */
typedef TknStrOSXL NhuLocInfo_r10horizontalVelocity_r10;
/* Element ---------- gnss-TOD-msec-r10 ----------- */
typedef TknStrOSXL NhuLocInfo_r10gnss_TOD_msec_r10;
typedef struct NhuLocInfo_r10
{
	TknPres pres;
	NhuLocInfo_r10locationCoordinates_r10 locationCoordinates_r10;
	NhuLocInfo_r10horizontalVelocity_r10 horizontalVelocity_r10;
	NhuLocInfo_r10gnss_TOD_msec_r10 gnss_TOD_msec_r10;
} NhuLocInfo_r10;

typedef struct NhuMeasResultServFreq_r10measResultSCell_r10
{
	TknPres pres;
	NhuRSRP_Range rsrpResultSCell_r10;
	NhuRSRQ_Range rsrqResultSCell_r10;
} NhuMeasResultServFreq_r10measResultSCell_r10;

typedef struct NhuMeasResultServFreq_r10measResultBestNeighCell_r10
{
	TknPres pres;
	NhuPhysCellId physCellId_r10;
	NhuRSRP_Range rsrpResultNCell_r10;
	NhuRSRQ_Range rsrqResultNCell_r10;
} NhuMeasResultServFreq_r10measResultBestNeighCell_r10;

typedef struct NhuMeasResultServFreq_r10
{
	TknPres pres;
	NhuServCellIdx_r10 servFreqId_r10;
	NhuMeasResultServFreq_r10measResultSCell_r10 measResultSCell_r10;
	NhuMeasResultServFreq_r10measResultBestNeighCell_r10 measResultBestNeighCell_r10;
} NhuMeasResultServFreq_r10;

typedef struct NhuMeasResultServFreqLst_r10
{
	TknU16 noComp;
	NhuMeasResultServFreq_r10 *member;
}NhuMeasResultServFreqLst_r10;

typedef struct NhuMeasResultsmeasResultPCell
{
	TknPres pres;
	NhuRSRP_Range rsrpResult;
	NhuRSRQ_Range rsrqResult;
} NhuMeasResultsmeasResultPCell;

typedef struct NhuMeasResultsmeasResultNeighCells
{
	TknU8 choice;
	union {
		NhuMeasResultLstEUTRA measResultLstEUTRA;
		NhuMeasResultLstUTRA measResultLstUTRA;
		NhuMeasResultLstGERAN measResultLstGERAN;
		NhuMeasResultsCDMA2000 measResultsCDMA2000;
	} val;
} NhuMeasResultsmeasResultNeighCells;

typedef struct NhuMeasResultsextaddgrp_1
{
	TknPres pres;
	NhuMeasResultForECID_r9 measResultForECID_r9;
} NhuMeasResultsextaddgrp_1;

typedef struct NhuMeasResultsextaddgrp_2
{
	TknPres pres;
	NhuLocInfo_r10 locationInfo_r10;
	NhuMeasResultServFreqLst_r10 measResultServFreqLst_r10;
} NhuMeasResultsextaddgrp_2;

typedef struct NhuMeasResults
{
	TknPres pres;
	NhuMeasId measId;
	NhuMeasResultsmeasResultPCell measResultPCell;
	NhuMeasResultsmeasResultNeighCells measResultNeighCells;
	NhuMeasResultsextaddgrp_1 extaddgrp_1;
	NhuMeasResultsextaddgrp_2 extaddgrp_2;
} NhuMeasResults;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuMeasurementReport_v8a0_IEslateNonCriticalExtn;
typedef struct NhuMeasurementReport_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuMeasurementReport_v8a0_IEsnonCriticalExtn;

typedef struct NhuMeasurementReport_v8a0_IEs
{
	TknPres pres;
	NhuMeasurementReport_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuMeasurementReport_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuMeasurementReport_v8a0_IEs;

typedef struct NhuMeasurementReport_r8_IEs
{
	TknPres pres;
	NhuMeasResults measResults;
	NhuMeasurementReport_v8a0_IEs nonCriticalExtn;
} NhuMeasurementReport_r8_IEs;

typedef struct NhuMeasurementReportcriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuMeasurementReport_r8_IEs measurementReport_r8;
	} val;
} NhuMeasurementReportcriticalExtnsc1;

typedef struct NhuMeasurementReportcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuMeasurementReportcriticalExtnscriticalExtnsFuture;

typedef struct NhuMeasurementReportcriticalExtns
{
	TknU8 choice;
	union {
		NhuMeasurementReportcriticalExtnsc1 c1;
		NhuMeasurementReportcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuMeasurementReportcriticalExtns;

typedef struct NhuMeasurementReport
{
	TknPres pres;
	NhuMeasurementReportcriticalExtns criticalExtns;
} NhuMeasurementReport;

/* Element ----- connEstFailInfoAvailable-r11 ------- */
typedef enum enumNhuRRCConRecfgnCompl_v1130_IEsconnEstFailInfoAvailable_r11
{
	NhuRRCConRecfgnCompl_v1130_IEsconnEstFailInfoAvailable_r11trueEnum
} EnumNhuRRCConRecfgnCompl_v1130_IEsconnEstFailInfoAvailable_r11;
typedef TknU32 NhuRRCConRecfgnCompl_v1130_IEsconnEstFailInfoAvailable_r11;

typedef struct NhuRRCConRecfgnCompl_v1130_IEsnonCriticalExtn
{
	TknPres pres;
} NhuRRCConRecfgnCompl_v1130_IEsnonCriticalExtn;

typedef struct NhuRRCConRecfgnCompl_v1130_IEs
{
	TknPres pres;
	NhuRRCConRecfgnCompl_v1130_IEsconnEstFailInfoAvailable_r11 connEstFailInfoAvailable_r11;
	NhuRRCConRecfgnCompl_v1130_IEsnonCriticalExtn nonCriticalExtn;
} NhuRRCConRecfgnCompl_v1130_IEs;

/* Element ----- rlf-InfoAvailable-r10 ------- */
typedef enum enumNhuRRCConRecfgnCompl_v1020_IEsrlf_InfoAvailable_r10
{
	NhuRRCConRecfgnCompl_v1020_IEsrlf_InfoAvailable_r10trueEnum
} EnumNhuRRCConRecfgnCompl_v1020_IEsrlf_InfoAvailable_r10;
typedef TknU32 NhuRRCConRecfgnCompl_v1020_IEsrlf_InfoAvailable_r10;

/* Element ----- logMeasAvailable-r10 ------- */
typedef enum enumNhuRRCConRecfgnCompl_v1020_IEslogMeasAvailable_r10
{
	NhuRRCConRecfgnCompl_v1020_IEslogMeasAvailable_r10trueEnum
} EnumNhuRRCConRecfgnCompl_v1020_IEslogMeasAvailable_r10;
typedef TknU32 NhuRRCConRecfgnCompl_v1020_IEslogMeasAvailable_r10;

typedef struct NhuRRCConRecfgnCompl_v1020_IEs
{
	TknPres pres;
	NhuRRCConRecfgnCompl_v1020_IEsrlf_InfoAvailable_r10 rlf_InfoAvailable_r10;
	NhuRRCConRecfgnCompl_v1020_IEslogMeasAvailable_r10 logMeasAvailable_r10;
	NhuRRCConRecfgnCompl_v1130_IEs nonCriticalExtn;
} NhuRRCConRecfgnCompl_v1020_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuRRCConRecfgnCompl_v8a0_IEslateNonCriticalExtn;
typedef struct NhuRRCConRecfgnCompl_v8a0_IEs
{
	TknPres pres;
	NhuRRCConRecfgnCompl_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuRRCConRecfgnCompl_v1020_IEs nonCriticalExtn;
} NhuRRCConRecfgnCompl_v8a0_IEs;

typedef struct NhuRRCConRecfgnCompl_r8_IEs
{
	TknPres pres;
	NhuRRCConRecfgnCompl_v8a0_IEs nonCriticalExtn;
} NhuRRCConRecfgnCompl_r8_IEs;

typedef struct NhuRRCConRecfgnComplcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuRRCConRecfgnComplcriticalExtnscriticalExtnsFuture;

typedef struct NhuRRCConRecfgnComplcriticalExtns
{
	TknU8 choice;
	union {
		NhuRRCConRecfgnCompl_r8_IEs rrcConRecfgnCompl_r8;
		NhuRRCConRecfgnComplcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuRRCConRecfgnComplcriticalExtns;

typedef struct NhuRRCConRecfgnCompl
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuRRCConRecfgnComplcriticalExtns criticalExtns;
} NhuRRCConRecfgnCompl;

/* Element ----- connEstFailInfoAvailable-r11 ------- */
typedef enum enumNhuRRCConReestbCompl_v1130_IEsconnEstFailInfoAvailable_r11
{
	NhuRRCConReestbCompl_v1130_IEsconnEstFailInfoAvailable_r11trueEnum
} EnumNhuRRCConReestbCompl_v1130_IEsconnEstFailInfoAvailable_r11;
typedef TknU32 NhuRRCConReestbCompl_v1130_IEsconnEstFailInfoAvailable_r11;

typedef struct NhuRRCConReestbCompl_v1130_IEsnonCriticalExtn
{
	TknPres pres;
} NhuRRCConReestbCompl_v1130_IEsnonCriticalExtn;

typedef struct NhuRRCConReestbCompl_v1130_IEs
{
	TknPres pres;
	NhuRRCConReestbCompl_v1130_IEsconnEstFailInfoAvailable_r11 connEstFailInfoAvailable_r11;
	NhuRRCConReestbCompl_v1130_IEsnonCriticalExtn nonCriticalExtn;
} NhuRRCConReestbCompl_v1130_IEs;

/* Element ----- logMeasAvailable-r10 ------- */
typedef enum enumNhuRRCConReestbCompl_v1020_IEslogMeasAvailable_r10
{
	NhuRRCConReestbCompl_v1020_IEslogMeasAvailable_r10trueEnum
} EnumNhuRRCConReestbCompl_v1020_IEslogMeasAvailable_r10;
typedef TknU32 NhuRRCConReestbCompl_v1020_IEslogMeasAvailable_r10;

typedef struct NhuRRCConReestbCompl_v1020_IEs
{
	TknPres pres;
	NhuRRCConReestbCompl_v1020_IEslogMeasAvailable_r10 logMeasAvailable_r10;
	NhuRRCConReestbCompl_v1130_IEs nonCriticalExtn;
} NhuRRCConReestbCompl_v1020_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuRRCConReestbCompl_v8a0_IEslateNonCriticalExtn;
typedef struct NhuRRCConReestbCompl_v8a0_IEs
{
	TknPres pres;
	NhuRRCConReestbCompl_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuRRCConReestbCompl_v1020_IEs nonCriticalExtn;
} NhuRRCConReestbCompl_v8a0_IEs;

/* Element ----- rlf-InfoAvailable-r9 ------- */
typedef enum enumNhuRRCConReestbCompl_v920_IEsrlf_InfoAvailable_r9
{
	NhuRRCConReestbCompl_v920_IEsrlf_InfoAvailable_r9trueEnum
} EnumNhuRRCConReestbCompl_v920_IEsrlf_InfoAvailable_r9;
typedef TknU32 NhuRRCConReestbCompl_v920_IEsrlf_InfoAvailable_r9;

typedef struct NhuRRCConReestbCompl_v920_IEs
{
	TknPres pres;
	NhuRRCConReestbCompl_v920_IEsrlf_InfoAvailable_r9 rlf_InfoAvailable_r9;
	NhuRRCConReestbCompl_v8a0_IEs nonCriticalExtn;
} NhuRRCConReestbCompl_v920_IEs;

typedef struct NhuRRCConReestbCompl_r8_IEs
{
	TknPres pres;
	NhuRRCConReestbCompl_v920_IEs nonCriticalExtn;
} NhuRRCConReestbCompl_r8_IEs;

typedef struct NhuRRCConReestbComplcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuRRCConReestbComplcriticalExtnscriticalExtnsFuture;

typedef struct NhuRRCConReestbComplcriticalExtns
{
	TknU8 choice;
	union {
		NhuRRCConReestbCompl_r8_IEs rrcConReestbCompl_r8;
		NhuRRCConReestbComplcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuRRCConReestbComplcriticalExtns;

typedef struct NhuRRCConReestbCompl
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuRRCConReestbComplcriticalExtns criticalExtns;
} NhuRRCConReestbCompl;

/* Element ---------- mmegi ----------- */
typedef TknStrBSXL NhuRegisteredMMEmmegi;
typedef struct NhuRegisteredMME
{
	TknPres pres;
	NhuPLMN_Identity plmn_Identity;
	NhuRegisteredMMEmmegi mmegi;
	NhuMMEC mmec;
} NhuRegisteredMME;

/* Element ----- connEstFailInfoAvailable-r11 ------- */
typedef enum enumNhuRRCConSetupCompl_v1130_IEsconnEstFailInfoAvailable_r11
{
	NhuRRCConSetupCompl_v1130_IEsconnEstFailInfoAvailable_r11trueEnum
} EnumNhuRRCConSetupCompl_v1130_IEsconnEstFailInfoAvailable_r11;
typedef TknU32 NhuRRCConSetupCompl_v1130_IEsconnEstFailInfoAvailable_r11;

typedef struct NhuRRCConSetupCompl_v1130_IEsnonCriticalExtn
{
	TknPres pres;
} NhuRRCConSetupCompl_v1130_IEsnonCriticalExtn;

typedef struct NhuRRCConSetupCompl_v1130_IEs
{
	TknPres pres;
	NhuRRCConSetupCompl_v1130_IEsconnEstFailInfoAvailable_r11 connEstFailInfoAvailable_r11;
	NhuRRCConSetupCompl_v1130_IEsnonCriticalExtn nonCriticalExtn;
} NhuRRCConSetupCompl_v1130_IEs;

/* Element ----- gummei-Type-r10 ------- */
typedef enum enumNhuRRCConSetupCompl_v1020_IEsgummei_Typ_r10
{
	NhuRRCConSetupCompl_v1020_IEsgummei_Typ_r10nativeEnum,
	NhuRRCConSetupCompl_v1020_IEsgummei_Typ_r10mappedEnum
} EnumNhuRRCConSetupCompl_v1020_IEsgummei_Typ_r10;
typedef TknU32 NhuRRCConSetupCompl_v1020_IEsgummei_Typ_r10;

/* Element ----- rlf-InfoAvailable-r10 ------- */
typedef enum enumNhuRRCConSetupCompl_v1020_IEsrlf_InfoAvailable_r10
{
	NhuRRCConSetupCompl_v1020_IEsrlf_InfoAvailable_r10trueEnum
} EnumNhuRRCConSetupCompl_v1020_IEsrlf_InfoAvailable_r10;
typedef TknU32 NhuRRCConSetupCompl_v1020_IEsrlf_InfoAvailable_r10;

/* Element ----- logMeasAvailable-r10 ------- */
typedef enum enumNhuRRCConSetupCompl_v1020_IEslogMeasAvailable_r10
{
	NhuRRCConSetupCompl_v1020_IEslogMeasAvailable_r10trueEnum
} EnumNhuRRCConSetupCompl_v1020_IEslogMeasAvailable_r10;
typedef TknU32 NhuRRCConSetupCompl_v1020_IEslogMeasAvailable_r10;

/* Element ----- rn-SubframeConfigReq-r10 ------- */
typedef enum enumNhuRRCConSetupCompl_v1020_IEsrn_SubfrmConfigReq_r10
{
	NhuRRCConSetupCompl_v1020_IEsrn_SubfrmConfigReq_r10requiredEnum,
	NhuRRCConSetupCompl_v1020_IEsrn_SubfrmConfigReq_r10notReqdEnum
} EnumNhuRRCConSetupCompl_v1020_IEsrn_SubfrmConfigReq_r10;
typedef TknU32 NhuRRCConSetupCompl_v1020_IEsrn_SubfrmConfigReq_r10;

typedef struct NhuRRCConSetupCompl_v1020_IEs
{
	TknPres pres;
	NhuRRCConSetupCompl_v1020_IEsgummei_Typ_r10 gummei_Typ_r10;
	NhuRRCConSetupCompl_v1020_IEsrlf_InfoAvailable_r10 rlf_InfoAvailable_r10;
	NhuRRCConSetupCompl_v1020_IEslogMeasAvailable_r10 logMeasAvailable_r10;
	NhuRRCConSetupCompl_v1020_IEsrn_SubfrmConfigReq_r10 rn_SubfrmConfigReq_r10;
	NhuRRCConSetupCompl_v1130_IEs nonCriticalExtn;
} NhuRRCConSetupCompl_v1020_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuRRCConSetupCompl_v8a0_IEslateNonCriticalExtn;
typedef struct NhuRRCConSetupCompl_v8a0_IEs
{
	TknPres pres;
	NhuRRCConSetupCompl_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuRRCConSetupCompl_v1020_IEs nonCriticalExtn;
} NhuRRCConSetupCompl_v8a0_IEs;

/* Element ----- selectedPLMN-Identity ------- */
typedef TknU32 NhuRRCConSetupCompl_r8_IEsselectedPLMN_Identity;

typedef struct NhuRRCConSetupCompl_r8_IEs
{
	TknPres pres;
	NhuRRCConSetupCompl_r8_IEsselectedPLMN_Identity selectedPLMN_Identity;
	NhuRegisteredMME registeredMME;
	NhuDedicatedInfoNAS dedicatedInfoNAS;
	NhuRRCConSetupCompl_v8a0_IEs nonCriticalExtn;
} NhuRRCConSetupCompl_r8_IEs;

typedef struct NhuRRCConSetupComplcriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuRRCConSetupCompl_r8_IEs rrcConSetupCompl_r8;
	} val;
} NhuRRCConSetupComplcriticalExtnsc1;

typedef struct NhuRRCConSetupComplcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuRRCConSetupComplcriticalExtnscriticalExtnsFuture;

typedef struct NhuRRCConSetupComplcriticalExtns
{
	TknU8 choice;
	union {
		NhuRRCConSetupComplcriticalExtnsc1 c1;
		NhuRRCConSetupComplcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuRRCConSetupComplcriticalExtns;

typedef struct NhuRRCConSetupCompl
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuRRCConSetupComplcriticalExtns criticalExtns;
} NhuRRCConSetupCompl;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSecModeCompl_v8a0_IEslateNonCriticalExtn;
typedef struct NhuSecModeCompl_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuSecModeCompl_v8a0_IEsnonCriticalExtn;

typedef struct NhuSecModeCompl_v8a0_IEs
{
	TknPres pres;
	NhuSecModeCompl_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuSecModeCompl_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuSecModeCompl_v8a0_IEs;

typedef struct NhuSecModeCompl_r8_IEs
{
	TknPres pres;
	NhuSecModeCompl_v8a0_IEs nonCriticalExtn;
} NhuSecModeCompl_r8_IEs;

typedef struct NhuSecModeComplcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuSecModeComplcriticalExtnscriticalExtnsFuture;

typedef struct NhuSecModeComplcriticalExtns
{
	TknU8 choice;
	union {
		NhuSecModeCompl_r8_IEs securityModeCompl_r8;
		NhuSecModeComplcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuSecModeComplcriticalExtns;

typedef struct NhuSecModeCompl
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuSecModeComplcriticalExtns criticalExtns;
} NhuSecModeCompl;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuSecModeFail_v8a0_IEslateNonCriticalExtn;
typedef struct NhuSecModeFail_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuSecModeFail_v8a0_IEsnonCriticalExtn;

typedef struct NhuSecModeFail_v8a0_IEs
{
	TknPres pres;
	NhuSecModeFail_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuSecModeFail_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuSecModeFail_v8a0_IEs;

typedef struct NhuSecModeFail_r8_IEs
{
	TknPres pres;
	NhuSecModeFail_v8a0_IEs nonCriticalExtn;
} NhuSecModeFail_r8_IEs;

typedef struct NhuSecModeFailcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuSecModeFailcriticalExtnscriticalExtnsFuture;

typedef struct NhuSecModeFailcriticalExtns
{
	TknU8 choice;
	union {
		NhuSecModeFail_r8_IEs securityModeFail_r8;
		NhuSecModeFailcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuSecModeFailcriticalExtns;

typedef struct NhuSecModeFail
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuSecModeFailcriticalExtns criticalExtns;
} NhuSecModeFail;

/* Element ---------- ueCapabilityRAT-Container ----------- */
typedef TknStrOSXL NhuUE_CapRAT_ContueCapRAT_Cont;
typedef struct NhuUE_CapRAT_Cont
{
	TknPres pres;
	NhuRAT_Typ rat_Typ;
	NhuUE_CapRAT_ContueCapRAT_Cont ueCapRAT_Cont;
} NhuUE_CapRAT_Cont;

typedef struct NhuUE_CapRAT_ContLst
{
	TknU16 noComp;
	NhuUE_CapRAT_Cont *member;
}NhuUE_CapRAT_ContLst;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuUECapInfo_v8a0_IEslateNonCriticalExtn;
typedef struct NhuUECapInfo_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuUECapInfo_v8a0_IEsnonCriticalExtn;

typedef struct NhuUECapInfo_v8a0_IEs
{
	TknPres pres;
	NhuUECapInfo_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuUECapInfo_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuUECapInfo_v8a0_IEs;

typedef struct NhuUECapInfo_r8_IEs
{
	TknPres pres;
	NhuUE_CapRAT_ContLst ue_CapRAT_ContLst;
	NhuUECapInfo_v8a0_IEs nonCriticalExtn;
} NhuUECapInfo_r8_IEs;

typedef struct NhuUECapInfocriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuUECapInfo_r8_IEs ueCapInfo_r8;
	} val;
} NhuUECapInfocriticalExtnsc1;

typedef struct NhuUECapInfocriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuUECapInfocriticalExtnscriticalExtnsFuture;

typedef struct NhuUECapInfocriticalExtns
{
	TknU8 choice;
	union {
		NhuUECapInfocriticalExtnsc1 c1;
		NhuUECapInfocriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuUECapInfocriticalExtns;

typedef struct NhuUECapInfo
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuUECapInfocriticalExtns criticalExtns;
} NhuUECapInfo;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuULHovrPrepTfr_v8a0_IEslateNonCriticalExtn;
typedef struct NhuULHovrPrepTfr_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuULHovrPrepTfr_v8a0_IEsnonCriticalExtn;

typedef struct NhuULHovrPrepTfr_v8a0_IEs
{
	TknPres pres;
	NhuULHovrPrepTfr_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuULHovrPrepTfr_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuULHovrPrepTfr_v8a0_IEs;

/* Element ---------- meid ----------- */
typedef TknStrBSXL NhuULHovrPrepTfr_r8_IEsmeid;
typedef struct NhuULHovrPrepTfr_r8_IEs
{
	TknPres pres;
	NhuCDMA2000_Typ cdma2000_Typ;
	NhuULHovrPrepTfr_r8_IEsmeid meid;
	NhuDedicatedInfoCDMA2000 dedicatedInfo;
	NhuULHovrPrepTfr_v8a0_IEs nonCriticalExtn;
} NhuULHovrPrepTfr_r8_IEs;

typedef struct NhuULHovrPrepTfrcriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuULHovrPrepTfr_r8_IEs ulHovrPrepTfr_r8;
	} val;
} NhuULHovrPrepTfrcriticalExtnsc1;

typedef struct NhuULHovrPrepTfrcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuULHovrPrepTfrcriticalExtnscriticalExtnsFuture;

typedef struct NhuULHovrPrepTfrcriticalExtns
{
	TknU8 choice;
	union {
		NhuULHovrPrepTfrcriticalExtnsc1 c1;
		NhuULHovrPrepTfrcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuULHovrPrepTfrcriticalExtns;

typedef struct NhuULHovrPrepTfr
{
	TknPres pres;
	NhuULHovrPrepTfrcriticalExtns criticalExtns;
} NhuULHovrPrepTfr;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuULInfoTfr_v8a0_IEslateNonCriticalExtn;
typedef struct NhuULInfoTfr_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuULInfoTfr_v8a0_IEsnonCriticalExtn;

typedef struct NhuULInfoTfr_v8a0_IEs
{
	TknPres pres;
	NhuULInfoTfr_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuULInfoTfr_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuULInfoTfr_v8a0_IEs;

typedef struct NhuULInfoTfr_r8_IEsdedicatedInfoTyp
{
	TknU8 choice;
	union {
		NhuDedicatedInfoNAS dedicatedInfoNAS;
		NhuDedicatedInfoCDMA2000 dedicatedInfoCDMA2000_1XRTT;
		NhuDedicatedInfoCDMA2000 dedicatedInfoCDMA2000_HRPD;
	} val;
} NhuULInfoTfr_r8_IEsdedicatedInfoTyp;

typedef struct NhuULInfoTfr_r8_IEs
{
	TknPres pres;
	NhuULInfoTfr_r8_IEsdedicatedInfoTyp dedicatedInfoTyp;
	NhuULInfoTfr_v8a0_IEs nonCriticalExtn;
} NhuULInfoTfr_r8_IEs;

typedef struct NhuULInfoTfrcriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuULInfoTfr_r8_IEs ulInfoTfr_r8;
	} val;
} NhuULInfoTfrcriticalExtnsc1;

typedef struct NhuULInfoTfrcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuULInfoTfrcriticalExtnscriticalExtnsFuture;

typedef struct NhuULInfoTfrcriticalExtns
{
	TknU8 choice;
	union {
		NhuULInfoTfrcriticalExtnsc1 c1;
		NhuULInfoTfrcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuULInfoTfrcriticalExtns;

typedef struct NhuULInfoTfr
{
	TknPres pres;
	NhuULInfoTfrcriticalExtns criticalExtns;
} NhuULInfoTfr;

/* Element ----- count-Uplink ------- */
typedef TknU32 NhuDRB_CountInfocount_Ulnk;

/* Element ----- count-Downlink ------- */
typedef TknU32 NhuDRB_CountInfocount_Dlnk;

typedef struct NhuDRB_CountInfo
{
	TknPres pres;
	NhuDRB_Identity drb_Identity;
	NhuDRB_CountInfocount_Ulnk count_Ulnk;
	NhuDRB_CountInfocount_Dlnk count_Dlnk;
} NhuDRB_CountInfo;

typedef struct NhuDRB_CountInfoLst
{
	TknU16 noComp;
	NhuDRB_CountInfo *member;
}NhuDRB_CountInfoLst;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuCounterCheckRsp_v8a0_IEslateNonCriticalExtn;
typedef struct NhuCounterCheckRsp_v8a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuCounterCheckRsp_v8a0_IEsnonCriticalExtn;

typedef struct NhuCounterCheckRsp_v8a0_IEs
{
	TknPres pres;
	NhuCounterCheckRsp_v8a0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuCounterCheckRsp_v8a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuCounterCheckRsp_v8a0_IEs;

typedef struct NhuCounterCheckRsp_r8_IEs
{
	TknPres pres;
	NhuDRB_CountInfoLst drb_CountInfoLst;
	NhuCounterCheckRsp_v8a0_IEs nonCriticalExtn;
} NhuCounterCheckRsp_r8_IEs;

typedef struct NhuCounterCheckRspcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuCounterCheckRspcriticalExtnscriticalExtnsFuture;

typedef struct NhuCounterCheckRspcriticalExtns
{
	TknU8 choice;
	union {
		NhuCounterCheckRsp_r8_IEs counterCheckRsp_r8;
		NhuCounterCheckRspcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuCounterCheckRspcriticalExtns;

typedef struct NhuCounterCheckRsp
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuCounterCheckRspcriticalExtns criticalExtns;
} NhuCounterCheckRsp;

/* Element ----- NumberOfPreamblesSent-r11 ------- */
typedef TknU32 NhuNumberOfPreamblesSent_r11;

typedef struct NhuMeasResult2EUTRA_r9
{
	TknPres pres;
	NhuARFCN_ValueEUTRA carrierFreq_r9;
	NhuMeasResultLstEUTRA measResultLst_r9;
} NhuMeasResult2EUTRA_r9;

typedef struct NhuMeasResultLst2EUTRA_r9
{
	TknU16 noComp;
	NhuMeasResult2EUTRA_r9 *member;
}NhuMeasResultLst2EUTRA_r9;

typedef struct NhuMeasResult2UTRA_r9
{
	TknPres pres;
	NhuARFCN_ValueUTRA carrierFreq_r9;
	NhuMeasResultLstUTRA measResultLst_r9;
} NhuMeasResult2UTRA_r9;

typedef struct NhuMeasResultLst2UTRA_r9
{
	TknU16 noComp;
	NhuMeasResult2UTRA_r9 *member;
}NhuMeasResultLst2UTRA_r9;

typedef struct NhuMeasResult2CDMA2000_r9
{
	TknPres pres;
	NhuCarrierFreqCDMA2000 carrierFreq_r9;
	NhuMeasResultsCDMA2000 measResultLst_r9;
} NhuMeasResult2CDMA2000_r9;

typedef struct NhuMeasResultLst2CDMA2000_r9
{
	TknU16 noComp;
	NhuMeasResult2CDMA2000_r9 *member;
}NhuMeasResultLst2CDMA2000_r9;

/* Element ----- TimeSinceFailure-r11 ------- */
typedef TknU32 NhuTimeSinceFail_r11;

typedef struct NhuRLF_Report_r9measResultLastServCell_r9
{
	TknPres pres;
	NhuRSRP_Range rsrpResult_r9;
	NhuRSRQ_Range rsrqResult_r9;
} NhuRLF_Report_r9measResultLastServCell_r9;

typedef struct NhuRLF_Report_r9measResultNeighCells_r9
{
	TknPres pres;
	NhuMeasResultLst2EUTRA_r9 measResultLstEUTRA_r9;
	NhuMeasResultLst2UTRA_r9 measResultLstUTRA_r9;
	NhuMeasResultLstGERAN measResultLstGERAN_r9;
	NhuMeasResultLst2CDMA2000_r9 measResultsCDMA2000_r9;
} NhuRLF_Report_r9measResultNeighCells_r9;

typedef struct NhuRLF_Report_r9extaddgrp_1failedPCellId_r10pci_arfcn_r10
{
	TknPres pres;
	NhuPhysCellId physCellId_r10;
	NhuARFCN_ValueEUTRA carrierFreq_r10;
} NhuRLF_Report_r9extaddgrp_1failedPCellId_r10pci_arfcn_r10;

typedef struct NhuRLF_Report_r9extaddgrp_1failedPCellId_r10
{
	TknU8 choice;
	union {
		NhuCellGlobalIdEUTRA cellGlobalId_r10;
		NhuRLF_Report_r9extaddgrp_1failedPCellId_r10pci_arfcn_r10 pci_arfcn_r10;
	} val;
} NhuRLF_Report_r9extaddgrp_1failedPCellId_r10;

/* Element ----- timeConnFailure-r10 ------- */
typedef TknU32 NhuRLF_Report_r9extaddgrp_1timeConnFail_r10;

/* Element ----- connectionFailureType-r10 ------- */
typedef enum enumNhuRLF_Report_r9extaddgrp_1connectionFailTyp_r10
{
	NhuRLF_Report_r9extaddgrp_1connectionFailTyp_r10rlfEnum,
	NhuRLF_Report_r9extaddgrp_1connectionFailTyp_r10hofEnum
} EnumNhuRLF_Report_r9extaddgrp_1connectionFailTyp_r10;
typedef TknU32 NhuRLF_Report_r9extaddgrp_1connectionFailTyp_r10;

typedef struct NhuRLF_Report_r9extaddgrp_2failedPCellId_v1090
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_v9e0 carrierFreq_v1090;
} NhuRLF_Report_r9extaddgrp_2failedPCellId_v1090;

/* Element ----- rlf-Cause-r11 ------- */
typedef enum enumNhuRLF_Report_r9extaddgrp_3basicFields_r11rlf_Cause_r11
{
	NhuRLF_Report_r9extaddgrp_3basicFields_r11rlf_Cause_r11t310_ExpiryEnum,
	NhuRLF_Report_r9extaddgrp_3basicFields_r11rlf_Cause_r11randomAccessProblemEnum,
	NhuRLF_Report_r9extaddgrp_3basicFields_r11rlf_Cause_r11rlc_MaxNumRetxEnum,
	NhuRLF_Report_r9extaddgrp_3basicFields_r11rlf_Cause_r11spare1Enum
} EnumNhuRLF_Report_r9extaddgrp_3basicFields_r11rlf_Cause_r11;
typedef TknU32 NhuRLF_Report_r9extaddgrp_3basicFields_r11rlf_Cause_r11;

typedef struct NhuRLF_Report_r9extaddgrp_3basicFields_r11
{
	TknPres pres;
	NhuC_RNTI c_RNTI_r11;
	NhuRLF_Report_r9extaddgrp_3basicFields_r11rlf_Cause_r11 rlf_Cause_r11;
	NhuTimeSinceFail_r11 timeSinceFail_r11;
} NhuRLF_Report_r9extaddgrp_3basicFields_r11;

typedef struct NhuRLF_Report_r9extaddgrp_3previousUTRA_CellId_r11physCellId_r11
{
	TknU8 choice;
	union {
		NhuPhysCellIdUTRA_FDD fdd_r11;
		NhuPhysCellIdUTRA_TDD tdd_r11;
	} val;
} NhuRLF_Report_r9extaddgrp_3previousUTRA_CellId_r11physCellId_r11;

typedef struct NhuRLF_Report_r9extaddgrp_3previousUTRA_CellId_r11
{
	TknPres pres;
	NhuARFCN_ValueUTRA carrierFreq_r11;
	NhuRLF_Report_r9extaddgrp_3previousUTRA_CellId_r11physCellId_r11 physCellId_r11;
	NhuCellGlobalIdUTRA cellGlobalId_r11;
} NhuRLF_Report_r9extaddgrp_3previousUTRA_CellId_r11;

typedef struct NhuRLF_Report_r9extaddgrp_3selectedUTRA_CellId_r11physCellId_r11
{
	TknU8 choice;
	union {
		NhuPhysCellIdUTRA_FDD fdd_r11;
		NhuPhysCellIdUTRA_TDD tdd_r11;
	} val;
} NhuRLF_Report_r9extaddgrp_3selectedUTRA_CellId_r11physCellId_r11;

typedef struct NhuRLF_Report_r9extaddgrp_3selectedUTRA_CellId_r11
{
	TknPres pres;
	NhuARFCN_ValueUTRA carrierFreq_r11;
	NhuRLF_Report_r9extaddgrp_3selectedUTRA_CellId_r11physCellId_r11 physCellId_r11;
} NhuRLF_Report_r9extaddgrp_3selectedUTRA_CellId_r11;

typedef struct NhuRLF_Report_r9extaddgrp_1
{
	TknPres pres;
	NhuLocInfo_r10 locationInfo_r10;
	NhuRLF_Report_r9extaddgrp_1failedPCellId_r10 failedPCellId_r10;
	NhuCellGlobalIdEUTRA reestablishmentCellId_r10;
	NhuRLF_Report_r9extaddgrp_1timeConnFail_r10 timeConnFail_r10;
	NhuRLF_Report_r9extaddgrp_1connectionFailTyp_r10 connectionFailTyp_r10;
	NhuCellGlobalIdEUTRA previousPCellId_r10;
} NhuRLF_Report_r9extaddgrp_1;

typedef struct NhuRLF_Report_r9extaddgrp_2
{
	TknPres pres;
	NhuRLF_Report_r9extaddgrp_2failedPCellId_v1090 failedPCellId_v1090;
} NhuRLF_Report_r9extaddgrp_2;

typedef struct NhuRLF_Report_r9extaddgrp_3
{
	TknPres pres;
	NhuRLF_Report_r9extaddgrp_3basicFields_r11 basicFields_r11;
	NhuRLF_Report_r9extaddgrp_3previousUTRA_CellId_r11 previousUTRA_CellId_r11;
	NhuRLF_Report_r9extaddgrp_3selectedUTRA_CellId_r11 selectedUTRA_CellId_r11;
} NhuRLF_Report_r9extaddgrp_3;

typedef struct NhuRLF_Report_r9
{
	TknPres pres;
	NhuRLF_Report_r9measResultLastServCell_r9 measResultLastServCell_r9;
	NhuRLF_Report_r9measResultNeighCells_r9 measResultNeighCells_r9;
	NhuRLF_Report_r9extaddgrp_1 extaddgrp_1;
	NhuRLF_Report_r9extaddgrp_2 extaddgrp_2;
	NhuRLF_Report_r9extaddgrp_3 extaddgrp_3;
} NhuRLF_Report_r9;

typedef struct NhuMeasResultLst2GERAN_r10
{
	TknU16 noComp;
	NhuMeasResultLstGERAN *member;
}NhuMeasResultLst2GERAN_r10;

typedef struct NhuMeasResult2EUTRA_v9e0
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_v9e0 carrierFreq_v9e0;
} NhuMeasResult2EUTRA_v9e0;

typedef struct NhuMeasResultLst2EUTRA_v9e0
{
	TknU16 noComp;
	NhuMeasResult2EUTRA_v9e0 *member;
}NhuMeasResultLst2EUTRA_v9e0;

/* Element ----- relativeTimeStamp-r10 ------- */
typedef TknU32 NhuLogMeasInfo_r10relativeTimeStamp_r10;

typedef struct NhuLogMeasInfo_r10measResultServCell_r10
{
	TknPres pres;
	NhuRSRP_Range rsrpResult_r10;
	NhuRSRQ_Range rsrqResult_r10;
} NhuLogMeasInfo_r10measResultServCell_r10;

typedef struct NhuLogMeasInfo_r10measResultNeighCells_r10
{
	TknPres pres;
	NhuMeasResultLst2EUTRA_r9 measResultLstEUTRA_r10;
	NhuMeasResultLst2UTRA_r9 measResultLstUTRA_r10;
	NhuMeasResultLst2GERAN_r10 measResultLstGERAN_r10;
	NhuMeasResultLst2CDMA2000_r9 measResultLstCDMA2000_r10;
} NhuLogMeasInfo_r10measResultNeighCells_r10;

typedef struct NhuLogMeasInfo_r10extaddgrp_1
{
	TknPres pres;
	NhuMeasResultLst2EUTRA_v9e0 measResultLstEUTRA_v1090;
} NhuLogMeasInfo_r10extaddgrp_1;

typedef struct NhuLogMeasInfo_r10
{
	TknPres pres;
	NhuLocInfo_r10 locationInfo_r10;
	NhuLogMeasInfo_r10relativeTimeStamp_r10 relativeTimeStamp_r10;
	NhuCellGlobalIdEUTRA servCellIdentity_r10;
	NhuLogMeasInfo_r10measResultServCell_r10 measResultServCell_r10;
	NhuLogMeasInfo_r10measResultNeighCells_r10 measResultNeighCells_r10;
	NhuLogMeasInfo_r10extaddgrp_1 extaddgrp_1;
} NhuLogMeasInfo_r10;

typedef struct NhuLogMeasInfoLst_r10
{
	TknU16 noComp;
	NhuLogMeasInfo_r10 *member;
}NhuLogMeasInfoLst_r10;

/* Element ---------- traceRecordingSessionRef-r10 ----------- */
typedef TknStrOSXL NhuLogMeasReport_r10traceRecordingSessionRef_r10;
/* Element ---------- tce-Id-r10 ----------- */
typedef TknStrOSXL NhuLogMeasReport_r10tce_Id_r10;
/* Element ----- logMeasAvailable-r10 ------- */
typedef enum enumNhuLogMeasReport_r10logMeasAvailable_r10
{
	NhuLogMeasReport_r10logMeasAvailable_r10trueEnum
} EnumNhuLogMeasReport_r10logMeasAvailable_r10;
typedef TknU32 NhuLogMeasReport_r10logMeasAvailable_r10;

typedef struct NhuLogMeasReport_r10
{
	TknPres pres;
	NhuAbsoluteTimeInfo_r10 absoluteTimeStamp_r10;
	NhuTraceReference_r10 traceReference_r10;
	NhuLogMeasReport_r10traceRecordingSessionRef_r10 traceRecordingSessionRef_r10;
	NhuLogMeasReport_r10tce_Id_r10 tce_Id_r10;
	NhuLogMeasInfoLst_r10 logMeasInfoLst_r10;
	NhuLogMeasReport_r10logMeasAvailable_r10 logMeasAvailable_r10;
} NhuLogMeasReport_r10;

typedef struct NhuConnEstFailReport_r11measResultFailedCell_r11
{
	TknPres pres;
	NhuRSRP_Range rsrpResult_r11;
	NhuRSRQ_Range rsrqResult_r11;
} NhuConnEstFailReport_r11measResultFailedCell_r11;

typedef struct NhuConnEstFailReport_r11measResultNeighCells_r11
{
	TknPres pres;
	NhuMeasResultLst2EUTRA_r9 measResultLstEUTRA_r11;
	NhuMeasResultLst2UTRA_r9 measResultLstUTRA_r11;
	NhuMeasResultLstGERAN measResultLstGERAN_r11;
	NhuMeasResultLst2CDMA2000_r9 measResultsCDMA2000_r11;
} NhuConnEstFailReport_r11measResultNeighCells_r11;

/* Element ----- contentionDetected-r11 ------- */
typedef TknU8 NhuConnEstFailReport_r11contentionDetected_r11;

/* Element ----- maxTxPowerReached-r11 ------- */
typedef TknU8 NhuConnEstFailReport_r11maxTxPowerReached_r11;

typedef struct NhuConnEstFailReport_r11
{
	TknPres pres;
	NhuCellGlobalIdEUTRA failedCellId_r11;
	NhuLocInfo_r10 locationInfo_r11;
	NhuConnEstFailReport_r11measResultFailedCell_r11 measResultFailedCell_r11;
	NhuConnEstFailReport_r11measResultNeighCells_r11 measResultNeighCells_r11;
	NhuNumberOfPreamblesSent_r11 numberOfPreamblesSent_r11;
	NhuConnEstFailReport_r11contentionDetected_r11 contentionDetected_r11;
	NhuConnEstFailReport_r11maxTxPowerReached_r11 maxTxPowerReached_r11;
	NhuTimeSinceFail_r11 timeSinceFail_r11;
	NhuMeasResultLst2EUTRA_v9e0 measResultLstEUTRA_v1130;
} NhuConnEstFailReport_r11;

typedef struct NhuUEInfoRsp_v1130_IEsnonCriticalExtn
{
	TknPres pres;
} NhuUEInfoRsp_v1130_IEsnonCriticalExtn;

typedef struct NhuUEInfoRsp_v1130_IEs
{
	TknPres pres;
	NhuConnEstFailReport_r11 connEstFailReport_r11;
	NhuUEInfoRsp_v1130_IEsnonCriticalExtn nonCriticalExtn;
} NhuUEInfoRsp_v1130_IEs;

typedef struct NhuUEInfoRsp_v1020_IEs
{
	TknPres pres;
	NhuLogMeasReport_r10 logMeasReport_r10;
	NhuUEInfoRsp_v1130_IEs nonCriticalExtn;
} NhuUEInfoRsp_v1020_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuUEInfoRsp_v930_IEslateNonCriticalExtn;
typedef struct NhuUEInfoRsp_v930_IEs
{
	TknPres pres;
	NhuUEInfoRsp_v930_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuUEInfoRsp_v1020_IEs nonCriticalExtn;
} NhuUEInfoRsp_v930_IEs;

/* Element ----- contentionDetected-r9 ------- */
typedef TknU8 NhuUEInfoRsp_r9_IEsrach_Report_r9contentionDetected_r9;

typedef struct NhuUEInfoRsp_r9_IEsrach_Report_r9
{
	TknPres pres;
	NhuNumberOfPreamblesSent_r11 numberOfPreamblesSent_r9;
	NhuUEInfoRsp_r9_IEsrach_Report_r9contentionDetected_r9 contentionDetected_r9;
} NhuUEInfoRsp_r9_IEsrach_Report_r9;

typedef struct NhuUEInfoRsp_r9_IEs
{
	TknPres pres;
	NhuUEInfoRsp_r9_IEsrach_Report_r9 rach_Report_r9;
	NhuRLF_Report_r9 rlf_Report_r9;
	NhuUEInfoRsp_v930_IEs nonCriticalExtn;
} NhuUEInfoRsp_r9_IEs;

typedef struct NhuUEInfoRsp_r9criticalExtnsc1
{
	TknU8 choice;
	union {
		NhuUEInfoRsp_r9_IEs ueInfoRsp_r9;
	} val;
} NhuUEInfoRsp_r9criticalExtnsc1;

typedef struct NhuUEInfoRsp_r9criticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuUEInfoRsp_r9criticalExtnscriticalExtnsFuture;

typedef struct NhuUEInfoRsp_r9criticalExtns
{
	TknU8 choice;
	union {
		NhuUEInfoRsp_r9criticalExtnsc1 c1;
		NhuUEInfoRsp_r9criticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuUEInfoRsp_r9criticalExtns;

typedef struct NhuUEInfoRsp_r9
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuUEInfoRsp_r9criticalExtns criticalExtns;
} NhuUEInfoRsp_r9;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuProximityInd_v930_IEslateNonCriticalExtn;
typedef struct NhuProximityInd_v930_IEsnonCriticalExtn
{
	TknPres pres;
} NhuProximityInd_v930_IEsnonCriticalExtn;

typedef struct NhuProximityInd_v930_IEs
{
	TknPres pres;
	NhuProximityInd_v930_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuProximityInd_v930_IEsnonCriticalExtn nonCriticalExtn;
} NhuProximityInd_v930_IEs;

/* Element ----- type-r9 ------- */
typedef enum enumNhuProximityInd_r9_IEstype_r9
{
	NhuProximityInd_r9_IEstype_r9enteringEnum,
	NhuProximityInd_r9_IEstype_r9leavingEnum
} EnumNhuProximityInd_r9_IEstype_r9;
typedef TknU32 NhuProximityInd_r9_IEstype_r9;

typedef struct NhuProximityInd_r9_IEscarrierFreq_r9
{
	TknU8 choice;
	union {
		NhuARFCN_ValueEUTRA eutra_r9;
		NhuARFCN_ValueUTRA utra_r9;
		NhuARFCN_ValueEUTRA_v9e0 eutra2_v9e0;
	} val;
} NhuProximityInd_r9_IEscarrierFreq_r9;

typedef struct NhuProximityInd_r9_IEs
{
	TknPres pres;
	NhuProximityInd_r9_IEstype_r9 type_r9;
	NhuProximityInd_r9_IEscarrierFreq_r9 carrierFreq_r9;
	NhuProximityInd_v930_IEs nonCriticalExtn;
} NhuProximityInd_r9_IEs;

typedef struct NhuProximityInd_r9criticalExtnsc1
{
	TknU8 choice;
	union {
		NhuProximityInd_r9_IEs proximityInd_r9;
	} val;
} NhuProximityInd_r9criticalExtnsc1;

typedef struct NhuProximityInd_r9criticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuProximityInd_r9criticalExtnscriticalExtnsFuture;

typedef struct NhuProximityInd_r9criticalExtns
{
	TknU8 choice;
	union {
		NhuProximityInd_r9criticalExtnsc1 c1;
		NhuProximityInd_r9criticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuProximityInd_r9criticalExtns;

typedef struct NhuProximityInd_r9
{
	TknPres pres;
	NhuProximityInd_r9criticalExtns criticalExtns;
} NhuProximityInd_r9;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuRNRecfgnCompl_r10_IEslateNonCriticalExtn;
typedef struct NhuRNRecfgnCompl_r10_IEsnonCriticalExtn
{
	TknPres pres;
} NhuRNRecfgnCompl_r10_IEsnonCriticalExtn;

typedef struct NhuRNRecfgnCompl_r10_IEs
{
	TknPres pres;
	NhuRNRecfgnCompl_r10_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuRNRecfgnCompl_r10_IEsnonCriticalExtn nonCriticalExtn;
} NhuRNRecfgnCompl_r10_IEs;

typedef struct NhuRNRecfgnCompl_r10criticalExtnsc1
{
	TknU8 choice;
	union {
		NhuRNRecfgnCompl_r10_IEs rnRecfgnCompl_r10;
	} val;
} NhuRNRecfgnCompl_r10criticalExtnsc1;

typedef struct NhuRNRecfgnCompl_r10criticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuRNRecfgnCompl_r10criticalExtnscriticalExtnsFuture;

typedef struct NhuRNRecfgnCompl_r10criticalExtns
{
	TknU8 choice;
	union {
		NhuRNRecfgnCompl_r10criticalExtnsc1 c1;
		NhuRNRecfgnCompl_r10criticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuRNRecfgnCompl_r10criticalExtns;

typedef struct NhuRNRecfgnCompl_r10
{
	TknPres pres;
	NhuRRC_TrnsxnId rrc_TrnsxnId;
	NhuRNRecfgnCompl_r10criticalExtns criticalExtns;
} NhuRNRecfgnCompl_r10;

/* Element ----- countingResponseService-r10 ------- */
typedef TknU32 NhuCountingRspInfo_r10countingRspService_r10;

typedef struct NhuCountingRspInfo_r10
{
	TknPres pres;
	NhuCountingRspInfo_r10countingRspService_r10 countingRspService_r10;
} NhuCountingRspInfo_r10;

typedef struct NhuCountingRspLst_r10
{
	TknU16 noComp;
	NhuCountingRspInfo_r10 *member;
}NhuCountingRspLst_r10;

/* Element ----- mbsfn-AreaIndex-r10 ------- */
typedef TknU32 NhuMBMSCountingRsp_r10_IEsmbsfn_AreaIdx_r10;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuMBMSCountingRsp_r10_IEslateNonCriticalExtn;
typedef struct NhuMBMSCountingRsp_r10_IEsnonCriticalExtn
{
	TknPres pres;
} NhuMBMSCountingRsp_r10_IEsnonCriticalExtn;

typedef struct NhuMBMSCountingRsp_r10_IEs
{
	TknPres pres;
	NhuMBMSCountingRsp_r10_IEsmbsfn_AreaIdx_r10 mbsfn_AreaIdx_r10;
	NhuCountingRspLst_r10 countingRspLst_r10;
	NhuMBMSCountingRsp_r10_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuMBMSCountingRsp_r10_IEsnonCriticalExtn nonCriticalExtn;
} NhuMBMSCountingRsp_r10_IEs;

typedef struct NhuMBMSCountingRsp_r10criticalExtnsc1
{
	TknU8 choice;
	union {
		NhuMBMSCountingRsp_r10_IEs countingRsp_r10;
	} val;
} NhuMBMSCountingRsp_r10criticalExtnsc1;

typedef struct NhuMBMSCountingRsp_r10criticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuMBMSCountingRsp_r10criticalExtnscriticalExtnsFuture;

typedef struct NhuMBMSCountingRsp_r10criticalExtns
{
	TknU8 choice;
	union {
		NhuMBMSCountingRsp_r10criticalExtnsc1 c1;
		NhuMBMSCountingRsp_r10criticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuMBMSCountingRsp_r10criticalExtns;

typedef struct NhuMBMSCountingRsp_r10
{
	TknPres pres;
	NhuMBMSCountingRsp_r10criticalExtns criticalExtns;
} NhuMBMSCountingRsp_r10;

/* Element ----- measPRS-Offset-r10 ------- */
typedef TknU32 NhuRSTD_InterFreqInfo_r10measPRS_Offset_r10;

typedef struct NhuRSTD_InterFreqInfo_r10extaddgrp_1
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_v9e0 carrierFreq_v1090;
} NhuRSTD_InterFreqInfo_r10extaddgrp_1;

typedef struct NhuRSTD_InterFreqInfo_r10
{
	TknPres pres;
	NhuARFCN_ValueEUTRA carrierFreq_r10;
	NhuRSTD_InterFreqInfo_r10measPRS_Offset_r10 measPRS_Offset_r10;
	NhuRSTD_InterFreqInfo_r10extaddgrp_1 extaddgrp_1;
} NhuRSTD_InterFreqInfo_r10;

typedef struct NhuRSTD_InterFreqInfoLst_r10
{
	TknU16 noComp;
	NhuRSTD_InterFreqInfo_r10 *member;
}NhuRSTD_InterFreqInfoLst_r10;

typedef struct NhuInterFreqRSTDMeasurementInd_r10_IEsrstd_InterFreqInd_r10start
{
	TknPres pres;
	NhuRSTD_InterFreqInfoLst_r10 rstd_InterFreqInfoLst_r10;
} NhuInterFreqRSTDMeasurementInd_r10_IEsrstd_InterFreqInd_r10start;

typedef struct NhuInterFreqRSTDMeasurementInd_r10_IEsrstd_InterFreqInd_r10
{
	TknU8 choice;
	union {
		NhuInterFreqRSTDMeasurementInd_r10_IEsrstd_InterFreqInd_r10start start;
	} val;
} NhuInterFreqRSTDMeasurementInd_r10_IEsrstd_InterFreqInd_r10;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuInterFreqRSTDMeasurementInd_r10_IEslateNonCriticalExtn;
typedef struct NhuInterFreqRSTDMeasurementInd_r10_IEsnonCriticalExtn
{
	TknPres pres;
} NhuInterFreqRSTDMeasurementInd_r10_IEsnonCriticalExtn;

typedef struct NhuInterFreqRSTDMeasurementInd_r10_IEs
{
	TknPres pres;
	NhuInterFreqRSTDMeasurementInd_r10_IEsrstd_InterFreqInd_r10 rstd_InterFreqInd_r10;
	NhuInterFreqRSTDMeasurementInd_r10_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuInterFreqRSTDMeasurementInd_r10_IEsnonCriticalExtn nonCriticalExtn;
} NhuInterFreqRSTDMeasurementInd_r10_IEs;

typedef struct NhuInterFreqRSTDMeasurementInd_r10criticalExtnsc1
{
	TknU8 choice;
	union {
		NhuInterFreqRSTDMeasurementInd_r10_IEs interFreqRSTDMeasurementInd_r10;
	} val;
} NhuInterFreqRSTDMeasurementInd_r10criticalExtnsc1;

typedef struct NhuInterFreqRSTDMeasurementInd_r10criticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuInterFreqRSTDMeasurementInd_r10criticalExtnscriticalExtnsFuture;

typedef struct NhuInterFreqRSTDMeasurementInd_r10criticalExtns
{
	TknU8 choice;
	union {
		NhuInterFreqRSTDMeasurementInd_r10criticalExtnsc1 c1;
		NhuInterFreqRSTDMeasurementInd_r10criticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuInterFreqRSTDMeasurementInd_r10criticalExtns;

typedef struct NhuInterFreqRSTDMeasurementInd_r10
{
	TknPres pres;
	NhuInterFreqRSTDMeasurementInd_r10criticalExtns criticalExtns;
} NhuInterFreqRSTDMeasurementInd_r10;

/* Element ----- powerPrefIndication-r11 ------- */
typedef enum enumNhuUEAssistanceInfo_r11_IEspowerPrefInd_r11
{
	NhuUEAssistanceInfo_r11_IEspowerPrefInd_r11normalEnum,
	NhuUEAssistanceInfo_r11_IEspowerPrefInd_r11lowPowerConsumptionEnum
} EnumNhuUEAssistanceInfo_r11_IEspowerPrefInd_r11;
typedef TknU32 NhuUEAssistanceInfo_r11_IEspowerPrefInd_r11;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuUEAssistanceInfo_r11_IEslateNonCriticalExtn;
typedef struct NhuUEAssistanceInfo_r11_IEsnonCriticalExtn
{
	TknPres pres;
} NhuUEAssistanceInfo_r11_IEsnonCriticalExtn;

typedef struct NhuUEAssistanceInfo_r11_IEs
{
	TknPres pres;
	NhuUEAssistanceInfo_r11_IEspowerPrefInd_r11 powerPrefInd_r11;
	NhuUEAssistanceInfo_r11_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuUEAssistanceInfo_r11_IEsnonCriticalExtn nonCriticalExtn;
} NhuUEAssistanceInfo_r11_IEs;

typedef struct NhuUEAssistanceInfo_r11criticalExtnsc1
{
	TknU8 choice;
	union {
		NhuUEAssistanceInfo_r11_IEs ueAssistanceInfo_r11;
	} val;
} NhuUEAssistanceInfo_r11criticalExtnsc1;

typedef struct NhuUEAssistanceInfo_r11criticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuUEAssistanceInfo_r11criticalExtnscriticalExtnsFuture;

typedef struct NhuUEAssistanceInfo_r11criticalExtns
{
	TknU8 choice;
	union {
		NhuUEAssistanceInfo_r11criticalExtnsc1 c1;
		NhuUEAssistanceInfo_r11criticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuUEAssistanceInfo_r11criticalExtns;

typedef struct NhuUEAssistanceInfo_r11
{
	TknPres pres;
	NhuUEAssistanceInfo_r11criticalExtns criticalExtns;
} NhuUEAssistanceInfo_r11;

/* Element ----- interferenceDirection-r11 ------- */
typedef enum enumNhuAffectedCarrierFreq_r11interferenceDirection_r11
{
	NhuAffectedCarrierFreq_r11interferenceDirection_r11eutraEnum,
	NhuAffectedCarrierFreq_r11interferenceDirection_r11otherEnum,
	NhuAffectedCarrierFreq_r11interferenceDirection_r11bothEnum,
	NhuAffectedCarrierFreq_r11interferenceDirection_r11spareEnum
} EnumNhuAffectedCarrierFreq_r11interferenceDirection_r11;
typedef TknU32 NhuAffectedCarrierFreq_r11interferenceDirection_r11;

typedef struct NhuAffectedCarrierFreq_r11
{
	TknPres pres;
	NhuMeasObjectId carrierFreq_r11;
	NhuAffectedCarrierFreq_r11interferenceDirection_r11 interferenceDirection_r11;
} NhuAffectedCarrierFreq_r11;

typedef struct NhuAffectedCarrierFreqLst_r11
{
	TknU16 noComp;
	NhuAffectedCarrierFreq_r11 *member;
}NhuAffectedCarrierFreqLst_r11;

/* Element ---------- subframePatternFDD-r11 ----------- */
typedef TknStrBSXL NhuIDC_SubfrmPattern_r11subframePatternFDD_r11;
/* Element ---------- subframeConfig0-r11 ----------- */
typedef TknStrBSXL NhuIDC_SubfrmPattern_r11subframePatternTDD_r11subframeConfig0_r11;
/* Element ---------- subframeConfig1-5-r11 ----------- */
typedef TknStrBSXL NhuIDC_SubfrmPattern_r11subframePatternTDD_r11subframeConfig1_5_r11;
/* Element ---------- subframeConfig6-r11 ----------- */
typedef TknStrBSXL NhuIDC_SubfrmPattern_r11subframePatternTDD_r11subframeConfig6_r11;
typedef struct NhuIDC_SubfrmPattern_r11subframePatternTDD_r11
{
	TknU8 choice;
	union {
		NhuIDC_SubfrmPattern_r11subframePatternTDD_r11subframeConfig0_r11 subframeConfig0_r11;
		NhuIDC_SubfrmPattern_r11subframePatternTDD_r11subframeConfig1_5_r11 subframeConfig1_5_r11;
		NhuIDC_SubfrmPattern_r11subframePatternTDD_r11subframeConfig6_r11 subframeConfig6_r11;
	} val;
} NhuIDC_SubfrmPattern_r11subframePatternTDD_r11;

typedef struct NhuIDC_SubfrmPattern_r11
{
	TknU8 choice;
	union {
		NhuIDC_SubfrmPattern_r11subframePatternFDD_r11 subframePatternFDD_r11;
		NhuIDC_SubfrmPattern_r11subframePatternTDD_r11 subframePatternTDD_r11;
	} val;
} NhuIDC_SubfrmPattern_r11;

typedef struct NhuIDC_SubfrmPatternLst_r11
{
	TknU16 noComp;
	NhuIDC_SubfrmPattern_r11 *member;
}NhuIDC_SubfrmPatternLst_r11;

/* Element ----- drx-CycleLength-r11 ------- */
typedef enum enumNhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_CycleLength_r11
{
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_CycleLength_r11sf40Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_CycleLength_r11sf64Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_CycleLength_r11sf80Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_CycleLength_r11sf128Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_CycleLength_r11sf160Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_CycleLength_r11sf256Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_CycleLength_r11spare2Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_CycleLength_r11spare1Enum
} EnumNhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_CycleLength_r11;
typedef TknU32 NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_CycleLength_r11;

/* Element ----- drx-Offset-r11 ------- */
typedef TknU32 NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_Offset_r11;

/* Element ----- drx-ActiveTime-r11 ------- */
typedef enum enumNhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_ActiveTime_r11
{
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_ActiveTime_r11sf20Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_ActiveTime_r11sf30Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_ActiveTime_r11sf40Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_ActiveTime_r11sf60Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_ActiveTime_r11sf80Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_ActiveTime_r11sf100Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_ActiveTime_r11spare2Enum,
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_ActiveTime_r11spare1Enum
} EnumNhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_ActiveTime_r11;
typedef TknU32 NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_ActiveTime_r11;

typedef struct NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11
{
	TknPres pres;
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_CycleLength_r11 drx_CycleLength_r11;
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_Offset_r11 drx_Offset_r11;
	NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11drx_ActiveTime_r11 drx_ActiveTime_r11;
} NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11;

typedef struct NhuTDM_AssistanceInfo_r11
{
	TknU8 choice;
	union {
		NhuTDM_AssistanceInfo_r11drx_AssistanceInfo_r11 drx_AssistanceInfo_r11;
		NhuIDC_SubfrmPatternLst_r11 idc_SubfrmPatternLst_r11;
	} val;
} NhuTDM_AssistanceInfo_r11;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuInDeviceCoexInd_r11_IEslateNonCriticalExtn;
typedef struct NhuInDeviceCoexInd_r11_IEsnonCriticalExtn
{
	TknPres pres;
} NhuInDeviceCoexInd_r11_IEsnonCriticalExtn;

typedef struct NhuInDeviceCoexInd_r11_IEs
{
	TknPres pres;
	NhuAffectedCarrierFreqLst_r11 affectedCarrierFreqLst_r11;
	NhuTDM_AssistanceInfo_r11 tdm_AssistanceInfo_r11;
	NhuInDeviceCoexInd_r11_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuInDeviceCoexInd_r11_IEsnonCriticalExtn nonCriticalExtn;
} NhuInDeviceCoexInd_r11_IEs;

typedef struct NhuInDeviceCoexInd_r11criticalExtnsc1
{
	TknU8 choice;
	union {
		NhuInDeviceCoexInd_r11_IEs inDeviceCoexInd_r11;
	} val;
} NhuInDeviceCoexInd_r11criticalExtnsc1;

typedef struct NhuInDeviceCoexInd_r11criticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuInDeviceCoexInd_r11criticalExtnscriticalExtnsFuture;

typedef struct NhuInDeviceCoexInd_r11criticalExtns
{
	TknU8 choice;
	union {
		NhuInDeviceCoexInd_r11criticalExtnsc1 c1;
		NhuInDeviceCoexInd_r11criticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuInDeviceCoexInd_r11criticalExtns;

typedef struct NhuInDeviceCoexInd_r11
{
	TknPres pres;
	NhuInDeviceCoexInd_r11criticalExtns criticalExtns;
} NhuInDeviceCoexInd_r11;

typedef struct NhuCarrierFreqLstMBMS_r11
{
	TknU16 noComp;
	NhuARFCN_ValueEUTRA_r9 *member;
}NhuCarrierFreqLstMBMS_r11;

/* Element ----- mbms-Priority-r11 ------- */
typedef enum enumNhuMBMSInterestInd_r11_IEsmbms_Priority_r11
{
	NhuMBMSInterestInd_r11_IEsmbms_Priority_r11trueEnum
} EnumNhuMBMSInterestInd_r11_IEsmbms_Priority_r11;
typedef TknU32 NhuMBMSInterestInd_r11_IEsmbms_Priority_r11;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuMBMSInterestInd_r11_IEslateNonCriticalExtn;
typedef struct NhuMBMSInterestInd_r11_IEsnonCriticalExtn
{
	TknPres pres;
} NhuMBMSInterestInd_r11_IEsnonCriticalExtn;

typedef struct NhuMBMSInterestInd_r11_IEs
{
	TknPres pres;
	NhuCarrierFreqLstMBMS_r11 mbms_FreqLst_r11;
	NhuMBMSInterestInd_r11_IEsmbms_Priority_r11 mbms_Priority_r11;
	NhuMBMSInterestInd_r11_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuMBMSInterestInd_r11_IEsnonCriticalExtn nonCriticalExtn;
} NhuMBMSInterestInd_r11_IEs;

typedef struct NhuMBMSInterestInd_r11criticalExtnsc1
{
	TknU8 choice;
	union {
		NhuMBMSInterestInd_r11_IEs interestInd_r11;
	} val;
} NhuMBMSInterestInd_r11criticalExtnsc1;

typedef struct NhuMBMSInterestInd_r11criticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuMBMSInterestInd_r11criticalExtnscriticalExtnsFuture;

typedef struct NhuMBMSInterestInd_r11criticalExtns
{
	TknU8 choice;
	union {
		NhuMBMSInterestInd_r11criticalExtnsc1 c1;
		NhuMBMSInterestInd_r11criticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuMBMSInterestInd_r11criticalExtns;

typedef struct NhuMBMSInterestInd_r11
{
	TknPres pres;
	NhuMBMSInterestInd_r11criticalExtns criticalExtns;
} NhuMBMSInterestInd_r11;

typedef struct NhuUL_DCCH_MsgTypc1
{
	TknU8 choice;
	union {
		NhuCSFBParamsRqstCDMA2000 csfbParamsRqstCDMA2000;
		NhuMeasurementReport measurementReport;
		NhuRRCConRecfgnCompl rrcConRecfgnCompl;
		NhuRRCConReestbCompl rrcConReestbCompl;
		NhuRRCConSetupCompl rrcConSetupCompl;
		NhuSecModeCompl securityModeCompl;
		NhuSecModeFail securityModeFail;
		NhuUECapInfo ueCapInfo;
		NhuULHovrPrepTfr ulHovrPrepTfr;
		NhuULInfoTfr ulInfoTfr;
		NhuCounterCheckRsp counterCheckRsp;
		NhuUEInfoRsp_r9 ueInfoRsp_r9;
		NhuProximityInd_r9 proximityInd_r9;
		NhuRNRecfgnCompl_r10 rnRecfgnCompl_r10;
		NhuMBMSCountingRsp_r10 mbmsCountingRsp_r10;
		NhuInterFreqRSTDMeasurementInd_r10 interFreqRSTDMeasurementInd_r10;
	} val;
} NhuUL_DCCH_MsgTypc1;

typedef struct NhuUL_DCCH_MsgTypmessageClassExtnc2
{
	TknU8 choice;
	union {
		NhuUEAssistanceInfo_r11 ueAssistanceInfo_r11;
		NhuInDeviceCoexInd_r11 inDeviceCoexInd_r11;
		NhuMBMSInterestInd_r11 mbmsInterestInd_r11;
	} val;
} NhuUL_DCCH_MsgTypmessageClassExtnc2;

typedef struct NhuUL_DCCH_MsgTypmessageClassExtnmessageClassExtnFuture_r11
{
	TknPres pres;
} NhuUL_DCCH_MsgTypmessageClassExtnmessageClassExtnFuture_r11;

typedef struct NhuUL_DCCH_MsgTypmessageClassExtn
{
	TknU8 choice;
	union {
		NhuUL_DCCH_MsgTypmessageClassExtnc2 c2;
		NhuUL_DCCH_MsgTypmessageClassExtnmessageClassExtnFuture_r11 messageClassExtnFuture_r11;
	} val;
} NhuUL_DCCH_MsgTypmessageClassExtn;

typedef struct NhuUL_DCCH_MsgTyp
{
	TknU8 choice;
	union {
		NhuUL_DCCH_MsgTypc1 c1;
		NhuUL_DCCH_MsgTypmessageClassExtn messageClassExtn;
	} val;
} NhuUL_DCCH_MsgTyp;

typedef struct NhuUL_DCCH_Msg
{
	TknPres pres;
	NhuUL_DCCH_MsgTyp message;
} NhuUL_DCCH_Msg;

typedef struct NhuRedirectedCarrierInfo_v9e0
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_v9e0 eutra_v9e0;
} NhuRedirectedCarrierInfo_v9e0;

typedef struct NhuFreqPriorityEUTRA_v9e0
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_v9e0 carrierFreq_v9e0;
} NhuFreqPriorityEUTRA_v9e0;

typedef struct NhuIdleModeMobilityCntrlInfo_v9e0freqPriorityLstEUTRA_v9e0
{
	TknU16 noComp;
	NhuFreqPriorityEUTRA_v9e0 *member;
}NhuIdleModeMobilityCntrlInfo_v9e0freqPriorityLstEUTRA_v9e0;

typedef struct NhuIdleModeMobilityCntrlInfo_v9e0
{
	TknPres pres;
	NhuIdleModeMobilityCntrlInfo_v9e0freqPriorityLstEUTRA_v9e0 freqPriorityLstEUTRA_v9e0;
} NhuIdleModeMobilityCntrlInfo_v9e0;

typedef struct NhuRRCConRls_v9e0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuRRCConRls_v9e0_IEsnonCriticalExtn;

typedef struct NhuRRCConRls_v9e0_IEs
{
	TknPres pres;
	NhuRedirectedCarrierInfo_v9e0 redirectedCarrierInfo_v9e0;
	NhuIdleModeMobilityCntrlInfo_v9e0 idleModeMobilityCntrlInfo_v9e0;
	NhuRRCConRls_v9e0_IEsnonCriticalExtn nonCriticalExtn;
} NhuRRCConRls_v9e0_IEs;

typedef struct NhuMultiBandInfoLst
{
	TknU16 noComp;
	NhuFreqBandIndicator *member;
}NhuMultiBandInfoLst;

/* Element ----- FreqBandIndicator-v9e0 ------- */
typedef TknU32 NhuFreqBandIndicator_v9e0;

typedef struct NhuMultiBandInfo_v9e0
{
	TknPres pres;
	NhuFreqBandIndicator_v9e0 freqBandIndicator_v9e0;
} NhuMultiBandInfo_v9e0;

typedef struct NhuMultiBandInfoLst_v9e0
{
	TknU16 noComp;
	NhuMultiBandInfo_v9e0 *member;
}NhuMultiBandInfoLst_v9e0;

typedef struct NhuSysInfoBlockTyp1_v9e0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuSysInfoBlockTyp1_v9e0_IEsnonCriticalExtn;

typedef struct NhuSysInfoBlockTyp1_v9e0_IEs
{
	TknPres pres;
	NhuFreqBandIndicator_v9e0 freqBandIndicator_v9e0;
	NhuMultiBandInfoLst_v9e0 multiBandInfoLst_v9e0;
	NhuSysInfoBlockTyp1_v9e0_IEsnonCriticalExtn nonCriticalExtn;
} NhuSysInfoBlockTyp1_v9e0_IEs;

typedef struct NhuSysInfoBlockTyp1_v8h0_IEs
{
	TknPres pres;
	NhuMultiBandInfoLst multiBandInfoLst;
	NhuSysInfoBlockTyp1_v9e0_IEs nonCriticalExtn;
} NhuSysInfoBlockTyp1_v8h0_IEs;

typedef struct NhuRLF_Report_v9e0
{
	TknPres pres;
	NhuMeasResultLst2EUTRA_v9e0 measResultLstEUTRA_v9e0;
} NhuRLF_Report_v9e0;

typedef struct NhuUEInfoRsp_v9e0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuUEInfoRsp_v9e0_IEsnonCriticalExtn;

typedef struct NhuUEInfoRsp_v9e0_IEs
{
	TknPres pres;
	NhuRLF_Report_v9e0 rlf_Report_v9e0;
	NhuUEInfoRsp_v9e0_IEsnonCriticalExtn nonCriticalExtn;
} NhuUEInfoRsp_v9e0_IEs;

typedef struct NhuSysInfoBlockTyp2_v9e0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuSysInfoBlockTyp2_v9e0_IEsnonCriticalExtn;

typedef struct NhuSysInfoBlockTyp2_v9e0_IEs
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_v9e0 ul_CarrierFreq_v9e0;
	NhuSysInfoBlockTyp2_v9e0_IEsnonCriticalExtn nonCriticalExtn;
} NhuSysInfoBlockTyp2_v9e0_IEs;

typedef struct NhuSysInfoBlockTyp2_v8h0_IEsmultiBandInfoLst
{
	TknU16 noComp;
	NhuAdditionalSpectrumEmission *member;
}NhuSysInfoBlockTyp2_v8h0_IEsmultiBandInfoLst;

typedef struct NhuSysInfoBlockTyp2_v8h0_IEs
{
	TknPres pres;
	NhuSysInfoBlockTyp2_v8h0_IEsmultiBandInfoLst multiBandInfoLst;
	NhuSysInfoBlockTyp2_v9e0_IEs nonCriticalExtn;
} NhuSysInfoBlockTyp2_v8h0_IEs;

typedef struct NhuInterFreqCarrierFreqInfo_v8h0
{
	TknPres pres;
	NhuMultiBandInfoLst multiBandInfoLst;
} NhuInterFreqCarrierFreqInfo_v8h0;

typedef struct NhuInterFreqCarrierFreqInfo_v9e0
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_v9e0 dl_CarrierFreq_v9e0;
	NhuMultiBandInfoLst_v9e0 multiBandInfoLst_v9e0;
} NhuInterFreqCarrierFreqInfo_v9e0;

typedef struct NhuSysInfoBlockTyp5_v9e0_IEsinterFreqCarrierFreqLst_v9e0
{
	TknU16 noComp;
	NhuInterFreqCarrierFreqInfo_v9e0 *member;
}NhuSysInfoBlockTyp5_v9e0_IEsinterFreqCarrierFreqLst_v9e0;

typedef struct NhuSysInfoBlockTyp5_v9e0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuSysInfoBlockTyp5_v9e0_IEsnonCriticalExtn;

typedef struct NhuSysInfoBlockTyp5_v9e0_IEs
{
	TknPres pres;
	NhuSysInfoBlockTyp5_v9e0_IEsinterFreqCarrierFreqLst_v9e0 interFreqCarrierFreqLst_v9e0;
	NhuSysInfoBlockTyp5_v9e0_IEsnonCriticalExtn nonCriticalExtn;
} NhuSysInfoBlockTyp5_v9e0_IEs;

typedef struct NhuSysInfoBlockTyp5_v8h0_IEsinterFreqCarrierFreqLst_v8h0
{
	TknU16 noComp;
	NhuInterFreqCarrierFreqInfo_v8h0 *member;
}NhuSysInfoBlockTyp5_v8h0_IEsinterFreqCarrierFreqLst_v8h0;

typedef struct NhuSysInfoBlockTyp5_v8h0_IEs
{
	TknPres pres;
	NhuSysInfoBlockTyp5_v8h0_IEsinterFreqCarrierFreqLst_v8h0 interFreqCarrierFreqLst_v8h0;
	NhuSysInfoBlockTyp5_v9e0_IEs nonCriticalExtn;
} NhuSysInfoBlockTyp5_v8h0_IEs;

/* Element ----- FreqBandIndicator-UTRA-FDD ------- */
typedef TknU32 NhuFreqBandIndicator_UTRA_FDD;

typedef struct NhuCarrierFreqInfoUTRA_FDD_v8h0multiBandInfoLst
{
	TknU16 noComp;
	NhuFreqBandIndicator_UTRA_FDD *member;
}NhuCarrierFreqInfoUTRA_FDD_v8h0multiBandInfoLst;

typedef struct NhuCarrierFreqInfoUTRA_FDD_v8h0
{
	TknPres pres;
	NhuCarrierFreqInfoUTRA_FDD_v8h0multiBandInfoLst multiBandInfoLst;
} NhuCarrierFreqInfoUTRA_FDD_v8h0;

typedef struct NhuSysInfoBlockTyp6_v8h0_IEscarrierFreqLstUTRA_FDD_v8h0
{
	TknU16 noComp;
	NhuCarrierFreqInfoUTRA_FDD_v8h0 *member;
}NhuSysInfoBlockTyp6_v8h0_IEscarrierFreqLstUTRA_FDD_v8h0;

typedef struct NhuSysInfoBlockTyp6_v8h0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuSysInfoBlockTyp6_v8h0_IEsnonCriticalExtn;

typedef struct NhuSysInfoBlockTyp6_v8h0_IEs
{
	TknPres pres;
	NhuSysInfoBlockTyp6_v8h0_IEscarrierFreqLstUTRA_FDD_v8h0 carrierFreqLstUTRA_FDD_v8h0;
	NhuSysInfoBlockTyp6_v8h0_IEsnonCriticalExtn nonCriticalExtn;
} NhuSysInfoBlockTyp6_v8h0_IEs;

/* Element ----- AccessStratumRelease ------- */
typedef enum enumNhuAccessStratumRls
{
	NhuAccessStratumRlsrel8Enum,
	NhuAccessStratumRlsrel9Enum,
	NhuAccessStratumRlsrel10Enum,
	NhuAccessStratumRlsrel11Enum,
	NhuAccessStratumRlsspare4Enum,
	NhuAccessStratumRlsspare3Enum,
	NhuAccessStratumRlsspare2Enum,
	NhuAccessStratumRlsspare1Enum
} EnumNhuAccessStratumRls;
typedef TknU32 NhuAccessStratumRls;

/* Element ----- profile0x0001 ------- */
typedef TknU8 NhuPDCP_ParamssupportedROHC_Profilesprofile0x0001;

/* Element ----- profile0x0002 ------- */
typedef TknU8 NhuPDCP_ParamssupportedROHC_Profilesprofile0x0002;

/* Element ----- profile0x0003 ------- */
typedef TknU8 NhuPDCP_ParamssupportedROHC_Profilesprofile0x0003;

/* Element ----- profile0x0004 ------- */
typedef TknU8 NhuPDCP_ParamssupportedROHC_Profilesprofile0x0004;

/* Element ----- profile0x0006 ------- */
typedef TknU8 NhuPDCP_ParamssupportedROHC_Profilesprofile0x0006;

/* Element ----- profile0x0101 ------- */
typedef TknU8 NhuPDCP_ParamssupportedROHC_Profilesprofile0x0101;

/* Element ----- profile0x0102 ------- */
typedef TknU8 NhuPDCP_ParamssupportedROHC_Profilesprofile0x0102;

/* Element ----- profile0x0103 ------- */
typedef TknU8 NhuPDCP_ParamssupportedROHC_Profilesprofile0x0103;

/* Element ----- profile0x0104 ------- */
typedef TknU8 NhuPDCP_ParamssupportedROHC_Profilesprofile0x0104;

typedef struct NhuPDCP_ParamssupportedROHC_Profiles
{
	TknPres pres;
	NhuPDCP_ParamssupportedROHC_Profilesprofile0x0001 profile0x0001;
	NhuPDCP_ParamssupportedROHC_Profilesprofile0x0002 profile0x0002;
	NhuPDCP_ParamssupportedROHC_Profilesprofile0x0003 profile0x0003;
	NhuPDCP_ParamssupportedROHC_Profilesprofile0x0004 profile0x0004;
	NhuPDCP_ParamssupportedROHC_Profilesprofile0x0006 profile0x0006;
	NhuPDCP_ParamssupportedROHC_Profilesprofile0x0101 profile0x0101;
	NhuPDCP_ParamssupportedROHC_Profilesprofile0x0102 profile0x0102;
	NhuPDCP_ParamssupportedROHC_Profilesprofile0x0103 profile0x0103;
	NhuPDCP_ParamssupportedROHC_Profilesprofile0x0104 profile0x0104;
} NhuPDCP_ParamssupportedROHC_Profiles;

/* Element ----- maxNumberROHC-ContextSessions ------- */
typedef enum enumNhuPDCP_ParamsmaxNumberROHC_CtxtSessions
{
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs2Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs4Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs8Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs12Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs16Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs24Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs32Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs48Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs64Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs128Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs256Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs512Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs1024Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs16384Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionsspare2Enum,
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessionsspare1Enum
} EnumNhuPDCP_ParamsmaxNumberROHC_CtxtSessions;
typedef TknU32 NhuPDCP_ParamsmaxNumberROHC_CtxtSessions;

typedef struct NhuPDCP_Params
{
	TknPres pres;
	NhuPDCP_ParamssupportedROHC_Profiles supportedROHC_Profiles;
	NhuPDCP_ParamsmaxNumberROHC_CtxtSessions maxNumberROHC_CtxtSessions;	/* DEFAULT 0 */ 
} NhuPDCP_Params;

/* Element ----- ue-TxAntennaSelectionSupported ------- */
typedef TknU8 NhuPhyLyrParamsue_TxAntennaSelectionSupp;

/* Element ----- ue-SpecificRefSigsSupported ------- */
typedef TknU8 NhuPhyLyrParamsue_SpecificRefSigsSupp;

typedef struct NhuPhyLyrParams
{
	TknPres pres;
	NhuPhyLyrParamsue_TxAntennaSelectionSupp ue_TxAntennaSelectionSupp;
	NhuPhyLyrParamsue_SpecificRefSigsSupp ue_SpecificRefSigsSupp;
} NhuPhyLyrParams;

/* Element ----- halfDuplex ------- */
typedef TknU8 NhuSuppBandEUTRAhalfDuplex;

typedef struct NhuSuppBandEUTRA
{
	TknPres pres;
	NhuFreqBandIndicator bandEUTRA;
	NhuSuppBandEUTRAhalfDuplex halfDuplex;
} NhuSuppBandEUTRA;

typedef struct NhuSuppBandLstEUTRA
{
	TknU16 noComp;
	NhuSuppBandEUTRA *member;
}NhuSuppBandLstEUTRA;

typedef struct NhuRF_Params
{
	TknPres pres;
	NhuSuppBandLstEUTRA supportedBandLstEUTRA;
} NhuRF_Params;

/* Element ----- interFreqNeedForGaps ------- */
typedef TknU8 NhuInterFreqBandInfointerFreqNeedForGaps;

typedef struct NhuInterFreqBandInfo
{
	TknPres pres;
	NhuInterFreqBandInfointerFreqNeedForGaps interFreqNeedForGaps;
} NhuInterFreqBandInfo;

typedef struct NhuInterFreqBandLst
{
	TknU16 noComp;
	NhuInterFreqBandInfo *member;
}NhuInterFreqBandLst;

/* Element ----- interRAT-NeedForGaps ------- */
typedef TknU8 NhuInterRAT_BandInfointerRAT_NeedForGaps;

typedef struct NhuInterRAT_BandInfo
{
	TknPres pres;
	NhuInterRAT_BandInfointerRAT_NeedForGaps interRAT_NeedForGaps;
} NhuInterRAT_BandInfo;

typedef struct NhuInterRAT_BandLst
{
	TknU16 noComp;
	NhuInterRAT_BandInfo *member;
}NhuInterRAT_BandLst;

typedef struct NhuBandInfoEUTRA
{
	TknPres pres;
	NhuInterFreqBandLst interFreqBandLst;
	NhuInterRAT_BandLst interRAT_BandLst;
} NhuBandInfoEUTRA;

typedef struct NhuBandLstEUTRA
{
	TknU16 noComp;
	NhuBandInfoEUTRA *member;
}NhuBandLstEUTRA;

typedef struct NhuMeasParams
{
	TknPres pres;
	NhuBandLstEUTRA bandLstEUTRA;
} NhuMeasParams;

/* Element ----- SupportedBandUTRA-FDD ------- */
typedef enum enumNhuSuppBandUTRA_FDD
{
	NhuSuppBandUTRA_FDDbandIEnum,
	NhuSuppBandUTRA_FDDbandIIEnum,
	NhuSuppBandUTRA_FDDbandIIIEnum,
	NhuSuppBandUTRA_FDDbandIVEnum,
	NhuSuppBandUTRA_FDDbandVEnum,
	NhuSuppBandUTRA_FDDbandVIEnum,
	NhuSuppBandUTRA_FDDbandVIIEnum,
	NhuSuppBandUTRA_FDDbandVIIIEnum,
	NhuSuppBandUTRA_FDDbandIXEnum,
	NhuSuppBandUTRA_FDDbandXEnum,
	NhuSuppBandUTRA_FDDbandXIEnum,
	NhuSuppBandUTRA_FDDbandXIIEnum,
	NhuSuppBandUTRA_FDDbandXIIIEnum,
	NhuSuppBandUTRA_FDDbandXIVEnum,
	NhuSuppBandUTRA_FDDbandXVEnum,
	NhuSuppBandUTRA_FDDbandXVIEnum,
	NhuSuppBandUTRA_FDDbandXVII_8a0Enum,
	NhuSuppBandUTRA_FDDbandXVIII_8a0Enum,
	NhuSuppBandUTRA_FDDbandXIX_8a0Enum,
	NhuSuppBandUTRA_FDDbandXX_8a0Enum,
	NhuSuppBandUTRA_FDDbandXXI_8a0Enum,
	NhuSuppBandUTRA_FDDbandXXII_8a0Enum,
	NhuSuppBandUTRA_FDDbandXXIII_8a0Enum,
	NhuSuppBandUTRA_FDDbandXXIV_8a0Enum,
	NhuSuppBandUTRA_FDDbandXXV_8a0Enum,
	NhuSuppBandUTRA_FDDbandXXVI_8a0Enum,
	NhuSuppBandUTRA_FDDbandXXVII_8a0Enum,
	NhuSuppBandUTRA_FDDbandXXVIII_8a0Enum,
	NhuSuppBandUTRA_FDDbandXXIX_8a0Enum,
	NhuSuppBandUTRA_FDDbandXXX_8a0Enum,
	NhuSuppBandUTRA_FDDbandXXXI_8a0Enum,
	NhuSuppBandUTRA_FDDbandXXXII_8a0Enum
} EnumNhuSuppBandUTRA_FDD;
typedef TknU32 NhuSuppBandUTRA_FDD;

typedef struct NhuSuppBandLstUTRA_FDD
{
	TknU16 noComp;
	NhuSuppBandUTRA_FDD *member;
}NhuSuppBandLstUTRA_FDD;

typedef struct NhuIRAT_ParamsUTRA_FDD
{
	TknPres pres;
	NhuSuppBandLstUTRA_FDD supportedBandLstUTRA_FDD;
} NhuIRAT_ParamsUTRA_FDD;

/* Element ----- SupportedBandUTRA-TDD128 ------- */
typedef enum enumNhuSuppBandUTRA_TDD128
{
	NhuSuppBandUTRA_TDD128aEnum,
	NhuSuppBandUTRA_TDD128bEnum,
	NhuSuppBandUTRA_TDD128cEnum,
	NhuSuppBandUTRA_TDD128dEnum,
	NhuSuppBandUTRA_TDD128eEnum,
	NhuSuppBandUTRA_TDD128fEnum,
	NhuSuppBandUTRA_TDD128gEnum,
	NhuSuppBandUTRA_TDD128hEnum,
	NhuSuppBandUTRA_TDD128iEnum,
	NhuSuppBandUTRA_TDD128jEnum,
	NhuSuppBandUTRA_TDD128kEnum,
	NhuSuppBandUTRA_TDD128lEnum,
	NhuSuppBandUTRA_TDD128mEnum,
	NhuSuppBandUTRA_TDD128nEnum,
	NhuSuppBandUTRA_TDD128oEnum,
	NhuSuppBandUTRA_TDD128pEnum
} EnumNhuSuppBandUTRA_TDD128;
typedef TknU32 NhuSuppBandUTRA_TDD128;

typedef struct NhuSuppBandLstUTRA_TDD128
{
	TknU16 noComp;
	NhuSuppBandUTRA_TDD128 *member;
}NhuSuppBandLstUTRA_TDD128;

typedef struct NhuIRAT_ParamsUTRA_TDD128
{
	TknPres pres;
	NhuSuppBandLstUTRA_TDD128 supportedBandLstUTRA_TDD128;
} NhuIRAT_ParamsUTRA_TDD128;

/* Element ----- SupportedBandUTRA-TDD384 ------- */
typedef enum enumNhuSuppBandUTRA_TDD384
{
	NhuSuppBandUTRA_TDD384aEnum,
	NhuSuppBandUTRA_TDD384bEnum,
	NhuSuppBandUTRA_TDD384cEnum,
	NhuSuppBandUTRA_TDD384dEnum,
	NhuSuppBandUTRA_TDD384eEnum,
	NhuSuppBandUTRA_TDD384fEnum,
	NhuSuppBandUTRA_TDD384gEnum,
	NhuSuppBandUTRA_TDD384hEnum,
	NhuSuppBandUTRA_TDD384iEnum,
	NhuSuppBandUTRA_TDD384jEnum,
	NhuSuppBandUTRA_TDD384kEnum,
	NhuSuppBandUTRA_TDD384lEnum,
	NhuSuppBandUTRA_TDD384mEnum,
	NhuSuppBandUTRA_TDD384nEnum,
	NhuSuppBandUTRA_TDD384oEnum,
	NhuSuppBandUTRA_TDD384pEnum
} EnumNhuSuppBandUTRA_TDD384;
typedef TknU32 NhuSuppBandUTRA_TDD384;

typedef struct NhuSuppBandLstUTRA_TDD384
{
	TknU16 noComp;
	NhuSuppBandUTRA_TDD384 *member;
}NhuSuppBandLstUTRA_TDD384;

typedef struct NhuIRAT_ParamsUTRA_TDD384
{
	TknPres pres;
	NhuSuppBandLstUTRA_TDD384 supportedBandLstUTRA_TDD384;
} NhuIRAT_ParamsUTRA_TDD384;

/* Element ----- SupportedBandUTRA-TDD768 ------- */
typedef enum enumNhuSuppBandUTRA_TDD768
{
	NhuSuppBandUTRA_TDD768aEnum,
	NhuSuppBandUTRA_TDD768bEnum,
	NhuSuppBandUTRA_TDD768cEnum,
	NhuSuppBandUTRA_TDD768dEnum,
	NhuSuppBandUTRA_TDD768eEnum,
	NhuSuppBandUTRA_TDD768fEnum,
	NhuSuppBandUTRA_TDD768gEnum,
	NhuSuppBandUTRA_TDD768hEnum,
	NhuSuppBandUTRA_TDD768iEnum,
	NhuSuppBandUTRA_TDD768jEnum,
	NhuSuppBandUTRA_TDD768kEnum,
	NhuSuppBandUTRA_TDD768lEnum,
	NhuSuppBandUTRA_TDD768mEnum,
	NhuSuppBandUTRA_TDD768nEnum,
	NhuSuppBandUTRA_TDD768oEnum,
	NhuSuppBandUTRA_TDD768pEnum
} EnumNhuSuppBandUTRA_TDD768;
typedef TknU32 NhuSuppBandUTRA_TDD768;

typedef struct NhuSuppBandLstUTRA_TDD768
{
	TknU16 noComp;
	NhuSuppBandUTRA_TDD768 *member;
}NhuSuppBandLstUTRA_TDD768;

typedef struct NhuIRAT_ParamsUTRA_TDD768
{
	TknPres pres;
	NhuSuppBandLstUTRA_TDD768 supportedBandLstUTRA_TDD768;
} NhuIRAT_ParamsUTRA_TDD768;

/* Element ----- SupportedBandGERAN ------- */
typedef enum enumNhuSuppBandGERAN
{
	NhuSuppBandGERANgsm450Enum,
	NhuSuppBandGERANgsm480Enum,
	NhuSuppBandGERANgsm710Enum,
	NhuSuppBandGERANgsm750Enum,
	NhuSuppBandGERANgsm810Enum,
	NhuSuppBandGERANgsm850Enum,
	NhuSuppBandGERANgsm900PEnum,
	NhuSuppBandGERANgsm900EEnum,
	NhuSuppBandGERANgsm900REnum,
	NhuSuppBandGERANgsm1800Enum,
	NhuSuppBandGERANgsm1900Enum,
	NhuSuppBandGERANspare5Enum,
	NhuSuppBandGERANspare4Enum,
	NhuSuppBandGERANspare3Enum,
	NhuSuppBandGERANspare2Enum,
	NhuSuppBandGERANspare1Enum
} EnumNhuSuppBandGERAN;
typedef TknU32 NhuSuppBandGERAN;

typedef struct NhuSuppBandLstGERAN
{
	TknU16 noComp;
	NhuSuppBandGERAN *member;
}NhuSuppBandLstGERAN;

/* Element ----- interRAT-PS-HO-ToGERAN ------- */
typedef TknU8 NhuIRAT_ParamsGERANinterRAT_PS_HO_ToGERAN;

typedef struct NhuIRAT_ParamsGERAN
{
	TknPres pres;
	NhuSuppBandLstGERAN supportedBandLstGERAN;
	NhuIRAT_ParamsGERANinterRAT_PS_HO_ToGERAN interRAT_PS_HO_ToGERAN;
} NhuIRAT_ParamsGERAN;

typedef struct NhuSuppBandLstHRPD
{
	TknU16 noComp;
	NhuBandclassCDMA2000 *member;
}NhuSuppBandLstHRPD;

/* Element ----- tx-ConfigHRPD ------- */
typedef enum enumNhuIRAT_ParamsCDMA2000_HRPDtx_ConfigHRPD
{
	NhuIRAT_ParamsCDMA2000_HRPDtx_ConfigHRPDsingleEnum,
	NhuIRAT_ParamsCDMA2000_HRPDtx_ConfigHRPDdualEnum
} EnumNhuIRAT_ParamsCDMA2000_HRPDtx_ConfigHRPD;
typedef TknU32 NhuIRAT_ParamsCDMA2000_HRPDtx_ConfigHRPD;

/* Element ----- rx-ConfigHRPD ------- */
typedef enum enumNhuIRAT_ParamsCDMA2000_HRPDrx_ConfigHRPD
{
	NhuIRAT_ParamsCDMA2000_HRPDrx_ConfigHRPDsingleEnum,
	NhuIRAT_ParamsCDMA2000_HRPDrx_ConfigHRPDdualEnum
} EnumNhuIRAT_ParamsCDMA2000_HRPDrx_ConfigHRPD;
typedef TknU32 NhuIRAT_ParamsCDMA2000_HRPDrx_ConfigHRPD;

typedef struct NhuIRAT_ParamsCDMA2000_HRPD
{
	TknPres pres;
	NhuSuppBandLstHRPD supportedBandLstHRPD;
	NhuIRAT_ParamsCDMA2000_HRPDtx_ConfigHRPD tx_ConfigHRPD;
	NhuIRAT_ParamsCDMA2000_HRPDrx_ConfigHRPD rx_ConfigHRPD;
} NhuIRAT_ParamsCDMA2000_HRPD;

typedef struct NhuSuppBandLst1XRTT
{
	TknU16 noComp;
	NhuBandclassCDMA2000 *member;
}NhuSuppBandLst1XRTT;

/* Element ----- tx-Config1XRTT ------- */
typedef enum enumNhuIRAT_ParamsCDMA2000_1XRTTtx_Config1XRTT
{
	NhuIRAT_ParamsCDMA2000_1XRTTtx_Config1XRTTsingleEnum,
	NhuIRAT_ParamsCDMA2000_1XRTTtx_Config1XRTTdualEnum
} EnumNhuIRAT_ParamsCDMA2000_1XRTTtx_Config1XRTT;
typedef TknU32 NhuIRAT_ParamsCDMA2000_1XRTTtx_Config1XRTT;

/* Element ----- rx-Config1XRTT ------- */
typedef enum enumNhuIRAT_ParamsCDMA2000_1XRTTrx_Config1XRTT
{
	NhuIRAT_ParamsCDMA2000_1XRTTrx_Config1XRTTsingleEnum,
	NhuIRAT_ParamsCDMA2000_1XRTTrx_Config1XRTTdualEnum
} EnumNhuIRAT_ParamsCDMA2000_1XRTTrx_Config1XRTT;
typedef TknU32 NhuIRAT_ParamsCDMA2000_1XRTTrx_Config1XRTT;

typedef struct NhuIRAT_ParamsCDMA2000_1XRTT
{
	TknPres pres;
	NhuSuppBandLst1XRTT supportedBandLst1XRTT;
	NhuIRAT_ParamsCDMA2000_1XRTTtx_Config1XRTT tx_Config1XRTT;
	NhuIRAT_ParamsCDMA2000_1XRTTrx_Config1XRTT rx_Config1XRTT;
} NhuIRAT_ParamsCDMA2000_1XRTT;

/* Element ----- enhancedDualLayerFDD-r9 ------- */
typedef enum enumNhuPhyLyrParams_v920enhancedDualLyrFDD_r9
{
	NhuPhyLyrParams_v920enhancedDualLyrFDD_r9supportedEnum
} EnumNhuPhyLyrParams_v920enhancedDualLyrFDD_r9;
typedef TknU32 NhuPhyLyrParams_v920enhancedDualLyrFDD_r9;

/* Element ----- enhancedDualLayerTDD-r9 ------- */
typedef enum enumNhuPhyLyrParams_v920enhancedDualLyrTDD_r9
{
	NhuPhyLyrParams_v920enhancedDualLyrTDD_r9supportedEnum
} EnumNhuPhyLyrParams_v920enhancedDualLyrTDD_r9;
typedef TknU32 NhuPhyLyrParams_v920enhancedDualLyrTDD_r9;

typedef struct NhuPhyLyrParams_v920
{
	TknPres pres;
	NhuPhyLyrParams_v920enhancedDualLyrFDD_r9 enhancedDualLyrFDD_r9;
	NhuPhyLyrParams_v920enhancedDualLyrTDD_r9 enhancedDualLyrTDD_r9;
} NhuPhyLyrParams_v920;

/* Element ----- dtm-r9 ------- */
typedef enum enumNhuIRAT_ParamsGERAN_v920dtm_r9
{
	NhuIRAT_ParamsGERAN_v920dtm_r9supportedEnum
} EnumNhuIRAT_ParamsGERAN_v920dtm_r9;
typedef TknU32 NhuIRAT_ParamsGERAN_v920dtm_r9;

/* Element ----- e-RedirectionGERAN-r9 ------- */
typedef enum enumNhuIRAT_ParamsGERAN_v920e_RedirectionGERAN_r9
{
	NhuIRAT_ParamsGERAN_v920e_RedirectionGERAN_r9supportedEnum
} EnumNhuIRAT_ParamsGERAN_v920e_RedirectionGERAN_r9;
typedef TknU32 NhuIRAT_ParamsGERAN_v920e_RedirectionGERAN_r9;

typedef struct NhuIRAT_ParamsGERAN_v920
{
	TknPres pres;
	NhuIRAT_ParamsGERAN_v920dtm_r9 dtm_r9;
	NhuIRAT_ParamsGERAN_v920e_RedirectionGERAN_r9 e_RedirectionGERAN_r9;
} NhuIRAT_ParamsGERAN_v920;

/* Element ----- e-RedirectionUTRA-r9 ------- */
typedef enum enumNhuIRAT_ParamsUTRA_v920e_RedirectionUTRA_r9
{
	NhuIRAT_ParamsUTRA_v920e_RedirectionUTRA_r9supportedEnum
} EnumNhuIRAT_ParamsUTRA_v920e_RedirectionUTRA_r9;
typedef TknU32 NhuIRAT_ParamsUTRA_v920e_RedirectionUTRA_r9;

typedef struct NhuIRAT_ParamsUTRA_v920
{
	TknPres pres;
	NhuIRAT_ParamsUTRA_v920e_RedirectionUTRA_r9 e_RedirectionUTRA_r9;
} NhuIRAT_ParamsUTRA_v920;

/* Element ----- e-CSFB-1XRTT-r9 ------- */
typedef enum enumNhuIRAT_ParamsCDMA2000_1XRTT_v920e_CSFB_1XRTT_r9
{
	NhuIRAT_ParamsCDMA2000_1XRTT_v920e_CSFB_1XRTT_r9supportedEnum
} EnumNhuIRAT_ParamsCDMA2000_1XRTT_v920e_CSFB_1XRTT_r9;
typedef TknU32 NhuIRAT_ParamsCDMA2000_1XRTT_v920e_CSFB_1XRTT_r9;

/* Element ----- e-CSFB-ConcPS-Mob1XRTT-r9 ------- */
typedef enum enumNhuIRAT_ParamsCDMA2000_1XRTT_v920e_CSFB_ConcPS_Mob1XRTT_r9
{
	NhuIRAT_ParamsCDMA2000_1XRTT_v920e_CSFB_ConcPS_Mob1XRTT_r9supportedEnum
} EnumNhuIRAT_ParamsCDMA2000_1XRTT_v920e_CSFB_ConcPS_Mob1XRTT_r9;
typedef TknU32 NhuIRAT_ParamsCDMA2000_1XRTT_v920e_CSFB_ConcPS_Mob1XRTT_r9;

typedef struct NhuIRAT_ParamsCDMA2000_1XRTT_v920
{
	TknPres pres;
	NhuIRAT_ParamsCDMA2000_1XRTT_v920e_CSFB_1XRTT_r9 e_CSFB_1XRTT_r9;
	NhuIRAT_ParamsCDMA2000_1XRTT_v920e_CSFB_ConcPS_Mob1XRTT_r9 e_CSFB_ConcPS_Mob1XRTT_r9;
} NhuIRAT_ParamsCDMA2000_1XRTT_v920;

/* Element ----- intraFreqProximityIndication-r9 ------- */
typedef enum enumNhuCSG_ProximityIndParams_r9intraFreqProximityInd_r9
{
	NhuCSG_ProximityIndParams_r9intraFreqProximityInd_r9supportedEnum
} EnumNhuCSG_ProximityIndParams_r9intraFreqProximityInd_r9;
typedef TknU32 NhuCSG_ProximityIndParams_r9intraFreqProximityInd_r9;

/* Element ----- interFreqProximityIndication-r9 ------- */
typedef enum enumNhuCSG_ProximityIndParams_r9interFreqProximityInd_r9
{
	NhuCSG_ProximityIndParams_r9interFreqProximityInd_r9supportedEnum
} EnumNhuCSG_ProximityIndParams_r9interFreqProximityInd_r9;
typedef TknU32 NhuCSG_ProximityIndParams_r9interFreqProximityInd_r9;

/* Element ----- utran-ProximityIndication-r9 ------- */
typedef enum enumNhuCSG_ProximityIndParams_r9utran_ProximityInd_r9
{
	NhuCSG_ProximityIndParams_r9utran_ProximityInd_r9supportedEnum
} EnumNhuCSG_ProximityIndParams_r9utran_ProximityInd_r9;
typedef TknU32 NhuCSG_ProximityIndParams_r9utran_ProximityInd_r9;

typedef struct NhuCSG_ProximityIndParams_r9
{
	TknPres pres;
	NhuCSG_ProximityIndParams_r9intraFreqProximityInd_r9 intraFreqProximityInd_r9;
	NhuCSG_ProximityIndParams_r9interFreqProximityInd_r9 interFreqProximityInd_r9;
	NhuCSG_ProximityIndParams_r9utran_ProximityInd_r9 utran_ProximityInd_r9;
} NhuCSG_ProximityIndParams_r9;

/* Element ----- intraFreqSI-AcquisitionForHO-r9 ------- */
typedef enum enumNhuNeighCellSI_AcquisitionParams_r9intraFreqSI_AcquisitionForHO_r9
{
	NhuNeighCellSI_AcquisitionParams_r9intraFreqSI_AcquisitionForHO_r9supportedEnum
} EnumNhuNeighCellSI_AcquisitionParams_r9intraFreqSI_AcquisitionForHO_r9;
typedef TknU32 NhuNeighCellSI_AcquisitionParams_r9intraFreqSI_AcquisitionForHO_r9;

/* Element ----- interFreqSI-AcquisitionForHO-r9 ------- */
typedef enum enumNhuNeighCellSI_AcquisitionParams_r9interFreqSI_AcquisitionForHO_r9
{
	NhuNeighCellSI_AcquisitionParams_r9interFreqSI_AcquisitionForHO_r9supportedEnum
} EnumNhuNeighCellSI_AcquisitionParams_r9interFreqSI_AcquisitionForHO_r9;
typedef TknU32 NhuNeighCellSI_AcquisitionParams_r9interFreqSI_AcquisitionForHO_r9;

/* Element ----- utran-SI-AcquisitionForHO-r9 ------- */
typedef enum enumNhuNeighCellSI_AcquisitionParams_r9utran_SI_AcquisitionForHO_r9
{
	NhuNeighCellSI_AcquisitionParams_r9utran_SI_AcquisitionForHO_r9supportedEnum
} EnumNhuNeighCellSI_AcquisitionParams_r9utran_SI_AcquisitionForHO_r9;
typedef TknU32 NhuNeighCellSI_AcquisitionParams_r9utran_SI_AcquisitionForHO_r9;

typedef struct NhuNeighCellSI_AcquisitionParams_r9
{
	TknPres pres;
	NhuNeighCellSI_AcquisitionParams_r9intraFreqSI_AcquisitionForHO_r9 intraFreqSI_AcquisitionForHO_r9;
	NhuNeighCellSI_AcquisitionParams_r9interFreqSI_AcquisitionForHO_r9 interFreqSI_AcquisitionForHO_r9;
	NhuNeighCellSI_AcquisitionParams_r9utran_SI_AcquisitionForHO_r9 utran_SI_AcquisitionForHO_r9;
} NhuNeighCellSI_AcquisitionParams_r9;

/* Element ----- rach-Report-r9 ------- */
typedef enum enumNhuSON_Params_r9rach_Report_r9
{
	NhuSON_Params_r9rach_Report_r9supportedEnum
} EnumNhuSON_Params_r9rach_Report_r9;
typedef TknU32 NhuSON_Params_r9rach_Report_r9;

typedef struct NhuSON_Params_r9
{
	TknPres pres;
	NhuSON_Params_r9rach_Report_r9 rach_Report_r9;
} NhuSON_Params_r9;

/* Element ----- nonContiguousUL-RA-WithinCC-Info-r10 ------- */
typedef enum enumNhuNonContiguousUL_RA_WithinCC_r10nonContiguousUL_RA_WithinCC_Info_r10
{
	NhuNonContiguousUL_RA_WithinCC_r10nonContiguousUL_RA_WithinCC_Info_r10supportedEnum
} EnumNhuNonContiguousUL_RA_WithinCC_r10nonContiguousUL_RA_WithinCC_Info_r10;
typedef TknU32 NhuNonContiguousUL_RA_WithinCC_r10nonContiguousUL_RA_WithinCC_Info_r10;

typedef struct NhuNonContiguousUL_RA_WithinCC_r10
{
	TknPres pres;
	NhuNonContiguousUL_RA_WithinCC_r10nonContiguousUL_RA_WithinCC_Info_r10 nonContiguousUL_RA_WithinCC_Info_r10;
} NhuNonContiguousUL_RA_WithinCC_r10;

typedef struct NhuNonContiguousUL_RA_WithinCC_Lst_r10
{
	TknU16 noComp;
	NhuNonContiguousUL_RA_WithinCC_r10 *member;
}NhuNonContiguousUL_RA_WithinCC_Lst_r10;

/* Element ----- twoAntennaPortsForPUCCH-r10 ------- */
typedef enum enumNhuPhyLyrParams_v1020twoAntennaPortsForPUCCH_r10
{
	NhuPhyLyrParams_v1020twoAntennaPortsForPUCCH_r10supportedEnum
} EnumNhuPhyLyrParams_v1020twoAntennaPortsForPUCCH_r10;
typedef TknU32 NhuPhyLyrParams_v1020twoAntennaPortsForPUCCH_r10;

/* Element ----- tm9-With-8Tx-FDD-r10 ------- */
typedef enum enumNhuPhyLyrParams_v1020tm9_With_8Tx_FDD_r10
{
	NhuPhyLyrParams_v1020tm9_With_8Tx_FDD_r10supportedEnum
} EnumNhuPhyLyrParams_v1020tm9_With_8Tx_FDD_r10;
typedef TknU32 NhuPhyLyrParams_v1020tm9_With_8Tx_FDD_r10;

/* Element ----- pmi-Disabling-r10 ------- */
typedef enum enumNhuPhyLyrParams_v1020pmi_Disabling_r10
{
	NhuPhyLyrParams_v1020pmi_Disabling_r10supportedEnum
} EnumNhuPhyLyrParams_v1020pmi_Disabling_r10;
typedef TknU32 NhuPhyLyrParams_v1020pmi_Disabling_r10;

/* Element ----- crossCarrierScheduling-r10 ------- */
typedef enum enumNhuPhyLyrParams_v1020crossCarrierScheduling_r10
{
	NhuPhyLyrParams_v1020crossCarrierScheduling_r10supportedEnum
} EnumNhuPhyLyrParams_v1020crossCarrierScheduling_r10;
typedef TknU32 NhuPhyLyrParams_v1020crossCarrierScheduling_r10;

/* Element ----- simultaneousPUCCH-PUSCH-r10 ------- */
typedef enum enumNhuPhyLyrParams_v1020simultaneousPUCCH_PUSCH_r10
{
	NhuPhyLyrParams_v1020simultaneousPUCCH_PUSCH_r10supportedEnum
} EnumNhuPhyLyrParams_v1020simultaneousPUCCH_PUSCH_r10;
typedef TknU32 NhuPhyLyrParams_v1020simultaneousPUCCH_PUSCH_r10;

/* Element ----- multiClusterPUSCH-WithinCC-r10 ------- */
typedef enum enumNhuPhyLyrParams_v1020multiClusterPUSCH_WithinCC_r10
{
	NhuPhyLyrParams_v1020multiClusterPUSCH_WithinCC_r10supportedEnum
} EnumNhuPhyLyrParams_v1020multiClusterPUSCH_WithinCC_r10;
typedef TknU32 NhuPhyLyrParams_v1020multiClusterPUSCH_WithinCC_r10;

typedef struct NhuPhyLyrParams_v1020
{
	TknPres pres;
	NhuPhyLyrParams_v1020twoAntennaPortsForPUCCH_r10 twoAntennaPortsForPUCCH_r10;
	NhuPhyLyrParams_v1020tm9_With_8Tx_FDD_r10 tm9_With_8Tx_FDD_r10;
	NhuPhyLyrParams_v1020pmi_Disabling_r10 pmi_Disabling_r10;
	NhuPhyLyrParams_v1020crossCarrierScheduling_r10 crossCarrierScheduling_r10;
	NhuPhyLyrParams_v1020simultaneousPUCCH_PUSCH_r10 simultaneousPUCCH_PUSCH_r10;
	NhuPhyLyrParams_v1020multiClusterPUSCH_WithinCC_r10 multiClusterPUSCH_WithinCC_r10;
	NhuNonContiguousUL_RA_WithinCC_Lst_r10 nonContiguousUL_RA_WithinCC_Lst_r10;
} NhuPhyLyrParams_v1020;

/* Element ----- CA-BandwidthClass-r10 ------- */
typedef enum enumNhuCA_BandwidthClass_r10
{
	NhuCA_BandwidthClass_r10aEnum,
	NhuCA_BandwidthClass_r10bEnum,
	NhuCA_BandwidthClass_r10cEnum,
	NhuCA_BandwidthClass_r10dEnum,
	NhuCA_BandwidthClass_r10eEnum,
	NhuCA_BandwidthClass_r10fEnum
} EnumNhuCA_BandwidthClass_r10;
typedef TknU32 NhuCA_BandwidthClass_r10;

/* Element ----- MIMO-CapabilityUL-r10 ------- */
typedef enum enumNhuMIMO_CapUL_r10
{
	NhuMIMO_CapUL_r10twoLyrsEnum,
	NhuMIMO_CapUL_r10fourLyrsEnum
} EnumNhuMIMO_CapUL_r10;
typedef TknU32 NhuMIMO_CapUL_r10;

typedef struct NhuCA_MIMO_ParamsUL_r10
{
	TknPres pres;
	NhuCA_BandwidthClass_r10 ca_BandwidthClassUL_r10;
	NhuMIMO_CapUL_r10 supportedMIMO_CapUL_r10;
} NhuCA_MIMO_ParamsUL_r10;

typedef struct NhuBandParamsUL_r10
{
	TknU16 noComp;
	NhuCA_MIMO_ParamsUL_r10 *member;
}NhuBandParamsUL_r10;

/* Element ----- MIMO-CapabilityDL-r10 ------- */
typedef enum enumNhuMIMO_CapDL_r10
{
	NhuMIMO_CapDL_r10twoLyrsEnum,
	NhuMIMO_CapDL_r10fourLyrsEnum,
	NhuMIMO_CapDL_r10eightLyrsEnum
} EnumNhuMIMO_CapDL_r10;
typedef TknU32 NhuMIMO_CapDL_r10;

typedef struct NhuCA_MIMO_ParamsDL_r10
{
	TknPres pres;
	NhuCA_BandwidthClass_r10 ca_BandwidthClassDL_r10;
	NhuMIMO_CapDL_r10 supportedMIMO_CapDL_r10;
} NhuCA_MIMO_ParamsDL_r10;

typedef struct NhuBandParamsDL_r10
{
	TknU16 noComp;
	NhuCA_MIMO_ParamsDL_r10 *member;
}NhuBandParamsDL_r10;

typedef struct NhuBandParams_r10
{
	TknPres pres;
	NhuFreqBandIndicator bandEUTRA_r10;
	NhuBandParamsUL_r10 bandParamsUL_r10;
	NhuBandParamsDL_r10 bandParamsDL_r10;
} NhuBandParams_r10;

typedef struct NhuBandCombinationParams_r10
{
	TknU16 noComp;
	NhuBandParams_r10 *member;
}NhuBandCombinationParams_r10;

typedef struct NhuSuppBandCombination_r10
{
	TknU16 noComp;
	NhuBandCombinationParams_r10 *member;
}NhuSuppBandCombination_r10;

typedef struct NhuRF_Params_v1020
{
	TknPres pres;
	NhuSuppBandCombination_r10 supportedBandCombination_r10;
} NhuRF_Params_v1020;

typedef struct NhuBandCombinationLstEUTRA_r10
{
	TknU16 noComp;
	NhuBandInfoEUTRA *member;
}NhuBandCombinationLstEUTRA_r10;

typedef struct NhuMeasParams_v1020
{
	TknPres pres;
	NhuBandCombinationLstEUTRA_r10 bandCombinationLstEUTRA_r10;
} NhuMeasParams_v1020;

/* Element ----- e-CSFB-dual-1XRTT-r10 ------- */
typedef enum enumNhuIRAT_ParamsCDMA2000_1XRTT_v1020e_CSFB_dual_1XRTT_r10
{
	NhuIRAT_ParamsCDMA2000_1XRTT_v1020e_CSFB_dual_1XRTT_r10supportedEnum
} EnumNhuIRAT_ParamsCDMA2000_1XRTT_v1020e_CSFB_dual_1XRTT_r10;
typedef TknU32 NhuIRAT_ParamsCDMA2000_1XRTT_v1020e_CSFB_dual_1XRTT_r10;

typedef struct NhuIRAT_ParamsCDMA2000_1XRTT_v1020
{
	TknPres pres;
	NhuIRAT_ParamsCDMA2000_1XRTT_v1020e_CSFB_dual_1XRTT_r10 e_CSFB_dual_1XRTT_r10;
} NhuIRAT_ParamsCDMA2000_1XRTT_v1020;

/* Element ----- loggedMeasurementsIdle-r10 ------- */
typedef enum enumNhuUE_BasedNetwPerfMeasParams_r10loggedMeasurementsIdle_r10
{
	NhuUE_BasedNetwPerfMeasParams_r10loggedMeasurementsIdle_r10supportedEnum
} EnumNhuUE_BasedNetwPerfMeasParams_r10loggedMeasurementsIdle_r10;
typedef TknU32 NhuUE_BasedNetwPerfMeasParams_r10loggedMeasurementsIdle_r10;

/* Element ----- standaloneGNSS-Location-r10 ------- */
typedef enum enumNhuUE_BasedNetwPerfMeasParams_r10standaloneGNSS_Loc_r10
{
	NhuUE_BasedNetwPerfMeasParams_r10standaloneGNSS_Loc_r10supportedEnum
} EnumNhuUE_BasedNetwPerfMeasParams_r10standaloneGNSS_Loc_r10;
typedef TknU32 NhuUE_BasedNetwPerfMeasParams_r10standaloneGNSS_Loc_r10;

typedef struct NhuUE_BasedNetwPerfMeasParams_r10
{
	TknPres pres;
	NhuUE_BasedNetwPerfMeasParams_r10loggedMeasurementsIdle_r10 loggedMeasurementsIdle_r10;
	NhuUE_BasedNetwPerfMeasParams_r10standaloneGNSS_Loc_r10 standaloneGNSS_Loc_r10;
} NhuUE_BasedNetwPerfMeasParams_r10;

/* Element ----- e-RedirectionUTRA-TDD-r10 ------- */
typedef enum enumNhuIRAT_ParamsUTRA_TDD_v1020e_RedirectionUTRA_TDD_r10
{
	NhuIRAT_ParamsUTRA_TDD_v1020e_RedirectionUTRA_TDD_r10supportedEnum
} EnumNhuIRAT_ParamsUTRA_TDD_v1020e_RedirectionUTRA_TDD_r10;
typedef TknU32 NhuIRAT_ParamsUTRA_TDD_v1020e_RedirectionUTRA_TDD_r10;

typedef struct NhuIRAT_ParamsUTRA_TDD_v1020
{
	TknPres pres;
	NhuIRAT_ParamsUTRA_TDD_v1020e_RedirectionUTRA_TDD_r10 e_RedirectionUTRA_TDD_r10;
} NhuIRAT_ParamsUTRA_TDD_v1020;

/* Element ----- otdoa-UE-Assisted-r10 ------- */
typedef enum enumNhuOTDOA_PositioningCapabilities_r10otdoa_UE_Assisted_r10
{
	NhuOTDOA_PositioningCapabilities_r10otdoa_UE_Assisted_r10supportedEnum
} EnumNhuOTDOA_PositioningCapabilities_r10otdoa_UE_Assisted_r10;
typedef TknU32 NhuOTDOA_PositioningCapabilities_r10otdoa_UE_Assisted_r10;

/* Element ----- interFreqRSTD-Measurement-r10 ------- */
typedef enum enumNhuOTDOA_PositioningCapabilities_r10interFreqRSTD_Measurement_r10
{
	NhuOTDOA_PositioningCapabilities_r10interFreqRSTD_Measurement_r10supportedEnum
} EnumNhuOTDOA_PositioningCapabilities_r10interFreqRSTD_Measurement_r10;
typedef TknU32 NhuOTDOA_PositioningCapabilities_r10interFreqRSTD_Measurement_r10;

typedef struct NhuOTDOA_PositioningCapabilities_r10
{
	TknPres pres;
	NhuOTDOA_PositioningCapabilities_r10otdoa_UE_Assisted_r10 otdoa_UE_Assisted_r10;
	NhuOTDOA_PositioningCapabilities_r10interFreqRSTD_Measurement_r10 interFreqRSTD_Measurement_r10;
} NhuOTDOA_PositioningCapabilities_r10;

/* Element ---------- featureGroupIndRel10-v1060 ----------- */
typedef TknStrBSXL NhuUE_EUTRA_CapAddXDD_Mode_v1060featureGroupIndRel10_v1060;
typedef struct NhuUE_EUTRA_CapAddXDD_Mode_v1060extaddgrp_1
{
	TknPres pres;
	NhuOTDOA_PositioningCapabilities_r10 otdoa_PositioningCapabilities_r10;
} NhuUE_EUTRA_CapAddXDD_Mode_v1060extaddgrp_1;

typedef struct NhuUE_EUTRA_CapAddXDD_Mode_v1060
{
	TknPres pres;
	NhuPhyLyrParams_v1020 phyLyrParams_v1060;
	NhuUE_EUTRA_CapAddXDD_Mode_v1060featureGroupIndRel10_v1060 featureGroupIndRel10_v1060;
	NhuIRAT_ParamsCDMA2000_1XRTT_v1020 interRAT_ParamsCDMA2000_v1060;
	NhuIRAT_ParamsUTRA_TDD_v1020 interRAT_ParamsUTRA_TDD_v1060;
	NhuUE_EUTRA_CapAddXDD_Mode_v1060extaddgrp_1 extaddgrp_1;
} NhuUE_EUTRA_CapAddXDD_Mode_v1060;

/* Element ---------- SupportedBandwidthCombinationSet-r10 ----------- */
typedef TknStrBSXL NhuSuppBandwidthCombinationSet_r10;
typedef struct NhuBandCombinationParamsExt_r10
{
	TknPres pres;
	NhuSuppBandwidthCombinationSet_r10 supportedBandwidthCombinationSet_r10;
} NhuBandCombinationParamsExt_r10;

typedef struct NhuSuppBandCombinationExt_r10
{
	TknU16 noComp;
	NhuBandCombinationParamsExt_r10 *member;
}NhuSuppBandCombinationExt_r10;

typedef struct NhuRF_Params_v1060
{
	TknPres pres;
	NhuSuppBandCombinationExt_r10 supportedBandCombinationExt_r10;
} NhuRF_Params_v1060;

typedef struct NhuBandParams_v1090
{
	TknPres pres;
	NhuFreqBandIndicator_v9e0 bandEUTRA_v1090;
} NhuBandParams_v1090;

typedef struct NhuBandCombinationParams_v1090
{
	TknU16 noComp;
	NhuBandParams_v1090 *member;
}NhuBandCombinationParams_v1090;

typedef struct NhuSuppBandCombination_v1090
{
	TknU16 noComp;
	NhuBandCombinationParams_v1090 *member;
}NhuSuppBandCombination_v1090;

typedef struct NhuRF_Params_v1090
{
	TknPres pres;
	NhuSuppBandCombination_v1090 supportedBandCombination_v1090;
} NhuRF_Params_v1090;

/* Element ----- pdcp-SN-Extension-r11 ------- */
typedef enum enumNhuPDCP_Params_v1130pdcp_SN_Extn_r11
{
	NhuPDCP_Params_v1130pdcp_SN_Extn_r11supportedEnum
} EnumNhuPDCP_Params_v1130pdcp_SN_Extn_r11;
typedef TknU32 NhuPDCP_Params_v1130pdcp_SN_Extn_r11;

/* Element ----- supportRohcContextContinue-r11 ------- */
typedef enum enumNhuPDCP_Params_v1130supportRohcCtxtContinue_r11
{
	NhuPDCP_Params_v1130supportRohcCtxtContinue_r11supportedEnum
} EnumNhuPDCP_Params_v1130supportRohcCtxtContinue_r11;
typedef TknU32 NhuPDCP_Params_v1130supportRohcCtxtContinue_r11;

typedef struct NhuPDCP_Params_v1130
{
	TknPres pres;
	NhuPDCP_Params_v1130pdcp_SN_Extn_r11 pdcp_SN_Extn_r11;
	NhuPDCP_Params_v1130supportRohcCtxtContinue_r11 supportRohcCtxtContinue_r11;
} NhuPDCP_Params_v1130;

/* Element ----- crs-InterfHandl-r11 ------- */
typedef enum enumNhuPhyLyrParams_v1130crs_InterfHandl_r11
{
	NhuPhyLyrParams_v1130crs_InterfHandl_r11supportedEnum
} EnumNhuPhyLyrParams_v1130crs_InterfHandl_r11;
typedef TknU32 NhuPhyLyrParams_v1130crs_InterfHandl_r11;

/* Element ----- ePDCCH-r11 ------- */
typedef enum enumNhuPhyLyrParams_v1130ePDCCH_r11
{
	NhuPhyLyrParams_v1130ePDCCH_r11supportedEnum
} EnumNhuPhyLyrParams_v1130ePDCCH_r11;
typedef TknU32 NhuPhyLyrParams_v1130ePDCCH_r11;

/* Element ----- multiACK-CSI-Reporting-r11 ------- */
typedef enum enumNhuPhyLyrParams_v1130multiACK_CSI_Rprtng_r11
{
	NhuPhyLyrParams_v1130multiACK_CSI_Rprtng_r11supportedEnum
} EnumNhuPhyLyrParams_v1130multiACK_CSI_Rprtng_r11;
typedef TknU32 NhuPhyLyrParams_v1130multiACK_CSI_Rprtng_r11;

/* Element ----- ss-CCH-InterfHandl-r11 ------- */
typedef enum enumNhuPhyLyrParams_v1130ss_CCH_InterfHandl_r11
{
	NhuPhyLyrParams_v1130ss_CCH_InterfHandl_r11supportedEnum
} EnumNhuPhyLyrParams_v1130ss_CCH_InterfHandl_r11;
typedef TknU32 NhuPhyLyrParams_v1130ss_CCH_InterfHandl_r11;

/* Element ----- tdd-SpecialSubframe-r11 ------- */
typedef enum enumNhuPhyLyrParams_v1130tdd_SpecialSubfrm_r11
{
	NhuPhyLyrParams_v1130tdd_SpecialSubfrm_r11supportedEnum
} EnumNhuPhyLyrParams_v1130tdd_SpecialSubfrm_r11;
typedef TknU32 NhuPhyLyrParams_v1130tdd_SpecialSubfrm_r11;

/* Element ----- txDiv-PUCCH1b-ChSelect-r11 ------- */
typedef enum enumNhuPhyLyrParams_v1130txDiv_PUCCH1b_ChSelect_r11
{
	NhuPhyLyrParams_v1130txDiv_PUCCH1b_ChSelect_r11supportedEnum
} EnumNhuPhyLyrParams_v1130txDiv_PUCCH1b_ChSelect_r11;
typedef TknU32 NhuPhyLyrParams_v1130txDiv_PUCCH1b_ChSelect_r11;

/* Element ----- ul-CoMP-r11 ------- */
typedef enum enumNhuPhyLyrParams_v1130ul_CoMP_r11
{
	NhuPhyLyrParams_v1130ul_CoMP_r11supportedEnum
} EnumNhuPhyLyrParams_v1130ul_CoMP_r11;
typedef TknU32 NhuPhyLyrParams_v1130ul_CoMP_r11;

typedef struct NhuPhyLyrParams_v1130
{
	TknPres pres;
	NhuPhyLyrParams_v1130crs_InterfHandl_r11 crs_InterfHandl_r11;
	NhuPhyLyrParams_v1130ePDCCH_r11 ePDCCH_r11;
	NhuPhyLyrParams_v1130multiACK_CSI_Rprtng_r11 multiACK_CSI_Rprtng_r11;
	NhuPhyLyrParams_v1130ss_CCH_InterfHandl_r11 ss_CCH_InterfHandl_r11;
	NhuPhyLyrParams_v1130tdd_SpecialSubfrm_r11 tdd_SpecialSubfrm_r11;
	NhuPhyLyrParams_v1130txDiv_PUCCH1b_ChSelect_r11 txDiv_PUCCH1b_ChSelect_r11;
	NhuPhyLyrParams_v1130ul_CoMP_r11 ul_CoMP_r11;
} NhuPhyLyrParams_v1130;

/* Element ----- supportedCSI-Proc-r11 ------- */
typedef enum enumNhuBandParams_v1130supportedCSI_Proc_r11
{
	NhuBandParams_v1130supportedCSI_Proc_r11n1Enum,
	NhuBandParams_v1130supportedCSI_Proc_r11n3Enum,
	NhuBandParams_v1130supportedCSI_Proc_r11n4Enum
} EnumNhuBandParams_v1130supportedCSI_Proc_r11;
typedef TknU32 NhuBandParams_v1130supportedCSI_Proc_r11;

typedef struct NhuBandParams_v1130
{
	TknPres pres;
	NhuBandParams_v1130supportedCSI_Proc_r11 supportedCSI_Proc_r11;
} NhuBandParams_v1130;

/* Element ----- multipleTimingAdvance-r11 ------- */
typedef enum enumNhuBandCombinationParams_v1130multipleTimingAdvance_r11
{
	NhuBandCombinationParams_v1130multipleTimingAdvance_r11supportedEnum
} EnumNhuBandCombinationParams_v1130multipleTimingAdvance_r11;
typedef TknU32 NhuBandCombinationParams_v1130multipleTimingAdvance_r11;

/* Element ----- simultaneousRx-Tx-r11 ------- */
typedef enum enumNhuBandCombinationParams_v1130simultaneousRx_Tx_r11
{
	NhuBandCombinationParams_v1130simultaneousRx_Tx_r11supportedEnum
} EnumNhuBandCombinationParams_v1130simultaneousRx_Tx_r11;
typedef TknU32 NhuBandCombinationParams_v1130simultaneousRx_Tx_r11;

typedef struct NhuBandCombinationParams_v1130bandParameterLst_r11
{
	TknU16 noComp;
	NhuBandParams_v1130 *member;
}NhuBandCombinationParams_v1130bandParameterLst_r11;

typedef struct NhuBandCombinationParams_v1130
{
	TknPres pres;
	NhuBandCombinationParams_v1130multipleTimingAdvance_r11 multipleTimingAdvance_r11;
	NhuBandCombinationParams_v1130simultaneousRx_Tx_r11 simultaneousRx_Tx_r11;
	NhuBandCombinationParams_v1130bandParameterLst_r11 bandParameterLst_r11;
} NhuBandCombinationParams_v1130;

typedef struct NhuSuppBandCombination_v1130
{
	TknU16 noComp;
	NhuBandCombinationParams_v1130 *member;
}NhuSuppBandCombination_v1130;

typedef struct NhuRF_Params_v1130
{
	TknPres pres;
	NhuSuppBandCombination_v1130 supportedBandCombination_v1130;
} NhuRF_Params_v1130;

/* Element ----- rsrqMeasWideband-r11 ------- */
typedef enum enumNhuMeasParams_v1130rsrqMeasWideband_r11
{
	NhuMeasParams_v1130rsrqMeasWideband_r11supportedEnum
} EnumNhuMeasParams_v1130rsrqMeasWideband_r11;
typedef TknU32 NhuMeasParams_v1130rsrqMeasWideband_r11;

typedef struct NhuMeasParams_v1130
{
	TknPres pres;
	NhuMeasParams_v1130rsrqMeasWideband_r11 rsrqMeasWideband_r11;
} NhuMeasParams_v1130;

/* Element ----- cdma2000-NW-Sharing-r11 ------- */
typedef enum enumNhuIRAT_ParamsCDMA2000_v1130cdma2000_NW_Sharing_r11
{
	NhuIRAT_ParamsCDMA2000_v1130cdma2000_NW_Sharing_r11supportedEnum
} EnumNhuIRAT_ParamsCDMA2000_v1130cdma2000_NW_Sharing_r11;
typedef TknU32 NhuIRAT_ParamsCDMA2000_v1130cdma2000_NW_Sharing_r11;

typedef struct NhuIRAT_ParamsCDMA2000_v1130
{
	TknPres pres;
	NhuIRAT_ParamsCDMA2000_v1130cdma2000_NW_Sharing_r11 cdma2000_NW_Sharing_r11;
} NhuIRAT_ParamsCDMA2000_v1130;

/* Element ----- inDeviceCoexInd-r11 ------- */
typedef enum enumNhuOther_Params_r11inDeviceCoexInd_r11
{
	NhuOther_Params_r11inDeviceCoexInd_r11supportedEnum
} EnumNhuOther_Params_r11inDeviceCoexInd_r11;
typedef TknU32 NhuOther_Params_r11inDeviceCoexInd_r11;

/* Element ----- powerPrefInd-r11 ------- */
typedef enum enumNhuOther_Params_r11powerPrefInd_r11
{
	NhuOther_Params_r11powerPrefInd_r11supportedEnum
} EnumNhuOther_Params_r11powerPrefInd_r11;
typedef TknU32 NhuOther_Params_r11powerPrefInd_r11;

/* Element ----- ue-Rx-TxTimeDiffMeasurements-r11 ------- */
typedef enum enumNhuOther_Params_r11ue_Rx_TxTimeDiffMeasurements_r11
{
	NhuOther_Params_r11ue_Rx_TxTimeDiffMeasurements_r11supportedEnum
} EnumNhuOther_Params_r11ue_Rx_TxTimeDiffMeasurements_r11;
typedef TknU32 NhuOther_Params_r11ue_Rx_TxTimeDiffMeasurements_r11;

typedef struct NhuOther_Params_r11
{
	TknPres pres;
	NhuOther_Params_r11inDeviceCoexInd_r11 inDeviceCoexInd_r11;
	NhuOther_Params_r11powerPrefInd_r11 powerPrefInd_r11;
	NhuOther_Params_r11ue_Rx_TxTimeDiffMeasurements_r11 ue_Rx_TxTimeDiffMeasurements_r11;
} NhuOther_Params_r11;

typedef struct NhuUE_EUTRA_CapAddXDD_Mode_v1130
{
	TknPres pres;
	NhuPhyLyrParams_v1130 phyLyrParams_v1130;
	NhuMeasParams_v1130 measParams_v1130;
	NhuOther_Params_r11 otherParams_r11;
} NhuUE_EUTRA_CapAddXDD_Mode_v1130;

/* Element ---------- interBandTDD-CA-WithDifferentConfig-r11 ----------- */
typedef TknStrBSXL NhuPhyLyrParams_v1170interBandTDD_CA_WithDifferentConfig_r11;
typedef struct NhuPhyLyrParams_v1170
{
	TknPres pres;
	NhuPhyLyrParams_v1170interBandTDD_CA_WithDifferentConfig_r11 interBandTDD_CA_WithDifferentConfig_r11;
} NhuPhyLyrParams_v1170;

/* Element ----- supportedCSI-Proc-r11 ------- */
typedef enum enumNhuBandParams_r11supportedCSI_Proc_r11
{
	NhuBandParams_r11supportedCSI_Proc_r11n1Enum,
	NhuBandParams_r11supportedCSI_Proc_r11n3Enum,
	NhuBandParams_r11supportedCSI_Proc_r11n4Enum
} EnumNhuBandParams_r11supportedCSI_Proc_r11;
typedef TknU32 NhuBandParams_r11supportedCSI_Proc_r11;

typedef struct NhuBandParams_r11
{
	TknPres pres;
	NhuFreqBandIndicator_r11 bandEUTRA_r11;
	NhuBandParamsUL_r10 bandParamsUL_r11;
	NhuBandParamsDL_r10 bandParamsDL_r11;
	NhuBandParams_r11supportedCSI_Proc_r11 supportedCSI_Proc_r11;
} NhuBandParams_r11;

typedef struct NhuBandCombinationParams_r11bandParameterLst_r11
{
	TknU16 noComp;
	NhuBandParams_r11 *member;
}NhuBandCombinationParams_r11bandParameterLst_r11;

/* Element ----- multipleTimingAdvance-r11 ------- */
typedef enum enumNhuBandCombinationParams_r11multipleTimingAdvance_r11
{
	NhuBandCombinationParams_r11multipleTimingAdvance_r11supportedEnum
} EnumNhuBandCombinationParams_r11multipleTimingAdvance_r11;
typedef TknU32 NhuBandCombinationParams_r11multipleTimingAdvance_r11;

/* Element ----- simultaneousRx-Tx-r11 ------- */
typedef enum enumNhuBandCombinationParams_r11simultaneousRx_Tx_r11
{
	NhuBandCombinationParams_r11simultaneousRx_Tx_r11supportedEnum
} EnumNhuBandCombinationParams_r11simultaneousRx_Tx_r11;
typedef TknU32 NhuBandCombinationParams_r11simultaneousRx_Tx_r11;

typedef struct NhuBandCombinationParams_r11
{
	TknPres pres;
	NhuBandCombinationParams_r11bandParameterLst_r11 bandParameterLst_r11;
	NhuSuppBandwidthCombinationSet_r10 supportedBandwidthCombinationSet_r11;
	NhuBandCombinationParams_r11multipleTimingAdvance_r11 multipleTimingAdvance_r11;
	NhuBandCombinationParams_r11simultaneousRx_Tx_r11 simultaneousRx_Tx_r11;
	NhuBandInfoEUTRA bandInfoEUTRA_r11;
} NhuBandCombinationParams_r11;

typedef struct NhuSuppBandCombinationAdd_r11
{
	TknU16 noComp;
	NhuBandCombinationParams_r11 *member;
}NhuSuppBandCombinationAdd_r11;

/* Element ----- freqBandRetrieval-r11 ------- */
typedef enum enumNhuRF_Params_v1180freqBandRetrieval_r11
{
	NhuRF_Params_v1180freqBandRetrieval_r11supportedEnum
} EnumNhuRF_Params_v1180freqBandRetrieval_r11;
typedef TknU32 NhuRF_Params_v1180freqBandRetrieval_r11;

typedef struct NhuRF_Params_v1180requestedBands_r11
{
	TknU16 noComp;
	NhuFreqBandIndicator_r11 *member;
}NhuRF_Params_v1180requestedBands_r11;

typedef struct NhuRF_Params_v1180
{
	TknPres pres;
	NhuRF_Params_v1180freqBandRetrieval_r11 freqBandRetrieval_r11;
	NhuRF_Params_v1180requestedBands_r11 requestedBands_r11;
	NhuSuppBandCombinationAdd_r11 supportedBandCombinationAdd_r11;
} NhuRF_Params_v1180;

/* Element ----- mbms-SCell-r11 ------- */
typedef enum enumNhuMBMS_Params_r11mbms_SCell_r11
{
	NhuMBMS_Params_r11mbms_SCell_r11supportedEnum
} EnumNhuMBMS_Params_r11mbms_SCell_r11;
typedef TknU32 NhuMBMS_Params_r11mbms_SCell_r11;

/* Element ----- mbms-NonServingCell-r11 ------- */
typedef enum enumNhuMBMS_Params_r11mbms_NonServingCell_r11
{
	NhuMBMS_Params_r11mbms_NonServingCell_r11supportedEnum
} EnumNhuMBMS_Params_r11mbms_NonServingCell_r11;
typedef TknU32 NhuMBMS_Params_r11mbms_NonServingCell_r11;

typedef struct NhuMBMS_Params_r11
{
	TknPres pres;
	NhuMBMS_Params_r11mbms_SCell_r11 mbms_SCell_r11;
	NhuMBMS_Params_r11mbms_NonServingCell_r11 mbms_NonServingCell_r11;
} NhuMBMS_Params_r11;

typedef struct NhuUE_EUTRA_CapAddXDD_Mode_v1180
{
	TknPres pres;
	NhuMBMS_Params_r11 mbms_Params_r11;
} NhuUE_EUTRA_CapAddXDD_Mode_v1180;

/* Element ----- benefitsFromInterruption-r11 ------- */
typedef enum enumNhuMeasParams_v11a0benefitsFromInterruption_r11
{
	NhuMeasParams_v11a0benefitsFromInterruption_r11trueEnum
} EnumNhuMeasParams_v11a0benefitsFromInterruption_r11;
typedef TknU32 NhuMeasParams_v11a0benefitsFromInterruption_r11;

typedef struct NhuMeasParams_v11a0
{
	TknPres pres;
	NhuMeasParams_v11a0benefitsFromInterruption_r11 benefitsFromInterruption_r11;
} NhuMeasParams_v11a0;

/* Element ----- ue-Category-v11a0 ------- */
typedef TknU32 NhuUE_EUTRA_Cap_v11a0_IEsue_Category_v11a0;

typedef struct NhuUE_EUTRA_Cap_v11a0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuUE_EUTRA_Cap_v11a0_IEsnonCriticalExtn;

typedef struct NhuUE_EUTRA_Cap_v11a0_IEs
{
	TknPres pres;
	NhuUE_EUTRA_Cap_v11a0_IEsue_Category_v11a0 ue_Category_v11a0;
	NhuMeasParams_v11a0 measParams_v11a0;
	NhuUE_EUTRA_Cap_v11a0_IEsnonCriticalExtn nonCriticalExtn;
} NhuUE_EUTRA_Cap_v11a0_IEs;

typedef struct NhuUE_EUTRA_Cap_v1180_IEs
{
	TknPres pres;
	NhuRF_Params_v1180 rf_Params_v1180;
	NhuMBMS_Params_r11 mbms_Params_r11;
	NhuUE_EUTRA_CapAddXDD_Mode_v1180 fdd_Add_UE_EUTRA_Capabilities_v1180;
	NhuUE_EUTRA_CapAddXDD_Mode_v1180 tdd_Add_UE_EUTRA_Capabilities_v1180;
	NhuUE_EUTRA_Cap_v11a0_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v1180_IEs;

/* Element ----- ue-Category-v1170 ------- */
typedef TknU32 NhuUE_EUTRA_Cap_v1170_IEsue_Category_v1170;

typedef struct NhuUE_EUTRA_Cap_v1170_IEs
{
	TknPres pres;
	NhuPhyLyrParams_v1170 phyLyrParams_v1170;
	NhuUE_EUTRA_Cap_v1170_IEsue_Category_v1170 ue_Category_v1170;
	NhuUE_EUTRA_Cap_v1180_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v1170_IEs;

typedef struct NhuUE_EUTRA_Cap_v1130_IEs
{
	TknPres pres;
	NhuPDCP_Params_v1130 pdcp_Params_v1130;
	NhuPhyLyrParams_v1130 phyLyrParams_v1130;
	NhuRF_Params_v1130 rf_Params_v1130;
	NhuMeasParams_v1130 measParams_v1130;
	NhuIRAT_ParamsCDMA2000_v1130 interRAT_ParamsCDMA2000_v1130;
	NhuOther_Params_r11 otherParams_r11;
	NhuUE_EUTRA_CapAddXDD_Mode_v1130 fdd_Add_UE_EUTRA_Capabilities_v1130;
	NhuUE_EUTRA_CapAddXDD_Mode_v1130 tdd_Add_UE_EUTRA_Capabilities_v1130;
	NhuUE_EUTRA_Cap_v1170_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v1130_IEs;

typedef struct NhuUE_EUTRA_Cap_v1090_IEs
{
	TknPres pres;
	NhuRF_Params_v1090 rf_Params_v1090;
	NhuUE_EUTRA_Cap_v1130_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v1090_IEs;

typedef struct NhuUE_EUTRA_Cap_v1060_IEs
{
	TknPres pres;
	NhuUE_EUTRA_CapAddXDD_Mode_v1060 fdd_Add_UE_EUTRA_Capabilities_v1060;
	NhuUE_EUTRA_CapAddXDD_Mode_v1060 tdd_Add_UE_EUTRA_Capabilities_v1060;
	NhuRF_Params_v1060 rf_Params_v1060;
	NhuUE_EUTRA_Cap_v1090_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v1060_IEs;

/* Element ----- ue-Category-v1020 ------- */
typedef TknU32 NhuUE_EUTRA_Cap_v1020_IEsue_Category_v1020;

/* Element ---------- featureGroupIndRel10-r10 ----------- */
typedef TknStrBSXL NhuUE_EUTRA_Cap_v1020_IEsfeatureGroupIndRel10_r10;
typedef struct NhuUE_EUTRA_Cap_v1020_IEs
{
	TknPres pres;
	NhuUE_EUTRA_Cap_v1020_IEsue_Category_v1020 ue_Category_v1020;
	NhuPhyLyrParams_v1020 phyLyrParams_v1020;
	NhuRF_Params_v1020 rf_Params_v1020;
	NhuMeasParams_v1020 measParams_v1020;
	NhuUE_EUTRA_Cap_v1020_IEsfeatureGroupIndRel10_r10 featureGroupIndRel10_r10;
	NhuIRAT_ParamsCDMA2000_1XRTT_v1020 interRAT_ParamsCDMA2000_v1020;
	NhuUE_BasedNetwPerfMeasParams_r10 ue_BasedNetwPerfMeasParams_r10;
	NhuIRAT_ParamsUTRA_TDD_v1020 interRAT_ParamsUTRA_TDD_v1020;
	NhuUE_EUTRA_Cap_v1060_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v1020_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuUE_EUTRA_Cap_v940_IEslateNonCriticalExtn;
typedef struct NhuUE_EUTRA_Cap_v940_IEs
{
	TknPres pres;
	NhuUE_EUTRA_Cap_v940_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuUE_EUTRA_Cap_v1020_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v940_IEs;

/* Element ----- deviceType-r9 ------- */
typedef enum enumNhuUE_EUTRA_Cap_v920_IEsdeviceTyp_r9
{
	NhuUE_EUTRA_Cap_v920_IEsdeviceTyp_r9noBenFromBatConsumpOptEnum
} EnumNhuUE_EUTRA_Cap_v920_IEsdeviceTyp_r9;
typedef TknU32 NhuUE_EUTRA_Cap_v920_IEsdeviceTyp_r9;

typedef struct NhuUE_EUTRA_Cap_v920_IEs
{
	TknPres pres;
	NhuPhyLyrParams_v920 phyLyrParams_v920;
	NhuIRAT_ParamsGERAN_v920 interRAT_ParamsGERAN_v920;
	NhuIRAT_ParamsUTRA_v920 interRAT_ParamsUTRA_v920;
	NhuIRAT_ParamsCDMA2000_1XRTT_v920 interRAT_ParamsCDMA2000_v920;
	NhuUE_EUTRA_Cap_v920_IEsdeviceTyp_r9 deviceTyp_r9;
	NhuCSG_ProximityIndParams_r9 csg_ProximityIndParams_r9;
	NhuNeighCellSI_AcquisitionParams_r9 neighCellSI_AcquisitionParams_r9;
	NhuSON_Params_r9 son_Params_r9;
	NhuUE_EUTRA_Cap_v940_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v920_IEs;

/* Element ----- ue-Category ------- */
typedef TknU32 NhuUE_EUTRA_Capue_Category;

/* Element ---------- featureGroupIndicators ----------- */
typedef TknStrBSXL NhuUE_EUTRA_CapfeatureGroupIndicators;
typedef struct NhuUE_EUTRA_CapinterRAT_Params
{
	TknPres pres;
	NhuIRAT_ParamsUTRA_FDD utraFDD;
	NhuIRAT_ParamsUTRA_TDD128 utraTDD128;
	NhuIRAT_ParamsUTRA_TDD384 utraTDD384;
	NhuIRAT_ParamsUTRA_TDD768 utraTDD768;
	NhuIRAT_ParamsGERAN geran;
	NhuIRAT_ParamsCDMA2000_HRPD cdma2000_HRPD;
	NhuIRAT_ParamsCDMA2000_1XRTT cdma2000_1xRTT;
} NhuUE_EUTRA_CapinterRAT_Params;

typedef struct NhuUE_EUTRA_Cap
{
	TknPres pres;
	NhuAccessStratumRls accessStratumRls;
	NhuUE_EUTRA_Capue_Category ue_Category;
	NhuPDCP_Params pdcp_Params;
	NhuPhyLyrParams phyLyrParams;
	NhuRF_Params rf_Params;
	NhuMeasParams measParams;
	NhuUE_EUTRA_CapfeatureGroupIndicators featureGroupIndicators;
	NhuUE_EUTRA_CapinterRAT_Params interRAT_Params;
	NhuUE_EUTRA_Cap_v920_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap;

/* Element ---------- featureGroupIndicators-r9 ----------- */
typedef TknStrBSXL NhuUE_EUTRA_CapAddXDD_Mode_r9featureGroupIndicators_r9;
/* Element ---------- featureGroupIndRel9Add-r9 ----------- */
typedef TknStrBSXL NhuUE_EUTRA_CapAddXDD_Mode_r9featureGroupIndRel9Add_r9;
typedef struct NhuUE_EUTRA_CapAddXDD_Mode_r9
{
	TknPres pres;
	NhuPhyLyrParams phyLyrParams_r9;
	NhuUE_EUTRA_CapAddXDD_Mode_r9featureGroupIndicators_r9 featureGroupIndicators_r9;
	NhuUE_EUTRA_CapAddXDD_Mode_r9featureGroupIndRel9Add_r9 featureGroupIndRel9Add_r9;
	NhuIRAT_ParamsGERAN interRAT_ParamsGERAN_r9;
	NhuIRAT_ParamsUTRA_v920 interRAT_ParamsUTRA_r9;
	NhuIRAT_ParamsCDMA2000_1XRTT_v920 interRAT_ParamsCDMA2000_r9;
	NhuNeighCellSI_AcquisitionParams_r9 neighCellSI_AcquisitionParams_r9;
} NhuUE_EUTRA_CapAddXDD_Mode_r9;

/* Element ----- voiceOverPS-HS-UTRA-FDD-r9 ------- */
typedef enum enumNhuIRAT_ParamsUTRA_v9c0voiceOverPS_HS_UTRA_FDD_r9
{
	NhuIRAT_ParamsUTRA_v9c0voiceOverPS_HS_UTRA_FDD_r9supportedEnum
} EnumNhuIRAT_ParamsUTRA_v9c0voiceOverPS_HS_UTRA_FDD_r9;
typedef TknU32 NhuIRAT_ParamsUTRA_v9c0voiceOverPS_HS_UTRA_FDD_r9;

/* Element ----- voiceOverPS-HS-UTRA-TDD128-r9 ------- */
typedef enum enumNhuIRAT_ParamsUTRA_v9c0voiceOverPS_HS_UTRA_TDD128_r9
{
	NhuIRAT_ParamsUTRA_v9c0voiceOverPS_HS_UTRA_TDD128_r9supportedEnum
} EnumNhuIRAT_ParamsUTRA_v9c0voiceOverPS_HS_UTRA_TDD128_r9;
typedef TknU32 NhuIRAT_ParamsUTRA_v9c0voiceOverPS_HS_UTRA_TDD128_r9;

/* Element ----- srvcc-FromUTRA-FDD-ToUTRA-FDD-r9 ------- */
typedef enum enumNhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_FDD_ToUTRA_FDD_r9
{
	NhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_FDD_ToUTRA_FDD_r9supportedEnum
} EnumNhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_FDD_ToUTRA_FDD_r9;
typedef TknU32 NhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_FDD_ToUTRA_FDD_r9;

/* Element ----- srvcc-FromUTRA-FDD-ToGERAN-r9 ------- */
typedef enum enumNhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_FDD_ToGERAN_r9
{
	NhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_FDD_ToGERAN_r9supportedEnum
} EnumNhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_FDD_ToGERAN_r9;
typedef TknU32 NhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_FDD_ToGERAN_r9;

/* Element ----- srvcc-FromUTRA-TDD128-ToUTRA-TDD128-r9 ------- */
typedef enum enumNhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_TDD128_ToUTRA_TDD128_r9
{
	NhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_TDD128_ToUTRA_TDD128_r9supportedEnum
} EnumNhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_TDD128_ToUTRA_TDD128_r9;
typedef TknU32 NhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_TDD128_ToUTRA_TDD128_r9;

/* Element ----- srvcc-FromUTRA-TDD128-ToGERAN-r9 ------- */
typedef enum enumNhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_TDD128_ToGERAN_r9
{
	NhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_TDD128_ToGERAN_r9supportedEnum
} EnumNhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_TDD128_ToGERAN_r9;
typedef TknU32 NhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_TDD128_ToGERAN_r9;

typedef struct NhuIRAT_ParamsUTRA_v9c0
{
	TknPres pres;
	NhuIRAT_ParamsUTRA_v9c0voiceOverPS_HS_UTRA_FDD_r9 voiceOverPS_HS_UTRA_FDD_r9;
	NhuIRAT_ParamsUTRA_v9c0voiceOverPS_HS_UTRA_TDD128_r9 voiceOverPS_HS_UTRA_TDD128_r9;
	NhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_FDD_ToUTRA_FDD_r9 srvcc_FromUTRA_FDD_ToUTRA_FDD_r9;
	NhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_FDD_ToGERAN_r9 srvcc_FromUTRA_FDD_ToGERAN_r9;
	NhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_TDD128_ToUTRA_TDD128_r9 srvcc_FromUTRA_TDD128_ToUTRA_TDD128_r9;
	NhuIRAT_ParamsUTRA_v9c0srvcc_FromUTRA_TDD128_ToGERAN_r9 srvcc_FromUTRA_TDD128_ToGERAN_r9;
} NhuIRAT_ParamsUTRA_v9c0;

/* Element ----- tm5-FDD-r9 ------- */
typedef enum enumNhuPhyLyrParams_v9d0tm5_FDD_r9
{
	NhuPhyLyrParams_v9d0tm5_FDD_r9supportedEnum
} EnumNhuPhyLyrParams_v9d0tm5_FDD_r9;
typedef TknU32 NhuPhyLyrParams_v9d0tm5_FDD_r9;

/* Element ----- tm5-TDD-r9 ------- */
typedef enum enumNhuPhyLyrParams_v9d0tm5_TDD_r9
{
	NhuPhyLyrParams_v9d0tm5_TDD_r9supportedEnum
} EnumNhuPhyLyrParams_v9d0tm5_TDD_r9;
typedef TknU32 NhuPhyLyrParams_v9d0tm5_TDD_r9;

typedef struct NhuPhyLyrParams_v9d0
{
	TknPres pres;
	NhuPhyLyrParams_v9d0tm5_FDD_r9 tm5_FDD_r9;
	NhuPhyLyrParams_v9d0tm5_TDD_r9 tm5_TDD_r9;
} NhuPhyLyrParams_v9d0;

typedef struct NhuSuppBandEUTRA_v9e0
{
	TknPres pres;
	NhuFreqBandIndicator_v9e0 bandEUTRA_v9e0;
} NhuSuppBandEUTRA_v9e0;

typedef struct NhuSuppBandLstEUTRA_v9e0
{
	TknU16 noComp;
	NhuSuppBandEUTRA_v9e0 *member;
}NhuSuppBandLstEUTRA_v9e0;

typedef struct NhuRF_Params_v9e0
{
	TknPres pres;
	NhuSuppBandLstEUTRA_v9e0 supportedBandLstEUTRA_v9e0;
} NhuRF_Params_v9e0;

/* Element ----- mfbi-UTRA-r9 ------- */
typedef enum enumNhuIRAT_ParamsUTRA_v9h0mfbi_UTRA_r9
{
	NhuIRAT_ParamsUTRA_v9h0mfbi_UTRA_r9supportedEnum
} EnumNhuIRAT_ParamsUTRA_v9h0mfbi_UTRA_r9;
typedef TknU32 NhuIRAT_ParamsUTRA_v9h0mfbi_UTRA_r9;

typedef struct NhuIRAT_ParamsUTRA_v9h0
{
	TknPres pres;
	NhuIRAT_ParamsUTRA_v9h0mfbi_UTRA_r9 mfbi_UTRA_r9;
} NhuIRAT_ParamsUTRA_v9h0;

/* Element ---------- modifiedMPR-Behavior-r10 ----------- */
typedef TknStrBSXL NhuRF_Params_v10f0modifiedMPR_Behavior_r10;
typedef struct NhuRF_Params_v10f0
{
	TknPres pres;
	NhuRF_Params_v10f0modifiedMPR_Behavior_r10 modifiedMPR_Behavior_r10;
} NhuRF_Params_v10f0;

typedef struct NhuUE_EUTRA_Cap_v10f0_IEsnonCriticalExtn
{
	TknPres pres;
} NhuUE_EUTRA_Cap_v10f0_IEsnonCriticalExtn;

typedef struct NhuUE_EUTRA_Cap_v10f0_IEs
{
	TknPres pres;
	NhuRF_Params_v10f0 rf_Params_v10f0;
	NhuUE_EUTRA_Cap_v10f0_IEsnonCriticalExtn nonCriticalExtn;
} NhuUE_EUTRA_Cap_v10f0_IEs;

typedef struct NhuUE_EUTRA_Cap_v10c0_IEs
{
	TknPres pres;
	NhuOTDOA_PositioningCapabilities_r10 otdoa_PositioningCapabilities_r10;
	NhuUE_EUTRA_Cap_v10f0_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v10c0_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuUE_EUTRA_Cap_v9h0_IEslateNonCriticalExtn;
typedef struct NhuUE_EUTRA_Cap_v9h0_IEs
{
	TknPres pres;
	NhuIRAT_ParamsUTRA_v9h0 interRAT_ParamsUTRA_v9h0;
	NhuUE_EUTRA_Cap_v9h0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuUE_EUTRA_Cap_v10c0_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v9h0_IEs;

typedef struct NhuUE_EUTRA_Cap_v9e0_IEs
{
	TknPres pres;
	NhuRF_Params_v9e0 rf_Params_v9e0;
	NhuUE_EUTRA_Cap_v9h0_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v9e0_IEs;

typedef struct NhuUE_EUTRA_Cap_v9d0_IEs
{
	TknPres pres;
	NhuPhyLyrParams_v9d0 phyLyrParams_v9d0;
	NhuUE_EUTRA_Cap_v9e0_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v9d0_IEs;

typedef struct NhuUE_EUTRA_Cap_v9c0_IEs
{
	TknPres pres;
	NhuIRAT_ParamsUTRA_v9c0 interRAT_ParamsUTRA_v9c0;
	NhuUE_EUTRA_Cap_v9d0_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v9c0_IEs;

/* Element ---------- featureGroupIndRel9Add-r9 ----------- */
typedef TknStrBSXL NhuUE_EUTRA_Cap_v9a0_IEsfeatureGroupIndRel9Add_r9;
typedef struct NhuUE_EUTRA_Cap_v9a0_IEs
{
	TknPres pres;
	NhuUE_EUTRA_Cap_v9a0_IEsfeatureGroupIndRel9Add_r9 featureGroupIndRel9Add_r9;
	NhuUE_EUTRA_CapAddXDD_Mode_r9 fdd_Add_UE_EUTRA_Capabilities_r9;
	NhuUE_EUTRA_CapAddXDD_Mode_r9 tdd_Add_UE_EUTRA_Capabilities_r9;
	NhuUE_EUTRA_Cap_v9c0_IEs nonCriticalExtn;
} NhuUE_EUTRA_Cap_v9a0_IEs;

typedef struct NhuVarConnEstFailReport_r11
{
	TknPres pres;
	NhuConnEstFailReport_r11 connEstFailReport_r11;
	NhuPLMN_Identity plmn_Identity_r11;
} NhuVarConnEstFailReport_r11;

typedef struct NhuVarLogMeasConfig_r10
{
	TknPres pres;
	NhuAreaCfg_r10 areaCfg_r10;
	NhuLoggingDuration_r10 loggingDuration_r10;
	NhuLoggingInterval_r10 loggingInterval_r10;
} NhuVarLogMeasConfig_r10;

typedef struct NhuVarLogMeasConfig_r11
{
	TknPres pres;
	NhuAreaCfg_r10 areaCfg_r10;
	NhuAreaCfg_v1130 areaCfg_v1130;
	NhuLoggingDuration_r10 loggingDuration_r10;
	NhuLoggingInterval_r10 loggingInterval_r10;
} NhuVarLogMeasConfig_r11;

typedef struct NhuLogMeasInfoLst2_r10
{
	TknU16 noComp;
	NhuLogMeasInfo_r10 *member;
}NhuLogMeasInfoLst2_r10;

/* Element ---------- traceRecordingSessionRef-r10 ----------- */
typedef TknStrOSXL NhuVarLogMeasReport_r10traceRecordingSessionRef_r10;
/* Element ---------- tce-Id-r10 ----------- */
typedef TknStrOSXL NhuVarLogMeasReport_r10tce_Id_r10;
typedef struct NhuVarLogMeasReport_r10
{
	TknPres pres;
	NhuTraceReference_r10 traceReference_r10;
	NhuVarLogMeasReport_r10traceRecordingSessionRef_r10 traceRecordingSessionRef_r10;
	NhuVarLogMeasReport_r10tce_Id_r10 tce_Id_r10;
	NhuPLMN_Identity plmn_Identity_r10;
	NhuAbsoluteTimeInfo_r10 absoluteTimeInfo_r10;
	NhuLogMeasInfoLst2_r10 logMeasInfoLst_r10;
} NhuVarLogMeasReport_r10;

/* Element ---------- traceRecordingSessionRef-r10 ----------- */
typedef TknStrOSXL NhuVarLogMeasReport_r11traceRecordingSessionRef_r10;
/* Element ---------- tce-Id-r10 ----------- */
typedef TknStrOSXL NhuVarLogMeasReport_r11tce_Id_r10;
typedef struct NhuVarLogMeasReport_r11
{
	TknPres pres;
	NhuTraceReference_r10 traceReference_r10;
	NhuVarLogMeasReport_r11traceRecordingSessionRef_r10 traceRecordingSessionRef_r10;
	NhuVarLogMeasReport_r11tce_Id_r10 tce_Id_r10;
	NhuPLMN_IdentityLst3_r11 plmn_IdentityLst_r11;
	NhuAbsoluteTimeInfo_r10 absoluteTimeInfo_r10;
	NhuLogMeasInfoLst2_r10 logMeasInfoLst_r10;
} NhuVarLogMeasReport_r11;

/* Element ----- s-Measure ------- */
typedef TknS32 NhuVarMeasConfigs_Measure;

typedef struct NhuVarMeasConfigspeedStateParssetup
{
	TknPres pres;
	NhuMobilityStateParams mobilityStateParams;
	NhuSpeedStateScaleFactors timeToTrigger_SF;
} NhuVarMeasConfigspeedStateParssetup;

typedef struct NhuVarMeasConfigspeedStatePars
{
	TknU8 choice;
	union {
		NhuVarMeasConfigspeedStateParssetup setup;
	} val;
} NhuVarMeasConfigspeedStatePars;

/* Element ----- allowInterruptions-r11 ------- */
typedef TknU8 NhuVarMeasConfigallowInterruptions_r11;

typedef struct NhuVarMeasConfig
{
	TknPres pres;
	NhuMeasIdToAddModLst measIdLst;
	NhuMeasObjectToAddModLst measObjectLst;
	NhuMeasObjectToAddModLst_v9e0 measObjectLst_v9i0;
	NhuReportConfigToAddModLst reportConfigLst;
	NhuQuantityConfig quantityConfig;
	NhuVarMeasConfigs_Measure s_Measure;
	NhuVarMeasConfigspeedStatePars speedStatePars;
	NhuVarMeasConfigallowInterruptions_r11 allowInterruptions_r11;
} NhuVarMeasConfig;

typedef struct NhuCellsTriggeredLstMemberphysCellIdUTRA
{
	TknU8 choice;
	union {
		NhuPhysCellIdUTRA_FDD fdd;
		NhuPhysCellIdUTRA_TDD tdd;
	} val;
} NhuCellsTriggeredLstMemberphysCellIdUTRA;

typedef struct NhuCellsTriggeredLstMemberphysCellIdGERAN
{
	TknPres pres;
	NhuCarrierFreqGERAN carrierFreq;
	NhuPhysCellIdGERAN physCellId;
} NhuCellsTriggeredLstMemberphysCellIdGERAN;

typedef struct NhuCellsTriggeredLstMember
{
	TknU8 choice;
	union {
		NhuPhysCellId physCellIdEUTRA;
		NhuCellsTriggeredLstMemberphysCellIdUTRA physCellIdUTRA;
		NhuCellsTriggeredLstMemberphysCellIdGERAN physCellIdGERAN;
		NhuPhysCellIdCDMA2000 physCellIdCDMA2000;
	} val;
} NhuCellsTriggeredLstMember;

typedef struct NhuCellsTriggeredLst
{
	TknU16 noComp;
	NhuCellsTriggeredLstMember *member;
}NhuCellsTriggeredLst;

/* Element ----- numberOfReportsSent ------- */
typedef TknS32 NhuVarMeasReportnumberOfReportsSent;

typedef struct NhuVarMeasReport
{
	TknPres pres;
	NhuMeasId measId;
	NhuCellsTriggeredLst cellsTriggeredLst;
	NhuVarMeasReportnumberOfReportsSent numberOfReportsSent;
} NhuVarMeasReport;

typedef struct NhuVarMeasReportLst
{
	TknU16 noComp;
	NhuVarMeasReport *member;
}NhuVarMeasReportLst;

typedef struct NhuVarRLF_Report_r10
{
	TknPres pres;
	NhuRLF_Report_r9 rlf_Report_r10;
	NhuPLMN_Identity plmn_Identity_r10;
} NhuVarRLF_Report_r10;

typedef struct NhuVarRLF_Report_r11
{
	TknPres pres;
	NhuRLF_Report_r9 rlf_Report_r10;
	NhuPLMN_IdentityLst3_r11 plmn_IdentityLst_r11;
} NhuVarRLF_Report_r11;

typedef struct NhuVarShortMAC_Input
{
	TknPres pres;
	NhuCellIdentity cellIdentity;
	NhuPhysCellId physCellId;
	NhuC_RNTI c_RNTI;
} NhuVarShortMAC_Input;

/* Element ---------- handoverCommandMessage ----------- */
typedef TknStrOSXL NhuHovrCmd_r8_IEshandoverCmdMsg;
typedef struct NhuHovrCmd_r8_IEsnonCriticalExtn
{
	TknPres pres;
} NhuHovrCmd_r8_IEsnonCriticalExtn;

typedef struct NhuHovrCmd_r8_IEs
{
	TknPres pres;
	NhuHovrCmd_r8_IEshandoverCmdMsg handoverCmdMsg;
	NhuHovrCmd_r8_IEsnonCriticalExtn nonCriticalExtn;
} NhuHovrCmd_r8_IEs;

typedef struct NhuHovrCmdcriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuHovrCmd_r8_IEs handoverCmd_r8;
	} val;
} NhuHovrCmdcriticalExtnsc1;

typedef struct NhuHovrCmdcriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuHovrCmdcriticalExtnscriticalExtnsFuture;

typedef struct NhuHovrCmdcriticalExtns
{
	TknU8 choice;
	union {
		NhuHovrCmdcriticalExtnsc1 c1;
		NhuHovrCmdcriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuHovrCmdcriticalExtns;

typedef struct NhuHovrCmd
{
	TknPres pres;
	NhuHovrCmdcriticalExtns criticalExtns;
} NhuHovrCmd;

/* Element ---------- sourceSystemInformationBlockType1Ext ----------- */
typedef TknStrOSXL NhuAS_Configextaddgrp_1sourceSysInfoBlockTyp1Ext;
typedef struct NhuAS_Configextaddgrp_1
{
	TknPres pres;
	NhuAS_Configextaddgrp_1sourceSysInfoBlockTyp1Ext sourceSysInfoBlockTyp1Ext;
	NhuOtherConfig_r9 sourceOtherConfig_r9;
} NhuAS_Configextaddgrp_1;

typedef struct NhuAS_Configextaddgrp_2
{
	TknPres pres;
	NhuSCellToAddModLst_r10 sourceSCellConfigLst_r10;
} NhuAS_Configextaddgrp_2;

typedef struct NhuAS_Config
{
	TknPres pres;
	NhuMeasConfig sourceMeasConfig;
	NhuRadioResourceConfigDedicated sourceRadioResourceConfig;
	NhuSecAlgorithmConfig sourceSecAlgorithmConfig;
	NhuC_RNTI sourceUE_Identity;
	NhuMasterInfoBlock sourceMasterInfoBlock;
	NhuSysInfoBlockTyp1 sourceSysInfoBlockTyp1;
	NhuSysInfoBlockTyp2 sourceSysInfoBlockTyp2;
	NhuAntennaInfoCmn antennaInfoCmn;
	NhuARFCN_ValueEUTRA sourceDl_CarrierFreq;
	NhuAS_Configextaddgrp_1 extaddgrp_1;
	NhuAS_Configextaddgrp_2 extaddgrp_2;
} NhuAS_Config;

typedef struct NhuCandidateCellInfo_r10extaddgrp_1
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_v9e0 dl_CarrierFreq_v1090;
} NhuCandidateCellInfo_r10extaddgrp_1;

typedef struct NhuCandidateCellInfo_r10
{
	TknPres pres;
	NhuPhysCellId physCellId_r10;
	NhuARFCN_ValueEUTRA dl_CarrierFreq_r10;
	NhuRSRP_Range rsrpResult_r10;
	NhuRSRQ_Range rsrqResult_r10;
	NhuCandidateCellInfo_r10extaddgrp_1 extaddgrp_1;
} NhuCandidateCellInfo_r10;

typedef struct NhuCandidateCellInfoLst_r10
{
	TknU16 noComp;
	NhuCandidateCellInfo_r10 *member;
}NhuCandidateCellInfoLst_r10;

/* Element ----- ue-InactiveTime ------- */
typedef enum enumNhuRRM_Configue_InactiveTime
{
	NhuRRM_Configue_InactiveTimes1Enum,
	NhuRRM_Configue_InactiveTimes2Enum,
	NhuRRM_Configue_InactiveTimes3Enum,
	NhuRRM_Configue_InactiveTimes5Enum,
	NhuRRM_Configue_InactiveTimes7Enum,
	NhuRRM_Configue_InactiveTimes10Enum,
	NhuRRM_Configue_InactiveTimes15Enum,
	NhuRRM_Configue_InactiveTimes20Enum,
	NhuRRM_Configue_InactiveTimes25Enum,
	NhuRRM_Configue_InactiveTimes30Enum,
	NhuRRM_Configue_InactiveTimes40Enum,
	NhuRRM_Configue_InactiveTimes50Enum,
	NhuRRM_Configue_InactiveTimemin1Enum,
	NhuRRM_Configue_InactiveTimemin1s20cEnum,
	NhuRRM_Configue_InactiveTimemin1s40Enum,
	NhuRRM_Configue_InactiveTimemin2Enum,
	NhuRRM_Configue_InactiveTimemin2s30Enum,
	NhuRRM_Configue_InactiveTimemin3Enum,
	NhuRRM_Configue_InactiveTimemin3s30Enum,
	NhuRRM_Configue_InactiveTimemin4Enum,
	NhuRRM_Configue_InactiveTimemin5Enum,
	NhuRRM_Configue_InactiveTimemin6Enum,
	NhuRRM_Configue_InactiveTimemin7Enum,
	NhuRRM_Configue_InactiveTimemin8Enum,
	NhuRRM_Configue_InactiveTimemin9Enum,
	NhuRRM_Configue_InactiveTimemin10Enum,
	NhuRRM_Configue_InactiveTimemin12Enum,
	NhuRRM_Configue_InactiveTimemin14Enum,
	NhuRRM_Configue_InactiveTimemin17Enum,
	NhuRRM_Configue_InactiveTimemin20Enum,
	NhuRRM_Configue_InactiveTimemin24Enum,
	NhuRRM_Configue_InactiveTimemin28Enum,
	NhuRRM_Configue_InactiveTimemin33Enum,
	NhuRRM_Configue_InactiveTimemin38Enum,
	NhuRRM_Configue_InactiveTimemin44Enum,
	NhuRRM_Configue_InactiveTimemin50Enum,
	NhuRRM_Configue_InactiveTimehr1Enum,
	NhuRRM_Configue_InactiveTimehr1min30Enum,
	NhuRRM_Configue_InactiveTimehr2Enum,
	NhuRRM_Configue_InactiveTimehr2min30Enum,
	NhuRRM_Configue_InactiveTimehr3Enum,
	NhuRRM_Configue_InactiveTimehr3min30Enum,
	NhuRRM_Configue_InactiveTimehr4Enum,
	NhuRRM_Configue_InactiveTimehr5Enum,
	NhuRRM_Configue_InactiveTimehr6Enum,
	NhuRRM_Configue_InactiveTimehr8Enum,
	NhuRRM_Configue_InactiveTimehr10Enum,
	NhuRRM_Configue_InactiveTimehr13Enum,
	NhuRRM_Configue_InactiveTimehr16Enum,
	NhuRRM_Configue_InactiveTimehr20Enum,
	NhuRRM_Configue_InactiveTimeday1Enum,
	NhuRRM_Configue_InactiveTimeday1hr12Enum,
	NhuRRM_Configue_InactiveTimeday2Enum,
	NhuRRM_Configue_InactiveTimeday2hr12Enum,
	NhuRRM_Configue_InactiveTimeday3Enum,
	NhuRRM_Configue_InactiveTimeday4Enum,
	NhuRRM_Configue_InactiveTimeday5Enum,
	NhuRRM_Configue_InactiveTimeday7Enum,
	NhuRRM_Configue_InactiveTimeday10Enum,
	NhuRRM_Configue_InactiveTimeday14Enum,
	NhuRRM_Configue_InactiveTimeday19Enum,
	NhuRRM_Configue_InactiveTimeday24Enum,
	NhuRRM_Configue_InactiveTimeday30Enum,
	NhuRRM_Configue_InactiveTimedayMoreThan30Enum
} EnumNhuRRM_Configue_InactiveTime;
typedef TknU32 NhuRRM_Configue_InactiveTime;

typedef struct NhuRRM_Configextaddgrp_1
{
	TknPres pres;
	NhuCandidateCellInfoLst_r10 candidateCellInfoLst_r10;
} NhuRRM_Configextaddgrp_1;

typedef struct NhuRRM_Config
{
	TknPres pres;
	NhuRRM_Configue_InactiveTime ue_InactiveTime;
	NhuRRM_Configextaddgrp_1 extaddgrp_1;
} NhuRRM_Config;

/* Element ---------- Key-eNodeB-Star ----------- */
typedef TknStrBSXL NhuKey_eNodeB_Star;
typedef struct NhuAdditionalReestabInfo
{
	TknPres pres;
	NhuCellIdentity cellIdentity;
	NhuKey_eNodeB_Star key_eNodeB_Star;
	NhuShortMAC_I shortMAC_I;
} NhuAdditionalReestabInfo;

typedef struct NhuAdditionalReestabInfoLst
{
	TknU16 noComp;
	NhuAdditionalReestabInfo *member;
}NhuAdditionalReestabInfoLst;

typedef struct NhuReestbInfo
{
	TknPres pres;
	NhuPhysCellId sourcePhysCellId;
	NhuShortMAC_I targetCellShortMAC_I;
	NhuAdditionalReestabInfoLst additionalReestabInfoLst;
} NhuReestbInfo;

typedef struct NhuAS_Ctxt
{
	TknPres pres;
	NhuReestbInfo reestablishmentInfo;
} NhuAS_Ctxt;

typedef struct NhuAS_Config_v9e0
{
	TknPres pres;
	NhuARFCN_ValueEUTRA_v9e0 sourceDl_CarrierFreq_v9e0;
} NhuAS_Config_v9e0;

/* Element ---------- idc-Indication-r11 ----------- */
typedef TknStrOSXL NhuAS_Ctxt_v1130idc_Ind_r11;
/* Element ---------- mbmsInterestIndication-r11 ----------- */
typedef TknStrOSXL NhuAS_Ctxt_v1130mbmsInterestInd_r11;
/* Element ---------- powerPrefIndication-r11 ----------- */
typedef TknStrOSXL NhuAS_Ctxt_v1130powerPrefInd_r11;
typedef struct NhuAS_Ctxt_v1130
{
	TknPres pres;
	NhuAS_Ctxt_v1130idc_Ind_r11 idc_Ind_r11;
	NhuAS_Ctxt_v1130mbmsInterestInd_r11 mbmsInterestInd_r11;
	NhuAS_Ctxt_v1130powerPrefInd_r11 powerPrefInd_r11;
} NhuAS_Ctxt_v1130;

typedef struct NhuHovrPrepInfo_v1130_IEsnonCriticalExtn
{
	TknPres pres;
} NhuHovrPrepInfo_v1130_IEsnonCriticalExtn;

typedef struct NhuHovrPrepInfo_v1130_IEs
{
	TknPres pres;
	NhuAS_Ctxt_v1130 as_Ctxt_v1130;
	NhuHovrPrepInfo_v1130_IEsnonCriticalExtn nonCriticalExtn;
} NhuHovrPrepInfo_v1130_IEs;

typedef struct NhuHovrPrepInfo_v9e0_IEs
{
	TknPres pres;
	NhuAS_Config_v9e0 as_Config_v9e0;
	NhuHovrPrepInfo_v1130_IEs nonCriticalExtn;
} NhuHovrPrepInfo_v9e0_IEs;

/* Element ---------- lateNonCriticalExtension ----------- */
typedef TknStrOSXL NhuHovrPrepInfo_v9d0_IEslateNonCriticalExtn;
typedef struct NhuHovrPrepInfo_v9d0_IEs
{
	TknPres pres;
	NhuHovrPrepInfo_v9d0_IEslateNonCriticalExtn lateNonCriticalExtn;
	NhuHovrPrepInfo_v9e0_IEs nonCriticalExtn;
} NhuHovrPrepInfo_v9d0_IEs;

/* Element ----- ue-ConfigRelease-r9 ------- */
typedef enum enumNhuHovrPrepInfo_v920_IEsue_ConfigRls_r9
{
	NhuHovrPrepInfo_v920_IEsue_ConfigRls_r9rel9Enum,
	NhuHovrPrepInfo_v920_IEsue_ConfigRls_r9rel10Enum,
	NhuHovrPrepInfo_v920_IEsue_ConfigRls_r9rel11Enum,
	NhuHovrPrepInfo_v920_IEsue_ConfigRls_r9spare5Enum,
	NhuHovrPrepInfo_v920_IEsue_ConfigRls_r9spare4Enum,
	NhuHovrPrepInfo_v920_IEsue_ConfigRls_r9spare3Enum,
	NhuHovrPrepInfo_v920_IEsue_ConfigRls_r9spare2Enum,
	NhuHovrPrepInfo_v920_IEsue_ConfigRls_r9spare1Enum
} EnumNhuHovrPrepInfo_v920_IEsue_ConfigRls_r9;
typedef TknU32 NhuHovrPrepInfo_v920_IEsue_ConfigRls_r9;

typedef struct NhuHovrPrepInfo_v920_IEs
{
	TknPres pres;
	NhuHovrPrepInfo_v920_IEsue_ConfigRls_r9 ue_ConfigRls_r9;
	NhuHovrPrepInfo_v9d0_IEs nonCriticalExtn;
} NhuHovrPrepInfo_v920_IEs;

typedef struct NhuHovrPrepInfo_r8_IEs
{
	TknPres pres;
	NhuUE_CapRAT_ContLst ue_RadioAccessCapInfo;
	NhuAS_Config as_Config;
	NhuRRM_Config rrm_Config;
	NhuAS_Ctxt as_Ctxt;
	NhuHovrPrepInfo_v920_IEs nonCriticalExtn;
} NhuHovrPrepInfo_r8_IEs;

typedef struct NhuHovrPrepInfocriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuHovrPrepInfo_r8_IEs handoverPrepInfo_r8;
	} val;
} NhuHovrPrepInfocriticalExtnsc1;

typedef struct NhuHovrPrepInfocriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuHovrPrepInfocriticalExtnscriticalExtnsFuture;

typedef struct NhuHovrPrepInfocriticalExtns
{
	TknU8 choice;
	union {
		NhuHovrPrepInfocriticalExtnsc1 c1;
		NhuHovrPrepInfocriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuHovrPrepInfocriticalExtns;

typedef struct NhuHovrPrepInfo
{
	TknPres pres;
	NhuHovrPrepInfocriticalExtns criticalExtns;
} NhuHovrPrepInfo;

/* Element ---------- ue-RadioAccessCapabilityInfo ----------- */
typedef TknStrOSXL NhuUERadioAccessCapInfo_r8_IEsue_RadioAccessCapInfo;
typedef struct NhuUERadioAccessCapInfo_r8_IEsnonCriticalExtn
{
	TknPres pres;
} NhuUERadioAccessCapInfo_r8_IEsnonCriticalExtn;

typedef struct NhuUERadioAccessCapInfo_r8_IEs
{
	TknPres pres;
	NhuUERadioAccessCapInfo_r8_IEsue_RadioAccessCapInfo ue_RadioAccessCapInfo;
	NhuUERadioAccessCapInfo_r8_IEsnonCriticalExtn nonCriticalExtn;
} NhuUERadioAccessCapInfo_r8_IEs;

typedef struct NhuUERadioAccessCapInfocriticalExtnsc1
{
	TknU8 choice;
	union {
		NhuUERadioAccessCapInfo_r8_IEs ueRadioAccessCapInfo_r8;
	} val;
} NhuUERadioAccessCapInfocriticalExtnsc1;

typedef struct NhuUERadioAccessCapInfocriticalExtnscriticalExtnsFuture
{
	TknPres pres;
} NhuUERadioAccessCapInfocriticalExtnscriticalExtnsFuture;

typedef struct NhuUERadioAccessCapInfocriticalExtns
{
	TknU8 choice;
	union {
		NhuUERadioAccessCapInfocriticalExtnsc1 c1;
		NhuUERadioAccessCapInfocriticalExtnscriticalExtnsFuture criticalExtnsFuture;
	} val;
} NhuUERadioAccessCapInfocriticalExtns;

typedef struct NhuUERadioAccessCapInfo
{
	TknPres pres;
	NhuUERadioAccessCapInfocriticalExtns criticalExtns;
} NhuUERadioAccessCapInfo;


#endif
/**********************************************************************
         End of file:     nhu_asn.x@@/main/3 - Thu Jun 30 17:23:38 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---                 ch           1. RRC LTE Initial Release.
/main/3      ---      nhu_asn_x_001.main_2 sbalakrishna 1. Updated for Release of 3.1.
*********************************************************************91*/
