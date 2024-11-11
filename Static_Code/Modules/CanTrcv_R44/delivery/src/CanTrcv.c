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
**  SRC-MODULE: CanTrcv.c                                                     **
**                                                                            **
**  TARGET    : General CAN Transceiver                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transceiver Driver Module                         **
**                                                                            **
**  PURPOSE   : Provision APIs of CAN Transceiver Module                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.0.11         08-Feb-2024         Yubin Song       #CP44-3726             **
** 1.0.10         02-Jun-2023         HieuTM8          #CP44-2271             **
** 1.0.9          03-Mar-2023         HieuTM8          #CP44-1782             **
** 1.0.8          09-Dec-2022         HieuTM8          #CP44-1194             **
** 1.0.6          17-Oct-2022         HieuTM8          #CP44-877              **
** 1.0.5          30-Jul-2022         HieuTM8          #CP44-512              **
** 1.0.3          29-Apr-2022         HieuTM8          Redmine #26478         **
** 1.0.1          14-Sep-2021         DuyNHP2          Redmine #20148         **
** 1.0.0          15-Dec-2020         JsLim            Initial version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CanTrcv_SUD_FILE_001 */
/* Can Transceiver header file */
#include "CanTrcv.h"
/* Can Transceiver schedule header file */
#include "SchM_CanTrcv.h"
/* Can Transceiver internal functions header file */
#include "CanTrcv_IntFunc.h"
/* Can Transceiver global variables header file */
#include "CanTrcv_Globals.h"


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#define CANTRCV_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : CANTRCV_INIT_MACRO                                  **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This service sets the CAN Transceiver Driver mode   **
**                        to either Normal or StandBy or Sleep Mode based on  **
**                        the configured initialization state.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr - Pointer to driver configuration.        **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanTrcv_CanTrcvNetwork,       **
**                        CanTrcv_ArisuCan, CanTrcv_ArisuCanSts,              **
**                        CanTrcv_ArisuChannelUsed, CanTrcv_InitStatus        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_IntInitialize, CanTrcv_IntGetPorFlag,       **
**                        CanTrcv_IntClearPorFlag, CanTrcv_SetNormalMode,     **
**                        CanTrcv_SetStandbyMode, CanTrcv_SetSleepMode,       **
**                        CanTrcv_ArisuCan_Init, EcuM_SetWakeupEvent,         **
**                        Det_ReportRuntimeError                              **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00099 SWS_CanTrcv_00100 SWS_CanTrcv_00167 SWS_CanTrcv_00177
  SWS_CanTrcv_00181 SWS_CanTrcv_00182 SWS_CanTrcv_00183 SWS_CanTrcv_00184
  SWS_CanTrcv_00113 SWS_CanTrcv_00148 SWS_CanTrcv_00226 SWS_CanTrcv_00085
  SWS_CanTrcv_00086 SWS_CanTrcv_00163 SWS_CanTrcv_00209 SRS_BSW_00172
  SRS_BSW_00101 SRS_BSW_00160 SRS_BSW_00310 SRS_BSW_00358 SRS_BSW_00371
  SRS_BSW_00386 SRS_BSW_00388 SRS_BSW_00389 SRS_BSW_00390 SRS_BSW_00392
  SRS_BSW_00393 SRS_BSW_00394 SRS_BSW_00408 SRS_BSW_00414 SRS_BSW_00425
  SRS_Can_01090 SRS_Can_01091 SRS_Can_01097 SRS_Can_01108 SRS_Can_01109
  SRS_Can_01110 SRS_BSW_00400 SRS_BSW_00404 SRS_BSW_00405 SRS_Can_01096 */
FUNC(void, CANTRCV_CODE) CANTRCV_INIT_MACRO(
  P2CONST(CanTrcv_ConfigType, AUTOMATIC, CANTRCV_CONST) ConfigPtr)
{
  #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL) || \
      ((STD_ON == CANTRCV_CHANNEL_USED_ALL) && \
      (STD_ON == CANTRCV_ARISUCAN_SUPPORTED))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif
  #if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)
  P2CONST(ArisuCan_CanConfigType, AUTOMATIC, CANTRCV_CONST) ptrArisuCanCfg;
  #endif
  VAR(uint8, AUTOMATIC) CanTrcvChannel;

  #if(STD_ON == CANTRCV_POSTBUILD_SUPPORTED)
  VAR(Std_ReturnType, AUTOMATIC) returnVal;
  #endif

  #if (STD_ON == CANTRCV_POSTBUILD_SUPPORTED)
  /* Check whether the configset is null */
  if (NULL_PTR == ConfigPtr)
  /* polyspace +5 RTE:UNR [Justified:Low] "This DET error is reported when ConfigPtr is set to NULL pointer." */
  {
    #if(STD_ON == CANTRCV_DEV_ERROR_DETECT)
    /* Report to DET */
	/* @Trace: CanTrcv_SUD_API_308 */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_INIT_SID, CANTRCV_E_PARAM_POINTER);
    #endif
    /* set result to E_NOT_OK*/
    returnVal= (Std_ReturnType)E_NOT_OK;
  }
  else
  {
	/* set result to E_OK*/
	returnVal= (Std_ReturnType)E_OK;
  }
  if((Std_ReturnType)E_OK == returnVal)
  #endif /* (STD_ON == CANTRCV_POSTBUILD_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_POSTBUILD_SUPPORTED)
    #if (STD_ON == CANTRCV_SPI_SUPPORTED)
    /* Get the pointer to the structure of ArisuCan */
    /* polyspace +3 MISRA2012:D4.14 [Justified:Low] "Pointer ConfigPtr is checked NULL by DET." */
    CanTrcv_SPICommRetries = ConfigPtr->SPICommRetries;
    #endif /* (STD_ON == CANTRCV_SPI_SUPPORTED) */
    #if (STD_OFF == CANTRCV_SUPPORT_AR403)
    #if (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED)
    /* Get the pointer to the structure of ArisuCan */
    CanTrcv_SPICommTimeout = ConfigPtr->SPICommTimeout;
    #endif /* (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED) */
    #endif /*(STD_OFF == CANTRCV_SUPPORT_AR403)*/
    #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
    /* Get the pointer to the structure of ArisuCan */
    CanTrcv_PartialNetwork = ConfigPtr->PnNetwork;
    #endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */
    #else
    /* polyspace +1 RTE:UNR [Justified:Low] "This macro function is to avoid compiler error when input arg ConfigPtr is not used." */
    CANTRCV_UNUSED_VAL(ConfigPtr);
    #endif /* (STD_ON == CANTRCV_POSTBUILD_SUPPORTED) */

    #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL) || \
        ((STD_ON == CANTRCV_CHANNEL_USED_ALL) && \
        (STD_ON == CANTRCV_ARISUCAN_SUPPORTED))
    /* Get the pointer to the structure of first network */
    ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[CANTRCV_ZERO];
    #endif
    #if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)
    /* Get the pointer to the structure of ArisuCan */
    ptrArisuCanCfg = &CanTrcv_ArisuCan[ARISUCAN_SBCMODE_INIT];
    #endif /* (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) */

    /* Set the network value to zero */
    CanTrcvChannel = (uint8)CANTRCV_ZERO;

    /* Loop for initializing all the configured CAN Transceiver Driver networks */
    while(CANTRCV_NUM_OF_NETWORKS > CanTrcvChannel)
    {
      /* Check if channel is used or not*/
      #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL)
      if (CANTRCV_TRUE == ptrCanTrcvNetwork->ChannelUsed)
      #endif /* (STD_OFF == CANTRCV_CHANNEL_USED_ALL) */
      {
        #if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)
        if ((ptrCanTrcvNetwork->CanTrcvHwDev == CANTRCV_ARISU_CAN0) ||
          (ptrCanTrcvNetwork->CanTrcvHwDev == CANTRCV_ARISU_CAN1) ||
          (ptrCanTrcvNetwork->CanTrcvHwDev == CANTRCV_ARISU_CAN2) ||
          (ptrCanTrcvNetwork->CanTrcvHwDev == CANTRCV_ARISU_CAN3))
        {
          /* ARISU-CAN Device is not need to set init mode */
          /* WDG Driver do that by calling SPI API */
        }
        else
        #endif /* (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) */
        {
          CanTrcv_Init_Channel(CanTrcvChannel);
        }
      }
      #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL)
      else
      {
        /* @Trace: CanTrcv_SUD_API_002 */
        /* Report a Development error If there is no/incorrect communication to
          the transceiver */
        (void)Det_ReportRuntimeError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
          CANTRCV_INIT_SID, CANTRCV_E_NO_TRCV_CONTROL);
      }
      #endif /* (STD_OFF == CANTRCV_CHANNEL_USED_ALL) */
      #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL) || \
        ((STD_ON == CANTRCV_CHANNEL_USED_ALL) && \
        (STD_ON == CANTRCV_ARISUCAN_SUPPORTED))
      /* Increment the pointer for the network structure */
      ptrCanTrcvNetwork++;
      #endif
      /* Increment the network number */
      CanTrcvChannel++;
    }
    /* Check whether the network number is less than CANTRCV_NUM_OF_NETWORKS */

    /* ARISU-CAN Device's initial mode */
    #if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)
    /* @Trace: CanTrcv_SUD_API_007 */
    CanTrcv_ArisuCanSts.ArisuCan0Mode = ptrArisuCanCfg->ArisuCan0Mode;
    CanTrcv_ArisuCanSts.ArisuCan1Mode = ptrArisuCanCfg->ArisuCan1Mode;
    CanTrcv_ArisuCanSts.ArisuCan2Mode = ptrArisuCanCfg->ArisuCan2Mode;
    CanTrcv_ArisuCanSts.ArisuCan3Mode = ptrArisuCanCfg->ArisuCan3Mode;
    CanTrcv_ArisuChannelUsed.ArisuCan0Used = ARISUCAN_UNCONFIGURE;
    CanTrcv_ArisuChannelUsed.ArisuCan1Used = ARISUCAN_UNCONFIGURE;
    CanTrcv_ArisuChannelUsed.ArisuCan2Used = ARISUCAN_UNCONFIGURE;
    CanTrcv_ArisuChannelUsed.ArisuCan3Used = ARISUCAN_UNCONFIGURE;

    /* Initialize HW ArisuCan */
    CanTrcv_ArisuCan_Init(ptrArisuCanCfg);
    #endif /* (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) */

    /* Set the global variable status to initialized */
    CanTrcv_InitStatus = CANTRCV_INITIALIZED;
  }
}

/*******************************************************************************
** Function Name        : CANTRCV_SETOPMODE_MACRO                             **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : Sets the mode of the Transceiver to the value       **
**                        OpMode.                                             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant for different transceivers                **
**                                                                            **
** Input Parameters     : Transceiver - CAN transceiver to which API call has **
**                                      to be applied.                        **
**                        OpMode      - This parameter contains the desired   **
**                                      operating mode.                       **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK:     Will be returned if the request for       **
**                                  transceiver mode change has been accepted.**
**                        E_NOT_OK: will be returned if the request for       **
**                                  transceiver mode change has not been      **
**                                  accepted or any parameter is out of the   **
**                                  allowed range.                            **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  : CanTrcv_InitStatus,           **
**                        CanTrcv_CanTrcvNetwork, CanTrcv_ByteArray           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, Det_ReportRuntimeError,            **
**                        CanTrcv_SetNormalMode, CanTrcv_IntGetPorFlag,       **
**                        CanTrcv_SetStandbyMode, CanTrcv_SetSleepMode,       **
**                        CanIf_TrcvModeIndication,                           **
**                        CanIf_ConfirmPnAvailability                         **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00002 SWS_CanTrcv_00050 SWS_CanTrcv_00163
  SWS_CanTrcv_00102 SWS_CanTrcv_00103 SWS_CanTrcv_00104 SWS_CanTrcv_00105
  SWS_CanTrcv_00186 SWS_CanTrcv_00187 SWS_CanTrcv_00188 SWS_CanTrcv_00114
  SWS_CanTrcv_00120 SWS_CanTrcv_00121 SWS_CanTrcv_00122 SWS_CanTrcv_00123
  SWS_CanTrcv_00087 SWS_CanTrcv_00161 SWS_CanTrcv_00158 SWS_CanTrcv_00085
  SWS_CanTrcv_00086 SRS_BSW_00310 SRS_BSW_00327 SRS_BSW_00350 SRS_BSW_00357
  SRS_BSW_00369 SRS_BSW_00371 SRS_BSW_00386 SRS_Can_01091 SRS_Can_01097
  SRS_Can_01098 SRS_Can_01099 SRS_Can_01100 SRS_Can_01108 SRS_Can_01109
  SRS_Can_01110 SRS_BSW_00406
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_SETOPMODE_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) OpMode)
{
  #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL)
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif
  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  VAR(uint8, AUTOMATIC) currentOpMode;
  #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize return value to E_NOT_OK */
  returnValue = (Std_ReturnType)E_NOT_OK;

  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  /* Check whether the module is initialized */
  if (CANTRCV_UNINITIALIZED == CanTrcv_InitStatus)
  {
    /* @Trace: CanTrcv_SUD_API_030 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_SETOPMODE_SID, CANTRCV_E_UNINIT);
  }
  /* Check whether network is out of range */
  else if (CANTRCV_NUM_OF_NETWORKS <= Transceiver)
  {
    /* @Trace: CanTrcv_SUD_API_029 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_SETOPMODE_SID, CANTRCV_E_INVALID_TRANSCEIVER);
  }
  /* Check whether OpMode is out of range */
  else if ((CANTRCV_TRCVMODE_NORMAL != OpMode) &&
    (CANTRCV_TRCVMODE_STANDBY != OpMode) &&
    (CANTRCV_TRCVMODE_SLEEP != OpMode))
  /* polyspace +5 RTE:UNR [Justified:Low] "This DET error is reported when OpMode is set out of its enum range." */
  {
    /* @Trace: CanTrcv_SUD_API_028 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_SETOPMODE_SID, CANTRCV_E_PARAM_TRCV_OPMODE);
  }
  else
  #endif/* #if (CAN_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL)
    /* Get the pointer to the structure of the requested network */
    ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[Transceiver];
    /* Check if channel is used or not*/
    if (CANTRCV_TRUE == ptrCanTrcvNetwork->ChannelUsed)
    #endif /* (STD_OFF == CANTRCV_CHANNEL_USED_ALL) */
    {
      #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
      /* Get the current operation mode of CanTrcv network */
      currentOpMode = (uint8)CanTrcv_ByteArray[Transceiver];
      /* Report to DET if invalid mode is requested */
      if (((uint8) CANTRCV_TRCVMODE_SLEEP == currentOpMode) &&
        ((CanTrcv_TrcvModeType)CANTRCV_TRCVMODE_STANDBY == OpMode))
      {
        /* @Trace: CanTrcv_SUD_API_031 */
        /* Report to DET */
        (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
          CANTRCV_SETOPMODE_SID, CANTRCV_E_TRCV_NOT_NORMAL);
      }
      /* Report to DET if current mode is not equal to standby and requested
         mode is in sleep */
      else if (((uint8)CANTRCV_TRCVMODE_NORMAL == currentOpMode) &&
        ((CanTrcv_TrcvModeType)CANTRCV_TRCVMODE_SLEEP == OpMode))
      {
        /* @Trace: CanTrcv_SUD_API_032 */
        /* Report to DET */
        (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
          CANTRCV_SETOPMODE_SID, CANTRCV_E_TRCV_NOT_STANDBY);
      }
      else
      #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
      {
        returnValue = CanTrcv_SetOpMode_Processing(Transceiver, OpMode);
      }
    }
    #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL)
    else
    {
      /* @Trace: CanTrcv_SUD_API_040 */
      /* Report a Development error If there is no/incorrect communication to
        the transceiver */
      (void)Det_ReportRuntimeError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
        CANTRCV_SETOPMODE_SID, CANTRCV_E_NO_TRCV_CONTROL);
    }
    #endif /* (STD_OFF == CANTRCV_CHANNEL_USED_ALL) */
  }

  return (returnValue);
}

/*******************************************************************************
** Function Name        : CANTRCV_GETOPMODE_MACRO                             **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : Gets the mode of the Transceiver and returns it in  **
**                        OpMode.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Transceiver - CAN transceiver to which API call has **
**                                      to be applied.                        **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : OpMode - Pointer to operation mode of the bus the   **
**                                 API is applied to.                         **
**                                                                            **
** Return parameter     : E_OK:     Will be returned if the operation mode    **
**                                  was detected.                             **
**                        E_NOT_OK: Will be returned if the operation mode    **
**                                  was not detected.                         **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        CanTrcv_InitStatus,                                 **
**                        CanTrcv_CanTrcvNetwork,                             **
**                        CanTrcv_ByteArray                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        Det_ReportRuntimeError                              **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00005 SWS_CanTrcv_00050 SWS_CanTrcv_00163
  SWS_CanTrcv_00106 SWS_CanTrcv_00115 SWS_CanTrcv_00124 SWS_CanTrcv_00129
  SWS_CanTrcv_00132 SWS_CanTrcv_00085 SWS_CanTrcv_00086 SRS_BSW_00310
  SRS_BSW_00327 SRS_BSW_00350 SRS_BSW_00357 SRS_BSW_00369 SRS_BSW_00371
  SRS_BSW_00377 SRS_BSW_00386 SRS_Can_01091 SRS_Can_01097 SRS_Can_01101
  SRS_Can_01109 SRS_Can_01110
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_GETOPMODE_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) OpMode)
{
  #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL)
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif /* (STD_OFF == CANTRCV_CHANNEL_USED_ALL) */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* Initialize return value to E_NOT_OK */
  returnValue = (Std_ReturnType)E_NOT_OK;

  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  /* Check whether the module is Initialized */
  if (CANTRCV_UNINITIALIZED == CanTrcv_InitStatus)
  {
    /* @Trace: CanTrcv_SUD_API_041 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_GETOPMODE_SID, CANTRCV_E_UNINIT);
  }
  /* Check whether the Transceiver id is out of range */
  else if (CANTRCV_NUM_OF_NETWORKS <= Transceiver)
  {
    /* @Trace: CanTrcv_SUD_API_042 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_GETOPMODE_SID, CANTRCV_E_INVALID_TRANSCEIVER);
  }
  /* Check for NULL POINTER */
  else if (NULL_PTR == OpMode)
  /* polyspace +5 RTE:UNR [Justified:Low] "This DET error is reported when OpMode is set to NULL pointer." */
  {
    /* @Trace: CanTrcv_SUD_API_043 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_GETOPMODE_SID, CANTRCV_E_PARAM_POINTER);
  }
  else
  #endif /* #if (CANTRCV_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL)
    /* Get the pointer to the structure of the requested network */
    ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[Transceiver];
    /* polyspace +2 DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanTrcv. No impact" */
    /* Check if channel is used or not */
    if (CANTRCV_TRUE == ptrCanTrcvNetwork->ChannelUsed)
    #endif /* (STD_OFF == CANTRCV_CHANNEL_USED_ALL) */
    {
      /* @Trace: CanTrcv_SUD_API_044 */
      /* Get the operational mode of CAN Transceiver */
      /* polyspace +1 MISRA2012:D4.14 [Justified:Low] "Pointer OpMode is checked NULL by DET." */
      *OpMode = (CanTrcv_TrcvModeType)CanTrcv_ByteArray[Transceiver];
      /* Set return value as E_OK */
      returnValue = (Std_ReturnType)E_OK;
    }
    #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL)
    else
    {
      /* @Trace: CanTrcv_SUD_API_045 */
      /* Report a Development error If there is no/incorrect communication to
        the transceiver */
      (void)Det_ReportRuntimeError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
        CANTRCV_GETOPMODE_SID, CANTRCV_E_NO_TRCV_CONTROL);
    }
    #endif /* (STD_OFF == CANTRCV_CHANNEL_USED_ALL) */
  }

  return returnValue;
}

#if (STD_ON == CANTRCV_GET_VERSION_INFO)
/*******************************************************************************
** Function Name        : CANTRCV_GETVERSIONINFO_MACRO                        **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : Gets the version of the module and returns it in    **
**                        VersionInfo.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : versioninfo - Pointer to version information of     **
**                                      this module.                          **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00008 SWS_CanTrcv_00050 SWS_CanTrcv_00086
  SRS_BSW_00310 SRS_BSW_00327 SRS_BSW_00350 SRS_BSW_00369 SRS_BSW_00371
  SRS_BSW_00386 SRS_BSW_00411 SRS_BSW_00407
*/
FUNC(void, CANTRCV_CODE)CANTRCV_GETVERSIONINFO_MACRO(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CANTRCV_APPL_DATA) versioninfo)
{
  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  /* Check whether the versioninfo is equal to null pointer */
  if (NULL_PTR == versioninfo)
  /* polyspace +5 RTE:UNR [Justified:Low] "This DET error is reported when versioninfo is set to NULL pointer." */
  {
    /* Report to DET */
    /* @Trace: CanTrcv_SUD_API_011 */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_GETVERSIONINFO_SID, CANTRCV_E_PARAM_POINTER);
  }
  else
  #endif /* #if (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanTrcv_SUD_API_012 */
    /* polyspace +10 MISRA2012:D4.14 [Justified:Low] "Pointer versioninfo is checked NULL by DET." */
    /* Copy the vendor Id */
    versioninfo->vendorID = CANTRCV_VENDOR_ID;
    /* Copy the module Id */
    versioninfo->moduleID = CANTRCV_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = (uint8)CANTRCV_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = (uint8)CANTRCV_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = (uint8)CANTRCV_SW_PATCH_VERSION;
  }
}
#endif /* (STD_ON == CANTRCV_GET_VERSION_INFO) */

/*******************************************************************************
** Function Name        : CANTRCV_CHECKWAKEUP_MACRO                           **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : Service is called by underlying CANIF in case a     **
**                        wake up interrupt is detected.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Transceiver - CAN transceiver to which API call has **
**                                      to be applied.                        **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: API call has been accepted.                   **
**                        E_NOT_OK: API call has not been accepted.           **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        CanTrcv_InitStatus,                                 **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        CanTrcv_IntCheckWakeup                              **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00050 SWS_CanTrcv_00143 SWS_CanTrcv_00086
  SWS_CanTrcv_00144 SWS_CanTrcv_00145 SWS_CanTrcv_00146 SWS_CanTrcv_00091
  SRS_BSW_00160 SRS_BSW_00327 SRS_BSW_00350 SRS_BSW_00357 SRS_BSW_00369
  SRS_BSW_00386 SRS_BSW_00388 SRS_BSW_00389 SRS_BSW_00390 SRS_BSW_00392
  SRS_BSW_00393 SRS_BSW_00394 SRS_BSW_00395 SRS_BSW_00408 SRS_Can_01090
  SRS_Can_01091 SRS_Can_01092 */
FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_CHECKWAKEUP_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver)
{
  #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize return value to E_NOT_OK */
  returnValue = (Std_ReturnType)E_NOT_OK;

  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  /* Check whether the module is Initialized */
  if (CANTRCV_UNINITIALIZED == CanTrcv_InitStatus)
  {
    /* @Trace: CanTrcv_SUD_API_156 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_CHECKWAKEUP_SID, CANTRCV_E_UNINIT);
  }
  /* Check whether the Transceiver id is out of range */
  else if (CANTRCV_NUM_OF_NETWORKS <= Transceiver)
  {
    /* @Trace: CanTrcv_SUD_API_157 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_CHECKWAKEUP_SID, CANTRCV_E_INVALID_TRANSCEIVER);
  }
  else
  #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
  {
    #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
    /* Get the pointer to the structure of the requested network */
    ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[Transceiver];
    /* Check channel is used and supported wake up */
    if ((CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed) &&
      (CANTRCV_FALSE != ptrCanTrcvNetwork->WakeupByBusUsed))
    {
      /* @Trace: CanTrcv_SUD_API_158 */
      /* Invoke internal function to check wake up */
      returnValue = CanTrcv_IntCheckWakeup(Transceiver);
    }
    else
    {
      /* Nothing to do */
    }
    #else
    /* A void compiler warning */
    CANTRCV_UNUSED_VAL(Transceiver);
    /* Wake up function is not support, so set return value as E_OK */
    returnValue = (Std_ReturnType)E_OK;
    #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
  }

  return returnValue;
}

#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)

/*******************************************************************************
** Function Name        : CANTRCV_SETWAKEUPMODE_MACRO                         **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : Enables, disables or clears wake-up events of the   **
**                        Transceiver according to TrcvWakeupMode.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different transceivers.               **
**                                                                            **
** Input Parameters     : Transceiver    - CAN transceiver to which API call  **
**                                         has to be applied.                 **
**                        TrcvWakeupMode - Requested transceiver wakeup       **
**                                         reason.                            **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK:     The wakeup state has been changed to the  **
**                                  requested mode.                           **
**                        E_NOT_OK: The wakeup state change has failed or the **
**                                  parameter is out of the allowed range.    **
**                                  The previous state has not been changed.  **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  : CanTrcv_InitStatus,           **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        CanTrcv_IntSetWakeupMode,                           **
**                        Det_ReportRuntimeError                              **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00009 SWS_CanTrcv_00050 SWS_CanTrcv_00111
  SWS_CanTrcv_00093 SWS_CanTrcv_00094 SWS_CanTrcv_00150 SWS_CanTrcv_00095
  SWS_CanTrcv_00117 SWS_CanTrcv_00127 SWS_CanTrcv_00131 SWS_CanTrcv_00089
  SWS_CanTrcv_00085 SWS_CanTrcv_00086 SWS_CanTrcv_00164 SWS_CanTrcv_00090
  SWS_CanTrcv_00091 SRS_BSW_00172 SRS_BSW_00160 SRS_BSW_00310 SRS_BSW_00327
  SRS_BSW_00350 SRS_BSW_00357 SRS_BSW_00369 SRS_BSW_00371 SRS_BSW_00386
  SRS_BSW_00388 SRS_BSW_00389 SRS_BSW_00390 SRS_BSW_00392 SRS_BSW_00393
  SRS_BSW_00394 SRS_BSW_00395 SRS_BSW_00395 SRS_BSW_00408 SRS_BSW_00408
  SRS_BSW_00408 SRS_BSW_00408 SRS_BSW_00425 SRS_Can_01090 SRS_Can_01090
  SRS_Can_01091 SRS_Can_01097 SRS_Can_01109 SRS_Can_01110 SRS_Can_01115
  SRS_Can_01092 */
FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_SETWAKEUPMODE_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  VAR(CanTrcv_TrcvWakeupModeType, AUTOMATIC) TrcvWakeupMode)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize return value to E_NOT_OK */
  returnValue = (Std_ReturnType)E_NOT_OK;

  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  /* Check whether the module is Initialized */
  if (CANTRCV_UNINITIALIZED == CanTrcv_InitStatus)
  {
    /* @Trace: CanTrcv_SUD_API_164 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_SETWAKEUPMODE_SID, CANTRCV_E_UNINIT);
  }
  /* Check whether the Transceiver id is out of range */
  else if (CANTRCV_NUM_OF_NETWORKS <= Transceiver)
  {
    /* @Trace: CanTrcv_SUD_API_165 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_SETWAKEUPMODE_SID, CANTRCV_E_INVALID_TRANSCEIVER);
  }
  /* Check whether the wake up mode is out of range */
  else if ((CANTRCV_WUMODE_ENABLE != TrcvWakeupMode) &&
    (CANTRCV_WUMODE_DISABLE != TrcvWakeupMode) &&
    (CANTRCV_WUMODE_CLEAR != TrcvWakeupMode))
  /* polyspace +5 RTE:UNR [Justified:Low] "This DET error is reported when TrcvWakeupMode is set out of its enum range." */
  {
    /* @Trace: CanTrcv_SUD_API_166 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_SETWAKEUPMODE_SID, CANTRCV_E_PARAM_TRCV_WAKEUP_MODE);
  }
  else
  #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
  {
    /* Get the pointer to the structure of the requested network */
    ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[Transceiver];

    /* Check channel is used and supported wake up or not */
    if ((CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed) &&
      (CANTRCV_FALSE != ptrCanTrcvNetwork->WakeupByBusUsed))
    {
      /* @Trace: CanTrcv_SUD_API_167 */
      /* Invoke internal function to set wake up mode */
      returnValue = CanTrcv_IntSetWakeupMode(Transceiver, TrcvWakeupMode);
    }
    else
    {
      /* @Trace: CanTrcv_SUD_API_309 */
      /* Report a Development error If there is no/incorrect communication to
        the transceiver */
      (void)Det_ReportRuntimeError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
        CANTRCV_SETWAKEUPMODE_SID, CANTRCV_E_NO_TRCV_CONTROL);
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CANTRCV_GETBUSWUREASON_MACRO                        **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : Gets the wakeup reason for the Transceiver and      **
**                        returns it in parameter Reason.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Transceiver - CAN transceiver to which API call has **
**                                      to be applied.                        **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : reason - Pointer to wake up reason of the bus the   **
**                                 API is applied to.                         **
**                                                                            **
** Return parameter     : E_OK:     Will be returned if the transceiver       **
**                                  wakeup reason was provided.               **
**                        E_NOT_OK: Will be returned if no wake up reason is  **
**                                  available or if the service request       **
**                                  failed due to development errors.         **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  : CanTrcv_InitStatus,           **
**                        CanTrcv_CanTrcvNetwork,                             **
**                        CanTrcv_WakeUpReason                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        Det_ReportRuntimeError                              **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00007 SWS_CanTrcv_00050 SWS_CanTrcv_00165
  SWS_CanTrcv_00107 SWS_CanTrcv_00116 SWS_CanTrcv_00125 SWS_CanTrcv_00130
  SWS_CanTrcv_00133 SWS_CanTrcv_00085 SWS_CanTrcv_00086 SRS_BSW_00310
  SRS_BSW_00327 SRS_BSW_00350  SRS_BSW_00357 SRS_BSW_00369 SRS_BSW_00371
  SRS_BSW_00375 SRS_BSW_00377 SRS_BSW_00386 SRS_Can_01091 SRS_Can_01097
  SRS_Can_01109 SRS_Can_01110 SRS_Can_01106 SRS_Can_01103 SRS_Can_01095
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_GETBUSWUREASON_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_APPL_DATA) reason)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize return value as E_NOT_OK */
  returnValue = E_NOT_OK;

  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  /* Check whether the module is Initialized */
  if (CANTRCV_UNINITIALIZED == CanTrcv_InitStatus)
  {
    /* @Trace: CanTrcv_SUD_API_171 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_GETBUSWUREASON_SID, CANTRCV_E_UNINIT);
  }
  /* Check whether the Transceiver id is out of range */
  else if (CANTRCV_NUM_OF_NETWORKS <= Transceiver)
  {
    /* @Trace: CanTrcv_SUD_API_172 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_GETBUSWUREASON_SID, CANTRCV_E_INVALID_TRANSCEIVER);
  }
  /* Check for NULL POINTER */
  else if (NULL_PTR == reason)
  /* polyspace +5 RTE:UNR [Justified:Low] "This DET error is reported when reason is set to NULL pointer." */
  {
    /* @Trace: CanTrcv_SUD_API_173 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_GETBUSWUREASON_SID, CANTRCV_E_PARAM_POINTER);
  }
  else
  #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
  {
    /* Get the pointer to the structure of the requested network */
    ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[Transceiver];

    /* Check channel is used and support wake up or not */
    if ((CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed) &&
      (CANTRCV_FALSE != ptrCanTrcvNetwork->WakeupByBusUsed))
    {
      /* @Trace: CanTrcv_SUD_API_174 */
      /* Get wake up reason */
      /* polyspace +1 MISRA2012:D4.14 [Justified:Low] "Pointer reason is checked NULL by DET." */
      *reason = CanTrcv_WakeUpReason[Transceiver];
      /* Set the return value to E_OK */
      returnValue = (Std_ReturnType)E_OK;
    }
    else
    {
      /* @Trace: CanTrcv_SUD_API_175 */
      /* Report a Development error If there is no/incorrect communication to
        the transceiver */
      (void)Det_ReportRuntimeError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
        CANTRCV_GETBUSWUREASON_SID, CANTRCV_E_NO_TRCV_CONTROL);
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CANTRCV_MAINFUNCTION_MACRO                          **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : Service to scan all busses for wake up events and   **
**                        perform these event.                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanTrcv_CanTrcvNetwork        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_IntMainFunction,                            **
**                        CanTrcv_CheckWakeFlagIndication                     **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00013 SWS_CanTrcv_00050 SWS_CanTrcv_00112
  SWS_CanTrcv_00086 SRS_BSW_00172 SRS_BSW_00171 SRS_BSW_00310 SRS_BSW_00327
  SRS_BSW_00343 SRS_BSW_00350 SRS_BSW_00371 SRS_BSW_00373 SRS_BSW_00424
  SRS_BSW_00428 SRS_Can_01097 SRS_Can_01109 SRS_Can_01110
*/
FUNC(void, CANTRCV_CODE) CANTRCV_MAINFUNCTION_MACRO(void)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(uint8, AUTOMATIC) transceiver;

  /* Check whether module is initialized */
  if (CANTRCV_UNINITIALIZED != CanTrcv_InitStatus)
  {
    /* Scan all channel */
    for(transceiver = (uint8)CANTRCV_ZERO;
      transceiver < CANTRCV_NUM_OF_NETWORKS; transceiver++)
    {
      /* Get the pointer to the structure of the requested network */
      ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

      /* Scan all busses in STANDBY and SLEEP for wake up events. */
      if ((CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed) &&
        (CANTRCV_FALSE != ptrCanTrcvNetwork->WakeupByBusUsed) &&
        (CANTRCV_TRCVMODE_NORMAL != CanTrcv_ByteArray[transceiver]))
      {
        /* @Trace: CanTrcv_SUD_API_214 */
        CanTrcv_IntMainFunction(transceiver);
      }
      else
      {
        /* Nothing to do */
      }
      /* polyspace +5 DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanTrcv. No impact" */
      #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
      /* Check wake flag indication */
      #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
      if ((CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed) &&
        (CANTRCV_INVALID_PNINDEX != ptrCanTrcvNetwork->PnNetworkIndex) &&
        (CANTRCV_TRUE == CanTrcv_CheckWakeFlagIndication[transceiver]))
      {
        /* @Trace: CanTrcv_SUD_API_215 */
        /* Disable flag indication */
        CanTrcv_CheckWakeFlagIndication[transceiver] = CANTRCV_FALSE;
        /* Invoke internal function to check wake flag */
        CanTrcv_IntCheckWakeFlag(transceiver);
      }
      else
      {
        /* Nothing to do */
      }
      /* Check clear wake up flag */
      if (CanTrcv_ClearWufFlag[transceiver] == CANTRCV_TRUE)
      {
        /* Reset the status of clear wake up flag  */
        CanTrcv_ClearWufFlag[transceiver] = CANTRCV_FALSE;
        /* Notify to upper layer about the wake up flag has been cleared */
        CanIf_ClearTrcvWufFlagIndication(transceiver);
      }

      #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */
      #endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */
    }
  }
  else
  {
    /* Nothing to do */
  }
}
#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
/*******************************************************************************
** Function Name        : CANTRCV_CHECKWAKEFLAG_MACRO                         **
**                                                                            **
** Service ID           : 0x0E                                                **
**                                                                            **
** Description          : Requests to check the status of the wakeup flag     **
**                        from the transceiver hardware.                      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Transceiver - CAN transceiver to which API call has **
**                                      to be applied.                        **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK:     Will be returned, if the request for      **
**                                  checking the wakeup flag has been         **
**                                  accepted.                                 **
**                        E_NOT_OK: Will be returned, if the request for      **
**                                  checking the wakeup flag has not been     **
**                                  accepted.                                 **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        CanTrcv_CanTrcvNetwork,                             **
**                        CanTrcv_CheckWakeFlagIndication                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00223 SWS_CanTrcv_00224 SWS_CanTrcv_00050
  SWS_CanTrcv_00225 SWS_CanTrcv_00086 SRS_BSW_00327 SRS_BSW_00350 SRS_BSW_00357
  SRS_BSW_00369 SRS_BSW_00386 SRS_Can_01091
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_CHECKWAKEFLAG_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize return value to E_NOT_OK */
  returnValue = (Std_ReturnType)E_NOT_OK;

  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  /* Check whether the Transceiver id is out of range */
  if (CANTRCV_NUM_OF_NETWORKS <= Transceiver)
  {
    /* @Trace: CanTrcv_SUD_API_162 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_CHECKWAKEFLAG_SID, CANTRCV_E_INVALID_TRANSCEIVER);
  }
  else
  #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
  {
    /* Get the pointer to the structure of the requested network */
    ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[Transceiver];
    /* Check channel is used and support wake up or not */
    if ((CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed) &&
      (CANTRCV_FALSE != ptrCanTrcvNetwork->WakeupByBusUsed) &&
      (CANTRCV_INVALID_PNINDEX != ptrCanTrcvNetwork->PnNetworkIndex))
    {
      /* @Trace: CanTrcv_SUD_API_163 */
      /* Set flag to perform check wake flag in main function */
      CanTrcv_CheckWakeFlagIndication[Transceiver] = CANTRCV_TRUE;
      /* Set return value as E_OK */
      returnValue = (Std_ReturnType)E_OK;
    }
    else
    {
      /* Nothing to do */
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CANTRCV_GETTRCVSYSTEMDATA_MACRO                     **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : Reads the transceiver configuration/status data     **
**                        and returns it through parameter TrcvSysData.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Transceiver - CAN transceiver ID.                   **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : TrcvSysData - Configuration/Status data of the      **
**                                      transceiver.                          **
**                                                                            **
** Return parameter     : E_OK:     Will be returned if the transceiver       **
**                                  status is successfully read.              **
**                        E_NOT_OK: Will be returned if the transceiver       **
**                                  status data is not available or a         **
**                                  development error occurs.                 **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized and      **
**                        CanTrcvHwPnSupport = TRUE                           **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanTrcv_InitStatus,                                 **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        CanTrcv_IntGetTrcvSystemData                        **
**                        Det_ReportRuntimeError                              **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00050 SWS_CanTrcv_00175 SWS_CanTrcv_00213
  SWS_CanTrcv_00189 SWS_CanTrcv_00190 SWS_CanTrcv_00191 SWS_CanTrcv_00192
  SWS_CanTrcv_00193 SWS_CanTrcv_00085 SWS_CanTrcv_00086 SRS_BSW_00327
  SRS_BSW_00350 SRS_BSW_00357 SRS_BSW_00369 SRS_BSW_00386 SRS_Can_01091
*/
/* polyspace +3 MISRA2012:8.13 [Not a defect:Low] "This function definition follow Autosar requirement SWS_CanTrcv_00213(R21-11). No impact"*/
FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_GETTRCVSYSTEMDATA_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  P2VAR(uint32, AUTOMATIC, CANTRCV_VAR) TrcvSysData)
{
  #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize return value to E_NOT_OK */
  returnValue = E_NOT_OK;

  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  /* Check whether the module is Initialized */
  if (CANTRCV_UNINITIALIZED == CanTrcv_InitStatus)
  {
    /* @Trace: CanTrcv_SUD_API_310 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_GETTRCVSYSTEMDATA_SID, CANTRCV_E_UNINIT);
  }
  /* Check whether the Transceiver id is out of range */
  else if (CANTRCV_NUM_OF_NETWORKS <= Transceiver)
  {
    /* @Trace: CanTrcv_SUD_API_311 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_GETTRCVSYSTEMDATA_SID, CANTRCV_E_INVALID_TRANSCEIVER);
  }
  /* Check for NULL POINTER */
  else if (NULL_PTR == TrcvSysData)
  /* polyspace +5 RTE:UNR [Justified:Low] "This DET error is reported when TrcvSysData is set to NULL pointer." */
  {
    /* @Trace: CanTrcv_SUD_API_312 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_GETTRCVSYSTEMDATA_SID, CANTRCV_E_PARAM_POINTER);
  }
  else
  #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
  {
    #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
    /* Get the pointer to the structure of the requested network */
    ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[Transceiver];
    /* polyspace +3 DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanTrcv. No impact" */
    /* Check channel is used and support partial networking or not */
    if ((CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed) &&
      (CANTRCV_INVALID_PNINDEX != ptrCanTrcvNetwork->PnNetworkIndex))
    {
      /* @Trace: CanTrcv_SUD_API_313 */
      /* Invoke internal function to get transceiver system flag */
      #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
           (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
          (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
      returnValue = CanTrcv_IntGetTrcvSystemData(Transceiver, TrcvSysData);
      #else
      returnValue = CanTrcv_IntGetTrcvSystemData(Transceiver);
      CANTRCV_UNUSED_VAL(TrcvSysData);
      #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
               (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
               (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */
    }
    else
    #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */
    {
      /* @Trace: CanTrcv_SUD_API_314 */
      /* Report a Development error If there is no/incorrect communication to
        the transceiver */
      (void)Det_ReportRuntimeError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
        CANTRCV_GETTRCVSYSTEMDATA_SID, CANTRCV_E_NO_TRCV_CONTROL);
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CANTRCV_READTRCVTIMEOUTFLAG_MACRO                   **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : Reads the status of the timeout flag from the       **
**                        transceiver hardware.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Transceiver - CAN transceiver ID.                   **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : FlagState - State of the timeout flag.              **
**                                                                            **
** Return parameter     : E_OK:     Will be returned, if status of the        **
**                                  timeout flag is successfully read.        **
**                        E_NOT_OK: Will be returned, if status of the        **
**                                  timeout flag could not be read.           **
**                                                                            **
** Preconditions        : CanTrcvHwPnSupport = TRUE                           **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        CanTrcv_IntReadTrcvTimeoutFlag                      **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00050 SWS_CanTrcv_00175 SWS_CanTrcv_00215
  SWS_CanTrcv_00199 SWS_CanTrcv_00200 SWS_CanTrcv_00086 SWS_CanTrcv_00211
  SRS_BSW_00327 SRS_BSW_00350 SRS_BSW_00357 SRS_BSW_00369 SRS_BSW_00386
  SRS_Can_01091
*/
/* polyspace +3 MISRA2012:8.13 [Not a defect:Low] "This function definition follow Autosar requirement SWS_CanTrcv_00215(R21-11). No impact "*/
FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_READTRCVTIMEOUTFLAG_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState)
{
  #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize return value to E_NOT_OK */
  returnValue = E_NOT_OK;

  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  /* Check whether the Transceiver id is out of range */
  if (CANTRCV_NUM_OF_NETWORKS <= Transceiver)
  {
    /* @Trace: CanTrcv_SUD_API_315 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_READTRCVTIMEOUTFLAG_SID, CANTRCV_E_INVALID_TRANSCEIVER);
  }
  /* Check for NULL POINTER */
  else if (NULL_PTR == FlagState)
  /* polyspace +5 RTE:UNR [Justified:Low] "This DET error is reported when FlagState is set to NULL pointer." */
  {
    /* @Trace: CanTrcv_SUD_API_176 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_READTRCVTIMEOUTFLAG_SID, CANTRCV_E_PARAM_POINTER);
  }
  else
  #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
  {
    #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
    /* Get the pointer to the structure of the requested network */
    ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[Transceiver];
    /* polyspace +3 DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanTrcv. No impact" */
    /* Check channel is used and support partial networking or not */
    if ((CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed) &&
      (CANTRCV_INVALID_PNINDEX != ptrCanTrcvNetwork->PnNetworkIndex))
    {
      /* @Trace: CanTrcv_SUD_API_177 */
      /* Invoke internal function to get transceiver time out flag */
      #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
           (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
           (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
      returnValue = CanTrcv_IntReadTrcvTimeoutFlag(Transceiver, FlagState);
      #else
      returnValue = CanTrcv_IntReadTrcvTimeoutFlag();
      #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
           (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
           (STD_ON == CANTRCV_TLE9255W_SUPPORTED))*/
    }
    else
    #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */
    {
      /* Nothing to do */
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CANTRCV_CLEARTRCVTIMEOUTFLAG_MACRO                  **
**                                                                            **
** Service ID           : 0x0C                                                **
**                                                                            **
** Description          : Clears the status of the timeout flag in the        **
**                        transceiver hardware.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Transceiver - CAN transceiver ID.                   **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK:     Will be returned, if the timeout flag is  **
**                                  successfully cleared.                     **
**                        E_NOT_OK: Will be returned, if the timeout flag     **
**                                  could not be cleared.                     **
**                                                                            **
** Preconditions        : CanTrcvHwPnSupport = TRUE                           **
**                                                                            **
** Remarks              : Global Variable(s): CanTrcv_CanTrcvNetwork          **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Det_ReportError,                                    **
**                        CanTrcv_IntClearTrcvTimeoutFlag                     **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00050 SWS_CanTrcv_00175 SWS_CanTrcv_00216
  SWS_CanTrcv_00201 SWS_CanTrcv_00086 SRS_BSW_00327 SRS_BSW_00350 SRS_BSW_00357
  SRS_BSW_00369 SRS_BSW_00386 SRS_Can_01091
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_CLEARTRCVTIMEOUTFLAG_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver)
{
  #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize return value to E_NOT_OK */
  returnValue = E_NOT_OK;

  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  /* Check whether the Transceiver id is out of range */
  if (CANTRCV_NUM_OF_NETWORKS <= Transceiver)
  {
    /* @Trace: CanTrcv_SUD_API_186 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_CLEARTRCVTIMEOUTFLAG_SID, CANTRCV_E_INVALID_TRANSCEIVER);
  }
  else
  #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
  {
    #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
    /* Get the pointer to the structure of the requested network */
    ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[Transceiver];
    /* polyspace +3 DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanTrcv. No impact" */
    /* Check channel is used and support partial networking or not */
    if ((CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed) &&
      (CANTRCV_INVALID_PNINDEX != ptrCanTrcvNetwork->PnNetworkIndex))
    {
      /* @Trace: CanTrcv_SUD_API_187 */
      /* Invoke internal function to clear transceiver time out flag */
      returnValue = CanTrcv_IntClearTrcvTimeoutFlag(Transceiver);
    }
    else
    {
      /* Nothing to do */
    }
    #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CANTRCV_READTRCVSILENCEFLAG_MACRO                   **
**                                                                            **
** Service ID           : 0x0D                                                **
**                                                                            **
** Description          : Reads the status of the silence flag from the       **
**                        transceiver hardware.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Transceiver - CAN transceiver ID.                   **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : FlagState - State of the silence flag.              **
**                                                                            **
** Return parameter     : E_OK:     Will be returned, if status of the        **
**                                  silence flag is successfully read.        **
**                        E_NOT_OK: Will be returned, if status of the        **
**                                  silence flag could not be read.           **
**                                                                            **
** Preconditions        : CanTrcvHwPnSupport = TRUE                           **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        CanTrcv_IntReadTrcvSilenceFlag                      **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00050 SWS_CanTrcv_00175 SWS_CanTrcv_00217
  SWS_CanTrcv_00202 SWS_CanTrcv_00203 SWS_CanTrcv_00086 SWS_CanTrcv_00211
  SRS_BSW_00327 SRS_BSW_00350 SRS_BSW_00357 SRS_BSW_00369 SRS_BSW_00386
  SRS_Can_01091
*/
/* polyspace +3 MISRA2012:8.13 [Not a defect:Low] " This function definition follow Autosar requirement SWS_CanTrcv_00217(R21-11). No impact "*/
FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_READTRCVSILENCEFLAG_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState)
{
  #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize return value to E_NOT_OK */
  returnValue = E_NOT_OK;

  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  /* Check whether the Transceiver id is out of range */
  if (CANTRCV_NUM_OF_NETWORKS <= Transceiver)
  {
    /* @Trace: CanTrcv_SUD_API_192 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_READTRCVSILENCEFLAG_SID, CANTRCV_E_INVALID_TRANSCEIVER);
  }
  /* Check for NULL POINTER */
  else if (NULL_PTR == FlagState)
  /* polyspace +5 RTE:UNR [Justified:Low] "This DET error is reported when FlagState is set to NULL pointer." */
  {
    /* @Trace: CanTrcv_SUD_API_193 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_READTRCVSILENCEFLAG_SID, CANTRCV_E_PARAM_POINTER);
  }
  else
  #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
  {
    #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
    /* Get the pointer to the structure of the requested network */
    ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[Transceiver];
    /* polyspace +3 DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanTrcv. No impact" */
    /* Check channel is used and support partial networking or not */
    if ((CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed) &&
      (CANTRCV_INVALID_PNINDEX != ptrCanTrcvNetwork->PnNetworkIndex))
    {
      /* @Trace: CanTrcv_SUD_API_194 */
      /* Invoke internal function to read transceiver silence flag */
      #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
           (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
           (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
      returnValue = CanTrcv_IntReadTrcvSilenceFlag(Transceiver, FlagState);
      #else
      returnValue = CanTrcv_IntReadTrcvSilenceFlag();
      CANTRCV_UNUSED_VAL(FlagState);
      #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
           (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
           (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */
    }
    else
    {
      /* Nothing to do */
    }
    #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CANTRCV_SETPNACTIVATIONSTATE_MACRO                  **
**                                                                            **
** Service ID           : 0x0F                                                **
**                                                                            **
** Description          : The API configures the wake-up of the transceiver   **
**                        for Standby and Sleep Mode: Either the CAN          **
**                        transceiver is woken up by a remote wake-up pattern **
**                        (standard CAN wake-up) or by the configured remote  **
**                        wake-up frame.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ActivationState - PN_ENABLED: PN wakeup enable.     **
**                                          PN_DIABLED: PN wakeup disbale.    **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK:     Will be returned, if the PN has been      **
**                                  changed to the requested configuration.   **
**                        E_NOT_OK: Will be returned, if the PN configuration **
**                                  change has failed. The previous           **
**                                  configuration has not been changed.       **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized and      **
**                        CanTrcvHwPnSupport = TRUE                           **
**                                                                            **
** Remarks              : Global Variable(s): CanTrcv_InitStatus,             **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked : Det_ReportError,              **
**                        CanTrcv_IntSetPNActivationState                     **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00050 SWS_CanTrcv_00219 SWS_CanTrcv_00220
  SWS_CanTrcv_00221 SWS_CanTrcv_00222 SWS_CanTrcv_00086 SWS_CanTrcv_00210
  SRS_BSW_00327 SRS_BSW_00350 SRS_BSW_00357 SRS_BSW_00369 SRS_BSW_00386
  SRS_Can_01091
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_SETPNACTIVATIONSTATE_MACRO(
  VAR(CanTrcv_PNActivationType, AUTOMATIC) ActivationState)
{
  #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(uint8, AUTOMATIC) transceiver;
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  
  /* Initialize return value to E_OK */
  returnValue = E_NOT_OK;
  #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
  returnStatus = E_OK;
  #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */

  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  /* Check whether the module is Initialized */
  if (CANTRCV_UNINITIALIZED == CanTrcv_InitStatus)
  {
    /* @Trace: CanTrcv_SUD_API_199 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_SETPNACTIVATIONSTATE_SID, CANTRCV_E_UNINIT);
  }
  else
  #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
  {
    #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
    /* Scan all channel */
    for(transceiver = (uint8)CANTRCV_ZERO;
      transceiver < CANTRCV_NUM_OF_NETWORKS; transceiver++)
    {
      /* Get the pointer to the structure of the requested network */
      ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
      /* polyspace +3 DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanTrcv. No impact" */
      /* Check channel is used and support partial networking */
      
      if ((CANTRCV_TRUE == ptrCanTrcvNetwork->ChannelUsed) &&
        (CANTRCV_INVALID_PNINDEX != ptrCanTrcvNetwork->PnNetworkIndex))
      {
        /* @Trace: CanTrcv_SUD_API_200 */
        /* Invoke internal function to set state of partial networking */
        returnStatus |= CanTrcv_IntSetPNActivationState(transceiver,
          ActivationState);
        if (E_OK != returnStatus)
        {
          returnValue = E_NOT_OK;
        }
        else
        {
          returnValue = E_OK;
        }
      }
    }
    #else
    CANTRCV_UNUSED_VAL(ActivationState);
    #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CANTRCV_CLEARTRCVWUFFLAG_MACRO                      **
**                                                                            **
** Service ID           : 0x0A                                                **
**                                                                            **
** Description          : Clears the WUF flag in the transceiver hardware.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different transceivers                **
**                                                                            **
** Input Parameters     : Transceiver - CAN transceiver ID.                   **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Will be returned if the WUF flag has been     **
**                              cleared.                                      **
**                        E_NOT_OK: Will be returned if the WUF flag has not  **
**                              been cleared or a development error occurs.   **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized and      **
**                        CanTrcvHwPnSupport = TRUE.                          **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanTrcv_InitStatus,                                 **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Det_ReportError,                                    **
**                        Det_ReportRuntimeError,                             **
**                        CanTrcv_IntClearTrcvWufFlag                         **
**                        CanIf_ClearTrcvWufFlagIndication                    **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00050 SWS_CanTrcv_00175 SWS_CanTrcv_00214
  SWS_CanTrcv_00194 SWS_CanTrcv_00195 SWS_CanTrcv_00196 SWS_CanTrcv_00197
  SWS_CanTrcv_00198 SWS_CanTrcv_00085 SWS_CanTrcv_00086 SRS_BSW_00327
  SRS_BSW_00350 SRS_BSW_00357 SRS_BSW_00369 SRS_BSW_00386 SRS_Can_01091
  SRS_Can_01157 */
FUNC(Std_ReturnType, CANTRCV_CODE) CANTRCV_CLEARTRCVWUFFLAG_MACRO(
  VAR(uint8, AUTOMATIC) Transceiver)
{
  #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize return value to E_NOT_OK */
  returnValue = E_NOT_OK;

  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  /* Check whether the module is initialized */
  if (CANTRCV_UNINITIALIZED == CanTrcv_InitStatus)
  {
    /* @Trace: CanTrcv_SUD_API_203 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_CLEARTRCVWUFLAG_SID, CANTRCV_E_UNINIT);
  }
  /* Check whether the Transceiver id is out of range */
  else if (CANTRCV_NUM_OF_NETWORKS <= Transceiver)
  {
    /* @Trace: CanTrcv_SUD_API_204 */
    /* Report to DET */
    (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
      CANTRCV_CLEARTRCVWUFLAG_SID, CANTRCV_E_INVALID_TRANSCEIVER);
  }
  else
  #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
  {
    #if ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK))
    /* Get the pointer to the structure of the requested network */
    ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[Transceiver];

    if ((CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed) &&
      (CANTRCV_INVALID_PNINDEX != ptrCanTrcvNetwork->PnNetworkIndex))
    {
      /* @Trace: CanTrcv_SUD_API_205 */
      /* Invoke internal function to clear transceiver wake up frame flag */
      returnValue = CanTrcv_IntClearTrcvWufFlag(Transceiver);
      /* check status clear transceiver wake up frame flag */
      if (E_NOT_OK != returnValue)
      {
        /* @Trace: CanTrcv_SUD_API_206 */
        /* Inform CanIf that the wakeup flag has been cleared */
        CanTrcv_ClearWufFlag[Transceiver] = CANTRCV_TRUE;
      }
      else
      {
        /* Nothing to do */
      }
    }
    else
    #endif /* ((STD_ON == CANTRCV_CHANNEL_USED) && (STD_ON == CANTRCV_CHANNEL_USED_PN_NETWORK)) */
    {
      /* @Trace: CanTrcv_SUD_API_207 */
      /* Report a Development error If there is no/incorrect communication to
        the transceiver */
      (void)Det_ReportRuntimeError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
        CANTRCV_CLEARTRCVWUFLAG_SID, CANTRCV_E_NO_TRCV_CONTROL);
    }
  }

  return returnValue;
}
#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

/*******************************************************************************
** Function Name        : CANTRCV_DEINIT_MACRO                                **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : De-initializes the CanTrcv module.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        CanTrcv_ByteArray,                                  **
**                        CanTrcv_DeinitStatus,                               **
**                        CanTrcv_InitStatus                                  **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Det_ReportError,                                    **
**                        Det_ReportRuntimeError                              **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_91001 SWS_CanTrcv_91002 SWS_CanTrcv_91003
  SWS_CanTrcv_91004 SWS_CanTrcv_91005 SWS_CanTrcv_00085 SWS_CanTrcv_00086
  SRS_BSW_00336 SRS_BSW_00369 SRS_BSW_00386 SRS_Can_01091 SRS_Can_01108
*/
FUNC(void, CANTRCV_CODE) CANTRCV_DEINIT_MACRO(void)
{
  #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL)
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif /* (STD_OFF == CANTRCV_CHANNEL_USED_ALL) */
  VAR(uint8, AUTOMATIC) transceiver;
  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  VAR(boolean, AUTOMATIC) errFlag;

  /* Initialize error flag as CANTRCV_FALSE */
  errFlag = CANTRCV_FALSE;

  /* Scan all channel */
  /* @Trace: CanTrcv_SUD_API_008 */
  for(transceiver = (uint8)CANTRCV_ZERO;
    transceiver < CANTRCV_NUM_OF_NETWORKS; transceiver++)
  {
    #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL)
    /* Get the pointer to the structure of the requested network */
    ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
    /* Check channel is used or not */
    if (CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed)
    #endif /* (STD_OFF == CANTRCV_CHANNEL_USED_ALL) */
    {
      /* Check state of all Can Transceivers, if there are any Can Transceiver
        is in Normal state, report DET error */
      if (CANTRCV_TRCVMODE_NORMAL == CanTrcv_ByteArray[transceiver])
      {
        /* Report to DET */
        (void)Det_ReportError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
          CANTRCV_DEINIT_SID, CANTRCV_E_TRCV_NOT_NORMAL);
        /* Set DET error flag as TRUE */
        errFlag = CANTRCV_TRUE;
        /* Break the loop */
        break;
      }
      else
      {
        /* Nothing to do */
      }
    }
  }
  if ((CANTRCV_TRUE != errFlag) && (CANTRCV_UNINITIALIZED != CanTrcv_InitStatus))
  #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
  {
    /* Scan all channel */
    for(transceiver = (uint8)CANTRCV_ZERO;
      transceiver < CANTRCV_NUM_OF_NETWORKS; transceiver++)
    {
      #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL)
      /* Get the pointer to the structure of the requested network */
      ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
      /* Check channel is used or not */
      /* polyspace +1 DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanTrcv. No impact" */
      if (CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed)
      #endif /* (STD_OFF == CANTRCV_CHANNEL_USED_ALL) */
      {
        #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
        /* Set wake up mode is disable */
        CanTrcv_WakeupMode[transceiver] = CANTRCV_WUMODE_DISABLE;
        #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

        #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
           (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
           (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
        /* @Trace: CanTrcv_SUD_API_009 */
        (void)CanTrcv_IntDeInitializeBySpi(transceiver);
        #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
           (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
           (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */
      }
      #if (STD_OFF == CANTRCV_CHANNEL_USED_ALL)
      else
      {
        /* Report a Development error If there is no/incorrect communication to
          the transceiver */
        /* @Trace: CanTrcv_SUD_API_010 */
        (void)Det_ReportRuntimeError(CANTRCV_MODULE_ID, CANTRCV_INSTANCE_ID,
          CANTRCV_DEINIT_SID, CANTRCV_E_NO_TRCV_CONTROL);
      }
      #endif /* (STD_OFF == CANTRCV_CHANNEL_USED_ALL) */
    }
    /* Set the global variable from initialized to uninitialized */
    CanTrcv_InitStatus = CANTRCV_UNINITIALIZED;
  }
  #if (STD_ON == CANTRCV_DEV_ERROR_DETECT)
  else
  {
    /* Nothing to do */
  }
  #endif /* (STD_ON == CANTRCV_DEV_ERROR_DETECT) */
}

#if (STD_ON == CANTRCV_E_BUS_ERROR_SUPPORTED)
/*******************************************************************************
** Function Name        : CANTRCV_MAINFUNCTIONDIAGNOSTICS_MACRO               **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This service Reads the transceiver diagnostic       **
**                        status periodically and sets product/development    **
*                         accordingly.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanTrcv_CanTrcvNetwork        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_IntMainFunctionDiagnostics                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00205 SWS_CanTrcv_00218 SRS_BSW_00343 SRS_BSW_00373
  SRS_BSW_00386
*/
/* polyspace -begin MISRA-C3:18.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
FUNC(void, CANTRCV_CODE) CANTRCV_MAINFUNCTIONDIAGNOSTICS_MACRO(void)
{
  #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  P2CONST(CanTrcv_PartialNetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvPnNetwork;
  VAR(uint8, AUTOMATIC) transceiver;
  VAR(uint8, AUTOMATIC) pnIndex;

  /* Check whether module is initialized */
  if (CANTRCV_UNINITIALIZED != CanTrcv_InitStatus)
  {
    /* Scan all channel */
    for(transceiver = (uint8)CANTRCV_ZERO;
      transceiver < CANTRCV_NUM_OF_NETWORKS; transceiver++)
    {
      /* Get the pointer to the structure of the requested network */
      ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
      /* Get the index of PN network */
      pnIndex = ptrCanTrcvNetwork->PnNetworkIndex;
      /* Check channel is used and support partial networking and
         in active mode
      */
      /* polyspace -begin RTE:IDP [Justified:Low] "The size of CanTrcv_PartialNetwork is pre-defined, the value of pnIndex is already guaranteed by generator" */
      /* polyspace -begin MISRA-C3:D4.1 [Justified:Low] "The value of  pnIndex is checked by generator.
       * Therefore, it will never exceed the size of CanTrcv_PartialNetwork which is pre-defined." */
      /* polyspace +4 MISRA-C3:18.1 [Justified:Low] "The size of CanTrcv_PartialNetwork  is pre-defined, the value of pnIndex is guaranteed by generator.
       *  So, ptrCanTrcvPnNetwork is valid in this case." */
      /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "The size of CanTrcv_PartialNetwork  is pre-defined, the value of pnIndex is guaranteed by generator.
       * So, ptrCanTrcvPnNetwork is valid in this case." */
      if ((CANTRCV_FALSE != ptrCanTrcvNetwork->ChannelUsed) &&
        (CANTRCV_INVALID_PNINDEX != ptrCanTrcvNetwork->PnNetworkIndex) &&
        (CANTRCV_TRCVMODE_NORMAL == CanTrcv_ByteArray[transceiver]))
      {
        /* Get the pointer to the structure of the requested PN network */
        /* polyspace +8 MISRA-C3:18.1 [Justified:Low] "The size of CanTrcv_PartialNetwork  is pre-defined, the value of pnIndex is guaranteed by generator.
    	*  So, ptrCanTrcvPnNetwork is valid in this case." */
    	/* polyspace +6 MISRA-C3:D4.1 [Justified:Low] "The size of CanTrcv_PartialNetwork  is pre-defined, the value of pnIndex is guaranteed by generator.
    	* So, ptrCanTrcvPnNetwork is valid in this case." */
    	/* polyspace +4 RTE:IDP [Justified:Low] "The size of CanTrcv_PartialNetwork is pre-defined, the value of pnIndex is checked by generator.
    	   * So, pointer ptrCanTrcvNetwork is valid." */
        ptrCanTrcvPnNetwork = &CanTrcv_PartialNetwork[pnIndex];
        if (CANTRCV_FALSE != ptrCanTrcvPnNetwork->BusErrFlag)
        {
          /* @Trace: CanTrcv_SUD_API_245 */
          CanTrcv_IntMainFunctionDiagnostics(transceiver);
        }
        else
        {
          /* Nothing to do */
        }
      }
      /* polyspace -end RTE:IDP [Justified:Low] "The size of CanTrcv_PartialNetwork is pre-defined, the value of pnIndex is already guaranteed by generator" */
      /* polyspace -end MISRA-C3:D4.1 [Justified:Low] "The value of  pnIndex is checked by generator.
       * Therefore, it will never exceed the size of CanTrcv_PartialNetwork which is pre-defined." */
      else
      {
        /* Nothing to do */
      }
    }
  }
  else
  {
    /* Nothing to do */
  }
  #endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */
}
#endif /* (STD_ON == CANTRCV_E_BUS_ERROR_SUPPORTED) */
/* polyspace -end MISRA-C3:18.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
/*******************************************************************************
**                      AUTRON APIs                                           **
*******************************************************************************/
#if ((STD_ON == CANTRCV_ARISUCAN_SUPPORTED) && \
  (STD_ON == CANTRCV_SPI_SUPPORTED))
/*******************************************************************************
** Function Name        : CanTrcv_ArisuCan_GetInternalSBCMode                 **
**                                                                            **
** Service ID           : 0x12                                                **
**                                                                            **
** Description          : This service will return SBC mode of ArisuCan.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : SBC mode for ArisuCan.                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked :                               **
**                        CanTrcv_ArisuCan_IntGetInternalSBCMode              **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_HWM_00005 */
FUNC(ArisuCan_SBCModeType, CANTRCV_CODE)
  CanTrcv_ArisuCan_GetInternalSBCMode(void)
{
  /* @Trace: CanTrcv_SUD_API_253 */
  /* Return SBC mode of ArisuCan */
  return CanTrcv_ArisuCan_IntGetInternalSBCMode();
}

/*******************************************************************************
** Function Name        : CanTrcv_ArisuCan_ReadStatus                         **
**                                                                            **
** Service ID           : 0x13                                                **
**                                                                            **
** Description          : This service will read value in register on         **
**                        ArisuCan.                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : address - Pointer to source address.                **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : data - Value in ArisuCan register.                  **
**                                                                            **
** Return parameter     : E_OK:     Will be returned if the transceiver state **
**                                  read successed.                           **
**                        E_NOT_OK: Will be returned if the transceiver state **
**                                  read failed.                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked :                               **
**                        CanTrcv_ArisuCan_IntReadStatus                      **
**                                                                            **
*******************************************************************************/
/* @Trace: CanTrcv_SAD_HWM_00003 SRS_BSW_00357 SRS_HWM_00003 */
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_ReadStatus(
  VAR(CanTrcv_ArisuCanType, AUTOMATIC) address,
  P2VAR(CanTrcv_ArisuCanType, AUTOMATIC, CANTRCV_VAR) data)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  if (NULL_PTR == data)
  /* polyspace +4 RTE:UNR [Justified:Low] "This function returns E_NOT_OK when data is set to NULL pointer." */
  {
    /* Set the return value to E_NOT_OK */
    returnValue = E_NOT_OK;
  }
  else
  {
    /* @Trace: CanTrcv_SUD_API_255 */
    /* Invoke internal function to read register value */
    returnValue = CanTrcv_ArisuCan_IntReadStatus(address, data);
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : CanTrcv_ArisuCan_PowerDownMode                      **
**                                                                            **
** Service ID           : 0x14                                                **
**                                                                            **
** Description          : This service will set power down mode for ArisuCan. **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK:     Will be returned if the transceiver       **
**                                  state change.                             **
**                        E_NOT_OK: Will be returned if the request for       **
**                                  transceiver mode change to stop mode      **
**                                  has not been completed.                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_ArisuCan_IntPowerDownMode                   **
**                                                                            **
*******************************************************************************/
/* @Trace: CanTrcv_SAD_HWM_00002 SRS_BSW_00357 SRS_HWM_00002 */
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_PowerDownMode(void)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* @Trace: CanTrcv_SUD_API_260 */
  /* Invoke internal function to read register value */
  returnValue = CanTrcv_ArisuCan_IntPowerDownMode();

  return returnValue;
}

/*******************************************************************************
** Function Name        : CanTrcv_ArisuCan_ChangeStopMode                     **
**                                                                            **
** Service ID           : 0x15                                                **
**                                                                            **
** Description          : This service will change stop mode.                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK:     Will be returned if the request for       **
**                                  transceiver mode change to stop mode      **
**                                  has been accepted.                        **
**                        E_NOT_OK: Will be returned if the request for       **
**                                  transceiver mode change to stop mode      **
**                                  has not been completed.                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_ArisuCan_IntChangeStopMode                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00357 CanTrcv_SAD_HWM_00001 SRS_HWM_00001 */
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_ChangeStopMode(void)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(ArisuCan_CanConfigType, AUTOMATIC) canTrcvConfigure;
  P2CONST(ArisuCan_CanConfigType, AUTOMATIC, CANTRCV_CONST) ptrCanCfgInit;
  P2CONST(ArisuCan_CanConfigType, AUTOMATIC, CANTRCV_CONST) ptrCanCfgStop;

  /* Initialize local variables */
  ptrCanCfgInit = &CanTrcv_ArisuCan[ARISUCAN_SBCMODE_INIT];
  ptrCanCfgStop = &CanTrcv_ArisuCan[ARISUCAN_SBCMODE_STOP];

  /* @Trace: CanTrcv_SUD_API_272 */
  /* Check wheater Configure or UnConfigure */
  if (CanTrcv_ArisuChannelUsed.ArisuCan0Used == ARISUCAN_CONFIGURE)
  {
    canTrcvConfigure.ArisuCan0Mode = ptrCanCfgStop->ArisuCan0Mode;
  }
  else
  {
    canTrcvConfigure.ArisuCan0Mode = ptrCanCfgInit->ArisuCan0Mode;
  }

  if (CanTrcv_ArisuChannelUsed.ArisuCan1Used == ARISUCAN_CONFIGURE)
  {
    canTrcvConfigure.ArisuCan1Mode = ptrCanCfgStop->ArisuCan1Mode;
  }
  else
  {
    canTrcvConfigure.ArisuCan1Mode = ptrCanCfgInit->ArisuCan1Mode;
  }

  if (CanTrcv_ArisuChannelUsed.ArisuCan2Used == ARISUCAN_CONFIGURE)
  {
    canTrcvConfigure.ArisuCan2Mode = ptrCanCfgStop->ArisuCan2Mode;
  }
  else
  {
    canTrcvConfigure.ArisuCan2Mode = ptrCanCfgInit->ArisuCan2Mode;
  }

  if (CanTrcv_ArisuChannelUsed.ArisuCan3Used == ARISUCAN_CONFIGURE)
  {
    canTrcvConfigure.ArisuCan3Mode = ptrCanCfgStop->ArisuCan3Mode;
  }
  else
  {
    canTrcvConfigure.ArisuCan3Mode = ptrCanCfgInit->ArisuCan3Mode;
  }

  /* @Trace: CanTrcv_SUD_API_270 */
  /* Invoke internal function to change ArisuCan to Stop mode */
  returnValue = CanTrcv_ArisuCan_IntChangeStopMode(canTrcvConfigure);

  return returnValue;
}

/*******************************************************************************
** Function Name        : CanTrcv_ArisuCan_VbsenseEnable                      **
**                                                                            **
** Service ID           : 0x16                                                **
**                                                                            **
** Description          : This service will enable Vbsense.                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK:     Will be returned if the Vbsense Enable Bit**
**                                  of ARISU-CAN is set ‘1’.                  **
**                        E_NOT_OK: Will be returned if the Vbsense Enable Bit**
**                                  of ARISU-CAN is set ‘0’.                  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked :                               **
**                        CanTrcv_ArisuCan_IntVbsenseEnable                   **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00357 SRS_HWM_00006 */
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_VbsenseEnable(void)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* @Trace: CanTrcv_SUD_API_279 */
  returnValue = CanTrcv_ArisuCan_IntVbsenseEnable();

  return returnValue;
}

/*******************************************************************************
** Function Name        : CanTrcv_ArisuCan_VbsenseDisable                     **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : This service will disable Vbsense.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK:     Will be returned if the Vbsense Enable Bit**
**                                  of ARISU-CAN is set ‘0’.                  **
**                        E_NOT_OK: Will be returned if the Vbsense Enable Bit**
**                                  of ARISU-CAN is set ‘1’.                  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked :                               **
**                        CanTrcv_ArisuCan_IntVbsenseDisable                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00357 SRS_HWM_00006 */
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_VbsenseDisable(void)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* @Trace: CanTrcv_SUD_API_280 */
  returnValue = CanTrcv_ArisuCan_IntVbsenseDisable();

  return returnValue;
}

/*******************************************************************************
** Function Name        : CanTrcv_ArisuCan_SetMode                            **
**                                                                            **
** Service ID           : 0x18                                                **
**                                                                            **
** Description          : This service will set SBC mode of Arisu-CAN.        **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
** Input Parameters     : mode - This parameter contains the desired          **
**                               operating mode.                              **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK:     Will be returned if the request for       **
**                                  transceiver mode change has been accepted.**
**                        E_NOT_OK: Will be returned if the request for       **
**                                  transceiver mode change has not been      **
**                                  accepted or any parameter is out of the   **
**                                  allowed range.                            **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked :                               **
**                        CanTrcv_IntArisuCan_SetMode                         **
**                                                                            **
*******************************************************************************/
/* @Trace: CanTrcv_SAD_HWM_00001 CanTrcv_SAD_HWM_00004 SRS_BSW_00357 SRS_HWM_00001 SRS_HWM_00004 */
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_SetMode(
  VAR(ArisuCan_SBCModeType, AUTOMATIC) mode)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* @Trace: CanTrcv_SUD_API_281 */
  returnValue = CanTrcv_IntArisuCan_SetMode(mode);

  return returnValue;
}

/*******************************************************************************
** Function Name        : CanTrcv_ArisuCan_RequestCanMode                     **
**                                                                            **
** Service ID           : 0x19                                                **
**                                                                            **
** Description          : This service will request SBC mode of Arisu-CAN.    **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : canTrcv - This parameter contains H/W Specific name.**
**                        mode    - This parameter contains the desired       **
**                                  operating mode.                           **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_IntArisuCan_RequestCanMode                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_HWM_00004  */
FUNC(void, CANTRCV_CODE) CanTrcv_ArisuCan_RequestCanMode(
  VAR(CanTrcv_HwType, AUTOMATIC) canTrcv,
  VAR(ArisuCan_SBCModeType, AUTOMATIC) mode)
{
  /* @Trace: CanTrcv_SUD_API_292 */
  /* Invoke internal function to request ArisuCan mode */
  (void)CanTrcv_IntArisuCan_RequestCanMode(canTrcv, mode);
}
#endif /* ((STD_ON == CANTRCV_ARISUCAN_SUPPORTED) && \
  (STD_ON == CANTRCV_SPI_SUPPORTED)) */

/*******************************************************************************
** Function Name        : CanTrcv_Init_Channel                                **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This service sets the CAN Transceiver Driver mode   **
**                        to either Normal or StandBy or Sleep Mode based on  **
**                        the configured initialization state.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr - Pointer to driver configuration.        **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanTrcv_CanTrcvNetwork,       **
**                        CanTrcv_ArisuCan, CanTrcv_ArisuCanSts,              **
**                        CanTrcv_ArisuChannelUsed, CanTrcv_InitStatus        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_IntInitialize, CanTrcv_IntGetPorFlag,       **
**                        CanTrcv_IntClearPorFlag, CanTrcv_SetNormalMode,     **
**                        CanTrcv_SetStandbyMode, CanTrcv_SetSleepMode,       **
**                        CanTrcv_ArisuCan_Init, EcuM_SetWakeupEvent,         **
**                        Det_ReportRuntimeError                              **
*******************************************************************************/
FUNC(void, CANTRCV_CODE) CanTrcv_Init_Channel(
  VAR(uint8, AUTOMATIC) CanTrcvChannel)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) initOpMode;

  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED))
  #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
  #if (STD_ON == CANTRCV_HW_POR_SUPPORTED)
  VAR(boolean, AUTOMATIC) porFlag;
  #endif /* (STD_ON == CANTRCV_HW_POR_SUPPORTED) */
  VAR(uint8, AUTOMATIC) pnIndex;
  VAR(boolean, AUTOMATIC) syserrFlag;
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  #endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) */

  /* Get the pointer to the structure of first network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[CanTrcvChannel];

  /* @Trace: CanTrcv_SUD_API_001 */
  #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
  /* Initialize check wake flag indication */
  CanTrcv_CheckWakeFlagIndication[CanTrcvChannel] = CANTRCV_FALSE;
  #endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */
  #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
  /* Initialize wake up reason as not support */
  CanTrcv_WakeUpReason[CanTrcvChannel] = CANTRCV_WU_NOT_SUPPORTED;
  /* Clear wake up pending */
  CanTrcv_WakeupPending[CanTrcvChannel] = CANTRCV_WAKEUP_NO_PENDING;
  /* Initialize wake up status as enable */
  CanTrcv_WakeupMode[CanTrcvChannel] = CANTRCV_WUMODE_ENABLE;
  /* Initialize wakeup status on Can Transceiver */
  CanTrcv_WakeupFlagIndication[CanTrcvChannel] =
    CANTRCV_WAKE_UP_NOT_OCCURRED;
  /* Check channel has configure wake up support or not */
  if (CANTRCV_FALSE != ptrCanTrcvNetwork->WakeupByBusUsed)
  {
    /* Check validate wake up */
    CanTrcv_IntCheckWakeupInit(CanTrcvChannel);
  }
  else
  {
    /* Nothing to do */
  }
  #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED))
  /* Initialize XJA11XX/TLE9255/TCAN1145 device */
  (void)CanTrcv_IntInitializeBySpi(CanTrcvChannel);

  #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
  /* Get PN Network index */
  pnIndex = ptrCanTrcvNetwork->PnNetworkIndex;
  /* Check channel has use partial networking */
  if (CANTRCV_INVALID_PNINDEX != pnIndex)
  {
    /* @Trace: CanTrcv_SUD_API_003 */
    #if (STD_ON == CANTRCV_HW_POR_SUPPORTED)
    /* Initialize POR flag */
    porFlag = CANTRCV_FALSE;
    /* polyspace -begin RTE:IDP [Justified:Low] "The size of CanTrcv_PartialNetwork is pre-defined, the value of pnIndex is already guaranteed by generator" */
    /* polyspace -begin MISRA-C3:18.1 [Justified:Low] "The value of  pnIndex is checked by generator.
      * Therefore, it will never exceed the size of CanTrcv_PartialNetwork which is pre-defined." */
    /* polyspace -begin MISRA-C3:D4.1 [Justified:Low] "The value of  pnIndex is checked by generator.
      * Therefore, it will never exceed the size of CanTrcv_PartialNetwork which is pre-defined." */
    /* polyspace +5 MISRA-C3:18.1 [Justified:Low] "The size of CanTrcv_PartialNetwork  is pre-defined, the value of pnIndex is guaranteed by generator" */
    /* polyspace +4 MISRA-C3:D4.1 [Justified:Low] "The size of CanTrcv_PartialNetwork  is pre-defined,
      * the value of pnIndex is guaranteed by generator." */
    /* polyspace +2 RTE:IDP [Justified:Low] "The size of CanTrcv_PartialNetwork  is pre-defined,
      * the value of pnIndex is guaranteed by generator" */
    if (CANTRCV_FALSE != CanTrcv_PartialNetwork[pnIndex].PowerOnFlag)
    {
      /* Get POR status */
      returnStatus = CanTrcv_IntGetPorFlag(CanTrcvChannel, &porFlag);
      if ((E_NOT_OK != returnStatus) && (CANTRCV_FALSE != porFlag))
      {
        /* @Trace: CanTrcv_SUD_API_004 */
        #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
        /* Set wake up reason */
        CanTrcv_WakeUpReason[CanTrcvChannel] = CANTRCV_WU_POWER_ON;
        #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
        /* If the POR flag is set, wakeup shall be reported to EcuM
          through API EcuM_SetWakeupEvent */
        #if(STD_ON == CANTRCV_HW_PN_SUPPORTED)
        EcuM_SetWakeupEvent(ptrCanTrcvNetwork->PorWakeupSource);
        /* Clear POR flag */
        (void)CanTrcv_IntClearPorFlag(CanTrcvChannel);
        #endif
      }
      else
      {
        /* Nothing to do */
      }
    }
    /* polyspace -end RTE:IDP [Justified:Low] "The size of CanTrcv_PartialNetwork is pre-defined, the value of pnIndex is already guaranteed by generator" */
    /* polyspace -end MISRA-C3:D4.1 [Justified:Low] "The value of  pnIndex is checked by generator.
      * Therefore, it will never exceed the size of CanTrcv_PartialNetwork which is pre-defined." */
    /* polyspace -end MISRA-C3:18.1 [Justified:Low] "The value of  pnIndex is checked by generator.
      * Therefore, it will never exceed the size of CanTrcv_PartialNetwork which is pre-defined." */
    else
    {
      /* Nothing to do */
    }
    #endif /* (STD_ON == CANTRCV_HW_POR_SUPPORTED) */

    /* Initialize SYSERR flag */
    syserrFlag = CANTRCV_FALSE;
    /* Get SYSERR status */
    #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
      (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
      (STD_ON == CANTRCV_TCAN1145_SUPPORTED))
    returnStatus = CanTrcv_IntGetSyserrFlag(CanTrcvChannel, &syserrFlag);
    #else
    returnStatus = CanTrcv_IntGetSyserrFlag();
    #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
      (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
      (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) */
    if ((E_NOT_OK != returnStatus) && (CANTRCV_FALSE != syserrFlag))
    {
      #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
      /* Set wake up reason */
      CanTrcv_WakeUpReason[CanTrcvChannel] = CANTRCV_WU_BY_SYSERR;
      #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
      /* If the SYSERR flag is set, wakeup shall be reported to EcuM
        through API EcuM_SetWakeupEvent */
      EcuM_SetWakeupEvent(ptrCanTrcvNetwork->SyserrWakeupSource);
      #if((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || (STD_ON == CANTRCV_TCAN1145_SUPPORTED))
      /* Clear SYSERR flag */
      (void)CanTrcv_IntClearSyserrFlag(CanTrcvChannel);
      #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) */
    }
    else
    {
      /* Nothing to do */
    }
    /* @Trace: CanTrcv_SUD_API_005 */
    #if (STD_ON == CANTRCV_HW_POR_SUPPORTED)
    if ((CANTRCV_FALSE != syserrFlag) ||
      (CANTRCV_UNINITIALIZED == CanTrcv_InitStatus) ||
      (CANTRCV_FALSE != porFlag))
    #else
    if ((CANTRCV_FALSE != syserrFlag) ||
      (CANTRCV_UNINITIALIZED == CanTrcv_InitStatus))
    #endif /* (STD_ON == CANTRCV_HW_POR_SUPPORTED) */
    {
      /* If the POR flag or SYSERR flag is set, transceiver shall be
        re-configured for selective wake-up functionality by running the
        configuration sequence */
      /* Invoke internal function to initialize Can Transceiver */
      (void)CanTrcv_IntInitializePN(CanTrcvChannel);
    }
    else
    {
      /* If the POR flag or SYSERR flag is not set, the configuration
        stored in the transceiver memory will be still valid and
        re-configuration is not necessary. */
    }
  }
  else
  {
    /* Nothing to do */
  }
  #endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */
  #endif/* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) */

  /* Copy the configured init state of Transceiver to Local variable */
  initOpMode = ptrCanTrcvNetwork->InitState;
  /* Set init opmode for channel */
  CanTrcv_InitOpMode_Channel(CanTrcvChannel, initOpMode);
}

/*******************************************************************************
** Function Name        : CanTrcv_InitOpMode_Channel                          **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This service sets the CAN Transceiver Driver mode   **
**                        to either Normal or StandBy or Sleep Mode based on  **
**                        the configured initialization state.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr - Pointer to driver configuration.        **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanTrcv_ByteArray             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_SetNormalMode, CanTrcv_SetSleepMode,        **
**                        CanTrcv_SetStandbyMode                              **
*******************************************************************************/
FUNC(void, CANTRCV_CODE) CanTrcv_InitOpMode_Channel(
  VAR(uint8, AUTOMATIC) CanTrcvChannel,
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) initOpMode)
{
  /* Check whether initOpMode is standby */
  /* @Trace: CanTrcv_SUD_API_006 */
  #if (STD_OFF == CANTRCV_CHANNELS_INIT_MODE_ALL_STANDBY)
  switch (initOpMode)
  {
    #if (STD_ON == CANTRCV_CHANNELS_INIT_MODE_NORMAL)
    case CANTRCV_TRCVMODE_NORMAL:
      /* Invoke the function to set the CAN Transceiver Driver to Normal
        Mode */
      (void)CanTrcv_SetNormalMode(CanTrcvChannel);
      break;
    #endif /* (STD_ON == CANTRCV_CHANNELS_INIT_MODE_NORMAL) */
    #if (STD_ON == CANTRCV_CHANNELS_INIT_MODE_SLEEP)
    case CANTRCV_TRCVMODE_SLEEP:
      /* Invoke the function to set the CAN Transceiver Driver to Sleep
        Mode */
      (void)CanTrcv_SetSleepMode(CanTrcvChannel);
      break;
    #endif /* (STD_ON == CANTRCV_CHANNELS_INIT_MODE_SLEEP) */
    default: /* CANTRCV_TRCVMODE_STANDBY */
      /* Invoke the function to set the CAN Transceiver Driver to Standby
        Mode */
      (void)CanTrcv_SetStandbyMode(CanTrcvChannel);
      break;
  }
  #else
  (void)CanTrcv_SetStandbyMode(CanTrcvChannel);
  #endif /* (STD_OFF == CANTRCV_CHANNELS_INIT_MODE_ALL_STANDBY) */
  /* Set the Operational Mode of the requested network */
  CanTrcv_ByteArray[CanTrcvChannel] = initOpMode;
  CanTrcv_ClearWufFlag[CanTrcvChannel] = CANTRCV_FALSE;
}

/*******************************************************************************
** Function Name        : CanTrcv_SetOpMode_Processing                        **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : Sets the mode of the Transceiver to the value       **
**                        OpMode.                                             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant for different transceivers                **
**                                                                            **
** Input Parameters     : Transceiver - CAN transceiver to which API call has **
**                                      to be applied.                        **
**                        OpMode      - This parameter contains the desired   **
**                                      operating mode.                       **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK:     Will be returned if the request for       **
**                                  transceiver mode change has been accepted.**
**                        E_NOT_OK: will be returned if the request for       **
**                                  transceiver mode change has not been      **
**                                  accepted or any parameter is out of the   **
**                                  allowed range.                            **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  : CanTrcv_InitStatus,           **
**                        CanTrcv_CanTrcvNetwork, CanTrcv_ByteArray           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, Det_ReportRuntimeError,            **
**                        CanTrcv_SetNormalMode, CanTrcv_IntGetPorFlag,       **
**                        CanTrcv_SetStandbyMode, CanTrcv_SetSleepMode,       **
**                        CanIf_TrcvModeIndication,                           **
**                        CanIf_ConfirmPnAvailability                         **
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetOpMode_Processing(
  VAR(uint8, AUTOMATIC) Transceiver,
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) OpMode)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED))
  VAR(boolean, AUTOMATIC) syserrFlag;
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) */
  #if (STD_ON == CANTRCV_HW_POR_SUPPORTED)
  VAR(uint8, AUTOMATIC) pnIndex;
  P2CONST(CanTrcv_PartialNetworkType, AUTOMATIC, CANTRCV_CONST)
    ptrCanTrcvPnNetwork;
  VAR(boolean, AUTOMATIC) porFlag;
  #endif /* (STD_ON == CANTRCV_HW_POR_SUPPORTED) */
  #endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[Transceiver];

  #if ((STD_ON == CANTRCV_HW_PN_SUPPORTED) && \
    (STD_ON == CANTRCV_HW_POR_SUPPORTED))
  /* Initialize POR flag */
  porFlag = CANTRCV_FALSE;

  /* Get Cantrcv PN Network index */
  pnIndex = ptrCanTrcvNetwork->PnNetworkIndex;
  if (CANTRCV_INVALID_PNINDEX != pnIndex)
  {
    /* polyspace -begin RTE:IDP [Justified:Low] "The size of CanTrcv_PartialNetwork is pre-defined, the value of pnIndex is already guaranteed by generator" */
    /* polyspace -begin MISRA-C3:18.1 [Justified:Low] "The value of  pnIndex is checked by generator.
      * Therefore, it will never exceed the size of CanTrcv_PartialNetwork which is pre-defined." */
    /* polyspace -begin MISRA-C3:D4.1 [Justified:Low] "The value of  pnIndex is checked by generator.
      * Therefore, it will never exceed the size of CanTrcv_PartialNetwork which is pre-defined." */
    /* Get the pointer to the structure of the requested PN network */
    ptrCanTrcvPnNetwork = &CanTrcv_PartialNetwork[pnIndex];

    /* Check POR is available on transceiver */
    /* polyspace +6 MISRA-C3:18.1 [Justified:Low] "The size of CanTrcv_PartialNetwork  is pre-defined, the value of pnIndex is guaranteed by generator.
      * So, ptrCanTrcvPnNetwork is valid in this case." */
    /* polyspace +4 MISRA-C3:D4.1 [Justified:Low] "The size of CanTrcv_PartialNetwork  is pre-defined, the value of pnIndex is guaranteed by generator.
      * So, ptrCanTrcvPnNetwork is valid in this case." */
    /* polyspace +2 RTE:IDP [Justified:Low] "The size of CanTrcv_PartialNetwork  is pre-defined, the value of pnIndex is guaranteed by generator.
      * So, ptrCanTrcvPnNetwork is valid in this case." */
    if (CANTRCV_TRUE == ptrCanTrcvPnNetwork->PowerOnFlag)
    {
      /* @Trace: CanTrcv_SUD_API_033 */
      /* Get POR status */
      returnValue = CanTrcv_IntGetPorFlag(Transceiver, &porFlag);
      /* Check POR status */
      if ((E_NOT_OK != returnValue) && (CANTRCV_FALSE != porFlag))
      {
        /* If the POR flag is set, transceiver shall be re-initialized to
          run the transceiver configuration sequence. */
        (void)CanTrcv_IntInitializeBySpi(Transceiver);
        /* Configure partial networking */
        (void)CanTrcv_IntInitializePN(Transceiver);
        /* Clear POR flag */
        (void)CanTrcv_IntClearPorFlag(Transceiver);
      }
      else
      {
        /* Nothing to do */
      }
    }
    /* polyspace -end RTE:IDP [Justified:Low] "The size of CanTrcv_PartialNetwork is pre-defined, the value of pnIndex is already guaranteed by generator" */
    /* polyspace -end MISRA-C3:D4.1 [Justified:Low] "The value of  pnIndex is checked by generator.
      * Therefore, it will never exceed the size of CanTrcv_PartialNetwork which is pre-defined." */
    /* polyspace -end MISRA-C3:18.1 [Justified:Low] "The value of  pnIndex is checked by generator.
      * Therefore, it will never exceed the size of CanTrcv_PartialNetwork which is pre-defined." */
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }
  #endif /* #if ((STD_ON == CANTRCV_HW_PN_SUPPORTED) && \
    (STD_ON == CANTRCV_HW_POR_SUPPORTED)) */

  if ((CanTrcv_TrcvModeType)CANTRCV_TRCVMODE_NORMAL == OpMode)
  {
    /* @Trace: CanTrcv_SUD_API_034 */
    /* Invoke the CanTrcv_SetNormalMode to set the Normal Mode */
    returnValue = CanTrcv_SetNormalMode(Transceiver);

    #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
    if ((E_NOT_OK != returnValue) &&
      (CANTRCV_INVALID_PNINDEX != ptrCanTrcvNetwork->PnNetworkIndex))
    {
      /* @Trace: CanTrcv_SUD_API_035 */
      #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
        (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
        (STD_ON == CANTRCV_TCAN1145_SUPPORTED))
      /* Initialize SYSERR flag */
      syserrFlag = CANTRCV_FALSE;
      /* Get SYSERR status */
      returnValue = CanTrcv_IntGetSyserrFlag(Transceiver, &syserrFlag);
      #else
      returnValue = CanTrcv_IntGetSyserrFlag();
      #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
        (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
        (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) */
      /* Check SYSERR status */
      /* polyspace +1 DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanTrcv. No impact" */
      #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
        (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
        (STD_ON == CANTRCV_TCAN1145_SUPPORTED))
      if ((E_NOT_OK != returnValue) && (CANTRCV_FALSE == syserrFlag))
      {
        /* If the SYSERR flag is NOT set and the requested mode is
          CANTRCV_NORMAL transceiver shall informs CanNm that selective
          wakeup is enabled. */
        CanIf_ConfirmPnAvailability(Transceiver);
      }
      else
      {
        /* Nothing to do */
      }
      #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
        (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
        (STD_ON == CANTRCV_TCAN1145_SUPPORTED))*/
    }
    else
    {
      /* Nothing to do */
    }
    #endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */
  }
  else if ((CanTrcv_TrcvModeType)CANTRCV_TRCVMODE_STANDBY == OpMode)
  {
    /* polyspace +2 DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanTrcv. No impact" */
    #if (STD_ON == CANTRCV_SLEEP_MODE_USED)
    if (CANTRCV_SLEEPMODE_UNUSED == ptrCanTrcvNetwork->SleepModeUsed)
    #endif /* (STD_ON == CANTRCV_SLEEP_MODE_USED) */
    {
      /* @Trace: CanTrcv_SUD_API_036 */
      /* Invoke the CanTrcv_SetStandbyMode to set the Standby Mode */
      returnValue = CanTrcv_SetStandbyMode(Transceiver);
    }
    #if (STD_ON == CANTRCV_SLEEP_MODE_USED)
    else
    {
      /* @Trace: CanTrcv_SUD_API_037 */
      /* Invoke the CanTrcv_SetSleepMode to set Sleep mode */
      returnValue = CanTrcv_SetSleepMode(Transceiver);
    }
    #endif /* (STD_ON == CANTRCV_SLEEP_MODE_USED) */
  }
  else /* @ (CANTRCV_TRCVMODE_SLEEP == OpMode) */
  {
    /* @Trace: CanTrcv_SUD_API_038 */
    /* Invoke the CanTrcv_SetSleepMode to set Sleep mode */
    returnValue = CanTrcv_SetSleepMode(Transceiver);
  }

  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_039 */
    /* Indicate mode change to CanIf */
    (void)CanIf_TrcvModeIndication(Transceiver, OpMode);
    /* Set the Operational Mode of the requested network */
    CanTrcv_ByteArray[Transceiver] = OpMode;
  }
  else
  {
    /* Nothing to do */
  }
  CANTRCV_UNUSED_VAL(ptrCanTrcvNetwork);
  return(returnValue);
}

#define CANTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
