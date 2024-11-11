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
**  SRC-MODULE: Os_Definition.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of AUTOSAR OS Standard Type Definitions.            **
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
** 1.5.1     20-Sep-2023   HJ.Kim           Jira CP44-XXXX                    **
** 1.5.0     09-Jun-2023   HJ.Kim           Jira CP44-2325                    **
**                         HJ.Kim           Jira CP44-2322                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-2081                    **
** 1.4.1     07-Apr-2023   HG.Kim          Jira CP44-1803                     **
** 1.4.0     19-Sep-2022   TinHV            Jira CP44-192                     **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.1.0     20-Apr-2021   Thao             R44-Redmine #17907                **
** 1.0.6.0   01-Mar-2021   Thao             R44-Redmine #18295                **
** 1.0.4     22-Sep-2020   TamNN1           R44-Redmine #15236                **
**                                          R44-Redmine #12870                **
**                                          Fixed Defect detect by polyspace  **
** 1.0.3     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Add comment for Misra-C 2.5       **
** 1.0.2     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.1     16-Jul-2020   DanhDC1          R44-Redmine #14667 Add the        **
**                                          E_OS_SYS_RAMECC,                  **
**                                          E_OS_SYS_DFLASHECC and            **
**                                          E_OS_SYS_PFLASHECC                **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace-begin MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */
/* polyspace-begin MISRA-C3:11.4 [No action planned:Low] "The conversion of scalar integers to other types to avoid hard code" */

/* @Trace: SRS_Os_00097 SRS_Os_11005 SRS_BSW_00327 SRS_BSW_00335 */

#ifndef OS_DEFINITIONS_H
#define OS_DEFINITIONS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SafeOs_SUD_DATATYPE_00101 */
/*
 * Service ID for GetApplicationID
 */
#define OSServiceId_GetApplicationID           0

/*
 * Service ID for GetTaskID
 */
#define OSServiceId_GetISRID                   1

/*
 * Service ID for CallTrustedFunction
 */
#define OSServiceId_CallTrustedFunction        2

/*
 * Service ID for CheckISRMemoryAccess
 */
#define OSServiceId_CheckISRMemoryAccess       3

/*
 * Service ID for CheckTaskMemoryAccess
 */
#define OSServiceId_CheckTaskMemoryAccess      4

/*
 * Service ID for CheckObjectAccess
 */
#define OSServiceId_CheckObjectAccess          5

/*
 * Service ID for CheckObjectOwnership
 */
#define OSServiceId_CheckObjectOwnership       6

/*
 * Service ID for StartScheduleTableRel
 */
#define OSServiceId_StartScheduleTableRel      7

/*
 * Service ID for StartScheduleTableAbs
 */
#define OSServiceId_StartScheduleTableAbs      8

/*
 * Service ID for StopScheduleTable
 */
#define OSServiceId_StopScheduleTable          9

/*
 * Service ID for NextScheduleTable
 */
#define OSServiceId_NextScheduleTable          10

/*
 * Service ID for StartScheduleTableSynchron
 */
#define OSServiceId_StartScheduleTableSynchron 11

/*
 * Service ID for SyncScheduleTable
 */
#define OSServiceId_SyncScheduleTable          12

/*
 * Service ID for SetScheduleTableAsync
 */
#define OSServiceId_SetScheduleTableAsync      13

/*
 * Service ID for GetScheduleTableStatus
 */
#define OSServiceId_GetScheduleTableStatus     14

/*
 * Service ID for IncrementCounter
 */
#define OSServiceId_IncrementCounter           15

/*
 * Service ID for GetCounterValue
 */
#define OSServiceId_GetCounterValue            16

/*
 * Service ID for GetElapsedValue
 */
#define OSServiceId_GetElapsedValue            17

/*
 * Service ID for TerminateApplication
 */
#define OSServiceId_TerminateApplication       18

/*
 * Service ID for AllowAccess
 */
#define OSServiceId_AllowAccess                19

/*
 * Service ID for GetApplicationState
 */
#define OSServiceId_GetApplicationState        20

/*
 * Service ID for GetNumberOfActivatedCores
 */
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "This Macro is used in GetNumberOfActivatedCores() function" */
#define OSServiceId_GetNumberOfActivatedCores  21

/*
 * Service ID for GetCoreID
 */
#define OSServiceId_GetCoreID                  22

/*
 * Service ID for StartCore
 */
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "This macro is define OSServiceId" */
#define OSServiceId_StartCore                  23

/*
 * Service ID for StartNonAutosarCore
 */
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "Macro used with purpose OSEK backward compatibility" */
#define OSServiceId_StartNonAutosarCore        24

/*
 * Service ID for GetSpinlock
 */
#define OSServiceId_GetSpinlock                25

/*
 * Service ID for ReleaseSpinlock
 */
#define OSServiceId_ReleaseSpinlock            26

/*
 * Service ID for TryToGetSpinlock
 */
#define OSServiceId_TryToGetSpinlock           27

/*
 * Service ID for ShutdownAllCores
 */
#define OSServiceId_ShutdownAllCores           28

/*
 * Service ID for ControlIdle
 */
#define OSServiceId_ControlIdle                29

/*
 * Service ID for Os_IocSend
 */
#define IOCServiceId_IOC_Send                  30

/*
 * Service ID for Os_IocWrite
 */
#define IOCServiceId_IOC_Write                 31

/* 32  OSServiceId_UnknownSyscall */
/* 33  OSServiceId_UnknownSyscall */

/*
 * Service ID for Os_IocPullCB
 */
#define IOCServiceId_IOC_Receive               34

/*
 * Service ID for Os_IocRead
 */
#define IOCServiceId_IOC_Read                  35

/* 36  OSServiceId_UnknownSyscall */
/* 37  OSServiceId_UnknownSyscall */

/*
 * Service ID for Os_IocEmptyQueue
 */
#define IOCServiceId_IOC_EmptyQueue            38

/*
 * Service ID for GetCurrentApplicationID
 */
#define OSServiceId_GetCurrentApplicationID    39

/*
 * Service ID for ReadPeripheral8
 */
#define OSServiceId_ReadPeripheral8            40

/*
 * Service ID for ReadPeripheral16
 */
#define OSServiceId_ReadPeripheral16           41

/*
 * Service ID for ReadPeripheral32
 */
#define OSServiceId_ReadPeripheral32           42

/*
 * Service ID for WritePeripheral8
 */
#define OSServiceId_WritePeripheral8           43

/*
 * Service ID for WritePeripheral16
 */
#define OSServiceId_WritePeripheral16          44

/*
 * Service ID for WritePeripheral32
 */
#define OSServiceId_WritePeripheral32          45

/*
 * Service ID for ModifyPeripheral8
 */
#define OSServiceId_ModifyPeripheral8          46

/*
 * Service ID for ModifyPeripheral16
 */
#define OSServiceId_ModifyPeripheral16         47

/*
 * Service ID for DisableInterruptSource
 */
#define OSServiceId_DisableInterruptSource     48

/*
 * Service ID for EnableInterruptSource
 */
#define OSServiceId_EnableInterruptSource      49

/*
 * Service ID for ClearPendingInterrupt
 */
#define OSServiceId_ClearPendingInterrupt      50

/*
 * Service ID for ActivateTaskAsyn
 */
#define OSServiceId_ActivateTaskAsyn           51

/*
 * Service ID for SetEventAsyn
 */
#define OSServiceId_SetEventAsyn               52

/*
 * Service ID for ModifyPeripheral32
 */
#define OSServiceId_ModifyPeripheral32         53

/* 54  OSServiceId_UnknownSyscall */
/* 55  OSServiceId_UnknownSyscall */
#define OSServiceId_ReturnKernelStack                56 /* 56  OSServiceId_UnknownSyscall */
#define OSServiceId_ReturnNTISRKernelStack           57 /* 57  OSServiceId_UnknownSyscall */
/* 58  OSServiceId_UnknownSyscall */
/* 59  OSServiceId_UnknownSyscall */
/* 60  OSServiceId_UnknownSyscall */
/* 61  OSServiceId_UnknownSyscall */
/* 62  OSServiceId_UnknownSyscall */

/*
 * Service ID for Os_IocPullCB
 */
#define OSServiceId_Os_IocPullCB               63

/*
 * Service ID for Os_ErrorTerminateTask
 */
#define OSServiceId_Os_ErrorTerminateTask      64

/*
 * Service ID for ActivateTask
 */
#define OSServiceId_ActivateTask               65

/*
 * Service ID for TerminateTask
 */
#define OSServiceId_TerminateTask              66

/*
 * Service ID for ChainTask
 */
#define OSServiceId_ChainTask                  67

/*
 * Service ID for Schedule
 */
#define OSServiceId_Schedule                   68

/*
 * Service ID for GetTaskID
 */
#define OSServiceId_GetTaskID                  69

/*
 * Service ID for GetTaskState
 */
#define OSServiceId_GetTaskState               70

/*
 * Service ID for EnableAllInterrupts
 */
#define OSServiceId_EnableAllInterrupts        71

/*
 * Service ID for DisableAllInterrupts
 */
#define OSServiceId_DisableAllInterrupts       72

/*
 * Service ID for ResumeAllInterrupts
 */
#define OSServiceId_ResumeAllInterrupts        73

/*
 * Service ID for SuspendAllInterrupts
 */
#define OSServiceId_SuspendAllInterrupts       74

/*
 * Service ID for ResumeOSInterrupts
 */
#define OSServiceId_ResumeOSInterrupts         75

/*
 * Service ID for SuspendOSInterrupts
 */
#define OSServiceId_SuspendOSInterrupts        76

/*
 * Service ID for GetResource
 */
#define OSServiceId_GetResource                77

/*
 * Service ID for ReleaseResource
 */
#define OSServiceId_ReleaseResource            78

/*
 * Service ID for SetEvent
 */
#define OSServiceId_SetEvent                   79

/*
 * Service ID for ClearEvent
 */
#define OSServiceId_ClearEvent                 80

/*
 * Service ID for GetEvent
 */
#define OSServiceId_GetEvent                   81

/*
 * Service ID for WaitEvent
 */
#define OSServiceId_WaitEvent                  82

/*
 * Service ID for GetAlarmBase
 */
#define OSServiceId_GetAlarmBase               83

/*
 * Service ID for GetAlarm
 */
#define OSServiceId_GetAlarm                   84

/*
 * Service ID for SetRelAlarm
 */
#define OSServiceId_SetRelAlarm                85

/*
 * Service ID for SetAbsAlarm
 */
#define OSServiceId_SetAbsAlarm                86

/*
 * Service ID for CancelAlarm
 */
#define OSServiceId_CancelAlarm                87

/*
 * Service ID for GetActiveApplicationMode
 */
#define OSServiceId_GetActiveApplicationMode   88

/*
 * Service ID for StartOS
 */
#define OSServiceId_StartOS                    89

/*
 * Service ID for ShutdownOS
 */
#define OSServiceId_ShutdownOS                 90

/* @Trace: SafeOs_SUD_DATATYPE_00102 */
/*
 * @def IOC_E_OK
 *
 * This error code means : No error occurred
 */
#ifndef IOC_E_OK
#define IOC_E_OK                              ((Std_ReturnType) 0)
#endif

/*
 * @def IOC_E_NOK
 *
 * This error code means : Error occurred. Shall be used to identify error
 * cases without error specification.
 */
#ifndef IOC_E_NOK
#define IOC_E_NOK                             ((Std_ReturnType) 1)
#endif

/*
 * @def IOC_E_LIMIT
 *
 * This error code means : In case of "event"(queued) semantic, the internal
 * buffer within the IOC communication service is full (Case: Receiver slower
 * than sender). This error produces additionally an Overlayed Error on the
 * receiver side at the next data reception.
 */
#ifndef IOC_E_LIMIT
#define IOC_E_LIMIT                           ((Std_ReturnType) 130)
#endif

/*
 * @def IOC_E_LOST_DATA
 *
 * This error code means : In case of "event"(queued) semantic, this Overlayed
 * Error indicates that the IOC service refuses an IocSend request due to
 * internal buffer overflow.
 */
#ifndef IOC_E_LOST_DATA
#define IOC_E_LOST_DATA                       ((Std_ReturnType) 64)
#endif

/*
 * @def IOC_E_NO_DATA
 *
 * This error code means : In case of "event"(queued) semantic,
 * no data is available for reception.
 */
#ifndef IOC_E_NO_DATA
#define IOC_E_NO_DATA                         ((Std_ReturnType) 131)
#endif

/*
 * @def E_OS_ACCESS
 *
 * This error code means : specified Os objects are not accessible
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_ACCESS                           ((uint8) 1)

/*
 * @def E_OS_CALLEVEL
 *
 * This error code means : call at interrupt level
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_CALLEVEL                         ((uint8) 2)

/*
 * @def E_OS_ID
 *
 * This error code means : invalid identifier
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_ID                               ((uint8) 3)

/*
 * @def E_OS_LIMIT
 *
 * This error code means : limit exceeded. The only limit known to raise this
 * error is the number of task activations
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_LIMIT                            ((uint8) 4)

/*
 * @def E_OS_NOFUNC
 *
 * This error code means : not appropriate.
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_NOFUNC                           ((uint8) 5)

/*
 * @def E_OS_RESOURCE
 *
 * This error code means : calling task still occupies resources
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_RESOURCE                         ((uint8) 6)

/*
 * @def E_OS_STATE
 *
 * This error code means : related state not appropriate
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_STATE                            ((uint8) 7)

/*
 * @def E_OS_VALUE
 *
 * This error code means : value outside of the admissible limits
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_VALUE                            ((uint8) 8)

/*
 * @def E_OS_STACKFAULT
 *
 * This error code means : value outside of the admissible limits
 *
 */
#define E_OS_STACKFAULT                       ((uint8) 9)

/*
 * @def E_OS_PROTECTION_ARRIVAL
 *
 * This error code means : value outside of the admissible limits
 *
 */
#define E_OS_PROTECTION_ARRIVAL               ((uint8) 10)

/*
 * @def E_OS_PROTECTION_TIME
 *
 * This error code means : value outside of the admissible limits
 *
 */
#define E_OS_PROTECTION_TIME                  ((uint8) 11)

/*
 * @def E_OS_PROTECTION_LOCKED
 *
 * This error code means : value outside of the admissible limits
 */

#define E_OS_PROTECTION_LOCKED                ((uint8) 12)

/*
 * @def E_OS_MISSINGEND
 *
 * This error code means : Tasks terminates without a TerminateTask()
 *                          or ChainTask() call.
 *
 */
#define E_OS_MISSINGEND                       ((uint8) 35)

/*
 * @def E_OS_DISABLEDINT
 *
 * This error code means : A service of the OS is called inside an interrupt
 *                          disable/enable pair.
 */
#define E_OS_DISABLEDINT                      ((uint8) 13)

/*
 * @def E_OS_PROTECTION_EXCEPTION
 *
 * This error code means : If an instruction exception occurs
 *                          (e.g. division by zero).
 */

#define E_OS_PROTECTION_EXCEPTION             ((uint8) 14)
/*
 * @def E_OS_CORE
 *
 * This error code means : All functions that are not allowed to operate cross
 *               core shall return E_OS_CORE in extended status if
 *               called with parameters that require a cross core
 *               operation
 */

#define E_OS_CORE                             ((uint8) 15)

/*
 * @def E_OS_INTERFERENCE_DEADLOCK
 *
 * This error code means : The function GetSpinlock shall return  this error if
 *                         the spinlock referred by the parameter SpinlockID is
 *                     already occupied by a TASK/ISR2 on the same core.
 */

#define E_OS_INTERFERENCE_DEADLOCK            ((uint8) 16)

/*
 * @def E_OS_NESTING_DEADLOCK
 *
 * This error code means : A TASK tries to occupy the spinlock while holding a
 *              different spinlock in a way that may cause a deadlock.
 */

#define E_OS_NESTING_DEADLOCK                 ((uint8) 17)

/*
 * @def E_OS_SPINLOCK
 *
 * This error code means : This error means de-scheduling with occupied
 *spinlock.
 *
 */

#define E_OS_SPINLOCK                         ((uint8) 18)

/*
 * @def E_OS_SERVICEID
 *
 * This error code means : If the function index in a call of
 *               CallTrustedFunction() is undefined.
 */

#define E_OS_SERVICEID                        ((uint8) 19)
/*
 * @def E_OS_PARAM_POINTER
 *
 * This error code means : If A pointer argument of an API is NULL pointer
 *
 */
#define E_OS_PARAM_POINTER                    ((uint8) 20)
/*
 * @def E_OS_PROTECTION_MEMORY
 *
 * This error code means : A memory access violation occurred
 */
#define E_OS_PROTECTION_MEMORY                ((uint8) 21)
/*
 * @def E_OS_ILLEGAL_ADDRESS
 *
 * This error code means : An invalid address is given as a parameter to a
 *                         service.
 */
#define E_OS_ILLEGAL_ADDRESS                  ((uint8) 22)
/*
 * @def E_OS_SYS_ALARMINUSE
 *
 * This error code means : An invalid address is given as a alarm is in use
 *
 */
#define E_OS_SYS_ALARM_INUSE                  ((uint8) 23)
/*
 * @def E_OS_SYS_RAMECC
 *
 * This error code means : An ECC error has occurred on the RAM
 *
 */
/* polyspace +1 MISRA-C3:2.5 [Justified:High] "Macro used for ECC error on the RAM" */
#define E_OS_SYS_RAMECC                       ((uint8) 24)

/*
 * @def E_OS_SYS_DFLASHECC
 *
 * This error code means : An ECC error has occurred on the Data Flash
 *
 */
/* polyspace +1 MISRA-C3:2.5 [Justified:High] "Macro used for ECC error on the Data Flash" */
#define E_OS_SYS_DFLASHECC                    ((uint8) 25)

/*
 * @def E_OS_SYS_PFLASHECC
 *
 * This error code means : An ECC error has occurred on the Program Flash
 *
 */
/* polyspace +1 MISRA-C3:2.5 [Justified:High] "Macro used for ECC error on the Program Flash" */
#define E_OS_SYS_PFLASHECC                    ((uint8) 26)

/*
 * @def E_OS_SYS_CORE_IS_DOWN
 *
 * This error code means : When an inter-core API request is made,
 * the target core on which the API is actually executed is already shutdown
 * and the API request can not be processed.
 *
 */
#define E_OS_SYS_CORE_IS_DOWN                 ((uint8)100)
/*
 * @def E_OS_SYS_PANIC
 *
 * This error code means : A fatal OS error occurs
 *
 */
#define E_OS_SYS_PANIC                        ((uint8)101)
/*
 * @def E_OS_SYS_NMI
 *
 * This error code means : An exception occurred from NMI.
 *
 */
#define E_OS_SYS_NMI                          ((uint8)102)
/*
 * @def E_OS_SYS_INTERCOREMSG
 *
 * This error code means : A problem occurred during the inter-core API
 * request process.
 *
 */
#define E_OS_SYS_INTERCOREMSG                 ((uint8)103)

/******************************************************************************
 **                      Always existing application mode                    **
 *****************************************************************************/
/* @Trace: SafeOs_SUD_DATATYPE_00103 */
/*
 * @def OSDEFAULTAPPMODE
 *
 * Default application mode, always a valid parameter to StartOS.
 *
 * @see #StartOS
 * @see #AppModeType
 */
#define OSDEFAULTAPPMODE                      ((AppModeType) 0xfe)

/*
 * @def DONOTCARE
 *
 * Default application mode, always a valid parameter to StartOS.
 *
 * @see #StartOS
 * @see #AppModeType
 */
#define DONOTCARE                             ((AppModeType) 0xff)

/*******************************************************************************
 *                        Task flags for the type field                        *
 ******************************************************************************/
/* @Trace: SafeOs_SUD_DATATYPE_00104 */
/*
 * @def TASK_BASIC
 *
 * identifies a Basic task
 *
 */

#define OS_TASK_BASIC                         ((uint8) 0x01)

/*
 * @def TASK_EXTENDED
 *
 * identifies an extended task
 *
 */
#define OS_TASK_EXTENDED                      ((uint8) 0x02)

/*
 * @def OS_ISR2
 *
 * identifies a category 2 Interrupt Service Routine
 *
 */

#define OS_ISR2                               ((uint8) 0x04)

/*
 * @def TASK_INVALID
 *
 * identifies a invalid task
 *
 */

#define OS_TASK_INVALID                       ((uint8) 0xff)
/******************************************************************************
 *                            Tasks states and actions                        *
 *****************************************************************************/
/* @Trace: SafeOs_SUD_DATATYPE_00105 */
#define OS_TASK_UNINITIALIZED                 ((uint8) 0x0)
/*
 * @def SUSPENDED
 *
 * This is a state of a task
 */
#define SUSPENDED                             ((uint8) 0x4)
/*
 * @def READY
 *
 * This is a state of a task
 */
#define READY                                 ((uint8) 0x2)
/*
 * @def RUNNING
 *
 * This is a state of a task
 */
#define RUNNING                               ((uint8) 0x6)
/*
 * @def WAITING
 *
 * This is a state of a task
 */
#define WAITING                               ((uint8) 0x5)
/*
 * @def DYING
 *
 * This is a state of a task
 */
#define DYING                                 ((uint8) 0xD)
/*
 * @def OS_READY_AND_NEW
 *
 * This is a state of a task
 */
#define OS_READY_AND_NEW                      ((uint8) 0xA)
/*
 * @def OS_READY_AND_WAITING
 *
 * This is a state of a task
 */
#define OS_READY_AND_WAITING                  ((uint8) 0x1A)

/*
 * @def READY_AND_INTERRUPTED
 *
 * This is a state of a task
 */
#define READY_AND_INTERRUPTED              ((uint8) 0x2E)

/*
 * @def INVALID_TASK
 *
 * This is a ID of an invalid Task. */
#define INVALID_TASK                          ((TaskType)0xff)

/*
 * @def INVALID_ISR
 *
 * This is a ID of an invalid ISR. */
#define INVALID_ISR                           ((ISRType)0xff)

/******************************************************************************
 * Alarms states and actions                                                  *
 *****************************************************************************/
/* @Trace: SafeOs_SUD_DATATYPE_00106 */
/*
 * @def OS_ALARM_SLEEP
 *
 * This is a state of a Alarm
 */
#define OS_ALARM_SLEEP                        ((uint8) 0)

/**
 * @def OS_ALARM_ACTIVE
 *
 * This is a state of a Alarm
 */
#define OS_ALARM_ACTIVE                       ((uint8) 1)

/******************************************************************************
 * Schedule Table states and actions                                          *
 *****************************************************************************/
/* @Trace: SafeOs_SUD_DATATYPE_00107 */
/**
 * @def SCHEDULETABLE_STOPPED
 *
 * This is a state of a ScheduleTable.
 */
#define SCHEDULETABLE_STOPPED                 ((StatusType) 0)

/**
 * @def SCHEDULETABLE_NEXT
 *
 * This is a state of a ScheduleTable.
 */
#define SCHEDULETABLE_NEXT                    ((StatusType) 1)

/**
 * @def SCHEDULETABLE_RUNNING
 *
 * This is a state of a ScheduleTable.
 */
#define SCHEDULETABLE_RUNNING                 ((StatusType) 2)

/**
 * @def SCHEDULETABLE_STOPPED
 *
 * This is a state of a ScheduleTable.
 */
#define SCHEDULETABLE_WAITING                 ((StatusType) 3)

/**
 * @def OS_SCHEDULETABLE_EXP_DEV
 *
 * This is a state of a ScheduleTable.
 */
#define OS_SCHEDULETABLE_EXP_DEV              ((StatusType) 4)

/**
 * @def SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS
 *
 * This is a state of a ScheduleTable.
 */
#define SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS ((StatusType) 5)

/**
 * @def OS_SCHEDULETABLE_EXP_REQ
 *
 * This is a state of a ScheduleTable.
 */
#define OS_SCHEDULETABLE_EXP_REQ              ((StatusType) 6)

/**
 * @def OS_SCHEDULETABLE_EXP_PRE
 *
 * This is a state of a ScheduleTable.
 */
#define OS_SCHEDULETABLE_EXP_PRE              ((StatusType) 7)

/* @Trace: SafeOs_SUD_DATATYPE_00108 */
/**
 * @def TASK
 *
 * Macro used to define (declare) a task
 *
 * @param Name the name (C identifier) of the task
 */
/* polyspace +3 MISRA-C3:20.4 [Justified:Low] "Definition for function redirection does not use parenthesised expression" */
/* polyspace +2 MISRA-C3:20.10 [Justified:Low] "## preprocessor is needed to naming task" */
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "Following Naming convention of OSEK" */
#define TASK(Name)                       void TASK_##Name(void)

/* @Trace: SafeOs_SUD_DATATYPE_00109 */
/**
 * @def ISR
 *
 * Macro used to define (declare) a category 2 interrupt service routine.
 *
 * @param Name the name (C identifier) of the IRS
 */

/* polyspace +2 MISRA-C3:20.4 [Justified:Low] "Definition for function redirection does not use parenthesised expression" */
/* polyspace +1 MISRA-C3:20.10 [Justified:Low] "## preprocessor is needed to naming ISR" */
#define ISR(Name)                        void ISR_##Name(void)

/* @Trace: SafeOs_SUD_DATATYPE_00110 */
/**
 * @def OSMEMORY_IS_READABLE
 *
 * Macro to check if memory is readable.
 * For following macros if argument is NO_ACCESS(=1), the macro will negate it
 * as the macro is suppose to return zero in case of NO_ACCESS.
 * Note: changing value of NO_ACCESS as zero will have its side-effects on
 * Error checking. As E_OK is mapped to ACCESS is mapped to OS_ZERO
 */
/* @Trace: SRS_BSW_00330 */
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "Macro is provided to check memory permission with purpose return is OK or NOT_OK" */
#define OSMEMORY_IS_READABLE(Argument)\
  ((NO_ACCESS == ((Argument) & NO_ACCESS)) ? OS_ZERO : OS_ONE)

/* @Trace: SafeOs_SUD_DATATYPE_00112 */
/**
 * @def OSMEMORY_IS_WRITEABLE
 *
 * Macro to check if memory is Writeable.
 */
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "Macro is provided to check memory permission with purpose return is OK or NOT_OK" */
#define OSMEMORY_IS_WRITEABLE(Argument)\
  ((OS_READ_WRITE == ((Argument) & OS_READ_WRITE)) ? OS_ONE : OS_ZERO)

/* @Trace: SafeOs_SUD_DATATYPE_00113 */
/**
 * @def OSMEMORY_IS_STACKSPACE
 *
 * Macro to check if memory is in stack space.
 */
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "Macro is provided to check memory permission with purpose return is OK or NOT_OK" */
#define OSMEMORY_IS_STACKSPACE(Argument)\
  ((OS_STACKSPACE == ((Argument) & OS_STACKSPACE)) ? OS_ONE : OS_ZERO)

/* @Trace: SafeOs_SUD_DATATYPE_00114 */
/**
 * @def OSMEMORY_IS_STACKSPACE
 *
 * Macro to check if memory is in code space.
 */
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "Macro is provided to check memory permission with purpose return is OK or NOT_OK" */
#define OSMEMORY_IS_EXECUTABLE(Argument) \
  (((OS_EXECUTE == ((Argument) & OS_EXECUTE)) && ((NO_ACCESS != ((Argument) & NO_ACCESS)))) ? OS_ONE : OS_ZERO)

/* @Trace: SafeOs_SUD_DATATYPE_00115 */
/**
 * @def ALARMCALLBACK
 *
 * Macro used to define an alarm callback function
 *
 * @param Name callback name
 *
 * @warning don't be confused with ALARM_CALLBACK
 */
/* polyspace +3 MISRA-C3:20.4 [Justified:Low] "Definition for function redirection does not use parenthesised expression" */
/* polyspace +2 MISRA-C3:20.10 [Justified:Low] "## preprocessor is needed to naming alarm callback" */
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "Following Naming convention of OSEK" */
#define ALARMCALLBACK(Name)              void _##Name(void)

/* @Trace: SafeOs_SUD_DATATYPE_00116 */
/**
 * @def DeclareEvent(EventIdentifier)
 *
 * OSEK backward compatibility. Needs to be empty!
 *
 * Macro used to DeclareEvent serves as an external declaration of an event.
 * The function and use of this service are similar to that of the external
 * declaration of variables.
 *
 * @param [in]  EventIdentifier    The event which shall be declared.
 *
 */
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "Macro used with purpose OSEK backward compatibility" */
#define DeclareEvent(EventIdentifier)

/* @Trace: SafeOs_SUD_DATATYPE_00117 */
/**
 * @def DeclareAlarm(AlarmIdentifier)
 *
 * OSEK backward compatibility. Needs to be empty!
 *
 * @param [in]  AlarmIdentifier    The alarm which shall be declared.
 *
 */
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "Macro used with purpose OSEK backward compatibility" */
#define DeclareAlarm(AlarmIdentifier)

/* @Trace: SafeOs_SUD_DATATYPE_00118 */
/**
 * @def DeclareResource(ResourceIdentifier)
 *
 * OSEK backward compatibility. Needs to be empty!
 *
 * Macro used to DeclareResource serves as an external declaration of
 * a resource. The function and use of this service are similar to that of
 * the external declaration of variables.
 *
 * @param [in]  ResourceIdentifier    The resource which shall be declared.
 *
 */
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "Macro used with purpose OSEK backward compatibility" */
#define DeclareResource(ResourceIdentifier)

/* @Trace: SafeOs_SUD_DATATYPE_00119 */
/**
 * @def DeclareTask(TaskIdentifier)
 *
 * OSEK backward compatibility. Needs to be empty!
 *
 * Macro used to DeclareTask serves as an external declaration of a task.
 * The function and use of this service are similar to that of the external
 * declaration of variables.
 *
 * @param [in]  TaskIdentifier    The task which shall be declared.
 *
 */
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "Macro used with purpose OSEK backward compatibility" */
#define DeclareTask(TaskIdentifier)

/* @Trace: SafeOs_SUD_DATATYPE_00121 */
/**
 * @def ACCESS
 *
 * Return for accessible.
 *
 * @param access return values
 *
 */
#define ACCESS                                ((ObjectAccessType)0x0)

/**
 * @def NO_ACCESS
 *
 * Return for non-accessible.
 *
 * @param access return values
 *
 */
#define NO_ACCESS                             ((ObjectAccessType)0x1)
/**
 * @def OS_FULLACCESS
 *
 * Return for Fully-accessible.
 *
 * @param access return values
 *
 */
#define OS_FULLACCESS                         0xFFFFFFFFUL
/**
 * @def CoreIDType
 *
 * Macro used to remove the case sensitivity
 *
 */
/* polyspace +1 MISRA-C3:20.4 [Justified:Low] "Definition for function redirection does not use parenthesised expression" */
#define CoreIDType                            CoreIdType

/* @Trace: SafeOs_SUD_DATATYPE_00123 */
/**
 * @def INVALID_OSAPPLICATION
 *
 * This is a ID of an invalid application.
 */
#define INVALID_OSAPPLICATION                 ((ApplicationType)0xff)

/* @Trace: SafeOs_SUD_DATATYPE_00124 */
/**
 * @def APPLICATION_ACCESSIBLE
 *
 * This is a state of a Application.
 */
#define APPLICATION_ACCESSIBLE                ((ApplicationStateType) 0x00)
/**
 * @def APPLICATION_RESTARTING
 *
 * This is a state of a Application.
 */
#define APPLICATION_RESTARTING                ((ApplicationStateType) 0x01)
/**
 * @def APPLICATION_TERMINATED
 *
 * This is a state of a Application.
 */
#define APPLICATION_TERMINATED                ((ApplicationStateType) 0x02)

/* @Trace: SafeOs_SUD_DATATYPE_00125 */
/**
 * @def OS_TRUSTED
 *
 * Type of a Application.
 */
#define OS_TRUSTED                            ((uint8)255)
/**
 * @def OS_NON_TRUSTED
 *
 * Type of a Application.
 */
#define OS_NON_TRUSTED                        ((uint8)254)
/**
 * @def OS_TRUSTED_PROTECTION
 *
 * Type of a Application.
 */
#define OS_TRUSTED_PROTECTION                 ((uint8)253)

/* @Trace: SafeOs_SUD_DATATYPE_00126 */
/**
 * @def OBJECT_TASK
 *
 * Type of a Object.
 */
#define OBJECT_TASK                           ((ObjectTypeType)0x0)
/**
 * @def OBJECT_ISR
 *
 * Type of a Object.
 */
#define OBJECT_ISR                            ((ObjectTypeType)0x1)
/**
 * @def OBJECT_ALARM
 *
 * Type of a Object.
 */
#define OBJECT_ALARM                          ((ObjectTypeType)0x2)
/**
 * @def OBJECT_RESOURCE
 *
 * Type of a Object.
 */
#define OBJECT_RESOURCE                       ((ObjectTypeType)0x3)
/**
 * @def OBJECT_COUNTER
 *
 * Type of a Object.
 */
#define OBJECT_COUNTER                        ((ObjectTypeType)0x4)
/**
 * @def OBJECT_SCHEDULETABLE
 *
 * Type of a Object.
 */
#define OBJECT_SCHEDULETABLE                  ((ObjectTypeType)0x5)

/* @Trace: SafeOs_SUD_DATATYPE_00127 */
/**
 * @def OS_SCHEDTABLE_NONE_SYNC
 *
 * Synchronization Strategy of Schedule Table.
 */
#define OS_SCHEDTABLE_NONE_SYNC               ((uint8) 0)
/**
 * @def OS_SCHEDTABLE_EXPLICIT_SYNC
 *
 * Synchronization Strategy of Schedule Table.
 */
#define OS_SCHEDTABLE_EXPLICIT_SYNC           ((uint8) 1)
/**
 * @def OS_SCHEDTABLE_IMPLICIT_SYNC
 *
 * Synchronization Strategy of Schedule Table.
 */
#define OS_SCHEDTABLE_IMPLICIT_SYNC           ((uint8) 2)

/* @Trace: SafeOs_SUD_DATATYPE_00128 */
/**
 * @def OS_CAT1_ISR
 *
 * Type of ISR.
 */
#define OS_CAT1_ISR                           (0x0u)
/**
 * @def OS_CAT2_ISR
 *
 * Type of ISR.
 */
#define OS_CAT2_ISR                           (0x1u)

/* @Trace: SafeOs_SUD_DATATYPE_00129 */
/**
 * @def RESTART
 *
 * Restart Option.
 */
#define RESTART                               ((RestartType)(0))
/**
 * @def NO_RESTART
 *
 * Restart Option.
 */
#define NO_RESTART                            ((RestartType)(0x1))

/* @Trace: SafeOs_SUD_DATATYPE_00130 */
/**
 * @def PRO_TERMINATETASKISR
 *
 * return from ProtectionHook.
 */
#define PRO_TERMINATETASKISR                  0x00
/**
 * @def PRO_TERMINATEAPPL
 *
 * return from ProtectionHook.
 */
#define PRO_TERMINATEAPPL                     0x01
/**
 * @def PRO_TERMINATEAPPL_RESTART
 *
 * return from ProtectionHook.
 */
#define PRO_TERMINATEAPPL_RESTART             0x02
/**
 * @def PRO_SHUTDOWN
 *
 * return from ProtectionHook.
 */
#define PRO_SHUTDOWN                          0x03
/**
 * @def PRO_IGNORE
 *
 * return from ProtectionHook.
 */
#define PRO_IGNORE                            0x04

/* Os Internal Macros for values */
#define OS_FALSE                              ((uint8) 0x00)
#define OS_TRUE                               ((uint8) 0x01)
#define OS_ZERO                               0x00
#define OS_PRE_ZERO                           0x00
#define OS_PRE_ONE                            0x01
#define OS_ONE                                0x01
#define OS_TWO                                0x02
#define OS_THREE                              0x03
#define OS_FOUR                               0x04
#define OS_FIVE                               0x05
#define OS_SIX                                0x06
#define OS_SEVEN                              0x07
#define OS_EIGHT                              0x08
#define OS_NINE                               0x09
#define OS_TEN                                0x0A
#define OS_SCHETABLE_SYNC_PRIORITY            0xFE
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "Macro OS_TIMER_PRIORITY is  used in  Os_PortInit() function" */
#define OS_TIMER_PRIORITY                     0xFF
#define OS_HUNDRED                            (100u)
#define OS_THOUSAND                           (1000u)
#define OS_LONG_BIT_COUNT                     0x20
#define OS_SECOND_STEP                        0x02
#define OS_THIRD_STEP                         0x03
#define OS_INVALID_VALUE                      ((uint8) 0xFF)
#define OS_MINUS_ONE                          ((sint64)(-1))
#define OS_INVALID_MASK                       ((uint32) 0xFFFFFFFFUL)
/* FIXME: OS_DEFECT_27 Resource extension to interrupts. */
/* NOTE: Os_GaaHardWareResource[] generator update required. */
#define OS_INVALID_HW_PRIORITY                ((uint32) 0xFFFFFFFFUL)
#define OS_UINT_MAX                           ((uint32) 0xFFFFFFFFu)

/* Os Mask Macros for peripheral */
/* @Trace: SafeOs_SUD_DATATYPE_00131 */
#define OS_MASK_BASE_ADDRESS                  (0xFFFFFFFCu)
#define OS_MASK_OFFSET                        (0x00000003u)
#define OS_MASK_PERIPHERAL_8BIT               (0x000000FFu)
#define OS_MASK_PERIPHERAL_16BIT              (0x0000FFFFu)
#define OS_MASK_PERIPHERAL_SUB_BLOCKZIZE      (8u)

/* Os Internal Status return values */
#define OS_E_OK_AND_SCHEDULE                  ((StatusType) 0x40)
#define OS_E_OK_AND_LOAD                      ((StatusType) 0x80)
#define OS_STATUS_MASK                        ((StatusType) 0x1f)
#define OS_TASK_STATUS                        ((StatusType) 0x07)
#define OS_CAN_BE_ACTIVATED                   ((uint8) 0x00)
#define OS_ALREADY_ACTIVATED                  ((uint8) 0x01)

/* Macro for access, according to linux permission style */
/* @Trace: SafeOs_SUD_DATATYPE_00132 */
#define OS_WRITE_ONLY                         0x2
#define OS_READ_ONLY                          0x4
#define OS_READ_WRITE                         0x6
#define OS_EXECUTE                            0x8
#define OS_STACKSPACE                         0x10

/* @Trace: SRS_Os_11012 */
/* @Trace: SafeOs_SUD_DATATYPE_00133 */
/* Scalability class */
#define OS_SC1                                0x1
#define OS_SC2                                0x2
#define OS_SC3                                0x3
#define OS_SC4                                0x4

/* Os status*/
/* @Trace: SafeOs_SUD_DATATYPE_00134 */
#define STANDARD                              0x1
#define EXTENDED                              0x2

/* To avoid violation of unused variable */
/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "To avoid violation of unused variable" */
#define OS_UNUSED(x)                          do { \
                                                   if((uint32)(x) != \
                                                   (uint32)OS_ZERO) {} \
                                                 } while(0)

#define OS_UNUSED_PTR(x)              do { \
                                          if((x) != NULL_PTR) {} \
                                      } while(0)
/* polyspace-end MISRA-C3:2.5 [Justified:Low] "To avoid violation of unused variable" */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#endif /* OS_DEFINITION_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:11.4 [No action planned:Low] "The conversion of scalar integers to other types to avoid hard code" */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace-end MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */

/******************************************************************************
**                      End of File                                          **
******************************************************************************/
