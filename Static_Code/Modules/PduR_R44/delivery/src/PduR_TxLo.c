/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't matter" */
/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: PduR_TxLo.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of the Common functionality of                      **
**              PduR_DETCheckLoTxConfirmation(), PduR_GWLoTxConfirmation()    **
**              PduR_LoTxConfirmation(), PduR_DETCheckLoTriggerTransmit(),    **
**              PduR_LoTriggerTransmit(), PduR_FifoHandleTriggerTransmit      **
**              PduR_IfFreeBuffer()                                           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By          Description                          **
********************************************************************************
** 1.0.9.0_HF1 24-May-2024   Mj Kim      CP44-3752, CP44-7397, CP44-8274      **
** 1.0.4       11-Aug-2022   PhucNHM     CP44-635                             **
** 1.0.3       07-Dec-2021   PhucNHM     R44-Redmine #22235                   **
** 1.0.2       05-Oct-2021   PhucNHM     R44-Redmine #20586                   **
** 1.0.1       22-Jun-2021   PhucNHM     R44-Redmine #18951                   **
** 1.0.0       04-Dec-2020   AUTOEVER    Initial Version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: PduR_SUD_FILE_001 */
#include "PduR.h"               /* Header File */
#include "PduR_TxLo.h"          /* PduR Tx Lo Header */
#include "SchM_PduR.h"          /* SchM header */
#include "PduR_Incl.h"          /* Dependent module Header files*/
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_LO_TXCONFIRMATION == STD_ON)
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, PDUR_CODE) PduR_DETCheckLoTxConfirmation( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType txPduId, uint8 moduleType);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && \
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_GWLoTxConfirmation( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
       P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) ptrLoTxConfirmation);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif




#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && \
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_IfFreeBuffer( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif


#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON) &&\
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_DETCheckLoTriggerTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType txPduId, uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) && \
      (PDUR_IF_BUFFER_TT_FIFO_EXIST == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_FifoHandleTriggerTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) ptrIfTriggerTransmit,
  P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif /* #if ((PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON) &&\
  (PDUR_LO_TXCONFIRMATION == STD_ON)) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF)  */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : PduR_LoTxConfirmation                               **
**                                                                            **
** Service ID           : 0x40                                                **
**                                                                            **
** Description          : This function is called by the interface layer after**
**                        the PDU has been transmitted on the network. The    **
**                        PDU Router shall translate the TxPduId into the     **
**                        configured target PDU ID and route this             **
**                        confirmation to the configured target function.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds                      **
**                        Non-Reentrant for the same PduId                    **
**                                                                            **
** Input Parameters     : PduIdType txPduId,                                  **
**                        uint8 moduleType, Std_ReturnType result             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        TxConfirmation, PduR_LowIfConfirmation              **
**                        PduR_LoTxConfig                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckLoTxConfirmation(),                    **
**                        PduR_GWLoTxConfirmation(),                          **
**                        SchM_Enter_PduR_TP_TX_PROTECTION_AREA(),            **
**                        SchM_Exit_PduR_TP_TX_PROTECTION_AREA()              **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_PduR_06020 */
/* @Trace: SRS_PduR_06116 */
/* @Trace: SRS_PduR_06117 */
/* @Trace: SRS_PduR_06123 */
/* @Trace: SRS_BSW_00167 */
/* @Trace: SRS_BSW_00171 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_LO_TXCONFIRMATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
/* @Traceability BEGIN -- SRS: SWS_PduR_00119 SWS_PduR_00100 SWS_PduR_00766
                               SWS_PduR_00627 SWS_PduR_00221 SWS_PduR_00667
                               SWS_PduR_00665 SWS_PduR_00640 SWS_PduR_00807
                               SWS_PduR_00785 SWS_PduR_00793 SWS_PduR_00788
                               SWS_PduR_00816 SWS_PduR_00287 SWS_PduR_00806
                               SWS_PduR_00256 SWS_PduR_00589 SWS_PduR_00328
                               SWS_PduR_00330 SWS_PduR_00365 SWS_PduR_00824
                               SWS_PduR_00008 SWS_PduR_00764 */
FUNC(void, PDUR_CODE) PduR_LoTxConfirmation(PduIdType txPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  uint8 moduleType, Std_ReturnType result)
#else
FUNC(void, PDUR_CODE) PduR_LoTxConfirmation(PduIdType txPduId,
  Std_ReturnType result)
#endif
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoTxDestination, AUTOMATIC, PDUR_CONST) ptrLoTxDestination;
  #endif
  P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) ptrLoTxConfirmation;
  #if ((PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON) && \
      (PDUR_IF_TRANSMIT == STD_ON))
  P2VAR(PduR_MulticastTxInfo, AUTOMATIC, PDUR_VAR) ptrMulticastTxInfo;
  #endif
  PDUR_UNUSED(result);
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean detErrorFlag;
  detErrorFlag = PduR_DETCheckLoTxConfirmation(txPduId, moduleType);
  /* Check whether any development errors are detected */
  if ((boolean)PDUR_FALSE == detErrorFlag)
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_334 */
    /* Get the pointer to LoTxDestination structure */
    ptrLoTxDestination = &PduR_LoTxConfig[txPduId];
    /* Get the pointer to LoIfTpDestiantion structure */
    ptrLoTxConfirmation = (P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST))
                               (ptrLoTxDestination->LoIfTpDestiantion);
    #else
    /* @Trace: PduR_SUD_API_337 */
    /* Get the pointer to LoTxConfirmation structure */
    ptrLoTxConfirmation = &PduR_LowIfTxConfirmation[txPduId];
    #endif
    #if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
    /* Check if Gateway */
    if (PDUR_GATEWAY_MASK ==
        (ptrLoTxConfirmation->TargetIndex & PDUR_GATEWAY_MASK))
    {
      /* If Buffered Gateway present  */
      #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
      if (PDUR_INVALID_BUFFER != ptrLoTxConfirmation->TxBufferIndex)
      {
        /* @Trace: PduR_SUD_API_326 */
        PduR_GWLoTxConfirmation(ptrLoTxConfirmation);
      } /* if Buffered Gateway present  */
      else
      {
        /* No Action */
      }
      #endif /* #if(PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
    } /* Check if Gateway */
    else
    #endif /* End of if (PDUR_IF_GATEWAY_OPERATION == STD_ON) */
    {
      #if (PDUR_IF_NORMAL_OPERATION == STD_ON)
      /* @Trace: SRS_PduR_06119 */
      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of LoTxConfirmation is generated by generator and could be changed in another configuration" */
      if ((boolean)PDUR_TRUE == ptrLoTxConfirmation->LoTxConfirmation)
      {
        /* Check whether PduConfig is PDUR_TP_GATEWAY */
        #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
        /* Check if confirmation status is non-zero */
        if (((uint8)PDUR_ZERO) != ((ptrLoTxConfirmation->TargetIndex)
                                                & ((uint8)PDUR_MULTICAST_MASK)))
        {
          /* @Trace: PduR_SUD_API_127 */
          ptrMulticastTxInfo = (ptrLoTxConfirmation->MulticastTxInfo);
          /* Disable relevant interrupts */
          SchM_Enter_PduR_TP_TX_PROTECTION_AREA();
          /* Update the result value */
          ptrMulticastTxInfo->Result &= result; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:IDP [Not a defect:Low] "configured memory access index" */
          /* Clear the confirmation status */
          ptrMulticastTxInfo->ConfStatus &=
                              (uint8)(~(ptrLoTxConfirmation->TxConfirmMask));
          /* Enable relevant interrupts */
          SchM_Exit_PduR_TP_TX_PROTECTION_AREA();
          if ((uint8)PDUR_ZERO == ptrMulticastTxInfo->ConfStatus)
          {
            /* Invoke Upper layer TxConfirmation function */
            if(PduR_LowIfConfirmation
              [(ptrLoTxConfirmation->TargetIndex) & /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "Array index is valid due to data flow" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
                (uint8)PDUR_IFCONF_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
            {
              /* @Trace: PduR_SUD_API_328 */
              (void)PduR_LowIfConfirmation[(ptrLoTxConfirmation->TargetIndex)
                  & (uint8)PDUR_IFCONF_TARGET_INDEX_MASK].TargetLayer
                  (ptrLoTxConfirmation->TargetPduId,
                  ptrMulticastTxInfo->Result);
            }
            else
            { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
              /* No Action */
            }
          }
          else
          {
            /* No Action */
          }
        } /* End of if (PDUR_ZERO != ptrLoTxConfirmation->TxConfirmMask) */
        /* Single cast */
        else
        #endif /*  #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)  */
        {
          /* Invoke Upper layer TxConfirmation function */
          if(PduR_LowIfConfirmation[(ptrLoTxConfirmation->TargetIndex) & /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "Array index is valid due to data flow" */
            (uint8)PDUR_IFCONF_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
          {
            /* @Trace: PduR_SUD_API_128 */
            (void)PduR_LowIfConfirmation[(ptrLoTxConfirmation->TargetIndex) &
                (uint8)PDUR_IFCONF_TARGET_INDEX_MASK]
                .TargetLayer(ptrLoTxConfirmation->TargetPduId, result);
          }
          else
          { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
            /* No Action */
          }
        }
      } /* @if ((boolean)PDUR_TRUE == ptrLoTxConfirmation->LoTxConfirmation) */
      else
      #endif /* End of if (PDUR_IF_NORMAL_OPERATION == STD_ON) */
      { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
        /* No Action */
      }
    }
  }
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No Action */
  }
  #endif
} /* End of PduR_LoTxConfirmation(PduIdType txPduId) */
/* @Traceability BEGIN -- SRS: SWS_PduR_00119 SWS_PduR_00100 SWS_PduR_00766
                               SWS_PduR_00627 SWS_PduR_00221 SWS_PduR_00667
                               SWS_PduR_00665 SWS_PduR_00640 SWS_PduR_00807
                               SWS_PduR_00785 SWS_PduR_00793 SWS_PduR_00788
                               SWS_PduR_00816 SWS_PduR_00287 SWS_PduR_00806
                               SWS_PduR_00256 SWS_PduR_00589 SWS_PduR_00328
                               SWS_PduR_00330 SWS_PduR_00365 SWS_PduR_00824
                               SWS_PduR_00008 SWS_PduR_00764 */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_LO_TXCONFIRMATION == STD_ON)  */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_ON)  */
/*******************************************************************************
** Function Name        : PduR_DETCheckLoTxConfirmation                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the interface after      **
**                        the PDU has been transmitted on the network. The    **
**                        PDU Router shall translate the txPduId into the     **
**                        configured target PDU ID and route this             **
**                        confirmation to the configured target function.     **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds                      **
**                        Non-Reentrant for the same PduId                    **
**                                                                            **
** Input Parameters     : PduIdType txPduId,                                  **
**                        uint8 moduleType, boolean ifRouting                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean detErrorFlag                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_LowIfTxConfirmation, PduR_InitStatus           **
**                        PduR_IfTpConfirmationMaxPduId, PduR_LoTxConfig      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_LO_TXCONFIRMATION == STD_ON)
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, PDUR_CODE) PduR_DETCheckLoTxConfirmation(
  PduIdType txPduId, uint8 moduleType)
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoTxDestination, AUTOMATIC, PDUR_CONST) ptrLoTxDestination;
  #endif
  P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) ptrLoTxConfirmation;
  boolean detErrorFlag;
  detErrorFlag = (boolean)PDUR_FALSE;
  /* Check whether the module is initialised */
  if (PDUR_UNINIT == PduR_InitStatus)
  {
    /* @Trace: SRS_BSW_00406 */
    /* @Trace: PduR_SUD_API_138 */
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_TX_CONFIRMATION_SID, PDUR_E_UNINIT);
    /* Set the error flag to TRUE */
    detErrorFlag = (boolean)PDUR_TRUE;
  } /* End of if (PDUR_UNINIT == PduR_InitStatus) */
  else
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_344 */
    if (txPduId >= PduR_IfTpConfirmationMaxPduId)
    #else
    /* @Trace: PduR_SUD_API_139 */
    if (txPduId >= PDUR_LO_TXCONFIRMATION_MAXPDUID)
    #endif
    {
      /* Report to DET */
      /* @Trace: SRS_PduR_06103 */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_TX_CONFIRMATION_SID, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      detErrorFlag = (boolean)PDUR_TRUE;
    } /* End of if (txPduId >= PDUR_LO_TXCONFIRMATION_MAXPDUID) */
    else
    {
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_OFF)
      ptrLoTxConfirmation = &PduR_LowIfTxConfirmation[txPduId];
      #else
      /* Get the pointer to ptrLoTxDestination structure */
      ptrLoTxDestination = &PduR_LoTxConfig[txPduId];
      /* Get the pointer to LoIfTpDestiantion structure */
      ptrLoTxConfirmation = (P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST))
                               (ptrLoTxDestination->LoIfTpDestiantion);
      if ((boolean)PDUR_TRUE !=
                             (boolean)ptrLoTxDestination->IsInterfaceRouting)
      {
        /* Report to DET */
        /* @Trace: PduR_SUD_API_345 */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          PDUR_TX_CONFIRMATION_SID, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to TRUE */
        detErrorFlag = (boolean)PDUR_TRUE;
      }
      else
      #endif
      {
        if (ptrLoTxConfirmation->ModuleType != moduleType)
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* Report to DET */
          /* @Trace: SRS_PduR_06103 */
          /* @Trace: PduR_SUD_API_140 */
          (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
            PDUR_TX_CONFIRMATION_SID, PDUR_E_PDU_ID_INVALID);
          /* Set the error flag to TRUE */
          detErrorFlag = (boolean)PDUR_TRUE;
        } /* End of if (ptrLoTxConfirmation->ModuleType != moduleType) */
        else
        {
          /* No Action */
        }
      }
    }
  }
  return (detErrorFlag);
} /* End of PduR_DETCheckLoTxConfirmation(
  PduIdType txPduId, uint8 moduleType)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON)  */
#endif /* #if (PDUR_LO_TXCONFIRMATION == STD_ON)  */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_GWLoTxConfirmation                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTxConfirmation function in case of gateway.  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduR_LoTxConf *ptrLoTxConfirmation                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_IfTransmitService, PduR_IfTxBuffer             **
**                        PduR_TxBufferConfig                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_IfFreeBuffer                                   **
**                        CANIF_TXPDU_GW_STATUS()                             **
**                        SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA(),       **
**                        Det_ReportRuntimeError()                            **
*******************************************************************************/
#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && \
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_GWLoTxConfirmation( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) ptrLoTxConfirmation)
{
  P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;
  P2VAR(PduR_TxQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  Std_ReturnType returnVal;
  #if (PDUR_CANIF_SUPPORT == STD_ON)
  uint8 canIfPduStatus;
  canIfPduStatus = PDUR_INVALID;
  if (PDUR_CANIF == ((ptrLoTxConfirmation->TargetIndex) &
                                            PDUR_TARGET_INDEX_MASK))
  {
    SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
    /* @Trace: PduR_SUD_API_402 */
    canIfPduStatus = CANIF_TXPDU_GW_STATUS(ptrLoTxConfirmation->TargetPduId); /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "Range is provided by CanIf module" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
    SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
  }
  else
  { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
    /* No Action */
  }
  #endif
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* @Trace: PduR_SUD_API_385 */
  /* Get the pointer to TxBuffer from the LoTxConfirmation structure */
  ptrTxBuffer = &PduR_TxBufferConfig[ptrLoTxConfirmation->TxBufferIndex];
  #else
  /* @Trace: PduR_SUD_API_384 */
  /* Get the pointer to TxBuffer from the LoTxConfirmation structure */
  ptrTxBuffer = &PduR_IfTxBuffer[ptrLoTxConfirmation->TxBufferIndex];
  #endif
  /* Check if buffer type is FIFO */
  if (ptrLoTxConfirmation->BufferType == (uint8)PDUR_D_FIFO)
  { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
    /* Enter critical area */
    #if(PDUR_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA();
    #endif
    /* Check if depth count is not zero */
    if ((uint8)PDUR_ZERO != ptrTxBuffer->CurrentDepth)
    {
      PduR_IfFreeBuffer(ptrTxBuffer);
      /* Check I-PDU is remain in FIFO buffer */
      if (((uint8)PDUR_ZERO != ptrTxBuffer->CurrentDepth)
      #if (PDUR_CANIF_SUPPORT == STD_ON)
        && (!((CANIF_GW_STOPPED == canIfPduStatus) || (CANIF_GW_ERRVOL ==
      canIfPduStatus)))
      #endif
         )
      {
        /* @Trace: SRS_PduR_06126 */
        /* @Trace: SRS_PduR_CUS_00002 */
        /* @Trace: PduR_SUD_API_143 */
        /* Get first queue in buffer PduR */
        ptrQueue = ptrTxBuffer->FirstQueuePtr;
        #if (PDUR_SHARED_GW_IF_BUFFER == STD_ON)
        if ((boolean)PDUR_TRUE == ptrLoTxConfirmation->BufferShared)
        {
          /* @Trace: PduR_SUD_API_439 */
          /* Invoke transmit function */
          returnVal = PduR_IfTransmitService[(
                                  ptrLoTxConfirmation->TargetIndex) &
                                  PDUR_TARGET_INDEX_MASK].TargetLayer(
                                  ptrQueue->TargetPduId,
                                  &ptrQueue->PduInfoPtr);
        }
        else
        #endif
        {
          /* @Trace: PduR_SUD_API_440 */
          /* Invoke transmit function */
          returnVal = PduR_IfTransmitService[(
                                  ptrLoTxConfirmation->TargetIndex) &
                                  PDUR_TARGET_INDEX_MASK].TargetLayer(
                                  ptrLoTxConfirmation->TargetPduId,
                                  &ptrQueue->PduInfoPtr);
        }
        if((Std_ReturnType)E_NOT_OK == returnVal)
        {
          /* Report to DET */
          /* @Trace: SRS_PduR_06105 */
          /* @Trace: PduR_SUD_API_144 */
          (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
            PDUR_TX_CONFIRMATION_SID, PDUR_E_PDU_INSTANCES_LOST);
        }
        else
        {
          /* No Action */
        }
      }
      else
      {
        /* No Action */
      }
    } /* End of if ((uint8)PDUR_ZERO != ptrTxBuffer->CurrentDepth) */
    else
    {
      /* @Trace: PduR_SUD_API_146 */
      /* No Action */
    }
    /* Exit critical area */
    #if(PDUR_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA();
    #endif
  } /* @if (ptrLoTxConfirmation->BufferType == (uint8)PDUR_D_FIFO) */
  else
  {
    /* No Action */
  }
} /* End of PduR_GWLoTxConfirmation(
     P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) ptrLoTxConfirmation)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
#endif /* #if ((PDUR_ZERO_COST_OPERATION == STD_OFF) &&
       (PDUR_LO_TXCONFIRMATION == STD_ON)) */

/*******************************************************************************
** Function Name        : PduR_LoTriggerTransmit                              **
**                                                                            **
** Service ID           : 0x41                                                **
**                                                                            **
** Description          : This function is called by the Master for           **
**                        sending out a frame. The trigger transmit can       **
**                        be initiated by the Master schedule table itself    **
**                        or a received header. Whether this function is      **
**                        called or not is statically configured for each     **
**                        PDU.The PDU Router shall translate the txPduId      **
**                        into the configuredtarget PDU ID and route this     **
**                        trigger to the configured target function           **
**                        (e.g. AUTOSAR Com).                                 **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds                      **
**                        Non-Reentrant for the same PduId                    **
**                                                                            **
** Input Parameters     : PduIdType txPduId,                                  **
**                        uint8 moduleType ,                                  **
**                        PduInfoType *ptrPduInfoPtr                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType returnVal                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_LowIfTxConfirmation, PduR_LoTxConfig           **
**                        PduR_IfTxBuffer,                                    **
**                        PduR_LowIfTriggerTransmit, PduR_IfTransmitService   **
**                        PduR_TxBufferConfig                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckLoTriggerTransmit(),                   **
**                        PduR_FifoIfMulticastTriggerTransmit(),              **
**                        PduR_IfFreeBuffer(),                                **
**                        Det_ReportRuntimeError(),                           **
**                        SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA(),       **
**                        SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA(),       **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_PduR_06020 */
/* @Trace: SRS_PduR_06116 */
/* @Trace: SRS_PduR_06117 */
/* @Trace: SRS_PduR_06123 */
/* @Trace: SRS_BSW_00167 */
/* @Trace: SRS_BSW_00171 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON) &&\
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* @Traceability BEGIN -- SRS: SWS_PduR_00119 SWS_PduR_00100 SWS_PduR_00330
                               SWS_PduR_00430 SWS_PduR_00661 SWS_PduR_00717
                               SWS_PduR_00221 SWS_PduR_00666 SWS_PduR_00715
                               SWS_PduR_00819 SWS_PduR_00785 SWS_PduR_00369
                               SWS_PduR_00662 SWS_PduR_00256 SWS_PduR_00824
                               SWS_PduR_00788 SWS_PduR_00807 SWS_PduR_00829
                               SWS_PduR_00805 SWS_PduR_00287 SWS_PduR_00816
                               SWS_PduR_00328 SWS_PduR_00010 SWS_PduR_00011
                               SWS_PduR_00764 */
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_LoTriggerTransmit(PduIdType txPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  uint8 moduleType,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) ptrPduInfoPtr)
#else
FUNC(Std_ReturnType, PDUR_CODE) PduR_LoTriggerTransmit(PduIdType txPduId,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) ptrPduInfoPtr)
#endif
{
  P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) ptrIfTriggerTransmit;
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoTxDestination, AUTOMATIC, PDUR_CONST) ptrLoTxDestination;
  #endif
  #if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
  #if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||\
  (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
  P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;

  P2VAR(uint8, AUTOMATIC, PDUR_VAR) ptrDataBuffer;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) ptrDestSduPtr;
  PduLengthType sduLengthVar = (uint8)PDUR_ZERO;
  #endif /* End of if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||
          *(PDUR_SB_TX_BUFFER_SUPPORT == STD_ON)) */
  #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  P2VAR(PduR_TxQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  #endif
  #endif /* End of if (PDUR_IF_GATEWAY_OPERATION == STD_ON) */
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif
  Std_ReturnType returnVal;

  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  returnVal = PduR_DETCheckLoTriggerTransmit(txPduId,
    moduleType, ptrPduInfoPtr);
  /* Check whether any development errors are detected */
  if ((Std_ReturnType)E_OK == returnVal)
  #else
  returnVal = (Std_ReturnType)E_OK;
  #endif
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_338 */
    /* Get the pointer to LoTxDestination structure */
    ptrLoTxDestination = &PduR_LoTxConfig[txPduId];
    /* Get the pointer to ptrIfTriggerTransmit structure */
    ptrIfTriggerTransmit = (P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST))
                               (ptrLoTxDestination->LoIfTpDestiantion);
    #else
    /* @Trace: PduR_SUD_API_179 */
    /* Get the pointer to ptrIfTriggerTransmit from PduR_LowIfTxConfirmation */
    ptrIfTriggerTransmit = &PduR_LowIfTxConfirmation[txPduId];
    #endif
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    groupIdValue = ptrIfTriggerTransmit->GroupMaskValue;
    indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
    idConvert = groupIdValue % PDUR_BITMASK_UINT8;
    /* @Trace: SRS_PduR_06120 */
    /* Check if routing path is enabled */
    if ((PDUR_UNDEFINED == groupIdValue) ||
        ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] &
                                          (((uint32)PDUR_ONE) << idConvert))))
    #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
    {
      #if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
      /* Check whether the Pdu is configured for Gateway operation */
      if (PDUR_GATEWAY_MASK == ((ptrIfTriggerTransmit->TargetIndex) &
                                                          PDUR_GATEWAY_MASK))
      {
        #if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||\
                                    (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
        /* Check whether buffer has been allocated to target */
        if (PDUR_INVALID_BUFFER != ptrIfTriggerTransmit->TxBufferIndex)
        {
          #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
          /* @Trace: PduR_SUD_API_375 */
          /* Get the pointer to TxBuffer from the PduR_ConfigSet structure */
          ptrTxBuffer = &PduR_TxBufferConfig[ptrIfTriggerTransmit->TxBufferIndex];
          #else
          /* @Trace: PduR_SUD_API_374 */
          /* Get the pointer to ptrTxBuffer from the PduR TxBuffer*/
          ptrTxBuffer = &PduR_IfTxBuffer[ptrIfTriggerTransmit->TxBufferIndex];
          #endif
          #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
          /* Check if buffer type is FIFO */
          /* @Trace: SRS_PduR_06032 */
          if (
            #if (PDUR_IF_BUFFER_TT_FIFO_EXIST == STD_ON)
            ((uint8)PDUR_TT_FIFO == ptrIfTriggerTransmit->BufferType) &&
            #endif
            ((uint8)PDUR_ZERO != ptrTxBuffer->CurrentDepth)
            )
          {
            /* @Trace: PduR_SUD_API_183 */
            /* Get FirstQueuePtr into local pointer */
            ptrQueue = ptrTxBuffer->FirstQueuePtr;
            /* Get the SduLength into Local variable */
            sduLengthVar = ptrQueue->PduInfoPtr.SduLength; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
            /* Get the pointer to ptrDataBuffer from ptrQueue*/
            ptrDataBuffer = ptrQueue->PduInfoPtr.SduDataPtr; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
          }
          else
          #endif
          {
            /* @Trace: PduR_SUD_API_182 */
            /* Get the SduLength into Local variable */
            sduLengthVar = ptrTxBuffer->SduLengthUpdate;
            /* Get the pointer to ptrDataBuffer from Tx Buffer*/
            ptrDataBuffer = ptrTxBuffer->SduPtr;
          }
          /* SduLength of low layer isn't smaller SduLength of PduR Buffer */
          if (ptrPduInfoPtr->SduLength >= sduLengthVar) /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "ptrPduInfoPtr is checked null by PduR_DETCheckLoTriggerTransmit function" */ /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:IDP [Not a defect:Low] "configured memory access index" */
          {
            /* Get the pointer to ptrDestSduPtr from ptrPduInfoPtr*/
            ptrDestSduPtr = ptrPduInfoPtr->SduDataPtr;
            /* Copy the length to ptrPduInfoPtr */
            ptrPduInfoPtr->SduLength = sduLengthVar;
            /* @Trace: SRS_BSW_00312 */
            /* Disable relevant interrupts */
            SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
            /* Copy the data from SduDataPtr to data buffer */
            while ((PduLengthType)PDUR_ZERO != sduLengthVar)
            {
              /* @Trace: PduR_SUD_API_184 */
              /* copy the data from Sdu Pointer to Data Pointer */
              *ptrDestSduPtr = *ptrDataBuffer; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
              /* MISRA Rule     : 17.4.
               *   Message      : Increment or decrement operation
               *                  performed on the pointer
               *   Reason       : Increment operator used
               *                  to achieve better throughput.
               *   Verification : However, part of the code
               *                  is verified manually and
               *                  it is not having any impact.
               */
              /* Increment the ptrDataBuffer Pointer */
              ptrDataBuffer++;
              /* MISRA Rule     : 17.4.
               *   Message      : Increment or decrement operation
               *                  performed on the pointer
               *   Reason       : Increment operator used
               *                  to achieve better throughput.
               *   Verification : However, part of the code
               *                  is verified manually and
               *                  it is not having any impact.
               */
              /* Increment the Data Pointer */
              ptrDestSduPtr++;
              /* Decrement SduLength */
              sduLengthVar--;
            }
            /* Enable relevant interrupts */
            SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();

            #if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) && \
              (PDUR_IF_BUFFER_TT_FIFO_EXIST == STD_ON))
            if (ptrIfTriggerTransmit->BufferType == (uint8)PDUR_TT_FIFO)
            {
              /* Check if depth count is not zero */
              if ((uint8)PDUR_ZERO != (ptrTxBuffer->CurrentDepth))
              {
                /* @Trace: PduR_SUD_API_419 */
                PduR_FifoHandleTriggerTransmit(ptrIfTriggerTransmit,
                  ptrTxBuffer);
              }
              else
              {
                /* @Trace: PduR_SUD_API_186 */
                returnVal = (Std_ReturnType)E_NOT_OK;
              }
            }
            else
            {
              /* No Action */
            }
            #endif /* End of if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
          } /* End if (ptrPduInfoPtr->SduLength >= sduLengthVar) */
          else
          {
            returnVal = (Std_ReturnType)E_NOT_OK;
          }
        } /* End if (PDUR_INVALID_BUFFER !=
                         ptrIfTriggerTransmit->TxBufferIndex) */
        else
        #endif  /*#if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) || \
                  (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))*/
        {
          returnVal = (Std_ReturnType)E_NOT_OK;
        }
      }
      /*
       * Check whether the Pdu is configured for Gateway operation
       * else no gateway
       */
      else
      #endif /* End of if (PDUR_IF_GATEWAY_OPERATION == STD_ON) */
      {
        #if (PDUR_IF_NORMAL_OPERATION == STD_ON)
        /* Invoke <Up>_TriggerTransmit */
        if(PduR_LowIfTriggerTransmit[ptrIfTriggerTransmit->TargetIndex &
          (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
        {
          /* @Trace: PduR_SUD_API_181 */
          returnVal =
            PduR_LowIfTriggerTransmit[ptrIfTriggerTransmit->TargetIndex &
            (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer(
            ptrIfTriggerTransmit->TargetPduId, ptrPduInfoPtr);
        }
        else
        #endif
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          returnVal = (Std_ReturnType)E_NOT_OK;
        }
      }
    }
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    else
    {
      /* @Trace: PduR_SUD_API_180 */
      returnVal = (Std_ReturnType)E_NOT_OK;
    }
    #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
  } /* Return Std Return Value*/
  return (returnVal);
} /* End of PduR_LoTriggerTransmit(PduIdType txPduId, P2VAR(PduInfoType,
   *AUTOMATIC, PDUR_VAR) ptrPduInfoPtr) */
/* @Traceability END -- SRS: SWS_PduR_00119 SWS_PduR_00100 SWS_PduR_00330
                               SWS_PduR_00430 SWS_PduR_00661 SWS_PduR_00717
                               SWS_PduR_00221 SWS_PduR_00666 SWS_PduR_00715
                               SWS_PduR_00819 SWS_PduR_00785 SWS_PduR_00369
                               SWS_PduR_00662 SWS_PduR_00256 SWS_PduR_00824
                               SWS_PduR_00788 SWS_PduR_00807 SWS_PduR_00829
                               SWS_PduR_00805 SWS_PduR_00287 SWS_PduR_00816
                               SWS_PduR_00328 SWS_PduR_00010 SWS_PduR_00011
                               SWS_PduR_00764 */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_LO_TXCONFIRMATION == STD_ON) */
#endif/* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
** Function Name        : PduR_DETCheckLoTriggerTransmit                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by PduR_LoTriggerTransmit   **
**                        check the parameters passed are valid               **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType txPduId,                                  **
**                        uint8 moduleType, PduInfoType *ptrPduInfoPtr,       **
**                        boolean ifRouting                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType returnVal                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_LowIfTxConfirmation, PduR_InitStatus           **
**                        PduR_IfTpConfirmationMaxPduId, PduR_LoTxConfig      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON) &&\
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
 static FUNC(Std_ReturnType, PDUR_CODE) PduR_DETCheckLoTriggerTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType txPduId, uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr)
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoTxDestination, AUTOMATIC, PDUR_CONST) ptrLoTxDestination;
  #endif
  P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) ptrIfTriggerTransmit;
  Std_ReturnType returnVal;
  returnVal = (Std_ReturnType)E_OK;
  /* Check whether the module is initialised */
  if (PDUR_UNINIT == PduR_InitStatus)
  {
    /* @Trace: SRS_BSW_00406 */
    /* @Trace: PduR_SUD_API_193 */
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_TRIGGER_TRANSMIT_SID, PDUR_E_UNINIT);
    /* Set the return value to E_NOT_OK */
    returnVal = (Std_ReturnType)E_NOT_OK;
  } /* End of if (PDUR_UNINIT == PduR_InitStatus) */
  else
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_341 */
    if (txPduId >= PduR_IfTpConfirmationMaxPduId)
    #else
    /* @Trace: PduR_SUD_API_194 */
    if (txPduId >= PDUR_LO_TXCONFIRMATION_MAXPDUID)
    #endif
    {
      /* Report to DET */
      /* @Trace: SRS_PduR_06103 */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_TRIGGER_TRANSMIT_SID, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      returnVal = (Std_ReturnType)E_NOT_OK;
    } /* End of if (txPduId >= PDUR_LO_TXCONFIRMATION_MAXPDUID) */
    else
    {
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_OFF)
      /* Get the pointer to ptrIfTriggerTransmit from PduR_LowIfTxConfirmation */
      ptrIfTriggerTransmit = &PduR_LowIfTxConfirmation[txPduId];
      #else
      /* Get the pointer to ptrLoTxDestination structure */
      ptrLoTxDestination = &PduR_LoTxConfig[txPduId];
      /* Get the pointer to ptrIfTriggerTransmit structure */
      ptrIfTriggerTransmit = (P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST))
                               (ptrLoTxDestination->LoIfTpDestiantion);
      if ((boolean)PDUR_TRUE !=
                             (boolean)ptrLoTxDestination->IsInterfaceRouting)
      {
        /* @Trace: PduR_SUD_API_342 */
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          PDUR_TRIGGER_TRANSMIT_SID, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to TRUE */
        returnVal = (Std_ReturnType)E_NOT_OK;
      }
      else
      #endif
      {
        if (ptrIfTriggerTransmit->ModuleType != moduleType)
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* Report to DET */
          /* @Trace: SRS_PduR_06103 */
          /* @Trace: PduR_SUD_API_195 */
          (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
            PDUR_TRIGGER_TRANSMIT_SID, PDUR_E_PDU_ID_INVALID);
          /* Set the error flag to TRUE */
          returnVal = (Std_ReturnType)E_NOT_OK;
        } /* End of if (ptrIfTriggerTransmit->ModuleType != moduleType) */
        else
        {
          /* Check if Gateway */
          if (PDUR_GATEWAY_MASK ==
            (ptrIfTriggerTransmit->TargetIndex & PDUR_GATEWAY_MASK))
          {
            /* Check If ptrPduInfoPtr is NULL_PTR */
            if (NULL_PTR == ptrPduInfoPtr)
            {
              /* Report to DET */
              /* @Trace: PduR_SUD_API_196 */
              (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                PDUR_TRIGGER_TRANSMIT_SID, PDUR_E_PARAM_POINTER);
              /* Set the return value to E_NOT_OK */
              returnVal = (Std_ReturnType)E_NOT_OK;
            } /* End of if (NULL_PTR == ptrPduInfoPtr) */
            /* Check If SduDataPtr is NULL_PTR */
            else
            {
              if (NULL_PTR == ptrPduInfoPtr->SduDataPtr) /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "ptrPduInfoPtr is checked not NULL_PTR" */
              {
                /* Report to DET */
                /* @Trace: PduR_SUD_API_343 */
                (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                  PDUR_TRIGGER_TRANSMIT_SID, PDUR_E_PARAM_POINTER);
                /* Set the return value to E_NOT_OK */
                returnVal = (Std_ReturnType)E_NOT_OK;
              } /* End of if (NULL_PTR == ptrPduInfoPtr->SduDataPtr) */
              else
              {
                /* No Action */
              }
            }
          }
          else
          {
            /* No Action */
          }
        }
      }
    }
  }
  return (returnVal);
} /* End of PduR_DETCheckLoTriggerTransmit(
  PduIdType txPduId, uint8 moduleType,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) ptrPduInfoPtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON)  */
#endif /* #if (PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON)&&
        * (PDUR_LO_TXCONFIRMATION == STD_ON)  */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_ON) */
/*******************************************************************************
** Function Name        : PduR_FifoHandleTriggerTransmit                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by PduR_LoTriggerTransmit   **
**                        to multicast transmit to lower module               **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : uint8 rxPduIndex, PduR_TxQueueType *ptrQueue        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType returnVal                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_LowRxIndication,                               **
**                        PduR_IfTransmitService, PduR_LoRxConfig             **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON) &&\
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) && \
      (PDUR_IF_BUFFER_TT_FIFO_EXIST == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_FifoHandleTriggerTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) ptrIfTriggerTransmit,
  P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer)
{
  P2VAR(PduR_TxQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  Std_ReturnType returnTxVal;
  /* @Trace: SRS_BSW_00312 */
  /* Enter critical area */
  SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA();
  /* @Trace: SRS_PduR_06105 */
  do
  {
    PduR_IfFreeBuffer(ptrTxBuffer);
    /* Check if depth count is not zero */
    if ((uint8)PDUR_ZERO != (ptrTxBuffer->CurrentDepth))
    {
      /* @Trace: SRS_PduR_06126 */
      ptrQueue = ptrTxBuffer->FirstQueuePtr;
      /* @Trace: PduR_SUD_API_189 */
      /* Invoke transmit function */
      returnTxVal = PduR_IfTransmitService[(
        ptrIfTriggerTransmit->TargetIndex) &
        PDUR_TARGET_INDEX_MASK].TargetLayer(
        ptrIfTriggerTransmit->TargetPduId,
        &ptrQueue->PduInfoPtr);
      if ((Std_ReturnType)E_NOT_OK == returnTxVal)
      {
        /* Report to DET */
        /* @Trace: SRS_PduR_06105 */
        /* @Trace: PduR_SUD_API_190 */
        (void)Det_ReportRuntimeError(PDUR_MODULE_ID,
          PDUR_INSTANCE_ID, PDUR_TRIGGER_TRANSMIT_SID,
          PDUR_E_PDU_INSTANCES_LOST);
      }
      else
      {
        /* No Action */
      }
    } /* End if ((uint8)PDUR_ZERO != (ptrTxBuffer->CurrentDepth)) */
    else
    {
      /* @Trace: PduR_SUD_API_187 */
      returnTxVal = (Std_ReturnType)E_OK;
    }
  } while ((Std_ReturnType)E_NOT_OK == returnTxVal);
  SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA();
} /* @End of PduR_FifoHandleTriggerTransmit() */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
#endif /* #if ((PDUR_TRIGGER_TRANSMIT_SUPPORT == STD_ON) &&\
  (PDUR_LO_TXCONFIRMATION == STD_ON)) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF)  */
/*******************************************************************************
** Function Name        : PduR_IfFreeBuffer                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by PduR_LoTriggerTransmit,  **
**                        PduR_GWLoTxConfirmation to free buffer              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduR_TxBuffer *ptrTxBuffer                          **
**                                                                            **
** InOut parameter      : None                                                **
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
#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && \
  (PDUR_LO_TXCONFIRMATION == STD_ON))
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_IfFreeBuffer( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer)
{
  P2VAR(PduR_TxQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  /* Decrement Depth */
  ptrQueue = ptrTxBuffer->FirstQueuePtr;
  /* Decrement CurrentDepth */
  ptrTxBuffer->CurrentDepth--;
  /* Buffer is release */
  ptrQueue->FreeBuffer = (boolean)PDUR_EMPTY; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:IDP [Not a defect:Low] "configured memory access index" */
  /* Update HeadLength or TailLength of ptrTxBuffer */
  if (ptrQueue->PduInfoPtr.SduDataPtr < ptrTxBuffer->IndexSduPtr) /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
  {
    /* @Trace: PduR_SUD_API_147 */
    /* Increment TailLength */
    ptrTxBuffer->TailLength += ptrQueue->PduInfoPtr.SduLength; /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
    /* Check Tail is greater TotalLength */
    if (ptrTxBuffer->TailLength >= ptrTxBuffer->TotalLength)
    {
      /* @Trace: PduR_SUD_API_149 */
      /* Set TailLength to SduPtr */
      ptrTxBuffer->TailLength = (PduLengthType)PDUR_ZERO;
    }
    else
    {
      /* No Action */
    }
  }
  else
  {
    /* @Trace: PduR_SUD_API_148 */
    /* Increment HeadLength */
    ptrTxBuffer->HeadLength += ptrQueue->PduInfoPtr.SduLength; /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
  }
  /* Set FirstQueuePtr to next queue */
  ptrTxBuffer->FirstQueuePtr = ptrQueue->Next; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
  ptrQueue->PduInfoPtr.SduDataPtr = NULL_PTR;
  ptrQueue->PduInfoPtr.MetaDataPtr = NULL_PTR;
  ptrQueue->PduInfoPtr.SduLength = 0xFFFF;
  ptrQueue->Next = NULL_PTR;
} /* End of PduR_IfFreeBuffer(
  P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
#endif /* #if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && \
  (PDUR_LO_TXCONFIRMATION == STD_ON)) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
