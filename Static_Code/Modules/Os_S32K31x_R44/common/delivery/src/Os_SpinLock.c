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
**  SRC-MODULE: Os_Spinlock.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Spinlock functionality.                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.5.3     16-Feb-2024   HG.Kim           Jira CP44-3828                    **
** 1.5.1     06-Oct-2023   JC.Kim           Jira CP44-2438                    **
** 1.5.0     26-Jun-2023   HJ.Kim           Jira CP44-2459                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
**                                          Jira CP44-2005                    **
**                                          Jira CP44-1772                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.8     27-Oct-2020   DanhDC1          R44-Redmine #16649  Check         **
**                                          NULL_PTR the end of linked task   **
** 1.0.7     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
** 1.0.6     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C  17.7, 8.5, 16.1    **
**                                          Add comment for Misra-C D4.5      **
** 1.0.5     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.4     13-Aug-2020   DanhDC1          R44-Redmine #15262                **
** 1.0.3     08-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed defect DEAD CODE from       **
**                                          detected by bug finder polyspace  **
** 1.0.2     28-Jul-2020   DanhDC1          R44-Redmine #11180                **
**                                          Merge the TryToGetSpinLock() and  **
**                                          GetSpinLock() into one            **
** 1.0.1     22-Jun-2020   DanhDC1          R44-Redmine #13809                **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/* polyspace-begin DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
/* polyspace-begin CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os Ram header file */
#include "Os_Kernel.h"            /* Os Kernel header file */
#include "Os_Error.h"             /* Os Error header file */
#include "Os_SpinLock.h"          /* Os Spinlock header file */
/* @Trace: SRS_BSW_00410 */
#if (OS_MULTICORE == STD_ON)
#include "Os_MulticoreMessage.h"
#endif
#include "Os_Application.h"       /* Os Application header file */
#include "Os_SystemCallTable.h"
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_TimingProtection.h"  /* Os TimerProtection header file */
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

#if (OS_RES_SCHEDULER == STD_ON) && (OS_SPINLOCK == STD_ON)
static FUNC(void, OS_CODE) Os_SpinlockLockResource(ResourceType ResID);
static FUNC(void, OS_CODE) Os_SpinlockUnLockResource(ResourceType ResID);
#endif

#if (OS_SPINLOCK == STD_ON)
static FUNC(void, OS_CODE) Os_SpinlockLockMethod(SpinlockIdType SpinlockId);
static FUNC(void, OS_CODE) Os_SpinlockUnLockMethod(SpinlockIdType SpinlockId);
#endif

/*******************************************************************************
** Function Name        : Os_KernReleaseSpinlock                              **
**                                                                            **
** Service ID           : OSServiceId_ReleaseSpinlock                         **
**                                                                            **
** Description          : ReleaseSpinlock releases a spinlock variable that   **
**                       was occupied before. Before terminating a TASK all   **
**                       spinlock variables that have been occupied with      **
**                       GetSpinlock() shall be released.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : SpinlockId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaSpinlock, Os_GpLinkTask, Os_GaaTask           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_ReleaseSpinlock(),                               **
**                        Os_SpinlockUnLockMethod()                           **
*******************************************************************************/
/* @Trace: SRS_Os_80021 */
#if (OS_SPINLOCK == STD_ON)
/* polyspace +1 MISRA-C3:17.2 [Justified:Low] "Os_SpinlockUnLockMethod -> Os_ScheduleService -> Os_CheckStack -> Os_ProtectionHookService -> Os_KillTaskOrISR -> ReleaseSpinlock -> OS_SYSCALL_RELEASESPINLOCK -> Os_SystemCallReleaseSpinlock ->Os_KernReleaseSpinlock" */
FUNC(StatusType, OS_CODE) Os_KernReleaseSpinlock(SpinlockIdType SpinlockId)
{
  P2VAR(Tdd_Os_Spinlock, AUTOMATIC, OS_VAR) LpSpinlock;
  StatusType LenStatusReturn;
  CoreIDType OS_CORE_ID;

  /* @Trace: SafeOs_SUD_API_22801 */
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Get curent Core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Check whether SpinlockId is greater than number of Spinlock count */
  OS_CHECK_SPINLOCK_ID_ERROR(SpinlockId, LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(RELEASESPINLOCK, LenStatusReturn);
  /* Check Access for the spinlock */
  /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "SpinlockId have been checked before using" */
  OS_CHECK_SPINLOCK_APPLICATION_ACCESS(LenStatusReturn,SpinlockId);
  /* Check if Spinlock is not aquired by the task */
  /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
  OS_CHECK_SPINLOCK_STATE_ERROR(SpinlockId, LenStatusReturn);
  /* Check if releasing order is incorrect */
  /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
  OS_CHECK_SPINLOCK_RELEASE_ORDER_ERROR(SpinlockId, LenStatusReturn);
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "SpinlockId have been checked before using" */

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_22802 */
    /* Take Spinlock into local variable */
    LpSpinlock = &Os_GaaSpinlock[SpinlockId];
    /* Update taskID into Spinlock structure */
    LpSpinlock->ddTaskId = OS_INVALID_VALUE;
    /* Update Spinlock id in Task structure with next Spinlock ID */
    /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
    Os_GaaTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID].ddSpinlock = LpSpinlock->ddNextSpinIndex;
    /* Release the Spinlock */
    Os_ReleaseSpinlock(SpinlockId);

    /* After Spinlock was released we need to unlock method for its */
    Os_SpinlockUnLockMethod(SpinlockId);

  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_22803 */
    /* Store service ID of ReleaseSpinlock */
    OS_STORE_SERVICE(OSServiceId_ReleaseSpinlock);
    /*Store the parameter 1 - SpinlockId */
    OS_STORE_PARAM1_SPINLOCKID(SpinlockId);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* Return the status */
  /* @Trace: SafeOs_SUD_API_22804 */
  return (LenStatusReturn);
} /* End of ReleaseSpinlock(SpinlockIdType SpinlockId) */
#endif /* End of if (OS_SPINLOCK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernTryToGetSpinlock                             **
**                                                                            **
** Service ID           : OSServiceId_TryToGetSpinlock                        **
**                                                                            **
** Description          : The Os_KernTryToGetSpinlock indicates if the        **
**                        Spinlock has been occupied or not.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : - SpinlockId                                        **
**                                                                            **
** InOut parameter      : Success                                             **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() API should be invoked                     **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaSpinlock, Os_GpLinkTask, Os_GaaTask           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SpinlockLockMethod(),                            **
**                        Os_TryToGetSpinlock()                               **
**                        Os_SpinlockUnLockMethod()                           **
*******************************************************************************/
/* @Trace: SRS_Os_80018 SRS_Os_80021 */
#if (OS_SPINLOCK == STD_ON)
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
FUNC(StatusType, OS_CODE) Os_KernTryToGetSpinlock(SpinlockIdType SpinlockId,
                         P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success)
{
  P2VAR(Tdd_Os_Spinlock, AUTOMATIC, OS_VAR) LpSpinlock;
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) LpTask;
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  boolean LblStatus;

  /* @Trace: SafeOs_SUD_API_22901 */
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Get curent Core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Check whether SpinlockId is greater than number of Spinlock count */
  OS_CHECK_SPINLOCK_ID_ERROR(SpinlockId, LenStatusReturn);
  /* Check for call level of TryToGetSpinlock */
  OS_CHECK_E_OS_CALLEVEL(TRYTOGETSPINLOCK, LenStatusReturn);
  /* Check Access for the spinlock */
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "SpinlockId have been checked before using" */
  /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
  OS_CHECK_SPINLOCK_APPLICATION_ACCESS(LenStatusReturn, SpinlockId);
  /* Check whether Spinlock is already occupied by same task or task belonging
   *     on same core */
  OS_CHECK_SPINLOCK_STATUS_ERROR(SpinlockId, LenStatusReturn);
  /* polyspace +2 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
  /* Check whether Spinlock can create deadlock */
  OS_CHECK_SPINLOCK_DEADLOCK_ERROR(SpinlockId, LenStatusReturn);
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "SpinlockId have been checked before using" */
  /* Check for NULL_PTR of Success for TryToGetSpinlock */
  OS_CHECK_NULL_PTR(Success, LenStatusReturn);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_22902 */
    /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
    LpTask = &Os_GaaTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];
    /* Lock method The Spinlock */
    Os_SpinlockLockMethod(SpinlockId);
    /* Init status of the Spinlock  */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "*Success have been checked before using" */
    *Success = TRYTOGETSPINLOCK_NOSUCCESS;

    /* Try to get The Spinlock */
    (void)Os_TryToGetSpinlock(SpinlockId, &LblStatus);

    /* Check if Spinlock is aquired */
    if (LblStatus == OS_TRUE)
    {
      /* @Trace: SafeOs_SUD_API_22903 */
      /* Update status of the Spinlock  */
      *Success = TRYTOGETSPINLOCK_SUCCESS;
      /* Take Spinlock into local variable */
      LpSpinlock = &Os_GaaSpinlock[SpinlockId];
      /* polyspace +2 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
      /* Update TaskID into Spinlock structure */
      LpSpinlock->ddTaskId = Os_GpLinkTask[OS_CORE_ID]->ddTaskID;
      /* Update ddNextSpinIndex with Index of the previously aquired Spinlock */
      LpSpinlock->ddNextSpinIndex = LpTask->ddSpinlock;
      /* Update Spinlock ID in Task structure */
      LpTask->ddSpinlock = SpinlockId;
    }
    else /* End of if (LblStatus == OS_TRUE) */
    {
      /* @Trace: SafeOs_SUD_API_22904 */
      /* Unlock method of Spinlock in case of TryToGetSpinLock() return NOSUCCESS */
      Os_SpinlockUnLockMethod(SpinlockId);
    }
  } /* End of if (LenStatusReturn == E_OK) */

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_22905 */
    /* Store the parameter 1 - SpinlockId */
    OS_STORE_PARAM1_SPINLOCKID(SpinlockId);
    /* Store the service ID of TryToGetSpinlock */
    OS_STORE_SERVICE(OSServiceId_TryToGetSpinlock);
    /* Store the parameter 2 - Success */
    OS_STORE_PARAM2_SUCCESS(Success);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* @Trace: SafeOs_SUD_API_22906 */
  /* Return the value */
  return (LenStatusReturn);
} /* End of TryToGetSpinlock(SpinlockIdType SpinlockId,
   * P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success) */
#endif /* End of if (OS_SPINLOCK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_ReleaseAllSpinlocks                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function releases all the spinlocks associated **
**                        with the core.                                      **
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
** Return parameter     : Void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GpLinkTask                                       **
**                        Os_GaaTask, Os_GaaSpinlock                          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_ReleaseSpinlock()                                **
**                                                                            **
*******************************************************************************/
#if (OS_SPINLOCK == STD_ON)
FUNC(void, OS_CODE) Os_ReleaseAllSpinlocks(void)
{
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpLinkTask;
  P2VAR(Tdd_Os_Spinlock, AUTOMATIC, OS_VAR) LpSpinlock;
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) LpTask;
  CoreIDType OS_CORE_ID;

  /* @Trace: SafeOs_SUD_API_22401 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Point to the link list */
  LpLinkTask = Os_GpLinkTask[OS_CORE_ID];
  /* Point to the task corresponding to the link list */
  /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
  LpTask = &Os_GaaTask[LpLinkTask->ddTaskID];

  do
  {
    /* Run through the loop till any spinlock is assosiated with the task */
    while (LpTask->ddSpinlock != OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_22402 */
      /* Point to the spinlock */
      LpSpinlock = &Os_GaaSpinlock[LpTask->ddSpinlock];
      /* Update taskID with Invalid value into Spinlock structure */
      LpSpinlock->ddTaskId = OS_INVALID_VALUE;
      /* Update Spinlock id in Task structure with next task ID */
      LpTask->ddSpinlock = LpSpinlock->ddNextSpinIndex;
      /* Release the Spinlock */
      Os_ReleaseSpinlock(LpTask->ddSpinlock);
    }
    /* @Trace: SafeOs_SUD_API_22403 */
    /* Point to next link task */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually */
    LpLinkTask = LpLinkTask->pLinkList;

    /* RestartTask was not configured and got the end of linked list */
    if(LpLinkTask == NULL_PTR)
    {
      /* @Trace: SafeOs_SUD_API_22404 */
      /* Nothing to do and quit the loop */
      break;
    } /* @End of if(LpLinkTask == NULL_PTR) */

    /* Point to the task corresponding to the link list */
    /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
    LpTask = &Os_GaaTask[LpLinkTask->ddTaskID];
  } while (LpLinkTask->ddTaskID != OS_CORE_ID);
} /* End of Os_ReleaseAllSpinlocks(void) */
#endif /* End of if (OS_SPINLOCK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_SpinlockLockMethod                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function to support lock method  for spinlock  **
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
** Return parameter     : Void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaSpinlock, Os_GddISRLock, Os_GddISR2Lock,      **
**                        Os_GblISRLock, Os_GddOldSuspendOs,                  **
**                        Os_GddOldSuspendAll, Os_GpStaticTask,               **
**                        Os_GusCallevelCheck                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StartMonitor(), Os_SuspendInterrupts(),          **
**                        Os_SpinlockLockResource(), Os_IntRestore()          **
*******************************************************************************/
#if (OS_SPINLOCK == STD_ON)
static FUNC(void, OS_CODE) Os_SpinlockLockMethod(SpinlockIdType SpinlockId)
{
  Os_SpinlockMethod LenLockMethod = LOCK_NOTHING;
  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  Os_OldLevel_T *olp = NULL_PTR;   /* Pointer to Old level store */
  Os_IsrLockType *ncp = NULL_PTR;  /* Pointer to nesting counter */
  Os_IntStatus_T is = 0;
  Os_IntStatus_T level = 0;
  #endif

  #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  TickType LddRequestedTime;
  #endif

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  #if (OS_RES_SCHEDULER == STD_ON)
  ResourceType ResID;
  #endif
  /* @Trace: SafeOs_SUD_API_22701 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "SpinlockId have been checked before using" */
  LenLockMethod = Os_GaaSpinlock[SpinlockId].enSpinMethod;

  switch (LenLockMethod)
  {
    /* Lock all Interrupt */
    case LOCK_ALL_INTERRUPTS:
      /* Check if DisableAllInterrupts() is not called */
      if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
      {
        /* @Trace: SafeOs_SUD_API_22702 */
        level = OS_INT_MAX_PRIORITY;
        olp = &Os_GddOldSuspendAll[OS_CORE_ID];
        ncp = &Os_GddISRLock[OS_CORE_ID];
      }
      if (ncp != NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_22703 */
        is = Os_IntDisableConditional();

        if (*ncp == 0)
        {
          /* @Trace: SafeOs_SUD_API_22704 */
          *ncp = 1;

          #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
          if (
              #if (OS_CAT1_ISR_COUNT != OS_PRE_ZERO)
              /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
              (OS_NOT_IN_CAT1()) &&
              #endif
              ((Os_GusCallevelCheck[OS_CORE_ID] & (OS_CONTEXT_HOOK)) == OS_ZERO)
            )
          {
            /* @Trace: SafeOs_SUD_API_22705 */
            LpStaticTask = Os_GpStaticTask[OS_CORE_ID];
            /* Check if TP is configured for currently running object */
            /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually*/
            if (LpStaticTask->pStaticTimProtection != NULL_PTR)
            {
              /* @Trace: SafeOs_SUD_API_22706 */
              LddRequestedTime =
                /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
                LpStaticTask->pStaticTimProtection->ddAllInterruptLockTime;
              /* Check if All Interrupt Lock Budget is configured */
              if (LddRequestedTime != OS_ZERO)
              {
                /* @Trace: SafeOs_SUD_API_22707 */
                /* Start monitoring for All Interrupt Lock Budget */
                Os_StartMonitor(LddRequestedTime, OS_ALL_INT_LOCK, OS_ALL_INT_LOCK_INDEX);
              }
            } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
          }
          #endif /* End of if ((OS_ALLINTLOCK_TP_EB == STD_ON)
                  * || (OS_INTLOCK_TP_EB == STD_ON)) */
          /* @Trace: SafeOs_SUD_API_22708 */
          Os_SuspendInterrupts(olp, level);
        }
        else if (*ncp < (Os_IsrLockType)OS_SUSPENDNESTLIMIT)
        {
          /* @Trace: SafeOs_SUD_API_22709 */
          /* No need to restore the interrupt state here - they remain blocked
          * at the expected level. */
          (*ncp)++;
        }
        else
        {
          /* @Trace: SafeOs_SUD_API_22710 */
          Os_IntRestore(is);
        }
      }
      /* @Trace: SafeOs_SUD_API_22711 */
      break;
    /* Lock CAT2 Interrupt */
    #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
    case LOCK_CAT2_INTERRUPTS:
      /* Check if DisableAllInterrupts() is not called */
      if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
      {
        /* @Trace: SafeOs_SUD_API_22712 */
        if (Os_GddISRLock[OS_CORE_ID] == OS_ZERO)
        {
          /* @Trace: SafeOs_SUD_API_22714 */
          level = Os_CAT2_Max_Priority;
          olp = &Os_GddOldSuspendOs[OS_CORE_ID];
          ncp = &Os_GddISR2Lock[OS_CORE_ID];
        }
      }
      if (ncp != NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_22715 */
        is = Os_IntDisableConditional();

        if (*ncp == 0)
        {
          /* @Trace: SafeOs_SUD_API_22716 */
          *ncp = 1;

          #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
          if (
              #if (OS_CAT1_ISR_COUNT != OS_PRE_ZERO)
              /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
              (OS_NOT_IN_CAT1()) &&
              #endif
              ((Os_GusCallevelCheck[OS_CORE_ID] & (OS_CONTEXT_HOOK)) == OS_ZERO)
            )
          {
            /* @Trace: SafeOs_SUD_API_22717 */
            LpStaticTask = Os_GpStaticTask[OS_CORE_ID];
            /* Check if TP is configured for currently running object */
            /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually*/
            if (LpStaticTask->pStaticTimProtection != NULL_PTR)
            {
              /* @Trace: SafeOs_SUD_API_22718 */
              LddRequestedTime =
                /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
                LpStaticTask->pStaticTimProtection->ddInterruptLockTime;
              /* Check if OS Interrupt Lock Budget is configured */
              if (LddRequestedTime != OS_ZERO)
              {
                /* @Trace: SafeOs_SUD_API_22719 */
                /* Start monitoring for OS Interrupt Lock Budget */
                Os_StartMonitor(LddRequestedTime, OS_INT_LOCK, OS_INT_LOCK_INDEX);
              }
            } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
          }
          #endif /* End of if ((OS_ALLINTLOCK_TP_EB == STD_ON)
                  * || (OS_INTLOCK_TP_EB == STD_ON)) */
          /* @Trace: SafeOs_SUD_API_22720 */
          Os_SuspendInterrupts(olp, level);
        }
        else if (*ncp < (Os_IsrLockType)OS_SUSPENDNESTLIMIT)
        {
          /* @Trace: SafeOs_SUD_API_22721 */
          /* No need to restore the interrupt state here - they remain blocked
          * at the expected level. */
          (*ncp)++;
        }
        else
        {
          /* @Trace: SafeOs_SUD_API_22722 */
          Os_IntRestore(is);
        }
      }
      /* @Trace: SafeOs_SUD_API_22723 */
      break;
    #endif
    /* Lock RES_SCHEDULER */
    #if (OS_RES_SCHEDULER == STD_ON)
    case LOCK_WITH_RES_SCHEDULER:
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_22724 */
      /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "configured resource scheduler and os core id" */
      ResID = RES_SCHEDULER + OS_CORE_ID;
      #endif
      /* @Trace: SafeOs_SUD_API_22725 */
      Os_SpinlockLockResource(ResID);
      break;
    #endif
    /* Lock NOTHING */
    case LOCK_NOTHING:
      /* @Trace: SafeOs_SUD_API_22726 */
      break;
    /* polyspace +1 RTE:UNR [No action planned:Low] "Default switch-case with no lock methods of spinlock" */
    default:
      /* @Trace: SafeOs_SUD_API_22727 */
      /* Do Nothing */
      break;
  }
}
#endif /* End of if (OS_SPINLOCK == STD_ON) */
/*******************************************************************************
** Function Name        : Os_SpinlockUnLockMethod                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function to support lock method  for spinlock  **
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
** Return parameter     : Void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaSpinlock, Os_GddISRLock, Os_GddISR2Lock,      **
**                        Os_GblISRLock, Os_GddOldSuspendOs,                  **
**                        Os_GddOldSuspendAll, Os_GpStaticTask,               **
**                        Os_GusCallevelCheck                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StopIntMonitor(), Os_ResumeInterrupts(),         **
**                        Os_SpinlockUnLockResource(),                        **
**                        Os_IntDisableConditional(), Os_IntRestore()         **
*******************************************************************************/
/* @Trace: SRS_Os_80021 */
#if (OS_SPINLOCK == STD_ON)
/* polyspace +1 MISRA-C3:17.2 [Justified:Low] " Os_SpinlockUnLockResource -> Os_ScheduleService -> Os_CheckStack -> Os_ProtectionHookService -> Os_KillTaskOrISR -> ReleaseSpinlock -> OS_SYSCALL_RELEASESPINLOCK -> Os_SystemCallReleaseSpinlock ->Os_KernReleaseSpinlock ->Os_SpinlockUnLockMethod " */
static FUNC(void, OS_CODE) Os_SpinlockUnLockMethod(SpinlockIdType SpinlockId)
{
  Os_SpinlockMethod LenLockMethod = LOCK_NOTHING;
  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  Os_OldLevel_T *olp = NULL_PTR;   /* Pointer to Old level store */
  Os_IsrLockType *ncp = NULL_PTR;  /* Pointer to nesting counter */
  Os_IntStatus_T is;
  #endif

  #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  TickType LddRequestedTime;
  #endif

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  #if (OS_RES_SCHEDULER == STD_ON)
  ResourceType ResID;
  #endif
  /* @Trace: SafeOs_SUD_API_22601 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "SpinlockId have been checked before using" */
  LenLockMethod = Os_GaaSpinlock[SpinlockId].enSpinMethod;

  switch (LenLockMethod)
  {
    /* Lock all Interrupt */
    case LOCK_ALL_INTERRUPTS:
      /* Check if DisableAllInterrupts() is not called */
      if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
      {
        /* @Trace: SafeOs_SUD_API_22602 */
        olp = &Os_GddOldSuspendAll[OS_CORE_ID];
        ncp = &Os_GddISRLock[OS_CORE_ID];
      }
      if (ncp != NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_22603 */
        is = Os_IntDisableConditional();

        if (*ncp == 1)
        {
          #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
          if (
              #if (OS_CAT1_ISR_COUNT != OS_PRE_ZERO)
              /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
              (OS_NOT_IN_CAT1()) &&
              #endif
              ((Os_GusCallevelCheck[OS_CORE_ID] & (OS_CONTEXT_HOOK)) == OS_ZERO)
            )
          {
            /* @Trace: SafeOs_SUD_API_22604 */
            LpStaticTask = Os_GpStaticTask[OS_CORE_ID];
            /* Check if TP is configured for currently running object */
            /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually*/
            if (LpStaticTask->pStaticTimProtection != NULL_PTR)
            {
              /* @Trace: SafeOs_SUD_API_22605 */
              LddRequestedTime =
                /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
                LpStaticTask->pStaticTimProtection->ddAllInterruptLockTime;
              /* Check if All interrupt Lock Budget is configured */
              if (LddRequestedTime != OS_ZERO)
              {
                /* @Trace: SafeOs_SUD_API_22606 */
                /*Stop monitoring for All Interrupt Lock Budget*/
                Os_StopIntMonitor(LpStaticTask, OS_ALL_INT_LOCK_INDEX);
              }
            } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
          }
          #endif /* End of if ((OS_ALLINTLOCK_TP_EB == STD_ON)
                  * || (OS_INTLOCK_TP_EB == STD_ON)) */
          /* @Trace: SafeOs_SUD_API_22607 */
          *ncp = 0;
          Os_ResumeInterrupts(olp);
        }
        else if (*ncp >= 2)
        {
          /* @Trace: SafeOs_SUD_API_22608 */
          (*ncp)--;

          /* No need to restore here - already at the correct level */
        }
        else
        {
          /* @Trace: SafeOs_SUD_API_22609 */
          Os_IntRestore(is);
        }
      }
      /* @Trace: SafeOs_SUD_API_22610 */
      break;
    /* Lock CAT2 Interrupt */
    #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
    case LOCK_CAT2_INTERRUPTS:
      /* Check if DisableAllInterrupts() is not called */
      if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
      {
        if ( Os_GddISRLock[OS_CORE_ID] == OS_ZERO )
        {
          /* @Trace: SafeOs_SUD_API_22611 */
          olp = &Os_GddOldSuspendOs[OS_CORE_ID];
          ncp = &Os_GddISR2Lock[OS_CORE_ID];
        }
      }
      if (ncp != NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_22612 */
        is = Os_IntDisableConditional();

        if (*ncp == 1)
        {
          #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
          if (
              #if (OS_CAT1_ISR_COUNT != OS_PRE_ZERO)
              /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
              (OS_NOT_IN_CAT1()) &&
              #endif
              ((Os_GusCallevelCheck[OS_CORE_ID] & (OS_CONTEXT_HOOK)) == OS_ZERO)
            )
          {
            /* @Trace: SafeOs_SUD_API_22613 */
            LpStaticTask = Os_GpStaticTask[OS_CORE_ID];
            /* Check if TP is configured for currently running object */
            /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually*/
            if (LpStaticTask->pStaticTimProtection != NULL_PTR)
            {
                /* @Trace: SafeOs_SUD_API_22614*/
                LddRequestedTime =
                  /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
                  LpStaticTask->pStaticTimProtection->ddInterruptLockTime;
                /* Check if OS Interrupt Lock Budget is configured */
                if (LddRequestedTime != OS_ZERO)
                {
                  /* @Trace: SafeOs_SUD_API_22615 */
                  /* Stop monitoring for OS Interrupt Lock Budget */
                  Os_StopIntMonitor(LpStaticTask, OS_INT_LOCK_INDEX);
                }
            } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
          }
          #endif /* End of if ((OS_ALLINTLOCK_TP_EB == STD_ON)
                  * || (OS_INTLOCK_TP_EB == STD_ON)) */
          /* @Trace: SafeOs_SUD_API_22616 */
          *ncp = 0;
          Os_ResumeInterrupts(olp);
        }
        else if (*ncp >= 2)
        {
          /* @Trace: SafeOs_SUD_API_22617 */
          (*ncp)--;

          /* No need to restore here - already at the correct level */
        }
        else
        {
          /* @Trace: SafeOs_SUD_API_22618 */
          Os_IntRestore(is);
        }
      }
      /* @Trace: SafeOs_SUD_API_22619 */
      break;
    #endif
    /* Lock RES_SCHEDULER */
    #if (OS_RES_SCHEDULER == STD_ON)
    case LOCK_WITH_RES_SCHEDULER:
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_22620 */
      /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "configured resource scheduler and os core id" */
      ResID = RES_SCHEDULER + OS_CORE_ID;
      #endif
      /* @Trace: SafeOs_SUD_API_22621 */
      Os_SpinlockUnLockResource(ResID);
      break;
    #endif
    /* Lock NOTHING */
    case LOCK_NOTHING:
      /* @Trace: SafeOs_SUD_API_22622 */
      break;
    /* polyspace +1 RTE:UNR [No action planned:Low] "Default switch-case with no unlock methods of spinlock" */
    default:
      /* @Trace: SafeOs_SUD_API_22623 */
      /* Do Nothing */
      break;
  }
}
#endif /* End of if (OS_SPINLOCK == STD_ON) */
/*******************************************************************************
** Function Name        : Os_SpinlockLockResource                             **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This Function is used to Get the resource for       **
**                        spinlock                                            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ResourceType ResID                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaResourceTable, Os_GpLinkTask,                 **
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StartMonitor()                                   **
*******************************************************************************/
#if (OS_RES_SCHEDULER == STD_ON) && (OS_SPINLOCK == STD_ON)
static FUNC(void, OS_CODE) Os_SpinlockLockResource(ResourceType ResID)
{
  #if (OS_RES_TP_EB == STD_ON)
  TickType LddRequestedTime;
  #endif
  P2VAR(Tdd_Os_Resource, AUTOMATIC, OS_VAR) LpResource;
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) LpTask;
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* @Trace: SafeOs_SUD_API_22301 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LpResource = &Os_GaaResourceTable[ResID];
  /* polyspace-begin RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
  /* Get the currently running Task in a local pointer */
  LpStaticTask = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];
  #if (OS_RES_TP_EB == STD_ON)

  /* Check if timing protection is configured for currently running object */
  if (LpStaticTask->pStaticTimProtection != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_22302 */
    /* polyspace +2 RTE:NIP [Not a defect:Unset] "ptr points to a valid value and code is verified manually" */
    LddRequestedTime = LpStaticTask->pStaticTimProtection->pResourceLockTime[ResID];

    /* Check if Resource Lock Budget is configured */
    if (LddRequestedTime != OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_22303 */
      /* polyspace +1 CERT-C:MEM35-C DEFECT:OUT_BOUND_PTR [Justified:Low] "Ptr points to a valid value and code is verified manually" */
      Os_StartMonitor(LddRequestedTime, OS_REZ_LOCK, LpResource->ddResLockTimeIndex);
    }
  } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
  #endif /* End of if (OS_RES_TP_EB == STD_ON) */
  /* @Trace: SafeOs_SUD_API_22304 */
  LpTask = LpStaticTask->pTask;
  /* Set the owner of the resource to the calling task */
  /* polyspace +1 CERT-C:MEM35-C DEFECT:OUT_BOUND_PTR [Justified:Low] "Ptr points to a valid value and code is verified manually" */
  LpResource->pOwner = LpTask;
  /* Add the ressource at the beginning of the resource list stored in the
   *   task descriptor */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually */
  LpResource->pNextResource = LpTask->pResources;
  /* Occupy requested resource */
  LpTask->pResources = LpResource;
  /* Save the current priority of the task in the resource */
  LpResource->scOwnerPrevPriority = (uint8) Os_GpLinkTask[OS_CORE_ID]->scPriority;

  if (Os_GpLinkTask[OS_CORE_ID]->scPriority < (sint8) LpResource->scCeilingPriority)
  {
    /* @Trace: SafeOs_SUD_API_22305 */
    /* Update Priority for Os_GpLinkTask */
    Os_GpLinkTask[OS_CORE_ID]->scPriority = (sint8) LpResource->scCeilingPriority;
  }
  /* polyspace-end RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
}
#endif
/*******************************************************************************
** Function Name        : Os_SpinlockUnLockResource                           **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This Function is used to Release the resource for   **
**                        spinlock                                            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ResourceType ResID                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaResourceTable, Os_GpLinkTask                  **
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_InsertPreemptedTask(),                           **
**                        Os_StopResMonitor(),                                **
**                        Os_ScheduleService(),                               **
**                        Os_TaskPreemptionHook()                             **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_AUTRON_00017 */
#if (OS_RES_SCHEDULER == STD_ON) && (OS_SPINLOCK == STD_ON)
/* polyspace +1 MISRA-C3:17.2 [Justified:Low] " Os_ScheduleService -> Os_CheckStack -> Os_ProtectionHookService -> Os_KillTaskOrISR -> ReleaseSpinlock -> OS_SYSCALL_RELEASESPINLOCK -> Os_SystemCallReleaseSpinlock ->Os_KernReleaseSpinlock ->Os_SpinlockUnLockMethod -> Os_SpinlockUnLockResource" */
static FUNC(void, OS_CODE) Os_SpinlockUnLockResource(ResourceType ResID)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  P2VAR(Tdd_Os_Resource, AUTOMATIC, OS_VAR) LpResource;
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpNextLink;
  #if (OS_RES_TP_EB == STD_ON)
  TickType LddRequestedTime;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_22501 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LpResource = &Os_GaaResourceTable[ResID];
  /* polyspace-begin RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
  /* Get the currently running Task in a local pointer */
  LpStaticTask = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];
  #if (OS_RES_TP_EB == STD_ON)

  /* Check if timing protection is configured for currently running object */
  if (LpStaticTask->pStaticTimProtection != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_22502 */
    /* polyspace +2 RTE:NIP [Not a defect:Unset] "ptr points to a valid value and code is verified manually" */
    LddRequestedTime = LpStaticTask->pStaticTimProtection->pResourceLockTime[ResID];

    /* Check if Resource Lock Budget is configured */
    if (LddRequestedTime != OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_22503 */
      /* Stop resource lock budget */
      Os_StopResMonitor(LpStaticTask, LpResource);
    }
  } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
  #endif /* OS_TIMING_PROTECTION */
  /* @Trace: SafeOs_SUD_API_22504 */
  /* Save the current priority of the task in the resource   */
  /* polyspace +1 CERT-C:MEM35-C DEFECT:OUT_BOUND_PTR [Justified:Low] "Ptr points to a valid value and code is verified manually" */
  Os_GpLinkTask[OS_CORE_ID]->scPriority = (sint8) LpResource->scOwnerPrevPriority;
  /* Remove the resource from the resource list  */
  LpStaticTask->pTask->pResources = LpResource->pNextResource;
  /* Update NextResource of the Resource with NULL_PTR*/
  LpResource->pNextResource = NULL_PTR;
  /* Remove the owner */
  LpResource->pOwner = NULL_PTR;

  /* polyspace<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually */
  LpNextLink = Os_GpLinkTask[OS_CORE_ID]->pLinkList;

  /* Check if Context switch is required */
  if (LpNextLink->scPriority > Os_GpLinkTask[OS_CORE_ID]->scPriority)
  {
    #if (OS_POSTTASK_HOOK == STD_ON)
    /* @Trace: SafeOs_SUD_API_22505 */
    /* Process PostTaskHook */
    OS_PROCESS_POSTTASKHOOK();
    #endif
    /* @Trace: SafeOs_SUD_API_22506 */
    /* Update Os_GpLinkTask */
    Os_GpLinkTask[OS_CORE_ID] = LpNextLink;
    #if (OS_TASK  == STD_ON)
    /* Insert the preempted task */
    Os_InsertPreemptedTask(LpStaticTask);
    #endif
    /* Change state of the running task to ready */
    LpStaticTask->pTask->ddState = READY;
    #if (OS_PROFILING_HOOK == STD_ON)
    /* @Trace: SafeOs_SUD_API_22507 */
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
    Os_TaskPreemptionHook(OS_CORE_ID, LpStaticTask->ddTaskId);
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
    #endif
    /* @Trace: SafeOs_SUD_API_22508 */
    Os_ScheduleService();
    /* @Trace: SafeOs_SUD_API_22509 */
    OS_SAVECONTEXT();
    /* polyspace-end RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
  } /* End of if (LpNextLink->scPriority >
       *Os_GpLinkTask[OS_CORE_ID]->scPriority) */
}
#endif

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define OS_API_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#if (OS_SPINLOCK == STD_ON)
/***************************************************************************//**
 * Function Name        : Os_CallReleaseSpinlock
 *
 * Service ID           : OSServiceId_ReleaseSpinlock
 *
 * Description          : Os_CallReleaseSpinlock calls system call to release
 *                        a spinlock variable that was occupied before.
 *                        Before terminating a TASK all spinlock variables
 *                        that have been occupied with GetSpinlock()
 *                        shall be released.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param [in]            SpinlockId    The value refers to the spinlock
 *                                      instance that shall be locked
 *                                      (range : 0 ~ OS_SPINLOCK_COUNT - 1)
 *
 * @return              : StatusType
 *                        - E_OK : No Error
 *                        - E_OS_ID : The <SpinlockId> is invalid
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ACCESS : The spinlock cannot be accessed
 *                        - E_OS_STATE : The Spinlock is not occupied
 *                        - E_OS_NOFUNC : Attempt to release a spinlock while
 *                          another spinlock has to be released before
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* polyspace +1 MISRA-C3:17.2 [Justified:Low] "OS_SYSCALL_RELEASESPINLOCK -> Os_SystemCallReleaseSpinlock ->Os_KernReleaseSpinlock -> Os_SpinlockUnLockMethod -> Os_ScheduleService -> Os_CheckStack -> Os_ProtectionHookService -> Os_KillTaskOrISR -> ReleaseSpinlock -> Os_CallReleaseSpinlock" */
FUNC(StatusType, OS_CODE) Os_CallReleaseSpinlock(SpinlockIdType SpinlockId)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace: SafeOs_SUD_API_54401 */
  LddStatusReturn = OS_SYSCALL_RELEASESPINLOCK(SpinlockId);
  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : Os_CallTryToGetSpinlock
 *
 * Service ID           : OSServiceId_TryToGetSpinlock
 *
 * Description          : The TryToGetSpinlockType indicates if the spinlock
 *                        has been occupied or not.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param [in]            SpinlockId    The value refers to the spinlock
 *                                      instance that shall be locked
 *                                      (range : 0 ~ OS_SPINLOCK_COUNT - 1)
 * @param [out]           Success       Returns if the lock has been occupied
 *                                      or not
 *                                      (range : TRYTOGETSPINLOCK_SUCCESS,
 *                                               TRYTOGETSPINLOCK_NOSUCCESS)
 *
 * @return              : StatusType
 *                        - E_OK : No Error
 *                        - E_OS_ID : The <SpinlockId> is invalid
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ACCESS : The spinlock cannot be accessed
 *                        - E_OS_INTERFERENCE_DEADLOCK : A TASK tries to occupy
 *                          the spinlock while the lock is already occupied by
 *                          a TASK on the same core. This would cause a deadlock
 *                        - E_OS_NESTING_DEADLOCK : A TASK tries to occupy the
 *                          spinlock while holding a different spinlock in a way
 *                          that may cause a deadlock
 *                        - E_OS_PARAM_POINTER : <Success> is a NULL_PTR
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
FUNC(StatusType, OS_CODE) Os_CallTryToGetSpinlock(SpinlockIdType SpinlockId,
     P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace: SafeOs_SUD_API_54501 */
  LddStatusReturn = OS_SYSCALL_TRYTOGETSPINLOCK(SpinlockId, Success);
  return LddStatusReturn;
}
#endif

#define OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/* polyspace-end DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
/* polyspace-end CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
