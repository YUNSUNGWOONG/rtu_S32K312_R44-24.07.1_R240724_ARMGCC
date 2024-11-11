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
**  SRC-MODULE: Os_MulticoreReceive.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Inter-core Message receiving functionality.      **
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
** 1.0.4     13-Oct-2020   DanhDC1          R44-Redmine #16287 don't allow    **
**                                          Counter in case of cross core     **
** 1.0.3     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
** 1.0.2     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C 15.7, 12.1          **
**                                          Add comment for Misra-C D4.5      **
** 1.0.1     14-Jul-2020   DanhDC1          R44-Redmine #13533 Update the     **
**                                          result of message in MC-Message   **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually." */
/* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-begin MISRA-C3:11.4 [Not a defect:Justify with annotations] "Conversion is needed for implementation" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace-begin MISRA-C3:11.1 [Not a defect:Low] "Conversion is needed for implementation" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */

/* @Trace: SRS_BSW_00410 */
#if (OS_MULTICORE == STD_ON)

#include "Os_MulticoreMessage.h"
#include "Os_Shutdown.h"          /* Os Shutdown header file */
#include "Os_Error.h"             /* Os Error header file */

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
#include "Os_Ioc.h"               /* Os IOC Pull CB header file */
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
** Function Name        : Os_RecvUnknownCall                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is an UnknownCall message handler.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
FUNC(void, OS_CODE) Os_RecvUnknownCall(Os_MessageType *msg)
{
  /* @Trace: SafeOs_SUD_API_23501 */
  msg->result = E_OS_NOFUNC;
}

/*******************************************************************************
** Function Name        : Os_RecvActivateTask                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is an ActivateTask message handler.   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_DoActivateTask()                                 **
*******************************************************************************/
#if (OS_TASK == STD_ON)
FUNC(void, OS_CODE) Os_RecvActivateTask(Os_MessageType *msg)
{
  /* @Trace: SafeOs_SUD_API_23601 */
  /* Do the task activation and put the result code in the message
  */
  msg->result = Os_DoActivateTask((TaskType)msg->parameter[0], OS_TRUE);
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvAsynFuncError                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is an Asyn Function Error             **
**                          message handler                                   **
**                                                                            **
** Sync/Async           : ASynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : msg - Across-Core Message Stucture                  **
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
**                        None                                                **
*******************************************************************************/
#if (OS_TASK == STD_ON) || ((OS_EVENT == STD_ON) && (OS_STATUS == EXTENDED))
/* polyspace +1 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace" */
FUNC(void, OS_CODE) Os_RecvAsynFuncError(Os_MessageType *msg)
{
  #if (OS_ERROR_HOOK == STD_ON)
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  #endif

  #if ((OS_ERROR_HOOK == STD_ON) || (OS_APP_ERROR_HOOK == STD_ON))
  StatusType ErrorId;
  /* @Trace: SafeOs_SUD_API_48801 */
  ErrorId = E_OK;
  #endif

  /* Set the return status value to "E_OK" */
  if (msg->opcode == OS_IC_ErrorActivateTaskAsyn)
  {
    /* @Trace: SafeOs_SUD_API_48802 */
    /* polyspace +2 RTE:OBAI [Not a defect:Low] "The input value have checked before using" */
    /* Store the service ID of ActivateTaskAsyn */
    OS_STORE_SERVICE(OSServiceId_ActivateTaskAsyn);
    /* Store the parameter 1 - id */
    OS_STORE_PARAM1_TASKID((TaskType)msg->parameter[0]);
    #if ((OS_ERROR_HOOK == STD_ON) || (OS_APP_ERROR_HOOK == STD_ON))
    /* Got an error to report error hook */
    ErrorId = (StatusType)msg->parameter[1];
    #endif
  }
  else if (msg->opcode == OS_IC_ErrorSetEventAsyn)
  {
    /* @Trace: SafeOs_SUD_API_48803 */
    /* polyspace +2 RTE:OBAI [Not a defect:Low] "The input value have checked before using" */
    /* Store the service ID of SetEvent */
    OS_STORE_SERVICE(OSServiceId_SetEventAsyn);
    /* Store the parameter 1 - TaskID */
    OS_STORE_PARAM1_TASKID((TaskType)msg->parameter[0]);
    /* Store the parameter 2 - Mask */
    OS_STORE_PARAM2_MASK(((EventMaskType)(msg->parameter[2])) | (((EventMaskType)(msg->parameter[3])) << 32));

    #if ((OS_ERROR_HOOK == STD_ON) || (OS_APP_ERROR_HOOK == STD_ON))
    /* Got an error to report error hook */
    ErrorId = (StatusType)msg->parameter[1];
    #endif
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_48804 */
    /* Do nothing */
  }
  #if ((OS_ERROR_HOOK == STD_ON) || (OS_APP_ERROR_HOOK == STD_ON))
  /* Report an error to error hook */
  OS_PROCESS_ERROR(ErrorId);
  #endif
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvAsynFunc                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is an Asyn Function message handler   **
**                                                                            **
** Sync/Async           : ASynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : msg - Across-Core Message Stucture                  **
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
**                        Os_DoActivateTask(),                                **
**                        Os_DoSetEvent(),                                    **
**                        Os_SendAsynFuncError()                              **
*******************************************************************************/
#if (OS_TASK == STD_ON) || (OS_EVENT == STD_ON)
FUNC(void, OS_CODE) Os_RecvAsynFunc(Os_MessageType *msg)
{
  /* Set the result code of message to E_OK */
  msg->result = E_OK;
  /* @Trace: SafeOs_SUD_API_48901 */
  #if (OS_TASK == STD_ON)
  /* Check the parameter for IC Message Operation Code */
  if (msg->opcode == OS_IC_ActivateTaskAsyn)
  {
    /* @Trace: SafeOs_SUD_API_48902 */
    /* Do the task activation and put the result code in the message */
    msg->result = Os_DoActivateTask((TaskType)msg->parameter[1], OS_TRUE);
  }
  #endif
  #if (OS_EVENT == STD_ON)
  else if (msg->opcode == OS_IC_SetEventAsyn)
  {
    /* @Trace: SafeOs_SUD_API_48903 */
    /* Do the event-setting and put the result code in the message */
    msg->result = Os_DoSetEvent((TaskType)(msg->parameter[1]), \
      (((EventMaskType)(msg->parameter[2])) | (((EventMaskType)(msg->parameter[3])) << 32)), OS_FALSE);
  }
  #endif /* End of #if (OS_EVENT == STD_ON) */
  else
  {

  }

  #if (OS_STATUS == EXTENDED)
  if (msg->result != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_48904 */
    Os_SendAsynFuncError((CoreIdType)msg->parameter[0], \
      (TaskType)(msg->parameter[1]), (((EventMaskType)(msg->parameter[2])) | (((EventMaskType)(msg->parameter[3])) << 32)), \
      (StatusType)msg->result);
  }
  #endif /* End of if (OS_STATUS == EXTENDED) */
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvGetTaskState                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a GetTaskState message handler.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaTask                                          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if (OS_TASK == STD_ON)
FUNC(void, OS_CODE) Os_RecvGetTaskState(Os_MessageType *msg)
{
  TaskType task;
  TaskStateType State;
  /* @Trace: SafeOs_SUD_API_23701 */
  /* Get the task state */
  task = (TaskType)msg->parameter[0];
  /* polyspace +1 RTE:OBAI [Not a defect:Low] "configured array index and message is checked by sender" */
  State = ((Os_GaaTask[task].ddState) & OS_TASK_STATUS);
  if (State == OS_TASK_UNINITIALIZED)
  {
    /* @Trace: SafeOs_SUD_API_23702 */
    State = SUSPENDED;
  }
  msg->parameter[0] = State;
  msg->result = E_OK;
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvSetEvent                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a SetEvent message handler.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_DoSetEvent()                                     **
*******************************************************************************/
#if (OS_EVENT == STD_ON)
FUNC(void, OS_CODE) Os_RecvSetEvent(Os_MessageType *msg)
{
  /* Do the event-setting and put the result code in the message
  */
  /* @Trace: SafeOs_SUD_API_23801 */
  msg->result = Os_DoSetEvent((TaskType)msg->parameter[0], \
                (EventMaskType)(msg->parameter[2]) | (((EventMaskType)(msg->parameter[3])) << 32), OS_TRUE);
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvGetEvent                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a GetEvent message handler.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticTask                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_DoGetEvent()                                     **
*******************************************************************************/
#if (OS_EVENT == STD_ON)
FUNC(void, OS_CODE) Os_RecvGetEvent(Os_MessageType *msg)
{
  /* Get the event and get the result code
  */
  /* polyspace-begin CERT-C:INT36-C 
  [Justified:Low] "This conversion cannot be modified to handle memory" */
  /* @Trace: SafeOs_SUD_API_23901 */
  msg->result = Os_DoGetEvent((TaskType)msg->parameter[0], \
                                           (EventMaskRefType)msg->parameter[1]);
  /* polyspace-end CERT-C:INT36-C 
  [Justified:Low] "This conversion cannot be modified to handle memory" */                                          
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvGetAlarm                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a GetAlarm message handler.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoGetAlarm()                                     **
*******************************************************************************/
#if (OS_ALARM == STD_ON)
FUNC(void, OS_CODE) Os_RecvGetAlarm(Os_MessageType *msg)
{
  /* Get the alarm delta and put the result code in the message
   */
  /* polyspace-begin CERT-C:INT36-C 
  [Justified:Low] "This conversion cannot be modified to handle memory" */
  /* @Trace: SafeOs_SUD_API_24001 */
  msg->result = Os_DoGetAlarm((AlarmType)msg->parameter[0], \
                                       (TickRefType)msg->parameter[1], OS_TRUE);
  /* polyspace-end CERT-C:INT36-C 
  [Justified:Low] "This conversion cannot be modified to handle memory" */                                     
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvGetAlarmBase                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a GetAlarmBase message handler.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoGetAlarmBase()                                 **
*******************************************************************************/
#if (OS_ALARM == STD_ON)
FUNC(void, OS_CODE) Os_RecvGetAlarmBase(Os_MessageType *msg)
{
  /* Get the alarm delta and put the result code in the message
   */
  /* polyspace-begin CERT-C:INT36-C 
  [Justified:Low] "This conversion cannot be modified to handle memory" */
  /* @Trace: SafeOs_SUD_API_24101 */
  msg->result = Os_DoGetAlarmBase((AlarmType)msg->parameter[0], \
                                  (AlarmBaseRefType)msg->parameter[1], OS_TRUE);
  /* polyspace-end CERT-C:INT36-C 
  [Justified:Low] "This conversion cannot be modified to handle memory" */                                
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvSetRelAlarm                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a SetRelAlarm message handler.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoSetRelAlarm()                                  **
*******************************************************************************/
#if (OS_ALARM == STD_ON)
FUNC(void, OS_CODE) Os_RecvSetRelAlarm(Os_MessageType *msg)
{
  /* Set an alarm at a relative time and put the result code in the message
   */
  /* @Trace: SafeOs_SUD_API_24201 */
  msg->result = Os_DoSetRelAlarm((AlarmType)msg->parameter[0], \
             (TickType)msg->parameter[1], (TickType)msg->parameter[2], OS_TRUE);
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvSetAbsAlarm                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a SetAbsAlarm message handler.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoSetAbsAlarm()                                  **
*******************************************************************************/
#if (OS_ALARM == STD_ON)
FUNC(void, OS_CODE) Os_RecvSetAbsAlarm(Os_MessageType *msg)
{
  /* Set an alarm at a absolute time and put the result code in the message
   */
  /* @Trace: SafeOs_SUD_API_24301 */
  msg->result = Os_DoSetAbsAlarm((AlarmType)msg->parameter[0], \
             (TickType)msg->parameter[1], (TickType)msg->parameter[2], OS_TRUE);
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvCancelAlarm                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a CancelAlarm message handler.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoCancelAlarm()                                  **
*******************************************************************************/
#if (OS_ALARM == STD_ON)
FUNC(void, OS_CODE) Os_RecvCancelAlarm(Os_MessageType *msg)
{
  /* Cancel the alarm and put the result code in the message
   */
  /* @Trace: SafeOs_SUD_API_24401 */
  msg->result = Os_DoCancelAlarm((AlarmType)msg->parameter[0], OS_TRUE);
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvStartScheduleTableAbs                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a StartScheduleTableAbs message    **
**                        handler.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoStartScheduleTableAbs()                        **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(void, OS_CODE) Os_RecvStartScheduleTableAbs(Os_MessageType *msg)
{
  /* Start a schedule table at a relative or absolute time
   * and put the result code in the message
   */
  /* @Trace: SafeOs_SUD_API_24801 */
  msg->result = Os_DoStartScheduleTableAbs((ScheduleTableType)msg->parameter[0],
                                          (TickType)msg->parameter[1], OS_TRUE);
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvStartScheduleTableRel                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a StartScheduleTableRel message    **
**                        handler.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoStartScheduleTableRel()                           **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(void, OS_CODE) Os_RecvStartScheduleTableRel(Os_MessageType *msg)
{
  /* Start a schedule table at a relative or absolute time
   * and put the result code in the message
   */
  /* @Trace: SafeOs_SUD_API_24701 */
  msg->result = Os_DoStartScheduleTableRel((ScheduleTableType)msg->parameter[0],
                                          (TickType)msg->parameter[1], OS_TRUE);
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvNextScheduleTable                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a NextScheduleTable message        **
**                        handler.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoNextScheduleTable()                            **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(void, OS_CODE) Os_RecvNextScheduleTable(Os_MessageType *msg)
{
  /* Chain a schedule table to an already-active schedule table
   */
  /* @Trace: SafeOs_SUD_API_24901 */
  msg->result = Os_DoNextScheduleTable((ScheduleTableType)msg->parameter[0],\
                (ScheduleTableType)msg->parameter[1], OS_TRUE);
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvStopScheduleTable                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a StopScheduleTable message        **
**                        handler.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoStopScheduleTable()                            **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(void, OS_CODE) Os_RecvStopScheduleTable(Os_MessageType *msg)
{
  /* Stop a schedule table immediately
   * and put the result code in in the message
   */
  /* @Trace: SafeOs_SUD_API_25001 */
  msg->result = Os_DoStopScheduleTable((ScheduleTableType)msg->parameter[0],\
                OS_TRUE);
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvGetScheduleTableStatus                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a GetScheduleTableStatus message   **
**                        handler.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        None                                                **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(void, OS_CODE) Os_RecvGetScheduleTableStatus(Os_MessageType *msg)
{
  /* Get the schedule table status */
  /* polyspace-begin CERT-C:INT36-C 
  [Justified:Low] "This conversion cannot be modified to handle memory" */ 
  /* @Trace: SafeOs_SUD_API_25101 */
  msg->result = Os_DoGetScheduleTableStatus(
                        (ScheduleTableType)msg->parameter[0],\
                        (ScheduleTableStatusRefType)msg->parameter[1], OS_TRUE);
  /* polyspace-end CERT-C:INT36-C 
  [Justified:Low] "This conversion cannot be modified to handle memory" */ 
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvStartScheduleTableSynchron                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a StartScheduleTableSynchron       **
**                        message handler.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoStartScheduleTableSynchron()                   **
*******************************************************************************/
#if ((OS_SCHEDTABLE == STD_ON) && (OS_SCHED_EXPLICIT_SYNC == STD_ON))
FUNC(void, OS_CODE) Os_RecvStartScheduleTableSynchron(Os_MessageType *msg)
{
  /* Start a schedule table at a relative or absolute time
   * and put the result code in the message
   */
  /* @Trace: SafeOs_SUD_API_25201 */
  msg->result = Os_DoStartScheduleTableSynchron(
                                 (ScheduleTableType)msg->parameter[0], OS_TRUE);
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvSetScheduleTableAsync                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a SetScheduleTableAsync message    **
**                        handler.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoSetScheduleTableAsync()                        **
*******************************************************************************/
#if ((OS_SCHEDTABLE == STD_ON) && (OS_SCHED_EXPLICIT_SYNC == STD_ON))
FUNC(void, OS_CODE) Os_RecvSetScheduleTableAsync(Os_MessageType *msg)
{
  /* Set a schedule table to the aysynchronous state
   * and put the result code in the message
   */
  /* @Trace: SafeOs_SUD_API_25301 */
  msg->result = Os_DoSetScheduleTableAsync((ScheduleTableType)msg->parameter[0],
                                                                       OS_TRUE);
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvSyncScheduleTable                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a SyncScheduleTable message        **
**                        handler.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoSyncScheduleTable()                            **
*******************************************************************************/
#if ((OS_SCHEDTABLE == STD_ON) && (OS_SCHED_EXPLICIT_SYNC == STD_ON))
FUNC(void, OS_CODE) Os_RecvSyncScheduleTable(Os_MessageType *msg)
{
  /* Synchronise a schedule table to the given global time
   * and put the result code in the message
   */
  /* @Trace: SafeOs_SUD_API_25401 */
  msg->result = Os_DoSyncScheduleTable((ScheduleTableType)msg->parameter[0],\
                (TickType)msg->parameter[1], OS_TRUE);
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvTerminateApplication                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a TerminateApplication message     **
**                        handler.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoTerminateApplication()                         **
*******************************************************************************/
#if (OS_SCALABILITY_CLASS >= OS_SC3)
FUNC(void, OS_CODE) Os_RecvTerminateApplication(Os_MessageType *msg)
{
  /* Do the task activation and put the result code in the message
   */
  /* @Trace: SafeOs_SUD_API_25501 */
  msg->result = Os_DoTerminateApplication((ApplicationType)msg->parameter[0],\
                                                (RestartType)msg->parameter[1]);
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvGetApplicationState                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a GetApplicationState message      **
**                        handler.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        None                                                **
*******************************************************************************/
#if (OS_SCALABILITY_CLASS >= OS_SC3)
FUNC(void, OS_CODE) Os_RecvGetApplicationState(Os_MessageType *msg)
{
  /* @Trace: SafeOs_SUD_API_25601 */
  /* polyspace-begin CERT-C:INT36-C 
  [Justified:Low] "This conversion cannot be modified to handle memory" */ 
  Os_DoGetApplicationState((ApplicationType)msg->parameter[0],
      (ApplicationStateRefType)msg->parameter[1]);
  msg->result = E_OK;
  /* polyspace-end CERT-C:INT36-C 
  [Justified:Low] "This conversion cannot be modified to handle memory" */ 
}
#endif

/*******************************************************************************
** Function Name        : Os_RecvShutdownCore                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a ShutdownCore message handler.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_ReleaseSpinlock(), Os_ShutdownCore()             **
*******************************************************************************/
/* polyspace +1 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace" */
FUNC(void, OS_CODE) Os_RecvShutdownCore(Os_MessageType *msg)
{
  /* Call Os_ShutdownCore */
  /* @Trace: SafeOs_SUD_API_25701 */
  #if (OS_MULTICORE == STD_ON)
  Os_ReleaseSpinlock(OS_MESSAGEQLOCKBASE+Os_MyCore());
  #endif
  Os_ShutdownCore((StatusType)msg->parameter[0], OS_SHUTDOWN_SYNCHRONIZED);
}
/*******************************************************************************
** Function Name        : Os_RecvIocPullCB                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is a IocPullCB message handler        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : msg                                                 **
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
**                        Os_DoIocPullCB()                                    **
*******************************************************************************/
#if (OS_APPLICATION == STD_ON)
FUNC(void, OS_CODE) Os_RecvIocPullCB(Os_MessageType *msg)
{
  /* @Trace: SafeOs_SUD_API_25801 */
  /* polyspace-begin CERT-C:INT36-C 
  [Justified:Low] "This conversion cannot be modified to handle memory" */ 
  Os_DoIocPullCB((void (*)(void))msg->parameter[0],
                                            (ApplicationType)msg->parameter[1]);

  /* polyspace-end CERT-C:INT36-C 
  [Justified:Low] "This conversion cannot be modified to handle memory" */ 
  /* Set E_OK to the result code in the message */
  msg->result = E_OK;
}
#endif


#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /* End of #if (OS_MULTICORE == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:11.1 [Not a defect:Low] "Conversion is needed for implementation" */
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace-end RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually." */
/* polyspace-end RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-end MISRA-C3:11.4 [Not a defect:Justify with annotations] "Conversion is needed for implementation" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
