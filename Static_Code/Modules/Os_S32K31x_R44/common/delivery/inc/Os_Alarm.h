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
**  SRC-MODULE: Os_Alarm.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for Os_Alarm.c file containing the declaration of **
**              Alarm related functions.                                      **
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
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2005                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.2     07-Oct-2020   DanhDC1          R44-Redmine #15959                **
**                                          Remove un-used function           **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

#ifndef OS_ALARM_H
#define OS_ALARM_H

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
#if ((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON))
extern FUNC(void, OS_CODE) Os_InsertAlarm(P2VAR(Tdd_Os_Alarm, AUTOMATIC,
                                                               OS_VAR) LpAlarm);

extern FUNC(void, OS_CODE) Os_RemoveAlarm(P2VAR(Tdd_Os_Alarm, AUTOMATIC,
                                                               OS_VAR) LpAlarm);

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

#if (OS_ALARM == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_DoGetAlarm(AlarmType AlarmID,
                                       TickRefType Tick, boolean LblRemoteCall);
extern FUNC(StatusType, OS_CODE) Os_DoSetRelAlarm(AlarmType AlarmID,
                     TickType Increment, TickType Cycle, boolean LblRemoteCall);
extern FUNC(StatusType, OS_CODE) Os_DoSetAbsAlarm(AlarmType AlarmID,
                         TickType Start, TickType Cycle, boolean LblRemoteCall);
extern FUNC(StatusType, OS_CODE) Os_DoCancelAlarm(AlarmType AlarmID,
                                                         boolean LblRemoteCall);
extern FUNC(StatusType, OS_CODE) Os_DoGetAlarmBase(AlarmType AlarmID,
                                  AlarmBaseRefType Info, boolean LblRemoteCall);
#endif /* End of if (OS_ALARM == STD_ON) */
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define OS_API_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#if (OS_ALARM == STD_ON)
extern FUNC(StatusType, OS_CODE) Os_CallGetAlarmBase(AlarmType AlarmID,  AlarmBaseRefType Info);
extern FUNC(StatusType, OS_CODE) Os_CallGetAlarm(AlarmType AlarmID,  TickRefType Tick);
extern FUNC(StatusType, OS_CODE) Os_CallCancelAlarm(AlarmType AlarmID);
#endif /* End of if (OS_ALARM == STD_ON) */
#define OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"


#endif /* OS_ALARM_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
