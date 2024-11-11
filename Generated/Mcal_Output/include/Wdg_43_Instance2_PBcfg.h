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

#ifndef WDG_43_INSTANCE2_PBCFG_H
#define WDG_43_INSTANCE2_PBCFG_H

/**
*   @file
*
*   @addtogroup Wdg
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
* 4) user callback header files
==================================================================================================*/
#include "Wdg_ChannelTypes.h"
#include "Wdg_43_Instance2_Ipw_PBcfg.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define WDG_43_INSTANCE2_VENDOR_ID_PBCFG                    43
#define WDG_43_INSTANCE2_AR_RELEASE_MAJOR_VERSION_PBCFG     4
#define WDG_43_INSTANCE2_AR_RELEASE_MINOR_VERSION_PBCFG     7
#define WDG_43_INSTANCE2_AR_RELEASE_REVISION_VERSION_PBCFG  0
#define WDG_43_INSTANCE2_SW_MAJOR_VERSION_PBCFG             3
#define WDG_43_INSTANCE2_SW_MINOR_VERSION_PBCFG             0
#define WDG_43_INSTANCE2_SW_PATCH_VERSION_PBCFG             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Check if current file and Wdg_ChannelTypes header file are of the same vendor */
#if (WDG_43_INSTANCE2_VENDOR_ID_PBCFG != WDG_CHANNEL_TYPES_VENDOR_ID)
#error "Wdg_43_Instance2_PBcfg.h and Wdg_ChannelTypes.h have different vendor ids"
#endif

/* Check if current file and Wdg_ChannelTypes header file are of the same Autosar version */
#if ((WDG_43_INSTANCE2_AR_RELEASE_MAJOR_VERSION_PBCFG     != WDG_CHANNEL_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (WDG_43_INSTANCE2_AR_RELEASE_MINOR_VERSION_PBCFG     != WDG_CHANNEL_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (WDG_43_INSTANCE2_AR_RELEASE_REVISION_VERSION_PBCFG  != WDG_CHANNEL_TYPES_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Wdg_43_Instance2_PBcfg.h and Wdg_ChannelTypes.h are different"
#endif

/* Check if current file and Wdg_ChannelTypes header file are of the same software version */
#if ((WDG_43_INSTANCE2_SW_MAJOR_VERSION_PBCFG != WDG_CHANNEL_TYPES_SW_MAJOR_VERSION) || \
     (WDG_43_INSTANCE2_SW_MINOR_VERSION_PBCFG != WDG_CHANNEL_TYPES_SW_MINOR_VERSION) || \
     (WDG_43_INSTANCE2_SW_PATCH_VERSION_PBCFG != WDG_CHANNEL_TYPES_SW_PATCH_VERSION))
#error "Software Version Numbers of Wdg_43_Instance2_PBcfg.h and Wdg_ChannelTypes.h are different"
#endif

/* Check if current file and Wdg_43_Instance2_Ipw_PBcfg configuration header file are of the same vendor */
#if (WDG_43_INSTANCE2_VENDOR_ID_PBCFG != WDG_43_INSTANCE2_IPW_VENDOR_ID_PBCFG)
#error "Wdg_43_Instance2_PBcfg.h and Wdg_43_Instance2_Ipw_PBcfg.h have different vendor ids"
#endif

#if ((WDG_43_INSTANCE2_AR_RELEASE_MAJOR_VERSION_PBCFG    != WDG_43_INSTANCE2_IPW_AR_RELEASE_MAJOR_VERSION_PBCFG) || \
     (WDG_43_INSTANCE2_AR_RELEASE_MINOR_VERSION_PBCFG    != WDG_43_INSTANCE2_IPW_AR_RELEASE_MINOR_VERSION_PBCFG) || \
     (WDG_43_INSTANCE2_AR_RELEASE_REVISION_VERSION_PBCFG != WDG_43_INSTANCE2_IPW_AR_RELEASE_REVISION_VERSION_PBCFG))
#error "AutoSar Version Numbers of Wdg_43_Instance2_PBcfg.h and Wdg_43_Instance2_Ipw_PBcfg.h are different"
#endif

#if ((WDG_43_INSTANCE2_SW_MAJOR_VERSION_PBCFG != WDG_43_INSTANCE2_IPW_SW_MAJOR_VERSION_PBCFG) || \
     (WDG_43_INSTANCE2_SW_MINOR_VERSION_PBCFG != WDG_43_INSTANCE2_IPW_SW_MINOR_VERSION_PBCFG) || \
     (WDG_43_INSTANCE2_SW_PATCH_VERSION_PBCFG != WDG_43_INSTANCE2_IPW_SW_PATCH_VERSION_PBCFG))
#error "Software Version Numbers of Wdg_43_Instance2_PBcfg.h and Wdg_43_Instance2_Ipw_PBcfg.h are different"
#endif


/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                            ENUMS
==================================================================================================*/

/*==================================================================================================
*                               STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/



/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* WDG_43_INSTANCE'2`_PBCFG_H */