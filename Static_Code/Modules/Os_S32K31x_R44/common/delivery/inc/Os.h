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
**  SRC-MODULE: Os.h                                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of extern declaration of APIs and Service-ID's.     **
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
** 1.5.0     13-Sep-2023   HJ.Kim           Jira CP44-2459                    **
**            9-Jun-2023   HJ.Kim           Jira CP44-2325                    **
** 1.3.12.0  09-Mar-2023   TanHX            Jira CP44-1335                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.3     26-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C 2.5                 **
** 1.0.2     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Add comment for Misra-C D4.5      **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/
/* @Trace: SRS_Os_11016 SRS_Os_00097 SRS_BSW_00357 */

#ifndef OS_H
#define OS_H

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SafeOs_SUD_DATATYPE_00001 SafeOs_SUD_DATATYPE_00002 SafeOs_SUD_DATATYPE_00003 */
#include "Std_Types.h"            /* Standard Header */
#include "Compiler.h"             /* Compiler Header */
#include "Os_Definition.h"        /* Definition of OS */
#include "Os_Cfg.h"               /* Configuration header file */
#include "Os_PCfg.h"              /* Port Specific Configuration header file */
#include "Os_Types.h"             /* Type definition of OS */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* Fixme: Need to update more to cover below trace */
/* @Trace: SRS_Os_00097 SRS_Os_80013 SRS_Os_80020 SRS_Os_11013 SRS_Os_80001 SRS_Os_11016 SRS_Os_80021 SRS_Os_80015 SRS_Os_11016 SRS_BSW_00351 SRS_AUTRON_00018 SRS_AUTRON_00021 */
/* polyspace-begin MISRA-C3:20.4 [Justified:Low] "Definition for function redirection does not use parenthesised expression" */
#define GetElapsedCounterValue        GetElapsedValue
#define Os_MeasureCPULoadSlave1       Os_MeasureCPULoad
#define Os_MeasureCPULoadSlave2       Os_MeasureCPULoad
#define Os_MeasureCPULoadSlave3       Os_MeasureCPULoad
#define Os_MeasureCPULoadSlave4       Os_MeasureCPULoad
#define Os_MeasureCPULoadSlave5       Os_MeasureCPULoad
#define Os_OrEventMaskArray           OS_OREVENT_BITMASK_ARRAY
/* polyspace-end MISRA-C3:20.4 [Justified:Low] "Definition for function redirection does not use parenthesised expression" */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_API_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/* @Trace: SRS_BSW_00410 */
#if (OS_TASK == STD_ON)
extern FUNC(StatusType, OS_CODE) ActivateTask(TaskType TaskID);

extern FUNC(void, OS_CODE) ActivateTaskAsyn(TaskType TaskID);

extern FUNC(StatusType, OS_CODE) TerminateTask(void);

extern FUNC(StatusType, OS_CODE) ChainTask(TaskType TaskID);

extern FUNC(StatusType, OS_CODE) GetTaskID(TaskRefType TaskID);

extern FUNC(StatusType, OS_CODE) GetTaskState(TaskType TaskID,
                                                        TaskStateRefType State);
/* @Trace: SRS_Os_00097 */
extern FUNC(StatusType, OS_CODE) Schedule(void);
#endif /* (OS_TASK == STD_ON) */
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
extern FUNC(StatusType, OS_CODE) ReadPeripheral8(AreaIdType Area,
                            P2CONST(uint8, AUTOMATIC, OS_CONST) Address,
                                                      uint8* Readvalue);
extern FUNC(StatusType, OS_CODE) ReadPeripheral16(AreaIdType Area,
                            P2CONST(uint16, AUTOMATIC, OS_CONST) Address,
                                                      uint16* Readvalue);
extern FUNC(StatusType, OS_CODE) ReadPeripheral32(AreaIdType Area,
                            P2CONST(uint32, AUTOMATIC, OS_CONST) Address,
                                                      uint32* Readvalue);
extern FUNC(StatusType, OS_CODE) WritePeripheral8(AreaIdType Area,
                                 P2VAR(uint8, AUTOMATIC, OS_VAR) Address,
                                                       uint8 WriteValue);
extern FUNC(StatusType, OS_CODE) WritePeripheral16(AreaIdType Area,
                                 P2VAR(uint16, AUTOMATIC, OS_VAR) Address,
                                                       uint16 WriteValue);
extern FUNC(StatusType, OS_CODE) WritePeripheral32(AreaIdType Area,
                                 P2VAR(uint32, AUTOMATIC, OS_VAR) Address,
                                                       uint32 WriteValue);
extern FUNC(StatusType, OS_CODE) ModifyPeripheral8(AreaIdType Area,
                                  P2VAR(uint8, AUTOMATIC, OS_VAR) Address,
                                          uint8 Clearmask, uint8 Setmask);
extern FUNC(StatusType, OS_CODE) ModifyPeripheral16(AreaIdType Area,
                                  P2VAR(uint16, AUTOMATIC, OS_VAR) Address,
                                         uint16 Clearmask, uint16 Setmask);
extern FUNC(StatusType, OS_CODE) ModifyPeripheral32(AreaIdType Area,
                                  P2VAR(uint32, AUTOMATIC, OS_VAR) Address,
                                         uint32 Clearmask, uint32 Setmask);
#endif
extern FUNC(void, OS_CODE) ResumeAllInterrupts(void);

extern FUNC(void, OS_CODE) SuspendAllInterrupts(void);

extern FUNC(void, OS_CODE) EnableAllInterrupts(void);

extern FUNC(void, OS_CODE) DisableAllInterrupts(void);

extern FUNC(void, OS_CODE) ResumeOSInterrupts(void);

extern FUNC(void, OS_CODE) SuspendOSInterrupts(void);

#if (OS_CAT2_ISR_COUNT != OS_ZERO)
extern FUNC(StatusType, OS_CODE) EnableInterruptSource(ISRType ISRID,
                                                      boolean ClearPending);

extern FUNC(StatusType, OS_CODE) DisableInterruptSource(ISRType ISRID);

extern FUNC(StatusType, OS_CODE) ClearPendingInterrupt(ISRType ISRID);
#endif

#if (OS_RESOURCE == STD_ON)
extern FUNC(StatusType, OS_CODE) GetResource(ResourceType ResID);

extern FUNC(StatusType, OS_CODE) ReleaseResource(ResourceType ResID);
#endif /* (OS_RESOURCE == STD_ON) */

#if (OS_EVENT == STD_ON)
extern FUNC(StatusType, OS_CODE) SetEvent(TaskType TaskID, EventMaskType Mask);

extern FUNC(void, OS_CODE) SetEventAsyn(TaskType TaskID, EventMaskType Mask);

extern FUNC(StatusType, OS_CODE) ClearEvent(EventMaskType Mask);

extern FUNC(StatusType, OS_CODE) GetEvent(TaskType TaskID,
                                                        EventMaskRefType Event);

extern FUNC(StatusType, OS_CODE) WaitEvent(EventMaskType Mask);
#endif /*(OS_EVENT == STD_ON) */

#if (OS_ALARM == STD_ON)
extern FUNC(StatusType, OS_CODE) GetAlarmBase(AlarmType AlarmID,
                                                         AlarmBaseRefType Info);
extern FUNC(StatusType, OS_CODE) GetAlarm(AlarmType AlarmID, TickRefType Tick);

extern FUNC(StatusType, OS_CODE) SetRelAlarm(AlarmType AlarmID,
                                            TickType Increment, TickType Cycle);

extern FUNC(StatusType, OS_CODE) SetAbsAlarm(AlarmType AlarmID,
                                                TickType Start, TickType Cycle);

extern FUNC(StatusType, OS_CODE) CancelAlarm(AlarmType AlarmID);
#endif /* (OS_ALARM == STD_ON) */

extern FUNC(AppModeType, OS_CODE) GetActiveApplicationMode(void);

extern FUNC(void, OS_CODE) StartOS(AppModeType Mode);

extern FUNC(void, OS_CODE) ShutdownOS(StatusType Error);

#if (OS_PROTECTION_HOOK == STD_ON)
extern FUNC(ProtectionReturnType, OS_CODE) ProtectionHook(
                                                         StatusType Fatalerror);
#endif /* End of if (OS_PROTECTION_HOOK == STD_ON) */

/* @Trace: SRS_Os_00097 */
extern FUNC(void, OS_CODE) ErrorHook(StatusType Error);

/* @Trace: SRS_Os_00097 */
extern FUNC(void, OS_CODE) PreTaskHook(void);

/* @Trace: SRS_Os_00097 */
extern FUNC(void, OS_CODE) PostTaskHook(void);

/* @Trace: SRS_Os_00097 */
extern FUNC(void, OS_CODE) StartupHook(void);

/* @Trace: SRS_Os_00097 */
extern FUNC(void, OS_CODE) ShutdownHook(StatusType Error);

#if (OS_CAT2_ISR_COUNT > OS_ZERO)
extern FUNC(ISRType, OS_CODE)  GetISRID(void);
#endif /* (OS_CAT2_ISR_COUNT > OS_ZERO) */

#if (OS_SCHEDTABLE == STD_ON)
extern FUNC(StatusType, OS_CODE) StartScheduleTableAbs(
                             ScheduleTableType ScheduleTableID, TickType Start);

extern FUNC(StatusType, OS_CODE) StartScheduleTableRel(
                            ScheduleTableType ScheduleTableID, TickType Offset);

extern FUNC(StatusType, OS_CODE) NextScheduleTable(
  ScheduleTableType ScheduleTableID_From, ScheduleTableType ScheduleTableID_To);

extern FUNC(StatusType, OS_CODE) GetScheduleTableStatus(
  ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus);

extern FUNC(StatusType, OS_CODE) StopScheduleTable(
                                            ScheduleTableType ScheduleTableID);
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
extern FUNC(StatusType, OS_CODE) StartScheduleTableSynchron(
                                             ScheduleTableType ScheduleTableID);

extern FUNC(StatusType, OS_CODE) SyncScheduleTable(
                             ScheduleTableType ScheduleTableID, TickType Value);

extern FUNC(StatusType, OS_CODE) SetScheduleTableAsync(
                                             ScheduleTableType ScheduleTableID);
#endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */

#if (OS_COUNTER == STD_ON)
extern FUNC(StatusType, OS_CODE) IncrementCounter(CounterType CounterID);

extern FUNC(StatusType, OS_CODE) GetCounterValue(CounterType CounterID,
  TickRefType Value);

extern FUNC(StatusType, OS_CODE) GetElapsedValue(CounterType CounterID,
  TickRefType Value,
  TickRefType ElapsedValue);
#endif /* (OS_COUNTER == STD_ON) */

#if (OS_SPINLOCK == STD_ON)
extern FUNC(StatusType, OS_CODE) TryToGetSpinlock(SpinlockIdType SpinlockId,
                        P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success);

extern FUNC(StatusType, OS_CODE) GetSpinlock(SpinlockIdType SpinlockId);

extern FUNC(StatusType, OS_CODE) ReleaseSpinlock(SpinlockIdType SpinlockId);
#endif /* End of if (OS_SPINLOCK == STD_ON) */

#if (OS_MULTICORE == STD_ON)
extern FUNC(uint32, OS_CODE) GetNumberOfActivatedCores(void);

extern FUNC(CoreIdType, OS_CODE) GetCoreID(void);

extern FUNC(void, OS_CODE) StartCore(CoreIDType CoreID, StatusType * Status);

extern FUNC(void, OS_CODE) StartNonAutosarCore
                                       (CoreIDType CoreID, StatusType * Status);

extern FUNC(void, OS_CODE) ShutdownAllCores(StatusType Error);
#endif /* End of if (OS_MULTICORE == STD_ON) */

#if (OS_APPLICATION == STD_ON)
extern FUNC(ApplicationType, OS_CODE) GetApplicationID(void);

extern FUNC(ApplicationType, OS_CODE) GetCurrentApplicationID(void);

extern FUNC(ApplicationType, OS_CODE) CheckObjectOwnership(
                           ObjectTypeType ObjectType, ObjectTypeIndex ObjectID);

extern FUNC(StatusType, OS_CODE) AllowAccess(void);

extern FUNC(StatusType, OS_CODE) GetApplicationState(
                    ApplicationType Application, ApplicationStateRefType Value);

extern FUNC(ObjectAccessType, OS_CODE) CheckObjectAccess(
   ApplicationType ApplID, ObjectTypeType ObjectType, ObjectTypeIndex ObjectID);

extern FUNC(StatusType, OS_CODE) TerminateApplication(
                        ApplicationType Application, RestartType RestartOption);

#if (OS_MEMORY_PROTECTION == STD_ON)
extern FUNC(AccessType, OS_CODE) CheckTaskMemoryAccess(TaskType TaskID,
                           MemoryStartAddressType Address, MemorySizeType Size);

extern FUNC(AccessType, OS_CODE) CheckISRMemoryAccess(ISRType ISRID,
                           MemoryStartAddressType Address, MemorySizeType Size);

#if (OS_TRUSTED_FUNC_COUNT != OS_ZERO)
extern FUNC(StatusType, OS_CODE) CallTrustedFunction(TrustedFunctionIndexType
                  FunctionIndex,TrustedFunctionParameterRefType FunctionParams);
#endif /* (OS_TRUSTED_FUNC_COUNT != OS_ZERO) */
#endif /* (OS_MEMORY_PROTECTION == STD_ON) */
#endif /* (OS_APPLICATION == STD_ON) */

#if (OS_APPLICATION == STD_ON)
extern FUNC(Std_ReturnType, OS_CODE) IocRead(uint32 IocID,
                                     P2VAR(void, AUTOMATIC, OS_VAR) data[]);
extern FUNC(Std_ReturnType, OS_CODE) IocWrite(uint32 IocID,
                                CONSTP2CONST(void, AUTOMATIC, OS_CONST) data[]);
extern FUNC(Std_ReturnType, OS_CODE) IocReceive(uint32 IocID,
                                     P2VAR(void, AUTOMATIC, OS_VAR) data[]);
extern FUNC(Std_ReturnType, OS_CODE) IocSend(uint32 IocID,
                                CONSTP2CONST(void, AUTOMATIC, OS_CONST) data[]);
extern FUNC(Std_ReturnType, OS_CODE) IocEmptyQueue(uint32 IocID);
extern FUNC(void, OS_CODE) Os_IocPullCB
         (P2FUNC(void, OS_CONST, pIocPullCB) (void), ApplicationType recvAppID);
#endif

#if (OS_PROFILING_HOOK == STD_ON)
extern FUNC(void, OS_CODE) Os_IsrEntryHook(CoreIDType LddCoreId, ISRType LddIsrId);
extern FUNC(void, OS_CODE) Os_IsrExitHook(CoreIDType LddCoreId, ISRType LddIsrId);
extern FUNC(void, OS_CODE) Os_IsrKillHook(CoreIDType LddCoreId, ISRType LddIsrId);
extern FUNC(void, OS_CODE) Os_TaskActivationHook(CoreIDType LddCoreId, TaskType LddTaskId);
extern FUNC(void, OS_CODE) Os_TaskTerminationHook(CoreIDType LddCoreId, TaskType LddTaskId);
extern FUNC(void, OS_CODE) Os_TaskPreemptionHook(CoreIDType LddCoreId, TaskType LddTaskId);
extern FUNC(void, OS_CODE) Os_TaskRunningHook(CoreIDType LddCoreId, TaskType LddTaskId, TaskStateType LddTaskState);
extern FUNC(void, OS_CODE) Os_TaskWaitingHook(CoreIDType LddCoreId, TaskType LddTaskId);
extern FUNC(void, OS_CODE) Os_TaskReleaseHook(CoreIDType LddCoreId, TaskType LddTaskId);
extern FUNC(void, OS_CODE) Os_TaskKillHook(CoreIDType LddCoreId, TaskType LddTaskId);
extern FUNC(void, OS_CODE) Os_IdleEntryHook(CoreIDType LddCoreId);
extern FUNC(void, OS_CODE) Os_IdleExitHook(CoreIDType LddCoreId);
#endif

extern FUNC(StatusType, OS_CODE) ControlIdle(CoreIDType CoreID, IdleModeType IdleMode);
#define OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /*OS_H_*/

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
