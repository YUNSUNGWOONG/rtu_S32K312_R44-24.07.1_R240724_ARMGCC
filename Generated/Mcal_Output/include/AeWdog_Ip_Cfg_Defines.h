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
*   All Rights Reserved.
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef AEWDOG_IP_CFG_DEFINES_H
#define AEWDOG_IP_CFG_DEFINES_H

/**
*   @file
*
*   @addtogroup AeWdog_Ip
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "StandardTypes.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define AEWDOG_IP_CFG_DEFINES_VENDOR_ID                    43
#define AEWDOG_IP_CFG_DEFINES_MODULE_ID                    102
#define AEWDOG_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION     4
#define AEWDOG_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION     7
#define AEWDOG_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION  0
#define AEWDOG_IP_CFG_DEFINES_SW_MAJOR_VERSION             3
#define AEWDOG_IP_CFG_DEFINES_SW_MINOR_VERSION             0
#define AEWDOG_IP_CFG_DEFINES_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if current file and StandardTypes header file are of the same Autosar version */
    #if ((AEWDOG_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION    != STD_AR_RELEASE_MAJOR_VERSION) || \
        (AEWDOG_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION     != STD_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of AeWdog_Ip_Cfg_Defines.h and StandardTypes.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/**
* @brief  Compile switch to enable development error detection
*/
#define AEWDOG_IP_DEV_ERROR_DETECT (STD_OFF)
/**
* @brief  This constant specifies if the instance of the AEWDOG is selected or not
*/
#define AEWDOG_IP_ENABLE           (STD_OFF)

/**
* @brief  This variable will indicate RAM/ROM execution
*/
#define WDG_ROM (1U)

/**
* @brief  This macros indicate the Wdg timeout value for Wdg module.
*/

#define AEWDOG_IPW_TIMEOUT_VALUE_ARRAY {(uint32) 0, (uint32)0, (uint32) 0}

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* AEWDOG_IP_CFG_DEFINES_H */
