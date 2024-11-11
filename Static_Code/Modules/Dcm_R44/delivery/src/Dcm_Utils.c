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
**  SRC-MODULE: Dcm_Utils.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Utils functions for Dcm                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     31-Dec-2019   LanhLT         AR440 Implementation                **
** 0.0.2     19-Mar-2020   LanhLT         Add Dcm_ChkUDSProtocolPriority()    **
** 0.0.3     19-May-2019   LanhLT         Add Dcm_IsOBDRequestProcessing()    **
** 0.0.4     16-Aug-2020   HueKM          Add Dcm_GetPeriodicTxPduInfo()      **
** 0.0.5     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.6     02-Nov-2020   LanhLT         Changes made as per #16832          **
** 0.0.7     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.8     18-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
** 1.1.0     13-Oct-2023   LanhLT         Refer #CP44-2675, #CP44-3106        **
** 1.3.0     31-Dec-2023   EK Kim         Refer #CP44-3198                    **
** 1.3.0_HF1 13-Jan-2024   SY Kim         Refer #45119                        **
** 1.4.1     01-Apr-2024   DanhTQ1        Refer #CP44-3362                    **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Config.h"
#include "Dcm_Utils.h"
#include "Dcm_Authentication.h"
#include "Dcm_DspServices.h"

#include "PduR_Dcm.h"
#include "BswM_Dcm.h"

#if ((DCM_MODE_CONDITION == STD_ON) && (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
#include "Dcm_APIs.h"
#endif


#if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) \
      || (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))
#define DCM_COM_CONTROL_SERVICES_ENABLED
#endif

#define DCM_START_SEC_CODE
#include "MemMap.h"

#if (DCM_MODE_RULE == STD_ON)
/* @Trace: SWS_Dcm_00942 will be implemented in generator */
static FUNC(boolean, DCM_CODE) Dcm_IsValidModeRule(
  Dcm_Uint8PtrType pModeRuleIndex);

static FUNC(boolean, DCM_CODE) Dcm_IsValidModeCondition(
  uint8 ModeCondIndex);

static FUNC(boolean, DCM_CODE) Dcm_IsValidBswOrSwcModeCondition(
  Dcm_ModeConditionConfigConstPtrType pModeCondCfg);

static FUNC(boolean, DCM_CODE) Dcm_IsValidSwcSRDataElementCondition(
  Dcm_ModeConditionConfigConstPtrType pModeCondCfg);
#endif

/* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 MISRA2012:8.13 [Justified:Unset] "It will be fixed soon" */

/*******************************************************************************
** Function Name        : Dcm_Internal_GetDemClientId                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to get Dem clientId from current protocol  **
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
** Return parameter     : DemClientId                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddRxPduId                 **
**                                                                            **
**                        Function(s) : Dcm_GetProtocolConfigPtr              **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01047 */
FUNC(uint8, DCM_CODE) Dcm_Internal_GetDemClientId(void)
{
  Dcm_ProtocolConfigConstPtrType pProtocolCfg;
  pProtocolCfg = Dcm_GetProtocolConfigPtr(Dcm_GddRxPduId);

  /* @Trace: Dcm_SUD_API_11346 Dcm_SUD_API_11347 */
  uint8 DemClientId = (NULL_PTR != pProtocolCfg) ?
    pProtocolCfg->DemClientId : DEM_CLIENTID_UNSET;

  return DemClientId;
}

/*******************************************************************************
** Function Name        : Dcm_CheckModeRule                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check current mode rule                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : IsModeRuleConfigured, ModeRuleIndex                 **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ErrorCode                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_IsValidModeRule                   **
**                                                                            **
*******************************************************************************/
#if (DCM_MODE_RULE == STD_ON)
FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckModeRule(
  boolean IsModeRuleConfigured
  , Dcm_ModeType ModeRuleIndex)
{
  /* @Trace: Dcm_SUD_API_11227 */
  Dcm_ModeType ValidModeRuleIndex = ModeRuleIndex;
  Dcm_NegativeResponseCodeType ErrorCode = DCM_POS_RESP;

  if (DCM_TRUE == IsModeRuleConfigured)
  {
    /* @Trace: Dcm_SUD_API_11226 */
    boolean Valid = Dcm_IsValidModeRule(&ValidModeRuleIndex);

    #if (DCM_DSP_MODE_RULE_NRC == STD_ON)
    /* @Trace: SWS_Dcm_00812 SWS_Dcm_00782 */
    Dcm_NegativeResponseCodeType Nrc = Dcm_GaaModeRuleConfig[
      ValidModeRuleIndex].NrcValue;
    #else
    /* @Trace: SWS_Dcm_00815 */
    Dcm_NegativeResponseCodeType Nrc = DCM_E_CONDITIONSNOTCORRECT;
    #endif

    CHK_RET_VAL(DCM_FALSE == Valid, ErrorCode, Nrc);
  }

  return ErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_IsValidModeRule                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function validate available mode rule               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pModeRuleIndex                                      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ChkVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_IsValidModeCondition              **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsValidModeRule(Dcm_Uint8PtrType pModeRuleIndex)
{
  Dcm_ModeRuleConfigConstPtrType pModeRuleCfg = &Dcm_GaaModeRuleConfig[*pModeRuleIndex];
  Dcm_LogicalOperatorType LogicalOperator = pModeRuleCfg->LogicalOperator;

  /* @Trace: SWS_Dcm_00808 */
  /* @Trace: Dcm_SUD_API_11284 Dcm_SUD_API_11285 */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "LogicalOperator depends on configuration."*/
  boolean ChkVal = (DCM_AND == LogicalOperator) ? DCM_TRUE : DCM_FALSE;

  /* @Trace: SWS_Dcm_00811 */
  uint8 idxCondStart = pModeRuleCfg->ucIndexOfModeConditionIndexArray;
  uint8 idxCondEnd = idxCondStart + pModeRuleCfg->ucDcmNoOfModeCondnArg;
  boolean ValidCond;
  for (uint8 idx = idxCondStart; idx < idxCondEnd; idx++)
  {
    /* @Trace: Dcm_SUD_API_11286 */
    ValidCond = Dcm_IsValidModeCondition(idx);
    if (((DCM_AND == LogicalOperator) && (DCM_FALSE == ValidCond)) // first fail
         || ((DCM_OR == LogicalOperator) && (DCM_TRUE == ValidCond))) // first success
    {
      /* @Trace: Dcm_SUD_API_11287 Dcm_SUD_API_11288 */
      ChkVal = (DCM_AND == LogicalOperator) ? DCM_FALSE : DCM_TRUE;
      break;
    }
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "LogicalOperator depends on configuration."*/

  #if (DCM_MODE_RULE_INDEX == STD_ON)
  /* @Trace: Dcm_SUD_API_11291 */
  uint8 idxRuleStart = pModeRuleCfg->ucIndexOfModeRuleIndexArray;
  uint8 idxRuleEnd = idxRuleStart + pModeRuleCfg->ucDcmNoOfModeRuleArg;
  boolean ValidRule;
  uint8 idxChk;
  uint8 idxFail = *pModeRuleIndex;
  for (uint8 idx = idxRuleStart; idx < idxRuleEnd; idx++)
  {
    /* @Trace: Dcm_SUD_API_11292 */
    idxChk = Dcm_GaaModeRuleIndexArray[idx];
    ValidRule = Dcm_IsValidModeRule(&idxChk);

    /* @Trace: SWS_Dcm_00813 SWS_Dcm_00814 */
    CHK_RET_VAL(DCM_FALSE == ValidRule, idxFail, idxChk);

    if ((DCM_AND == LogicalOperator && (DCM_FALSE == ValidRule)) // first fail
         || (DCM_OR == LogicalOperator && DCM_TRUE == ValidRule)) // first success
    {
      /* @Trace: Dcm_SUD_API_11294 Dcm_SUD_API_11296 */
      ChkVal = (DCM_AND == LogicalOperator) ? DCM_FALSE : DCM_TRUE;
      break;
    }
  }

  /* @Trace: Dcm_SUD_API_11298 */
  CHK_RET_VAL(idxFail != *pModeRuleIndex, *pModeRuleIndex, idxFail);
  #endif

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsValidModeCondition                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function validate available mode condition          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : ModeCondIndex                                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ChkVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_IsValidBswOrSwcModeCondition      **
**                                      Dcm_IsValidCertificateElementCondition**
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsValidModeCondition(uint8 ModeCondIndex)
{
  /* @Trace: Dcm_SUD_API_10197 */
  boolean ChkVal = DCM_FALSE;

  uint8 idx = Dcm_GaaModeConditionIndexArray[ModeCondIndex];
  Dcm_ModeConditionConfigConstPtrType pModeCondCfg = &Dcm_GaaModeConditionConfig[idx];
  Dcm_CompareModeType CompareMode = pModeCondCfg->CompareMode;

  if (DCM_COMPARE_BSW_OR_SWC_MODE == CompareMode)
  {
    /* @Trace: Dcm_SUD_API_20270 */
    ChkVal = Dcm_IsValidBswOrSwcModeCondition(pModeCondCfg);
  }

  #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
  else if (DCM_COMPARE_CERT_ELE == CompareMode)
  {
    /* @Trace: SRS_Diag_04232 */
    /* @Trace: Dcm_SUD_API_20271 */
    ChkVal = Dcm_IsValidCertificateElementCondition(pModeCondCfg);
  }
  #endif

  else if (DCM_COMPARE_SWC_SR_DATA_ELE == CompareMode)
  {
    ChkVal = Dcm_IsValidSwcSRDataElementCondition(pModeCondCfg);
  }
  else 
  {

  }
  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ModeConditionSRReadPIDData                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function validate mode condition with S/R PID       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : ucDsPPIDDataIndex                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaDcmDspPidData           **
**                        Dcm_GaaPIDBooleanFunc, Dcm_GaaPIDUint8Func          **
**                        Dcm_GaaPIDUint8NFunc, Dcm_GaaPIDUint16Func          **
**                        Dcm_GaaPIDUint16NFunc, Dcm_GaaPIDUint32Func         **
**                        Dcm_GaaPIDUint32NFunc                               ** 
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
#if (DCM_MODE_CONDITION_SR_PID_USED == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_ModeConditionSRReadPIDData(
  uint8 ucDsPPIDDataIndex)
{
  Std_ReturnType RetVal;
  P2CONST(Dcm_DspPidData, AUTOMATIC, DCM_APPL_CONST) LpPidData;
  uint8 LucFunctionIndex;

  #if ((DCM_DSP_PID_UINT16 == STD_ON) || (DCM_DSP_PID_UINT16_N == STD_ON) || \
       (DCM_DSP_PID_UINT32 == STD_ON) || (DCM_DSP_PID_UINT32_N == STD_ON))
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutData;
  #endif


  LpPidData = &Dcm_GaaDcmDspPidData[ucDsPPIDDataIndex];
  LucFunctionIndex = LpPidData->ucReadFunctionIndex;
  RetVal = E_NOT_OK;

  #if ((DCM_DSP_PID_UINT16 == STD_ON) || (DCM_DSP_PID_UINT16_N == STD_ON) || \
       (DCM_DSP_PID_UINT32 == STD_ON) || (DCM_DSP_PID_UINT32_N == STD_ON))
  pOutData = &Dcm_GaaModeConditionSwcData[0];
  #endif


  /* polyspace-begin MISRA-C3:10.5 MISRA-C3:10.3 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
  switch (LpPidData->ucDcmPIDDataType)
  {
    case DCM_DATA_TYPE_BOOLEAN:
      #if (DCM_DSP_PID_BOOLEAN == STD_ON)
      RetVal = Dcm_GaaPIDBooleanFunc[LucFunctionIndex].
          pReadPidDataBoolFun((boolean*)&Dcm_GaaModeConditionSwcData[0]);
      #endif
    break;

    case DCM_DATA_TYPE_UINT8:
      #if (DCM_DSP_PID_UINT8 == STD_ON)
      RetVal = Dcm_GaaPIDUint8Func[LucFunctionIndex].
        pReadPidDataUint8Fun(&Dcm_GaaModeConditionSwcData[0]);
      #endif
    break;

    case DCM_DATA_TYPE_UINT8_N:
      #if (DCM_DSP_PID_UINT8_N == STD_ON)
      RetVal = Dcm_GaaPIDUint8NFunc[LucFunctionIndex].
        pReadPidDataUint8NFun(&Dcm_GaaModeConditionSwcData[0]);
      #endif
    break;

    case DCM_DATA_TYPE_UINT16:
      #if (DCM_DSP_PID_UINT16 == STD_ON)
      RetVal = Dcm_GaaPIDUint16Func[LucFunctionIndex].
        pReadPidDataUint16Fun((P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA))pOutData);
      #endif
    break;

    case DCM_DATA_TYPE_UINT16_N:
      #if (DCM_DSP_PID_UINT16_N == STD_ON)
      RetVal = Dcm_GaaPIDUint16NFunc[LucFunctionIndex].
        pReadPidDataUint16NFun((P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA))pOutData);
      #endif
    break;

    case DCM_DATA_TYPE_UINT32:
      #if (DCM_DSP_PID_UINT32 == STD_ON)
      RetVal = Dcm_GaaPIDUint32Func[LucFunctionIndex].
        pReadPidDataUint32Fun((P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA))pOutData);
      #endif
    break;

    case DCM_DATA_TYPE_UINT32_N:
      #if (DCM_DSP_PID_UINT32_N == STD_ON)
      RetVal = Dcm_GaaPIDUint32NFunc[LucFunctionIndex].
        pReadPidDataUint32NFun((P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA))pOutData);
      #endif
    break;

    default:
      RetVal = E_NOT_OK;
    break;
  }
    /* polyspace-end MISRA-C3:10.5 MISRA-C3:10.3 MISRA-C3:11.5 [Justified:Low] Justify with annotations */

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ModeConditionParse4ByteData                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function parse a 4 byte variable to 1 byte array    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : DataIn                                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDataOut                                            **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_ModeConditionParse4ByteData( 
  uint32 DataIn,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut)
{
  if (pDataOut != NULL_PTR)
  {
    pDataOut[0] = (uint8)DataIn;
    pDataOut[1] = (uint8)(DataIn >> 8U);
    pDataOut[2] = (uint8)(DataIn >> 16U);
    pDataOut[3] = (uint8)(DataIn >> 24U);
  }
}

/*******************************************************************************
** Function Name        : Dcm_ModeConditionCompareData                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function compare 1 byte data with specific          **
**                        condition                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : Dest, Src, Condition                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_ModeConditionCompareData(
  uint8 Dest
  , uint8 Src
  , Dcm_ConditionType Condition)
{
  boolean ChkVal = DCM_TRUE;
  if (((DCM_EQUALS == Condition) && (Src != Dest))
      || ((DCM_EQUALS_NOT == Condition) && (Src == Dest))
      || ((DCM_GREATER_OR_EQUAL == Condition) && (Src < Dest))
      || ((DCM_GREATER_THAN == Condition) && (Src <= Dest))
      || ((DCM_LESS_OR_EQUAL == Condition) && (Src > Dest))
      || ((DCM_LESS_THAN == Condition) && (Src >= Dest)))
  {
    ChkVal = DCM_FALSE;
  }
  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ModeConditionSRCompare                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function compare mode condition                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : Dest, Src, Condition, DataType                      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_ModeConditionSRCompare(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Dest,
  uint32 Src,
  Dcm_ConditionType Condition, 
  Dcm_DataType DataType)
{
  boolean ChkVal = DCM_TRUE;
  uint8 LucSrcData[4];
  uint8 LucIndex;
  uint8 LucLoopValue;

  Dcm_ModeConditionParse4ByteData(Src, &LucSrcData[0]);

  switch (DataType)
  {
    case DCM_DATA_TYPE_UINT8_N:
    case DCM_DATA_TYPE_UINT8:
     LucLoopValue = 1U;
    break;

    case DCM_DATA_TYPE_UINT16_N:
    case DCM_DATA_TYPE_UINT16:
      LucLoopValue = 2U;
    break;

    case DCM_DATA_TYPE_UINT32_N:
    case DCM_DATA_TYPE_UINT32:
      LucLoopValue = 4U;
    break;

    default:
      LucLoopValue = 0U;
    break;
  }

  LucIndex = 0U;
  while ((LucIndex < LucLoopValue) && (ChkVal == DCM_TRUE))
  {
    ChkVal =  Dcm_ModeConditionCompareData(
      Dest[LucIndex], 
      LucSrcData[LucIndex], 
      Condition);

    LucIndex++;
  }
  
  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsValidSwcSRDataElementCondition                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function validate for Mode Condition with S/R       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pModeCondCfg                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaModeConditionSwcData    **
**                                                                            **
**                        Function(s) :  Dcm_ModeConditionSRReadPIDData       **
**                            Dcm_APIs_DidData, Dcm_DataElementCompare        **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsValidSwcSRDataElementCondition(
  Dcm_ModeConditionConfigConstPtrType pModeCondCfg)
{
  boolean ChkVal = DCM_FALSE;
  Std_ReturnType RetVal;
  uint32 LusCompareValue;
  uint8 LucArrIndex;
  uint8 LucStep;
  #if ((DCM_MODE_CONDITION_SR_DID_USED == STD_ON) && \
       (DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON))
  uint16 LusLength;
  #endif

  Dcm_ConditionType LddCondition = pModeCondCfg->ConditionType;

  RetVal = E_NOT_OK;

  if (pModeCondCfg->usDID != 0x00)
  {
    #if (DCM_MODE_CONDITION_SR_DID_USED == STD_ON)
    uint16 LusDataIdentifier = pModeCondCfg->usDID;
    Dcm_DidParaConfigConstPtrType LpDidConfig;
    LpDidConfig = Dcm_DspInternal_GetConfigByDid(LusDataIdentifier);
    uint32 LulDataSize = DCM_ZERO;

    switch (LpDidConfig->ucDcmDspDidUsePort)
    {
      case USE_ATOMIC_SENDER_RECEIVER_INTERFACE:
      case USE_ATOMIC_SENDER_RECEIVER_INTERFACE_AS_SERVICE:
        #if (DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON)
        RetVal = Dcm_APIs_DidData(
          pModeCondCfg->usDID,
          &Dcm_GaaModeConditionSwcData[0],
          &LusLength);
        #endif /* End of (DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON) */
        break;

      case USE_DATA_ELEMENT_SPECIFIC_INTERFACES:
        RetVal = Dcm_DspInternal_ReadDidByDataSpecificIf_ModeRule(
          LpDidConfig, &Dcm_GaaModeConditionSwcData[0], &LulDataSize);
        break;
      
      default:
        /* Do nothing*/
        break;
    }
    #endif /* End of (DCM_MODE_CONDITION_SR_DID_USED == STD_ON) */
  }
  else
  {
    #if (DCM_MODE_CONDITION_SR_PID_USED == STD_ON)
    if (pModeCondCfg->ucDspPIDDataIndex != 0xFFU)
    {
      RetVal = Dcm_ModeConditionSRReadPIDData(
        pModeCondCfg->ucDspPIDDataIndex);
    }
    #endif
  }

  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Return value depend on Application code."*/
  if (RetVal == E_OK)
  {
    /* DcmSwcDataElementArray configured */
    if (pModeCondCfg->NumberOfDataElementArray > 0)
    {
      switch (pModeCondCfg->ucSRDataType)
      {
        case DCM_DATA_TYPE_UINT16_N:
          LucStep = 2U;
        break;

        case DCM_DATA_TYPE_UINT32_N:
          LucStep = 4U;
        break;

        default:
          LucStep = 1U;
        break;
      }


      for (LucArrIndex = 0; 
          LucArrIndex < pModeCondCfg->NumberOfDataElementArray;
          LucArrIndex++ )
      {
        LusCompareValue = pModeCondCfg->pPrimitiveCompareValue[LucArrIndex];
        ChkVal = Dcm_ModeConditionSRCompare(
          &Dcm_GaaModeConditionSwcData[LucArrIndex * LucStep],
          LusCompareValue, 
          LddCondition,
          pModeCondCfg->ucSRDataType);

        if (DCM_FALSE == ChkVal)
        {
          break;
        }
      }
    }
    else /* DcmSwcDataElementPrimitive configured */
    {
      LusCompareValue = pModeCondCfg->PrimitiveCompareValue;
      ChkVal = Dcm_ModeConditionSRCompare(
        &Dcm_GaaModeConditionSwcData[0], 
        LusCompareValue, 
        LddCondition,
        pModeCondCfg->ucSRDataType);
    }
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Return value depend on Application code."*/

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsValidBswOrSwcModeCondition                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function validate available BSW or SWC              **
**                        condition mode                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pModeCondCfg                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ChkVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsValidBswOrSwcModeCondition(
  Dcm_ModeConditionConfigConstPtrType pModeCondCfg)
{
  /* @Trace: Dcm_SUD_API_50907 */
  boolean ChkVal = DCM_FALSE;
  Dcm_GetCurrentModeFunType pGetCurrentMode = pModeCondCfg->pGetCurrentMode;

  if (NULL_PTR != pGetCurrentMode)
  {
    /* @Trace: SWS_Dcm_00810 */
    /* @Trace: Dcm_SUD_API_20272 */
    uint8 CurrentMode = pGetCurrentMode();
    uint8 ChkMode = pModeCondCfg->ucBsworSwcMode;
    Dcm_ConditionType Condition = pModeCondCfg->ConditionType;

    CHK_RET_VAL((Condition == DCM_EQUALS) && (CurrentMode == ChkMode), ChkVal, DCM_TRUE);
    CHK_RET_VAL((Condition == DCM_EQUALS_NOT) && (CurrentMode != ChkMode), ChkVal, DCM_TRUE);
  }

  return ChkVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_IsDiffConnection                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check old and current connection is same   **
**                        or differrent                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : PduId1, PduId2                                      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsDiffConnection(PduIdType PduId1, PduIdType PduId2)
{
  /* @Trace: Dcm_SUD_API_11252 */
  boolean LblRetVal = DCM_FALSE;

  uint16 ConnectionId1 = Dcm_GaaPduIdTableConfig[PduId1].RxConnectionId;
  uint16 ConnectionId2 = Dcm_GaaPduIdTableConfig[PduId2].RxConnectionId;

  if (ConnectionId1 != ConnectionId2)
  {
    /* @Trace: Dcm_SUD_API_11253 */
    LblRetVal = DCM_TRUE;
  }

  return LblRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsNotInNoComMode                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check current ComM chanel is no            **
**                        communitcation or different                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : ComMChannelId                                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaCommMode                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsNotInNoComMode(uint8 ComMChannelId)
{
  uint8 CommMode = Dcm_GaaCommMode[ComMChannelId];

  /* @Trace: Dcm_SUD_API_20273 Dcm_SUD_API_20274 */
  return (DCM_NO_COMMUNICATION != CommMode) ? DCM_TRUE : DCM_FALSE;
}

/*******************************************************************************
** Function Name        : Dcm_IsInFullComMode                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check current ComM chanel is full          **
**                        communitcation or different                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : ComMChannelId                                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaCommMode                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00157 SWS_Dcm_00161 */
FUNC(boolean, DCM_CODE) Dcm_IsInFullComMode(uint8 ComMChannelId)
{
  uint8 CommMode = Dcm_GaaCommMode[ComMChannelId];

  /* @Trace: Dcm_SUD_API_20275 Dcm_SUD_API_20276 */
  return (DCM_FULL_COMMUNICATION == CommMode) ? DCM_TRUE : DCM_FALSE;
}

/*******************************************************************************
** Function Name        : Dcm_IsNotInReset                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check Dcm is being reset or not            **
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
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblReset                   **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsNotInReset(void)
{
  /* @Trace: Dcm_SUD_API_20277 Dcm_SUD_API_20278 */
  return (DCM_FALSE == Dcm_GblReset) ? DCM_TRUE : DCM_FALSE;
}

/*******************************************************************************
** Function Name        : Dcm_IsFunctionalRequest                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check incoming request is function         **
**                        request                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pPduIdTable                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsFunctionalRequest(Dcm_PduIdTablePtrType pPduIdTable)
{
  /* @Trace: Dcm_SUD_API_11255 */
  boolean LblRetVal = DCM_FALSE;

  if ((NULL_PTR != pPduIdTable) && (DCM_FUNCTIONAL_TYPE == pPduIdTable->ucRxAddrType))
  {
    /* @Trace: Dcm_SUD_API_11254 */
    LblRetVal = DCM_TRUE;
  }

  return LblRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsProcessingRequest                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check Dcm is processing request or not     **
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
** Return parameter     : ChkVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblNormalReq               **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsProcessingRequest(void)
{
  boolean ChkVal = DCM_FALSE;

  /* @Trace: Dcm_SUD_API_11267 */
  if ((DCM_TRUE == Dcm_GblNormalReq)

      #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
      || (Dcm_GucResOnEventStatus == DCM_ROEONGOING)
      #endif
     )
  {
    /* @Trace: Dcm_SUD_API_11266 */
    ChkVal = DCM_TRUE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsReceivingToProcessOtherRequest                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check Dcm receive new request when         **
**                        current request is processing                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : PduId                                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ChkVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsReceivingToProcessOtherRequest(PduIdType PduId)
{
  boolean ChkVal = DCM_FALSE;

  for (uint8 id = 0U; id < DCM_NUM_OF_PDUIDTABLECONFIG; id++)
  {
    /* @Trace: Dcm_SUD_API_20279 */
    if ((id != PduId)
        && (DCM_RECEPTION_IDLE != Dcm_GaaPduIdTableConfig[id].ucReceiveStatus))
    {
      /* @Trace: Dcm_SUD_API_11269 */
      ChkVal = DCM_TRUE;
      break;
    }
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsHigherPriorityProtocol                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check incoming request protocol            **
**                        whether higher current protocol                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pPduIdTable                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : boolean                                             **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GucPrtclPriority           **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00015 */
FUNC(boolean, DCM_CODE) Dcm_IsHigherPriorityProtocol(Dcm_PduIdTablePtrType pPduIdTable)
{
  /* @Trace: Dcm_SUD_API_20280 */
  boolean LblRetVal = DCM_FALSE;

  if (NULL_PTR != pPduIdTable)
  {
    uint8 ProtocolIdx = Dcm_GetProtocolTypeIndex(pPduIdTable->ProtocolType);
    uint8 NewPrtclPriority = (ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG) ?
      Dcm_GaaProtocolConfig[ProtocolIdx].ucProtocolPrio : Dcm_GucPrtclPriority;

    if (NewPrtclPriority < Dcm_GucPrtclPriority)
    {
      /* @Trace: Dcm_SUD_API_20283 */
      LblRetVal = DCM_TRUE;
    }
  }
  
  return LblRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsSpecialNrc                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dcm check special negative response code            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : NrcVal                                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Result                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsSpecialNrc(uint8 NrcVal)
{
  /* @Trace: Dcm_SUD_API_11274 */
  boolean Result = DCM_FALSE;

  if ((DCM_E_SERVICENOTSUPPORTED == NrcVal)
      || (DCM_E_SUBFUNCTIONNOTSUPPORTED == NrcVal)
      || (DCM_E_REQUESTOUTOFRANGE == NrcVal)
      || (DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION == NrcVal)
      || (DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION == NrcVal))
  {
    /* @Trace: Dcm_SUD_API_11275 */
    Result = DCM_TRUE;
  }

  return Result;
}

/*******************************************************************************
** Function Name        : Dcm_IsNonDefaultSession                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check current session is non-default       **
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
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddCurrentSession          **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsNonDefaultSession(void)
{
  /* @Trace: Dcm_SUD_API_50905 */
  boolean LblRetVal = DCM_FALSE;

  if (DCM_DEFAULT_SESSION != Dcm_GddCurrentSession)
  {
    /* @Trace: Dcm_SUD_API_20284 */
    LblRetVal = DCM_TRUE;
  }

  return LblRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_GetUdsActiveProtocolInfo                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to get UDS protocol information            **
**                        by pduId                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pProtocolType, pConnectionId, pSourceTesterAddress  **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddRxPduId                 **
**                                                                            **
**                        Function(s) : Dcm_IsOBDRequestById                  **
**                                      Dcm_GetProtocolInfo                   **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01366 SWS_Dcm_01365*/
FUNC(void, DCM_CODE) Dcm_GetUdsActiveProtocolInfo(
  Dcm_ProtocolTypePtrType pProtocolType
  , Dcm_Uint16PtrType pConnectionId
  , Dcm_Uint16PtrType pSourceTesterAddress)
{
  /* @Trace: Dcm_SUD_API_50906 */
  *pProtocolType = DCM_NO_ACTIVE_PROTOCOL;

  if (DCM_TRUE == DCM_IS_ACTIVE_PROTOCOL_STATUS())
  {
    /* @Trace: Dcm_SUD_API_20285 */
    if (DCM_FALSE == Dcm_IsOBDRequestById(Dcm_GddRxPduId))
    {
      /* @Trace: Dcm_SUD_API_20286 */
      Dcm_GetProtocolInfo(Dcm_GddRxPduId, 
        pProtocolType, pConnectionId, pSourceTesterAddress);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_GetProtocolInfo                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function get protocol information                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : PduId                                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pProtocolType, pConnectionId, pSourceTesterAddress  **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_GetProtocolInfo(
  PduIdType PduId
  , Dcm_ProtocolTypePtrType pProtocolType
  , Dcm_Uint16PtrType pConnectionId
  , Dcm_Uint16PtrType pSourceTesterAddress)
{
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[PduId];

  *pProtocolType = pPduIdTable->ProtocolType;
  *pConnectionId = pPduIdTable->RxConnectionId;

  /* @Trace: SWS_Dcm_01429 */
  /* @Trace: Dcm_SUD_API_11237 Dcm_SUD_API_11236 */
  *pSourceTesterAddress = (pPduIdTable->PduRef == PDUREF_NO_METADATA) ?
    pPduIdTable->ConfigTesterAddress : pPduIdTable->SourceTesterAddress;
}

/*******************************************************************************
** Function Name        : Dcm_SwitchProtocol                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function switch protocol corresponding pduid        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : PduId                                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : RetVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddRxPduId                 **
**                                                                            **
**                        Function(s) : Dcm_StopProtocol                      **
**                                      Dcm_StartProtocol                     **
**                                      Dcm_StopTimer                         **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SwitchProtocol(PduIdType PduId)
{
  /* @Trace: Dcm_SUD_API_11341 */
  Std_ReturnType RetVal = E_OK;

  DCM_CLEAR_ALL_DSP_FLAGS();

  #if (DCM_DSP_SECURITY_SERVICE == STD_ON)
  Dcm_StopTimer(DCM_SECURITY_TIMER);
  #endif

  /* Stop active protocol */
  if (DCM_TRUE == DCM_IS_ACTIVE_PROTOCOL_STATUS())
  {
    /* @Trace: SWS_Dcm_00459 */
    /* @Trace: Dcm_SUD_API_11342 */
    RetVal = Dcm_StopProtocol(Dcm_GddRxPduId);
    DCM_DEACTIVATE_PROTOCOL_STATUS();
  }

  /* Start incoming protocol */
  CHK_RET_VAL(RetVal == E_OK, RetVal, Dcm_StartProtocol(PduId));

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_StartProtocol                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function start protocol corresponding pduid         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : PduId                                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : RetVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_GetProtocolInfo                   **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_StartProtocol(PduIdType PduId)
{
  Std_ReturnType RetVal = E_NOT_OK;
  #if (DCM_TOTAL_NUM_OF_CALLBACK_REQUEST != DCM_ZERO)
  Dcm_ProtocolType ProtocolType;
  uint16 ConnectionId;
  uint16 SourceTesterAddress;
  Dcm_GetProtocolInfo(PduId, &ProtocolType, &ConnectionId, &SourceTesterAddress);

  Dcm_StartProtocolFunType pStartProtocolFun;
  for (uint8 idx = 0U; idx < DCM_TOTAL_NUM_OF_CALLBACK_REQUEST; idx++)
  {
    pStartProtocolFun = Dcm_GaaCbkReqServices[idx].pStartProtocolFun;
    if (pStartProtocolFun == NULL_PTR)
    {
      /* @Trace: Dcm_SUD_API_11314 */
      continue;
    }

    RetVal = pStartProtocolFun(ProtocolType, SourceTesterAddress, ConnectionId);
    if (RetVal != E_OK)
    {
      /* @Trace: Dcm_SUD_API_11317 */
      break;
    }
  }
  #else
  DCM_UNUSED(PduId);
  RetVal = E_OK;
  #endif

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_StopProtocol                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function stop protocol corresponding pduid          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : PduId                                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : RetVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_GetProtocolInfo                   **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_StopProtocol(PduIdType PduId)
{
  Std_ReturnType RetVal = E_NOT_OK;
  #if (DCM_TOTAL_NUM_OF_CALLBACK_REQUEST != DCM_ZERO)
  Dcm_ProtocolType ProtocolType;
  uint16 ConnectionId;
  uint16 SourceTesterAddress;
  Dcm_GetProtocolInfo(PduId, &ProtocolType, &ConnectionId, &SourceTesterAddress);

  Dcm_StopProtocolFunType pStopProtocolFun;
  for (uint8 idx = 0U; idx < DCM_TOTAL_NUM_OF_CALLBACK_REQUEST; idx++)
  {
    pStopProtocolFun = Dcm_GaaCbkReqServices[idx].pStopProtocolFun;
    if (pStopProtocolFun == NULL_PTR)
    {
      /* @Trace: Dcm_SUD_API_11320 */
      continue;
    }

    RetVal = pStopProtocolFun(ProtocolType, SourceTesterAddress, ConnectionId);
    if (RetVal != E_OK)
    {
      /* @Trace: Dcm_SUD_API_11319 */
      break;
    }
  }
  #else
  DCM_UNUSED(PduId);
  RetVal = E_OK;
  #endif

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_CancelAllReceivingOtherRequests                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function cancel receiving other request             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : PduId                                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : PduR_DcmCancelReceive                 **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_CancelAllReceivingOtherRequests(PduIdType PduId)
{
  boolean LbdoCancel;
  Dcm_PduIdTablePtrType pPduIdTable;
  uint8 ProtocolIdx;
  for (uint8 id = 0; id < DCM_NUM_OF_PDUIDTABLECONFIG; id++)
  { 
    LbdoCancel = DCM_FALSE;

    /* Do not cancel hte Pdu with inputparameter "id"  */
	if (id != PduId)
	{
    	/* @Trace: Dcm_SUD_API_11222 */
    	pPduIdTable = &Dcm_GaaPduIdTableConfig[id];
	    /**/
		if (DCM_RECEPTION_ONGOING == pPduIdTable->ucReceiveStatus) 
		{
	    	LbdoCancel = DCM_TRUE;
		}
		else if (DCM_RECEPTION_COMPLETED == pPduIdTable->ucReceiveStatus)
		{
	    	/* @Trace: Dcm_SUD_API_11223 */
			LbdoCancel = DCM_TRUE;
		}
		else
		{
			/* Do Nothing  */
		}

    }
   if (DCM_TRUE == LbdoCancel)
   {
    ProtocolIdx = Dcm_GetProtocolTypeIndex(pPduIdTable->ProtocolType);
    SchM_Enter_Dcm_RxPduIdProtection();
    DCM_CLR_PDU_STATUS(pPduIdTable);
    DCM_CLR_PROTOCOL_STATUS(&Dcm_GaaProtocolConfig[ProtocolIdx]);
    SchM_Exit_Dcm_RxPduIdProtection();
    pPduIdTable->ucReceiveStatus = DCM_RECEPTION_CANCELLED;
    (void)PduR_DcmCancelReceive(id);
	}
  }
}

/*******************************************************************************
** Function Name        : Dcm_IsValidServiceId                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function validate ServiceId                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     :ServiceId                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ChkVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsValidServiceId(uint8 ServiceId)
{
  /* @Trace: Dcm_SUD_API_11231 */
  boolean ChkVal = DCM_TRUE;

  #if (DCM_RESPOND_ALL_REQUEST == STD_OFF)
  /* @Trace: SWS_Dcm_00084 */
  if ((((uint8) 0x40 <= ServiceId) && (ServiceId <= (uint8) 0x7F)) ||
       ((uint8) 0xC0 <= ServiceId))
  {
    /* @Trace: Dcm_SUD_API_11233 */
    ChkVal = DCM_FALSE;
  }
  #else
  DCM_UNUSED(ServiceId);
  #endif

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsOBDRequest                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check incoming request is OBD request      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pPduIdTable                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ChkVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsOBDRequest(
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) pPduIdTable)
{
  /* @Trace: Dcm_SUD_API_11265 */
  boolean ChkVal = DCM_FALSE;
  Dcm_ProtocolType ProtocolType = pPduIdTable->ProtocolType;

  if ((DCM_OBD_ON_CAN == ProtocolType)
      || (DCM_OBD_ON_FLEXRAY == ProtocolType)
      || (DCM_OBD_ON_IP == ProtocolType))
  {
    /* @Trace: Dcm_SUD_API_11264 */
    ChkVal = DCM_TRUE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsOBDRequestById                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check is OBD request incoming              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : PduId                                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsOBDRequestById(PduIdType PduId)
{
  /* @Trace: Dcm_SUD_API_10219 */
  return Dcm_IsOBDRequest(&Dcm_GaaPduIdTableConfig[PduId]);
}

/*******************************************************************************
** Function Name        : Dcm_IsUDSRequest                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check request incoming is UDS request      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pPduIdTable                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ChkVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsUDSRequest(
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) pPduIdTable)
{
  /* @Trace: Dcm_SUD_API_11355 */
  boolean ChkVal = DCM_FALSE;
  Dcm_ProtocolType ProtocolType = pPduIdTable->ProtocolType;

  if ((DCM_UDS_ON_CAN == ProtocolType)
      || (DCM_UDS_ON_FLEXRAY == ProtocolType)
      || (DCM_UDS_ON_IP == ProtocolType)
      || (DCM_UDS_ON_LIN == ProtocolType))
  {
    /* @Trace: Dcm_SUD_API_11356 */
    ChkVal = DCM_TRUE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_IsUDSRequestById                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check incoming request by pduid is UDS     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : PduId                                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Function(s) : Dcm_IsUDSRequest                      **
**                                                                            **
*******************************************************************************/
extern FUNC(boolean, DCM_CODE) Dcm_IsUDSRequestById(PduIdType PduId)
{
  /* @Trace: Dcm_SUD_API_11358 */
  return Dcm_IsUDSRequest(&Dcm_GaaPduIdTableConfig[PduId]);
}

/*******************************************************************************
** Function Name        : Dcm_MemClear                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function clear pointer memory                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : Size                                                **
**                                                                            **
** InOut Parameters     : pDest                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_MemClear(
  Dcm_Uint8PtrType pDest,
  uint32 Size)
{
  uint32 idx;

  /* @Trace: Dcm_SUD_API_10220 */
  if (NULL_PTR != pDest)
  {
    for (idx = 0U; idx < Size; idx++)
    {
      /* @Trace: Dcm_SUD_API_11299 */
      pDest[idx] = 0U;
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_MemCopy                                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to copy data to pointer                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pSrc, Size                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDest                                               **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_MemCopy(
  Dcm_Uint8PtrType pDest,
  Dcm_Uint8ConstPtrType pSrc,
  uint32 Size)
{
  uint32 idx;

  /* @Trace: Dcm_SUD_API_10221 */
  if ((NULL_PTR != pDest) && (NULL_PTR != pSrc))
  {
    for (idx = 0U; idx < Size; idx++)
    {
      /* @Trace: Dcm_SUD_API_11306 */
      pDest[idx] = pSrc[idx];
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_MemCompare                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to compare 2 memory data with              **
**                        input condition                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pDest, pSrc, Size, Condition                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_MemCompare(
  Dcm_Uint8ConstPtrType pDest
  , Dcm_Uint8ConstPtrType pSrc
  , uint32 Size
  , Dcm_ConditionType Condition)
{
  /* @Trace: Dcm_SUD_API_11301 */
  boolean ChkVal = DCM_TRUE;

  for (uint32 idx = 0U; idx < Size; idx++)
  {
    if (((DCM_EQUALS == Condition) && (pSrc[idx] != pDest[idx]))
        || ((DCM_EQUALS_NOT == Condition) && (pSrc[idx] == pDest[idx]))
        || ((DCM_GREATER_OR_EQUAL == Condition) && (pSrc[idx] < pDest[idx]))
        || ((DCM_GREATER_THAN == Condition) && (pSrc[idx] <= pDest[idx]))
        || ((DCM_LESS_OR_EQUAL == Condition) && (pSrc[idx] > pDest[idx]))
        || ((DCM_LESS_THAN == Condition) && (pSrc[idx] >= pDest[idx])))
    {
      /* @Trace: Dcm_SUD_API_11303 */
      ChkVal = DCM_FALSE;
      break;
    }
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_SwitchCommMode_AllChannel                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to swith all channel configuration         **
**                        to input mode                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : CommMode                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                          BswM_Dcm_CommunicationMode_CurrentState           **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SwitchCommMode_AllChannel(
  Dcm_CommunicationModeType CommMode)
{
  #if ((0 < DCM_TOTAL_NUM_OF_ALL_CHANNEL) \
       && (defined(DCM_COM_CONTROL_SERVICES_ENABLED)))
  Dcm_AllCommControlConfigConstPtrType pAllCommControlCfg;
  for (uint8 idx = 0; idx < DCM_TOTAL_NUM_OF_ALL_CHANNEL; idx++)
  {
    pAllCommControlCfg = &Dcm_GaaAllCommControlConfig[idx];
    if (DCM_FALSE == pAllCommControlCfg->ChannelUsed)
    {
      /* @Trace: Dcm_SUD_API_11325 */
      continue;
    }

    /* @Trace: Dcm_SUD_API_11327 */
    pAllCommControlCfg->pSchMSwitchCommModeFunc(CommMode);
    BswM_Dcm_CommunicationMode_CurrentState(pAllCommControlCfg->ComMChannelId, CommMode);
  }
  #else
  DCM_UNUSED(CommMode);
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_SwitchCommMode_ReceivedOnChannel                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to switch received channel to input mode   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : CommMode                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                          BswM_Dcm_CommunicationMode_CurrentState           **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SwitchCommMode_ReceivedOnChannel(
  Dcm_CommunicationModeType CommMode)
{
  if (DCM_NUM_OF_PDUIDTABLECONFIG <= Dcm_GstMsgContext.dcmRxPduId)
  {
    /* @Trace: Dcm_SUD_API_10224 */
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);
  }
  else
  {
    #if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) \
         || (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))
    Dcm_PduIdTablePtrType pPduIdTable;
    pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GstMsgContext.dcmRxPduId];

    if (NULL_PTR != pPduIdTable->pSchMSwitchCommModeFunc)
    {
      /* @Trace: Dcm_SUD_API_11330 */
      pPduIdTable->pSchMSwitchCommModeFunc(CommMode);
      BswM_Dcm_CommunicationMode_CurrentState(
        pPduIdTable->ComMChannelId, CommMode);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_11332 */
      DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);
    }
    #else
    DCM_UNUSED(CommMode);
    #endif
  }
}

/*******************************************************************************
** Function Name        : Dcm_SwitchCommMode_SpecificChannel                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to swith specific channel to input mode    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : CommMode                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                          BswM_Dcm_CommunicationMode_CurrentState           **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SwitchCommMode_SpecificChannel(
  Dcm_CommunicationModeType CommMode)
{
  #if ((0 < DCM_TOTAL_NUM_OF_SPECIFIC_CHANNEL) \
       && (defined(DCM_COM_CONTROL_SERVICES_ENABLED)))
  Dcm_CommControlConfigConstPtrType pCommControlCfg;
  for (uint8 idx = 0; idx < DCM_TOTAL_NUM_OF_SPECIFIC_CHANNEL; idx++)
  {
    #if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
    pCommControlCfg = &Dcm_GaaCommControlConfig[idx];
    if ((DCM_FALSE == pCommControlCfg->ChannelUsed)
        || (pCommControlCfg->SubNetNumber != Dcm_GucSubNetValue))
    {
      /* @Trace: Dcm_SUD_API_11334 */
      continue;
    }

    /* @Trace: Dcm_SUD_API_11335 */
    pCommControlCfg->pSchMSwitchCommModeFunc(CommMode);
    BswM_Dcm_CommunicationMode_CurrentState(pCommControlCfg->ComMChannelId, CommMode);
    break;
    #else
    DCM_UNUSED(CommMode);
    DCM_UNUSED(pCommControlCfg);
    #endif
  }
  #else
  DCM_UNUSED(CommMode);
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_SwitchCommMode_SubNode                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to swicth received subnode to input mode   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : CommMode                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                          BswM_Dcm_CommunicationMode_CurrentState           **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SwitchCommMode_SubNode(
  Dcm_CommunicationModeType CommMode)
{
  #if ((0 < DCM_TOTAL_NUM_OF_SUBNODE) \
       && (defined(DCM_COM_CONTROL_SERVICES_ENABLED)))
  Dcm_CommControlSubNodeConfigConstPtrType pCommControlSubNodeCfg;
  for (uint8 idx = 0; idx < DCM_TOTAL_NUM_OF_SUBNODE; idx++)
  {
    pCommControlSubNodeCfg = &Dcm_GaaCommControlSubNodeConfig[idx];
    if ((DCM_FALSE == pCommControlSubNodeCfg->SubNodeUsed)
        || (pCommControlSubNodeCfg->SubNodeId != Dcm_GucSubNodeId))
    {
      /* @Trace: Dcm_SUD_API_11337 */
      continue;
    }

    /* @Trace: Dcm_SUD_API_11338 */
    pCommControlSubNodeCfg->pSchMSwitchCommModeFunc(CommMode);
    BswM_Dcm_CommunicationMode_CurrentState(pCommControlSubNodeCfg->ComMChannelId, CommMode);
    break;
  }
  #else
  DCM_UNUSED(CommMode);
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_IsSubNodeIdSupported                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function validate received SubNodeId                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : SubNodeId                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ChkVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_IsSubNodeIdSupported(
  uint16 SubNodeId)
{
  /* @Trace: Dcm_SUD_API_11276 */
  boolean ChkVal = DCM_FALSE;

  #if (0 < DCM_TOTAL_NUM_OF_SUBNODE)
  Dcm_CommControlSubNodeConfigConstPtrType pCommControlSubNodeCfg;
  for (uint8 idx = 0; idx < DCM_TOTAL_NUM_OF_SUBNODE; idx++)
  {
    /* @Trace: SWS_Dcm_01081 SWS_Dcm_01082 */
    pCommControlSubNodeCfg = &Dcm_GaaCommControlSubNodeConfig[idx];
    if ((DCM_FALSE == pCommControlSubNodeCfg->SubNodeUsed)
        || (pCommControlSubNodeCfg->SubNodeId != SubNodeId))
    {
      /* @Trace: Dcm_SUD_API_11278 */
      continue;
    }

    /* @Trace: Dcm_SUD_API_11280 */
    ChkVal = DCM_TRUE;
    break;
  }
  #else
  DCM_UNUSED(SubNodeId);
  #endif

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_PagedBuffer_GetMaxRespLen                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function use to get the max response length    **
**                        of the current protocol                             **
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
** Return parameter     : LulMaxResLen                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
FUNC(uint32, DCM_CODE) Dcm_PagedBuffer_GetMaxRespLen(
  Dcm_MsgContextConstPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_11352 */
  uint32 LulMaxResLen = DCM_ZERO;
  PduIdType LddRxPduId = pMsgContext->dcmRxPduId;

  if (LddRxPduId < DCM_NUM_OF_PDUIDTABLECONFIG)
  {
    /* @Trace: Dcm_SUD_API_11350 */
    uint8 LucProtocolType = Dcm_GaaPduIdTableConfig[LddRxPduId].ProtocolType;
    uint8 LucProtocolIdx = Dcm_GetProtocolTypeIndex(LucProtocolType);

    if (LucProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG)
    {
      /* @Trace: Dcm_SUD_API_11351 */
      LulMaxResLen = Dcm_GaaProtocolConfig[LucProtocolIdx].usProtocolMaxResSize;
    }
  }

  return LulMaxResLen;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_Internal_GetPduIdOnReset                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function use to get the max response length    **
**                        of the current protocol                             **
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
** Return parameter     : LulMaxResLen                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Dcm_PduIdTablePtrType, DCM_CODE) Dcm_Internal_GetPduIdOnReset(
  uint16 testerAddress,
  P2VAR(PduIdType, AUTOMATIC, DCM_APPL_DATA) pRxPduId)
{
  uint8 LucIdx;
  Dcm_PduIdTablePtrType LpPduIdTable = NULL_PTR;

  for (LucIdx = DCM_ZERO; LucIdx < DCM_NUM_OF_PDUIDTABLECONFIG; LucIdx++)
  {
    /* @Trace: Dcm_SUD_API_11250 */
    if ((Dcm_GaaPduIdTableConfig[LucIdx].ucRxAddrType == DCM_PHYSICAL_TYPE) &&
        (Dcm_GaaPduIdTableConfig[LucIdx].ConfigTesterAddress == testerAddress))
    {
      /* @Trace: Dcm_SUD_API_11246 */
      if (NULL_PTR != pRxPduId)
      {
        /* @Trace: Dcm_SUD_API_11248 */
        *pRxPduId = LucIdx;
        LpPduIdTable = &Dcm_GaaPduIdTableConfig[LucIdx];
      }
      break;
    }
  }

  return LpPduIdTable;
}

/*******************************************************************************
** Function Name        : Dcm_RequestParameterToUint16                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function use to get data                       **
**                        from request message and convert it to uint16       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : numOfByte, pData                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LulData                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(uint16, DCM_CODE) Dcm_RequestParameterToUint16(
  uint8 numOfByte,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pData)
{
  uint8 LucIdx;
  uint16 LusData = DCM_ZERO;

  for (LucIdx = DCM_ZERO; LucIdx < numOfByte; LucIdx++)
  {
    /* @Trace: Dcm_SUD_API_20288 */
    LusData = LusData << DCM_EIGHT;
    LusData = LusData | pData[LucIdx];
  }

  return LusData;
}

/*******************************************************************************
** Function Name        : Dcm_RequestParameterToUint32                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function use to get data                       **
**                        from request message and convert it to uint32       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : numOfByte, pData                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LulData                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(uint32, DCM_CODE) Dcm_RequestParameterToUint32(
  uint8 numOfByte,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pData)
{
  uint8 LucIdx;
  uint32 LulData = DCM_ZERO;

  for (LucIdx = DCM_ZERO; LucIdx < numOfByte; LucIdx++)
  {
    /* @Trace: Dcm_SUD_API_20289 */
    LulData = LulData << DCM_EIGHT;
    LulData = LulData | pData[LucIdx];
  }

  return LulData;
}

/*******************************************************************************
** Function Name        : Dcm_RequestParameterToUint64                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function use to get data                       **
**                        from request message and convert it to uint64       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : numOfByte, pData                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LulData                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(uint64, DCM_CODE) Dcm_RequestParameterToUint64(
  uint8 numOfByte,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pData)
{
  uint8 LucIdx;
  uint64 LulData = DCM_ZERO;

  for (LucIdx = DCM_ZERO; LucIdx < numOfByte; LucIdx++)
  {
    /* @Trace: Dcm_SUD_API_20290 */
    LulData = LulData << DCM_EIGHT;
    LulData = LulData | pData[LucIdx];
  }

  return LulData;
}

/*******************************************************************************
** Function Name        : Dcm_DataToResponseParameter                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function use to convert                        **
**                        a series of byte data to response message           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : numOfByte, pInData                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pOutData                                            **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DataToResponseParameter(
  uint8 numOfByte,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pInData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pOutData)
{
  uint8 LucIdx;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpShadowInData = pInData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpShadowOutData = pOutData;

  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* Big endian */
  /* The LpShadowInData will point to the MSB byte */
  for (LucIdx = DCM_ZERO; LucIdx < numOfByte; LucIdx++)
  {
    /* @Trace: Dcm_SUD_API_50908 */
    LpShadowOutData[LucIdx] = (uint8) (*LpShadowInData);
    LpShadowInData++;
  }
  #else
  /* Little endian */
  /* Pointer to the MSB byte at the end of variable address */
  LpShadowInData = &LpShadowInData[numOfByte];
  for (LucIdx = DCM_ZERO; LucIdx < numOfByte; LucIdx++)
  {
    /* @Trace: Dcm_SUD_API_50909 */
    LpShadowInData--;
    LpShadowOutData[LucIdx] = (uint8) (*LpShadowInData);
  }
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_Uint32ToResponseParameter                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function use to convert n byte                 **
**                        from uint32 variable to response message            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : numOfByte, resData                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pResData                                            **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Uint32ToResponseParameter(
  uint8 numOfByte,
  uint32 resData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pResData)
{
  /* @Trace: Dcm_SUD_API_10234 */
  uint32 shadowResData = resData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpActualResData = (uint8*) &shadowResData;
  Dcm_DataToResponseParameter(numOfByte, LpActualResData, pResData);
}

/*******************************************************************************
** Function Name        : Dcm_Uint64ToResponseParameter                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function use to convert n byte                 **
**                        from uint64 variable to response message            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : numOfByte, resData                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pResData                                            **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Uint64ToResponseParameter(
  uint8 numOfByte,
  uint64 resData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pResData)
{
  /* @Trace: Dcm_SUD_API_10235 */
  uint64 shadowResData = resData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpActualResData = (uint8*) &shadowResData;
  Dcm_DataToResponseParameter(numOfByte, LpActualResData, pResData);
}

/*******************************************************************************
** Function Name        : Dcm_CheckParameterByteLen                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function use to check the maximum length       **
**                        of parameter based on number of byte                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : numOfByte, value                                    **
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
FUNC(boolean, DCM_CODE) Dcm_CheckParameterByteLen(
  uint8 numOfByte,
  uint64 value)
{
  /* @Trace: Dcm_SUD_API_11235 */
  boolean LblRetVal = DCM_TRUE;

  /* number of bit = number of byte x 8 */
  uint8 LucNumOfBit = numOfByte << DCM_THREE;

  /*  The length of a number is n bytes, so maximum value of it is 2^n - 1 */
  uint64 LulMaxValue = ((uint64) DCM_ONE << (uint64) LucNumOfBit) - (uint64) DCM_ONE;

  if (value > LulMaxValue)
  {
    /* @Trace: Dcm_SUD_API_11234 */
    LblRetVal = DCM_FALSE;
  }

  return LblRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_GetPeriodicTxPduInfo                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the periodic tx pdu info by RxPduId             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : RxPduId, PerTxPduIdx                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LpPerTxPdu                                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
FUNC(Dcm_PeriodicTxPduPtrType, DCM_CODE) Dcm_GetPeriodicTxPduInfo(
  PduIdType RxPduId,
  uint8 PerTxPduIdx)
{
  /* @Trace: Dcm_SUD_API_11347 */
  Dcm_PduIdTablePtrType LpPduIdTable = NULL_PTR;
  Dcm_PeriodicTxPduPtrType LpPerTxPdu = NULL_PTR;

  if (RxPduId < DCM_NUM_OF_PDUIDTABLECONFIG)
  {
    LpPduIdTable = &Dcm_GaaPduIdTableConfig[RxPduId];

    if (PerTxPduIdx < LpPduIdTable->ucNumPerTxPdu)
    {
      /* @Trace: Dcm_SUD_API_11348 */
      LpPerTxPdu = &LpPduIdTable->pPerTxPdu[PerTxPduIdx];
    }
  }

  return LpPerTxPdu;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_IsProtocolType2                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          :                                                     **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_PROTOCOL_TRANSTYPE2  ==  STD_ON)
FUNC(uint8, DCM_CODE) Dcm_IsProtocolType2(PduIdType Id)
{
  /* @Trace: Dcm_SUD_API_20291 */
  uint8 RetVal = DCM_FALSE;

  if (Id < DCM_NUM_OF_PDUIDTABLECONFIG)
  {
    Dcm_ProtocolType ProtocolType;
    ProtocolType = Dcm_GaaPduIdTableConfig[Id].ProtocolType;
    uint8 ProtocolIdx;
    ProtocolIdx = Dcm_GetProtocolTypeIndex(ProtocolType);
    Dcm_ProtocolTransType PrtclTransType = TYPE1;

    if (ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG)
    {
      /* @Trace: Dcm_SUD_API_20292 */
      PrtclTransType = Dcm_GaaProtocolConfig[ProtocolIdx].ProtocolTransType;
    }

    CHK_RET_VAL(TYPE2 == PrtclTransType, RetVal, DCM_TRUE);
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_GetDataIdFromRequest                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get data identifier from request message            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : offset, pReqData                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(uint16, DCM_CODE) Dcm_GetDataIdFromRequest(
  uint16 offset,
  Dcm_Uint8PtrType pReqData)
{
  /* @Trace: Dcm_SUD_API_50910 */
  uint16 LusDid = DCM_ZERO;

  if (NULL_PTR != pReqData)
  {
    /* @Trace: Dcm_SUD_API_20293 */
    LusDid = (uint16) pReqData[offset] << DCM_EIGHT;
    LusDid = (uint16) LusDid | pReqData[offset + DCM_ONE];
  }

  return LusDid;
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
