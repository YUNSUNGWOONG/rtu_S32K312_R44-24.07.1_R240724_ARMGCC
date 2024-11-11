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
**  SRC-MODULE: Os_Arch_Timer.h                                               **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for S32K31x related (OS) Timer API                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:     Yes                                      **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:  No                                       **
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
** 1.1.0      7-Apr-2023    HG.Kim       Jira    CP44-1803                    **
** 1.0.2     11-Jan-2023    HGKim        Jira    CP44-1488                    **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

#ifndef OS_ARCH_EXCEPT_H_
#define OS_ARCH_EXCEPT_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

extern FUNC(void, OS_CODE) Reset_Handler(void);
#if (OS_MULTICORE == STD_ON)
extern FUNC(void, OS_CODE) Reset_Handler_Core1(void);
#if (OS_CORE_COUNT >= OS_THREE)
extern FUNC(void, OS_CODE) Reset_Handler_Core2(void);
#if (OS_CORE_COUNT >= OS_FOUR)
extern FUNC(void, OS_CODE) Reset_Handler_Core3(void);
#endif /* Core 4*/
#endif /* Core 3*/
#endif /* End of if (OS_MULTICORE == STD_ON) */
extern FUNC(void, OS_CODE) Os_NMIHandler(void);
extern FUNC(void, OS_CODE) Os_FaultHandler(void);
extern FUNC(void, OS_CODE) Os_SVCallHandler(void);
extern FUNC(void, OS_CODE) Os_ISRHandler(void);
extern FUNC(void, OS_CODE) Os_UnusedExceptionHandler(void);
extern uint32 Os_CallFuncKernelStack(uint32 param0, uint32 param1,
                                                uint32 param2, uint32 param3, uint32 param4, uint32 function);

/* polyspace +3 MISRA-C3:21.2 [Not a defect:Low] "Defined in .ld file" */
/* polyspace<MISRA-C3:8.6:Not a defect:Justify with annotations> Defined in .ld file */
extern uint32 StackTop;
#if (OS_MULTICORE == STD_ON)
extern uint32 OS_MAIN_TOS;
extern uint32 OS_CORE1_TOS;   /* Top of Core1 Stack(Kernel Stack) */
#if (OS_CORE_COUNT >= OS_THREE)
extern uint32 OS_CORE2_TOS;   /* Top of Core2 Stack(Kernel Stack) */
#if (OS_CORE_COUNT >= OS_FOUR)
extern uint32 OS_CORE3_TOS;   /* Top of Core3 Stack(Kernel Stack) */
#endif /* FOUR */
#endif /* THREE */
#endif /* End of if (OS_MULTICORE == STD_ON) */

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /* OS_ARCH_TIMER_H_ */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/


