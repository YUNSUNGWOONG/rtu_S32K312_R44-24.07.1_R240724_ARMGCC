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

#ifndef FLS_CFG_DEFINES_H
#define FLS_CFG_DEFINES_H

/**
*   @file Fls_Cfg_Defines.h
*
*   @addtogroup FLS
*   @{
*/

/* implements Fls_Cfg_Defines.h_Artifact */

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLS_VENDOR_ID_CFG_DEFINES                    43
#define FLS_AR_RELEASE_MAJOR_VERSION_CFG_DEFINES     4
#define FLS_AR_RELEASE_MINOR_VERSION_CFG_DEFINES     7
#define FLS_AR_RELEASE_REVISION_VERSION_CFG_DEFINES  0
#define FLS_SW_MAJOR_VERSION_CFG_DEFINES             3
#define FLS_SW_MINOR_VERSION_CFG_DEFINES             0
#define FLS_SW_PATCH_VERSION_CFG_DEFINES             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
DEFINES AND MACROS
==================================================================================================*/

/* STD_ON: Flash access code loaded on job start / unloaded on job end or error */
#define FLS_AC_LOAD_ON_JOB_START             (STD_OFF)

#if (FLS_AC_LOAD_ON_JOB_START == STD_ON)
/* Cleaning cache after loading access code to RAM */
#define FLS_CLEAN_CACHE_AFTER_LOAD_AC    (STD_OFF)
#endif

/* Compile switch to enable and disable the Fls Utest Mode function */
#define FLS_UTEST_MODE_API                   (STD_OFF)

/* Enable calculates CRC for items of Fls Configuration */
#define FLS_CHECK_CFG_CRC                    (STD_OFF)

/* Compile switch to enable and disable the Fls_Cancel function */
#define FLS_CANCEL_API                       (STD_ON)

/* Compile switch to enable and disable the Fls_Compare function */
#define FLS_COMPARE_API                      (STD_ON)

/* Compile switch to enable and disable the Fls_BlankCheck function */
#define FLS_BLANK_CHECK_API                  (STD_OFF)

/* Pre-processor switch to enable and disable development error detection */
#define FLS_DEV_ERROR_DETECT                 (STD_ON)

/* Compile switch to enable and disable the Fls_GetJobResult function */
#define FLS_GET_JOB_RESULT_API               (STD_ON)

/* Compile switch to enable and disable the Fls_GetStatus function */
#define FLS_GET_STATUS_API                   (STD_ON)

/* Compile switch to enable and disable the Fls_SetMode function */
#define FLS_SET_MODE_API                     (STD_ON)

/* Pre-processor switch to enable / disable the API to read out the modules version information */
#define FLS_VERSION_INFO_API                 (STD_ON)

/* Pre-processor switch to enable / disable the API to report data storage (ECC) errors to the flash driver */
#define FLS_ECC_CHECK                        (STD_ON)
#define FLS_ECC_CHECK_BY_AUTOSAR_OS          (STD_OFF)


/* External QSPI sectors are present or not in the current configuration. */
#define FLS_QSPI_SECTORS_CONFIGURED          (STD_OFF)

#if (FLS_QSPI_SECTORS_CONFIGURED == STD_ON)
/* Enable the hang recovery feature for the external QuadSPI controller. */
#define FLS_QSPI_HANG_RECOVERY               (STD_OFF)
#endif

/* Pre-processor switch to enable / disable the erase blank check */
#define FLS_ERASE_VERIFICATION_ENABLED       (STD_ON)

/* Pre-processor switch to enable / disable the write verify check */
#define FLS_WRITE_VERIFICATION_ENABLED       (STD_ON)

#if ((STD_ON == FLS_ERASE_VERIFICATION_ENABLED) && (STD_ON == FLS_QSPI_SECTORS_CONFIGURED))
/* The maximum number of bytes to blank check in one cycle of the flash driver job processing function */
#define FLS_MAX_ERASE_BLANK_CHECK        (256U)
#endif

/* Timeout handling enabled */
#define FLS_TIMEOUT_SUPERVISION_ENABLED      (STD_OFF)

/* Enable multicore core synchronization feature. */
#define FLS_MCORE_ENABLED                    (STD_OFF)


/* Internal sectors are present or not in the current configuration. */
#define FLS_INTERNAL_SECTORS_CONFIGURED      (STD_ON)

/* Base address of code flash */
#define FLS_PROGRAM_FLASH_BASE_ADDR          (0x00400000UL)
/* Base address of data flash */
#define FLS_DATA_FLASH_BASE_ADDR             (0x10000000UL)
/* Base address of utest flash */
#define FLS_UTEST_FLASH_BASE_ADDR            (0x1B000000UL)

/* Internal flash write register size */
#define FLS_INTERNAL_WRITE_SIZE              (128UL)


/* Domain ID value */
#define FLS_DOMAIN_ID                        (0U)

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

#endif /* FLS_CFG_DEFINES_H */
