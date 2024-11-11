/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : C40_IP IPV_QSPI
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

#ifndef QSPI_IP_PBCFG_H
#define QSPI_IP_PBCFG_H

/**
*   @file Qspi_Ip_PBcfg.h
*
*   @addtogroup FLS
*   @{
*/

/* implements Qspi_Ip_PBcfg.h_Artifact */

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Qspi_Ip_Types.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define QSPI_IP_PBCFG_VENDOR_ID                    43

#define QSPI_IP_PBCFG_AR_RELEASE_MAJOR_VERSION     4
#define QSPI_IP_PBCFG_AR_RELEASE_MINOR_VERSION     7
#define QSPI_IP_PBCFG_AR_RELEASE_REVISION_VERSION  0

#define QSPI_IP_PBCFG_SW_MAJOR_VERSION             3
#define QSPI_IP_PBCFG_SW_MINOR_VERSION             0
#define QSPI_IP_PBCFG_SW_PATCH_VERSION             0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Qspi_Ip_Types.h header file are of the same vendor */
#if (QSPI_IP_PBCFG_VENDOR_ID != FLS_QSPI_TYPES_VENDOR_ID)
    #error "Qspi_Ip_PBcfg.h and Qspi_Ip_Types.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Types.h header file are of the same Autosar version */
#if ((QSPI_IP_PBCFG_AR_RELEASE_MAJOR_VERSION    != FLS_QSPI_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (QSPI_IP_PBCFG_AR_RELEASE_MINOR_VERSION    != FLS_QSPI_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (QSPI_IP_PBCFG_AR_RELEASE_REVISION_VERSION != FLS_QSPI_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
#error "AutoSar Version Numbers of Qspi_Ip_PBcfg.h and Qspi_Ip_Types.h are different"
#endif
/* Check if current file and Qspi_Ip_Types.h header file are of the same software version */
#if ((QSPI_IP_PBCFG_SW_MAJOR_VERSION != FLS_QSPI_TYPES_SW_MAJOR_VERSION) || \
     (QSPI_IP_PBCFG_SW_MINOR_VERSION != FLS_QSPI_TYPES_SW_MINOR_VERSION) || \
     (QSPI_IP_PBCFG_SW_PATCH_VERSION != FLS_QSPI_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Qspi_Ip_PBcfg.h and Qspi_Ip_Types.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/


/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#define FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"



#define FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/**@}*/

#endif    /* #ifndef QSPI_IP_PBCFG_H */