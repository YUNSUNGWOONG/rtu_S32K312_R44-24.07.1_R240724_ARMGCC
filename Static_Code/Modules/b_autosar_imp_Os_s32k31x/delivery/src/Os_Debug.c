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
**  SRC-MODULE: Os_Debug.c                                                    **
**                                                                            **
**  TARGET    : s32k31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Debug feature(CPU/IT Load, Stack Depth)          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.1.0      7-Apr-2023    HG.Kim        Redmine #39577                      **
** 1.0.0     11-Jan-2023    HG.Kim        Redmine #38437                      **
*******************************************************************************/

/*******************************************************************************
**                      Polyspace begin                                       **
*******************************************************************************/
/* polyspace:begin<RTE:ABS_ADDR:Not a defect:Justify with annotations> Absolute address are used to get register value and stack address */
/* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:begin<MISRA-C3:8.7:Not a defect:Justify with annotations> function shall be used by other files so provided external linkage */
/* polyspace:begin<VARIABLE:ALL:Not a defect:Justify with annotations> unused Global Variable may be used for other Test application */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Debug.h"

#include "Os_Arch_Interrupt.h"
#include "Os_Ram.h"
#include "Os_Multicore.h"
#include "Os_Arch_Timer.h"
#include "Os_Arch_Regs.h"
#include "Os_Arch_Context.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define OS_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/** This global variable used to save elapsed CPU time. */
VAR(uint32, OS_VAR) Os_GulCPUTimeElapsed[OS_CORE_COUNT];
/** This global variable used to save previous timestamp for CPU load. */
VAR(uint32, OS_VAR) Os_GulTimestampBefore[OS_CORE_COUNT];
/** This global variable used to save idle time. */
VAR(uint32, OS_VAR) Os_GulCPUTimeInIdle[OS_CORE_COUNT];
/** This global variable used to save interrupt time. */
VAR(uint32, OS_VAR) Os_GulCPUTimeInIT[OS_CORE_COUNT];
/** This global variable used to save timestamp when enter idle mode. */
VAR(uint32, OS_VAR) Os_GulIdleEntryTime[OS_CORE_COUNT];
/** This global variable used to save timestamp when enter interrupt context. */
VAR(uint32, OS_VAR) Os_GulITEntryTime[OS_CORE_COUNT];
/** This global variable used to save count of measures. */
VAR(uint32, OS_VAR) Os_GulMeasureCount[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/** This global variable used to save CPU load. */
VAR(uint16, OS_VAR) Os_GusCPULoad[OS_CORE_COUNT];
/** This global variable used to save Interrupt load. */
VAR(uint16, OS_VAR) Os_GusITLoad[OS_CORE_COUNT];
/** This global variable used to save peak CPU load. */
VAR(uint16, OS_VAR) Os_GusCPULoadPeak[OS_CORE_COUNT];
/** This global variable used to save peak Interrupt load. */
VAR(uint16, OS_VAR) Os_GusITLoadPeak[OS_CORE_COUNT];
/** This global variable used to save mean CPU load. */
VAR(uint16, OS_VAR) Os_GusCPULoadMean[OS_CORE_COUNT];
/** This global variable used to save mean Interrupt load. */
VAR(uint16, OS_VAR) Os_GusITLoadMean[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/** This global variable used to save sum of Interrupt load. */
VAR(Os_uint64, OS_VAR) Os_GullITLoadSum[OS_CORE_COUNT];
/** This global variable used to save sum of CPU load. */
VAR(Os_uint64, OS_VAR) Os_GullCPULoadSum[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"


#define OS_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/** This global Variable used as a flag to hold idle mode. */
VAR(boolean, OS_VAR) Os_GblInIdleMode[OS_CORE_COUNT];
/** This global variable used to indicate entry of idle task. */
VAR(boolean, OS_VAR) Os_GblEntryIdleTask[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/** This global Variable used to check the interrupt context. */
VAR(uint8, OS_VAR) Os_GucITCount[OS_CORE_COUNT];
#define OS_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/** This global Variable indicates that Power Mode transition is occurred. */
VAR(boolean, OS_VAR) Os_GblPmTransFlag;
#define OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OS_START_SEC_CODE
#include "MemMap.h"

FUNC(void, OS_CODE) Os_SumCPUTimeInIT(uint32 LulTimestampNow);
/***************************************************************************//**
 * Function Name        : Os_InitDebugFeatures
 *
 * Service ID           : NA
 *
 * Description          : This function initializes CPU and IT load variables.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulCPUTimeElapsed, Os_GulTimestampBefore,
 *                        Os_GulCPUTimeInIdle, Os_GulIdleEntryTime,
 *                        Os_GblInIdleMode, Os_GulCPUTimeInIT,
 *                        Os_GulITEntryTime, Os_GucITCount, Os_GusCPULoad,
 *                        Os_GusITLoad, Os_GusCPULoadPeak, Os_GusITLoadPeak
 *                        Os_GusCPULoadMean, Os_GusITLoadMean, 
 *                        Os_GullCPULoadSum, Os_GullITLoadSum, 
 *                        Os_GulMeasureCount, Os_GblEntryIdleTask
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/

FUNC(void, OS_CODE) Os_InitDebugFeatures(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  Os_GulCPUTimeElapsed[OS_CORE_ID] = OS_ZERO;

/* polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
  Os_GulTimestampBefore[OS_CORE_ID] = OS_GET_TIMESTAMP();
/* polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */

  /* Initialize value is set to ignore first measurement */
  Os_GulCPUTimeInIdle[OS_CORE_ID] = 0x7FFFFFFFu;
  Os_GulIdleEntryTime[OS_CORE_ID] = OS_ZERO;
  Os_GblInIdleMode[OS_CORE_ID] = OS_FALSE;

  Os_GulCPUTimeInIT[OS_CORE_ID] = OS_ZERO;
  Os_GulITEntryTime[OS_CORE_ID] = OS_ZERO;
  Os_GucITCount[OS_CORE_ID] = OS_ZERO;

  Os_GusCPULoad[OS_CORE_ID] = OS_ZERO;
  Os_GusITLoad[OS_CORE_ID] = OS_ZERO;
  Os_GusCPULoadPeak[OS_CORE_ID] = OS_ZERO;
  Os_GblEntryIdleTask[OS_CORE_ID] = OS_FALSE;
  Os_GusITLoadPeak[OS_CORE_ID] = OS_ZERO;
  Os_GusCPULoadMean[OS_CORE_ID] = OS_ZERO;
  Os_GusITLoadMean[OS_CORE_ID] = OS_ZERO;
  Os_GullCPULoadSum[OS_CORE_ID] = OS_ZERO;
  Os_GullITLoadSum[OS_CORE_ID] = OS_ZERO;
  Os_GulMeasureCount[OS_CORE_ID] = OS_ZERO;

  Os_GblPmTransFlag = OS_FALSE;
}

/***************************************************************************//**
 * Function Name        : Os_ITEntryForCPULoad
 *
 * Service ID           : NA
 *
 * Description          : Update idle time.
 *                        Start CPU occupancy time measure in Interrupt.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulCPUTimeInIdle, Os_GulIdleEntryTime,
 *                        Os_GblInIdleMode, Os_GulITEntryTime, Os_GucITCount,
 *                        Os_GblEntryIdleTask
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ITEntryForCPULoad(void)
{
  uint32 LulTimestampNow;
  uint32 LulCPUTimeInIdle;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

/* polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
  LulTimestampNow = OS_GET_TIMESTAMP();
/* polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* set Os_GblInIdleMode to TRUE if it is from idle task */
  if (Os_GblEntryIdleTask[OS_CORE_ID] == OS_TRUE)
  {
    Os_GblInIdleMode[OS_CORE_ID] = OS_TRUE;
  }

  /* Sum CPU time in IDLE */
  if (Os_GblInIdleMode[OS_CORE_ID] == OS_TRUE)
  {
    Os_GblInIdleMode[OS_CORE_ID] = OS_FALSE;

    if (LulTimestampNow >= Os_GulIdleEntryTime[OS_CORE_ID])
    {
      LulCPUTimeInIdle = (LulTimestampNow - Os_GulIdleEntryTime[OS_CORE_ID]);
    }
    else
    {
      LulCPUTimeInIdle = (OS_TIMESTAMP_MAX - Os_GulIdleEntryTime[OS_CORE_ID]);
      LulCPUTimeInIdle += (LulTimestampNow + OS_ONE);
    }

    /* add to Os_GulCPUTimeInIdle the duration of idle mode */
    Os_GulCPUTimeInIdle[OS_CORE_ID] += LulCPUTimeInIdle;

    /* reset idle entry time */
   if (Os_GblEntryIdleTask[OS_CORE_ID] == OS_TRUE)
    {
      /* polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
       Os_GulIdleEntryTime[OS_CORE_ID] = OS_GET_TIMESTAMP();
      /* polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
    }
  }

  /* Record IT entry time */
  if (Os_GucITCount[OS_CORE_ID] == OS_ZERO)
  {
    Os_GulITEntryTime[OS_CORE_ID] = LulTimestampNow;
  }
  Os_GucITCount[OS_CORE_ID]++;
}

/***************************************************************************//**
 * Function Name        : Os_SumCPUTimeInIT
 *
 * Service ID           : NA
 *
 * Description          : Update CPU time used in ISR.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param[in]             LulTimestampNow    Current timestamp
 *                                           (range : 0 ~ OS_TIMESTAMP_MAX)
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulCPUTimeInIT, Os_GulITEntryTime
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_SumCPUTimeInIT(uint32 LulTimestampNow)
{
  uint32 LulCPUTimeInIT;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  if (LulTimestampNow >= Os_GulITEntryTime[OS_CORE_ID])
  {
    LulCPUTimeInIT = (LulTimestampNow - Os_GulITEntryTime[OS_CORE_ID]);
  }
  else
  {
    LulCPUTimeInIT = (OS_TIMESTAMP_MAX - Os_GulITEntryTime[OS_CORE_ID]);
    LulCPUTimeInIT += (LulTimestampNow + OS_ONE);
  }

  /* add to Os_GulCPUTimeInIT the duration of ISR */
  Os_GulCPUTimeInIT[OS_CORE_ID] += LulCPUTimeInIT;
}

/***************************************************************************//**
 * Function Name        : Os_ITExitForCPULoad
 *
 * Service ID           : NA
 *
 * Description          : Stop CPU occupancy time measure in Interrupt.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GucITCount
 *
 *                        Function(s) invoked    :
 *                        Os_SumCPUTimeInIT()
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ITExitForCPULoad(void)
{
  uint32 LulTimestampNow;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
/* polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
  LulTimestampNow = OS_GET_TIMESTAMP();
/* polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* Sum CPU time in IT */
  Os_GucITCount[OS_CORE_ID]--;
  if (Os_GucITCount[OS_CORE_ID] == OS_ZERO)
  {
    Os_SumCPUTimeInIT(LulTimestampNow);
  }
}

/***************************************************************************//**
 * Function Name        : Os_ResetIdleEntry
 *
 * Service ID           : NA
 *
 * Description          : If an Interrupt is occurred after set idle flag but
 *                        not passed Halt(wait mode), then reset idle flag and
 *                        idle entry time
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : This function should be called from PreTaskHook()
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GblInIdleMode,
 *                        Os_GulIdleEntryTime, Os_GblEntryIdleTask
 *
 *                        Function(s) invoked    :
 *                        GetTaskID()
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ResetIdleEntry(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "configured memory access index" */
  if ((Os_GddIdleTaskId[OS_CORE_ID] == Os_GpLinkTask[OS_CORE_ID]->ddTaskID) &&
       (Os_GblBeforeHalt[OS_CORE_ID] == OS_TRUE))
  {
    /* @Trace: SafeOs_SUD_API_38902 */
    Os_GblInIdleMode[OS_CORE_ID] = OS_TRUE;
    /* polyspace<MISRA-C:11.3:Not a defect:Justify with annotations> This is to access registers which are assigned to absolute address  */
    Os_GulIdleEntryTime[OS_CORE_ID] = OS_GET_TIMESTAMP();
  }
}
/***************************************************************************//**
 * Function Name        : Os_MeasureCPULoad
 *
 * Service ID           : NA
 *
 * Description          : This service measures CPU and IT load.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param[in]           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulCPUTimeElapsed, Os_GulTimestampBefore,
 *                        Os_GulCPUTimeInIdle, Os_GusCPULoad, Os_GusITLoad,
 *                        Os_GusCPULoadPeak, Os_GusITLoadPeak,
 *                        Os_GblPmTransFlag, Os_GusCPULoadMean,
 *                        Os_GusITLoadMean, Os_GullITLoadSum, Os_GullCPULoadSum
 *
 *                        Function(s) invoked    :
 *                        Os_SumCPUTimeInIT()
 ******************************************************************************/
FUNC(void, OS_CODE) Os_MeasureCPULoad(void)
{

  uint32 LulTimestampNow;
  uint32 LulCPUTimeElapsed;
  uint32 LulCPULoad;
  uint32 LulMeasureCount;
  boolean LblMeasurementFail = OS_FALSE;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

/* polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
  LulTimestampNow = OS_GET_TIMESTAMP();
/* polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */

  /* Get the elapsed time since entering here last. */
  if (LulTimestampNow > Os_GulTimestampBefore[OS_CORE_ID])
  {
    /* @Trace: SafeOs_SUD_API_39002 */
    LulCPUTimeElapsed = (LulTimestampNow - Os_GulTimestampBefore[OS_CORE_ID]);
  }
  else if (LulTimestampNow < Os_GulTimestampBefore[OS_CORE_ID])
  {
    /* @Trace: SafeOs_SUD_API_39003 */
  /* polyspace-begin MISRA-C3:D1.1 [Justified:Low] "This is to prevent overflow warning. Overflow does not occur because of if statement" */
    LulCPUTimeElapsed = (OS_TIMESTAMP_MAX - Os_GulTimestampBefore[OS_CORE_ID]);
    LulCPUTimeElapsed += (LulTimestampNow + OS_ONE);
 /* polyspace-end MISRA-C3:D1.1 [Justified:Low] "This is to prevent overflow warning. Overflow does not occur because of if statement" */
  }
  else
  {
    LulCPUTimeElapsed = OS_TIMESTAMP_MAX;
  }
  Os_GulTimestampBefore[OS_CORE_ID] = LulTimestampNow;

  /* If entering to Low Power Mode, restart CPU Load measure */
  if (Os_GblPmTransFlag == OS_TRUE)
  {
    LblMeasurementFail = OS_TRUE;
    Os_GblPmTransFlag = OS_FALSE;
  }
  /* Os_GulCPUTimeElapsed overflows */
  else if ((OS_TIMESTAMP_MAX - Os_GulCPUTimeElapsed[OS_CORE_ID]) < LulCPUTimeElapsed)
  {
    LblMeasurementFail = OS_TRUE;
  }
  else
  {
    Os_GulCPUTimeElapsed[OS_CORE_ID] += LulCPUTimeElapsed;
    /* In case that OS enters the idle state rarely
     * or measurement interval is too small
     */
    if ((Os_GulCPUTimeElapsed[OS_CORE_ID] < Os_GulCPUTimeInIdle[OS_CORE_ID]) ||
        (Os_GulCPUTimeElapsed[OS_CORE_ID] < Os_GulCPUTimeInIT[OS_CORE_ID]))
    {
      LblMeasurementFail = OS_TRUE;
    }
  }

  if (LblMeasurementFail == OS_FALSE)
  {
    if (Os_GulCPUTimeElapsed[OS_CORE_ID]<(OS_TIMESTAMP_MAX/OS_FULL_PERMILLAGE))
    {
      /* Calculate CPU load */
      LulCPULoad = Os_GulCPUTimeElapsed[OS_CORE_ID] -
                                              Os_GulCPUTimeInIdle[OS_CORE_ID];
      LulCPULoad = (LulCPULoad * OS_FULL_PERMILLAGE) /
                                             Os_GulCPUTimeElapsed[OS_CORE_ID];
      Os_GusCPULoad[OS_CORE_ID] = (uint16)LulCPULoad;
      /* Calculate IT load */
      /* If current context is ISR */
      if (Os_GucITCount[OS_CORE_ID] > OS_ZERO)
      {
        Os_SumCPUTimeInIT(LulTimestampNow);
        /* Updating Interrupt entry time is required
         * when call this function in ISR */
        Os_GulITEntryTime[OS_CORE_ID] = LulTimestampNow;
      }
      LulCPULoad = Os_GulCPUTimeInIT[OS_CORE_ID];
      LulCPULoad = (LulCPULoad * OS_FULL_PERMILLAGE) /
                                             Os_GulCPUTimeElapsed[OS_CORE_ID];
      Os_GusITLoad[OS_CORE_ID] = (uint16)LulCPULoad;
    }
    else
    {
      /* Calculate CPU load */
      LulCPULoad = Os_GulCPUTimeElapsed[OS_CORE_ID] -
                                              Os_GulCPUTimeInIdle[OS_CORE_ID];
      LulCPULoad = LulCPULoad /
                      (Os_GulCPUTimeElapsed[OS_CORE_ID] / OS_FULL_PERMILLAGE);
      Os_GusCPULoad[OS_CORE_ID] = (uint16)LulCPULoad;
      /* Calculate IT load */
      /* If current context is ISR */
      if (Os_GucITCount[OS_CORE_ID] > OS_ZERO)
      {
        Os_SumCPUTimeInIT(LulTimestampNow);
        /* Updating Interrupt entry time is required
         * when call this function in ISR */
        Os_GulITEntryTime[OS_CORE_ID] = LulTimestampNow;
      }
      LulCPULoad = Os_GulCPUTimeInIT[OS_CORE_ID];
      LulCPULoad = LulCPULoad /
                      (Os_GulCPUTimeElapsed[OS_CORE_ID] / OS_FULL_PERMILLAGE);
      Os_GusITLoad[OS_CORE_ID] = (uint16)LulCPULoad;
    }

    /* Update peak load */
    /* Exclude illegal output of CPU load  */
    if (Os_GusCPULoad[OS_CORE_ID] <= OS_FULL_PERMILLAGE)
    {
      if (Os_GusCPULoad[OS_CORE_ID] > Os_GusCPULoadPeak[OS_CORE_ID])
      {
        Os_GusCPULoadPeak[OS_CORE_ID] = Os_GusCPULoad[OS_CORE_ID];
      }
    }

    if (Os_GusITLoad[OS_CORE_ID] <= OS_FULL_PERMILLAGE)
    {
      if (Os_GusITLoad[OS_CORE_ID] > Os_GusITLoadPeak[OS_CORE_ID])
      {
        Os_GusITLoadPeak[OS_CORE_ID] = Os_GusITLoad[OS_CORE_ID];
      }
    }
    
    /* Update mean load */
    if(Os_GulMeasureCount[OS_CORE_ID] < OS_MEASURECOUNT_MAX)
    {
      Os_GulMeasureCount[OS_CORE_ID]++;
    }
    LulMeasureCount = Os_GulMeasureCount[OS_CORE_ID];
    
    Os_GullITLoadSum[OS_CORE_ID] += Os_GusITLoad[OS_CORE_ID];
    Os_GullCPULoadSum[OS_CORE_ID] += Os_GusCPULoad[OS_CORE_ID];    
    Os_GusITLoadMean[OS_CORE_ID] = (uint16)(Os_GullITLoadSum[OS_CORE_ID] /
      LulMeasureCount);
    Os_GusCPULoadMean[OS_CORE_ID] = (uint16)(Os_GullCPULoadSum[OS_CORE_ID] /
      LulMeasureCount);

    if(LulMeasureCount == OS_MEASURECOUNT_MAX)
    {
      Os_GulMeasureCount[OS_CORE_ID] = OS_ZERO;
      Os_GullITLoadSum[OS_CORE_ID] = OS_ZERO;
      Os_GullCPULoadSum[OS_CORE_ID] = OS_ZERO;
    }

  }

    /* Restart measurement */
    Os_GulCPUTimeElapsed[OS_CORE_ID] = OS_ZERO;
    Os_GulCPUTimeInIdle[OS_CORE_ID] = OS_ZERO;
    Os_GulCPUTimeInIT[OS_CORE_ID] = OS_ZERO;

}
/* polyspace:end<RTE:UNR:Not a defect:Justify with annotations> This code occurs by hardware failure not by software */
/***************************************************************************//**
 * Function Name        : Os_SetIdleForCPULoad
 *
 * Service ID           : NA
 *
 * Description          : Start CPU idle time measure and enter wait state
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : None Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GblInIdleMode, Os_GulIdleEntryTime,
 *
 *                        Function(s) invoked    :
 *                          None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_SetIdleForCPULoad(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
   /* polyspace +1 RTE:IDP [Not a defect:Low] "configured memory access index" */
  Os_GddIdleTaskId[OS_CORE_ID] = Os_GpLinkTask[OS_CORE_ID]->ddTaskID;
  if (Os_GblInIdleMode[OS_CORE_ID] == OS_FALSE)
  {
    #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
    OS_DISABLEINTERRUPTS();
    #endif

    Os_GblInIdleMode[OS_CORE_ID] = OS_TRUE;
    /* polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
    Os_GulIdleEntryTime[OS_CORE_ID] =  OS_GET_TIMESTAMP();
    /* polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> pointer to integral type should be used to access register */
    Os_GblBeforeHalt[OS_CORE_ID] = OS_TRUE;
    #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
    OS_ENABLEINTERRUPTS();
    #endif
  }
}

/***************************************************************************//**
 * Function Name        : Os_ClearCPULoadPeak
 *
 * Service ID           : NA
 *
 * Description          : Clear CPU Load Peak value in current core.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GusCPULoadPeak
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ClearCPULoadPeak(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  Os_GusCPULoadPeak[OS_CORE_ID] = OS_ZERO;
}

/***************************************************************************//**
 * Function Name        : Os_ClearITLoadPeak
 *
 * Service ID           : NA
 *
 * Description          : Clear Interrupt Load Peak value in current core.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GusITLoadPeak
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ClearITLoadPeak(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  Os_GusITLoadPeak[OS_CORE_ID] = OS_ZERO;
}

/***************************************************************************//**
 * Function Name        : Os_UserGetCPULoad
 *
 * Service ID           : NA
 *
 * Description          : This service is used to get CPU and Interrupt Load.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : None Re-entrant
 *
 * @param[out]          : LpLoad     A pointer for save CPU and IT load
 *
 * @param[in]           :  None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GusCPULoad, Os_GusCPULoadPeak, Os_GusCPULoadMean,
 *                        Os_GusITLoad, Os_GusITLoadPeak, Os_GusITLoadMean
 *
 *                        Function(s) invoked    :
  *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_UserGetCPULoad(
                  P2VAR(Os_LoadType, AUTOMATIC, OS_VAR) LpLoad, boolean restart)
{
  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  uint32 LulIntStat;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);


  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  LulIntStat = OS_DISABLE_AND_SAVE_INTERRUPTS();
  #endif 
  
  if (restart == OS_TRUE)
  {
    Os_MeasureCPULoad();
  }

  /* polyspace<RTE:UNR:Not a defect:Justify with annotations> Below code is verified and not a defect. */
  /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justify with annotations> NULL pointer check is done */
  if (LpLoad != NULL_PTR)
  {
    LpLoad->usCPULoad = Os_GusCPULoad[OS_CORE_ID];
    LpLoad->usCPULoadPeak = Os_GusCPULoadPeak[OS_CORE_ID];
    LpLoad->usCPULoadMean = Os_GusCPULoadMean[OS_CORE_ID];    
    LpLoad->usITLoad = Os_GusITLoad[OS_CORE_ID];
    LpLoad->usITLoadPeak = Os_GusITLoadPeak[OS_CORE_ID];
    LpLoad->usITLoadMean = Os_GusITLoadMean[OS_CORE_ID];
  }
  /* polyspace:end<MISRA-C3:D4.14> */

  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  /* polyspace:begin<MISRA-C3:10.3:Not a defect:Justify with annotations> type casting does not affect the result */
  OS_RESTORE_INTERRUPTS(LulIntStat);
  /* polyspace:end<MISRA-C3:10.3> */
  #endif
}
/***************************************************************************//**
 * Function Name        : Os_DebugH2L
 *
 * Service ID           : NA
 *
 * Description          : Set a flag which indicates Power Mode transition
 *                        This function is called at PM transition
 *                        (High Power -> Low Power)
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_PmTransFlag
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_DebugH2L(void)
{
  Os_GblPmTransFlag = OS_TRUE;
}

/***************************************************************************//**
 * Function Name        : Os_RestartMeanLoad
 *
 * Service ID           : NA
 *
 * Description          : This service is used to restart the measure of
 *                        the mean of CPU/IT load.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulMeasureCount
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_RestartMeanLoad(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  
  Os_GulMeasureCount[OS_CORE_ID] = OS_ZERO;
  Os_GullITLoadSum[OS_CORE_ID] = OS_ZERO;
  Os_GullCPULoadSum[OS_CORE_ID] = OS_ZERO;
}


#if (OS_DEBUG_STACKDEPTH == STD_ON)
/* polyspace-begin MISRA-C3:18.1 [Justified:Medium] "Checked array index is used" */
/***************************************************************************//**
 * Function Name        : Os_FillStackPattern
 *
 * Service ID           : NA
 *
 * Description          : This service is used to fill stack pattern
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : None Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStack
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, OS_CODE) Os_FillStackPattern(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType coreID = GetCoreID();
  #endif
  Os_StackType* pStackArea;
  uint16 LusStackSize;
  uint16 LusIdx;
  uint16 LusPos;

  #if (OS_MULTICORE == STD_ON)
  if(coreID == OS_CORE_ID_MASTER)
  #endif
  {
    for(LusIdx = OS_ZERO; LusIdx < OS_STACK_COUNT; LusIdx++)
    {
      pStackArea = Os_GaaStack[LusIdx].pStackArea;
      LusStackSize = Os_GaaStack[LusIdx].usStackSize;

      if((pStackArea != NULL_PTR) && (LusStackSize > OS_ONE))
      {
        #if (OS_STACK_MONITORING == STD_ON)
        /* pStackArea[OS_ZERO] is for 'AAAAAAAA' */
        for(LusPos = OS_ONE ; LusPos < LusStackSize; LusPos++)
        #else
        for(LusPos = OS_ZERO ; LusPos < LusStackSize; LusPos++)
        #endif
        {
          /* polyspace +2 RTE:IDP [Justified:Medium] "Valid position" */
          pStackArea[LusPos] = OS_STACK_EMPTY_PATTERN;
        }
      }
    }
  }
}

/***************************************************************************//**
 * Function Name        : Os_GetMaxStackUsage
 *
 * Service ID           : NA
 *
 * Description          : This service is used to get max stack usage of the
 *                        stack which is used by the target Task.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : None Re-entrant
 *
 * @param[out]            pStackUsage  Stack usage of the stack which is used by
 *                                     Task
 * @param[out]            pStackSize   Total stack size of the stack which is
 *                                     used by Task
 * @param[in]             LddTaskId    Task ID
 *
 * @return              : StatusType   E_OK          no error
 *                                     E_OS_STATE    error occurs during execution
 *
 * @pre                 : NA
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticTask, Os_GaaStack
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(StatusType, OS_CODE) Os_GetMaxStackUsage(TaskType LddTaskId, uint32* pStackUsage, uint32* pStackSize)
{
  StatusType LddStatusReturn;
  Os_StackType* pStackArea;
  uint32 LulStackUsage;
  uint32 LulStackEmpty;
  uint16 LusStackSize;
  uint16 LusIdx;
  uint16 LusPos;

  LulStackEmpty = 0u;
  LddStatusReturn = E_OS_STATE;
  if ((LddTaskId < (OS_TASK_COUNT + OS_CAT2_ISR_COUNT + OS_CORE_COUNT)) &&
      (pStackUsage != NULL_PTR) && (pStackSize != NULL_PTR))
  {
    /* 255 means invalid stack index */
    LusIdx = Os_GaaStaticTask[LddTaskId].ucStackIndex;
    if(LusIdx != 255)
    {
      pStackArea = Os_GaaStack[LusIdx].pStackArea;
      LusStackSize = Os_GaaStack[LusIdx].usStackSize;

      if((pStackArea != NULL_PTR) && (LusStackSize > OS_ONE))
      {
        #if (OS_STACK_MONITORING == STD_ON)
        /* pStackArea[OS_ZERO] is for 'AAAAAAAA' */
        for(LusPos = OS_ONE ; LusPos < LusStackSize; LusPos++)
        #else
        for(LusPos = OS_ZERO ; LusPos < LusStackSize; LusPos++)
        #endif
        {
          /* polyspace +3 RTE:NIV [Justified:Medium] "Valid index" */
          /* polyspace +2 RTE:IDP [Justified:Medium] "Valid position" */
          if(pStackArea[LusPos] != OS_STACK_EMPTY_PATTERN)
          {
            LulStackEmpty = LusPos;
            break;
          }
        }
        LulStackUsage = LusStackSize - LulStackEmpty;
        /* polyspace-begin MISRA-C3:D4.14 [Not a Defect] "NULL pointer check is done" */
        *pStackUsage = LulStackUsage * sizeof(Os_StackType);
        *pStackSize = LusStackSize * sizeof(Os_StackType);
        LddStatusReturn = E_OK;
        /* polyspace-end MISRA-C3:D4.14 */
      }
    }
  }
  return LddStatusReturn;
}
/* polyspace-end MISRA-C3:18.1 */
#endif /* #if (OS_DEBUG_STACKDEPTH == STD_ON) */

#define OS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Polyspace end                                       **
*******************************************************************************/
/* polyspace:end<RTE:ABS_ADDR:Not a defect:Justify with annotations> Absolute address are used to get register value and stack address */
/* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:end<MISRA-C3:8.7:Not a defect:Justify with annotations> function shall be used by other files so provided external linkage */
/* polyspace:end VARIABLE:ALL [Not a defect:Low] "unused Global Variable may be used for other Test application" */
/* polyspace:end<VARIABLE:ALL:Not a defect:Justify with annotations> unused Global Variable may be used for other Test application */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
