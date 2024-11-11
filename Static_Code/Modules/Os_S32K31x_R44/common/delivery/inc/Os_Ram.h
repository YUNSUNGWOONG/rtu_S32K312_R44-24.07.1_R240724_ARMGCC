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
**  SRC-MODULE: Os_Ram.h                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for Os_Ram.c                                      **
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
** 1.5.0     26-Jun-2023   HJ.Kim           Jira CP44-2459                    **
**            9-Jun-2023   HJ.Kim           Jira CP44-2325                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-2097                    **
**                                          Jira CP44-2028                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace-begin MISRA-C3:8.11 [Justified:Low] "External linkage with array size makes error because of compiler optimization" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

#ifndef OS_RAM_H
#define OS_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
#include "MemMap.h"
extern VAR(boolean, OS_VAR) Os_GblOsInitialized[];
extern VAR(boolean, OS_VAR) Os_GblISRLock[];
extern VAR(boolean, OS_VAR) Os_GblStartOs[];
extern VAR(boolean, OS_VAR) Os_GblBeforeHalt[];
extern VAR(boolean, OS_VAR) Os_GblInterCoreInt[];
extern VAR(boolean, OS_VAR) Os_GblCoreShutdown[];
/* @Trace: SRS_BSW_00410 */
#if (OS_MULTICORE == STD_ON)
extern VAR(boolean, OS_VAR) Os_GblAppModeCheck;
extern VAR(boolean, OS_VAR) Os_GblShutdownFlag[];
#endif
#if (OS_TIMING_PROTECTION == STD_ON)
extern VAR(boolean, OS_VAR) Os_GblTPSFlag[];
#endif
#if (OS_TRUSTED_FUNC_COUNT != OS_PRE_ZERO)
extern VAR(boolean, OS_VAR) Os_GblTimeViolationDelayed[];
#endif
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
#include "MemMap.h"
extern VAR(Os_IsrLockType, OS_VAR) Os_GddISRLock[];
extern VAR(Os_IsrLockType, OS_VAR) Os_GddISR2Lock[];
extern VAR(AppModeType, OS_VAR) Os_GddAppMode;
extern VAR(TaskType, OS_VAR) Os_GddIdleTaskId[];
#if (OS_MULTICORE == STD_ON)
extern volatile VAR(uint8, OS_VAR) Os_GucSync1;
extern VAR(uint8, OS_VAR) Os_GucActivateCore;
#endif
#if(OS_APPLICATION == STD_ON)
extern VAR(ApplicationType, OS_VAR) Os_GddAppId[];
extern VAR(ApplicationType, OS_VAR) Os_GddCurAppId[];
#endif
#if (OS_TRUSTED_FUNC_COUNT != OS_PRE_ZERO)
extern VAR(uint8, OS_VAR) Os_GucTrustedFuncCount[];
#endif
#if (OS_TIMING_PROTECTION == STD_ON)
extern VAR(uint8, OS_VAR) Os_GucExecFail[];
extern VAR(TaskType, OS_VAR) Os_GddFaultyTask[];
#endif /* OS_TIMING_PROTECTION == STD_ON */
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
#include "MemMap.h"
extern VAR(uint16, OS_VAR) Os_GusCallevelCheck[];

#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
#include "MemMap.h"

#if (OS_TIMING_PROTECTION == STD_ON)
extern VAR(uint32, OS_VAR) Os_GulBudgetTimerCount[];
extern VAR(uint32, OS_VAR) Os_GulTFTimerCount[];
#endif
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) Os_GpStaticTask[];
extern VAR(TaskType, OS_VAR) Os_GaaLinkIndex[];
extern P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) Os_GpLinkTask[];
extern VAR(Os_OldLevel_T, OS_VAR) Os_GddOldSuspendOs[];
extern VAR(Os_OldLevel_T, OS_VAR) Os_GddOldSuspendAll[];
extern VAR(IdleModeType, OS_VAR) Os_GddCurIdleMode[];
extern VAR(Os_StackType, OS_VAR) Os_GaaRamTaskStackSize[];
#if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
extern VAR(Os_StackType, OS_VAR) Os_GaaRamISRStackSize[];
#endif /* End of if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO) */
#if (OS_ERROR_HOOK == STD_ON)
extern VAR(Tdd_Os_ServiceCall, OS_VAR) Os_GddServiceCall[];
#endif /* End of if (OS_ERROR_HOOK == STD_ON) */
#if (OS_APPLICATION == STD_ON)
extern VAR(Tdd_Os_ApplicationData, OS_VAR) Os_GaaApplication[];
#endif
#if (OS_MULTICORE == STD_ON)
/* polyspace +1 MISRA-C3:8.5 [Justified:Low] "To avoid cross reference, external array is needed." */
extern VAR(Tdd_Os_Core, OS_VAR) Os_GaaCore[];

#endif
#if (OS_TIMING_PROTECTION == STD_ON)
extern P2VAR(Tdd_Os_ScheduleWatchdog, AUTOMATIC, OS_VAR) Os_GpSchedWatchdog[];
extern VAR(Tdd_Os_TPWatchdog, OS_VAR) Os_GaaRunningWdg[];
#endif

#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, OS_CODE) Os_MemCopy(void *dstAddr, const void *srcAddr, const uint32 cntData);
FUNC(void, OS_CODE) Os_MemSet(void *dstAddr, const uint8 data, const uint32 cntData);
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /* OS_RAM_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace-end MISRA-C3:8.11 [Justified:Low] "External linkage with array size makes error because of compiler optimization" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
