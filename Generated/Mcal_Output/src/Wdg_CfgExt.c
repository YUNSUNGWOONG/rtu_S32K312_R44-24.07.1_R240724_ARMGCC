
/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : Swt
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
* @file
*
* @addtogroup  Wdg
* @{
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

#include "Wdg_ChannelTypes.h"
#include "Wdg_Cfg.h"
#include "Wdg_CfgExt.h"









/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define WDG_VENDOR_ID_CFG_EXT_C                    43
#define WDG_AR_RELEASE_MAJOR_VERSION_CFG_EXT_C     4
#define WDG_AR_RELEASE_MINOR_VERSION_CFG_EXT_C     7
#define WDG_AR_RELEASE_REVISION_VERSION_CFG_EXT_C  0
#define WDG_SW_MAJOR_VERSION_CFG_EXT_C             3
#define WDG_SW_MINOR_VERSION_CFG_EXT_C             0
#define WDG_SW_PATCH_VERSION_CFG_EXT_C             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Wdg_CfgExt header file are of the same vendor */
#if (WDG_VENDOR_ID_CFG_EXT_C != WDG_VENDOR_ID_CFG_EXT)
    #error "Wdg_CfgExt.c and Wdg_CfgExt.h have different vendor ids"
#endif

/* Check if current file and Wdg_CfgExt header file are of the same Autosar version */
#if ((WDG_AR_RELEASE_MAJOR_VERSION_CFG_EXT_C     != WDG_AR_RELEASE_MAJOR_VERSION_CFG_EXT) || \
     (WDG_AR_RELEASE_MINOR_VERSION_CFG_EXT_C     != WDG_AR_RELEASE_MINOR_VERSION_CFG_EXT) || \
     (WDG_AR_RELEASE_REVISION_VERSION_CFG_EXT_C  != WDG_AR_RELEASE_REVISION_VERSION_CFG_EXT))
#error "AutoSar Version Numbers of Wdg_CfgExt.c and Wdg_CfgExt.h are different"
#endif

/* Check if current file and Wdg_CfgExt header file are of the same software version */
#if ((WDG_SW_MAJOR_VERSION_CFG_EXT_C != WDG_SW_MAJOR_VERSION_CFG_EXT) || \
     (WDG_SW_MINOR_VERSION_CFG_EXT_C != WDG_SW_MINOR_VERSION_CFG_EXT) || \
     (WDG_SW_PATCH_VERSION_CFG_EXT_C != WDG_SW_PATCH_VERSION_CFG_EXT))
#error "Software Version Numbers of Wdg_CfgExt.c and Wdg_CfgExt.h are different"
#endif

/* Check if current file and Wdg_ChannelTypes header file are of the same vendor */
#if (WDG_VENDOR_ID_CFG_EXT_C != WDG_CHANNEL_TYPES_VENDOR_ID)
    #error "Wdg_CfgExt.c and Wdg_ChannelTypes.h have different vendor ids"
#endif

#if (( WDG_AR_RELEASE_MAJOR_VERSION_CFG_EXT_C    != WDG_CHANNEL_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (WDG_AR_RELEASE_MINOR_VERSION_CFG_EXT_C     != WDG_CHANNEL_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (WDG_AR_RELEASE_REVISION_VERSION_CFG_EXT_C  != WDG_CHANNEL_TYPES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Wdg_CfgExt.c and Wdg_ChannelTypes.h are different"
#endif

#if ((WDG_SW_MAJOR_VERSION_CFG_EXT_C != WDG_CHANNEL_TYPES_SW_MAJOR_VERSION) || \
     (WDG_SW_MINOR_VERSION_CFG_EXT_C != WDG_CHANNEL_TYPES_SW_MINOR_VERSION) || \
     (WDG_SW_PATCH_VERSION_CFG_EXT_C != WDG_CHANNEL_TYPES_SW_PATCH_VERSION))
#error "Software Version Numbers of Wdg_CfgExt.c and Wdg_ChannelTypes.h are different"
#endif

/* Check if source file and Wdg_Cfg header file are of the same Autosar version */
#if (WDG_VENDOR_ID_CFG_EXT_C != WDG_VENDOR_ID_CFG)
    #error "Wdg_CfgExt.c and Wdg_Cfg.h have different vendor ids"
#endif

#if (( WDG_AR_RELEASE_MAJOR_VERSION_CFG_EXT_C    != WDG_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (WDG_AR_RELEASE_MINOR_VERSION_CFG_EXT_C     != WDG_AR_RELEASE_MINOR_VERSION_CFG) || \
     (WDG_AR_RELEASE_REVISION_VERSION_CFG_EXT_C  != WDG_AR_RELEASE_REVISION_VERSION_CFG))
    #error "AutoSar Version Numbers of Wdg_CfgExt.c and Wdg_Cfg.h are different"
#endif

#if ((WDG_SW_MAJOR_VERSION_CFG_EXT_C != WDG_SW_MAJOR_VERSION_CFG) || \
     (WDG_SW_MINOR_VERSION_CFG_EXT_C != WDG_SW_MINOR_VERSION_CFG) || \
     (WDG_SW_PATCH_VERSION_CFG_EXT_C != WDG_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of Wdg_CfgExt.c and Wdg_Cfg.h are different"
#endif


/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/

#define WDG_START_SEC_CONFIG_DATA_UNSPECIFIED

#include "Wdg_MemMap.h"


const uint16 Wdg_au16CfgInitialTimeout[WDG_NO_OF_INSTANCES]=
{
 WDG_43_INSTANCE0_INITIAL_TIMEOUT_U16
};

const uint16 Wdg_au16CfgMaxTimeout[WDG_NO_OF_INSTANCES]=
{
 WDG_43_INSTANCE0_MAX_TIMEOUT_U16
};

#if (WDG_MULTICORE_ENABLED == STD_ON)
const uint32 Wdg_au32InstanceCoreUsed[WDG_NO_OF_INSTANCES]=
{
0xFFFF
};
#endif

#define WDG_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @brief Include Memory mapping specification
*
*/
#include "Wdg_MemMap.h"





/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                     GLOBAL FUNCTIONS
==================================================================================================*/
#ifdef __cplusplus
}
#endif

/** @} */
