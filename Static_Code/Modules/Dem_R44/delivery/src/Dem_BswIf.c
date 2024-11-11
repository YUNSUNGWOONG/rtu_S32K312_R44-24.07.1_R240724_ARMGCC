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
**  SRC-MODULE: Dem_BswIf.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of Bsw error report functionality                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.13    01-Aug-2023   DanhTQ1       Jira #CP44-2480                      **
** 1.0.10.0  24-Mar-2023   SY Kim        Jira #CP44-1830                      **
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"            /* DEM module Header File */
#include "Dem_Ram.h"        /* DEM Ram Header File */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"            /* Det Module Header File */
#endif

#include "NvM.h"              /* NVRAM manager symbols Header File */
#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */
#include "Dem_Event.h"
#include "Dem_Dtc.h"
#include "Dem_EventDebounce.h"
#include "Dem_EventCallback.h"
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dem_SetEventStatus                                  **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : Called by SW-Cs or BSW modules to report monitor    **
**                        status information to the Dem. BSW modules calling  **
**                        Dem_SetEventStatus can safely ignore                **
**                        the return value.                                   **
**                                                                            **
** Sync/Async           : Synchronous/Asynchronous                            **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId,                            **
**                        Dem_EventStatusType EventStatus                     **
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
**                        Dem_GaaPreDebounceTimeBased                         **
**                        Dem_GaaDebouncingCompleteBuffer                     **
**                        Dem_MonitorStatus                                   **
**                        Dem_GaaErrorBuffer                                  **
**                        Dem_GaaErrorBufferStatus                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_BSW_00337 SRS_BSW_00339 SRS_Diag_04001 SRS_Diag_04067
           SRS_Diag_04068 SRS_Diag_04124 SRS_Diag_04125 SRS_Diag_04126
           SRS_Diag_04127 SRS_Diag_04129 SRS_Diag_04137 SRS_Diag_04151
           SRS_Diag_04165
 */
/* @Trace: Dem_SUD_MACRO_049 */
/* polyspace +1 CODE-METRICS:VG  CODE-METRICS:LEVEL CODE-METRICS:CALLS CODE-METRICS:FXLN CODE-METRICS:CALLING CODE-METRICS:PATH[Not a defect:LOW] "Not a defect" */ 
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(
  Dem_EventIdType EventId,
  Dem_EventStatusType EventStatus)
{
  Dem_EventStatusType LddEvStatus = EventStatus;
  /* @Trace: SWS_Dem_00330
   * The Dem module shall provide the capability to report the status of an
   * event allowing a diagnostic monitor to inform the Dem about the result
   * of the internal diagnostic test (refer to Dem_SetEventStatus).
   */
  Std_ReturnType LddRetVal = E_NOT_OK;
  boolean LblIsBit0GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_0);
  boolean LblIsBit1GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_1);
  boolean LblIsBit2GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_2);
  boolean LblIsBit3GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_3);
  boolean LblIsBit4GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_4);
  boolean LblIsBit5GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_5);
  boolean LblIsBit6GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_6);
  boolean LblIsBit7GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_7);

  if ((EventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == EventId))
  {
    /* @Trace: Dem_SUD_API_12375 */
    DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_CONFIG);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if ((boolean) DEM_FALSE == Dem_EventStatusIsValid(LddEvStatus))
  {
    /* @Trace: Dem_SUD_API_12386 */
    DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_DATA);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if ((DEM_TRUE == LblIsBit0GetTransit) ||
           (DEM_TRUE == LblIsBit1GetTransit) ||
           (DEM_TRUE == LblIsBit2GetTransit) ||
           (DEM_TRUE == LblIsBit3GetTransit) ||
           (DEM_TRUE == LblIsBit4GetTransit) ||
           (DEM_TRUE == LblIsBit5GetTransit) ||
           (DEM_TRUE == LblIsBit6GetTransit) ||
           (DEM_TRUE == LblIsBit7GetTransit))
  {
    /* @Trace: SWS_Dem_01286
     * If the API Dem_SetEventStatus is called and the Dem has synchronously
     * processed the reported monitor status according to [SWS_Dem_01280] and
     * the corresponding UDS status (see [SWS_Dem_01285]) cannot be processed,
     * the Dem shall report the development error
     * DEM_E_UDS_STATUS_PROCESSING_FAILED.
     */
    /* @Trace: Dem_SUD_API_12397 */
    DEM_REPORT_ERROR(
        DEM_SETEVENTSTATUS_SID, DEM_E_UDS_STATUS_PROCESSING_FAILED);
  }
  else
  {
    /* @Trace: Dem_SUD_API_12408 */
    #if ((DEM_DEV_ERROR_DETECT == STD_ON) && \
        (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO))
    /* @Trace: Dem_SUD_API_12419 */
    Dem_NumOfDebounceType LddDebounceId
                  =  Dem_Event[EventId - DEM_ONE].ucIndexOfDebounceAry;
    P2CONST(Dem_PreDebounceCounterType, AUTOMATIC, DEM_CONST) LddPreDBC
                  = &Dem_GaaPreDebounceCounter[LddDebounceId];
    uint8 LucDbType = DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(
                  Dem_Event[EventId - DEM_ONE].ParamFieldsA
        );
    #endif
    /* @Trace: SWS_Dem_00676
     * If development error detection is enabled and
     * Dem_SetEventStatus or Dem_ResetEventDebounceStatus is called before
     * Dem_Init or after Dem_Shutdown for events which have DemDebounce-
     * CounterStorage set to True, the Dem module shall set the error code
     * DEM_E_WRONG_CONDITION. */
    /* @Trace: Dem_SUD_API_12377 */
    #if ((DEM_DEV_ERROR_DETECT == STD_ON) && \
        (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO))
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
    /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
    if ((DEM_DEBOUNCE_COUNTER_BASED == LucDbType) &&
        (DEM_TRUE == (LddPreDBC->blDemDebounceCounterStorage)) &&
        (DEM_INIT != Dem_GucInit)
       )
    {
      /* @Trace: Dem_SUD_API_12379 */
      DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_WRONG_CONDITION);
      /* LddRetVal = E_NOT_OK */
    }
    else
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
    #endif
    {
      /* @Trace: Dem_SUD_API_12382 */
      /* @Trace: SWS_Dem_01250
       * For each DemMultiEventTriggeringSlaveEventRef of this
       * DemMultiEventTriggering the Dem shall trigger the same API calls
       * with identical parameters only the EventId parameter shall be replaced
       * with the event referenced from DemMultiEventTriggeringSlaveEventRef.*/
      Dem_EventIdType LddEvId = EventId;
      uint8 LucStartIdx = DEM_ZERO;
      uint8 LucStopIdx = DEM_ONE;
      /* @Trace: Dem_SUD_API_12384 */
      #if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
      uint8 LucIdxOfMasterEvent = Dem_GetIndexOfMasterEventByEventId(LddEvId);
      boolean LblIdxOfMasterEventIsFound = DEM_FALSE;
      /* @Trace: Dem_SUD_API_12385 */
      if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING != LucIdxOfMasterEvent)
      {
        /* @Trace: Dem_SUD_API_12387 */
        LucStartIdx = Dem_DemMultiEventTrg[LucIdxOfMasterEvent].slaveEventIdx;
        LucStopIdx = LucStartIdx +
            Dem_DemMultiEventTrg[LucIdxOfMasterEvent].numberOfSlaveEvent;
        LblIdxOfMasterEventIsFound = DEM_TRUE;
      }
      #endif
      /* Report status for all salve event related from master event id */
      /* @Trace: Dem_SUD_API_12388 */
      for (; LucStartIdx < LucStopIdx; LucStartIdx++)
      {
        /* @Trace: Dem_SUD_API_12389 */
        #if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
        /* @Trace: Dem_SUD_API_12390 */
        if (DEM_TRUE == LblIdxOfMasterEventIsFound)
        {
          /* @Trace: Dem_SUD_API_12391 */
          LddEvId = Dem_ListOfSlaveEventTrg[LucStartIdx];
        }
        #endif
        /* @Trace: SWS_Dem_01091
         * Dem_SetEventStatus shall ignore the replacement event.
         */
        /* @Trace: Dem_SUD_API_12392 */
        /* @Trace: Dem_SUD_MACRO_012*/
        #if ( DEM_STORAGE_CONDITION_SUPPORT == STD_ON )
        boolean LblIsReplacementEvent = DEM_FALSE;
        /* @Trace: Dem_SUD_API_12393 */
        for ( uint8 LucStorageConditionIdx = DEM_ZERO;
             LucStorageConditionIdx < DEM_NUMBER_STORAGE_CONDITION;
             LucStorageConditionIdx++ )
        {
          /* @Trace: Dem_SUD_API_12394 */
          if ( DEM_NO_EVENT_INDEX !=
              Dem_GaaStorageCondition[LucStorageConditionIdx].ucDemEventIdx )
          {
            /* @Trace: Dem_SUD_API_12395 */
            if ( LddEvId ==
                Dem_GaaStorageCondition[LucStorageConditionIdx].ucDemEventIdx)
            {
              LblIsReplacementEvent = DEM_TRUE;
              break;
            }
          }
        }

        if (DEM_FALSE != LblIsReplacementEvent)
        {
          /* @Trace: Dem_SUD_API_12398 */
          /* LddRetVal = E_NOT_OK; */
        }
        else
        #endif
        /* @Trace: Dem_SUD_API_12396 */
        /* @Trace: SWS_Dem_00368
         * If development error detection is enabled and any instance calls any
         * Dem API, excluding Dem_SetEventStatus, Dem_ResetEventDebounceStatus,
         * Dem_GetVersionInfo and Dem_MainFunction, after Dem_Shutdown has
         * been called, the Dem module shall set the error code DEM_E_UNINIT
         * until Dem_Init is called again.
         */

        /* @Trace: SWS_Dem_01212
         * After Dem_PreInit, the Dem shall support debouncing by calling API
         * Dem_SetEventStatus with EventStatus set to DEM_EVENT_STATUS_PREPASSED
         * or DEM_EVENT_STATUS_PREFAILED.
         */
        if ((DEM_EVENT_KIND_BSW == Dem_GetEventKind(LddEvId)) &&
            (DEM_UNINIT == Dem_GucInit))
        {
          /* @Trace: Dem_SUD_API_12399 */
          /* @Trace: SWS_Dem_00364 */
          DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_UNINIT);
          /* @LddRetVal = E_NOT_OK; */
        }
        else if ((DEM_EVENT_KIND_SWC == Dem_GetEventKind(LddEvId)) &&
                 (DEM_INIT != Dem_GucInit))
        {
          /* @Trace: Dem_SUD_API_12400 */
          DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_UNINIT);
          /* @LddRetVal = E_NOT_OK; */
        }
        /* @Trace: Dem_SUD_API_12401 */
        #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
        else if (DEM_TRUE != Dem_EvIsProcStateTriggered ( LddEvId,
            DEM_EVPROCSTATE_EVENT_AVAILABLE))
        {
          /* @Trace: Dem_SUD_API_12402 */
          /* @Trace: SWS_Dem_01108
           * If an event is set to unavailable, the corresponding event shall
           * be treated as if it is not configured in the system (e.g.
           * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return
           * E_NOT_OK). */
          /* LddRetVal = E_NOT_OK; */
        }
        #endif
        else
        {
          /* @Trace: Dem_SUD_API_12403 */
          LddRetVal = E_OK;
          /* @Trace: Dem_SUD_API_12404 */
          if (DEM_INIT == Dem_GucInit)
          {
            Dem_OperationCycleStateType LddOpCycleState =
                (Dem_OperationCycleStateType)DEM_CYCLE_STATE_NOTSTART;

            /* Note: If Power cycle (DEM_OPCYC_POWER) should not be
             * ended/stopped during 'ECU Sleep' then it should be configured
             * with DemOperationCycleStatusStorage == TRUE.
             *
             * if DemOperationCycleStatusStorage is true then state is stored,
             * so Bsw Events always able to be processed regardless
             * Dem Init State */
            (void)Dem_GetOpCycleStateByEvent(LddEvId, &LddOpCycleState);
            /* @Trace: Dem_SUD_API_12405 */
            if (DEM_CYCLE_STATE_START != LddOpCycleState)
            {
              /* @Trace: Dem_SUD_API_12406 */
              LddRetVal = E_NOT_OK;
            }
          }
          /* @Trace: Dem_SUD_MACRO_117 */
          #if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
          /* @Trace: SWS_Dem_00805
           * If the configuration parameter DemEnvironmentDataCapture is set
           * to DEM_CAPTURE_SYNCHRONOUS_TO_REPORTING (refer to DemPrimaryMemory
           * or DemUserDefinedMemory) and DemDebounceTimeBasedSupport is set to
           * "false", event-specific freeze frame data shall be captured within
           * the reporting function (i.e. in the context of Dem_SetEventStatus).
           */
          /* @Trace: SWS_Dem_01082
           * If the configuration parameter DemEnvironmentDataCapture is set to
           * DEM_CAPTURE_SYNCHRONOUS_TO_REPORTING (refer to DemPrimaryMemory or
           * DemUserDefinedMemory), event-specific extended data shall be
           * captured within the context of Dem_SetEventStatus.
           */
          /* @Trace: Dem_SUD_API_12407 */
          if (( DEM_DTC_ORIGIN_PRIMARY_MEMORY ==
              Dem_Event[LddEvId - DEM_ONE].aaEventDestination) ||
              ( DEM_DTCORGIN_USER_DEFINED_IS_VALID (
                  Dem_Event[LddEvId - DEM_ONE].aaEventDestination)))
          {
            Std_ReturnType LddResult = E_NOT_OK;
            /* @Trace: Dem_SUD_API_12409 */
            if ( DEM_NO_EVMEM_IDX !=
                 Dem_Event[LddEvId - DEM_ONE].ucEventMemDstIdx)
            {
              if ( DEM_DTC_ORIGIN_PRIMARY_MEMORY ==
                  Dem_Event[LddEvId - DEM_ONE].aaEventDestination)
              {
                /* @Trace: Dem_SUD_API_12411 */
                /* @Trace: Dem_SUD_MACRO_155 */
                /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
                /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Configuration. */
                #if ( DEM_MAX_NUMBER_PRIMARY_MEMORY > DEM_ZERO)
                uint8 LucDemEnvDataCapture =
                    Dem_GaaDemPrimaryMemory[
                       Dem_Event[LddEvId - DEM_ONE].ucEventMemDstIdx].
                       usDemEnvironmentDataCapture;
                /* @Trace: Dem_SUD_API_12412 */
                /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
                if ( DEM_CAPTURE_SYNCHRONOUS_TO_REPORTING ==
                     LucDemEnvDataCapture )
                {
                  /* @Trace: Dem_SUD_API_12413 */
                  LddResult = E_OK;
                }
                #endif
                /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
                /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
              }
              else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID (
                  Dem_Event[LddEvId - DEM_ONE].aaEventDestination ))
              {
                /* @Trace: Dem_SUD_API_12410 */
                /* @Trace: Dem_SUD_API_12415 */
                /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
                /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Configuration. */
                #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
                /* @Trace: Dem_SUD_API_12416 */
                uint8 LucDemEnvDataCapture = Dem_GaaDemUserDefinedMemory[
                      Dem_Event[LddEvId - DEM_ONE].ucEventMemDstIdx].
                      usDemEnvironmentDataCapture;
                /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
                if ( DEM_CAPTURE_SYNCHRONOUS_TO_REPORTING ==
                    LucDemEnvDataCapture)
                {
                  LddResult = E_OK;
                }
                #endif
                /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
                /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
              }
              else
              {
                /* @Trace: Dem_SUD_API_12414 */
                /* Nothing to do */
              }
            }
            /* @Trace: Dem_SUD_API_12417 */
            /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
            /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
            if (E_OK == LddResult)
            {
              /* @Trace: Dem_SUD_API_12418 */
              /* @Trace: Dem_SUD_MACRO_142 */
              #if (DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER > DEM_ZERO)
              /* @Trace: SWS_Dem_01083
               * If DemEnvironmentDataCapture is equal to
               * DEM_CAPTURE_ SYNCHRONOUS_TO_REPORTING (refer to
               * DemPrimaryMemory or DemUserDefinedMemory), the Dem module
               * shall queue the environmental data from the reporting (see
               * [SWS_Dem_00805] and [SWS_Dem_01082]) till the next call of
               * the Dem_MainFunction. The Dem shall at minimum queue the
               * configured size (refer DemMaxNumberEventEntryEventBuffer).
               * In case the queue is fullDem_SetEventStatus shall return
               * E_NOT_OK.
               */
              if (Dem_GucReportIndex < DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER)
              {
                /* @Trace: Dem_SUD_API_12421 */
                if (DEM_NO_EVENT == Dem_GaaEventEDCBuffer[Dem_GucReportIndex])
                {
                  /* @Trace: Dem_SUD_API_12422 */
                  Dem_GaaEventEDCBuffer[Dem_GucReportIndex] = LddEvId;
                  Dem_GaaEventEDCBufferStatus[Dem_GucReportIndex] = LddEvStatus;
                  Dem_GucReportIndex++;
                }
              }
              else
              {
                /* @Trace: Dem_SUD_API_12420 */
                LddRetVal = E_NOT_OK;
              }
              #endif
            }
            /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
          }
          #endif
        }

        if (E_OK == LddRetVal)
        {
          Dem_EventParameterCPCType LddEvent = &Dem_Event[LddEvId - DEM_ONE];
          uint8 LucDebounceType = DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(
              LddEvent->ParamFieldsA);
          /********************************************************************
           *                 Process event debouncing                         *
           ****************************************************************** */
          /* @Trace: Dem_SUD_API_12423 */
          if (DEM_DEBOUNCE_NO_DEBOUNCE_BASED != LucDebounceType)
          {
            /* @Trace: Dem_SUD_API_12424 */
            #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
            /* @Trace: SWS_Dem_01279
             * The Dem shall perform the counter based event debouncing
             * synchronously within the context of the calling
             * Dem_SetEventStatus function. */

            /* @Trace: SWS_Dem_01209
             * The Dem shall perform the configured debouncing independently
             * from the setting of the configuration parameter
             * DemEventRecoverableInSameOperationCycle.
             * I.e. if DemEventRecoverableInSameOperationCycle is set to FALSE
             * and the monitor for this event reports PREPASSED the Dem shall
             * still process the debouncing (e.g. decrement the counter).
             */
            /* @Trace: Dem_SUD_API_12425 */
            if (DEM_DEBOUNCE_COUNTER_BASED == LucDebounceType)
            {
              /* @Trace: SWS_Dem_00654
               * If the configuration parameter DemDebounceBehavior is set to
               * DEM_DEBOUNCE_RESET and the function Dem_SetEnableCondition
               * (refer to chapter 7.7.6) sets one configured enable condition
               * for the event to not fulfilled, it shall reset the related
               * fault detection counter(s).
               * */

              /* @Trace: SWS_Dem_00677
               * If the configuration parameter DemDebounceBehavior is set
               * to DEM_DEBOUNCE_RESET, the function Dem_DisableDTCSetting
               * (refer to chapter 7.11.2.6) shall reset the related fault
               * detection counter(s).
               * */
              P2CONST(Dem_PreDebounceCounterType, AUTOMATIC, DEM_CONST) LddDcb
                 = &Dem_GaaPreDebounceCounter[LddEvent->ucIndexOfDebounceAry];
              if (E_NOT_OK ==
                    Dem_GetEventConditionsAndControlDTCSetting(LddEvId))
              {
                if (DEM_DEBOUNCE_RESET == LddDcb->eDemDebounceBehavior)
                {
                  /* @Trace: Dem_SUD_API_12427 */
                  Dem_ResetFaultDectectionCounter(LddEvId);
                }
                else /* DEM_DEBOUNCE_FREEZE */
                {
                    /* @Trace: Dem_SUD_API_12428 */
                    /* do nothing */
                }
              }
              else if ((boolean) DEM_FALSE == Dem_ProcessDebounceCounterBased(
                  LddEvent->ucIndexOfDebounceAry, &LddEvStatus))
              {
                /* @Trace: Dem_SUD_API_12426 */
                /* @Trace: Dem_SUD_API_12429 */
                /* LddEvStatus = DEM_EVENT_STATUS_UNDEFINED; */
              }
              else
              {
                /* @Trace: Dem_SUD_API_12431 */
                /* Nothing to do */
              }
            }
            #endif
          }

          /* qualified as PASSED */
          Std_ReturnType LddResult = E_OK;
          Dem_MonitorStatusType LddMonitorStatusByteOld =
              Dem_AllMonitorStatus[LddEvId];

          #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
          /* @Trace: Dem_SUD_API_12433 */
          const Dem_UdsStatusByteType LddDTCStatusByteOld =
              Dem_GetDTCStatus(LddEvId);
          uint8 LucTestFailedThisOpCycle = (uint8) (LddDTCStatusByteOld
              & (Dem_UdsStatusByteType) DEM_UDS_STATUS_TFTOC);
          #else /* combination is disabled or type 2 */
          /* @Trace: Dem_SUD_API_12432 */
          const Dem_UdsStatusByteType LddEventStatusByteOld =
              Dem_AllEventStatusByte[LddEvId];
          uint8 LucTestFailedThisOpCycle = (uint8) (LddEventStatusByteOld &
              (Dem_UdsStatusByteType) DEM_UDS_STATUS_TFTOC);
          #endif
          Dem_NumOfEventMemoryEntryType LddMemLocOld =
              Dem_EvMemToEventMap[LddEvId];
          Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(LddEvId);
          /* @Trace: SWS_Dem_01208
           * If the configuration parameter
           * DemEventRecoverableInSameOperationCycle is set to FALSE, report
           * of PASSED will be ignored if the event status byte has the
           * "TestFailedThisOperationCycle" flag is set to 1.*/

          /* @Trace: SWS_Dem_01280
           * Upon call of Dem_SetEventStatus and after debouncing, the Dem shall
           * process the monitor status in the same manner as the UDS status
           * Bit0 (TestFailed) and Bit1 (TestNotCompleteThisOperationCycle)*/
          if ((
            /* (DEM_FALSE != event->blEventRecoverableInSameOperationCycle) && */
               (DEM_ONE != LucTestFailedThisOpCycle)) &&
               ((DEM_EVENT_STATUS_PASSED == LddEvStatus) &&
               ((DEM_IS_BIT_SET_MONITORSTATUSBYTE(LddEvId,
                   DEM_MONITOR_STATUS_TF)) ||
                (DEM_IS_BIT_SET_MONITORSTATUSBYTE(LddEvId,
                    DEM_MONITOR_STATUS_TNCTOC)))))
          {
            /* @Trace: Dem_SUD_API_12434 */
            /* Clears Bit0: TestFailed to 0 */
            /* Clears bit6: TestNotCompletedThisOperationCycle to 0*/
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            DEM_CLR_MONITORSTATUSBYTE(LddEvId, (Dem_MonitorStatusType)
                DEM_MONITOR_STATUS_TF);
            DEM_CLR_MONITORSTATUSBYTE(LddEvId, (Dem_MonitorStatusType)
                DEM_MONITOR_STATUS_TNCTOC);
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
          /* @Trace: SWS_Dem_01280
           * Upon call of Dem_SetEventStatus and after debouncing, the Dem shall
           * process the monitor status in the same manner as the UDS status
           * Bit0 (TestFailed) and Bit1 (TestNotCompleteThisOperationCycle)*/
          else if ((DEM_EVENT_STATUS_FAILED == LddEvStatus) &&
                  ((DEM_IS_BIT_UNSET_MONITORSTATUSBYTE(LddEvId,
                      DEM_MONITOR_STATUS_TF))              ||
                   (DEM_IS_BIT_SET_MONITORSTATUSBYTE(LddEvId,
                       DEM_MONITOR_STATUS_TNCTOC))         ||
                  ((NULL_PTR != LddCbDTC) &&
                   (DEM_NO_EVMEM_ENTRY == LddMemLocOld))))  /* Not stored */
          {
            /* @Trace: Dem_SUD_API_12435 */
            /* Sets Bit0: TestFailed to 1 */
            /* Clears bit6: TestNotCompletedThisOperationCycle to 0*/
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            DEM_SET_MONITORSTATUSBYTE(LddEvId, (Dem_MonitorStatusType)
                DEM_MONITOR_STATUS_TF);
            DEM_CLR_MONITORSTATUSBYTE(LddEvId, (Dem_MonitorStatusType)
                DEM_MONITOR_STATUS_TNCTOC);
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
          else if ((DEM_EVENT_KIND_BSW == Dem_GetEventKind(LddEvId)) &&
                   (DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED == LddEvStatus))
          {
            /* @Trace: Dem_SUD_API_12436 */
            LddResult = E_NOT_OK;
          }
          else
          {
            /* @Trace: Dem_SUD_API_12438 */
            /* Nothing to do */
          }
          /* @Trace: SWS_Dem_01282
           * Upon processing the monitor status, the Dem shall call the monitor
           * status changed callback functions:
           * <Module>_DemTriggerOnMonitorStatus
           * whenever the monitor status has changed. */
          /* @Trace: Dem_SUD_API_12437 */
          if (LddMonitorStatusByteOld != Dem_AllMonitorStatus[LddEvId])
          {
            /* @Trace: Dem_SUD_API_12439 */
            DemTriggerCallbackOnMonitorStatus(LddEvId);
          }
          /* @Trace: Dem_SUD_API_12440 */
          if (E_NOT_OK != LddResult)
          {
            LddRetVal = E_NOT_OK;
            if (DEM_EVENT_KIND_BSW == Dem_GetEventKind(LddEvId))
            {
              /* @Trace: Dem_SUD_API_12444 */
              #if (DEM_BSW_ERROR_BUFFER_SIZE > DEM_ZERO)
              SchM_Enter_Dem_REQUEST_BUFFER_PROTECTION();
              /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition
               * always evaluates to true */
              /* @Trace: Dem_SUD_API_12445 */
              if (Dem_GucErrorWriteIndex < DEM_BSW_ERROR_BUFFER_SIZE)
              {
                /* Check if the error buffer is empty */
                /* @Trace: Dem_SUD_API_12446 */
                if (DEM_NO_EVENT == Dem_GaaErrorBuffer[Dem_GucErrorWriteIndex])
                {
                  /* Load the event into the buffer */
                  Dem_GaaErrorBuffer[Dem_GucErrorWriteIndex] = LddEvId;
                  Dem_GaaErrorBufferStatus[Dem_GucErrorWriteIndex] =
                      LddEvStatus;

                  /* Check if the buffer is full */
                  Dem_GucErrorWriteIndex++;
                  /* @Trace: Dem_SUD_API_12447 */
                  if (Dem_GucErrorWriteIndex >= DEM_BSW_ERROR_BUFFER_SIZE)
                  {
                    /* @Trace: Dem_SUD_API_12448 */
                    /* Initialize the buffer to zero */
                    Dem_GucErrorWriteIndex = DEM_ZERO;
                  }
                  LddRetVal = E_OK;
                }
              }
              SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();
              #endif
            }
            else if (DEM_EVENT_KIND_SWC == Dem_GetEventKind(LddEvId))
            {
              /* @Trace: Dem_SUD_API_12442 */
              LddRetVal = Dem_ProcessEventStatus(LddEvId, LddEvStatus);
            }
            else
            {
              /* @Trace: Dem_SUD_API_12443 */
              /* Nothing to do */
            }
          }
        }
      }
    }
  }
  return LddRetVal;
}
/*******************************************************************************
** Function Name        : Dem_SetEventStatusWithMonitorData                   **
**                                                                            **
** Service ID           : 0xbd                                                **
**                                                                            **
** Description          : None                                                **
**                                                                            **
** Sync/Async           : Synchronous/Asynchronous                            **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId,                            **
**                        Dem_EventStatusType EventStatus                     **
**                        Dem_MonitorDataType monitorData0                    **
**                        Dem_MonitorDataType monitorData1                    **
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
**                        Dem_GaaPreDebounceTimeBased                         **
**                        Dem_GaaDebouncingCompleteBuffer                     **
**                        Dem_MonitorStatus                                   **
**                        Dem_GaaErrorBuffer                                  **
**                        Dem_GaaErrorBufferStatus                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_BSW_00337 SRS_BSW_00339 SRS_Diag_04001 SRS_Diag_04067
           SRS_Diag_04068 SRS_Diag_04124 SRS_Diag_04125 SRS_Diag_04126
           SRS_Diag_04127 SRS_Diag_04129 SRS_Diag_04137 SRS_Diag_04151
           SRS_Diag_04165
 */
/* @Trace: Dem_SUD_MACRO_052 */
/* polyspace-begin MISRA-C3:8.3 MISRA-C3:8.4 MISRA-C3:8.5 [Justified:Low] Justify with annotations */
/* polyspace-begin DEFECT:DECL_MISMATCH CERT-C:DCL40-C [Justified:Low] Justify with annotations */
/* polyspace +1 CODE-METRICS:VG CODE-METRICS:LEVEL CODE-METRICS:CALLS CODE-METRICS:CALLING CODE-METRICS:FXLN CODE-METRICS:PATH [Not a defect:LOW] "Not a defect" */ 
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatusWithMonitorData(
    Dem_EventIdType EventId,
    Dem_EventStatusType EventStatus,
    Dem_MonitorDataType monitorData0,
    Dem_MonitorDataType monitorData1)
/* polyspace-end MISRA-C3:8.3 MISRA-C3:8.4 MISRA-C3:8.5 [Justified:Low] Justify with annotations */
/* polyspace-end DEFECT:DECL_MISMATCH CERT-C:DCL40-C [Justified:Low] Justify with annotations */
{
  Dem_EventStatusType LddEvStatus = EventStatus;
  /* @Trace: SWS_Dem_01333
   * The API Dem_SetEventStatusWithMonitorData shall have the same functionality
   * as Dem_SetEventStatus with the only difference that it provides further
   * parameters with data to store in an event related data.
   */
  /* @Trace: SWS_Dem_00330
   * The Dem module shall provide the capability to report the status of an
   * event allowing a diagnostic monitor to inform the Dem about the result
   * of the internal diagnostic test (refer to Dem_SetEventStatus).
   */
  Std_ReturnType LddRetVal = E_NOT_OK;
  boolean LblIsBit0GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_0);
  boolean LblIsBit1GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_1);
  boolean LblIsBit2GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_2);
  boolean LblIsBit3GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_3);
  boolean LblIsBit4GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_4);
  boolean LblIsBit5GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_5);
  boolean LblIsBit6GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_6);
  boolean LblIsBit7GetTransit = Dem_EvIsUdsProcStateTriggered(EventId,
    DEM_UDSPROCSTATE_TRANSITION_BIT_7);
  if ((DEM_NO_EVENT == EventId) || (EventId > DEM_NUMBER_OF_EVENTS))
  {
    /* @Trace: Dem_SUD_API_10711 */
    DEM_REPORT_ERROR(DEM_SETEVENTSTATUSWITHMONITORDATA_SID, DEM_E_PARAM_CONFIG);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if ((boolean) DEM_FALSE == Dem_EventStatusIsValid(LddEvStatus))
  {
    /* @Trace: Dem_SUD_API_10712 */
    DEM_REPORT_ERROR(DEM_SETEVENTSTATUSWITHMONITORDATA_SID, DEM_E_PARAM_DATA);
    /* @LddRetVal = E_NOT_OK; */
  }
  else if ((DEM_TRUE == LblIsBit0GetTransit) ||
           (DEM_TRUE == LblIsBit1GetTransit) ||
           (DEM_TRUE == LblIsBit2GetTransit) ||
           (DEM_TRUE == LblIsBit3GetTransit) ||
           (DEM_TRUE == LblIsBit4GetTransit) ||
           (DEM_TRUE == LblIsBit5GetTransit) ||
           (DEM_TRUE == LblIsBit6GetTransit) ||
           (DEM_TRUE == LblIsBit7GetTransit))
  {
    /* @Trace: Dem_SUD_API_12451 */
    /* @Trace: SWS_Dem_01286
     * If the API Dem_SetEventStatus is called and the Dem has synchronously
     * processed the reported monitor status according to [SWS_Dem_01280] and
     * the corresponding UDS status (see [SWS_Dem_01285]) cannot be processed,
     * the Dem shall report the development error
     * DEM_E_UDS_STATUS_PROCESSING_FAILED.
     */
    DEM_REPORT_ERROR(DEM_SETEVENTSTATUSWITHMONITORDATA_SID,
        DEM_E_UDS_STATUS_PROCESSING_FAILED);
  }
  else
  {
    /* @Trace: Dem_SUD_API_12462 */
    #if ((DEM_DEV_ERROR_DETECT == STD_ON) && \
        (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO))
    /* @Trace: Dem_SUD_API_30004 */
    Dem_NumOfDebounceType LddDebounceId = Dem_Event[EventId - DEM_ONE].
        ucIndexOfDebounceAry;
    P2CONST(Dem_PreDebounceCounterType, AUTOMATIC, DEM_CONST) LddPreDBC =
        &Dem_GaaPreDebounceCounter[LddDebounceId];
    uint8 LucDbType = DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(
        Dem_Event[EventId - DEM_ONE].ParamFieldsA);
    #endif
    /* @Trace: SWS_Dem_00676
     * If development error detection is enabled and
     * Dem_SetEventStatus or Dem_ResetEventDebounceStatus is called before
     * Dem_Init or after Dem_Shutdown for events which have DemDebounce-
     * CounterStorage set to True, the Dem module shall set the error code
     * DEM_E_WRONG_CONDITION. */
    /* @Trace: Dem_SUD_API_12517 */
    #if ((DEM_DEV_ERROR_DETECT == STD_ON) && \
        (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO))

    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
    /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
    if ((DEM_DEBOUNCE_COUNTER_BASED == LucDbType) &&
        (DEM_TRUE == (LddPreDBC->blDemDebounceCounterStorage)) &&
        (DEM_INIT != Dem_GucInit)
    )
    {
      /* @Trace: Dem_SUD_API_10713 */
      DEM_REPORT_ERROR(
          DEM_SETEVENTSTATUSWITHMONITORDATA_SID, DEM_E_WRONG_CONDITION);
      /* LddRetVal = E_NOT_OK */
    }
    else
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
    /* @Trace: Dem_SUD_API_12519 */
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
      /* @Trace: Dem_SUD_API_12455 */
      #if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
      uint8 LucIdxOfMasterEvent = Dem_GetIndexOfMasterEventByEventId(LddEvId);
      boolean LblIdxOfMasterEventIsFound = DEM_FALSE;
      /* @Trace: Dem_SUD_API_12456 */
      if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING != LucIdxOfMasterEvent)
      {
        /* @Trace: Dem_SUD_API_12457 */
        LucStartIdx = Dem_DemMultiEventTrg[LucIdxOfMasterEvent].slaveEventIdx;
        LucStopIdx = LucStartIdx +
            Dem_DemMultiEventTrg[LucIdxOfMasterEvent].numberOfSlaveEvent;
        LblIdxOfMasterEventIsFound = DEM_TRUE;
      }
      #endif
      /* Report status for all salve event related from master event id */
      /* @Trace: Dem_SUD_API_12458 */
      for (; LucStartIdx < LucStopIdx; LucStartIdx++)
      {
        /* @Trace: Dem_SUD_API_12459 */
        #if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
        /* @Trace: Dem_SUD_API_12460 */
        if (DEM_TRUE == LblIdxOfMasterEventIsFound)
        {
          /* @Trace: Dem_SUD_API_12461 */
          LddEvId = Dem_ListOfSlaveEventTrg[LucStartIdx];
        }
        #endif
        /* @Trace: SWS_Dem_01091
         * Dem_SetEventStatus shall ignore the replacement event.
         */
        /* @Trace: Dem_SUD_API_12463 */
        #if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
        boolean LblIsReplacementEvent = DEM_FALSE;
        /* @Trace: Dem_SUD_API_12464 */
        for ( uint8 LucStorageConditionIdx = DEM_ZERO;
              LucStorageConditionIdx < DEM_NUMBER_STORAGE_CONDITION;
              LucStorageConditionIdx++ )
        {
          /* @Trace: Dem_SUD_API_12465 */
          if (DEM_NO_EVENT_INDEX !=
                Dem_GaaStorageCondition[LucStorageConditionIdx].ucDemEventIdx)
          {
            /* @Trace: Dem_SUD_API_12466 */
            if (LddEvId ==
                  Dem_GaaStorageCondition[LucStorageConditionIdx].ucDemEventIdx)
            {
              /* @Trace: Dem_SUD_API_12467 */
              LblIsReplacementEvent = DEM_TRUE;
              break;
            }
          }
        }
        if (DEM_FALSE != LblIsReplacementEvent)
        {
          /* @Trace: Dem_SUD_API_12469 */
          /* LddRetVal = E_NOT_OK; */
        }
        else
        /* @Trace: Dem_SUD_API_12468 */
        #endif
        /* @Trace: SWS_Dem_00368
         * If development error detection is enabled and any instance calls any
         * Dem API, excluding Dem_SetEventStatus, Dem_ResetEventDebounceStatus,
         * Dem_GetVersionInfo and Dem_MainFunction, after Dem_Shutdown has been
         * called, the Dem module shall set the error code DEM_E_UNINIT
         * until Dem_Init is called again.
         */
        if ((DEM_EVENT_KIND_BSW == Dem_GetEventKind(LddEvId)) &&
            (DEM_UNINIT == Dem_GucInit))
        {
          /* @Trace: Dem_SUD_API_12470 */
          DEM_REPORT_ERROR(DEM_SETEVENTSTATUSWITHMONITORDATA_SID, DEM_E_UNINIT);
          /* @LddRetVal = E_NOT_OK; */
        }
        else if ((DEM_EVENT_KIND_SWC == Dem_GetEventKind(LddEvId)) &&
                 (DEM_INIT != Dem_GucInit))
        {
          /* @Trace: Dem_SUD_API_12471 */
          DEM_REPORT_ERROR(DEM_SETEVENTSTATUSWITHMONITORDATA_SID, DEM_E_UNINIT);
          /* @LddRetVal = E_NOT_OK; */
        }
        /* @Trace: Dem_SUD_API_12474 */
        #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
        else if ( DEM_TRUE != Dem_EvIsProcStateTriggered(LddEvId,
                   DEM_EVPROCSTATE_EVENT_AVAILABLE))
        {
          /* @Trace: Dem_SUD_API_12472 */
          /* @Trace: SWS_Dem_01108
           * If an event is set to unavailable, the corresponding event shall
           * be treated as if it is not configured in the system (e.g.
           * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return
           * E_NOT_OK). */
          /* LddRetVal = E_NOT_OK; */
        }
        #endif
        else
        {
          /* @Trace: Dem_SUD_API_12518 */
          Dem_OperationCycleStateType LddOpCycleState =
              (Dem_OperationCycleStateType)DEM_CYCLE_STATE_NOTSTART;

          /* Note: If Power cycle (DEM_OPCYC_POWER) should not be ended/stopped
           * during 'ECU Sleep' then it should be configured with
           * DemOperationCycleStatusStorage == TRUE.
           *
           * if DemOperationCycleStatusStorage is true then state is stored,
           * so Bsw Events always able to be processed regardless Dem Init
           * State */
          (void)Dem_GetOpCycleStateByEvent(LddEvId, &LddOpCycleState);
          /* @Trace: Dem_SUD_API_12475 */
          if ((DEM_CYCLE_STATE_START == LddOpCycleState))
          {
             /* @Trace: Dem_SUD_API_12476 */
              LddRetVal = E_OK;
          }
          /* @Trace: Dem_SUD_API_12477 */
          #if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
          /* @Trace: SWS_Dem_00805
           * If the configuration parameter DemEnvironmentDataCapture is set
           * to DEM_CAPTURE_SYNCHRONOUS_TO_REPORTING (refer to
           * DemPrimaryMemory or DemUserDefinedMemory) and
           * DemDebounceTimeBasedSupport is set to "false", event-specific
           * freeze frame data shall be captured within the reporting function
           * (i.e. in the context of Dem_SetEventStatus).
           */
          /* @Trace: SWS_Dem_01082
           * If the configuration parameter DemEnvironmentDataCapture is set to
           * DEM_CAPTURE_SYNCHRONOUS_TO_REPORTING (refer to DemPrimaryMemory
           * or DemUserDefinedMemory), event-specific extended data shall be
           * captured within the context of Dem_SetEventStatus.
           */
          /* @Trace: Dem_SUD_API_12478 */
          if (( DEM_DTC_ORIGIN_PRIMARY_MEMORY ==
                  Dem_Event[LddEvId - DEM_ONE].aaEventDestination) ||
              (DEM_DTCORGIN_USER_DEFINED_IS_VALID(
                  Dem_Event[LddEvId - DEM_ONE].aaEventDestination)))
          {
            Std_ReturnType LddResult = E_NOT_OK;
            /* @Trace: Dem_SUD_API_12479 */
            if ( DEM_NO_EVMEM_IDX != Dem_Event[LddEvId - DEM_ONE].
                        ucEventMemDstIdx)
            {
              /* @Trace: Dem_SUD_API_12480 */
              #if (DEM_MAX_NUMBER_PRIMARY_MEMORY > DEM_ZERO)
              #if (DEM_ALL_CAPTURED_DATA_CONFIGURED_SYNCHRONOUS_TO_REPORTING == STD_ON)
              LddResult = E_OK;
              #else /* DEM_ALL_CAPTURED_DATA_CONFIGURED_SYNCHRONOUS_TO_REPORTING == STD_ON */
              /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
              /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Configuration. */
              /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
              if ( DEM_CAPTURE_SYNCHRONOUS_TO_REPORTING ==
                  Dem_GaaDemPrimaryMemory[Dem_Event[LddEvId - DEM_ONE].
                                          ucEventMemDstIdx].
                                          usDemEnvironmentDataCapture )
              
              {
                /* @Trace: Dem_SUD_API_12481 */
                LddResult = E_OK;
              }
              else
              #endif /* DEM_ALL_CAPTURED_DATA_CONFIGURED_SYNCHRONOUS_TO_REPORTING == STD_ON */
              #endif /* DEM_MAX_NUMBER_PRIMARY_MEMORY > DEM_ZERO */
              /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
              /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */

              /* @Trace: Dem_SUD_API_12483 */
              #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
              #if (DEM_ALL_CAPTURED_DATA_CONFIGURED_SYNCHRONOUS_TO_REPORTING == STD_ON)
              LddResult = E_OK;
              #else /* DEM_ALL_CAPTURED_DATA_CONFIGURED_SYNCHRONOUS_TO_REPORTING == STD_ON */
              /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
              /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Configuration. */
              /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
              if (DEM_CAPTURE_SYNCHRONOUS_TO_REPORTING ==
                  Dem_GaaDemUserDefinedMemory[Dem_Event[LddEvId - DEM_ONE].
                                              ucEventMemDstIdx].
                                              usDemEnvironmentDataCapture)
              {
                /* @Trace: Dem_SUD_API_12482 */
                LddResult = E_OK;
              }
              else
              #endif /* DEM_ALL_CAPTURED_DATA_CONFIGURED_SYNCHRONOUS_TO_REPORTING == STD_ON */
              #endif /* DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO */
              {
                /* @Trace: Dem_SUD_API_12485 */
                /* Do nothing */
              }
              /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
              /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
            }
            /* @Trace: Dem_SUD_API_12486 */
            
            /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
            /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
            if (E_OK == LddResult)
            {
              /* @Trace: Dem_SUD_API_12487 */
              #if (DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER > DEM_ZERO)
              /* @Trace: SWS_Dem_01083
               * If DemEnvironmentDataCapture is equal to
               * DEM_CAPTURE_ SYNCHRONOUS_TO_REPORTING (refer to
               * DemPrimaryMemory or DemUserDefinedMemory), the Dem module
               * shall queue the environmental data from the reporting (see
               * [SWS_Dem_00805] and [SWS_Dem_01082]) till the next call of
               * the Dem_MainFunction. The Dem shall at minimum queue the
               * configured size (refer DemMaxNumberEventEntryEventBuffer).
               * In case the queue is full Dem_SetEventStatus shall return
               * E_NOT_OK.
               */
              if (Dem_GucReportIndex < DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER)
              {
                /* @Trace: Dem_SUD_API_12488 */
                if (DEM_NO_EVENT == Dem_GaaEventEDCBuffer[Dem_GucReportIndex])
                {
                 /* @Trace: Dem_SUD_API_12489 */
                  Dem_GaaEventEDCBuffer[Dem_GucReportIndex] = LddEvId;
                  Dem_GaaEventEDCBufferStatus[Dem_GucReportIndex] = LddEvStatus;
                  Dem_GucReportIndex++;
                }
              }
              else
              {
                /* @Trace: Dem_SUD_API_12490 */
                LddRetVal = E_NOT_OK;
              }
              #endif
            }
            /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
          }
          #endif
        }
        /* @Trace: Dem_SUD_API_12491 */
        if (E_OK == LddRetVal)
        {
          Dem_EventParameterCPCType LddEvent = &Dem_Event[LddEvId - DEM_ONE];
          uint8 LucDebounceType = DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(
              LddEvent->ParamFieldsA);
          /*********************************************************************
           *                 Process event debouncing                          *
           ********************************************************************/
          /* @Trace: Dem_SUD_API_12492 */
          if (DEM_DEBOUNCE_NO_DEBOUNCE_BASED != LucDebounceType)
          {
            /* @Trace: Dem_SUD_API_12493 */
            #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
            /* @Trace: SWS_Dem_01279
             * The Dem shall perform the counter based event debouncing
             * synchronously within the context of the calling
             * Dem_SetEventStatus function. */

            /* @Trace: SWS_Dem_01209
             * The Dem shall perform the configured debouncing independently
             * from the setting of the configuration parameter
             * DemEventRecoverableInSameOperationCycle.
             * I.e. if DemEventRecoverableInSameOperationCycle is set to FALSE
             * and the monitor for this event reports PREPASSED the Dem shall
             * still process the debouncing (e.g. decrement the counter).
             */
            /* @Trace: Dem_SUD_API_12494 */
            if (DEM_DEBOUNCE_COUNTER_BASED == LucDebounceType)
            {
              /* @Trace: SWS_Dem_00654
               * If the configuration parameter DemDebounceBehavior is set to
               * DEM_DEBOUNCE_RESET and the function Dem_SetEnableCondition
               * (refer to chapter 7.7.6) sets one configured enable condition
               * for the event to not fulfilled, it shall reset
               * the related fault detection counter(s).
               * */

              /* @Trace: SWS_Dem_00677
               * If the configuration parameter DemDebounceBehavior is set
               * to DEM_DEBOUNCE_RESET, the function Dem_DisableDTCSetting
               * (refer to chapter 7.11.2.6) shall reset the related fault
               * detection counter(s).
               * */
              P2CONST(Dem_PreDebounceCounterType, AUTOMATIC, DEM_CONST) LddDcb
                 = &Dem_GaaPreDebounceCounter[LddEvent->ucIndexOfDebounceAry];
              if (E_NOT_OK ==
                    Dem_GetEventConditionsAndControlDTCSetting(LddEvId))
              {
                if (DEM_DEBOUNCE_RESET == LddDcb->eDemDebounceBehavior)
                {
                  /* @Trace: Dem_SUD_API_12497 */
                  Dem_ResetFaultDectectionCounter(LddEvId);
                }
                else /* DEM_DEBOUNCE_FREEZE */
                {
                  /* @Trace: Dem_SUD_API_12498 */
                  /* do nothing */
                }
              }
              else if ((boolean) DEM_FALSE == Dem_ProcessDebounceCounterBased(
                  LddEvent->ucIndexOfDebounceAry, &LddEvStatus))
              {
                /* @Trace: Dem_SUD_API_12496 */
                /* @Trace: Dem_SUD_API_12499 */
                /* LddEvStatus = DEM_EVENT_STATUS_UNDEFINED; */
              }
              else
              {
                /* @Trace: Dem_SUD_API_12500 */
                /* Nothing to do */
              }
            }
            #endif
          }

          /* qualified as PASSED */
          Std_ReturnType LddResult = E_OK;
          Dem_MonitorStatusType LddMonitorStatusByteOld =
              Dem_AllMonitorStatus[LddEvId];

          #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
          /* @Trace: Dem_SUD_API_12502 */
          const Dem_UdsStatusByteType LddDTCStatusByteOld =
              Dem_GetDTCStatus(LddEvId);
          uint8 LucTestFailedThisOpCycle = (uint8) (LddDTCStatusByteOld &
              (Dem_UdsStatusByteType) DEM_UDS_STATUS_TFTOC);
          #else /* combination is disabled or type 2 */
          /* @Trace: Dem_SUD_API_12501 */
          const Dem_UdsStatusByteType LddEventStatusByteOld =
              Dem_AllEventStatusByte[LddEvId];
          uint8 LucTestFailedThisOpCycle = (uint8) (LddEventStatusByteOld &
              (Dem_UdsStatusByteType) DEM_UDS_STATUS_TFTOC);
          #endif
          Dem_NumOfEventMemoryEntryType LddMemLocOld =
              Dem_EvMemToEventMap[LddEvId];
          Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(LddEvId);
          /* @Trace: SWS_Dem_01208
           * If the configuration parameter
           * DemEventRecoverableInSameOperationCycle is set to FALSE, report
           * of PASSED will be ignored if the event status byte has the
           * "TestFailedThisOperationCycle" flag is set to 1.*/

          /* @Trace: SWS_Dem_01280
           * Upon call of Dem_SetEventStatus and after debouncing, the Dem shall
           * process the monitor status in the same manner as the UDS status
           * Bit0 (TestFailed) and Bit1 (TestNotCompleteThisOperationCycle)*/
          if ((
            /* (DEM_FALSE != event->blEventRecoverableInSameOperationCycle) &&*/
               (DEM_ONE != LucTestFailedThisOpCycle))    &&
               ((DEM_EVENT_STATUS_PASSED == LddEvStatus) &&
               ((DEM_IS_BIT_SET_MONITORSTATUSBYTE(LddEvId,
                   DEM_MONITOR_STATUS_TF)) ||
               (DEM_IS_BIT_SET_MONITORSTATUSBYTE(LddEvId,
                   DEM_MONITOR_STATUS_TNCTOC)))))
          {
            /* @Trace: Dem_SUD_API_12503 */
            /* Clears Bit0: TestFailed to 0 */
            /* Clears bit6: TestNotCompletedThisOperationCycle to 0*/
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            DEM_CLR_MONITORSTATUSBYTE(LddEvId, (Dem_MonitorStatusType)
                DEM_MONITOR_STATUS_TF);
            DEM_CLR_MONITORSTATUSBYTE(LddEvId, (Dem_MonitorStatusType)
                DEM_MONITOR_STATUS_TNCTOC);
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
          /* @Trace: SWS_Dem_01280
           * Upon call of Dem_SetEventStatus and after debouncing, the Dem shall
           * process the monitor status in the same manner as the UDS status
           * Bit0 (TestFailed) and Bit1 (TestNotCompleteThisOperationCycle)*/
          else if ((DEM_EVENT_STATUS_FAILED == LddEvStatus) &&
                  ((DEM_IS_BIT_UNSET_MONITORSTATUSBYTE(LddEvId,
                      DEM_MONITOR_STATUS_TF)) ||
                   (DEM_IS_BIT_SET_MONITORSTATUSBYTE(LddEvId,
                       DEM_MONITOR_STATUS_TNCTOC)) ||
                  ((NULL_PTR != LddCbDTC) &&
                   (DEM_NO_EVMEM_ENTRY == LddMemLocOld))))  /* Not stored */
          {
            /* @Trace: Dem_SUD_API_12504 */
            /* Sets Bit0: TestFailed to 1 */
            /* Clears bit6: TestNotCompletedThisOperationCycle to 0*/
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            DEM_SET_MONITORSTATUSBYTE(LddEvId, (Dem_MonitorStatusType)
                DEM_MONITOR_STATUS_TF);
            DEM_CLR_MONITORSTATUSBYTE(LddEvId, (Dem_MonitorStatusType)
                DEM_MONITOR_STATUS_TNCTOC);
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
          else if ((DEM_EVENT_KIND_BSW == Dem_GetEventKind(LddEvId)) &&
                   (DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED == LddEvStatus))
          {
            /* @Trace: Dem_SUD_API_12505 */
            LddResult = E_NOT_OK;
          }
          else
          {
            /* @Trace: Dem_SUD_API_12507 */
            /* Nothing to do */
          }
          /* @Trace: SWS_Dem_01282
           * Upon processing the monitor status, the Dem shall call the monitor
           * status changed callback functions:
           * <Module>_DemTriggerOnMonitorStatus
           * whenever the monitor status has changed. */
          if (LddMonitorStatusByteOld != Dem_AllMonitorStatus[LddEvId])
          {
            /* @Trace: Dem_SUD_API_12508 */
            DemTriggerCallbackOnMonitorStatus(LddEvId);
          }
          /* @Trace: Dem_SUD_API_12509 */
          if (E_NOT_OK != LddResult)
          {
            LddRetVal = E_NOT_OK;
            if (DEM_EVENT_KIND_BSW == Dem_GetEventKind(LddEvId))
            {
              /* @Trace: Dem_SUD_API_12511 */
              #if (DEM_BSW_ERROR_BUFFER_SIZE > DEM_ZERO)
              SchM_Enter_Dem_REQUEST_BUFFER_PROTECTION();
              /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition
               * always evaluates to true */
              /* @Trace: Dem_SUD_API_12512 */
              if (Dem_GucErrorWriteIndex < DEM_BSW_ERROR_BUFFER_SIZE)
              {
                /* Check if the error buffer is empty */
                /* @Trace: Dem_SUD_API_12513 */
                if (DEM_NO_EVENT == Dem_GaaErrorBuffer[Dem_GucErrorWriteIndex])
                {
                  /* Load the event into the buffer */
                  Dem_GaaErrorBuffer[Dem_GucErrorWriteIndex] = LddEvId;
                  Dem_GaaErrorBufferStatus[Dem_GucErrorWriteIndex] =
                      LddEvStatus;
                  Dem_MonitorData[LddEvId].usMonitorData0 = monitorData0;
                  Dem_MonitorData[LddEvId].usMonitorData1 = monitorData1;
                  /* Check if the buffer is full */
                  Dem_GucErrorWriteIndex++;
                  /* @Trace: Dem_SUD_API_12514 */
                  if (Dem_GucErrorWriteIndex >= DEM_BSW_ERROR_BUFFER_SIZE)
                  {
                    /* Initialize the buffer to zero */
                    Dem_GucErrorWriteIndex = DEM_ZERO;
                  }
                  LddRetVal = E_OK;
                }
              }
              SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();
              #endif
            }
            else if (DEM_EVENT_KIND_SWC == Dem_GetEventKind(LddEvId))
            {
              /* @Trace: Dem_SUD_API_12516 */
              /* @Trace: Dem_SUD_API_12510 */
              Dem_MonitorData[LddEvId].usMonitorData0 = monitorData0;
              Dem_MonitorData[LddEvId].usMonitorData1 = monitorData1;
              (void) Dem_ProcessEventStatus(LddEvId, LddEvStatus);
              LddRetVal = E_OK;
            }
            else
            {
              /* @Trace: Dem_SUD_API_12515 */
              /* Nothing to do */
            }
          }
        }
      }
    }
  }
  return LddRetVal;
}
#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
