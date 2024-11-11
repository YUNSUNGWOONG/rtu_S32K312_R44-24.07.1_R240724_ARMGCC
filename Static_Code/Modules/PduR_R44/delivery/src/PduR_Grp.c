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
**  SRC-MODULE: PduR_Grp.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of Enabling and Disabling Routing path groups       **
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
** 1.0.9.0_HF1 24-May-2024   Mj Kim      CP44-8274                            **
** 1.0.2       05-Oct-2021   PhucNHM     R44-Redmine #20586                   **
** 1.0.1       22-Jun-2021   PhucNHM     R44-Redmine #18951                   **
** 1.0.0       04-Dec-2020   AUTOEVER    Initial Version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: PduR_SUD_FILE_001 */
#include "PduR.h"
#include "SchM_PduR.h"            /* Schm header file */
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
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : PduR_EnableRouting                                  **
**                                                                            **
** Service ID           : 0xF3                                                **
**                                                                            **
** Description          : This Service initializes PDU Routing path groups    **
**                        If the configuration parameter                      **
**                        PDUR_ROUTINGPATH_GROUP_SUPPORT is enabled this      **
**                        service shall be realized as an empty function-like **
**                        macro                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduR_RoutingPathGroupIdType id                      **
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
**                        PduR_InitStatus, PduR_RoutingPathGroupMaxId         **
** Function(s) invoked  : Det_ReportError(),                                  **
**                        SchM_Enter_PduR_GROUP_STATUS_PROTECTION_AREA(),     **
**                        SchM_Exit_PduR_GROUP_STATUS_PROTECTION_AREA()		    **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* @Traceability BEGIN -- SRS: SWS_PduR_00119 SWS_PduR_00100 SWS_PduR_00715
                               SWS_PduR_00615 SWS_PduR_00648 SWS_PduR_00647
                               SWS_PduR_00028*/
FUNC(void, PDUR_VAR) PduR_EnableRouting(PduR_RoutingPathGroupIdType id)
{
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  uint16 indexBitmask;
  uint16 idConvert;
  boolean errorFlag;
  errorFlag = TRUE;
  if (PDUR_UNINIT == PduR_InitStatus)
  {
    /* @Trace: PduR_SUD_API_008 */
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_ENABLE_ROUTING_SID, PDUR_E_UNINIT);
    /* Set the return value to True */
    errorFlag = (boolean)FALSE;
  } /* End of if (PDUR_UNINIT == PduR_InitStatus) */
  else
  {
    /* Check whether the Group Id Is present */
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    if (id > PduR_RoutingPathGroupMaxId)
    /* @Trace: PduR_SUD_API_335 */
    #else
    if (id > PDUR_MAX_ROUTINGPATH_GROUP_ID)
    /* @Trace: PduR_SUD_API_080 */
    #endif
    {
      /* Report to DET */
      (void)Det_ReportError (PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_ENABLE_ROUTING_SID, PDUR_E_ROUTING_PATH_GROUP_ID_INVALID);
      errorFlag = (boolean)FALSE;
    }
    else
    {
      /* No Action */
    }
  }
  /* Check whether any development errors are detected */
  if ((boolean)TRUE == errorFlag)
  #endif /* #PDUR_DEV_ERROR_DETECT = STD_ON) */
  {
    /* @Trace: PduR_SUD_API_009 */
    /* @Trace: SRS_BSW_00312 */
    /* Disable relevant interrupts */
    SchM_Enter_PduR_GROUP_STATUS_PROTECTION_AREA();
    /* @Trace: SRS_PduR_06120 */
    /*Enable the routing path group*/
    indexBitmask = id / PDUR_BITMASK_UINT8;
    idConvert = id % PDUR_BITMASK_UINT8;
    PduR_GroupPathId[indexBitmask] = (uint8)(PduR_GroupPathId[indexBitmask] |
                                            (((uint32)PDUR_ONE) << idConvert));
    /* Enable relevant interrupts */
    SchM_Exit_PduR_GROUP_STATUS_PROTECTION_AREA();
  }
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No Action */
  }
  #endif
} /* End of PduR_EnableRouting(PduR_RoutingPathGroupIdType id ) */
/* @Traceability END -- SRS: SWS_PduR_00119 SWS_PduR_00100 SWS_PduR_00715
                             SWS_PduR_00615 SWS_PduR_00648 SWS_PduR_00647
                             SWS_PduR_00028*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
** Function Name        : PduR_DisableRouting                                 **
**                                                                            **
** Service ID           : 0xF4                                                **
**                                                                            **
** Description          : This Service Disables PDU Routing path groups If the**
**                        configuration parameter                             **
**                        PDUR_ROUTINGPATH_GROUP_SUPPORT is enabled this      **
**                        service shall be realized as an empty function-like **
**                        macro                                               **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduR_RoutingPathGroupIdType id, boolean initialize  **
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
**                        PduR_InitStatus                                     **
**                        PduR_RoutingPathGroupMaxId, PduR_LoTxConfig         **
**                        PduR_IfTpConfirmationMaxPduId,                      **
**                        PduR_LowIfTxConfirmation, PduR_TxBufferConfig       **
**                        PduR_IfTxBuffer                                     **
**                                                                            **
** Function(s) invoked  : Det_ReportError(),                                  **
**                        SchM_Enter_PduR_GROUP_STATUS_PROTECTION_AREA(),     **
**                        SchM_Exit_PduR_GROUP_STATUS_PROTECTION_AREA(),	    **
**                        SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA(),      **
**                        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA          **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)

#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* @Traceability BEGIN -- SRS: SWS_PduR_00119 SWS_PduR_00100 SWS_PduR_00617
                               SWS_PduR_00805 SWS_PduR_00810 SWS_PduR_00649
                               SWS_PduR_00716 SWS_PduR_00028*/
FUNC(void, PDUR_VAR) PduR_DisableRouting(PduR_RoutingPathGroupIdType id,
  boolean initialize)
{
  #if (PDUR_TP_BUFFER_ROUTING_COUNT > PDUR_ZERO)
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTpBuffer;
  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrTpQueue;
  #endif
  uint8 loopTpIndex;
  #endif
  #if (PDUR_TX_BUFFER_ROUTING_COUNT > PDUR_ZERO)
  P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_VAR) ptrTxBuffer;
  #if (PDUR_DEFAULTVALUE_SUPPORT == STD_ON)
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) ptrDataBuffer;
  P2VAR(uint8, AUTOMATIC, PDUR_CONST) ptrDataDefault;
  #endif
  #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  P2VAR(PduR_TxQueueType, AUTOMATIC, PDUR_VAR) ptrQueue;
  #endif
  uint8 loopTxIndex;
  #endif
  #if ((PDUR_TX_BUFFER_ROUTING_COUNT > PDUR_ZERO) || \
    (PDUR_TP_BUFFER_ROUTING_COUNT > PDUR_ZERO))
  uint16 groupIdValue;
  #endif
  uint16 indexBitmask;
  uint16 idConvert;
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  boolean errorFlag;
  errorFlag = TRUE;
  if (PDUR_UNINIT == PduR_InitStatus)
  {
    /* @Trace: PduR_SUD_API_010 */
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_DISABLE_ROUTING_SID, PDUR_E_UNINIT);
    /* Set the return value to FALSE */
    errorFlag = (boolean)FALSE;
  } /* End of if (PDUR_UNINIT == PduR_InitStatus) */
  else
  {
    /* Check whether the Group Id Is present */
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_336 */
    if (id > PduR_RoutingPathGroupMaxId)
    #else
    /* @Trace: PduR_SUD_API_081 */
    if (id > PDUR_MAX_ROUTINGPATH_GROUP_ID)
    #endif
    {
      /* Report to DET */
      (void)Det_ReportError (PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_DISABLE_ROUTING_SID, PDUR_E_ROUTING_PATH_GROUP_ID_INVALID);
      errorFlag = (boolean)FALSE;
    }
    else
    {
      /* No Action */
    }
  }
  /* Check whether any development errors are detected */
  if ((boolean)TRUE == errorFlag)
  #endif  /* #if(PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: SRS_BSW_00312 */
    /* Disable relevant interrupts */
    SchM_Enter_PduR_GROUP_STATUS_PROTECTION_AREA();
    /* @Trace: SRS_PduR_06120 */
    /* @Trace: PduR_SUD_API_011 */
    /* Disable the routing path group*/
    indexBitmask = id / PDUR_BITMASK_UINT8;
    idConvert = id % PDUR_BITMASK_UINT8;
    PduR_GroupPathId[indexBitmask] = (uint8)(PduR_GroupPathId[indexBitmask] &
                                          (~(((uint32)PDUR_ONE) << idConvert)));
    /* Enable relevant interrupts */
    SchM_Exit_PduR_GROUP_STATUS_PROTECTION_AREA();

    if ((boolean)TRUE == initialize)
    {
      #if (PDUR_TX_BUFFER_ROUTING_COUNT > PDUR_ZERO)
      /* Clean all buffer of routing paths communication interfaces*/
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
      for (loopTxIndex = PDUR_ZERO; loopTxIndex < PduR_TxBufRoutingCount;
        loopTxIndex++)
      {
        /* @Trace: PduR_SUD_API_404 */
        /* Get the pointer to address of IfTxBuffer */
        ptrTxBuffer = &PduR_TxBufferConfig[loopTxIndex];
      #else
      for (loopTxIndex = PDUR_ZERO; loopTxIndex < PDUR_TX_BUFFER_ROUTING_COUNT;
        loopTxIndex++)
      {
        /* @Trace: PduR_SUD_API_403 */
        /* Get the pointer to address of PduR_IfTxBuffer */
        ptrTxBuffer = &PduR_IfTxBuffer[loopTxIndex];
      #endif
        /* Get group mask value from ptrTxBuffer */
        groupIdValue = ptrTxBuffer->GroupMaskValue;
        if (groupIdValue == id)
        {
          /* Start data buffer protection area*/
          /* @Trace: SRS_BSW_00312 */
          #if (PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
          SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
          #endif
          /* Check fifo is used */
          if ((uint8)PDUR_ONE != ptrTxBuffer->FIFODepth)
          {
            /* @Trace: PduR_SUD_API_012 */
            #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
            /* Clean queue in PduR buffer */
            while (NULL_PTR != ptrTxBuffer->FirstQueuePtr)
            {
              /* Set ptrQueue to first queue */
              ptrQueue = ptrTxBuffer->FirstQueuePtr;
              /* Clean FreeBuffer of ptrQueue*/
              ptrQueue->FreeBuffer = PDUR_EMPTY; /* polyspace RTE:IDP [Not a defect:Low] "this pointer in range of bound due to data flow" */
              /* Set first queue to next queue */
              ptrTxBuffer->FirstQueuePtr = ptrQueue->Next; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized variable due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
            }
            /* Clean buffer to zero */
            memset(ptrTxBuffer->SduPtr, PDUR_ZERO, ptrTxBuffer->TotalLength); /* polyspace RTE:STD_LIB [Justified:Low] "ptrTxBuffer->SduPtr can't NULL by it's controled by generator " */
            /* Clean Depth FIFO of PduR buffer */
            ptrTxBuffer->CurrentDepth = (uint8)PDUR_ZERO;
            /* Increment HeadLength to TotalLength*/
            ptrTxBuffer->HeadLength = ptrTxBuffer->TotalLength;
            /* Report to DET */
            (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                                                PDUR_DISABLE_ROUTING_SID,
                                                PDUR_E_PDU_INSTANCES_LOST);
            #endif /* #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
          }
          else
          {
            /* Clean buffer to zero */
            memset(ptrTxBuffer->SduPtr, PDUR_ZERO, ptrTxBuffer->SduLengthUpdate); /* polyspace RTE:STD_LIB [Justified:Low] "ptrTxBuffer->SduPtr can't NULL by it's controled by generator " */
            #if (PDUR_DEFAULTVALUE_SUPPORT == STD_ON)
            /* Get the default data pointer into local variable */
            ptrDataDefault = ptrTxBuffer->SduDefaultValuePtr;
            /* Check default value is configured */
            if (NULL_PTR != ptrDataDefault)
            {
              /* @Trace: PduR_SUD_API_013 */
              /* Get the data pointer into local variable */
              ptrDataBuffer = ptrTxBuffer->SduPtr;
              memcpy((P2VAR(void, AUTOMATIC, PDUR_VAR))(ptrDataBuffer),
                (P2CONST(void, AUTOMATIC, PDUR_CONST))(ptrDataDefault),
                ptrTxBuffer->SduLengthUpdate);
            }
            else
            {
              /* No Action */
            }
            #endif /* #if (PDUR_DEFAULTVALUE_SUPPORT == STD_ON) */
          }
          /* End data buffer protection area */
          #if (PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
          SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
          #endif
        }
        else
        {
          /* No Action */
        }
      }
      #endif /* #if (PDUR_TX_BUFFER_ROUTING_COUNT > PDUR_ZERO) */

      #if (PDUR_TP_BUFFER_ROUTING_COUNT > PDUR_ZERO)
      /* Clean all buffer of routing paths transport protocols*/
      #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
      for (loopTpIndex = PDUR_ZERO; loopTpIndex < PduR_TpBufRoutingCount;
        loopTpIndex++)
      {
        /* @Trace: PduR_SUD_API_406 */
        /* Get the pointer to address of PduR_GaaTpBuffer */
        ptrTpBuffer = &PduR_TpBufferConfig[loopTpIndex];
      #else
      for (loopTpIndex = PDUR_ZERO; loopTpIndex < PDUR_TP_BUFFER_ROUTING_COUNT;
        loopTpIndex++)
      {
        /* @Trace: PduR_SUD_API_405 */
        /* Get the pointer to address of PduR_GaaTpBuffer */
        ptrTpBuffer = &PduR_TpTxBuffer[loopTpIndex];
      #endif
        /* Get group mask value from ptrTpBuffer */
        groupIdValue = ptrTpBuffer->GroupMaskValue;
        if (groupIdValue == id)
        {
          /* Start data buffer protection area*/
          #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
          SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
          #endif
          #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
          /* Check fifo is used */
          if (NULL_PTR == ptrTpBuffer->SinBufPtr)
          {
            /* @Trace: PduR_SUD_API_014 */
            /* Clean queue in PduR buffer */
            while (NULL_PTR != ptrTpBuffer->FirstQueuePtr)
            {
              /* Set ptrTpQueue to first queue */
              ptrTpQueue = ptrTpBuffer->FirstQueuePtr;
              /* Clean TxConfirm of ptrQueue*/
              ptrTpQueue->TxConfirm       = (uint8)PDUR_ZERO; /* polyspace RTE:IDP [Not a defect:Low] "this pointer in range of bound due to design module" */
              /* Clean FreeBuffer of ptrQueue*/
              ptrTpQueue->FreeBuffer      = (boolean)PDUR_FALSE;
              /* Set RxState of ptrQueue to PDUR_RX_YETTOSTART*/
              ptrTpQueue->RxState         = PDUR_RX_YETTOSTART;
              /* Set first queue to next queue */
              ptrTpBuffer->FirstQueuePtr  = ptrTpQueue->Next; /* polyspace MISRA-C:2012 D4.1 [Not a defect:Low] "initialized variable due to data flow" */ /* polyspace RTE:NIP [Not a defect:Unset] "initialized variable due to data flow" */
            }
            /* Increment HeadLength to TotalLength*/
            ptrTpBuffer->HeadLength      = ptrTpBuffer->TotalLength;
            /* Clean Depth FIFO of PduR buffer */
            ptrTpBuffer->CurrentDepth    = (uint8)PDUR_ZERO;
            /* Report to DET */
            (void)Det_ReportRuntimeError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                                                PDUR_DISABLE_ROUTING_SID,
                                                PDUR_E_PDU_INSTANCES_LOST);
          }
          else
          #endif /* #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON) */
          {
            /* @Trace: PduR_SUD_API_329 */
            /* Clean FreeBuffer of SinBufPtr struct*/
            ptrTpBuffer->SinBufPtr->FreeBuffer = (boolean)PDUR_FALSE; /* polyspace RTE:IDP [Not a defect:Low] "this pointer in range of bound due to design module" */
            /* Set RxState of SinBufPtr to PDUR_RX_YETTOSTART */
            ptrTpBuffer->SinBufPtr->RxState    = PDUR_RX_YETTOSTART; /* polyspace RTE:IDP [Not a defect:Low] "this pointer in range of bound due to design module" */
            /* Clean TxConfirm of SinBufPtr struct*/
            ptrTpBuffer->SinBufPtr->TxConfirm  = (uint8)PDUR_ZERO; /* polyspace RTE:IDP [Not a defect:Low] "this pointer in range of bound due to design module" */
          }
          #if (PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
          SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
          #endif
          /* End data buffer protection area */
        }
        else
        {
          /* No Action */
        }
      }
      #endif /* #if (PDUR_TP_BUFFER_ROUTING_COUNT > PDUR_ZERO) */
    }
    else
    {
      /* No Action */
    }
  }
  #if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No Action */
  }
  #endif
} /* End of PduR_DisableRouting(PduR_RoutingPathGroupIdType id) */
/* @Traceability END -- SRS: SWS_PduR_00119 SWS_PduR_00100 SWS_PduR_00617
                             SWS_PduR_00805 SWS_PduR_00810 SWS_PduR_00649
                             SWS_PduR_00716 SWS_PduR_00028 */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
#endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
