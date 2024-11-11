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

#ifndef EMIOS_ICU_IP_CFG_H
#define EMIOS_ICU_IP_CFG_H

/**
 *   @file    Emios_Icu_Ip_Cfg.h
 *   @version 3.0.0
 *
 *   @brief   AUTOSAR Icu - contains the data exported by the ICU module.
 *   @details Contains the information that will be exported by the module, as requested by AUTOSAR.
 *
 *   @addtogroup emios_icu_ip EMIOS IPL
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
/* Include all variants header files. */
#include "Emios_Icu_Ip_PBcfg.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define EMIOS_ICU_IP_CFG_VENDOR_ID                    43
#define EMIOS_ICU_IP_CFG_AR_RELEASE_MAJOR_VERSION     4
#define EMIOS_ICU_IP_CFG_AR_RELEASE_MINOR_VERSION     7
#define EMIOS_ICU_IP_CFG_AR_RELEASE_REVISION_VERSION  0
#define EMIOS_ICU_IP_CFG_SW_MAJOR_VERSION             3
#define EMIOS_ICU_IP_CFG_SW_MINOR_VERSION             0
#define EMIOS_ICU_IP_CFG_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and ICU configuration header file are of the same vendor */
#if (EMIOS_ICU_IP_CFG_VENDOR_ID != EMIOS_ICU_IP_PBCFG_VENDOR_ID)
    #error "Emios_Icu_Ip_Cfg.h and Emios_Icu_Ip_PBcfg.h have different vendor IDs"
#endif
    /* Check if header file and Icu configuration header file are of the same Autosar version */
#if ((EMIOS_ICU_IP_CFG_AR_RELEASE_MAJOR_VERSION != EMIOS_ICU_IP_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (EMIOS_ICU_IP_CFG_AR_RELEASE_MINOR_VERSION != EMIOS_ICU_IP_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (EMIOS_ICU_IP_CFG_AR_RELEASE_REVISION_VERSION != EMIOS_ICU_IP_PBCFG_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Emios_Icu_Ip_Cfg.h and Emios_Icu_Ip_PBcfg.h are different"
#endif
/* Check if header file and Icu configuration header file are of the same software version */
#if ((EMIOS_ICU_IP_CFG_SW_MAJOR_VERSION != EMIOS_ICU_IP_PBCFG_SW_MAJOR_VERSION) || \
     (EMIOS_ICU_IP_CFG_SW_MINOR_VERSION != EMIOS_ICU_IP_PBCFG_SW_MINOR_VERSION) || \
     (EMIOS_ICU_IP_CFG_SW_PATCH_VERSION != EMIOS_ICU_IP_PBCFG_SW_PATCH_VERSION))
#error "Software Version Numbers of Emios_Icu_Ip_Cfg.h and Emios_Icu_Ip_PBcfg.h are different"
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#if (STD_ON == EMIOS_ICU_IP_USED)
/** @brief Macros to check EMIOS channels used by ICU. */
#ifndef EMIOS_0_CH_1_USED
    #define EMIOS_0_CH_1_USED
#else
    #error "EMIOS_0_CH_1 channel cannot be used by ICU. Instance locked by another driver!"
#endif
/** @brief Macros to check EMIOS channels used by ICU. */
#ifndef EMIOS_0_CH_2_USED
    #define EMIOS_0_CH_2_USED
#else
    #error "EMIOS_0_CH_2 channel cannot be used by ICU. Instance locked by another driver!"
#endif
/** @brief Macros to check EMIOS channels used by ICU. */
#ifndef EMIOS_0_CH_3_USED
    #define EMIOS_0_CH_3_USED
#else
    #error "EMIOS_0_CH_3 channel cannot be used by ICU. Instance locked by another driver!"
#endif
/** @brief Macros to check EMIOS channels used by ICU. */
#ifndef EMIOS_0_CH_4_USED
    #define EMIOS_0_CH_4_USED
#else
    #error "EMIOS_0_CH_4 channel cannot be used by ICU. Instance locked by another driver!"
#endif

#define EMIOS_ICU_CONFIG_EXT \
        EMIOS_ICU_CONFIG_PB
#endif  /* EMIOS_ICU_IP_USED */


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* EMIOS_ICU_IP_CFG_H */

