/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  INC-MODULE:           ComXf.c                                             **
**                                                                            **
**  PRODUCT   :           AUTOSAR COM Based Transformer Module                **
**                                                                            **
**  PURPOSE   :           This file provides definitions of packing functions **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
*******************************************************************************/

/*******************************************************************************
**                         Revision History                                   **
********************************************************************************
** Revision  Date             By          Description                         **
********************************************************************************
** 1.0.7     31-Aug-2022      KhaLN1      #CP44-614                           **
** 1.0.0     22-Feb-2020      HIEPVT1     Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA2012:D4.14 [Justified:Low] "The validity of all external parameters has checked by ComXf_APIs.c" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SafeComXf_SUD_FILE_001 */
/*include for ComXf.h*/
#include "ComXf.h"
/*include for ComXf_Cfg.h*/
#include "ComXf_Cfg.h"
/*include for ComXf_Version.h*/
#include "ComXf_Version.h"

/*******************************************************************************
**                            Type Definition                                 **
*******************************************************************************/

/*******************************************************************************
**                        Global Variable Declaration                         **
*******************************************************************************/
#define COMXF_START_SEC_VAR_INIT_ASIL_D_BOOLEAN
#include "MemMap.h"
/* @Trace: SafeComXf_SUD_GLOBALVAR_001 */
/* Definition of the global Initialization status variable */
VAR(boolean, AUTOMATIC) ComXf_InitStatus = COMXF_CS_DEINIT;
#define COMXF_STOP_SEC_VAR_INIT_ASIL_D_BOOLEAN
#include "MemMap.h"

/*******************************************************************************
**                            Function Declaration                            **
*******************************************************************************/

/*******************************************************************************
**                           Function Definitions                             **
*******************************************************************************/
/*=============================================================================*
** Function Name        : ComXf_GetVersionInfo                                **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This service returns the version information of the **
**                        called transformer module                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : VersionInfo                                         **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : No Preconditions                                    **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Det_ReportError               **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_BSW_00337 SRS_BSW_00407 SRS_BSW_00411 */

#if(STD_ON == COMXF_VERSION_INFORMATION)
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"

/* @Trace: SafeComXf_SUD_DATATYPE_007 */

FUNC(void, COMXF_CODE) ComXf_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, COMXF_APPL_DATA) versionInfo)
{
  /* Check whether pointer is null */
  if (NULL_PTR == versionInfo)
  {
    /* @Trace: SafeComXf_SUD_API_004 */
#if (STD_ON == COMXF_DEV_ERROR_DETECT)
    (void)Det_ReportError(COMXF_MODULE_ID, COMXF_INSTANCE_ID,
       COMXF_GETVERSIONINFO_SERVICE_ID, COMXF_E_PARAM_POINTER);
#endif /*End of #if (STD_ON == COMXF_DEV_ERROR_DETECT)*/
  }
  /* Pointer is valid*/
  else
  {
    /* @Trace: SafeComXf_SUD_API_016 */
    /* Assigning vendor Id to the VersionInfo parameter */
    versionInfo->vendorID = COMXF_VENDOR_ID;

    /* Assigning module Id to the VersionInfo parameter */
    versionInfo->moduleID = COMXF_MODULE_ID;

    /* Assigning software major version to the VersionInfo parameter */
    versionInfo->sw_major_version = COMXF_SW_MAJOR_VERSION;

    /* Assigning software minor version to the VersionInfo parameter */
    versionInfo->sw_minor_version = COMXF_SW_MINOR_VERSION;

    /* Assigning software patch version to the VersionInfo parameter */
    versionInfo->sw_patch_version = COMXF_SW_PATCH_VERSION;
  }
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"
#endif /* End of #if(STD_ON == COMXF_VERSION_INFORMATION)*/

/*=============================================================================*
** Function Name        : ComXf_DeInit                                        **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service de-initializes the transformer         **
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
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
** Remarks              : Global Variable(s)  : ComXf_InitStatus              **
**                        Function(s) invoked : Det_ReportError               **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_BSW_00337 SRS_BSW_00407 SRS_BSW_00411 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_DeInit(void)
{
  if ((boolean) COMXF_CS_DEINIT == ComXf_InitStatus)
  {
    /* @Trace: SafeComXf_SUD_API_002 */
#if (STD_ON == COMXF_DEV_ERROR_DETECT)
    (void)Det_ReportError(COMXF_MODULE_ID, COMXF_INSTANCE_ID,
      COMXF_DEINIT_SERVICE_ID, COMXF_E_UNINIT);
#endif /*End of #if (STD_ON == COMXF_DEV_ERROR_DETECT)*/
  }
  else
  {
    /* @Trace: SafeComXf_SUD_API_003 */
    /* Store module de-initialization value into global */
    ComXf_InitStatus = (boolean)COMXF_CS_DEINIT;
  }
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"


/*=============================================================================*
** Function Name        : ComXf_FillUnusedBufferArea                          **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : initializes the transformer buffer                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ComXfBufferLength,                                  **
**                        ComXfUnusedAreaValue                                **
**                                                                            **
** InOut parameter      : buffer                                              **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_APPL_CODE) ComXf_FillUnusedBufferArea(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  VAR(uint32, AUTOMATIC) ComXfBufferLength,
  VAR(uint8, AUTOMATIC) ComXfUnusedAreaValue)
{
  /* @Trace: SafeComXf_SUD_API_019 */
  /*Local variable to store buffer index */
  VAR(uint32, AUTOMATIC) bufferIndex;

  /*Start with buffer index equal zero value*/
  bufferIndex = COMXF_ZEROTH_BYTE;

  /* Loop for buffer set unused */
  do{
    /*Copy the unused value to application buffer*/
    buffer[bufferIndex] = ComXfUnusedAreaValue;

    /*Increment buffer index*/
    bufferIndex++;

  }while(bufferIndex < ComXfBufferLength);
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA RULE CHECKER)                   **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 */
/* polyspace-end MISRA2012:D4.14*/

/*******************************************************************************
*                       End of File                                            *
*******************************************************************************/