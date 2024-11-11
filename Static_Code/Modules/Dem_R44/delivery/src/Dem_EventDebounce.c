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
**  SRC-MODULE: Dem_EventDebounce.c                                           **
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
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

 

/*******************************************************************************
**                     Include Section                                       **
*******************************************************************************/
#include "Dem.h"        /* DEM module Header File */
#include "Dem_Ram.h"    /* DEM Ram Header File */
#include "Dem_Config.h"

/* DEM_DEV_ERROR_DETECT is defined in Dem_Cfg.h
 * Dem_Cfg.h is included by Dem.h */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"        /* Det Module Header File */
#endif

#include "SchM_Dem.h"   /* Basic s/w module Scheduler symbols Header File */ 
#include "Rte_Dem.h"
#include "Dem_Event.h"
#include "Dem_EventDebounce.h"

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
 ** Function Name       : Dem_ProcessDebounceCounterBased                     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Perform Counter based Debouncing of events and      **
 **                       qualify them as pass or fail.                       **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : DebounceId                                          **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : EventStatus                                         **
 **                                                                           **
 ** Return parameter    : boolean                                             **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: SRS_Diag_04067 SRS_Diag_04068
 */
/* @Trace: Dem_SUD_MACRO_033 */
#if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
FUNC(boolean, DEM_CODE)Dem_ProcessDebounceCounterBased(
  const Dem_NumOfDebounceType DebounceId,
  P2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus)
{
  /* @Trace: SWS_Dem_00427 */
  /* @Trace: SWS_Dem_00414
   * If the configuration container DemDebounceAlgorithmClass is set to
   * DemDebounceCounterBased, the Dem module shall provide an internal
   * debounce counter for each individual event, to qualify the reported
   * event.
   */
  boolean LblQulifiedAsPassOrFailed = DEM_FALSE;
  
  if ((DebounceId < DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER) &&
      (NULL_PTR != EventStatus))
  { 
    P2CONST(Dem_PreDebounceCounterType, AUTOMATIC, DEM_CONST) LddDcb =
        &Dem_GaaPreDebounceCounter[DebounceId];
    const sint16 LssMaxFDC = LddDcb->ssDemCounterFailedThreshold; /* (+) value */
    const sint16 LssMinFDC = LddDcb->ssDemCounterPassedThreshold; /* (-) value */
    switch (*EventStatus)
    {
      case DEM_EVENT_STATUS_FAILED:
        /* Temporary counter is set to Maximum threshold */
        /* @Trace: SWS_Dem_00420
         * If the monitor reports DEM_EVENT_STATUS_FAILED, the Dem module shall
         * set the internal debounce counter value to its configured threshold
         * being the failed criteria.
         */
        /* @Trace: Dem_SUD_API_11348 */
        Dem_GssTempCounter[DebounceId] = LssMaxFDC;
        Dem_CtrDebDirection[DebounceId] = DEM_CTRDEB_DIRECTION_UP;
        LblQulifiedAsPassOrFailed = DEM_TRUE;
      break;
      case DEM_EVENT_STATUS_PASSED:
        /* Set the FDC value to minimum */
        /* Temporary counter is set to Minimum threshold */
        /* @Trace: SWS_Dem_00421
         * If the monitor reports DEM_EVENT_STATUS_PASSED, the Dem module shall
         * set the internal debounce counter value to its configured threshold
         * being the passed criteria.
         */
        /* @Trace: Dem_SUD_API_11349 */
        Dem_GssTempCounter[DebounceId] = LssMinFDC;
        Dem_CtrDebDirection[DebounceId] = DEM_CTRDEB_DIRECTION_DOWN;        
        LblQulifiedAsPassOrFailed = DEM_TRUE;
        break;
      case DEM_EVENT_STATUS_PREFAILED:
      
        /* check if JumpUp is configured and 
         * the counting direction changes from decrementing to incrementing,
         * set to the new internal dcb counter init value.
         * direction :DEM_CTRDEB_DIRECTION_UNDEF - do not jump 
         * Dem_GssTempCounter is zero */
        /* @Trace: Dem_SUD_API_11351 */
        if ((LddDcb->blDemJumpUp == DEM_TRUE) &&
            (Dem_CtrDebDirection[DebounceId] == DEM_CTRDEB_DIRECTION_DOWN))
        {
          /***           
           *                |                     Jump Up!!! (if 0 > -20) 
           * JumpUpValue  0 +---------------------#------
           *                |                     #
           *            -10 +####-----------------#------           
           *                |   #                 #
           *                |   #                 #
           * Counter    -20 +---###################-------
           *                  prepassed     prefailed 
           */
          /* @Trace: Dem_SUD_API_10410 */
          if (LddDcb->ssDemCounterJumpUpValue > Dem_GssTempCounter[DebounceId])
          {
            /* @Trace: Dem_SUD_API_11350 */
            /* Load the internal counter with jump up value */
            Dem_GssTempCounter[DebounceId] = LddDcb->ssDemCounterJumpUpValue;
          }    
        }
        Dem_CtrDebDirection[DebounceId] = DEM_CTRDEB_DIRECTION_UP;   

        /* We follow the AR4.2.2 but not 4.0.3(having bug about jump value)
         */
        /* @Trace: SWS_Dem_00425
         * If the jump-up behavior is enabled, the Dem module shall pro-vide
         * the configuration parameter DemDebounceCounterJumpUpValue defining
         * the new internal dcb counter init value. Each reporting of a pre-
         * failed value while the current dcb counter value is smaller than the
         * DemDebounceCounterJumpUpValue shall ?rst reset the dcb counter to
         * DemDebounceCounterJumpUpValue before performing the pre-failed dcb
         * event ([SWS_Dem_00418]).
         */

        /* @Trace: SWS_Dem_00418
         * The Dem module shall increment the internal debounce counter with its
         * configured step-size (refer to DemDebounceCounterIncrementStepSize),
         * when the monitor reports DEM_EVENT_STATUS_PREFAILED.
         */
        if ((LssMaxFDC - (sint16)LddDcb->usDemCountIncStepSize) >
             Dem_GssTempCounter[DebounceId])
        /* (+)FDC max - step > (+/-)FDC value */
        {
          /* Increment FDC */
          /* @Trace: Dem_SUD_API_11353 */
          Dem_GssTempCounter[DebounceId] +=
              (sint16)LddDcb->usDemCountIncStepSize;
        }
        else
        {
          /* @Trace: Dem_SUD_API_11352 */
          /* Qualify the Event to failed if the counter has reached the max
           * value */
          *EventStatus = DEM_EVENT_STATUS_FAILED;
          Dem_GssTempCounter[DebounceId] = LssMaxFDC;
          LblQulifiedAsPassOrFailed = DEM_TRUE;
        }
        break;
      case DEM_EVENT_STATUS_PREPASSED:
        /* check if JumpDown is configured and 
         * the counting direction changes from incrementing to decrementing,
         * set to the new internal dcb counter init value direction :
         * DEM_CTRDEB_DIRECTION_UNDEF - do not jump Dem_GssTempCounter is zero
         */
        /* @Trace: Dem_SUD_API_11354 */
        if ((LddDcb->blDemJumpDown == DEM_TRUE) &&
            (Dem_CtrDebDirection[DebounceId] == DEM_CTRDEB_DIRECTION_UP))
        {
          /***           
           *                 |                     
           * Counter      20 +---####################---
           *                 |   #                  #
           *              10 +####------------------#---
           *                 |                      #
           *                 |                      # 
           * JumpDownValue 0 +---+------------------#--- Jump down - (if 0 < 20)
           *                  prefailed         prepassed
           */        
          /* @Trace: Dem_SUD_API_11355 */
          if (LddDcb->ssDemCounterJumpDownValue < Dem_GssTempCounter[DebounceId])
          {
            /* @Trace: Dem_SUD_API_11345 */
            /* Load the internal counter with jump down value */
            Dem_GssTempCounter[DebounceId] = LddDcb->ssDemCounterJumpDownValue;
          }
        }
        /* @Trace: Dem_SUD_API_10411 */
        Dem_CtrDebDirection[DebounceId] = DEM_CTRDEB_DIRECTION_DOWN;   

        /* We follow the AR4.2.2 but not 4.0.3(having bug about jump value)
         */
        /* @Trace: SWS_Dem_00423
         * If the jump-down behavior is enabled, the Dem module shall
         * provide the configuration parameter DemDebounceCounterJumpDownValue
         * defining the new internal dcb counter init value. Each reporting of a
         * pre-passed value while the current dcb counter value is greater than
         * the DemDebounceCounterJumpDownValue shall first reset the dcb counter
         * to DemDebounceCounterJumpDownValue before performing the pre-passed
         * dcb event */

        /* @Trace: SWS_Dem_00419
         * The Dem module shall decrement the internal debounce counter with its
         * configured step-size (refer to DemDebounceCounterDecrementStepSize),
         * when the monitor reports DEM_EVENT_STATUS_PREPASSED.
         */
        if ((LssMinFDC + (sint16)LddDcb->usDemCountDecStepSize) <
             Dem_GssTempCounter[DebounceId])
        /* (-)FDC min + step < (+/-)FDC value */
        {
          /* @Trace: Dem_SUD_API_11346 */
          Dem_GssTempCounter[DebounceId] -=
              (sint16)LddDcb->usDemCountDecStepSize;
        }
        else
        {
          /* @Trace: Dem_SUD_API_11347 */
          /*Qualify the Event to passed if the counter has reached the min value
           */
          *EventStatus = DEM_EVENT_STATUS_PASSED;
          /* Load the internal counter with passed threshold */
          Dem_GssTempCounter[DebounceId] = LssMinFDC;
          LblQulifiedAsPassOrFailed = DEM_TRUE;
        }    

        break;
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * Default switch clause is unreachable. switch-expression */
      default:
       /* @Trace: Dem_SUD_API_10402 */
        /* Do Nothing */
        break;
    }
  }
  else
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * Above If-condition always evaluates to true. Avoid the runtime error of the
   * polyspace */
  {
    /* @Trace: Dem_SUD_API_10401 */
    DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_POINTER);
  }

  return LblQulifiedAsPassOrFailed;
}


#endif

/*******************************************************************************
 ** Function Name       : Dem_GetFDCDebounceTimeBased                         **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Gets the FaultDetectionCounter value of an event    **
 **                       with time based debounce                            **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : event                                               **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : FDC                                                 **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                                                                           **
 **                       Function(s) invoked :                               **
 **                        Dem_GetCfgDebounceTimer()                          **
 *******************************************************************************/
#if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON) 
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetFDCDebounceTimeBased(
  Dem_EventParameterCPCType event,
  P2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_VAR) FDC)
{
  P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) LddTimerStatus =
      NULL_PTR;
  P2CONST(Dem_PreDebounceTimeBasedType, AUTOMATIC, DEM_VAR) LddCfgTimer =
      NULL_PTR;
  uint32 LulTimerCounter= DEM_ZERO;
  Dem_EventStatusType LddEventStatus =
      (Dem_EventStatusType)DEM_EVENT_STATUS_FAILED;
  Std_ReturnType LddRetVal = E_NOT_OK;
  
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to false. Avoid the runtime error of the
   * polyspace */
  if (NULL_PTR  == event)
  {
    /* @Trace: Dem_SUD_API_10403 */
    DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_POINTER);
    LddRetVal = E_NOT_OK;
  }
  else if (NULL_PTR == FDC)
  {
    /* @Trace: Dem_SUD_API_10404 */
    DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_POINTER);
    LddRetVal = E_NOT_OK;
  }
  else
  {    
    LddTimerStatus = Dem_GetDebounceTimerStatus(event->ucIndexOfDebounceAry);
    LddCfgTimer = Dem_GetCfgDebounceTimer(event->ucIndexOfDebounceAry);
    /* @Trace: Dem_SUD_API_10417 */
    if ((NULL_PTR != LddCfgTimer) && (NULL_PTR != LddTimerStatus))
    {
      SchM_Enter_Dem_REQUEST_DEBOUNCETIMEBASED();

      LulTimerCounter = LddTimerStatus->tds_Counter;
      LddEventStatus = LddTimerStatus->tds_EventStatus;
      
      SchM_Exit_Dem_REQUEST_DEBOUNCETIMEBASED();
    
      *FDC = 0;
    
      /* Check whether Reported Event Status is Failed */
      switch (LddEventStatus)
      {
        case DEM_EVENT_STATUS_FAILED:
          if (DEM_ZERO == LulTimerCounter)
          {
            /* @Trace: Dem_SUD_API_11358 */
            /* Set the FDC to maximum value */
            *FDC = DEM_COUNTER_MAX;
            LddRetVal = E_OK;
          }
          else
          {
            /* @Trace: Dem_SUD_API_11356 */
            DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_DATA);
          }          
          break;
        case DEM_EVENT_STATUS_PASSED:
          if (DEM_ZERO == LulTimerCounter)
          {
            /* @Trace: Dem_SUD_API_10407 */
            /* Set the FDC value to minimum */
            *FDC = DEM_COUNTER_MIN;
            LddRetVal = E_OK;
          }
          else
          {
            /* @Trace: Dem_SUD_API_11359 */
            DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_DATA);
          }          
          break;
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
        case DEM_EVENT_STATUS_PREFAILED:
          if (DEM_ZERO != LddCfgTimer->ulDemTimeFailedThreshold)
          {
            /* Calculate the FDC from the internal counter
             *
             * 1) unit of ulDemTimeFailedThreshold is ms.
             * 2) timer counter is  0 => FDC is max
             * 3) timer counter is max => FDC is 0  */
            const uint32 LulMaxCounter =
                LddCfgTimer->ulDemTimeFailedThreshold / Dem_Task_Time;
            const uint32 LulDigit = 1000U;
    
            uint32 LulTimerValue;
            uint32 LulCounterRatio;
    
            if ((DEM_ZERO != LulMaxCounter) &&
                (LulTimerCounter <= LulMaxCounter))
            {
              /* @Trace: Dem_SUD_API_11361 */
              /* fomula : FDC = ( timer value / threshold) * FDC max */
              LulTimerValue =  (LulMaxCounter - LulTimerCounter) * LulDigit;
              LulCounterRatio =
                  ((LulTimerValue / LulMaxCounter) *
                      (uint32)DEM_COUNTER_MAX) / LulDigit;
              *FDC = (Dem_FaultDetectionCounterType)LulCounterRatio;
              LddRetVal = E_OK;
            }
            else
            {
              /* @Trace: Dem_SUD_API_11362 */
              DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_DATA);
            }
          }
          else
          /* @IF_REQ : ulDemTimeFailedThreshold shall be greater than zero */
          /* polyspace<RTE:UNR:Not a defect:No action planned>
           * Above If-condition always evaluates to true. Avoid the runtime
           * error of the polyspace */
          {
            /* @Trace: Dem_SUD_API_11360 */
            /* in case of a threshold is 0(zero) , 
             * event status is changed to failed immediately */
            *FDC = DEM_COUNTER_MAX;
            LddRetVal = E_OK;
          }
          break;
        case DEM_EVENT_STATUS_PREPASSED:
          if (DEM_ZERO != LddCfgTimer->ulDemTimePassedThreshold)
          {
            /* Calculate the FDC from the internal counter
             *
             * 1) unit of ulDemTimePassedThreshold is ms.
             * 2) timer counter is  0 => FDC is max
             * 3) timer counter is max => FDC is 0
             */
            const uint32 LulMaxCounter =
                LddCfgTimer->ulDemTimePassedThreshold / Dem_Task_Time;
            const uint32 LulDigit = 1000U;
            uint32 LulTimerValue;
            sint32 LslCounterRatio;
            
            if ((DEM_ZERO != LulMaxCounter) &&
                (LulTimerCounter <= LulMaxCounter))
            {
            	/* @Trace: Dem_SUD_API_11363 */
              /* fomula : FDC = ( timer value / threshold) * FDC min */
              LulTimerValue =  (LulMaxCounter - LulTimerCounter) * LulDigit;
              LslCounterRatio =
                  (((sint32)LulTimerValue / (sint32)LulMaxCounter) *
                      (sint32)DEM_COUNTER_MIN) / (sint32)LulDigit;
              *FDC = (Dem_FaultDetectionCounterType)LslCounterRatio;
              LddRetVal = E_OK;
            }
            else
            {
              /* @Trace: Dem_SUD_API_11364 */
              DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_DATA);
            }
          }
          else
          /* @IF_REQ : ulDemTimePassedThreshold shall be greater than zero */
          /* polyspace<RTE:UNR:Not a defect:No action planned>
           * Above If-condition always evaluates to true. Avoid the runtime
           * error of the polyspace */
          {
            /* @Trace: Dem_SUD_API_11365 */
            /* in case of a threshold is 0(zero) , 
             * event status is changed to passed immediately */
            *FDC = DEM_COUNTER_MIN;
            LddRetVal = E_OK;
          }
          /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
          /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
          break;
        default: /* DEM_EVENT_STATUS_UNDEFINED */
          /* @Trace: Dem_SUD_API_11357 */
          /* *FDC = 0; */
          break;
      }
    }
  }

  return LddRetVal;
}

/*******************************************************************************
 ** Function Name       : Dem_ProcessDebounceTimeBased                        **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Starts timer for Time based  Debouncing             **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : DebounceId                                          **
 **                                                                           **
 ** InOut parameter     : EventStatus                                         **
 **                                                                           **
 ** Output Parameters   : none                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 ** Global Variable(s)  :                                                     **
 **                                                                           **
 *******************************************************************************/
/* polyspace:begin<MISRA-C:16.7:Not a defect:Justify with annotations>
 * A pointer parameter in a function prototype should be declared as pointer to
 * const if the pointer is not used to modify the addressed object. */

/* @Trace: SRS_Diag_04067 SRS_Diag_04068
 */
FUNC(boolean, DEM_CODE)
Dem_ProcessDebounceTimeBased(
  const Dem_NumOfDebounceType DebounceId,
  P2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus)
{
  /* @Trace: SWS_Dem_00426
   * If the configuration container DemDebounceAlgorithmClass is set to
   * DemDebounceTimeBased, the Dem module shall provide an internal debounce
   * timer for each individual event, to qualify the reported event.
   */
  boolean LblQulifiedAsPassOrFailed = DEM_FALSE;

  P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) LddTimerStatus =
      NULL_PTR;
  P2CONST(Dem_PreDebounceTimeBasedType, AUTOMATIC, DEM_VAR) LddCfgTimer =
      NULL_PTR;
  /*
   * Conditions to (re)starts timer
   *  1) when the monitor reports DEM_EVENT_STATUS_PREPASSED for the first time
   *  2) EventStatus changes from DEM_EVENT_STATUS_PREPASSED to
   *  DEM_EVENT_STATUS_PREFAILED
   *  3) EventStatus changes from DEM_EVENT_STATUS_PREFAILED to
   *  DEM_EVENT_STATUS_PREPASSED
   *  4) EventStatus changes from DEM_EVENT_STATUS_FAILED to
   *  DEM_EVENT_STATUS_PREPASSED
   *  5) EventStatus changes from DEM_EVENT_STATUS_PASSED to
   *  DEM_EVENT_STATUS_PREFAILED
   *
   * Dem should set the internal debounce timer value to its configured
   * threshold to start timer. */
  
  /* [Dem431] If the monitor reports DEM_EVENT_STATUS_FAILED, the Dem module
   * shall set the internal debounce timer value to its configured threshold
   * being the failed criteria (refer to DemDebounceTimeFailedThreshold)
   *
   * Our algorithm decreases from threshold to 0,but suggested algorithm of
   * AUTOSAR increases from 0 to threshold. So counter shall be zero */

  /* @Trace: SWS_Dem_00428
   * The Dem module shall start the internal debounce timer to qualify the
   * reported event as failed when the monitor reports
   * DEM_EVENT_STATUS_PREFAILED.
   */
  /* @Trace: SWS_Dem_00429
   * If the internal debounce timer of a specific event was already triggered
   * as pre-failed or the event is qualified as failed, and the monitor reports
   * consecutively DEM_EVENT_STATUS_PREFAILED again, the Dem module shall not
   * restart the internal debounce timer.
   */

  const uint8 LaaActionByEventStatus[DEM_FOUR][DEM_SIX] =
  {
    /* New Status = DEM_EVENT_STATUS_PASSED = 0 */
    {
      DCM_DBTIME_ACT_EVENT_QUALIFIED,
      /* Old Status = DEM_EVENT_STATUS_PASSED,   = 0 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,
      /* Old Status = DEM_EVENT_STATUS_FAILED,   = 1 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,
      /* Old Status = DEM_EVENT_STATUS_PREPASSED = 2 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,
      /* Old Status = DEM_EVENT_STATUS_PREFAILED = 3 */
      DEM_ZERO,
      DCM_DBTIME_ACT_EVENT_QUALIFIED,
      /* Old Status = DEM_EVENT_STATUS_UNDEFINED = 5 */
    },
    /* New Status = DEM_EVENT_STATUS_FAILED  = 1*/
    {
      DCM_DBTIME_ACT_EVENT_QUALIFIED,
      /* Old Status = DEM_EVENT_STATUS_PASSED,   = 0 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,
      /* Old Status = DEM_EVENT_STATUS_FAILED,   = 1 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,
      /* Old Status = DEM_EVENT_STATUS_PREPASSED = 2 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,
      /* Old Status = DEM_EVENT_STATUS_PREFAILED = 3 */
      DEM_ZERO,
      DCM_DBTIME_ACT_EVENT_QUALIFIED,
      /* Old Status = DEM_EVENT_STATUS_UNDEFINED = 5 */
    },
    /* New Status = DEM_EVENT_STATUS_PREPASSED = 2*/
    {
      DCM_DBTIME_ACT_EVENT_QUALIFIED,
      /* Old Status = DEM_EVENT_STATUS_PASSED,   = 0 */
      DCM_DBTIME_ACT_START_PASS_TIMER,
      /* Old Status = DEM_EVENT_STATUS_FAILED,   = 1 */
      DCM_DBTIME_ACT_CONTINOUS,
      /* Old Status = DEM_EVENT_STATUS_PREPASSED = 2 */
      DCM_DBTIME_ACT_START_PASS_TIMER,
      /* Old Status = DEM_EVENT_STATUS_PREFAILED = 3 */
      DEM_ZERO,
      DCM_DBTIME_ACT_START_PASS_TIMER,
      /* Old Status = DEM_EVENT_STATUS_UNDEFINED = 5 */
    },
    /* New Status = DEM_EVENT_STATUS_PREFAILED = 3*/
    {
      DCM_DBTIME_ACT_START_FAIL_TIMER,
      /* Old Status = DEM_EVENT_STATUS_PASSED,   = 0 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,
      /* Old Status = DEM_EVENT_STATUS_FAILED,   = 1 */
      DCM_DBTIME_ACT_START_FAIL_TIMER,
      /* Old Status = DEM_EVENT_STATUS_PREPASSED = 2 */
      DCM_DBTIME_ACT_CONTINOUS,
      /* Old Status = DEM_EVENT_STATUS_PREFAILED = 3 */
      DEM_ZERO,
      DCM_DBTIME_ACT_START_FAIL_TIMER,
      /* Old Status = DEM_EVENT_STATUS_UNDEFINED = 5 */
    }
  };  

  LddCfgTimer = Dem_GetCfgDebounceTimer(DebounceId);
  LddTimerStatus = Dem_GetDebounceTimerStatus(DebounceId);
  /* @Trace: Dem_SUD_API_10416 */
  if ((LddCfgTimer != NULL_PTR) &&
      (LddTimerStatus != NULL_PTR)  &&
      (*EventStatus < DEM_FOUR) &&
      (LddTimerStatus->tds_EventStatus < DEM_SIX))
  {    

    SchM_Enter_Dem_REQUEST_DEBOUNCETIMEBASED();
    /* stores old event status */

    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
    switch (LaaActionByEventStatus[*EventStatus]
                                   [LddTimerStatus->tds_EventStatus])
    {
      case DCM_DBTIME_ACT_START_FAIL_TIMER:
        if (DEM_ZERO != LddCfgTimer->ulDemTimeFailedThreshold)
        {
          /* @Trace: Dem_SUD_API_11366 */
          LddTimerStatus->tds_Counter =
              LddCfgTimer->ulDemTimeFailedThreshold/Dem_Task_Time;
          LddTimerStatus->tds_EventStatus = *EventStatus;
        }
        else
        /* polyspace<RTE:UNR:Not a defect:No action planned>
         * Above If-condition always evaluates to true. */
        {
          /* @Trace: Dem_SUD_API_10405 */
          /* if threshold is 0, event status is changed to failed immediately */
          LddTimerStatus->tds_Counter = DEM_ZERO;
          LddTimerStatus->tds_EventStatus = DEM_EVENT_STATUS_FAILED;
          
          *EventStatus = DEM_EVENT_STATUS_FAILED; 
          LblQulifiedAsPassOrFailed = DEM_TRUE;
        }
        break;
        /* @Trace: SWS_Dem_00432
         * The Dem module shall start the internal debounce timer to qualify the
         * reported event as passed when the monitor reports
         * DEM_EVENT_STATUS_PREPASSED.
         */
        /* @Trace: SWS_Dem_00433
         * If the internal debounce timer of a specific event was already
         * triggered as pre-passed or the event is qualified as passed, and the
         * monitor reports consecutively DEM_EVENT_STATUS_PREPASSED again, the
         * Dem module shall not restart the internal debounce timer.
         */
      case DCM_DBTIME_ACT_START_PASS_TIMER:
        if (DEM_ZERO != LddCfgTimer->ulDemTimePassedThreshold)
        {
          /* @Trace: Dem_SUD_API_11367 */
          /* @Trace: SWS_Dem_00435
           * If the monitor reports DEM_EVENT_STATUS_PASSED the Dem module shall
           * set the internal debounce timer value to its configured threshold
           * being the passed criteria (refer to DemDebounceTimePassedThreshold).
           */
          LddTimerStatus->tds_Counter =
              LddCfgTimer->ulDemTimePassedThreshold/Dem_Task_Time;
          LddTimerStatus->tds_EventStatus = *EventStatus;
        }
        else
        /* polyspace<RTE:UNR:Not a defect:No action planned>
         * Above If-condition always evaluates to true.*/
        {
          /* @Trace: Dem_SUD_API_10406 */
          /* if threshold is 0, event status is changed to passed immediately */
          LddTimerStatus->tds_Counter = DEM_ZERO;
          LddTimerStatus->tds_EventStatus = DEM_EVENT_STATUS_PASSED;
          
          *EventStatus = DEM_EVENT_STATUS_PASSED; 
          LblQulifiedAsPassOrFailed = DEM_TRUE;
        }
        break;
      case DCM_DBTIME_ACT_EVENT_QUALIFIED:
        /* Stop timer. Refer to Dem431 */
        /* @Trace: SWS_Dem_00431
         * If the monitor reports DEM_EVENT_STATUS_FAILED, the Dem module shall
         * set the internal debounce timer value to its configured threshold
         * being the failed criteria (refer to DemDebounceTimeFailedThreshold).
         */
        /* @Trace: Dem_SUD_API_11368 */
        LddTimerStatus->tds_Counter = 0;
        LddTimerStatus->tds_EventStatus = *EventStatus;
        
        LblQulifiedAsPassOrFailed = DEM_TRUE;
        break;
      default: /* DCM_DBTIME_ACT_CONTINOUS*/
        /* @IF_REQ: Does it need...?  */
        /* @Trace: Dem_SUD_API_11369 */
        LddTimerStatus->tds_EventStatus = *EventStatus;
        break;
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */   
    SchM_Exit_Dem_REQUEST_DEBOUNCETIMEBASED();
  }    

  return LblQulifiedAsPassOrFailed;
}
/* polyspace:end<MISRA-C:16.7:Not a defect:Justify with annotations>
 * A pointer parameter in a function prototype should be declared as pointer to
 * const if the pointer is not used to modify the addressed object. */

/*******************************************************************************
 ** Function Name       : Dem_ProcessDebounceTimer                            **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Performs internal calculation for Time based        **
 **                       Debouncing                                          **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : none                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                                                                           **
 **                       Function(s) invoked :                               **
 **                       Dem_ProcessEventStatus                              **
 *******************************************************************************/
/* @Trace: SRS_Diag_04068 SRS_Diag_04125
 */
FUNC(void, DEM_CODE)Dem_ProcessDebounceTimer(void)
{
  /* @Trace: Dem_SUD_API_11370 */
  #if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11373 */
  P2CONST(Dem_PreDebounceTimeBasedType, AUTOMATIC, DEM_VAR) LddCfgTimer =
      NULL_PTR;
  P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) LddTimerStatus =
      NULL_PTR;

  const Dem_EventStatusType LaaFilterOfEventStatus[] =
  {
    DEM_FALSE, /* DEM_EVENT_STATUS_PASSED     0x00 unused */
    DEM_FALSE, /* DEM_EVENT_STATUS_FAILED     0x01 unused */
    DEM_TRUE,  /* DEM_EVENT_STATUS_PREPASSED  0x02 used   */
    DEM_TRUE,  /* DEM_EVENT_STATUS_PREFAILED  0x03 used   */
    DEM_FALSE,
    DEM_FALSE  /* DEM_EVENT_STATUS_UNDEFINED  0x05 unused   */
  };    
  const Dem_EventStatusType LaaResultOfTimeout[] =
  {
    DEM_ZERO,                /* DEM_EVENT_STATUS_PASSED     0x00 unused */
    DEM_ZERO,                /* DEM_EVENT_STATUS_FAILED     0x01 unused */
    DEM_EVENT_STATUS_PASSED, /* DEM_EVENT_STATUS_PREPASSED  0x02 used   */
    DEM_EVENT_STATUS_FAILED, /* DEM_EVENT_STATUS_PREFAILED  0x03 used   */
    DEM_ZERO,
    DEM_ZERO                 /* DEM_EVENT_STATUS_UNDEFINED  0x05 unused   */
  };
  Dem_NumOfDebounceType LddDbIndex;
  #endif

  /* @IF_REQ: The event  queue shall be used for loop optimization */
  /* Loop for the time debounce */
  /* @Trace: Dem_SUD_API_11374 */
  #if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11372 */
  for (LddDbIndex = DEM_ZERO;
       LddDbIndex < DEM_NUMBER_OF_PRE_DEBOUNCE_TIME;
       LddDbIndex++)
  {
    /* @Trace: Dem_SUD_API_10408 */
    LddCfgTimer= Dem_GetCfgDebounceTimer(LddDbIndex);
    LddTimerStatus = Dem_GetDebounceTimerStatus(LddDbIndex);
    
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * If-condition always evaluates to true. Avoid the runtime error of the
     * polyspace */
    /* @Trace: Dem_SUD_API_11375 */
    if ((LddCfgTimer != NULL_PTR) && (LddTimerStatus != NULL_PTR))
    {
      /* @IF_REQ: at first, shall check LddTimerStatus->tds_Counter > DEM_ZERO)
       * for optimization */
      /* Check the status of all enable conditions configured for the event.
      It is a condition of the specific event(Don't care a combined event) */
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition can evaluate to true or false according to the request of
       * application.*/

      /* @Trace: SWS_Dem_00655
       * If the configuration parameter DemDebounceBehavior is set
       * to DEM_DEBOUNCE_STATUS_FREEZE, the Dem module shall freeze the internal
       * debounce timer when at least one enable condition for the related event
       * is set to not fulfilled.
       * */

      /* @Trace: SWS_Dem_00678
       * If the configuration parameter DemDebounceBehavior is set
       * to DEM_DEBOUNCE_STATUS_FREEZE, the Dem module shall freeze the internal
       * debounce timer when ControlDTCSetting is set to disabled for the
       * related event.
       * */

      /* @Trace: SWS_Dem_00685
       * If the API Dem_ResetEventDebounceStatus is called with
       * DEM_DEBOUNCE_STATUS_FREEZE, it shall freeze the related internal
       * debounce timer
       * */
      /* @Trace: Dem_SUD_API_11376 */
      /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
      if ((LddCfgTimer->t_EventId <= DEM_NUMBER_OF_EVENTS) &&
          (DEM_NO_EVENT != LddCfgTimer->t_EventId))
      {
        /* @Trace: Dem_SUD_API_11377 */
        if ((E_OK == Dem_GetEventConditionsAndControlDTCSetting(
            LddCfgTimer->t_EventId)) &&
           (DEM_TRUE != Dem_EnableFreeze[LddCfgTimer->t_EventId - DEM_ONE])
           )
        {
          Dem_OperationCycleStateType LddOpCycleState =
              (Dem_OperationCycleStateType)DEM_CYCLE_STATE_NOTSTART;

          (void)Dem_GetOpCycleStateByEvent(
              LddCfgTimer->t_EventId, &LddOpCycleState);
          /* @Trace: Dem_SUD_API_11378 */
          if (DEM_CYCLE_STATE_START == LddOpCycleState)
          {
            SchM_Enter_Dem_REQUEST_DEBOUNCETIMEBASED();
            if ((LddTimerStatus->tds_Counter > DEM_ZERO) &&
                (LddTimerStatus->tds_EventStatus <
                    COUNTOF(LaaFilterOfEventStatus)))
            {
              LddTimerStatus->tds_Counter--;
              if ((DEM_ZERO == LddTimerStatus->tds_Counter) &&
                  (DEM_TRUE ==
                      LaaFilterOfEventStatus[LddTimerStatus->tds_EventStatus]))
              {
                /* @Trace: Dem_SUD_API_11380 */
                SchM_Exit_Dem_REQUEST_DEBOUNCETIMEBASED();
                (void)Dem_ProcessEventStatus(
                    LddCfgTimer->t_EventId,
                    LaaResultOfTimeout[LddTimerStatus->tds_EventStatus]);
              }
              else
              {
                /* @Trace: Dem_SUD_API_11371 */
                SchM_Exit_Dem_REQUEST_DEBOUNCETIMEBASED();
              }
            }
            else
            {
              /* @Trace: Dem_SUD_API_11379 */
              SchM_Exit_Dem_REQUEST_DEBOUNCETIMEBASED();
            }
          }
        }
      }
    }
  }
  #endif
}

#endif

/*******************************************************************************
** Function Name        : Dem_ResetFaultDectectionCounter                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Reset fault dectection counter for kinds of         **
**                        debounce                                            **
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
** Remarks              : None                                                **
*******************************************************************************/
FUNC(void, DEM_CODE)
Dem_ResetFaultDectectionCounter(
  Dem_EventIdType EventId)
{
  Dem_EventParameterPCType LddEvent= &Dem_Event[EventId - DEM_ONE];
  switch(DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(LddEvent->ParamFieldsA))
  {
    /* Debounce Counter Based */
    /* #if (DEM_DEBOUNCE_COUNTER_SUPPORT == STD_ON) */
    /* @Trace: Dem_SUD_API_11381 */
    #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
    case DEM_DEBOUNCE_COUNTER_BASED:
      /* polyspace<RTE:UNR:Not a defect:No action planned>
       * If-condition always evaluates to true. Avoid the runtime error of the
       * polyspace */
      /* @Trace: Dem_SUD_API_10409 */
      if ( LddEvent->ucIndexOfDebounceAry < DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER)
      {
        /* @Trace: Dem_SUD_API_11382 */
        Dem_GssTempCounter[LddEvent->ucIndexOfDebounceAry] = 0;
        Dem_CtrDebDirection[LddEvent->ucIndexOfDebounceAry] =
            DEM_CTRDEB_DIRECTION_UNDEF;
      }
      break;
    #endif

      /* Debounce Time Based */
     /* @Trace: Dem_SUD_API_11383 */
    #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
    case DEM_DEBOUNCE_TIME_BASED:
    {
      P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) LddTimerStatus;
      LddTimerStatus =
          Dem_GetDebounceTimerStatus(LddEvent->ucIndexOfDebounceAry);
      /* @Trace: Dem_SUD_API_11384 */
      if (LddTimerStatus != NULL_PTR)
      {
        /* @Trace: Dem_SUD_API_10412 */
        LddTimerStatus->tds_Counter = DEM_ZERO;
        LddTimerStatus->tds_EventStatus = DEM_EVENT_STATUS_UNDEFINED;
      }
      break;
    }
    #endif
    /* @Trace: Dem_SUD_API_11385 */
    #if (DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL > DEM_ZERO)
    case DEM_DEBOUNCE_MONITOR_BASED:
      /*
       * Dem_SetOperationCycle
       * Note: For resetting the fault detection counter implemented in a
       * monitor, the Dem module uses the callback-function InitMonitorForEvent
       * (refer to section 7.2 and InitMonitorForEvent).
       */
      /* @Trace: Dem_SUD_API_10413 */
      break;
    #endif

    default:
      /* @Trace: Dem_SUD_API_10414 */
      /* LddRetVal = E_NOT_OK; */
      break;
  }
}

/*******************************************************************************
** Function Name        : Dem_InitDebounce                                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Init status and value counter for debounce          **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
*******************************************************************************/
FUNC(void, DEM_CODE) Dem_InitDebounce(void)
{
  /* @Trace: Dem_SUD_API_11386 */
  #if ((DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO) || \
       (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON))
  /* @Trace: Dem_SUD_API_11390 */
  Dem_NumOfDebounceType LddIdx;
  #endif

  /* @IF_REQ : Redesign -> the counter debounce shall be not dependent on
   * Library */
  /* #if (DEM_DEBOUNCE_COUNTER_SUPPORT == STD_ON) */
  /* @Trace: Dem_SUD_API_11391 */
  #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11392 */
  for (LddIdx = DEM_ZERO; LddIdx < DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER; LddIdx++)
  {
    /* @Trace: Dem_SUD_API_11393 */
    Dem_GssTempCounter[LddIdx] = 0;
    Dem_CtrDebDirection[LddIdx] = DEM_CTRDEB_DIRECTION_UNDEF;
  }
  #endif
  /* @Trace: Dem_SUD_API_11394 */
  #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
  Dem_EventIdType LddEventId;
  /* @Trace: Dem_SUD_API_11395 */
  for (LddEventId = DEM_ONE; LddEventId <= DEM_NUMBER_OF_EVENTS; LddEventId++)
  {
    /* @Trace: Dem_SUD_API_11396 */
    Dem_EnableFreeze[LddEventId - DEM_ONE] = DEM_FALSE;
  }

  /* The time debounce is not dependent on Library */
  /* @Trace: Dem_SUD_API_11397 */
  #if (DEM_NUMBER_OF_PRE_DEBOUNCE_TIME > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11389 */
  for (LddIdx = DEM_ZERO; LddIdx < DEM_NUMBER_OF_PRE_DEBOUNCE_TIME; LddIdx++)
  {
    P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) LddTimerStatus ;
    LddTimerStatus = Dem_GetDebounceTimerStatus(LddIdx);
    /* @Trace: Dem_SUD_API_11388 */
    if (LddTimerStatus != NULL_PTR)
    {
      /* @Trace: Dem_SUD_API_11387 */
      LddTimerStatus->tds_Counter = 0;
      LddTimerStatus->tds_EventStatus = DEM_EVENT_STATUS_UNDEFINED;
    }
  }
  #endif
  #endif
}

#define DEM_STOP_SEC_CODE
#include "MemMap.h"
