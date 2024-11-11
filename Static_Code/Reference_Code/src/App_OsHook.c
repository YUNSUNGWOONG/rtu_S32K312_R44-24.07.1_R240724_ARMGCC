/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**            You can NOT use this sample code for Product Release            **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os.h"
#include "Os_Hook.h"
#include "Os_Ram.h"
#include "App_OsHook.h"
#include "EcuM.h"
#if (OS_ERRM_USED == STD_ON)
#include "ErrM.h"
#endif
#include "Gpt_Cfg.h"
#include "Gpt.h"
#include "Os_Debug.h"

#include "Opf_OsProfiler.h"
#include "Opf_Cfg.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
FUNC(void, OS_CODE) AppCallbackOnSystemError(StatusType ErrorId);

#define OS_START_SEC_CODE
#include "MemMap.h"


FUNC(void, OS_CODE) ErrorHook(StatusType Error)
{
  /* Do not modify : Start */
  /* Code for OS Profiler ----------------------------------------------------*/
  if (E_OS_LIMIT == Error)
  {
    #if (OPF_PROFILE_ENABLED == STD_ON)
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    CoreIDType LddCoreID = GetCoreID();
    if (LddCoreID < OPF_CORE_COUNT)
    #else
    #if (OS_MULTICORE == STD_ON)
    CoreIDType LddCoreID = GetCoreID();
    if (LddCoreID == OS_CORE_ZERO)
    #endif
    #endif
    {
      Opf_SetLimitErrorEvent();
    }
    #endif
  }
  /*--------------------------------------------------------------------------*/
  
  AppCallbackOnSystemError(Error);
  /* Do not modify : End */
}

FUNC(void, OS_CODE) PreTaskHook(void)
{
  #if 0
  /* Do not modify : Start */
  #if (OS_DEBUG_CPULOAD == STD_ON)
  TaskType LddRunningTask;
  StatusType LddReturn;
  #endif
  
  #if (OS_DEBUG_CPULOAD == STD_ON)
  LddReturn = GetTaskID(&LddRunningTask);
  if ((LddReturn == E_OK) && (LddRunningTask == INVALID_TASK))
  {
   Os_GblEntryIdleTask[OS_ZERO] = OS_TRUE;
   Os_ResetIdleEntry();
  }
  else
  {
   Os_GblEntryIdleTask[OS_ZERO] = OS_FALSE;
  }
  #endif
  /* Do not modify : End */
  #endif
}

FUNC(void, OS_CODE) PostTaskHook(void)
{
  /* Do not modify : Start */
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_IsrEntryHook(CoreIDType LddCoreID, ISRType LddIsrId)
{
  /* Do not modify : Start */
  /* Code for OS Profiler ----------------------------------------------------*/
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreID < OPF_CORE_COUNT)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreID == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetPreIsrEvent();
  }
  #endif
  /* CPU/Interrupt load */
  #if (OS_DEBUG_CPULOAD == STD_ON)
  Os_ITEntryForCPULoad();
  #endif
  /*--------------------------------------------------------------------------*/
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_IsrExitHook(CoreIDType LddCoreID, ISRType LddIsrId)
{
  /* Do not modify : Start */
  /* Code for OS Profiler ----------------------------------------------------*/
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreID < OPF_CORE_COUNT)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreID == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetPostIsrEvent();
  }
  #endif
  /* CPU/Interrupt load */
  #if (OS_DEBUG_CPULOAD == STD_ON)
  Os_ITExitForCPULoad();
  #endif
  /*--------------------------------------------------------------------------*/
  /* Do not modify : End */
}

/** S32K14x RTU 20.03.1 Add **/
FUNC(void, OS_CODE) Os_IsrKillHook(CoreIDType LddCoreId, ISRType LddIsrId)
{
  #if (OS_DEBUG_CPULOAD == STD_ON)
  Os_ITExitForCPULoad();
  #endif
}

FUNC(void, OS_CODE) Os_IdleEntryHook(CoreIDType LddCoreID)
{
  /* Do not modify : Start */
  Os_SetIdleForCPULoad();
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_IdleExitHook(CoreIDType LddCoreID)
{
  /* Do not modify : Start */
  /* Do not modify : End */
}

FUNC(void, OS_CODE) StartupHook(void)
{
  /* Do not modify : Start */
  Os_InitDebugFeatures();
  /* Code for OS Profiler ----------------------------------------------------*/
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OS_MULTICORE == STD_ON)
  // Add Start //
  CoreIDType LddCoreID = GetCoreID();
  if (LddCoreID < OPF_CORE_COUNT)
  #else
  #if (OS_MULTICORE == STD_ON)
    CoreIDType LddCoreID = GetCoreID();
  // Add End //
  if (LddCoreID == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_InitOsProfiler();
    Opf_StartOsProfiler();
  }
  #endif

  #if (OS_DEBUG_STACKDEPTH == STD_ON)
  /*Refer to ticket 44046*/
  Os_FillStackPattern();
  #endif
  /*--------------------------------------------------------------------------*/

/* Temporary changed by integrator - Start */
  // #if (OS_DEBUG_CPULOAD == STD_ON)
  // /* Initialize LPIT timer for CPU load */
  // Os_InitCPULoad();
  // #endif
/* Temporary changed by integrator - End */
  
/* Temporary changed by integrator - Start */
  // OS_LPIT_MCR.B.DOZE_EN = 1;
/* Temporary changed by integrator - End */

  /* If OS timer is Software, user must activated the below code. ------------------------------------------*/
  // Gpt_StopTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_STM);
  // Gpt_EnableNotification(GptConf_GptChannelConfiguration_GptChannelConfiguration_STM);
  // Gpt_StartTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_STM, 10000);
  // Gpt_StopTimer(GptChannelConfiguration_STM);
  // Gpt_EnableNotification(GptChannelConfiguration_STM);
  // Gpt_StartTimer(GptChannelConfiguration_STM, 10000);
  /*--------------------------------------------------------------------------------------------------------*/
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_TaskActivationHook(CoreIDType LddCoreID, TaskType LddTaskId)
{
  /* Do not modify : Start */
  /* Code for OS Profiler ----------------------------------------------------*/
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreID < OPF_CORE_COUNT)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreID == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetTaskEvent(LddTaskId, OPF_TASK_ACTIVATED);
  }
  #endif
  /*--------------------------------------------------------------------------*/
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_TaskTerminationHook(CoreIDType LddCoreID, TaskType LddTaskId)
{
  /* Do not modify : Start */
  /* Code for OS Profiler ----------------------------------------------------*/
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreID < OPF_CORE_COUNT)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreID == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetTaskEvent(LddTaskId, OPF_TASK_SUSPENDED);
  }
  #endif
  /*--------------------------------------------------------------------------*/
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_TaskPreemptionHook(CoreIDType LddCoreID, TaskType LddTaskId)
{
  /* Do not modify : Start */
  /* Code for OS Profiler ----------------------------------------------------*/
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreID < OPF_CORE_COUNT)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreID == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetTaskEvent(LddTaskId, OPF_TASK_READY);
  }
  #endif
  /*--------------------------------------------------------------------------*/
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_TaskRunningHook(CoreIDType LddCoreID, TaskType LddTaskId, TaskStateType LddTaskState)
{
  /* Do not modify : Start */
  #if (OS_DEBUG_CPULOAD == STD_ON)
  TaskType LddRunningTask;
  StatusType LddReturn;
  #endif
  
  /* Code for OS Profiler ----------------------------------------------------*/
  #if (OPF_PROFILE_ENABLED == STD_ON)
  OpfRecModeType LddOpfMode;
  LddOpfMode = Opf_GetOsProfilerRecMode();
  
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreID < OPF_CORE_COUNT)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreID == OS_CORE_ZERO)
  #endif
  #endif
  {
    /* Check restart */
    if (LddOpfMode == OPF_RECMODE_RESTART)
    {
      Opf_RestartOsProfiler();
    }
    Opf_SetTaskEvent(LddTaskId, OPF_TASK_RUNNING);
  }
  #endif
  /*--------------------------------------------------------------------------*/
  
  #if (OS_DEBUG_CPULOAD == STD_ON)
  LddReturn = GetTaskID(&LddRunningTask);
  if ((LddReturn == E_OK) && (LddRunningTask == INVALID_TASK))
  {
    Os_GblEntryIdleTask[OS_ZERO] = OS_TRUE;
    Os_ResetIdleEntry();
  }
  else
  {
    Os_GblEntryIdleTask[OS_ZERO] = OS_FALSE;
  }
  #endif
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_TaskWaitingHook(CoreIDType LddCoreID, TaskType LddTaskId)
{
  /* Do not modify : Start */
  /* Code for OS Profiler ----------------------------------------------------*/
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreID < OPF_CORE_COUNT)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreID == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetTaskEvent(LddTaskId, OPF_TASK_WAITING);
  }
  #endif
  /*--------------------------------------------------------------------------*/
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_TaskReleaseHook(CoreIDType LddCoreID, TaskType LddTaskId)
{
  /* Do not modify : Start */
  /* Code for OS Profiler ----------------------------------------------------*/
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreID < OPF_CORE_COUNT)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreID == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetTaskEvent(LddTaskId, OPF_TASK_READY);
  }
  #endif
  /*--------------------------------------------------------------------------*/
  /* Do not modify : End */
}

/* Temporary changed by integrator - Start */
//FUNC(void, OS_CODE) Gpt_Os_Sys_Timer_Notif(void)
//{
//  (void)IncrementCounter(OsCounter_Main);
//}
/* Temporary changed by integrator - End */

FUNC(void, OS_CODE) ShutdownHook(StatusType Error)
{
  /* Do not modify : Start */
  AppCallbackOnSystemError(Error);
  EcuM_Shutdown();
  /* Do not modify : End */
}

FUNC(void, OS_CODE) AppCallbackOnSystemError(StatusType ErrorId)
{
  if (ErrorId == E_OS_SYS_RAMECC)
  {
    /* RAM ECC Error occurred!!
     * All global variables are cleared before call this callback */
  }
  else
  {
    /* Do not modify : Start */
    Os_UpdateOsErrorInfo(ErrorId);
    #if (OS_ERRM_USED == STD_ON)
    ErrM_OsErrorNotification(Error);
    #endif
    /* Do not modify : End */
  }
}

FUNC(void, OS_CODE) Os_MeasureCPULoadRun(void)
{
  /* Do not modify : Start */
  #if (OS_DEBUG_CPULOAD == STD_ON)
/* Temporary changed by integrator - Start */
  Os_MeasureCPULoad();
/* Temporary changed by integrator - End */
  #endif
  /* Do not modify : End */
}

//FUNC(void, OS_CODE) Os_EnterIdle(IdleModeType IdleMode)
//{
//  /* Checking the real of Idle Mode */
//  switch(IdleMode)
//  {
//    case IDLE_NO_HALT:
//      Os_Halt();
//      break;
//    default:
//      /* Do Nothing */
//      break;
//  }
//}

FUNC(void, OS_CODE) Os_RamEccHandler(void)
{
}

FUNC(void, OS_CODE) Os_RomEccHandler(void)
{
}

//FUNC(void, OS_CODE) Os_MeasureCPULoad(void)
//{
//}

Std_ReturnType Det_ErrorHook(uint16 LusModuleId, uint8 LucInstanceId,
  uint8 LucApiId, uint8 LucErrorId)
{
	return E_OK;
}

#define OS_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

