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
**  SRC-MODULE: Os_TimingProtection.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Timing Protection functionality                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 SRS_Os_11012 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.5.3     16-Feb-2024   HG.Kim           Jira CP44-3828                    **
** 1.5.0     13-Sep-2023   HJ.Kim           Jira CP44-2965                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually*/
/* polyspace:begin<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
/* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and  code is verified manually code is manually checked" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Array index inside bounds and code is verified manually code is manually checked" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os Ram header file */
#include "Os_Error.h"             /* Os Error header file */
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_TimingProtection.h" /* Os TimerProtection header file */
#endif
#include "Os_Kernel.h"            /* Os Kernel header file */
/* @Trace: SRS_BSW_00410 */
#if (OS_RESOURCE == STD_ON)
#include "Os_Resource.h"          /* Os Resource header file */
#endif
#if (OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Application.h"
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Os_OsWdgHandler                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This handler is used to schedule the next task when **
**                        a particular task has violated the timing protection**
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaRunningWdg, Os_GpStaticTask,                  **
**                        Os_GaaStaticTask, Os_GpLinkTask                     **
**                                                                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StopTimer(), Os_ProtectionHookService()          **
*******************************************************************************/
#if (OS_TIMING_PROTECTION == STD_ON)
FUNC(void, OS_CODE) Os_OsWdgHandler(void)
{
  Os_WatchdogType LddWdgType;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Stop the timer */
  Os_StopTimer(OS_BUDGET_WATCHDOG);

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace-begin DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace-begin CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace-begin MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  LddWdgType = Os_GaaRunningWdg[OS_CORE_ID].ddWdgType;
  Os_GaaRunningWdg[OS_CORE_ID].ddWdgType = OS_WDG_DISABLED;
  Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx = OS_INVALID_VALUE;
  /* polyspace-end DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace-end CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace-end MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  switch (LddWdgType)
  {
    /* Execution budget measurement */
    /* @Trace : SafeOs_SUD_API_15201 */
    case OS_EXEC_BUDGET:
      (void)Os_ProtectionHookService(E_OS_PROTECTION_TIME);
      break;
      #if (OS_RESOURCE == STD_ON)
    /* Resource lock measurement */
    /* @Trace : SafeOs_SUD_API_15202 */
    case OS_REZ_LOCK:
      (void)Os_ProtectionHookService(E_OS_PROTECTION_LOCKED);
      break;
      #endif

      #if (OS_ISR_COUNT != OS_PRE_ZERO)
    /* Interrupt lock measurement */
    /* @Trace : SafeOs_SUD_API_15203 */
    case OS_ALL_INT_LOCK:
    case OS_INT_LOCK:
      (void)Os_ProtectionHookService(E_OS_PROTECTION_LOCKED);
      break;

      #endif /* End of if (OS_ISR_COUNT != OS_PRE_ZERO) */
    /* Default */
    /* @Trace : SafeOs_SUD_API_15204 */
    default:
      #if(OS_SCALABILITY_CLASS == OS_SC4)
      (void)Os_ProtectionHookService(Os_GucExecFail[OS_CORE_ID]);
      #else
      /* Do Nothing */
      #endif
      break;
  } /* End of switch (LddWdgType) */

  Os_GpStaticTask[OS_CORE_ID] =
    &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];
} /* End of Os_OsWdgHandler(void) */
#endif /* End of if (OS_TIMING_PROTECTION == STD_ON) */
/*******************************************************************************
** Function Name        : Os_TimeFrameHandler                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is the handler for Time Frame Interrupt**
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GpSchedWatchdog                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StartTimer(), Os_StopTimer()                     **
*******************************************************************************/
#if ((OS_ISR_TP_TF == STD_ON) || (OS_TASK_TP_TF == STD_ON))
FUNC(void, OS_CODE) Os_TimeFrameHandler(void)
{
  P2VAR(Tdd_Os_ScheduleWatchdog, AUTOMATIC, OS_VAR) LpSchedWatchdog;
  P2VAR(Tdd_Os_ScheduleWatchdog, AUTOMATIC, OS_VAR) LpNextSchedWatchdog;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  if (Os_GpSchedWatchdog[OS_CORE_ID] != NULL_PTR)
  {
    /* @Trace : SafeOs_SUD_API_15101 */
    LpSchedWatchdog = Os_GpSchedWatchdog[OS_CORE_ID];

    do
    {
      LpSchedWatchdog->pStaticTask->pTask->blActivateAllowed =
                                                            OS_CAN_BE_ACTIVATED;
      LpSchedWatchdog->ddSchedTick = OS_ZERO;
      LpNextSchedWatchdog = LpSchedWatchdog;
      LpSchedWatchdog = LpSchedWatchdog->pNextSchedWatchdog;
      LpNextSchedWatchdog->pNextSchedWatchdog = NULL_PTR;
    } while ((LpSchedWatchdog != NULL_PTR) &&
                                     (LpSchedWatchdog->ddSchedTick == OS_ZERO));

    if (LpSchedWatchdog != NULL_PTR)
    {
      /* @Trace : SafeOs_SUD_API_15102 */
      Os_StartTimer(OS_TIMEFRAME_WATCHDOG, LpSchedWatchdog->ddSchedTick);
    }
    else
    {
      /* @Trace : SafeOs_SUD_API_15103 */
      Os_StopTimer(OS_TIMEFRAME_WATCHDOG);
    }
    Os_GpSchedWatchdog[OS_CORE_ID] = LpSchedWatchdog;
  } /* End of if (Os_GpSchedWatchdog[OS_CORE_ID] != NULL_PTR) */
  else
  {
    /* @Trace : SafeOs_SUD_API_15104 */
    Os_StopTimer(OS_TIMEFRAME_WATCHDOG);
  }
} /* End of Os_TimeFrameHandler(void) */
#endif /* End of if ((OS_ISR_TP_TF == STD_ON) || (OS_TASK_TP_TF == STD_ON)) */

/*******************************************************************************
** Function Name        : Os_StartAllLockMonitor                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is to start monitoring for all         **
**                        interrupt lock budget                               **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GpStaticTask, Os_GusCallevelCheck                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StartMonitor()                                   **
*******************************************************************************/
#if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
FUNC(void, OS_CODE) Os_StartAllLockMonitor(void)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  TickType LddRequestedTime;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace : SafeOs_SUD_API_14701 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace-begin MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
  if (
      #if (OS_CAT1_ISR_COUNT != OS_PRE_ZERO)
      (OS_NOT_IN_CAT1()) &&
      #endif
      /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      ((Os_GusCallevelCheck[OS_CORE_ID] & (OS_CONTEXT_HOOK)) == OS_ZERO)
     )
  {
    /* @Trace : SafeOs_SUD_API_14702 */
    LpStaticTask = Os_GpStaticTask[OS_CORE_ID];
    /* Check if TP is configured for currently running object */
    if ((LpStaticTask != NULL_PTR)
                            && (LpStaticTask->pStaticTimProtection != NULL_PTR))
    {
      /* @Trace : SafeOs_SUD_API_14703 */
      LddRequestedTime =
      LpStaticTask->pStaticTimProtection->ddAllInterruptLockTime;
      /* Check if All Interrupt Lock Budget is configured */
      if (LddRequestedTime != OS_ZERO)
      {
        /* @Trace : SafeOs_SUD_API_14704 */
        /* Start monitoring for All Interrupt Lock Budget */
        Os_StartMonitor(LddRequestedTime, OS_ALL_INT_LOCK,
                                             OS_ALL_INT_LOCK_INDEX);
      }
    }
  }
  /* polyspace-end MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
}
#endif

/*******************************************************************************
** Function Name        : Os_StartOsLockMonitor                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is to start monitoring for OS          **
**                        interrupt lock budget                               **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GpStaticTask, Os_GusCallevelCheck                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StartMonitor()                                   **
*******************************************************************************/
#if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
FUNC(void, OS_CODE) Os_StartOsLockMonitor(void)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  TickType LddRequestedTime;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace : SafeOs_SUD_API_14801 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace-begin MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
  if (
      #if (OS_CAT1_ISR_COUNT != OS_PRE_ZERO)
      (OS_NOT_IN_CAT1()) &&
      #endif
      /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      ((Os_GusCallevelCheck[OS_CORE_ID] & (OS_CONTEXT_HOOK)) == OS_ZERO)
     )
  {
    /* @Trace : SafeOs_SUD_API_14802 */
    LpStaticTask = Os_GpStaticTask[OS_CORE_ID];
    /* Check if TP is configured for currently running object */
    if ((LpStaticTask != NULL_PTR)
                            && (LpStaticTask->pStaticTimProtection != NULL_PTR))
    {
      /* @Trace : SafeOs_SUD_API_14803 */
      LddRequestedTime =
        LpStaticTask->pStaticTimProtection->ddInterruptLockTime;
      /* Check if OS Interrupt Lock Budget is configured */
      if (LddRequestedTime != OS_ZERO)
      {
        /* @Trace : SafeOs_SUD_API_14804 */
        /* Start monitoring for OS Interrupt Lock Budget */
        Os_StartMonitor(LddRequestedTime, OS_INT_LOCK, OS_INT_LOCK_INDEX);
      }
    }
  }
  /* polyspace-end MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
}
#endif

/*******************************************************************************
** Function Name        : Os_StopAllLockMonitor                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is to stop monitoring for all          **
**                        interrupt lock budget                               **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GpStaticTask, Os_GusCallevelCheck                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StopIntMonitor()                                 **
*******************************************************************************/
#if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
FUNC(void, OS_CODE) Os_StopAllLockMonitor(void)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  TickType LddRequestedTime;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace : SafeOs_SUD_API_15001 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace-begin MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
  if (
      #if (OS_CAT1_ISR_COUNT != OS_PRE_ZERO)
      (OS_NOT_IN_CAT1()) &&
      #endif
      /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      ((Os_GusCallevelCheck[OS_CORE_ID] & (OS_CONTEXT_HOOK)) == OS_ZERO)
     )
  {
    /* @Trace : SafeOs_SUD_API_15002 */
    LpStaticTask = Os_GpStaticTask[OS_CORE_ID];
    /* Check if TP is configured for currently running object */
    if ((LpStaticTask != NULL_PTR)
                            && (LpStaticTask->pStaticTimProtection != NULL_PTR))
    {
      /* @Trace : SafeOs_SUD_API_15003 */
      /* Check if TP is configured for currently running object */
      LddRequestedTime =
        LpStaticTask->pStaticTimProtection->ddAllInterruptLockTime;
      /* Check if All interrupt Lock Budget is configured */
      if (LddRequestedTime != OS_ZERO)
      {
        /* @Trace : SafeOs_SUD_API_15004 */
        /*Stop monitoring for All Interrupt Lock Budget*/
        Os_StopIntMonitor(LpStaticTask, OS_ALL_INT_LOCK_INDEX);
      }
    }
  }
  /* polyspace-end MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
}
#endif

/*******************************************************************************
** Function Name        : Os_StopOsLockMonitor                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is to stop monitoring for OS           **
**                        interrupt lock budget                               **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GpStaticTask, Os_GusCallevelCheck                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StopIntMonitor()                                 **
*******************************************************************************/
#if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
FUNC(void, OS_CODE) Os_StopOsLockMonitor(void)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  TickType LddRequestedTime;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace : SafeOs_SUD_API_14901 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace-begin MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
  if (
      #if (OS_CAT1_ISR_COUNT != OS_PRE_ZERO)
      (OS_NOT_IN_CAT1()) &&
      #endif
      /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      ((Os_GusCallevelCheck[OS_CORE_ID] & (OS_CONTEXT_HOOK)) == OS_ZERO)
     )
  {
    /* @Trace : SafeOs_SUD_API_14902 */
    LpStaticTask = Os_GpStaticTask[OS_CORE_ID];
    /* Check if TP is configured for currently running object */
    if ((LpStaticTask != NULL_PTR)
                            && (LpStaticTask->pStaticTimProtection != NULL_PTR))
    {
      /* @Trace : SafeOs_SUD_API_14903 */
      LddRequestedTime =
        LpStaticTask->pStaticTimProtection->ddInterruptLockTime;
      /* Check if OS Interrupt Lock Budget is configured */
      if (LddRequestedTime != OS_ZERO)
      {
        /* @Trace : SafeOs_SUD_API_14904 */
        /* Stop monitoring for OS Interrupt Lock Budget */
        Os_StopIntMonitor(LpStaticTask, OS_INT_LOCK_INDEX);
      }
    }
  }
  /* polyspace-end MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
}
#endif

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually*/
/* polyspace:end<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
/* polyspace-end RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and  code is verified manually code is manually checked" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Array index inside bounds and code is verified manually code is manually checked" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
