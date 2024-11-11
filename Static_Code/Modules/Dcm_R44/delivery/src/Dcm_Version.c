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
**  SRC-MODULE: Dcm_Version.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Define the Dcm and dependence module version                  **
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
** 1.0.1     23-May-2023   Suyon Kim      Refer #CP44-2221                    **
** 1.0.12    30-Jun-2023   Suyon Kim      Refer #CP44-2255                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_Version.h"
#include "Dcm.h"

#include "Rte.h"
#include "Rte_Dcm.h"

#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dem.h"
#endif
#include "ComM.h"
#include "PduR.h"
#include "BswM.h"
#if (DCM_NVM_CONFIGURED == STD_ON)
#include "NvM.h"
#endif
#if(DCM_USE_ECU_SIGNAL_ENABLED == STD_ON)
#include "IoHwAb.h"
#endif

#if (DCM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
#include "Csm.h"
#include "KeyM.h"
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR SPECIFICATION VERSION INFORMATION */
#define DCM_VERSION_C_AR_RELEASE_MAJOR_VERSION      4
#define DCM_VERSION_C_AR_RELEASE_MINOR_VERSION      4
#define DCM_VERSION_C_AR_RELEASE_REVISION_VERSION   0

/* FILE VERSION INFORMATION */
#define DCM_VERSION_C_SW_MAJOR_VERSION  1
#define DCM_VERSION_C_SW_MINOR_VERSION  0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (DCM_VERSION_AR_RELEASE_MAJOR_VERSION != \
                                         DCM_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "Dcm_Version : Mismatch in Specification Major Version"
#endif

#if (DCM_VERSION_AR_RELEASE_MINOR_VERSION != \
                                         DCM_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "Dcm_Version : Mismatch in Specification Minor Version"
#endif

#if (DCM_VERSION_AR_RELEASE_REVISION_VERSION != \
                                      DCM_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "Dcm_Version : Mismatch in Specification Patch Version"
#endif

#if (DCM_VERSION_SW_MAJOR_VERSION != DCM_VERSION_C_SW_MAJOR_VERSION)
  #error "Dcm_Version : Mismatch in Major Version"
#endif

#if (DCM_VERSION_SW_MINOR_VERSION != DCM_VERSION_C_SW_MINOR_VERSION)
  #error "Dcm_Version : Mismatch in Minor Version"
#endif

#if (DCM_DEV_ERROR_DETECT == STD_ON)
#if (DET_AR_RELEASE_MAJOR_VERSION != DCM_DET_AR_RELEASE_MAJOR_VERSION)
  #error "Det.h : Mismatch in Specification Major Version"
#endif

#if (DET_AR_RELEASE_MINOR_VERSION != DCM_DET_AR_RELEASE_MINOR_VERSION)
  #error "Det.h : Mismatch in Specification Minor Version"
#endif
#endif

#if (RTE_AR_RELEASE_MAJOR_VERSION != DCM_RTE_AR_RELEASE_MAJOR_VERSION)
  #error "Rte.h : Mismatch in Specification Major Version"
#endif

#if (RTE_AR_RELEASE_MINOR_VERSION != DCM_RTE_AR_RELEASE_MINOR_VERSION)
  #error "Rte.h : Mismatch in Specification Minor Version"
#endif

#if (DCM_DEM_CONFIGURED == STD_ON)
#if (DEM_AR_RELEASE_MAJOR_VERSION != DCM_DEM_AR_RELEASE_MAJOR_VERSION)
  #error "Dem.h : Mismatch in Specification Major Version"
#endif

#if (DEM_AR_RELEASE_MINOR_VERSION != DCM_DEM_AR_RELEASE_MINOR_VERSION)
  #error "Dem.h : Mismatch in Specification Minor Version"
#endif
#endif

#if (COMM_AR_RELEASE_MAJOR_VERSION != DCM_COMM_AR_RELEASE_MAJOR_VERSION)
  #error "ComM.h : Mismatch in Specification Major Version"
#endif

#if (COMM_AR_RELEASE_MINOR_VERSION != DCM_COMM_AR_RELEASE_MINOR_VERSION)
  #error "ComM.h : Mismatch in Specification Minor Version"
#endif

#if (PDUR_AR_RELEASE_MAJOR_VERSION != DCM_PDUR_AR_RELEASE_MAJOR_VERSION)
  #error "PduR.h : Mismatch in Specification Major Version"
#endif

#if (PDUR_AR_RELEASE_MINOR_VERSION != DCM_PDUR_AR_RELEASE_MINOR_VERSION)
  #error "PduR.h : Mismatch in Specification Minor Version"
#endif

#if (BSWM_AR_RELEASE_MAJOR_VERSION != DCM_BSWM_AR_RELEASE_MAJOR_VERSION)
  #error "BswM.h : Mismatch in Specification Major Version"
#endif

#if (BSWM_AR_RELEASE_MINOR_VERSION != DCM_BSWM_AR_RELEASE_MINOR_VERSION)
  #error "BswM.h : Mismatch in Specification Minor Version"
#endif

#if (DCM_NVM_CONFIGURED == STD_ON)
#if (NVM_AR_RELEASE_MAJOR_VERSION != DCM_NVM_AR_RELEASE_MAJOR_VERSION)
  #error "NvM.h : Mismatch in Specification Major Version"
#endif

#if (NVM_AR_RELEASE_MINOR_VERSION != DCM_NVM_AR_RELEASE_MINOR_VERSION)
  #error "NvM.h : Mismatch in Specification Minor Version"
#endif
#endif

#if(DCM_USE_ECU_SIGNAL_ENABLED == STD_ON)
#if (IOHWAB_AR_RELEASE_MAJOR_VERSION != DCM_IOHWAB_AR_RELEASE_MAJOR_VERSION)
  #error "IoHwAb.h : Mismatch in Specification Major Version"
#endif

#if (IOHWAB_AR_RELEASE_MINOR_VERSION != DCM_IOHWAB_AR_RELEASE_MINOR_VERSION)
  #error "IoHwAb.h : Mismatch in Specification Minor Version"
#endif
#endif

#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
#if (CSM_AR_RELEASE_MAJOR_VERSION != DCM_CSM_AR_RELEASE_MAJOR_VERSION)
  #error "Csm.h : Mismatch in Specification Major Version"
#endif

#if (CSM_AR_RELEASE_MINOR_VERSION != DCM_CSM_AR_RELEASE_MINOR_VERSION)
  #error "Csm.h : Mismatch in Specification Minor Version"
#endif

#if (KEYM_AR_RELEASE_MAJOR_VERSION != DCM_KEYM_AR_RELEASE_MAJOR_VERSION)
  #error "KeyM.h : Mismatch in Specification Major Version"
#endif

#if (KEYM_AR_RELEASE_MINOR_VERSION != DCM_KEYM_AR_RELEASE_MINOR_VERSION)
  #error "Key.h : Mismatch in Specification Minor Version"
#endif
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
