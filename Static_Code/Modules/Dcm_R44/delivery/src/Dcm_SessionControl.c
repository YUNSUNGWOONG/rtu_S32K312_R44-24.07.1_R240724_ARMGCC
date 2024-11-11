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
**  SRC-MODULE: Dcm_SessionControl.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains interfaces for services related to session **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision     Date            By           Description                      **
********************************************************************************
** 0.0.1        04-Dec-2019     HueKM        Initial Version                  **
** 0.0.2        16-Aug-2020     HueKM        Fix defect and coding rules      **
** 0.0.3        13-Oct-2020     HueKM        Changes made as per #15766       **
** 0.0.4        02-Nov-2020     HueKM        Changes made as per #16832       **
** 0.0.5        04-Dec-2020     HueKM        Polyspace fixing as per #15175   **
** 0.0.6        16-Dec-2020     HueKM        Mapping SUD API ID as per #17448 **
** 1.0.7        16-Dec-2022     LanhLT       Fix UNECE                        **
** 1.0.9        31-Mar-2023     LanhLT       Refer #CP44-1819                 **
** 1.1.2        13-Nov-2023     DH Kwak      Refer #CP44-3122                 **
** 1.4.1        01-Apr-2024     GuillaumeMPD Refer #CP44-5271                 **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_SessionControl.h"

#include "Dcm_Ram.h"
#include "Dcm_Lib.h"
#include "Dcm_Timer.h"
#include "Dcm_Config.h"
#include "Dcm_Validate.h"
#include "Dcm_DslInternal.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_ReqRespHandling.h"

#if ((DCM_DSP_DIAG_SESSION_SERVICE == STD_ON) || \
     (DCM_DSP_STOP_DIAG_SESSION_SERVICE == STD_ON))
#define DCM_SESSION_CONTROL_SERVICE_ENABLED
#endif

/* polyspace-begin MISRA2012:8.13 [Justified:Unset] "It will be fixed soon" */

/*******************************************************************************
**                     Types and Variables definition                         **
*******************************************************************************/
#ifdef DCM_SESSION_CONTROL_SERVICE_ENABLED
typedef enum
{
  DCM_SESCTRL_SEND_RCRRP,
  DCM_SESCTRL_PENDING,
  DCM_SESCTRL_FORCE_PENDNG,
  DCM_SESCTRL_FLAG_NUM
} Dcm_SesCtrlFlagType;

typedef enum
{
  DCM_SESCTRL_NO_ACTION,
  DCM_SESCTRL_SEND_POSITIVE,
  DCM_SESCTRL_SWITCH_SESSION,
  DCM_SESCTRL_RESET_AFTER_RCRRP,
  DCM_SESCTRL_RESET_AFTER_POSITIVE,
} Dcm_SesCtrlActionType;

typedef struct
{
  /* Store the index of session configuration */
  uint8 cfgIndex;

  /* Indicate the status of current operation */
  boolean flag[DCM_SESCTRL_FLAG_NUM];

} Dcm_SesCtrlStateType;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
static VAR(Dcm_SesCtrlStateType, DCM_VAR) Dcm_SesCtrlState;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
**                      Static Functions Declaration                          **
*******************************************************************************/
#ifdef DCM_SESSION_CONTROL_SERVICE_ENABLED
static FUNC(void, DCM_CODE) Dcm_SesCtrl_ClearAllFlags(void);

/* polyspace +1 DEFECT:UNCALLED_FUNC [Justified:Low] "Because service 0x10 is not configured, this defect occurs" */
static FUNC(boolean, DCM_CODE) Dcm_SesCtrl_IsAllFlagsCleared(void);

static FUNC(void, DCM_CODE) Dcm_SesCtrl_SwitchSession(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_SesCtrl_UpdateS3Timer(
  Dcm_MsgContextPtrType pMsgContext);
#endif

#if (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
static FUNC(boolean, DCM_CODE) Dcm_SesCtrl_IsBootNormal(
  Dcm_SesForBootType sesForBoot);

static FUNC(boolean, DCM_CODE) Dcm_SesCtrl_IsBootResApp(
  Dcm_SesForBootType sesForBoot);

static FUNC(boolean, DCM_CODE) Dcm_SesCtrl_IsOemBoot(
  Dcm_SesForBootType sesForBoot);

static FUNC(boolean, DCM_CODE) Dcm_SesCtrl_IsSysBoot(
  Dcm_SesForBootType sesForBoot);

static FUNC(boolean, DCM_CODE) Dcm_SesCtrl_IsProgramRequest(
  Dcm_SesCtrlType sessionLevel);

static FUNC(void, DCM_CODE) Dcm_SesCtrl_UpdatePosResp(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_SesCtrl_UpdateProgCondition(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_SessionConfigConstPtrType pSessionCfg);

static FUNC(void, DCM_CODE) Dcm_SesCtrl_ProcessProgCondition(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_SesCtrl_SwitchMode(
  Dcm_SesForBootType sesForBoot);

static FUNC(void, DCM_CODE) Dcm_SesCtrl_ProcessJumpToBootloader(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_SessionConfigConstPtrType pSessionCfg,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_SesCtrl_ProcessStartSession(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_SessionConfigConstPtrType pSessionCfg,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Dcm_SesCtrlActionType, DCM_CODE) Dcm_SesCtrl_GetPosSuccessAction(
  Dcm_SesForBootType sesForBoot);

static FUNC(Dcm_SesCtrlActionType, DCM_CODE) Dcm_SesCtrl_GetNegSuccessAction(
  Dcm_SesForBootType sesForBoot);

static FUNC(Dcm_SesCtrlActionType, DCM_CODE) Dcm_SesCtrl_GetConfirmAction(
  Dcm_ConfirmationStatusType confirmStatus);

static FUNC(void, DCM_CODE) Dcm_SesCtrl_DoConfirmAction(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_SesCtrlActionType actionType);

static FUNC(void, DCM_CODE) Dcm_SesCtrl_CheckProcessingDone(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_SesCtrl_SendNrcRcrrp(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);
#endif

/*******************************************************************************
**                              Function definition                           **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

#ifdef DCM_SESSION_CONTROL_SERVICE_ENABLED
/*******************************************************************************
** Function Name        : Dcm_SesCtrl_ClearAllFlags                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Clear all operation flag of Session Control Service **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SesCtrl_ClearAllFlags(void) 
{
  /* @Trace: Dcm_SUD_API_30062 */
  uint16 flagIdx;

  for (flagIdx = DCM_ZERO; flagIdx < (uint16) DCM_SESCTRL_FLAG_NUM; flagIdx++) 
  {
    /* @Trace: Dcm_SUD_API_30063 */
    Dcm_SesCtrlState.flag[flagIdx] = DCM_FALSE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_IsAllFlagsCleared                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check whether all operation flag is cleared or not  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : retVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +1 DEFECT:UNCALLED_FUNC [Justified:Low] "Because service 0x10 is not configured, this defect occurs" */
static FUNC(boolean, DCM_CODE) Dcm_SesCtrl_IsAllFlagsCleared(void) 
{
  /* @Trace: Dcm_SUD_API_30085 */
  boolean retVal = DCM_FALSE;

  if ((DCM_FALSE == Dcm_GblReset) &&
      (DCM_FALSE == Dcm_SesCtrlState.flag[DCM_SESCTRL_SEND_RCRRP]) &&
      (DCM_FALSE == Dcm_SesCtrlState.flag[DCM_SESCTRL_PENDING]) &&
      (DCM_FALSE == Dcm_SesCtrlState.flag[DCM_SESCTRL_FORCE_PENDNG]))
  {
    /* @Trace: Dcm_SUD_API_30086 */
    retVal = DCM_TRUE;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_SwitchSession                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Switch to new session and update timing parameter   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SesCtrl_SwitchSession(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_30133 */
  Dcm_SessionConfigConstPtrType pSessionCfg = Dcm_GetSesCtrlConfig();

  if (NULL_PTR != pSessionCfg)
  {
    Dcm_TimerServerType newTiming;
    /* @Trace: Dcm_SUD_API_30134 */
    Dcm_SesCtrlType sessionLevel = pSessionCfg->ddSesCtrlLevel;
    DslInternal_SetSesCtrlType(sessionLevel);

    /* @Trace: SRS_Diag_04208 */
    /* polyspace +1 MISRA-C3:17.7 [Justified:Low] Justify with annotations */
    SchM_Switch_Dcm_DcmDiagnosticSessionControl(sessionLevel);

    newTiming.Timer_P2ServerMax = pSessionCfg->usSesP2ServerMax;
    newTiming.Timer_P2StarServerMax = pSessionCfg->usSesP2StrServerMax;
    newTiming.Timer_S3Server = DCM_TIMSTR_S3_SERVER;
    
    Dcm_DslSetSesTimingValues(&newTiming);

    Dcm_SesCtrl_UpdateS3Timer(pMsgContext);
  }
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_UpdateS3Timer                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Update S3 timing relate to Session Service          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SesCtrl_UpdateS3Timer(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* YoungJinYun: fixed session timeout bug */
  if (CHECK_NONDEFAULT_SESSION(Dcm_GddCurrentSession))
  {
    /* @Trace: Dcm_SUD_API_35002 */
    if (DCM_TRUE == pMsgContext->msgAddInfo.suppressPosResponse)
    {
      /* @Trace: Dcm_SUD_API_30145 */
      Dcm_StartTimer(DCM_S3SERVER_TIMER, GET_TIMER_S3_SERVER);
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_35001 */
    if (CHECK_NONDEFAULT_SESSION(Dcm_GddOldSession))
    {
      /* @Trace: Dcm_SUD_API_30146 */
      Dcm_StopTimer(DCM_S3SERVER_TIMER);
    }
  }
}
#endif

#if (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
/*******************************************************************************
** Function Name        : Dcm_SesCtrl_IsProgramRequest                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if requested session is PROGRAMMING or not    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : sessionLevel                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : retVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_SesCtrl_IsProgramRequest(
  Dcm_SesCtrlType sessionLevel)
{
  /* @Trace: Dcm_SUD_API_30097 */
  boolean retVal = DCM_FALSE;

  /* @Trace: SWS_Dcm_01182 */
  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT)
  if (E_OK == Dcm_ChkSessionLevel(sessionLevel))
  {
    /* @Trace: Dcm_SUD_API_30098 */
    retVal = DCM_TRUE;
  }
  #else
  if (DCM_PROGRAMMING_SESSION == sessionLevel)
  {
    /* @Trace: Dcm_SUD_API_30099 */
    retVal = DCM_TRUE;
  }
  #endif

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_IsBootNormal                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the session for boot is request send       **
**                        response before jump to bootloader or not           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : sesForBoot                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : retVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_SesCtrl_IsBootNormal(
  Dcm_SesForBootType sesForBoot)
{
  /* @Trace: Dcm_SUD_API_30088 */
  boolean retVal = DCM_FALSE;

  if ((DCM_OEM_BOOT == sesForBoot) ||
      (DCM_SYS_BOOT == sesForBoot))
  {
    /* @Trace: Dcm_SUD_API_30089 */
    retVal = DCM_TRUE;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_IsBootResApp                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the session for boot is request send       **
**                        response before jump to bootloader or not           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : sesForBoot                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : retVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_SesCtrl_IsBootResApp(
  Dcm_SesForBootType sesForBoot)
{
  /* @Trace: Dcm_SUD_API_30091 */
  boolean retVal = DCM_FALSE;

  if ((DCM_OEM_BOOT_RESPAPP == sesForBoot) ||
      (DCM_SYS_BOOT_RESPAPP == sesForBoot))
  {
    /* @Trace: Dcm_SUD_API_30092 */
    retVal = DCM_TRUE;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_IsOemBoot                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the requested session is required to       **
**                        Jump to OEM bootloader or not                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : sesForBoot                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : retVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_SesCtrl_IsOemBoot(
  Dcm_SesForBootType sesForBoot)
{
  /* @Trace: Dcm_SUD_API_30094 */
  boolean retVal = DCM_FALSE;

  if ((DCM_OEM_BOOT == sesForBoot) ||
      (DCM_OEM_BOOT_RESPAPP == sesForBoot))
  {
    /* @Trace: Dcm_SUD_API_30095 */
    retVal = DCM_TRUE;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_IsSysBoot                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the requested session is required to       **
**                        Jump to System Supplier bootloader or not           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : sesForBoot                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : retVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_SesCtrl_IsSysBoot(
  Dcm_SesForBootType sesForBoot)
{
  /* @Trace: Dcm_SUD_API_30101 */
  boolean retVal = DCM_FALSE;

  if ((DCM_SYS_BOOT == sesForBoot) ||
      (DCM_SYS_BOOT_RESPAPP == sesForBoot))
  {
    /* @Trace: Dcm_SUD_API_30102 */
    retVal = DCM_TRUE;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_UpdatePosResp                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function use to update positive response of     **
**                        UDS 0x10 service                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SesCtrl_UpdatePosResp(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_30140 */
  Dcm_SessionConfigConstPtrType pSessionCfg = Dcm_GetSesCtrlConfig();

  if (NULL_PTR != pSessionCfg)
  {
    /* @Trace: Dcm_SUD_API_30141 */
    /* Get session level, this is also sub-function */
    uint8 sessionLevel = (uint8) pSessionCfg->ddSesCtrlLevel;

    /* The resolution of P2 Server timing is 1 ms */
    uint16 p2ServerTiming = pSessionCfg->usSesP2ServerMax;

    /* The resolution of P2* Server timing is 10 ms */
    uint16 p2StrServerTiming = (pSessionCfg->usSesP2StrServerMax) / 10U;

    /* Response message length is 5 */
    pMsgContext->resDataLen = 5U;
    pMsgContext->resData[0U] = sessionLevel;

    /* Set P2 Server timing  */
    pMsgContext->resData[1U] = (uint8) (p2ServerTiming >> (uint16) 8);
    pMsgContext->resData[2U] = (uint8) (p2ServerTiming & (uint16) 0x00ff);

    /* Set P2* Server timing  */
    pMsgContext->resData[3U] = (uint8) (p2StrServerTiming >> (uint16) 8);
    pMsgContext->resData[4U] = (uint8) (p2StrServerTiming & (uint16) 0x00ff);
 
    if (pSessionCfg->ddSesCtrlLevel == DCM_PROGRAMMING_SESSION)
    {
      Dcm_GblJumpToBootloader = DCM_TRUE;
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_UpdateProgCondition                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function use to update the progress condition   **
**                        before Ecu execute a Jump to bootloader             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pSessionCfg                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SesCtrl_UpdateProgCondition(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_SessionConfigConstPtrType pSessionCfg)
{
  /* @Trace: Dcm_SUD_API_30142 */
  Dcm_SesCtrlType sessionLevel = pSessionCfg->ddSesCtrlLevel;
  Dcm_SesForBootType sesForBoot = pSessionCfg->ucSesForBootLevel;

  Dcm_SecLevelType securityLevel = DCM_SEC_LEV_LOCKED;
  (void) Dcm_GetSecurityLevel(&securityLevel);

  uint16 pduIdIdx = pMsgContext->dcmRxPduId;
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[pduIdIdx];

  /* Update connection id and tester address */
  Dcm_GddProgConditions.ConnectionId = pPduIdTable->RxConnectionId;
  Dcm_GddProgConditions.TesterAddress = pPduIdTable->ConfigTesterAddress;

  /* Update service id and sub-function id */
  Dcm_GddProgConditions.Sid = DCM_DIAGNOSTICSESSIONCONTROL;
  Dcm_GddProgConditions.SubFncId = (uint8) sessionLevel;

  /* Clear application updated flag and set security level */
  Dcm_GddProgConditions.ApplUpdated = DCM_FALSE;
  Dcm_GddProgConditions.SecurityLevel = (uint8) securityLevel;

  /* @Trace: SWS_Dcm_01182 */
  boolean isProgRequest = Dcm_SesCtrl_IsProgramRequest(sessionLevel);
  Dcm_GddProgConditions.ReprogramingRequest = isProgRequest;

  /* @Trace: SWS_Dcm_01183 */
  boolean isProgResRequired = Dcm_SesCtrl_IsBootNormal(sesForBoot);
  if (DCM_TRUE == pMsgContext->msgAddInfo.suppressPosResponse)
  {
    /* FBL no need to create a positive response*/
    Dcm_GddProgConditions.ResponseRequired = DCM_FALSE;
  } 
  else 
  {
    Dcm_GddProgConditions.ResponseRequired = isProgResRequired;
  }
  
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_ProcessProgCondition                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function will call Dcm_SetProgConditions and    **
**                        process the return value of it                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SesCtrl_ProcessProgCondition(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType retVal;

  Dcm_SesCtrl_ClearAllFlags();
  retVal = Dcm_SetProgConditions(OpStatus, &Dcm_GddProgConditions);

  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00543, the function Dcm_SetProgConditions has return 4 values.
    So, Dcm must be implement to cover all return value of function Dcm_SetProgConditions." */
  switch (retVal)
  {
    case E_OK:
      /* @Trace: SWS_Dcm_01163 SWS_Dcm_01180 SWS_Dcm_00719 SWS_Dcm_01164 */
      /* @Trace: Dcm_SUD_API_30111 */
      Dcm_GblReset = DCM_TRUE;
      Dcm_GblExecuteECUReset = DCM_TRUE;
      break;

    case DCM_E_PENDING:
      /* @Trace: Dcm_SUD_API_30112 */
      Dcm_SesCtrlState.flag[DCM_SESCTRL_PENDING] = DCM_TRUE;
      break;

    case DCM_E_FORCE_RCRRP:
      /* @Trace: Dcm_SUD_API_30113 */
      Dcm_SesCtrlState.flag[DCM_SESCTRL_FORCE_PENDNG] = DCM_TRUE;
      (void)Dcm_SesCtrl_SendNrcRcrrp(pMsgContext, pErrorCode);
      break;

    default:
      /* @Trace: SWS_Dcm_01163 SWS_Dcm_00715 */
      /* @Trace: Dcm_SUD_API_30114 */
      *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;

      /* @Trace: SWS_Dcm_01185 */
      DCM_REPORT_ERROR(DCM_SETPROGCONDITIONS_SID, DCM_E_SET_PROG_CONDITIONS_FAIL);
      break;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00543, the function Dcm_SetProgConditions has return 4 values.
    So, Dcm must be implement to cover all return value of function Dcm_SetProgConditions. " */
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_SwitchMode                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Inform new mode of DcmEcuReset to BswM              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : sesForBoot                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : schMReturn                                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04098 */
static FUNC(Std_ReturnType, DCM_CODE) Dcm_SesCtrl_SwitchMode(
  Dcm_SesForBootType sesForBoot)
{
  /* @Trace: Dcm_SUD_API_30129 */
  Std_ReturnType schMReturn = E_NOT_OK;

  if (DCM_TRUE == Dcm_SesCtrl_IsOemBoot(sesForBoot))
  {
    /* @Trace: SWS_Dcm_00532 */
    /* @Trace: Dcm_SUD_API_30130 */
    schMReturn = SchM_Switch_Dcm_DcmEcuReset(DCM_JUMPTOBOOTLOADER);
  }

  if (DCM_TRUE == Dcm_SesCtrl_IsSysBoot(sesForBoot))
  {
    /* @Trace: SWS_Dcm_00592 */
    /* @Trace: Dcm_SUD_API_30131 */
    schMReturn = SchM_Switch_Dcm_DcmEcuReset(DCM_JUMPTOSYSSUPPLIERBOOTLOADER);
  }

  return schMReturn;
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_ProcessJumpToBootloader                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process to prepare Jump to bootloader          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pSessionCfg                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SesCtrl_ProcessJumpToBootloader(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_SessionConfigConstPtrType pSessionCfg,
  Dcm_NrcPtrType pErrorCode)
{
  Dcm_SesForBootType sesForBoot = pSessionCfg->ucSesForBootLevel;

  Dcm_ProtocolConfigConstPtrType pProtocolCfg;
  Std_ReturnType RetVal = E_NOT_OK;
  pProtocolCfg = Dcm_GetProtocolConfigPtr(pMsgContext->dcmRxPduId);

  if (E_OK != Dcm_SesCtrl_SwitchMode(sesForBoot))
  {
    /* @Trace: SWS_Dcm_01175 */
    /* @Trace: Dcm_SUD_API_30105 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  else if (NULL_PTR == pProtocolCfg)
  {
    /* @Trace: Dcm_SUD_API_30106 */
    *pErrorCode = DCM_E_GENERALREJECT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30107 */
    /* Update programming condition before going to reset */
    Dcm_SesCtrl_UpdateProgCondition(pMsgContext, pSessionCfg);

    if (DCM_TRUE == pProtocolCfg->IsSendRespPendOnRestart)
    {
      /* @Trace: SWS_Dcm_00654 */
      /* @Trace: Dcm_SUD_API_30108 */
      Dcm_SesCtrlState.flag[DCM_SESCTRL_SEND_RCRRP] = DCM_TRUE;
      RetVal = Dcm_SesCtrl_SendNrcRcrrp(pMsgContext, pErrorCode);

      /*Jump to bootloader: suppressPosRspMsgIndicationBit flag
       *  is set to true and NRC78 transmit before.
       *   -> need to send Positive response (Use case 2,4 )*/
      if (RetVal == E_OK)
      {
        /* @Trace: Dcm_SUD_API_30110 */
        boolean isProgResRequired = Dcm_SesCtrl_IsBootNormal(sesForBoot);
        /* FBL need to create a positive response*/
        /*only valid for session where it is the bootloader that sends the final response*/
        Dcm_GddProgConditions.ResponseRequired = isProgResRequired;
      }
    }
    else
    {
      if (DCM_TRUE == Dcm_SesCtrl_IsBootNormal(sesForBoot))
      {
        /* @Trace: SWS_Dcm_00720 */
        /* @Trace: Dcm_SUD_API_30109 */
        Dcm_SesCtrl_ProcessProgCondition(DCM_INITIAL, pMsgContext, pErrorCode);
      }
    }
  } 
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_ProcessStartSession                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process to start change session or Jump to boot     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pSessionCfg                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SesCtrl_ProcessStartSession(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_SessionConfigConstPtrType pSessionCfg,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_30119 */
  Dcm_SesForBootType sesForBoot = pSessionCfg->ucSesForBootLevel;

  if (DCM_NO_BOOT != sesForBoot)
  {
    /* @Trace: Dcm_SUD_API_30120 */
    Dcm_SesCtrl_ProcessJumpToBootloader(pMsgContext, pSessionCfg, pErrorCode);
  }
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_GetPosSuccessAction                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the confirmation action when a positive         **
**                        response is sent successfully                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : sesForBoot                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : actionType                                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Dcm_SesCtrlActionType, DCM_CODE) Dcm_SesCtrl_GetPosSuccessAction(
  Dcm_SesForBootType sesForBoot)
{
  /* @Trace: Dcm_SUD_API_30081 */
  Dcm_SesCtrlActionType actionType = DCM_SESCTRL_NO_ACTION;

  if (DCM_NO_BOOT == sesForBoot)
  {
    /* @Trace: Dcm_SUD_API_30082 */
    actionType = DCM_SESCTRL_SWITCH_SESSION;
  }

  if (DCM_TRUE == Dcm_SesCtrl_IsBootResApp(sesForBoot))
  {
    /* @Trace: SWS_Dcm_01179 */
    /* @Trace: Dcm_SUD_API_30083 */
    actionType = DCM_SESCTRL_RESET_AFTER_POSITIVE;
  }

  return actionType;
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_GetNegSuccessAction                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the confirmation action when a negative         **
**                        response is sent successfully                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : sesForBoot                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : actionType                                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Dcm_SesCtrlActionType, DCM_CODE) Dcm_SesCtrl_GetNegSuccessAction(
  Dcm_SesForBootType sesForBoot)
{
  /* @Trace: Dcm_SUD_API_30076 */
  Dcm_SesCtrlActionType actionType = DCM_SESCTRL_NO_ACTION;

  /* Only do action in case NRC 0x78 is sent successfully */
  if (DCM_TRUE == Dcm_SesCtrlState.flag[DCM_SESCTRL_SEND_RCRRP])
  {
    /* @Trace: Dcm_SUD_API_30077 */
    Dcm_SesCtrlState.flag[DCM_SESCTRL_SEND_RCRRP] = DCM_FALSE;

    if (DCM_TRUE == Dcm_SesCtrl_IsBootResApp(sesForBoot))
    {
      /* @Trace: SWS_Dcm_01177 */
      /* @Trace: Dcm_SUD_API_30078 */
      actionType = DCM_SESCTRL_SEND_POSITIVE;
    }

    if (DCM_TRUE == Dcm_SesCtrl_IsBootNormal(sesForBoot))
    {
      /* @Trace: SWS_Dcm_00535 */
      /* @Trace: Dcm_SUD_API_30079 */
      actionType = DCM_SESCTRL_RESET_AFTER_RCRRP;
    }
  }

  return actionType;
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_GetConfirmAction                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the confirmation action at DSP layer            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : confirmStatus                                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : actionType                                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Dcm_SesCtrlActionType, DCM_CODE) Dcm_SesCtrl_GetConfirmAction(
  Dcm_ConfirmationStatusType confirmStatus)
{
  /* @Trace: Dcm_SUD_API_30070 */
  Dcm_SesCtrlActionType actionType = DCM_SESCTRL_NO_ACTION;
  Dcm_SessionConfigConstPtrType pSesCtrlCfg = Dcm_GetSesCtrlConfig();

  if (NULL_PTR != pSesCtrlCfg)
  {
    if (DCM_RES_POS_OK == confirmStatus)
    {
      /* @Trace: Dcm_SUD_API_30071 */
      actionType = Dcm_SesCtrl_GetPosSuccessAction(pSesCtrlCfg->ucSesForBootLevel);
    }

    if (DCM_RES_NEG_OK == confirmStatus)
    {
      /* @Trace: Dcm_SUD_API_30072 */
      actionType = Dcm_SesCtrl_GetNegSuccessAction(pSesCtrlCfg->ucSesForBootLevel);
    }
  }

  return actionType;
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_DoConfirmAction                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Do the confirmation action after response is sent   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, actionType                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04098 */
static FUNC(void, DCM_CODE) Dcm_SesCtrl_DoConfirmAction(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_SesCtrlActionType actionType)
{
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  switch (actionType)
  {
    case DCM_SESCTRL_SEND_POSITIVE:
      /* @Trace: SWS_Dcm_01177 */
      /* @Trace: Dcm_SUD_API_30065 */
      Dcm_SesCtrl_CheckProcessingDone(pMsgContext, errorCode);
      break;

    case DCM_SESCTRL_SWITCH_SESSION:
      /* @Trace: SWS_Dcm_00311 */
      /* @Trace: Dcm_SUD_API_30066 */
      Dcm_SesCtrl_SwitchSession(pMsgContext);
      break;

    case DCM_SESCTRL_RESET_AFTER_RCRRP:
      /* @Trace: SWS_Dcm_00535 */
      /* @Trace: Dcm_SUD_API_30067 */
      Dcm_SesCtrl_ProcessProgCondition(DCM_INITIAL, pMsgContext, &errorCode);
      Dcm_SesCtrl_CheckProcessingDone(pMsgContext, errorCode);
      break;

    case DCM_SESCTRL_RESET_AFTER_POSITIVE:
      /* @Trace: SWS_Dcm_01179 SWS_Dcm_01181 */
      /* @Trace: Dcm_SUD_API_30068 */
      Dcm_SesCtrl_ProcessProgCondition(DCM_INITIAL, pMsgContext, &errorCode);
      break;

    default:
      /* @Trace: SWS_Dcm_00995 SWS_Dcm_00997 */
      /* @Trace: Dcm_SUD_API_30069 */
      Dcm_SesCtrlState.flag[DCM_SESCTRL_SEND_RCRRP] = DCM_FALSE;
      break;
  }
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_CheckProcessingDone                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Perform final check before send response message    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, errorCode                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SesCtrl_CheckProcessingDone(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode)
{
  if (DCM_TRUE == Dcm_SesCtrl_IsAllFlagsCleared())
  {
    if (DCM_POS_RESP == errorCode)
    {
      /* @Trace: Dcm_SUD_API_30127 */
      Dcm_SesCtrl_UpdatePosResp(pMsgContext);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_30126 */
      Dcm_InternalSetNegResponse(pMsgContext, errorCode);
    }

    /* Send response at main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_SendNrcRcrrp                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The primary function that use to trigger a NRC 0x78 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_SesCtrl_SendNrcRcrrp(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType RetVal = E_OK;
  Dcm_GusMaxNoOfForceRespPend++;

  if (DCM_FALSE == Dcm_ChkNumRespPend(DCM_VARIANT_FUNC_SID, Dcm_GusMaxNoOfForceRespPend))
  {
    /* @Trace: Dcm_SUD_API_30122 */
    *pErrorCode = DCM_E_GENERALREJECT;
    Dcm_GusMaxNoOfForceRespPend = (uint16) DCM_ZERO;

    Dcm_SesCtrl_CancelOperation();
    RetVal = E_NOT_OK;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30123 */
    uint8 serviceId = pMsgContext->idContext & DCM_BIT6_AND_MASK;
    Dcm_SetNegResp(serviceId, DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING);

    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;

    /* Send 0x78 from main function */
    Dcm_GblPduRTransmitResponse = DCM_TRUE;
  }
  return(RetVal);
}
#endif

/*******************************************************************************
**                         Public Functions Definition                        **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dcm_InitSessionControl                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function use to initialize the data of          **
**                        Session Control service                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pConfig                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_InitSessionControl(
  Dcm_ConfigConstPtrType pConfig)
{
  /* @Trace: Dcm_SUD_API_30059 */
  #ifdef DCM_SESSION_CONTROL_SERVICE_ENABLED
  Dcm_SesCtrl_ClearAllFlags();
  Dcm_SesCtrlState.cfgIndex = DCM_MAXVALUE;
  #endif

  DCM_UNUSED(pConfig);
}

/*******************************************************************************
** Function Name        : Dcm_GetSesCtrlConfig                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function use to get the session config          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : pSesCtrlCfg                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(Dcm_SessionConfigConstPtrType, DCM_CODE) Dcm_GetSesCtrlConfig(void)
{
  /* @Trace: Dcm_SUD_API_30047 */
  Dcm_SessionConfigConstPtrType pSesCtrlCfg = NULL_PTR;

  #ifdef DCM_SESSION_CONTROL_SERVICE_ENABLED
  pSesCtrlCfg = Dcm_GetSesCtrlConfigByIndex(Dcm_SesCtrlState.cfgIndex);
  #endif

  return pSesCtrlCfg;
}

/*******************************************************************************
** Function Name        : Dcm_GetSesCtrlConfigByIndex                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function use to get the session config by index **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : SesCtrlIdx                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : pSesCtrlCfg                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(Dcm_SessionConfigConstPtrType, DCM_CODE) Dcm_GetSesCtrlConfigByIndex(
  uint8 SesCtrlIdx)
{
  /* @Trace: Dcm_SUD_API_30049 */
  Dcm_SessionConfigConstPtrType pSesCtrlCfg = NULL_PTR;

  #ifdef DCM_SESSION_CONTROL_SERVICE_ENABLED
  if (SesCtrlIdx < (uint8) DCM_NUM_OF_DIAGSESSIONCONFIG)
  {
    /* @Trace: Dcm_SUD_API_30050 */
    pSesCtrlCfg = &Dcm_GaaDiagSessionConfig[SesCtrlIdx];
  }
  #else
  DCM_UNUSED(SesCtrlIdx);
  #endif

  return pSesCtrlCfg;
}

/*******************************************************************************
** Function Name        : Dcm_GetSesCtrlConfigByType                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function use to get the session config by type  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : SesCtrlType                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : pSesCtrlCfg                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(Dcm_SessionConfigConstPtrType, DCM_CODE) Dcm_GetSesCtrlConfigByType(
  Dcm_SesCtrlType SesCtrlType)
{
  /* @Trace: Dcm_SUD_API_30053 */
  Dcm_SessionConfigConstPtrType pSesCtrlCfg = NULL_PTR;

  #ifdef DCM_SESSION_CONTROL_SERVICE_ENABLED
  for (uint8 SesCtrlIdx = DCM_ZERO; SesCtrlIdx < DCM_NUM_OF_DIAGSESSIONCONFIG; SesCtrlIdx++)
  {
    /* @Trace: Dcm_SUD_API_30056 */
    if (SesCtrlType == Dcm_GaaDiagSessionConfig[SesCtrlIdx].ddSesCtrlLevel)
    {
      /* @Trace: Dcm_SUD_API_30057 */
      Dcm_SesCtrlState.cfgIndex = SesCtrlIdx;
      pSesCtrlCfg = &Dcm_GaaDiagSessionConfig[SesCtrlIdx];
      break;
    }
  }
  #else
  DCM_UNUSED(SesCtrlType);
  #endif

  return pSesCtrlCfg;
}

#if (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
/*******************************************************************************
** Function Name        : Dcm_DcmDiagnosticSessionControl                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The primary function that use to process UDS $10    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04006 SRS_Diag_04198 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmDiagnosticSessionControl(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_00250 */
  Std_ReturnType RetVal = E_OK;

  Dcm_SubServiceIdConfigConstPtrType pSubServiceCfg;
  pSubServiceCfg = Dcm_GetSubServiceConfigPtr(pMsgContext);

  if (NULL_PTR == pSubServiceCfg)
  {
    /* @Trace: Dcm_SUD_API_30034 */
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
  else if (NULL_PTR != pSubServiceCfg->pSubServiceFnc)
  {
    /* @Trace: Dcm_SUD_API_30035 */
    RetVal = pSubServiceCfg->pSubServiceFnc(OpStatus, pMsgContext, pErrorCode);
  }
  else
  {
    Dcm_SesCtrl_ClearAllFlags();

    Dcm_NegativeResponseCodeType ErrorCode = DCM_POS_RESP;
    Dcm_SesCtrlType SesCtrlType = pSubServiceCfg->ucSubServiceId;

    Dcm_SessionConfigConstPtrType pSessionCfg;
    pSessionCfg = Dcm_GetSesCtrlConfigByType(SesCtrlType);

    if (NULL_PTR == pSessionCfg)
    {
      /* @Trace: SWS_Dcm_00307 */
      /* @Trace: Dcm_SUD_API_30037 */
      ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
    }
    else if (DCM_ONE != pMsgContext->reqDataLen)
    {
      /* @Trace: Dcm_SUD_API_30038 */
      ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_30039 */
      Dcm_SesCtrl_ProcessStartSession(pMsgContext, pSessionCfg, &ErrorCode);
    }

    /* @Trace: SWS_Dcm_01178 SWS_Dcm_01183 */
    Dcm_SesCtrl_CheckProcessingDone(pMsgContext, ErrorCode);
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_TxConfirmation                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The primary function that use to process the final  **
**                        action when response is transmitted successfully    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, confirmStatus                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SesCtrl_TxConfirmation(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_ConfirmationStatusType ConfirmStatus)
{
  Dcm_SesCtrlActionType actionType = DCM_SESCTRL_NO_ACTION;

  if (DCM_TRUE == Dcm_GblSendResOnReset)
  {
    /* @Trace: Dcm_SUD_API_30137 */
    /* Reset this variable in the first call of main function */
    Dcm_GblSendResOnReset = DCM_FALSE;

    /* Switch to new session after reset */
    if (DCM_RES_POS_OK == ConfirmStatus)
    {
      /* @Trace: Dcm_SUD_API_30138 */
      actionType = DCM_SESCTRL_SWITCH_SESSION;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30136 */
    actionType = Dcm_SesCtrl_GetConfirmAction(ConfirmStatus);
  }

  /* Do final action for session control processing */
  Dcm_SesCtrl_DoConfirmAction(pMsgContext, actionType);
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_UpdateRespOnReset                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function use to update response when           **
**                        ECU startup from bootloader                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, subfunctionId                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SesCtrl_UpdateRespOnReset(
  Dcm_MsgContextPtrType pMsgContext,
  uint8 subfunctionId)
{
  /* @Trace: Dcm_SUD_API_30143 */
  Dcm_SessionConfigConstPtrType pSessionCfg;
  pSessionCfg = Dcm_GetSesCtrlConfigByType((Dcm_SesCtrlType) subfunctionId);

  if (NULL_PTR != pSessionCfg)
  {
    /* @Trace: Dcm_SUD_API_30144 */
    Dcm_SesCtrl_UpdatePosResp(pMsgContext);
  }
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_ProcessProgPending                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The primary function that use to process            **
**                        Dcm_SetProgCondition in case it return PENDING      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SesCtrl_ProcessProgPending(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_30115 */
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  if ((DCM_TRUE == Dcm_SesCtrlState.flag[DCM_SESCTRL_PENDING]) ||
      (DCM_TRUE == Dcm_SesCtrlState.flag[DCM_SESCTRL_FORCE_PENDNG]))
  {
    if (DCM_TRUE == Dcm_SesCtrlState.flag[DCM_SESCTRL_PENDING])
    {
      /* @Trace: Dcm_SUD_API_30116 */
      Dcm_SesCtrl_ProcessProgCondition(DCM_PENDING, pMsgContext, &errorCode);
    }

    if ((DCM_TRUE == Dcm_GblRespPendConfirmation) &&
        (DCM_TRUE == Dcm_SesCtrlState.flag[DCM_SESCTRL_FORCE_PENDNG]))
    {
      /* @Trace: Dcm_SUD_API_30117 */
      /* Reset confirmation status for next process */
      Dcm_GblRespPendConfirmation = DCM_FALSE;

      Dcm_SesCtrl_ProcessProgCondition(DCM_FORCE_RCRRP_OK, pMsgContext, &errorCode);
    }

    /* @Trace: Dcm_SUD_API_30118 */
    /* Send response immediately in main function */
    Dcm_SesCtrl_CheckProcessingDone(pMsgContext, errorCode);
  }
}

/*******************************************************************************
** Function Name        : Dcm_SesCtrl_CancelOperation                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The primary function that use to cancel             **
**                        the operation of Dcm_SetProgCondition and UDS $10   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SesCtrl_CancelOperation(void)
{
  if ((DCM_TRUE == Dcm_SesCtrlState.flag[DCM_SESCTRL_PENDING]) ||
      (DCM_TRUE == Dcm_SesCtrlState.flag[DCM_SESCTRL_FORCE_PENDNG]))
  {
    /* @Trace: Dcm_SUD_API_30061 */
    Dcm_SesCtrl_ClearAllFlags();
    (void) Dcm_SetProgConditions(DCM_CANCEL, &Dcm_GddProgConditions);
  }
}
#endif

#if (DCM_DSP_STOP_DIAG_SESSION_SERVICE == STD_ON)
/*******************************************************************************
** Function Name        : Dcm_DcmStopDiagnosticSession                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The primary function that use to process ES95486    **
**                        Stop Diagnostic Session Service                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_ES95486_00E_00004 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmStopDiagnosticSession(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;

  if (NULL_PTR != pMsgContext)
  {
    /* @Trace: Dcm_SUD_API_30043 */
    Dcm_SesCtrl_ClearAllFlags();

    /* @Trace: SWS_ES95486_00004 */
    Dcm_DspInternal_DcmStopDiagnosticSession(pMsgContext);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30044 */
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_StopSession_TxConfirmation                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The primary function that use to process the final  **
**                        action when response is transmitted successfully    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, confirmStatus                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_StopSession_TxConfirmation(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_ConfirmationStatusType ConfirmStatus)
{
  if (NULL_PTR != pMsgContext)
  {
    if (DCM_RES_POS_OK == ConfirmStatus)
    {
      /* @Trace: Dcm_SUD_API_30148 */
      Dcm_SesCtrl_SwitchSession(pMsgContext);
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30147 */
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);
  }
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"


/* polyspace-end MISRA2012:8.13 [Justified:Unset] "It will be fixed soon" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
