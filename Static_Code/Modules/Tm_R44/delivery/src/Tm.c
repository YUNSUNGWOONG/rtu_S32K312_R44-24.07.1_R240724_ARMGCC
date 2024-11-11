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
**  SRC-MODULE: Tm.c                                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Time Service Module                                   **
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
** 1.0.1     24-Jun-2022   PhatCT         R44-Redmine #25858, #28232          **
** 1.0.0     19-Jun-2020   DanhLT2        Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Tm.h"                    /* Header file of Tm */
#if(TM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                   /* Det module Header file */
#endif
#include "Gpt.h"


/*******************************************************************************
**                      Global Types                                          **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name       : TM_GetVersionInfo                                    **
**                                                                            **
** Service ID          : 0x01                                                 **
**                                                                            **
** Description         : This service gives version information of the Tm     **
**                       module. The version information includes module Id,  **
**                       vendor Id, InstanceId & vendor specific version no's **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy         : Reentrant                                            **
**                                                                            **
** Input Parameters    : None                                                 **
**                                                                            **
** InOut Parameters    : versioninfo                                          **
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** Return parameter    : None                                                 **
**                                                                            **
** Preconditions       : TM_VERSION_INFO_API = STD_ON                         **
**                                                                            **
** Remarks             : Global Variable(s)  : None                           **
**                       Function(s) invoked : Det_ReportError                **
*******************************************************************************/

/* @Trace: SRS_BSW_00407 Tm_SUD_FILE_001 */
#if (TM_VERSION_INFO_API == STD_ON)
#define TM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, TM_CODE) Tm_GetVersionInfo(P2VAR(Std_VersionInfoType,
  AUTOMATIC, TM_APPL_DATA) versioninfo)
{
  /* Check whether the pointer passed to API is Null Pointer */
  if (NULL_PTR == versioninfo)
  {
    /* @Trace: Tm_SUD_API_120 */
    /* Report to Det when pointer is Null */
    #if (TM_DEV_ERROR_DETECT  == STD_ON)
    (void)Det_ReportError(TM_MODULE_ID, TM_INSTANCE_ID,
      TM_GETVERSIONINFO_SID, TM_E_PARAM_POINTER);
    #endif /* TM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    /* @Trace: Tm_SUD_API_121 */
    /* Copy the vendor Id */
	/* @Trace: Tm_SUD_DATATYPE_002 */
    versioninfo->vendorID = TM_VENDOR_ID; /* polyspace MISRA2012:D4.14 [Not a defect:Unset] "Pointer versioninfo have data type is structure and it is checked not NULL so it is not having any impact" */

    /* Copy the module Id */
    versioninfo->moduleID = TM_MODULE_ID;

    /* Copy Software Major Version */
    versioninfo->sw_major_version = TM_SW_MAJOR_VERSION;

    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = TM_SW_MINOR_VERSION;

    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = TM_SW_PATCH_VERSION;
  } /* End of else */
}

#define TM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* TM_VERSION_INFO_API == STD_ON */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
