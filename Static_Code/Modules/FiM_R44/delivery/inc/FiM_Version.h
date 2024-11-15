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
**  SRC-MODULE: FiM_Version.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : C header for FiM_Version.c                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.0.0    11-Sept-2020   ThienVT1        Changes made As per Redmine #15664 **
** 1.0.0    05-June-2020   ThienVT1        Initial Version                    **
*******************************************************************************/
#ifndef FIM_VERSION_H
#define FIM_VERSION_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "FiM_Cfg.h"        /* FiM Cfg Definition Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define FIM_VERSION_AR_RELEASE_MAJOR_VERSION     FIM_AR_RELEASE_MAJOR_VERSION
#define FIM_VERSION_AR_RELEASE_MINOR_VERSION     FIM_AR_RELEASE_MINOR_VERSION
#define FIM_VERSION_AR_RELEASE_REVISION_VERSION  FIM_AR_RELEASE_REVISION_VERSION

/* FiM Software Version Information */
#define FIM_VERSION_SW_MAJOR_VERSION     FIM_SW_MAJOR_VERSION
#define FIM_VERSION_SW_MINOR_VERSION     FIM_SW_MINOR_VERSION

/* Version information of Dem module */
#define FIM_DEM_AR_RELEASE_MAJOR_VERSION         4
#define FIM_DEM_AR_RELEASE_MINOR_VERSION         4

#define FIM_RTE_AR_RELEASE_MAJOR_VERSION         4
#define FIM_RTE_AR_RELEASE_MINOR_VERSION         4

/*Version information of Det module */
#if (FIM_DEV_ERROR_DETECT == STD_ON)
  #define FIM_DET_AR_RELEASE_MAJOR_VERSION       4
  #define FIM_DET_AR_RELEASE_MINOR_VERSION       4
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
    /* Extern for FiM_GetVersionInfo */
/* @Trace: FiM_SUD_MACRO_001*/
#if (FIM_VERSION_INFO_API == STD_ON)
#define FIM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, FIM_CODE) FiM_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, FIM_APPL_DATA)versioninfo
);
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (FIM_VERSION_INFO_API == STD_ON) */
#endif /* FIM_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
