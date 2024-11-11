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
**  SRC-MODULE: CanTp_RxInternal.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : Internal Functions implementation for CanTp module            **
**              CanTp_RxPduBufferChk                                          **
**              CanTp_RequestRxBuffer                                         **
**              CanTp_TransmitFc                                              **
**              CanTp_CopyRxFrame                                             **
**              CanTp_RxCfDlcCheck                                            **
**              CanTp_RxNewframeDlcCheck                                      **
**              CanTp_RxBinarySearch                                          **
**              CanTp_ReceptionComplete                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0     31-Oct-2023   HieuTM8        #CP44-2819, #CP44-3155, #CP44-3129  **
** 1.0.10    20-Apr-2023   HieuTM8        #CP44-2002                          **
** 1.0.9     12-Dec-2022   HieuTM8        #CP44-1244                          **
** 1.0.8     25-Nov-2022   HieuTM8        #CP44-1199                          **
** 1.0.4     04-Jul-2022   HieuTM8        CP44-98                             **
** 1.0.3.1   22-Jun-2022   SMKwon         CP44-94                             **
** 1.0.3     30-May-2022   HieuTM8        R44-Redmine #26803, #26380          **
** 1.0.2     18-Apr-2022   HieuTM8        R44-Redmine #25679, #25515          **
** 1.0.1     28-Feb-2022   HieuTM8        R44-Redmine #20400, #19344, #23963  **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp.h"                /* CanTp RxInternal Header File */
#include "CanTp_PCTypes.h"        /* CanTp PCTypes Header File */
#include "CanTp_RxInternal.h"     /* CanTp RxInternal Header File */
#include "CanTp_Ram.h"            /* CanTp Global RAM variables header file */
#include "SchM_CanTp.h"           /* SchM Header File */
/* @Trace: SWS_CanTp_00216 SWS_CanTp_00217 SWS_CanTp_00267 */
/* @Trace: SWS_CanTp_00216: Include mandatory header */
#include "PduR_CanTp.h"           /* PduR Header File */
#if (STD_ON == CANTP_DEV_ERROR_DETECT)
/* @Trace: SWS_CanTp_00217: include DET header */
#include "Det.h"                  /* DET header file */
#endif
#include "CanIf.h"                /* CanIf Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: SWS_CanTp_00267: Version number macros for checking */
/* AUTOSAR specification version information */
#define CANTP_RXINTERNAL_C_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANTP_RXINTERNAL_C_AR_RELEASE_MINOR_VERSION    0x04u
#define CANTP_RXINTERNAL_C_AR_RELEASE_REVISION_VERSION 0x00u

/* CANTP software version information */
#define CANTP_RXINTERNAL_C_SW_MAJOR_VERSION            0x01u
#define CANTP_RXINTERNAL_C_SW_MINOR_VERSION            0x01u

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANTP_AR_RELEASE_MAJOR_VERSION !=\
 CANTP_RXINTERNAL_C_AR_RELEASE_MAJOR_VERSION)
#error "CanTp_RxInternal.c : Mismatch in Specification Major Version"
#endif
#if (CANTP_AR_RELEASE_MINOR_VERSION !=\
 CANTP_RXINTERNAL_C_AR_RELEASE_MINOR_VERSION)
#error "CanTp_RxInternal.c : Mismatch in Specification Minor Version"
#endif
#if (CANTP_AR_RELEASE_REVISION_VERSION !=\
     CANTP_RXINTERNAL_C_AR_RELEASE_REVISION_VERSION)
#error "CanTp_RxInternal.c : Mismatch in Specification Revision Version"
#endif
#if (CANTP_SW_MAJOR_VERSION != CANTP_RXINTERNAL_C_SW_MAJOR_VERSION)
#error "CanTp_RxInternal.c : Mismatch in Software Major Version"
#endif
#if (CANTP_SW_MINOR_VERSION != CANTP_RXINTERNAL_C_SW_MINOR_VERSION)
#error "CanTp_RxInternal.c : Mismatch in Software Minor Version"
#endif

#define CANTP_START_OF_RECPT_FOUR_FOUR_ZERO (STD_ON)
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> configured memory access index */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanTp_ReceptionComplete                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for completing the            **
**                        reception and indicate the upper layer about        **
**                        reception result                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrChannelRam                                       **
**                        result                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_RxSduStatic,         **
**                                                 CanTp_GpRxSduDynamic       **
**                                                 CANTP_CHANNEL_ID           **
**                        Function(s) invoked    : PduR_CanTpRxIndication     **
**                                                 Dem_ReportErrorStatus      **
**                                                 Det_ReportError            **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01073 */
FUNC(void, CANTP_CODE) CanTp_ReceptionComplete(P2VAR(CanTp_ChannelRamType,
    AUTOMATIC, CANTP_VAR) ptrChannelRam, CanTp_NotifResultType result)
{
  P2CONST(CanTp_RxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrRxNSdu = NULL_PTR;
  P2CONST(CanTp_RxNSduDynamicType, AUTOMATIC, CANTP_CONST) ptrRxNSduDyna;
  /* @Trace: CanTp_SUD_API_211 */
  if ((uint8)CANTP_WAIT != ptrChannelRam->ChannelState)
  {
    /* @Trace: CanTp_SUD_API_212 */
    /* Initialize the channel state to IDLE (i.e. TxWait and RxWait) */
    ptrChannelRam->ChannelState = (uint8)CANTP_WAIT;

    /* Reset Tx Confirmation state to IDLE */
    ptrChannelRam->TxConfirmState = (uint8)CANTP_TX_CONF_IDLE;

    /* Clear ByteCounter */
    ptrChannelRam->ByteCounter = (uint32)CANTP_ZERO;

    /* If support PostBuild */
    #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
    /* Get the static RxNSdu structure Pointer */
    ptrRxNSdu = &(Variant_Select->PtrRxNSduStatic)[ptrChannelRam->ActivePduId];
    #else
    /* Get the static RxNSdu structure Pointer */
    ptrRxNSdu = &CanTp_RxSduStatic[ptrChannelRam->ActivePduId];
    #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

    /* polyspace:begin<RTE: IDP : Not a defect : Low > 
                                  Its boundary is pre-defined */

    /* If support PostBuild */
    #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
    /* Get the dynamic RxNSdu structure Pointer */
    ptrRxNSduDyna = &(Variant_Select->PtrRxNSduDynamic)[ptrChannelRam->ActivePduId];
    #else
    /* Get the dynamic RxNSdu structure Pointer */
    ptrRxNSduDyna = &CanTp_RxSduDynamic[ptrChannelRam->ActivePduId];
    #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

    /* Reset the Ram variable */
    ptrChannelRam->ActivePduId = (PduIdType)CANTP_ZERO;

    /* polyspace:end<RTE: IDP : Not a defect : Low > 
                                Its boundary is pre-defined */
    /* Check the communication Result value other than NTFRSLT_OK to report Dem */
    if (result != (CanTp_NotifResultType)E_OK)
    {
      #if (STD_ON == CANTP_DEV_ERROR_DETECT)
      /* @Trace: SWS_CanTp_00346 */
      /* Abort the ongoing last CF */
      /* @Trace: SWS_CanTp_00229 */
      /* Report error through DET with CANTP_E_RX_COM if any timeout error */
      if (result == (CanTp_NotifResultType)CANTP_E_PADDING)
      {
        /* @Trace: CanTp_SUD_API_213 */
        /* Report to DET */
        (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_MAINFUNCTION_SID, CANTP_E_PADDING);
      } /* @ if((result == NTFRSLT_E_TIMEOUT_A) ||(result == ..) */
      /* polyspace +6 RTE:UNR [Justified:Low] "Any timeout issues in case of reception operation should be reported" */
      else if (result == (CanTp_NotifResultType)CANTP_E_RX_COM)
      {
        /* @Trace: CanTp_SUD_API_214 */
        /* Report to DET */
        (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
            CANTP_RXINDICATION_SID, CANTP_E_RX_COM);
      }
      else /* Report error through DET with CANTP_E_COM if other than timeout
            * error */
      {
        /* @Trace: CanTp_SUD_API_215 */
        /* Report to DET */
        (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_MAINFUNCTION_SID, CANTP_E_COM);
      }
      #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
      /* Invoke upper layer Rx indication with result */
      /* @Trace: SWS_CanTp_00339 */
      /* The returns buffer is BUFREQ_OK with a smaller available buffer size
      * than needed for the already received data.
      * The CanTp module shall abort the reception */
      /* @Trace: SWS_CanTp_00084 */
      /* When the transport reception session is completed (successfully or not) the CanTp module
      * shall call the upper layer notification service PduR_CanTpRxIndication()*/

      /* polyspace +1 RTE:IDP [Not a defect:Low] "The pointer ptrRxNSduDyna->UpTargetPduId can not outside its bounds because the variable UpTargetPduId is declared with uint16 but User shall not config the large number. So, this warning not impact." */
      PduR_CanTpRxIndication(ptrRxNSduDyna->UpTargetPduId, E_NOT_OK);
    } /* if(result != NTFRSLT_OK) */
    else
    {
      /* @Trace: CanTp_SUD_API_216 */
      /* @Trace: SWS_CanTp_00084 */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "The pointer ptrRxNSduDyna->UpTargetPduId can not outside its bounds because the variable UpTargetPduId is declared with uint16 but User shall not config the large number. So, this warning not impact." */
      /* Invoke upper layer Rx indication with result */
      PduR_CanTpRxIndication(ptrRxNSduDyna->UpTargetPduId, E_OK);
    }
    /* Store the connection channel in local variable*/
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined " */
    CANTP_STOP_ALL_RX_TIMERS(ptrRxNSdu->ChannelId);
  } /* End of if ((uint8)CANTP_WAIT != ptrChannelRam->ChannelState) */
} /* End of CanTp_ReceptionComplete(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
   * CANTP_VAR) ptrChannelRam, NotifResultType result) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_TransmitFc                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is responsible for transmitting       **
**                        the FC                                              **
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
** Remarks              : Global Variable(s)     : CanTp_RxSduStatic,         **
**                                                 CanTp_GpRxSduDynamic,      **
**                                                 CANTP_CHANNEL_ID           **
**                                                 Cantp_Padding_Byte         **
**                        Function(s) invoked    : CanIf_Transmit             **
*******************************************************************************/
#if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01148 SRS_Can_01068 SRS_Can_01069 SRS_Can_01071 SRS_Can_01078 */
FUNC(void, CANTP_CODE) CanTp_TransmitFc(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
    CANTP_VAR) ptrChannelRam)
{
  P2CONST(CanTp_STminBsType, AUTOMATIC, CANTP_CONST) ptrRxNSduRam;
  P2CONST(CanTp_RxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrRxNSdu;
  P2CONST(CanTp_RxNSduDynamicType, AUTOMATIC, CANTP_CONST) ptrRxNSduDyna;
  PduInfoType pduInfo;
  CanTp_ChannelType channel;
  uint16 narTimer;
  uint8 dataArray[CANTP_EIGHT];
  uint8 frameSize;
  uint8 bytePos;
  
  /* Set MetaDataPtr to default */
  pduInfo.MetaDataPtr = NULL_PTR;

  /*If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  /* Get the static RxNSdu structure Pointer */
  ptrRxNSdu = &(Variant_Select->PtrRxNSduStatic)[ptrChannelRam->ActivePduId];
  #else
  /* Get the static RxNSdu structure Pointer */
  ptrRxNSdu = &CanTp_RxSduStatic[ptrChannelRam->ActivePduId];
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  /* @Trace: SWS_CanTp_00332 */
  /* When calling CanIf_Transmit() for an FC on a generic
   * connection (N-PDU with MetaData), the CanTp module shall provide the stored
   * addressing information via the MetaData of the N-PDU. The addressing information
   * in the MetaData depends on the addressing format:
   * + Normal, Extended, Mixed 11 bit: none
   * + Normal fixed, Mixed 29 bit: N_SA (saved N_TA), N_TA (saved N_SA)
   * [Other] Apply same with case Dynamic support and generic connection is off.
   */
  #ifdef CANTP_DYNID_SUPPORT
  #if ((STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
    (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))
  
  if ((((uint8)CANTP_NORMALFIXED_ADDRESS == ptrRxNSdu->AddressingMode)||\
      ((uint8)CANTP_MIXED29BIT_ADDRESS == ptrRxNSdu->AddressingMode)) &&\
    /* PduFC for RxSdu configured with metaData */
    (CANTP_TRUE == ptrRxNSdu->InPduwithMetaDataSts))
  {
    /* @Trace: CanTp_SUD_API_217 */
    pduInfo.MetaDataPtr = (uint8*)&ptrChannelRam->LoFcMetaData;
  }
  #endif
  #endif

  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  /* Get the dynamic RxNSdu structure Pointer */
  ptrRxNSduDyna = &(Variant_Select->PtrRxNSduDynamic)[ptrChannelRam->ActivePduId];
  #else
  /* Get the dynamic RxNSdu structure Pointer */
  ptrRxNSduDyna = &CanTp_RxSduDynamic[ptrChannelRam->ActivePduId];
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))

  /* Get the N_PCI position if transmit NSDU is configured as Extended */
  bytePos = CanTp_BytePos[ptrRxNSdu->AddressingMode];
  #else
  bytePos = (uint8)CANTP_ZERO;
  #endif
  /* polyspace +2 RTE:IDP [Not a defect:Low] "The pointer ptrRxNSdu->ChannelId can outsite its bounds with declare varible ChannelId is uint8 then maximum the number of ChannelId is 255. However, User shall not config over many Channel to outside its bounds. This warning not imapct." */
  /* Get the channel according to receive SDU structure */
  channel = ptrRxNSdu->ChannelId;
  
  /* Set the frame size */
  frameSize = (ptrChannelRam->RxDl - CANTP_ONE) - bytePos;

  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))

  /* Check and store the N_Ta in local buffer */
  /* @Trace: SWS_CanTp_00283 */
  /* @Trace: SWS_CanTp_00094 */
  /* FC also contains the N_TA or N_AE value */
  if ((uint8)CANTP_ONE == bytePos)
  {
    /* @Trace: CanTp_SUD_API_218 */
    dataArray[CANTP_ZERO] = ptrRxNSdu->FcNTaOrNAeValue;
  }
  #endif /* End of if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||
          *(STD_ON == CANTP_RX_MIXED_ADDRESS)) */

  /* Store the N_PCI byte 1 in the local buffer */
  dataArray[bytePos] = ((uint8)CANTP_FC_PCI) | ptrChannelRam->FlowStatus;
  bytePos++;

  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  /* Get the pointer to STMin and BS array */
  ptrRxNSduRam = &(Variant_Select->PtrSTminBs)[ptrChannelRam->ActivePduId];
  #else
  /* Get the pointer to STMin and BS array */
  ptrRxNSduRam = &CanTp_STminBs[ptrChannelRam->ActivePduId];
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
  /* Store the Block size as N_PCI byte 2 in the local buffer */
  dataArray[bytePos] = CanTp_EstimateBS(ptrChannelRam, ptrRxNSduRam, frameSize);
  bytePos++;

  /* Store the separation Time value as N_PCI byte 3 in the local buffer */
  /* @Trace: SWS_CanTp_00067 */
  /* The CanTp shall use the same value for the BS and STmin parameters on each FC
   * sent during a segmented reception */
  /* polyspace:begin<RTE: IDP : Not a defect : Low > Its bound is pre-defined */
  dataArray[bytePos] = ptrRxNSduRam->STMin;
  /* polyspace:end<RTE: IDP : Not a defect : Low > Its bound is pre-defined */  
  bytePos++;

  #if (STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION)
  /* @Trace: SWS_CanTp_00347 */
  /* Check if the SDU is configured for PADDING ACTIVATION equal to STD_ON */
  #if (STD_ON == CANTP_RXNDSU_PADDING_ON_OFF_MIXED) 
  if (CANTP_TRUE == ptrRxNSdu->RxPaddingActivation)
  #endif
  {
    #if ((STD_ON == CANTP_RXNDSU_PADDING_ON_OFF_MIXED) || \
         (STD_ON == CANTP_RXNDSU_PADDING_ALL_ON))
    /* @Trace: CanTp_SUD_API_225 */
    CANTP_MEMCPY(&dataArray[bytePos], &CanTp_PaddingByte[(uint8)CANTP_ZERO], 
    ((size_t)CANTP_EIGHT - (size_t)bytePos));
    /* Initialize the Sdu Length as eight */
    pduInfo.SduLength = (PduLengthType)CANTP_EIGHT;
    #endif
  } /* @ end if(ptrRxNSdu->RxPaddingActivation == CANTP_TRUE) */
  #if (STD_ON == CANTP_RXNDSU_PADDING_ON_OFF_MIXED)
  else
  #endif
  {
    #if ((STD_ON == CANTP_RXNDSU_PADDING_ON_OFF_MIXED) || \
         (STD_ON == CANTP_RXNDSU_PADDING_ALL_OFF))
    /* Initialize the Sdu Length as 3 if padding activation off */
    pduInfo.SduLength = (PduLengthType)bytePos;
    #endif
  }
  #else /* End of if (STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION) */
  /* Initialize the Sdu Length as 3 if padding activation off */
  pduInfo.SduLength = (PduLengthType)bytePos;
  #endif /* End of if (STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION) */

  pduInfo.SduDataPtr = dataArray;

  /* Initiate lower layer transmit request */
  if (ptrChannelRam->FlowStatus < (uint8)CANTP_FS_OVFLW)
  {
    /* @Trace: CanTp_SUD_API_358 */
    /* polyspace +1 RTE:IDP [Not a defect :Low] "Its bound is pre-defined" */    
    narTimer = ptrRxNSduDyna->NarTimeoutValue;
 
    /* Load Nar timer based on Buffer busy state */
    if (((uint8)CANTP_ONE == ptrChannelRam->NewFrameFlag) ||
        ((uint8)CANTP_CF_PCI == ptrChannelRam->FrameType))
    {
      /* @Trace: CanTp_SUD_API_226 */
      narTimer = ptrRxNSduDyna->NarTimeoutValue + (uint16)CANTP_ONE;
    }
    /* Start N_Ar timer */
    CANTP_TIMER_UPDATE_MACRO(channel, CANTP_NAR_TIMER,
      narTimer);

    /* Update the channel state */
    ptrChannelRam->ChannelState = (uint8)CANTP_FC_TXCONF;
    ptrChannelRam->TxConfirmState = (uint8)CANTP_FC_TX_CONF;
  } /* End of if (ptrChannelRam->FlowStatus < CANTP_FS_OVFLW) */
  /* @Trace: SWS_CanTp_00342 */
  /* Terminate the reception when when CanIf_Transmit() returns E_NOT_OK */
  /* Invoke lower layer API for transmission of FC */
  /* @Trace: SWS_CanTp_00035 */
  /* NSduId shall only be linked to one CAN LSduId */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Its bound is pre-defined" */  
  if( E_OK != CanIf_Transmit(ptrRxNSduDyna->LoTxFcTargetPduId, &pduInfo))
  {
     /* @Trace: CanTp_SUD_API_227 */
     /* Terminate the current connection if CanIf_Transmit return not OK */
     CanTp_ReceptionComplete(ptrChannelRam, (CanTp_NotifResultType)E_NOT_OK);
  }
} /* End of CanTp_TransmitFc(P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR)
   * ptrChannelRam) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */

/*******************************************************************************
** Function Name        : CanTp_CopyRxFrame                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copies data to the upper layer(PduR)  **
**                        buffer either from lower layer(CanIf) buffer or     **
**                        CanTp local buffer.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrChannelRam                                       **
**                        ptrRxSrc                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_RxSduDynamic         **
**                        Function(s) invoked    : PduR_CanTpCopyRxData       **
**                                                 CanTp_TransmitFc           **
**                                                 CanTp_ReceptionComplete    **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01073 */
FUNC(void, CANTP_CODE) CanTp_CopyRxFrame(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
    CANTP_VAR) ptrChannelRam, P2VAR(uint8, AUTOMATIC, CANTP_VAR) ptrRxSrc)
{
  /* @Trace: CanTp_SUD_API_376 CanTp_SUD_DATATYPE_001 */
  P2CONST(CanTp_RxNSduDynamicType, AUTOMATIC, CANTP_CONST) ptrRxNSduDyna;
  PduInfoType rxPduInfo;
  BufReq_ReturnType lenBufferStatus;
  PduLengthType bufferSize;
  PduLengthType dataBytes;

  bufferSize = (PduLengthType)CANTP_ZERO;
  
  /* Get the current frame length to copy */
  dataBytes = (PduLengthType)ptrChannelRam->CurrentFrameLen;

  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
    /* Initialize RxNSdu dynamic structure according to RxNSduId */
    ptrRxNSduDyna = &(Variant_Select->PtrRxNSduDynamic)[ptrChannelRam->ActivePduId];
  #else
    /* Initialize RxNSdu dynamic structure according to RxNSduId */
    ptrRxNSduDyna = &CanTp_RxSduDynamic[ptrChannelRam->ActivePduId];
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  /* Set the flow status as CTS */
  /* @Trace: SWS_CanTp_00277 */
  /* With regard to FF N-PDU reception, the content of the Flow Control
   * N-PDU depends on the PduR_CanTpStartOfReception() service result */
  ptrChannelRam->FlowStatus = (uint8)CANTP_FS_CTS;
  
  /* Copy the data from lower layer to upper layer buffer */
  /* @Trace: SWS_CanTp_00116 */
  /* In both padding and no padding modes,
   * the CanTp module shall only transfer used data bytes to
   * the upper layer. */
  /* @Trace: SWS_CanTp_00269 */
  /* Call the PduR_CanTpCopyRxData() function after reception of CF */
  rxPduInfo.SduDataPtr = ptrRxSrc;
  rxPduInfo.SduLength = dataBytes;
  
  /* polyspace +1 RTE:IDP [Not a defect:Low] "The pointer ptrRxNSduDyna->UpTargetPduId can not outside its bounds because the variable UpTargetPduId is declared with uint16 but User shall not config the large number. So, this warning not impact." */
  lenBufferStatus = PduR_CanTpCopyRxData(ptrRxNSduDyna->UpTargetPduId,
    &rxPduInfo, &bufferSize);

  if (BUFREQ_OK == lenBufferStatus)
  {
    /* @Trace: CanTp_SUD_API_228 */
    /* polyspace:begin<RTE: NIV : Not a defect : Low > initialized variable */
    /* Update the available upperlayer buffer length */
    ptrChannelRam->AvlBuffLength = (uint32)bufferSize;

    /* Decrement the byte counter */
    ptrChannelRam->ByteCounter =
      ptrChannelRam->ByteCounter - (uint32)dataBytes;
    /* polyspace:end<RTE: NIV : Not a defect : Low > initialized variable */

    /* Check if enough buffer is available after receiving last CF in a Block
     * Or FF to start one reception.
     */
    #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
    /* @Trace: SWS_CanTp_00278 */
    /* It is important to note that FC N-PDU will only be sent after every block,
     *  composed of a number BS (Block Size) of consecutive frames */
    if (((uint8)CANTP_ZERO == ptrChannelRam->BSVar)
        && (ptrChannelRam->ByteCounter != (uint32)CANTP_ZERO))
    {
      /* @Trace: CanTp_SUD_API_229 */
      /* Check buffer available enough to next the next block */
      if (( bufferSize >= (uint32)(ptrChannelRam->CurrentFrameLen))
          || ((uint32)bufferSize >= ptrChannelRam->ByteCounter))
      {
        /* @Trace: CanTp_SUD_API_230 */
        /* Update the channel status */
        ptrChannelRam->FlowStatus = (uint8)CANTP_FS_CTS;
        /* Transmit the flow control frame */
        CanTp_TransmitFc(ptrChannelRam);
      } /* End of if ((bufferSize >= ptrChannelRam->CurrentFrameLen) */
      else
      {
        /* @Trace: CanTp_SUD_API_231 */
        /* @Trace: SWS_CanTp_00325 */
    	  /* The function PduR_CanTpCopyRxData() return BUFREQ_OK,
         * but the remaining buffer is not sufficient for the reception of the next block,
         * the CanTp module shall start the timer N_Br */
        /* N_Br already started.
         * Update the buffer state to indicate waiting for receive buffer
         * */
        ptrChannelRam->BufferState = (uint8)CANTP_RX_NOTRDY_INITREQ;
      }
    } /* @ end if((ptrChannelRam->BSVar == CANTP_ZERO)... */

    #endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */
  } /* @ end if(lenBufferStatus == BUFREQ_OK) */
  else /*Check if the buffer is NOT_OK*/
  {
    /* @Trace: CanTp_SUD_API_232 */
    /* Update the Tp Buffer status */
    ptrChannelRam->BufferState = (uint8)CANTP_RX_NOTRDY;

    /* @Trace: SWS_CanTp_00271 */
    /* Invoke upper layer Rx Indication to abort the reception of this N-SDU and
     * notify the PduR module by calling the PduR_CanTpRxIndication() with the result E_NOT_OK */
    CanTp_ReceptionComplete(ptrChannelRam, (CanTp_NotifResultType)E_NOT_OK);
  } /* @ else if(lenBufferStatus == BUFREQ_E_NOT_OK) */
} /* End of CanTp_CopyRxFrame(P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR)
   * ptrChannelRam, P2VAR(uint8, AUTOMATIC, CANTP_VAR) ptrRxSrc) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_RequestRxBuffer                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function requests upper Layer for Rx buffer    **
**                        and also handles the request results provided by    **
**                        upper layer                                         **
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
** Remarks              : Global Variable(s)     : CanTp_RxSduStatic,      **
**                                                 CanTp_GaaTimers            **
**                CANTP_CHANNEL_ID    **
**                        Function(s) invoked    : PduR_CanTpCopyRxData       **
**                                                 CanTp_TransmitFc           **
**                                                 CanTp_ReceptionComplete    **
**                                                 PduR_CanTpStartOfReception **
*******************************************************************************/
/* @Trace: SRS_Can_01081 */
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_RequestRxBuffer(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
    CANTP_VAR) ptrChannelRam)
{
  P2CONST(CanTp_RxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrRxNSdu = NULL_PTR;
  P2CONST(CanTp_RxNSduDynamicType, AUTOMATIC, CANTP_CONST) ptrRxNSduDyna;
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) ptrRxSrc;

  /* @Trace: CanTp_SUD_DATATYPE_001 */
  BufReq_ReturnType lenBufferStatus;
  PduLengthType bufferSize;
  PduIdType activeSduId;
  CanTp_ChannelType channel;
  uint16 nbrTimer;
  uint8 frameType;

  bufferSize = (PduLengthType)CANTP_ZERO;

  /* Initialize the source pointer */
  ptrRxSrc = ptrChannelRam->ptrUpLayerBuff;

  /* Update the Tp Buffer status */
  ptrChannelRam->BufferState = (uint8)CANTP_RX_NOTRDY_INITREQ;

  /* Get the frame type */
  frameType = ptrChannelRam->FrameType;

  /*Get the SduId */
  activeSduId = ptrChannelRam->ActivePduId;

  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)

  /* Get the static RxNSdu structure Pointer */
  ptrRxNSdu = &(Variant_Select->PtrRxNSduStatic)[activeSduId];

  /* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */

  ptrRxNSduDyna = &(Variant_Select->PtrRxNSduDynamic)[activeSduId];
  #else
  /* Get the static RxNSdu structure Pointer */
  ptrRxNSdu = &CanTp_RxSduStatic[activeSduId];

  /* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */

  ptrRxNSduDyna = &CanTp_RxSduDynamic[activeSduId];
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  /* polyspace +2 RTE:IDP [Not a defect:Low] "The pointer ptrRxNSdu->ChannelId can outsite its bounds with declare varible ChannelId is uint8 then maximum the number of ChannelId is 255. However, User shall not config over many Channel to outside its bounds. This warning not imapct." */
  /* Get the channel according to receive SDU structure */
  channel = ptrRxNSdu->ChannelId;

  /* @Trace: SWS_CanTp_00166 */
  /* @Trace: CanTp_SUD_API_377 */
  /* Start time-out N_Br before calling PduR_CanTpStartOfReception or PduR_CanTpCopyRxData */
  /* Start N_Br reception one FF, last CF or request buffer for next block */
  SchM_Enter_CanTp_TIMER_PROTECTION();
  nbrTimer = CanTp_Timers[channel][CANTP_NBR_TIMER];
  /* polyspace:begin<RTE: IDP : Not a defect : Low > Its bound is pre-defined  */
  /* Check if N_Br Timer is not started */
  if ((uint16)CANTP_ZERO == nbrTimer)
  {
    /* @Trace: CanTp_SUD_API_233 */
    /* Start N_Br timer */
    nbrTimer = ptrRxNSduDyna->NbrTimeoutValue;
  }
  /* polyspace:end<RTE: IDP : Not a defect : Low > Its bound is pre-defined */  
  /* Update the Nbr timer value */
  CANTP_TIMER_UPDATE_MACRO(channel, CANTP_NBR_TIMER, nbrTimer);
  SchM_Exit_CanTp_TIMER_PROTECTION();

  lenBufferStatus = CanTp_CheckRxBuffer(ptrChannelRam, &bufferSize);

  /* Check if the buffer is ready */
  /* @Trace: SWS_CanTp_00277 */
  /* With regard to FF N-PDU reception, the content of the Flow Control
   * N-PDU depends on the PduR_CanTpStartOfReception() service result */
  if (BUFREQ_OK == lenBufferStatus)
  {
    /* @Trace: CanTp_SUD_API_241 */
    /* polyspace:begin<RTE: NIV : Not a defect : Low > initialized variable */
    /* Copy the PDU router buffer length to global variable */
    ptrChannelRam->AvlBuffLength = (uint32)bufferSize;
    /* polyspace:end<RTE: NIV : Not a defect : Low > initialized variable */
    /*  */
    /* If buffer available for next block */
    if (ptrChannelRam->AvlBuffLength >=    \
            (uint32)ptrChannelRam->CurrentFrameLen)
    {
      /* @Trace: CanTp_SUD_API_242 */
      /* Stop N_Br timer */
      nbrTimer = (uint16)CANTP_ZERO;
    }
    CanTp_RxPduBufferChk(ptrChannelRam, ptrRxSrc);
  }
     /* Check if the buffer is overflow
     */
  else if (BUFREQ_E_OVFL == lenBufferStatus)
  {
    /* @Trace: CanTp_SUD_API_244 */
    /* Only sending the FC if request is FF */
    if ((uint8)CANTP_FF_PCI == frameType)
    {
      /* @Trace: CanTp_SUD_API_243 */
      /* @Trace: SWS_CanTp_00318 */
      /* Send FC(OVFLW) after reception of FF */
      #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
      ptrChannelRam->FlowStatus = (uint8)CANTP_FS_OVFLW;

      /* Update the Tp Buffer status */
      ptrChannelRam->BufferState = (uint8)CANTP_RX_NOTRDY;

      if (ptrChannelRam->TxConfirmState == CANTP_TX_CONF_IDLE)
      {
        /* @Trace: CanTp_SUD_API_245 */
        /*Invoke lower layer Tx API */
        /* @Trace: SWS_CanTp_00064 */
        /* When receiving a FF N-PDU, the Flow Control shall only be sent after
        * having the result of the PduR_CanTpStartOfReception() service */
        CanTp_TransmitFc(ptrChannelRam);
      }
      #endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */
    }
    /* @Trace: SWS_CanTp_00353 */
    /* Abort reception of a SF */
    /* Invoke upper layer Rx Indication to abort the reception of this N-SDU */
    CanTp_ReceptionComplete(ptrChannelRam, (CanTp_NotifResultType)E_NOT_OK);
  } /*
     * else if(lenBufferStatus == BUFREQ_E_OVFL)
     * Check if the buffer is E_NOT_OK
     */
  else
  {
    /* check if the buffer is requested for FF or SF */
    if ((uint8)CANTP_ONE == ptrChannelRam->NewFrameFlag)
    {
      /* @Trace: CanTp_SUD_API_246 */
      /* @Trace: SWS_CanTp_00081 */
      /* Abort a reception of FF or SF when BUFREQ_E_NOT_OK */
      /* Update the Tp Buffer status */
      ptrChannelRam->BufferState = (uint8)CANTP_RX_NOTRDY;

      /* Initialize the channel state to IDLE (i.e. TxWait and RxWait) */
      ptrChannelRam->ChannelState = (uint8)CANTP_WAIT;

      /* Reset Tx Confirmation state to IDLE */
      ptrChannelRam->TxConfirmState = (uint8)CANTP_TX_CONF_IDLE;

      /* Clear ByteCounter */
      ptrChannelRam->ByteCounter = (uint32)CANTP_ZERO;
      /* Reset all Rx timers */
      CANTP_STOP_ALL_RX_TIMERS(ptrRxNSdu->ChannelId);
    } 
    /* The buffer is requested for CF */
    else
    {
      ptrChannelRam->BufferState = (uint8)CANTP_RX_NOTRDY;
      /* @Trace: SWS_CanTp_00271 */
      /* Invoke upper layer Rx Indication to abort the reception of this N-SDU */
      CanTp_ReceptionComplete(ptrChannelRam, (CanTp_NotifResultType)E_NOT_OK);
    }
  } /* @ else if(lenBufferStatus == BUFREQ_E_NOT_OK) */

  if (((uint32)CANTP_ZERO == ptrChannelRam->ByteCounter) &&
      (ptrChannelRam->ChannelState != (uint8)CANTP_WAIT))
  {
    /* @Trace: CanTp_SUD_API_247 */
    /* Update the Tp Buffer status */
    ptrChannelRam->BufferState = (uint8)CANTP_RX_NOTRDY;

    /* Invoke upper layer Rx Indication */
    CanTp_ReceptionComplete(ptrChannelRam, (CanTp_NotifResultType)E_OK);
  } /* End of if ((ptrChannelRam->ByteCounter == CANTP_ZERO) && */
  /* @Trace: SWS_CanTp_00325 */
  /* The function PduR_CanTpCopyRxData() called after reception of the last Consecutive Frame,
   * start time-out N_Br when available buffer is smaller than needed for next block */
  /* @Trace: SWS_CanTp_00082 */
  /* The reception of a First Frame, if the function PduR_CanTpStartOfReception() returns BUFREQ_OK,
   * start time-out N_Br when available buffer is smaller than needed for next block */
  CANTP_TIMER_UPDATE_MACRO(channel, CANTP_NBR_TIMER, nbrTimer);
} /* End of CanTp_RequestRxBuffer(P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR)
   * ptrChannelRam) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_RxPduBufferChk                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function Check if the buffer given by PDU      **
**                        router is enough to store the complete receive      **
**                        data or atleast current frame length of received    **
**                        data.                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrChannelRam                                        **
**                        ptrRxSrc                                          **
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
**                        Function(s) invoked    : CanTp_CopyRxFrame          **
**                                                 CanTp_TransmitFc           **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_RxPduBufferChk(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
    CANTP_VAR) ptrChannelRam, P2VAR(uint8, AUTOMATIC, CANTP_CONST) ptrRxSrc)
{
  P2VAR(uint8, AUTOMATIC, CANTP_CONST) ptrRxSrcLc;
  ptrRxSrcLc = ptrRxSrc;
  /* Check if the buffer given by PDU router is enough to store the
   * complete receive data or at least current frame length of received data
   */
  if (ptrChannelRam->AvlBuffLength >=
      (uint16)(ptrChannelRam->CurrentFrameLen))
  {
    /* @Trace: CanTp_SUD_API_248 */
    /* Check if any local data bytes are available */
    if (ptrChannelRam->LocalDataByteIndex > (uint8)CANTP_ZERO)
    {
      /* @Trace: CanTp_SUD_API_249 */
      /* Update no local data available by next time */
      ptrChannelRam->LocalDataByteIndex = (uint8)CANTP_ZERO;

      /* Get the address of CanTp local data */
      ptrRxSrcLc = &ptrChannelRam->DataBuffer[CANTP_ZERO];
    } /* End of if (ptrChannelRam->LocalDataByteIndex > CANTP_ZERO) */

    /* Update the flow status for not a new frame */
    ptrChannelRam->NewFrameFlag = (uint8)CANTP_ZERO;

    /* Update the Tp Buffer status */
    ptrChannelRam->BufferState = (uint8)CANTP_RX_NOTRDY;

    /*Invoke copy Rx Frame if only SF or FF or Start of new block*/
    if (ptrChannelRam->FrameType != (uint8)CANTP_CF_PCI)
    {
      /* @Trace: CanTp_SUD_API_250 */
      /* Copy the received frame into upper layer */
      CanTp_CopyRxFrame(ptrChannelRam, ptrRxSrcLc);
    }
    else
    {
      /* @Trace: CanTp_SUD_API_251 */
      #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)

      /* Update the channel status */
      ptrChannelRam->FlowStatus = (uint8)CANTP_FS_CTS;

      /* Transmit FC if Tx confirmation is not awaited
       *   for previous Transmission*/
      if ((uint8)CANTP_TX_CONF_IDLE == ptrChannelRam->TxConfirmState)
      {
        /* @Trace: CanTp_SUD_API_252 */
        /* Transmit the flow control frame */
        CanTp_TransmitFc(ptrChannelRam);
      }
      #endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */
    } /* End of else */
  } /* if((ptrChannelRam->AvlBuffLength >= ptrChannelRam->ByteCounter)*/
  else
  {
    if ((uint8)CANTP_ONE == ptrChannelRam->NewFrameFlag)
    {
      /* @Trace: CanTp_SUD_API_254 */
      /* @Trace: SWS_CanTp_00082 */
      /* Smaller avaible buffer size than needed for the next block */
      /* @Trace: SWS_CanTp_00339 */
      /* The returns buffer is BUFREQ_OK with a smaller available buffer size
      * than needed for the already received data.
      * The CanTp module shall abort the reception */
      CanTp_ReceptionComplete(ptrChannelRam,
                               (CanTp_NotifResultType)E_NOT_OK);
    }
  } /* Available buffer length is not enough to copy the received frame  */
} /* End of CanTp_RxPduBufferChk(P2VAR(CanTp_ChannelRamType, AUTOMATIC, */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_RxCfDlcCheck                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs the data length checks on    **
**                        consecutive frames                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrRxNSdu                                           **
**                        receivedDlc                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : dlcErrorFlag                                        **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_ChannelRam           **
**                                                 CanTp_BytePos              **
**                                                 CANTP_CHANNEL_ID           **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01073 */
FUNC(boolean, CANTP_CODE) CanTp_RxCfDlcCheck(P2CONST(CanTp_RxNsduStaticType,
    AUTOMATIC, CANTP_CONST) ptrRxNSdu, uint8 receivedDlc)
{
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  uint32 byteCounter;
  uint8 bytePos;
  uint8 rxDlMax;
  uint8 frameLength;
  boolean dlcErrorFlag;

  /* Initialise the Default value as No Datalength error */
  dlcErrorFlag = CANTP_FALSE;
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))

  /* Get the N_PCI position if transmit NSDU is configured as Extended */
  bytePos = CanTp_BytePos[ptrRxNSdu->AddressingMode];
  #else

  /* Initialise the Addressing format value as Standard */
  bytePos = (uint8)CANTP_ZERO;
  #endif

  /* Get the channel according to receive SDU structure */
  ptrChannelRam = &CanTp_ChannelRxRam[ptrRxNSdu->ChannelId];

  /* polyspace:begin<RTE: IDP : Not a defect : Low > Its bound is pre-defined */
  /* Assign value RxDL to local variable */
  rxDlMax = ptrChannelRam->RxDl;
  /* polyspace:end<RTE: IDP : Not a defect : Low > Its bound is pre-defined */ 	
  /* Calculate posible data len of CFs */
  frameLength = rxDlMax - (uint8)CANTP_ONE - bytePos;

  /* Get the remaining bytes */
  byteCounter = ptrChannelRam->ByteCounter;

  /* @Trace: SWS_CanTp_00344 */
  /* @Trace: CanTp_SUD_API_368 */
  /* CanTp shall only accept SF or last CF Rx N-PDUs with a length of eight bytes */
  /* If Padding is on, DLC 2...7 must be padded to DLC 8
   * and also for small CAN_FD (len = 8) */
  #if(CANTP_RX_SDU_PADDING_ACTIVATION == STD_ON)
  if((ptrRxNSdu->RxPaddingActivation == CANTP_TRUE) && (receivedDlc < CANTP_EIGHT))
  {
    /* @Trace: CanTp_SUD_API_255 */
    dlcErrorFlag = CANTP_TRUE;
  }
  #endif
    
  #if (CANTP_FD_SUPPORT == STD_ON)
  if (CANTP_FALSE == dlcErrorFlag)
  {
    /* @Trace: CanTp_SUD_API_256 */
    /* Check if the consecutive frame is not the last consecutive frame and
     * frame length is less than the configured frame */
    if ((byteCounter > (uint32)frameLength) &&
        (receivedDlc != rxDlMax))
    {
      /* @Trace: CanTp_SUD_API_257 */
      dlcErrorFlag = CANTP_TRUE;
    }
    else
    {
      bytePos++;
      /* Except for last CF, CF must be matched with RX_DL */
      if (byteCounter <= ((uint32)rxDlMax - (uint32)bytePos))
      {
        /* Check the DLC of last CF PDU */
        if ((uint32)receivedDlc < ((byteCounter) + (uint32)bytePos))
        {
          /* @Trace: CanTp_SUD_API_260 */
          dlcErrorFlag = CANTP_TRUE;
        }
        else
        {
          /* @Trace: CanTp_SUD_API_261 */
          frameLength = (uint8)(byteCounter);
        }
      }
    }
  }
  else
  #endif /* End of  #if (CANTP_FD_SUPPORT == STD_ON) */
  {
    /* @Trace: CanTp_SUD_API_262 */
    /* Check if the consecutive frame is not the last consecutive frame and
     * frame length is less than the configured frame */
    if ((byteCounter > (uint32)frameLength) &&
        ((uint8)CANTP_EIGHT > receivedDlc))
    {
      /* @Trace: CanTp_SUD_API_263 */
      dlcErrorFlag = CANTP_TRUE;
    }
    else
    {
      bytePos++;
      /* @Trace: CanTp_SUD_API_265 */
      if (byteCounter <= (((uint32)CANTP_EIGHT) - (uint32)bytePos))
      {
        /* Check the DLC of last CF PDU */
        if ((uint32)receivedDlc < ((byteCounter) + (uint32)bytePos))
        {
          /* @Trace: CanTp_SUD_API_266 */
          dlcErrorFlag = CANTP_TRUE;
        }
        else
        {
          /* @Trace: CanTp_SUD_API_267 */
          frameLength = (uint8)(byteCounter);
        }
       }
     }
  }
  ptrChannelRam->CurrentFrameLen = frameLength;

  return (dlcErrorFlag);
} /* End of CanTp_RxCfDlcCheck(uint8 receivedDlc) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_RxNewframeDlcCheck                            **
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
** Input Parameters     : ptrRxNSdu                                           **
**                        receivedDlc                                         **
**                        ptrSrc                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : dlcErrorFlag                                        **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_ChannelRam           **
**                                                 CanTp_BytePos              **
**                                                 CANTP_CHANNEL_ID           **
**                        Function(s) invoked    : Det_ReportError            **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01073 SWP_CP_SRS_UDS_0064 */
FUNC(boolean, CANTP_CODE) CanTp_RxNewframeDlcCheck(P2CONST(CanTp_RxNsduStaticType,
  AUTOMATIC, CANTP_CONST) ptrRxNSdu, P2CONST(uint8, AUTOMATIC, CANTP_CONST)
  ptrSrc, uint8 receivedDlc)
{
  /* @Trace: CanTp_SUD_API_268 */
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  PduLengthType sduLength;
  uint8 bytePos;
  uint8 pci;
  uint8 pciByte;
  boolean dlcErrorFlag;

  /* Initialise the SduLength to Zero */
  sduLength = (PduLengthType)CANTP_ZERO;
  /* Initialise value*/
  dlcErrorFlag = CANTP_FALSE;
  /* Get the channel according to receive SDU structure */
  ptrChannelRam = &CanTp_ChannelRxRam[ptrRxNSdu->ChannelId];

  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))
  /* Get the N_PCI position if transmit NSDU is configured as Extended */
  bytePos = CanTp_BytePos[ptrRxNSdu->AddressingMode];
  #else
  /* Initialise the Addressing format value as Standard */
  bytePos = (uint8)CANTP_ZERO;
  #endif
  /* polyspace +2 RTE:NIV [Not a defect:Low] "The value of ptrSrc has been gotten from PDU, no impact" */
  /* Get the N_PCI byte */
  pciByte = *ptrSrc;

  /* Decode the N_PCI byte for PCI information */
  pci = (uint8)(pciByte & (uint8)CANTP_PCI_MASK);
  /* */
  #if (STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION)
  /* @Trace: SWS_CanTp_00344 */
  /* CanTp shall only accept SF or last CF Rx N-PDUs with a length of eight bytes */
  if((ptrRxNSdu->RxPaddingActivation == CANTP_TRUE) &&
     (receivedDlc < (uint8)CANTP_EIGHT))
  {
    /* @Trace: CanTp_SUD_API_369 */
    dlcErrorFlag = CANTP_TRUE;
  }
  #endif /* End of (STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION) */
  /* @Trace: SWS_CanTp_00351 */
  /* The padding of CAN frame data is mandatory for DLC values greater than eight */
  if (CANTP_FALSE == dlcErrorFlag)
  {
    /* @Trace: CanTp_SUD_API_274 */
    /* In case of Single Frame */
    if ((uint8)CANTP_SF_PCI == pci)
    {
      dlcErrorFlag |= CanTp_RxNewframeDlcCheckSingleframe(ptrRxNSdu, ptrSrc, 
                                                          &sduLength, receivedDlc);
    } /* if(pci == CANTP_SF_PCI) */
    /* In case of First Frame */
    else
    {
      dlcErrorFlag |= CanTp_RxNewframeDlcCheckfirstframe(ptrRxNSdu, ptrSrc, &sduLength, receivedDlc);
    } /* End of In case of First Frame */
    
    if (CANTP_FALSE == dlcErrorFlag)
    {
      /* @Trace: CanTp_SUD_API_294 */
      /* Store the decoded data length into global variable */
      ptrChannelRam->ByteCounter = (uint32)sduLength;
      ptrChannelRam->SduLength = sduLength;

      /* Update the current addressing */
      ptrChannelRam->CurrentBytePosition = bytePos;
    } /* @ if(dlcErrorFlag == CANTP_FALSE) */
  } /* @ if(dlcErrorFlag == CANTP_FALSE) */

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  /* @Trace: SWS_CanTp_00345 */
  /* Reception of an SF Rx N-PDU belonging to that N-SDU, with a length smaller than eight bytes */
  if (CANTP_TRUE == dlcErrorFlag)
  {
    /* @Trace: CanTp_SUD_API_295 */
    /* Report to DET */
    (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_RXINDICATION_SID, CANTP_E_PADDING);
  }
  #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  return (dlcErrorFlag);
} /* End of CanTp_RxNewframeDlcCheck(P2CONST(CanTp_RxNsduStaticType, AUTOMATIC,
   * CANTP_CONST) ptrRxNSdu, P2CONST(uint8, AUTOMATIC, CANTP_CONST) ptrSrc,
   * uint8 receivedDlc) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_RxBinarySearch                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs the binary search to find    **
**                        the Sdu for extended addressing modes               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : firstSduMap                                         **
**                        size                                                **
**                        rxNsa                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ptrsduMap                                           **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS)\
  || (STD_ON == CANTP_TX_MIXED_ADDRESS)||(STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS)||(STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
  (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC_P2CONST(CanTp_RxNSaOrNAeSduMappingType, AUTOMATIC, CANTP_CODE) 
    CanTp_RxBinarySearch(P2CONST(CanTp_RxNSaOrNAeSduMappingType,
    AUTOMATIC, CANTP_CONST) firstSduMap, uint8 size, uint8 rxNsa)
{
  /* @Trace: CanTp_SUD_API_296 */
  P2CONST(CanTp_RxNSaOrNAeSduMappingType, AUTOMATIC, CANTP_CONST) ptrsduMap;
  uint8 tpCurrNSaOrNAe;
  uint8 low;
  uint8 high;
  uint8 mid;

  /* Initialize high variable with number of Rx Sdus associated to the Pdu */
  high = size - (uint8)CANTP_ONE;

  /* Initialize low variable with one */
  low = CANTP_ONE;

  /* Initialize return value with null pointer */
  ptrsduMap = NULL_PTR;

  /* Get the lower limit of Nsa */
  tpCurrNSaOrNAe = firstSduMap->RxNTaOrNAe;

  /* Check whether search Nsa is in range */
  if ((rxNsa >= tpCurrNSaOrNAe) &&
      (rxNsa <= (firstSduMap[high].RxNTaOrNAe)))
  {
    /* @Trace: CanTp_SUD_API_297 */
    /* Check whether requested Nsa is same as first Nsa of the list */
    if (rxNsa != tpCurrNSaOrNAe)
    {
      do
      {
        /* Get the middle index number */
        mid = (high + low) >> (uint8)CANTP_ONE;

        /* Get the Nsa of the mid Tp Rx PDU */
        tpCurrNSaOrNAe = (firstSduMap[mid].RxNTaOrNAe);

        /* Compare Nsa with the requested one */
        if (tpCurrNSaOrNAe == rxNsa)
        {
          /* @Trace: CanTp_SUD_API_298 */
          /* Update the return pointer with the Rx SDU mapping structure */
          ptrsduMap = (&firstSduMap[mid]);

          /* Set high to zero to break the loop */
          high = (uint8)CANTP_ZERO;
        } /* End of if (tpCurrNSaOrNAe == rxNsa) */
        else
        {
          /* Compare the Nsa with the requested one */
          if (rxNsa < tpCurrNSaOrNAe)
          {
            /* @Trace: CanTp_SUD_API_299 */
            /* If the received Nsa is lower, update high */
            high = mid - (uint8)CANTP_ONE;
          } 
          else
          {
            /* @Trace: CanTp_SUD_API_300 */
            /* If the received Nsa is higher, update low */
            low = mid + (uint8)CANTP_ONE;
          }
        } /* @ end if (tpCurrNSaOrNAe == rxNsa) */
      } while (low <= high);
    } /* if(rxNsa != tpCurrNSaOrNAe) */
    else
    {
      /* @Trace: CanTp_SUD_API_301 */
      /* Update the return pointer with the actual Sdu mapping structure */
      ptrsduMap = firstSduMap;
    }
  } /*
     * if((rxNsa >= tpCurrNSaOrNAe) &&...
     * Return Sdu mapping pointer
     */
  return (ptrsduMap);
} /* End of CanTp_RxBinarySearch(P2CONST(CanTp_RxNSaOrNAeSduMapping, AUTOMATIC,
   * CANTP_CONST) */
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||
        *(STD_ON == CANTP_RX_MIXED_ADDRESS)) || ((CANTP_TX_EXTENDED_ADDRESS ==
        * STD_ON) || (STD_ON == CANTP_TX_MIXED_ADDRESS))) */
/*******************************************************************************
** Function Name        : CanTp_RxSpecificBinarySearch                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs the binary search to find    **
**                        the Sdu for normal fixed or mixed 29bit             **
**                        addressing modes                                    **
**                        Gen-tool have to order the RxN_Sa smaller fist      **
**                        and put same RxN_Sa closely.                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrFirstSduMap                                      **
**                        size                                                **
**                        addresMode                                          **
**                        RxNSa                                               **
**                        RxNTa                                               **
**                        RxNAe                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ptrsduMap                                           **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#ifdef CANTP_DYNID_SUPPORT
#if((STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) ||\
(STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
(STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) ||\
(STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(P2CONST(CanTp_RxNSaOrNAeSduMappingType, AUTOMATIC,
        CANTP_CONST), CANTP_CODE) CanTp_RxSpecificBinarySearch(P2CONST(
        CanTp_RxNSaOrNAeSduMappingType, AUTOMATIC, CANTP_CONST)
        ptrFirstSduMap, uint8 size, uint8 addresMode,
        uint8 RxNSa, uint8 RxNTa, uint8 RxNAe)
{
  /* @Trace: CanTp_SUD_API_302 */
  P2CONST(CanTp_RxNSaOrNAeSduMappingType, AUTOMATIC, CANTP_CONST) ptrsduMap;
  uint8 tpCurrNSa;
  uint8 tpCurrNTa;
  #if (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS)
  uint8 tpCurrNAe;
  #endif
  uint8 sduIdex;

  /* Initialize high variable with number of Rx Sdus associated to the Pdu */
  sduIdex = (uint8)CANTP_ZERO;

  /* Initialize return value with null pointer */
  ptrsduMap = NULL_PTR;

  do
  {
    tpCurrNSa = (ptrFirstSduMap + sduIdex)->RxNSa;
    tpCurrNTa = (ptrFirstSduMap + sduIdex)->RxNTa;

    if (tpCurrNTa == RxNTa)
    {
      /* @Trace: CanTp_SUD_API_303 */
      if (tpCurrNSa == RxNSa)
      {
        /* @Trace: CanTp_SUD_API_304 */
        #if (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS)
        if (CANTP_MIXED29BIT_ADDRESS == addresMode)
        {
          tpCurrNAe = (ptrFirstSduMap + sduIdex)->RxNTaOrNAe;

          if (tpCurrNAe == RxNAe)
          {
        	/* @Trace: CanTp_SUD_API_305 */
        	ptrsduMap = (ptrFirstSduMap + sduIdex);

            sduIdex = (uint8)size;
          }
          else
          {
        	/* @Trace: CanTp_SUD_API_306 */
        	sduIdex++;
          }
        }
        else
        {
          /* @Trace: CanTp_SUD_API_307 */
          ptrsduMap = (ptrFirstSduMap + sduIdex);

          sduIdex = (uint8)size;
        }
        #else
        ptrsduMap = (ptrFirstSduMap + sduIdex);

        sduIdex = (uint8)size;

        CANTP_UNUSED(addresMode);
        CANTP_UNUSED(RxNAe);
        #endif
      }
      else
      {
        /* @Trace: CanTp_SUD_API_308 */
        sduIdex++;
      }
    }
    else
    {
      /* @Trace: CanTp_SUD_API_309 */
      sduIdex++;
    }
  }while (sduIdex < size);
  return (ptrsduMap);
}
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /*#if((STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) ||\
(STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
(STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) ||\
(STD_ON == CANTP_RX_MIXED29BIT_ADDRESS)) */
#endif /* Dynamic Id support */

/*******************************************************************************
** Function Name        : CanTp_RxNewframeDlcCheckSingleframe                 **
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
** Input Parameters     : ptrRxNSdu                                           **
**                        ptrSrc                                              **
**                        sduLength                                           **
**                        receivedDlc                                         **
**                                                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : dlcErrorFlag                                        **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SWP_CP_SRS_UDS_0068 SWP_CP_SRS_UDS_0069 SWP_CP_SRS_UDS_0070 SWP_CP_SRS_UDS_0071 SWP_CP_SRS_UDS_0072 */
FUNC(boolean, CANTP_CODE) CanTp_RxNewframeDlcCheckSingleframe(
  P2CONST(CanTp_RxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrRxNSdu,
  P2CONST(uint8, AUTOMATIC, CANTP_CONST) ptrSrc, 
  P2VAR(PduLengthType, AUTOMATIC, CANIF_VAR) sduLength,
  uint8 receivedDlc)
{
  
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  /* Get the channel according to receive SDU structure */
  ptrChannelRam = &CanTp_ChannelRxRam[ptrRxNSdu->ChannelId];
  uint8 bytePos;
  uint8 pciByte;
  boolean dlcErrorFlag;

  #if(CANTP_FD_SUPPORT == STD_ON)
  uint8 iteration;
  PduLengthType prevDiscreteLen;
  PduLengthType discreteLen;
  uint8 flagLoop;

  /* Initialise the prevDiscreteLen to Zero*/
  prevDiscreteLen = (PduLengthType)CANTP_ZERO;

  /* Initialise the discreteLen to Zero */
  discreteLen = (PduLengthType)CANTP_ZERO;
  #endif
  /* polyspace +2 RTE:NIV [Not a defect:Low] "The value of ptrSrc has been gotten from the PDU, no impact" */
  /* Get the N_PCI byte */
  pciByte = *ptrSrc;

  dlcErrorFlag = CANTP_FALSE;

  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))
  /* Get the N_PCI position if transmit NSDU is configured as Extended */
  bytePos = CanTp_BytePos[ptrRxNSdu->AddressingMode];
  #else
  /* Initialise the Addressing format value as Standard */
  bytePos = (uint8)CANTP_ZERO;
  #endif

  #if (CANTP_FD_SUPPORT == STD_ON) 
  /* In case CAN_DL <= 8 */
  if(receivedDlc <= 8)
  {
    /* @Trace: CanTp_SUD_API_275 */
    *sduLength = (PduLengthType)pciByte;
    ptrChannelRam->CurrentFrameLen = (uint8)*sduLength;
    
    /* 1. Check if SF_DL exceeds CAN_DL-1(normal add.) or CAN_DL-2(mixed/extended add.) */
    if(receivedDlc < ((uint8)*sduLength + bytePos + (uint8)CANTP_ONE))
    {
      /* @Trace: CanTp_SUD_API_276 */
      dlcErrorFlag = CANTP_TRUE;
    }
    #if (STD_OFF == CANTP_RX_SDU_PADDING_ACTIVATION)
    /*Redmine #19445*/
    /* 2. Check SF_DL and CAN_DL are matched, only for enable PAdding */
    else if (!(receivedDlc == ((uint8)*sduLength + bytePos + (uint8)CANTP_ONE)))
    {
      /* @Trace: CanTp_SUD_API_277 */  
      dlcErrorFlag = CANTP_TRUE;
    }
    #endif /* End of #if (STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION) */
    /* 3. Check if SF_DL is 0 */
    else if(*sduLength == (PduLengthType)CANTP_ZERO)
    {
      /* @Trace: CanTp_SUD_API_278 */  
      dlcErrorFlag = CANTP_TRUE;
    }
    else
    {
      /* Do Nothing */
    }
  }
  /* In case CAN_DL > 8*/
  /* @Trace: SWS_CanTp_00351 */
  /* The padding of CAN frame data is mandatory for DLC values greater than eight *
   * FD Padding Byte Check - DLC 9..15: Check Mandatory Padding */
  else
  {
    /* @Trace: CanTp_SUD_API_279 */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "The value of ptrSrc has been gotten from the PDU, no impact" */
    *sduLength = (PduLengthType)ptrSrc[CANTP_ONE];
    ptrChannelRam->CurrentFrameLen = (uint8)*sduLength;

    /* @Trace: CanTp_SUD_API_270 */
    dlcErrorFlag = CANTP_TRUE;
    flagLoop = CANTP_ZERO;
    /* polyspace-begin RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined " */
    for(iteration = 0 ; (iteration < CANTP_SEVEN) && (flagLoop == CANTP_FALSE) ; iteration ++)
    {
      if(receivedDlc == CanTp_DiscreteDlcDataLength[iteration])
      {
        dlcErrorFlag = CANTP_FALSE;
        ptrChannelRam->DecreteIndex = iteration;
        discreteLen = CanTp_DiscreteDlcDataLength[ptrChannelRam->DecreteIndex];

        /* When Discrete Length is '12', assign Previous Discrete Length '9'*/
        if(iteration == CANTP_ZERO)
        {
          /* @Trace: CanTp_SUD_API_271 */
          prevDiscreteLen = CANTP_NINE;
        }
        else
        {
          /* @Trace: CanTp_SUD_API_272 */
          /* Assign Previous Discrete Length */
          prevDiscreteLen =
            CanTp_DiscreteDlcDataLength[ptrChannelRam->DecreteIndex - (uint8)CANTP_ONE];
        }
        flagLoop = CANTP_ONE;
      }
    }
    /* polyspace-end RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined " */
    /* 1. If first PCI byte is not equal to 0 */
    if(!(pciByte == (uint8)CANTP_ZERO))
    {
      /* @Trace: CanTp_SUD_API_280 */
      dlcErrorFlag = CANTP_TRUE;
    }
    /* 2. Check SF_DL and CAN_DL are matched */
    else if((*sduLength < ((PduLengthType)prevDiscreteLen - (PduLengthType)CANTP_ONE - (PduLengthType)bytePos))
        || (*sduLength > ((PduLengthType)discreteLen - (PduLengthType)CANTP_TWO - (PduLengthType)bytePos)))
    {
      /* @Trace: CanTp_SUD_API_281 */
      dlcErrorFlag = CANTP_TRUE;
    }
    else
    {
      /* Do Nothing */
    }
  }
  #else /* (CANTP_FD_SUPPORT == STD_ON)  */
  /* In case of Classic CAN and  when Padding is off */
  *sduLength = (PduLengthType)pciByte;
  ptrChannelRam->CurrentFrameLen = (uint8)*sduLength;

  /* 1. Check if SF_DL exceeds CAN_DL-1(normal add.) or CAN_DL-2(mixed/extended add.) */
  if(receivedDlc < ((uint8)*sduLength + bytePos + (uint8)CANTP_ONE))
  {
    /* @Trace: CanTp_SUD_API_282 */
    dlcErrorFlag = CANTP_TRUE;
  }
  #if (STD_OFF == CANTP_RX_SDU_PADDING_ACTIVATION)
  /*Redmine #19445*/
  /* 2. Check SF_DL and CAN_DL are matched */
  else if(!(receivedDlc == ((uint8)*sduLength + bytePos + (uint8)CANTP_ONE)))
  {
    /* @Trace: CanTp_SUD_API_283 */
    dlcErrorFlag = CANTP_TRUE;
  }
  #endif
  /* 3. Check if SF_DL is 0 */
  else if(*sduLength == CANTP_ZERO)
  {
    /* @Trace: CanTp_SUD_API_284 */
    dlcErrorFlag = CANTP_TRUE;
  }
  /* 4. Check LddDecodedSduLength validity - does it exceed maximum capacity*/
  else if ((uint8)*sduLength > ((uint8)CANTP_SEVEN - bytePos))
  {
    /* @Trace: CanTp_SUD_API_285 */
    dlcErrorFlag = CANTP_TRUE;
  }
  else
  {
    /* Do Nothing */
  }
  #endif /* (CANTP_FD_SUPPORT == STD_ON) */

  return (dlcErrorFlag);
}
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_RxNewframeDlcCheckfirstframe                  **
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
** Input Parameters     : ptrRxNSdu                                           **
**                        ptrSrc                                              **
**                        sduLength                                           **
**                        receivedDlc                                         **
**                                                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : dlcErrorFlag                                        **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SWP_CP_SRS_UDS_0074 SWP_CP_SRS_UDS_0075 SWP_CP_SRS_UDS_0076 */
FUNC(boolean, CANTP_CODE) CanTp_RxNewframeDlcCheckfirstframe(
  P2CONST(CanTp_RxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrRxNSdu,
  P2CONST(uint8, AUTOMATIC, CANTP_CONST) ptrSrc, 
  P2VAR(PduLengthType, AUTOMATIC, CANIF_VAR) sduLength,
  uint8 receivedDlc)
{
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam;
  
  uint8 pciByte;
  uint8 rxDlMax;
  uint8 bytePos;
  /* polyspace +1 RTE:NIV [Not a defect:Low] "The value of ptrSrc has been gotten from PDU, no impact" */
  pciByte = *ptrSrc;
  ptrChannelRam = &CanTp_ChannelRxRam[ptrRxNSdu->ChannelId];
  rxDlMax = ptrChannelRam->RxDl;
  boolean dlcErrorFlag;
  dlcErrorFlag = CANTP_FALSE;

  

  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))
  /* Get the N_PCI position if transmit NSDU is configured as Extended */
  bytePos = CanTp_BytePos[ptrRxNSdu->AddressingMode];
  #else
  /* Initialise the Addressing format value as Standard */
  bytePos = (uint8)CANTP_ZERO;
  #endif
  /* polyspace-begin RTE:NIV [Not a defect:Low] "The value of ptrSrc has been gotten from PDU, no impact" */
  /* Get FF_DL in case of there is no escape sequence (FF_DL <= 4095) */
  if((ptrSrc[CANTP_ONE] != CANTP_ZERO) 
            || ((ptrSrc[CANTP_ZERO] & (uint8)CANTP_FF_LEN_MASK) != CANTP_ZERO))
  {
    /* @Trace: CanTp_SUD_API_287 */
    *sduLength =
    ((PduLengthType)pciByte & (PduLengthType)CANTP_FF_LEN_MASK);
    *sduLength =
    (PduLengthType)(((uint32)((uint32)*sduLength << CANTP_EIGHT)) | (uint32)ptrSrc[CANTP_ONE]);
  }
  /* Get FF_DL in case of there is escape sequence (FF_DL > 4095) */
  else
  {
    /* @Trace: CanTp_SUD_API_288 */
    *sduLength =
        (PduLengthType)((uint32)*sduLength | (uint32)((uint32)(ptrSrc[CANTP_TWO]) << CANTP_TWENTYFOUR));
    *sduLength =
        (PduLengthType)((uint32)*sduLength | (uint32)((uint32)(ptrSrc[CANTP_THREE]) << CANTP_SIXTEEN));
    *sduLength =
        (PduLengthType)((uint32)*sduLength | (uint32)((uint32)(ptrSrc[CANTP_FOUR]) << CANTP_EIGHT));
    *sduLength =
        (PduLengthType)((uint32)*sduLength | (uint32)ptrSrc[CANTP_FIVE]);
  }
  /* polyspace +5 RTE:UNR [Justified:Low] "It depends on the Sdulength of the received PDU, No impact" */
  /* 1. Check if CAN_DL is less than 8 */
  if(receivedDlc < ((uint8)(CANTP_EIGHT)))
  {
    /* @Trace: CanTp_SUD_API_289 */
    dlcErrorFlag = CANTP_TRUE;
  }
  /* 2. Check if it has escape sequence even though FF_DL is less than 4095 byte */
  else if(((ptrSrc[CANTP_ONE] == (uint8)CANTP_ZERO)
    && ((ptrSrc[CANTP_ZERO] & (uint8)CANTP_FF_LEN_MASK) == (uint8)CANTP_ZERO))
    && (*sduLength <= (PduLengthType)CANTP_FOURZERONINEFIVE))
  {
    /* @Trace: CanTp_SUD_API_290 */
    dlcErrorFlag = CANTP_TRUE;
  }
  /* polyspace-end RTE:NIV [Not a defect:Low] "The value of ptrSrc has been gotten from PDU, no impact" */
  /* 3. Check if received FF_DL is less than min(FF_DL) - should be transmitted by SF */
  /* 3.1. TX_DL of sender is equal to 8 */
  else if((rxDlMax == (uint8)CANTP_EIGHT) && (*sduLength < ((uint16)CANTP_EIGHT - (uint16)bytePos)))
  {
    /* @Trace: CanTp_SUD_API_291 */
    dlcErrorFlag = CANTP_TRUE;
  }
  /* 3.2. TX_DL of sender is more than 8 */
  else if((rxDlMax > (uint8)CANTP_EIGHT)
      && ((uint32)*sduLength < (((uint32)rxDlMax - (uint32)CANTP_ONE) - (uint32)bytePos)))
  {
    /* @Trace: CanTp_SUD_API_292 */
    dlcErrorFlag = CANTP_TRUE;
  }
  #if (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)
  /* 4. Functionally addressed FirstFrame shall be ignored. */
  else if((uint8)CANTP_FUNCTIONAL_ADDRESS == ptrRxNSdu->TaType)
  {
    /* @Trace: CanTp_SUD_API_293 */
    dlcErrorFlag = CANTP_TRUE;
  }
  #endif
  else
  {
    /* Do Nothing */
  }
  return (dlcErrorFlag);
}
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_CheckRxBuffer                                 **
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
** Input Parameters     : ptrChannelRam                                       **
**                        bufferSize                                          **
**                                                                            **
**                                                                            **
**                                                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : lenBufferStatus                                     **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(BufReq_ReturnType, CANTP_CODE) CanTp_CheckRxBuffer(
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam,
  P2VAR(PduLengthType, AUTOMATIC, CANTP_VAR) bufferSize)
{
  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) || \
      (STD_ON == CANTP_RX_MIXED_ADDRESS) || \
      (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) || \
      (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS))  
  P2CONST(CanTp_RxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrRxNSdu;
  #endif
  #endif
  #endif
  P2CONST(CanTp_RxNSduDynamicType, AUTOMATIC, CANTP_CONST) ptrRxNSduDyna;
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) ptrRxSrc;
  BufReq_ReturnType lenBufferStatus;
  PduInfoType pduInfo;
  
  PduIdType activeSduId;

  

  /* Set metaData to default */
  pduInfo.MetaDataPtr = NULL_PTR;

  /* Initialize the source pointer */
  ptrRxSrc = ptrChannelRam->ptrUpLayerBuff;

  /*Get the SduId */
  activeSduId = ptrChannelRam->ActivePduId;

  /* If support PostBuild */
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  ptrRxNSduDyna = &(Variant_Select->PtrRxNSduDynamic)[activeSduId];
  #else
  ptrRxNSduDyna = &CanTp_RxSduDynamic[activeSduId];
  #endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

  #ifdef CANTP_DYNID_SUPPORT
  #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) || \
      (STD_ON == CANTP_RX_MIXED_ADDRESS) || \
      (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) || \
      (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS))
  #if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
  /* Get the static RxNSdu structure Pointer */
  ptrRxNSdu = &(Variant_Select->PtrRxNSduStatic)[activeSduId];
  #else
  /* Get the static RxNSdu structure Pointer */
  ptrRxNSdu = &CanTp_RxSduStatic[activeSduId];
  #endif
  #endif
  #endif /* End of #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
  #endif /* End of #ifdef CANTP_DYNID_SUPPORT */

  /* Check if the buffer request for FF or SF */
  if ((uint8)CANTP_ONE == ptrChannelRam->NewFrameFlag)
  {
    /* @Trace: CanTp_SUD_API_234 */
    #if (CANTP_START_OF_RECPT_FOUR_FOUR_ZERO == STD_ON)
    pduInfo.SduDataPtr = ptrRxSrc;
    pduInfo.SduLength = ptrChannelRam->CurrentFrameLen;
    pduInfo.MetaDataPtr = NULL_PTR;

    /* @Trace: SWS_CanTp_00331 */
    /* When calling PduR_CanTpStartOfReception() for a
     * generic connection (N-SDU with MetaData), the CanTp module shall forward the
     * extracted addressing information via the MetaData of the N-SDU. The addressing
     * information in the MetaData depends on the addressing format:
     * Normal: none
     * Extended: N_TA
     * Mixed 11 bit: N_AE
     * Normal fixed: N_SA, N_TA
     * Mixed 29 bit: N_SA, N_TA, N_AE
     */
    #ifdef CANTP_DYNID_SUPPORT
    #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT)
    #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) || \
        (STD_ON == CANTP_RX_MIXED_ADDRESS) || \
        (STD_ON == CANTP_RX_MIXED29BIT_ADDRESS) || \
        (STD_ON == CANTP_RX_NORMALFIXED_ADDRESS))
    /* Provide metaData to upper layer if Generic connection supported */
    if (CANTP_STANDARD_ADDRESS != ptrRxNSdu->AddressingMode)
    {
      #if (STD_ON == CANTP_RX_NSDU_METADATA)
      if ((CANTP_TRUE == ptrChannelRam->AvlMetaDt) &&\
         (CANTP_TRUE == ptrRxNSdu->OutPduwithMetaDataSts))
      {
        /* @Trace: CanTp_SUD_API_236 */
        /* Forward the extracted addressing information
         * via the MetaData of the N-SDU
         */
        pduInfo.MetaDataPtr = &ptrChannelRam->UpMetaData[(uint8)CANTP_ZERO];
      }
      else
      #endif /* STD_ON == CANTP_RX_NSDU_METADATA */
      {
        /* @Trace: CanTp_SUD_API_237 */
        pduInfo.MetaDataPtr = NULL_PTR;
      }
    }
    #endif
    #endif /* End of #if (STD_ON == CANTP_GENERIC_CONNECTION_SUPPORT) */
    #endif /* End of #ifdef CANTP_DYNID_SUPPORT */

    /* @Trace: SWS_CanTp_00329 */
    /* Provide the content of the FF/SF to PduR using the parameter TpSduInfoPtr */
    /* @Trace: SWS_CanTp_00079 */
    /* Notify the upper layer when receving an SF or FF
     * Invoke the buffer request for FF or SF reception */
    /* @Trace: SWS_CanTp_00080 */
    /* The available Rx buffer size is reported to the CanTp in the output pointer
     * parameter of the PduR_CanTpStartOfReception() service. The available Rx buffer can be smaller
     * than the expected N-SDU data length */
    /* polyspace-begin RTE:IDP [Not a defect:Low] "Its boundary is pre-defined " */ 
    lenBufferStatus = PduR_CanTpStartOfReception(ptrRxNSduDyna->UpTargetPduId,
      &pduInfo, ptrChannelRam->SduLength, bufferSize);

    #else
    /* Invoke the buffer request for FF or SF reception */
    lenBufferStatus = PduR_CanTpStartOfReception(ptrRxNSduDyna->UpTargetPduId,
      ptrChannelRam->SduLength, bufferSize);
    #endif
    /* polyspace-end RTE:IDP [Not a defect:Low] "Its boundary is pre-defined " */
  }
  else /* The buffer request for CF */
  {
    /* @Trace: CanTp_SUD_API_238 */
    /* @Trace: SWS_CanTp_00222 */
    /* While the timer N_Br is active, the CanTp module shall call the service PduR_CanTpCopyRxData()
     * with a data length 0 (zero) and NULL_PTR */
    /* Initialize the PduInfo to request buffer for CF */
    pduInfo.SduDataPtr = NULL_PTR;
    pduInfo.SduLength = (PduLengthType)CANTP_ZERO;
    /* polyspace +3 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined " */
    /* Invoke the buffer request for CF reception */
    lenBufferStatus = PduR_CanTpCopyRxData(ptrRxNSduDyna->UpTargetPduId,
      &pduInfo, bufferSize);

    /* @Trace: SWS_CanTp_00224 */
    /* The Rx buffer is large enough for the next block,
     * CanTp shall expect the reception of Consecutive Frame N-PDUs */
    if ((*bufferSize >= (PduLengthType)ptrChannelRam->CurrentFrameLen) ||
            ((uint32)*bufferSize >= ptrChannelRam->ByteCounter))
    {
      /* @Trace: CanTp_SUD_API_240 */
      if ((uint32)ptrChannelRam->CurrentFrameLen > ptrChannelRam->ByteCounter)
      {
         ptrChannelRam->CurrentFrameLen = \
                 (uint8)(CANTP_ERASE_3BYTES_HIGH & ptrChannelRam->ByteCounter);
      }
      /* Expected receiver one CF */
      ptrChannelRam->FrameType = (uint8)CANTP_CF_PCI;
    }
  } /* End of else */
  return (lenBufferStatus);
}
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_EstimateBS                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is estimate Block size                **
**                        for transmitting the FC                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrChannelRam                                       **
**                        ptrRxNSduRam                                        **
**                        frameSize                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                                                                            **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01148 SRS_Can_01068 SRS_Can_01069 SRS_Can_01071 SRS_Can_01078 */
FUNC(uint8, CANTP_CODE) CanTp_EstimateBS(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
    CANTP_VAR) ptrChannelRam,
    P2CONST(CanTp_STminBsType, AUTOMATIC, CANTP_CONST) ptrRxNSduRam,
    uint8 frameSize)
{
  PduLengthType bufferLength;
  PduLengthType bsEstimated;
  uint8 remByte;
  uint8 dataArray;

  if ((uint8)CANTP_FS_CTS == ptrChannelRam->FlowStatus)
  {  
    /* @Trace: CanTp_SUD_API_219 */
    /* @Trace: SWS_CanTp_00067 */
    /* The CanTp shall use the same value for the BS and STmin parameters on each FC
     * sent during a segmented reception */
    /* @Trace: SWS_CanTp_00091 */
    /* The dynamic setting of some transport protocol internal parameters
     * (STmin and BS) by application */
    /* @Trace: SWS_CanTp_00282 */
    /* FC protocol data units give receivers the possibility of controlling sender data flow */
    /* Check if the available buffer length greater than number of bytes needs
     * to be received and configured BS is ZERO. */
    /* polyspace +2 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined " */
    if ((ptrChannelRam->AvlBuffLength >= ptrChannelRam->ByteCounter)
        && (ptrRxNSduRam->BlockSize == (uint8)CANTP_ZERO))
    {
      /* @Trace: CanTp_SUD_API_220 */
      /* Store the Configure BS that is infinite */
      ptrChannelRam->BSVar = CANTP_INFINITE_BS;
    }
    else 
    {
      /* Check if the available buffer length greater than number of bytes needs to be received. */
      if (ptrChannelRam->AvlBuffLength >= ptrChannelRam->ByteCounter)
      {
        /* @Trace: CanTp_SUD_API_221 */
        /* Store the byte counter as buffer length in local variable */
        bufferLength = (PduLengthType)ptrChannelRam->ByteCounter;

        /* polyspace +2 RTE:ZDV [Not a defect:Low] "The value of frameSize depend on the value of RxDl but RxDl shall be assigned equal CANTP_EIGHT when receivedDlc < CANTP_EIGHT and equal receivedDlc when receivedDlc > CANTP_EIGHT. Therefore, this warning not impact." */
        /* Check data is exact multiple of framelength*/
        remByte = (uint8)(bufferLength % (PduLengthType)frameSize);
        bsEstimated = ((((PduLengthType)bufferLength) /
                          (PduLengthType)frameSize) +
                          (PduLengthType)CANTP_ONE);   
        if ((uint8)CANTP_ZERO == remByte)
        {
          /* @Trace: CanTp_SUD_API_360 */
          bsEstimated = (((PduLengthType)bufferLength) /
                        (PduLengthType)frameSize);
        }
      } /* else if(ptrChannelRam->AvlBuffLength >=ptrChannelRam->ByteCounter) */
      else
      {
        /* @Trace: CanTp_SUD_API_222 */
        /* Store the buffer length in local variable */
        bufferLength = (PduLengthType)ptrChannelRam->AvlBuffLength;

        /* polyspace +3 RTE:ZDV [Not a defect:Low] "The value of frameSize depend on the value of RxDl but RxDl shall be assigned equal CANTP_EIGHT when receivedDlc < CANTP_EIGHT and equal receivedDlc when receivedDlc > CANTP_EIGHT. Therefore, this warning not impact." */
        /* Estimate the possible BS value */
        bsEstimated = (((PduLengthType)bufferLength) /
        (PduLengthType)frameSize);
      } /*
        * End of else
        * Store the Block Size value
        */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined " */
      ptrChannelRam->BSVar = (uint16)ptrRxNSduRam->BlockSize;
      /* Check if the estimated BS value is less than maximum BS configured */
      if ((bsEstimated < ptrRxNSduRam->BlockSize) ||
          ((ptrRxNSduRam->BlockSize == (uint8)CANTP_ZERO) &&
           (bsEstimated != (PduLengthType)CANTP_ZERO)))
      {
        /* @Trace: CanTp_SUD_API_223 */
        /* Store the Estimate possible Block Size value */
        ptrChannelRam->BSVar = (uint16)bsEstimated;
      }
    }
    /* Store the Block size as N_PCI byte 2 in the local buffer */
    dataArray = (uint8)(ptrChannelRam->BSVar & CANTP_NAI_MASK);
  } /* Flow status is CTS */
  else
  {
    /* @Trace: CanTp_SUD_API_224 */
    /* Store the null as N_PCI byte 2 in the local buffer */
    dataArray = (uint8)CANTP_ZERO;
  }
  return(dataArray);
}
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

