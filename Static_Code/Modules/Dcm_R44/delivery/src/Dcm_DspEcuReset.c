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
**                                                                            **
**  SRC-MODULE: Dcm_DspEcuReset.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains interfaces for ECU Reset Service           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                          Revision History                                  **
********************************************************************************
** Revision   Date           By               Description                     **
********************************************************************************
** 0.0.1      28-Nov-2019    HueKM           Initial Version                  **
** 0.0.2      13-Oct-2020    HueKM           Changes made as per #15766       **
** 0.0.3      02-Nov-2020    HueKM           Changes made as per #16832       **
** 0.0.4      04-Dec-2020    HueKM           Change to support ES96590        **
** 0.0.5      16-Dec-2020    HueKM           Mapping SUD API ID as per #17448 **
** 1.0.9      31-Mar-2023    LanhLT          Refer #CP44-1819                 **
** 1.0.11     28-Apr-2023    SY Kim          Refer #CP44-1876                 **
** 1.1.1      30-Oct-2023    DanhTQ1         Refer #CP44-2730                 **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_DspEcuReset.h"

#include "Dcm_Ram.h"
#include "Dcm_Config.h"
#include "Dcm_Validate.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_ReqRespHandling.h"

/*******************************************************************************
**                     Types and Variables definition                         **
*******************************************************************************/
#if (DCM_ECURESET_SERVICE == STD_ON)

#define DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET      ((uint8) 0x04)
#define DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET     ((uint8) 0x05)

typedef enum 
{
  DCM_ECU_RESET_SEND_RCRRP,
  DCM_ECU_RESET_PENDING, 
  DCM_ECU_RESET_FORCE_RCRRP, 
  DCM_ECU_RESET_FLAG_NUM
} Dcm_EcuResetFlagType;

typedef struct 
{
  uint8 cfgIndex;
  boolean flag[DCM_ECU_RESET_FLAG_NUM];
} Dcm_EcuResetStateType;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
static VAR(Dcm_EcuResetStateType, DCM_VAR) Dcm_EcuResetState;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                              Function definition                           **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

static FUNC(Dcm_EcuResetCfgPtrType, DCM_CODE) Dcm_EcuReset_GetConfigByType(
  uint8 resetType);

static FUNC(void, DCM_CODE) Dcm_EcuReset_ClearAllFlags(void);

static FUNC(boolean, DCM_CODE) Dcm_EcuReset_IsAllFlagsCleared(void);

static FUNC(boolean, DCM_CODE) Dcm_EcuReset_IsProgRequireResp(
  Dcm_EcuResetResponseType respType);

static FUNC(void, DCM_CODE) Dcm_EcuReset_UpdatePosResp(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_EcuReset_UpdateProgCondition(
  Dcm_MsgContextConstPtrType pMsgContext, 
  Dcm_EcuResetCfgPtrType pEcuResetCfg);

static FUNC(void, DCM_CODE) Dcm_EcuReset_ProcessProgCondition(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_EcuReset_SwitchMode(
  uint8 resetType);

static FUNC(void, DCM_CODE) Dcm_EcuReset_InternalProcess(
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_EcuResetCfgPtrType pEcuResetCfg,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_EcuReset_DoConfirmAction(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_EcuResetResponseType respType,
  Dcm_ConfirmationStatusType confirmStatus);

static FUNC(void, DCM_CODE) Dcm_EcuReset_CheckProcessingDone(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode);

static FUNC(void, DCM_CODE) Dcm_EcuReset_SendNrcRcrrp(
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

/*******************************************************************************
** Function Name        : Dcm_EcuReset_GetConfigByType                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function use to get the Ecu Reset Configuration **
**                        by the reset type                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : resetType                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LpEcuResetCfg                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_EcuResetCfgPtrType, DCM_CODE) Dcm_EcuReset_GetConfigByType(
  uint8 resetType)
{
  /* @Trace: Dcm_SUD_API_31020 */
  uint8 LucIdx;
  Dcm_EcuResetCfgPtrType LpEcuResetCfg = NULL_PTR;

  for (LucIdx = DCM_ZERO; LucIdx < (uint8) DCM_NUM_OF_ECURESETCONFIG; LucIdx++)
  {
    /* @Trace: Dcm_SUD_API_31021 */
    if (resetType == Dcm_GaaEcuResetConfig[LucIdx].ucResetType)
    {
      /* @Trace: Dcm_SUD_API_31022 */
      Dcm_EcuResetState.cfgIndex = LucIdx;
      LpEcuResetCfg = &Dcm_GaaEcuResetConfig[LucIdx];
      break;
    }
  }

  return LpEcuResetCfg;
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_ClearAllFlags                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Clear all operation flag of Ecu Reset Service       **
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
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_EcuReset_ClearAllFlags(void)
{
  /* @Trace: Dcm_SUD_API_31013 */
  uint16 LusIdx;

  for (LusIdx = DCM_ZERO; LusIdx < (uint16) DCM_ECU_RESET_FLAG_NUM; LusIdx++) 
  {
    /* @Trace: Dcm_SUD_API_31014 */
    Dcm_EcuResetState.flag[LusIdx] = DCM_FALSE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_IsAllFlagsCleared                      **
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
** Return parameter     : LblRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_EcuReset_IsAllFlagsCleared(void) 
{
  /* @Trace: Dcm_SUD_API_31037 */
  boolean LblRetVal = DCM_FALSE;

  if ((DCM_FALSE == Dcm_GblReset) &&
      (DCM_FALSE == Dcm_EcuResetState.flag[DCM_ECU_RESET_SEND_RCRRP]) &&
      (DCM_FALSE == Dcm_EcuResetState.flag[DCM_ECU_RESET_PENDING]) &&
      (DCM_FALSE == Dcm_EcuResetState.flag[DCM_ECU_RESET_FORCE_RCRRP]))
  {
    /* @Trace: Dcm_SUD_API_31038 */
    LblRetVal = DCM_TRUE;
  }

  return LblRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_IsProgRequireResp                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function use to check whether the UDS service   **
**                        0x11 is required a response on restart time or not  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : respType                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : respRequired                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_EcuReset_IsProgRequireResp(
  Dcm_EcuResetResponseType respType)
{
  /* @Trace: Dcm_SUD_API_31040 */
  boolean LblRespRequired = DCM_FALSE;

  if (AFTER_RESET == respType)
  {
    /* @Trace: Dcm_SUD_API_31041 */
    LblRespRequired = DCM_TRUE;
  }

  return LblRespRequired;
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_UpdatePosResp                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function use to update positive response of     **
**                        UDS Ecu Reset service                               **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_EcuReset_UpdatePosResp(
  Dcm_MsgContextPtrType pMsgContext)
{
  uint8 LucResetType = pMsgContext->reqData[DCM_ZERO];

  if (DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET == LucResetType)
  {
    /* @Trace: Dcm_SUD_API_31066 */
    pMsgContext->resDataLen = DCM_TWO;
    pMsgContext->resData[DCM_ZERO] = LucResetType;

    /* @Trace: SWS_Dcm_00589 */
    pMsgContext->resData[DCM_ONE] = DCM_POWERDOWN_TIME;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31067 */
    pMsgContext->resDataLen = DCM_ONE;
    pMsgContext->resData[DCM_ZERO] = LucResetType;
  }
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_UpdateProgCondition                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function use to update the progress condition   **
**                        before Ecu execute a reset                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pEcuResetCfg                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_EcuReset_UpdateProgCondition(
  Dcm_MsgContextConstPtrType pMsgContext, 
  Dcm_EcuResetCfgPtrType pEcuResetCfg)
{
  /* @Trace: Dcm_SUD_API_31068 */
  uint8 LucResetType = pEcuResetCfg->ucResetType;
  Dcm_SecLevelType LddSecurityLevel = DCM_SEC_LEV_LOCKED;
  Dcm_EcuResetResponseType LddRespType = pEcuResetCfg->ucResToEcuReset;
  
  uint16 LusPduIdIdx = pMsgContext->dcmRxPduId;
  Dcm_PduIdTablePtrType LpPduIdTable = &Dcm_GaaPduIdTableConfig[LusPduIdIdx];

  /* Update connection id and tester address */
  Dcm_GddProgConditions.ConnectionId = LpPduIdTable->RxConnectionId;
  Dcm_GddProgConditions.TesterAddress = LpPduIdTable->ConfigTesterAddress;

  /* Update service id and sub-function id */
  Dcm_GddProgConditions.Sid = DCM_ECURESET;
  Dcm_GddProgConditions.SubFncId = LucResetType;

  /* Clear application updated and reprogramming flags */
  Dcm_GddProgConditions.ApplUpdated = DCM_FALSE;
  Dcm_GddProgConditions.ReprogramingRequest = DCM_TRUE;

  /* Update response requried flag */
  boolean LblProgResRequired = Dcm_EcuReset_IsProgRequireResp(LddRespType);

  if (DCM_TRUE == pMsgContext->msgAddInfo.suppressPosResponse)
  {
    Dcm_GddProgConditions.ResponseRequired = DCM_FALSE;
  }
  else
  {
    Dcm_GddProgConditions.ResponseRequired = LblProgResRequired;
  }

  /* Update current security level */
  (void) Dcm_GetSecurityLevel(&LddSecurityLevel);
  Dcm_GddProgConditions.SecurityLevel = LddSecurityLevel;
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_ProcessProgCondition                   **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_EcuReset_ProcessProgCondition(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal;

  Dcm_EcuReset_ClearAllFlags();
  LddRetVal = Dcm_SetProgConditions(OpStatus, &Dcm_GddProgConditions);

  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00543, the function Dcm_SetProgConditions has return 4 values.
    So, Dcm must be implement to cover all return value of function Dcm_SetProgConditions." */
  switch (LddRetVal)
  {
    case E_OK:
      /* @Trace: SWS_Dcm_00834 */
      /* @Trace: Dcm_SUD_API_31044 */
      Dcm_GblReset = DCM_TRUE;
      (void) SchM_Switch_Dcm_DcmEcuReset(DCM_EXECUTE);
      break;

    case DCM_E_PENDING:
      /* @Trace: SWS_Dcm_01184 */
      /* @Trace: Dcm_SUD_API_31045 */
      Dcm_EcuResetState.flag[DCM_ECU_RESET_PENDING] = DCM_TRUE;
      break;

    case DCM_E_FORCE_RCRRP:
      /* @Trace: Dcm_SUD_API_31046 */
      Dcm_EcuResetState.flag[DCM_ECU_RESET_FORCE_RCRRP] = DCM_TRUE;
      Dcm_EcuReset_SendNrcRcrrp(pMsgContext, pErrorCode);
      break;
    
    default:
      /* @Trace: SWS_Dcm_00271*/
      /* @Trace: Dcm_SUD_API_31047 */
      *pErrorCode = DCM_E_GENERALREJECT;
      break;
  }
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00543, the function Dcm_SetProgConditions has return 4 values.
    So, Dcm must be implement to cover all return value of function Dcm_SetProgConditions." */
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_SwitchMode                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function use to switch to new EcuReset Mode     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : resetType                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddSchMReturn                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_EcuReset_SwitchMode(
  uint8 resetType)
{
  /* @Trace: Dcm_SUD_API_31055 */
  Std_ReturnType LddSchMReturn = E_NOT_OK;

  switch (resetType)
  {
    case DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET:
      #if (DCM_RAPID_POWER_SHUTDOWN_CONFIGURED == STD_ON)
      /* @Trace: SWS_Dcm_00818 */
      /* @Trace: Dcm_SUD_API_31056 */
      LddSchMReturn = SchM_Switch_Dcm_DcmModeRapidPowerShutDown(
        DCM_ENABLE_RAPIDPOWERSHUTDOWN);
      #endif
      break;

    case DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET:
      #if (DCM_RAPID_POWER_SHUTDOWN_CONFIGURED == STD_ON)
      /* @Trace: SWS_Dcm_00818 */
      /* @Trace: Dcm_SUD_API_31057 */
      LddSchMReturn = SchM_Switch_Dcm_DcmModeRapidPowerShutDown(
        DCM_DISABLE_RAPIDPOWERSHUTDOWN);
      #endif
      break;

    default:
      /* @Trace: SWS_Dcm_00373 */
      /* @Trace: Dcm_SUD_API_31058 */
      LddSchMReturn = SchM_Switch_Dcm_DcmEcuReset(resetType);
      break;
  }

  return LddSchMReturn;
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_InternalProcess                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function use to check whether what the type     **
**                        of response is sent:                                **
**                        + Final response or Response pending (0x78)         **
**                        + Send before reset or after reset                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pEcuResetCfg                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04098 */
static FUNC(void, DCM_CODE) Dcm_EcuReset_InternalProcess(
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_EcuResetCfgPtrType pEcuResetCfg,
  Dcm_NrcPtrType pErrorCode)
{
  uint8 LucResetType = pEcuResetCfg->ucResetType;
  Dcm_EcuResetResponseType LddRespType = pEcuResetCfg->ucResToEcuReset;

  /* Get the protocol configuration */
  Dcm_ProtocolConfigConstPtrType LpProtocolCfg;
  LpProtocolCfg = Dcm_GetProtocolConfigPtr(pMsgContext->dcmRxPduId);

  if (E_OK != Dcm_EcuReset_SwitchMode(LucResetType))
  {
    /* @Trace: Dcm_SUD_API_31032 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  else if (NULL_PTR == LpProtocolCfg)
  {
    /* @Trace: Dcm_SUD_API_31033 */
    *pErrorCode = DCM_E_GENERALREJECT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31034 */
    /* Update programming condition before going to reset */
    Dcm_EcuReset_UpdateProgCondition(pMsgContext, pEcuResetCfg);

    if (DCM_TRUE == LpProtocolCfg->IsSendRespPendOnRestart)
    {
      /* @Trace: Dcm_SUD_API_31035 */
      Dcm_EcuResetState.flag[DCM_ECU_RESET_SEND_RCRRP] = DCM_TRUE;

      /* @Trace: SWS_Dcm_01425 */
      Dcm_EcuReset_SendNrcRcrrp(pMsgContext, pErrorCode);
    }
    else
    {
      if (AFTER_RESET == LddRespType)
      {
        /* @Trace: SWS_Dcm_01423 */
        /* @Trace: Dcm_SUD_API_31036 */
        Dcm_EcuReset_ProcessProgCondition(DCM_INITIAL, pMsgContext, pErrorCode);
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_DoConfirmAction                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function will implement the confirm action      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, respType, confirmStatus                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_EcuReset_DoConfirmAction(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_EcuResetResponseType respType,
  Dcm_ConfirmationStatusType confirmStatus)
{
  /* @Trace: Dcm_SUD_API_31024 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if (DCM_RES_POS_OK == confirmStatus)
  {
    if (AFTER_RESET == respType)
    {
      Dcm_EcuReset_ProcessProgCondition(
        DCM_INITIAL, pMsgContext, &LddErrorCode);
    }
    else
    {
      Dcm_GblExecuteECUReset = DCM_TRUE;
    }

  }

  if (DCM_TRUE == Dcm_EcuResetState.flag[DCM_ECU_RESET_SEND_RCRRP]) 
  {
    /* @Trace: Dcm_SUD_API_31026 */
    Dcm_EcuResetState.flag[DCM_ECU_RESET_SEND_RCRRP] = DCM_FALSE;

    if (DCM_RES_NEG_OK == confirmStatus)
    {
      if (AFTER_RESET == respType)
      {
        /* @Trace: Dcm_SUD_API_31028 */
        Dcm_EcuReset_ProcessProgCondition(
          DCM_INITIAL, pMsgContext, &LddErrorCode);
        
        Dcm_EcuReset_CheckProcessingDone(pMsgContext, LddErrorCode);
      }
      else
      {
        /* @Trace: Dcm_SUD_API_31027 */
        Dcm_EcuReset_CheckProcessingDone(pMsgContext, LddErrorCode);
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_CheckProcessingDone                    **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_EcuReset_CheckProcessingDone(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode)
{
  if ((DCM_TRUE == Dcm_EcuReset_IsAllFlagsCleared()))
  {
    if (DCM_POS_RESP == errorCode)
    {
      /* @Trace: Dcm_SUD_API_31010 */
      Dcm_EcuReset_UpdatePosResp(pMsgContext);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_31011 */
      Dcm_InternalSetNegResponse(pMsgContext, errorCode);
    }

    /* @Trace: Dcm_SUD_API_31012 */
    /* Send response at main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_SendNrcRcrrp                           **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_EcuReset_SendNrcRcrrp(
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Dcm_GusMaxNoOfForceRespPend++;

  if (DCM_FALSE == Dcm_ChkNumRespPend(
    DCM_VARIANT_FUNC_SID, Dcm_GusMaxNoOfForceRespPend))
  {
    /* @Trace: Dcm_SUD_API_31053 */
    *pErrorCode = DCM_E_GENERALREJECT;
    Dcm_GusMaxNoOfForceRespPend = (uint16) DCM_ZERO;

    Dcm_EcuReset_CancelOperation();
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31054 */
    uint8 LucServiceId = pMsgContext->idContext & DCM_BIT6_AND_MASK;
    Dcm_SetNegResp(LucServiceId, DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING);

    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;

    /* Send 0x78 from main function */
    Dcm_GblPduRTransmitResponse = DCM_TRUE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_InitData                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function use to initialize the data of          **
**                        Ecu Reset service                                   **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_EcuReset_InitData(void)
{
  /* @Trace: Dcm_SUD_API_31030 */
  Dcm_EcuReset_ClearAllFlags();
  Dcm_EcuResetState.cfgIndex = DCM_MAXVALUE;
}

/*******************************************************************************
** Function Name        : Dcm_DcmECUResetService                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The primary function that use to process UDS $11    **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04216 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmECUResetService(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_00260 */
  Std_ReturnType LddRetVal = E_OK;

  Dcm_SubServiceIdConfigConstPtrType LpSubServiceCfg;
  LpSubServiceCfg = Dcm_GetSubServiceConfigPtr(pMsgContext);

  if (NULL_PTR == LpSubServiceCfg)
  {
    /* @Trace: Dcm_SUD_API_31002 */
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
  else if (NULL_PTR != LpSubServiceCfg->pSubServiceFnc)
  {
    /* @Trace: Dcm_SUD_API_31003 */
    LddRetVal = LpSubServiceCfg->pSubServiceFnc(
      OpStatus, pMsgContext, pErrorCode);
  }
  else
  {
    Dcm_EcuResetCfgPtrType LpEcuResetCfg;
    uint8 LucResetType = LpSubServiceCfg->ucSubServiceId;
    Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

    Dcm_EcuReset_ClearAllFlags();
    LpEcuResetCfg = Dcm_EcuReset_GetConfigByType(LucResetType);

    if (NULL_PTR == LpEcuResetCfg)
    {
      /* @Trace: Dcm_SUD_API_31005 */
      LddErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
    }
    else if (DCM_ONE != pMsgContext->reqDataLen)
    {
      /* @Trace: Dcm_SUD_API_31006 */
      LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_31007 */
      Dcm_EcuReset_InternalProcess(pMsgContext, LpEcuResetCfg, &LddErrorCode);
    }

    /* @Trace: SWS_Dcm_01424 */
    Dcm_EcuReset_CheckProcessingDone(pMsgContext, LddErrorCode);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_TxConfirmation                         **
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
** Input Parameters     : confirmStatus, pMsgContext                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_EcuReset_TxConfirmation(
  Dcm_ConfirmationStatusType confirmStatus,
  Dcm_MsgContextPtrType pMsgContext)
{
  uint8 LucResetType;
  Dcm_EcuResetCfgPtrType LpEcuResetCfg;

  if (DCM_TRUE == Dcm_GblSendResOnReset)
  {
    /* @Trace: Dcm_SUD_API_31062 */
    Dcm_GblSendResOnReset = DCM_FALSE;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31061 */
    LucResetType = pMsgContext->reqData[DCM_ZERO];
    LpEcuResetCfg = Dcm_EcuReset_GetConfigByType(LucResetType);

    if (NULL_PTR != LpEcuResetCfg)
    {
      /* @Trace: SWS_Dcm_00594 */
      /* @Trace: Dcm_SUD_API_31063 */
      Dcm_EcuReset_DoConfirmAction(
        pMsgContext, LpEcuResetCfg->ucResToEcuReset, confirmStatus);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_UpdateRespOnReset                      **
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
** Input Parameters     : pMsgContext, resetType                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_EcuReset_UpdateRespOnReset(
  Dcm_MsgContextPtrType pMsgContext, 
  uint8 resetType)
{
  /* @Trace: Dcm_SUD_API_31069 */
  Dcm_EcuResetCfgPtrType LpEcuResetCfg;
  LpEcuResetCfg = Dcm_EcuReset_GetConfigByType(resetType);

  if (NULL_PTR != LpEcuResetCfg)
  {
    /* @Trace: Dcm_SUD_API_31070 */
    Dcm_EcuReset_UpdatePosResp(pMsgContext);
  }
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_ProcessProgPending                     **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_EcuReset_ProcessProgPending(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_31048 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if ((DCM_TRUE == Dcm_EcuResetState.flag[DCM_ECU_RESET_PENDING]) ||
      (DCM_TRUE == Dcm_EcuResetState.flag[DCM_ECU_RESET_FORCE_RCRRP]))
  {
    /* @Trace: SWS_Dcm_01184 */
    if (DCM_TRUE == Dcm_EcuResetState.flag[DCM_ECU_RESET_PENDING])
    {
      /* @Trace: Dcm_SUD_API_31049 */
      Dcm_EcuReset_ProcessProgCondition(
        DCM_PENDING, pMsgContext, &LddErrorCode);
    }
    
    if ((DCM_TRUE == Dcm_GblRespPendConfirmation) &&
        (DCM_TRUE == Dcm_EcuResetState.flag[DCM_ECU_RESET_FORCE_RCRRP]))
    {
      /* @Trace: Dcm_SUD_API_31050 */
      /* Reset confirmation status for next process */
      Dcm_GblRespPendConfirmation = DCM_FALSE;

      Dcm_EcuReset_ProcessProgCondition(
        DCM_FORCE_RCRRP_OK, pMsgContext, &LddErrorCode);
    }
    
    /* @Trace: Dcm_SUD_API_31051 */
    Dcm_EcuReset_CheckProcessingDone(pMsgContext, LddErrorCode);
  }
}

/*******************************************************************************
** Function Name        : Dcm_EcuReset_CancelOperation                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The primary function that use to cancel             **
**                        the operation of Dcm_SetProgCondition and UDS $11   **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_EcuReset_CancelOperation(void)
{
  /* @Trace: SWS_Dcm_00120 */
  /* @Trace: Dcm_SUD_API_31073 */
  if ((DCM_TRUE == Dcm_EcuResetState.flag[DCM_ECU_RESET_PENDING]) ||
      (DCM_TRUE == Dcm_EcuResetState.flag[DCM_ECU_RESET_FORCE_RCRRP]))
  {
    /* @Trace: Dcm_SUD_API_31009 */
    Dcm_EcuReset_ClearAllFlags();
    (void) Dcm_SetProgConditions(DCM_CANCEL, &Dcm_GddProgConditions);
  }
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
