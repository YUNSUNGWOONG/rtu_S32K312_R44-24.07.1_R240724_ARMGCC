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
**  SRC-MODULE: Os_Hook.c                                                     **
**                                                                            **
**  TARGET    : s32k31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS Improvement Code                                   **
**                                                                            **
**  PURPOSE   : Provision of helper functions for OS Hooks                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.1.0      7-Apr-2023    HG.Kim        Redmine # 39577                     **
** 1.0.0     11-Jan-2023    HG.Kim        Redmine #38437                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Hook.h"
#include "Os_Multicore.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define OS_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
uint32 GulOsErrorCount;
uint32 GulOsErrorLastPosition;
uint32 Os_GulOsLimitError;
uint32 Os_GulOsStackFaultError;
#define OS_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
Os_ErrorType GucOsError[SZ_OSERROR];
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OS_START_SEC_CODE
#include "MemMap.h"

/***************************************************************************//**
 * Function Name        : Os_UpdateOsErrorInfo
 *
 * Service ID           : NA
 *
 * Description          : This service is used to save OS error information.
 *                        API name, error reason and API parameter are saved to
 *                        'GucOsError'
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LddError      Error reason
 *                                      (range : 1 ~ 103)
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        GulOsErrorLastPosition, GulOsErrorCount, GucOsError,
 *                        Os_GulOsLimitError, Os_GulOsStackFaultError
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_UpdateOsErrorInfo(StatusType LddError)
{
  Os_ErrorApiType LddServiceId;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  #if ((OS_ERROR_HOOK == STD_ON) && (OS_USE_GET_SERVICE_ID == STD_ON))
  /* polyspace:begin<MISRA-C3:10.5:Not a defect:Justify with annotations> type casting does not affect the result */
  switch (LddError)
  {
    case E_OS_STACKFAULT:
    case E_OS_PROTECTION_MEMORY:
    case E_OS_PROTECTION_TIME:
    case E_OS_PROTECTION_LOCKED:
    case E_OS_PROTECTION_EXCEPTION:
    case E_OS_PROTECTION_ARRIVAL:
    case E_OS_SYS_RAMECC:
    case E_OS_SYS_DFLASHECC:
    case E_OS_SYS_PFLASHECC:
    case E_OS_SYS_PANIC:
    case E_OS_SYS_NMI:
      LddServiceId = OS_INVALID_VALUE;
      break;
    default :
      LddServiceId = (Os_ErrorApiType)OSErrorGetServiceId();
      break;
  }
  /* polyspace:end<MISRA-C3:10.5> */
  #else
  LddServiceId = OS_INVALID_VALUE;
  #endif

  /* polyspace:begin<MISRA-C3:10.5:Not a defect:Justify with annotations> type casting does not affect the result */
  GulOsErrorLastPosition = GulOsErrorCount & (uint32)MASK_OSERROR_BUF;
  GucOsError[GulOsErrorLastPosition].enApi = LddServiceId;
  GucOsError[GulOsErrorLastPosition].enErrorNo = (Os_ErrorValueType)LddError;
  /* polyspace:end<MISRA-C3:10.5> */
  #if ((OS_ERROR_HOOK == STD_ON) && (OS_USER_PARAMETER_ACCESS == STD_ON))
  switch (LddServiceId)
  {
    /* below OS APIs doesn't call error hook
     *
     * StartOS, ShutdownOS, GetActiveApplicationMode, CheckISRMemoryAccess,
     * CheckTaskMemoryAccess, GetApplicationID, CheckObjectAccess,
     * CheckObjectOwnership                                                   */

    /* services for memory protection */
    #if (OS_MEMORY_PROTECTION == STD_ON)
    #if (OS_TRUSTED_FUNC_COUNT != OS_ZERO)
    case OSServiceId_CallTrustedFunction:
      GucOsError[GulOsErrorLastPosition].unPar1.OsTrustedFunctionIndexId =
                                    OSError_CallTrustedFunction_FunctionIndex();
      GucOsError[GulOsErrorLastPosition].unPar2.OsTrustedFunctionParams =
                                   OSError_CallTrustedFunction_FunctionParams();
      break;
    #endif
    #endif /* #if (OS_MEMORY_PROTECTION == STD_ON) */

    /* services for OS-Application */
    #if (OS_APPLICATION == STD_ON)
    case OSServiceId_TerminateApplication:
      GucOsError[GulOsErrorLastPosition].unPar1.OsApplicationId =
                                     OSError_TerminateApplication_Application();
      GucOsError[GulOsErrorLastPosition].unPar2.OsRestartOption =
                                   OSError_TerminateApplication_RestartOption();
      break;
    case OSServiceId_AllowAccess:
      break;
    case OSServiceId_GetApplicationState:
      GucOsError[GulOsErrorLastPosition].unPar1.OsApplicationId =
                                      OSError_GetApplicationState_Application();
      break;
    #endif /* (OS_APPLICATION == STD_ON) */

    /* services for Task */
    #if (OS_TASK == STD_ON)
    case OSServiceId_ActivateTask:
      GucOsError[GulOsErrorLastPosition].unPar1.OsTaskId =
                                                  OSError_ActivateTask_TaskID();
      break;
    case OSServiceId_TerminateTask:
      break;
    case OSServiceId_ChainTask:
      GucOsError[GulOsErrorLastPosition].unPar1.OsTaskId =
                                                     OSError_ChainTask_TaskID();
      break;
    case OSServiceId_Schedule:
      break;
    case OSServiceId_GetTaskID:
      break;
    case OSServiceId_GetTaskState:
      GucOsError[GulOsErrorLastPosition].unPar1.OsTaskId =
                                                  OSError_GetTaskState_TaskID();
      break;
    #endif /* #if (OS_TASK == STD_ON) */

    /* services for resource */
    #if (OS_RESOURCE == STD_ON)
    case OSServiceId_GetResource:
      GucOsError[GulOsErrorLastPosition].unPar1.OsResourceId =
                                                    OSError_GetResource_ResID();
      break;
    case OSServiceId_ReleaseResource:
      GucOsError[GulOsErrorLastPosition].unPar1.OsResourceId =
                                                OSError_ReleaseResource_ResID();
      break;
    #endif /* #if (OS_RESOURCE == STD_ON) */

    /* services for event */
    #if (OS_EVENT == STD_ON)
    case OSServiceId_SetEvent:
      GucOsError[GulOsErrorLastPosition].unPar1.OsTaskId =
                                                      OSError_SetEvent_TaskID();
      GucOsError[GulOsErrorLastPosition].unPar2.OsMaskParam2 =
                                                        OSError_SetEvent_Mask();
      break;
    case OSServiceId_ClearEvent:
      GucOsError[GulOsErrorLastPosition].unPar1.OsMask =
                                                      OSError_ClearEvent_Mask();
      break;
    case OSServiceId_GetEvent:
      GucOsError[GulOsErrorLastPosition].unPar1.OsTaskId =
                                                      OSError_GetEvent_TaskID();
      break;
    #endif /* #if (OS_EVENT == STD_ON) */

    /* services for alarm */
    #if (OS_ALARM == STD_ON)
    case OSServiceId_GetAlarmBase:
      GucOsError[GulOsErrorLastPosition].unPar1.OsAlarmId =
                                                 OSError_GetAlarmBase_AlarmID();
      break;
    case OSServiceId_GetAlarm:
      GucOsError[GulOsErrorLastPosition].unPar1.OsAlarmId =
                                                     OSError_GetAlarm_AlarmID();
      break;
    case OSServiceId_SetRelAlarm:
      GucOsError[GulOsErrorLastPosition].unPar1.OsAlarmId =
                                                  OSError_SetRelAlarm_AlarmID();
      GucOsError[GulOsErrorLastPosition].unPar2.OsIncrement =
                                                OSError_SetRelAlarm_Increment();
      GucOsError[GulOsErrorLastPosition].unPar3.OsCycle =
                                                    OSError_SetRelAlarm_Cycle();
      break;
    case OSServiceId_SetAbsAlarm:
      GucOsError[GulOsErrorLastPosition].unPar1.OsAlarmId =
                                                  OSError_SetAbsAlarm_AlarmID();
      GucOsError[GulOsErrorLastPosition].unPar2.OsStart =
                                                    OSError_SetAbsAlarm_Start();
      GucOsError[GulOsErrorLastPosition].unPar3.OsCycle =
                                                    OSError_SetAbsAlarm_Cycle();
      break;
    case OSServiceId_CancelAlarm:
      GucOsError[GulOsErrorLastPosition].unPar1.OsAlarmId =
                                                  OSError_CancelAlarm_AlarmID();
      break;
    #endif /* #if (OS_ALARM == STD_ON) */

    /* services for counter */
    #if (OS_COUNTER == STD_ON)
    case OSServiceId_IncrementCounter:
      GucOsError[GulOsErrorLastPosition].unPar1.OsCounterId =
                                           OSError_IncrementCounter_CounterID();
      break;
    case OSServiceId_GetCounterValue:
      GucOsError[GulOsErrorLastPosition].unPar1.OsCounterId =
                                            OSError_GetCounterValue_CounterID();
      break;
    case OSServiceId_GetElapsedValue:
      GucOsError[GulOsErrorLastPosition].unPar1.OsCounterId =
                                            OSError_GetElapsedValue_CounterID();
      break;
    #endif /* #if (OS_COUNTER == STD_ON) */

    /* services for scheduletable */
    #if (OS_SCHEDTABLE == STD_ON)
    case OSServiceId_StartScheduleTableRel:
      GucOsError[GulOsErrorLastPosition].unPar1.OsScheduleTableId =
                                OSError_StartScheduleTableRel_ScheduleTableID();
      GucOsError[GulOsErrorLastPosition].unPar2.OsOffset =
                                         OSError_StartScheduleTableRel_Offset();
      break;
    case OSServiceId_StartScheduleTableAbs:
      GucOsError[GulOsErrorLastPosition].unPar1.OsScheduleTableId =
                                OSError_StartScheduleTableAbs_ScheduleTableID();
      GucOsError[GulOsErrorLastPosition].unPar2.OsStart =
                                          OSError_StartScheduleTableAbs_Start();
      break;
    case OSServiceId_StopScheduleTable:
      GucOsError[GulOsErrorLastPosition].unPar1.OsScheduleTableId =
                                    OSError_StopScheduleTable_ScheduleTableID();
      break;
    case OSServiceId_NextScheduleTable:
      GucOsError[GulOsErrorLastPosition].unPar1.OsScheduleTableId_From =
                                OSError_NextScheduleTable_ScheduleTableIDFrom();
      GucOsError[GulOsErrorLastPosition].unPar2.OsScheduleTableId_To =
                                  OSError_NextScheduleTable_ScheduleTableIDTo();
      break;
    #if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
    case OSServiceId_StartScheduleTableSynchron:
      GucOsError[GulOsErrorLastPosition].unPar1.OsScheduleTableId =
                           OSError_StartScheduleTableSynchron_ScheduleTableID();
      break;
    case OSServiceId_SyncScheduleTable:
      GucOsError[GulOsErrorLastPosition].unPar1.OsScheduleTableId =
                                    OSError_SyncScheduleTable_ScheduleTableID();
      GucOsError[GulOsErrorLastPosition].unPar2.OsValue =
                                              OSError_SyncScheduleTable_Value();
      break;
    case OSServiceId_SetScheduleTableAsync:
      GucOsError[GulOsErrorLastPosition].unPar1.OsScheduleTableId =
                                OSError_SetScheduleTableAsync_ScheduleTableID();
      break;
    #endif /* #if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */
    case OSServiceId_GetScheduleTableStatus:
      GucOsError[GulOsErrorLastPosition].unPar1.OsScheduleTableId =
                               OSError_GetScheduleTableStatus_ScheduleTableID();
      break;
    #endif /* #if (OS_SCHEDTABLE == STD_ON) */

    #if (OS_SPINLOCK == STD_ON)
    case OSServiceId_GetSpinlock:
      GucOsError[GulOsErrorLastPosition].unPar1.OsSpinlockId =
                                               OSError_GetSpinlock_SpinlockId();
      break;
    case OSServiceId_ReleaseSpinlock:
      GucOsError[GulOsErrorLastPosition].unPar1.OsSpinlockId =
                                           OSError_ReleaseSpinlock_SpinlockId();
      break;
    case OSServiceId_TryToGetSpinlock:
      GucOsError[GulOsErrorLastPosition].unPar1.OsSpinlockId =
                                          OSError_TryToGetSpinlock_SpinlockId();
      break;
    #endif /* #if (OS_SPINLOCK == STD_ON) */

    default:
      GucOsError[GulOsErrorLastPosition].unPar1.OsAlarmId = OS_INVALID_VALUE;
      GucOsError[GulOsErrorLastPosition].unPar2.OsStart = OS_INVALID_VALUE;
      GucOsError[GulOsErrorLastPosition].unPar3.OsCycle = OS_INVALID_VALUE;
      break;
  }
  #endif /* #if (OS_USER_PARAMETER_ACCESS == STD_ON) */

  if (E_OS_LIMIT == LddError)
  {
    Os_GulOsLimitError++;
  }
  if (E_OS_STACKFAULT == LddError)
  {
    Os_GulOsStackFaultError++;
    /* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> pointer is within pre-defined range */
    /* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> pointer is within pre-defined range */
    /* polyspace:begin<RTE:OBAI:Not a defect:Justify with annotations> array is within pre-defined range */
    /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> result of pointer operation is within pre-defined range */
    GucOsError[GulOsErrorLastPosition].unPar1.OsTaskId =
                                          Os_GpStaticTask[OS_CORE_ID]->ddTaskId;
    /* polyspace:end<RTE:IDP> */
    /* polyspace:end<RTE:NIV> */
    /* polyspace:end<RTE:OBAI> */
    /* polyspace:end<MISRA-C3:18.1> */
  }

  GulOsErrorCount++;
} /* End of Os_UpdateErrorHookInfo() */

#define OS_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

