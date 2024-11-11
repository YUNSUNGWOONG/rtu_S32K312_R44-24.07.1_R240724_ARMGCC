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
**  SRC-MODULE: CanIf_TxConfirm.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Transmit Confirmation module of CAN Interface                 **
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
** 1.1.0     29-Feb-2024   Jh Yang        #CP44-2947                          **
** 1.0.12    12-Dec-2022   HieuTM8        #CP44-1254                          **
** 1.0.9     03-Oct-2022   HieuTM8        #CP44-832                           **
** 1.0.5     30-Jun-2022   HieuTM8        #CP44-130                           **
** 1.0.2   	 25-Mar-2022   HieuTM8        #25534                              **
** 1.0.1     22-Sep-2021   HieuTM8        #20891                              **
** 1.0.0.3   23-Aug-2021   HieuTM8        #19470, #19526                      **
** 1.0.0     21-Dec-2020   SJ Kim         Initialization                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "CanIf_Ram.h"           /* Module RAM header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#include "CanIf_TxConfirm.h"     /* Tx Confirmation header */
#include "CanSM_CanIf.h"           /* CAN State Manager call back header file */
#include "SchM_CanIf.h"          /* SchM CanIf Header file */

#include "CanIf_Error.h"         /* Det File Check */

#include "CanIf_UserInc.h"      /* User included header file */
#if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
#include "Mirror.h"			 /* Mirroring Module header file*/
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANIF_TXCONFIRM_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_TXCONFIRM_C_AR_RELEASE_MINOR_VERSION    4
#define CANIF_TXCONFIRM_C_AR_RELEASE_REVISION_VERSION 0

/* File version information */
#define CANIF_TXCONFIRM_C_SW_MAJOR_VERSION       1
#define CANIF_TXCONFIRM_C_SW_MINOR_VERSION       1
#define CANIF_TXCONFIRM_C_SW_REVISION_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_TXCONFIRM_AR_RELEASE_MAJOR_VERSION != \
  CANIF_TXCONFIRM_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_TXCONFIRM.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_TXCONFIRM_AR_RELEASE_MINOR_VERSION != \
  CANIF_TXCONFIRM_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_TXCONFIRM.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_TXCONFIRM_AR_RELEASE_REVISION_VERSION != \
  CANIF_TXCONFIRM_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_TXCONFIRM.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_TXCONFIRM_SW_MAJOR_VERSION != CANIF_TXCONFIRM_C_SW_MAJOR_VERSION)
  #error "CANIF_TXCONFIRM.c : Mismatch in Software Major Version"
#endif
#if (CANIF_TXCONFIRM_SW_MINOR_VERSION != CANIF_TXCONFIRM_C_SW_MINOR_VERSION)
  #error "CANIF_TXCONFIRM.c : Mismatch in Software Minor Version"
#endif

/* polyspace-begin RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanIf_TxConfirmation                                **
**                                                                            **
** Service ID           : 0x13                                                **
**                                                                            **
** Description          : This service is implemented in the CAN Interface    **
**                        and called by the CAN Driver after the CAN L-PDU    **
**                        has been transmitted on the CAN controller.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant, Not for same Tx L-PDU                   **
**                                                                            **
** Input Parameters     : CanIfTxSduId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_CanIfStatus,              **
**                                            CanIf_Controller                **
**                                            CanIf_TxLpdu,                   **
**                                                                            **
**                        Function(s) invoked:Det_ReportError,                **
**                                            CanIf_QueueTransmit             **
**                                            Mirror_ReportCanFrame           **
**                                            CanIf_TxNotification            **
*******************************************************************************/
#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01009 SRS_Can_01172 SRS_BSW_00323 */
FUNC(void, CANIF_CODE) CanIf_TxConfirmation (
                                           VAR(PduIdType, CANIF_VAR) CanIfTxSduId)
{
  /* @Trace: SWS_CANIF_00007 */
  /* @Trace: SWS_CANIF_00011 */
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  VAR(uint8, CANIF_VAR) tmpVar;

  #if(STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
  VAR(uint8, CANIF_VAR) controlerId;
  P2VAR(PduInfoType, AUTOMATIC, COM_VAR) ptrPduInfoPtr;
  #endif

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  /* retVal is initialized as E_OK */
  retVal = (uint8) E_OK;
  /* polyspace +4 RTE:UNR [Justified:Low] "It depends on the configuration of CanIf. No impact" */
  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00412 */
  /* @Trace: CanIf_SUD_API_026 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_TX_CONFIRMATION_SID, retVal);

  /* Report to DET, if TxPduID is out of range */
  /* @Trace: SWS_CANIF_00410 */
  /* @Trace: CanIf_SUD_API_026 */
  /* check Lpdu out of range */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  if (CanIfTxSduId >= (PduIdType)CanIf_NoofTxLpdu) 
  #else
  if (CanIfTxSduId >= CANIF_NO_OF_TXLPDU)
  #endif
  {             
    /* @Trace: CanIf_SUD_API_346 */   
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_TX_CONFIRMATION_SID,  
                      CANIF_E_PARAM_LPDU);                               
    (retVal) = (uint8)E_NOT_OK;                                              
  }

  /* Check if any development error occurred? */
  if ((uint8) E_OK == retVal)
  #endif
  {
    /* @Trace: CanIf_SUD_API_347 */
    /* Get the pointer to requested Tx L-PDU */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrTxLpdu = &CanIfTxLpdu[CanIfTxSduId];
    #else
    ptrTxLpdu = &CanIf_TxLpdu[CanIfTxSduId];
    #endif

    #if(CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
    #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
    if((ptrTxLpdu->ControllerId) < CANIF_NO_OF_CONTROLLER)
    {
      /* polyspace +2 RTE:OBAI [Not a defect: Justified] "Pointer is not outside its bounds." */
      /* polyspace +1 RTE:IDP [Not a defect: Justified] "Pointer is not outside its bounds." */
      CanIf_TxMsgCnt[ptrTxLpdu->ControllerId]++;
    }
    else
    {
      /* Do noting */
    } 
    #else
    CanIf_TxMsgCnt[CANIF_ZERO]++;
    #endif
    #endif

    #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
    /* Get the pointer to controller */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    ptrController = &CanIf_Controller[ptrTxLpdu->ControllerId];
    #else
    /* Get the pointer to controller */
    ptrController = &CanIf_Controller[CANIF_ZERO];
    #endif
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    tmpVar = (uint8)CANIF_TX_STATUS(ptrController->PduMode);
    /* Check whether TxStatus is active as well as online */
    if ((CANIF_TX_ENABLED == tmpVar) 
    /* @Trace: SWS_CANIF_00072 */
    /* @Trace: CanIf_SUD_API_020 */    
    #if (STD_ON == CANIF_TX_OFFLINE_ACTIVE_SUPPORT)
		  || ((uint8)CANIF_TX_OFFLINE_ACTIVE == tmpVar)
    #endif
		)
    {
      /* @Trace: CanIf_SUD_API_345 */
      #if (STD_ON == CANIF_PN_SUPPORT)
      #if (STD_ON == CANIF_TXCONFIRM_POLLING_SUPPORT)
      /* Set the Status to CANIF_TX_CONFIRMED */
      CANIF_SET_TX_CONFIRMED(ptrController->PduMode);
      #endif

      /* @Trace: SWS_CANIF_00751 PnTxFilter shall be disabled */
      /* @Trace: CanIf_SUD_API_021 */
      CANIF_CLEAR_TX_PNENABLED(ptrController->PduMode);

      #endif/* #if ((STD_ON == CANIF_PN_SUPPORT) */

      #if ((STD_ON == CANIF_BASIC_CAN_TXPDU) && (STD_ON == CANIF_TX_QUEUE))
      /* Get the HTH Type */
      tmpVar = ((CANIF_HTHTYPE_MASK) & (ptrTxLpdu->HTHTypeOrTXPN));
      /* Check whether HTH type is BasicCAN */
      if (CANIF_BASIC_CAN == tmpVar)
      {
        /* @Trace: CanIf_SUD_API_346 */
        /* Transmit all the pdus in the queue */
        CanIf_QueueTransmit(ptrTxLpdu);
      }
      else
      {
        /*Do nothing*/
      }
      #endif
      /* Not to delay transmission of queued pdu
         because of direct transmission on confirmation such as gateway */
      CanIf_TxNotification(ptrTxLpdu, E_OK);

      #if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
      #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
      controlerId = ptrTxLpdu->ControllerId;
      #else
      controlerId = CANIF_ZERO;
      #endif /* #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE) */

      ptrPduInfoPtr = (PduInfoType*)&CanIf_TxPduInfoPtr[CanIfTxSduId];

      /* Check Mirroring is active or not*/
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
      if((TRUE == ptrController->MirroringActive) && (NULL_PTR != ptrPduInfoPtr->SduDataPtr))
      {
        /* @Trace: CanIf_SUD_API_347 */
        /* Invoke Mirror Report Can Frame*/
        (void)Mirror_ReportCanFrame(controlerId, ptrTxLpdu->CanId, (uint8)ptrPduInfoPtr->SduLength, ptrPduInfoPtr->SduDataPtr);
      }
      else
      {
      	/* Do nothing*/
      }
      #endif /* #if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT) */

      #if (STD_ON == CANIF_READTXPDU_NOTIFY_STATUS_API)
      if (CANIF_TX_INVALID_UL_USER != ptrTxLpdu->TxCbkUser)
      {
        /* @Trace: CanIf_SUD_API_348 */
         /* Set the Status to CANIF_TX_CONFIRMED */
         CANIF_SET_TX_CONFIRMED(ptrController->PduMode);
      }
      else
      {
      	/* Do nothing*/
      }
      #endif/* #if (STD_ON == CANIF_READTXPDU_NOTIFY_STATUS_API) */
    } 
    else /* Tx Status should be active - check for Tx_offline_Active */
    {
    	/* Do nothing*/
    }
  } /* @ #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_ReadTxNotifStatus                             **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This service provides the status of the CAN         **
**                        L-PDU requested by CanIfTxSduId. This API service   **
**                        notifies the upper layer about any transmit         **
**                        confirmation or receive indication event to the     **
**                        corresponding requested CAN L-PDU. During this      **
**                        call the CAN L-PDU notification status is reset     **
**                        inside the CAN Interface.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : CanIfTxSduId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : CanIf_NotifStatusType(CANIF_NO_NOTIFICATION,        **
**                                           CANIF_TX_RX_NOTIFICATION)        **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanIf_CanIfStatus, CanIf_BitArray                   **
**                        CanIf_TxLpdu                                        **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Det_ReportError,                                    **
**                        SchM_Enter_CanIf_TX_NOTIFSTATUS_PROTECTION,         **
**                        SchM_Exit_CanIf_TX_NOTIFSTATUS_PROTECTION           **
*******************************************************************************/
#if ((STD_ON == CANIF_TX_LPDU) && (STD_ON == CANIF_READTXPDU_NOTIFY_STATUS_API))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01130 */
FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadTxNotifStatus (
                                           VAR(PduIdType, CANIF_VAR) CanIfTxSduId)
{
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  VAR(CanIf_NotifStatusType, CANIF_VAR) notifStsType;
  VAR(uint8, CANIF_VAR) notifStsMask;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  #endif

  /* Initialize the return value with no notification */
  notifStsType = CANIF_NO_NOTIFICATION;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  retVal = (uint8) E_OK;
  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_READ_TX_NOTIF_STATUS_SID, retVal);

  /* @Trace: SWS_CANIF_00331 */
  /* @Trace: CanIf_SUD_API_030 */
  /* Report to DET, if CanIfTxSduId is out of range */
  /* Check TxLpduId range */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  if (CanIfTxSduId >= (PduIdType)CanIf_NoofTxLpdu) 
  #else
  if (CanIfTxSduId >= CANIF_NO_OF_TXLPDU) 
  #endif
  {   
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_READ_TX_NOTIF_STATUS_SID,  
            CANIF_E_INVALID_TXPDUID);                          
    (retVal) = (uint8)E_NOT_OK;                                              
  }

  /* Check whether any error occurred? */
  if ((uint8) E_OK == retVal)
  #endif
  {
    /* @Trace: CanIf_SUD_API_350 */
    /* Get the pointer to the TxLpdu from requested CanIfTxSduId */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrTxLpdu = &CanIfTxLpdu[CanIfTxSduId];
    #else
    ptrTxLpdu = &CanIf_TxLpdu[CanIfTxSduId];
    #endif

    /* Get the notification mask from the Tx L-PDU structure */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    notifStsMask = ptrTxLpdu->TxNotifyStsMask;

    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    /* Report to DET, if notification is not configured for that Tx L-PDU */
    CANIF_NOTIFICATION_STATUS_ERROR(CANIF_READ_TX_NOTIF_STATUS_SID, retVal);

    if ((uint8) E_OK == retVal)
    #endif
    {
        /* @Trace: CanIf_SUD_API_351 */
        /* Check whether notification flag is set */
        /* polyspace +2 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
        if ((CANIF_BITARRAY_SIZE >= ptrTxLpdu->TxNotifyStatusIndex) && ((uint8)CANIF_ZERO !=
        (CanIf_BitArray[ptrTxLpdu->TxNotifyStatusIndex] & notifStsMask)))
        {
          /* enter critical area */
          SchM_Enter_CanIf_TX_NOTIFSTATUS_PROTECTION();
          /* @Trace: SWS_CANIF_00393 */
          /* @Trace: CanIf_SUD_API_031 */
          /* Reset the status to zero */
          CanIf_BitArray[ptrTxLpdu->TxNotifyStatusIndex] &=
                                                      (uint8)(~(notifStsMask));
          /* Exit critical area */
          SchM_Exit_CanIf_TX_NOTIFSTATUS_PROTECTION();

          /* Return confirmation to upper layer */
          notifStsType = CANIF_TX_RX_NOTIFICATION;

        }
        else /* if (CANIF_ZERO != (CanIf_BitArray[ptrTxLpdu->...)) */
        {
        	/* Do nothing*/
        }
    }/* if (E_OK == retVal) */
  }/* if (E_OK == retVal) */
  /* Return the Notification Status */
  return(notifStsType);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        :  CanIf_GetTxConfirmationState                       **
**                                                                            **
** Service ID           :  0x19                                               **
**                                                                            **
** Description          :  This service reports, if any TX confirmation has   **
**                         been done for the whole CAN controller since the   **
**                         last CAN controller start.                         **
**                                                                            **
** Sync/Async           :  Synchronous                                        **
**                                                                            **
** Re-entrancy          :  Reentrant                                          **
**                                                                            **
** Input Parameters     :  CanController                                      **
**                                                                            **
** InOut Parameters     :  None                                               **
**                                                                            **
** Output Parameters    :  None                                               **
**                                                                            **
** Return value         :  CanIf_NotifStatusType                              **
**                                                                            **
** Preconditions        :  CanIf module must be initialized                   **
**                                                                            **
** Remarks              : Global Variable(s) :  CanIf_CanIfStatus             **
**                                              CanIf_Controller              **
**                        Function(s) invoked:  Det_ReportError               **
*******************************************************************************/
#if (STD_ON == CANIF_TXCONFIRM_POLLING_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(CanIf_NotifStatusType, CANIF_CODE)CanIf_GetTxConfirmationState (
                                             VAR(uint8, CANIF_VAR) ControllerId)
{
  VAR(CanIf_NotifStatusType, CANIF_VAR) notifStsType;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  #endif

  /* Set default status of notify */
  notifStsType = CANIF_NO_NOTIFICATION;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  retVal = (uint8) E_OK;
  /* Check if CanIf is Initialised */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_GET_TX_CONFIRM_STATE_SID, retVal);

  /* Check if the Range of controller is valid */
  /* @Trace: SWS_CANIF_00736 */
  /* @Trace: CanIf_SUD_API_027 */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_GET_TX_CONFIRM_STATE_SID, retVal);

  /* Is any DET error detected */
  if ((uint8) E_OK == retVal)
  #endif
  {
    /* @Trace: CanIf_SUD_API_352 */
    /* Set status for Tx confirmation notification */
    /* polyspace<RTE: OBAI : Not a defect : No Action Planned > array range is pre-defined */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "array range is pre-defined" */
    if (CANIF_IS_TX_CONFIRMED(CanIf_Controller[ControllerId].PduMode))
    {
      /* @Trace: CanIf_SUD_API_353 */
      /* setting Tx Rx notification as return value */
      notifStsType = CANIF_TX_RX_NOTIFICATION;
    }
    else
    {
    	/* Do nothing*/
    }
  }/* @ if (E_OK == retVal) */
  return (notifStsType);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* polyspace-end RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
