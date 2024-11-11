/*******************************************************************************
**  FILE-NAME: Opf_Cfg.h                                                      **
**                                                                            **
**  MODULE-NAME: AUTOSAR OsProfiler Module                                    **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Tool Version: 1.5.8                                                       **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/

/*
 * INPUT FILE:    Configuration\Ecu\Ecud_Os.arxml
 *                Configuration\Ecu\Ecud_OsProfiler.arxml
 * GENERATED ON: The time-stamp is removed
 */

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations> External linkage with array size makes error because of compiler optimization */

#ifndef OPF_CFG_H
#define OPF_CFG_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Opf_Types.h"
#include "Os.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Pre compile option for enabling OS Profiler */
#define OPF_PROFILE_ENABLED                 STD_ON

/* Pre Compile option for profiling ISR */
#define OPF_PROFILE_ISR                     STD_OFF

/* Pre Compile option for time index */
#define OPF_PROFILE_TIME_INDEX              STD_OFF

/* Direction of System Timer Clock for OsProfiler */
#define OPF_UPWARD_DIRECTION_COUNT          STD_ON

/* Total Number of Profile Event */
#define OPF_PROFILE_EVENT_COUNT             20u

/* Length of Event Queue */
#define OPF_EVENT_QUEUE_LENGTH              (OPF_PROFILE_EVENT_COUNT*2)

/* Total Number of Profiled Task */
#define OPF_PROFILE_TASK_COUNT              3u

/* Max Task Count */
#define OPF_MAX_TASK_ID                     255u

/* OsProfiler Number of Cores */
#define OPF_CORE_COUNT                      1u

/* Pre Compiler option for Os Profiler multi-core */
#define OPF_MULTICORE_ENABLED               STD_OFF

/* OPF_FREESCALE_MPC560XB */
#define OPF_FREESCALE_MPC560XB              1

/* OPF_RENESAS_RH850 */
#define OPF_RENESAS_RH850                   2

/* OPF_AUTRON_COMMON */
#define OPF_AUTRON_COMMON                   3

/* Target Operating System */
#define OPF_TARGET_OS                       OPF_AUTRON_COMMON

/* XOSC */
#define OPF_XOSC_CLOCK                      0u

/* Address of System Timer Clock for OsProfiler */
#define OPF_STM_TICK                        ((uint32 *) 1076314112u)

/* Max Tick of System Timer Clock for OsProfiler */
#define OPF_MAX_STM_TICK                    (4294967295u)

/* Frequency of System Timer Clock for OsProfiler (in KHz) */
#define OPF_STM_CLOCK                       (60000u)


/**
  * @struct STagTdd_Opf_ProfileEventQ
  *
  * This structure holds an information of profiled event queue.
  */
typedef struct STagTdd_Opf_ProfileEventQ
{
  /* Size of an event queue */
  OpfEventQueueSizeType ddEventQueueSize;
  /* Position for a last event in an event queue */
  OpfEventQueuePosType ddLastEventPos;
  /* Pointer to a profiled event queue */
  P2VAR(Tdd_Opf_ProfileTaskInfo, AUTOMATIC, OS_VAR) pCurProfiledTaskInfo;
  
  /* Pointer to a profiled event queue */
  Tdd_Opf_Event ddEvent[OPF_EVENT_QUEUE_LENGTH];
  
} Tdd_Opf_ProfileEventQ;

typedef struct STagTdd_Opf_EventQ
{

  /* Size of an event queue */
  OpfEventQueueSizeType ddEventQueueSize;
  /* Position for a last event in an event queue */
  OpfEventQueuePosType ddLastEventPos;
  /* Count of events */
  OpfEventCountType ddEventCount;
  
  /* Pointer to an event queue */
  Tdd_Opf_Event ddEvent[OPF_EVENT_QUEUE_LENGTH];
  
} Tdd_Opf_EventQ;

/**
  * @struct STagTdd_Opf_ProfileEventQ
  *
  * This structure holds an information of profiled event queue.
  */
typedef struct STagTdd_Opf_OsProfiler
{
  /* Record Mode of OS Profiler */
  OpfRecModeType ddRecMode;
  /* System Timer Clock */
  OpfClockType ddSTMClock;
  /* Next Index Tick */
  OpfTickType ddNextIndexTick;
  /* Pointer to a task information */
  P2VAR(Tdd_Opf_EventQ, AUTOMATIC, OS_VAR) pEventQ;
  /* Pointer to a task information */
  P2VAR(Tdd_Opf_ProfileEventQ, AUTOMATIC, OS_VAR) pProfileEventQ;
  
} Tdd_Opf_OsProfiler;

extern VAR(Tdd_Opf_ProfileTaskInfo, OS_VAR) 
                             Opf_GaaProfileTaskInfo[];


/*******************************************************************************
**                      Configuration Set Handles                             **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern FUNC(void, OPF_CODE) Opf_InitProfileTaskInfo(void);

#endif /* OPF_CFG_H */
/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations> External linkage with array size makes error because of compiler optimization */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
