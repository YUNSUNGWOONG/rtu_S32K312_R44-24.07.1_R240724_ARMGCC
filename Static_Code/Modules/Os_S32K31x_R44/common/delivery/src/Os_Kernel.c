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
**  SRC-MODULE: Os_Kernel.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Kernel functionality                             **
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
** 1.5.0.1   27-Nov-2023   JHLim            Jira CP44-2916                    **
** 1.5.0     13-Sep-2023   HJ.Kim           Jira CP44-2965                    **
**           25-Jul-2023   HJ.Kim           Jira CP44-2549                    **
**            9-Jun-2023   HJ.Kim           Jira CP44-2325                    **
**                                          Jira CP44-2322                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-2247                    **
**                                          Jira CP44-2097                    **
**                                          Jira CP44-2075                    **
** 1.3.12.0  09-Mar-2023   TanHX            Jira CP44-1335                    **
** 1.4.0     19-Sep-2022   TinHV            Jira CP44-192                     **
** 1.3.10.1  24-Aug-2022   Manje Woo        Jira CP44-766                     **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.8     07-Oct-2020   DanhDC1          R44-Redmine #15959                **
**                                          Remove un-used function           **
** 1.0.7     22-Sep-2020   TamNN1           R44-Redmine #15236                **
**                                          R44-Redmine #12870                **
**                                          Fixed Defect detect by polyspace  **
** 1.0.6     16-Sep-2020   Thao             R44-Redmine #13398 Change access  **
**                                          rights of specific Os application **
**                                          Hooks                             **
** 1.0.5     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
** 1.0.4     12-Sep-2020   DanhDC1          R44-Redmine #14284                **
** 1.0.3     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C 20.7                **
**                                          Add comment for Misra-C 17.2      **
** 1.0.2     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.1     17-Jul-2020   DanhDC1          R44-Redmine #14601 Change the type**
**                                          of internal variable for the      **
**                                          ActivateTaskCount                 **
**                                          and Os_GaaLinkIndex variable      **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually." */
/* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace:begin<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually*/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os Ram header file */
#include "Os_Stack.h"             /* Os Stack header file */
#include "Os_Resource.h"          /* Os Resource header file */
#include "Os_Task.h"              /* Os Task header file */
#include "Os_Alarm.h"             /* Os Alarm header file */
/* @Trace: SRS_BSW_00410 */
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_TimingProtection.h" /* Os TimerProtection header file */
#endif
#include "Os_Kernel.h"            /* Os Kernel header file */
#include "Os_Error.h"             /* Os Error header file */
#if (OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Application.h"       /* Os Application header file */
#endif
#include "Os_Interrupt.h"         /* Os Interrupt header file */
#if (OS_MULTICORE == STD_ON)
#include "Os_MulticoreMessage.h"
#endif
#if (OS_PROTECTION_HOOK == STD_ON)
#include "Os_Shutdown.h"
#endif
#include "Os_SystemCallTable.h"

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

#if ((OS_TASK == STD_ON) || (OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON))
static FUNC(void, OS_CODE) Os_InitOS(void);
#endif
#if ((OS_TASK == STD_ON) && (OS_CAT2_ISR_COUNT != OS_PRE_ZERO))
static FUNC(void, OS_CODE) Os_RunISR(void);
#endif

/*******************************************************************************
** Function Name        : Os_InsertTask                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is used to put a new task in link list **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : LpStaticTask                                        **
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
**                        Os_GpLinkTask                                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if (OS_TASK == STD_ON)
FUNC(void, OS_CODE) Os_InsertTask(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
                                                         OS_CONST) LpStaticTask)
{
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpLinkTask;
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpCurrentLink;
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpNextLink;
  #if (OS_MAX_ACTIVATION_COUNT != OS_ONE)
  /* Intenal variable index of link Task */
  TaskType LulIndex;
  #endif
  #if (OS_MULTICORE == STD_ON)
  /* @Trace: SafeOs_SUD_API_03401 */
  /* Take Os_GpLinkTask in local variable */
  LpCurrentLink = Os_GpLinkTask[LpStaticTask->ddCoreId];
  #else
  /* @Trace: SafeOs_SUD_API_03402 */
  LpCurrentLink = Os_GpLinkTask[OS_ZERO];
  #endif

  /* Insert task in queue */
  OS_INSERT_TASK_IN_QUEUE();
  /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "LpCurrentLink to check ptr NULL before used" */
  /* Point to next link list */
  LpNextLink = LpCurrentLink->pLinkList;
  /* Check if Next list is not a NULL_PTR and it's priority is greater than
   *   the task priority */
  while ((LpNextLink != NULL_PTR) &&
                             (LpNextLink->scPriority >= LpLinkTask->scPriority))
  {
    /* @Trace: SafeOs_SUD_API_03403 */
    /* Point to next link list */
    LpCurrentLink = LpNextLink;
    /* Update LpNextLink */
    LpNextLink = LpCurrentLink->pLinkList;
  }

  /* Insert task in link list */
  LpCurrentLink->pLinkList = LpLinkTask;
  /* Update Next link list for the current task */
  LpLinkTask->pLinkList = LpNextLink;
  /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "LpCurrentLink to check ptr NULL before used" */
} /* End of Os_InsertTask(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
   * OS_CONST) LpStaticTask) */
#endif /*OS_TASK == STD_ON*/

/*******************************************************************************
** Function Name        : Os_InsertPreemptedTask                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is used to put a preempted task        **
**                        in link list                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : LpStaticTask                                        **
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
**                        Os_GpLinkTask                                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if (OS_TASK == STD_ON)
FUNC(void, OS_CODE) Os_InsertPreemptedTask
                 (P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask)
{
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpLinkTask;
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpCurrentLink;
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpNextLink;
  #if (OS_MAX_ACTIVATION_COUNT != OS_ONE)
  /* Intenal variable index of link Task */
  TaskType LulIndex;
  #endif

  /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "The parameter has been checked before used" */
  #if (OS_MULTICORE == STD_ON)
  /* @Trace: SafeOs_SUD_API_03506 */
  /* Take Os_GpLinkTask in local variable */
  LpCurrentLink = Os_GpLinkTask[LpStaticTask->ddCoreId];
  #else
  /* @Trace: SafeOs_SUD_API_03507 */
  LpCurrentLink = Os_GpLinkTask[OS_ZERO];
  #endif

  /* Get task in queue */
  #if (OS_MAX_ACTIVATION_COUNT != OS_ONE)
  /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "The parameter has been checked before used" */
  if (LpStaticTask->ulMaxActivateCount == OS_ONE)
  {
    /* @Trace: SafeOs_SUD_API_03501 */
    LpLinkTask = LpStaticTask->pLinkTask;
  }
  else
  {
    LulIndex = Os_GaaLinkIndex[LpStaticTask->ddTaskId];

    if (LulIndex >= LpStaticTask->pTask->ulActivateCount)
    {
      /* @Trace: SafeOs_SUD_API_03502 */
      LulIndex -= LpStaticTask->pTask->ulActivateCount;
    }
    else
    {
      /* @Trace: SafeOs_SUD_API_03503 */
      /* Intended code:
      LulIndex = LpStaticTask->ulMaxActivateCount -
                           (LpStaticTask->pTask->ulActivateCount - LulIndex); */
      /* Equivalent code: */
      LulIndex += (LpStaticTask->ulMaxActivateCount -
                                          LpStaticTask->pTask->ulActivateCount);
    }
    /* polyspace +1 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
    LpLinkTask = LpStaticTask->pLinkTask + LulIndex;
  }
  #else
  /* @Trace: SafeOs_SUD_API_03504 */
  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
  /* polyspace +1 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
  LpLinkTask = LpStaticTask->pLinkTask;
  #endif
  /* Point to next link list */
  LpNextLink = LpCurrentLink->pLinkList;
  /* Check if Next list is not a NULL_PTR and it's priority is greater than
   *   the task priority */
  while ((LpNextLink != NULL_PTR) &&
                             (LpNextLink->scPriority > LpLinkTask->scPriority))
  {
    /* @Trace: SafeOs_SUD_API_03505 */
    /* Point to next link list */
    LpCurrentLink = LpNextLink;
    /* Update LpNextLink */
    LpNextLink = LpCurrentLink->pLinkList;
  }

  /* Insert task in link list */
  LpCurrentLink->pLinkList = LpLinkTask;
  /* Update Next link list for the current task */
  LpLinkTask->pLinkList = LpNextLink;
  /* polyspace-end MISRA-C3:D4.14 [Not a defect:Low] "The parameter has been checked before used" */
}
#endif /* End of if (OS_TASK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_ScheduleService                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This service causes scheduling of a  task,          **
**                        if previous task is terminated or pre-empted and    **
**                        updates the task link list if needed                **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
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
**                        Os_GpStaticTask, Os_GpLinkTask                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_CheckStack(),                                    **
**                        Os_StopExecutionBudget(),                           **
**                        Os_PauseTimingProtection(),                         **
**                        Os_ReleaseInternalResource(),                       **
**                        Os_TaskTerminationHook()                            **
*******************************************************************************/
/* @Trace: SRS_Os_11008 SRS_AUTRON_00014 */
/* polyspace +1 MISRA-C3:17.2 [Justified:Low] "Os_CheckStack -> Os_ProtectionHookService -> Os_KillTaskOrISR -> ReleaseSpinlock -> OS_SYSCALL_RELEASESPINLOCK -> Os_SystemCallReleaseSpinlock ->Os_KernReleaseSpinlock -> Os_SpinlockUnLockMethod -> Os_ScheduleService " */
FUNC(void, OS_CODE) Os_ScheduleService(void)
{
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) LpTask;
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  #if (OS_TASK_TP_EB == STD_ON)
  TickType LddRequestedTime;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  /* @Trace: SafeOs_SUD_API_04001 */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  LpStaticTask = Os_GpStaticTask[OS_CORE_ID];

  #if (OS_STACK_MONITORING == STD_ON)
  /* @Trace: SafeOs_SUD_API_04002 */
  /* Call function to check Stack if it overflows */
  Os_CheckStack(LpStaticTask);
  #endif /* OS_STACK_MONITORING */
  /* Store current task in local variable */
  LpTask = LpStaticTask->pTask;

  #if (OS_TASK_TP_EB == STD_ON)

  /* Check if timing protection is configured for the currently running Task */
  if (LpStaticTask->pStaticTimProtection != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_04003 */
    LddRequestedTime = LpStaticTask->pStaticTimProtection->ddExecutionBudget;

    /* Check if Execution Budget is configured */
    if (LddRequestedTime != OS_ZERO)
    {
      /* Check if the task is to be terminated or waiting */
      if ((LpTask->ddState == DYING) || (LpTask->ddState == WAITING))
      {
        /* @Trace: SafeOs_SUD_API_04004 */
        /* Stop the execution budget monitoring */
        Os_StopExecutionBudget(LpStaticTask);
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_04005 */
        /* Call a function to Pause Execution budget */
        Os_PauseTimingProtection();
      }
    } /* End of if (LddRequestedTime != OS_ZERO) */
  } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
  #endif /* End of if (OS_TASK_TP_EB == STD_ON) */

  /* Check if the task is not in ready state */
  if (LpTask->ddState >= WAITING)
  {
    /* Check if the task is to be terminated */
    if (LpTask->ddState == DYING)
    {
      #if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO)
      /* @Trace: SafeOs_SUD_API_04006 */
      /* Release internal resource */
      Os_ReleaseInternalResource(LpStaticTask);
      #endif

      #if (OS_EVENT == STD_ON)
      /* If the object is an EXTENDED task, initialize the events */
      if (LpStaticTask->usType == OS_TASK_EXTENDED)
      {
        /* @Trace: SafeOs_SUD_API_04007 */
        /* Set ddEventSet to ZERO */
        LpTask->ddEventSet = OS_ZERO;
        /* Set ddEventWait to ZERO */
        LpTask->ddEventWait = OS_ZERO;
      } /* End of if (LpStaticTask->ucType == OS_TASK_EXTENDED) */
      #endif /* End of if (OS_EVENT == STD_ON) */

      /* Decrement Activate count by one */
      LpTask->ulActivateCount--;

      /* Check if Task needs to be activated again */
      if (LpTask->ulActivateCount != OS_ZERO)
      {
        #if (OS_PROFILING_HOOK == STD_ON)
        /* @Trace: SafeOs_SUD_API_04008 */
        /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
        Os_TaskTerminationHook(OS_CORE_ID, LpStaticTask->ddTaskId);
        /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
        #endif
        /* @Trace: SafeOs_SUD_API_04009 */
        /* Change state of the task to OS_READY_AND_NEW */
        LpTask->ddState = OS_READY_AND_NEW;
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_04010 */
        /* Change the state to SUSPENDED */
        LpTask->ddState = SUSPENDED;
        #if (OS_PROFILING_HOOK == STD_ON)
        /* @Trace: SafeOs_SUD_API_04011 */
        /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
        Os_TaskTerminationHook(OS_CORE_ID, LpStaticTask->ddTaskId);
        /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
        #endif
      }
    } /* End of if (LpTask->ddState == DYING) */
    /* @Trace: SafeOs_SUD_API_04012 */
    /* Update Os_GpLinkTask with next task */
    Os_GpLinkTask[OS_CORE_ID] = Os_GpLinkTask[OS_CORE_ID]->pLinkList;
  } /* End of if (LpTask->ddState >= WAITING) */
  /* NOTE: Os_RunTask() separately executed later.
   * Call Os_RunTask function to put task in Running mode */
} /* End of Os_ScheduleService(void) */

/*******************************************************************************
** Function Name        : Os_KernSchedule                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service checks if a higher-priority task is    **
**                        ready, the internal resource of the task is released**
**                        the current task is put into the ready state        **
**                        and the higher-priority task is executed. Otherwise **
**                        the calling task is continued.                      **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
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
**                        Os_GpStaticTask, Os_GpLinkTask                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_GetInternalResource()                            **
**                        Os_InsertPreemptedTask(), Os_TaskPreemptionHook(),  **
**                        Os_ReleaseInternalResource(), Os_ScheduleService()  **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11008 SRS_Os_80021 SRS_AUTRON_00017 SRS_AUTRON_00012 SRS_AUTRON_00014 */
#if (OS_TASK == STD_ON)
/* polyspace +1 CODE-METRICS:CALLS [Not a defect:Low] "Function is called to checks the priority task" */
FUNC(StatusType, OS_CODE) Os_KernSchedule(void)
{
  #if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO)
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpNextLink;
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  #endif
  StatusType LenStatusReturn;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_03906 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(SCHEDULE, LenStatusReturn);
  /* Check we are at the task level */
  OS_CHECK_TASK_CALL_LEVEL_ERROR(LenStatusReturn);
  /* Check the task does not own a resource */
  OS_CHECK_RUNNING_OWNS_REZ_ERROR(LenStatusReturn);
  /* Check the task does not own a spinlock */
  OS_CHECK_RUNNING_OWNS_SPINLOCK_ERROR(LenStatusReturn);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    #if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO)
    /* @Trace: SafeOs_SUD_API_03901 */
    LpStaticTask = Os_GpStaticTask[OS_CORE_ID];
    /* Release the internal resource */
    Os_ReleaseInternalResource(LpStaticTask);
    /* Take next link list in local variable */
    LpNextLink = Os_GpLinkTask[OS_CORE_ID]->pLinkList;

    /* Check if the task needs to be */
    if (LpNextLink->scPriority > Os_GpLinkTask[OS_CORE_ID]->scPriority)
    {
      #if (OS_POSTTASK_HOOK == STD_ON)
      /* @Trace: SafeOs_SUD_API_03902 */
      /* Process PostTaskHook */
      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      OS_PROCESS_POSTTASKHOOK();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      #endif
      /* Update Os_GpLinkTask */
      Os_GpLinkTask[OS_CORE_ID] = LpNextLink;
      /* Insert the preempted task */
      Os_InsertPreemptedTask(LpStaticTask);
      Os_GpStaticTask[OS_CORE_ID]->pTask->ddState = READY;
      #if (OS_PROFILING_HOOK == STD_ON)
      /* @Trace: SafeOs_SUD_API_03903 */
      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      Os_TaskPreemptionHook(OS_CORE_ID, Os_GpStaticTask[OS_CORE_ID]->ddTaskId);
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      #endif
      /* @Trace: SafeOs_SUD_API_03907 */
      /* Call Function to switch context with new task */
      Os_ScheduleService();
      OS_SAVECONTEXT();
    } /* End of if (LpNextLink->scPriority >
       *Os_GpLinkTask[OS_CORE_ID]->scPriority) */
    /* @Trace: SafeOs_SUD_API_03904 */
    /* Get the internal resource */
    Os_GetInternalResource(Os_GpStaticTask[OS_CORE_ID]);
    #endif /* End of if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO) */
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  else
  {
    /* @Trace: SafeOs_SUD_API_03905 */
    /* Lock the task or ISR */
    OS_STORE_SERVICE(OSServiceId_Schedule);
    /* Call Error Hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* Return the value */
  return (LenStatusReturn);
} /* End of Schedule(void) */
#endif /* End of if (OS_TASK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_ScheduleFromChain                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function does the scheduling when called from  **
**                        a dying object, and when same object is to be       **
**                        inserted again                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
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
**                        Os_GpStaticTask, Os_GpLinkTask                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_CheckStack(),                                    **
**                        OS_PROCESS_POSTTASKHOOK(),                          **
**                        Os_InsertTask(),                                    **
**                        Os_StopExecutionBudget(),                           **
**                        Os_ReleaseInternalResource(),                       **
**                        Os_TaskTerminationHook(),                           **
**                        Os_TaskActivationHook()                             **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_AUTRON_00012 SRS_AUTRON_00014  */
#if (OS_TASK == STD_ON)
FUNC(void, OS_CODE) Os_ScheduleFromChain(void)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  #if (OS_TASK_TP_EB == STD_ON)
  TickType LddRequestedTime;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_03701 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Get the pointer to current running task */
  LpStaticTask = Os_GpStaticTask[OS_CORE_ID];

  #if (OS_STACK_MONITORING == STD_ON)
  /* @Trace: SafeOs_SUD_API_03702 */
  /* Call function to check Stack if it overflows */
  Os_CheckStack(LpStaticTask);
  #endif
  #if (OS_POSTTASK_HOOK == STD_ON)
  /* @Trace: SafeOs_SUD_API_03703 */
  /* Process PostTaskHook */
  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  OS_PROCESS_POSTTASKHOOK();
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  #endif
  #if (OS_TASK_TP_EB == STD_ON)

  /* Check if timing protection is configured for the currently running Task */
  if (LpStaticTask->pStaticTimProtection != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_03704 */
    LddRequestedTime = LpStaticTask->pStaticTimProtection->ddExecutionBudget;

    /* Check if Execution Budget is configured */
    if (LddRequestedTime != OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_03705 */
      /* Stop the execution budget monitoring */
      Os_StopExecutionBudget(LpStaticTask);
    }
  } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
  #endif /* End of if (OS_TASK_TP_EB == STD_ON) */

  #if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO)
  /* @Trace: SafeOs_SUD_API_03706 */
  /* Release internal resource */
  Os_ReleaseInternalResource(LpStaticTask);
  #endif

  #if (OS_PROFILING_HOOK == STD_ON)
  /* @Trace: SafeOs_SUD_API_03707 */
  LpStaticTask->pTask->ddState = SUSPENDED;
  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  Os_TaskTerminationHook(OS_CORE_ID, LpStaticTask->ddTaskId);
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  #endif
  /* Make state of the Task to READY and NEW*/
  LpStaticTask->pTask->ddState = OS_READY_AND_NEW;
  #if (OS_PROFILING_HOOK == STD_ON)
  /* @Trace: SafeOs_SUD_API_03708 */
  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  Os_TaskActivationHook(OS_CORE_ID, LpStaticTask->ddTaskId);
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
  #endif
  if (Os_GpLinkTask[OS_CORE_ID]->scPriority <=
                               Os_GpLinkTask[OS_CORE_ID]->pLinkList->scPriority)
  {
    /* @Trace: SafeOs_SUD_API_03709 */
    Os_GpLinkTask[OS_CORE_ID] = Os_GpLinkTask[OS_CORE_ID]->pLinkList;
    /* Put a new executable object in the ready executable object list */
    Os_InsertTask(LpStaticTask);
  }
} /* End of Os_ScheduleFromChain(void) */
#endif /* End of if (OS_TASK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_RunTask                                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to put new task in Running mode**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
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
**                        Os_GpLinkTask, Os_GddAppId,                         **
**                        Os_GaaStaticTask, Os_GpStaticTask                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_ReInitContext(),                                 **
**                        Os_StartMonitor(),                                  **
**                        Os_GetInternalResource(),                           **
**                        Os_HandleMemoryBlock(),                             **
**                        Os_TaskRunningHook(),                               **
**                        Os_ContinueTimingProtection(),                      **
**                        Os_RunISR()                                         **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11008 SRS_AUTRON_00013 */
#if (OS_TASK == STD_ON)
FUNC(void, OS_CODE) Os_RunTask(void)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) LpTask;
  #if (OS_TASK_TP_EB == STD_ON)
  TickType LddRequestedTime;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Take the Static task into local pointer */
  LpStaticTask = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];
  /* Update the currently running task */
  Os_GpStaticTask[OS_CORE_ID] = LpStaticTask;

  #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
  if (LpStaticTask->usType != OS_ISR2)
  #endif
  {
    /* @Trace: SafeOs_SUD_API_03315 */
    /* Take the task into local pointer */
    LpTask = LpStaticTask->pTask;

    /* Check if State is in OS_READY_AND_NEW state */
    if (LpTask->ddState == OS_READY_AND_NEW)
    {
      #if (OS_EVENT == STD_ON)
      /* If the object is an EXTENDED task, initialize the events */
      if (LpStaticTask->usType == OS_TASK_EXTENDED)
      {
        /* @Trace: SafeOs_SUD_API_03301 */
        /* Set ddEventSet to ZERO */
        LpTask->ddEventSet = OS_ZERO;
        /* Set ddEventWait to ZERO */
        LpTask->ddEventWait = OS_ZERO;
      } /* End of if (LpStaticTask->ucType == OS_TASK_EXTENDED) */
      #endif /* End of if (OS_EVENT == STD_ON) */
      /* @Trace: SafeOs_SUD_API_03302 */
      /* Re-Initialize the context for task */
      Os_ReInitContext(LpStaticTask);
    } /* End of if (LpTask->ddState == OS_READY_AND_NEW) */

    #if (OS_TASK_TP_EB == STD_ON)
    /* Check if State is in OS_READY_AND_NEW or OS_READY_AND_WAITING state */
    if ((LpTask->ddState == OS_READY_AND_NEW)
                                  || (LpTask->ddState == OS_READY_AND_WAITING))
    {
      /* @Trace: SafeOs_SUD_API_03303 */
      /* Check if timing protection is configured for currently running object */
      if (LpStaticTask->pStaticTimProtection != NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_03304 */
        /* Save execution budget time in a local */
        LddRequestedTime = LpStaticTask->pStaticTimProtection->ddExecutionBudget;

        /* Check if Execution Budget is configured */
        if (LddRequestedTime != OS_ZERO)
        {
          /* @Trace: SafeOs_SUD_API_03305 */
          /* Invoke the fuction Os_StartMoniter */
          Os_StartMonitor(LddRequestedTime, OS_EXEC_BUDGET,
              LpStaticTask->pStaticTimProtection->ucTaskExeBudgetIndex);
        }
      } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
    } /* End of if (LpTask->ddState == OS_READY_AND_NEW || ... */
    else
    {
      /* @Trace: SafeOs_SUD_API_03306 */
      /* Check if timing protection is configured for currently running object */
      if (LpStaticTask->pStaticTimProtection != NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_03307 */
        /* Continue Execution budget */
        Os_ContinueTimingProtection(LpStaticTask);
      }
    } /* End of else */
    #endif /* End of if (OS_TASK_TP_EB == STD_ON) */
    #if (OS_MEMORY_PROTECTION == STD_ON)
    #if (OS_APP_MEMBLK_CNT != OS_ZERO)
    #if (OS_TRUSTED_START_INDX != OS_ZERO)
    /* @Trace: SafeOs_SUD_API_03309 */
    Os_HandleMemoryBlock(LpStaticTask);
    #endif
    #endif /* End of if (OS_APP_MEMBLK_CNT != OS_ZERO) */
    #endif /* End of if (OS_MEMORY_PROTECTION == STD_ON) */
    /* Update the currently running Application */
    #if(OS_APPLICATION == STD_ON)
    /* @Trace: SafeOs_SUD_API_03310 */
    Os_GddAppId[OS_CORE_ID] = LpStaticTask->ddAppId;
    #endif
    #if (OS_PROFILING_HOOK == STD_ON)
    /* @Trace: SafeOs_SUD_API_03311 */
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Os_TaskRunningHook(OS_CORE_ID, LpStaticTask->ddTaskId, LpTask->ddState);
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    #endif
    /* Make state of task as RUNNING */
    LpTask->ddState = RUNNING;
    #if (OS_PRETASK_HOOK == STD_ON)
    /* @Trace: SafeOs_SUD_API_03312 */
    /* Process PreTaskHook */
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    OS_PROCESS_PRETASKHOOK();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    #endif
    #if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO)
    /* @Trace: SafeOs_SUD_API_03313 */
    /* Get internal Resource */
    Os_GetInternalResource(LpStaticTask);
    #endif
  }
  #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
  else
  {
    /* @Trace: SafeOs_SUD_API_03314 */
    Os_RunISR();
  }
  #endif
} /* End of Os_RunTask(void) */
#endif /* End of if (OS_TASK == STD_ON) */


/*******************************************************************************
** Function Name        : Os_RunISR                                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to restart ISR                 **
**                        in OS-ApplicationRunning mode                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
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
**                        Os_GpLinkTask, Os_GddAppId,                         **
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_HandleMemoryBlock()                              **
**                        Os_ContinueTimingProtection()                       **
*******************************************************************************/
#if ((OS_TASK == STD_ON) && (OS_CAT2_ISR_COUNT != OS_PRE_ZERO))
static FUNC(void, OS_CODE) Os_RunISR(void)
{
  #if ((OS_ISR_TP_EB == STD_ON) || (OS_APPLICATION == STD_ON) || \
       (OS_MEMORY_PROTECTION == STD_ON))
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* @Trace: SafeOs_SUD_API_00701 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  #if ((OS_ISR_TP_EB == STD_ON) || (OS_APPLICATION == STD_ON) || \
       (OS_MEMORY_PROTECTION == STD_ON))
  /* @Trace: SafeOs_SUD_API_00702 */
  /* Take the Static task into local pointer */
  LpStaticTask = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];
  #endif

  #if (OS_ISR_TP_EB == STD_ON)
  /* Check if timing protection is configured for currently running object */
  if (LpStaticTask->pStaticTimProtection != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_00703 */
    /* Continue Execution budget */
    Os_ContinueTimingProtection(LpStaticTask);
  }
  #endif /* End of if (OS_ISR_TP_EB == STD_ON) */

  /* Update the currently running Application */
  #if(OS_APPLICATION == STD_ON)
  /* @Trace: SafeOs_SUD_API_00704 */
  Os_GddAppId[OS_CORE_ID] = LpStaticTask->ddAppId;
  #endif

  #if (OS_MEMORY_PROTECTION == STD_ON)
  #if (OS_APP_MEMBLK_CNT != OS_ZERO)
  /* Check if Application is non -trusted */
  #if (OS_TRUSTED_START_INDX != OS_ZERO)
  if (Os_GddAppId[OS_CORE_ID] < (ApplicationType)Os_Trusted_Start_Indx)
  {
    /* Invoke function Os_HandleMemoryBlock */
    /* @Trace: SafeOs_SUD_API_00706 */
    Os_HandleMemoryBlock(LpStaticTask);
  }
  #endif
  #endif /* End of if (OS_APP_MEMBLK_CNT != OS_ZERO) */
  #endif /* End of if (OS_MEMORY_PROTECTION == STD_ON) */
} /* End of Os_RunISR(void) */
#endif /* End of #if((OS_TASK == STD_ON) && (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)) */

/*******************************************************************************
** Function Name        : Os_InitOS                                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called from StartOS().It autostarts**
**                        task, alarm or scheduletable if configured.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
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
**                        Os_GaaApplMode, Os_GaaAlarm, Os_GddAppMode          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_ActivateTaskService(), Os_InsertAlarm()          **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80006 */
#if ((OS_TASK == STD_ON) || (OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON))
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
static FUNC(void, OS_CODE) Os_InitOS(void)
{
  #if (OS_ALARM == STD_ON)
  P2CONST(Tdd_Os_AutoStartAlarm, AUTOMATIC, OS_CONST) LpAutoStartAlarm;
  #endif
  #if (OS_TASK == STD_ON)
  P2CONST(Tdd_Os_AutoStartTask, AUTOMATIC, OS_CONST) LpAutoStartTask;
  #endif
  #if (OS_SCHEDTABLE == STD_ON)
  P2CONST(Tdd_Os_AutoStartSchedTable, AUTOMATIC, OS_CONST)
  LpAutoStartSchedTable;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  #endif
  uint16_least LusCount;
  AppModeType LddMode;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_21301 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Save Application mode into local variable */
  LddMode = Os_GddAppMode;

  /* polyspace-begin DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "The index of array is checked before used" */
  /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "The index of array is checked before used" */
  #if (OS_TASK == STD_ON)
  /* Take  Autostart task count in local variable */
  LusCount = Os_GaaApplMode[LddMode].ddNoOfAutoStartTask;

  /* Check if count is zero */
  /* polyspace<RTE: UNR : Not a defect : No Action Planned > Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  /* polyspace +2 MISRA-C3:14.3,2.1 [Justified:Medium] "Value changes based on OS_GaaApplMode member No of AutostastTask. This is not if-condition always evaluates to false*/
  /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:low] "Value changes based on OS_GaaApplMode member No of AutostastTask. This is not if-condition always evaluates to false*/
  if (LusCount != OS_ZERO)
  {
    /* Get the pointer to first task */
    /* polyspace +1 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "Index of array is checked before used" */
    LpAutoStartTask = Os_GaaApplMode[LddMode].pAutoStartTask;

    do
    {
      #if (OS_MULTICORE == STD_ON)

      if (LpAutoStartTask->pStaticTask->ddCoreId == OS_CORE_ID)
      #endif
      {
        /* @Trace: SafeOs_SUD_API_21302 */
        /* Each AUTOSTART task is activated   */
        (void)Os_ActivateTaskService(LpAutoStartTask->pStaticTask);
      }
      /* Point to next task */
      /* polyspace +2 MISRA-C3:18.4 [Justified:Low] "Increment operator on pointer used to achieve better throughput" */
      /* @Trace: SafeOs_SUD_API_21303 */
      LpAutoStartTask++;

      /* Decrement count */
      LusCount--;
      /* Check if Autostart tasks exists */
    } while (LusCount != OS_ZERO);
  } /* End of if (LusCount != OS_ZERO) */
  /* polyspace-end DEFECT:DEAD_CODE [Not a defect:low] "Value changes based on OS_GaaApplMode member No of AutostastTask. This is not if-condition always evaluates to false*/
  #endif /* End of if (OS_TASK == STD_ON) */

  #if (OS_ALARM == STD_ON)
  /* Take  Autostart Alarm count in local variable */
  /* polyspace +1 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "The index is checked before used" */
  LusCount = Os_GaaApplMode[LddMode].ddNoOfAutoStartAlarm;

  /* Check if count is zero */
  /* polyspace +3 MISRA-C3:14.3 [Justified:Low] "This code has already been verified and no impact of this rule violation" */
  /* polyspace +2 MISRA-C3:2.1 [Justified:Low] "This code has already been verified and no impact of this rule violation" */
  /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation" */
  if (LusCount != OS_ZERO)
  {
    /* Get the pointer to first Alarm */
    LpAutoStartAlarm = Os_GaaApplMode[LddMode].pAutoStartAlarm;

    do
    {
      #if (OS_MULTICORE == STD_ON)

      if (LpAutoStartAlarm->pAlarm->ddCoreId == OS_CORE_ID)
      #endif
      {
        /* @Trace: SafeOs_SUD_API_21304 */
        /* Each AUTOSTART Alarm is activated   */
        Os_InsertAlarm(LpAutoStartAlarm->pAlarm);
        /* Note: Alarm is not made active by default because it needs to be
         *   active only for the requested Appmode. Thus make the Alarm Active
         * */
        LpAutoStartAlarm->pAlarm->ucAlarmState = OS_ALARM_ACTIVE;
      }
      /* Point to next alarm */
      /* polyspace +2 MISRA-C3:18.4 [Justified:Low] "Increment operator on pointer used to achieve better throughput" */
      /* @Trace: SafeOs_SUD_API_21305 */
      LpAutoStartAlarm++;

      /* Decrement count */
      LusCount--;
      /* Check if Autostart alarm exists */
    } while (LusCount != OS_ZERO);
  } /* End of if (LusCount != OS_ZERO) */
  /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation" */
  #endif /* End of if (OS_ALARM == STD_ON) */

  #if (OS_SCHEDTABLE == STD_ON)
  /* Take  Autostart ScheduleTable count in local variable */
  LusCount = Os_GaaApplMode[LddMode].ddNoOfAutoStartSchedTable;

  /* Check if count is zero */
  if (LusCount != OS_ZERO)
  {
    /* Get the pointer to first task */
    LpAutoStartSchedTable = Os_GaaApplMode[LddMode].pAutoStartSchedTable;

    do
    {
      /* Point to the respected alarm for the scheduleTable */
      LpAlarm =
        &Os_GaaAlarm[LpAutoStartSchedTable->pStaticSchedTable->ddAlarmIndex];
      #if (OS_MULTICORE == STD_ON)

      if (LpAlarm->ddCoreId == OS_CORE_ID)
      #endif
      {
        /* @Trace: SafeOs_SUD_API_21306 */
        /* Insert the alarm */
        Os_InsertAlarm(LpAlarm);
        /* Note: Alarm is not made active by default because it needs to be
         *   active only for the requested Appmode. Thus make the Alarm Active
         * */
        LpAlarm->ucAlarmState = SCHEDULETABLE_RUNNING;
      }
      /* @Trace: SafeOs_SUD_API_21307 */
      /* Point to next ScheduleTable */
      LpAutoStartSchedTable++;
      /* Decrement count */
      LusCount--;
      /* Check if Autostart ScheduleTable exists */
    } while (LusCount != OS_ZERO);
  } /* End of if (LusCount != OS_ZERO) */
  #endif /* End of if (OS_SCHEDTABLE == STD_ON) */
  /* polyspace-end DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "The index of array is checked before used" */
  /* polyspace-end MISRA-C3:D4.14 [Not a defect:Low] "The index of array is checked before used" */
} /* End of Os_InitOS(void) */
#endif /* End of if ((OS_TASK == STD_ON) || (OS_ALARM == STD_ON) ||
        *(OS_SCHEDTABLE == STD_ON)) */

/***************************************************************************//**
 * Function Name        : Os_Sleep
 *
 * Service ID           : NA
 *
 * Description          : This function represents the idle task
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GddCurIdleMode
 *
 *                        Function(s) invoked    :
 *                        Os_EnterIdle(),
 *                        Os_IdleEntryHook(),
 *                        Os_IdleExitHook()
 ******************************************************************************/
FUNC(void, OS_CODE) Os_Sleep(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

 /* polyspace RTE:NTL [Not a defect:Low] "Infinite loop is intended instruction for sleep." */
  while (OS_ONE)
  {
    #if (OS_PROFILING_HOOK == STD_ON)
    /* @Trace: SafeOs_SUD_API_00801 */
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Os_IdleEntryHook(OS_CORE_ID);
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    #endif

    /* Enter the idle mode */
    /* @Trace: SafeOs_SUD_API_00803 */
    /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    Os_EnterIdle(Os_GddCurIdleMode[OS_CORE_ID]);

    #if (OS_PROFILING_HOOK == STD_ON)
    /* @Trace: SafeOs_SUD_API_00804 */
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Os_IdleExitHook(OS_CORE_ID);
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    #endif
  }
} /* End of Os_Sleep(void) */

/*******************************************************************************
** Function Name        : Os_KernStartOS                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called to start the Os             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : AppModeType Mode                                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GblAppModeCheck, Os_GddAppMode, Os_GpStaticTask, **
**                        Os_GpSchedWatchdog, Os_GpLinkTask, Os_GaaLinkTask,  **
**                        Os_GucActivateCore, Os_GaaStaticTask,               **
**                        Os_GaaRunningWdg, Os_GblStartOS, Os_GaaCore,        **
**                        Os_GaaStaticMemBlock, Os_GddFaultyTask,             **
**                        Os_GblOsInitialized,                                **
**                        Os_GaaStaticAppHook, Os_GaaApplication              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SetISRPriority(), StartupHook(),                 **
**                        Os_SetSyncFirst(), Os_ReleaseSpinlock(),            **
**                        Os_InitTimer(), Os_InitOS(), Os_SetSyncSecond(),    **
**                        Os_GetSpinlock(), Os_InitMessageQueue(),            **
**                        Os_InitDebugFeatures(), Os_TaskActivationHook(),    **
**                        Os_InitializeDedicatedMemBlock()                    **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11006 SRS_Os_80001 SRS_Os_80006 SRS_Os_80026 SRS_Os_80008 SRS_Os_11013 SRS_AUTRON_00012 SRS_Os_11008 SRS_Os_11009 SRS_AUTRON_00008 SRS_Os_11003 SRS_Os_80011 SRS_Os_80021 SRS_Os_80022 SRS_Os_80027 SRS_Os_00098 */
/* polyspace +2 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
/* polyspace +1 CODE-METRICS:CALLS [Not a defect:Low] "Function is called at the time starting the OS" */
FUNC(void, OS_CODE) Os_KernStartOS(AppModeType Mode)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  #if (OS_APPLICATION == STD_ON)
  ApplicationType LucAppCount;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  StatusType LblErrorMode;
  #endif
  StatusType LenStatusReturn;
  LenStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  LblErrorMode = OS_FALSE;
  #endif
  /* @Trace: SafeOs_SUD_API_21201 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check the validity of OsAppMode ID */
  OS_CHECK_APPMODE_ERROR(Mode, LenStatusReturn);
  /* Check if Os is already started on the core */
  /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  OS_CHECK_STARTOS_ERROR(LenStatusReturn);

  if (LenStatusReturn == E_OK)
  {
    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_21202 */
    /* Acquire the spinlock */
    Os_GetSpinlock(OS_SPIN_LOCK_ZERO);
    /* Increment activated core */
    Os_GucActivateCore++;
    if(Mode != DONOTCARE)
    {
      if((Os_GblAppModeCheck == OS_FALSE) || (Mode == Os_GddAppMode))
      {
        /* @Trace: SafeOs_SUD_API_21203 */
        Os_GddAppMode = Mode;
        Os_GblAppModeCheck = OS_TRUE;
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_21204 */
        LblErrorMode = OS_TRUE;
      }
    }
    /* Master Core is self-started */
    if (OS_CORE_ID == OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_21205 */
      Os_GaaCore[OS_CORE_ID].blCoreStatus = OS_TRUE;
    }
    /* Release the spinlock */
    Os_ReleaseSpinlock(OS_SPIN_LOCK_ZERO);
    #else /* End of if (OS_MULTICORE == STD_ON) */
    /* @Trace: SafeOs_SUD_API_21206 */
    /* Store the application mode */
    Os_GddAppMode = Mode;
    #endif /* End of if (OS_MULTICORE == STD_ON) */

    /* Disable the interrupts */
    OS_DISABLEINTERRUPTS();
    /*
     * Store the application mode
     * Update Os_GpLinkTask
     */
    Os_GpLinkTask[OS_CORE_ID] = &Os_GaaLinkTask[OS_CORE_ID];
    #if (OS_TIMING_PROTECTION == STD_ON)
    /* @Trace: SafeOs_SUD_API_21207 */
    /* Initialize Global watchdog */
    Os_GpSchedWatchdog[OS_CORE_ID] = NULL_PTR;
    /* Initialize state and the array index of the budget monitoring watchdog */
    Os_GaaRunningWdg[OS_CORE_ID].ulTPArrayIndx = OS_INVALID_VALUE;
    Os_GaaRunningWdg[OS_CORE_ID].ddWdgType = OS_WDG_DISABLED;
    /* Initialize faulty task id for timing budget violation in kernel mode */
    Os_GddFaultyTask[OS_CORE_ID] = INVALID_TASK;
    #endif /* End of if (OS_TIMING_PROTECTION == STD_ON) */

    #if (OS_SAFETY_KERNEL != STD_ON)
    #if (OS_MEMORY_PROTECTION == STD_ON)
    /* initialize dedicated memory block*/
    Os_InitializeDedicatedMemBlock();
    #endif
    #endif  /* End of #if (OS_SAFETY_KERNEL != STD_ON) */

    /* Init default idle mode */
    Os_GddCurIdleMode[OS_CORE_ID] = IDLE_NO_HALT;

    /* Make the sleep Tasks as OS_READY_AND_NEW */
    LpStaticTask = &Os_GaaStaticTask[OS_CORE_ID];
    LpStaticTask->pTask->ddState = OS_READY_AND_NEW;
    #if (OS_PROFILING_HOOK == STD_ON)
    /* @Trace: SafeOs_SUD_API_21210 */
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Os_TaskActivationHook(OS_CORE_ID, LpStaticTask->ddTaskId);
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    #endif

    /* NOTE: OS Init must be finished before the first SYNC point. */
    /* InitOs function is called to initialize AUTOSTART objects */
    #if ((OS_TASK == STD_ON) || (OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON))
    Os_InitOS();
    #endif

    /* Set the status that OS in initialized globally */
    Os_GblOsInitialized[OS_CORE_ID] = OS_TRUE;

    /* Update the GpStaticTask with the task to start */
    Os_GpStaticTask[OS_CORE_ID] =
        &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];

    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_21211 */
    /* Init multi-core message queue */
    Os_InitMessageQueue();

    /* Initialize the port */
    OS_PORTINITIALIZE();

    /* Call function to set first synchronization */
    Os_SetSyncFirst();

    if((Os_GblAppModeCheck == OS_TRUE) && (LblErrorMode == FALSE))
    #else
    /* Initialize the port */
    OS_PORTINITIALIZE();
    #endif /* End of if (OS_MULTICORE == STD_ON) */
    {
      /* Initialize the state of all OS-Applications to APPLICATION_ACCESSIBLE */
      #if (OS_APPLICATION == STD_ON)
      #if (OS_MULTICORE == STD_ON)
      if(OS_CORE_ID == OS_CORE_ID_MASTER)
      #endif
      {
        /* @Trace: SafeOs_SUD_API_21213 */
        LucAppCount = Os_Application_Count;
        do
        {
          /* Decrement the loop count */
          LucAppCount--;
          Os_GaaApplication[LucAppCount].ddState = APPLICATION_ACCESSIBLE;
        }while(LucAppCount != OS_ZERO);
      }
      #endif

      /* Set Global Variable to notice that Os was started on current core */
      Os_GblStartOs[OS_CORE_ID] = OS_TRUE;

      #if (OS_STARTUP_HOOK == STD_ON)
      /* @Trace: SafeOs_SUD_API_21214 */
      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /* Process StartupHook */
      OS_PROCESS_STARTUPHOOK();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      #endif
      #if (OS_APP_STARTUP_HOOK == STD_ON)
      LucAppCount = Os_Application_Count;

      /* Run through the while loop for all the applications */
      do
      {
        /* Decrement the loop count */
        LucAppCount--;

        /* Check if startupHook is configured for the application */
        /* polyspace +1 RTE:UNR [Not a defect:Low] "Check NULL_PTR is done" */
        if (Os_GaaStaticAppHook[LucAppCount].pStartupHook != NULL_PTR)
        {
          /* @Trace: SafeOs_SUD_API_21215 */
          #if(OS_MULTICORE == STD_ON)
          if (Os_GaaStaticAppHook[LucAppCount].ddCoreID == OS_CORE_ID)
          #endif
          {
            /* @Trace: SafeOs_SUD_API_21216 */
            /* Make a call Application specific startuphook */
            /* Process Application StartupHook */
            /* polyspace-begin RTE:UNR [Not a defect:Low] "Check NULL_PTR is done" */
            OS_PROCESS_APP_STARTUPHOOK(((ApplicationType)LucAppCount),
                                (Os_GaaStaticAppHook[LucAppCount].pStartupHook));
            /* polyspace-end RTE:UNR [Not a defect:Low] "Check NULL_PTR is done" */
          }
        }
      } while (LucAppCount != OS_ZERO);

      #endif /* End of if (OS_APP_STARTUP_HOOK == STD_ON) */

      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_21217 */
      /* Call function to set first synchronization */
      Os_SetSyncSecond();
      #endif

      OS_STARTUPCONTEXT();
    }
    #if (OS_MULTICORE == STD_ON)
    else
    {
      /* @Trace: SafeOs_SUD_API_21219 */
      OS_INFINITELOOP();
    } /* End of else */
    #endif /* End of if (OS_MULTICORE == STD_ON) */
  }
} /* End of Os_KernStartOS(AppModeType Mode) */

/*******************************************************************************
** Function Name        : Os_KernGetActiveApplicationMode                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the active application mode   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : AppModeType                                         **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GddAppMode                                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(AppModeType, OS_CODE) Os_KernGetActiveApplicationMode(void)
{
  StatusType LenStatusReturn;
  AppModeType LddReturnVal;

  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call from call level */
  OS_CHECK_E_OS_CALLEVEL(GETACTIVEAPPLICATIONMODE, LenStatusReturn);
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_00901 */
    LddReturnVal = Os_GddAppMode;
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_00902 */
    LddReturnVal = OS_INVALID_VALUE;
  }
  return (LddReturnVal);
} /* End of GetActiveApplicationMode(void) */

/*******************************************************************************
** Function Name        : Os_KillTask                                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service Terminates the specified Task.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : LpStaticTask                                        **
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
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StopExecutionBudget(),                           **
**                        Os_ReleaseInternalResource()                        **
*******************************************************************************/
#if ((OS_PROTECTION_HOOK == STD_ON) || (OS_APPLICATION == STD_ON))
FUNC(void, OS_CODE) Os_KillTask(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
                                                         OS_CONST) LpStaticTask)
{
  #if (OS_TASK_TP_EB == STD_ON)
  /* @Trace: SafeOs_SUD_API_18501 */
  /* Invoke StopExecutionBudget */
  Os_StopExecutionBudget(LpStaticTask);
  #endif

  #if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO)
  /* @Trace: SafeOs_SUD_API_18502 */
  /* Release internal resource */
  Os_ReleaseInternalResource(LpStaticTask);
  #endif

  /* reset the activate count */
  LpStaticTask->pTask->ulActivateCount = OS_ZERO;
  /* Change the state to SUSPENDED */
  LpStaticTask->pTask->ddState = SUSPENDED;
  #if (OS_EVENT == STD_ON)

  /* If the object is an EXTENDED task, initialize the events */
  if (LpStaticTask->usType == OS_TASK_EXTENDED)
  {
    /* @Trace: SafeOs_SUD_API_18503 */
    /* Set ddEventSet to ZERO */
    LpStaticTask->pTask->ddEventSet = OS_ZERO;
    /* Set ddEventWait to ZERO */
    LpStaticTask->pTask->ddEventWait = OS_ZERO;
  } /* End of if (LpStaticTask->ucType == OS_TASK_EXTENDED) */
  #endif /* End of if (OS_EVENT == STD_ON) */
  /* @Trace: SafeOs_SUD_API_18504 */
  OS_REMOVECONTEXT(LpStaticTask);
} /* End of Os_KillTask(P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST)
   *LpStaticTask) */
#endif /* End of if (OS_PROTECTION_HOOk == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KillIsr                                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to kill the ISR that has caused**
**                        the timing fault                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : LpStaticTask                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOs() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GucNestingCAT2ISR, Os_GusCallevelCheck           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StopExecutionBudget(),                           **
*******************************************************************************/
#if ((OS_PROTECTION_HOOK == STD_ON) || (OS_APPLICATION == STD_ON))
#if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
FUNC(void, OS_CODE) Os_KillIsr(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
                                                         OS_CONST) LpStaticTask)
{
  #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  OS_GET_CORE_ID(OS_CORE_ID);

  #if (OS_ISR_TP_EB == STD_ON)
  /* @Trace: SafeOs_SUD_API_18602 */
  /* Invoke StopExecutionBudget */
  Os_StopExecutionBudget(LpStaticTask);
  #endif
  /* Decrement the CAT2 ISR nesting count */
  /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  if (Os_GucNestingCAT2ISR[OS_CORE_ID] > 0)
  {
    /* @Trace: SafeOs_SUD_API_18603 */
    Os_GucNestingCAT2ISR[OS_CORE_ID]--;
    if(Os_GucNestingCAT2ISR[OS_CORE_ID] == OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_18604 */
      Os_GusCallevelCheck[OS_CORE_ID] &= (uint16)((uint16)0xFFFF & ~(uint16)OS_CONTEXT_CAT2ISR);
    }
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_18605 */
    /* TODO: OS Panic */
  }

  #if (OS_SCALABILITY_CLASS >= OS_SC3)
  (void)Os_EnableInterruptSource(LpStaticTask->ddTaskId, OS_TRUE);
  #endif

  OS_REMOVECONTEXT(LpStaticTask);
  #endif/* End of if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO) */
} /* End of Os_KillIsr(P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST)
   *LpStaticTask) */
#endif /* End of if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO) */
#endif /* End of if (OS_PROTECTION_HOOk == STD_ON) */

/*******************************************************************************
** Function Name        : Os_ProtectionHookService                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is used to take the action for the     **
**                        error occured due to not following the              **
**                        TimingProtection.                                   **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Fatalerror                                          **
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
**                        Os_GddAppId, Os_GddISR2Lock, Os_GddISRLock          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SyncShutdownOSService(),                         **
**                        Os_RunTask(),                                       **
**                        Os_KillTaskOrISR(),                                 **
**                        Os_SetTaskStackPointer()                            **
**                        Os_DoTerminateApplication()                         **
*******************************************************************************/
/* @Trace: SRS_Os_11006 SRS_Os_11014 SRS_Os_11013 SRS_Os_11012 */
#if (OS_PROTECTION_HOOK == STD_ON)
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "Value of LenResult depends on User-Configuration in Hook" */
/* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Value of LenResult depends on User-Configuration in Hook" */
/* polyspace +1 MISRA-C3:17.2 [Justified:Low] "Os_ActivateTaskService-> Os_StartTimeFrame #if (OS_TASK_TP_TF == STD_ON) -> Os_ProtectionHookService -> Os_DoTerminateApplication -> #if (OS_RESTART_TASK == STD_ON) Os_ActivateTaskService" */
FUNC(StatusType, OS_CODE) Os_ProtectionHookService(StatusType Fatalerror)
{
  ProtectionReturnType LenResult;
  StatusType LenStatusValue;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_20201 */
  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* Init the value of LenStatusValue variable */
  LenStatusValue = E_OK;

  /* Process ProtectionHook */
  /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  OS_PROCESS_PROTECTIONHOOK(LenResult, Fatalerror);

  #if (OS_TIMING_PROTECTION == STD_ON)
  /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "The parameter update value which depends on configuration" */
  /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "The parameter update value which depends on configuration" */
  if ((Fatalerror == E_OS_PROTECTION_ARRIVAL) && (LenResult != PRO_IGNORE))
  /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "The parameter update value which depends on configuration" */
  /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "The parameter update value which depends on configuration" */
  {
    /* @Trace: SafeOs_SUD_API_20202 */
    LenResult = PRO_SHUTDOWN;
  }
  #endif
  switch (LenResult)
  {
    case PRO_TERMINATETASKISR:
      /* Current Task Not RUNNING -> Os_GpStaticTask is not faulty Task */
      if ((Os_GpStaticTask[OS_CORE_ID]->usType != OS_ISR2) &&
          (Os_GpStaticTask[OS_CORE_ID]->pTask->ddState != RUNNING))
      {
        #if (OS_SCALABILITY_CLASS >= OS_SC3)
        if (Os_GddAppId[OS_CORE_ID] != (ApplicationType)INVALID_OSAPPLICATION)
        {
          /* @Trace: SafeOs_SUD_API_20203 */
          /* Invoke Os_DoTerminateApplication with NO_RESTART */
          LenStatusValue =
                 Os_DoTerminateApplication(Os_GddAppId[OS_CORE_ID], NO_RESTART);
        }
        else
        #endif
        {
          /*
           * NTC.9 : The called function ShutdownOS (in the current context)
           *         either contains an error or does not terminate
           * Description: As per requirement OS425, ShutdownOS() shall
           *         enter an endless loop, thus this warning is encountered.
           */
          /* @Trace: SafeOs_SUD_API_20204 */
          Os_SyncShutdownOSService(Fatalerror);
        }
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_20205 */
        LenStatusValue = Os_KillTaskOrISR();
      }
      break;

    #if (OS_TIMING_PROTECTION == STD_ON)
    case PRO_IGNORE:
      /*
       * NTC.9 : The called function ShutdownOS (in the current context)
       *         either contains an error or does not terminate
       * Description: As per requirement OS425, ShutdownOS() shall
       *              enter an endless loop, thus this warning is encountered.
       */
      if (Fatalerror != E_OS_PROTECTION_ARRIVAL)
      {
        /* @Trace: SafeOs_SUD_API_20206 */
        Os_SyncShutdownOSService(Fatalerror);
      }
      break;
    #endif
    case PRO_SHUTDOWN:
      /*
       * NTC.9 : The called function ShutdownOS (in the current context)
       *         either contains an error or does not terminate
       * Description: As per requirement OS425, ShutdownOS() shall
       *              enter an endless loop, thus this warning is encountered.
       */
      /* @Trace: SafeOs_SUD_API_20207 */
      Os_SyncShutdownOSService(Fatalerror);
      break;

    #if (OS_SCALABILITY_CLASS >= OS_SC3)
    case PRO_TERMINATEAPPL:
    /* @Trace: SafeOs_SUD_API_20208 */
      /* Invoke Os_DoTerminateApplication with NO_RESTART */
      LenStatusValue =
                 Os_DoTerminateApplication(Os_GddAppId[OS_CORE_ID], NO_RESTART);
      break;

    case PRO_TERMINATEAPPL_RESTART:
    /* @Trace: SafeOs_SUD_API_20209 */
      /* Invoke Os_DoTerminateApplication with RESTART */
      LenStatusValue =
                    Os_DoTerminateApplication(Os_GddAppId[OS_CORE_ID], RESTART);
      break;
    #endif /* End of if (OS_SCALABILITY_CLASS >= OS_SC3) */

    default:
      /* Default: Go to Shutdown :
       *
       * NTC.9 : The called function ShutdownOS (in the current context)
       *         either contains an error or does not terminate
       * Description: As per requirement OS425, ShutdownOS() shall
       *              enter an endless loop, thus this warning is encountered.
       */
      /* @Trace: SafeOs_SUD_API_20210 */
      Os_SyncShutdownOSService(Fatalerror);
      break;
  } /* End of switch (LenResult) */

  /* Reset Interrupt processing services. */
  #if(OS_ISR_COUNT > OS_ZERO)
  /* @Trace: SafeOs_SUD_API_20211 */
  Os_GblISRLock[OS_CORE_ID] = OS_FALSE;
  Os_GddISRLock[OS_CORE_ID] = OS_ZERO;
  #if (OS_CAT2_ISR_COUNT >= OS_ONE)
  /* @Trace: SafeOs_SUD_API_20212 */
  Os_GddISR2Lock[OS_CORE_ID] = OS_ZERO;
  #endif
  #endif

  /* NOTE: Os_KillTaskOrISR() and Os_DoTerminateApplication()
   *       demands context switching */
  /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "The parameter update value which depends on configuration" */
  /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "The parameter update value which depends on configuration" */
  if (LenStatusValue >= OS_E_OK_AND_LOAD)
  /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "The parameter update value which depends on configuration" */
  /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "The parameter update value which depends on configuration" */  
  {
    /* @Trace: SafeOs_SUD_API_20213 */
    /* Set TASK or CAT2 ISR's stack base address */
    Os_SetTaskStackPointer();
    #if (OS_TASK == STD_ON)
    Os_RunTask();
    #endif /*OS_TASK == STD_ON*/
  }
  /* @Trace: SafeOs_SUD_API_20214 */
  return (LenStatusValue);
} /* End of Os_ProtectionHookService(StatusType Fatalerror) */
/* polyspace-end CERT-C:MSC12-C */
/* polyspace-end DEFECT:DEAD_CODE */
#endif /* End of if (OS_PROTECTION_HOOK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernControlIdle                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called to to select the idle mode  **
**                       action which is performed during idle time of the OS **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : CoreID                                              **
**                        IdleMode                                            **
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
**                        Os_GddCurIdleMode                                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80023 */
FUNC(StatusType, OS_CODE) Os_KernControlIdle(CoreIDType CoreID, IdleModeType IdleMode)
{
  #if (OS_ERROR_HOOK == STD_ON)
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get Core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  #endif
  StatusType LenStatusReturn;
  /* Init the value of LenStatusReturn variable */
  LenStatusReturn = E_OK;

  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(CONTROLIDLE, LenStatusReturn);
  /* Check the IdleMode is invalid */
  OS_CHECK_IDLE_MODE(CoreID, IdleMode, LenStatusReturn);
  /* Checking whether error or not */
  #if (OS_STATUS == EXTENDED)
  if(LenStatusReturn == E_OK)
  #endif
  {
    /* @Trace: SafeOs_SUD_API_01501 */
    /* Checking current and new Idle Mode */
    if(Os_GddCurIdleMode[CoreID] != IdleMode)
    {
      /* @Trace: SafeOs_SUD_API_01502 */
      Os_GddCurIdleMode[CoreID] = IdleMode;
    }
  }
  #if (OS_STATUS == EXTENDED)
  else
  {
    /* @Trace: SafeOs_SUD_API_01503 */
    /* Store service Id of ControlIdle */
    /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    OS_STORE_SERVICE(OSServiceId_ControlIdle);
    /* Store the parameter 1 - CoreID */
    OS_STORE_PARAM1_COREID(CoreID);
    /* Store the parameter 2 - IdleMode */
    OS_STORE_PARAM2_IDLEMODE(IdleMode);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif

  /* Return the Status */
  return LenStatusReturn;
}

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace-end RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually." */
/* polyspace-end RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace:end<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually*/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
