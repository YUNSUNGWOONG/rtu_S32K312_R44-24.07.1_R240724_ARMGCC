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
**  SRC-MODULE: Os_Arch_TimingProtection.c                                    **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Timing Protection functionality                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: Yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.1.0      1-Sep-2023    HJ.Kim       Jira    CP44-2528                    **
** 1.0.2     31-Dec-2022    TinHV        Jira    CP44-856                     **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:NIP:Not a defect:Justify with annotations> Initialized at other location */
/* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> Variable initialized at other location */
/* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:begin<RTE:OBAI:Not a defect:Justify with annotations> Configured array index */
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> Run-time failures are justified */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Pointer not access out of array */

/* @Trace: SRS_Os_11008 */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os Ram header file */
#include "Os_TimingProtection.h"  /* Os TimerProtection header file */
#include "Os_Kernel.h"            /* Os Kernel header file */
/* @Trace: SRS_BSW_00410 */
#if (OS_RESOURCE == STD_ON)
#include "Os_Resource.h"          /* Os Resource header file */
#endif
#if (OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Application.h"       /* Os Application header file */
#endif
#include "Os_Arch_Multicore.h"    /* Os Multi-core header file */
#include "Os_Arch_Timer.h"        /* Os Timer header file */
#include "Os_Gen.h"
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#if (OS_TIMING_PROTECTION == STD_ON)
#if ((OS_ISR_TP_TF == STD_ON) || (OS_TASK_TP_TF == STD_ON))
static FUNC(void, OS_CODE) Os_GetTimeElapsed(uint8 ChannelId);
#endif

/***************************************************************************//**
 * Function Name        : Os_GetTimeElapsed
 *
 * Service ID           : NA
 *
 * Description          : This service is used to measure the time elapsed
 *                        of watchdog
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            ChannelId
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GpSchedWatchdog
 *
 *                        Function(s) invoked    :
 *                        Os_GetTimeElapsedService()
 *
 * {Ref: SWR_OS_S32K31X_013}
 *
 * @ingroup               OS_S32K31X_ESDD_007 
 ******************************************************************************/
#if ((OS_ISR_TP_TF == STD_ON) || (OS_TASK_TP_TF == STD_ON))
static FUNC(void, OS_CODE) Os_GetTimeElapsed(uint8 ChannelId)
{
  TickType LddTimeElapsed;
  boolean LblRetVal;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace:  SafeOs_SUD_API_33101 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* Invoke Os_GetTimeElapsedService, also check no interrupt is raised during
   *   Os_GetTimeElapsedService */
  LblRetVal = Os_GetTimeElapsedService(ChannelId, &LddTimeElapsed);

  if (LblRetVal == OS_FALSE)
  {
    /* @Trace:  SafeOs_SUD_API_33102 */
    /* Reset the flag */
    Os_GpSchedWatchdog[OS_CORE_ID]->pStaticTask->pTask->blActivateAllowed =
      OS_CAN_BE_ACTIVATED;
    Os_GpSchedWatchdog[OS_CORE_ID] =
                             Os_GpSchedWatchdog[OS_CORE_ID]->pNextSchedWatchdog;
  } /* End of if (LblRetVal == OS_FALSE) */
  else
  {
    /* @Trace:  SafeOs_SUD_API_33103 */
    /* Updated the Time elapsed in the currently running watchdog */
    Os_GpSchedWatchdog[OS_CORE_ID]->ddSchedTick -= LddTimeElapsed;
  }
} /* End of Os_GetTimeElapsed(uint8 ChannelId) */
#endif /* End of if ((OS_ISR_TP_TF == STD_ON) || (OS_TASK_TP_TF == STD_ON)) */

/***************************************************************************//**
 * Function Name        : Os_StartTimeFrame
 *
 * Service ID           : NA
 *
 * Description          : This service is used to start the monitoring of
 *                        the interarrival time between successive
 *                        activation or termination of the tasks
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LpStaticTask
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GpSchedWatchdog, Os_GaaSchedWatchdog
 *
 *                        Function(s) invoked    :
 *                        Os_StartTimer(), Os_GetTimeElapsed()
 *                        Os_ProtectionHookService()
 *
 * {Ref: SWR_OS_S32K31X_013}
 *
 * @ingroup               OS_S32K31X_ESDD_007 
 ******************************************************************************/
#if ((OS_ISR_TP_TF == STD_ON) || (OS_TASK_TP_TF == STD_ON))
FUNC(void, OS_CODE) Os_StartTimeFrame(P2CONST(Tdd_Os_StaticTask,
                                             AUTOMATIC, OS_CONST) LpStaticTask)
{
  P2VAR(Tdd_Os_ScheduleWatchdog, AUTOMATIC, OS_VAR) LpSchedWatchdog;
  P2VAR(Tdd_Os_ScheduleWatchdog, AUTOMATIC, OS_VAR) LpCurrentWatchdog;
  P2VAR(Tdd_Os_ScheduleWatchdog, AUTOMATIC, OS_VAR) LpPrevSchedWatchdog;
  TickType LddTickValue;
  TickType LddPrevTickValue;
  boolean LblBreakFlag;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace:  SafeOs_SUD_API_33001 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LblBreakFlag = OS_TRUE;

  /* Check for TP, if configured for the corresponding task, and the time frame
   *   configured is not equal to zero */
  if ((LpStaticTask->pStaticTimProtection != NULL_PTR) &&
      (LpStaticTask->pStaticTimProtection->ddTimeFrame != OS_ZERO))
  {
    if (LpStaticTask->pTask->blActivateAllowed == OS_CAN_BE_ACTIVATED)
    {
      /* @Trace:  SafeOs_SUD_API_33002 */
      /* Change the Flag to already activated state */
      LpStaticTask->pTask->blActivateAllowed = OS_ALREADY_ACTIVATED;

      /* Update the Watchdog for the current task in local pointer */
      LpSchedWatchdog = &Os_GaaSchedWatchdog[
        LpStaticTask->pStaticTimProtection->ucTimeFrameWdgId];

      /* Load the time frame in the watchdog */
      LpSchedWatchdog->ddSchedTick =
        LpStaticTask->pStaticTimProtection->ddTimeFrame;
      LpCurrentWatchdog = Os_GpSchedWatchdog[OS_CORE_ID];

      /* Check if there exists a Link List for Time Frame */
      if (LpCurrentWatchdog != NULL_PTR)
      {
        /* @Trace:  SafeOs_SUD_API_33003 */
        /* Get the time elapsed */
        Os_GetTimeElapsed(OS_TIMEFRAME_WATCHDOG);

        if (LpCurrentWatchdog->ddSchedTick > LpSchedWatchdog->ddSchedTick)
        {
          /* @Trace:  SafeOs_SUD_API_33004 */
          /* Update the Schedule tick of the head node */
          LpCurrentWatchdog->ddSchedTick -= LpSchedWatchdog->ddSchedTick;

          /* Insert the current watchdog at the Head of the Link List */
          LpSchedWatchdog->pNextSchedWatchdog = LpCurrentWatchdog;
          Os_GpSchedWatchdog[OS_CORE_ID] = LpSchedWatchdog;
        } /* End of if (LpCurrentWatchdog->ddSchedTick >
           *LpSchedWatchdog->ddSchedTick) */
        else
        {
          /* @Trace:  SafeOs_SUD_API_33005 */
          /* Loop through the Time Frame link list in order to insert the
           *   current Watchdog */
          LddTickValue = LpCurrentWatchdog->ddSchedTick;
          LddPrevTickValue = LddTickValue;
          LpPrevSchedWatchdog = LpCurrentWatchdog;
          LpCurrentWatchdog = LpCurrentWatchdog->pNextSchedWatchdog;
          while ((LpCurrentWatchdog != NULL_PTR) && (LblBreakFlag == OS_TRUE))
          {
            /* @Trace:  SafeOs_SUD_API_33006 */
            LddPrevTickValue = LddTickValue;
            LddTickValue += LpCurrentWatchdog->ddSchedTick;

            if (((LpSchedWatchdog->ddSchedTick) < (LddTickValue)))
            {
              /* @Trace:  SafeOs_SUD_API_33007 */
              LblBreakFlag = OS_FALSE;
            }
            else
            {
              /* @Trace:  SafeOs_SUD_API_33008 */
              LpPrevSchedWatchdog = LpCurrentWatchdog;
              LpCurrentWatchdog = LpCurrentWatchdog->pNextSchedWatchdog;
            }
          }
          /* @Trace:  SafeOs_SUD_API_33009 */
          /* Insert the the current watch dog in the link list */
          LpSchedWatchdog->pNextSchedWatchdog = LpCurrentWatchdog;
          LpPrevSchedWatchdog->pNextSchedWatchdog = LpSchedWatchdog;
          LpSchedWatchdog->ddSchedTick -= LddPrevTickValue;

          if (LpCurrentWatchdog != NULL_PTR)
          {
            /* @Trace:  SafeOs_SUD_API_33010 */
            LpCurrentWatchdog->ddSchedTick -= LpSchedWatchdog->ddSchedTick;
          }
        } /* End of else */
      } /* End of if (LpCurrentWatchdog != NULL_PTR) */
      else
      {
        /* @Trace:  SafeOs_SUD_API_33011 */
        /* Make the current WatchDog as the head node of the link list */
        Os_GpSchedWatchdog[OS_CORE_ID] = LpSchedWatchdog;
        LpSchedWatchdog->pNextSchedWatchdog = NULL_PTR;
      }
      /* @Trace:  SafeOs_SUD_API_33012 */
      /* Start the WatchDog */
      Os_StartTimer(OS_TIMEFRAME_WATCHDOG,
                                   Os_GpSchedWatchdog[OS_CORE_ID]->ddSchedTick);
    }
    else
    {
      /* @Trace:  SafeOs_SUD_API_33013 */
      /* Call the ProtectionHook if the time frame is still running */
      (void)Os_ProtectionHookService(E_OS_PROTECTION_ARRIVAL);
    }
  } /* End of if ((LpStaticTask->pStaticTimProtection != NULL_PTR) && */
} /* End of Os_StartTimeFrame(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
   *OS_CONST) LpStaticTask) */
#endif /* End of if ((OS_ISR_TP_TF == STD_ON) || (OS_TASK_TP_TF == STD_ON)) */

/***************************************************************************//**
 * Function Name        : Os_StartMonitor
 *
 * Service ID           : NA
 *
 * Description          : This function is used to start the timing
 *                        protection in case of budget monitoring.
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LddRequestedTime, LddWdgType, LulReqArrayIndx
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaTimingProtValue, Os_GaaRunningWdg
 *
 *                        Function(s) invoked    :
 *                        Os_GetTimeElapsedService(), Os_StartTimer()
 *
 * {Ref: SWR_OS_S32K31X_013}
 *
 * @ingroup               OS_S32K31X_ESDD_007 
 ******************************************************************************/
FUNC(void, OS_CODE) Os_StartMonitor(TickType LddRequestedTime, Os_WatchdogType
                                             LddWdgType, uint32 LulReqArrayIndx)
{
  TickType LddRemainingTime;
  TickType LddTimeElapsed;
  uint32 LulCurrIndex;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  boolean LblStartTimer;
  boolean LblRetVal;
  /* @Trace:  SafeOs_SUD_API_32501 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LblStartTimer = OS_TRUE;

  /* Check if there is a timing protection (TP) already running for the current
   *   Task */
  if (Os_GaaRunningWdg[OS_CORE_ID].ddWdgType != OS_WDG_DISABLED)
  {
    /* @Trace:  SafeOs_SUD_API_32502 */
    /* Invoke Os_GetTimeElapsedService, also check no interrupt is raised during
     *   Os_GetTimeElapsedService */
    LblRetVal = Os_GetTimeElapsedService(OS_BUDGET_WATCHDOG, &LddTimeElapsed);

    if (LblRetVal == OS_TRUE)
    {
      /* @Trace:  SafeOs_SUD_API_32503 */
      /* Get the index for currently running TP and calculate the remaining
       *   time */
      LulCurrIndex = Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx;
      if(LulCurrIndex < OS_MAX_TP_INDEX)
      {
        LddRemainingTime = Os_GaaTimingProtValue[LulCurrIndex] - LddTimeElapsed;
      }
      /* polyspace +2 MISRA-C3:9.1 CERT-C:EXP33-C RTE:NIVL [Justified:Low] "Variable value will be initialized based on currentIdex and will not exceed OS_MAX_TP_Index" */
      /* If the requested timing protection is invalid return FALSE */
      if (LddRequestedTime < LddRemainingTime)
      {
        /* @Trace:  SafeOs_SUD_API_32504 */
        LblStartTimer = OS_TRUE;
        /* Store the remaining time for currently running TP at its location
         *   in global array */
        Os_GaaTimingProtValue[LulCurrIndex] =
          LddRemainingTime - LddRequestedTime;
      } /* End of if (LddRequestedTime < LddRemainingTime) */
      else
      {
        /* @Trace:  SafeOs_SUD_API_32505 */
        /* Do not Start the Timer */
        LblStartTimer = OS_FALSE;
      }
    } /* End of if (LblRetVal == OS_TRUE) */
  } /* End of if (Os_GaaRunningWdg[OS_CORE_ID].ddWdgType != OS_WDG_DISABLED) */

  /* Start new TP only if it is valid */
  if (LblStartTimer == OS_TRUE)
  {
    /* @Trace:  SafeOs_SUD_API_32506 */
    /* Update the type for new TP */
    Os_GaaRunningWdg[OS_CORE_ID].ddWdgType = LddWdgType;
    /* Update the array index for new TP */
    Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx = LulReqArrayIndx;
    /* Update the Timer value at the global array location */
    Os_GaaTimingProtValue[LulReqArrayIndx] = LddRequestedTime;
    /* Start the Timer */
    Os_StartTimer(OS_BUDGET_WATCHDOG, LddRequestedTime);
  } /* End of if (LblStartTimer == OS_TRUE) */
} /* End of Os_StartMonitor(TickType LddRequestedTime, Os_WatchdogType
   *LddWdgType, uint32 LulReqArrayIndx) */

/***************************************************************************//**
 * Function Name        : Os_UpdateTpStructure
 *
 * Service ID           : NA
 *
 * Description          : This function is used to update the remaining
 *                        ticks in case of stopping of a running timing
 *                        protection
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LpStaticTask
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaRunningWdg, Os_GaaTimingProtValue
 *
 *                        Function(s) invoked    : Os_StopTimer()
 *                          Os_StartTimer(), Os_GetTimeElapsedService()
 *
 * {Ref: SWR_OS_S32K31X_013}
 *
 * @ingroup               OS_S32K31X_ESDD_007 
 ******************************************************************************/
/* polyspace-begin MISRA-C3:2.7 [Not a defect:Low] "The parameter is check/will used depending on user's configuration" */
/* polyspace-begin MISRA-C3:9.1 CERT-C:EXP33-C RTE:NIVL [Justified:Low] "Variable value will be initialized based on global variable value" */
#if ((OS_RES_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON) ||\
                                               (OS_ALLINTLOCK_TP_EB == STD_ON))
FUNC(void, OS_CODE) Os_UpdateTpStructure(P2CONST(Tdd_Os_StaticTask,
                                              AUTOMATIC, OS_CONST) LpStaticTask)
{
  #if (OS_RES_TP_EB == STD_ON)
  P2VAR(Tdd_Os_Resource, AUTOMATIC, OS_VAR) LpResource;
  #endif
  TickType LddTimeElapsed;
  #if ((OS_RES_TP_EB == STD_ON)||(OS_TASK_TP_EB == STD_ON) || \
                                                      (OS_ISR_TP_EB == STD_ON))
  TickType LddCurrAlarmTime;
  uint8 LulPrevIndex;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  boolean LblRetVal;
  /* @Trace:  SafeOs_SUD_API_32601 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  if(Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx < OS_MAX_TP_INDEX)
  {
    #if ((OS_RES_TP_EB == STD_ON)||(OS_TASK_TP_EB == STD_ON) || (OS_ISR_TP_EB == STD_ON))                                             
    /* @Trace:  SafeOs_SUD_API_32602 */
    /* Take the currently running TP time in local */
    LddCurrAlarmTime =
      Os_GaaTimingProtValue[Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx];
    #endif
    /* @Trace:  SafeOs_SUD_API_32603 */
    /* Clear running TP time */
    Os_GaaTimingProtValue[Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx] = OS_ZERO;
  }

  /* Invoke Os_GetTimeElapsedService, also check no interrupt is raised during
   *   Os_GetTimeElapsedService */
  LblRetVal = Os_GetTimeElapsedService(OS_BUDGET_WATCHDOG, &LddTimeElapsed);

  if (LblRetVal == OS_TRUE)
  {
    /* If dying TP is All Interrupt lock taken over Interrupt lock */
    if (Os_GaaTimingProtValue[OS_INT_LOCK_INDEX] != OS_ZERO)
    {
      /* @Trace:  SafeOs_SUD_API_32604 */
      /* Update the watchdog type as OS_INT_LOCK */
      Os_GaaRunningWdg[OS_CORE_ID].ddWdgType = OS_INT_LOCK;
      /* Update the running wdg index as zero */
      Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx = OS_ZERO;
      /* Start the timer */
      Os_StartTimer(OS_BUDGET_WATCHDOG, Os_GaaTimingProtValue[OS_ZERO]);
    } /* End of if (Os_GaaTimingProtValue[OS_INT_LOCK_INDEX] != OS_ZERO) */
    else
    {
      #if (OS_RES_TP_EB == STD_ON)

      /* If dying TP is Resource Lock */
      if (Os_GaaRunningWdg[OS_CORE_ID].ddWdgType == OS_REZ_LOCK)
      {
        /* @Trace:  SafeOs_SUD_API_32605 */
        /* Start the search with the next resource to head resource */
        LpResource = LpStaticTask->pTask->pResources->pNextResource;
      }
      else /* Dying TP is Interrupt/AllInterrupt lock Budget */
      {
        /* @Trace:  SafeOs_SUD_API_32606 */
        /* Start the search with the head resource */
        LpResource = LpStaticTask->pTask->pResources;
      }
      /* Find the first resource with timing protection configured */
      while (LpResource != NULL_PTR)
      {
        /* Check if TP is configured for the resource */
        if (LpResource->ddResLockTimeIndex != OS_INVALID_VALUE)
        {
          /* @Trace:  SafeOs_SUD_API_32607 */
          break;
        }
        else
        {
          /* @Trace:  SafeOs_SUD_API_32608 */
          /* Go to the next resource */
          LpResource = LpResource->pNextResource;
        }
      }

      /* If there exist an acquired resource with TP configured */
      if (LpResource != NULL_PTR)
      {
        /* @Trace:  SafeOs_SUD_API_32609 */
        /* Find the index for that resource */
        LulPrevIndex = LpResource->ddResLockTimeIndex;
        /* Update the remaining time in Global array for that resource */
        Os_GaaTimingProtValue[LulPrevIndex] +=
          (LddCurrAlarmTime - LddTimeElapsed);
        /* Update the type for new TP as Resource monitoring */
        Os_GaaRunningWdg[OS_CORE_ID].ddWdgType = OS_REZ_LOCK;
        /* Update the index same as that of first resource with TP configured */
        Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx = LulPrevIndex;
        /* Start the Timer */
        Os_StartTimer(OS_BUDGET_WATCHDOG, Os_GaaTimingProtValue[LulPrevIndex]);
      } /* End of if (LpResource != NULL_PTR) */
      else
      #endif /* End of if (OS_RES_TP_EB == STD_ON) */
      {
        #if ((OS_TASK_TP_EB == STD_ON) || (OS_ISR_TP_EB == STD_ON))

        /* Check for execution budget */
        if (LpStaticTask->pStaticTimProtection->ddExecutionBudget != OS_ZERO)
        {
          /* @Trace:  SafeOs_SUD_API_32610 */
          /* Find the index for execution budget */
          LulPrevIndex =
            LpStaticTask->pStaticTimProtection->ucTaskExeBudgetIndex;
          /* Update the remaining time in Global array for execution budget */
          Os_GaaTimingProtValue[LulPrevIndex] +=
            (LddCurrAlarmTime - LddTimeElapsed);
          /* Update the type for new TP as execution budget monitoring */
          Os_GaaRunningWdg[OS_CORE_ID].ddWdgType = OS_EXEC_BUDGET;
          /* Update the index as that of execution budget for current Task */
          Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx = LulPrevIndex;
          /* Start the Timer */
          Os_StartTimer(OS_BUDGET_WATCHDOG,
            Os_GaaTimingProtValue[LulPrevIndex]);
        } /* End of if (LpStaticTask->pStaticTimProtection->ddExecutionBudget !=
           *OS_ZERO) */
        else /* There are no pending TP for current Task */
        #endif /* End of if ((OS_TASK_TP_EB == STD_ON) || (OS_ISR_TP_EB ==
                *STD_ON)) */
        {
          /* @Trace:  SafeOs_SUD_API_32611 */
          /* Stop the Timer */
          Os_StopTimer(OS_BUDGET_WATCHDOG);
          /* Update the status as disabled */
          Os_GaaRunningWdg[OS_CORE_ID].ddWdgType = OS_WDG_DISABLED;
          Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx = OS_INVALID_VALUE;
        }
      }
    }
  }
}
#endif /* End of if ((OS_RES_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON) ||
        *(OS_ALLINTLOCK_TP_EB == STD_ON)) */
/* polyspace-end MISRA-C3:2.7 [Not a defect:Low] "The parameter is check/will used depending on user's configuration" */
/* polyspace-end MISRA-C3:9.1 CERT-C:EXP33-C RTE:NIVL [Justified:Low] "Variable value will be initialized based on global variable value" */
/***************************************************************************//**
 * Function Name        : Os_PauseTimingProtection
 *
 * Service ID           : NA
 *
 * Description          : This function is used to pause the timing
 *                        protection for currently running task or isr.
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaRunningWdg, Os_GaaTimingProtValue
 *                        Os_GddFaultyTask, Os_GpLinkTask
 *
 *                        Function(s) invoked    :  Os_GetTimeElapsedService()
 *                        Os_StopTimer()
 *
 * {Ref: SWR_OS_S32K31X_013}
 *
 * @ingroup               OS_S32K31X_ESDD_007 
 ******************************************************************************/
FUNC(void, OS_CODE) Os_PauseTimingProtection(void)
{
  uint32 LulIndex;
  TickType LddTimeElapsed;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  boolean LblRetVal;
  /* @Trace:  SafeOs_SUD_API_32701 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  if (Os_GaaRunningWdg[OS_CORE_ID].ddWdgType != OS_WDG_DISABLED)
  {
    /* @Trace:  SafeOs_SUD_API_32702 */
    /* Invoke Os_GetTimeElapsedService, also check no interrupt is raised during
     *   Os_GetTimeElapsedService */
    LblRetVal = Os_GetTimeElapsedService(OS_BUDGET_WATCHDOG, &LddTimeElapsed);

    if (LblRetVal == OS_TRUE)
    {
      /* @Trace:  SafeOs_SUD_API_32703 */
      /* Stop the Timer */
      Os_StopTimer(OS_BUDGET_WATCHDOG);
      /* Take the index of currently running TP in a local */
      LulIndex = Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx;
      /* Update the remaining time in global array */
      if(LulIndex < OS_MAX_TP_INDEX)
      {
        Os_GaaTimingProtValue[LulIndex] -= LddTimeElapsed;
      }
      /* Update the status as disabled */
      Os_GaaRunningWdg[OS_CORE_ID].ddWdgType = OS_WDG_DISABLED;
      Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx = OS_INVALID_VALUE;
    } /* End of if (LblRetVal == OS_TRUE) */
    else
    {
      /* @Trace:  SafeOs_SUD_API_32704 */
      Os_GddFaultyTask[OS_CORE_ID] = Os_GpLinkTask[OS_CORE_ID]->ddTaskID;
    }
  } /* End of if (Os_GaaRunningWdg[OS_CORE_ID].ddWdgType != OS_WDG_DISABLED) */
} /* End of Os_PauseTimingProtection() */

/***************************************************************************//**
 * Function Name        : Os_ContinueTimingProtection
 *
 * Service ID           : NA
 *
 * Description          : This function is used to continue the timing
 *                        protection for currently running task or isr
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LpStaticTask
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaRunningWdg, Os_GaaTimingProtValue
 *
 *                        Function(s) invoked    :  
 *                        Os_StopTimer(), Os_StartTimer()
 *
 * {Ref: SWR_OS_S32K31X_013}
 *
 * @ingroup               OS_S32K31X_ESDD_007 
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ContinueTimingProtection(P2CONST(
                           Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask)
{
  #if (OS_RES_TP_EB == STD_ON)
  P2VAR(Tdd_Os_Resource, AUTOMATIC, OS_VAR) LpResource;
  #endif
  #if ((OS_TASK_TP_EB == STD_ON) || (OS_ISR_TP_EB == STD_ON) || (OS_RES_TP_EB == STD_ON))
  uint32 LulIndex;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  #if ((OS_RES_TP_EB == STD_OFF) && (OS_TASK_TP_EB == STD_OFF) &&\
  (OS_ISR_TP_EB == STD_OFF))
  /* @Trace:  SafeOs_SUD_API_32801 */
  UNUSED(LpStaticTask);
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  #if (OS_RES_TP_EB == STD_ON)
  /* @Trace:  SafeOs_SUD_API_32802 */
  /* Find the first resource with TP configured */
  LpResource = LpStaticTask->pTask->pResources;
  while (LpResource != NULL_PTR)
  {
    /* Check if TP is configured for the resource */
    if (LpResource->ddResLockTimeIndex != OS_INVALID_VALUE)
    {
      /* @Trace:  SafeOs_SUD_API_32803 */
      break;
    }
    else
    {
      /* @Trace:  SafeOs_SUD_API_32804 */
      /* Go to the next resource */
      LpResource = LpResource->pNextResource;
    }
  }

  /* Proceed if there is a resource acquired with timing protection */
  if (LpResource != NULL_PTR)
  {
    /* @Trace:  SafeOs_SUD_API_32805 */
    /* Take the TP index in a local */
    LulIndex = LpResource->ddResLockTimeIndex;
    /* Update the type for new TP as Resource monitoring */
    Os_GaaRunningWdg[OS_CORE_ID].ddWdgType = OS_REZ_LOCK;
    /* Update the index same as that of first resource with TP configured */
    Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx = LulIndex;
    /* Start the Timer */
    Os_StartTimer(OS_BUDGET_WATCHDOG, Os_GaaTimingProtValue[LulIndex]);
  } /* End of if (LpResource != NULL_PTR) */
  else
  #endif /* End of if (OS_RES_TP_EB == STD_ON) */
  {
    #if ((OS_TASK_TP_EB == STD_ON) || (OS_ISR_TP_EB == STD_ON))

    /* Check for execution budget */
    if (LpStaticTask->pStaticTimProtection->ddExecutionBudget != OS_ZERO)
    {
      /* @Trace:  SafeOs_SUD_API_32806 */
      /* Find the index for execution budget */
      LulIndex = LpStaticTask->pStaticTimProtection->ucTaskExeBudgetIndex;
      /* Update the type for new TP as execution budget monitoring */
      Os_GaaRunningWdg[OS_CORE_ID].ddWdgType = OS_EXEC_BUDGET;
      /* Update the index as that of execution budget for current Task */
      Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx = LulIndex;
      /* Start the Timer */
      Os_StartTimer(OS_BUDGET_WATCHDOG, Os_GaaTimingProtValue[LulIndex]);
    } /* End of if (LpStaticTask->pStaticTimProtection->ddExecutionBudget !=
       *OS_ZERO) */
    else
    #endif /* End of if ((OS_TASK_TP_EB == STD_ON) || (OS_ISR_TP_EB == STD_ON))
            **/
    {
      /* @Trace:  SafeOs_SUD_API_32807 */
      /* Stop the Timer */
      Os_StopTimer(OS_BUDGET_WATCHDOG);
      /* Update the status as disabled */
      Os_GaaRunningWdg[OS_CORE_ID].ddWdgType = OS_WDG_DISABLED;
      Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx = OS_INVALID_VALUE;
    }
  }
} /* End of Os_ContinueTimingProtection(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
   *OS_CONST) LpStaticTask) */

/***************************************************************************//**
 * Function Name        : Os_StopExecutionBudget
 *
 * Service ID           : NA
 *
 * Description          : This function is used to stop the execution budget
 *                        for currently running task or isr. And clear lock
 *                        budget too. Because if task or isr terminated, lock
 *                        should be free by AUTOSAR spec.
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LpStaticTask
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaRunningWdg, Os_GaaTimingProtValue
 *
 *                        Function(s) invoked    : Os_StopTimer()
 *
 * {Ref: SWR_OS_S32K31X_013}
 *
 * @ingroup               OS_S32K31X_ESDD_007 
 ******************************************************************************/
#if ((OS_TASK_TP_EB == STD_ON) || (OS_ISR_TP_EB == STD_ON))
FUNC(void, OS_CODE) Os_StopExecutionBudget(P2CONST(Tdd_Os_StaticTask,
                                             AUTOMATIC, OS_CONST) LpStaticTask)
{
  uint32 LulIndex;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  #if (OS_RES_TP_EB == STD_ON)
  P2VAR(Tdd_Os_Resource, AUTOMATIC, OS_VAR) LpResource;
  #endif
  boolean LblTimeNotExpired;
  TickType LddTick;

  if ((LpStaticTask->pStaticTimProtection != NULL_PTR) && 
      (LpStaticTask->pStaticTimProtection->ddExecutionBudget != OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_32901 */
    /* Get The coreID */
    OS_GET_CORE_ID(OS_CORE_ID);
    /* Stop the Timer */
    Os_StopTimer(OS_BUDGET_WATCHDOG);
    LblTimeNotExpired = Os_GetTimeElapsedService(OS_BUDGET_WATCHDOG, &LddTick);
    if (LblTimeNotExpired == OS_FALSE)
    {
      /* @Trace:  SafeOs_SUD_API_32902 */
      Os_GddFaultyTask[OS_CORE_ID] = LpStaticTask->ddTaskId;
    }
    /* @Trace:  SafeOs_SUD_API_32903 */
    /* Update the status as disabled */
    Os_GaaRunningWdg[OS_CORE_ID].ddWdgType = OS_WDG_DISABLED;
    Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx = OS_INVALID_VALUE;
    LulIndex = LpStaticTask->pStaticTimProtection->ucTaskExeBudgetIndex;
    /* Update the remaining time as Zero */
    Os_GaaTimingProtValue[LulIndex] = OS_ZERO;
    #if (OS_RES_TP_EB == STD_ON)
    LpResource = LpStaticTask->pTask->pResources;
    /* Find all resources with timing protection configured */
    while (LpResource != NULL_PTR)
    {
      /* @Trace:  SafeOs_SUD_API_32904 */
      /* Check if TP is configured for the resource */
      if (LpResource->ddResLockTimeIndex != OS_INVALID_VALUE)
      {
        /* @Trace:  SafeOs_SUD_API_32905 */
        /* Update the remaining time as Zero */
        Os_GaaTimingProtValue[LpResource->ddResLockTimeIndex] = OS_ZERO;
      }
      /* @Trace:  SafeOs_SUD_API_32906 */
      /* Go to the next resource */
      LpResource = LpResource->pNextResource;
    }
    #endif
    #if (OS_INTLOCK_TP_EB == STD_ON)
    /* @Trace:  SafeOs_SUD_API_32907 */
    /* Update the remaining time as Zero */
    Os_GaaTimingProtValue[OS_INT_LOCK_INDEX] = OS_ZERO;
    #endif
    #if (OS_ALLINTLOCK_TP_EB == STD_ON)
    /* @Trace:  SafeOs_SUD_API_32908 */
    /* Update the remaining time as Zero */
    Os_GaaTimingProtValue[OS_ALL_INT_LOCK_INDEX] = OS_ZERO;
    #endif
  } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
  /* @Trace:  SafeOs_SUD_API_32909 */
} /* End of Os_StopExecutionBudget(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
   *OS_CONST) LpStaticTask) */
#endif /* End of if ((OS_TASK_TP_EB == STD_ON) || (OS_ISR_TP_EB == STD_ON)) */
#endif /* End of #if (OS_TIMING_PROTECTION == STD_ON) */

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<RTE:NIP:Not a defect:Justify with annotations> Initialized at other location */
/* polyspace:end<RTE:NIV:Not a defect:Justify with annotations> Variable initialized at other location */
/* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:end<RTE:OBAI:Not a defect:Justify with annotations> Configured array index */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> Run-time failures are justified */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Pointer not access out of array */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

