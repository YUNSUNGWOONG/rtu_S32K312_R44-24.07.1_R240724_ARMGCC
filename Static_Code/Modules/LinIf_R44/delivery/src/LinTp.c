/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
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
**  SRC-MODULE: LinTp.c                                                       **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : Provision of LinTP APIs                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By               Description                      **
********************************************************************************
** 1.0.10     07-Mar-2023   KhaLN1           #CP44-1811                       **
** 1.0.6      17-Oct-2022   KhaLN1           #CP44-563                        **
** 1.0.5      03-Aug-2022   KhaLN1           #CP44-513                        **
** 1.0.3      25-Apr-2022   DuyNHP2          R44-Redmine #26480               **
** 1.0.3      17-Sep-2021   DuyNGB           R44-Redmine #20121               **
** 1.0.1      20-Apr-2021   LongTQB          R44-Redmine #17195               **
** 1.0.0      22-Dec-2020   SJ Kim           Initial version                  **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "LinIf_Cfg.h"
#if(LINTP_SUPPORT == STD_ON)
#include "LinTp_PCTypes.h"            /* LinTp pre compile header file */
#include "LinTp.h"                    /* LIN TP Header File */
#include "LinIf_SubProcess.h"         /* LinIf RAM header */
#include "LinIf_Ram.h"                /* LinIf RAM header */
#include "LinTp_Ram.h"                /* LinTp RAM header */
#include "LinTp_Rx.h"                 /* LinTp Rx Internal Header */
#include "SchM_LinIf.h"               /* Schedule Manager header */
#if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
#include "BswM_LinTp.h"               /* BswM callback header for LinTp */
#endif
#if (LINIF_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                      /* DET header */
#endif
#include "PduR_LinTp.h"               /* PduR callback header for LinTp */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name      : LinTp_Init                                            **
**                                                                            **
** Service ID         : 0x40                                                  **
**                                                                            **
** Description        : This service initializes the LIN Transport Layer. Each**
**                      LIN TP channel state will be set to LINTP_CHANNEL_IDLE**
**                      after successful completion of this API.              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *ConfigPtr                                            **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : Lin Interface should be initialized.                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinTp_GblInitSts, LinIf_GblInitSts, LinTp_GpDbTocPtr  **
**                      LinTp_GpFirstChannel,LinTp_GpFirstTxMsg,              **
**                      LinTp_GpFirstRxMsg                                    **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError()                                     **
*******************************************************************************/
/* @Trace: SWS_LinIf_00350 SWS_LinIf_00427 SWS_LinIf_00320 SWS_LinIf_00681
 * SRS_BSW_00101 SRS_BSW_00414 SRS_BSW_00416 SRS_BSW_00358 SRS_Lin_01540
 * SRS_BSW_00171 SRS_Lin_01534 SRS_Lin_01574 SRS_Lin_01579 SRS_Lin_01593
 * SRS_Lin_01594 SRS_BSW_00167
 */
#if (LINTP_SUPPORT == STD_ON)
#define LINTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTP_CODE) LinTp_Init
  (P2CONST(LinTp_ConfigType, AUTOMATIC, LINTP_APPL_CONST) ConfigPtr)
{
  /* @Trace: SWS_LinIf_00350*/
  /* @Trace: LinIf_SUD_API_426*/
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData;
  uint8_least LucTpChannelCount;

  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  /* Check if the LINIF module is not initialized */
  if(LinIf_GblInitSts == LINIF_UNINIT)
  {
    /* @Trace: SWS_LinIf_00376*/
    /* @Trace: LinIf_SUD_API_427*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINTP_INIT_SID, LINIF_E_UNINIT);
  }
  /* Check if the LinTp module is initialized */
  if(LinTp_GblInitSts == LINTP_INIT)
  {
    /* @Trace: SWS_LinIf_00376*/
    /* @Trace: LinIf_SUD_API_428*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINTP_INIT_SID, LINIF_E_ALREADY_INITIALIZED);
  }
  else
  #endif /*#if(LINIF_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: SWS_LinIf_00450*/
    /* @Trace: LinIf_SUD_API_429*/
    /* Copy the first channel pointer to a global pointer */
    LinTp_GpFirstChannel = &LinTp_GaaChannelInfo[LINIF_ZERO];
    /* Get the number of TP channels into local variable */
    LucTpChannelCount = LinIf_Tp_Channels;
    /* Get the address of first TP channel RAM data into local pointer */
    LpTpChannelRamData = LinTp_GpFirstChannel->pLinTpChannelRamData;

    do
    {
      /* @Trace: SWS_LinIf_00321*/
      /* @Trace: LinIf_SUD_API_430*/
      /* Change the TP channel state to IDLE */
      LpTpChannelRamData->ucLinTpStatus = LINTP_CHANNEL_IDLE;
      /* Reset the response pending frame counter */
      LpTpChannelRamData->usRespPendingFrameCounter = LINIF_ZERO;
      /* Reset the P2 Timer Counter */
      LpTpChannelRamData->usP2TimerCounter = LINIF_ZERO;
      /* Clear the P2 timer load flag */
      LpTpChannelRamData->blP2TimerInitialLoad = LINIF_FALSE;
      /* Set the first frame to true */
      LpTpChannelRamData->blFirstFrame = LINIF_TRUE;
      /* Set buffer availability to TRUE */
      LpTpChannelRamData->blAvblBuff = LINIF_TRUE;
      /* Set the requested frame id to zero */
      LpTpChannelRamData->ddMRFSduId = LINIF_ZERO;

      LpTpChannelRamData++;
      LucTpChannelCount--;

    }while(LucTpChannelCount != LINIF_ZERO);

    /* @Trace: SWS_LinIf_00710*/
    /* @Trace: LinIf_SUD_API_431*/
    /* Update the LIN TP status to initialized */
    LinTp_GblInitSts = LINTP_INIT;
  }

  /* @Trace: LinIf_SUD_API_432*/
  /* To avoid compilation waarning */
  /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_LinTp_Transmit" */
  LINIF_UNUSED_PTR(ConfigPtr);
  /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_LinTp_Transmit" */
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : LinTp_GetVersionInfo                                  **
**                                                                            **
** Service ID         : 0x42                                                  **
**                                                                            **
** Description        : This service returns the version information of LinIf **
**                      module.                                               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : *versioninfo                                          **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      None                                                  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError()                                     **
*******************************************************************************/
/* @Trace: SWS_LinIf_00352 SWS_LinIf_00639 SRS_BSW_00407 SRS_BSW_00167 */
#if ((LINTP_VERSION_INFO_API == STD_ON) && (LINTP_SUPPORT == STD_ON))
#define LINTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinTp_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, LINTP_APPL_DATA) versioninfo)
{
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  /* check if versioninfo pointer is equal to Null */
  if(versioninfo == NULL_PTR)
  {
    /* @Trace: LinIf_SUD_API_433*/
    /* Report to DET  */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
      LINTP_GETVERSIONINFO_SID, LINIF_E_PARAM_POINTER);
  }
  else
  #endif /*#if(LINIF_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: LinIf_SUD_API_434*/
    /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "The pointer has been checked NULL" */
    /* Copy the vendor Id */
    versioninfo->vendorID = LINIF_VENDOR_ID;
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "The pointer has been checked NULL" */
    /* Copy the module Id */
    versioninfo->moduleID = LINIF_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = LINIF_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = LINIF_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = LINIF_SW_PATCH_VERSION;
  }
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : LinTp_Shutdown                                        **
**                                                                            **
** Service ID         : 0x43                                                  **
**                                                                            **
** Description        : This service closes all pending transport protocol    **
**                      connection, frees all resources and sets the          **
**                      corresponding LinTp module into the LINTP_UNINIT      **
**                      state.                                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GblInitSts, LinTp_GpDbTocPtr,                   **
**                      LinTp_GpFirstChannel, LinTp_GblInitSts                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError()                                     **
*******************************************************************************/
/* @Trace: SWS_LinIf_00355 SWS_LinIf_00356 SWS_LinIf_00433 SWS_LinIf_00484
 * SWS_LinIf_00683 SRS_BSW_00336 SRS_BSW_00167
 */
#if(LINTP_SUPPORT == STD_ON)
#define LINTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinTp_Shutdown(void)
{
  /* @Trace: LinIf_SUD_API_435*/
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINTP_CONST) LpTpChannelPtr;
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamPtr;
  uint8_least LucTpChannelCount;

  #if(LINIF_DEV_ERROR_DETECT == STD_ON)
  /* Declare the error status flag */
  boolean LblErrFlag;
  /* Initialize the error status flag to false */
  LblErrFlag = LINIF_FALSE;
  /* Check if the LINIF module is not initialized */
  if(LinIf_GblInitSts == LINIF_UNINIT)
  {
    /* @Trace: LinIf_SUD_API_436*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
       LINTP_SHUTDOWN_SID, LINIF_E_UNINIT);
    /* Set the error status flag to true */
    LblErrFlag = LINIF_TRUE;
  }

  /* Check if the LinTp module is not initialized */
  else if(LinTp_GblInitSts == LINTP_UNINIT)
  {
    /* @Trace: LinIf_SUD_API_437*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
      LINTP_SHUTDOWN_SID, LINIF_E_UNINIT);
    /* Set the error status flag to true */
    LblErrFlag = LINIF_TRUE;
  }
  else
  {
    /* To avoid QAC warning */
  }

  /* Check whether any development error occurred */
  if(LblErrFlag != LINIF_TRUE)
  #endif
  {
    /* @Trace: LinIf_SUD_API_438*/
    /* Get the number of TP channels into local variable */
    LucTpChannelCount = LinIf_Tp_Channels;
    /* Copy the first channel pointer to a Local pointer */
    LpTpChannelPtr = LinTp_GpFirstChannel;
    /* Get the address of first TP channel RAM data into local pointer */
    /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
    LpTpChannelRamPtr = LpTpChannelPtr->pLinTpChannelRamData;
    /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
    do
    {
      /* @Trace: LinIf_SUD_API_439*/
      /* Change the TP channel state to UNINIT*/
      /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
      LpTpChannelRamPtr->ucLinTpStatus = LINTP_UNINIT;
      /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */

      LpTpChannelRamPtr++;
      LucTpChannelCount--;
    }while(LucTpChannelCount != LINIF_ZERO);
    /* @Trace: LinIf_SUD_API_440*/
    /* Update the LIN TP status to initialized */
    LinTp_GblInitSts = LINTP_UNINIT;
  }/* No development errors occurred */
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : LinTp_Transmit                                        **
**                                                                            **
** Service ID         : 0x41                                                  **
**                                                                            **
** Description        : This service is used to request the transfer of       **
**                      segmented data over the LIN bus.                      **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : LinTpTxSduId, *LinTpTxInfoPtr                         **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinTp_GpFirstTxMsg, LinTp_GpFirstChannel              **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_LinIf_STATUS_PROTECTION,                   **
**                      (), SchM_Exit_LinIf_STATUS_PROTECTION(),              **
**                      PduR_LinTpTxConfirmation(), PduR_LinTpRxIndication(), **
**                      LinIf_SwitchScheduleMode(), LinTp_TransmitDetCheck    **
*******************************************************************************/
/* @Trace: SWS_LinIf_00351 SWS_LinIf_00326 SWS_LinIf_00413 SWS_LinIf_00422
 * SWS_LinIf_00584 SWS_LinIf_00616 SWS_LinIf_00586 SWS_LinIf_00702
 * SWS_LinIf_00574 SWS_LinIf_00576 SWS_LinIf_00682 SRS_Lin_01544
 * SRS_Lin_01592 SRS_BSW_00167
 */
#if (LINTP_SUPPORT == STD_ON)
#define LINTP_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinTp_Transmit(PduIdType TxPduId,
P2CONST(PduInfoType, AUTOMATIC, LINTP_APPL_CONST) PduInfoPtr)
{
  /* @Trace: LinIf_SUD_API_441*/
  P2CONST(LinTp_TxMsg, AUTOMATIC, LINTP_CONST) LpTpMsgPtr;
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINTP_CONST) LpTpChannelPtr;
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamPtr;
  Std_ReturnType LddReturnValue;
  uint16 LusByteCounter;
  uint8 LucByte;

  #if (LINIF_DEV_ERROR_DETECT == STD_OFF)
  LddReturnValue = E_OK;
  #else /*(LINIF_DEV_ERROR_DETECT == STD_ON)*/
  /* Check for Det errors */
  LddReturnValue = LinTp_TransmitDetCheck(TxPduId, PduInfoPtr);
  /* Check if no development errors occurred */
  if(LddReturnValue == E_OK)
  #endif
  {
    /* @Trace: LinIf_SUD_API_442*/
    /* Get pointer to Rx Msg structure */
    LpTpMsgPtr = &(LinTp_GaaTxMsg[TxPduId]);
    /* Get the channel pointer */
    LpTpChannelPtr = &(LinTp_GpFirstChannel[LpTpMsgPtr->ucTpTxChannelIndex]);
    /* Get the address of first TP channel RAM data into local pointer */
    /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
    LpTpChannelRamPtr = LpTpChannelPtr->pLinTpChannelRamData;
    /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */

    /* Check if the request is functional and channel status is not idle */
    if((LINTP_FUNCTIONAL_NAD == LpTpMsgPtr->ucTpNad) && (LpTpChannelRamPtr->ucLinTpStatus != LINTP_CHANNEL_IDLE))
    {
      /* @Trace: LinIf_SUD_API_444*/
      /* Enter protection area */
      SchM_Enter_LinIf_STATUS_PROTECTION();
      /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
      switch(LpTpChannelRamPtr->ucLinTpStatus)
      /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
      {
        /* Check if there is an ongoing transmission */
        case LINTP_TX_BUSY_BUFF_RDY:
        case LINTP_TX_BUSY_BUFF_NOT_RDY:
          /* @Trace: LinIf_SUD_API_445*/
          /* Invoke the upper layer confirmation callback with failure */
          PduR_LinTpTxConfirmation(LpTpMsgPtr->ddTpTxPduId,
          NTFRSLT_E_NOT_OK);
          /* Switch the mode to LINTP_APPLICATIVE_SCHEDULE */
          LinIf_SwitchScheduleMode(LpTpChannelPtr, LINTP_APPLICATIVE_SCHEDULE);
        break;
        /* Check if there is an ongoing reception */
        case LINTP_RX_BUSY_BUFF_RDY:
        case LINTP_RX_BUSY_BUFF_NOT_RDY:
          /* @Trace: LinIf_SUD_API_446*/
          /* Invoke Upper Layer Rx Indication with NTFRSLT_E_NOT_OK */
          PduR_LinTpRxIndication(LpTpMsgPtr->ddTpTxPduId,
          NTFRSLT_E_NOT_OK);
          LinIf_SwitchScheduleMode(LpTpChannelPtr, LINTP_APPLICATIVE_SCHEDULE);
        break;
        default:
        /* @Trace: LinIf_SUD_API_447*/
        /* LINTP_CHANNEL_IDLE */
        /* LINTP_TX_BUSY_BUFF_ERROR */
        break;
      }
      /* Exit protection area */
      SchM_Exit_LinIf_STATUS_PROTECTION();
    }

    /* Check if channel is idle or current request is functional */
    if((LpTpChannelRamPtr->ucLinTpStatus == LINTP_CHANNEL_IDLE) ||
      (LpTpMsgPtr->ucTpNad == LINTP_FUNCTIONAL_NAD))
    {
      /* Enter protection area */
      SchM_Enter_LinIf_STATUS_PROTECTION();
      /* @Trace: LinIf_SUD_API_448*/
      /* Update the Tp status */
      LpTpChannelRamPtr->ucLinTpStatus = LINTP_TX_BUSY_BUFF_NOT_RDY;
      /* Exit protection area */
      SchM_Exit_LinIf_STATUS_PROTECTION();
    }
    else
    {
      /* Set the return value */
      LddReturnValue = E_NOT_OK;
    }

    #if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
    /* Invoke BswM with requested schedule mode */
    if(LINTP_DIAG_SELECT ==
    ((LpTpChannelPtr->ucLinTpChannelStatus) & LINTP_DIAG_SELECT))
    {
      /* @Trace: LinIf_SUD_API_449*/
      /* Invoke BswM with requested schedule mode --LINIF641 */
      /* polyspace-begin RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
      BswM_LinTp_RequestMode(LinIf_GaaLtChannelInfo[LpTpChannelPtr->ucTpChannelIndex].
      ddComMNwHndlId, LINTP_DIAG_REQUEST);
      /* polyspace-end RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
    }
    #endif /* (LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON) */
    if((LpTpChannelRamPtr->ucLinTpStatus) == (LINTP_TX_BUSY_BUFF_NOT_RDY))
    {
      /* @Trace: LinIf_SUD_API_450*/
      /* Initialize frame counter */
      LpTpChannelRamPtr->ucTpFrameCounter = LINIF_ZERO;
      /* Update the active PduId */
      LpTpChannelRamPtr->ddActiveTpPduId = TxPduId;
      /* Update the byte counter with the received byte count */
      LpTpChannelRamPtr->usTpByteCounter = (uint16)PduInfoPtr->SduLength;
      /* Set Tp Header sent flag to false*/
      LpTpChannelRamPtr->blTpHeaderSent = LINIF_FALSE;
      /* Set the node Id in the buffer data */
      LpTpChannelRamPtr->aaLinTpBuffer[LINIF_ZERO] = LpTpMsgPtr->ucTpNad;
      /* Get the data length */
      LusByteCounter = LpTpChannelRamPtr->usTpByteCounter;
      /* Check if the data length fits in a single frame */
      if(LusByteCounter <= LINIF_EIGHT)
      {
        /* @Trace: LinIf_SUD_API_451*/
        /* Set the PCI byte for single frame (SF) */
        LpTpChannelRamPtr->aaLinTpBuffer[LINIF_ONE] = (uint8)LusByteCounter;
        /* Set the index for aaLinTpBuffer */
        LpTpChannelRamPtr->ucLocalTpData = LINIF_ZERO;
      }
      else
      {
        /* @Trace: LinIf_SUD_API_452*/
        /* Divide the length by 256 */
        LucByte = (uint8) (LusByteCounter >> LINTP_EIGHT);
        /* Set the PCI byte for first frame (FF) */
        LpTpChannelRamPtr->aaLinTpBuffer[LINIF_ONE] =
        (LINIF_FF_PCI | LucByte);
        /* Set the LEN field */
        LpTpChannelRamPtr->aaLinTpBuffer[LINIF_TWO] =
        (uint8) (LusByteCounter & LINIF_EIGHT_LEAST_MASK);
        /* Set the index for aaLinTpBuffer */
        LpTpChannelRamPtr->ucLocalTpData = LINIF_THREE;
      }
    }
  }
  /* @Trace: LinIf_SUD_API_453*/
  return(LddReturnValue);
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : LinTp_ChangeParameter                                 **
**                                                                            **
** Service ID         : 0x44                                                  **
**                                                                            **
** Description        : This function shall request changes in parameter.     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : LinTpTxSduId, LinTpParameterValue.                    **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      LinIf_GblInitSts, LinTp_GblInitSts, LinTp_GpDbTocPtr  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportError()                                     **
*******************************************************************************/
/* @Trace: SWS_LinIf_00501 SWS_LinIf_00592 SWS_LinIf_00578 SWS_LinIf_00685
 */
#if (LINTP_SUPPORT == STD_ON)
#define LINTP_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINIF_CODE) LinTp_ChangeParameter
  (PduIdType id, TPParameterType parameter, uint16 value)
{
  #if (LINIF_DEV_ERROR_DETECT == STD_ON)
  /* Check if the LINIF module is not initialized */
  if(LinIf_GblInitSts == LINIF_UNINIT)
  {
    /* @Trace: LinIf_SUD_API_454*/
    /* Report to DET */
    (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
      LINTP_CHANGEPARAMETER_SID, LINIF_E_UNINIT);
    /* Set the return value */
  }
  else
  {
    /* Check if the TP is not initialized */
    if(LinTp_GblInitSts == LINTP_UNINIT)
    {
      /* @Trace: LinIf_SUD_API_455*/
      /* Report to DET */
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINTP_CHANGEPARAMETER_SID, LINIF_E_UNINIT);
      /* Set the return value */
    }
    /* Check if the PduId is out of range */
    else if(id >= LinIf_Max_Rx_Sdu)
    {
      /* @Trace: LinIf_SUD_API_456*/
      /* Report to DET */
      (void)Det_ReportError(LINIF_MODULE_ID, LINIF_INSTANCE_ID,
        LINTP_CHANGEPARAMETER_SID, LINIF_E_PARAMETER);
    }
    else
    {
      /* To avoid QAC warning */
    }
  } /* if LinIf module is initialized */
  #else
  /* To avoid compilation waarning */
  LINIF_UNUSED(id);
  #endif
  /* @Trace: LinIf_SUD_API_457*/
  /* To avoid compilation waarning */
  LINIF_UNUSED(parameter);
  LINIF_UNUSED(value);
  /* return the value */
  return(E_NOT_OK);
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
