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
**  SRC-MODULE: Os_Type.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file containing the declaration of                     **
**              type related functions                                        **
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
** 1.5.0      9-Jun-2023   HJ.Kim           Jira CP44-2325                    **
** 1.3.12.0  09-Mar-2023   TanHX            Jira CP44-1335                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.3.0     09-Aug-2021   TinHV1           Redmine #18024                    **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.4     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
** 1.0.3     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C  14.3               **
** 1.0.2     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.1     21-May-2019   DanhDC1          #12951 Declare PhysicalTimeType   **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/
/* @Trace: SRS_AUTRON_00001 SRS_Os_00097 SRS_Os_11023 SRS_Os_11000 SRS_Os_11000 SRS_Os_11000 SRS_Os_11000 SRS_Os_11010 SRS_Os_00098 SRS_Os_00099 SRS_Os_11002 SRS_Os_11020 SRS_Os_11021 SRS_Os_11022 SRS_Os_80021 SRS_Os_80022 SRS_Os_80023 SRS_Os_11005 SRS_BSW_00357 */

#ifndef OS_TYPES_H
#define OS_TYPES_H

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
/**
  * @typedef EventMaskType
  *
  * Data type of the event mask
  *
  * see paragraph 13.5.1, page 60 of OSEK/VDX 2.2.3 spec
  */
/* @Trace: SafeOs_SUD_DATATYPE_00034 */
typedef uint64 EventMaskType;

/**
  * @typedef EventMaskRefType
  *
  * References a #EventMaskType
  *
  * see paragraph 13.5.1, page 60 of OSEK/VDX 2.2.3 spec
  */
/* @Trace: SafeOs_SUD_DATATYPE_00033 */
typedef P2VAR(EventMaskType, AUTOMATIC, OS_VAR) EventMaskRefType;

/**
  * @typedef TaskStateType
  *
  * identifies the state of a task
  *
  * see paragraph 13.2.1, page 49 of OSEK/VDX 2.2.3 spec
  */
/* @Trace: SafeOs_SUD_DATATYPE_00006 */
typedef uint8 TaskStateType;

/**
  * @typedef TaskStateRefType
  *
  * References a #TaskStateType
  *
  * see paragraph 13.2.1, page 49 of OSEK/VDX 2.2.3 spec
  */
/* @Trace: SafeOs_SUD_DATATYPE_00007 */
typedef P2VAR(TaskStateType, AUTOMATIC, OS_VAR) TaskStateRefType;

/**
  * @typedef TaskType
  *
  * A task's identifier.
  *
  * see paragraph 13.2.1, page 49 of OSEK/VDX 2.2.3 spec
  */
/* @Trace: SafeOs_SUD_DATATYPE_00004 */
typedef uint32 TaskType;

/**
  * @typedef TaskRefType
  *
  * References a #TaskType
  *
  * see paragraph 13.2.1, page 49 of OSEK/VDX 2.2.3 spec
  */
/* @Trace: SafeOs_SUD_DATATYPE_00005 */
typedef P2VAR(TaskType, AUTOMATIC, OS_VAR) TaskRefType;

/**
  * @typedef AppModeType
  *
  * Identifies an application mode
  *
  * see paragraph 13.7.1, page 66 of OSEK/VDX 2.2.3 spec
  */
/* @Trace: SafeOs_SUD_DATATYPE_00040 */
typedef uint32 AppModeType;

/**
  * @typedef ApplicationType
  *
  * Identifies the OS-Application
  *
  * see Section 8.3.1 of AUTOSAR_SWS_OS
  */
/* @Trace: SafeOs_SUD_DATATYPE_00011 */
typedef uint32 ApplicationType;

/**
  * @typedef ISRType
  *
  * Identifies an interrupt service routine (ISR)
  *
  * see Section 8.3.11 of AUTOSAR_SWS_OS
  */
/* @Trace: SafeOs_SUD_DATATYPE_00021 */
typedef uint32 ISRType;

/**
  * @typedef TickType
  *
  * Represents count values in ticks
  *
  * see paragraph 13.6.1, page 62 of OSEK/VDX 2.2.3 spec
  */
/* @Trace: SafeOs_SUD_DATATYPE_00036 */
typedef uint32 TickType;

/**
  * @typedef TickRefType
  *
  * Reference to the TickType
  *
  * see paragraph 13.6.1, page 62 of OSEK/VDX 2.2.3 spec
  */
/* @Trace: SafeOs_SUD_DATATYPE_00038 */
typedef P2VAR(TickType, AUTOMATIC, OS_VAR) TickRefType;

/**
  * @typedef ResourceType
  *
  * Data type for a resource.
  *
  * see paragraph 13.4.1, page 58 of OSEK/VDX 2.2.3 spec
  */
/* @Trace: SafeOs_SUD_DATATYPE_00035 */
typedef uint32 ResourceType;

/**
  * @typedef AlarmType
  *
  * Identifies an alarm object.
  *
  * see paragraph 13.6.1, page 62 of OSEK/VDX 2.2.3 spec
  */
/* @Trace: SafeOs_SUD_DATATYPE_00032 */
typedef uint32 AlarmType;

/**
  * @typedef TrustedFunctionIndexType
  *
  * Identifies a trusted function.
  *
  * see Section 8.3.4 of AUTOSAR_SWS_OS
  */
/* @Trace: SafeOs_SUD_DATATYPE_00014 */
typedef uint32 TrustedFunctionIndexType;

/**
  * @typedef ScheduleTableType
  *
  * Identifies a schedule table.
  *
  * see Section 8.3.12 of AUTOSAR_SWS_OS
  */
/* @Trace: SafeOs_SUD_DATATYPE_00022 */
typedef uint32 ScheduleTableType;

/**
  * @typedef CounterType
  *
  * Identifies an Counter
  *
  * see Section 8.3.15 of AUTOSAR_SWS_OS
  */
/* @Trace: SafeOs_SUD_DATATYPE_00024 */
typedef uint32 CounterType;

/**
  * @typedef ProtectionReturnType
  *
  * Identifies a value which controls further actions of the OS on return from
  * the protection hook.
  *
  * see Section 8.3.16 of AUTOSAR_SWS_OS
  */
/* @Trace: SafeOs_SUD_DATATYPE_00025 */
typedef uint8 ProtectionReturnType;

/**
  * @typedef RestartType
  *
  * Defines the use of a Restart Task after terminating an OS-Application.
  *
  * see Section 8.3.17 of AUTOSAR_SWS_OS
  */
/* @Trace: SafeOs_SUD_DATATYPE_00026 */
typedef uint32 RestartType;

/**
  * @typedef ScheduleTableStatusType
  *
  * identifies the state of a ScheduleTable
  *
  * see Section 8.3.13 of AUTOSAR_SWS_OS
  */
/* @Trace: SafeOs_SUD_DATATYPE_00023 */
typedef uint8 ScheduleTableStatusType;

/**
  * @typedef ScheduleTableStatusRefType
  *
  * Points to a variable of the data type ScheduleTableStatusType.
  *
  * see Section 8.3.14 of AUTOSAR_SWS_OS
  */
/* @Trace: SafeOs_SUD_DATATYPE_00037 */
typedef P2VAR(ScheduleTableStatusType, AUTOMATIC, OS_VAR)
ScheduleTableStatusRefType;

/**
  * @struct AlarmBaseType
  *
  * This structure is defined as paragraph 13.6.1 of OSEK/VDX spec
  *
  * @see AlarmBaseType
  */
/* polyspace-begin MISRA-C3:D4.8 [Justified:Low] "Not request the object should be hidden" */
/* @Trace: SafeOs_SUD_DATATYPE_00008 */
typedef struct
{
  /* maximum possible allowed count values in tick */
  TickType  maxallowedvalue;

  /* number of ticks required to reach a counter-specific (significant) unit */
  TickType  ticksperbase;

  /* smallest allowed value for the cycle-parameter of
  SetRelAlarm/SetAbsAlarm (only for systems with extended status) */
  TickType  mincycle;
} AlarmBaseType;
/* polyspace-end MISRA-C3:D4.8 [Justified:Low] "Not request the object should be hidden" */
/**
  * @typedef AlarmBaseRefType
  *
  * References an #AlarmBaseType
  *
  * See paragraph 13.6.1 page 62 of OSEK/VDX 2.2.3 spec
  */
/* @Trace: SafeOs_SUD_DATATYPE_00009 */
typedef P2VAR(AlarmBaseType, AUTOMATIC, OS_VAR)  AlarmBaseRefType;

/**
  * This data type points to a structure which holds the arguments for
  * a call to a trusted function.
  */
/* @Trace: SafeOs_SUD_DATATYPE_00015 */
typedef CONSTP2VAR(void, AUTOMATIC, OS_VAR) TrustedFunctionParameterRefType;

/**
  * This data type is a pointer which is able to point to any location in the
  * MCU address space.
  */
/* @Trace: SafeOs_SUD_DATATYPE_00019 */
typedef P2CONST(void, AUTOMATIC, OS_CONST) MemoryStartAddressType;

/**
  * This data type points to location where an ApplicationStateType can be stored.
  */
/* @Trace: SafeOs_SUD_DATATYPE_00013 */
typedef P2VAR(uint8, AUTOMATIC, OS_VAR) ApplicationStateRefType;

/**
  * This data type identifies an object.
  */
/* @Trace: SafeOs_SUD_DATATYPE_00018 */
typedef uint8 ObjectTypeType;

/**
  * This data type holds the size (in bytes) of a memory region.
  */
/* @Trace: SafeOs_SUD_DATATYPE_00020 */
typedef uint32 MemorySizeType;

/**
  * This data type identifies the state of an OS-Application.
  */
/* @Trace: SafeOs_SUD_DATATYPE_00012 */
typedef uint8 ApplicationStateType;

/**
  * This data type identifies if an OS-Application has access to an object.
  */
/* @Trace: SafeOs_SUD_DATATYPE_00017 */
typedef uint8 ObjectAccessType;

/**
  * This type holds information how a specific memory region can be accessed.
  */
/* @Trace: SafeOs_SUD_DATATYPE_00016 */
typedef uint8 AccessType;

/**
  * This data type identifies the Index of an Object Type.
  */
/* @Trace: SafeOs_SUD_DATATYPE_00041 */
typedef uint32 ObjectTypeIndex;

/**
  * This data type identifies the CoreID.
  */
/* @Trace: SafeOs_SUD_DATATYPE_00028 */
typedef uint16 CoreIDType;

/**
  * This data type identifies the Spinlock Id type.
  */
/* @Trace: SafeOs_SUD_DATATYPE_00029 */
typedef uint32 SpinlockIdType;

/**
  * This data type identifies the Os Service Id type.
  */
/* @Trace: SafeOs_SUD_DATATYPE_00010 */
typedef uint8 OSServiceIdType;

/* Type definition for TryToGetSpinlockType */
/* @Trace: SafeOs_SUD_DATATYPE_00039 */
typedef enum
{
  TRYTOGETSPINLOCK_NOSUCCESS=0,
  TRYTOGETSPINLOCK_SUCCESS
} TryToGetSpinlockType;

/* polyspace-end MISRA-C3:D4.8 [Justified:Low] "Not request the object should be hidden" */
/**
  * @typedef IdleModeType
  *
  * identifies the type of Idle
  *
  * see Section 8.3.21 of AUTOSAR_SWS_OS
  */
/* @Trace: SafeOs_SUD_DATATYPE_00030 */
typedef enum
{
    IDLE_NO_HALT = 0, /* The core does not perform any specific action during idle time */
    IDLE_CS_HALT, /* For chipset Idle mode */
    IDLE_UNKNOWN
}IdleModeType;

/**
  * @typedef Os_ExecutionType
  *
  * identifies the type of Os Execution in Asyn or Sync Modes
  *
  */
/* @Trace: SafeOs_SUD_DATATYPE_00042 */
typedef enum
{
  SYNC = 0,
  ASYNC
} Os_ExecutionType;

/**
  * This data type identifies the Peripheral Area ID.
  */
/* @Trace: SafeOs_SUD_DATATYPE_00031 */
typedef uint32 AreaIdType;

/**
  * @typedef PhysicalTimeType
  *
  * identifies the type is used for values returned by the conversion macro (see OS393())
  *
  */
/* @Trace: SafeOs_SUD_DATATYPE_00027 */
typedef uint32 PhysicalTimeType;

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#endif /* OS_TYPES_H */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
