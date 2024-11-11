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
**  SRC-MODULE: Os_MulticoreSend.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Inter-core Message sending functionality.        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 SRS_Os_11012 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2097                    **
**                                          Jira CP44-2028                    **
** 1.3.12.0  09-Mar-2023   TanHX            Jira CP44-1335                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.8     13-Oct-2020   DanhDC1          R44-Redmine #16287 don't allow    **
**                                          Counter in case of cross core     **
** 1.0.7     08-Oct-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed defecet polyspace           **
** 1.0.6     07-Oct-2020   DanhDC1          R44-Redmine #15959                **
**                                          Remove un-used function           **
** 1.0.5     14-Sep-2020   TamNN1           R44-Redmine #12870                **
** 1.0.4     26-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Add Comment Misra-C 11.4          **
** 1.0.3     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Add comment for Misra-C D4.5      **
** 1.0.2     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.1     08-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed defect NON INIT VARIABLE    **
**                                          detected by bug finder polyspace  **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os RAM header file */

/* @Trace: SRS_BSW_00410 */
#if (OS_MULTICORE == STD_ON)
#include "Os_MulticoreMessage.h"

#if (OS_TASK == STD_ON)
#include "Os_Task.h"              /* Os Task header file */
#endif
#if (OS_EVENT == STD_ON)
#include "Os_Event.h"             /* Os Event header file */
#endif
#if (OS_ALARM == STD_ON)
#include "Os_Alarm.h"             /* Os Alarm header file */
#endif
#if (OS_COUNTER == STD_ON)
#include "Os_Counter.h"           /* Os Counter header file */
#endif
#if (OS_SCHEDTABLE == STD_ON)
#include "Os_SchedTable.h"        /* Os ScheduleTable header file */
#endif
#if (OS_APPLICATION == STD_ON)
#include "Os_Application.h"       /* Os Application header file */
#endif

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
/*******************************************************************************
** Function Name        : Os_SendActivateTask                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending an ActivateTask message    **
**                        and waits until message is returned.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : TaskID                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
/* @Trace: SRS_Os_80015 */
#if (OS_TASK == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendActivateTask(TaskType TaskID)
{
  /* @Trace: SafeOs_SUD_API_25901 */
  Os_MessageType msg;

  msg.opcode = OS_IC_ActivateTask;
  msg.parameter[0] = (uint32)TaskID;
  msg.parameter[1] = (uint32)OS_ZERO;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;
  /* polyspace +4 MISRA-C3:D4.14 [Justified:Low] "TaskID have been checked before using" */
  /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
  /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
  /* polyspace +1 RTE:OBAI [Not a defect:Low] "configured memory access index" */
  return Os_SendMessageWait(Os_GaaStaticTask[TaskID].ddCoreId, &msg);

}
#endif


/*******************************************************************************
** Function Name        : Os_SendAsynFunc                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending an ActivateTask message    **
**                        without waits until message is returned.            **
**                                                                            **
** Sync/Async           : ASynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : coreId - Core ID of ActivateTaskAsyn caller         **
** Input Parameters     : id - The id of the task to be activated             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessage()                                    **
*******************************************************************************/
#if (OS_TASK == STD_ON) || (OS_EVENT == STD_ON)
FUNC(void, OS_CODE) Os_SendAsynFunc(TaskType TaskID, EventMaskType EventMask)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  boolean LblIsOsICActivateTaskAsyn;
  LblIsOsICActivateTaskAsyn = OS_TRUE;

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  Os_MessageType msg;

  /* Get Core Id of caller for Asyn Function */
  msg.parameter[0] = (uint32)OS_CORE_ID;

  /* Check if the inter-core message used for ActivateTaskAsyn or not */
  if (EventMask != OS_ZERO)
  {
    LblIsOsICActivateTaskAsyn = OS_FALSE;
  }

  /* If EventMask is all zeros, this action comes from the ActivateTaskAsyn() */
  if(LblIsOsICActivateTaskAsyn == OS_TRUE)
  {
    /* @Trace: SafeOs_SUD_API_49101 */
    msg.opcode = OS_IC_ActivateTaskAsyn;
    msg.parameter[1] = (uint32)TaskID;
    msg.parameter[2] = (uint32)OS_ZERO;
    msg.parameter[3] = (uint32)OS_ZERO;
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_49102 */
    msg.opcode = OS_IC_SetEventAsyn;
    msg.parameter[1] = (uint32)TaskID;
    msg.parameter[2] = (uint32)(EventMask & 0xFFFFFFFFu);
    msg.parameter[3] = (uint32)(EventMask >> 32);
  }
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "TaskID have been checked before using Os_SendAsynFunc function" */
  (void)Os_SendMessage(Os_GaaStaticTask[TaskID].ddCoreId, &msg);

}
#endif

/*******************************************************************************
** Function Name        : Os_SendAsynFuncError                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending an Error for Asyn Function **
**                         Fupported for ActivateTaskAsyn()                   **
**                         and SetEventAsyn()                                 **
**                                                                            **
** Sync/Async           : ASynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : coreId - Core ID of ActivateTaskAsyn caller         **
** Input Parameters     : TaskId - The id of the task to be activated         **
** Input Parameters     : EventMask - The id of event for task to be          **
** Input Parameters     : ErrorId - The id of the task to be activated        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessage(), Os_MemSet()                       **
*******************************************************************************/
#if (OS_TASK == STD_ON) || (OS_EVENT == STD_ON)
FUNC(void, OS_CODE) Os_SendAsynFuncError(CoreIDType CoreID, TaskType TaskID, \
  EventMaskType EventMask, StatusType ErrorId)
{
  Os_MessageType msg;
  boolean LblIsOsICActivateTaskAsyn;
  LblIsOsICActivateTaskAsyn = OS_TRUE;

  /* Initialize all parameter(s) of the msg by ZERO */
  /* polyspace +1 MISRA-C3:10.3 [Not a defect:Low] "The message param has OS_MAXPARAM times of uint32" */
  Os_MemSet(msg.parameter, OS_ZERO, OS_MAXPARAM * sizeof(uint32));

  msg.parameter[0] = (uint32)TaskID;

  /* Check if the inter-core message used for ActivateTaskAsyn or not */
  if (EventMask != OS_ZERO)
  {
    LblIsOsICActivateTaskAsyn = OS_FALSE;
  }

  /* If EventMask is all zeros, this error comes from the ActivateTaskAsyn() */
  if(LblIsOsICActivateTaskAsyn == OS_TRUE)
  {
    /* @Trace: SafeOs_SUD_API_49201 */
    msg.opcode = OS_IC_ErrorActivateTaskAsyn;
    msg.parameter[1] = (uint32)ErrorId;
    msg.parameter[2] = (uint32)OS_ZERO;
    msg.parameter[3] = (uint32)OS_ZERO;
  }
  /* If EventMask is NOT NULL, this error comes from the SetEventAsyn() */
  else
  {
    /* @Trace: SafeOs_SUD_API_49202 */
    msg.opcode = OS_IC_ErrorSetEventAsyn;
    msg.parameter[1] = (uint32)ErrorId;
    msg.parameter[2] = (uint32)(EventMask & 0xFFFFFFFFu);
    msg.parameter[3] = (uint32)(EventMask >> 32);
  }

  (void)Os_SendMessage(CoreID, &msg);
}
#endif

/*******************************************************************************
** Function Name        : Os_SendGetTaskState                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a GetTaskState message     **
**                        and waits until message is returned.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : t                                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : out                                                 **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_TASK == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendGetTaskState
(P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) t, TaskStateRefType out)
{
  /* @Trace: SafeOs_SUD_API_26001 */
  Os_MessageType msg;
  StatusType result;

  msg.opcode = OS_IC_GetTaskState;
  msg.parameter[0] = (uint32)t->ddTaskId;
  msg.parameter[1] = (uint32)OS_ZERO;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;
  result = Os_SendMessageWait(t->ddCoreId, &msg);

  /* polyspace +4 MISRA-C3:9.1 [Justified:Low] "value msg is assigned by Os_SendMessageWait function" */
  /* polyspace +3 RTE:NIVL [Not a defect:Low] "No Impact of this rule violation" */
  /* polyspace +2 RTE:IDP [Not a defect:Low] "configured memory access index" */
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "ptr out have been checked before using" */
  *out = (TaskStateType)(msg.parameter[0]);

  return result;
}
#endif

/*******************************************************************************
** Function Name        : Os_SendSetEvent                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a SetEvent message         **
**                        and waits until message is returned.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : t, e                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
/* @Trace: SRS_Os_80016 */
#if (OS_EVENT == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendSetEvent
(P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) t, EventMaskType e)
{
  /* @Trace: SafeOs_SUD_API_26101 */
  Os_MessageType msg;

  msg.opcode = OS_IC_SetEvent;
  /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
  msg.parameter[0] = (uint32)t->ddTaskId; /* Targetted TaskID to be set events */
  msg.parameter[1] = (uint32)OS_ZERO;     /* Error code */
  msg.parameter[2] = (uint32)(e & 0xFFFFFFFFu);
  msg.parameter[3] = (uint32)(e >> 32);
  /* polyspace<RTE: NIVL : Not a defect : No Action Planned > variable is initialized and code is verified manually */
  /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
  return Os_SendMessageWait(t->ddCoreId, &msg);
}
#endif

/*******************************************************************************
** Function Name        : Os_SendGetEvent                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a GetEvent message         **
**                        and waits until message is returned.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : TaskID                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Event                                               **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_EVENT == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendGetEvent
                                       (TaskType TaskID, EventMaskRefType Event)
{
  /* @Trace: SafeOs_SUD_API_26201 */
  Os_MessageType msg;

  msg.opcode = OS_IC_GetEvent;
  msg.parameter[0] = (uint32)TaskID;
  /* polyspace +1 MISRA-C3:11.4 [Justified:Medium] "Conversion is needed for implementation" */
  msg.parameter[1] = (uint32)Event;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;

  return Os_SendMessageWait(Os_GaaStaticTask[TaskID].ddCoreId, &msg);
}
#endif

/*******************************************************************************
** Function Name        : Os_SendGetAlarm                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a GetAlarm message         **
**                        and waits until message is returned.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : a                                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : out                                                 **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_ALARM == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendGetAlarm(AlarmType a, TickRefType out)
{
  /* @Trace: SafeOs_SUD_API_26301 */
  Os_MessageType msg;

  msg.opcode = OS_IC_GetAlarm;
  msg.parameter[0] = (uint32)a;
  /* polyspace +1 MISRA-C3:11.4 [Justified:Medium] "Conversion is needed for implementation" */
  msg.parameter[1] = (uint32)out;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] " a index have been checked before using Os_SendGetAlarm function" */
  return Os_SendMessageWait(Os_GaaStaticAlarm[a].ddCoreID, &msg);
}
#endif

/*******************************************************************************
** Function Name        : Os_SendGetAlarmBase                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a GetAlarmBase message     **
**                        and waits until message is returned.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : a                                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : out                                                 **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_ALARM == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendGetAlarmBase(AlarmType AlarmID, \
                                                          AlarmBaseRefType Info)
{
  /* @Trace: SafeOs_SUD_API_26401 */
  Os_MessageType msg;
  StatusType result;

  msg.opcode = OS_IC_GetAlarmBase;
  msg.parameter[0] = (uint32)AlarmID;
  /* polyspace +1 MISRA-C3:11.4 [Justified:Medium] "Conversion is needed for implementation" */
  msg.parameter[1] = (uint32)Info;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;
  result = Os_SendMessageWait(Os_GaaStaticAlarm[AlarmID].ddCoreID, &msg);
  return result;
}
#endif

/*******************************************************************************
** Function Name        : Os_SendSetRelAlarm                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a SetRelAlarm message      **
**                        and waits until message is returned.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : a, inc, cyc                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_ALARM == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendSetRelAlarm(AlarmType a, TickType inc,
                                                                   TickType cyc)
{
  /* @Trace: SafeOs_SUD_API_26501 */
  Os_MessageType msg;

  msg.opcode = OS_IC_SetRelAlarm;
  msg.parameter[0] = (uint32)a;
  msg.parameter[1] = (uint32)inc;
  msg.parameter[2] = (uint32)cyc;
  msg.parameter[3] = (uint32)OS_ZERO;
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "a index have been checked before using" */
  return Os_SendMessageWait(Os_GaaStaticAlarm[a].ddCoreID, &msg);

}
#endif

/*******************************************************************************
** Function Name        : Os_SendSetAbsAlarm                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a SetAbsAlarm message      **
**                        and waits until message is returned.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : a, start, cyc                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_ALARM == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendSetAbsAlarm(AlarmType a, TickType Start,
                                                                   TickType cyc)
{
  /* @Trace: SafeOs_SUD_API_26601 */
  Os_MessageType msg;

  msg.opcode = OS_IC_SetAbsAlarm;
  msg.parameter[0] = (uint32)a;
  msg.parameter[1] = (uint32)Start;
  msg.parameter[2] = (uint32)cyc;
  msg.parameter[3] = (uint32)OS_ZERO;
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "a index have been checked before using" */
  return Os_SendMessageWait(Os_GaaStaticAlarm[a].ddCoreID, &msg);

}
#endif

/*******************************************************************************
** Function Name        : Os_SendCancelAlarm                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a CancelAlarm message      **
**                        and waits until message is returned.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : a                                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_ALARM == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendCancelAlarm(AlarmType a)
{
  /* @Trace: SafeOs_SUD_API_26701 */
  Os_MessageType msg;

  msg.opcode = OS_IC_CancelAlarm;
  msg.parameter[0] = (uint32)a;
  msg.parameter[1] = (uint32)OS_ZERO;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;

  return Os_SendMessageWait(Os_GaaStaticAlarm[a].ddCoreID, &msg);
}
#endif

/*******************************************************************************
** Function Name        : Os_SendStartScheduleTableRel                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a StartScheduleTable       **
**                        message and waits until message is returned.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : s, offset, rel                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendStartScheduleTableRel(ScheduleTableType s,
                                                   TickType Offset)
{
  /* @Trace: SafeOs_SUD_API_27001 */
  Os_MessageType msg;

  msg.opcode = OS_IC_StartScheduleTableRel;
  msg.parameter[0] = (uint32)s;
  msg.parameter[1] = (uint32)Offset;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;

  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "s have been checked before using" */
  return Os_SendMessageWait(Os_GaaStaticSchedTable[s].ddCoreID, &msg);

}
#endif

/*******************************************************************************
** Function Name        : Os_SendStartScheduleTableAbs                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a StartScheduleTable       **
**                        message and waits until message is returned.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : s, start, rel                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendStartScheduleTableAbs(ScheduleTableType s,
                                                   TickType Start)
{
  /* @Trace: SafeOs_SUD_API_27101 */
  Os_MessageType msg;

  msg.opcode = OS_IC_StartScheduleTableAbs;
  msg.parameter[0] = (uint32)s;
  msg.parameter[1] = (uint32)Start;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;

  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "s have been checked before using" */
  return Os_SendMessageWait(Os_GaaStaticSchedTable[s].ddCoreID, &msg);

}
#endif


/*******************************************************************************
** Function Name        : Os_SendNextScheduleTable                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a NextScheduleTable        **
**                        message and waits until message is returned.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : sc, sn                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendNextScheduleTable
(
  ScheduleTableType sc,   /* Currently-running schedule table */
  ScheduleTableType sn    /* Schedule table to chain */
)
{
  /* @Trace: SafeOs_SUD_API_27201 */
  Os_MessageType msg;

  msg.opcode = OS_IC_ChainScheduleTable;
  msg.parameter[0] = (uint32)sc;
  msg.parameter[1] = (uint32)sn;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;

  return Os_SendMessageWait(Os_GaaStaticSchedTable[sc].ddCoreID, &msg);
}
#endif

/*******************************************************************************
** Function Name        : Os_SendStopScheduleTable                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a StopScheduleTable        **
**                        message and waits until message is returned.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : s                                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendStopScheduleTable(ScheduleTableType s)
{
  /* @Trace: SafeOs_SUD_API_27301 */
  Os_MessageType msg;

  msg.opcode = OS_IC_StopScheduleTable;
  msg.parameter[0] = (uint32)s;
  msg.parameter[1] = (uint32)OS_ZERO;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;

  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "s have been checked before using" */
  return Os_SendMessageWait(Os_GaaStaticSchedTable[s].ddCoreID, &msg);

}
#endif

/*******************************************************************************
** Function Name        : Os_SendGetScheduleTableStatus                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a GetScheduleTableStatus   **
**                        message and waits until message is returned.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : s                                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : out                                                 **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_SendGetScheduleTableStatus(ScheduleTableType s,
                                                 ScheduleTableStatusRefType out)
{
  /* @Trace: SafeOs_SUD_API_27401 */
  Os_MessageType msg;
  StatusType result;

  msg.opcode = OS_IC_GetScheduleTableStatus;
  msg.parameter[0] = (uint32)s;
/* polyspace +1 MISRA-C3:11.4 [Justified:Low] " To contain variable generally, msg.parameter[] uses uint32 type" */
  msg.parameter[1] = (uint32)out;

  msg.parameter[2] = (uint32)OS_ZERO;

  msg.parameter[3] = (uint32)OS_ZERO;

  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "s have been checked before using" */
  result = Os_SendMessageWait(Os_GaaStaticSchedTable[s].ddCoreID, &msg);

  return result;
}
#endif

/*******************************************************************************
** Function Name        : Os_SendStartScheduleTableSynchron                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending                            **
**                        a StartScheduleTableSynchron message and waits      **
**                        until message is returned.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : s                                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if ((OS_SCHEDTABLE == STD_ON) && (OS_SCHED_EXPLICIT_SYNC == STD_ON))
FUNC(StatusType, OS_CODE) Os_SendStartScheduleTableSynchron(ScheduleTableType s)
{
  /* @Trace: SafeOs_SUD_API_27501 */
  Os_MessageType msg;

  msg.opcode = OS_IC_StartScheduleTableSynchron;
  msg.parameter[0] = (uint32)s;
  msg.parameter[1] = (uint32)OS_ZERO;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "s have been checked before using" */
  return Os_SendMessageWait(Os_GaaStaticSchedTable[s].ddCoreID, &msg);

}
#endif

/*******************************************************************************
** Function Name        : Os_SendSetScheduleTableAsync                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a SetScheduleTableAsync    **
**                        message and waits until message is returned.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : s                                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if ((OS_SCHEDTABLE == STD_ON) && (OS_SCHED_EXPLICIT_SYNC == STD_ON))
FUNC(StatusType, OS_CODE) Os_SendSetScheduleTableAsync(ScheduleTableType s)
{
  /* @Trace: SafeOs_SUD_API_27601 */
  Os_MessageType msg;

  msg.opcode = OS_IC_SetScheduleTableAsync;
  msg.parameter[0] = (uint32)s;
  msg.parameter[1] = (uint32)OS_ZERO;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "s have been checked before using" */
  return Os_SendMessageWait(Os_GaaStaticSchedTable[s].ddCoreID, &msg);

}
#endif

/*******************************************************************************
** Function Name        : Os_SendSyncScheduleTable                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a SyncScheduleTable        **
**                        message and waits until message is returned.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : s, globalTime                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if ((OS_SCHEDTABLE == STD_ON) && (OS_SCHED_EXPLICIT_SYNC == STD_ON))
FUNC(StatusType, OS_CODE) Os_SendSyncScheduleTable(ScheduleTableType s,
                                                            TickType globalTime)
{
  /* @Trace: SafeOs_SUD_API_27701 */
  Os_MessageType msg;

  msg.opcode = OS_IC_SyncScheduleTable;
  msg.parameter[0] = (uint32)s;
  msg.parameter[1] = (uint32)globalTime;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "s have been checked before using" */
  return Os_SendMessageWait(Os_GaaStaticSchedTable[s].ddCoreID, &msg);

}
#endif

/*******************************************************************************
** Function Name        : Os_SendTerminateApplication                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a TerminateApplication     **
**                        message and waits until message is returned.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : a, restart                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticApplication                             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_SCALABILITY_CLASS >= OS_SC3)
FUNC(StatusType, OS_CODE) Os_SendTerminateApplication(ApplicationType a,
                                                            RestartType restart)
{
  /* @Trace: SafeOs_SUD_API_27801 */
  Os_MessageType msg;

  msg.opcode = OS_IC_TerminateApplication;
  msg.parameter[0] = (uint32)a;
  msg.parameter[1] = (uint32)restart;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "a index have been checked before using" */
  return Os_SendMessageWait(Os_GaaStaticApplication[a].ddCoreID, &msg);
}
#endif

/*******************************************************************************
** Function Name        : Os_SendGetApplicationState                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a GetApplicationState      **
**                        message and waits until message is returned.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : a                                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : out                                                 **
**                                                                            **
** Return parameter     : none                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessageWait()                                **
*******************************************************************************/
#if (OS_SCALABILITY_CLASS >= OS_SC3)
FUNC(void, OS_CODE) Os_SendGetApplicationState(ApplicationType Application,
                                                    ApplicationStateRefType out)
{
  /* @Trace: SafeOs_SUD_API_27901 */
  Os_MessageType msg;

  msg.opcode = OS_IC_GetApplicationState;
  msg.parameter[0] = (uint32)Application;
  /* polyspace +1 MISRA-C3:11.4 [Justified:Medium] "Conversion is needed for implementation" */
  msg.parameter[1] = (uint32)out;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;

  (void)Os_SendMessageWait(Os_GaaStaticApplication[Application].ddCoreID, &msg);

}
#endif

/*******************************************************************************
** Function Name        : Os_SendShutdownAllCores                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function sends a shutdown message              **
**                        to other cores.                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : coreId, Error                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessage()                                    **
*******************************************************************************/
FUNC(void, OS_CODE) Os_SendShutdownAllCores(CoreIDType CoreID, StatusType Error)
{
  /* @Trace: SafeOs_SUD_API_28001 */
  Os_MessageType msg;

  msg.opcode = OS_IC_ShutdownCore;
  msg.result = 0;
  msg.parameter[0] = Error;
  msg.parameter[1] = (uint32)OS_ZERO;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;

 /* polyspace RTE:NTC [Not a defect:Low] "It waits other cores response." */
  (void)Os_SendMessage(CoreID, &msg);
}

/*******************************************************************************
** Function Name        : Os_SendIocPullCB                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a IocPullCB                **
**                        message and waits until message is returned.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : pIocPullCB, recvAppID                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessage()                                    **
*******************************************************************************/
#if (OS_APPLICATION == STD_ON)
FUNC(void, OS_CODE) Os_SendIocPullCB(P2FUNC(void, OS_CONST, pIocPullCB) (void),
    ApplicationType recvAppID)
{
  /* @Trace: SafeOs_SUD_API_20001 */
  Os_MessageType msg;

  msg.opcode = OS_IC_IocPullCB;
  /* polyspace<MISRA-C:11.3:Not a defect:Justify with annotations> For implementation, conversion from function pointer to void pointer is needed to represent function address */
  msg.parameter[0] = (uint32)pIocPullCB;
  msg.parameter[1] = (uint32)recvAppID;
  msg.parameter[2] = (uint32)OS_ZERO;
  msg.parameter[3] = (uint32)OS_ZERO;

  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "recvAppID have been checked before using" */
  /* polyspace RTE:NTC [Not a defect:Low] "It waits other cores response." */
  (void)Os_SendMessage(Os_GaaStaticApplication[recvAppID].ddCoreID, &msg);

}
#endif


#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /* End of #if (OS_MULTICORE == STD_ON) */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
