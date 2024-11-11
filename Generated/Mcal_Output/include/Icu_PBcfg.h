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

#ifndef ICU_PBCFG_H
#define ICU_PBCFG_H

/**
 *   @file       Icu_PBcfg.h
 *   @version    3.0.0
 *
 *   @brief      AUTOSAR Icu  - ICU driver configuration header file.
 *   @details        
 *
 *   @addtogroup icu Icu Driver
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

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ICU_PBCFG_VENDOR_ID                    43
#define ICU_PBCFG_AR_RELEASE_MAJOR_VERSION     4
#define ICU_PBCFG_AR_RELEASE_MINOR_VERSION     7
#define ICU_PBCFG_AR_RELEASE_REVISION_VERSION  0
#define ICU_PBCFG_SW_MAJOR_VERSION             3
#define ICU_PBCFG_SW_MINOR_VERSION             0
#define ICU_PBCFG_SW_PATCH_VERSION             0

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define ICU_CONFIG_PB \
        extern const Icu_ConfigType Icu_Config;

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* ICU_PBCFG_H */

