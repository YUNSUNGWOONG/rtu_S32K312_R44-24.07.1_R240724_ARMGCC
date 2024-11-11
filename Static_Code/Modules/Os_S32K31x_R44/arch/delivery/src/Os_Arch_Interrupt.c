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
**  SRC-MODULE: Os_Arch_Interrupt.c                                           **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of interrupt specific functionality                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: Yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.3.0     31-Jan-2024    HJ.Kim       Jira    CP44-4168                    **
**                          HJ.Kim       Jira    CP44-4169                    **
** 1.1.0      6-Sep-2023    HJ.Kim       Jira    CP44-2549                    **
**            6-Sep-2023    HJ.Kim       Jira    CP44-2549                    ** 
**            1-Sep-2023    HJ.Kim       Jira    CP44-2528                    **
**           29-Aug-2023    HJ.Kim       Jira    CP44-1712                    **
**           27-Jun-2023    HJ.Kim       Jira    CP44-1874                    **
**            8-Jun-2023    HJ.Kim       Jira    CP44-2090                    **
** 1.0.2     31-Dec-2022    TinHV        Jira    CP44-856                     **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:NIP:Not a defect:Justify with annotations> Initialized at other location */
/* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> Variable initialized at other location */
/* polyspace:begin<RTE:SHF:Not a defect:Justify with annotations> Calculated access to outside bounds */
/* polyspace:begin<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:begin<RTE:OBAI:Not a defect:Justify with annotations> configured array index */
/* polyspace:begin<RTE:COR:Not a defect:Justify with annotations> ptr points to a valid value and code is verified manually */
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> Run-time failures are justified */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:11.1:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace-begin MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array" */
/* polyspace:begin<MISRA-C3:18.4:Not a defect:Justify with annotations> Operators on pointer is used for better performance */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<CERT-C:INT36-C:Not a defect:Justify with annotation> This conversion cannot be modified to handle memory */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Arch_Interrupt.h"
#include "Os_Arch_Multicore.h"
#include "Os_Arch_Context.h"
#include "Os_Ram.h"
#include "Os_Error.h"
#include "Os_Interrupt.h"         /* Os Interrupt header file */
/* @Trace: SRS_BSW_00410 */
#if (OS_RES_INT_SHARE == STD_ON)
#include "Os_Resource.h"
#endif
/* @Trace: SRS_BSW_00410 */
#if(OS_STACK_MONITORING == STD_ON)
#include "Os_Stack.h"
#endif
/* @Trace: SRS_BSW_00410 */
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_TimingProtection.h"
#endif
/* @Trace: SRS_BSW_00410 */
#if ((OS_MEMORY_PROTECTION == STD_ON) && (OS_APP_MEMBLK_CNT != OS_ZERO))
#include "Os_Arch_MemPro.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OS_API_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/*******************************************************************************
 * Function             : Os_NonTrustedIsrTerminate
 *
 * Service ID           : NA
 *
 * Description          : This function is called when non-trusted Isr terminated
 *                        with Os_ReturnNTISRKernelStack()
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
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_MEMORY_PROTECTION == STD_ON))
static FUNC(void, OS_CODE) Os_NonTrustedIsrTerminate(void)
{
  /* @Trace: SafeOs_SUD_API_36601 */
  OS_SYSCALL_RETURNNTISRKERNELSTACK();
}
#endif /* (OS_TRUSTED_START_INDX != OS_ZERO) */
#define OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/* @Trace: SRS_AUTRON_00019 */
/*******************************************************************************
 * Function             : Os_LoadTISRContext
 *
 * Service ID           : NA
 *
 * Description          : This function is used to switch context for ISR CAT2
 *                        belong to trusted applications
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]          : LulOldKernelSP, LpNewISR
 *
 * @return              : NA
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulOsAppSP, Os_GulUserSP,
 *                        Os_GulKernelSP
 *
 *                        Function(s) invoked    :
 *                        Os_GetMSP(),
 *                        Os_SetMSP(),
 *                        OS_ENABLEINTERRUPTS(), OS_DISABLEINTERRUPTS(),
 *                        Os_SetMSP()
 *
 * {Ref: SWR_OS_S32K31X_001}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
static FUNC(void, OS_CODE) Os_LoadTISRContext(uint32 LulOldKernelSP, \
                                   P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpNewISR)
{
  volatile uint32 LulISRSP;
  volatile P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpISR = LpNewISR;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  #if (OS_APPLICATION == STD_ON)
  LulISRSP = (uint32)Os_GulOsAppSP[LpISR->ddAppId];
  #else
  LulISRSP = (uint32)Os_GulUserSP[OS_CORE_ID];
  #endif
  
  /* @Trace: SafeOs_SUD_API_33201 */
  /*polyspace<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by OS (not our OS), and pointer conversion is required  */
  LpISR->pContext->pPowerOnSP = (Os_StackType *)LulISRSP;
  LpISR->pContext->ulSP = LulISRSP;

  /* Save OS stack (used by OS) */
  Os_GulKernelSP[OS_CORE_ID] = (uint32)Os_GetMSP();

  /* MSP Setting */
  __asm("isb");
  __asm("dsb");
  Os_SetMSP(LulISRSP);

  OS_ENABLEINTERRUPTS();
  /** 5. Run CAT2 ISR */
  /* @Trace: SafeOs_SUD_API_33202 */
  LpISR->pFuncEntry();
  OS_DISABLEINTERRUPTS();

  /* MSP Setting */
  __asm("isb");
  __asm("dsb");
  Os_SetMSP(Os_GulKernelSP[OS_CORE_ID]);

  Os_GulKernelSP[OS_CORE_ID] = LulOldKernelSP;
}
/*******************************************************************************
 * Function             : Os_LoadNTISRContext
 *
 * Service ID           : NA
 *
 * Description          : This function is used to switch context for ISR CAT2
 *                        belong to non-trusted applications
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]          : LulOldKernelSP, LulCurrentPSP, LpNewISR
 *
 * @return              : NA
 * 
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GulOsAppSP, Os_GulSaveSp_NTISR,
 *                        Os_GulKernelSP
 *
 *                        Function(s) invoked    :
 *                        Os_HandleMemoryBlock(),
 *                        Os_GetMSP(), OS_ENABLEINTERRUPTS(),
 *                        Os_LoadCurrentContext_NTISR(), OS_ENABLECURRENTCAT2ISR(),
 *                        OS_DISABLEINTERRUPTS(), Os_SetPSP(),
 *                        OS_DISABLECURRENTCAT2ISR()
 *
 * {Ref: SWR_OS_S32K31X_001}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
/* Check if Application is non-trusted */
#if ((OS_MEMORY_PROTECTION == STD_ON) && (OS_TRUSTED_START_INDX != OS_ZERO))
/* @Trace: SRS_AUTRON_00019 */
static FUNC(void, OS_CODE) Os_LoadNTISRContext(uint32 LulOldKernelSP, const uint32 LulCurrentPSP, \
                                     P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpNewISR)
{
  uint32 LulISRSP;
  TaskType LulCurrentIsrId;
  uint32 LulTrusted;
  uint32 LulPRIV;
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpISR = LpNewISR;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  
  /* Save current PSP to avoid the optimization */
  #if (OS_APPLICATION == STD_ON)
  /* @Trace: SafeOs_SUD_API_33301 */
  LulISRSP = (uint32)Os_GulOsAppSP[LpISR->ddAppId];
  #endif
  /* Init ISR context */
  /* @Trace: SafeOs_SUD_API_33302 */
  /*polyspace:begin<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by OS (not our OS), and pointer conversion is required  */
  LpISR->pContext->pPowerOnSP = (Os_StackType *)LulISRSP;
  /*polyspace:end<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by OS (not our OS), and pointer conversion is required  */
  LpISR->pContext->ulEXC_RETURN = 0xFFFFFFFDu;
  LpISR->pContext->ulPSR = OS_TASK_INIT_PSR;
  LpISR->pContext->ulLR = (uint32)Os_NonTrustedIsrTerminate;
  LpISR->pContext->ulPC = (uint32)LpISR->pFuncEntry;
  LpISR->pContext->ulSP = LulISRSP;

  #if ((OS_MEMORY_PROTECTION == STD_ON) && (OS_APP_MEMBLK_CNT != OS_ZERO))
  /* Invoke function Os_HandleMemoryBlock */
  /* @Trace: SafeOs_SUD_API_33303 */
  Os_HandleMemoryBlock(LpISR);
  #endif
  /* CTRL.nPRIV = 1 which means Thread mode has unprivileged access */
  LulTrusted = __MRS(__CONTROL);
  LulPRIV = LulTrusted & 0x00000001u;
  LulTrusted |= 0x00000001u;
  __MSR(__CONTROL, LulTrusted);

  /* Get current ISR Id */
  LulCurrentIsrId = LpISR->ddTaskId;

  /* Save OS stack (used by OS) */
  Os_GulSaveSp_NTISR[OS_CORE_ID] = (uint32)Os_GetMSP();

  OS_ENABLEINTERRUPTS();
  /** 5. Run CAT2 ISR */
  /* @Trace: SafeOs_SUD_API_33304 */
  /* Disable current ISR temporarily to switch context of ISR in unprivileged mode with PSP */
  OS_DISABLECURRENTCAT2ISR(LulCurrentIsrId);
  /* Load currrent context ISR */
  Os_LoadCurrentContext_NTISR(LpISR->pContext);
  /* Enbale current ISR */
  OS_ENABLECURRENTCAT2ISR(LulCurrentIsrId);

  OS_DISABLEINTERRUPTS();

  Os_SetPSP(LulCurrentPSP);
  Os_GulKernelSP[OS_CORE_ID] = LulOldKernelSP;
  /* Reutern privileged mode */
  /* CTRL.nPRIV = 0 which means Thread mode has privileged access */
  LulTrusted = __MRS(__CONTROL);
  LulTrusted = LulTrusted & 0xFFFFFFFEu;
  LulTrusted |= LulPRIV & 0x00000001u;
  __MSR(__CONTROL, LulTrusted);
}
#endif /*(OS_MEMORY_PROTECTION == STD_ON)*/

/***************************************************************************//**
 * Function             : Os_CAT2ISRHandler
 *
 * Service ID           : NA
 *
 * Description          : This function is used to handle Category2 interrupt
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]          : LulIsrIdx, LulNestOnEntry
 *
 * @return              : 1 - context-switch is necessary,
 *                        0 - context-switch is not necessary
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticTask, Os_GpStaticTask,
 *                        Os_GpLinkTask, Os_GucNestingCAT2ISR,
 *                        Os_GusCallevelCheck, Os_GddISR2Lock, Os_GddISRLock,
 *                        Os_GblISRLock
 *
 *                        Function(s) invoked    :
 *                        ISR_OsIsrxx (CAT2 interrupt service routine)
 *                        Os_CheckStack(), Os_ReleaseResourceService(),
 *                        Os_LogTraceInfo(), Os_ITEntryForCPULoad(),
 *                        Os_ITExitForCPULoad()
 *
 * {Ref: SWR_OS_S32K31X_001}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11014 SRS_BSW_00439 SRS_AUTRON_00017 SRS_AUTRON_00020 */
/* polyspace +3 CODE-METRIC:FXLN [Justified:Low] "The display of specific values of the number of Executable Lines is justified" */
/* polyspace +2 CODE-METRICS:PATH [Justified:Low] "The display of specific values of the number of paths is justified" */
/* polyspace +1 CODE-METRICS:CALLS [Justified:Low] "The display of specific values of the number of Called Function is justified"*/
FUNC(uint8, OS_CODE) Os_CAT2ISRHandler(uint32 LulIsrIdx, uint32 LulNestOnEntry)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpNewISR;
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpNewTaskISR;
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpPrevTaskISR;
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpNewList;

  uint32 LulOldKernelSP;
  uint8 LucIsrReturn = OS_ZERO;
  uint16 LusCallevelCat2Isr = (uint16)OS_CONTEXT_CAT2ISR;
  #if (OS_MULTICORE == STD_ON)
  /* @Trace: SafeOs_SUD_API_48001 */
  CoreIDType OS_CORE_ID;
  #endif
  #if (OS_RES_INT_SHARE == STD_ON)
  Os_OldLevel_T defaultPriority;
  #endif
  /* NTISR HW Counter Handling*/
  #if (((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_MEMORY_PROTECTION == STD_ON)) \
        && (OS_ISR_COUNT != OS_PRE_ZERO))
  uint32 LulCounterIsrId;
  #endif

  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  
  /** 1. Save Preempted Task */
  LpPrevTaskISR = Os_GpStaticTask[OS_CORE_ID];

  #if (OS_STACK_MONITORING == STD_ON)
  /* Call function to check if stack has overflowed */
  if(LulNestOnEntry == OS_ZERO)
  {
    /* @Trace: SafeOs_SUD_API_48003 */
    Os_CheckStack(LpPrevTaskISR);
  }
  #endif

  LpNewISR = &Os_GaaStaticTask[LulIsrIdx];

  #if (OS_ISR_TP_TF == STD_ON)
  if((LpNewISR->pStaticTimProtection != NULL_PTR) &&
     (LpNewISR->pStaticTimProtection->ddTimeFrame != OS_ZERO))
  {
    /* @Trace: SafeOs_SUD_API_48004 */
    /* Start Time frame*/
    Os_StartTimeFrame(LpNewISR);
  }
  #endif

  #if ((OS_ISR_TP_EB == STD_ON) || (OS_TASK_TP_EB == STD_ON))
  /* Call a function to Pause Execution budget */
  Os_PauseTimingProtection();

  /* Start execution budget monitoring*/
  if (LpNewISR->pStaticTimProtection != NULL_PTR)
  {
    TickType LddRequestedTime;

    LddRequestedTime = LpNewISR->pStaticTimProtection->ddExecutionBudget;
    if (LddRequestedTime != OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_48005 */
      Os_StartMonitor(LddRequestedTime, OS_EXEC_BUDGET,
          LpNewISR->pStaticTimProtection->ucTaskExeBudgetIndex);
    }
  } /* End (LpCurrentTask->pStaticTimProtection != NULL_PTR) */
  #endif

  /** 2. Insert new ISR into Ready Queue */
  LpNewList = LpNewISR->pLinkTask;
  LpNewList->pLinkList = Os_GpLinkTask[OS_CORE_ID];
  Os_GpLinkTask[OS_CORE_ID] = LpNewList;

  /** 3. Update Os_GpStaticTask and it's state */
  Os_GpStaticTask[OS_CORE_ID] = LpNewISR;
  Os_GpStaticTask[OS_CORE_ID]->pTask->ddState = RUNNING;

  /* Update the currently running Application */
  #if(OS_APPLICATION == STD_ON)
  /* @Trace: SafeOs_SUD_API_48006 */
  Os_GddAppId[OS_CORE_ID] = LpNewISR->ddAppId;
  #endif

  /* Increment the cat2 nesting count */
  Os_GucNestingCAT2ISR[OS_CORE_ID]++;
  if(Os_GucNestingCAT2ISR[OS_CORE_ID] == OS_ONE)
  {
    /* @Trace: SafeOs_SUD_API_48007 */
    Os_GusCallevelCheck[OS_CORE_ID] |= LusCallevelCat2Isr;
  }

  #if (OS_PROFILING_HOOK == STD_ON)
  /* @Trace: SafeOs_SUD_API_48008 */
  Os_GucInKernel[OS_CORE_ID]++;
  Os_IsrEntryHook(OS_CORE_ID, LpNewISR->ddTaskId);
  Os_GucInKernel[OS_CORE_ID]--;
  #endif

  /** 4. Change to user stack */
  LulOldKernelSP = Os_GulKernelSP[OS_CORE_ID];

  if ((LpPrevTaskISR->usType == OS_TASK_BASIC) ||
      (LpPrevTaskISR->usType == OS_ISR2))
  {
    /* polyspace-begin MISRA-C3:11.6 [Justified:Medium] "To save address data" */
    #if (OS_APPLICATION == STD_ON)
    if (LpPrevTaskISR->ddTaskId != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_48010 */
      Os_GulOsAppSP[LpPrevTaskISR->ddAppId] = (uint32)Os_GetStackPointer(LpPrevTaskISR) - OS_CONTEXT_SIZE;
    }
    else
    #endif
    {
      /* @Trace: SafeOs_SUD_API_48011 */  
      Os_GulUserSP[OS_CORE_ID] = (uint32)Os_GetStackPointer(LpPrevTaskISR) - OS_CONTEXT_SIZE;
    }
    /* polyspace-end MISRA-C3:11.6 */
  }

  /* Check if Application is non-trusted */
  #if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_MEMORY_PROTECTION == STD_ON))
  #if (OS_ISR_COUNT != OS_PRE_ZERO)
  #if (OS_MULTICORE == STD_ON)
  LulCounterIsrId = OS_COUNTER_ISRID[OS_CORE_ID];
  #else
  LulCounterIsrId = OS_COUNTER_ISRID;
  #endif
  #endif
  if((LpNewISR->ddAppId < (ApplicationType)Os_Trusted_Start_Indx)
  #if (OS_ISR_COUNT != OS_PRE_ZERO)
      && (LpNewISR->ddTaskId != LulCounterIsrId)
  #endif
    )
  {
    /* @Trace: SafeOs_SUD_API_48015 */
    uint32 LulCurrentPSP;
    LulCurrentPSP = (uint32)Os_GetPSP();
    /* Run Isr context belong to non-trusted applicaiton thread mode has unprivileged access */
    Os_LoadNTISRContext(LulOldKernelSP, LulCurrentPSP, LpNewISR);
  }
  else
  #endif
  {
    /* @Trace: SafeOs_SUD_API_48016 */
    /* Run Isr context belong to non-trusted applicaiton thread mode has privileged access */
    Os_LoadTISRContext(LulOldKernelSP, LpNewISR);
  }

  #if (OS_PROFILING_HOOK == STD_ON)
  /* @Trace: SafeOs_SUD_API_48017 */
  Os_GucInKernel[OS_CORE_ID]++;
  Os_IsrExitHook(OS_CORE_ID, LpNewISR->ddTaskId);
  Os_GucInKernel[OS_CORE_ID]--;
  #endif

  /* Decrement the cat2 nesting count */
  Os_GucNestingCAT2ISR[OS_CORE_ID]--;
  if(Os_GucNestingCAT2ISR[OS_CORE_ID] == OS_ZERO)
  {
    /* @Trace: SafeOs_SUD_API_48018 */
    LusCallevelCat2Isr = ~LusCallevelCat2Isr;
    Os_GusCallevelCheck[OS_CORE_ID] &= LusCallevelCat2Isr;
  }

  #if (OS_STACK_MONITORING == STD_ON)
  /* @Trace: SafeOs_SUD_API_48019 */
  /* Call function to check if stack has overflowed */
  Os_CheckStack(LpNewISR);
  #endif

  #if (OS_ISR_TP_EB == STD_ON)
  /* @Trace: SafeOs_SUD_API_48020 */
  if ((LpNewISR->pStaticTimProtection != NULL_PTR) &&
      (LpNewISR->pStaticTimProtection->ddExecutionBudget != OS_ZERO))
  {
    Os_StopExecutionBudget(LpNewISR);
  }
  #endif

  /* Check if interrupts are disabled */
  #if (OS_ISR_COUNT != OS_ZERO)
  #if (OS_CAT2_ISR_COUNT != OS_ZERO)
  if (Os_GddISR2Lock[OS_CORE_ID] != OS_ZERO)
  {
    /* @Trace: SafeOs_SUD_API_48021 */
    Os_GddISR2Lock[OS_CORE_ID] = OS_ONE;
    /* restore the previous state */
    ResumeOSInterrupts();

    #if (OS_ERROR_HOOK == STD_ON)
    /* @Trace: SafeOs_SUD_API_48022 */
    OS_PROCESS_ERROR(E_OS_DISABLEDINT);
    #endif
  }
  #endif
  if (Os_GddISRLock[OS_CORE_ID] != OS_ZERO)
  {
    if(Os_GblISRLock[OS_CORE_ID] == OS_TRUE){
      /* @Trace: SafeOs_SUD_API_48023 */
      EnableAllInterrupts();
    }
    else
    {
      while(Os_GddISRLock[OS_CORE_ID] != OS_ZERO)
      {
        /* @Trace: SafeOs_SUD_API_48024 */
        ResumeAllInterrupts();
      }
    }
    #if (OS_ERROR_HOOK == STD_ON)
    /* @Trace: SafeOs_SUD_API_48025 */
    OS_PROCESS_ERROR(E_OS_DISABLEDINT);
    #endif
  }
  #endif
  
  #if (OS_RES_INT_SHARE == STD_ON)
  if (LpNewISR->pTask->pResources != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_48026 */
    defaultPriority = (Os_OldLevel_T)OS_INT_MIN_PRIORITY;
    Os_ResumeInterrupts(&defaultPriority);
    /* restore the previous state */
    Os_ReleaseResourceService(LpNewISR);
    #if (OS_ERROR_HOOK == STD_ON)
    /* @Trace: SafeOs_SUD_API_48027 */
    OS_PROCESS_ERROR(E_OS_RESOURCE);
    #endif
  }
  #endif

  LpNewTaskISR = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];

  /** 7. Remove CAT2 ISR from Ready Queue if the ISR is not terminated
   *     by Stack Monitoring */
  if(LpNewISR == LpNewTaskISR)
  {
    /* @Trace: SafeOs_SUD_API_48028 */
    Os_GpStaticTask[OS_CORE_ID]->pTask->ddState = SUSPENDED;
    LpNewList = Os_GpLinkTask[OS_CORE_ID]->pLinkList;
    Os_GpLinkTask[OS_CORE_ID] = LpNewList;

    LpNewTaskISR = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];
  }

  /** 8. If there's higher priority Task, return non-zero */
  /** 9. If there's not higher priority Task, return zero */
  if(LulNestOnEntry == OS_ZERO)
  {
    if((LpNewTaskISR->usType != OS_ISR2) &&
       (LpPrevTaskISR->usType != OS_ISR2) &&
       (LpNewTaskISR != LpPrevTaskISR))
    {
      /* context-switch is necessary */
      #if (OS_MEMORY_PROTECTION == STD_ON)
      /* @Trace: SafeOs_SUD_API_48029 */
      if(LpPrevTaskISR->pTask->ddState != SUSPENDED)
      #endif
      {
        #if (OS_POSTTASK_HOOK == STD_ON)
        /* @Trace: SafeOs_SUD_API_48030 */
        /* Process PostTaskHook */
        OS_PROCESS_POSTTASKHOOK();
        #endif
        LpPrevTaskISR->pTask->ddState = READY;
        #if (OS_PROFILING_HOOK == STD_ON)
        /* @Trace: SafeOs_SUD_API_48031 */
        /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "The function works differently depending on whether OsProfiler is used and whether Multi-Core is used" */
        Os_TaskPreemptionHook(OS_CORE_ID, LpPrevTaskISR->ddTaskId);
        /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "The function works differently depending on whether OsProfiler is used and whether Multi-Core is used" */
        #endif
      }

      LucIsrReturn = OS_ONE;
    }
    else
    {
      /* context-switch is not necessary */
      Os_GpStaticTask[OS_CORE_ID] = LpNewTaskISR;
      /* Restore previous Task or CAT2 ISR's stack base address */
      Os_SetTaskStackPointer();
      /* Update the currently running Application */
      #if(OS_APPLICATION == STD_ON)
      /* @Trace: SafeOs_SUD_API_48032 */
      Os_GddAppId[OS_CORE_ID] = LpNewTaskISR->ddAppId;
      #endif

      #if ((OS_ISR_TP_EB == STD_ON) || (OS_TASK_TP_EB == STD_ON))
      if(LpNewTaskISR->pStaticTimProtection != NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_48033 */
        /* Continue Execution budget */
        Os_ContinueTimingProtection(LpNewTaskISR);
      }
      #endif /* End of if (OS_ISR_TP_EB == STD_ON) */
      /* @Trace: SafeOs_SUD_API_48034 */
    }
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_48035 */
    /* Restore Os_GpStaticTask[OS_CORE_ID] */
    Os_GpStaticTask[OS_CORE_ID] = LpPrevTaskISR;
  }

  return LucIsrReturn;
}

/***************************************************************************
 * Function             : Os_ExitCAT2ISRHandler
 *
 * Service ID           : NA
 *
 * Description          : This function is used to handle Category2 interrupt
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]          : LulIsrIdx, LulNestOnEntry
 *
 * @return              : 1 - context-switch is necessary,
 *                        0 - context-switch is not necessary
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticTask, Os_GpStaticTask,
 *                        Os_GpLinkTask, Os_GucNestingCAT2ISR,
 *                        Os_GusCallevelCheck, Os_GddISR2Lock, Os_GddISRLock,
 *                        Os_GblISRLock
 *
 *                        Function(s) invoked    :
 *                        ISR_OsIsrxx (CAT2 interrupt service routine)
 *                        Os_CheckStack(), Os_ReleaseResourceService(),
 *                        Os_LogTraceInfo(), Os_ITEntryForCPULoad(),
 *                        Os_ITExitForCPULoad()
 *
 * {Ref: SWR_OS_CYTXXX_001}
 *
 * @ingroup               OS_CYTXXX_ESDD_002
 ******************************************************************************/
FUNC(void, OS_CODE) Os_ExitCAT2ISRHandler(void)
{
  #if (OS_ISR_COUNT != OS_PRE_ZERO)
  #if ((OS_TIMING_PROTECTION == STD_ON) || (OS_MEMORY_PROTECTION == STD_ON))

  volatile P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpNewTaskISR;
  #if(OS_ISR_COUNT > OS_ZERO)
  Os_OldLevel_T LddDefaultLevel = (Os_OldLevel_T) OS_INT_MIN_PRIORITY;
  #endif
  
  #if (OS_APP_MEMBLK_CNT != OS_ZERO)
  uint32 LulCtrl;
  #endif
  /* Do not allow nesting becuase this ISR is killed */
  OS_DISABLEINTERRUPTS();

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  
  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* Check if CAT2ISR is killed */
  if(Os_GucKillCAT2ISR[OS_CORE_ID] > (uint8)OS_ZERO)
  {
    /* @Trace: SafeOs_SUD_API_48002 */
    Os_GucKillCAT2ISR[OS_CORE_ID] --;
    Os_GucInKernel[OS_CORE_ID] = (uint8)OS_ZERO;

    /* Update Link and Static */
    Os_GpLinkTask[OS_CORE_ID] = Os_GpLinkTask[OS_CORE_ID]->pLinkList;
    Os_GpStaticTask[OS_CORE_ID] = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];

    /* Running Task or ISR was killed. Need Context switching */
    LpNewTaskISR = Os_GpStaticTask[OS_CORE_ID];

    #if(OS_ISR_COUNT > OS_ZERO)
    /* Set lowest priority */
    Os_ResumeInterrupts(&LddDefaultLevel);
    #endif

    #if (OS_APP_MEMBLK_CNT != OS_ZERO)
    /* polyspace +2 RTE:NIP [Justified:Medium] "ptr points to a valid value and code is verified manually" */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array"*/
    LulCtrl = __MRS(__CONTROL);
    /* If Application is non-trusted, set privileged mode to user */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array"*/
    if (LpNewTaskISR->ddAppId < (ApplicationType)Os_Trusted_Start_Indx)
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

    /* Return to Next Task/ISR */
    Os_DoContextSwitch(LpNewTaskISR->pContext);
  }
  #endif /* (OS_ISR_COUNT != OS_PRE_ZERO) */
  #endif /* SC2, SC3, SC4 */
}

#if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_TIMING_PROTECTION==STD_ON))
/*****************************************************************************
 * Function             : Os_IntSetEnable
 * Service ID           : NA
 * Description          : Enable System Interrupt (external interrupts)
 * Sync/Async           : Synchronous
 * Re-entrancy          : Non Re-entrant
 * @param [in]          : intrNum - core irq input line number
 * @return              : void
 * @pre                 : None
 * @remarks             : Global Variable(s)     :
 *                        None
 *                        Function(s) invoked    :
 *                        None
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
/* @Trace: SRS_Os_11011 */
/* polyspace +2 MISRA-C3:8.7 [Not a defect:Low] "External visible function" */
FUNC(void, OS_CODE) Os_IntSetEnable(uint32 intrNum)
{
  uint32 irqNum;
  uint32 irqEnSetAddr;

  irqNum = intrNum % OS_NUM_OF_BIT_UINT32;
  irqEnSetAddr = ((intrNum / OS_NUM_OF_BIT_UINT32) * sizeof(uint32));
  irqEnSetAddr += OS_ARM_M_IRQ_EN_SET_START ;
  /* polyspace:begin<CERT-C:INT36-C:Not a defect:Justify with annotations>This conversion cannot be modified to handle memory */
  *((volatile uint32 *) (irqEnSetAddr)) = ((uint32) 1 << irqNum); /* Write 0 has no effect */
  /* polyspace:end<CERT-C:INT36-C:Not a defect:Justify with annotations>This conversion cannot be modified to handle memory */
}

/*****************************************************************************
 * Function             : Os_IntSetDisable
 * Service ID           : NA
 * Description          : Disable System Interrupt (external interrupts)
 * Sync/Async           : Synchronous
 * Re-entrancy          : Non Re-entrant
 * @param [in]          : intrNum - core irq input line number
 * @return              : void
 * @pre                 : None
 * @remarks             : Global Variable(s)     :
 *                        None
 *                        Function(s) invoked    :
 *                        None
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
 /* @Trace: SRS_Os_11011 */
FUNC(void, OS_CODE) Os_IntSetDisable(uint32 intrNum)
{
  uint32 irqNum;
  uint32 irqEnSetAddr;
  
  irqNum = intrNum % OS_NUM_OF_BIT_UINT32;
  irqEnSetAddr = ((intrNum / OS_NUM_OF_BIT_UINT32) * sizeof(uint32));
  irqEnSetAddr += OS_ARM_M_IRQ_EN_CLR_START ;
  /* polyspace:begin<CERT-C:INT36-C:Not a defect:Justify with annotations>This conversion cannot be modified to handle memory */
  *((volatile uint32 *) (irqEnSetAddr)) = ((uint32) 1 << irqNum); /* Write 0 has no effect */
  /* polyspace:end<CERT-C:INT36-C:Not a defect:Justify with annotations>This conversion cannot be modified to handle memory */
}

/*****************************************************************************
 * Function             : Os_IntClearPend
 * Service ID           : NA
 * Description          : Clear System Interrupt pending state(external interrupts)
 * Sync/Async           : Synchronous
 * Re-entrancy          : Non Re-entrant
 * @param [in]          : intrNum - core irq input line number
 * @return              : void
 * @pre                 : None
 * @remarks             : Global Variable(s)     :
 *                        None
 *                        Function(s) invoked    :
 *                        None
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
FUNC(void, OS_CODE) Os_IntClearPend(uint32 intrNum)
{
  uint32 irqNum;
  uint32 irqEnSetAddr;
  
  irqNum = intrNum % OS_NUM_OF_BIT_UINT32;
  irqEnSetAddr = ((intrNum / OS_NUM_OF_BIT_UINT32) * sizeof(uint32));
  irqEnSetAddr += OS_ARM_M_IRQ_CLEAR_PENDING_START ;
  /* polyspace:begin<CERT-C:INT36-C:Not a defect:Justify with annotations>This conversion cannot be modified to handle memory */
  *((volatile uint32 *) (irqEnSetAddr)) = ((uint32) 1 << irqNum); /* Write 0 has no effect */
  /* polyspace:end<CERT-C:INT36-C:Not a defect:Justify with annotations>This conversion cannot be modified to handle memory */
}
#endif

#if (OS_ISR_COUNT != OS_PRE_ZERO)
/***************************************************************************//**
 * Function             : Os_SetISRPriority
 *
 * Service ID           : NA
 *
 * Description          : This function is called to initialize interrupt
 *                        requests and set the priorities of interrupts
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaISRIndex, Os_GaaISRPriority
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_002}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
FUNC(void, OS_CODE) Os_SetISRPriority(void)
{

  P2CONST(Tdd_Os_ISRPriority, AUTOMATIC, OS_CONST) LpISRPriority;
  P2CONST(Tdd_Os_ISRIndex, AUTOMATIC, OS_CONST) LpISRIndex;
  uint8 LucIsrCount;
  uint32 LulIsrNumber;
  uint32 LulIsrNumber_Sub;
  uint8 LucIdxICER;
  volatile uint32 *LpIrqClrSetAddr;
  /* Address of the priority register for OS HW Counter(SysTick) */
  /* polyspace +2 MISRA-C3:20.7 [Justified:Low] "AUTOSAR compiler abstraction" */
  CONSTP2VAR(volatile uint8, REGSPACE, OS_CONST) OS_HW_COUNTER_PRI_ADDR = OS_SHPR3_PRI_15_ADDR;

  LpISRIndex = &Os_GaaISRIndex[Os_MyCore()];
  LucIsrCount = LpISRIndex->ucIsrCount;
  LpISRPriority = &Os_GaaISRPriority[LpISRIndex->ucIsrStartIdx];

  /* Disable all IRQ (NVIC_ICER0[31:0] ~ NVIC_ICER14[31:0], NVIC_ICER14[15:0]) */
  LucIdxICER = OS_ZERO;
  LpIrqClrSetAddr = (volatile uint32 *)OS_ARM_M_IRQ_EN_CLR_START;

  while (LucIdxICER < OS_INT_MIN_PRIORITY)
  {
      /* @Trace: SafeOs_SUD_API_33701 */
      *LpIrqClrSetAddr = 0xFFFFFFFFu;
      LpIrqClrSetAddr++;
      LucIdxICER++;
  }
  *LpIrqClrSetAddr = 0x0000FFFFu;

  /**
   * Configure Priority in INTC_IPR.
   */
  while (LucIsrCount != OS_ZERO)
  {
    /* polyspace:begin<DEFECT:PTR_CAST:Not a defect:Justify with annotations> type casting has no effects */
    if (LpISRPriority->pICRAddress == OS_HW_COUNTER_PRI_ADDR)
    {
      /* Set SysTick exception priority */
      /* @Trace: SafeOs_SUD_API_33704 */
      *(LpISRPriority->pICRAddress) = (LpISRPriority->usISRPriorityMask)<<4;
    }
    else
    {
      /* @Trace: SafeOs_SUD_API_33705 */
      *(LpISRPriority->pICRAddress) = (LpISRPriority->usISRPriorityMask)<<4;
      LulIsrNumber_Sub = (uint32)LpISRPriority->pICRAddress;
      LulIsrNumber = (uint32)(LulIsrNumber_Sub - (OS_ARM_M_IRQ_IPR_START * sizeof(uint8)));
      Os_IntSetEnable(LulIsrNumber);
    }
    /* polyspace:end<DEFECT:PTR_CAST> */
    /* MISRA Rule   : 17.4
     *   Message      : Increment or decrement operation performed on pointer.
     *   Reason       : Increment operator used to achieve better throughput.
     *   Verification : However, part of the code is verified manually
     *                  and it is not having any impact.
     */
    LpISRPriority++;
    LucIsrCount--;
  }

  /**
   * 4. Set the enable bits or clear the mask bits for the peripheral interrupt
   * requests.
   *   - It will be executed on each peripheral initialization routine
   * 5. Lower PRI in INTC_CPRn to zero.
   *   - It will be executed at Task start procedure
   * 6. Enable processor(s) recognition of interrupts.
   *   - It will be executed at Task start procedure
  */
}
#endif

/***************************************************************************//**
 * Function             : Os_RaisePriority
 *
 * Service ID           : NA
 *
 * Description          : This function is called to raise priority.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LpResource Pointer of Resource structure
 * @param [in]            LulHwPrio  Hardware Priority that to be raised
 *
 * @return              : New Priority
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_002}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
#if (OS_RES_INT_SHARE == STD_ON)
FUNC(uint32, OS_CODE) Os_RaisePriority
    (P2VAR(Tdd_Os_Resource, AUTOMATIC, OS_VAR) LpResource, uint32 LulHwPrio)
{
  uint32 LulCurPrio;
  uint32 LulNewPrio;

  LulCurPrio = Os_SetInterruptPriority(OS_INT_MAX_PRIORITY << OS_IPR_LSB);
  LulCurPrio >>= OS_IPR_LSB;

  LulNewPrio = LulCurPrio;
  LpResource->ulOwnerPrevHwPrio = LulCurPrio;
  if ((LulCurPrio == 0U) || (LulHwPrio < LulCurPrio))
  {
    /* @Trace: SafeOs_SUD_API_33801 */
    LulNewPrio = LulHwPrio;
    /* Set new priority */
    (void)Os_SetInterruptPriority(LulHwPrio << OS_IPR_LSB);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_33802 */
    /* Restore original priority */
    (void)Os_SetInterruptPriority(LulCurPrio << OS_IPR_LSB);
  }
  __asm("isb");

  return LulNewPrio;
}
#endif

/*****************************************************************************
 * Function             : Os_OriginalPriority
 *
 * Service ID           : NA
 *
 * Description          : This function is called to enable interrupts
 *                        when Resource is released.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LpResource Pointer of Resource structure
 *
 * @return              : New Priority
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_002}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
/* polyspace +3 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace" */
#if (OS_RES_INT_SHARE == STD_ON)
FUNC(uint32, OS_CODE) Os_OriginalPriority
                          (P2CONST(Tdd_Os_Resource, AUTOMATIC, OS_CONST) LpResource)
{
  uint32 LulCurPrio;
  uint32 LulNewPrio;

  LulCurPrio = Os_SetInterruptPriority(OS_INT_MAX_PRIORITY << OS_IPR_LSB);
  LulCurPrio >>= OS_IPR_LSB;

  LulNewPrio = LulCurPrio;
  if ((LpResource->ulOwnerPrevHwPrio == 0U) || (LulCurPrio < LpResource->ulOwnerPrevHwPrio))
  {
    /* @Trace: SafeOs_SUD_API_33901 */
    LulNewPrio = LpResource->ulOwnerPrevHwPrio;
    /* Set new priority */
    (void)Os_SetInterruptPriority(LulNewPrio << OS_IPR_LSB);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_33902 */
    /* Restore original priority */
    (void)Os_SetInterruptPriority(LulCurPrio << OS_IPR_LSB);
  }
  __asm("isb");


  return LulNewPrio;
}
#endif

/***************************************************************************//**
 * Function             : OS_NOT_IN_CAT1
 *
 * Service ID           : NA
 *
 * Description          : return true, if current context is not CAT1 ISR
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]          : void
 *
 * @return              : True/False
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_002}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
#if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
FUNC(boolean, OS_CODE) OS_NOT_IN_CAT1(void)
{
  boolean Ldd_OsNotInCat1;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  
  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  if (Os_GucNestingCAT1ISR[OS_CORE_ID] == (uint8)OS_ZERO)
  {
    /* @Trace: SafeOs_SUD_API_35301 */
    Ldd_OsNotInCat1 = OS_TRUE;
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_35302 */
    Ldd_OsNotInCat1 = OS_FALSE; 
  }
  #else
  /* @Trace: SafeOs_SUD_API_35303 */
  Ldd_OsNotInCat1 = OS_TRUE; 
  #endif
  
  return Ldd_OsNotInCat1;
}
#endif

/***************************************************************************//**
 * Function             : OS_IN_CAT1
 *
 * Service ID           : NA
 *
 * Description          : return true, if current context is CAT1 ISR 
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]          : void
 *
 * @return              : True/False
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_002}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
FUNC(boolean, OS_CODE) OS_IN_CAT1(void)
{
  boolean Ldd_OsInCat1;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  
  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  if (Os_GucNestingCAT1ISR[OS_CORE_ID] > (uint8)OS_ZERO)
  {
    /* @Trace: SafeOs_SUD_API_35401 */
    Ldd_OsInCat1 = OS_TRUE;
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_35402 */
    Ldd_OsInCat1 = OS_FALSE; 
  }
  #else
  /* @Trace: SafeOs_SUD_API_35403 */
  Ldd_OsInCat1 = OS_FALSE; 
  #endif
  
  return Ldd_OsInCat1;
}

/***************************************************************************//**
 * Function Name        : Os_IntDisableConditional
 *
 * Service ID           : NA
 *
 * Description          : If current priority is less than Os_CAT2_Max_Priority,
 *                        sets the BASEPRI to Os_CAT2_Max_Priority
 *                        (to disable CAT2 ISR) and returns the previous state.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : Previous interrupt state
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_CAT2_Max_Priority
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
FUNC(Os_IntStatus_T, OS_CODE) Os_IntDisableConditional(void)
{
  Os_IntStatus_T intval;

  /* Get old priority level by setting highest priority */
  intval = Os_SetInterruptPriority(OS_INT_MAX_PRIORITY << OS_IPR_LSB);
  if (intval > Os_CAT2_Max_Priority)
  {
    /* @Trace: SafeOs_SUD_API_35101 */
    (void)Os_SetInterruptPriority((Os_IntStatus_T)Os_CAT2_Max_Priority << OS_IPR_LSB);
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_35102 */
    (void)Os_SetInterruptPriority(intval << OS_IPR_LSB);
  }
  __asm("isb");
  /* @Trace: SafeOs_SUD_API_35103 */
  return intval;
}

/***************************************************************************//**
 * Function Name        : Os_CheckISR
 *
 * Service ID           : NA
 *
 * Description          : This service is used to check wether ISR belongs to the Application
 *                        is trusted or non-trusted
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : Previous interrupt state
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticTask
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_002
 ******************************************************************************/
FUNC(boolean, OS_CODE) Os_CheckISR(uint8 LulIsrIdx)
{

  boolean retVal;
  /* Check whether ISR belongs to the Application is non-trusted or trusted */
  #if (OS_TRUSTED_START_INDX != OS_ZERO)
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpNewISR;
  LpNewISR = &Os_GaaStaticTask[LulIsrIdx];
  if (LpNewISR->ddAppId < (ApplicationType)Os_Trusted_Start_Indx)
  {
    retVal =  OS_FALSE;
  }
  else
  #else
  OS_UNUSED(LulIsrIdx);
  #endif
  {
    retVal =  OS_TRUE;
  }
  return retVal;
}

/*******************************************************************************
** Function Name        : Os_EnableInterruptSource                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called to enable interrupts Source **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ISRID                                               **
**                      : ClearPending                                        **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOs() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaISRPriority, Os_ISR_Count                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_11011 */
#if(OS_CAT2_ISR_COUNT != OS_ZERO)
FUNC(StatusType, OS_CODE) Os_EnableInterruptSource(ISRType ISRID,
                                                        boolean ClearPending)
{
  P2CONST(Tdd_Os_ISRPriority, AUTOMATIC, OS_CONST) LpISRPriority;
  P2CONST(Tdd_Os_ISRIndex, AUTOMATIC, OS_CONST) LpISRIndex;
  uint8 LucIsrCount;
  uint32 LulIsrNumber;
  StatusType LenStatusReturn = E_OS_ACCESS;
  uint32 LulIrqNum;
  uint32 LulIrqEnSetAddr;
  uint32 LulIrqEnClrAddr;
  uint32 LulIrqEnClrPenAddr;
  uint32 LulCounterIsrId;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  
  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LpISRIndex = &Os_GaaISRIndex[OS_CORE_ID];
  LucIsrCount = LpISRIndex->ucIsrCount;
  LpISRPriority = &Os_GaaISRPriority[LpISRIndex->ucIsrStartIdx];

  while (LucIsrCount != OS_ZERO)
  {
    if((LpISRPriority->ucISRType == OS_CAT2_ISR)
        && (LpISRPriority->ddTaskId == ISRID)
        #if(OS_APPLICATION == STD_ON)
        && (LpISRPriority->ddAppId == Os_GddAppId[OS_CORE_ID])
        #endif
        )
    {
      #if (OS_MULTICORE == STD_ON)
      LulCounterIsrId = OS_COUNTER_ISRID[OS_CORE_ID];
      #else
      LulCounterIsrId = OS_COUNTER_ISRID;
      #endif
      /*polyspace:begin<DEFECT:DEAD_CODE:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
      /*polyspace:begin<MISRA-C3:14.3:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
      /*polyspace:begin<MISRA-C3:2.2:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
      /*polyspace:begin<MISRA-C3:2.1:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
      /*polyspace:begin<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by OS (not our OS), and pointer conversion is required  */
      if((LulCounterIsrId != (uint32)OS_INVALID_ISR_ID) &&
         (LpISRPriority->ddTaskId == LulCounterIsrId))
      {
        if(OS_SYST_CSR.TICKINT == STD_OFF)
        {
          /* Clear current value */
          /* Control and Status register */
          OS_SYST_CSR.TICKINT = STD_ON;
          if(ClearPending == OS_TRUE)
          {
            /* Clear counted flag */
            OS_SYST_CSR.COUNTFLAG = STD_OFF;
          }
          LenStatusReturn = E_OK;
        }
        #if (OS_STATUS == EXTENDED)
        else
        {
          LenStatusReturn = E_OS_NOFUNC;
        }
        #endif
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_33705 */
        LulIsrNumber = (uint32)(LpISRPriority->pICRAddress - OS_ARM_M_IRQ_IPR_START);
        LulIrqNum = LulIsrNumber % OS_NUM_OF_BIT_UINT32;
        LulIrqEnSetAddr = ((LulIsrNumber / OS_NUM_OF_BIT_UINT32) * sizeof(uint32));
        LulIrqEnClrAddr = LulIrqEnSetAddr;
        LulIrqEnClrPenAddr = LulIrqEnSetAddr;
        LulIrqEnSetAddr += OS_ARM_M_IRQ_EN_SET_START;
        LulIrqEnClrAddr += OS_ARM_M_IRQ_EN_CLR_START;
        LulIrqEnClrPenAddr += OS_ARM_M_IRQ_CLEAR_PENDING_START;

        if((*((volatile uint32 *)(LulIrqEnClrAddr)) & ((uint32) 1 << LulIrqNum)) == (uint32)OS_ZERO)
        {
          *((volatile uint32 *)(LulIrqEnSetAddr)) = ((uint32) 1 << LulIrqNum);

          if(ClearPending == OS_TRUE)
          {
            *((volatile uint32 *)(LulIrqEnClrPenAddr)) = ((uint32) 1 << LulIrqNum);
          }
          __asm("dsb");
          __asm("isb");
          LenStatusReturn = E_OK;
          /* Exit the loop for efficiency */
          break;
        }
        #if (OS_STATUS == EXTENDED)
        /* Check whether the nested call of enable interrupt source */
        else
        {
          /* @Trace: SafeOs_SUD_API_35005 */
          /* Set the status return is E_OS_NOFUNC */
          LenStatusReturn = E_OS_NOFUNC;
        }
        #endif
      }
      /*polyspace:end<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by OS (not our OS), and pointer conversion is required  */
      /*polyspace:end<MISRA-C3:14.3:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
      /*polyspace:end<MISRA-C3:2.2:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
      /*polyspace:end<MISRA-C3:2.1:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
      /*polyspace:end<DEFECT:DEAD_CODE:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
    }
    LpISRPriority++;
    LucIsrCount--;
  }

  /* Return the value */
  return (LenStatusReturn);
}
#endif

/*******************************************************************************
** Function Name        : Os_DisableInterruptSource                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called to disable interrupt source **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ISRType                                             **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOs() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaISRPriority, Os_ISR_Count                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_11011 */
#if(OS_CAT2_ISR_COUNT != OS_ZERO)
FUNC(StatusType, OS_CODE) Os_DisableInterruptSource (ISRType ISRID)
{
  P2CONST(Tdd_Os_ISRPriority, AUTOMATIC, OS_CONST) LpISRPriority;
  P2CONST(Tdd_Os_ISRIndex, AUTOMATIC, OS_CONST) LpISRIndex;
  uint8 LucIsrCount;
  uint32 LulIsrNumber;
  StatusType LenStatusReturn = E_OS_ACCESS;
  uint32 LulIrqNum;
  uint32 LulIrqEnClrAddr;
  uint32 LulCounterIsrId;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  
  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LpISRIndex = &Os_GaaISRIndex[OS_CORE_ID];
  LucIsrCount = LpISRIndex->ucIsrCount;
  LpISRPriority = &Os_GaaISRPriority[LpISRIndex->ucIsrStartIdx];

  while (LucIsrCount != OS_ZERO)
  {
    if((LpISRPriority->ucISRType == OS_CAT2_ISR)
        && (LpISRPriority->ddTaskId == ISRID)
        #if(OS_APPLICATION == STD_ON)
        && (LpISRPriority->ddAppId == Os_GddAppId[OS_CORE_ID])
        #endif
        )
    {
      #if (OS_MULTICORE == STD_ON)
      LulCounterIsrId = OS_COUNTER_ISRID[OS_CORE_ID];
      #else
      LulCounterIsrId = OS_COUNTER_ISRID;
      #endif
    /*polyspace:begin<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by OS (not our OS), and pointer conversion is required  */
    /*polyspace:begin<DEFECT:DEAD_CODE:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
    /*polyspace:begin<MISRA-C3:14.3:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
    /*polyspace:begin<MISRA-C3:2.2:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
    /*polyspace:begin<MISRA-C3:2.1:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
      if((LulCounterIsrId != (uint32)OS_INVALID_ISR_ID) &&
         (LpISRPriority->ddTaskId == LulCounterIsrId))
      {
        if(OS_SYST_CSR.TICKINT == STD_ON)
        {
          /** 3. Program Control and Status register */
          OS_SYST_CSR.TICKINT = STD_OFF;
          LenStatusReturn = E_OK;
        }
        #if (OS_STATUS == EXTENDED)
        else
        {
          LenStatusReturn = E_OS_NOFUNC;
        }
        #endif
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_33705 */
        LulIsrNumber = (uint32)(LpISRPriority->pICRAddress - OS_ARM_M_IRQ_IPR_START);
        LulIrqNum = LulIsrNumber % OS_NUM_OF_BIT_UINT32;
        LulIrqEnClrAddr = ((LulIsrNumber / OS_NUM_OF_BIT_UINT32) * sizeof(uint32));
        LulIrqEnClrAddr += OS_ARM_M_IRQ_EN_CLR_START;

        if((*((volatile uint32 *)(LulIrqEnClrAddr)) & ((uint32) 1 << LulIrqNum)) != (uint32)OS_ZERO)
        {
          *((volatile uint32 *)(LulIrqEnClrAddr)) = ((uint32) 1 << LulIrqNum);

          __asm("dsb");
          __asm("isb");
          LenStatusReturn = E_OK;
          /* Exit the loop for efficiency */
          break;
        }
        #if (OS_STATUS == EXTENDED)
        /* Check whether the nested call of enable interrupt source */
        else
        {
          /* @Trace: SafeOs_SUD_API_35005 */
          /* Set the status return is E_OS_NOFUNC */
          LenStatusReturn = E_OS_NOFUNC;
        }
        #endif
      }
    }
    /*polyspace:end<DEFECT:DEAD_CODE:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
    /*polyspace:end<MISRA-C3:14.3:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
    /*polyspace:end<MISRA-C3:2.2:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
    /*polyspace:end<MISRA-C3:2.1:Not a defect: Justify with annotations> Verified manually with no impacts due to error check characteristic of user configuration */
    /*polyspace:end<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by OS (not our OS), and pointer conversion is required  */
    LpISRPriority++;
    LucIsrCount--;
  }

  /* Return the value */
  return (LenStatusReturn);
}
#endif

/*******************************************************************************
** Function Name        : Os_ClearPendingInterruptSource                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called to clear pending interrupt  **
**                        source                                              **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ISRID                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOs() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaISRPriority, Os_ISR_Count                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if(OS_CAT2_ISR_COUNT != OS_ZERO)
FUNC(StatusType, OS_CODE) Os_ClearPendingInterruptSource (ISRType ISRID)
{
  P2CONST(Tdd_Os_ISRPriority, AUTOMATIC, OS_CONST) LpISRPriority;
  P2CONST(Tdd_Os_ISRIndex, AUTOMATIC, OS_CONST) LpISRIndex;
  uint8 LucIsrCount;
  uint32 LulIsrNumber;
  StatusType LenStatusReturn = E_OS_ACCESS;
  uint32 LulIrqNum;
  uint32 LulIrqEnClrPenAddr;
  uint32 LulCounterIsrId;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  
  /* Get core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LpISRIndex = &Os_GaaISRIndex[OS_CORE_ID];
  LucIsrCount = LpISRIndex->ucIsrCount;
  LpISRPriority = &Os_GaaISRPriority[LpISRIndex->ucIsrStartIdx];

  while (LucIsrCount != OS_ZERO)
  {
    if((LpISRPriority->ucISRType == OS_CAT2_ISR)
        && (LpISRPriority->ddTaskId == ISRID)
        #if(OS_APPLICATION == STD_ON)
        && (LpISRPriority->ddAppId == Os_GddAppId[OS_CORE_ID])
        #endif
        )
    {
      #if (OS_MULTICORE == STD_ON)
      LulCounterIsrId = OS_COUNTER_ISRID[OS_CORE_ID];
      #else
      LulCounterIsrId = OS_COUNTER_ISRID;
      #endif
      /*polyspace:begin<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by OS (not our OS), and pointer conversion is required  */
      /*polyspace-begin DEFECT:DEAD_CODE MISRA-C3:14.3,2.2,2.1 [Not a defect:low] "Verified manually with no impacts due to error check characteristic of user configuration" */
      if((LulCounterIsrId != (uint32)OS_INVALID_ISR_ID) &&
         (LpISRPriority->ddTaskId == LulCounterIsrId))
      {
        OS_SYST_CSR.COUNTFLAG = STD_OFF;
        LenStatusReturn = E_OK;
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_33705 */
        LulIsrNumber = (uint32)(LpISRPriority->pICRAddress - OS_ARM_M_IRQ_IPR_START);
        LulIrqNum = LulIsrNumber % OS_NUM_OF_BIT_UINT32;
        LulIrqEnClrPenAddr = ((LulIsrNumber / OS_NUM_OF_BIT_UINT32) * sizeof(uint32));
        LulIrqEnClrPenAddr += OS_ARM_M_IRQ_CLEAR_PENDING_START;

        *((volatile uint32 *)(LulIrqEnClrPenAddr)) = ((uint32) 1 << LulIrqNum);

        __asm("dsb");
        __asm("isb");
        LenStatusReturn = E_OK;
        /* Exit the loop for efficiency */
        break;
      }
    }
    /*polyspace-begin DEFECT:DEAD_CODE MISRA-C3:14.3,2.2,2.1 [Not a defect:low] "Verified manually with no impacts due to error check characteristic of user configuration" */
    /*polyspace:end<CERT-C:INT36-C:Not a defect: Justify with annotations> variable is provided by OS (not our OS), and pointer conversion is required  */
    LpISRPriority++;
    LucIsrCount--;
  }

  /* Return the value */
  return (LenStatusReturn);
}
#endif

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<RTE:NIP:Not a defect:Justify with annotations> Initialized at other location */
/* polyspace:end<RTE:NIV:Not a defect:Justify with annotations> Variable initialized at other location */
/* polyspace:end<RTE:SHF:Not a defect:Justify with annotations> Calculated access to outside bounds */
/* polyspace:end<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:end<RTE:OBAI:Not a defect:Justify with annotations> configured array index */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> Run-time failures are justified */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:11.1:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace-end MISRA-C3:18.1 */
/* polyspace:end<MISRA-C3:18.4:Not a defect:Justify with annotations> Operators on pointer is used for better performance */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<CERT-C:INT36-C:Not a defect:Justify with annotation> This conversion cannot be modified to handle memory */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
