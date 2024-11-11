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
**  SRC-MODULE: Os_Debug.h                                                    **
**                                                                            **
**  TARGET    : s32k31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for Os_Debug.c file containing the declaration    **
**              of Debug features(CPU/IT Load, Stack Depth) related functions **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
#ifndef OS_DEBUG_H
#define OS_DEBUG_H
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.1.0      7-Apr-2023    HG.Kim        Redmine #39577                      **
** 1.0.0     11-Jan-2023    HG.Kim        Redmine #38437                      **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:19.7:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro definition is required */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os.h"
#include "Os_Arch_Regs.h"
#include "Os_Imp_Cfg.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define OS_FULL_PERMILLAGE      1000u
/** The maximum value of timestamp */
#define OS_TIMESTAMP_MAX        0xFFFFFFFFu

/* polyspace<MISRA-C:1.1:Not a defect:Justify with annotations> 64 bit should be used to express large value  */
typedef unsigned long long Os_uint64;

/* Max count of measurement */
#define OS_MEASURECOUNT_MAX    0xFFFFFFFFu

/*#define OS_MULTICORE            STD_OFF */


/** This structure holds the CPU and Interrupt Load value. */
typedef struct
{
  uint16 usCPULoad;     /* Current CPU Load value */
  uint16 usCPULoadPeak; /* CPU Load Peak value after value reset */
  uint16 usCPULoadMean; /* CPU Load Mean value */
  uint16 usITLoad;      /* Current Interrupt Load value */
  uint16 usITLoadPeak;  /* Interrupt Load Peak value after value reset */
  uint16 usITLoadMean;  /* Interrupt Load Mean value */
} Os_LoadType;

#define OS_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/** This global variable used to save elapsed CPU time. */
extern VAR(uint32, OS_VAR) Os_GulCPUTimeElapsed[OS_CORE_COUNT];
/** This global variable used to save previous timestamp for CPU load. */
extern VAR(uint32, OS_VAR) Os_GulTimestampBefore[OS_CORE_COUNT];
/** This global variable used to save idle time. */
extern VAR(uint32, OS_VAR) Os_GulCPUTimeInIdle[OS_CORE_COUNT];
/** This global variable used to save interrupt time. */
extern VAR(uint32, OS_VAR) Os_GulCPUTimeInIT[OS_CORE_COUNT];
/** This global variable used to save timestamp when enter idle mode. */
extern VAR(uint32, OS_VAR) Os_GulIdleEntryTime[OS_CORE_COUNT];
/** This global variable used to save timestamp when enter interrupt context. */
extern VAR(uint32, OS_VAR) Os_GulITEntryTime[OS_CORE_COUNT];
/** This global variable used to save count of measures. */
extern VAR(uint32, OS_VAR) Os_GulMeasureCount[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/** This global variable used to save CPU load. */
extern VAR(uint16, OS_VAR) Os_GusCPULoad[OS_CORE_COUNT];
/** This global variable used to save Interrupt load. */
extern VAR(uint16, OS_VAR) Os_GusITLoad[OS_CORE_COUNT];
/** This global variable used to save peak CPU load. */
extern VAR(uint16, OS_VAR) Os_GusCPULoadPeak[OS_CORE_COUNT];
/** This global variable used to save peak Interrupt load. */
extern VAR(uint16, OS_VAR) Os_GusITLoadPeak[OS_CORE_COUNT];
/** This global variable used to save mean CPU load. */
extern VAR(uint16, OS_VAR) Os_GusCPULoadMean[OS_CORE_COUNT];
/** This global variable used to save mean Interrupt load. */
extern VAR(uint16, OS_VAR) Os_GusITLoadMean[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/** This global variable used to save sum of Interrupt load. */
extern VAR(Os_uint64, OS_VAR) Os_GullITLoadSum[OS_CORE_COUNT];
/** This global variable used to save sum of CPU load. */
extern VAR(Os_uint64, OS_VAR) Os_GullCPULoadSum[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/** This global Variable used as a flag to hold idle mode. */
extern VAR(boolean, OS_VAR) Os_GblInIdleMode[OS_CORE_COUNT];
/** This global variable used to indicate entry of idle task. */
extern VAR(boolean, OS_VAR) Os_GblEntryIdleTask[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/** This global Variable used to check the interrupt context. */
extern VAR(uint8, OS_VAR) Os_GucITCount[OS_CORE_COUNT];
/** This global variable used to save Idle Task ID. */
extern VAR(TaskType, OS_VAR) Os_GddIdleTaskId[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/** This global Variable indicates that Power Mode transition is occurred. */
extern VAR(boolean, OS_VAR) Os_GblPmTransFlag;
#define OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern FUNC(void, OS_CODE) Os_InitDebugFeatures(void);
extern FUNC(void, OS_CODE) Os_SetIdleForCPULoad(void);
extern FUNC(void, OS_CODE) Os_ResetIdleEntry(void);
extern FUNC(void, OS_CODE) Os_ITEntryForCPULoad(void);
extern FUNC(void, OS_CODE) Os_ITExitForCPULoad(void);
extern FUNC(void, OS_CODE) Os_ClearCPULoadPeak(void);
extern FUNC(void, OS_CODE) Os_ClearITLoadPeak(void);
extern FUNC(void, OS_CODE) Os_MeasureCPULoad(void);
extern FUNC(void, OS_CODE) Os_UserGetCPULoad(
                 P2VAR(Os_LoadType, AUTOMATIC, OS_VAR) LpLoad, boolean restart);
extern FUNC(void, OS_CODE) Os_RestartMeanLoad(void);
extern FUNC(void, OS_CODE) Os_DebugH2L(void);

#endif /* OS_DEBUG_H_ */

#if (OS_DEBUG_STACKDEPTH == STD_ON)
extern FUNC(void, OS_CODE) Os_FillStackPattern(void);
extern FUNC(StatusType, OS_CODE) Os_GetMaxStackUsage(TaskType LddTaskId,
                                       uint32* pStackUsage, uint32* pStackSize);
#endif


#if (OS_DEBUG_STACKDEPTH == STD_ON)
#define OS_STACK_EMPTY_PATTERN  0xEEEEEEEEu /* 'E'mpty */
#endif

/*******************************************************************************
**                      Polyspace end                                         **
*******************************************************************************/
/* polyspace:end<MISRA-C3:19.7:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro definition is required */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
