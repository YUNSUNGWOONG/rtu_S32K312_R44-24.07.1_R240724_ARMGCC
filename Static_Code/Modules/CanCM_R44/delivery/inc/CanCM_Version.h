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
**  SRC-MODULE: CanCM_Version.h                                               **
**                                                                            **
**  TARGET    : General CAN Communication Manager                             **
**                                                                            **
**  PRODUCT   : AUTOEVER CAN Communication Manager Module                     **
**                                                                            **
**  PURPOSE   : Header file of CanCM_Version.c                                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.0.9     20-Dec-2023   HieuTM8          CP44-3561                         **
** 1.0.3.1   29-Jun-2022   NhatTD2          CP44-135                          **
** 1.0.1     22-Sep-2021   LinhTT36         Redmine #20380                    **
** 1.0.0     22-Dec-2020   SJ Kim           Initial Version                   **
*******************************************************************************/
#ifndef CANCM_VERSION_H
#define CANCM_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanCM.h"
/* @Trace: CanCM_SUD_MACRO_001 */
/* Autosar Det Specification Version */
#define CANCM_DET_AR_RELEASE_MAJOR_VERSION                (0x04u)
#define CANCM_DET_AR_RELEASE_MINOR_VERSION_FOUR           (0x04u)
#define CANCM_DET_AR_RELEASE_MINOR_VERSION_ZERO           (0x00u)

/* Autosar Dem Specification Version */
#define CANCM_DEM_AR_RELEASE_MAJOR_VERSION                (0x04u)
#define CANCM_DEM_AR_RELEASE_MINOR_VERSION_FOUR           (0x04u)
#define CANCM_DEM_AR_RELEASE_MINOR_VERSION_ZERO           (0x00u)

/* Autosar CanIf Specification Version */
#define CANCM_CANIF_AR_RELEASE_MAJOR_VERSION              (0x04u)
#define CANCM_CANIF_AR_RELEASE_MINOR_VERSION_FOUR         (0x04u)
#define CANCM_CANIF_AR_RELEASE_MINOR_VERSION_ZERO         (0x00u)

/* Autosar CanIf Specification Version */
#define CANCM_ECUM_AR_RELEASE_MAJOR_VERSION               (0x04u)
#define CANCM_ECUM_AR_RELEASE_MINOR_VERSION_FOUR          (0x04u)
#define CANCM_ECUM_AR_RELEASE_MINOR_VERSION_ZERO          (0x00u)

/* Autosar IOHWAB Specification Version */
#define CANCM_IOHWAB_AR_RELEASE_MAJOR_VERSION             (0x04u)
#define CANCM_IOHWAB_AR_RELEASE_MINOR_VERSION_FOUR        (0x04u)
#define CANCM_IOHWAB_AR_RELEASE_MINOR_VERSION_ZERO        (0x00u)

/* Autosar COMM Specification Version */
#define CANCM_COMM_AR_RELEASE_MAJOR_VERSION               (0x04u)
#define CANCM_COMM_AR_RELEASE_MINOR_VERSION_FOUR          (0x04u)
#define CANCM_COMM_AR_RELEASE_MINOR_VERSION_ZERO          (0x00u)

/* Autosar BSWM Specification Version */
#define CANCM_BSWM_AR_RELEASE_MAJOR_VERSION               (0x04u)
#define CANCM_BSWM_AR_RELEASE_MINOR_VERSION_FOUR          (0x04u)
#define CANCM_BSWM_AR_RELEASE_MINOR_VERSION_ZERO          (0x00u)

/* Autosar BSWM Specification Version */
#define CANCM_RTE_AR_RELEASE_MAJOR_VERSION                (0x04u)
#define CANCM_RTE_AR_RELEASE_MINOR_VERSION_FOUR           (0x04u)
#define CANCM_RTE_AR_RELEASE_MINOR_VERSION_ZERO           (0x00u)

#endif
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
