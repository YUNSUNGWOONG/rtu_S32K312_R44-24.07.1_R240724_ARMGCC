/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**            You can NOT use this sample code for Product Release            **
*******************************************************************************/

/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  FILE-NAME : App_Mode.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Application Mode SWC                                  **
**                                                                            **
**  PURPOSE   : Sample SWC code for Application Mode                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By            Description                         **
********************************************************************************
** x.x.x      dd-mmm-yyyy   Name          Description                         **
*******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "Rte_SWC_AppMode.h"
#include "EcuM_Generated_Callouts.h"
#include "App_Lin.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define APPMODE_FAILED  (uint8)(0x00)
#define APPMODE_PASSED (uint8)(0x01)
#define APPMODE_ZERO   (uint8)(0x00)
#define APPMODE_MAX_TESTSTEP ((uint8)7u)

static uint8 AppMode_GucTestCase = 0u;
static uint8 AppMode_TimerCounter = 0u;
static uint8 AppMode_WdgTestCase = 0u;
static uint16 WdgCounter = 0u;

static Rte_ModeType_MDG_WakeupEvent AppMode_GddWakeupEvent = RTE_MODE_MDG_WakeupEvent_INITIAL_MODE;

#define INTTST_MODE_SLEEP_TIME  (100u)
uint32 IntTst_Mode_SleepCnt = 0;
uint16 IntTst_Lin_ScheduleCmd = 0xFF;

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define APP_MODE_USER 255ul


#define SWC_AppMode_START_SEC_CODE
#include "SWC_AppMode_MemMap.h"

void IcuSignalEdgeDetection_Cbk_WakeUp(void)
{
  /* Do nothing*/
}

void IcuSignalED_Cbk_WakeUp(void)
{
  /* Do nothing*/
}


static uint16 buffertimeStampSize = 2;
static uint16 bufferptrTimestamp[2];
static uint16 timestampIcuNotifyInterval = 10;
/**** User can remove/edit this definition for other purpose **/
Std_ReturnType EcuM_UserHook_DeterminePbConfiguration(uint8* VariantIdx)
{
  *VariantIdx = 0x00;
  return E_OK;
}
void EcuM_UserHook_EnableWakeupSources(EcuM_WakeupSourceType wakeupSource)
{
  /* Set to Sleep Mode
   * 1. Disable notification
   * 2. Set to sleep
   * 3. Enable notification
   * */
  
  /*
   * CAN module
   */
}

void EcuM_UserHook_DisableWakeupSources(EcuM_WakeupSourceType wakeupSource)
{
  /* Set to Sleep Mode
   * 1. Disable notification
   * 2. Set to sleep
   * 3. Enable notification
   * */
}

void EcuM_UserHook_SetProgrammableInterrupts()
{
  /*
   * Do nothing
   */
}

void EcuM_UserHook_CheckValidation(EcuM_WakeupSourceType wakeupSource)
{
}

Std_ReturnType EcuM_UserHook_CheckRamHash()
{
  return E_OK;
}

void EcuM_UserHook_StartWakeupSources(EcuM_WakeupSourceType wakeupSource)
{

}

void EcuM_UserHook_StopWakeupSources(EcuM_WakeupSourceType wakeupSource)
{

}

void EcuM_UserHook_SleepActivity()
{

}

void EcuM_UserHook_GenerateRamHash()
{

}

void EcuM_UserHook_ErrorHook(uint16 reasion)
{
}

void EcuM_UserHook_LoopDetection()
{

}

/*******************************************************************************
** Function Name        : AppMode_InitCompleted                               **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when BSW Init Completed            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void,AppMode_CODE) AppMode_InitCompleted(void)
{
  Rte_ModeType_MDG_InitState LddPrevInitState, LddNextInitState;
  (void)Rte_Mode_modeNotificationPort_InitState_InitState(&LddPrevInitState, &LddNextInitState);
  
  /* Condition when BSW initialization completed */
  if (LddNextInitState == RTE_MODE_MDG_InitState_COMPLETE)
  {
  }
  else 
  {
    /* for MISRA-C:2012 15.7 */
  }
}

/*******************************************************************************
** Function Name        : AppMode_EcuModeSwitched                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when EcuMode updated from BswM     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void,AppMode_CODE) AppMode_EcuModeSwitched(void)
{
  Rte_ModeType_EcuMode LddPrevEcuMode, LddNextEcuMode, LddCurrtEcuMode;
  LddCurrtEcuMode = Rte_Mode_SWC_AppMode_modeNotificationPort_currentMode_currentMode(&LddPrevEcuMode, &LddNextEcuMode);
  
  if (LddNextEcuMode == RTE_MODE_EcuMode_ECUM_STATE_APP_RUN)
  {
    /* Condition when ECU state changed from STARTUP to RUN */
    if ((AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_INITIAL_MODE)
    && (RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE == LddPrevEcuMode))
    {
      //(void)Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);
      /* Disable mode limitation from ComM */
      (void)Rte_Call_SWC_AppMode_R_modeLimitation_SetECUGroupClassification(0x03);
      (void)Rte_Call_R_CL_ComMChannel_FD_CAN1_PNC32_LimitChannelToNoComMode(FALSE);
      (void)Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN1_LimitChannelToNoComMode(FALSE);
      (void)Rte_Call_SWC_AppMode_R_CL_ComMChannel_LIN2_LimitChannelToNoComMode(FALSE);
      /* This code is executed only once shortly after Rte_Start */
      (void)Rte_Write_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32(COMM_MODE_FULL_COM);
      (void)Rte_Write_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1(COMM_MODE_FULL_COM);
      (void)Rte_Write_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2(COMM_MODE_FULL_COM);
    }
    /* Condition when ECU state changed from SLEEP to RUN */
    else if (RTE_MODE_EcuMode_ECUM_STATE_SLEEP == LddPrevEcuMode)
    {
      (void)Rte_Write_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32(COMM_MODE_FULL_COM);
      (void)Rte_Write_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1(COMM_MODE_FULL_COM);
      (void)Rte_Write_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2(COMM_MODE_FULL_COM);
    }
    else 
    {
      /* for MISRA-C:2012 15.7 */
    }
  }
  else if(LddNextEcuMode == RTE_MODE_EcuMode_ECUM_STATE_APP_POST_RUN)
  {
    /*
     * Do nothing there, anything will execute in each testcase.
     */
  }
  else if(LddNextEcuMode == RTE_MODE_EcuMode_ECUM_STATE_SLEEP)
  {
  }
  else
  {
    /* for MISRA-C:2012 15.7 */
  }
}

/*******************************************************************************
** Function Name        : AppMode_WakeupEventValidated                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when wakeup event occurs           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void,AppMode_CODE) AppMode_WakeupEventValidated(void)
{
  Rte_ModeType_MDG_WakeupEvent LddPrevWakeupEvent;
  Rte_ModeType_EcuMode LddPrevEcuMode;
  Rte_ModeType_EcuMode LddNextEcuMode;
  Rte_ModeType_EcuMode LddCurrEcuMode;
  
  (void)Rte_Mode_modeNotificationPort_WakeupEvent_WakeupEvent(&LddPrevWakeupEvent, &AppMode_GddWakeupEvent);
  LddCurrEcuMode = Rte_Mode_SWC_AppMode_modeNotificationPort_currentMode_currentMode(&LddPrevEcuMode, &LddNextEcuMode);
  
  /* Conditions when wakeup occured from ECU SLEEP */
  if (AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_HS_CAN1_RX)
  {
    (void)Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);
  }
  /* Conditions when remote wakeup occured from BUS SLEEP */
  else if (AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_HS_CAN1_RX_POLL)
  {
    /* Actions when CanCM Polling Wakeup occurs */
    (void)Rte_Write_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32(COMM_MODE_FULL_COM);
    (void)Rte_Write_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1(COMM_MODE_FULL_COM);
    (void)Rte_Write_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2(COMM_MODE_FULL_COM);
    
    if (LddCurrEcuMode != RTE_MODE_EcuMode_ECUM_STATE_RUN)
    {
      (void)Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);
    }
    else
    {
      /* for MISRA-C:2012 15.7 */
    }
  }
  else if (AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_FD_CAN1_RX)
  {
    (void)Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);
  }
  /* Conditions when remote wakeup occured from BUS SLEEP */
  else if (AppMode_GddWakeupEvent == RTE_MODE_MDG_WakeupEvent_FD_CAN1_RX_POLL)
  {
    /* Actions when CanCM Polling Wakeup occurs */
    (void)Rte_Write_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32(COMM_MODE_FULL_COM);
    (void)Rte_Write_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1(COMM_MODE_FULL_COM);
    (void)Rte_Write_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2(COMM_MODE_FULL_COM);
    
    if (LddCurrEcuMode != RTE_MODE_EcuMode_ECUM_STATE_RUN)
    {
      (void)Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);
    }
    else
    {
      /* for MISRA-C:2012 15.7 */
    }
  }
  else
  {
    /* for MISRA-C:2012 15.7 */
  }
}

/*******************************************************************************
** Function Name        : AppMode_ComMModeSwitched_FD_CAN1_PNC32              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when ComM Mode switched            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void,AppMode_CODE) AppMode_ComMModeSwitched_FD_CAN1_PNC32(void)
{
  Rte_ModeType_MDG_ComMMode LddPrevBusState, LddNextBusState;
  (void)Rte_Mode_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32(&LddPrevBusState, &LddNextBusState);
  
  /* Conditions when Com Mode No Com switched */
  if (LddNextBusState == RTE_MODE_MDG_ComMMode_NO_COM)
  {
  }
  /* Conditions when Com Mode Silent Com switched */
  else if (LddNextBusState == RTE_MODE_MDG_ComMMode_SILENT_COM)
  {
  }
  /* Conditions when Full Mode No Com switched */
  else if (LddNextBusState == RTE_MODE_MDG_ComMMode_FULL_COM)
  {
  }
  else
  {
    /* for MISRA-C:2012 15.7 */
  }
}

/*******************************************************************************
** Function Name        : AppMode_CanSMBorStateSwitched_FD_CAN1               **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when CanSM Busoff Recovery State   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void,AppMode_CODE) AppMode_CanSMBorStateSwitched_FD_CAN1(void)
{
  Rte_ModeType_MDG_CanSMBORState LddPrevBorState, LddNextBorState;
  (void)Rte_Mode_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1(&LddPrevBorState, &LddNextBorState);
  
  /* Conditions when bus-off recovery started */
  if (LddNextBorState == RTE_MODE_MDG_CanSMBORState_START)
  {
  }
  /* Conditions when bus-off recovery completed */
  else if (LddNextBorState == RTE_MODE_MDG_CanSMBORState_COMPLETE)
  {
  }
  else
  {
    /* for MISRA-C:2012 15.7 */
  }
}

/*******************************************************************************
** Function Name        : AppMode_PduGroupSwitched_FD_CAN1_PNC32_Rx           **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when CanSM PduGroup Switched       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void,AppMode_CODE) AppMode_PduGroupSwitched_FD_CAN1_PNC32_Rx (void)
{
  Rte_ModeType_MDG_PduGroup LddPrevPduState, LddNextPduState;
  (void)Rte_Mode_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32(&LddPrevPduState, &LddNextPduState);
  
  /* Conditions when PduGroup started */
  if (LddNextPduState == RTE_MODE_MDG_PduGroup_STOP)
  {
  }
  /* Conditions when PduGroup completed */
  else if (LddNextPduState == RTE_MODE_MDG_PduGroup_START)
  {
  }
  else 
  {
    /* for MISRA-C:2012 15.7 */
  }
}

/*******************************************************************************
** Function Name        : AppMode_PduGroupSwitched_FD_CAN1_PNC32_Tx           **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when CanSM PduGroup Switched       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void,AppMode_CODE) AppMode_PduGroupSwitched_FD_CAN1_PNC32_Tx (void)
{
  Rte_ModeType_MDG_PduGroup LddPrevPduState, LddNextPduState;
  (void)Rte_Mode_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32(&LddPrevPduState, &LddNextPduState);
  
  /* Conditions when PduGroup started */
  if (LddNextPduState == RTE_MODE_MDG_PduGroup_STOP)
  {
    /* Pdu Group Stop */
  }
  /* Conditions when PduGroup completed */
  else if (LddNextPduState == RTE_MODE_MDG_PduGroup_START)
  {
    /* Pdu Group Start */
  }
  else
  {
    /* for MISRA-C:2012 15.7 */
  }
}

/*******************************************************************************
** Function Name        : AppMode_ComMModeSwitched_LIN1                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when ComM Mode switched            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void,AppMode_CODE) AppMode_ComMModeSwitched_LIN1(void)
{
  Rte_ModeType_MDG_ComMMode LddPrevBusState, LddNextBusState;
  (void)Rte_Mode_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1(&LddPrevBusState, &LddNextBusState);
  
  /* Conditions when Com Mode No Com switched */
  if (LddNextBusState == RTE_MODE_MDG_ComMMode_NO_COM)
  {
  }
  /* Conditions when Com Mode Silent Com switched */
  else if (LddNextBusState == RTE_MODE_MDG_ComMMode_SILENT_COM)
  {
  }
  /* Conditions when Com Mode Full Com switched */
  else if (LddNextBusState == RTE_MODE_MDG_ComMMode_FULL_COM)
  {
  }
  else
  {
    /* for MISRA-C:2012 15.7 */
  }
}

/*******************************************************************************
** Function Name        : AppMode_ComMModeSwitched_LIN1                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Runnable invoked when ComM Mode switched            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void,AppMode_CODE) AppMode_ComMModeSwitched_LIN2(void)
{
  Rte_ModeType_MDG_ComMMode LddPrevBusState, LddNextBusState;
  (void)Rte_Mode_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2(&LddPrevBusState, &LddNextBusState);

  /* Conditions when Com Mode No Com switched */
  if (LddNextBusState == RTE_MODE_MDG_ComMMode_NO_COM)
  {
  }
  /* Conditions when Com Mode Silent Com switched */
  else if (LddNextBusState == RTE_MODE_MDG_ComMMode_SILENT_COM)
  {
  }
  /* Conditions when Com Mode Full Com switched */
  else if (LddNextBusState == RTE_MODE_MDG_ComMMode_FULL_COM)
  {
  }
  else
  {
    /* for MISRA-C:2012 15.7 */
  }
}

/*******************************************************************************
** Function Name        : AppMode_Test                                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Test application runnable                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void,AppMode_CODE) AppMode_Test(void)
{
  switch (AppMode_GucTestCase)
  {
    case 1: /* ECU RUN Test */
      (void)Rte_Call_clientPort_StateRequest_RequestRUN(APP_MODE_USER);
      (void)Rte_Write_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32(COMM_MODE_FULL_COM);
      (void)Rte_Write_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2(COMM_MODE_FULL_COM);
      (void)Rte_Write_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1(COMM_MODE_FULL_COM);
      
      AppMode_GucTestCase = 0;
      break;
      
    case 2: /* ECU OFF Test */
      (void)Rte_Call_clientPort_StateRequest_RequestOff(APP_MODE_USER);
      AppMode_GucTestCase = 0;
      break;
      
    case 3: /* ECU RESET Test */
      (void)Rte_Call_clientPort_StateRequest_RequestReset(APP_MODE_USER);
      AppMode_GucTestCase = 0;
      break;
      
    case 4: /* ECU SLEEP Test */
      if(AppMode_TimerCounter == 0u)
      {
        (void)Rte_Write_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32(COMM_MODE_NO_COM);
        (void)Rte_Write_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1(COMM_MODE_NO_COM);
        (void)Rte_Write_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2(COMM_MODE_NO_COM);
        /* Set up timer 1 second to all network into NO_COM*/
        AppMode_TimerCounter = 70;
      }
      else
      {
        /* Count down the timer */
        AppMode_TimerCounter--;
        
        if(0u == AppMode_TimerCounter)
        {
          (void)Rte_Call_clientPort_StateRequest_RequestSleep(APP_MODE_USER);
          AppMode_GucTestCase = 0;
        }
        else
        {
          /* for MISRA-C:2012 15.7 */
        }
      }
      
      break;
      
    case 5: /* FULL COM Test */
      (void)Rte_Write_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32(COMM_MODE_FULL_COM);
      (void)Rte_Write_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1(COMM_MODE_FULL_COM);
      (void)Rte_Write_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2(COMM_MODE_FULL_COM);
      
      AppMode_GucTestCase = 0;
      break;
      
    case 6: /* NO COM Test */
      (void)Rte_Write_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32(COMM_MODE_NO_COM);
      (void)Rte_Write_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1(COMM_MODE_NO_COM);
      (void)Rte_Write_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2(COMM_MODE_NO_COM);
      
      AppMode_GucTestCase = 0;
      break;
      
    case 7: /* #30821 Watchdog Test*/
      WdgCounter++;
      if(WdgCounter % 100 == 0)
      {
        AppMode_WdgTestCase = 99;
        SuspendAllInterrupts();
        while(1){;}
        ResumeAllInterrupts();
      }
      else
      {
        /* for MISRA-C:2012 15.7 */
      }
      break;
    case 11: /* For Lin test */
      if(IntTst_Lin_ScheduleCmd != 0xFF)
      {
        AppLin_LinLinScheduleRequest(IntTst_Lin_ScheduleCmd);
        IntTst_Lin_ScheduleCmd = 0xFF;
      }
      else
      {
        /* for MISRA-C:2012 15.7 */
      }
      
      AppMode_GucTestCase = 0;
      break;
    case 12: /* For Sleep test by no debugger */
      if(IntTst_Mode_SleepCnt >= INTTST_MODE_SLEEP_TIME)
      {
        AppMode_GucTestCase = 4;
        IntTst_Mode_SleepCnt = 0;
      }
      else
      {
        IntTst_Mode_SleepCnt++;
      }
    default:
      /* for MISRA-C:2012 16.4 */
      break;
  }
}

#define SWC_AppMode_STOP_SEC_CODE
#include "SWC_AppMode_MemMap.h"
