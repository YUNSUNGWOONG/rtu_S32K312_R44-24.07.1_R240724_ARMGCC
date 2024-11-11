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
**  SRC-MODULE: Os_Arch_SystemCall.h                                          **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for S32K31x related (OS) SystemaCall API          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:     Yes                                      **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:  No                                       **
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
**           31-Jan-2024    HJ.Kim       Jira    CP44-4171                    **
** 1.1.1     23-Nov-2023    HJ.Kim       Jira    CP44-3306                    **
** 1.1.0     29-Aug-2023    HJ.Kim       Jira    CP44-1712                    **
**            8-Jun-2023    HJ.Kim       Jira    CP44-2090                    **
**            5-Jul-2023    HJ.Kim       Jira    CP44-2457                    **
** 1.0.2     31-Dec-2022    TinHV        Jira    CP44-856                     **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/
#ifndef OS_ARCH_SYSTEMCALL_H_
#define OS_ARCH_SYSTEMCALL_H_

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Arch_Regs.h"
#include "Os_SystemCallTable.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#if (OS_ALARM == STD_ON)
StatusType Os_SystemCallGetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info);
extern StatusType Os_SystemCallGetAlarm(AlarmType AlarmID,  TickRefType Tick);
extern StatusType Os_SystemCallSetRelAlarm(AlarmType AlarmID, TickType Increment, TickType Cycle);
extern StatusType Os_SystemCallSetAbsAlarm(AlarmType AlarmID, TickType Start, TickType Cycle);
extern StatusType Os_SystemCallCanCelAlarm(AlarmType AlarmID);
#endif
#if ((OS_APPLICATION == STD_ON) && (OS_SCALABILITY_CLASS >= OS_SC3) || (OS_MULTICORE == STD_ON))
/* Inline function for GetApplicationID() system call */
extern ApplicationType Os_SystemCallGetApplicationID(void);
extern ApplicationType Os_SystemCallGetCurrentApplicationID(void);
extern ObjectAccessType Os_SystemCallCheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType, ObjectTypeIndex ObjectID);
extern ApplicationType Os_SystemCallCheckObjectOwnership(ObjectTypeType ObjectType, ObjectTypeIndex ObjectID);
extern StatusType Os_SystemCallTerminateApplication(ApplicationType Application, RestartType RestartOption);
extern StatusType Os_SystemCallAllowAccess(void);
extern StatusType Os_SystemCallGetApplicationState(ApplicationType Application, ApplicationStateRefType Value);
#endif
#if (OS_MEMORY_PROTECTION == STD_ON)
#if (OS_TRUSTED_FUNC_COUNT != OS_ZERO)
extern StatusType Os_SystemCallCallTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
#endif
extern AccessType Os_SystemCallCheckISRMemoryAccess(ISRType IsrID, MemoryStartAddressType Address, MemorySizeType Size);
extern AccessType Os_SystemCallCheckTaskMemoryAccess(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size);
#endif
#if (OS_COUNTER == STD_ON)
extern StatusType Os_SystemCallIncrementCounter(CounterType CounterID);
extern StatusType Os_SystemCallGetCounterValue(CounterType CounterID, TickRefType Value);
extern StatusType Os_SystemCallGetElapsedValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue);
#endif
#if (OS_EVENT == STD_ON)
extern StatusType Os_SystemCallSetEvent(TaskType TaskID, EventMaskType Mask);
extern void Os_SystemCallSetEventAsyn(TaskType TaskID, EventMaskType Mask);
extern StatusType Os_SystemCallClearEvent(EventMaskType Mask);
extern StatusType Os_SystemCallGetEvent(TaskType TaskID, EventMaskRefType Event);
extern StatusType Os_SystemCallWaitEvent(EventMaskType Mask);
#endif
#if (OS_CAT2_ISR_COUNT > OS_PRE_ZERO)
extern ISRType Os_SystemCallGetISRID(void);
#endif
#if (OS_SPINLOCK == STD_ON)
extern StatusType Os_SystemCallReleaseSpinlock(SpinlockIdType SpinlockId);
extern StatusType Os_SystemCallTryToGetSpinlock(SpinlockIdType SpinlockId,  P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success);
#endif
#if (OS_MULTICORE == STD_ON)
extern void Os_SystemCallShutdownAllCores(StatusType Error);
#endif
extern AppModeType Os_SystemCallGetActiveApplicationMode(void);
/* polyspace +2 MISRA-C3:D4.5 [Not a defect:Low] "Unique in OS name space" */
extern void Os_SystemCallStartOS(AppModeType Mode);
extern void Os_SystemCallShutdownOS(StatusType Error);
#if (OS_RESOURCE == STD_ON)
extern StatusType Os_SystemCallGetResource(ResourceType ResID);
extern StatusType Os_SystemCallReleaseResource(ResourceType ResID);
#endif
#if (OS_SCHEDTABLE == STD_ON)
extern StatusType Os_SystemCallStartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset);
extern StatusType Os_SystemCallStartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Start);
extern StatusType Os_SystemCallStopScheduleTable(ScheduleTableType ScheduleTableID);
extern StatusType Os_SystemCallNextScheduleTable(ScheduleTableType ScheduleTableID_From, ScheduleTableType ScheduleTableID_To);
extern StatusType Os_SystemCallStartScheduleTableSynchron(ScheduleTableType ScheduleTableID);
extern StatusType Os_SystemCallSyncScheduleTable(ScheduleTableType ScheduleTableID, TickType Value);
extern StatusType Os_SystemCallSetScheduleTableAsync(ScheduleTableType ScheduleTableID);
extern StatusType Os_SystemCallGetScheduleTableStatus(ScheduleTableType ScheduleTableID,  ScheduleTableStatusRefType ScheduleStatus);
#endif
#if (OS_TASK == STD_ON)
extern StatusType Os_SystemCallActivateTask(TaskType TaskID);
extern void Os_SystemCallActivateTaskAsyn(TaskType TaskID);
extern StatusType Os_SystemCallTerminateTask(void);
extern StatusType Os_SystemCallChainTask(TaskType TaskID);
extern StatusType Os_SystemCallSchedule(void);
extern StatusType Os_SystemCallGetTaskID(TaskRefType TaskID);
extern StatusType Os_SystemCallGetTaskState(TaskType TaskID, TaskStateRefType State);
#endif
#if (OS_MULTICORE == STD_ON)
extern CoreIdType Os_SystemCallGetCoreID(void);
#endif
#if (OS_APPLICATION == STD_ON)
extern Std_ReturnType Os_SystemCallIocRead(uint32 IocID, P2VAR(uint32, AUTOMATIC, OS_VAR) data[]);
extern Std_ReturnType Os_SystemCallIocWrite(uint32 IocID, CONSTP2CONST(uint32, AUTOMATIC, OS_CONST) data[]);
extern Std_ReturnType Os_SystemCallIocReceive(uint32 IocID, P2VAR(uint32, AUTOMATIC, OS_VAR) data[]);
extern Std_ReturnType Os_SystemCallIocSend(uint32 IocID, CONSTP2CONST(uint32, AUTOMATIC, OS_CONST) data[]);
extern Std_ReturnType Os_SystemCallIocEmptyQueue(uint32 IocID);

extern void Os_SystemCallIocPullCB(P2FUNC(void, OS_CONST, pIocPullCB) (void), ApplicationType recvAppID);
#endif
#if (OS_PERIPHERAL == STD_ON)
extern Std_ReturnType Os_SystemCallReadPeripheral8(AreaIdType Area, \
                      P2CONST(uint8, AUTOMATIC, OS_CONST) Address, uint8* Readvalue);
extern Std_ReturnType Os_SystemCallReadPeripheral16(AreaIdType Area, \
                      P2CONST(uint16, AUTOMATIC, OS_CONST) Address, uint16* Readvalue);
extern Std_ReturnType Os_SystemCallReadPeripheral32(AreaIdType Area, \
                      P2CONST(uint32, AUTOMATIC, OS_CONST) Address, uint32* Readvalue);

extern Std_ReturnType Os_SystemCallWritePeripheral8(AreaIdType Area, \
                      P2VAR(uint8, AUTOMATIC, OS_VAR) Address, uint8 WriteValue);
extern Std_ReturnType Os_SystemCallWritePeripheral16(AreaIdType Area, \
                      P2VAR(uint16, AUTOMATIC, OS_VAR) Address, uint16 WriteValue);
extern Std_ReturnType Os_SystemCallWritePeripheral32(AreaIdType Area, \
                      P2VAR(uint32, AUTOMATIC, OS_VAR) Address, uint32 WriteValue);

extern Std_ReturnType Os_SystemCallModifyPeripheral8(AreaIdType Area, \
                      P2VAR(uint8, AUTOMATIC, OS_VAR) Address, uint8 Clearmask, uint8 Setmask);
extern Std_ReturnType Os_SystemCallModifyPeripheral16(AreaIdType Area, \
                      P2VAR(uint16, AUTOMATIC, OS_VAR) Address, uint16 Clearmask, uint16 Setmask);
extern Std_ReturnType Os_SystemCallModifyPeripheral32(AreaIdType Area, \
                      P2VAR(uint32, AUTOMATIC, OS_VAR) Address, uint32 Clearmask, uint32 Setmask);
#endif /* (OS_PERIPHERAL == STD_ON) */
extern void Os_SystemCallReturnKernelStack(void);
extern void Os_SystemCallReturnNTISRKernelStack(void);
/* Definition for dummy return value of syscall */
#define OS_SYSCALL_DUMMY_RETURN OS_ZERO


enum {
    __APSR		= 0,
    __IAPSR		= 1,
    __EAPSR		= 2,
    __XPSR		= 3,
    __IPSR		= 5,
    __EPSR		= 6,
    __IEPSR		= 7,
    __MSP		= 8,
    __PSP		= 9,
    __PRIMASK		= 16,
    __BASEPRI		= 17,
    __BASEPRI_MAX	= 18,
    __FAULTMASK		= 19,
    __CONTROL		= 20
};


void CALLSVC(uint8 svc_number) {
	__asm volatile(
			"mov r0, %0 \n"		// Move the svc_number into R0 register
			"svc 0 \n"			// Execute SVC instruction with the number in R0
			:					// No output operands
			: "r" (svc_number)	// Input operand: SVC number to be placed in R0
			: "r0"				// Clobbered register list
			);
}


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*****************************************************************************
 * Function Name        : Os_CanUseSvc
 *
 * Service ID           : NA
 *
 * Description          : Check whether SVC instruction is available
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : TRUE - SVC available, FALSE - SVC not available
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_CYTXXX_005}
 *
 * @ingroup               OS_CYTXXX_ESDD_005
 ******************************************************************************/
 /* @Trace: SRS_BSW_00330 */
OS_LOCAL_INLINE boolean Os_CanUseSvc(void)
{
  uint32 ipsrRegVal;
  uint32 faultmaskRegVal;
  uint32 primaskRegVal;
  boolean canUseSvc;

//  ipsrRegVal = __MRS(__IPSR);
//  faultmaskRegVal = __MRS(__FAULTMASK);
//  primaskRegVal = __MRS(__PRIMASK);
  __asm("MRS %0, IPSR" : "=r"(ipsrRegVal));
  __asm("MRS %0, FAULTMASK" : "=r"(faultmaskRegVal));
  __asm("MRS %0, PRIMASK" : "=r"(primaskRegVal));


  if ((ipsrRegVal == OS_ZERO) &&      /* Check whether Exception handler */
      (faultmaskRegVal == OS_ZERO) && /* To prevent lockup */
      (primaskRegVal == OS_ZERO))     /* To prevent priority escalation */
  {
    /* @Trace: SafeOs_SUD_API_54001 */
    canUseSvc = TRUE;
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_54002 */
    canUseSvc = FALSE;
  }

  return canUseSvc;
}

#if (OS_ALARM == STD_ON)
/* Inline function for GetAlarmBase() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_GETALARMBASE(AlarmType AlarmID, AlarmBaseRefType Info)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_39501 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetAlarmBase);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_39502 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallGetAlarmBase(AlarmID, Info);
  }
  return LddStatusReturn;
}

/* Inline function for GetAlarm() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_GETALARM(AlarmType AlarmID,  TickRefType Tick)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_39601 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetAlarm);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_39602 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallGetAlarm(AlarmID, Tick);
  }
  return LddStatusReturn;
}

/* Inline function for GetAlarmBase() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_SETRELALARM(AlarmType AlarmID, TickType Increment,
                                                                          TickType Cycle)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_39701 */
    /* Thread Mode */
    CALLSVC(OSServiceId_SetRelAlarm);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_39702 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallSetRelAlarm(AlarmID, Increment, Cycle);
  }
  return LddStatusReturn;
}

/* Inline function for SetAbsAlarm() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_SETABSALARM(AlarmType AlarmID, TickType Start, TickType Cycle)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_39801 */
    /* Thread Mode */
    CALLSVC(OSServiceId_SetAbsAlarm);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_39802 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallSetAbsAlarm(AlarmID, Start, Cycle);
  }
  return LddStatusReturn;
}

/* Inline function for CancelAlarm() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_CANCELALARM(AlarmType AlarmID)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_39901 */
    /* Thread Mode */
    CALLSVC(OSServiceId_CancelAlarm);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_39902 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallCanCelAlarm(AlarmID);
  }
  return LddStatusReturn;
}
#endif /* (OS_ALARM == STD_ON) */

#if (OS_APPLICATION == STD_ON)
/* Inline function for GetApplicationID() system call */
OS_LOCAL_INLINE ApplicationType OS_SYSCALL_GETAPPLICATIONID(void)
{
  ApplicationType LddApplicationID = INVALID_OSAPPLICATION;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_40001 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetApplicationID);
    __asm("mov %0, r0" : "=r" (LddApplicationID) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_40002 */
    /* Handler Mode */
    LddApplicationID = Os_SystemCallGetApplicationID();
  }
  return LddApplicationID;
}

/* Inline function for GetCurrentApplicationID() system call */
OS_LOCAL_INLINE ApplicationType OS_SYSCALL_GETCURRENTAPPLICATIONID(void)
{
  ApplicationType LddApplicationID = INVALID_OSAPPLICATION;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_40101 */
    /* Thread Mode */
  CALLSVC(OSServiceId_GetCurrentApplicationID);
  __asm("mov %0, r0" : "=r" (LddApplicationID) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_40102 */
    /* Handler Mode */
    LddApplicationID = Os_SystemCallGetCurrentApplicationID();
  }
  return LddApplicationID;
}

/* Inline function for CheckObjectOwnership() system call */
OS_LOCAL_INLINE ApplicationType OS_SYSCALL_CHECKOBJECTOWNERSHIP(ObjectTypeType ObjectType, ObjectTypeIndex ObjectID)
{
  ApplicationType LddApplicationID = INVALID_OSAPPLICATION;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_40301 */
    /* Thread Mode */
    CALLSVC(OSServiceId_CheckObjectOwnership);
    __asm("mov %0, r0" : "=r" (LddApplicationID) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_40302 */
    /* Handler Mode */
    LddApplicationID = Os_SystemCallCheckObjectOwnership(ObjectType, ObjectID);
  }
  return LddApplicationID;
}

#if (OS_MEMORY_PROTECTION == STD_ON)
/* Inline function for CheckObjectAccess() system call */
OS_LOCAL_INLINE ObjectAccessType OS_SYSCALL_CHECKOBJECTACCESS(ApplicationType ApplID,
                                                     ObjectTypeType ObjectType,
                                                     ObjectTypeIndex ObjectID)
{
  ObjectAccessType LddAccessReturn = NO_ACCESS;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_40201 */
    /* Thread Mode */
    CALLSVC(OSServiceId_CheckObjectAccess);
    __asm("mov %0, r0" : "=r" (LddAccessReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_40202 */
    /* Handler Mode */
    LddAccessReturn = Os_SystemCallCheckObjectAccess(ApplID, ObjectType, ObjectID);
  }
  return LddAccessReturn;
}

/* Inline function for TerminateApplication() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_TERMINATEAPPLICATION(ApplicationType Application,
                                                  RestartType RestartOption)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_40401 */
    /* Thread Mode */
    CALLSVC(OSServiceId_TerminateApplication);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_40402 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallTerminateApplication(Application, RestartOption);
  }
  return LddStatusReturn;
}

/* Inline function for AllowAccess() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_ALLOWACCESS(void)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_40501 */
    /* Thread Mode */
    CALLSVC(OSServiceId_AllowAccess);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_40502 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallAllowAccess();
  }
  return LddStatusReturn;
}

/* Inline function for GetApplicationState() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_GETAPPLICATIONSTATE(ApplicationType Application,
                                                 ApplicationStateRefType Value)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_40601 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetApplicationState);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_40602 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallGetApplicationState(Application, Value);
  }
  return LddStatusReturn;
}

/* Inline function for CheckISRMemoryAccess() system call */
OS_LOCAL_INLINE AccessType OS_SYSCALL_CHECKISRMEMORYACCESS(ISRType IsrID, MemoryStartAddressType Address, MemorySizeType Size)
{
  AccessType LddAccessReturn = NO_ACCESS;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_40801 */
    /* Thread Mode */
    CALLSVC(OSServiceId_CheckISRMemoryAccess);
    __asm("mov %0, r0" : "=r" (LddAccessReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_40802 */
    /* Handler Mode */
    LddAccessReturn = Os_SystemCallCheckISRMemoryAccess(IsrID, Address, Size);
  }
  return LddAccessReturn;
}

/* Inline function for CheckTaskMemoryAccess() system call */
OS_LOCAL_INLINE AccessType OS_SYSCALL_CHECKTASKMEMORYACCESS(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size)
{
  AccessType LddAccessReturn = NO_ACCESS;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_40901 */
    /* Thread Mode */
    CALLSVC(OSServiceId_CheckTaskMemoryAccess);
    __asm("mov %0, r0" : "=r" (LddAccessReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_40902 */
    /* Handler Mode */
    LddAccessReturn = Os_SystemCallCheckTaskMemoryAccess(TaskID, Address, Size);
  }
  return LddAccessReturn;
}

#if (OS_TRUSTED_FUNC_COUNT != OS_ZERO)
/* Inline function for CallTrustedFunction() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_CALLTRUSTEDFUNCTION(TrustedFunctionIndexType FunctionIndex,
                                                 TrustedFunctionParameterRefType FunctionParams)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_40701 */
    /* Thread Mode */
    CALLSVC(OSServiceId_CallTrustedFunction);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_40702 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallCallTrustedFunction(FunctionIndex, FunctionParams);
  }
  return LddStatusReturn;
}
#endif /* (OS_TRUSTED_FUNC_COUNT != OS_ZERO) */
#endif /* (OS_MEMORY_PROTECTION == STD_ON) */
#endif /* (OS_APPLICATION == STD_ON) */

#if (OS_COUNTER == STD_ON)
/* Inline function for IncrementCounter() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_INCREMENTCOUNTER(CounterType CounterID)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_41001 */
    /* Thread Mode */
    CALLSVC(OSServiceId_IncrementCounter);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_41002 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallIncrementCounter(CounterID);
  }
  return LddStatusReturn;
}

/* Inline function for GetCounterValue() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_GETCOUNTERVALUE(CounterType CounterID, TickRefType Value)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_41101 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetCounterValue);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_41102 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallGetCounterValue(CounterID, Value);
  }
  return LddStatusReturn;
}

/* Inline function for GetElapsedValue() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_GETELAPSEDVALUE(CounterType CounterID,
                                             TickRefType Value,
                                             TickRefType ElapsedValue)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_41201 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetElapsedValue);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_41202 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallGetElapsedValue(CounterID, Value, ElapsedValue);
  }
  return LddStatusReturn;
}
#endif /* (OS_COUNTER == STD_ON) */

#if (OS_EVENT == STD_ON)
/* Inline function for SetEvent() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_SETEVENT(TaskType TaskID, EventMaskType Mask)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_41301 */
    /* Thread Mode */
    CALLSVC(OSServiceId_SetEvent);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_41302 */
    LddStatusReturn = Os_SystemCallSetEvent(TaskID, Mask);
  }
  return LddStatusReturn;
}

/* Inline function for SetEvent() system call */
OS_LOCAL_INLINE void OS_SYSCALL_SETEVENTASYN(TaskType TaskID, EventMaskType Mask)
{
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_41401 */
    /* Thread Mode */
    CALLSVC(OSServiceId_SetEventAsyn);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_41402 */
    (void)Os_SystemCallSetEventAsyn(TaskID, Mask);
  }
}

/* Inline function for ClearEvent() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_CLEAREVENT(EventMaskType Mask)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_41501 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ClearEvent);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_41502 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallClearEvent(Mask);
  }
  return LddStatusReturn;
}

/* Inline function for GetEvent() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_GETEVENT(TaskType TaskID, EventMaskRefType Event)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_41601 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetEvent);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_41602 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallGetEvent(TaskID, Event);
  }
  return LddStatusReturn;
}

/* Inline function for WaitEvent() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_WAITEVENT(EventMaskType Mask)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_41701 */
    /* Thread Mode */
    CALLSVC(OSServiceId_WaitEvent);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_41702 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallWaitEvent(Mask);
  }
  return LddStatusReturn;
}
#endif /*(OS_EVENT == STD_ON) */

/* Inline function for EnableAllInterrupts() system call */
OS_LOCAL_INLINE void OS_SYSCALL_ENABLEALLINTERRUPTS(void)
{
  /* @Trace: SafeOs_SUD_API_41801 */
  /* Thread Mode & non-privilege */
  CALLSVC(OSServiceId_EnableAllInterrupts);
}

/* Inline function for EnableAllInterrupts() system call */
OS_LOCAL_INLINE void OS_SYSCALL_DISABLEALLINTERRUPTS(void)
{
  /* @Trace: SafeOs_SUD_API_41901 */
  /* Thread Mode & non-privilege */
  CALLSVC(OSServiceId_DisableAllInterrupts);
}

/* Inline function for EnableAllInterrupts() system call */
OS_LOCAL_INLINE void OS_SYSCALL_RESUMEALLINTERRUPTS(void)
{
  /* @Trace: SafeOs_SUD_API_42001 */
  /* Thread Mode & non-privilege */
  CALLSVC(OSServiceId_ResumeAllInterrupts);
}

/* Inline function for EnableAllInterrupts() system call */
OS_LOCAL_INLINE void OS_SYSCALL_SUSPENDALLINTERRUPTS(void)
{
  /* @Trace: SafeOs_SUD_API_42101 */
  /* Thread Mode & non-privilege */
  CALLSVC(OSServiceId_SuspendAllInterrupts);
}

/* Inline function for ResumeOSInterrupts() system call */
OS_LOCAL_INLINE void OS_SYSCALL_RESUMEOSINTERRUPTS(void)
{
  /* @Trace: SafeOs_SUD_API_42201 */
  /* Thread Mode & non-privilege */
  CALLSVC(OSServiceId_ResumeOSInterrupts);
}

/* Inline function for SuspendOSInterrupts() system call */
OS_LOCAL_INLINE void OS_SYSCALL_SUSPENDOSINTERRUPTS(void)
{
  /* @Trace: SafeOs_SUD_API_42301 */
  CALLSVC(OSServiceId_SuspendOSInterrupts);
}

#if (OS_CAT2_ISR_COUNT > OS_PRE_ZERO)
/* Inline function for GetISRID() system call */
OS_LOCAL_INLINE ISRType OS_SYSCALL_GETISRID(void)
{
  ISRType isrId = INVALID_ISR;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_42401 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetISRID);
    __asm("mov %0, r0" : "=r" (isrId) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_42402 */
    isrId = Os_SystemCallGetISRID();
  }
  return isrId;
}
#endif

#if (OS_SPINLOCK == STD_ON)
/* Inline function for ReleaseSpinlock() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_RELEASESPINLOCK(SpinlockIdType SpinlockId)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_42501 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ReleaseSpinlock);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_42502 */
    LddStatusReturn = Os_SystemCallReleaseSpinlock(SpinlockId);
  }
  return LddStatusReturn;
}

/* Inline function for TryToGetSpinlock() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_TRYTOGETSPINLOCK(SpinlockIdType SpinlockId,
                                             P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_42601 */
    /* Thread Mode */
    CALLSVC(OSServiceId_TryToGetSpinlock);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_42602 */
    LddStatusReturn = Os_SystemCallTryToGetSpinlock(SpinlockId, Success);
  }
  return LddStatusReturn;
}
#endif /* End of if (OS_SPINLOCK == STD_ON) */

#if (OS_MULTICORE == STD_ON)
/* Inline function for ShutdownAllCores() system call */
OS_LOCAL_INLINE void OS_SYSCALL_SHUTDOWNALLCORES(StatusType Error)
{
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_42701 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ShutdownAllCores);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_42702 */
    Os_SystemCallShutdownAllCores(Error);
  }
}
#endif /* End of if (OS_MULTICORE == STD_ON) */

/* Inline function for GetActiveApplicationMode() system call */
OS_LOCAL_INLINE AppModeType OS_SYSCALL_GETACTIVEAPPLICATIONMODE(void)
{
  AppModeType LddApplicationMode = OSDEFAULTAPPMODE;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_42801 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetActiveApplicationMode);
    __asm("mov %0, r0" : "=r" (LddApplicationMode) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_42802 */
    LddApplicationMode = Os_SystemCallGetActiveApplicationMode();
  }
  return LddApplicationMode;
}

/* Inline function for StartOS() system call */
/* polyspace +2 MISRA-C3:D4.5 [Not a defect:Low] "Unique in OS name space" */
OS_LOCAL_INLINE void OS_SYSCALL_STARTOS(AppModeType Mode)
{
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_42901 */
    /* Thread Mode */
    CALLSVC(OSServiceId_StartOS);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_42902 */
    /* Handler Mode */
    Os_SystemCallStartOS(Mode);
  }
}

/* Inline function for StartOS() system call */
OS_LOCAL_INLINE void OS_SYSCALL_SHUTDOWNOS(StatusType Error)
{
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_43001 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ShutdownOS);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_43002 */
    /* Handler Mode */
    Os_SystemCallShutdownOS(Error);
  }
}

#if (OS_RESOURCE == STD_ON)
/* Inline function for GetResource() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_GETRESOURCE(ResourceType ResID)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_43101 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetResource);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_43102 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallGetResource(ResID);
  }
  return LddStatusReturn;
}

/* Inline function for ReleaseResource() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_RELEASERESOURCE(ResourceType ResID)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_43201 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ReleaseResource);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_43202 */
    LddStatusReturn = Os_SystemCallReleaseResource(ResID);
  }
  return LddStatusReturn;
}
#endif /* (OS_RESOURCE == STD_ON) */

#if (OS_SCHEDTABLE == STD_ON)
/* Inline function for StartScheduleTableRel() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_STARTSCHEDULETABLEREL(ScheduleTableType ScheduleTableID,
                                                   TickType Offset)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_43301 */
    /* Thread Mode */
    CALLSVC(OSServiceId_StartScheduleTableRel);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_43302 */
    LddStatusReturn = Os_SystemCallStartScheduleTableRel(ScheduleTableID, Offset);
  }
  return LddStatusReturn;
}

/* Inline function for StartScheduleTableAbs() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_STARTSCHEDULETABLEABS(ScheduleTableType ScheduleTableID,
                                                   TickType Start)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_43401 */
    /* Thread Mode */
    CALLSVC(OSServiceId_StartScheduleTableAbs);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_43402 */
    LddStatusReturn = Os_SystemCallStartScheduleTableAbs(ScheduleTableID, Start);
  }
  return LddStatusReturn;
}

/* Inline function for StopScheduleTable() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_STOPSCHEDULETABLE(ScheduleTableType ScheduleTableID)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_43501 */
    /* Thread Mode */
    CALLSVC(OSServiceId_StopScheduleTable);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_43502 */
    LddStatusReturn = Os_SystemCallStopScheduleTable(ScheduleTableID);
  }
  return LddStatusReturn;
}

/* Inline function for NextScheduleTable() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_NEXTSCHEDULETABLE(ScheduleTableType ScheduleTableID_From,
                                               ScheduleTableType ScheduleTableID_To)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_43601 */
    /* Thread Mode */
    CALLSVC(OSServiceId_NextScheduleTable);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_43602 */
    LddStatusReturn = Os_SystemCallNextScheduleTable(ScheduleTableID_From, ScheduleTableID_To);
  }
  return LddStatusReturn;
}

#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
/* Inline function for StartScheduleTableSynchron() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_STARTSCHEDULETABLESYNCHRON(ScheduleTableType ScheduleTableID)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_43701 */
    /* Thread Mode */
    CALLSVC(OSServiceId_StartScheduleTableSynchron);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_43702 */
    LddStatusReturn = Os_SystemCallStartScheduleTableSynchron(ScheduleTableID);
  }
  return LddStatusReturn;
}

/* Inline function for OSServiceId_SyncScheduleTable() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_SYNCSCHEDULETABLE(ScheduleTableType ScheduleTableID,
                                                                          TickType Value)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_43801 */
    /* Thread Mode */
    CALLSVC(OSServiceId_SyncScheduleTable);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_43802 */
    LddStatusReturn = Os_SystemCallSyncScheduleTable(ScheduleTableID, Value);
  }
  return LddStatusReturn;
}

/* Inline function for SetScheduleTableAsync() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_SETSCHEDULETABLEASYNC(ScheduleTableType ScheduleTableID)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_43901 */
    /* Thread Mode */
    CALLSVC(OSServiceId_SetScheduleTableAsync);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_43902 */
    LddStatusReturn = Os_SystemCallSetScheduleTableAsync(ScheduleTableID);
  }
  return LddStatusReturn;
}
#endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */

/* Inline function for GetScheduleTableStatus() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_GETSCHEDULETABLESTATUS(ScheduleTableType ScheduleTableID,
                                                    ScheduleTableStatusRefType ScheduleStatus)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_44001 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetScheduleTableStatus);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_44002 */
    LddStatusReturn = Os_SystemCallGetScheduleTableStatus(ScheduleTableID, ScheduleStatus);
  }
  return LddStatusReturn;
}
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

#if (OS_TASK == STD_ON)
/* Inline function for ActivateTask() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_ACTIVATETASK(TaskType TaskID)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_44101 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ActivateTask);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_44102 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallActivateTask(TaskID);
  }
  return LddStatusReturn;
}

/* Inline function for ActivateTask() system call */
OS_LOCAL_INLINE void OS_SYSCALL_ACTIVATETASKASYN(TaskType TaskID)
{
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_44101 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ActivateTaskAsyn);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_44102 */
    /* Handler Mode */
    Os_SystemCallActivateTaskAsyn(TaskID);
  }
}

/* Inline function for TerminateTask() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_TERMINATETASK(void)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_44301 */
    /* Thread Mode */
    CALLSVC(OSServiceId_TerminateTask);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_44302 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallTerminateTask();
  }
  return LddStatusReturn;
}

/* Inline function for ChainTask() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_CHAINTASK(TaskType TaskID)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_44401 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ChainTask);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_44402 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallChainTask(TaskID);
  }
  return LddStatusReturn;
}

/* Inline function for Schedule() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_SCHEDULE(void)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_44501 */
    /* Thread Mode */
    CALLSVC(OSServiceId_Schedule);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_44502 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallSchedule();
  }
  return LddStatusReturn;
}

/* Inline function for GetTaskID() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_GETTASKID(TaskRefType TaskID)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_44601 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetTaskID);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_44602 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallGetTaskID(TaskID);
  }
  return LddStatusReturn;
}

/* Inline function for GetTaskState() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_GETTASKSTATE(TaskType TaskID, TaskStateRefType State)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_44701 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetTaskState);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_44702 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallGetTaskState(TaskID, State);
  }
  return LddStatusReturn;
}
#endif /* (OS_TASK == STD_ON) */

#if (OS_MULTICORE == STD_ON)
/* Inline function for GetCoreID() system call */
OS_LOCAL_INLINE CoreIdType OS_SYSCALL_GETCOREID(void)
{
  CoreIdType LddCoreID = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_44801 */
    /* Thread Mode */
    CALLSVC(OSServiceId_GetCoreID);
    __asm("mov %0, r0" : "=r" (LddCoreID) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_44802 */
    /* Handler Mode */
    LddCoreID = Os_SystemCallGetCoreID();
  }
  return LddCoreID;
}
#endif /* End of if (OS_MULTICORE == STD_ON) */

#if (OS_APPLICATION == STD_ON)
/* Inline function for IocRead() system call */
OS_LOCAL_INLINE Std_ReturnType OS_SYSCALL_IOCREAD(uint32 IocID,
                                              P2VAR(void, AUTOMATIC, OS_VAR) data[])
{
  Std_ReturnType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_44901 */
    /* Thread Mode */
    CALLSVC(IOCServiceId_IOC_Read);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_44902 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallIocRead(IocID, (uint32 **)data);
  }
  return LddStatusReturn;
}

/* Inline function for IocWrite() system call */
OS_LOCAL_INLINE Std_ReturnType OS_SYSCALL_IOCWRITE(uint32 IocID,
                                         CONSTP2CONST(void, AUTOMATIC, OS_CONST) data[])
{
  Std_ReturnType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_45001 */
    /* Thread Mode */
    CALLSVC(IOCServiceId_IOC_Write);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_45002 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallIocWrite(IocID, (const uint32* const *)data);
  }
  return LddStatusReturn;
}

/* Inline function for IocReceive() system call */
OS_LOCAL_INLINE Std_ReturnType OS_SYSCALL_IOCRECEIVE(uint32 IocID,
                                              P2VAR(void, AUTOMATIC, OS_VAR) data[])
{
  Std_ReturnType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_45101 */
    /* Thread Mode */
    CALLSVC(IOCServiceId_IOC_Receive);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_45102 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallIocReceive(IocID, (uint32 **)data);
  }
  return LddStatusReturn;
}

/* Inline function for IocSend() system call */
OS_LOCAL_INLINE Std_ReturnType OS_SYSCALL_IOCSEND(uint32 IocID,
                                         CONSTP2CONST(void, AUTOMATIC, OS_CONST) data[])
{
  Std_ReturnType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_45201 */
    /* Thread Mode */
    CALLSVC(IOCServiceId_IOC_Send);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_45202 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallIocSend(IocID, (const uint32* const*)data);
  }
  return LddStatusReturn;
}

/* Inline function for IocSend() system call */
OS_LOCAL_INLINE Std_ReturnType OS_SYSCALL_IOCEMPTYQUEUE(uint32 IocID)
{
  Std_ReturnType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_45301 */
    /* Thread Mode */
    CALLSVC(IOCServiceId_IOC_EmptyQueue);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_45302 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallIocEmptyQueue(IocID);
  }
  return LddStatusReturn;
}

/* Inline function for Os_IocPullCB() system call */
OS_LOCAL_INLINE void OS_SYSCALL_IOCPULLCB(P2FUNC(void, OS_CONST, pIocPullCB)(void),
                                 ApplicationType recvAppID)
{
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_45401 */
    /* Thread Mode */
    CALLSVC(OSServiceId_Os_IocPullCB);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_45402 */
    /* Handler Mode */
    Os_SystemCallIocPullCB(pIocPullCB, recvAppID);
  }
}
#endif /* (OS_APPLICATION == STD_ON)*/

/* Inline function for Os_ErrorTerminateTask() system call */
OS_LOCAL_INLINE void OS_SYSCALL_ERRORTERMINATETASK(void)
{
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_45501 */
    /* Thread Mode */
    CALLSVC(OSServiceId_Os_ErrorTerminateTask);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_45502 */
    /* Do nothing */
  }
}
OS_LOCAL_INLINE Std_ReturnType OS_SYSCALL_CONTROLIDLE(CoreIDType CoreID, IdleModeType IdleMode)
{
  boolean canUseSvc;
  Std_ReturnType LddStatusReturn = E_OK;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_45601 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ControlIdle);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_45602 */
    LddStatusReturn = Os_KernControlIdle(CoreID, IdleMode);
  }
  
  return LddStatusReturn;

}
#if(OS_CAT2_ISR_COUNT > OS_ZERO)
OS_LOCAL_INLINE StatusType OS_SYSCALL_ENABLEINTERRUPTSOURCE(ISRType ISRID,
                                            boolean ClearPending)
{
  boolean canUseSvc;
  StatusType LddStatusReturn = E_OK;
  
  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
  /* @Trace: SafeOs_SUD_API_45701 */
  /* Thread Mode */
    CALLSVC(OSServiceId_EnableInterruptSource);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_45702 */
    LddStatusReturn = Os_KernEnableInterruptSource(ISRID, ClearPending);
  }

  return LddStatusReturn;
}

OS_LOCAL_INLINE StatusType OS_SYSCALL_DISABLEINTERRUPTSOURCE(ISRType ISRID)
{
  boolean canUseSvc;
  StatusType LddStatusReturn = E_OK;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
  /* @Trace: SafeOs_SUD_API_45801 */
  /* Thread Mode */
    CALLSVC(OSServiceId_DisableInterruptSource);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_45802 */
    LddStatusReturn = Os_KernDisableInterruptSource(ISRID);
  }

  return LddStatusReturn;
}

OS_LOCAL_INLINE StatusType OS_SYSCALL_CLEARPENDINGINTERRUPT(ISRType ISRID)
{
  boolean canUseSvc;
  StatusType LddStatusReturn = E_OK;

  canUseSvc = Os_CanUseSvc();
  if(canUseSvc == TRUE)
  {
  /* @Trace: SafeOs_SUD_API_45901 */
  /* Thread Mode */
    CALLSVC(OSServiceId_ClearPendingInterrupt);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_45902 */
    LddStatusReturn = Os_KernClearPendingInterrupt(ISRID);
  }

  return LddStatusReturn;
}
#endif

#if (OS_PERIPHERAL == STD_ON)
/* Inline function for Os_ReadPeripheral8() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_READPERIPHERAL8(AreaIdType Area,
                          P2CONST(uint8, AUTOMATIC, OS_CONST) Address,
                          uint8* Readvalue)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if (canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_46001 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ReadPeripheral8);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_46002 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallReadPeripheral8(Area, Address, Readvalue);
  }
  
  return LddStatusReturn;
}

/* Inline function for Os_ReadPeripheral16() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_READPERIPHERAL16(AreaIdType Area,
                            P2CONST(uint16, AUTOMATIC, OS_CONST) Address,
                            uint16* Readvalue)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if (canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_46101 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ReadPeripheral16);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_46102 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallReadPeripheral16(Area, Address, Readvalue);
  }
  return LddStatusReturn;
}

/* Inline function for Os_ReadPeripheral32() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_READPERIPHERAL32(AreaIdType Area,
                            P2CONST(uint32, AUTOMATIC, OS_CONST) Address,
                            uint32* Readvalue)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if (canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_46201 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ReadPeripheral32);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_46202 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallReadPeripheral32(Area, Address, Readvalue);
  }
  return LddStatusReturn;
}

/* Inline function for Os_WritePeripheral8() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_WRITEPERIPHERAL8(AreaIdType Area,
                                 P2VAR(uint8, AUTOMATIC, OS_VAR) Address,
                                 uint8 WriteValue)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if (canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_46301 */
    /* Thread Mode */
    CALLSVC(OSServiceId_WritePeripheral8);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_46302 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallWritePeripheral8(Area, Address, WriteValue);
  }
  return LddStatusReturn;
}

/* Inline function for Os_WritePeripheral16() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_WRITEPERIPHERAL16(AreaIdType Area,
                                 P2VAR(uint16, AUTOMATIC, OS_VAR) Address,
                                 uint16 WriteValue)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if (canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_46401 */
    /* Thread Mode */
    CALLSVC(OSServiceId_WritePeripheral16);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_46402 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallWritePeripheral16(Area, Address, WriteValue);
  }
  return LddStatusReturn;
}

/* Inline function for Os_WritePeripheral32() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_WRITEPERIPHERAL32(AreaIdType Area,
                                 P2VAR(uint32, AUTOMATIC, OS_VAR) Address,
                                 uint32 WriteValue)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if (canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_46501 */
    /* Thread Mode */
    CALLSVC(OSServiceId_WritePeripheral32);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_46502 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallWritePeripheral32(Area, Address, WriteValue);
  }
  return LddStatusReturn;
}

/* Inline function for Os_ModifyPeripheral8() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_MODIFYPERIPHERAL8(AreaIdType Area,
                                  P2VAR(uint8, AUTOMATIC, OS_VAR) Address,
                                              uint8 Clearmask, uint8 Setmask)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if (canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_46601 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ModifyPeripheral8);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_46602 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallModifyPeripheral8(Area, Address, Clearmask, Setmask);
  }
  return LddStatusReturn;
}

/* Inline function for Os_ModifyPeripheral16() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_MODIFYPERIPHERAL16(AreaIdType Area,
                                  P2VAR(uint16, AUTOMATIC, OS_VAR) Address,
                                             uint16 Clearmask, uint16 Setmask)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if (canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_46701 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ModifyPeripheral16);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_46702 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallModifyPeripheral16(Area, Address, Clearmask, Setmask);
  }
  return LddStatusReturn;
}

/* Inline function for Os_ModifyPeripheral32() system call */
OS_LOCAL_INLINE StatusType OS_SYSCALL_MODIFYPERIPHERAL32(AreaIdType Area,
                                  P2VAR(uint32, AUTOMATIC, OS_VAR) Address,
                                             uint32 Clearmask, uint32 Setmask)
{
  StatusType LddStatusReturn = E_OK;
  boolean canUseSvc;

  canUseSvc = Os_CanUseSvc();
  if (canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_46801 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ModifyPeripheral32);
    __asm("mov %0, r0" : "=r" (LddStatusReturn) :);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_46802 */
    /* Handler Mode */
    LddStatusReturn = Os_SystemCallModifyPeripheral32(Area, Address, Clearmask, Setmask);
  }
  return LddStatusReturn;
}
#endif /* (OS_PERIPHERAL == STD_ON) */

#if (OS_MEMORY_PROTECTION == STD_ON)
/* Inline function for Os_ReturnKernelStack() system call */
OS_LOCAL_INLINE void OS_SYSCALL_RETURNKERNELSTACK(void)
{

  boolean canUseSvc;
  canUseSvc = Os_CanUseSvc();
  if (canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_46901 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ReturnKernelStack);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_46902 */
    Os_SystemCallReturnKernelStack();
  }
}
/* Inline function for Os_ReturnNTISRKernelStack() system call */
OS_LOCAL_INLINE void OS_SYSCALL_RETURNNTISRKERNELSTACK(void)
{

  boolean canUseSvc;
  canUseSvc = Os_CanUseSvc();
  if (canUseSvc == TRUE)
  {
    /* @Trace: SafeOs_SUD_API_47001 */
    /* Thread Mode */
    CALLSVC(OSServiceId_ReturnNTISRKernelStack);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_47002 */
    Os_SystemCallReturnNTISRKernelStack();
  }
}
#endif /* (OS_MEMORY_PROTECTION == STD_ON)*/

#endif /* OS_ARCH_TIMER_H_ */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
