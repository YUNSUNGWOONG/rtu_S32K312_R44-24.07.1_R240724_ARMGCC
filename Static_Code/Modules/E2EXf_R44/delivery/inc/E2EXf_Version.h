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
 **  SRC-MODULE: E2EXf_Version.h                                               **
 **                                                                            **
 **  TARGET    : All                                                           **
 **                                                                            **
 **  PRODUCT   : AUTOSAR E2E Transformer Module                                **
 **                                                                            **
 **  PURPOSE   : Definition of version information of E2E Transformer Module   **
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
 ** 1.1.1.  30-Jun-2022    Seungjin Noh         #CP44-2597                     ** 
 ** 1.0.2.1  30-Jun-2022    Gongbin Lim         #CP44-321                      **
 ** 1.0.0    04-Dec-2020    Gongbin Lim         Initial Version                **
 ** 1.0.2    28-Aug-2021    HiepVT1             Update to support Det R40      **
 *******************************************************************************/

#ifndef E2EXF_VERSION_H
#define E2EXF_VERSION_H

/*******************************************************************************
 **                      Include Section                                       **
 *******************************************************************************/
#include "E2EXf.h"                   	/* E2E Transformer Header File */

/*******************************************************************************
 **                      Version Information                                   **
 *******************************************************************************/
/* AUTOSAR Specification Version Information */
#define E2EXF_VERSION_AR_RELEASE_MAJOR_VERSION           (4U)
#define E2EXF_VERSION_AR_RELEASE_MINOR_VERSION           (4U)
#define E2EXF_VERSION_AR_RELEASE_REVISION_VERSION        (0U)

/* Software Version Information */
#define E2EXF_VERSION_SW_MAJOR_VERSION                   (1U)
#define E2EXF_VERSION_SW_MINOR_VERSION                   (1U)
#define E2EXF_VERSION_SW_PATCH_VERSION                   (1U)

/*Version information of E2E module */
#define E2EXF_E2E_AR_RELEASE_MAJOR_VERSION               (4U)
#define E2EXF_E2E_AR_RELEASE_MINOR_VERSION               (4U)

/*Version information of DEM module */
#define E2EXF_DEM_AR_RELEASE_MAJOR_VERSION               (4U)
#define E2EXF_DEM_AR_RELEASE_MINOR_VERSION_L             (0U)
#define E2EXF_DEM_AR_RELEASE_MINOR_VERSION_U             (4U)

#if(E2EXF_DEV_ERROR_DETECT == STD_ON)
/*Version information of DET module */
#define E2EXF_DET_AR_RELEASE_MAJOR_VERSION               (4U)
#define E2EXF_DET_AR_RELEASE_MINOR_VERSION_L             (0U)
#define E2EXF_DET_AR_RELEASE_MINOR_VERSION_U             (4U)
#endif /* End of (E2EXF_DEV_ERROR_DETECT == STD_ON) */

#endif /* E2EXF_VERSION_H */
/*******************************************************************************
 **                      End of File                                           **
 *******************************************************************************/
