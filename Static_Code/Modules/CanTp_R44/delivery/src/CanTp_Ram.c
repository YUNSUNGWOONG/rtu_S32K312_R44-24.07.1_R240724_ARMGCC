/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanTp_Ram.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : Global RAM variables of CanTp                                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0     13-Sep-2023   HieuTM8        #CP44-2819                          **
** 1.0.7     31-Oct-2022   HieuTM8        #CP44-1038                          **
** 1.0.3.1   22-Jun-2022   SMKwon         CP44-94                             **
** 1.0.1     28-Feb-2022   HieuTM8        R44-Redmine #20400, #19344          **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "CanTp.h"            /* CanTp PCTypes Header File */
#include "CanTp_Ram.h"            /* CanTp PCTypes Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: SWS_CanTp_00267 */
/* SWS_CanTp_00267: Version number macros for checking */
/* AUTOSAR specification version information */
#define CANTP_RAM_C_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANTP_RAM_C_AR_RELEASE_MINOR_VERSION    0x04u
#define CANTP_RAM_C_AR_RELEASE_REVISION_VERSION 0x00u

/* CANTP software version information */
#define CANTP_RAM_C_SW_MAJOR_VERSION            0x01u
#define CANTP_RAM_C_SW_MINOR_VERSION            0x01u

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANTP_AR_RELEASE_MAJOR_VERSION != CANTP_RAM_C_AR_RELEASE_MAJOR_VERSION)
#error "CanTp_Ram.c : Mismatch in Specification Major Version"
#endif
#if (CANTP_AR_RELEASE_MINOR_VERSION != CANTP_RAM_C_AR_RELEASE_MINOR_VERSION)
#error "CanTp_Ram.c : Mismatch in Specification Minor Version"
#endif
#if (CANTP_AR_RELEASE_REVISION_VERSION !=\
     CANTP_RAM_C_AR_RELEASE_REVISION_VERSION)
#error "CanTp_Ram.c : Mismatch in Specification Revision Version"
#endif
#if (CANTP_SW_MAJOR_VERSION != CANTP_RAM_C_SW_MAJOR_VERSION)
#error "CanTp_Ram.c : Mismatch in Software Major Version"
#endif
#if (CANTP_SW_MINOR_VERSION != CANTP_RAM_C_SW_MINOR_VERSION)
#error "CanTp_Ram.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define CANTP_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Global variable to store CanTp Initialization status */
/* @Trace: SWS_CanTp_00168 */
/* SWS_CanTp_00168: The CanTp module shall be in the CANTP_OFF state after power up */
VAR(boolean, CANTP_VAR) CanTp_InitStatus = CANTP_OFF;
#define CANTP_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
#define CANTP_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, CANTP_VAR) CanTp_NumOfChannel;
#define CANTP_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

