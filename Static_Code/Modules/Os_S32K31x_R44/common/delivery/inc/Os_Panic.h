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
**  SRC-MODULE: Os_Panic.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for declaration of OS internal error functions.   **
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
**           26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

#ifndef OS_PANIC_H_
#define OS_PANIC_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
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
/* polyspace +1 MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */
#define OS_PANIC(x)       (Os_Panic(x))

/* Panic codes
*/
enum Os_Panic_E
{
  OS_PANIC_NONE = 0,
  OS_PANIC_ASSERT,

  /* Problems detected at startup
   */
  OS_PANIC_InsufficientHeap,
  OS_PANIC_InsufficientPageMaps,
  OS_PANIC_SyncArrayCorrupted,
  OS_PANIC_AmbiguousApplicationMode,

  /* Problems detected at runtime
   */
  OS_PANIC_SlaveSlotNotOccupied,
  OS_PANIC_TaskIsNotInPriorityQueue,
  OS_PANIC_PriorityQueueAlreadyFull,
  OS_PANIC_InvalidTaskState,
  OS_PANIC_InvalidAlarmState,
  OS_PANIC_IsrCannotBeKilled,
  OS_PANIC_HookCannotBeKilled,
  OS_PANIC_UnhandledNmi,
  OS_PANIC_IncorrectKernelNesting,

  /* Problems detected during startup consistency checks
   */
  OS_PANIC_SCHK_KernAssemblerOffsetsAreIncorrect,
  OS_PANIC_SCHK_NonPowerOfTwoTimerWraparoundNotSupported,
  OS_PANIC_SCHK_TimerMaxDeltaAndDefDeltaInconsistent,
  OS_PANIC_SCHK_CounterRangeLowerThanHardwareTimer,
  OS_PANIC_SCHK_TaskIdIsNotIndexInTaskTable,
  OS_PANIC_SCHK_TaskWithRunPrioLowerThanQueuePrio,
  OS_PANIC_SCHK_NonPremptiveTaskWithLowRunPrio,
  OS_PANIC_SCHK_ExtendedTaskInBasicConformanceClass,
  OS_PANIC_SCHK_ExtendedTaskWithMultipleActivations,
  OS_PANIC_SCHK_MultipleActivationsInConformanceClass1,
  OS_PANIC_SCHK_TaskWithMeasureExecButNoAccountingStructure,
  OS_PANIC_SCHK_TaskWithExecTimeLimitButNoAccountingStructure,
  OS_PANIC_SCHK_TaskWithOsIntLockTimeLessThanAllIntLockTime,
  OS_PANIC_SCHK_TaskAssemblerOffsetsAreIncorrect,
  OS_PANIC_SCHK_IncorrectNumberOfPriorityQueues,
  OS_PANIC_SCHK_ZeroEntriesInPriorityQueue,
  OS_PANIC_SCHK_SingleEntryQueueWithDynamicVariables,
  OS_PANIC_SCHK_MultipleEntryQueueInConformanceClass1,
  OS_PANIC_SCHK_MultipleEntryQueueWithNoDynamicVariables,
  OS_PANIC_SCHK_IncorrectNumberOfEntriesInPriorityQueue,
  OS_PANIC_SCHK_OverlappingPriorityQueuesFound,
  OS_PANIC_SCHK_PriorityQueueEntriesOutOfBounds,
  OS_PANIC_SCHK_GapInPriorityQueuesFound,
  OS_PANIC_SCHK_PrioritySlotsArrayHasWrongSize,
  OS_PANIC_SCHK_IncorrectMasterPriorityBitAssignment,
  OS_PANIC_SCHK_IncorrectSlavePriorityBitAssignment,
  OS_PANIC_SCHK_AppIdIsNotIndexInAppTable,
  OS_PANIC_SCHK_AppConfigurationIdMismatch,
  OS_PANIC_SCHK_AppRestartTaskNotMemberOfApp,
  OS_PANIC_SCHK_AppHasNoPermissions,
  OS_PANIC_SCHK_AppPermissionBitNotUnique,
  OS_PANIC_SCHK_AppPermissionBitSystem,
  OS_PANIC_SCHK_OwningApplicationHasNoPermission,
  OS_PANIC_SCHK_IsrWithMeasureExecButNoAccountingStructure,
  OS_PANIC_SCHK_IsrWithExecTimeLimitButNoAccountingStructure,
  OS_PANIC_SCHK_IsrWithOsIntLockTimeLessThanAllIntLockTime,
  OS_PANIC_SCHK_ScheduleTableActivateTaskAfterSetEvent,
  OS_PANIC_SCHK_ScheduleTableEventsNotInOrder,
  OS_PANIC_SCHK_DelayGreaterThanCounterMax,
  OS_PANIC_SCHK_DelayPlusMaxIncreaseGreaterThanCounterMax,
  OS_PANIC_SCHK_MaxDecreaseGreaterThanDelay,
  OS_PANIC_SCHK_SynchronisationRangeGreaterThanScheduleTableLength,

  /* Problems detected at multi-core scheduling
   */
  OS_PANIC_InterCoreMessageQueueIndexInvalid,
  OS_PANIC_InterCoreMessageQueueOverflow,
  OS_PANIC_InterCoreMessageQueueUnderflow,
  OS_PANIC_InterCoreMessageIndexInvalid,
  OS_PANIC_InterCoreMessageOpcodeInvalid,
  OS_PANIC_InterCoreMessageResultNotReady,
  OS_PANIC_InterCoreMessageResultNotSet,

  OS_PANIC_UNKNOWN    /* Must be last */
};


typedef enum Os_Panic_E Os_Panic_T;

/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_Panic_T, OS_VAR) Os_GenPanicCode;
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
extern FUNC(void, OS_CODE) Os_Panic(Os_Panic_T panicCode);

/* @Trace: SRS_BSW_00411 */
#define OS_DEBUG                        STD_ON
#if defined (OS_DEBUG)
#if (OS_DEBUG == STD_ON)
/* polyspace-begin RTE:UNR [Not a defect:Low] "Defensive programming purpose" */
OS_LOCAL_INLINE FUNC(void, OS_CODE) OS_ASSERT(boolean LblExpression)
{
  if (LblExpression == OS_TRUE)
  {
    /* Nothing todo */
  }
  else
  {
    Os_Panic(OS_PANIC_ASSERT);
  }
}
/* polyspace-end RTE:UNR [Not a defect:Low] "Defensive programming purpose" */
#else
#define OS_ASSERT(x)
#endif
#endif /* defined (OS_DEBUG) */

#endif /* OS_PANIC_H_ */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
