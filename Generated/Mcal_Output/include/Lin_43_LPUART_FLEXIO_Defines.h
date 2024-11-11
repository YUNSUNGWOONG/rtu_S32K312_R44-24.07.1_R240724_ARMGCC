/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : LPUART_FLEXIO
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
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef LIN_43_LPUART_FLEXIO_DEFINES_H
#define LIN_43_LPUART_FLEXIO_DEFINES_H

/**
*   @file
*
*   @defgroup lin_driver LIN Driver
*   @addtogroup  lin_driver LIN Driver
*   @{
*/

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcal.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LIN_43_LPUART_FLEXIO_DEFINES_VENDOR_ID                     43
#define LIN_43_LPUART_FLEXIO_DEFINES_AR_RELEASE_MAJOR_VERSION      4
#define LIN_43_LPUART_FLEXIO_DEFINES_AR_RELEASE_MINOR_VERSION      7
#define LIN_43_LPUART_FLEXIO_DEFINES_AR_RELEASE_REVISION_VERSION   0
#define LIN_43_LPUART_FLEXIO_DEFINES_SW_MAJOR_VERSION              3
#define LIN_43_LPUART_FLEXIO_DEFINES_SW_MINOR_VERSION              0
#define LIN_43_LPUART_FLEXIO_DEFINES_SW_PATCH_VERSION              0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((LIN_43_LPUART_FLEXIO_DEFINES_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (LIN_43_LPUART_FLEXIO_DEFINES_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AUTOSAR Version Numbers of Lin_Defines.h and Mcal.h are different"
    #endif
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/
/**
* @brief          Pre-compile Support.
*
*
*/
#define LIN_43_LPUART_FLEXIO_PRECOMPILE_SUPPORT  (STD_OFF) 

/**
* @brief   No of Channels configured.
*
*
*/
#define LIN_43_LPUART_FLEXIO_HW_MAX_MODULES (2U)

/**
* @brief   Total number of available hardware lin channels.
*
*
*/
#define LIN_43_LPUART_FLEXIO_HW_MAX_AVAILABLE_MODULES (12U)

/**
* @brief   Switches the Development Error Detection and Notification ON or OFF.
*
*
*/
#define LIN_43_LPUART_FLEXIO_DEV_ERROR_DETECT (STD_ON)  /* Enable Development Error Detection */

/**
* @brief   Switches the Production Error Detection and Notification OFF
*
*
*/
#define LIN_43_LPUART_FLEXIO_DISABLE_DEM_REPORT_ERROR_STATUS  (STD_ON) /* Disable Production Error Detection */ 

/**
* @brief          Lin Master Node Used
* @details        When LinGlobalConfig/LinChannel/LinNodeType contains at least one MASTER channel.
*
*
*/
#define LIN_43_LPUART_FLEXIO_MASTER_NODE_USED  (STD_ON) /* Used Master Node */

/**
* @brief          Support for version info API.
* @details        Switches the Lin_GetVersionInfo() API ON or OFF.
*
*
*/
#define LIN_43_LPUART_FLEXIO_VERSION_INFO_API (STD_OFF) /* Disable API Lin_GetVersionInfo     */

/**
* @brief        All CoreIDs are supported by LIN driver.
*/

#define LIN_43_LPUART_FLEXIO_MAX_PARTITIONS     ((uint32)1U)

/**
* @brief          Multicore is enabled or not
*/
#define LIN_43_LPUART_FLEXIO_MULTICORE_SUPPORT   (STD_OFF) /* Multicore is disabled */

/**
* @brief          Enable Non-Autosar API for Dual-Clock support.
* @details        Enable/Disable API Lin_SetClockMode() to set the
*                 clock to be used by the LIN driver (Normal clock: default mode;
*                 Alternate clock: when the driver is in Low-Power mode).
*                 This can be set to STD_ON only if it is activated from xdm file:
*                 LinClockRef_Alternate is enable.
*
* @api
*/

#define LIN_43_LPUART_FLEXIO_DUAL_CLOCK_MODE  (STD_OFF) /* Disable API Lin_SetClockMode */ 

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define LIN_43_LPUART_FLEXIO_UNALLOCATEDPAR_CORE_ID  ((uint32)0x0U)

#if (STD_ON == LIN_43_LPUART_FLEXIO_MULTICORE_SUPPORT)
    #define Lin_43_LPUART_FLEXIO_GetCoreID() (OsIf_GetCoreID())
#else
    #define Lin_43_LPUART_FLEXIO_GetCoreID() (LIN_43_LPUART_FLEXIO_UNALLOCATEDPAR_CORE_ID)
#endif /* (STD_ON == LIN_43_LPUART_FLEXIO_MULTICORE_SUPPORT) */

/**
* @brief          LIN driver status initialization variable.
*/
#define LIN_43_LPUART_FLEXIO_UNINIT_ARRAY  {LIN_43_LPUART_FLEXIO_UNINIT}

/**
*
* @internal
* @brief          Lin FlexIO Used
* @details        When LinGlobalConfig/LinChannel/LinHwChannel contains FLEXIO.
*
*
*/
#define LIN_43_LPUART_FLEXIO_FLEXIO_USED (STD_OFF) /* No Used Flexio */
/**
*
* @internal
* @brief          Lin Wakeup detection feature 
* @details        It is set to STD_ON when LinGlobalConfig/LinChannel/WakeupDetectionSupport is enabled.
*
*
*/
#define LIN_43_LPUART_FLEXIO_WAKEUP_DETECTION (STD_OFF) /* Support wakeup detection */
/**
*
* @internal
* @brief          Instance number assigned to the driver         
* @details        InstanceId of this module instance. If only one instance is present it shall have the Id 0
*
*
*/
#define LIN_43_LPUART_FLEXIO_DRIVER_INSTANCE             (0U)    /* Instance number assigned to the driver */
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                  EXTERNAL CONSTANTS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* LIN_43_LPUART_FLEXIO_DEFINES_H */
