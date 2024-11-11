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
**  SRC-MODULE: CanIf_Rx.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of Receive Indication Functionality                 **
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
** 1.1.0     29-Feb-2024   Jh Yang        #CP44-2946, #CP44-2947, #CP44-3811  **
** 1.0.15    05-Jan-2024   JH Jang        #CP44-2848                          **
** 1.0.14    12-Jun-2023   HieuTM8        #CP44-2289                          **
** 1.0.12    12-Dec-2022   HieuTM8        #CP44-1254                          **
** 1.0.10    27-Oct-2022   HieuTM8        #CP44-1008, #CP44-1006              **
** 1.0.9     04-Oct-2022   HieuTM8        #CP44-832, #CP44-896, #CP44-899     **
** 1.0.6     25-Jul-2022   HieuTM8        #CP44-444                           **
** 1.0.5     30-Jun-2022   HieuTM8        #CP44-130                           **
** 1.0.3     14-Apr-2022   HieuTM8        #26257                              **
** 1.0.2     25-Mar-2022   HieuTM8,JW Oh  #25353, #25534                      **
** 1.0.1     22-Sep-2021   HieuTM8        #20891, #19125, #19167              **
** 1.0.0.3   23-Aug-2021   HieuTM8        #19470, #19526                      **
** 1.0.0     21-Dec-2020   SJ Kim         Initialization                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_Ram.h"           /* RAM header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#include "CanIf_Rx.h"            /* Receive header */
#include "CanSM_CanIf.h"           /* CAN State Manager call back header file */
#include "SchM_CanIf.h"          /* SchM CanIf Header file */
#include "CanIf_Can.h"           /* CAN Driver Module Header File */
#include "CanIf_Error.h"         /* CanIf DET file */

#if (STD_ON == CANIF_AUTRON_CANTRCV_SUPPORT)
#include "CanTrcv.h"            /* CanTrcv header file */
#endif
#if (STD_ON == CANIF_EXTENAL_CANTRCV_SUPPORT)
#include "CanIf_CanTrcv.h"            /* CanTrcv header file */
#endif
#include "CanIf_UserInc.h"
#if (STD_ON == CANIF_IDSM_SUPPORT)
#include "IdsM.h"            /* IdsM Module header file */
#endif
#if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
/* @Trace: SWS_CANIF_00903 */
#include "Mirror.h"			 /* Mirroring Module header file*/
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANIF_RX_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_RX_C_AR_RELEASE_MINOR_VERSION    4
#define CANIF_RX_C_AR_RELEASE_REVISION_VERSION 0

/* File version information */
#define CANIF_RX_C_SW_MAJOR_VERSION       1
#define CANIF_RX_C_SW_MINOR_VERSION       1
#define CANIF_RX_C_SW_REVISION_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_RX_AR_RELEASE_MAJOR_VERSION != \
  CANIF_RX_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_RX.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_RX_AR_RELEASE_MINOR_VERSION != \
  CANIF_RX_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_RX.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_RX_AR_RELEASE_REVISION_VERSION != \
  CANIF_RX_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_RX.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_RX_SW_MAJOR_VERSION != CANIF_RX_C_SW_MAJOR_VERSION)
  #error "CANIF_RX.c : Mismatch in Software Major Version"
#endif
#if (CANIF_RX_SW_MINOR_VERSION != CANIF_RX_C_SW_MINOR_VERSION)
  #error "CANIF_RX.c : Mismatch in Software Minor Version"
#endif

/* polyspace-begin RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : CanIf_RxNotification                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service provides the Rx Indication to the      **
**                        respective upper layers                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrRxLpdu, CanDlc                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value        : None                                                 **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_CanIfStatus               **
**                                            CanIf_RxCbkUser                 **
**                        Function(s) invoked:Det_ReportError,                **
**                                            CanIf_RxStatusUpdate            **
**                                            IdsM_MsgReceptionReport         **
*******************************************************************************/
#if (STD_ON == CANIF_RX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01005 SRS_Can_01005 */
FUNC(void, CANIF_CODE) CanIf_RxNotification (
    P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu,
    P2CONST(PduInfoType, AUTOMATIC, CANIF_CONST) PduInfoPtr)
{
  /* @Trace: SWS_CANIF_00026 */
  P2CONST(CanIf_RxCbkUserType, AUTOMATIC, CANIF_CONST) ptrRxCbkUser;
  VAR(PduIdType, CANIF_VAR) targetId;
  VAR(uint8, CANIF_VAR) tmpVar;

  #if (STD_ON == CANIF_PRIVATE_DATA_LENGTH_CHECK)
  VAR(uint8, CANIF_VAR) dataLenCheck;
  #endif

  #if (STD_ON == CANIF_PRIVATE_DATA_LENGTH_CHECK)
  dataLenCheck = E_OK;
  #endif
  /* @Trace: SWS_CANIF_00026 SWS_CANIF_00390 SWS_CANIF_00902 SWS_CANIF_00830 SWS_CANIF_00829 */
  /* @Trace: CanIf_SUD_API_040 */
  /* @Trace: CanIf_SUD_API_046 */
  #if (STD_ON == CANIF_PRIVATE_DATA_LENGTH_CHECK )
  if (CANIF_TRUE == ptrRxLpdu->DataLengthCheck)
  {
    if (ptrRxLpdu->Dlc > PduInfoPtr->SduLength)
    {
      /* @Trace: CanIf_SUD_API_230 */
      dataLenCheck = E_NOT_OK;
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

  if(dataLenCheck == E_OK)
  #endif
  {
    #if (STD_ON == CANIF_IDSM_SUPPORT)
    if (CANIF_ZERO != (ptrRxLpdu->RxUserOrNotifSts & CANIF_RX_IDSM_REPORT_MASK))
    {
      /* @Trace: CanIf_SUD_API_231 */
      IdsM_MsgReceptionReport(ptrRxLpdu->RxPduId, PduInfoPtr);
    }
    else
    {
      /* Do nothing */
    }
    #endif
    #if ((STD_ON == CANIF_RX_LPDU) && (STD_ON == CANIF_TX_RX_MONITORING_SUPPORT))
    CanIf_ReceiveCnt[ptrRxLpdu->RxPduId]++;
    #endif
    
    #if ((STD_ON == CANIF_READRXPDU_NOTIFY_STATUS_API) || \
                                         (STD_ON == CANIF_READRXPDU_DATA_API))
    /* Invoke CanIf_RxStatusUpdate for updation of RxPdu structure */
    /* @Trace: SWS_CANIF_00392 */
    CanIf_RxStatusUpdate(ptrRxLpdu, PduInfoPtr);
    #endif

    /* Get the upper layer user into local variable */
    tmpVar = ((CANIF_UL_MASK) & (ptrRxLpdu->RxUserOrNotifSts));

    /* Check whether any upper layer is configured for upper layer indication */
    if (CANIF_MAX_UL >= tmpVar)
    {
      /* Get TargetId */
      targetId = (PduIdType)ptrRxLpdu->TargetId;
      /* polyspace-begin RTE:COR [Not a defect:Low] "Its value has been checked by the generator, can not be NULL" */
      /* @Trace: SWS_CANIF_00415, SWS_CANIF_00056 */
      /* @Trace: CanIf_SUD_API_046 */
      #if (CANIF_RX_MULTIPLE_CALLBACK == STD_ON)
      /* Get the pointer to RxCbkUser structure */
      ptrRxCbkUser = &CanIf_RxMulCbkUser[ptrRxLpdu->CallbackIndex];

      /* invoke the respective upper layer Indication for received PDU */
      ptrRxCbkUser->RxIndication(targetId, PduInfoPtr);

      #else
      /* Get the pointer to RxCbkUser structure */
      ptrRxCbkUser = &CanIf_RxSingleCbkUser[tmpVar];

      /* invoke the respective upper layer Indication for received PDU */
      ptrRxCbkUser->RxIndication(targetId, PduInfoPtr);
      /* polyspace-end RTE:COR [Not a defect:Low] "Its value has been checked by the generator, can not be NULL" */
      #endif
    } 
    else /*  if (CANIF_MAX_UL >= tmpVar) */
    {
    	/* Do nothing */
    }
  } 
  #if (STD_ON == CANIF_PRIVATE_DATA_LENGTH_CHECK) && (STD_ON == CANIF_DEV_ERROR_DETECT)
  else /* if (ptrRxLpdu->Dlc <= discreteLen) */
  {
    /* Report to DET for invalid DLC*/
    /* @Trace: SWS_CANIF_00168 */
    /* @Trace: CanIf_SUD_API_047 */
    (void)Det_ReportRuntimeError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                          CANIF_RX_INDICATION_SID, CANIF_E_INVALID_DATA_LENGTH);
  }
  #endif /*(STD_ON == CANIF_PRIVATE_DATA_LENGTH_CHECK) && (STD_ON == CANIF_DEV_ERROR_DETECT)*/

}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON == CANIF_RX_LPDU) */

/*******************************************************************************
** Function Name        : CanIf_RxIndication                                  **
**                                                                            **
** Service ID           : 0x14                                                **
**                                                                            **
** Description          : This service indicates a L-PDU reception of a       **
**                        CAN L-PDU in any of the CAN drivers. This           **
**                        service performs software filtering and DLC check.  **
**                        On successful completion of software filtering and  **
**                        DLC check the upper layer is notified with          **
**                        respective upper layer call back function.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant but not for same HRH                     **
**                                                                            **
** Input Parameters     : Mailbox, PduInfoPtr                                 **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_CanIfStatus               **
**                                            CanIf_Controller                **
**                                            CanIf_HrhMapArray               **
**                                            CanIf_Hrh                       **
**                                            CanIf_RxCanId                   **
**                        Function(s) invoked:CanIf_RxNotification            **
**                                            SchM_Enter_CanIf_MODE_STATUS_   **
**                                            PROTECTION,                     **
**                                            SchM_Exit_CanIf_MODE_STATUS_    **
**                                            PROTECTION,                     **
**                                            Det_ReportError,                **
**                                            CanIf_TriggerSWFilter           **
*******************************************************************************/
#if (STD_ON == CANIF_RX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 SRS_Can_01151 SRS_Can_01172 SRS_Can_01004
           SRS_Can_01002 SRS_Can_01003 SRS_Can_01018 SRS_Can_01159 */
FUNC(void, CANIF_CODE) CanIf_RxIndication(
                          P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_CONST) Mailbox,
                          P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr)
{
  /* @Trace: SWS_CANIF_00006 */
  /* @Trace: SWS_CANIF_00012 */
  P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu;
  P2CONST(CanIf_HrhType, AUTOMATIC, CANIF_CONST) ptrHrh;
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  VAR(uint8, CANIF_VAR) rxStatus;
  VAR(uint8, CANIF_VAR) sftwrFltrng;
  VAR(uint8, CANIF_VAR) hrhOffSetId;
  VAR(uint8, CANIF_VAR) canFrameType;
  VAR(Can_HwHandleType, CANIF_VAR) hrh;
  VAR(Can_IdType, CANIF_VAR) canId;
  VAR(PduInfoType, CANIF_VAR) pduInfo;
  VAR (Can_IdType, CANIF_VAR) metadata;

  #if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
  VAR(uint8, CANIF_VAR) controlerId;
  #endif

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(uint8, CANIF_VAR) retVal;
  #endif

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  retVal = CanIf_DETRxindication(Mailbox,PduInfoPtr);  
  /* polyspace +2 RTE:UNR [Justified:Low] "It depends on the configuration of CanIf. No impact" */
  /* Check whether any development errors are detected ?*/
  if ((uint8) E_OK == retVal)
  #endif /* if development error is not enabled */
  { 
    /* @Trace: CanIf_SUD_API_232 */   
    /* Get the pointer to HRH structure */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrHrh = &CanIfHrh[CANIF_ZERO];
    #else
    ptrHrh = &CanIf_Hrh[CANIF_ZERO];
    #endif

    /* polyspace +2 MISRA2012:D4.14 [Not a defect:Low] "Its value is checked by Det" */
    hrh = Mailbox->Hoh;
    canId = Mailbox->CanId;

    #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)  
    hrhOffSetId = CanIfControllerConfig[Mailbox->ControllerId].CanDriverId;
    hrhOffSetId = CanIfHrhInit[hrhOffSetId].HrhOffSetId;
    #else
    hrhOffSetId = CanIf_ControllerConfig[Mailbox->ControllerId].CanDriverId;
    hrhOffSetId = CanIf_HrhInit[hrhOffSetId].HrhOffSetId;
    #endif
    #else
    hrhOffSetId = CANIF_ZERO;
    #endif

    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    /* polyspace +4 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
    ptrHrh = &ptrHrh[(CanIf_PtrSize)CanIfHrhMapArray[hrh + hrhOffSetId]];
    #else
    ptrHrh = &ptrHrh[(CanIf_PtrSize)CanIf_HrhMapArray[hrh + hrhOffSetId]];
    #endif

    #if(CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
    #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
    /* polyspace +2 RTE:IDP [Not a defect: Justified] "Pointer is not outside its bounds." */
    /* polyspace +1 RTE:OBAI [Not a defect: Justified] "Pointer is not outside its bounds." */
    CanIf_RxMsgCnt[ptrHrh->ControllerId]++;
    #else
    CanIf_RxMsgCnt[CANIF_ZERO]++;
    #endif
    #endif

    /*Get Controller Id*/
    #if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
    controlerId = Mailbox->ControllerId;
    #endif

    #if (CANIF_NO_OF_CONTROLLER > CANIF_ONE)
    /* Get the pointer to Controller */
    ptrController = &CanIf_Controller[Mailbox->ControllerId];
    #else
    /* Get the pointer to Controller */
    ptrController = &CanIf_Controller[CANIF_ZERO];
    #endif
    /* Get can frame type */
    canFrameType = (uint8)((canId & CANIF_FRAME_TYPE_MASK) >> CANIF_FRAME_TYPE_SHIFT);

    /* Get the actual can id (excluding the two most significant bits) */
    canId = canId & CANIF_CANID_MASK_FOUR;
    /* Save CAN identifier to global variable */
    CanIf_RxCanId = canId;

    /* @Trace: SWS_CANIF_00896 PnTxFilter shall be disabled */
    /* @Trace: CanIf_SUD_API_032 */
    /* polyspace +2 RTE:IDP [Not a defect:Low] "Its checked by Det" */
    #if (STD_ON == CANIF_PN_SUPPORT)
    if (CANIF_IS_TX_PNENABLED(ptrController->PduMode))
    {
      /* @Trace: CanIf_SUD_API_233 */
      /* Tx Status of controller is updated - Clear PNEABLE*/
      CANIF_CLEAR_TX_PNENABLED(ptrController->PduMode);
    }
    else
    {
    	/* Do nothing */
    }
    #endif

    /* Check if Rx status of controller is set */
    rxStatus = CANIF_RX_STATUS(ptrController->PduMode);

    /* Check the rx status of controller is not disabled */
    if (CANIF_RX_DISABLED != rxStatus)
    {
      /* @Trace: CanIf_SUD_API_234 */
      /* Get SDU length */
      pduInfo.SduLength = PduInfoPtr->SduLength;

      /* Get SDU data pointer */
      pduInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
      
      /* Check whether that HRH is FullCAN or BasicCAN */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Its covered by generation" */
      sftwrFltrng = ptrHrh->FilterMethod;
      /* Filter Method :
         0x00: -> BasicCAN WITH STANDARD
         0x01: -> BASICCAN WITH EXTENDED
         0x02: -> BASICCAN WITH MIXED
         0x03: -> FULLCAN WITH STANDARD
         0x04: -> FULLCAN WITH EXTENDED
         0x05: -> FULLCAN WITH MIXED
      Check whether received CAN-ID is type of FullCAN or BasicCAN */
      /* @Trace: SWS_CANIF_00663 SWS_CANIF_00389*/	  
      /* @Trace: CanIf_SUD_API_036 */
      ptrRxLpdu = CanIf_Filtering(sftwrFltrng, ptrHrh, canId, canFrameType, &metadata);

      if (NULL_PTR != ptrRxLpdu)
      {
        /* polyspace +7 RTE:UNR [Justified:Low] "It depends on the configuration of CanIf. No impact" */
        /* polyspace +2 RTE:IDP [Not a defect:Low] "Its covered by generation" */
        #if (STD_ON == CANIF_META_DATA_SUPPORT)
        if (CAN_ID_32 == (ptrRxLpdu->MetaDataType))
        {
          /* @Trace: CanIf_SUD_API_235 */
          pduInfo.MetaDataPtr = (uint8*) &metadata;
        }
        else
        {
          /* @Trace: CanIf_SUD_API_236 */
          pduInfo.MetaDataPtr = NULL_PTR;
        }
        #else
        pduInfo.MetaDataPtr = NULL_PTR;
        #endif
        /* Invoke CanIf_RxNotification to invoke upper layer indication */
        /* @Trace: SWS_CANIF_00390 */
        CanIf_RxNotification(ptrRxLpdu, &pduInfo);

        /* @Trace: SWS_CANIF_00906 */
        /* @Trace: CanIf_SUD_API_037 */
        #if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
        /* Check Mirroring is active or not*/
        if(TRUE == ptrController->MirroringActive)
        {
          /* @Trace: CanIf_SUD_API_237 */
          /* Invoke Mirror Report Can Frame*/
          (void)Mirror_ReportCanFrame(controlerId, canId, (uint8)pduInfo.SduLength,
                                pduInfo.SduDataPtr);
        }
        else
        {
        	/* Do nothing*/
        }
        #endif
      }
      else /* (NULL_PTR != ptrRxLpdu) */
      {
        /* Do nothing */
      }

      #if ((STD_ON == CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT))
      /* Disable relevant interrupts */
      SchM_Enter_CanIf_MODE_STATUS_PROTECTION();
      
      /* @Trace: SWS_CANIF_00286 */
      /* @Trace: CanIf_SUD_API_038 */
      #if (STD_ON == CANIF_PUBLIC_WAKEUP_CHECK_VALID_BYNM)
      if((NULL_PTR != ptrRxLpdu) && (CANIF_CANNM/*NM*/ 
        == (ptrRxLpdu->RxUserOrNotifSts & CANIF_CANNM)))
      {
        /* @Trace: CanIf_SUD_API_238 */
        /* Set the wakeup validation flag */
        CANIF_SET_RX_VALIDATE_WAKEUP(ptrController->PduMode);
      }
      else
      {
        /* Do nothing */
      }
      #else

      /* Set the wakeup validation flag */
      CANIF_SET_RX_VALIDATE_WAKEUP(ptrController->PduMode);
      #endif

      /* Enable relevant interrupts */
      SchM_Exit_CanIf_MODE_STATUS_PROTECTION();

      #endif
    }
    else /* if (CANIF_RX_DISABLED != rxStatus) */
    {
    	/* Do nothing */
    }
  } /* if CANIF_DEV_ERROR_DETECT */
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_ReadRxNotifStatus                             **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This service provides the status of the CAN Rx      **
**                        L-PDU requested by CanRxPduId. This API service     **
**                        notifies the upper layer about any transmit         **
**                        confirmation or receive indication event to the     **
**                        corresponding requested CAN Rx L-PDU.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : CanIfRxSduId                                        **
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
** Remarks              : Global Variable(s): CanIf_CanIfStatus               **
**                                            CanIf_Controller                **
**                                            CanIf_RxLpduNotify              **
**                        Function(s) invoked:Det_ReportError                 **
**                                            SchM_Enter_CanIf_RX_NOTIFSTATUS_**
**                                            PROTECTION,                     **
**                                            SchM_Exit_CanIf_RX_NOTIFSTATUS_ **
**                                            PROTECTION                      **
**                                                                            **
*******************************************************************************/
#if (STD_ON == CANIF_READRXPDU_NOTIFY_STATUS_API) /* @Trace: SWS_CANIF_00340 */
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01130, SRS_Can_01131 */
FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadRxNotifStatus (
                                       VAR(PduIdType, CANIF_VAR) CanIfRxSduId)
{
  P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu;
  P2VAR(CanIf_RxLpduNotifyType, AUTOMATIC, CANIF_VAR) ptrRxLpduNotify;
  CanIf_NotifStatusType notifStsType;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(uint8, CANIF_VAR) notifStatus;
  VAR(uint8, CANIF_VAR) retVal;
  #endif

  VAR(uint8, CANIF_VAR) pdu;
  VAR(uint16, CANIF_VAR) rxPduCnt;  

  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  rxPduCnt = CanIf_NoofRxLpdu;
  #else
  rxPduCnt = CANIF_NO_OF_RXLPDU;
  #endif

  pdu = CANIF_FALSE;

  /* Initialize notifStsType to CANIF_NO_NOTIFICATION */
  notifStsType = CANIF_NO_NOTIFICATION;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  retVal = CANIF_ZERO;

  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_READ_RX_NOTIF_STATUS_SID, retVal);

  /* Report to DET, if RXPDUID is not in limits */
  /* @Trace: SWS_CANIF_00336 */
  /* @Trace: CanIf_SUD_API_024 */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  if (CanIfRxSduId >= CanIf_NoofRxLpdu)
  #else
  if (CanIfRxSduId >= CANIF_NO_OF_RXLPDU)
  #endif
  {
    /* @Trace: CanIf_SUD_API_239 */
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                    CANIF_READ_RX_NOTIF_STATUS_SID, CANIF_E_INVALID_RXPDUID);
    retVal++;
  }
  else
  {
  	/* Do nothing */
  }

  #if (STD_OFF == CANIF_READRXPDU_DATA_API)
  (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                  CANIF_READ_RX_NOTIF_STATUS_SID, CANIF_E_INVALID_RXPDUID);
  retVal++;
  #endif

  if ((uint8)CANIF_ZERO == retVal)
  #endif
  {
    /* @Trace: CanIf_SUD_API_240 */
    /* Get the pointer to first Rx L-PDU of range/list type */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrRxLpdu = &CanIfRxLpdu[CANIF_ZERO];
    #else
    ptrRxLpdu = &CanIf_RxLpdu[CANIF_ZERO];
    #endif

    /* Get the pointer to desired Rx L-PDU of range/list type */
    do
    {
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
      if (CanIfRxSduId != (PduIdType)ptrRxLpdu->RxPduId)
      {
        /* @Trace: CanIf_SUD_API_241 */
        ptrRxLpdu++;
        rxPduCnt--;
      }
      else
      {
        /* @Trace: CanIf_SUD_API_242 */
        #if (STD_ON == CANIF_DEV_ERROR_DETECT)
        notifStatus = ptrRxLpdu->RxUserOrNotifSts;

        /* Report to DET if Status information is not available for RxPDU*/
        if ((notifStatus & CANIF_RX_NOTIFY_STATUS_MASK) == CANIF_ZERO)
        {
          /* @Trace: CanIf_SUD_API_243 */
          (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                          CANIF_READ_RX_NOTIF_STATUS_SID, CANIF_E_INVALID_RXPDUID);
          retVal++;
        }
        else /* @ if ((notifStatus & 0x10) == CANIF_ZERO) */
        {
        	/* Do nothing */
        }
        #endif

        /* to break the loop */
        pdu = CANIF_TRUE;
      }
    } while ((CANIF_TRUE != pdu) && (CANIF_ZERO != rxPduCnt));

    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    /* Check whether any development error are detected */
    if ((uint8)CANIF_ZERO == retVal)
    #endif
    {
      if (CANIF_TRUE == pdu)
      {
        /* @Trace: CanIf_SUD_API_244 */
        /* Get the pointer to RxLpduNotify structure */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
        ptrRxLpduNotify = &CanIf_RxLpduNotify[ptrRxLpdu->RxNotifyId];

        /* Check whether RxLpduStatus is set or not */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
        if ((ptrRxLpduNotify->DlcOrNotify & CANIF_NOTIFY_STATUS_MASK) !=
                                                              (uint8)CANIF_ZERO)
        {
          /* Disable relevant interrupts */
          SchM_Enter_CanIf_RX_NOTIFSTATUS_PROTECTION();

          /* @Trace: SWS_CANIF_00394 */
          /* @Trace: CanIf_SUD_API_025 */
          /* Reset the notification status */
          ptrRxLpduNotify->DlcOrNotify &= CANIF_CLEAR_NOTIFY_STATUS;
          /* Enable relevant interrupts */
          SchM_Exit_CanIf_RX_NOTIFSTATUS_PROTECTION();

          /* Set Rx notification to an upper layer */
          notifStsType = CANIF_TX_RX_NOTIFICATION;

        } 
        else /*  if ((ptrRxLpduNotify->DlcOrNotify & ... */
        {
        	/* Do nothing */
        }
      } 
      else /* @ if (pdu == CANIF_TRUE) */
      {
      	/* Do nothing */
      }
    } /* @ if ((uint8) E_OK == retVal) */
  }/* @ if (E_OK == retVal)*/
  return(notifStsType);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_ReadRxPduData                                 **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : This service provides the CAN DLC and the received  **
**                        data of the requested CanRxPduId to the calling     **
**                        upper layer.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : CanIfRxSduId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : PduInfoPtr                                          **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s):  CanIf_CanIfStatus              **
**                                             RxBufferData                   **
**                                             CanIf_RxLpduNotify             **
**                                             CanIf_Controller               **
**                        Function(s) invoked: Det_ReportError                **
**                                             SchM_Enter_CanIf_RX_DATA_      **
**                                             PROTECTION                     **
**                                             SchM_Exit_CanIf_RX_DATA_       **
**                                             PROTECTION                     **
*******************************************************************************/
#if (STD_ON == CANIF_READRXPDU_DATA_API)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01125, SRS_Can_01129 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ReadRxPduData (
                      VAR(PduIdType, CANIF_VAR) CanIfRxSduId,
                      P2VAR(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr)
{
  P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu;
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  P2VAR(CanIf_RxLpduNotifyType, AUTOMATIC, CANIF_VAR) ptrRxLpduNotify;
  P2VAR (uint8, AUTOMATIC, CANIF_VAR) ptrDataPtr;
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  VAR(uint8, CANIF_VAR) dlc;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(uint8, CANIF_VAR) notifStatus;  
  #endif

  VAR(uint8, CANIF_VAR) pdu;
  VAR(uint16, CANIF_VAR) rxPduCnt; 
  pdu = CANIF_FALSE;

  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  rxPduCnt = CanIf_NoofRxLpdu;
  #else
  rxPduCnt = CANIF_NO_OF_RXLPDU;
  #endif

  #if (STD_OFF == CANIF_DEV_ERROR_DETECT)
  retVal = E_OK;
  #else
  /* Initialize standard return type to E_OK */
  retVal = CanIf_DETReadRxPduData(CanIfRxSduId, PduInfoPtr);

  if ((uint8)CANIF_ZERO == retVal)
  #endif
  {
    /* @Trace: CanIf_SUD_API_249 */
    /* Get the pointer to first Rx L-PDU of range/list type */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrRxLpdu = &CanIfRxLpdu[CANIF_ZERO];
    #else
    ptrRxLpdu = &CanIf_RxLpdu[CANIF_ZERO];
    #endif

    /* Get the RxNotifyId */
    do
    {
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Its covered by generation" */
      if (CanIfRxSduId != (PduIdType)ptrRxLpdu->RxPduId)
      {
        /* @Trace: CanIf_SUD_API_250 */
        ptrRxLpdu++;
        rxPduCnt--;
      } 
      else
      {
        /* @Trace: CanIf_SUD_API_251 */
        #if (STD_ON == CANIF_DEV_ERROR_DETECT)
        notifStatus = ptrRxLpdu->RxUserOrNotifSts;

        /* Report to DET if Read data is not available for RxPDU*/
        if (CANIF_ZERO == (notifStatus & CANIF_RX_DATA_STATUS_MASK))
        {
          /* @Trace: CanIf_SUD_API_252 */
          (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                          CANIF_READ_RXPDU_DATA_SID, CANIF_E_INVALID_RXPDUID);
          retVal++;
        }
        else
        {
          /* Do nothing */
        }
        #endif /* (STD_ON == CANIF_DEV_ERROR_DETECT) */
        pdu = CANIF_TRUE;
      }
    } while ((CANIF_TRUE != pdu) && (CANIF_ZERO != rxPduCnt));
    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    /* Check whether any development error are detected */
    if ((uint8)CANIF_ZERO == retVal)
    #endif
    {
      if (CANIF_TRUE == pdu)
      {
        /* @Trace: CanIf_SUD_API_253 */
        /* Set the retVal */
        retVal = (Std_ReturnType)E_NOT_OK;

        /* Point to Controller */
        /* polyspace +4 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
        ptrController =  &CanIf_Controller[ptrRxLpdu->ControllerId];

        /* Check if controller mode is started (CAN_CS_STARTED)*/
        if (CANIF_STARTED == ptrController->ControllerMode)
        {
          /* Check RxStatus of controller */
          if (CANIF_RX_DISABLED != CANIF_RX_STATUS(ptrController->PduMode))
          {
            /* @Trace: CanIf_SUD_API_254 */
            /* Set the retVal */
            retVal = (Std_ReturnType)E_OK;

            /* Get the pointer to RxLpduNotify structure */
            /* polyspace +4 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
            ptrRxLpduNotify = &CanIf_RxLpduNotify[ptrRxLpdu->RxNotifyId];

            /* Get the DLC */
            dlc = ((ptrRxLpduNotify->DlcOrNotify) & (CANIF_RX_DLC_STATUS_MASK));

            /* Store Length */
            PduInfoPtr->SduLength = (uint8)dlc;

            /* Get the pointer to SduDataPtr */
            ptrDataPtr = (PduInfoPtr->SduDataPtr);

            /* Disable relevant interrupts */
            SchM_Enter_CanIf_RX_DATA_PROTECTION();

            /* Loop to copy the data from BufferData to DataPtr */
            while ((uint8)CANIF_ZERO != dlc)
            {
              /* @Trace: CanIf_SUD_API_255 */
              /* Decrement DLC counter */
              dlc--;

              /* Copy the data */
	      /* polyspace +2 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
	      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
              ptrDataPtr[dlc] = ptrRxLpduNotify->RxBufferData[dlc];
              /* Increment buffer pointer by one */
            }
            /* Enable relevant interrupts */
            SchM_Exit_CanIf_RX_DATA_PROTECTION();
          }
          else /* @ if (E_OK == retVal) */
          {
            /* Do nothing */
          }
        }
        else /* @ if ((uint8) CAN_CS_STARTED == ptrController->ControllerMode) */
        {
        	/* Do nothing */
        }
      } /* @ if (pdu == CANIF_TRUE) */
    }/* @ if (E_OK == retVal) */
  }/* @ if (E_OK == retVal) */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  else
  {
    /* @Trace: CanIf_SUD_API_256 */
    retVal = (uint8)E_NOT_OK;
  }
  #endif
  /* Return std return value */
  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_RxData                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service provides the Rx Indication to the      **
**                        respective upper layers                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrRxLpdu, CanDlc                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : None                                                **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s): None                            **
**                                                                            **
**                        Function(s) invoked:None                            **
*******************************************************************************/
#if ((STD_ON == CANIF_RX_LPDU) && (STD_ON == CANIF_META_DATA_SUPPORT))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_RxData (Can_IdType CanId,
    P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu,
    P2VAR(Can_IdType, AUTOMATIC, CANIF_VAR) metadata)
{
  VAR(Can_IdType, CANIF_VAR) canId;
  canId = CanId;
  P2VAR(uint8, AUTOMATIC, CANIF_VAR) ptrMetadata = (uint8*)metadata;
  /* Get metadata from CanId */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined, cover by generation" */
  if (CAN_ID_32 == ptrRxLpdu->MetaDataType)
  {
    /* @Trace: CanIf_SUD_API_034 */
    if (CANIF_FOUR == ptrRxLpdu->MetaDataLength)
    {
      /* @Trace: CanIf_SUD_API_257 */
      /* Get actual CanId */
      canId = canId & CANIF_CANID_MASK_FOUR; /* CANIF_CANID_MASK_FOUR = 0x1FFFFFFF */
      
      /* @ CANIF_MASK_BYTE_FOUR = 0XFF000000U ; CANIF_TWENTY_FOUR = 24 */
      ptrMetadata[0] = (uint8)((canId & CANIF_MASK_BYTE_FOUR) >> CANIF_TWENTY_FOUR);

      /* @ CANIF_MASK_BYTE_THREE = 0X00FF0000 ; CANIF_SIXTEEN = 16 */
      ptrMetadata[1] = (uint8)((canId & CANIF_MASK_BYTE_THREE) >> CANIF_SIXTEEN);

      /* @ CANIF_MASK_BYTE_ONE = 0XFF00 ; CANIF_EIGHT = 8 */
      ptrMetadata[2] = (uint8)((canId & CANIF_MASK_BYTE_ONE) >> CANIF_EIGHT);

      /* CANIF_CANID_MASK_ONE = 0xFF */
      ptrMetadata[3] = (uint8)(canId & CANIF_CANID_MASK_ONE);
    }
  }
  else
  {
    /* @Trace: SWS_CANIF_00856 */
    /* @Trace: CanIf_SUD_API_035 */
    /*Do nothing*/
  }

}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_BinarySearch                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to implement the Binary       **
**                        search                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrHrh, size, canId                                 **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : ptrRxLpdu                                           **
**                                                                            **
** Return Value         : CanIf_RxLpduTypePtr                                 **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/
#if ((STD_ON == CANIF_BINARY_SEARCH)||(STD_ON == CANIF_IDTABLE_SEARCH))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01140 SRS_Can_01141 SRS_Can_01162 */
FUNC(CanIf_RxLpduTypePtr, CANIF_CODE)
                         CanIf_BinarySearch (
                         P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu,
                         VAR(PduIdType, CANIF_VAR) size,
                         VAR(Can_IdType, CANIF_VAR) canId,
                         VAR(uint8, CANIF_VAR) canFrameType)
{
  P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpduRetVal;
  VAR(Can_IdType, CANIF_VAR) listCanId;
  VAR(PduIdType, CANIF_VAR) low;
  VAR(PduIdType, CANIF_VAR) high;
  VAR(PduIdType, CANIF_VAR) mid;
  
  /* Initialize high variable with number of List L-PDUs - 1 */
  high = size - (PduIdType)CANIF_ONE;

  /* Initialize low variable with zero */
  low = (PduIdType)CANIF_ONE;

  /* Initialize return value with null pointer */
  ptrRxLpduRetVal = NULL_PTR;

  /* Get the lower limit of CAN-ID */
  /* polyspace +5 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
  listCanId = (ptrRxLpdu->RxPduCanId);

  /* Check whether search CAN-ID is in range */
  if ((canId >= ptrRxLpdu->RxLowerCanId) && (canId <= ptrRxLpdu[high].RxUpperCanId))
  {
    /* @Trace: CanIf_SUD_API_147 */
    /* Check whether requested CAN-ID is same as first CAN-ID of the list */
    #if ((STD_ON == CANIF_RX_LPDU) && (STD_ON == CANIF_META_DATA_SUPPORT))
    if ((canId & (ptrRxLpdu->CanIfRxPduCanIdMask)) !=
              (listCanId &(ptrRxLpdu->CanIfRxPduCanIdMask)))
    #else
    /* Check whether requested CAN-ID is same as first CAN-ID of the list */
    if (canId != listCanId)
    #endif
    {
      do
      {
        /* @Trace: CanIf_SUD_API_258 */
        /* Get the middle index number */
        mid = (high + low) >> (PduIdType)CANIF_ONE;
        /* Get the CAN-ID of the mid Rx L-PDU */
        listCanId = (Can_IdType)((ptrRxLpdu[mid]).RxPduCanId);
        /* if rxcanid range is not config */
        if (CANIF_INVALID_RXCANIDRANGE == ptrRxLpdu->RxUpperCanId)
        {
          /* Compare CAN-ID with the requested one */
          #if ((STD_ON == CANIF_RX_LPDU) && (STD_ON == CANIF_META_DATA_SUPPORT))
          if ((canId & ((ptrRxLpdu[mid]).CanIfRxPduCanIdMask)) == 
              (listCanId &((ptrRxLpdu[mid]).CanIfRxPduCanIdMask)))
          #else
          if (listCanId == canId)
          /* @Trace: SWS_CANIF_00877 */
          #endif
          {
            if (CanIf_CheckRxPduCanIdType(&ptrRxLpdu[mid], canFrameType) == (Std_ReturnType)E_OK)
            {
              /* @Trace: CanIf_SUD_API_148 */
              /* Update the return pointer with the Rx L-PDU structure */
              ptrRxLpduRetVal = &ptrRxLpdu[mid];
            }
            /* Set high to zero to break the loop */
            high = (PduIdType)CANIF_ZERO;
          }
          else
          {
            if (mid == (PduIdType)CANIF_ZERO)
            {
              /* Set high to zero to break the loop */
              high = (PduIdType)CANIF_ZERO;            
            }
            /* @Trace: CanIf_SUD_API_259 */
            /* Compare the CAN-ID with the requested one */
            else if (canId < listCanId)
            {
              /* If the priority is lower, update high */
              high = mid - (PduIdType)CANIF_ONE;
            }
            else
            {
              /* @Trace: CanIf_SUD_API_260 */
              /* If the priority is higher, update low */
              low = mid + (PduIdType)CANIF_ONE;
            }
          }
        }
        else /* if rxcanid range is config */
        {
          if ((canId >= ptrRxLpdu[mid].RxLowerCanId) &&
              (canId <= ptrRxLpdu[mid].RxUpperCanId))
          {
            if (CanIf_CheckRxPduCanIdType(&ptrRxLpdu[mid], canFrameType) == (Std_ReturnType)E_OK)
            {
              /* @Trace: CanIf_SUD_API_261 */
              /* Update the return pointer with the Rx L-PDU structure */
              ptrRxLpduRetVal = &ptrRxLpdu[mid];
            }
            /* Set high to zero to break the loop */
            high = (PduIdType)CANIF_ZERO;            
          }
          else
          {
            if (mid == (PduIdType)CANIF_ZERO)
            {
              /* Set high to zero to break the loop */
              high = (PduIdType)CANIF_ZERO;            
            }
            /* Compare the CAN-ID with the requested one */
            else if (canId < listCanId)
            {
              /* @Trace: CanIf_SUD_API_262 */
              /* If the priority is lower, update high */
              high = mid - (PduIdType)CANIF_ONE;
            }
            else
            {
              /* @Trace: CanIf_SUD_API_263 */
              /* If the priority is higher, update low */
              low = mid + (PduIdType)CANIF_ONE;
            }
          }
        }
      } while (low <= high);
    }
    else /* if (canId != listCanId) */
    {
      if (CanIf_CheckRxPduCanIdType(ptrRxLpdu, canFrameType) == (Std_ReturnType)E_OK)
      {
        /* @Trace: CanIf_SUD_API_264 */
        /* Update the return pointer with the actual Rx L-PDU structure */
        ptrRxLpduRetVal = ptrRxLpdu;
      }
    }
  } /* if (listCanId != canId) */
  /* Return RxLpduRetVal pointer */
  return (ptrRxLpduRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_TriggerSWFilter                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is triggerred to do the software      **
**                        filtering for the CanIds                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrHrh, CanId                                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : ptrRxLpdu                                           **
**                                                                            **
** Return Value         : CanIf_RxLpduTypePtr                                 **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(CanIf_RxLpduTypePtr, CANIF_CODE)
                          CanIf_TriggerSWFilter (
                          P2CONST(CanIf_HrhType, AUTOMATIC, CANIF_CONST) ptrHrh,
                          VAR(Can_IdType, CANIF_VAR) CanId,
                          VAR(uint8, CANIF_VAR) canFrameType)
{
  P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu;
  VAR(PduIdType, CANIF_VAR) noOfLpdus;

  #if ((STD_ON == CANIF_BINARY_SEARCH) || (STD_ON == CANIF_LINEAR_SEARCH))|| (STD_ON == CANIF_IDTABLE_SEARCH)
  VAR(uint8, CANIF_VAR) filterStatus;
  #endif

  #if(STD_ON == CANIF_IDTABLE_SEARCH)
  VAR(uint8, CANIF_VAR) ldpuIdTableIndex;
  P2CONST(CanIf_RxLpduIdTableType, AUTOMATIC, CANIF_CONST) ptrRxLpduIdTable;
  #endif
  
  /* Get the pointer to first Rx L-PDU of range/list type */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  ptrRxLpdu = &CanIfRxLpdu[ptrHrh->RxLpduIndex];
  #else
  ptrRxLpdu = &CanIf_RxLpdu[ptrHrh->RxLpduIndex];
  #endif

  #if ((STD_ON == CANIF_BINARY_SEARCH) || (STD_ON == CANIF_LINEAR_SEARCH))|| (STD_ON == CANIF_IDTABLE_SEARCH)
  /* Check the filter method for BASIC or FULL can*/
  filterStatus = CANIF_RANGE_SUCCESS;
  #endif
  if (CANIF_TRUE == ptrHrh->Softwarefilter)
  {
    /* @Trace: CanIf_SUD_API_265 */
    /* Get the number of ranges supported for that HRH */
    noOfLpdus = ptrHrh->NoOfHrhRange;
    /* Check whether HRH is configured for range */
    while ((PduIdType)CANIF_ZERO != noOfLpdus)
    {
      /* @Trace: SWS_CANIF_00645 ECUC_CanIf_00826*/
      /* Check whether CAN-ID is in range */
      if (((CanId >= ptrHrh->Hrhcanidlower) && (CanId <= ptrHrh->Hrhcanidupper)) || \
          ((CanId & ptrHrh->HrhRangeMask) == ptrHrh->HrhRangeBaseId)) 
      {
        /* @Trace: CanIf_SUD_API_266 */
        /* Break the loop */
        noOfLpdus = (PduIdType)CANIF_ZERO;
      } 
      else /* if canid not in range */
      {
        /* @Trace: CanIf_SUD_API_267 */
        /* Decrement the number of Tx L-PDU(s) */
        #if ((STD_ON == CANIF_BINARY_SEARCH) || (STD_ON == CANIF_LINEAR_SEARCH)) || (STD_ON == CANIF_IDTABLE_SEARCH)
        filterStatus = CANIF_FAILURE;
        #endif
        noOfLpdus--;
      }
    } /* @ while (noOfLpdus != CANIF_ZERO);*/
    #if(STD_ON == CANIF_IDTABLE_SEARCH)
    /* Index Search Controller ID * 8(IP Table Number of each Controller) */
    ldpuIdTableIndex = (ptrRxLpdu->ControllerId * CANIF_IPTABLE_COUNT) +
        ((CanId & CANIF_STANDARD_ID_FIRSTBIT_MASK) >> CANIF_IPTABLE_COUNT);
    #endif

    #if ((STD_ON == CANIF_BINARY_SEARCH) || (STD_ON == CANIF_LINEAR_SEARCH)) || (STD_ON == CANIF_IDTABLE_SEARCH)
    /* Check whether id is found in range search */
    if (CANIF_RANGE_SUCCESS == filterStatus)
    {
      /* @Trace: CanIf_SUD_API_268 */
      #if(STD_ON == CANIF_IDTABLE_SEARCH)
      ptrRxLpduIdTable = &CanIf_RxLpduIdTable[ldpuIdTableIndex];

      /* Get the pointer to first Rx L-PDU of range/list type */
      #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
      ptrRxLpdu = &CanIfRxLpdu[ptrRxLpduIdTable->RxLpduIdTableIndex];
      #else
      ptrRxLpdu = &CanIf_RxLpdu[ptrRxLpduIdTable->RxLpduIdTableIndex];
      #endif

      noOfLpdus = ptrRxLpduIdTable->NoOfRxLpdusRange;
      #else
      /* Get the number of List IDs from HRH structure */
      noOfLpdus = ptrHrh->NoOfRxLpdusList;
      #endif

      /* Check whether any list L-PDUs configured for that HRH */
      if ((PduIdType)CANIF_ZERO != noOfLpdus)
      {
        /* @Trace: CanIf_SUD_API_269 */
        /* Check filter method for that HRH*/
        #if (STD_ON == CANIF_BINARY_SEARCH) || (STD_ON == CANIF_IDTABLE_SEARCH)
        /* Do the Binary Search */
        ptrRxLpdu = CanIf_BinarySearch(ptrRxLpdu, noOfLpdus, CanId, canFrameType);
        #endif
        #if (STD_ON == CANIF_LINEAR_SEARCH)
        /* Linear Search */
        ptrRxLpdu = CanIf_LinearSearch(ptrRxLpdu, noOfLpdus, CanId, canFrameType);
        #endif
      } 
      else /* if (noOfLpdus != CANIF_ZERO) */
      {
        /* @Trace: CanIf_SUD_API_270 */
        /* Initialize value as null pointer */
        ptrRxLpdu = NULL_PTR;
      }
    } /* @ if (CANIF_FAILURE == filterStatus)  */
    else
    {
      /* @Trace: CanIf_SUD_API_271 */
      ptrRxLpdu = NULL_PTR;
    }
    #endif /* #if ((STD_ON == CANIF_BINARY_SEARCH) ||(...)) */ 
  }
  /* Check whether software check returns true */
  return (ptrRxLpdu);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_LinearSearch                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to implement the liear search **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrHrh, size, canId                                 **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : ptrRxLpdu                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                        None                                                **
*******************************************************************************/
#if (STD_ON == CANIF_LINEAR_SEARCH)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01140 SRS_Can_01141 SRS_Can_01162 */
FUNC(CanIf_RxLpduTypePtr, CANIF_CODE)
                         CanIf_LinearSearch (
                         P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu,
                         VAR(PduIdType, CANIF_VAR) size,
                         VAR(Can_IdType, CANIF_VAR) canId,
                         VAR(uint8, CANIF_VAR) canFrameType)
{
  VAR(boolean, CANIF_VAR) searchValue;
  P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdulc;
  VAR(PduIdType, CANIF_VAR) sizelc;
  /* Initialize search value to false */
  searchValue = CANIF_FALSE;

  ptrRxLpdulc = ptrRxLpdu;
  sizelc = size;

  /*Loop all the Rx L-PDUs for the requested CAN ID. */
  do
  {
    /* If the CAN-ID is found in database,
      >> set the flag
      >> break the loop
    */
    /* if Rx Lpdu has not config range */
    if (CANIF_INVALID_RXCANIDRANGE == ptrRxLpdulc->RxUpperCanId)
    {
      #if ((STD_ON == CANIF_RX_LPDU) && (STD_ON == CANIF_META_DATA_SUPPORT))
      if (((ptrRxLpdulc->RxPduCanId) & (ptrRxLpdulc->CanIfRxPduCanIdMask)) ==
          (canId & (ptrRxLpdulc->CanIfRxPduCanIdMask)))
      #else
      if (ptrRxLpdulc->RxPduCanId == canId) /* @Trace: SWS_CANIF_00877 */
      #endif
      {
        if (CanIf_CheckRxPduCanIdType(ptrRxLpdulc, canFrameType) == (Std_ReturnType)E_OK)
        {
          /* @Trace: CanIf_SUD_API_051 */
          /* Set search flag to true */
          searchValue = CANIF_TRUE;
        }
        /* Set size to zero to break the loop */
        sizelc = (PduIdType)CANIF_ZERO;
      }
      else
      {
        /* @Trace: CanIf_SUD_API_272 */
        /* Increment Rx L-PDU structure */
        ptrRxLpdulc++;
        /* Decrement the size */
        sizelc--;
      }
    }
    else /* if Rx Lpdu has config range */
    {
      if ((canId >= ptrRxLpdulc->RxLowerCanId) && (canId <= ptrRxLpdulc->RxUpperCanId))
      {
        if (CanIf_CheckRxPduCanIdType(ptrRxLpdulc, canFrameType) == (Std_ReturnType)E_OK)
        {
          /* @Trace: CanIf_SUD_API_273 */
          /* Set search flag to true */
          searchValue = CANIF_TRUE;
        }
        /* Set size to zero to break the loop */
        sizelc = (PduIdType)CANIF_ZERO;
      }
      else
      {
        /* @Trace: CanIf_SUD_API_274 */
        /* Increment Rx L-PDU structure */
        ptrRxLpdulc++;
        /* Decrement the size */
        sizelc--;        
      }
    }
  } while ((PduIdType)CANIF_ZERO != sizelc);

  /* Check whether CAN-ID is found in database */
  if ((boolean)CANIF_FALSE == searchValue)
  {
    /* @Trace: CanIf_SUD_API_275 */
    /* Return the null pointer */
    ptrRxLpdulc = NULL_PTR;
  }
  else
  {
    /* Do nothing*/
  }

  /* Return ptrRxLpdu pointer */
  return (ptrRxLpdulc);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_RxStatusUpdate                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for the updating the RxStatus **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrRxLpdu                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_RxLpduNotify              **
**                                                                            **
**                        Function(s) invoked:                                **
**                                        SchM_Enter_CanIf_RX_DATA_PROTECTION **
**                                        SchM_Exit_CanIf_RX_DATA_PROTECTION  **
**                                                                            **
*******************************************************************************/
#if ((STD_ON == CANIF_READRXPDU_NOTIFY_STATUS_API) || \
                                           (STD_ON == CANIF_READRXPDU_DATA_API))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_RxStatusUpdate (
                        P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu,
                        P2CONST(PduInfoType, AUTOMATIC, CANIF_CONST) PduInfoPtr)
{
  P2VAR(CanIf_RxLpduNotifyType, AUTOMATIC, CANIF_VAR) ptrRxLpduNotify;
  VAR(PduIdType, CANIF_VAR) notifyId;

  #if (STD_ON == CANIF_READRXPDU_DATA_API)
  VAR(uint8, CANIF_VAR) tmpVar;
  #endif

  VAR(uint8, CANIF_VAR) CanDlc;
  CanDlc = (uint8)PduInfoPtr->SduLength;

  /* Get the notify structure id from RxLpdu structure */
  notifyId = ptrRxLpdu->RxNotifyId;
  /* @Trace: CanIf_SUD_API_048 */
  /* Check the notification status mask */
  ptrRxLpduNotify = &CanIf_RxLpduNotify[notifyId];

  /* @Trace: SWS_CANIF_00473 */
  /* update the RxNotifSts with DLC and notification status */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
  ptrRxLpduNotify->DlcOrNotify = (CanDlc | CANIF_NOTIFY_STATUS_MASK);

  /*CANIF_NOTIFY_STATUS_MASK = 0x80*/
  #if (STD_ON == CANIF_READRXPDU_DATA_API)
  /* Get the pointer to RxLpduData pointer from RxLpduNotify
     structure CANIF_DATA_STATUS_MASK - 0X80 */
  /* @Trace: SWS_CANIF_00198 */
  /* @Trace: CanIf_SUD_API_049 */
  if (CANIF_ZERO != (ptrRxLpdu->RxUserOrNotifSts & CANIF_RX_DATA_STATUS_MASK))
  {
    /* Assigned length to local variable */
    tmpVar = CanDlc;

    /* Disable relevant interrupts */
    /* @Trace: SWS_CANIF_00199 */
    /* @Trace: CanIf_SUD_API_050 */
    SchM_Enter_CanIf_RX_DATA_PROTECTION();

    /* Run Loop to copy the data as per DLC */
    while ((uint8)CANIF_ZERO != tmpVar)
    { 
      /* @Trace: CanIf_SUD_API_276 */
      tmpVar--; /* decrement the value of tmpVar */
      /* polyspace +3 RTE:NIV [Not a defect:Low] "Its value has been gotten from the upper layer, no impact" */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined" */
      ptrRxLpduNotify->RxBufferData[tmpVar] = PduInfoPtr->SduDataPtr[tmpVar];
    }
    /* Enable relevant interrupts */
    SchM_Exit_CanIf_RX_DATA_PROTECTION();
  } 
  else /*if ( ptrRxLpduData != NULL_PTR) */
  {
  	/* Do nothing*/
  }
  #endif
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_ReadRxCanId                                   **
**                                                                            **
** Service ID           : none                                                **
**                                                                            **
** Description          : This service provides the actual value of           **
**                        CAN identifier received                             **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : none                                                **
**                                                                            **
** Output Parameters    : CanIdPtr                                            **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        For post-build and pre-compile Implementation:      **
**                        CanIf_RxCanId                                       **
**                                                                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                                                        f                   **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void,CANIF_CODE) CanIf_ReadRxCanId
    (P2VAR(Can_IdType, AUTOMATIC, CANIF_APPL_DATA) CanIdPtr)
{
  /* polyspace +11 RTE:UNR [Justified:Low] "It depends on the configuration of CanIf. No impact" */
  if(NULL_PTR != CanIdPtr)
  {
    /* @Trace: CanIf_SUD_API_277 */
    /* Copy CAN message identifier value */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "It's value is pre-defined" */
    *CanIdPtr = CanIf_RxCanId;
  }
  else
  {
  	/* Do nothing */
  }
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_Filtering                                     **
**                                                                            **
** Service ID           : none                                                **
**                                                                            **
** Description          : This service Check whether received CAN-ID          **
                          is type of FullCAN or BasicCAN                      **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : none                                                **
**                                                                            **
** Output Parameters    : uint8 sftwrFltrng                                   **
**                                                                            **
** Return value         : pointer                                             **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanIf_RxLpdu              **
**                                                                            **
**                        Function(s) invoked    :  CanIf_TriggerSWFilter     **
**                                                  CanIf_RxData              **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(CanIf_RxLpduTypePtr, CANIF_CODE) CanIf_Filtering (
      VAR(uint8, CANIF_VAR) sftwrFltrng,
      P2CONST(CanIf_HrhType, AUTOMATIC, CANIF_CONST) ptrHrh,
      VAR(Can_IdType, CANIF_VAR) canId,
      VAR(uint8, CANIF_VAR) canFrameType,
      P2VAR(Can_IdType, AUTOMATIC, CANIF_VAR)  metadata)
{
  P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu;
  /* polyspace +13 RTE:UNR [Justified:Low] "It depends on the configuration of CanIf. No impact" */
  /* @Trace: SWS_CANIF_00663 SWS_CANIF_00389*/
  /* @Trace: CanIf_SUD_API_036 */
  if ((CANIF_RX_BASIC_CAN_MIXED >= sftwrFltrng)
        && (STD_ON == CANIF_RX_BASIC_CAN_SUPPORT))
  {
    /* call the S/W triggering function */
    ptrRxLpdu = CanIf_TriggerSWFilter(ptrHrh, canId, canFrameType);
    #if (STD_ON == CANIF_META_DATA_SUPPORT)
    if (NULL_PTR != ptrRxLpdu) {
      /* @Trace: SWS_CANIF_00297 If CanIf has accepted a L-PDU received via
      CanIf_RxIndication() during Data Length Check,
      CanIf shall copy the number of bytes according to the configured Data Length
      to the static receive buffer
       
	   [SWS_CANIF_00851] If MetaData is configured for a received L-SDU,
         CanIf shall copy the PDU payload to the static receive buffer
         and the CAN ID to the Meta-DataItem of type CAN_ID_32 */
      /* @Trace: SWS_CANIF_00847 */  
      /* @Trace: CanIf_SUD_API_033 */   
      CanIf_RxData(canId, ptrRxLpdu, metadata);
    }
    else
    {
      /* Do nothing*/
    }
    #endif
  }
  else /* For the Case of FULL CAN */
  {
    /* @Trace: CanIf_SUD_API_281 */
    /* Get the pointer to desired Rx L-PDU of range/list type */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrRxLpdu = &CanIfRxLpdu[ptrHrh->RxLpduIndex];
    #else
    ptrRxLpdu = &CanIf_RxLpdu[ptrHrh->RxLpduIndex];
    #endif
    if (CanIf_CheckRxPduCanIdType(ptrRxLpdu, canFrameType) == (Std_ReturnType)E_NOT_OK)
    {
      ptrRxLpdu = NULL_PTR;
    }
  }
  CANIF_UNUSED(metadata);
  return(ptrRxLpdu);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_DETRxindication                               **
**                                                                            **
** Service ID           : none                                                **
**                                                                            **
** Description          : This service Check Error of CanIf_Rxindication      **
**                                                                            **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Mailbox, PduInfoPtr                                 **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return value         : retVal (E_OK, E_NOT_OK)                             **
**                                                                            **
** Preconditions        : Det error report on                                 **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanIf_HrhMapArray         **
**                                                                            **
**                                                                            **
**                                                                            **
**                                                                            **
**                        Function(s) invoked    :  CanIf_TriggerSWFilter     **
**                                                  CanIf_RxData              **
*******************************************************************************/
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, CANIF_CODE) CanIf_DETRxindication (
                    P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_CONST) Mailbox,
                    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr)
{
  VAR(uint8, CANIF_VAR) retVal;
  retVal = (uint8) E_OK;
  /* @Trace: CanIf_SUD_API_041 */
  VAR(uint8, CANIF_VAR) driverid;
  VAR(uint8, CANIF_VAR) offsetid;
  
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  driverid = CanIfControllerConfig[Mailbox->ControllerId].CanDriverId;
  offsetid = CanIfHrhInit[driverid].HrhOffSetId;
  #else
  driverid = CanIf_ControllerConfig[Mailbox->ControllerId].CanDriverId;
  offsetid = CanIf_HrhInit[driverid].HrhOffSetId;
  #endif
  #else
  driverid = CANIF_ZERO;
  offsetid = CANIF_ZERO;
  #endif

  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00421 */
  /* @Trace: CanIf_SUD_API_042 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_RX_INDICATION_SID, retVal);

  /* Report to DET, if Mailbox is null pointer */
  /* @Trace: SWS_CANIF_00419 */
  /* @Trace: CanIf_SUD_API_043 */
  CANIF_NULL_PTR_ERROR(CANIF_RX_INDICATION_SID, retVal, Mailbox);

  /* Report to DET, if PduInfoPtr is null pointer */
  /* @Trace: SWS_CANIF_00419 */
  CANIF_NULL_PTR_ERROR(CANIF_RX_INDICATION_SID, retVal, PduInfoPtr);

  if ((uint8) E_OK == retVal)
  {
    /* Report to DET, if HRH Id is out of range */
    /* @Trace: SWS_CANIF_00416 */
    /* @Trace: CanIf_SUD_API_044 */
    /* polyspace +16 RTE:UNR [Justified:Low] "It depends on the configuration of CanIf. No impact" */
    /* polyspace +8 MISRA-C3:D4.14 [Not a defect:Low] "Its boundary is pre-defined"*/  
    /* polyspace +7 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    /* polyspace +6 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/  
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)     
    if (((Mailbox->Hoh) > CanIfHrhInit[driverid].MaxHrhId) ||
      (CanIfHrhMapArray[(Mailbox->Hoh)+offsetid] == CANIF_INVALID))
    #else /* Pre compile */
    if (((Mailbox->Hoh) > CanIf_HrhInit[driverid].MaxHrhId) ||
      (CanIf_HrhMapArray[(Mailbox->Hoh)+offsetid] == CANIF_INVALID))
    #endif  
    {
      /* @Trace: CanIf_SUD_API_283 */                  
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_RX_INDICATION_SID,  
                            CANIF_E_PARAM_HOH);                                
      (retVal) = (uint8)E_NOT_OK;                                              
    }
  }
  /* polyspace +8 RTE:UNR [Justified:Low] "It depends on the configuration of CanIf. No impact" */
  if ((uint8) E_OK == retVal)
  {
    /* @Trace: CanIf_SUD_API_284 */
    retVal = CanIf_CheckParameter(Mailbox, PduInfoPtr, offsetid);
  }
  else /* @ E_OK == retVal */
  {
  	/* Do nothing */
  }

  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_CheckParameter                                **
**                                                                            **
** Service ID           : none                                                **
**                                                                            **
** Description          : This service Check Error of CanIf_Rxindication      **
**                                                                            **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Mailbox, PduInfoPtr                                 **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return value         : retVal (E_OK, E_NOT_OK)                             **
**                                                                            **
** Preconditions        : Det error report on                                 **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanIf_HrhMapArray         **
**                                                                            **
**                                                                            **
**                                                                            **
**                                                                            **
**                        Function(s) invoked    :  CanIf_TriggerSWFilter     **
**                                                  CanIf_RxData              **
*******************************************************************************/
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, CANIF_CODE) CanIf_CheckParameter (
                    P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_CONST) Mailbox,
                    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr,
                    VAR(uint8, CANIF_VAR) offsetid)
{
  VAR(uint8, CANIF_VAR) retVal;
  retVal = (uint8) E_OK;
  /* @Trace: CanIf_SUD_API_041 */
  VAR(uint8, CANIF_VAR) sftwrFltrng;

  /* @Trace: CanIf_SUD_API_284 */
  /* polyspace +4 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)                                    
  sftwrFltrng = CanIfHrh[CanIfHrhMapArray[(Mailbox->Hoh)+offsetid]].FilterMethod;
  #else
  sftwrFltrng = CanIf_Hrh[CanIf_HrhMapArray[(Mailbox->Hoh)+offsetid]].FilterMethod;
  #endif
  /* polyspace +14 RTE:UNR [Justified:Low] "It depends on the configuration of CanIf. No impact" */
  #if (STD_ON == CANIF_STANDARD_CANID_ONLY) 
  /* If CanId is out of range of STD */
  /* @Trace: SWS_CANIF_00417 */
  /* @Trace: CanIf_SUD_API_045 */
  CANIF_INVALID_STANDARD_CANID_ERROR(CANIF_RX_INDICATION_SID, Mailbox->CanId, retVal);
  #endif

  #if ((STD_ON == CANIF_EXTENDED_CANID_ONLY) || (STD_ON == CANIF_EXT_STD_CANID))
  /* If CanId is out of range of EXT*/
  CANIF_INVALID_EXTENDED_CANID_ERROR(CANIF_RX_INDICATION_SID, Mailbox->CanId, retVal);
  #endif

  /* Report to DET, if CanSduPtr is null pointer */
  CANIF_NULL_PTR_ERROR(CANIF_RX_INDICATION_SID, retVal, PduInfoPtr->SduDataPtr);
  /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "Its boundary is pre-defined" */
  /* polyspace-end RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/

  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_DETReadRxPduData                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service provides the CAN DLC and the received  **
**                        data of the requested CanRxPduId to the calling     **
**                        upper layer.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : CanIfRxSduId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : PduInfoPtr                                          **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s):  CanIf_CanIfStatus              **
**                                             RxBufferData                   **
**                                             CanIf_RxLpduNotify             **
**                                             CanIf_Controller               **
**                        Function(s) invoked: Det_ReportError                **
**                                             SchM_Enter_CanIf_RX_DATA_      **
**                                             PROTECTION                     **
**                                             SchM_Exit_CanIf_RX_DATA_       **
**                                             PROTECTION                     **
*******************************************************************************/
#if (STD_ON == CANIF_READRXPDU_DATA_API)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01125, SRS_Can_01129 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_DETReadRxPduData (
                      VAR(PduIdType, CANIF_VAR) CanIfRxSduId,
                      P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr)
{
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  #if (STD_OFF == CANIF_DEV_ERROR_DETECT)
  retVal = E_OK;
  CANIF_UNUSED(CanIfRxSduId);
  CANIF_UNUSED(PduInfoPtr);
  #else
  /* Initialize standard return type to E_OK */
  retVal = CANIF_ZERO;

  /* Report to DET, if module is not initialized */
  if (CANIF_UNINITIALISED == CanIf_CanIfStatus)
  {
    /* @Trace: CanIf_SUD_API_245 */
    (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                    CANIF_READ_RXPDU_DATA_SID, CANIF_E_UNINIT);
    retVal++;
  }
  else
  {
    /* Report to DET, if RXPDUID is not in range */
    /* @Trace: SWS_CANIF_00325 */
    /* @Trace: CanIf_SUD_API_028 */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    if (CanIfRxSduId >= CanIf_NoofRxLpdu) {
    #else
    if (CanIfRxSduId >= CANIF_NO_OF_RXLPDU) {
    #endif  
      /* @Trace: CanIf_SUD_API_246 */
      (void) Det_ReportError(CANIF_MODULE_ID, (uint8) CANIF_ZERO,
              CANIF_READ_RXPDU_DATA_SID, CANIF_E_INVALID_RXPDUID);
      retVal++;
    }
    else
    {
      /* Do nothing */
    }

    /* Report to DET, if PduInfopointer is a Null Pointer */
    /* @Trace: SWS_CANIF_00326 */
    /* @Trace: CanIf_SUD_API_029 */
    if (NULL_PTR == PduInfoPtr) 
    {
      /* @Trace: CanIf_SUD_API_247 */
      (void) Det_ReportError(CANIF_MODULE_ID, (uint8) CANIF_ZERO,
            CANIF_READ_RXPDU_DATA_SID, CANIF_E_PARAM_POINTER);
      retVal++;
    } 
    else 
    {
      /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "It's value is pre-define" */
      if (NULL_PTR == PduInfoPtr->SduDataPtr) 
      {
        /* @Trace: CanIf_SUD_API_248 */
      (void) Det_ReportError(CANIF_MODULE_ID, (uint8) CANIF_ZERO,
            CANIF_READ_RXPDU_DATA_SID, CANIF_E_PARAM_POINTER);
      retVal++;
      } 
      else 
      {
        /* Do nothing */
      }
    } /* @ (NULL_PTR == PduInfoPtr) */
  } /* @ (CANIF_UNINITIALISED == CanIf_CanIfStatus) */
  #endif

  /* Return std return value */
  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* polyspace-end RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
/*******************************************************************************
** Function Name        : CanIf_CheckRxPduCanIdType                           **
**                                                                            **
** Service ID           : 0x15                                                **
**                                                                            **
** Description          : This service checks whether the received can frame  **
                          type and can id type are appropriate.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrRxLpdu, canFrameType                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s): None                            **
**                        Function(s) invoked: None                           **
*******************************************************************************/
#if (STD_ON == CANIF_RX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckRxPduCanIdType (
                      P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu,
                      VAR(uint8, CANIF_VAR) canFrameType)
{
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  
  if (((ptrRxLpdu-> RxPduCanIdType == CANIF_STANDARD_CANID_TYPE) && ((canFrameType == CANIF_CANFD_NO_STANDARD_CANID_TYPE) || (canFrameType == CANIF_CANFD_STANDARD_CANID_TYPE))) ||
      ((ptrRxLpdu-> RxPduCanIdType == CANIF_EXTENDED_CANID_TYPE) && ((canFrameType == CANIF_CANFD_NO_EXTENDED_CANID_TYPE) || (canFrameType == CANIF_CANFD_EXTENDED_CANID_TYPE))) ||
      ((ptrRxLpdu-> RxPduCanIdType == CANIF_CANFD_NO_STANDARD_CANID_TYPE) && (canFrameType == CANIF_CANFD_NO_STANDARD_CANID_TYPE)) ||
      ((ptrRxLpdu-> RxPduCanIdType == CANIF_CANFD_STANDARD_CANID_TYPE) && (canFrameType == CANIF_CANFD_STANDARD_CANID_TYPE)) ||
      ((ptrRxLpdu-> RxPduCanIdType == CANIF_CANFD_NO_EXTENDED_CANID_TYPE) && (canFrameType == CANIF_CANFD_NO_EXTENDED_CANID_TYPE)) ||
      ((ptrRxLpdu-> RxPduCanIdType == CANIF_CANFD_EXTENDED_CANID_TYPE) && (canFrameType == CANIF_CANFD_EXTENDED_CANID_TYPE)))
  {
    retVal = E_OK;
  }
  else
  {
    (void)Det_ReportRuntimeError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_CHECK_RX_PDU_CAN_ID_TYPE_SID, CANIF_E_RXPDU_CANIDTYPE_INVALID);
    retVal = E_NOT_OK;
  }  
  /* Return std return value */
  return(retVal);
}
/* polyspace-end RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
