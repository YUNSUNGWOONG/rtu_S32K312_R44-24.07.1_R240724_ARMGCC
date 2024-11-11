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
**  SRC-MODULE: Os_Event.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Event functionality.                             **
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
**           26-Apr-2023   SH.Yoo           Jira CP44-2097                    **
**                                          Jira CP44-2028                    **
**                                          Jira CP44-1988                    **
** 1.3.12.0  09-Mar-2023   TanHX            Jira CP44-1335                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.2     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually." */
/* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os Ram header file */
#include "Os_Kernel.h"            /* Os Kernel header file */
#include "Os_Event.h"             /* Os Event header file */
#include "Os_Error.h"             /* Os Error header file */
#if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO)
#include "Os_Resource.h"          /* Os Resource header file */
#endif
/* @Trace: SRS_BSW_00410 */
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_TimingProtection.h"  /* Os TimerProtection header file */
#endif
#if (OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Application.h"       /* Os Application header file */
#endif
#if (OS_MULTICORE == STD_ON)
#include "Os_MulticoreMessage.h"
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

/*******************************************************************************
** Function Name        : Os_DoSetEvent                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to Set the events              **
**                        of task <TaskID> according to the event mask <Mask> **
**                        Calling SetEvent causes the task <TaskID> to be     **
**                        transferred to the ready state, if it was waiting   **
**                        for at least one of the events specified in <Mask>. **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : LpStaticTask, Mask, LblRemoteCall                   **
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
**                        Os_GpLinkTask, Os_GpStaticTask, Os_GblInterCoreInt, **
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StartTimeFrame(),                                **
**                        Os_TaskPreemptionHook(),                            **
**                        Os_ScheduleService(),                               **
**                        Os_InsertTask(),                                    **
**                        Os_TaskReleaseHook(), Os_MemSet                     **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_AUTRON_00016 SRS_AUTRON_00017 */
/* polyspace +3 MISRA-C3:8.13 [Justified:Medium] "EventMaskType is possible integer or pointer" */
#if (OS_EVENT == STD_ON)
FUNC(StatusType, OS_CODE) Os_DoSetEvent
(TaskType TaskID, EventMaskType Mask, boolean LblRemoteCall)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpCurrentLink;
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) LpTask;
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  boolean LblIsWaitingEventIncoming;
  boolean LblIsWaitingEventRefreshed;
  LblIsWaitingEventIncoming = OS_FALSE;
  LblIsWaitingEventRefreshed = OS_FALSE;

  LpStaticTask = &Os_GaaStaticTask[TaskID];
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  #if (OS_SCALABILITY_CLASS > OS_SC2)
  /* @Trace : SafeOs_SUD_API_06407 */
  /* Check whether the requested application is accessible */
  OS_CHECK_TASK_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn, \
                                         LpStaticTask->ddTaskId, LblRemoteCall);
  #else
  /* @Trace : SafeOs_SUD_API_06408 */
  OS_UNUSED(LblRemoteCall);
  #endif /* End of (OS_SCALABILITY_CLASS > OS_SC2) */
  /* Check the task is not in the SUSPENDED state */
  OS_CHECK_SUSPENDED_TASK_ERROR(LpStaticTask->ddTaskId, &LenStatusReturn);
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn == E_OK)
  #endif
  {
    /* @Trace : SafeOs_SUD_API_06401 */
    /* Get the pointer to RAM Task */
    LpTask = LpStaticTask->pTask;
    if ((LpTask->ddEventWait & Mask) != 0)
    {
      LblIsWaitingEventIncoming = OS_TRUE;
    }


    /* Cross check the event the task is waiting for and the incoming event */
    if (LblIsWaitingEventIncoming == OS_TRUE)
    {
      /* @Trace : SafeOs_SUD_API_06402 */
      /* Check whether task is in the WAITING state */
      if (LpTask->ddState == WAITING)
      {
        /* @Trace : SafeOs_SUD_API_06403 */
        #if (OS_TASK_TP_TF == STD_ON)
        /* @Trace : SafeOs_SUD_API_06409 */
        /* Check if task is invoked after the expiry of time frame */
        Os_StartTimeFrame(LpStaticTask);
        #endif
        #if (OS_MULTICORE == STD_ON)
        /* @Trace : SafeOs_SUD_API_06410 */
        /* GetCoreID into local variable */
        OS_CORE_ID = LpStaticTask->ddCoreId;
        #endif

        /* Check if task to be activated is higher priority task */
        if (LpStaticTask->ucBasePriority >
            (uint8)Os_GpLinkTask[OS_CORE_ID]->scPriority)
        {
          /* @Trace : SafeOs_SUD_API_06404 */
          #if (OS_POSTTASK_HOOK == STD_ON)
          /* @Trace : SafeOs_SUD_API_06411 */
          /* Process PostTaskHook */
          /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
          OS_PROCESS_POSTTASKHOOK();
          /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
          #endif
          /* @Trace : SafeOs_SUD_API_06412 */
          /* Take Link list into a local variable */
          LpCurrentLink = LpStaticTask->pLinkTask;
          /* Update the task link list*/
          LpCurrentLink->pLinkList = Os_GpLinkTask[OS_CORE_ID];
          /* Update Os_GpLinkTask */
          Os_GpLinkTask[OS_CORE_ID] = LpCurrentLink;
          /* Call Function to Switch context of old task with new task */
          /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
          Os_GpStaticTask[OS_CORE_ID]->pTask->ddState = READY;
          #if (OS_PROFILING_HOOK == STD_ON)
          /* @Trace : SafeOs_SUD_API_06413 */
          /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
          Os_TaskPreemptionHook(OS_CORE_ID, Os_GpStaticTask[OS_CORE_ID]->ddTaskId);
          /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
          #endif

          Os_ScheduleService();
          #if (OS_MULTICORE == STD_ON)
          if(Os_GblInterCoreInt[OS_CORE_ID] == OS_FALSE)
          #endif
          {
            /* @Trace : SafeOs_SUD_API_06405 */
            OS_SAVECONTEXT();
          }
        } /* End of if (LpStaticTask->ucBasePriority > */
        else
        {
          /* @Trace : SafeOs_SUD_API_06406 */
          /* Insert Task in Queue */
          Os_InsertTask(LpStaticTask);
        }
        /* Set the state to READY state */
        LpTask->ddState = OS_READY_AND_WAITING;
        #if (OS_PROFILING_HOOK == STD_ON)
        /* @Trace : SafeOs_SUD_API_06414 */
        /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
        Os_TaskReleaseHook(OS_CORE_ID, TaskID);
        /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
        #endif
      } /* End of if (LpTask->ddState == WAITING) */
      /* Reset the Eventwait of the running task to Zero */
      /* @Trace : SafeOs_SUD_API_06415 */
      LblIsWaitingEventRefreshed = OS_TRUE;
    } /* End of if (LblIsWaitingEventIncoming == OS_TRUE) */

    /* Merge the incoming event mask with the old one */
    if (LblIsWaitingEventRefreshed == OS_TRUE)
    {
      LpTask->ddEventWait = OS_ZERO;
    }

    LpTask->ddEventSet |= Mask;
  }

  /* Return The value */
  return (LenStatusReturn);
}
#endif /* End of if (OS_EVENT == STD_ON) */

/*******************************************************************************
** Function Name        : Os_DoGetEvent                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service returns the current state of all       **
**                        event bits of the task.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : TaskID                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : EventMaskRefType Event                              **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if (OS_EVENT == STD_ON)
FUNC(StatusType, OS_CODE) Os_DoGetEvent(TaskType TaskID, EventMaskRefType Event)
{
  StatusType LenStatusReturn;

  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check the task is not in the SUSPENDED state */
  /* polyspace<RTE: UNR : Not a defect : No Action Planned > Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  OS_CHECK_SUSPENDED_TASK_ERROR(TaskID, &LenStatusReturn);
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn == E_OK)
  #endif
  {
    /* @Trace : SafeOs_SUD_API_06301 */
    /* Get the Event of Current Task */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "ptr Event have been checked before using" */
    *Event = (&Os_GaaStaticTask[TaskID])->pTask->ddEventSet;
  }
  /* @Trace : SafeOs_SUD_API_06302 */
  return LenStatusReturn;
}
#endif /* End of if (OS_EVENT == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernSetEvent                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to Set the events              **
**                        of task <TaskID> according to the event mask <Mask> **
**                        Calling SetEvent causes the task <TaskID> to be     **
**                        transferred to the ready state, if it was waiting   **
**                        for at least one of the events specified in <Mask>. **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : TaskType TaskID, EventMaskType Mask                 **
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
**                        Os_SendSetEvent(), Os_DoSetEvent()                  **
*******************************************************************************/
/* @Trace: SRS_Os_11008 SRS_Os_00097 SRS_Os_80016 SRS_Os_80013 */
#if (OS_EVENT == STD_ON)
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
FUNC(StatusType, OS_CODE) Os_KernSetEvent(TaskType TaskID, EventMaskType Mask)
{
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
  /* @Trace : SafeOs_SUD_API_06501 */
  OS_CHECK_E_OS_CALLEVEL(SETEVENT, LenStatusReturn);

  /* Check whether TaskID is greater than number of task count */
  OS_CHECK_TASK_ID_ERROR(TaskID, LenStatusReturn);
  /* Check the task is an extended one  */
  OS_CHECK_NOT_EXTENDED_TASK_ERROR(TaskID, LenStatusReturn);
  /* Check whether the current application can access the task */
  OS_CHECK_TASK_APPLICATION_ACCESS_SELF_CORE(&LenStatusReturn, TaskID);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_06502 */
    #if (OS_MULTICORE == STD_ON)
    /* Get the pointer to static task */
    LpStaticTask = &Os_GaaStaticTask[TaskID];
    /* Check if new task belongs to same core */
    if (LpStaticTask->ddCoreId != OS_CORE_ID)
    {
      /* @Trace : SafeOs_SUD_API_06503 */
      /* Call Os_SendSetEvent to schedule task on respective core */
      LenStatusReturn = Os_SendSetEvent(LpStaticTask, Mask);
    } /* End of if (LpStaticTask->ddCoreId != OS_CORE_ID) */
    else
    #endif /* End of if (OS_MULTICORE == STD_ON) */
    {
      /* @Trace : SafeOs_SUD_API_06504 */
      /* Call Os_DoSetEvent and get the return value */
      LenStatusReturn = Os_DoSetEvent(TaskID, Mask, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_06505 */
    /* Store the service ID of SetEvent */
    OS_STORE_SERVICE(OSServiceId_SetEvent);
    /* Store the parameter 1 - TaskID */
    OS_STORE_PARAM1_TASKID(TaskID);
    /* Store the parameter 2 - Mask */
    OS_STORE_PARAM2_MASK(Mask);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */

  /* Return The value */
  return (LenStatusReturn);
} /* End of SetEvent(TaskType TaskID, EventMaskType Mask) */
#endif /* End of if (OS_EVENT == STD_ON) */
/*******************************************************************************
** Function Name        : Os_KernSetEventAsyn                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to Set the events              **
**                        of task <TaskID> according to the event mask <Mask> **
**                        Calling SetEvent causes the task <TaskID> to be     **
**                        transferred to the ready state, if it was waiting   **
**                        for at least one of the events specified in <Mask>. **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : TaskType TaskID, EventMaskType Mask                 **
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
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendAsynFunc(), Os_DoSetEvent()                  **
*******************************************************************************/
/* @Trace: SRS_Os_11008 SRS_Os_00097 SRS_Os_80016 SRS_Os_80013 */
#if (OS_EVENT == STD_ON)
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
FUNC(void, OS_CODE) Os_KernSetEventAsyn(TaskType TaskID, EventMaskType Mask)
{
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
  /* @Trace : SafeOs_SUD_API_56101 */
  OS_CHECK_E_OS_CALLEVEL(SETEVENTASYN, LenStatusReturn);
  /* Check whether TaskID is greater than number of task count */
  OS_CHECK_TASK_ID_ERROR(TaskID, LenStatusReturn);
  /* Check the task is an extended one  */
  OS_CHECK_NOT_EXTENDED_TASK_ERROR(TaskID, LenStatusReturn);
  /* Check whether the current application can access the task */
  OS_CHECK_TASK_APPLICATION_ACCESS_SELF_CORE(&LenStatusReturn, TaskID);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_56102 */
    #if (OS_MULTICORE == STD_ON)
    /* Get the pointer to static task */
    LpStaticTask = &Os_GaaStaticTask[TaskID];
    /* Check if new task belongs to same core */
    if (LpStaticTask->ddCoreId != OS_CORE_ID)
    {
      /* @Trace : SafeOs_SUD_API_56103 */
      /* Call Os_SendAsynFunc to schedule task on respective core */
      Os_SendAsynFunc(TaskID, Mask);
    } /* End of if (LpStaticTask->ddCoreId != OS_CORE_ID) */
    else
    #endif /* End of if (OS_MULTICORE == STD_ON) */
    {
      /* @Trace : SafeOs_SUD_API_56104 */
      /* Call Os_DoSetEvent and get the return value */
      LenStatusReturn = Os_DoSetEvent(TaskID, Mask, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_56105 */
    /* Store the service ID of SetEventAsyn */
    OS_STORE_SERVICE(OSServiceId_SetEventAsyn);
    /* Store the parameter 1 - TaskID */
    OS_STORE_PARAM1_TASKID(TaskID);
    /* Store the parameter 2 - Mask */
    OS_STORE_PARAM2_MASK(Mask);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */
} /* End of SetEvent(TaskType TaskID, EventMaskType Mask) */
#endif /* End of if (OS_EVENT == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernClearEvent                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The events of the extended task calling ClearEvent  **
**                        are cleared according to the event mask <Mask>.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : EventMaskType Mask                                  **
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
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 */
#if (OS_EVENT == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernClearEvent(EventMaskType Mask)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace : SafeOs_SUD_API_06603 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call from call level */
  OS_CHECK_E_OS_CALLEVEL(CLEAREVENT, LenStatusReturn);
  /* Check that the calling task is an extended one */
  OS_CHECK_NOT_EXTENDED_RUNNING_ERROR(LenStatusReturn);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_06601 */
    /* Clear the Event */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
    Os_GpStaticTask[OS_CORE_ID]->pTask->ddEventSet &= (EventMaskType)(~Mask);
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  else
  {
    /* @Trace : SafeOs_SUD_API_06602 */
    /* Store service ID of ClearEvent */
    OS_STORE_SERVICE(OSServiceId_ClearEvent);
    /* Store the parameter 1 - Mask */
    OS_STORE_PARAM1_MASK(Mask);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif /* End of if (OS_STATUS == EXTENDED) */

  /* Return The value */
  return (LenStatusReturn);
} /* End of ClearEvent(EventMaskType Mask) */
#endif /* End of if (OS_EVENT == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernGetEvent                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service returns the current state of all       **
**                        event bits of the task.                             **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : TaskType TaskID, EventMaskRefType Event             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : EventMaskRefType Event                              **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendGetEvent(), Os_DoGetEvent()                  **
*******************************************************************************/
/* @Trace: SRS_Os_00097 */
#if (OS_EVENT == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernGetEvent(TaskType TaskID,
                                                         EventMaskRefType Event)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace : SafeOs_SUD_API_06705 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(GETEVENT, LenStatusReturn);
  /* Check whether TaskID is greater than number of task count */
  OS_CHECK_TASK_ID_ERROR(TaskID, LenStatusReturn);
  /* Check the task is an extended one */
  OS_CHECK_NOT_EXTENDED_TASK_ERROR(TaskID, LenStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(Event, LenStatusReturn);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_06701 */
    #if (OS_MULTICORE == STD_ON)
    /* @Trace : SafeOs_SUD_API_06706 */
    /* Store the static task corresponding to TaskID in local pointer */
    LpStaticTask = &Os_GaaStaticTask[TaskID];
    /* Check if new task belongs to same core */
    if (LpStaticTask->ddCoreId != OS_CORE_ID)
    {
      /* @Trace : SafeOs_SUD_API_06702 */
      /* Call Os_SendGetEvent to get event on respective core */
      LenStatusReturn = Os_SendGetEvent(TaskID, Event);
    } /* End of if (LpStaticTask->ddCoreId != OS_CORE_ID) */
    else
    #endif /* End of if (OS_MULTICORE == STD_ON) */
    {
      /* @Trace : SafeOs_SUD_API_06703 */
      /* Call Os_DoGetEvent and get the return value */
      LenStatusReturn = Os_DoGetEvent(TaskID, Event);
    }
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_06704 */
    /* Store the service ID of GetEvent */
    OS_STORE_SERVICE(OSServiceId_GetEvent);
    /* Store the parameter 1 - TaskID */
    OS_STORE_PARAM1_TASKID(TaskID);
    /* Store the parameter 2 - Event */
    OS_STORE_PARAM2_EVENT(Event);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */

  /* Return The value */
  return (LenStatusReturn);
} /* End of GetEvent(TaskType TaskID, EventMaskRefType Event) */
#endif /* End of if (OS_EVENT == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernWaitEvent                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The state of the calling task is set to waiting     **
**                        unless at least one of the events specified         **
**                        in <Mask> has already been set.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : EventMaskType Mask                                  **
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
**                        Os_ReleaseInternalResource(),                       **
**                        Os_TaskWaitingHook(),                               **
**                        Os_ScheduleService(),                               **
**                        Os_StartTimeFrame(),                                **
**                        Os_MemCopy()                                        **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11008 SRS_Os_80021 SRS_AUTRON_00015 */
#if (OS_EVENT == STD_ON)
/* polyspace +2 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
/* polyspace +1 CODE-METRICS:CALLS [Not a defect:Low] "Function is called to wait the task calling" */
FUNC(StatusType, OS_CODE) Os_KernWaitEvent(EventMaskType Mask)
{
  #if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO)
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  #endif

  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) LpTask;
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  boolean LblHasWaitingEventNotSet;
  LblHasWaitingEventNotSet = OS_FALSE;

  /* @Trace : SafeOs_SUD_API_06805 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(WAITEVENT, LenStatusReturn);
  /* Check the calling task is an extended one */
  OS_CHECK_NOT_EXTENDED_RUNNING_ERROR(LenStatusReturn);
  /* Check the task does not occupied resource(s) */
  OS_CHECK_RUNNING_OWNS_REZ_ERROR(LenStatusReturn);
  /* Check the task does not own a spinlock */
  OS_CHECK_RUNNING_OWNS_SPINLOCK_ERROR(LenStatusReturn);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_06801 */
    #if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO)
    /* @Trace : SafeOs_SUD_API_06806 */
    LpStaticTask = Os_GpStaticTask[OS_CORE_ID];
    /* Release the internal resource */
    Os_ReleaseInternalResource(LpStaticTask);
    #endif

    /* Take Task in local variable */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
    /* @Trace : SafeOs_SUD_API_06807 */
    LpTask = Os_GpStaticTask[OS_CORE_ID]->pTask;
    /* Get the value of Mask into EventWait of running task */
    LpTask->ddEventWait = Mask;

    if ((LpTask->ddEventSet & Mask) != OS_ZERO)
    {
      LblHasWaitingEventNotSet = OS_TRUE;
    }

    /* Check one of the event to wait is not already set */
    if (LblHasWaitingEventNotSet != OS_TRUE)
    {
      /* @Trace : SafeOs_SUD_API_06802 */
      #if (OS_POSTTASK_HOOK == STD_ON)
      /* @Trace : SafeOs_SUD_API_06808 */
      /* Process PostTaskHook */
      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      OS_PROCESS_POSTTASKHOOK();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      #endif

      /* Put the running task into the WAITING state */
      LpTask->ddState = WAITING;
      #if (OS_PROFILING_HOOK == STD_ON)
      /* @Trace : SafeOs_SUD_API_06809 */
      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      Os_TaskWaitingHook(OS_CORE_ID, Os_GpStaticTask[OS_CORE_ID]->ddTaskId);
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      #endif
      /* @Trace : SafeOs_SUD_API_06810 */
      /* Call Function to switch context of old task with new task */
      Os_ScheduleService();
      OS_SAVECONTEXT();
    } /* End of if (LblHasWaitingEventNotSet != OS_TRUE) */
    #if (OS_TASK_TP_TF == STD_ON)
    else
    {
      /* @Trace : SafeOs_SUD_API_06803 */
      /* Check if task is invoked after the expiry of time frame */
      Os_StartTimeFrame(Os_GpStaticTask[OS_CORE_ID]);
    } /* End of else */
    #endif /* End of if (OS_TASK_TP_TF == STD_ON) */
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)

  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_06804 */
    /* Store service ID of WaitEvent */
    OS_STORE_SERVICE(OSServiceId_WaitEvent);
    /* Store the parameter 1 - Mask */
    OS_STORE_PARAM1_MASK(Mask);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */

  /* Return The value */
  return (LenStatusReturn);
} /* End of WaitEvent(EventMaskType Mask) */
#endif /* End of if (OS_EVENT == STD_ON) */

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually." */
/* polyspace-end RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
