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
**  SRC-MODULE: Dem_EventAging.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provides the interface of varialble data that ara configurable**
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
** 1.0.12.0  12-May-2023   DanhTQ1       R40-Redmine #40627                   **
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

 

/*******************************************************************************
**                     Include Section                                       **
*******************************************************************************/
#include "Dem.h"        /* DEM module Header File */
#include "Dem_Ram.h"    /* DEM Ram Header File */

/* DEM_DEV_ERROR_DETECT is defined in Dem_Cfg.h
 * Dem_Cfg.h is included by Dem.h */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"        /* Det Module Header File */
#endif

#include "SchM_Dem.h"   /* Basic s/w module Scheduler symbols Header File */ 
#include "Rte_Dem.h"
#include "Dem_Event.h"
#include "Dem_Dtc.h"
#include "Dem_EventMemory.h"
#include "Dem_EventCallback.h"
#include "Dem_EventAging.h"

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
 * Function Name        : Dem_EventAgingOnEventPassed
 *
 * Service ID           : None
 *
 * Description          : Process event aging on event passed
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId, DTCOrigin, MemLocation
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *
 * Preconditions        :
 * 
 * Remarks              :
 ******************************************************************************/
/* @Trace: SRS_Diag_04073 SRS_Diag_04141
 */
/* @Trace: Dem_SUD_MACRO_021 */
FUNC(boolean, DEM_CODE) Dem_EventAgingOnEventPassed(
  const Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin,
  Dem_NumOfEventMemoryEntryType MemLocation)
{
  boolean LblAged = DEM_FALSE;
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * Avoid the runtime error of the polyspace */
  /* @Trace: Dem_SUD_API_11435 */
  if ((DEM_NO_EVENT != EventId) && (EventId <= DEM_NUMBER_OF_EVENTS) )
  {
    Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - DEM_ONE];

    /*
     * [1] Aging is supported
     * [2] Threshold for aging shall be equal to 0 (zero)
     * [3] Specific aging cycle is ignored    
     * [4] CombinedDTC's WarningIndicatorRequest bit7 == 0 (SWS_Dem_01053)
     * [5] Event is qualified as passed (this function is called when event is
     *     qualified as passed)
     * [6] TestFailedThisOperationCycle bi is ignored , as soon as event is
     *     qualified as passed
     *     Event shall be aged */

    /* @Trace: SWS_Dem_01176
     * Additional to event aging described in chapter 7.7.8 the event shall be
     * aged after 200 hours of engine operation while the aging conditions are
     * met.
     */
    /* @Trace: Dem_SUD_API_11442 */
    if ((DEM_TRUE == DEM_GET_EVENTPARAM_AGING_ALLOWED(LddEvent->ParamFieldsA))
        &&
        (DEM_ZERO == LddEvent->ucAgingCycleCounterThreshold)
       ) /* [1][2][3] */
    {
      /* @Trace: SWS_Dem_01053
       * If the Dem module is requested to support combination on storage,
       * the aging shall be calculated based on the combined DTC status.
       * So, if combined event is type 1 , Combined DTC Status shall be used
       * during aging */
      #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
      /* @Trace: Dem_SUD_API_11444 */
      const Dem_UdsStatusByteType LddUdsStatusByteOld =
          Dem_GetDTCStatus(EventId);
      #else
      /* @Trace: Dem_SUD_API_11443 */
      /* @Trace: SWS_Dem_00541
       */
      const Dem_UdsStatusByteType LddUdsStatusByteOld =
          Dem_AllEventStatusByte[EventId];
      #endif
      /* @Trace: Dem_SUD_API_11445 */
      if (DEM_ZERO == (uint8)(LddUdsStatusByteOld & (uint8)DEM_UDS_STATUS_WIR))
      /* [4][5][6] */
      {
        Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
        /* @Trace: Dem_SUD_API_11446 */
        #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        Dem_DTCType LddDtcValue = DEM_NO_DTC;
        if (NULL_PTR != LddCbDTC)
        {
          /* @Trace: Dem_SUD_API_11447 */
          LddDtcValue = LddCbDTC->usObdDtc;
        }
        if (DEM_NO_DTC != LddDtcValue)
        {
          /* @Trace: Dem_SUD_API_10816 */
          if (Dem_OBDOldEngStartInfo > DEM_TWO_HUNDRED)
          {
            /* @Trace: Dem_SUD_API_11449 */
            LblAged = DEM_TRUE;
          }
        }
        else
        #endif
        {
          /* @Trace: Dem_SUD_API_11448 */
          LblAged = DEM_TRUE;
        }
        /* @Trace: Dem_SUD_API_10817 */
        /* polyspace+1 MISRA-C3:14.3 [Justified:Low] "The returnValue may be changed in second config." */
        #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        if (DEM_TRUE == LblAged)
        #endif
        {
          Dem_EventMemoryEntryPtrType LddMemEntry =
              Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, MemLocation);
          /* @Trace: Dem_SUD_API_10818 */
          if (NULL_PTR != LddMemEntry)
          {
            /* @Trace: Dem_SUD_API_11436 */
            Dem_EvMem_AgingEvMemEntry(EventId, DTCOrigin, LddMemEntry);
          }
          /* @Trace: Dem_SUD_API_11441 */
          if (NULL_PTR != LddCbDTC) /* Always true */
          {
            Dem_EvMem_SetEvMemNvBlockStatus(
                DTCOrigin, MemLocation, LddCbDTC->EvMemTriggerFlag);
            /* @Trace: Dem_SUD_API_11437 */
            #if (DEM_UDS_STATUS_IN_EVENT_NVBLOCK == STD_ON)
            /* @Trace: Dem_SUD_API_11438 */
            Dem_EvMem_SetNonVolatieDataStatus(
                DEM_NVDATA_ALL_EVENT_STATUS_ID, LddCbDTC->EvMemTriggerFlag);
            #endif
            /* @Trace: Dem_SUD_API_11439 */
            /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
            if (DEM_EVMEM_STATUS_DIRTY_NVM == LddCbDTC->EvMemTriggerFlag)
            {
              /* @Trace: Dem_SUD_API_11440 */
              Dem_EvMem_TriggerWriteAllBlocks();
            }
            /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
          }
        }
      } 
    }
  }

  return LblAged;
}

/*******************************************************************************
** Function Name        : Dem_EventAgingOnOperationCycleChanged               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Process event aging on operation cycle changed      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId, MemEntry, DTCOrigin, OperationCycleId      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04067 SRS_Diag_04068 SRS_Diag_04073 SRS_Diag_04133
           SRS_Diag_04141 SRS_Diag_04178
 */
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
FUNC(void, DEM_CODE) Dem_EventAgingOnOperationCycleChanged(
  Dem_EventIdType EventId,
  Dem_EventMemoryEntryPtrType MemEntry,
  const Dem_DTCOriginType DTCOrigin,
  const uint8 OperationCycleId)
{
  boolean LblEventIsAged = DEM_FALSE;
  uint8 LucEvStatusBlkState = DEM_EVMEM_STATUS_DIRTY;
  Dem_NumOfEventMemoryEntryType LddMemLoc = Dem_EvMemToEventMap[EventId];
  /* @Trace: Dem_SUD_API_11450 */
  if (NULL_PTR != MemEntry) /* Always true */
  {
    /* @Trace: Dem_SUD_API_11461 */
    #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
    /* @Trace: Dem_SUD_API_11472 */
    uint32 LulMaxTimeStamp = DEM_ZERO;
    #endif
    /* @Trace: Dem_SUD_API_11483 */
    if ((EventId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != EventId))
    {
      /* @Trace: Dem_SUD_API_11487 */
      if ((boolean)DEM_TRUE == Dem_DTCOriginBelongToEvent(EventId, DTCOrigin))
      {
        boolean LblDirty = DEM_FALSE;
        Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];

        /* @Trace: SWS_Dem_01053
         * If the Dem module is requested to support combination on storage,
         * the aging shall be calculated based on the combined DTC status.
         * So, if combined event is type 1 , Combined DTC Status shall be used
         * during aging */
        /* @Trace: Dem_SUD_API_11488 */
        #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
        Dem_UdsStatusByteType LddUDSStatusByte = Dem_GetDTCStatus(EventId);
        #else
        /* @Trace: Dem_SUD_API_11489 */
        Dem_UdsStatusByteType LddUDSStatusByte =
            Dem_AllEventStatusByte[EventId];
        #endif

        /* @Trace: SWS_Dem_00985
         * The aging counter shall be calculated based on the referenced aging/
         * operation cycle (refer to configuration parameter DemAgingCycleRef),
         * if aging is enabled (refer to DemAgingAllowed) for this event. */

        /* @Trace: SWS_Dem_00494
         * The Dem module shall provide the configuration parameter
         * DemAgingCycleRef (refer to DemDTCAttributes) defining the event-
         * specific operation/aging cycle, whose status change triggers the
         * processing (counting further) of the aging counter value.
         */
        /* @Trace: Dem_SUD_API_11490 */
        if ((DEM_TRUE ==
            DEM_GET_EVENTPARAM_AGING_ALLOWED(LddEvent->ParamFieldsA)) &&
            (LddEvent->e_AgingCycleId == OperationCycleId))
        {
          const Dem_TestResultType LddOpTestResult =
              Dem_GetTestResultThisOperation(LddUDSStatusByte,
                  Dem_Aging_Requieres_Tested_Cycle);
          /* @Trace: SWS_Dem_00826
           * If the configuration parameter DemAgingRequieresTestedCycle
           * (refer DemGeneral) set to True, the Dem module shall process (count
           * further) the aging cycle counter value, if the respective aging
           * cycle ends/restarts and the UDS status bit 6
           * (TestNotCompleteThisOperationCycle) is set to zero. */

          /* @Trace: SWS_Dem_01214
           * If the configuration parameter DemAgingRequiresNotFailedCycle is
           * set to true, the aging counter shall only be processed in an
           * operation cycle without a test failed report. */
          /* @Trace: Dem_SUD_MACRO_139 */
          if ((DEM_TRUE == DEM_AGING_REQUIRES_NOT_FAILED_CYCLE) &&
              (DEM_TEST_RESULT_PASSED_THIS_OPERATION == LddOpTestResult))
          {
            /* [1] AgingCycle can be different with a OperationCycle for a event
             * [2] WarningIndicatorRequest bit == 0
             * In case of TYPE1, UDSStatusByte is combined event status */
            /* @Trace: SWS_Dem_00698
             * The process of aging (counting of aging counter) starts when
             * healing is completed
             * (WarningIndicatorRequested bit == 0 , refer to Figure 7.43).
             * WarningIndicatorOnCriteriaFulfilled ? */
            /* @Trace: SWS_Dem_01053, @SWS_Dem_00541
             */
            /* @Trace: Dem_SUD_API_11455 */
            if ((uint8)(LddUDSStatusByte &
                (uint8)DEM_UDS_STATUS_WIR) == DEM_ZERO)
            {
              /* @Trace: Dem_SUD_API_11452 */
              #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
              Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
              Dem_DTCType LddDtcValue = DEM_NO_DTC;
              /* @Trace: Dem_SUD_API_11453 */
              if (NULL_PTR != LddCbDTC)
              {
                /* @Trace: Dem_SUD_API_11454 */
                LddDtcValue = LddCbDTC->usObdDtc;
              }
              #endif
              /* [1] AgingCycle can be different with a OperationCycle for a
               * event.
               * [2] Shall be called when OperationCycle is changed */
              if (DEM_ZERO != LddEvent->ucAgingCycleCounterThreshold)
              {
                uint8 LucAgingCounter = DEM_ZERO;
                LblDirty |= Dem_EvMem_IncAgingCounter(
                    MemEntry, &LucAgingCounter);
                /* Aging Completed */
                /* @Trace: SWS_Dem_01176
                 * Additional to event aging described in chapter 7.7.8 the
                 * event shall be aged after 200 hours of engine operation while
                 * the aging conditions are met.
                 */
                /* @Trace: Dem_SUD_API_11460 */
                if (LucAgingCounter >= LddEvent->ucAgingCycleCounterThreshold)
                {
                  /* @Trace: Dem_SUD_API_11462 */
                  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
                  if (DEM_NO_DTC != LddDtcValue)
                  {
                    /* @Trace: Dem_SUD_API_11464 */
                    if (Dem_OBDOldEngStartInfo > DEM_TWO_HUNDRED)
                    {
                      /* @Trace: Dem_SUD_API_11465 */
                      LblEventIsAged = DEM_TRUE;
                    }
                  }
                  else
                  #endif
                  {
                    /* @Trace: Dem_SUD_API_11463 */
                    LblEventIsAged = DEM_TRUE;
                  }
                }
              }
              else
              {
                /* @Trace: Dem_SUD_API_11456 */
                /* @Trace: Dem_SUD_API_11457 */
                #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
                if (DEM_NO_DTC != LddDtcValue)
                {
                  if (Dem_OBDOldEngStartInfo > DEM_TWO_HUNDRED)
                  {
                    /* @Trace: Dem_SUD_API_11459 */
                    LblEventIsAged = DEM_TRUE;
                  }
                }
                else
                #endif
                {
                  /* @Trace: Dem_SUD_API_11458 */
                  LblEventIsAged = DEM_TRUE;
                }
              }
              /* @Trace: Dem_SUD_API_11466 */
              if (DEM_TRUE == LblEventIsAged)
              {
                /* @Trace: Dem_SUD_API_11467 */
                /* If Dem_Aging_Requieres_Tested_Cycle set to false and Event is
                 * not failed during this operation cycle Event shall be aged.
                 * in case of Dem_Aging_Requieres_Tested_Cycle set to true ,
                 * this code never be reached because event was cleared already
                 */
                Dem_EvMem_AgingEvMemEntry(EventId, DTCOrigin, MemEntry);
                LblDirty = DEM_TRUE;
              }
            }
          } /* if event tested completed as failed this operation cycle */
          /* @Trace: SWS_Dem_01215
           * If the configuration parameter DemAgingRequiresNotFailedCycle is
           * set to false, the aging counter behavior shall not be influenced.
           */
          else if (DEM_TEST_RESULT_FAILED_THIS_OPERATION == LddOpTestResult)
          {
            /* @Trace: Dem_SUD_API_11491 */
            /* @Trace: SWS_Dem_00489
             * Aging is independent of the UDS status bit 3 (ConfirmedDTC) and
             * therefore independent of the fault confirmation*/
            /* Clear aging counter when event status is changed to failed */
             LblDirty |= Dem_EvMem_SetAgingCounter(MemEntry, DEM_ZERO);
          }
          else
          {
            /* @Trace: Dem_SUD_API_11451 */
            /* Nothing to do */
          }
        }

        /* Searching max time stamp */
        /* @Trace: Dem_SUD_API_11468 */
        #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
        /* @Trace: Dem_SUD_API_11469 */
        if (DEM_NO_EVENT != Dem_EvMem_GetEventIdByEvMemEntry(
            DTCOrigin, LddMemLoc))
        {
          uint32 LulCurrTimeStamp = MemEntry->TimeStamp;
          /* @Trace: Dem_SUD_API_11470 */
          if (LulMaxTimeStamp < LulCurrTimeStamp)
          {
            /* @Trace: Dem_SUD_API_11471 */
            LulMaxTimeStamp =  LulCurrTimeStamp;
          }
        }
        #endif

        /* polyspace<RTE:UNR:Not a defect:No action planned>
         * If-condition evaluates to true or false according to configuration */
        
        /* @Trace: SWS_Dem_00529
         * The configuration parameter DemOperationCycleRef (refer to
         * DemEventParameter) shall be used for calculating the trip counter
         * according ISO14229-1[2] (see figure 7.20).
         */
        /* @Trace: Dem_SUD_API_11473 */
        if (OperationCycleId == LddEvent->e_OperationCycleId)
        {
          /* @Trace: Dem_SUD_API_11474 */
          if ((LddUDSStatusByte & DEM_BITMASK_RESET_TRIP) == DEM_ZERO)
          {
            /* @Trace: Dem_SUD_API_11475 */
            /* [SWS_Dem_00391]
             * Dem_SetOperationCycleState[
             * OperationCycleId == DemOperationCycleRef &&
             * testFailedThisOperationCycle == 0 &&
             * testNotCompleteThisOperationCycle == 0] /failure counter = 0 */
            LblDirty |= Dem_EvMem_SetFailureCounter(MemEntry, DEM_ZERO);
          }
        }
        /* @Trace: Dem_SUD_API_11476 */
        if (DEM_TRUE == LblDirty)
        {
          Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
          /* @Trace: Dem_SUD_API_11478 */
          if (NULL_PTR != LddCbDTC)
          {
            /* @Trace: Dem_SUD_API_11477 */
            LucEvStatusBlkState |= LddCbDTC->EvMemTriggerFlag;
            Dem_EvMem_SetEvMemNvBlockStatus(
                DTCOrigin, LddMemLoc, LddCbDTC->EvMemTriggerFlag);
          }
        }
      }
    }
    /* @Trace: Dem_SUD_API_11479 */
    #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
    /* @Trace: Dem_SUD_API_11480 */
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
    if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(DTCOrigin))
    {
      /* @Trace: Dem_SUD_API_11482 */
      Dem_MaxTimeStamp[DEM_DTC_ORIGIN_USERDEFINED_MEMORY] = LulMaxTimeStamp;
    }
    else
    #endif
    {
     /* @Trace: Dem_SUD_API_11481 */
      Dem_MaxTimeStamp[DTCOrigin] = LulMaxTimeStamp;
    }
    #endif
    /* @Trace: Dem_SUD_API_11484 */
    #if (DEM_UDS_STATUS_IN_EVENT_NVBLOCK == STD_ON)
    /* @Trace: Dem_SUD_API_11485 */
    if (DEM_TRUE == LblEventIsAged)
    {
      /* @Trace: Dem_SUD_API_11486 */
      Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID,
          LucEvStatusBlkState);
    }
    #endif
  }
}
#define DEM_STOP_SEC_CODE
#include "MemMap.h"


