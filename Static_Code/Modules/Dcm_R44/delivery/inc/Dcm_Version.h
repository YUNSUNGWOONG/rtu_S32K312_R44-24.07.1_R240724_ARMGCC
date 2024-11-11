/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Dcm_Version.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_Version                                      **
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
** 1.0.0     31-Dec-2019   LanhLT         AR440 Implementation                **
** 1.0.0     16-Aug-2020   LanhLT         Update version for Csm and KeyM     **
** 1.0.0     16-Sep-2020   HueKM          Update version for Rte, NvM and BswM**
*******************************************************************************/

#ifndef DCM_VERSION_H
#define DCM_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_Types.h"
#include "Dcm_Cfg.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR SPECIFICATION VERSION */
#define DCM_VERSION_AR_RELEASE_MAJOR_VERSION        4
#define DCM_VERSION_AR_RELEASE_MINOR_VERSION        4
#define DCM_VERSION_AR_RELEASE_REVISION_VERSION     0

/* SOFTWARE VERSION INFORMATION */
#define DCM_VERSION_SW_MAJOR_VERSION                1
#define DCM_VERSION_SW_MINOR_VERSION                0

#define DCM_DET_AR_RELEASE_MAJOR_VERSION            4
#define DCM_DET_AR_RELEASE_MINOR_VERSION            4

#define DCM_RTE_AR_RELEASE_MAJOR_VERSION            4
#define DCM_RTE_AR_RELEASE_MINOR_VERSION            4

#define DCM_DEM_AR_RELEASE_MAJOR_VERSION            4
#define DCM_DEM_AR_RELEASE_MINOR_VERSION            4

#define DCM_COMM_AR_RELEASE_MAJOR_VERSION           4
#define DCM_COMM_AR_RELEASE_MINOR_VERSION           4

#define DCM_PDUR_AR_RELEASE_MAJOR_VERSION           4
#define DCM_PDUR_AR_RELEASE_MINOR_VERSION           4

#define DCM_NVM_AR_RELEASE_MAJOR_VERSION            4
#define DCM_NVM_AR_RELEASE_MINOR_VERSION            4

#define DCM_IOHWAB_AR_RELEASE_MAJOR_VERSION         4
#define DCM_IOHWAB_AR_RELEASE_MINOR_VERSION         4

#define DCM_BSWM_AR_RELEASE_MAJOR_VERSION           4
#define DCM_BSWM_AR_RELEASE_MINOR_VERSION           4

#define DCM_CSM_AR_RELEASE_MAJOR_VERSION            4
#define DCM_CSM_AR_RELEASE_MINOR_VERSION            4

#define DCM_KEYM_AR_RELEASE_MAJOR_VERSION           4
#define DCM_KEYM_AR_RELEASE_MINOR_VERSION           4

#endif /* DCM_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
