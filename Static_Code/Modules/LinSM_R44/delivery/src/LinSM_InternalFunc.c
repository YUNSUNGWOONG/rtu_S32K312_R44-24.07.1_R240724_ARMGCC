/* polyspace +1 MISRA2012:1.1 [Justified:Low] "This rule is checked manually  and has no impact" */
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
**  SRC-MODULE: LinSM_InternalFunc.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinSM Module                                          **
**                                                                            **
**  PURPOSE   : Provision of LinSM Internal Functions                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                  By               Description          **
********************************************************************************
** 1.0.8          05-Jul-2023           KhaLN1           #CP44-2522           **
** 1.0.6.1        22-Dec-2022           HJ Seong         #CP44-1379           **
** 1.0.6          25-Nov-2022           TruongND18       #CP44-1089           **
** 1.0.5.1        25-Oct-2022           KhaLN1           #CP44-564            **
** 1.0.5          03-Aug-2022           KhaLN1           #CP44-514            **
** 1.0.2          17-Sep-2021           DuyNGB           R44-Redmine #20123   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinSM_InternalFunc.h"   /* LinSM Internal header file */
#include "Det.h"
#include "BswM_LinSM.h" 
#include "ComM.h"                 /* ComM header file */
#include "LinSM_PCTypes.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : LinSM_ProcessTimer                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall process the timer                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LddLocalChannelId, LucTimerCount, LucTimerType      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        None                                                **
**                        Function(s) invoked :                               **
**                        Det_ReportError()                                   **
*******************************************************************************/
#if (LINSM_TIMEOUT_FUNC == STD_ON)
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, LINSM_CODE) LinSM_ProcessTimer(NetworkHandleType
  LddLocalChannelId, uint16 LusTimerCount, uint8 LucTimerType)
{
  /* @Trace: LinSM_SUD_API_066 */
  uint16 LusUpdatedTimerCount;
  P2VAR(LinSM_Channel, AUTOMATIC, LINSM_DATA) LpChannel;

  /* @Trace: LinSM_SUD_API_067 */
  /* Get the timer value */
  LusUpdatedTimerCount = LusTimerCount;
  /* Get pointer to channel structure */
  /*LINSM_GET_PTR_TO_CHANNEL_STRUCTURE();*/
  LpChannel = &LinSM_GaaChannel[LddLocalChannelId];

  /* Check the timer expired or not*/
  if (LINSM_ZERO != LusUpdatedTimerCount)
  {
    /* @Trace: LinSM_SUD_API_068 */
    /* Decrement the timer value */
    LusUpdatedTimerCount--;
  }
  else
  {
    /* @Trace: LinSM_SUD_API_069 */
    /* Report DET with LINSM_E_CONFIRMATION_TIMEOUT */
    (void)Det_ReportRuntimeError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_MAINFUNCTION_SID, LINSM_E_CONFIRMATION_TIMEOUT);

    /* Check if the timer type is mode request or not */
    if (LINSM_MODE_REQ_TIMER == LucTimerType)
    {
      /* @Trace: LinSM_SUD_API_070 */
      /* Set mode request as unsuccessful and mode request status to false */
      LpChannel->ucModeScheduleReqStatus =
        (LpChannel->ucModeScheduleReqStatus | LINSM_MODE_REQ_FAILED) &
        LINSM_RESET_MODE_REQ;
    } /* End of if (LucTimerType == LINSM_MODE_REQ_TIMER) */
    else
    {
      /* @Trace: LinSM_SUD_API_071 */
      /* Set the schedule request failure flag and schedule
       * request status to false*/
      LpChannel->ucModeScheduleReqStatus =
        (LpChannel->ucModeScheduleReqStatus | LINSM_SCHEDULE_REQ_FAILED) &
        LINSM_RESET_SCHEDULE_REQ;
    } /* End of else */
  } /* If timer has not expired */
  return (LusUpdatedTimerCount);
} /* End of LinSM_ProcessTimer */

#define LINSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (LINSM_TIMEOUT_FUNC == STD_ON) */

/*******************************************************************************
** Function Name        : LinSM_ProcessTimerSlave                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall process the timer of Slave       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LucTimerCount                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        None                                                **
**                        Function(s) invoked :                               **
**                        Det_ReportError()                                   **
*******************************************************************************/
#if (LINSM_TIMEOUT_FUNC == STD_ON)
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, LINSM_CODE) LinSM_ProcessTimerSlave(uint16 LusTimerCount)
{
  uint16 LusUpdatedTimerCount;

  /* @Trace: LinSM_SUD_API_072 */
  /* Get the timer value */
  LusUpdatedTimerCount = LusTimerCount;

  /* Check the timer expired or not*/
  if (LINSM_ZERO != LusUpdatedTimerCount)
  {
  /* @Trace: LinSM_SUD_API_073 */
    /* Decrement the timer value */
    LusUpdatedTimerCount--;
  }
  else
  {
    /* @Trace: LinSM_SUD_API_074 */
    /* Report DET with LINSM_E_CONFIRMATION_TIMEOUT */
    (void)Det_ReportRuntimeError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_MAINFUNCTION_SID, LINSM_E_CONFIRMATION_TIMEOUT);

  }
  return (LusUpdatedTimerCount);
} /* End of LinSM_ProcessTimerSlave */

#define LINSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (LINSM_TIMEOUT_FUNC == STD_ON) */

/*******************************************************************************
** Function Name        : LinSM_CheckSchedule                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall check the schedule               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : network, schedule                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        None                                                **
**                        Function(s) invoked :                               **
**                        Det_ReportError()                                   **
*******************************************************************************/
#if ((LINSM_DEV_ERROR_DETECT == STD_ON) && (LINSM_MASTER_SUPPORT == STD_ON))
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINSM_CODE) LinSM_CheckSchedule(NetworkHandleType
  network, LinIf_SchHandleType schedule)
{
  /* @Trace: LinSM_SUD_API_075 */
  P2CONST(LinSM_ConfigType, AUTOMATIC, LINSM_CONST) LpConfigType;
  P2CONST(LinSM_HandleChannel, AUTOMATIC, LINSM_CONST) LpHandleChannel;
  P2CONST(uint8, AUTOMATIC, LINSM_CONST) LpScheduleIds;
  NetworkHandleType LddLocalChannelId;
  Std_ReturnType LddReturnValue;
  LinIf_SchHandleType LddArrayIndex;
  boolean LblSearchResult;

  /* @Trace: LinSM_SUD_API_076 */
  /* Set the default return value */
  LddReturnValue = E_OK;
  /* Set the search result with LINSM_TRUE */
  LblSearchResult = LINSM_FALSE;

  /* Set the array index to zero */
  LddArrayIndex = LINSM_ZERO;

  /* Get the Channel Id from the Internal Channel Map array */
  /*LINSM_GET_LOCAL_CHANNEL_ID();*/
	#if (LINSM_SINGLE_CHANNEL == STD_OFF)
    /* @Trace: LinSM_SUD_API_077 */
		(LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
	#else
    /* @Trace: LinSM_SUD_API_078 */
		(LddLocalChannelId) = (network) - (network);
	#endif
  /* @Trace: LinSM_SUD_API_079 */
  /* Get pointer to config type structure */
  /*LINSM_GET_PTR_TO_CONFIG_TYPE_CHANNEL();*/
  LpConfigType = &LinSM_GaaConfigType[LddLocalChannelId];
  /* Get pointer to handle channel structure */
  /*LINSM_GET_PTR_TO_HANDLE_CHANNEL();*/
  LpHandleChannel = &LinSM_GaaHandleChannel[LddLocalChannelId];

  if(LINSM_ZERO == schedule)
  {
    /* @Trace: LinSM_SUD_API_080 */
    LblSearchResult = LINSM_TRUE;
  }
  else
  {
    /* @Trace: LinSM_SUD_API_081 */
    /* polyspace +3 RTE:IDP [Justified:Low] "the value that exceeds LinSM_GaaStaticChannel's maximum element is not used." */
    /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "the value that exceeds LinSM_GaaStaticChannel's maximum element is not used." */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "the value that exceeds LinSM_GaaStaticChannel's maximum element is not used." */
    LpScheduleIds = LpHandleChannel->pScheduleIds; 
    do
    {
      /* Check if requested schedule is configured */
      /* polyspace +4 RTE:IDP [Justified:Low] "the value that exceeds LinSM_GaaScheduleIds' maximum element is filtered by while's condition statement" */
      /* polyspace +3 MISRA-C3:18.4 [Justified:Low] "the value that exceeds LinSM_GaaScheduleIds' maximum element is filtered by while's condition statement" */
      /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "the value that exceeds LinSM_GaaScheduleIds' maximum element is filtered by while's condition statement" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "the value that exceeds LinSM_GaaScheduleIds' maximum element is filtered by while's condition statement" */
      if (schedule == *(LpScheduleIds + (LinSM_UnderlyingType)LddArrayIndex))
      {
        /* @Trace: LinSM_SUD_API_082 */
        /* Set the search result to true*/
        LblSearchResult = LINSM_TRUE;
      }
      /* @Trace: LinSM_SUD_API_083 */
      /* Increment the index */
      LddArrayIndex++;
      /* Check if index is less than no. of schedules and search
       * result is false */
    } while ((LddArrayIndex < LpConfigType->ddNoOfSchedules) &&
	     (LINSM_FALSE == LblSearchResult));
  }

  /* Check if search result is false */
  if (LINSM_FALSE == LblSearchResult)
  {
    /* @Trace: LinSM_SUD_API_084 */
    /* Report to DET */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_SCHEDULEREQUEST_SID, LINSM_E_PARAMETER);
    /* Set return value with E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  } /* End of if (LblSearchResult == LINSM_FALSE) */
  return (LddReturnValue);
} /* End of LinSM_CheckSchedule(NetworkHandleType */

#define LINSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (LINSM_DEV_ERROR_DETECT == STD_ON) */

#if (LINSM_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Function Name        : LinSM_DetRequestComMode                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall check Det ReportError            **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ReturnValue,mode, network                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        LinSM_GblInitStatus, LinSM_GblInitStatus            **
**                        Function(s) invoked :                               **
**                        Det_ReportError()                                   **
*******************************************************************************/

#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINSM_CODE)LinSM_DetRequestComMode(
    Std_ReturnType ReturnValue,
    ComM_ModeType mode,
    NetworkHandleType network)
{
  Std_ReturnType LddReturnValue = ReturnValue;
  #if (LINSM_SINGLE_CHANNEL == STD_OFF)
  NetworkHandleType LddLocalChannelId;
  #endif /* (LINSM_SINGLE_CHANNEL == STD_OFF) */

  /* Check if channel is initialized or not*/
  if (LINSM_UNINIT == LinSM_GblInitStatus)
  {
    /* @Trace: LinSM_SUD_API_011 */
    /* Report DET with LINSM_E_UNINIT */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_REQUESTCOMMODE_SID, LINSM_E_UNINIT);
    /* Set the return value */
    LddReturnValue = E_NOT_OK;
  } /* End of if (LinSM_GblInitStatus == LINSM_UNINIT) */
  #if (LINSM_SINGLE_CHANNEL == STD_ON)

  /* Check network index is out of bounds */
  if (LINSM_MAX_CHANNEL_ID != network)
  {
	/* @Trace: LinSM_SUD_API_012 */
    /* Report to DET */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_REQUESTCOMMODE_SID, LINSM_E_NONEXISTENT_NETWORK);
    /* Set return value with E_NOT_OK*/
    LddReturnValue = E_NOT_OK;
  } /* End of if (network != LINSM_MAX_CHANNEL_ID) */
  #else /* End of if (LINSM_SINGLE_CHANNEL == STD_ON) */
  /* Check network index is out of bounds */
  /*LINSM_CHECK_FOR_INVALID_NETWORK(network, LINSM_REQUESTCOMMODE_SID);*/
  if ((network) > (LINSM_MAX_CHANNEL_ID))
  {
	/* @Trace: LinSM_SUD_API_012 */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
        LINSM_REQUESTCOMMODE_SID, LINSM_E_NONEXISTENT_NETWORK);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    if ((LddLocalChannelId) == (LINSM_INACTIVE_CHANNEL))
    {
	  /* @Trace: LinSM_SUD_API_012 */
      (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
          LINSM_REQUESTCOMMODE_SID, LINSM_E_NONEXISTENT_NETWORK);
      LddReturnValue = E_NOT_OK;
    }
  }
  #endif /* End of if (LINSM_SINGLE_CHANNEL == STD_ON) */

  /* Check if mode parameter is invalid */
  if (!((COMM_FULL_COMMUNICATION == mode) || (COMM_NO_COMMUNICATION == mode) ||
        (COMM_SILENT_COMMUNICATION == mode)))
  {
    /* @Trace: LinSM_SUD_API_013 */
    /* Report to DET */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_REQUESTCOMMODE_SID, LINSM_E_PARAMETER);
    /* Set return value with E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  } /* @ End of if (!((mode == COMM_FULL_COMMUNICATION) || (mode ==
     *COMM_NO_COMMUNICATION) || (mode == COMM_SILENT_COMMUNICATION)))*/
return (LddReturnValue);
}
#define LINSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (LINSM_DEV_ERROR_DETECT == STD_ON) */



#if (LINSM_SLAVE_SUPPORT == STD_ON)
/*******************************************************************************
** Function Name        : LinSM_SlaveRequestComMode                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall RequestComMode of Slave          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : network                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        LinSM_GaaCurrentState, LinSM_GaaSchMEnterFuncPtr,   **
**                        LinSM_GaaCurrentState                               **
**                        Function(s) invoked :                               **
**                        LinIf_WakeUp()                                      **
*******************************************************************************/
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINSM_CODE)LinSM_SlaveRequestComMode(
    NetworkHandleType network)
{
  Std_ReturnType LddReturnValue;
  NetworkHandleType LddLocalChannelId;
  P2VAR(LinSM_Channel, AUTOMATIC, LINSM_DATA) LpChannel;
  #if ((LINSM_GLOBAL_TRCV_SUPPORT == STD_ON) || (LINSM_TIMEOUT_FUNC == STD_ON))
  P2CONST(LinSM_StaticChannel, AUTOMATIC, LINSM_CONST) LpStaticChannel;
  #endif
  LddReturnValue = E_OK;
    
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
    (LddLocalChannelId) = (network) - (network);
    #endif
     LpChannel = &LinSM_GaaChannel[LddLocalChannelId];
     
    #if ((LINSM_GLOBAL_TRCV_SUPPORT == STD_ON) || (LINSM_TIMEOUT_FUNC == STD_ON))
     LpStaticChannel = &LinSM_GaaStaticChannel[LddLocalChannelId];
    #endif
      /* Replace "else if" by "if" to avoid Polyspace tool detect this is a defect */
      /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "It depends on configuration" */
      /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
      /* polyspace-begin RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
      /*else*/ 
      if (LINSM_SLAVE_NODE == LinSM_CurrentNodeType[LddLocalChannelId])
      {
        if (LINSM_FULL_COM == LinSM_GaaCurrentState[LddLocalChannelId])
        {
	      /* @Trace: LinSM_SUD_API_019 */
          /* Enter protection area */
          (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
          /* Set the mode request status to true */
          LpChannel->ucModeScheduleReqStatus =
            LpChannel->ucModeScheduleReqStatus | LINSM_MODE_REQ;
          /* Exit protection area */
          (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
          /* LinSM return E_OK without further action */
          LddReturnValue = E_OK;
        }
        else if (LINSM_NO_COM == LinSM_GaaCurrentState[LddLocalChannelId])
        {
          /* silence-after-wakeup timeout has occurred or not appear */
          if (LINSM_ZERO == LpChannel->ucSilenceAfterWakeupTimeoutCount)
          {
            /* Invoke the API LinIf_Wakeup */
            LddReturnValue = LinIf_Wakeup(network);

            if (E_OK == LddReturnValue)
            {
              /* @Trace: LinSM_SUD_API_022 */
              /* Enter protection area */
              (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
              /* Start Timer By loading the timeout value */
              #if (LINSM_TIMEOUT_FUNC == STD_ON)
              if (LpStaticChannel->usLinSMConfirmationTimeout != LINSM_ZERO)
              {
                LpChannel->usModeReqTimerCount =
                  LpStaticChannel->usLinSMConfirmationTimeout;
              }
              #endif /* End of if (LINSM_TIMEOUT_FUNC == STD_ON) */

              /* Increase Number of Retry */
              LpChannel->ucModeRequestRepetitionCount++;

              /* Set the mode request status to true */
              LpChannel->ucModeScheduleReqStatus =
                LpChannel->ucModeScheduleReqStatus | LINSM_MODE_REQ;

              /* Exit protection area */
              (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
            } /* @ End if (LddReturnValue == E_OK) */
            else
            {
		      /* @Trace: LinSM_SUD_API_021 */
              /* Enter protection area */
              (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
              /* Set mode request to LinIf was not invoked */
              LpChannel->ucModeScheduleReqStatus =
                LpChannel->ucModeScheduleReqStatus | LINSM_MODE_REQ_FAILED;
              /* Exit protection area */
              (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
            } /* End of else */

          }
          else /* silence-after-wakeup timer is running*/
          {
			/* @Trace: LinSM_SUD_API_023 */
            /* delay the call of LinIf_Wakeup */
            LddReturnValue = E_NOT_OK;
          }
        }
        else
        {
 		  /* @Trace: LinSM_SUD_API_020 */
          /* Enter protection area */
          (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
          /* Set mode request as unsuccessful */
          LpChannel->ucModeScheduleReqStatus = LpChannel->ucModeScheduleReqStatus |
                                                LINSM_MODE_REQ_FAILED;
          /* Exit protection area */
          (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
          /* Set the return value E_NOT_OK */
          LddReturnValue = E_NOT_OK;
        }
      }
      /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
      /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "It depends on configuration" */
      /* polyspace-end RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
return (LddReturnValue);
}
#define LINSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (LINSM_SLAVE_SUPPORT == STD_ON) */

#if ((LINSM_TIMEOUT_FUNC == STD_ON) && (LINSM_SLAVE_SUPPORT == STD_ON))
/*******************************************************************************
** Function Name        : LinSM_SlaveMainFunc                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is the main processing function for   **
**                      Slave. It will be invoked by LinSM_MainFunction       **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : LpChannel, LpStaticChannel,LddComMode,              **
**                        LpConfigType, network,LddLocalChannelId             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        LinSM_GaaCurrentState, LinSM_GaaSchMEnterFuncPtr,   **
**                        LinSM_GaaCurrentState                               **
**                        Function(s) invoked :                               **
**                        LinIf_WakeUp(),ComM_BusSM_ModeIndication(),         **
**                        LinSM_ProcessTimer(),BswM_LinSM_CurrentState()      **
*******************************************************************************/
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINSM_CODE)LinSM_SlaveMainFunc(
P2VAR(LinSM_Channel, AUTOMATIC, LINSM_DATA) LpChannel,
P2CONST(LinSM_StaticChannel, AUTOMATIC, LINSM_CONST) LpStaticChannel,
P2CONST(LinSM_ConfigType, AUTOMATIC, LINSM_CONST) LpConfigType,
NetworkHandleType network,
NetworkHandleType LddLocalChannelId,
ComM_ModeType LddComMode)
{
      uint16 LscModeTimerCount;
      Std_ReturnType LddReturnValue;
      if (LINSM_SLAVE_NODE == LinSM_CurrentNodeType[LddLocalChannelId])
      {
      /* silence-after-wakeup timer is running */
      if (LINSM_ZERO != LpChannel->ucSilenceAfterWakeupTimeoutCount)
      {
        /* @Trace: LinSM_SUD_API_034 */
       /* Decrease silence-after-wakeup timer */
       LpChannel->ucSilenceAfterWakeupTimeoutCount--;
      }
      else
      {
       /* do nothing */
      }

      /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "It has been covered by App_LinSM_Slave_x86." */
      /* polyspace-begin RTE:UNR [Justified:Low] "It has been covered by App_LinSM_Slave_x86." */
      /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "It has been covered by App_LinSM_Slave_x86." */
      /* Justify: If condition is False when usLinSMConfirmationTimeout = 0.
       * It has been covered by App_LinSM_Slave_x86.
       * */
      /* Check if timeout configured for particular channel */
      if (LINSM_ZERO != LpStaticChannel->usLinSMConfirmationTimeout)
      {
        
      /* polyspace-end MISRA-C3:14.3 [Justified:Low] "It has been covered by App_LinSM_Slave_x86." */
      /* polyspace-end RTE:UNR [Justified:Low] "It has been covered by App_LinSM_Slave_x86." */
      /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "It has been covered by App_LinSM_Slave_x86." */

        /* Check if mode request is in progress */
        if ((LpChannel->ucModeScheduleReqStatus & LINSM_MODE_REQ) ==
            LINSM_MODE_REQ)
        {
          /* @Trace: LinSM_SUD_API_035 */
          /* Get the timer value configured for this channel */
          LscModeTimerCount = LpChannel->usModeReqTimerCount;
          /* Enter protection area */
          (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
          /* Process the mode req timer by invoking LinSM_ProcessTimerSlave */
          LpChannel->usModeReqTimerCount = LinSM_ProcessTimerSlave(LscModeTimerCount);
          /* Exit protection area */
          (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();

          if (LINSM_ZERO == LpChannel->usModeReqTimerCount)
          {
            /* @Trace: LinSM_SUD_API_036 */
            /* Enter protection area */
            (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
            /* Set mode request as unsuccessful and mode request status to false */
            LpChannel->ucModeScheduleReqStatus =
              (LpChannel->ucModeScheduleReqStatus | LINSM_MODE_REQ_FAILED) &
              LINSM_RESET_MODE_REQ;
            /* Exit protection area */
            (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();

            /* polyspace-begin RTE:UNR [Justified:Low] "It has been covered by App_LinSM_Slave_x86." */
            /* Maximum number of retries have not been reached*/
            if ((LINSM_ZERO != LpChannel->ucModeRequestRepetitionCount)
                && (LpChannel->ucModeRequestRepetitionCount
                    < LpConfigType->ucModeRequestRepetitionMax))
            {
            /* @Trace: LinSM_SUD_API_037 */
            /* polyspace-end RTE:UNR [Justified:Low] "This if-condition will equal to true while run time." */
              /* Invoke the API LinIf_Wakeup */
              LddReturnValue = LinIf_Wakeup(network);

              if (LddReturnValue == E_OK)
              {
                /* @Trace: LinSM_SUD_API_038 */
                /* Enter protection area */
                (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
                /* Start Timer again By loading the timeout value */
                #if (LINSM_TIMEOUT_FUNC == STD_ON)
                /* @Trace: LinSM_SUD_API_039 */
                LpChannel->usModeReqTimerCount =
                  LpStaticChannel->usLinSMConfirmationTimeout;
                #endif /* End of if (LINSM_TIMEOUT_FUNC == STD_ON) */

                /* @Trace: LinSM_SUD_API_040 */
                /* Increase Number of Retry */
                LpChannel->ucModeRequestRepetitionCount++;

                /* Set the mode request status to true */
                LpChannel->ucModeScheduleReqStatus =
                  LpChannel->ucModeScheduleReqStatus | LINSM_MODE_REQ;

                /* Exit protection area */
                (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
              } /* @ End if (LddReturnValue == E_OK) */
              else
              {
                /* @Trace: LinSM_SUD_API_041 */
                /* Enter protection area */
                (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
                /* Reset the flag */
                LpChannel->ucModeScheduleReqStatus =
                  LpChannel->ucModeScheduleReqStatus & LINSM_RESET_MODE_REQ_FAILED;
                /* Exit protection area */
                (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
              } /* End of else */
            }
            /* Maximum number of retries have been reached */
            else if ((LINSM_ZERO != LpChannel->ucModeRequestRepetitionCount)
                  && (LpChannel->ucModeRequestRepetitionCount
                      == LpConfigType->ucModeRequestRepetitionMax))
            {
              /* @Trace: LinSM_SUD_API_042 */
              /* Enter protection area */
              (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
              /* start silence-after-wakeup timer */
              LpChannel->ucSilenceAfterWakeupTimeoutCount = LpStaticChannel->usSilenceAfterWakeupTimeout;

              /* Reset Number of Retry */
              LpChannel->ucModeRequestRepetitionCount = LINSM_ZERO;

              /* Reset the flag */
              LpChannel->ucModeScheduleReqStatus =
                LpChannel->ucModeScheduleReqStatus & LINSM_RESET_MODE_REQ_FAILED;

              /* Invoke ComM_BusSM_ModeIndication */
              ComM_BusSM_ModeIndication(LpStaticChannel->ddLinSMChannelId,
                LddComMode);

              /* Invoke BswM_LinSM_CurrentState */
              BswM_LinSM_CurrentState(LpStaticChannel->ddLinSMChannelId,
                LinSM_GaaCurrentState[LddLocalChannelId]);

              /* Exit protection area */
              (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
            }
            else /* (LINSM_ZERO == LpChannel->ucModeRequestRepetitionCount), handle Gotosleep command */
            {
              /* @Trace: LinSM_SUD_API_043 */
              /* Enter protection area */
              (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();

              /* Reset the flag */
              LpChannel->ucModeScheduleReqStatus =
                LpChannel->ucModeScheduleReqStatus & LINSM_RESET_MODE_REQ_FAILED;

              /* Invoke ComM_BusSM_ModeIndication */
              ComM_BusSM_ModeIndication(LpStaticChannel->ddLinSMChannelId,
                LddComMode);

              /* Invoke BswM_LinSM_CurrentState */
              BswM_LinSM_CurrentState(LpStaticChannel->ddLinSMChannelId,
                LinSM_GaaCurrentState[LddLocalChannelId]);

              /* Exit protection area */
              (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
            }
          }
        } /* End of if ((LpChannel->ucModeScheduleReqStatus & LINSM_MODE_REQ) ==
           *LINSM_MODE_REQ*/
      } /* End if (LpStaticChannel->usLinSMConfirmationTimeout != LINSM_ZERO) */
     }
}
#define LINSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((LINSM_TIMEOUT_FUNC == STD_ON) && (LINSM_SLAVE_SUPPORT == STD_ON)) */

/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
