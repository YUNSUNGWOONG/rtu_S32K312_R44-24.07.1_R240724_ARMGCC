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
**  SRC-MODULE: Dcm_Dsl.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Implementation for DSL sub-module                             **
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
** 0.0.3     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.4     02-Nov-2020   LanhLT         Changes made as per #16832          **
** 0.0.5     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.6     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm.h"
#include "Dcm_Ram.h"

#include "Rte_Dcm.h"
#include "SchM_Dcm.h"
#include "ComM_Dcm.h"
#include "PduR_Dcm.h"
#include "Dcm_DslInternal.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Dsl.h"
#include "Dcm_Config.h"
#include "Dcm_ActiveDiag.h"
#include "Dcm_Timer.h"
#include "Dcm_SessionControl.h"
#include "Dcm_Utils.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : DslInternal_ResponseOnOneDataByPeriodicId           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API provides the processing of one event,      **
**                        requested by the DSP internally                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PeriodicId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_StatusType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GaaCommMode, Dcm_GblResOnPeriodicIdStatus,      **
**                        Dcm_GblNormalReq, Dcm_GaaPduIdTableConfig           **
**                        Dcm_GaaBufferConfig,                                **
**                        Dcm_GucPeriodicRxPduId , Dcm_GddRxPduId             **
**                        Dcm_GaaProtocolConfig                               **
**                        Function(s) invoked : Dcm_DsdIndication             **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
FUNC(Dcm_StatusType, DCM_CODE) DslInternal_ResponseOnOneDataByPeriodicId(
  uint8 PeriodicId)
{
  uint8 LucRxBufferId;
  boolean LblIndRetVal;
  Dcm_StatusType LddRetVal = DCM_E_PERIODICID_NOT_ACCEPTED;

  Dcm_Uint8PtrType LpBufferArea;
  Dcm_PduIdTablePtrType LpPduIdTable;

  if (Dcm_GddPerStatus.ddRxPduId < DCM_NUM_OF_PDUIDTABLECONFIG)
  {
    /* @Trace: Dcm_SUD_API_00758 */
    /* Get Pdu Table configure using for receive initial request */
    LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddPerStatus.ddRxPduId];

    /* @Trace: SWS_Dcm_00123 */
    if (DCM_FULL_COMMUNICATION == Dcm_GaaCommMode[LpPduIdTable->ComMChannelId])
    {
      /* @Trace: Dcm_SUD_API_00759 */
      /* Separate buffer using for simulating request */
      LucRxBufferId = LpPduIdTable->ucPerRxBufferId;
      LpBufferArea = Dcm_GaaBufferConfig[LucRxBufferId].pBufferArea;

      /* Simulate the UDS 0x22 request */
      LpBufferArea[DCM_ZERO] = DCM_READDATABYIDENTIFIER;

      /* Set PDID from data queue */
      LpBufferArea[DCM_ONE] = DCM_PDID_HIGH_BYTE;
      LpBufferArea[DCM_TWO] = PeriodicId;

      /* Start the Timer P2ServerMax */
      Dcm_StartTimer(
        DCM_P2SERVERMAX_TIMER,
        (GET_TIMER_P2_SERVER_MAX - GET_TIMER_P2_SERVER_ADJUST));

      /* Main processing to get data */
      LblIndRetVal = Dcm_DsdIndication(
        Dcm_GddPerStatus.ddRxPduId, DCM_FALSE, DCM_TRUE, DCM_FALSE);

      /* @Trace: Dcm_SUD_API_00760 Dcm_SUD_API_00761 */
      /* Convert the return value */
      LddRetVal = (DCM_TRUE == LblIndRetVal) ? DCM_E_OK : DCM_E_PERIODICID_NOT_ACCEPTED;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_00757 */
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM);
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DslTransmit                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is invoked by DSD when the response   **
**                        is ready in the DSD layer                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : TxPduId, IsPeriodicTransmission,                    **
**                        IsROETransmission                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_PrtclTxBufStatus,          **
**                        Dcm_TxRespStatus,                                   **
**                        Dcm_GblNormalReq , Dcm_GaaCommMode                  **
**                        Dcm_GblResOnPeriodicIdStatus, Dcm_GucPeriodicRxPduId**
**                        Dcm_GaaCbkReqServices, Dcm_GaaPduIdTableConfig      **
**                        Dcm_GpPerMsgContext , Dcm_GddRxPduId                **
**                        Function(s) invoked : PduR_DcmTransmit              **
**                        Dcm_DsdConfirmation, Dcm_DslStatusReset,            **
**                        Dcm_DslCheckPrtclStatus,                            **
**                        Xxx_StartProtocol                                   **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DslTransmit(
  PduIdType TxPduId
  , boolean IsPeriodicTransmission
  , boolean IsRoeTransmission)
{
  PduInfoType PduInfo;
  Std_ReturnType RetVal;

  PduIdType RxPduId = Dcm_GddRxPduId;
  if (DCM_NUM_OF_PDUIDTABLECONFIG <= RxPduId)
  {
    /* @Trace: Dcm_SUD_API_00722 */
    /* Det Error */
  }
  else if (DCM_TRUE == DCM_IS_ACTIVE_PROTOCOL_STATUS())
  {
    if (Dcm_TxRespStatus.ucNegResp == DCM_FALSE)
    {
      /* @Trace: Dcm_SUD_API_00726 */
      Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[RxPduId];
      uint8 NetworkId = pPduIdTable->ComMChannelId;

      if (NetworkId < DCM_NO_OF_COMM_CHANNELS)
      {
        /* @Trace: Dcm_SUD_API_00730 */
        if ((Dcm_GaaCommMode[NetworkId] == DCM_FULL_COMMUNICATION)
            &&
            (
              (Dcm_GblNormalReq == DCM_TRUE)

              #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
              || (Dcm_GddPerStatus.blOnResTrans == DCM_TRUE)
              #endif

              #if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
              || (Dcm_GucResOnEventStatus == DCM_ROEONGOING)
              #endif
            )
           )
        {
          /* @Trace: Dcm_SUD_API_00737 */
          #if ((DCM_PROTOCOL_TRANSTYPE2 == STD_ON) && \
               (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON))
          uint8 IsPrtclType2 = Dcm_IsProtocolType2(RxPduId);
          /* @Trace: SWS_Dcm_01045 */
          if ((DCM_TRUE == IsRoeTransmission)
              && (DCM_TRUE == IsPrtclType2))
          {
            /* @Trace: Dcm_SUD_API_00739 */
            PduInfo.SduLength = (uint16)Dcm_GpRoeMsgContext->resDataLen;
            PduInfo.SduDataPtr = Dcm_GpRoeMsgContext->resData;
          }
          else
          #else
          DCM_UNUSED(IsRoeTransmission);
          #endif
          {
            /* @Trace: Dcm_SUD_API_00741 */
            #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
            if (DCM_TRUE == IsPeriodicTransmission)
            {
              /* @Trace: SWS_Dcm_01101 */
              if (Dcm_GddPerStatus.blOnResTrans == DCM_TRUE)
              {
                /* @Trace: SWS_Dcm_01072 */
                /* @Trace: Dcm_SUD_API_00743 */
                SchM_Enter_Dcm_ProtclProtection();
                PduInfo.SduLength = (uint16) Dcm_GstPerMsgContext.resDataLen;
                PduInfo.SduDataPtr = Dcm_GstPerMsgContext.resData;
                SchM_Exit_Dcm_ProtclProtection();
              }
            }
            else
            #endif
            {
              /* @Trace: Dcm_SUD_API_00742 */
              PduInfo.SduLength = (PduLengthType)Dcm_GstMsgContext.resDataLen;
              PduInfo.SduDataPtr = Dcm_GstMsgContext.resData;
            }
          }

          /* Stop P2 server max timer*/
          Dcm_StopTimer(DCM_P2SERVERMAX_TIMER);

          #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
          if (Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE)
          {
            /* @Trace: Dcm_SUD_API_00747 Dcm_SUD_API_00748 */
            RetVal = (Dcm_TxRespStatus.ucFirstPageTrans == DCM_TRUE) ?
              Dcm_DslWPduR_DcmTransmit(RxPduId, TxPduId, &PduInfo) : E_OK;
          }
          else
          #endif
          {
            /* @Trace: Dcm_SUD_API_00746 */
            RetVal = Dcm_DslWPduR_DcmTransmit(RxPduId, TxPduId, &PduInfo);
          }

          /* Transmission OK */
          if (RetVal == E_OK)
          {
            #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
            if (Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE)
            {
              /* @Trace: Dcm_SUD_API_00749 */
              Dcm_TxRespStatus.ucDslPagedTrans = DCM_TRUE;
            }
            #endif

            if (DCM_FALSE == IsPeriodicTransmission)
            {
              /* @Trace: Dcm_SUD_API_00750 */
              Dcm_TxRespStatus.ucNormResponse = DCM_TRUE;
            }
          }
          /* @Trace: SWS_Dcm_00118 */
          /* Transmission NOT_OK */
          else
          {
            if (DCM_TRUE == IsPeriodicTransmission)
            {
              /* @Trace: Dcm_SUD_API_00751 */
              #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
              Dcm_PeriodicTxPduPtrType LpPerTxPdu = Dcm_GetPeriodicTxPduInfo(
                Dcm_GddPerStatus.ddRxPduId, Dcm_GddPerStatus.ucTxPduIdx);

              if (NULL_PTR != LpPerTxPdu)
              {
                /* @Trace: SWS_Dcm_01104 */
                /* @Trace: Dcm_SUD_API_00752 */
                /* Retry the transmit in this Tx channel */
                LpPerTxPdu->blBusyStatus = DCM_FALSE;

                SchM_Enter_Dcm_ProtclProtection();

                DCM_PDID_CLR_PDU_STATUS(LpPerTxPdu);

                Dcm_GaaPerDataInfo[Dcm_GddPerStatus.ucDataInfoIdx].
                  ucDataStatus = DCM_PDID_DATA_IDLE;

                SchM_Exit_Dcm_ProtclProtection();
              }
              #endif
            }

            /* @Trace: Dcm_SUD_API_00753 */
            Dcm_DsdConfirmation(E_NOT_OK);

            #if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
            if (Dcm_GucResOnEventStatus == DCM_ROE_IDLE)
            {
              /* @Trace: Dcm_SUD_API_00755 */
              Dcm_GblNormalReq = DCM_FALSE;
              Dcm_DslStatusReset();
            }
            #else
            Dcm_GblNormalReq = DCM_FALSE;
            Dcm_DslStatusReset();
            #endif
          }
        }
      }
    }
    else
    {
      /* @Trace: Dcm_SUD_API_00725 */
      Dcm_TxRespStatus.ucRespPending = DCM_TRUE;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_00723 */
    /* No action in this case */
  }
}

/*******************************************************************************
** Function Name        : Dcm_DslSetParameters                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function loads the needed parameters into the  **
**                        global variables after the successful start of the  **
**                        protocol                                            **
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
** Remarks              : Global Variable(s) : Dcm_GaaPduIdTableConfig        **
**                        Dcm_GddProtocolType, Dcm_GaaProtocolConfig,         **
**                        Dcm_GucPrtclPriority, Dcm_GddCurrentSession         **
**                        Dcm_GpMsgContext                                    **
**                        Dcm_GddRxPduId                                      **
**                        Dcm_GulChannelIdentifier ,                          **
**                        Function(s) invoked : ComM_DCM_ActiveDiagnostic,    **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04059 */
FUNC(void, DCM_CODE) Dcm_DslSetParameters(void)
{
  Dcm_SessionConfigConstPtrType pSessionCfg;
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) rxPduId;
  P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_CONST) cfgProtocol;

  #if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_GddRxPduId >= DCM_NUM_OF_PDUIDTABLECONFIG)
  {
    /* @Trace: Dcm_SUD_API_00703 */
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM);
  }
  else
  #endif
  {
    /* Get the pointer to the corresponding RxPduId structure */
    rxPduId = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
    cfgProtocol = Dcm_GetProtocolConfigPtr(Dcm_GddRxPduId);

    if (NULL_PTR != cfgProtocol)
    {
      Dcm_GddProtocolType = rxPduId->ProtocolType;
      Dcm_GucPrtclPriority = cfgProtocol->ucProtocolPrio;

      if (Dcm_GblJumpToBootloader == DCM_FALSE)
      {
        /* @Trace: Dcm_SUD_API_00707 */
        /* Reset the session level in the global variable */
        Dcm_GddCurrentSession = DCM_DEFAULT_SESSION;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_00709 */
        /* if ECU is started from FBL, 
         * shall keep the session that was changed in the FBL */
        Dcm_GblJumpToBootloader = DCM_FALSE;
      }

      /* @Trace: SWS_Dcm_00146 */
      DslInternal_SetSecurityLevel(DCM_SEC_LEV_LOCKED);

      /* Update the RxPduId in the message context */
      Dcm_GstMsgContext.dcmRxPduId = Dcm_GddRxPduId;

      /* @Trace: SRS_Diag_04208 */
      /* @Trace: SWS_Dcm_00147 */
      (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(Dcm_GddCurrentSession);

      /* Get the current session configuration */
      pSessionCfg = Dcm_GetSesCtrlConfigByType(Dcm_GddCurrentSession);

      /* @Trace: SWS_Dcm_00144 */
      /* @Trace: SRS_Diag_04015 */
      if (NULL_PTR != pSessionCfg)
      {
        /* @Trace: Dcm_SUD_API_00710 */
        /* Set the configured timing value if it is valid */
        SET_TIMER_P2_SERVER_MAX(pSessionCfg->usSesP2ServerMax);
        SET_TIMER_P2STAR_SERVER_MAX(pSessionCfg->usSesP2StrServerMax);
      }
      else
      {
        /* @Trace: Dcm_SUD_API_00711 */
        /* Set default P2 and P2Star timing value */
        SET_TIMER_P2_SERVER_MAX(DCM_TIMSTR_P2_SERVER_MAX);
        SET_TIMER_P2STAR_SERVER_MAX(DCM_TIMSTR_P2_STAR_SERVER_MAX);
      }

      /* Set other timing values */
      SET_TIMER_S3_SERVER(DCM_TIMSTR_S3_SERVER);
      SET_TIMER_P2_SERVER_ADJUST(cfgProtocol->usTimStrP2ServerAdjust);
      SET_TIMER_P2STAR_SERVER_ADJUST(cfgProtocol->usTimStrP2StarServerAdjust);
      
      /* Get the Channel Identifier associated to the received Pdu */
      Dcm_GulChannelIdentifier = rxPduId->ComMChannelId;

      /* @Trace: SWS_Dcm_01373 */
      Dcm_TriggerEventActivationDiagnostic(AD_TE_RECEIVED_REQUEST);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_00705 */
      DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DslStatusReset                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function starts the S3 server timer and also   **
**                        clears the RxPduId status                           **
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
** Remarks              : Global Variable(s) :                                **
**                          Dcm_GddCurrentSession,                            **
**                        Dcm_GddRxPduId ,Dcm_GaaPduIdTableConfig             **
**                                                                            **
**                        Function(s) invoked :                               **
**                          Dcm_StartTimer, Dcm_StopTimer,                    **
**                          Dcm_GetProtocolConfigPtr,                         **
**                          Dcm_TriggerEventActivationDiagnostic              **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DslStatusReset(void)
{
  Dcm_PduIdTablePtrType pPduIdTable;
  Dcm_ProtocolConfigConstPtrType pProtocolCfg;

  #if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_GddRxPduId >= DCM_NUM_OF_PDUIDTABLECONFIG)
  {
    /* @Trace: Dcm_SUD_API_00715 */
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    if (CHECK_NONDEFAULT_SESSION(Dcm_GddCurrentSession))
    {
      /* @Trace: Dcm_SUD_API_00717 */
      /* Restart S3 timer if Dcm is on non-default session */
      Dcm_StartTimer(DCM_S3SERVER_TIMER, GET_TIMER_S3_SERVER);
    }
    else
    {
      /* @Trace: SWS_Dcm_01374 SWS_Dcm_01378 */
      /* @Trace: Dcm_SUD_API_00716 */
      Dcm_TriggerEventActivationDiagnostic(AD_TE_FINISHED_REQUEST);
    }

    /* Stop P2 server max timer */
    Dcm_StopTimer(DCM_P2SERVERMAX_TIMER);

    /* Get Pdu Table configuration, it must not be null */
    pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];

    /* Clear pdu status in critical section */
    SchM_Enter_Dcm_RxPduIdProtection();
    DCM_CLR_PDU_STATUS(pPduIdTable);
    SchM_Exit_Dcm_RxPduIdProtection();

    /* Get protocol configuration, it can be null */
    pProtocolCfg = Dcm_GetProtocolConfigPtr(Dcm_GddRxPduId);

    if (NULL_PTR != pProtocolCfg)
    {
      /* @Trace: Dcm_SUD_API_00719 */
      /* Clear protocol status in critical section */
      SchM_Enter_Dcm_ProtclProtection();
      DCM_CLR_PROTOCOL_STATUS(pProtocolCfg);
      SchM_Exit_Dcm_ProtclProtection();
    }
  }
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
