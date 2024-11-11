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
**  PURPOSE   : Provision of Dem operation cycle functionality                **
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
** 2.1.0.0   29-Mar-2024   EK Kim        Jira #CP44-3819                      **
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"           /* DEM module Header File */
#include "Dem_Ram.h"       /* DEM Ram Header File */
#include "Dem_Dtc.h"
#include "Dem_EventMemory.h"
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"           /* Det Module Header File */
#endif

#include "NvM.h"           /* NVRAM manager symbols Header File */
#include "SchM_Dem.h"      /* Basic s/w module Scheduler symbols Header File */
#include "Dem_Event.h"
#include "Dem_EventAging.h"
#include "Dem_Indicator.h"
#include "Dem_EventDebounce.h"
#include "Dem_EventCallback.h"
#include "Dem_ObdRam.h"
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Dem_RestartOperationCycle                           **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : Interface for BSW Components to report Errors       **
**                        during start up (even before DEM initialization)    **
**                        and normal operation.                               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : OperationCycleId - Identification of operation      **
**                                           cycle, like power cycle,driving  **
**                                           cycle                            **
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
/* @Trace: SRS_BSW_00101 SRS_BSW_00310 SRS_Diag_04010 SRS_Diag_04065
           SRS_Diag_04067 SRS_Diag_04068 SRS_Diag_04105 SRS_Diag_04117
           SRS_Diag_04124 SRS_Diag_04125 SRS_Diag_04129 SRS_Diag_04131
           SRS_Diag_04133 SRS_Diag_04178 SRS_BSW_00387 SRS_Diag_04076
 */
/* @Trace: Dem_SUD_MACRO_030 */
/* polyspace +1 CODE-METRICS:VG CODE-METRICS:CALLS CODE-METRICS:FXLN CODE-METRICS:PATH[Not a defect:LOW] "Not a defect" */ 
FUNC(Std_ReturnType, DEM_CODE) Dem_RestartOperationCycle(
    uint8 OperationCycleId)
{
  /* @Trace: SWS_Dem_01317
   * The Dem shall store the qualification state of the dependent operation
   * cycles over power cycles*/

  Std_ReturnType LddRetVal = E_NOT_OK;

  if (DEM_UNINIT == Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12190 */
    DEM_REPORT_ERROR(DEM_RESTARTOPERATIONCYCLE_SID, DEM_E_UNINIT);
  }
  else if (OperationCycleId >= Dem_Num_Operation_Cycles)
  {
    /* @Trace: Dem_SUD_API_12201 */
    DEM_REPORT_ERROR(DEM_RESTARTOPERATIONCYCLE_SID, DEM_E_WRONG_CONFIGURATION);
  }
  /* The previous restart has not been fully processed */
  else if (Dem_OperationCycleBuffer[OperationCycleId] != DEM_FALSE)
  {
    /* @Trace: Dem_SUD_API_12212 */
    /* @Trace: SWS_Dem_01316
     * The Dem shall only restart operation cycles after the previous restart
     * has been fully processed. In other words this means that there is no
     * Operation Cycle restart queue.
     * */
    /* retVal = E_NOT_OK; */
  }
  else
  {
    /*Add to queue to handling later. */
    if (DEM_PREINIT == Dem_GucInit)
    {
      /* @Trace: Dem_SUD_API_12223 */
      /* Set the buffer to proceed later */
      SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
      Dem_OperationCycleBuffer[OperationCycleId] = DEM_TRUE;
      SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
    }
    else
    {
      /* @Trace: Dem_SUD_MACRO_035 */
      uint8 LucOperationCycleIdx;
      /* @Trace: SWS_Dem_01221
       * The Dem allows definition of dependent operation cycles using
       * DemLeadingCycleRef parameter. Whenever the parameter is set, the
       * operation cycle is considered as a dependent operation cycle. Whenever
       * the parameter is not set, the operation cycle is considered as "normal"
       * operation cycle.
       * */
      /* @Trace: Dem_SUD_API_12234 */
      #if (DEM_NUM_OF_DEPENDENT_OPERATION_CYCLE_LIST > DEM_ZERO)
      /* @Trace: SWS_Dem_01225
       * When restarting a dependent operation cycle, its operation cycle
       * qualification shall be reset.
       * */
      /* @Trace: Dem_SUD_API_12245 */
      if (DEM_NO_OPER_CYCLE_IDX !=
            Dem_GaaOperationCycleIdsList[OperationCycleId].usDemLeadingCycleRef)
      {
        /* @Trace: Dem_SUD_API_12256 */
        /* Trace: DEM_CYCLE_02 */
        Dem_EvMem_SetOpCycleQualifiedState(OperationCycleId, DEM_CYCLE_STATE_NOTSTART);
      }

      uint8 LucDepdntOpCylIdx =
          Dem_GaaOperationCycleIdsList[OperationCycleId].usDemDepdntOpCylIdx;
      uint8 LucNumberOfDependents =
          LucDepdntOpCylIdx +
          Dem_GaaOperationCycleIdsList[OperationCycleId].
            usNumberOfDemDepdntOpCyl;
      /* @Trace: SWS_Dem_01224
       * Whenever an operation cycle is requested to be restarted via
       * Dem_RestartOperationCycle, all operation cycles which are depending on
       * the selected operation cycle shall also be restarted, but only if they
       * are qualified
       * */
      /* @Trace: Dem_SUD_API_12267 */
      for (; LucDepdntOpCylIdx < (LucNumberOfDependents + DEM_ONE);
             LucDepdntOpCylIdx++)
      #endif
      {
        /* @Trace: Dem_SUD_API_12278 */
        #if (DEM_NUM_OF_DEPENDENT_OPERATION_CYCLE_LIST > DEM_ZERO)
        if (LucDepdntOpCylIdx < LucNumberOfDependents)
        {
          /* @Trace: Dem_SUD_API_12192 */
          LucOperationCycleIdx =
              Dem_ListOfDependentOperationCycle[LucDepdntOpCylIdx];
        }
        else
        {
          /* @Trace: Dem_SUD_API_12191 */
          LucOperationCycleIdx = OperationCycleId;
        }
        /* @Trace: Dem_SUD_API_12193 */
        /* Trace: DEM_CYCLE_02 */
        Dem_OperationCycleStateType LddCycleQualified;
        Dem_EvMem_GetOpCycleQualifiedState(LucOperationCycleIdx, &LddCycleQualified);
        if ((DEM_OPERATION_CYCLE_QUALIFIED == LddCycleQualified) ||
            (LucOperationCycleIdx == OperationCycleId))
        #else
        LucOperationCycleIdx = OperationCycleId;
        #endif
        {
          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          if (DEM_FALSE == Dem_EvMem_Lock())
          {
            boolean LblDirty = DEM_FALSE;
            Dem_EventIdType LddEventId = DEM_ONE;

            Dem_OperationCycleTrigger = DEM_TRUE;

            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
            Dem_OperationCycleStateType LddCycleStateOld =
                (Dem_OperationCycleStateType)DEM_CYCLE_STATE_NOTSTART;
            Dem_EvMem_GetOpCycleState(LucOperationCycleIdx, &LddCycleStateOld);
            Dem_OperationCycleStateType LddCycleState =
                (Dem_OperationCycleStateType)DEM_CYCLE_STATE_START;
            /* @Trace: Dem_SUD_API_12195 */
            if (DEM_CYCLE_STATE_NOTSTART == LddCycleStateOld)
            {
              /* @Trace: Dem_SUD_API_12196 */
              LddCycleState = DEM_CYCLE_STATE_START;
            }

            /* Store cycle state */
            boolean LblRetDirty =
                Dem_EvMem_SetOpCycleState(LucOperationCycleIdx, LddCycleState);
            /* @Trace: Dem_SUD_API_12198 */
            /* @Trace: Dem_SUD_MACRO_009 */
            #if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_ON)
            /* @Trace: Dem_SUD_API_12197 */
            if (DEM_TRUE == LblRetDirty)
            {
              /* if there is no DTC, operation cycle state should not be stored
               * (optimization) */
              if ((Dem_NumOfStoredEvtMemEntryies
                     [DEM_DTC_ORIGIN_PRIMARY_MEMORY] > DEM_ZERO))
              {
                /* @Trace: Dem_SUD_API_12200 */
                /* If ECU doesn't have a power latch functionality,
                 * DemOperationCycleStatusStorage should be configured as TRUE */
                Dem_EvMem_SetNonVolatieDataStatus(
                DEM_NVDATA_GENERIC_NVRAM_DATA_ID,
                    (DEM_EVMEM_STATUS_DIRTY | DEM_EVMEM_STATUS_TRIGGER_NVM));
              }
              else
              {
                /* @Trace: Dem_SUD_API_12199 */
                /* operation cycle state would be stored later */
                Dem_EvMem_SetNonVolatieDataStatus(
                DEM_NVDATA_GENERIC_NVRAM_DATA_ID,
                DEM_EVMEM_STATUS_TRIGGER_WAIT_NVM);
              }
            }
            #else
            DEM_UNUSED(LblRetDirty);
            #endif
            /* @Trace: SWS_Dem_00773
             * In case the counter is available and started, it shall be
             * incremented at the end of the referenced operation cycle (refer
             * to DemOperationCycleRef).
             * */

            /* @Trace: SWS_Dem_00777
             * In case the counter is available and started, it shall be
             * incremented at the end of the referenced operation cycle (refer
             * to DemOperationCycleRef).
             * */

            /* @Trace: SWS_Dem_00781
             * In case the counter is available and started, it shall be
             * incremented at the end of the referenced operation cycle (refer
             * to DemOperationCycleRef) in case the UDS status bit 1 is set to 1.
             * */
            /* @Trace: Dem_SUD_API_12202 */
            for (LddEventId = DEM_ONE; LddEventId <= DEM_NUMBER_OF_EVENTS; LddEventId++)
            {
              /* @Trace: Dem_SUD_API_12203 */
              Dem_EventParameterPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];

              /* polyspace<RTE:UNR:Not a defect:No action planned>
               * If-condition can evaluate to true/false according to
               * configuration */
              /* @Trace: Dem_SUD_API_12204 */
              if (LucOperationCycleIdx == LddEvent->e_OperationCycleId)
              {

                Dem_NumOfEventMemoryEntryType LddMemLoc =
                    Dem_EvMemToEventMap[LddEventId];
                Dem_DTCOriginType LddDTCOrigin = LddEvent->aaEventDestination;

                Dem_EventMemoryEntryPtrType LddMemEntry = NULL_PTR;
                Dem_NumOfEventMemoryEntryType LddStartIndex =
                    Dem_EvMem_GetStartIndexEventMemorySet(
                        LddEventId, LddDTCOrigin);
                Dem_NumOfEventMemoryEntryType LddStopIndex =
                    Dem_EvMem_GetStopIndexEventMemorySet(
                        LddEventId, LddDTCOrigin);

                /* @Trace: SWS_Dem_00790
                 * The maximum FDC during current operation cycle shall be reset
                 * to zero with each restart operation cycle (refer to
                 * DemOperationCycleRef).
                 * */
                /* @Trace: Dem_SUD_API_12205 */
                #if (DEM_INTERNAL_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON)
                /* @Trace: Dem_SUD_API_12206 */
                if (LddEvent->e_PointToDTC < DEM_MAX_NUMBER_OF_DTC)
                {
                  Dem_InternalDataMaxFdc
                    [LddEvent->e_PointToDTC].maxFdcCurrentCycle = 0;
                }
                #endif

                /* Already stored */
                /* @Trace: Dem_SUD_API_12207 */
                if ((LddStartIndex <= LddMemLoc) && (LddMemLoc < LddStopIndex))
                {
                  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == LddDTCOrigin)
                  {
                    /* @Trace: Dem_SUD_API_12209 */
                    LddMemEntry = &Dem_PrimaryEventMemory[LddMemLoc];
                  }
                  /* @Trace: Dem_SUD_API_12210 */
                  #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
                  else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(LddDTCOrigin))
                  {
                    /* @Trace: Dem_SUD_API_12208 */
                    /* @Trace: Dem_SUD_API_12213 */
                    LddMemEntry = &Dem_UserDefinedEventMemory[LddMemLoc];
                  }
                  #endif
                  else
                  {
                    /* @Trace: Dem_SUD_API_12211 */
                    /* Nothing to do */
                  }
                  /* @Trace: Dem_SUD_API_12214 */
                  if (NULL_PTR != LddMemEntry)
                  {
                    /* @Trace: SWS_Dem_00774
                     * The counter shall be implemented as one byte. If any
                     * count operation occurs which would cause a counter to
                     * roll over past 0xFF then the count value shall instead
                     * be maintained at 0xFF
                     * */
                    /* @Trace: Dem_SUD_API_12215 */
                    #if (DEM_INTERNAL_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
                    /* @Trace: Dem_SUD_API_12216 */
                    if (LddMemEntry->cyclesSinLastFailedCounter < 0xFFU)
                    {
                      /* @Trace: Dem_SUD_API_12217 */
                      LddMemEntry->cyclesSinLastFailedCounter++;
                    }
                    #endif


                    /* @Trace: SWS_Dem_00778
                     * The counter shall be implemented as one byte. If any
                     * count operation occurs which would cause a counter to
                     * roll over past 0xFF then the count value shall instead
                     * be maintained at 0xFF.
                     * */
                    /* @Trace: Dem_SUD_API_12218 */
                    #if (DEM_INTERNAL_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
                    /* @Trace: Dem_SUD_API_12219 */
                    if (LddMemEntry->cyclesSinFirstFailedCounter < 0xFFU)
                    {
                      /* @Trace: Dem_SUD_API_12220 */
                      LddMemEntry->cyclesSinFirstFailedCounter++;
                    }
                    #endif
                    /* @Trace: SWS_Dem_00782
                     * The counter shall be implemented as one byte. If any
                     * count operation occurs which would cause a counter to
                     * roll over past 0xFF then the count value shall instead
                     * be maintained at 0xFF.
                     * */
                    /* @Trace: Dem_SUD_API_12221 */
                    #if (DEM_INTERNAL_DATA_FAILED_CYCLES == STD_ON)
                    /* @Trace: Dem_SUD_API_12222 */
                    if (LddMemEntry->failedCyclesCounter < 0xFFU)
                    {
                      /* @Trace: Dem_SUD_API_12224 */
                      LddMemEntry->failedCyclesCounter++;
                    }
                    #endif
                  }
                }
              }
            }
            /* @Trace: Dem_SUD_API_12225 */
            #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
            /* @Trace: Dem_SUD_API_12226 */
            /* @Trace: Dem_SUD_MACRO_087 */
             (void)Dem_SetObdCycle(LucOperationCycleIdx);
            Dem_GulEventIdDisabled = DEM_ZERO;           
            /* Trace: DEM_COMB_06 */
            /* Keep the Status at the Last Cycle end*/
            #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
            for (uint16 LucIdxCombEvent = DEM_ZERO;
                       LucIdxCombEvent < DEM_MAX_LISTOFCOMBINEDEVENTS;
                       LucIdxCombEvent++ )
            {
              Dem_CombinedEventStatusByteAtCycleEnd[LucIdxCombEvent] = 
              Dem_GetDTCStatus(Dem_ListOfCombinedEvents[LucIdxCombEvent]);
            }
            #endif
			#endif

            /* Initialize Event Status
             *
             * 1. Healing, PDTC
             * 2. EventStatus initialization on OperationCycle is started
             */

            /* @Trace: SWS_Dem_00824
             * If configuration parameter DemResetConfirmedBitOnOverflow is set
             * to false and an event memory entry aging occurs the Dem module
             * shall check for other events having UDS status bit 3 set to 1
             * and UDS status bit 0 set to 0. If such an event is found, the
             * Dem shall allocate an event memory location to get an aging
             * counter.
             */
            /* @Trace: Dem_SUD_API_12231 */
            for (LddEventId = DEM_ONE;
                 LddEventId <= DEM_NUMBER_OF_EVENTS;
                 LddEventId++)
            {
              Dem_EventParameterPCType LddEvent =
                  &Dem_Event[LddEventId - DEM_ONE];
              Dem_NumOfEventMemoryEntryType LddMemLoc =
                  Dem_EvMemToEventMap[LddEventId];
              Dem_DTCOriginType LddDTCOrigin =
                  LddEvent->aaEventDestination;
              Dem_CombinedDtcPCType LddCbDTC =
                  Dem_GetCbDTCByEventId(LddEventId);

              Dem_EventMemoryEntryPtrType LddMemEntry = NULL_PTR;
              Dem_NumOfEventMemoryEntryType LddStartIdx =
                 Dem_EvMem_GetStartIndexEventMemorySet(
                     LddEventId, LddDTCOrigin);
              Dem_NumOfEventMemoryEntryType LddStopIdx =
                 Dem_EvMem_GetStopIndexEventMemorySet(LddEventId, LddDTCOrigin);
              /* @Trace: Dem_SUD_API_12232 */
              if ((LddStartIdx <= LddMemLoc) && (LddMemLoc < LddStopIdx))
              {
                if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == LddDTCOrigin)
                {
                  /* @Trace: Dem_SUD_API_12235 */
                  /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
                  if (LddMemLoc < DEM_MAX_NUMBER_EVENT_ENTRY_PRI)
                  {
                    LddMemEntry = &Dem_PrimaryEventMemory[LddMemLoc];
                  }
                }
                /* @Trace: SWS_Dem_01063
                 * The user defined memory shall have the same behavior as the
                 * primary memory(event retention, event prioritization, aging,
                 * displacement).
                 */
                /* @Trace: Dem_SUD_API_12236 */
                #if (DEM_MAX_NUMBER_EVENT_ENTRY_UD > DEM_ZERO)
                else if (DEM_DTCORGIN_USER_DEFINED_IS_VALID(LddDTCOrigin))
                {
                  /* @Trace: Dem_SUD_API_12233 */
                  /* @Trace: Dem_SUD_API_12238 */
                  if (LddMemLoc < DEM_MAX_NUMBER_EVENT_ENTRY_UD)
                  {
                    /* @Trace: Dem_SUD_API_12239 */
                    LddMemEntry = &Dem_UserDefinedEventMemory[LddMemLoc];
                  }
                }
                #endif
                else
                {
                  /* @Trace: Dem_SUD_API_12237 */
                  /* Nothing to do */
                }
              }

              /* polyspace<RTE:UNR:Not a defect:No action planned>
               * If-condition can evaluate to true/false according to
               * configuration */
              /* @Trace: SWS_Dem_01056
               * The Dem shall process healing only on passed events using the
               * current operation cycle DemOperationCycleRef.
               */
              /* @Trace: Dem_SUD_API_12240 */
              if (LucOperationCycleIdx == LddEvent->e_OperationCycleId)
              {
                /* Trace: DEM_GEN_20 */
                Dem_UdsStatusByteType LddTempEventStatusByteOld;
				#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
                #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
                LddCbDTC = Dem_GetCbDTCByEventId(LddEventId);
                if (LddCbDTC != NULL_PTR)                
                {
                  uint16 LucIdxComb;
                  for (LucIdxComb = DEM_ZERO;
                       LucIdxComb < DEM_MAX_LISTOFCOMBINEDEVENTS;
                       LucIdxComb++ )
                  {
                    if(Dem_ListOfCombinedEvents[LucIdxComb] == LddEventId)
                    {
                      break;
                    }
                  }

                  if (LucIdxComb < DEM_MAX_LISTOFCOMBINEDEVENTS)
                  {
                    LddTempEventStatusByteOld =
                      Dem_CombinedEventStatusByteAtCycleEnd[LucIdxComb];
                  }

                }
                else
                #endif
				#endif
                {
                  LddTempEventStatusByteOld =
                      Dem_AllEventStatusByte[LddEventId];
                }
                const Dem_UdsStatusByteType LddEventStatusByteOld = LddTempEventStatusByteOld;

                /* [1] if operation state transmits from START to END ( for
                 * specific aging cycle such as warm cycle)
                 * [2] if operation state transmits from START to START( no
                 * power latch, DemOperationCycleStatusStorage == true) */
                /* @Trace: Dem_SUD_API_12241 */
                if (DEM_CYCLE_STATE_START == LddCycleStateOld)
                {

                  /* @Trace: SWS_Dem_00390
                   * PedingDTC = 0
                   * [1] NOT TestFailedThisOperationCycle AND
                   * [2] NOT TestNotCompletedThisOperationCycle AND
                   * [3] CycleState = DEM_CYCLE_STATE_END|RESTART) */
                  /* @Trace: Dem_SUD_API_12242 */
                  if ((LddEventStatusByteOld & DEM_BITMASK_RESET_PDTC) ==
                         (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC)
                  {
                    /* @Trace: Dem_SUD_API_12243 */
                    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
                    DEM_CLR_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_PDTC);
                    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
                    /* @dirty = DEM_TRUE; */
                  }
                  /* @Trace: Dem_SUD_API_12244 */
                  if ( LddEvent->ucNumberofIndicator > DEM_ZERO)
                  {
                    /* @Trace: Dem_SUD_API_12246 */
                    /* Trace: DEM_OBD_04_01 */
                    if (DEM_TEST_RESULT_PASSED_THIS_OPERATION == 
                        Dem_GetTestResultThisOperation(LddEventStatusByteOld, Dem_Healing_Requieres_Tested_Cycle))                    
                    {
                      /* @Trace: Dem_SUD_API_12247 */
                      /* Healing : WarningIndicatorRequestOffCondition
                       * [1] Indicator Failure/Healing Operation Cycle is a
                       *     OperationCycle for  a event
                       * [2] Indicator is supported */
                      LblDirty |=
                          Dem_DeActivateIndicatorOnOperationChange(LddEventId);
                    }
                  }

                  /* @Trace: Dem_SUD_API_12250 */
                  if ((DEM_NO_DTC_ORIGIN != LddDTCOrigin) &&
                      (DEM_DTC_ORIGIN_MIRROR_MEMORY != LddDTCOrigin) &&
                      (NULL_PTR != LddCbDTC))
                  {
                    /* @Trace: SWS_Dem_00823
                     * If configuration parameter DemResetConfirmedBitOnOverflow
                     * is set to false and in case an event has UDS status bit 3
                     * set and gets qualified as passed and is not stored in an
                     * event memory entry the Dem module shall try to allocate
                     * an event memory entry to get an aging counter.
                     */
                    /* @Trace: Dem_SUD_API_12251 */
                    if (NULL_PTR == LddMemEntry)
                    {
                      /* @Trace: Dem_SUD_API_12252 */
                      #if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW != STD_ON)
                      /* @Trace: Dem_SUD_API_12253 */
                      if (((Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC ==
                             (LddEventStatusByteOld &
                              (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC) &&
                          ((Dem_UdsStatusByteType)DEM_UDS_STATUS_TF !=
                             (LddEventStatusByteOld &
                              (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF))))
                      {
                        /* @Trace: Dem_SUD_API_12254 */
                        #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
                        /* @Trace: Dem_SUD_API_12255 */
                        Dem_DTCType LddDTC = Dem_GetDtcByCombineDTC(LddCbDTC);
                        #endif
                        LddMemEntry = Dem_AllocateEventMemoryEntry(
                            LddEventId,
                            #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == \
                                   STD_ON)
                            LddDTC,
                            #endif
                            LddDTCOrigin
                            );
                      }
                      #endif
                    }
                  }
                  /* @Trace: SWS_Dem_01185
                   * In case there is no memory location available or occupied
                   * by an individual event, the UDS status bit
                   * TestFailedSinceLastClear of this event will not be aged.
                   */
                  /* @Trace: Dem_SUD_API_12257 */
                  if (NULL_PTR != LddMemEntry)
                  {
                    /* Aging, healing shall be processed
                     * [1] if operation state transmits from START to END ( for
                     *     specific aging cycle such as warm cycle)
                     * [2] if operation state transmits from START to START( no
                     *     power latch, DemOperationCycleStatusStorage == true)
                     *
                     * If ECU doesn't have a power latch functionality,
                     * DemOperationCycleStatusStorage should be configured
                     * as TRUE */
                    /* @Trace: Dem_SUD_API_12258 */
                    if (Dem_NumOfStoredEvtMemEntryies
                          [DEM_DTC_ORIGIN_PRIMARY_MEMORY] > DEM_ZERO)
                    {
                      /* @Trace: Dem_SUD_API_12259 */
                      Dem_EventAgingOnOperationCycleChanged(
                          LddEventId,
                          LddMemEntry,
                          DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                          LucOperationCycleIdx);
                    }
                    /* @Trace: Dem_SUD_API_12260 */
                    #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
                    /* @Trace: Dem_SUD_API_12261 */
                    if (Dem_NumOfStoredEvtMemEntryies
                          [DEM_DTC_ORIGIN_USERDEFINED_MEMORY] > DEM_ZERO)
                    {
                      /* @Trace: Dem_SUD_API_12262 */
                      Dem_EventAgingOnOperationCycleChanged(
                          LddEventId,
                          LddMemEntry,
                          DEM_DTC_ORIGIN_USERDEFINED_MEMORY,
                          LucOperationCycleIdx);
                    }
                    #endif
                  }
                }

                const Dem_UdsStatusByteType LddDTCStatusOld =
                    Dem_GetDTCStatus(LddEventId);
                /* @Trace: SWS_Dem_00439
                 * Note: For resetting the fault detection counter implemented
                 * in a monitor, the Dem module uses the callback-function
                 * InitMonitorForEvent (refer to section 7.2 and Init-
                 * MonitorForEvent). */
                /* @Trace: SWS_Dem_00344
                 * If Dem-internal debouncing is configured, the Dem module
                 * shall reset the Dem-internal debounce algorithm upon starting
                 * a new operation cycle (refer to chapter 7.6).
                 */
                /* @Trace: Dem_SUD_API_12263 */
                if (DEM_DEBOUNCE_NO_DEBOUNCE_BASED !=
                      DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(LddEvent->ParamFieldsA))
                {
                  /* @Trace: Dem_SUD_API_12264 */
                  Dem_ResetFaultDectectionCounter(LddEventId);
                }

                SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
                /* TestFailedThisOperationCycle bit1 = 0 */
                DEM_CLR_UDSSTATUSBYTE(LddEventId ,DEM_UDS_STATUS_TFTOC);
                /* TestNotCompletedThisOperationCycle bit6 = 1 */
                DEM_SET_UDSSTATUSBYTE(LddEventId,DEM_UDS_STATUS_TNCTOC);
                /* Monitor TestNotCompletedThisOperationCycle bit1 = 1*/
                DEM_RST_MONITORSTATUSBYTE(
                    LddEventId,
                    (Dem_MonitorStatusType) DEM_MONITOR_STATUS_TNCTOC);
                /* @Trace: Dem_SUD_API_12265 */
                if (DEM_IS_BIT_SET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_TF))
                {
                  /* @Trace: Dem_SUD_API_12266 */
                  if (DEM_FALSE ==
                        DEM_GET_EVENTPARAM_STORAGE_TF(LddEvent->ParamFieldsA))
                  {
                    /* @Trace: Dem_SUD_API_12268 */
                    DEM_CLR_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_TF);
                  }
                }
                /* @Trace: Dem_SUD_API_12269 */
                if (DEM_TRUE ==
                      Dem_EvIsUdsProcStateTriggered(
                          LddEventId, DEM_UDSPROCSTATE_TRANSITION_BIT_3))
                {
                  if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(
                        LddEventId, DEM_UDS_STATUS_CDTC))
                  {
                    /* @Trace: Dem_SUD_API_12270 */
                    DEM_SET_UDSSTATUSBYTE(LddEventId,
                              (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC);
                  }
                  else
                  {
                   /* @Trace: Dem_SUD_API_12271 */
                    DEM_CLR_UDSSTATUSBYTE(LddEventId,
                              (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC);
                  }
                  Dem_EvClearUdsProcState(
                      LddEventId, DEM_UDSPROCSTATE_TRANSITION_BIT_3);
                }
                /* @Trace: Dem_SUD_API_12272 */
                if (DEM_TRUE ==
                      Dem_EvIsUdsProcStateTriggered(
                          LddEventId, DEM_UDSPROCSTATE_TRANSITION_BIT_5))
                {
                  if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(
                        LddEventId, DEM_UDS_STATUS_TFSLC))
                  {
                    /* @Trace: Dem_SUD_API_12273 */
                    DEM_SET_UDSSTATUSBYTE(LddEventId,
                              (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFSLC);
                  }
                  else
                  {
                    /* @Trace: Dem_SUD_API_12274 */
                    DEM_CLR_UDSSTATUSBYTE(LddEventId,
                              (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFSLC);
                  }
                  Dem_EvClearUdsProcState(
                      LddEventId, DEM_UDSPROCSTATE_TRANSITION_BIT_5);
                }
                SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

                /* @Trace: SWS_Dem_00016
                 * The Dem module shall trigger the event-specific callback-
                 * function EventStatusChanged on each event status change. */
                /* @Trace: Dem_SUD_API_12275 */
                if (LddEventStatusByteOld != Dem_AllEventStatusByte[LddEventId])
                {
                  /* @Trace: Dem_SUD_API_12276 */
                  Dem_TriggerCallbackOnUdsStatus(
                      LddEventId, LddEventStatusByteOld, LddDTCStatusOld);
                }

                /* @Trace: SWS_Dem_00679
                 * The API Dem_SetOperationCycleState shall trigger the callback
                 * function InitMonitorForEvent of the related event(s) in case
                 * of starting or restarting the operation cycle of the event(s)
                 * . The InitMonitorReason parameter shall be set to
                 * DEM_INIT_MONITOR_RESTART
                 * */
                /* Call Callback for initialization of monitor for a event */
                /* @Trace: SWS_Dem_00256
                 */
                /* @Trace: Dem_SUD_API_12277 */
                if (NULL_PTR != LddEvent->pDemInitMonitorForEvent)
                {
                  /* @Trace: Dem_SUD_API_12279 */
                  /*Return value unused - only for compatibility with according
                   * RTE operation.*/
                  /* polyspace<RTE: COR : Not a defect : No Action Planned >
                   * function ptr points to a valid function */
                  (void)LddEvent->pDemInitMonitorForEvent(
                      (Dem_InitMonitorReasonType)DEM_INIT_MONITOR_RESTART);
                }

                /* @Trace: Dem_SUD_API_12283 */
                if (LddEventStatusByteOld != Dem_AllEventStatusByte[LddEventId])
                {
                  /* @Trace: Dem_SUD_API_12284 */
                  if ((NULL_PTR != LddCbDTC) &&
                      (DEM_NO_DTC_ORIGIN != LddEvent->aaEventDestination))
                  {
                     /* @Trace: Dem_SUD_API_12285 */
                    (void)Dem_EvMem_TriggerNvDataStorage(
                      LddEventId,
                      LddEvent->aaEventDestination,
                      LddEventStatusByteOld,
                      LddCbDTC->EvMemTriggerFlag,
                      DEM_FALSE,
                      LblDirty);
                  }
                }
              }
              /* Trace: DEM_GEN_01 */
              else if ((LucOperationCycleIdx == LddEvent->e_AgingCycleId) && 
                      (LddEvent->e_AgingCycleId != LddEvent->e_OperationCycleId))
              {
                /* @Trace: SWS_Dem_01185
                  * In case there is no memory location available or occupied
                  * by an individual event, the UDS status bit
                  * TestFailedSinceLastClear of this event will not be aged.
                  */
                /* @Trace: Dem_SUD_API_12257 */
                if (NULL_PTR != LddMemEntry)
                {
                  /* Aging, healing shall be processed
                    * [1] if operation state transmits from START to END ( for
                    *     specific aging cycle such as warm cycle)
                    * [2] if operation state transmits from START to START( no
                    *     power latch, DemOperationCycleStatusStorage == true)
                    *
                    * If ECU doesn't have a power latch functionality,
                    * DemOperationCycleStatusStorage should be configured
                    * as TRUE */
                  /* @Trace: Dem_SUD_API_12258 */
                  if (Dem_NumOfStoredEvtMemEntryies
                        [DEM_DTC_ORIGIN_PRIMARY_MEMORY] > DEM_ZERO)
                  {
                    /* @Trace: Dem_SUD_API_12259 */
                    Dem_EventAgingOnOperationCycleChanged(
                        LddEventId,
                        LddMemEntry,
                        DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                        LucOperationCycleIdx);
                  }
                  /* @Trace: Dem_SUD_API_12260 */
                  #if (DEM_MAX_NUMBER_USER_DEFINED_MEMORY > DEM_ZERO)
                  /* @Trace: Dem_SUD_API_12261 */
                  if (Dem_NumOfStoredEvtMemEntryies
                        [DEM_DTC_ORIGIN_USERDEFINED_MEMORY] > DEM_ZERO)
                  {
                    /* @Trace: Dem_SUD_API_12262 */
                    Dem_EventAgingOnOperationCycleChanged(
                        LddEventId,
                        LddMemEntry,
                        DEM_DTC_ORIGIN_USERDEFINED_MEMORY,
                        LucOperationCycleIdx);
                  }
                  #endif
                }
              }
              else
              {
                /* Do Nothing */
              }
            }

            Dem_EvMem_TriggerWriteAllBlocks();
            Dem_OperationCycleTrigger = DEM_FALSE;
            LddRetVal = E_OK;
          }
          else
          {
            /* @Trace: Dem_SUD_API_12194 */
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
          /* Trace: DEM_CYCLE_02 */
          (void)Dem_EvMem_SetOpCycleQualifiedState(LucOperationCycleIdx, DEM_OPERATION_CYCLE_NOTQUALIFIED);
        }
      }
    }
  }
  /* Return appropriate value */
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_GetCycleQualified                               **
**                                                                            **
** Service ID           : 0xab                                                **
**                                                                            **
** Description          : Returns the qualification state of the dependent    **
**                        operation cycle.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OperationCycleId - Identification of a configured   **
**                                           DemOperationCycle.               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : isQualified                                         **
**                                         TRUE : The dependent operation     **
**                                                cycle is qualified          **
**                                         FALSE: The qualification conditions**
**                                                of the dependent operation  **
**                                                cycle have not been met     **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04001 SRS_Diag_04129
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetCycleQualified(
    uint8 OperationCycleId,
    P2VAR (boolean, AUTOMATIC, DEM_APPL_DATA) isQualified)
{
  /* @Trace: SWS_Dem_01235
   * If the operation cycle passed to Dem_GetCycleQualified is not configured
   * at all, the Det error DEM_E_WRONG_CONFIGURATION shall be reported.
   * */
  Std_ReturnType LddRetVal = E_OK;

  if (OperationCycleId >= Dem_Num_Operation_Cycles)
  {
    /* @Trace: Dem_SUD_API_12918 */
    DEM_REPORT_ERROR(DEM_GETCYCLEQUALIFIED_SID, DEM_E_WRONG_CONFIGURATION);
    /*@retVal = E_OK;*/
  }
  else if (NULL_PTR == isQualified)
  {
   /* @Trace: Dem_SUD_API_12929 */
    DEM_REPORT_ERROR(DEM_GETCYCLEQUALIFIED_SID, DEM_E_PARAM_POINTER);
    /*@retVal = E_OK;*/
  }
  else
  {
    /* @Trace: SWS_Dem_01234
     * The API Dem_GetCycleQualified shall provide the qualification state
     * of the requested operation cycle in the out parameter "isQualified".
     * */
    /* Trace: DEM_CYCLE_02 */
    Dem_OperationCycleStateType LddCycleQualified;
    Dem_EvMem_GetOpCycleQualifiedState(OperationCycleId, &LddCycleQualified);
    if (DEM_OPERATION_CYCLE_QUALIFIED == LddCycleQualified)
    {
     /* @Trace: Dem_SUD_API_12932 */
      *isQualified = DEM_TRUE;
    }
    else
    {
      /* @Trace: Dem_SUD_API_12931 */
      *isQualified = DEM_FALSE;
      /* Trace: DEM_GEN_11 */
    }
    LddRetVal = E_OK;
  }
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_SetCycleQualified                               **
**                                                                            **
** Service ID           : 0x56                                                **
**                                                                            **
** Description          : Sets a dependent operation cycle as qualified, so   **
**                        it may be processed along with its leading cycle.   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : OperationCycleId - Identification of a configured   **
**                                           DemOperationCycle.               **
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
/* @Trace: SRS_Diag_04129
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_SetCycleQualified(
    uint8 OperationCycleId )
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  /* @Trace: SWS_Dem_01222
   * If the operation cycle passed to Dem_SetCycleQualified is not configured
   * as dependent operation cycle, the Det error DEM_E_WRONG_CONFIGURATION
   * shall be reported.*/

  if (OperationCycleId >= Dem_Num_Operation_Cycles)
  {
    /* @Trace: Dem_SUD_API_12938 */
    DEM_REPORT_ERROR(DEM_SETCYCLEQUALIFIED_SID, DEM_E_WRONG_CONFIGURATION);
  }
  /* @Trace: Dem_SUD_API_12939 */
  #if (DEM_NUM_OF_DEPENDENT_OPERATION_CYCLE_LIST > DEM_ZERO)
  else if (DEM_NO_OPER_CYCLE_IDX ==
             Dem_GaaOperationCycleIdsList[OperationCycleId].
               usDemLeadingCycleRef)
  {
    /* @Trace: Dem_SUD_API_12940 */
    DEM_REPORT_ERROR(DEM_SETCYCLEQUALIFIED_SID, DEM_E_WRONG_CONFIGURATION);
  }
  #endif
  else
  {
    /* Trace: DEM_CYCLE_02 */
    Dem_OperationCycleStateType LddCycleQualified;
    Dem_EvMem_GetOpCycleQualifiedState(OperationCycleId, &LddCycleQualified);
    if (DEM_OPERATION_CYCLE_NOTQUALIFIED == LddCycleQualified)
    {    
      /* @Trace: Dem_SUD_API_12941 */
      /* Trace: DEM_CYCLE_02 */
      (void)Dem_EvMem_SetOpCycleQualifiedState(OperationCycleId, DEM_OPERATION_CYCLE_QUALIFIED);
        
      /* @Trace: SWS_Dem_01220
      * If DemOBDDelayedDCYConfirmedAndMIL is set to TRUE, the behavior of
      * events linked to the OBD driving cycle (DemOBDDrivingCycleRef) shall
      * be changed: If the operation cycle is not qualified, status reports
      * shall be processed, except update of the confirmed status. At the
      * moment the OBD driving cycle is set to qualified, the Dem shall execute
      * computations required to reach the confirmed states of events collected
      * during the "not qualified" phase of the cycle.
      */
      /* Trace: DEM_GEN_11 */
      #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
      #if (DEM_OBD_DELAYED_DCY_CONFIRMED_AND_MIL == STD_ON)
      /* @Trace: Dem_SUD_API_12933 */
      if (Dem_GstOperationCycleName[OperationCycleId].ucOperationCycle ==
            DEM_OPCYC_OBD_DCY)
      {
        Dem_EventIdType LddEventId = DEM_ONE;
        Dem_EventParameterPCType LddEvent;
        /* @Trace: Dem_SUD_API_12934 */
        for (; LddEventId <= DEM_NUMBER_OF_EVENTS; LddEventId++)
        {
          /* @Trace: Dem_SUD_API_12935 */
          if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_CDTC))
          {
            LddEvent = &Dem_Event[LddEventId - DEM_ONE];
            /* @Trace: Dem_SUD_API_12936 */
            if (LddEvent->e_OperationCycleId == OperationCycleId)
            {
              Dem_EventMemoryEntryPtrType LddMemEntry = Dem_EvMem_FindEntry(LddEventId, LddEvent->aaEventDestination);           

              /* Trace: DEM_GEN_12 */
              if (NULL_PTR != LddMemEntry)
              {
                if(LddMemEntry->EventIdRef == LddEventId)
                {
                  if (DEM_IS_BIT_SET_UDSSTATUSBYTE(LddEventId, DEM_UDS_STATUS_TFTOC))
                  {
                    #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE)
                    if (LddMemEntry->FailureCycleCounter < (uint8)0xFF)
                    {
                        LddMemEntry->FailureCycleCounter++;
                    }
                    #endif

                    if (LddEvent->ucNumberofIndicator > DEM_ZERO)
                    {
                        (void)Dem_ActivateIndicatorOnEventFailed(
                        LddEventId, DEM_ZERO);
                    }
                  }
                  /* Trace: DEM_GEN_21 */
                  #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
                  else
                  {
                    Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(LddEventId);
                    /* @Trace: Dem_SUD_API_13320 */
                    if (NULL_PTR != LddCbDTC)
                    {
                      Dem_NumOfEventIdType LddStartPos =
                          Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
                      const Dem_NumOfEventIdType LddEndPos =
                          Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);
                      while (LddStartPos < LddEndPos)
                      {
                        Dem_EventIdType LddTmpEvId =
                            Dem_ListOfCombinedEvents[LddStartPos];
                        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(LddTmpEvId, DEM_UDS_STATUS_TFTOC))
                        {
                          #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE)
                          if (LddMemEntry->FailureCycleCounter < (uint8)0xFF)
                          {
                              LddMemEntry->FailureCycleCounter++;
                          }
                          #endif /*DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE*/

                          if (LddEvent->ucNumberofIndicator > DEM_ZERO)
                          {
                              (void)Dem_ActivateIndicatorOnEventFailed(
                              LddEventId, DEM_ZERO);
                          }
                          break;
                        }                  
                        ++LddStartPos;
                      }
                    }              
                  }
                  #endif
                }

                /* @Trace: Dem_SUD_MACRO_110 */
                #if (DEM_NUM_OF_ENABLE_TRIP_COUNTER > DEM_ONE)
                /* @Trace: Dem_SUD_API_12925 */
                if (Dem_GaaEventFailureThreshold[LddEventId] >= DEM_ONE)
                {
                  if (LddMemEntry->FailureCycleCounter >=
                        Dem_GaaEventFailureThreshold[LddEventId])
                  {
                    /* @Trace: Dem_SUD_API_12928 */
                    if ((DEM_NO_EVENT != LddMemEntry->EventIdRef) &&
                        (LddMemEntry->EventIdRef <= DEM_NUMBER_OF_EVENTS))
                    {
                      /* @Trace: Dem_SUD_API_12930 */
                      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
                      DEM_SET_UDSSTATUSBYTE(
                          LddMemEntry->EventIdRef, DEM_UDS_STATUS_CDTC);
                      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
                    }
                    LddMemEntry->FailureCycleCounter = DEM_ZERO;
                  }
                }
                #endif
              }
            }
          }
        }
      }
      #endif
      #endif

      /* Trace: DEM_OBD_04_02 */ 
      #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
      if(OperationCycleId == Dem_GstGeneralOBDInfo[DEM_ZERO].pOBDPFCCycleRef->ucOperationCycleId )
      {
        Dem_NumOfEventMemoryEntryType memLoc = DEM_NO_EVMEM_ENTRY;
        Dem_NumOfEventMemoryEntryType numOfMemEntries = Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_PERMANENT_MEMORY];
        
        for(memLoc = 0U; memLoc < numOfMemEntries; memLoc++)
        {
          if ((Dem_PermanentEventMemory[memLoc].EventIdRef != DEM_NO_DTC) && (Dem_PermanentEventMemory[memLoc].PfcQualified == DEM_FALSE ))
          {          
            Dem_PermanentEventMemory[memLoc].PfcQualified = DEM_TRUE;                        
          } 
        }
      }
      #endif

      LddRetVal = E_OK;
    }
  }
  return LddRetVal;
}

#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
