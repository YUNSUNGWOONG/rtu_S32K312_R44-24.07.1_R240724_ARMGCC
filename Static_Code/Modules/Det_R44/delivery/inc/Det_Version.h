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
**  SRC-MODULE: Det_Version.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Default Error Tracer Module                           **
**                                                                            **
**  PURPOSE   : Provision of callback functions and their functionality.      **
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
** 0.0.1     30-Sep-2019   DanhLT2      Initial Version                       **
*******************************************************************************/
#ifndef DET_VERSION_H
#define DET_VERSION_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Det_Cfg.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* @Trace: Det_SUD_MACRO_001*/
/* AUTOSAR Specification Version Information */
#define DET_VERSION_AR_RELEASE_MAJOR_VERSION    4
#define DET_VERSION_AR_RELEASE_MINOR_VERSION    4
#define DET_VERSION_AR_RELEASE_REVISION_VERSION 0

/* DET Software Version Information */
#define DET_VERSION_SW_MAJOR_VERSION            1
#define DET_VERSION_SW_MINOR_VERSION            0
#define DET_VERSION_SW_PATCH_VERSION            0

/* Rte Software Version Information */
#define DET_RTE_AR_RELEASE_MAJOR_VERSION        4
#define DET_RTE_AR_RELEASE_MINOR_VERSION        4

/* Dlt Software Version Information */
#define DET_DLT_AR_RELEASE_MAJOR_VERSION        4
#define DET_DLT_AR_RELEASE_MINOR_VERSION        4


#endif /* DET_VERSION_H */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
