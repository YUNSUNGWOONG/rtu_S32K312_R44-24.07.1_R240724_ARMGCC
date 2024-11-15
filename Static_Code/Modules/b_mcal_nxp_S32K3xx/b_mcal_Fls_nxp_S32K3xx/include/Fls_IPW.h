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
/*==================================================================================================
==================================================================================================*/

#ifndef FLS_IPW_H
#define FLS_IPW_H

/**
*   @file Fls_IPW.h
*
*   @addtogroup FLS
*   @{
*/
/* implements Fls_IPW.h_Artifact */
#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Fls.h"
#include "Qspi_Ip_Features.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLS_IPW_VENDOR_ID_H                       43
#define FLS_IPW_AR_RELEASE_MAJOR_VERSION_H        4
#define FLS_IPW_AR_RELEASE_MINOR_VERSION_H        7
#define FLS_IPW_AR_RELEASE_REVISION_VERSION_H     0
#define FLS_IPW_SW_MAJOR_VERSION_H                3
#define FLS_IPW_SW_MINOR_VERSION_H                0
#define FLS_IPW_SW_PATCH_VERSION_H                0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Fls header file are of the same vendor */
#if (FLS_IPW_VENDOR_ID_H != FLS_VENDOR_ID)
    #error "Fls_IPW.c and Fls.h have different vendor ids"
#endif
/* Check if current file and Fls header file are of the same Autosar version */
#if ((FLS_IPW_AR_RELEASE_MAJOR_VERSION_H    != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (FLS_IPW_AR_RELEASE_MINOR_VERSION_H    != FLS_AR_RELEASE_MINOR_VERSION) || \
     (FLS_IPW_AR_RELEASE_REVISION_VERSION_H != FLS_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Fls_IPW.c and Fls.h are different"
#endif
/* Check if current file and Fls header file are of the same Software version */
#if ((FLS_IPW_SW_MAJOR_VERSION_H != FLS_SW_MAJOR_VERSION) || \
     (FLS_IPW_SW_MINOR_VERSION_H != FLS_SW_MINOR_VERSION) || \
     (FLS_IPW_SW_PATCH_VERSION_H != FLS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Fls_IPW.c and Fls.h are different"
#endif

/* Check if current file and Qspi_Ip_Features header file are of the same vendor */
#if (FLS_IPW_VENDOR_ID_H != QSPI_IP_FEATURES_VENDOR_ID_CFG)
    #error "Fls_IPW.c and Qspi_Ip_Features.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Features header file are of the same Autosar version */
#if ((FLS_IPW_AR_RELEASE_MAJOR_VERSION_H    != QSPI_IP_FEATURES_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (FLS_IPW_AR_RELEASE_MINOR_VERSION_H    != QSPI_IP_FEATURES_AR_RELEASE_MINOR_VERSION_CFG) || \
     (FLS_IPW_AR_RELEASE_REVISION_VERSION_H != QSPI_IP_FEATURES_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Fls_IPW.c and Qspi_Ip_Features.h are different"
#endif
/* Check if current file and Qspi_Ip_Features header file are of the same Software version */
#if ((FLS_IPW_SW_MAJOR_VERSION_H != QSPI_IP_FEATURES_SW_MAJOR_VERSION_CFG) || \
     (FLS_IPW_SW_MINOR_VERSION_H != QSPI_IP_FEATURES_SW_MINOR_VERSION_CFG) || \
     (FLS_IPW_SW_PATCH_VERSION_H != QSPI_IP_FEATURES_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Fls_IPW.c and Qspi_Ip_Features.h are different"
#endif

/*******************************************************************************
* Definitions
******************************************************************************/

/*! Invalid configuration, specifies unused device */
#define FLS_IPW_CFG_INVALID          (uint8)0xFFU


/*==================================================================================================
*                                    VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    DEFINES AND MACROS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"

void Fls_IPW_Init(void);
#if (FLS_QSPI_SECTORS_CONFIGURED == STD_ON)
void Fls_IPW_AbortSuspended(void);
#endif
void Fls_IPW_ClearHVJob(void);
void Fls_IPW_Cancel(void);
void Fls_IPW_LLDMainFunction(void);

Fls_LLDReturnType Fls_IPW_SectorRead(const Fls_AddressType SectorOffset,
                                     const Fls_AddressType Length,
                                     uint8 *JobDataDestPtr,
                                     const uint8 *JobDataSrcPtr
                                    );

Fls_LLDReturnType Fls_IPW_SectorErase(const Fls_AddressType SectorOffset,
                                      const Fls_LengthType PhysicalSectorSize,
                                      const boolean Asynch
                                     );

Fls_LLDReturnType Fls_IPW_SectorWrite(const Fls_AddressType SectorOffset,
                                      const Fls_AddressType Length,
                                      const uint8 *JobDataSrcPtr,
                                      const boolean Asynch
                                     );

#if ( STD_ON == FLS_INTERNAL_SECTORS_CONFIGURED )
#if ( (STD_ON == FLS_ECC_CHECK) || (STD_ON == FLS_ECC_CHECK_BY_AUTOSAR_OS) )
Fls_CompHandlerReturnType Fls_IPW_DsiHandler(const Fls_ExceptionDetailsType *ExceptionDetailsPtr);
#endif /* (STD_ON == FLS_ECC_CHECK) || (STD_ON == FLS_ECC_CHECK_BY_AUTOSAR_OS) */

#if (STD_ON == FLS_ECC_CHECK_BY_AUTOSAR_OS)
void Fls_IPW_ReadEachBlock(void);
#endif /* STD_ON == FLS_ECC_CHECK_BY_AUTOSAR_OS */
#endif /* STD_ON == FLS_INTERNAL_SECTORS_CONFIGURED */

#if ( STD_ON == FLS_AC_LOAD_ON_JOB_START )
Fls_BlockNumberOfSectorType Fls_IPW_GetBlockNumberFromAddress(Fls_AddressType TargetAddress);
#endif /* STD_ON == FLS_AC_LOAD_ON_JOB_START */

#if (STD_ON == FLS_UTEST_MODE_API)
Fls_LLDReturnType Fls_IPW_CheckUserTestStatus(const Fls_MisrType *MisrExpectedValues,
                                              Fls_UtestStateType *OpStatus
                                             );

Fls_LLDReturnType Fls_IPW_ArrayIntegrityCheck(uint32 SelectBlock,
                                              Fls_ArrayIntegritySequenceType AddressSequence,
                                              Fls_FlashBreakPointsType BreakPoints,
                                              const Fls_MisrType *MisrSeedValues
                                             );

Fls_LLDReturnType Fls_IPW_ArrayIntegrityCheckSuspend(void);

Fls_LLDReturnType Fls_IPW_ArrayIntegrityCheckResume(void);

Fls_LLDReturnType Fls_IPW_UserMarginReadCheck(uint32 SelectBlock,
                                              Fls_FlashBreakPointsType BreakPoints,
                                              Fls_MarginOptionType MarginLevel,
                                              const Fls_MisrType *MisrSeedValues
                                             );
#endif /* STD_ON == FLS_UTEST_MODE_API */


#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* FLS_IPW_H */
