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
**  SRC-MODULE: CanTp_Version.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : C header for CanTp_Version                                    **
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
** 1.0.3.1   22-Jun-2022   SMKwon         CP44-94                             **
** 1.0.3     30-May-2022   HieuTM8        R44-Redmine #26803                  **
** 1.0.1     27-Feb-2022   HieuTM8        R44-Redmine #20400                  **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/
#ifndef CANTP_VERSION_H
#define CANTP_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp.h"                /* CAN TP Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: SWS_CanTp_00267 */
/* SWS_CanTp_00267: Version number macros for checking */
/* AUTOSAR Specification Version Information */
/* @Trace: CanTp_SUD_MACRO_008 */
#define CANTP_VERSION_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANTP_VERSION_AR_RELEASE_MINOR_VERSION    0x04u
#define CANTP_VERSION_AR_RELEASE_REVISION_VERSION 0x00u

/* Software Version Information */
#define CANTP_VERSION_SW_MAJOR_VERSION            0x01u
#define CANTP_VERSION_SW_MINOR_VERSION            0x01u
#define CANTP_VERSION_SW_PATCH_VERSION            0x00u

/* Other (Interface) module version information */
#define CANTP_PDUR_AR_RELEASE_MAJOR_VERSION  0x04u
#define CANTP_PDUR_AR_RELEASE_MINOR_VERSION  0x04u

#define CANTP_CANIF_AR_RELEASE_MAJOR_VERSION 0x04u
#define CANTP_CANIF_AR_RELEASE_MINOR_VERSION 0x04u

#if (CANTP_DEV_ERROR_DETECT == STD_ON)
#define CANTP_DET_AR_RELEASE_MAJOR_VERSION   0x04u
#define CANTP_DET_AR_RELEASE_MINOR_VERSION   0x04u
#endif

#define CANTP_RTE_AR_RELEASE_MAJOR_VERSION   0x04u
#define CANTP_RTE_AR_RELEASE_MINOR_VERSION   0x04u

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* CANTP_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

