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
**  SRC-MODULE: Dem_Indicator.c                                               **
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
** 2.1.0.0   31-Mar-2024   EK Kim        Jira #CP44-4043                      **
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.13    01-Aug-2023   DanhTQ1       Jira #CP44-2579                      **
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
#include "Dem_EventMemory.h"
#include "Dem_Indicator.h"


#define DEM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
 ** Function Name        : Dem_InitIndicator                                  **
 **                                                                           **
 ** Service ID           : None                                               **
 **                                                                           **
 ** Description          : Initialize  Indicator                              **
 **                                                                           **
 ** Sync/Async           : Synchronous                                        **
 **                                                                           **
 ** Re-entrancy          : Reentrant                                          **
 **                                                                           **
 ** Input Parameters     : eventId                                            **
 **                                                                           **
 ** InOut parameter      : None                                               **
 **                                                                           **
 ** Output Parameters    : None                                               **
 **                                                                           **
 ** Return parameter     : boolean                                            **
 **                                                                           **
 ** Preconditions        : None                                               **
 **                                                                           **
 ** Remarks              :                                                    **
 ******************************************************************************/
/* @Trace: Dem_SUD_MACRO_019 */
FUNC(boolean, DEM_CODE) Dem_InitIndicator(Dem_EventIdType EventId)
{
  boolean LblDirty = DEM_FALSE;
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];

  P2CONST(Dem_IndicatorAttributeType, AUTOMATIC, DEM_VAR) LddIndicator;
  Dem_NumOfIndicatorAttributeType LddMax =
      LddEvent->e_PointToIndicator + LddEvent->ucNumberofIndicator;
  Dem_NumOfIndicatorAttributeType LddIdx;

  if (LddMax <= DEM_NUMBER_OF_INDICATORS)
  {      
    /* @Trace: Dem_SUD_API_00057 */
    /* @Trace: Dem_SUD_API_00341 */
    for (LddIdx = LddEvent->e_PointToIndicator; LddIdx < LddMax ; LddIdx++)
    {
      /* @Trace: Dem_SUD_API_00058 */
      LddIndicator = Dem_GetCfgIndicatorAtt(LddIdx);
      LblDirty |= Dem_EvMem_ResetIndicatorAttribute(LddIndicator);
    }
    /* @Trace: Dem_SUD_API_00342 */
    if (DEM_TRUE == LblDirty)
    {
      /* @Trace: Dem_SUD_API_00059 */
      Dem_EvMem_SetNonVolatieDataStatus(
          DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY);
    }
  }
  else
  {
    /* @Trace: Dem_SUD_API_00340 */
    /* Do nothing */
  }
  /* @Trace: Dem_SUD_API_00060 */
  return LblDirty;
}

/*******************************************************************************
 ** Function Name        : Dem_ActivateIndicatorOnEventFailed                 **
 **                                                                           **
 ** Service ID           : None                                               **
 **                                                                           **
 ** Description          : Active Indicator on Event failed                   **
 **                                                                           **
 ** Sync/Async           : Synchronous                                        **
 **                                                                           **
 ** Re-entrancy          : Reentrant                                          **
 **                                                                           **
 ** Input Parameters     : eventId, testFailedThisOpCycle                     **
 **                                                                           **
 ** InOut parameter      : None                                               **
 **                                                                           **
 ** Output Parameters    : None                                               **
 **                                                                           **
 ** Return parameter     : boolean                                            **
 **                                                                           **
 ** Preconditions        :                                                    **
 **                                                                           **
 ** Remarks              :                                                    **
 ******************************************************************************/
/* @Trace: SRS_Diag_04067 SRS_Diag_04069 SRS_Diag_04161
 */
FUNC(boolean, DEM_CODE) Dem_ActivateIndicatorOnEventFailed(
  Dem_EventIdType EventId, 
  uint8  testFailedThisOpCycle)  
{
  boolean LblDirty = DEM_FALSE;
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];

  const Dem_NumOfIndicatorAttributeType LddMax = LddEvent->e_PointToIndicator
    + LddEvent->ucNumberofIndicator;
  /* @Trace: Dem_SUD_API_00343 */
  if (LddMax <= DEM_NUMBER_OF_INDICATORS)
  {
    P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR) LddIndicator;
    Dem_NumOfIndicatorAttributeType LddIdx;
    /* @Trace: Dem_SUD_API_00061 */
    boolean LblIndicatorAttStatus = DEM_FALSE;
    boolean LblIndicatorStatus = DEM_FALSE;
    uint8 LucCounterValue;
    /* @Trace: Dem_SUD_API_00344 */
    #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    /* @Trace: Dem_SUD_API_00346 */
    boolean LblPerRegister = DEM_FALSE;
    #endif
    uint8 LucThresHold;

    /*
     * WarningIndicatorRequest On
     *
     * [1] LblIndicatorStatus == false
     * [2] Shall be only called from Dem_SetEventStatus by design decision
     * [3] Event qualified as failed this operation cycle at first */
    /* @Trace: Dem_SUD_API_00345 */
    for (LddIdx = LddEvent->e_PointToIndicator; LddIdx < LddMax; LddIdx++)
    {
      /* @Trace: Dem_SUD_API_00068 */
      /* @Trace: Dem_SUD_API_00062 */
      LddIndicator = Dem_GetCfgIndicatorAtt(LddIdx);
      LblIndicatorAttStatus = Dem_EvMem_GetIndicatorAttStatus(
          EventId, LddIndicator->IndicatorAttStatusPos);

      LucCounterValue = DEM_ZERO;
      /* @Trace: Dem_SUD_API_00352 */
      if (DEM_FALSE == LblIndicatorAttStatus)
      {
        /* @Trace: Dem_SUD_API_00353 */
        if (DEM_ZERO == testFailedThisOpCycle)
        {
          /* @Trace: Dem_SUD_API_00063 */
          LblDirty |= Dem_EvMem_IncreaseIndicatorFailureCounter(
              LddIndicator->FailureCycleCounterPos, &LucCounterValue);
        }
        /* if failure cycle counter is not existed, indicator status shall set
         * to true */
        /* @Trace: SWS_Dem_00567
         * If an indicator is configured for controlling the MIL of an
         * OBDrelevant ECU, the Dem module shall use the configured event
         * failure cycle counter of this event (refer to 0 Fault confirmation)
         * to define the maximum number of tested and failed cycles, before
         * the stored event activates the respective indicator.
         */
        LucThresHold = LddIndicator->NumFailureCycles;

        /* @Trace: Dem_SUD_API_00354 */
        /* @Trace: SWS_Dem_01246
         * A DemIndicatorAttribute with a configured DemMILIndicatorRef, shall
         * use the DemEventConfirmationThreshold instead of the
         * DemIndicatorFailureCycleCounterThreshold to calculate the indicator
         * On Criteria (WarningIndicatorOnCriteriaFulfilled).
         */
        if (LddEvent->ucEventMemDstIdx != DEM_NO_EVMEM_IDX)
        {
          /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
          /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Configuration. */
          if ((Dem_GaaDemMemorySet[LddEvent->ucEventMemDstIdx].usDemMILIndicatorRef == LddIndicator->IndicatorIdRef))
          {
            LucThresHold = Dem_GaaEventFailureThreshold[EventId];
          }
          /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
          /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
          /* else  usDemMILIndicatorRef is  not configured or usDemMILIndicatorRef is not equal to IndicatorIdRef  */
        }
        
        if (LucCounterValue >= LucThresHold)
        {
          /* @Trace: SWS_Dem_00566
          */
          /* @Trace: Dem_SUD_API_00064 */
          LblDirty |= Dem_EvMem_SetIndicatorAttStatus(LddIndicator, DEM_TRUE);
          /* from false to true */
          LblDirty |= Dem_EvMem_SetIndicatorFailureCounter(
              LddIndicator->FailureCycleCounterPos, DEM_ZERO);
          LblIndicatorAttStatus = DEM_TRUE;
        }
        /* @Trace: SWS_Dem_00701
         * If the MIL is deactivated and the event is confirmed the MIL shall
         * be reactivated according to [SWS_Dem_00567] i.e. again according to
         * the indicator failure cycle counter is reaching it's threshold.*/
        /* @Trace: Dem_SUD_API_00351 */
        #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        /* @Trace: Dem_SUD_API_00350 */
        if (LucCounterValue >= Dem_GaaEventFailureThreshold[EventId])
        {
          /* @Trace: Dem_SUD_API_00065 */
          uint8 LucMemSetIdx = LddEvent->ucEventMemDstIdx;
          /* @Trace: Dem_SUD_API_00349 */
          if (DEM_NO_IDX_U8 != LucMemSetIdx)
          {
            /* @Trace: Dem_SUD_API_00356 */
            if (Dem_GaaDemMemorySet[LucMemSetIdx].usDemMILIndicatorRef ==
                  LddIndicator->IndicatorIdRef)
            {
              /* @Trace: Dem_SUD_API_00355 */
              if (Dem_GucMilonFlag != DEM_BIT7_MASK1)
              {
                /*Its increased the number of MIL is ON*/
                /* @Trace: Dem_SUD_API_00066 */
                Dem_GucMilActivatedCnt++;
              }
              Dem_MilonStatus = DEM_BIT7_MASK1;
              LblPerRegister = DEM_TRUE;
            }
          }
        }
        #endif
      }

      /* [1] testFailedThisOperationCycle==1
       * [2] testNotCompletedThisOperationCycle==0
       * [3] As result, healing counter = 0
       * [4] N/A: IndicatorStatusPtr is true */
      /* @Trace: Dem_SUD_API_00067 */
      LblDirty |= Dem_EvMem_SetIndicatorHealingCounter(
          LddIndicator->HealingCycleCounterPos, DEM_ZERO);

      /* calculates the combined indicator status for an indicatorId of an
       * event */
      LblIndicatorStatus |= LblIndicatorAttStatus;
    }
    /* @Trace: SWS_Dem_00501
     * The condition WarningIndicatorOnCriteriaFulfilled shall be fulfilled if
     * at least one respective event indicator failure counter has reached its
     * DemIndicatorFailureCycleCounterThreshold of tested and failed
     * DemOperationCycles.
     */
    /* @Trace: Dem_SUD_API_00359 */
    if (DEM_TRUE == LblIndicatorStatus)
    {
      /* @Trace: Dem_SUD_API_00358 */
      if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_WIR))
      {
        /* WarningIndicatorRequest bit = 1 */
        /* @Trace: SWS_Dem_00395
         * The Dem module shall implement the status bit transition for UDS
         * status bit 7 (WarningIndicatorRequested) according to figure 7.24.
         * WarningIndicatorOnCriteriaFulfilled */
        /* @Trace: Dem_SUD_API_00069 */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        Dem_EvSetUdsProcState(EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_7);
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
      /* @Trace: Dem_SUD_API_00347 */
      #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
      /* @Trace: Dem_SUD_API_00357 */
      if (LblPerRegister == DEM_TRUE)
      {
        /* @Trace: Dem_SUD_API_00348 */
        /*Trace: Dem_SUD_MACRO_028 */
        #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
        /* @Trace: Dem_SUD_API_00070 */
        (void)Dem_EvMem_RegisterPermanentDTC(EventId);
        #endif
      }
      #endif
    }
  }
  /* @Trace: Dem_SUD_API_00071 */
  return LblDirty;
}
/*******************************************************************************
 ** Function Name        : Dem_DeActivateIndicatorOnEventPassed               **
 **                                                                           **
 ** Service ID           : None                                               **
 **                                                                           **
 ** Description          : De-Activate Indicator on Event pass                **
 **                                                                           **
 ** Sync/Async           : Synchronous                                        **
 **                                                                           **
 ** Re-entrancy          : Reentrant                                          **
 **                                                                           **
 ** Input Parameters     : EventId                                            **
 **                                                                           **
 ** InOut parameter      : None                                               **
 **                                                                           **
 ** Output Parameters    : None                                               **
 **                                                                           **
 ** Return parameter     : boolean                                            **
 **                                                                           **
 ** Preconditions        : None                                               **
 **                                                                           **
 ** Remarks              :                                                    **
 ******************************************************************************/
/* @Trace: SRS_Diag_04067 SRS_Diag_04069
 */
/* @Trace: Dem_SUD_MACRO_133 */
FUNC(boolean, DEM_CODE) Dem_DeActivateIndicatorOnEventPassed(
  Dem_EventIdType EventId)
{
  boolean LblDirty = DEM_FALSE;
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  
  Dem_NumOfIndicatorAttributeType LddMax =
      LddEvent->e_PointToIndicator + LddEvent->ucNumberofIndicator;
  if (LddMax <= DEM_NUMBER_OF_INDICATORS)
  {
    /* @Trace: Dem_SUD_API_00072 */
    P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR)  LddIndicator;
    Dem_NumOfIndicatorAttributeType LddIdx;
    boolean LblIndicatorAttributeStatus = DEM_FALSE;
    boolean LblIndicatorStatus = DEM_FALSE;
    /* @Trace: Dem_SUD_API_00372 */
    #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
         (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
    /* @Trace: Dem_SUD_API_00373 */
    boolean LblPerClear = DEM_FALSE;
    #endif
    Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_NO_EVMEM_ENTRY;
    /* @Trace: Dem_SUD_API_00374 */
    #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
         (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
    /* @Trace: Dem_SUD_API_00375 */
    LddMemLoc = Dem_EvMem_FindPerMemLoc(EventId);
    #endif
    
    /*
     * WarningIndicatorRequest Off immediately
     *
     * [1] WarningIndicatorRequest == 1
     * [2] @IF_REQ: Shall be only called when TestResult is passed firstly(
     *     TestFailedThisOperationCycle = 0)
     * [3] Only indicator shall be processed with healingCycleThreshold = 0
     * [4] @IF_REQ: Shall be called in Dem_SetEventStatus(first passed this
     *     operation) */

    /* @Trace: SWS_Dem_01233
     * If an indicator is configured (via DemIndicatorAttribute) the Dem module
     * shall set when the Event is reported/qualified to PASSED the UDSstatus
     * bit 7 (WarningIndicatorRequested)to 0, if the following conditions are
     * fulfilled:
     * + All DemIndicatorHealingCycleCounterThreshold are equal to 0
     * + WIRbit is not enabled by calling the API Dem_SetWIRStatus
     */
    /* @Trace: Dem_SUD_API_00360 */
    if (DEM_FALSE ==
          Dem_EvIsProcStateTriggered(
              EventId, DEM_EVPROCSTATE_IS_SET_WIR_STATUS))
    {
      /* @Trace: Dem_SUD_API_00073 */
      /* @Trace: Dem_SUD_API_00369 */
      for (LddIdx = LddEvent->e_PointToIndicator; LddIdx < LddMax ; LddIdx++)
      {
        /* @Trace: Dem_SUD_API_00079 */
        /* @Trace: Dem_SUD_API_00074 */
        LddIndicator = Dem_GetCfgIndicatorAtt(LddIdx);
        LblIndicatorAttributeStatus =
            Dem_EvMem_GetIndicatorAttStatus(
                EventId, LddIndicator->IndicatorAttStatusPos);


        /* healing is processed immediately when threshold value is 0 */
        /* @Trace: Dem_SUD_API_00370 */
        if ((DEM_TRUE == LblIndicatorAttributeStatus) ||
            (DEM_NO_EVMEM_ENTRY != LddMemLoc))
        {
          /* @Trace: Dem_SUD_API_00371 */
          if (((DEM_ZERO == LddIndicator->NumHealingCycles))&&
              (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_WIR)))
          {
            /* HealingCycleCounterPtr don't be needed because healing is
             * processed immediately
             * LddIndicator->HealingCycleCounterPtr = DEM_ZERO; */
            /* from true to false */
            LblDirty |=
                Dem_EvMem_SetIndicatorAttStatus(LddIndicator, DEM_FALSE);
            LblIndicatorAttributeStatus = DEM_FALSE;

            /*  obd */
            /* @Trace: Dem_SUD_API_00376 */
            /* @Trace: Dem_SUD_MACRO_008 */
            #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
            uint8 LucMemSetIdx = LddEvent->ucEventMemDstIdx;
            /* @Trace: Dem_SUD_API_00362 */
            if (DEM_NO_IDX_U8 != LucMemSetIdx)
            {
              /* @Trace: Dem_SUD_API_00361 */
              if (Dem_GaaDemMemorySet[LucMemSetIdx].usDemMILIndicatorRef ==
                    LddIndicator->IndicatorIdRef)
              {
                /* @Trace: Dem_SUD_API_00363 */
                #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
                /* @Trace: Dem_SUD_API_00364 */
                LblPerClear = DEM_TRUE;
                #endif
                Dem_GucMilonFlag = LblIndicatorAttributeStatus << DEM_SEVEN;
              }
            }
            #endif
          }
        }
        /* @Trace: Dem_SUD_API_00082 */
        LblIndicatorStatus |= LblIndicatorAttributeStatus;
      }
      /* WIR bit off */
      /* @Trace: Dem_SUD_API_00365 */
      if (DEM_FALSE == LblIndicatorStatus)
      {
        /* @Trace: Dem_SUD_API_00366 */
        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_WIR))
        {
          /* WarningIndicatorRequest bit = 0 */

          /* @Trace: SWS_Dem_00395
           * The Dem module shall implement the status bit transition for UDS
           * status bit 7 (WarningIndicatorRequested) according to figure 7.24.
           * WarningIndicatorOffCriteriaFulfilled */
          /* @Trace: Dem_SUD_API_00080 */
          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          DEM_CLR_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_WIR);
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        }
      }
    }
    /* @Trace: Dem_SUD_API_00368 */
    #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
         (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
    /* @Trace: Dem_SUD_API_00367 */
    if (DEM_TRUE == LblPerClear)
    {     
      /* @Trace: Dem_SUD_API_00081 */
      #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
      /* Trace: DEM_COMB_01 */
      Dem_EvMem_ClearPermanentDTCAllCbEvents(EventId, DEM_TRUE);
      #else
      Dem_EvMem_ClearPermanentDTC(EventId, DEM_TRUE);
      #endif
    }
    #endif
    
  }
  /* @Trace: Dem_SUD_API_00083 */
  return LblDirty;
}

/*******************************************************************************
 ** Function Name        : Dem_DeActivateIndicatorOnOperationChange           **
 **                                                                           **
 ** Service ID           : None                                               **
 **                                                                           **
 ** Description          : De-Activate Indicator on Operation change          **
 **                                                                           **
 ** Sync/Async           : Synchronous                                        **
 **                                                                           **
 ** Re-entrancy          : Reentrant                                          **
 **                                                                           **
 ** Input Parameters     : EventId                                            **
 **                                                                           **
 ** InOut parameter      : None                                               **
 **                                                                           **
 ** Output Parameters    : None                                               **
 **                                                                           **
 ** Return parameter     : boolean                                            **
 **                                                                           **
 ** Preconditions        : None                                               **
 **                                                                           **
 ** Remarks              :                                                    **
 ******************************************************************************/
/* @Trace: SRS_Diag_04067 SRS_Diag_04069
 */
/* @Trace: Dem_SUD_MACRO_134 */
FUNC(boolean, DEM_CODE) Dem_DeActivateIndicatorOnOperationChange(
  Dem_EventIdType EventId)
{
  boolean LblDirty = DEM_FALSE;
  Dem_EventParameterPCType LddEvent = &Dem_Event[EventId - DEM_ONE];

  Dem_NumOfIndicatorAttributeType LddMax =
      LddEvent->e_PointToIndicator + LddEvent->ucNumberofIndicator;
  /* if event don't have  any indicator */
  /* @Trace: Dem_SUD_API_00385 */
  if (LddMax <= DEM_NUMBER_OF_INDICATORS)
  {
    P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR)  LddIndicator;
    Dem_NumOfIndicatorAttributeType LddIdx;
    boolean LblIndicatorAttributeStatus = DEM_FALSE;
    boolean LblIndicatorStatus = DEM_FALSE;
    uint8 LucCounterValue;
    /* @Trace: Dem_SUD_API_00396 */
    #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
         (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
    /* @Trace: Dem_SUD_API_00402 */
    uint8 LucPerClear = DEM_ZERO;
    #endif
    Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_NO_EVMEM_ENTRY;
    /* @Trace: Dem_SUD_API_00403 */
    #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
         (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
    LddMemLoc = Dem_EvMem_FindPerMemLoc(EventId);
    #endif
    
    /* WarningIndicatorRequest Off OperationCycleChange
     *
     * [1] LblIndicatorStatus == true
     * [2] Tested and qualified as passed this operation
     * [3] Shall be called when OperationCycleChange(START) */

    /* @Trace: SWS_Dem_00503
     * If an indicator is configured (via DemIndicatorAttribute) the Dem module
     * shall set at the end of an operation cycle the UDS status bit 7
     * (WarningIndicatorRequested)to 0, if the following conditions are
     * fulfilled:
     *  + At least one DemIndicatorHealingCycleCounterThreshold is unequal to 0
     *  + All respective events indicator healing counters have reached their
     *    DemIndicatorHealingCycleCounterThreshold of tested and passed healing
     *    DemOperationCycles (equals WarningIndicatorOffCriteriaFulfilled)
     *  + WIRbit is not enabled by calling the API Dem_SetWIRStatus
     */
    /* @Trace: Dem_SUD_API_00404 */
    if (DEM_FALSE ==
          Dem_EvIsProcStateTriggered(
              EventId, DEM_EVPROCSTATE_IS_SET_WIR_STATUS))
    {
      /* @Trace: Dem_SUD_API_00405 */
      for (LddIdx = LddEvent->e_PointToIndicator; LddIdx < LddMax ; LddIdx++)
      {
        LucCounterValue = DEM_ZERO;
        LddIndicator = Dem_GetCfgIndicatorAtt(LddIdx);
        LblIndicatorAttributeStatus =
            Dem_EvMem_GetIndicatorAttStatus(
                EventId, LddIndicator->IndicatorAttStatusPos);
        /* @Trace: Dem_SUD_API_00406 */
        if ((DEM_TRUE == LblIndicatorAttributeStatus) ||
            (DEM_NO_EVMEM_ENTRY != LddMemLoc))
        {
          if (DEM_ZERO != LddIndicator->NumHealingCycles)
          {
            LblDirty |=
                Dem_EvMem_IncreaseIndicatorHealingCounter(
                    LddIndicator->HealingCycleCounterPos, &LucCounterValue);
            /* @Trace: Dem_SUD_API_00408 */
            if (LucCounterValue >= LddIndicator->NumHealingCycles)
            {
              /* @Trace: SWS_Dem_00566
               */
              /* from true to false */
              LblDirty |=
                  Dem_EvMem_SetIndicatorAttStatus(LddIndicator, DEM_FALSE);
              LblDirty |=
                  Dem_EvMem_SetIndicatorHealingCounter(
                      LddIndicator->HealingCycleCounterPos, DEM_ZERO);

              /*  obd */
              /* @Trace: Dem_SUD_API_00386 */
              #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
              uint8 LucMemSetIdx = LddEvent->ucEventMemDstIdx;
              /* @Trace: Dem_SUD_API_00387 */
              if (DEM_NO_IDX_U8 != LucMemSetIdx)
              {
                /* @Trace: Dem_SUD_API_00388 */
                if (Dem_GaaDemMemorySet[LucMemSetIdx].usDemMILIndicatorRef ==
                      LddIndicator->IndicatorIdRef)
                {
                  if (LblIndicatorAttributeStatus == DEM_TRUE)
                  {
                    /* @Trace: Dem_SUD_API_00390 */
                    if (Dem_GucMilonFlag != DEM_BIT7_MASK1)
                    {
                      /*Its increased the number of MIL is ON*/
                      Dem_GucMilActivatedCnt++;
                    }
                    /* @Trace: Dem_SUD_API_00391 */
                    #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
                    /* @Trace: Dem_SUD_API_00394 */
                    LucPerClear = DEM_ONE;
                    #endif
                  }
                  else
                  {
                    /* @Trace: Dem_SUD_API_00389 */
                    /* @Trace: Dem_SUD_API_00392 */
                    #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
                    /* @Trace: Dem_SUD_API_00393 */
                    LucPerClear = DEM_TWO;
                    #endif
                  }
                  Dem_MilonStatus = LblIndicatorAttributeStatus << DEM_SEVEN;
                }
              }
              #endif

              LblIndicatorAttributeStatus = DEM_FALSE;
            }
          }
          else
          {
            /* @Trace: Dem_SUD_API_00407 */
            /* HealingCycleCounterPtr don't be needed because healing is
             * processed immediately
             * indicator->HealingCycleCounterPtr = DEM_ZERO; */
            /* from true to false */
            LblDirty |=
                Dem_EvMem_SetIndicatorAttStatus(LddIndicator, DEM_FALSE);
            LblIndicatorAttributeStatus = DEM_FALSE;
          }
        }
        LblIndicatorStatus |= LblIndicatorAttributeStatus;
      }
      /* WIR bit off */
      /* @Trace: Dem_SUD_API_00395 */
      if (DEM_FALSE == LblIndicatorStatus)
      {
        /* @Trace: Dem_SUD_API_00397 */
        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_WIR))
        {
          /* WarningIndicatorRequest bit = 0 */
          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          DEM_CLR_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_WIR);
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        }
      }
    }
    /* @Trace: Dem_SUD_API_00398 */
    #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
         (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
    if (DEM_ONE == LucPerClear)
    {     
      #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
      /* Trace: DEM_COMB_01 */
      Dem_EvMem_ClearPermanentDTCAllCbEvents(EventId, DEM_TRUE);
      #else
      Dem_EvMem_ClearPermanentDTC(EventId, DEM_TRUE);
      #endif

    }
    else if (DEM_TWO == LucPerClear)
    {     
      /* @Trace: Dem_SUD_API_00399 */
      /* @Trace: Dem_SUD_API_00400 */
      #if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
      /* Trace: DEM_COMB_01 */
      Dem_EvMem_ClearPermanentDTCAllCbEvents(EventId, DEM_FALSE);
      #else
      Dem_EvMem_ClearPermanentDTC(EventId, DEM_FALSE);
      #endif

    }
    else
    {
      /* @Trace: Dem_SUD_API_00401 */
      /* Do Nothing  */
    }
    #endif
  
  }
  
  return LblDirty;
}

/*******************************************************************************
 ** Function Name        : Dem_DeactivateMIL                                  **
 **                                                                           **
 ** Service ID           : None                                               **
 **                                                                           **
 ** Description          : Handling for Deactivate MIL                        **
 **                                                                           **
 ** Sync/Async           : Synchronous                                        **
 **                                                                           **
 ** Re-entrancy          : Reentrant                                          **
 **                                                                           **
 ** Input Parameters     : EventId                                            **
 **                                                                           **
 ** InOut parameter      : None                                               **
 **                                                                           **
 ** Output Parameters    : None                                               **
 **                                                                           **
 ** Return parameter     : boolean                                            **
 **                                                                           **
 ** Preconditions        : None                                               **
 **                                                                           **
 ** Remarks              :                                                    **
 ******************************************************************************/
/* @Trace: Dem_SUD_MACRO_135 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(void, DEM_CODE) Dem_DeactivateMIL(void)
{
  /*Handle for MIL */
  boolean LblIsDeactivateMIL = DEM_TRUE;
  /* @Trace: Dem_SUD_API_00380 */
  for (Dem_EventIdType LddEventId = DEM_ONE;
                       LddEventId <= DEM_NUMBER_OF_EVENTS;
                       LddEventId++)
  {
    /* @Trace: Dem_SUD_API_00088 */
    /* @Trace: Dem_SUD_API_00084 */
    Dem_EventParameterPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
    const Dem_NumOfIndicatorAttributeType LddMax = LddEvent->e_PointToIndicator
        + LddEvent->ucNumberofIndicator;
    /* @Trace: Dem_SUD_API_00379 */
    if (LddMax <= DEM_NUMBER_OF_INDICATORS)
    {
      /* @Trace: Dem_SUD_API_00085 */
      P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR) LddIndicator;
      Dem_NumOfIndicatorAttributeType LddIdx;
      /* @Trace: Dem_SUD_API_00384 */
      for (LddIdx = LddEvent->e_PointToIndicator; LddIdx < LddMax; LddIdx++)
      {
        /* @Trace: Dem_SUD_API_00089 */
        /* @Trace: Dem_SUD_API_00086 */
        LddIndicator = Dem_GetCfgIndicatorAtt(LddIdx);
        uint8 LucMemSetIdx = LddEvent->ucEventMemDstIdx;
        /* @Trace: Dem_SUD_API_00377 */
        if (DEM_NO_IDX_U8 != LucMemSetIdx)
        {
          /* @Trace: Dem_SUD_API_00378 */
          if ((Dem_GaaDemMemorySet[LucMemSetIdx].usDemMILIndicatorRef ==
                 LddIndicator->IndicatorIdRef) &&
               (Dem_EvMem_GetIndicatorAttStatus(
                LddEventId, LddIndicator->IndicatorAttStatusPos) == DEM_TRUE))
          {
            /* @Trace: Dem_SUD_API_00087 */
            LblIsDeactivateMIL = DEM_FALSE;
            break;
          }
        }
      }
    }
  }
  /* Trace: DEM_GEN_09 */
  /* @Trace: Dem_SUD_API_00381 */
  if (DEM_TRUE == LblIsDeactivateMIL)
  {
    /* @Trace: Dem_SUD_API_00090 */
    /* Deactive MIL */
    Dem_MilonStatus = DEM_ZERO << DEM_SEVEN;
    /* @Trace: Dem_SUD_API_00382 */
    #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    /* @Trace: Dem_SUD_API_00383 */
    Dem_GucMilonFlag = Dem_MilonStatus;
    #endif  
  }
  /* If Mil Activated */
  else
  {
    if (Dem_GucMilonFlag == DEM_ZERO) 
    {
      Dem_MilonStatus = DEM_ONE << DEM_SEVEN;
      /* @Trace: Dem_SUD_API_00383 */
      Dem_GucMilonFlag = Dem_MilonStatus;
    }
  }
}
#endif

#define DEM_STOP_SEC_CODE
#include "MemMap.h"
