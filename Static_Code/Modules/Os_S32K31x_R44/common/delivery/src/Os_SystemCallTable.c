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
**  SRC-MODULE: Os_SystemCall_Table.c                                         **
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
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.5.0     26-Jun-2023   HJ.Kim           Jira CP44-2459                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
**                                          Jira CP44-2005                    **
** 1.4.0     19-Sep-2022   TinHV            Jira CP44-192                     **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.1     28-Jul-2020   DanhDC1          R44-Redmine #11180                **
**                                          Merge the TryToGetSpinLock() and  **
**                                          GetSpinLock() into one            **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace-begin MISRA-C3:11.1 [Justified:Low] "For implementation, conversion from function pointer to void pointer is needed to represent function address" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
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
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
CONSTP2CONST(void, AUTOMATIC, OS_CONST) Os_GaaSyscallTable[OS_N_SYSCALL] =
{
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetApplicationID), /* 0 OSServiceId_GetApplicationID*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetISRID), /* 1 OSServiceId_GetISRID*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernCallTrustedFunction),  /* 2 OSServiceId_CallTrustedFunction*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernCheckISRMemoryAccess), /* 3 OSServiceId_CheckISRMemoryAccess*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernCheckTaskMemoryAccess),  /* 4 OSServiceId_CheckTaskMemoryAccess*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernCheckObjectAccess),  /* 5 OSServiceId_CheckObjectAccess*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernCheckObjectOwnership), /* 6 OSServiceId_CheckObjectOwnership*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernStartScheduleTableRel),  /* 7 OSServiceId_StartScheduleTableRel*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernStartScheduleTableAbs),  /* 8 OSServiceId_StartScheduleTableAbs*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernStopScheduleTable),  /* 9 OSServiceId_StopScheduleTable*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernNextScheduleTable),  /* 10 OSServiceId_NextScheduleTable*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernStartScheduleTableSynchron), /* 11 OSServiceId_StartScheduleTableSynchron*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernSyncScheduleTable),  /* 12 OSServiceId_SyncScheduleTable*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernSetScheduleTableAsync),  /* 13 OSServiceId_SetScheduleTableAsync*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetScheduleTableStatus), /* 14 OSServiceId_GetScheduleTableStatus*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernIncrementCounter), /* 15 OSServiceId_IncrementCounter*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetCounterValue),  /* 16 OSServiceId_GetCounterValue*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetElapsedValue),  /* 17 OSServiceId_GetElapsedValue*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernTerminateApplication), /* 18 OSServiceId_TerminateApplication*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernAllowAccess),  /* 19 OSServiceId_AllowAccess*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetApplicationState),  /* 20 OSServiceId_GetApplicationState*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall), /* 21 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetCoreID),  /* 22 OSServiceId_GetCoreID*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall),  /* 23 OSServiceId_StartCore*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall),  /* 24 OSServiceId_StartNonAutosarCore*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernTryToGetSpinlock),  /* 25 OSServiceId_GetSpinlock*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernReleaseSpinlock),  /* 26 OSServiceId_ReleaseSpinlock*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernTryToGetSpinlock), /* 27 OSServiceId_TryToGetSpinlock*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernShutdownAllCores), /* 28 OSServiceId_ShutdownAllCores*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernControlIdle),  /* 29 OSServiceId_ControlIdle*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernIocSend),  /* 30 OSServiceId_IocSend*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernIocWrite), /* 31 OSServiceId_IocWrite*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall), /* 32 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall), /* 33 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernIocReceive), /* 34 OSServiceId_IocReceive*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernIocRead),  /* 35 OSServiceId_IocRead*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall), /* 36 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall), /* 37 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernIocEmptyQueue),  /* 38 OSServiceId_IocEmptyQueue*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetCurrentApplicationID),  /* 39 OSServiceId_GetCurrentApplicationID*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernReadPeripheral8),  /* 40 OSServiceId_ReadPeripheral8*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernReadPeripheral16),  /* 41 OSServiceId_ReadPeripheral16*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernReadPeripheral32),  /* 42 OSServiceId_ReadPeripheral32*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernWritePeripheral8), /* 43 OSServiceId_WritePeripheral8*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernWritePeripheral16), /* 44 OSServiceId_WritePeripheral16*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernWritePeripheral32), /* 45 OSServiceId_WritePeripheral32*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernModifyPeripheral8),  /* 46 OSServiceId_ModifyPeripheral8*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernModifyPeripheral16),  /* 47 OSServiceId_ModifyPeripheral16*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernDisableInterruptSource), /* 48 OSServiceId_DisableInterruptSource*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernEnableInterruptSource),  /* 49 OSServiceId_EnableInterruptSource*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernClearPendingInterrupt),  /* 50 OSServiceId_ClearPendingInterrupt*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernActivateTaskAsyn), /* 51 OSServiceId_ActivateTaskAsyn*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernSetEventAsyn), /* 52 OSServiceId_SetEventAsyn*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernModifyPeripheral32),  /* 53 OSServiceId_ModifyPeripheral32*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall), /* 54 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall), /* 55 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_ReturnKernelStack), /* 56 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_ReturnNTISRKernelStack), /* 57 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall), /* 58 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall), /* 59 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall), /* 60 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall), /* 61 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall), /* 62 OSServiceId_UnknownSyscall*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernIocPullCB),  /* 63 OSServiceId_IocPullCB*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernErrorTerminateTask), /* 64 OSServiceId_ErrorTerminateTask*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernActivateTask), /* 65 OSServiceId_ActivateTask*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernTerminateTask),  /* 66 OSServiceId_TerminateTask*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernChainTask),  /* 67 OSServiceId_ChainTask*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernSchedule), /* 68 OSServiceId_Schedule*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetTaskID),  /* 69 OSServiceId_GetTaskID*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetTaskState), /* 70 OSServiceId_GetTaskState*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernResumeInterrupts), /* 71 OSServiceId_EnableAllInterrupts*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernSuspendInterrupts),  /* 72 OSServiceId_DisableAllInterrupts*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernResumeInterrupts), /* 73 OSServiceId_ResumeAllInterrupts*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernSuspendInterrupts),  /* 74 OSServiceId_SuspendAllInterrupts*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernResumeInterrupts), /* 75 OSServiceId_ResumeOSInterrupts*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernSuspendInterrupts),  /* 76 OSServiceId_SuspendOSInterrupts*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetResource),  /* 77 OSServiceId_GetResource*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernReleaseResource),  /* 78 OSServiceId_ReleaseResource*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernSetEvent), /* 79 OSServiceId_SetEvent*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernClearEvent), /* 80 OSServiceId_ClearEvent*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetEvent), /* 81 OSServiceId_GetEvent*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernWaitEvent),  /* 82 OSServiceId_WaitEvent*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetAlarmBase), /* 83 OSServiceId_GetAlarmBase*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetAlarm), /* 84 OSServiceId_GetAlarm*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernSetRelAlarm),  /* 85 OSServiceId_SetRelAlarm*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernSetAbsAlarm),  /* 86 OSServiceId_SetAbsAlarm*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernCancelAlarm),  /* 87 OSServiceId_CancelAlarm*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernGetActiveApplicationMode), /* 88 OSServiceId_GetActiveApplicationMode*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernStartOS),  /* 89 OSServiceId_StartOS*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernShutdownOS), /* 90 OSServiceId_ShutdownOS*/
  SYSCALLTYPE(void, AUTOMATIC, OS_CONST)(&Os_KernUnknownSyscall) /* 91 OSServiceId_UnknownSyscall*/
};
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Os_KernUnknownSyscall                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function does Nothing                          **
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
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, OS_CODE) Os_KernUnknownSyscall(void)
{

}
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace-end MISRA-C3:11.1 [Justified:Low] "For implementation, conversion from function pointer to void pointer is needed to represent function address" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
