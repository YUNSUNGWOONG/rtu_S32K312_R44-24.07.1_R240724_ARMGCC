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
* @addtogroup  Wdg
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

#include "Wdg_Cfg.h"
#include "Wdg_CfgExt.h"
#ifdef WDG_INSTANCE0
#if (WDG_INSTANCE0 == STD_ON)
  







/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define WDG_VENDOR_ID_PBCFG_C                    43
#define WDG_AR_RELEASE_MAJOR_VERSION_PBCFG_C     4
#define WDG_AR_RELEASE_MINOR_VERSION_PBCFG_C     7
#define WDG_AR_RELEASE_REVISION_VERSION_PBCFG_C  0
#define WDG_SW_MAJOR_VERSION_PBCFG_C             3
#define WDG_SW_MINOR_VERSION_PBCFG_C             0
#define WDG_SW_PATCH_VERSION_PBCFG_C             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and WDG configuration header file are of the same vendor */
#if (WDG_VENDOR_ID_PBCFG_C != WDG_VENDOR_ID_CFG)
#error "Wdg_43_Instance0_PBcfg.c and Wdg_Cfg.h have different vendor ids"
#endif

/* Check if current file and Wdg_Cfg header file are of the same Autosar version */
#if ((WDG_AR_RELEASE_MAJOR_VERSION_PBCFG_C     != WDG_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (WDG_AR_RELEASE_MINOR_VERSION_PBCFG_C     != WDG_AR_RELEASE_MINOR_VERSION_CFG) || \
     (WDG_AR_RELEASE_REVISION_VERSION_PBCFG_C  != WDG_AR_RELEASE_REVISION_VERSION_CFG))
#error "AutoSar Version Numbers of Wdg_43_Instance0_PBcfg.c and Wdg_Cfg.h are different"
#endif

/* Check if current file and Wdg_Cfg header file are of the same software version */
#if ((WDG_SW_MAJOR_VERSION_PBCFG_C != WDG_SW_MAJOR_VERSION_CFG) || \
     (WDG_SW_MINOR_VERSION_PBCFG_C != WDG_SW_MINOR_VERSION_CFG) || \
     (WDG_SW_PATCH_VERSION_PBCFG_C != WDG_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of Wdg_43_Instance0_PBcfg.c and Wdg_Cfg.h are different"
#endif

/* Check if current file and Wdg_CfgExt header file are of the same vendor */
#if (WDG_VENDOR_ID_PBCFG_C != WDG_VENDOR_ID_CFG_EXT)
#error "Wdg_43_Instance0_PBcfg.c and Wdg_CfgExt.h have different vendor ids"
#endif

#if ((WDG_AR_RELEASE_MAJOR_VERSION_PBCFG_C     != WDG_AR_RELEASE_MAJOR_VERSION_CFG_EXT) || \
     (WDG_AR_RELEASE_MINOR_VERSION_PBCFG_C     != WDG_AR_RELEASE_MINOR_VERSION_CFG_EXT) || \
     (WDG_AR_RELEASE_REVISION_VERSION_PBCFG_C  != WDG_AR_RELEASE_REVISION_VERSION_CFG_EXT))
#error "AutoSar Version Numbers of Wdg_43_Instance0_PBcfg.c and Wdg_CfgExt.h are different"
#endif

#if ((WDG_SW_MAJOR_VERSION_PBCFG_C != WDG_SW_MAJOR_VERSION_CFG_EXT) || \
     (WDG_SW_MINOR_VERSION_PBCFG_C != WDG_SW_MINOR_VERSION_CFG_EXT) || \
     (WDG_SW_PATCH_VERSION_PBCFG_C != WDG_SW_PATCH_VERSION_CFG_EXT))
#error "Software Version Numbers of Wdg_43_Instance0_PBcfg.c and Wdg_CfgExt.h are different"
#endif


/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/

#define WDG_START_SEC_CONFIG_DATA_UNSPECIFIED

#include "Wdg_MemMap.h"

static const Wdg_ModeType Wdg_OffModeSettings_0=
{
    (uint32) 0,
    &Wdg_Ipw_OffModeSettings_0

};

static const Wdg_ModeType Wdg_SlowModeSettings_0=
{
    (uint32) 0x7270e0,

    &Wdg_Ipw_SlowModeSettings_0

};

static const Wdg_ModeType Wdg_FastModeSettings_0=
{
    (uint32) 0x16e360,

    &Wdg_Ipw_FastModeSettings_0

};

#define WDG_STOP_SEC_CONFIG_DATA_UNSPECIFIED

#include "Wdg_MemMap.h"

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                     GLOBAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/
#define WDG_START_SEC_CONFIG_DATA_UNSPECIFIED

#include "Wdg_MemMap.h"

    
const Wdg_ConfigType Wdg_Config_0=
{
    WDGIF_OFF_MODE,
    WDG_IPW_INSTANCE0,
#if (WDG_DIRECT_SERVICE == STD_OFF)
        (Gpt_ChannelType)GptConf_GptChannelConfiguration_GptChannelConfiguration_WdgTrig,
    (uint32)30000,
    #endif
    {&Wdg_OffModeSettings_0, &Wdg_SlowModeSettings_0, &Wdg_FastModeSettings_0}
};


#define WDG_STOP_SEC_CONFIG_DATA_UNSPECIFIED

#include "Wdg_MemMap.h"
/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
    *                                      LOCAL FUNCTIONS
==================================================================================================*/


#endif /* #if `WDG_INSTANCE'0 == STD_ON */
#ifdef __cplusplus
}
#endif
#endif
/** @} */
