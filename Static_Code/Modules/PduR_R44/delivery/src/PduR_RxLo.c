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
**  SRC-MODULE: PduR_RxLo.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of the Common functionality of                      **
**              PduR_DETCheckLoRxIndication(), PduR_GWLoRxIndication(),       **
**              PduR_LoRxIndication and PduR_GWBufferUpdate(),                **
**              PduR_LowIfTransmit(), PduR_FreeIfBuffer                       **
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
** 1.0.5       11-Nov-2022   HaoTA4      CP44-383                             **
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
#include "PduR_RxLo.h"          /* PduR RxLo header */
#include "SchM_PduR.h"          /* Schedular Manager header */
#include "PduR_Incl.h"          /* Dependent module Header files*/
#include "string.h"             /* memcpy() */
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
#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_LO_RXINDICATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, PDUR_VAR) PduR_DETCheckLoRxIndication( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType rxPduId, uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_VAR) ptrPduInfoPtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if ((PDUR_ZERO_COST_OPERATION == STD_OFF) &&
                                           (PDUR_LO_RXINDICATION == STD_ON)) */
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON)*/

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||\
  (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
#if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_VAR) PduR_GWBufferUpdate /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
(P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr,
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) ptrGWIfPdu);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON)*/
#endif
#endif /* #if ((PDUR_ZERO_COST_OPERATION == STD_OFF) */

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_VAR) PduR_GWLoRxIndication(PduIdType rxPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON)*/
#endif /* #if ((PDUR_ZERO_COST_OPERATION == STD_OFF) */

#if ((PDUR_IF_GATEWAY_OPERATION == STD_ON) &&\
  (PDUR_ZERO_COST_OPERATION == STD_OFF))
#if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||\
  (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_LowIfTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) ptrGWIfPdu);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if ((PDUR_IF_GATEWAY_OPERATION == STD_ON) &&\
  (PDUR_ZERO_COST_OPERATION == STD_OFF))
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_FreeIfBuffer(
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) ptrGWIfPdu);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : PduR_LoRxIndication                                 **
**                                                                            **
** Service ID           : 0x42                                                **
**                                                                            **
** Description          : This function is called by the Interface layer after**
**                        a L-PDU has been received. The PDU Router shall     **
**                        translate the RxPduId into the configured target    **
**                        PDU ID and route this indication to the configured  **
**                        target function.                                    **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds                      **
**                        Non-Reentrant for the same PduId                    **
**                                                                            **
** Input Parameters     : PduIdType rxPduId,                                  **
**                        uint8 moduleType, PduInfoType *ptrPduInfoPtr        **
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
**                        PduR_LowRxIndication, PduR_LowIfReceive             **
**                        PduR_LoRxConfig                                     **
**                                                                            **
** Function(s) invoked  : PduR_DETCheckLoRxIndication(),                      **
**                        PduR_GWLoRxIndication()                             **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_PduR_06020 */
/* @Trace: SRS_PduR_06116 */
/* @Trace: SRS_PduR_06117 */
/* @Trace: SRS_PduR_06123 */
/* @Trace: SRS_BSW_00167 */
/* @Trace: SRS_BSW_00171 */
/* @Trace: SRS_BSW_00310 */
/* @Trace: SRS_PduR_06003 */
/* @Trace: SRS_PduR_06004 */
/* @Trace: SRS_PduR_06049 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_LO_RXINDICATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
/* @Traceability BEGIN -- SRS: SWS_PduR_00119 SWS_PduR_00100 SWS_PduR_00330
                               SWS_PduR_00160 SWS_PduR_00161 SWS_PduR_00164
                               SWS_PduR_00744 SWS_PduR_00328 SWS_PduR_00221
                               SWS_PduR_00638 SWS_PduR_00436 SWS_PduR_00437
                               SWS_PduR_00783 SWS_PduR_00303 SWS_PduR_00784
                               SWS_PduR_00306 SWS_PduR_00746 SWS_PduR_00621
                               SWS_PduR_00809 SWS_PduR_00665 SWS_PduR_00806
                               SWS_PduR_00785 SWS_PduR_00307 SWS_PduR_00786
                               SWS_PduR_00787 SWS_PduR_00793 SWS_PduR_00807
                               SWS_PduR_00816 SWS_PduR_00256 SWS_PduR_00255
                               SWS_PduR_00670 SWS_PduR_00669 SWS_PduR_00663
                               SWS_PduR_00829 SWS_PduR_00805 SWS_PduR_00715
                               SWS_PduR_00287 SWS_PduR_00827 SWS_PduR_00362
                               SWS_PduR_00824 SWS_PduR_00002 SWS_PduR_00764 */
FUNC(void, PDUR_VAR) PduR_LoRxIndication(PduIdType rxPduId,
  uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr)
#else
FUNC(void, PDUR_VAR) PduR_LoRxIndication(PduIdType rxPduId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr)
#endif /*#if (PDUR_DEV_ERROR_DETECT == STD_OFF)*/
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_LoRxInd, AUTOMATIC, PDUR_CONST) ptrLoRxIndication;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif
  #if (PDUR_TOTAL_COUNT_RX_LO_CALLOUT > 0)
  boolean LblLoRxIndFlag = PDUR_TRUE;
  #endif
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean detErrorFlag;
  detErrorFlag = PduR_DETCheckLoRxIndication(rxPduId,
    moduleType, ptrPduInfoPtr);
  /* Check whether any development errors are detected */
  if ((boolean)PDUR_FALSE == detErrorFlag)
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_354 */
    /* Get the pointer to ptrLoRxSource structure */
    ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
    /* Get the pointer to ptrIfTriggerTransmit structure */
    ptrLoRxIndication = (P2CONST(PduR_LoRxInd, AUTOMATIC, PDUR_CONST))
                               (ptrLoRxSource->LoIfTpSource);
    #else
    /* @Trace: PduR_SUD_API_047 */
    /* Pointer to Interface Rx Indication Structure for the source PduId */
    ptrLoRxIndication = &PduR_LowRxIndication[rxPduId];
    #endif
    /* @Trace: SRS_PduR_CUS_00003 */
    #if (PDUR_TOTAL_COUNT_RX_LO_CALLOUT > 0)
      if (NULL_PTR != ptrLoRxIndication->pFuncPduRCallOut)
      {
        /* @Trace: PduR_SUD_API_485 */
        LblLoRxIndFlag = ptrLoRxIndication->pFuncPduRCallOut(rxPduId, ptrPduInfoPtr);
      }
    if (PDUR_TRUE == LblLoRxIndFlag)
    #endif
    {
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      /* Get the group mask value */
      groupIdValue = ptrLoRxIndication->GroupMaskValue;
      indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
      idConvert = groupIdValue % PDUR_BITMASK_UINT8;
      /* Check if routing path is enabled */
      if ((PDUR_UNDEFINED == groupIdValue) ||
            ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] &
                                            (((uint32)PDUR_ONE) << idConvert))))
      #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
      {
        #if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
        /* check whether it's gateway  */
        if ((uint8)PDUR_ZERO == (ptrLoRxIndication->TargetIndexOrRoutePDU &
                                          (uint8)PDUR_UPPERLAYER_MASK))
        #endif
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          #if (PDUR_IF_RECEIVE_SUPPORT == STD_ON)
          /* Invoke <Up>_RxIndication */
          if(PduR_LowIfReceive[ptrLoRxIndication->TargetIndexOrRoutePDU]
            .TargetLayer != NULL_PTR)
          {
           /* @Trace: PduR_SUD_API_049 */
           (void)PduR_LowIfReceive[ptrLoRxIndication->TargetIndexOrRoutePDU]
             .TargetLayer((ptrLoRxIndication->UpTargetPduId), ptrPduInfoPtr);
          }
          else
          {
            /* No Action */
          }
          #endif
        } /* @End of if (PDUR_ZERO ==
          (ptrLoRxIndication->TargetIndexOrRoutePDU & PDUR_NONGATEWAY_MASK))*/
        #if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
        else /* If Gateway */
        {
          /* @Trace: PduR_SUD_API_048 */
         PduR_GWLoRxIndication(rxPduId, ptrPduInfoPtr);

        } /* End of else */
        #endif /* #if (PDUR_IF_GATEWAY_OPERATION == STD_ON) */
      }
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      else
      {
        /* No Action */
      }
      #endif
    }
    #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  }
  else
  {
     /* No Action */
  }
    #endif
  }
 /* End of PduR_LoRxIndication(PduIdType rxPduId, P2VAR(PduInfoType,
     *AUTOMATIC, PDUR_VAR) ptrPduInfoPtr) */
  #define PDUR_STOP_SEC_CODE
  #include "MemMap.h"
  #endif /* #if (PDUR_LO_RXINDICATION == STD_ON) */
  #endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
  /* @Traceability END -- SRS: SWS_PduR_00119 SWS_PduR_00100 SWS_PduR_00330
                               SWS_PduR_00160 SWS_PduR_00161 SWS_PduR_00164
                               SWS_PduR_00744 SWS_PduR_00328 SWS_PduR_00221
                               SWS_PduR_00638 SWS_PduR_00436 SWS_PduR_00437
                               SWS_PduR_00783 SWS_PduR_00303 SWS_PduR_00784
                               SWS_PduR_00306 SWS_PduR_00746 SWS_PduR_00621
                               SWS_PduR_00809 SWS_PduR_00665 SWS_PduR_00806
                               SWS_PduR_00785 SWS_PduR_00307 SWS_PduR_00786
                               SWS_PduR_00787 SWS_PduR_00793 SWS_PduR_00807
                               SWS_PduR_00816 SWS_PduR_00256 SWS_PduR_00255
                               SWS_PduR_00670 SWS_PduR_00669 SWS_PduR_00663
                               SWS_PduR_00829 SWS_PduR_00805 SWS_PduR_00715
                               SWS_PduR_00287 SWS_PduR_00827 SWS_PduR_00362
                               SWS_PduR_00824 SWS_PduR_00002 SWS_PduR_00764 */

/*******************************************************************************
** Function Name        : PduR_DETCheckLoRxIndication                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoRxIndication function                        **
**                        to check the parameters passed are valid and        **
**                        buffer does not need to be the length of the        **
**                        report to DET in case of invalid values.            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType rxPduId, uint8 moduleType,                **
**                        PduInfoType *ptrPduInfoPtr, boolean ifRouting       **
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
**                        PduR_InitStatus, PduR_LowRxIndication               **
**                        PduR_IfTpRxIndicationMaxPduId, PduR_LoRxConfig      **
**						                                                                **
**                                                                            **
** Function(s) invoked  : Det_ReportError()                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00337 */
/* @Trace: SRS_BSW_00350 */
/* @Trace: SRS_BSW_00323 */
#if ((PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_LO_RXINDICATION == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
  static FUNC(boolean, PDUR_VAR) PduR_DETCheckLoRxIndication( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType rxPduId, uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_VAR) ptrPduInfoPtr)
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_LoRxInd, AUTOMATIC, PDUR_CONST) ptrLoRxIndication;
  boolean detErrorFlag;
  /* Set the DetErrorFlag to the PDUR_FALSE */
  detErrorFlag = (boolean)PDUR_FALSE;
  /* Check whether the module is initialised */
  if (PDUR_UNINIT == PduR_InitStatus)
  {
    /* @Trace: SRS_BSW_00406 */
    /* @Trace: PduR_SUD_API_061 */
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                                     PDUR_RX_INDICATION_SID,
                                     PDUR_E_UNINIT);
    /* Set the error flag to TRUE */
    detErrorFlag = (boolean)PDUR_TRUE;
  } /* End of if (PDUR_UNINIT == PduR_InitStatus) */
  else
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_356 */
    if (rxPduId >= PduR_IfTpRxIndicationMaxPduId)
    #else
    /* @Trace: PduR_SUD_API_355 */
    if (rxPduId >= PDUR_LO_RXINDICATION_MAXPDUID)
    #endif
    {
      /* Report to DET */
      /* @Trace: SRS_PduR_06103 */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_RX_INDICATION_SID, PDUR_E_PDU_ID_INVALID);
      /* Set the error flag to TRUE */
      detErrorFlag = (boolean)PDUR_TRUE;
    } /* End of if (rxPduId >= PDUR_LO_RXINDICATION_MAXPDUID) */
    else
    {
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_OFF)
      /* Assign Local Pointer to Interface Rx Indication Structure */
      ptrLoRxIndication = &PduR_LowRxIndication[rxPduId];
      #else
      /* Get the pointer to ptrLoRxSource structure */
      ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
      /* Get the pointer to ptrIfTriggerTransmit structure */
      ptrLoRxIndication = (P2CONST(PduR_LoRxInd, AUTOMATIC, PDUR_CONST))
                               (ptrLoRxSource->LoIfTpSource);
      if ((boolean)PDUR_TRUE != (boolean)ptrLoRxSource->IsInterfaceRouting)
      {
        /* Report to DET */
        /* @Trace: PduR_SUD_API_357 */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          PDUR_RX_INDICATION_SID, PDUR_E_PDU_ID_INVALID);
        /* Set the error flag to TRUE */
        detErrorFlag = (boolean)PDUR_TRUE;
      }
      else
      #endif
      {
        if (ptrLoRxIndication->ModuleType != moduleType)
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* Report to DET */
          /* @Trace: SRS_PduR_06103 */
          /* @Trace: PduR_SUD_API_062 */
          (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          PDUR_RX_INDICATION_SID, PDUR_E_PDU_ID_INVALID);
          /* Set the error flag to TRUE */
          detErrorFlag = (boolean)PDUR_TRUE;
        } /* End of if (ptrLoRxIndication->ModuleType != moduleType) */
        else
        {
          /* No Action */
        }
      }
    }
    /* Check If ptrPduInfoPtr is NULL_PTR */
    if (NULL_PTR == ptrPduInfoPtr)
    {
      /* @Trace: PduR_SUD_API_063 */
      /* Report to DET */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                                            PDUR_RX_INDICATION_SID,
                                            PDUR_E_PARAM_POINTER);
      /* Set the error flag to TRUE */
      detErrorFlag = (boolean)PDUR_TRUE;
    } /* End of if (NULL_PTR == ptrPduInfoPtr) */
    else
    {
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "ptrPduInfoPtr is checked null by if (NULL_PTR == ptrPduInfoPtr)" */
      if((NULL_PTR == ptrPduInfoPtr->SduDataPtr))
      {
        /* Report to DET */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                                              PDUR_RX_INDICATION_SID,
                                              PDUR_E_PARAM_POINTER);
        /* Set the error flag to TRUE */
        detErrorFlag = (boolean)PDUR_TRUE;
      } /* End of if ((NULL_PTR == ptrPduInfoPtr->SduDataPtr)) */
      else
      {
        /* No Action */
      }
    }
  }
  return (detErrorFlag);
} /* End of PduR_DETCheckLoRxIndication(
   * PduIdType rxPduId, uint8 moduleType,
   * P2CONST(PduInfoType, AUTOMATIC, PDUR_VAR) ptrPduInfoPtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
#endif /* #if (PDUR_LO_RXINDICATION == STD_ON) */

/*******************************************************************************
** Function Name        : PduR_GWLoRxIndication                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_LoRxIndication function in case of gateway.    **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType rxPduId,                                  **
**                        PduInfoType *ptrPduInfoPtr                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean LblRetVal                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_LowRxIndication,                               **
**                        PduR_IfTransmitService, PduR_LowIfReceive,          **
**                        PduR_LoRxConfig                                     **
**                                                                            **
** Function(s) invoked  : PduR_GWBufferUpdate(), PduR_LowIfTransmit()         **
**                        PduR_FreeIfBuffer                                   **
**                                                                            **
*******************************************************************************/
#if ((PDUR_IF_GATEWAY_OPERATION == STD_ON) &&\
  (PDUR_ZERO_COST_OPERATION == STD_OFF))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
 static FUNC(void, PDUR_VAR) PduR_GWLoRxIndication(PduIdType rxPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
   P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr)
{
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif
  P2CONST(PduR_LoRxInd, AUTOMATIC, PDUR_CONST) ptrLoRxIndication;
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) ptrGWIfPdu;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif
  uint8 noOfRoutePdu;
  uint8 targetIndexBufType;
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* @Trace: PduR_SUD_API_372 */
  /* Get the pointer to ptrLoRxSource structure */
  ptrLoRxSource = &PduR_LoRxConfig[rxPduId];
  /* Get the pointer to ptrIfTriggerTransmit structure */
  ptrLoRxIndication = (P2CONST(PduR_LoRxInd, AUTOMATIC, PDUR_CONST))
                               (ptrLoRxSource->LoIfTpSource);
  #else
  /* @Trace: PduR_SUD_API_371 */
  /* Assign Local Pointer to Interface Rx Indication Structure */
  ptrLoRxIndication = &PduR_LowRxIndication[rxPduId];
  #endif
  /* Assign Local Pointer to GWRxIndication Structure */
  ptrGWIfPdu = ptrLoRxIndication->GWIfPdu;
  /* Get the Number of Route for Source PDU */
  noOfRoutePdu = (ptrLoRxIndication->TargetIndexOrRoutePDU &
                      (uint8)PDUR_NOOFROUTE_MASK);
  /* Loop for the Number of Route of the Source PDU */
  /* @Trace: SRS_PduR_06030 */
  do
  {
    /* Get the target layer configuration */
    targetIndexBufType = (uint8)(ptrGWIfPdu->TargetIndexBufType); /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */

    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    groupIdValue = ptrGWIfPdu->GroupMaskValue;
    indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
    idConvert = groupIdValue % PDUR_BITMASK_UINT8;
    /* @Trace: SRS_PduR_06120 */
    /* Check if routing path is enabled */
    if ((PDUR_UNDEFINED == groupIdValue) ||
        ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] &
                                          (((uint32)PDUR_ONE) << idConvert))))
    #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
    {
      if (PDUR_UPPER_LAYER == (ptrGWIfPdu->TxBufferIndex))
      {
        #if (PDUR_IF_RECEIVE_SUPPORT == STD_ON)
        /* Invoke <Up>_RxIndication */
        if (PduR_LowIfReceive[targetIndexBufType & PDUR_TARGET_INDEX_MASK]
          .TargetLayer != NULL_PTR)
        {
          /* @Trace: PduR_SUD_API_066 */
          (void)PduR_LowIfReceive[targetIndexBufType & PDUR_TARGET_INDEX_MASK]
            .TargetLayer(ptrGWIfPdu->TargetPduId, ptrPduInfoPtr);
        }
        else
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* No Action */
        }
        #endif
      }
      else
      {
        #if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||\
          (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
        /* Check whether buffer is allocated */
        if ((uint16)PDUR_GATEWAY_NOBUFFER != (ptrGWIfPdu->TxBufferIndex))
        {
          /* DI-EI should be added because of Nesting Interrupt or Polling Rx Case */
          SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
          /* Copy data to PduR buffer */
          PduR_GWBufferUpdate(ptrPduInfoPtr, ptrGWIfPdu);
          /* @Trace: PduR_SUD_API_067 */
          PduR_LowIfTransmit(ptrGWIfPdu);
          
          SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
        } /* End of if (PDUR_GATEWAY_NOBUFFER != LusTxBufferIndex) */
        else /* gateway without buffer */
        #endif /* #if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) || \
                              (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON)) */
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          #if (PDUR_LO_TXCONFIRMATION == STD_ON)
          /* Invoke transmit function */
          if(PduR_IfTransmitService[targetIndexBufType
                  & PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
          {
            /* @Trace: PduR_SUD_API_068 */
            (void)PduR_IfTransmitService[targetIndexBufType
                  & PDUR_TARGET_INDEX_MASK].TargetLayer(
                  ptrGWIfPdu->TargetPduId,
                  ptrPduInfoPtr);
          }
          else
          {
            /* No Action */
          }
          #endif
        }
      }
    }
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    else
    {
      /* @Trace: PduR_SUD_API_069 */
      /* No action */
    }
    #endif
    /* Increment the MulticastGWIfPdu Pointer */
    ptrGWIfPdu++;
    /* Decrement the Number of Route PDU */
    noOfRoutePdu--;
  } while ((uint8)PDUR_ZERO != noOfRoutePdu);
} /* End of PduR_GWLoRxIndication(PduIdType rxPduId, P2VAR(PduInfoType,
   *AUTOMATIC, PDUR_VAR) ptrPduInfoPtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_IF_GATEWAY_OPERATION == STD_ON) &&
        *   (PDUR_ZERO_COST_OPERATION == STD_OFF)) */

/*******************************************************************************
** Function Name        : PduR_GWBufferUpdate                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_GWLoRxIndication function in case of           **
**                        gateway.                                            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduInfoType *ptrPduInfoPtr, ptrGWIfPdu              **
**                        uint8 noOfRoutePdu, uint8 totalRoute                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean returnVal                                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_IfTxBuffer, PduR_IfTransmitService,            **
**                        PduR_IfTxQueue, PduR_TxBufferConfig                 **
**                                                                            **
** Function(s) invoked  : Det_ReportError(),                                  **
**                        Det_ReportRuntimeError(),                           **
**                        CANIF_TXPDU_GW_STATUS(),                            **
**                        SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA(),       **
**                        SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA(),       **
*******************************************************************************/
#if ((PDUR_IF_GATEWAY_OPERATION == STD_ON) &&\
  (PDUR_ZERO_COST_OPERATION == STD_OFF))
#if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||\
  (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_VAR) PduR_GWBufferUpdate( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr,
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) ptrGWIfPdu)
{
  #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  P2VAR(PduR_TxQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  P2VAR(PduR_TxQueueType, AUTOMATIC, PDUR_VAR) nextQueue;
  uint8 mask;
  boolean flushFifo;
  uint8 indexDepth = (uint8)PDUR_ZERO;
  PduLengthType lengthOfDest;
  #if (PDUR_CANIF_SUPPORT == STD_ON)
  uint8 canIfPduStatus;
  #endif
  #endif
  P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) ptrDataBuffer;

  #if(PDUR_META_DATA_SUPPORT == STD_ON)
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) ptrMetaDataBuffer;
  uint16 lengthMetaDataVar;
  #endif
  PduLengthType lengthVar;
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* @Trace: PduR_SUD_API_373 */
  /* Get the respective buffer into local pointer */
  ptrTxBuffer = &PduR_TxBufferConfig[ptrGWIfPdu->TxBufferIndex];
  #else
  /* @Trace: PduR_SUD_API_072 */
  /* Get the respective buffer into local pointer */
  ptrTxBuffer = &PduR_IfTxBuffer[ptrGWIfPdu->TxBufferIndex];
  #endif
  /* Get SduLength of PduInforPtr */
  lengthVar = ptrPduInfoPtr->SduLength; /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "ptrPduInfoPtr is checked null by PduR_DETCheckLoRxIndication function" */
  /* Get the Meta data pointer from Tx Buffer */
  #if(PDUR_META_DATA_SUPPORT == STD_ON)
  lengthMetaDataVar = ptrGWIfPdu->MetaDataLength;
  #endif
  /* @Trace: SRS_PduR_06012 */
  /* @Trace: SRS_PduR_06032 */
  if (ptrGWIfPdu->PduLength < lengthVar)
  {
    /* @Trace: PduR_SUD_API_071 */
    lengthVar = ptrGWIfPdu->PduLength;
  }
  else
  {
    /* No Action */
  }
  #if(PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  #if (PDUR_CANIF_SUPPORT == STD_ON)
  canIfPduStatus = PDUR_INVALID;
  if (PDUR_CANIF == ((ptrGWIfPdu->TargetIndexBufType) &
                                            PDUR_TARGET_INDEX_MASK))
  {
    /* @Trace: PduR_SUD_API_398 */
    canIfPduStatus = CANIF_TXPDU_GW_STATUS(ptrGWIfPdu->TargetPduId); /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "Range is provided by CanIf module" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
  }
  else
  { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
    /* No Action */
  }
  #endif
  mask = ((ptrGWIfPdu->TargetIndexBufType) & (uint8)(PDUR_BUFFER_MASK));
  /* If the buffer type is FIFO */
  if (((uint8)PDUR_D_FIFO == mask)||((uint8)PDUR_TT_FIFO == mask))
  {
    lengthOfDest = lengthVar;
    /* Enter critical area */
    #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
    /* @Trace: SRS_BSW_00312 */
    SchM_Enter_PduR_FIFO_STATUS_PROTECTION_AREA();
    #endif
    /* Check whether Depth is greater than configured value */
    /* @Trace: SRS_PduR_06012 */
    /* @Trace: SRS_PduR_06032 */
    if (((ptrTxBuffer->CurrentDepth) >= (ptrTxBuffer->FIFODepth)) || /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
      ((ptrTxBuffer->HeadLength < lengthOfDest) &&
      (ptrTxBuffer->TailLength < lengthOfDest)))
    {
      /* @Trace: PduR_SUD_API_400 */
      flushFifo = (boolean)PDUR_TRUE;
    }
    else
    {
      /* @Trace: PduR_SUD_API_399 */
      flushFifo = (boolean)PDUR_FALSE;
    }
    #if (PDUR_CANIF_SUPPORT == STD_ON)
    if ((CANIF_GW_NOCOMM == canIfPduStatus) ||
                             (CANIF_GW_ERRVOL == canIfPduStatus))
    {
      /* @Trace: PduR_SUD_API_401 */
      flushFifo = (boolean)PDUR_TRUE;
    }
    else
    {
      /* No Action */
    }
    #endif
    if ((boolean)PDUR_TRUE == flushFifo)
    {
      while (NULL_PTR != ptrTxBuffer->FirstQueuePtr)
      {
        /* @Trace: PduR_SUD_API_073 */
        ptrQueue = ptrTxBuffer->FirstQueuePtr;
        ptrQueue->PduInfoPtr.SduDataPtr = NULL_PTR;
        ptrQueue->PduInfoPtr.MetaDataPtr = NULL_PTR;
        ptrQueue->PduInfoPtr.SduLength = 0xFFFF;
        ptrQueue->FreeBuffer = (boolean)PDUR_EMPTY; /* polyspace RTE:IDP [Not a defect:Low] "this pointer in range of bound due to data flow" */
        ptrTxBuffer->FirstQueuePtr = ptrQueue->Next; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
        ptrQueue->Next = NULL_PTR;
      }
      memset(ptrTxBuffer->SduPtr, PDUR_ZERO, ptrTxBuffer->TotalLength); /* polyspace RTE:STD_LIB [Justified:Low] "ptrTxBuffer->SduPtr can't NULL by it's controled by generator " */
      ptrTxBuffer->CurrentDepth = (uint8)PDUR_ZERO;
      ptrTxBuffer->HeadLength = ptrTxBuffer->TotalLength;
      /* Report to DET */
      /* @Trace: SRS_PduR_06106 */
      (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                                                PDUR_RX_INDICATION_SID,
                                                PDUR_E_PDU_INSTANCES_LOST);
    }
    else
    {
      /* No Action */
    }
    #if (PDUR_CANIF_SUPPORT == STD_ON)
    if (CANIF_GW_ERRVOL != canIfPduStatus)
    #endif
    {
      /* @Trace: SRS_PduR_06126 */
      if (NULL_PTR == ptrTxBuffer->FirstQueuePtr)
      {
        /* @Trace: PduR_SUD_API_075 */
        ptrQueue = &PduR_IfTxQueue[ptrGWIfPdu->TxQueueIndex];
        /* Update pointer SduDataPtr of PduInfoPtr */
        ptrQueue->PduInfoPtr.SduDataPtr = ptrTxBuffer->SduPtr;
        /* Check Meta Data is support */
        #if (PDUR_META_DATA_SUPPORT == STD_ON)
        if (NULL_PTR != ptrTxBuffer->MetaPtr)
        {
          /* @Trace: PduR_SUD_API_077 */
          /* Update pointer MetaDataPtr of PduInfoPtr */
          ptrQueue->PduInfoPtr.MetaDataPtr = ptrTxBuffer->MetaPtr;
          /* Increment IndexMetaPtr */
          ptrTxBuffer->IndexMetaPtr = &ptrTxBuffer->MetaPtr[lengthMetaDataVar];
        }
        else
        {
          /* @Trace: PduR_SUD_API_076 */
          ptrMetaDataBuffer = NULL_PTR;
        }
        #else
        /* Update pointer MetaDataPtr of PduInfoPtr */
        ptrQueue->PduInfoPtr.MetaDataPtr = NULL_PTR;
        #endif
        /* Update SduLength of PduInfoPtr */
        ptrQueue->PduInfoPtr.SduLength = lengthOfDest;
        #if (PDUR_SHARED_GW_IF_BUFFER == STD_ON)
        /* Update TargetPduId for later use (in TxConfirmation context) */
        ptrQueue->TargetPduId = ptrGWIfPdu->TargetPduId;
        #endif
        /* Add PduInforPtr to first queue */
        ptrTxBuffer->FirstQueuePtr = ptrQueue;
        /* Increment IndexSduPtr */
        ptrTxBuffer->IndexSduPtr = &ptrTxBuffer->SduPtr[lengthOfDest];
        /* Update TailLength */
        ptrTxBuffer->TailLength  = (PduLengthType)PDUR_ZERO;
        /* Update HeadLength */
        ptrTxBuffer->HeadLength = ptrTxBuffer->TotalLength - lengthOfDest;
      }
      else
      {
        /* Allocation for next queue */
        /* @Trace: SRS_PduR_06126 */
        do
        {
          /* @Trace: PduR_SUD_API_074 */
          ptrQueue = &PduR_IfTxQueue[ptrGWIfPdu->TxQueueIndex + (indexDepth++)];
        }
        while ((indexDepth < ptrTxBuffer->FIFODepth) &&
               (PDUR_OCCUPIED == ptrQueue->FreeBuffer)); /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
        /* check remain buffer is greater length of PduInforPtr */
        if (ptrTxBuffer->HeadLength >= lengthOfDest)
        {
          /* @Trace: PduR_SUD_API_079 */
          /* Update pointer SduDataPtr of PduInfoPtr */
          ptrQueue->PduInfoPtr.SduDataPtr = ptrTxBuffer->IndexSduPtr; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
          /* Update SduLength of PduInfoPtr */
          ptrQueue->PduInfoPtr.SduLength = lengthOfDest;
          /* Update HeadLength in tx queue buffer */
          ptrTxBuffer->HeadLength = ptrTxBuffer->HeadLength - lengthOfDest;
        }
        else
        {
          /* @Trace: PduR_SUD_API_082 */
          /* Set IndexSduPtr to SduPtr of tx queue buffer */
          ptrTxBuffer->IndexSduPtr = ptrTxBuffer->SduPtr;
          /* Set HeadLength to TailLength */
          ptrTxBuffer->HeadLength  = ptrTxBuffer->TailLength - lengthOfDest;
          /* Set TailLength to zero */
          ptrTxBuffer->TailLength = (PduLengthType)PDUR_ZERO;
          /* Update pointer SduDataPtr of PduInfoPtr */
          ptrQueue->PduInfoPtr.SduDataPtr = ptrTxBuffer->SduPtr; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
          /* Check Meta Data is support */
          #if(PDUR_META_DATA_SUPPORT == STD_ON)
          /* Update pointer MetaDataPtr of PduInfoPtr */
          ptrTxBuffer->IndexMetaPtr = ptrTxBuffer->MetaPtr;
          #endif
          /* Update SduLength of PduInfoPtr */
          ptrQueue->PduInfoPtr.SduLength = lengthOfDest;
        }
        #if (PDUR_META_DATA_SUPPORT == STD_ON)
        if (NULL_PTR != ptrTxBuffer->MetaPtr)
        {
          /* @Trace: PduR_SUD_API_083 */
          /* Update pointer MetaDataPtr of PduInfoPtr */
          ptrQueue->PduInfoPtr.MetaDataPtr = ptrTxBuffer->IndexMetaPtr;
          /* Increment IndexMetaPtr */
          ptrTxBuffer->IndexMetaPtr = &ptrTxBuffer->IndexMetaPtr[lengthMetaDataVar];
        }
        else
        {
          /* @Trace: PduR_SUD_API_084 */
          ptrMetaDataBuffer = NULL_PTR;
        }
        #else
        /* Update pointer MetaDataPtr of PduInfoPtr */
        ptrQueue->PduInfoPtr.MetaDataPtr = NULL_PTR;
        #endif
        #if (PDUR_SHARED_GW_IF_BUFFER == STD_ON)
        /* Update TargetPduId for later use (in TxConfirmation context) */
        ptrQueue->TargetPduId = ptrGWIfPdu->TargetPduId;
        #endif
        /* Increment IndexSduPtr */
        ptrTxBuffer->IndexSduPtr = &ptrTxBuffer->IndexSduPtr[lengthOfDest];
        /* Get first queue pointer */
        nextQueue = ptrTxBuffer->FirstQueuePtr;
        /* Add last queue */
        /* polyspace +2 RTE:IDP [Justified:Low] "nextQueue pointer is in of range with max of range is ptrTxBuffer->FIFODepth" */
        /* polyspace +1 RTE:NIP [Justified:Low] "this pointer is initialized by ptrQueue->Next = NULL_PTR in PduR_GWBufferUpdate func" */
        while(nextQueue->Next != NULL_PTR)
        {
          /* @Trace: PduR_SUD_API_085 */
          nextQueue = nextQueue->Next;
        }
        nextQueue->Next = ptrQueue;
      }
      /* set flag FreeBuffer */
      ptrQueue->FreeBuffer = PDUR_OCCUPIED;
      ptrQueue->Next = NULL_PTR;
      /* Increment CurrentDepth */
      ptrTxBuffer->CurrentDepth++;
      /* Get the Sdu data pointer from Tx queue */
      ptrDataBuffer = ptrQueue->PduInfoPtr.SduDataPtr;
      /* Get the Meta data pointer from Tx queue */
      #if(PDUR_META_DATA_SUPPORT == STD_ON)
      ptrMetaDataBuffer = ptrQueue->PduInfoPtr.MetaDataPtr;
      #endif
    }
    #if (PDUR_CANIF_SUPPORT == STD_ON)
    else
    {
      /* No Action */
    }
    #endif
    /* Exit critical area */
    #if(PDUR_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_PduR_FIFO_STATUS_PROTECTION_AREA();
    #endif
  }/* @End of if ((mask == (uint8)PDUR_D_FIFO)||
                                     (mask == (uint8)PDUR_TT_FIFO)) */
  else
  #endif /* End of if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
  {
    /* @Trace: PduR_SUD_API_070 */
    /* Get the Sdu data pointer from Tx Buffer */
    ptrDataBuffer = ptrTxBuffer->SduPtr;
    /* Get the Meta data pointer from Tx Buffer */
    #if(PDUR_META_DATA_SUPPORT == STD_ON)
    ptrMetaDataBuffer = ptrTxBuffer->MetaPtr;
    #endif
  }
  #if ((PDUR_CANIF_SUPPORT == STD_ON) &&\
                      (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON))
  if (CANIF_GW_ERRVOL != canIfPduStatus)
  #endif
  {
    #if (PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
    /* @Trace: SRS_BSW_00312 */
    SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
    #endif
    /* Copy Sdu data from I-PDU to buffer */
    memcpy((P2VAR(void, AUTOMATIC, PDUR_VAR))(ptrDataBuffer), /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */ /* polyspace RTE:STD_LIB [Not a defect:Low] "all input function are valid due to data flow" */
      (P2CONST(void, AUTOMATIC, PDUR_CONST))(ptrPduInfoPtr->SduDataPtr), /* polyspace MISRA-C:2012 D4.11 [Not a defect:Low] "all input function are valid due to data flow" */
      lengthVar);

    #if (PDUR_META_DATA_SUPPORT == STD_ON)
    if ((NULL_PTR != ptrMetaDataBuffer) && /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
      (NULL_PTR != ptrPduInfoPtr->MetaDataPtr)) /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
    {
      /* @Trace: PduR_SUD_API_086 */
      /* Copy Meta data from I-PDU to buffer */
      memcpy((P2VAR(void, AUTOMATIC, PDUR_VAR))(ptrMetaDataBuffer), /* polyspace MISRA-C:2012 D4.11 [Not a defect:Low] "all input function are valid due to data flow" */ /* polyspace RTE:STD_LIB [Not a defect:Low] "all input function are valid due to data flow" */
        (P2CONST(void, AUTOMATIC, PDUR_CONST))(ptrPduInfoPtr->MetaDataPtr),
        lengthMetaDataVar);
    }
    else
    {
      /* @Trace: PduR_SUD_API_087 */
      ptrMetaDataBuffer = NULL_PTR;
    }
    #endif
    #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
    #endif
  }
  #if ((PDUR_CANIF_SUPPORT == STD_ON) &&\
                      (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON))
  else
  {
    /* No Action */
  }
  #endif
} /* End of PduR_GWBufferUpdate(
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr,
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) ptrGWIfPdu) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||\
        * (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON)) */
#endif /* #if (PDUR_IF_GATEWAY_OPERATION == STD_ON) &&
        *  (PDUR_ZERO_COST_OPERATION == STD_OFF)) */
/*******************************************************************************
** Function Name        : PduR_LowIfTransmit                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_GWLoRxIndication to transmission I-PDU         **
**                        in case of gateway operation                        **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduR_LoGWRxIndication ptrGWIfPdu,                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType returnTransmit                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):PduR_IfTransmitService,          **
**                        PduR_IfTxBuffer, PduR_TxBufferConfig                **
**                                                                            **
** Function(s) invoked  : Det_ReportRuntimeError()                            **
**                        CANIF_TXPDU_GW_STATUS()                             **
**                                                                            **
*******************************************************************************/
#if ((PDUR_IF_GATEWAY_OPERATION == STD_ON) &&\
  (PDUR_ZERO_COST_OPERATION == STD_OFF))
#if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) ||\
  (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_LowIfTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) ptrGWIfPdu)
{
  P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;
  PduInfoType pduInfoUpdatePtr;
  #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  P2VAR(PduR_TxQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  Std_ReturnType returnTransmit;
  uint8 mask;
  #if (PDUR_CANIF_SUPPORT == STD_ON)
  uint8 canIfPduStatus;
  #endif
  #endif
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* Get the respective buffer into local pointer */
  ptrTxBuffer = &PduR_TxBufferConfig[ptrGWIfPdu->TxBufferIndex];
  #else
  /* Get the respective buffer into local pointer */
  ptrTxBuffer = &PduR_IfTxBuffer[ptrGWIfPdu->TxBufferIndex];
  #endif
  #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  #if (PDUR_CANIF_SUPPORT == STD_ON)
  canIfPduStatus = PDUR_INVALID;
  if (PDUR_CANIF == ((ptrGWIfPdu->TargetIndexBufType) &
                                             PDUR_TARGET_INDEX_MASK))
  {
    /* @Trace: PduR_SUD_API_417 */
    canIfPduStatus = CANIF_TXPDU_GW_STATUS(ptrGWIfPdu->TargetPduId); /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "Range is provided by CanIf module" */ /* polyspace RTE:OBAI [Not a defect:Low] "Range is provided by CanIf module" */
  }
  else
  { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
    /* No Action */
  }
  #endif
  /* Get mask to check buffer type */
  mask = ((ptrGWIfPdu->TargetIndexBufType) & (uint8)(PDUR_BUFFER_MASK));
  /* If the buffer type is FIFO */
  if (((uint8)PDUR_D_FIFO == mask) || ((uint8)PDUR_TT_FIFO == mask))
  {
    if (ptrTxBuffer->CurrentDepth == (uint8)PDUR_ONE)
    {
      #if (PDUR_CANIF_SUPPORT == STD_ON)
      if (CANIF_GW_STOPPED != canIfPduStatus)
      #endif
      {
        /* @Trace: SRS_PduR_06126 */
        ptrQueue = ptrTxBuffer->FirstQueuePtr;
        /* Invoke transmit function */
        if (PduR_IfTransmitService[(ptrGWIfPdu->TargetIndexBufType) &
          PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
        {
          /* @Trace: PduR_SUD_API_091 */
          returnTransmit =
            PduR_IfTransmitService[(ptrGWIfPdu->TargetIndexBufType) &
            PDUR_TARGET_INDEX_MASK].TargetLayer(
            ptrGWIfPdu->TargetPduId, &ptrQueue->PduInfoPtr);
          /* Report Det when <Lo>_Transmit() is failed */
          if ((Std_ReturnType)E_NOT_OK == returnTransmit)
          {
            /* Report to DET */
            /* @Trace: SRS_BSW_00452 */
            /* @Trace: SRS_PduR_06105 */
            /* @Trace: PduR_SUD_API_092 */
            (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                                     PDUR_RX_INDICATION_SID,
                                     PDUR_E_PDU_INSTANCES_LOST);
          }
          else
          {
            /* No Action */
          }
        }
        else
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* @Trace: PduR_SUD_API_090 */
          returnTransmit = (Std_ReturnType)E_NOT_OK;
        }
        /* If the buffer type is PDUR_TT_FIFO */
        if (((uint8)PDUR_TT_FIFO == mask) &&
          ((Std_ReturnType)E_NOT_OK == returnTransmit))
        {
          /* @Trace: PduR_SUD_API_418 */
          PduR_FreeIfBuffer(ptrGWIfPdu);
        }
        else
        {
          /* No Action */
        }
      }
      #if (PDUR_CANIF_SUPPORT == STD_ON)
      else
      {
        /* No Action */
      }
      #endif
    }
    else
    {
      #if (PDUR_CANIF_SUPPORT == STD_ON)
      if (((uint8)PDUR_D_FIFO == mask) &&
                               (CANIF_GW_NOREQUEST == canIfPduStatus)) /* polyspace RTE:UNR [Not a defect:Low] "Not a redundant condition in other configuration" */
      { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
        ptrQueue = ptrTxBuffer->FirstQueuePtr;
        /* Invoke transmit function */
        if (PduR_IfTransmitService[(ptrGWIfPdu->TargetIndexBufType) &
          PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
        {
          /* @Trace: PduR_SUD_API_177 */
          (void)PduR_IfTransmitService[(ptrGWIfPdu->TargetIndexBufType) &
            PDUR_TARGET_INDEX_MASK].TargetLayer(
            ptrGWIfPdu->TargetPduId, &ptrQueue->PduInfoPtr);
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
      #endif
    }
  } /* @if (((uint8)PDUR_D_FIFO == mask) || ((uint8)PDUR_TT_FIFO == mask)) */
  else
  #endif /* #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
  {
    /* @Trace: PduR_SUD_API_088 */
    /* Update pointer SduDataPtr of pduInfoUpdatePtr */
    pduInfoUpdatePtr.SduDataPtr  = ptrTxBuffer->SduPtr;
    /* Update pointer SduLength of pduInfoUpdatePtr */
    pduInfoUpdatePtr.SduLength   = ptrTxBuffer->SduLengthUpdate;
    /* Update pointer MetaDataPtr of PduInfoPtr */
    pduInfoUpdatePtr.MetaDataPtr = ptrTxBuffer->MetaPtr;
    #if (PDUR_LO_TXCONFIRMATION == STD_ON)
    /* Invoke transmit function */
    if(PduR_IfTransmitService[(ptrGWIfPdu->TargetIndexBufType) &
              PDUR_TARGET_INDEX_MASK].TargetLayer != NULL_PTR)
    {
      /* @Trace: PduR_SUD_API_089 */
      (void)PduR_IfTransmitService[(ptrGWIfPdu->TargetIndexBufType) &
              PDUR_TARGET_INDEX_MASK].TargetLayer
                            (ptrGWIfPdu->TargetPduId, &pduInfoUpdatePtr);
    }
    else
    { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
      /* No Action */
    }
    #endif
  }
} /* End of PduR_LowTpTransmit(
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) ptrGWTpPdu) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
/*******************************************************************************
** Function Name        : PduR_FreeIfBuffer                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        PduR_GWLoRxIndication function to free buffer if    **
**                        all destination failed                              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduR_LoGWRxIndication *ptrGWIfPdu,                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): PduR_IfTxBuffer                 **
**                        PduR_TxBufferConfig                                 **
**                                                                            **
** Function(s) invoked  : None                                                **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, PDUR_CODE) PduR_FreeIfBuffer(
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) ptrGWIfPdu)
{
  P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  /* Get the respective buffer into local pointer */
  ptrTxBuffer = &PduR_TxBufferConfig[ptrGWIfPdu->TxBufferIndex];
  #else
  /* Get the respective buffer into local pointer */
  ptrTxBuffer = &PduR_IfTxBuffer[ptrGWIfPdu->TxBufferIndex];
  #endif
  /* Decrement CurrentDepth */
  ptrTxBuffer->CurrentDepth--; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */
  /* Set FirstQueuePtr to NULL_PTR */
  /* @Trace: SRS_PduR_06105 */
  ptrTxBuffer->FirstQueuePtr = NULL_PTR; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized pointer due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
  /* @Trace: PduR_SUD_API_178 */
  /* Update HeadLength of tx queue buffer */
  ptrTxBuffer->HeadLength = ptrTxBuffer->TotalLength;
} /* End of PduR_FreeIfBuffer(
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) ptrGWIfPdu) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
#endif /* #if (PDUR_IF_GATEWAY_OPERATION == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_GetGwBufferStatus                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the                      **
**                        User in case of gateway to check buffer is available**
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType LddPduRSrcPduId                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PduR_GwBufferStatus                                 **
**                                                                            **
** Return parameter     : PduR_GwBufferStatus ret                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        PduR_GaaLoRxIndication                              **
**                                                                            **
** Function(s) invoked  :                                                     **
*******************************************************************************/
#if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* Rx Buffer is always smaller than when this API called. */
FUNC(void, PDUR_CODE) PduR_GetGwBufferStatus(PduIdType LddPduRSrcPduId, 
  P2VAR(PduR_GwBufferStatus, AUTOMATIC, PDUR_VAR) LpGwStatus)
{
  /* @Trace: PduR_SUD_API_433 */
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) ptrLoRxSource;
  #endif

  P2CONST(PduR_LoRxInd, AUTOMATIC, PDUR_CONST) LpLoRxIndication;
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) LpGWIfPdu;
  P2CONST(PduR_TxBuffer, AUTOMATIC, PDUR_CONST) LpTxBuffer;
  uint8 LucNoOfRoutePdu = 0;
  uint8 LucMask = 0;
  uint8 LucConfiguredFifoDepth = 0;
  uint8 LucCurrentFifoDepth = 0;

  if (LpGwStatus != NULL_PTR)
  {
    LpGwStatus->ucNoOfRoutePdu = 0; /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "LpGwStatus is checked null by if (LpGwStatus != NULL_PTR)" */
    memset(LpGwStatus->aaPathStatus, 0x00, PDUR_MAX_MULTICAST_COUNT);
    memset(LpGwStatus->aaBufStatus, 0x00, PDUR_MAX_MULTICAST_COUNT);

    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    if (LddPduRSrcPduId < PduR_IfTpRxIndicationMaxPduId)
    #else
    if (LddPduRSrcPduId < PDUR_LO_RXINDICATION_MAXPDUID)
    #endif
    {
      /* @Trace: PduR_SUD_API_434 */
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
      /* Get the pointer to ptrLoRxSource structure */
      ptrLoRxSource = &PduR_LoRxConfig[LddPduRSrcPduId];
      /* Get the pointer to ptrIfTriggerTransmit structure */
      LpLoRxIndication = (P2CONST(PduR_LoRxInd, AUTOMATIC, PDUR_CONST))
                                  (ptrLoRxSource->LoIfTpSource);
      #else
      /* Assign Local Pointer to Interface Rx Indication Structure for the source PduId */
      LpLoRxIndication = &PduR_LowRxIndication[LddPduRSrcPduId];
      #endif

      /* Assign Local Pointer to LoGWRxIndication Structure */
      LpGWIfPdu = LpLoRxIndication->GWIfPdu;
    
      if (LpGWIfPdu != NULL_PTR)
      {
        /* Get the Number of Route for Source PDU */
        LucNoOfRoutePdu = (LpLoRxIndication->TargetIndexOrRoutePDU &
                          (uint8)PDUR_NOOFROUTE_MASK);
      
        LpGwStatus->ucNoOfRoutePdu = LucNoOfRoutePdu;
        
        /* Loop for the Number of Route of the Source PDU */
        while ((uint8)PDUR_ZERO != LucNoOfRoutePdu)
        {
          /* @Trace: PduR_SUD_API_435 */
          uint8 LucNum = LucNoOfRoutePdu - (uint8)PDUR_ONE;
          LucMask = ((LpGWIfPdu->TargetIndexBufType) & (uint8)(PDUR_BUFFER_MASK)); /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */

          /* If the buffer type is FIFO */
          if ((uint8)PDUR_D_FIFO == LucMask)
          { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
            /* @Trace: PduR_SUD_API_436 */
            LpGwStatus->aaPathStatus[LucNum / (uint8)8] |= (uint8)PDUR_ONE << (LucNum % (uint8)8);
            
            #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
            LpTxBuffer = &PduR_TxBufferConfig[LpGWIfPdu->TxBufferIndex];
            #else
            LpTxBuffer = &PduR_IfTxBuffer[LpGWIfPdu->TxBufferIndex];
            #endif
          
            /* Get configured TxBuffer */
            LucConfiguredFifoDepth = LpTxBuffer->FIFODepth;

            /* Get current TxBuffer */
            LucCurrentFifoDepth = LpTxBuffer->CurrentDepth;
            
            /* Check current Buffer status */
            if (LucConfiguredFifoDepth > LucCurrentFifoDepth)
            {
              /* @Trace: SRS_PduR_CUS_00001 */
              /* @Trace: PduR_SUD_API_437 */
              LpGwStatus->aaBufStatus[LucNum / (uint8)8] |= (uint8)PDUR_ONE << (LucNum % (uint8)8);
            }
          }
          /* @Trace: PduR_SUD_API_438 */
          /* Increment the MulticastGWIfPdu Pointer */
          LpGWIfPdu++;
          /* Decrement the Number of Route PDU */
          LucNoOfRoutePdu--;
        };
      } /* End of if (LpGWIfPdu != NULL_PTR) */
      else
      { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
        /* No action */
      }
    }
  } /* End of if (LpGwStatus != NULL_PTR) */
  else
  {
    /* No action */
  }
}

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif /* #if (PDUR_IF_GATEWAY_OPERATION == STD_ON) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
