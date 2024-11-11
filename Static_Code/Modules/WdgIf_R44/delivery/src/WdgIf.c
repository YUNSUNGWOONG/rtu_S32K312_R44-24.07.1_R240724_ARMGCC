/* polyspace +1 MISRA2012:1.1 [Justified: Low] "Macro definitions are needed for performance and file size" */
/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted with **
**  Hyundai Autoever, and any other use is prohibited.                        **
**  If you use it for other  purposes or change the source code, you may take **
**  legal responsibility.                                                     **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: WdgIf.c                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTOEVER CUSTOM WDGIF                                 **
**                                                                            **
**  PURPOSE   : AutoEver Custom Watchdog Interface API Functionality          **
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
** 0.0.1     23-Sep-2019 Tungdt39           R44-Redmine <#1440>               **
** 0.0.2     11-Mar-2020 Tungdt39           R44-Redmine <#11479>              **
** 0.0.3     13-Oct-2020 MinhNQ26           Fix warnings <#16420>             **
** 1.3.1     04-Aug-2022 TriBD              CP44-386, CP44-323                **
** 1.4.0     20-Sep-2022 NhanNV8            Traceability <#27616>             **

*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgIf.h"
#include "WdgIf_Cfg.h"
#if (WDGIF_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* end of #if (WDGIF_DEV_ERROR_DETECT == STD_ON) */
/* @Trace: SRS_BSW_00304 SRS_MemHwAb_14024*/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/* polyspace-begin MISRA2012:20.1 [Not a Defect:Low] "This macro is necessary for Memory mapping" */

#define WDGIF_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : WdgIf_SetMode                                       **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service changes the mode of the Watchdog timer **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : DeviceIndex, WdgIf_ModeType WdgMode                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK, E_NOT_OK)                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Wdg_SetModePtr[](WdgMode),    **
**                                              Wdg_SetMode(WdgMode)          **
**                                              Det_ReportError               **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00369 SRS_MemHwAb_14020 SRS_MemHwAb_14023
           SRS_SPAL_12448 SRS_Wdg_12018 SRS_BSW_00337 SRS_BSW_00384
           SRS_BSW_00385 SRS_BSW_00386 SRS_MemHwAb_14019 SRS_MemHwAb_14021
           SRS_MemHwAb_14022 SRS_BSW_00357 SRS_Wdg_12165 SRS_Wdg_12167 */
FUNC(Std_ReturnType, WDGIF_CODE) WdgIf_SetMode \
    (VAR(uint8, WDGIF_VAR) DeviceIndex, VAR(WdgIf_ModeType, WDGIF_VAR) WdgMode)
{
  /* @Trace: WdgIf_SUD_API_001 */
  /* local var ReturnStatus used to update and Return 'Status of WdgIf' */
  VAR(Std_ReturnType, WDGIF_VAR) ReturnStatus;
 
  #if (WDGIF_SINGLE_DEVICE < WDGIF_NUMBER_OF_DEVICES)
  /* Module operation in multiple mode */
  if (WDGIF_NUMBER_OF_DEVICES > DeviceIndex)
  {
    /* @Trace: WdgIf_SUD_API_003 */
    /* Invoke the corresponding Watchdog driver SetMode API
      through the pra "DeviceIndex" */
    /* polyspace +2 RTE:OBAI MISRA2012:D4.1 MISRA2012:18.1 [Justified:Low] "array index was check limited before used" */
    /* polyspace +1 RTE:COR MISRA2012:D4.1 [Justified:Low] "Size of array was declare in generate code" */
    ReturnStatus = Wdg_SetModePtr[DeviceIndex](WdgMode);
  }
  else
  {
    #if (STD_ON == WDGIF_DEV_ERROR_DETECT)
    /* @Trace: WdgIf_SUD_API_002 */
    /* report error to DET if pra "DeviceIndex"
       more than number of device configured */
    (void)Det_ReportError(WDGIF_MODULE_ID,\
                          WDGIF_INSTANCE_ID,\
                          WDGIF_SETMODE_SID,\
                          WDGIF_E_PARAM_DEVICE);
    #endif /* end of #if (STD_ON == WDGIF_DEV_ERROR_DETECT) */
    /* @Trace: WdgIf_SUD_API_005 */
    ReturnStatus = E_NOT_OK;
  } /* end of if (WDGIF_NUMBER_OF_DEVICES <= DeviceIndex) */
  #else /* else of #if (WDGIF_SINGLE_DEVICE < WDGIF_NUMBER_OF_DEVICES ) */
  /* @Trace: WdgIf_SUD_API_004 */
  /* operating mode single device with internal wdg */
  WDGIF_UNUSED(DeviceIndex);
  /* polyspace +1 RTE:OBAI RTE:COR MISRA2012:18.1 MISRA2012:D4.1 [Justified:Low] "Size of array was declare in generate code" */
  ReturnStatus = Wdg_SetModePtr[0](WdgMode);
  #endif /* end of #if (WDGIF_SINGLE_DEVICE < WDGIF_NUMBER_OF_DEVICES ) */
  /* @Trace: WdgIf_SUD_API_006 */
  return ReturnStatus;
}
#define WDGIF_STOP_SEC_CODE
#include "MemMap.h"

#define WDGIF_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : WdgIf_SetTriggerCondition                           **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service is used to trigger the Watchdog timer  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : DeviceIndex, Timeout                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked :                               **
**                                        Det_ReportError                     **
**                                        Wdg_SetTriggerCondition(Timeout)    **
**                                        Wdg_SetTriggerConditionPtr(Timeout) **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00369 SRS_MemHwAb_14020 SRS_BSW_00337
           SRS_SPAL_12448 SRS_Wdg_13500 SRS_BSW_00384 SRS_BSW_00385
           SRS_BSW_00386 SRS_MemHwAb_14019 SRS_MemHwAb_14021 SRS_MemHwAb_14022
           SRS_MemHwAb_14023 SRS_Wdg_12165 SRS_Wdg_12167 */

FUNC(void, WDGIF_CODE) WdgIf_SetTriggerCondition \
    (VAR(uint8, WDGIF_VAR) DeviceIndex, VAR(uint16, WDGIF_VAR) Pra_Timeout)
{
  #if (WDGIF_SINGLE_DEVICE < WDGIF_NUMBER_OF_DEVICES)
  /* Module operation in multiple mode */
  if (WDGIF_NUMBER_OF_DEVICES > DeviceIndex)
  {
      /* @Trace: WdgIf_SUD_API_008 */
    /* Invoke the corresponding Watchdog driver Trigger
       API through the pra "DeviceIndex" */
     /* polyspace +2 RTE:OBAI MISRA2012:D4.1 MISRA2012:18.1 [Justified:Low] "array index was check limited before used" */
    /* polyspace +1 RTE:COR MISRA2012:D4.1 [Justified:Low] "Size of array was declare in generate code" */
    Wdg_SetTriggerConditionPtr[DeviceIndex](Pra_Timeout);
  }
  else
  {
      /* @Trace: WdgIf_SUD_API_007 */
    /* report error to DET if pra "DeviceIndex"
      more than number of device configured */
    #if (STD_ON == WDGIF_DEV_ERROR_DETECT)
        (void)Det_ReportError(WDGIF_MODULE_ID,\
                            WDGIF_INSTANCE_ID,\
                            WDGIF_SETTRIGGERCONDITION_SID,\
                            WDGIF_E_PARAM_DEVICE);
    #endif /* end of #if (STD_ON == WDGIF_DEV_ERROR_DETECT) */
  }
  #else /* else of #if (WDGIF_SINGLE_DEVICE < WDGIF_NUMBER_OF_DEVICES) */
  /* @Trace: WdgIf_SUD_API_009 */
  /* operating mode single device with internal wdg  */
  WDGIF_UNUSED(DeviceIndex);
  /* polyspace +1 RTE:OBAI RTE:COR MISRA2012:18.1 MISRA2012:D4.1 [Justified:Low] "Size of array was declare in generate code" */
  Wdg_SetTriggerConditionPtr[0](Pra_Timeout);
  #endif /* end of #if (WDGIF_SINGLE_DEVICE < WDGIF_NUMBER_OF_DEVICES) */
}
#define WDGIF_STOP_SEC_CODE
#include "MemMap.h"

#define WDGIF_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : WdgIf_GetVersionInfo                                **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service returns the version information of     **
**                        this component.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : VersionInfoPtr                                      **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
/* @Trace: SRS_BSW_00369 SRS_SPAL_12448 SWS_BSW_00212 SRS_BSW_00337
           SRS_BSW_00385 SRS_BSW_00386 */
/* Version information service enabled */
#if (STD_ON == WDGIF_VERSION_INFO_API)
FUNC(void, WDGIF_CODE) WdgIf_GetVersionInfo \
    (P2VAR(Std_VersionInfoType, AUTOMATIC, WDGIF_APPL_DATA)VersionInfoPtr)
{
  /* get infomation version of this component. */
  if (NULL_PTR != VersionInfoPtr)
  {
    /* @Trace: WdgIf_SUD_API_010 */
    /* Copy the vendor Id */
    /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "The pointer has checked for not NULL" */
    VersionInfoPtr->vendorID = WDGIF_VENDOR_ID;
    /* Copy the module Id */
    VersionInfoPtr->moduleID = WDGIF_MODULE_ID;
    /* Copy Software Major Version */
    VersionInfoPtr->sw_major_version = WDGIF_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    VersionInfoPtr->sw_minor_version = WDGIF_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    VersionInfoPtr->sw_patch_version = WDGIF_SW_PATCH_VERSION;
    /* polyspace-end MISRA2012:D4.14 */
  }
  else
  {
  #if (STD_ON == WDGIF_DEV_ERROR_DETECT)
    /* @Trace: WdgIf_SUD_API_011 */
    /* report error to DET if pra "VersionInfoPtr" equal to NULL */
    (void)Det_ReportError(WDGIF_MODULE_ID,\
                          WDGIF_INSTANCE_ID,\
                          WDGIF_GETVERSIONINFO_SID,\
                          WDGIF_E_INV_POINTER\
                          );
  #endif /* end of #if (STD_ON == WDGIF_DEV_ERROR_DETECT) */
  } /* end of if (NULL_PTR != VersionInfoPtr) */
}
#endif /* end of #if (STD_ON == WDGIF_VERSION_INFO_API) */
#define WDGIF_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA2012:20.1 */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/

