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
**  FILE-NAME : EcuM_Internal.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Internal Functionality implementation of EcuM                 **
**              EcuM_SearchMode                                               **
**              EcuM_SearchShutdownCause                                      **
**              EcuM_SearchWakeupSource                                       **
**              EcuM_SearchGoDownUser                                         **
**              EcuM_SearchAlarmClockUser                                     **
**              EcuM_ValidationProtocol                                       **
**              EcuM_OsWaitEvent                                              **
**              EcuM_OsSetEvent                                               **
**              EcuM_GoSleepSeq                                               **
**              EcuM_ClearAlarm                                               **
**              EcuM_WakeupRestartSeq                                         **
**              EcuM_CheckResetReason                                         **
**              EcuM_WakeUpReactSeq                                           **
**              EcuM_CheckSlaveSleep                                          **
**              EcuM_PollSeq                                                  **
**              EcuM_GetGptTicks                                              **
**              EcuM_ProcessModeHandingChangedRequest                         **
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
** 1.2.0     04-Oct-2022   TriBD             R44_2021 #27878                  **
** 1.1.6     10-Aug-2022   Manje Woo         CP44-727                         **
** 1.1.5     15-Mar-2022   TriBD             R44_2021 #24753                  **
** 1.1.4     17-Jan-2022   TriBD             R44_2021 #20832                  **
** 1.1.0     22-Mar-2021   TinhPV3           R44_2021 #17960                  **
** 1.0.1     05-Mar-2021   TinhPV3           R44_2021 #17961                  **
** 0.0.3     30-Jul-2020   ThiNT8            R44-Redmine #655, #14588         **
** 0.0.2     07-Apr-2020   LocLT5            R44-Redmine #655, #8670          **
** 0.0.1     14-Feb-2020   ThangMA            R44-Redmine #655, #8668         **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "EcuM_Internal.h"
#include "EcuM_Ram.h"

#include "Rte_EcuM.h"
#include "SchM_EcuM.h"
#include "BswM_EcuM.h"
#include "BswM.h"
#include "Mcu.h"
#include "Os.h"
#include "Rte_Main.h"

#include "HwResource.h"
#if HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE)
#include "Reg_Macros.h"
#include "Reg_eSys_Rtc.h"
#endif

#if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
#include "Os_PortTypes.h"
#endif

#if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
#include "Gpt.h"
#endif

#if (STD_ON == ECUM_DEV_ERROR_DETECT)
#include "Det.h"
#endif

/*******************************************************************************
**                        Global Data                                         **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define ECUM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : EcuM_SearchMode                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching index corresponding to a specific mode**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : mode                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : lpModeIdx                                           **
**                                                                            **
** Return parameter     : TRUE, FALSE                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_SleepModes, EcuM_ShutdownCauseTarget,          **
**                        EcuM_ResetModeId                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(boolean, ECUM_CODE) EcuM_SearchMode
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) lpModeIdx, EcuM_ShutdownModeType mode)
{
  uint8 modeIndex;

  /* variable to break the FOR loop */
  boolean lblSearchResult;
  /* @Trace: EcuM_SUD_API_904 */
  /* Set the search result flag to FALSE */
  lblSearchResult = FALSE;

  /* Check the mode by linear search */
  if (ECUM_SHUTDOWN_TARGET_SLEEP ==
    EcuM_ShutdownCauseTarget.SelectShutdownTarget)
  {
    /* Set the initial value */
    *lpModeIdx = ECUM_NO_OF_SLEEPMODES;

    for (modeIndex = (uint8)ECUM_ZERO; ((modeIndex < ECUM_NO_OF_SLEEPMODES) &&
      (lblSearchResult == FALSE)); modeIndex++)
    {
      /* Is 'mode' matches with the configured SleepMode */
      if (EcuM_SleepModes[modeIndex].SleepModeId == mode)
      {
        /* @Trace: EcuM_SUD_API_903 */
        /* Set the search result flag to TRUE */
        lblSearchResult = TRUE;

        /* Update index for Request Array index */
        *lpModeIdx = modeIndex;
      }
    }
  }
  /* polyspace +1 RTE:UNR [Not a defect:Low] "The value of SelectShutdownTarget shall can change to RESET value by EcuM_SelectShutdownTarget method" */
  else if (ECUM_SHUTDOWN_TARGET_RESET ==
    EcuM_ShutdownCauseTarget.SelectShutdownTarget)
  {
    /* Set the initial value */
    *lpModeIdx = ECUM_NO_OF_RESETMODES;

    for (modeIndex = (uint8)ECUM_ZERO; ((modeIndex < ECUM_NO_OF_RESETMODES) &&
      (lblSearchResult == FALSE)); modeIndex++)
    {
      /* Is 'mode' matches with the configured ResetMode */
      if (EcuM_ResetModeId[modeIndex] == mode)
      {
        /* @Trace: EcuM_SUD_API_902 */
        /* Set the search result flag to TRUE */
        lblSearchResult = TRUE;

        /* Update index for Request Array index */
        *lpModeIdx = modeIndex;
      }
    }
  }
  else
  {
    /* do nothing  */
  }

  /* Return TRUE if found else FALSE */
  return (lblSearchResult);
}/* End of function body */


/*******************************************************************************
** Function Name        : EcuM_SearchShutdownCause                            **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching index corresponding to a specific     **
**                         ShutdownCause                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : target                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : lpCauseIdx                                          **
**                                                                            **
** Return parameter     : TRUE, FALSE                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_ShutdownCauseId                                **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(boolean, ECUM_CODE) EcuM_SearchShutdownCause
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) lpCauseIdx,
  EcuM_ShutdownCauseType target)
{
  uint8 causeIndex;

  /* variable to break the FOR loop */
  boolean searchResult;
  /* @Trace: EcuM_SUD_API_906 */
  /* Set the search result flag to FALSE */
  searchResult = FALSE;

  /* Set the initial value */
  /* polyspace-begin RTE:IDP [Not a defect:Low] "The pointer has checked for not NULL." */
  *lpCauseIdx = (uint8)ECUM_NO_OF_SHUTDOWNCAUSE;/* polyspace MISRA-C3:D4.14 [Not a defect:Low] "The pointer has checked for not NULL." */
  /* polyspace-end RTE:IDP [Not a defect:Low] "The pointer has checked for not NULL." */
  /* Check the ShutdownCause by linear search */
  for (causeIndex = (uint8)ECUM_ZERO; ((causeIndex < ECUM_NO_OF_SHUTDOWNCAUSE) &&
    (searchResult == FALSE)); causeIndex++)
  {
    /* Is 'ShutdownCause' matches with the configured ShutdownCause */
    if (EcuM_ShutdownCauseId[causeIndex] == target)
    {
      /* @Trace: EcuM_SUD_API_905 */
      /* Set the search result flag to TRUE */
      searchResult = TRUE;

      /* Update index for Request Array Index */
      *lpCauseIdx = causeIndex;
    }
  }

  /* Return TRUE if found else FALSE */
  return (searchResult);
} /* End of function body */

/*******************************************************************************
** Function Name        : EcuM_SearchWakeupSource                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching index corresponding to a specific user**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : WakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : lpSourceIdx                                         **
**                                                                            **
** Return parameter     : TRUE, FALSE                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_WakeupSource          **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(boolean, ECUM_CODE) EcuM_SearchWakeupSource
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) lpSourceIdx,
  EcuM_WakeupSourceType WakeupSource)
{
  uint8 sourceIndex;

  /* variable to break the FOR loop */
  boolean searchResult;
  /* variables to store the number of wakeup source */
  uint8 noOfWakeupSource;
  /* @Trace: EcuM_SUD_API_929 */
  /* Set the search result flag to FALSE */
  searchResult = FALSE;
  /* set number of wakeup source */
  noOfWakeupSource = (uint8)ECUM_NO_OF_WAKEUPSOURCES;
  /* Set the initial value */
  *lpSourceIdx = noOfWakeupSource;

  /* Check the WakeupSource by linear search */
  for (sourceIndex = (uint8)ECUM_ZERO; ((sourceIndex < ECUM_NO_OF_WAKEUPSOURCES) &&
    (searchResult == FALSE)); sourceIndex++)
  {
    /* Is 'WakeupSource' matches with the configured WakeupSource */
    if ((WakeupSource & EcuM_WakeupSource[sourceIndex].WakeupSourceId) ==
      EcuM_WakeupSource[sourceIndex].WakeupSourceId)
    {
      /* @Trace: EcuM_SUD_API_930 */
      /* Set the search result flag to TRUE */
      searchResult = TRUE;

      /* Update index for Request Array Index */
      *lpSourceIdx = sourceIndex;
    }
  }

  /* Return TRUE if found else FALSE */
  return (searchResult);
} /* End of function body */


/*******************************************************************************
** Function Name        : EcuM_SearchGoDownUser                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching index corresponding to a specific user**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : lpGoDownUserIdx                                     **
**                                                                            **
** Return parameter     : TRUE, FALSE                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_GoDownAllowedUser     **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(boolean, ECUM_CODE) EcuM_SearchGoDownUser
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) lpGoDownUserIdx, EcuM_UserType user) /* polyspace MISRA-C3:8.13 [Not a defect:Low] "The parameters pointer type  conform to AUTOSAR R4.4.0 specfication" */
{
  /* variable to break the FOR loop */
  boolean searchResult;

  /* Set the search result flag to FALSE */
  searchResult = FALSE;
  #if (ECUM_ZERO != ECUM_NO_OF_GODOWNUSERS)
  uint8 godownIndex;
  /* @Trace: EcuM_SUD_API_919 */
  /* Set the initial value */
  *lpGoDownUserIdx = ECUM_NO_OF_GODOWNUSERS;

  /* Check the user by linear search */
  for (godownIndex = (uint8)ECUM_ZERO; ((godownIndex < ECUM_NO_OF_GODOWNUSERS) &&
    (searchResult == FALSE)); godownIndex++)
  {
    /* Is 'user' matches with the configured users */
    if (EcuM_GoDownAllowedUser[godownIndex] == user)
    {
      /* @Trace: EcuM_SUD_API_920 */
      /* Set the search result flag to TRUE */
      searchResult = TRUE;

      /* Update index for Request Array Index */
      *lpGoDownUserIdx = godownIndex;
    }
  }
  #else
  /* @Trace: EcuM_SUD_API_918 */
  ECUM_UNUSED_PTR(lpGoDownUserIdx);
  ECUM_UNUSED(user);
  #endif
  /* Return TRUE if found else FALSE */
  return (searchResult);
}/* End of function body */


/*******************************************************************************
** Function Name        : EcuM_SearchAlarmClockUser                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching index corresponding to a specific user**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : lpAlarmUserIdx                                      **
**                                                                            **
** Return parameter     : TRUE, FALSE                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_AlarmClock            **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
FUNC(boolean, ECUM_CODE) EcuM_SearchAlarmClockUser
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) lpAlarmUserIdx, EcuM_UserType user)
{
  /* @Trace: EcuM_SUD_API_938 */
  uint8 alarmIndex;

  /* variable to break the FOR loop */
  boolean searchResult;

  /* Set the search result flag to FALSE */
  searchResult = FALSE;

  /* Set the initial value */
  *lpAlarmUserIdx = ECUM_NO_OF_ALARMS;

  /* Check the user by linear search */
  for (alarmIndex = (uint8)ECUM_ZERO; ((alarmIndex < ECUM_NO_OF_ALARMS) &&
    (searchResult == FALSE)); alarmIndex++)
  {
    /* Is 'user' matches with the configured users */
    if (EcuM_AlarmClock[alarmIndex].User == user)
    {
      /* Set the search result flag to TRUE */
      searchResult = TRUE;

      /* Update index for Request Array Index */
      *lpAlarmUserIdx = alarmIndex;
    }
  }

  /* Return TRUE if found else FALSE */
  return (searchResult);
} /* End of EcuM_SearchAlarmClockUser */

#endif /* (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

/*******************************************************************************
** Function Name        : EcuM_ValidationProtocol                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching a validated Wakeup Source             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_PendingWakeupEvents, EcuM_State                **
**                        EcuM_WakeupSource                                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_CheckValidation, BswM_EcuM_CurrentState        **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09100 SRS_ModeMgm_09097 SRS_EcuM_AR_00004 */
FUNC(void, ECUM_CODE) EcuM_ValidationProtocol(void)
{
  /* Local variable for wakeup sources */
  EcuM_WakeupSourceType wakeupSources;
  uint8 i;

  /* @Trace: EcuM_SUD_API_933 */
  EcuM_State = ECUM_STATE_WAKEUP_VALIDATION;
  BswM_EcuM_CurrentState(EcuM_State);

  /* Loop FOR all configured wakeup sources */
  for (i = (uint8)ECUM_ZERO; i < ECUM_NO_OF_WAKEUPSOURCES;
    i++)
  {
    wakeupSources = EcuM_WakeupSource[i].WakeupSourceId;

    /* Is wakeup source pending */
    if (((EcuM_PendingWakeupEvents & wakeupSources) ==
      wakeupSources))
    {
      /* @Trace: EcuM_SUD_API_932 */
      /* Invoke callout for wakeup validation */
      EcuM_CheckValidation(wakeupSources);
    }
  }
} /* End of EcuM_ValidationProtocol */


/*******************************************************************************
** Function Name        : EcuM_OsWaitEvent                                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It is invoked by master core for all slave core     **
**                        for the synchronized shutdown.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_OsTask, EcuM_WaitingTaskId, EcuM_EventMask     **
**                        EcuM_ShutdownCauseTarget                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        WaitEvent(), GetEvent(), ClearEvent()               **
*******************************************************************************/
#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
FUNC(void, ECUM_CODE) EcuM_OsWaitEvent(void)
{
  #if (ECUM_ZERO != ECUM_LOOP_COUNT_MAX)
  volatile uint32 loopCount;
  #endif
  uint8 eventIdx;
  uint8 taskIdx;
  EventMaskType eventMask;
  EventMaskType waitEventMask;
  EventMaskType eventBit;
  StatusType status;

  /* @Trace: EcuM_SUD_API_912 */
  eventMask = (EventMaskType)ECUM_ZERO;
  waitEventMask = (EventMaskType)ECUM_ZERO;
  (void)GetTaskID(&EcuM_WaitingTaskId);

  taskIdx = (uint8)ECUM_ZERO;
  while (taskIdx < ECUM_NO_OF_OS_TASKS)
  {
    if (EcuM_WaitingTaskId == EcuM_OsTask[taskIdx])
    {
      /* @Trace: EcuM_SUD_API_911 */
      /* Loop for number of events configured to get eventMask */
      for (eventIdx = (uint8)ECUM_ZERO; eventIdx < ECUM_NO_OF_EVENT_MASKS;
        eventIdx++)
      {
        /* Get the event mask for the configured events
             by bitwise OR operation */
        waitEventMask |= EcuM_EventMask[eventIdx];
      }

      #if (ECUM_ZERO != ECUM_LOOP_COUNT_MAX)
      loopCount = 0u;
      #endif
      while (waitEventMask != (EventMaskType)ECUM_ZERO)
      {
        /* If OsResource not used, using WaitEvent and GetEvent loop */
        /* polyspace-begin RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
        if ((EcuM_ShutdownCauseTarget.SelectShutdownTarget == ECUM_SHUTDOWN_TARGET_RESET) ||
            (EcuM_ShutdownCauseTarget.SelectShutdownTarget == ECUM_SHUTDOWN_TARGET_OFF))
        {
          (void)WaitEvent(waitEventMask);
        }
        /* polyspace-end RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
        /* If OsResource used(ECUM_STATE_SLEEP), using GetEvent loop */
        status = GetEvent(EcuM_WaitingTaskId, &eventMask);
        /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "It's required to check the return value from OS during runtime" */
        if (status == (StatusType)E_OK)
        {
          for (eventIdx = (uint8)ECUM_ZERO; eventIdx < ECUM_NO_OF_EVENT_MASKS;
            eventIdx++)
          {
            eventBit = EcuM_EventMask[eventIdx];

            if ((eventMask & eventBit) == eventBit)
            {
              (void)ClearEvent(eventBit);
              waitEventMask &= (~eventBit);
            }
          } /* End of for (eventIdx.. */
        } /* End of if (status is equal (StatusType)E_OK) */

        #if (ECUM_ZERO != ECUM_LOOP_COUNT_MAX)
        /* @Trace: EcuM_SUD_API_913 */
        /* Fail safe for infinite loop */
        if (loopCount >= ECUM_LOOP_COUNT_MAX)
        {
          break;
        }
        loopCount++;
		#endif
      } /* End of while (waitEventMask != (EventMaskType)ECUM_ZERO) */

      /* Set the condition to come out of while loop */
      taskIdx = ECUM_NO_OF_OS_TASKS;

    } /* End of if (status is (StatusType)E_OK) */
    else
    {
      taskIdx++;
    }
  } /* End of for loop */

} /* End of EcuM_OsWaitEvent */

/*******************************************************************************
** Function Name        : EcuM_OsSetEvent                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It is invoked by slave core                         **
**                        for the synchronized shutdown.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : CoreId                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_ShutdownMask, EcuM_HaltMask,                   **
**                        EcuM_PollMask, EcuM_EventMask,                      **
**                        EcuM_WaitingTaskId, EcuM_CoreID                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        GetSpinlock(), ReleaseSpinlock(), SetEvent()        **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_OsSetEvent(CoreIdType lddCoreId)
{
  uint8 coreIdx;
  uint8 eventIdx;
  uint8 coreMask;

  /* @Trace: EcuM_SUD_API_914 */
  coreIdx = (uint8)ECUM_ONE;
  while(coreIdx < ECUM_NO_OF_CORES)
  {
    if (lddCoreId == EcuM_CoreID[coreIdx])
    {
      coreMask = ((uint8)ECUM_ONE << lddCoreId);

      (void)GetSpinlock(ECUM_OS_SPINLOCK);

      EcuM_ShutdownMask &= (~coreMask);
      EcuM_HaltMask &= (~coreMask);
      EcuM_PollMask &= (~coreMask);

      (void)ReleaseSpinlock(ECUM_OS_SPINLOCK);

      eventIdx = coreIdx - (uint8)ECUM_ONE;

      /* Call Os API SetEvent to come out of wait state for each event mask */
      (void)SetEvent(EcuM_WaitingTaskId, EcuM_EventMask[eventIdx]);

      /* Set the condition to come out of while loop */
      coreIdx = ECUM_NO_OF_CORES;
    }

    else
    {
      coreIdx++;
    }
  }
} /* End of EcuM_OsSetEvent */

#endif /* End of if (ECUM_MULTI_CORE_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : EcuM_GoSleepSeq                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : In the GoSleepseq the ECU Manager module configures **
**                        hardware for the upcoming sleep phase and sets the  **
**                        ECU up for the next wakeup event.                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : lucSleepModeIndex                                   **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : TRUE, FALSE                                         **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_ShutdownCauseTarget, EcuM_SleepModes           **
**                        EcuM_WakeupSource, EcuM_State                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_IsMasterCore, EcuM_EnableWakeupSources         **
**                        BswM_EcuM_CurrentWakeup                             **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09100 */
FUNC(boolean, ECUM_CODE) EcuM_GoSleepSeq
(P2VAR(uint8, AUTOMATIC, ECUM_APPL_DATA) lucSleepModeIndex)
{
  EcuM_WakeupSourceType wakeupSources;

  uint8 i;
  uint8 lucWksIndex;

  boolean lblGoSleepResult;
  lblGoSleepResult = FALSE;

  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  boolean isMasterCore;
  /* Local variable for master core result */

  isMasterCore = EcuM_IsMasterCore();
  #endif

  i = (uint8)ECUM_ZERO;
  /* Loop for the configured sleep modes */
  while (i < ECUM_NO_OF_SLEEPMODES)
  {
    /* To get the index of the structure array EcuM_SleepModes for
     *   current sleep mode */
    if (EcuM_SleepModes[i].SleepModeId ==
      EcuM_ShutdownCauseTarget.SleepMode)
    {
      /* @Trace: EcuM_SUD_API_917 */
      /* Invoke callout to enable wakeup sources configured for this
       *   sleep mode */
      EcuM_EnableWakeupSources(EcuM_SleepModes[i].WakeupSourceMask);

      #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
      if (TRUE == isMasterCore)
      #endif
      {
        /* @Trace: EcuM_SUD_API_103 */
        /* Loop FOR all configured wakeup sources */
        for (lucWksIndex = (uint8)ECUM_ZERO; lucWksIndex < ECUM_NO_OF_WAKEUPSOURCES;
          lucWksIndex++)
        {
          wakeupSources = EcuM_WakeupSource[lucWksIndex].WakeupSourceId;

          /* Is wakeup source pending */
          if (((EcuM_SleepModes[i].WakeupSourceMask &
            wakeupSources) != (uint32)ECUM_ZERO))
          {
            /* Indicate current status of Wakeup source to BswM */
            BswM_EcuM_CurrentWakeup(wakeupSources, ECUM_WKSTATUS_NONE);
          }
        }

        /* Enable data protection  */
        SchM_Enter_EcuM_STATE_PROTECTION();
        /* Update the state to sleep */
        EcuM_State = ECUM_STATE_GO_SLEEP;
        /* Disable data protection */
        SchM_Exit_EcuM_STATE_PROTECTION();
      }

      *lucSleepModeIndex = i;

      lblGoSleepResult = TRUE;

      /* To come out of FOR loop */
      i = ECUM_NO_OF_SLEEPMODES;
    } /* End of if (EcuM_SleepModes[i].SleepModeId is equal
       *EcuM_ShutdownCauseTarget.SleepMode) */
    i++;
  }

  return lblGoSleepResult;
} /* End of EcuM_GoSleepSeq */


/*******************************************************************************
** Function Name        : EcuM_ClearAlarm                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It is used to clearing the Alarms corresponding     **
**                        to Master Alarm.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_AlarmTime, EcuM_MasterAlarm              **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
FUNC(void, ECUM_CODE) EcuM_ClearAlarm(void)
{
  /* @Trace: EcuM_SUD_API_941 */
  uint8 alarmIndx;
  /* Enable data protection */
  SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
  /* Clear the master alarm */
  EcuM_MasterAlarm = (uint32)ECUM_ZERO;
  /* Disable data protection  */
  SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
  alarmIndx = (uint8)ECUM_ZERO;
  while (alarmIndx < ECUM_NO_OF_ALARMS)
  {
    /* Enable data protection  */
    SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
    /* Clear the validation timeout array */
    EcuM_AlarmTime[alarmIndx] = (uint32)ECUM_ZERO;
    /* Disable data protection */
    SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
    alarmIndx++;
  }
}

#endif /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

/*******************************************************************************
** Function Name        : EcuM_WakeupRestartSeq                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It gives the Wakeup Restart sequence used by EcuM   **
**                        to make the EcuM Up for any wake up event.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : SleepIndex                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_SleepModes, EcuM_State                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_IsMasterCore, DisableAllInterrupts, Mcu_SetMode**
**                        EnableAllInterrupts, EcuM_GetPendingWakeupEvents,   **
**                        EcuM_DisableWakeupSources, BswM_EcuM_CurrentWakeup, **
**                        EcuM_AL_DriverRestart, BswM_EcuM_CurrentState       **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09100 SRS_ModeMgm_09097 SRS_EcuM_AR_00004 */
FUNC(void, ECUM_CODE) EcuM_WakeupRestartSeq(void)
{
  EcuM_WakeupSourceType pendingWakeupEvents;
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  boolean isMasterCore;
  /* Local variable for master core result */
  isMasterCore = EcuM_IsMasterCore();
  #endif

  #if (ECUM_MCU_NORMAL_MODE_SUPPORT == STD_ON)
  /* @Trace: EcuM_SUD_API_931 */
  /* Disable all interrupts */
  DisableAllInterrupts();
  /* Set MCU mode as NORMAL */
  Mcu_SetMode(ECUM_MCU_NORMAL_MODE);
  /* Enable all interrupts */
  EnableAllInterrupts();
  #endif

  /* @Trace: EcuM_SUD_API_190 */
  /* Invoke callout to disable all wakeup sources which are configured
   * for the particular sleep mode*/
  pendingWakeupEvents = EcuM_GetPendingWakeupEvents();
  EcuM_DisableWakeupSources(pendingWakeupEvents);

  /* @Trace: EcuM_SUD_API_191 */
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  if (TRUE == isMasterCore)
  #endif
  {
    /* Initiating Driver Restart */
    /* polyspace +1 MISRA-C3:2.2 [Justified:Medium] "Scope to be implemented by user" */
    EcuM_AL_DriverRestart();
    /* Enable data protection */
    SchM_Enter_EcuM_STATE_PROTECTION();
    /* Update the current state to start up one */
    EcuM_State = ECUM_STATE_STARTUP_ONE;
    /* Disable the data protection */
    SchM_Exit_EcuM_STATE_PROTECTION();
    /* Indicate state change to BswM */
    BswM_EcuM_CurrentState(EcuM_State);
  }
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  else
  {
    /*
     * MISRA Rule   : 14.2
     * Message      : This statements has no side effects it can be removed.
     * Reason       : The statement is used only to avoid compilation warning.
     * Verification : However, part of the code is verified manually
     *                 and it is not having any impact.
     */
     /*To avoid compilation warning*/
  }
  #endif
} /* End of EcuM_WakeupRestartSeq(void) */


/*******************************************************************************
** Function Name        : EcuM_CheckResetReason                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This service checks the reset reason.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ResetReason                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_PendingWakeupEvents, EcuM_WakeupSource,        **
**                        EcuM_ValidatedWakeupEvents                          **
**                        Function(s) invoked    :                            **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09126 SRS_ModeMgm_09274 SRS_ModeMgm_09275
 * SRS_ModeMgm_09100 */
FUNC(void, ECUM_CODE) EcuM_CheckResetReason(Mcu_ResetType ResetReason)
{
  uint8 i;
  boolean wakeupSourceFlag;

  wakeupSourceFlag = FALSE;

  /* Loop for wakeup source */
  for (i = (uint8)ECUM_ZERO; i < ECUM_NO_OF_WAKEUPSOURCES; i++)
  {
    /* Map reset reason obtained from Mcu to wakeup source */
    if (EcuM_WakeupSource[i].ResetReason == ResetReason)
    {
      wakeupSourceFlag = TRUE;

      /* Is validation required for the wakeup source */
      if (EcuM_WakeupSource[i].WakeupValidationTimeOut != (uint16)ECUM_ZERO)
      {
        /* @Trace: EcuM_SUD_API_218 */
        /* Update EcuM_PendingWakeupEvents to remember the wakeup source
         *   resulting from the reset reason translation */
        EcuM_PendingWakeupEvents |= EcuM_WakeupSource[i].WakeupSourceId;
      }
      else
      {
		/* @Trace: EcuM_SUD_API_984 */
        /* Update EcuM_ValidatedWakeupEvents to remember the wakeup source
         *   resulting from the reset reason translation */
        EcuM_ValidatedWakeupEvents |= EcuM_WakeupSource[i].WakeupSourceId;
      }
    } /* End of if ((Mcu_ResetType)EcuM_WakeupSource[i].ResetReason is equal
       *ResetReason) */
  }
  /* @Trace: EcuM_SUD_API_105 */
  if (wakeupSourceFlag != TRUE)
  {
    /* Update EcuM_ValidatedWakeupEvents to remember the wakeup source
     * resulting from the reset reason translation */
    EcuM_ValidatedWakeupEvents |= ECUM_WKSOURCE_RESET;
  }
} /* End of EcuM_CheckResetReason */



/*******************************************************************************
** Function Name        : EcuM_PollSeq                                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It gives the poll sequence used by the EcuM to      **
**                        check for any pending wakeup event.                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : lucSleepModeIndex                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_WakeupSource, EcuM_ValidatedWakeupEvents,      **
**                        EcuM_PendingWakeupEvents                            **
**                        Function(s) invoked    :                            **
**                        EcuM_WakeupRestartSeq, EcuM_ClearAlarm,             **
**                        EcuM_CheckWakeup, EcuM_SleepActivity                **
**                                                                            **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_PollSeq(void)
{
  /* Local variable for looping */
  uint8 loop;
  uint8 i;
  /* @Trace: EcuM_SUD_API_915 */
  /* Initialize loop variable */
  loop = (uint8)ECUM_ONE;
  while ((loop != (uint8)ECUM_ZERO)
         #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
         || (EcuM_AlarmExpired != TRUE)
         #endif
         )
  {
    /* Invoke to poll wakeup source */
    /* polyspace +1 MISRA-C3:2.2 [Justified:Medium] "Scope to be implemented by user" */
    EcuM_SleepActivity();
    i = (uint8)ECUM_ZERO;
    /* For all wakeup sources */
    while (i < ECUM_NO_OF_WAKEUPSOURCES)
    {
      /* Check whether polling is set for specific wakeup source */
      /* polyspace-begin RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
      if (EcuM_WakeupSource[i].WakeupSourcePolling ==
        (boolean)ECUM_ONE)
      {
        /* Invoke to poll wakeup source */
        EcuM_CheckWakeup(EcuM_WakeupSource[i].WakeupSourceId);

        if ((EcuM_ValidatedWakeupEvents != ECUM_NO_EVENTS) ||
          (EcuM_PendingWakeupEvents != ECUM_NO_EVENTS))
        {
          /* @Trace: EcuM_SUD_API_916 */
          #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)		  
          /* Clear the alarm */
          EcuM_ClearAlarm();
          #endif
          /* Perform wakeup restart sequence */
          EcuM_WakeupRestartSeq();

          /* update with zero to come out of loop */
          loop = (uint8)ECUM_ZERO;
          i = ECUM_NO_OF_WAKEUPSOURCES;
        }
      } /* End of if (EcuM_WakeupSource[i].WakeupSourcePolling is equal
         * ECUM_ONE) */
      else
      {
        loop = (uint8)ECUM_ZERO;
      }
      /* polyspace-end RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
      i++;
    }
  }
} /* End of EcuM_PollSeq */


#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
/*******************************************************************************
** Function Name        : EcuM_SlaveShutDownOrSleep                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : If Multicore support is ON,It gives the poll        **
**                        sequence used by the EcuM to check for any pending  **
**                        wakeup events for slave.                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : lddCoreId                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_HaltMask,             **
**                        EcuM_ShutdownMask, EcuM_PollMask                    **
**                        Function(s) invoked    :                            **
**                        EcuM_WakeupRestartSeq ,EcuM_GoSleepSeq              **
**                        EcuM_OsSetEvent,Mcu_SetMode,EnableAllInterrupts     **
**                        DisableAllInterrupts, EcuM_ReleaseOSResource        **
**                        EcuM_GetOSResource                                  **
*******************************************************************************/
/* @Trace: SRS_EcuM_AR_00011 SRS_BSW_00172 */
FUNC(void, ECUM_CODE) EcuM_SlaveShutDownOrSleep(CoreIdType lddCoreId)
{
  uint8 slaveSleepModeIndex;
  uint8 coreMask;
  boolean sleepModeValid;
  /* polyspace +2 RTE:OVFL [Not a defect:Low] "coreMask has been checked manual and not outside */
  /* polyspace +1 RTE:SHF [Not a defect:Low] "coreMask has been checked manual and not outside */
  coreMask = ((uint8)ECUM_ONE << lddCoreId);

  /* Perform slave shutdown sequence */
  if ((EcuM_ShutdownMask & coreMask) == coreMask)
  {
    /* @Trace: EcuM_SUD_API_925 */
    EcuM_OnGoOffOne();

    /* Deinitializes the BSW Mode Manager */
    BswM_Deinit(); //LOOP FOR ALL PARTITIONS ON RUNNING CORE

    /* Deinitialize the schedule manager */
    SchM_Deinit();
    /* Set the event to signal the master about slave shutdown */
    EcuM_OsSetEvent(lddCoreId);
  }
  else if ((EcuM_HaltMask & coreMask) == coreMask)
  {
    /* Perform slave sleep sequence */
    /* For Redmine #5257 */
    sleepModeValid = EcuM_GoSleepSeq(&slaveSleepModeIndex);

    if(sleepModeValid == TRUE) /* sleepModeValid is valid */
    {
      /* While in transition to sleep, if there is a wakeup source
       * start wakeup reaction sequence and do not enter halt sequence */
      if ((EcuM_ValidatedWakeupEvents != ECUM_NO_EVENTS) ||
        (EcuM_PendingWakeupEvents != ECUM_NO_EVENTS))
      {
        /* @Trace: EcuM_SUD_API_923 */
        EcuM_WakeupRestartSeq();
      }
      else
      {
        /* @Trace: EcuM_SUD_API_106 */
        /* Halt sequence */
        EcuM_SlaveCoreHaltSequence(slaveSleepModeIndex, lddCoreId);
      }
    }/* End of if(sleepModeValid is TRUE)  */
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    else /* sleepModeValid is invalid */
    {
	  /* @Trace: EcuM_SUD_API_924 */
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_INSTANCE_ID,
        ECUM_E_UNKNOWN_SLEEP_MODE);
    }
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  }
  else if ((EcuM_PollMask & coreMask) == coreMask)
  {
    /* Perform slave sleep sequence */
    /* For Redmine #5257 */
    sleepModeValid = EcuM_GoSleepSeq(&slaveSleepModeIndex);

    if(sleepModeValid == TRUE) /* sleepModeValid is valid */
    {
      /* While in transition to sleep, if there is a wakeup source
           start wakeup reaction sequence and do not enter poll sequence */
      if ((EcuM_ValidatedWakeupEvents != ECUM_NO_EVENTS) ||
        (EcuM_PendingWakeupEvents != ECUM_NO_EVENTS))
      {
		/* @Trace: EcuM_SUD_API_922 */
        EcuM_WakeupRestartSeq();
      }
      else
      {
        /* @Trace: EcuM_SUD_API_107 */
        /* Poll sequence */
        EcuM_SlaveCorePollSequence(slaveSleepModeIndex, lddCoreId);
      }
    }/* End of if(sleepModeValid is TRUE)  */
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    else /* sleepModeValid is invalid */
    {
      /* @Trace: EcuM_SUD_API_921 */
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_INSTANCE_ID,
        ECUM_E_UNKNOWN_SLEEP_MODE);
    }
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  }
  else
  {
    /* do nothing  */
  }
} /* End of EcuM_SlaveShutDownOrSleep */

/*******************************************************************************
** Function Name        : EcuM_SlaveCoreHaltSequence                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Implement sequence slave core go halt.              **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : lddCoreId                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_HaltMask,             **
**                        EcuM_ShutdownMask, EcuM_PollMask                    **
**                        Function(s) invoked    :                            **
**                        EcuM_WakeupRestartSeq ,EcuM_GoSleepSeq              **
**                        EcuM_OsSetEvent,Mcu_SetMode,EnableAllInterrupts     **
**                        DisableAllInterrupts, EcuM_ReleaseOSResource        **
**                        EcuM_GetOSResource                                  **
*******************************************************************************/
/* @Trace: SRS_EcuM_AR_00011 SRS_BSW_00172 */
FUNC(void, ECUM_CODE) EcuM_SlaveCoreHaltSequence(
  VAR(uint8,ECUM_VAR) slaveSleepModeIndex, VAR(CoreIdType, ECUM_VAR) lddCoreId)
{
   /* Halt sequence */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
  /* polyspace +1 MISRA-C3:14.3 DEFECT:DEAD_CODE MISRA-C3:2.1 [Justified:Medium] "Condition is changed by user configuration" */
  if (EcuM_SleepModes[slaveSleepModeIndex].SleepModeSuspnd == TRUE)
  {
    /* @Trace: EcuM_SUD_API_888 */
    /* For Redmine #5257 */
    /* Get OS Resource */
    EcuM_GetOSResource();

    /* Set the event to signal the master about slave sleep */
    EcuM_OsSetEvent(lddCoreId);
    /* @Trace: EcuM_SUD_API_106*/
    /* Disable all the interrupts  */
    DisableAllInterrupts();
    /* Set MCU mode */
    Mcu_SetMode(EcuM_SleepModes[slaveSleepModeIndex].McuSleepModeType);
    /* Enable all the interrupts */
    EnableAllInterrupts();

    /* Start wakeup restart sequence if any validated or pending
                                                      wakeup events */
    /* redmine #17451 */
    /* polyspace-begin RTE:UNR [Not a defect:Low] "The statement is used only to avoid compilation warning." */
    /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "This point is multi task, global variables EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents would been updated by other task." */
    /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "This point is multi task, global variables EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents would been updated by other task." */
    /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This point is related to power consumption , global variables EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents would been updated by wake-up interrupt after MCU was in saving mode" */

    if ((EcuM_ValidatedWakeupEvents != ECUM_NO_EVENTS) ||
      (EcuM_PendingWakeupEvents != ECUM_NO_EVENTS))
    {
      /* @Trace: EcuM_SUD_API_887 */
      EcuM_WakeupRestartSeq();
    }

    /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This point is related to power consumption , global variables EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents would been updated by wake-up interrupt after MCU was in saving mode" */
    /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "This point is multi task, global variables EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents would been updated by other task." */
    /* polyspace-end RTE:UNR [Not a defect:Low] "The statement is used only to avoid compilation warning." */
    /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "This point is multi task, global variables EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents would been updated by other task." */

    /* Release Resource Redmine #5257 */
    EcuM_ReleaseOSResource();
  }
  /* polyspace-end RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
}

/*******************************************************************************
** Function Name        : EcuM_SlaveCorePollSequence                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Implement sequence slave core go Poll.              **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : lddCoreId                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_HaltMask,             **
**                        EcuM_ShutdownMask, EcuM_PollMask                    **
**                        Function(s) invoked    :                            **
**                        EcuM_WakeupRestartSeq ,EcuM_GoSleepSeq              **
**                        EcuM_OsSetEvent,Mcu_SetMode,EnableAllInterrupts     **
**                        DisableAllInterrupts, EcuM_ReleaseOSResource        **
**                        EcuM_GetOSResource                                  **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_SlaveCorePollSequence(
  VAR(uint8,ECUM_VAR) slaveSleepModeIndex, VAR(CoreIdType, ECUM_VAR) lddCoreId)
{
  /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "This point is multi task, global variables EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents would been updated by other task." */
  /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "This point is multi task, global variables EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents would been updated by other task." */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "Wake Up event shall be updated after api Mcu_setMode is called so polyspace can't detect is point" */
  /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This point is related to power consumption , global variables EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents would been updated by wake-up interrupt after MCU was in saving mode" */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
  if (EcuM_SleepModes[slaveSleepModeIndex].SleepModeSuspnd ==
    FALSE)
    {
    /* @Trace: EcuM_SUD_API_886 */
    /* For Redmine #5257 */
    /* Get OS Resource */
    EcuM_GetOSResource();

    /* Set the event to signal the master about slave sleep */
    EcuM_OsSetEvent(lddCoreId);
    /* @Trace: EcuM_SUD_API_107*/
    /* Disable all the interrupts */
    DisableAllInterrupts();
    /* Set MCU mode */
    Mcu_SetMode(EcuM_SleepModes[slaveSleepModeIndex].McuSleepModeType);
    /* Enable all interrupts */
    EnableAllInterrupts();

    /* Start wakeup restart sequence if any validated or pending
        wakeup events */
    /* redmine #17451 */
    if ((EcuM_ValidatedWakeupEvents != ECUM_NO_EVENTS) ||
      (EcuM_PendingWakeupEvents != ECUM_NO_EVENTS))
    {
      /* @Trace: EcuM_SUD_API_885 */
      EcuM_WakeupRestartSeq();
    }
    else
    {
      /* Do nothing */
    }
    /* Release Resource Redmine #5257 */
    EcuM_ReleaseOSResource();
  }
  /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This point is related to power consumption , global variables EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents would been updated by wake-up interrupt after MCU was in saving mode" */
  /* polyspace-end RTE:UNR [Not a defect:Low] "Wake Up event shall be updated after api Mcu_setMode is called so polyspace can't detect is point" */
  /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "This point is multi task, global variables EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents would been updated by other task." */
  /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "This point is multi task, global variables EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents would been updated by other task." */
  /* polyspace-end RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
}
#endif

#if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
/*******************************************************************************
** Function Name        : EcuM_GetGptTicks                                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It gives the next GPT ticks.                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : lpTickValue                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        EcuM_MasterAlarm, EcuM_RunningTimer                 **
**                        Function(s) invoked : None                          **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_GetGptTicks
  (P2VAR(uint32, AUTOMATIC, ECUM_DATA) lpTickValue)
{
  if (EcuM_MasterAlarm > EcuM_RunningTimer)
  {
    /* @Trace: EcuM_SUD_API_940 */
    *lpTickValue = (uint32)ECUM_GPT_CHANNEL_TICK_MAX;
  }
  else
  {
    /* @Trace: EcuM_SUD_API_939 */
    *lpTickValue = (uint32)ECUM_ZERO;
  }
}
#endif /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

#if (STD_ON == ECUM_DEV_ERROR_DETECT)
/*******************************************************************************
** Function Name        : EcuM_DetReportError                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : If Dev Error Detection is enabled,                  **
**                        it stores last error status and reports to Det.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucApiId, LucErrorId                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : Dev Error Detection should be enabled.              **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_LastDetError                                   **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_DetReportError(uint8 LucApiId,
  uint8 LucErrorId)
{
  /* @Trace: EcuM_SUD_API_926 */
  /* Local variable for return value */
  Std_ReturnType stdRetVal;

  EcuM_LastDetError.InstanceId = ECUM_INSTANCE_ID;
  EcuM_LastDetError.ApiId = LucApiId;
  EcuM_LastDetError.ErrorId = LucErrorId;

  /*Report to DET */
  stdRetVal = Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID,
    LucApiId, LucErrorId);

  return stdRetVal;
}
#endif

/*******************************************************************************
** Function Name        : EcuM_SearchSleepModeWakeupSource                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching index corresponding to a specific user**
**                        ONLY IN current Sleep Mode Wakeup source            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : WakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : lpSourceIdx                                         **
**                                                                            **
** Return parameter     : TRUE, FALSE                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_GusSleepModeIndex     **
**                        EcuM_WakeupSource, EcuM_SleepModeId, EcuM_SleepModes**
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(boolean, ECUM_CODE) EcuM_SearchSleepModeWakeupSource
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) lpSourceIdx,
  EcuM_WakeupSourceType WakeupSource)
{
  uint8 sourceIndex;

  /* variable to break the FOR loop */
  boolean searchResult;
  /* @Trace: EcuM_SUD_API_928 */
  /* Set the search result flag to FALSE */
  searchResult = FALSE;

  /* Set the initial value */
  *lpSourceIdx = ECUM_NO_OF_WAKEUPSOURCES;

  /* For Redmine #5257 */
  if (EcuM_SleepModeId != ECUM_INVALID_SLEEPMODEID)
  {
    /* Check the WakeupSource by linear search */
    for (sourceIndex = (uint8)ECUM_ZERO; ((sourceIndex < ECUM_NO_OF_WAKEUPSOURCES) &&
      (searchResult == FALSE)); sourceIndex++)
    {
      if(EcuM_SleepModeId < ECUM_NO_OF_SLEEPMODES)
      {
        /* Is 'WakeupSource' matches with the configured WakeupSource with
         * Sleepmode MASK */
        if ( ((WakeupSource & EcuM_WakeupSource[sourceIndex].WakeupSourceId) &
          (EcuM_SleepModes[EcuM_SleepModeId].WakeupSourceMask)) ==
          EcuM_WakeupSource[sourceIndex].WakeupSourceId)
        {
          /* @Trace: EcuM_SUD_API_927 */
          /* Set the search result flag to TRUE */
          searchResult = TRUE;

          /* Update index for Request Array index */
          *lpSourceIdx = sourceIndex;
        }
      }
    }
  }

  /* Return TRUE if found else FALSE */
  return (searchResult);
} /* End of function body */


/*******************************************************************************
** Function Name        : EcuM_GetOSResource                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Releasing OS Resource in wakeup sequence        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     : EcuM_OsResources           **
**                                                                            **
**                        Function(s) invoked    : GetResource, GetCoreID     **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_GetOSResource (void)
{
  #if (ECUM_NO_OF_OSRESOURCES > ECUM_ZERO)
  uint8 osResInd;
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  /* @Trace: EcuM_SUD_API_910 */
  osResInd = (uint8)GetCoreID();
  /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "The coreID got from OS side and could be updated in the runtime environment" */
  if (osResInd < ECUM_NO_OF_OSRESOURCES)
  {
    (void)GetResource(EcuM_OsResources[osResInd]);
  }
  #else
  /* @Trace: EcuM_SUD_API_909 */
  osResInd = (uint8)ECUM_ZERO;
  (void)GetResource(EcuM_OsResources[osResInd]);
  #endif
  #endif /* End of if (ECUM_NO_OF_OSRESOURCES > ECUM_ZERO) */
} /* End of function body */

/*******************************************************************************
** Function Name        : EcuM_ReleaseOSResource                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Releasing OS Resource in wakeup sequence        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     : EcuM_OsResources           **
**                                                                            **
**                        Function(s) invoked    : ReleaseResource, GetCoreID **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_ReleaseOSResource (void)
{
  #if (ECUM_NO_OF_OSRESOURCES > ECUM_ZERO)
  uint8 osResInd;
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  /* @Trace: EcuM_SUD_API_908 */
  osResInd = (uint8)GetCoreID();
  /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "The coreID got from OS side and could be updated in the runtime environment" */
  if (osResInd < ECUM_NO_OF_OSRESOURCES)
  {
    (void)ReleaseResource(EcuM_OsResources[osResInd]);
  }
  #else
  /* @Trace: EcuM_SUD_API_907 */
  osResInd = (uint8)ECUM_ZERO;
  (void)ReleaseResource(EcuM_OsResources[osResInd]);
  #endif
  #endif /* End of if (ECUM_NO_OF_OSRESOURCES > ECUM_ZERO) */
} /* End of function body */


/*******************************************************************************
** Function Name        : EcuM_McuPostInit                                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Post init step for Mcu                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        REG_WRITE32, RTC_CLEAR_ALL_INTERRUPT,               **
**                        Mcu_ClearColdResetStatus                            **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_McuPostInit (void)
{
  /*  For Redmine #5213  */
  /* @Trace: EcuM_SUD_API_220 */
  #if HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE)
/* polyspace<MISRA-C:11.3:Not a defect:Justify with annotations> Not a defect */
  REG_WRITE32(RTC_CR, (uint32)0x00000000UL);
/* polyspace<MISRA-C:11.3:Not a defect:Justify with annotations> Not a defect */
  RTC_CLEAR_ALL_INTERRUPT();
  #endif

  /* For Redmine #4945  */
  #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
  #ifdef MCU_CLR_COLD_RESET_STAT_API
  Mcu_ClearColdResetStatus();
  #endif
  #endif
} /* End of function body */

/*******************************************************************************
** Function Name        : EcuM_EnableInterrupts                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Enable Interrupt Fail Safe                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_EnableInterrupts (void)
{
  /* @Trace: EcuM_SUD_API_221 */
  /* For Tricore Compiler */
  #ifdef __TASKING__
  /* polyspace<MISRA-C:8.1:Not a defect:Justify with annotations> Not a defect */
  (void) __enable();
  #endif

  /* For GreenHills Compiler */
  #ifdef __ghs__
  /* polyspace<MISRA-C:8.1:Not a defect:Justify with annotations> Not a defect */
  (void) __EI();
  #endif

} /* End of function body */

/*******************************************************************************
** Function Name        : EcuM_GoHaltSequence                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : EcuM_GoHaltSequence                                 **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK, E_NOT_OK)                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_HaltMask, EcuM_SleepCycle, EcuM_AlarmCycle     **
**                        EcuM_AlarmExpired, EcuM_NextTick, EcuM_WakeupType   **
**                        EcuM_PostRunRequestStatus, EcuM_RunRequestStatus    **
**                        EcuM_PendingWakeupEvents, EcuM_ValidatedWakeupEvents**
**                                                                            **
**                        Function(s) invoked    :                            **
**                        GetSpinlock, ReleaseSpinlock, EcuM_DetReportError   **
**                        EcuM_OsWaitEvent, Gpt_EnableWakeup, EcuM_GetGptTicks**
**                        Gpt_EnableNotification, Gpt_StartTimer, Gpt_SetMode **
**                        DisableAllInterrupts, EcuM_GenerateRamHash,         **
**                        EcuM_SetMode, EnableAllInterrupts,                  **
**                        EcuM_EnableInterrupts, EcuM_CheckRamHash,           **
**                        EcuM_ErrorHook, EcuM_ClearAlarm, Gpt_StopTimer,     **
**                        Gpt_DisableWakeup, Gpt_DisableNotification,         **
**                        EcuM_WakeupRestartSeq EcuM_ClearWakeupEvent,        **
**                        EcuM_ReleaseOSResource                              **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00337 SRS_BSW_00327 SRS_BSW_00339 SRS_EcuM_AR_00008 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoHaltSequence(uint8 sleepModeIndex)
{
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  /* Initialize stdRetVal with E_OK */
  stdRetVal = (Std_ReturnType)E_OK;
  uint8 retVal;
  /* Get OS Resource */
  /* Set Breakpoint Here for MODE_TEST_ECUM_LOWPOWER_MANUAL1 */
  EcuM_GetOSResource();
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  /* @Trace: EcuM_SUD_API_895 */
  (void)GetSpinlock(ECUM_OS_SPINLOCK);
  /* Set a sleep flag to be read by slave core */
  EcuM_HaltMask =  ECUM_SLAVE_CORE_MASK;
  (void)ReleaseSpinlock(ECUM_OS_SPINLOCK);
  /* Wait for all slaves to complete their sleep sequence */
  EcuM_OsWaitEvent();
  /* Redmine #17451 */
  /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "This point is multi task, global variables EcuM_HaltMask would been updated by other task." */
  /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "This point is multi task, global variables EcuM_HaltMask would been updated by other task." */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "EcuM_HaltMask shall be updated in other event" */
  /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "Related to cores synchronization mechanism, firstly EcuM_HaltMask is set to ECUM_SLAVE_CORE_MASK, and after that EcuM_HaltMask mask would been clear by slave cores in the waiting time EcuM_OsWaitEvent()" */
  if (EcuM_HaltMask != (uint8)ECUM_ZERO)
  {
    /* @Trace: EcuM_SUD_API_894 */
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GODOWNHALTPOLL_SID, ECUM_E_SHUTDOWN_FAILED);
    #endif
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif
  {
    EcuM_SleepCycle = TRUE;

    #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
    /* @Trace: EcuM_SUD_API_893 */
    if (TRUE == EcuM_AlarmCycle)
    {
      /* Set Breakpoint Here for MODE_TEST_ECUM_LOWPOWER_MANUAL2 */
      Gpt_EnableWakeup(ECUM_GPT_CHANNEL_ID);
    }

    /* Enable data protection */
    SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
    EcuM_AlarmExpired =  FALSE;
    /* Disable data protection */
    SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
    /* Set Breakpoint Here for MODE_TEST_ECUM_LOWPOWER_MANUAL3 */
    while (EcuM_AlarmExpired == FALSE)
    #endif
    {
      #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
      SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
      /* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
      if (EcuM_AlarmCycle == TRUE)
      {
        EcuM_GetGptTicks(&EcuM_NextTick);

        if (EcuM_NextTick > (uint32)ECUM_ZERO)
        {
          Gpt_EnableNotification(ECUM_GPT_CHANNEL_ID);
          Gpt_StartTimer(ECUM_GPT_CHANNEL_ID, EcuM_NextTick);
          Gpt_SetMode(GPT_MODE_SLEEP);
        }
        else
        {
          EcuM_AlarmExpired = TRUE;
          EcuM_SleepCycle =  FALSE;
        }

        EcuM_AlarmCycle =  FALSE;
      }
      SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
      #endif
      /* Set Breakpoint Here for MODE_TEST_ECUM_LOWPOWER_MANUAL4 */
      DisableAllInterrupts();

      if ((TRUE == EcuM_SleepCycle) &&
        ((ECUM_NO_EVENTS == EcuM_ValidatedWakeupEvents) &&
        (ECUM_NO_EVENTS == EcuM_PendingWakeupEvents)) &&
        (((uint8)ECUM_RUNSTATUS_RELEASED) == EcuM_RunRequestStatus) &&
        (((uint8)ECUM_RUNSTATUS_REQUESTED) != EcuM_PostRunRequestStatus))
      {
        /* @Trace: EcuM_SUD_API_889 */
        /* Invoke before putting ECU to sleep */
        /* polyspace +1 MISRA-C3:2.2 [Justified:Medium] "Scope to be implemented by user" */
        EcuM_GenerateRamHash();

        /* Set Mcu mode */
        /* Set Breakpoint Here for MODE_TEST_ECUM_LOWPOWER_MANUAL1~4 */
        EcuM_SetMode(EcuM_SleepModes[sleepModeIndex].McuSleepModeType);
      }
      #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
      else
      {
        EcuM_AlarmExpired = TRUE;
      }
      #endif
      EnableAllInterrupts();
      /* polyspace-begin MISRA-C3:2.2 [Not a defect:Justify with annotations] "Not a defect" */
      /* EI Fail Safe Redmine #8552 */
      EcuM_EnableInterrupts();
      /* polyspace-begin MISRA-C3:2.2 [Not a defect:Justify with annotations] "Not a defect" */
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /*  Check Wakeup ISR calls EcuM_SetWakeupEvent  */
      if ((ECUM_NO_EVENTS == EcuM_ValidatedWakeupEvents) &&
        (ECUM_NO_EVENTS == EcuM_PendingWakeupEvents))
      {
        /* @Trace: EcuM_SUD_API_892 */
        /* Report to DET */
        (void)EcuM_DetReportError(ECUM_GODOWNHALTPOLL_SID,
          ECUM_E_UNKNOWN_WAKEUP_SOURCE);
        stdRetVal = (Std_ReturnType)E_NOT_OK;
      }
      #endif
    }
    /* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

    /* @Trace: EcuM_SUD_API_196 */
    /* Invoke after ECU is woken up from sleep */
    retVal = EcuM_CheckRamHash();
    /* Is RAM Integrity test failed */
    if (retVal == (uint8)ECUM_ZERO)
    {
      /* Invoke Callout error hook */
      EcuM_ErrorHook((uint16)ECUM_E_RAM_CHECK_FAILED);
    }
  }/* End of if (EcuM_HaltMask is (uint8)ECUM_ZERO) */
  /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "Related to cores synchronization mechanism, firstly EcuM_HaltMask is set to ECUM_SLAVE_CORE_MASK, and after that EcuM_HaltMask mask would been clear by slave cores in the waiting time EcuM_OsWaitEvent()" */
  /* polyspace-end RTE:UNR [Not a defect:Low] "EcuM_HaltMask shall be updated in other event" */
  /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "This point is multi task, global variables EcuM_HaltMask would been updated by other task." */
  /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "This point is multi task, global variables EcuM_HaltMask would been updated by other task." */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents shall be updated in wakeup event" */
  if ((ECUM_NO_EVENTS != EcuM_ValidatedWakeupEvents) ||
    (ECUM_NO_EVENTS != EcuM_PendingWakeupEvents))
  {
    /* Start wakeup restart sequence if any validated or pending
     * wakeup events */
    #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
    /* @Trace: EcuM_SUD_API_891 */
    if (ECUM_WK_KNOWN_ALARM == EcuM_WakeupType)
    {
      /* Clear alarm */
      EcuM_ClearAlarm();

      /* Stop timer  */
      Gpt_StopTimer(ECUM_GPT_CHANNEL_ID);
      Gpt_DisableWakeup(ECUM_GPT_CHANNEL_ID);
      Gpt_DisableNotification(ECUM_GPT_CHANNEL_ID);
      Gpt_SetMode(GPT_MODE_NORMAL);
    }
    #endif

    /* Perform wakeup restart sequence */
    EcuM_WakeupRestartSeq();
    /* Set Breakpoint Here for MODE_TEST_ECUM_LOWPOWER_MANUAL1~4 */
    EcuM_ClearWakeupEvent(ECUM_WKSOURCE_ALL_SOURCES);
  }
  /* polyspace-end RTE:UNR [Not a defect:Low] "EcuM_ValidatedWakeupEvents, EcuM_PendingWakeupEvents shall be updated in wakeup event" */
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  else
  {
    /* @Trace: EcuM_SUD_API_890 */
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GODOWNHALTPOLL_SID,
      ECUM_E_UNKNOWN_WAKEUP_SOURCE);
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  /* Release OS Resource */
  EcuM_ReleaseOSResource();
  return stdRetVal;
} /* End of function body */

/*******************************************************************************
** Function Name        : EcuM_GoPollSequence                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : EcuM_GoPollSequence                                 **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_PollMask, EcuM_SleepModes                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_GetOSResource, Mcu_SetMode,                    **
**                        EnableAllInterrupts, GetSpinlock, ReleaseSpinlock,  **
**                        EcuM_OsWaitEvent, EcuM_DetReportError, EcuM_PollSeq,**
**                        EcuM_ReleaseOSResource                              **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoPollSequence(uint8 sleepModeIndex )
{
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  /* Initialize stdRetVal with E_OK */
  stdRetVal = (Std_ReturnType)E_OK;
  /* Get OS Resource */
  EcuM_GetOSResource();

  #if (STD_OFF == ECUM_MULTI_CORE_SUPPORT)
  /* @Trace: EcuM_SUD_API_898 */
  /* Set Mcu mode */
  Mcu_SetMode(EcuM_SleepModes[sleepModeIndex].McuSleepModeType);
  #else
  /* Disable all interrupts */
  DisableAllInterrupts();

  /* Set MCU mode */
  Mcu_SetMode(EcuM_SleepModes[sleepModeIndex].McuSleepModeType);
  /* Enable all interrupts */
  EnableAllInterrupts();
  #endif /* End of if (ECUM_MULTI_CORE_SUPPORT == STD_OFF) */

  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  /* @Trace: EcuM_SUD_API_897 */
  (void)GetSpinlock(ECUM_OS_SPINLOCK);
  /* Set a shutdown flag to be read by slave core */
  EcuM_PollMask =  ECUM_SLAVE_CORE_MASK;
  (void)ReleaseSpinlock(ECUM_OS_SPINLOCK);
  /* Wait for all slaves to complete their sleep sequence */
  /*LOOP FOR ALL SLAVE CORES*/
  EcuM_OsWaitEvent();
  /* Redmine #17451 */
  /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "This point is multi task, global variables EcuM_PollMask would been updated by other task." */
  /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "This point is multi task, global variables EcuM_PollMask would been updated by other task." */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "Wake Up event shall be updated after api Mcu_setMode is called so polyspace can't detect is point" */
  /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "Related to cores synchronization mechanism, firstly EcuM_HaltMask is set to ECUM_SLAVE_CORE_MASK, and after that EcuM_HaltMask mask would been clear by slave cores in the waiting time EcuM_OsWaitEvent()" */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "This point is multi task, global variables EcuM_PollMask would been updated by other task." */
  if (EcuM_PollMask != (uint8)ECUM_ZERO)
  {
    /* @Trace: EcuM_SUD_API_896 */
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GODOWNHALTPOLL_SID, ECUM_E_SHUTDOWN_FAILED);
    stdRetVal = (Std_ReturnType)E_NOT_OK;
    #endif
  }
  else
  #endif
  {
    /* Master Poll Sequence */
    EcuM_PollSeq();
  }
  /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "Related to cores synchronization mechanism, firstly EcuM_HaltMask is set to ECUM_SLAVE_CORE_MASK, and after that EcuM_HaltMask mask would been clear by slave cores in the waiting time EcuM_OsWaitEvent()" */
  /* polyspace-end RTE:UNR [Not a defect:Low] "Wake Up event shall be updated after api Mcu_setMode is called so polyspace can't detect is point" */
  /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "This point is multi task, global variables EcuM_PollMask would been updated by other task." */
  /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "This point is multi task, global variables EcuM_PollMask would been updated by other task." */
  /* polyspace-end RTE:UNR [Not a defect:Low] "This point is multi task, global variables EcuM_PollMask would been updated by other task." */
  /* Release Resource Redmine #5257 */
  EcuM_ReleaseOSResource();
  return stdRetVal;
} /* End of function body */

/*******************************************************************************
** Function Name        : EcuM_GoDownSequence                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : EcuM_GoDownSequence                                 **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_LastShutdown, EcuM_ShutdownCauseTarget         **
**                        EcuM_ShutdownMask,                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION,         **
**                        SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION,          **
**                        EcuM_OnGoOffOne, GetSpinlock, ReleaseSpinlock,      **
**                        EcuM_ClearAlarm, BswM_Deinit, SchM_Deinit,          **
**                        EcuM_OsWaitEvent, ShutdownAllCores,                 **
**                        EcuM_DetReportError, ShutdownOS                     **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09127 SRS_ModeMgm_09114 SRS_ModeMgm_09104*/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoDownSequence(void)
{
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  /* Initialize stdRetVal with E_OK */
  stdRetVal = (Std_ReturnType)E_OK;
  /* Enable data protection */
  SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION();

  /* Update Next recent shutdown Target state */
  EcuM_LastShutdown.NextRecentTarget =
  EcuM_LastShutdown.MostRecentTarget;

  /* Update Last/Most Recent shutdown Target state */
  EcuM_LastShutdown.MostRecentTarget =
  EcuM_ShutdownCauseTarget.SelectShutdownTarget;
  EcuM_LastShutdown.NextRecentShutDownCause =
  EcuM_LastShutdown.MostRecentShutDownCause;
  EcuM_LastShutdown.MostRecentShutDownCause =
  EcuM_ShutdownCauseTarget.ShutdownCause;
  /* Update Next recent reset mode id */
  EcuM_LastShutdown.NextRecentRstModeId =
  EcuM_LastShutdown.MostRecentRstModeId;
  /* Update Last/Most Recent reset mode id */
  EcuM_LastShutdown.MostRecentRstModeId =
  EcuM_ShutdownCauseTarget.ResetMode;
  /* Disable data protection */
  SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION();
  /* call to allow the system designer to notify that the GO OFF I state
  * is about to be entered. */
  EcuM_OnGoOffOne();

  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  /* @Trace: EcuM_SUD_API_901 */
  (void)GetSpinlock(ECUM_OS_SPINLOCK);
  /* Set a shutdown flag to be read by slave core */
  EcuM_ShutdownMask =  ECUM_SLAVE_CORE_MASK;
  (void)ReleaseSpinlock(ECUM_OS_SPINLOCK);
  #endif
  #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
  EcuM_ClearAlarm();
  #endif
  /* @Trace: EcuM_SUD_API_108 */
  /* Deinitializes the BSW Mode Manager */
  BswM_Deinit();

  /* Deinitializes the schedule Manager */
  SchM_Deinit();


  if (EcuM_ShutdownCauseTarget.SelectShutdownTarget == ECUM_SHUTDOWN_TARGET_OFF)
  {
    /* Check for any Pending Wakeup Events, if present update the
    *   shutdownTarget as ECUM_SHUTDOWN_TARGET_RESET */
    if ((EcuM_PendingWakeupEvents != ECUM_NO_EVENTS) &&
       (EcuM_ptrEcuMConfigPtr != NULL_PTR))
    {
      /* @Trace: EcuM_SUD_API_900 */
      /* polyspace +2 RTE:NIV [Not a defect:Low] "Value of EcuM_ptrEcuMConfigPtr is generated by generation tool" */
      (void)EcuM_SelectShutdownTarget(ECUM_SHUTDOWN_TARGET_RESET,
      EcuM_ptrEcuMConfigPtr->EcuMDefaultResetMode);
    }
  }
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  /* @Trace: EcuM_SUD_API_899 */
  /*Wait for all slaves to complete their shutdown */
  EcuM_OsWaitEvent();
  /* Redmine #17451 */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "EcuM_HaltMask shall be updated in other event, it's dependence on api EcuM_OsWaitEvent" */
  /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "variable EcuM_ShutdownMask shall be update by other Event after EcuM_OsWaitEvent execute." */
  /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "variable EcuM_ShutdownMask shall be update by other Event after EcuM_OsWaitEvent execute." */
  /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "Related to cores synchronization mechanism, firstly EcuM_HaltMask is set to ECUM_SLAVE_CORE_MASK, and after that EcuM_HaltMask mask would been clear by slave cores in the waiting time EcuM_OsWaitEvent()" */
  /* Call Shutdown for all cores if slave core has signalled sleep */
  if (EcuM_ShutdownMask == (uint8)ECUM_ZERO)
  {
    ShutdownAllCores((StatusType)E_OK);
  }
  else
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GODOWNHALTPOLL_SID, ECUM_E_SHUTDOWN_FAILED);
    stdRetVal = (Std_ReturnType)E_NOT_OK;
    #endif
  }
  /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "Related to cores synchronization mechanism, firstly EcuM_HaltMask is set to ECUM_SLAVE_CORE_MASK, and after that EcuM_HaltMask mask would been clear by slave cores in the waiting time EcuM_OsWaitEvent()" */
  /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "variable EcuM_ShutdownMask shall be update by other Event." */
  /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "variable EcuM_ShutdownMask shall be update by other Event." */
  /* polyspace-end RTE:UNR [Not a defect:Low] "EcuM_HaltMask shall be updated in other event, it's dependence on api EcuM_OsWaitEvent" */
  #else
  ShutdownOS((StatusType)E_OK);
  #endif
  return stdRetVal;

}/* End of function body */

FUNC(void, ECUM_CODE) EcuM_ProcessModeHandingChangedRequest(void)
{
    /* Process if mode request arbitration is changed */
    if((uint32)ECUM_TRUE == (uint32)EcuM_ModeHandlingChangeStatus)
    {
       EcuM_ModeHandlingChangeStatus = ECUM_FALSE;
       /* Mode Arbitration */
       if((uint32)ECUM_RUNSTATUS_REQUESTED == (uint32)EcuM_RunRequestStatus)
       {
         /* @Trace: EcuM_SUD_API_937 */
         /* Inform RUN requested to BswM */
         BswM_EcuM_RequestedState(ECUM_STATE_APP_RUN, ECUM_RUNSTATUS_REQUESTED);
       }
       else if((uint32)ECUM_RUNSTATUS_RELEASED == (uint32)EcuM_RunRequestStatus)
       {
         if((uint32)ECUM_RUNSTATUS_REQUESTED == (uint32)EcuM_PostRunRequestStatus)
         {
           /* @Trace: EcuM_SUD_API_936 */
           /* Inform POST_RUN requested and RUN released to BswM*/
           BswM_EcuM_RequestedState(ECUM_STATE_APP_POST_RUN, ECUM_RUNSTATUS_REQUESTED);
           BswM_EcuM_RequestedState(ECUM_STATE_APP_RUN, ECUM_RUNSTATUS_RELEASED);
         }
         else
         {
           /* @Trace: EcuM_SUD_API_935 */
           /* Inform to BswM about RUN and POST_RUN release */
           BswM_EcuM_RequestedState(ECUM_STATE_APP_POST_RUN, ECUM_RUNSTATUS_RELEASED);
           BswM_EcuM_RequestedState(ECUM_STATE_APP_RUN, ECUM_RUNSTATUS_RELEASED);
         }
       }
       else
       {
         /* Do nothing */
       }
    }
    else
    {

    }

    /* Check if any request state from user */
    if((uint8)ECUM_REQUEST_INVALID != EcuM_ShutdownOrSleepRequested)
    {
      /* @Trace: EcuM_SUD_API_934 */
      /* Request BswM mode RESET */
      BswM_RequestMode((BswM_UserType)ECUM_STATEREQ_ID, EcuM_ShutdownOrSleepRequested);

      /* Clear the shutdown/sleep request state */
      SchM_Enter_EcuM_STATE_PROTECTION();
      EcuM_ShutdownOrSleepRequested = ECUM_REQUEST_INVALID;
      SchM_Exit_EcuM_STATE_PROTECTION();
    }
}

#define ECUM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<RTE:UNR : Not a defect : Justify with annotations > Not a defect */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

