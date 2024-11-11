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
**  SRC-MODULE: LinSM_Cbk.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinSM Module                                          **
**                                                                            **
**  PURPOSE   : Provision of LinSM Call back Functions                        **
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
** 1.0.6.1        22-Dec-2022           HJ Seong         #CP44-1379           **
** 1.0.5.1        25-Oct-2022           KhaLN1           #CP44-564            **
** 1.0.5          03-Aug-2022           KhaLN1           #CP44-514            **
** 1.0.2          26-Apr-2022           DuyNHP2          R44-Redmine #26483   **
** 1.0.2          17-Sep-2021           DuyNGB           R44-Redmine #20123   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinSM_Ram.h"            /* LinSM_Ram header file */
/* @Trace: Com_SUD_FILE_001 */
#include "LinSM.h"                /* LinSM Call back functions header */
/* @Trace: Com_SUD_FILE_001 */
#include "LinSM_PCTypes.h"        /* LinSM pre-compile types header */
#include "Lin_GeneralTypes.h"     /* Lin General Types Header */
/* @Trace: Com_SUD_FILE_001 */
#include "ComM.h"                 /* ComM header file */
/* @Trace: Com_SUD_FILE_001 */
#include "BswM_LinSM.h"           /* BswM header file */
/* @Trace: Com_SUD_FILE_001 */
#include "LinIf.h"
#if (LINSM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* Det header file */
#endif

/* polyspace:begin<RTE: COR : Justified : Justify with annotations > Configured memory access index */
/* polyspace:begin<RTE: OBAI : Justified : Justify with annotations > Configured memory access index */
/* polyspace:begin<RTE: IDP : Justified : Justify with annotations > Configured memory access index */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : LinSM_ScheduleRequestConfirmation                   **
**                                                                            **
** Service ID           : 0x20                                                **
**                                                                            **
** Description          : The LinIf module will call this callback when the   **
**                        new requested schedule table is active.             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : channel, schedule                                   **
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
**                        LinSM_GaaSchMEnterFuncPtr, LinSM_GaaSchMExitFuncPtr,**
**                        LinSM_GblInitStatus                                 **
**                        Function(s) invoked :                               **
**                        Det_ReportError, BswM_LinSM_CurrentSchedule,        **
*******************************************************************************/
/* @Trace: SWS_LinSM_00242 SWS_LinSM_00129 SWS_LinSM_00131
 * SWS_LinSM_00130 SWS_LinSM_00206 SWS_LinSM_00207
 * SWS_LinSM_00172 SRS_BSW_00406
 */
#if (LINSM_MASTER_SUPPORT == STD_ON)
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINSM_APPL_CODE) LinSM_ScheduleRequestConfirmation(
  NetworkHandleType network, LinIf_SchHandleType schedule)
{
  /* @Trace: LinSM_SUD_API_085 */
  /* @Trace: SRS_BSW_00415 */
  NetworkHandleType LddLocalChannelId;
  P2VAR(LinSM_Channel, AUTOMATIC, LINSM_DATA) LpChannel;
  P2CONST(LinSM_StaticChannel, AUTOMATIC, LINSM_CONST) LpStaticChannel;

  #if (LINSM_DEV_ERROR_DETECT == STD_ON)
  /* @Trace: LinSM_SUD_API_086 */
  boolean LblDetErrorFlag;

  /* Set the error flag as false */
  LblDetErrorFlag = LINSM_FALSE;

  /* Check if module is initialized or not */
  if (LINSM_UNINIT == LinSM_GblInitStatus)
  {
    /* @Trace: LinSM_SUD_API_087 */
    /* Report to DET  with LINSM_E_UNINIT */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_SCHEDULEREQUESTCONFIRMATION_SID, LINSM_E_UNINIT);
    /* Set the error flag as true */
    LblDetErrorFlag = LINSM_TRUE;
  } /* End of if (LinSM_GblInitStatus == LINSM_UNINIT) */

  #if (LINSM_SINGLE_CHANNEL == STD_ON)

  /* Check network index is out of bounds */
  if (LINSM_MAX_CHANNEL_ID != network)
  {
	/* @Trace: LinSM_SUD_API_088 */
    /* Report to DET */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_SCHEDULEREQUESTCONFIRMATION_SID, LINSM_E_NONEXISTENT_NETWORK);
    /* Set the error flag as true */
    LblDetErrorFlag = LINSM_TRUE;
  } /* End of if (network != LINSM_MAX_CHANNEL_ID) */

  #else /* End of if (LINSM_SINGLE_CHANNEL == STD_ON) */
  /* Check network index is out of bounds */
//LINSM_CBK_CHECK_FOR_INVALID_NETWORK(network,
//    LINSM_SCHEDULEREQUESTCONFIRMATION_SID);
  if ((network) > (LINSM_MAX_CHANNEL_ID))
  {
	 /* @Trace: LinSM_SUD_API_089 */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
        LINSM_SCHEDULEREQUESTCONFIRMATION_SID, LINSM_E_NONEXISTENT_NETWORK);
    (LblDetErrorFlag) = LINSM_TRUE;
  }
  else
  {
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
	/* @Trace: LinSM_SUD_API_090 */
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
	 /* @Trace: LinSM_SUD_API_091 */
    (LddLocalChannelId) = (network) - (network);
    #endif
    if ((LddLocalChannelId) == (LINSM_INACTIVE_CHANNEL))
    {
	  /* @Trace: LinSM_SUD_API_092 */
      (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
          LINSM_SCHEDULEREQUESTCONFIRMATION_SID, LINSM_E_NONEXISTENT_NETWORK);
      (LblDetErrorFlag) = LINSM_TRUE;
    }
  }
  #endif /* End of if (LINSM_SINGLE_CHANNEL == STD_ON) */

  /* Check if DET has occurred or not */
  if (LblDetErrorFlag == LINSM_FALSE)
  #endif /* End of if (LINSM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the local channel id */
    /*LINSM_GET_LOCAL_CHANNEL_ID();*/
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
	/* @Trace: LinSM_SUD_API_093 */
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
	/* @Trace: LinSM_SUD_API_094 */
    (LddLocalChannelId) = (network) - (network);
    #endif
	/* @Trace: LinSM_SUD_API_095 */
    /* Get pointer to channel structure */
    /*LINSM_GET_PTR_TO_CHANNEL_STRUCTURE();*/
    LpChannel = &LinSM_GaaChannel[LddLocalChannelId];
    /* Get pointer to static channel structure */
    /*LINSM_GET_PTR_TO_STATIC_CHANNEL();*/
    LpStaticChannel = &LinSM_GaaStaticChannel[LddLocalChannelId];
    /* polyspace-begin DEFECT:DEAD_CODE DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
    if (LINSM_MASTER_NODE == LinSM_CurrentNodeType[LddLocalChannelId])
    {
	  /* @Trace: LinSM_SUD_API_096 */
      /* Reset the schedule request status to not requested */
      LpChannel->ucModeScheduleReqStatus = LpChannel->ucModeScheduleReqStatus &
                          LINSM_RESET_SCHEDULE_REQ;
      #if (LINSM_TIMEOUT_FUNC == STD_ON)
      /* Check whether timer is enabled or not for this channel */
      if ((LINSM_ZERO == LpStaticChannel->usLinSMConfirmationTimeout) ||
          ((LINSM_ZERO != LpChannel->usScheduleReqTimerCount) &&
           (LpChannel->ddReqSchedule == schedule)))
      #endif /* End of if (LINSM_TIMEOUT_FUNC == STD_ON) */
      {
		/* @Trace: LinSM_SUD_API_097 */
        /* Enter protection area */
        (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
        #if (LINSM_TIMEOUT_FUNC == STD_ON)
		/* @Trace: LinSM_SUD_API_098 */
        /* Stop the timer by loading LINSM_ZERO */
        LpChannel->usScheduleReqTimerCount = LINSM_ZERO;
        #endif
		/* @Trace: LinSM_SUD_API_099 */
        /* Copy the current schedule to be started */
        LpChannel->ddCurrSchedule = schedule;
        /* Exit protection area */
        (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
        /* Invoke BswM_LinSM_CurrentSchedule */
        BswM_LinSM_CurrentSchedule(LpStaticChannel->ddLinSMChannelId,
        LpChannel->ddCurrSchedule);
      } /* End Checking whether timer is enabled or not for this channel */
      #if (LINSM_TIMEOUT_FUNC == STD_ON)
      else if ((LINSM_ZERO == LpChannel->usScheduleReqTimerCount) &&
               (LpChannel->ddReqSchedule != schedule))
      {
	    /* @Trace: LinSM_SUD_API_100 */
        /* Enter protection area */
        (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
        /* Copy the current schedule to be started */
        LpChannel->ddCurrSchedule = schedule;
        /* Exit protection area */
        (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
        /* Invoke BswM_LinSM_CurrentSchedule */
        BswM_LinSM_CurrentSchedule(LpStaticChannel->ddLinSMChannelId,
        LpChannel->ddCurrSchedule);
      } /* End of if ((LpChannel->usScheduleReqTimerCount == LINSM_ZERO) && */
      else
      {
        /* Do Nothing */
      }
      #endif /* End of if (LINSM_TIMEOUT_FUNC == STD_ON) */
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
    /* polyspace-end DEFECT:DEAD_CODE DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
    #if (LINSM_SLAVE_SUPPORT == STD_ON)
    else
    {
      /* Do Nothing */
    }
    #endif /* (LINSM_SLAVE_SUPPORT == STD_ON) */
  } /* @ End if (LblDetErrorFlag == LINSM_FALSE) */

} /* End of LinSM_ScheduleRequestConfirmation */

#define LINSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (LINSM_MASTER_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : LinSM_GotoSleepIndication                           **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : The LinIf will call this callback when the          **
**                        go to sleep command is received on the              **
**                        network or a bus idle timeout occurs.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : channel                                             **
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
**                        LinSM_GaaSchMEnterFuncPtr, LinSM_GaaSchMExitFuncPtr **
**                        LinSM_GblInitStatus,                                **
**                        LinSM_GaaCurrentState                               **
**                        Function(s) invoked :                               **
**                        Det_ReportError, LinIf_SetTrcvMode,                 **
**                        ComM_BusSM_BusSleepMode                             **
*******************************************************************************/
/* @Trace: SWS_LinSM_91000 SWS_LinSM_00239 SWS_LinSM_00240
 * SWS_LinSM_00243
 */
#if (LINSM_SLAVE_SUPPORT == STD_ON)
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINSM_APPL_CODE) LinSM_GotoSleepIndication(
    NetworkHandleType network)
{
  /* @Trace: LinSM_SUD_API_101 */
  /* @Trace: SRS_BSW_00415 */
  NetworkHandleType LddLocalChannelId;
  P2VAR(LinSM_Channel, AUTOMATIC, LINSM_DATA) LpChannel;
  P2CONST(LinSM_StaticChannel, AUTOMATIC, LINSM_CONST) LpStaticChannel;
  Std_ReturnType LddReturnValue;

  #if (LINSM_DEV_ERROR_DETECT == STD_ON)
  /* @Trace: LinSM_SUD_API_102 */
  boolean LblDetErrorFlag;

  /* @Trace: LinSM_SUD_API_103 */
  /* Set the error flag as false */
  LblDetErrorFlag = LINSM_FALSE;

  if (LINSM_UNINIT == LinSM_GblInitStatus)
  {
    /* @Trace: LinSM_SUD_API_104 */
    /* Report to DET  with LINSM_E_UNINIT */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_GOTOSLEEPCONFIRMATION_SID, LINSM_E_UNINIT);
    /* Set the error flag as true */
    LblDetErrorFlag = LINSM_TRUE;
  } /* End of if (LinSM_GblInitStatus == LINSM_UNINIT) */

  #if (LINSM_SINGLE_CHANNEL == STD_ON)

  /* Check network index is out of bounds */
  if (LINSM_MAX_CHANNEL_ID != network)
  {
	/* @Trace: LinSM_SUD_API_105 */
    /* Report to DET */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_GOTOSLEEPCONFIRMATION_SID, LINSM_E_NONEXISTENT_NETWORK);
    /* Set the error flag as true */
    LblDetErrorFlag = LINSM_TRUE;
  } /* End of if (network != LINSM_MAX_CHANNEL_ID) */

  #else /* End of if (LINSM_SINGLE_CHANNEL == STD_ON) */
  /* Check network index is out of bounds */
//LINSM_CBK_CHECK_FOR_INVALID_NETWORK(network, LINSM_GOTOSLEEPCONFIRMATION_SID);
  if ((network) > (LINSM_MAX_CHANNEL_ID))
  {
	/* @Trace: LinSM_SUD_API_106 */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
        LINSM_GOTOSLEEPCONFIRMATION_SID, LINSM_E_NONEXISTENT_NETWORK);
    (LblDetErrorFlag) = LINSM_TRUE;
  }
  else
  {
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
	/* @Trace: LinSM_SUD_API_107 */
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
	/* @Trace: LinSM_SUD_API_108 */
    (LddLocalChannelId) = (network) - (network);
    #endif
    if ((LddLocalChannelId) == (LINSM_INACTIVE_CHANNEL))
    {
	   /* @Trace: LinSM_SUD_API_109 */
      (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
          LINSM_GOTOSLEEPCONFIRMATION_SID, LINSM_E_NONEXISTENT_NETWORK);
      (LblDetErrorFlag) = LINSM_TRUE;
    }
  }
  #endif /* End of if (LINSM_SINGLE_CHANNEL == STD_ON) */

  /* Check if DET has occurred or not */
  if (LINSM_FALSE == LblDetErrorFlag)
  #endif /* End of if (LINSM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the local channel id */
    /*LINSM_GET_LOCAL_CHANNEL_ID();*/
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
	/* @Trace: LinSM_SUD_API_110 */
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
	/* @Trace: LinSM_SUD_API_111 */
    (LddLocalChannelId) = (network) - (network);
    #endif
	/* @Trace: LinSM_SUD_API_112 */
    /* Get pointer to channel structure */
    /*LINSM_GET_PTR_TO_CHANNEL_STRUCTURE();*/
    LpChannel = &LinSM_GaaChannel[LddLocalChannelId];
    /* Get pointer to static channel structure */
    /*LINSM_GET_PTR_TO_STATIC_CHANNEL();*/
    LpStaticChannel = &LinSM_GaaStaticChannel[LddLocalChannelId];
    if ((LINSM_FULL_COM == LinSM_GaaCurrentState[LddLocalChannelId]) &&
        (LINSM_RUN_COMMUNICATION == LinSM_CurrentSubState[LddLocalChannelId]))
    {
	   /* @Trace: LinSM_SUD_API_113 */
      /* Invoke the API LinIf_GotoSleep */
      LddReturnValue = LinIf_GotoSleep(network);
    }
    else
    {
	  /* @Trace: LinSM_SUD_API_114 */
      LddReturnValue = E_NOT_OK;
    }

    if ((E_OK == LddReturnValue) &&
        ((LpChannel->ucModeScheduleReqStatus & LINSM_MODE_REQ) ==
                  LINSM_MODE_REQ))
    {
	  /* @Trace: LinSM_SUD_API_115 */
      /* Enter protection area */
      (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
      /* Start Timer By loading the timeout value */
      #if (LINSM_TIMEOUT_FUNC == STD_ON)
      if (LINSM_ZERO != LpStaticChannel->usLinSMConfirmationTimeout)
      {
		/* @Trace: LinSM_SUD_API_116 */
        LpChannel->usModeReqTimerCount =
          LpStaticChannel->usLinSMConfirmationTimeout;
      }
      #endif /* End of if (LINSM_TIMEOUT_FUNC == STD_ON) */

      /*Set sub-state to LINSM_GOTOSLEEP if the LinIf_GotoSleep returns E_OK*/
      //if (LINSM_FULL_COM == LinSM_GaaCurrentState[LddLocalChannelId])
      //{
	    /* @Trace: LinSM_SUD_API_117 */
        LinSM_CurrentSubState[LddLocalChannelId] = LINSM_GOTO_SLEEP;
      //}
      /* Invoke ComM_BusSM_BusSleepMode */
      ComM_BusSM_BusSleepMode(network);

      /* Exit protection area */
      (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
    } /* @ End if (LddReturnValue == E_OK) */
    else
    {
      /* @Trace: LinSM_SUD_API_118 */
      /* Enter protection area */
      (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
      /* Set mode request to LinIf was not invoked */
      LpChannel->ucModeScheduleReqStatus =
        LpChannel->ucModeScheduleReqStatus | LINSM_MODE_REQ_FAILED;
      /* Exit protection area */
      (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
    } /* End of else */
  } /* If no development error has occurred */
} /* End of LinSM_GotoSleepIndication */

#define LINSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (LINSM_SLAVE_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : LinSM_GotoSleepConfirmation                         **
**                                                                            **
** Service ID           : 0x22                                                **
**                                                                            **
** Description          : The LinIf will call this callback when the          **
**                        go to sleep command is sent successfully            **
**                        or not sent successfully on the network.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : network, success                                    **
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
**                        LinSM_GaaSchMEnterFuncPtr, LinSM_GaaSchMExitFuncPtr **
**                        LinSM_GaaTrcvPassiveMode, LinSM_GblInitStatus,      **
**                        LinSM_GaaCurrentState                               **
**                        Function(s) invoked :                               **
**                        Det_ReportError, LinIf_SetTrcvMode,                 **
**                        ComM_BusSM_ModeIndication, BswM_LinSM_CurrentState, **
*******************************************************************************/
/* @Trace: SWS_LinSM_00135 SWS_LinSM_00137 SWS_LinSM_00136
 * SWS_LinSM_00046 SWS_LinSM_00027 SWS_LinSM_00193 SWS_LinSM_00203
 * SRS_BSW_00406
 */
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINSM_APPL_CODE) LinSM_GotoSleepConfirmation(
  NetworkHandleType network, boolean success)
{
  /* @Trace: LinSM_SUD_API_119 */
  /* @Trace: SRS_BSW_00415 */
  NetworkHandleType LddLocalChannelId;
  P2VAR(LinSM_Channel, AUTOMATIC, LINSM_DATA) LpChannel;
  P2CONST(LinSM_StaticChannel, AUTOMATIC, LINSM_CONST) LpStaticChannel;
  ComM_ModeType LddComMode;
  (void) success;
  #if (LINSM_DEV_ERROR_DETECT == STD_ON)
  /* @Trace: LinSM_SUD_API_120 */
  boolean LblDetErrorFlag;
  /* @Trace: LinSM_SUD_API_121 */
  /* Set the error flag as false */
  LblDetErrorFlag = LINSM_FALSE;

  if (LINSM_UNINIT == LinSM_GblInitStatus)
  {
    /* @Trace: LinSM_SUD_API_122 */
    /* Report to DET  with LINSM_E_UNINIT */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_GOTOSLEEPCONFIRMATION_SID, LINSM_E_UNINIT);
    /* Set the error flag as true */
    LblDetErrorFlag = LINSM_TRUE;
  } /* End of if (LinSM_GblInitStatus == LINSM_UNINIT) */

  #if (LINSM_SINGLE_CHANNEL == STD_ON)

  /* Check network index is out of bounds */
  if (LINSM_MAX_CHANNEL_ID != network)
  {
  /* @Trace: LinSM_SUD_API_123 */
    /* Report to DET */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_GOTOSLEEPCONFIRMATION_SID, LINSM_E_NONEXISTENT_NETWORK);
    /* Set the error flag as true */
    LblDetErrorFlag = LINSM_TRUE;
  } /* End of if (network != LINSM_MAX_CHANNEL_ID) */

  #else /* End of if (LINSM_SINGLE_CHANNEL == STD_ON) */
  /* Check network index is out of bounds */
//LINSM_CBK_CHECK_FOR_INVALID_NETWORK(network, LINSM_GOTOSLEEPCONFIRMATION_SID);
  if ((network) > (LINSM_MAX_CHANNEL_ID))
  {
	/* @Trace: LinSM_SUD_API_124 */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
        LINSM_GOTOSLEEPCONFIRMATION_SID, LINSM_E_NONEXISTENT_NETWORK);
    (LblDetErrorFlag) = LINSM_TRUE;
  }
  else
  {
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
	/* @Trace: LinSM_SUD_API_125 */
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
	/* @Trace: LinSM_SUD_API_126 */
    (LddLocalChannelId) = (network) - (network);
    #endif
    if ((LddLocalChannelId) == (LINSM_INACTIVE_CHANNEL))
    {
	   /* @Trace: LinSM_SUD_API_127 */
      (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
          LINSM_GOTOSLEEPCONFIRMATION_SID, LINSM_E_NONEXISTENT_NETWORK);
      (LblDetErrorFlag) = LINSM_TRUE;
    }
  }
  #endif /* End of if (LINSM_SINGLE_CHANNEL == STD_ON) */

  /* Check if DET has occurred or not */
  if (LINSM_FALSE == LblDetErrorFlag)
  #endif /* End of if (LINSM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the local channel id */
    /*LINSM_GET_LOCAL_CHANNEL_ID();*/
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
	/* @Trace: LinSM_SUD_API_128 */
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
	/* @Trace: LinSM_SUD_API_129 */
    (LddLocalChannelId) = (network) - (network);
    #endif
	/* @Trace: LinSM_SUD_API_130 */
    /* Get pointer to channel structure */
    /*LINSM_GET_PTR_TO_CHANNEL_STRUCTURE();*/
    LpChannel = &LinSM_GaaChannel[LddLocalChannelId];
    /* Get pointer to static channel structure */
    /*LINSM_GET_PTR_TO_STATIC_CHANNEL();*/
    LpStaticChannel = &LinSM_GaaStaticChannel[LddLocalChannelId];
    /* Set the mode request status to false */
    LpChannel->ucModeScheduleReqStatus = LpChannel->ucModeScheduleReqStatus &
                                         LINSM_RESET_MODE_REQ;
    /* Set communication mode to COMM_NO_COMMUNICATION */
    LddComMode = COMM_NO_COMMUNICATION;

    #if (LINSM_TIMEOUT_FUNC == STD_ON)
    /* Check whether timer is enabled for this channel and check whether timer
     *   has expired for this channel*/
    if ((LINSM_ZERO == LpStaticChannel->usLinSMConfirmationTimeout) ||
      (LINSM_ZERO != LpChannel->usModeReqTimerCount))
    {
      /* @Trace: LinSM_SUD_API_131 */
      /* Stop the timer by loading LINSM_ZERO */
      LpChannel->usModeReqTimerCount = LINSM_ZERO;
    #endif /* End of if (LINSM_TIMEOUT_FUNC == STD_ON) */

      /* Check if goto sleep was successful */
      if ((LINSM_FULL_COM == LinSM_GaaCurrentState[LddLocalChannelId]) &&
          (LINSM_GOTO_SLEEP == LinSM_CurrentSubState[LddLocalChannelId]))
      {
	    /* @Trace: LinSM_SUD_API_132 */
        /* Enter protection area */
        (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
        /* Set the state of the channel to LINSM_NO_COM */
        LinSM_GaaCurrentState[LddLocalChannelId] = LINSM_NO_COM;
        /* Exit protection area */
        (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
        /* Invoke ComM_BusSM_ModeIndication */
        ComM_BusSM_ModeIndication(LpStaticChannel->ddLinSMChannelId,
          LddComMode);
        /* Invoke BswM_LinSM_CurrentState */
        BswM_LinSM_CurrentState(LpStaticChannel->ddLinSMChannelId,
          LinSM_GaaCurrentState[LddLocalChannelId]);
        #if (LINSM_GLOBAL_TRCV_SUPPORT == STD_ON)

        /* Check if LinSMTransceiverPassiveMode is configured */
        /* polyspace-begin DEFECT:DEAD_CODE DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
        if (LINSM_TRCV_NOTCONFIGURED !=
          LinSM_GaaTrcvPassiveMode[LddLocalChannelId])
        {
          /*Check if LinSMTransceiverPassiveMode is configured true */
          if (LINSM_TRCV_CONFIGURED_TRUE ==
              LinSM_GaaTrcvPassiveMode[LddLocalChannelId])
          {
			/* @Trace: LinSM_SUD_API_133 */
            /* Invoke LinIf_SetTrcvMode with Standby */
            (void)LinIf_SetTrcvMode(LpStaticChannel->ddLinSMChannelId,
              LINTRCV_TRCV_MODE_STANDBY);
          }
          else
          {
			/* @Trace: LinSM_SUD_API_134 */
            /* Invoke LinIf_SetTrcvMode with Sleep */
            (void)LinIf_SetTrcvMode(LpStaticChannel->ddLinSMChannelId,
              LINTRCV_TRCV_MODE_SLEEP);
          }
          
        } /* If LinSMTransceiverPassiveMode is configured */
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on configuration" */
        /* polyspace-end DEFECT:DEAD_CODE DEFECT:USELESS_IF [Not a defect:Low] "It depends on configuration" */
        #endif /* # if (LINSM_GLOBAL_TRCV_SUPPORT == STD_ON) */
      } /* @ End if (success == LINSM_TRUE) */
      else
      {
		/* @Trace: LinSM_SUD_API_135 */
        LpChannel->ucModeScheduleReqStatus =
          LpChannel->ucModeScheduleReqStatus | LINSM_MODE_REQ_FAILED;
      }

    #if (LINSM_TIMEOUT_FUNC == STD_ON)
    } /* If enabled timer is running */
    #endif /* End of if (LINSM_TIMEOUT_FUNC == STD_ON) */
  } /* If no development error has occurred */
} /* End of LinSM_GotoSleepConfirmation */

#define LINSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinSM_WakeupConfirmation                            **
**                                                                            **
** Service ID           : 0x21                                                **
**                                                                            **
** Description          : The LinIf will call this callback when              **
**                        the wake up signal command is sent not              **
**                        successfully/successfully on the network.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : channel, success                                    **
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
**                        LinSM_GaaSchMEnterFuncPtr, LinSM_GaaSchMExitFuncPtr **
**                        LinSM_GaaTrcvPassiveMode, LinSM_GblInitStatus,      **
**                        LinSM_GaaCurrentState                               **
**                        Function(s) invoked :                               **
**                        Det_ReportError, LinIf_SetTrcvMode                  **
**                        ComM_BusSM_ModeIndication, BswM_LinSM_CurrentState, **
*******************************************************************************/
/* @Trace: SWS_LinSM_00132 SWS_LinSM_00134 SWS_LinSM_00133
 * SWS_LinSM_00049 SWS_LinSM_00033 SWS_LinSM_00301
 * SWS_LinSM_00192 SWS_LinSM_00172 SWS_LinSM_00032
 * SRS_BSW_00406
 */
#define LINSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINSM_APPL_CODE) LinSM_WakeupConfirmation(NetworkHandleType network,
  boolean success)
{
  /* @Trace: LinSM_SUD_API_136 */
  /* @Trace: SRS_BSW_00415 */
  NetworkHandleType LddLocalChannelId;
  P2VAR(LinSM_Channel, AUTOMATIC, LINSM_DATA) LpChannel;
  P2CONST(LinSM_StaticChannel, AUTOMATIC, LINSM_CONST) LpStaticChannel;
  ComM_ModeType LddComMode;
  #if (LINSM_DEV_ERROR_DETECT == STD_ON)
  /* @Trace: LinSM_SUD_API_137 */
  boolean LblDetErrorFlag;
  /* @Trace: LinSM_SUD_API_138 */
  /* Set the error flag as false */
  LblDetErrorFlag = LINSM_FALSE;

  /* Check if LinSM initialized */
  if (LINSM_UNINIT == LinSM_GblInitStatus)
  {
    /* @Trace: LinSM_SUD_API_139 */
    /* Report to DET  with LINSM_E_UNINIT */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_WAKEUPCONFIRMATION_SID, LINSM_E_UNINIT);
    /* Set the error flag as true */
    LblDetErrorFlag = LINSM_TRUE;
  } /* End of if (LinSM_GblInitStatus == LINSM_UNINIT) */

  #if (LINSM_SINGLE_CHANNEL == STD_ON)

  /* Check network index is out of bounds */
  if (LINSM_MAX_CHANNEL_ID != network)
  {
	/* @Trace: LinSM_SUD_API_140 */
    /* Report to DET */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
      LINSM_WAKEUPCONFIRMATION_SID, LINSM_E_NONEXISTENT_NETWORK);
    /* Set the error flag as true */
    LblDetErrorFlag = LINSM_TRUE;
  } /* End of if (network != LINSM_MAX_CHANNEL_ID) */

  #else /* End of if (LINSM_SINGLE_CHANNEL == STD_ON) */
  /* Check network index is out of bounds */
//LINSM_CBK_CHECK_FOR_INVALID_NETWORK(network, LINSM_WAKEUPCONFIRMATION_SID);
  if ((network) > (LINSM_MAX_CHANNEL_ID))
  {
	/* @Trace: LinSM_SUD_API_141 */
    (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
        LINSM_WAKEUPCONFIRMATION_SID, LINSM_E_NONEXISTENT_NETWORK);
    (LblDetErrorFlag) = LINSM_TRUE;
  }
  else
  {
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
	/* @Trace: LinSM_SUD_API_142 */
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
	/* @Trace: LinSM_SUD_API_143 */
    (LddLocalChannelId) = (network) - (network);
    #endif
    if ((LddLocalChannelId) == (LINSM_INACTIVE_CHANNEL))
    {
	  /* @Trace: LinSM_SUD_API_144 */
      (void)Det_ReportError(LINSM_MODULE_ID, LINSM_INSTANCE_ID,
          LINSM_WAKEUPCONFIRMATION_SID, LINSM_E_NONEXISTENT_NETWORK);
      (LblDetErrorFlag) = LINSM_TRUE;
    }
  }
  #endif /* End of if (LINSM_SINGLE_CHANNEL == STD_ON) */

  if (LblDetErrorFlag == LINSM_FALSE)
  #endif /* End of if (LINSM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the local channel id */
    /*LINSM_GET_LOCAL_CHANNEL_ID();*/
    #if (LINSM_SINGLE_CHANNEL == STD_OFF)
	/* @Trace: LinSM_SUD_API_145 */
    (LddLocalChannelId) = (LinSM_GaaInternalChannelMap[network]);
    #else
	/* @Trace: LinSM_SUD_API_146 */
    (LddLocalChannelId) = (network) - (network);
    #endif
	/* @Trace: LinSM_SUD_API_147 */
    /* Get pointer to channel structure */
    /*LINSM_GET_PTR_TO_CHANNEL_STRUCTURE();*/
    LpChannel = &LinSM_GaaChannel[LddLocalChannelId];
    /* Get pointer to static channel structure */
    /*LINSM_GET_PTR_TO_STATIC_CHANNEL();*/
    LpStaticChannel = &LinSM_GaaStaticChannel[LddLocalChannelId];
    /* Set the mode request status to false */
    LpChannel->ucModeScheduleReqStatus = LpChannel->ucModeScheduleReqStatus &
                                         LINSM_RESET_MODE_REQ;
    /* Set communication mode to COMM_FULL_COMMUNICATION */
    LddComMode = COMM_FULL_COMMUNICATION;
    /* Check whether timer is enabled for this channel and check whether timer
     *   has expired for this channel*/
    #if (LINSM_TIMEOUT_FUNC == STD_ON)
    if ((LINSM_ZERO == LpStaticChannel->usLinSMConfirmationTimeout) ||
        (LINSM_ZERO != LpChannel->usModeReqTimerCount))
    {
      /* @Trace: LinSM_SUD_API_148 */
      /* Stop the timer by loading LINSM_ZERO */
      LpChannel->usModeReqTimerCount = LINSM_ZERO;
    #endif /* End of if (LINSM_TIMEOUT_FUNC == STD_ON) */

      /* Check if wakeup was successful */
      if (LINSM_TRUE == success)
      {
	    /* @Trace: LinSM_SUD_API_149 */
        /* Enter protection area */
        (LinSM_GaaSchMEnterFuncPtr[LddLocalChannelId])();
        /* Set the state of the channel to LINSM_FULL_COM */
        LinSM_GaaCurrentState[LddLocalChannelId] = LINSM_FULL_COM;
        /* Set the sub-state of the channel to LINSM_RUN_COMMUNICATION */
        LinSM_CurrentSubState[LddLocalChannelId] = LINSM_RUN_COMMUNICATION;
        /* Exit protection area */
        (LinSM_GaaSchMExitFuncPtr[LddLocalChannelId])();
        /* Invoke ComM_BusSM_ModeIndication */
        ComM_BusSM_ModeIndication(LpStaticChannel->ddLinSMChannelId,
          LddComMode);
        /* Invoke BswM_LinSM_CurrentState */
        BswM_LinSM_CurrentState(LpStaticChannel->ddLinSMChannelId,
          LinSM_GaaCurrentState[LddLocalChannelId]);

        /* Redmine #9471: Already set to normal before the call of LinIf_Wakeup() */
        /* So, Remove LinIf_SetTrcvMode(NORMAL)                                   */

      } /* @ End if (success == LINSM_TRUE) */
      else
      {
		/* @Trace: LinSM_SUD_API_150 */
        LpChannel->ucModeScheduleReqStatus =
          LpChannel->ucModeScheduleReqStatus | LINSM_MODE_REQ_FAILED;
      }

    #if (LINSM_TIMEOUT_FUNC == STD_ON)
    } /* If enabled timer is running */
    #endif /* End of if (LINSM_TIMEOUT_FUNC == STD_ON) */
  } /* If no development error has occurred */
} /* End of LinSM_WakeupConfirmation **/

#define LINSM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end<RTE: COR : Justified : Justify with annotations > Configured memory access index */
/* polyspace:end<RTE: OBAI : Justified : Justify with annotations > Configured memory access index */
/* polyspace:end<RTE: IDP : Justified : Justify with annotations > Configured memory access index */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
