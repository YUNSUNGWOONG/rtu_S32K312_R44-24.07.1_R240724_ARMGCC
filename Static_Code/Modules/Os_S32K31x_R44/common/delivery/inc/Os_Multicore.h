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
**  SRC-MODULE: Os_Multicore.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for Os_Multicore.c file containing the declaration**
**              of Multicore functionality related functions.                 **
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
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

#ifndef OS_MULTICORE_H_
#define OS_MULTICORE_H_

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/*
 * @def OS_CORE_ID
 *
 * This is a ID of a Core
 */
/* @Trace: SRS_BSW_00410 */
#if (OS_MULTICORE == STD_ON)
/* polyspace-begin MISRA-C3:20.4 [Justified:Low] "Definition for function redirection does not use parenthesised expression" */
/* polyspace-begin MISRA-C3:5.4 [Justified:Low] "This macro is define for core id is returned so and has no impact" */
#define OS_CORE_ID                     LddCoreId
#else
#define OS_CORE_ID                     (OS_CORE_ID_MASTER)
#endif
/* polyspace-end MISRA-C3:5.7 [Justified:Low] "This is to refer structure of Os_PortTypes.h which include this file." */
/* polyspace-end MISRA-C3:1.3 [Justified:Low] "This is to refer structure of Os_PortTypes.h which include this file." */
#define OS_SPIN_LOCK_ZERO              0

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */

#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#if (OS_MULTICORE == STD_ON)
extern FUNC(void, OS_CODE) Os_TryToGetSpinlock
       (SpinlockIdType SpinlockId, boolean* Success);

extern FUNC(void, OS_CODE) Os_GetSpinlock(SpinlockIdType SpinlockId);

extern FUNC(void, OS_CODE) Os_ReleaseSpinlock(SpinlockIdType SpinlockId);

extern FUNC(void, OS_CODE) Os_StartCore(CoreIdType CoreID);

extern FUNC(void, OS_CODE) Os_SetSyncFirst(void);

extern FUNC(void, OS_CODE) Os_SetSyncSecond(void);

extern FUNC(void, OS_CODE) Os_SetSyncCountShutDown(void);

extern FUNC(void, OS_CODE) Os_WaitSyncShutDown(void);

extern FUNC(CoreIdType, OS_CODE) Os_KernGetCoreID(void);
#else
/* polyspace +2 MISRA-C3:20.4 [Justified:Low] "Definition for function redirection does not use parenthesised expression" */
/* polyspace +1 MISRA-C3:11.1 [Justified:Low] "For implementation, conversion from function pointer to void pointer is needed to represent function address" */
#define Os_KernGetCoreID    Os_KernUnknownSyscall
#endif /* End of if (OS_MULTICORE == STD_ON) */
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define OS_API_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#if (OS_MULTICORE == STD_ON)
extern FUNC(CoreIdType, OS_CODE) Os_CallGetCoreID(void);
#endif /* End of if (OS_MULTICORE == STD_ON) */
#define OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /* OS_MULTICORE_H_ */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
