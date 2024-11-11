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
**  SRC-MODULE: Os_ErrorExternal.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file containing the declaration of                     **
**              Hook functionality related functions.                         **
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
** 1.5.0     24-May-2023   SH.Yoo           Jira CP44-2227                    **
** 1.3.12.0  09-Mar-2023   TanHX            Jira CP44-1335                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.2     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.1     31-Jul-2020   DanhDC1          R44-Redmine #14813                **
**                                          Check the NULL_PTR IOC APIs       **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Inline functions are needed for performance and Macro definitions are needed for performance and file size  */
/* polyspace:begin<MISRA-C:8.1:Not a defect:Justify with annotations> Prototype declaration of inline function is not needed */
/* polyspace-begin MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */
/* @Trace: SRS_Os_00097 SRS_BSW_00330 */
#ifndef OS_ERROREXTERNAL_H
#define OS_ERROREXTERNAL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Ram.h"
#include "Os_Cfg.h"
#include "Os_Multicore.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00410 */
#if ((OS_ERROR_HOOK == STD_ON) || (OS_APP_ERROR_HOOK == STD_ON))
#define OS_PROCESS_ERROR(Error) (Os_ErrorHook(Error))
#else
#define OS_PROCESS_ERROR(Error)
#endif

/* @Trace: SRS_BSW_00330 */
#if (OS_ERROR_HOOK == STD_ON)
#define OS_STORE_SERVICE(Service)\
  do{ \
    Os_GddServiceCall[OS_CORE_ID].ucServiceID = (uint8)(Service); \
  } while(0)
#else
#define OS_STORE_SERVICE(Service)
#endif

/* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Left operand cannot be enclosed in parentheses" */
#if (OS_STATUS == STANDARD)
#define OS_CHECK_NULL_PTR(Value, LenStatusReturn)
#else
#define OS_CHECK_NULL_PTR(Value, LenStatusReturn)\
  do{ \
    if (((LenStatusReturn) == E_OK) && ((Value) == NULL_PTR))\
    {\
      LenStatusReturn = E_OS_PARAM_POINTER;\
    } \
  } while(0)
#endif

#define OS_CHECK_IOC_NULL_PTR(Value, LenStatusReturn)\
  do{ \
    if (((LenStatusReturn) == E_OK) && ((Value) == NULL_PTR))\
    {\
      LenStatusReturn = IOC_E_NOK;\
    } \
  } while(0)
/* polyspace-end MISRA-C3:20.7 [Justified:Low] "Left operand cannot be enclosed in parentheses" */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if ((OS_ERROR_HOOK == STD_ON) || (OS_APP_ERROR_HOOK == STD_ON))
extern FUNC(void, OS_CODE) Os_ErrorHook(StatusType Error);
#endif /* End of if ((OS_ERROR_HOOK == STD_ON) || (OS_APP_ERROR_HOOK == STD_ON))
        */

#if (OS_ERROR_HOOK == STD_ON)
#if (OS_USE_GET_SERVICE_ID == STD_ON)
/* @Trace: SRS_Os_00097 */
OS_LOCAL_INLINE OSServiceIdType OSErrorGetServiceId(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ucServiceID;
}
#else
#define OSErrorGetServiceId()
#endif

/* polyspace-begin MISRA-C3:5.1 [Justified:Low] "External function is defined for same API with different parameter which is used as postfix" */
/* @Trace: SafeOs_SUD_DATATYPE_00201 */
#if (OS_USER_PARAMETER_ACCESS == STD_ON)

/* CallTrustedFunction - FunctionIndex, FunctionParams */
OS_LOCAL_INLINE TrustedFunctionIndexType OSError_CallTrustedFunction_FunctionIndex(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.FunctionIndex;
}

OS_LOCAL_INLINE TrustedFunctionParameterRefType \
                                OSError_CallTrustedFunction_FunctionParams(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.FunctionParams;
}

/* StartScheduleTableRel - ScheduleTableID, Offset */
OS_LOCAL_INLINE ScheduleTableType OSError_StartScheduleTableRel_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

OS_LOCAL_INLINE TickType OSError_StartScheduleTableRel_Offset(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Offset;
}

/* StartScheduleTableAbs - ScheduleTableID, Start */
OS_LOCAL_INLINE ScheduleTableType OSError_StartScheduleTableAbs_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

OS_LOCAL_INLINE TickType OSError_StartScheduleTableAbs_Start(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Start;
}

/* StopScheduleTable - ScheduleTableID */
OS_LOCAL_INLINE ScheduleTableType OSError_StopScheduleTable_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

/* NextScheduleTable - ScheduleTableID_From, ScheduleTableID_To */
OS_LOCAL_INLINE ScheduleTableType OSError_NextScheduleTable_ScheduleTableIDFrom(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID_From;
}

OS_LOCAL_INLINE ScheduleTableType OSError_NextScheduleTable_ScheduleTableIDTo(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.ScheduleTableID_To;
}

/* StartScheduleTableSynchron - ScheduleTableID */
OS_LOCAL_INLINE ScheduleTableType OSError_StartScheduleTableSynchron_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

/* SyncScheduleTable - ScheduleTableID, Value */
OS_LOCAL_INLINE ScheduleTableType OSError_SyncScheduleTable_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

OS_LOCAL_INLINE TickType OSError_SyncScheduleTable_Value(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Value;
}

/* SetScheduleTableAsync - ScheduleTableID */
OS_LOCAL_INLINE ScheduleTableType OSError_SetScheduleTableAsync_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

/* GetScheduleTableStatus - ScheduleTableID, ScheduleStatus */
OS_LOCAL_INLINE ScheduleTableType OSError_GetScheduleTableStatus_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

OS_LOCAL_INLINE ScheduleTableStatusRefType \
                             OSError_GetScheduleTableStatus_ScheduleStatus(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.ScheduleStatus;
}

/* IncrementCounter - CounterID */
OS_LOCAL_INLINE CounterType OSError_IncrementCounter_CounterID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.CounterID;
}

/* GetCounterValue - CounterID, Value */
OS_LOCAL_INLINE CounterType OSError_GetCounterValue_CounterID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.CounterID;
}

OS_LOCAL_INLINE TickRefType OSError_GetCounterValue_Value(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.ValueRef;
}

/* GetElapsedValue - CounterID, Value, ElapsedValue */
OS_LOCAL_INLINE CounterType OSError_GetElapsedValue_CounterID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.CounterID;
}

OS_LOCAL_INLINE TickRefType OSError_GetElapsedValue_Value(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.ValueRef;
}

OS_LOCAL_INLINE TickRefType OSError_GetElapsedValue_ElapsedValue(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.ElapsedValue;
}

/* TerminateApplication - Application, RestartOption */
OS_LOCAL_INLINE ApplicationType OSError_TerminateApplication_Application(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Application;
}

OS_LOCAL_INLINE RestartType OSError_TerminateApplication_RestartOption(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.RestartOption;
}

/* GetApplicationState - Application, Value */
OS_LOCAL_INLINE ApplicationType OSError_GetApplicationState_Application(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Application;
}

OS_LOCAL_INLINE ApplicationStateRefType OSError_GetApplicationState_Value(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.AppValueRef;
}

/* ActivateTask - TaskID */
OS_LOCAL_INLINE TaskType OSError_ActivateTask_TaskID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskID;
}

/* ActivateTaskAsyn - TaskID */
OS_LOCAL_INLINE TaskType OSError_ActivateTaskAsyn_Id(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskID;
}

/* ChainTask - TaskID */
OS_LOCAL_INLINE TaskType OSError_ChainTask_TaskID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskID;
}

/* GetTaskID - TaskID */
OS_LOCAL_INLINE TaskRefType OSError_GetTaskID_TaskID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskIDRef;
}

/* GetTaskState - TaskID, State */
OS_LOCAL_INLINE TaskType OSError_GetTaskState_TaskID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskID;
}

OS_LOCAL_INLINE TaskStateRefType OSError_GetTaskState_State(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.State;
}

/* GetResource - ResID */
OS_LOCAL_INLINE ResourceType OSError_GetResource_ResID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ResID;
}

/* ReleaseResource - ResID */
OS_LOCAL_INLINE ResourceType OSError_ReleaseResource_ResID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ResID;
}

/* SetEvent - TaskID, Mask */
OS_LOCAL_INLINE TaskType OSError_SetEvent_TaskID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskID;
}

OS_LOCAL_INLINE EventMaskType OSError_SetEvent_Mask(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Mask;
}

/* ClearEvent - Mask */
OS_LOCAL_INLINE EventMaskType OSError_ClearEvent_Mask(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Mask;
}

/* WaitEvent - Mask */
OS_LOCAL_INLINE EventMaskType OSError_WaitEvent_Mask(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Mask;
}

/* SetEventAsyn - TaskID, Mask */
OS_LOCAL_INLINE TaskType OSError_SetEventAsyn_Id(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskID;
}

OS_LOCAL_INLINE EventMaskType OSError_SetEventAsyn_m(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Mask;
}

/* GetEvent - TaskID, Event */
OS_LOCAL_INLINE TaskType OSError_GetEvent_TaskID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskID;
}

OS_LOCAL_INLINE EventMaskRefType OSError_GetEvent_Event(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
    return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Event;
}

/* GetAlarmBase - AlarmID, Info */
OS_LOCAL_INLINE AlarmType OSError_GetAlarmBase_AlarmID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.AlarmID;
}

OS_LOCAL_INLINE AlarmBaseRefType OSError_GetAlarmBase_Info(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Info;
}

/* GetAlarm - AlarmID, Tick */
OS_LOCAL_INLINE AlarmType OSError_GetAlarm_AlarmID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.AlarmID;
}

OS_LOCAL_INLINE TickRefType OSError_GetAlarm_Tick(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Tick;
}

/* SetRelAlarm - AlarmID, Increment, Cycle */
OS_LOCAL_INLINE AlarmType OSError_SetRelAlarm_AlarmID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.AlarmID;
}

OS_LOCAL_INLINE TickType OSError_SetRelAlarm_Increment(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Increment;
}

OS_LOCAL_INLINE TickType OSError_SetRelAlarm_Cycle(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.Cycle;
}

/* SetAbsAlarm - AlarmID, Start, Cycle */
OS_LOCAL_INLINE AlarmType OSError_SetAbsAlarm_AlarmID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.AlarmID;
}

OS_LOCAL_INLINE TickType OSError_SetAbsAlarm_Start(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Start;
}

OS_LOCAL_INLINE TickType OSError_SetAbsAlarm_Cycle(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.Cycle;
}

/* CancelAlarm - AlarmID */
OS_LOCAL_INLINE AlarmType OSError_CancelAlarm_AlarmID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.AlarmID;
}

/* GetSpinlock - SpinlockId */
OS_LOCAL_INLINE SpinlockIdType OSError_GetSpinlock_SpinlockId(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.SpinlockId;
}

/* ReleaseSpinlock - SpinlockId */
OS_LOCAL_INLINE SpinlockIdType OSError_ReleaseSpinlock_SpinlockId(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.SpinlockId;
}

/* TryToGetSpinlock - SpinlockId, Success */
OS_LOCAL_INLINE SpinlockIdType OSError_TryToGetSpinlock_SpinlockId(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.SpinlockId;
}

OS_LOCAL_INLINE TryToGetSpinlockType* OSError_TryToGetSpinlock_Success(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Success;
}

/* ControlIdle - CoreID, IdleMode */
OS_LOCAL_INLINE CoreIDType OSError_ControlIdle_CoreID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.CoreID;
}

OS_LOCAL_INLINE IdleModeType OSError_ControlIdle_IdleMode(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.IdleMode;
}

/* EnableInterruptSource - ISRID, ClearPending */
OS_LOCAL_INLINE ISRType OSError_EnableInterruptSource_ISRID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ISRID;
}

OS_LOCAL_INLINE boolean OSError_EnableInterruptSource_ClearPending(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.ClearPending;
}

/* DisableInterruptSource - ISRID */
OS_LOCAL_INLINE ISRType OSError_DisableInterruptSource_ISRID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ISRID;
}

/* ClearPendingInterrupt - ISRID */
OS_LOCAL_INLINE ISRType OSError_ClearPendingInterrupt_ISRID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ISRID;
}

/* ReadPeripheral8 - Area, Address, ReadValue  */
OS_LOCAL_INLINE AreaIdType OSError_ReadPeripheral8_Area(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Area;
}

OS_LOCAL_INLINE P2CONST(uint32, AUTOMATIC, OS_CONST) OSError_ReadPeripheral8_Address(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.AddressR;
}

OS_LOCAL_INLINE uint32* OSError_ReadPeripheral8_ReadValue(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.Readvalue;
}

/* ReadPeripheral16 - Area, Address, ReadValue  */
OS_LOCAL_INLINE AreaIdType OSError_ReadPeripheral16_Area(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Area;
}

OS_LOCAL_INLINE P2CONST(uint32, AUTOMATIC, OS_CONST) OSError_ReadPeripheral16_Address(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.AddressR;
}

OS_LOCAL_INLINE uint32* OSError_ReadPeripheral16_ReadValue(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.Readvalue;
}

/* ReadPeripheral32 - Area, Address, ReadValue  */
OS_LOCAL_INLINE AreaIdType OSError_ReadPeripheral32_Area(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Area;
}

OS_LOCAL_INLINE P2CONST(uint32, AUTOMATIC, OS_CONST) OSError_ReadPeripheral32_Address(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.AddressR;
}

OS_LOCAL_INLINE uint32* OSError_ReadPeripheral32_ReadValue(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.Readvalue;
}

/* WritePeripheral8 - Area, Address, WriteValue */
OS_LOCAL_INLINE AreaIdType OSError_WritePeripheral8_Area(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Area;
}

OS_LOCAL_INLINE P2CONST(uint32, AUTOMATIC, OS_CONST) OSError_WritePeripheral8_Address(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.AddressW;
}

OS_LOCAL_INLINE uint32 OSError_WritePeripheral8_WriteValue(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.WriteValue;
}

/* WritePeripheral16 - Area, Address, WriteValue */
OS_LOCAL_INLINE AreaIdType OSError_WritePeripheral16_Area(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Area;
}

OS_LOCAL_INLINE P2CONST(uint32, AUTOMATIC, OS_CONST) OSError_WritePeripheral16_Address(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.AddressW;
}

OS_LOCAL_INLINE uint32 OSError_WritePeripheral16_WriteValue(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.WriteValue;
}

/* WritePeripheral32 - Area, Address, WriteValue */
OS_LOCAL_INLINE AreaIdType OSError_WritePeripheral32_Area(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Area;
}

OS_LOCAL_INLINE P2CONST(uint32, AUTOMATIC, OS_CONST) OSError_WritePeripheral32_Address(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.AddressW;
}

OS_LOCAL_INLINE uint32 OSError_WritePeripheral32_WriteValue(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.WriteValue;
}

/* ModifyPeripheral8 - Area, Address, Clearmask, Setmask */
OS_LOCAL_INLINE AreaIdType OSError_ModifyPeripheral8_Area(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Area;
}

OS_LOCAL_INLINE P2CONST(uint32, AUTOMATIC, OS_CONST) OSError_ModifyPeripheral8_Address(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.AddressM;
}

OS_LOCAL_INLINE uint32 OSError_ModifyPeripheral8_Clearmask(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.Clearmask;
}

OS_LOCAL_INLINE uint32 OSError_ModifyPeripheral8_Setmask(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam4.Setmask;
}

/* ModifyPeripheral16 - Area, Address, Clearmask, Setmask */
OS_LOCAL_INLINE AreaIdType OSError_ModifyPeripheral16_Area(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Area;
}

OS_LOCAL_INLINE P2CONST(uint32, AUTOMATIC, OS_CONST) OSError_ModifyPeripheral16_Address(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.AddressM;
}

OS_LOCAL_INLINE uint32 OSError_ModifyPeripheral16_Clearmask(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.Clearmask;
}

OS_LOCAL_INLINE uint32 OSError_ModifyPeripheral16_Setmask(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam4.Setmask;
}

/* ModifyPeripheral32 - Area, Address, Clearmask, Setmask */
OS_LOCAL_INLINE AreaIdType OSError_ModifyPeripheral32_Area(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Area;
}

OS_LOCAL_INLINE P2CONST(uint32, AUTOMATIC, OS_CONST) OSError_ModifyPeripheral32_Address(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.AddressM;
}

OS_LOCAL_INLINE uint32 OSError_ModifyPeripheral32_Clearmask(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.Clearmask;
}

OS_LOCAL_INLINE uint32 OSError_ModifyPeripheral32_Setmask(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam4.Setmask;
}
/* polyspace-end MISRA-C3:5.1 [Justified:Low] "External function is defined for same API with different parameter which is used as postfix" */
#else

/* CallTrustedFunction - FunctionIndex, FunctionParams */
#define OSError_CallTrustedFunction_FunctionIndex()
#define OSError_CallTrustedFunction_FunctionParams()

/* StartScheduleTableRel - ScheduleTableID, Offset */
#define OSError_StartScheduleTableRel_ScheduleTableID()
#define OSError_StartScheduleTableRel_Offset()

/* StartScheduleTableAbs - ScheduleTableID, Start */
#define OSError_StartScheduleTableAbs_ScheduleTableID()
#define OSError_StartScheduleTableAbs_Start()

/* StopScheduleTable - ScheduleTableID */
#define OSError_StopScheduleTable_ScheduleTableID()

/* NextScheduleTable - ScheduleTableID_From, ScheduleTableID_To */
#define OSError_NextScheduleTable_ScheduleTableID_From()
#define OSError_NextScheduleTable_ScheduleTableID_To()

/* StartScheduleTableSynchron - ScheduleTableID */
#define OSError_StartScheduleTableSynchron_ScheduleTableID()

/* SyncScheduleTable - ScheduleTableID, Value */
#define OSError_SyncScheduleTable_ScheduleTableID()
#define OSError_SyncScheduleTable_Value()

/* SetScheduleTableAsync - ScheduleTableID */
#define OSError_SetScheduleTableAsync_ScheduleTableID()

/* GetScheduleTableStatus - ScheduleTableID, ScheduleStatus */
#define OSError_GetScheduleTableStatus_ScheduleTableID()
#define OSError_GetScheduleTableStatus_ScheduleStatus()

/* IncrementCounter - CounterID */
#define OSError_IncrementCounter_CounterID()

/* GetCounterValue - CounterID, Value */
#define OSError_GetCounterValue_CounterID()
#define OSError_GetCounterValue_Value()

/* GetElapsedValue - CounterID, Value, ElapsedValue */
#define OSError_GetElapsedValue_CounterID()
#define OSError_GetElapsedValue_Value()
#define OSError_GetElapsedValue_ElapsedValue()

/* TerminateApplication - Application, RestartOption */
#define OSError_TerminateApplication_Application()
#define OSError_TerminateApplication_RestartOption()

/* GetApplicationState - Application, Value */
#define OSError_GetApplicationState_Application()
#define OSError_GetApplicationState_Value()

/* ActivateTask - TaskID */
#define OSError_ActivateTask_TaskID()

/* ChainTask - TaskID */
#define OSError_ChainTask_TaskID()

/* GetTaskID - TaskID */
#define OSError_GetTaskID_TaskID()

/* GetTaskState - TaskID, State */
#define OSError_GetTaskState_TaskID()
#define OSError_GetTaskState_State()

/* GetResource - ResID */
#define OSError_GetResource_ResID()

/* ReleaseResource - ResID */
#define OSError_ReleaseResource_ResID()

/* SetEvent - TaskID, Mask */
#define OSError_SetEvent_TaskID()
#define OSError_SetEvent_Mask()

/* ClearEvent - Mask */
#define OSError_ClearEvent_Mask()

/* GetEvent - TaskID, Event */
#define OSError_GetEvent_TaskID()
#define OSError_GetEvent_Event()

/* WaitEvent - Mask */
#define OSError_WaitEvent_Mask()

/* GetAlarmBase - AlarmID, Info */
#define OSError_GetAlarmBase_AlarmID()
#define OSError_GetAlarmBase_Info()

/* GetAlarm - AlarmID, Tick */
#define OSError_GetAlarm_AlarmID()
#define OSError_GetAlarm_Tick()

/* SetRelAlarm - AlarmID, Increment, Cycle */
#define OSError_SetRelAlarm_AlarmID()
#define OSError_SetRelAlarm_Increment()
#define OSError_SetRelAlarm_Cycle()

/* SetAbsAlarm - AlarmID, Start, Cycle */
#define OSError_SetAbsAlarm_AlarmID()
#define OSError_SetAbsAlarm_Start()
#define OSError_SetAbsAlarm_Cycle()

/* CancelAlarm - AlarmID */
#define OSError_CancelAlarm_AlarmID()

/* GetSpinlock - SpinlockId */
#define OSError_GetSpinlock_SpinlockId()

/* ReleaseSpinlock - SpinlockId */
#define OSError_ReleaseSpinlock_SpinlockId()

/* TryToGetSpinlock - SpinlockId, Success */
#define OSError_TryToGetSpinlock_SpinlockId()
#define OSError_TryToGetSpinlock_Success()

/* ActivateTaskAsyn - TaskID */
#define OSError_ActivateTaskAsyn_Id()

/* SetEventAsyn - TaskID, Mask */
#define OSError_SetEventAsyn_Id()
#define OSError_SetEventAsyn_m()

/* ControlIdle - CoreID, IdleMode */
#define OSError_ControlIdle_CoreID()
#define OSError_ControlIdle_IdleMode()

/* EnableInterruptSource - ISRID, ClearPending */
#define OSError_EnableInterruptSource_ISRID()
#define OSError_EnableInterruptSource_ClearPending()

/* DisableInterruptSource - ISRID */
#define OSError_DisableInterruptSource_ISRID()

/* ClearPendingInterrupt - ISRID */
#define OSError_ClearPendingInterrupt_ISRID()

/* ReadPeripheral8 - Area, Address, ReadValue */
#define OSError_ReadPeripheral8_Area()
#define OSError_ReadPeripheral8_Address()
#define OSError_ReadPeripheral8_ReadValue()

/* ReadPeripheral16 - Area, Address, ReadValue */
#define OSError_ReadPeripheral16_Area()
#define OSError_ReadPeripheral16_Address()
#define OSError_ReadPeripheral16_ReadValue()

/* ReadPeripheral32 - Area, Address, ReadValue */
#define OSError_ReadPeripheral32_Area()
#define OSError_ReadPeripheral32_Address()
#define OSError_ReadPeripheral32_ReadValue()

/* WritePeripheral8 - Area, Address, WriteValue */
#define OSError_WritePeripheral8_Area()
#define OSError_WritePeripheral8_Address()
#define OSError_WritePeripheral8_WriteValue()

/* WritePeripheral16 - Area, Address, WriteValue */
#define OSError_WritePeripheral16_Area()
#define OSError_WritePeripheral16_Address()
#define OSError_WritePeripheral16_WriteValue()

/* WritePeripheral32 - Area, Address, WriteValue */
#define OSError_WritePeripheral32_Area()
#define OSError_WritePeripheral32_Address()
#define OSError_WritePeripheral32_WriteValue()

/* ModifyPeripheral8 - Area, Address, Clearmask, Setmask */
#define OSError_ModifyPeripheral8_Area()
#define OSError_ModifyPeripheral8_Address()
#define OSError_ModifyPeripheral8_Clearmask()
#define OSError_ModifyPeripheral8_Setmask()

/* ModifyPeripheral16 - Area, Address, Clearmask, Setmask */
#define OSError_ModifyPeripheral16_Area()
#define OSError_ModifyPeripheral16_Address()
#define OSError_ModifyPeripheral16_Clearmask()
#define OSError_ModifyPeripheral16_Setmask()

/* ModifyPeripheral32 - Area, Address, Clearmask, Setmask */
#define OSError_ModifyPeripheral32_Area()
#define OSError_ModifyPeripheral32_Address()
#define OSError_ModifyPeripheral32_Clearmask()
#define OSError_ModifyPeripheral32_Setmask()

#endif /*#if (OS_USER_PARAMETER_ACCESS == STD_ON)*/

#endif /* Error Hook */



#endif /* OS_ERROR_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Inline functions are needed for performance and Macro definitions are needed for performance and file size  */
/* polyspace:end<MISRA-C:8.1:Not a defect:Justify with annotations> Prototype declaration of inline function is not needed */
/* polyspace-end MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
