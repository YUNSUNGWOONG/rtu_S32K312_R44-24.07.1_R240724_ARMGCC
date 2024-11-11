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
**  SRC-MODULE: Os_TimingProtection.h                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for OS_TIMINGPROTECTION.c file containing the     **
**              declaration of Timer Protection functionality related         **
**              functions.                                                    **
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
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.2     18-Aug-2020   Nguyen           R44-Redmine #13974                **
**                                          Bugfix for Multi-Timing Protect   **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

#ifndef OS_TIMINGPROTECTION_H
#define OS_TIMINGPROTECTION_H

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (OS_TIMING_PROTECTION == STD_ON)
#define OS_TIMEFRAME_WATCHDOG               0
#define OS_BUDGET_WATCHDOG                  1
#define OS_INT_LOCK_INDEX                   0
#define OS_ALL_INT_LOCK_INDEX               1

/* @Trace: SRS_BSW_00330 */
/* This macro stops Interrupt monitoring Timer*/
/* polyspace +1 MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */
#define Os_StopIntMonitor(LpStaticTask, LulIndex)\
  do{ \
    Os_UpdateTpStructure(LpStaticTask); \
  } while(0)

/* This macro stops Resource monitoring Timer*/
/* polyspace +1 MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */
#define Os_StopResMonitor(LpStaticTask, LpResource)\
  do{\
    Os_UpdateTpStructure(LpStaticTask); \
  } while(0)

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
extern FUNC(void, OS_CODE) Os_StartAllLockMonitor(void);

extern FUNC(void, OS_CODE) Os_StartOsLockMonitor(void);

extern FUNC(void, OS_CODE) Os_StopAllLockMonitor(void);

extern FUNC(void, OS_CODE) Os_StopOsLockMonitor(void);
#endif

extern FUNC(void, OS_CODE) Os_OsWdgHandler(void);

extern FUNC(void, OS_CODE) Os_TimeFrameHandler(void);

extern FUNC(boolean, OS_CODE) Os_GetTimeElapsedService(uint8 TimerType,
                                                      TickRefType TimeElapsed);

extern FUNC(void, OS_CODE) Os_StartTimer(uint8 TimerType,
                                                         TickType LddTickValue);

extern FUNC(void, OS_CODE) Os_StopTimer(uint8 TimerType);

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /* End of if (OS_TIMING_PROTECTION == STD_ON) */
#endif /* OS_TIMINGPROTECTION_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
