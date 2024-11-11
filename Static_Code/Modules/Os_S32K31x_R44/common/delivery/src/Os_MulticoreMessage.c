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
**  SRC-MODULE: Os_MulticoreMessage.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Inter-core Message functionality                 **
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
** 1.5.3     16-Feb-2024   HG.Kim           Jira CP44-3828                    **
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2097                    **
**                                          Jira CP44-2006                    **
** 1.3.12.0  09-Mar-2023   TanHX            Jira CP44-1335                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.2.0     17-Jun-2021   Thao             Redmine #18697                    **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.7     13-Oct-2020   DanhDC1          R44-Redmine #16287 don't allow    **
**                                          Counter in case of cross core     **
** 1.0.6     07-Oct-2020   DanhDC1          R44-Redmine #15959                **
**                                          Remove un-used function           **
** 1.0.5     07-Oct-2020   DanhDC1          R44-Redmine #16251 Support the    **
**                                          parameter 4 in multicore system   **
** 1.0.4     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
** 1.0.3     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C 15.7 10.7, 20.7,8.2 **
**                                          Add comment for Misra-C D4.5      **
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
/* polyspace-begin RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually." */
/* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-begin MISRA-C3:20.4 [Justified:Low] "Definition for function redirection does not use parenthesised expression" */
/* polyspace-begin RTE:NTC [Not a defect:Low] "Os_Panic invoked Shutdown with infinite loop is intended instruction." */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/* polyspace-begin CERT-C:PRE00-C [Not a defect:Low] "Function like macro is used to improve performance" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os RAM header file */

/* @Trace: SRS_BSW_00410 */
#if (OS_MULTICORE == STD_ON)
#include "Os_MulticoreMessage.h"
#include "Os_Panic.h"             /* Os Panic header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (OS_TASK == STD_ON)
#define OS_XC_RECVACTIVATETASK                 Os_RecvActivateTask
#define OS_XC_RECVACTIVATETASKASYN             Os_RecvAsynFunc
#define OS_XC_RECVERRORACTIVATETASKASYN        Os_RecvAsynFuncError
#define OS_XC_RECVGETTASKSTATE                 Os_RecvGetTaskState
#endif
#if (OS_EVENT == STD_ON)
#define OS_XC_RECVSETEVENT                     Os_RecvSetEvent
#define OS_XC_RECVSETEVENTASYN                 Os_RecvAsynFunc
#define OS_XC_RECVERRORSETEVENTASYN            Os_RecvAsynFuncError
#define OS_XC_RECVGETEVENT                     Os_RecvGetEvent
#endif
#if (OS_ALARM == STD_ON)
#define OS_XC_RECVGETALARM                     Os_RecvGetAlarm
#define OS_XC_RECVGETALARMBASE                 Os_RecvGetAlarmBase
#define OS_XC_RECVSETRELALARM                  Os_RecvSetRelAlarm
#define OS_XC_RECVSETABSALARM                  Os_RecvSetAbsAlarm
#define OS_XC_RECVCANCELALARM                  Os_RecvCancelAlarm
#endif

#if (OS_SCHEDTABLE == STD_ON)
#define OS_XC_RECVSTARTSCHEDULETABLEREL        Os_RecvStartScheduleTableRel
#define OS_XC_RECVSTARTSCHEDULETABLEABS        Os_RecvStartScheduleTableAbs
#define OS_XC_RECVNEXTSCHEDULETABLE            Os_RecvNextScheduleTable
#define OS_XC_RECVSTOPSCHEDULETABLE            Os_RecvStopScheduleTable
#define OS_XC_RECVGETSCHEDULETABLESTATUS       Os_RecvGetScheduleTableStatus
#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
#define OS_XC_RECVSTARTSCHEDULETABLESYNCHRON   Os_RecvStartScheduleTableSynchron
#define OS_XC_RECVSETSCHEDULETABLEASYNC        Os_RecvSetScheduleTableAsync
#define OS_XC_RECVSYNCSCHEDULETABLE            Os_RecvSyncScheduleTable
#endif
#endif
/* @Trace: SRS_Os_11012 */
#if (OS_SCALABILITY_CLASS >= OS_SC3)
#define OS_XC_RECVTERMINATEAPPLICATION         Os_RecvTerminateApplication
#define OS_XC_RECVGETAPPLICATIONSTATE          Os_RecvGetApplicationState
#endif
#define OS_XC_RECVSHUTDOWNCORE                 Os_RecvShutdownCore

#if (OS_APPLICATION == STD_ON)
#define OS_XC_RECVIOCPULLCB                    Os_RecvIocPullCB
#else
#define OS_XC_RECVIOCPULLCB                    NULL_PTR
#endif

#ifndef OS_XC_RECVACTIVATETASK
#define OS_XC_RECVACTIVATETASK                 NULL_PTR
#endif

#ifndef OS_XC_RECVACTIVATETASKASYN
#define OS_XC_RECVACTIVATETASKASYN             NULL_PTR
#endif

#ifndef OS_XC_RECVERRORACTIVATETASKASYN
#define OS_XC_RECVERRORACTIVATETASKASYN        NULL_PTR
#endif

#ifndef OS_XC_RECVGETTASKSTATE
#define OS_XC_RECVGETTASKSTATE          NULL_PTR
#endif

#ifndef OS_XC_RECVSETEVENT
#define OS_XC_RECVSETEVENT            NULL_PTR
#endif

#ifndef OS_XC_RECVSETEVENTASYN
#define OS_XC_RECVSETEVENTASYN                 NULL_PTR
#endif

#ifndef OS_XC_RECVERRORSETEVENTASYN
#define OS_XC_RECVERRORSETEVENTASYN            NULL_PTR
#endif

#ifndef OS_XC_RECVGETEVENT
#define OS_XC_RECVGETEVENT            NULL_PTR
#endif

#ifndef OS_XC_RECVGETALARM
#define OS_XC_RECVGETALARM            NULL_PTR
#endif

#ifndef OS_XC_RECVSETRELALARM
#define OS_XC_RECVSETRELALARM         NULL_PTR
#endif

#ifndef OS_XC_RECVSETABSALARM
#define OS_XC_RECVSETABSALARM         NULL_PTR
#endif

#ifndef OS_XC_RECVCANCELALARM
#define OS_XC_RECVCANCELALARM         NULL_PTR
#endif

#ifndef OS_XC_RECVSTARTSCHEDULETABLEREL
#define OS_XC_RECVSTARTSCHEDULETABLEREL      NULL_PTR
#endif

#ifndef OS_XC_RECVSTARTSCHEDULETABLEABS
#define OS_XC_RECVSTARTSCHEDULETABLEABS      NULL_PTR
#endif

#ifndef OS_XC_RECVNEXTSCHEDULETABLE
#define OS_XC_RECVNEXTSCHEDULETABLE      NULL_PTR
#endif

#ifndef OS_XC_RECVSTOPSCHEDULETABLE
#define OS_XC_RECVSTOPSCHEDULETABLE       NULL_PTR
#endif

#ifndef OS_XC_RECVGETSCHEDULETABLESTATUS
#define OS_XC_RECVGETSCHEDULETABLESTATUS    NULL_PTR
#endif

#ifndef OS_XC_RECVSTARTSCHEDULETABLESYNCHRON
#define OS_XC_RECVSTARTSCHEDULETABLESYNCHRON  NULL_PTR
#endif

#ifndef OS_XC_RECVSETSCHEDULETABLEASYNC
#define OS_XC_RECVSETSCHEDULETABLEASYNC     NULL_PTR
#endif

#ifndef OS_XC_RECVSYNCSCHEDULETABLE
#define OS_XC_RECVSYNCSCHEDULETABLE       NULL_PTR
#endif

#ifndef OS_XC_RECVTERMINATEAPPLICATION
#define OS_XC_RECVTERMINATEAPPLICATION      NULL_PTR
#endif

#ifndef OS_XC_RECVGETAPPLICATIONSTATE
#define OS_XC_RECVGETAPPLICATIONSTATE     NULL_PTR
#endif

#ifndef OS_XC_RECVSHUTDOWNCORE
#define OS_XC_RECVSHUTDOWNCORE    NULL_PTR
#endif

#ifndef OS_XC_RECVGETALARMBASE
#define OS_XC_RECVGETALARMBASE NULL_PTR
#endif

/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
CONST(Os_MessageHandler_T, OS_CONST) Os_GaaMessageHandler[OS_N_INTERCORE] =
{
  Os_RecvUnknownCall,                     /*  0 */
  OS_XC_RECVACTIVATETASK,                 /*  1 */
  OS_XC_RECVGETTASKSTATE,                 /*  2 */
  OS_XC_RECVSETEVENT,                     /*  3 */
  OS_XC_RECVGETEVENT,                     /*  4 */
  OS_XC_RECVGETALARM,                     /*  5 */
  OS_XC_RECVGETALARMBASE,                 /*  6 */
  OS_XC_RECVSETRELALARM,                  /*  7 */
  OS_XC_RECVSETABSALARM,                  /*  8 */
  OS_XC_RECVCANCELALARM,                  /*  9 */
  OS_XC_RECVSTARTSCHEDULETABLEREL,        /* 10 */
  OS_XC_RECVSTARTSCHEDULETABLEABS,        /* 11 */
  OS_XC_RECVNEXTSCHEDULETABLE,            /* 12 */
  OS_XC_RECVSTOPSCHEDULETABLE,            /* 13 */
  OS_XC_RECVGETSCHEDULETABLESTATUS,       /* 14 */
  OS_XC_RECVSTARTSCHEDULETABLESYNCHRON,   /* 15 */
  OS_XC_RECVSETSCHEDULETABLEASYNC,        /* 16 */
  OS_XC_RECVSYNCSCHEDULETABLE,            /* 17 */
  OS_XC_RECVTERMINATEAPPLICATION,         /* 18 */
  OS_XC_RECVGETAPPLICATIONSTATE,          /* 19 */
  OS_XC_RECVSHUTDOWNCORE,                 /* 20 */
  OS_XC_RECVIOCPULLCB,                    /* 21 */
  OS_XC_RECVACTIVATETASKASYN,             /* 22 */
  OS_XC_RECVERRORACTIVATETASKASYN,        /* 23 */
  OS_XC_RECVSETEVENTASYN,                 /* 24 */
  OS_XC_RECVERRORSETEVENTASYN,            /* 25 */
};
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Os_InitMessageQueue                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function initializes multicore message queue.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaInterCoreMsgQ                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
FUNC(void, OS_CODE) Os_InitMessageQueue(void)
{
  Os_MessageQueueType *mq;
  Os_Int_T i;
  /* @Trace: SafeOs_SUD_API_23001 */
  /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "This typecast is needed in order to implement a common interface for multicore message" */
  mq = (Os_MessageQueueType*)&Os_GaaInterCoreMsgQ[Os_MyCore()];
  /* polyspace +1 DEFECT:OUT_BOUND_PTR CERT-C:MEM35-C CERT-C:ARR30-C [Justified:Low] "pointer points to a valid value and code is verified manually " */
  mq->fill = 0;
  mq->empty = 0;
  mq->msgCnt = 0;

  for (i = 0; i < OS_N_MESSAGES; i++)
  {
    /* @Trace: SafeOs_SUD_API_23002 */
    mq->buffer[i] = 0;
  }
}

/*******************************************************************************
** Function Name        : Os_SendMessageWait                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a message to other core    **
**                        and wait until message is returned.                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : CoreID                                              **
**                                                                            **
** InOut parameter      : msg                                                 **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaInterCoreMsgQ, Os_GblCoreShutdown             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendMessage(),                                   **
**                        Os_ReceiveMessage(),                                **
**                        Os_MemCopy()                                        **
*******************************************************************************/
/* polyspace +1 CODE-METRICS:CALLING [Not a defect:Low] "Function for sending a message to another core and waiting for acknowlegment" */
FUNC(StatusType, OS_CODE) Os_SendMessageWait(CoreIDType CoreID, Os_MessageType *msg)
{
  volatile uint32 *vMsgResultReady;
  Os_MessageQueueType *mq;
  Os_MessageType *mqmsg;
  uint16 MqFillReturn;
  /* @Trace: SafeOs_SUD_API_23101 */
  /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "This typecast is needed in order to implement a common interface for multicore message" */
  mq = (Os_MessageQueueType*)&Os_GaaInterCoreMsgQ[CoreID];

  /* Send the request to the other core.
   */
  MqFillReturn = Os_SendMessage(CoreID, msg);

  mqmsg = &mq->msg[MqFillReturn];
  vMsgResultReady = &mqmsg->resultReady;

  do
  {
    /* @Trace: SafeOs_SUD_API_23102 */
    /* polyspace +2 RTE:OBAI [Not a defect:Low] "configured array index" */
    /* Check if the current core has already held the spinlock */
    if(Os_GulSpinlocks[OS_MESSAGEQLOCKBASE+Os_MyCore()] != OS_ONE)
    {
      Os_ReceiveMessage(Os_MyCore());
    }

    if(Os_GblCoreShutdown[CoreID] == OS_TRUE)
    {
      /* @Trace: SafeOs_SUD_API_23103 */
      mqmsg->result = E_OS_SYS_CORE_IS_DOWN;
      *vMsgResultReady = OS_TRUE;
    }
  } while ( *vMsgResultReady == OS_FALSE );

  /* @Trace: SafeOs_SUD_API_23104 */
  /* polyspace +2 RTE:STD_LIB MISRA-C3:D4.11 [Justified:Low] "function is called with a valid arguments that are confirmed by testing" */
  /* Update message parameter */
  Os_MemCopy(msg, mqmsg, sizeof(Os_MessageType));

  return (StatusType)mqmsg->result;
}

/*******************************************************************************
** Function Name        : Os_SendMessage                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is sending a message and notifes      **
**                        to other core.                                      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : CoreID                                              **
**                                                                            **
** InOut parameter      : msg                                                 **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaInterCoreMsgQ                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_GetSpinlock(),                                   **
**                        Os_NotifyCore(),                                    **
**                        Os_ReleaseSpinlock()                                **
*******************************************************************************/
FUNC(uint16, OS_CODE) Os_SendMessage(CoreIDType CoreID, P2CONST(Os_MessageType, AUTOMATIC, OS_CONST) msg)
{
  Os_MessageQueueType *mq;
  boolean issend = OS_FALSE;
  uint16 MqFillReturn;
  MqFillReturn = 0;

  /* @Trace: SafeOs_SUD_API_23201 */
  /* Get the message queue descriptor for the target core  */
  /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "This typecast is needed in order to implement a common interface for multicore message" */
  mq = (Os_MessageQueueType*)&Os_GaaInterCoreMsgQ[CoreID];
  do
  {
    /* @Trace: SafeOs_SUD_API_23202 */
    /* Lock message queue */
    Os_GetSpinlock(OS_MESSAGEQLOCKBASE+CoreID);

    if(mq->msgCnt < OS_N_MESSAGES)
    {
      /* @Trace: SafeOs_SUD_API_23203 */
      /* Get the queue data */
      OS_MC_CHECK_MSGQ_STATUS(mq,CoreID)
      OS_MC_CHECK_MSG_COUNT_OVERFLOW(mq,CoreID)

      /* Update the fill pointer to the next slot and force the write */
   /* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
      mq->msg[mq->fill].opcode = msg->opcode;

      mq->msg[mq->fill].parameter[0] = msg->parameter[0];

      mq->msg[mq->fill].parameter[1] = msg->parameter[1];

      mq->msg[mq->fill].parameter[2] = msg->parameter[2];

      mq->msg[mq->fill].parameter[3] = msg->parameter[3];

      mq->buffer[mq->fill] = (CoreIDType)Os_MyCore();

      if((msg->opcode != OS_IC_ShutdownCore) && (msg->opcode != OS_IC_IocPullCB) &&
         (msg->opcode != OS_IC_ErrorActivateTaskAsyn) && (msg->opcode != OS_IC_ErrorSetEventAsyn))
      {
        /* @Trace: SafeOs_SUD_API_23204 */
        mq->msg[mq->fill].result = E_OS_SYS_INTERCOREMSG;
        mq->msg[mq->fill].resultReady = OS_FALSE;
      }
      /* @Trace: SafeOs_SUD_API_23205 */
      /* Return the fill value of the message queue currently being processed */
      MqFillReturn = mq->fill;

   /* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */
      #if (OS_CORE_COUNT >= OS_THREE)
      mq->fill = ((mq->fill+OS_ONE) >= OS_N_MESSAGES) ?
                                                  OS_ZERO : (mq->fill+OS_ONE);
      #else
      /* @Trace: SafeOs_SUD_API_23206 */
      mq->fill = OS_ZERO;
      #endif
      /* @Trace: SafeOs_SUD_API_23207 */
      mq->msgCnt++;

      /* Inform the recipient that it has a message
       */
      Os_NotifyCore(CoreID);
      issend = OS_TRUE;
    }
    /* @Trace: SafeOs_SUD_API_23208 */
    /* Unlock message queue */
    Os_ReleaseSpinlock(OS_MESSAGEQLOCKBASE+CoreID);
  } while (issend == OS_FALSE);
  /* @Trace: SafeOs_SUD_API_23209 */
  return MqFillReturn;
}

/*******************************************************************************
** Function Name        : Os_ReceiveMessage                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Receives a message from other core.                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : CoreID                                              **
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
**                        Os_GaaInterCoreMsgQ, Os_GaaMessageHandler           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_GetSpinlock(),                                   **
**                        Os_AckNotifyCore(),                                 **
**                        Os_ReleaseSpinlock()                                **
*******************************************************************************/
/* polyspace +1 CODE-METRICS:PATH [Justified:Low] "The display of specific values of the number of paths is justified" */
FUNC(void, OS_CODE) Os_ReceiveMessage(CoreIDType CoreID)
{
  Os_MessageQueueType *mq;
  Os_MessageType *msg;
  /* @Trace: SafeOs_SUD_API_23301 */
  /* Get the message queue descriptor for the target core*/
  /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "This typecast is needed in order to implement a common interface for multicore message" */
  mq = (Os_MessageQueueType*)&Os_GaaInterCoreMsgQ[CoreID];

  /* Lock message queue */
  Os_GetSpinlock(OS_MESSAGEQLOCKBASE+CoreID);

  /* Acknowledge the interrupt */
  Os_AckNotifyCore(CoreID);

  /* Get the queue data */
  OS_MC_CHECK_MSGQ_STATUS(mq,CoreID)

  /* Process all messages in the queue.
  */
 /* polyspace +1 DEFECT:OUT_BOUND_PTR CERT-C:MEM35-C CERT-C:ARR30-C [Justified:Low] "pointer points to a valid value and code is verified manually " */
  while ( mq->msgCnt != 0 )
  {
    /* @Trace: SafeOs_SUD_API_23302 */
    /* polyspace +2 RTE:OBAI [Not a defect:Low] "configured array index" */
    /* Get the buffer */
    OS_MC_CHECK_MSG_INDEX((mq->buffer[mq->empty]),CoreID)

    /* Process one message
    */
    msg = (Os_MessageType*)&(mq->msg[mq->empty]);
    OS_MC_CHECK_MSG_STATUS1(msg);
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "configured array index" */
    if (Os_GaaMessageHandler[msg->opcode] != NULL_PTR)
    {
      /* @Trace: SafeOs_SUD_API_23303 */
      /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function and code is manually checked*/
      (*Os_GaaMessageHandler[msg->opcode])(msg);
    }
    else
    { /* polyspace RTE:UNR [Not a defect:Low] "Defensive programming in case of invalid inter-core message handler" */
      /* @Trace: SafeOs_SUD_API_23304 */
      msg->result = E_OS_CORE;
    }
    /* @Trace: SafeOs_SUD_API_23305 */
    OS_MC_CHECK_MSG_STATUS2(msg)

    if((msg->opcode != OS_IC_ShutdownCore) && (msg->opcode != OS_IC_IocPullCB) &&
       (msg->opcode != OS_IC_ErrorActivateTaskAsyn) && (msg->opcode != OS_IC_ErrorSetEventAsyn))
    {
      /* @Trace: SafeOs_SUD_API_23306 */
      msg->resultReady = OS_TRUE;
    }

    /* Move to next message and force pointer write */
    #if (OS_CORE_COUNT >= OS_THREE)
    /* @Trace: SafeOs_SUD_API_23307*/
    mq->empty = ((mq->empty+OS_ONE) >= OS_N_MESSAGES) ?
                                                  OS_ZERO : (mq->empty+OS_ONE);
    #else
    /* @Trace: SafeOs_SUD_API_23308 */
    mq->empty = OS_ZERO;
    #endif
    /* @Trace: SafeOs_SUD_API_23309 */
    mq->msgCnt--;
  }
  /* @Trace: SafeOs_SUD_API_23310 */
  /* Unlock message queue */
  Os_ReleaseSpinlock(OS_MESSAGEQLOCKBASE+CoreID);
}
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif /* End of #if (OS_MULTICORE == STD_ON) */
/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end CERT-C:PRE00-C [Not a defect:Low] "Function like macro is used to improve performance" */
/* polyspace-end RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually." */
/* polyspace-end RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-end MISRA-C3:20.4 [Justified:Low] "Definition for function redirection does not use parenthesised expression" */
/* polyspace-end RTE:NTC [Not a defect:Low] "Os_Panic invoked Shutdown with infinite loop is intended instruction." */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
