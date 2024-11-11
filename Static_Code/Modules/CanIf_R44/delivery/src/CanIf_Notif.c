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
**  SRC-MODULE: CanIf_Notif.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of callback Bus-Off and Wakeup Notifications        **
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
** 1.0.6     25-Jul-2022   HieuTM8        #CP44-444                           **
** 1.0.5     30-Jun-2022   HieuTM8        #CP44-130                           **
** 1.0.1     22-Sep-2021   HieuTM8        #20891                              **
** 1.0.0.3   23-Aug-2021   HieuTM8        #19470, #19526                      **
** 1.0.0     21-Dec-2020   SJ Kim         Initialization                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_Ram.h"           /* CanIf RAM header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#include "CanIf_Notif.h"         /* Notification header */
#include "CanSM_CanIf.h"           /* CAN State Manager call back header file */
#if (STD_ON == CANIF_WAKEUP_SUPPORT)
#include "EcuM.h"            /* EcuM call back header file */
#endif
#include "SchM_CanIf.h"          /* SchM CanIf Header file */
#include "CanIf_UserInc.h"       /* User Included CanIf Header file */

#include "CanIf_Error.h"         /* CanIf Det file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANIF_NOTIF_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_NOTIF_C_AR_RELEASE_MINOR_VERSION    4
#define CANIF_NOTIF_C_AR_RELEASE_REVISION_VERSION 0

/* File version information */
#define CANIF_NOTIF_C_SW_MAJOR_VERSION       1
#define CANIF_NOTIF_C_SW_MINOR_VERSION       1
#define CANIF_NOTIF_C_SW_REVISION_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_NOTIF_AR_RELEASE_MAJOR_VERSION != \
  CANIF_NOTIF_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_NOTIF.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_NOTIF_AR_RELEASE_MINOR_VERSION != \
  CANIF_NOTIF_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_NOTIF.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_NOTIF_AR_RELEASE_REVISION_VERSION != \
  CANIF_NOTIF_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_NOTIF.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_NOTIF_SW_MAJOR_VERSION != CANIF_NOTIF_C_SW_MAJOR_VERSION)
  #error "CANIF_NOTIF.c : Mismatch in Software Major Version"
#endif
#if (CANIF_NOTIF_SW_MINOR_VERSION != CANIF_NOTIF_C_SW_MINOR_VERSION)
  #error "CANIF_NOTIF.c : Mismatch in Software Minor Version"
#endif

/* polyspace-begin RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : CanIf_CheckWakeup                                   **
**                                                                            **
** Service ID           : 0x11                                                **
**                                                                            **
** Description          : This service checks, whether an underlying CAN      **
**                        driver or a CAN transceiver driver already signals  **
**                        a wakeup event                                      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : WakeupSource                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s):  CanIf_CanIfStatus              **
**                                             CanIf_WakeupSource             **
**                        Function(s) invoked: Det_ReportError                **
**                                             CanIf_TrcvCheckwakeupService   **
**                                             CanIf_CanCheckwakeupService    **
**                                             EcuM_SetWakeupEvent            **
*******************************************************************************/
#if ((STD_ON == CANIF_WAKEUP_SUPPORT) && ((STD_ON == CANIF_TRCV_WAKEUP_SUPPORT) ||\
     (STD_ON == CANIF_CTRL_WAKEUP_SUPPORT)))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckWakeup (
                             VAR(EcuM_WakeupSourceType, CANIF_VAR) WakeupSource)
{
  /* @Trace: CanIf_SUD_API_093 */
  P2CONST(CanIf_WakeupSourceInfoType, AUTOMATIC, CANIF_CONST) ptrWkpSource;
  VAR(EcuM_WakeupSourceType, CANIF_VAR) wakeupEvent;
  VAR(uint8_least, CANIF_VAR) noOfWakeupSources;
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Setting the return val to E_OK */
  retVal = (uint8) E_OK;

  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CHECK_WAKEUP_SID, retVal);

  /* Check for any development error */
  if ((uint8) E_OK == retVal)
  #endif /*  (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanIf_SUD_API_214 */
    /* Set retVal to E_NOT_OK */
    retVal = (uint8)E_NOT_OK;

    /* Get the number of wakeup sources into the local variable */
    noOfWakeupSources = (uint8_least)CANIF_NO_OF_WAKEUP_SOURCES;

    /* Get the pointer to the wakeup structure */
    ptrWkpSource = &CanIf_WakeupSource[CANIF_ZERO];

    while (noOfWakeupSources != (uint8_least)CANIF_ZERO)
    {
      /* @Trace: CanIf_SUD_API_215 */
      /* Get the wakeup event and store it in a local variable */
      wakeupEvent = ptrWkpSource->WakeupEvent;

      /* Check whether the wakeup event is matched or not */
      if (wakeupEvent != WakeupSource)
      {
        /* @Trace: CanIf_SUD_API_216 */
        /* Decrement the number of wakeup sources */
        noOfWakeupSources--;

        /* Increment wakeup source pointer by one */
        ptrWkpSource++;
      }
      else
      {
        /* @Trace: CanIf_SUD_API_217 */
        /* Set the noOfWakeupSources to zero to break the loop */
        noOfWakeupSources = (uint8_least)CANIF_ZERO;

        /* Setting the return val to E_OK */
        retVal = (uint8) E_OK;
      }
    }
    /* Check whether wakeup flag is true */
    if ((uint8) E_OK == retVal)
    {
      /* Check if DET invoked or not */
      #if (STD_ON == CANIF_CTRL_WAKEUP_SUPPORT)
      /* Is the wakeup source is due to Can Driver */
      /* @Trace: CanIf_SUD_API_094 */
      if (CANIF_CANDRV_WAKEUPSOURCE == (ptrWkpSource->WakeupSource))
      {
        /* invoke CanIf_CanCheckwakeupService */
        retVal = CanIf_CanCheckwakeupService(ptrWkpSource);
      }
      else
      #endif
      {
        /* @Trace: CanIf_SUD_API_218 */
        #if (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)
        /* invoke CanIf_TrcvCheckwakeupService  */
        retVal = CanIf_TrcvCheckwakeupService(ptrWkpSource);
        #endif
      }
      /* @Trace: CanIf_SUD_API_095 */
      #if (STD_ON == CANIF_CTRL_WAKEUP_SUPPORT)

      if ((uint8) E_OK == retVal)
      {
        /* Invoke Wakeup Indication function */
        EcuM_SetWakeupEvent(WakeupSource);
      }
      else /* if ((uint8) E_OK == retVal) */
      {
      	/* Do nothing */
      }
      #endif
    }/*(E_OK == retVal) */

    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    else /* if ((uint8) E_OK == retVal) */
    {
      /* Report to DET, if Wakeup sourceId is invalid */
      /* @Trace: CanIf_SUD_API_096 */
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                            CANIF_CHECK_WAKEUP_SID, CANIF_E_PARAM_WAKEUPSOURCE);
    }
    #endif
  }/*after passing DET Checks */
  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_CheckValidation                               **
**                                                                            **
** Service ID           : 0x12                                                **
**                                                                            **
** Description          : This service is performed to validate a previous    **
**                        wakeup event. The CAN Interface checks inside this  **
**                        service, whether a L-PDU is successfully received   **
**                        in the meantime.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : WakeupSource                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_WakeupSource              **
**                                            CanIf_CanIfStatus               **
**                                            CanIf_Controller                **
**                        Function(s) invoked:                                **
**                                            Det_ReportError                 **
**                                            SchM_Enter_CanIf_MODE_STATUS_   **
**                                            PROTECTION,                     **
**                                            SchM_Exit_CanIf_MODE_STATUS_    **
**                                            PROTECTION                      **
*******************************************************************************/
#if ((STD_ON == CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT) && \
     ((STD_ON == CANIF_CTRL_WAKEUP_SUPPORT) || (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckValidation (
                             VAR(EcuM_WakeupSourceType, CANIF_VAR) WakeupSource)
{
  /* @Trace: SWS_CANIF_00178, SRS_Can_01136 */
  /* @Trace: CanIf_SUD_API_090 */
  P2CONST(CanIf_WakeupSourceInfoType, AUTOMATIC, CANIF_CONST) ptrWkpSource;
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  
  VAR(EcuM_WakeupSourceType, CANIF_VAR) wakeupEvent;
  VAR(uint8_least, CANIF_VAR) noOfWakeupSources;
  VAR(uint8_least, CANIF_VAR) noOfCntrl;
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Setting the return val to E_OK */
  retVal = (uint8) E_OK;

  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CHECK_VALIDATION_SID, retVal);

  /* Check for any development error */
  if ((uint8) E_OK == retVal)
  #endif
  {
    /* @Trace: CanIf_SUD_API_219 */
    /* Set retVal to E_NOT_OK */
    retVal = (uint8)E_NOT_OK;

    /* Get the number of wakeup sources into the local variable */
    noOfWakeupSources = (uint8_least)CANIF_NO_OF_WAKEUP_SOURCES;

    /* Get the pointer to the wakeup structure */
    ptrWkpSource = &CanIf_WakeupSource[CANIF_ZERO];

    while (noOfWakeupSources != (uint8_least)CANIF_ZERO)
    {
      /* @Trace: CanIf_SUD_API_220 */
      /* Get the wakeup event and store it in a local variable */
      wakeupEvent = ptrWkpSource->WakeupEvent;

      /* Check whether the wakeup event is matched or not */
      if (wakeupEvent != WakeupSource)
      {
        /* @Trace: CanIf_SUD_API_221 */
        /* Decrement the number of wakeup sources */
        noOfWakeupSources--;

        /* Increment wakeup source pointer by one */
        ptrWkpSource++;
      }
      else
      {
        /* @Trace: CanIf_SUD_API_222 */
        /*noOfWakeupSources set to zero to break the loop*/
        noOfWakeupSources = (uint8_least)CANIF_ZERO;

        /* Set retVal to E_OK */
        retVal = (uint8) E_OK;
      }
    }/*while (noOfWakeupSources != CANIF_ZERO)*/

    if ((uint8) E_OK == retVal)
    {
      /* @Trace: CanIf_SUD_API_223 */
      /* Get the pointer to the controller structure*/
      ptrController =  &CanIf_Controller[ptrWkpSource->ControllerConfigId];

      /* Check the wakeup validation flag for true as per CANIF681 */
      if (CANIF_IS_RX_VALIDATE_WAKEUP(ptrController->PduMode))
      {
    	  /* @Trace: SWS_CANIF_00179 */
        /* @Trace: CanIf_SUD_API_092 */
        /* Invoke EcuM/Cdd_ValidateWakeupEvent function */
        CANIF_DISPATCH_USERVALIDATEWAKEUPEVENT_NAME(WakeupSource);
      } 
      else /* CANIF_IS_RX_VALIDATE_WAKEUP(ptrController->PduMode)) */
      {
        /* @Trace: CanIf_SUD_API_225 */
        /* Set retVal to E_NOT_OK */
        retVal = (uint8)E_NOT_OK;
      }
      /* Disable interrupts */
      SchM_Enter_CanIf_MODE_STATUS_PROTECTION();

      /* Clear the wakeup validation flag */
      CANIF_CLEAR_RX_VALIDATE_WAKEUP(ptrController->PduMode);

      /* Take controllers in local variable */
      noOfCntrl = ptrWkpSource->NoOfCanCntrlOrTrcvId;

      /* check if multiple controllers are connected */
      while (noOfCntrl >= (uint8_least)CANIF_TWO)
      {
        /* @Trace: CanIf_SUD_API_226 */
        /* Point to next controller */
        ptrController++;

        /* Clear the wakeup validation flag */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
        CANIF_CLEAR_RX_VALIDATE_WAKEUP(ptrController->PduMode);

        /* Decrement controller */
        noOfCntrl--;
      }
      /* Enable interrupts */
      SchM_Exit_CanIf_MODE_STATUS_PROTECTION();
    }
    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    else /* (E_OK == retVal) */
    {
      /* Report to DET, if Wakeup sourceId is invalid */
      /* @Trace: SWS_CANIF_00404 */
      /* @Trace: CanIf_SUD_API_091 */
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                        CANIF_CHECK_VALIDATION_SID, CANIF_E_PARAM_WAKEUPSOURCE);
    }
    #endif /* (STD_ON == CANIF_DEV_ERROR_DETECT) */
  }/* after passing DET Checks */
  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/*#if ((STD_ON == CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT) && (STD_ON == CANIF_CTRL_WAKEUP_SUPPORT))*/

/*******************************************************************************
** Function Name        : CanIf_ControllerBusOff                              **
**                                                                            **
** Service ID           : 0x16                                                **
**                                                                            **
** Description          : This service indicates a Controller BusOff event    **
**                        referring to the corresponding CAN Controller       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ControllerId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized               **
**                                                                            **
** Remarks              : Global Variable(s) : CanIf_CanIfStatus              **
**                                             CanIf_Controller               **
**                                             CanIf_ControllerConfigType     **
**                                             CanIf_TxLpdu                   **
**                        Function(s) invoked:                                **
**                                             CanIf_ClearTxQueue,            **
**                                             CanIf_TxNotification           **
**                                             Det_ReportError,               **
**                                             SchM_Enter_CanIf_MODE_STATUS_  **
**                                             PROTECTION,                    **
**                                             SchM_Exit_CanIf_MODE_STATUS_   **
**                                             PROTECTION                     **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 SRS_Can_01114 SRS_Can_01029 */
FUNC(void, CANIF_CODE) CanIf_ControllerBusOff (
                                             VAR(uint8, CANIF_VAR) ControllerId)
{
  /* @Trace: SWS_CANIF_00014 */
  /* @Trace: CanIf_SUD_API_108 */
  #if (STD_ON == CANIF_TX_LPDU)
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;
  VAR(uint16, CANIF_VAR) count;
  #endif

  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;

  /* If the Development errors detection is enabled */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)

  VAR(Std_ReturnType, CANIF_VAR) retVal;
  /* Initialize the det error flag status to zero */
  retVal = (uint8) E_OK;
  /* polyspace +12 RTE:UNR [Not a defect:Low] "According to requirements, CanTp init status should be checked before any further processing" */
  /* Report to DET, if module is not initialized */
  /* @Trace: CanIf_SUD_API_109 */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CNTRL_BUS_OFF_SID, retVal);

  /* Report to DET, if requested controller id is more than available
  controller */
  /* @Trace: CanIf_SUD_API_110 */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_CNTRL_BUS_OFF_SID, retVal);

  /* check for any development occurred? */
  if ((uint8) E_OK == retVal)
  #endif /* CANIF_DEV_ERROR_DETECT */
  {
    /* @Trace: CanIf_SUD_API_227 */
    ptrController = &CanIf_Controller[ControllerId];

    /* Check controller mode is in start mode */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
    if (CANIF_STARTED == ptrController->ControllerMode)
    {
      /* @Trace: CanIf_SUD_API_228 */
      /* Disable interrupts */
      SchM_Enter_CanIf_MODE_STATUS_PROTECTION();

      /* Change the controller state to CAN_CS_STOPPED*/
      ptrController->ControllerMode = CANIF_STOPPED;

      /* @Trace: CanIf_SUD_API_111 Change the Pdu mode to CANIF_TX_OFFLINE */
      CANIF_SET_PDU_MODE(ptrController->PduMode, CANIF_TX_OFFLINE);

      #if (STD_ON == CANIF_TXCONFIRM_POLLING_SUPPORT)
      /* @Trace: CanIf_SUD_API_112 clear the information about a TxConfirmation */
      /* @Trace: SWS_CANIF_00740 */
      CANIF_CLEAR_TX_CONFIRMED(ptrController->PduMode);
      #endif

      #if (STD_ON == CANIF_TX_LPDU)
      #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
      ptrStaticController = &CanIfControllerConfig[ControllerId];
      #else
      ptrStaticController = &CanIf_ControllerConfig[ControllerId];
      #endif

      /* Get the pointer to Tx L-PDU */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
      ptrTxLpdu = ptrStaticController->TxLpdu;

      for(count = CANIF_ZERO; count < ptrStaticController->NoOfTxPdu; count++)
      {
        /* @Trace: CanIf_SUD_API_113 Inform corresponding upper layer modules about failed transmission */
        CanIf_TxNotification(ptrTxLpdu, E_NOT_OK);
        ptrTxLpdu++;
      }
      #endif

      /* Enable interrupts */
      SchM_Exit_CanIf_MODE_STATUS_PROTECTION();

      /* Invoke the upper layer function  */
      CANIF_DISPATCH_USERCTRLBUSOFF_NAME(ControllerId);

      #if ((STD_ON == CANIF_BASIC_CAN_TXPDU) && (STD_ON == CANIF_TX_QUEUE))	
      /* Disabling relevant interrupts*/
      /* @Trace: CanIf_SUD_API_114 */
      SchM_Enter_CanIf_TX_QUEUE_PROTECTION();

      /* Clear Tx queue */
      CanIf_ClearTxQueue(ptrStaticController);

      /* Enabling relevant interrupts*/
      SchM_Exit_CanIf_TX_QUEUE_PROTECTION();
      #endif
    }
    else /* @ if (CAN_CS_STARTED == ptrController->ControllerMode) */
    {
    	/* Do nothing */
    }
  }/* @ if (E_OK == retVal) */
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_CanCheckwakeupService                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to invoke the Can_CheckWakeup **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrWkpSource                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Output Value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanIf_Init() should be invoked                      **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_CanDriver                 **
**                                            CanIf_Controller                **
**                                                                            **
**                        Function(s) invoked: Can_CheckWakeup                **
**                                    SchM_Enter_CanIf_MODE_STATUS_PROTECTION **
**                                    SchM_Exit_CanIf_MODE_STATUS_PROTECTION  **
*******************************************************************************/
#if (STD_ON == CANIF_CTRL_WAKEUP_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE)CanIf_CanCheckwakeupService (
                 P2CONST(CanIf_WakeupSourceInfoType, AUTOMATIC, CANIF_CONST)ptrWkpSource)
{
  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  P2CONST(CanIf_CanDriverType, AUTOMATIC, CANIF_CONST) ptrDriver;
  #endif

  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;

  VAR(Std_ReturnType, CANIF_VAR) retVal;

  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  /* Get the pointer to corresponding Can Driver structure */
  ptrDriver = &CanIf_CanDriver[ptrWkpSource->DriverId];

  /* Invoke corresponding Driver function */
  retVal = (Std_ReturnType)ptrDriver->CanCheckwakeup(ptrWkpSource->ControllerConfigId);

  #else
  /* Invoke Can_Checkwakeup function */
  retVal = (Std_ReturnType)Can_CheckWakeup(ptrWkpSource->ControllerConfigId);
  #endif
  if ((Std_ReturnType)E_OK == retVal)
  {
    /* @Trace: CanIf_SUD_API_229 */
    /* Get the pointer to the controller structure */
    ptrController = &CanIf_Controller[ptrWkpSource->ControllerConfigId];

    /* Disable interrupts */
    SchM_Enter_CanIf_MODE_STATUS_PROTECTION();

    /* Change the state of the Controller to CAN_CS_STOPPED */
    ptrController->ControllerMode = CANIF_STOPPED;

    #if (STD_ON == CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT)

    /* Change the state of the Rx Status to Wakeup */
    CANIF_SET_RX_VALIDATE_WAKEUP(ptrController->PduMode);

    #endif/*#if (STD_ON == CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT)*/

    /* Enable interrupts */
    SchM_Exit_CanIf_MODE_STATUS_PROTECTION();
  }
  else
  {
  	/* Do nothing */
  }
  return (retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_TrcvCheckwakeupService                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to invoke the                 **
**                        CanTrcv_CheckWakeup                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ptrWkpSource                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_CanTrcvDriver             **
**                                                                            **
**                        Function(s) invoked: CanTrcv_CheckWakeup            **
*******************************************************************************/
#if (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE)CanIf_TrcvCheckwakeupService (
                 P2CONST(CanIf_WakeupSourceInfoType, AUTOMATIC, CANIF_CONST)ptrWkpSource)
{
  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  P2CONST(CanIf_CanTrcvDriverType, AUTOMATIC, CANIF_CONST) ptrCanTrcvDriver;
  #endif

  VAR(Std_ReturnType, CANIF_VAR) retVal;

  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
    /* Get the pointer to corresponding Can Driver structure */
  ptrCanTrcvDriver = &CanIf_CanTrcvDriver[ptrWkpSource->DriverId];

  /* Invoke corresponding Driver function */
  retVal = ptrCanTrcvDriver->CanTrcvCheckWakeup(ptrWkpSource->CanCntrlOrTrcvId);

  #else
  /* Invoke Can_Checkwakeup function */
  retVal = CanTrcv_CheckWakeup(ptrWkpSource->CanCntrlOrTrcvId);

  #endif/*#if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)*/

  return (retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* polyspace-end RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
