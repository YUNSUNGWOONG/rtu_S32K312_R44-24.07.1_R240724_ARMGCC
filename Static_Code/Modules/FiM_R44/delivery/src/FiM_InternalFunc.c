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
**  SRC-MODULE: FiM_InternalFunc.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : Provision of EventId, FID Binary Search and calculation of    **
**              FID Permission Functionality                                  **
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
** 0.0.4    11-Sept-2020   ThienVT1        Changes made As per Redmine #15664 **
** 0.0.3     20-Aug-2020   ThienVT1        Changes made As per Redmine #15009 **
** 0.0.2    28-July-2020   ThienVT1        Changes made As per Redmine #14839 **
** 0.0.1    05-June-2020   ThienVT1        Initial Version                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "FiM.h"                  /* FiM Header File */
#include "SchM_FiM.h"             /* SchM Header File */
#include "FiM_InternalFunc.h"     /* Internal Func header file */
#include "Dem.h"                  /* Dem Header File */

/*******************************************************************************
**                           Global Data                                      **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : FiM_CalcAllFidsPermissions                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Calculation of FID permission for all the configured**
**                        FIDs                                                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non - Reentrant                                     **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        FiM_GaaFidInhibitCounter, FiM_GaaEventInfo,         **
**                        FiM_GaaFidPermissionState                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dem_GetMonitorStatus, FiM_CalcFidPermission         **
*******************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, FIM_CODE) FiM_CalcAllFidsPermissions(void)
{
  /* @Trace: FiM_SUD_API_084 */
  Dem_EventIdType LddEventId;
  FiM_EventsSizeType LddEvent;
  #if (FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO)
  boolean LblComponentFailedStatus;
  FiM_EventsSizeType LddComponent;
  Dem_ComponentIdType LddComponentId;
  #endif
  Dem_MonitorStatusType LddMonitorStatus = (Dem_MonitorStatusType)FIM_ZERO;
  Std_ReturnType LddDemReturn;
  Std_ReturnType LddReturn;
  /* Default return */
  LddReturn = E_OK;

  #if (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_OFF) && \
    (FIM_TOTAL_NUM_OF_FIDS > FIM_ZERO)
  FiM_FidsSizeType LddFid;
  /* Reset FID counters for all the configured Fids */
  for (LddFid = FIM_ZERO; LddFid < FIM_TOTAL_NUM_OF_FIDS; LddFid++)
  {
    /* @Trace: FiM_SUD_API_086 */
    FiM_GaaFidInhibitCounter[LddFid] = FIM_ZERO;
  }
  #endif
  /* Loop for all configured Events */
  /* to update the inhibition counters for all FIDs */
  #if (FIM_TOTAL_NUM_OF_DEM_EVENTS > FIM_ZERO)
  for (LddEvent = FIM_ZERO; LddEvent < FIM_TOTAL_NUM_OF_DEM_EVENTS; LddEvent++)
  {
    /* Get the EventId */
    /* @Trace: FiM_SUD_API_087 */
    LddEventId = FiM_GaaEventInfo[LddEvent].ddEventId;
    
    /* Get the Event Status of the configured EventId */
    LddDemReturn = Dem_GetMonitorStatus(LddEventId, &LddMonitorStatus);
    
    if (LddDemReturn == E_OK)
    {
      /* Data Protection ON */
      /* @Trace: FiM_SUD_API_089 */
      SchM_Enter_FiM_REQUEST_EVENTID_PROTECTION();
      /* Update the counters for all the FIDs linked to this Event */
      /* @Trace: SWS_Fim_00067 */
      FiM_CalcFidPermission(LddMonitorStatus, LddEvent);
      /* Data Protection OFF */
      SchM_Exit_FiM_REQUEST_EVENTID_PROTECTION();
    }
    /* This loop is used only during initialization and DET is enabled */
    /* @Trace: SWS_Fim_00097 */
    else
    {
      /* This loop is used only during initialization and DET is enabled */
      /* @Trace: FiM_SUD_API_090 */
      LddReturn = E_NOT_OK;
    }
  } /* for(LddEvent = FIM_ZERO; ... */
  #endif

  /* Enter Data Protection */
  /* @Trace: FiM_SUD_API_091 */
  SchM_Enter_FiM_REQUEST_FID_PROTECTION();
  /* For all configured FIDs */
  #if (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_OFF)
  for (LddFid = FIM_ZERO; LddFid < FIM_TOTAL_NUM_OF_FIDS; LddFid++)
  {
    /* @Trace: FiM_SUD_API_092 */
    #if (FIM_AVAILABILITY_SUPPORT == STD_ON)
    if(FIM_TRUE == FiM_GaaFidAvailableState[LddFid])
    #endif /* FIM_AVAILABILITY_SUPPORT == STD_ON */
    {
      if (FiM_GaaFidInhibitCounter[LddFid] > FIM_ZERO)
      {
        /* Inhibit the permission */
        /* @Trace: FiM_SUD_API_093 */
        FiM_GaaFidPermissionState[LddFid] = FIM_FALSE;
      }
      else
      {
        /* Clear permission state */
        FiM_GaaFidPermissionState[LddFid] = FIM_TRUE;
        /* @Trace: FiM_SUD_API_094 */
      }
    }
  }
  #endif
  /* Exit Data Protection */
  /* @Trace: FiM_SUD_API_095 */
  SchM_Exit_FiM_REQUEST_FID_PROTECTION();

  /* Loop for all configured Demcomponent */
  #if (FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO)
  /* @Trace: FiM_SUD_API_137 */
  LblComponentFailedStatus = FIM_FALSE;
  for (LddComponent = FIM_ZERO; LddComponent < FIM_TOTAL_NUM_OF_DEM_COMPONENT;
      LddComponent++)
  {
    /* @Trace: FiM_SUD_API_109 */
    /* Get the ComponentID */
    LddComponentId = FiM_GaaComponentInfo[LddComponent].ddComponentId;

    /* Get the Dem component Status configured */
    LddDemReturn = Dem_GetComponentFailed(LddComponentId,
        &LblComponentFailedStatus);
    if (E_OK == LddDemReturn)
    {
      FiM_GaaComponentFailedState[LddComponent] = LblComponentFailedStatus;
      /* Set Permission State */
      /* @Trace: SWS_Fim_00100 */
      /* @Trace: FiM_SUD_API_110 */
      FiM_CalcFidPermissionByComponent(LblComponentFailedStatus, LddComponent);
    }
    else
    {
      /* No require action */
    }
  } /* for(LddComponent = FIM_ZERO; ... */
  /* @Trace: FiM_SUD_API_111 */
  #endif
  return(LddReturn);
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : FiM_CalcFidPermission                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Calculation of FID permission for the FIDs related  **
**                        to one Event.                                       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non - Reentrant                                     **
**                                                                            **
** Input Parameters     : Dem_MonitorStatusType LddMonitorStatus,             **
**                        FiM_EventsSizeType LddEvent                         **
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
**                        FiM_GaaFidInhibitCounter, FiM_GaaFunctionIdMask,    **
**                        FiM_GaaEventInfo, FiM_GaaMaskValues,                **
**                        FiM_GaaExpMaskedResult, FiM_GaaFidPermissionState   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        None                                                **
*******************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, FIM_CODE) FiM_CalcFidPermission(Dem_MonitorStatusType
  LddMonitorStatus, FiM_EventsSizeType LddEvent)
{
  FiM_FidsSizeType LddFidArrayIndex;
  FiM_EventFidLinkType LddEventFidLink;
  FiM_FidsSizeType LddFid;
  FiM_FidsSizeType LddNoOfFids;
  uint8 LucFidMask;

  /* Index of configured FID Inhibition Mask Structure */
  /* @Trace: SWS_Fim_00013 */
  /* @Trace: SRS_Fim_04706 */
  /* @Trace: FiM_SUD_API_096 */
  LddEventFidLink = FiM_GaaEventInfo[LddEvent].ddFidArrayIndex;
  LddNoOfFids = FiM_GaaEventInfo[LddEvent].ddNumberOfFids;

  /* Checking Inhibition Mask of all the FIDs Configured for that EventId */
  /* The FiM shall compute the permission of a FID independently of the state
   * of other FIDs. */
  /* @Trace: SWS_Fim_00043 */
  /* @Trace: SRS_Fim_04706 */
  #if (FIM_TOTAL_NUM_OF_FUNCTION_ID_MASK > FIM_ZERO)
  for (LddFid = FIM_ZERO; LddFid < LddNoOfFids; LddFid++)
  {
     /* @Trace: FiM_SUD_API_097 */
    if (LddEventFidLink < (FiM_FidsSizeType)FIM_TOTAL_NUM_OF_FUNCTION_ID_MASK)
    {
      /* Fid Inhibition Mask */
      /* @Trace: SWS_Fim_00013 */
      /* @Trace: SRS_Fim_04706 */
      /* @Trace: SWS_Fim_00065 */
      /* @Trace: FiM_SUD_API_098 */
      LucFidMask = FiM_GaaFunctionIdMask[LddEventFidLink].ucInhibitionMask;
      LddFidArrayIndex = FiM_GaaFunctionIdMask[LddEventFidLink].ddFidIndex;

      /* Check if the changed status match with configured mask */
      /* @Trace: SWS_Fim_00012 */
      /* @Trace: SRS_Fim_04702 */
      #if (FIM_AVAILABILITY_SUPPORT == STD_ON)
      if (FIM_TRUE == FiM_GaaFidAvailableState[LddFid])
      #endif /* FIM_AVAILABILITY_SUPPORT == STD_ON */
      {
        /* @Trace: SWS_Fim_00012 */
        /* @Trace: SRS_Fim_04702 */
        if ((LddMonitorStatus & FiM_GaaMaskValues[LucFidMask]) ==
            FiM_GaaExpMaskedResult[LucFidMask])
        {
          /* Increment Counter */
          if (FiM_GaaFidInhibitCounter[LddFidArrayIndex]
              < (FiM_FidsSizeType) FIM_MAX_INHIBIT_COUNTER)
          {
            /* @Trace: FiM_SUD_API_099 */
            FiM_GaaFidInhibitCounter[LddFidArrayIndex]++;
            FiM_GaaFidPermissionState[LddFidArrayIndex] = FIM_FALSE;
          }
          else
          {
            /* No action in this case */
          }
        }
        else
        {
          #if (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON)
          /* Check Fid counter is non ZERO */
          if (FiM_GaaFidInhibitCounter[LddFidArrayIndex] > FIM_ONE)
          {
            /* @Trace: FiM_SUD_API_101 */
            FiM_GaaFidInhibitCounter[LddFidArrayIndex]--;
          }
          else
          {
            /* @Trace: FiM_SUD_API_100 */
            /* If counter reaches ZERO or ONE, change FID status */
            FiM_GaaFidInhibitCounter[LddFidArrayIndex] = FIM_ZERO;
            FiM_GaaFidPermissionState[LddFidArrayIndex] = FIM_TRUE;
          }
        #endif
        }
      }
      /* Move to next Fid of the Event */
      /* @Trace: FiM_SUD_API_112 */
      LddEventFidLink++;
      /* for(LddFid = FIM_ZERO; ... */
    }
    else
    {
      /* No action require */
    }
  }
  #endif
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : FiM_CalcFidPermissionByComponent                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Calculation of FID permission for the FIDs related  **
**                        to one DemComponent.                                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non - Reentrant                                     **
**                                                                            **
** Input Parameters     : boolean  ComponentFailedStatus,                     **
**                        FiM_ComponentSizeType LddComponentArrayIndex        **
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
**                        FiM_GaaComponentInfo, FiM_GaaFunctionIdComponent    **
**                        FiM_GaaFidPermissionState                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        None                                                **
*******************************************************************************/
#if (FIM_TOTAL_NUM_OF_FUNCTION_ID_COMPONENT > FIM_ZERO)
#define FIM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, FIM_CODE) FiM_CalcFidPermissionByComponent (boolean
        ComponentFailedStatus, FiM_ComponentSizeType LddComponentArrayIndex)
{
  FiM_FidsSizeType LddNoOfFids;
  FiM_ComponentFidLinkType LddComponentFidLink;
  FiM_FidsSizeType LddFidCount;
  FiM_FidsSizeType LddFidArrayIndex;
  /* Index of configured FID Inhibition Mask Structure */
  /* @Trace: SWS_Fim_00098 */
  /* @Trace: FiM_SUD_API_102 */
  LddComponentFidLink =
      FiM_GaaComponentInfo[LddComponentArrayIndex].ddFidArrayIndex;

  /* Get FID info */
  LddNoOfFids = FiM_GaaComponentInfo[LddComponentArrayIndex].ddNumberOfFids;
  for (LddFidCount = FIM_ZERO; LddFidCount < LddNoOfFids; LddFidCount++)
  {
    /* Get FID Index*/
    LddFidArrayIndex =
        FiM_GaaFunctionIdComponent[LddComponentFidLink].ddFidIndex;
    /* Whenever the component status is FAILED (ComponentFailedStatus */
    /* = TRUE), the FID is inhibited */
    /* @Trace: SWS_Fim_00099 */
    /* Set Inhibition all the FIDs Configured for that ComponentId */
    if ((FiM_GaaFidPermissionState[LddFidArrayIndex] != FIM_FALSE)
        && (ComponentFailedStatus != FIM_TRUE))
    {
      /* @Trace: FiM_SUD_API_138 */
      FiM_GaaFidPermissionState[LddFidArrayIndex] =  FIM_TRUE;
    }
    else
    {
      /* @Trace: FiM_SUD_API_139 */
      FiM_GaaFidPermissionState[LddFidArrayIndex] =  FIM_FALSE;
    }

    #if (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_ON)
    if ((ComponentFailedStatus == FIM_FALSE)
        && (FiM_GaaFidInhibitCounter[LddFidArrayIndex] == 0))
    {
      /* @Trace: FiM_SUD_API_140 */
      FiM_GaaFidPermissionState[LddFidArrayIndex] = FIM_TRUE;
    }
    #endif
    /* @Trace: FiM_SUD_API_141 */
    LddComponentFidLink++;
  }
}

#define FIM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : FiM_Report_Error                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : FiM report error to Det                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : uint8 sid                                           **
**                        uint8 type                                          **
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
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, FIM_CODE) FiM_Report_Error(uint8 sid, uint8 type)
{
   /* @Trace: SRS_BSW_00386 */
  #if (FIM_DEV_ERROR_DETECT == STD_ON)
  do
  {
    /* @Trace: FiM_SUD_API_142 */
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID,(sid),(type));
  }
  while (0);
  #else
  /* @Trace: FiM_SUD_API_143 */
  UNUSED(sid);
  UNUSED(type);
  do
  {
    /* Nothing to do */
  }
  while (0);
  #endif
}
#define FIM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
