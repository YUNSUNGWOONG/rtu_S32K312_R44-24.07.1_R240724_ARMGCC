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
**  SRC-MODULE: Os_Kernel.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for Os_Kernel.c file containing the declaration   **
**              of Kernel functionality related functions.                    **
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
** 1.5.1     06-Oct-2023   JC.Kim           Jira CP44-2438                    **
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
** 1.4.0     19-Sep-2022   TinHV            Jira CP44-192                     **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.4     23-Sep-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Defect detect by polyspace  **
** 1.0.4     26-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C 2.5                 **
** 1.0.3     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Add comment for Misra-C D4.5      **
** 1.0.2     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.1     20-Jul-2020   DanhDC1          R44-Redmine #14601 Change the type**
**                                          of internal variable for the      **
**                                          ActivateTaskCount                 **
**                                          and Os_GaaLinkIndex variable      **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

#ifndef OS_KERNEL_H
#define OS_KERNEL_H

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/* @Trace: SRS_BSW_00410 */
#if (OS_TASK == STD_ON)
extern FUNC(void, OS_CODE) Os_ScheduleFromChain(void);

extern FUNC(void, OS_CODE) Os_InsertTask(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
                                                       OS_CONST) LpStaticTask);
extern FUNC(void, OS_CODE) Os_InsertPreemptedTask(P2CONST(Tdd_Os_StaticTask,
                                            AUTOMATIC, OS_CONST) LpStaticTask);
extern FUNC(void, OS_CODE) Os_RunTask(void);
#endif /*OS_TASK == STD_ON*/

extern FUNC(void, OS_CODE) Os_KillTask(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
                                                       OS_CONST) LpStaticTask);

extern FUNC(void, OS_CODE) Os_Sleep(void);

extern FUNC(void, OS_CODE) Os_ScheduleService(void);

#if ((OS_PROTECTION_HOOK == STD_ON) || (OS_APPLICATION == STD_ON))
extern FUNC(void, OS_CODE) Os_KillTask(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
                                                        OS_CONST) LpStaticTask);

extern FUNC(void, OS_CODE) Os_KillIsr(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
                                                        OS_CONST) LpStaticTask);
#endif

#if (OS_PROTECTION_HOOK == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_ProtectionHookService(
                                                         StatusType Fatalerror);

extern FUNC(StatusType, OS_CODE) Os_KillTaskOrISR(void);
#endif

#if ((OS_PROTECTION_HOOK == STD_ON) || (OS_APPLICATION == STD_ON))
extern FUNC(void, OS_CODE) Os_KillUsedCsa(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
                                                        OS_CONST) LpStaticTask);
#endif /* End of if (OS_PROTECTION_HOOk == STD_ON) */

/* polyspace +1 MISRA-C3:8.5 [Justified:Low] "To avoid cross reference, external function needed." */
extern FUNC(void, OS_CODE) Os_InitTimer(void);


/* @Trace: SRS_BSW_00330 */
#if (OS_MAX_ACTIVATION_COUNT != OS_ONE)
/* polyspace +2 MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */
/* polyspace +1 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
#define OS_INSERT_TASK_IN_QUEUE()\
  LulIndex = Os_GaaLinkIndex[LpStaticTask->ddTaskId];\
  Os_GaaLinkIndex[LpStaticTask->ddTaskId]++;\
  if (Os_GaaLinkIndex[LpStaticTask->ddTaskId] ==\
      (LpStaticTask->ulMaxActivateCount))\
  {\
    Os_GaaLinkIndex[LpStaticTask->ddTaskId] = OS_ZERO;\
  }\
  LpLinkTask = LpStaticTask->pLinkTask + LulIndex;\
  LpLinkTask->scPriority = (sint8)(LpStaticTask->ucBasePriority);

#else /* End of if (OS_MAX_ACTIVATION_COUNT != OS_ONE) */
/* polyspace +1 MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */
#define OS_INSERT_TASK_IN_QUEUE()\
  do{\
    LpLinkTask = LpStaticTask->pLinkTask;\
    LpLinkTask->scPriority = (sint8)(LpStaticTask->ucBasePriority);\
  } while(0)

#endif /* End of if (OS_MAX_ACTIVATION_COUNT != OS_ONE) */
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /* OS_KERNEL_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
