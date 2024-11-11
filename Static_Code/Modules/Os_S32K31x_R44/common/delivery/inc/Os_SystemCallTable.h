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
**  SRC-MODULE: Os_SystemCallTable.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : All the OS services utilize CPU system-call.                  **
**              All the OS services renamed as Os_KernXXX().                  **
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
** 1.5.0     26-Jun-2023   HJ.Kim           Jira CP44-2459                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
**                                          Jira CP44-2017                    **
**                                          Jira CP44-1988                    **
**                                          Jira CP44-1987                    **
**                                          Jira CP44-1772                    **
** 1.4.0     19-Sep-2022   TinHV            Jira CP44-192                     **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.4     07-Jan-2022   TinHV1           R44-Redmine #23444/#23536         **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.2     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C   8.5               **
**                                          Add comment for Misra-C D4.5      **
** 1.0.1     28-Jul-2020   DanhDC1          R44-Redmine #11180                **
**                                          Merge the TryToGetSpinLock() and  **
**                                          GetSpinLock() into one            **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.5 [Justified:Low] "To avoid cross reference, external function is needed." */
/* polyspace-begin MISRA-C3:20.4 [Justified:Low] "Definition for function redirection does not use parenthesised expression" */
/* polyspace-begin MISRA-C3:11.1 [Justified:Low] "For implementation, conversion from function pointer to void pointer is needed to represent function address" */

#ifndef OS_SYSTEMCALLTABLE_H_
#define OS_SYSTEMCALLTABLE_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_Interrupt.h"         /* Os Interrupt header file */
#include "Os_Multicore.h"         /* Os Multicore header file */
#include "Os_Arch_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* Max number of OS service calls */
#define OS_N_SYSCALL   92
/* @Trace: SRS_BSW_00309 */
extern CONSTP2CONST(void, AUTOMATIC, OS_CONST) Os_GaaSyscallTable[OS_N_SYSCALL];
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*
 OSServiceId_GetApplicationID           0
 OSServiceId_GetISRID                   1
 OSServiceId_CallTrustedFunction        2
 OSServiceId_CheckISRMemoryAccess       3
 OSServiceId_CheckTaskMemoryAccess      4
 OSServiceId_CheckObjectAccess          5
 OSServiceId_CheckObjectOwnership       6
*/

/* @Trace: SRS_BSW_00410 */
#if (OS_APPLICATION == STD_ON)
extern FUNC(ApplicationType, OS_CODE) Os_KernGetApplicationID(void);
#else
#define Os_KernGetApplicationID   Os_KernUnknownSyscall
#endif
#if (OS_CAT2_ISR_COUNT > OS_PRE_ZERO)
extern FUNC(ISRType, OS_CODE) Os_KernGetISRID(void);
#else
#define Os_KernGetISRID   Os_KernUnknownSyscall
#endif
#if (OS_TRUSTED_FUNC_COUNT != OS_ZERO)
extern FUNC(StatusType, OS_CODE) Os_KernCallTrustedFunction(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams);
#else
#define Os_KernCallTrustedFunction   Os_KernUnknownSyscall
#endif
#if (OS_SCALABILITY_CLASS >= OS_SC3)
#if (OS_MEMORY_PROTECTION == STD_ON)
extern FUNC(AccessType, OS_CODE) Os_KernCheckISRMemoryAccess(ISRType ISRID,
    MemoryStartAddressType Address, MemorySizeType Size);
extern FUNC(AccessType, OS_CODE) Os_KernCheckTaskMemoryAccess(TaskType TaskID,
    MemoryStartAddressType Address, MemorySizeType Size);
#endif
extern FUNC(ObjectAccessType, OS_CODE) Os_KernCheckObjectAccess(
    ApplicationType ApplID, ObjectTypeType ObjectType,
    ObjectTypeIndex ObjectID);
#else
#define Os_KernCheckISRMemoryAccess    Os_KernUnknownSyscall
#define Os_KernCheckTaskMemoryAccess   Os_KernUnknownSyscall
#define Os_KernCheckObjectAccess       Os_KernUnknownSyscall
#endif

#if (OS_APPLICATION == STD_ON)
extern FUNC(ApplicationType, OS_CODE) Os_KernCheckObjectOwnership(
    ObjectTypeType ObjectType, ObjectTypeIndex ObjectID);
#else
#define Os_KernCheckObjectOwnership    Os_KernUnknownSyscall
#endif

/*
 OSServiceId_StartScheduleTableRel      7
 OSServiceId_StartScheduleTableAbs      8
 OSServiceId_StopScheduleTable          9
 OSServiceId_NextScheduleTable          10
 OSServiceId_StartScheduleTableSynchron 11
 OSServiceId_SyncScheduleTable          12
 OSServiceId_SetScheduleTableAsync      13
 OSServiceId_GetScheduleTableStatus     14
*/
#if (OS_SCHEDTABLE == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_KernStartScheduleTableRel(
    ScheduleTableType ScheduleTableID, TickType Offset);
extern FUNC(StatusType, OS_CODE) Os_KernStartScheduleTableAbs(
    ScheduleTableType ScheduleTableID, TickType Start);
extern FUNC(StatusType, OS_CODE) Os_KernStopScheduleTable(
    ScheduleTableType ScheduleTableID);
extern FUNC(StatusType, OS_CODE) Os_KernNextScheduleTable(
    ScheduleTableType ScheduleTableID_From,
    ScheduleTableType ScheduleTableID_To);
#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_KernStartScheduleTableSynchron(
    ScheduleTableType ScheduleTableID);
extern FUNC(StatusType, OS_CODE) Os_KernSyncScheduleTable(
    ScheduleTableType ScheduleTableID, TickType Value);
extern FUNC(StatusType, OS_CODE) Os_KernSetScheduleTableAsync(
    ScheduleTableType ScheduleTableID);
#else
#define Os_KernStartScheduleTableSynchron   Os_KernUnknownSyscall
#define Os_KernSyncScheduleTable            Os_KernUnknownSyscall
#define Os_KernSetScheduleTableAsync        Os_KernUnknownSyscall
#endif
extern FUNC(StatusType, OS_CODE) Os_KernGetScheduleTableStatus(
    ScheduleTableType ScheduleTableID,
    ScheduleTableStatusRefType ScheduleStatus);
#else
#define Os_KernStartScheduleTableRel        Os_KernUnknownSyscall
#define Os_KernStartScheduleTableAbs        Os_KernUnknownSyscall
#define Os_KernStopScheduleTable            Os_KernUnknownSyscall
#define Os_KernNextScheduleTable            Os_KernUnknownSyscall
#define Os_KernStartScheduleTableSynchron   Os_KernUnknownSyscall
#define Os_KernSyncScheduleTable            Os_KernUnknownSyscall
#define Os_KernSetScheduleTableAsync        Os_KernUnknownSyscall
#define Os_KernGetScheduleTableStatus       Os_KernUnknownSyscall
#endif


/*
 OSServiceId_IncrementCounter           15
 OSServiceId_GetCounterValue            16
 OSServiceId_GetElapsedValue            17
*/
#if (OS_COUNTER == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_KernIncrementCounter(CounterType CounterID);
extern FUNC(StatusType, OS_CODE) Os_KernGetCounterValue(CounterType CounterID,
    TickRefType Value);
extern FUNC(StatusType, OS_CODE) Os_KernGetElapsedValue(CounterType CounterID,
    TickRefType Value, TickRefType ElapsedValue);
#else
#define Os_KernIncrementCounter   Os_KernUnknownSyscall
#define Os_KernGetCounterValue    Os_KernUnknownSyscall
#define Os_KernGetElapsedValue    Os_KernUnknownSyscall
#endif


/*
 OSServiceId_TerminateApplication       18
 OSServiceId_AllowAccess                19
 OSServiceId_GetApplicationState        20
*/
#if (OS_SCALABILITY_CLASS >= OS_SC3)
extern FUNC(StatusType, OS_CODE) Os_KernTerminateApplication(
    ApplicationType Application, RestartType RestartOption);
extern FUNC(StatusType, OS_CODE) Os_KernAllowAccess(void);
extern FUNC(StatusType, OS_CODE) Os_KernGetApplicationState(
    ApplicationType Application, ApplicationStateRefType Value);
#else
#define Os_KernTerminateApplication   Os_KernUnknownSyscall
#define Os_KernAllowAccess            Os_KernUnknownSyscall
#define Os_KernGetApplicationState    Os_KernUnknownSyscall
#endif

/*
 Missing GetNumberOfActivatedCores      21 (See Os_Definition.h)
 Missing GetCoreID                      22 (See Os.c)
 Missing StartCore                      23 (See Os.c)
 Missing StartNonAutosarCore            24 (See Os_Definition.h)
*/

/*
 OSServiceId_GetSpinlock                25
 OSServiceId_ReleaseSpinlock            26
 OSServiceId_TryToGetSpinlock           27
*/
#if (OS_SPINLOCK == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_KernReleaseSpinlock(SpinlockIdType SpinlockId);
extern FUNC(StatusType, OS_CODE) Os_KernTryToGetSpinlock(
    SpinlockIdType SpinlockId, P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success);
#else
#define Os_KernReleaseSpinlock    Os_KernUnknownSyscall
#define Os_KernTryToGetSpinlock   Os_KernUnknownSyscall
#endif

/*
 OSServiceId_ShutdownAllCores           28
 */
#if (OS_MULTICORE == STD_ON)
extern FUNC(void, OS_CODE) Os_KernShutdownAllCores(StatusType Error);
#else
#define Os_KernShutdownAllCores      Os_KernUnknownSyscall
#endif

/*
 OSServiceId_ControlIdle                29
*/
extern FUNC(StatusType, OS_CODE) Os_KernControlIdle(CoreIDType CoreID, IdleModeType IdleMode);


/*
 OSServiceId_IocSend                    30
 OSServiceId_IocWrite                   31
 OSServiceId_UnknownSyscall             32
 OSServiceId_UnknownSyscall             33
 OSServiceId_IocReceive                 34
 OSServiceId_IocRead                    35
 OSServiceId_UnknownSyscall             36
 OSServiceId_UnknownSyscal              37
 OSServiceId_IocEmptyQueue              38
*/
#if (OS_APPLICATION == STD_ON)
extern FUNC(Std_ReturnType, OS_CODE) Os_KernIocRead(uint32 IocID,
                                     P2VAR(uint32, AUTOMATIC, OS_VAR) data[]);
extern FUNC(Std_ReturnType, OS_CODE) Os_KernIocWrite(uint32 IocID,
                                CONSTP2CONST(uint32, AUTOMATIC, OS_CONST) data[]);
extern FUNC(Std_ReturnType, OS_CODE) Os_KernIocReceive(uint32 IocID,
                                     P2VAR(uint32, AUTOMATIC, OS_VAR) data[]);
extern FUNC(Std_ReturnType, OS_CODE) Os_KernIocSend(uint32 IocID,
                                CONSTP2CONST(uint32, AUTOMATIC, OS_CONST) data[]);
extern FUNC(Std_ReturnType, OS_CODE) Os_KernIocEmptyQueue(uint32 IocID);
#else
#define Os_KernIocRead       Os_KernUnknownSyscall
#define Os_KernIocWrite      Os_KernUnknownSyscall
#define Os_KernIocReceive    Os_KernUnknownSyscall
#define Os_KernIocSend       Os_KernUnknownSyscall
#define Os_KernIocEmptyQueue Os_KernUnknownSyscall
#endif

/*
 OSServiceId_GetCurrentApplicationId    39
*/
#if (OS_APPLICATION == STD_ON)
extern FUNC(ApplicationType, OS_CODE) Os_KernGetCurrentApplicationID(void);
#else
#define Os_KernGetCurrentApplicationID   Os_KernUnknownSyscall
#endif

/*
 OSServiceId_ReadPeripheral8         40
 OSServiceId_ReadPeripheral16        41
 OSServiceId_ReadPeripheral32        42
 OSServiceId_WritePeripheral8        43
 OSServiceId_WritePeripheral16       44
 OSServiceId_WritePeripheral32       45
 OSServiceId_ModifyPeripheral8       46
 OSServiceId_ModifyPeripheral16      47
 OSServiceId_ModifyPeripheral32      53
*/
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
extern FUNC(StatusType, OS_CODE) Os_KernReadPeripheral8(AreaIdType Area,
                P2CONST(uint8, AUTOMATIC, OS_CONST) Address, uint8* Readvalue);
extern FUNC(StatusType, OS_CODE) Os_KernReadPeripheral16(AreaIdType Area,
                P2CONST(uint16, AUTOMATIC, OS_CONST) Address, uint16* Readvalue);
extern FUNC(StatusType, OS_CODE) Os_KernReadPeripheral32(AreaIdType Area,
                P2CONST(uint32, AUTOMATIC, OS_CONST) Address, uint32* Readvalue);
extern FUNC(StatusType, OS_CODE) Os_KernWritePeripheral8(AreaIdType Area,
                    P2VAR(uint8, AUTOMATIC, OS_VAR) Address, uint8 WriteValue);
extern FUNC(StatusType, OS_CODE) Os_KernWritePeripheral16(AreaIdType Area,
                    P2VAR(uint16, AUTOMATIC, OS_VAR) Address, uint16 WriteValue);
extern FUNC(StatusType, OS_CODE) Os_KernWritePeripheral32(AreaIdType Area,
                    P2VAR(uint32, AUTOMATIC, OS_VAR) Address, uint32 WriteValue);
extern FUNC(StatusType, OS_CODE) Os_KernModifyPeripheral8(AreaIdType Area,
     P2VAR(uint8, AUTOMATIC, OS_VAR) Address, uint8 Clearmask, uint8 Setmask);
extern FUNC(StatusType, OS_CODE) Os_KernModifyPeripheral16(AreaIdType Area,
     P2VAR(uint16, AUTOMATIC, OS_VAR) Address, uint16 Clearmask, uint16 Setmask);
extern FUNC(StatusType, OS_CODE) Os_KernModifyPeripheral32(AreaIdType Area,
     P2VAR(uint32, AUTOMATIC, OS_VAR) Address, uint32 Clearmask, uint32 Setmask);
#else
#define Os_KernReadPeripheral8      Os_KernUnknownSyscall
#define Os_KernReadPeripheral16     Os_KernUnknownSyscall
#define Os_KernReadPeripheral32     Os_KernUnknownSyscall
#define Os_KernWritePeripheral8     Os_KernUnknownSyscall
#define Os_KernWritePeripheral16    Os_KernUnknownSyscall
#define Os_KernWritePeripheral32    Os_KernUnknownSyscall
#define Os_KernModifyPeripheral8    Os_KernUnknownSyscall
#define Os_KernModifyPeripheral16   Os_KernUnknownSyscall
#define Os_KernModifyPeripheral32   Os_KernUnknownSyscall
#endif

/*
  OSServiceId_EnableInterruptSource             48
  OSServiceId_DisableInterruptSource            49
  OSServiceId_ClearPendingInterrupt             50
*/

#if (OS_CAT2_ISR_COUNT != OS_ZERO)
extern FUNC(StatusType, OS_CODE) Os_KernEnableInterruptSource(ISRType ISRID,
                                                      boolean ClearPending);
extern FUNC(StatusType, OS_CODE) Os_KernDisableInterruptSource(ISRType ISRID);
extern FUNC(StatusType, OS_CODE) Os_KernClearPendingInterrupt(ISRType ISRID);
#else
#define Os_KernEnableInterruptSource      Os_KernUnknownSyscall
#define Os_KernDisableInterruptSource     Os_KernUnknownSyscall
#define Os_KernClearPendingInterrupt    Os_KernUnknownSyscall
#endif

/*
 OSServiceId_ActivateTaskAsyn                   51 (Refer to Os_KernActivateTask)
*/

/*
 OSServiceId_SetEventAsyn                       52 (Refer to Os_KernSetEvent)
*/

/* 54 OSServiceId_UnknownSyscall*/
/* 55 OSServiceId_UnknownSyscall*/
#if (OS_MEMORY_PROTECTION == STD_ON)
extern FUNC(void, OS_CODE) Os_ReturnKernelStack(void);/* 56 OSServiceId_UnknownSyscall*/
extern FUNC(void, OS_CODE) Os_ReturnNTISRKernelStack(void); /* 57 OSServiceId_UnknownSyscall*/
#else
#define Os_ReturnKernelStack     Os_KernUnknownSyscall
#define Os_ReturnNTISRKernelStack     Os_KernUnknownSyscall
#endif

/* 58 OSServiceId_UnknownSyscall*/
/* 59 OSServiceId_UnknownSyscall*/
/* 60 OSServiceId_UnknownSyscall*/
/* 61 OSServiceId_UnknownSyscall*/
/* 62 OSServiceId_UnknownSyscall*/

/*
 OSServiceId_Os_IocPullCB               63
 */
#if (OS_APPLICATION == STD_ON)
extern FUNC(void, OS_CODE) Os_KernIocPullCB(
        P2FUNC(void, OS_CONST, pIocPullCB) (void), ApplicationType recvAppID);
#else
#define Os_KernIocPullCB     Os_KernUnknownSyscall
#endif

#if (OS_TASK == STD_ON)
/*
 OSServiceId_Os_ErrorTerminateTask      64
 */
extern FUNC(void, OS_CODE) Os_KernErrorTerminateTask(void);
#else
#define Os_KernErrorTerminateTask     Os_KernUnknownSyscall
#endif

/*
 OSServiceId_ActivateTask               65
 OSServiceId_TerminateTask              66
 OSServiceId_ChainTask                  67
 OSServiceId_Schedule                   68
 OSServiceId_GetTaskID                  69
 OSServiceId_GetTaskState               70
*/
#if (OS_TASK == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_KernActivateTask(TaskType TaskID);
extern FUNC(void, OS_CODE) Os_KernActivateTaskAsyn(TaskType TaskID);
extern FUNC(StatusType, OS_CODE) Os_KernTerminateTask(void);
extern FUNC(StatusType, OS_CODE) Os_KernChainTask(TaskType TaskID);
extern FUNC(StatusType, OS_CODE) Os_KernSchedule(void);
extern FUNC(StatusType, OS_CODE) Os_KernGetTaskID(TaskRefType TaskID);
extern FUNC(StatusType, OS_CODE) Os_KernGetTaskState(TaskType TaskID,
    TaskStateRefType State);
#else
#define Os_KernActivateTask     Os_KernUnknownSyscall
#define Os_KernActivateTaskAsyn Os_KernUnknownSyscall
#define Os_KernTerminateTask    Os_KernUnknownSyscall
#define Os_KernChainTask        Os_KernUnknownSyscall
#define Os_KernSchedule         Os_KernUnknownSyscall
#define Os_KernGetTaskID        Os_KernUnknownSyscall
#define Os_KernGetTaskState     Os_KernUnknownSyscall
#endif

/*
 OSServiceId_EnableAllInterrupts        71
 OSServiceId_DisableAllInterrupts       72
 OSServiceId_ResumeAllInterrupts        73
 OSServiceId_SuspendAllInterrupts       74
 OSServiceId_ResumeOSInterrupts         75
 OSServiceId_SuspendOSInterrupts        76
*/
extern FUNC(void, OS_CODE) Os_KernSuspendInterrupts(OsIntLockType locktype);
extern FUNC(void, OS_CODE) Os_KernResumeInterrupts(OsIntLockType locktype);


/*
 OSServiceId_GetResource                77
 OSServiceId_ReleaseResource            78
*/
#if (OS_RESOURCE == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_KernGetResource(ResourceType ResID);
extern FUNC(StatusType, OS_CODE) Os_KernReleaseResource(ResourceType ResID);
#else
#define Os_KernGetResource       Os_KernUnknownSyscall
#define Os_KernReleaseResource   Os_KernUnknownSyscall
#endif


/*
 OSServiceId_SetEvent                   79
 OSServiceId_ClearEvent                 80
 OSServiceId_GetEvent                   81
 OSServiceId_WaitEvent                  82
*/
#if (OS_EVENT == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_KernSetEvent(TaskType TaskID, EventMaskType Mask);
extern FUNC(void, OS_CODE) Os_KernSetEventAsyn(TaskType TaskID, EventMaskType Mask);
extern FUNC(StatusType, OS_CODE) Os_KernClearEvent(EventMaskType Mask);
extern FUNC(StatusType, OS_CODE) Os_KernGetEvent(TaskType TaskID,
    EventMaskRefType Event);
extern FUNC(StatusType, OS_CODE) Os_KernWaitEvent(EventMaskType Mask);
#else
#define Os_KernSetEvent     Os_KernUnknownSyscall
#define Os_KernSetEventAsyn Os_KernUnknownSyscall
#define Os_KernClearEvent   Os_KernUnknownSyscall
#define Os_KernGetEvent     Os_KernUnknownSyscall
#define Os_KernWaitEvent    Os_KernUnknownSyscall
#endif


/*
 OSServiceId_GetAlarmBase               83
 OSServiceId_GetAlarm                   84
 OSServiceId_SetRelAlarm                85
 OSServiceId_SetAbsAlarm                86
 OSServiceId_CancelAlarm                87
*/
#if (OS_ALARM == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_KernGetAlarmBase(AlarmType AlarmID,
    AlarmBaseRefType Info);
extern FUNC(StatusType, OS_CODE) Os_KernGetAlarm(AlarmType AlarmID,
    TickRefType Tick);
extern FUNC(StatusType, OS_CODE) Os_KernSetRelAlarm(AlarmType AlarmID,
    TickType Increment, TickType Cycle);
extern FUNC(StatusType, OS_CODE) Os_KernSetAbsAlarm(AlarmType AlarmID,
    TickType Start, TickType Cycle);
extern FUNC(StatusType, OS_CODE) Os_KernCancelAlarm(AlarmType AlarmID);
#else
#define Os_KernGetAlarmBase   Os_KernUnknownSyscall
#define Os_KernGetAlarm       Os_KernUnknownSyscall
#define Os_KernSetRelAlarm    Os_KernUnknownSyscall
#define Os_KernSetAbsAlarm    Os_KernUnknownSyscall
#define Os_KernCancelAlarm    Os_KernUnknownSyscall
#endif


/*
 OSServiceId_GetActiveApplicationMode   88
 OSServiceId_StartOS                    89
 OSServiceId_ShutdownOS                 90
*/
extern FUNC(AppModeType, OS_CODE) Os_KernGetActiveApplicationMode(void);
extern FUNC(void, OS_CODE) Os_KernStartOS(AppModeType Mode);
extern FUNC(void, OS_CODE) Os_KernShutdownOS(StatusType Error);

/*
 OSServiceId_UnknownSyscall             91
*/
extern FUNC(void, OS_CODE) Os_KernUnknownSyscall(void);


#endif /* OS_SYSTEMCALLTABLE_H_ */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA-C3:8.5 [Justified:Low] "To avoid cross reference, external function is needed." */
/* polyspace-end MISRA-C3:20.4 [Justified:Low] "Definition for function redirection does not use parenthesised expression" */
/* polyspace-end MISRA-C3:11.1 [Justified:Low] "For implementation, conversion from function pointer to void pointer is needed to represent function address" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

