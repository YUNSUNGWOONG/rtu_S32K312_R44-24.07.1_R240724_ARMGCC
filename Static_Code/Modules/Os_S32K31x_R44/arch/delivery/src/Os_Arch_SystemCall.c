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
**  SRC-MODULE: Os_Arch_SystemCall.c                                          **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of system call specific functionality               **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: Yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.3.0     31-Jan-2024    HJ.Kim       Jira    CP44-4169                    **
** 1.0.0      1-Sep-2023    HJ.Kim       Jira    CP44-2528                    **
**           29-Aug-2023    HJ.Kim       Jira    CP44-2442                    **
**           29-Jun-2023    HJ.Kim       Jira    CP44-2457                    **
** 1.0.2     31-Dec-2022    TinHV        Jira    CP44-856                     **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:11.1:Not a defect:Justify with annotations> To meet the system call interface */
/* polyspace:begin<MISRA-C3:11.4:Not a defect:Justify with annotations> To meet the system call interface */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> To meet system call interface */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_SystemCallTable.h"
#include "Os_Arch_SystemCall.h"
#include "Os_Arch_Interrupt.h"
#include "Os_Arch_Ram.h"
#include "Os_Arch_Except.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/* @Trace: SRS_BSW_00410 */
#if (OS_ALARM == STD_ON)
/* function for GetAlarmBase() system call */
FUNC(StatusType, OS_CODE) Os_SystemCallGetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace: SafeOs_SUD_API_30801 */
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(AlarmID, (uint32)Info, (uint32)0, \
                                                                (uint32)0, (uint32)0, (uint32)Os_KernGetAlarmBase);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_30802 */
    LddStatusReturn = Os_KernGetAlarmBase(AlarmID, Info);
  }
  /* @Trace: SafeOs_SUD_API_30803 */
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for GetAlarm() system call */
FUNC(StatusType, OS_CODE) Os_SystemCallGetAlarm(AlarmType AlarmID,  TickRefType Tick)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace: SafeOs_SUD_API_30901 */
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(AlarmID, (uint32)Tick, (uint32)0, (uint32)0, \
                                                                                (uint32)0, (uint32)Os_KernGetAlarm);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_30902 */
    LddStatusReturn = Os_KernGetAlarm(AlarmID, Tick);
  }
  /* @Trace: SafeOs_SUD_API_30903 */
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for SetRelAlarm() system call */
FUNC(StatusType, OS_CODE) Os_SystemCallSetRelAlarm(AlarmType AlarmID, TickType Increment, TickType Cycle)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace: SafeOs_SUD_API_31001 */
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(AlarmID, Increment, Cycle, \
                                                                      (uint32)0, (uint32)0, (uint32)Os_KernSetRelAlarm);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_31002 */
    LddStatusReturn = Os_KernSetRelAlarm(AlarmID, Increment, Cycle);
  }
  /* @Trace: SafeOs_SUD_API_31003 */
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for SetAbsAlarm() system call */
FUNC(StatusType, OS_CODE) Os_SystemCallSetAbsAlarm(AlarmType AlarmID, TickType Start, TickType Cycle)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace: SafeOs_SUD_API_31101 */
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(AlarmID, Start, Cycle, \
                                                                     (uint32)0, (uint32)0, (uint32)Os_KernSetAbsAlarm);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_31102 */
    LddStatusReturn = Os_KernSetAbsAlarm(AlarmID, Start, Cycle);
  }
  /* @Trace: SafeOs_SUD_API_31103 */
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for CancelAlarm() system call */
FUNC(StatusType, OS_CODE) Os_SystemCallCanCelAlarm(AlarmType AlarmID)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace: SafeOs_SUD_API_31201 */
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(AlarmID, (uint32)0, (uint32)0, \
                                                         (uint32)0, (uint32)0, (uint32)Os_KernCancelAlarm);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_31202 */
    LddStatusReturn = Os_KernCancelAlarm(AlarmID);
  }
  /* @Trace: SafeOs_SUD_API_31203 */
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}
#endif /* (OS_ALARM == STD_ON) */

#if (OS_APPLICATION == STD_ON)
/* function for GetApplicationID() system call */
ApplicationType Os_SystemCallGetApplicationID(void)
{
  Os_OldLevel_T LddOldIntVal;
  ApplicationType LddApplicationID = INVALID_OSAPPLICATION;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_51201*/
    LddApplicationID = Os_CallFuncKernelStack((uint32)0, (uint32)0, (uint32)0, \
                                              (uint32)0, (uint32)0, (uint32)Os_KernGetApplicationID);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_51202*/
    LddApplicationID = Os_KernGetApplicationID();
  }
  /* @Trace:  SafeOs_SUD_API_51203*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddApplicationID;
}

/* function for GetCurrentApplicationID() system call */
ApplicationType Os_SystemCallGetCurrentApplicationID(void)
{
  Os_OldLevel_T LddOldIntVal;
  ApplicationType LddApplicationID = INVALID_OSAPPLICATION;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_50801*/
    LddApplicationID = Os_CallFuncKernelStack((uint32)0, (uint32)0, (uint32)0, \
                                              (uint32)0, (uint32)0, (uint32)Os_KernGetCurrentApplicationID);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_50802*/
    LddApplicationID = Os_KernGetCurrentApplicationID();
  }
  /* @Trace:  SafeOs_SUD_API_50803*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddApplicationID;
}

/* function for CheckObjectOwnership() system call */
ApplicationType Os_SystemCallCheckObjectOwnership(ObjectTypeType ObjectType, ObjectTypeIndex ObjectID)
{
  Os_OldLevel_T LddOldIntVal;
  ApplicationType LddApplicationID = INVALID_OSAPPLICATION;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_50701*/
    LddApplicationID = Os_CallFuncKernelStack((uint32)ObjectType, ObjectID, (uint32)0, \
                                                       (uint32)0, (uint32)0, (uint32)Os_KernCheckObjectOwnership);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_50702*/
    LddApplicationID = Os_KernCheckObjectOwnership(ObjectType, ObjectID);
  }
  /* @Trace:  SafeOs_SUD_API_50703*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddApplicationID;
}

#if (OS_SCALABILITY_CLASS >= OS_SC3)
/* function for CheckObjectAccess() system call */
ObjectAccessType Os_SystemCallCheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType, ObjectTypeIndex ObjectID)
{
  Os_OldLevel_T LddOldIntVal;
  ObjectAccessType LddAccessReturn = NO_ACCESS;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_50901*/
    LddAccessReturn = (ObjectAccessType)Os_CallFuncKernelStack(ApplID, (uint32)ObjectType, ObjectID, \
                                                                  (uint32)0, (uint32)0, (uint32)Os_KernCheckObjectAccess);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_50902*/
    LddAccessReturn = Os_KernCheckObjectAccess(ApplID, ObjectType, ObjectID);
  }
  /* @Trace:  SafeOs_SUD_API_50903*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddAccessReturn;
}

/* function for TerminateApplication() system call */
StatusType Os_SystemCallTerminateApplication(ApplicationType Application, RestartType RestartOption)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_50501*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(Application, RestartOption, (uint32)0, \
                                                            (uint32)0, (uint32)0, (uint32)Os_KernTerminateApplication);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_50502*/
    LddStatusReturn = Os_KernTerminateApplication(Application, RestartOption);
  }
  /* @Trace:  SafeOs_SUD_API_50503*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for AllowAccess() system call */
StatusType Os_SystemCallAllowAccess(void)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_54101*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack((uint32)0, (uint32)0, (uint32)0, \
                                                         (uint32)0, (uint32)0, (uint32)Os_KernAllowAccess);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_54102*/
    LddStatusReturn = Os_KernAllowAccess();
  }
  /* @Trace:  SafeOs_SUD_API_54103*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for GetApplicationState() system call */
StatusType Os_SystemCallGetApplicationState(ApplicationType Application, ApplicationStateRefType Value)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_54401*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(Application, (uint32)Value, (uint32)0, \
                                                          (uint32)0, (uint32)0, (uint32)Os_KernGetApplicationState);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_54402*/
    LddStatusReturn = Os_KernGetApplicationState(Application, Value);
  }
  /* @Trace:  SafeOs_SUD_API_54403*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}
#endif /* (OS_SCALABILITY_CLASS >= OS_SC3) */
#endif /* OS_APPLICATION*/

#if (OS_MEMORY_PROTECTION == STD_ON)
#if (OS_TRUSTED_FUNC_COUNT != OS_ZERO)
/* function for CallTrustedFunction() system call */
StatusType  Os_SystemCallCallTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_54501*/
    /* polyspace-begin MISRA-C3:11.6 [Justified:Medium] "To handle function parameter type" */
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(FunctionIndex, (uint32)FunctionParams, (uint32)0, \
                                                                 (uint32)0, (uint32)0, (uint32)Os_KernCallTrustedFunction);
    /* polyspace-end MISRA-C3:11.6 [Justified:Medium] "To handle function parameter type" */
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_54502*/
    LddStatusReturn = Os_KernCallTrustedFunction(FunctionIndex, FunctionParams);
  }
  /* @Trace:  SafeOs_SUD_API_54503*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}
#endif /* (OS_TRUSTED_FUNC_COUNT != OS_ZERO) */

/* function for CheckISRMemoryAccess() system call */
AccessType Os_SystemCallCheckISRMemoryAccess(ISRType IsrID, MemoryStartAddressType Address, MemorySizeType Size)
{
  Os_OldLevel_T LddOldIntVal;
  AccessType LddAccessReturn = NO_ACCESS;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_54601*/
    LddAccessReturn = (AccessType)Os_CallFuncKernelStack(IsrID, (uint32)Address, Size, \
                                                         (uint32)0, (uint32)0, (uint32)Os_KernCheckISRMemoryAccess);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_54602*/
    LddAccessReturn = Os_KernCheckISRMemoryAccess(IsrID, Address, Size);
  }
  /* @Trace:  SafeOs_SUD_API_54603*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddAccessReturn;
}

/* function for CheckTaskMemoryAccess() system call */
AccessType Os_SystemCallCheckTaskMemoryAccess(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size)
{
  Os_OldLevel_T LddOldIntVal;
  AccessType LddAccessReturn = NO_ACCESS;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_54701*/
    LddAccessReturn = (AccessType)Os_CallFuncKernelStack(TaskID, (uint32)Address, Size, \
                                                         (uint32)0, (uint32)0, (uint32)Os_KernCheckTaskMemoryAccess);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_54702*/
    LddAccessReturn = Os_KernCheckTaskMemoryAccess(TaskID, Address, Size);
  }
  /* @Trace:  SafeOs_SUD_API_54703*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddAccessReturn;
}
#endif /* (OS_MEMORY_PROTECTION == STD_ON) */

#if (OS_COUNTER == STD_ON)
/* function for IncrementCounter() system call */
StatusType Os_SystemCallIncrementCounter(CounterType CounterID)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_54801*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(CounterID, (uint32)0, (uint32)0, \
                                                          (uint32)0, (uint32)0, (uint32)Os_KernIncrementCounter);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_54802*/
    LddStatusReturn = Os_KernIncrementCounter(CounterID);
  }
  /* @Trace:  SafeOs_SUD_API_54803*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for GetCounterValue() system call */
StatusType Os_SystemCallGetCounterValue(CounterType CounterID, TickRefType Value)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_54901*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(CounterID, (uint32)Value, (uint32)0, \
                                                         (uint32)0, (uint32)0, (uint32)Os_KernGetCounterValue);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_54902*/
    LddStatusReturn = Os_KernGetCounterValue(CounterID, Value);
  }
  /* @Trace:  SafeOs_SUD_API_54903*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for GetElapsedValue() system call */
StatusType Os_SystemCallGetElapsedValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_55001*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(CounterID, (uint32)Value, (uint32)ElapsedValue, \
                                                                   (uint32)0, (uint32)0, (uint32)Os_KernGetElapsedValue);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_55002*/
    LddStatusReturn = Os_KernGetElapsedValue(CounterID, Value, ElapsedValue);
  }
  /* @Trace:  SafeOs_SUD_API_55003*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}
#endif /* (OS_COUNTER == STD_ON) */

#if (OS_EVENT == STD_ON)
/* function for SetEvent() system call */
StatusType Os_SystemCallSetEvent(TaskType TaskID, EventMaskType Mask)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_55101*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(TaskID, (uint32)Mask, (uint32)0, \
                                                                  (uint32)0, (uint32)0, (uint32)Os_KernSetEvent);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_55102*/
    LddStatusReturn = Os_KernSetEvent(TaskID, Mask);
  }
  /* @Trace:  SafeOs_SUD_API_55103*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for SetEventAsyn() system call */
void Os_SystemCallSetEventAsyn(TaskType TaskID, EventMaskType Mask)
{
  Os_OldLevel_T LddOldIntVal;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_55101*/
    (void)Os_CallFuncKernelStack(TaskID, (uint32)Mask, (uint32)0, \
                                                                  (uint32)0, (uint32)0, (uint32)Os_KernSetEventAsyn);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_55102*/
    Os_KernSetEventAsyn(TaskID, Mask);
  }
  /* @Trace:  SafeOs_SUD_API_55103*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
}


/* function for ClearEvent() system call */
StatusType Os_SystemCallClearEvent(EventMaskType Mask)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_55201*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack((uint32)Mask, (uint32)0, (uint32)0, \
                                                            (uint32)0, (uint32)0, (uint32)Os_KernClearEvent);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_55202*/
    LddStatusReturn = Os_KernClearEvent(Mask);
  }
  /* @Trace:  SafeOs_SUD_API_55203*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for GetEvent() system call */
StatusType Os_SystemCallGetEvent(TaskType TaskID, EventMaskRefType Event)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_55301*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(TaskID, (uint32)Event, (uint32)0, \
                                                               (uint32)0, (uint32)0, (uint32)Os_KernGetEvent);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_55302*/
    LddStatusReturn = Os_KernGetEvent(TaskID, Event);
  }
  /* @Trace:  SafeOs_SUD_API_55303*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for WaitEvent() system call */
StatusType Os_SystemCallWaitEvent(EventMaskType Mask)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_55401*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack((uint32)Mask, (uint32)0, (uint32)0, \
                                                            (uint32)0, (uint32)0, (uint32)Os_KernWaitEvent);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_55402*/
    LddStatusReturn = Os_KernWaitEvent(Mask);
  }
  /* @Trace:  SafeOs_SUD_API_55403*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}
#endif /*(OS_EVENT == STD_ON) */

#if (OS_CAT2_ISR_COUNT > OS_PRE_ZERO)
/* function for GetISRID() system call */
ISRType Os_SystemCallGetISRID(void)
{
  Os_OldLevel_T LddOldIntVal;
  ISRType LddIsrId = INVALID_ISR;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_55501*/
    LddIsrId = Os_CallFuncKernelStack((uint32)0, (uint32)0, (uint32)0, \
                                      (uint32)0, (uint32)0, (uint32)Os_KernGetISRID);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_55502*/
    LddIsrId = Os_KernGetISRID();
  }
  /* @Trace:  SafeOs_SUD_API_55503*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddIsrId;
}
#endif

#if (OS_SPINLOCK == STD_ON)
/* function for ReleaseSpinlock() system call */
StatusType  Os_SystemCallReleaseSpinlock(SpinlockIdType SpinlockId)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_55601*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(SpinlockId, (uint32)0, (uint32)0, \
                                                              (uint32)0, (uint32)0, (uint32)Os_KernReleaseSpinlock);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_55602*/
    LddStatusReturn = Os_KernReleaseSpinlock(SpinlockId);
  }
  /* @Trace:  SafeOs_SUD_API_55603*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for TryToGetSpinlock() system call */
StatusType Os_SystemCallTryToGetSpinlock(SpinlockIdType SpinlockId,  P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_55701*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(SpinlockId, (uint32)Success, (uint32)0, \
                                                                  (uint32)0, (uint32)0, (uint32)Os_KernTryToGetSpinlock);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_55702*/
    LddStatusReturn = Os_KernTryToGetSpinlock(SpinlockId, Success);
  }
  /* @Trace:  SafeOs_SUD_API_55703*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}
#endif /* End of if (OS_SPINLOCK == STD_ON) */

#if (OS_MULTICORE == STD_ON)
/* function for ShutdownAllCores() system call */
void Os_SystemCallShutdownAllCores(StatusType Error)
{
  Os_OldLevel_T LddOldIntVal;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_55801*/
    (void)Os_CallFuncKernelStack((uint32)Error, (uint32)0, (uint32)0, \
                                          (uint32)0, (uint32)0, (uint32)Os_KernShutdownAllCores);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_55802*/
    Os_KernShutdownAllCores(Error);
  }
  /* @Trace:  SafeOs_SUD_API_55803*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
}
#endif /* End of if (OS_MULTICORE == STD_ON) */

/* function for GetActiveApplicationMode() system call */
AppModeType Os_SystemCallGetActiveApplicationMode(void)
{
  Os_OldLevel_T LddOldIntVal;
  AppModeType LddApplicationMode = OSDEFAULTAPPMODE;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_55901*/
    LddApplicationMode = Os_CallFuncKernelStack((uint32)0, (uint32)0, (uint32)0, \
                                                (uint32)0, (uint32)0, (uint32)Os_KernGetActiveApplicationMode);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_55902*/
    LddApplicationMode = Os_KernGetActiveApplicationMode();
  }
  /* @Trace:  SafeOs_SUD_API_55903*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddApplicationMode;
}

/* function for StartOS() system call */
/* polyspace +2 MISRA-C3:D4.5 [Not a defect:Low] "Unique in OS name space" */
void Os_SystemCallStartOS(AppModeType Mode)
{
  Os_OldLevel_T LddOldIntVal;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> check status */
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_56001*/
    (void)Os_CallFuncKernelStack(Mode, (uint32)0, (uint32)0, \
                                               (uint32)0, (uint32)0, (uint32)Os_KernStartOS);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_56002*/
    Os_KernStartOS(Mode);
  }
  /* polyspace:end<RTE:UNR> */
  /* @Trace:  SafeOs_SUD_API_56003*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
}

/* function for ShutdownOS() system call */
void Os_SystemCallShutdownOS(StatusType Error)
{
  Os_OldLevel_T LddOldIntVal;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_56101*/
    (void)Os_CallFuncKernelStack((uint32)Error, (uint32)0, (uint32)0, \
                                                (uint32)0, (uint32)0, (uint32)Os_KernShutdownOS);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_56102*/
    Os_KernShutdownOS(Error);
  }
  /* @Trace:  SafeOs_SUD_API_56103*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
}

#if (OS_RESOURCE == STD_ON)
/* function for GetResource() system call */
StatusType Os_SystemCallGetResource(ResourceType ResID)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_56201*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(ResID, (uint32)0, (uint32)0, \
                                                           (uint32)0, (uint32)0, (uint32)Os_KernGetResource);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_56202*/
    LddStatusReturn = Os_KernGetResource(ResID);
  }
  /* @Trace:  SafeOs_SUD_API_56203*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for ReleaseResource() system call */
StatusType Os_SystemCallReleaseResource(ResourceType ResID)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_56301*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(ResID, (uint32)0, (uint32)0, \
                                                         (uint32)0, (uint32)0, (uint32)Os_KernReleaseResource);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_56302*/
    LddStatusReturn = Os_KernReleaseResource(ResID);
  }
  /* @Trace:  SafeOs_SUD_API_56303*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}
#endif /* (OS_RESOURCE == STD_ON) */

#if (OS_SCHEDTABLE == STD_ON)
/* function for StartScheduleTableRel() system call */
StatusType Os_SystemCallStartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    
    /* @Trace:  SafeOs_SUD_API_56401*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(ScheduleTableID, Offset, (uint32)0, \
                                                               (uint32)0, (uint32)0, (uint32)Os_KernStartScheduleTableRel);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_56402*/
    LddStatusReturn = Os_KernStartScheduleTableRel(ScheduleTableID, Offset);
  }
  /* @Trace:  SafeOs_SUD_API_56403*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for StartScheduleTableAbs() system call */
StatusType Os_SystemCallStartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Start)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_56501*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(ScheduleTableID, Start, (uint32)0, \
                                                                (uint32)0, (uint32)0, (uint32)Os_KernStartScheduleTableAbs);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_56502*/
    LddStatusReturn = Os_KernStartScheduleTableAbs(ScheduleTableID, Start);
  }
  /* @Trace:  SafeOs_SUD_API_56503*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for StopScheduleTable() system call */
StatusType Os_SystemCallStopScheduleTable(ScheduleTableType ScheduleTableID)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_56601*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(ScheduleTableID, (uint32)0, (uint32)0, \
                                                               (uint32)0, (uint32)0, (uint32)Os_KernStopScheduleTable);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_56602*/
    LddStatusReturn = Os_KernStopScheduleTable(ScheduleTableID);
  }
  /* @Trace:  SafeOs_SUD_API_56603*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for NextScheduleTable() system call */
StatusType Os_SystemCallNextScheduleTable(ScheduleTableType ScheduleTableID_From, ScheduleTableType ScheduleTableID_To)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_56701*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(ScheduleTableID_From, ScheduleTableID_To, (uint32)0, \
                                                                             (uint32)0, (uint32)0, (uint32)Os_KernNextScheduleTable);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_56702*/
    LddStatusReturn = Os_KernNextScheduleTable(ScheduleTableID_From, ScheduleTableID_To);
  }
  /* @Trace:  SafeOs_SUD_API_56703*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
/* function for StartScheduleTableSynchron() system call */
StatusType Os_SystemCallStartScheduleTableSynchron(ScheduleTableType ScheduleTableID)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_56801*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(ScheduleTableID, (uint32)0, (uint32)0, \
                                                              (uint32)0, (uint32)0, (uint32)Os_KernStartScheduleTableSynchron);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_56802*/
    LddStatusReturn = Os_KernStartScheduleTableSynchron(ScheduleTableID);
  }
  /* @Trace:  SafeOs_SUD_API_56803*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for SyncScheduleTable() system call */
StatusType Os_SystemCallSyncScheduleTable(ScheduleTableType ScheduleTableID, TickType Value)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_56901*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(ScheduleTableID, Value, (uint32)0, \
                                                                (uint32)0, (uint32)0, (uint32)Os_KernSyncScheduleTable);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_56902*/
    LddStatusReturn = Os_KernSyncScheduleTable(ScheduleTableID, Value);
  }
  /* @Trace:  SafeOs_SUD_API_56903*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for SetScheduleTableAsync() system call */
StatusType Os_SystemCallSetScheduleTableAsync(ScheduleTableType ScheduleTableID)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_57001*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(ScheduleTableID, (uint32)0, (uint32)0, \
                                                         (uint32)0, (uint32)0, (uint32)Os_KernSetScheduleTableAsync);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_57002*/
    LddStatusReturn = Os_KernSetScheduleTableAsync(ScheduleTableID);
  }
  /* @Trace:  SafeOs_SUD_API_57003*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}
#endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */

/* function for GetScheduleTableStatus() system call */
StatusType Os_SystemCallGetScheduleTableStatus(ScheduleTableType ScheduleTableID,  ScheduleTableStatusRefType ScheduleStatus)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_57101*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(ScheduleTableID, (uint32)ScheduleStatus, (uint32)0, \
                                                                 (uint32)0, (uint32)0, (uint32)Os_KernGetScheduleTableStatus);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_57102*/
    LddStatusReturn = Os_KernGetScheduleTableStatus(ScheduleTableID, ScheduleStatus);
  }
  /* @Trace:  SafeOs_SUD_API_57103*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

#if (OS_TASK == STD_ON)
/* function for ActivateTask() system call */
StatusType Os_SystemCallActivateTask(TaskType TaskID)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_57201*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(TaskID, (uint32)0, (uint32)0, \
                                                            (uint32)0, (uint32)0, (uint32)Os_KernActivateTask);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_57202*/
    LddStatusReturn = Os_KernActivateTask(TaskID);
  }
  /* @Trace:  SafeOs_SUD_API_57203*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for ActivateTaskAsyn() system call */
void Os_SystemCallActivateTaskAsyn(TaskType TaskID)
{
  Os_OldLevel_T LddOldIntVal;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_57201*/
    (void)Os_CallFuncKernelStack(TaskID, (uint32)0, (uint32)0, \
                                                            (uint32)0, (uint32)0, (uint32)Os_KernActivateTaskAsyn);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_57202*/
    Os_KernActivateTaskAsyn(TaskID);
  }
  /* @Trace:  SafeOs_SUD_API_57203*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

}

/* function for TerminateTask() system call */
StatusType Os_SystemCallTerminateTask(void)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_57301*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack((uint32)0, (uint32)0, (uint32)0, \
                                                         (uint32)0, (uint32)0, (uint32)Os_KernTerminateTask);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_57302*/
    LddStatusReturn = Os_KernTerminateTask();
  }
  /* @Trace:  SafeOs_SUD_API_57303*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for ChainTask() system call */
StatusType Os_SystemCallChainTask(TaskType TaskID)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_57401*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(TaskID, (uint32)0, (uint32)0, \
                                                        (uint32)0, (uint32)0, (uint32)Os_KernChainTask);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_57402*/
    LddStatusReturn = Os_KernChainTask(TaskID);
  }
  /* @Trace:  SafeOs_SUD_API_57403*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for Schedule() system call */
StatusType Os_SystemCallSchedule(void)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_57501*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack((uint32)0, (uint32)0, (uint32)0, \
                                                          (uint32)0, (uint32)0, (uint32)Os_KernSchedule);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_57502*/
    LddStatusReturn = Os_KernSchedule();
  }
  /* @Trace:  SafeOs_SUD_API_57503*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for GetTaskID() system call */
StatusType Os_SystemCallGetTaskID(TaskRefType TaskID)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_57601*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack((uint32)TaskID, (uint32)0, (uint32)0, \
                                                          (uint32)0, (uint32)0, (uint32)Os_KernGetTaskID);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_57602*/
    LddStatusReturn = Os_KernGetTaskID(TaskID);
  }
  /* @Trace:  SafeOs_SUD_API_57603*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for GetTaskState() system call */
StatusType Os_SystemCallGetTaskState(TaskType TaskID, TaskStateRefType State)
{
  Os_OldLevel_T LddOldIntVal;
  StatusType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_57701*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(TaskID, (uint32)State, (uint32)0, \
                                                             (uint32)0, (uint32)0, (uint32)Os_KernGetTaskState);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_57702*/
    LddStatusReturn = Os_KernGetTaskState(TaskID, State);
  }
  /* @Trace:  SafeOs_SUD_API_57703*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}
#endif /* (OS_TASK == STD_ON) */

#if (OS_MULTICORE == STD_ON)
/* function for GetCoreID() system call */
CoreIdType Os_SystemCallGetCoreID(void)
{
  Os_OldLevel_T LddOldIntVal;
  CoreIdType LddCoreID = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_57801*/
    LddCoreID = (StatusType)Os_CallFuncKernelStack((uint32)0, (uint32)0, (uint32)0, \
                                                          (uint32)0, (uint32)0, (uint32)Os_KernGetCoreID);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_57802*/
    LddCoreID = Os_KernGetCoreID();
  }
  /* @Trace:  SafeOs_SUD_API_57803*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddCoreID;
}
#endif /* End of if (OS_MULTICORE == STD_ON) */

#if (OS_APPLICATION == STD_ON)
/* function for IocRead() system call */
Std_ReturnType Os_SystemCallIocRead(uint32 IocID, P2VAR(uint32, AUTOMATIC, OS_VAR) data[])
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_57901*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(IocID, (uint32)data, (uint32)0, \
                                                                  (uint32)0, (uint32)0, (uint32)Os_KernIocRead);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_57902*/
    LddStatusReturn = Os_KernIocRead(IocID, (uint32 **)data);
  }
  /* @Trace:  SafeOs_SUD_API_57903*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for IocWrite() system call */
Std_ReturnType Os_SystemCallIocWrite(uint32 IocID, CONSTP2CONST(uint32, AUTOMATIC, OS_CONST) data[])
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_58001*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(IocID, (uint32)data, (uint32)0, \
                                                                (uint32)0, (uint32)0, (uint32)Os_KernIocWrite);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_58002*/
    LddStatusReturn = Os_KernIocWrite(IocID, (const uint32* const*)data);
  }
  /* @Trace:  SafeOs_SUD_API_58003*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for IocReceive() system call */
Std_ReturnType Os_SystemCallIocReceive(uint32 IocID, P2VAR(uint32, AUTOMATIC, OS_VAR) data[])
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_58101*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(IocID, (uint32)data, (uint32)0, \
                                                             (uint32)0, (uint32)0, (uint32)Os_KernIocReceive);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_58102*/
    LddStatusReturn = Os_KernIocReceive(IocID, data);
  }
  /* @Trace:  SafeOs_SUD_API_58103*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for IocSend() system call */
Std_ReturnType Os_SystemCallIocSend(uint32 IocID, CONSTP2CONST(uint32, AUTOMATIC, OS_CONST) data[])
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_58201*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(IocID, (uint32)data, (uint32)0, \
                                                                       (uint32)0, (uint32)0, (uint32)Os_KernIocSend);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_58202*/
    LddStatusReturn = Os_KernIocSend(IocID, (const uint32* const*)data);
  }
  /* @Trace:  SafeOs_SUD_API_58203*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for IocEmptyQueue() system call */
Std_ReturnType Os_SystemCallIocEmptyQueue(uint32 IocID)
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_58301*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(IocID, (uint32)0, (uint32)0, \
                                                              (uint32)0, (uint32)0, (uint32)Os_KernIocEmptyQueue);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_58302*/
    LddStatusReturn = Os_KernIocEmptyQueue(IocID);
  }
  /* @Trace:  SafeOs_SUD_API_58303*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);

  return LddStatusReturn;
}

/* function for IocPullCB() system call */
void Os_SystemCallIocPullCB(P2FUNC(void, OS_CONST, pIocPullCB) (void), ApplicationType recvAppID)
{
  Os_OldLevel_T LddOldIntVal;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_58401*/
    (void)Os_CallFuncKernelStack((uint32)pIocPullCB, recvAppID, (uint32)0, \
                                                     (uint32)0, (uint32)0, (uint32)Os_KernIocPullCB);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_58402*/
    Os_KernIocPullCB(pIocPullCB, recvAppID);
  }
  /* @Trace:  SafeOs_SUD_API_58403*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
}
#endif /* (OS_APPLICATION == STD_ON) */
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
/* function for ReadPeripheral8() system call */
Std_ReturnType Os_SystemCallReadPeripheral8(AreaIdType Area, \
                      P2CONST(uint8, AUTOMATIC, OS_CONST) Address, \
                      uint8* Readvalue)
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_58501*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(Area, (uint32)Address, (uint32)Readvalue, (uint32)0, \
                                                                                      (uint32)0, (uint32)Os_KernReadPeripheral8);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_58502*/
    LddStatusReturn = (StatusType)Os_KernReadPeripheral8(Area, Address, Readvalue);
  }
  /* @Trace:  SafeOs_SUD_API_58503*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
  return LddStatusReturn;
}
/* function for ReadPeripheral16() system call */
Std_ReturnType Os_SystemCallReadPeripheral16(AreaIdType Area, \
                      P2CONST(uint16, AUTOMATIC, OS_CONST) Address, \
                      uint16* Readvalue)
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_58601*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(Area, (uint32)Address, (uint32)Readvalue, (uint32)0, \
                                                                                      (uint32)0, (uint32)Os_KernReadPeripheral16);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_58602*/
    LddStatusReturn = (StatusType)Os_KernReadPeripheral16(Area, Address, Readvalue);
  }
  /* @Trace:  SafeOs_SUD_API_58603*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
  return LddStatusReturn;
}

/* function for ReadPeripheral32() system call */
Std_ReturnType Os_SystemCallReadPeripheral32(AreaIdType Area, \
                      P2CONST(uint32, AUTOMATIC, OS_CONST) Address, \
                      uint32* Readvalue)
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_58701*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(Area, (uint32)Address, (uint32)Readvalue, (uint32)0, \
                                                                                      (uint32)0, (uint32)Os_KernReadPeripheral32);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_58702*/
    LddStatusReturn = (StatusType)Os_KernReadPeripheral32(Area, Address, Readvalue);
  }
  /* @Trace:  SafeOs_SUD_API_58703*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
  return LddStatusReturn;
}

/* function for WritePeripheral8() system call */
Std_ReturnType Os_SystemCallWritePeripheral8(AreaIdType Area, \
                      P2VAR(uint8, AUTOMATIC, OS_VAR) Address, \
                      uint8 WriteValue)
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_58801*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(Area, (uint32)Address, (uint32)WriteValue, (uint32)0, \
                                                                                      (uint32)0, (uint32)Os_KernWritePeripheral8);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_58802*/
    LddStatusReturn = (StatusType)Os_KernWritePeripheral8(Area, Address, WriteValue);
  }
  /* @Trace:  SafeOs_SUD_API_58803*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
  return LddStatusReturn;
}

/* function for WritePeripheral16() system call */
Std_ReturnType Os_SystemCallWritePeripheral16(AreaIdType Area, \
                      P2VAR(uint16, AUTOMATIC, OS_VAR) Address, \
                      uint16 WriteValue)
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_58901*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(Area, (uint32)Address, (uint32)WriteValue, (uint32)0, \
                                                                                      (uint32)0, (uint32)Os_KernWritePeripheral16);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_58902*/
    LddStatusReturn = (StatusType)Os_KernWritePeripheral16(Area, Address, WriteValue);
  }
  /* @Trace:  SafeOs_SUD_API_58903*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
  return LddStatusReturn;
}

/* function for WritePeripheral32() system call */
Std_ReturnType Os_SystemCallWritePeripheral32(AreaIdType Area, \
                      P2VAR(uint32, AUTOMATIC, OS_VAR) Address, \
                      uint32 WriteValue)
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_59001*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(Area, (uint32)Address, WriteValue, (uint32)0, \
                                                                                      (uint32)0, (uint32)Os_KernWritePeripheral32);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_59002*/
    LddStatusReturn = (StatusType)Os_KernWritePeripheral32(Area, Address, WriteValue);
  }
  /* @Trace:  SafeOs_SUD_API_59003*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
  return LddStatusReturn;
}

/* function for ModifyPeripheral8() system call */
Std_ReturnType Os_SystemCallModifyPeripheral8(AreaIdType Area, \
                      P2VAR(uint8, AUTOMATIC, OS_VAR) Address, \
                      uint8 Clearmask, uint8 Setmask)
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_59101*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(Area, (uint32)Address, (uint32)Clearmask, (uint32)Setmask, \
                                                                               (uint32)0, (uint32)Os_KernModifyPeripheral8);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_59102*/
    LddStatusReturn = (StatusType)Os_KernModifyPeripheral8(Area, Address, Clearmask, Setmask);
  }
  /* @Trace:  SafeOs_SUD_API_59103*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
  return LddStatusReturn;
}

/* function for ModifyPeripheral16() system call */
Std_ReturnType Os_SystemCallModifyPeripheral16(AreaIdType Area, \
                      P2VAR(uint16, AUTOMATIC, OS_VAR) Address, \
                      uint16 Clearmask, uint16 Setmask)
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_59201*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(Area, (uint32)Address, (uint32)Clearmask, (uint32)Setmask, \
                                                                         (uint32)0, (uint32)Os_KernModifyPeripheral16);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_59202*/
    LddStatusReturn = (StatusType)Os_KernModifyPeripheral16(Area, Address, Clearmask, Setmask);
  }
  /* @Trace:  SafeOs_SUD_API_59203*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
  return LddStatusReturn;
}

/* function for ModifyPeripheral32() system call */
Std_ReturnType Os_SystemCallModifyPeripheral32(AreaIdType Area, \
                      P2VAR(uint32, AUTOMATIC, OS_VAR) Address, \
                      uint32 Clearmask, uint32 Setmask)
{
  Os_OldLevel_T LddOldIntVal;
  Std_ReturnType LddStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_59301*/
    LddStatusReturn = (StatusType)Os_CallFuncKernelStack(Area, (uint32)Address, Clearmask, Setmask, \
                                                                         (uint32)0, (uint32)Os_KernModifyPeripheral32);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_59302*/
    LddStatusReturn = (StatusType)Os_KernModifyPeripheral32(Area, Address, Clearmask, Setmask);
  }
  /* @Trace:  SafeOs_SUD_API_59303*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
  return LddStatusReturn;
}
#endif /* (OS_PERIPHERAL == STD_ON) */

/* function for ReturnKernelStack() system call */
void Os_SystemCallReturnKernelStack(void)
{
  Os_OldLevel_T LddOldIntVal;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_59401*/
    (void)Os_CallFuncKernelStack((uint32)0, (uint32)0, (uint32)0, (uint32)0, (uint32)0, (uint32)Os_ReturnKernelStack);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_59402*/
    /* polyspace +1 MISRA-C3:2.2[justified:low] "The content of external API which will be called in assembly"*/
    Os_ReturnKernelStack();
  }
  /* @Trace:  SafeOs_SUD_API_59403*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
}

/* function for ReturnNTISRKernelStack() system call */
void Os_SystemCallReturnNTISRKernelStack(void)
{
  Os_OldLevel_T LddOldIntVal;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LddOldIntVal = OS_DISABLE_AND_SAVE_INTERRUPTS();
  if((Os_GucNestingCAT2ISR[OS_CORE_ID] != OS_ZERO) && (Os_GucInKernel[OS_CORE_ID] == OS_ZERO))
  {
    /* @Trace:  SafeOs_SUD_API_59501*/
    (void)Os_CallFuncKernelStack((uint32)0, (uint32)0, (uint32)0, (uint32)0, (uint32)0, (uint32)Os_ReturnNTISRKernelStack);
  }
  else
  {
    /* @Trace:  SafeOs_SUD_API_59502*/
    /* polyspace +1 MISRA-C3:2.2[justified:low] "The content of external API which will be called in assembly"*/
    Os_ReturnNTISRKernelStack();
  }
  /* @Trace:  SafeOs_SUD_API_59503*/
  OS_RESTORE_INTERRUPTS(LddOldIntVal);
}
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C3:11.1:Not a defect:Justify with annotations> To meet the system call interface */
/* polyspace:end<MISRA-C3:11.4:Not a defect:Justify with annotations> To meet the system call interface */
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> To meet system call interface */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
