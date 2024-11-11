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
**  SRC-MODULE: Dcm_Dsd.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Implementation for Dsd sub-module                             **
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
** 0.0.4     02-Nov-2020   HueKM          Changes made as per #16832          **
** 0.0.5     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.6     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.7     16-Dec-2022   LanhLT         Fix UNECE                           **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Rte_Dcm.h"
#if(DCM_DEM_CONFIGURED == STD_ON)
#include "Dem.h"
#endif

#include "SchM_Dcm.h"
#include "PduR_Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_Dsl.h"
#include "Dcm_DspMain.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Config.h"
#include "Dcm_Utils.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_DiagnosticServiceDispatch                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dispatch function to call service processing        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pRequestContext                           **
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
FUNC(void, DCM_CODE) Dcm_DiagnosticServiceDispatch(
  Dcm_OpStatusType OpStatus,
  Dcm_RequestContextPtrType pRequestContext)
{
  Std_ReturnType result;
  Dcm_NegativeResponseCodeType errorCode;
  Dcm_ServiceIdConfigConstPtrType pSidCfg;

  if ((NULL_PTR != pRequestContext)
      && (NULL_PTR != pRequestContext->rct_MsgContext)
      && (NULL_PTR != pRequestContext->rct_ServiceCfg))
  {
    pSidCfg = pRequestContext->rct_ServiceCfg;

    if (NULL_PTR != pSidCfg->pDiagnosticService)
    {
      result = pSidCfg->pDiagnosticService(
        OpStatus, pRequestContext->rct_MsgContext, &errorCode);

      /* @Trace: Dcm_SUD_API_00606 Dcm_SUD_API_00607 */
      pRequestContext->rct_RequestResult = (DCM_CANCEL == OpStatus) ? E_OK : result;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_00604 */
      DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_00602 */
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);
  }
}

/*******************************************************************************
** Function Name        : Dcm_InternalSetNegResponse                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal function to set negative response code     **
**                        to transmission buffer                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, ErrorCode                              **
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
FUNC(void, DCM_CODE) Dcm_InternalSetNegResponse(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType ErrorCode)
{
  /* @Trace: Dcm_SUD_API_00663 */
  Dcm_ExternalSetNegResponse(pMsgContext, ErrorCode);
}

/*******************************************************************************
** Function Name        : Dcm_InternalProcessingDone                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal process function to finish the diagnostic  **
**                        service processing                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, IsSync                                 **
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
FUNC(void, DCM_CODE) Dcm_InternalProcessingDone(
  Dcm_MsgContextPtrType pMsgContext,
  boolean IsSync)
{
  if (DCM_SYNC_DONE == IsSync)
  {
    /* @Trace: Dcm_SUD_API_00662 */
    /* Send response immediately */
    Dcm_ExternalProcessingDone(pMsgContext);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_00661 */
    /* Send response at next main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_ExternalSetNegResponse                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs the setting of the negative  **
**                        response in the corresponding buffer whenever it    **
**                        is called.                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, ErrorCode                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* MISRA Rule         : 16.7
   Message            : A pointer parameter in a function prototype should be
                        declared as pointer to const if the pointer is not
                        used to modify the addressed object.
   Reason             : This is the prototype specified in the specification.
   Verification       : However, part of the code is verified
                        manually and it is not having any impact.
*/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(void, DCM_CODE) Dcm_ExternalSetNegResponse(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType ErrorCode)
{
  #if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == pMsgContext)
  {
    /* @Trace: Dcm_SUD_API_00656 */
    DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* @Trace: Dcm_SUD_API_00657 */
    /* If this API is called during paged transmission then set the global
     * variable indicating paged transmission ongoing to FALSE */
    Dcm_TxRespStatus.ucPagedTrans = DCM_FALSE;

    /* Initialize pointer to the Tx buffer area */
    Dcm_MsgType TxMsgPtr = Dcm_DsdInternal_GetMsgTxBuffer(
      pMsgContext->dcmRxPduId, DCM_BUFFER_KIND_TX);

    #if (DCM_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == TxMsgPtr)
    {
      /* @Trace: Dcm_SUD_API_00658 */
      DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM_POINTER);
    }
    else
    #endif
    {
      /* @Trace: Dcm_SUD_API_00660 */
      TxMsgPtr[0U] = DCM_NEGATIVE_RESPONSE_SID;

      /* Since NRC has occurred Response Id is changed back to Service Id
       * Update second byte of Tx buffer with Service Id */
      TxMsgPtr[1U] =  pMsgContext->idContext & DCM_SID_MASK;

      TxMsgPtr[2U] = (uint8)ErrorCode;
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_ExternalProcessingDone                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API will transmit the response based on data   **
**                        pointed by pMsgContext.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExternalProcessingDone(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_00617 */
  #if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) \
       && (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
  P2CONST(Dcm_DslRoeTrans, AUTOMATIC, DCM_APPL_CONST) LpRoeTxId;
  uint8 IsPrtclType2;
  #endif

  Dcm_ConfirmationStatusType ConfirmStatus = DCM_RES_NEG_NOT_OK;

  boolean LblROEType2 = DCM_FALSE;

  #if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (pMsgContext == NULL_PTR)
  {
    /* @Trace: Dcm_SUD_API_00619 */
    DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM_POINTER);
  }
  else if (pMsgContext->dcmRxPduId >= DCM_NUM_OF_PDUIDTABLECONFIG)
  {
    /* @Trace: Dcm_SUD_API_00620 */
    DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
  }
  else
  #endif
  {
    /* @Trace: Dcm_SUD_API_00621 */
    uint8 IdContext = pMsgContext->idContext;
    PduIdType RxPduId = pMsgContext->dcmRxPduId;
    uint8 ReqType = pMsgContext->msgAddInfo.reqType;

    /* @Trace: SWS_Dcm_00231 */
    boolean IsSuppressPosResponse = pMsgContext->msgAddInfo.suppressPosResponse;

    Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[RxPduId];
    uint8 TxBufferId = pPduIdTable->ucTxBufferId;
    uint8 NetworkId = pPduIdTable->ComMChannelId;
    PduIdType TxPduId = pPduIdTable->ddTxPduId;

    /* Reset the variable to store th number of response pending transmitted */
    Dcm_GusMaxNoOfRespPend = DCM_ZERO;

    #if ((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) \
         && (DCM_RESPONSE_ON_EVENT_SERVICE  ==  STD_ON))
    /* @Trace: SWS_Dcm_00928 SWS_Dcm_00132 */
    IsPrtclType2 = Dcm_IsProtocolType2(RxPduId);
    if ((Dcm_GucResOnEventStatus == DCM_ROEONGOING)
        && (DCM_TRUE == IsPrtclType2))
    {
      /* @Trace: SWS_Dcm_00926 */
      /* @Trace: Dcm_SUD_API_00624 */
      LpRoeTxId = Dcm_GaaPduIdTableConfig[RxPduId].pRoeTxId;
      TxBufferId = LpRoeTxId->ucRoeTxBufferId;
      TxPduId = LpRoeTxId->ddRoeTxPduId;
      LblROEType2 = DCM_TRUE;
    }
    #endif

    if ((TxBufferId < DCM_NUM_OF_BUFFER_CONFIG)
        && (NetworkId < DCM_NO_OF_COMM_CHANNELS))
    {
      /* @Trace: Dcm_SUD_API_00626 */
      P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer;
      pTxBuffer = Dcm_GaaBufferConfig[TxBufferId].pBufferArea;

      #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
      if (Dcm_GddPerStatus.blOnResTrans == DCM_TRUE)
      {
        /* @Trace: Dcm_SUD_API_00629 */
        RxPduId = Dcm_GddPerStatus.ddRxPduId;
        pTxBuffer = Dcm_GaaPerDataInfo[Dcm_GddPerStatus.ucDataInfoIdx].pDataBuffer;
      }
      #endif

      boolean IsNrcOccurred = DCM_FALSE;
      if (pTxBuffer[0U] == DCM_NEGATIVE_RESPONSE_SID)
      {
        /* @Trace: Dcm_SUD_API_00631 */
         IsNrcOccurred = DCM_TRUE;
         Dcm_GstMsgContext.resDataLen = 3U;
      }

      boolean IsSupResp = DCM_FALSE;
      uint8 NrcVal = pTxBuffer[2U];
      boolean IsSpecialNrcOccurred = DCM_FALSE;
      if (DCM_TRUE == IsNrcOccurred)
      {
        /* @Trace: Dcm_SUD_API_00634 */
        IsSpecialNrcOccurred = Dcm_IsSpecialNrc(NrcVal);
      }
      /* polyspace +1 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
      if (((Dcm_ProtocolRxAddrType)ReqType == DCM_FUNCTIONAL_TYPE)
          && (DCM_TRUE == IsSpecialNrcOccurred))
      {
        /* @Trace: Dcm_SUD_API_00635 */
        IsSupResp = DCM_TRUE;
        ConfirmStatus = DCM_RES_NEG_OK;
      }
      else if ((DCM_FALSE == IsNrcOccurred)
               && (DCM_TRUE == IsSuppressPosResponse))
      {
        /* @Trace: Dcm_SUD_API_00636 */
        IsSupResp = DCM_TRUE;
        ConfirmStatus = DCM_RES_POS_OK;
      }
      /* Response is transmitted in full communication mode */
      else if (Dcm_GaaCommMode[NetworkId] == DCM_FULL_COMMUNICATION)
      {
        if (DCM_FALSE == IsNrcOccurred)
        {
          #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
          if (Dcm_GddPerStatus.blOnResTrans == DCM_TRUE)
          {
            /* @Trace: SWS_Dcm_00122 */
            /* @Trace: Dcm_SUD_API_00643 */
            Dcm_PeriodicTxPduPtrType LpPerTxPdu = Dcm_GetPeriodicTxPduInfo(
              Dcm_GddPerStatus.ddRxPduId, Dcm_GddPerStatus.ucTxPduIdx);

            if (NULL_PTR != LpPerTxPdu)
            {
              /* @Trace: Dcm_SUD_API_00647 */
              TxPduId = LpPerTxPdu->ddPerTxPduId;
              TxBufferId = LpPerTxPdu->ucDataBufferId;

              if (Dcm_GaaPerDataInfo[TxBufferId].ucDataStatus == DCM_PDID_DATA_READY)
              {
                SchM_Enter_Dcm_ProtclProtection();
                if (DCM_PDID_IS_CLR_PDU_STATUS(LpPerTxPdu)) 
                {
                  /* @Trace: Dcm_SUD_API_00650 */
                  Dcm_GaaPerDataInfo[TxBufferId].ucDataStatus = DCM_PDID_DATA_BUSY;
                  DCM_PDID_SET_PDU_STATUS(LpPerTxPdu);
                  SchM_Exit_Dcm_ProtclProtection();

                  Dcm_DslTransmit(TxPduId, DCM_TRUE, LblROEType2);
                }
                else
                {
                  /* @Trace: Dcm_SUD_API_00649 */
                  SchM_Exit_Dcm_ProtclProtection();
                }
              }
            }
          }
          else
          #endif
          {
            /* @Trace: Dcm_SUD_API_00642 */
            pTxBuffer[0U] = IdContext;
            pMsgContext->resDataLen++;

            if (pMsgContext->resData != &(pTxBuffer[1U]))
            {
              /* Transfer response from the MsgContext to TxBuffer */
              for (uint8 idx = 0U; idx < pMsgContext->resDataLen; idx++)
              {
                /* @Trace: Dcm_SUD_API_00645 */
                pTxBuffer[1U + idx] = pMsgContext->resData[idx];
              }
            }

            /* Transmit positive response */
            pMsgContext->resData = pTxBuffer;
            Dcm_DslTransmit(TxPduId, DCM_FALSE, LblROEType2);
          }
        }
        else
        {
          /* In case of NRC */
          /* @Trace: SWS_Dcm_01474 */
          /* @Trace: Dcm_SUD_API_00640 */
          pMsgContext->resData = pTxBuffer;
          Dcm_DslTransmit(TxPduId, DCM_FALSE, LblROEType2);
        }
      }
      /* DCM_NO_COMMUNICATION */
      else
      {
        IsSupResp = DCM_TRUE;

        /* @Trace: Dcm_SUD_API_00638 Dcm_SUD_API_00639 */
        ConfirmStatus = (DCM_TRUE == IsNrcOccurred) ? \
          DCM_RES_NEG_NOT_OK : DCM_RES_POS_NOT_OK;
      }

      /* @Trace: SRS_Diag_04020 */
      /* @Trace: SWS_Dcm_00200 */
      if (IsSupResp == DCM_TRUE)
      {
        /* @Trace: Dcm_SUD_API_00651 */
        DspInternal_DcmConfirmation(IdContext, RxPduId, ConfirmStatus);

        Dcm_IdContextType SID = IdContext & DCM_SID_MASK;

        (void) Dcm_DsdReqManuConfirm(SID, RxPduId, ConfirmStatus);

        (void) Dcm_DsdReqSuppConfirm(SID, RxPduId, ConfirmStatus);

        if ((Dcm_GblNormalReq == DCM_TRUE)
            && (Dcm_TxRespStatus.ucPagedTrans == DCM_FALSE))
        {
          /* @Trace: Dcm_SUD_API_00653 */
          Dcm_GblNormalReq = DCM_FALSE;
        }

        Dcm_DslStatusReset();
      }
    }
    else
    {
      /* @Trace: Dcm_SUD_API_00627 */
      DCM_REPORT_ERROR(DCM_COPY_TXDATA_SID, DCM_E_PARAM);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DsdStartPagedProcessing                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API will give the complete response length to  **
**                        DCM and starts page buffer handling.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
/* @Trace: SWS_Dcm_00028 */
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
/* polyspace +1 MISRA-C3:8.3 [Justified:Low] Justify with annotations */
FUNC(void, DCM_CODE) Dcm_DsdStartPagedProcessing(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer;
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) pPduIdTable;
  P2CONST(Dcm_BufferConfig, AUTOMATIC, DCM_APPL_CONST) pBufferConfig;

  uint8 txBufferIndex;
  uint32 txBufferSize;

  PduIdType rxPduId = pMsgContext->dcmRxPduId;

  uint8 suppressPosResponse = pMsgContext->msgAddInfo.suppressPosResponse;

  /* Set the global bit flag for paging started */
  Dcm_DspSerPgStatus.ucPagingStarted = DCM_TRUE;

  /* Check if the response is to be suppressed */
  if (suppressPosResponse == DCM_FALSE)
  {
    /* @Trace: Dcm_SUD_API_00616 */
    /* Set global bit variable indicating first page is to be transmitted */
    Dcm_TxRespStatus.ucFirstPageTrans = DCM_TRUE;

    /* Set global bit variable indicating paged transmission has started */
    Dcm_TxRespStatus.ucPagedTrans = DCM_TRUE;

    /* Initialize the complete response length that is to be transmitted */
    Dcm_GddCurrentLength = pMsgContext->resDataLen;

    /* Get Tx Buffer Configuration to obtain buffer area and buffer size */
    pPduIdTable = &Dcm_GaaPduIdTableConfig[rxPduId];
    txBufferIndex = pPduIdTable->ucTxBufferId;
    pBufferConfig = &Dcm_GaaBufferConfig[txBufferIndex];

    /* Get the pointer to buffer area and the buffer size */
    pTxBuffer = pBufferConfig->pBufferArea;
    txBufferSize = pBufferConfig->ulBufferSize;

    /* Prepare one byte for SID */
    pTxBuffer++;
    txBufferSize--;

    Dcm_DspUpdatePage(pTxBuffer, txBufferSize);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_00615 */
    /* Reset the status of the RxPduId */
    Dcm_DslStatusReset();

    /* Invoke the confirmation function */
    DspInternal_DcmConfirmation(
      pMsgContext->idContext, rxPduId, DCM_RES_POS_OK);
  }
}
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DsdProcessPage                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API requests the transmission of the filled    **
**                        page during paged transmission.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : FilledPageLen                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
FUNC(void, DCM_CODE) Dcm_DsdProcessPage(
  Dcm_MsgLenType FilledPageLen)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer;
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) pPduIdTable;

  uint8 txBufferIndex;

  PduIdType rxPduId;
  PduIdType txPduId;

  rxPduId = Dcm_GstMsgContext.dcmRxPduId;
  pPduIdTable = &Dcm_GaaPduIdTableConfig[rxPduId];

  txPduId = pPduIdTable->ddTxPduId;
  txBufferIndex = pPduIdTable->ucTxBufferId;

  pTxBuffer = Dcm_GaaBufferConfig[txBufferIndex].pBufferArea;

  /* Check if it is first page that is to be transmitted */
  if (Dcm_TxRespStatus.ucFirstPageTrans == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_00609 */
    /* Update the overall length of response include SID */
    Dcm_GstMsgContext.resDataLen = Dcm_GddCurrentLength + DCM_ONE;

    /* The actual response length will be transmited */
    Dcm_GddTxResponseLen = FilledPageLen + DCM_ONE;

    /* Store the SID to the first byte of the Tx buffer */
    pTxBuffer[DCM_ZERO] = Dcm_GstMsgContext.idContext;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_00610 */
    /* Update the response length with FilledPageLen */
    Dcm_GstMsgContext.resDataLen = FilledPageLen;
  }

  /* Update the pointer to response data */
  Dcm_GstMsgContext.resData = pTxBuffer;

  /* Invoke the transmit once the response is ready */
  Dcm_DslTransmit(txPduId, DCM_FALSE, DCM_FALSE);

  /* Update the response length that is to be transmitted */
  if (Dcm_GddCurrentLength <= FilledPageLen)
  {
    /* @Trace: Dcm_SUD_API_00613 */
    /* Set the bit indicating the last page to DSP layer to True */
    Dcm_DspSerPgStatus.ucLastPage = DCM_TRUE;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_00612 */
    /* Update the response length that is to be transmitted */
    Dcm_GddCurrentLength -= FilledPageLen;
  }
}
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
