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
* @addtogroup  Swt
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

#include "Swt_43_Instance1_Ip_PBcfg.h"









/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SWT_43_INSTANCE1_IP_PBCFG_VENDOR_ID_C                     43
#define SWT_43_INSTANCE1_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define SWT_43_INSTANCE1_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C      7
#define SWT_43_INSTANCE1_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define SWT_43_INSTANCE1_IP_PBCFG_SW_MAJOR_VERSION_C              3
#define SWT_43_INSTANCE1_IP_PBCFG_SW_MINOR_VERSION_C              0
#define SWT_43_INSTANCE1_IP_PBCFG_SW_PATCH_VERSION_C              0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Swt_43_Instance1_Ip_PBcfg header file are of the same vendor */
#if (SWT_43_INSTANCE1_IP_PBCFG_VENDOR_ID_C != SWT_43_INSTANCE1_IP_VENDOR_ID_PBCFG)
#error "Swt_43_Instance1_Ip_PBcfg.c and Swt_43_Instance1_Ip_PBcfg.h have different vendor ids"
#endif

/* Check if current file and Swt_43_Instance1_Ip_PBcfg header file are of the same Autosar version */
#if ((SWT_43_INSTANCE1_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != SWT_43_INSTANCE1_IP_AR_RELEASE_MAJOR_VERSION_PBCFG   ) || \
     (SWT_43_INSTANCE1_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C    != SWT_43_INSTANCE1_IP_AR_RELEASE_MINOR_VERSION_PBCFG   ) || \
     (SWT_43_INSTANCE1_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C != SWT_43_INSTANCE1_IP_AR_RELEASE_REVISION_VERSION_PBCFG))
#error "AutoSar Version Numbers of Swt_43_Instance1_Ip_PBcfg.c and Swt_43_Instance1_Ip_PBcfg.h are different"
#endif

/* Check if current file and Swt_43_Instance1_Ip_PBcfg header file are of the same software version */
#if ((SWT_43_INSTANCE1_IP_PBCFG_SW_MAJOR_VERSION_C != SWT_43_INSTANCE1_IP_SW_MAJOR_VERSION_PBCFG) || \
     (SWT_43_INSTANCE1_IP_PBCFG_SW_MINOR_VERSION_C != SWT_43_INSTANCE1_IP_SW_MINOR_VERSION_PBCFG) || \
     (SWT_43_INSTANCE1_IP_PBCFG_SW_PATCH_VERSION_C != SWT_43_INSTANCE1_IP_SW_PATCH_VERSION_PBCFG))
#error "Software Version Numbers of Swt_43_Instance1_Ip_PBcfg.c and Swt_43_Instance1_Ip_PBcfg.h are different"
#endif



/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

#define WDG_START_SEC_CONFIG_DATA_UNSPECIFIED

#include "Wdg_MemMap.h"





#define WDG_STOP_SEC_CONFIG_DATA_UNSPECIFIED

#include "Wdg_MemMap.h"

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

