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
**  SRC-MODULE: Dem_Version.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Dem Module                                            **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"
#include "Dem_Version.h"        /* Dem Version Header File */

#include "NvM.h"              /* NVRAM Header File */
#include "Rte.h"
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"              /* DET header file */
#endif
#if (DEM_TRIGGER_DCM_REPORTS == STD_ON)
#include "Dcm.h"
#endif
#if (DEM_FIM_INTEGRATED == STD_ON)
#include "FiM.h"
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define DEM_VERSION_C_MAJOR_VERSION     4
#define DEM_VERSION_C_MINOR_VERSION     4
#define DEM_VERSION_C_REVISION_VERSION  0

/* Software Version Information */
#define DEM_VERSION_C_SW_MAJOR_VERSION     1
#define DEM_VERSION_C_SW_MINOR_VERSION     0
#define DEM_VERSION_C_SW_PATH_VERSION      0
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (DEM_VERSION_AR_MAJOR_VERSION != \
  DEM_VERSION_C_MAJOR_VERSION)
  #error "Dem_Version.c : Mismatch in Specification Major Version"
#endif

#if (DEM_VERSION_AR_MINOR_VERSION != \
  DEM_VERSION_C_MINOR_VERSION)
  #error "Dem_Version.c : Mismatch in Specification Minor Version"
#endif

#if (DEM_VERSION_AR_REVISION_VERSION != \
  DEM_VERSION_C_REVISION_VERSION)
  #error "Dem_Version.c : Mismatch in Specification Revision Version"
#endif

#if (DEM_VERSION_SW_MAJOR_VERSION != DEM_VERSION_C_SW_MAJOR_VERSION)
  #error "Dem_Version.c : Mismatch in Major Version"
#endif

#if (DEM_VERSION_SW_MINOR_VERSION != DEM_VERSION_C_SW_MINOR_VERSION)
  #error "Dem_Version.c : Mismatch in Minor Version"
#endif

#if (DEM_DEV_ERROR_DETECT == STD_ON)
#if (DET_AR_RELEASE_MAJOR_VERSION != DEM_DET_AR_RELEASE_MAJOR_VERSION)
  #error "Det.h : Mismatch in Specification Major Version"
#endif

#if (DET_AR_RELEASE_MINOR_VERSION != DEM_DET_AR_RELEASE_MINOR_VERSION)
  #error "Det.h : Mismatch in Specification Minor Version"
#endif
#endif


#if (RTE_AR_RELEASE_MAJOR_VERSION != DEM_RTE_AR_RELEASE_MAJOR_VERSION)
  #error "Rte.h : Mismatch in Specification Major Version"
#endif

#if (RTE_AR_RELEASE_MINOR_VERSION != DEM_RTE_AR_RELEASE_MINOR_VERSION)
  #error "Rte.h : Mismatch in Specification Minor Version"
#endif
/* @Trace: Dem_SUD_MACRO_014 */
#if (DEM_TRIGGER_DCM_REPORTS == STD_ON)
#if (DCM_AR_RELEASE_MAJOR_VERSION != DEM_DCM_AR_RELEASE_MAJOR_VERSION)
  #error "Dcm.h : Mismatch in Specification Major Version"
#endif

#if (DCM_AR_RELEASE_MINOR_VERSION != DEM_DCM_AR_RELEASE_MINOR_VERSION)
  #error "Dcm.h : Mismatch in Specification Minor Version"
#endif
#endif

#if (DEM_FIM_INTEGRATED == STD_ON)
#if (FIM_AR_RELEASE_MAJOR_VERSION != DEM_FIM_AR_RELEASE_MAJOR_VERSION)
  #error "FiM.h : Mismatch in Specification Major Version"
#endif

#if (FIM_AR_RELEASE_MINOR_VERSION != DEM_FIM_AR_RELEASE_MINOR_VERSION)
  #error "FiM.h : Mismatch in Specification Minor Version"
#endif
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
