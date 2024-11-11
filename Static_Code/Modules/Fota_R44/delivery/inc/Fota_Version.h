/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_Version.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Fota                                                  **
**                                                                            **
**  PURPOSE   : C header for Fota_Version                                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.0.0     23-Dec-2022   VuPH6       Init version                           **
*******************************************************************************/
#ifndef FOTA_VERSION_H
#define FOTA_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fota.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* AUTOSAR Specification Version Information */
#define FOTA_VERSION_AR_RELEASE_MAJOR_VERSION       4
#define FOTA_VERSION_AR_RELEASE_MINOR_VERSION       4
#define FOTA_VERSION_AR_RELEASE_REVISION_VERSION    0

/* Software Version Information */
#define FOTA_VERSION_SW_MAJOR_VERSION               0
#define FOTA_VERSION_SW_MINOR_VERSION               0
#define FOTA_VERSION_SW_PATCH_VERSION               1

/* Other (Lower) module version information */
#if (FOTA_CSM_SUPPORT == STD_ON)
#define FOTA_CSM_AR_RELEASE_MAJOR_VERSION           4
#define FOTA_CSM_AR_RELEASE_MINOR_VERSION           4
#endif

#define FOTA_MEM_76_PFLS_AR_RELEASE_MAJOR_VERSION   4
#define FOTA_MEM_76_PFLS_AR_RELEASE_MINOR_VERSION   4

#endif /* FOTA_VERSION_H */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
