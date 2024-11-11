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
**  SRC-MODULE: Os_InternalTypes.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of AUTOSAR OS type internally used macros,          **
**              structure declarations and extern declarations of variables   **
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
**           26-Apr-2023   SH.Yoo           Jira CP44-2017                    **
**                                          Jira CP44-2005                    **
** 1.3.12.0  09-Mar-2023   TanHX            Jira CP44-1335                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.1.0     20-Apr-2021   Thao             R44-Redmine #17907                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.6     22-Sep-2020   TamNN1           R44-Redmine #15778                **
** 1.0.5     14-Sep-2020   TamNN1           R44-Redmine #12870                **
** 1.0.4     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Add comment for MISRAC 20.7, 8.5  **
**                                          Add comment for Misra-C D4.5      **
** 1.0.3     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.2     28-Jul-2020   DanhDC1          R44-Redmine #11180                **
**                                          Merge the TryToGetSpinLock() and  **
**                                          GetSpinLock() into one            **
** 1.0.1     16-Jul-2020   DanhDC1          R44-Redmine #14601                **
**                                          Change the type of                **
**                                          OsTaskActivation from uint8 to    **
**                                          uint32 type as ECUC_Os_00074      **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace-begin MISRA-C3:8.11 [Justified:Low] "External linkage with array size makes error because of compiler optimization" */
/* polyspace-begin MISRA-C3:D4.9 [Justified:Low] "Macro definitions are needed for performance and file size" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:20.7 [Justified:Low] "This macro is defined by tasking compiler" */
/* polyspace-begin MISRA-C3:D4.8 [Justified:Low] "Not request the object should be hidden" */
#ifndef OS_INTERNALTYPES_H
#define OS_INTERNALTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00357 SRS_BSW_00410 */
#if (OS_TIMING_PROTECTION == STD_ON)
typedef enum
{
  OS_WDG_DISABLED = OS_ZERO,
  OS_EXEC_BUDGET,
  OS_TIME_FRAME,
  OS_REZ_LOCK,
  OS_INT_LOCK,
  OS_ALL_INT_LOCK
} Os_WatchdogType;

typedef struct STagTdd_Os_ScheduleWatchdog
{
  /* pointer to the current running task*/
  P2CONST(struct STagTdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
  /*pointer to  the same structure*/
  P2VAR(struct STagTdd_Os_ScheduleWatchdog, AUTOMATIC, OS_VAR)
  pNextSchedWatchdog;
  /* Absolute Time */
  TickType ddSchedTick;
} Tdd_Os_ScheduleWatchdog;

typedef struct
{
  /* Array index for Timing Protection */
  uint32 ulTPArrayIndx;
  /*Hold the types of currently running Timing Protection.*/
  Os_WatchdogType ddWdgType;
  /* Hold the pointer to the timing protected task or cat2 isr */
  P2CONST(struct STagTdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
} Tdd_Os_TPWatchdog;

typedef struct
{
  /* Array where timing protection is specified (or not) for each resource
   *   (zero if no timing protection) */
  P2CONST(uint32, AUTOMATIC, OS_CONST)  pResourceLockTime;
  /* Maximum duration the task can be active within a timeframe or maximum
   *   isr execution time since last activation */
  TickType ddExecutionBudget;
  /* Configured timeframe for this timing protection */
  TickType ddTimeFrame;
  /* Interrupt lock time */
  TickType ddInterruptLockTime;
  /* All interrupt lock time */
  TickType ddAllInterruptLockTime;
  /* Time Frame ID */
  uint8 ucTimeFrameWdgId;
  /* ExeBudgetIndex */
  #if ((OS_TASK_TP_EB == STD_ON) || (OS_ISR_TP_EB == STD_ON))
  uint8 ucTaskExeBudgetIndex;
  #endif
} Tdd_Os_TimingProtection;
#endif /* #if(OS_TIMING_PROTECTION == ON) */

typedef enum
{
  LOCK_ALL_INTERRUPTS,
  LOCK_CAT2_INTERRUPTS,
  LOCK_WITH_RES_SCHEDULER,
  LOCK_NOTHING
} Os_SpinlockMethod;

typedef struct
{
  /* Access Mask for Spinlock */
  uint32 ulAppAccessMask;
  /* Index to the next Spinlock */
  SpinlockIdType ddNextSpinIndex;
  /* Spin lock acquired Task */
  TaskType ddTaskId;
  /* Spin lock method */
  Os_SpinlockMethod enSpinMethod;
} Tdd_Os_Spinlock;

typedef struct
{
  /* Min Id of the nested spinlock */
  uint32 ulMinSpinID;
  /* Max Id of the nested spinlock */
  uint32 ulMaxSpinID;
} Tdd_Os_StaticSpinlock;

typedef struct
{
  #if (OS_SCALABILITY_CLASS >= OS_SC3)
  /* Application Mask */
  uint32 ddAppAccesMask;
  #endif
  #if (OS_APPLICATION == STD_ON)
  /* Application Id */
  ApplicationType ddAppId;
  #endif
  /* Priority of the owner before accessing to the resource. This field is
   *   used to restore the priority of the task when the resource is released */
  uint8 scOwnerPrevPriority;
  /* Ceiling priority as computed at system generation time. */
  uint8 scCeilingPriority;
  /* Flag to tell if the internal resource is taken or not */
  uint8 ucTaken;
} Tdd_Os_InternalResource;

typedef struct STagTdd_Os_Resource
{
  /* Owner of the resource or NULL if the resource is not owned */
  P2VAR(struct STagTdd_Os_Task, AUTOMATIC, OS_VAR) pOwner;
  /* Pointer to the next resource used to link them together when a task get
   *   more than one resource */
  P2VAR(struct STagTdd_Os_Resource, AUTOMATIC, OS_VAR) pNextResource;
  #if (OS_SCALABILITY_CLASS >= OS_SC3)
  /* Application Mask */
  uint32 ddAppAccesMask;
  #endif
  /* Resource ID */
  ResourceType ddResID;
  /* Priority of the owner before accessing to the resource. This field is
   *   used to restore the priority of the task when the resource is released */
  uint8 scOwnerPrevPriority;
  /* Ceiling priority as computed at system generation time. */
  uint8 scCeilingPriority;
  #if (OS_APPLICATION == STD_ON)
  /* Application Id */
  ApplicationType ddAppId;
  #endif
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
  #if (OS_RES_TP_EB == STD_ON)
  /* Index in Os_GaaTimingProtValue array */
  uint8 ddResLockTimeIndex;
  #endif

  #if (OS_RES_INT_SHARE == STD_ON)
  /* Store previous interrupt priority */
  uint32 ulOwnerPrevHwPrio;
  #endif
} Tdd_Os_Resource;

typedef struct
{
  /* Hardware priority of Interrupt if shared between Task and ISR */
  uint32 ulHardwarePriority;
} Tdd_Os_HardWareResource;
/* polyspace +1 MISRA-C3:2.4 [Justified:Low] "This Tag is used to member of Tdd_Os_Resource which is defined in Internaltypes.h" */
typedef struct STagTdd_Os_Task
{
  #if (OS_RESOURCE == STD_ON)
  /* Head of the ressources held */
  P2VAR(struct STagTdd_Os_Resource, AUTOMATIC, OS_VAR) pResources;
  #endif
  #if (OS_EVENT == STD_ON)
  /* Event */
  EventMaskType ddEventSet;
  /* Wait for Event */
  EventMaskType ddEventWait;
  #endif
  /* State */
  TaskStateType ddState;
  /* Current activate count */
  uint32 ulActivateCount;
  #if (OS_SPINLOCK == STD_ON)
  SpinlockIdType ddSpinlock;
  #endif
  #if (OS_TIMING_PROTECTION == STD_ON)
  /* TimeFrame Flag */
  boolean blActivateAllowed;
  #endif
} Tdd_Os_Task;
/* polyspace +1 MISRA-C3:2.4 [Justified:Low] "This Tag is used to member of Tdd_Os_ScheduleWatchdog which is defined in Internaltypes.h" */
typedef struct STagTdd_Os_StaticTask
{
  /* Context of the ISR */
 /* polyspace +4 MISRA-C3:5.6 [Justified:Low] "This is to refer structure of Os_PortTypes.h which include this file." */
 /* polyspace +3 MISRA-C3:5.7 [Justified:Low] "This is to refer structure of Os_PortTypes.h which include this file." */
 /* polyspace +2 MISRA-C3:1.3 [Justified:Low] "This is to refer structure of Os_PortTypes.h which include this file." */
 /* polyspace +1 MISRA-C3:2.4 [Justified:Low] "This is to refer structure of Os_PortTypes.h which include this file." */
  P2VAR(struct STagTdd_Os_ContextSwitch, AUTOMATIC, OS_VAR) pContext;
  #if (OS_TIMING_PROTECTION == STD_ON)
  /* Timing protection configuration (can be NULL if no timing protection is
   *   needed) */
  P2CONST(Tdd_Os_TimingProtection, AUTOMATIC, OS_CONST) pStaticTimProtection;
  #endif
  /* Pointer to static descriptor */
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) pTask;

  /* Pointer to Link list structure */
  P2VAR(struct STagTdd_Os_LinkTask, AUTOMATIC, OS_VAR) pLinkTask;
  #if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO)
  /* Pointer to an internal resource. NULL if the task does not have an
   *   internal resource */
  P2VAR(Tdd_Os_InternalResource, AUTOMATIC, OS_VAR) pInternalResource;
  #endif
  /* Function that is the entry point of the task/isr */
  P2FUNC(void, OS_VAR, pFuncEntry) (void);
  #if (OS_SCALABILITY_CLASS >= OS_SC3)
  /* Application Mask */
  uint32 ddAppAccesMask;
  #endif
  /* Type of the Task/ISR */
  /* OS_TASK_BASIC = 0x01,
   * OS_TASK_EXTENDED = 0x02,
   * OS_ISR_ROUTINE = 0x04*/
  uint16 usType;
  /* Stack Index */
  uint8 ucStackIndex;
  /* Id of task/isr */
  TaskType ddTaskId;
  /* Base priority of the task/isr */
  uint8 ucBasePriority;
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreId;
  #endif
  #if (OS_APPLICATION == STD_ON)
  /* ID of the application to which the task belongs */
  ApplicationType ddAppId;
  #endif
  /* Max activation count of a task/isr */
  uint32 ulMaxActivateCount;
} Tdd_Os_StaticTask;

typedef struct
{
  /* Core activation status */
  boolean blCoreStatus;
} Tdd_Os_Core;

typedef struct STagTdd_Os_LinkTask
{
  /* Pointer to the next Link list */
  P2VAR(struct STagTdd_Os_LinkTask, AUTOMATIC, OS_VAR) pLinkList;
  /* Task ID */
  TaskType ddTaskID;
  /* Priority of the task */
  sint8 scPriority;
} Tdd_Os_LinkTask;


typedef struct STagTdd_Os_Alarm
{
  /* Next alarm in the active alarm list */
  P2VAR(struct STagTdd_Os_Alarm, AUTOMATIC, OS_VAR) pNextAlarm;
  /* Previous alarm in the active alarm list */
  P2VAR(struct STagTdd_Os_Alarm, AUTOMATIC, OS_VAR) pPrevAlarm;
  /* Pointer to Alarm object */
  P2CONST(struct STagTdd_Os_StaticAlarm, AUTOMATIC, OS_CONST) pStaticAlarm;
  /* Cycle delay for cyclic alarms */
  TickType ddCycle;
  /* Absolute date of the alarm */
  TickType ddAbsCount;
  /* State of the alarm*/
  /* OS_ALARM_SLEEP = 0
   * OS_ALARM_ACTIVE = 1 */
  uint8 ucAlarmState;
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreId;
  #endif
} Tdd_Os_Alarm;

typedef enum
{
  OS_ACTION_ACTIVATETASK     = 0,
  OS_ACTION_SETEVENT         = 1,
  OS_ACTION_INCREMENTCOUNTER = 2,
  OS_ACTION_ALARMCALLBACK    = 3,
  OS_ACTION_SCHEDULETABLE    = 4
} Os_AlarmActionType;

typedef struct STagTdd_Os_AlarmCallback
{
  /* Pointer to the Action which takes place on expiry of alarm*/
  P2FUNC(StatusType, OS_VAR, pAlarmCallbackFunc)
  (P2CONST(struct STagTdd_Os_AlarmCallback, AUTOMATIC, OS_CONST)
   pAction);
  /* pAlarm Callback function */
  P2FUNC(void, OS_VAR, pAlarmCallBack) (void);
} Tdd_Os_AlarmCallback;

typedef struct STagTdd_Os_ActivateTask
{
  /* Pointer to the Action which takes place on expiry of alarm*/
  P2FUNC(StatusType, OS_VAR, pActivateTaskFunc)
  (P2CONST(struct STagTdd_Os_ActivateTask, AUTOMATIC, OS_CONST)
   pAction);
  /* Task descriptor pointer */
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
} Tdd_Os_ActivateTask;

typedef struct STagTdd_Os_AlarmEvent
{
  /* Pointer to the Action which takes place on expiry of alarm*/
  P2FUNC(StatusType, OS_VAR, pAlarmEventFunc)
  (P2CONST(struct STagTdd_Os_AlarmEvent, AUTOMATIC, OS_CONST)
   pAction);
  /* Task descriptor pointer */
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
  /* Event information */
  EventMaskType ddEventMask;
} Tdd_Os_AlarmEvent;

typedef struct
{
  /* Action type which takes place on expiry of alarm*/
  Os_AlarmActionType enActionType;
  /* Task descriptor pointer */
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
  /* Event information */
  EventMaskType ddEventMask;
} Tdd_Os_Action;

typedef struct STagTdd_Os_IncrementCounter
{
  /* Pointer to the Action which takes place on expiry of alarm*/
  P2FUNC(StatusType, OS_VAR, pIncrementCounterFunc)
  (P2CONST(struct STagTdd_Os_IncrementCounter, AUTOMATIC, OS_CONST)
   pAction);
  /* ID of the counter to be updated */
  CounterType ddCounterId;
} Tdd_Os_IncrementCounter;


typedef struct STagTdd_Os_Counter
{
  #if ((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON))
  /* Active alarms list head */
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR)  pHeadAlarm;
  #endif
  /* Counter flag for using */
  boolean blAlarmInUse;
  /* Current value of the counter */
  TickType ddCurrentCount;
  /* Count of delayed ticks more than 1 tick */
  uint32 ulCounterLoss;
} Tdd_Os_Counter;
/* polyspace-end MISRA-C3:2.4 [Justified:Low] "This Tag is used to member of Tdd_Os_StaticCounter which is defined in internaltypes.h" */

/* polyspace +3 MISRA-C3:5.7 [Justified:Low] "This is to refer structure of Os_PortTypes.h which include this file." */
/* polyspace +2 MISRA-C3:1.3 [Justified:Low] "This is to refer structure of Os_PortTypes.h which include this file." */
/* polyspace +1 MISRA-C3:2.4 [Justified:Low] "This Tag is used to refer structure of Os_PortTypes.h which include in this file" */
typedef struct STagTdd_Os_HardwareCounter Tdd_Os_HardwareCounter;

/* polyspace +1 MISRA-C3:2.4 [Justified:Low] "This Tag is used to member of Tdd_Os_StaticAlarm which is defined in Internaltypes.h" */
typedef struct STagTdd_Os_StaticCounter
{
  /* Pointer to RAM Counter */
  P2VAR(Tdd_Os_Counter, AUTOMATIC, OS_VAR) pCounter;
  /* Pointer to Hardware Counter Info */
  P2VAR(Tdd_Os_HardwareCounter, AUTOMATIC, OS_VAR) pHwCounter;
  /* Maximum allowed value for a counter */
  TickType ddMaxAllowedValue;
  /* Number of ticks until the counter increments */
  TickType ddMinCycle;
  #if (OS_SCALABILITY_CLASS >= OS_SC3)
  /* Application Mask */
  uint32 ddAppAccesMask;
  #endif
  #if (OS_APPLICATION == STD_ON)
  /* Application Id */
  ApplicationType ddAppId;
  #endif
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
} Tdd_Os_StaticCounter;

typedef struct
{
  /* Pointer to first action associated with expiry point */
  P2CONST(Tdd_Os_Action, AUTOMATIC, OS_CONST) pAction;
  /* Offset of the actions from the start time of the schedule table */
  TickType ddOffset;
  /* Maximum Advance Period */
  TickType ddMaxAdvancePeriod;
  /* Maximum Retard Period */
  TickType ddMaxRetardPeriod;
  /* Number of actions associated with the expiry point */
  uint32 ulCount;
} Tdd_Os_ExpiryPoint;

typedef struct
{
  /* Pointer to first expiry points */
  P2CONST(Tdd_Os_ExpiryPoint, AUTOMATIC, OS_CONST) pExpiryPoint;
  /* Pointer to counter object */
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) pStaticCounter;
  /* Duration of schedule table */
  TickType ddSchedTblDuration;
  /* OsScheduleTblExplicitPrecision */
  TickType ddExplictPrecision;
  /* Index to Alarm object */
  AlarmType ddAlarmIndex;
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
  /* Number of expiry count */
  uint32 ucExpiryCount;
  /* Synchroinization strategy */
  /* OS_EXPLICIT = 0
   * OS_IMPLICIT = 1 */
  uint8 ucSynchStrategy;
  /* True if schedule table is repeating */
  boolean blPeriodic;
} Tdd_Os_StaticSchedTable;

typedef struct STagTdd_Os_SchedTable
{
  /* Pointer to the Action which takes place on expiry of alarm*/
  P2FUNC(StatusType, OS_VAR, pSchedTableFunc)
  (P2VAR(struct STagTdd_Os_SchedTable, AUTOMATIC, OS_VAR)
   pAction);
  /* Offset of next expiry point to be processed from start */
  TickType ddExpiryOffset;
  /* Deviation */
  sint64 ssDeviation;
  /* Next schedule table to start */
  ScheduleTableType ddNextSchedTable;
  /* Index of the Schedule Table */
  ScheduleTableType ddSchedTableId;

  #if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
  /* ScheduleTable has Expiry Points were Expired */
  uint32 ucIsExpired;
  #endif

  /* Next expiry point to process in the schedule table */
  uint32 ulIndex;
} Tdd_Os_SchedTable;

typedef struct
{
  /* Pointer to the task to be restarted */
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
} Tdd_Os_ReStartTask;

typedef struct
{
  /* Pointer to the task which is autostart */
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
} Tdd_Os_AutoStartTask;

typedef struct
{
  /* Pointer to the Alarm which is autostart */
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) pAlarm;
} Tdd_Os_AutoStartAlarm;

typedef struct
{
  /* Pointer to the ScheduleTable which is autostart */
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC,
    OS_CONST) pStaticSchedTable;
} Tdd_Os_AutoStartSchedTable;

typedef struct
{
  /* Pointer to the AutosatrtTask Structure */
  P2CONST(Tdd_Os_AutoStartTask, AUTOMATIC, OS_CONST) pAutoStartTask;
  /* Pointer to the AutosatrtAlarm Structure */
  P2CONST(Tdd_Os_AutoStartAlarm, AUTOMATIC, OS_CONST) pAutoStartAlarm;
  /* Pointer to the AutosatrtScheduleTable Structure */
  P2CONST(Tdd_Os_AutoStartSchedTable, AUTOMATIC, OS_CONST)
  pAutoStartSchedTable;
  /* Number of Autostart Schedule Table */
  ScheduleTableType ddNoOfAutoStartSchedTable;
  /* Number of Autostart Task */
  TaskType ddNoOfAutoStartTask;
  /* Number of Autostart Alarm */
  AlarmType ddNoOfAutoStartAlarm;
} Tdd_Os_ApplMode;

typedef struct
{
  #if (OS_RESTART_TASK_COUNT != OS_PRE_ZERO)
  /* Pointer to the RestartTask in the application */
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) pRestartTask;
  #endif
  /* Pointer to the Alarm in the application */
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) pApplicationAlarm;
  /* Pointer to the ScheduleTable in the application */
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) pApplicationScheTbl;
  /*  Application Mask = 2^ddAppId */
  uint32 ulAppMask;
  /* Number of Schedule Table in the application */
  ScheduleTableType ddNoOfStaticSchedTable;
  /* Number of Alarm in the application */
  AlarmType ddNoOfAlarm;
  /* Application Id */
  ApplicationType ddAppId;
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
  /* Stack Index */
  uint8 ucStackIndex;
  #if ((OS_SCALABILITY_CLASS == OS_SC3) || (OS_SCALABILITY_CLASS == OS_SC4))
  /* ucType */
  uint8 ucType;
  /* Base Index of memory blocks */
  uint8 ucBaseMemBlockIndex;
  /* Maximum Index of memory blocks */
  uint8 ucNoOfMemBlk;
  #endif
  #if ((OS_TIMING_PROTECTION == STD_ON) && (OS_TRUSTED_FUNC_COUNT != OS_ZERO))
  /* Timing violation Flag */
  boolean blHasDelay;
  #endif
} Tdd_Os_Application;

typedef struct
{
  /* State of the Application */
  ApplicationStateType ddState;
} Tdd_Os_ApplicationData;

/* polyspace-begin MISRA-C3:2.4 [Justified:Low] "This Tag is used to member of Tdd_Os_Alarm which is defined in internaltypes.h" */
typedef struct STagTdd_Os_StaticAlarm
{
  /* Pointer to Action Object for ActivateTask */
  P2CONST(Tdd_Os_ActivateTask, AUTOMATIC, OS_CONST) pActivateTask;

  /* Pointer to Action Object for AlarmEvent */
  P2CONST(Tdd_Os_AlarmEvent, AUTOMATIC, OS_CONST) pAlarmEvent;

  /* Pointer to Action Object for IncrementCounter */
  P2CONST(Tdd_Os_IncrementCounter, AUTOMATIC, OS_CONST) pIncrementCounter;

  /* Pointer to Action Object for AlarmCallback */
  P2CONST(Tdd_Os_AlarmCallback, AUTOMATIC, OS_CONST) pAlarmCallback;

  /* Pointer to Action Object for SchedTable */
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) pSchedTable;
  /* Pointer to counter */
  P2VAR(struct STagTdd_Os_Counter, AUTOMATIC, OS_VAR) pCounter;
  /* Pointer to static counter */
  P2CONST(struct STagTdd_Os_StaticCounter, AUTOMATIC, OS_CONST)
  pStaticCounter;
  #if (OS_SCALABILITY_CLASS >= OS_SC3)
  /* Application Mask */
  uint32 ddAppAccesMask;
  #endif
  #if (OS_APPLICATION == STD_ON)
  /* Application Id */
  ApplicationType ddAppId;
  #endif
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
} Tdd_Os_StaticAlarm;

#if (OS_TRUSTED_FUNC_COUNT != OS_ZERO)
typedef struct
{
  /* polyspace +2 MISRA-C3:8.2 [Justified:Low] "function parameters are defined by the user" */
  /* Pointer to trusted function */
  P2FUNC(void, OS_VAR, pTrustedFunc) (void*);
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
  /* Owner Application Id */
  ApplicationType ddOwnerAppId;
} Tdd_Os_TrustedFunction;
#endif /* End of if (OS_TRUSTED_FUNC_COUNT != OS_ZERO) */
#if ((OS_APP_ERROR_HOOK == STD_ON) || (OS_APP_SHUTDOWN_HOOK == STD_ON) ||\
  (OS_APP_STARTUP_HOOK == STD_ON))
typedef struct
{
  #if (OS_APP_ERROR_HOOK == STD_ON)
  /* Application specific Error Hook function */
  P2FUNC(void, OS_VAR, pErrorHook) (StatusType Fatalerror);
  #endif

  #if (OS_APP_SHUTDOWN_HOOK == STD_ON)
  /* Application specific Error Hook function */
  P2FUNC(void, OS_VAR, pShutDownHook) (StatusType Fatalerror);
  #endif

  #if (OS_APP_STARTUP_HOOK == STD_ON)
  /* Application specific Error Hook function */
  P2FUNC(void, OS_VAR, pStartupHook) (void);
  #endif
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
} Tdd_Os_ApplicationHook;
#endif /* End of if ((OS_APP_ERROR_HOOK == STD_ON) || (OS_APP_SHUTDOWN_HOOK ==
        *STD_ON) || (OS_APP_STARTUP_HOOK == STD_ON)) */

#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
typedef struct
{
  uint32 ulAreaStartAddr;
  uint32 ulAreaEndAddr;
  uint32 ddAppAccesMask;
} Os_PeripheralArea;

typedef enum
{
  OS_PERIPHERAL_UINT8,
  OS_PERIPHERAL_UINT16,
  OS_PERIPHERAL_UINT32
} Os_PeripheralSize;
#endif

/* The type service define of spinlock api */
typedef enum
{
  TRYTOGETSPINLOCK,
  GETSPINLOCK
} Os_SpinLockServiceType;

#if (OS_ERROR_HOOK == STD_ON)

/* polyspace-begin MISRA-C3:19.2 [Justified:Low] "These unions are used to specify error type" */
typedef union
{
  TrustedFunctionIndexType FunctionIndex;
  TaskType TaskID;
  ScheduleTableType ScheduleTableID;
  ScheduleTableType ScheduleTableID_From;
  CounterType CounterID;
  ApplicationType Application;
  TaskRefType TaskIDRef;                   /* GetTaskID's 1st param - TaskID */
  ResourceType ResID;
  EventMaskType Mask;
  AlarmType AlarmID;
  SpinlockIdType SpinlockId;
  CoreIDType CoreID;                    /* ControlIdle's 1st param - CoreID */
  AreaIdType Area;
  ISRType ISRID;
} Tdd_Os_ParamBlock1;

typedef union
{
  TrustedFunctionParameterRefType FunctionParams;
  TickType Offset;
  TickType Start;
  ScheduleTableType ScheduleTableID_To;
  TickType Value;
  ScheduleTableStatusRefType ScheduleStatus;
  TickRefType ValueRef;                    /* GetCounterValue's 2nd param - Value */
                                           /* GetElapsedValue's 2nd param - Value */
  RestartType RestartOption;
  ApplicationStateRefType AppValueRef;     /* GetApplicationState's 2nd param - Value */
  TaskStateRefType State;
  EventMaskType Mask;
  EventMaskRefType Event;
  AlarmBaseRefType Info;
  TickRefType Tick;
  TickType Increment;
  TickType TickStart;                      /* SetAbsAlarm's 2nd param - Start */
  TryToGetSpinlockType* Success;
  IdleModeType IdleMode;                   /* ControlIdle's 2nd param - IdleMode */
  P2CONST(uint32, AUTOMATIC, OS_CONST) AddressR;
  P2VAR(uint32, AUTOMATIC, OS_VAR) AddressW;
  P2VAR(uint32, AUTOMATIC, OS_VAR) AddressM;
  boolean ClearPending;
} Tdd_Os_ParamBlock2;

typedef union
{
  TickRefType ElapsedValue;
  TickType Cycle;
  uint32* Readvalue;
  uint32 WriteValue;
  uint32 Clearmask;
} Tdd_Os_ParamBlock3;

typedef union
{
  uint32 Setmask;
} Tdd_Os_ParamBlock4;
/* polyspace-end MISRA-C3:19.2 [Justified:Low] "These unions are used to specify error type" */

typedef struct
{
  Tdd_Os_ParamBlock1 unParam1;
  Tdd_Os_ParamBlock2 unParam2;
  Tdd_Os_ParamBlock3 unParam3;
  Tdd_Os_ParamBlock4 unParam4;
} Tdd_Os_Parameter;

typedef struct
{
  Tdd_Os_Parameter ddParameters;
  OSServiceIdType  ucServiceID;
} Tdd_Os_ServiceCall;
#endif /* #if (OS_ERROR_HOOK == STD_ON) */


/* Data types for Multi-core Scheduling with Cross-core Messaging */
#if (OS_MULTICORE == STD_ON)
/* Largest no. of parameters to a service */
#define OS_MAXPARAM   4

/* The number of messages in the queues
*/
#define OS_N_MESSAGES             (OS_CORE_COUNT-1)

/* Inter-core message queue.
 *
 * The message queue itself is an array of n message structures, where n is the largest number of
 * messages that can be queued at any time. This array is written by the sender and read by the
 * receiver.
 *
 * Queue control is achieved through three indices; the fill, the empty and the message counter.
 *
 * The fill index is written by the sender and is read-only for the receiver. The empty index
 * is read-only for the sender and is written by the receiver.
 * Message counter index is incremented by the sender and decremented by the receiver.
 */

/* A single message.
 */
typedef struct
{
  uint32 opcode;
  uint32 result;
  uint32 parameter[OS_MAXPARAM];
  uint32 resultReady;
} Os_MessageType;

/* Message queue structure.
 */
typedef struct
{
  uint16 fill;
  uint16 empty;
  uint16 msgCnt;
  uint16 buffer[OS_N_MESSAGES];
  Os_MessageType msg[OS_N_MESSAGES];
}Os_MessageQueueType;

#endif /* #if (OS_MULTICORE == STD_ON) */

/* Privilege mode type */
typedef enum
{
  OS_PRIV_UNKNOWN,     /* Unknown status */
  OS_PRIV_SUPERVISOR,  /* Privileged mode: Unrestricted access is available */
  OS_PRIV_USER         /* Non-privileged mode : Access is restricted */
} Os_PrivModeType;

typedef enum
{
  OS_LOCKTYPE_OS = 0,       /* Suspend/ResumeOSInterrupts() */
  OS_LOCKTYPE_ALL = 1,      /* Suspend/ResumeAllInterrupts() */
  OS_LOCKTYPE_NONEST = 2    /* Disable/EnableAllInterrupts() */
} OsIntLockType;

typedef enum
{
  OS_SHUTDOWN_SYNCHRONIZED,
  OS_SHUTDOWN_INDIVIDUAL
} Os_ShutdownType;

/** This data type identifies the nesting count of SuspendAll(OS)Interrupts. */
typedef uint8 Os_IsrLockType;

typedef struct
{
  P2VAR(Os_StackType, AUTOMATIC, OS_VAR) pStackArea; /**< Pointer Variable for Stack Area */
  uint16 usStackSize;                                /**< Variable for Stack size */
} Tdd_Os_Stack;

/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
#if ((OS_APP_ERROR_HOOK == STD_ON) || (OS_APP_SHUTDOWN_HOOK == STD_ON) ||\
                                                (OS_APP_STARTUP_HOOK == STD_ON))
/* @Trace: SRS_BSW_00309 */
extern CONST(Tdd_Os_ApplicationHook, OS_CONST) Os_GaaStaticAppHook[];
#endif /* End of if ((OS_APP_ERROR_HOOK == STD_ON) || (OS_APP_SHUTDOWN_HOOK ==
        *STD_ON) || (OS_APP_STARTUP_HOOK == STD_ON)) */
#if (OS_TRUSTED_FUNC_COUNT != OS_ZERO)
extern CONST(Tdd_Os_TrustedFunction, OS_CONST) Os_GaaTrustedFunction[];
#endif /* End of if (OS_TRUSTED_FUNC_COUNT != OS_ZERO) */
extern CONST(Tdd_Os_StaticTask, OS_CONST) Os_GaaStaticTask[];
extern CONST(Tdd_Os_HardWareResource, OS_CONST) Os_GaaHardWareResource[];
extern CONST(Tdd_Os_AutoStartTask, OS_CONST) Os_GaaAutoStartTask[];
extern CONST(Tdd_Os_AutoStartSchedTable, OS_CONST) Os_GaaAutoSchedTable[];
#if (OS_COUNTER == STD_ON)
extern CONST(Tdd_Os_StaticCounter, OS_CONST) Os_GaaStaticCounter[];
#endif /* End of if (OS_COUNTER == STD_ON) */
#if((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON))
extern CONST(Tdd_Os_StaticAlarm, OS_CONST) Os_GaaStaticAlarm[];
#endif /* End of if (OS_ALARM == STD_ON) ||  (OS_SCHEDTABLE == STD_ON)*/
extern CONST(Tdd_Os_ApplMode, OS_CONST) Os_GaaApplMode[];
extern CONST(Tdd_Os_Action, OS_CONST) Os_GaaAction[];
extern CONST(Tdd_Os_IncrementCounter, OS_CONST) Os_GaaIncrementCounter[];
extern CONST(Tdd_Os_AlarmCallback, OS_CONST) Os_GaaAlarmCallback[];
extern CONST(Tdd_Os_ActivateTask, OS_CONST) Os_GaaActivateTask[];
extern CONST(Tdd_Os_AlarmEvent, OS_CONST) Os_GaaAlarmEvent[];
extern CONST(Tdd_Os_AutoStartAlarm, OS_CONST) Os_GaaAutoStartAlarm[];
extern CONST(Tdd_Os_ReStartTask, OS_CONST) Os_GaaReStartTask[];
extern CONST(Tdd_Os_ExpiryPoint, OS_CONST) Os_GaaExpiryPoint[];
#if (OS_TIMING_PROTECTION == STD_ON)
extern CONST(Tdd_Os_TimingProtection, OS_CONST) Os_GaaTimingProtection[];
#endif /*OS_TIMING_PROTECTION == STD_ON*/
#if (OS_MULTICORE == STD_ON)
extern CONST(uint8, OS_CONST)  Os_GaaCAT2MaxPriority[];
extern CONST(uint8, OS_CONST)  Os_GaaCAT1LeastPriority[];
#endif /*OS_MULTICORE == STD_ON*/
#if (OS_SPINLOCK == STD_ON)
extern CONST(Tdd_Os_StaticSpinlock, OS_CONST) Os_GaaStaticSpinlock[];
#endif /*OS_SPINLOCK == STD_ON*/
#if (OS_APPLICATION == STD_ON)
extern CONST(Tdd_Os_Application, OS_CONST) Os_GaaStaticApplication[];
#endif
extern CONST(Tdd_Os_Stack, OS_CONST) Os_GaaStack[];
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
extern CONST(Os_PeripheralArea, OS_CONST) Os_GaaStaticPeripheralArea[];
#endif
extern CONST(AppModeType, OS_CONST) Os_ApplMode_Count;
extern CONST(TaskType, OS_CONST) Os_Task_Count;
extern CONST(ISRType, OS_CONST) Os_CAT2_ISR_Count;
extern CONST(ISRType, OS_CONST) Os_CAT1_ISR_Count;
extern CONST(ISRType, OS_CONST) Os_ISR_Count;
extern CONST(uint16, OS_CONST) Os_CAT2_Max_Priority;
extern CONST(uint16, OS_CONST) Os_CAT1_Least_Priority;
extern CONST(ISRType, OS_CONST) Os_Max_Nest_Level;
extern CONST(ResourceType, OS_CONST) OS_Resource_Count;
extern CONST(AreaIdType, OS_CONST) OS_Area_Count;
extern CONST(CounterType, OS_CONST) Os_Counter_Count;
extern CONST(AlarmType, OS_CONST) Os_Alarm_Count;
extern CONST(ScheduleTableType, OS_CONST) Os_Schedule_Count;
extern CONST(uint8, OS_CONST) Os_Core_Count;
extern CONST(SpinlockIdType, OS_CONST) Os_Spinlock_Count;
extern CONST(uint16, OS_CONST) Os_Ioc_Callback_Count;
extern CONST(uint16, OS_CONST) Os_Ioc_Count;
extern CONST(uint16, OS_CONST) Os_Ioc_Count_Queued;
extern CONST(uint16, OS_CONST) Os_Ioc_Count_Unqueued;
extern CONST(ApplicationType, OS_CONST) Os_Application_Count;
extern CONST(ApplicationType, OS_CONST) Os_Trusted_Start_Indx;
extern CONST(ApplicationType, OS_CONST)
                                      Os_Trusted_App_With_Protection_Start_Indx;
extern CONST(TrustedFunctionIndexType, OS_CONST) Os_Trusted_Func_Count;
extern CONST(uint16, OS_CONST) Os_App_MemBlk_Cnt;


#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_CONST_ASIL_D_GLOBAL_32
#include "MemMap.h"
#if (OS_TIMING_PROTECTION == STD_ON)
extern CONST(uint32, OS_CONST) Os_GaaResourceLock[];
#endif /*OS_TIMING_PROTECTION == STD_ON*/
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
extern VAR(Tdd_Os_Task, OS_VAR) Os_GaaTask[];
/* polyspace +1 MISRA-C3:8.5 [Justified:Low] "To avoid cross reference, external array is needed." */
extern VAR(Tdd_Os_Core, OS_VAR) Os_GaaCore[];

extern VAR(Tdd_Os_Counter, OS_VAR) Os_GaaCounter[];
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
extern VAR(Tdd_Os_Alarm, OS_VAR) Os_GaaAlarm[];
extern VAR(Tdd_Os_LinkTask, OS_VAR) Os_GaaLinkTask[];
extern VAR(Tdd_Os_InternalResource, OS_VAR) Os_GaaInternalResource[];
extern VAR(Tdd_Os_Resource, OS_VAR) Os_GaaResourceTable[];
#if (OS_SCHEDTABLE == STD_ON)
extern VAR(Tdd_Os_SchedTable, OS_VAR) Os_GaaSchedTable[];
extern CONST(Tdd_Os_StaticSchedTable, OS_CONST) Os_GaaStaticSchedTable[];
#endif /*OS_SCHEDTABLE == STD_ON*/
#if (OS_TIMING_PROTECTION == STD_ON)
extern VAR(Tdd_Os_ScheduleWatchdog, OS_VAR) Os_GaaSchedWatchdog[];
#endif /*OS_TIMING_PROTECTION == STD_ON*/
#if (OS_SPINLOCK == STD_ON)
extern VAR(Tdd_Os_Spinlock, OS_VAR) Os_GaaSpinlock[];
#endif /*OS_SPINLOCK == STD_ON*/
#define OS_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#endif /* Os_InternalTypes*/


/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace-end MISRA-C3:8.11 [Justified:Low] "External linkage with array size makes error because of compiler optimization" */
/* polyspace-end MISRA-C3:D4.9 [Justified:Low] "Macro definitions are needed for performance and file size" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:20.7 [Justified:Low] "This macro is defined by tasking compiler" */
/* polyspace-end MISRA-C3:D4.8 [Justified:Low] "Not request the object should be hidden" */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
