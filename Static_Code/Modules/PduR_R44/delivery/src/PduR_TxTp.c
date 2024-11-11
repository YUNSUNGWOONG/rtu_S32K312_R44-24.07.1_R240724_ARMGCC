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
**  SRC-MODULE: PduR_TxTp.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of the common functionality of PduR_LoTpCopyTxData()**
**              PduR_DETCheckLoTpCopyTxData(), PduR_LoTpGWCopyTxData,         **
**              PduR_DETCheckLoTpTxConfirmation(), PduR_LoTpTxConfirmation()  **
**              PduR_SortPriorityQueue(), PduR_FifoMulticastTransmit()        **
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
** 1.0.5       11-Nov-2022   HaoTA4      CP44-383                             **
** 1.0.4       11-Aug-2022   PhucNHM     CP44-635                             **
** 1.0.2       05-Oct-2021   PhucNHM     R44-Redmine #20586                   **
** 1.0.1       22-Jun-2021   PhucNHM     R44-Redmine #18951                   **
** 1.0.0       04-Dec-2020   AUTOEVER    Initial Version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: PduR_SUD_FILE_001 */
#include "PduR.h"               /* Header File */
#include "PduR_TxTp.h"          /* Header file for PduR_TxTp.c */
#include "SchM_PduR.h"          /* Schedular Manager header file */

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
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpGWCopyTxData( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) ptrCopyTxData,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pduInfoPtr,
  P2CONST(RetryInfoType, AUTOMATIC, PDUR_CONST) ptrRetry,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) availableDataPtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_GWLoTpTxConfirmation( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) ptrTpCopyTxDataBuf);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && \
    (PDUR_TP_TXCONFIRMATION == STD_ON))
#if (PDUR_MULTICAST_GATEWAY_TP_FIFO_SUPPORT == STD_ON) &&\
   (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_FifoMulticastTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  uint8 rxPduIndex,
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrQueue);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, PDUR_CODE) PduR_SortPriorityQueue(
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_CONST) ptrQueue);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DETCheckLoTpCopyTxData( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType txPduId, uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr,
  P2CONST(PduLengthType, AUTOMATIC, PDUR_CONST) ptrAvailableDataPtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, PDUR_CODE) PduR_DETCheckLoTpTxConfirmation( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType txPduId, PduIdType moduleType);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : PduR_LoTpCopyTxData                                 **
**                                                                            **
** Service ID           : 0x43                                                **
**                                                                            **
** Description          : This function is called by the TP for               **
**                        requesting a transmit buffer.The length of the      **
**                        buffer does not need to be the length of the        **
**                        complete N-SDU to be transmitted. It only needs to  **
**                        be as large as required by the caller of that       **
**                        service (Length).Within this function, the PDU      **
**                        Router shall translate the TpTxPduId into the       **
**                        configured target PDU ID and route this request to  **
**                        the configured target function.                     **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType txPduId,                                  **
**                        uint8 moduleType, PduInfoType *ptrPduInfoPtr,       **
**                        RetryInfoType *ptrRetry,                            **
**                        PduLengthType *ptrAvailableDataPtr                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PduLengthType ptrAvailableDataPtr                   **
**                                                                            **
** Return parameter     : BufReq_ReturnType bufReqReturn                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_LowTpCopyTxDataBuf,                            **
**                        PduR_LowTpCopyTxData,                               **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckLoTpCopyTxData()                       **
**                        PduR_LoTpGWCopyTxData()                             **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_PduR_06020 */
/* @Trace: SRS_PduR_06117 */
/* @Trace: SRS_BSW_00167 */
/* @Trace: SRS_BSW_00171 */
/* @Trace: SRS_PduR_06121 */
#if(PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
/* @Traceability BEGIN -- SRS: SWS_PduR_00697 SWS_PduR_00814 SWS_PduR_00330
                               SWS_PduR_00813 SWS_PduR_00707 SWS_PduR_00715
                               SWS_PduR_00696 SWS_PduR_00705 SWS_PduR_00100
                               SWS_PduR_00815 SWS_PduR_00740 SWS_PduR_00119
                               SWS_PduR_00744 SWS_PduR_00299 SWS_PduR_00221
                               SWS_PduR_00676 SWS_PduR_00631 SWS_PduR_00518
                               SWS_PduR_00632 SWS_PduR_00287 SWS_PduR_00161
                               SWS_PduR_00824 SWS_PduR_00013 SWS_PduR_00764
                               SWS_PduR_00818 */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyTxData(PduIdType txPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr,
  P2CONST(RetryInfoType, AUTOMATIC, PDUR_CONST) ptrRetry,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) ptrAvailableDataPtr)
#else
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyTxData(PduIdType txPduId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr,
  P2CONST(RetryInfoType, AUTOMATIC, PDUR_CONST) ptrRetry,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) ptrAvailableDataPtr)
#endif
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoTxDestination, AUTOMATIC, PDUR_CONST) ptrLoTxDestination;
  #endif
  #if ((PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON) &&\
    (PDUR_TP_TRANSMIT == STD_ON))
  P2VAR(PduR_MulticastTpInfo, AUTOMATIC, PDUR_VAR) ptrMulticastTpInfo;
  RetryInfoType retryForMulti;
  #endif
  P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) ptrTpCopyTxData;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif
  /* Local variable to hold the return value of the function */
  BufReq_ReturnType bufReqReturn;
  /* Check for DET */
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  bufReqReturn = PduR_DETCheckLoTpCopyTxData(txPduId, moduleType,
    ptrPduInfoPtr, ptrAvailableDataPtr);
  /* Check whether any development errors are detected */
  if ((BufReq_ReturnType)BUFREQ_OK == bufReqReturn)
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_352 */
    /* Get pointer to LoTxDestination from PduR_ConfigSet */
    ptrLoTxDestination = &PduR_LoTxConfig[txPduId];
    /* Get pointer to ptrTpCopyTxData from ptrLoTxDestination */
    ptrTpCopyTxData = (P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST))
                                  (ptrLoTxDestination->LoIfTpDestiantion);
    #else
    /* @Trace: PduR_SUD_API_351 */
    /* Get the pointer to ptrTpCopyTxData from PduR_LowTpCopyTxDataBuf*/
    ptrTpCopyTxData = &PduR_LowTpCopyTxDataBuf[txPduId];
    #endif
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    groupIdValue = ptrTpCopyTxData->GroupMaskValue;
    indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
    idConvert = groupIdValue % PDUR_BITMASK_UINT8;
    /* @Trace: SRS_PduR_06120 */
    /* Check if routing path is enabled */
    if ((PDUR_UNDEFINED == groupIdValue) ||
        ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] &
                                          (((uint32)PDUR_ONE) << idConvert))))
    #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
    {
      /* Check if gateway present */
      #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
      if ((uint8)PDUR_ZERO != (ptrTpCopyTxData->TargetIndex &
                                                   PDUR_GATEWAY_MASK))
      {
        /* @Trace: PduR_SUD_API_211 */
        bufReqReturn =
                  PduR_LoTpGWCopyTxData(ptrTpCopyTxData, ptrPduInfoPtr,
                    ptrRetry, ptrAvailableDataPtr);
      }
      else
      #endif
      {
        #if (PDUR_TP_TRANSMIT == STD_ON)
        #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
        if ((uint8)PDUR_ZERO != (ptrTpCopyTxData->TargetIndex & /* polyspace MISRA-C:2012 10.1 10.4 [Not a defect:Low] "all variable and macro in expressions are define is hex number 8bit and have range valid" */
                                                (uint8)PDUR_MULTICAST_MASK))
        {
          ptrMulticastTpInfo = (ptrTpCopyTxData->MulticastTpInfo);
          if ((boolean)PDUR_TRUE == ptrMulticastTpInfo->FirstLower) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
          {
            /* @Trace: PduR_SUD_API_420 */
            ptrMulticastTpInfo->FirstLower = (boolean)PDUR_FALSE;
            /* Set TpDataState to TP_CONFPENDING for first destination lower */
            retryForMulti.TpDataState = TP_CONFPENDING;
            /* Set value of TxTpDataCnt not change  */
            retryForMulti.TxTpDataCnt = (PduLengthType)PDUR_ZERO;
          }
          else
          {
            /* @Trace: PduR_SUD_API_207 */
            /* Set TpDataState to TP_CONFPENDING for first destination lower */
            retryForMulti.TpDataState = TP_DATARETRY;
            /* Set value of TxTpDataCnt not change  */
            /* polyspace +2 MISRA-C3:D4.14 [Not a defect:Low] "ptrPduInfoPtr is checked null by PduR_DETCheckLoTpCopyTxData function" */
            /* polyspace +1 RTE:IDP [Not a defect:Unset] "configured memory access index" */
            retryForMulti.TxTpDataCnt = ptrPduInfoPtr->SduLength;
          }
          /* Invoke the Dcm_CopyTxData() API and get the return value */
          if (PduR_LowTpCopyTxData[ptrTpCopyTxData->TargetIndex & /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "Array index is valid due to data flow" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
            (uint8)PDUR_TPCOPYTX_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
          {
            /* @Trace: PduR_SUD_API_208 */
            bufReqReturn =
              PduR_LowTpCopyTxData[ptrTpCopyTxData->TargetIndex &
                (uint8)PDUR_TPCOPYTX_TARGET_INDEX_MASK].TargetLayer
                (ptrTpCopyTxData->UpTargetPduId, ptrPduInfoPtr, &retryForMulti,
                ptrAvailableDataPtr);
          }
          else
          { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
            /* @Trace: PduR_SUD_API_209 */
            bufReqReturn = BUFREQ_E_NOT_OK;
          }
        }
        else
        #endif /* #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON) */
        {
          /* Invoke the <Up>_CopyTxData() API and get the return value */
          if (PduR_LowTpCopyTxData[ptrTpCopyTxData->TargetIndex & /* polyspace RTE:OBAI [Not a defect:Low] "configured memory access index" */ /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "Array index is valid due to data flow" */
                (uint8)PDUR_TPCOPYTX_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
          {
            /* @Trace: PduR_SUD_API_210 */
            bufReqReturn =
            PduR_LowTpCopyTxData[ptrTpCopyTxData->TargetIndex &
                (uint8)PDUR_TPCOPYTX_TARGET_INDEX_MASK].TargetLayer
              (ptrTpCopyTxData->UpTargetPduId, ptrPduInfoPtr, ptrRetry,
              ptrAvailableDataPtr);
          }
          else
          { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
            bufReqReturn = BUFREQ_E_NOT_OK;
          }
        }
        #endif /* #if(PDUR_TP_TRANSMIT == STD_ON) */
      }
    }
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    else
    { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
      /* @Trace: PduR_SUD_API_206 */
      bufReqReturn = BUFREQ_E_NOT_OK;
    }
    #endif
  } /* @if (BUFREQ_OK == bufReqReturn) */
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* @Trace: PduR_SUD_API_205 */
    /* No Action */
  }
  #endif
  /* return the Return value */
  return (bufReqReturn);
} /* End of PduR_LoTpCopyTxData(PduIdType txPduId, P2VAR(PduInfoType,
  *AUTOMATIC, PDUR_VAR) ptrPduInfoPtr, P2VAR(RetryInfoType, AUTOMATIC,
  *PDUR_VAR) ptrRetry, P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR)
  *ptrAvailableDataPtr) */
/* @Traceability END -- SRS: SWS_PduR_00697 SWS_PduR_00814 SWS_PduR_00330
                               SWS_PduR_00813 SWS_PduR_00707 SWS_PduR_00715
                               SWS_PduR_00696 SWS_PduR_00705 SWS_PduR_00100
                               SWS_PduR_00815 SWS_PduR_00740 SWS_PduR_00119
                               SWS_PduR_00744 SWS_PduR_00299 SWS_PduR_00221
                               SWS_PduR_00676 SWS_PduR_00631 SWS_PduR_00518
                               SWS_PduR_00632 SWS_PduR_00287 SWS_PduR_00161
                               SWS_PduR_00824 SWS_PduR_00013 SWS_PduR_00764
                               SWS_PduR_00818 */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_TP_TXCONFIRMATION == STD_ON)  */
#endif

/*******************************************************************************
** Function Name        : PduR_DETCheckLoTpCopyTxData                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the PduR_LoTpCopyTxData  **
**                        to check the parameters passed are valid and        **
**                        buffer does not need to be the length of the        **
**                        report to DET in case of invalid values.            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType txPduId,uint8 moduleType,                 **
**                        PduInfoType *ptrPduInfoPtr,                         **
**                        PduLengthType *ptrAvailableDataPtr                  **
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
**                        PduR_InitStatus, PduR_LowTpCopyTxDataBuf            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if(PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
 static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DETCheckLoTpCopyTxData( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType txPduId, uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr,
  P2CONST(PduLengthType, AUTOMATIC, PDUR_CONST) ptrAvailableDataPtr)
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoTxDestination, AUTOMATIC, PDUR_CONST) ptrLoTxDestination;
  #endif
  P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) ptrTpCopyTxData;
  BufReq_ReturnType bufReqReturn;
  /* Initialize buffer return type to "BUFREQ_OK" */
  bufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
  /* Check whether the module is initialised */
  if (PDUR_UNINIT == PduR_InitStatus)
  {
    /* @Trace: SRS_BSW_00406 */
    /* @Trace: PduR_SUD_API_255 */
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_COPYTX_DATA_SID, PDUR_E_UNINIT);
    /* Set the return value to BUFREQ_E_NOT_OK  */
    bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
  } /* End of if (PDUR_UNINIT == PduR_InitStatus) */
  else
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_349 */
    if (txPduId >= PduR_IfTpConfirmationMaxPduId)
    #else
    /* @Trace: PduR_SUD_API_348 */
    if (txPduId >= PDUR_TP_TXCONFIRMATION_MAXPDUID)
    #endif
    {
      /* Report to DET */
      /* @Trace: SRS_PduR_06103 */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_COPYTX_DATA_SID, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to BUFREQ_E_NOT_OK */
      bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
    } /* End of if (txPduId >= PDUR_TP_TXCONFIRMATION_MAXPDUID) */
    else
    {
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_OFF)
      /* Get the pointer to ptrTpCopyTxData from PduR_LowTpCopyTxDataBuf*/
      ptrTpCopyTxData = &PduR_LowTpCopyTxDataBuf[txPduId];
      #else
      /* Get pointer to ptrLoTxDestination from PduR_LoTxConfig */
      ptrLoTxDestination = &PduR_LoTxConfig[txPduId];
      /* Get pointer to ptrTpCopyTxData from ptrLoTxDestination */
      ptrTpCopyTxData = (P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST))
                                  (ptrLoTxDestination->LoIfTpDestiantion);
      if ((boolean)PDUR_FALSE !=
                              (boolean)ptrLoTxDestination->IsInterfaceRouting)
      {
        /* @Trace: PduR_SUD_API_350 */
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          PDUR_COPYTX_DATA_SID, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to BUFREQ_E_NOT_OK */
        bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
      }
      else
      #endif
      {
        if (ptrTpCopyTxData->ModuleType != moduleType)
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* Report to DET */
          /* @Trace: SRS_PduR_06103 */
          /* @Trace: PduR_SUD_API_257 */
          (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
            PDUR_COPYTX_DATA_SID, PDUR_E_PDU_ID_INVALID);
          /* Set the error flag to BUFREQ_E_NOT_OK */
          bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
        } /* (ptrTpCopyTxData->ModuleType != moduleType) */
        else
        {
          #if(PDUR_TP_GATEWAY_OPERATION == STD_ON)
          /* Check routing is gateway */
          if ((uint8)PDUR_ZERO != (ptrTpCopyTxData->TargetIndex & /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
                                                  PDUR_GATEWAY_MASK))
          {
            /* Check If PduInfoPtr is NULL_PTR */
            if (NULL_PTR == ptrPduInfoPtr)
            {
              /* @Trace: PduR_SUD_API_258 */
              /* Report to DET */
              (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                PDUR_COPYTX_DATA_SID, PDUR_E_PARAM_POINTER);
              /* Set the return value to BUFREQ_E_NOT_OK  */
              bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
            } /* End of if (NULL_PTR == ptrPduInfoPtr) */
            /* Check If PduInfoPtr is NULL_PTR */
            else
            {
              if (((uint8)PDUR_ZERO != ptrPduInfoPtr->SduLength) && /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "ptrPduInfoPtr is checked null by if (NULL_PTR == ptrPduInfoPtr)" */
                (NULL_PTR == ptrPduInfoPtr->SduDataPtr))
              {
                /* @Trace: PduR_SUD_API_421 */
                /* Report to DET */
                (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                PDUR_COPYTX_DATA_SID, PDUR_E_PARAM_POINTER);
                /* Set the return value to BUFREQ_E_NOT_OK  */
                bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
              } /* End of if (NULL_PTR == ptrPduInfoPtr->SduDataPtr) */
              else
              {
                /* No Action */
              }
            }
            /* Check If ptrAvailableDataPtr is NULL_PTR */
            if (NULL_PTR == ptrAvailableDataPtr)
            {
              /* @Trace: PduR_SUD_API_259 */
              /* Report to DET */
              (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                PDUR_COPYTX_DATA_SID, PDUR_E_PARAM_POINTER);
              /* Set the return value to BUFREQ_E_NOT_OK  */
              bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
            } /* End of if (NULL_PTR == ptrAvailableDataPtr) */
            else
            {
              /* No Action */
            }
          }
          else
          #endif
          {
            /* No Action */
          }
        }
      }
    }
  }

  #if(PDUR_TP_GATEWAY_OPERATION == STD_OFF)
  PDUR_UNUSED_PTR(ptrPduInfoPtr);
  PDUR_UNUSED_PTR(ptrAvailableDataPtr);
  #endif

  return (bufReqReturn);
} /* End of PduR_DETCheckLoTpCopyTxData
   *(PduIdType txPduId, uint8 moduleType,
   *P2VAR(PduInfoType, AUTOMATIC,PDUR_VAR) ptrPduInfoPtr,
   *P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) ptrAvailableDataPtr)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
#endif /* #if (PDUR_TP_TXCONFIRMATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_LoTpGWCopyTxData                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the TP for               **
**                        requesting a gate buffer in case of gateway.The     **
**                        length of the buffer does not need to be the length **
**                        of the complete N-SDU to be transmitted. It only    **
**                        needs to be as large as required by the caller of   **
**                        that service (Length).Within this function, the PDU **
**                        Router shall translate the TpTxPduId into the       **
**                        configured target PDU ID and route this request to  **
**                        the configured target function.                     **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduR_TpCopyTxDataBuf *ptrCopyTxData,                **
**                        PduInfoType *pduInfoPtr, RetryInfoType *ptrRetry    **
**                        PduLengthType *availableDataPtr                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PduLengthType *ptrAvailableDataPtr                  **
**                                                                            **
** Return parameter     : BufReq_ReturnType bufReqReturn                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_TpTxBuffer, PduR_PoolPtr                       **
**                                                                            **
** Function(s) invoked  : SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA()        **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
 static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpGWCopyTxData( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) ptrCopyTxData,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_VAR) pduInfoPtr,
  P2CONST(RetryInfoType, AUTOMATIC, PDUR_CONST) ptrRetry,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) availableDataPtr)
{
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) destSduDataPtr;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) sduDataPtr;
  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  #endif
  PduLengthType sduLengthVar;
  BufReq_ReturnType bufReqReturn;
  PduLengthType copiedLength;
  PduLengthType reqLength;
  boolean abortCopyTxData;
  abortCopyTxData = (boolean)PDUR_FALSE;
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* Get pointer from Tx Buffer address */
  ptrTxBuffer = &PduR_TpBufferConfig[ptrCopyTxData->TxBufferIndex];
  #else
  /* Get pointer from Tx Buffer address */
  ptrTxBuffer = &PduR_TpTxBuffer[ptrCopyTxData->TxBufferIndex];
  #endif
  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  if (NULL_PTR == ptrTxBuffer->SinBufPtr) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
  {
    /* @Trace: SRS_PduR_06127 */
    ptrQueue     = ptrTxBuffer->FirstQueuePtr;
    if (NULL_PTR != ptrQueue)
    {
      /* @Trace: PduR_SUD_API_260 */
      sduDataPtr   = ptrQueue->PduInfoPtr.SduDataPtr; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
      copiedLength = ptrQueue->CopiedLength; /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
      reqLength    = ptrQueue->ReqLength; /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
    }
    else
    {
      /* @Trace: PduR_SUD_API_429 */
      abortCopyTxData = (boolean)PDUR_TRUE;
    }
  }
  else
  #endif
  {
    /* polyspace +2 RTE:IDP [Justified:Low] "ptrTxBuffer->SinBufPtr pointer is in range of bound due to dependency on generation rule" */
    /* polyspace +1 RTE:NIV [Justified:Low] "ptrTxBuffer->SinBufPtr->FreeBuffer variable always is initialize in PduR_Init()" */
    if ((boolean)PDUR_TRUE == ptrTxBuffer->SinBufPtr->FreeBuffer)
    {
      #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
      if ((boolean)PDUR_TRUE == ptrTxBuffer->SinBufPtr->PoolStatus) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
      {
        /* @Trace: PduR_SUD_API_261 */
        sduDataPtr = PduR_PoolPtr[ptrTxBuffer->SinBufPtr->IndexPool].SduPtr; /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "index poor support range from 0..255" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */ /* polyspace RTE:OBAI [Not a defect:Low] "Array index is valid" */
      }
      else
      #endif
      {
        /* @Trace: PduR_SUD_API_262 */
        /* Get the Sdu data pointer from Tx Buffer */
        sduDataPtr = ptrTxBuffer->SduPtr;
      }
      copiedLength = ptrTxBuffer->SinBufPtr->CopiedLength; /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
      reqLength    = ptrTxBuffer->SinBufPtr->ReqLength; /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
    }
    else
    {
      /* @Trace: PduR_SUD_API_431 */
      abortCopyTxData = (boolean)PDUR_TRUE;
    }
  }
  /* Abort copy data when buffer is free */
  if ((boolean)PDUR_FALSE == abortCopyTxData)
  {
    /* Set SduLength in PduInfoPtr to local variable */
    /* polyspace +2 MISRA-C3:D4.14 [Not a defect:Low] "pduInfoPtr is checked null by PduR_DETCheckLoTpCopyTxData function" */
    /* polyspace +1 RTE:IDP [Not a defect:Unset] "configured memory access index" */
    sduLengthVar = pduInfoPtr->SduLength;
    if ((PduLengthType)PDUR_ZERO == sduLengthVar)
    {
      /* @Trace: PduR_SUD_API_263 */
      /* Update available data in buffer */
      /* polyspace +2 RTE:IDP [Not a defect:Unset] "availableDataPtr NULL check performed in PduR_DETCheckLoTpCopyTxData" */
      /* polyspace +1 RTE:NIVL [Justified:Low] "reqLength always is initialize when abortCopyTxData is PDUR_FALSE" */
      *availableDataPtr = reqLength - (*(ptrCopyTxData->RamArea));
      /* Set return value as BUFREQ_OK */
      bufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
    }
    else
    {
      /* TPs which doesn't support the Retransmission, will send retry as
        NULL_PTR or TP_CONFPENDING or TP_DATACONF*/
      if ((NULL_PTR == ptrRetry) || (TP_DATARETRY != ptrRetry->TpDataState))
      {
        /* check whether we have requested length of data for copy */
        /* #2304 : type casting error for TP SF gateway */
        if (((PduLengthType)(*(ptrCopyTxData->RamArea)) + sduLengthVar) <=
          copiedLength) /* polyspace RTE:NIVL [Justified:Low] "copiedLength always is initialize when abortCopyTxData is PDUR_FALSE" */
        {
          /* Set the return value to BUFREQ_OK */
          bufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
          /* @Trace: SRS_BSW_00312 */
          SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
          if (sduLengthVar == reqLength)  /* polyspace RTE:NIVL [Justified:Low] "reqLength always is initialize when abortCopyTxData is PDUR_FALSE" */
          {
            /* @Trace: PduR_SUD_API_266 */
            (*(ptrCopyTxData->RamAreaFrame)) = PDUR_TRANSMITSSION_SINGLE_FRAME;
          }
          else
          {
            /* @Trace: PduR_SUD_API_265 */
            (*(ptrCopyTxData->RamAreaFrame)) = PDUR_TRANSMITSSION_MULTI_FRAME;
          }
          /* Update the Sdu data buffer */
          sduDataPtr = &sduDataPtr[(*(ptrCopyTxData->RamArea))];
          /* Update the total Sdu length is copied after copied */
          (*(ptrCopyTxData->RamArea)) += sduLengthVar;
          /* Update remain available data in buffer after copied */
          /* polyspace +1 RTE:IDP [Not a defect:Unset] "availableDataPtr NULL check performed in PduR_DETCheckLoTpCopyTxData" */
          *availableDataPtr = reqLength - (*(ptrCopyTxData->RamArea));
          /* Set the pointer to PduInfoPtr */
          destSduDataPtr = pduInfoPtr->SduDataPtr;
          /* Copy the Received data for transmitting */
          while (sduLengthVar != (PduLengthType)PDUR_LENGTH_ZERO)
          {
            /* @Trace: PduR_SUD_API_267 */
            *(destSduDataPtr) = *(sduDataPtr); /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
            /* MISRA Rule   : 17.4.
             *   Message      : Increment or decrement operation
             *                  performed on pointer
             *   Reason       : Increment operator used
             *                  to achieve better throughput.
             *   Verification : However, part of the code
             *                  is verified manually and
             *                  it is not having any impact.
             */
            sduDataPtr++;
            /* MISRA Rule   : 17.4.
             *   Message      : Increment or decrement operation
             *                  performed on pointer
             *   Reason       : Increment operator used
             *                  to achieve better throughput.
             *   Verification : However, part of the code
             *                  is verified manually and
             *                  it is not having any impact.
             */
            destSduDataPtr++;
            sduLengthVar--;
          }
          SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
        }
        else
        {
          /* @Trace: PduR_SUD_API_264 */
          bufReqReturn = (BufReq_ReturnType)BUFREQ_E_BUSY;
        }
      }
      else
      {
        if (((ptrRetry->TxTpDataCnt) < (*(ptrCopyTxData->RamArea))) &&
          (PDUR_TRANSMITSSION_SINGLE_FRAME ==
                                 (*(ptrCopyTxData->RamAreaFrame))))
        {
          /* Update the total Sdu length is copied after copied */
          (*(ptrCopyTxData->RamArea)) -= ptrRetry->TxTpDataCnt;
          /* check available data is enough for copying */
          if ((PduLengthType)(*(ptrCopyTxData->RamArea) +
                                            sduLengthVar) <= copiedLength)  /* polyspace RTE:NIVL [Justified:Low] "copiedLength always is initialize when abortCopyTxData is PDUR_FALSE" */
          {
            /* Set back the position in buffer */
            sduDataPtr = &sduDataPtr[(*(ptrCopyTxData->RamArea))];
            /* Set the pointer to PduInfoPtr*/
            destSduDataPtr = pduInfoPtr->SduDataPtr;
            /* Update the Sdu length is copied after copied*/
            (*(ptrCopyTxData->RamArea)) += sduLengthVar;
            /* Update remain available data in buffer after set back */
            /* polyspace +2 RTE:IDP [Not a defect:Unset] "availableDataPtr NULL check performed in PduR_DETCheckLoTpCopyTxData" */
            /* polyspace +1 RTE:NIVL [Justified:Low] "reqLength always is initialize when abortCopyTxData is PDUR_FALSE" */
            *availableDataPtr = reqLength - (*(ptrCopyTxData->RamArea));
            #ifdef AUTRON_LOCAL_BUG_FIX
            /* @Trace: SRS_BSW_00312 */
            SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
            #endif
            while (sduLengthVar != (PduLengthType)PDUR_LENGTH_ZERO)
            {
              /* @Trace: PduR_SUD_API_270 */
              *(destSduDataPtr) = *(sduDataPtr); /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
              /* MISRA Rule   : 17.4.
               *   Message      : Increment or decrement operation
               *                  performed on pointer
               *   Reason       : Increment operator used
               *                  to achieve better throughput.
               *   Verification : However, part of the code
               *                  is verified manually and
               *                  it is not having any impact.
               */
              sduDataPtr++;
              /* MISRA Rule   : 17.4.
               *   Message      : Increment or decrement operation
               *                  performed on pointer
               *   Reason       : Increment operator used
               *                  to achieve better throughput.
               *   Verification : However, part of the code
               *                  is verified manually and
               *                  it is not having any impact.
               */
              destSduDataPtr++;
              sduLengthVar--;
            }
            #ifdef AUTRON_LOCAL_BUG_FIX
            SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
            #endif
            /* Set the return value to BUFREQ_OK */
            bufReqReturn = (BufReq_ReturnType)BUFREQ_OK;
          }
          else
          {
            /* @Trace: PduR_SUD_API_269 */
            bufReqReturn = (BufReq_ReturnType)BUFREQ_E_BUSY;
          }
        }
        else
        {
          /* @Trace: PduR_SUD_API_268 */
          /* Set return value as BUFREQ_E_NOT_OK */
          bufReqReturn = BUFREQ_E_NOT_OK;
        }
      }
    } /* @End if ((PduLengthType)PDUR_ZERO == sduLengthVar) */
  }
  else
  {
    /* @Trace: PduR_SUD_API_430 */
    /* Set the return value to BUFREQ_E_NOT_OK */
    bufReqReturn = (BufReq_ReturnType)BUFREQ_E_NOT_OK;
  }
  return (bufReqReturn);
} /* End of PduR_LoTpGWCopyTxData
   *(P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) ptrCopyTxData,
   *P2VAR(PduInfoType, AUT
   MATIC, PDUR_VAR) pduInfoPtr,
   *P2VAR(RetryInfoType, AUTOMATIC, PDUR_VAR) ptrRetry,
  *P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) availableDataPtr)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
#endif /* #if (PDUR_TP_TXCONFIRMATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_LoTpTxConfirmation                             **
**                                                                            **
** Service ID           : 0x48                                                **
**                                                                            **
** Description          : This function is called by a transport protocol     **
**                        module after the I-PDU has been transmitted on its  **
**                        network, the result will reveal if the transmission **
**                        was successful or not.                              **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType txPduId,                                  **
**                        PduIdType moduleType, Std_ReturnType result         **
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
**                        PduR_LowTpCopyTxDataBuf, PduR_PoolPtr               **
**                        PduR_TpTxBuffer, PduR_LowTpConfirmation             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckLoTpTxConfirmation() ,                 **
**                        PduR_GWLoTpTxConfirmation()                         **
**                        SchM_Enter_PduR_TP_TX_PROTECTION_AREA() ,           **
**                        SchM_Exit_PduR_TP_TX_PROTECTION_AREA() 			        **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_PduR_06020 */
/* @Trace: SRS_PduR_06117 */
/* @Trace: SRS_BSW_00167 */
/* @Trace: SRS_BSW_00171 */
/* @Trace: SRS_PduR_06121 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
/* @Traceability BEGIN -- SRS: SWS_PduR_00825 SWS_PduR_00785 SWS_PduR_00833
                               SWS_PduR_00835 SWS_PduR_00637 SWS_PduR_00806
                               SWS_PduR_00812 SWS_PduR_00765 SWS_PduR_00328
                               SWS_PduR_00301 SWS_PduR_00287 SWS_PduR_00330
                               SWS_PduR_00667 SWS_PduR_00161 SWS_PduR_00803
                               SWS_PduR_00100 SWS_PduR_00119 SWS_PduR_00221
                               SWS_PduR_00381 SWS_PduR_00824 SWS_PduR_00008
                               SWS_PduR_00024 SWS_PduR_00764 */
FUNC(void, PDUR_CODE) PduR_LoTpTxConfirmation(PduIdType txPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType moduleType, Std_ReturnType result)
#else
FUNC(void, PDUR_CODE) PduR_LoTpTxConfirmation(PduIdType txPduId,
  Std_ReturnType result)
#endif
{
  /*  Compiler Warning   :  Argument  'result' is not used in function
   *  Reason             :  For pre-compile implementation the parameter
   *                        "result" will not be used.
   *  Verification       :  However, part of the code is verified manually
   *                        and it is not having any impact.
   */
  P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) ptrCopyTxDataBuf;
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoTxDestination, AUTOMATIC, PDUR_CONST) ptrLoTxDestination;
  #endif
  #if ((PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON) &&\
      (PDUR_TP_TRANSMIT == STD_ON))
  P2VAR(PduR_MulticastTpInfo, AUTOMATIC, PDUR_VAR) ptrMulticastTpInfo;
  #endif
  #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;
  #endif
  #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
  uint8 localIndex;
  #endif
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean detErrorFlag;
  detErrorFlag = PduR_DETCheckLoTpTxConfirmation(txPduId,
    moduleType);
  /* polyspace<MISRA-C:14.2 : Low : Justify with annotations> Not a defect */
  PDUR_UNUSED(result);

  /* Check whether any development errors are detected */
  if ((boolean)PDUR_FALSE == detErrorFlag)
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_353 */
    /* Get pointer to LoTxDestination from PduR_ConfigSet */
    ptrLoTxDestination = &PduR_LoTxConfig[txPduId];
    /* Get pointer to ptrCopyTxDataBuf from ptrLoTxDestination */
    ptrCopyTxDataBuf = (P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST))
                                  (ptrLoTxDestination->LoIfTpDestiantion);
    #else
    /* @Trace: PduR_SUD_API_129 */
    /* Get pointer to ptrCopyTxDataBuf from PduR_LowTpCopyTxDataBuf */
    ptrCopyTxDataBuf = &PduR_LowTpCopyTxDataBuf[txPduId];
    #endif
    #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
    /* Check whether it's configured for Gateway */
    if ((uint8)PDUR_ZERO !=
                        (ptrCopyTxDataBuf->TargetIndex & PDUR_GATEWAY_MASK))
    {
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
      ptrTxBuffer = &PduR_TpBufferConfig[ptrCopyTxDataBuf->TxBufferIndex];
      #else
      ptrTxBuffer = &PduR_TpTxBuffer[ptrCopyTxDataBuf->TxBufferIndex];
      #endif
      (*(ptrCopyTxDataBuf->RamArea)) = (uint16)PDUR_ZERO;
      #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
      if (NULL_PTR == ptrTxBuffer->SinBufPtr) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
      {
        /* @Trace: PduR_SUD_API_133 */
        PduR_GWLoTpTxConfirmation(ptrCopyTxDataBuf);
      }
      else
      #endif
      {
        /* Check transmit for ptrQueue is called*/
        if ((uint8)PDUR_ZERO < ptrTxBuffer->SinBufPtr->TxConfirm) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
        {
          /* @Trace: PduR_SUD_API_134 */
          ptrTxBuffer->SinBufPtr->TxConfirm--;
        }
        else
        {
          /* No Action */
        }
        if ((uint8)PDUR_ZERO == ptrTxBuffer->SinBufPtr->TxConfirm) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
        {
          /* @Trace: PduR_SUD_API_135 */
          ptrTxBuffer->SinBufPtr->RxState    = PDUR_RX_YETTOSTART;
          ptrTxBuffer->SinBufPtr->FreeBuffer  = (boolean)PDUR_FALSE; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
          #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
          localIndex = ptrTxBuffer->SinBufPtr->IndexPool; /* polyspace RTE:IDP [Not a defect:Unset] "cover by generation and unit test" */ /* polyspace RTE:NIV [Not a defect:Unset] "cover by generation and unit test" */

          if (((uint8)PDUR_TP_POOLS_INDEX_COUNT > localIndex) && \
            ((boolean)PDUR_TRUE == ptrTxBuffer->SinBufPtr->PoolStatus)) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
          {
            /* @Trace: PduR_SUD_API_136 */
            PduR_PoolPtr[localIndex].State = (boolean)PDUR_FALSE; /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "index poor support range from 0..255" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */ /* polyspace RTE:OBAI [Not a defect:Low] "Array index is valid" */
            ptrTxBuffer->SinBufPtr->PoolStatus = (boolean)PDUR_FALSE;
          }
          else
          {
            /* No Action */
          }
          #endif
        }
      }
    } /* End of if (PDUR_ZERO != (ptrCopyTxDataBuf->TargetIndex &
       *PDUR_GATEWAY_MASK)) */
    else
    #endif /* #if (PDUR_TP_GATEWAY_OPERATION == STD_ON) */
    {
      #if (PDUR_TP_TRANSMIT == STD_ON)
      /* Check whether PduConfig is PDUR_TP_GATEWAY */
      #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
      /* Check if confirmation status is non-zero */
      if (((uint8)PDUR_ZERO) != ((ptrCopyTxDataBuf->TargetIndex)
                                              & ((uint8)PDUR_MULTICAST_MASK)))
      {
        /* @Trace: PduR_SUD_API_131 */
        ptrMulticastTpInfo = (ptrCopyTxDataBuf->MulticastTpInfo);
        /* @Trace: SRS_BSW_00312 */
        /* Disable relevant interrupts */
        SchM_Enter_PduR_TP_TX_PROTECTION_AREA();
        /* Update the result value */
        ptrMulticastTpInfo->Result &= result; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
        /* Clear the confirmation status */
        ptrMulticastTpInfo->ConfStatus &=
                              (uint8)(~(ptrCopyTxDataBuf->TxCnfrmStsMask));
        /* Enable relevant interrupts */
        SchM_Exit_PduR_TP_TX_PROTECTION_AREA();
        if ((uint8)PDUR_ZERO == ptrMulticastTpInfo->ConfStatus)
        {
          /* Invoke Tp confirmation fucntion */
          if (PduR_LowTpConfirmation[ptrCopyTxDataBuf->TargetIndex & /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "Array index is valid due to data flow" */ /* polyspace RTE:OBAI [Not a defect:Low] "Array index is valid" */
              (uint8)PDUR_TPCONF_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
          {
            /* @Trace: PduR_SUD_API_137 */
            (void)PduR_LowTpConfirmation[ptrCopyTxDataBuf->TargetIndex&
              (uint8)PDUR_TPCONF_TARGET_INDEX_MASK].TargetLayer
              (ptrCopyTxDataBuf->UpTargetPduId,
              ptrMulticastTpInfo->Result);
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
      } /* End of if (PDUR_ZERO != ptrCopyTxDataBuf->TxCnfrmStsMask) */
      else
      #endif /*  #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)  */
      {
        /* Invoke Tp confirmation function */
        if(PduR_LowTpConfirmation[(ptrCopyTxDataBuf->TargetIndex) & /* polyspace RTE:OBAI [Not a defect:Low] "Array index is valid due to data flow" */
            (uint8)PDUR_TPCONF_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
        {
          /* @Trace: PduR_SUD_API_132 */
          (void)PduR_LowTpConfirmation[(ptrCopyTxDataBuf->TargetIndex) & /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "Array index is valid due to data flow" */
            (uint8)PDUR_TPCONF_TARGET_INDEX_MASK].TargetLayer
            (ptrCopyTxDataBuf->UpTargetPduId, result);
        }
        else
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* No Action */
        }
      }
      #endif /* End of if (PDUR_TP_TRANSMIT == STD_ON) */
    }
  }
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No Action */
  }
  #endif
} /* End of PduR_LoTpTxConfirmation(PduIdType txPduId, NotifResultType
   *result) */
/* @Traceability BEGIN -- SRS: SWS_PduR_00825 SWS_PduR_00785 SWS_PduR_00833
                               SWS_PduR_00835 SWS_PduR_00637 SWS_PduR_00806
                               SWS_PduR_00812 SWS_PduR_00765 SWS_PduR_00328
                               SWS_PduR_00301 SWS_PduR_00287 SWS_PduR_00330
                               SWS_PduR_00667 SWS_PduR_00161 SWS_PduR_00803
                               SWS_PduR_00100 SWS_PduR_00119 SWS_PduR_00221
                               SWS_PduR_00381 SWS_PduR_00824 SWS_PduR_00008
                               SWS_PduR_00024 SWS_PduR_00764 */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*  #if (PDUR_TP_TXCONFIRMATION == STD_ON)  */
#endif /*  #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_DETCheckLoTpTxConfirmation                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by a transport protocol     **
**                        module after the I-PDU has been transmitted on its  **
**                        network, the result will reveal if the transmission **
**                        was successful or not.                              **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType txPduId,                                  **
**                        PduIdType moduleType                                **
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
**                        PduR_InitStatus,PduR_LowTpCopyTxDataBuf             **
**                                                                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, PDUR_CODE) PduR_DETCheckLoTpTxConfirmation(
  PduIdType txPduId, PduIdType moduleType)
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoTxDestination, AUTOMATIC, PDUR_CONST) ptrLoTxDestination;
  #endif
  P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) ptrTpCopyTxData;
  boolean detErrorFlag;
  /* Set the error flag to PDUR_FALSE */
  detErrorFlag = (boolean)PDUR_FALSE;

  /* Check whether the module is initialised */
  if (PDUR_UNINIT == PduR_InitStatus)
  {
    /* @Trace: SRS_BSW_00406 */
    /* @Trace: PduR_SUD_API_150 */
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_TP_TX_CONFIRMATION_SID, PDUR_E_UNINIT);
    /* Set the error flag to TRUE */
    detErrorFlag = (boolean)PDUR_TRUE;
  } /* End of if (PDUR_UNINIT == PduR_InitStatus) */
  else
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_347 */
    if (txPduId >= PduR_IfTpConfirmationMaxPduId)
    #else
    /* @Trace: PduR_SUD_API_151 */
    if (txPduId >= PDUR_TP_TXCONFIRMATION_MAXPDUID)
    #endif
    {
      /* Report to DET */
      /* @Trace: SRS_PduR_06103 */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_TP_TX_CONFIRMATION_SID, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      detErrorFlag = (boolean)PDUR_TRUE;
    } /* End of if (txPduId >= PDUR_TP_TXCONFIRMATION_MAXPDUID) */
    else
    {
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_OFF)
      /* Get the pointer to ptrTpCopyTxData from PduR_LowTpCopyTxDataBuf*/
      ptrTpCopyTxData = &PduR_LowTpCopyTxDataBuf[txPduId];
      #else
      /* Get pointer to ptrLoTxDestination from PduR_LoTxConfig */
      ptrLoTxDestination = &PduR_LoTxConfig[txPduId];
      /* Get pointer to ptrTpCopyTxData from ptrLoTxDestination */
      ptrTpCopyTxData = (P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST))
                                  (ptrLoTxDestination->LoIfTpDestiantion);
      if ((boolean)PDUR_FALSE !=
                             (boolean)ptrLoTxDestination->IsInterfaceRouting)
      {
        /* Report to DET */
        /* @Trace: SRS_PduR_06103 */
        /* @Trace: PduR_SUD_API_346 */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          PDUR_TP_TX_CONFIRMATION_SID, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to TRUE */
        detErrorFlag = (boolean)PDUR_TRUE;
      }
      else
      #endif
      {
        if (ptrTpCopyTxData->ModuleType != moduleType)
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* Report to DET */
          /* @Trace: SRS_PduR_06103 */
          /* @Trace: PduR_SUD_API_152 */
          (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
            PDUR_TP_TX_CONFIRMATION_SID, PDUR_E_PDU_ID_INVALID);
          /* Set the error flag to TRUE */
          detErrorFlag = (boolean)PDUR_TRUE;
        } /* (ptrTpCopyTxData->ModuleType != moduleType) */
        else
        {
          /* No Action */
        }
      }
    }
  }
  return (detErrorFlag);
} /* End of PduR_DETCheckLoTpTxConfirmation
  *(PduIdType txPduId, PduIdType moduleType)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*  #if (PDUR_DEV_ERROR_DETECT == STD_ON)  */
#endif /*  #if (PDUR_TP_TXCONFIRMATION == STD_ON)  */
#endif /*  #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_GWLoTpTxConfirmation                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoTpTxConfirmation function in case of gateway.**
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduR_TpCopyTxDataBuf *ptrTpCopyTxDataBuf            **
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
**                        PduR_TpTransmitService, PduR_TpTxBuffer             **
**                        PduR_PoolPtr                                        **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA(),       **
**                        Det_ReportRuntimeError()                            **
**                        PduR_SortPriorityQueue(),                           **
**                        PduR_FifoMulticastTransmit()                        **

*******************************************************************************/
#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && \
  (PDUR_TP_TXCONFIRMATION == STD_ON))
#if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_GWLoTpTxConfirmation( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_TpCopyTxDataBuf, AUTOMATIC, PDUR_CONST) ptrTpCopyTxDataBuf)
{
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  Std_ReturnType returnVal;
  boolean rxState;
  #if (PDUR_MULTICAST_GATEWAY_TP_FIFO_SUPPORT == STD_ON)
  uint8 rxPduIndex;
  #endif
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* Get the pointer from TxBuffer address */
  /* @Trace: PduR_SUD_API_383 */
  ptrTxBuffer = &PduR_TpBufferConfig[ptrTpCopyTxDataBuf->TxBufferIndex];
  #else
  /* @Trace: PduR_SUD_API_382 */
  ptrTxBuffer = &PduR_TpTxBuffer[ptrTpCopyTxDataBuf->TxBufferIndex];
  #endif
  /* Enter critical area */
  #if(PDUR_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  /* @Trace: SRS_BSW_00312 */
  SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA();
  #endif
  /* Check if depth count is not zero */
  if ((uint8)PDUR_ZERO != ptrTxBuffer->CurrentDepth) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
  {
    /* @Trace: PduR_SUD_API_153 */
    /* Get first queue of tx buffer */
    ptrQueue = ptrTxBuffer->FirstQueuePtr;
    /* Decrement TxConfirm */
    ptrQueue->TxConfirm--; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
    /* Check TxConfirm is zero */
    if ((uint8)PDUR_ZERO == ptrQueue->TxConfirm)
    {
      do
      {
        /* @Trace: PduR_SUD_API_155 */
        /* Decrement CurrentDepth */
        ptrTxBuffer->CurrentDepth--;
        /* Buffer is released */
        ptrQueue->RxState    = PDUR_RX_YETTOSTART; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
        ptrQueue->FreeBuffer = (boolean)PDUR_FALSE;
        ptrQueue->IndexList  = (uint8)PDUR_INVALID;
        #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
        if ((boolean)PDUR_TRUE == ptrQueue->PoolStatus) /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
        {
          /* @Trace: PduR_SUD_API_158 */
          /* Pool buffer is released */
          PduR_PoolPtr[ptrQueue->IndexPool].State = (boolean)PDUR_FALSE; /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "index poor support range from 0..255" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */ /* polyspace RTE:OBAI [Not a defect:Low] "Array index is valid" */
          ptrQueue->PoolStatus = (boolean)PDUR_FALSE;
        }
        else
        #endif
        {
          /* Update HeadLength or TailLength of ptrTxBuffer */
          do
          {
            if (ptrQueue->PduInfoPtr.SduDataPtr < ptrTxBuffer->IndexSduPtr) /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
            {
              /* To check data of queue is next address of first queue */
              if ((NULL_PTR == ptrQueue->Next) || /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
                (ptrQueue->PduInfoPtr.SduDataPtr <
                                  ptrQueue->Next->PduInfoPtr.SduDataPtr)) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
              {
                /* @Trace: PduR_SUD_API_164 */
                /* Increment TailLength */
                ptrTxBuffer->TailLength += ptrQueue->ReqLength; /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
                /* Check Tail is greater TotalLength */
                /* polyspace-begin MISRA-C:2012 1.1 [Not a defect:Low] "Due to behavior of function" */
                if (ptrTxBuffer->TailLength >= ptrTxBuffer->TotalLength)
                {
                  /* @Trace: PduR_SUD_API_165 */
                  /* Set TailLength to zero */
                  ptrTxBuffer->TailLength = (PduLengthType)PDUR_ZERO;
                }
                else
                {
                  /* No Action */
                }
                /* polyspace-end MISRA-C:2012 1.1 [Not a defect:Low] "Due to behavior of function" */
              }
              else
              {
                /* No Action */
              }
            }
            else
            {
              /* @Trace: PduR_SUD_API_163 */
              /* Increment HeadLength */
              ptrTxBuffer->HeadLength += ptrQueue->ReqLength; /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
            }
            ptrQueue = ptrQueue->Next; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
          } while ((NULL_PTR != ptrQueue) &&
            ((boolean)PDUR_FALSE == ptrQueue->FreeBuffer)); /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
        }
        if ((uint8)PDUR_ZERO != ptrTxBuffer->CurrentDepth)
        {
          /* Sort queue that completed Rx in PduR buffer */
          rxState = PduR_SortPriorityQueue(ptrTxBuffer, ptrQueue);
          /* Check exits queue that completed Rx process */
          if ((boolean)PDUR_TRUE == rxState)
          {
            /* @Trace: SRS_PduR_06127 */
            ptrQueue = ptrTxBuffer->FirstQueuePtr;
            #if (PDUR_MULTICAST_GATEWAY_TP_FIFO_SUPPORT == STD_ON)
            /* Get Index for struct LoRxIndication */
            rxPduIndex = ptrTpCopyTxDataBuf->RxPduIndex;
            if (PDUR_INVALID != rxPduIndex)
            {
              /* @Trace: PduR_SUD_API_159 */
              returnVal = PduR_FifoMulticastTransmit(rxPduIndex, ptrQueue);
            }
            else
            #endif
            {
              returnVal = PduR_TpTransmitService[(
                      ptrTpCopyTxDataBuf->TargetIndex) &
                      PDUR_TARGET_INDEX_MASK].TargetLayer(
                      ptrTpCopyTxDataBuf->UpTargetPduId,
                      &ptrQueue->PduInfoPtr);
              if ((Std_ReturnType)E_NOT_OK == returnVal)
              {
                /* @Trace: PduR_SUD_API_160 */
                /* Report to DET */
                (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                  PDUR_TP_TX_CONFIRMATION_SID, PDUR_E_TP_TX_REQ_REJECTED);
              }
              else
              {
                /* @Trace: PduR_SUD_API_161 */
                /* Increment TxConfirm */
                ptrQueue->TxConfirm++; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
              }
            }
          }
          else
          {
            /* @Trace: PduR_SUD_API_157 */
            returnVal = (Std_ReturnType)E_OK;
          }
        }
        else
        {
          /* @Trace: PduR_SUD_API_156 */
          ptrTxBuffer->FirstQueuePtr = NULL_PTR;
          /* Set HeadLength to TotalLength */
          ptrTxBuffer->HeadLength = ptrTxBuffer->TotalLength;
          returnVal = (Std_ReturnType)E_OK;
        }
      } while ((Std_ReturnType)E_NOT_OK == returnVal);
    }
    else
    {
      /* No Action */
    }
  } /* End of if ((uint8)PDUR_ZERO != ptrTxBuffer->CurrentDepth) */
  else
  {
    /* No Action */
  }
  /* Exit critical area */
  #if(PDUR_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA();
  #endif
} /* End of PduR_GWLoTxConfirmation(
     P2CONST(PduR_LoTxConf, AUTOMATIC, PDUR_CONST) LpLoTxConfirmation)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON) */
#endif /* #if ((PDUR_ZERO_COST_OPERATION == STD_OFF) &&
       (PDUR_LO_TXCONFIRMATION == STD_ON)) */
/*******************************************************************************
** Function Name        : PduR_FifoMulticastTransmit                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by a                        **
**                        PduR_GWLoTpTxConfirmation to multicast transmit to  **
**                        lower module                                        **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : uint8 rxPduIndex, PduR_TpQueueType *ptrQueue        **
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
**                        PduR_LowTpRxIndication, PduR_TpTransmitService      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportRuntimeError()                            **
**                                                                            **
*******************************************************************************/
#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && \
    (PDUR_TP_TXCONFIRMATION == STD_ON))
#if (PDUR_MULTICAST_GATEWAY_TP_FIFO_SUPPORT == STD_ON) &&\
   (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_FifoMulticastTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  uint8 rxPduIndex,
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrQueue)
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST) ptrTpRxIndication;
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu;
  uint8 noOfRoutePdu;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif
  Std_ReturnType returnVal;
  Std_ReturnType returnAllTxVal;
  returnAllTxVal = (Std_ReturnType)E_NOT_OK;
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* Get the pointer to ptrLoRxSource structure */
  ptrLoRxSource = &PduR_LoRxConfig[rxPduIndex];
  /* Get the pointer to ptrTpRxIndication structure */
  ptrTpRxIndication = (P2CONST(PduR_TpRxIndication, AUTOMATIC, PDUR_CONST))
                        (ptrLoRxSource->LoIfTpSource);
  #else
  /* Assign Local Pointer to Interface Rx Indication Structure */
  ptrTpRxIndication = &PduR_LowTpRxIndication[rxPduIndex];
  #endif
  /* Assign Local Pointer to LoGWRxIndication Structure */
  ptrGWTpPdu = ptrTpRxIndication->GWRxTpPdu;
  /* Get the Number of Route for Source PDU */
  noOfRoutePdu = (ptrTpRxIndication->TargetIndexOrNoOfRoute &
                                               (uint8)PDUR_NOOFROUTE_MASK);
  /* @Trace: SRS_PduR_06029 */
  while ((uint8)PDUR_ZERO != noOfRoutePdu)
  {
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    groupIdValue = ptrGWTpPdu->GroupMaskValue;
    indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
    idConvert = groupIdValue % PDUR_BITMASK_UINT8;
    /* @Trace: SRS_PduR_06120 */
    /* Check if routing path is enabled */
    if ((PDUR_UNDEFINED == groupIdValue) ||
        ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] & /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
                                          (((uint32)PDUR_ONE) << idConvert))))
    #endif
    {
      /* Check routing isn't reception to upper */
      if ((uint8)PDUR_ZERO == ((ptrGWTpPdu->TargetIndexBufType) &
                                                        PDUR_UPPERLAYER_MASK))
      {
        /* Invoke transmit function */
        if (PduR_TpTransmitService [
            (uint8)(ptrGWTpPdu->TargetIndexBufType) &
            (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
        {
          returnVal =
            PduR_TpTransmitService [(uint8)(
            ptrGWTpPdu->TargetIndexBufType) &
            (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer(
            ptrGWTpPdu->TargetPduId, &ptrQueue->PduInfoPtr);
          if ((Std_ReturnType)E_OK == returnVal)
          {
            /* @Trace: PduR_SUD_API_168 */
            ptrQueue->TxConfirm++; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
          }
          else
          {
            /* @Trace: PduR_SUD_API_169 */
            /* Report to DET */
            (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
              PDUR_TP_TX_CONFIRMATION_SID, PDUR_E_TP_TX_REQ_REJECTED);
          }
          returnAllTxVal = returnAllTxVal & returnVal;
        }
        else
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* No Action */
        }
      } /* if (PDUR_UPPER_LAYER != ptrGWTpPdu->TxBufferIndex) */
      else
      { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
        /* @Trace: PduR_SUD_API_167 */
        /* No Action */
      }
    }
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    else
    { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
      /* @Trace: PduR_SUD_API_166 */
      /* No action */
    }
    #endif
    /* Increment the MulticastGWIfPdu Pointer */
    ptrGWTpPdu++;
    /* Decrement the Number of Route PDU */
    noOfRoutePdu--;
  }
  return returnAllTxVal;
} /* End of PduR_FifoMulticastTransmit(rxPduIndex, ptrQueue) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*  #if (PDUR_MULTICAST_GATEWAY_TP_FIFO_SUPPORT == STD_ON) */
#endif /*  #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
/*******************************************************************************
** Function Name        : PduR_SortPriorityQueue                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by PduR_GWLoTpTxConfirmation**
**                        to sort priority queue that completed reception     **
**                        process to first queue                              **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduR_TpBuffer *ptrTxBuffer,                         **
**                        PduR_TpQueueType *ptrQueue                          **
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
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, PDUR_CODE) PduR_SortPriorityQueue(
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_CONST) ptrQueue)
{
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrQueueVar;
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) afterQueuePtr;
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) beforeQueuePtr;
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) firstTempPtr;
  boolean returnVal;
  boolean isFirstQueueCompletedRx;
  isFirstQueueCompletedRx = (boolean)PDUR_TRUE;
  returnVal = (boolean)PDUR_TRUE;
  ptrQueueVar = ptrQueue;
  /* Set FirstQueuePtr to next queue */
  ptrTxBuffer->FirstQueuePtr = ptrQueueVar;
  firstTempPtr = ptrTxBuffer->FirstQueuePtr;
  /* Find PduId that completed receive data */
  while ((NULL_PTR != ptrQueueVar) &&
    (PDUR_RX_ACKNOWLEDGE != ptrQueueVar->RxState)) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
  {
    /* @Trace: PduR_SUD_API_170 */
    isFirstQueueCompletedRx = (boolean)PDUR_FALSE;
    beforeQueuePtr = ptrQueueVar;
    ptrQueueVar = ptrQueueVar->Next; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */

  }
  if ((NULL_PTR != ptrQueueVar) &&
    ((boolean)PDUR_TRUE != isFirstQueueCompletedRx)) /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
  {
    /* Store next of queue that moved to first */
    afterQueuePtr = ptrQueueVar->Next; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
    /* Set queue first queue */
    ptrTxBuffer->FirstQueuePtr = ptrQueueVar;
    /* Assign FirstQueuePtr to ptrQueueVar */
    ptrQueueVar = ptrTxBuffer->FirstQueuePtr;
    /* Set next of first queue */
    ptrQueueVar->Next = firstTempPtr;
    /* Find queue that same IndexList */
    while (beforeQueuePtr->IndexList != ptrQueueVar->IndexList) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace MISRA-C:2012 9.1 D4.1 [Not a defect:Low] "this local pointer local always be initialized due to data flow" */ /* polyspace DEFECT:NON_INIT_PTR [Not a defect:Low] "this local pointer local always be initialized due to data flow" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
    {
      /* @Trace: PduR_SUD_API_173 */
      ptrQueueVar = ptrQueueVar->Next; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
    }
    /* Set next of queue that same IndexList */
    ptrQueueVar->Next = afterQueuePtr;
  }
  else
  {
    if (NULL_PTR == ptrQueueVar)
    {
      /* @Trace: PduR_SUD_API_171 */
      returnVal = (boolean)PDUR_FALSE;
    }
    else
    {
      /* @Trace: PduR_SUD_API_172 */
      returnVal = (boolean)PDUR_TRUE;
    }
  }
  return returnVal;
} /* End of PduR_SortPriorityQueue(
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer,
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrQueue) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON) */
#endif /*  #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
