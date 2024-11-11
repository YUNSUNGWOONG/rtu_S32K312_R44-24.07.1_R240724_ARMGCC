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
**  SRC-MODULE: Os_MulticoreMessage.h                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for Os_MulticoreMessage.c file containing the     **
**              declaration of Inter-core Message functionality related       **
**              functions.                                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.5.3     16-Feb-2024   HG.Kim           Jira CP44-3828                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6     13-Oct-2020   DanhDC1          R44-Redmine #16287 don't allow    **
**                                          Counter in case of cross core     **
** 1.0.5     07-Oct-2020   DanhDC1          R44-Redmine #15959                **
**                                          Remove un-used function           **
** 1.0.4     22-Sep-2020   TamNN1           R44-Redmine #15778                **
** 1.0.3     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Add comment for Misra-C 21.1, D4.5**
**                                          Add comment for Misra-C D4.5, 2.5 **
** 1.0.2     14-Jul-2020   DanhDC1          R44-Redmine #13533 Enable         **
**                                          OS_CHECK_IC_MESSAGE               **
**                                          for fullfill Safety implementation**
** 1.0.1     16-Dec-2019   DanhDC1          R44-Redmine #11719 Remove         **
**                                          OS_CHECK_IC_MESSAGE               **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

#ifndef OS_MULTICOREMESSAGE_H
#define OS_MULTICOREMESSAGE_H

/* @Trace: SRS_BSW_00411 */
/* Enable the checking of message handler between cores */
#define OS_CHECK_IC_MESSAGE       STD_ON
#define OS_MESSAGEQLOCKBASE       (1)

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
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
/* @Trace: SRS_BSW_00410 */
#if (OS_MULTICORE == STD_ON)

/* @Trace: SRS_BSW_00330 */
#if (OS_CHECK_IC_MESSAGE == STD_ON)
/* polyspace-begin MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */
#define OS_MC_CHECK_MSGQ_STATUS(mq,core) \
  if ((mq->fill >= OS_N_MESSAGES) || (mq->empty >= OS_N_MESSAGES)) \
  { \
    Os_ReleaseSpinlock(OS_MESSAGEQLOCKBASE+core); \
    OS_PANIC(OS_PANIC_InterCoreMessageQueueIndexInvalid); \
  } \
  if (mq->fill == mq->empty) \
  { \
    if ((mq->msgCnt != 0) && (mq->msgCnt != OS_N_MESSAGES)) \
    { \
      Os_ReleaseSpinlock(OS_MESSAGEQLOCKBASE+core); \
      OS_PANIC(OS_PANIC_InterCoreMessageQueueIndexInvalid); \
    } \
  } \
  else if (mq->fill > mq->empty) \
  { \
    if (mq->msgCnt != (mq->fill - mq->empty)) \
    { \
      Os_ReleaseSpinlock(OS_MESSAGEQLOCKBASE+core); \
      OS_PANIC(OS_PANIC_InterCoreMessageQueueIndexInvalid); \
    } \
  } \
  else \
  { \
    if (mq->msgCnt != ((OS_N_MESSAGES - mq->empty) + mq->fill)) \
    { \
      Os_ReleaseSpinlock(OS_MESSAGEQLOCKBASE+core); \
      OS_PANIC(OS_PANIC_InterCoreMessageQueueIndexInvalid); \
    } \
  }

#define OS_MC_CHECK_MSG_COUNT_OVERFLOW(mq,core) \
  if (mq->msgCnt >= (uint8)(Os_Core_Count-1)) \
  { \
    Os_ReleaseSpinlock(OS_MESSAGEQLOCKBASE+core); \
    OS_PANIC(OS_PANIC_InterCoreMessageQueueOverflow); \
  }

#define OS_MC_CHECK_MSG_INDEX(msgIdx,core) \
  if ((msgIdx >= Os_Core_Count) || (msgIdx == core)) \
  { \
    Os_ReleaseSpinlock(OS_MESSAGEQLOCKBASE+core); \
    OS_PANIC(OS_PANIC_InterCoreMessageIndexInvalid); \
  }

#define OS_MC_CHECK_MSG_STATUS1(msg) \
  if (msg->opcode >= OS_N_INTERCORE) \
  { \
    OS_PANIC(OS_PANIC_InterCoreMessageOpcodeInvalid); \
  } \
  else if ((msg->result != E_OS_SYS_INTERCOREMSG) && \
           (msg->opcode != OS_IC_ShutdownCore) && \
           (msg->opcode != OS_IC_IocPullCB) && \
           (msg->opcode != OS_IC_ErrorActivateTaskAsyn) && \
           (msg->opcode != OS_IC_ErrorSetEventAsyn)) \
  { \
    OS_PANIC(OS_PANIC_InterCoreMessageResultNotReady); \
  }\
  else\
  {\
    /* Do nothing */\
  }

#define OS_MC_CHECK_MSG_STATUS2(msg) \
  if (msg->result == E_OS_SYS_INTERCOREMSG) \
  { \
    OS_PANIC(OS_PANIC_InterCoreMessageResultNotSet); \
  }
#else
#define OS_MC_CHECK_MSGQ_STATUS(mq,coreId)
#define OS_MC_CHECK_MSG_COUNT_OVERFLOW(mq,coreId)
#define OS_MC_CHECK_MSG_INDEX(msgIdx,coreId)
#define OS_MC_CHECK_MSG_STATUS1(msg)
#define OS_MC_CHECK_MSG_STATUS2(msg)
/* polyspace-end MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */
#endif /* End of #if (OS_CHECK_IC_MESSAGE == STD_ON) */

/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "This macro is provided for UnknownCall which is not belong OS service" */
#define OS_IC_UnknownCall                  (0)
#define OS_IC_ActivateTask                 (1)
#define OS_IC_GetTaskState                 (2)
#define OS_IC_SetEvent                     (3)
#define OS_IC_GetEvent                     (4)
#define OS_IC_GetAlarm                     (5)
#define OS_IC_GetAlarmBase                 (6)
#define OS_IC_SetRelAlarm                  (7)
#define OS_IC_SetAbsAlarm                  (8)
#define OS_IC_CancelAlarm                  (9)
#define OS_IC_StartScheduleTableRel        (10)
#define OS_IC_StartScheduleTableAbs        (11)
#define OS_IC_ChainScheduleTable           (12)
#define OS_IC_StopScheduleTable            (13)
#define OS_IC_GetScheduleTableStatus       (14)
#define OS_IC_StartScheduleTableSynchron   (15)
#define OS_IC_SetScheduleTableAsync        (16)
#define OS_IC_SyncScheduleTable            (17)
#define OS_IC_TerminateApplication         (18)
#define OS_IC_GetApplicationState          (19)
#define OS_IC_ShutdownCore                 (20)
#define OS_IC_IocPullCB                    (21)
#define OS_IC_ActivateTaskAsyn             (22)
#define OS_IC_ErrorActivateTaskAsyn        (23)
#define OS_IC_SetEventAsyn                 (24)
#define OS_IC_ErrorSetEventAsyn            (25)

#define OS_N_INTERCORE                     (OS_IC_ErrorSetEventAsyn+1)

/* polyspace +1 MISRA-C3:8.11 [Justified:Low] "External linkage with array size makes error because of compiler optimization" */
extern Os_MessageQueueType Os_GaaInterCoreMsgQ[];

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* Message handlers
*/
typedef void (*Os_MessageHandler_T)(Os_MessageType *msg);

#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
extern CONST(Os_MessageHandler_T, OS_CONST) Os_GaaMessageHandler[OS_N_INTERCORE];
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, OS_CODE) Os_InitMessageQueue(void);
FUNC(StatusType, OS_CODE) Os_SendMessageWait(CoreIDType CoreID, Os_MessageType *msg);
FUNC(void, OS_CODE) Os_SendShutdownAllCores(CoreIDType CoreID, StatusType Error);
FUNC(uint16, OS_CODE) Os_SendMessage(CoreIDType CoreID, P2CONST(Os_MessageType, AUTOMATIC, OS_CONST) msg);
FUNC(void, OS_CODE) Os_ReceiveMessage(CoreIDType CoreID);

/* Individual message senders */
extern FUNC(StatusType, OS_CODE) Os_SendActivateTask(TaskType TaskID);
extern FUNC(void, OS_CODE) Os_SendAsynFuncError(CoreIDType CoreID, TaskType TaskID, \
  EventMaskType EventMask, StatusType ErrorId);
extern FUNC(void, OS_CODE) Os_SendAsynFunc(TaskType TaskID, \
    EventMaskType EventMask);

extern FUNC(StatusType, OS_CODE) Os_SendGetTaskState
  (P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) t, TaskStateRefType out);
extern FUNC(StatusType, OS_CODE) Os_SendSetEvent
  (P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) t, EventMaskType e);
extern FUNC(StatusType, OS_CODE) Os_SendGetEvent
  (TaskType TaskID, EventMaskRefType Event);

extern FUNC(StatusType, OS_CODE) Os_SendGetAlarm(AlarmType a, TickRefType out);
extern FUNC(StatusType, OS_CODE) Os_SendGetAlarmBase(AlarmType AlarmID, \
    AlarmBaseRefType Info);
extern FUNC(StatusType, OS_CODE) Os_SendSetRelAlarm
  (AlarmType a, TickType inc, TickType cyc);
extern FUNC(StatusType, OS_CODE) Os_SendSetAbsAlarm
  (AlarmType a, TickType Start, TickType cyc);
extern FUNC(StatusType, OS_CODE) Os_SendCancelAlarm(AlarmType a);

extern FUNC(StatusType, OS_CODE) Os_SendStartScheduleTableRel
  (ScheduleTableType s, TickType Offset);
extern FUNC(StatusType, OS_CODE) Os_SendStartScheduleTableAbs
  (ScheduleTableType s, TickType Start);
extern FUNC(StatusType, OS_CODE) Os_SendNextScheduleTable
  (ScheduleTableType sc, ScheduleTableType sn);
extern FUNC(StatusType, OS_CODE) Os_SendStopScheduleTable(ScheduleTableType s);
extern FUNC(StatusType, OS_CODE) Os_SendGetScheduleTableStatus
  (ScheduleTableType s, ScheduleTableStatusRefType out);
extern FUNC(StatusType, OS_CODE) Os_SendStartScheduleTableSynchron
  (ScheduleTableType s);
extern FUNC(StatusType, OS_CODE) Os_SendSetScheduleTableAsync(ScheduleTableType s);
extern FUNC(StatusType, OS_CODE) Os_SendSyncScheduleTable
  (ScheduleTableType s, TickType globalTime);

extern FUNC(StatusType, OS_CODE) Os_SendTerminateApplication
  (ApplicationType a, RestartType restart);
extern FUNC(void, OS_CODE) Os_SendGetApplicationState
  (ApplicationType Application, ApplicationStateRefType out);

extern FUNC(void, OS_CODE) Os_SendIocPullCB(
    P2FUNC(void, OS_CONST, pIocPullCB) (void), ApplicationType recvAppID);

/* Individual message handlers
 * These are responsible for handling inter-core APIs
*/
FUNC(void, OS_CODE) Os_RecvUnknownCall(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvActivateTask(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvAsynFunc(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvAsynFuncError(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvGetTaskState(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvSetEvent(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvGetEvent(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvGetAlarm(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvSetRelAlarm(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvSetAbsAlarm(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvCancelAlarm(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvStartScheduleTableRel(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvStartScheduleTableAbs(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvNextScheduleTable(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvStopScheduleTable(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvGetScheduleTableStatus(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvStartScheduleTableSynchron(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvSetScheduleTableAsync(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvSyncScheduleTable(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvTerminateApplication(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvGetApplicationState(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvShutdownCore(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvGetAlarmBase(Os_MessageType *msg);
FUNC(void, OS_CODE) Os_RecvIocPullCB(Os_MessageType *msg);

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /* #if (OS_MULTICORE == STD_ON) */

#endif /* OS_MULTICOREMESSAGE_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
