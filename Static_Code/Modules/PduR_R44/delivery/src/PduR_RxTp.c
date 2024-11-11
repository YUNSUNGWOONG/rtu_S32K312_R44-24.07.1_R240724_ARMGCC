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
**  SRC-MODULE: PduR_RxTp.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of the functionality of PduR_LoTpStartOfReception(),**
**              PduR_GWTpStartOfReception(),                                  **
**              PduR_BuffUpdateLoTpStartOfReception(),                        **
**              PduR_LoTpCopyRxData(), PduR_LoTpGWCopyRxData(),               **
**              PduR_BuffUpdateLoTpGWCopyRxData()                             **
**              PduR_DETCheckLoTpStartOfReception (),                         **
**              PduR_<Lo>TpRxIndication(), PduR_UpTpRxIndication()            **
**              PduR_DETCheckLoTpCopyRxData(), PduR_CheckPoolBuffer()         **
**              PduR_CheckBuffer(), PduR_FindPduIdQueue(),                    **
**              PduR_LowTpTransmit(), PduR_FreeBuffer(),                      **
**              PduR_DETCheckLoTpRxIndication(), PduR_DETCheckCancelReceive() **
**              and PduR_CancelReceive().                                     **
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
** 1.0.9.0_HF1 24-May-2024   Mj Kim      CP44-3752                            **
** 1.0.4       11-Aug-2022   PhucNHM     CP44-635                             **
** 1.0.2       05-Oct-2021   PhucNHM     R44-Redmine #20586                   **
** 1.0.1       22-Jun-2021   PhucNHM     R44-Redmine #18951                   **
** 1.0.0       04-Dec-2020   AUTOEVER    Initial Version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: PduR_SUD_FILE_001 */
#include "PduR.h"                 /* PDU router header file */
#include "PduR_RxTp.h"            /* PduR Rx Tp header */
#include "SchM_PduR.h"            /* SchM header */
#include "string.h"               /* memcpy() */
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
#if (PDUR_TP_RXINDICATION == STD_ON)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_GWTpStartOfReception( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
PduLengthType tpSduLength,
P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr,
PduIdType rxPduId,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* End of if (PDUR_TP_RXINDICATION == STD_ON) */

#if (PDUR_TP_RXINDICATION == STD_ON)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_BuffUpdateLoTpStartOfReception(
PduLengthType tpSduLength,
P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
PduIdType rxPduId);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* End of if (PDUR_TP_RXINDICATION == STD_ON) */

#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_TP_RXINDICATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DETCheckLoTpCopyRxData( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType rxPduId, uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
  P2CONST(PduLengthType, AUTOMATIC, PDUR_CONST) bufferSizePtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((PDUR_ZERO_COST_OPERATION == STD_OFF) &&
        *(PDUR_TP_RXINDICATION == STD_ON)) */
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */

#if ((PDUR_TP_GATEWAY_OPERATION == STD_ON) &&\
  (PDUR_ZERO_COST_OPERATION == STD_OFF))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpGWCopyRxData( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
    PduIdType rxPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */

#if ((PDUR_TP_GATEWAY_OPERATION == STD_ON) &&\
  (PDUR_ZERO_COST_OPERATION == STD_OFF))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_BuffUpdateLoTpGWCopyRxData( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
  PduIdType rxPduId);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */

#if ((PDUR_TP_RXINDICATION == STD_ON) && (PDUR_ZERO_COST_OPERATION == STD_OFF))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, PDUR_CODE) PduR_DETCheckLoTpRxIndication( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType rxPduId, uint8 moduleType);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((PDUR_ZERO_COST_OPERATION == STD_OFF) &&
        *(PDUR_TP_RXINDICATION == STD_ON)) */
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON) &&\
  (PDUR_TP_RXINDICATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_VAR) PduR_DETCheckCancelReceive( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType rxPduId);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif /* End of if ((PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON) &&
        *(PDUR_TP_RXINDICATION == STD_ON)) */
#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

#if ((PDUR_TP_RXINDICATION == STD_ON) && (PDUR_ZERO_COST_OPERATION == STD_OFF))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DETCheckLoTpStartOfReception( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType rxPduId, uint8 moduleType,
  P2CONST(PduLengthType, AUTOMATIC, PDUR_CONST) bufferSizePtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* */
#endif

#if ((PDUR_TP_UP_RX_SUPPORT == STD_ON) &&\
  (PDUR_ZERO_COST_OPERATION == STD_OFF))
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_UpTpRxIndication(
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu,
  P2CONST(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  P2CONST(PduR_TpQueueType, AUTOMATIC, PDUR_CONST) ptrQueue,
  Std_ReturnType result);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CheckPoolBuffer( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  PduLengthType tpSduLength);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#else
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CheckBuffer(
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  PduLengthType tpSduLength);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif /* End of if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(uint16, PDUR_CODE) PduR_FindPduIdQueue( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  PduIdType rxPduId);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_OFF) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_LowTpTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu,
  PduIdType rxPduId,
  uint8 serviceId);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* End of #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if(PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
static FUNC(void, PDUR_CODE) PduR_FreeBuffer( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  PduIdType rxPduId, uint8 serviceId);
#else
static FUNC(void, PDUR_CODE) PduR_FreeBuffer( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_TpBuffer, AUTOMATIC, PDUR_CONST) ptrTxBuffer,
  PduIdType rxPduId, uint8 serviceId);
#endif
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_TP_GATEWAY_OPERATION == STD_OFF) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : PduR_LoTpStartOfReception                           **
**                                                                            **
** Service ID           : 0x46                                                **
**                                                                            **
** Description          : This function will be called by the transport       **
**                        protocol module at the start of receiving an I-PDU. **
**                        The I-PDU might be fragmented into multiple N-PDUs  **
**                        (FF with one or more following CFs) or might        **
**                        consist of a single N-PDU (SF). The service shall   **
**                        provide the currently available maximum buffer size **
**                        when invoked with TpSdulength equal to 0.           **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType rxPduId, PduLengthType TpSduLength,       **
**                        uint8 moduleType, PduInfoType pduInfoPtr,           **
**                        PduLengthType* bufferSizePtr                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType bufReqReturn                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        PduR_LowTpRxIndication, PduR_LowTpStartOfReception, **
**                        PduR_LoRxConfig                                     **
**                                                                            **
** Function(s) invoked  : PduR_DETCheckLoTpStartOfReception(),                **
**                        PduR_GWTpStartOfReception()                         **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_PduR_06020 */
/* @Trace: SRS_PduR_06117 */
/* @Trace: SRS_BSW_00171 */
/* @Trace: SRS_BSW_00167 */
/* @Trace: SRS_BSW_00310 */
/* @Trace: SRS_PduR_06004 */
/* @Trace: SRS_PduR_06049 */
/* @Trace: SRS_PduR_06121 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_RXINDICATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
/* @Traceability BEGIN -- SRS: SWS_PduR_00715 SWS_PduR_00328 SWS_PduR_00507
                               SWS_PduR_00805 SWS_PduR_00804 SWS_PduR_00803
                               SWS_PduR_00799 SWS_PduR_00825 SWS_PduR_00826
                               SWS_PduR_00785 SWS_PduR_00307 SWS_PduR_00834
                               SWS_PduR_00832 SWS_PduR_00829 SWS_PduR_00806
                               SWS_PduR_00835 SWS_PduR_00830 SWS_PduR_00330
                               SWS_PduR_00670 SWS_PduR_00663 SWS_PduR_00798
                               SWS_PduR_00638 SWS_PduR_00623 SWS_PduR_00708
                               SWS_PduR_00794 SWS_PduR_00797 SWS_PduR_00823
                               SWS_PduR_00811 SWS_PduR_00549 SWS_PduR_00821
                               SWS_PduR_00673 SWS_PduR_00287 SWS_PduR_00161
                               SWS_PduR_00827 SWS_PduR_00100 SWS_PduR_00119
                               SWS_PduR_00221 SWS_PduR_00824 SWS_PduR_00003
                               SWS_PduR_00013 SWS_PduR_00014 SWS_PduR_00016
                               SWS_PduR_00017 SWS_PduR_00018 SWS_PduR_00019
                               SWS_PduR_00020 SWS_PduR_00022 SWS_PduR_00023
                               SWS_PduR_00764 */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpStartOfReception( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType rxPduId,
  uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
  PduLengthType tpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr)
#else
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpStartOfReception(
  PduIdType rxPduId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
  PduLengthType tpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr)
#endif
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) ptrTpRxIndication;
  BufReq_ReturnType bufReqReturn;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  bufReqReturn = PduR_DETCheckLoTpStartOfReception(rxPduId,
    moduleType, bufferSizePtr);
  /* Check whether any development errors are detected */
  if (BUFREQ_OK == bufReqReturn)
  #endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_358 */
    /* Get the pointer to ptrLoRxSource structure */
    ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
    /* Get the pointer to ptrTpRxIndication structure */
    ptrTpRxIndication = (P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST))
                          (ptrLoRxSource->LoIfTpSource);
    #else
    /* @Trace: PduR_SUD_API_065 */
    /* Get the pointer to TpRxIndication structure */
    ptrTpRxIndication = &PduR_LowTpRxIndication[rxPduId];
    #endif
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get routing path group id from struct data */
    groupIdValue = ptrTpRxIndication->GroupMaskValue;
    indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
    idConvert = groupIdValue % PDUR_BITMASK_UINT8;
    /* @Trace: SRS_PduR_06120 */
    /* Check if routing path is enabled */
    if ((PDUR_UNDEFINED == groupIdValue) ||
        ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] & /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
                                          (((uint32)PDUR_ONE) << idConvert))))
    #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
    {
      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of TargetIndexOrNoOfRoute is generated by generator and has checked that have no impact" */
      if ((uint8)PDUR_ZERO == ((ptrTpRxIndication->TargetIndexOrNoOfRoute) &
                               PDUR_NONGATEWAY_MASK))
      { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
        #if (PDUR_TP_UP_RX_SUPPORT == STD_ON)
        /* Invoke Upper layer StartOfReception() API */
        /* @Trace: SRS_PduR_06104 */
        if(PduR_LowTpStartOfReception[ptrTpRxIndication->TargetIndexOrNoOfRoute
           & (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
        {
          /* @Trace: PduR_SUD_API_274 */
          bufReqReturn =
            PduR_LowTpStartOfReception[
              ptrTpRxIndication->TargetIndexOrNoOfRoute
              & (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer(
              (ptrTpRxIndication->UpTargetPduId), pduInfoPtr,
              tpSduLength, bufferSizePtr);
        }
        else
        #endif   /*end of if (PDUR_TP_UP_RX_SUPPORT == STD_ON)*/
        {
          bufReqReturn = BUFREQ_E_NOT_OK;
        }
      } /* End of if ((uint8)PDUR_ZERO ==
      *((ptrTpRxIndication->TargetIndexOrNoOfRoute) & */
      #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
      else
      {
        /* @Trace: PduR_SUD_API_273 */
        bufReqReturn = PduR_GWTpStartOfReception(tpSduLength,
          bufferSizePtr, rxPduId, pduInfoPtr);
      } /* End of else */
      #endif /* End of if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
    }
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    else
    { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
      /* @Trace: PduR_SUD_API_272 */
      bufReqReturn = BUFREQ_E_NOT_OK;
    }
    #endif
  }
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No Action */
    /* @Trace: PduR_SUD_API_271 */
  }
  #endif
  /* return with the BufReqReturn */
  return (bufReqReturn);
} /* End of PduR_LoTpStartOfReception(PduIdType rxPduId,
   * P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
   * PduLengthType tpSduLength,
   * P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr) */
/* @Traceability END -- SRS:   SWS_PduR_00715 SWS_PduR_00328 SWS_PduR_00507
                               SWS_PduR_00805 SWS_PduR_00804 SWS_PduR_00803
                               SWS_PduR_00799 SWS_PduR_00825 SWS_PduR_00826
                               SWS_PduR_00785 SWS_PduR_00307 SWS_PduR_00834
                               SWS_PduR_00832 SWS_PduR_00829 SWS_PduR_00806
                               SWS_PduR_00835 SWS_PduR_00830 SWS_PduR_00330
                               SWS_PduR_00670 SWS_PduR_00663 SWS_PduR_00798
                               SWS_PduR_00638 SWS_PduR_00623 SWS_PduR_00708
                               SWS_PduR_00794 SWS_PduR_00797 SWS_PduR_00823
                               SWS_PduR_00811 SWS_PduR_00549 SWS_PduR_00821
                               SWS_PduR_00673 SWS_PduR_00287 SWS_PduR_00161
                               SWS_PduR_00827 SWS_PduR_00100 SWS_PduR_00119
                               SWS_PduR_00221 SWS_PduR_00824 SWS_PduR_00003
                               SWS_PduR_00013 SWS_PduR_00014 SWS_PduR_00016
                               SWS_PduR_00017 SWS_PduR_00018 SWS_PduR_00019
                               SWS_PduR_00020 SWS_PduR_00022 SWS_PduR_00023
                               SWS_PduR_00764 */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_TP_RXINDICATION == STD_ON) */
#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
** Function Name        : PduR_GWTpStartOfReception                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpStartOfReception function in case of       **
**                        gateway.                                            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduLengthType tpSduLength                           **
**                        PduLengthType* bufferSizePtr                        **
**                        PduIdType rxPduId                                   **
**                        PduInfoType* pduInfoPtr                             **
**                                                                            **
** InOut parameter      : PduLengthType* bufferSizePtr                        **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType bufReqReturn                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_LowTpRxIndication,                             **
**                        PduR_TpTxBuffer, PduR_TpBufferConfig,               **
**                        PduR_LoRxConfig                                     **
**                                                                            **
** Function(s) invoked  : PduR_BuffUpdateLoTpStartOfReception()               **
**                        PduR_CheckPoolBuffer(), PduR_CheckBuffer()          **
**                        PduR_LowTpTransmit(), PduR_FreeBuffer               **
**                                                                            **
*******************************************************************************/
#if ((PDUR_TP_GATEWAY_OPERATION == STD_ON) &&\
  (PDUR_ZERO_COST_OPERATION == STD_OFF))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_GWTpStartOfReception( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
PduLengthType tpSduLength,
P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr,
PduIdType rxPduId,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr)
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) ptrTpRxIndication;
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu;
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;
  #if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON)
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif
  Std_ReturnType returnAllTxVal;
  returnAllTxVal = (Std_ReturnType)E_NOT_OK;
  uint8 noOfRoutePdu;
  #endif
  BufReq_ReturnType bufReqReturn;
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* @Trace: PduR_SUD_API_377 */
  /* Get the pointer to ptrLoRxSource structure */
  ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
  /* Get the pointer to ptrTpRxIndication structure */
  ptrTpRxIndication = (P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST))
                        (ptrLoRxSource->LoIfTpSource);
  /* Assign Local Pointer to LoGWRxIndication Structure */
  ptrGWTpPdu = ptrTpRxIndication->GWRxTpPdu;
  /* Get pointer to Tx Buffer Structure */
  ptrTxBuffer = &PduR_TpBufferConfig[ptrGWTpPdu->TxBufferIndex];
  #else
  /* @Trace: PduR_SUD_API_376 */
  /* Get the pointer to TpRxIndication structure */
  ptrTpRxIndication = &PduR_LowTpRxIndication[rxPduId];
  /* Assign Local Pointer to LoGWRxIndication Structure */
  ptrGWTpPdu = ptrTpRxIndication->GWRxTpPdu;
  /* Get pointer to Tx Buffer Structure */
  ptrTxBuffer = &PduR_TpTxBuffer[ptrGWTpPdu->TxBufferIndex];
  #endif
  #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
  /* @Trace: PduR_SUD_API_379 */
  /* Check buffer of routing path are pool and valid */
  bufReqReturn = PduR_CheckPoolBuffer(ptrTxBuffer, tpSduLength);
  #else
  /* @Trace: PduR_SUD_API_378 */
  /* Check buffer of routing path is valid */
  bufReqReturn = PduR_CheckBuffer(ptrTxBuffer, tpSduLength);
  #endif

  if ((BufReq_ReturnType)BUFREQ_OK == bufReqReturn)
  {
    /* Update buffer of routing path for gateway */
    bufReqReturn = PduR_BuffUpdateLoTpStartOfReception(
      tpSduLength, bufferSizePtr, pduInfoPtr, rxPduId);
    /* check gateway on-the-fly is supported*/
    #if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON)
    /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of bufReqReturn could be changed in case buffer error" */
    if ((BufReq_ReturnType)BUFREQ_OK == bufReqReturn)
    {
      /* @Trace: PduR_SUD_API_276 */
      /* Get the Number of Route for Source PDU */
      noOfRoutePdu = (ptrTpRxIndication->TargetIndexOrNoOfRoute &
                    (uint8)PDUR_NOOFROUTE_MASK);
      /* Loop for the Number of Route of the Source PDU */
      /* @Trace: SRS_PduR_06029 */
      do
      {
        #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
        /* Get routing path group id from data struct */
        groupIdValue = ptrGWTpPdu->GroupMaskValue; /* polyspace RTE:IDP [Not a defect:Low] "configured memory access index" */
        indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
        idConvert = groupIdValue % PDUR_BITMASK_UINT8;
        /* @Trace: SRS_PduR_06120 */
        /* Check if routing path is enabled */
        if ((PDUR_UNDEFINED == groupIdValue) ||
          ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] &
                                          (((uint32)PDUR_ONE) << idConvert))))
        #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
        {
          /* Check routing isn't reception to upper */
          if ((uint8)PDUR_ZERO == ((ptrGWTpPdu->TargetIndexBufType) &
                                                        PDUR_UPPERLAYER_MASK))
          {
            /* Init state of transmit in case of gateway on-the-fly */
            (*(ptrGWTpPdu->RamArea)) = PDUR_RX_TX_NOT_COMPLETED;
            /* @Trace: SRS_PduR_06026 */
            if ((uint8)PDUR_ZERO == ptrGWTpPdu->TpThreshold)
            {
              /* @Trace: PduR_SUD_API_280 */
              returnAllTxVal = returnAllTxVal & PduR_LowTpTransmit(
                ptrTxBuffer, ptrGWTpPdu, rxPduId, PDUR_STARTOF_RECEPTION_SID);
            }
            else
            {
              /* @Trace: PduR_SUD_API_283 */
              returnAllTxVal = (Std_ReturnType)E_OK;
            }
          }
          else
          {
            /* @Trace: PduR_SUD_API_279 */
            returnAllTxVal = (Std_ReturnType)E_OK;
          }
        }
        #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
        else
        {
          /* @Trace: PduR_SUD_API_277 */
          /* No Action */
        }
        #endif
        /* Increment the ptrGWTpPdu Pointer */
        ptrGWTpPdu++;
        /* Decrement the Number of Route PDU */
        noOfRoutePdu--;
      } while ((uint8)PDUR_ZERO != noOfRoutePdu);
      /* Free PduR buffer when all destination failed */
      /* @Trace: SRS_PduR_06105 */
      if ((Std_ReturnType)E_OK != returnAllTxVal)
      {
        /* @Trace: PduR_SUD_API_282 */
        *bufferSizePtr = tpSduLength; /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "bufferSizePtr is checked null by PduR_DETCheckLoTpStartOfReception function" */
        PduR_FreeBuffer(ptrTxBuffer, rxPduId, PDUR_STARTOF_RECEPTION_SID);
        bufReqReturn = BUFREQ_E_NOT_OK;
      }
      else
      {
        /* @Trace: PduR_SUD_API_281 */
        bufReqReturn = BUFREQ_OK;
      }
    }
    else
    #endif /* #if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON) */
    {
      /* No Action */
    }
  }
  else
  {
    /* @Trace: PduR_SUD_API_275 */
    /* No Action */
  }
  return(bufReqReturn);
} /* End of PduR_GWLoRxIndication(PduLengthType tpSduLength,
   * P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr,
   * PduIdType rxPduId,
   * P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if ((PDUR_TP_GATEWAY_OPERATION == STD_ON) &&
        * (PDUR_ZERO_COST_OPERATION == STD_OFF)) */
/*******************************************************************************
** Function Name        : PduR_BuffUpdateLoTpStartOfReception                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_GWTpStartOfReception function                  **
**                        to update the TP buffers.                           **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduLengthType tpSduLength                           **
** Input Parameters     : PduLengthType* bufferSizePtr                        **
** Input Parameters     : PduInfoType* pduInfoPtr                             **
** Input Parameters     : PduIdType rxPduId                                   **
**                                                                            **
** InOut parameter      : PduLengthType* bufferSizePtr                        **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): PduR_LowTpRxIndication,         **
**                        PduR_TpTxBuffer, PduR_TpTxQueue, PduR_PoolPtr,      **
**                        PduR_LoRxConfig, PduR_TpBufferConfig                **
**                                                                            **
** Function(s) invoked  : SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA()       **
**                        SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA()        **
**                        SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA()       **
**                        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA()        **
**                        PduR_FindPduIdQueue()                               **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_BuffUpdateLoTpStartOfReception
(PduLengthType tpSduLength,
P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
PduIdType rxPduId)
{
  /* @Trace: SRS_PduR_06026 */
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) ptrTpRxIndication;
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu;
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;
  #if ((PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON))
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) nextQueue;
  uint16 indexFifoPduId;
  uint8 indexDepth;
  indexDepth = (uint8)PDUR_ZERO;
  #endif
  BufReq_ReturnType bufReqReturn;
  bufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
  #if (PDUR_META_DATA_SUPPORT == STD_ON)
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) ptrMetaDataBuffer;
  #endif
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* @Trace: PduR_SUD_API_381 */
  /* Get the pointer to ptrLoRxSource structure */
  ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
  /* Get the pointer to ptrTpRxIndication structure */
  ptrTpRxIndication = (P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST))
                        (ptrLoRxSource->LoIfTpSource);
  /* Assign Local Pointer to LoGWRxIndication Structure */
  ptrGWTpPdu = ptrTpRxIndication->GWRxTpPdu;
  /* Get the pointer to Tx Buffer structure */
  ptrTxBuffer = &PduR_TpBufferConfig[ptrGWTpPdu->TxBufferIndex];
  #else
  /* @Trace: PduR_SUD_API_380 */
  /* Get the pointer to TpRxIndication structure */
  ptrTpRxIndication = &PduR_LowTpRxIndication[rxPduId];
  /* Assign Local Pointer to LoGWRxIndication Structure */
  ptrGWTpPdu = ptrTpRxIndication->GWRxTpPdu;
  /* Get the pointer to Tx Buffer structure */
  ptrTxBuffer = &PduR_TpTxBuffer[ptrGWTpPdu->TxBufferIndex];
  #endif
  #if(PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  if (NULL_PTR == ptrTxBuffer->SinBufPtr)
  {
    /* Enter critical area */
    #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
    /* @Trace: SRS_BSW_00312 */
    SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA();
    #endif
    /* @Trace: SRS_PduR_06127 */
    if (NULL_PTR == ptrTxBuffer->FirstQueuePtr)
    {
      ptrQueue = &PduR_TpTxQueue[ptrGWTpPdu->TxQueueIndex];
      /* @Trace: SRS_PduR_06124 */
      #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
      if ((boolean)PDUR_TRUE == PduR_PoolVar.PoolStatus)
      {
        /* @Trace: PduR_SUD_API_301 */
        ptrQueue->PduInfoPtr.SduDataPtr =
          PduR_PoolPtr[PduR_PoolVar.IndexPool].SduPtr; /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "index poor support range from 0..255" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
        /* Update IndexSduPtr */
        ptrTxBuffer->IndexSduPtr = ptrTxBuffer->SduPtr;
      }
      else
      #endif
      {
        /* @Trace: PduR_SUD_API_300 */
        ptrQueue->PduInfoPtr.SduDataPtr = ptrTxBuffer->SduPtr;
        /* Update IndexSduPtr */
        ptrTxBuffer->IndexSduPtr = &ptrTxBuffer->SduPtr[tpSduLength];
      }
      /* Check Meta Data is support */
      #if(PDUR_META_DATA_SUPPORT == STD_ON)
      if (NULL_PTR != ptrTxBuffer->MetaPtr)
      {
        /* @Trace: PduR_SUD_API_302 */
        /* Update pointer MetaDataPtr of PduInfoPtr */
        ptrQueue->PduInfoPtr.MetaDataPtr = ptrTxBuffer->MetaPtr;
        /* Increment IndexMetaPtr */
        ptrTxBuffer->IndexMetaPtr = 
          &ptrTxBuffer->MetaPtr[ptrGWTpPdu->MetaDataLength];
      }
      else
      {
        /* @Trace: PduR_SUD_API_303 */
        ptrMetaDataBuffer = NULL_PTR;
      }
      #else
      /* Update pointer MetaDataPtr of PduInfoPtr */
      ptrQueue->PduInfoPtr.MetaDataPtr = NULL_PTR;
      #endif
      ptrQueue->PduInfoPtr.SduLength = tpSduLength;
      /* Init index list in queue */
      ptrQueue->IndexList = (uint8)PDUR_ZERO;
      /* Add first queue */
      ptrTxBuffer->FirstQueuePtr = ptrQueue;
      /* Set TailLength to zero*/
      ptrTxBuffer->TailLength  = (PduLengthType)PDUR_ZERO;
      /* Update HeadLength */
      ptrTxBuffer->HeadLength = ptrTxBuffer->HeadLength - tpSduLength;
    }
    else
    {
      /* @Trace: SRS_PduR_06127 */
      indexFifoPduId = PduR_FindPduIdQueue(ptrTxBuffer, rxPduId);
      /* Check Pdu Id is valid in fifo buffer */
      if (PDUR_UNDEFINED == indexFifoPduId)
      {
        /* Allocation for next queue */
        do
        {
          /* @Trace: PduR_SUD_API_307 */
          indexDepth++;
          ptrQueue = &PduR_TpTxQueue[ptrGWTpPdu->TxQueueIndex +
              indexDepth];
        }
        while ((boolean)PDUR_TRUE == ptrQueue->FreeBuffer); /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:IDP [Not a defect:Low] "configured memory access index" */
        /* check remain buffer is greater length of PduInforPtr */
        /* @Trace: SRS_PduR_06124 */
        if (ptrTxBuffer->HeadLength >= tpSduLength)
        {
          /* @Trace: PduR_SUD_API_308 */
          /* Update PduInfoPtr in tx queue buffer */
          ptrQueue->PduInfoPtr.SduDataPtr = ptrTxBuffer->IndexSduPtr;
          ptrQueue->PduInfoPtr.SduLength = tpSduLength;
          /* Update IndexSduPtr in tx queue buffer */
          ptrTxBuffer->IndexSduPtr = &ptrTxBuffer->IndexSduPtr[tpSduLength];
          /* Update HeadLength in tx queue buffer */
          ptrTxBuffer->HeadLength = ptrTxBuffer->HeadLength - tpSduLength;
        }
        else if (ptrTxBuffer->TailLength >= tpSduLength)
        {
          /* @Trace: PduR_SUD_API_310 */
          /* Set IndexSduPtr to SduPtr of tx queue buffer */
          ptrTxBuffer->IndexSduPtr = ptrTxBuffer->SduPtr;
          /* Set HeadLength to TailLength */
          ptrTxBuffer->HeadLength  = ptrTxBuffer->TailLength - tpSduLength;
          /* Set TailLength to zero */
          ptrTxBuffer->TailLength = (PduLengthType)PDUR_ZERO;
          /* Update PduInfoPtr in tx queue buffer */
          ptrQueue->PduInfoPtr.SduDataPtr = ptrTxBuffer->IndexSduPtr;
          ptrQueue->PduInfoPtr.SduLength = tpSduLength;
          /* Update IndexMetaPtr */
          #if (PDUR_META_DATA_SUPPORT == STD_ON)
          ptrTxBuffer->IndexMetaPtr = ptrTxBuffer->MetaPtr;
          #endif
          /* Update IndexSduPtr in tx queue buffer */
          ptrTxBuffer->IndexSduPtr = &ptrTxBuffer->IndexSduPtr[tpSduLength];
        }
        else
        {
          #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
          /* @Trace: PduR_SUD_API_309 */
          ptrQueue->PduInfoPtr.SduDataPtr =
            PduR_PoolPtr[PduR_PoolVar.IndexPool].SduPtr; /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "index poor support range from 0..255" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
          ptrQueue->PduInfoPtr.SduLength = tpSduLength;
          #endif
        }
        /* Check Meta Data is support */
        #if(PDUR_META_DATA_SUPPORT == STD_ON)
        if (NULL_PTR != ptrTxBuffer->MetaPtr)
        {
          /* @Trace: PduR_SUD_API_312 */
          /* Update pointer MetaDataPtr of PduInfoPtr */
          ptrQueue->PduInfoPtr.MetaDataPtr = ptrTxBuffer->IndexMetaPtr;
          /* Increment IndexMetaPtr */
          ptrTxBuffer->IndexMetaPtr = &ptrTxBuffer->IndexMetaPtr[ptrGWTpPdu->MetaDataLength];
        }
        else
        {
          /* @Trace: PduR_SUD_API_311 */
          ptrMetaDataBuffer = NULL_PTR;
        }
        #else
        /* Update pointer MetaDataPtr of PduInfoPtr */
        ptrQueue->PduInfoPtr.MetaDataPtr = NULL_PTR;
        #endif
        nextQueue = ptrTxBuffer->FirstQueuePtr;
        /* Added next queue */
        while (nextQueue->Next != NULL_PTR) { /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:IDP [Not a defect:Low] "configured memory access index" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
          nextQueue = nextQueue->Next;
        }
        /* Increment index list in queue */
        ptrQueue->IndexList = nextQueue->IndexList + (uint8)PDUR_ONE; /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
        nextQueue->Next = ptrQueue;
      }
      else
      {
        /* @Trace: PduR_SUD_API_306 */
        bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
      }
    }
    if ((BufReq_ReturnType)BUFREQ_E_NOT_OK != bufReqReturn)
    {
      /* @Trace: PduR_SUD_API_313 */
      /* Get index in fifo buffer */
      ptrQueue->IndexFifo     = ptrGWTpPdu->TxQueueIndex + indexDepth;
      ptrQueue->FreeBuffer    = PDUR_TRUE;
      ptrQueue->RxPduId       = rxPduId;
      ptrQueue->Next          = NULL_PTR;
      ptrQueue->ReqLength     = tpSduLength;
      ptrQueue->AvailLength   = tpSduLength;
      ptrQueue->CopiedLength  = (uint8)PDUR_ZERO;
      ptrQueue->RxState       = PDUR_RX_IN_PROGRESS;
      #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
      ptrQueue->IndexPool     = PduR_PoolVar.IndexPool;
      ptrQueue->PoolStatus    = PduR_PoolVar.PoolStatus;
      #endif
      ptrTxBuffer->CurrentDepth++;
      /* Get the Meta data pointer from Tx queue */
      #if(PDUR_META_DATA_SUPPORT == STD_ON)
      ptrMetaDataBuffer = ptrQueue->PduInfoPtr.MetaDataPtr;
      #endif
    }
    else
    {
      /* No Action */
    }
    /* Exit critical area */
    #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA();
    #endif
  }
  else
  #endif /* #if(PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON) */
  {
        /* @Trace: PduR_SUD_API_305 */
    /* Get the Meta data pointer from Tx Buffer */
    #if(PDUR_META_DATA_SUPPORT == STD_ON)
    ptrMetaDataBuffer = ptrTxBuffer->MetaPtr;
    #endif
    ptrTxBuffer->SinBufPtr->ReqLength    = tpSduLength; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
    ptrTxBuffer->SinBufPtr->AvailLength  = tpSduLength; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
    ptrTxBuffer->SinBufPtr->CopiedLength = (uint8)PDUR_ZERO; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
    ptrTxBuffer->SinBufPtr->RxState      = PDUR_RX_IN_PROGRESS; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
    ptrTxBuffer->SinBufPtr->FreeBuffer   = (boolean)PDUR_TRUE; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
    #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
    ptrTxBuffer->SinBufPtr->PoolStatus   = PduR_PoolVar.PoolStatus; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
    ptrTxBuffer->SinBufPtr->IndexPool    = PduR_PoolVar.IndexPool; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
    #endif
  }
  /* Check pduInfoPtr not NULL_PTR */
  /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of bufReqReturn could be changed in case buffer error" */
  if ((BufReq_ReturnType)BUFREQ_OK == bufReqReturn)
  {
    if (pduInfoPtr != NULL_PTR)
    {
      #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
      SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
      #endif
      #if(PDUR_META_DATA_SUPPORT == STD_ON)
      if ((NULL_PTR != ptrMetaDataBuffer) &&
        (NULL_PTR != pduInfoPtr->MetaDataPtr)) /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "pduInfoPtr is checked null by PduR_DETCheckLoTpStartOfReception function" */
      {
            /* @Trace: PduR_SUD_API_316 */
        /* Copy Meta data from I-PDU to buffer */
        memcpy((P2VAR(void, AUTOMATIC, PDUR_VAR))(ptrMetaDataBuffer), /* polyspace MISRA-C:2012 D4.11 [Not a defect:Low] "all input function are valid due to data flow" */ /* polyspace RTE:STD_LIB [Not a defect:Low] "all input function are valid due to data flow" */
          (P2CONST(void, AUTOMATIC, PDUR_CONST))(pduInfoPtr->MetaDataPtr), /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "pduInfoPtr is checked null by PduR_DETCheckLoTpStartOfReception function" */
          ptrGWTpPdu->MetaDataLength);
      }
      else
      {
            /* @Trace: PduR_SUD_API_317 */
        ptrMetaDataBuffer = NULL_PTR;
      }
      #endif
      #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
      SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
      #endif
    }
    else
    {
      /* No Action */
    }
    if ((boolean)PDUR_ZERO == tpSduLength)
    {
      *bufferSizePtr = ptrTxBuffer->TotalLength;

      #if(PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
      if (NULL_PTR == ptrTxBuffer->SinBufPtr)
      {
        /* @Trace: PduR_SUD_API_323 */
        ptrTxBuffer->CurrentDepth = ptrTxBuffer->FIFODepth;
        ptrQueue->AvailLength = *bufferSizePtr; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
      }
      else
      #endif
      {
        /* @Trace: PduR_SUD_API_322 */
        ptrTxBuffer->SinBufPtr->AvailLength = *bufferSizePtr; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
      }
    }
    else
    {
      #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
      if (NULL_PTR == ptrTxBuffer->SinBufPtr)
      {
        /* @Trace: PduR_SUD_API_320 */
        *bufferSizePtr = ptrQueue->AvailLength; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
      }
      else
      #endif
      {
        /* @Trace: PduR_SUD_API_321 */
        *bufferSizePtr = ptrTxBuffer->SinBufPtr->AvailLength; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
      }
    }
  }
  else
  {
    /* No Action */
  }
  return bufReqReturn;
} /* End of PduR_BuffUpdateLoTpStartOfReception(PduLengthType tpSduLength,
   *P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_LoTpCopyRxData                                 **
**                                                                            **
** Service ID           : 0x44                                                **
**                                                                            **
** Description          : This service is called by the TP for requesting     **
**                        a new buffer (pointer to a PduInfoStructure         **
**                        containing a pointer to a SDU buffer and the buffer **
**                        length) for the TP to fill in the received          **
**                        data.                                               **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType rxPduId, uint8 moduleType,                **
**                        PduInfoType* pduInfoPtr,                            **
**                        PduLengthType*  bufferSizePtr                       **
**                                                                            **
** InOut parameter      : PduLengthType*  bufferSizePtr                       **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType  bufReqReturn                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        PduR_LowTpRxIndication, PduR_LowTpCopyRxData        **
**                        PduR_LoRxConfig                                     **
**                                                                            **
** Function(s) invoked  : PduR_DETCheckLoTpCopyRxData()                       **
**                        PduR_LoTpGWCopyRxData()                             **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_PduR_06020 */
/* @Trace: SRS_PduR_06117 */
/* @Trace: SRS_BSW_00171 */
/* @Trace: SRS_BSW_00167 */
/* @Trace: SRS_BSW_00310 */
/* @Trace: SRS_PduR_06121 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_RXINDICATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
/* @Traceability BEGIN -- SRS: SWS_PduR_00805 SWS_PduR_00804 SWS_PduR_00004
                               SWS_PduR_00825 SWS_PduR_00830 SWS_PduR_00708
                               SWS_PduR_00831 SWS_PduR_00317 SWS_PduR_00740
                               SWS_PduR_00687 SWS_PduR_00428 SWS_PduR_00287
                               SWS_PduR_00161 SWS_PduR_00827 SWS_PduR_00834
                               SWS_PduR_00806 SWS_PduR_00328 SWS_PduR_00330
                               SWS_PduR_00715 SWS_PduR_00100 SWS_PduR_00119
                               SWS_PduR_00221 SWS_PduR_00512 SWS_PduR_00824
                               SWS_PduR_00013 SWS_PduR_00017 SWS_PduR_00794
                               SWS_PduR_00018 SWS_PduR_00022 SWS_PduR_00764 */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyRxData(PduIdType rxPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr)
#else
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyRxData(PduIdType rxPduId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr)
#endif
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  /*Local pointer to generated array of Structure type - PduR_TpRxIndication */
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) ptrTpRxIndication;
  BufReq_ReturnType bufReqReturn;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  bufReqReturn = PduR_DETCheckLoTpCopyRxData(rxPduId, moduleType,
    pduInfoPtr, bufferSizePtr);
  /* Check whether any development errors are detected */
  if (BUFREQ_OK == bufReqReturn)
  #endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_362 */
    /* Get the pointer to ptrLoRxSource structure */
    ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
    /* Get the pointer to ptrTpRxIndication structure */
    ptrTpRxIndication = (P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST))
                               (ptrLoRxSource->LoIfTpSource);
    #else
    /* @Trace: PduR_SUD_API_361 */
    /* Get the pointer to TpRxIndication structure */
    ptrTpRxIndication = &PduR_LowTpRxIndication[rxPduId];
    #endif
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get routing path group id from data struct */
    groupIdValue = ptrTpRxIndication->GroupMaskValue;
    indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
    idConvert = groupIdValue % PDUR_BITMASK_UINT8;
    /* @Trace: SRS_PduR_06120 */
    /* Check if routing path is enabled */
    if ((PDUR_UNDEFINED == groupIdValue) ||
      ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] & /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
                                          (((uint32)PDUR_ONE) << idConvert))))
    #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
    {
      /* Check if gateway */
      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of TargetIndexOrNoOfRoute is generated by generator and has checked that have no impact" */
      if ((uint8)PDUR_ZERO == (ptrTpRxIndication->TargetIndexOrNoOfRoute &
                                                  (uint8)PDUR_NONGATEWAY_MASK))
      { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
        /* Requirement PDUR428 */
        #if (PDUR_TP_UP_RX_SUPPORT == STD_ON)
        /* Invoke Upper Layer CopyRxData() API */
        /* @Trace: SRS_PduR_06104 */
        if(PduR_LowTpCopyRxData[ptrTpRxIndication->TargetIndexOrNoOfRoute].
                                                    TargetLayer != NULL_PTR)
        {
          /* @Trace: PduR_SUD_API_204 */
          bufReqReturn = PduR_LowTpCopyRxData[
            ptrTpRxIndication->TargetIndexOrNoOfRoute].TargetLayer
                                      (ptrTpRxIndication->UpTargetPduId,
                                       pduInfoPtr, bufferSizePtr);
        }
        else
        #endif
        {
          bufReqReturn = BUFREQ_E_NOT_OK;
        }
      } /* End of if (PDUR_ZERO == */
      #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
      else
      {
        /* @Trace: PduR_SUD_API_203 */
        bufReqReturn = PduR_LoTpGWCopyRxData(
                              rxPduId, pduInfoPtr, bufferSizePtr);
      } /* End of else */
      #endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
      /* Set the receive status to In progress */
    }
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    else
    { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
      /* @Trace: PduR_SUD_API_202 */
      bufReqReturn = BUFREQ_E_NOT_OK;
    }
    #endif
  }
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* @Trace: PduR_SUD_API_201 */
    /* No Action */
  }
  #endif
  /* return with the BufReqReturn */
  return (bufReqReturn);
} /* End of PduR_LoTpCopyRxData(PduIdType rxPduId, P2VAR(PduInfoType,
   *AUTOMATIC, PDUR_VAR) pduInfoPtr, P2VAR(PduLengthType, AUTOMATIC,
   *PDUR_VAR) bufferSizePtr) */
/* @Traceability END -- SRS: SWS_PduR_00805 SWS_PduR_00804 SWS_PduR_00004
                               SWS_PduR_00825 SWS_PduR_00830 SWS_PduR_00708
                               SWS_PduR_00831 SWS_PduR_00317 SWS_PduR_00740
                               SWS_PduR_00687 SWS_PduR_00428 SWS_PduR_00287
                               SWS_PduR_00161 SWS_PduR_00827 SWS_PduR_00834
                               SWS_PduR_00806 SWS_PduR_00328 SWS_PduR_00330
                               SWS_PduR_00715 SWS_PduR_00100 SWS_PduR_00119
                               SWS_PduR_00221 SWS_PduR_00512 SWS_PduR_00824
                               SWS_PduR_00013 SWS_PduR_00017 SWS_PduR_00794
                               SWS_PduR_00018 SWS_PduR_00022 SWS_PduR_00764 */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*  #if (PDUR_TP_RXINDICATION == STD_ON)  */
#endif  /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF)  */

/*******************************************************************************
** Function Name        : PduR_DETCheckLoTpCopyRxData                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpCopyRxData function                        **
**                        to check the parameters passed are valid and        **
**                        buffer does not need to be the length of the        **
**                        report to DET in case of invalid values.            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType rxPduId, uint8 moduleType,                **
**                        PduInfoType* pduInfoPtr,                            **
**                        PduLengthType* bufferSizePtr, boolean ifRouting     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType bufReqReturn                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_InitStatus, PduR_LowTpRxIndication             **
**                        PduR_IfTpRxIndicationMaxPduId, PduR_LoRxConfig      **
**                                                                            **
** Function(s) invoked  : Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_TP_RXINDICATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
 static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DETCheckLoTpCopyRxData( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType rxPduId, uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
  P2CONST(PduLengthType, AUTOMATIC, PDUR_CONST) bufferSizePtr)
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) ptrTpRxIndication;
  BufReq_ReturnType bufReqReturn;
  /* Initialize buffer return type to "BUFREQ_OK" */
  bufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
  /* Check whether the module is initialised */
  if (PDUR_UNINIT == PduR_InitStatus)
  {
    /* @Trace: SRS_BSW_00406 */
    /* @Trace: PduR_SUD_API_212 */
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_COPYRX_DATA_SID, PDUR_E_UNINIT);
    /* Set the return value to BUFREQ_E_NOT_OK */
    bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
  } /* End of if (PDUR_UNINIT == PduR_InitStatus) */
  else
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_366 */
    if (rxPduId >= PduR_IfTpRxIndicationMaxPduId)
    #else
    /* @Trace: PduR_SUD_API_365 */
    if (rxPduId >= PDUR_TP_RXINDICATION_MAXPDUID)
    #endif
    {
      /* Report to DET */
      /* @Trace: SRS_PduR_06103 */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_COPYRX_DATA_SID, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
    } /* End of if (rxPduId >= PDUR_TP_RXINDICATION_MAXPDUID) */
    else
    {
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_OFF)
      /* Get the pointer to TpRxIndication structure */
      ptrTpRxIndication = &PduR_LowTpRxIndication[rxPduId];
      #else
      /* Get the pointer to ptrLoRxSource structure */
      ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
      /* Get the pointer to ptrTpRxIndication structure */
      ptrTpRxIndication = (P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST))
                               (ptrLoRxSource->LoIfTpSource);
      if ((boolean)PDUR_FALSE !=
                              (boolean)ptrLoRxSource->IsInterfaceRouting)
      {
          /* Report to DET */
          /* @Trace: SRS_PduR_06103 */
          /* @Trace: PduR_SUD_API_367 */
          (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
            PDUR_COPYRX_DATA_SID, PDUR_E_PDU_ID_INVALID);
          /* Set the error flag to TRUE */
          bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
      }
      else
      #endif
      {
        if (ptrTpRxIndication->ModuleType != moduleType)
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* Report to DET */
          /* @Trace: SRS_PduR_06103 */
          /* @Trace: PduR_SUD_API_214 */
          (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
            PDUR_COPYRX_DATA_SID, PDUR_E_PDU_ID_INVALID);
          /* Set the error flag to TRUE */
          bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
        }
        else
        {
          #if(PDUR_TP_GATEWAY_OPERATION == STD_ON)
          /* Check routing is gateway */
          if ((uint8)PDUR_ZERO != ((ptrTpRxIndication->TargetIndexOrNoOfRoute) & /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
            PDUR_GATEWAY_MASK))
          {
            /* Check If PduInfoPtr is NULL_PTR */
            if (NULL_PTR == pduInfoPtr)
            {
              /* Report to DET */
              /* @Trace: PduR_SUD_API_422 */
              (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                PDUR_COPYRX_DATA_SID, PDUR_E_PARAM_POINTER);
              /* Set the return value to BUFREQ_E_NOT_OK */
              bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
            } /* End of if (NULL_PTR == pduInfoPtr) */
            else
            {
              if (((uint8)PDUR_ZERO != pduInfoPtr->SduLength) && /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "pduInfoPtr is checked null" */
                (NULL_PTR == pduInfoPtr->SduDataPtr))
              {
                /* @Trace: PduR_SUD_API_215 */
                /* Report to DET */
                (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                PDUR_COPYRX_DATA_SID, PDUR_E_PARAM_POINTER);
                /* Set the return value to BUFREQ_E_NOT_OK  */
                bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
              } /* End of if (NULL_PTR == pduInfoPtr->SduDataPtr) */
              else
              {
                /* No Action */
              }
            }
            /* Check If bufferSizePtr is NULL_PTR */
            if (NULL_PTR == bufferSizePtr)
            {
              /* @Trace: PduR_SUD_API_216 */
              /* Report to DET */
              (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                PDUR_COPYRX_DATA_SID, PDUR_E_PARAM_POINTER);
              /* Set the return value to BUFREQ_E_NOT_OK  */
              bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
            } /* End of if (NULL_PTR == bufferSizePtr) */
            else
            {
              /* No Action */
            }
          }
          else
          #endif
          { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
            /* No Action */
          }
        }
      }
    }
  }

  #if(PDUR_TP_GATEWAY_OPERATION == STD_OFF)
  PDUR_UNUSED_PTR(pduInfoPtr);
  PDUR_UNUSED_PTR(bufferSizePtr);
  #endif

  return (bufReqReturn);
} /* End of PduR_DETCheckLoTpCopyRxData(
   * PduIdType rxPduId, uint8 moduleType,
   * P2VAR(PduInfoType, AUTOMATIC,PDUR_VAR) pduInfoPtr,
   * P2VAR(PduLengthType, AUTOMATIC,PDUR_VAR) bufferSizePtr)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
#endif /* #if (PDUR_TP_RXINDICATION == STD_ON) */

/*******************************************************************************
** Function Name        : PduR_LoTpGWCopyRxData                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpCopyRxData function                        **
**                        in case of multicast gateway.                       **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType rxPduId,                                  **
**                        PduInfoType* pduInfoPtr,                            **
**                        PduLengthType* bufferSizePtr                        **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : PduLengthType* bufferSizePtr                        **
**                                                                            **
** Return parameter     : BufReq_ReturnType bufReqReturn                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        PduR_LowTpRxIndication, PduR_LoRxConfig             **
**                        PduR_TpTxBuffer,                                    **
**                        PduR_TpBufferConfig                                 **
**                                                                            **
** Function(s) invoked  : PduR_BuffUpdateLoTpGWCopyRxData(),                  **
**                        PduR_LowTpTransmit(), PduR_FreeBuffer()             **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
 static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpGWCopyRxData( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
    PduIdType rxPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr)
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) ptrTpRxIndication;
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu;
  BufReq_ReturnType bufReqReturn;
  #if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON)
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif
  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  #endif
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;
  Std_ReturnType returnAllTxVal;
  returnAllTxVal = (Std_ReturnType)E_NOT_OK;
  uint8 noOfRoutePdu;
  #endif
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* @Trace: PduR_SUD_API_408 */
  /* Get the pointer to ptrLoRxSource structure */
  ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
  /* Get the pointer to ptrTpRxIndication structure */
  ptrTpRxIndication = (P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST))
                               (ptrLoRxSource->LoIfTpSource);
  #else
  /* @Trace: PduR_SUD_API_407 */
  /* Get pGWRxTpPdu to local pointer*/
  ptrTpRxIndication = &PduR_LowTpRxIndication[rxPduId];
  #endif
  /* Get pGWRxTpPdu to local pointer*/
  ptrGWTpPdu = ptrTpRxIndication->GWRxTpPdu;
  /* Update buffer of routing path for gateway */
  bufReqReturn = PduR_BuffUpdateLoTpGWCopyRxData(ptrGWTpPdu, bufferSizePtr,
    pduInfoPtr, rxPduId);
  /* check gateway on-the-fly is supported*/
  #if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON)
  if (((uint8)PDUR_ZERO != pduInfoPtr->SduLength) &&
    (BUFREQ_E_NOT_OK != bufReqReturn))
  {
    /* Get ptrTxBuffer from Tx Buffer PduR */
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    ptrTxBuffer = &PduR_TpBufferConfig[ptrGWTpPdu->TxBufferIndex];
    #else
    ptrTxBuffer = &PduR_TpTxBuffer[ptrGWTpPdu->TxBufferIndex];
    #endif
    /* Get the Number of Route for Source PDU */
    noOfRoutePdu = (ptrTpRxIndication->TargetIndexOrNoOfRoute &
      (uint8)PDUR_NOOFROUTE_MASK);
    /* Loop for the Number of Route of the Source PDU */
    /* @Trace: SRS_PduR_06029 */
    do
    {
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      /* Get routing path group id from data struct */
      groupIdValue = ptrGWTpPdu->GroupMaskValue; /* polyspace RTE:IDP [Not a defect:Low] "configured memory access index" */
      indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
      idConvert = groupIdValue % PDUR_BITMASK_UINT8;
      /* @Trace: SRS_PduR_06120 */
      /* Check if routing path is enabled */
      if ((PDUR_UNDEFINED == groupIdValue) ||
        ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] &
                                          (((uint32)PDUR_ONE) << idConvert))))
      #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
      {
        /* Check routing isn't reception to upper module */
        if ((uint8)PDUR_ZERO == ((ptrGWTpPdu->TargetIndexBufType) &
                                                        PDUR_UPPERLAYER_MASK))
        {
          if (PDUR_RX_TX_NOT_COMPLETED == (*(ptrGWTpPdu->RamArea)))
          {
            #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
            if (NULL_PTR == ptrTxBuffer->SinBufPtr)
            {
              ptrQueue = ptrTxBuffer->FirstQueuePtr;
              /* Check threshold is reach */
              /* @Trace: SRS_PduR_06026 */
              if (ptrQueue->CopiedLength >= ptrGWTpPdu->TpThreshold) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
              {
                /* @Trace: PduR_SUD_API_223 */
                returnAllTxVal = returnAllTxVal & PduR_LowTpTransmit(
                  ptrTxBuffer, ptrGWTpPdu, rxPduId, PDUR_COPYRX_DATA_SID);
              }
              else
              {
                /* @Trace: PduR_SUD_API_225 */
                returnAllTxVal = (Std_ReturnType)E_OK;
              }
            }
            else
            #endif /* #if(PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON) */
            {
              /* @Trace: SRS_PduR_06026 */
              if (ptrTxBuffer->SinBufPtr->CopiedLength >= /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
                                       ptrGWTpPdu->TpThreshold)
              {
                /* @Trace: PduR_SUD_API_224 */
                returnAllTxVal = returnAllTxVal & PduR_LowTpTransmit(
                  ptrTxBuffer, ptrGWTpPdu, rxPduId, PDUR_COPYRX_DATA_SID);
              }
              else
              {
                returnAllTxVal = (Std_ReturnType)E_OK;
              }
            }
          } /* @if (PDUR_RX_TX_NOT_COMPLETED == (*(ptrGWTpPdu->RamArea))) */
          else
          {
            /* @Trace: PduR_SUD_API_219 */
            returnAllTxVal = (Std_ReturnType)E_OK;
          }
        } /* @if ((uint8)PDUR_ZERO == ((ptrGWTpPdu->TargetIndexBufType) &
                                                  PDUR_UPPERLAYER_MASK)) */
        else
        {
          /* @Trace: PduR_SUD_API_222 */
          returnAllTxVal = (Std_ReturnType)E_OK;
        }
      }
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      else
      {
        /* @Trace: PduR_SUD_API_221 */
        /* No Action */
      }
      #endif
      /* Increment the ptrGWTpPdu Pointer */
      ptrGWTpPdu++;
      /* Decrement the Number of Route PDU */
      noOfRoutePdu--;
    } while ((uint8)PDUR_ZERO != noOfRoutePdu);
    /* Free PduR buffer when all destination failed */
    /* @Trace: SRS_PduR_06105 */
    if ((Std_ReturnType)E_OK != returnAllTxVal)
    {
      /* @Trace: PduR_SUD_API_220 */
      PduR_FreeBuffer(ptrTxBuffer, rxPduId, PDUR_COPYRX_DATA_SID);
      bufReqReturn = BUFREQ_E_NOT_OK;
    }
    else
    {
      bufReqReturn = BUFREQ_OK;
    }
  }
  else
  #endif /* #if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON) */
  {
    /* @Trace: PduR_SUD_API_217 */
    /* No Action */
  }
  return (bufReqReturn);
} /* End of PduR_LoTpGWCopyRxData(PduIdType rxPduId, P2VAR(PduInfoType,
   *AUTOMATIC, PDUR_VAR) pduInfoPtr, P2VAR(PduLengthType, AUTOMATIC,
   *PDUR_VAR) bufferSizePtr) */

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
** Function Name        : PduR_BuffUpdateLoTpGWCopyRxData                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpGWCopyRxData function                      **
**                        to update the TP buffers.                           **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduR_GWRxTpPdu ptrGWTpPdu                           **
** Input Parameters     : PduLengthType* bufferSizePtr                        **
** Input Parameters     : PduInfoType* pduInfoPtr                             **
** Input Parameters     : PduIdType rxPduId                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PduLengthType* bufferSizePtr                        **
**                                                                            **
** Return parameter     : BufReq_ReturnType bufReqReturn                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): PduR_TpTxBuffer,                **
**                        PduR_PoolPtr, PduR_TpBufferConfig                   **
**                                                                            **
** Function(s) invoked  : PduR_FindPduIdQueue()                               **
**                        SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA()       **
**                        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA()        **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_BuffUpdateLoTpGWCopyRxData( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu,
P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
PduIdType rxPduId)
{
  /* @Trace: SRS_PduR_06026 */
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) ptrDestSduDataPtr;
  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  uint16 indexFifo;
  indexFifo = PDUR_UNDEFINED;
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  #endif
  PduLengthType availLength;
  availLength = PDUR_ZERO;
  BufReq_ReturnType bufReqReturn;
  bufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
  boolean isUpdateBuffer;
  isUpdateBuffer = (boolean)PDUR_TRUE;
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* @Trace: PduR_SUD_API_410 */
  ptrTxBuffer = &PduR_TpBufferConfig[ptrGWTpPdu->TxBufferIndex];
  #else
  /* @Trace: PduR_SUD_API_409 */
  ptrTxBuffer = &PduR_TpTxBuffer[ptrGWTpPdu->TxBufferIndex];
  #endif
  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  if (NULL_PTR == ptrTxBuffer->SinBufPtr)
  {
    indexFifo = PduR_FindPduIdQueue(ptrTxBuffer, rxPduId);
    if (PDUR_UNDEFINED != indexFifo)
    {
      ptrQueue = &PduR_TpTxQueue[indexFifo];
      #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
      if ((boolean)PDUR_TRUE == ptrQueue->PoolStatus) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
      {
        /* @Trace: PduR_SUD_API_230 */
        ptrDestSduDataPtr = &PduR_PoolPtr[ptrQueue->IndexPool].SduPtr[ptrQueue->CopiedLength]; /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "index poor support range from 0..255" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
      }
      else
      #endif
      {
        /* @Trace: PduR_SUD_API_229 */
        ptrDestSduDataPtr = &ptrQueue->PduInfoPtr.SduDataPtr[ptrQueue->CopiedLength];
      }
      if (PDUR_RX_IN_PROGRESS == ptrQueue->RxState)
      {
        /* @Trace: PduR_SUD_API_232 */
        availLength = ptrQueue->AvailLength;
      }
      else
      {
        /* @Trace: PduR_SUD_API_231 */
        isUpdateBuffer = (boolean)PDUR_FALSE;
      }
    }
    else
    {
      /* @Trace: PduR_SUD_API_424 */
      isUpdateBuffer = (boolean)PDUR_FALSE;
    }
  }
  else
  #endif /* #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON) */
  {
    PDUR_UNUSED(rxPduId);
    #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
    if ((boolean)PDUR_TRUE == ptrTxBuffer->SinBufPtr->PoolStatus) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
    {
      /* @Trace: PduR_SUD_API_227 */
      /* polyspace +3 MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "index poor support range from 0..255" */ 
      /* polyspace +3 RTE:NIV [Not a defect:Low] "initialized variable" */ 
      /* polyspace +1 RTE:OBAI [Not a defect:Unset] "configured memory access index" */
      ptrDestSduDataPtr = &(PduR_PoolPtr[ptrTxBuffer->SinBufPtr->IndexPool].SduPtr
        [ptrTxBuffer->SinBufPtr->CopiedLength]); 
    }
    else
    #endif
    {
      /* @Trace: PduR_SUD_API_228 */
      ptrDestSduDataPtr = &ptrTxBuffer->SduPtr[ptrTxBuffer->SinBufPtr->CopiedLength]; /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
    }
    if (PDUR_RX_IN_PROGRESS == ptrTxBuffer->SinBufPtr->RxState) /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
    {
      /* @Trace: PduR_SUD_API_233 */
      availLength = ptrTxBuffer->SinBufPtr->AvailLength; /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
    }
    else
    {
      /* @Trace: PduR_SUD_API_234 */
      isUpdateBuffer = (boolean)PDUR_FALSE;
    }
  }
  if (availLength < pduInfoPtr->SduLength) /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "pduInfoPtr is checked null by PduR_DETCheckLoTpCopyRxData function" */
  {
    /* @Trace: PduR_SUD_API_423 */
    isUpdateBuffer = (boolean)PDUR_FALSE;
  }
  else
  {
    /* No Action */
  }
  if (((uint8)PDUR_ZERO != pduInfoPtr->SduLength) && /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "code is handled in case of pointer may be NULL" */
    ((boolean)PDUR_TRUE == isUpdateBuffer))
  {
    /* @Trace: SRS_BSW_00312 */
    /* @Trace: PduR_SUD_API_235 */
    /* Enter into critical area */
    SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
    /* API to copy the Received data for transmitting */
    memcpy((P2VAR(void, AUTOMATIC, PDUR_VAR))(ptrDestSduDataPtr), /* polyspace MISRA-C:2012 9.1 D4.1 [Not a defect:Low] "this local pointer local always be initialized due to data flow" */ /* polyspace RTE:STD_LIB [Not a defect:Low] "all input function are valid due to data flow" */ /* polyspace RTE:NIP [Not a defect:Low] "initialized variable due to data flow" */
        (P2CONST(void, AUTOMATIC, PDUR_CONST))(pduInfoPtr->SduDataPtr), /* polyspace DEFECT:NON_INIT_PTR [Not a defect:Low] "this local pointer local always be initialized due to data flow" */
        pduInfoPtr->SduLength); /* polyspace MISRA-C:2012 D4.11 [Not a defect:Low] "all input function are valid due to data flow" */

    #if(PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
    if (NULL_PTR == ptrTxBuffer->SinBufPtr)
    {
      /* Increment data length is copied */
      ptrQueue->CopiedLength += pduInfoPtr->SduLength; /* polyspace MISRA-C:2012 9.1 D4.1 [Not a defect:Low] "this local pointer local always be initialized due to data flow" */ /* polyspace DEFECT:NON_INIT_PTR [Not a defect:Low] "this local pointer local always be initialized due to data flow" */ /* polyspace RTE:NIP [Not a defect:Low] "initialized variable due to data flow" */
      ptrQueue->AvailLength  -= pduInfoPtr->SduLength;
      if (ptrQueue->CopiedLength == ptrQueue->ReqLength)
      {
        /* @Trace: PduR_SUD_API_236 */
        ptrQueue->RxState = PDUR_RX_COMPLETED;
      }
      else
      {
        /* No Action */
      }
    }
    else
    #endif
    {
      ptrTxBuffer->SinBufPtr->CopiedLength += pduInfoPtr->SduLength; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
      ptrTxBuffer->SinBufPtr->AvailLength  -= pduInfoPtr->SduLength; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
      if (ptrTxBuffer->SinBufPtr->CopiedLength == /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
        ptrTxBuffer->SinBufPtr->ReqLength) /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
      {
        /* @Trace: PduR_SUD_API_238 */
        ptrTxBuffer->SinBufPtr->RxState = PDUR_RX_COMPLETED;
      }
      else
      {
        /* No Action */
      }
    }
    SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
  }
  else
  {
    if ((uint8)PDUR_ZERO == pduInfoPtr->SduLength)
    {
      /* @Trace: PduR_SUD_API_241 */
      bufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
    }
    else
    {
      /* @Trace: PduR_SUD_API_240 */
      bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
    }
  }
  #if(PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  if (NULL_PTR == ptrTxBuffer->SinBufPtr)
  {
    if (PDUR_UNDEFINED != indexFifo)
    {
      /* @Trace: PduR_SUD_API_243 */
      *bufferSizePtr = ptrQueue->AvailLength; /* polyspace MISRA-C:2012 9.1 D4.1[Not a defect:Low] "this local pointer local always be initialized due to data flow" */ /* polyspace DEFECT:NON_INIT_PTR [Not a defect:Low] "this local pointer local always be initialized due to data flow" */ /* polyspace RTE:NIP [Not a defect:Low] "initialized variable due to data flow" */
    }
    else
    {
      *bufferSizePtr = PDUR_ZERO;
    }
  }
  else
  #endif
  {
    /* @Trace: PduR_SUD_API_242 */
    *bufferSizePtr = ptrTxBuffer->SinBufPtr->AvailLength; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
  }
  return bufReqReturn;
} /* End of PduR_BuffUpdateLoTpGWCopyRxData(PduLengthType tpSduLength,
   *P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
** Function Name        : PduR_LoTpRxIndication                               **
**                                                                            **
** Service ID           : 0x45                                                **
**                                                                            **
** Description          : This function is called by the TP modules. The PDU  **
**                        Router shall translate the <Lo>TpRxPduId into the   **
**                        configured target PDU ID and route this indication  **
**                        to the configured target function.                  **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType rxPduId,                                  **
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
**                        PduR_LowTpRxIndication, PduR_TpBufferConfig,        **
**                        PduR_TpTxBuffer, PduR_LowTpReceive, PduR_LoRxConfig **
**                                                                            **
** Function(s) invoked  : PduR_FindPduIdQueue(), PduR_UpTpRxIndication(),     **
**                        PduR_DETCheckLoTpRxIndication(),                    **
**                        PduR_LowTpTransmit(), PduR_FreeBuffer()             **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_PduR_06020 */
/* @Trace: SRS_PduR_06117 */
/* @Trace: SRS_BSW_00171 */
/* @Trace: SRS_BSW_00167 */
/* @Trace: SRS_BSW_00310 */
/* @Trace: SRS_PduR_06121 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_RXINDICATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
/* @Traceability BEGIN -- SRS: SWS_PduR_00790 SWS_PduR_00791 SWS_PduR_00307
                               SWS_PduR_00792 SWS_PduR_00825 SWS_PduR_00835
                               SWS_PduR_00831 SWS_PduR_00806 SWS_PduR_00328
                               SWS_PduR_00787 SWS_PduR_00830 SWS_PduR_00689
                               SWS_PduR_00551 SWS_PduR_00808 SWS_PduR_00708
                               SWS_PduR_00789 SWS_PduR_00330 SWS_PduR_00100
                               SWS_PduR_00429 SWS_PduR_00119 SWS_PduR_00221
                               SWS_PduR_00207 SWS_PduR_00287 SWS_PduR_00375
                               SWS_PduR_00161 SWS_PduR_00824 SWS_PduR_00005
                               SWS_PduR_00017 SWS_PduR_00794 SWS_PduR_00018
                               SWS_PduR_00021 SWS_PduR_00764 */
FUNC(void, PDUR_CODE) PduR_LoTpRxIndication(PduIdType rxPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  uint8 moduleType, Std_ReturnType result)
#else
FUNC(void, PDUR_CODE) PduR_LoTpRxIndication(PduIdType rxPduId,
  Std_ReturnType result)
#endif
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) ptrTpRxIndication;
  #if(PDUR_TP_GATEWAY_OPERATION == STD_ON)
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu;
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  uint16 indexFifo;
  #endif
  uint8 noOfRoutePdu;
  uint8 rxState;
  Std_ReturnType returnTransmit;
  returnTransmit = (Std_ReturnType)E_NOT_OK;
  uint8 targetIndexOrNoOfRoute;
  #endif /* End of if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */

  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean detErrorFlag;
  detErrorFlag = PduR_DETCheckLoTpRxIndication(rxPduId, moduleType);
  /* Check whether any development errors are detected */
  if ((boolean)PDUR_FALSE == detErrorFlag)
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_360 */
    /* Get the pointer to ptrLoRxSource structure */
    ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
    /* Get the pointer to ptrTpRxIndication structure */
    ptrTpRxIndication = (P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST))
                               (ptrLoRxSource->LoIfTpSource);
    #else
    /* @Trace: PduR_SUD_API_359 */
    /* Assign Local Pointer to TP Rx Indication Structure */
    ptrTpRxIndication = &PduR_LowTpRxIndication[rxPduId];
    #endif
    #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
    targetIndexOrNoOfRoute = ptrTpRxIndication->TargetIndexOrNoOfRoute;

    if ((uint8)PDUR_ZERO !=
      (targetIndexOrNoOfRoute & (uint8)PDUR_NONGATEWAY_MASK))
    {
      noOfRoutePdu = ptrTpRxIndication->TargetIndexOrNoOfRoute &
                                                   (uint8)PDUR_NOOFROUTE_MASK;
      /* Assign Local Pointer to LoGWRxIndication Structure */
      ptrGWTpPdu = ptrTpRxIndication->GWRxTpPdu;
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
      ptrTxBuffer = &PduR_TpBufferConfig[ptrGWTpPdu->TxBufferIndex];
      #else
      ptrTxBuffer = &PduR_TpTxBuffer[ptrGWTpPdu->TxBufferIndex];
      #endif
      #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
      if (NULL_PTR == ptrTxBuffer->SinBufPtr)
      {
        indexFifo = PduR_FindPduIdQueue(ptrTxBuffer, rxPduId);
        if (PDUR_UNDEFINED != indexFifo)
        {
          /* @Trace: PduR_SUD_API_053 */
          ptrQueue = &PduR_TpTxQueue[indexFifo];
          rxState = ptrQueue->RxState; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
        }
        else
        {
          /* @Trace: PduR_SUD_API_052 */
          rxState = PDUR_RX_YETTOSTART;
        }
      }
      else
      #endif /* #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON) */
      {
        /* @Trace: PduR_SUD_API_051 */
        ptrQueue = NULL_PTR;
        rxState = ptrTxBuffer->SinBufPtr->RxState; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
      }
      PDUR_UNUSED_PTR(ptrQueue); /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
      if (((Std_ReturnType)E_OK == result) &&
        (PDUR_RX_COMPLETED == rxState))
      {
        /* @Trace: SRS_PduR_06029 */
        do
        {
          #if (PDUR_TP_UP_RX_SUPPORT == STD_ON)
          /* TP multicast to Upper layer */
          if ((uint8)PDUR_ZERO != ((ptrGWTpPdu->TargetIndexBufType) & /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
                                                        PDUR_UPPERLAYER_MASK))
          {
            /* @Trace: PduR_SUD_API_055 */
            PduR_UpTpRxIndication(ptrGWTpPdu, ptrTxBuffer, ptrQueue, result);
          }
          else  /* Gateway case only */
          #endif
          {
            if (PDUR_RX_TX_NOT_COMPLETED == (*(ptrGWTpPdu->RamArea)))
            {
              /* @Trace: PduR_SUD_API_057 */
              returnTransmit &= PduR_LowTpTransmit(ptrTxBuffer, ptrGWTpPdu,
                rxPduId, PDUR_TP_RX_INDICATION_SID);
            }
            else
            {
              /* @Trace: PduR_SUD_API_056 */
              returnTransmit &= (Std_ReturnType)E_OK;
            }
          }  /* Gateway only */
          --noOfRoutePdu;
          /* MISRA Rule   : 17.4.
           *   Message      : Increment or decrement operation
           *                  performed on the pointer
           *   Reason       : Increment operator used
           *                  to achieve better throughput.
           *   Verification : However, part of the code
           *                  is verified manually and
           *                  it is not having any impact.
           */
          /* Increment the Rx gateway structure index */
          ++ptrGWTpPdu;
        } while ((uint8)PDUR_ZERO != noOfRoutePdu);
        if ((Std_ReturnType)E_OK == returnTransmit)
        {
          #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
          if (NULL_PTR == ptrTxBuffer->SinBufPtr)
          {
            /* @Trace: PduR_SUD_API_058 */
            ptrQueue->RxState = PDUR_RX_ACKNOWLEDGE; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
          }
          else
          #endif
          {
            /* @Trace: PduR_SUD_API_059 */
            ptrTxBuffer->SinBufPtr->RxState = PDUR_RX_ACKNOWLEDGE; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
          }
        }
        else
        {
          /* No Action */
        }
      } /* @if (((Std_ReturnType)E_OK == result) &&
             (PDUR_RX_COMPLETED == rxState)) */
      else
      {
        /* No Action */
      }
      /* @Trace: SRS_PduR_06105 */
      if ((Std_ReturnType)E_NOT_OK == returnTransmit)
      {
        /* @Trace: PduR_SUD_API_060 */
        /* Check free buffer routing when all destination failed */
        PduR_FreeBuffer(ptrTxBuffer, rxPduId, PDUR_TP_RX_INDICATION_SID);
      }
      else
      {
        /* No Action */
      }
      
    } /* if ((uint8)PDUR_ZERO !=
           (targetIndexOrNoOfRoute & (uint8)PDUR_NONGATEWAY_MASK)) */
    else
    #endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
    { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
      #if (PDUR_TP_UP_RX_SUPPORT == STD_ON)
      if(PduR_LowTpReceive[ptrTpRxIndication->TargetIndexOrNoOfRoute &
                        (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
      {
        /* @Trace: PduR_SUD_API_050 */
        (void)PduR_LowTpReceive[ptrTpRxIndication->TargetIndexOrNoOfRoute &
                        (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer
                       (ptrTpRxIndication->UpTargetPduId, result);
      }
      #endif
    }
  } /* @if ((boolean)PDUR_FALSE == detErrorFlag) */
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No Action */
  }
  #endif
}
/* @Traceability END -- SRS: SWS_PduR_00790 SWS_PduR_00791 SWS_PduR_00307
                               SWS_PduR_00792 SWS_PduR_00825 SWS_PduR_00835
                               SWS_PduR_00831 SWS_PduR_00806 SWS_PduR_00328
                               SWS_PduR_00787 SWS_PduR_00830 SWS_PduR_00689
                               SWS_PduR_00551 SWS_PduR_00808 SWS_PduR_00708
                               SWS_PduR_00789 SWS_PduR_00330 SWS_PduR_00100
                               SWS_PduR_00429 SWS_PduR_00119 SWS_PduR_00221
                               SWS_PduR_00207 SWS_PduR_00287 SWS_PduR_00375
                               SWS_PduR_00161 SWS_PduR_00824 SWS_PduR_00005
                               SWS_PduR_00017 SWS_PduR_00794 SWS_PduR_00018
                               SWS_PduR_00021 SWS_PduR_00764 */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_TP_RXINDICATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_DETCheckLoTpRxIndication                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpRxIndication function                      **
**                        to update the TP buffers.                           **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType rxPduId, uint8 moduleType                 **
**                        boolean ifRouting                                   **
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
**                        PduR_InitStatus, PduR_LowTpRxIndication,            **
**                        PduR_IfTpRxIndicationMaxPduId, PduR_LoRxConfig      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
**                                                                            **
*******************************************************************************/
#if ((PDUR_TP_RXINDICATION == STD_ON) && (PDUR_ZERO_COST_OPERATION == STD_OFF))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
 static FUNC(boolean, PDUR_CODE) PduR_DETCheckLoTpRxIndication( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType rxPduId, uint8 moduleType)
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) ptrTpRxIndication;
  boolean detErrorFlag;
  /* Set the DetErrorFlag to the PDUR_FALSE */
  detErrorFlag = (boolean)PDUR_FALSE;
  /* Check whether the module is initialised */
  if (PDUR_UNINIT == PduR_InitStatus)
  {
    /* @Trace: SRS_BSW_00406 */
    /* @Trace: PduR_SUD_API_107 */
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_TP_RX_INDICATION_SID, PDUR_E_UNINIT);
    /* Set the error flag to TRUE */
    detErrorFlag = (boolean)PDUR_TRUE;
  } /* End of if (PDUR_UNINIT == PduR_InitStatus) */
  else
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_369 */
    if (rxPduId >= PduR_IfTpRxIndicationMaxPduId)
    #else
    /* @Trace: PduR_SUD_API_368 */
    if (rxPduId >= PDUR_TP_RXINDICATION_MAXPDUID)
    #endif
    {
      /* Report to DET */
      /* @Trace: SRS_PduR_06103 */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_TP_RX_INDICATION_SID, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      detErrorFlag = (boolean)PDUR_TRUE;
    } /* End of if (rxPduId >= PDUR_TP_RXINDICATION_MAXPDUID) */
    else
    {
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_OFF)
      /* Get the pointer to TpRxIndication structure */
      ptrTpRxIndication = &PduR_LowTpRxIndication[rxPduId];
      #else
      /* Get the pointer to ptrLoRxSource structure */
      ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
      /* Get the pointer to ptrTpRxIndication structure */
      ptrTpRxIndication = (P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST))
                               (ptrLoRxSource->LoIfTpSource);
      if ((boolean)PDUR_FALSE !=
                              (boolean)ptrLoRxSource->IsInterfaceRouting)
      {
        /* Report to DET */
        /* @Trace: PduR_SUD_API_370 */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          PDUR_TP_RX_INDICATION_SID, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to TRUE */
        detErrorFlag = (boolean)PDUR_TRUE;
      }
      else
      #endif
      {
        if (ptrTpRxIndication->ModuleType != moduleType)
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* Report to DET */
          /* @Trace: SRS_PduR_06103 */
          /* @Trace: PduR_SUD_API_108 */
          (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
            PDUR_TP_RX_INDICATION_SID, PDUR_E_PDU_ID_INVALID);
          /* Set the error flag to TRUE */
          detErrorFlag = (boolean)PDUR_TRUE;
        } /* End of if (ptrTpRxIndication->ModuleType != moduleType) */
        else
        {
          /* No Action */
        }
      }
    }
  }
  return (detErrorFlag);
} /* End of PduR_DETCheckLoTpRxIndication(
   * PduIdType rxPduId, uint8 moduleType, uint8 PDUR_TP_RX_INDICATION_SID) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
#endif /* End of if (PDUR_TP_RXINDICATION == STD_ON) */

/*******************************************************************************
** Function Name        : PduR_CancelReceive                                  **
**                                                                            **
** Service ID           : 0x4c                                                **
**                                                                            **
** Description          : The PDU Router shall translate the DcmRxPduId       **
**                        into the configured target PDU ID and route this    **
**                        cancel receive request to the configured target     **
**                        TP module.This function shall only be provided if   **
**                        the pre-compile time configuration parameter        **
**                        PDUR_DCM_SUPPORT and PDUR_CANCEL_RECEIVE_SUPPORT    **
**                        is enabled.                                         **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PduIdType rxPduId                                   **
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
**                        PduR_UpTpCancelReceive, PduR_LoRxConfig             **
**                        PduR_LowTpRxIndication,                             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckCancelReceive                          **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_PduR_06020 */
/* @Trace: SRS_BSW_00171 */
/* @Trace: SRS_BSW_00167 */
/* @Trace: SRS_BSW_00310 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* @Traceability BEGIN -- SRS: SWS_PduR_00726 SWS_PduR_00732 SWS_PduR_00736
                               SWS_PduR_00727 SWS_PduR_00161 SWS_PduR_00328
                               SWS_PduR_00330 SWS_PduR_00717 SWS_PduR_00715
                               SWS_PduR_00100 SWS_PduR_00119 SWS_PduR_00221
                               SWS_PduR_00767 SWS_PduR_00824 SWS_PduR_00764 */
FUNC(Std_ReturnType, PDUR_CODE) PduR_CancelReceive(PduIdType rxPduId)
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) ptrTpRxIndication;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif
  Std_ReturnType returnVal;
  uint8 localIndex;
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  returnVal = PduR_DETCheckCancelReceive(rxPduId);
  /* Check whether any development errors are detected */
  if ((Std_ReturnType)E_OK == returnVal)
  #endif /* #if(PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    returnVal = (Std_ReturnType)E_NOT_OK;
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_412 */
    /* Get the pointer to ptrLoRxSource structure */
    ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
    /* Get the pointer to ptrTpRxIndication structure */
    ptrTpRxIndication = (P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST))
                               (ptrLoRxSource->LoIfTpSource);
    #else
    /* @Trace: PduR_SUD_API_411 */
    /* Get the pointer to TpRxIndication structure */
    ptrTpRxIndication = &PduR_LowTpRxIndication[rxPduId];
    #endif
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get routing path group id from data struct */
    groupIdValue = ptrTpRxIndication->GroupMaskValue;
    indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
    idConvert = groupIdValue % PDUR_BITMASK_UINT8;
    /* @Trace: SRS_PduR_06120 */
    /* Check if routing path is enabled */
    if ((PDUR_UNDEFINED == groupIdValue) ||
      ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] & /* polyspace RTE:UNR [Not a defect:Low] "Not a redundant condition in other configuration" */
                                          (((uint32)PDUR_ONE) << idConvert))))
    #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
    {
      /* check for Non-Gateway */
      /* polyspace +1 MISRA2012:14.3 [Justified:Low] "Value of TargetIndexOrNoOfRoute is generated by generator and has checked that have no impact" */
      if ((uint8)PDUR_ZERO == (ptrTpRxIndication->TargetIndexOrNoOfRoute &
                                                   (uint8)PDUR_NONGATEWAY_MASK))
      { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
        localIndex = ptrTpRxIndication->SourceIndex;
        /* Invoke Cancel Receive Request of corresponding Tp layer */
        if (((uint8)PDUR_TOTAL_COUNT_TP_CANCEL_RECEIVE > localIndex) && \
          (PduR_UpTpCancelReceive[localIndex].TargetLayer != NULL_PTR))
        {
          /* @Trace: PduR_SUD_API_044 */
          returnVal = PduR_UpTpCancelReceive[localIndex].TargetLayer(
                                 ptrTpRxIndication->LoRxHandleId);
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
    }
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Requirement PDUR0726 */
    /* If the routing path for the requested I-PDUs is disabled, then
    PduR_<Up>CancelReceive shall return E_NOT_OK */
    else
    { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
      /* No Action */
    }
    #endif
  }
  /* return with the returnVal */
  return (returnVal);
} /* End of PduR_CancelReceive(PduIdType rxPduId) */
/* @Traceability END -- SRS: SWS_PduR_00726 SWS_PduR_00732 SWS_PduR_00736
                               SWS_PduR_00727 SWS_PduR_00161 SWS_PduR_00328
                               SWS_PduR_00330 SWS_PduR_00717 SWS_PduR_00715
                               SWS_PduR_00100 SWS_PduR_00119 SWS_PduR_00221
                               SWS_PduR_00767 SWS_PduR_00824 SWS_PduR_00764 */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*#if (PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
** Function Name        : PduR_DETCheckCancelReceive                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The PDU Router shall translate the DcmRxPduId       **
**                        into the configured target PDU ID and route this    **
**                        cancel receive request to the configured target     **
**                        TP module.This function shall only be provided if   **
**                        the pre-compile time  configuration parameter       **
**                        PDUR_DCM_SUPPORT and  PDUR_CANCEL_RECEIVE_SUPPORT   **
**                        is  enabled.                                        **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PduIdType rxPduId, boolean ifRouting                **
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
**                        PduR_InitStatus, PduR_IfTpRxIndicationMaxPduId      **
**                        PduR_LoRxConfig                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON) &&\
  (PDUR_TP_RXINDICATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_VAR) PduR_DETCheckCancelReceive(PduIdType rxPduId) /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  Std_ReturnType returnVal;
  returnVal = (Std_ReturnType)E_OK;
  if (PDUR_UNINIT == PduR_InitStatus)
  {
    /* @Trace: SRS_BSW_00406 */
    /* @Trace: PduR_SUD_API_045 */
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_CANCEL_RECEIVE_SID, PDUR_E_UNINIT);
    /* Set the return flag to E_NOT_OK */
    returnVal = (Std_ReturnType)E_NOT_OK;
  } /* End of if (PDUR_UNINIT == PduR_InitStatus) */
  else
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_413 */
    if (rxPduId >= PduR_IfTpRxIndicationMaxPduId)
    #else
    /* @Trace: PduR_SUD_API_046 */
    if (rxPduId >= PDUR_TP_RXINDICATION_MAXPDUID)
    #endif
    {
      /* Report to DET */
      /* @Trace: SRS_PduR_06103 */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_CANCEL_RECEIVE_SID, PDUR_E_PDU_ID_INVALID);
      /* Set the return value to E_NOT_OK */
      returnVal = (Std_ReturnType)E_NOT_OK;
    } /* End of if (rxPduId >= PDUR_TP_RXINDICATION_MAXPDUID) */
    else
    {
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
      /* Get the pointer to ptrLoRxSource structure */
      ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
      if ((boolean)PDUR_FALSE !=
                              (boolean)ptrLoRxSource->IsInterfaceRouting)
      {
        /* Report to DET */
        /* @Trace: PduR_SUD_API_414 */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          PDUR_CANCEL_RECEIVE_SID, PDUR_E_PDU_ID_INVALID);
        /* Set the return value to E_NOT_OK */
        returnVal = (Std_ReturnType)E_NOT_OK;
      }
      else
      {
        /* No Action */
      }
      #endif
    }
  }
  return (returnVal);
} /* End Of PduR_DETCheckCancelReceive(PduIdType rxPduId, uint8 PDUR_CANCEL_RECEIVE_SID)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_OFF)*/
#endif /* #if (PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF)*/

/*******************************************************************************
** Function Name        : PduR_DETCheckLoTpStartOfReception                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpStartOfReception function                  **
**                        to check the parameters passed are valid and        **
**                        buffer does not need to be the length of the        **
**                        report to DET in case of invalid values.            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType rxPduId,                                  **
**                        uint8 moduleType, PduLengthType* bufferSizePtr      **
**                        boolean ifRouting                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType bufReqReturn                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_InitStatus, PduR_LowTpRxIndication             **
**                        PduR_IfTpRxIndicationMaxPduId, PduR_LoRxConfig      **
**                                                                            **
** Function(s) invoked  : Det_ReportError()                                   **
*******************************************************************************/
#if ((PDUR_TP_RXINDICATION == STD_ON) && (PDUR_ZERO_COST_OPERATION == STD_OFF))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
 static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DETCheckLoTpStartOfReception( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType rxPduId, uint8 moduleType,
  P2CONST(PduLengthType, AUTOMATIC, PDUR_CONST) bufferSizePtr)
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST)ptrTpRxIndication;
  BufReq_ReturnType bufReqReturn;
  /* Initialize buffer return type to "BUFREQ_OK" */
  bufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
  /* Check whether the module is Initialized */
  if (PDUR_UNINIT == PduR_InitStatus)
  {
    /* @Trace: SRS_BSW_00406 */
    /* @Trace: PduR_SUD_API_284 */
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_STARTOF_RECEPTION_SID, PDUR_E_UNINIT);
    /* Set the return value to BUFREQ_E_NOT_OK */
    bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
  } /* End of if (PDUR_UNINIT == PduR_InitStatus) */
  else
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_363 */
    if (rxPduId >= PduR_IfTpRxIndicationMaxPduId)
    #else
    /* @Trace: PduR_SUD_API_285 */
    if (rxPduId >= PDUR_TP_RXINDICATION_MAXPDUID)
    #endif
    {
      /* Report to DET */
      /* @Trace: SRS_PduR_06103 */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_STARTOF_RECEPTION_SID, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
    } /* End of if (rxPduId >= PDUR_TP_RXINDICATION_MAXPDUID) */
    else
    {
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_OFF)
      /* Get the pointer to TpRxIndication structure */
      ptrTpRxIndication = &PduR_LowTpRxIndication[rxPduId];
      #else
      /* Get the pointer to ptrLoRxSource structure */
      ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
      /* Get the pointer to ptrTpRxIndication structure */
      ptrTpRxIndication = (P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST))
                               (ptrLoRxSource->LoIfTpSource);
      if ((boolean)PDUR_FALSE != (boolean)ptrLoRxSource->IsInterfaceRouting)
      {
        /* Report to DET */
        /* @Trace: SRS_PduR_06103 */
        /* @Trace: PduR_SUD_API_364 */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          PDUR_STARTOF_RECEPTION_SID, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to TRUE */
        bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
      }
      else
      #endif
      {
        if (ptrTpRxIndication->ModuleType != moduleType)
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* Report to DET */
          /* @Trace: SRS_PduR_06103 */
          /* @Trace: PduR_SUD_API_286 */
          (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
            PDUR_STARTOF_RECEPTION_SID, PDUR_E_PDU_ID_INVALID);
          /* Set the error flag to TRUE */
          bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
        }
        else
        {
          #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
          /* Check routing is gateway */
          if ((uint8)PDUR_ZERO != ((ptrTpRxIndication->TargetIndexOrNoOfRoute) & /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
            PDUR_GATEWAY_MASK))
          {
            if (NULL_PTR == bufferSizePtr)
            {
              /* @Trace: PduR_SUD_API_287 */
              /* Report to DET */
              (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                PDUR_STARTOF_RECEPTION_SID, PDUR_E_PARAM_POINTER);
              /* Set the return value to BUFREQ_E_NOT_OK */
              bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
            } /* End of if (NULL_PTR == bufferSizePtr) */
            else
            {
              /* No Action */
            }
          }
          else
          #endif
          { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
            /* No Action */
          }
        } /* End of if (ptrTpRxIndication->ModuleType != moduleType) */
      }
    }
  }

  #if (PDUR_TP_GATEWAY_OPERATION == STD_OFF)
  PDUR_UNUSED_PTR(bufferSizePtr);
  #endif

  return (bufReqReturn);
} /* End of PduR_DETCheckLoTpStartOfReception(
   * PduIdType rxPduId, uint8 moduleType,
   * P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
#endif /* End of if (PDUR_TP_RXINDICATION == STD_ON) */

/*******************************************************************************
** Function Name        : PduR_UpTpRxIndication                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpRxIndication function                      **
**                        to call the API of Upper Layers.                    **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduR_GWRxTpPdu ptrGWTpPdu                           **
**                        PduR_TpBuffer ptrTxBuffer                           **
**                        PduR_TpQueueType ptrQueue                           **
**                        Std_ReturnType result                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):PduR_LowTpStartOfReception,      **
**                        PduR_LowTpReceive, PduR_LowTpCopyRxData,            **
**                        PduR_PoolPtr                                        **
**                                                                            **
** Function(s) invoked  : Det_ReportRuntimeError                              **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_UP_RX_SUPPORT == STD_ON)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_UpTpRxIndication(
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu,
  P2CONST(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  P2CONST(PduR_TpQueueType, AUTOMATIC, PDUR_CONST) ptrQueue,
  Std_ReturnType result)
{
  PduInfoType pduInfoPtr;
  BufReq_ReturnType bufReqReturn;
  PduLengthType bufferSize;
  PduLengthType reqLength;
  bufferSize = (PduLengthType)PDUR_ZERO;
  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  if (NULL_PTR == ptrTxBuffer->SinBufPtr)
  {
    /* @Trace: PduR_SUD_API_110 */
    reqLength = ptrQueue->ReqLength; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
    pduInfoPtr.MetaDataPtr = ptrQueue->PduInfoPtr.MetaDataPtr;
  }
  else
  #endif
  {
    /* @Trace: PduR_SUD_API_113 */
    PDUR_UNUSED_PTR(ptrQueue);
    reqLength = ptrTxBuffer->SinBufPtr->ReqLength; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
    pduInfoPtr.MetaDataPtr = ptrTxBuffer->MetaPtr;
  }
  pduInfoPtr.SduDataPtr = NULL_PTR;
  pduInfoPtr.SduLength  = (uint8)PDUR_ZERO;
  if (PduR_LowTpStartOfReception[(uint8)(ptrGWTpPdu->TargetIndexBufType &
                            PDUR_TARGET_INDEX_MASK)].TargetLayer != NULL_PTR)
  {
    /* @Trace: PduR_SUD_API_114 */
    bufReqReturn =
    PduR_LowTpStartOfReception[(uint8)(ptrGWTpPdu->TargetIndexBufType) &
                               PDUR_TARGET_INDEX_MASK].TargetLayer(
      ptrGWTpPdu->TargetPduId, &pduInfoPtr, reqLength,
      &bufferSize);
  }
  else
  { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
    /* @Trace: PduR_SUD_API_115 */
    bufReqReturn = BUFREQ_E_NOT_OK;
  }
  /* Invoke Upper layer CopyRxData once StartOfReception returns */
  if (BUFREQ_OK == bufReqReturn)
  {
    if(reqLength > bufferSize)
    {
      if(PduR_LowTpReceive[((uint8)(ptrGWTpPdu->TargetIndexBufType))&
                        PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
      {
        /* @Trace: PduR_SUD_API_118 */
        (void)PduR_LowTpReceive[((uint8)(ptrGWTpPdu->TargetIndexBufType))&
                        PDUR_TARGET_INDEX_MASK].TargetLayer(
        ptrGWTpPdu->TargetPduId, (Std_ReturnType)E_NOT_OK);
      }
      else
      { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
        /* No Action */
      }
      /* Report to DET */
      (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_TP_RX_INDICATION_SID, PDUR_E_PDU_INSTANCES_LOST);
    } /* if (reqLength > bufferSize) */
    else
    {
      #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
      if (NULL_PTR == ptrTxBuffer->SinBufPtr)
      {
        /* @Trace: PduR_SUD_API_119 */
        pduInfoPtr.SduDataPtr = ptrQueue->PduInfoPtr.SduDataPtr; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
        pduInfoPtr.SduLength  = ptrQueue->PduInfoPtr.SduLength;
      }
      else
      #endif
      {
        #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
        if ((boolean)PDUR_TRUE == ptrTxBuffer->SinBufPtr->PoolStatus) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
        {
          /* @Trace: PduR_SUD_API_120 */
          pduInfoPtr.SduDataPtr =
            PduR_PoolPtr[ptrTxBuffer->SinBufPtr->IndexPool].SduPtr; /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "index poor support range from 0..255" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
        }
        else
        #endif
        {
          /* @Trace: PduR_SUD_API_121 */
          /* Get the Sdu data pointer from Tx Buffer */
          pduInfoPtr.SduDataPtr = ptrTxBuffer->SduPtr;
        }
        pduInfoPtr.SduLength = ptrTxBuffer->SinBufPtr->ReqLength; /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
      }
      /* Invoke Up_CopyRxdata */
      if (PduR_LowTpCopyRxData[((uint8)(ptrGWTpPdu->TargetIndexBufType)) &
        PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
      {
        /* @Trace: PduR_SUD_API_123 */
        bufReqReturn =
          PduR_LowTpCopyRxData[((uint8)(ptrGWTpPdu->TargetIndexBufType)) &
            PDUR_TARGET_INDEX_MASK].TargetLayer(
            ptrGWTpPdu->TargetPduId, &pduInfoPtr, &bufferSize);
      }
      else
      { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
        /* @Trace: PduR_SUD_API_122 */
        bufReqReturn = BUFREQ_E_NOT_OK;
      }
      /*  Invoke Tp receive function  */
      if(BUFREQ_OK == bufReqReturn)
      {
        if (PduR_LowTpReceive[((uint8)(ptrGWTpPdu->TargetIndexBufType)) &
                        PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
        {
          /* @Trace: PduR_SUD_API_125 */
          (void)PduR_LowTpReceive[((uint8)(ptrGWTpPdu->TargetIndexBufType)) &
                        PDUR_TARGET_INDEX_MASK].TargetLayer(
                      ptrGWTpPdu->TargetPduId, result);
        }
        else
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* No Action */
        }
      }
      else
      {
        if(PduR_LowTpReceive[((uint8)(ptrGWTpPdu->TargetIndexBufType)) &
                        PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
        {
          /* @Trace: PduR_SUD_API_126 */
          (void)PduR_LowTpReceive[((uint8)(ptrGWTpPdu->TargetIndexBufType)) &
                        PDUR_TARGET_INDEX_MASK].TargetLayer(
                    ptrGWTpPdu->TargetPduId, (Std_ReturnType)E_NOT_OK);
        }
        else
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* No Action */
        }
        /* Report to DET */
        /* @Trace: SRS_BSW_00452 */
        (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          PDUR_TP_RX_INDICATION_SID, PDUR_E_PDU_INSTANCES_LOST);
      }
    } /* End else of if (reqLength > bufferSize) */
  } /* @if (BUFREQ_OK == bufReqReturn) */
  else
  {
    /* @Trace: PduR_SUD_API_116 */
    /* Report to DET */
    (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_TP_RX_INDICATION_SID, PDUR_E_PDU_INSTANCES_LOST);
  }
} /* End of PduR_UptrTpRxIndication(
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu,
  P2VAR(PduR_TpPduInfoPtr, AUTOMATIC, PDUR_VAR) LpPduInfoUpdatePtr,
  Std_ReturnType result) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* #if (PDUR_TP_UP_RX_SUPPORT == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
** Function Name        : PduR_CheckPoolBuffer                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_GWTpStartOfReception to check buffer is pool   **
**                        buffer and valid                                    **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduR_TpBuffer ptrTxBuffer,                          **
**                        PduLengthType tpSduLength                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): PduR_PoolVar, PduR_PoolPtr      **
**                                                                            **
** Function(s) invoked  : Det_ReportRuntimeError                              **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CheckPoolBuffer( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  PduLengthType tpSduLength)
{
  uint8 indexPool;
  BufReq_ReturnType returnVal;
  returnVal = (BufReq_ReturnType)BUFREQ_OK;
  #if(PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  if (NULL_PTR == ptrTxBuffer->SinBufPtr)
  {
    if (ptrTxBuffer->CurrentDepth < ptrTxBuffer->FIFODepth)
    {
      if ((ptrTxBuffer->HeadLength >= tpSduLength) ||
        (ptrTxBuffer->TailLength >= tpSduLength))
      {
        /* @Trace: PduR_SUD_API_294 */
        PduR_PoolVar.PoolStatus = (boolean)PDUR_FALSE;
      }
      else
      {
        /* @Trace: PduR_SUD_API_293 */
        PduR_PoolVar.PoolStatus = (boolean)PDUR_TRUE;
      }
    }
    else
    {
      /* @Trace: PduR_SUD_API_292 */
      returnVal = BUFREQ_E_NOT_OK;
      /* Report to DET */
      /* @Trace: SRS_PduR_06106 */
      (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                                              PDUR_STARTOF_RECEPTION_SID,
                                              PDUR_E_PDU_INSTANCES_LOST);
    }
  }
  else
  #endif
  {
    if ((boolean)PDUR_FALSE == ptrTxBuffer->SinBufPtr->FreeBuffer) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
    {
      if (ptrTxBuffer->TotalLength >= tpSduLength)
      {
        PduR_PoolVar.PoolStatus = (boolean)PDUR_FALSE;
      }
      else
      {
        PduR_PoolVar.PoolStatus = (boolean)PDUR_TRUE;
      }
    }
    else
    {
      /* @Trace: PduR_SUD_API_295 */
      returnVal = BUFREQ_E_NOT_OK;
      PduR_PoolVar.PoolStatus = (boolean)PDUR_FALSE;
    }
  }
  if ((BufReq_ReturnType)BUFREQ_OK == returnVal)
  {
    if ((boolean)PDUR_FALSE == PduR_PoolVar.PoolStatus)
    {
      /* @Trace: PduR_SUD_API_296 */
      returnVal = (BufReq_ReturnType)BUFREQ_OK;
    }
    else
    {
      indexPool = PDUR_TP_POOLS_INDEX_COUNT;
      returnVal = (BufReq_ReturnType)BUFREQ_E_OVFL;
      PduR_PoolVar.PoolStatus = (boolean)PDUR_FALSE;
      while (PDUR_ZERO != indexPool)
      {
        indexPool--;
        if (((boolean)PDUR_FALSE == PduR_PoolPtr[indexPool].State) &&
          (PduR_PoolPtr[indexPool].PduMaxLength >= tpSduLength))
        {
          /* @Trace: PduR_SUD_API_298 */
          returnVal = BUFREQ_OK;
          PduR_PoolPtr[indexPool].State = (boolean)PDUR_TRUE;
          PduR_PoolVar.PoolStatus = (boolean)PDUR_TRUE;
          PduR_PoolVar.IndexPool = indexPool;
          indexPool = (uint8)PDUR_ZERO;
        }
        else
        {
          /* @Trace: PduR_SUD_API_297 */
          /* No Action */
        }
      }
    }
  } /* @if ((BufReq_ReturnType)BUFREQ_OK == returnVal) */
  else
  {
    /* No Action */
  }
  return returnVal;
} /* End of PduR_CheckPoolBuffer(
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  PduLengthType tpSduLength) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON) */
#endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
** Function Name        : PduR_CheckBuffer                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_GWTpStartOfReception to check buffer is valid  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : ptrTxBuffer, tpSduLength                            **
**                                                                            **
** InOut parameter      : returnIndex                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : BufReq_ReturnType bufReqReturn                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
** Function(s) invoked  : Det_ReportRuntimeError                              **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_OFF)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CheckBuffer(
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  PduLengthType tpSduLength)
{
  BufReq_ReturnType bufReqReturn;
  #if(PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  if (NULL_PTR == ptrTxBuffer->SinBufPtr)
  {
    if (ptrTxBuffer->CurrentDepth < ptrTxBuffer->FIFODepth)
    {
      if ((ptrTxBuffer->HeadLength >= tpSduLength) ||
        (ptrTxBuffer->TailLength >= tpSduLength))
      {
        /* @Trace: PduR_SUD_API_290 */
        bufReqReturn = BUFREQ_OK;
      }
      else
      {
        /* @Trace: PduR_SUD_API_289 */
        bufReqReturn = BUFREQ_E_OVFL;
      }
    }
    else
    {
      /* @Trace: PduR_SUD_API_288 */
      bufReqReturn = BUFREQ_E_NOT_OK;
      /* Report to DET */
      /* @Trace: SRS_BSW_00452 */
      /* @Trace: SRS_PduR_06106 */
      (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                                              PDUR_STARTOF_RECEPTION_SID,
                                              PDUR_E_PDU_INSTANCES_LOST);
    }
  }
  else
  #endif
  {
    if ((boolean)PDUR_FALSE == ptrTxBuffer->SinBufPtr->FreeBuffer)
    {
      if (ptrTxBuffer->TotalLength >= tpSduLength)
      {
        bufReqReturn = BUFREQ_OK;
      }
      else
      {
        /* @Trace: PduR_SUD_API_198 */
        bufReqReturn = BUFREQ_E_OVFL;
      }
    }
    else
    {
      /* @Trace: PduR_SUD_API_291 */
      bufReqReturn = BUFREQ_E_NOT_OK;
    }
  }
  return bufReqReturn;
} /* End of PduR_CheckBuffer(
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  PduLengthType tpSduLength) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_OFF) */
#endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
** Function Name        : PduR_FindPduIdQueue                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_BuffUpdateLoTpGWCopyRxData, PduR_LowTpTransmit **
**                        PduR_BuffUpdateLoTpStartOfReception,                **
**                        PduR_FreeBuffer, PduR_LoTpRxIndication function to  **
**                        get index FIFO of PduId in FIFO buffer              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduR_TpBuffer ptrTxBuffer, PduIdType rxPduId        **
**                                                                            **
** InOut parameter      : NA                                                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : PduR_TpQueueType ptrQueue                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
** Function(s) invoked  : None                                                **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(uint16, PDUR_CODE) PduR_FindPduIdQueue( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  PduIdType rxPduId)
{
  uint16 returnVal;
  returnVal = PDUR_UNDEFINED;
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  ptrQueue = ptrTxBuffer->FirstQueuePtr;
  while ((NULL_PTR != ptrQueue) &&
    (PDUR_UNDEFINED == returnVal))
  {
    if ((boolean)PDUR_TRUE == ptrQueue->FreeBuffer) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
    {
      if ((ptrQueue->RxPduId == rxPduId) && /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
        (PDUR_RX_ACKNOWLEDGE != ptrQueue->RxState)) /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
      {
        /* @Trace: PduR_SUD_API_095 */
        /* @Trace: PduR_SUD_API_245 */
        returnVal = ptrQueue->IndexFifo; /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
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
    /* @Trace: PduR_SUD_API_096 */
    /* @Trace: PduR_SUD_API_218 */
    ptrQueue = ptrQueue->Next; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "pointer is not null due to data flow" */ /* polyspace RTE:NIP [Not a defect:Low] "initialized variable due to data flow" */
  }
  return returnVal;
} /* End of PduR_FindPduIdQueue(
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  PduIdType rxPduId) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
** Function Name        : PduR_LowTpTransmit                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_GWTpStartOfReception, PduR_LoTpGWCopyRxData,   **
**                        PduR_LoTpRxIndication function to transmit I-PDU    **
**                        in case of gateway operation                        **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduR_TpBuffer ptrTxBuffer,                          **
**                        PduR_GWRxTpPdu ptrGWTpPdu,                          **
**                        PduIdType rxPduId, uint8 serviceId                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType returnVal                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):PduR_TpTransmitService,          **
**                        PduR_PoolPtr, PduR_TpTxQueue                        **
**                                                                            **
** Function(s) invoked  : PduR_FindPduIdQueue, Det_ReportRuntimeError         **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_LowTpTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu,
  PduIdType rxPduId,
  uint8 serviceId)
{
  Std_ReturnType returnVal;
  returnVal = (Std_ReturnType)E_NOT_OK;
  PduInfoType pduInfoUpdatePtr;
  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  uint16 indexFifo;
  #endif
  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  if (NULL_PTR == ptrTxBuffer->SinBufPtr)
  {
    /* @Trace: PduR_SUD_API_097 */
    indexFifo = PduR_FindPduIdQueue(ptrTxBuffer, rxPduId);
    ptrQueue = &PduR_TpTxQueue[indexFifo];
    if (PDUR_UNDEFINED != indexFifo)
    {
      /* @Trace: SRS_PduR_06127 */
      if (ptrTxBuffer->FirstQueuePtr->IndexList == ptrQueue->IndexList) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace DEFECT:OUT_BOUND_PTR [Not a defect:Low] "indexFifo never is 0xFFFF by it is prevent by condition before" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
      {
        #if (PDUR_TP_TXCONFIRMATION == STD_ON)
        if (PduR_TpTransmitService [
        (uint8)(ptrGWTpPdu->TargetIndexBufType) &
        (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
        {
          (*(ptrGWTpPdu->RamArea)) = PDUR_RX_TX_COMPLETED;
          /* @Trace: PduR_SUD_API_104 */
          returnVal =
            PduR_TpTransmitService [(uint8)(
            ptrGWTpPdu->TargetIndexBufType) &
            (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer(
            ptrGWTpPdu->TargetPduId, &ptrQueue->PduInfoPtr);
          if ((Std_ReturnType)E_OK == returnVal)
          {
            /* @Trace: PduR_SUD_API_106 */
            /* @Trace: PduR_SUD_API_251 */
            (*(ptrGWTpPdu->RamArea)) = PDUR_RX_TX_COMPLETED_RESULT_OK;
            ptrQueue->TxConfirm++;
          }
          else
          {
            /* @Trace: PduR_SUD_API_105 */
            /* @Trace: PduR_SUD_API_250 */
            /* Report to DET */
            /* @Trace: SRS_BSW_00452 */
            (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
              serviceId, PDUR_E_TP_TX_REQ_REJECTED);
          }
        }
        else
        #endif /* #if (PDUR_TP_TXCONFIRMATION == STD_ON) */
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* No Action */
        }
      }
      else
      {
        /* @Trace: PduR_SUD_API_103 */
        /* @Trace: PduR_SUD_API_249 */
        returnVal = (Std_ReturnType)E_OK;
      }
    }
    else
    {
      /* No Action */
    }
  }
  else
  #endif
  {
    PDUR_UNUSED(rxPduId);
    #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
    if ((boolean)PDUR_TRUE == ptrTxBuffer->SinBufPtr->PoolStatus) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
    {
      /* @Trace: PduR_SUD_API_098 */
      /* @Trace: PduR_SUD_API_247 */
      pduInfoUpdatePtr.SduDataPtr =
        PduR_PoolPtr[ptrTxBuffer->SinBufPtr->IndexPool].SduPtr; /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "Index poor support range from 0..255" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
    }
    else
    #endif
    {
      /* @Trace: PduR_SUD_API_099 */
      /* @Trace: PduR_SUD_API_248 */
      /* Get the Sdu data pointer from Tx Buffer */
      pduInfoUpdatePtr.SduDataPtr = ptrTxBuffer->SduPtr;
    }
    pduInfoUpdatePtr.SduLength = ptrTxBuffer->SinBufPtr->ReqLength; /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
    pduInfoUpdatePtr.MetaDataPtr = ptrTxBuffer->MetaPtr;
    #if (PDUR_TP_TXCONFIRMATION == STD_ON)
    if (PduR_TpTransmitService [
      (uint8)(ptrGWTpPdu->TargetIndexBufType) &
      (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
    {
      (*(ptrGWTpPdu->RamArea)) = (uint8)PDUR_RX_TX_COMPLETED;
      returnVal =
        PduR_TpTransmitService [(uint8)(
        ptrGWTpPdu->TargetIndexBufType) &
        (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer(
        ptrGWTpPdu->TargetPduId, &pduInfoUpdatePtr);
      if ((Std_ReturnType)E_OK == returnVal)
      {
        /* @Trace: PduR_SUD_API_101 */
        /* @Trace: PduR_SUD_API_253 */
        (*(ptrGWTpPdu->RamArea)) = PDUR_RX_TX_COMPLETED_RESULT_OK;
        ptrTxBuffer->SinBufPtr->TxConfirm++; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
      }
      else
      {
        /* @Trace: PduR_SUD_API_102 */
        /* @Trace: PduR_SUD_API_254 */
        /* Report to DET */
        /* @Trace: SRS_BSW_00452 */
        (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        serviceId, PDUR_E_TP_TX_REQ_REJECTED);
      }
    }
    else
    #endif /* #if (PDUR_TP_TXCONFIRMATION == STD_ON) */
    { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
      /* No Action */
    }
  }
  return returnVal;
} /* End of PduR_LowTpTransmit(
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu,
  PduIdType rxPduId,
  uint8 serviceId) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
** Function Name        : PduR_FreeBuffer                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_GWTpStartOfReception, PduR_LoTpGWCopyRxData,   **
**                        PduR_LoTpRxIndication function to free buffer if    **
**                        all destination failed                              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduR_TpBuffer ptrTxBuffer,                          **
**                        PduIdType rxPduId                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): PduR_TpTxQueue, PduR_LoRxConfig **
**                                                                            **
** Function(s) invoked  : PduR_FindPduIdQueue                                 **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if(PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
static FUNC(void, PDUR_CODE) PduR_FreeBuffer( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  PduIdType rxPduId, uint8 serviceId)
#else
static FUNC(void, PDUR_CODE) PduR_FreeBuffer( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_TpBuffer, AUTOMATIC, PDUR_CONST) ptrTxBuffer,
  PduIdType rxPduId, uint8 serviceId)
#endif
{
  P2VAR(PduR_TpSingleBuffer, AUTOMATIC, PDUR_VAR) ptrSinBuf;
  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) ptrTpRxIndication;
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu;
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  uint16 indexFifo;
  Std_ReturnType returnVal;
  #if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON)
  uint8 noOfRoutePdu;
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* @Trace: PduR_SUD_API_427 */
  /* Get the pointer to ptrLoRxSource structure */
  ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
  /* Get the pointer to ptrTpRxIndication structure */
  ptrTpRxIndication = (P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST))
                               (ptrLoRxSource->LoIfTpSource);
  #else
  /* @Trace: PduR_SUD_API_426 */
  /* Get ptrTpRxIndication to local pointer*/
  ptrTpRxIndication = &PduR_LowTpRxIndication[rxPduId];
  #endif
  /* Assign Local Pointer to LoGWRxIndication Structure */
  ptrGWTpPdu = ptrTpRxIndication->GWRxTpPdu;
  /* Get the Number of Route for Source PDU */
  noOfRoutePdu = ptrTpRxIndication->TargetIndexOrNoOfRoute &
    (uint8)PDUR_NOOFROUTE_MASK;
  /* Loop for the Number of Route of the Source PDU */
  do
  {
    if (PDUR_RX_TX_COMPLETED_RESULT_OK == (*(ptrGWTpPdu->RamArea))) /* polyspace RTE:IDP [Justified:Low] "ptrGWTpPdu pointer is in range of bound due to dependency on generation rule" */
    {
      /* Invoke Cancel transmit frunction */
      if (PduR_UpTpCancellation[(uint8)(
        ptrGWTpPdu->TargetIndexBufType) &
        (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer !=NULL_PTR)
      {
        /* @Trace: PduR_SUD_API_425 */
        (void)PduR_UpTpCancellation[(uint8)(
                          ptrGWTpPdu->TargetIndexBufType) &
                          (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer(
                          ptrGWTpPdu->TargetPduId);
      }
      else
      { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
        /* @Trace: PduR_SUD_API_428 */
        /* No Action */
      }
    }
    else
    {
      /* No Action */
    }
    /* Set state of transmit in case of gateway to default */
    (*(ptrGWTpPdu->RamArea)) = PDUR_RX_TX_NOT_COMPLETED;
    /* Increment the ptrGWTpPdu Pointer */
    ptrGWTpPdu++;
    /* Decrement the Number of Route PDU */
    noOfRoutePdu--;
  } while ((uint8)PDUR_ZERO != noOfRoutePdu);
  #endif
  if (NULL_PTR == ptrTxBuffer->SinBufPtr)
  {
    indexFifo = PduR_FindPduIdQueue(ptrTxBuffer, rxPduId);
    if (PDUR_UNDEFINED != indexFifo)
    {
      ptrQueue = &PduR_TpTxQueue[indexFifo];
      do
      {
        if ((boolean)PDUR_TRUE == ptrQueue->FreeBuffer) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
        {
          /* @Trace: PduR_SUD_API_386 */
          ptrTxBuffer->CurrentDepth--;
          ptrQueue->RxState    = PDUR_RX_YETTOSTART;
          ptrQueue->FreeBuffer = (boolean)PDUR_FALSE;
          #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
          if ((boolean)PDUR_TRUE == ptrQueue->PoolStatus) /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
          {
            /* @Trace: PduR_SUD_API_387 */
            PduR_PoolPtr[ptrQueue->IndexPool].State = PDUR_FALSE; /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "index poor support range from 0..255" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
            ptrQueue->PoolStatus = (boolean)PDUR_FALSE;
          }
          else
          {
            /* No Action */
          }
          #endif
        }
        else
        {
          /* No Action */
        }
        if ((uint8)PDUR_ZERO != ptrTxBuffer->CurrentDepth)
        {
          if (ptrTxBuffer->FirstQueuePtr->IndexList == ptrQueue->IndexList) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
          {
            ptrTxBuffer->FirstQueuePtr = ptrQueue->Next; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized variable due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
            /* Increment TailLength */
            ptrTxBuffer->TailLength += ptrQueue->ReqLength; /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
            /* Get ptrQueue to first queue */
            /* @Trace: SRS_PduR_06127 */
            ptrQueue = ptrTxBuffer->FirstQueuePtr;
            if ((boolean)PDUR_TRUE == ptrQueue->FreeBuffer) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
            {
              #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
              /* @Trace: PduR_SUD_API_392 */
              /* Get the pointer to ptrLoRxSource structure */
              ptrLoRxSource = &PduR_LoRxConfig[ptrQueue->RxPduId];
              /* Get the pointer to ptrTpRxIndication structure */
              ptrTpRxIndication = (P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST))
                               (ptrLoRxSource->LoIfTpSource);
              #else
              /* @Trace: PduR_SUD_API_391 */
              /* Get ptrTpRxIndication to local pointer*/
              ptrTpRxIndication = &PduR_LowTpRxIndication[ptrQueue->RxPduId]; /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
              #endif
              /* Get ptrGWTpPdu to local pointer*/
              ptrGWTpPdu = ptrTpRxIndication->GWRxTpPdu; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
              /* Check threshold is reached */
              /* @Trace: SRS_PduR_06026 */
              if ((PDUR_RX_ACKNOWLEDGE == ptrQueue->RxState) /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
              #if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON)
                || (ptrQueue->CopiedLength >= ptrGWTpPdu->TpThreshold) /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
              #endif
                )
              {
                returnVal =
                  PduR_TpTransmitService [(uint8)(
                  ptrGWTpPdu->TargetIndexBufType) &
                  (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer(
                  ptrGWTpPdu->TargetPduId, &ptrQueue->PduInfoPtr);
                /* polyspace-begin MISRA-C:2012 1.1 [Not a defect:Low] "Due to behavior of function" */
                if ((Std_ReturnType)E_OK == returnVal)
                {
                  /* @Trace: PduR_SUD_API_395 */
                  (*(ptrGWTpPdu->RamArea)) = PDUR_RX_TX_COMPLETED;
                  ptrQueue->TxConfirm++; /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
                }
                else
                {
                  /* @Trace: PduR_SUD_API_394 */
                  /* Report to DET */
                  (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                    serviceId, PDUR_E_TP_TX_REQ_REJECTED);
                }
                /* polyspace-end MISRA-C:2012 1.1 [Not a defect:Low] "Due to behavior of function" */
              }
              else
              {
                /* @Trace: PduR_SUD_API_393 */
                returnVal = (Std_ReturnType)E_OK;
              }
            }
            else
            {
              /* @Trace: PduR_SUD_API_390 */
              returnVal = (Std_ReturnType)E_NOT_OK;
            }
          }
          else
          {
            /* @Trace: PduR_SUD_API_389 */
            returnVal = (Std_ReturnType)E_OK;
          }
        }
        else
        {
          /* @Trace: PduR_SUD_API_388 */
          ptrTxBuffer->FirstQueuePtr = NULL_PTR;
          /* Reset HeadLength buffer queue */
          ptrTxBuffer->HeadLength = ptrTxBuffer->TotalLength;
          returnVal = (Std_ReturnType)E_OK;
        }
      } while ((Std_ReturnType)E_NOT_OK == returnVal);
    }
    else
    {
      /* No Action */
    }
  }
  else
  #endif /* #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON) */
  {
    PDUR_UNUSED(rxPduId);
    PDUR_UNUSED(serviceId); /* polyspace RTE:UNR [Not a defect:Low] "Always true condition is expected behavior" */
    ptrSinBuf = ptrTxBuffer->SinBufPtr;
    if ((boolean)PDUR_TRUE == ptrSinBuf->FreeBuffer) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
    {
      /* @Trace: PduR_SUD_API_396 */
      ptrSinBuf->RxState    = PDUR_RX_YETTOSTART;
      ptrSinBuf->FreeBuffer  = (boolean)PDUR_FALSE;
      #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
      if ((boolean)PDUR_TRUE == ptrSinBuf->PoolStatus) /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */
      {
        /* @Trace: PduR_SUD_API_397 */
        PduR_PoolPtr[ptrSinBuf->IndexPool].State = PDUR_FALSE; /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "index poor support range from 0..255" */ /* polyspace RTE:NIV [Not a defect:Low] "initialized variable" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
        ptrSinBuf->PoolStatus = (boolean)PDUR_FALSE;
      }
      else
      {
        /* No Action */
      }
      #endif
    }
    else
    {
      /* No Action */
    }
  }
} /* End of PduR_FreeBuffer(
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  PduIdType rxPduId) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
