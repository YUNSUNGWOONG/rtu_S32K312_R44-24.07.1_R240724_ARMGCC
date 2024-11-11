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

/**
*   @file Fls_PBcfg.c
*
*   @addtogroup FLS
*   @{
*/

/* implements Fls_PBcfg.c_Artifact */

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Fls.h"
#include "Qspi_Ip_Features.h"
#include "Qspi_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLS_PBCFG_VENDOR_ID_CFG_C                      43
#define FLS_PBCFG_AR_RELEASE_MAJOR_VERSION_CFG_C       4
#define FLS_PBCFG_AR_RELEASE_MINOR_VERSION_CFG_C       7
#define FLS_PBCFG_AR_RELEASE_REVISION_VERSION_CFG_C    0
#define FLS_PBCFG_SW_MAJOR_VERSION_CFG_C               3
#define FLS_PBCFG_SW_MINOR_VERSION_CFG_C               0
#define FLS_PBCFG_SW_PATCH_VERSION_CFG_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Fls header file are of the same vendor */
#if (FLS_PBCFG_VENDOR_ID_CFG_C != FLS_VENDOR_ID)
    #error "Fls_PBcfg.c and Fls.h have different vendor ids"
#endif
/* Check if current file and Fls header file are of the same Autosar version */
#if ((FLS_PBCFG_AR_RELEASE_MAJOR_VERSION_CFG_C    != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (FLS_PBCFG_AR_RELEASE_MINOR_VERSION_CFG_C    != FLS_AR_RELEASE_MINOR_VERSION) || \
     (FLS_PBCFG_AR_RELEASE_REVISION_VERSION_CFG_C != FLS_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Fls_PBcfg.c and Fls.h are different"
#endif
/* Check if current file and Fls header file are of the same Software version */
#if ((FLS_PBCFG_SW_MAJOR_VERSION_CFG_C != FLS_SW_MAJOR_VERSION) || \
     (FLS_PBCFG_SW_MINOR_VERSION_CFG_C != FLS_SW_MINOR_VERSION) || \
     (FLS_PBCFG_SW_PATCH_VERSION_CFG_C != FLS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Fls_PBcfg.c and Fls.h are different"
#endif

/* Check if current file and Qspi_Ip_Features header file are of the same vendor */
#if (FLS_PBCFG_VENDOR_ID_CFG_C != QSPI_IP_FEATURES_VENDOR_ID_CFG)
    #error "Fls_PBcfg.c and Qspi_Ip_Features.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Features header file are of the same Autosar version */
#if ((FLS_PBCFG_AR_RELEASE_MAJOR_VERSION_CFG_C    != QSPI_IP_FEATURES_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (FLS_PBCFG_AR_RELEASE_MINOR_VERSION_CFG_C    != QSPI_IP_FEATURES_AR_RELEASE_MINOR_VERSION_CFG) || \
     (FLS_PBCFG_AR_RELEASE_REVISION_VERSION_CFG_C != QSPI_IP_FEATURES_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Fls_PBcfg.c and Qspi_Ip_Features.h are different"
#endif
/* Check if current file and Qspi_Ip_Features header file are of the same Software version */
#if ((FLS_PBCFG_SW_MAJOR_VERSION_CFG_C != QSPI_IP_FEATURES_SW_MAJOR_VERSION_CFG) || \
     (FLS_PBCFG_SW_MINOR_VERSION_CFG_C != QSPI_IP_FEATURES_SW_MINOR_VERSION_CFG) || \
     (FLS_PBCFG_SW_PATCH_VERSION_CFG_C != QSPI_IP_FEATURES_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Fls_PBcfg.c and Qspi_Ip_Features.h are different"
#endif

/* Check if current file and Qspi_Ip_Cfg header file are of the same vendor */
#if (FLS_PBCFG_VENDOR_ID_CFG_C != QSPI_IP_VENDOR_ID_CFG)
    #error "Fls_PBcfg.c and Qspi_Ip_Cfg.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Cfg header file are of the same Autosar version */
#if ((FLS_PBCFG_AR_RELEASE_MAJOR_VERSION_CFG_C    != QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (FLS_PBCFG_AR_RELEASE_MINOR_VERSION_CFG_C    != QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG) || \
     (FLS_PBCFG_AR_RELEASE_REVISION_VERSION_CFG_C != QSPI_IP_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Fls_PBcfg.c and Qspi_Ip_Cfg.h are different"
#endif
/* Check if current file and Qspi_Ip_Cfg header file are of the same Software version */
#if ((FLS_PBCFG_SW_MAJOR_VERSION_CFG_C != QSPI_IP_SW_MAJOR_VERSION_CFG) || \
     (FLS_PBCFG_SW_MINOR_VERSION_CFG_C != QSPI_IP_SW_MINOR_VERSION_CFG) || \
     (FLS_PBCFG_SW_PATCH_VERSION_CFG_C != QSPI_IP_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Fls_PBcfg.c and Qspi_Ip_Cfg.h are different"
#endif

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
/* Declaration of Fls notification function (Fee_JobEndNotification())*/
extern void Fee_JobEndNotification( void );

/* Declaration of Fls notification function (Fee_JobErrorNotification())*/
extern void Fee_JobErrorNotification( void );

#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

                    
#define FLS_START_SEC_CONFIG_DATA_8
#include "Fls_MemMap.h"

/* aFlsSectorFlags */
static const uint8 FlsConfigSet_aFlsSectorFlags[11U] =
{
    (uint8)FLS_SECTOR_ERASE_ASYNCH,  /* FlsSector_0 */
    (uint8)FLS_SECTOR_ERASE_ASYNCH,  /* FlsSector_1 */
    (uint8)FLS_SECTOR_ERASE_ASYNCH,  /* FlsSector_2 */
    (uint8)FLS_SECTOR_ERASE_ASYNCH,  /* FlsSector_3 */
    (uint8)FLS_SECTOR_ERASE_ASYNCH,  /* FlsSector_4 */
    (uint8)FLS_SECTOR_ERASE_ASYNCH,  /* FlsSector_5 */
    (uint8)FLS_SECTOR_ERASE_ASYNCH,  /* FlsSector_6 */
    (uint8)FLS_SECTOR_ERASE_ASYNCH,  /* FlsSector_7 */
    (uint8)FLS_SECTOR_ERASE_ASYNCH,  /* FlsSector_8 */
    (uint8)FLS_SECTOR_ERASE_ASYNCH,  /* FlsSector_9 */
    (uint8)FLS_SECTOR_ERASE_ASYNCH   /* FlsSector_10 */
};

#define FLS_STOP_SEC_CONFIG_DATA_8
#include "Fls_MemMap.h"



#define FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"

/* aFlsSectorEndAddr */
static const Fls_AddressType FlsConfigSet_aFlsSectorEndAddr[11U] =
{
    (Fls_AddressType)8191U,  /* FlsSector_0 */
    (Fls_AddressType)16383U,  /* FlsSector_1 */
    (Fls_AddressType)24575U,  /* FlsSector_2 */
    (Fls_AddressType)32767U,  /* FlsSector_3 */
    (Fls_AddressType)40959U,  /* FlsSector_4 */
    (Fls_AddressType)49151U,  /* FlsSector_5 */
    (Fls_AddressType)57343U,  /* FlsSector_6 */
    (Fls_AddressType)65535U,  /* FlsSector_7 */
    (Fls_AddressType)73727U,  /* FlsSector_8 */
    (Fls_AddressType)81919U,  /* FlsSector_9 */
    (Fls_AddressType)90111U   /* FlsSector_10 */
};

/* paSectorSize */
static const Fls_LengthType FlsConfigSet_aFlsSectorSize[11U] =
{
    (Fls_LengthType)8192U,  /* FlsSector_0 */
    (Fls_LengthType)8192U,  /* FlsSector_1 */
    (Fls_LengthType)8192U,  /* FlsSector_2 */
    (Fls_LengthType)8192U,  /* FlsSector_3 */
    (Fls_LengthType)8192U,  /* FlsSector_4 */
    (Fls_LengthType)8192U,  /* FlsSector_5 */
    (Fls_LengthType)8192U,  /* FlsSector_6 */
    (Fls_LengthType)8192U,  /* FlsSector_7 */
    (Fls_LengthType)8192U,  /* FlsSector_8 */
    (Fls_LengthType)8192U,  /* FlsSector_9 */
    (Fls_LengthType)8192U   /* FlsSector_10 */
};

/* paSectorPageSize */
static const Fls_LengthType FlsConfigSet_aFlsSectorPageSize[11U] =
{
    (Fls_LengthType)8U,  /* FlsSector_0 */
    (Fls_LengthType)8U,  /* FlsSector_1 */
    (Fls_LengthType)8U,  /* FlsSector_2 */
    (Fls_LengthType)8U,  /* FlsSector_3 */
    (Fls_LengthType)8U,  /* FlsSector_4 */
    (Fls_LengthType)8U,  /* FlsSector_5 */
    (Fls_LengthType)8U,  /* FlsSector_6 */
    (Fls_LengthType)8U,  /* FlsSector_7 */
    (Fls_LengthType)8U,  /* FlsSector_8 */
    (Fls_LengthType)8U,  /* FlsSector_9 */
    (Fls_LengthType)8U   /* FlsSector_10 */
};

/* Info structure (reg prot, ecc trigger, etc) for each internal flash sector. */
static const Fls_Flash_InternalSectorInfoType FlsSector_0_FlsConfigSet_sInternalSectorInfo =
{
    (FLS_DATA_FLASH_BASE_ADDR + 0x000000UL),  /* pSectorStartAddressPtr */
    0U  /* Sector location to calculate cfgCRC */
};

static const Fls_Flash_InternalSectorInfoType FlsSector_1_FlsConfigSet_sInternalSectorInfo =
{
    (FLS_DATA_FLASH_BASE_ADDR + 0x002000UL),  /* pSectorStartAddressPtr */
    1U  /* Sector location to calculate cfgCRC */
};

static const Fls_Flash_InternalSectorInfoType FlsSector_2_FlsConfigSet_sInternalSectorInfo =
{
    (FLS_DATA_FLASH_BASE_ADDR + 0x004000UL),  /* pSectorStartAddressPtr */
    2U  /* Sector location to calculate cfgCRC */
};

static const Fls_Flash_InternalSectorInfoType FlsSector_3_FlsConfigSet_sInternalSectorInfo =
{
    (FLS_DATA_FLASH_BASE_ADDR + 0x006000UL),  /* pSectorStartAddressPtr */
    3U  /* Sector location to calculate cfgCRC */
};

static const Fls_Flash_InternalSectorInfoType FlsSector_4_FlsConfigSet_sInternalSectorInfo =
{
    (FLS_DATA_FLASH_BASE_ADDR + 0x008000UL),  /* pSectorStartAddressPtr */
    4U  /* Sector location to calculate cfgCRC */
};

static const Fls_Flash_InternalSectorInfoType FlsSector_5_FlsConfigSet_sInternalSectorInfo =
{
    (FLS_DATA_FLASH_BASE_ADDR + 0x00A000UL),  /* pSectorStartAddressPtr */
    5U  /* Sector location to calculate cfgCRC */
};

static const Fls_Flash_InternalSectorInfoType FlsSector_6_FlsConfigSet_sInternalSectorInfo =
{
    (FLS_DATA_FLASH_BASE_ADDR + 0x00C000UL),  /* pSectorStartAddressPtr */
    6U  /* Sector location to calculate cfgCRC */
};

static const Fls_Flash_InternalSectorInfoType FlsSector_7_FlsConfigSet_sInternalSectorInfo =
{
    (FLS_DATA_FLASH_BASE_ADDR + 0x00E000UL),  /* pSectorStartAddressPtr */
    7U  /* Sector location to calculate cfgCRC */
};

static const Fls_Flash_InternalSectorInfoType FlsSector_8_FlsConfigSet_sInternalSectorInfo =
{
    (FLS_DATA_FLASH_BASE_ADDR + 0x010000UL),  /* pSectorStartAddressPtr */
    8U  /* Sector location to calculate cfgCRC */
};

static const Fls_Flash_InternalSectorInfoType FlsSector_9_FlsConfigSet_sInternalSectorInfo =
{
    (FLS_DATA_FLASH_BASE_ADDR + 0x012000UL),  /* pSectorStartAddressPtr */
    9U  /* Sector location to calculate cfgCRC */
};

static const Fls_Flash_InternalSectorInfoType FlsSector_10_FlsConfigSet_sInternalSectorInfo =
{
    (FLS_DATA_FLASH_BASE_ADDR + 0x014000UL),  /* pSectorStartAddressPtr */
    10U  /* Sector location to calculate cfgCRC */
};


/* FLASH physical sectorization description */
static const Fls_Flash_InternalSectorInfoType * const FlsConfigSet_aSectorList[11U] =
{
    &FlsSector_0_FlsConfigSet_sInternalSectorInfo,  /* FLS_DATA_ARRAY_0_BLOCK_2_S000 */
    &FlsSector_1_FlsConfigSet_sInternalSectorInfo,  /* FLS_DATA_ARRAY_0_BLOCK_2_S001 */
    &FlsSector_2_FlsConfigSet_sInternalSectorInfo,  /* FLS_DATA_ARRAY_0_BLOCK_2_S002 */
    &FlsSector_3_FlsConfigSet_sInternalSectorInfo,  /* FLS_DATA_ARRAY_0_BLOCK_2_S003 */
    &FlsSector_4_FlsConfigSet_sInternalSectorInfo,  /* FLS_DATA_ARRAY_0_BLOCK_2_S004 */
    &FlsSector_5_FlsConfigSet_sInternalSectorInfo,  /* FLS_DATA_ARRAY_0_BLOCK_2_S005 */
    &FlsSector_6_FlsConfigSet_sInternalSectorInfo,  /* FLS_DATA_ARRAY_0_BLOCK_2_S006 */
    &FlsSector_7_FlsConfigSet_sInternalSectorInfo,  /* FLS_DATA_ARRAY_0_BLOCK_2_S007 */
    &FlsSector_8_FlsConfigSet_sInternalSectorInfo,  /* FLS_DATA_ARRAY_0_BLOCK_2_S008 */
    &FlsSector_9_FlsConfigSet_sInternalSectorInfo,  /* FLS_DATA_ARRAY_0_BLOCK_2_S009 */
    &FlsSector_10_FlsConfigSet_sInternalSectorInfo   /* FLS_DATA_ARRAY_0_BLOCK_2_S010 */
};

/* paHwCh */
static const Fls_HwChType FlsConfigSet_paHwCh[11U] =
{
    FLS_CH_INTERN,  /* FlsSector_0 */
    FLS_CH_INTERN,  /* FlsSector_1 */
    FLS_CH_INTERN,  /* FlsSector_2 */
    FLS_CH_INTERN,  /* FlsSector_3 */
    FLS_CH_INTERN,  /* FlsSector_4 */
    FLS_CH_INTERN,  /* FlsSector_5 */
    FLS_CH_INTERN,  /* FlsSector_6 */
    FLS_CH_INTERN,  /* FlsSector_7 */
    FLS_CH_INTERN,  /* FlsSector_8 */
    FLS_CH_INTERN,  /* FlsSector_9 */
    FLS_CH_INTERN   /* FlsSector_10 */
};

/* paSectorHwAddress */
static const Fls_AddressType FlsConfigSet_paSectorHwAddress[11U] =
{
    (Fls_AddressType)0U,  /* FlsSector_0 */
    (Fls_AddressType)0U,  /* FlsSector_1 */
    (Fls_AddressType)0U,  /* FlsSector_2 */
    (Fls_AddressType)0U,  /* FlsSector_3 */
    (Fls_AddressType)0U,  /* FlsSector_4 */
    (Fls_AddressType)0U,  /* FlsSector_5 */
    (Fls_AddressType)0U,  /* FlsSector_6 */
    (Fls_AddressType)0U,  /* FlsSector_7 */
    (Fls_AddressType)0U,  /* FlsSector_8 */
    (Fls_AddressType)0U,  /* FlsSector_9 */
    (Fls_AddressType)0U   /* FlsSector_10 */
};



/**
* @brief        Structure used to set function pointers notification, working mode
*/
/* Fls module initialization data (FlsConfigSet)*/
const Fls_ConfigType Fls_Config =
{
#if (STD_ON == FLS_AC_LOAD_ON_JOB_START)
    (Fls_AcErasePtrType)NULL_PTR,                                     /* FlsAcErase */
    (Fls_AcWritePtrType)NULL_PTR,                                     /* FlsAcWrite */
#endif
    NULL_PTR,                                                         /* FlsACCallback */
    &Fee_JobEndNotification,                                          /* FlsJobEndNotification */
    &Fee_JobErrorNotification,                                        /* FlsJobErrorNotification */
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
    NULL_PTR,                                                         /* FlsMCoreTimeoutNotification */
#endif
#if (STD_ON == FLS_ECC_CHECK_BY_AUTOSAR_OS)
    NULL_PTR,                                                         /* FlsReadFunctionCallout */
#endif        
    MEMIF_MODE_FAST,                                                  /* FlsDefaultMode */
    48U,                                                              /* FlsMaxReadFastMode */
    24U,                                                              /* FlsMaxReadNormalMode */
    256U,                                                             /* FlsMaxWriteFastMode */
    128U,                                                             /* FlsMaxWriteNormalMode */
    11U,                                                              /* FlsSectorCount */
    &FlsConfigSet_aFlsSectorEndAddr,                                  /* (*paSectorEndAddr)[] */
    &FlsConfigSet_aFlsSectorSize,                                     /* (*paSectorSize)[] */
    &FlsConfigSet_aSectorList,                                        /* (*pSectorList)[] */
    &FlsConfigSet_aFlsSectorFlags,                                    /* (*paSectorFlags)[] */
    &FlsConfigSet_aFlsSectorPageSize,                                 /* (*paSectorPageSize)[] */
    &FlsConfigSet_paHwCh,                                             /* (*paHwCh)[] */
    &FlsConfigSet_paSectorHwAddress,                                  /* (*paSectorHwAddress)[] */
    NULL_PTR,                                                         /* FlsQspiConfig */
    &FlsConfigSet_InitCfg,                                            /* FlsInternalConfig */
#if (STD_ON == FLS_CHECK_CFG_CRC)
    10340U                                                            /* configCrc */
#endif
};


#define FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @}*/

