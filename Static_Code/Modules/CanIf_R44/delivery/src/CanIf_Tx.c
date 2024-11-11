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
**  SRC-MODULE: CanIf_Tx.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of Transmit and Queue Functionality                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
*******************************************************************************/
/*******************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0     23-Feb-2024   Jh Yang        #CP44-2947                          **
** 1.0.15    05-Jan-2024   JH Jang        #CP44-2840, #CP44-2848              **
** 1.0.14    13-Jun-2023   HieuTM8        #CP44-2236                          **
** 1.0.12    12-Dec-2022   HieuTM8        #CP44-1254                          **
** 1.0.10    27-Oct-2022   HieuTM8        #CP44-1008                          **
** 1.0.9     03-Oct-2022   HieuTM8        #CP44-832, #CP44-896                **
** 1.0.7     21-Aug-2022   Jiwon Oh       #CP44-751                           **
** 1.0.6     25-Jul-2022   HieuTM8        #CP44-444                           **
** 1.0.5     30-Jun-2022   HieuTM8        #CP44-130, #CP44-444                **
** 1.0.4     09-May-2022   Jiwon Oh       #26814,#27128                       **
** 1.0.3     29-Apr-2022   HieuTM8        #26257, #26442                      **
** 1.0.1  	 22-Sep-2021   HieuTM8        #20891,#19106                       **
** 1.0.0.3	 23-Aug-2021   HieuTM8        #19470, #19526                      **
** 1.0.0  	 21-Dec-2020   SJ Kim         Initialization                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"               /* Module header file */
#include "CanIf_Ram.h"           /* Module RAM header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#include "CanIf_Tx.h"            /* Transmit header file */
#include "CanIf_TxConfirm.h"     /* Tx Confirmation header file */
#if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
#include "string.h"              /* memcpy() */
#endif
#if (STD_ON == CANIF_PDUR_CALLBACK)
#include "PduR_CanIf.h"          /* Call-back PduR header file */
#endif
#if (STD_ON == CANIF_CANTP_CALLBACK)
#include "CanTp.h"           /* Call-back CanTp header file */
#endif
#if (STD_ON == CANIF_CANNM_CALLBACK)
#include "CanNm.h"           /* Call-back CanNm header file */
#endif
#if (STD_ON == CANIF_OSEKNM_CALLBACK)
#include "OsekNm.h"           /* Call-back OsekNm header file */
#endif
#include "SchM_CanIf.h"          /* SchM CanIf Header file */

#include "CanIf_Error.h"         /* Det File Check */

#if (STD_ON == CANIF_TX_XCP_CALLBACK)
#include "Xcp.h"             /* Call-back XCP header file */
#endif
#if (STD_ON == CANIF_TX_J1939TP_CALLBACK)
#include "J1939Tp.h"         /* Call-back J1939Tp header file */
#endif
#include "CanIf_UserInc.h"       /* User included header file */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANIF_TX_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_TX_C_AR_RELEASE_MINOR_VERSION    4
#define CANIF_TX_C_AR_RELEASE_REVISION_VERSION 0

/* File version information */
#define CANIF_TX_C_SW_MAJOR_VERSION       1
#define CANIF_TX_C_SW_MINOR_VERSION       1
#define CANIF_TX_C_SW_REVISION_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_TX_AR_RELEASE_MAJOR_VERSION != \
  CANIF_TX_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_TX.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_TX_AR_RELEASE_MINOR_VERSION != \
  CANIF_TX_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_TX.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_TX_AR_RELEASE_REVISION_VERSION != \
  CANIF_TX_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_TX.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_TX_SW_MAJOR_VERSION != CANIF_TX_C_SW_MAJOR_VERSION)
  #error "CANIF_TX.c : Mismatch in Software Major Version"
#endif
#if (CANIF_TX_SW_MINOR_VERSION != CANIF_TX_C_SW_MINOR_VERSION)
  #error "CANIF_TX.c : Mismatch in Software Minor Version"
#endif

/* polyspace-begin RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */  
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanIf_Transmit                                      **
**                                                                            **
** Service ID           : 0x49                                                **
**                                                                            **
** Description          : This service initiates a request for transmission of**
**                        the CAN L-PDU specified by the CanTxPduId and CAN   **
**                        related data in the L-PDU structure                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds. Non reentrant       **
**                        for the same PduId.                                 **
**                                                                            **
** Input Parameters     : TxPduId, PduInfoPtr                                 **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_CanIfStatus,              **
**                                            CanIf_TxLpdu,                   **
**                                            CanIf_Controller                **
**                                            CanIf_TxPduInfoPtr              **
**                                                                            **
**                        Function(s) invoked:                                **
**                                            CanIf_DETTransmit,              **
**                                            CanIf_CheckHthType,             **
**                                            CanIf_TxNotification            **
**                                                                            **
*******************************************************************************/
#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01008 SRS_Can_01114 SRS_Can_01126 SRS_Can_01020 SRS_Can_01061 SRS_Can_01153 SRS_CanIf_ES96560_01E_00001 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_Transmit (
                   VAR(PduIdType, CANIF_VAR) TxPduId,
                   P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr)
{
  /* @Trace: SWS_CANIF_00005 */
  /* @Trace: SWS_CANIF_00058 */
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  VAR(uint8, CANIF_VAR) txStatus;

  #if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) ptrPduInfoUpdate;
  #endif

  /* Invoke the CanIf_DETTransmit to check the errors in the parameters and report to DET */
  retVal = CanIf_DETTransmit (TxPduId, PduInfoPtr);

  if ((uint8) E_OK == retVal)
  {
    /* @Trace: CanIf_SUD_API_285 */
    /* Get the pointer to Tx Lpdu */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrTxLpdu = &CanIfTxLpdu[TxPduId];
    #else
    ptrTxLpdu = &CanIf_TxLpdu[TxPduId];
    #endif

    #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
    /* Get the pointer to controller */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    ptrController = &CanIf_Controller[ptrTxLpdu->ControllerId];
    #else
    ptrController = &CanIf_Controller[CANIF_ZERO];
    #endif

    /* @Trace: SWS_CANIF_00904 SWS_CANIF_00905 */
    /* @Trace: CanIf_SUD_API_008 */
    #if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
    /* polyspace +8 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    if(TRUE == ptrController->MirroringActive)
    {
      /* @Trace: CanIf_SUD_API_286 */
      /* Get the respective PduPtr into local pointer */
      ptrPduInfoUpdate = &CanIf_TxPduInfoPtr[TxPduId];

      /* Update length for Pdu in real transmission*/
      /* polyspace +2 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
      /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "SudLength checked by Det"*/
      ptrPduInfoUpdate->SduLength = PduInfoPtr->SduLength;

      if(NULL_PTR != PduInfoPtr->SduDataPtr)
      {
        /* @Trace: CanIf_SUD_API_287 */
        /* enter critical area */
        SchM_Enter_CanIf_TX_NOTIFSTATUS_PROTECTION();

        /* Update Sdu in real transmission*/
        /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "Its boundary is pre-defined" */
        memcpy((P2VAR(void, AUTOMATIC, CANIF_VAR))(ptrPduInfoUpdate->SduDataPtr), \
         (P2CONST(void, AUTOMATIC, CANIF_CONST))(PduInfoPtr->SduDataPtr), ptrPduInfoUpdate->SduLength);

        /* exit critical area */
        SchM_Exit_CanIf_TX_NOTIFSTATUS_PROTECTION();
      }
      else
      {
        /*In case PduInfoPtr->SduDataPtr is Null, Sdu will be stored in TxConfirmation Api */
        /*Do nothing*/
      }
    }
    else
    {
    	/* Do nothing */
    }
    #endif
    /* get the Tx status into local variable */
    txStatus = (uint8)CANIF_TX_STATUS(ptrController->PduMode);

    /*Is any DET error is detected*/
    if (
    #if (STD_ON == CANIF_CANCM_SUPPORT)
        (CANIF_TX_BAT_NORMAL == ptrController->BatVolStatus) &&
    #endif
        ((CANIF_TX_ENABLED == txStatus)
    /* @Trace: SWS_CANIF_00072 */
    #if (STD_ON == CANIF_TX_OFFLINE_ACTIVE_SUPPORT)
      || ((uint8)CANIF_TX_OFFLINE_ACTIVE == txStatus)
    #endif
    ))
    {
      /* @Trace: SWS_CANIF_00072 */  
      /* @Trace: CanIf_SUD_API_009 */  
      #if (STD_ON == CANIF_TX_OFFLINE_ACTIVE_SUPPORT)
      /* Check if current status is CANIF_TX_OFFLINE_ACTIVE */
      if ((uint8)CANIF_TX_OFFLINE_ACTIVE == txStatus)
      {
        /* @Trace: CanIf_SUD_API_288 */
        /* Invoke CanIf_TxNotification */
        CanIf_TxNotification(ptrTxLpdu, E_OK);

        /* return status as E_OK */
      }/*if (CANIF_TX_OFFLINE_ACTIVE == txStatus)*/
      else/* Status is active */
      #endif
      {
        #if (STD_ON == CANIF_PN_SUPPORT)
        /* Check whether Partial Networking status is enabled */
        if (CANIF_IS_TX_PNENABLED(ptrController->PduMode) &&
           ((uint8)CANIF_BLOCK != ((ptrTxLpdu->HTHTypeOrTXPN) &
           (uint8)CANIF_TX_PN_MASK)))
           /* CANIF_PN_STATUS_MASK = 0x10 */
           /* CANIF_BLOCK = 0x10 */
        {
          /* @Trace: CanIf_SUD_API_289 */
          /* Set the return value to  E_NOT_OK*/
          retVal = (uint8)E_NOT_OK;
        }
        else
        #endif
        {
          /* @Trace: CanIf_SUD_API_290 */
          CANIF_UNUSED(ptrTxLpdu);
          retVal = CanIf_CheckHthType(TxPduId,PduInfoPtr);		    
        } /* Status is active to transmit message */
      } /* @ else -> if (CANIF_TX_OFFLINE_ACTIVE == txStatus) */
    }
    else /* @ if (((txStatus == CANIF_TX_ENABLED) || (txStatus == CANIF_TX_OFFLINE_ACTIVE))) */
    {
      /* @Trace: CanIf_SUD_API_291 */
      retVal = (uint8)E_NOT_OK;
    }
  }/* @ if (((uint8) E_OK == retVal) */
  return(retVal);
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_CheckQueueStatus                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates a request for transmission of**
**                        the CAN L-PDU specified by the CanTxPduId and CAN   **
**                        related data in the L-PDU structure                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrTxBuffer                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : QueueIndex                                          **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s) : CanIf_TxQueue                  **
**                        Function(s) invoked: None                           **
*******************************************************************************/
#if ((STD_ON == CANIF_BASIC_CAN_TXPDU) && (STD_ON == CANIF_TX_QUEUE))	
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(CanIf_TxQueueSizeType, CANIF_CODE) CanIf_CheckQueueStatus (
                P2CONST(CanIf_TxBufferType, AUTOMATIC, CANIF_CONST)ptrTxBuffer)
{
  P2VAR(CanIf_TxQueueType, AUTOMATIC, CANIF_VAR) ptrTxNextQueue;
  VAR(CanIf_TxQueueSizeType, CANIF_VAR) noOfTxQueue;
  VAR(CanIf_TxQueueSizeType, CANIF_VAR) txQueueId;
  VAR(boolean, CANIF_VAR) freeQueue;

  /* Set freeQueue to CANIF_FALSE */
  freeQueue = CANIF_FALSE;

  /* Get the pointer to first queue index */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
  ptrTxNextQueue = &(CanIf_TxQueue[ptrTxBuffer->QueueIndex]);

  /* Get the number of Tx Queue associated with this buffer */
  noOfTxQueue = ptrTxBuffer->NoOfTxQueue;

  /*Get the appropriate queue Id */
  txQueueId = noOfTxQueue + ptrTxBuffer->QueueIndex;

  do
  {
    /* Check the queue status ->availability */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */  
    if ((uint8)CANIF_ZERO == ptrTxNextQueue->Dlc)
    {
      /* @Trace: CanIf_SUD_API_292 */
      /* Marking the queue as occupied */
      ptrTxNextQueue->Dlc = CANIF_TXQUEUE_OCCUPIED;

      /* Get the correct Queue Id*/
      txQueueId = txQueueId - noOfTxQueue;

      /* to break the loop */
      noOfTxQueue = (CanIf_TxQueueSizeType)CANIF_ZERO;

      /* Set the freeQueue status to CANIF_TRUE*/
      freeQueue = CANIF_TRUE;
    }
    else
    {
      /* @Trace: CanIf_SUD_API_293 */
      /* shift to next queue location */
      ptrTxNextQueue++;

      /* Reduce the number of available TX Queue */
      noOfTxQueue--;
    }
  } while ((CanIf_TxQueueSizeType)CANIF_ZERO != noOfTxQueue);

  if (CANIF_FALSE == freeQueue)
  {
    /* @Trace: CanIf_SUD_API_294 */
    /*Reset TxQueueId to 0x255 to indicate that the queue is available*/
    txQueueId = CANIF_INVALID_TXQUEUE;
  }
  else
  {
  	/* Do nothing */
  }
  return (txQueueId);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : CanIf_IsInQueue                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service indicate if a request for transmission **
**                        of the CAN L-PDU has been stored in Tx queue        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrTxBuffer                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : isInQueue (CANIF_FALSE/CANIF_TRUE)                  **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_TxBuffCon                 **
**                        Function(s) invoked: None                           **
*******************************************************************************/
#if ((STD_ON == CANIF_BASIC_CAN_TXPDU) && (STD_ON == CANIF_TX_QUEUE))	
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, CANIF_CODE) CanIf_IsInQueue (
                      P2CONST(CanIf_TxBufferType, AUTOMATIC, CANIF_CONST)ptrTxBuffer,
                      P2CONST(Can_PduType, AUTOMATIC, CANIF_CONST) CanPduInfo)
{
  P2VAR(CanIf_TxQueueType, AUTOMATIC, CANIF_VAR) ptrTxNextQueue;
  VAR(CanIf_TxQueueSizeType, CANIF_VAR) noOfTxQueue;
  VAR(boolean, CANIF_VAR) isInQueue;
  /* polyspace +3 RTE:IDP [Not a defect:Low] "pointer is predefined, not null" */
  /* Set freeQueue to CANIF_FALSE */
  isInQueue = CANIF_FALSE;
  if (CANIF_NO_OF_TXQUEUE > ptrTxBuffer->QueueIndex)
  {
    /* @Trace: CanIf_SUD_API_295 */
    /* Get the pointer to first queue index */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    ptrTxNextQueue = &(CanIf_TxQueue[ptrTxBuffer->QueueIndex]);
    /* Get the number of Tx Queue associated with this buffer */
    noOfTxQueue = ptrTxBuffer->NoOfTxQueue;
    do
    {
      /* Check the queue status -> has data */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
      if ((uint8) CANIF_ZERO != ptrTxNextQueue->Dlc)
      {
        if ((ptrTxNextQueue->CanId == CanPduInfo->id) &&
            (ptrTxNextQueue->TxLPduId == CanPduInfo->swPduHandle) &&
            (ptrTxNextQueue->Dlc == CanPduInfo->length)) 
        {
          /* @Trace: CanIf_SUD_API_296 */
          /* to break the loop */
          noOfTxQueue = (CanIf_TxQueueSizeType) CANIF_ZERO;

          /* Set the isInQueue status to CANIF_TRUE*/
          isInQueue = CANIF_TRUE;
        }
        else
        {
          /* Do nothing */
        }
      }
      else
      {
        /* @Trace: CanIf_SUD_API_297 */
        /* shift to next queue location */
        ptrTxNextQueue++;

        /* Reduce the number of available TX Queue */
        noOfTxQueue--;
      }
    } while ((CanIf_TxQueueSizeType) CANIF_ZERO != noOfTxQueue);
  }
  return (isInQueue);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : CanIf_TxQueueHandling                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates a request for transmission of**
**                        the CAN L-PDU specified by the CanTxPduId and CAN   **
**                        related data in the L-PDU structure                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrBuffer, index                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : None                                                **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_TxQueue                   **
**                        Function(s) invoked: None                           **
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
#if ((STD_ON == CANIF_BASIC_CAN_TXPDU) && (STD_ON == CANIF_TX_QUEUE))	
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_TxQueueHandling (
                P2CONST(CanIf_TxBufferType, AUTOMATIC, CANIF_CONST) ptrTxBuffer,
                VAR(CanIf_TxQueueSizeType, CANIF_VAR) txQueueId)
{
  P2VAR(CanIf_TxQueueType, AUTOMATIC, CANIF_VAR) ptrTxPrevQueue;
  P2VAR(CanIf_TxQueueType, AUTOMATIC, CANIF_VAR) ptrTxQueue;
  P2VAR(CanIf_TxQueueType, AUTOMATIC, CANIF_VAR) ptrTxCurrentQueue;

  /* Get the pointer to Tx Queue */
  ptrTxQueue = &(CanIf_TxQueue[txQueueId]);

  /* Get the current pointer to Tx Queue */
  /* polyspace +1 RTE:NIP [Not a defect:Low] "Value is defined when function is called" */
  ptrTxCurrentQueue = *ptrTxBuffer->TxFirstQueue;

  /* Check for free queue */
  if (NULL_PTR == ptrTxCurrentQueue)
  {
    /* @Trace: CanIf_SUD_API_298 */
    /* update the next queue index to invalid */
    ptrTxQueue->TxNextQueue = NULL_PTR;

    /* Update head entry */
    *ptrTxBuffer->TxFirstQueue = ptrTxQueue;
  }
  else
  {
    /* @Trace: CanIf_SUD_API_299 */
    /* Make the pointer to NULL Pointer */
    ptrTxPrevQueue = NULL_PTR;

    /* Check the insertion point */
    /* polyspace +4 MISRA2012:18.1 [Not a defect:Low] "Value is redefined " */
    /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "Value is redefined " */
    /* polyspace +2 RTE:NIV [Not a defect:Low] "Value is redefined " */
    while ((NULL_PTR != ptrTxCurrentQueue) &&
        (ptrTxCurrentQueue->CanId <= ptrTxQueue->CanId))
    {
      /* @Trace: CanIf_SUD_API_300 */
      /* Set the current queue to previous queue*/
      ptrTxPrevQueue = ptrTxCurrentQueue;

      /* get the pointer to the next queue as current queue*/
      /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "Value is defined in ptrTxBuffer " */
      /* polyspace +1 RTE:NIP [Not a defect:Low] "Value is defined in ptrTxBuffer " */
      ptrTxCurrentQueue = ptrTxCurrentQueue->TxNextQueue;
    }
    /* Store the current queue pointer to next queue pointer */
    ptrTxQueue->TxNextQueue = ptrTxCurrentQueue;

    /* Check if the precious queue is a null pointer or not*/
    if (NULL_PTR != ptrTxPrevQueue)
    {
      /* @Trace: CanIf_SUD_API_301 */
      /*Store the ptrTxQueue as the next queue */
      ptrTxPrevQueue->TxNextQueue = ptrTxQueue;
    }
    else
    {
      /* @Trace: CanIf_SUD_API_302 */
      /* Update head entry */
      *ptrTxBuffer->TxFirstQueue = ptrTxQueue;
    }/*(NULL_PTR != ptrTxPrevQueue)*/
  }
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* polyspace-end RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
/*******************************************************************************
** Function Name        : CanIf_SetDynamicTxId                                **
**                                                                            **
** Service ID           : 0x0C                                                **
**                                                                            **
** Description          : This service re-configures the corresponding CAN    **
**                        identifier of the requested CAN L-PDU.              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : CanIfTxSduId, CanId                                 **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : The function may not be interrupted by              **
**                        CanIf_Transmit(), if the same L-PDU ID is handled.  **
**                        The CAN Interface must be initialized after         **
**                        POWER ON.                                           **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanIf_TxLpdu, CanIf_CanIfStatus,                    **
**                        CanIf_CanId                                         **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Det_ReportError, CANIF_STD_CANID_ERROR,             **
**                        SchM_Enter_CanIf_TX_DYNCANID_PROTECTION,            **
**                        SchM_Exit_CanIf_TX_DYNCANID_PROTECTION              **
*******************************************************************************/
#if ((STD_ON == CANIF_TX_LPDU) && (STD_ON == CANIF_SETDYNAMICTXID_API))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 */
FUNC(void, CANIF_CODE)CanIf_SetDynamicTxId (
                                       VAR(PduIdType, CANIF_VAR) CanIfTxSduId,
                                       VAR(Can_IdType, CANIF_VAR) CanId)
{
  /* @Trace: CanIf_SUD_API_061 */
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  retVal = (uint8) E_OK;

  /* Report to DET, if module is not initialized */
  /* @Trace: CanIf_SUD_API_057 */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_SET_DYNAMIC_TXID_SID, retVal);

  /* @Trace: CanIf_SUD_API_058 */
  /* Report to DET, if CanTxPduId is out of range */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  if (CanIfTxSduId >= (PduIdType)CanIf_NoofTxLpdu) 
  #else
  if (CanIfTxSduId >= CANIF_NO_OF_TXLPDU) 
  #endif
  {
    /* @Trace: CanIf_SUD_API_303 */              
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_SET_DYNAMIC_TXID_SID,  
            CANIF_E_INVALID_TXPDUID);                          
    (retVal) = (uint8)E_NOT_OK;                                              
  }
  #endif
  /* Get the pointer to Tx L-PDU structure */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  ptrTxLpdu = &CanIfTxLpdu[CanIfTxSduId];
  #else
  ptrTxLpdu = &CanIf_TxLpdu[CanIfTxSduId];
  #endif

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Is any DET error Invoked */
  if ((uint8) E_OK == retVal)
  {
    /* Check the CAN-ID type of Tx L-PDU */
    /* polyspace +3 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */  
    if ((CANIF_STANDARD_CANID_TYPE == (ptrTxLpdu->CanIdType))
    #if (STD_ON == CANIF_CANFD_SUPPORT)
      || (CANIF_CANFD_STANDARD_CANID_TYPE == (ptrTxLpdu->CanIdType))
    #endif
    )
    {
      /* @Trace: CanIf_SUD_API_059 */
      /* Report to DET, If requested CAN-ID value is out of range */
      CANIF_STD_CANID_ERROR(CANIF_SET_DYNAMIC_TXID_SID, retVal);
    } 
    else /* not Standard CAN-ID; Extended CAN ID */
    {
      /* @Trace: CanIf_SUD_API_059 */
      /* Report to DET, if requested CAN-ID value is out of range */
      CANIF_EXTD_CANID_ERROR(CANIF_SET_DYNAMIC_TXID_SID, retVal);
      
    }/* @ if (CANIF_STANDARD_CANID_TYPE == (ptrTxLpdu->CanIdType)) */
  }
  else /* @ if ((uint8) E_OK == retVal) */
  {
  	/* Do nothing */
  }
  /* Check whether any development error occurred */
  if ((uint8) E_OK == retVal)
  #endif /* #if  (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* Disable relevant interrupts to protect dynamic CAN-ID */
    SchM_Enter_CanIf_TX_DYNCANID_PROTECTION();

    /* Store the requested CAN ID */
    /* @Trace: CanIf_SUD_API_060 */
    /* polyspace +6 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    if (ptrTxLpdu->DynCanIdIndex != CANIF_INVALID_DYNCANID)
    {
      /* @Trace: CanIf_SUD_API_304 */
      #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
      CanIfCanId[ptrTxLpdu->DynCanIdIndex] = CanId;
      #else
      CanIf_CanId[ptrTxLpdu->DynCanIdIndex] = CanId;
      #endif
    }
    else
    {
      /* Do nothing */
    }
    /* Enable relevant interrupts */
    SchM_Exit_CanIf_TX_DYNCANID_PROTECTION();
  } /* Check whether any development error occurred */
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_ClearTxQueue                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service clears the queue status bit for all    **
**                        the for that controller.                            **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant but not for same controller.             **
**                                                                            **
** Input Parameters     : ptrController                                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_TxBasicPduIndexMapping    **
**                                                                            **
**                        Function(s) invoked: None                           **
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
#if ((STD_ON == CANIF_BASIC_CAN_TXPDU) && (STD_ON == CANIF_TX_QUEUE))	
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_ClearTxQueue (
 P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController)
{
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  VAR(CanIf_TxPduIdType, CANIF_VAR) noOfTxPdu;
  VAR(CanIf_TxQueueSizeType, CANIF_VAR) txQueueIndex;
  VAR(CanIf_TxQueueSizeType, CANIF_VAR) txQueueId;

  /* Get the Number of TxPdu */
  noOfTxPdu = (CanIf_TxPduIdType)ptrStaticController->NoOfTxPdu;

  if((CanIf_TxPduIdType)CANIF_ZERO < noOfTxPdu)
  {
    /* @Trace: CanIf_SUD_API_300 */
    /* Get the respective pointer to TxLpdu */
    ptrTxLpdu = ptrStaticController->TxLpdu;
    do
    {
      /* polyspace +2 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
      /* Check the type of the Can for Basic of Full */
      if (CANIF_BASIC_CAN == (CANIF_HTHTYPE_MASK & ptrTxLpdu->HTHTypeOrTXPN))
      {
        /* @Trace: CanIf_SUD_API_306 */
        /* polyspace +17 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
        #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
        /* Clear the TxFirstQueue*/
        *(CanIfTxBuffer[ptrTxLpdu->HthIdorBufferId].TxFirstQueue) = NULL_PTR;

        /* Get tx queue index */
        txQueueIndex = CanIfTxBasicPduIndexMapping[ptrTxLpdu->TxPduId];

        #else
        /* Clear the TxFirstQueue*/
        *(CanIf_TxBuffer[ptrTxLpdu->HthIdorBufferId].TxFirstQueue) = NULL_PTR;

        /* Get tx queue index */
        txQueueIndex = CanIf_TxBasicPduIndexMapping[ptrTxLpdu->TxPduId];

        #endif
        /* Get tx queue Id from queue index */
        txQueueId = CanIf_TxPduToQueueMapping[txQueueIndex];

        if((CanIf_TxPduIdType)CANIF_INVALID_TXQUEUE != txQueueId)
        {
          /* @Trace: CanIf_SUD_API_307 */
          /* clear Dlc of Tx in queue */
          /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
          CanIf_TxQueue[txQueueId].Dlc = (uint8) CANIF_ZERO;

          /* clear the pointer to next queue of Tx in queue */
          CanIf_TxQueue[txQueueId].TxNextQueue = NULL_PTR;

          /* Set status of this queue to empty*/
          CanIf_TxPduToQueueMapping[txQueueIndex] = (CanIf_TxPduIdType) CANIF_INVALID_TXQUEUE;
        }
        else
        {
        	/* Do nothing */
        }
      }
      else /* @ if (CANIF_BASIC_CAN == (CANIF_HTHTYPE_MASK)) */
      {
      	/* Do nothing */
      }
      /* Decrement the number of TxPdu and */
      noOfTxPdu--;
      /* increment pointer to ptrTxPdu */
      ptrTxLpdu++;
    } while ((CanIf_TxPduIdType) CANIF_ZERO != noOfTxPdu);
  }
  else
  {
  	/* Do nothing */
  }

}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* polyspace-end RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */

/*******************************************************************************
** Function Name        : CanIf_QueueTransmit                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service transmit L-PDU to Can Driver           **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrTxLpdu                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):  CanIf_TxBuffer                 **
**                                             CanIf_TxBasicPduIndexMapping   **
**                                             CanIf_TxPduToQueueMapping      **
**                        Function(s) invoked: CanIf_CanWriteService          **
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
#if (STD_ON == CANIF_TX_QUEUE)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_QueueTransmit (
                    P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST)ptrTxLpdu)
{
  P2CONST(CanIf_TxBufferType, AUTOMATIC, CANIF_CONST) ptrTxBuffer;
  P2VAR(CanIf_TxQueueType, AUTOMATIC, CANIF_VAR) ptrTxQueue;
  VAR(Can_PduType, CANIF_VAR) canPduInfo;
  
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
      ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
      (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))  
  VAR(Std_ReturnType, CANIF_VAR) canReturn;
  #else
  VAR(Can_ReturnType, CANIF_VAR) canReturn;
  #endif
  
  VAR(CanIf_TxQueueSizeType, CANIF_VAR) txQueueIndex;

  /* @Trace: SWS_CANIF_00033 */
  /* @Trace: CanIf_SUD_API_017 */
  SchM_Enter_CanIf_TX_QUEUE_PROTECTION();

  /* Get the pointer to the TxBuffer*/
  /* @Trace: SWS_CANIF_00668 */
  /* @Trace: CanIf_SUD_API_018 */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  ptrTxBuffer = &(CanIfTxBuffer[ptrTxLpdu->HthIdorBufferId]);
  #else
  ptrTxBuffer = &(CanIf_TxBuffer[ptrTxLpdu->HthIdorBufferId]);
  #endif
  /* polyspace +13 RTE:NIP [Not a defect:Low] "Value is defined in ptrTxBuffer " */
  /* Get the pointer to the TxQueue*/
  ptrTxQueue = *ptrTxBuffer->TxFirstQueue;
  /* polyspace +10 RTE:NIV [Not a defect:Low] "Value is redefined, it's cover by generation " */
  if (NULL_PTR != ptrTxQueue)
  {
    /* @Trace: CanIf_SUD_API_308 */
    /* Get the id */
    canPduInfo.id = ptrTxQueue->CanId;

    /* Get the DLC */
    canPduInfo.length = (ptrTxQueue->Dlc);
    /* polyspace +2 RTE:NIP [Not a defect:Low] "It has been checked, no impact" */
    /* Get the pointer to queue data */
    canPduInfo.sdu = ptrTxQueue->TxBufferPtr;
    
    /* Get the Tx L-PDU handle Id */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "Value is defined in ptrTxBuffer " */
    canPduInfo.swPduHandle = ptrTxQueue->TxLPduId;

    #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    /* Call Can_Write() */
    canReturn = CanIf_CanWriteService(ptrTxLpdu, ptrTxBuffer->HthId, &canPduInfo);
    #else
    /* Call Can_Write() */
    canReturn = CanIf_CanWriteService(ptrTxBuffer->HthId, &canPduInfo);
    #endif
    /* polyspace +6 DEFECT:DEAD_CODE MISRA2012:2.1,14.3 [Not a defect:Justified] "It's depend on the configuration of Can. No impact" */
    #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
      ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
      (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE)) 
    if (E_OK == canReturn)
    #else	
    if (CAN_OK == canReturn)
    #endif
    {
      /* @Trace: CanIf_SUD_API_309 */
      /* Set the Dlc Value of ptrTxQueue as Zero so that the tx queue is
          available for further storing of pdu */
      /* polyspace +1 DEFECT:CONSTANT_OBJECT_WRITE [not a defect:Low] "No impact" */
      ptrTxQueue->Dlc = (uint8)CANIF_ZERO;

      /* Make the next queue as first queue to be transmitted */
      /* polyspace +1 RTE:NIP [Not a defect:Low] "Value is defined in ptrTxBuffer " */
      *ptrTxBuffer->TxFirstQueue = ptrTxQueue->TxNextQueue;

      /* polyspace +6 MISRA2012:18.1 [Not a defect:Low] "Its boundary is pre-defined" */
      /* polyspace +5 MISRA2012:D4.1 [Not a defect:Low] "Its boundary is pre-defined" */
      /* polyspace +14 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined" */
      /* Get the mapping index to TxPduToQueueMapping array */
      /* polyspace +4 RTE:NIV [Not a defect:Low] "Value is redefined, it's cover by generation " */
      #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
      txQueueIndex = CanIfTxBasicPduIndexMapping[ptrTxQueue->TxLPduId];
      #else
      txQueueIndex = CanIf_TxBasicPduIndexMapping[ptrTxQueue->TxLPduId];
      #endif
      if (CANIF_NO_OF_BASIC_TXLPDU > txQueueIndex)
      {
        /* Clearing the mapping for the transmitted Pdu */
        /* @Trace: SWS_CANIF_00183 */
        /* @Trace: CanIf_SUD_API_019 */
        CanIf_TxPduToQueueMapping[txQueueIndex] = (CanIf_TxPduIdType) CANIF_INVALID_TXQUEUE;
      }
    }
    else /* @ (CAN_OK == canReturn) */
    {
      /* Do nothing */
    }
  }
  else /* if (NULL_PTR != ptrTxQueue) */
  {
    /* Do nothing */
  }
  SchM_Exit_CanIf_TX_QUEUE_PROTECTION();
  
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* polyspace-end RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */

/*******************************************************************************
** Function Name        : CanIf_TxNotification                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates a request for transmission of**
**                        the CAN L-PDU specified by the CanTxPduId and CAN   **
**                        related data in the L-PDU structure                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrTxLpdu                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : None                                                **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s):   CanIf_TxCbkUser               **
**                                              CanIf_BitArray                **
**                        Function(s) invoked:  None                          **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_TxNotification (
                         P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu,
                         Std_ReturnType result)
{
  VAR(uint8, CANIF_VAR) tmpVar;

  /* Get the upper layer callback user */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
  tmpVar = ptrTxLpdu->TxCbkUser;

  /* Check if confirmation is configured for that Tx L-PDU */
  if (CANIF_MAX_UL >= tmpVar)
  {
    /* @Trace: CanIf_SUD_API_310 */
    #if (CANIF_TX_MULTIPLE_CALLBACK == STD_ON)
    /* Invoke the upper layer Tx Confirmation callback */
    CanIf_TxMulCbkUser[ptrTxLpdu->CallbackIndex].TxCbkUser
      (ptrTxLpdu->TxConfirmPduId, result);
    #else
    /* polyspace +2 MISRA2012:D4.14 [Not a defect:Low] "pointer is predefined, not null" */
    /* polyspace +1 RTE:COR [Not a defect:Low] "pointer is predefined, not null" */
    CanIf_TxSingleCbkUser[tmpVar].TxCbkUser(ptrTxLpdu->TxConfirmPduId, result);
    #endif
  } 
  else /* Check if Tx Confirmation is not disabled */
  {
    /* Do nothing */
  }
  /* @Trace: SWS_CANIF_00472 */
  /* @Trace: CanIf_SUD_API_022 */
  #if (STD_ON == CANIF_READTXPDU_NOTIFY_STATUS_API)
  /* Get the mask value */
  tmpVar = ptrTxLpdu->TxNotifyStsMask;

  /* Check if notification is configured for that Tx L-PDU */
  if (((CANIF_BITARRAY_SIZE >= ptrTxLpdu->TxNotifyStatusIndex) && 
        ((uint8)CANIF_ZERO != tmpVar)                          && 
        (E_OK == result)))
  {
    /* @Trace: CanIf_SUD_API_311 */
    /* Disable relevant interrupts */
    SchM_Enter_CanIf_TX_NOTIFSTATUS_PROTECTION();

    /* Set the notification status value by applying appropriate mask */
    /* polyspace +2 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
    CanIf_BitArray[ptrTxLpdu->TxNotifyStatusIndex] =
                    CanIf_BitArray[ptrTxLpdu->TxNotifyStatusIndex] | tmpVar;

    /* Enable relevant interrupts */
    SchM_Exit_CanIf_TX_NOTIFSTATUS_PROTECTION();
  } 
  else /* if (tmpVar != CANIF_ZERO) */
  {
  	/* Do nothing */
  }
  #endif

}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_CanWriteService                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates a request for transmission of**
**                        the CAN L-PDU specified by the CanTxPduId and CAN   **
**                        related data in the L-PDU structure                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrTxLpdu, hth, PduInfo                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : drvRetVal                                           **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_CanDriver                 **
**                                            CanIf_TxPduGwStatus             **
**                        Function(s) invoked: Can_Write()                    **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CanWriteService (
#else
FUNC(Can_ReturnType, CANIF_CODE) CanIf_CanWriteService (
#endif
    #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu,
    #endif
    VAR(Can_HwHandleType, CANIF_VAR) hth,
    P2CONST(Can_PduType, AUTOMATIC, CANIF_CONST) PduInfo)
{
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  P2CONST(CanIf_CanDriverType, AUTOMATIC, CANIF_CONST) ptrDriver;
  #endif
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
      ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
      (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  VAR(Std_ReturnType, CANIF_VAR) drvRetVal;
  #else
  VAR(Can_ReturnType, CANIF_VAR) drvRetVal;
  #endif

  #if (STD_ON == CANIF_TX_LPDU)
  SchM_Enter_CanIf_MODE_STATUS_PROTECTION();

  /* Set GW state to REQUESTED */
  /* polyspace +1 MISRA2012:D4.1 [Not a defect:Low] "Its boundary is pre-defined"*/
  if ((PduInfo->swPduHandle) < CANIF_NO_OF_TXLPDU)
  {
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
    CanIf_TxPduGwStatus[PduInfo->swPduHandle] = CANIF_GW_REQUESTED;
  }
  else
  {
    /* Do nothing */
  }

  SchM_Exit_CanIf_MODE_STATUS_PROTECTION();
  #endif

  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  /* Get the pointer to corresponding Can Driver structure */
  ptrDriver = &CanIf_CanDriver[ptrTxLpdu->DriverId];
  /* polyspace-begin CERT-C:DCL39-C [Not a defect: Justified] "Can_PduType Type of PduInfo is defined by Autosar, it can not be modified. No impact" */
  /* Invoke the function to set the controller mode for Can Driver*/
  drvRetVal = ptrDriver->CanWrite (hth, PduInfo);
  #else
  /* Invoke the function to set the controller mode for Can Driver*/
  //drvRetVal = Can_Write(hth, PduInfo);
  #endif
  
  #if ((STD_ON == CANIF_TX_LPDU) && (STD_ON == CANIF_TX_RX_MONITORING_SUPPORT))
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
  ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
  (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  if (E_OK == drvRetVal)
  #else
  if (CAN_OK == drvRetVal)
  #endif
  {
    CanIf_TransmitCnt[PduInfo->swPduHandle]++;
  }
  #endif
  /* polyspace-end CERT-C:DCL39-C [Not a defect: Justified] "Can_PduType Type of PduInfo is defined by Autosar, it can not be modified. No impact" */
  return drvRetVal;
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_ClearTxBuffer                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates a request for transmission of**
**                        the CAN L-PDU specified by the CanTxPduId and CAN   **
**                        related data in the L-PDU structure                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : txPduId, ptrTxBuffer                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Void                                                **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_TxBasicPduIndexMapping    **
**                                            CanIf_TxPduToQueueMapping       **
**                                            CanIf_TxQueue                   **
**                        Function(s) invoked:  None                          **
*******************************************************************************/
#if (STD_ON == CANIF_TX_QUEUE)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_ClearTxBuffer (
                     VAR(CanIf_TxQueueSizeType, CANIF_VAR) txQueueIndex,
                     P2CONST(CanIf_TxBufferType, AUTOMATIC, CANIF_CONST) ptrTxBuffer)
{
  P2VAR(CanIf_TxQueueType, AUTOMATIC, CANIF_VAR) ptrTxQueue;
  P2VAR(CanIf_TxQueueType, AUTOMATIC, CANIF_VAR) ptrTxFirstQueue;
  VAR(CanIf_TxQueueSizeType, CANIF_VAR) txQueueId;

  /* Enable interrupts to protect Tx DATA */
  SchM_Enter_CanIf_TX_QUEUE_PROTECTION();

  /* Get the TxqueueId from CanIf_TxPduToQueueMapping array */
  /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
  txQueueId = CanIf_TxPduToQueueMapping[txQueueIndex];

  if(CANIF_INVALID_TXQUEUE != txQueueId){
    /* @Trace: CanIf_SUD_API_312 */
    /* Mark it as available */
    CanIf_TxPduToQueueMapping[txQueueIndex] = (CanIf_TxPduIdType)CANIF_INVALID_TXQUEUE;

    /* Set Status of Tx queue as available*/
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
    CanIf_TxQueue[txQueueId].Dlc = (uint8)CANIF_ZERO;

    /* Get the pointer to respective TxQueue */
    /* polyspace +12 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    ptrTxQueue = &(CanIf_TxQueue[txQueueId]);

    /* Get the pointer to respective TxQueue */
    /* polyspace +11 RTE:NIP [Not a defect:Low] "Value is defined in ptrTxBuffer " */
    ptrTxFirstQueue = *ptrTxBuffer->TxFirstQueue;

    if (ptrTxFirstQueue != NULL_PTR)
    {
      if (ptrTxFirstQueue == ptrTxQueue)
      { 
        /* @Trace: CanIf_SUD_API_313 */
        /* Make the next queue as first queue */
          *ptrTxBuffer->TxFirstQueue = ptrTxQueue->TxNextQueue;
      }
      else
      {
        /* @Trace: CanIf_SUD_API_314 */
        /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "It has been checked, no impact" */
        /* polyspace +2 RTE:NIP [Not a defect:Low] "It has been checked, no impact" */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
        while ((NULL_PTR != ptrTxFirstQueue->TxNextQueue) &&
              (ptrTxQueue != ptrTxFirstQueue->TxNextQueue))
        {
          /* @Trace: CanIf_SUD_API_315 */
          /* Make the next queue as first queue */
          ptrTxFirstQueue = ptrTxFirstQueue->TxNextQueue;
        }
        /* Update next queue */
        ptrTxFirstQueue->TxNextQueue = ptrTxQueue->TxNextQueue;
      }
    }
    else
    {
      /* Do nothing */
    }
  }
  else
  {
    /* Do nothing */
  }

  /* Disable interrupts to protect Tx DATA */
  SchM_Exit_CanIf_TX_QUEUE_PROTECTION(); 

}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : CanIf_DETTransmit                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates a request for transmission of**
**                        the CAN L-PDU specified by the CanTxPduId and CAN   **
**                        related data in the L-PDU structure                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : CanTxPduId, PduInfoPtr                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_Return (E_OK or E_NOT_OK)                       **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanIf_CanIfStatus, CanIf_TxLpdu,                    **
**                        CanIf_Controller                                    **
**                        Function(s) invoked:                                **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01126 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_DETTransmit (
                        VAR(PduIdType, CANIF_VAR) CanTxPduId,
                        P2CONST(PduInfoType, AUTOMATIC, CANIF_CONST) PduInfoPtr)
{
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  VAR(uint8, CANIF_VAR) txStatus;
  VAR(uint8, CANIF_VAR) rxStatus;
  VAR(uint8, CANIF_VAR) currentMode;

  /* Set retVal to E_OK */
  retVal = (Std_ReturnType) E_OK;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_TRANSMIT_SID, retVal);
  
  /* Report to DET, if Tx L-PDU is out of range */
  /* Check TxLpduId range */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  if (CanTxPduId >= (PduIdType)CanIf_NoofTxLpdu)
  #else
  if (CanTxPduId >= CANIF_NO_OF_TXLPDU)
  #endif
  {
    /* @Trace: CanIf_SUD_API_316 */
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_TRANSMIT_SID,  
            CANIF_E_INVALID_TXPDUID);
    (retVal) = (uint8)E_NOT_OK;
  }
  /* Report to DET, if PduInfoptr is a Null Ptr*/
  CANIF_NULL_PTR_ERROR(CANIF_TRANSMIT_SID, retVal, PduInfoPtr);

  #endif

  if ((Std_ReturnType) E_OK == retVal)
  {
    /* @Trace: CanIf_SUD_API_317 */
    /* Get the pointer to Tx Lpdu */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrTxLpdu = &CanIfTxLpdu[CanTxPduId];
    #else
    ptrTxLpdu = &CanIf_TxLpdu[CanTxPduId];
    #endif

    #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
    /* Get the pointer to controller */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    ptrController = &CanIf_Controller[ptrTxLpdu->ControllerId];
    #else
    ptrController = &CanIf_Controller[CANIF_ZERO];
    #endif
    /* polyspace +2 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    /* get the Tx status into local variable */
    txStatus = (uint8)CANIF_TX_STATUS(ptrController->PduMode);

    /* get the Rx status into local variable */
    rxStatus = (uint8)CANIF_RX_STATUS(ptrController->PduMode);

    /* get the ControllerMode into local variable */
    currentMode = (uint8)ptrController->ControllerMode;

    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    #if (((STD_ON == CANIF_SETDYNAMICTXID_API) && (STD_ON == CANIF_META_DATA_SUPPORT)) || (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT))
    retVal = CanIf_CheckPduInfo(CanTxPduId, PduInfoPtr);
    #else
    retVal = CanIf_CheckPduInfo(PduInfoPtr);
    #endif
    #endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */

    /* Report to DET, if PDU mode is Offline or Controller Mode is Stopped */
    /* @Trace: SWS_CANIF_00677 SWS_CANIF_00317 SWS_CANIF_00382 */
    CANIF_OFFLINE_PDU_STOPPED_CTRL_MODE(CANIF_TRANSMIT_SID, retVal);
    /* polyspace +3 RTE:NIV [Not a defect:Low] "The value of PduInfoPtr->SduLength has been gotten from the upper layer, no impact" */
    /* @Trace: SWS_CANIF_00893 SWS_CANIF_00894 SWS_CANIF_00900 */
    /* polyspace +2 MISRA2012:D4.14 [Not a defect:Low] "This Macro used to check Null of PduInfoPtr->SduLength" */
    CANIF_VALID_SDU_LENGTH(CANIF_TRANSMIT_SID, retVal);
  }
  else
  {
  	/* Do nothing*/
  }

  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /* ((STD_ON == CANIF_DEV_ERROR_DETECT) && (STD_ON == CANIF_TX_LPDU)) */

/*******************************************************************************
** Function Name        : CanIf_DummyTxTriggerTransmit                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : dummy API                                           ** 
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : TxPduId, PduInfoPtr                                 **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The CAN Interface must be initialised.              **
**                                                                            **
** Remarks              : Global Variable(s):None                             **
**                        Function(s) invoked:None                            **
*******************************************************************************/ 
#if (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT) 	
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_DummyTxTriggerTransmit (PduIdType TxPduId,
       P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr)
{
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;
  LenStdRetVal = (uint8)E_NOT_OK;

  CANIF_UNUSED(TxPduId);
  CANIF_UNUSED(PduInfoPtr);

  return(LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif 

/*******************************************************************************
** Function Name        : CanIf_TriggerTransmit                               **
**                                                                            **
** Service ID           : 0x41                                                **
**                                                                            **
** Description          : Within this API, the upper layer module             **
** 						            (called module) shall check whether the available   **
**						            data fits into the buffer size reported by          ** 
**						            PduInfoPtr->SduLength. If it fits, it shall copy    **
** 					              its data into the buffer provided by 				        **
**						            PduInfoPtr->SduDataPtr and update the length of the **
**					           	  actual copied data in PduInfoPtr->SduLength.        **
**						            If not, it returns E_NOT_OK without changing        **
**						            PduInfoPtr.                              			      ** 
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : TxPduId, PduInfoPtr                                 **
**                                                                            **
** InOut Parameters     : PduInfoPtr                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s):CanIf_TxLpdu                     **
**                        Function(s) invoked: PduR_CanIfTriggerTransmit      **
**											                                                      **
*******************************************************************************/ 
/* polyspace +7 MISRA2012:8.13 [Not a defect:Low] " This function definition follow Autosar requirement SWS_CANIF_00883. No impact "*/
#if (STD_ON == CANIF_TX_LPDU) && (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_TriggerTransmit (
                   VAR(PduIdType, CANIF_VAR) TxPduId,
				   P2VAR(PduInfoType, AUTOMATIC, CANIF_VAR) PduInfoPtr)
{
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  VAR(uint8, CANIF_VAR) tmpVar;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Initialize error status flag to false */
  retVal = (uint8) E_OK;

  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_TRIGGER_TRANSMIT_SID, retVal);

  if ((uint8) E_OK == retVal)
  #endif /* if development error is not enabled */
  {
    /* @Trace: CanIf_SUD_API_320 */
    /* Get the pointer to requested Tx L-PDU */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrTxLpdu = &CanIfTxLpdu[TxPduId];
    #else
    ptrTxLpdu = &CanIf_TxLpdu[TxPduId];
    #endif

    /* Get the upper layer callback user */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    tmpVar = ptrTxLpdu->TxCbkUser;
    /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanIf. No impact" */
    /* @Trace: SWS_CANIF_00885 */
    /* @Trace: CanIf_SUD_API_023 */
    if(CANIF_PDUR == tmpVar)
    {
      /* @Trace: CanIf_SUD_API_321 */
      retVal = CanIf_TxSingleCbkTriggerUser[CANIF_PDUR_TRIGGER].
                    pTxCbkTriggerUser(ptrTxLpdu->TxConfirmPduId, PduInfoPtr);
    }
    #if (STD_ON == CANIF_TRIGGER_TRANSMIT_CDD_SUPPORT)
    else if (CANIF_CDD == tmpVar)
    {
      /* @Trace: CanIf_SUD_API_322 */
      retVal = CanIf_TxSingleCbkTriggerUser[CANIF_CDD_TRIGGER].
                    pTxCbkTriggerUser(ptrTxLpdu->TxConfirmPduId, PduInfoPtr);
    }
    #endif
    else
    {
      /* @Trace: CanIf_SUD_API_323 */
      retVal = CanIf_DummyTxTriggerTransmit(TxPduId,PduInfoPtr);
    }
    /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanIf. No impact" */
  }
  return(retVal);
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /*#if (STD_ON == CANIF_TX_LPDU) && (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT)*/

/*******************************************************************************
** Function Name        : CanIf_CheckHthType                                  **
**                                                                            **
** Service ID           :                                                     **
**                                                                            **
** Description          : Within this API, CanIf will check Hth type ref      **
**                        is BASIC or FULL for Transmit                       **
**                                                                            **
**                                                                            **
** Sync/Async           :                                                     **
**                                                                            **
** Re-entrancy          :                                                     **
**                                                                            **
** Input Parameters     : TxPduId, PduInfoPtr                                 **
**                                                                            **
** InOut Parameters     :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s)  : CanIf_TxLpdu                  **
**                        Function(s) invoked : CanIf_CanWriteService         **
**											                        CanIf_StoreLpduInQueue        **
*******************************************************************************/ 
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckHthType(
                   VAR(PduIdType, CANIF_VAR) TxPduId,
                   P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr)
{
  #if (STD_ON == CANIF_META_DATA_SUPPORT)&&(STD_ON == CANIF_SETDYNAMICTXID_API)
  VAR(uint32, CANIF_VAR) canId;
  canId = CANIF_ZERO;
  #endif
  
  VAR(Can_HwHandleType, CANIF_VAR) hthIdOrBufferId;
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
    (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  VAR(Std_ReturnType, CANIF_VAR) canReturn;
  #else
  VAR(Can_ReturnType, CANIF_VAR) canReturn;
  #endif
  VAR(Can_PduType, CANIF_VAR) canPduInfo;  
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;

  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  ptrTxLpdu = &CanIfTxLpdu[TxPduId];
  #else
  ptrTxLpdu = &CanIf_TxLpdu[TxPduId];
  #endif

  VAR(Std_ReturnType, CANIF_VAR) retVal;
  #if (STD_ON == CANIF_BASIC_CAN_TXPDU)
  VAR(uint8, CANIF_VAR) hthType;
  #endif

  /* Prepare message to transmit L-PDU to CAN Driver */
  #if (STD_ON == CANIF_SETDYNAMICTXID_API)
  /* Is CanId index value is CANIF_INVALID_DYNCANID in rxpdu structure*/
  if (CANIF_INVALID_DYNCANID != ptrTxLpdu->DynCanIdIndex)
  {
    SchM_Enter_CanIf_TX_DYNCANID_PROTECTION();
    /* @Trace: SWS_CANIF_00855 */
    /* @Trace: CanIf_SUD_API_010 */
    #if (STD_ON == CANIF_META_DATA_SUPPORT)
    /* get the Tx mask into local variable */

    switch (ptrTxLpdu->MetaDataLength)
    {
      /* if meta data length is four */
      /* polyspace +3 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
      case CANIF_FOUR:
        /* @Trace: CanIf_SUD_API_324 */
        canId = PduInfoPtr->MetaDataPtr[CANIF_ZERO];
        canId = canId << CANIF_EIGHT;
        canId = (canId | PduInfoPtr->MetaDataPtr[CANIF_ONE]);
        canId = canId << CANIF_EIGHT;
        canId = (canId | PduInfoPtr->MetaDataPtr[CANIF_TWO]);
        canId = canId << CANIF_EIGHT;
        canId = (canId | PduInfoPtr->MetaDataPtr[CANIF_THREE]);
        /* CANIF_EXTENDED_BIT_SET = 0x80000000uL */
        canId = canId | CANIF_EXTENDED_BIT_SET; 
        break;

      default:
        /* Do nothing */
        break;
    }
    /* polyspace +4 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    CanIfCanId[ptrTxLpdu->DynCanIdIndex] = canId;
    #else
    CanIf_CanId[ptrTxLpdu->DynCanIdIndex] = canId;
    #endif

    #endif /* (STD_ON == CANIF_META_DATA_SUPPORT) */

    /* Read the CAN ID from the RAM area */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    canPduInfo.id = CanIfCanId[ptrTxLpdu->DynCanIdIndex];
    #else
    canPduInfo.id = CanIf_CanId[ptrTxLpdu->DynCanIdIndex];
    #endif

    SchM_Exit_CanIf_TX_DYNCANID_PROTECTION();
  }
  else
  #endif
  {
    /* @Trace: CanIf_SUD_API_325 */
    /* Read the CAN ID from ROM area */
    canPduInfo.id = (ptrTxLpdu->CanId);
  }
  /* polyspace +2 RTE:NIP [Not a defect:Low] "The value of PduInfoPtr->SduDataPtr has been gotten from the upper layer and Its value has been checked before this function is called" */
  /* copy the data pointer  */
  canPduInfo.sdu = PduInfoPtr->SduDataPtr;
  /* polyspace +12 RTE:NIV [Not a defect:Low] "The value of PduInfoPtr->SduLength has been gotten from the upper layer and Its value has been checked before this function is called" */
  /* copy the length */
  if (((uint8)CANIF_SDU_MAX_LENGTH < (PduInfoPtr->SduLength)) && 
                        (CANIF_TRUE == ptrTxLpdu->Truncate)) 
  {
    /* @Trace: CanIf_SUD_API_326 */
    canPduInfo.length = (uint8)CANIF_SDU_MAX_LENGTH;
  }
  else
  {
    /* @Trace: CanIf_SUD_API_327 */
    canPduInfo.length = (uint8)PduInfoPtr->SduLength;
  }
  
  /* copy the CanTxPduId handle id */
  canPduInfo.swPduHandle = TxPduId;

  /* @Trace: SWS_CANIF_00835 */
  /* @Trace: CanIf_SUD_API_011 */
  /* Get the index to HthId or Buffer Index */
  hthIdOrBufferId = ptrTxLpdu->HthIdorBufferId;

  #if (STD_ON == CANIF_BASIC_CAN_TXPDU)
  /* Get the HthType as FULL or BASIC Can*/
  hthType = (uint8)(CANIF_HTHTYPE_MASK & ptrTxLpdu->HTHTypeOrTXPN);
  /* Check if TXPDU is FULL CAN */
  if (CANIF_FULL_CAN == hthType)
  #endif
  {
    #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    /* @Trace: SWS_CANIF_00318 */
    /* @Trace: CanIf_SUD_API_039 */
    /* Call Can_Write() */
    canReturn = CanIf_CanWriteService(ptrTxLpdu, hthIdOrBufferId,
                                      &canPduInfo);
    #else
    /* @Trace: SWS_CANIF_00318 */
    /* Call Can_Write() */
    canReturn = CanIf_CanWriteService(hthIdOrBufferId, &canPduInfo);
    #endif
    /* Check if TxPDU is transmitted on bus */
    /* @Trace: SWS_CANIF_00162 */
    /* polyspace +6 DEFECT:DEAD_CODE MISRA2012:2.1,14.3 [Not a defect:Justified] "It's depend on the configuration of Can. No impact" */
    #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
    (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
    if (E_OK == canReturn)
    #else
    if (CAN_OK == canReturn)
    #endif
    {
      /* @Trace: CanIf_SUD_API_329 */
      /* Return E_OK */
      retVal = (uint8) E_OK;
    }
    else
    {
      /* @Trace: CanIf_SUD_API_330 */
      retVal = (uint8)E_NOT_OK;
    }
  }
  #if ((STD_ON == CANIF_BASIC_CAN_TXPDU) && (STD_ON == CANIF_TX_QUEUE))
  else /* @ if (CANIF_FULL_CAN == hthType) */
  {
    /* @Trace: CanIf_SUD_API_331 */
    retVal = CanIf_StoreLpduInQueue(canPduInfo,TxPduId);    
  }/* Check if Partial networking is configured for the PDU */
  #endif
  return(retVal);
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_StoreLpduInQueue                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Within this API, transmit with hth type BASIC Can   ** 
** Sync/Async           :                                                     **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : canPduInfo, TxPduId                                 **
**                                                                            **
** InOut Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The CAN Interface buffer must be configure          **
**                                                                            **
** Remarks              : Global Variable(s) : CanIf_TxLpdu                   **
**                        Function(s) invoked: CanIf_CanWriteService          **
**											   CanIf_ClearTxBuffer            **
**                                             CanIf_IsInQueue                **
**                                             CanIf_CheckQueueStatus         **
**                                             CanIf_TxQueueHandling          **
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
#if ((STD_ON == CANIF_BASIC_CAN_TXPDU) && (STD_ON == CANIF_TX_QUEUE))	
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01011 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_StoreLpduInQueue (
                     VAR(Can_PduType, CANIF_VAR) CanPduInfo,
                     VAR(PduIdType, CANIF_VAR) TxPduId)
{
  P2CONST(CanIf_TxBufferType, AUTOMATIC, CANIF_CONST) ptrTxBuffer;  
  VAR(CanIf_TxQueueSizeType, CANIF_VAR) txQueueId;
  VAR(CanIf_TxQueueSizeType, CANIF_VAR) txQueueIndex;
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
  ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
  (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  VAR(Std_ReturnType, CANIF_VAR) canReturn;
  #else
  VAR(Can_ReturnType, CANIF_VAR) canReturn;
  #endif
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  VAR(Can_PduType, CANIF_VAR) canPduInfo;
  canPduInfo = CanPduInfo;
  retVal = E_OK;
  
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;  

  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  ptrTxLpdu = &CanIfTxLpdu[TxPduId];
  #else
  ptrTxLpdu = &CanIf_TxLpdu[TxPduId];
  #endif

  /* copy the CanTxPduId handle id */
  canPduInfo.swPduHandle = TxPduId;
  if (CANIF_NO_OF_TXBUFFER > ptrTxLpdu->HthIdorBufferId)
  {
    /* @Trace: CanIf_SUD_API_332 */
    /* Get the pointer to TX buffer */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    /* Get tx buffer */
    ptrTxBuffer = &(CanIfTxBuffer[ptrTxLpdu->HthIdorBufferId]);

    /* Get tx queue index */
    txQueueIndex = CanIfTxBasicPduIndexMapping[TxPduId];
    #else
    /* Get tx buffer */
    ptrTxBuffer = &(CanIf_TxBuffer[ptrTxLpdu->HthIdorBufferId]);

    /* Get tx queue index */
    txQueueIndex = CanIf_TxBasicPduIndexMapping[TxPduId];
    #endif

    /* Enable interrupts to protect Tx DATA */
    /* @Trace: SWS_CANIF_00033 */
    /* @Trace: CanIf_SUD_API_013 */
    SchM_Enter_CanIf_TX_QUEUE_PROTECTION();

    /*Get the tx queue Id from the CanTxPduId*/
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
    txQueueId = CanIf_TxPduToQueueMapping[txQueueIndex];
    
    /* Check if queue is free */
    if (CANIF_INVALID_TXQUEUE == txQueueId)
    {
      #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
      /* @Trace: SWS_CANIF_00318 */
      /* @Trace: CanIf_SUD_API_012 */
      /* Call Can_Write() */
      canReturn = CanIf_CanWriteService(ptrTxLpdu, ptrTxBuffer->HthId,
                                        &canPduInfo);
      #else
      /* @Trace: SWS_CANIF_00318 */
      /* Call Can_Write() */
      canReturn = CanIf_CanWriteService(ptrTxBuffer->HthId, &canPduInfo);
      #endif
      /* Check if TxPDU is transmitted on bus */
      /* @Trace: SWS_CANIF_00162 */
      /* polyspace +6 DEFECT:DEAD_CODE MISRA2012:2.1,14.3 [Not a defect:Justified] "It's depend on the configuration of Can. No impact" */
      #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
      ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
      (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
      if (E_OK == canReturn)
      #else
      if (CAN_OK == canReturn)
      #endif
      {
        /* @Trace: CanIf_SUD_API_333 */
        /* Return E_OK */
        retVal = (uint8) E_OK;
      }
      else
      {
        /* @Trace: CanIf_SUD_API_334 */
        retVal = (uint8)E_NOT_OK;
      }
    }/* @ if (CANIF_INVALID_TXQUEUE == txQueueId) */

    #if (STD_ON == CANIF_SETDYNAMICTXID_API)
    /* Check whether dynamic ID has been changed after Tx request */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
    else if (CanIf_TxQueue[txQueueId].CanId != canPduInfo.id)
    {
      /* @Trace: CanIf_SUD_API_335 */
      #if (STD_ON == CANIF_TX_QUEUE)
      /* Flush data from Tx Queue */
      CanIf_ClearTxBuffer(txQueueIndex, ptrTxBuffer);
      #endif
    
      #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
      /* Call Can_Write() */
      /* @Trace: SWS_CANIF_00318 */
      canReturn = CanIf_CanWriteService(ptrTxLpdu, ptrTxBuffer->HthId,
                                      &canPduInfo);
      #else
      /* Call Can_Write() */
      /* @Trace: SWS_CANIF_00318 */
      canReturn = CanIf_CanWriteService(ptrTxBuffer->HthId, &canPduInfo);
      #endif
      /* @Trace: SWS_CANIF_00162 */
      /* polyspace +6 DEFECT:DEAD_CODE MISRA2012:2.1,14.3 [Not a defect:Justified] "It's depend on the configuration of Can. No impact" */
      #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    	((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
    	(CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
      if (E_OK == canReturn)
      #else
      if (CAN_OK == canReturn)
      #endif
      {
        /* @Trace: CanIf_SUD_API_336 */
        /* Return E_OK */
        retVal = (uint8) E_OK;
      }
      else
      {
        /* @Trace: CanIf_SUD_API_337 */
        retVal = (uint8)E_NOT_OK;
      }
    }
    #endif
    else
    {
      /* @Trace: CanIf_SUD_API_338 */
      #if (STD_ON == CANIF_TX_BUFFERING)	
      /* Set CAN return value to busy */
      canReturn = CAN_BUSY;
      #endif  
    }
    
    #if (STD_ON == CANIF_TX_BUFFERING)		
    /* Check if can returns busy */
    if (CAN_BUSY == canReturn)
    {
      /* @Trace: CanIf_SUD_API_339 */
      retVal = CanIf_StoreLpduInQueue_CAN_BUSY(&canPduInfo,TxPduId);
    }
    else /* @ if (CAN_BUSY == canReturn) */
    {
      /* Do nothing */
    }
    #else /* if (STD_ON == CANIF_TX_BUFFERING)*/
    if (CAN_OK != canReturn)
    {
      /* @Trace: CanIf_SUD_API_344 */
      retVal = (uint8)E_NOT_OK;
    }
    else
    {
      /* Do nothing */
    }
    #endif
    
    /* Disable interrupts to protect Tx DATA */
    SchM_Exit_CanIf_TX_QUEUE_PROTECTION();    
  }
  else
  {
    /* @Trace: CanIf_SUD_API_345 */
    retVal = E_NOT_OK;
  }
  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* polyspace-end RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */

/*******************************************************************************
** Function Name        : CanIf_StoreLpduInQueue_CAN_BUSY                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Within this API, transmit with hth type BASIC Can   ** 
** Sync/Async           :                                                     **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : canPduInfo, TxPduId                                 **
**                                                                            **
** InOut Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The CAN Interface buffer must be configure          **
**                                                                            **
** Remarks              : Global Variable(s) : CanIf_TxLpdu                   **
**                        Function(s) invoked: CanIf_CanWriteService          **
**											   CanIf_ClearTxBuffer            **
**                                             CanIf_IsInQueue                **
**                                             CanIf_CheckQueueStatus         **
**                                             CanIf_TxQueueHandling          **
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
#if ((STD_ON == CANIF_BASIC_CAN_TXPDU) && (STD_ON == CANIF_TX_QUEUE))	
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01011 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_StoreLpduInQueue_CAN_BUSY (
                     P2VAR(Can_PduType, AUTOMATIC, CANIF_VAR) CanPduInfo,
                     VAR(PduIdType, CANIF_VAR) TxPduId)
{
  P2CONST(CanIf_TxBufferType, AUTOMATIC, CANIF_CONST) ptrTxBuffer;  
  VAR(CanIf_TxQueueSizeType, CANIF_VAR) txQueueId;
  VAR(CanIf_TxQueueSizeType, CANIF_VAR) txQueueIndex;

  VAR(Std_ReturnType, CANIF_VAR) retVal;
  P2VAR(Can_PduType, AUTOMATIC, CANIF_VAR) canPduInfo;
  canPduInfo = CanPduInfo;

  VAR(uint8, CANIF_VAR) maxlength;
  #if (STD_ON == CANIF_TX_BUFFERING)
  VAR(boolean, CANIF_VAR) isTrigTransInQueue;
  VAR(uint8, CANIF_VAR) count;
  P2VAR(CanIf_TxQueueType, AUTOMATIC, CANIF_VAR) ptrTxQueue;
  #endif

  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;  

  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  ptrTxLpdu = &CanIfTxLpdu[TxPduId];
  #else
  ptrTxLpdu = &CanIf_TxLpdu[TxPduId];
  #endif

  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  ptrTxBuffer = &(CanIfTxBuffer[ptrTxLpdu->HthIdorBufferId]);
  txQueueIndex = CanIfTxBasicPduIndexMapping[TxPduId];
  #else
  ptrTxBuffer = &(CanIf_TxBuffer[ptrTxLpdu->HthIdorBufferId]);
  txQueueIndex = CanIf_TxBasicPduIndexMapping[TxPduId];
  #endif

  /* Enable interrupts to protect Tx DATA */
  SchM_Enter_CanIf_TX_QUEUE_PROTECTION();

  /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
  txQueueId = CanIf_TxPduToQueueMapping[txQueueIndex];
  /* copy the CanTxPduId handle id */
  canPduInfo->swPduHandle = TxPduId;
    
  /* @Trace: CanIf_SUD_API_339 */
  /* Check if trigger transmit request has been stored in queue */
  isTrigTransInQueue = CANIF_FALSE;

  if (NULL_PTR == canPduInfo->sdu) {
    /* @Trace: CanIf_SUD_API_340 */
    isTrigTransInQueue = CanIf_IsInQueue(ptrTxBuffer, canPduInfo);
  }
  else
  {
    /* Do nothing */
  }
  
  #if (STD_ON == CANIF_CANFD_SUPPORT)
  if ((ptrTxLpdu->CanIdType == CANIF_CANFD_EXTENDED_CANID_TYPE) || 
      (ptrTxLpdu->CanIdType == CANIF_CANFD_STANDARD_CANID_TYPE))
  {
    maxlength = CANIF_CANFD_MAX_LENGTH;
  }
  else 
  {
    maxlength = CANIF_EIGHT;
  }
  #else
  maxlength = CANIF_EIGHT;
  #endif

  if (CANIF_TRUE == isTrigTransInQueue) {
    /* @Trace: CanIf_SUD_API_341 */
    /* @Trace: SWS_CANIF_00837 Trigger transmit request already stored, return E_NOT_OK */
    /* @Trace: CanIf_SUD_API_014 */
    retVal = (uint8) E_NOT_OK;
  }
  /* Check if queue is available */
  else if (CANIF_INVALID_TXQUEUE == txQueueId)
  {
    /* @Trace: SWS_CANIF_00881 */
    /* @Trace: CanIf_SUD_API_015 */
    /* Check the tx queue status to store the data */
    txQueueId = CanIf_CheckQueueStatus(ptrTxBuffer);

    if (CANIF_INVALID_TXQUEUE != txQueueId)
    {
      /* @Trace: CanIf_SUD_API_016 */
      CanIf_TxPduToQueueMapping[txQueueIndex] = (CanIf_TxPduIdType)txQueueId;

      /* @Trace: SWS_CANIF_00836 SWS_CANIF_00068 */
      /* Store the pdu in the queue */
      /* polyspace-begin RTE:NIV [Not a defect:Low] "Value is redefined " */
      /* polyspace-begin RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
      ptrTxQueue = &(CanIf_TxQueue[(txQueueId)]);                                
      ptrTxQueue->TxLPduId = canPduInfo->swPduHandle;                     
      ptrTxQueue->Dlc = canPduInfo->length;                               
      ptrTxQueue->CanId = canPduInfo->id;                                 
      if (NULL_PTR != canPduInfo->sdu)                                    
      {                                                                  
        count = canPduInfo->length;                                       
        if ((CANIF_TRUE == ptrTxLpdu->Truncate) &&                       
            ((uint8)maxlength < count))                       
        {	                                                               
          /* @Trace: SWS_CANIF_00894 SWS_CANIF_00895 */                                    
          count = (uint8)maxlength;                           
          CANIF_STOGARE_ERROR_DET_REPORT();                              
        }    
        while ((uint8)CANIF_ZERO != count)                               
        {                                                                
          count--;                                                       
          ptrTxQueue->TxBuffer[count] = canPduInfo->sdu[count];           
        };                                                               
        ptrTxQueue->TxBufferPtr = ptrTxQueue->TxBuffer;                  
      }                                                                  
      else                                                               
      {                                                                  
        ptrTxQueue->TxBufferPtr = NULL_PTR;                              
      }
      /* polyspace-end RTE:NIV [Not a defect:Low] "Value is redefined " */
      /* polyspace-end RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
      /* Arrange the pdus according to the priority*/
      CanIf_TxQueueHandling(ptrTxBuffer, txQueueId);

      /* return E_OK */
      retVal = (uint8) E_OK;
    }
    else /* (CANIF_INVALID_TXQUEUE != txQueueId) */
    {    
      /* @Trace: CanIf_SUD_API_342 */
      retVal = (uint8)E_NOT_OK;
    }
  }
  else /* @ (CANIF_INVALID_TXQUEUE == CanIf_TxPduToQueueMapping [...]) */
  {
    /* @Trace: CanIf_SUD_API_343 */
    /* Store the pdu in the queue*/
    /* polyspace-begin RTE:NIV [Not a defect:Low] "Value is redefined " */
    /* polyspace-begin RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
    ptrTxQueue = &(CanIf_TxQueue[(txQueueId)]);                                
    ptrTxQueue->TxLPduId = canPduInfo->swPduHandle;                     
    ptrTxQueue->Dlc = canPduInfo->length;                               
    ptrTxQueue->CanId = canPduInfo->id;                                 
    if (NULL_PTR != canPduInfo->sdu)                                    
    {                                                                  
      count = canPduInfo->length;                                       
      if ((CANIF_TRUE == ptrTxLpdu->Truncate) &&                       
          ((uint8)maxlength < count))                       
      {	                                                               
        /* @Trace: SWS_CANIF_00894 SWS_CANIF_00895 */                                   
        count = (uint8)maxlength;                           
        CANIF_STOGARE_ERROR_DET_REPORT();                              
      }              
      /* polyspace +4 RTE:NIV [Not a defect:Low] "Value is redefined " */
      while ((uint8)CANIF_ZERO != count)                               
      {                                                                
        count--;                                                       
        ptrTxQueue->TxBuffer[count] = canPduInfo->sdu[count];           
      };                                                               
      ptrTxQueue->TxBufferPtr = ptrTxQueue->TxBuffer;                  
    }                                                                  
    else                                                               
    {                                                                  
      ptrTxQueue->TxBufferPtr = NULL_PTR;                              
    }
    /* polyspace-end RTE:NIV [Not a defect:Low] "Value is redefined " */
    /* polyspace-end RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
    /* Return E_OK */
    retVal = (uint8) E_OK;
  }

  /* Disable interrupts to protect Tx DATA */
  SchM_Exit_CanIf_TX_QUEUE_PROTECTION();
  
  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* polyspace-end RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */

/*******************************************************************************
** Function Name        : CanIf_CheckPduInfo                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates a request for transmission of**
**                        the CAN L-PDU specified by the CanTxPduId and CAN   **
**                        related data in the L-PDU structure                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : CanTxPduId, PduInfoPtr                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_Return (E_OK or E_NOT_OK)                       **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanIf_CanIfStatus, CanIf_TxLpdu,                    **
**                        CanIf_Controller                                    **
**                        Function(s) invoked:                                **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01126 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckPduInfo (
                        #if (((STD_ON == CANIF_SETDYNAMICTXID_API) && (STD_ON == CANIF_META_DATA_SUPPORT)) || (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT))
                        VAR(PduIdType, CANIF_VAR) CanTxPduId,
                        #endif
                        P2CONST(PduInfoType, AUTOMATIC, CANIF_CONST) PduInfoPtr)
{
  #if (((STD_ON == CANIF_SETDYNAMICTXID_API) && (STD_ON == CANIF_META_DATA_SUPPORT)) || (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT))
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  #endif
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  /* Set retVal to E_OK */
  retVal = (Std_ReturnType) E_OK;

  /* @Trace: CanIf_SUD_API_317 */
  /* Get the pointer to Tx Lpdu */
  #if (((STD_ON == CANIF_SETDYNAMICTXID_API) && (STD_ON == CANIF_META_DATA_SUPPORT)) || (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT))
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  ptrTxLpdu = &CanIfTxLpdu[CanTxPduId];
  #else
  ptrTxLpdu = &CanIf_TxLpdu[CanTxPduId];
  #endif
  #endif

  /* Report to DET, if PduInfoPtr or SduDataPtr is equal to NULL.
  * Accept NULL pointer if the PDU is configured for triggered transmission. */
  /* @Trace: SWS_CANIF_00882 */
  #if (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT)
  if (CANIF_FALSE == ptrTxLpdu->TriggerTransmit)
  #endif
  {
    /* @Trace: CanIf_SUD_API_318 */
    /* polyspace +2 RTE:NIP [Not a defect:Low] "The value of PduInfoPtr->SduDataPtr has been gotten from the upper layer, no impact" */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "This Macro used to check Null of PduInfoPtr->SduDataPtr" */
    CANIF_NULL_PTR_ERROR(CANIF_TRANSMIT_SID, retVal, PduInfoPtr->SduDataPtr);
  }
  /* polyspace +10 RTE:UNR [Justified:Low] "It depends on the configuration of CanIf. No impact" */
  /* Report to DET, if MetaDataPtr is equals to NULL */
  #if ((STD_ON == CANIF_SETDYNAMICTXID_API) && \
        (STD_ON == CANIF_META_DATA_SUPPORT))
  if (CANIF_INVALID_DYNCANID != ptrTxLpdu->DynCanIdIndex)
  {
    /* @Trace: CanIf_SUD_API_319 */
    /* polyspace +2 MISRA2012:D4.14 [Not a defect:Low] "This Macro used to check Null" */
    /* "of PduInfoPtr->SduDataPtr" */
    CANIF_NULL_PTR_ERROR(CANIF_TRANSMIT_SID, retVal, PduInfoPtr->MetaDataPtr);
  }
  #endif /* MetaDataPtr is equals to NULL */
  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /* ((STD_ON == CANIF_DEV_ERROR_DETECT) && (STD_ON == CANIF_TX_LPDU)) */

/* polyspace-end RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
