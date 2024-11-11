/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
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
*   @file    Port_PBcfg.c
*
*   @implements Port_PBcfg.c_Artifact
*   @addtogroup Port_CFG
*   @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Port.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
#define PORT_VENDOR_ID_PBCFG_C 43
#define PORT_AR_RELEASE_MAJOR_VERSION_PBCFG_C 4
#define PORT_AR_RELEASE_MINOR_VERSION_PBCFG_C 7
#define PORT_AR_RELEASE_REVISION_VERSION_PBCFG_C 0
#define PORT_SW_MAJOR_VERSION_PBCFG_C 3
#define PORT_SW_MINOR_VERSION_PBCFG_C 0
#define PORT_SW_PATCH_VERSION_PBCFG_C 0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
/* Check if Port_PBcfg.c and Port.h are of the same vendor */
#if (PORT_VENDOR_ID_PBCFG_C != PORT_VENDOR_ID)
    #error "Port_PBcfg.c and Port.h have different vendor ids"
#endif
/* Check if Port_PBcfg.c and Port.h are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_PBCFG_C    != PORT_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_AR_RELEASE_MINOR_VERSION_PBCFG_C    != PORT_AR_RELEASE_MINOR_VERSION) || \
     (PORT_AR_RELEASE_REVISION_VERSION_PBCFG_C != PORT_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Port_PBcfg.c and Port.h are different"
#endif
/* Check if Port_PBcfg.c and Port.h are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_PBCFG_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_PBCFG_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_PBCFG_C != PORT_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Port_PBcfg.c and Port.h are different"
#endif

/*=================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/


/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL CONSTANTS
=================================================================================================*/
#define PORT_START_SEC_CONFIG_DATA_8
#include "Port_MemMap.h"


/**
* @brief Array containing list of partition which used in driver
*/
const uint8 au8Port_PartitionList[PORT_MAX_PARTITION] =
{
    1
};

#define PORT_STOP_SEC_CONFIG_DATA_8
#include "Port_MemMap.h"

#define PORT_START_SEC_CONFIG_DATA_32
#include "Port_MemMap.h"
/**
* @brief Array containing list of mapping information for mappable elements
*/
static const uint32 au32Port_PinToPartitionMap[PORT_MAX_CONFIGURED_PADS_U16] =
{
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001
};

#define PORT_STOP_SEC_CONFIG_DATA_32
#include "Port_MemMap.h"


#if (PORT_MAX_UNUSED_PADS_U16 != 0U)

#define PORT_START_SEC_CONFIG_DATA_16
#include "Port_MemMap.h"

/**
* @brief Array containing list of MSCRs that are not used and should be configured with values from NotUsedPortPin container
*/
static const Port_Siul2_UnUsedPinType Port_aUnusedPads[PORT_MAX_UNUSED_PADS_U16]=
{
    /* Mscr Id, Mscr Siul Instance*/

};

#define PORT_STOP_SEC_CONFIG_DATA_16
#include "Port_MemMap.h"

#endif /* (PORT_MAX_UNUSED_PADS_U16 != 0) */

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/**
 * @brief Default Configuration for Pins not initialized
 */
static const Port_Siul2_UnUsedPinConfigType Port_UnusedPinConfig =
{
    /**
    * @note: Configuration of Default pin
    */
    (uint32)0x00082000, (uint8)0
    
};


/**
* @brief Pin default configuration data for configPB
*/
static const Port_Siul2_PinConfigType Port_aUsedPinConfigs[PORT_MAX_CONFIGURED_PADS_U16]=
{
    /* Mscr Id, Mscr Value, Mscr Siul Instance, Output Level, Direction, IsGpio, Direction Configurable, Mode Changeable, IsImcrAvailable, Imcr Id */
    { (uint16)0, (uint32)0x00200002, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)1, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)2, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)3, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)4, (uint32)0x00280007, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)TRUE, 186 },
    { (uint16)5, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)6, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)TRUE, 0 },
    { (uint16)7, (uint32)0x00200004, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)8, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)9, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)10, (uint32)0x00200007, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)11, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)12, (uint32)0x00200006, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)13, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)14, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)15, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)16, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)17, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)TRUE, 54 },
    { (uint16)18, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)19, (uint32)0x00280000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)20, (uint32)0x00280000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)21, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)24, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)25, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)27, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)28, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)29, (uint32)0x00200000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)30, (uint32)0x00200000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)31, (uint32)0x00200000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)32, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)TRUE, 187 },
    { (uint16)33, (uint32)0x00200002, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)34, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)35, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)36, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)37, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)40, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)41, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)42, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)43, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)44, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)45, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)TRUE, 49 },
    { (uint16)46, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)TRUE, 50 },
    { (uint16)47, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)TRUE, 51 },
    { (uint16)48, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)49, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)50, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)51, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)52, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)53, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)54, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)55, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)56, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)57, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)58, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)59, (uint32)0x00200001, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)60, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)TRUE, 192 },
    { (uint16)61, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)62, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)64, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)65, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)66, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)67, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)68, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)TRUE, 184 },
    { (uint16)69, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)TRUE, 185 },
    { (uint16)70, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)71, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)72, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)73, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)74, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)75, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)76, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)77, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)78, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)79, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)80, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)81, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)82, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)83, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)84, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)85, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)87, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)88, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)89, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)90, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)91, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)92, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)93, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)94, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)95, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)96, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)97, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)98, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)99, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)100, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)101, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)102, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)103, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)104, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)105, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)106, (uint32)0x00200000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)107, (uint32)0x00200000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)108, (uint32)0x00200000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)109, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)110, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)111, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)112, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)113, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)114, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)116, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)117, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)118, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)119, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)120, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)122, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)123, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)124, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)125, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)126, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)127, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)128, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)129, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)130, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)131, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)132, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)133, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)134, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)135, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)TRUE, 55 },
    { (uint16)136, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)137, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)138, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)139, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)140, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)141, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)142, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)143, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)144, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)145, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)146, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)147, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)149, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)150, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)151, (uint32)0x00200000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)152, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)153, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)154, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 }
};

#ifdef PORT_CODE_SIZE_OPTIMIZATION
#if (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION)

/* SIUL2_0 */
/**
* @brief IMCR configuration set by Port_Init() for SIUL2 instance: SIUL2_0
*/
static const Port_Siul2_ImcrConfigType Port_aSIUL2_0_ImcrInitConfig[PORT_SIUL2_0_NUM_IMCRS_U16]=
{
    { (uint8)0x02, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x02, (uint8)0 },
    { (uint8)0x03, (uint8)0 },
    { (uint8)0x01, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x02, (uint8)0 },
    { (uint8)0x02, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x02, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x04, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
};

#endif /* (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION) */
#endif /* PORT_CODE_SIZE_OPTIMIZATION */

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/*=================================================================================================
*                                      LOCAL VARIABLES
=================================================================================================*/


/*=================================================================================================
*                                      GLOBAL CONSTANTS
=================================================================================================*/
#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/**
* @brief This table contains all the Configured Port Pin parameters and the
*        number of Port Pins configured by the tool for the post-build mode
*/
const Port_ConfigType Port_Config =
{
    PORT_MAX_CONFIGURED_PADS_U16,
    PORT_MAX_UNUSED_PADS_U16,
    {
        PORT_SIUL2_0_NUM_IMCRS_U16
    },
#if (PORT_MAX_UNUSED_PADS_U16 != 0U)
    Port_aUnusedPads,
#else
    NULL_PTR,
#endif
    &Port_UnusedPinConfig,
    Port_aUsedPinConfigs,
#ifdef PORT_CODE_SIZE_OPTIMIZATION
#if (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION)
    {
        Port_aSIUL2_0_ImcrInitConfig
    },
#else
    {
        NULL_PTR
    },
#endif /* (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION) */
#endif /* PORT_CODE_SIZE_OPTIMIZATION */
    au32Port_PinToPartitionMap,
    au8Port_PartitionList,
    g_pin_mux_InitConfigArr,

    aTspc_InitConfigArr
};

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/*=================================================================================================
*                                      GLOBAL VARIABLES
=================================================================================================*/


/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/


/*=================================================================================================
*                                       LOCAL FUNCTIONS
=================================================================================================*/


/*=================================================================================================
*                                       GLOBAL FUNCTIONS
=================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

/* End of File */
