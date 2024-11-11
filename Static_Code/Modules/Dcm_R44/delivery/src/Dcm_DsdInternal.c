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
**  SRC-MODULE: Dcm_DsdInternal.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Contain internal API for DSD operation                        **
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
** 0.0.1     31-Dec-2019   HueKM          AR440 Implementation                **
** 0.0.2     16-Aug-2020   HueKM          Update code for SID2A as per #14836 **
** 0.0.3     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.4     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.5     23-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.2     18-May-2022   LanhLT         Changes made as per #26479          **
** 1.0.9     31-Mar-2023   LanhLT         Refer #CP44-1637                    **
** 1.0.12    16-May-2023   DanhTQ1        Refer #40629                        **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
** 1.3.0     31-Dcm-2023   DH Kwak        Refer #CP44-1415                    **
** 1.4.0     29-Mar-2024   EK Kim         Refer #CP44-3850                    **
*******************************************************************************/

/*******************************************************************************
**                      Include  Section                                      **
*******************************************************************************/
#include  "Dcm.h"
#include  "Dcm_Ram.h"
#if(DCM_DEM_CONFIGURED == STD_ON)
#include  "Dem.h"
#endif

#include  "Rte_Dcm.h"
#include  "ComM_Dcm.h"
#include  "SchM_Dcm.h"
#include  "Dcm_DspMain.h"
#include  "Dcm_Dsl.h"
#include  "PduR_Dcm.h"
#include "Dcm_DspServices.h"
#include "Dcm_DspMemoryServices.h"
#include  "Dcm_DsdInternal.h"
#include "Dcm_DslManageSecurity.h"
#include "Dcm_DspUploadDownload.h"
#include "Dcm_RoutineControl.h"

#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
#include "Dcm_DspResponseOnEvent.h"
#endif

#include "Dcm_Config.h"
#include "Dcm_ActiveDiag.h"
#include "Dcm_Timer.h"
#include "Dcm_Utils.h"
#include "Dcm_Lib.h"
#include "Dcm_Validate.h"
#include "Dcm_Authentication.h"
#include "Dcm_ReqRespHandling.h"

/*******************************************************************************
**                      Function  Definitions                                 **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

static FUNC(boolean, DCM_CODE) Dcm_DsdIndication_NormalRequest(
  PduIdType RxPduId
  , boolean IsPerTransmission
  , boolean IsRoeTransmission);

static FUNC(boolean, DCM_CODE) Dcm_DsdIndication_HigherPriorityRequest(
  PduIdType RxPduId);

static FUNC(boolean, DCM_CODE) Dcm_DsdPostValidation(
  uint8 ServiceId
  , uint8 SubServiceId);

static FUNC(boolean, DCM_CODE) Dcm_DsdServiceValidation(
  uint8 ServiceId);

static FUNC(boolean, DCM_CODE) Dcm_DsdSubServiceValidation(
  Dcm_ServiceIdConfigConstPtrType pSidCfg
  , uint8 SubServiceId);

static boolean Dcm_DsdValidateSubServiceId(
  Dcm_SubServiceIdConfigConstPtrType pSubSidCfg
  , uint8 SubSerNum
  , uint8 SubServiceId
  , Dcm_Uint8PtrType pSubSerIdx);

static FUNC(void, DCM_CODE) Dcm_DsdInternal_SetMsgContext(
  Dcm_MsgContextPtrType pMsgContext
  , PduIdType RxPduId
  , Dcm_Uint8PtrType pRxBuffer
  , boolean ExistSubFunction);

static FUNC(boolean, DCM_CODE) Dcm_DsdReqManuInd(
  Dcm_Uint8ConstPtrType RxBufferId
  , PduIdType RxPduId
  , Dcm_MsgLenType ResDataLen
  , Dcm_NrcPtrType pErrorCode);

static FUNC(boolean, DCM_CODE) Dcm_DsdReqSuppInd(
  Dcm_Uint8ConstPtrType RxBufferId
  , PduIdType RxPduId
  , Dcm_MsgLenType ResDataLen
  , Dcm_NrcPtrType pErrorCode);

static FUNC(boolean, DCM_CODE) Dcm_DsdReqInd(
  Dcm_Uint8ConstPtrType RxBufferId
  , PduIdType RxPduId
  , Dcm_MsgLenType ResDataLen
  , Dcm_NrcPtrType pErrorCode
  , boolean ManuFlg);

static FUNC(boolean, DCM_CODE) Dcm_DsdReqConfirm(
  uint8 SID
  , PduIdType RxPduId
  , Dcm_ConfirmationStatusType ConfirmStatus
  , boolean ManuFlg);

#if(DCM_J1979_2_SUPPORT == STD_ON)
static FUNC(boolean, DCM_CODE) Dcm_DsdIsOBDService(
  uint8 LucSID);
#endif

/*******************************************************************************
** Function Name        : Dcm_GetServiceConfigPtr                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the service configuration                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ServiceId                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_ServiceIdConfigConstPtrType                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00145 */
FUNC(Dcm_ServiceIdConfigConstPtrType, DCM_CODE) Dcm_GetServiceConfigPtr(
  uint8 ServiceId)
{
  /* @Trace: Dcm_SUD_API_70100 */
  Dcm_ServiceIdConfigConstPtrType pServiceCfg = NULL_PTR;

  Dcm_ProtocolConfigConstPtrType pProtocolCfg = NULL_PTR;
  Dcm_ServiceIdConfigConstPtrType pTempServiceCfg = NULL_PTR;
  uint8 ProtocolIdx = Dcm_GetProtocolTypeIndex(Dcm_GddProtocolType);

  if (ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG)
  {
    /* @Trace: Dcm_SUD_API_70101 */
    pProtocolCfg = &Dcm_GaaProtocolConfig[ProtocolIdx];
    pTempServiceCfg = pProtocolCfg->pServiceIdTable;
  }

  if (pTempServiceCfg != NULL_PTR)
  {
    /* @Trace: Dcm_SUD_API_70102 */
    for (uint8 idx = 0; idx < pProtocolCfg->ucServiceCount; idx++)
    {
      if ((pTempServiceCfg[idx].ucServiceId != ServiceId)
          || (DCM_FALSE == pTempServiceCfg[idx].ServiceUsed))
      {
        continue;
      }

      /* @Trace: Dcm_SUD_API_70103 */
      pServiceCfg = &pTempServiceCfg[idx];
      break;
    }
  }

  return pServiceCfg;
}

/*******************************************************************************
**  Function  Name       : Dcm_DsdInternal_SetMsgContext                      **
**                                                                            **
**  Service  ID          : NA                                                 **
**                                                                            **
**  Description          : This  function  will  give  the  indication  to    **
**                         the  DSD layer  on  the  arrival  of  the          **
**                         new  request.                                      **
**                                                                            **
**  Sync/Async           : Synchronous                                        **
**                                                                            **
**  Re-entrancy          : Non-Reentrant                                      **
**                                                                            **
**  Input  Parameters    : RxPduId, pRxBuffer, ExistSubFunction               **
**                                                                            **
**  InOut parameter      : pMsgContext                                        **
**                                                                            **
**  Output  Parameters   : None                                               **
**                                                                            **
**  Return  parameter    : void                                               **
**                                                                            **
**  Preconditions        : None                                               **
**                                                                            **
**  Remarks              : None                                               **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DsdInternal_SetMsgContext(
  Dcm_MsgContextPtrType pMsgContext
  , PduIdType RxPduId
  , Dcm_Uint8PtrType pRxBuffer
  , boolean ExistSubFunction)
{
  if ((NULL_PTR == pMsgContext)
      || (NULL_PTR == pRxBuffer)
      || (DCM_NUM_OF_PDUIDTABLECONFIG <= RxPduId))
  {
    /* @Trace: Dcm_SUD_API_70104 */
    /* Do nothing in this case */
  }
  else
  {
    /* @Trace: Dcm_SUD_API_70105 */
    Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[RxPduId];

    pMsgContext->idContext = (Dcm_IdContextType)(pRxBuffer[0U] | DCM_RESPONSE_ID);
    pMsgContext->reqData = &pRxBuffer[1U];
    pMsgContext->dcmRxPduId = RxPduId;

    /*
     * Check if the Suppress positive bit is set and
     * Sub-function is available for the requested service Id
     */
    pMsgContext->msgAddInfo.suppressPosResponse = DCM_FALSE;

    if (Dcm_GddProtocolType != 0U)
    {
      #if (DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT)
      /* @Trace: Dcm_SUD_API_70106 */
      Std_ReturnType ret = E_NOT_OK;
      ret = Dcm_ChkSuppressPosResponse(pRxBuffer, pMsgContext->reqDataLen);

      if (ret == E_OK)
      {
        /* @Trace: Dcm_SUD_API_70107 */
        pMsgContext->msgAddInfo.suppressPosResponse = DCM_TRUE;
      }
      else
      #endif
      {
        /* @Trace: SWS_Dcm_01411 SWS_Dcm_00204*/
        if (((pMsgContext->reqData[0U] & DCM_SUPRESSBIT_MASK) == DCM_SUPRESSBIT_MASK)
            && (DCM_TRUE == ExistSubFunction))
        {
          /* @Trace: Dcm_SUD_API_70108 */
          pMsgContext->msgAddInfo.suppressPosResponse = DCM_TRUE;
          pMsgContext->reqData[0U] = pMsgContext->reqData[0U] & DCM_SUBFUNCTION_MASK;
        }
      }
    }

    pMsgContext->msgAddInfo.reqType = (uint8) pPduIdTable->ucRxAddrType;
  }
}

/*******************************************************************************
**  Function  Name       : Dcm_DsdIndication                                  **
**                                                                            **
**  Service  ID          : NA                                                 **
**                                                                            **
**  Description          : This  function  will  give  the  indication  to    **
**                         the  DSD layer  on  the  arrival  of  the          **
**                         new  request.                                      **
**                                                                            **
** Sync/Async            : Synchronous                                        **
**                                                                            **
**  Re-entrancy          : Non-Reentrant                                      **
**                                                                            **
**  Input  Parameters    : RxPduId,  IsStopProtocol,                          **
**                         IsPerTransmission, IsRoeTransmission               **
**                                                                            **
** InOut parameter       : None                                               **
**                                                                            **
**  Output  Parameters   : None                                               **
**                                                                            **
**  Return  parameter    : boolean                                            **
**                                                                            **
**  Preconditions        : None                                               **
**                                                                            **
**  Remarks              : None                                               **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_DsdIndication(
  PduIdType RxPduId
  , boolean IsStopProtocol
  , boolean IsPerTransmission
  , boolean IsRoeTransmission)
{
  /* @Trace: Dcm_SUD_API_70109 */
  boolean RetVal = DCM_FALSE;

  uint8 ApiId = DCM_RX_INDICATION_SID;
  boolean ChkVal = Dcm_ChkPduId(ApiId, RxPduId);

  if (DCM_TRUE == ChkVal)
  {
    Dcm_GddNegRespError = DCM_POS_RESP;

    if (DCM_FALSE == IsStopProtocol)
    {
      /* @Trace: Dcm_SUD_API_70110 */
      RetVal = Dcm_DsdIndication_NormalRequest(
        RxPduId, IsPerTransmission, IsRoeTransmission);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_70111 */
      RetVal = Dcm_DsdIndication_HigherPriorityRequest(RxPduId);
    }
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DsdIndication_NormalRequest                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Dsd Indication in case normal request       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
**  Input  Parameters    : RxPduId, IsPerTransmission, IsRoeTransmission      **
**                                                                            **
** InOut parameter       : None                                               **
**                                                                            **
**  Output  Parameters   : None                                               **
**                                                                            **
**  Return  parameter    : boolean                                            **
**                                                                            **
**  Preconditions        : None                                               **
**                                                                            **
**  Remarks              : None                                               **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04173 */
static FUNC(boolean, DCM_CODE) Dcm_DsdIndication_NormalRequest(
  PduIdType RxPduId
  , boolean IsPerTransmission
  , boolean IsRoeTransmission)
{
  boolean RetVal = DCM_TRUE;

  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[RxPduId];
  uint8 ProtocolIdx = Dcm_GetProtocolTypeIndex(Dcm_GddProtocolType);

  uint8 RxBufferId = pPduIdTable->ucRxBufferId;
  uint8 TxBufferId = pPduIdTable->ucTxBufferId;

  Dcm_Uint8PtrType pRxBuffer = Dcm_GaaBufferConfig[RxBufferId].pBufferArea;
  Dcm_Uint8PtrType pTxBuffer = Dcm_GaaBufferConfig[TxBufferId].pBufferArea;

  Dcm_MsgLenType LddBufferSize = DCM_ZERO;
  Dcm_DiagnosticServiceFunType pDiagnosticServiceFun = NULL_PTR;

  #if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) \
     && (DCM_PROTOCOL_TRANSTYPE2  ==  STD_ON))
  uint8 IsPrtclType2;
  #endif

  if ((ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG)
      && (RxBufferId < DCM_NUM_OF_BUFFER_CONFIG)
      && (TxBufferId < DCM_NUM_OF_BUFFER_CONFIG)
      && (NULL_PTR != pRxBuffer)
      && (NULL_PTR != pTxBuffer))
  {
    Dcm_NegativeResponseCodeType ErrorCode = DCM_POS_RESP;
    Dcm_MsgLenType ResDataLen;

    uint8 ReqType = (uint8) pPduIdTable->ucRxAddrType;
    PduIdType TxPduId = pPduIdTable->ddTxPduId;
    Dcm_GddDcmTxPduId = pPduIdTable->ddTxPduId;
    Dcm_GddDcmTxConfPduId = (uint8)pPduIdTable->usTxConfirmationPduId;

    Dcm_GstMsgContext.resMaxDataLen = Dcm_GaaBufferConfig[
      TxBufferId].ulBufferSize - 1U;

    Dcm_GstMsgContext.resDataLen = (Dcm_MsgLenType) DCM_ZERO;

    #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
    if (IsPerTransmission == DCM_TRUE)
    {
      /* @Trace: Dcm_SUD_API_70203 */
      RxBufferId = pPduIdTable->ucPerRxBufferId;
      pRxBuffer = Dcm_GaaBufferConfig[RxBufferId].pBufferArea;

      TxBufferId = Dcm_GddPerStatus.ucDataInfoIdx;
      pTxBuffer = Dcm_GaaPerDataInfo[TxBufferId].pDataBuffer;
    }
    #endif

    #if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) \
         && (DCM_PROTOCOL_TRANSTYPE2  ==  STD_ON))
    IsPrtclType2 = Dcm_IsProtocolType2(RxPduId);
    if ((IsRoeTransmission == DCM_TRUE)
        && (DCM_TRUE == IsPrtclType2))
    {
      /* @Trace: Dcm_SUD_API_70204 */
      pPduIdTable = &Dcm_GaaPduIdTableConfig[RxPduId];
      Dcm_DslRoeTransConstPtrType pRoeTx = pPduIdTable->pRoeTxId;
      TxPduId = pRoeTx->ddRoeTxPduId;
      Dcm_GddDcmTxConfPduId = pRoeTx->usRoeTxConfirmPduId;

      /* @Trace: SWS_Dcm_00131 */
      RxBufferId = pRoeTx->ucRoeRxBufferId;
      TxBufferId = pRoeTx->ucRoeTxBufferId;
      pRxBuffer = Dcm_GaaBufferConfig[RxBufferId].pBufferArea;
      pTxBuffer = Dcm_GaaBufferConfig[TxBufferId].pBufferArea;

      Dcm_GpRoeMsgContext->resMaxDataLen = Dcm_GaaBufferConfig[
        TxBufferId].ulBufferSize - 1U;
    }
    #endif

    #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
    if (IsPerTransmission == DCM_TRUE)
    {
      /* @Trace: Dcm_SUD_API_70205 */
      ResDataLen = DCM_TWO;
    }
    else
    #endif
    {
      /* @Trace: Dcm_SUD_API_70206 */
      ResDataLen = Dcm_GaaReqLength[ProtocolIdx] - DCM_ONE;
    }

    /* @Trace: SRS_Diag_04199 */
    uint8 SID = pRxBuffer[DCM_ZERO];
    #if (DCM_RESPOND_ALL_REQUEST == STD_OFF)
    boolean SearchResult = (DCM_TRUE == Dcm_IsValidServiceId(SID)) ?
      Dcm_DsdReqManuInd(pRxBuffer, RxPduId, ResDataLen, &ErrorCode) : DCM_FALSE;
    #else 
    boolean SearchResult = Dcm_DsdReqManuInd(pRxBuffer, RxPduId, ResDataLen, &ErrorCode);
    #endif

    boolean ErrorOccurred = DCM_FALSE;
    if ((SearchResult == DCM_FALSE) && (ErrorCode != DCM_POS_RESP))
    {
      /* @Trace: Dcm_SUD_API_70207 */
      /* at least a Xxx_Indication() returns E_NOT_OK
       * and no function returns E_REQUEST_NOT_ACCEPTED
       * DSD shall trigger a NRC */
      ErrorOccurred = DCM_TRUE;
      pTxBuffer[2U] = (uint8)ErrorCode;
      Dcm_GddNegRespError = ErrorCode;
    }
    else if (SearchResult == DCM_FALSE)
    {
      /* @Trace: Dcm_SUD_API_70208 */
      /* at least a Xxx_Indication() returns E_REQUEST_NOT_ACCEPTED
       * DSD shall give no response */
      Dcm_GblNormalReq = DCM_FALSE;
      Dcm_DslStatusReset();
    }
    else
    {
      /* @Trace: Dcm_SUD_API_70209 */
      SearchResult = Dcm_DsdServiceValidation(SID);

      if (SearchResult == DCM_TRUE)
      {
        /* @Trace: Dcm_SUD_API_70210 */
        SearchResult = Dcm_DsdReqSuppInd(
          pRxBuffer, RxPduId, ResDataLen, &ErrorCode);

        /* @Trace: SWS_Dcm_00678 */
        /* Negative response */
        if ((SearchResult == DCM_FALSE) && (ErrorCode != DCM_POS_RESP))
        {
          /* @Trace: Dcm_SUD_API_70211 */
          ErrorOccurred = DCM_TRUE;
          pTxBuffer[2U] = (uint8)ErrorCode;
          Dcm_GddNegRespError = ErrorCode;
        }
        /* @Trace: SWS_Dcm_00677*/
        /* No response */
        else if (SearchResult == DCM_FALSE)
        {
          /* @Trace: Dcm_SUD_API_70212 */
          Dcm_GblNormalReq = DCM_FALSE;
          Dcm_DslStatusReset();
        }
        else
        {
          /* @Trace: Dcm_SUD_API_70232 */
          /* Possitive response */
          uint8 SubFunction = pRxBuffer[1U] & DCM_SUBFUNCTION_MASK;

          Dcm_ServiceIdConfigConstPtrType LpSIDTAB = Dcm_GetServiceConfigPtr(SID);
          SearchResult = Dcm_DsdPostValidation(SID, SubFunction);

          if ((SearchResult == DCM_TRUE) && (NULL_PTR != LpSIDTAB))
           {
            #if ((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) && \
                 (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON))
            if ((DCM_TRUE == IsRoeTransmission) && (DCM_TRUE == IsPrtclType2))
            {
              /* @Trace: Dcm_SUD_API_70213 */
              pTxBuffer[DCM_ZERO] = DCM_ZERO; // clear NRC-SID byte

              if (DCM_UDS_READ_DTC_INFO_0E == SubFunction)
              {
                /* @Trace: Dcm_SUD_API_70214 */
                Dcm_RequestContextPtrType requestContext;
                requestContext = Dcm_GetRequestContextPtr(Dcm_GddRxPduId);

                if (NULL_PTR != requestContext)
                {
                  /* @Trace: Dcm_SUD_API_70215 */
                  requestContext->rct_ServiceCfg = LpSIDTAB;
                  requestContext->rct_SubFunctionId = SubFunction;
                  requestContext->rct_RequestResult = E_OK;
                  requestContext->rct_MsgContext = Dcm_GpRoeMsgContext;
                }
              }

              Dcm_GpRoeMsgContext->idContext = (SID | DCM_RESPONSE_ID);
              Dcm_GpRoeMsgContext->reqData = &pRxBuffer[1U];
              Dcm_GpRoeMsgContext->reqDataLen  =  Dcm_GddRoeReqLength - DCM_ONE;
              Dcm_GpRoeMsgContext->resData = &pTxBuffer[1U];
              Dcm_GpRoeMsgContext->dcmRxPduId = RxPduId;
              Dcm_GpRoeMsgContext->msgAddInfo.reqType = ReqType;

              pDiagnosticServiceFun = LpSIDTAB->pDiagnosticService;
              if (NULL_PTR != pDiagnosticServiceFun)
              {
                /* @Trace: Dcm_SUD_API_70216 */
                (void) pDiagnosticServiceFun(
                  DCM_INITIAL, Dcm_GpRoeMsgContext, NULL_PTR);
              }
            }
            else
            #endif
            {
              #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
              if (DCM_TRUE == IsPerTransmission)
              {
                /* @Trace: Dcm_SUD_API_70217 */
                /* Clear NRC or SID byte */
                pTxBuffer[DCM_ZERO] = DCM_ZERO;

                Dcm_GstPerMsgContext.reqDataLen = DCM_TWO;
                Dcm_GstPerMsgContext.idContext = SID | DCM_RESPONSE_ID;

                Dcm_GstPerMsgContext.dcmRxPduId = RxPduId;
                Dcm_GstPerMsgContext.msgAddInfo.reqType = ReqType;

                Dcm_GstPerMsgContext.reqData = &pRxBuffer[DCM_ONE];
                Dcm_GstPerMsgContext.resData = &pTxBuffer[DCM_ZERO];

                LddBufferSize = Dcm_GaaPerDataInfo[TxBufferId].ulMaxDataLen;
                Dcm_GstPerMsgContext.resMaxDataLen = LddBufferSize - DCM_ONE;

                pDiagnosticServiceFun = LpSIDTAB->pDiagnosticService;

                if (NULL_PTR != pDiagnosticServiceFun)
                {
                  /* @Trace: SWS_Dcm_00716 */
                  /* @Trace: Dcm_SUD_API_70218 */
                  (void) pDiagnosticServiceFun(
                    DCM_INITIAL, &Dcm_GstPerMsgContext, NULL_PTR);
                }
              }
              else
              #endif
              {
                /* @Trace: Dcm_SUD_API_70219 */
                Dcm_GstMsgContext.reqDataLen = ResDataLen;
                Dcm_GstMsgContext.resData = &pTxBuffer[1U];
                pTxBuffer[0U] = 0U; // clear NRC-SID byte

                Dcm_DsdInternal_SetMsgContext(
                  &Dcm_GstMsgContext, RxPduId, 
                  pRxBuffer, LpSIDTAB->blSubFunctionAvailable);

                Dcm_RequestContextPtrType pRequestContext = Dcm_GetRequestContextPtr(
                  Dcm_GddRxPduId);

                if (NULL_PTR != pRequestContext)
                {
                  /* @Trace: Dcm_SUD_API_70220 */
                  pRequestContext->rct_ServiceCfg = LpSIDTAB;
                  pRequestContext->rct_SubFunctionId = SubFunction;
                  pRequestContext->rct_RequestResult = E_OK;
                  pRequestContext->rct_MsgContext = &Dcm_GstMsgContext;
                }

                LddBufferSize = Dcm_GaaBufferConfig[TxBufferId].ulBufferSize;
                if (SID != DCM_TRANSFERDATA)
                {
                  /* @Trace: Dcm_SUD_API_70221 */
                  Dcm_MsgLenType maxDataSize = LddBufferSize - DCM_ONE;
                  Dcm_MemClear(Dcm_GstMsgContext.resData, maxDataSize);
                }

                Dcm_GddNegRespError = DCM_POS_RESP;

                /* @Trace: SWS_Dcm_00221 */
                pDiagnosticServiceFun = LpSIDTAB->pDiagnosticService;

                if (NULL_PTR != pDiagnosticServiceFun)
                {
                  /* @Trace: Dcm_SUD_API_70222 */
                  /* @Trace: SWS_Dcm_00527 SWS_Dcm_00732 */
                  /* @Trace: SRS_Diag_04007 SRS_Diag_04169 */
                  if (DCM_E_PENDING == pDiagnosticServiceFun(
                    DCM_INITIAL, &Dcm_GstMsgContext, NULL_PTR))
                  {
                    if (NULL_PTR != pRequestContext)
                    {
                      /* @Trace: Dcm_SUD_API_70223 */
                      pRequestContext->rct_RequestResult = DCM_E_PENDING;
                    }
                  }

                  #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
                  Dcm_TriggerAddPendingRequestToQueue();
                  #endif
                }
              }
            }
          }
          else
          {
            /* @Trace: Dcm_SUD_API_70224 */
            ErrorOccurred = DCM_TRUE;
            pTxBuffer[2U] = (uint8)Dcm_GddNegRespError;
          }
        }
      }
      else
      {
        /* @Trace: Dcm_SUD_API_70225 */
        ErrorOccurred = DCM_TRUE;
        pTxBuffer[2U] = (uint8)Dcm_GddNegRespError;
      }
    }

    if ((DCM_FALSE == ErrorOccurred)
        && ((SID == DCM_OBD_REQ_CURRENTPOWERTRAINDIAGDATA)
            || (SID == DCM_OBD_REQ_ONBOAD_MONITOR_RESULT)
            || (SID == DCM_OBD_REQ_CTLR_ONBOAD_SYSTEM)
            || (SID == DCM_OBD_REQ_VEHICLEINFO)))
    {
      /* Check if any NRC is updated, if updated then invoke Dcm_ExternalSetNegResponse
       * before calling Dcm_ExternalProcessingDone  API */
      if (Dcm_GddNegRespError != DCM_POS_RESP)
      {
        /* @Trace: Dcm_SUD_API_70226 */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }

      /* Invoke the Dcm_ExternalProcessingDone only if it is not of paged transmission type */
      #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if (Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
      #endif
      {
        /* @Trace: Dcm_SUD_API_70227 */
        Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
      }
    }

    /*
     * Initialize  the  global  bit  flag  indicating  that  all  the
     * verifications  were  successful
     */
    Dcm_TxRespStatus.ucFailedInd = DCM_FALSE;
    if (ErrorOccurred == DCM_TRUE)
    {
      RetVal = DCM_FALSE;

      /* @Trace: SWS_Dcm_00001 */
      /*
       * In the case of a Negative Result of the execution and active
       * Functional Addressing the DSD submodule shall activate the suppression of the
       * following Negative Responses:
       * NRC 0x11 (Service not supported),
       * NRC 0x12 (SubFunction not supported),
       * NRC 0x31 (Request out of range),
       * NRC 0x7E (Subfunction not supported in active session),
       * NRC 0x7F (Service not supported in active session) ( BSW04020)
       */
      /* polyspace +4 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
      /* polyspace +3 MISRA-C:12.1 [Justified:Low] Justify with annotations */
      uint8 NrcVal = pTxBuffer[2U];
      if (((DCM_TRUE == Dcm_IsSpecialNrc(NrcVal))
          && (Dcm_ProtocolRxAddrType)ReqType == DCM_FUNCTIONAL_TYPE))
      {
        /* @Trace: Dcm_SUD_API_70228 */
        Dcm_GblNormalReq = DCM_FALSE;
        Dcm_DslStatusReset();
      }
      else
      {
        /* @Trace: Dcm_SUD_API_70229 */
        Dcm_GstMsgContext.resData = pTxBuffer;
        pTxBuffer[0U] = DCM_NEGATIVE_RESPONSE_SID;
        pTxBuffer[1U] = SID;
        Dcm_GstMsgContext.resDataLen = 3U;

        Dcm_DslTransmit(TxPduId, DCM_FALSE, DCM_FALSE);

        /* Check if the current processing is for normal request */
        if (Dcm_GblNormalReq == DCM_TRUE)
        {
          /* @Trace: Dcm_SUD_API_70230 */
          /* The global bit flag is made true, so that no confirmation
           * to the upper layer is given */
          Dcm_TxRespStatus.ucFailedInd = DCM_TRUE;
        }
      }
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_70202 */
    Dcm_GblNormalReq = DCM_FALSE;
    Dcm_DslStatusReset();
  }

  #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_OFF)
  DCM_UNUSED(IsPerTransmission);
  #endif

  #if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_OFF) || \
       (DCM_PROTOCOL_TRANSTYPE2 == STD_OFF))
  DCM_UNUSED(IsRoeTransmission);
  #endif

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DsdIndication_HigherPriorityRequest             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process Dsd Indication in case                      **
**                        higher priority request                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RxPduId                                             **
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
static FUNC(boolean, DCM_CODE) Dcm_DsdIndication_HigherPriorityRequest(
  PduIdType RxPduId)
{
  /* @Trace: Dcm_SUD_API_70112 */
  (void)Dcm_DsdCancelTransmission(RxPduId);

  /* @Trace: SWS_Dcm_01046 */
  Dcm_DsdCancelOperation();

  Dcm_DsdResetPendingFlag();

  #if ((DCM_CLEAR_ITC_SERVICE_SUPPRT == STD_ON) \
       || (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON))
  Dcm_InternalTroubleCodeService = DCM_FALSE;
  #endif

  #if (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_DspReturnControlToEcu();
  #endif

  #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
  Dcm_StopTimer(DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIMER);
  #endif

  Dcm_TriggerEventActivationDiagnostic(AD_TE_PROTOCOL_PREEMPTION);

  return DCM_TRUE;
}

/*******************************************************************************
** Function Name        : Dcm_DsdCancelTransmission                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Cancel the transmission                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RxPduId                                             **
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
FUNC(boolean, DCM_CODE) Dcm_DsdCancelTransmission(PduIdType RxPduId)
{
  /* @Trace: Dcm_SUD_API_70113 */
  boolean RetVal = DCM_TRUE;

  if ((Dcm_TxRespStatus.ucNegResp == DCM_TRUE)
      || (Dcm_TxRespStatus.ucNormResponse == DCM_TRUE)
      #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
      || ((Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE)
          && (Dcm_TxRespStatus.ucDslPagedTrans == DCM_TRUE))
      #endif
     )
  {
    /* @Trace: SWS_Dcm_00079 */
    /* @Trace: Dcm_SUD_API_70114 */
    Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[RxPduId];
    RetVal = PduR_DcmCancelTransmit(pPduIdTable->ddTxPduId);
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DsdResetPendingFlag                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Reset pending flag                                  **
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
FUNC(void, DCM_CODE) Dcm_DsdResetPendingFlag(void)
{
  #if(DCM_DEM_CONFIGURED == STD_ON)
  /* @Trace: Dcm_SUD_API_70115 */
  Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucOBDClearDTCStatus = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucReportOBDDtc = DCM_FALSE;
  Dcm_GblDTCFDCPending = DCM_FALSE;
  Dcm_GblFaultDetectionCounter = DCM_FALSE;
  #endif
}

/*******************************************************************************
**  Function Name         : Dcm_DsdReqManuInd                                 **
**                                                                            **
**  Service ID            : NA                                                **
**                                                                            **
**  Description           : This  function  used to check the Manufacturer    **
**                          permission/environment. This function will call   **
**                          Manufacturer Application  to check permission     **
**                          /environment.                                     **
**                                                                            **
**  Sync/Async            : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input Parameters      : RxBufferId, RxPduId, ResDataLen                   **
**                                                                            **
**  InOut parameter       : None                                              **
**                                                                            **
**  Output Parameters     : pErrorCode                                        **
**                                                                            **
**  Return parameter      : boolean                                           **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : None                                              **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00218 */
static FUNC(boolean, DCM_CODE) Dcm_DsdReqManuInd(
  Dcm_Uint8ConstPtrType RxBufferId
  , PduIdType RxPduId
  , Dcm_MsgLenType ResDataLen
  , Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_70116 */
  boolean TransmitReqToDsp = Dcm_DsdReqInd(
    RxBufferId, RxPduId, ResDataLen, pErrorCode, DCM_TRUE);

  return TransmitReqToDsp;
}

/*******************************************************************************
**  Function Name         : Dcm_DsdReqSuppInd                                 **
**                                                                            **
**  Service ID            : NA                                                **
**                                                                            **
**  Description           : This  function  used to check the Supplier        **
**                          permission/environment. This function will call   **
**                          Supplier Application  to check permission         **
**                          /environment.                                     **
**                                                                            **
**  Sync/Async            : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input Parameters      : RxBufferId, RxPduId, ResDataLen                   **
**                                                                            **
**  InOut parameter       : None                                              **
**                                                                            **
**  Output Parameters     : pErrorCode                                        **
**                                                                            **
**  Return parameter      : boolean                                           **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : None                                              **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00516 */
static FUNC(boolean, DCM_CODE) Dcm_DsdReqSuppInd(
  Dcm_Uint8ConstPtrType RxBufferId
  , PduIdType RxPduId
  , Dcm_MsgLenType ResDataLen
  , Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_70117 */
  boolean TransmitReqToDsp = Dcm_DsdReqInd(
    RxBufferId, RxPduId, ResDataLen, pErrorCode, DCM_FALSE);

  return TransmitReqToDsp;
}

/*******************************************************************************
** Function Name          : Dcm_DsdReqInd                                     **
**                                                                            **
** Service ID             : NA                                                **
**                                                                            **
**  Description           : This  function  used to check                     **
**                          the permission/environment. This function will    **
**                          call Application  to check permission/environment **
**                                                                            **
**  Sync/Async            : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input Parameters      : RxBufferId, RxPduId, ResDataLen, ManuFlg          **
**                                                                            **
**  InOut parameter       : None                                              **
**                                                                            **
**  Output Parameters     : pErrorCode                                        **
**                                                                            **
**  Return parameter      : boolean                                           **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : None                                              **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_DsdReqInd(
  Dcm_Uint8ConstPtrType RxBufferId
  , PduIdType RxPduId
  , Dcm_MsgLenType ResDataLen
  , Dcm_NrcPtrType pErrorCode
  , boolean ManuFlg)
{
  boolean TransmitReqToDsp = DCM_TRUE;

  uint8 NotAcceptedCnt = 0U;
  uint8 NotOkCnt = 0U;
  uint8 MaxLen;
  
  Dcm_PduIdTablePtrType pPduIdTable;
  pPduIdTable = &Dcm_GaaPduIdTableConfig[RxPduId];

  Dcm_ProtocolType ProtocolType;
  uint16 ConnectionId;
  uint16 SourceTesterAddress;

  Dcm_GetProtocolInfo(RxPduId, &ProtocolType, 
    &ConnectionId, &SourceTesterAddress);

  uint8 SID = RxBufferId[0U];

  Dcm_IndicationFunType pIndicationFun = NULL_PTR;
  Std_ReturnType RetVal = E_OK;
  Dcm_NegativeResponseCodeType TempErrorCode = DCM_POS_RESP;
  Dcm_NegativeResponseCodeType FinalErrorCode = DCM_POS_RESP;

  /*
   * Invoke the API xxx_Indication to do the request
   * message environment verification
   */
  if (DCM_TRUE == ManuFlg)
  {
    MaxLen = (uint8)DCM_NUMBER_OF_REQUEST_MANUFACTURER_INDICATION;

	/* @Trace: Dcm_SUD_API_70118 */
    for (uint8 idx = 0U; idx < MaxLen; idx++)
    {
      /* @Trace: Dcm_SUD_API_70119 Dcm_SUD_API_70120 */
      /* 
      * [SWS_Dcm_00516] If container DcmDsdServiceRequestSupplierNotification exists, 
      * the DSD submodule shall call the operation Xxx_Indication on all configured 
      * ServiceRequestIndication ports (see configuration parameter DcmDsdServiceRequestSupplierNotification). 
      */
	  pIndicationFun = DCM_GET_MANU_INDICATION_FUN(idx);
      if (pIndicationFun != NULL_PTR)
      {
        /* @Trace: Dcm_SUD_API_70121 */
        RetVal = pIndicationFun(SID
          , &RxBufferId[1U]
          , (uint16)ResDataLen
          , (uint8) pPduIdTable->ucRxAddrType
          , ConnectionId
          , &TempErrorCode
          , ProtocolType
          , SourceTesterAddress);

        /* @Trace: SWS_Dcm_00462 SWS_Dcm_01172 SWS_Dcm_00463 */
        /* @Trace: SWS_Dcm_01321 SWS_Dcm_00517 SWS_Dcm_00518 SWS_Dcm_01322 */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_01341. Dcm must be implement to cover all return values of Xxx_Indication." */
        NotOkCnt += (RetVal == E_NOT_OK) ? 1U : 0U;
        NotAcceptedCnt += (RetVal == E_REQUEST_NOT_ACCEPTED) ? 1U : 0U;
        if(RetVal == E_NOT_OK)
        {
          FinalErrorCode = (NotOkCnt == 1U) ? TempErrorCode: FinalErrorCode;
        }
      }
    }
  }
  else
  {
    MaxLen = (uint8)DCM_NUMBER_OF_REQUEST_SUPPLIER_INDICATION;

    for (uint8 idx = 0U; idx < MaxLen; idx++)
    {
      pIndicationFun = DCM_GET_SUPP_INDICATION_FUN(idx);
      if (pIndicationFun != NULL_PTR)
      {
        RetVal = pIndicationFun(SID
          , &RxBufferId[1U]
          , (uint16)ResDataLen
          , (uint8) pPduIdTable->ucRxAddrType
          , ConnectionId
          , &TempErrorCode
          , ProtocolType
          , SourceTesterAddress);

        NotOkCnt += (RetVal == E_NOT_OK) ? 1U : 0U;
        NotAcceptedCnt += (RetVal == E_REQUEST_NOT_ACCEPTED) ? 1U : 0U;
        if(RetVal == E_NOT_OK)
        {
          FinalErrorCode = (NotOkCnt == 1U) ? TempErrorCode: FinalErrorCode;
        }
      }
    }
  }

  if(NotAcceptedCnt > 0U)
  {
    /* @Trace: Dcm_SUD_API_70467 */
    /* 
     * [SWS_Dcm_00517] If at least a single Xxx_Indication function called according
     * to [SWS_Dcm_00516] returns E_REQUEST_NOT_ACCEPTED, the DSD submodule shall give no response. 
     */
    *pErrorCode = DCM_POS_RESP;
    TransmitReqToDsp = DCM_FALSE;
  }
  else 
  {
    /* 
     * [SWS_Dcm_00518] If at least a single Xxx_Indication function called according to [SWS_Dcm_00516] 
     * has returned E_NOT_OK and no function has returned E_REQUEST_NOT_ACCEPTED, 
     * the DSD submodule shall trigger a negative response with NRC from the ErrorCode parameter. 
     */

    /* 
     * [SWS_Dcm_01322] If more than one Xxx_Indication function called, according to [SWS_Dcm_00516], 
     * has returned E_NOT_OK and no function has returned E_REQUEST_NOT_ACCEPTED, the DSD submodule shall trigger
     * a negative response using the ErrorCode parameter from the first Xxx_Indication returning E_NOT_OK. 
     */
    if (NotOkCnt > 0U) /* NotAcceptedCnt is zero */
    {
      /* @Trace: Dcm_SUD_API_70122 */
      *pErrorCode = FinalErrorCode;
      TransmitReqToDsp = DCM_FALSE;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_70468 */
      /* Positive response*/
      TransmitReqToDsp = DCM_TRUE;
    }
  }

  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_01341. Dcm must be implement to cover all return values of Xxx_Indication." */
  return TransmitReqToDsp;
}

/*******************************************************************************
** Function Name        : Dcm_DsdReqManuConfirm                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Request manufacturer confirmation                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : SID, RxPduId, ConfirmStatus                         **
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
FUNC(boolean, DCM_CODE) Dcm_DsdReqManuConfirm(
  uint8 SID
  , PduIdType RxPduId
  , Dcm_ConfirmationStatusType ConfirmStatus)
{
  /* @Trace: Dcm_SUD_API_70123 */
  Std_ReturnType RetVal = Dcm_DsdReqConfirm(
    SID, RxPduId, ConfirmStatus, DCM_TRUE);

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DsdReqSuppConfirm                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Request supplier confirmation                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : SID, RxPduId, ConfirmStatus                         **
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
FUNC(boolean, DCM_CODE) Dcm_DsdReqSuppConfirm(
  uint8 SID
  , PduIdType RxPduId
  , Dcm_ConfirmationStatusType ConfirmStatus)
{
  /* @Trace: Dcm_SUD_API_70124 */
  Std_ReturnType RetVal = Dcm_DsdReqConfirm(
    SID, RxPduId, ConfirmStatus, DCM_FALSE);

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DsdReqConfirm                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Request confirmation from Manafacturer or Supplier  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : SID, RxPduId, ConfirmStatus, ManuFlg                **
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
static FUNC(boolean, DCM_CODE) Dcm_DsdReqConfirm(
  uint8 SID
  , PduIdType RxPduId
  , Dcm_ConfirmationStatusType ConfirmStatus
  , boolean ManuFlg)
{
  Std_ReturnType RetVal = E_OK;

  Dcm_PduIdTablePtrType pPduIdTable;
  pPduIdTable = &Dcm_GaaPduIdTableConfig[RxPduId];

  Dcm_ProtocolType ProtocolType;
  uint16 ConnectionId;
  uint16 SourceTesterAddress;
  uint8 MaxLen;

  Dcm_GetProtocolInfo(RxPduId, 
    &ProtocolType, &ConnectionId, &SourceTesterAddress);

  Dcm_ConfirmationFunType pConfirmationFun = NULL_PTR;

  if (ManuFlg == DCM_TRUE)
  {
    MaxLen = (uint8)DCM_NUMBER_OF_REQUEST_MANUFACTURER_INDICATION;

    for (uint8 idx = 0U; idx < MaxLen; idx++)
	  {
      /* @Trace: Dcm_SUD_API_70126 Dcm_SUD_API_70127 */
      pConfirmationFun = DCM_GET_MANU_CONFIRMATION_FUN(idx);
      
      if (pConfirmationFun != NULL_PTR)
      {
        /* @Trace: Dcm_SUD_API_70128 */
        RetVal = pConfirmationFun(SID
          , (uint8) pPduIdTable->ucRxAddrType
          , ConnectionId
          , ConfirmStatus
          , ProtocolType
          , SourceTesterAddress);
      }
    }
  }
  else
  {
    MaxLen = (uint8)DCM_NUMBER_OF_REQUEST_SUPPLIER_INDICATION;

    for (uint8 idx = 0U; idx < MaxLen; idx++)
	  {
      /* @Trace: Dcm_SUD_API_70126 Dcm_SUD_API_70127 */
      pConfirmationFun = DCM_GET_SUPP_CONFIRMATION_FUN(idx);

      if (pConfirmationFun != NULL_PTR)
      {
        /* @Trace: Dcm_SUD_API_70128 */
        RetVal = pConfirmationFun(SID
          , (uint8) pPduIdTable->ucRxAddrType
          , ConnectionId
          , ConfirmStatus
          , ProtocolType
          , SourceTesterAddress);
      }
    }
  }

  return RetVal;
}

/*******************************************************************************
**  Function  Name        :  Dcm_DsdPostValidation                            **
**                                                                            **
**  Service  ID           :  NA                                               **
**                                                                            **
**  Description           :  This function will validate the service and      **
**                           subfunction requested.                           **
**                                                                            **
**  Sync/Async            :  Synchronous                                      **
**                                                                            **
**  Re-entrancy           :  Non-Reentrant                                    **
**                                                                            **
**  Input  Parameters     :  ServiceId, SubServiceId                          **
**                                                                            **
**  InOut parameter       :  None                                             **
**                                                                            **
**  Output  Parameters    :  None                                             **
**                                                                            **
**  Return  parameter     :  boolean                                          **
**                                                                            **
**  Preconditions         :  None                                             **
**                                                                            **
**  Remarks               :  None                                             **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04228 */
static FUNC(boolean, DCM_CODE) Dcm_DsdPostValidation(
  uint8 ServiceId
  , uint8 SubServiceId)
{
  boolean RetVal = DCM_TRUE;

  uint8 ProtocolIdx = Dcm_GetProtocolTypeIndex(Dcm_GddProtocolType);
  Dcm_ServiceIdConfigConstPtrType pServiceCfg = Dcm_GetServiceConfigPtr(ServiceId);

  if ((ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG)
      && (NULL_PTR != pServiceCfg))
  {
    #if (DCM_MODE_RULE == STD_ON)
    /* @Trace: Dcm_SUD_API_70129 */
    /* @Trace: SWS_Dcm_00773 SWS_Dcm_00774 */
    Dcm_GddNegRespError = Dcm_CheckModeRule(
      pServiceCfg->blModeRuleConfigured, pServiceCfg->ucseviceModeruleindexarray);

    RetVal = (Dcm_GddNegRespError == DCM_POS_RESP) ? DCM_TRUE : DCM_FALSE;

    if (DCM_TRUE == RetVal)
    #endif
    {
      /* @Trace: SWS_Dcm_00696 */
      if (Dcm_GaaReqLength[ProtocolIdx] < pServiceCfg->ucMinReqLength)
      {
        /* @Trace: Dcm_SUD_API_70130 */
        RetVal = DCM_FALSE;
        Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }
      else
      {
        if ((NULL_PTR != pServiceCfg->pSubServiceId) && (DCM_ROUTINECONTROL != ServiceId))
        {
          /* @Trace: SWS_Dcm_00273 */
          /* @Trace: Dcm_SUD_API_70131 */
          RetVal = Dcm_DsdSubServiceValidation(pServiceCfg, SubServiceId);

          if (DCM_TRUE == RetVal)
          {
            /* @Trace: SWS_Dcm_01354 */
            /* @Trace: Dcm_SUD_API_70132 */
            RetVal = Dcm_IsSecurityAttemptCounterRestored(
              ServiceId, SubServiceId, &Dcm_GddNegRespError);
          }
        }
      }
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_70133 */
    RetVal = DCM_FALSE;
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }

  return RetVal;
}

/*******************************************************************************
**  Function  Name        :  Dcm_DsdServiceValidation                         **
**                                                                            **
**  Service  ID           :  NA                                               **
**                                                                            **
**  Description           :  This function will validate service requested    **
**                                                                            **
**  Sync/Async            :  Synchronous                                      **
**                                                                            **
**  Re-entrancy           :  Non-Reentrant                                    **
**                                                                            **
**  Input  Parameters     :  ServiceId                                        **
**                                                                            **
**  InOut parameter       :  None                                             **
**                                                                            **
**  Output  Parameters    :  None                                             **
**                                                                            **
**  Return  parameter     :  boolean                                          **
**                                                                            **
**  Preconditions         :  None                                             **
**                                                                            **
**  Remarks               :  None                                             **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01535 SWS_Dcm_00197 SRS_Diag_04177 SRS_Diag_04203 */
static FUNC(boolean, DCM_CODE) Dcm_DsdServiceValidation(uint8 ServiceId)
{
  /* @Trace: Dcm_SUD_API_70134 */
  boolean RetVal = DCM_FALSE;

  Dcm_ServiceIdConfigConstPtrType pSidCfg = Dcm_GetServiceConfigPtr(ServiceId);
  uint8 ProtocolIdx = Dcm_GetProtocolTypeIndex(Dcm_GddProtocolType);

  if ((NULL_PTR == pSidCfg)
      || (DCM_SERVICE_NOT_CONFIGURED == ProtocolIdx))
  {
    /* @Trace: Dcm_SUD_API_70135 */
    Dcm_GddNegRespError = DCM_E_SERVICENOTSUPPORTED;
  }
  #if(DCM_J1979_2_SUPPORT == STD_ON)
  else if (((Dcm_GddProtocolType == DCM_OBD_ON_UDS) || (Dcm_GddProtocolType == DCM_ZEV_ON_UDS)) && 
          (Dcm_DsdIsOBDService(ServiceId) == DCM_TRUE))
  {
    Dcm_GddNegRespError = DCM_E_SERVICENOTSUPPORTED;
  }
  #endif
  else
  {
    /* Do Nothing */
  }

  if (DCM_POS_RESP == Dcm_GddNegRespError)
  {
    /* @Trace: SRS_Diag_04237 */
    /* @Trace: SWS_Dcm_01539 */
    /* @Trace: Dcm_SUD_API_70136 */
    #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
    RetVal = Dcm_ValidateServiceAccessRights(pSidCfg);
    /* @Trace: SWS_Dcm_01544 */
    CHK_RET_VAL(DCM_FALSE == RetVal, Dcm_GddNegRespError, DCM_E_AUTHENTICATIONREQUIRED);
    #else
    RetVal = DCM_TRUE;
    #endif /* DCM_AUTHENTICATION_SERVICE == STD_ON */

    if ((DCM_TRUE == RetVal)
        && (NULL_PTR != pSidCfg->pSession))
    {
      /* @Trace: Dcm_SUD_API_70137 */
      RetVal = Dcm_DsdValidateSession(pSidCfg->pSession, pSidCfg->ucSessionCount);
      CHK_RET_VAL(DCM_FALSE == RetVal, Dcm_GddNegRespError, DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION);
    }

    if ((DCM_TRUE == RetVal)
        && (NULL_PTR != pSidCfg->pSecurity))
    {
      /* @Trace: SWS_Dcm_00617 */
      /* @Trace: Dcm_SUD_API_70138 */
      RetVal = Dcm_DsdValidateSecurity(pSidCfg->pSecurity, pSidCfg->ucSecurityCount);
      CHK_RET_VAL(DCM_FALSE == RetVal, Dcm_GddNegRespError, DCM_E_SECURITYACCESSDENIED);
    }
  }

  return RetVal;
}

/*******************************************************************************
**  Function  Name        :  Dcm_DsdSubServiceValidation                      **
**                                                                            **
**  Service  ID           :  NA                                               **
**                                                                            **
**  Description           :  This function validates subfunction requested    **
**                                                                            **
**  Sync/Async            :  Synchronous                                      **
**                                                                            **
**  Re-entrancy           :  Non-Reentrant                                    **
**                                                                            **
**  Input  Parameters     :  pSidCfg,  SubServiceId                           **
**                                                                            **
**  InOut parameter       :  None                                             **
**                                                                            **
**  Output  Parameters    :  None                                             **
**                                                                            **
**  Return  parameter     :  boolean                                          **
**                                                                            **
**  Preconditions         :  None                                             **
**                                                                            **
**  Remarks               :  None                                             **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04177 SRS_Diag_04203 */
static FUNC(boolean, DCM_CODE) Dcm_DsdSubServiceValidation(
  Dcm_ServiceIdConfigConstPtrType pSidCfg
  , uint8 SubServiceId)
{
  /* @Trace: Dcm_SUD_API_70139 */
  boolean RetVal = DCM_FALSE;

  #if (DCM_DEV_ERROR_DETECT == STD_ON)
  CHK_RET_VAL(NULL_PTR == pSidCfg, Dcm_GddNegRespError, DCM_E_GENERALREJECT);
  if (NULL_PTR != pSidCfg)
  #endif
  {
    /* @Trace: Dcm_SUD_API_70140 */
    Dcm_SubServiceIdConfigConstPtrType pSubSidCfg;
    uint8 SubSidIdx = DCM_SERVICE_NOT_CONFIGURED;

    pSubSidCfg = pSidCfg->pSubServiceId;
    if (NULL_PTR != pSubSidCfg)
    {
      /* @Trace: Dcm_SUD_API_70141 */
      RetVal = Dcm_DsdValidateSubServiceId(
        pSubSidCfg, pSidCfg->ucSubServiceCount, SubServiceId, &SubSidIdx);
      CHK_RET_VAL(DCM_FALSE == RetVal, Dcm_GddNegRespError, DCM_E_SUBFUNCTIONNOTSUPPORTED);
    }

    if (DCM_TRUE == RetVal)
    {
      /* @Trace: Dcm_SUD_API_70142 */
      pSubSidCfg = &pSubSidCfg[SubSidIdx];

      /* @Trace: SRS_Diag_04237 */
      #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
      RetVal = Dcm_ValidateSubServiceAccessRights(pSidCfg, pSubSidCfg);
      #endif

      /* @Trace: SWS_Dcm_01544 */
      CHK_RET_VAL(DCM_FALSE == RetVal, Dcm_GddNegRespError, DCM_E_AUTHENTICATIONREQUIRED);
    }

    if ((DCM_TRUE == RetVal)
        && (NULL_PTR != pSubSidCfg->pSubSerSession))
    {
      /* @Trace: SWS_Dcm_00616 */
      /* @Trace: Dcm_SUD_API_70143 */
      RetVal = Dcm_DsdValidateSession(pSubSidCfg->pSubSerSession, pSubSidCfg->ucSubSerSessionCount);
      CHK_RET_VAL(DCM_FALSE == RetVal, Dcm_GddNegRespError, DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION);
    }

    if ((DCM_TRUE == RetVal)
        && (NULL_PTR != pSubSidCfg->pSubSerSecurity))
    {
      /* @Trace: Dcm_SUD_API_70144 */
      RetVal = Dcm_DsdValidateSecurity(pSubSidCfg->pSubSerSecurity, pSubSidCfg->ucSubSerSecurityCount);
      CHK_RET_VAL(DCM_FALSE == RetVal, Dcm_GddNegRespError, DCM_E_SECURITYACCESSDENIED);
    }

    #if (DCM_MODE_RULE == STD_ON)
    if (DCM_TRUE == RetVal)
    {
      /* @Trace: Dcm_SUD_API_70145 */
      Dcm_GddNegRespError = Dcm_CheckModeRule(
        pSubSidCfg->blModeRuleConfigured, pSubSidCfg->ucsubmoderuleArrayindex);
      RetVal = (DCM_POS_RESP == Dcm_GddNegRespError) ? DCM_TRUE : DCM_FALSE;
    }
    #endif
  }

  return RetVal;
}

/*******************************************************************************
**  Function  Name      : Dcm_DsdConfirmation                                 **
**                                                                            **
**  Service  ID         : NA                                                  **
**                                                                            **
**  Description         : This  function  will  give  the  confirmation  to   **
**                        upper  layer.  It  is  invoked  by  the  API        **
**                        Dcm_TpTxConfirmation.                               **
**                                                                            **
**  Sync/Async          : Synchronous                                         **
**                                                                            **
**  Re-entrancy         : Non-Reentrant                                       **
**                                                                            **
**  Input  Parameters   : LddResult                                           **
**                                                                            **
**  InOut parameter     : None                                                **
**                                                                            **
**  Output  Parameters  : None                                                **
**                                                                            **
**  Return  parameter   : void                                                **
**                                                                            **
**  Preconditions       : None                                                **
**                                                                            **
**  Remarks             : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04172 */
FUNC(void, DCM_CODE) Dcm_DsdConfirmation(Std_ReturnType Result)
{
  Dcm_ConfirmationStatusType ConfirmStatus;
  boolean LblNrcOccured;
  boolean LblResetInRccrp = DCM_TRUE;

  uint8 TxBufferId = DCM_ZERO;
  uint8 ApiId = DCM_TP_TX_CONFIRMATION_SID;
  PduIdType RxPduId  = Dcm_GstMsgContext.dcmRxPduId;

  /* @Trace: Dcm_SUD_API_70187 */
  boolean ChkVal = Dcm_ChkPduId(ApiId, RxPduId);

  if (DCM_TRUE == ChkVal)
  {
    TxBufferId = (uint8)Dcm_GaaPduIdTableConfig[RxPduId].ucTxBufferId;

    if (DCM_NUM_OF_BUFFER_CONFIG <= TxBufferId)
    {
      /* @Trace: Dcm_SUD_API_70188 */
      ChkVal = DCM_FALSE;
      DCM_REPORT_ERROR(ApiId, DCM_E_PARAM);
    }
  }

  if (DCM_TRUE == ChkVal)
  {
    Dcm_BufferConfigConstPtrType pBufferCfg = &Dcm_GaaBufferConfig[TxBufferId];
    Dcm_Uint8PtrType pTxBuffer = pBufferCfg->pBufferArea;

    #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
    /*  Check if the paged transmission is currently in progress */
    if (Dcm_TxRespStatus.ucPagedTrans == DCM_FALSE)
    #endif
    {
      Dcm_IdContextType SID = Dcm_GstMsgContext.idContext & DCM_SID_MASK;

      /*  Check if Dcm_ExternalSetNegResponse was called before calling
      *  Dcm_ExternalProcessingDone
      */
      if ((DCM_TRUE == Dcm_TxRespStatus.ucNeedFailedConfiramtion) &&
          (E_OK == Result))
      {
        /* @Trace: Dcm_SUD_API_70189 */
        LblResetInRccrp = DCM_FALSE;
      }

      if (DCM_TRUE == Dcm_TxRespStatus.ucNeedFailedConfiramtion)
      {
        /* @Trace: Dcm_SUD_API_70190 */
        LblNrcOccured = DCM_TRUE;
        Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
      }
      else
      {
        if (pTxBuffer[0U] == DCM_NEGATIVE_RESPONSE_SID)
        {
          /* @Trace: Dcm_SUD_API_70191 */
          /* Clear the negative response Id */
          pTxBuffer[0U] = 0U;
          LblNrcOccured = DCM_TRUE;
        }
        else
        {
          /* @Trace: Dcm_SUD_API_70231 */
          LblNrcOccured  =  DCM_FALSE;
        }
      }

      if (DCM_TRUE == LblNrcOccured)
      {
        /* @Trace: Dcm_SUD_API_70192 Dcm_SUD_API_70193 */
        ConfirmStatus = (E_OK == Result) ? DCM_RES_NEG_OK : DCM_RES_NEG_NOT_OK;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_70194 Dcm_SUD_API_70195 */
        ConfirmStatus = (E_OK == Result) ? DCM_RES_POS_OK : DCM_RES_POS_NOT_OK;
      }

      /* The global bit flag is made true, so that no confirmation
       * to the upper layer is given
       *
       * Dcm_TxRespStatus.ucFailedInd is true in case of Dcm_GblNormalReq is true and
       * 1. Xxx_Indication has returned E_NOT_OK or
       * 2. NRC is generated by DSD
       *
       * [SWS_Dcm_01000]
       * In case a NRC is generated by DSD, the API
       * DspInternal_DcmConfirmation is not called, but only XXX_Confirmation
       *
       * [SWS_Dcm_00218]
       * If configured (configuration parameter
       * DcmDsdRequestManufacturerNotificationEnabled=TRUE), the DSD submodule
       * shall call the operation Xxx_Indication() on all configured
       * ServiceRequestIndication ports (see configuration parameter
       * DcmDsdServiceRequestManufacturerNotification).
       *
       * [SWS_Dcm_00462]
       * If at least a single Xxx_Indication() function called
       * according to SWS_Dcm_00218 returns E_REQUEST_NOT_ACCEPTED, the DSD
       * submodule shall give no response.
       *
       * [SWS_Dcm_01172]
       * In case of [SWS_Dcm_00462, the DSD shall only call
       * Xxx_Confirmation but not DspInternal_DcmConfirmation.
       */
      /* @Trace: SWS_Dcm_00240*/
      if (Dcm_TxRespStatus.ucFailedInd == DCM_FALSE)
      {
        /* @Trace: Dcm_SUD_API_70196 */
        DspInternal_DcmConfirmation(
          Dcm_GstMsgContext.idContext, RxPduId, ConfirmStatus);
      }

      /* @Trace: Dcm_SUD_API_70197 */
      /* @Trace: SWS_Dcm_00742, SWS_Dcm_00741 */
      /* The call of Xxx_Confirmation() shall be done right after the
       * call of DspInternal_DcmConfirmation() */
      (void) Dcm_DsdReqManuConfirm(SID, RxPduId, ConfirmStatus);

      (void) Dcm_DsdReqSuppConfirm(SID, RxPduId, ConfirmStatus);
    }
    #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
    else
    {
      /*  Check  if  the  previous  page  was  transmitted  successfully  */
      if (Result == E_OK)
      {
        /* @Trace: Dcm_SUD_API_70198 */
        /*  Get  the  buffer  size  where  the  next  page  is  to be updated */
        uint32 BufferSize  =  pBufferCfg->ulBufferSize;

        /*
         *  Invoke  the  update  function  of  DSP/RTE  based  on  where
         *  the requested service  is  implemented
        */
        Dcm_DspUpdatePage(pTxBuffer, BufferSize);
      }
      else
      {
        /* @Trace: Dcm_SUD_API_70199 */
        /* Invoke  the  cancel  paged  buffer  function  of  DSP/RTE  based  on
         * where the  requested  service  is  implemented */
        Dcm_DspCancelPagedBufferProcessing();

        /*  Update  the  bit  for  the  paged  transmission  to  FALSE  */
        Dcm_TxRespStatus.ucPagedTrans = DCM_FALSE;
      }
    }
    #endif

    /* Check if the pre compile option DCM_RESPONSE_ON_EVENT_SERVICE is enabled */
    #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
    if (DCM_ROEONGOING == Dcm_GucResOnEventStatus)
    {
      /* @Trace: Dcm_SUD_API_70200 */
      Dcm_GucResOnEventStatus = DCM_ROE_IDLE;
    }
    #endif /* (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) */
    /*
     * Check if the current request under process is of normal request or periodic
     * request and if the confirmation was not called during paged transmission
     */
    if ((Dcm_GblNormalReq == DCM_TRUE)
        #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
        && (Dcm_GddPerStatus.blOnResTrans == DCM_FALSE)
        #endif
        && (Dcm_TxRespStatus.ucPagedTrans == DCM_FALSE)
        && (LblResetInRccrp == DCM_TRUE))
    {
      /* @Trace: Dcm_SUD_API_70201 */
      Dcm_GblNormalReq = DCM_FALSE;
      Dcm_GusMaxNoOfRespPend = DCM_ZERO;

      Dcm_DslStatusReset();
    }
  }

  /* Clears flag */
  Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
}

/*******************************************************************************
**  Function  Name       : Dcm_GetProtocolTypeIndex                           **
**                                                                            **
**  Service  ID          : NA                                                 **
**                                                                            **
**  Description          : This  function  will  give  the  protocol  index   **
**                                                                            **
**  Sync/Async           : Synchronous                                        **
**                                                                            **
**  Re-entrancy          : Non-Reentrant                                      **
**                                                                            **
**  Input  Parameters    : ProtocolId                                         **
**                                                                            **
**  InOut parameter      : None                                               **
**                                                                            **
**  Output  Parameters   : ProtocolIdx                                        **
**                                                                            **
**  Return  parameter    : void                                               **
**                                                                            **
**  Preconditions        : None                                               **
**                                                                            **
**  Remarks              : Global  Variable(s)  :                             **
**                         Dcm_GaaProtocolIds, Dcm_GaaProtocolConfig          **
**                                                                            **
*******************************************************************************/
FUNC(uint8, DCM_CODE) Dcm_GetProtocolTypeIndex(uint8 ProtocolId)
{
  /* @Trace: Dcm_SUD_API_70146 */
  uint8 ProtocolIdx = DCM_SERVICE_NOT_CONFIGURED;

  for (uint8 idx = 0U; idx < DCM_NUM_OF_PROTOCOLCONFIG; idx++)
  {
    if ((ProtocolId == Dcm_GaaProtocolIds[idx])
        && (DCM_TRUE == Dcm_GaaProtocolConfig[idx].ProtocolUsed))
    {
      /* @Trace: Dcm_SUD_API_70147 */
      ProtocolIdx = idx;
      break;
    }
  }

  return ProtocolIdx;
}

/*******************************************************************************
**  Function  Name        : Dcm_DsdValidateSecurity                           **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This  function  is  used  to  validate  security  **
**                                                                            **
**  Sync/Async            : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : pSecLvlCfg, SecLvlNum                             **
**                                                                            **
**  InOut parameter       : None                                              **
**                                                                            **
**  Output  Parameters    : None                                              **
**                                                                            **
**  Return  parameter     : boolean                                           **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : Global  Variable(s)  : None                       **
**                          Function(s)  invoked  :  Dcm_GetSecurityLevel,    **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04227 */
/* @Trace: SWS_Dcm_00217 */
FUNC(boolean, DCM_CODE) Dcm_DsdValidateSecurity(
  Dcm_Uint8ConstPtrType pSecLvlCfg
  , uint8 SecLvlNum)
{
  /* @Trace: Dcm_SUD_API_70148 */
  boolean ChkVal = DCM_FALSE;
  CHK_RET_VAL((pSecLvlCfg == NULL_PTR) || (SecLvlNum == 0), ChkVal, DCM_TRUE);

  if (DCM_FALSE == ChkVal)
  {
    Dcm_SecLevelType SecLvl = 0U;
    (void) Dcm_GetSecurityLevel(&SecLvl);

    for (uint8 SecLvlIdx = 0U; SecLvlIdx < SecLvlNum; SecLvlIdx++)
    {
      if (pSecLvlCfg[SecLvlIdx] == SecLvl)
      {
        /* @Trace: Dcm_SUD_API_70149 */
        ChkVal = DCM_TRUE;
        break;
      }
    }
  }

  return ChkVal;
}

/*******************************************************************************
**  Function  Name        : Dcm_DsdValidateSession                            **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This  function  is  to  validate  session         **
**                                                                            **
**  Sync/Async            : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : pSesCtrlCfg, SesCtrlNum                           **
**                                                                            **
**  InOut parameter       : None                                              **
**                                                                            **
**  Output  Parameters    : None                                              **
**                                                                            **
**  Return  parameter     : boolean                                           **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : Global  Variable(s)  :  None                      **
**                          Function(s)  invoked :  Dcm_GetSesCtrlType,       **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04226 */
/* @Trace: SWS_Dcm_00211 */
FUNC(boolean, DCM_CODE) Dcm_DsdValidateSession(
  Dcm_Uint8ConstPtrType pSesCtrlCfg
  , uint8 SesCtrlNum)
{
  /* @Trace: Dcm_SUD_API_70150 */
  /* polyspace +2 MISRA-C:12.1 [Justified:Low] Justify with annotations */
  boolean ChkVal = DCM_FALSE;
  CHK_RET_VAL(pSesCtrlCfg == NULL_PTR || SesCtrlNum == 0, ChkVal, DCM_TRUE);

  if (DCM_FALSE == ChkVal)
  {
    Dcm_SesCtrlType SesCtrl = 0U;
    (void) Dcm_GetSesCtrlType(&SesCtrl);

    for (uint8 SesCtrlIdx = 0U; SesCtrlIdx < SesCtrlNum; SesCtrlIdx++)
    {
      if (SesCtrl == pSesCtrlCfg[SesCtrlIdx])
      {
        /* @Trace: Dcm_SUD_API_70151 */
        ChkVal = DCM_TRUE;
        break;
      }
    }
  }

  return ChkVal;
}

/*******************************************************************************
**  Function  Name        : Dcm_DsdValidateSubServiceId                       **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This  function  to  validate  the subservice id   **
**                          for session, security and mode rule               **
**                                                                            **
**  Sync/Async            : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : pSubSidCfg,  SubSerNum,  SubServiceId             **
**                                                                            **
** InOut parameter        : None                                              **
**                                                                            **
**  Output  Parameters    : pSubSerIdx                                        **
**                                                                            **
**  Return  parameter     : boolean                                           **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : Global  Variable(s)  : None                       **
**                          Function(s)  invoked :  None                      **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_DsdValidateSubServiceId(
  Dcm_SubServiceIdConfigConstPtrType pSubSidCfg
  , uint8 SubSerNum
  , uint8 SubServiceId
  , Dcm_Uint8PtrType pSubSerIdx)
{
  /* @Trace: Dcm_SUD_API_70152 */
  boolean RetVal = DCM_FALSE;

  if (pSubSidCfg != NULL_PTR)
  {
    Dcm_SubServiceIdConfigConstPtrType pTempSubSidCfg;
    for (uint8 SubSerIdx = 0U; SubSerIdx < SubSerNum; SubSerIdx++)
    {
      pTempSubSidCfg = &pSubSidCfg[SubSerIdx];
      if ((SubServiceId == pTempSubSidCfg->ucSubServiceId)
          && (DCM_TRUE == pTempSubSidCfg->SubServiceUsed))
      {
        /* @Trace: Dcm_SUD_API_70153 */
        *pSubSerIdx = SubSerIdx;
        RetVal = DCM_TRUE;
        break;
      }
    }
  }

  return RetVal;
}

/*******************************************************************************
** Function Name       : Dcm_DsdCancelOperation                               **
**                                                                            **
** Service ID          : NA                                                   **
**                                                                            **
** Description         : This function is used to stop the current active     **
**                       service when max number of pending responses         **
**                       exceeds configured limit                             **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy         : Non-Reentrant                                        **
**                                                                            **
** Input Parameters    : None                                                 **
**                                                                            **
** InOut parameter     : None                                                 **
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** Return parameter    : void                                                 **
**                                                                            **
** Preconditions       : Dcm_Init should be called before calling this API.   **
**                                                                            **
** Remarks             : None                                                 **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DsdCancelOperation(void)
{
  /* @Trace: Dcm_SUD_API_70154 */
  Dcm_RequestContextPtrType pReqCtx = Dcm_GetRequestContextPtr(Dcm_GddRxPduId);

  if ((NULL_PTR != pReqCtx)
      && (DCM_E_PENDING == pReqCtx->rct_RequestResult))
  {
    /* @Trace: SWS_Dcm_00735 */
    /* @Trace: Dcm_SUD_API_70155 */
    Dcm_DiagnosticServiceDispatch(DCM_CANCEL, pReqCtx);
  }

  Dcm_GddOpStatus = DCM_CANCEL;

  /* TODO : Shall be redesigned , running service is only one
  switch (sid)
  case read : cancel if (in total != true) break;
  case write : cancel if (in total != true) break; */
  #if (DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
  if (Dcm_MemServicePendingStatus.ucReadMemPendingStatus == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_70156 */
    (void)Dcm_DcmReadMemoryCall(&Dcm_GstMsgContext);
  }
  #endif

  #if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
  /* @Trace: SWS_Dcm_00925 */
  if (Dcm_GucResOnEventStatus == DCM_ROEONGOING)
  {
    /* @Trace: Dcm_SUD_API_70157 */
    Dcm_GucResOnEventStatus = DCM_ROE_IDLE;
  }
  #endif

  #if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
  if (Dcm_MemServicePendingStatus.ucWriteMemPendingStatus == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_70158 */
    (void)Dcm_DcmWriteMemoryCall(&Dcm_GstMsgContext);
  }
  #endif

  /* Cancel upload download services */
  Dcm_CancelUploadDownloadServices();

  #if(DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_WriteDid_CancelOperation(&Dcm_GstMsgContext);
  #endif

  #if(DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
  if(Dcm_ServicePendingStatus.ucReadDataPendingStatus == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_70159 */
    Dcm_DspInternal_DcmReadDataByIdentifier(DCM_CANCEL, &Dcm_GstMsgContext);
    Dcm_ServicePendingStatus.ucReadDataPendingStatus = DCM_FALSE;
  }
  #endif

  #if (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_DspIOCtrl_CancelOperation(&Dcm_GstMsgContext);
  #endif

  #if (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_ReadScalingInfo_CancelOperation(&Dcm_GstMsgContext);
  #endif

  #if (DCM_ROUTINECONTROL_SERVICE == STD_ON)
  Dcm_RidCtrl_CancelOperation();
  #endif

  #if (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
  Dcm_SesCtrl_CancelOperation();
  #endif

  #if (DCM_ECURESET_SERVICE == STD_ON)
  Dcm_EcuReset_CancelOperation();
  #endif

  #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
  Dcm_SecurityAccess_CancelOperation(&Dcm_GstMsgContext);
  #endif

  #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  Dcm_Pdid_CancelOperation(&Dcm_GstMsgContext);
  #endif

  #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
  Dcm_SetPendingAsyncCsif(NULL_PTR);
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_DsdInternal_GetMsgTxBuffer                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the address of tx buffer for  **
**                        Tx PDU.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : aPduId, aBufferKind                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_MsgType                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
********************************************************************************/
FUNC(Dcm_MsgType, DCM_CODE) Dcm_DsdInternal_GetMsgTxBuffer(
  PduIdType aPduId,
  Dcm_BufferKindType aBufferKind)
{
  /* Local pointer for the Tx buffer */
  Dcm_MsgType txMsgPtr = NULL_PTR;

  #if(DCM_DEV_ERROR_DETECT == STD_ON)
  if (aPduId >=  DCM_NUM_OF_PDUIDTABLECONFIG)
  {
    /* @Trace: Dcm_SUD_API_70177 */
    DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM);
  }
  else
  #endif
  {
    /* @Trace: Dcm_SUD_API_70178 */
    /* Initialize Tx buffer Id configured for RxPduID */
    uint8 txBufferIndex =0;
    boolean checkedBuffer = DCM_FALSE;

    #if ((DCM_RESPONSE_ON_EVENT_SERVICE  ==  STD_ON) && \
     (DCM_PROTOCOL_TRANSTYPE2  ==  STD_ON))
    uint8 IsPrtclType2;
    IsPrtclType2 = Dcm_IsProtocolType2(aPduId);
    #endif

    switch(aBufferKind)
    {
      case DCM_BUFFER_KIND_TX:
        /* @Trace: Dcm_SUD_API_70179 */
        txBufferIndex = Dcm_GaaPduIdTableConfig[aPduId].ucTxBufferId;
        checkedBuffer = DCM_TRUE;
        break;

      case DCM_BUFFER_KIND_RX:
        /* @Trace: Dcm_SUD_API_70180 */
        /* Do nothing in this case */
        break;

      #if ((DCM_RESPONSE_ON_EVENT_SERVICE  ==  STD_ON) && \
       (DCM_PROTOCOL_TRANSTYPE2  ==  STD_ON))
      case DCM_BUFFER_KIND_TX_ROE:
        if (DCM_TRUE == IsPrtclType2)
        {
          #if(DCM_DEV_ERROR_DETECT == STD_ON)
          if (NULL_PTR == Dcm_GaaPduIdTableConfig[aPduId].pRoeTxId)
          {
            /* @Trace: Dcm_SUD_API_70181 */
            DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM_POINTER);
          }
          else
          #endif
          {
            /* @Trace: Dcm_SUD_API_70182 */
            checkedBuffer = DCM_TRUE;

            txBufferIndex = Dcm_GaaPduIdTableConfig[
              aPduId].pRoeTxId->ucRoeTxBufferId;
          }
        }
        break;
      #endif
      case DCM_BUFFER_KIND_TX_PERIODIC:
        /* @Trace: Dcm_SUD_API_70183 */
        #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
        SchM_Enter_Dcm_ProtclProtection();
        txMsgPtr = Dcm_GaaPerDataInfo[Dcm_GddPerStatus.ucDataInfoIdx].pDataBuffer;
        SchM_Exit_Dcm_ProtclProtection();
        #endif
        break;

      default:
      /* @Trace: Dcm_SUD_API_70184 */
      /* Do nothing in this case */
      break;
    }

    if (DCM_TRUE == checkedBuffer)
    {
      #if (DCM_DEV_ERROR_DETECT == STD_ON)
      if (txBufferIndex >= DCM_NUM_OF_BUFFER_CONFIG)
      {
        /* @Trace: Dcm_SUD_API_70185 */
        DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM);
      }
      else
      #endif
      {
        /* @Trace: Dcm_SUD_API_70186 */
        /* Initialize pointer to the Tx buffer area */
        txMsgPtr = Dcm_GaaBufferConfig[txBufferIndex].pBufferArea;
      }
    }
  }

  return txMsgPtr;
}

/*******************************************************************************
** Function Name        : Dcm_DsdInternal_GetBufferSize                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the buffer size based on PduId and Buffer Kind  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PduId, BufferKind                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(uint32, DCM_CODE) Dcm_DsdInternal_GetBufferSize(
  PduIdType PduId,
  Dcm_BufferKindType BufferKind)
{
  /* @Trace: Dcm_SUD_API_70173 */
  uint8 LucBufferIndex = DCM_ZERO;
  boolean LblCheckedBuffer = DCM_FALSE;

  uint32 LulBufferSize = DCM_ZERO;

  if (PduId < DCM_NUM_OF_PDUIDTABLECONFIG)
  {
    if (DCM_BUFFER_KIND_TX == BufferKind)
    {
      /* @Trace: Dcm_SUD_API_70174 */
      LblCheckedBuffer = DCM_TRUE;
      LucBufferIndex = Dcm_GaaPduIdTableConfig[PduId].ucTxBufferId;
    }

    if (DCM_BUFFER_KIND_RX == BufferKind)
    {
      /* @Trace: Dcm_SUD_API_70175 */
      LblCheckedBuffer = DCM_TRUE;
      LucBufferIndex = Dcm_GaaPduIdTableConfig[PduId].ucRxBufferId;
    }
  }

  if (DCM_TRUE == LblCheckedBuffer)
  {
    if (LucBufferIndex < DCM_NUM_OF_BUFFER_CONFIG)
    {
      /* @Trace: Dcm_SUD_API_70176 */
      LulBufferSize = Dcm_GaaBufferConfig[LucBufferIndex].ulBufferSize;
    }
  }

  return LulBufferSize;
}

/*******************************************************************************
** Function Name        : Dcm_GetRequestContextPtr                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the request context based of RxPduId            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RxPduId                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_RequestContextPtrType                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Dcm_RequestContextPtrType, DCM_CODE) Dcm_GetRequestContextPtr(
  PduIdType RxPduId)
{
  /* @Trace: Dcm_SUD_API_70170 */
  Dcm_RequestContextPtrType pRequestContext = NULL_PTR;

  if (RxPduId < DCM_NUM_OF_PDUIDTABLECONFIG)
  {
    /* @Trace: Dcm_SUD_API_70171 */
    uint8 ProtocolIdx = Dcm_GetProtocolTypeIndex(
      Dcm_GaaPduIdTableConfig[RxPduId].ProtocolType);

    if (ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG)
    {
      /* @Trace: Dcm_SUD_API_70172 */
      pRequestContext = &Dcm_RequestContext[ProtocolIdx];
    }
  }

  return pRequestContext;
}

/*******************************************************************************
** Function Name        : Dcm_InitRequestContext                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize the request context                      **
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
FUNC(void, DCM_CODE) Dcm_InitRequestContext(void)
{
  uint8 reqCtxIdx;

  for (reqCtxIdx = 0U; reqCtxIdx < DCM_NUM_OF_PROTOCOLCONFIG; reqCtxIdx++)
  {
    /* @Trace: Dcm_SUD_API_70169 */
    Dcm_RequestContext[reqCtxIdx].rct_MsgContext = NULL_PTR;
    Dcm_RequestContext[reqCtxIdx].rct_ServiceCfg = NULL_PTR;
    Dcm_RequestContext[reqCtxIdx].rct_SubFunctionId = (uint8)0xFF;
    Dcm_RequestContext[reqCtxIdx].rct_RxPduId = (uint8)0xFF;
    Dcm_RequestContext[reqCtxIdx].rct_RequestResult = E_NOT_OK;
  }
}

/*******************************************************************************
**  Function  Name        : Dcm_GetSubServiceConfigPtr                        **
**                                                                            **
**  Service  ID           : NA                                                **
**                                                                            **
**  Description           : This function provides the subfunction            **
**                          information of request in progressing             **
**                                                                            **
**  Sync/Async            : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input  Parameters     : pMsgContext                                       **
**                                                                            **
**  InOut parameter       : None                                              **
**                                                                            **
**  Output  Parameters    : None                                              **
**                                                                            **
**  Return  parameter     : Dcm_SubServiceIdConfigConstPtrType                **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : None                                              **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(Dcm_SubServiceIdConfigConstPtrType, DCM_CODE) Dcm_GetSubServiceConfigPtr(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_70165 */
  Dcm_SubServiceIdConfigConstPtrType pSubSerivceCfg = NULL_PTR;

  Dcm_RequestContextPtrType pRequestContext;
  pRequestContext = (NULL_PTR == pMsgContext) ? NULL_PTR
    : Dcm_GetRequestContextPtr(pMsgContext->dcmRxPduId);

  Dcm_ServiceIdConfigConstPtrType pServiceCfg = NULL_PTR;

  if ((NULL_PTR != pRequestContext)
      && (NULL_PTR != pRequestContext->rct_ServiceCfg))
  {
    /* @Trace: Dcm_SUD_API_70166 */
    pServiceCfg = pRequestContext->rct_ServiceCfg;
  }

  if ((NULL_PTR != pServiceCfg)
      && (NULL_PTR != pServiceCfg->pSubServiceId)
      && (DCM_TRUE == pServiceCfg->blSubFunctionAvailable))
  {
    /* @Trace: Dcm_SUD_API_70167 */
    Dcm_SubServiceIdConfigConstPtrType pTempSubSerCfg;

    for (uint8 SubSerIdx = 0U; SubSerIdx < pServiceCfg->ucSubServiceCount; SubSerIdx++)
    {
      pTempSubSerCfg = &pServiceCfg->pSubServiceId[SubSerIdx];

      if ((NULL_PTR != pTempSubSerCfg)
          && (pRequestContext->rct_SubFunctionId == pTempSubSerCfg->ucSubServiceId)
          && (DCM_TRUE == pTempSubSerCfg->SubServiceUsed))
      {
        /* @Trace: Dcm_SUD_API_70168 */
        pSubSerivceCfg = pTempSubSerCfg;
        break;
      }
    }
  }

  return pSubSerivceCfg;
}

/*******************************************************************************
**  Function Name         : Dcm_GetProtocolConfigPtr                          **
**                                                                            **
**  Service ID            : NA                                                **
**                                                                            **
**  Description           : This  function provides the protocol              **
**                          information of request in progressing             **
**                                                                            **
**  Sync/Async            : Synchronous                                       **
**                                                                            **
**  Re-entrancy           : Non-Reentrant                                     **
**                                                                            **
**  Input Parameters      : RxPduId                                           **
**                                                                            **
**  InOut parameter       : None                                              **
**                                                                            **
**  Output Parameters     : None                                              **
**                                                                            **
**  Return parameter      : Dcm_ProtocolConfigConstPtrType                    **
**                                                                            **
**  Preconditions         : None                                              **
**                                                                            **
**  Remarks               : None                                              **
**                                                                            **
*******************************************************************************/
FUNC(Dcm_ProtocolConfigConstPtrType, DCM_CODE) Dcm_GetProtocolConfigPtr(
  PduIdType RxPduId)
{
  /* @Trace: Dcm_SUD_API_70162 */
  Dcm_ProtocolConfigConstPtrType pProtocolCfg = NULL_PTR;

  if (RxPduId < DCM_NUM_OF_PDUIDTABLECONFIG)
  {
    /* @Trace: Dcm_SUD_API_70163 */
    uint8 ProtocolIdx = Dcm_GetProtocolTypeIndex(
      Dcm_GaaPduIdTableConfig[RxPduId].ProtocolType);

    if (ProtocolIdx < DCM_NUM_OF_PROTOCOLCONFIG)
    {
      /* @Trace: Dcm_SUD_API_70164 */
      pProtocolCfg = &Dcm_GaaProtocolConfig[ProtocolIdx];
    }
  }

  return pProtocolCfg;
}

/*******************************************************************************
** Function Name        : Dcm_GetBufferConfigPtr                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get buffer configuration based on RxPduId           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RxPduId                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_BufferConfigConstPtrType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Dcm_BufferConfigConstPtrType, DCM_CODE) Dcm_GetBufferConfigPtr(
  PduIdType RxPduId)
{
  /* @Trace: Dcm_SUD_API_70160 */
  Dcm_BufferConfigConstPtrType pBufferCfg = NULL_PTR;

  if ((RxPduId < DCM_NUM_OF_PDUIDTABLECONFIG)
      && (Dcm_GaaPduIdTableConfig[RxPduId].ucRxBufferId < DCM_NUM_OF_BUFFER_CONFIG))
  {
    /* @Trace: Dcm_SUD_API_70161 */
    pBufferCfg = &Dcm_GaaBufferConfig[Dcm_GaaPduIdTableConfig[RxPduId].ucRxBufferId];
  }

  return pBufferCfg;
}

/*******************************************************************************
** Function Name        : Dcm_DsdIsOBDService                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if OBD Servie or not                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucSID                                              **
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
#if(DCM_J1979_2_SUPPORT == STD_ON)
static FUNC(boolean, DCM_CODE) Dcm_DsdIsOBDService(
  uint8 LucSID)
{
  /* @Trace: Dcm_SUD_API_11265 */
  boolean ChkVal = DCM_FALSE;


  if ((LucSID > 0) && (LucSID < 0x0B))
  {
    /* @Trace: Dcm_SUD_API_11264 */
    ChkVal = DCM_TRUE;
  }

  return ChkVal;
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
