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
**  SRC-MODULE: CanTp_Ram.h                                                   **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CANTP MODULE                                          **
**                                                                            **
**  PURPOSE   : Header file for CanTp_Ram.c                                   **
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
#ifndef CANTP_RAM_H
#define CANTP_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
 /* @Trace: SWS_CanTp_00267 */
 /* @Trace: CanTp_SUD_MACRO_005 */
/* SWS_CanTp_00267: Version number macros for checking */
/* AUTOSAR specification version information */
#define CANTP_RAM_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANTP_RAM_AR_RELEASE_MINOR_VERSION    0x04u
#define CANTP_RAM_AR_RELEASE_REVISION_VERSION 0x00u

/* CANTP software version information */
#define CANTP_RAM_SW_MAJOR_VERSION            0x01u
#define CANTP_RAM_SW_MINOR_VERSION            0x01u
#define CANTP_RAM_SW_PATCH_VERSION            0x00u

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define CANTP_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Global variable to store CanTp Initialization status */
/* @Trace: CanTp_SUD_GLOBALVAR_018 */
extern VAR(boolean, CANTP_VAR) CanTp_InitStatus;
#define CANTP_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
#define CANTP_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
extern VAR(uint16, CANTP_VAR) CanTp_NumOfChannel;
#define CANTP_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */


/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/

#endif /* CANTP_RAM_H */

/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/

