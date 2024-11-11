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
**  SRC-MODULE: CanIf_ModeCntrl.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of Mode Control Functionality Of the Controller     **
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
** 1.1.0     29-Feb-2024   Jh Yang        #CP44-2947, #CP44-3895              **
** 1.0.15    05-Jan-2024   JH Jang        #CP44-2840                          **
** 1.0.14    13-Jun-2023   HieuTM8        #CP44-2236                          **
** 1.0.12    12-Dec-2022   HieuTM8        #CP44-1254                          **
** 1.0.10    27-Oct-2022   HieuTM8        #CP44-1008                          **
** 1.0.9     03-Oct-2022   HieuTM8        #CP44-832                           **
** 1.0.6     25-Jul-2022   HieuTM8        #CP44-444                           **
** 1.0.5     30-Jun-2022   HieuTM8        #CP44-130                           **
** 1.0.4     09-May-2022   Jiwon Oh       #26814,#27128                       **
** 1.0.2     25-Mar-2022   HieuTM8        #25534                              **
** 1.0.1     22-Sep-2021   HieuTM8        #20891                              **
** 1.0.0.3   23-Aug-2021   HieuTM8        #19470, #19526                      **
** 1.0.0     21-Dec-2020   SJ Kim         Initialization                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"               /* CanIf header file */
#include "CanIf_Ram.h"           /* CanIf RAM header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#include "CanIf_ModeCntrl.h"     /* Mode control header */
#include "SchM_CanIf.h"          /* SchM CanIf Header file */
#include "CanIf_Can.h"           /* CAN Driver Module Header File */
#include "CanSM_CanIf.h"           /* CAN State Manager call back header file */
#include "CanIf_Error.h"         /* CanIf DET header file */

#if (STD_ON == CANIF_PDUR_CALLBACK)
#include "PduR.h"                /* PduR header file */
#endif
#include "CanIf_UserInc.h"       /* User Included CanIf Header file */

#if (STD_ON == CANIF_IDSM_SUPPORT)
#include "IdsM.h"            /* IdsM Module header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANIF_MODECNTRL_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_MODECNTRL_C_AR_RELEASE_MINOR_VERSION    4
#define CANIF_MODECNTRL_C_AR_RELEASE_REVISION_VERSION 0

/* File version information */
#define CANIF_MODECNTRL_C_SW_MAJOR_VERSION       1
#define CANIF_MODECNTRL_C_SW_MINOR_VERSION       1
#define CANIF_MODECNTRL_C_SW_REVISION_VERSION    0
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_MODECNTRL_AR_RELEASE_MAJOR_VERSION != \
  CANIF_MODECNTRL_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_MODECNTRL.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_MODECNTRL_AR_RELEASE_MINOR_VERSION != \
  CANIF_MODECNTRL_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_MODECNTRL.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_MODECNTRL_AR_RELEASE_REVISION_VERSION != \
  CANIF_MODECNTRL_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_MODECNTRL.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_MODECNTRL_SW_MAJOR_VERSION != CANIF_MODECNTRL_C_SW_MAJOR_VERSION)
  #error "CANIF_MODECNTRL.c : Mismatch in Software Major Version"
#endif
#if (CANIF_MODECNTRL_SW_MINOR_VERSION != CANIF_MODECNTRL_C_SW_MINOR_VERSION)
  #error "CANIF_MODECNTRL.c : Mismatch in Software Minor Version"
#endif

/* polyspace-begin RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanIf_SetControllerMode                             **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service calls corresponding CAN Driver service **
**                        for changing of the CAN controller mode. It         **
**                        initiates a transition to the requested CAN         **
**                        controller mode of one or multiple CAN controllers. **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : Controller, ControllerMode                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s):   CanIf_CanIfStatus             **
**                                              CanIf_Controller              **
**                                              CanIf_ControllerConfigType    **
**                                                                            **
**                        Function(s) invoked:  Det_ReportError               **
**                                              CanIf_SetControllerModeService**
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */  
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01027 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE)CanIf_SetControllerMode (
                        VAR(uint8, CANIF_VAR) ControllerId,
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
                        VAR(Can_ControllerStateType, CANIF_VAR) ControllerMode)
#else
                        VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode)
#endif												
{
  /* @Trace: SWS_CANIF_00003 */
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
	  ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
	   (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  VAR(Std_ReturnType, CANIF_VAR) canReturn;
  #else
  VAR(Can_ReturnType, CANIF_VAR) canReturn;
  #endif

  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  VAR(Can_ControllerStateType, CANIF_VAR) controllerMode;
  #else
  VAR(CanIf_ControllerModeType, CANIF_VAR) controllerMode;
  #endif	
  /* Get request Controller mode */
  controllerMode = ControllerMode;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  
  retVal = CanIf_DETSetControllerMode(ControllerId, ControllerMode);
  
  /* Check if any development error occurred */
  if ((Std_ReturnType) E_OK == retVal)
  #endif  /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanIf_SUD_API_162 */
    /* Initialize the Standard Return Value with E_OK */
    retVal = (Std_ReturnType) E_OK;
    canReturn = CanIf_PreSetControllerMode(ControllerId, &controllerMode);

    if (CANIF_OK == canReturn)
    {
      canReturn = CanIf_SetControllerModeProcessing(ControllerId, controllerMode);
    }
    /* If Can  driver returns CAN_NOT_OK retVal returns E_NOT_OK */
    if (CANIF_NOT_OK == canReturn)
    {
      /* @Trace: CanIf_SUD_API_171 */
      retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      /*Do nothing*/
    }
  } /* End of if retVal = E_NOT_OK */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  else
  {
    CANIF_UNUSED(canReturn);
  }
  #endif  /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  return (retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace-end RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
/*******************************************************************************
** Function Name        : CanIf_SetBatteryVoltageMode                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service sets internal battery voltage mode     **
**                        for blocking transmit request when battery voltage  **
**                        level is abnormal.                                  **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : ControllerId, BatteryVolMode                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s):   CanIf_CanIfStatus             **
**                                              CanIf_Controller              **
**                                              CanIf_ControllerConfigType    **
**                                                                            **
**                        Function(s) invoked:  Det_ReportError               **
**                                              CanIf_SetControllerModeService**
*******************************************************************************/
#if (STD_ON == CANIF_CANCM_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: ESD_99001*/
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetBatteryVoltageMode(
                                             VAR(uint8, CANIF_VAR) ControllerId,
                         VAR(CanIf_BatVolSetModeType, CANIF_VAR) BatteryVolMode)
{
  /* @Trace: CanIf_SUD_API_134 */
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  VAR(uint8, CANIF_VAR) prevVolStatus;
  VAR(uint16, CANIF_VAR) count;
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;

  /* Initialize the Standard Return Value with E_OK */
  retVal = (uint8) E_OK;

 #if (STD_ON == CANIF_DEV_ERROR_DETECT)

  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_SET_PDU_MODE_SID, retVal);

  /* Report to DET, if requested channel is more than available controller */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_SET_PDU_MODE_SID, retVal);

  if ((uint8) E_OK == retVal)
  {
    /* @Trace: CanIf_SUD_API_172 */
    /* Get the pointer to corresponding Can Controller Config ControllerId*/
    ptrController = &CanIf_Controller[ControllerId];

    /* Report to DET, if requested controller mode is uninitialized (CAN_CS_UNINIT) */
    if (CANIF_UNINIT == ptrController->ControllerMode)
    {
      /* @Trace: CanIf_SUD_API_173 */
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                                        CANIF_SET_PDU_MODE_SID, CANIF_E_UNINIT);
      retVal = (uint8)E_NOT_OK;
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

  if ((uint8) E_OK == retVal)
  #endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanIf_SUD_API_174 */
    ptrController = &CanIf_Controller[ControllerId];

    /* Disable relevant interrupts */
    SchM_Enter_CanIf_MODE_STATUS_PROTECTION();

    prevVolStatus = ptrController->BatVolStatus;

    /* Update status Battery if BatteryVolMode is CANIF_SET_BATVOL_CRITICAL */
    if(CANIF_SET_BATVOL_CRITICAL == BatteryVolMode)
    {
      /* @Trace: CanIf_SUD_API_175 */
      ptrController->BatVolStatus = CANIF_TX_BAT_ERROR;
    }
    /* Update status Battery if BatteryVolMode is CANIF_SET_BATVOL_NORMAL */
    else if(CANIF_SET_BATVOL_NORMAL == BatteryVolMode)
    {
      /* @Trace: CanIf_SUD_API_176 */
      ptrController->BatVolStatus = CANIF_TX_BAT_NORMAL;
    }
    else
    {
      /* @Trace: CanIf_SUD_API_177 */
      retVal = (uint8)E_NOT_OK;
    }

    #if (STD_ON == CANIF_TX_LPDU)
    /* Update Tx Gateway Buffer Status */
    if((prevVolStatus==CANIF_TX_BAT_NORMAL) &&
                           (ptrController->BatVolStatus == CANIF_TX_BAT_ERROR))
    {
      /* @Trace: CanIf_SUD_API_178 */
      /* Get the pointer to corresponding Can Controller structure */
      #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
      ptrStaticController = &CanIfControllerConfig[ControllerId];
      #else
      ptrStaticController = &CanIf_ControllerConfig[ControllerId];
      #endif

      ptrTxLpdu = ptrStaticController->TxLpdu;
      for(count = CANIF_ZERO; count < ptrStaticController->NoOfTxPdu; count++)
      {
        if(CanIf_TxPduGwStatus[ptrTxLpdu->TxPduId] != CANIF_GW_NOCOMM)
        {
          /* @Trace: CanIf_SUD_API_179 */
          CanIf_TxPduGwStatus[ptrTxLpdu->TxPduId] = CANIF_GW_ERRVOL;
        }
        else
        {
        	/* Do nothing */
        }
        ptrTxLpdu++;
      }
    }
    else if((prevVolStatus==CANIF_TX_BAT_ERROR) &&
                          (ptrController->BatVolStatus == CANIF_TX_BAT_NORMAL))
    {
      /* @Trace: CanIf_SUD_API_180 */
      /* Get the pointer to corresponding Can Controller structure */
      #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
      ptrStaticController = &CanIfControllerConfig[ControllerId];
      #else
      ptrStaticController = &CanIf_ControllerConfig[ControllerId];
      #endif

      ptrTxLpdu = ptrStaticController->TxLpdu;
      for(count = CANIF_ZERO; count < ptrStaticController->NoOfTxPdu; count++)
      {
        if(CanIf_TxPduGwStatus[ptrTxLpdu->TxPduId] != CANIF_GW_NOCOMM)
        {
          if(CANIF_TX_STATUS(ptrController->PduMode) == CANIF_TX_DISABLED)
          {
            /* @Trace: CanIf_SUD_API_181 */
            CanIf_TxPduGwStatus[ptrTxLpdu->TxPduId] = CANIF_GW_STOPPED;
          }
          else{
            /* @Trace: CanIf_SUD_API_182 */
            CanIf_TxPduGwStatus[ptrTxLpdu->TxPduId] = CANIF_GW_NOREQUEST;
          }
        }
        else
        {
        	/* Do nothing */
        }
        ptrTxLpdu++;
      }
    }
    else
    {
      /* Do nothing */
    }
    #endif /* (STD_ON == CANIF_TX_LPDU) */
    /* Enable relevant interrupts */
    SchM_Exit_CanIf_MODE_STATUS_PROTECTION();
  }
  return retVal;
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_SetPduMode                                    **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This service sets the requested mode at all L-PDUs  **
**                        of the predefined logical PDU channel. The channel  **
**                        parameter can be derived from Controller.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : ControllerId, PduModeRequest                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_CanIfStatus               **
**                                            CanIf_Controller                **
**                                            CanIf_ControllerConfigType      **
**                        Function(s)invoked: CanIf_ClearTxQueue              **
**                                            CanIf_SetTxOrRxSts,             **
**                                            SchM_Enter_CanIf_MODE_STATUS_   **
**                                            PROTECTION,                     **
**                                            SchM_Exit_CanIf_MODE_STATUS_    **
**                                            PROTECTION                      **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 SRS_Can_01013 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetPduMode (
                            VAR(uint8, CANIF_VAR) ControllerId,
                            VAR(CanIf_PduModeType, CANIF_VAR) PduModeRequest)
{
  /* @Trace: CanIf_SUD_API_068 */
  /* @Trace: SWS_CANIF_00008 */
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  #if ((STD_ON == CANIF_BASIC_CAN_TXPDU) && (STD_ON == CANIF_TX_QUEUE))
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;
  VAR(uint8, CANIF_VAR) txStatus;
  #endif
  #if (STD_OFF == CANIF_DEV_ERROR_DETECT)
  /* Initialize the Standard Return Value with E_OK */
  retVal = (Std_ReturnType) E_OK;
  #endif
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)

  retVal = CanIf_DETSetPduMode(ControllerId, PduModeRequest);

  /* Check if any development error occurred? */
  if ((Std_ReturnType) E_OK == retVal)
  #endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanIf_SUD_API_185 */
    /* Get the pointer to corresponding Can Controller Config ControllerId*/
    ptrController = &CanIf_Controller[ControllerId];

    if (CANIF_STARTED == ptrController->ControllerMode)
    {
      /* @Trace: CanIf_SUD_API_064 */
      /* Disable relevant interrupts */
      SchM_Enter_CanIf_MODE_STATUS_PROTECTION();

      /* Update the Rx and Tx status based on current channel status
      and controller status */
      CanIf_SetTxOrRxSts(ControllerId, PduModeRequest);

      /* Enable relevant interrupts */
      SchM_Exit_CanIf_MODE_STATUS_PROTECTION();
      /* polyspace +15 RTE:UNR [Justified:Low] "It depends on the configuration of CanIf. No impact" */
      #if (STD_ON == CANIF_PN_SUPPORT)
      if (CANIF_TX_OFFLINE == PduModeRequest)
      {
        /* Check if partial networking is enabled for specific controller */
        /* polyspace +4 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */  
        #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
        if (CANIF_TRUE == CanIfControllerConfig[ControllerId].PartialNWEnabled)
        #else
        if (CANIF_TRUE == CanIf_ControllerConfig[ControllerId].PartialNWEnabled)
        #endif
        {
          /* @Trace: CanIf_SUD_API_065 Tx Status of controller is updated as CANIF_TX_PNENABLED */
          /* @Trace: SWS_CANIF_00878 */
          CANIF_SET_TX_PNENABLED(ptrController->PduMode);
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
      #endif /*#if (STD_ON == CANIF_PN_SUPPORT)*/
      #if ((STD_ON == CANIF_BASIC_CAN_TXPDU) && (STD_ON == CANIF_TX_QUEUE))	
      /* Clear Tx queue if Tx Status is changed to offline active */
      txStatus = (uint8)CANIF_TX_STATUS(ptrController->PduMode);

      /* check the TxStatus of the controller*/
      if ((CANIF_TX_DISABLED == txStatus) 
      /* @Trace: CanIf_SUD_API_066 */
      #if (STD_ON == CANIF_TX_OFFLINE_ACTIVE_SUPPORT)
        || ((uint8)CANIF_TX_OFFLINE_ACTIVE == txStatus)	
      #endif		
      )
      {
        #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
        ptrStaticController = &CanIfControllerConfig[ControllerId];
        #else
        ptrStaticController = &CanIf_ControllerConfig[ControllerId];
        #endif

        /* Disabling relevant interrupts*/
        /* @Trace: CanIf_SUD_API_067 */
        SchM_Enter_CanIf_TX_QUEUE_PROTECTION();

        /* Clear Tx queue */
        CanIf_ClearTxQueue(ptrStaticController);

        /* Enabling relevant interrupts*/
        SchM_Exit_CanIf_TX_QUEUE_PROTECTION();
      }
      else
      {
        /* Do nothing */
      }
      #endif 
    }/* @ if ((CAN_CS_STARTED == ptrController->ControllerMode)*/
    else
    {
      /* @Trace: CanIf_SUD_API_186 */
      /* @Trace: SWS_CANIF_00874 Not accept any request and return E_NOT_OK */
      retVal = (Std_ReturnType)E_NOT_OK;
    }
  }/*if (E_OK == retVal)*/
  /* Return the value */
  return (retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_GetControllerMode                             **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This service reports about the current status of    **
**                        the requested CAN Controller.                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : ControllerId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : ControllerModePtr                                   **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s)  : CanIf_CanIfStatus,            **
**                                              CanIf_Controller              **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01028 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE)CanIf_GetControllerMode (
  VAR(uint8, CANIF_VAR) ControllerId,
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
  ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
   (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))  
  P2VAR(Can_ControllerStateType, AUTOMATIC, CANIF_APPL_DATA) ControllerModePtr)
  #else
  P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_APPL_DATA) ControllerModePtr)	  
  #endif	  
{
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT) && \
      ((CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
       ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
        (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE)))
  P2CONST(CanIf_CanDriverType, AUTOMATIC, CANIF_CONST) ptrDriver;
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;
  #endif
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  /* Initialize the Standard Return Value with E_OK */
  retVal = (uint8) E_OK;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_GET_CNTRL_MODE_SID, retVal);

  /* Report to DET, if requested channel is more than available controller */
  /* @Trace: CanIf_SUD_API_124 */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_GET_CNTRL_MODE_SID, retVal);

  /* Report to DET, if pointer is NULL */
  /* @Trace: CanIf_SUD_API_125 */
  CANIF_NULL_PTR_ERROR(CANIF_GET_CNTRL_MODE_SID, retVal, ControllerModePtr);

  /* Check If any DET error occurred? */
  if ((uint8) E_OK == retVal)
  #endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanIf_SUD_API_187 */
    ptrController = &CanIf_Controller[ControllerId];
    #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
        ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
        (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))

    #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrStaticController = &CanIfControllerConfig[ControllerId];
    #else
    ptrStaticController = &CanIf_ControllerConfig[ControllerId];
    #endif

    /* Get the pointer to corresponding Can Driver structure */
    ptrDriver = &CanIf_CanDriver[ptrStaticController->CanDriverId];

    /* Invoke the function to set the controller mode for Can Driver */
    retVal = ptrDriver->CanGetControllerMode(ControllerId, &ptrController->ControllerMode);

    #else
    /* Invoke the function to set the controller mode for for Can Driver */
    retVal = Can_GetControllerMode(ControllerId, &ptrController->ControllerMode);
    #endif /*#if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)*/
    /* polyspace +1 DEFECT:DEAD_CODE MISRA2012:2.1,14.3 [Not a defect:Justified] "It's depend on the configuration of Can. No impact" */
    if ((uint8) E_OK == retVal)
    #endif /*#if ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) ...*/
    {
      /* @Trace: CanIf_SUD_API_188 */
      /* Get the controller mode from the controller structure */
      /* polyspace +3 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
      /* polyspace +2 MISRA2012:D4.14 [Not a defect:Low] "It's value checked by Det" */
      /* polyspace +1 MISRA2012:10.5 [No action planned:Low] "Value is checked"*/
      *ControllerModePtr = ptrController->ControllerMode;
    }
  }/*if (E_OK == retVal)*/
  /* Return the standard return value */
  return (retVal);
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_GetControllerErrorState                       **
**                                                                            **
** Service ID           : 0x4b                                                **
**                                                                            **
** Description          : This service calls the corresponding CAN Driver     **
                          service for obtaining the error state of the CAN    **
                          controller.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant for the same ControllerId             **
**                                                                            **
** Input Parameters     : ControllerId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : ErrorStatePtr                                       **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s)  : CanIf_CanIfStatus,            **
**                                              CanIf_Controller              **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
/* polyspace +6 MISRA2012:8.13 [Not a defect:Low] " This function definition follow Autosar requirement SWS_CANIF_91001. No impact "*/
/* @Trace: SRS_Can_01169 SRS_BSW_00323 */
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE)CanIf_GetControllerErrorState (
  VAR(uint8, CANIF_VAR) ControllerId,
  P2VAR(Can_ErrorStateType, AUTOMATIC, CANIF_APPL_DATA) ErrorStatePtr)
{
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT) && \
      ((CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
       ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
        (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE)))
  P2CONST(CanIf_CanDriverType, AUTOMATIC, CANIF_CONST) ptrDriver;
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;
  #endif /*#if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT) ...*/
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  /* Initialize the Standard Return Value with E_OK */
  retVal = (uint8) E_OK;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_GET_CNTRL_ERROR_STATE_SID, retVal);

  /* @Trace: SWS_CANIF_00898 */
  /* Report to DET, if requested channel is more than available controller */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_GET_CNTRL_ERROR_STATE_SID, retVal);

  /* @Trace: SWS_CANIF_00899 */
  /* Report to DET, if pointer is NULL */
  CANIF_NULL_PTR_ERROR(CANIF_GET_CNTRL_ERROR_STATE_SID, retVal, ErrorStatePtr);

  /* Check If any DET error occurred? */
  if ((uint8) E_OK == retVal)
  #endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanIf_SUD_API_189 */
    #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
        ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
         (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
    #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrStaticController = &CanIfControllerConfig[ControllerId];
    #else
    ptrStaticController = &CanIf_ControllerConfig[ControllerId];
    #endif

    /* Get the pointer to corresponding Can Driver structure */
    ptrDriver = &CanIf_CanDriver[ptrStaticController->CanDriverId];

    /* Invoke the function to get the controller error state for Can Driver */
    retVal = ptrDriver->CanGetControllerErrorState(ControllerId, ErrorStatePtr);

    #else
    /* Invoke the function to set the controller error state for for Can Driver */
    retVal = Can_GetControllerErrorState(ControllerId, ErrorStatePtr);

    #endif /* #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT) */
	  #else
    CANIF_UNUSED(ControllerId);

    CANIF_UNUSED(ErrorStatePtr);

	  retVal = E_NOT_OK;
    #endif /*((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) ...*/
  }
  return retVal;
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_GetPduMode                                    **
**                                                                            **
** Service ID           : 0x0A                                                **
**                                                                            **
** Description          : This service reports about the current status of    **
**                        the requested Pdu channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : ControllerId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : PduModePtr                                          **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s)  : CanIf_CanIfStatus,            **
**                                              CanIf_Controller              **
**                                                                            **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE)CanIf_GetPduMode (
             VAR(uint8, CANIF_VAR) ControllerId,
             P2VAR(CanIf_PduModeType, AUTOMATIC, CANIF_APPL_DATA) PduModePtr)
{
  /* @Trace: CanIf_SUD_API_126 */
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  /* Initialize the Standard Return Value with E_OK */
  retVal = (Std_ReturnType) E_OK;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_GET_PDU_MODE_SID, retVal);

  /* Report to DET, if requested channel is more than available controller */
  /* @Trace: CanIf_SUD_API_127 */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_GET_PDU_MODE_SID, retVal);

  /* Report to DET, if pointer is NULL */
  /* @Trace: CanIf_SUD_API_128 */
  CANIF_NULL_PTR_ERROR(CANIF_GET_PDU_MODE_SID, retVal, PduModePtr);

  /* Check If any DET error occurred? */
  if ( retVal == (Std_ReturnType)E_OK)
  #endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanIf_SUD_API_190 */
    /* Get the pointer to corresponding Can Controller Config ControllerId*/
    ptrController = &CanIf_Controller[ControllerId];
    /* polyspace +2 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */  
    /* polyspace +17 MISRA2012:D4.14 [Not a defect:Low] "It's value is pre-define" */
    switch (CANIF_PDU_MODE(ptrController->PduMode)) 
    {
      case CANIF_ZERO:
      /* @Trace: CanIf_SUD_API_191 */
        *PduModePtr = CANIF_OFFLINE;
        break;     
      case CANIF_ONE:  
      /* @Trace: CanIf_SUD_API_192 */  
        *PduModePtr = CANIF_TX_OFFLINE;
        break;     
      case CANIF_TWO: 
      /* @Trace: CanIf_SUD_API_193 */  
        *PduModePtr = CANIF_TX_OFFLINE_ACTIVE;
        break;   
      default:
      /* @Trace: CanIf_SUD_API_194 */
        *PduModePtr = CANIF_ONLINE;
        break;
    };
  }/*if (E_OK == retVal)*/
  /* Return the standard return value */
  return (retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_SetTxOrRxSts                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine Sets Tx or Rx Status based on Current  **
**                        Mode Channel Status for Controller.                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : ControllerId, pduMode                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */  
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC (void, CANIF_CODE) CanIf_SetTxOrRxSts (VAR(uint8, CANIF_VAR) ControllerId,
                      VAR(CanIf_PduModeType, CANIF_VAR) pduMode)
{
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  /* Get the pointer of current controller structure*/
  ptrController = &CanIf_Controller[ControllerId];

  #if (STD_ON == CANIF_TX_LPDU)
  VAR(uint8, CANIF_VAR) prevTxStatus;
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;
  VAR(uint16, CANIF_VAR) count;
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  prevTxStatus = (uint8)CANIF_TX_STATUS(ptrController->PduMode);
  #endif

  /* New PDU mode.
   * The following flags will be cleared:
   * - Rx Validate wake up (The four bit)
   * - Tx confirmed (The fifth bit)
   */
  CANIF_SET_PDU_MODE(ptrController->PduMode, pduMode);

  /* Get the pointer to corresponding Can Controller structure */
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  ptrStaticController = &CanIfControllerConfig[ControllerId];
  #else
  ptrStaticController = &CanIf_ControllerConfig[ControllerId];
  #endif
  /* Update Tx Gateway Buffer Status only if voltage is normal */
  #if (STD_ON == CANIF_TX_LPDU)
  #if (STD_ON == CANIF_CANCM_SUPPORT)
  if(ptrController->BatVolStatus != CANIF_TX_BAT_ERROR)
  #endif
  {
    if((prevTxStatus==CANIF_TX_ENABLED) &&
      (CANIF_TX_STATUS(ptrController->PduMode) == CANIF_TX_DISABLED))
    {
      /* @Trace: CanIf_SUD_API_195 */
      ptrTxLpdu = ptrStaticController->TxLpdu;
      for(count = CANIF_ZERO; count < ptrStaticController->NoOfTxPdu ; count++)
      {
        /* @Trace: CanIf_SUD_API_196 */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
	CanIf_TxPduGwStatus[ptrTxLpdu->TxPduId] = CANIF_GW_STOPPED;
        ptrTxLpdu++;
      }
    }
    else if((prevTxStatus==CANIF_TX_DISABLED) &&
    (CANIF_TX_STATUS(ptrController->PduMode) == CANIF_TX_ENABLED))
    {
      /* @Trace: CanIf_SUD_API_197 */
      ptrTxLpdu = ptrStaticController->TxLpdu;

      for(count = CANIF_ZERO; count < ptrStaticController->NoOfTxPdu ; count++)
      {
        /* @Trace: CanIf_SUD_API_198 */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
	CanIf_TxPduGwStatus[ptrTxLpdu->TxPduId] = CANIF_GW_NOREQUEST;
        ptrTxLpdu++;
      }
    }
    else
    {
      /* Do Nothing */
    }
  }
#endif /* (STD_ON == CANIF_TX_LPDU) */
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace-end RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */  
/*******************************************************************************
** Function Name        : CanIf_ControllerModeIndication                      **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : This service indicates a controller state transition**
**                        referring to the corresponding CAN controller       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ControllerId, ControllerMode                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : CanIf_ControllerConfigType,    **
**                                             CanIf_CanIfStatus,             **
**                                             CanIf_Controller               **
**                        Function(s) invoked: SchM_Exit_CanIf_MODE_STATUS_   **
**                                             PROTECTION,                    **
**                                             CanSM_ControllerModeIndication **
**                                             CanIf_ClearTxQueue,            **
**                                             SchM_Enter_CanIf_MODE_STATUS_  **
**                                             PROTECTION,                    **
**                                             IdsM_ControllerModeIndication  **
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */  
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01114 */
FUNC(void, CANIF_CODE) CanIf_ControllerModeIndication (
                        VAR(uint8, CANIF_VAR) ControllerId,
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
                        VAR(Can_ControllerStateType, CANIF_VAR) ControllerMode)
#else
                        VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode)
#endif
{
  /* @Trace: CanIf_SUD_API_115   */  
  VAR(Can_ControllerStateType, CANIF_VAR) controllerMode;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  /* Initialize the Standard Return Value with E_OK */
  retVal = CanIf_DETControllerModeIndication(ControllerId, ControllerMode);

  /* Check If any DET error occurred? */
  if ((Std_ReturnType) E_OK == retVal)
  #endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    CanIf_ControllerModeIndicationProcessing(ControllerId, ControllerMode);

    
    

    #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
    controllerMode = ControllerMode;
    #else
    switch (ControllerMode)
    {
      case CANIF_CS_SLEEP:
      /* @Trace: CanIf_SUD_API_206 */
        controllerMode = CAN_CS_SLEEP;
        break;
      case CANIF_CS_STARTED:
      /* @Trace: CanIf_SUD_API_207 */
        controllerMode = CAN_CS_STARTED;
        break;
      case CANIF_CS_STOPPED:
      /* @Trace: CanIf_SUD_API_208 */
        controllerMode = CAN_CS_STOPPED;
        break;
      /* polyspace +3 RTE:UNR [Not a defect:Low] "It has been checked, no impact" */
      default:
      /* @Trace: CanIf_SUD_API_209 */
        controllerMode = CAN_CS_UNINIT;
        break;
    }
    #endif
    /* Invoke CanSM/Cdd_ControllerModIndication */
    /* @Trace: CanIf_SUD_API_123 */
    CANIF_DISPATCH_USERCTRLMODEINDICATION_NAME(ControllerId, controllerMode);
    
    #if (STD_ON == CANIF_IDSM_SUPPORT)
    IdsM_ControllerModeIndication(ControllerId, controllerMode);
    #endif

  } /* @ if ((uint8) E_OK == retVal) */
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace-end RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */  

/*******************************************************************************
** Function Name        : CanIf_SetControllerModeService                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to invoke the                 **
**                        Can_SetControllerMode                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : Controller, CanMode                                 **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanIf_Init() should be invoked                      **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_CanDriver                 **
**                                            CanIf_ControllerConfigType      **
**                                                                            **
**                        Function(s) invoked: Can_SetControllerMode          **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetControllerModeService (
                                VAR(uint8, CANIF_VAR) Controller,
                                VAR(Can_ControllerStateType, CANIF_VAR) CanMode)
#else
FUNC(Can_ReturnType, CANIF_CODE) CanIf_SetControllerModeService (
                                VAR(uint8, CANIF_VAR) Controller,
                                VAR(Can_StateTransitionType, CANIF_VAR) CanMode)
#endif
{
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  VAR(Std_ReturnType, CANIF_VAR) drvRetVal;
  #else
  VAR(Can_ReturnType, CANIF_VAR) drvRetVal;
  #endif

  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  P2CONST(CanIf_CanDriverType, AUTOMATIC, CANIF_CONST) ptrDriver;
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;

  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  ptrStaticController = &CanIfControllerConfig[Controller];
  #else
  ptrStaticController = &CanIf_ControllerConfig[Controller];
  #endif

  /* Get the pointer to corresponding Can Driver structure */
  ptrDriver = &CanIf_CanDriver[ptrStaticController->CanDriverId];

  /* Invoke the function to set the controller mode for Can Driver*/
  drvRetVal = ptrDriver->CanSetControllerMode(CAN_CONTROLLER_ID, CanMode);
  
  #else
  
  #if (CANIF_ONE != CANIF_NO_OF_CONTROLLER)
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;

  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  ptrStaticController = &CanIfControllerConfig[Controller];
  #else
  ptrStaticController = &CanIf_ControllerConfig[Controller];
  #endif
  
  #endif
  
  /* Invoke the function to set the controller mode for Can Driver*/
  drvRetVal = Can_SetControllerMode(CAN_CONTROLLER_ID, CanMode);
  #endif

  return(drvRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_EnableBusMirroring                      	  **
**                                                                            **
** Service ID           : 0x4c                                                **
**                                                                            **
** Description          : Enables or disables mirroring for a CAN controller  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ControllerId, MirroringActive                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Bus Mirroring is enabled                            **
**                                                                            **
** Remarks              : Global Variable(s):  CanIf_Controller               **
**                                                                            **
**                        Function(s) invoked: Can_EnableBusMirroring         **
*******************************************************************************/
#if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01172 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_EnableBusMirroring (
                                VAR(uint8, CANIF_VAR) ControllerId,
                                VAR(boolean, CANIF_VAR) MirroringActive)
{
  /* @Trace: SWS_CANIF_91005 */
  /* @Trace: CanIf_SUD_API_137 */
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;

  /* Initialize the det error flag status*/
  retVal = (Std_ReturnType) E_OK;

  /* If the Development errors detection is enabled */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_ENABLE_BUS_MIRRORING_SID, retVal);

  /* @Trace: SWS_CANIF_00912 */
  /* Report to DET, if requested controller id is more than available
  controller */
  /* @Trace: CanIf_SUD_API_138 */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_ENABLE_BUS_MIRRORING_SID, retVal);

  /* check for any development occurred? */
  if ((Std_ReturnType) E_OK == retVal)
  #endif /* CANIF_DEV_ERROR_DETECT */
  {
    /* @Trace: CanIf_SUD_API_139 */
    /* Get the pointer of current controller structure*/
    ptrController = &CanIf_Controller[ControllerId];

    /* Store MirroringActive value*/
    /* @Trace: SWS_CANIF_00905 SWS_CANIF_00904 */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */  
    ptrController->MirroringActive = MirroringActive;

  }/*if (E_OK == retVal)*/

  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_SetIcomConfiguration                      	  **
**                                                                            **
** Service ID           : 0x25                                                **
**                                                                            **
** Description          : This service shall change the Icom Configuration    **
**                        of a CAN controller to the requested one.           **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant only for different controller Ids         **
**                                                                            **
** Input Parameters     : ControllerId, ConfigurationId                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanIfPublicIcomSupport is enable                    **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_ControllerConfig          **
**                                            CanIf_CanDriver                 **
**                        Function(s) invoked: Can_SetIcomConfiguration       **
*******************************************************************************/
#if (STD_ON == CANIF_PUBLIC_ICOM_SUPPORT) /* @Trace: SWS_CANIF_00875 */
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetIcomConfiguration (
                                VAR(uint8, CANIF_VAR) ControllerId,
                                VAR(IcomConfigIdType, CANIF_VAR) ConfigurationId)
{
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  P2CONST(CanIf_CanDriverType, AUTOMATIC, CANIF_CONST) ptrDriver;
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;
  #endif

  VAR(Std_ReturnType, CANIF_VAR) retVal;

  /* Initialize the det error flag status*/
  retVal = (Std_ReturnType) E_OK;

  /* If the Development errors detection is enabled */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)

  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_SET_ICOM_CONFIGURATION_SID, retVal);

  /* @Trace: SWS_CANIF_00872 */
  /* Report to DET, if requested controller id is more than available
  controller */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_SET_ICOM_CONFIGURATION_SID, retVal);

  /* check for any development occurred? */
  if ((Std_ReturnType) E_OK == retVal)
  #endif /* CANIF_DEV_ERROR_DETECT */
  {
    /* @Trace: CanIf_SUD_API_210 */
    #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrStaticController = &CanIfControllerConfig[ControllerId];
    #else
    ptrStaticController = &CanIf_ControllerConfig[ControllerId];
    #endif
    
    ptrDriver = &CanIf_CanDriver[ptrStaticController->CanDriverId];

    /* Invoke the function to set  Icom Configuration for Can Driver */
    /* @Trace: SWS_CANIF_00838 */
    retVal =(Std_ReturnType)ptrDriver->CanSetIcomConfiguration(ControllerId, ConfigurationId);
    
    #else
    /* Invoke the function to set  Icom Configuration for Can Driver */
    #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
        ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
         (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
    retVal = (Std_ReturnType)Can_SetIcomConfiguration(ControllerId, ConfigurationId);
	  
    #else
    /* @Trace: SWS_CANIF_00838 */
    retVal = (Std_ReturnType)Can_17_McmCan_SetIcomConfiguration(ControllerId, ConfigurationId);
    
    #endif /*#if ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \*/
    #endif /*#if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)*/
  }/*if (E_OK == retVal)*/

  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_GetControllerRxErrorCounter                   **
**                                                                            **
** Service ID           : 0x4d                                                **
**                                                                            **
** Description          : This service calls the corresponding CAN Driver     **
**                        service for obtaining the Rx error counter of       **
**                        the CAN controller                                  **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant for the same ControllerId             **
**                                                                            **
** Input Parameters     : ControllerId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : RxErrorCounterPtr                                   **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_ControllerConfig          **
**                                            CanIf_CanDriver                 **
**                        Function(s) invoked: Can_GetControllerRxErrorCounter**
*******************************************************************************/
/* polyspace +6 MISRA2012:8.13 [Not a defect:Low] " This function definition follow Autosar requirement SWS_CANIF_91003. No impact "*/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerRxErrorCounter (
                                VAR(uint8, CANIF_VAR) ControllerId,
                                P2VAR(uint8, AUTOMATIC, CANIF_VAR) RxErrorCounterPtr)
{
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT) && \
      ((CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
       ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
        (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_FOUR)))
  P2CONST(CanIf_CanDriverType, AUTOMATIC, CANIF_CONST) ptrDriver;
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;
  #endif
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  /* Initialize the det error flag status*/
  retVal = (Std_ReturnType) E_OK;

  /* If the Development errors detection is enabled */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)

  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_GET_CONTROLLER_RX_ERROR_COUNTER_SID, retVal);

  /* @Trace: SWS_CANIF_00907 */
  /* Report to DET, if requested controller id is more than available
  controller */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_GET_CONTROLLER_RX_ERROR_COUNTER_SID, retVal);

  /* @Trace: SWS_CANIF_00908 */
  /* Report to DET, if TxErrorCounterPtr  is Invalid  */
  CANIF_NULL_PTR_ERROR(CANIF_GET_CONTROLLER_RX_ERROR_COUNTER_SID, retVal, \
                       RxErrorCounterPtr);

  /* check for any development occurred? */
  if ((Std_ReturnType) E_OK == retVal)
  #endif /* CANIF_DEV_ERROR_DETECT */
  {
    /* @Trace: CanIf_SUD_API_211 */
    #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
        ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
         (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_FOUR))
    #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrStaticController = &CanIfControllerConfig[ControllerId];
    #else
    ptrStaticController = &CanIf_ControllerConfig[ControllerId];
    #endif

    /* Get the pointer to corresponding Can Driver structure */
    ptrDriver = &CanIf_CanDriver[ptrStaticController->CanDriverId];

    /* Invoke the function to get the Rx error counter of the CAN Driver */
    retVal = ptrDriver->CanGetControllerRxErrorCounter(ControllerId, RxErrorCounterPtr);

    #else
    /* Invoke the function to get the Rx error counter of the CAN controller */
    retVal = Can_GetControllerRxErrorCounter(ControllerId, RxErrorCounterPtr);

    #endif /* #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)*/
    #else

    CANIF_UNUSED(ControllerId);
    CANIF_UNUSED(RxErrorCounterPtr);
	  retVal = (Std_ReturnType)E_NOT_OK;

	  #endif /*#if ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR)...*/
  }/* @ if (E_OK == retVal)*/

  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_GetControllerTxErrorCounter                   **
**                                                                            **
** Service ID           : 0x4e                                                **
**                                                                            **
** Description          : This service calls the corresponding CAN Driver     **
**                        service for obtaining the Tx error counter of       **
**                        the CAN controller                                  **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant for the same ControllerId             **
**                                                                            **
** Input Parameters     : ControllerId                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : TxErrorCounterPtr                                   **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_ControllerConfig          **
**                                            CanIf_CanDriver                 **
**                        Function(s) invoked: Can_GetControllerTxErrorCounter**
*******************************************************************************/
/* polyspace +6 MISRA2012:8.13 [Not a defect:Low] " This function definition follow Autosar requirement SWS_CANIF_91004. No impact "*/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323  */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerTxErrorCounter (
                                VAR(uint8, CANIF_VAR) ControllerId,
                                P2VAR(uint8, AUTOMATIC, CANIF_VAR) TxErrorCounterPtr)
{
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT) && \
      ((CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
       ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
        (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_FOUR)))
  P2CONST(CanIf_CanDriverType, AUTOMATIC, CANIF_CONST) ptrDriver;
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;
  #endif /*#if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT) && \*/

  VAR(Std_ReturnType, CANIF_VAR) retVal;

  /* Initialize the det error flag status*/
  retVal = (Std_ReturnType) E_OK;

  /* If the Development errors detection is enabled */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)

  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_GET_CONTROLLER_TX_ERROR_COUNTER_SID, retVal);

  /* @Trace: SWS_CANIF_00909 */
  /* Report to DET, if requested controller id is more than available
  controller */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_GET_CONTROLLER_TX_ERROR_COUNTER_SID, retVal);

  /* @Trace: SWS_CANIF_00910 */
  /* Report to DET, if TxErrorCounterPtr  is Invalid  */
  CANIF_NULL_PTR_ERROR(CANIF_GET_CONTROLLER_TX_ERROR_COUNTER_SID, retVal, \
                       TxErrorCounterPtr);

  /* check for any development occurred? */
  if ((Std_ReturnType) E_OK == retVal)
  #endif /* CANIF_DEV_ERROR_DETECT */
  {
    /* @Trace: CanIf_SUD_API_212 */
    #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
        ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
         (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_FOUR))
    #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrStaticController = &CanIfControllerConfig[ControllerId];
    #else
    ptrStaticController = &CanIf_ControllerConfig[ControllerId];
    #endif

    ptrDriver = &CanIf_CanDriver[ptrStaticController->CanDriverId];
    /* Invoke the function to get the Tx error for Can Driver */

    retVal = ptrDriver->CanGetControllerTxErrorCounter(ControllerId, TxErrorCounterPtr);

    #else
    /* Invoke the function to get the Tx error for for Can Driver */
    retVal = Can_GetControllerTxErrorCounter(ControllerId, TxErrorCounterPtr);

    #endif /*#if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)*/
    #else /* #if((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR)... */

    CANIF_UNUSED(ControllerId);
    CANIF_UNUSED(TxErrorCounterPtr);
    retVal = (Std_ReturnType)E_NOT_OK;

    #endif /*#if((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \*/
  }/* @ if (E_OK == retVal)*/

  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_CurrentIcomConfiguration                      **
**                                                                            **
** Service ID           : 0x26                                                **
**                                                                            **
** Description          : This service shall inform about the change          **
**                        of the Icom Configuration of a CAN controller       **
**                        using the abstract CanIf ControllerId.  		        **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant only for different controller Ids         **
**                                                                            **
** Input Parameters     : ControllerId, ConfigurationId, Error                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s):               				          **
**                                                                            **
**                        Function(s) invoked: CanSM_CurrentIcomConfiguration **
*******************************************************************************/
#if (CANIF_PUBLIC_ICOM_SUPPORT == STD_ON) /* @Trace: SWS_CANIF_00876 */
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323
           */
FUNC(void, CANIF_CODE) CanIf_CurrentIcomConfiguration (
                                VAR(uint8, CANIF_VAR) ControllerId,
                                VAR(IcomConfigIdType, CANIF_VAR) ConfigurationId,
                                VAR(IcomSwitch_ErrorType, CANIF_VAR) Error)
{
  /* Initialize the det error flag status*/
  /* If the Development errors detection is enabled */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Can_ReturnType, CANIF_VAR) retVal;
  retVal = E_OK;

  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CURRENT_ICOM_CONFIGURATION_SID, retVal);

  /* @Trace: SWS_CANIF_00873 */
  /* Report to DET, if requested controller id is more than available
  controller */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_CURRENT_ICOM_CONFIGURATION_SID, retVal);

  /* check for any development occurred? */
  if ((uint8) E_OK == retVal)
  #endif /* CANIF_DEV_ERROR_DETECT */
  {
    /* @Trace: CanIf_SUD_API_213 */
    /* @Trace: SWS_CANIF_00839 */
    CanSM_CurrentIcomConfiguration(ControllerId, ConfigurationId, Error);

  }/*if (E_OK == retVal)*/

}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_ReadBusMsgCount                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall provide Tx/Rx Message Counts of  **
**                        CAN Channel.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : Controller                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : MsgCnt                                              **
**                                                                            **
** Preconditions        : CanIf_Init() should be invoked                      **
**                                                                            **
** Remarks              : None                                                **
*******************************************************************************/
#if (CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_ReadBusMsgCount(VAR(uint8, CANIF_VAR) Controller,
                      P2VAR(CanIf_MsgType, AUTOMATIC, CANIF_APPL_DATA) MsgCnt)
{
  /* polyspace +4 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
  /* polyspace +3 RTE:IDP [Not a defect: Justified] "Pointer is not outside its bounds." */
  /* polyspace +2 RTE:OBAI [Not a defect: Justified] "Pointer is not outside its bounds." */
  MsgCnt->TxMsgCnt = CanIf_TxMsgCnt[Controller];
  MsgCnt->RxMsgCnt = CanIf_RxMsgCnt[Controller];
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : CanIf_ControllerModeIndicationProcessing            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service indicates a controller state transition**
**                        referring to the corresponding CAN controller       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ControllerId, ControllerMode                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : CanIf_ControllerConfigType,    **
**                                             CanIf_CanIfStatus,             **
**                                             CanIf_Controller               **
**                        Function(s) invoked: SchM_Exit_CanIf_MODE_STATUS_   **
**                                             PROTECTION,                    **
**                                             CanSM_ControllerModeIndication **
**                                             CanIf_ClearTxQueue,            **
**                                             SchM_Enter_CanIf_MODE_STATUS_  **
**                                             PROTECTION,                    **
**                                             IdsM_ControllerModeIndication  **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_ControllerModeIndicationProcessing (
                        VAR(uint8, CANIF_VAR) ControllerId,
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
                        VAR(Can_ControllerStateType, CANIF_VAR) ControllerMode)
#else
                        VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode)
#endif
{
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  #if (STD_ON == CANIF_TX_LPDU)
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  ptrStaticController = &CanIfControllerConfig[ControllerId];
  #else
  ptrStaticController = &CanIf_ControllerConfig[ControllerId];
  #endif
  VAR(uint8, CANIF_VAR) prevTxStatus;
  VAR(uint16, CANIF_VAR) count;
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  #endif


  /* @Trace: CanIf_SUD_API_199 */
  /* Get the pointer to corresponding Can Controller Config ControllerId*/
  ptrController = &CanIf_Controller[ControllerId];

  /* Enable relevant interrupts */
  SchM_Enter_CanIf_MODE_STATUS_PROTECTION();
  /* polyspace +2 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
  /* Store the requested mode */
  ptrController->ControllerMode = ControllerMode;

  /* Check whether current mode is started or not */
  switch (ControllerMode)
  {
    case CANIF_STARTED: /* CAN_CS_STARTED */
    /* @Trace: CanIf_SUD_API_200 */
      #if (STD_ON == CANIF_TX_LPDU)
      prevTxStatus = CANIF_TX_STATUS(ptrController->PduMode);
      #endif

      /* Put the channel state of online state and clear all Tx flags */
      CANIF_SET_PDU_MODE(ptrController->PduMode, CANIF_ONLINE);

      #if (STD_ON == CANIF_TXCONFIRM_POLLING_SUPPORT)
      CANIF_CLEAR_TX_CONFIRMED(ptrController->PduMode);
      #endif

      #if (STD_ON == CANIF_TX_LPDU)
      #if (STD_ON == CANIF_CANCM_SUPPORT)
      if(ptrController->BatVolStatus != CANIF_TX_BAT_ERROR)
      #endif
      {
        if(prevTxStatus == CANIF_TX_DISABLED)
        {
          /* @Trace: CanIf_SUD_API_201 */
          /* Get the pointer to corresponding Can Controller structure */       
          /* polyspace +6 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
          ptrTxLpdu = ptrStaticController->TxLpdu;
          for(count = CANIF_ZERO; count < ptrStaticController->NoOfTxPdu; count++)
          {
            /* @Trace: CanIf_SUD_API_202 */
            /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
            CanIf_TxPduGwStatus[ptrTxLpdu->TxPduId] = CANIF_GW_NOREQUEST;
            ptrTxLpdu++;
          }
        }
        else
        {
          /*Do nothing*/
        }
      }
      #endif /* (STD_ON == CANIF_TX_LPDU) */
      break;
    case CANIF_SLEEP: /* CAN_CS_SLEEP */
      /* @Trace: CanIf_SUD_API_118 Set the PDU channel mode of the corresponding channel to CANIF_OFFLINE */
      CANIF_SET_PDU_MODE(ptrController->PduMode, CANIF_OFFLINE);
      /* polyspace +3 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
      #if (STD_ON == CANIF_PN_SUPPORT)
      /* @Trace: CanIf_SUD_API_119 the PnTxFilter of the corresponding CAN Controller shall be enabled */
      /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "It's depends on the configuration of CanIf. No impact" */
      if (ptrStaticController->PartialNWEnabled == CANIF_TRUE)
      {
        /* @Trace: CanIf_SUD_API_203 */
        CANIF_SET_TX_PNENABLED(ptrController->PduMode);
      }
      #endif

      /* @Trace: CanIf_SUD_API_120 the stored event from previous wake-up shall be cleared */
      CANIF_CLEAR_RX_VALIDATE_WAKEUP(ptrController->PduMode);

      break;
    /*Invoke the CanIf_SetControllerModeService with CAN_CS_STOPPED*/
    case CANIF_STOPPED: /* CAN_CS_STOPPED */
      /* @Trace: CanIf_SUD_API_121 Put the channel state of online state and clear all Tx flags */
      CANIF_SET_PDU_MODE(ptrController->PduMode, CANIF_TX_OFFLINE);
      break;
    /* polyspace +2 RTE:UNR [No action planned:Low] "List full type of mode to cover coverage"*/
    case CANIF_UNINIT: 
    default:
      /* Do nothing */
      break;
  }
  if (CANIF_STARTED != ControllerMode) /* CAN_CS_STARTED */
  {
    /* @Trace: CanIf_SUD_API_204 */
    #if (CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
    /* polyspace +2 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
    CanIf_TxMsgCnt[ControllerId] = CANIF_ZERO;
    CanIf_RxMsgCnt[ControllerId] = CANIF_ZERO;
    #endif

    #if ((STD_ON == CANIF_BASIC_CAN_TXPDU) && (STD_ON == CANIF_TX_QUEUE))	
    if((CANIF_STOPPED == ControllerMode)) /* CAN_CS_STOPPED */
    {
      /* @Trace: CanIf_SUD_API_205 */
      /* Get the pointer to corresponding Can Controller structure */
      #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
      ptrStaticController = &CanIfControllerConfig[ControllerId];
      #else
      ptrStaticController = &CanIf_ControllerConfig[ControllerId];
      #endif

      /* Disabling relevant interrupts*/
      /* @Trace: CanIf_SUD_API_122 */
      SchM_Enter_CanIf_TX_QUEUE_PROTECTION();

      /* Clear Tx queue */
      CanIf_ClearTxQueue(ptrStaticController);

      /* Enabling relevant interrupts*/
      SchM_Exit_CanIf_TX_QUEUE_PROTECTION();
    }
    #endif
  }
  /* Disable relevant interrupts */
  SchM_Exit_CanIf_MODE_STATUS_PROTECTION();
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_DETControllerModeIndication                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service indicates a controller state transition**
**                        referring to the corresponding CAN controller       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ControllerId, ControllerMode                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : CanIf_ControllerConfigType,    **
**                                             CanIf_CanIfStatus,             **
**                                             CanIf_Controller               **
**                        Function(s) invoked: SchM_Exit_CanIf_MODE_STATUS_   **
**                                             PROTECTION,                    **
**                                             CanSM_ControllerModeIndication **
**                                             CanIf_ClearTxQueue,            **
**                                             SchM_Enter_CanIf_MODE_STATUS_  **
**                                             PROTECTION,                    **
**                                             IdsM_ControllerModeIndication  **
*******************************************************************************/
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01114 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_DETControllerModeIndication (
                        VAR(uint8, CANIF_VAR) ControllerId,
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
                        VAR(Can_ControllerStateType, CANIF_VAR) ControllerMode)
#else
                        VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode)
#endif
{
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  /* Initialize the Standard Return Value with E_OK */
  retVal = (Std_ReturnType) E_OK;

  /* Report to DET, if module is not initialized */
  /* @Trace: CanIf_SUD_API_116 */
  /* @Trace: SWS_CANIF_00661 SWS_CANIF_00702 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CTRL_MODE_IND_SID, retVal);

  /* Report to DET, if requested channel is more than available controller */
  /* @Trace: CanIf_SUD_API_117 */
  /* @Trace: SWS_CANIF_00700 */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_CTRL_MODE_IND_SID, retVal);

  /* Report to DET, if requested controller mode is invalid */	
  /* @Trace: SWS_CANIF_00774 */
  CANIF_INVALID_CONTROLLER_MODE_ERROR(CANIF_CTRL_MODE_IND_SID, ControllerMode, retVal);

  return(retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (STD_ON == CANIF_DEV_ERROR_DETECT) */

/*******************************************************************************
** Function Name        : CanIf_PreSetControllerMode                          **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service calls corresponding CAN Driver service **
**                        for changing of the CAN controller mode. It         **
**                        initiates a transition to the requested CAN         **
**                        controller mode of one or multiple CAN controllers. **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : Controller, ControllerMode                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s):   CanIf_CanIfStatus             **
**                                              CanIf_Controller              **
**                                              CanIf_ControllerConfigType    **
**                                                                            **
**                        Function(s) invoked:  Det_ReportError               **
**                                              CanIf_SetControllerModeService**
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
FUNC(Std_ReturnType, CANIF_CODE)CanIf_PreSetControllerMode (
#else
FUNC(Can_ReturnType, CANIF_CODE)CanIf_PreSetControllerMode (
#endif
                        VAR(uint8, CANIF_VAR) ControllerId,
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
        P2VAR(Can_ControllerStateType, AUTOMATIC, CANIF_VAR) ControllerMode)
#else
        P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_VAR) ControllerMode)
#endif												
{
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
	  ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
	   (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  VAR(Std_ReturnType, CANIF_VAR) canReturn;
  #else
  VAR(Can_ReturnType, CANIF_VAR) canReturn;
  #endif

  /* Initialize the Can Return Value with E_OK */
  canReturn = CANIF_OK;

  /* Get the pointer of current controller structure */
  ptrController = &CanIf_Controller[ControllerId];
  /* polyspace +1 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
  if ((CANIF_SLEEP == ptrController->ControllerMode) && (*ControllerMode >= CANIF_STARTED)) 
  {
    #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
      ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
      (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
    /* From SLEEP to STOPPED */
    if (CANIF_SLEEP != *ControllerMode) 
    {
      /* @Trace: CanIf_SUD_API_163 */
      canReturn = CanIf_SetControllerModeService(ControllerId, CAN_CS_STOPPED);
    }
    #else
    /* Invoke the CanIf_SetControllerModeService with CAN_T_WAKEUP */
    canReturn = CanIf_SetControllerModeService(ControllerId, CAN_T_WAKEUP);
    #endif
    /* polyspace +3 MISRA2012:17.8 [No action planned:Low] "Not impact" */
    if (CANIF_STOPPED == *ControllerMode)
    {
      /* @Trace: CanIf_SUD_API_164 */
      *ControllerMode = CANIF_UNINIT;
      /* @Trace: SWS_CANIF_00866 */
      CANIF_SET_PDU_MODE(ptrController->PduMode, CANIF_TX_OFFLINE);
    }
  }
  else if ((CANIF_STARTED == ptrController->ControllerMode) &&
                              (CANIF_SLEEP == *ControllerMode))
  {
    /* @Trace: CanIf_SUD_API_165 */
    #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
        ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
        (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
    canReturn = CanIf_SetControllerModeService(ControllerId, CAN_CS_STOPPED);
    #else
    canReturn = CanIf_SetControllerModeService(ControllerId, CAN_T_STOP);
    #endif
  } else {
    /* Do nothing */
  }
  return(canReturn);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_SetControllerModeProcessing                   **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service calls corresponding CAN Driver service **
**                        for changing of the CAN controller mode. It         **
**                        initiates a transition to the requested CAN         **
**                        controller mode of one or multiple CAN controllers. **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : Controller, ControllerMode                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s):   CanIf_CanIfStatus             **
**                                              CanIf_Controller              **
**                                              CanIf_ControllerConfigType    **
**                                                                            **
**                        Function(s) invoked:  Det_ReportError               **
**                                              CanIf_SetControllerModeService**
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
FUNC(Std_ReturnType, CANIF_CODE)CanIf_SetControllerModeProcessing (
#else
FUNC(Can_ReturnType, CANIF_CODE)CanIf_SetControllerModeProcessing (
#endif
                        VAR(uint8, CANIF_VAR) ControllerId,
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
        VAR(Can_ControllerStateType, CANIF_VAR) ControllerMode)
#else
        VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode)
#endif												
{
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
	  ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
	   (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
  VAR(Std_ReturnType, CANIF_VAR) canReturn;
  #else
  VAR(Can_ReturnType, CANIF_VAR) canReturn;
  #endif
  P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu;
  VAR(uint16, CANIF_VAR) count;
  /* Initialize the Can Return Value with E_OK */
  canReturn = CANIF_OK;

  /* Get the pointer to current controller structure*/
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
  ptrStaticController = &CanIfControllerConfig[ControllerId];
  #else
  ptrStaticController = &CanIf_ControllerConfig[ControllerId];
  #endif
  /* Get the pointer of current controller structure*/
  ptrController = &CanIf_Controller[ControllerId];

  switch (ControllerMode)
  {
    /* Invoke the CanIf_SetControllerModeService with CAN_CS_STARTED */
    /* @Trace: SWS_CANIF_00308 */
    case CANIF_STARTED: /* CAN_CS_STARTED */
    /* @Trace: CanIf_SUD_API_166 */
    /* polyspace +6 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
      #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
          ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
          (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
      canReturn = CanIf_SetControllerModeService(ControllerId, CAN_CS_STARTED);
      #else
      canReturn = CanIf_SetControllerModeService(ControllerId, CAN_T_START);
      #endif
      break;

    /*Invoke the CanIf_SetControllerModeService with CAN_CS_SLEEP*/
    case CANIF_SLEEP: /* CAN_CS_SLEEP */
      /* @Trace: CanIf_SUD_API_167 */
      /* polyspace +9 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
      #if (STD_ON == CANIF_TX_LPDU)
      SchM_Enter_CanIf_TX_NOTIFSTATUS_PROTECTION();
      /* Update Tx Gateway Buffer Status */
      ptrTxLpdu = ptrStaticController->TxLpdu;

      for(count = CANIF_ZERO; count < ptrStaticController->NoOfTxPdu; count++)
      {
        /* @Trace: CanIf_SUD_API_168 */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "Its boundary is pre-defined"*/
        CanIf_TxPduGwStatus[ptrTxLpdu->TxPduId] = CANIF_GW_NOCOMM;
        ptrTxLpdu++;
      }
      SchM_Exit_CanIf_TX_NOTIFSTATUS_PROTECTION();
      #endif
      /* @Trace: SWS_CANIF_00308 */
      #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
          ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
          (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
      canReturn = CanIf_SetControllerModeService(ControllerId, CAN_CS_SLEEP);
      #else
      canReturn = CanIf_SetControllerModeService(ControllerId, CAN_T_SLEEP);
      #endif
      /* @Trace: CanIf_SUD_API_053 Set the PDU channel mode of the corresponding channel to CANIF_OFFLINE */
      /* @Trace: SWS_CANIF_00865 */
      CANIF_SET_PDU_MODE(ptrController->PduMode, CANIF_OFFLINE);

      /* @Trace: CanIf_SUD_API_054 the PnTxFilter of the corresponding CAN Controller shall be enabled */
      /* @Trace: SWS_CANIF_00749 */
      #if (STD_ON == CANIF_PN_SUPPORT)
      if (ptrStaticController->PartialNWEnabled == CANIF_TRUE)
      {
        /* @Trace: CanIf_SUD_API_169 */
        CANIF_SET_TX_PNENABLED(ptrController->PduMode);
      }
      #endif
      /* @Trace: CanIf_SUD_API_055 the stored event from previous wake-up shall be cleared */
      /* @Trace: SWS_CANIF_00756 */
      CANIF_CLEAR_RX_VALIDATE_WAKEUP(ptrController->PduMode);

      break;

    /* Invoke the CanIf_SetControllerModeService with CAN_CS_STOPPED */
    /* @Trace: SWS_CANIF_00308 */
    case CANIF_STOPPED: /* CAN_CS_STOPPED */
      /* @Trace: CanIf_SUD_API_056 */
      /* polyspace +6 RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
      #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
          ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
          (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
      canReturn = CanIf_SetControllerModeService(ControllerId, CAN_CS_STOPPED);
      #else
      canReturn = CanIf_SetControllerModeService(ControllerId, CAN_T_STOP);
      #endif
      /* @Trace: SWS_CANIF_00866 */
      CANIF_SET_PDU_MODE(ptrController->PduMode, CANIF_TX_OFFLINE);

      break;

    default:
    /* @Trace: CanIf_SUD_API_170 */
    /* Do nothing */ 
      CANIF_UNUSED(ptrStaticController);
      break;
  }

  return(canReturn);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_DETSetPduMode                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service sets the requested mode at all L-PDUs  **
**                        of the predefined logical PDU channel. The channel  **
**                        parameter can be derived from Controller.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : ControllerId, PduModeRequest                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_CanIfStatus               **
**                                            CanIf_Controller                **
**                                            CanIf_ControllerConfigType      **
**                        Function(s)invoked: CanIf_ClearTxQueue              **
**                                            CanIf_SetTxOrRxSts,             **
**                                            SchM_Enter_CanIf_MODE_STATUS_   **
**                                            PROTECTION,                     **
**                                            SchM_Exit_CanIf_MODE_STATUS_    **
**                                            PROTECTION                      **
*******************************************************************************/
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 SRS_Can_01013 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_DETSetPduMode (
                            VAR(uint8, CANIF_VAR) ControllerId,
                            VAR(CanIf_PduModeType, CANIF_VAR) PduModeRequest)
{
  P2VAR(CanIf_ControllerType, AUTOMATIC, CANIF_VAR) ptrController;
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  /* Initialize the Standard Return Value with E_OK */
  retVal = (Std_ReturnType) E_OK;
  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_SET_PDU_MODE_SID, retVal);

  /* Report to DET, if requested channel is more than available controller */
  /* @Trace: CanIf_SUD_API_062 */
  /* @Trace: SWS_CANIF_00341 */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_SET_PDU_MODE_SID, retVal);

  if ((Std_ReturnType) E_OK == retVal)
  {
    /* @Trace: CanIf_SUD_API_183 */
    /* Get the pointer to corresponding Can Controller Config ControllerId*/
    ptrController = &CanIf_Controller[ControllerId];

    /* Report to DET, if requested controller mode is uninitialized*/
    /* polyspace<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
    if (CANIF_UNINIT == ptrController->ControllerMode)
    {
      /* @Trace: CanIf_SUD_API_184 */
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                                        CANIF_SET_PDU_MODE_SID, CANIF_E_UNINIT);
      retVal = (Std_ReturnType)E_NOT_OK;
    }
  }

  /* @Trace: CanIf_SUD_API_063 */
  /* Report to DET, If requested channel mode state is invalid */ 
  /* polyspace +2 RTE:UNR [Not a defect:Low] "it's to cover autosar requirement when error occurs" */
  /* @Trace: SWS_CANIF_00860 */
  CANIF_INVALID_PDU_MODE_REQ_ERROR(CANIF_SET_PDU_MODE_SID, retVal); 
  return (retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (STD_ON == CANIF_DEV_ERROR_DETECT) */

/*******************************************************************************
** Function Name        : CanIf_DETSetControllerMode                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service calls corresponding CAN Driver service **
**                        for changing of the CAN controller mode. It         **
**                        initiates a transition to the requested CAN         **
**                        controller mode of one or multiple CAN controllers. **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : Controller, ControllerMode                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s):   CanIf_CanIfStatus             **
**                                              CanIf_Controller              **
**                                              CanIf_ControllerConfigType    **
**                                                                            **
**                        Function(s) invoked:  Det_ReportError               **
**                                              CanIf_SetControllerModeService**
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */  
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Can_01027 SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE)CanIf_DETSetControllerMode (
                        VAR(uint8, CANIF_VAR) ControllerId,
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
                        VAR(Can_ControllerStateType, CANIF_VAR) ControllerMode)
#else
                        VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode)
#endif												
{
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  retVal = (Std_ReturnType) E_OK;

  /* Report to DET, if module is not initialized */  
  /* @Trace: CanIf_SUD_API_052 */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_SET_CNTRL_MODE_SID, retVal);

  /* Report to DET, if requested controller Id is more than available
  controller */
  /* @Trace: SWS_CANIF_00311 */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_SET_CNTRL_MODE_SID, retVal);

  /* Report to DET, if requested controller mode is invalid */
  /* @Trace: SWS_CANIF_00774 */
  /* polyspace +1 MISRA2012:10.5 [No action planned:Low] "Not impact, bacause the mismatch version between CanIf & CanDrv"*/
  CANIF_INVALID_CONTROLLER_MODE_ERROR(CANIF_SET_CNTRL_MODE_SID, ControllerMode, retVal);

  return (retVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* polyspace-end RTE:IDP [Not a defect:Low] "Its boundary is pre-defined" */
/* polyspace-end RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
