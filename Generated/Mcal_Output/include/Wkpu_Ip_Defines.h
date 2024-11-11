/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : Emios Siul2 Wkpu LpCmp
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
#ifndef WKPU_IP_DEFINES_H
#define WKPU_IP_DEFINES_H

/**
 *   @file    Wkpu_Ip_Defines.h
 *   @version 3.0.0
 *
 *   @brief   AUTOSAR Icu - contains the data exported by the Icu module
 *   @details Contains the information that will be exported by the module, as requested by Autosar.
 *
 *   @addtogroup wkpu_icu_ip WKPU IPL
 *   @{
 */

#ifdef __cplusplus
extern "C"{
#endif
 /*==================================================================================================
 *                                         INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
 *================================================================================================*/
#include "Std_Types.h"
/* Include platform header file. */
#include "S32K312_WKPU.h"

/*==================================================================================================
 *                              SOURCE FILE VERSION INFORMATION
 *================================================================================================*/

#define WKPU_IP_DEFINES_VENDOR_ID                    43
#define WKPU_IP_DEFINES_AR_RELEASE_MAJOR_VERSION     4
#define WKPU_IP_DEFINES_AR_RELEASE_MINOR_VERSION     7
#define WKPU_IP_DEFINES_AR_RELEASE_REVISION_VERSION  0
#define WKPU_IP_DEFINES_SW_MAJOR_VERSION             3
#define WKPU_IP_DEFINES_SW_MINOR_VERSION             0
#define WKPU_IP_DEFINES_SW_PATCH_VERSION             0

/*==================================================================================================
 *                                      FILE VERSION CHECKS
 *================================================================================================*/
/* Check if header file and Std_Types.h file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((WKPU_IP_DEFINES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (WKPU_IP_DEFINES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Wkpu_Ip_Defines.h and Std_Types.h are different"
    #endif
#endif

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

#define WKPU_IP_USED               (STD_ON)

#if (STD_ON == WKPU_IP_USED)
#define WKPU_IP_NMI_API               (STD_OFF)

#if (defined (WKPU_IP_NMI_API) && (STD_ON == WKPU_IP_NMI_API))
/*! @brief The distance between cores */
#define     WKPU_IP_CORE_OFFSET_SIZE            (8U)
#define     WKPU_IP_SUPPORT_NONE_REQUEST
#define     WKPU_IP_SUPPORT_NON_MASK_INT
/** @brief The WKPU core array */
#define WKPU_IP_CORE_ARRAY \
{                          \
    WKPU_CORE0    /*!< Core 0 */,\
    WKPU_CORE1    /*!< Core 1 */\
}
#define     WKPU_IP_NMI_NUM_CORES               (2U)
#endif

#define     WKPU_IP_SUPPORT_INTERRUPT_REQUEST
#define     WKPU_IP_NUM_OF_CHANNELS             (64U)

/** @brief The number of Wkpu channels are used in configuration */
#define     WKPU_IP_NUM_OF_CHANNELS_USED        ((uint8)1U)

#define     WKPU_IP_NUM_OF_CHANNELS_IN_ONE_REG  (32U)

/** @brief Switch for enabling Standby wakeup support  on or off */
#define     WKPU_IP_STANDBY_WAKEUP_SUPPORT      (STD_OFF)





#define WKPU_IP_INITIAL_INDEX_OF_CHANNELS \
    {255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 0U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U, 255U}


#endif /* WKPU_IP_USED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* WKPU_IP_DEFINES_H */
