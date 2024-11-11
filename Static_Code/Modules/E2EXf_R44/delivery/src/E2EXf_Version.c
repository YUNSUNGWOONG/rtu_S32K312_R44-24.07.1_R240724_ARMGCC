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
 **  SRC-MODULE: E2EXf_Version.c                                               **
 **                                                                            **
 **  TARGET    : All                                                           **
 **                                                                            **
 **  PRODUCT   : AUTOSAR E2E Transformer Module                                **
 **                                                                            **
 **  PURPOSE   : Implementation of version check of E2E Transformer Module     **
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
 ** 1.1.1    19-Jul-2023    Seungjin Noh        #CP44-2521                     **
 ** 1.0.2.1  30-Jun-2022    Gongbin Lim         #CP44-321                      **
 ** 1.0.0    04-Dec-2020    Gongbin Lim         Initial Version                **
 ** 1.0.2    23-Aug-2021    HiepVT1             Update code to support         **
 **                                             DEM, DET R40                   **
 *******************************************************************************/

/*******************************************************************************
 **                      Include Section                                       **
 *******************************************************************************/
#include "E2EXf_Version.h"                  /* E2EXf Version File */
#include "E2E.h"                            /* E2E Library Header File */

#if(E2EXF_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                            /* DET Module Header File */
#endif /* End of (E2EXF_DEV_ERROR_DETECT == STD_ON) */

#if defined(DEM_AR_RELEASE_MAJOR_VERSION) \
		&& defined(DEM_AR_RELEASE_MINOR_VERSION)
#include "Dem.h"                            /* DEM Module Header File */
#endif /* End of defined(DEM_AR_RELEASE_MAJOR_VERSION) && defined(DEM_AR_RELEASE_MINOR_VERSION) */

/*******************************************************************************
 **                      File Version Check                                    **
 *******************************************************************************/

/* E2EXF AUTOSAR Version check */
#if ((E2EXF_AR_RELEASE_MAJOR_VERSION != E2EXF_VERSION_AR_RELEASE_MAJOR_VERSION) || \
		(E2EXF_AR_RELEASE_MINOR_VERSION != E2EXF_VERSION_AR_RELEASE_MINOR_VERSION) || \
		(E2EXF_AR_RELEASE_REVISION_VERSION != E2EXF_VERSION_AR_RELEASE_REVISION_VERSION))
#error "E2EXf : Mismatch AUTOSAR Version in E2EXf_Version.c "
#endif
/* E2EXF Software Version check */
#if ((E2EXF_SW_MAJOR_VERSION != E2EXF_VERSION_SW_MAJOR_VERSION) || \
		(E2EXF_SW_MINOR_VERSION != E2EXF_VERSION_SW_MINOR_VERSION) || \
		(E2EXF_SW_PATCH_VERSION != E2EXF_VERSION_SW_PATCH_VERSION))
#error "E2EXf : Mismatch Software Version in E2EXf_Version.c "
#endif

/* E2E Library Version check */
#if defined(E2E_AR_RELEASE_MAJOR_VERSION) \
		&& defined(E2E_AR_RELEASE_MINOR_VERSION)
#if ((E2E_AR_RELEASE_MAJOR_VERSION != E2EXF_E2E_AR_RELEASE_MAJOR_VERSION) || \
		(E2E_AR_RELEASE_MINOR_VERSION != E2EXF_E2E_AR_RELEASE_MINOR_VERSION))
#error "E2EXf : Mismatch AUTOSAR Version with E2E.h"
#endif
#endif

/* DEM Version check */
#if defined(DEM_AR_RELEASE_MAJOR_VERSION) \
		&& defined(DEM_AR_RELEASE_MINOR_VERSION)
#if ((DEM_AR_RELEASE_MAJOR_VERSION != E2EXF_DEM_AR_RELEASE_MAJOR_VERSION) || \
		(DEM_AR_RELEASE_MINOR_VERSION < E2EXF_DEM_AR_RELEASE_MINOR_VERSION_L) || \
		(DEM_AR_RELEASE_MINOR_VERSION > E2EXF_DEM_AR_RELEASE_MINOR_VERSION_U))
#error "E2EXf : Mismatch AUTOSAR Version with Dem.h"
#endif
#endif

#if(E2EXF_DEV_ERROR_DETECT == STD_ON)
/* DET Version check */
#if defined(DET_AR_RELEASE_MAJOR_VERSION) \
		&& defined(DET_AR_RELEASE_MINOR_VERSION)
#if ((DET_AR_RELEASE_MAJOR_VERSION != E2EXF_DET_AR_RELEASE_MAJOR_VERSION) || \
		(DET_AR_RELEASE_MINOR_VERSION < E2EXF_DET_AR_RELEASE_MINOR_VERSION_L) || \
		(DET_AR_RELEASE_MINOR_VERSION > E2EXF_DET_AR_RELEASE_MINOR_VERSION_U))
#error "E2EXf : Mismatch AUTOSAR Version with Det.h"
#endif
#endif
#endif /* End of (E2EXF_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
 **                      End of File                                           **
 *******************************************************************************/

