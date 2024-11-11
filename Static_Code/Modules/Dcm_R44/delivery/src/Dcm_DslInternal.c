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
**  SRC-MODULE: Dcm_DslInternal.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Provided internal API for DSL operation                       **
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
** 0.0.1     31-Dec-2019   SonDT1         AR440 Implementation                **
** 0.0.2     16-Aug-2020   HueKM          Update code for SID2A as per #14836 **
** 0.0.3     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.4     02-Nov-2020   LanhLT         Changes made as per #16832          **
** 0.0.5     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.6     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.2     18-May-2022   LanhLT         Changes made as per #26479          **
** 1.1.1     30-Oct-2023   DanhTQ1        Refer #CP44-3035                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_DslInternal.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Dsl.h"
#include "Rte_Dcm.h"

#include "SchM_Dcm.h"
#include "PduR_Dcm.h"
#include "ComM_Dcm.h"
#include "Dcm_Config.h"
#include "Dcm_ActiveDiag.h"
#include "Dcm_Timer.h"
#include "Dcm_ReqRespHandling.h"
#include "Dcm_GenericConnection.h"
#include "Dcm_Utils.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_DslWPduR_DcmTransmit                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Wrapper function of PduR_DcmTransmit                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RxPduId, TxPduId, pPduInfo                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DslWPduR_DcmTransmit(
  PduIdType RxPduId, 
  PduIdType TxPduId, 
  PduInfoPtrType pPduInfo)
{
  /* @Trace: Dcm_SUD_API_00880 */
  Std_ReturnType RetVal = E_NOT_OK;

  /* @Trace: SWS_Dcm_01166 */
  if (TxPduId != TXPDUID_UNSET)
  {
    /* @Trace: SRS_Diag_04153 SRS_Diag_04170 SRS_Diag_04174 */
    /* @Trace: Dcm_SUD_API_00881 */
    Dcm_GetTxMetaDataPtr(RxPduId, pPduInfo);

    /* @Trace: SWS_Dcm_00115 */
    /* polyspace +1 CERT-C:DCL39-C [Justified:Low] "This is Autosar structure. No Impact" */
    RetVal = PduR_DcmTransmit(TxPduId, pPduInfo);
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DslPduRTransmit                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function transmits the negative response.      **
**                        It further checks the return value of the negative  **
**                        response transmitted and further processing is done **
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
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddRxPduId,                **
**                        Dcm_GaaProtocolConfig,                              **
**                        Dcm_GaaPduIdTableConfig, Dcm_TxRespStatus,          **
**                        Dcm_GaaCommMode, Dcm_PrtclTxBufStatus,              **
**                        Dcm_GblSecDeclRequest                               **
**                        Function(s) invoked : PduR_DcmTransmit,             **
**                        Dcm_DslStatusReset, Dcm_DsdConfirmation             **
*******************************************************************************/
/* @Trace: SWS_Dcm_00114 */
FUNC(void, DCM_CODE) Dcm_DslPduRTransmit(void)
{
  PduIdType RxPduId = Dcm_GddRxPduId;
  if ((Dcm_TxRespStatus.ucNegResp == DCM_TRUE)
      && (RxPduId < DCM_NUM_OF_PDUIDTABLECONFIG))
  {
    /* @Trace: Dcm_SUD_API_00808 */
    Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[RxPduId];
    PduIdType TxPduId = pPduIdTable->ddTxPduId;

    uint8 NetworkId = pPduIdTable->ComMChannelId;
    if (NetworkId < DCM_NO_OF_COMM_CHANNELS)
    {
      if (Dcm_GaaCommMode[NetworkId] == DCM_FULL_COMMUNICATION)
      {
        /* @Trace: Dcm_SUD_API_00811 */
        PduInfoType PduInfo;
        Dcm_GetNegResp(&PduInfo);

        Std_ReturnType RetVal = Dcm_DslWPduR_DcmTransmit(RxPduId, TxPduId, &PduInfo);
        if (RetVal == E_OK)
        {
          /* @Trace: Dcm_SUD_API_00815 */
          Dcm_GddDcmTxPduId = pPduIdTable->ddTxPduId;
          Dcm_GddDcmTxConfPduId = (uint8)pPduIdTable->usTxConfirmationPduId;

          #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
          if (Dcm_GblSecDeclRequest == DCM_FALSE)
          #endif
          {
            if (DCM_TRUE == Dcm_IsTimerStarted(DCM_P2SERVERMAX_TIMER))
            {
              /* @Trace: Dcm_SUD_API_00826 */
              Dcm_StartTimer(DCM_P2SERVERMAX_TIMER,
                (GET_TIMER_P2STAR_SERVER_MAX - GET_TIMER_P2STAR_SERVER_ADJUST));
            }
          }
        }
        else /* @Trace: SWS_Dcm_00118 */
        {
          /* @Trace: Dcm_SUD_API_00817 */
          #if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
          if (Dcm_GblSecDeclRequest == DCM_FALSE)
          #endif
          {
            /* @Trace: Dcm_SUD_API_00819 */
            Dcm_DslStatusReset();
            Dcm_DsdConfirmation(E_NOT_OK);
          }

          SchM_Enter_Dcm_RxPduIdProtection();
          if (DCM_TRUE == Dcm_TxRespStatus.ucNeedFailedConfiramtion)
          {
            /* @Trace: Dcm_SUD_API_00820 */
            Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
            Dcm_TriggerCancelPendingOperation = DCM_TRUE;
          }

          SchM_Exit_Dcm_RxPduIdProtection();
          Dcm_TxRespStatus.ucNegResp = DCM_FALSE;
        }
      }
      /* @Trace: SWS_Dcm_00152 */
      else
      {
        /* @Trace: Dcm_SUD_API_00812 */
        SchM_Enter_Dcm_RxPduIdProtection();

        if (DCM_TRUE == Dcm_TxRespStatus.ucNeedFailedConfiramtion)
        {
          /* @Trace: Dcm_SUD_API_00813 */
          Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
          Dcm_TriggerCancelPendingOperation = DCM_TRUE;
        }

        SchM_Exit_Dcm_RxPduIdProtection();

        Dcm_TxRespStatus.ucNegResp = DCM_FALSE;
      }
    }
    else
    {
      /* @Trace: Dcm_SUD_API_00809 */
      Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
      Dcm_TxRespStatus.ucNegResp = DCM_FALSE;
      DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_00807 */
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;
    Dcm_TxRespStatus.ucNegResp = DCM_FALSE;
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
  }
}

/*******************************************************************************
** Function Name        : Dcm_DslTxIncorrectCondition                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function checks the status of the protocol     **
**                        start and report to DET in case of error in         **
**                        protocol. Further processing of the request is done **
**                        in case of successful protocol start                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaPduIdTableConfig,       **
**                        Dcm_GaaBufferConfig, Dcm_GddRxPduId                 **
**                        Dcm_PrtclTxBufStatus,Dcm_GddDcmTxPduId              **
**                        Dcm_MemServicePendingStatus, Dcm_GblNormalReq       **
**                        Function(s) invoked : Dcm_DslSetParameters,         **
**                        Dcm_DsdIndication, Dcm_DslStatusReset               **
**                                                                            **
*******************************************************************************/
/* sg.baek 022305 - Task #2163 in redmine */
FUNC(void, DCM_CODE) Dcm_DslTxIncorrectCondition(uint8 API_ServiceId)
{
  PduIdType RxPduId = Dcm_GddRxPduId;

  if (DCM_NUM_OF_PDUIDTABLECONFIG <= RxPduId)
  {
    /* @Trace: Dcm_SUD_API_00830 */
    DCM_REPORT_ERROR(API_ServiceId, DCM_E_INTERFACE_BUFFER_OVERFLOW);
  }
  else
  {
    uint8 RxBufferId = Dcm_GaaPduIdTableConfig[RxPduId].ucRxBufferId;

    if (DCM_NUM_OF_BUFFER_CONFIG <= RxBufferId)
    {
      /* @Trace: Dcm_SUD_API_00832 */
      DCM_REPORT_ERROR(API_ServiceId, DCM_E_INTERFACE_BUFFER_OVERFLOW);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_00833 */
      Dcm_Uint8PtrType pBufferArea = Dcm_GaaBufferConfig[RxBufferId].pBufferArea;
      Dcm_SetNegResp(pBufferArea[0], DCM_E_CONDITIONSNOTCORRECT);

      PduInfoType PduInfo;
      Dcm_GetNegResp(&PduInfo);

      Dcm_TxRespStatus.ucNegResp = DCM_TRUE;

      PduIdType TxPduId = Dcm_GaaPduIdTableConfig[RxPduId].ddTxPduId;
      Std_ReturnType RetVal = Dcm_DslWPduR_DcmTransmit(RxPduId, TxPduId, &PduInfo);

      if (RetVal == E_OK)
      {
        /* @Trace: Dcm_SUD_API_00834 */
        /* To do Dcm_DslStatusReset() after performing Dcm_TpTxConfirmation()*/
        Dcm_MemServicePendingStatus.ucStartProtocolFailed = DCM_TRUE;
        Dcm_GddDcmTxPduId = TxPduId;
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DslCheckPrtclStatus                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function checks the status of the protocol     **
**                        start and report to DET in case of error in         **
**                        protocol. Further processing of the request is done **
**                        in case of successful protocol start                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaPduIdTableConfig,       **
**                        Dcm_GaaBufferConfig, Dcm_GddRxPduId                 **
**                        Dcm_PrtclTxBufStatus,                               **
**                        Dcm_MemServicePendingStatus, Dcm_GblNormalReq       **
**                        Function(s) invoked : Dcm_DslSetParameters,         **
**                        Dcm_DsdIndication, Dcm_DslStatusReset               **
**                                                                            **
*******************************************************************************/
/* sg.baek 022305 - Task #2163 in redmine */
FUNC(void, DCM_CODE) Dcm_DslCheckPrtclStatus(void)
{
  /* @Trace: Dcm_SUD_API_00801 */
  if (Dcm_GddRxPduId < DCM_NUM_OF_PDUIDTABLECONFIG)
  {
    /* Check whether protocol started or incoming request RxPduId protocol is
     * not of the current running protocol */
    if ((Dcm_PrtclTxBufStatus.ucProtclStatus == DCM_FALSE) ||   /* No active protocol */
         (Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId].ProtocolType != Dcm_GddProtocolType)) /* preemtion */
    {
      /* @Trace: Dcm_SUD_API_00804 */
      /* Invoke function to set the values after protocol start */
      Dcm_DslSetParameters();
      Dcm_PrtclTxBufStatus.ucProtclStatus = DCM_TRUE;
    }

    if (GET_TIMER_P2_SERVER_ADJUST <= GET_TIMER_P2_SERVER_MAX)
    {
      /* @Trace: Dcm_SUD_API_00805 */
      /* if timeP2ServerMax is reached(timeout!), Dcm may respond the pending message to client */
      uint32 timeP2ServerMax = GET_TIMER_P2_SERVER_MAX - GET_TIMER_P2_SERVER_ADJUST;
      Dcm_StartTimer(DCM_P2SERVERMAX_TIMER, timeP2ServerMax);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_00806 */
      DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM);
    }

    /* Forward the request to the DSD layer */
    (void) Dcm_DsdIndication(Dcm_GddRxPduId, DCM_FALSE, DCM_FALSE, DCM_FALSE);
  }
}

/*******************************************************************************
** Function Name        : Dcm_DslSetSesTimingValues                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function should be requested by the application**
**                        after successful preparation of the timing          **
**                        parameters.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : TimerServerNew                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init and Dcm_PrepareSesTimingValues APIs should **
**                        be called before calling this API.                  **
**                        This API is only used for the service               **
**                        "DiagnosticSessionControl" which is not used within **
**                        UDS on CAN                                          **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GddOldSession, Dcm_GulChannelIdentifier         **
**                        Dcm_GddCurrentSession                               **
**                        Function(s) invoked :ComM_DCM_ActiveDiagnostic      **
**                        ComM_DCM_InactiveDiagnostic                         **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DslSetSesTimingValues(
  P2CONST(Dcm_TimerServerType, AUTOMATIC, DCM_APPL_CONST) NewTiming)
{
  /* @Trace: Dcm_SUD_API_00829 */
  if (NULL_PTR != NewTiming)
  {
    /* @Trace: SRS_Diag_04059 */
    /* @Trace: Dcm_SUD_API_00828 */
    SET_TIMER_P2_SERVER_MAX(NewTiming->Timer_P2ServerMax);
    SET_TIMER_P2STAR_SERVER_MAX(NewTiming->Timer_P2StarServerMax);

    /* @Trace: SWS_Dcm_01373  SWS_Dcm_01374*/
    Dcm_TriggerEventActivationDiagnostic(AD_TE_SESSION_CHANGE);
  }
}

/*******************************************************************************
** Function Name        : DslInternal_ResponseOnOneEvent                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API provides the processing of one event,      **
**                        requested internally in DCM.                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : MsgPtr, LddMsgLen and LddRxPduId                    **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_StatusType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GaaCommMode, Dcm_GblResOnPeriodicIdStatus,      **
**                        Dcm_GaaBufferConfig,                                **
**                        Dcm_GaaPduIdTableConfig, Dcm_GddRxPduId,            **
**                        Function(s) invoked : Dcm_DsdIndication             **
*******************************************************************************/
#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
/* @Trace: SWS_Dcm_00128 */
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(Dcm_StatusType, DCM_CODE) DslInternal_ResponseOnOneEvent(
   const Dcm_MsgType MsgPtr, Dcm_MsgLenType LddMsgLen, uint16 ConnectionId)
{
  P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_PRIVATE_CONST) LpProtocolConfig;
  P2CONST(Dcm_BufferConfig, AUTOMATIC, DCM_PRIVATE_CONST) LpBufferConfig = NULL_PTR;
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_PRIVATE_CONST) LpPduIdTable;
  P2VAR(uint8, AUTOMATIC, DCM_PRIVATE_DATA) LpRxBuffer;
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext;

  Dcm_StatusType LddResponseStatus;
  uint8 LucRxBufferId;
  uint8 LucLoopCount;
  uint8 LucProtocolId;
  uint8 LucNetworkId = DCM_ZERO;
  uint8 LucProtocolIDIndex;
  boolean LblROEType2;
  PduIdType LddRxPduId = DCM_MAXVALUE;

  for (uint8 idx = DCM_ZERO; idx < DCM_NUM_OF_PDUIDTABLECONFIG; idx++)
  {
    /* @Trace: Dcm_SUD_API_00837 */
    if (ConnectionId == Dcm_GaaPduIdTableConfig[idx].RxConnectionId)
    {
      /* @Trace: Dcm_SUD_API_00838 */
      LddRxPduId = idx;
      break;
    }
  }

  /* @Trace: Dcm_SUD_API_00839 */
  /* Initialize the return value LddResponseStatus */
  LddResponseStatus = DCM_E_ROE_NOT_ACCEPTED;
  LpPduIdTable = NULL_PTR;
  LpRxBuffer = NULL_PTR;
  LblROEType2 = DCM_FALSE;

  CHK_RET_VAL(LddRxPduId < DCM_NUM_OF_PDUIDTABLECONFIG, \
    LpPduIdTable, &Dcm_GaaPduIdTableConfig[LddRxPduId]);

  if (LpPduIdTable != NULL_PTR)
  {
    /* @Trace: Dcm_SUD_API_00843 */
    #if(DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
    LblROEType2 = Dcm_IsProtocolType2(LddRxPduId);
    if (DCM_TRUE == LblROEType2)
    {
      /* @Trace: Dcm_SUD_API_00845 */
      LucRxBufferId = ((LpPduIdTable->pRoeTxId)->ucRoeRxBufferId);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_00844 */
      LucRxBufferId = Dcm_GaaPduIdTableConfig[LddRxPduId].ucRxBufferId;
    }
    #else
    /* Initialize the Rx buffer Id for periodic event request */
    LucRxBufferId = Dcm_GaaPduIdTableConfig[LddRxPduId].ucRxBufferId;
    #endif
    
    if (LucRxBufferId < DCM_NUM_OF_BUFFER_CONFIG)
    {
      /* @Trace: Dcm_SUD_API_00846 */
      /* Initialize pointer to the Rx buffer area */
      LpBufferConfig = &Dcm_GaaBufferConfig[LucRxBufferId];
      LpRxBuffer = LpBufferConfig->pBufferArea;
      LucNetworkId = LpPduIdTable->ComMChannelId;
    }
  }

  /* @Trace: SWS_Dcm_00134 SWS_Dcm_00133 */
  if ((LpRxBuffer != NULL_PTR) &&
      (Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION) &&
      (LddMsgLen < (LpBufferConfig->ulBufferSize)))
  {
    /* @Trace: Dcm_SUD_API_00849 */
    /* Initialize the global variable for the requested message length */
    Dcm_GddRoeReqLength = LddMsgLen;

    /* Initialize the return value */
    LddResponseStatus = DCM_E_OK;

    for(LucLoopCount = DCM_ZERO; LucLoopCount < LddMsgLen; LucLoopCount++)
    {
      LpRxBuffer[LucLoopCount] = MsgPtr[LucLoopCount];
    }

    Dcm_GucResOnEventStatus = DCM_ROEONGOING;

    Dcm_StartTimer(DCM_P2SERVERMAX_TIMER, GET_TIMER_P2_SERVER_MAX);

    LpPduIdTable = &Dcm_GaaPduIdTableConfig[LddRxPduId];
    LucProtocolId = LpPduIdTable->ProtocolType;
    LucProtocolIDIndex = Dcm_GetProtocolTypeIndex(LucProtocolId);

    if (LucProtocolIDIndex < DCM_NUM_OF_PROTOCOLCONFIG)
    {
      /* @Trace: Dcm_SUD_API_00853 */
      LpProtocolConfig = &Dcm_GaaProtocolConfig[LucProtocolIDIndex];
      Dcm_GaaReqLength[LucProtocolIDIndex] = Dcm_GddRoeReqLength;

      SchM_Enter_Dcm_RxPduIdProtection();
      DCM_SET_PDU_STATUS(LpPduIdTable);
      SchM_Exit_Dcm_RxPduIdProtection();

      SchM_Enter_Dcm_ProtclProtection();
      *(LpProtocolConfig->pProtocolStatus) |=
                           (LpProtocolConfig->ucPrtclStatusMask);

      Dcm_PrtclTxBufStatus.ucProtclStatus = DCM_TRUE;
      SchM_Exit_Dcm_ProtclProtection();

      Dcm_GddRxPduId = LddRxPduId;
    }
  }

  if (LddResponseStatus == DCM_E_OK)
  {
    /* Invoke the Indication function */
    if (DCM_TRUE == Dcm_DsdIndication(Dcm_GddRxPduId, DCM_FALSE, DCM_FALSE, LblROEType2))
    {
      /* @Trace: Dcm_SUD_API_00856 */
      if(Dcm_GblSendResponse == DCM_TRUE)
      {
        /* @Trace: Dcm_SUD_API_00857 */
        Dcm_GblSendResponse = DCM_FALSE;

        #if(DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
        if (DCM_TRUE == LblROEType2)
        {
          /* @Trace: Dcm_SUD_API_00861 */
          pMsgContext = Dcm_GpRoeMsgContext;
        }
        else
        {
          /* @Trace: Dcm_SUD_API_00860 */
          pMsgContext = &Dcm_GstMsgContext;
        }
        #else
        pMsgContext = &Dcm_GstMsgContext;
        #endif

        if (Dcm_GddNegRespError != DCM_POS_RESP)
        {
          /* @Trace: Dcm_SUD_API_00863 */
          Dcm_ExternalSetNegResponse(pMsgContext, Dcm_GddNegRespError);
        }

        Dcm_ExternalProcessingDone(pMsgContext);
      }
    }
    else
    {
      Dcm_GucResOnEventStatus = DCM_ROE_IDLE;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_00854 */
    Dcm_GucResOnEventStatus = DCM_ROE_IDLE;
  }

  return(LddResponseStatus);
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
