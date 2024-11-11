/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : ADC_SAR
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_RTD_3_0_0_P01_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file
*
*   @addtogroup adc_driver_config Adc Driver Configuration
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Adc_PBcfg.h"
#include "Adc_Ipw_PBcfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define ADC_VENDOR_ID_PBCFG_C                    43
#define ADC_AR_RELEASE_MAJOR_VERSION_PBCFG_C     4
#define ADC_AR_RELEASE_MINOR_VERSION_PBCFG_C     7
#define ADC_AR_RELEASE_REVISION_VERSION_PBCFG_C  0
#define ADC_SW_MAJOR_VERSION_PBCFG_C             3
#define ADC_SW_MINOR_VERSION_PBCFG_C             0
#define ADC_SW_PATCH_VERSION_PBCFG_C             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Check if Adc_PBcfg.c file and Adc_PBcfg.h file are of the same vendor */
#if (ADC_VENDOR_ID_PBCFG_C != ADC_VENDOR_ID_PBCFG)
    #error "Adc_PBcfg.c and Adc_PBcfg.h have different vendor ids"
#endif

/* Check if Adc_PBcfg.c file and Adc_PBcfg.h file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_PBCFG_C != ADC_AR_RELEASE_MAJOR_VERSION_PBCFG) || \
     (ADC_AR_RELEASE_MINOR_VERSION_PBCFG_C != ADC_AR_RELEASE_MINOR_VERSION_PBCFG) || \
     (ADC_AR_RELEASE_REVISION_VERSION_PBCFG_C != ADC_AR_RELEASE_REVISION_VERSION_PBCFG) \
    )
    #error "AutoSar Version Numbers of Adc_PBcfg.c and Adc_PBcfg.h are different"
#endif

/* Check if Adc_PBcfg.c file and Adc_PBcfg.h file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_PBCFG_C != ADC_SW_MAJOR_VERSION_PBCFG) || \
     (ADC_SW_MINOR_VERSION_PBCFG_C != ADC_SW_MINOR_VERSION_PBCFG) || \
     (ADC_SW_PATCH_VERSION_PBCFG_C != ADC_SW_PATCH_VERSION_PBCFG) \
    )
  #error "Software Version Numbers of Adc_PBcfg.c and Adc_PBcfg.h are different"
#endif

/* Check if Adc_PBcfg.c file and Adc_Ipw_PBcfg.h file are of the same vendor */
#if (ADC_VENDOR_ID_PBCFG_C != ADC_IPW_VENDOR_ID_PBCFG)
    #error "Adc_PBcfg.c and Adc_Ipw_PBcfg.h have different vendor ids"
#endif

/* Check if Adc_PBcfg.c file and Adc_Ipw_PBcfg.h file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_PBCFG_C != ADC_IPW_AR_RELEASE_MAJOR_VERSION_PBCFG) || \
     (ADC_AR_RELEASE_MINOR_VERSION_PBCFG_C != ADC_IPW_AR_RELEASE_MINOR_VERSION_PBCFG) || \
     (ADC_AR_RELEASE_REVISION_VERSION_PBCFG_C != ADC_IPW_AR_RELEASE_REVISION_VERSION_PBCFG) \
    )
    #error "AutoSar Version Numbers of Adc_PBcfg.c and Adc_Ipw_PBcfg.h are different"
#endif

/* Check if Adc_PBcfg.c file and Adc_Ipw_PBcfg.h file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_PBCFG_C != ADC_IPW_SW_MAJOR_VERSION_PBCFG) || \
     (ADC_SW_MINOR_VERSION_PBCFG_C != ADC_IPW_SW_MINOR_VERSION_PBCFG) || \
     (ADC_SW_PATCH_VERSION_PBCFG_C != ADC_IPW_SW_PATCH_VERSION_PBCFG) \
    )
  #error "Software Version Numbers of Adc_PBcfg.c and Adc_Ipw_PBcfg.h are different"
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

#define ADC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Adc_MemMap.h"


/**
* @brief          Group Assignments on ADC0.
*
*/
static const Adc_ChannelType Adc_Group0_Assignment_0[ADC_CFGSET_GROUP_0_CHANNELS] =
{
    0U
};


/**
* @brief          Group Assignments on ADC0.
*
*/
static const Adc_ChannelType Adc_Group1_Assignment_0[ADC_CFGSET_GROUP_1_CHANNELS] =
{
    2U
};


/**
* @brief          Group Assignments on ADC0.
*
*/
static const Adc_ChannelType Adc_Group2_Assignment_0[ADC_CFGSET_GROUP_2_CHANNELS] =
{
    1U
};


/**
* @brief          Group Assignments on ADC0.
*
*/
static const Adc_ChannelType Adc_Group3_Assignment_0[ADC_CFGSET_GROUP_3_CHANNELS] =
{
    3U
};


/**
* @brief          Group Assignments on ADC1.
*
*/
static const Adc_ChannelType Adc_Group4_Assignment_1[ADC_CFGSET_GROUP_4_CHANNELS] =
{
    0U
};


/**
* @brief          Group Assignments on ADC1.
*
*/
static const Adc_ChannelType Adc_Group5_Assignment_1[ADC_CFGSET_GROUP_5_CHANNELS] =
{
    1U
};

/**
* @brief          Definition of all ADC groups for configuration variant.
*/
static const Adc_GroupConfigurationType Adc_GroupsCfg[] =
{
    /**< @brief Group0 -- Logical Unit Id 0 -- Hardware Unit ADC0 */
    {
        /**< @brief Index of group */
        0U, /* GroupId */
        /**< @brief ADC Logical Unit Id that the group belongs to */
        (Adc_HwUnitType)0, /* AdcLogicalUnitId */
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE, /* AccessMode */
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT, /* Mode */
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL, /* Type */
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief Priority configured */
        (Adc_GroupPriorityType)ADC_GROUP_PRIORITY(0), /* Priority */
#endif /* ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART, /* ReplacementMode */
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW, /* TriggerSource */
#if (STD_ON == ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger source for the group */
        0U, /* HwTriggerSource */
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE, /* TriggerEdge */
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */
        NULL_PTR, /* Notification */
#endif /* (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
#if (ADC_ENABLE_INITIAL_NOTIFICATION == STD_ON)
        /**< @brief Extra notification function */
        NULL_PTR, /* ExtraNotification */
#endif /* (ADC_ENABLE_INITIAL_NOTIFICATION == STD_ON) */
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR, /* BufferMode */
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
        /**< @brief Index of the group with AdcEnableChDisableChGroup enabled */
        (Adc_GroupType)ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX, /* EnableChDisableChGroupIndex */
#endif /* (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) */
        /**< @brief Number of streaming samples */
        (Adc_StreamNumSampleType)ADC_STREAMING_NUM_SAMPLES(1), /* NumSamples */
#if (ADC_ENABLE_GROUP_STREAMING_RESULTS_REORDER == STD_ON)
        /**< @brief Arrange the adc results as multiple sets of group result buffer */
        (boolean)FALSE, /* StreamResultGroupMultiSets */
#endif /* (ADC_ENABLE_GROUP_STREAMING_RESULTS_REORDER == STD_ON) */
        /**< @brief Channels assigned to the group*/
        Adc_Group0_Assignment_0, /* AssignmentPtr */
        /**< @brief Number of channels in the group*/
        (Adc_ChannelIndexType)ADC_CFGSET_GROUP_0_CHANNELS, /* AssignedChannelCount */
        /**< @brief Last Channel configured */
        (Adc_ChannelType)(ADC_ID_CHANNEL_U8(33)), /* LastCh */
        /**< @brief First Channel configured */
        (Adc_ChannelType)(ADC_ID_CHANNEL_U8(33)), /* FirstCh */
        /**< @brief Enables or Disables the ADC and DMA interrupts */
        (uint8)(STD_ON), /* AdcWithoutInterrupt */
        /**< @brief Enables or Disables configuring external DMA channel in the group */
        (uint8)(STD_OFF), /* AdcExtDMAChanEnable */
        /**< @brief When true, disables completely DMA configuration done by ADC driver for the group */
        (boolean)FALSE, /* AdcWithoutDma */
#if (STD_ON == ADC_OPTIMIZE_DMA_STREAMING_GROUPS)
        /**< @brief Enables or Disables the ADC optimize DMA streaming groups feature */
        (boolean)(FALSE), /* AdcOptimizeDmaStream */
        /**< @brief Enable/disable half interrupt for group with optimize DMA streaming groups */
        (boolean)FALSE, /* HalfInterrupt */
#endif /* (STD_ON == ADC_OPTIMIZE_DMA_STREAMING_GROUPS) */
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        /**< @brief Enables or disables the usage of limit checking for an ADC group. */
        (boolean)FALSE, /* AdcGroupLimitcheck */
#endif /* (STD_ON == ADC_ENABLE_LIMIT_CHECK) */
        { { 0x0U, 0x2U, 0x0U } }, /* AssignedChannelMask */
#if (ADC_CTU_HW_TRIGGER_OPTIMIZATION == STD_ON)
        /**< @brief First position of channel in BCTU channel list or CTU command list. */
        0, /* CtuTrigListPos */
#endif /* (ADC_CTU_HW_TRIGGER_OPTIMIZATION == STD_ON) */
#ifdef ADC_AVERAGING_FUNCTIONALITY_SUPPORT
#if (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF)
        &AdcIpwGroupConfig_0 /* AdcIpwGroupConfigPtr */
#endif /* (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF) */
#endif /* ADC_AVERAGING_FUNCTIONALITY_SUPPORT */
    },
    /**< @brief Group1 -- Logical Unit Id 0 -- Hardware Unit ADC0 */
    {
        /**< @brief Index of group */
        1U, /* GroupId */
        /**< @brief ADC Logical Unit Id that the group belongs to */
        (Adc_HwUnitType)0, /* AdcLogicalUnitId */
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE, /* AccessMode */
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT, /* Mode */
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL, /* Type */
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief Priority configured */
        (Adc_GroupPriorityType)ADC_GROUP_PRIORITY(0), /* Priority */
#endif /* ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART, /* ReplacementMode */
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW, /* TriggerSource */
#if (STD_ON == ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger source for the group */
        0U, /* HwTriggerSource */
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE, /* TriggerEdge */
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */
        NULL_PTR, /* Notification */
#endif /* (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
#if (ADC_ENABLE_INITIAL_NOTIFICATION == STD_ON)
        /**< @brief Extra notification function */
        NULL_PTR, /* ExtraNotification */
#endif /* (ADC_ENABLE_INITIAL_NOTIFICATION == STD_ON) */
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR, /* BufferMode */
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
        /**< @brief Index of the group with AdcEnableChDisableChGroup enabled */
        (Adc_GroupType)ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX, /* EnableChDisableChGroupIndex */
#endif /* (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) */
        /**< @brief Number of streaming samples */
        (Adc_StreamNumSampleType)ADC_STREAMING_NUM_SAMPLES(1), /* NumSamples */
#if (ADC_ENABLE_GROUP_STREAMING_RESULTS_REORDER == STD_ON)
        /**< @brief Arrange the adc results as multiple sets of group result buffer */
        (boolean)FALSE, /* StreamResultGroupMultiSets */
#endif /* (ADC_ENABLE_GROUP_STREAMING_RESULTS_REORDER == STD_ON) */
        /**< @brief Channels assigned to the group*/
        Adc_Group1_Assignment_0, /* AssignmentPtr */
        /**< @brief Number of channels in the group*/
        (Adc_ChannelIndexType)ADC_CFGSET_GROUP_1_CHANNELS, /* AssignedChannelCount */
        /**< @brief Last Channel configured */
        (Adc_ChannelType)(ADC_ID_CHANNEL_U8(41)), /* LastCh */
        /**< @brief First Channel configured */
        (Adc_ChannelType)(ADC_ID_CHANNEL_U8(41)), /* FirstCh */
        /**< @brief Enables or Disables the ADC and DMA interrupts */
        (uint8)(STD_ON), /* AdcWithoutInterrupt */
        /**< @brief Enables or Disables configuring external DMA channel in the group */
        (uint8)(STD_OFF), /* AdcExtDMAChanEnable */
        /**< @brief When true, disables completely DMA configuration done by ADC driver for the group */
        (boolean)FALSE, /* AdcWithoutDma */
#if (STD_ON == ADC_OPTIMIZE_DMA_STREAMING_GROUPS)
        /**< @brief Enables or Disables the ADC optimize DMA streaming groups feature */
        (boolean)(FALSE), /* AdcOptimizeDmaStream */
        /**< @brief Enable/disable half interrupt for group with optimize DMA streaming groups */
        (boolean)FALSE, /* HalfInterrupt */
#endif /* (STD_ON == ADC_OPTIMIZE_DMA_STREAMING_GROUPS) */
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        /**< @brief Enables or disables the usage of limit checking for an ADC group. */
        (boolean)FALSE, /* AdcGroupLimitcheck */
#endif /* (STD_ON == ADC_ENABLE_LIMIT_CHECK) */
        { { 0x0U, 0x200U, 0x0U } }, /* AssignedChannelMask */
#if (ADC_CTU_HW_TRIGGER_OPTIMIZATION == STD_ON)
        /**< @brief First position of channel in BCTU channel list or CTU command list. */
        0, /* CtuTrigListPos */
#endif /* (ADC_CTU_HW_TRIGGER_OPTIMIZATION == STD_ON) */
#ifdef ADC_AVERAGING_FUNCTIONALITY_SUPPORT
#if (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF)
        &AdcIpwGroupConfig_1 /* AdcIpwGroupConfigPtr */
#endif /* (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF) */
#endif /* ADC_AVERAGING_FUNCTIONALITY_SUPPORT */
    },
    /**< @brief Group2 -- Logical Unit Id 0 -- Hardware Unit ADC0 */
    {
        /**< @brief Index of group */
        2U, /* GroupId */
        /**< @brief ADC Logical Unit Id that the group belongs to */
        (Adc_HwUnitType)0, /* AdcLogicalUnitId */
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE, /* AccessMode */
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT, /* Mode */
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL, /* Type */
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief Priority configured */
        (Adc_GroupPriorityType)ADC_GROUP_PRIORITY(0), /* Priority */
#endif /* ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART, /* ReplacementMode */
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW, /* TriggerSource */
#if (STD_ON == ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger source for the group */
        0U, /* HwTriggerSource */
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE, /* TriggerEdge */
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */
        NULL_PTR, /* Notification */
#endif /* (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
#if (ADC_ENABLE_INITIAL_NOTIFICATION == STD_ON)
        /**< @brief Extra notification function */
        NULL_PTR, /* ExtraNotification */
#endif /* (ADC_ENABLE_INITIAL_NOTIFICATION == STD_ON) */
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR, /* BufferMode */
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
        /**< @brief Index of the group with AdcEnableChDisableChGroup enabled */
        (Adc_GroupType)ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX, /* EnableChDisableChGroupIndex */
#endif /* (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) */
        /**< @brief Number of streaming samples */
        (Adc_StreamNumSampleType)ADC_STREAMING_NUM_SAMPLES(1), /* NumSamples */
#if (ADC_ENABLE_GROUP_STREAMING_RESULTS_REORDER == STD_ON)
        /**< @brief Arrange the adc results as multiple sets of group result buffer */
        (boolean)FALSE, /* StreamResultGroupMultiSets */
#endif /* (ADC_ENABLE_GROUP_STREAMING_RESULTS_REORDER == STD_ON) */
        /**< @brief Channels assigned to the group*/
        Adc_Group2_Assignment_0, /* AssignmentPtr */
        /**< @brief Number of channels in the group*/
        (Adc_ChannelIndexType)ADC_CFGSET_GROUP_2_CHANNELS, /* AssignedChannelCount */
        /**< @brief Last Channel configured */
        (Adc_ChannelType)(ADC_ID_CHANNEL_U8(7)), /* LastCh */
        /**< @brief First Channel configured */
        (Adc_ChannelType)(ADC_ID_CHANNEL_U8(7)), /* FirstCh */
        /**< @brief Enables or Disables the ADC and DMA interrupts */
        (uint8)(STD_ON), /* AdcWithoutInterrupt */
        /**< @brief Enables or Disables configuring external DMA channel in the group */
        (uint8)(STD_OFF), /* AdcExtDMAChanEnable */
        /**< @brief When true, disables completely DMA configuration done by ADC driver for the group */
        (boolean)FALSE, /* AdcWithoutDma */
#if (STD_ON == ADC_OPTIMIZE_DMA_STREAMING_GROUPS)
        /**< @brief Enables or Disables the ADC optimize DMA streaming groups feature */
        (boolean)(FALSE), /* AdcOptimizeDmaStream */
        /**< @brief Enable/disable half interrupt for group with optimize DMA streaming groups */
        (boolean)FALSE, /* HalfInterrupt */
#endif /* (STD_ON == ADC_OPTIMIZE_DMA_STREAMING_GROUPS) */
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        /**< @brief Enables or disables the usage of limit checking for an ADC group. */
        (boolean)FALSE, /* AdcGroupLimitcheck */
#endif /* (STD_ON == ADC_ENABLE_LIMIT_CHECK) */
        { { 0x80U, 0x0U, 0x0U } }, /* AssignedChannelMask */
#if (ADC_CTU_HW_TRIGGER_OPTIMIZATION == STD_ON)
        /**< @brief First position of channel in BCTU channel list or CTU command list. */
        0, /* CtuTrigListPos */
#endif /* (ADC_CTU_HW_TRIGGER_OPTIMIZATION == STD_ON) */
#ifdef ADC_AVERAGING_FUNCTIONALITY_SUPPORT
#if (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF)
        &AdcIpwGroupConfig_2 /* AdcIpwGroupConfigPtr */
#endif /* (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF) */
#endif /* ADC_AVERAGING_FUNCTIONALITY_SUPPORT */
    },
    /**< @brief Group3 -- Logical Unit Id 0 -- Hardware Unit ADC0 */
    {
        /**< @brief Index of group */
        3U, /* GroupId */
        /**< @brief ADC Logical Unit Id that the group belongs to */
        (Adc_HwUnitType)0, /* AdcLogicalUnitId */
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE, /* AccessMode */
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT, /* Mode */
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL, /* Type */
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief Priority configured */
        (Adc_GroupPriorityType)ADC_GROUP_PRIORITY(0), /* Priority */
#endif /* ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART, /* ReplacementMode */
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW, /* TriggerSource */
#if (STD_ON == ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger source for the group */
        0U, /* HwTriggerSource */
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE, /* TriggerEdge */
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */
        NULL_PTR, /* Notification */
#endif /* (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
#if (ADC_ENABLE_INITIAL_NOTIFICATION == STD_ON)
        /**< @brief Extra notification function */
        NULL_PTR, /* ExtraNotification */
#endif /* (ADC_ENABLE_INITIAL_NOTIFICATION == STD_ON) */
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR, /* BufferMode */
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
        /**< @brief Index of the group with AdcEnableChDisableChGroup enabled */
        (Adc_GroupType)ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX, /* EnableChDisableChGroupIndex */
#endif /* (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) */
        /**< @brief Number of streaming samples */
        (Adc_StreamNumSampleType)ADC_STREAMING_NUM_SAMPLES(1), /* NumSamples */
#if (ADC_ENABLE_GROUP_STREAMING_RESULTS_REORDER == STD_ON)
        /**< @brief Arrange the adc results as multiple sets of group result buffer */
        (boolean)FALSE, /* StreamResultGroupMultiSets */
#endif /* (ADC_ENABLE_GROUP_STREAMING_RESULTS_REORDER == STD_ON) */
        /**< @brief Channels assigned to the group*/
        Adc_Group3_Assignment_0, /* AssignmentPtr */
        /**< @brief Number of channels in the group*/
        (Adc_ChannelIndexType)ADC_CFGSET_GROUP_3_CHANNELS, /* AssignedChannelCount */
        /**< @brief Last Channel configured */
        (Adc_ChannelType)(ADC_ID_CHANNEL_U8(47)), /* LastCh */
        /**< @brief First Channel configured */
        (Adc_ChannelType)(ADC_ID_CHANNEL_U8(47)), /* FirstCh */
        /**< @brief Enables or Disables the ADC and DMA interrupts */
        (uint8)(STD_ON), /* AdcWithoutInterrupt */
        /**< @brief Enables or Disables configuring external DMA channel in the group */
        (uint8)(STD_OFF), /* AdcExtDMAChanEnable */
        /**< @brief When true, disables completely DMA configuration done by ADC driver for the group */
        (boolean)FALSE, /* AdcWithoutDma */
#if (STD_ON == ADC_OPTIMIZE_DMA_STREAMING_GROUPS)
        /**< @brief Enables or Disables the ADC optimize DMA streaming groups feature */
        (boolean)(FALSE), /* AdcOptimizeDmaStream */
        /**< @brief Enable/disable half interrupt for group with optimize DMA streaming groups */
        (boolean)FALSE, /* HalfInterrupt */
#endif /* (STD_ON == ADC_OPTIMIZE_DMA_STREAMING_GROUPS) */
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        /**< @brief Enables or disables the usage of limit checking for an ADC group. */
        (boolean)FALSE, /* AdcGroupLimitcheck */
#endif /* (STD_ON == ADC_ENABLE_LIMIT_CHECK) */
        { { 0x0U, 0x8000U, 0x0U } }, /* AssignedChannelMask */
#if (ADC_CTU_HW_TRIGGER_OPTIMIZATION == STD_ON)
        /**< @brief First position of channel in BCTU channel list or CTU command list. */
        0, /* CtuTrigListPos */
#endif /* (ADC_CTU_HW_TRIGGER_OPTIMIZATION == STD_ON) */
#ifdef ADC_AVERAGING_FUNCTIONALITY_SUPPORT
#if (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF)
        &AdcIpwGroupConfig_3 /* AdcIpwGroupConfigPtr */
#endif /* (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF) */
#endif /* ADC_AVERAGING_FUNCTIONALITY_SUPPORT */
    },
    /**< @brief Group4 -- Logical Unit Id 1 -- Hardware Unit ADC1 */
    {
        /**< @brief Index of group */
        4U, /* GroupId */
        /**< @brief ADC Logical Unit Id that the group belongs to */
        (Adc_HwUnitType)1, /* AdcLogicalUnitId */
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE, /* AccessMode */
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT, /* Mode */
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL, /* Type */
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief Priority configured */
        (Adc_GroupPriorityType)ADC_GROUP_PRIORITY(0), /* Priority */
#endif /* ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART, /* ReplacementMode */
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW, /* TriggerSource */
#if (STD_ON == ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger source for the group */
        0U, /* HwTriggerSource */
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE, /* TriggerEdge */
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */
        NULL_PTR, /* Notification */
#endif /* (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
#if (ADC_ENABLE_INITIAL_NOTIFICATION == STD_ON)
        /**< @brief Extra notification function */
        NULL_PTR, /* ExtraNotification */
#endif /* (ADC_ENABLE_INITIAL_NOTIFICATION == STD_ON) */
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR, /* BufferMode */
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
        /**< @brief Index of the group with AdcEnableChDisableChGroup enabled */
        (Adc_GroupType)ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX, /* EnableChDisableChGroupIndex */
#endif /* (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) */
        /**< @brief Number of streaming samples */
        (Adc_StreamNumSampleType)ADC_STREAMING_NUM_SAMPLES(1), /* NumSamples */
#if (ADC_ENABLE_GROUP_STREAMING_RESULTS_REORDER == STD_ON)
        /**< @brief Arrange the adc results as multiple sets of group result buffer */
        (boolean)FALSE, /* StreamResultGroupMultiSets */
#endif /* (ADC_ENABLE_GROUP_STREAMING_RESULTS_REORDER == STD_ON) */
        /**< @brief Channels assigned to the group*/
        Adc_Group4_Assignment_1, /* AssignmentPtr */
        /**< @brief Number of channels in the group*/
        (Adc_ChannelIndexType)ADC_CFGSET_GROUP_4_CHANNELS, /* AssignedChannelCount */
        /**< @brief Last Channel configured */
        (Adc_ChannelType)(ADC_ID_CHANNEL_U8(34)), /* LastCh */
        /**< @brief First Channel configured */
        (Adc_ChannelType)(ADC_ID_CHANNEL_U8(34)), /* FirstCh */
        /**< @brief Enables or Disables the ADC and DMA interrupts */
        (uint8)(STD_OFF), /* AdcWithoutInterrupt */
        /**< @brief Enables or Disables configuring external DMA channel in the group */
        (uint8)(STD_OFF), /* AdcExtDMAChanEnable */
        /**< @brief When true, disables completely DMA configuration done by ADC driver for the group */
        (boolean)FALSE, /* AdcWithoutDma */
#if (STD_ON == ADC_OPTIMIZE_DMA_STREAMING_GROUPS)
        /**< @brief Enables or Disables the ADC optimize DMA streaming groups feature */
        (boolean)(FALSE), /* AdcOptimizeDmaStream */
        /**< @brief Enable/disable half interrupt for group with optimize DMA streaming groups */
        (boolean)FALSE, /* HalfInterrupt */
#endif /* (STD_ON == ADC_OPTIMIZE_DMA_STREAMING_GROUPS) */
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        /**< @brief Enables or disables the usage of limit checking for an ADC group. */
        (boolean)FALSE, /* AdcGroupLimitcheck */
#endif /* (STD_ON == ADC_ENABLE_LIMIT_CHECK) */
        { { 0x0U, 0x4U, 0x0U } }, /* AssignedChannelMask */
#if (ADC_CTU_HW_TRIGGER_OPTIMIZATION == STD_ON)
        /**< @brief First position of channel in BCTU channel list or CTU command list. */
        0, /* CtuTrigListPos */
#endif /* (ADC_CTU_HW_TRIGGER_OPTIMIZATION == STD_ON) */
#ifdef ADC_AVERAGING_FUNCTIONALITY_SUPPORT
#if (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF)
        &AdcIpwGroupConfig_4 /* AdcIpwGroupConfigPtr */
#endif /* (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF) */
#endif /* ADC_AVERAGING_FUNCTIONALITY_SUPPORT */
    },
    /**< @brief Group5 -- Logical Unit Id 1 -- Hardware Unit ADC1 */
    {
        /**< @brief Index of group */
        5U, /* GroupId */
        /**< @brief ADC Logical Unit Id that the group belongs to */
        (Adc_HwUnitType)1, /* AdcLogicalUnitId */
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE, /* AccessMode */
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT, /* Mode */
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL, /* Type */
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief Priority configured */
        (Adc_GroupPriorityType)ADC_GROUP_PRIORITY(0), /* Priority */
#endif /* ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART, /* ReplacementMode */
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW, /* TriggerSource */
#if (STD_ON == ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger source for the group */
        0U, /* HwTriggerSource */
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE, /* TriggerEdge */
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */
        NULL_PTR, /* Notification */
#endif /* (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
#if (ADC_ENABLE_INITIAL_NOTIFICATION == STD_ON)
        /**< @brief Extra notification function */
        NULL_PTR, /* ExtraNotification */
#endif /* (ADC_ENABLE_INITIAL_NOTIFICATION == STD_ON) */
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR, /* BufferMode */
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
        /**< @brief Index of the group with AdcEnableChDisableChGroup enabled */
        (Adc_GroupType)ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX, /* EnableChDisableChGroupIndex */
#endif /* (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) */
        /**< @brief Number of streaming samples */
        (Adc_StreamNumSampleType)ADC_STREAMING_NUM_SAMPLES(1), /* NumSamples */
#if (ADC_ENABLE_GROUP_STREAMING_RESULTS_REORDER == STD_ON)
        /**< @brief Arrange the adc results as multiple sets of group result buffer */
        (boolean)FALSE, /* StreamResultGroupMultiSets */
#endif /* (ADC_ENABLE_GROUP_STREAMING_RESULTS_REORDER == STD_ON) */
        /**< @brief Channels assigned to the group*/
        Adc_Group5_Assignment_1, /* AssignmentPtr */
        /**< @brief Number of channels in the group*/
        (Adc_ChannelIndexType)ADC_CFGSET_GROUP_5_CHANNELS, /* AssignedChannelCount */
        /**< @brief Last Channel configured */
        (Adc_ChannelType)(ADC_ID_CHANNEL_U8(44)), /* LastCh */
        /**< @brief First Channel configured */
        (Adc_ChannelType)(ADC_ID_CHANNEL_U8(44)), /* FirstCh */
        /**< @brief Enables or Disables the ADC and DMA interrupts */
        (uint8)(STD_OFF), /* AdcWithoutInterrupt */
        /**< @brief Enables or Disables configuring external DMA channel in the group */
        (uint8)(STD_OFF), /* AdcExtDMAChanEnable */
        /**< @brief When true, disables completely DMA configuration done by ADC driver for the group */
        (boolean)FALSE, /* AdcWithoutDma */
#if (STD_ON == ADC_OPTIMIZE_DMA_STREAMING_GROUPS)
        /**< @brief Enables or Disables the ADC optimize DMA streaming groups feature */
        (boolean)(FALSE), /* AdcOptimizeDmaStream */
        /**< @brief Enable/disable half interrupt for group with optimize DMA streaming groups */
        (boolean)FALSE, /* HalfInterrupt */
#endif /* (STD_ON == ADC_OPTIMIZE_DMA_STREAMING_GROUPS) */
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        /**< @brief Enables or disables the usage of limit checking for an ADC group. */
        (boolean)FALSE, /* AdcGroupLimitcheck */
#endif /* (STD_ON == ADC_ENABLE_LIMIT_CHECK) */
        { { 0x0U, 0x1000U, 0x0U } }, /* AssignedChannelMask */
#if (ADC_CTU_HW_TRIGGER_OPTIMIZATION == STD_ON)
        /**< @brief First position of channel in BCTU channel list or CTU command list. */
        0, /* CtuTrigListPos */
#endif /* (ADC_CTU_HW_TRIGGER_OPTIMIZATION == STD_ON) */
#ifdef ADC_AVERAGING_FUNCTIONALITY_SUPPORT
#if (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF)
        &AdcIpwGroupConfig_5 /* AdcIpwGroupConfigPtr */
#endif /* (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF) */
#endif /* ADC_AVERAGING_FUNCTIONALITY_SUPPORT */
    }
};



#define ADC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONFIG_DATA_16
#include "Adc_MemMap.h"

/**
* @brief         Array of index for mapping the groups.
* @details       Array of index for mapping the groups in each partition.
*
*/
static const uint16 Adc_au16GroupIdToIndexMap[ADC_MAX_GROUPS] =
{
    0,
    1,
    2,
    3,
    4,
    5
};

#define ADC_STOP_SEC_CONFIG_DATA_16
#include "Adc_MemMap.h"

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/
#define ADC_START_SEC_CONFIG_DATA_8
#include "Adc_MemMap.h"

/**
* @brief         Array contains coreId used for .
* @details       Array contains coreId used for .
*
*/
static const uint8 Adc_Partition_Assignment[1] =
{
    (uint8)(0UL)
};

#define ADC_STOP_SEC_CONFIG_DATA_8
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Adc_MemMap.h"


/* PB with no variants (VARIANT_NO := 0) or no ECUC */
/* No ADC configured Ecuc Partitions */
const Adc_ConfigType Adc_Config =
{
    &AdcIpwCfg, /* AdcIpwConfigPtr */
    /** @brief Group configurations */
    Adc_GroupsCfg, /* GroupsPtr */
    ADC_GROUPS, /* GroupCount */
    /**< @brief Array for mapping the groups */
    Adc_au16GroupIdToIndexMap, /* GroupIdToIndexMapPtr */
    /** @brief Configuration CoreID */
    (uint8)(0U), /* CoreId */
    /**< @brief Array contains CoreId */
    Adc_Partition_Assignment, /* AssignmentPartitionPtr */
    /**< @brief Number of partitions */
    (uint8)1UL /* AssignedPartitionCount */
};



#define ADC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Adc_MemMap.h"

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

