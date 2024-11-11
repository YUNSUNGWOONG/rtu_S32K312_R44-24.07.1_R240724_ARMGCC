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
**  SRC-MODULE: Dcm_DspResponseOnEvent.c                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions for UDS services           **
**              implemented by DSP layer of Dcm module                        **
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
** 0.0.1     31-Dec-2019   LamNV10        AR440 Implementation                **
** 0.0.2     14-Jul-2020   LamNV10        Update ResponseOnEvent              **
** 0.0.3     16-Aug-2020   LanhLT         Changes made as per #14836          **
** 0.0.4     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.5     02-Nov-2020   LanhLT         Changes made as per #16832          **
** 0.0.6     04-Dec-2020   LanhLT         Polyspace fixing as per #15175      **
** 0.0.7     21-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.7     16-Dec-2022   LanhLT         Fix UNECE                           **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
** 1.3.0_HF1 13-Jan-2024   SY Kim         Refer #45119                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm_Ram.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DspResponseOnEvent.h"
#include "Dcm_DspServices.h"
#include "Dcm_DslInternal.h"
#include "Rte_Dcm.h"
#if (DCM_NVM_CONFIGURED == STD_ON)
#include "NvM.h"
#endif
#include "Dcm_Config.h"
#include "Dcm_Utils.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)

#define DCM_START_SEC_CODE
#include "MemMap.h"

#define ROE_READ_NVM_TIME (40 * DCM_TASK_TIME)
#define ROE_WRITE_NVM_TIME (40 * DCM_TASK_TIME)

static VAR(uint8, DCM_VAR) Dcm_CurrentROEEventIndex;

static VAR(uint8, DCM_VAR) Dcm_TriggeredROEEventInfo[DCM_NUM_OF_ROE_EVENT_CONFIG];

static VAR(uint8, DCM_VAR) Dcm_PrevTriggeredROEEventInfo[DCM_NUM_OF_ROE_EVENT_CONFIG];

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmSetUpRoeEvent(
  uint8 eventTypeRecordLength
  , P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

static FUNC(boolean, DCM_CODE) Dcm_DspStorageStateAndEventWindowTimeValidation(
  uint8 SubFuntion
  ,Dcm_RoeEventWindowTimeType WindowTimeType);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspROESubFunProcessing(
  uint8 Subfunction
  , Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_DspROEValidation(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_DspROEProcessControlRequest(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

static FUNC(void, DCM_CODE) Dcm_DspROEProcessReportRequest(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

static FUNC(boolean, DCM_CODE) Dcm_DspEventWindowTimeSupportCheck(
  Dcm_RoeEventWindowTimeType ucEventWindowTime);



static FUNC(void, DCM_CODE) Dcm_InternalPreConfigRoe(uint8 indexVal);

static FUNC(void, DCM_CODE) Dcm_InternalUpdateNonVolatileData(
  P2CONST(Dcm_RoeRequestInfo, AUTOMATIC, DCM_APPL_CONST) pData
  ,uint8 Index);

static FUNC(void, DCM_CODE) Dcm_InternalUpdateServiceToRespondTo(
  uint8 IsOnChangeOfDID
  , uint8 Index
  , uint16 EventTypeRecord);

static FUNC(uint8, DCM_CODE) Dcm_IsRoeEventStart(void);

static FUNC(void, DCM_CODE) Dcm_ValidateRoeProtocol(
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_ValidateRequestWhenRoeEventStart(
  uint8 Subfunction
  , Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_RoeSearchDIDEvent(
  uint16 EventTypeRecord
  , Dcm_Uint8PtrType pIndex);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_RoeSearchDTCEvent(
  Dcm_Uint8PtrType pIndex);

static FUNC(void, DCM_CODE) Dcm_RoeClearNVData(void);

static FUNC(void, DCM_CODE) Dcm_InternalUpdateNVState(uint8 Subfunction);

#if (DCM_RESPONSE_ONEVENT_BLOCKID > 0)

static FUNC(void, DCM_CODE) Dcm_StoreRoeEvent(void);

static FUNC(void, DCM_CODE) Dcm_PendingRoeWriteNvmData(void);
static FUNC(void, DCM_CODE) Dcm_CanncelRoeWriteNvmData(void);

static FUNC(void, DCM_CODE) Dcm_CanncelReadRoeNvmData(void);
static FUNC(void, DCM_CODE) Dcm_PendingRoeReadNvmData(void);

#endif /*DCM_RESPONSE_ONEVENT_BLOCKID > 0*/


/*******************************************************************************
** Function Name        : Dcm_DcmSetUpRoeEvent                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is used to store serviceToRespondToRecord  **
**                        in the request message when the sub-function is     **
**                        equal to "ROE set up sub-functions"                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : eventTypeRecordLength                               **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmSetUpRoeEvent(
  uint8 eventTypeRecordLength
  , P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) LpPduIdTable;
  Dcm_MsgLenType LusReqLength;
  Dcm_MsgType LddReqDataPtr;
  Std_ReturnType LddReturnValue = E_NOT_OK;
  uint8 LucDataCount;
  uint8 LucIndex = DCM_ZERO;
  uint16 EventTypeRecord = DCM_ZERO;

  LusReqLength = pMsgContext->reqDataLen;
  LddReqDataPtr = pMsgContext->reqData;

  if (DCM_ROE_ETR_LEN_ONDTCS == eventTypeRecordLength)
  {
    /* @Trace: Dcm_SUD_API_50000 */
    /* Process for onDTCStatusChange */
    EventTypeRecord = LddReqDataPtr[DCM_TWO];
    LddReturnValue = Dcm_RoeSearchDTCEvent(&LucIndex);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_50001 */
    /* Process for onChangeOfDataIdentifier */
    DCM_GET_DATAID_FROM_REQUEST(EventTypeRecord, pMsgContext->reqData, DCM_TWO);
    LddReturnValue = Dcm_RoeSearchDIDEvent(EventTypeRecord, &LucIndex);
  }

  if (E_OK == LddReturnValue)
  {
    /* @Trace: SWS_Dcm_00873 SWS_Dcm_00952 SWS_Dcm_00953 */
    Dcm_GddRoeRequestInfo[LucIndex].ucCurrentState = DCM_ROE_STOPPED;

    /* @Trace: SWS_Dcm_00903 */
    /* polyspace +1 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
    Dcm_GddRoeRequestInfo[LucIndex].EventWindowTime = (Dcm_RoeEventWindowTimeType)
      LddReqDataPtr[DCM_ONE];

    Dcm_GddRoeRequestInfo[LucIndex].ucRxAddrType = pMsgContext->msgAddInfo.reqType;

    /* Update eventTypeRecord */
    if (DCM_ROE_ETR_LEN_ONDTCS == eventTypeRecordLength)
    {
      /* @Trace: Dcm_SUD_API_50002 */
      Dcm_GddRoeRequestInfo[LucIndex].ucEventTypeRecord = EventTypeRecord;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_50003 */
      Dcm_GddRoeRequestInfo[LucIndex].ucEventTypeRecord = EventTypeRecord;
    }

    LpPduIdTable = &Dcm_GaaPduIdTableConfig[pMsgContext->dcmRxPduId];

    #if(DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
    uint8 IsPrtclType2 = Dcm_IsProtocolType2(pMsgContext->dcmRxPduId);
    if (DCM_TRUE == IsPrtclType2)
    {
      /* @Trace: Dcm_SUD_API_50004 */
      Dcm_GddRoeRequestInfo[LucIndex].ddRoeTxPduId = LpPduIdTable->pRoeTxId->ddRoeTxPduId;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_50005 */
      Dcm_GddRoeRequestInfo[LucIndex].ddRoeTxPduId = LpPduIdTable->ddTxPduId;
    }
    #else
    Dcm_GddRoeRequestInfo[LucIndex].ddRoeTxPduId = LpPduIdTable->ddTxPduId;
    #endif

    if (DCM_ROE_ETR_LEN_ONDTCS == eventTypeRecordLength)
    {
      /* @Trace: Dcm_SUD_API_50006 */
      /* Process for onDTCStatusChange */
      Dcm_GddRoeRequestInfo[LucIndex].ddRoeReqDataLen = DCM_TWO;
      Dcm_GddRoeRequestInfo[LucIndex].RoeReqData[DCM_ZERO] = LddReqDataPtr[DCM_THREE];
      Dcm_GddRoeRequestInfo[LucIndex].RoeReqData[DCM_ONE] = LddReqDataPtr[DCM_FOUR];
    }
    else
    {
      /* @Trace: Dcm_SUD_API_50007 */
      /* Process for onChangeOfDataIdentifier */
      Dcm_GddRoeRequestInfo[LucIndex].ddRoeReqDataLen = DCM_THREE;
      Dcm_GddRoeRequestInfo[LucIndex].RoeReqData[DCM_ZERO] = LddReqDataPtr[DCM_FOUR];
      Dcm_GddRoeRequestInfo[LucIndex].RoeReqData[DCM_ONE] = LddReqDataPtr[DCM_TWO];
      Dcm_GddRoeRequestInfo[LucIndex].RoeReqData[DCM_TWO] = LddReqDataPtr[DCM_THREE];
    }

    /* @Trace: SWS_Dcm_00874 */
    if((LddReqDataPtr[DCM_ZERO] & DCM_ROE_STORE_BIT_MASK) == DCM_ROE_STORE_BIT_MASK)
    {
      /* @Trace: Dcm_SUD_API_50008 */
      Dcm_DspServiceProcessingSts.ucRoeStoreRequest = DCM_TRUE;
      Dcm_InternalUpdateNonVolatileData(&Dcm_GddRoeRequestInfo[LucIndex], LucIndex);
      #if (DCM_RESPONSE_ONEVENT_BLOCKID > 0)
      Dcm_StoreRoeEvent();
      #endif
    }

    /* @Trace: Dcm_SUD_API_50009 */
    /* Update the response data */
    pMsgContext->resData[DCM_ZERO] = LddReqDataPtr[DCM_ZERO];

    /* numberOfIdentifiedEvents is equal to zero when the event is set up */
    pMsgContext->resData[DCM_ONE] = DCM_ZERO;

    for (LucDataCount = DCM_ZERO; LucDataCount < LusReqLength; LucDataCount++)
    {
      pMsgContext->resData[LucDataCount + DCM_TWO] = LddReqDataPtr[LucDataCount + DCM_ONE];
    }

    pMsgContext->resDataLen = LusReqLength + DCM_ONE;
  }

  return(LddReturnValue);
}

/*******************************************************************************
** Function Name        : Dcm_DspReadROEDIDValue                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the DID value from the Application          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DIDValue                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DIDSize, pBuffer                                    **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if(DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspReadROEDIDValue(
  uint16 DIDValue
  , P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DIDSize
  , P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pBuffer)
{
  /* @Trace: Dcm_SUD_API_50010 */
  P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_DATA) LpDIDTAB;
  Dcm_DidSignalConfigPtrType LpDcmDspSignal;
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) LpDcmDspData;
  Dcm_NegativeResponseCodeType LddErrorCode;
  Std_ReturnType LddReturnValue;
  uint8 LucSignalIndex;
  uint8 LucSignalCount;
  uint16 DIDIndex;

  LddReturnValue = E_OK;

  /* No need to check returned value because it is always correct here */
  (void) Dcm_GetDidConfigIndex(DIDValue, &DIDIndex);

  LpDIDTAB = &Dcm_GaaDIDParaConfig[DIDIndex];
  LucSignalCount = LpDIDTAB->ucDcmDspSignalCount;
  LpDcmDspSignal = LpDIDTAB->pDcmDspSignal;

  for(LucSignalIndex = DCM_ZERO; LucSignalIndex < LucSignalCount; LucSignalIndex++)
  {
    /* @Trace: Dcm_SUD_API_50028 */
    /* Get the configuration of Data's */
    LpDcmDspData = LpDcmDspSignal->pDataConfig;

    LddReturnValue = E_OK;

    /* Get the DID size from the configured DID */
    *DIDSize = LpDcmDspData->usDcmDspDataByteSize;
    
    switch (LpDcmDspData->ucDcmDspDataUsePort)
    {
      case USE_DATA_ASYNCH_CLIENT_SERVER:
      case USE_DATA_ASYNCH_FNC:
        if (NULL_PTR != LpDcmDspData->pConditionCheckReadAsyncFun)
        {
          /* @Trace: Dcm_SUD_API_50011 */
          LddReturnValue = LpDcmDspData->pConditionCheckReadAsyncFun(
            Dcm_GddOpStatus, &LddErrorCode);
        }

        if (E_OK == LddReturnValue)
        {
          /* Invoke ReadDataLength function to get the length of the DID with variable Length */
          if (DCM_DATA_TYPE_UINT8_DYN == LpDcmDspData->ucDcmDspDataType)
          {
            if (NULL_PTR != LpDcmDspData->pReadDataLengthAsyncFun)
            {
              /* @Trace: Dcm_SUD_API_50012 */
              LddReturnValue = LpDcmDspData->pReadDataLengthAsyncFun(
                Dcm_GddOpStatus, DIDSize);
            }
            else
            {
              /* @Trace: Dcm_SUD_API_50013 */
              LddReturnValue = E_NOT_OK;
            }
          }
          
          if (E_OK == LddReturnValue)
          {
            /* TODO : if func is null. what kinds of error shall we return */
            if (NULL_PTR != LpDcmDspData->pReadDataAsyncFun)
            {
              /* @Trace: Dcm_SUD_API_50014 */
              LddReturnValue = LpDcmDspData->pReadDataAsyncFun(
                Dcm_GddOpStatus, pBuffer);
            }
          }
        }
        break;

      case USE_DATA_SYNCH_FNC:
      case USE_DATA_SYNCH_CLIENT_SERVER:
        if (NULL_PTR != LpDcmDspData->pConditionCheckReadSyncFun)
        {
          /* @Trace: Dcm_SUD_API_50016 */
          LddReturnValue = LpDcmDspData->pConditionCheckReadSyncFun(
            &LddErrorCode);
        }
          
        if (E_OK == LddReturnValue)
        {
          /* Invoke ReadDataLength function to get the length of the DID with variable Length */
          if (DCM_DATA_TYPE_UINT8_DYN == LpDcmDspData->ucDcmDspDataType)
          {
            if (NULL_PTR != LpDcmDspData->pReadDataLengthSyncFun)
            {
              /* @Trace: Dcm_SUD_API_50017 */
              LddReturnValue = LpDcmDspData->pReadDataLengthSyncFun(DIDSize);
            }
          }
          
          if (E_OK == LddReturnValue)
          {
            if (NULL_PTR != LpDcmDspData->pReadDataSyncFun)
            {
              /* @Trace: Dcm_SUD_API_50019 */
              LddReturnValue = LpDcmDspData->pReadDataSyncFun(pBuffer);
            }
          }
        }
        break;

      case USE_ECU_SIGNAL:
      {
        uint8 i = LpDcmDspData->ucEcuSignalFunctionIndex;
        /* polyspace +1 MISRA2012:16.1 MISRA2012:16.6 [Justified:Low] Justify with annotations */
        switch(LpDcmDspData->ucDcmDspDataType)
        {
          #if (DCM_DSP_USE_ECU_SIGNAL_UINT8 == STD_ON)
          case DCM_DATA_TYPE_UINT8:
            if (NULL_PTR != Dcm_GaaEcuSignalUint8Func[i].pDataReadEcuSignalUint8)
            {
              /* @Trace: Dcm_SUD_API_50021 */
              Dcm_GaaEcuSignalUint8Func[i].pDataReadEcuSignalUint8(pBuffer);
            }
            break;
          #endif

          #if (DCM_DSP_USE_ECU_SIGNAL_UINT16 == STD_ON)
          case DCM_DATA_TYPE_UINT16:
            if (NULL_PTR != Dcm_GaaEcuSignalUint16Func[i].pDataReadEcuSignalUint16)
            {
              /* @Trace: Dcm_SUD_API_50022 */
              Dcm_GaaEcuSignalUint16Func[i].pDataReadEcuSignalUint16(
                (P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA)) pBuffer);
            }
            break;
          #endif

          #if (DCM_DSP_USE_ECU_SIGNAL_UINT32 == STD_ON)
          case DCM_DATA_TYPE_UINT32:
            if (NULL_PTR != Dcm_GaaEcuSignalUint32Func[i].pDataReadEcuSignalUint32)
            {
              /* @Trace: Dcm_SUD_API_50023 */
              Dcm_GaaEcuSignalUint32Func[i].pDataReadEcuSignalUint32(
                (P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)) pBuffer);
            }
            break;
          #endif

          #if (DCM_DSP_USE_ECU_SIGNAL_SINT8 == STD_ON)
          case DCM_DATA_TYPE_SINT8:
            if (NULL_PTR != Dcm_GaaEcuSignalSint8Func[i].pDataReadEcuSignalSint8)
            {
              /* @Trace: Dcm_SUD_API_50024 */
              Dcm_GaaEcuSignalSint8Func[i].pDataReadEcuSignalSint8(
                (P2VAR(sint8, AUTOMATIC, DCM_APPL_DATA)) pBuffer);
            }
            break;
          #endif

          #if (DCM_DSP_USE_ECU_SIGNAL_SINT16 == STD_ON)
          case DCM_DATA_TYPE_SINT16:
            if (NULL_PTR != Dcm_GaaEcuSignalSint16Func[i].pDataReadEcuSignalSint16)
            {
              /* @Trace: Dcm_SUD_API_50025 */
              Dcm_GaaEcuSignalSint16Func[i].pDataReadEcuSignalSint16(
                (P2VAR(sint16, AUTOMATIC, DCM_APPL_DATA)) pBuffer);
            }
            break;
          #endif

          #if (DCM_DSP_USE_ECU_SIGNAL_SINT32 == STD_ON)
          case DCM_DATA_TYPE_SINT32:
            if (NULL_PTR != Dcm_GaaEcuSignalSint32Func[i].pDataReadEcuSignalSint32)
            {
              /* @Trace: Dcm_SUD_API_50026 */
              Dcm_GaaEcuSignalSint32Func[i].pDataReadEcuSignalSint32(
                (P2VAR(sint32, AUTOMATIC, DCM_APPL_DATA)) pBuffer);
            }
            break;
          #endif

          default:
            /* @Trace: Dcm_SUD_API_50027 */
            DCM_UNUSED(i);
            break;
        }
        break;
      }

      default:
        /* No action in this case */
        break;
    }
  }

  return (LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspManagedDIDInternally                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is enable ROE events.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked: Dcm_DspReadROEDIDValue         **
**                                                                            **
*******************************************************************************/
#if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspManagedDIDInternally(void)
{
  /* @Trace: Dcm_SUD_API_50029 */
  for (uint8 LucIndex = DCM_ZERO; LucIndex < DCM_NUM_OF_ROE_EVENT_CONFIG; LucIndex++)
  {
    if ((Dcm_GddRoeRequestInfo[LucIndex].ucCurrentState == DCM_ROE_STARTED) &&
        (Dcm_GddRoeRequestInfo[LucIndex].RoeConfig.blIsOnChngOfDIDRxed == DCM_TRUE))
    {
      /* @Trace: Dcm_SUD_API_50030 */
      /* Get DID data to manage internally */
      (void) Dcm_DspReadROEDIDValue(
        *(Dcm_GddRoeRequestInfo[LucIndex].RoeConfig.pRoeDidRef),
        &Dcm_GddRoeRequestInfo[LucIndex].usDIDValueSize,
        &Dcm_GddRoeRequestInfo[LucIndex].ucInternalBuffer[DCM_ZERO]);
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmResponseOnEvent                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The ResponseOnEvent service starts or stops the     **
**                        transmission of responses on a specified Event.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError            **
**                                                                            **
**                        Function(s) invoked:                                **
**                                             Dcm_DcmSetUpRoeEvent,          **
**                                             Dcm_DspManagedDIDInternally,   **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04100 SRS_Diag_04160 */
/* @Trace: SWS_Dcm_00595 */
/* polyspace +4 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmResponseOnEvent(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_50031 */
  Std_ReturnType RetVal = E_NOT_OK;
  Dcm_MsgType LddReqDataPtr;
  uint8 SubFunction;

  /* Validating requested msg */
  Dcm_GddNegRespError = DCM_POS_RESP;

  Dcm_DspROEValidation(pMsgContext, &Dcm_GddNegRespError);

  LddReqDataPtr = pMsgContext->reqData;
  SubFunction = LddReqDataPtr[DCM_ZERO];

  if (DCM_POS_RESP == Dcm_GddNegRespError)
  {
    /* @Trace: Dcm_SUD_API_50032 */
    RetVal = Dcm_DspROESubFunProcessing(
      (SubFunction & DCM_ROE_SUBFUNCTION_MASK)
      , pMsgContext);
  }

  /* Send response from main function */
  Dcm_GblSendResponse = DCM_TRUE;
  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_InternalUpdateNVState                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal update non-volatile state                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Subfunction                                         **
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
static FUNC(void, DCM_CODE) Dcm_InternalUpdateNVState(uint8 Subfunction)
{
  if (DCM_START_ROE == Subfunction)
  {
    /* @Trace: Dcm_SUD_API_50033 */
    Dcm_GaaRoeNonVolatileData.Data.NVState = DCM_ROE_STARTED;
    Dcm_GaaRoeNonVolatileData.Data.NVActiveSession = Dcm_GddCurrentSession;
  }

  if (DCM_CLEAR_ROE == Subfunction)
  {
    /* @Trace: Dcm_SUD_API_50034 */
    Dcm_RoeClearNVData();
  }

  /* @Trace: Dcm_SUD_API_50035 */
  CHK_RET_VAL(DCM_STOP_ROE == Subfunction, \
    Dcm_GaaRoeNonVolatileData.Data.NVState, DCM_ROE_STOPPED);
}

/*******************************************************************************
** Function Name        : Dcm_StoreRoeEvent                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function stores the ROE event in NvM           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucSubFunction                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
#if (DCM_RESPONSE_ONEVENT_BLOCKID > 0)
static FUNC(void, DCM_CODE) Dcm_StoreRoeEvent(void)
{
  /* @Trace: Dcm_SUD_API_50036 */
  Std_ReturnType ReturnValue;
  NvM_SetBlockLockStatus(DCM_RESPONSE_ONEVENT_BLOCKID, DCM_FALSE);

  ReturnValue = NvM_WriteBlock(DCM_RESPONSE_ONEVENT_BLOCKID, 
    &Dcm_GaaRoeNonVolatileData.NVDataBuffer[DCM_ZERO]);

  if (ReturnValue == E_OK)
  {
    /* @Trace: SRS_Diag_04171 */
    /* @Trace: Dcm_SUD_API_50037 */
    Dcm_StartTimerExt(
      DCM_ROE_ACCESS_NVRAM_TIMER
      , ROE_WRITE_NVM_TIME
      , Dcm_PendingRoeWriteNvmData
      , Dcm_CanncelRoeWriteNvmData);
  } 
}
#endif
/*******************************************************************************
** Function Name        : Dcm_PendingRoeWriteNvmData                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Pending process function for write NvM data action  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : void                                                **
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
#if (DCM_RESPONSE_ONEVENT_BLOCKID > 0)
static FUNC(void, DCM_CODE) Dcm_PendingRoeWriteNvmData(void)
{
  /* @Trace: Dcm_SUD_API_50038 */
  NvM_RequestResultType ReqResult;

  Std_ReturnType RetVal = NvM_GetErrorStatus(
    DCM_RESPONSE_ONEVENT_BLOCKID, &ReqResult);

  if ((E_OK == RetVal) && (NVM_REQ_OK == ReqResult))
  {
    /* @Trace: Dcm_SUD_API_50039 */
    NvM_SetBlockLockStatus(DCM_RESPONSE_ONEVENT_BLOCKID, DCM_TRUE);
    Dcm_StopTimer(DCM_ROE_ACCESS_NVRAM_TIMER);
  }
}

/*******************************************************************************
** Function Name        : Dcm_CanncelRoeWriteNvmData                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Cancel process function for write NvM data action   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : void                                                **
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
static FUNC(void, DCM_CODE) Dcm_CanncelRoeWriteNvmData(void)
{
  /* @Trace: Dcm_SUD_API_50040 */
  NvM_CancelJobs(DCM_RESPONSE_ONEVENT_BLOCKID);
  NvM_SetBlockLockStatus(DCM_RESPONSE_ONEVENT_BLOCKID, DCM_TRUE);
}
#endif /*DCM_RESPONSE_ONEVENT_BLOCKID > 0*/

/*******************************************************************************
** Function Name        : Dcm_RoeSearchDIDEvent                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Search did event function                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : EventTypeRecord                                     **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pIndex                                              **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_RoeSearchDIDEvent(
  uint16 EventTypeRecord
  , Dcm_Uint8PtrType pIndex)
{
  Std_ReturnType RetVal = E_NOT_OK;

  if (NULL_PTR == pIndex)
  {
    /* @Trace: Dcm_SUD_API_50041 */
    RetVal = E_NOT_OK;
  }
  else
  {
    for(uint8 LucIndex = DCM_ZERO ; LucIndex < DCM_NUM_OF_ROE_EVENT_CONFIG; LucIndex++)
    {
      if (Dcm_GaaDcmDspRoeCfg[LucIndex].blIsOnChngOfDIDRxed == DCM_TRUE)
      {
        if (EventTypeRecord == *(Dcm_GaaDcmDspRoeCfg[LucIndex].pRoeDidRef))
        {
          /* @Trace: Dcm_SUD_API_50042 */
          Dcm_GddRoeRequestInfo[LucIndex].RoeConfig = Dcm_GaaDcmDspRoeCfg[LucIndex];
          *pIndex = LucIndex;
          RetVal = E_OK;
          break;
        }
      }
    }
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_RoeSearchDTCEvent                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Search DTC event function                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pIndex                                              **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_RoeSearchDTCEvent(
  Dcm_Uint8PtrType pIndex)
{
  /* @Trace: Dcm_SUD_API_50043 */
  Std_ReturnType RetVal = E_NOT_OK;

  if ((pIndex != NULL_PTR) &&
      (DCM_ROE_ONDTCSTATUS_CHANGE_INDEX != 0xFF))
  {
    /* @Trace: Dcm_SUD_API_50044 */
     *pIndex = DCM_ROE_ONDTCSTATUS_CHANGE_INDEX;
    RetVal = E_OK;
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspStorageStateAndEventWindowTimeValidation     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Storage State And Event Window Time Validation      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : SubFuntion, WindowTimeType                          **
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
static FUNC(boolean, DCM_CODE) Dcm_DspStorageStateAndEventWindowTimeValidation(
  uint8 SubFuntion
  , Dcm_RoeEventWindowTimeType WindowTimeType)
{
  /* @Trace: Dcm_SUD_API_50045 */
  boolean Retval;
  Retval = Dcm_DspEventWindowTimeSupportCheck(WindowTimeType);

  if ((DCM_TRUE == Retval)
      && ((SubFuntion & DCM_ROE_STORE_BIT_MASK) == DCM_ROE_STORE_BIT_MASK)
      && (WindowTimeType == DCM_ROE_EVENT_WINDOW_CURRENT_CYCLE))
  {
    /* @Trace: Dcm_SUD_API_50046 */
    Retval = DCM_FALSE;
  }

  return Retval;
}

/*******************************************************************************
** Function Name        : Dcm_DspROEValidation                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate roe request message                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(void, DCM_CODE) Dcm_DspROEValidation(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_50047 */
  Dcm_MsgLenType LusReqLength;
  Dcm_MsgType LddReqDataPtr;
  uint8 LucSubFunction;
  Dcm_RoeEventWindowTimeType LucEventWindowTime;
  uint8 LucStoreBit;
  boolean LblValidateResult;

  /* polyspace +3 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
  LusReqLength = pMsgContext->reqDataLen;
  LddReqDataPtr = pMsgContext->reqData;
  LucEventWindowTime = (Dcm_RoeEventWindowTimeType)LddReqDataPtr[DCM_ONE];
  *pErrorCode = DCM_POS_RESP;

  /* @Trace: SWS_Dcm_01076 SWS_Dcm_00894 SWS_Dcm_00896 SWS_Dcm_00903*/
  LblValidateResult = Dcm_DspStorageStateAndEventWindowTimeValidation(
    LddReqDataPtr[DCM_ZERO], LucEventWindowTime);

  if (DCM_FALSE == LblValidateResult)
  {
    /* @Trace: Dcm_SUD_API_50048 */
    *pErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }

  if (*pErrorCode == DCM_POS_RESP)
  {
    LucSubFunction = (uint8)(LddReqDataPtr[DCM_ZERO] & (DCM_ROE_SUBFUNCTION_MASK));

    switch(LucSubFunction)
    {
      case DCM_ON_DTC_STATUS_CHANGE:
      case DCM_ON_CHANGE_OF_DID:
        if (LusReqLength != DCM_ROE_SETUP_REQ_LEN)
        {
          /* @Trace: Dcm_SUD_API_50049 */
          *pErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        break;

      case DCM_STOP_ROE:
      case DCM_START_ROE:
      case DCM_REPORT_ACTIVATED_EVENTS:
      case DCM_CLEAR_ROE:
        if(LusReqLength != DCM_ROE_CONTROL_REQ_LEN)
        {
          /* @Trace: Dcm_SUD_API_50050 */
          *pErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        break;

      default:
        /* @Trace: Dcm_SUD_API_50051 */
        *pErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        break;
    }

    if (DCM_POS_RESP == *pErrorCode)
    {
      /* @Trace: Dcm_SUD_API_50052 */
      Dcm_ValidateRequestWhenRoeEventStart(LucSubFunction, pErrorCode);
    }

    if ((DCM_POS_RESP == *pErrorCode) &&
       ((DCM_STOP_ROE == LucSubFunction) || (DCM_START_ROE == LucSubFunction)))
    {
      /* @Trace: Dcm_SUD_API_50056 */
      uint8 LucTotalClearedRoe = DCM_ZERO;
      LucStoreBit = (uint8)(LddReqDataPtr[DCM_ZERO] & (DCM_ROE_STORE_BIT_MASK));

      for(uint8 LucIndex = DCM_ZERO; LucIndex < DCM_NUM_OF_ROE_EVENT_CONFIG; LucIndex++)
      {
        if (DCM_ROE_CLEARED == Dcm_GddRoeRequestInfo[LucIndex].ucCurrentState)
        {
          /* @Trace: Dcm_SUD_API_50053 */
          LucTotalClearedRoe++;
        }

        /* @Trace: SWS_Dcm_01076 */
        if ((DCM_ROE_STORE_BIT_MASK == LucStoreBit)
            && (DCM_ROE_EVENT_WINDOW_INFINITE != LucEventWindowTime)
            && ((DCM_ROE_STARTED == Dcm_GddRoeRequestInfo[LucIndex].ucCurrentState) 
                || (DCM_ROE_STOPPED == Dcm_GddRoeRequestInfo[LucIndex].ucCurrentState)))
        {
          /* @Trace: Dcm_SUD_API_50054 */
          *pErrorCode = DCM_E_REQUESTOUTOFRANGE;
          break;
        }
      }

      /* @Trace: SWS_Dcm_00885 SWS_Dcm_00886 */
      if (DCM_NUM_OF_ROE_EVENT_CONFIG == LucTotalClearedRoe)
      {
        /* @Trace: Dcm_SUD_API_50055 */
        *pErrorCode = DCM_E_REQUESTSEQUENCEERROR;
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_ValidateRequestWhenRoeEventStart                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate Request When Roe Event Start               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Subfunction                                         **
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
/* @Trace: SWS_Dcm_00940 SWS_Dcm_00929, SWS_Dcm_00930*/
static FUNC(void, DCM_CODE) Dcm_ValidateRequestWhenRoeEventStart(
  uint8 Subfunction
  , Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_50057 */
  if ((DCM_STOP_ROE != Subfunction) && (DCM_CLEAR_ROE != Subfunction))
  {
    if (DCM_TRUE == Dcm_IsRoeEventStart())
    {
      /* @Trace: Dcm_SUD_API_50058 */
      Dcm_ValidateRoeProtocol(pErrorCode);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_ValidateRoeProtocol                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate Roe Protocol                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
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
static FUNC(void, DCM_CODE) Dcm_ValidateRoeProtocol(
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_50059 */
  uint8 PrtclStartEventType = DCM_ZERO;
  uint8 CurrentPrtclType = DCM_ZERO;
  PduIdType EventStartPduId = DCM_MAXVALUE;

  for (uint8 idx = DCM_ZERO; idx < DCM_NUM_OF_ROE_EVENT_CONFIG; idx++)
  {
    if (DCM_ROE_STARTED == Dcm_GddRoeRequestInfo[idx].ucCurrentState)
    {
      /* @Trace: Dcm_SUD_API_50060 */
      EventStartPduId = Dcm_GddRoeRequestInfo[idx].ddRoeRxPduId;
      break;
    }
  }

  if (EventStartPduId < DCM_NUM_OF_ROE_EVENT_CONFIG)
  {
    /* @Trace: Dcm_SUD_API_50061 */
    PrtclStartEventType = Dcm_GaaPduIdTableConfig[EventStartPduId].ProtocolType;
    CurrentPrtclType = Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ProtocolType;
  }

  if (PrtclStartEventType != CurrentPrtclType)
  {
    /* @Trace: Dcm_SUD_API_50062 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspROEProcessControlRequest                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Control Request function                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
/* Make sure valid input msg before calling this function */
static FUNC(void, DCM_CODE) Dcm_DspROEProcessControlRequest(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dcm_MsgType LddReqDataPtr;
  uint8 LucSubFunction;
  uint8 LucEventWindowTime;
  uint8 LucIndex;
  uint8 LucStoreBit;

  LddReqDataPtr = pMsgContext->reqData;
  LucEventWindowTime = LddReqDataPtr[DCM_ONE];

  /* Check the subfunction value */
  LucSubFunction = (uint8)(LddReqDataPtr[DCM_ZERO] & (DCM_ROE_SUBFUNCTION_MASK));
  LucStoreBit = (uint8)(LddReqDataPtr[DCM_ZERO] & (DCM_ROE_STORE_BIT_MASK));

  switch(LucSubFunction)
  {
    case DCM_STOP_ROE:
      /* @Trace: SWS_Dcm_00877 SWS_Dcm_00891 */
      /* The stopped RoeEvents change to the 'ROE stopped' state */
      for (LucIndex = DCM_ZERO; LucIndex < DCM_NUM_OF_ROE_EVENT_CONFIG; LucIndex++)
      {
        if (DCM_ROE_STARTED == Dcm_GddRoeRequestInfo[LucIndex].ucCurrentState)
        {
          /* @Trace: Dcm_SUD_API_50064 */
          Dcm_GddRoeRequestInfo[LucIndex].ucCurrentState = DCM_ROE_STOPPED;
        }
      }
      break;

    case DCM_START_ROE:
      /* @Trace: SWS_Dcm_00876 SWS_Dcm_00880 SWS_Dcm_00930 */
      /* all stopped RoeEvents change to the 'ROE started' state */
      for(LucIndex = DCM_ZERO; LucIndex < DCM_NUM_OF_ROE_EVENT_CONFIG; LucIndex++)
      {
        if (DCM_ROE_STOPPED == Dcm_GddRoeRequestInfo[LucIndex].ucCurrentState)
        {
          /* @Trace: Dcm_SUD_API_50065 */
          Dcm_GddRoeRequestInfo[LucIndex].ucCurrentState = DCM_ROE_STARTED;

          /* @Trace: SWS_Dcm_00127 */
          Dcm_GddRoeRequestInfo[LucIndex].ddRoeRxPduId = pMsgContext->dcmRxPduId;
          Dcm_GddRoeRequestInfo[LucIndex].ucSessionActive = Dcm_GddCurrentSession;
        }
      }

      /* @Trace: Dcm_SUD_API_50066 */
      #if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
      Dcm_DspManagedDIDInternally();
      #endif
      break;

    case DCM_CLEAR_ROE:
      /* @Trace: SWS_Dcm_00884 SWS_Dcm_00887 SWS_Dcm_00875 */
      for (LucIndex = DCM_ZERO; LucIndex < DCM_NUM_OF_ROE_EVENT_CONFIG; LucIndex++)
      {
        /* @Trace: Dcm_SUD_API_50067 */
        Dcm_GddRoeRequestInfo[LucIndex].ucCurrentState = DCM_ROE_CLEARED;
      }
      break;

    default:
      /* No action in this case */
      break;
  }

  /* @Trace: Dcm_SUD_API_50063 */
  /* Update the response data */
  pMsgContext->resData[DCM_ZERO] = LddReqDataPtr[DCM_ZERO];
  pMsgContext->resData[DCM_ONE] = DCM_ZERO;
  pMsgContext->resData[DCM_TWO] = LucEventWindowTime;
  pMsgContext->resDataLen = DCM_THREE;

  if ((LucStoreBit == DCM_ROE_STORE_BIT_MASK) && 
      (DCM_TRUE == Dcm_DspServiceProcessingSts.ucRoeStoreRequest))
  {
    /* @Trace: Dcm_SUD_API_50068 */
    /* @Trace: SWS_Dcm_00965 SWS_Dcm_00890*/
    Dcm_InternalUpdateNVState(LucSubFunction);

    #if (DCM_RESPONSE_ONEVENT_BLOCKID > 0)
    Dcm_StoreRoeEvent();
    #endif
  }

  /* do not need to store event data after clear */
  if (LucSubFunction == DCM_CLEAR_ROE)
  {
    Dcm_DspServiceProcessingSts.ucRoeStoreRequest = DCM_FALSE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspROEProcessReportRequest                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Report Request function                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
/* Make sure valid input msg before calling this function */
static FUNC(void, DCM_CODE) Dcm_DspROEProcessReportRequest(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dcm_MsgType LddReqDataPtr;
  uint8 LucSubFunction;
  uint8 LucNumOfActivatedEvents;

  /* @Trace: Dcm_SUD_API_50069 */
  LddReqDataPtr = pMsgContext->reqData;

  /* Check the subfunction value */
  LucSubFunction = (uint8)(LddReqDataPtr[DCM_ZERO] & (DCM_ROE_SUBFUNCTION_MASK));

  if (DCM_REPORT_ACTIVATED_EVENTS == LucSubFunction)
  {
    /* @Trace: Dcm_SUD_API_50070 */
    /* Initialize numberOfActivatedEents */
    LucNumOfActivatedEvents = DCM_ZERO;

    /* Initialize Response Message Index */
    pMsgContext->resDataLen = DCM_TWO;

    for(uint8 LucIndex = DCM_ZERO; LucIndex < DCM_NUM_OF_ROE_EVENT_CONFIG; LucIndex++)
    {
      if(Dcm_GddRoeRequestInfo[LucIndex].ucCurrentState == DCM_ROE_STARTED)
      {
        /* Count up numberOfActivatedEents */
        LucNumOfActivatedEvents++;

        if (Dcm_GddRoeRequestInfo[LucIndex].RoeConfig.blIsOnChngOfDIDRxed != DCM_TRUE)
        {
          if(Dcm_DspServiceProcessingSts.ucRoeStoreRequest == DCM_TRUE)
          {
            /* @Trace: Dcm_SUD_API_50071 */
            pMsgContext->resData[pMsgContext->resDataLen] = DCM_ON_DTC_STATUS_CHANGE_STOREBIT;
            pMsgContext->resDataLen++;
          }
          else
          {
            /* @Trace: Dcm_SUD_API_50072 */
            pMsgContext->resData[pMsgContext->resDataLen] = DCM_ON_DTC_STATUS_CHANGE;
            pMsgContext->resDataLen++;
          }

          pMsgContext->resData[pMsgContext->resDataLen] = 
            (uint8) Dcm_GddRoeRequestInfo[LucIndex].EventWindowTime;

          pMsgContext->resDataLen++;

          pMsgContext->resData[pMsgContext->resDataLen] = 
            (uint8) Dcm_GddRoeRequestInfo[LucIndex].ucEventTypeRecord;

          pMsgContext->resDataLen++;
        }
        else
        {
          if(Dcm_DspServiceProcessingSts.ucRoeStoreRequest == DCM_TRUE)
          {
            /* @Trace: Dcm_SUD_API_50073 */
            pMsgContext->resData[pMsgContext->resDataLen] = DCM_ON_CHANGE_OF_DID_STOREBIT;
            pMsgContext->resDataLen++;
          }
          else
          {
            /* @Trace: Dcm_SUD_API_50074 */
            pMsgContext->resData[pMsgContext->resDataLen] = DCM_ON_CHANGE_OF_DID;
            pMsgContext->resDataLen++;
          }

          pMsgContext->resData[pMsgContext->resDataLen] = 
            (uint8) Dcm_GddRoeRequestInfo[LucIndex].EventWindowTime;

          pMsgContext->resDataLen++;

          Dcm_MemCopy(&pMsgContext->resData[pMsgContext->resDataLen],
            (uint8*) &Dcm_GddRoeRequestInfo[LucIndex].ucEventTypeRecord, DCM_TWO);

          pMsgContext->resDataLen += DCM_TWO;
        }

        /* @Trace: Dcm_SUD_API_50076 */
        for (uint8 LucCount = DCM_ZERO; 
             LucCount < Dcm_GddRoeRequestInfo[LucIndex].ddRoeReqDataLen;
             LucCount++)
        {
          pMsgContext->resData[pMsgContext->resDataLen] = 
            Dcm_GddRoeRequestInfo[LucIndex].RoeReqData[LucCount];

          pMsgContext->resDataLen++;
        }

        /* If onChangeOfDataIdentifier event, 
         * remove 2 byte of DID cause of it was include in eventTypeRecord */
        if (DCM_TRUE == Dcm_GddRoeRequestInfo[LucIndex].RoeConfig.blIsOnChngOfDIDRxed)
        {
          /* @Trace: Dcm_SUD_API_50075 */
          pMsgContext->resDataLen -= DCM_TWO;
        }
      }
    }

    /* Update the response data */
    pMsgContext->resData[DCM_ZERO] = DCM_REPORT_ACTIVATED_EVENTS;
    pMsgContext->resData[DCM_ONE] = LucNumOfActivatedEvents;
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspROEProcessSessionChange                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Session Change function                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
/* Processing function when session change happens */
FUNC(void, DCM_CODE) Dcm_DspROEProcessSessionChange(void)
{
  if (DCM_DEFAULT_SESSION != Dcm_GddCurrentSession)
  {
    for (uint8 idx = DCM_ZERO; idx < DCM_NUM_OF_ROE_EVENT_CONFIG; idx++)
    {
      /* @Trace: SWS_Dcm_00879 */
      /* @Trace: Dcm_SUD_API_50077 */
      /* Stop all started ROE when session change */
      CHK_RET_VAL(DCM_ROE_STARTED == Dcm_GddRoeRequestInfo[idx].ucCurrentState, \
        Dcm_GddRoeRequestInfo[idx].ucCurrentState, DCM_ROE_STOPPED);
    }
  }
  else
  {
    for (uint8 idx = DCM_ZERO; idx < DCM_NUM_OF_ROE_EVENT_CONFIG; idx++)
    {
      /* @Trace: SWS_Dcm_00902 */
      if ((DCM_ROE_STOPPED == Dcm_GddRoeRequestInfo[idx].ucCurrentState) &&
          (DCM_DEFAULT_SESSION == Dcm_GddRoeRequestInfo[idx].ucSessionActive))
      {
        /* @Trace: Dcm_SUD_API_50078 */
        Dcm_GddRoeRequestInfo[idx].ucCurrentState = DCM_ROE_STARTED;
      }
      else
      {
        /* @Trace: SWS_Dcm_00879 */
        /* @Trace: Dcm_SUD_API_50079 */
        CHK_RET_VAL(DCM_ROE_STARTED == Dcm_GddRoeRequestInfo[idx].ucCurrentState, \
          Dcm_GddRoeRequestInfo[idx].ucCurrentState, DCM_ROE_STOPPED);
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspEventWindowTimeSupportCheck                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if event window time is valid or not          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ucEventWindowTime                                   **
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
static FUNC(boolean, DCM_CODE) Dcm_DspEventWindowTimeSupportCheck(
  Dcm_RoeEventWindowTimeType ucEventWindowTime)
{
  /* @Trace: Dcm_SUD_API_50080 */
  boolean ret = DCM_FALSE;

  for (uint8 idx = DCM_ZERO; idx < DCM_NUM_OF_EVENTWINDOWTIME_SUPPORTED; idx++)
  {
    if (ucEventWindowTime == Dcm_GaaEventWindowTimeSupport[idx])
    {
      /* @Trace: Dcm_SUD_API_50081 */
      ret = DCM_TRUE;
      break;
    }
  }

  return ret;
}

/*******************************************************************************
** Function Name        : Dcm_DspROESubFunProcessing                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to process roe sub-function           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Subfunction                                         **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00892 */
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspROESubFunProcessing(
  uint8 Subfunction
  , Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_50110 */
  Std_ReturnType Retval = E_OK;
  uint8 SubFLength;

  switch(Subfunction)
  {
    case DCM_STOP_ROE:
    case DCM_START_ROE:
    case DCM_CLEAR_ROE:
      /* @Trace: Dcm_SUD_API_50082 */
      Dcm_DspROEProcessControlRequest(pMsgContext);
      break;

    case DCM_ON_DTC_STATUS_CHANGE:
    case DCM_ON_CHANGE_OF_DID:
      SubFLength = (DCM_ON_DTC_STATUS_CHANGE == Subfunction) 
                    ? DCM_ROE_ETR_LEN_ONDTCS : DCM_ROE_ETR_LEN_OCODID;

      if (E_OK != Dcm_DcmSetUpRoeEvent(SubFLength, pMsgContext))
      {
        /* @Trace: SWS_Dcm_00918 */
        /* @Trace: Dcm_SUD_API_50083 */
        Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
        Retval = E_NOT_OK;
      }
      break;

    case DCM_REPORT_ACTIVATED_EVENTS:
      /* @Trace: Dcm_SUD_API_50084 */
      Dcm_DspROEProcessReportRequest(pMsgContext);
      break;

    default:
      /* @Trace: Dcm_SUD_API_50085 */
      Dcm_GddNegRespError = DCM_E_SUBFUNCTIONNOTSUPPORTED;
      Retval = E_NOT_OK;
      break;
  }

  return Retval;
}

/*******************************************************************************
** Function Name        : Dcm_InternalUpdateNonVolatileData                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal Update Non Volatile Data                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pData, Index                                        **
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
static FUNC(void, DCM_CODE) Dcm_InternalUpdateNonVolatileData(
  P2CONST(Dcm_RoeRequestInfo, AUTOMATIC, DCM_APPL_CONST) pData
  , uint8 Index)
{
  /* @Trace: Dcm_SUD_API_50086 */
  if ((NULL_PTR != pData) && (Index < DCM_NUM_OF_ROE_EVENT_CONFIG))
  {
    /* @Trace: Dcm_SUD_API_50087 */
    Dcm_GaaRoeNonVolatileData.Data.NVEventWindowTime = pData->EventWindowTime;
    Dcm_GaaRoeNonVolatileData.Data.NVState = pData->ucCurrentState;
    Dcm_GaaRoeNonVolatileData.Data.NVEventTypeRecord = pData->ucEventTypeRecord;
    Dcm_GaaRoeNonVolatileData.Data.IsOnChangeOfDID = pData->RoeConfig.blIsOnChngOfDIDRxed;
    Dcm_GaaRoeNonVolatileData.Data.NVRoeEventId = pData->RoeConfig.ucRoeEventId;
    Dcm_GaaRoeNonVolatileData.Data.NVIndex = Index;
    Dcm_GaaRoeNonVolatileData.Data.NVActiveSession = pData->ucSessionActive;
  }
}

/*******************************************************************************
** Function Name        : Dcm_CanncelReadRoeNvmData                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Canncel Read Roe Nvm Data operation                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
#if (DCM_RESPONSE_ONEVENT_BLOCKID > 0)
static FUNC(void, DCM_CODE) Dcm_CanncelReadRoeNvmData(void)
{
  /* @Trace: Dcm_SUD_API_50088 */
  (void) NvM_CancelJobs(DCM_RESPONSE_ONEVENT_BLOCKID);
}

/*******************************************************************************
** Function Name        : Dcm_PendingRoeReadNvmData                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Pending process for Read Roe Nvm Data operation     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
static FUNC(void, DCM_CODE) Dcm_PendingRoeReadNvmData(void)
{
  /* @Trace: Dcm_SUD_API_50089 */
  NvM_RequestResultType ReqResult = NVM_REQ_NOT_OK;
  uint8 LucIndex = DCM_ZERO;

  Std_ReturnType RetVal = NvM_GetErrorStatus(
    DCM_RESPONSE_ONEVENT_BLOCKID, &ReqResult);

  if ((E_OK == RetVal) && (NVM_REQ_OK == ReqResult))
  {
    /* @Trace: Dcm_SUD_API_50090 */
    Dcm_StopTimer(DCM_ROE_ACCESS_NVRAM_TIMER);

    if ((DCM_ROE_CLEARED != Dcm_GaaRoeNonVolatileData.Data.NVState)
      && (DCM_ROE_EVENT_WINDOW_CURRENT_CYCLE !=
            Dcm_GaaRoeNonVolatileData.Data.NVEventWindowTime))
    {
      /* @Trace: Dcm_SUD_API_50091 */
      uint8 Index = Dcm_GaaRoeNonVolatileData.Data.NVIndex;

      Dcm_GddRoeRequestInfo[Index].EventWindowTime = 
        Dcm_GaaRoeNonVolatileData.Data.NVEventWindowTime;

      Dcm_GddRoeRequestInfo[Index].ucCurrentState = 
        Dcm_GaaRoeNonVolatileData.Data.NVState;

      Dcm_GddRoeRequestInfo[Index].ucEventTypeRecord = 
        Dcm_GaaRoeNonVolatileData.Data.NVEventTypeRecord;

      Dcm_GddRoeRequestInfo[Index].RoeConfig.ucRoeEventId = 
        Dcm_GaaRoeNonVolatileData.Data.NVRoeEventId;

      Dcm_GddRoeRequestInfo[Index].ucSessionActive = 
        Dcm_GaaRoeNonVolatileData.Data.NVActiveSession;

      /* @Trace: SWS_Dcm_00898 SWS_Dcm_00889 */
      if (DCM_DEFAULT_SESSION == Dcm_GddRoeRequestInfo[Index].ucSessionActive)
      {
        /* @Trace: Dcm_SUD_API_50092 */
        Dcm_InternalUpdateServiceToRespondTo(
          Dcm_GaaRoeNonVolatileData.Data.IsOnChangeOfDID
          , Index
          , Dcm_GddRoeRequestInfo[Index].ucEventTypeRecord);
        /* Set RoeConfig */
        Dcm_RoeSearchDIDEvent(Dcm_GddRoeRequestInfo[Index].ucEventTypeRecord, &LucIndex);
        /* Set InternalBuffer */
        Dcm_DspManagedDIDInternally();
        
        Dcm_DspServiceProcessingSts.ucRoeStoreRequest = DCM_TRUE;
      }

      if (DCM_ROE_EVENT_WINDOW_CURRENT_AND_FOLLOWING_CYCLE 
            == Dcm_GaaRoeNonVolatileData.Data.NVEventWindowTime)
      {
        /* @Trace: Dcm_SUD_API_50093 */
        Dcm_RoeClearNVData();
        Dcm_StoreRoeEvent();
      }
    }
  }
}
#endif /*DCM_RESPONSE_ONEVENT_BLOCKID > 0*/

/*******************************************************************************
** Function Name        : Dcm_ReadRoeNonVolatileData                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read Roe Non Volatile Data                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
#if (DCM_RESPONSE_ONEVENT_BLOCKID > 0)
FUNC(void, DCM_CODE) Dcm_ReadRoeNonVolatileData(void)
{
  /* @Trace: Dcm_SUD_API_50095 */
  /* @Trace: SWS_Dcm_00888 SWS_Dcm_00898 SWS_Dcm_00897 */
  Std_ReturnType RetVal = NvM_ReadBlock(DCM_RESPONSE_ONEVENT_BLOCKID, 
    &Dcm_GaaRoeNonVolatileData.NVDataBuffer[DCM_ZERO]);

  if (E_OK == RetVal)
  {
    /* @Trace: SRS_Diag_04171 */
    /* @Trace: Dcm_SUD_API_50094 */
    Dcm_StartTimerExt(
      DCM_ROE_ACCESS_NVRAM_TIMER
      , ROE_READ_NVM_TIME
      , Dcm_PendingRoeReadNvmData
      , Dcm_CanncelReadRoeNvmData);
    Dcm_GblNvMReadBlock = DCM_TRUE;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_InternalUpdateServiceToRespondTo                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal process function for service to response to**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : IsOnChangeOfDID, Index, EventTypeRecord             **
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
static FUNC(void, DCM_CODE) Dcm_InternalUpdateServiceToRespondTo(
  uint8 IsOnChangeOfDID
  , uint8 Index
  , uint16 EventTypeRecord)
{
  Dcm_GddRoeRequestInfo[Index].RoeConfig.blIsOnChngOfDIDRxed = IsOnChangeOfDID;

  if (DCM_FALSE == IsOnChangeOfDID)
  {
    /* @Trace: Dcm_SUD_API_50096 */
    Dcm_GddRoeRequestInfo[Index].ddRoeReqDataLen = DCM_TWO;
    Dcm_GddRoeRequestInfo[Index].RoeReqData[DCM_ZERO] = DCM_READDTCINFORMATION;
    Dcm_GddRoeRequestInfo[Index].RoeReqData[DCM_ONE] = DCM_UDS_READ_DTC_INFO_0E;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_50097 */
    Dcm_GddRoeRequestInfo[Index].ddRoeReqDataLen = DCM_THREE;

    Dcm_GddRoeRequestInfo[Index].
      RoeReqData[DCM_ZERO] = DCM_READDATABYIDENTIFIER;

    Dcm_GddRoeRequestInfo[Index].
      RoeReqData[DCM_ONE] = DCM_U16_HI_BYTE(EventTypeRecord);

    Dcm_GddRoeRequestInfo[Index].
      RoeReqData[DCM_TWO] = DCM_U16_LO_BYTE(EventTypeRecord);
  }
}

/*******************************************************************************
** Function Name        : Dcm_InternalPreConfigRoe                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal process function for Roe Pre Config        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : index                                               **
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
/* polyspace +1 MISRA-C3:8.3 MISRA-C3:5.8 [Justified:Low] Justify with annotations */
static FUNC(void, DCM_CODE) Dcm_InternalPreConfigRoe(uint8 indexVal)
{
  /* @Trace: Dcm_SUD_API_50098 */
  if (indexVal < DCM_NUM_OF_ROE_EVENT_CONFIG)
  {
    Dcm_GddRoeRequestInfo[indexVal].EventWindowTime = DCM_ROE_EVENT_WINDOW_INFINITE;

    /* @Trace: SWS_Dcm_01323*/
    Dcm_DspServiceProcessingSts.ucRoeStoreRequest = DCM_TRUE;
    
    /* @Trace: SWS_Dcm_00921 SWS_Dcm_00915*/
    if (DCM_FALSE == Dcm_GaaDcmDspRoeCfg[indexVal].blIsOnChngOfDIDRxed)
    {
      /* @Trace: Dcm_SUD_API_50099 */
      Dcm_GddRoeRequestInfo[indexVal].ucEventTypeRecord = 
        (uint16)Dcm_GaaDcmDspRoeCfg[indexVal].ucRoeDTCStatusMask;

      Dcm_InternalUpdateServiceToRespondTo(DCM_FALSE
        , indexVal
        , Dcm_GddRoeRequestInfo[indexVal].ucEventTypeRecord);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_50100 */
      uint16 Did = *(Dcm_GaaDcmDspRoeCfg->pRoeDidRef);
      Dcm_GddRoeRequestInfo[indexVal].ucEventTypeRecord = Did;
      Dcm_InternalUpdateServiceToRespondTo(DCM_TRUE, indexVal, Did);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_IsRoeEventStart                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the roe transmission is start or not       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
static FUNC(uint8, DCM_CODE) Dcm_IsRoeEventStart(void)
{
  /* @Trace: Dcm_SUD_API_50101 */
  uint8 RetVal = DCM_FALSE;

  for (uint8 idx = DCM_ZERO; idx < DCM_NUM_OF_ROE_EVENT_CONFIG; idx++)
  {
    if (DCM_ROE_STARTED == Dcm_GddRoeRequestInfo[idx].ucCurrentState)
    {
      /* @Trace: Dcm_SUD_API_50102 */
      RetVal = DCM_TRUE;
      break;
    }
  }
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_RoeClearNVData                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Clear non volatile Data                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
static FUNC(void, DCM_CODE) Dcm_RoeClearNVData(void)
{
  /* @Trace: Dcm_SUD_API_50103 */
  Dcm_GaaRoeNonVolatileData.Data.NVEventWindowTime = DCM_ROE_EVENT_WINDOW_INFINITE;
  Dcm_GaaRoeNonVolatileData.Data.NVState = DCM_ROE_CLEARED;
  Dcm_GaaRoeNonVolatileData.Data.NVEventTypeRecord = DCM_ZERO;
  Dcm_GaaRoeNonVolatileData.Data.IsOnChangeOfDID = DCM_FALSE;
  Dcm_GaaRoeNonVolatileData.Data.NVRoeEventId = DCM_ZERO;
  Dcm_GaaRoeNonVolatileData.Data.NVIndex = DCM_ZERO;
  Dcm_GaaRoeNonVolatileData.Data.NVActiveSession = DCM_ZERO;
}

/*******************************************************************************
** Function Name        : Dcm_InitROE                                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize data for roe functional                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
FUNC(void, DCM_CODE) Dcm_InitROE(void)
{
  /* @Trace: Dcm_SUD_API_50104 */
  Dcm_GpRoeMsgContext = &Dcm_GstRoeMsgContext;
  Dcm_DspServiceProcessingSts.ucRoeStoreRequest = DCM_FALSE;
  Dcm_GucResOnEventStatus = DCM_ROE_IDLE;
  Dcm_GblRoeClearAll = DCM_FALSE;

  for (uint8 idx = DCM_ZERO; idx < DCM_NUM_OF_ROE_EVENT_CONFIG; idx++)
  {
    /* @Trace: Dcm_SUD_API_50111 */
    Dcm_GddRoeRequestInfo[idx].ucSessionActive = DCM_DEFAULT_SESSION;
    Dcm_GddRoeRequestInfo[idx].ucEventTypeRecord = (uint16)DCM_ZERO;

    /* @Trace: SWS_Dcm_00872 */
    Dcm_GddRoeRequestInfo[idx].ucCurrentState = DCM_ROE_CLEARED;

    /* @Trace: SWS_Dcm_00954 SWS_Dcm_00951*/
    /* polyspace-begin RTE:UNR [Justify:Low] "This condition check for read non-volatile data in NVM" */
    if (Dcm_GaaDcmDspRoeCfg[idx].ucRoeInitialEventStatus == DCM_ROE_STOPPED)
    {
      /* @Trace: Dcm_SUD_API_50105 */
      Dcm_GddRoeRequestInfo[idx].ucCurrentState = DCM_ROE_STOPPED;
      Dcm_InternalPreConfigRoe(idx);
    }
    /* polyspace-end RTE:UNR [Justify:Low] "This condition check for read non-volatile data in NVM" */
  }

  Dcm_RoeClearNVData();
  Dcm_ClearRoeEventTriggeredInfo();
}

/*******************************************************************************
** Function Name        : Dcm_CheckRoeEventTriggered                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : function for verify that ROE Event is triggered     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_CheckRoeEventTriggered(void)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  for (int idx = DCM_ZERO; idx < DCM_NUM_OF_ROE_EVENT_CONFIG; idx++)
  {
    if (Dcm_TriggeredROEEventInfo[idx] == DCM_ONE)
    { 
      LddRetVal = E_OK;
      break;
    }
  }
  /* @Trace: Dcm_SUD_API_50106 */
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_StoreRoeEventTriggeredInfo                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Setter function for Roe Event Triggered Info        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Index                                               **
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
FUNC(void, DCM_CODE) Dcm_StoreRoeEventTriggeredInfo(uint8 Index)
{
  if (Index < DCM_NUM_OF_ROE_EVENT_CONFIG)
    {		
      /* @Trace: Dcm_SUD_API_50107 */
      Dcm_TriggeredROEEventInfo[Index] = DCM_TRUE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_ClearRoeEventTriggeredInfo                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Clear the Roe Event Triggered Data                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
FUNC(void, DCM_CODE) Dcm_ClearRoeEventTriggeredInfo(void)
{
  /* @Trace: Dcm_SUD_API_50108 */
  Dcm_CurrentROEEventIndex = DCM_NUM_OF_ROE_EVENT_CONFIG;

  Dcm_MemClear(Dcm_TriggeredROEEventInfo, DCM_NUM_OF_ROE_EVENT_CONFIG);
  Dcm_MemClear(Dcm_PrevTriggeredROEEventInfo, DCM_NUM_OF_ROE_EVENT_CONFIG);
}

/*******************************************************************************
** Function Name        : Dcm_SetFirstActivatedEvent                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Setter function for first Roe Event index           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
FUNC(void, DCM_CODE) Dcm_SetFirstActivatedEvent(void)
{
  /* find first index of activated events for ROE function */
  Dcm_CurrentROEEventIndex = DCM_ZERO;

  while (Dcm_CurrentROEEventIndex < DCM_NUM_OF_ROE_EVENT_CONFIG)
  {
    if (Dcm_GddRoeRequestInfo[Dcm_CurrentROEEventIndex].ucCurrentState != DCM_ROE_STARTED)
    {
      Dcm_CurrentROEEventIndex++;
    }
    else {
      break;
    }
  }

  /* Move data for process ROE function */
  for (int idx = DCM_ZERO; idx < DCM_NUM_OF_ROE_EVENT_CONFIG; idx++)
  {
    Dcm_PrevTriggeredROEEventInfo[idx] = Dcm_TriggeredROEEventInfo[idx];
  }

  /* Clear Array for monitoring events triggered. */
  Dcm_MemClear(Dcm_TriggeredROEEventInfo, DCM_NUM_OF_ROE_EVENT_CONFIG);
}

/*******************************************************************************
** Function Name        : Dcm_SetNextActivatedEvent                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Setter function for next Roe Event index            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
FUNC(void, DCM_CODE) Dcm_SetNextActivatedEvent(void)
{
  Dcm_CurrentROEEventIndex++;

  /* If new index is not valid, Try to find new valid Event Index. */
  while (Dcm_CurrentROEEventIndex < DCM_NUM_OF_ROE_EVENT_CONFIG)
  {
    if (Dcm_GddRoeRequestInfo[Dcm_CurrentROEEventIndex].ucCurrentState != DCM_ROE_STARTED)
    {
      Dcm_CurrentROEEventIndex++;
    }
    else 
    {
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_GetCurrentROEEventIndex                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Getter function for current Roe Event index         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
FUNC(uint8, DCM_CODE) Dcm_GetCurrentROEEventIndex(void)
{
  return Dcm_CurrentROEEventIndex;
}

/*******************************************************************************
** Function Name        : Dcm_GetROEEventTriggerdFlag                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Setter function for Triggered Roe Event flag        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
FUNC(uint8, DCM_CODE) Dcm_GetROEEventTriggerdFlag(uint8 index)
{
  return Dcm_PrevTriggeredROEEventInfo[index];
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
