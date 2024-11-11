/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanNm_Globals.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Network Management Protocol                       **
**                                                                            **
**  PURPOSE   : Global variables for CanNM                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:  No                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By             Description                        **
********************************************************************************
** 1.1.1      07-Oct-2022   NamNT1         CP44 #785, #786, #610, #838, #842  **
**                                         #887                               **
** 1.0.2.1    20-Jun-2022   SM Kwon        CP44-120                           **
** 1.0.0      16-Dec-2020   SHKim          Initial Version                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanNm.h"                /* CANNM APIs header file */
#include "CanNm_IntFunc.h"        /* CANNM Internal functions header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANNM_GLOBALS_C_AR_RELEASE_MAJOR_VERSION    (0x04u)
#define CANNM_GLOBALS_C_AR_RELEASE_MINOR_VERSION    (0x04u)
#define CANNM_GLOBALS_C_AR_RELEASE_REVISION_VERSION (0x00u)

/* CanNm software version information */
#define CANNM_GLOBALS_C_SW_MAJOR_VERSION            (0x01u)
#define CANNM_GLOBALS_C_SW_MINOR_VERSION            (0x02u)
#define CANNM_GLOBALS_C_SW_PATCH_VERSION            (0x00u)

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (CANNM_AR_RELEASE_MAJOR_VERSION != CANNM_GLOBALS_C_AR_RELEASE_MAJOR_VERSION)
#error "CanNm_Globals.c : Mismatch in Specification Major Version"
#endif

#if (CANNM_AR_RELEASE_MINOR_VERSION != CANNM_GLOBALS_C_AR_RELEASE_MINOR_VERSION)
#error "CanNm_Globals.c : Mismatch in Specification Minor Version"
#endif

#if (CANNM_AR_RELEASE_REVISION_VERSION !=\
     CANNM_GLOBALS_C_AR_RELEASE_REVISION_VERSION)
#error "CanNm_Globals.c : Mismatch in Specification Revision Version"
#endif

#if (CANNM_SW_MAJOR_VERSION != CANNM_GLOBALS_C_SW_MAJOR_VERSION)
#error "CanNm_Globals.c : Mismatch in Software Major Version"
#endif

#if (CANNM_SW_MINOR_VERSION != CANNM_GLOBALS_C_SW_MINOR_VERSION)
#error "CanNm_Globals.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define CANNM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* polyspace +2 VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
/* Variable to hold CANNM Initialization Status */
VAR(boolean, CANNM_VAR) CanNm_InitStatus;
#define CANNM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
#define CANNM_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"
/* polyspace +1 VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
VAR(uint8, CANNM_VAR) CanNm_ArrayPnEIRAPdu[CANNM_MAX_PDU_SIZE];
#define CANNM_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"
#endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

#define CANNM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* polyspace +2 VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
VAR(CanNm_Channel, CANNM_VAR_NOINIT)
CanNm_ArrayChannel[CANNM_NUMBER_OF_CHANNEL];
#define CANNM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
#define CANNM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* polyspace +2 VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
VAR(CanNm_TimeType, CANNM_VAR)
CanNm_ArrayPnEIRATimer[(CANNM_NUMBER_OF_PN_FILTER_MASK_BYTE * CANNM_EIGHT)];
#define CANNM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
#define CANNM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* polyspace +2 VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
/* Variable to hold CANNM Meta Data Status */
VAR(boolean, CANNM_VAR) CanNm_RxMetaDataCheck;
#define CANNM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
#define CANNM_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"
/* polyspace +1 VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
VAR(uint8, CANNM_VAR) CanNm_RxMetaData[CANNM_METADATA_LENGTH];
#define CANNM_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"
#endif /* #if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)) */

#if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
#if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
#define CANNM_START_SEC_CONFIG_CONST_POSTBUILD_8
#include "MemMap.h"
/* polyspace +1 VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
P2CONST(uint8, AUTOMATIC, CANNM_APPL_CONST) CanNm_PnFilterMaskBytesPtr;
#define CANNM_STOP_SEC_CONFIG_CONST_POSTBUILD_8
#include "MemMap.h"
#endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */
#endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

#if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
#define CANNM_START_SEC_CONFIG_CONST_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
/* polyspace +1 VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
P2CONST(CanNm_ChannelConfigType, AUTOMATIC, CANNM_APPL_CONST) CanNm_ChannelsDataPtr;
#define CANNM_STOP_SEC_CONFIG_CONST_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

#if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
#define CANNM_START_SEC_CONFIG_CONST_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
/* polyspace +1 VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
P2CONST(CanNm_RxPdu, AUTOMATIC, CANNM_APPL_CONST) CanNm_RxPduId;
#define CANNM_STOP_SEC_CONFIG_CONST_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */

#if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
#define CANNM_START_SEC_VAR_NO_INIT_POSTBUILD_32
#include "MemMap.h"
/* polyspace +1 VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
VAR(uint32, CANNM_VAR) CanNm_NumberOfRxPdu;
#define CANNM_STOP_SEC_VAR_NO_INIT_POSTBUILD_32
#include "MemMap.h"
#endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
