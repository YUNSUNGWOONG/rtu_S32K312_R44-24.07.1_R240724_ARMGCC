/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : General function of CSM                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0.0   15-Jan-2021   JH Lim       Initial version                       **
** 1.0.1.0   10-Mar-2021   TamTV6       Fix #17725, Add trace SUD             **
** 1.0.3.0   12-Aug-2022   DienTC1      #594                                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_IntFunc.h"

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
VAR(boolean, CSM_VAR_INIT) Csm_Initialisation = FALSE;
#define CSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Csm_Init                                            **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Initializes the CSM module                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : configPtr : Pointer to a selected configuration     **
**                                    structure                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Csm module shouldn't be initialized                 **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Csm_Initialisation                                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00101 SRS_BSW_00358 SRS_BSW_00414 */
FUNC(void, CSM_CODE) Csm_Init
(
  P2CONST(Csm_ConfigType, AUTOMATIC, CSM_APPL_CONST) configPtr
)
{
  /* @Trace: SRS_CSM_00050 */
  CSM_UNUSED(configPtr);
  if (TRUE == Csm_Initialisation)
  {
    /* @Trace: Csm_SUD_FUNC_002 */
    /* Csm has already been initialised */
    #if CSM_DEV_ERROR_DETECT == STD_ON
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
    CSM_INIT_SID, CSM_E_INIT_FAILED);
    #endif
  }
  else
  {
    /* @Trace: Csm_SUD_FUNC_001 */
    /* Do something here to initialise Csm Module.
    E.g: initialise Job state to IDLE */
    /* if everything is ok then set intialisation state of Csm to TRUE */
    Csm_Initialisation = TRUE;
  }
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Csm_GetVersionInfo                                  **
**                                                                            **
** Service ID           : 0x3B                                                **
**                                                                            **
** Description          : Returns the version information of this module      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : versioninfo : Pointer to where to store the version **
**                                      information of this module            **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (CSM_VERSION_INFO_API == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00407 SRS_CryptoStack_00087 */
FUNC(void, CSM_CODE) Csm_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CSM_APPL_DATA) versioninfo
)
{
    /* check NULL pointer */
  if (NULL_PTR == versioninfo)
  {
    /* @Trace: Csm_SUD_FUNC_004 */
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_GET_VERSION_INFO_SID, CSM_E_PARAM_POINTER);
    #endif
  }
  else
  {
    /* @Trace: Csm_SUD_FUNC_003 */
    /* Load the vendor Id */
    versioninfo->vendorID = CSM_VENDOR_ID;
    /* Load the module Id */
    versioninfo->moduleID = CSM_MODULE_ID;
    /* Load Software Major Version */
    versioninfo->sw_major_version = CSM_SW_MAJOR_VERSION;
    /* Load Software Minor Version */
    versioninfo->sw_minor_version = CSM_SW_MINOR_VERSION;
    /* Load Software Patch Version */
    versioninfo->sw_patch_version = CSM_SW_PATCH_VERSION;
  }
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
