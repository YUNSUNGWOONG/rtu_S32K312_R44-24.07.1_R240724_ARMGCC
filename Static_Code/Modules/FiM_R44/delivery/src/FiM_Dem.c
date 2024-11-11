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
**  SRC-MODULE: FiM.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : Provision of FiM APIs                                         **
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
** 1.0.3.0  21-Oct-2022    LanhLT          Ref #CP44-867                      **
** 0.0.5    11-Sept-2020   ThienVT1        Changes made As per Redmine #15664 **
** 0.0.4    20-Aug-2020    ThienVT1        Changes made As per Redmine #15009 **
** 0.0.3    28-July-2020   ThienVT1        Changes made As per Redmine #14839 **
** 0.0.2    18-July-2020   ThienVT1        Changes made As per Redmine #13068 **
** 0.0.1    05-June-2020   ThienVT1        Initial Version                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "FiM.h"         /* FiM Header File */
#include "FiM_Dem.h"
#include "FiM_Ram.h"     /* Ram header file */
#include "FiM_Config.h"     /* Ram header file */
#include "Dem.h"                     /* Dem Header File */
/* @Trace: FiM_SUD_DATATYPE_001 */
/* @Trace: FiM_SUD_DATATYPE_002 */
/* @Trace: FiM_SUD_DATATYPE_003 */
/* @Trace: SWS_Fim_00081 */
/* @Trace: SWS_Fim_00079 */
#include "SchM_FiM.h"                /* SchM Header File */
/* @Trace: FiM_SUD_DATATYPE_004 */
#include "Rte_FiM.h"                 /* Rte Header File */
#if (FIM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                     /* Det header file */
/* @Trace: SWS_Fim_00080 */
#endif
#include "FiM_InternalFunc.h"        /* Internal Func header file */

/*******************************************************************************
** Function Name        : FiM_DemInit                                         **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service shall re-initialize the permission     **
**                        states of the FIDs based on the event data of the   **
**                        Dem.                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GblInitStatus                                   **
**                        FiM_GaaComponentFailedState                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, FiM_CalcAllFidsPermissions         **
*******************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, FIM_CODE) FiM_DemInit(void)
/* @Trace: SWS_Fim_00006 */
{
  #if (FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO)
  FiM_FidsSizeType LddComponentID;
  for (LddComponentID= FIM_ZERO; LddComponentID < FIM_TOTAL_NUM_OF_DEM_COMPONENT
      ;LddComponentID++)
  {
    /* @Trace: FiM_SUD_API_135 */
    FiM_GaaComponentFailedState[LddComponentID] = FIM_FALSE;
  }
  #endif /* FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO */
  /*
   * Calculate all the configured Fid inhibition status.
   * Return value is not used
   */
  Std_ReturnType LddReturn;

  /* @Trace: SWS_Fim_00069 */
  /* @Trace: SWS_Fim_00082 */
  /* @Trace: FiM_SUD_API_024 */
  LddReturn = FiM_CalcAllFidsPermissions();
  if (LddReturn == E_OK)
  {
    /* @Trace: FiM_SUD_API_025 */
    FiM_GucInitStatus = FIM_INITIALIZED;
  }
  else
  {
    /* Report to DET that FiM is not successfully initialized */
    /* @Trace: SWS_Fim_00076 */
    /* @Trace: FiM_SUD_API_026 */
    FiM_Report_Error(FIM_DEMINIT_SID, FIM_E_INIT_FAILED);
  }
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : FiM_DemTriggerOnMonitorStatus                       **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service is provided to be called by the Dem in **
**                        order to inform the FiM about monitor status changes**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GblInitStatus, FiM_GaaEventInfo,                **
**                        FiM_GaaFunctionIdMask, FiM_GaaMaskValues,           **
**                        FiM_GaaExpMaskedResult, FiM_GaaFidInhibitCounter,   **
**                        FiM_GaaFidPermissionState                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, FiM_EventIdBinarySearch,           **
**                        SchM_Enter_FiM_REQUEST_EVENTID_PROTECTION,          **
**                        SchM_Exit_FiM_REQUEST_EVENTID_PROTECTION            **
*******************************************************************************/
/* Check if FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON */
#if (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON)
#define FIM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, FIM_CODE) FiM_DemTriggerOnMonitorStatus(Dem_EventIdType EventId)
/* polyspace<MISRA-C:5.6:Not a defect:Justify with annotations> EventId : AUTOSAR Standard */
/* @Trace: SWS_Fim_00021 */
/* @Trace: SRS_Fim_04717 */
{
  boolean LblEventExists;
  Std_ReturnType LddDemReturn;
  FiM_EventsSizeType LddEventArrayIndex;
  Dem_MonitorStatusType LddMonitorStatus;

  #if (FIM_DEV_ERROR_DETECT == STD_ON)
  boolean LblDevErrorFlag;
  #endif /* FIM_DEV_ERROR_DETECT == STD_ON */

  /* @Trace: FiM_SUD_API_120 */
  LddEventArrayIndex = (FiM_EventsSizeType)FIM_ZERO;
  LddMonitorStatus = (Dem_MonitorStatusType)FIM_ZERO;

  #if (FIM_DEV_ERROR_DETECT == STD_ON)
  LblDevErrorFlag = FIM_FALSE;
  #endif /* FIM_DEV_ERROR_DETECT == STD_ON */

  #if (FIM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the FiM Module is initialized */
  if (FiM_GucInitStatus != FIM_INITIALIZED)
  {
    /* Report to DET indicating WrongTriggerOnEvent */
    /* @Trace: SRS_BSW_00406 */
    /* @Trace: SWS_Fim_00076 */
    /* @Trace: SWS_Fim_00058 */
    /* @Trace: FiM_SUD_API_121 */
    FiM_Report_Error(FIM_DEMTRIGGERONMONITORSTATUS_SID, FIM_E_UNINIT);
    /* Set the development error flag */
    LblDevErrorFlag = FIM_TRUE;
  } 
  else if (((Dem_EventIdType)FIM_ZERO == EventId) 
          || ((Dem_EventIdType)FIM_DEM_NUMBER_OF_EVENTS < EventId))
  {
    /* @Trace: SWS_Fim_00057 */
    FiM_Report_Error(FIM_DEMTRIGGERONMONITORSTATUS_SID, FIM_E_EVENTID_OUT_OF_RANGE);
    LblDevErrorFlag = FIM_TRUE;
  }
  else
  {
    /* No require action */
  }
  /* Check if No Development errors occurred */
  if (LblDevErrorFlag == FIM_FALSE)
  #endif /* FIM_DEV_ERROR_DETECT == STD_ON */
  {
    /* Check whether EventId is in the configured range */
    /* @Trace: FiM_SUD_API_122 */
    LblEventExists = FiM_EventIdSearch(EventId, &LddEventArrayIndex);

    /* Requested Event Id is found in FIM configuration */
    if (LblEventExists == FIM_TRUE)
    {
      /* Get the Event Status of the configured EventId */
      /* @Trace: FiM_SUD_API_123 */
      LddDemReturn = Dem_GetMonitorStatus(EventId, &LddMonitorStatus);

      /* Check if No Development errors occurred */
      if (LddDemReturn == E_OK)
      {
        /* Data Protection ON */
        /* @Trace: FiM_SUD_API_125 */
        SchM_Enter_FiM_REQUEST_EVENTID_PROTECTION();
        /* Update the counters for all the FIDs linked to this Event */
        FiM_CalcFidPermission(LddMonitorStatus, LddEventArrayIndex);
        /* Data Protection OFF */
        SchM_Exit_FiM_REQUEST_EVENTID_PROTECTION();
      }
      else
      {
        /* No require action */
      }
    }
    else
    {
      /* @Trace: FiM_SUD_API_126 */
      UNUSED(LblEventExists);
      UNUSED(LddDemReturn);
      /* Report to DET that FiM is not successfully initialized */
      /* @Trace: SRS_BSW_00406 */
      /* @Trace: SWS_Fim_00076 */
      /* @Trace: SWS_Fim_00057 */
      FiM_Report_Error(FIM_DEMTRIGGERONMONITORSTATUS_SID,
          FIM_E_EVENTID_OUT_OF_RANGE);
    }
  }

  #if (FIM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No require action */
    /* @Trace: FiM_SUD_API_124 */
   UNUSED(LblEventExists);
   UNUSED(LddEventArrayIndex);
   UNUSED(EventId);
   UNUSED(LddMonitorStatus);
  }
  #endif /* FIM_DEV_ERROR_DETECT == STD_ON */
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON) */

/*******************************************************************************
** Function Name        : FiM_DemTriggerOnComponentStatus                     **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : Triggers on changes of the component failed status. **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Dem_ComponentIdType ComponentId                     **
**                        boolean ComponentFailedStatus                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GblInitStatus, FiM_GaaEventInfo,                **
**                        FiM_GaaFunctionIdMask, FiM_GaaMaskValues,           **
**                        FiM_GaaExpMaskedResult, FiM_GaaFidInhibitCounter,   **
**                        FiM_GaaFidPermissionState                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, FiM_ComponentIdSearch,             **
**                        SchM_Enter_FiM_REQUEST_EVENTID_PROTECTION,          **
**                        SchM_Exit_FiM_REQUEST_EVENTID_PROTECTION            **
*******************************************************************************/
/* (FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO)
 * && (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON)*/
#if ((FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO) \
  && (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON))
#define FIM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, FIM_CODE) FiM_DemTriggerOnComponentStatus(
  Dem_ComponentIdType ComponentId,
  VAR(boolean, FIM_VAR_NOINIT) ComponentFailedStatus)
/* @Trace: SWS_Fim_00101 */
{
  Std_ReturnType LddReturnValue;
 
  boolean LblDevErrorFlag;
  boolean LblComponentExists;
  boolean LblComponentFailedStatus;
  FiM_ComponentFidLinkType LddComponentArrayIndex;

  /* @Trace: FiM_SUD_API_127 */
  LblDevErrorFlag = FIM_FALSE;
  LddComponentArrayIndex = (uint16)FIM_ZERO;
  LblComponentFailedStatus = ComponentFailedStatus;
  
  /* Check if the FiM Module is initialized */
  if (FiM_GucInitStatus != FIM_INITIALIZED)
  {
    /* Report to DET indicating WrongTriggerOnEvent */
    /* @Trace: SWS_Fim_00076 */
    /* @Trace: FiM_SUD_API_128 */
    FiM_Report_Error(FIM_DEMTRIGGERONCOMPONENTSTATUS_SID, FIM_E_UNINIT);

    /* Set the development error flag */
    LblDevErrorFlag = FIM_TRUE;
  }
  else
  {
    /* No require action */
  }
  /* Check if No Development errors occurred */
  if (LblDevErrorFlag == FIM_FALSE)
  {
    /* Check whether ComponentId is in the configured range */
    /* @Trace: FiM_SUD_API_129 */
    LblComponentExists = FiM_ComponentIdSearch(ComponentId,
        &LddComponentArrayIndex);

    /* Requested Dem Component Id is found in FIM configuration */
    if (FIM_TRUE == LblComponentExists)
    {
      /* Get the Event Status of the configured ComponentId */
      /* @Trace: SWS_Fim_00099 */
      /* @Trace: FiM_SUD_API_130 */

      LddReturnValue =  Dem_GetComponentFailed(ComponentId,
          &LblComponentFailedStatus);
      /* Check if don't have any fail action */
      if (E_OK == LddReturnValue)
      {
        /* @Trace: FiM_SUD_API_131 */
        boolean LbloldFAILEDState =
            FiM_GaaComponentFailedState[LddComponentArrayIndex];
        if (LbloldFAILEDState != LblComponentFailedStatus)
        {
          /* @Trace: FiM_SUD_API_136 */
          FiM_GaaComponentFailedState[LddComponentArrayIndex] =
              LblComponentFailedStatus;
          /* Data Protection ON */
          SchM_Enter_FiM_REQUEST_EVENTID_PROTECTION();
          /* Set Permission State */
          /* @Trace: SWS_Fim_00100 */
          FiM_CalcFidPermissionByComponent(LblComponentFailedStatus,
                                           LddComponentArrayIndex);
          /* Data Protection OFF */
          SchM_Exit_FiM_REQUEST_EVENTID_PROTECTION();
        }
      }
      else
      {
        /* No require action */
      }
    }
    else
    {
      /* @Trace: FiM_SUD_API_132 */
      UNUSED(LddReturnValue);
      /* Report to DET that FiM is not successfully initialized */
      /* @Trace: SWS_Fim_00076 */
      FiM_Report_Error(FIM_DEMTRIGGERONCOMPONENTSTATUS_SID,
                       FIM_E_EVENTID_OUT_OF_RANGE);
    }
  }
  else
  {
    /* No require action */
    /* @Trace: FiM_SUD_API_133 */
    UNUSED(LblComponentExists);
  }
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* (FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO) && \
(FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON) */
