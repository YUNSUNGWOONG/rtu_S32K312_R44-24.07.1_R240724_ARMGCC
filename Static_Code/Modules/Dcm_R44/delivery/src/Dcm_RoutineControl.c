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
**  SRC-MODULE: Dcm_RoutineControl.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains interfaces for services related to routine **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date            By             Description                      **
********************************************************************************
** 0.0.1      03-Jul-2020     HueKM          Initial Version                  **
** 0.0.2      16-Aug-2020     HueKM          Correct OBD mirror features      **
** 0.0.3      22-Sep-2020     LanhLT         Add access right verification    **
** 0.0.4      13-Oct-2020     HueKM          Changes made as per #15766       **
** 0.0.5      02-Nov-2020     LanhLT         Changes made as per #16832       **
** 0.0.6      16-Dec-2020     HueKM          Mapping SUD API ID as per #17448 **
** 1.0.7      16-Dec-2022     LanhLT         #CP44-1003                       **
** 1.0.9      31-Mar-2023     LanhLT         Refer #CP44-1461                 **
** 1.3.0      31-Dec-2023     EK Kim         Refer #CP44-1515                 **
** 1.3.0_HF1  13-Jan-2024     SY Kim         Refer #45119                     **
** 1.3.1      24-Jan-2024     DanhTQ1        Refer #CP44-3270                 **
** 1.4.0      29-Mar-2024     EK Kim         Refer #CP44-3850                 **
** 1.4.1      01-Apr-2024     DanhTQ1        Refer #CP44-5771                 **
*******************************************************************************/
#include "Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_PCTypes.h"
#include "Dcm_Validate.h"

#if (DCM_ROUTINECONTROL_SERVICE == STD_ON)
#include "Dcm_APIs.h"
#endif

#include "Dcm_Utils.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_ReqRespHandling.h"
#include "Dcm_DspOBDInternals.h"
#include "Dcm_RoutineControl.h"
#include "Dcm_Authentication.h"

/*******************************************************************************
**                     Types and Variables definition                         **
*******************************************************************************/
#if (DCM_ROUTINECONTROL_SERVICE == STD_ON)

typedef struct
{
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pInData;

  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutData;

  uint16 usCfgIndex;

  uint16 usDynDataLen;

  uint8 ucCtrlType;

    /* Start Stop Flag */
  //uint8 ucCurrentRoutineControlType;

  boolean blPending;

  boolean blForcePending;

} Dcm_RoutineStateType;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static VAR(Dcm_RoutineStateType, DCM_VAR) Dcm_RoutineState;

/* Separate all current control state of each RID */
static VAR(uint8, DCM_VAR) Dcm_CurrentRoutineControlState[DCM_NUM_OF_ROUTINE_CONFIG];

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Static Functions Declaration                          **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

static FUNC(boolean, DCM_CODE) Dcm_RidCtrl_GetConfigIndex(
  uint16 routineId,
  Dcm_Uint16PtrType pCfgIndex);

static FUNC(Dcm_RoutineInfoConfigPtrType, DCM_CODE) Dcm_RidCtrl_GetRoutineInfo(
  uint8 ctrlType,
  Dcm_RoutineConfigPtrType pRoutineCfg);

#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_AuthValidate(
  uint8 ctrlType,
  uint16 routineId,
  Dcm_RoutineInfoConfigPtrType pRoutineInfoCfg);
#endif

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_CheckAuthorization(
  Dcm_CommonAuthorizationPtrType pCommonAuthorize);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_CheckFullLength(
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_RoutineInfoConfigPtrType pRoutineInfoCfg);

static FUNC(void, DCM_CODE) Dcm_RidCtrl_UnPackSignal(
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_RoutineInfoConfigPtrType pRoutineInfoCfg,
  Dcm_NrcPtrType pErrorCode);

static FUNC(uint32, DCM_CODE) Dcm_RidCtrl_PackSignal(
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_RoutineInfoConfigPtrType pRoutineInfoCfg);

#if (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_HandleObdRid(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_RoutineConfigPtrType pRoutineCfg);

static FUNC(void, DCM_CODE) Dcm_RidCtrl_GetAvlTidInfo(
  Dcm_MsgContextPtrType pMsgContext);

#if (DCM_ENABLE_OBD_MIRROR == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_GetOtherTidByObdIf(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_RoutineConfigPtrType pRoutineCfg);
#endif

#if (DCM_ENABLE_OBD_MIRROR == STD_OFF)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_GetOtherTidByUdsIf(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_RoutineConfigPtrType pRoutineCfg);
#endif
#endif

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RoutineSequenceCheck(
 uint8 ucNewSubfunction);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_HandleUdsRid(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_RoutineConfigPtrType pRoutineCfg);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_InternalProcess(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_RoutineConfigPtrType pRoutineCfg);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_CheckRoutineType(
  uint16 routineId,
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_RoutineInfoConfigPtrType pRoutineInfoCfg);

static FUNC(void, DCM_CODE) Dcm_RidCtrl_UpdatePosResp(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_RoutineConfigPtrType pRoutineCfg);

static FUNC(void, DCM_CODE) Dcm_RidCtrl_ProcessFunctionCall(
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_SendNrcRcrrp(
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                              Function definition                           **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_GetConfigIndex                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the configuration index of routine array        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : routineId                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pCfgIndex                                           **
**                                                                            **
** Return parameter     : LblRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_RidCtrl_GetConfigIndex(
  uint16 routineId,
  Dcm_Uint16PtrType pCfgIndex)
{
  /* @Trace: Dcm_SUD_API_30184 */
  uint16 LusIdx;
  boolean LblRetVal = DCM_FALSE;

  for (LusIdx = DCM_ZERO; LusIdx < DCM_NUM_OF_ROUTINE_CONFIG; LusIdx++)
  {
    /* @Trace: Dcm_SUD_API_30185 */
    if (routineId == Dcm_GaaRoutineConfig[LusIdx].usRoutineId)
    {
      /* @Trace: Dcm_SUD_API_30186 */
      *pCfgIndex = LusIdx;
      LblRetVal = DCM_TRUE;
      break;
    } 
  }

  return LblRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_GetRoutineInfo                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the routine info configuration by control type  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ctrlType, pRoutineCfg                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LpRoutineInfoCfg                                    **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_RoutineInfoConfigPtrType, DCM_CODE) Dcm_RidCtrl_GetRoutineInfo(
  uint8 ctrlType,
  Dcm_RoutineConfigPtrType pRoutineCfg)
{
  Dcm_RoutineInfoConfigPtrType LpRoutineInfoCfg;

  switch (ctrlType)
  {
    case DCM_RID_CTRL_START:
      /* @Trace: Dcm_SUD_API_30200 */
      LpRoutineInfoCfg = pRoutineCfg->pRoutineStart;
      break;

    case DCM_RID_CTRL_STOP:
      /* @Trace: Dcm_SUD_API_30201 */
      LpRoutineInfoCfg = pRoutineCfg->pRoutineStop;
      break;

    case DCM_RID_CTRL_REQUEST:
      /* @Trace: Dcm_SUD_API_30202 */
      LpRoutineInfoCfg = pRoutineCfg->pRoutineRequestResult;
      break;

    default:
      /* @Trace: Dcm_SUD_API_30203 */
      LpRoutineInfoCfg = NULL_PTR;
      break;
  }

  return LpRoutineInfoCfg;
}

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_AuthValidate                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check the access right for routine control service  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ctrlType, routineId, pRoutineInfoCfg                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_AuthValidate(
  uint8 ctrlType,
  uint16 routineId,
  Dcm_RoutineInfoConfigPtrType pRoutineInfoCfg)
{
  /* @Trace: Dcm_SUD_API_30159 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  Dcm_AuthenticationRoleType LddRole;
  Dcm_MemCopy(LddRole, pRoutineInfoCfg->ddRoutineRole, DCM_AUTHENTICATION_ROLE_SIZE);

  if (DCM_FALSE == Dcm_ValidateAccessRights(LddRole))
  {
    #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_RID_CONFIGURED == STD_ON)
    /* @Trace: Dcm_SUD_API_30160 */
    uint8 LaaRecord[DCM_THREE];
    uint8 LucBitShift = ctrlType - (uint8) DCM_ONE;

    LaaRecord[DCM_ZERO] = DCM_U16_HI_BYTE(routineId);
    LaaRecord[DCM_ONE] = DCM_U16_LO_BYTE(routineId);
    LaaRecord[DCM_TWO] = DCM_ONE << LucBitShift;

    if (DCM_FALSE == Dcm_ValidateAccessRightsWithWLRid(LaaRecord, DCM_THREE))
    #endif
    {
      /* @Trace: Dcm_SUD_API_30161 */
      LddErrorCode = DCM_E_AUTHENTICATIONREQUIRED;
    }
  }

  DCM_UNUSED(ctrlType);
  DCM_UNUSED(routineId);
  return LddErrorCode;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_CheckAuthorization                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate session, security and mode condition       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : pCommonAuthorize                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_CheckAuthorization(
  Dcm_CommonAuthorizationPtrType pCommonAuthorize)
{
  /* @Trace: Dcm_SUD_API_30166 */
  boolean LblResult = DCM_TRUE;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if (NULL_PTR != pCommonAuthorize)
  {
    LblResult = Dcm_DsdValidateSession(
      pCommonAuthorize->pSessionLevel, pCommonAuthorize->ucSessionCount);

    if (DCM_TRUE == LblResult)
    {
      LblResult = Dcm_DsdValidateSecurity(
        pCommonAuthorize->pSecurityLevel, pCommonAuthorize->ucSecurityCount);

      if (DCM_TRUE == LblResult)
      {
        #if (DCM_MODE_RULE == STD_ON)
        /* @Trace: Dcm_SUD_API_30171 */
        LddErrorCode = Dcm_CheckModeRule(
          pCommonAuthorize->blModeRuleConfigured, pCommonAuthorize->ucModeRuleIndex);
        #endif
      }
      else
      {
        /* @Trace: Dcm_SUD_API_30170 */
        LddErrorCode = DCM_E_SECURITYACCESSDENIED;
      }
    }
    else
    {
      /* @Trace: Dcm_SUD_API_30168 */
      LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_CheckFullLength                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Execute the full length check for routine request   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : pMsgContext, pRoutineInfoCfg                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_CheckFullLength(
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_RoutineInfoConfigPtrType pRoutineInfoCfg)
{
  /* @Trace: Dcm_SUD_API_30172 */
  uint16 LusSignalIdx;
  uint32 LulTotalSignalLen = DCM_ZERO;

  boolean LblDynamicLength = DCM_FALSE;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  uint16 LusNumOfSignal = pRoutineInfoCfg->usNumOfInSignal;
  Dcm_RoutineSignalPtrType LpRoutineSignal = pRoutineInfoCfg->pRoutineInSignal;

  if (LpRoutineSignal != NULL_PTR)
  {
    /* @Trace: Dcm_SUD_API_30173 */
    for (LusSignalIdx = DCM_ZERO; LusSignalIdx < LusNumOfSignal; LusSignalIdx++)
    {
      /* Only last signal may have a variable length */
      if (DCM_DATA_TYPE_VARIABLE_LENGTH == LpRoutineSignal[LusSignalIdx].ucSignalType)
      {
        /* @Trace: Dcm_SUD_API_30174 */
        LblDynamicLength = DCM_TRUE;
      }

      /* @Trace: Dcm_SUD_API_30175 */
      LulTotalSignalLen += LpRoutineSignal[LusSignalIdx].usSignalSize;
    }
  }

  if (DCM_TRUE == LblDynamicLength)
  {
    if ((pMsgContext->reqDataLen > (DCM_THREE + LulTotalSignalLen)) ||
        /* Input data length for signal has type VARIABLE_LENGTH (last signal) can be zero */
        (pMsgContext->reqDataLen <
        /* DCM_THREE [Sub service (1) + RID (2)] + maximum data length - length of variable signal */
        (DCM_THREE + LulTotalSignalLen - LpRoutineSignal[LusNumOfSignal - 1U].usSignalSize)))
    {
      /* @Trace: Dcm_SUD_API_30177 */
      LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
  }
  else
  {
    if (pMsgContext->reqDataLen != (DCM_THREE + LulTotalSignalLen))
    {
      /* @Trace: Dcm_SUD_API_30176 */
      LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_UnPackSignal                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert the request message to routine input data   **
**                        based on the signal data type                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pRoutineInfoCfg                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_RidCtrl_UnPackSignal(
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_RoutineInfoConfigPtrType pRoutineInfoCfg,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_30251 */
  #if (DCM_ROUTINE_IN_SIGNAL_ONE_BYTE == STD_ON)
  uint16 LusData8Idx = DCM_ZERO;
  #endif
  
  #if (DCM_ROUTINE_IN_SIGNAL_TWO_BYTE == STD_ON)
  uint16 LusData16Idx = DCM_ZERO;
  #endif

  #if (DCM_ROUTINE_IN_SIGNAL_FOUR_BYTE == STD_ON)
  uint16 LusData32Idx = DCM_ZERO;
  #endif

  uint16 LusSignalIdx;
  Dcm_PackUnPackType LddUnPackSignal;

  uint16 LusNumOfSignal = pRoutineInfoCfg->usNumOfInSignal;
  Dcm_RoutineSignalPtrType LpRoutineSignal = pRoutineInfoCfg->pRoutineInSignal;

  if (NULL_PTR != LpRoutineSignal)
  {
    /* @Trace: Dcm_SUD_API_30252 */
    for (LusSignalIdx = DCM_ZERO; LusSignalIdx < LusNumOfSignal; LusSignalIdx++)
    {
      /* @Trace: Dcm_SUD_API_30253 */
      uint8 LucByteType = LpRoutineSignal[LusSignalIdx].ucSignalByteType;
      uint16 LusByteIndex = DCM_THREE + LpRoutineSignal[LusSignalIdx].usSignalPos;

      Dcm_Uint8PtrType LpRequestData = &pMsgContext->reqData[LusByteIndex];
      LddUnPackSignal.blByteConversion = LpRoutineSignal[LusSignalIdx].blByteConversion;

      /* Only last signal may have a variable length */
      if (DCM_DATA_TYPE_VARIABLE_LENGTH == LpRoutineSignal[LusSignalIdx].ucSignalType)
      {
        /* @Trace: Dcm_SUD_API_30255 */
        if(pMsgContext->reqDataLen >= LusByteIndex)
        {
          LddUnPackSignal.usSignalSize = (uint16) (pMsgContext->reqDataLen - LusByteIndex);
          Dcm_RoutineState.usDynDataLen = LddUnPackSignal.usSignalSize;
        }
        else
        {
          /* If length of variable signal is 0, NRC 0x13 shall be sent */
          *pErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
      }
      else
      {
        /* @Trace: Dcm_SUD_API_30254 */
        LddUnPackSignal.usSignalSize = LpRoutineSignal[LusSignalIdx].usSignalSize;
      }

      if(*pErrorCode == DCM_POS_RESP)
      {
        if (DCM_ONE == LucByteType)
        {
          #if (DCM_ROUTINE_IN_SIGNAL_ONE_BYTE == STD_ON)
          /* @Trace: Dcm_SUD_API_30256 */
          Dcm_RoutineState.pInData = &Dcm_GaaRoutineInData8[LusData8Idx];
          LusData8Idx += LddUnPackSignal.usSignalSize;
          #endif
        }
        else if (DCM_TWO == LucByteType)
        {
          #if (DCM_ROUTINE_IN_SIGNAL_TWO_BYTE == STD_ON)
          /* @Trace: Dcm_SUD_API_30257 */
          Dcm_RoutineState.pInData = &Dcm_GaaRoutineInData16[LusData16Idx];
          LusData16Idx += LddUnPackSignal.usSignalSize >> DCM_ONE;
          #endif
        }
        else
        {
          #if (DCM_ROUTINE_IN_SIGNAL_FOUR_BYTE == STD_ON)
          /* @Trace: Dcm_SUD_API_30258 */
          Dcm_RoutineState.pInData = &Dcm_GaaRoutineInData32[LusData32Idx];
          LusData32Idx += LddUnPackSignal.usSignalSize >> DCM_TWO;
          #endif
        }

        /* @Trace: SWS_Dcm_00641 */
        uint8 LucUnPackFuncIdx = LpRoutineSignal[LusSignalIdx].ucUnPackFuncIndex;
        if (LucUnPackFuncIdx < DCM_NUM_OF_UNPACK_FUNC_CONFIG)
        {
          /* @Trace: Dcm_SUD_API_30260 */
          Dcm_GaaUnPackFunc[LucUnPackFuncIdx].pUnPackFunc(
            Dcm_RoutineState.pInData,
            LpRequestData,
            &LddUnPackSignal);
        }
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_PackSignal                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert the routine output data to response message **
**                        based on the signal data type                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pRoutineInfoCfg                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LulTotalSignalLen                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(uint32, DCM_CODE) Dcm_RidCtrl_PackSignal(
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_RoutineInfoConfigPtrType pRoutineInfoCfg)
{
  /* @Trace: Dcm_SUD_API_30225 */
  #if (DCM_ROUTINE_OUT_SIGNAL_ONE_BYTE == STD_ON)
  uint16 LusData8Idx = DCM_ZERO;
  #endif
  
  #if (DCM_ROUTINE_OUT_SIGNAL_TWO_BYTE == STD_ON)
  uint16 LusData16Idx = DCM_ZERO;
  #endif

  #if (DCM_ROUTINE_OUT_SIGNAL_FOUR_BYTE == STD_ON)
  uint16 LusData32Idx = DCM_ZERO;
  #endif

  uint16 LusSignalIdx;
  uint32 LulTotalSignalLen = DCM_ZERO;
  Dcm_PackUnPackType LddPackSignal;

  uint16 LusNumOfSignal = pRoutineInfoCfg->usNumOfOutSignal;
  Dcm_RoutineSignalPtrType LpRoutineSignal = pRoutineInfoCfg->pRoutineOutSignal;

  if (NULL_PTR != LpRoutineSignal)
  {
    /* @Trace: Dcm_SUD_API_30226 */
    for (LusSignalIdx = DCM_ZERO; LusSignalIdx < LusNumOfSignal; LusSignalIdx++)
    {
      /* @Trace: Dcm_SUD_API_30227 */
      uint8 LucByteType = LpRoutineSignal[LusSignalIdx].ucSignalByteType;
      uint16 LusByteIndex = DCM_THREE + LpRoutineSignal[LusSignalIdx].usSignalPos;

      Dcm_Uint8PtrType LpResponseData = &pMsgContext->resData[LusByteIndex];
      LddPackSignal.blByteConversion = LpRoutineSignal[LusSignalIdx].blByteConversion;

      /* Only last parameters in RID may have a variable length */
      if (DCM_DATA_TYPE_VARIABLE_LENGTH == LpRoutineSignal[LusSignalIdx].ucSignalType)
      {
        /* @Trace: Dcm_SUD_API_30229 */
        LulTotalSignalLen += Dcm_RoutineState.usDynDataLen;
        LddPackSignal.usSignalSize = Dcm_RoutineState.usDynDataLen;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_30228 */
        LulTotalSignalLen += LpRoutineSignal[LusSignalIdx].usSignalSize;
        LddPackSignal.usSignalSize = LpRoutineSignal[LusSignalIdx].usSignalSize;
      }

      if (DCM_ONE == LucByteType)
      {
        #if (DCM_ROUTINE_OUT_SIGNAL_ONE_BYTE == STD_ON)
        /* @Trace: Dcm_SUD_API_30230 */
        Dcm_RoutineState.pOutData = &Dcm_GaaRoutineOutData8[LusData8Idx];
        LusData8Idx += LddPackSignal.usSignalSize;
        #endif
      }
      else if (DCM_TWO == LucByteType)
      {
        #if (DCM_ROUTINE_OUT_SIGNAL_TWO_BYTE == STD_ON)
        /* @Trace: Dcm_SUD_API_30231 */
        Dcm_RoutineState.pOutData = &Dcm_GaaRoutineOutData16[LusData16Idx];
        LusData16Idx += LddPackSignal.usSignalSize >> DCM_ONE;
        #endif
      }
      else
      {
        #if (DCM_ROUTINE_OUT_SIGNAL_FOUR_BYTE == STD_ON)
        /* @Trace: Dcm_SUD_API_30232 */
        Dcm_RoutineState.pOutData = &Dcm_GaaRoutineOutData32[LusData32Idx];
        LusData32Idx += LddPackSignal.usSignalSize >> DCM_TWO;
        #endif
      }

      /* @Trace: SWS_Dcm_00641 */
      uint8 LucPackFuncIdx = LpRoutineSignal[LusSignalIdx].ucPackFuncIndex;
      if (LucPackFuncIdx < DCM_NUM_OF_PACK_FUNC_CONFIG)
      {
        /* @Trace: Dcm_SUD_API_30234 */
        Dcm_GaaPackFunc[LucPackFuncIdx].pPackFunc(
          Dcm_RoutineState.pOutData,
          LpResponseData,
          &LddPackSignal);
      }
    }
  }

  return LulTotalSignalLen;
}

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_HandleObdRid                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main processing function for RID inside OBD range   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pRoutineCfg                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_HandleObdRid(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_RoutineConfigPtrType pRoutineCfg)
{
  /* @Trace: Dcm_SUD_API_30204 */
  uint8 LucIdStatus;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  Dcm_Uint8PtrType LpReqData = pMsgContext->reqData;
  Dcm_Uint8PtrType LpResData = pMsgContext->resData;
  
  /* Get the type of OBD TID */
  LucIdStatus = Dcm_DspGetAvailibiltyIDStatus(
    DCM_GET_TID, &LpReqData[DCM_TWO], DCM_ONE, DCM_EIGHT);

  if (DCM_AVAIL_ID == LucIdStatus)
  {
    /* @Trace: Dcm_SUD_API_30205 */
    Dcm_RidCtrl_GetAvlTidInfo(pMsgContext);
  }
  else
  if (DCM_OTHER_PID == LucIdStatus)
  {
    #if (DCM_ENABLE_OBD_MIRROR == STD_ON)
    /* @Trace: Dcm_SUD_API_30207 */
    LddErrorCode = Dcm_RidCtrl_GetOtherTidByObdIf(pMsgContext, pRoutineCfg);
    #else
    /* @Trace: Dcm_SUD_API_30208 */
    LddErrorCode = Dcm_RidCtrl_GetOtherTidByUdsIf(pMsgContext, pRoutineCfg);
    #endif
  }
  else
  {
    /* @Trace: SWS_Dcm_01391 */
    /* @Trace: Dcm_SUD_API_30206 */
    LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_30209 */
    /* Copy sub-function and RID */
    Dcm_MemCopy(LpResData, LpReqData, DCM_THREE);

    /* Add three byte include sub-function and RID */
    pMsgContext->resDataLen += DCM_THREE;
  }

  return LddErrorCode;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_GetAvlTidInfo                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the data of availability TID                    **
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
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_RidCtrl_GetAvlTidInfo(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_30183 */
  Dcm_Uint8PtrType LpOutBuffer = &pMsgContext->resData[DCM_THREE];
  Dcm_Uint8ConstPtrType LpTidBuffer = &pMsgContext->reqData[DCM_TWO];

  /* @Trace: SWS_Dcm_01390 */
  (void) Dcm_DspReadOBD_AvlInfo(
    LpTidBuffer, LpOutBuffer, DCM_FIVE, DCM_ONE, DCM_GET_TID);

  /* Supported TID include four data byte */
  pMsgContext->resDataLen = DCM_FOUR;

  /* Remove TID byte from output buffer */
  Dcm_MemCopy(LpOutBuffer, &LpOutBuffer[DCM_ONE], DCM_FOUR);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_GetOtherTidByObdIf                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the TID info using OBD interface                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pRoutineCfg                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if ((DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) && \
  (DCM_ENABLE_OBD_MIRROR == STD_ON))
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_GetOtherTidByObdIf(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_RoutineConfigPtrType pRoutineCfg)
{
  uint8 LucIdx = DCM_ZERO;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  Std_ReturnType LddRetVal;
  Dcm_MsgLenType LddResLength;

  Dcm_Uint8PtrType LpInBuffer = &pMsgContext->reqData[DCM_THREE];
  Dcm_Uint8PtrType LpOutBuffer = &pMsgContext->resData[DCM_THREE];
  Dcm_Uint8ConstPtrType LpTidBuffer = &pMsgContext->reqData[DCM_TWO];

  /* @Trace: SWS_Dcm_01330 SWS_Dcm_01333 */
  /* In case OBD MIRROR is set to TRUE, Dcm will always use OBD interface */
  if (E_OK == Dcm_GetIDIndex(DCM_GET_TID, LpTidBuffer[DCM_ZERO], &LucIdx))
  {
    /* Get the configured length for other TID info */
    LddResLength = Dcm_GaaRequestControlConfig[LucIdx].ucRequestControlOutBufferSize;

    /* @Trace: SWS_Dcm_01393 */
    Dcm_MemClear(LpOutBuffer, LddResLength);

    /* @Trace: SWS_Dcm_01332 */
    LddRetVal = Dcm_GaaRequestControlConfig[LucIdx].pReqControlFnc(
      LpOutBuffer, LpInBuffer);

    if (E_OK == LddRetVal)
    {
      /* @Trace: Dcm_SUD_API_30192 */
      pMsgContext->resDataLen = LddResLength;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_30191 */
      LddErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30189 */
    LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }

  DCM_UNUSED(pRoutineCfg);
  return LddErrorCode;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_GetOtherTidByUdsIf                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the TID info using UDS interface                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pRoutineCfg                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if ((DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) && \
  (DCM_ENABLE_OBD_MIRROR == STD_OFF))
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_GetOtherTidByUdsIf(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_RoutineConfigPtrType pRoutineCfg)
{
  /* @Trace: Dcm_SUD_API_30194 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  uint16 LusDynDataLen = DCM_ZERO;
  Dcm_Uint8PtrType LpOutBuffer = &pMsgContext->resData[DCM_THREE];

  /* @Trace: SWS_Dcm_01331 SWS_Dcm_01392 */
  if (NULL_PTR != pRoutineCfg->pRoutineStart)
  {
    /* @Trace: Dcm_SUD_API_30195 */
    LddRetVal = Dcm_APIs_RoutineControlFunc(
      DCM_RID_CTRL_START, pRoutineCfg->usRoutineId,
      DCM_INITIAL, &LusDynDataLen, &LddErrorCode);
  }

  if (E_OK == LddRetVal)
  {
    /* @Trace: SWS_Dcm_00701 */
    /* @Trace: Dcm_SUD_API_30197 */
    pMsgContext->resDataLen = DCM_ONE;
    LpOutBuffer[DCM_ZERO] = pRoutineCfg->ucRoutineInfoByte;
  }
  else
  {
    /* @Trace: SWS_Dcm_01394 */
    /* @Trace: Dcm_SUD_API_30196 */
    LddErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return LddErrorCode;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_HandleUdsRid                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main processing function for RID outside OBD range  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pRoutineCfg                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_HandleUdsRid(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_RoutineConfigPtrType pRoutineCfg)
{
  /* @Trace: Dcm_SUD_API_30211 */
  Dcm_NegativeResponseCodeType LddErrorCode;
  uint8 LucCtrlType = pMsgContext->reqData[DCM_ZERO] & DCM_SUBFUNCTION_MASK;

  Dcm_RoutineInfoConfigPtrType LpRoutineInfoCfg;
  LpRoutineInfoCfg = Dcm_RidCtrl_GetRoutineInfo(LucCtrlType, pRoutineCfg);

  if (NULL_PTR != LpRoutineInfoCfg)
  {
    /* @Trace: SWS_Dcm_01139 */
    /* @Trace: Dcm_SUD_API_30213 */
    LddErrorCode = Dcm_RidCtrl_CheckRoutineType(
      pRoutineCfg->usRoutineId, pMsgContext, LpRoutineInfoCfg);
  }
  else
  {
    /* @Trace: SWS_Dcm_00869 */
    /* @Trace: Dcm_SUD_API_30212 */
    LddErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    LddErrorCode = Dcm_RoutineSequenceCheck(LucCtrlType);
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_30214 */
    /* Update routine control type */
    Dcm_RoutineState.ucCtrlType = LucCtrlType;

    /* @Trace: SWS_Dcm_00590 */
    Dcm_RidCtrl_UnPackSignal(pMsgContext, LpRoutineInfoCfg, &LddErrorCode);
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* Subsequent checks have to be performed by the SWC */
    Dcm_RidCtrl_ProcessFunctionCall(DCM_INITIAL, pMsgContext, &LddErrorCode);
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_InternalProcess                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal process function for UDS RID               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pRoutineCfg                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_InternalProcess(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_RoutineConfigPtrType pRoutineCfg)
{
  uint16 LusRoutineId = pRoutineCfg->usRoutineId;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if ((LusRoutineId >= DCM_RID_OBD_LOW_RANGE) && 
      (LusRoutineId <= DCM_RID_OBD_HIGH_RANGE))
  {
    /* @Trace: SWS_Dcm_01194 */
    #if (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON)
    /* @Trace: Dcm_SUD_API_30218 */
    LddErrorCode = Dcm_RidCtrl_HandleObdRid(pMsgContext, pRoutineCfg);
    #else
    /* @Trace: Dcm_SUD_API_30220 */
    LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
    #endif
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30219 */
    LddErrorCode = Dcm_RidCtrl_HandleUdsRid(pMsgContext, pRoutineCfg);
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_CheckRoutineType                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate request message and unpack input signal    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : routineId, pMsgContext, pRoutineInfoCfg             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RidCtrl_CheckRoutineType(
  uint16 routineId,
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_RoutineInfoConfigPtrType pRoutineInfoCfg)
{
  Dcm_NegativeResponseCodeType LddErrorCode;

  #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
  /* @Trace: Dcm_SUD_API_30180 */
  /* @Trace: SWS_Dcm_01555 SWS_Dcm_01556 SWS_Dcm_01557 */
  uint8 LucCtrlType = pMsgContext->reqData[DCM_ZERO] & DCM_SUBFUNCTION_MASK;
  LddErrorCode = Dcm_RidCtrl_AuthValidate(LucCtrlType, routineId, pRoutineInfoCfg);

  if (DCM_POS_RESP == LddErrorCode)
  #endif
  {
    /* @Trace: SWS_Dcm_00570 SWS_Dcm_00571 SWS_Dcm_01169 SWS_Dcm_01170 SWS_Dcm_01171 */
    /* @Trace: Dcm_SUD_API_30181 */
    LddErrorCode = Dcm_RidCtrl_CheckAuthorization(pRoutineInfoCfg->pCommonAuthorization);
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: SWS_Dcm_01140 */
    /* @Trace: Dcm_SUD_API_30182 */
    LddErrorCode = Dcm_RidCtrl_CheckFullLength(pMsgContext, pRoutineInfoCfg);
  }

  DCM_UNUSED(routineId);
  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_UpdatePosResp                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Pack output signal and update positive response     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pRoutineCfg                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_RidCtrl_UpdatePosResp(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_RoutineConfigPtrType pRoutineCfg)
{
  /* @Trace: Dcm_SUD_API_30262 */
  uint32 LulTotalSignalLen = DCM_ZERO;

  Dcm_RoutineInfoConfigPtrType LpRoutineInfoCfg;
  LpRoutineInfoCfg = Dcm_RidCtrl_GetRoutineInfo(Dcm_RoutineState.ucCtrlType, pRoutineCfg);

  if (NULL_PTR != LpRoutineInfoCfg)
  {
    /* @Trace: Dcm_SUD_API_30263 */
    LulTotalSignalLen = Dcm_RidCtrl_PackSignal(pMsgContext, LpRoutineInfoCfg);
  }

  pMsgContext->resDataLen = DCM_THREE + LulTotalSignalLen;
  Dcm_MemCopy(pMsgContext->resData, pMsgContext->reqData, DCM_THREE);
}

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_ProcessFunctionCall                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call routine API and process return value           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : opStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_RidCtrl_ProcessFunctionCall(
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Dcm_RoutineConfigPtrType LpRoutineCfg;
  LpRoutineCfg = &Dcm_GaaRoutineConfig[Dcm_RoutineState.usCfgIndex];

  /* @Trace: SWS_Dcm_01442 SWS_Dcm_01443 */
  /* @Trace: SWS_Dcm_01360 SWS_Dcm_01361 SWS_Dcm_01141 */ 
  /* @Trace: SWS_Dcm_01362 SWS_Dcm_01363 SWS_Dcm_01364 */
  /* @Trace: SWS_Dcm_00400 SWS_Dcm_00402 SWS_Dcm_00404 */
  Std_ReturnType LddRetVal = Dcm_APIs_RoutineControlFunc(
    Dcm_RoutineState.ucCtrlType, LpRoutineCfg->usRoutineId,
    opStatus, &Dcm_RoutineState.usDynDataLen, pErrorCode);

  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] It depends on request.*/
  switch (LddRetVal)
  {
    case E_OK:
      /* @Trace: Dcm_SUD_API_30243 */
      /* Clear the error code variable */
      *pErrorCode = DCM_POS_RESP;

      Dcm_RoutineState.blPending = DCM_FALSE;
      Dcm_RoutineState.blForcePending = DCM_FALSE;
      
      if ((Dcm_RoutineState.ucCtrlType == DCM_RID_CTRL_REQUEST) &&
         (Dcm_CurrentRoutineControlState[Dcm_RoutineState.usCfgIndex] == DCM_RID_CTRL_STOP))
      {
        /* Perious state is stop and requested RequestResult, state will be clear */
        Dcm_CurrentRoutineControlState[Dcm_RoutineState.usCfgIndex] = DCM_ZERO;
      }
      else 
      {
        /* update sequence processing state */
        Dcm_CurrentRoutineControlState[Dcm_RoutineState.usCfgIndex] = Dcm_RoutineState.ucCtrlType;
      }
      

      /* @Trace: SWS_Dcm_00401 SWS_Dcm_00403 SWS_Dcm_00405 */
      Dcm_RidCtrl_UpdatePosResp(pMsgContext, LpRoutineCfg);
      break;

    case E_NOT_OK:
      /* @Trace: SWS_Dcm_00668 SWS_Dcm_00670 SWS_Dcm_00672 */
      /* @Trace: Dcm_SUD_API_30244 */
      Dcm_RoutineState.blPending = DCM_FALSE;
      Dcm_RoutineState.blForcePending = DCM_FALSE;
      break;

    case DCM_E_PENDING:
      /* @Trace: Dcm_SUD_API_30245 */
      Dcm_RoutineState.blPending = DCM_TRUE;
      break;

    /* polyspace +2 DEFECT:DEAD_CODE [Justified:Low] "Because of SWS_Dcm_00669 SWS_Dcm_00671 SWS_Dcm_00673.
    So, Returned value DCM_E_FORCE_RCRRP must be checked." */
    case DCM_E_FORCE_RCRRP:
      /* @Trace: SWS_Dcm_00669 SWS_Dcm_00671 SWS_Dcm_00673 */
      /* @Trace: Dcm_SUD_API_30246 */
      Dcm_RoutineState.blForcePending = DCM_TRUE;
      Dcm_SendNrcRcrrp(pMsgContext, pErrorCode);
      break;

    default:
      /* @Trace: Dcm_SUD_API_30247 */
      *pErrorCode = DCM_E_GENERALREJECT;
      
      Dcm_RoutineState.blPending = DCM_FALSE;
      Dcm_RoutineState.blForcePending = DCM_FALSE;
      break;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] It depends on request.*/
}

/*******************************************************************************
** Function Name        : Dcm_SendNrcRcrrp                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Send NRC 0x78 due to return value of routine API    **
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
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SendNrcRcrrp(
  Dcm_MsgContextConstPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Dcm_GusMaxNoOfForceRespPend++;

  if (DCM_FALSE == Dcm_ChkNumRespPend(DCM_VARIANT_FUNC_SID, Dcm_GusMaxNoOfForceRespPend))
  {
    /* @Trace: Dcm_SUD_API_30266 */
    *pErrorCode = DCM_E_GENERALREJECT;
    Dcm_GusMaxNoOfForceRespPend = (uint16) DCM_ZERO;

    Dcm_RidCtrl_CancelOperation();
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30267 */
    /* Get service id for response message */
    uint8 LucServiceId = (pMsgContext->idContext) & DCM_SID_MASK;

    Dcm_SetNegResp(
      LucServiceId, DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING);

    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;

    /* Send 0x78 from main function */    
    Dcm_GblPduRTransmitResponse = DCM_TRUE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_InitData                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Intitalize the data for all operation of SID 0x31   **
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
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_RidCtrl_InitData(void)
{
  for (uint16 LucIndex = 0x00; LucIndex < DCM_NUM_OF_ROUTINE_CONFIG; LucIndex++)
  {
    Dcm_CurrentRoutineControlState[LucIndex] = DCM_ZERO;
  }

  /* @Trace: Dcm_SUD_API_30216 */
  Dcm_RoutineState.pInData = NULL_PTR;

  Dcm_RoutineState.pOutData = NULL_PTR;

  Dcm_RoutineState.usCfgIndex = DCM_ZERO;

  Dcm_RoutineState.usDynDataLen = DCM_ZERO;

  Dcm_RoutineState.ucCtrlType = DCM_ZERO;

  Dcm_RoutineState.blPending = DCM_FALSE;

  Dcm_RoutineState.blForcePending = DCM_FALSE;

}

/*******************************************************************************
** Function Name        : Dcm_DcmRoutineControl                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main processing function for UDS 0x31 service       **
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
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04224 */
/* @Trace: SWS_Dcm_00257 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmRoutineControl(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  Dcm_SubServiceIdConfigConstPtrType LpSubServiceCfg;
  LpSubServiceCfg = Dcm_GetSubServiceConfigPtr(pMsgContext);

  if ((NULL_PTR != LpSubServiceCfg) && (NULL_PTR != LpSubServiceCfg->pSubServiceFnc))
  {
    /* @Trace: Dcm_SUD_API_30150 */
    LddRetVal = LpSubServiceCfg->pSubServiceFnc(OpStatus, pMsgContext, pErrorCode);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30151 */
    uint16 LusCfgIndex = DCM_ZERO;
    uint16 LusRoutineId = DCM_ZERO;

    Dcm_RoutineState.blPending = DCM_FALSE;
    Dcm_RoutineState.blForcePending = DCM_FALSE;

    /* Get 2 byte routine identifier from request message */
    DCM_GET_RID_FROM_REQUEST(LusRoutineId, pMsgContext->reqData);

    if (DCM_FALSE == Dcm_RidCtrl_GetConfigIndex(LusRoutineId, &LusCfgIndex))
    {
      /* @Trace: SWS_Dcm_00568 */
      /* @Trace: Dcm_SUD_API_30152 */
      LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
      Dcm_RoutineConfigPtrType LpRoutineCfg = &Dcm_GaaRoutineConfig[LusCfgIndex];

      if (DCM_FALSE == LpRoutineCfg->blRoutineUsed)
      {
        /* @Trace: SWS_Dcm_00569 */
        /* @Trace: Dcm_SUD_API_30154 */
        LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_30155 */
        /* Update configuration index for further process */
        Dcm_RoutineState.usCfgIndex = LusCfgIndex;
        LddErrorCode = Dcm_RidCtrl_InternalProcess(pMsgContext, LpRoutineCfg);
      }
    }

    if ((DCM_FALSE == Dcm_RoutineState.blPending) &&
        (DCM_FALSE == Dcm_RoutineState.blForcePending))
    {
      if (DCM_POS_RESP != LddErrorCode)
      {
        /* @Trace: Dcm_SUD_API_30157 */
        Dcm_InternalSetNegResponse(pMsgContext, LddErrorCode);
      }

      /* @Trace: Dcm_SUD_API_30156 */
      /* Send response at next cycle of Main Function */
      Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
    }
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_CancelOperation                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Cancel operation of routine function                **
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
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_RidCtrl_CancelOperation(void)
{
  /* @Trace: Dcm_SUD_API_30164 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  Dcm_RoutineConfigPtrType LpRoutineCfg;
  LpRoutineCfg = &Dcm_GaaRoutineConfig[Dcm_RoutineState.usCfgIndex];

  if ((DCM_TRUE == Dcm_RoutineState.blPending) ||
      (DCM_TRUE == Dcm_RoutineState.blForcePending))
  {
    /* @Trace: Dcm_SUD_API_30165 */
    Dcm_RoutineState.blPending = DCM_FALSE;
    Dcm_RoutineState.blForcePending = DCM_FALSE;

    /* @Trace: SWS_Dcm_01413 */
    (void) Dcm_APIs_RoutineControlFunc(
      Dcm_RoutineState.ucCtrlType, LpRoutineCfg->usRoutineId,
      DCM_CANCEL, &Dcm_RoutineState.usDynDataLen, &LddErrorCode);
  }
}

/*******************************************************************************
** Function Name        : Dcm_RidCtrl_PendingOperation                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process routine function in case pending returned   **
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
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_RidCtrl_PendingOperation(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_30237 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if ((DCM_TRUE == Dcm_RoutineState.blPending) ||
      (DCM_TRUE == Dcm_RoutineState.blForcePending))
  {
    if (DCM_TRUE == Dcm_RoutineState.blPending)
    {
      /* @Trace: Dcm_SUD_API_30238 */
      Dcm_RidCtrl_ProcessFunctionCall(
        DCM_PENDING, pMsgContext, &LddErrorCode);
    }

    if ((DCM_TRUE == Dcm_GblRespPendConfirmation) &&
        (DCM_TRUE == Dcm_RoutineState.blForcePending))
    {
      /* @Trace: Dcm_SUD_API_30239 */
      /* Reset confirmation status for next process */
      Dcm_GblRespPendConfirmation = DCM_FALSE;

      Dcm_RidCtrl_ProcessFunctionCall(
        DCM_FORCE_RCRRP_OK, pMsgContext, &LddErrorCode);
    }

    if ((DCM_FALSE == Dcm_RoutineState.blPending) &&
        (DCM_FALSE == Dcm_RoutineState.blForcePending))
    {
      if (DCM_POS_RESP != LddErrorCode)
      {
        /* @Trace: Dcm_SUD_API_30240 */
        Dcm_InternalSetNegResponse(pMsgContext, LddErrorCode);
      }

      /* @Trace: Dcm_SUD_API_30241 */
      /* Response will be sent at transmit response function */
      Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_RoutineSequenceCheck                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process routine function in case pending returned   **
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
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_RoutineSequenceCheck(
 uint8 ucNewSubfunction)
{
  Dcm_NegativeResponseCodeType retVal;
  uint8 LucCurrentState;

  LucCurrentState = Dcm_CurrentRoutineControlState[Dcm_RoutineState.usCfgIndex];
  retVal = DCM_POS_RESP;

  if (DCM_RID_CTRL_STOP == ucNewSubfunction)
  {
    /**
     * Stop -> Stop
     * Stop when nerver start
     */
    if ((DCM_RID_CTRL_STOP == LucCurrentState) || (DCM_ZERO == LucCurrentState))
    {
      retVal = DCM_E_REQUESTSEQUENCEERROR;
    }
  } 
  else if (DCM_RID_CTRL_REQUEST == ucNewSubfunction)
  {
    /*RID never start*/
    if (DCM_ZERO == LucCurrentState)
    {
      retVal = DCM_E_REQUESTSEQUENCEERROR;
    }
  }
  else
  {
    /**
     * Start -> Start : Accept this sequence in BSW scope, depend on appicaiton code
     * Stop -> Start
     * RequestResult -> Start
     */
  }
  return retVal;
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
