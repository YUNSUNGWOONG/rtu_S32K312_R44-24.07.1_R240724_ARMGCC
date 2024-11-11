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
**  SRC-MODULE: FiM_Version.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : Provision of FiM Module Version information                   **
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
** 1.0.0    28-July-2020   ThienVT1        Changes made As per Redmine #15392 **
** 1.0.0    28-July-2020   ThienVT1        Changes made As per Redmine #14839 **
** 1.0.0    05-June-2020   ThienVT1        Initial Version                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"                      /* Dem Header File */
#include "FiM.h"              /* FiM Version Definition Header File */
#include "FiM_InternalFunc.h"
#if(FIM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                      /* Det Header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define FIM_VERSION_C_AR_RELEASE_MAJOR_VERSION  4
#define FIM_VERSION_C_AR_RELEASE_MINOR_VERSION  4
#define FIM_VERSION_C_AR_RELEASE_REVISION_VERSION  0

/* FiM Software Version Information */
#define FIM_VERSION_C_SW_MAJOR_VERSION     1
#define FIM_VERSION_C_SW_MINOR_VERSION     0
#define FIM_VERSION_C_SW_PATH_VERSION      0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* FiM Version Check */
#if (FIM_VERSION_AR_RELEASE_MAJOR_VERSION != \
  FIM_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "FiM_Version.c : Mismatch in Specification Major Version"
#endif
#if (FIM_VERSION_AR_RELEASE_MINOR_VERSION != \
  FIM_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "FiM_Version.c : Mismatch in Specification Minor Version"
#endif
#if (FIM_VERSION_AR_RELEASE_REVISION_VERSION != \
  FIM_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "FiM_Version.c : Mismatch in Specification Patch Version"
#endif
#if (FIM_VERSION_SW_MAJOR_VERSION != FIM_VERSION_C_SW_MAJOR_VERSION)
  #error "FiM_Version.c : Mismatch in Major Version"
#endif
#if (FIM_VERSION_SW_MINOR_VERSION != FIM_VERSION_C_SW_MINOR_VERSION)
  #error "FiM_Version.c : Mismatch in Minor Version"
#endif

/* Dem version check */
#if (DEM_AR_RELEASE_MAJOR_VERSION != FIM_DEM_AR_RELEASE_MAJOR_VERSION)
  #error "Dem.h : Mismatch in Specification Major Version"
#endif
#if (DEM_AR_RELEASE_MINOR_VERSION != FIM_DEM_AR_RELEASE_MINOR_VERSION)
  #error "Dem.h : Mismatch in Specification Minor Version"
#endif

#if (RTE_AR_RELEASE_MAJOR_VERSION != FIM_RTE_AR_RELEASE_MAJOR_VERSION)
  #error "Rte.h : Mismatch in Specification Major Version"
#endif

#if (RTE_AR_RELEASE_MINOR_VERSION != FIM_RTE_AR_RELEASE_MINOR_VERSION)
  #error "Rte.h : Mismatch in Specification Minor Version"
#endif

/* Det version check */
#if (FIM_DEV_ERROR_DETECT == STD_ON)
 #if (DET_AR_RELEASE_MAJOR_VERSION != FIM_DET_AR_RELEASE_MAJOR_VERSION)
   #error "Det.h : Mismatch in Specification Major Version"
 #endif
 #if (DET_AR_RELEASE_MINOR_VERSION != FIM_DET_AR_RELEASE_MINOR_VERSION)
   #error "Det.h : Mismatch in Specification Minor Version"
 #endif
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name    : FiM_GetVersionInfo                                      **
**                                                                            **
** Service ID       : 0x04                                                    **
**                                                                            **
** Description      : This Service returns the version information of         **
**                    Function Inhibition Manager Module.                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Input Parameters : None                                                    **
**                                                                            **
** InOut parameter  : None                                                    **
**                                                                            **
** Output Parameters: Std_VersionInfoType *versioninfo                        **
**                                                                            **
** Return parameter : None                                                    **
**                                                                            **
** Preconditions    : None                                                    **
**                                                                            **
** Remarks          :                                                         **
*******************************************************************************/
#if(FIM_VERSION_INFO_API == STD_ON)
#define FIM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00402 */
FUNC(void, FIM_CODE) FiM_GetVersionInfo(P2VAR(Std_VersionInfoType,
  AUTOMATIC, FIM_APPL_DATA)versioninfo)
/* @Trace: SWS_Fim_00078 */
{
  /* This service returns the version information of this module. */
  /* check NULL pointer */
  if(versioninfo == NULL_PTR)
  {
    /* Report to DET */
    /* @Trace: SWS_Fim_00076 */
    /* @Trace: FiM_SUD_API_107 */
    FiM_Report_Error(FIM_GETVERSIONINFO_SID,FIM_E_PARAM_POINTER);
  }
  else
  {
    /* @Trace: FiM_SUD_API_106 */
    /* Load the vendor Id */
    versioninfo->vendorID = FIM_VENDOR_ID;
    /* Load the module Id */
    versioninfo->moduleID = FIM_MODULE_ID;
    /* Load Software Major Version */
    versioninfo->sw_major_version = FIM_SW_MAJOR_VERSION;
    /* Load Software Minor Version */
    versioninfo->sw_minor_version = FIM_SW_MINOR_VERSION;
    /* Load Software Patch Version */
    versioninfo->sw_patch_version = FIM_SW_PATCH_VERSION;
  }
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (FIM_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
