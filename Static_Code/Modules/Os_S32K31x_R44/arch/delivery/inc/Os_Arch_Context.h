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
**  SRC-MODULE: Os_Arch_Context.h                                             **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for S32K31x related register                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:       Yes                                    **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:    No                                     **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.1.1     23-Nov-2023    HJ.Kim       Jira    CP44-3306                    **
** 1.0.2     11-Jen-2023    HGKim        Jira    CP44-1488                    **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:D4.9:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
/* polyspace-begin CERT-C:PRE00-C [Not a defect:Low] "Function like macro is used to improve performance" */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:8.11:Not a defect:Justify with annotations> The generator generates exact size of initializers */
/* polyspace:begin<MISRA-C3:9.5:Not a defect:Justify with annotations> The generator generates exact size of initializers */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

#ifndef OS_ARCH_CONTEXT_H_
#define OS_ARCH_CONTEXT_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Arch_Regs.h"
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/**
 * @addtogroup OS_S32K31X_ESDD
 * @{ */
 
 /** Macro for flag of context-switching
 *  \n{Ref: SWR_OS_S32K31X_006} */
#define CONTEXT_SWITCHING_NONE      0x00u
/** Macro for flag of context-switching
 *  \n{Ref: SWR_OS_S32K31X_006} */
#define CONTEXT_SWITCHING_STARTUP   0x01u
/** Macro for flag of context-switching
 *  \n{Ref: SWR_OS_S32K31X_006} */
#define CONTEXT_SWITCHING_LOAD      0x02u
/** Macro for flag of context-switching
 *  \n{Ref: SWR_OS_S32K31X_006} */
#define CONTEXT_SWITCHING_SAVE      0x04u
/** Macro for flag of context-switching
 *  \n{Ref: SWR_OS_S32K31X_006} */
#define CONTEXT_SWITCHING_RELOAD    0x08u

/** Macro for Task's initialized PSR
 *  \n{Ref: SWR_OS_S32K31X_006} */
#define OS_TASK_INIT_PSR            0x01000000u    /* Thumb, Thread mode */
/** Macro for EXEC_RETURN (Thread, PSP)
 *  \n{Ref: SWR_OS_S32K31X_006} */
#define OS_EXC_RETURN_THREAD_MODE   0xFFFFFFFDu    /* Thread Mode, PSP   */

/** Macro to write a typical data at the end of stack frame
 *  \n{Ref: SWR_OS_S32K31X_006} */
#define OS_STACK_PATTERN                (Os_StackType)(0xAAAAAAAAu)

/** Macro for invalid stack pointer
 *  \n{Ref: SWR_OS_S32K31X_006} */
#define INVALID_STACK_POINTER           0xFFFFFFFFUL

/** Macro for Stack frame (quadword alignment)
 *  \n{Ref: SWR_OS_S32K31X_006} */
#define OS_STACK_RSVD_SIZE              1U

/** Macro for invalid address
 *  \n{Ref: SWR_OS_S32K31X_006} */
#define OS_INVALID_ADDRESS              0xFFFFFFFFUL

/** Macro for saved context size ( sizeof(Tdd_Os_ContextSwitch) - sizeof(pPowerOnSP) )
  *  \n{Ref: SWR_OS_S32K31X_001} */
#if (OS_FPU_SUPPORT == STD_ON)
#define OS_CONTEXT_SIZE                 208U
#else
#define OS_CONTEXT_SIZE                 72U
#endif

/* Used by CPU & IT Load */
#define OS_GET_TIMESTAMP()   (OS_STM0_CNT)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern FUNC(void, OS_CODE) Os_Dispatch(void);
extern FUNC(void, OS_CODE) Os_ReInitContext(P2CONST(
                          Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask);
extern FUNC(void, OS_CODE) Os_DoContextSwitch
                 (P2CONST(Tdd_Os_ContextSwitch, AUTOMATIC, OS_CONST) LpContext);
extern FUNC(void, OS_CODE) Os_SetTaskStackPointer(void);
/* polyspace +2 MISRA-C3:20.7 [Justified:Low] "AUTOSAR compiler abstraction" */
extern FUNC(uint32*, OS_CODE) Os_GetStackPointer(P2CONST(
                          Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask);
#if ((OS_PROTECTION_HOOK == STD_ON) || (OS_APPLICATION == STD_ON))
extern FUNC(void, OS_CODE) OS_REMOVECONTEXT(P2CONST(
                          Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask);
#endif
extern FUNC(void, OS_CODE) OS_STARTUPCONTEXT(void);
extern FUNC(void, OS_CODE) OS_LOADCONTEXT(void);
extern FUNC(void, OS_CODE) OS_SAVECONTEXT(void);
extern FUNC(void, OS_CODE) OS_RELOADCONTEXT(void);
extern FUNC(void, OS_CODE) Os_DoContextSwitch_ToCAT2(void);

#if (OS_MEMORY_PROTECTION == STD_ON)
extern FUNC(void, OS_CODE) Os_NontrustedAppHook(ApplicationType LddAppId,
            P2FUNC(void, OS_VAR, pAppHook)(StatusType Error), StatusType Error);
extern FUNC(void, OS_CODE) Os_NontrustedAppStartupHook(ApplicationType LddAppId,
            P2FUNC(void, OS_VAR, pAppStartupHook)(void));
#endif /* End of if (OS_MEMORY_PROTECTION == STD_ON) */

/***************************************************************************//**
 * Function Name        : OS_INFINITELOOP
 *
 * Service ID           : NA
 *
 * Description          : Inline function to loop infinitely
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * return               : void
 *
 * pre                  : StartOS() function should be called
 *
 * remarks              : Global Variable(s)     :
 *                        None
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_005}
 *
 * @ingroup               OS_S32K31X_ESDD_003
 ******************************************************************************/
OS_LOCAL_INLINE FUNC(void, OS_CODE) OS_INFINITELOOP(void)
{
  /* polyspace<RTE : NTL :Not a defect:Justify with annotations> Infinite loop is intended instruction for failed init. */
  while(1)
  {
    /* @Trace: SafeOs_SUD_API_47101 */
  }
}

#endif /* OS_ARCH_CONTEXT_H_ */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:D4.9:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
/* polyspace-end CERT-C:PRE00-C [Not a defect:Low] "Function like macro is used to improve performance" */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:8.11:Not a defect:Justify with annotations> The generator generates exact size of initializers */
/* polyspace:end<MISRA-C3:9.5:Not a defect:Justify with annotations> The generator generates exact size of initializers */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
