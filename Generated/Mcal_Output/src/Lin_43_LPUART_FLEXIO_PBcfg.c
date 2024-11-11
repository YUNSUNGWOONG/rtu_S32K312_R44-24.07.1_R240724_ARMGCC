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
*   @file    Lin_PBcfg.c
*   @implements Lin_PBcfg.c_Artifact
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
#include "Lin_43_LPUART_FLEXIO_Cfg.h"
#include "Lin_43_LPUART_FLEXIO_Ipw_Cfg.h"
#include "Std_Types.h"

#if (STD_OFF == LIN_43_LPUART_FLEXIO_DISABLE_DEM_REPORT_ERROR_STATUS)
#include "Dem.h"
#endif /* STD_OFF == LIN_43_LPUART_FLEXIO_DISABLE_DEM_REPORT_ERROR_STATUS */

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define LIN_43_LPUART_FLEXIO_PBCFG_VENDOR_ID_C                     43
#define LIN_43_LPUART_FLEXIO_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define LIN_43_LPUART_FLEXIO_PBCFG_AR_RELEASE_MINOR_VERSION_C      7
#define LIN_43_LPUART_FLEXIO_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define LIN_43_LPUART_FLEXIO_PBCFG_SW_MAJOR_VERSION_C              3
#define LIN_43_LPUART_FLEXIO_PBCFG_SW_MINOR_VERSION_C              0
#define LIN_43_LPUART_FLEXIO_PBCFG_SW_PATCH_VERSION_C              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Lin_43_LPUART_FLEXIO_Cfg.h */
#if (LIN_43_LPUART_FLEXIO_PBCFG_VENDOR_ID_C != LIN_43_LPUART_FLEXIO_CFG_VENDOR_ID)
    #error "Lin_43_LPUART_FLEXIO_PBcfg.c and Lin_43_LPUART_FLEXIO_Cfg.h have different vendor ids"
#endif
#if ((LIN_43_LPUART_FLEXIO_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != LIN_43_LPUART_FLEXIO_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (LIN_43_LPUART_FLEXIO_PBCFG_AR_RELEASE_MINOR_VERSION_C    != LIN_43_LPUART_FLEXIO_CFG_AR_RELEASE_MINOR_VERSION) || \
     (LIN_43_LPUART_FLEXIO_PBCFG_AR_RELEASE_REVISION_VERSION_C != LIN_43_LPUART_FLEXIO_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of Lin_43_LPUART_FLEXIO_PBcfg.c and Lin_43_LPUART_FLEXIO_Cfg.h are different"
#endif
#if ((LIN_43_LPUART_FLEXIO_PBCFG_SW_MAJOR_VERSION_C != LIN_43_LPUART_FLEXIO_CFG_SW_MAJOR_VERSION) || \
     (LIN_43_LPUART_FLEXIO_PBCFG_SW_MINOR_VERSION_C != LIN_43_LPUART_FLEXIO_CFG_SW_MINOR_VERSION) || \
     (LIN_43_LPUART_FLEXIO_PBCFG_SW_PATCH_VERSION_C != LIN_43_LPUART_FLEXIO_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Lin_43_LPUART_FLEXIO_PBcfg.c and Lin_43_LPUART_FLEXIO_Cfg.h are different"
#endif

/* Checks against Lin_43_LPUART_FLEXIO_Ipw_Cfg.h */
#if (LIN_43_LPUART_FLEXIO_PBCFG_VENDOR_ID_C != LIN_43_LPUART_FLEXIO_IPW_CFG_VENDOR_ID)
    #error "Lin_43_LPUART_FLEXIO_PBcfg.c and Lin_43_LPUART_FLEXIO_Ipw_Cfg.h have different vendor ids"
#endif
#if ((LIN_43_LPUART_FLEXIO_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != LIN_43_LPUART_FLEXIO_IPW_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (LIN_43_LPUART_FLEXIO_PBCFG_AR_RELEASE_MINOR_VERSION_C    != LIN_43_LPUART_FLEXIO_IPW_CFG_AR_RELEASE_MINOR_VERSION) || \
     (LIN_43_LPUART_FLEXIO_PBCFG_AR_RELEASE_REVISION_VERSION_C != LIN_43_LPUART_FLEXIO_IPW_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of Lin_43_LPUART_FLEXIO_PBcfg.c and Lin_43_LPUART_FLEXIO_Ipw_Cfg.h are different"
#endif
#if ((LIN_43_LPUART_FLEXIO_PBCFG_SW_MAJOR_VERSION_C != LIN_43_LPUART_FLEXIO_IPW_CFG_SW_MAJOR_VERSION) || \
     (LIN_43_LPUART_FLEXIO_PBCFG_SW_MINOR_VERSION_C != LIN_43_LPUART_FLEXIO_IPW_CFG_SW_MINOR_VERSION) || \
     (LIN_43_LPUART_FLEXIO_PBCFG_SW_PATCH_VERSION_C != LIN_43_LPUART_FLEXIO_IPW_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Lin_43_LPUART_FLEXIO_PBcfg.c and Lin_43_LPUART_FLEXIO_Ipw_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if (STD_OFF == LIN_43_LPUART_FLEXIO_DISABLE_DEM_REPORT_ERROR_STATUS)
        /* Checks against Dem.h */
        #if ((LIN_43_LPUART_FLEXIO_PBCFG_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
             (LIN_43_LPUART_FLEXIO_PBCFG_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) \
            )
            #error "AUTOSAR Version Numbers of Lin_43_LPUART_FLEXIO_PBcfg.c and Dem.h are different"
        #endif
    #endif
#endif

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define LIN_43_LPUART_FLEXIO_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Lin_43_LPUART_FLEXIO_MemMap.h"

/**
* @brief   Export IPW configurations.
*/
LIN_43_LPUART_FLEXIO_IPW_CONFIG_EXT

#define LIN_43_LPUART_FLEXIO_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Lin_43_LPUART_FLEXIO_MemMap.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/
/**
* @brief        All CoreIDs are supported by LIN driver.
*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/
#define LIN_43_LPUART_FLEXIO_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Lin_43_LPUART_FLEXIO_MemMap.h"




/**
* @brief          Configuration for Lin Channel 0 - Configuration:
*                 LinGlobalConfig.
*
* 
*/
static const Lin_43_LPUART_FLEXIO_ChannelConfigType Lin_43_LPUART_FLEXIO_LinChannel_LIN1_UnAllocatedPar =
{
    (uint8)0U, /* Lin Channel ID */
 
    &Lin_43_LPUART_FLEXIO_Ipw_pHwConfigPB_0, /* Pointer to the hardware configuration*/

    LIN_43_LPUART_FLEXIO_UNALLOCATEDPAR_CORE_ID,         /* Partition core id of channel */

    (boolean)TRUE
};

/**
* @brief          Configuration for Lin Channel 1 - Configuration:
*                 LinGlobalConfig.
*
* 
*/
static const Lin_43_LPUART_FLEXIO_ChannelConfigType Lin_43_LPUART_FLEXIO_LinChannel_LIN2_UnAllocatedPar =
{
    (uint8)1U, /* Lin Channel ID */
 
    &Lin_43_LPUART_FLEXIO_Ipw_pHwConfigPB_1, /* Pointer to the hardware configuration*/

    LIN_43_LPUART_FLEXIO_UNALLOCATEDPAR_CORE_ID,         /* Partition core id of channel */

    (boolean)TRUE
};



/**
* @brief          Lin Configuration data for LinGlobalConfig.
*
*/
const Lin_43_LPUART_FLEXIO_ConfigType Lin_43_LPUART_FLEXIO_Config =
{
    LIN_43_LPUART_FLEXIO_UNALLOCATEDPAR_CORE_ID,            /** Core Id */

    {
        /**
        * @brief   Configuration for Lin Channel 0.
        */
        &Lin_43_LPUART_FLEXIO_LinChannel_LIN1_UnAllocatedPar,
        /**
        * @brief   Configuration for Lin Channel 1.
        */
        &Lin_43_LPUART_FLEXIO_LinChannel_LIN2_UnAllocatedPar
    }
};


#define LIN_43_LPUART_FLEXIO_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Lin_43_LPUART_FLEXIO_MemMap.h"

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

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
