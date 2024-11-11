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
**  SRC-MODULE: Os_SchedTable.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for Os_SchedTable.c file containing the           **
**              declaration of Schedule Table functionality related functions **
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
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

#ifndef OS_SCHEDTABLE_H
#define OS_SCHEDTABLE_H
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

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/* @Trace: SRS_BSW_00410 */
#if (OS_SCHEDTABLE == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_ProcessSchedTable(P2VAR
                          (Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) pAction);
extern FUNC(StatusType, OS_CODE) Os_DoStartScheduleTableRel(ScheduleTableType
                       ScheduleTableID, TickType Offset, boolean LblRemoteCall);
extern FUNC(StatusType, OS_CODE) Os_DoStartScheduleTableAbs(ScheduleTableType
                        ScheduleTableID, TickType Start, boolean LblRemoteCall);
extern FUNC(StatusType, OS_CODE) Os_DoStopScheduleTable(ScheduleTableType
                                        ScheduleTableID, boolean LblRemoteCall);
extern FUNC(StatusType, OS_CODE) Os_DoNextScheduleTable(
                                      ScheduleTableType ScheduleTableID_From,
                                      ScheduleTableType ScheduleTableID_To,
                                      boolean LblRemoteCall);
extern FUNC(StatusType, OS_CODE) Os_DoGetScheduleTableStatus(
                                      ScheduleTableType ScheduleTableID,
                                      ScheduleTableStatusRefType ScheduleStatus,
                                      boolean LblRemoteCall);
#endif /*(OS_SCHEDTABLE == STD_ON)*/

#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_DoStartScheduleTableSynchron(
                                              ScheduleTableType ScheduleTableID,
                                              boolean LblRemoteCall);
extern FUNC(StatusType, OS_CODE) Os_DoSyncScheduleTable(ScheduleTableType
                                                        ScheduleTableID,
                                                        TickType Value,
                                                        boolean LblRemoteCall);
extern FUNC(StatusType, OS_CODE) Os_DoSetScheduleTableAsync(
                                              ScheduleTableType ScheduleTableID,
                                              boolean LblRemoteCall);
#endif /* #if(OS_SCHED_EXPLICIT_SYNC == STD_ON) */

#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
extern FUNC(StatusType, OS_CODE)Os_SyncScheduleTableError
                             (ScheduleTableType ScheduleTableID,TickType Value);
#endif /* #if(OS_SCHED_EXPLICIT_SYNC == STD_ON) */

#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
extern FUNC(void, OS_CODE)Os_SyncSchedRunning(ScheduleTableType ScheduleTableID,
                                             TickType Value,TickType LddOffSet);
#endif /* #if(OS_SCHED_EXPLICIT_SYNC == STD_ON) */



#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif /* OS_SCHEDTABLE_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
