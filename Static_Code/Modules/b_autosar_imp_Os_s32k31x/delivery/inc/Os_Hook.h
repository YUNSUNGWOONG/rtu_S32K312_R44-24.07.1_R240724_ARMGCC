/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Os_Hook.h                                                     **
**                                                                            **
**  TARGET    : s32k31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS Improvement Code                                   **
**                                                                            **
**  PURPOSE   : Header file for Os Hook containing the declaration of error   **
**              information                                                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.0.0     11-Jan-2023    HG.Kim        Redmine #38437                      **
*******************************************************************************/

#ifndef OS_HOOK_H
#define OS_HOOK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os.h"
#include "Os_ErrorExternal.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define SZ_OSERROR 8
#define MASK_OSERROR_BUF 0x7

typedef unsigned char Os_ErrorValueType;
typedef unsigned char Os_ErrorApiType;

/* polyspace:begin<MISRA-C:18.4:Not a defect:Justify with annotations> These unions are used for debugging purposes only */
/** This union is defined for first parameter of OS API */
typedef union
{
  AlarmType OsAlarmId;
  ApplicationType OsApplicationId;
  CounterType OsCounterId;
  ResourceType OsResourceId;
  TaskType OsTaskId;
  ScheduleTableType OsScheduleTableId;
  ScheduleTableType OsScheduleTableId_From;
  TrustedFunctionIndexType OsTrustedFunctionIndexId;
  EventMaskType OsMask;
  SpinlockIdType OsSpinlockId;
} Os_ParamBlockType1;

/** This union is defined for second parameter of OS API */
typedef union
{
  ScheduleTableType OsScheduleTableId_To;
  TickType OsValue;
  P2VAR(void, AUTOMATIC, OS_VAR) OsTrustedFunctionParams;
  RestartType OsRestartOption;
  EventMaskType OsMaskParam2;
  TickType OsIncrement;
  TickType OsOffset;
  TickType OsStart;
} Os_ParamBlockType2;

/** This union is defined for third parameter of OS API */
typedef union
{
  TickType OsCycle;
} Os_ParamBlockType3;
/* polyspace:end<MISRA-C:18.4:Not a defect:Justify with annotations> These unions are used for debugging purposes only */

/** This structure is defined for OS error information type */
typedef struct
{
  Os_ErrorApiType enApi;       /**< OS API name */
  Os_ErrorValueType enErrorNo; /**< Error reason */
  Os_ParamBlockType1 unPar1;   /**< OS API first parameter */
  Os_ParamBlockType2 unPar2;   /**< OS API second parameter */
  Os_ParamBlockType3 unPar3;   /**< OS API third parameter */
} Os_ErrorType;

#define OS_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
extern VAR(uint32, OS_VAR) GulOsErrorCount;
extern VAR(uint32, OS_VAR) GulOsErrorLastPosition;
extern VAR(uint32, OS_VAR) Os_GulOsLimitError;
extern VAR(uint32, OS_VAR) Os_GulOsStackFaultError;
#define OS_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_ErrorType, OS_VAR) GucOsError[SZ_OSERROR];
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define OS_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, OS_CODE) Os_UpdateOsErrorInfo(StatusType LddError);
/* polyspace:begin<MISRA-C3:8.5:Not a defect:Justify with annotations> can be used for test application */
extern FUNC(void, OS_CALLOUT_CODE) AppCallbackOnSystemError(StatusType ErrorId);
/* polyspace:end<MISRA-C3:8.5> */
#define OS_STOP_SEC_CODE
#include "MemMap.h"

#endif /* OS_HOOK_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

