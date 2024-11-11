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
**  SRC-MODULE: E2EXf.c                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Transformer Module                                **
**                                                                            **
**  PURPOSE   : Implementation of de-initialization and                       **
**              get version information function                              **
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
** 1.1.1    30-Jun-2022    Seungjin Noh        #CP44-2597                     ** 
** 1.0.2.1  30-Jun-2022    Gongbin Lim         #CP44-321                      **
** 1.0.0    04-Dec-2020    Gongbin Lim         Initial Version                **
** 1.0.1    26-Feb-2021    GOngbin Lim         baseline release               **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SafeE2EXf_SUD_FILE_001 */

#include "E2EXf.h"                       /* E2E Transformer Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define E2EXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"

/*******************************************************************************
** Function Name        : E2EXf_DeInit                                        **
**                                                                            **
** Service ID           : E2EXF_DEINIT_SID: 0x02                              **
**                                                                            **
** Description          : Deinitialize the E2E transformer                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : E2EXf_InitState               **
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* @Trace: SRS_E2E_08528 */
/* @Trace: SafeE2EXf_SUD_API_002 */
FUNC(void, E2EXF_CODE) E2EXf_DeInit(void)
{
  /* @Trace: SafeE2EXf_SUD_API_019 */
  #if (E2EXF_DEV_ERROR_DETECT == STD_ON)
  /* Check if the E2E transformer is initialized */
  if (FALSE == E2EXf_InitState)
  {
    (void)Det_ReportError(E2EXF_MODULE_ID, E2EXF_INSTANCE_ID, 
                          E2EXF_DEINIT_SID, E2EXF_E_UNINIT);
  }
  else
  #endif /* End of (E2EXF_DEV_ERROR_DETECT == STD_ON) */
  /* @Trace: SafeE2EXf_SUD_API_020 */
  {
  	/* Set the module initialization state to FALSE */
    E2EXf_InitState = FALSE;
  }
}

#if (E2EXF_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Function Name        : E2EXf_GetVersionInfo                                **
**                                                                            **
** Service ID           : E2EXF_GETVERSIONINFO_SID: 0x00                      **
**                                                                            **
** Description          : Returns the version information of this module      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Input Parameters     : versionInfo : Pointer to where to store the         **
**                                      version information of this module    **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* @Trace: SafeE2EXf_SUD_API_003 */
/* polyspace +2 MISRA-C3:D4.5 [Justified:Low] "Parameter name is following specification document" */
FUNC(void, E2EXF_CODE) E2EXf_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, E2EXF_APPL_DATA) versionInfo)
{
  /* @Trace: SafeE2EXf_SUD_API_021 */
  /* Check if a NULL pointer is passed for the versionInfo parameter */
  if (NULL_PTR == versionInfo)
  {
  #if (E2EXF_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(E2EXF_MODULE_ID, E2EXF_INSTANCE_ID, 
                          E2EXF_GETVERSIONINFO_SID, E2EXF_E_PARAM_POINTER);
  #endif /* End of (E2EXF_DEV_ERROR_DETECT == STD_ON) */
  }
  else
  /* @Trace: SafeE2EXf_SUD_API_022 */
  {
    /* polyspace +4 MISRA-C3:D4.14 MISRA-C3:D4.1 MISRA-C3:18.1 [Justified:Low] "versionInfo is checked before using" */
    /* Get version information */
    versionInfo->vendorID = E2EXF_VENDOR_ID;
    versionInfo->moduleID = E2EXF_MODULE_ID;
    versionInfo->sw_major_version = E2EXF_SW_MAJOR_VERSION;
    versionInfo->sw_minor_version = E2EXF_SW_MINOR_VERSION;
    versionInfo->sw_patch_version = E2EXF_SW_PATCH_VERSION;
  }
}
#endif /* End of (E2EXF_VERSION_INFO_API == STD_ON) */

#define E2EXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
