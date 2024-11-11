/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't matter." */
/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanTp_TxInternal.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : Internal Functions implementation for CanTp module            **
**              CanTp_RequestCopyTxData                                       **
**              CanTp_CanIfTransmit                                           **
**              CanTp_ProcessRxFc                                             **
**              CanTp_TransmissionComplete                                    **
**              CanTp_UpdateTxFrameStatus                                     **
**              CanTp_TxDlcCheck                                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0     13-Sep-2023   HieuTM8        #CP44-2819                          **
** 1.0.9     12-Dec-2022   HieuTM8        #CP44-1244                          **
** 1.0.4     04-Jul-2022   HieuTM8        CP44-98                             **
** 1.0.3.1   22-Jun-2022   SMKwon         CP44-94                             **
** 1.0.3     30-May-2022   HieuTM8        R44-Redmine #26803                  **
** 1.0.2     29-Apr-2022   HieuTM8        R44-Redmine #25679, #25515          **
** 1.0.1     28-Feb-2022   HieuTM8        R44-Redmine #20400, #19344, #23963  **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp.h"                /* CanTp Module Header File */
#include "SchM_CanTp.h"           /* SchM Header File */
#include "CanTp_PCTypes.h"        /* CanTp PCTypes Header File */
#include "CanTp_TxInternal.h"     /* CanTp TxInternal Header File */
#include "CanTp_Ram.h"            /* CanTp Global RAM variables header file */
#include "PduR_CanTp.h"           /* PduR Header File */
#if (STD_ON == CANTP_DEV_ERROR_DETECT)
/* @Trace: SWS_CanTp_00217 SWS_CanTp_00267 */
/* @Trace: SWS_CanTp_00217: include DET header */
#include "Det.h"                  /* DET header file */
#endif
#include "CanIf.h"                /* CanIf Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: SWS_CanTp_00267: Version number macros for checking */
/* AUTOSAR specification version information */
#define CANTP_TXINTERNAL_C_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANTP_TXINTERNAL_C_AR_RELEASE_MINOR_VERSION    0x04u
#define CANTP_TXINTERNAL_C_AR_RELEASE_REVISION_VERSION 0x00u

/* CANTP software version information */
#define CANTP_TXINTERNAL_C_SW_MAJOR_VERSION            0x01u
#define CANTP_TXINTERNAL_C_SW_MINOR_VERSION            0x01u

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANTP_AR_RELEASE_MAJOR_VERSION !=\
 CANTP_TXINTERNAL_C_AR_RELEASE_MAJOR_VERSION)
#error "CanTp_TxInternal.c : Mismatch in Specification Major Version"
#endif
#if (CANTP_AR_RELEASE_MINOR_VERSION !=\
 CANTP_TXINTERNAL_C_AR_RELEASE_MINOR_VERSION)
#error "CanTp_TxInternal.c : Mismatch in Specification Minor Version"
#endif
#if (CANTP_AR_RELEASE_REVISION_VERSION !=\
     CANTP_TXINTERNAL_C_AR_RELEASE_REVISION_VERSION)
#error "CanTp_TxInternal.c : Mismatch in Specification Revision Version"
#endif
#if (CANTP_SW_MAJOR_VERSION != CANTP_TXINTERNAL_C_SW_MAJOR_VERSION)
#error "CanTp_TxInternal.c : Mismatch in Software Major Version"
#endif
#if (CANTP_SW_MINOR_VERSION != CANTP_TXINTERNAL_C_SW_MINOR_VERSION)
#error "CanTp_TxInternal.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> configured memory access index */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanTp_TransmissionComplete                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for completing the            **
**                        transmission and indicate the upper layer about     **
**                        transmission result                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrChannelRam                                       **
**                      : result                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_TxSduStatic          **
**                                                 CANTP_CHANNEL_ID           **
**                        Function(s) invoked    : PduR_CanTpTxConfirmation   **
**                                                 Det_ReportError            **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01081 SRS_BSW_00339 */
FUNC(void, CANTP_CODE) CanTp_TransmissionComplete(P2VAR(CanTp_ChannelRamType,
    AUTOMATIC, CANTP_VAR) ptrChannelRam, CanTp_NotifResultType result)
{
  /* @Trace: CanTp_SUD_API_310 */
  P2CONST(CanTp_TxNSduDynamicType, AUTOMATIC, CANTP_CONST) ptrTxNSduDyna;
  P2CONST(CanTp_TxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrTxNSdu = NULL_PTR;

  PduIdType activeSduId;
  
  /* Initialize the active pdu id */
  activeSduId = ptrChannelRam->ActivePduId;

  /* Initialize the channel state to IDLE (i.e. TxWait and RxWait) */
  ptrChannelRam->ChannelState = (uint8)CANTP_WAIT;

  /* Reset Tx Confirmation state to IDLE */
  ptrChannelRam->TxConfirmState = (uint8)CANTP_TX_CONF_IDLE;

  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  /* Get the dynamic RxNSdu structure Pointer */
  ptrTxNSduDyna = &(Variant_Select->PtrTxNSduDynamic)[activeSduId];

  /* Get the connection channel structure address */
  ptrTxNSdu = &(Variant_Select->PtrTxNSduStatic)[activeSduId];
  #else
  /* Get the dynamic RxNSdu structure Pointer */
  ptrTxNSduDyna = &CanTp_TxSduDynamic[activeSduId];

  /* Get the connection channel structure address */
  ptrTxNSdu = &CanTp_TxSduStatic[activeSduId];
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  /* polyspace:end<RTE: IDP : Not a defect : Low > configured memory access index */

  /* Check the communication Result value other than E_OK to report Dem*/
  if (result != (CanTp_NotifResultType)E_OK)
  {
    #if (STD_ON == CANTP_DEV_ERROR_DETECT)
    /* polyspace +7 RTE:UNR [Justified:Low] "Any timeout issues in case of transmission operation should be reported" */
    /* Report error though DET with CANTP_E_TX_COM if any timeout error */
    if (result == (CanTp_NotifResultType)CANTP_E_TX_COM)
    {
      /* @Trace: CanTp_SUD_API_311 */
      /* Report to DET */
      (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_TXCONFIRMATION_SID, CANTP_E_TX_COM);
    } /* @ if((result == NTFRSLT_E_TIMEOUT_A) ||(result == ..) */
    else /* Report error though DET with CANTP_E_COM if other than timeout error */
    {
      /* @Trace: CanTp_SUD_API_312 */
      /* Report to DET */
      (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_TXCONFIRMATION_SID, CANTP_E_COM);
    }
    #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */

    /* polyspace-begin RTE:IDP [Not a defect:Low] "Its bound is pre-defined"*/
    /* Invoke upper layer Rx indication with result */
    /* @Trace: SWS_CanTp_00310 */
    /* In case of N_As timeout occurrence */
    /* @Trace: SWS_CanTp_00280 */
    /* If data is not available within N_Cs timeout */
    /* @Trace: SWS_CanTp_00309 */
    /* If a FC frame is received with the FS set to OVFLW */
    /* @Trace: SWS_CanTp_00317 */ 
    /* Invalid FS */
    /* @Trace: SWS_CanTp_00316 */
    /* In case of N_Bs timeout occurrence the CanTp module shall abort transmission of this message */
    /* @Trace: SWS_CanTp_00204 */
    /* When the transport transmission session is successfully completed */
    /* @Trace: SWS_CanTp_00205 */
    /* Over flow, N_As timeout, N_Bs timeout */
    /* CanTp_SRS_SWS_01012 */
    /* After a transmit cancellation */
    PduR_CanTpTxConfirmation(ptrTxNSduDyna->UpConfirmationSduId, E_NOT_OK);
  } /* if(result != NTFRSLT_OK) */
  else
  {
    /* @Trace: CanTp_SUD_API_313 */
    /* @Trace: SWS_CanTp_00090 */
    /* @Trace: SWS_CanTp_00204 */
    /* When the transport transmission session is successfully completed */
    PduR_CanTpTxConfirmation(ptrTxNSduDyna->UpConfirmationSduId, E_OK);
  }
  CANTP_STOP_ALL_TX_TIMERS(ptrTxNSdu->ChannelId);
  /* polyspace-end RTE:IDP [Not a defect:Low] "Its bound is pre-defined"*/
} /* End of CanTp_TransmissionComplete(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
   * CANTP_VAR) ptrChannelRam, NotifResultType result) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON == CANTP_TX_NSDU ) */

/*******************************************************************************
** Function Name        : CanTp_RequestCopyTxData                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function requests upper Layer to copy Tx data  **
**                        and also handles the request results provided by    **
**                        upper layer                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrChannelRam                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_TxSduStatic,         **
**                                                 CanTp_GaaChannelMapping,   **
**                                                 CanTp_Timers,              **
**                                                 CANTP_CHANNEL_ID           **
**                        Function(s) invoked    : PduR_CanTpCopyTxData       **
**                                                 CanTp_TransmissionComplete **
**                                                 CanTp_CanIfTransmit        **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01079 */
FUNC(void, CANTP_CODE) CanTp_RequestCopyTxData(P2VAR(CanTp_ChannelRamType,
    AUTOMATIC, CANTP_VAR) ptrChannelRam)
{
  P2CONST(CanTp_TxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrTxNSdu = NULL_PTR;
  PduInfoType pdu;
  uint32 byteCount;
  PduLengthType availableDataPtr;
  /* @Trace: CanTp_SUD_DATATYPE_001 */
  BufReq_ReturnType lenBufferStatus;
  /* @Trace: CanTp_SUD_DATATYPE_005 */
  RetryInfoType retryInfo;
  #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
  uint16 ncsTimer;
  CanTp_ChannelType channel;
  #endif
  uint8 count;
  uint8 maxLength;
  uint8 byteIndex;
  #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
  uint8 channelIndex;
  #endif

  /* @Trace: SWS_CanTp_00272 */
  /* Note: The API PduR_CanTpCopyTxData() contains a parameter used for the
   * recovery mechanism �? (retry). Because ISO 15765-2 does not support such
   * a mechanism, the CAN Transport Layer does not implement any kind of recovery.
   * Thus, the parameter is always set to NULL pointer. */
  /* However, CanTp can initialize the retry info values */
  /* #8900 TP_NORETRY->TP_DATACONF */
  retryInfo.TpDataState = (TpDataStateType)TP_DATACONF;

  /* Set data count to default value */
  retryInfo.TxTpDataCnt = (PduLengthType)CANTP_ZERO;

  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  /* Get the TxNSdu structure address */
  ptrTxNSdu = &(Variant_Select->PtrTxNSduStatic)[ptrChannelRam->ActivePduId];
  #else
  /* Get the TxNSdu structure address */
  ptrTxNSdu = &CanTp_TxSduStatic[ptrChannelRam->ActivePduId];
	#endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  /* polyspace +2 RTE:IDP [Not a defect:Low] "The pointer ptrTxNSdu->TxSduMaxLength can not outside �t bounds. Because the variable TxSduMaxLength is declared uint8 but the maximum value of TxSduMaxLength is 4294967295. However, User shall not config over out of range uitn8. This warning not impact" */
  /* Get the CAN_DL of TxSdu */
  maxLength = ptrTxNSdu->TxSduMaxLength;
  /* Get the number of data bytes to be transmitted */
  byteCount = (ptrChannelRam->ByteCounter);

  #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
  /* polyspace:begin <RTE: IDP : Not a defect : Low -> configured memory access index */
  /* Get the connection channel structure address */
  channel = ptrTxNSdu->ChannelId;

  /* Get the channel index in the channel Mapping array*/
  channelIndex = CanTp_ChannelMapping[channel];

  SchM_Enter_CanTp_TIMER_PROTECTION();
  /* Get the N_Cs Timer value */
  ncsTimer = CanTp_Timers[channelIndex][CANTP_NCS_TIMER];


  
  /* Check if N_Cs timer is  not started */
  if ((uint16)CANTP_ZERO == ncsTimer)
  {
    /* @Trace: CanTp_SUD_API_314 */
    /* @Trace: SWS_CanTp_00167 */
    /* If support PostBuild */
    #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
    /* Start N_Cs Timer */
    ncsTimer = (Variant_Select->PtrTxNSduDynamic)[ptrChannelRam->ActivePduId].NcsTimeoutValue;
	  #else
    /* Start N_Cs Timer */
    ncsTimer = CanTp_TxSduDynamic[ptrChannelRam->ActivePduId].NcsTimeoutValue;
	#endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  } /* End of if (CANTP_ZERO == ncsTimer) */
  SchM_Exit_CanTp_TIMER_PROTECTION();
  #endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */

  /* Get the local data buffer index where the data will start filling out with the count or bytecount */
  byteIndex = ptrChannelRam->LocalDataByteIndex;

  /* Get the number of remaining bytes in the present frame  */
  count = ((uint8)maxLength) - byteIndex;

  /* Set the destination(local) buffer address */
  pdu.SduDataPtr = &(ptrChannelRam->DataBuffer[byteIndex]);

  #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
  if(ptrChannelRam->FrameType == (uint8)CANTP_FF_PCI)
  {
    /* @Trace: CanTp_SUD_API_315 */
    pdu.SduLength = count;
  }
  else if (ptrChannelRam->FrameType == (uint8)CANTP_CF_PCI)
  {
    #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
      (STD_ON == CANTP_TX_MIXED_ADDRESS) ||\
      (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS))
    /* Check if current frame for transmission is the last CF */
    if (byteCount <= (uint32)(((uint32)maxLength - (uint8)CANTP_ONE) -
          CanTp_BytePos[ptrTxNSdu->AddressingMode]))
    #else /* End of if ((STD_ON  == CANTP_TX_EXTENDED_ADDRESS) ||
              *(STD_ON == CANTP_TX_MIXED_ADDRESS)) */
    if (byteCount <= ((uint32)maxLength - (uint32)CANTP_ONE))
    #endif /* End of if ((STD_ON  == CANTP_TX_EXTENDED_ADDRESS) ||
            * (STD_ON == CANTP_TX_MIXED_ADDRESS)) */
    {
      /* @Trace: CanTp_SUD_API_318 */
      /* Set the number of bytes to be filled in the  last CF */
      pdu.SduLength = (PduLengthType)byteCount;
    }
    else
    {
      /* @Trace: CanTp_SUD_API_319 */
      /* Set the number of bytes to be filled in the CFs */
      pdu.SduLength = (PduLengthType)count;
    }
  } /* else if(ptrChannelRam->FrameType == CANTP_CF_PCI) */
  /* Frame type is single frame */
  else
  #endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */
  {
    /* @Trace: CanTp_SUD_API_320 */
    /* Set the number of bytes to be filled in the SF */
    pdu.SduLength = (PduLengthType)byteCount;
  }
  /* @Trace: SWS_CanTp_00299 */
  /* For an N-SDU with MetaData, the MetaData also provided via
   * the PduInfoPtr is relevant */
  /* @Trace: SWS_CanTp_00086 */
  /* The CanTp module shall call the PduR_CanTpCopyTxData service
   * for each segment that is sent (SF, FF and CF). The upper layer copy the
   * transmit data on the PduInfoType structure. */
  /* If support PostBuild */
	#if	(STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  lenBufferStatus = PduR_CanTpCopyTxData(
          (Variant_Select->PtrTxNSduDynamic)[ptrChannelRam->ActivePduId].UpConfirmationSduId,
          &pdu,
          &retryInfo,
          &availableDataPtr);
	#else
  lenBufferStatus = PduR_CanTpCopyTxData(
          CanTp_TxSduDynamic[ptrChannelRam->ActivePduId].UpConfirmationSduId,
          &pdu,
          &retryInfo,
          &availableDataPtr);
	#endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  /* Buffer status is okay */
  if (BUFREQ_OK == lenBufferStatus)
  {
    /* @Trace: CanTp_SUD_API_321 */
    #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
    /* Stop N_Cs timer */
    ncsTimer = (uint16)CANTP_ZERO;
    #endif

    /* Check if the frame is last frame */
    if (byteCount <= count)
    {
      /* @Trace: CanTp_SUD_API_322 */
      /* Set number of bytes to be copied equal to total remaining bytes */
      count = (uint8)byteCount;
    }

    /* Update the Byte counter and Available buffer length */
    ptrChannelRam->ByteCounter = (ptrChannelRam->ByteCounter) -\
                                    (uint32)count;

    /* Update the current frame length */
    ptrChannelRam->CurrentFrameLen = count + byteIndex;

    /* Check if current frame for transmission is SF or FF */
    if (ptrChannelRam->NewFrameFlag == (uint8)CANTP_TX_SFORFF)
    {
      /* @Trace: CanTp_SUD_API_323 */
      /* Transmit the data to lower layer */
      CanTp_CanIfTransmit(ptrTxNSdu);
      /*Set the new frame flag status as start of Transmission of CF */
      ptrChannelRam->NewFrameFlag = (uint8)CANTP_CONSCFRAME;
    } /* End of if (ptrChannelRam->NewFrameFlag == CANTP_TX_SFORFF) */
    else
    {
      /* @Trace: CanTp_SUD_API_324 */
      /* Set the buffer state to buffer ready */
      ptrChannelRam->BufferState = (uint8)CANTP_TX_RDY;
    }
  } /* if(lenBufferStatus == BUFREQ_OK) */
  /* @Trace: SWS_CanTp_00272 */
  /* If the upper layer cannot make Tx data available because of an error
    * (e.g. in gateway case it may indicate that the transport session from
    * the source network was terminated), the PduR_CanTpCopyTxData() function
    * returns BUFREQ_E_NOT_OK */
  /* @Trace: SWS_CanTp_00087 */
  /* If PduR_CanTpCopyTxData() returns BUFREQ_E_NOT_OK, the CanTp module
    * shall abort the transmit request and notify the upper layer of this failure by calling
    * the callback function PduR_CanTpTxConfirmation() with the result E_NOT_OK */
  else if (BUFREQ_E_NOT_OK == lenBufferStatus)
  {
    /* @Trace: CanTp_SUD_API_325 */
    /* Invoke TxConfirmation with failure */
    CanTp_TransmissionComplete(ptrChannelRam, (CanTp_NotifResultType)E_NOT_OK);
  } /* BUFREQ_E_NOT_OK */
  else if (BUFREQ_E_BUSY == lenBufferStatus)
  {
    /* Update the Tp Buffer status */
    /* @Trace: SWS_CanTp_00089 */
    /* @Trace: CanTp_SUD_API_378 */
    /* When Tx data is available, the CanTp module shall
      * resume the transmission of the N-SDU */
    ptrChannelRam->BufferState = (uint8)CANTP_TX_NOTRDY_INITREQ;
  } /* BUFREQ_E_BUSY */
  else
  {
    /* To avoid QAC error */
  }
  #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
  /* Reload the N_Cs timer */
  CANTP_TIMER_UPDATE_MACRO(channelIndex, CANTP_NCS_TIMER, ncsTimer);
  #endif

} /* End of CanTp_RequestCopyTxData(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
   * CANTP_VAR) ptrChannelRam) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON == CANTP_TX_NSDU ) */

/*******************************************************************************
** Function Name        : CanTp_CanIfTransmit                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to check STmin timer and      **
**                        hence invoke CanIf_Transmit function                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrTxNSdu                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_ChannelMapping,      **
**                                                 CanTp_ChannelRam,          **
**                                                 CanTp_StMinTimers          **
**                                                 CanTp_ChannelId            **
**                                                 Cantp_Padding_Byte         **
**                        Function(s) invoked    : CanTp_UpdateTxFrameStatus  **
**                                                 CanIf_Transmit             **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01073 SRS_Can_01068 SRS_Can_01069 SRS_Can_01071 SRS_Can_01078 */
FUNC(void, CANTP_CODE) CanTp_CanIfTransmit(P2CONST(CanTp_TxNsduStaticType,
    AUTOMATIC, CANTP_CONST) ptrTxNSdu)
{
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  PduInfoType pduInfo;
  CanTp_ChannelType channel;

  #if (CANTP_FD_SUPPORT == STD_ON)
  PduLengthType length;
  boolean flagLoop;
  #else
  #if (CANTP_TX_SDU_PADDING_ACTIVATION == STD_ON)
  PduLengthType length;
  #endif
  #endif
  uint16 nasTimer;
  uint8 channelIndex;
  #if(CANTP_FD_SUPPORT == STD_ON)
  PduLengthType discreteLen;
  uint8 iteration;
  #endif
  VAR(Std_ReturnType, AUTOMATIC) returnCanIfTransmit;

  /* Set MetaDataPtr to default */
  pduInfo.MetaDataPtr = NULL_PTR;
  #if(CANTP_FD_SUPPORT == STD_ON)
  discreteLen = (PduLengthType)CANTP_ZERO;
  flagLoop = CANTP_FALSE;
  #endif

  /* polyspace:begin<RTE: IDP : Not a defect : Low > configured memory access index */
  /* Get the connection channel structure address */
  channel = ptrTxNSdu->ChannelId;
  /* polyspace:end<RTE: IDP : Not a defect : Low > configured memory access index */

  channelIndex = CanTp_ChannelMapping[channel];

  /* Get the pointer to channel RAM*/
  ptrChannelRam = &CanTp_ChannelTxRam[channelIndex];

  /* When the STMin timer expired (CanTp_StMinTimers[channel] = CANTP_ZERO) */
  /* @Trace: SWS_CanTp_00335 */
  /* @Trace: CanTp_SUD_API_379 */
  /* When calling CanIf_Transmit() for an SF, FF, or CF
   * of a generic connection (N-PDU with MetaData),
   * the CanTp module shall provide the stored addressing information
   * via MetaData of the N-PDU.
   * The addressing information in the MetaData depends on the addressing format:
   * Normal, Extended, Mixed 11 bit: none
   * Normal fixed, Mixed 29 bit: N_SA, N_TA.
   */
  #ifdef CANTP_DYNID_SUPPORT
  if ((CANTP_TRUE == ptrChannelRam->AvlMetaDt) &&\
  /* Only pass metaData if Pdu is configured. Otherwise
   * consider same with normal */
  (CANTP_TRUE == ptrTxNSdu->OutTxPduwithMetaDataSts))
  {
    /* @Trace: CanTp_SUD_API_327 */
    #if (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS)
    /* Provide the stored addressing information via MetaData of the N-PDU.
     * Only available if addressing type is Normal fixed or mixed 29 bit
     */
	  if (CANTP_NORMALFIXED_ADDRESS == ptrTxNSdu->AddressingMode)
    {
      /* @Trace: CanTp_SUD_API_328 */
      pduInfo.MetaDataPtr = (uint8*)&ptrChannelRam->LoMetaData;
    }

    #endif /* End of #if (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) */

    #if (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS)
    if (CANTP_MIXED29BIT_ADDRESS == ptrTxNSdu->AddressingMode)
    {
      /* @Trace: CanTp_SUD_API_329 */
      pduInfo.MetaDataPtr = (uint8*)&ptrChannelRam->LoMetaData;
    }
    #endif /* End of #if (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) */
  }
  #endif /* End of #ifdef CANTP_DYNID_SUPPORT */

  pduInfo.SduDataPtr = ptrChannelRam->DataBuffer;
  pduInfo.SduLength = (PduLengthType)ptrChannelRam->CurrentFrameLen;
  /* ECUC_CanTp_00269: transmit a frame using padding or not */
  #if (CANTP_FD_SUPPORT == STD_ON)

  /* Selective Padding in case of DLC 1..7 */
  if(pduInfo.SduLength == (uint32)CANTP_EIGHT)
  {
      /* Do Nothing */
  }
  /* @Trace: SWS_CanTp_00348 */
  /* Frames with a payload <= 8 (either CAN 2.0 frames or small CAN FD frames) are used for a Tx N-SDU */
  else if(pduInfo.SduLength < (uint32)CANTP_EIGHT)
  {
    #if (STD_ON == CANTP_TX_SDU_PADDING_ACTIVATION)
    /* @Trace: CanTp_SUD_API_330 */
    if (CANTP_TRUE == ptrTxNSdu->TxPaddingActivation)
    {
      /* @Trace: CanTp_SUD_API_381 */
      /* if SduLength is less than CANTP_EIGHT, it needs to be padded */
      length = pduInfo.SduLength;
      pduInfo.SduLength = (PduLengthType)CANTP_EIGHT;
      CANTP_MEMCPY(&pduInfo.SduDataPtr[length], &CanTp_PaddingByte[(uint8)CANTP_ZERO], ((size_t)CANTP_EIGHT - (size_t)length));
    }
    #endif /* #if (STD_ON == CANTP_TX_SDU_PADDING_ACTIVATION) */
  }
  /* Rationale: The ISO 11898-1:2015 DLC values from 9 to 15 are assigned to nonlinear
    * discrete values for CAN frame pay-load length up to 64 byte. To prevent the
    * transmission of uninitialized data the padding of CAN frame data is mandatory for
    * DLC values greater than eight when the length of the N_PDU size to be transmitted
    * is not equal to one of the discrete length values defined in the ISO 11898-1:2015
    * DLC table. For DLC values from 9 to 15 only the mandatory padding should be used. */
  else
  {
    /* @Trace: CanTp_SUD_API_331 */
    /* @Trace: SWS_CanTp_00351 */
    /* Use the higher valid DLC.
      * Find Discreted Data Length for this transmission */
    for(iteration = 0; (iteration < CANTP_SEVEN) && (flagLoop == CANTP_FALSE); iteration++)
    {
      /* @Trace: CanTp_SUD_API_332 */
      if(pduInfo.SduLength <= (PduLengthType)CanTp_DiscreteDlcDataLength[iteration])
      {
        ptrChannelRam->DecreteIndex = iteration;

        discreteLen = (PduLengthType)CanTp_DiscreteDlcDataLength[iteration];

        flagLoop = CANTP_TRUE;
      }
    }
    
    length = pduInfo.SduLength;
    /* polyspace-begin RTE:STD_LIB [Not a defect:Low] "Confirmed by the customer, It's can be accepted"*/
    /* if sduLength is equal to Discrete Length, it does NOT need to be padded */
    if(length < discreteLen)
    {
      /* @Trace: CanTp_SUD_API_333 */
      pduInfo.SduLength = (PduLengthType)discreteLen;
      CANTP_MEMCPY(&pduInfo.SduDataPtr[length], &CanTp_PaddingByte[(uint8)CANTP_ZERO], ((size_t)discreteLen - (size_t)length)); /* polyspace MISRA C:2012 Dir 4.14 [Justified:Low] "By passed the call of CanTp_TxDetCheck() api, the value received from external sources already checked." */
    }
    /* polyspace-end RTE:STD_LIB [Not a defect:Low] "Confirmed by the customer, It's can be accepted"*/
  }

  /* @Trace: SWS_CanTp_00348 */
  /* Frames with a payload <= 8 (either CAN 2.0 frames or small CAN FD frames) are used for a Tx N-SDU */
  #else/*#if(CANTP_FD_SUPPORT == STD_ON)*/
  #if (STD_ON == CANTP_TX_SDU_PADDING_ACTIVATION)
  /* Check if the SDU is configured for PADDING ACTIVATION equal to STD_ON */
  if (CANTP_TRUE == ptrTxNSdu->TxPaddingActivation)
  {
    /* @Trace: CanTp_SUD_API_334 */
    if (pduInfo.SduLength < (PduLengthType)CANTP_EIGHT)
    {
      /* @Trace: CanTp_SUD_API_335 */
      length = pduInfo.SduLength;
      pduInfo.SduLength = (PduLengthType)CANTP_EIGHT;

      /* polyspace-begin RTE:IDP [Not a defect:Low] "Confirmed by the customer, It's can be accepted"*/
      /* if LucLength is less than CANTP_EIGHT, it needs to be padded */
      CANTP_MEMCPY(&pduInfo.SduDataPtr[length], &CanTp_PaddingByte[(uint8)CANTP_ZERO], (CANTP_EIGHT - length));
      /* polyspace-end RTE:IDP [Not a defect:Low] "Confirmed by the customer, It's can be accepted"*/
    } /* End of if (pduInfo.SduLength != CANTP_EIGHT) */
  } /* End of if (CANTP_TRUE == ptrTxNSdu->blTxPaddingActivation) */
  #endif /* End of #if (STD_ON == CANTP_TX_SDU_PADDING_ACTIVATION) */
  #endif /*#if(CANTP_FD_SUPPORT == STD_ON)*/

  /* polyspace-begin RTE:OBAI [Not a defect:Low] "configured memory access index"*/

  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  nasTimer = ((Variant_Select->PtrTxNSduDynamic)[ptrChannelRam->ActivePduId].
                        NasTimeoutValue + ((uint16)(ptrChannelRam->NewFrameFlag) &
                                            (uint16)CANTP_ONE));
  #else
  nasTimer = (CanTp_TxSduDynamic[ptrChannelRam->ActivePduId].
                        NasTimeoutValue + ((uint16)(ptrChannelRam->NewFrameFlag) &
                                            (uint16)CANTP_ONE));
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  /* polyspace-end RTE:OBAI [Not a defect:Low] "configured memory access index"*/

  /* Start N_As timer */
  CANTP_TIMER_UPDATE_MACRO(channelIndex, CANTP_NAS_TIMER, nasTimer);

  /* Update the frame parameters */
  CanTp_UpdateTxFrameStatus(ptrChannelRam, ptrTxNSdu);

  /* polyspace:begin<RTE: OBAI : Not a defect : Low > configured  memory access index */
  /* Request lower layer (CanIf) transmit request */
  /* @Trace: SWS_CanTp_00035 */
  /* @Trace: CanTp_SUD_API_374 */
    
  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  /* NSduId shall only be linked to one CAN LSduId */
  returnCanIfTransmit = CanIf_Transmit((Variant_Select->PtrTxNSduDynamic)
    [ptrChannelRam->ActivePduId].LoTargetPduId,
    &pduInfo);
  #else
  /* NSduId shall only be linked to one CAN LSduId */
  returnCanIfTransmit = CanIf_Transmit(CanTp_TxSduDynamic
    [ptrChannelRam->ActivePduId].LoTargetPduId,
    &pduInfo);
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  /* @Trace: SWS_CanTp_00343 */
  /* CanTp shall terminate the current transmission connection when
    * CanIf_Transmit() returns E_NOT_OK when transmitting an SF, FF, of CF. */
  if (E_NOT_OK == returnCanIfTransmit)
  {
    /* @Trace: CanTp_SUD_API_336 */
    /* Do not wait for timeout of N_As, CanTp shall notify to upper about
     * transmission result */
    CanTp_TransmissionComplete(ptrChannelRam, E_NOT_OK);
  }
  /* polyspace:end<RTE: OBAI : Not a defect : Low > configured  memory access index */

} /* End of CanTp_CanIfTransmit(void) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_TX_NSDU ) */

/*******************************************************************************
** Function Name        : CanTp_UpdateTxFrameStatus                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to update the status of next  **
**                        frame to be sent                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrChannelRam                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_UpdateTxFrameStatus(P2VAR(CanTp_ChannelRamType,
    AUTOMATIC, CANTP_VAR) ptrChannelRam, P2CONST(CanTp_TxNsduStaticType,
    AUTOMATIC, CANTP_CONST) ptrTxNSdu)
{
  (void)ptrTxNSdu;
  uint8 npciPos;
  uint8 txConfirmState;

  /* Check if the frame is not the last frame */
  if (ptrChannelRam->ByteCounter != (uint32)CANTP_ZERO)
  {
    /* @Trace: CanTp_SUD_API_337 */
    #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)

    /* Increment frame counter */
    (ptrChannelRam->FrameCounter)++;

    /* Check if frame counter is greater than 15 */
    if (ptrChannelRam->FrameCounter > (uint8)CANTP_MAX_FRAME_COUNTER)
    {
      /* @Trace: CanTp_SUD_API_338 */
      /* Reset the frame counter */
      ptrChannelRam->FrameCounter = (uint8)CANTP_ZERO;
    }
    #endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */
    /* Update the PCI byte position*/
    npciPos = ptrChannelRam->CurrentBytePosition;

    /* Update the buffer index from where the data needs to be loaded */
    ptrChannelRam->LocalDataByteIndex = npciPos + (uint8)CANTP_ONE;
    
    /* polyspace +2 RTE:OBAI [Not a defect:Low] "The maximum value of npciPos is assigned equal maximum of CanTp_BytePos[ptrRxNSdu->AddressingMode] is 4, but array DataBuffe[]r is declared with array index is CANTP_EIGHT. So, This warning not impact." */
    if ((ptrChannelRam->DataBuffer[npciPos] & (uint8)(CANTP_FF_PCI)) ==
        ((uint8)CANTP_FF_PCI))
    {
      /* @Trace: CanTp_SUD_API_339 */
      /* Update the Tx confirmation state to FF */
      txConfirmState = (uint8)CANTP_LAST_CF_TX_CONF;
    }
    else
    {
      /* @Trace: CanTp_SUD_API_340 */
      /* Update the Tx confirmation state to CF */
      txConfirmState = (uint8)CANTP_CF_TX_CONF;
    }
    #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)

    if (((uint16)CANTP_ZERO != ptrChannelRam->BSVar) &&
            (CANTP_INFINITE_BS != ptrChannelRam->BSVar))
    {
      /* @Trace: CanTp_SUD_API_341 */
      /* Decrement the BlockSize variable */
      (ptrChannelRam->BSVar)--;

      if ((uint16)CANTP_ZERO == ptrChannelRam->BSVar)
      {
        /* @Trace: CanTp_SUD_API_342 */
        /* Update the Tx confirmation state to last CF in the block */
        txConfirmState = (uint8)CANTP_LAST_CF_TX_CONF;
      }
    } /* End of if (ptrChannelRam->ucBSVar != CANTP_ZERO) */
    #endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */
  } /* Check if the frame is not the last frame */
  else
  {
    /* @Trace: CanTp_SUD_API_343 */
    /* Update the Tx confirmation state as last frame in the TP message */
    txConfirmState = (uint8)CANTP_SF_LF_TX_CONF;
  }

  /* Copy the Tx confirmation state to global variable */
  ptrChannelRam->TxConfirmState = txConfirmState;

  /* Update the Tx BufferState state to TX Buffer not ready */
  ptrChannelRam->BufferState = (uint8)CANTP_TX_NOTRDY;

} /* End of CanTp_UpdateTxFrameStatus(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
   * CANTP_VAR) ptrChannelRam) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_TX_NSDU ) */

/*******************************************************************************
** Function Name        : CanTp_ProcessRxFc                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for transmission of           **
**                        flow control to the sender                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : txSduId                                             **
**                        ptrCanTpRxPdu                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_TxSduStaticType,     **
**                                                 CanTp_ChannelMode,         **
**                                                 CanTp_ChannelMapping,      **
**                                                 CanTp_ChannelRamType,      **
**                                                 CanTp_STminMapping,        **
**                                                 CanTp_BytePos              **
**                                                 CanTp_TxSduDynamic         **
**                                                 Cantp_Main_Function_Period **
**                                                 CANTP_CHANNEL_ID           **
**                        Function(s) invoked    : CanTp_TransmissionComplete **
*******************************************************************************/
#if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01082 SRS_Can_01081 */
FUNC(void, CANTP_CODE) CanTp_ProcessRxFc(PduIdType txSduId, P2CONST(PduInfoType,
    AUTOMATIC, CANTP_CONST) ptrRxPduInfor)
{
  P2CONST(CanTp_TxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrTxNSdu = NULL_PTR;
  P2CONST(uint8, AUTOMATIC, CANTP_CONST) ptrCanTpRxPdu;
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  uint8 bytePos;
  uint8 flowStatus;
  uint8 stMin;
  CanTp_ChannelType channel;
  uint8 channelIndex;
  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  #if ((STD_ON == CANTP_TX_NORMALFIXED_ADDRESS)||\
    (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
    (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) ||\
     (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS))
  VAR(CanTp_LongAccessType, AUTOMATIC) longAccess;
  VAR(boolean, AUTOMATIC) invalidNAi;
  #endif
  #endif
  #endif

  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  #if ((STD_ON == CANTP_TX_NORMALFIXED_ADDRESS)||\
    (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
    (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) ||\
     (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS))
  /* Set invalidNAi to default*/
  longAccess.WholeLong = (uint32)CANTP_ZERO;
  invalidNAi = CANTP_FALSE;
  #endif
  #endif
  #endif

  /* Assign SduDataPtr to local pointer */
  ptrCanTpRxPdu = ptrRxPduInfor->SduDataPtr;

  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  ptrTxNSdu = &(Variant_Select->PtrTxNSduStatic)[txSduId];
  #else
  ptrTxNSdu = &CanTp_TxSduStatic[txSduId];
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  /* polyspace +2 RTE:IDP [Not a defect:Low] "The pointer ptrTxNSdu->ChannelId can outsite its bounds with declare varible ChannelId is uint8 then maximum the number of ChannelId is 255. However, User shall not config over many Channel to outside its bounds. This warning not imapct." */
  /* Get the connection channel structure address */
  channel = ptrTxNSdu->ChannelId;
  
  /* Get channel from the channel mapping table */
  channelIndex = CanTp_ChannelMapping[channel];

  ptrChannelRam = &CanTp_ChannelTxRam[channelIndex];
 
  /* @Trace: SWS_CanTp_00057 */
  /* Check if in awaited state for FC, otherwise ignore it */
  if ((uint8)CANTP_RX_FC == ptrChannelRam->ChannelState)
  {
    /* @Trace: CanTp_SUD_API_344 */
    #if (STD_ON == CANTP_TX_SDU_PADDING_ACTIVATION)
    /* @Trace: SWS_CanTp_00349 */
    /* Length of FC should be equal to Eight when Padding is enable */
    if ((CANTP_TRUE == ptrTxNSdu->TxPaddingActivation) &&\
      (ptrRxPduInfor->SduLength < (uint8)CANTP_EIGHT))
    {
      /* @Trace: CanTp_SUD_API_345 */
      #if (STD_ON == CANTP_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_RXINDICATION_SID, CANTP_E_PADDING);
      #endif
      /* The CanTp module shall abort the transmission session*/
      CanTp_TransmissionComplete(ptrChannelRam, \
              (CanTp_NotifResultType)E_NOT_OK);
    }
    else
    #endif /* (STD_ON == CANTP_TX_SDU_PADDING_ACTIVATION) */
    {
      /* @Trace: CanTp_SUD_API_346 */
      #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
      (STD_ON == CANTP_TX_MIXED_ADDRESS)||\
        (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS))

      /* Get the N_PCI position if transmit NSDU is configured as Extended */
      bytePos = CanTp_BytePos[ptrTxNSdu->AddressingMode];
      #else

      /* Get the N_PCI position */
      bytePos = (uint8)CANTP_ZERO;
      #endif
      /* polyspace +3 RTE:NIV [Not a defect:Low] "The value of ptrCanTpRxPdu has been gotten from the PDU, no impact" */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "The pointer ptrCanTpRxPdu can not outside its bounds because the maximum value of bytePos is 4. Thus, this warning not impact." */
      /* Get the flow status value into local variable */
      flowStatus = (ptrCanTpRxPdu[bytePos]) & ((uint8)CANTP_FS_MASK);
      #ifdef CANTP_DYNID_SUPPORT
      #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
      #if ((STD_ON == CANTP_TX_NORMALFIXED_ADDRESS)||\
      (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
      (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) ||\
        (STD_ON == CANTP_TX_MIXED29BIT_ADDRESS))
      if (((CANTP_NORMALFIXED_ADDRESS == ptrTxNSdu->AddressingMode) ||\
      (CANTP_MIXED29BIT_ADDRESS == ptrTxNSdu->AddressingMode)) &&\
      (CANTP_TRUE == ptrTxNSdu->OutTxPduwithMetaDataSts))
      {
        /* Only verify if Pdu following with valid metaData */
        /* @Trace: CanTp_SUD_API_347 */
        if(NULL_PTR != ptrRxPduInfor->MetaDataPtr)
        {
          /* @Trace: CanTp_SUD_API_367 */ 
          /* Get the metaData value */
          longAccess.WholeLong = (uint32)*((uint32*)&ptrRxPduInfor->MetaDataPtr[(uint8)CANTP_ZERO]);
          /* @Trace: SWS_CanTp_00336 */
          /* When CanTp_RxIndication is called for an FC
            * on a generic connection (N-PDU with MetaData),
            * the CanTp module shall check the addressing information
            * contained in the MetaData against the stored values.*/
          if ((ptrChannelRam->LoMetaData.byte_val.LSByte != longAccess.byte_val.Byte_1) ||\
            (ptrChannelRam->LoMetaData.byte_val.Byte_1 != longAccess.byte_val.LSByte))
          {
            /* @Trace: CanTp_SUD_API_349 */
            /* Mismatch N_AI */
            invalidNAi = CANTP_TRUE;
          }
        }
      }

      /* Check passed N_AI with Generic connection support only */
      if (CANTP_TRUE != invalidNAi)
      #endif /* #if ((STD_ON == CANTP_TX_NORMALFIXED_ADDRESS)||... */
      #endif /* #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
      #endif /* End of CANTP_DYNID_SUPPORT */
      {
        /* Decode the flow status */
        switch (flowStatus)
        {
          case (uint8)CANTP_FS_CTS:
            /* @Trace: CanTp_SUD_API_350 */
            bytePos++;
            /* polyspace +11 RTE:NIV [Not a defect:Low] "The value of ptrCanTpRxPdu has been gotten from the PDU, no impact" */
            /* Copy the BS value into global variables */
            ptrChannelRam->BSVar = ptrCanTpRxPdu[bytePos];

            if ((uint16)CANTP_ZERO == ptrChannelRam->BSVar)
            {
              ptrChannelRam->BSVar = CANTP_INFINITE_BS;
            }
            bytePos++;

            /* Copy the STmin value into local variable */
            stMin = ptrCanTpRxPdu[bytePos];

            if (stMin <= (uint8)CANTP_STMIN_DIRECT_VALUE_RANGE)
            {
              /* @Trace: CanTp_SUD_API_351 */
              if (stMin != (uint8)CANTP_ZERO)
              {
                /* @Trace: CanTp_SUD_API_352 */
                /* Update the current transmission STmin value =
                  * 2+(Received STmin - 1)/MainFunctionPeriod */

                ptrChannelRam->StMinValue =
                /* ((stMin - ((uint8)CANTP_ONE)) / CANTP_MAIN_FUNCTION_PERIOD) +*/
                (uint8)((stMin - ((uint8)CANTP_ONE)) / (uint8)CANTP_MAIN_FUNCTION_PERIOD ) +
                (uint8)CANTP_TWO;
              } /* End of if (stMin != CANTP_ZERO) */
              else
              {
                /* @Trace: CanTp_SUD_API_353 */
                /* Update the Minimum Separation Time value equal to Zero */
                ptrChannelRam->StMinValue = (uint8)CANTP_ZERO;
              }
            }
            /*
              * if(stMin <= CANTP_STMIN_DIRECT_VALUE_RANGE)
              * Check if the received STmin is in 100us - 900us range
              * */
            else if ((stMin >= (uint8)CANTP_STMIN_US_LOW) &&
                      (stMin <= (uint8)CANTP_STMIN_US_HIGH))
            {
              /* @Trace: CanTp_SUD_API_354 */
              /* Update the STmin value based on the received STmin */
              ptrChannelRam->StMinValue =
                CanTp_STminMapping[stMin & (uint8)CANTP_STMIN_MAP_MASK];
            } /* End of if ((stMin >= CANTP_STMIN_US_LOW) && */
            else /* Received STmin value is a reserved value */
            {
              /* @Trace: CanTp_SUD_API_355 */
              /* Update the STmin value equal to Max STmin delay(i.e 127ms) */

              /* Update the current transmission STmin value =
                *                     2+(Maximum STmin - 1)/MainFunctionPeriod */
              ptrChannelRam->StMinValue =
                (uint8)(((uint8)CANTP_MAX_STMIN_DELAY - (uint8)CANTP_ONE) /
                CANTP_MAIN_FUNCTION_PERIOD) + (uint8)CANTP_TWO;
            } /*
                * End of else
                * Update channel state to normal
                */
            ptrChannelRam->ChannelState = (uint8)CANTP_TX_NORMAL;

            /* Stop N_Bs timer */
            CANTP_TIMER_UPDATE_MACRO(channelIndex, CANTP_NBS_TIMER,
            ((uint16)CANTP_ZERO));

            /* Set the channel buffer state to request the buffer */
            ptrChannelRam->BufferState = (uint8)CANTP_TX_NOTRDY_INITREQ;
            break;

          case (uint8)CANTP_FS_WT:
            /* @Trace: CanTp_SUD_API_159 */
            /* polyspace +14 RTE:OBAI [Not a defect:Low] "Array index of CanTp_RxSduStatic[] can not outsside bounds because ptrChannelRam-> ActivePduId depend on rxSduId. However, the maximum value of rxSduId and ActivePduId are the same. So, this warning not impact." */
            /* (Re)Start the N_Bs timer */
            /* @Trace: SWS_CanTp_00315 */
            /* Start N_Bs after receiving FC with FS = WT */
            /* If support PostBuild */
            #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
              CANTP_TIMER_UPDATE_MACRO(
                    channelIndex,
                    CANTP_NBS_TIMER,
                    (Variant_Select->PtrTxNSduDynamic)[ptrChannelRam->ActivePduId].NbsTimeoutValue);
            #else
              CANTP_TIMER_UPDATE_MACRO(
                    channelIndex,
                    CANTP_NBS_TIMER,
                    CanTp_TxSduDynamic[ptrChannelRam->ActivePduId].NbsTimeoutValue);
            #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

            /* polyspace-end RTE:OBAI [Not a defect:Low] "configured memory access index"*/
            break;

          case (uint8)CANTP_FS_OVFLW:
            /* @Trace: CanTp_SUD_API_165 */
            /* Invoke upper layer Tx confirmation to mention there is no
              * receive buffer to receive further bytes */
            /* @Trace: SWS_CanTp_00309 */
            /* Receive with the FS set to OVFLW */
            CanTp_TransmissionComplete(
                    ptrChannelRam,
                    (CanTp_NotifResultType)E_NOT_OK);
            break;

          default: /* Invalid flow status */
            /* @Trace: CanTp_SUD_API_168 */
            /* Invoke upper layer Tx confirmation to mention an Invalid
              * Flow status is received */
            /* @Trace: SWS_CanTp_00317 */
            /* Iinvalid FS*/
            CanTp_TransmissionComplete(
                    ptrChannelRam,
                    (CanTp_NotifResultType)E_NOT_OK);
            break;
        } /* End of switch statement */
      } /* End of if (CANTP_TRUE != invalidNAi) */
    } /* end of Padding check */
  } /* @ if((uint8)CANTP_RX_FC == ptrChannelRam->ChannelState) */

} /* End of CanTp_ProcessRxFc(P2CONST(uint8, AUTOMATIC, CANTP_CONST)
   * ptrCanTpRxPdu) */
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */

/*******************************************************************************
** Function Name        : CanTp_TxDlcCheck                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs the data length checks on    **
**                        new frames                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrTxNSdu                                           **
**                        txDatalength                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : dlcErrorFlag                                        **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_BytePos              **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, CANTP_CODE) CanTp_TxDlcCheck(P2CONST(CanTp_TxNsduStaticType,
    AUTOMATIC, CANTP_CONST) ptrTxNSdu, PduLengthType txDatalength)
{
  boolean dlcErrorFlag;
  /* @Trace: CanTp_SUD_API_356 */
  /* Assign the default value to be used */
  dlcErrorFlag = CANTP_FALSE;

  /* Check Tx datalength is less than minimum length configured for
   * transmission */
  if (txDatalength < (PduLengthType)CANTP_ONE)
  {
    /* @Trace: CanTp_SUD_API_177 */
    dlcErrorFlag = CANTP_TRUE;
  }
  /* Passing MISRA-C rule */
  CANTP_UNUSED(txDatalength);

  /* polyspace +1 RTE:UNR [Not a defect:Unset] "This gray check not imapct because the parameter ptrTxNSdu can not config all  is Zero or NULL" */
  CANTP_UNUSED(ptrTxNSdu);
  return (dlcErrorFlag);
} /* End of CanTp_TxDlcCheck(P2CONST(CanTp_TxNsduStaticType, AUTOMATIC, CANTP_CONST)
   * ptrTxNSdu, PduLengthType txDatalength) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON == CANTP_TX_NSDU ) */
/* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> configured memory access index */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
