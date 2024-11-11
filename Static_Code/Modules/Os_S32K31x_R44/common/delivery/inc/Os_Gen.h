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
**  SRC-MODULE: Os_Gen.h                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for generated Os files containing the declaration **
**              of Task, Counter, Alarm, ScheduleTable related functions.     **
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
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
**                                          Jira CP44-2005                    **
** 1.3.9.2   20-Jul-2022   TinHV            Jira CP44-661                     **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.2     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Add comment for MISRAC 8.5        **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

#ifndef OS_GEN_H
#define OS_GEN_H

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os.h"
#include "Os_InternalTypes.h"
#include "Os_PortTypes.h"

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

/* polyspace-begin MISRA-C3:8.5 [Justified:Low] "To avoid cross reference, external function needed." */
extern FUNC(void, OS_CODE) Os_Sleep(void);

/* @Trace: SRS_BSW_00410 */
#if ((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON))
extern FUNC(StatusType, OS_CODE) Os_ProcessAlarm(P2CONST(Tdd_Os_StaticCounter,
                                          AUTOMATIC, OS_CONST) LpStaticCounter);

#if (OS_TASK == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_AlarmActivateTask(P2CONST
                         (Tdd_Os_ActivateTask, AUTOMATIC, OS_CONST) LpAction);
#endif /* (OS_TASK == STD_ON) */

#if (OS_EVENT == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_AlarmSetEvent(P2CONST(Tdd_Os_AlarmEvent,
                                                 AUTOMATIC,OS_CONST) LpAction);
#endif /* #if(OS_EVENT == STD_ON) */
#endif /* #if((OS_ALARM == STD_ON)||(OS_SCHEDTABLE == STD_ON)) */

#if (OS_CALLBACK_COUNT > OS_PRE_ZERO)
extern FUNC(StatusType,OS_CODE) Os_AlarmCallback(P2CONST(Tdd_Os_AlarmCallback,
                                                  AUTOMATIC, OS_CONST) LpAction);
#endif /* (OS_CALLBACK_COUNT > OS_PRE_ZERO) */

#if (OS_INCCOUNTER_COUNT > OS_PRE_ZERO)
extern FUNC(StatusType,  OS_CODE) Os_AlarmIncrementCounter(P2CONST
                        (Tdd_Os_IncrementCounter, AUTOMATIC, OS_CONST) LpAction);
#endif /* (OS_INCCOUNTER_COUNT > OS_PRE_ZERO) */

#if (OS_SCHEDTABLE == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_ProcessSchedTable(P2VAR
                         (Tdd_Os_SchedTable, AUTOMATIC, OS_CONST) LpAction);
#endif /* (OS_SCHEDTABLE == STD_ON) */

#if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
extern FUNC(void, OS_CODE) Os_UpdateCountInCounterISR(
             P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) LpStaticCounter,
                  P2CONST(Tdd_Os_HardwareCounter, AUTOMATIC, OS_VAR) LpHwCounter);

extern FUNC(void, OS_CODE) Os_ResetTimer(
        CONSTP2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) LpStaticCounter,
             CONSTP2VAR(Tdd_Os_HardwareCounter, AUTOMATIC, OS_VAR) LpHwCounter);
#endif
/* polyspace-end MISRA-C3:8.5 [Justified:Low] "To avoid cross reference, external function needed." */

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#if (OS_ISR_COUNT != OS_PRE_ZERO)

#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* polyspace +2 MISRA-C3:8.11 [Justified:Low] "External linkage with array size makes error because of compiler optimization" */
/* @Trace: SRS_BSW_00309 */
extern CONST(Tdd_Os_ISRPriority, OS_CONST) Os_GaaISRPriority[];
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* polyspace +1 MISRA-C3:8.11 [Justified:Low] "External linkage with array size makes error because of compiler optimization" */
extern CONST(Tdd_Os_ISRIndex, OS_CONST) Os_GaaISRIndex[];
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
#endif

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* @Trace: SafeOs_SUD_API_000109 */
extern VAR(Tdd_Os_ContextSwitch, OS_VAR) Os_GaaContextSwitch[];
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/** Variable to hold Timing Protection Values */
#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* @Trace: SafeOs_SUD_API_000408 */
extern VAR(TickType, OS_VAR) Os_GaaTimingProtValue[];
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#endif /* OS_GEN_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
