/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanSM_Version.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Header for CanSM_Version.c                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.0.1     14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306           **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/
/* @Trace: CanSM_SUD_FILE_001  */
#ifndef CANSM_VERSION_H
#define CANSM_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM.h"                /* Inclusion of CanSM header */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: CanSM_SUD_MACRO_008  */
/* AUTOSAR Specification Version Information */
#define CANSM_VERSION_H_AR_RELEASE_MAJOR_VERSION         0x04u
#define CANSM_VERSION_H_AR_RELEASE_MINOR_VERSION         0x04u
#define CANSM_VERSION_H_AR_RELEASE_REVISION_VERSION      0x00u

/* Software Version Information */
#define CANSM_VERSION_H_SW_MAJOR_VERSION                 0x01u
#define CANSM_VERSION_H_SW_MINOR_VERSION                 0x00u



/* Other (Interface) module version information */
#define CANSM_CANIF_AR_RELEASE_MAJOR_VERSION   0x04u
#define CANSM_CANIF_AR_RELEASE_MINOR_VERSION   0x04u

#define CANSM_CANNM_AR_RELEASE_MAJOR_VERSION   0x04u
#define CANSM_CANNM_AR_RELEASE_MINOR_VERSION   0x04u

#define CANSM_CANTRCV_AR_RELEASE_MAJOR_VERSION 0x04u
#define CANSM_CANTRCV_AR_RELEASE_MINOR_VERSION 0x04u

#define CANSM_COMM_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANSM_COMM_AR_RELEASE_MINOR_VERSION    0x04u

#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#define CANSM_DET_AR_RELEASE_MAJOR_VERSION     0x04u
#define CANSM_DET_AR_RELEASE_MINOR_VERSION     0x04u
#endif

#define CANSM_DEM_AR_RELEASE_MAJOR_VERSION     0x04u
#define CANSM_DEM_AR_RELEASE_MINOR_VERSION     0x04u

#define CANSM_SCHM_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANSM_SCHM_AR_RELEASE_MINOR_VERSION    0x04u

#define CANSM_BSWM_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANSM_BSWM_AR_RELEASE_MINOR_VERSION    0x04u

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
#endif /* CANSM_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
