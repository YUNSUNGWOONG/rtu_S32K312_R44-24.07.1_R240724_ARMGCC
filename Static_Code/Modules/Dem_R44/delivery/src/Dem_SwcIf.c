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
**  SRC-MODULE: Dem_SwcIf.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Provision of Software Components Interface Functionality      **
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
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"
#include "Dem_Ram.h"
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#include "NvM.h"              /* NVRAM manager symbols Header File */

#include "SchM_Dem.h"
#include "Rte_Dem.h"

#include "Dem_NvData.h"
#include "Dem_Event.h"
#include "Dem_EventRelatedData.h"
#include "Dem_EventCallback.h"
#include "Dem_Indicator.h"
#include "Dem_EventDebounce.h"
#include "Dem_Dtc.h"
#include "Dem_EventAging.h"
#include "Dem_EventMemory.h"


/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations>
 * Not a defect */


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
 * Function Name        : Dem_SetEventFailureCycleCounterThreshold            **
 *                                                                            **
 * Service ID           : 0x57                                                **
 *                                                                            **
 * Description          : Set the failure confirmation threshold of           **
 *                        an event                                            **
 *                                                                            **
 * Sync/Async           : Asynchronous                                        **
 *                                                                            **
 * Re-entrancy          : Reentrant                                           **
 *                                                                            **
 * Input Parameters     : EventId                                             **
 *                        FailureCycleCounterThreshold                        **
 *                                                                            **
 * InOut parameter      : None                                                **
 *                                                                            **
 * Output Parameters    : None                                                **
 *                                                                            **
 * Return parameter     : Std_ReturnType                                      **
 *                                                                            **
 * Preconditions        : None                                                **
 *                                                                            **
 * Remarks              : Global Variable(s)  :                               **
 *                        Dem_GucInit                                         **
 *                        Dem_GaaEventFailureThreshold                        **
 *                        Function(s) invoked :                               **
 *                        (void)Det_ReportError()                             **
 *                        None                                                **
 ******************************************************************************/
/* @Trace: SRS_Diag_04161 SRS_BSW_00300
 */
/* @Trace: Dem_SUD_MACRO_027 */
/* polyspace +1 MISRA-C3:8.4 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventFailureCycleCounterThreshold(
Dem_EventIdType EventId,
uint8 FailureCycleCounterThreshold
)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  /* Check module initialization after Dem_PreInit */
  /* @Trace: SWS_Dem_01242
   * The Dem shall support calls of Dem_SetEventFailureCycleCounterThreshold
   * after Dem_PreInit.
   */
  if ((DEM_INIT != Dem_GucInit) && (DEM_PREINIT != Dem_GucInit))
  {
    /* @Trace: Dem_SUD_API_12373 */
    DEM_REPORT_ERROR(DEM_SETEVENTFAILURECYCLECOUTERTHRESHOLD_SID, DEM_E_UNINIT);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if ((EventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == EventId))
  {
    /* @Trace: Dem_SUD_API_10319 */
    DEM_REPORT_ERROR(
        DEM_SETEVENTFAILURECYCLECOUTERTHRESHOLD_SID, DEM_E_PARAM_CONFIG);
    /* @LddRetVal = E_NOT_OK; */
  }
  else
  {
    /* @Trace: SWS_Dem_01243
     * A call of the API Dem_SetEventFailureCycleCounterThreshold shall set a
     * new failure confirmation threshold.
     */
    /* @Trace: Dem_SUD_API_10316 */
    if (DEM_FALSE != LddEvent->blDemEventFailureCycleCounterThresholdAdaptable)
    {
      /* @Trace: Dem_SUD_API_12374 */
      Dem_GaaEventFailureThreshold[EventId] = FailureCycleCounterThreshold;
      LddRetVal = E_OK;
    }
  }
  return LddRetVal;
}
/*******************************************************************************
** Function Name        : Dem_ResetEventStatus                                **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This service shall be used to reset the Event       **
**                        Status stored in the Event Memory in the DEM        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
** Global Variable(s)   :                                                     **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
**                        Dem_DtcStatusUpdate()                               **
**                        Dcm_DemTriggerOnDTCStatus()                         **
**                        Dlt_DemTriggerOnEventStatus()                       **
*******************************************************************************/
/* @Trace: SRS_BSW_00406 SRS_Diag_04067 SRS_Diag_04126 SRS_Diag_04165
           SRS_Diag_04179 SRS_BSW_00300
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_ResetEventStatus(Dem_EventIdType EventId)
{
  /* @Trace: SWS_Dem_00187
   * The function Dem_ResetEventStatus shall set the event status bit 0
   * (TestFailed) to 0 and reset the Dem-internal debounce algorithm to initial
   * values if configured. The Dem shall execute this action asynchronously at
   * a later point in time.
   */
  /* @Trace: SWS_Dem_00331
   * The Dem module shall provide the capability to reset the failed status of
   * an event without reporting a passed result (refer to Dem_ResetEventStatus).
   */

  /* @Trace: SWS_Dem_00124
   * If DemDevErrorDetect is set to TRUE and any Dem API excluding :
   * - Dem_ResetEventStatus
   * - Dem_SetEventAvailable
   * - Dem_ResetEventDebounceStatus
   * - Dem_GetVersionInfo
   * - Dem_MainFunction
   */
  Std_ReturnType LddRetVal = E_NOT_OK;
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12173 */
    DEM_REPORT_ERROR(DEM_RESETEVENTSTATUS_SID, DEM_E_UNINIT);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if ((EventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == EventId))
  {
    /* @Trace: Dem_SUD_API_12182 */
    DEM_REPORT_ERROR(DEM_RESETEVENTSTATUS_SID, DEM_E_PARAM_CONFIG);
    /* @LddRetVal = E_NOT_OK; */
  }
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  else if (DEM_TRUE !=
      Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE))
  {
    /* @Trace: Dem_SUD_API_12183 */
    /* @Trace: SWS_Dem_01108
     * If an event is set to unavailable, the corresponding event shall
     * be treated as if it is not configured in the system (e.g.
     * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return E_NOT_OK). */
    /* @LddRetVal = E_NOT_OK; */
  }
  #endif
  else
  {
    /* @Trace: SWS_Dem_01250
     * For each DemMultiEventTriggeringSlaveEventRef of this
     * DemMultiEventTriggering the Dem shall trigger the same API calls with
     * identical parameters only the EventId parameter shall be replaced with
     * the event referenced from DemMultiEventTriggeringSlaveEventRef.*/
    Dem_EventIdType LddEvId = EventId;
    uint8 LucStartIdx = DEM_ZERO;
    uint8 LucStopIdx = DEM_ONE;
    #if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
    /* @Trace: Dem_SUD_API_12184 */
    uint8 LucIdxOfMasterEvent = Dem_GetIndexOfMasterEventByEventId(LddEvId);
    boolean LblIdxOfMasterEventIsFound = DEM_FALSE;
    /* @Trace: Dem_SUD_API_12185 */
    if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING != LucIdxOfMasterEvent)
    {
      /* @Trace: Dem_SUD_API_12186 */
      LucStartIdx = Dem_DemMultiEventTrg[LucIdxOfMasterEvent].slaveEventIdx;
      LucStopIdx =
          LucStartIdx +
          Dem_DemMultiEventTrg[LucIdxOfMasterEvent].numberOfSlaveEvent;
      LblIdxOfMasterEventIsFound = DEM_TRUE;
    }
    #endif
    /* Report status for all salve event related from master event id */
    /* @Trace: Dem_SUD_API_12187 */
    for (; LucStartIdx < LucStopIdx; LucStartIdx++)
    {
      /* @Trace: Dem_SUD_API_12174 */
      #if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
      /* @Trace: Dem_SUD_API_12188 */
      if (DEM_TRUE == LblIdxOfMasterEventIsFound)
      {
        /* @Trace: Dem_SUD_API_12189 */
        LddEvId = Dem_ListOfSlaveEventTrg[LucStartIdx];
      }
      #endif

      if (DEM_FALSE == Dem_GetLocksByEventIdAndEvMem(LddEvId))
      {
        /* @Trace: Dem_SUD_API_12175 */
        /* LddRetVal = E_NOT_OK; */
      }
      else
      {
        /* @Trace: SWS_Dem_00638
         * The function Dem_ResetEventStatus shall return E_NOT_OK,
         * if the event was already tested this operation cycle (UDS DTC status
         * bit 6 - TestNotCompletedThisOperationCycle is set to 0).
         *
         * The operation cycle status has no impact on
         * Dem_ResetEventDebounceStatus and Dem_ResetEventStatus. */
        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(LddEvId, DEM_UDS_STATUS_TNCTOC))
        {
          Dem_EventParameterPCType LddEvent = &Dem_Event[LddEvId - DEM_ONE];
          /* @Trace: SWS_Dem_00525
           * If test failed bit is set then reset it */
          if (DEM_IS_BIT_SET_UDSSTATUSBYTE(LddEvId, DEM_UDS_STATUS_TF))
          {
            const Dem_UdsStatusByteType LddDTCStatusOld =
                Dem_GetDTCStatus(LddEvId);
            const Dem_UdsStatusByteType LddEventStatusByteOld =
                Dem_AllEventStatusByte[LddEvId];
            /* Reset the Status */
            DEM_CLR_UDSSTATUSBYTE(LddEvId, DEM_UDS_STATUS_TF);
            /* @Trace: Dem_SUD_API_12179 */
            if (DEM_TRUE ==
                  DEM_GET_EVENTPARAM_STORAGE_TF(LddEvent->ParamFieldsA))
            {
              Dem_CombinedDtcPCType LddCbDTC =
                  Dem_GetCbDTCByEventId(LddEvId);
                  /* @Trace: Dem_SUD_API_12180 */
              if ((NULL_PTR != LddCbDTC) &&
                  (DEM_NO_DTC_ORIGIN != LddEvent->aaEventDestination))
              {
                /* @Trace: Dem_SUD_API_12181 */
                /* Ignore ImmediateStorageLimit */
                if (DEM_EVMEM_STATUS_DIRTY_NVM ==
                      Dem_EvMem_TriggerNvDataStorage(
                          LddEvId,
                          LddEvent->aaEventDestination,
                          LddEventStatusByteOld,
                          LddCbDTC->EvMemTriggerFlag,
                          DEM_FALSE,
                          DEM_FALSE))
                {
                  /* @Trace: Dem_SUD_API_10301 */
                  Dem_EvMem_TriggerWriteAllBlocks();
                }
              }
            }
            /*No need  if (LddEventStatusByteOld != Dem_AllEventStatusByte[LddEvId]) */
            Dem_TriggerCallbackOnUdsStatus(
                EventId, LddEventStatusByteOld, LddDTCStatusOld);
          }
          /* @Trace: Dem_SUD_API_12177 */
          if (DEM_IS_BIT_SET_MONITORSTATUSBYTE(LddEvId, DEM_MONITOR_STATUS_TF))
          {
            const Dem_MonitorStatusType LddMonitorStatusByteOld =
                Dem_AllMonitorStatus[LddEvId];
            DEM_CLR_MONITORSTATUSBYTE(
                LddEvId, (Dem_MonitorStatusType) DEM_MONITOR_STATUS_TF);
            /* @Trace: SWS_Dem_01282
             * Upon processing the monitor status, the Dem shall call the
             * monitor status changed callback functions:
             * <Module>_DemTriggerOnMonitorStatus whenever the monitor status
             * has changed. */
            /* @Trace: Dem_SUD_API_12178 */
            if (LddMonitorStatusByteOld != Dem_AllMonitorStatus[LddEvId])
            {
              /* @Trace: Dem_SUD_API_10302 */
              DemTriggerCallbackOnMonitorStatus(LddEvId);
            }
          }
          /* Reset the debounce counters */
          Dem_ResetFaultDectectionCounter(LddEvId);

          /* @Trace: SWS_Dem_00626
           * Control DTC setting has no impact  Dem_ResetEventStatus */
          LddRetVal = E_OK;
        }
        else
        {
          /* @Trace: Dem_SUD_API_12176 */
          /* @Trace: SWS_Dem_00638
           * The function Dem_ResetEventStatus shall return E_NOT_OK, if the
           * event was already tested this operation cycle (UDS DTC status bit 6
           * - TestNotCompletedThisOperationCycle is set to 0).*/
          DEM_REPORT_ERROR(DEM_RESETEVENTSTATUS_SID, DEM_E_PARAM_DATA);
          LddRetVal = E_NOT_OK;
        }
        Dem_FreeLockByEventId(LddEvId);
      }
    }
  }
  return LddRetVal;
}


/*******************************************************************************
 ** Function Name       : Dem_ResetEventDebounceStatus                        **
 **                                                                           **
 ** Service ID          : 0x09                                                **
 **                                                                           **
 ** Description         : Control the internal debounce counter/timer by BSW  **
 **                       modules and SWCs.                                   **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant for different EventIds.                   **
 **                       Non reentrant for the same EventId                  **
 **                                                                           **
 ** Input Parameters    : EventId, DebounceResetStatus                        **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : none                                                **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                                                                           **
 **                       Function(s) invoked :                               **
 **                                                                           **
 ******************************************************************************/
/* @Trace: SRS_Diag_04068 SRS_Diag_04124 SRS_Diag_04126 SRS_Diag_04165
           SRS_BSW_00300
 */
/* polyspace +1 MISRA-C3:8.4 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DEM_CODE) Dem_ResetEventDebounceStatus(
    Dem_EventIdType EventId,
    Dem_DebounceResetStatusType DebounceResetStatus)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ((DEM_NO_EVENT == EventId) || (EventId > DEM_NUMBER_OF_EVENTS))
  {
    /* @Trace: Dem_SUD_API_10303 */
    DEM_REPORT_ERROR(DEM_RESETEVENTDEBOUNCESTATUS_SID, DEM_E_PARAM_CONFIG);
    /* @LddRetVal = E_NOT_OK; */
  }
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  else if ( DEM_TRUE !=
      Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE))
  {
    /* @Trace: Dem_SUD_API_12165 */
      /*@Trace: SWS_Dem_01108
       * If an event is set to unavailable, the corresponding event shall
       * be treated as if it is not configured in the system (e.g.
       * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return E_NOT_OK). */

      /* @LddRetVal = E_NOT_OK; */
  }
  #endif
  else if ((DEM_DEBOUNCE_STATUS_FREEZE != DebounceResetStatus) &&
           (DEM_DEBOUNCE_STATUS_RESET != DebounceResetStatus))
  {
    /* @Trace: Dem_SUD_API_10304 */
    DEM_REPORT_ERROR(DEM_RESETEVENTDEBOUNCESTATUS_SID, DEM_E_PARAM_DATA);
    /* LddRetVal = E_NOT_OK */
  }
  else
  {
    #if ((DEM_DEV_ERROR_DETECT == STD_ON) && \
        (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO))
    Dem_NumOfDebounceType LddDebounceId =
        Dem_Event[EventId - DEM_ONE].ucIndexOfDebounceAry;
    P2CONST(Dem_PreDebounceCounterType, AUTOMATIC, DEM_CONST) LddDcb =
        &Dem_GaaPreDebounceCounter[LddDebounceId];
    uint8 LucDebounceType =
        DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(
            Dem_Event[EventId - DEM_ONE].ParamFieldsA);
    #endif

    /* @Trace: SWS_Dem_00676
     * If development error detection is enabled and
     * Dem_SetEventStatus or Dem_ResetEventDebounceStatus is called before
     * Dem_Init or after Dem_Shutdown for events which have DemDebounce-
     * CounterStorage set to True, the Dem module shall set the error code
     * DEM_E_WRONG_CONDITION. */
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
    /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
    #if ((DEM_DEV_ERROR_DETECT == STD_ON) && \
         (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO))
    if ((DEM_DEBOUNCE_COUNTER_BASED == LucDebounceType) &&
        (DEM_TRUE == (LddDcb->blDemDebounceCounterStorage)) &&
        (DEM_INIT != Dem_GucInit))
    {
      /* @Trace: Dem_SUD_API_12166 */
      DEM_REPORT_ERROR(DEM_RESETEVENTDEBOUNCESTATUS_SID, DEM_E_WRONG_CONDITION);
      /* LddRetVal = E_NOT_OK */
    }
    else
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
    #endif
    {
      /* @Trace: SWS_Dem_01250
       * For each DemMultiEventTriggeringSlaveEventRef of this
       * DemMultiEventTriggering the Dem shall trigger the same API calls with
       * identical parameters only the EventId parameter shall be replaced with
       * the event referenced from DemMultiEventTriggeringSlaveEventRef.*/
      Dem_EventIdType LddEvId = EventId;
      uint8 LucStartIdx = DEM_ZERO;
      uint8 LucStopIdx = DEM_ONE;
      #if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
      /* @Trace: Dem_SUD_API_12167 */
      uint8 LucIdxOfMasterEvent = Dem_GetIndexOfMasterEventByEventId(LddEvId);
      boolean LblIdxOfMasterEventIsFound = DEM_FALSE;
      /* @Trace: Dem_SUD_API_12168 */
      if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING != LucIdxOfMasterEvent)
      {
        /* @Trace: Dem_SUD_API_10305 */
        LucStartIdx = Dem_DemMultiEventTrg[LucIdxOfMasterEvent].slaveEventIdx;
        LucStopIdx =
            LucStartIdx +
            Dem_DemMultiEventTrg[LucIdxOfMasterEvent].numberOfSlaveEvent;
        LblIdxOfMasterEventIsFound = DEM_TRUE;
      }
      #endif
      /* @Trace: Dem_SUD_API_12169 */
      /* Report status for all salve event related from master event id */
      for (; LucStartIdx < LucStopIdx; LucStartIdx++)
      {
        #if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
        /* @Trace: Dem_SUD_API_12170 */
        if (DEM_TRUE == LblIdxOfMasterEventIsFound)
        {
          /* @Trace: Dem_SUD_API_10306 */
          LddEvId = Dem_ListOfSlaveEventTrg[LucStartIdx];
        }
        #endif

        /* @Trace: SWS_Dem_00684
         * If the API Dem_ResetEventDebounceStatus is called with
         * DEM_DEBOUNCE_STATUS_RESET, it shall reset the related fault detection
         * counter. */

        if (DEM_DEBOUNCE_STATUS_RESET == DebounceResetStatus)
        {
          /* @Trace: Dem_SUD_API_12172 */
          Dem_ResetFaultDectectionCounter(LddEvId);
          #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
          Dem_EnableFreeze[LddEvId - DEM_ONE] = DEM_FALSE;
          #endif
          LddRetVal = E_OK;
        }
        /* @Trace: SWS_Dem_00685
         * If the API Dem_ResetEventDebounceStatus is called with
         * DEM_DEBOUNCE_STATUS_FREEZE, it shall freeze the related internal
         * debounce timer
         * */
        /* DebounceResetStatus = DEM_DEBOUNCE_STATUS_FREEZE */
        else
        {
          /* @Trace: Dem_SUD_API_12171 */
          #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
          Dem_EnableFreeze[LddEvId - DEM_ONE] = DEM_TRUE;
          #endif
          LddRetVal = E_OK;
        }
      }
    }
  }
  return LddRetVal;
}


/*******************************************************************************
** Function Name        : Dem_PrestoreFreezeFrame                             **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : This API call is used to capture the FreezeFrame    **
**                        data for a specific EventId before the Monitor      **
**                        Function reports the event status                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
**                        Dem_PrestorePid()                                   **
*******************************************************************************/
/* @Trace: SRS_Diag_04074 SRS_Diag_04126 SRS_Diag_04127 SRS_Diag_04165
           SRS_BSW_00300
 */
#if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO)
FUNC(Std_ReturnType, DEM_CODE) Dem_PrestoreFreezeFrame(Dem_EventIdType EventId)
{
  /* @Trace: SWS_Dem_00188
   */
  /* @Trace: SWS_Dem_00334
   * If any event is configured to use pre-storage of freeze frames (refer to
   * DemFFPrestorageSupported), the Dem module shall provide the API
   * Dem_PrestoreFreezeFrame and Dem_ClearPrestoredFreezeFrame. Otherwise they
   * are not provided.
   */
  /* @Trace: SWS_Dem_00807
   * The capture (sampling) of data (using [SWS_Dem_00261]) shall be synchronous
   * in the call of Dem_PrestoreFreezeFrame.
   */
  /* @Trace: SWS_Dem_00189
   * The Dem module shall provide the API Dem_PrestoreFreezeFrame to capture the
   * pre-storage data of an event-specific freeze frame regardless of the UDS
   * status bit changes.
   */
  Std_ReturnType LddRetVal = E_NOT_OK;
  if ( DEM_INIT != Dem_GucInit )
  {
    /* @Trace: Dem_SUD_API_12286 */
    DEM_REPORT_ERROR(DEM_PRESTOREFREEZEFRAME_SID, DEM_E_UNINIT);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if ((EventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == EventId))
  {
    /* @Trace: Dem_SUD_API_10334 */
    DEM_REPORT_ERROR(DEM_PRESTOREFREEZEFRAME_SID, DEM_E_PARAM_CONFIG);
    /* @LddRetVal = E_NOT_OK; */
  }
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  else if ( DEM_TRUE !=
      Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE))
  {
    /* @Trace: Dem_SUD_API_12291 */
    /* @Trace: SWS_Dem_01108
     * If an event is set to unavailable, the corresponding event shall
     * be treated as if it is not configured in the system (e.g.
     * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return E_NOT_OK). */
    /* LddRetVal = E_NOT_OK; */
  }
  #endif
  else
  {
    /* @Trace: SWS_Dem_01250
     * For each DemMultiEventTriggeringSlaveEventRef of this
     * DemMultiEventTriggering the Dem shall trigger the same API calls with
     * identical parameters only the EventId parameter shall be replaced with
     * the event referenced from DemMultiEventTriggeringSlaveEventRef.*/
    Dem_EventIdType LddEvId = EventId;
    uint8 LucStartIdx = DEM_ZERO;
    uint8 LucStopIdx = DEM_ONE;
    #if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
    uint8 LucIdxOfMasterEvent = Dem_GetIndexOfMasterEventByEventId(LddEvId);
    boolean LblIdxOfMasterEventIsFound = DEM_FALSE;
    /* @Trace: Dem_SUD_API_12292 */
    if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING != LucIdxOfMasterEvent)
    {
      /* @Trace: Dem_SUD_API_12293 */
      LucStartIdx = Dem_DemMultiEventTrg[LucIdxOfMasterEvent].slaveEventIdx;
      LucStopIdx =
          LucStartIdx +
          Dem_DemMultiEventTrg[LucIdxOfMasterEvent].numberOfSlaveEvent;
      LblIdxOfMasterEventIsFound = DEM_TRUE;
    }
    #endif
    /* Report status for all salve event related from master event id */
    for (; LucStartIdx < LucStopIdx; LucStartIdx++)
    {
      #if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
      /* @Trace: Dem_SUD_API_10332 */
      if (DEM_TRUE == LblIdxOfMasterEventIsFound)
      {
        /* @Trace: Dem_SUD_API_12294 */
        LddEvId = Dem_ListOfSlaveEventTrg[LucStartIdx];
      }
      #endif

      if (DEM_FALSE == Dem_GetLockByEventId(LddEvId))
      {
        /* @Trace: Dem_SUD_API_12295 */
        /* LddRetVal = E_NOT_OK; */
      }
      else
      {
        /* @Trace: Dem_SUD_API_12296 */
        P2VAR(uint8, AUTOMATIC, DEM_VAR) LpBase = NULL_PTR;
        Dem_NumOfPrestoredFFType LddBufferIndex = DEM_ZERO;

        Dem_EventParameterCPCType LddEvent = &Dem_Event[LddEvId - DEM_ONE];
        if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
        {
          /* @Trace: Dem_SUD_API_12298 */
          Dem_EventRelatedDataPCType LddEvData =
              &Dem_EventRelatedData[LddEvent->e_PointToData];
              /* @Trace: Dem_SUD_API_12289 */
          if (DEM_TRUE == LddEvData->FFPreStorageSupported)
          {
            /* @IF_REQ : 1. buffer need the lock. 2. need to optimize. */
            /* Search for empty entry in Prestored buffer */
            LpBase = Dem_GetBufferOfPrestoredFF(LddEvId, &LddBufferIndex);
            /* @Trace: Dem_SUD_API_12288 */
            if (NULL_PTR == LpBase)
            {
              /* @Trace: Dem_SUD_API_12287 */
              LpBase =
                  Dem_GetBufferOfPrestoredFF(DEM_NO_EVENT, &LddBufferIndex);
            }

            if (NULL_PTR != LpBase)
            {
              /* @IF_REQ step 1: check FFClassPos, step 2 get buffer */
              /* @Trace: Dem_SUD_MACRO_120 */
              #if (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO)
              /* @Trace: Dem_SUD_API_10333 */
              /* @Trace: Dem_SUD_MACRO_094 */
              if (LddEvData->FFClassPos < DEM_NUM_OF_FREEZEFRAMECLASS)
              {
                /* @Trace: Dem_SUD_API_12290 */
                /* polyspace +5 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
                (void)Dem_CaptureFFClass(
                    LddEvId,
                    &Dem_FreezeFrameClass[LddEvData->FFClassPos],
                    LpBase,
                    DEM_SIZE_OF_PRESTORED_FF);
                Dem_SetEventIdOfPrestoredFF(LddBufferIndex,LddEvId);
                LddRetVal = E_OK;
              }
              #endif
            }
            /* @Trace: SWS_Dem_00808
             * The API Dem_PrestoreFreezeFrame shall return E_NOT_OK if no
             * memory is available (see DemMaxNumberPrestoredFF).
             */
            else
            {
              /* @Trace: Dem_SUD_API_10307 */
              DEM_REPORT_ERROR(
                  DEM_PRESTOREFREEZEFRAME_SID, DEM_E_NODATAAVAILABLE);
            }
          }
        }
        /* @Trace: Dem_SUD_API_12297 */
        Dem_FreeLockByEventId(LddEvId);
      }
    }
  }
  return LddRetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_ClearPrestoredFreezeFrame                       **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : The API shall be called to delete or release        **
**                        the prestored FreezeFrame for specific EventId      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
**                        Dem_ClearPrestorePid()                              **
*******************************************************************************/
/* @Trace: SRS_Diag_04126 SRS_Diag_04165 SRS_BSW_00300
 */
#if (DEM_MAX_NUMBER_PRESTORED_FF > DEM_ZERO )
FUNC(Std_ReturnType, DEM_CODE)
Dem_ClearPrestoredFreezeFrame(Dem_EventIdType EventId)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  if (Dem_GucInit != DEM_INIT)
  {
    /* @Trace: Dem_SUD_API_11969 */
    DEM_REPORT_ERROR(DEM_CLEARPRESTOREDFREEZEFRAME_SID, DEM_E_UNINIT);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if ((EventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == EventId))
  {
    /* @Trace: Dem_SUD_API_10335 */
    DEM_REPORT_ERROR(DEM_CLEARPRESTOREDFREEZEFRAME_SID, DEM_E_PARAM_CONFIG);
    /* @LddRetVal = E_NOT_OK; */
  }
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  else if (DEM_TRUE !=
      Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE))
  {
    /* @Trace: SWS_Dem_01108
     * If an event is set to unavailable, the corresponding event shall
     * be treated as if it is not configured in the system (e.g.
     * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return E_NOT_OK). */
    /* @LddRetVal = E_NOT_OK; */
  }
  #endif
  else
  {
    /* @Trace: SWS_Dem_01250
     * For each DemMultiEventTriggeringSlaveEventRef of this
     * DemMultiEventTriggering the Dem shall trigger the same API calls with
     * identical parameters only the EventId parameter shall be replaced with
     * the event referenced from
     * DemMultiEventTriggeringSlaveEventRef.*/
    Dem_EventIdType LddEvId = EventId;
    uint8 LucStartIdx = DEM_ZERO;
    uint8 LucStopIdx = DEM_ONE;
    /* @Trace: Dem_SUD_API_11971 */
    #if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
    uint8 LucIdxOfMasterEvent = Dem_GetIndexOfMasterEventByEventId(LddEvId);
    boolean LblIdxOfMasterEventIsFound = DEM_FALSE;
    /* @Trace: Dem_SUD_API_11972 */
    if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING != LucIdxOfMasterEvent)
    {
      /* @Trace: Dem_SUD_API_11973 */
      LucStartIdx = Dem_DemMultiEventTrg[LucIdxOfMasterEvent].slaveEventIdx;
      LucStopIdx =
          LucStartIdx +
          Dem_DemMultiEventTrg[LucIdxOfMasterEvent].numberOfSlaveEvent;
      LblIdxOfMasterEventIsFound = DEM_TRUE;
    }
    #endif
    /* @Trace: Dem_SUD_API_11974 */
    /* Report status for all salve event related from master event id */
    for (; LucStartIdx < LucStopIdx; LucStartIdx++)
    {
      /* @Trace: Dem_SUD_API_11975 */
      #if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
      /* @Trace: Dem_SUD_API_11976 */
      if (DEM_TRUE == LblIdxOfMasterEventIsFound)
      {
        /* @Trace: Dem_SUD_API_11977 */
        LddEvId = Dem_ListOfSlaveEventTrg[LucStartIdx];
      }
      #endif

      #if (DEM_ZERO == DEM_MAX_NUMBER_PRESTORED_FF)
      /* @Trace: Dem_SUD_API_11978 */
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition evaluates to true or false according to configuration */
      DEM_REPORT_ERROR(DEM_CLEARPRESTOREDFREEZEFRAME_SID, DEM_E_PARAM_CONFIG);
      /* @LddRetVal = E_NOT_OK; */
      #else
      if (DEM_FALSE == Dem_GetLockByEventId(LddEvId))
      {
        /* @Trace: Dem_SUD_API_11970 */
        /* LddRetVal = E_NOT_OK; */
      }
      else
      {
        /* @Trace: Dem_SUD_API_10336 */
        LddRetVal = Dem_ClearSinglePrestoredFFbyEventId(LddEvId);
        Dem_FreeLockByEventId(LddEvId);
      }
      #endif
    }
  }
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_GetEventUdsStatus                               **
**                                                                            **
** Service ID           : 0xb6                                                **
**                                                                            **
** Description          : Gets the current UDS status byte assigned to        **
**                        the DTC for the event.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : UDSStatusByte                                       **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GaaEventAvailableBuffer                         **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
**                        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION()           **
*******************************************************************************/
/* @Trace: SRS_Diag_04067 SRS_Diag_04126 SRS_BSW_00300
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventUdsStatus(Dem_EventIdType EventId,
P2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA) UDSStatusByte)
{
  /* @Trace: SWS_Dem_00051
   * If the API Dem_GetEventUdsStatus is called, the Dem shall provide the
   * current event status byte of a specific event.
   */
  Std_ReturnType LddRetVal = E_NOT_OK;
  /* Check module initialization */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_11992 */
    DEM_REPORT_ERROR(DEM_GETEVENTUDSSTATUS_SID, DEM_E_UNINIT);
    /* LddRetVal = E_NOT_OK */
  }
  /* Check EventId does not exist */
  else if ((EventId > DEM_NUMBER_OF_EVENTS) || (EventId == DEM_NO_EVENT))
  {
    /* @Trace: Dem_SUD_API_11993 */
    DEM_REPORT_ERROR(DEM_GETEVENTUDSSTATUS_SID, DEM_E_WRONG_CONFIGURATION);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if (NULL_PTR == UDSStatusByte)
  {
    /* @Trace: Dem_SUD_API_11994 */
    DEM_REPORT_ERROR(DEM_GETEVENTUDSSTATUS_SID, DEM_E_PARAM_POINTER);
    /* @LddRetVal = E_NOT_OK; */
  }
  else
  /* @Trace: Dem_SUD_API_11995 */
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  /* @Trace: SWS_Dem_01277
   * If the API Dem_GetEventUdsStatus is called, the event from the parameter
   * EventId does not exists or is unavailable according to chapter subsection
   * 7.4.8, the Dem shall return E_NOT_OK. */

  /* @Trace: SWS_Dem_01108
   * If an event is set to unavailable, the corresponding event shall be treated
   * as if it is not configured in the system (e.g. Dem_SetEventStatus and
   * Dem_GetEventUdsStatus shall return E_NOT_OK). */

  if (DEM_TRUE ==
      Dem_EvIsProcStateTriggered(EventId,DEM_EVPROCSTATE_EVENT_AVAILABLE))
      /* @Trace: Dem_SUD_API_11997 */
  #endif
  {
    /* @Trace: SWS_Dem_01276
     * If the API Dem_GetEventUdsStatus is called, the event from the parameter
     * EventId exists and is available according to chapter subsection 7.4.8,
     * the Dem shall copy  the UDS status byte into the out parameter
     * UDSStatusByte and return E_OK. */
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    *UDSStatusByte = Dem_AllEventStatusByte[EventId];
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    LddRetVal = E_OK;
  }
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  else
  {
    /* @Trace: Dem_SUD_API_11996 */
    /* Nothing to do */
  }
  #endif
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_GetMonitorStatus                                **
**                                                                            **
** Service ID           : 0xb5                                                **
**                                                                            **
** Description          : Gets the current monitor status for an event.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : MonitorStatus                                       **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04031 SRS_Diag_04067 SRS_BSW_00300
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetMonitorStatus(
    Dem_EventIdType EventId,
    P2VAR(Dem_MonitorStatusType, AUTOMATIC, DEM_APPL_DATA) MonitorStatus)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  /* Check module initialization*/

  /* @Trace: SWS_Dem_01326
   * The monitor status shall be initialized within Dem_Init. Any call to
   * Dem_GetMonitorStatus shall return E_NOT_OK if the monitor status is
   * uninitialized. */
  if (DEM_DEINIT == Dem_GucInit)
  {
    /* LddRetVal = E_NOT_OK */
  }
  else if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_11999 */
    DEM_REPORT_ERROR(DEM_GETMONITORSTATUS_SID, DEM_E_UNINIT);
    /* LddRetVal = E_NOT_OK */
  }
  /* @Trace: SWS_Dem_01288
   * If the API Dem_GetMonitorStatus is called with an
   * invalid EventId the Dem shall return E_NOT_OK. */
  else if ((EventId > DEM_NUMBER_OF_EVENTS) || (EventId == DEM_NO_EVENT))
  {
    /* @Trace: Dem_SUD_API_12000 */
    DEM_REPORT_ERROR(DEM_GETMONITORSTATUS_SID, DEM_E_WRONG_CONFIGURATION);
    /* @LddRetVal = E_NOT_OK; */
  }

  else if (NULL_PTR == MonitorStatus)
  {
    /* @Trace: Dem_SUD_API_11998 */
    DEM_REPORT_ERROR(DEM_GETMONITORSTATUS_SID, DEM_E_PARAM_POINTER);
    /* @LddRetVal = E_NOT_OK; */
  }
  else
  {
    /* @Trace: Dem_SUD_API_10337 */
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    /* @Trace: SWS_Dem_01287
     * If the API Dem_GetMonitorStatus is called, the Dem shall copy the current
     * monitor status into the out parameter MonitorStatus and return E_OK. */
    *MonitorStatus = Dem_AllMonitorStatus[EventId];
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    LddRetVal = E_OK;
  }
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_GetDebouncingOfEvent                            **
**                                                                            **
** Service ID           : 0x9f                                                **
**                                                                            **
** Description          : Gets the debouncing status of an event.             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_DebouncingStateType* DebouncingState            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GaaDebouncingCompleteBuffer                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_Diag_04068 SRS_Diag_04126 SRS_BSW_00300
 */
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetDebouncingOfEvent(Dem_EventIdType EventId,
P2VAR (Dem_DebouncingStateType, AUTOMATIC, DEM_APPL_DATA) DebouncingState)
{
  /* @Trace: SWS_Dem_00844
   * The Dem shall provide a function Dem_GetDebouncingOfEvent () that reports
   * the debounce status of an event. The outparameter �DebouncingState� returns
   * the debouncing incl. intermediate states. One particular OBD specific bit
   * shall support the DTR update trigger if test is complete and debouncing is
   * at its limit while the enable and storage conditions are met.
   */
  Std_ReturnType LddRetVal = E_NOT_OK;
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_10308 */
    DEM_REPORT_ERROR(DEM_GETDEBOUNCINGOFEVENT_SID, DEM_E_UNINIT);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if (DEM_FALSE == Dem_EventIdIsValid(EventId))
  {
    /* @Trace: Dem_SUD_API_10309 */
    DEM_REPORT_ERROR(DEM_GETDEBOUNCINGOFEVENT_SID, DEM_E_PARAM_CONFIG);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if (NULL_PTR == DebouncingState)
  {
    /* @Trace: Dem_SUD_API_10310 */
    DEM_REPORT_ERROR(DEM_GETDEBOUNCINGOFEVENT_SID, DEM_E_PARAM_POINTER);
    /* @LddRetVal = E_NOT_OK; */
  }
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  else if ( DEM_TRUE !=
      Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE))
  {
    /* @Trace: Dem_SUD_API_12001 */
    /* @Trace: SWS_Dem_01108
     * If an event is set to unavailable, the corresponding event shall
     * be treated as if it is not configured in the system (e.g.
     * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return E_NOT_OK). */
    /* LddRetVal = E_NOT_OK; */
  }
  #endif
  else
  {
    sint8 LscFDC = (sint8)0x00;
    *DebouncingState = DEM_ZERO;
    /* @Trace: Dem_SUD_API_12012 */
    /* If event don't support FDC , FDC is zero, so 'result' is no-ok  */
    if (E_OK == Dem_GetFaultDetectionCounter(EventId, &LscFDC))
    {
      /* @Trace: Dem_SUD_API_12023 */
      if ((LscFDC > 0) && (LscFDC < 127))
      {
        /* @Trace: Dem_SUD_API_12031 */
        *DebouncingState |= (Dem_DebouncingStateType)DEM_TEMPORARILY_DEFECTIVE;
      }
      /* @Trace: Dem_SUD_API_12033 */
      if (LscFDC == 127)
      {
        /* @Trace: Dem_SUD_API_12032 */
        *DebouncingState |= (Dem_DebouncingStateType)DEM_FINALLY_DEFECTIVE;
      }
      /* @Trace: Dem_SUD_API_12035 */
      if ((LscFDC > -128) && (LscFDC < 0))
      {
        /* @Trace: Dem_SUD_API_12034 */
        *DebouncingState |= (Dem_DebouncingStateType)DEM_TEMPORARILY_HEALED;
      }
      /* @Trace: Dem_SUD_API_12002 */
      if ((LscFDC == 127) || (LscFDC == -128))
      {
        /* @Trace: Dem_SUD_API_12036 */
        *DebouncingState |= (Dem_DebouncingStateType)DEM_TEST_COMPLETE;
      }

      Std_ReturnType LddResult = E_NOT_OK;
      Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
      uint8 LucDebounceType =
          DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(LddEvent->ParamFieldsA);
          /* @Trace: Dem_SUD_API_12006 */
      if ((DEM_DEBOUNCE_COUNTER_BASED == LucDebounceType) ||
          (DEM_DEBOUNCE_TIME_BASED == LucDebounceType))
      {
        #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
        /* @Trace: Dem_SUD_API_12005 */
        if (DEM_DEBOUNCE_COUNTER_BASED == LucDebounceType)
        {
          /* @Trace: Dem_SUD_API_12004 */
          if (LddEvent->ucIndexOfDebounceAry <
                DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER)
          {
            P2CONST(Dem_PreDebounceCounterType, AUTOMATIC, DEM_CONST) LddDcb =
                &Dem_GaaPreDebounceCounter[LddEvent->ucIndexOfDebounceAry];
            /* (+) value */
            const sint16 LssMaxFDC = LddDcb->ssDemCounterFailedThreshold;
            /* (-) value */
            const sint16 LssMinFDC = LddDcb->ssDemCounterPassedThreshold;
            /* @Trace: Dem_SUD_API_12007 */
            if ((LssMaxFDC ==
                   Dem_GssTempCounter[LddEvent->ucIndexOfDebounceAry]) ||
                (LssMinFDC ==
                   Dem_GssTempCounter[LddEvent->ucIndexOfDebounceAry]))
            {
              /* @Trace: Dem_SUD_API_12003 */
              LddResult = E_OK;
            }
          }
        }
        #endif
        #if ((DEM_DEBOUNCE_TIME_SUPPORT == STD_ON))
        /* @Trace: Dem_SUD_API_12008 */
        if (DEM_DEBOUNCE_TIME_BASED == LucDebounceType)
        {
          P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) LddTimerStatus =
              NULL_PTR;
          LddTimerStatus =
              Dem_GetDebounceTimerStatus(LddEvent->ucIndexOfDebounceAry);
              /* @Trace: Dem_SUD_API_12009 */
          if (NULL_PTR != LddTimerStatus)
          {
            /* @Trace: Dem_SUD_API_12010 */
            if ((DEM_EVENT_STATUS_UNDEFINED !=
                   LddTimerStatus->tds_EventStatus) &&
                (DEM_ZERO == LddTimerStatus->tds_Counter))
            {
              /* @Trace: Dem_SUD_API_12011 */
              LddResult = E_OK;
            }
          }
        }
        #endif
      }
      /* @Trace: Dem_SUD_API_12013 */
      if (E_OK == LddResult)
      {
        LddResult = E_NOT_OK;
        #if (DEM_ENABLE_CONDITION_SUPPORT == STD_ON)
        /* @Trace: Dem_SUD_API_12014 */
        if (DEM_ZERO != LddEvent->ucNumOfEnableCondition)
        {
          const uint16 LusNumOfCond =
              LddEvent->PointToEnableConditionMap +
              LddEvent->ucNumOfEnableCondition;

          /* Check the status of all enable conditions configured for the event
           */
          /* @Trace: Dem_SUD_API_12015 */
          if (LusNumOfCond <= DEM_MAX_LISTOFENABLECONDITIONID)
          /* polyspace<RTE:UNR:Not a defect:No action planned>
           * If-condition evaluates to true or false according to configuration
           */
          {
            uint16 LusIdx = DEM_ZERO;
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            /* @Trace: Dem_SUD_API_12016 */
            for (LusIdx = LddEvent->PointToEnableConditionMap;
                 LusIdx < LusNumOfCond;
                 LusIdx++)
            {
              if ((boolean)DEM_FALSE == Dem_GetEnableConditionStatus(LusIdx))
              {
                /* @Trace: Dem_SUD_API_12017 */
                break;
              }
            }
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
            /* @Trace: Dem_SUD_API_12018 */
            if (LusNumOfCond == LusIdx)
            {
              /* @Trace: Dem_SUD_API_12019 */
              LddResult = E_OK;
            }
          }
        }
        #endif
        /* @Trace: Dem_SUD_API_12020 */
        if (E_OK != LddResult)
        {
          #if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
          const uint16 LusNumOfCond =
              LddEvent->PointToStorageConditionMap +
              LddEvent->ucNumOfStorageCondition;
              /* @Trace: Dem_SUD_API_12021 */
          if (LusNumOfCond <= DEM_MAX_LISTOFSTORAGECONDITIONID)
          {
            uint16 LusIdx = DEM_ZERO;
            /* Check the status of all enable conditions configured for the
             * event by SW-C*/
            /* @Trace: Dem_SUD_API_12022 */
            for (LusIdx = LddEvent->PointToStorageConditionMap;
                 LusIdx < LusNumOfCond ;
                 LusIdx++)
            {
              /* @Trace: Dem_SUD_API_12024 */
              /* enable storage == all condition is true */
              if ((boolean)DEM_FALSE == Dem_GetStorageConditionStatus(LusIdx))
              {
                /* @Trace: Dem_SUD_API_12025 */
                break;
              }
            }
              /* @Trace: Dem_SUD_API_12026 */
            if (LusNumOfCond == LusIdx)
            {
              /* @Trace: Dem_SUD_API_12027 */
              LddResult = E_OK;
            }
          }
          #endif
        }
      }
      /* @Trace: Dem_SUD_API_12028 */
      if ((((*DebouncingState & DEM_TEST_COMPLETE) == DEM_TEST_COMPLETE) &&
            (E_NOT_OK != LddResult)))
      {
        /* @Trace: Dem_SUD_API_12029 */
        *DebouncingState |= (Dem_DebouncingStateType)DEM_DTR_UPDATE;
      }
      /* @Trace: Dem_SUD_API_12030 */
      if (DEM_ZERO != *DebouncingState)
      {
        /* @Trace: Dem_SUD_API_10320 */
        LddRetVal = E_OK;
      }
    }
  }
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_GetDTCOfEvent                                   **
**                                                                            **
** Service ID           : 0x0D                                                **
**                                                                            **
** Description          : Gets the DTC which is mapped to EventId by          **
**                        DEM Configuration                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId,                            **
**                        Dem_DTCFormatType DTCFormat                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint32 *DTCOfEvent,                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_Diag_04126 SRS_Diag_04201 SRS_BSW_00300 SRS_Diag_04000
           SRS_Diag_04075
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCOfEvent(
  Dem_EventIdType EventId, 
  Dem_DTCFormatType DTCFormat,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTCOfEvent)
{
  /* @Trace: SWS_Dem_00269
   * The function Dem_GetDTCOfEvent shall get the DTC which is mapped to EventId
   * by the Dem configuration.
   */
  Std_ReturnType LddRetVal = DEM_E_NO_DTC_AVAILABLE;

  /* Module initialization check */
  if (Dem_GucInit != DEM_INIT)
  {
    /* @Trace: Dem_SUD_API_12037 */
    DEM_REPORT_ERROR(DEM_GETDTCOFEVENT_SID, DEM_E_UNINIT);
    LddRetVal = E_NOT_OK;
  }
  else if (DTCOfEvent == NULL_PTR)
  {
    /* @Trace: Dem_SUD_API_12038 */
    DEM_REPORT_ERROR(DEM_GETDTCOFEVENT_SID, DEM_E_PARAM_POINTER);
    LddRetVal = E_NOT_OK;
  }
  else if ((EventId == DEM_NO_EVENT) || (EventId > DEM_NUMBER_OF_EVENTS))
  {
    /* @Trace: Dem_SUD_API_10321 */
    DEM_REPORT_ERROR(DEM_GETDTCOFEVENT_SID, DEM_E_PARAM_CONFIG);
    LddRetVal = E_NOT_OK;
  }
  /* @Trace: Dem_SUD_API_12039 */
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  /* @Trace: Dem_SUD_API_12041 */
  else if ( DEM_TRUE !=
      Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE))

  {
    /* @Trace: Dem_SUD_API_12040 */
    /* @Trace: SWS_Dem_01108
     * If an event is set to unavailable, the corresponding event shall
     * be treated as if it is not configured in the system (e.g.
     * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return E_NOT_OK). */
    LddRetVal = E_NOT_OK;
  }
  #endif
  else if ((DTCFormat != DEM_DTC_FORMAT_OBD) &&
          #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
            /* Trace: DEM_19792_42_04 */
          (DTCFormat != DEM_DTC_FORMAT_OBD_3BYTE) &&
          #endif /* (DEM_J1979_2_OBD_ON_UDS == STD_ON) */
          (DTCFormat != DEM_DTC_FORMAT_UDS))
  {
    /* @Trace: Dem_SUD_API_12042 */
    DEM_REPORT_ERROR(DEM_GETDTCOFEVENT_SID, DEM_E_PARAM_CONFIG);
    LddRetVal = E_NOT_OK;
  }
  else
  {  
    /* @Trace: Dem_SUD_API_10322 */
    if (DEM_FALSE ==
          Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_DTC_SUPP))
    {
      /* @Trace: Dem_SUD_API_12043 */
      if (DEM_TRUE == Dem_DTCFormatIsValid(EventId, DTCFormat))
      {
        /* @Trace: Dem_SUD_API_12044 */
        LddRetVal =
            Dem_GetEventDTC(
                &Dem_Event[EventId - DEM_ONE], DTCOfEvent, DTCFormat);
      }
    }
  }
  
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_GetIndicatorStatus                              **
**                                                                            **
** Service ID           : 0x29                                                **
**                                                                            **
** Description          : This function shall be used to read the             **
**                        indicator-Status derived from the event status      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint8 IndicatorId                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_IndicatorStatusType* IndicatorStatus            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace:begin<MISRA-C:5.6:Not a defect:Justify with annotations>
 * Depends on Dem specfication */

/* @Trace: SRS_Diag_04069 SRS_Diag_04141 SRS_BSW_00300
 */
/* polyspace +2 MISRA-C3:5.8 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetIndicatorStatus(uint8 IndicatorId,
  P2VAR (Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA) IndicatorStatus)
{
  /* @Trace: SWS_Dem_00046
   * The Dem module shall provide the API Dem_GetIndicatorStatus that a software
   * component can get information about the calculated indicator status.
   */
  (void) IndicatorId;
  (void) IndicatorStatus;
  Std_ReturnType LddRetVal = E_NOT_OK;
  
  if (Dem_GucInit != DEM_INIT)
  {
    /* @Trace: Dem_SUD_API_12066 */
    DEM_REPORT_ERROR(DEM_GETINDICATORSTATUS_SID, DEM_E_UNINIT);
    /* @LddRetVal = E_NOT_OK;*/
  }
  else if ( IndicatorStatus == NULL_PTR )
  {
    /* @Trace: Dem_SUD_API_12077 */
    DEM_REPORT_ERROR(DEM_GETINDICATORSTATUS_SID, DEM_E_PARAM_POINTER);
    /* @LddRetVal = E_NOT_OK;*/
  }
  /* @Trace: Dem_SUD_MACRO_083 */
  #if (DEM_NUMBER_OF_INDICATORS > DEM_ZERO)
  /* @Trace: Dem_SUD_MACRO_114 */
  else if ( IndicatorId >= DEM_NUM_OF_INDICATORID )
  {
    /* @Trace: Dem_SUD_API_12084 */
    DEM_REPORT_ERROR(DEM_GETINDICATORSTATUS_SID, DEM_E_PARAM_DATA);
    /* @LddRetVal = E_NOT_OK;*/
  }
  #endif
  else
  {
    /* @Trace: SWS_Dem_01166
     * The function Dem_GetIndicatorStatus shall return the current
     * "indicator status"(refer to Table 7.5) of those events referenced by the
     * DemMILIndicatorRef. The conditions for the activation modes are defined
     * in Table 7.5.*/
    *IndicatorStatus = DEM_INDICATOR_OFF;
    /* @Trace: Dem_SUD_API_12085 */
    #if (DEM_NUMBER_OF_INDICATORS > DEM_ZERO)
    {
      Dem_NumOfIndicatorAttributeType *LddBehavior =
          Dem_IndicatorBehaviorAccumulator[IndicatorId];
      /* @Trace: Dem_SUD_API_12087 */
      if (DEM_ZERO != LddBehavior[DEM_INDICATOR_CONTINUOUS])
      {
        /* @Trace: Dem_SUD_API_12086 */
        *IndicatorStatus |= (Dem_IndicatorStatusType)DEM_INDICATOR_CONTINUOUS;
      }
      /* @Trace: Dem_SUD_API_12088 */
      if (DEM_ZERO !=LddBehavior[DEM_INDICATOR_BLINKING])
      {
        /* @Trace: Dem_SUD_API_12089 */
        *IndicatorStatus |= (Dem_IndicatorStatusType)DEM_INDICATOR_BLINKING;
      }
      /* @Trace: Dem_SUD_API_12067 */
      if (DEM_ZERO != LddBehavior[DEM_INDICATOR_BLINK_CONT])
      {
        /* @Trace: Dem_SUD_API_12090 */
        *IndicatorStatus |= (Dem_IndicatorStatusType)DEM_INDICATOR_BLINK_CONT;
      }    
      /* @Trace: Dem_SUD_API_12072 */
      #if (DEM_J1939_SUPPORT == STD_ON)
      /* @Trace: Dem_SUD_API_12070 */
      if (DEM_ZERO != LddBehavior[DEM_INDICATOR_SLOW_FLASH])
      {
        /* @Trace: Dem_SUD_API_12068 */
        *IndicatorStatus |= (Dem_IndicatorStatusType)DEM_INDICATOR_SLOW_FLASH;
      }
      /* @Trace: Dem_SUD_API_12071 */
      if (DEM_ZERO != LddBehavior[DEM_INDICATOR_FAST_FLASH])
      {
        /* @Trace: Dem_SUD_API_12069 */
        *IndicatorStatus |= (Dem_IndicatorStatusType)DEM_INDICATOR_FAST_FLASH;
      }    
      #endif
      /* @Trace: Dem_SUD_API_12073 */
      #if defined(DEM_INDICATOR_ON_DEMAND)
      /* @Trace: Dem_SUD_API_12074 */
      if (DEM_ZERO != LddBehavior[DEM_INDICATOR_ON_DEMAND])
      {
        /* @Trace: Dem_SUD_API_10311 */
        *IndicatorStatus |= (Dem_IndicatorStatusType)DEM_INDICATOR_ON_DEMAND;
      }
      /* @Trace: Dem_SUD_API_12075 */
      if (DEM_ZERO != LddBehavior[DEM_INDICATOR_SHORT])
      {
        /* @Trace: Dem_SUD_API_10312 */
        *IndicatorStatus |= (Dem_IndicatorStatusType)DEM_INDICATOR_SHORT;
      }    
      #endif
      /* @Trace: Dem_SUD_API_12083 */
      for (uint8 LucIdx = DEM_ZERO;
                 LucIdx < DEM_MAX_NUMBER_MEMORY_SET;
                 LucIdx++)
      {
        /* @Trace: Dem_SUD_API_12082 */
        #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        uint8 LucDemMilIndicator = Dem_EvMem_GetMILIndicator(LucIdx);
        /* @Trace: Dem_SUD_API_12081 */
        if (LucDemMilIndicator == IndicatorId)
        {
          if (DEM_WWHOBD_ACTIVATION_MODE_4 == Dem_WWHOBDActMode)
          {
            /* @Trace: Dem_SUD_API_12076 */
            *IndicatorStatus |=
                (Dem_IndicatorStatusType)DEM_INDICATOR_CONTINUOUS;
          }
          else if (DEM_WWHOBD_ACTIVATION_MODE_3 == Dem_WWHOBDActMode)
          {
            /* @Trace: Dem_SUD_API_12078 */
            *IndicatorStatus |=
                (Dem_IndicatorStatusType)DEM_INDICATOR_SHORT;
          }
          else if (DEM_WWHOBD_ACTIVATION_MODE_2 == Dem_WWHOBDActMode)
          {
            /* @Trace: Dem_SUD_API_12079 */
            *IndicatorStatus |=
                (Dem_IndicatorStatusType)DEM_INDICATOR_ON_DEMAND;
          }
          else if (DEM_WWHOBD_ACTIVATION_MODE_1 == Dem_WWHOBDActMode)
          {
            /* @Trace: Dem_SUD_API_12080 */
            *IndicatorStatus |=
                (Dem_IndicatorStatusType)DEM_INDICATOR_OFF;
          }
          else
          {
            /* Nothing to do */
          }
        }
        #endif
      }
    }
    #endif  
    
    LddRetVal = E_OK;
  }
  
  return LddRetVal;
}
/* polyspace:end<MISRA-C:5.6:Not a defect:Justify with annotations>
 * Depends on Dem specfication */

/*******************************************************************************
** Function Name        : Dem_SetEnableCondition                              **
**                                                                            **
** Service ID           : 0x39                                                **
**                                                                            **
** Description          : This function shall set the EnableCondition         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EnableConditionID, ConditionFulfilled               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
**                        SchM_Exit_Dem_REQUEST_DATA_PROTECTION()             **
*******************************************************************************/
/* @Trace: SRS_BSW_00101 SRS_BSW_00310 SRS_Diag_04125 SRS_Diag_04192
           SRS_BSW_00300
 */
#if (DEM_ENABLE_CONDITION_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEnableCondition(
  uint8 EnableConditionID,
  boolean ConditionFulfilled)
{
  /* @Trace: SWS_Dem_00202
   * If the Dem module is requested to support enable conditions, the Dem module
   * shall provide the API Dem_SetEnableCondition receiving the current status
   * (condition fulfilled or not) of a specific enable condition.
   */
  Std_ReturnType LddRetVal = E_NOT_OK;

  /* Check if the Dem module is not initialized */
  if (Dem_GucInit != DEM_INIT)
  {
    /* @Trace: Dem_SUD_API_12340 */
    DEM_REPORT_ERROR(DEM_SETENABLECONDITION_SID, DEM_E_UNINIT);
    /* @LddRetVal = E_NOT_OK;*/
  }
  else if ((ConditionFulfilled != DEM_TRUE) &&
           (ConditionFulfilled != DEM_FALSE))
  {
    /* @Trace: Dem_SUD_API_12344 */
    DEM_REPORT_ERROR(DEM_SETENABLECONDITION_SID, DEM_E_PARAM_DATA);
    /* @LddRetVal = E_NOT_OK;*/
  }
  else
  {   
    if (EnableConditionID < DEM_NUMBER_ENABLE_CONDITION)
    {
      /* @Trace: Dem_SUD_API_12346 */
      /* @Trace: Dem_SUD_MACRO_070 */
      #if ((DEM_MAX_LISTOFENABLECONDITIONID > DEM_ZERO) && \
           (DEM_NUMBER_ENABLE_CONDITION > DEM_ZERO))
           /* @Trace: Dem_SUD_API_12347 */
      boolean LblOldConditionFulfilled =
          Dem_EnableConditionStatus[EnableConditionID];
      #endif
      SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
      Dem_SetEnableConditionStatus(EnableConditionID, ConditionFulfilled);
      SchM_Exit_Dem_REQUEST_DATA_PROTECTION();

      /* @Trace: SWS_Dem_00681
       * The API Dem_SetEnableCondition shall trigger the callback function
       * InitMonitorForEvent of the related event(s) in case an enable condition
       * of the event(s) is changed to fulfilled and thus all enable conditions
       * of the event(s) are fulfilled. The InitMonitorReason parameter shall be
       * set to DEM_INIT_MONITOR_REENABLED.
       * */
      /* Call Callback for initialization of monitor for a event */
      /* @Trace: Dem_SUD_API_12348 */
      #if ((DEM_MAX_LISTOFENABLECONDITIONID > DEM_ZERO) && \
           (DEM_NUMBER_ENABLE_CONDITION > DEM_ZERO))
      /* @Trace: Dem_SUD_API_12349 */
      if ((DEM_TRUE == ConditionFulfilled) &&
          (LblOldConditionFulfilled != ConditionFulfilled))
      {
        /* @Trace: Dem_SUD_API_12350 */
        for (Dem_EventIdType LddEventId = DEM_ONE;
                             LddEventId <= DEM_NUMBER_OF_EVENTS;
                             LddEventId++)
        {
          Dem_EventParameterPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
          uint8 LucNumOfEnCond = LddEvent->ucNumOfEnableCondition;
          uint16 LusIdx = LddEvent->PointToEnableConditionMap;
          boolean LblIsFound = DEM_FALSE;
          /* @Trace: Dem_SUD_API_12351 */
          for (; LusIdx < LucNumOfEnCond; LusIdx++)
          {
            /* @Trace: Dem_SUD_API_12341 */
            /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
            if (EnableConditionID == Dem_ListOfEnableConditionId[LusIdx])
            {
              LblIsFound = DEM_TRUE;
              break;
            }
          }
          /* @Trace: SWS_Dem_00256
           */
          /* @Trace: Dem_SUD_API_12342 */
          if ((DEM_TRUE == LblIsFound) &&
              (NULL_PTR != LddEvent->pDemInitMonitorForEvent))
          {
            /* @Trace: Dem_SUD_API_12343 */
            /*Return value unused - only for compatibility with according RTE
             * operation.*/
            /* polyspace<RTE: COR : Not a defect : No Action Planned >
             * function ptr points to a valid function */
            (void)LddEvent->pDemInitMonitorForEvent(
                (Dem_InitMonitorReasonType)DEM_INIT_MONITOR_REENABLED);
          }
        }
      }
      #endif
      LddRetVal = E_OK;
    }
    else
    {
      /* @Trace: Dem_SUD_API_12345 */
      DEM_REPORT_ERROR(DEM_SETENABLECONDITION_SID, DEM_E_PARAM_CONFIG);
      /* @LddRetVal = E_NOT_OK; */
    }
  }
  
  return LddRetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_SetStorageCondition                             **
**                                                                            **
** Service ID           : 0x38                                                **
**                                                                            **
** Description          : This function shall set the StorageCondition        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : StorageConditionID, ConditionFulfilled              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_BSW_00101 SRS_BSW_00310 SRS_Diag_04095 SRS_Diag_04219
           SRS_BSW_00300
 */
#if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetStorageCondition(
  uint8 StorageConditionID,
  boolean ConditionFulfilled)
{
  /* @Trace: SWS_Dem_00543
   * If the Dem module is requested to support storage conditions, the Dem
   * module shall provide the API Dem_SetStorageCondition receiving the current
   * status (condition fulfilled or not) of a specific storage condition.
   */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if (Dem_GucInit != DEM_INIT)
  {
    /* @Trace: Dem_SUD_API_12521 */
    DEM_REPORT_ERROR(DEM_SETSTORAGECONDITION_SID, DEM_E_UNINIT);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if ((ConditionFulfilled != DEM_TRUE) &&
           (ConditionFulfilled != DEM_FALSE))
  {
    /* @Trace: Dem_SUD_API_12529 */
    DEM_REPORT_ERROR(DEM_SETSTORAGECONDITION_SID, DEM_E_PARAM_DATA);
    /* @LddRetVal = E_NOT_OK; */
  }
  else
  {
    if (StorageConditionID < DEM_NUMBER_STORAGE_CONDITION)
    {
      /* Set the condition for StorageConditionID */
      SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
      /* @Trace: Dem_SUD_API_12531 */
      /* @Trace: Dem_SUD_MACRO_073 */
      #if (DEM_MAX_LISTOFSTORAGECONDITIONID > DEM_ZERO)
      /* @Trace: Dem_SUD_API_12532 */
      boolean LblOldConditionFulfilled =
          Dem_GaaStorageConditionStatus[StorageConditionID];
      #endif
      Dem_SetStorageConditionStatus(StorageConditionID, ConditionFulfilled);
      SchM_Exit_Dem_REQUEST_DATA_PROTECTION();

      /* @Trace: SWS_Dem_01113
       * The API Dem_SetStorageCondition shall trigger the callback function
       * InitMonitorForEvent of the related event(s) in case a storage condition
       * of the event(s) is changed to fulfilled and thus all storage conditions
       * of the event(s) are fulfilled. Furthermore the callback shall only be
       * called, if the event did report FAILED or PASSED while the storage
       * condition was disabled. The InitMonitorReason parameter shall be set to
       * DEM_INIT_MONITOR_REENABLED.
       * */
      /* Call Callback for initialization of monitor for a event */
      /* @Trace: Dem_SUD_API_12533 */
      #if (DEM_MAX_LISTOFSTORAGECONDITIONID > DEM_ZERO)
      /* @Trace: Dem_SUD_API_12534 */
      if ((DEM_TRUE == ConditionFulfilled) &&
          (LblOldConditionFulfilled != ConditionFulfilled))
      {
        /* @Trace: Dem_SUD_API_12535 */
        for (Dem_EventIdType LddEventId = DEM_ONE;
                             LddEventId <= DEM_NUMBER_OF_EVENTS;
                             LddEventId++)
        {
          Dem_EventParameterPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];

          boolean LblIsFound = DEM_FALSE;
          boolean LblIsAllFound = DEM_TRUE;
          uint8 LucNumOfStgCond = LddEvent->ucNumOfStorageCondition;
          uint16 LusIdx = LddEvent->PointToStorageConditionMap;
          /* @Trace: Dem_SUD_API_12536 */
          for (; LusIdx < LucNumOfStgCond; LusIdx++)
          {
            /* @Trace: Dem_SUD_API_12523 */
            if (StorageConditionID == Dem_ListOfStorageConditionId[LusIdx])
            {
              /* @Trace: Dem_SUD_API_12522 */
              LblIsFound = DEM_TRUE;
              break;
            }
          }
          /* @Trace: Dem_SUD_API_12524 */
          /* All storage conditions of the event(s) are fulfilled*/
          if (DEM_TRUE == LblIsFound)
          {
            LusIdx = LddEvent->PointToStorageConditionMap;
            /* @Trace: Dem_SUD_API_12525 */
            for (; LusIdx < LucNumOfStgCond; LusIdx++)
            {
              
            /* @Trace: Dem_SUD_API_12526 */
              if (DEM_FALSE == Dem_GaaStorageConditionStatus[LusIdx])
              {
                
            /* @Trace: Dem_SUD_API_10313 */
                LblIsAllFound = DEM_FALSE;
                break;
              }
            }
          }

          /* @Trace: SWS_Dem_01113
           * The API Dem_SetStorageCondition shall trigger the callback function
           * InitMonitorForEvent of the related event(s) in case a storage
           * condition of the event(s) is changed to fulfilled and thus all
           * storage conditions of the event(s) are fulfilled. Furthermore the
           * callback shall only be called, if the event did report FAILED or
           * PASSED while the storage condition was disabled. The
           * InitMonitorReason parameter shall be set to
           * DEM_INIT_MONITOR_REENABLED.
           */
          /* @Trace: SWS_Dem_00256
           */
          
            /* @Trace: Dem_SUD_API_12527 */
          if ((DEM_TRUE == LblIsAllFound) &&
              (NULL_PTR != LddEvent->pDemInitMonitorForEvent))
          {
            /*Return value unused - only for compatibility with according RTE
             * operation.*/
            /* polyspace<RTE: COR : Not a defect : No Action Planned >
             * function ptr points to a valid function */
            
            /* @Trace: Dem_SUD_API_12528 */
            (void)LddEvent->pDemInitMonitorForEvent(
                (Dem_InitMonitorReasonType)DEM_INIT_MONITOR_REENABLED);
          }
        }
      }
      #endif

      LddRetVal = E_OK;
    }
    else
    {
      /* @Trace: Dem_SUD_API_12530 */
      DEM_REPORT_ERROR(DEM_SETSTORAGECONDITION_SID, DEM_E_PARAM_CONFIG);
      /* @LddRetVal = E_NOT_OK; */
    }
  }
  
  return LddRetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_GetFaultDetectionCounter                        **
**                                                                            **
** Service ID           : 0x3E                                                **
**                                                                            **
** Description          : Gets the FaultDetectionCounter value of an event    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : sint8* FaultDetectionCounter                        **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_Diag_04010 SRS_Diag_04068 SRS_Diag_04126 SRS_BSW_00300
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetFaultDetectionCounter(
  Dem_EventIdType EventId,
  P2VAR (sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter)
{
  /* @Trace: SWS_Dem_00204
   * The event-specific fault detection counter shall be accessible by using the
   * API Dem_GetFaultDetectionCounter.
   */
  Std_ReturnType LddRetVal = E_NOT_OK;
  
  /* Check if the Dem module is not initialized */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12053 */
    DEM_REPORT_ERROR(DEM_GETFAULTDETECTIONCOUNTER_SID, DEM_E_UNINIT);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if ((DEM_NO_EVENT == EventId) || (EventId > DEM_NUMBER_OF_EVENTS))
  {
    /* @Trace: Dem_SUD_API_12058 */
    DEM_REPORT_ERROR(DEM_GETFAULTDETECTIONCOUNTER_SID, DEM_E_PARAM_CONFIG);
    /* @LddRetVal = E_NOT_OK; */
  }
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  else if ( DEM_TRUE !=
      Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE))
  {
    /* @Trace: Dem_SUD_API_12059 */
    /* @Trace: SWS_Dem_01108
     * If an event is set to unavailable, the corresponding event shall
     * be treated as if it is not configured in the system (e.g.
     * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return E_NOT_OK). */

    /* @LddRetVal = E_NOT_OK; */
  }
  #endif
  else if (NULL_PTR == FaultDetectionCounter)
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * Above If-condition always evaluates to true . configuration error  */
  {
    /* @Trace: Dem_SUD_API_12530 */
    DEM_REPORT_ERROR(DEM_GETFAULTDETECTIONCOUNTER_SID, DEM_E_PARAM_POINTER);
    /* @LddRetVal = E_NOT_OK; */
  }
  else
  {
    /* @Trace: Dem_SUD_API_12060
     * The Dem module shall calculate the fault detection counter
     * (-128 ... +127 according to UDS) based on the value and range of the
     * internal debounce counter to map the internal counter values linearly
     * to the external values*/
    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    /* @Trace: Dem_SUD_MACRO_004 */
    #if ((DEM_DEBOUNCE_COUNTER_SUPPORT == STD_ON) || \
         (DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL > DEM_ZERO))
    Dem_NumOfDebounceType LddDebounceId = LddEvent->ucIndexOfDebounceAry;
    #endif
    
    switch(DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(LddEvent->ParamFieldsA))
    {
      /* Debounce Counter Based */
      #if (DEM_DEBOUNCE_COUNTER_SUPPORT == STD_ON)
      case DEM_DEBOUNCE_COUNTER_BASED:
        /* polyspace<RTE:UNR:Not a defect:No action planned>
         * If-condition always evaluates to true  */
        /* @Trace: Dem_SUD_MACRO_084 */
        #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
        /* @Trace: Dem_SUD_API_10327 */
        if (LddDebounceId < DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER)
        { 
          P2CONST(Dem_PreDebounceCounterType, AUTOMATIC, DEM_CONST) 
          LddDcb = &Dem_GaaPreDebounceCounter[LddDebounceId];
          if ( Dem_GssTempCounter[LddDebounceId] > 0)
          {
            if (Dem_GssTempCounter[LddDebounceId] > \
                  LddDcb->ssDemCounterFailedThreshold)
            {
              /* @Trace: Dem_SUD_API_10329 */
              DEM_REPORT_ERROR(
                  DEM_GETFAULTDETECTIONCOUNTER_SID, DEM_E_OUT_OF_BOUNDS);
            }
            else
            {
              /* @Trace: Dem_SUD_API_12054 */
              /* fomula : LscFDC = 127 * (counter value * FDC threshold) */
              /* polyspace<RTE:OVFL:Not a defect:No action planned> to avoid
               * floating point math */
              *FaultDetectionCounter = (Dem_FaultDetectionCounterType)
               (((sint32)Dem_GssTempCounter[LddDebounceId] *
                 (sint32)DEM_COUNTER_MAX)/
                   LddDcb->ssDemCounterFailedThreshold); /* (+) value */
            }
          }
          else
          {
            if (Dem_GssTempCounter[LddDebounceId] <
                  LddDcb->ssDemCounterPassedThreshold)
            /* polyspace<RTE:UNR:Not a defect:No action planned>
             * If-condition always evaluates to false  */
            {
              /* @Trace: Dem_SUD_API_12057 */
              DEM_REPORT_ERROR(
                  DEM_GETFAULTDETECTIONCOUNTER_SID, DEM_E_OUT_OF_BOUNDS);
            }
            else
            {
              /* fomula : LscFDC = -128 * (counter value / FDC threshold) */
              /* polyspace<RTE:OVFL:Not a defect:No action planned>
               * to avoid floating point math */
              /* @Trace: Dem_SUD_API_12056 */
              /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
              if ((sint16)0 != LddDcb->ssDemCounterPassedThreshold)
              {
                /* @Trace: Dem_SUD_API_12055 */
                *FaultDetectionCounter = (Dem_FaultDetectionCounterType)
                  (((sint32)Dem_GssTempCounter
                      [LddDebounceId] * DEM_COUNTER_MIN) /
                  LddDcb->ssDemCounterPassedThreshold); /* (-) value */
              }
            }
          }
          LddRetVal = E_OK;
        }
        #endif
      break;
      #endif
    
      /* Debounce Time Based */
      #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON) 
      case DEM_DEBOUNCE_TIME_BASED:
      /* @Trace: Dem_SUD_API_12061 */
        (void)Dem_GetFDCDebounceTimeBased(LddEvent, FaultDetectionCounter);
        /*@IF_REQ ,, OK or NOK according to return value */
        LddRetVal = E_OK;
      break;
      #endif
    
      #if (DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL > DEM_ZERO)
      case DEM_DEBOUNCE_MONITOR_BASED:
      /* @Trace: Dem_SUD_API_10328 */
        if (LddDebounceId < Dem_Number_Of_Pre_Debounce_Monitor_Internal)
        {
          /* @Trace: SWS_Dem_00264
           * If debouncing is performed by a SW-C (not handled Dem internally),
           * the Dem module shall retrieve the current value of the fault
           * detection counter for the requested event by using the method
           * defined in DemCallbackGetFDC container.
           */
          if (NULL_PTR !=
                Dem_GaaPreDebounceMonitorInternal
                  [LddDebounceId].pDemCallBackGetFDCnt)
          {
            /* @Trace: SWS_Dem_00439
             * If the callback-function GetFaultDetectionCounter returns
             * other than E_OK, this return value shall also be returned by the
             * API Dem_GetFaultDetectionCounter. */
            LddRetVal =
                Dem_GaaPreDebounceMonitorInternal[LddDebounceId].
                  pDemCallBackGetFDCnt(FaultDetectionCounter);
            /* @Trace: Dem_SUD_API_12065 */
            if (E_OK != LddRetVal)
            {
              /* @Trace: Dem_SUD_API_12064 */
              *FaultDetectionCounter = 0;
            }
          }
          else
          /* polyspace<RTE:UNR:Not a defect:No action planned>
           * Above If-condition always evaluates to true. configuration error */
          {
            /* @Trace: Dem_SUD_API_12063 */
            /* @Trace: SWS_Dem_00671
             * If the callback-function GetFaultDetectionCounter is not
             * configured (refer to configuration container DemCallbackGetFDC)
             * for a given event, the API Dem_GetFaultDetectionCounter shall
             * return DEM_E_NO_FDC_AVAILABLE. */
             
             /* LddRetVal = E_NOT_OK instead of DEM_E_NO_FDC_AVAILABLE; */
            LddRetVal = DEM_E_NO_FDC_AVAILABLE;
          }
        }
      break;
      #endif
    
      default:
      /* @Trace: Dem_SUD_API_12062 */
        *FaultDetectionCounter = 0;
        /* @LddRetVal = E_NOT_OK;  DEM_E_NO_FDC_AVAILABLE; */
      break;
      
    }
  }

  /* Return the value */
  return LddRetVal;
}
/*******************************************************************************
** Function Name        : Dem_GetEventMemoryOverflow                          **
**                                                                            **
** Service ID           : 0x32                                                **
**                                                                            **
** Description          : Gets the event memory overflow indication status.   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant for different ClientIDs,Non re-entrant   **
**                        for same ClientId.                                  **
**                                                                            **
** Input Parameters     : Dem_DTCOriginType DTCOrigin                         **
**                        uint8             ClientId                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : boolean* OverflowIndication                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_Diag_04093 SRS_BSW_00300 SRS_Diag_04164
 */
/* polyspace +1 MISRA-C3:8.3 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DEM_CODE)Dem_GetEventMemoryOverflow(
  uint8 ClientId,
  Dem_DTCOriginType DTCOrigin,
  P2VAR (boolean, AUTOMATIC, DEM_APPL_DATA) OverflowIndication)
{
  /* @Trace: SWS_Dem_00398
   * The Dem module shall provide the API Dem_GetEventMemoryOverflow to provide
   * access to the event memory overflow indication status of the respective
   * event memory.
   */
  Std_ReturnType LddRetVal = E_NOT_OK;

  boolean LblGetEventMemoryOverflowSIDLockIdx =
      Dem_SelectedDTCServiceIsLock(
          ClientId, DEM_GETEVENTMEMORYOVERFLOW_SID_LOCK_IDX);
  /* @Trace: Dem_SUD_API_12124 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_12138 */
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_12135 */
    DEM_REPORT_ERROR(DEM_GETEVENTMEMORYOVERFLOW_SID, DEM_E_WRONG_CONFIGURATION);
    /* @LddRetVal = E_NOT_OK; */
  }
  else
  #endif
  if (DEM_TRUE == LblGetEventMemoryOverflowSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_12139 */
    LddRetVal = E_NOT_OK;
  }
  else
  {
    /* @Trace: Dem_SUD_API_12140 */
    /* lock this client id */
    Dem_SelectedDTCServiceLock(
        ClientId, DEM_GETEVENTMEMORYOVERFLOW_SID_LOCK_IDX);

    /* Check if the Dem module is not initialized */
    if (DEM_INIT != Dem_GucInit)
    {
      /* @Trace: Dem_SUD_API_12141 */
      DEM_REPORT_ERROR(DEM_GETEVENTMEMORYOVERFLOW_SID, DEM_E_UNINIT);
      /* @LddRetVal = E_NOT_OK; */
    }
    else if (NULL_PTR == OverflowIndication)
    {
      /* @Trace: Dem_SUD_API_12142 */
      DEM_REPORT_ERROR(DEM_GETEVENTMEMORYOVERFLOW_SID, DEM_E_PARAM_POINTER);
      /* @LddRetVal = E_NOT_OK; */
    }
    else if (DEM_FALSE == Dem_EvMem_DTCOriginIsValid(DTCOrigin))
    {
      /* @Trace: Dem_SUD_API_12143 */
      DEM_REPORT_ERROR(DEM_GETEVENTMEMORYOVERFLOW_SID, DEM_E_PARAM_CONFIG);
      /* @LddRetVal = E_NOT_OK; */
    }
    else
    {
      switch(DTCOrigin)
      { /* @Trace: Dem_SUD_API_12126 */
        case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
        /* @Trace: Dem_SUD_API_12144 */
        /* @Trace: Dem_SUD_API_12125 */
        /* @Trace: Dem_SUD_MACRO_025 */
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
        /* @Trace: Dem_SUD_API_12128 */
        case DEM_DTC_ORIGIN_MIRROR_MEMORY:
        /* @Trace: Dem_SUD_API_12127 */
        #endif
        /* @Trace: Dem_SUD_API_12129 */
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
        /* @Trace: Dem_SUD_API_12131 */
        case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
        /* @Trace: Dem_SUD_API_12130 */
        #endif
        /* @Trace: Dem_SUD_API_12133 */
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
        /* @Trace: Dem_SUD_API_12132 */
        DEM_DTCORGIN_USER_DEFINED_CASE
        #endif
        /* @Trace: Dem_SUD_API_12134 */
        #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
        /* @Trace: Dem_SUD_API_12136 */
        /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
        if (DEM_NO_EVMEM_IDX != Dem_Client[ClientId].usDemEventMemorySetId)
        {
          /* @Trace: Dem_SUD_API_12137 */
          *OverflowIndication =
              Dem_EvMem_GetEvMemOverflowFlag(
                  Dem_Client[ClientId].usDemEventMemorySetId,DTCOrigin);
          LddRetVal = E_OK;
        }
        #endif
        break;
        default :
        /*  Do Nothing  */
        break;
      }
    }
    Dem_SelectedDTCServiceUnLock(
        ClientId, DEM_GETEVENTMEMORYOVERFLOW_SID_LOCK_IDX);
  }

  return LddRetVal;
}
/*******************************************************************************
** Function Name        : Dem_GetNumberOfEventMemoryEntries                   **
**                                                                            **
** Service ID           : 0x35                                                **
**                                                                            **
** Description          : Returns the number of entries currently stored in   **
**                        the requested event memory.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant for different ClientIDs, Non re-entrant  **
**                        for same ClientId.                                  **
**                                                                            **
** Input Parameters     : Dem_DTCOriginType DTCOrigin                         **
**                        uint8             ClientId                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint8* NumberOfEventMemoryEntries                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_Diag_04109 SRS_BSW_00300 SRS_Diag_04164
 */
/* polyspace +4 MISRA-C3:8.3 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DEM_CODE)Dem_GetNumberOfEventMemoryEntries(
        uint8 ClientId,
        Dem_DTCOriginType DTCOrigin,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) NumberOfEventMemoryEntries)
{
  /* @Trace: SWS_Dem_00651
   * The Dem module shall provide the API Dem_GetNumberOfEventMemoryEntries to
   * return the  number of event memory entries currently stored in the event
   * memory.
   */
  Std_ReturnType LddRetVal = E_NOT_OK;

  boolean LblGetNumberOfEventMemoryEntriesSIDLockIdx =
      Dem_SelectedDTCServiceIsLock(
          ClientId, DEM_GETNUMBEROFEVENTMEMORYENTRIES_SID_LOCK_IDX);
  /* @Trace: Dem_SUD_API_12145 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_12158 */
    DEM_REPORT_ERROR(
        DEM_GETNUMBEROFEVENTMEMORYENTRIES_SID, DEM_E_WRONG_CONFIGURATION);
    /* @LddRetVal = E_NOT_OK; */
  }
  else
  #endif
  /* @Trace: Dem_SUD_API_12156 */
  if (DEM_TRUE == LblGetNumberOfEventMemoryEntriesSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_12159 */
    LddRetVal = E_NOT_OK;
  }
  else
  {
    /* lock this client id */
    Dem_SelectedDTCServiceLock(
        ClientId, DEM_GETNUMBEROFEVENTMEMORYENTRIES_SID_LOCK_IDX);

    /* Check if the Dem module is not initialized */
    if (DEM_INIT != Dem_GucInit)
    {
      /* @Trace: Dem_SUD_API_12160 */
      DEM_REPORT_ERROR(DEM_GETNUMBEROFEVENTMEMORYENTRIES_SID, DEM_E_UNINIT);
      /* @LddRetVal = E_NOT_OK; */
    }
    else if (NULL_PTR == NumberOfEventMemoryEntries)
    {
      /* @Trace: Dem_SUD_API_12161 */
      DEM_REPORT_ERROR(
          DEM_GETNUMBEROFEVENTMEMORYENTRIES_SID, DEM_E_PARAM_POINTER);
      /* @LddRetVal = E_NOT_OK; */
    }
    else if (DEM_FALSE == Dem_EvMem_DTCOriginIsValid(DTCOrigin))
    {
      /* @Trace: Dem_SUD_API_12162 */
      DEM_REPORT_ERROR(
          DEM_GETNUMBEROFEVENTMEMORYENTRIES_SID, DEM_E_PARAM_CONFIG);
      /* @LddRetVal = E_NOT_OK; */
    }
    else
    {
      switch(DTCOrigin)
      {
        /* @Trace: Dem_SUD_API_12163 */
        case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
        /* @Trace: Dem_SUD_API_12164 */
        /* @Trace: Dem_SUD_API_12146 */
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > DEM_ZERO)
        /* @Trace: Dem_SUD_API_12148 */
        case DEM_DTC_ORIGIN_MIRROR_MEMORY:
        /* @Trace: Dem_SUD_API_12147 */
        #endif
        /* @Trace: Dem_SUD_API_12149 */
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
        /* @Trace: Dem_SUD_API_12150 */
        case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
        /* @Trace: Dem_SUD_API_12151 */
        #endif
        /* @Trace: Dem_SUD_API_12152 */
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
        /* @Trace: Dem_SUD_API_12153 */
        DEM_DTCORGIN_USER_DEFINED_CASE
        #endif
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
        case DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY:
        #endif
        /* @Trace: Dem_SUD_API_12154 */
        #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
        /* @Trace: Dem_SUD_API_12155 */
        /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
        if (DEM_NO_EVMEM_IDX != Dem_Client[ClientId].usDemEventMemorySetId)
        {
          /* @Trace: Dem_SUD_API_12157 */
          *NumberOfEventMemoryEntries =
              (uint8)Dem_EvMem_GetNumOfEvtMemFromDTCOrigin(
                  Dem_Client[ClientId].usDemEventMemorySetId,
                  DTCOrigin);
          LddRetVal = E_OK;
        }
        #endif
        break;
        default:
        /*  Do Nothing  */
        break;
      }
    }
    Dem_SelectedDTCServiceUnLock(
        ClientId, DEM_GETNUMBEROFEVENTMEMORYENTRIES_SID_LOCK_IDX);
  }
  return LddRetVal;
}



/*******************************************************************************
** Function Name        : Dem_GetEventFreezeFrameDataEx                       **
**                                                                            **
** Service ID           : 0x6e                                                **
**                                                                            **
** Description          : Gets the data of a freeze frame by event.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId                                             **
**                        RecordNumber                                        **
**                        DataId                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DestBuffer                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_Diag_04024 SRS_Diag_04074 SRS_Diag_04126 SRS_BSW_00300
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventFreezeFrameDataEx(
  Dem_EventIdType EventId, 
  uint8 RecordNumber, 
  uint16 DataId,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  /* @Trace: Dem_SUD_API_12102 */
  #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
       (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO))
  /* @Trace: Dem_SUD_API_12091 */
  Dem_DTCOriginType LddDTCOrigin = DEM_NO_DTC_ORIGIN;
  #endif

  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12104 */
    DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATAEX_SID, DEM_E_UNINIT);
  }
  /* @else if (DEM_FALSE == Dem_EventIdIsValid(EventId)) */
  else if ((EventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == EventId))
  {
    /* @Trace: Dem_SUD_API_12105 */
    DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATAEX_SID, DEM_E_PARAM_CONFIG);
  }
  else if (NULL_PTR == DestBuffer)
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to false  */
  {
    /* @Trace: Dem_SUD_API_12106 */
    DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATAEX_SID, DEM_E_PARAM_POINTER);
  }
  else if (NULL_PTR == BufSize)
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to false  */
  {
    /* @Trace: Dem_SUD_API_12107 */
    DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATAEX_SID, DEM_E_PARAM_POINTER);
  }
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  else if ( DEM_TRUE !=
      Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE))
  {
    /* @Trace: Dem_SUD_API_12108 */
    /* @Trace: SWS_Dem_01108
     * If an event is set to unavailable, the corresponding event shall
     * be treated as if it is not configured in the system (e.g.
     * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return E_NOT_OK). */

    /* @LddRetVal = E_NOT_OK; */
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_MACRO_100 */
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
         (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO))
    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    /* @Trace: SWS_Dem_01062
     * The functions Dem_GetEventExtendedDataRecordEx and
     * Dem_GetEventFreezeFrameDataEx shall consider only primary and user
     * defined memory.
     */
    /* @Trace: Dem_SUD_API_12110 */
    if (E_OK == Dem_GetEventDTCOrigin(LddEvent, &LddDTCOrigin))
    {
      if (DEM_ZERO == RecordNumber)
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition always evaluates to false . No Supported OBD */
      {
        #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        /* @Trace: Dem_SUD_API_12099 */
        if (DEM_TRUE == Dem_DTCFormatIsValid(EventId, DEM_DTC_FORMAT_OBD))
        {
          /* Dem_GetReadDataOfPID */
          /* @Trace: SWS_Dem_01194
           * The function Dem_GetEventFreezeFrameDataEx shall return the WWH-OBD
           * freeze frame  when called with RecordNumber 0x00. If WWH-OBD is not
           * supported, the function shall return DEM_NO_SUCH_ELEMENT instead
           * (refer to DemOBDSupport).
           */
          /* @Trace: Dem_SUD_API_12100 */
          if (DEM_MAX_NUMBER_OF_DTC > LddEvent->e_PointToDTC)
          {
            uint8 LucDemWWHOBDDTCClass =
                Dem_GaaCombinedDtc[LddEvent->e_PointToDTC].eDemWWHOBDDTCClass;
            /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
            if ((DEM_DTC_WWHOBD_CLASS_A != LucDemWWHOBDDTCClass)  &&
                (DEM_DTC_WWHOBD_CLASS_B1 != LucDemWWHOBDDTCClass) &&
                (DEM_DTC_WWHOBD_CLASS_C != LucDemWWHOBDDTCClass)  &&
                (DEM_DTC_WWHOBD_CLASS_NOCLASS != LucDemWWHOBDDTCClass))
            {
              /* @Trace: Dem_SUD_API_12103 */
              LddRetVal = DEM_NO_SUCH_ELEMENT;
            }
            else
            {
              /* @Trace: Dem_SUD_API_12101 */
              LddRetVal = Dem_GetWWHFreezeFrameData(
                          &Dem_EventRelatedData[LddEvent->e_PointToData],
                          LddDTCOrigin,
                          DataId,
                          DestBuffer,
                          BufSize);
            }
            /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
          }
        }
        #else
        /* @Trace: Dem_SUD_API_12098 */
        LddRetVal = DEM_NO_SUCH_ELEMENT;
        DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATAEX_SID, DEM_E_PARAM_CONFIG);
        #endif
      }
      else
      {
        Dem_ReturnReadEventDataType LddResult =
            DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
        /* @Trace: Dem_SUD_API_12096 */
        if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
        {
          /* @Trace: Dem_SUD_API_12097 */
          LddResult = Dem_ReadDataOfFreezeFrame(
            &Dem_EventRelatedData[LddEvent->e_PointToData],
            LddDTCOrigin, RecordNumber,
            DataId,
            DEM_FFFORMAT_TYPE_RAW,
            DestBuffer,
            BufSize);
        }
        switch(LddResult) {
        case DEM_GET_READEVDATA_OK:
          /* @Trace: Dem_SUD_API_12093 */
          LddRetVal = E_OK;
          break;
        /* @Trace: SWS_Dem_00996
         * Dem_GetEventFreezeFrameDataEx shall return E_NOT_OK in case the
         * requested FreezeFrame data is currently not accessible (e.g. in case
         * of asynchronous preempted data retrieval from application).
         */
        case DEM_GET_READEVDATA_NOT_STORED:
          /* @Trace: Dem_SUD_API_12094 */
          DEM_REPORT_ERROR(
              DEM_GETEVENTFREEZEFRAMEDATAEX_SID, DEM_E_PARAM_DATA);
          LddRetVal = E_NOT_OK;
          break;
        /* polyspace<RTE:UNR:Not a defect:No action planned>
         * If-condition evaluates to true or false according to configuration */
        case DEM_GET_READEVDATA_WRONG_BUFFERSIZE:
          /* @Trace: Dem_SUD_API_12095 */
          DEM_REPORT_ERROR(
              DEM_GETEVENTFREEZEFRAMEDATAEX_SID, DEM_E_PARAM_LENGTH);
          LddRetVal = E_NOT_OK;
          break;
        /* case DEM_GET_READEVDATA_WRONG_RECORDNUMBER: */
        default:
          /* @Trace: Dem_SUD_API_12092 */
          DEM_REPORT_ERROR(
              DEM_GETEVENTFREEZEFRAMEDATAEX_SID, DEM_E_PARAM_CONFIG);
          LddRetVal = E_NOT_OK;
          break;
        }
      }
    }
    else
    #endif
    {
      /* @Trace: Dem_SUD_API_12109 */
      /* polyspace:begin<RTE:UNR:Not a defect:No action planned>
       * No problem. Unreachable code */
      DEM_UNUSED(EventId);
      DEM_UNUSED(RecordNumber);
      DEM_UNUSED(DataId);
      DEM_UNUSED_PTR(DestBuffer);
      DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATAEX_SID, DEM_E_PARAM_DATA);
      LddRetVal = E_NOT_OK;
      /* polyspace:end<RTE:UNR:Not a defect:No action planned>
       * No problem. Unreachable code */
    }
  }
  
  return LddRetVal;
}



/*******************************************************************************
** Function Name        : Dem_GetEventExtendedDataRecordEx                    **
**                                                                            **
** Service ID           : 0x6d                                                **
**                                                                            **
** Description          : Gets the data of an extended data record by event.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId                                             **
**                        RecordNumber                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DestBuffer                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_Diag_04074 SRS_Diag_04126 SRS_Diag_04195 SRS_BSW_00300
 */
 #if (DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventExtendedDataRecordEx(
  Dem_EventIdType EventId, 
  uint8 RecordNumber,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize)
{
  /* @Trace: SWS_Dem_00477
   * The function Dem_GetEventExtendedDataRecordEx shall report the data of the
   * extended data record of the requested diagnostic event.
   */
  Std_ReturnType LddRetVal = E_NOT_OK;
  Dem_DTCOriginType LddDTCOrigin = DEM_NO_DTC_ORIGIN;

  if (Dem_GucInit != DEM_INIT)
  {
    /* @Trace: Dem_SUD_API_12111 */
    DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORDEX_SID, DEM_E_UNINIT);
    /*@ LddRetVal = E_NOT_OK; */
  }
  else if ((EventId == DEM_NO_EVENT) || (EventId > DEM_NUMBER_OF_EVENTS))
  {
    /* @Trace: Dem_SUD_API_12116 */
    DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORDEX_SID, DEM_E_PARAM_CONFIG);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if (DestBuffer == NULL_PTR)
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to false  */
  {
    /* @Trace: Dem_SUD_API_12117 */
    DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORDEX_SID, DEM_E_PARAM_POINTER);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if (BufSize == NULL_PTR)
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to false  */
  {
    /* @Trace: Dem_SUD_API_12118 */
    DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORDEX_SID, DEM_E_PARAM_POINTER);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if (((RecordNumber < (uint8)DEM_ONE) ||
           (RecordNumber > (uint8)DEM_MAX_VALID_RECORD_NUMBER)) &&
           (RecordNumber != DEM_MAX_RECORD))
  {
    /* @Trace: Dem_SUD_API_12119 */
    DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORDEX_SID, DEM_E_PARAM_CONFIG);
  }
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  else if ( DEM_TRUE !=
      Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE))
  {
    /* @Trace: Dem_SUD_API_12120 */
    /* @Trace: SWS_Dem_01108
     * If an event is set to unavailable, the corresponding event shall
     * be treated as if it is not configured in the system (e.g.
     * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return E_NOT_OK). */

    /* @LddRetVal = E_NOT_OK; */
  }
  #endif
  else  
  #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
       (DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO))
  /* @Trace: SWS_Dem_01062
   * The functions Dem_GetEventExtendedDataRecordEx and
   * Dem_GetEventFreezeFrameDataEx shall consider only primary and user defined
   * memory.
   */
  if (E_NOT_OK ==
        Dem_GetEventDTCOrigin(&Dem_Event[EventId - DEM_ONE], &LddDTCOrigin))
  {
    /* @Trace: Dem_SUD_API_12122 */
    DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORDEX_SID, DEM_E_PARAM_CONFIG);
  }
  else
  {
    Dem_ReturnReadEventDataType LddResult =
        DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
    Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
    /* @Trace: Dem_SUD_API_10318 */
    if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
    { 
      /* @Trace: Dem_SUD_API_12123 */
      LddResult =
          Dem_ReadDataOfExtendedData(
              &Dem_EventRelatedData[LddEvent->e_PointToData],
              LddDTCOrigin,
              RecordNumber,
              DestBuffer,
              BufSize);
    }
    /* @Trace: Dem_SUD_API_12112 */
    switch(LddResult) {
    case DEM_GET_READEVDATA_OK:
    /* @Trace: Dem_SUD_API_12113 */
      LddRetVal = E_OK;
      break;
    /* @Trace: SWS_Dem_00997
     * Dem_GetEventExtendedDataRecordEx shall return E_NOT_OK if the requested
     * data is currently not accessible (e.g.in case of asynchronous preempted
     * data retrieval from application).
     */
    case DEM_GET_READEVDATA_NOT_STORED:
    /* @Trace: Dem_SUD_API_12114 */
      DEM_REPORT_ERROR(
          DEM_GETEVENTEXTENDEDDATARECORDEX_SID, DEM_E_PARAM_DATA);
      LddRetVal = E_NOT_OK;
      break;        
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * If-condition evaluates to true or false according to configuration */
    case DEM_GET_READEVDATA_WRONG_BUFFERSIZE:
    /* @Trace: Dem_SUD_API_10315 */
      DEM_REPORT_ERROR(
          DEM_GETEVENTEXTENDEDDATARECORDEX_SID, DEM_E_PARAM_LENGTH);
      LddRetVal = E_NOT_OK;
      break;
    /* case DEM_GET_READEVDATA_WRONG_RECORDNUMBER: */
    default:
    /* @Trace: Dem_SUD_API_12115 */
      DEM_REPORT_ERROR(
          DEM_GETEVENTEXTENDEDDATARECORDEX_SID, DEM_E_PARAM_CONFIG);
      LddRetVal = E_NOT_OK;
      break;
    }
  }
  
  #else
  {
    /* @Trace: Dem_SUD_API_12121 */
    DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORDEX_SID, DEM_E_PARAM_CONFIG);
    /* LddRetVal = E_NOT_OK; */
    DEM_UNUSED(EventId);
    DEM_UNUSED(RecordNumber);
    DEM_UNUSED_PTR(DestBuffer);
  }
  #endif

  return LddRetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_SetDTCSuppression                               **
**                                                                            **
** Service ID           : 0x33                                                **
**                                                                            **
** Description          : Set the suppression status of a specific DTC.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : DTC                                                 **
**                        SuppressionStatus                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04220 SRS_BSW_00300
 */
/* polyspace +2 MISRA-C3:8.3 [Justified:Low] Justify with annotations */
#if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
FUNC(Std_ReturnType, DEM_CODE)Dem_SetDTCSuppression(
  uint8 ClientId,
  boolean SuppressionStatus)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint16 LusByteShift =
      ((uint16)DEM_ONE << DEM_SELECTDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_CLEARDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSEVERITYOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSTATUSOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SETDTCSUPPRESSION_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);
  Std_ReturnType LucResult = Dem_CheckStatusOfSelectedDTCServices(
      ClientId,
      DEM_SETDTCSUPPRESSION_SID,
      LusByteShift);
  /* @Trace: Dem_SUD_API_12326 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_12332 */
    DEM_REPORT_ERROR(DEM_SETDTCSUPPRESSION_SID, DEM_E_PARAM_DATA);
    /* @LddRetVal = E_NOT_OK; */
  }
  else
  #endif
  if (E_OK != LucResult)
  {
    /* @Trace: Dem_SUD_API_12333 */
    LddRetVal = LucResult;
  }
  else
  {
    Dem_SelectedDTCServiceLock(ClientId, DEM_SETDTCSUPPRESSION_SID_LOCK_IDX);
    /* Check if the Dem module is not initialized */
    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_12334 */
      DEM_REPORT_ERROR(DEM_SETDTCSUPPRESSION_SID, DEM_E_UNINIT);
      /* @LddRetVal = E_NOT_OK; */
    }
    /* @Trace: Dem_SUD_API_12335 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    else if (E_OK != Dem_ClientSelectDtcState[ClientId].resultSelectDTC)
    {
      /* @Trace: Dem_SUD_API_12336 */
      DEM_REPORT_ERROR(DEM_SETDTCSUPPRESSION_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = Dem_ClientSelectDtcState[ClientId].resultSelectDTC;
    }
    /* @Trace: Dem_SUD_API_12338 */
    #if (DEM_MAX_NUM_GRP_DTC > DEM_ZERO)
    else if (DEM_DTC_GROUP_IS_VALID(
        Dem_ClientSelectDtcState[ClientId].selectedDTC))
    {
      /* @Trace: Dem_SUD_API_12337 */
      DEM_REPORT_ERROR(DEM_SETDTCSUPPRESSION_SID, DEM_E_PARAM_DATA);
      /* @LddRetVal = E_NOT_OK; */
    }
    #endif
    #endif
    else if ((SuppressionStatus != DEM_TRUE) &&
             (SuppressionStatus != DEM_FALSE))
    {
      /* @Trace: Dem_SUD_API_12339 */
      DEM_REPORT_ERROR(DEM_SETDTCSUPPRESSION_SID, DEM_E_PARAM_DATA);
      /* @LddRetVal = E_NOT_OK; */
    }
    else
    {
      /* @Trace: Dem_SUD_API_12327 */
      #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
      /* Dem588 is ignored according to AR 4.2.2
       *
       * Dem588: The API Dem_SetDTCSuppression shall reject the request and
       * return E_NOT_OK, if the event memory entry exists already */

      /* @Trace: SWS_Dem_01315
       * If Dem_SetDTCSuppression is called the Dem shall set the suppression
       * status of the selected DTC to value of the parameter SuppressionStatus.
       * */
      Dem_CombinedDtcPCType LddCbDTC =
          Dem_GetDtcByDtcId(
              Dem_ClientSelectDtcState[ClientId].selectedDTC,
              Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);

      if ( (NULL_PTR != LddCbDTC) )
      {
        Dem_NumOfEventIdType LddStartPos =
            Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
        const Dem_NumOfEventIdType LddEndPos =
            Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);
        /* @Trace: Dem_SUD_API_12329 */
        for (; LddStartPos < LddEndPos; LddStartPos++)
        {
          Dem_EventIdType LddEventId = Dem_ListOfCombinedEvents[LddStartPos];
          SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
          if (DEM_TRUE == SuppressionStatus)
          {
            /* @Trace: Dem_SUD_API_12331 */
            Dem_EvSetProcState(LddEventId, DEM_EVPROCSTATE_DTC_SUPP);
          }
          else
          {
            /* @Trace: Dem_SUD_API_12330 */
            Dem_EvClearProcState(LddEventId, DEM_EVPROCSTATE_DTC_SUPP);
          }
          SchM_Exit_Dem_REQUEST_DATA_PROTECTION();

          LddRetVal = E_OK;
        }
      }
      else
      {
        /* @Trace: Dem_SUD_API_12328 */
        DEM_REPORT_ERROR(DEM_SETDTCSUPPRESSION_SID, DEM_E_PARAM_CONFIG);
        LddRetVal = E_NOT_OK;
      }
    }
    #endif
    Dem_SelectedDTCServiceUnLock(ClientId, DEM_SETDTCSUPPRESSION_SID_LOCK_IDX);
  }
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_GetDTCSuppression                               **
**                                                                            **
** Service ID           : 0xbc                                                **
**                                                                            **
** Description          : Returns the suppression status of a specific DTC.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ClientId          - Unique client id, assigned to   **
**                                            the instance of the calling     **
**                                            module.                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : SuppressionStatus - Defines whether the respective  **
**                                            DTC is suppressed the           **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04220 SRS_BSW_00300
 */
/* polyspace +2 MISRA-C3:8.3 MISRA-C3:8.4 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCSuppression(
    uint8 ClientId,
  P2VAR (boolean, AUTOMATIC, DEM_APPL_DATA) SuppressionStatus)
{
  /* @Trace: SWS_Dem_01102
   * DTC suppression shall not stop event processing of the corresponding DTC.
   */

  /* @Trace: SWS_Dem_01307
   * Dem_GetDTCSuppression is called, the Dem shall return the DTC suppression
   * status in the output parameter SuppressionStatus. A value of TRUE means
   * that the DTC was suppressed by a call of Dem_SetDTCSuppression with
   * SuppressionStatus= TRUE, a value of FALSE means, that the DTC is currently
   * not suppressed.
   */

  Std_ReturnType LddRetVal = E_OK;
  uint16 LusByteShift =
      ((uint16)DEM_ONE << DEM_SELECTDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_CLEARDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSEVERITYOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSTATUSOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SETDTCSUPPRESSION_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);
  Std_ReturnType LucResult = Dem_CheckStatusOfSelectedDTCServices(
      ClientId,
      DEM_GETDTCSUPPRESSION_SID,
      LusByteShift);

  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_12045 */
    DEM_REPORT_ERROR(DEM_GETDTCSUPPRESSION_SID, DEM_E_PARAM_DATA);
    LddRetVal = DEM_WRONG_DTC;
  }
  else
  #endif
  /* Check module Initialization status */
  if (E_OK != LucResult)
  {
    /* @Trace: Dem_SUD_API_12046 */
    LddRetVal = LucResult;
  }
  else
  {
      /* lock this client id */
    Dem_SelectedDTCServiceLock(ClientId, DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);

    /* check initialization */
    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_12047 */
      DEM_REPORT_ERROR(DEM_GETDTCSUPPRESSION_SID, DEM_E_UNINIT);
      LddRetVal = E_NOT_OK;
    }
    else if (SuppressionStatus == NULL_PTR)
    {
      /* @Trace: Dem_SUD_API_12048 */
      DEM_REPORT_ERROR(DEM_GETDTCSUPPRESSION_SID, DEM_E_PARAM_POINTER);
      LddRetVal = E_NOT_OK;
    }
    /* @Trace: Dem_SUD_API_12049 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    else if (E_OK != Dem_ClientSelectDtcState[ClientId].resultSelectDTC)
    {
      /* @Trace: Dem_SUD_API_12050 */
      DEM_REPORT_ERROR(DEM_GETDTCSUPPRESSION_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = Dem_ClientSelectDtcState[ClientId].resultSelectDTC;
    }
    #endif
    else
    /* @Trace: Dem_SUD_API_12051 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    {

      /* get evendId from selected Dtc*/
      Dem_EventIdType LddEventId = Dem_GetEventIdByDTC(
      DEM_GETSTATUSOFDTC_SID,
      Dem_ClientSelectDtcState[ClientId].selectedDTC,
      Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);

      /* check EventId valid or not */
      if ((LddEventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == LddEventId))
      {
        /* @Trace: Dem_SUD_API_10326 */
        DEM_REPORT_ERROR(DEM_GETDTCSUPPRESSION_SID, DEM_E_PARAM_CONFIG);
        LddRetVal = DEM_WRONG_DTC;
      }
      else
      {
        /* get suppression state */
        /* @Trace: Dem_SUD_API_12052 */
        *SuppressionStatus =
            Dem_EvIsProcStateTriggered(LddEventId, DEM_EVPROCSTATE_DTC_SUPP);
        LddRetVal = E_OK;
      }
    }
    #endif
    /* unlock this client id */
    Dem_SelectedDTCServiceUnLock(ClientId, DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);
  }
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_SetWIRStatus                                    **
**                                                                            **
** Service ID           : 0x7a                                                **
**                                                                            **
** Description          : Sets the WIR status bit via failsafe SW-Cs.         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant for different EventIds. Non reentrant for **
**                        the same EventId.                                   **
**                                                                            **
** Input Parameters     : EventId         Identification of an event by       **
**                                        assigned EventId. The Event Number  **
**                                        is configured in the DEM.           **
**                                        Min.: 1(0: Indication of no Event   **
**                                        or Failure)                         **
**                                        Max.:Result of configuration of     **
**                                        Event Numbers in DEM (Max is either **
**                                        255 or 65535)                       **
**                        WIRStatus       Requested status of event related   **
**                                        WIR-bit (regarding to the current   **
**                                        status of function inhibition)      **
**                                        WIRStatus = TRUE -> WIR-bit shall   **
**                                        be set to "1"                       **
**                                        WIRStatus = FALSE -> WIR-bit shall  **
**                                        be set to "0"                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DestBuffer                                          **
**                                                                            **
** Return parameter     : E_OK:           Request to set the WIR status was   **
**                                        successful.                         **
**                        E_NOT_OK:       Request to set the WIR status was   **
**                                        not accepted (e.g. disabled         **
**                                        controlDTCSetting) and should be    **
**                                        repeated.                           **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
**                        Dem_GetEventConditionsAndControlDTCSetting()        **
*******************************************************************************/
/* @Trace: SRS_Diag_04126 SRS_Diag_04128 SRS_BSW_00300
 */
/* polyspace +2 MISRA-C3:8.3 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DEM_CODE) Dem_SetWIRStatus(
   Dem_EventIdType EventId,
   boolean WIRStatus)
{
  /* @Trace: SWS_Dem_00831
   * Dem shall provide a function to control (set/reset) the
   * WarningIndicatorRequested-bit of a  configured event (in Dem) regarding to
   * e.g. failsafe state.
   */
  /* @Trace: SWS_Dem_00832
   * Setting of the WIR-bit of an event can be controlled via Dem_SetWIRStatus
   * OR by the Dem internal WIR-bit handling. (OR-Operation).
   */
  Std_ReturnType LddRetVal = E_NOT_OK;
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  /* @Trace: Dem_SUD_API_12537 */
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  /* @Trace: Dem_SUD_API_12538 */
  boolean LblEvIsProcStateTriggered =
      Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE);
  #endif
  /* Check module initialization */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_10323 */
    DEM_REPORT_ERROR(DEM_SETWIRSTATUS_SID, DEM_E_UNINIT);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if ((EventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == EventId))
  {
    /* @Trace: Dem_SUD_API_10324 */
    DEM_REPORT_ERROR(DEM_SETWIRSTATUS_SID, DEM_E_PARAM_DATA);
    /* @LddRetVal = E_NOT_OK; */
  }
  /* @Trace: SWS_Dem_00836
   * During disabled ControlDTCSettings the WIR-bit of an event shall not be
   * changed via Dem_SetWIRStatus and the function shall return E_NOT_OK.
   */
  /* @Trace: SWS_Dem_01108
   * If an event is set to unavailable, the corresponding event shall
   * be treated as if it is not configured in the system (e.g.
   * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return E_NOT_OK). */
  else if ((E_OK == Dem_GetEventConditionsAndControlDTCSetting(EventId))
          #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
          && (DEM_TRUE == LblEvIsProcStateTriggered)
          #endif
          )
  {
    SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
    /* @Trace: SWS_Dem_00833
     * The WIR-bit of the corresponding event shall be set to "1" if
     * Dem_SetWIRStatus is called with parameter WIRStatus = TRUE .
     */
    if (DEM_TRUE == WIRStatus)
    {
      /* @Trace: Dem_SUD_API_12540 */
        Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_WIR_STATUS);
        Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_IS_SET_WIR_STATUS);
        LddRetVal = E_OK;
    }
    /* @Trace: SWS_Dem_00834
     * The WIR-bit of the corresponding event shall be set to "0" if
     * Dem_SetWIRStatus is called with WIRStatus = FALSE and no referenced Dem
     * Indicator(s) are set.
     */
    else if ((DEM_FALSE == WIRStatus) &&
             (DEM_NO_INDATT_IDX == LddEvent->e_PointToIndicator))
    {
      /* @Trace: Dem_SUD_API_12541 */
        Dem_EvClearProcState(EventId, DEM_EVPROCSTATE_WIR_STATUS);
        Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_IS_SET_WIR_STATUS);
        LddRetVal = E_OK;
    }
    else
    {
      /* @Trace: Dem_SUD_API_10325 */
      /* Nothing to do */
    }
    SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
  }
  else
  {
    /* @Trace: Dem_SUD_API_12539 */
    /* Nothing to do */
  }
  return LddRetVal;
}

#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
