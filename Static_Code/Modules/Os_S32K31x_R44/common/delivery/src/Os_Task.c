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
**  SRC-MODULE: Os_Task.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Task functionality                               **
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
** 1.5.0     13-Sep-2023   HJ.Kim           Jira CP44-2965                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
**                                          Jira CP44-1988                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.3     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
**                                          R44-Redmine #12870                **
** 1.0.2     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Add comment for Misra-C 7.2       **
** 1.0.1     17-Jul-2020   DanhDC1          R44-Redmine #14601 Change the     **
**                                          type of internal                  **
**                                          variable for the ActivateTaskVount**
**                                          and Os_GaaLinkIndex variable      **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually." */
/* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Array index inside bounds and code is verified manually" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Array index inside bounds and code is verified manually" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os Ram header file */
#include "Os_Kernel.h"            /* Os Kernel header file */
#include "Os_Error.h"             /* Os Error header file */
#include "Os_Task.h"              /* Os Task header file */
/* @Trace: SRS_BSW_00410 */
#if (OS_RESOURCE == STD_ON)
#include "Os_Resource.h"          /* Os Task header file */
#endif
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_TimingProtection.h"   /* Os TimerProtection header file */
#endif
#if (OS_APPLICATION == STD_ON)
#include "Os_Application.h"       /* Os Application header file */
#endif
#if (OS_MULTICORE == STD_ON)
#include "Os_MulticoreMessage.h"
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

/* polyspace-begin MISRA-C3:8.5 [Justified:Low] "To avoid cross reference, external function needed." */

#if (OS_TASK == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernActivateTask(TaskType TaskID);
FUNC(void, OS_CODE) Os_KernActivateTaskAsyn(TaskType TaskID);
FUNC(StatusType, OS_CODE) Os_KernTerminateTask(void);
FUNC(StatusType, OS_CODE) Os_KernChainTask(TaskType TaskID);
static FUNC(StatusType, OS_CODE) Os_ChainTaskError(TaskType TaskID);
FUNC(StatusType, OS_CODE) Os_KernGetTaskID(TaskRefType TaskID);
FUNC(StatusType, OS_CODE) Os_KernGetTaskState(TaskType TaskID, TaskStateRefType State);
static FUNC(StatusType, OS_CODE) Os_GetTaskID(TaskRefType TaskID);
FUNC(void, OS_CODE) Os_KernErrorTerminateTask(void);
#endif

/* polyspace-end MISRA-C3:8.5 [Justified:Low] "To avoid cross reference, external function is needed." */

/*******************************************************************************
** Function Name        : Os_DoActivateTask                                   **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This Service transfers the TaskID from suspended    **
**                        state into the ready state                          **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : LpStaticTask, LblRemoteCall                         **
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
**                        Os_GpLinkTask, Os_GpStaticTask, Os_GblInterCoreInt  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StartTimeFrame(),                                **
**                        Os_ScheduleService(),                               **
**                        Os_InsertTask(),                                    **
**                        Os_TaskPreemptionHook(),                            **
**                        Os_TaskActivationHook()                             **
*******************************************************************************/
/* @Trace: SRS_Os_80005 SRS_Os_80015 SRS_Os_80016 SRS_AUTRON_00012 SRS_AUTRON_00017 */
#if (OS_TASK == STD_ON)
FUNC(StatusType, OS_CODE) Os_DoActivateTask
                                        (TaskType TaskID, boolean LblRemoteCall)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpLinkTask;
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) LpTask;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  StatusType LenStatusReturn;
  /* Intenal variable count for ActivateCount */
  uint32 LulCount;
  #if (OS_MAX_ACTIVATION_COUNT != OS_ONE)
  /* Intenal variable index of link Task */
  TaskType LulIndex;
  #endif

  LpStaticTask = &Os_GaaStaticTask[TaskID];

  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
   #if (OS_PROFILING_HOOK == STD_ON)
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  #endif

  #if (OS_SCALABILITY_CLASS > OS_SC2)

  /* Check whether the requested application is accessible */
  OS_CHECK_TASK_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn, TaskID, LblRemoteCall);
  /* Check whether status return is E_OK */
  /* polyspace<RTE: UNR : Not a defect : No Action Planned > Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  if (LenStatusReturn == E_OK)
  #else
  OS_UNUSED(LblRemoteCall);
  #endif /* End of (OS_SCALABILITY_CLASS > OS_SC2) */
  {
    /* @Trace: SafeOs_SUD_API_03201 */
    /* Get the pointer to RAM task */
    LpTask = LpStaticTask->pTask;
    #if (OS_TASK_TP_TF == STD_ON)
    /* Check if task is invoked after the expiry of time frame */
    Os_StartTimeFrame(LpStaticTask);
    #endif
    /* Get the current count into local variable */
    LulCount = LpTask->ulActivateCount;

    /* Check whether limit is exceeded */
    if (LulCount < LpStaticTask->ulMaxActivateCount)
    {
      /* @Trace: SafeOs_SUD_API_03202 */
      if (LulCount == OS_ZERO)
      {
        /* @Trace: SafeOs_SUD_API_03203 */
        #if (OS_MULTICORE == STD_ON)
        /* Take core ID into local variable */
        OS_CORE_ID = LpStaticTask->ddCoreId;
        #endif

        #if (OS_TRUSTED_FUNC_COUNT != OS_PRE_ZERO)
        /* polyspace +2 MISRA-C3:10.4 [Justified:Low] "It is used for consistency" */
        if ((IS_FREE_FROM_CALLTRUSTEDFUNC((ApplicationType)(LpStaticTask->ddAppId)) == OS_TRUE) &&
            (LpStaticTask->ucBasePriority > Os_GpLinkTask[OS_CORE_ID]->scPriority))
        #else
        /* Check if task to be activated is higher priority task */
        if (LpStaticTask->ucBasePriority > (uint8)Os_GpLinkTask[OS_CORE_ID]->scPriority)
        #endif
        {
          /* @Trace: SafeOs_SUD_API_03204*/
          #if (OS_POSTTASK_HOOK == STD_ON)
          /* Process PostTaskHook */
          /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
          OS_PROCESS_POSTTASKHOOK();
          /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
          #endif

          OS_INSERT_TASK_IN_QUEUE();
          /* Update linklist for the task */
          LpLinkTask->pLinkList = Os_GpLinkTask[OS_CORE_ID];
          /* Update Os_GpLinkTask */
          Os_GpLinkTask[OS_CORE_ID] = LpLinkTask;
          /* Call Function to Switch context of old task with new task */
          /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
          Os_GpStaticTask[OS_CORE_ID]->pTask->ddState = READY;
          #if (OS_PROFILING_HOOK == STD_ON)
          /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
          Os_TaskPreemptionHook(OS_CORE_ID, TaskID);
          /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
          #endif
          Os_ScheduleService();
          #if (OS_MULTICORE == STD_ON)
          if(Os_GblInterCoreInt[OS_CORE_ID] == OS_FALSE)
          #endif
          {
            /* @Trace: SafeOs_SUD_API_03205 */
            OS_SAVECONTEXT();
          }
        } /* End of if (LpStaticTask->ucBasePriority >
           *Os_GpLinkTask[OS_CORE_ID]->scPriority) */
        else
        {
          /* @Trace: SafeOs_SUD_API_03206 */
          /* Insert Task in Queue */
          Os_InsertTask(LpStaticTask);
        } /* End of else */
        /* Change the state to READY */
        LpTask->ddState = OS_READY_AND_NEW;
        #if (OS_PROFILING_HOOK == STD_ON)
        /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
        Os_TaskActivationHook(OS_CORE_ID, TaskID);
        /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
        #endif

        /* Increment Activation count of the task */
        LpTask->ulActivateCount++;
      } /* End of if (LulCount == OS_ZERO) */
      else
      {
        /* @Trace: SafeOs_SUD_API_03207 */
        #if (OS_PROFILING_HOOK == STD_ON)
        /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
        Os_TaskActivationHook(OS_CORE_ID, TaskID);
        /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
        #endif
        /* Increment Activation count of the task */
        LpTask->ulActivateCount++;
        /* Insert Task in Queue */
        Os_InsertTask(LpStaticTask);
      } /* End of else */
    } /* End of if (LulCount < LpStaticTask->ulMaxActivateCount) */
    else
    {
      /* @Trace: SafeOs_SUD_API_03208 */
      /* Status Return to E_OS_LIMIT */
      LenStatusReturn = E_OS_LIMIT;
    }
  } /* End of if (LenStatusReturn == E_OK) */

  /* Return the value */
  return (LenStatusReturn);
}
#endif /* End of if (OS_TASK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernActivateTask                                 **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This Service transfers the TaskID from suspended    **
**                        state into the ready state                          **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : TaskID                                              **
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
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendActivateTask(), Os_DoActivateTask()          **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11008 SRS_Os_80003 SRS_Os_80005 SRS_Os_80001 SRS_Os_80015 SRS_Os_80013 */
#if (OS_TASK == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernActivateTask(TaskType TaskID)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  StatusType LenStatusReturn;

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* @Trace: SafeOs_SUD_API_03001 */
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(ACTIVATETASK, LenStatusReturn);
  /* Check whether TaskID is greater than number of task count */
  OS_CHECK_TASK_ID_ERROR(TaskID, LenStatusReturn);
  /* Check whether the current application can access the task */
  OS_CHECK_TASK_APPLICATION_ACCESS_SELF_CORE(&LenStatusReturn, TaskID);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_03003 */
    /* Store the static task corresponding to TaskID in local pointer */
    #if (OS_MULTICORE == STD_ON)
    /* Check if new task belongs to same core */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "TaskID index is checked by macro OS_CHECK_TASK_ID_ERROR before using." */
    if (Os_GaaStaticTask[TaskID].ddCoreId != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_03004 */
      /* Call Os_SendActivateTask to schedule task on respective core */
      /* @Trace: SafeOs_SUD_API_03005 */
      LenStatusReturn = Os_SendActivateTask(TaskID);
    } /* End of if (Os_GaaStaticTask[TaskID].ddCoreId != OS_CORE_ID) */
    else
    #endif /* End of if (OS_MULTICORE == STD_ON) */
    {
      /* @Trace: SafeOs_SUD_API_03007 */
      /* Call Os_DoActivateTask and get the return value */
      LenStatusReturn = Os_DoActivateTask(TaskID, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_03008 */
    /* Store the service ID of ActivateTask */
    /* @Trace: SafeOs_SUD_API_03009 */
    OS_STORE_SERVICE(OSServiceId_ActivateTask);
    /* Store the parameter 1 - TaskID */
    OS_STORE_PARAM1_TASKID(TaskID);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
    /* End of if (LenStatusReturn != E_OK) */
  }
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* Return the value */
  return (LenStatusReturn);

} /* End of ActivateTask(TaskType TaskID) */
#endif /* End of if (OS_TASK == STD_ON) */
/*******************************************************************************
** Function Name        : Os_KernActivateTaskAsyn                             **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This Service transfers the TaskID from suspended    **
**                        state into the ready state asynchronously           **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : TaskID                                              **
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
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendAsynFunc(), Os_DoActivateTask()              **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11008 SRS_Os_80003 SRS_Os_80005 SRS_Os_80001 SRS_Os_80015 SRS_Os_80013 */
#if (OS_TASK == STD_ON)
FUNC(void, OS_CODE) Os_KernActivateTaskAsyn(TaskType TaskID)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  StatusType LenStatusReturn;

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* @Trace: SafeOs_SUD_API_55401 */
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(ACTIVATETASKASYN, LenStatusReturn);
  /* Check whether TaskID is greater than number of task count */
  OS_CHECK_TASK_ID_ERROR(TaskID, LenStatusReturn);
  /* Check whether the current application can access the task */
  OS_CHECK_TASK_APPLICATION_ACCESS_SELF_CORE(&LenStatusReturn, TaskID);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_55402 */
    /* Store the static task corresponding to TaskID in local pointer */
    #if (OS_MULTICORE == STD_ON)
    /* Check if new task belongs to same core */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "TaskID index is checked by macro OS_CHECK_TASK_ID_ERROR before using." */
    if (Os_GaaStaticTask[TaskID].ddCoreId != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_55403 */
      /* Call Os_SendAsynFunc to schedule task on respective core */
      /* @Trace: SafeOs_SUD_API_55404 */
      Os_SendAsynFunc(TaskID, OS_ZERO);
    } /* End of if (Os_GaaStaticTask[TaskID].ddCoreId != OS_CORE_ID) */
    else
    #endif /* End of if (OS_MULTICORE == STD_ON) */
    {
      /* @Trace: SafeOs_SUD_API_55405 */
      /* Call Os_DoActivateTask and get the return value */
      /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      LenStatusReturn = Os_DoActivateTask(TaskID, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_55406 */
    /* Store the service ID of ActivateTask */
    /* @Trace: SafeOs_SUD_API_55407 */
    OS_STORE_SERVICE(OSServiceId_ActivateTaskAsyn);
    /* Store the parameter 1 - TaskID */
    OS_STORE_PARAM1_TASKID(TaskID);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
    /* End of if (LenStatusReturn != E_OK) */
  }
  #else
  OS_UNUSED(LenStatusReturn);
  #endif /* End of if (OS_STATUS == EXTENDED) */
} /* End of ActivateTask(TaskType TaskID) */
#endif /* End of if (OS_TASK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernTerminateTask                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service causes the termination of the          **
**                        calling task. The calling task is transferred       **
**                        from the running state into the suspended state     **
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
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GpStaticTask                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_ScheduleService()                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11009 SRS_Os_80021 */
#if (OS_TASK == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernTerminateTask(void)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(TERMINATETASK, LenStatusReturn);
  /* Check the task does not own a resource  */
  OS_CHECK_RUNNING_OWNS_REZ_ERROR(LenStatusReturn);
  /* Check the task does not own a spinlock */
  OS_CHECK_RUNNING_OWNS_SPINLOCK_ERROR(LenStatusReturn);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_02901 */
    #if (OS_POSTTASK_HOOK == STD_ON)
    /* Process PostTaskHook */
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    OS_PROCESS_POSTTASKHOOK();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    #endif

    /* Change state of the running task to DYING */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
    Os_GpStaticTask[OS_CORE_ID]->pTask->ddState = DYING;
    /* Call Function to switch context with new task */
    Os_ScheduleService();
    OS_LOADCONTEXT();
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  else
  {
    /* @Trace: SafeOs_SUD_API_02902 */
    /* Store service ID of TerminateTask */
    OS_STORE_SERVICE(OSServiceId_TerminateTask);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif /* End of if (OS_STATUS == EXTENDED) */

  /* Return the value */
  return (LenStatusReturn);
} /* End of TerminateTask(void) */
#endif /* End of if (OS_TASK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernChainTask                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service causes the termination of the          **
**                        calling task. After termination of the calling      **
**                        task a succeeding task <TaskID> is activated.       **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : TaskType TaskID                                     **
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
**                        Os_GpStaticTask, Os_GaaStaticTask, Os_GpLinkTask    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_ChainTaskError(),                                **
**                        Os_SendActivateTask(),                              **
**                        Os_StartTimeFrame(),                                **
**                        Os_ScheduleFromChain(),                             **
**                        Os_InsertTask(),                                    **
**                        Os_ScheduleService(),                               **
**                        Os_TaskActivationHook()                             **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80001 SRS_Os_80015 SRS_Os_80021 SRS_AUTRON_00012 */
#if (OS_TASK == STD_ON)
/* polyspace +1 CODE-METRICS:CALLS [Not a defect:Low] "Function terminates the calling task and activates it again" */
FUNC(StatusType, OS_CODE) Os_KernChainTask(TaskType TaskID)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) LpTask;
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Intenal variable count for ActivateCount */
  uint32 LulCount;

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Check for call from hook*/
  LenStatusReturn = Os_ChainTaskError(TaskID);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_03101 */
    /* Store the static task corresponding to TaskID in local pointer */
    LpStaticTask = &Os_GaaStaticTask[TaskID];
    #if (OS_MULTICORE == STD_ON)
    /* Check if new task belongs to same core */
    if (LpStaticTask->ddCoreId != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_03102 */
      /* Call Os_SendActivateTask to schedule task on respective core */
      LenStatusReturn = Os_SendActivateTask(TaskID);
      /* Check whether status return is E_OK */
      if (LenStatusReturn == E_OK)
      {
        /* @Trace: SafeOs_SUD_API_03103 */
        #if (OS_POSTTASK_HOOK == STD_ON)
        /* Process PostTaskHook */
        OS_PROCESS_POSTTASKHOOK();
        #endif
        /* set LenStatusReturn to OS_E_OK_AND_SCHEDULE */
        LenStatusReturn = OS_E_OK_AND_SCHEDULE;
      }
    } /* End of if (LpStaticTask->ddCoreId != OS_CORE_ID) */
    else
    #endif /* End of if (OS_MULTICORE == STD_ON) */
    {
      /* @Trace: SafeOs_SUD_API_03104 */
      #if (OS_SCALABILITY_CLASS > OS_SC2)
      /* Check whether the current application can access the task */
      OS_CHECK_TASK_APPLICATION_ACCESS_SELF_CORE(&LenStatusReturn, TaskID);
      /* Check whether the requested application is accessible */
      /* polyspace +1 MISRA-C3:14.3 [Justified:Low] "The reason of result invariant is that the project is single core" */
      OS_CHECK_TASK_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn, TaskID, \
                                                                      OS_FALSE);

      /* Check whether status return is E_OK */
      /* polyspace<RTE: UNR : Not a defect : No Action Planned > Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
      if (LenStatusReturn == E_OK)
      #endif /* End of (OS_SCALABILITY_CLASS > OS_SC2) */
      {
        /* @Trace: SafeOs_SUD_API_03105 */
        #if (OS_TASK_TP_TF == STD_ON)
        /* Check if task is invoked after the expiry of time frame */
        Os_StartTimeFrame(LpStaticTask);
        #endif

        /*Check whether the activated task and the running task are the same*/
        if (LpStaticTask == Os_GpStaticTask[OS_CORE_ID])
        {
          /* @Trace: SafeOs_SUD_API_03106 */
          /* Invoke schedulefromChain to schedule the same task */
          Os_ScheduleFromChain();
          /* Load the context of the new task */
          OS_RELOADCONTEXT();
        } /* End of if (LpStaticTask == Os_GpStaticTask[OS_CORE_ID]) */
        else
        {
          /* @Trace: SafeOs_SUD_API_03107 */
          /* Get the pointer to RAM task */
          LpTask = LpStaticTask->pTask;
          /* Get the current count into local variable */
          LulCount = LpTask->ulActivateCount;
          /* Check whether limit is exceeded */
          if (LulCount < LpStaticTask->ulMaxActivateCount)
          {
            /* @Trace: SafeOs_SUD_API_03108 */
            #if (OS_POSTTASK_HOOK == STD_ON)
            /* Process PostTaskHook */
            /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
            OS_PROCESS_POSTTASKHOOK();
            /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
            #endif
            /* Check if task is activated for the first time */
            if (LulCount == OS_ZERO)
            {
              /* @Trace: SafeOs_SUD_API_03109 */
              /* Change the state to READY */
              LpTask->ddState = OS_READY_AND_NEW;
            }
            #if (OS_PROFILING_HOOK == STD_ON)
            /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
            Os_TaskActivationHook(OS_CORE_ID, TaskID);
            /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
            #endif
            /* Increment Activation count of the task */
            LpTask->ulActivateCount++;
            /* Insert Task in Queue */
            Os_InsertTask(LpStaticTask);
            /* set LenStatusReturn to OS_E_OK_AND_SCHEDULE */
            LenStatusReturn = OS_E_OK_AND_SCHEDULE;
          } /* End of if (LulCount < LpStaticTask->ulMaxActivateCount) */
          else
          {
            /* @Trace: SafeOs_SUD_API_03110 */
            /* Set status to E_OS_LIMIT */
            LenStatusReturn = E_OS_LIMIT;
          }
        } /* End of else */
      } /* End of if (LenStatusReturn == E_OK) */
    }
  }

  /* Check whether status return is E_OK */
  if (LenStatusReturn == OS_E_OK_AND_SCHEDULE)
  {
    /* @Trace: SafeOs_SUD_API_03111 */
    /* Set the return status value to "E_OK" */
    LenStatusReturn = E_OK;

    /* the object that is currently running is put in the Dying State */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
    Os_GpStaticTask[OS_CORE_ID]->pTask->ddState = DYING;

    /* Call Function to switch context with new task */
    Os_ScheduleService();
    OS_LOADCONTEXT();
  }

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_03112 */
    /* Store the service ID of ChainTask */
    OS_STORE_SERVICE(OSServiceId_ChainTask);
    /* Store the parameter 1 - TaskID */
    OS_STORE_PARAM1_TASKID(TaskID);
    /* Call Error Hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  }
  #endif /* End of if (OS_STATUS == EXTENDED) */

  return (LenStatusReturn);
} /* End of ChainTask(TaskType TaskID) */
#endif /* End of if (OS_TASK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_ChainTaskError                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function provides the error check of ChainTask **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : TaskType TaskID                                     **
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
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/\
/* @Trace: SRS_Os_11009 */
#if (OS_TASK == STD_ON)
/* polyspace +2 MISRA-C3:2.7 [Not a defect:Low] "The parameter get task ID and check validity of ID task" */
/* polyspace +1 DEFECT:UNUSED_PARAMETER [Not a defect:Low] "The parameter get task ID and check validity of ID task" */
static FUNC(StatusType, OS_CODE) Os_ChainTaskError(TaskType TaskID)
{
  StatusType LenStatusReturn;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* @Trace: SafeOs_SUD_API_02601 */
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(CHAINTASK, LenStatusReturn);
  #if (OS_STATUS == EXTENDED)
  /* Check whether TaskID is greater than number of task count */
  OS_CHECK_TASK_ID_ERROR(TaskID, LenStatusReturn);
  #else
  OS_UNUSED(TaskID);
  #endif /* end of #if (OS_STATUS == EXTENDED) */
  /* Check whether call is made at the task level */
  OS_CHECK_TASK_CALL_LEVEL_ERROR(LenStatusReturn);
  /* Check the task does not own a resource  */
  OS_CHECK_RUNNING_OWNS_REZ_ERROR(LenStatusReturn);
  /* Check the task does not own a spinlock */
  OS_CHECK_RUNNING_OWNS_SPINLOCK_ERROR(LenStatusReturn);

  return(LenStatusReturn);
}
#endif /* End of if (OS_TASK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernGetTaskID                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to get the task id from        **
**                        the task descriptor.                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : TaskRefType TaskID                                  **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GpStaticTask                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80023  */
#if (OS_TASK == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernGetTaskID(TaskRefType TaskID)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to E_OK */
  LenStatusReturn = E_OK;

  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(GETTASKID, LenStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(TaskID, LenStatusReturn);

  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_02701 */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "TaskID have been checked before using" */
    /* Get the value of Current Running Task */
    *TaskID = Os_GpStaticTask[OS_CORE_ID]->ddTaskId;

    /* Port Specific Code to check if TaskID needs to be updated */
    LenStatusReturn = OS_PROCURE_TASK_ID(TaskID);
  } /* End of if (LenStatusReturn == E_OK) */

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_02702 */
    /* Store service ID of GetTaskID */
    /* Store the service ID of GetTaskID */
    OS_STORE_SERVICE(OSServiceId_GetTaskID);
    /* Store the parameter 1 - TaskID */
    OS_STORE_PARAM1_TASKIDREF(TaskID);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */

  /* Return the value */
  return (LenStatusReturn);
} /* End of GetTaskID(TaskRefType TaskID) */
#endif /* End of if (OS_TASK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernGetTaskState                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to get the taskstate from      **
**                        the given taskID                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : TaskType TaskID                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : TaskStateRefType State                              **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaTask, Os_GaaStaticTask                        **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendGetTaskState()                               **
*******************************************************************************/
/* @Trace: SRS_Os_00097 */
#if (OS_TASK == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernGetTaskState(TaskType TaskID,
                                                        TaskStateRefType State)
{
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) LpTask;
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(GETTASKSTATE, LenStatusReturn);
  /* Check whether TaskID is greater than number of task count */
  OS_CHECK_TASK_ID_STATE_ERROR(TaskID, LenStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(State, LenStatusReturn);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_02801 */
    #if (OS_MULTICORE == STD_ON)
    /* Store the static task corresponding to TaskID in local pointer */
    LpStaticTask = &Os_GaaStaticTask[TaskID];
    /* Check if new task belongs to same core */
    if (LpStaticTask->ddCoreId != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_02802 */
      /* Call Os_SendGetTaskState to get task state on respective core */
      LenStatusReturn = Os_SendGetTaskState(LpStaticTask, State);
    } /* End of if (LpStaticTask->ddCoreId != OS_CORE_ID) */
    else
    #endif /* End of if (OS_MULTICORE == STD_ON) */
    {
      /* @Trace: SafeOs_SUD_API_02803 */
      /* Store the task corresponding to TaskID in local pointer */
      LpTask = &Os_GaaTask[TaskID];
      /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "State have been checked before using" */
      /* Get the state of Current Task */
      *State = ((LpTask->ddState) & OS_TASK_STATUS);

      if (*State == OS_TASK_UNINITIALIZED)
      {
        /* @Trace: SafeOs_SUD_API_02804 */
        *State = SUSPENDED;
      }
    }
  } /* End of if (LenStatusReturn == E_OK) */

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_02805 */
    /* Store service Id of GetTaskState */
    OS_STORE_SERVICE(OSServiceId_GetTaskState);
    /* Store the parameter 1 - TaskID */
    OS_STORE_PARAM1_TASKID(TaskID);
    /* Store the parameter 2 - State */
    OS_STORE_PARAM2_STATE(State);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif /* End of if (OS_STATUS == EXTENDED) */

  /* Return the value */
  return (LenStatusReturn);
} /* End of GetTaskState(TaskType TaskID, TaskStateRefType State) */
#endif /* End of if (OS_TASK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_ActivateTaskService                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by OSEK/VDX ActivateTask    **
**                        and by raised alarm. if the task is in the          **
**                        SUSPENDED state, its state is changed to            **
**                        READY or RUNNING                                    **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpStaticTask                                        **
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
**                        Os_GpLinkTask                                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_InsertTask(),                                    **
**                        Os_StartTimeFrame(),                                 **
**                        Os_TaskActivationHook()                             **
*******************************************************************************/
/* @Trace: SRS_AUTRON_00012 */
#if (OS_TASK == STD_ON)
/* polyspace +2 CODE-METRIC:ap_cg_cycle [Justified:Low] "Os_ActivateTaskService is only called by Os_DoTerminateApplication with OS_RESTART_TASK equal STD_ON" */
/* polyspace +1 MISRA-C3:17.2 [Justified:Low] "Os_ActivateTaskService is only called by Os_DoTerminateApplication with OS_RESTART_TASK equal STD_ON" */
FUNC(StatusType, OS_CODE) Os_ActivateTaskService(P2CONST(
                          Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask)
{
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpLinkTask;
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) LpTask;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  StatusType LenStatusReturn;
  /* Intenal variable count for ActivateCount */
  uint32 LulCount;
  #if (OS_MAX_ACTIVATION_COUNT != OS_ONE)
  /* Intenal variable index of link Task */
  TaskType LulIndex;
  #endif

  #if (OS_PROFILING_HOOK == STD_ON)
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  #endif
  /* Status Return to E_OS_LIMIT */
  LenStatusReturn = E_OS_LIMIT;
  /* Get the pointer to RAM task */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
  LpTask = LpStaticTask->pTask;
  #if (OS_TASK_TP_TF == STD_ON)

  /* Check if task is invoked after the expiry of time frame */
  Os_StartTimeFrame(LpStaticTask);
  #endif

  /* Get the current count into local variable */
  LulCount = LpTask->ulActivateCount;

  /* Check whether limit is exceeded */
  if (LulCount < LpStaticTask->ulMaxActivateCount)
  {
    /* @Trace: SafeOs_SUD_API_02501 */
    if (LulCount == OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_02502 */
      /* Change the state to READY */
      LpTask->ddState = OS_READY_AND_NEW;
      #if (OS_PROFILING_HOOK == STD_ON)
      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
      Os_TaskActivationHook(OS_CORE_ID, LpStaticTask->ddTaskId);
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
      #endif

      /* Increment Activation count of the task */
      LpTask->ulActivateCount++;
      #if (OS_MULTICORE == STD_ON)
      /* Take core ID into local variable */
      OS_CORE_ID = LpStaticTask->ddCoreId;
      #endif

      /* Check if task to be activated is higher priority task */
      if (LpStaticTask->ucBasePriority >
                                   (uint8)Os_GpLinkTask[OS_CORE_ID]->scPriority)
      {
        /* @Trace: SafeOs_SUD_API_02503 */
        /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
        OS_INSERT_TASK_IN_QUEUE();
        /* Update linklist for the task */
        LpLinkTask->pLinkList = Os_GpLinkTask[OS_CORE_ID];
        /* Update Os_GpLinkTask */
        Os_GpLinkTask[OS_CORE_ID] = LpLinkTask;
        /* set LenStatusReturn to OS_E_OK_AND_SCHEDULE */
        LenStatusReturn = OS_E_OK_AND_SCHEDULE;
      } /* End of if (LpStaticTask->ucBasePriority >
         *Os_GpLinkTask[OS_CORE_ID]->scPriority) */
      else
      {
        /* @Trace: SafeOs_SUD_API_02504 */
        /* Insert Task in Queue */
        Os_InsertTask(LpStaticTask);
        /* Set the return status value to "E_OK" */
        LenStatusReturn = E_OK;
      } /* End of else */
    } /* End of if (LulCount == OS_ZERO) */
    else
    {
      /* @Trace: SafeOs_SUD_API_02505 */
      #if (OS_PROFILING_HOOK == STD_ON)
      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
      Os_TaskActivationHook(OS_CORE_ID, LpStaticTask->ddTaskId);
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
      #endif
      /* Increment Activation count of the task */
      LpTask->ulActivateCount++;
      /* Insert Task in Queue */
      Os_InsertTask(LpStaticTask);
      /* Set the return status value to "E_OK" */
      LenStatusReturn = E_OK;
    } /* End of else */
  } /* End of if (LulCount < LpStaticTask->ulMaxActivateCount) */
  /* @Trace: SafeOs_SUD_API_02506 */
  /* Return the value */
  return (LenStatusReturn);
} /* End of Os_ActivateTaskService(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
   *OS_CONST) LpStaticTask) */
#endif /* End of if (OS_TASK == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernErrorTerminateTask                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called in case if Task             **
**                        is not terminated                                   **
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
**                        Os_GaaTask, Os_GpLinkTask, Os_GblISRLock,           **
**                        Os_GddISRLock, Os_GddISR2Lock, Os_GaaSpinlock,      **
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_ReleaseResourceService(), Os_ResumeInterrupts()  **
**                        Os_KernTerminateTask(), Os_ReleaseSpinlock()        **
*******************************************************************************/
/* polyspace-begin DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
/* @Trace: SRS_Os_11009 SRS_Os_11013 SRS_Os_11014 */
#if (OS_TASK == STD_ON)
FUNC(void, OS_CODE) Os_KernErrorTerminateTask(void)
{
  #if(OS_ISR_COUNT > OS_ZERO)
  Os_OldLevel_T LddDefaultLevel = OS_ZERO;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  #if (OS_SPINLOCK == STD_ON)
  SpinlockIdType LusSpinlockId;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Invoke an error hook for missing terminate task */
  OS_PROCESS_ERROR(E_OS_MISSINGEND);

  #if (OS_RESOURCE == STD_ON)
  /* Release all the acquired resources */
  Os_ReleaseResourceService(&Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID]);
  #endif

  #if(OS_ISR_COUNT > OS_ZERO)
  /* Release all interrupts */
  Os_GblISRLock[OS_CORE_ID] = OS_FALSE;
  Os_GddISRLock[OS_CORE_ID] = OS_ZERO;
  #if (OS_CAT2_ISR_COUNT >= OS_ONE)
  Os_GddISR2Lock[OS_CORE_ID] = OS_ZERO;
  #endif
  Os_ResumeInterrupts(&LddDefaultLevel);
  #endif

  #if (OS_SPINLOCK == STD_ON)
  if ((Os_GaaTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID].ddSpinlock) != OS_ZERO)
  {
    do
    {
      /* @Trace: SafeOs_SUD_API_02401 */
      LusSpinlockId = Os_GaaTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID].ddSpinlock;
      Os_GaaSpinlock[LusSpinlockId].ddTaskId = OS_INVALID_VALUE;
      Os_GaaTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID].ddSpinlock = \
                              Os_GaaSpinlock[LusSpinlockId].ddNextSpinIndex;
      (void)Os_ReleaseSpinlock(LusSpinlockId);
    } while (
      Os_GaaTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID].ddSpinlock != OS_ZERO);
  } /* End of if ((Os_GaaTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID].ddSpinlock)
     *!= OS_ZERO) */
  #endif /* End of if (OS_SPINLOCK == STD_ON) */
  /* Invoke terminate task */
  /* @Trace: SafeOs_SUD_API_02402 */
  (void)Os_KernTerminateTask();
} /* End of Os_KernErrorTerminateTask(void) */
#endif /* End of if (OS_TASK == STD_ON) */

/* polyspace-end DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
/*******************************************************************************
** Function Name        : Os_GetTaskID                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to get the running object ID   **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : TaskID                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOs() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GpLinkTask, Os_GaaStaticTask                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 */
#if (OS_TASK == STD_ON)
static FUNC(StatusType, OS_CODE) Os_GetTaskID(TaskRefType TaskID)
{
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LocalList;
  const StatusType LenStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  OS_GET_CORE_ID(OS_CORE_ID);
  #endif

  /* Copy the linklist from global */
  LocalList = Os_GpLinkTask[OS_CORE_ID];
  /* Loop around the linklist */
  while (LocalList != NULL_PTR)
  {
    /* Check if Task is basic or extended and state is RUNNING */
    if (((Os_GaaStaticTask[LocalList->ddTaskID].usType == OS_TASK_BASIC) ||
         (Os_GaaStaticTask[LocalList->ddTaskID].usType == OS_TASK_EXTENDED))
        && ((Os_GaaStaticTask[LocalList->ddTaskID].pTask->ddState == RUNNING)||
            (Os_GaaStaticTask[LocalList->ddTaskID].pTask->ddState == READY_AND_INTERRUPTED)))
    {
      if(LocalList->ddTaskID == OS_CORE_ID)
      {
        /* @Trace: SafeOs_SUD_API_02301 */
        *TaskID = INVALID_TASK;
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_02302 */
        /* Update the pointer */
        *TaskID = LocalList->ddTaskID;
      }
      /* Break the loop */
      LocalList = NULL_PTR;
    } /* End of @ if ((Os_GaaStaticTask[LocalList->ddTaskID].ucType ==
       *OS_TASK_BASIC) || */
    else
    {
      /* @Trace: SafeOs_SUD_API_02303 */
      /* Go to the next node */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
      LocalList = LocalList->pLinkList;
    }
  }

  return LenStatusReturn;
} /* End of Os_GetTaskID(TaskRefType TaskID) */
#endif /* End of if (OS_TASK == STD_ON) */
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<RTE : NIV :Not a defect:Justify with annotations> variable is initialized and code is verified manually. */
/* polyspace:end<RTE : IDP :Not a defect:Justify with annotations > configured memory access index */
/* polyspace:end<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Array index inside bounds and code is verified manually" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Array index inside bounds and code is verified manually" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
