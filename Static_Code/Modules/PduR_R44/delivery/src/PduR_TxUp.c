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
**  SRC-MODULE: PduR_TxUp.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of the functionality of PduR_DETCheckUpTransmit()   **
**              PduR_UpTransmit(), PduR_IfTransmit()                          **
**              and PduR_TpTransmit(), PduR_UpCancelTransmit                  **
**              PduR_DETCheckCancelTransmit                                   **
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
** 1.0.3       07-Dec-2021   PhucNHM     R44-Redmine #22235                   **
** 1.0.2       05-Oct-2021   PhucNHM     R44-Redmine #20586                   **
** 1.0.1       22-Jun-2021   PhucNHM     R44-Redmine #18951                   **
** 1.0.0       04-Dec-2020   AUTOEVER    Initial Version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: PduR_SUD_FILE_001 */
#include "PduR.h"                 /* Header File */
#include "PduR_IntTypes.h"   /* PDU Router module post-build time header */
#include "SchM_PduR.h"            /* SchM header */
#include "PduR_TxUp.h"            /* PduR Transmit header */
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
#if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_DETCheckUpTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType txPduId, uint8 moduleType);

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
#endif /* End of if ((PDUR_IF_TRANSMIT == STD_ON)||
        *(PDUR_TP_TRANSMIT == STD_ON))*/
#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_ON) */

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_IF_CANCEL_TRANSMIT_SUPPORT == STD_ON) ||\
  (PDUR_TP_CANCEL_TRANSMIT_SUPPORT == STD_ON))
#if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_DETCheckCancelTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType txPduId, uint8 moduleType);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif
#endif

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TRANSMIT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_TpTransmit
(P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) ptrUpTransmit,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_IF_TRANSMIT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_IfTransmit /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
(P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) ptrUpTransmit,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace:begin<MISRA-C:17.4:Not a defect:Justify with annotations> Not a defect, Decrement and Increment operator is used to achieve better throughput */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
/* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > configured memory access index */
/* polyspace:begin<RTE: COR : Not a defect : No Action Planned > masked value is generated based on configuration, masking value is defined for dividing configured functionality. function pointer is verified before ivoking */
/* polyspace:begin<RTE: NIV : Not a defect : Justify with annotations > initialized variable */
/* polyspace:begin<RTE: NIP : Not a defect : Justify with annotations > pointer is not null */
/*******************************************************************************
** Function Name        : PduR_UpTransmit                                     **
**                                                                            **
** Service ID           : 0x49                                                **
**                                                                            **
** Description          : Common function for requests transmission a PDU     **
**                        from upper module                                   **
**                                                                            **
** Sync/Async           : Async                                               **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PduIdType txPduId,                                  **
**                        uint8 moduleType, PduInfoType ptrPduInfoPtr         **
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
**                        PduR_UpIfTpTransmit, PduR_UpTransmitConfig          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckUpTransmit()                           **
**                        PduR_IfTransmit()                                   **
**                        PduR_TpTransmit()                                   **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_PduR_06114 */
/* @Trace: SRS_PduR_06115 */
/* @Trace: SRS_PduR_06116 */
/* @Trace: SRS_BSW_00167 */
/* @Trace: SRS_BSW_00171 */
/* @Trace: SRS_PduR_06003 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
/* @Traceability BEGIN -- SRS: SWS_PduR_00160 SWS_PduR_00161 SWS_PduR_00766
                               SWS_PduR_00162 SWS_PduR_00119 SWS_PduR_00100
                               SWS_PduR_00330 SWS_PduR_00629 SWS_PduR_00221
                               SWS_PduR_00745 SWS_PduR_00625 SWS_PduR_00717
                               SWS_PduR_00626 SWS_PduR_00432 SWS_PduR_00328
                               SWS_PduR_00805 SWS_PduR_00633 SWS_PduR_00007
                               SWS_PduR_00822 SWS_PduR_00634 SWS_PduR_00287
                               SWS_PduR_00218 SWS_PduR_00589 SWS_PduR_00715
                               SWS_PduR_00406 SWS_PduR_00824 SWS_PduR_00009
                               SWS_PduR_00012 SWS_PduR_00764 */
FUNC(Std_ReturnType, PDUR_CODE) PduR_UpTransmit(PduIdType txPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr)
#else
FUNC(Std_ReturnType, PDUR_CODE) PduR_UpTransmit(PduIdType txPduId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr)
#endif
{
  P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) ptrUpTransmit;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif
  Std_ReturnType returnVal;
  /* Check for the DET */
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  returnVal = PduR_DETCheckUpTransmit(txPduId, moduleType);

  /* Check whether any development errors are detected */
  if ((Std_ReturnType)E_OK == returnVal)
  #endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_333 */
    /* Get the pointer to ptrUpTransmit from UpTransmit */
    ptrUpTransmit = &PduR_UpTransmitConfig[txPduId];
    #else
    /* @Trace: PduR_SUD_API_015 */
    /* Get the pointer to ptrUpTransmit from PduR_UpIfTpTransmit */
    ptrUpTransmit = &PduR_UpIfTpTransmit[txPduId];
    #endif
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    groupIdValue = ptrUpTransmit->GroupMaskValue;
    indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
    idConvert = groupIdValue % PDUR_BITMASK_UINT8;
    /* @Trace: SRS_PduR_06120 */
    /* Check if routing path is enabled */
    if ((PDUR_UNDEFINED == groupIdValue) ||
        ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] & /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
                                          (((uint32)PDUR_ONE) << idConvert))))
    #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
    {
      #if(PDUR_IF_TRANSMIT == STD_ON)
      /* Check whether the transmit request if for TP or If layer */
      if((uint8)PDUR_TP_LAYER !=
                          ((ptrUpTransmit->FraTIOrNoOfRoute) & PDUR_TP_LAYER))
      {
        /* @Trace: PduR_SUD_API_017 */
        returnVal = PduR_IfTransmit(ptrUpTransmit, ptrPduInfoPtr);
      }
      else
      #endif /* End of if (PDUR_IF_TRANSMIT == STD_ON) */
      {
        /* @Trace: PduR_SUD_API_018 */
        #if (PDUR_TP_TRANSMIT == STD_ON)
        returnVal = PduR_TpTransmit(ptrUpTransmit, ptrPduInfoPtr);
        #endif /* End of if (PDUR_TP_TRANSMIT == STD_ON) */
      }
    }
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    else
    { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
      /* @Trace: PduR_SUD_API_016 */
      returnVal = (Std_ReturnType)E_NOT_OK;
    }
    #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
  }
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No Action */
  }
  #endif
  return (returnVal);
} /* End of PduR_UpTransmit(PduIdType txPduId, P2CONST(PduInfoType,
   * AUTOMATIC, PDUR_CONST) ptrPduInfoPtr) */
/* @Traceability END -- SRS: SWS_PduR_00160 SWS_PduR_00161 SWS_PduR_00766
                               SWS_PduR_00162 SWS_PduR_00119 SWS_PduR_00100
                               SWS_PduR_00330 SWS_PduR_00629 SWS_PduR_00221
                               SWS_PduR_00745 SWS_PduR_00625 SWS_PduR_00717
                               SWS_PduR_00626 SWS_PduR_00432 SWS_PduR_00328
                               SWS_PduR_00805 SWS_PduR_00633 SWS_PduR_00007
                               SWS_PduR_00822 SWS_PduR_00634 SWS_PduR_00287
                               SWS_PduR_00218 SWS_PduR_00589 SWS_PduR_00715
                               SWS_PduR_00406 SWS_PduR_00824 SWS_PduR_00009
                               SWS_PduR_00012 SWS_PduR_00764 */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*  #if (PDUR_IF_TRANSMIT == STD_ON)  */
#endif /*  #if (PDUR_ZERO_COST_OPERATION == STD_OFF)  */

/*******************************************************************************
** Function Name        : PduR_DETCheckUpTransmit                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Det Check for Transmit Function called by upper     **
**                        layer                                               **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType txPduId,                                  **
**                        uint8 moduleType, PduInfoType *ptrPduInfoPtr        **
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
**                        PduR_UpIfTpTransmit, PduR_InitStatus,               **
**                        PduR_UpTransmitConfig, PduR_UpTransmitMaxPduId      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_IF_TRANSMIT == STD_ON) || (PDUR_TP_TRANSMIT == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_DETCheckUpTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType txPduId, uint8 moduleType)
{
  P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) ptrUpTransmit;
  /* Initialize returnValue to E_OK */
  Std_ReturnType returnVal = (Std_ReturnType)E_OK;

  /* Check whether the module is initialised */
  if (PDUR_UNINIT == PduR_InitStatus)
  {
    /* @Trace: SRS_BSW_00406 */
    /* @Trace: PduR_SUD_API_019 */
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_TRANSMIT_SID, PDUR_E_UNINIT);
    /* Set the return value to E_NOT_OK */
    returnVal = (Std_ReturnType)E_NOT_OK;
  } /* End of if (PDUR_UNINIT == PduR_InitStatus) */
  else
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_340 */
    /* Get the pointer to ptrUpTransmit from UpTransmit */
    ptrUpTransmit = &PduR_UpTransmitConfig[txPduId];
    /* Check PduId is valid */
    if (txPduId >= PduR_UpTransmitMaxPduId)
    #else
    /* @Trace: PduR_SUD_API_111 */
    /* Get the pointer to ptrUpTransmit from PduR_UpIfTpTransmit */
    ptrUpTransmit = &PduR_UpIfTpTransmit[txPduId];
    /* Check PduId is valid */
    if (txPduId >= PDUR_UP_MAXPDUID)
    #endif
    {
      /* Report to DET */
      /* @Trace: SRS_PduR_06103 */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_TRANSMIT_SID, PDUR_E_PDU_ID_INVALID);
      /* Set the return value to E_NOT_OK */
      returnVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      if (ptrUpTransmit->ModuleType != moduleType) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:IDP [Not a defect:Low] "configured memory access index" */
      {
        /* Report to DET */
        /* @Trace: SRS_PduR_06103 */
        /* @Trace: PduR_SUD_API_020 */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
                                PDUR_TRANSMIT_SID, PDUR_E_PDU_ID_INVALID);
        /* Set the return value to E_NOT_OK */
        returnVal = (Std_ReturnType)E_NOT_OK;
      } /* (ptrUpTransmit->ModuleType != moduleType) */
      else
      {
        /* No Action */
      }
    }
  }
  /* Return Std Return Value*/
  return (returnVal);
} /* End of PduR_DETCheckUpTransmit(
   * PduIdType txPduId, uint8 moduleType)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /*#if (PDUR_DEV_ERROR_DETECT == STD_ON)  */
#endif /*#if (PDUR_IF_TRANSMIT == STD_ON)  */
#endif /*#if (PDUR_ZERO_COST_OPERATION == STD_ON)  */

/*******************************************************************************
** Function Name        : PduR_UpCancelTransmit                               **
**                                                                            **
** Service ID           : 0x4a                                                **
**                                                                            **
** Description          : The PDU Router shall translate the upper layer      **
**                        into the configured target PDU ID and route this    **
**                        cancel transmit request to the configured target    **
**                        TP or IF module.                                    **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : PduIdType txPduId,                                  **
**                        uint8 moduleType                                    **
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
**                        PduR_UpTpCancellation, PduR_UpTransmitConfig        **
**                        PduR_UpIfCancelTransmitService,                     **
**                        PduR_UpIfTpTransmit                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        PduR_DETCheckCancelTransmit()                       **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_PduR_06122 */
/* @Trace: SRS_BSW_00167 */
/* @Trace: SRS_BSW_00171 */
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_IF_CANCEL_TRANSMIT_SUPPORT == STD_ON) ||\
  (PDUR_TP_CANCEL_TRANSMIT_SUPPORT == STD_ON))
#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* @Traceability BEGIN -- SRS: SWS_PduR_00119 SWS_PduR_00100 SWS_PduR_00722
                               SWS_PduR_00721 SWS_PduR_00700 SWS_PduR_00221
                               SWS_PduR_00723 SWS_PduR_00701 SWS_PduR_00724
                               SWS_PduR_00710 SWS_PduR_00287 SWS_PduR_00161
                               SWS_PduR_00328 SWS_PduR_00330 SWS_PduR_00717
                               SWS_PduR_00715 SWS_PduR_00769 SWS_PduR_00824
                               SWS_PduR_00025 SWS_PduR_00764 */
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_UpCancelTransmit(PduIdType txPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  uint8 moduleType)
#else
FUNC(Std_ReturnType, PDUR_CODE) PduR_UpCancelTransmit(PduIdType txPduId)
#endif
{
  #if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
  P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) ptrUpTransmit;
  #if (PDUR_IF_CANCEL_TRANSMIT_SUPPORT == STD_ON)
  #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
  P2CONST(PduR_MulticastTxPdu, AUTOMATIC, PDUR_CONST) ptrMulticastTxPdu;
  #endif
  #endif
  #if (PDUR_TP_CANCEL_TRANSMIT_SUPPORT == STD_ON)
  #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
  P2CONST(PduR_MulticastTpPdu, AUTOMATIC, PDUR_CONST) ptrMulticastTpPdu;
  #endif
  #endif
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif

  #if ((PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON) || \
      (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON))
  uint8 noOfRoutePdu;
  #endif
  #endif
  /* Return value of the function */
  Std_ReturnType returnVal = (Std_ReturnType)E_OK;

  #if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
  /* Set return value to E_OK */
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  returnVal = PduR_DETCheckCancelTransmit(txPduId, moduleType);

  /* Check whether any development errors are detected */
  if ((Std_ReturnType)E_OK == returnVal)
  #endif /* #if(PDUR_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    /* @Trace: PduR_SUD_API_415 */
    /* Get the pointer to ptrUpTransmit from UpTransmit */
    ptrUpTransmit = &PduR_UpTransmitConfig[txPduId];
    #else
    /* @Trace: PduR_SUD_API_029 */
    /* Get the pointer to ptrUpTransmit from PduR_UpIfTpTransmit */
    ptrUpTransmit = &PduR_UpIfTpTransmit[txPduId];
    #endif
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    /* Get the group mask value */
    groupIdValue = ptrUpTransmit->GroupMaskValue;
    indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
    idConvert = groupIdValue % PDUR_BITMASK_UINT8;
    /* @Trace: SRS_PduR_06120 */
    /* Check if routing path is enabled */
    if ((PDUR_UNDEFINED == groupIdValue) ||
        ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] & /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
                                          (((uint32)PDUR_ONE) << idConvert))))
    #endif
    {
      #if(PDUR_IF_TRANSMIT == STD_ON)
      if((uint8)PDUR_TP_LAYER !=
                           ((ptrUpTransmit->FraTIOrNoOfRoute) & PDUR_TP_LAYER))
      {
        /* Check if Multicast */
        #if (PDUR_IF_CANCEL_TRANSMIT_SUPPORT == STD_ON)
        #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
        if ((uint8)PDUR_MULTICAST_MASK ==
            ((ptrUpTransmit->FraTIOrNoOfRoute) & ((uint8)PDUR_MULTICAST_MASK)))
        {
          /* @Trace: PduR_SUD_API_031 */
          /* Assign returnVal with E_OK */
          returnVal = (Std_ReturnType)E_OK;
          ptrMulticastTxPdu =
                           (P2CONST(PduR_MulticastTxPdu, AUTOMATIC, PDUR_CONST))
                             (ptrUpTransmit->MulticastTpOrTxPdu);

          /* Get the pointer to noOfRoutePdu from PduR_UpTransmit */
          noOfRoutePdu =
           (uint8)((ptrUpTransmit->FraTIOrNoOfRoute) & PDUR_TARGET_INDEX_MASK);

          /* Loop for all the destinations in case of multicast */
          /* @Trace: SRS_PduR_06125 */
          do
          {
            /* Invoke Cancel transmit function */
            if (PduR_UpIfCancelTransmitService[ptrMulticastTxPdu->TargetIndex].
              TargetLayer != NULL_PTR)
            {
            /* @Trace: PduR_SUD_API_034 */
              returnVal = returnVal |
                PduR_UpIfCancelTransmitService[ptrMulticastTxPdu->TargetIndex].
                TargetLayer(ptrMulticastTxPdu->TargetPduId);
            }
            else
            {
            /* @Trace: PduR_SUD_API_035 */
              returnVal = (Std_ReturnType)E_NOT_OK;
            }
            /* Get the next ptrMulticastTxPdu */
            ptrMulticastTxPdu++;
            /* Decrement the counter */
            noOfRoutePdu--;
          }while (noOfRoutePdu != (uint8)PDUR_ZERO);

        } /* Multicast Transmission */
        else
        #endif /* #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON) */
        {
          #if(PDUR_IF_CANCEL_TRANSMIT_API_SUPPORT == STD_ON)
          /* Invoke Cancel transmit function */
          if(PduR_UpIfCancelTransmitService[ptrUpTransmit->FraTIOrNoOfRoute
                              & (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer
                              != NULL_PTR)
          {
            /* @Trace: PduR_SUD_API_032 */
            returnVal =
              PduR_UpIfCancelTransmitService[ptrUpTransmit->FraTIOrNoOfRoute
                                  & (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer
                                  (ptrUpTransmit->LoTargetPduId);
          }
          else
          #endif
          {
            returnVal = (Std_ReturnType)E_NOT_OK;
          }
        } /* End of else */
        #endif /*#if ((PDUR_IF_CANCEL_TRANSMIT_SUPPORT == STD_ON)*/
      }
      else
      #endif
      {
        #if (PDUR_TP_TRANSMIT == STD_ON)
        #if (PDUR_TP_CANCEL_TRANSMIT_SUPPORT == STD_ON)
        #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
        if ((uint8)PDUR_MULTICAST_MASK ==
            ((ptrUpTransmit->FraTIOrNoOfRoute) & ((uint8)PDUR_MULTICAST_MASK)))
        {
          /* @Trace: PduR_SUD_API_036 */
          /* Get the pointer to pMulticastPdu from PduR_UpTransmit */
          ptrMulticastTpPdu =
                           (P2CONST(PduR_MulticastTpPdu, AUTOMATIC, PDUR_CONST))
                             (ptrUpTransmit->MulticastTpOrTxPdu);
          /* Get the pointer to noOfRoutePdu from PduR_UpTransmit */
          noOfRoutePdu =
           (uint8)((ptrUpTransmit->FraTIOrNoOfRoute) & PDUR_TARGET_INDEX_MASK);
          /* Loop for all the destinations in case of multicast */
          /* @Trace: SRS_PduR_06125 */
          do
          {
            /* Invoke Cancel transmit frunction */
            if (PduR_UpTpCancellation[ptrMulticastTpPdu->TargetIndex] /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "Array index is valid due to data flow" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
              .TargetLayer != NULL_PTR)
            {
              /* @Trace: PduR_SUD_API_040 */
              returnVal = returnVal |
              PduR_UpTpCancellation[ptrMulticastTpPdu->TargetIndex]
              .TargetLayer(ptrMulticastTpPdu->TargetPduId);
            }
            else
            {
              /* @Trace: PduR_SUD_API_041 */
              returnVal = (Std_ReturnType)E_NOT_OK;
            }
            /* Decrement noOfRoutePdu */
            noOfRoutePdu--;
            /* Get the next ptrMulticastTpPdu */
            ptrMulticastTpPdu++;
          } while ((uint8)PDUR_ZERO != noOfRoutePdu);
        } /* Multicast Transmission */
        else
        #endif /* #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON) */
        { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
          /* Invoke Cancel transmit frunction */
          if (PduR_UpTpCancellation[ptrUpTransmit->FraTIOrNoOfRoute
                         &(uint8)PDUR_TARGET_INDEX_MASK].TargetLayer !=
                         NULL_PTR)
          {
            /* @Trace: PduR_SUD_API_037 */
            returnVal = PduR_UpTpCancellation
                           [ptrUpTransmit->FraTIOrNoOfRoute
                           &(uint8)PDUR_TARGET_INDEX_MASK].TargetLayer
                           (ptrUpTransmit->LoTargetPduId);
          }
          else
          {
            /* @Trace: PduR_SUD_API_038 */
            returnVal = (Std_ReturnType)E_NOT_OK;
          }
        } /* End of else */
        #endif /*#if(PDUR_TP_CANCEL_TRANSMIT_SUPPORT == STD_ON)*/
        #endif
      }
    }
    /* If the routing path for the requested I-PDU is disabled, then
     PduR_UpCancelTransmit shall return E_NOT_OK directly without any
     further action */
    #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
    else
    { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
    /* @Trace: PduR_SUD_API_030 */
      returnVal = (Std_ReturnType)E_NOT_OK;
    }
    #endif
  }
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No Action */
  }
  #endif
  #endif /* #if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON)) */
  return (returnVal);
} /* End of PduR_IfCancelTransmit(PduIdType txPduId) */
/* @Traceability END -- SRS: SWS_PduR_00119 SWS_PduR_00100 SWS_PduR_00722
                               SWS_PduR_00721 SWS_PduR_00700 SWS_PduR_00221
                               SWS_PduR_00723 SWS_PduR_00701 SWS_PduR_00724
                               SWS_PduR_00710 SWS_PduR_00287 SWS_PduR_00161
                               SWS_PduR_00328 SWS_PduR_00330 SWS_PduR_00717
                               SWS_PduR_00715 SWS_PduR_00769 SWS_PduR_00824
                               SWS_PduR_00025 SWS_PduR_00764 */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : PduR_DETCheckCancelTransmit                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The PDU Router shall translate the upper layer      **
**                        into the configured target PDU ID and route this    **
**                        cancel transmit request to the configured target    **
**                        TP module.                                          **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : PduIdType txPduId,                                  **
**                        uint8 moduleType                                    **
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
**                        PduR_InitStatus, PduR_UpTransmitMaxPduId            **
**                        PduR_UpTransmitConfig, PduR_UpIfTpTransmit          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if ((PDUR_IF_CANCEL_TRANSMIT_SUPPORT == STD_ON) ||\
  (PDUR_TP_CANCEL_TRANSMIT_SUPPORT == STD_ON))
#if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
 static FUNC(Std_ReturnType, PDUR_CODE) PduR_DETCheckCancelTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType txPduId, uint8 moduleType)
{
  P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) ptrUpTx;
  /* Initialize returnValue to E_OK */
  Std_ReturnType returnVal;
  /* Set return value to E_OK */
  returnVal = (Std_ReturnType)E_OK;
  /* Check whether the module is initialised */
  if (PDUR_UNINIT == PduR_InitStatus)
  {
    /* @Trace: SRS_BSW_00406 */
    /* @Trace: PduR_SUD_API_042 */
    /* Report to DET */
    (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
      PDUR_CANCEL_TRANSMIT_SID, PDUR_E_UNINIT);
    /* Set the return value to E_NOT_OK */
    returnVal = (Std_ReturnType)E_NOT_OK;
  } /* End of if (PDUR_UNINIT == PduR_InitStatus) */
  else
  {
    #if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
    ptrUpTx = &PduR_UpTransmitConfig[txPduId];
    /* @Trace: PduR_SUD_API_416 */
    if (txPduId >= PduR_UpTransmitMaxPduId)
    #else
    /* @Trace: PduR_SUD_API_112 */
    ptrUpTx = &PduR_UpIfTpTransmit[txPduId];
    if (txPduId >= PDUR_UP_MAXPDUID)
    #endif
    {
      /* Report to DET */
      /* @Trace: SRS_PduR_06103 */
      (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
        PDUR_CANCEL_TRANSMIT_SID, PDUR_E_PDU_ID_INVALID);
      /* Set the return value to E_NOT_OK */
      returnVal = (Std_ReturnType)E_NOT_OK;
    } /* End of if (txPduId >= PduR_GulUpMaxPduId) */
    else
    {
      if (ptrUpTx->ModuleType != moduleType) /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:IDP [Not a defect:Low] "configured memory access index" */
      {
        /* Report to DET */
        /* @Trace: SRS_PduR_06103 */
        /* @Trace: PduR_SUD_API_043 */
        (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID,
          PDUR_CANCEL_TRANSMIT_SID, PDUR_E_PDU_ID_INVALID);
        /* Set the return value to E_NOT_OK */
        returnVal = (Std_ReturnType)E_NOT_OK;
      } /* (ptrUpTx->ModuleType != moduleType) */
      else
      {
        /* No Action */
      }
    } /* Return Std Return Value*/
  } /* Return Std Return Value*/
  return (returnVal);
} /* End Of PduR_DETCheckIfCancelTransmit(
   * PduIdType txPduId, uint8 moduleType)*/
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
#endif
#endif
/*******************************************************************************
** Function Name        : PduR_IfTransmit                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The PDU Router shall translate the upper layer      **
**                        into the configured target PDU ID and route this    **
**                        cancel transmit request to the configured target    **
**                        IF layer module.                                    **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : PduR_UpTx *ptrUpTransmit, PduInfoType *ptrPduInfoPtr**
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
**                        PduR_IfTransmitService,                             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_PduR_TP_TX_PROTECTION_AREA()             **
**                        SchM_Exit_PduR_TP_TX_PROTECTION_AREA()              **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_IF_TRANSMIT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_IfTransmit( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) ptrUpTransmit,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr)
{
  #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
  P2CONST(PduR_MulticastTxPdu, AUTOMATIC, PDUR_CONST) ptrMulticastTxPdu;
  P2VAR(PduR_MulticastTxInfo, AUTOMATIC, PDUR_VAR) ptrMulticastTxInfo;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif
  #endif
  Std_ReturnType returnVal;
  #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
  uint8 noOfRoutePdu;
  #endif
  /* Initialize returnValue to E_OK */
  returnVal = (Std_ReturnType)E_NOT_OK;
  #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON)
  if ((uint8)PDUR_MULTICAST_MASK ==
          ((ptrUpTransmit->FraTIOrNoOfRoute) & ((uint8)PDUR_MULTICAST_MASK)))
  {
    /* Get ptrMulticastTxPdu to local pointer */
    ptrMulticastTxPdu = (P2CONST(PduR_MulticastTxPdu, AUTOMATIC, PDUR_CONST))
                          (ptrUpTransmit->MulticastTpOrTxPdu);
    /*Get the pointer to ptrMulticastTpInfo from PduR_MulticastTpPdu*/
    ptrMulticastTxInfo = (ptrMulticastTxPdu->MulticastTxInfo);
    /* Get the local variable to ucNoOfRoutePdu */
    noOfRoutePdu = (uint8)((ptrUpTransmit->FraTIOrNoOfRoute) &
                        PDUR_TARGET_INDEX_MASK);
    #if (PDUR_LO_TXCONFIRMATION == STD_ON)
    /* @Trace: SRS_BSW_00312 */
    /* Disable relevant interrupts */
    SchM_Enter_PduR_TP_TX_PROTECTION_AREA();
    /* Set the mask for Transmit status bit based on Tx Module */
    ptrMulticastTxInfo->ConfStatus |= ptrUpTransmit->TxConfirmMask; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
    /* Store the result as Buffer OK */
    ptrMulticastTxInfo->Result = (Std_ReturnType)E_NOT_OK;
    /* Enable relevant interrupts */
    SchM_Exit_PduR_TP_TX_PROTECTION_AREA();
    #endif /* End of if (PDUR_LO_TXCONFIRMATION == STD_ON) */
    /* Multicast Transmission */
    /* @Trace: SRS_PduR_06030 */
    /* @Trace: SRS_PduR_06125 */
    do
    {
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      /* Get the group mask value */
      groupIdValue = ptrMulticastTxPdu->GroupMaskValue;
      indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
      idConvert = groupIdValue % PDUR_BITMASK_UINT8;
      /* @Trace: SRS_PduR_06120 */
      /* Check if routing path is enabled */
      if ((PDUR_UNDEFINED == groupIdValue) ||
        ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] &
                                          (((uint32)PDUR_ONE) << idConvert))))
      #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
      {
        /* Invoke <Lo>IfTransmit API with TargePduId and ptrPduInfoPtr */
        if (PduR_IfTransmitService[ptrMulticastTxPdu->TargetIndex].TargetLayer /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "Array index is valid due to data flow" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
          != NULL_PTR)
        {
          /* @Trace: SRS_PduR_06104 */
          /* @Trace: PduR_SUD_API_023 */
          returnVal = returnVal &
            PduR_IfTransmitService[ptrMulticastTxPdu->TargetIndex].
            TargetLayer(ptrMulticastTxPdu->TargetPduId, ptrPduInfoPtr);
        }
        else
        {
          /* Action */
        }
      }
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      else
      {
        /* Action */
      }
      #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
          /* @Trace: PduR_SUD_API_024 */
      /* Get the pointer to next Tx Pdu */
      ptrMulticastTxPdu++;
      noOfRoutePdu--;
    /* Check whether NoOfRoutePdu is not equal to zero */
    } while(noOfRoutePdu != (uint8)PDUR_ZERO);
  }
  else
  #endif /* #if (PDUR_MULTICAST_TOTXIF_SUPPORT == STD_ON) */
  /* Singlecast Transmission */
  { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
    /* Invoke <Lo>IfTransmit API with TargePduId and ptrPduInfoPtr */
    if(PduR_IfTransmitService[ptrUpTransmit->FraTIOrNoOfRoute].TargetLayer !=
      NULL_PTR)
    {
      /* @Trace: SRS_PduR_06104 */
      /* @Trace: PduR_SUD_API_021 */
      returnVal =
        PduR_IfTransmitService[ptrUpTransmit->FraTIOrNoOfRoute].
        TargetLayer(ptrUpTransmit->LoTargetPduId, ptrPduInfoPtr);
    }
    else
    { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
      /* Action */
    }
  }
  return (returnVal);
} /* End of PduR_IfCancelTransmit(PduIdType txPduId) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Function Name        : PduR_TpTransmit                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The PDU Router shall translate the upper layer      **
**                        into the configured target PDU ID and route this    **
**                        cancel transmit request to the configured target    **
**                        Tp layer module.                                    **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : PduR_UpTx ptrUpTransmit, PduInfoType ptrPduInfoPtr  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType returnAllVal                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        PduR_TpTransmitService,                             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        SchM_Enter_PduR_TP_TX_PROTECTION_AREA(),            **
**                        SchM_Exit_PduR_TP_TX_PROTECTION_AREA(),             **
**                                                                            **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TRANSMIT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, PDUR_CODE) PduR_TpTransmit
(P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) ptrUpTransmit,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr)
{
  #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
  P2CONST(PduR_MulticastTpPdu, AUTOMATIC, PDUR_CONST) ptrMulticastTpPdu;
  P2VAR(PduR_MulticastTpInfo, AUTOMATIC, PDUR_VAR) ptrMulticastTpInfo;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 groupIdValue;
  uint16 indexBitmask;
  uint16 idConvert;
  #endif
  #endif
  Std_ReturnType returnAllVal;
  /* Assign returnVal with E_OK */
  returnAllVal = (Std_ReturnType)E_NOT_OK;
  #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
  uint8 noOfRoutePdu;
  Std_ReturnType returnVal;
  /* Check if multicast transmission */
  if ((uint8)PDUR_MULTICAST_MASK ==
            ((ptrUpTransmit->FraTIOrNoOfRoute) & ((uint8)PDUR_MULTICAST_MASK)))
  {
    /* Get the pointer to ptrMulticastTpPdu from PduR_UpTransmit */
    ptrMulticastTpPdu = (P2CONST(PduR_MulticastTpPdu, AUTOMATIC, PDUR_CONST))
                                          (ptrUpTransmit->MulticastTpOrTxPdu);
    /*Get the pointer to ptrMulticastTpInfo from PduR_MulticastTpPdu*/
    ptrMulticastTpInfo = (ptrMulticastTpPdu->MulticastTpInfo);
    /* Get the number of routing path */
    noOfRoutePdu =
      (uint8)((ptrUpTransmit->FraTIOrNoOfRoute) & PDUR_TARGET_INDEX_MASK);
    /* @Trace: SRS_BSW_00312 */
    /* Disable relevant interrupts */
    SchM_Enter_PduR_TP_TX_PROTECTION_AREA();
    /* Store the result as Buffer OK */
    ptrMulticastTpInfo->Result = (Std_ReturnType)E_NOT_OK; /* polyspace RTE:IDP [Not a defect:Unset] "configured memory access index" */ /* polyspace RTE:IDP [Not a defect:Low] "configured memory access index" */
    /* Set variable for detect first destination lower to default */
    ptrMulticastTpInfo->FirstLower = (boolean)PDUR_TRUE;
    /* Enable relevant interrupts */
    SchM_Exit_PduR_TP_TX_PROTECTION_AREA();
    /* Multicast Transmission */
    /* @Trace: SRS_PduR_06029 */
    /* @Trace: SRS_PduR_06125 */
    do
    {
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      /* Get the group mask value */
      groupIdValue = ptrMulticastTpPdu->GroupMaskValue;
      indexBitmask = groupIdValue / PDUR_BITMASK_UINT8;
      idConvert = groupIdValue % PDUR_BITMASK_UINT8;
      /* @Trace: SRS_PduR_06120 */
      /* Check if routing path is enabled */
      if ((PDUR_UNDEFINED == groupIdValue) ||
        ((uint32)PDUR_ZERO != (PduR_GroupPathId[indexBitmask] &
                                          (((uint32)PDUR_ONE) << idConvert))))
      #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
      {
        #if (PDUR_TP_TXCONFIRMATION == STD_ON)
        /* Invoke <Lo>TpTransmit API with TargePduId and PduInfoPtr */
        if (PduR_TpTransmitService[ptrMulticastTpPdu->TargetIndex].TargetLayer /* polyspace MISRA-C:2012 D4.1 18.1 [Not a defect:Low] "Array index is valid due to data flow" */ /* polyspace RTE:OBAI [Not a defect:Unset] "configured memory access index" */
          != NULL_PTR)
        {
          /* @Trace: SRS_PduR_06104 */
          returnVal = PduR_TpTransmitService[ptrMulticastTpPdu->TargetIndex].
            TargetLayer(ptrMulticastTpPdu->TargetPduId, ptrPduInfoPtr);
          if ((Std_ReturnType)E_OK == returnVal)
          {
            /* @Trace: PduR_SUD_API_027 */
            /* Set the confirmation status */
            ptrMulticastTpInfo->ConfStatus |= /* polyspace RTE:NIV [Not a defect:Unset] "initialized variable" */
                              (uint8)(ptrMulticastTpPdu->TpConfirmMask);
            /* Set return transmission multicast successful */
            returnAllVal = (Std_ReturnType)E_OK;
          }
          else
          {
            /* No Action */
          }
        }
        else
        #endif /* #if (PDUR_TP_TXCONFIRMATION == STD_ON) */
        {
          /* No Action */
        }
      }
      #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
      else
      {
        /* No Action */
      }
      #endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
      /* @Trace: PduR_SUD_API_028 */
      /* Get the next ptrMulticastTpPdu */
      ptrMulticastTpPdu++;
      /* MISRA Rule   : 17.4.
       *   Message      : Increment or decrement operation
       *                  performed on the pointer
       *   Reason       : Increment operator used
       *                  to achieve better throughput.
       *   Verification : However, part of the code
       *                  is verified manually and
       *                  it is not having any impact.
       */
      /* Decrement the counter by one count */
      noOfRoutePdu--;
    /* Check whether NoOfRoutePdu is not equal to zero */
    } while ((uint8)PDUR_ZERO != noOfRoutePdu);
  }
  else
  #endif /* #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON) */
    /* Singlecast Transmission */
  { /* polyspace RTE:UNR [Not a defect:Low] "this issue is covered by unit test" */
    #if (PDUR_TP_TXCONFIRMATION == STD_ON)
    /* Invoke Tp transmit function */
    if (PduR_TpTransmitService[ptrUpTransmit->FraTIOrNoOfRoute &
                            (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer !=
                            NULL_PTR)
    {
      /* @Trace: SRS_PduR_06104 */
      /* @Trace: PduR_SUD_API_025 */
      returnAllVal =
        PduR_TpTransmitService[ptrUpTransmit->FraTIOrNoOfRoute &
                              (uint8)PDUR_TARGET_INDEX_MASK].TargetLayer
          (ptrUpTransmit->LoTargetPduId, ptrPduInfoPtr);
    }
    else
    #endif
    {
      /* No Action */
    }
  }
  return (returnAllVal);
} /* End of PduR_TpTransmit
(P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) ptrUpTransmit,
P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr) */
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/* polyspace:end<MISRA-C:17.4:Not a defect:Justify with annotations> Not a defect, Decrement and Increment operator is used to achieve better throughput */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
/* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > configured memory access index */
/* polyspace:end<RTE: COR : Not a defect : No Action Planned > masked value is generated based on configuration, masking value is defined for dividing configured functionality. function pointer is verified before ivoking */
/* polyspace:end<RTE: NIV : Not a defect : Justify with annotations > initialized variable */
/* polyspace:end<RTE: NIP : Not a defect : Justify with annotations > pointer is not null */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
