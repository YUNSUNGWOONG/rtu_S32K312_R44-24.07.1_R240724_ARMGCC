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

#ifndef FLS_CFG_H
#define FLS_CFG_H

/**
*   @file Fls_Cfg.h
*
*   @addtogroup FLS
*   @{
*/

/* implements Fls_Cfg.h_Artifact */

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Fls_Types.h"
#include "Mcal.h"
#include "MemIf_Types.h"
#include "C40_Ip_Cfg.h"
#include "C40_Ip_Ac.h"

#include "Qspi_Ip_Cfg.h"


#include "Fls_PBcfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLS_VENDOR_ID_CFG                    43
#define FLS_AR_RELEASE_MAJOR_VERSION_CFG     4
#define FLS_AR_RELEASE_MINOR_VERSION_CFG     7
#define FLS_AR_RELEASE_REVISION_VERSION_CFG  0
#define FLS_SW_MAJOR_VERSION_CFG             3
#define FLS_SW_MINOR_VERSION_CFG             0
#define FLS_SW_PATCH_VERSION_CFG             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Fls configuration header file are of the same vendor */
#if (FLS_TYPES_VENDOR_ID != FLS_VENDOR_ID_CFG)
    #error "Fls_Types.h and Fls_Cfg.h have different vendor ids"
#endif
/* Check if current file and Fls configuration header file are of the same Autosar version */
#if ((FLS_TYPES_AR_RELEASE_MAJOR_VERSION    != FLS_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (FLS_TYPES_AR_RELEASE_MINOR_VERSION    != FLS_AR_RELEASE_MINOR_VERSION_CFG) || \
     (FLS_TYPES_AR_RELEASE_REVISION_VERSION != FLS_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Fls_Types.h and Fls_Cfg.h are different"
#endif
/* Check if current file and Fls configuration header file are of the same software version */
#if ((FLS_TYPES_SW_MAJOR_VERSION != FLS_SW_MAJOR_VERSION_CFG) || \
     (FLS_TYPES_SW_MINOR_VERSION != FLS_SW_MINOR_VERSION_CFG) || \
     (FLS_TYPES_SW_PATCH_VERSION != FLS_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Fls_Types.h and Fls_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if current file and Std_Types header file are of the same version */
    #if ((FLS_AR_RELEASE_MAJOR_VERSION_CFG != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (FLS_AR_RELEASE_MINOR_VERSION_CFG != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Fls_Types.h and Mcal.h are different"
    #endif
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if current file and MemIf_Types.h file are of the same Autosar version */
    #if ((FLS_AR_RELEASE_MAJOR_VERSION_CFG != MEMIF_AR_RELEASE_MAJOR_VERSION) || \
         (FLS_AR_RELEASE_MINOR_VERSION_CFG != MEMIF_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Fls_Cfg.h and MemIf_Types.h are different"
    #endif
#endif

/* Check if current file and C40_Ip_Cfg header file are of the same vendor */
#if (FLS_VENDOR_ID_CFG != FLS_C40_IP_VENDOR_ID_CFG)
    #error "Fls_Cfg.h and C40_Ip_Cfg.h have different vendor ids"
#endif
/* Check if current file and C40_Ip_Cfg header file are of the same Autosar version */
#if ((FLS_AR_RELEASE_MAJOR_VERSION_CFG    != FLS_C40_IP_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (FLS_AR_RELEASE_MINOR_VERSION_CFG    != FLS_C40_IP_AR_RELEASE_MINOR_VERSION_CFG) || \
     (FLS_AR_RELEASE_REVISION_VERSION_CFG != FLS_C40_IP_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Fls_Cfg.h and C40_Ip_Cfg.h are different"
#endif
/* Check if current file and C40_Ip_Cfg header file are of the same Software version */
#if ((FLS_SW_MAJOR_VERSION_CFG != FLS_C40_IP_SW_MAJOR_VERSION_CFG) || \
     (FLS_SW_MINOR_VERSION_CFG != FLS_C40_IP_SW_MINOR_VERSION_CFG) || \
     (FLS_SW_PATCH_VERSION_CFG != FLS_C40_IP_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Fls_Cfg.h and C40_Ip_Cfg.h are different"
#endif



/* Check if current file and Qspi_Ip_Cfg header file are of the same vendor */
#if (FLS_VENDOR_ID_CFG != QSPI_IP_VENDOR_ID_CFG)
    #error "Fls_Cfg.h and Qspi_Ip_Cfg.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Cfg header file are of the same Autosar version */
#if ((FLS_AR_RELEASE_MAJOR_VERSION_CFG    != QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (FLS_AR_RELEASE_MINOR_VERSION_CFG    != QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG) || \
     (FLS_AR_RELEASE_REVISION_VERSION_CFG != QSPI_IP_AR_RELEASE_REVISION_VERSION_CFG) \
    )
#error "AutoSar Version Numbers of Fls_Cfg.h and Qspi_Ip_Cfg.h are different"
#endif
/* Check if current file and Qspi_Ip_Cfg header file are of the same software version */
#if ((FLS_SW_MAJOR_VERSION_CFG != QSPI_IP_SW_MAJOR_VERSION_CFG) || \
     (FLS_SW_MINOR_VERSION_CFG != QSPI_IP_SW_MINOR_VERSION_CFG) || \
     (FLS_SW_PATCH_VERSION_CFG != QSPI_IP_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Fls_Cfg.h and Qspi_Ip_Cfg.h are different"
#endif


/* Check if current file and Fls_PBcfg header file are of the same vendor */
#if (FLS_VENDOR_ID_CFG != FLS_PBCFG_VENDOR_ID)
    #error "Fls_Cfg.h and Fls_PBcfg.h have different vendor ids"
#endif
/* Check if current file and Fls_PBcfg header file are of the same Autosar version */
#if ((FLS_AR_RELEASE_MAJOR_VERSION_CFG    != FLS_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (FLS_AR_RELEASE_MINOR_VERSION_CFG    != FLS_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (FLS_AR_RELEASE_REVISION_VERSION_CFG != FLS_PBCFG_AR_RELEASE_REVISION_VERSION) \
    )
#error "AutoSar Version Numbers of Fls_Cfg.h and Fls_PBcfg.h are different"
#endif
/* Check if current file and Fls_PBcfg header file are of the same software version */
#if ((FLS_SW_MAJOR_VERSION_CFG != FLS_PBCFG_SW_MAJOR_VERSION) || \
     (FLS_SW_MINOR_VERSION_CFG != FLS_PBCFG_SW_MINOR_VERSION) || \
     (FLS_SW_PATCH_VERSION_CFG != FLS_PBCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Fls_Cfg.h and Fls_PBcfg.h are different"
#endif


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

#define FLS_CONFIG_EXT \
    FLS_CONFIG_PB
/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL CONSTANT DECLARATIONS
==================================================================================================*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* FLS_CFG_H */
