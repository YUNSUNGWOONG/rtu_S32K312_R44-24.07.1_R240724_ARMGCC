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

/**
*   @file    Flexio_Lin_Ip_PBcfg.c
*
*   @addtogroup FLEXIO_IP
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
#include "Flexio_Lin_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLEXIO_LIN_IP_PBCFG_VENDOR_ID_C                     43
#define FLEXIO_LIN_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define FLEXIO_LIN_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C      7
#define FLEXIO_LIN_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define FLEXIO_LIN_IP_PBCFG_SW_MAJOR_VERSION_C              3
#define FLEXIO_LIN_IP_PBCFG_SW_MINOR_VERSION_C              0
#define FLEXIO_LIN_IP_PBCFG_SW_PATCH_VERSION_C              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Checks against Flexio_Lin_Ip_Cfg.h */
#if (FLEXIO_LIN_IP_PBCFG_VENDOR_ID_C != FLEXIO_LIN_IP_CFG_VENDOR_ID)
    #error "Flexio_Lin_Ip_PBcfg.c and Flexio_Lin_Ip_Cfg.h have different vendor ids"
#endif
/* Check if current file and Flexio_Lin_Ip_Cfg header file are of the same Autosar version */
#if ((FLEXIO_LIN_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != FLEXIO_LIN_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_LIN_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C    != FLEXIO_LIN_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_LIN_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C != FLEXIO_LIN_IP_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Flexio_Lin_Ip_PBcfg.c and Flexio_Lin_Ip_Cfg.h are different"
#endif
/* Check if current file and Flexio_Lin_Ip_Cfg header file are of the same Software version */
#if ((FLEXIO_LIN_IP_PBCFG_SW_MAJOR_VERSION_C != FLEXIO_LIN_IP_CFG_SW_MAJOR_VERSION) || \
     (FLEXIO_LIN_IP_PBCFG_SW_MINOR_VERSION_C != FLEXIO_LIN_IP_CFG_SW_MINOR_VERSION) || \
     (FLEXIO_LIN_IP_PBCFG_SW_PATCH_VERSION_C != FLEXIO_LIN_IP_CFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Flexio_Lin_Ip_PBcfg.c and Flexio_Lin_Ip_Cfg.h are different"
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                      BUFFER DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                   STATE STRUCTURE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/




#define LIN_43_LPUART_FLEXIO_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Lin_43_LPUART_FLEXIO_MemMap.h"




#define LIN_43_LPUART_FLEXIO_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Lin_43_LPUART_FLEXIO_MemMap.h"
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
