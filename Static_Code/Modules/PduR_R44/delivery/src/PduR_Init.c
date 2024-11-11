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
**  SRC-MODULE: PduR_Init.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of Initialization and version control functionality **
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
#include "PduR.h"                /* PDU Router RAM header */
#include "SchM_PduR.h"           /* SchM header */
#include "string.h"              /* memcpy() */
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
** Function Name        : PduR_Init                                           **
**                                                                            **
** Service ID           : 0xF0                                                **
**                                                                            **
** Description          : This Service initializes PDU Router initialization. **
**                        If the configuration parameter                      **
**                        PDUR_ZERO_COST_OPERATION is enabled this service    **
**                        shall be realized as an empty function-like macro.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : PduR_PBConfigType *ConfigPtr                        **
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
**                        PduR_InitStatus,                                    **
**                        PduR_IfTxBuffer, PduR_TpTxBuffer, PduR_RamAreaTx    **
**                        PduR_UpTransmitConfig, PduR_ConfigurationId         **
**                        PduR_UpTransmitMaxPduId, PduR_PoolPtr               **
**                        PduR_LoRxConfig, PduR_IfTpRxIndicationMaxPduId      **
**                        PduR_LoTxConfig, PduR_IfTpConfirmationMaxPduId      **
**                        PduR_TxBufferConfig, PduR_TxBufRoutingCount         **
**                        PduR_TpBufferConfig, PduR_TpBufRoutingCount         **
**                        PduR_RoutingPathGroupMaxId, PduR_TpGWLowDestCount   **
**                                                                            **
** Function(s) invoked  : SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA()       **
**                        SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA()        **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00101 */
/* @Trace: SRS_BSW_00358 */
/* @Trace: SRS_BSW_00310 */
/* @Trace: SRS_PduR_06001 */
#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* @Traceability BEGIN -- SRS: SWS_PduR_00325 SWS_PduR_00644 SWS_PduR_00645
                               SWS_PduR_00324 SWS_PduR_00326 SWS_PduR_00308
                               SWS_PduR_00334 SWS_PduR_00709 */
FUNC(void, PDUR_CODE) PduR_Init(P2CONST(PduR_PBConfigType, AUTOMATIC,
    PDUR_APPL_CONST) ConfigPtr)
{
  #if (PDUR_ZERO_COST_OPERATION == STD_OFF)
  #if (PDUR_TP_BUFFER_ROUTING_COUNT > PDUR_ZERO)
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) ptrTpBuffer;
  #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
  P2VAR(PduR_TpQueueType, AUTOMATIC, PDUR_VAR) ptrTpQueue;
  #endif
  uint8 loopTpIndex;
  #endif
  #if ((PDUR_DEV_ERROR_DETECT == STD_ON) &&\
    (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON))
  boolean inputValid;
  inputValid = (boolean)PDUR_TRUE;
  #endif
  #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
  uint8 indexPool;
  #endif
  #if (PDUR_TP_TXCONFIRMATION == STD_ON)
  #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
  uint8 indexLoTp;
  #endif
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
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 indexGroup;
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) ptrGroupPathId;
  P2CONST(uint8, AUTOMATIC, PDUR_VAR) ptrPathIdAtInit;
  #endif
  #endif
  /* @Trace: SRS_BSW_00405 */
  /* @Trace: SRS_PduR_06002 */
  #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
  if (NULL_PTR != ConfigPtr)
  {
    /* @Trace: PduR_SUD_API_331 */
    #if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
    PduR_UpTransmitConfig = ConfigPtr->UpTransmit;
    PduR_UpTransmitMaxPduId = ConfigPtr->UpTransmitMaxPduId;
    #endif
    #if ((PDUR_LO_RXINDICATION == STD_ON)||(PDUR_TP_RXINDICATION == STD_ON))
    PduR_LoRxConfig = ConfigPtr->LoRxSource;
    PduR_IfTpRxIndicationMaxPduId = ConfigPtr->IfTpRxIndicationMaxPduId;
    #endif
    #if ((PDUR_LO_TXCONFIRMATION == STD_ON)||(PDUR_TP_TXCONFIRMATION == STD_ON))
    PduR_LoTxConfig = ConfigPtr->LoTxDestination;
    PduR_IfTpConfirmationMaxPduId = ConfigPtr->IfTpConfirmationMaxPduId;
    #endif
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    ptrGroupPathId = ConfigPtr->GroupPathId;
    ptrPathIdAtInit = ConfigPtr->PathIdAtInit;
    #endif
    #if (PDUR_TX_BUFFER_ROUTING_COUNT > PDUR_ZERO)
    PduR_TxBufferConfig = ConfigPtr->IfTxBuffer;
    PduR_TxBufRoutingCount = ConfigPtr->TxBufRoutingCount;
    #endif
    #if (PDUR_TP_BUFFER_ROUTING_COUNT > PDUR_ZERO)
    PduR_TpBufferConfig = ConfigPtr->TpTxBuffer;
    PduR_TpBufRoutingCount = ConfigPtr->TpBufRoutingCount;
    #endif
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    PduR_RoutingPathGroupMaxId = ConfigPtr->RoutingPathGroupMaxId;
    #endif
    #if ((PDUR_TP_TXCONFIRMATION == STD_ON) &&\
      (PDUR_TP_GATEWAY_OPERATION == STD_ON))
    PduR_TpGWLowDestCount = ConfigPtr->TpGWLowDestCount;
    #endif
    PduR_ConfigurationId = ConfigPtr->ConfigurationId;
  }
  else
  {
    /* @Trace: PduR_SUD_API_332 */
    #if (PDUR_DEV_ERROR_DETECT == STD_ON)
    inputValid = (boolean)PDUR_FALSE;
    /* Report to DET  */
    (void)(Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PDUR_INIT_SID,
      PDUR_E_INIT_FAILED));
    #endif
  }
  #else
  /* To avoid Compiler warning since "ConfigPtr" is not used in the function */
  /* polyspace<MISRA-C:14.2 : Low : Justify with annotations> Not a defect */
  /* @Trace: SRS_BSW_00414 */
  /* @Trace: PduR_SUD_API_432 */
  PDUR_UNUSED_PTR(ConfigPtr);
  #endif
  #if ((PDUR_DEV_ERROR_DETECT == STD_ON) &&\
    (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON))
  if ((boolean)PDUR_TRUE == inputValid)
  #endif
  {
    #if (PDUR_TX_BUFFER_ROUTING_COUNT > PDUR_ZERO)
    /* Clean all buffer of routing paths communication interfaces*/
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    for (loopTxIndex = PDUR_ZERO; loopTxIndex < PduR_TxBufRoutingCount;
      loopTxIndex++)
    {
      /* Get the pointer to address of IfTxBuffer */
      ptrTxBuffer = &PduR_TxBufferConfig[loopTxIndex];
    #else
    for (loopTxIndex = PDUR_ZERO; loopTxIndex < PDUR_TX_BUFFER_ROUTING_COUNT;
      loopTxIndex++)
    {
      /* Get the pointer to address of PduR_IfTxBuffer */
      ptrTxBuffer = &PduR_IfTxBuffer[loopTxIndex];
    #endif
      /* @Trace: SRS_BSW_00312 */
      /* Start data buffer protection area*/
      #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
      SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
      #endif
      /* Check fifo is used */
      if ((uint8)PDUR_ONE != ptrTxBuffer->FIFODepth)
      {
        #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
        /* Clean queue in PduR buffer */
        while (NULL_PTR != ptrTxBuffer->FirstQueuePtr)
        {
          /* @Trace: PduR_SUD_API_327 */
          /* Set ptrQueue to first queue */
          ptrQueue = ptrTxBuffer->FirstQueuePtr;
          /* Clean FreeBuffer of ptrQueue*/
          ptrQueue->FreeBuffer = PDUR_EMPTY; /* polyspace RTE:IDP [Not a defect:Low] "this pointer in range of bound due to data flow" */
          /* Set first queue to next queue */
          ptrTxBuffer->FirstQueuePtr = ptrQueue->Next; /* polyspace RTE:NIP [Justified:Low] "this pointer is initialized by "ptrQueue->Next = NULL_PTR" in PduR_GWBufferUpdate func" */
        }
        /* Clean buffer to zero */
        memset(ptrTxBuffer->SduPtr, PDUR_ZERO, ptrTxBuffer->TotalLength); /* polyspace RTE:STD_LIB [Justified:Low] "ptrTxBuffer->SduPtr can't NULL by it's controled by generator " */
        /* @Trace: PduR_SUD_API_001 */
        /* Clean Depth FIFO of PduR buffer */
        ptrTxBuffer->CurrentDepth = (uint8)PDUR_ZERO;
        /* Increment HeadLength to TotalLength*/
        ptrTxBuffer->HeadLength = ptrTxBuffer->TotalLength;
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
          /* @Trace: PduR_SUD_API_330 */
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
        #endif
      }
      #if (PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
      SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
      #endif
    }
    #endif /* #if (PDUR_TX_BUFFER_ROUTING_COUNT > PDUR_ZERO) */

    #if (PDUR_TP_BUFFER_ROUTING_COUNT > PDUR_ZERO)
    /* Clean all buffer of routing paths transport protocols*/
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    for (loopTpIndex = PDUR_ZERO; loopTpIndex < PduR_TpBufRoutingCount;
      loopTpIndex++)
    {
      /* Get the pointer to address of PduR_GaaTpBuffer */
      ptrTpBuffer = &PduR_TpBufferConfig[loopTpIndex];
    #else
    for (loopTpIndex = PDUR_ZERO; loopTpIndex < PDUR_TP_BUFFER_ROUTING_COUNT;
      loopTpIndex++)
    {
      /* Get the pointer to address of PduR_GaaTpBuffer */
      ptrTpBuffer = &PduR_TpTxBuffer[loopTpIndex];
    #endif
      /* @Trace: SRS_BSW_00312 */
      /* Start data buffer protection area*/
      #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
      SchM_Enter_PduR_DATA_BUFFER_PROTECTION_AREA();
      #endif
      #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON)
      /* Check fifo is used */
      if (NULL_PTR == ptrTpBuffer->SinBufPtr)
      {
        /* Clean queue in PduR buffer */
        while (NULL_PTR != ptrTpBuffer->FirstQueuePtr)
        {
          /* @Trace: PduR_SUD_API_002 */
          /* Set ptrTpQueue to first queue */
          ptrTpQueue = ptrTpBuffer->FirstQueuePtr;
          /* Clean TxConfirm of ptrQueue*/
          ptrTpQueue->TxConfirm       = (uint8)PDUR_ZERO; /* polyspace RTE:IDP [Justified:Low] "this pointer in range of bound due to data flow" */
          /* Clean FreeBuffer of ptrQueue*/
          ptrTpQueue->FreeBuffer      = (boolean)PDUR_FALSE;
          /* Set RxState of ptrQueue to PDUR_RX_YETTOSTART*/
          ptrTpQueue->RxState         = PDUR_RX_YETTOSTART;
          /* Set first queue to next queue */
          ptrTpBuffer->FirstQueuePtr  = ptrTpQueue->Next; /* polyspace RTE:NIP [Justified:Low] "this pointer is initialized by "ptrQueue->Next = NULL_PTR" in PduR_BuffUpdateLoTpStartOfReception func" */
        }
        /* Increment HeadLength to TotalLength*/
        ptrTpBuffer->HeadLength      = ptrTpBuffer->TotalLength;
        /* Clean Depth FIFO of PduR buffer */
        ptrTpBuffer->CurrentDepth    = (uint8)PDUR_ZERO;
      }
      else
      #endif /* #if (PDUR_FIFO_TP_BUFFER_SUPPORT == STD_ON) */
      {
        /* @Trace: PduR_SUD_API_003 */
        /* Clean FreeBuffer of SinBufPtr struct*/
        ptrTpBuffer->SinBufPtr->FreeBuffer = (boolean)PDUR_FALSE; /* polyspace RTE:IDP [Not a defect:Low] "this pointer in range of bound due to data flow" */
        /* Set RxState of SinBufPtr to PDUR_RX_YETTOSTART */
        ptrTpBuffer->SinBufPtr->RxState    = PDUR_RX_YETTOSTART; /* polyspace RTE:IDP [Not a defect:Low] "this pointer in range of bound due to data flow" */
        /* Clean TxConfirm of SinBufPtr struct*/
        ptrTpBuffer->SinBufPtr->TxConfirm  = (uint8)PDUR_ZERO; /* polyspace RTE:IDP [Not a defect:Low] "this pointer in range of bound due to data flow" */
      }
      #if(PDUR_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
      SchM_Exit_PduR_DATA_BUFFER_PROTECTION_AREA();
      #endif
      /* End data buffer protection area */
    }
    #endif /* #if (PDUR_TP_BUFFER_ROUTING_COUNT > PDUR_ZERO) */

    #if (PDUR_POOL_TP_BUFFER_SUPPORT == STD_ON)
    /* Clean all pool buffer */
    for (indexPool = PDUR_ZERO; indexPool < PDUR_TP_POOLS_INDEX_COUNT;
      indexPool++)
    {
      if ((boolean)PDUR_TRUE == PduR_PoolPtr[indexPool].State)
      {
        /* @Trace: PduR_SUD_API_004 */
        PduR_PoolPtr[indexPool].State = (boolean)PDUR_FALSE;
      }
      else
      {
        /* No Action */
      }
    }
    #endif

    #if (PDUR_TP_TXCONFIRMATION == STD_ON)
    #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
    /* Clean all global variable */
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    for (indexLoTp = PDUR_ZERO; indexLoTp < PduR_TpGWLowDestCount; indexLoTp++)
    #else
    for (indexLoTp = PDUR_ZERO;
      indexLoTp < PDUR_TP_GATEWAY_LOW_DESTINATION_COUNT; indexLoTp++)
    #endif
    {
      /* @Trace: PduR_SUD_API_005 */
      PduR_RamAreaTx[indexLoTp] = (PduLengthType)PDUR_ZERO;
    }
    #endif
    #endif
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_OFF)
    for (indexGroup = PDUR_ZERO; indexGroup <
                          PDUR_PATH_GROUP_MULTI_8_COUNT_MAX; indexGroup++)
    {
      /* @Trace: PduR_SUD_API_005 */
      PduR_GroupPathId[indexGroup] = PduR_GroupPathIdAtInit[indexGroup];
    }
    #else
    for (indexGroup = PDUR_ZERO; indexGroup <
                                ConfigPtr->PathGroupMulti32Count; indexGroup++)
    {
      /* @Trace: PduR_SUD_API_005 */
      *ptrGroupPathId = *ptrPathIdAtInit;
      ptrGroupPathId++;
      ptrPathIdAtInit++;
    }
    #endif
    #endif
    /* Set the InitStatus to PDUR_ONLINE */
    #if (PDUR_DEV_ERROR_DETECT == STD_ON)
    PduR_InitStatus = PDUR_ONLINE;
    #endif /* End of #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  }
  #if ((PDUR_DEV_ERROR_DETECT == STD_ON) &&\
    (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON))
  else
  {
    /* No Action */
  }
  #endif
  #else
  /* @Trace: PduR_SUD_API_432 */
  PDUR_UNUSED_PTR(ConfigPtr);
  #endif /* #if (PDUR_ZERO_COST_OPERATION == STD_OFF) */
} /* End of PduR_Init(P2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_CONST)
   *ConfigPtr) */
/* @Traceability END -- SRS: SWS_PduR_00325 SWS_PduR_00644 SWS_PduR_00645
                             SWS_PduR_00324 SWS_PduR_00326 SWS_PduR_00308
                             SWS_PduR_00334 SWS_PduR_00709 */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : PduR_GetVersionInfo                                 **
**                                                                            **
** Service ID           : 0xF1                                                **
**                                                                            **
** Description          : This service returns the version information of     **
**                        this module.                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Std_VersionInfoType *versioninfo                    **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        None                                                **
**                                                                            **
** Function(s) invoked :  Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00310 */
/* @Trace: SRS_BSW_00407 */
/* @Trace: SRS_BSW_00411 */
#if (PDUR_VERSION_INFO_API == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* @Traceability BEGIN -- SRS: SWS_PduR_00338 */
/* @Trace: SRS_BSW_00406 */
FUNC(void, PDUR_CODE) PduR_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
    PDUR_APPL_DATA) versioninfo)
{
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  /* Check whether Version Information is equal to Null Ptr */
  if (NULL_PTR == versioninfo)
  {
    /* Report to DET  */
    /* @Trace: SRS_BSW_00480 */
    /* @Trace: PduR_SUD_API_007 */
    (void)(Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PDUR_GET_VERSION_SID,
      PDUR_E_PARAM_POINTER));
  }
  else
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: PduR_SUD_API_006 */
    /* Copy the vendor Id */
    /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "Pointer is not a NULL and valid" */
    versioninfo->vendorID = PDUR_VENDOR_ID;
    /* Copy the module Id */
    versioninfo->moduleID = PDUR_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = PDUR_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = PDUR_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = PDUR_SW_PATCH_VERSION;
    /* polyspace-end MISRA-C3:D4.14 [Not a defect:Low] "Pointer is not a NULL and valid" */
  }
} /* End of PduR_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
   *PDUR_APPL_DATA) versioninfo) */
/* @Traceability END -- SRS: SWS_PduR_00338 */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (PDUR_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name        : PduR_GetConfigurationId                             **
**                                                                            **
** Service ID           : 0xF2                                                **
**                                                                            **
** Description          : This service returns unique identifier of the       **
**                        post-build time configuration of the PDU Router.    **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : PduR_PBConfigIdType PduR_ConfigurationId            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : PduR_ConfigurationId           **
**                        None                                                **
**                                                                            **
** Function(s) invoked :  None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_PduR_06097 */
#if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
FUNC(PduR_PBConfigIdType, PDUR_CODE) PduR_GetConfigurationId(void)
{
  /* @Trace: PduR_SUD_API_339 */
  return PduR_ConfigurationId;
} /* End of PduR_GetConfigurationId(void) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
