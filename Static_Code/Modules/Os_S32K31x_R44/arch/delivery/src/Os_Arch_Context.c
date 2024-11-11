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
**  SRC-MODULE: Os_Arch_Context.c                                             **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of port specific functionality                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
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
** 1.1.1     23-Nov-2023    HJ.Kim       Jira    CP44-3306                    **
** 1.1.0      1-Sep-2023    HJ.Kim       Jira    CP44-2528                    **
**           25-Jul-2023    HJ.Kim       Jira    CP44-1712                    **
**            8-Jun-2023    HJ.Kim       Jira    CP44-2090                    **
** 1.0.2     31-Dec-2022    TinHV        Jira    CP44-856                     **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:begin<RTE:OBAI:Not a defect:Justify with annotations> Configured array index */
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:11.1:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<MISRA-C3:18.4:Not a defect:Justify with annotations> Operators on pointer is used for better performance */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace-begin MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array" */
/* polyspace-begin CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
/* @Trace: SRS_Os_00097 */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os RAM header file */
#include "Os_Kernel.h"            /* Os Kernel header file */
#include "Os_Arch_Multicore.h"    /* Os Multi-core header file */
#include "Os_Application.h"       /* Os Application header file */
/* @Trace: SRS_BSW_00410 */
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_TimingProtection.h"  /* Os TimerProtection header file */
#endif
#include "Os_Arch_Interrupt.h"
#include "Os_Task.h"
#include "Os_Stack.h"
#include "Os_Arch_Context.h"
#if (OS_APP_MEMBLK_CNT != OS_ZERO)
#include "Os_Arch_MemPro.h"
#endif
#include "Os_Error.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_API_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#if (OS_APP_MEMBLK_CNT != OS_ZERO)
static FUNC(void, OS_CODE) Os_EndOfTask(void);
#endif

/*******************************************************************************
 * Function             : Os_ErrorTerminateTask
 *
 * Service ID           : OSServiceId_Os_ErrorTerminateTask
 *
 * Description          : This function is called when Task
 *                        terminated without TerminateTask()
 *                        This function process E_OS_MISSINGEND
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_003
 ******************************************************************************/
/* polyspace +2 MISRA-C3:8.7 [Not a defect:Low] "External visible function" */
FUNC(void, OS_CODE) Os_ErrorTerminateTask(void)
{
  /* @Trace: SafeOs_SUD_API_32401 */
  OS_SYSCALL_ERRORTERMINATETASK();
}

/*******************************************************************************
 * Function             : Os_EndOfTask
 *
 * Service ID           : NA
 *
 * Description          : This function is called when non-trusted Task
 *                        terminated without TerminateTask()
 *                        Switch to supervisor mode and process E_OS_MISSINGEND
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Os_ErrorTerminateTask()
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_003
 ******************************************************************************/
static FUNC(void, OS_CODE) Os_EndOfTask(void)
{
  /* @Trace: SafeOs_SUD_API_36601 */
  Os_ErrorTerminateTask();
}

#if (OS_MEMORY_PROTECTION == STD_ON) && (OS_STARTUP_HOOK == STD_ON) && \
    ((OS_APP_STARTUP_HOOK == STD_ON) || (OS_APP_ERROR_HOOK == STD_ON) || \
    (OS_APP_SHUTDOWN_HOOK == STD_ON))
/*******************************************************************************
 * Function             : Os_NonTrustedAppHookTerminate
 *
 * Service ID           : NA
 *
 * Description          : This function is called when non-trusted Appplication
 *                        Hook terminated with Os_ReturnKernelStack()
 *                        Switch to supervisor mode
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 *
 *
 * @ingroup               
 ******************************************************************************/
static FUNC(void, OS_CODE) Os_NonTrustedAppHookTerminate(void)
{
  /* @Trace: SafeOs_SUD_API_36601 */
  OS_SYSCALL_RETURNKERNELSTACK();
}
#endif /* OS_MEMORY_PROTECTION == STD_ON */

#define OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/***************************************************************************//**
 * Function Name        : Os_ReInitContext
 *
 * Service ID           : NA
 *
 * Description          : This service is used to initialize context
 *                        from LpStaticTask
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            LpStaticTask : Pointer of Task/ISR info
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_003
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ReInitContext(P2CONST(
                           Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask)
{
  /* @Trace: SafeOs_SUD_API_36701 */
  LpStaticTask->pContext->ulLR = (uint32)&Os_EndOfTask;

  LpStaticTask->pContext->ulPSR = OS_TASK_INIT_PSR;  
  LpStaticTask->pContext->ulPC  = (uint32)LpStaticTask->pFuncEntry;
  LpStaticTask->pContext->ulEXC_RETURN = OS_EXC_RETURN_THREAD_MODE;
  #if (OS_FPU_SUPPORT == STD_ON)
  LpStaticTask->pContext->ulFPSCR = Os_GddTaskInitFPSCR;
  #endif
}

/***************************************************************************//**
 * Function             : Os_Dispatch
 *
 * Service ID           : NA
 *
 * Description          : This function is used to dispatch new Task
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticTask, Os_GpLinkTask, Os_GucInKernel
 *
 *                        Function(s) invoked    :
 *                        Os_RunTask(), Os_DoContextSwitch()
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_003
 ******************************************************************************/
FUNC(void, OS_CODE) Os_Dispatch(void)
{

  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  #if (OS_APP_MEMBLK_CNT != OS_ZERO)
  uint32 LulCtrl;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Get new Task */
  /* polyspace<RTE:NIV:Not a defect:Justify with annotations> Variable initialized at other location */
  LpStaticTask = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];


  /* Os_RunTask() */
  /* @Trace: SafeOs_SUD_API_37001 */
  Os_GucInKernel[OS_CORE_ID]++;
  Os_SetTaskStackPointer();
  #if (OS_TASK == STD_ON)
  Os_RunTask();
  #endif /*OS_TASK == STD_ON*/
  Os_GucInKernel[OS_CORE_ID]--;

  #if (OS_APP_MEMBLK_CNT != OS_ZERO)
  LulCtrl = __MRS(__CONTROL);
  /* If Application is non-trusted, set privileged mode to user */
  if (LpStaticTask->ddAppId < (ApplicationType)Os_Trusted_Start_Indx)
  {
    /* @Trace: SafeOs_SUD_API_37002 */
    /* CTRL.nPRIV = 1 which means Thread mode has unprivileged access */
    LulCtrl |= 0x00000001u;
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_37003 */
    /* CTRL.nPRIV = 0 which means Thread mode has privileged access */
    LulCtrl &= 0xFFFFFFFEu;
  }
  __MSR(__CONTROL, LulCtrl);
  #endif

  /* Context-Switch */
  /* @Trace: SafeOs_SUD_API_37004 */
  Os_DoContextSwitch(LpStaticTask->pContext);
}

/***************************************************************************//**
 * Function Name        : Os_SetTaskStackPointer
 *
 * Service ID           : NA
 *
 * Description          : This service is used to set basic task or CAT2
 *                        Isr's stack base address
 *                        base address
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : StartOs() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GpStaticTask, Os_GaaStaticTask, Os_GulOsAppSP,
 *                        Os_GulUserSP, Os_GaaStack
 *
 *                        Function(s) invoked    :
 *                        Os_GetStackPointer
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_003
 *******************************************************************************/
/* polyspace +2 MISRA-C3:8.7 [Not a defect:Low] "External visible function" */
FUNC(void, OS_CODE) Os_SetTaskStackPointer(void)
{
  /* Type of stacks                                                          */
  /*                                                                         */
  /* 1. system stack        : used by start-up code, OS kernel               */
  /* 2. user stack          : used by Basic Task (without OS-Application),   */
  /*                          Os_sleep Task (without/with OS-Application)    */
  /* 3. application stack   : used by Basic Task (with OS-Application)       */
  /* 4. extended task stack : used by extended task                          */

  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpPreTask;
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpRunTask;
  #if (OS_EVENT == STD_ON)
  P2CONST(Tdd_Os_Stack, AUTOMATIC, OS_CONST) LpTaskStack;
  #endif
  uint32 LulNewTaskSP;
  #if (OS_MULTICORE == STD_ON)
  /* @Trace: SafeOs_SUD_API_37501 */
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  /* @Trace: SafeOs_SUD_API_37502 */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* polyspace<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
  LpPreTask = Os_GpStaticTask[OS_CORE_ID];
  /* polyspace +2 RTE:NIV [Justified:Medium] "Variable initialized at other location" */
  LpRunTask = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];

  if(LpPreTask != LpRunTask)
  {
    /* Basic task is preempted by other task */
    /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually*/
    /* polyspace +3 RTE:NIV [Justified:Medium] "Variable initialized at other location" */
    if((LpPreTask->usType == OS_TASK_BASIC) &&
                                           (LpPreTask->pTask->ddState == READY))
    /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually*/
    {
      /* polyspace +3 RTE:NIV [Justified:Medium] "Variable initialized at other location" */
      /* polyspace-begin MISRA-C3:11.6 [Justified:Medium] "To save address data" */
      #if (OS_APPLICATION == STD_ON)
      if(LpPreTask->ddTaskId != OS_CORE_ID)
      {
        /* @Trace: SafeOs_SUD_API_37503 */
        /* polyspace +2 RTE:NIV [Justified:Medium] "Variable initialized at other location" */
        /* polyspace<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
        Os_GulOsAppSP[LpPreTask->ddAppId] =
                                        (uint32)Os_GetStackPointer(LpPreTask);
      }
      else
      #endif
      {
        /* @Trace: SafeOs_SUD_API_37504 */
        Os_GulUserSP[OS_CORE_ID] = (uint32)Os_GetStackPointer(LpPreTask);
      }
      /* polyspace-end MISRA-C3:11.6 */
    }
  }
  if(LpRunTask->usType == OS_TASK_BASIC)
  {
    /* Task to be run is new task */
    /* polyspace +2 RTE:NIV [Justified:Medium] "Variable initialized at other location" */
    if(LpRunTask->pTask->ddState == OS_READY_AND_NEW)
    {
      #if (OS_APPLICATION == STD_ON)
      if(LpRunTask->ddTaskId != OS_CORE_ID)
      {
        /* polyspace:begin<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
        /* polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
        /* polyspace:begin<MISRA-C:17.4:Not a defect:Justify with annotations> Increment operator on pointer used to achieve better throughput */
        /* @Trace: SafeOs_SUD_API_37505 */
        LulNewTaskSP = Os_GulOsAppSP[LpRunTask->ddAppId];
        /* polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
        /* polyspace:end<MISRA-C:17.4:Not a defect:Justify with annotations> Increment operator on pointer used to achieve better throughput */
        /* polyspace:end<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
      }
      else
      #endif
      {
        /* @Trace: SafeOs_SUD_API_37506 */
        LulNewTaskSP = Os_GulUserSP[OS_CORE_ID];
      }
      /*polyspace:begin<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by Osek not autron, and pointer conversion is required  */
      LpRunTask->pContext->pPowerOnSP = (Os_StackType*)LulNewTaskSP;
      LpRunTask->pContext->ulSP = LulNewTaskSP;
      /*polyspace:end<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by Osek not autron, and pointer conversion is required  */
    }
    /* Task to be run is previously preempted task */
    else if((LpRunTask->pTask->ddState == READY) ||
                                         (LpRunTask->pTask->ddState == RUNNING))
    {
      /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually*/
      #if (OS_APPLICATION == STD_ON)
      if(LpRunTask->ddTaskId != OS_CORE_ID)
      {
        /* @Trace: SafeOs_SUD_API_37507 */
        /* polyspace<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
        Os_GulOsAppSP[LpRunTask->ddAppId] =
                                        (uint32)LpRunTask->pContext->pPowerOnSP;
      }
      else
      #endif
      {
        /* @Trace: SafeOs_SUD_API_37508 */
        Os_GulUserSP[OS_CORE_ID] = (uint32)LpRunTask->pContext->pPowerOnSP;
      }
      /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually*/
    }
    else
    {
      /* @Trace: SafeOs_SUD_API_37509 */
      /* Do nothing */
    }
  }
  else if(LpRunTask->usType == OS_ISR2)
  {
    /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually*/
    #if (OS_APPLICATION == STD_ON)
    /* polyspace<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
    /* @Trace: SafeOs_SUD_API_37510 */
    Os_GulOsAppSP[LpRunTask->ddAppId] = (uint32)LpRunTask->pContext->pPowerOnSP;
    #else
    /* @Trace: SafeOs_SUD_API_37511 */
    Os_GulUserSP[OS_CORE_ID] = (uint32)LpRunTask->pContext->pPowerOnSP;
    #endif
    /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually*/
  }
  else
  {
    #if (OS_EVENT == STD_ON)
    /* polyspace +2 RTE:NIV [Justified:Medium] "Variable initialized at other location" */
    if(LpRunTask->pTask->ddState == OS_READY_AND_NEW)
    {
      /* Make Task's context for new Task */
      /* @Trace: SafeOs_SUD_API_37512 */
      LpTaskStack = &Os_GaaStack[LpRunTask->ucStackIndex];
      /* polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
      /* polyspace:begin<MISRA-C:17.4:Not a defect:Justify with annotations> Increment operator on pointer used to achieve better throughput */
      LpRunTask->pContext->ulSP =
                   (uint32)((LpTaskStack->pStackArea + LpTaskStack->usStackSize)
                                                      - OS_STACK_RSVD_SIZE);
      /* polyspace:end<MISRA-C:17.4:Not a defect:Justify with annotations> Increment operator on pointer used to achieve better throughput */
      /* polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
    }
    #endif
  }
} /* FUNC(void, OS_CODE) Os_SetTaskStackPointer(void) */

/***************************************************************************//**
 * Function Name        : Os_GetStackPointer
 *
 * Service ID           : NA
 *
 * Description          : This service is used to get stack pointer
 *                        from LpStaticTask
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            LpStaticTask : Pointer of Task/ISR info
 *
 * @return              : Stack pointer
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_003
 ******************************************************************************/
/* polyspace +2 MISRA-C3:20.7 [Justified:Low] "AUTOSAR compiler abstraction" */
FUNC(uint32*, OS_CODE) Os_GetStackPointer(P2CONST(
    Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask)
{
  P2VAR(uint32, AUTOMATIC, OS_VAR) LpStackaddress;
  /* @Trace: SafeOs_SUD_API_36801 */
  /* polyspace<RTE:NIV:Not a defect:Justify with annotations> Variable initialized at other location */
  /* polyspace +4 CERT-C:INT36-C [Justified:Low] "ptr point to a valid value P2VAR" */
  /* polyspace +3 RTE:NIP [Justified:Medium] "ptr points to a valid value and code is verified manually" */
  /* polyspace +2 MISRA-C3:11.6 [Justified:Medium] "To handle address data" */
  LpStackaddress = (uint32*)LpStaticTask->pContext->ulSP;

  if(LpStackaddress == (uint32*)0u)
  {
    /* @Trace: SafeOs_SUD_API_36802 */
    /* polyspace +2 MISRA-C3:11.6 [Justified:Medium] "To indicate invalid address" */
    LpStackaddress = (uint32*)INVALID_STACK_POINTER;
  }

  return (LpStackaddress);
} /* End of Os_GetStackPointer(P2CONST( */

/***************************************************************************//**
 * Function Name        : Os_GetStackSize
 *
 * Service ID           : NA
 *
 * Description          : This service is used to get current task's stack size
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LpStaticTask : Pointer of Task/ISR info
 *
 * @return              : Stack Size
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStack
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_003
 ******************************************************************************/
#if (OS_STACK_MONITORING == STD_ON)
FUNC(uint16, OS_CODE) Os_GetStackSize(P2CONST(
    Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask)
{
  /* - user stack frame              */
  /*   : 8 bytes is reserved for     */
  /*     terminating task            */
  /* |--------------|                */
  /* |      LR      | -> reserved    */
  /* |--------------|                */
  /* |      BC      | -> reserved    */
  /* |--------------|                */
  /* |      ...     |                */
  /* |--------------|                */
  /* |      LR      |                */
  /* |--------------|                */
  /* |      BC      |                */
  /* |--------------|                */

  uint16 LusStackSize;

  if((LpStaticTask->usType == OS_TASK_BASIC) ||
     (LpStaticTask->usType == OS_TASK_EXTENDED))
  {
    /* polyspace<RTE:OBAI:Not a defect:Justify with annotations> Configured array index */
    if(Os_GaaStack[LpStaticTask->ucStackIndex].usStackSize > 
                                                     (uint16)OS_STACK_RSVD_SIZE)
    {
      /* @Trace: SafeOs_SUD_API_36901 */
      LusStackSize = (Os_GaaStack[LpStaticTask->ucStackIndex].usStackSize)
          - (uint16)OS_STACK_RSVD_SIZE;
    }
    else
    /* polyspace<RTE: UNR : Not a defect : Justify with annotations > Although it is unreachable code, fail-safety code is necessary. */
    {
      /* @Trace: SafeOs_SUD_API_36902 */
      LusStackSize = (uint16)OS_ZERO;
    }
  }
  else
  /* polyspace<RTE: UNR : Not a defect : Justify with annotations > Although it is unreachable code, fail-safety code is necessary. */
  {
    /* polyspace<RTE:OBAI:Not a defect:Justify with annotations> Configured array index */
    /* @Trace: SafeOs_SUD_API_36903 */
    LusStackSize = (Os_GaaStack[LpStaticTask->ucStackIndex].usStackSize);
  }

  return (LusStackSize);
} /* End of Os_GetStackPointer(P2CONST( */
#endif /* End of if (OS_STACK_MONITORING == STD_ON) */

/***************************************************************************//**
 * Function Name        : OS_REMOVECONTEXT
 *
 * Service ID           : NA
 *
 * Description          : This service is used to removing used context
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LpStaticTask : Pointer of Task/ISR info
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_003
 ******************************************************************************/
#if ((OS_PROTECTION_HOOK == STD_ON) || (OS_APPLICATION == STD_ON))
FUNC(void, OS_CODE) OS_REMOVECONTEXT(P2CONST(
                           Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  OS_GET_CORE_ID(OS_CORE_ID);

  if ((LpStaticTask->usType == OS_ISR2)
  /* polyspace +2 RTE:OBAI [Justified:low] Configured array index */
  #if ((OS_APPLICATION == STD_ON) && ((OS_SCALABILITY_CLASS == OS_SC3) || (OS_SCALABILITY_CLASS == OS_SC4)))
      && (Os_GaaStaticApplication[LpStaticTask->ddAppId].ucType == OS_TRUSTED)
  #endif
    )
    {
      /* @Trace: SafeOs_SUD_API_37101 */
      /* Increment the KillCAT2ISR count as we want to kill this CAT2 ISR */
      Os_GucKillCAT2ISR[OS_CORE_ID] ++;
  }
  /* @Trace: SafeOs_SUD_API_37102 */
}
#endif

/***************************************************************************//**
 * Function Name        : OS_STARTUPCONTEXT
 *
 * Service ID           : NA
 *
 * Description          : This service is used to load the context only of the first Task
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]          : void
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_003
 ******************************************************************************/
FUNC(void, OS_CODE) OS_STARTUPCONTEXT(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  OS_GET_CORE_ID(OS_CORE_ID);
  /* @Trace: SafeOs_SUD_API_50101 */
  Os_GucSchedReq[OS_CORE_ID] = CONTEXT_SWITCHING_STARTUP;
}

/***************************************************************************//**
 * Function Name        : OS_LOADCONTEXT
 *
 * Service ID           : NA
 *
 * Description          : This service is used to load the context
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]          : void
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_003
 ******************************************************************************/
FUNC(void, OS_CODE) OS_LOADCONTEXT(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  OS_GET_CORE_ID(OS_CORE_ID);
  /* @Trace: SafeOs_SUD_API_50201 */
  Os_GucSchedReq[OS_CORE_ID] = CONTEXT_SWITCHING_LOAD;
}

/***************************************************************************//**
 * Function Name        : OS_SAVECONTEXT
 *
 * Service ID           : NA
 *
 * Description          : This service is used to save the context
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]          : void
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_003
 ******************************************************************************/
FUNC(void, OS_CODE) OS_SAVECONTEXT(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  OS_GET_CORE_ID(OS_CORE_ID);
  /* @Trace: SafeOs_SUD_API_50301 */
  Os_GucSchedReq[OS_CORE_ID] = CONTEXT_SWITCHING_SAVE;
}

/***************************************************************************//**
 * Function Name        : OS_RELOADCONTEXT
 *
 * Service ID           : NA
 *
 * Description          : This service is used to reload the context
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]          : void
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_006}
 *
 * @ingroup               OS_S32K31X_ESDD_003
 ******************************************************************************/
FUNC(void, OS_CODE) OS_RELOADCONTEXT(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  OS_GET_CORE_ID(OS_CORE_ID);
  /* @Trace: SafeOs_SUD_API_30601 */
  Os_GucSchedReq[OS_CORE_ID] = CONTEXT_SWITCHING_RELOAD;
}

/*******************************************************************************
** Function Name        : Os_NontrustedAppHook                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called to process the specific     **
**                        Hooks of Os application which are not a TRUSTED one **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LddAppId,                                           **
**                        pAppHook, Error                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Os_GulOsAppSP,                **
**                        Os_GpLinkTask, Os_GaaStaticTask,                    **
**                        Os_GusCallevelCheck                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        None                                                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.7 [Not a defect:Low] "The parameter is check/will used depending on user's configuration" */
/* polyspace:begin<RTE:NIP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
#if (OS_MEMORY_PROTECTION == STD_ON) && ((OS_APP_ERROR_HOOK == STD_ON) || (OS_APP_SHUTDOWN_HOOK == STD_ON))
FUNC(void, OS_CODE) Os_NontrustedAppHook(ApplicationType LddAppId,
            P2FUNC(void, OS_VAR, pAppHook)(StatusType Error), StatusType Error)
{
  #if (OS_STARTUP_HOOK == STD_ON)
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpCurrentTask;
  VAR(Tdd_Os_ContextSwitch, OS_VAR) LddContext;
  VAR(Tdd_Os_StaticTask, OS_VAR) LddDummyTask;
  LddDummyTask.usType = OS_TASK_INVALID;
  
  static uint32 LulCurrentSP;
  static uint32 LulCurrentPSP;
  static ApplicationType LulCurrentAppID;
  #endif
  uint32 LulCtrl;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get the core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Check if the current Call Level is containing OS_CONTEXT_ERRORHOOK or  OS_CONTEXT_SHUTDOWNHOOK*/
  #if (OS_STARTUP_HOOK == STD_ON)
  /* Get application ID will run shutdown hook */
  /* Get current applicaiton ID to check the application shutdown hook call from trusted or non-trusted application */
  LulCurrentAppID = GetCurrentApplicationID();
  /* polyspace-begin DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "The index of array is checked before used" */
  /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "The index of array is checked before used" */
  if (((Os_GusCallevelCheck[OS_CORE_ID] & OS_CONTEXT_ERRORHOOK) != (uint16)OS_ZERO) ||
      ((Os_GusCallevelCheck[OS_CORE_ID] & OS_CONTEXT_SHUTDOWNHOOK) != (uint16)OS_ZERO))
  {
    /* @Trace: SafeOs_SUD_API_54201 */
    /* polyspace:begin<CERT-C:INT36-C:Not a defect: justify with annotation> This conversion is need */
    /* polyspace +2 MISRA-C3:11.4 [Justified:Low] "This is intended to handle stack address" */
    /* Take global OsApp stack address into a local context structure */
    LddContext.pPowerOnSP = (Os_StackType*)Os_GulOsAppSP[LddAppId];
    /* polyspace:end<CERT-C:INT36-C:Not a defect: justify with annotation> This conversion is need */
    /* Take startup information into a dummy task,
     * comprising of:
     * Task ID (ddTaskId) - for use of OsApp Stack for AppStartupHook
     * Context area (pContext) - no running tasks/ISRs so far,
     *                           take full OsApp stack area */
    LddDummyTask.ddTaskId = INVALID_TASK;
    LddDummyTask.pContext = &LddContext;
    LddDummyTask.ucStackIndex = Os_GaaStaticApplication[LddAppId].ucStackIndex;
    /* Take the current ddAppId into the dummy task */
    LddDummyTask.ddAppId = LddAppId;
    #if (OS_TRUSTED_START_INDX != OS_ZERO)
    if ((Os_GusCallevelCheck[OS_CORE_ID] & OS_CONTEXT_SHUTDOWNHOOK) != (uint16)OS_ZERO)
    {
      /* Handle configured additional memory blocks and stacks during
      * only the application startup hooks */
     /* @Trace: SafeOs_SUD_API_54202 */
     Os_HandleMemoryBlock(&LddDummyTask);
    }
    #endif
    /* No tasks/ISRs during OsApp Startup, LpCurrentTask is LddDummyTask */
    LpCurrentTask = &LddDummyTask;

    /* Update the currently running OsApplication ID */
    Os_GddAppId[OS_CORE_ID] = LpCurrentTask->ddAppId;
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_54203 */
    /* LpCurrentTask is a running task */
    /* polyspace +1 RTE:NIV [Justified:Medium] "Variable initialized at other location" */
    LpCurrentTask = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];
  } 
  #endif

  /* Check if the Os Application is non-trusted */
  LulCtrl = __MRS(__CONTROL);
  #if(OS_TRUSTED_START_INDX != OS_ZERO)
  if (LddAppId < Os_Trusted_Start_Indx)
  {
    /* @Trace: SafeOs_SUD_API_54204 */
    /* CTRL.nPRIV = 1 which means Thread mode has unprivileged access */
    LulCtrl |= 0x00000001u;
  }
  else /* Otherwise, the Os Application is non-trusted-with-protection */
  #endif
  {
    /* @Trace: SafeOs_SUD_API_54205 */
    /* CTRL.nPRIV = 0 which means Thread mode has privileged access */
    LulCtrl &= 0xFFFFFFFEu;
  }
  __MSR(__CONTROL, LulCtrl); 
  /* End of if (LddAppId < Os_Trusted_App_With_Protection_Start_Indx) */
  
  #if (OS_STARTUP_HOOK == STD_ON)
  if (((Os_GusCallevelCheck[OS_CORE_ID] & OS_CONTEXT_ERRORHOOK) != (uint16)OS_ZERO) ||
      (((Os_GusCallevelCheck[OS_CORE_ID] & OS_CONTEXT_SHUTDOWNHOOK) != (uint16)OS_ZERO) && (LulCurrentAppID == LddAppId)))
  {
    /* @Trace: SafeOs_SUD_API_54206 */
    /* Save previous stack pointer(PSP) */
    LulCurrentSP = (uint32)Os_GetPSP();
  }
  else if (((Os_GusCallevelCheck[OS_CORE_ID] & OS_CONTEXT_SHUTDOWNHOOK) != (uint16)OS_ZERO) &&
           (LulCurrentAppID != LddAppId))
  {
    /* @Trace: SafeOs_SUD_API_54207 */
    LulCurrentSP = (uint32)Os_GulOsAppSP[LddAppId];
    LulCurrentPSP = (uint32)Os_GetPSP();
  }
  else {
    /* @Trace: SafeOs_SUD_API_54208 */
    /* nothing */
  }
  /* Create current context */
  LpCurrentTask->pContext->ulR0 = Error;
  LpCurrentTask->pContext->ulSP = (uint32)LulCurrentSP;
  LpCurrentTask->pContext->ulEXC_RETURN = OS_EXC_RETURN_THREAD_MODE;
  LpCurrentTask->pContext->ulPSR = OS_TASK_INIT_PSR;
  LpCurrentTask->pContext->ulLR = (uint32)Os_NonTrustedAppHookTerminate;
  LpCurrentTask->pContext->ulPC = (uint32)pAppHook;
  /*polyspace:begin<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by OS (not our OS), and pointer conversion is required  */
  LpCurrentTask->pContext->pPowerOnSP = (Os_StackType*)LulCurrentSP;
  /*polyspace:end<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by OS (not our OS), and pointer conversion is required  */

  /* Save previous stack pointer(MSP) */
  Os_GulSaveSp[OS_CORE_ID] = (uint32)Os_GetMSP();
  
  /* Load context error-up hook routine */
  /* @Trace: SafeOs_SUD_API_54209 */
  Os_SwitchCurrentContext(LpCurrentTask->pContext);
  if (((Os_GusCallevelCheck[OS_CORE_ID] & OS_CONTEXT_ERRORHOOK) != (uint16)OS_ZERO) ||
      (((Os_GusCallevelCheck[OS_CORE_ID] & OS_CONTEXT_SHUTDOWNHOOK) != (uint16)OS_ZERO) && (LulCurrentAppID == LddAppId)))
  {
    /* @Trace: SafeOs_SUD_API_54210 */
    /* Restore previous stack pointer(PSP) */
    Os_SetPSP(LulCurrentSP);
  }
  else if (((Os_GusCallevelCheck[OS_CORE_ID] & OS_CONTEXT_SHUTDOWNHOOK) != (uint16)OS_ZERO) &&
            (LulCurrentAppID != LddAppId)) 
  {
    /* @Trace: SafeOs_SUD_API_54211 */
    /* Restore previous stack pointer(PSP) */
    Os_SetPSP(LulCurrentPSP);
  }
  else {
    /* @Trace: SafeOs_SUD_API_54212 */
    /* do nothing */
  }
  #else
  OS_UNUSED(Error);
  OS_UNUSED(LddAppId);
  OS_UNUSED_PTR(pAppHook);
  #endif

  OS_CLEAR_KERNEL_FLAG();
  /* Exit kernel mode */
  return;
  /* polyspace-end DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "The index of array is checked before used" */
  /* polyspace-end MISRA-C3:D4.14 [Not a defect:Low] "The index of array is checked before used" */
} /* End of Os_NontrustedAppHook(ApplicationType LddAppId,
        P2FUNC(void, OS_VAR, pAppHook)(StatusType Error), StatusType Error) */
/* polyspace-end MISRA-C3:2.7 [Not a defect:Low] "The parameter is check/will used depending on user's configuration" */
/* polyspace:end<RTE:NIP:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
#endif /* End of if (OS_MEMORY_PROTECTION == STD_ON) &&((OS_APP_ERROR_HOOK == STD_ON) || (OS_APP_SHUTDOWN_HOOK == STD_ON)) */

/*******************************************************************************
** Function Name        : Os_NontrustedAppStartupHook                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called to process the specific     **
**                        Startup Hooks of Os application which are not a     **
**                        TRUSTED Os Application                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LddAppId,                                           **
**                        pAppStartupHook                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Os_GulOsAppSP,                **
**                        Os_GpLinkTask, Os_GaaStaticTask,                    **
**                        Os_GusCallevelCheck                                 **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#if (OS_MEMORY_PROTECTION == STD_ON) && (OS_APP_STARTUP_HOOK == STD_ON)
FUNC(void, OS_CODE) Os_NontrustedAppStartupHook(ApplicationType LddAppId, P2FUNC(void, OS_VAR, pAppStartupHook)(void))
{
  #if (OS_STARTUP_HOOK == STD_ON)
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpCurrentTask;
  VAR(Tdd_Os_ContextSwitch, OS_VAR) LddContext;
  VAR(Tdd_Os_StaticTask, OS_VAR) LddDummyTask;
  LddDummyTask.usType = OS_TASK_INVALID;
  uint32 LulCurrentSP;
  #endif
  uint32 LulCtrl;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get the core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* Memblocks and Stacks Handling */
  /* Check if the current Call Level is containing OS_CONTEXT_STARTUPHOOK */
  #if (OS_STARTUP_HOOK == STD_ON)
  if ((Os_GusCallevelCheck[OS_CORE_ID] & OS_CONTEXT_STARTUPHOOK)
                                                            != (uint16)OS_ZERO)
  {
    /* polyspace:begin<CERT-C:INT36-C:Not a defect: justify with annotation> This conversion is need */
    /* @Trace: SafeOs_SUD_API_54301 */
    /* Take global OsApp stack address into a local context structure */
    LddContext.pPowerOnSP = (Os_StackType*)Os_GulOsAppSP[LddAppId];
    /* polyspace:end<CERT-C:INT36-C:Not a defect: justify with annotation> This conversion is need */
    /* Take startup information into a dummy task,
     * comprising of:
     * Task ID (ddTaskId) - for use of OsApp Stack for AppStartupHook
     * Context area (pContext) - no running tasks/ISRs so far,
     *                           take full OsApp stack area */
    /* Init for dummy context */
    LddDummyTask.ddTaskId = INVALID_TASK;
    LddDummyTask.pContext = &LddContext;
    LddDummyTask.ucStackIndex = Os_GaaStaticApplication[LddAppId].ucStackIndex;
    
    /* Take the current ddAppId into the dummy task
     * Os Application ID (ddAppId) - for configured memory blocks */
    LddDummyTask.ddAppId = LddAppId;
    #if (OS_TRUSTED_START_INDX != OS_ZERO)
    /* Handle configured additional memory blocks and stacks during
     * only the application startup hooks */
    /* @Trace: SafeOs_SUD_API_54302 */
    Os_HandleMemoryBlock(&LddDummyTask);
    #endif
    /* No tasks/ISRs during OsApp Startup, LpCurrentTask is LddDummyTask */
    LpCurrentTask = &LddDummyTask;

    /* Update the currently running OsApplication ID */
    Os_GddAppId[OS_CORE_ID] = LpCurrentTask->ddAppId;
  }
  else
  {
    /* LpCurrentTask is a running task */
    /* @Trace: SafeOs_SUD_API_54303 */
    LpCurrentTask = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];
  } /* End of if ((Os_GusCallevelCheck[OS_CORE_ID] & OS_CONTEXT_STARTUPHOOK)
                                                     != (uint16)OS_ZERO)) */
  LulCurrentSP = (uint32)Os_GulOsAppSP[LddAppId];
  #endif
  
  /* Check if the Os Application is non-trusted */
  LulCtrl = __MRS(__CONTROL);
  if (LddAppId < Os_Trusted_Start_Indx)
  {
    /* @Trace: SafeOs_SUD_API_54304 */
    /* CTRL.nPRIV = 1 which means Thread mode has unprivileged access */
    LulCtrl |= 0x00000001u;
  }
  else /* Otherwise, the Os Application is non-trusted-with-protection */
  {
    /* @Trace: SafeOs_SUD_API_54305 */
    /* CTRL.nPRIV = 0 which means Thread mode has privileged access */
    LulCtrl &= 0xFFFFFFFEu;
  }
  /* @Trace: SafeOs_SUD_API_54306 */
  __MSR(__CONTROL, LulCtrl); 
  /* End of if (LddAppId < Os_Trusted_App_With_Protection_Start_Indx) */

  #if (OS_STARTUP_HOOK == STD_ON)
  /* @Trace: SafeOs_SUD_API_54307 */
  /* Create current context */
  LpCurrentTask->pContext->ulSP = (uint32)LulCurrentSP;
  LpCurrentTask->pContext->ulEXC_RETURN = OS_EXC_RETURN_THREAD_MODE;
  LpCurrentTask->pContext->ulPSR = OS_TASK_INIT_PSR;
  LpCurrentTask->pContext->ulLR = (uint32)Os_NonTrustedAppHookTerminate;
  LpCurrentTask->pContext->ulPC = (uint32)pAppStartupHook;
  /*polyspace:begin<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by OS (not our OS), and pointer conversion is required  */
  LpCurrentTask->pContext->pPowerOnSP = (Os_StackType*)LulCurrentSP;
  /*polyspace:end<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by OS (not our OS), and pointer conversion is required  */
  /* Save previous stack pointer(MSP) */
  Os_GulSaveSp[OS_CORE_ID] = (uint32)Os_GetMSP();

  /* Load context start-up hook routine */
  Os_SwitchCurrentContext(LpCurrentTask->pContext);
  #endif
  /* Exit kernel mode */
  return;
} /* End of Os_NontrustedAppStartupHook(ApplicationType LddAppId,
            P2FUNC(void, OS_VAR, pAppStartupHook)(void)) */
#endif /* End (OS_MEMORY_PROTECTION == STD_ON) && (OS_APP_STARTUP_HOOK == STD_ON) */

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:18.1 */
/* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:end<RTE:OBAI:Not a defect:Justify with annotations> Configured array index */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:11.1:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<MISRA-C3:18.4:Not a defect:Justify with annotations> Operators on pointer is used for better performance */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace-end CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
