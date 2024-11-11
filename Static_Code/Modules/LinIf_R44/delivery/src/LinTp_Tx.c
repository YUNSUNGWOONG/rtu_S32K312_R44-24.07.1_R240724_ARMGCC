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
**  SRC-MODULE: LinTp_Tx.c                                                    **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : Provision of LINIF TP Tx Internal Functions                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision      Date           By             Description                    **
********************************************************************************
** 1.0.13        21-Aug-2023    KhaLN1         #CP44-2481                     **
** 1.0.10        07-Mar-2023    KhaLN1         #CP44-1811                     **
** 1.0.6         17-Oct-2022    KhaLN1         #CP44-563                      **
** 1.0.5         03-Aug-2022    KhaLN1         #CP44-513                      **
** 1.0.3         17-Sep-2021    DuyNGB         R44-Redmine #20121             **
** 1.0.1         20-Apr-2021    LongTQB        R44-Redmine #17195             **
** 1.0.0         22-Dec-2020    SJ Kim         Initial version                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "LinIf_Cfg.h"
#if(LINTP_SUPPORT == STD_ON)
#include "LinIf.h"
#include "LinTp_Tx.h"    /* LinIf TP transmit header */
#include "LinTp_Ram.h"   /* LinTp Ram header */
#include "PduR_LinTp.h"  /* PduR callback header for LinTp */
#if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
#include "BswM_LinTp.h"       /* BswM callback header for LinTp */
#endif
#include "SchM_LinIf.h"  /* SchM  header for LinIf */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* @Trace: LinTp_SUD_MACRO_008 */
/* AUTOSAR Specification version information */
#define LINTP_TX_C_AR_RELEASE_MAJOR_VERSION    4
#define LINTP_TX_C_AR_RELEASE_MINOR_VERSION    4
#define LINTP_TX_C_AR_RELEASE_REVISION_VERSION 0

/* File version information */
#define LINTP_TX_C_SW_MAJOR_VERSION    1
#define LINTP_TX_C_SW_MINOR_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (LINTP_TX_AR_RELEASE_MAJOR_VERSION != \
  LINTP_TX_C_AR_RELEASE_MAJOR_VERSION)
  #error "LinTp_Tx.c : Mismatch in Specification Major Version"
#endif
#if (LINTP_TX_AR_RELEASE_MINOR_VERSION != \
  LINTP_TX_C_AR_RELEASE_MINOR_VERSION)
  #error "LinTp_Tx.c : Mismatch in Specification Minor Version"
#endif
#if (LINTP_TX_AR_RELEASE_REVISION_VERSION != \
  LINTP_TX_C_AR_RELEASE_REVISION_VERSION)
  #error "LinTp_Tx.c : Mismatch in Specification Revision Version"
#endif
#if (LINTP_TX_SW_MAJOR_VERSION != LINTP_TX_C_SW_MAJOR_VERSION)
  #error "LinTp_Tx.c : Mismatch in Software Major Version"
#endif
#if (LINTP_TX_SW_MINOR_VERSION != LINTP_TX_C_SW_MINOR_VERSION)
  #error "LinTp_Tx.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name      : LinTp_CopyDataTxBuff                                  **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is used to request for Tx buffer        **
**                      from the upper layer in case of insufficient buffer to**
**                      transmit the scheduled frame.                         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpTpChannelInfo                                      **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      LinTp_GpDbTocPtr                                      **
**                                                                            **
**                      Function Invoked:                                     **
**                      PduR_LinTpCopyTxData(), PduR_LinTpTxConfirmation()    **
**                      BswM_LinTp_RequestMode(),                             **
**                      SchM_Enter_LinIf_STATUS_PROTECTION(),                 **
**                      SchM_Exit_LinIf_STATUS_PROTECTION()                   **
*******************************************************************************/
#define LINTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTP_CODE) LinTp_CopyDataTxBuff (P2CONST
  (LinTp_ChannelInfo, AUTOMATIC, LINTP_APPL_CONST) LpTpChannelInfo)
{
  /* @Trace: LinIf_SUD_API_458*/
  PduInfoType LpPduInfoPtr;
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData;
  P2CONST(LinTp_TxMsg, AUTOMATIC, LINTP_CONST) LpTpTxMsgPtr;
  BufReq_ReturnType LenBufferStatus;
  #if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
  uint8 LucChnlIndex;
  #endif
  uint16 LusBufferLength;
  uint8 LucByteCount;
  uint8 LucBufferIndex;
  PduLengthType LucRemainingULBuffer;
  /* Get the address of first TP channel RAM data into local pointer */
  LpTpChannelRamData = LpTpChannelInfo->pLinTpChannelRamData;
  /* Get the byte number from which the source data to be copied */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LucBufferIndex = LpTpChannelRamData->ucLocalTpData;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LucByteCount = LINTP_EIGHT - LucBufferIndex;

  LucRemainingULBuffer = (PduLengthType)LINIF_ZERO;
  /* Check if frame is not a last frame */
  if((LpTpChannelRamData->usTpByteCounter) > LucByteCount)
  {
    /* @Trace: LinIf_SUD_API_459*/
    /* polyspace-begin MISRA-C3:10.8 [Justified:Low] "Value right operand is within range" */
    LusBufferLength = (uint16)((uint16)(LINTP_EIGHT) - (uint16)(LucBufferIndex));
    /* polyspace-end MISRA-C3:10.8 [Justified:Low] "Value right operand is within range" */
  }
  else
  {
    /* @Trace: LinIf_SUD_API_460*/
    LusBufferLength =  LpTpChannelRamData->usTpByteCounter;
  }

  /* @Trace: LinIf_SUD_API_461*/
  #if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
  /* Get the channel index, data length pointer to a data */
  LucChnlIndex = LpTpChannelInfo->ucTpChannelIndex;
  #endif
  /* Always contain 8-byte data payload */
  LpPduInfoPtr.SduLength = LINIF_EIGHT;
  LpPduInfoPtr.SduDataPtr =
    &(LpTpChannelRamData->aaLinTpBuffer[LucBufferIndex]);

  /* get pointer to LinTp Tx structure */
  LpTpTxMsgPtr = &(LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId]);
  /* Invoke PduR Tp Tx provide buffer */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  /* polyspace +2 CERT-C:DCL39-C [Justified:Low] "The other module will access the data in the struct by specific element, so data padding will not affect" */
  LenBufferStatus = PduR_LinTpCopyTxData(LpTpTxMsgPtr->ddTpTxPduId,
    &LpPduInfoPtr, NULL_PTR, &LucRemainingULBuffer);
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */    

  /* Buffer status is ok */
  if(LenBufferStatus == BUFREQ_OK)
  {
    /* @Trace: LinIf_SUD_API_462*/
    /* Update the remaining bytes to be filled */
    (LpTpChannelRamData->usTpByteCounter) =
      (LpTpChannelRamData->usTpByteCounter) - LusBufferLength;

    /* Enter protection area */
    SchM_Enter_LinIf_STATUS_PROTECTION();
    /* Update the Tp status to buffer ready */
    LpTpChannelRamData->ucLinTpStatus = LINTP_TX_BUSY_BUFF_RDY;
    /* Exit protection area */
    SchM_Exit_LinIf_STATUS_PROTECTION();
  } /* Buffer status is ok */
  /* Buffer status is busy */
  else if(LenBufferStatus != BUFREQ_E_BUSY)
  {
    /* @Trace: LinIf_SUD_API_463*/
    /* Enter protection area */
    SchM_Enter_LinIf_STATUS_PROTECTION();
    /* Clear the Tp status */
    LpTpChannelRamData->ucLinTpStatus = LINTP_CHANNEL_IDLE;
    /* Exit protection area */
    SchM_Exit_LinIf_STATUS_PROTECTION();
    /* Invoke PduR Tp Tx Confirmation with failure */
    PduR_LinTpTxConfirmation(LpTpTxMsgPtr->ddTpTxPduId,
      NTFRSLT_E_NO_BUFFER);
    #if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
    /* Invoke BswM with requested schedule mode */
    if(((LpTpChannelInfo->ucLinTpChannelStatus) & LINTP_DIAG_SELECT) ==
      LINTP_DIAG_SELECT)
    {
      /* @Trace: LinIf_SUD_API_464*/
      /* Invoke BswM with requested schedule mode */
      /* polyspace-begin RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
      BswM_LinTp_RequestMode(LinIf_GaaLtChannelInfo[LucChnlIndex].
        ddComMNwHndlId, LINTP_APPLICATIVE_SCHEDULE);
      /* polyspace-end RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
    }
    #endif
  }
  else
  {
    /*Avoid QAC*/
  }
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : LinTp_PrepareNextTxFrame                              **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is used to prepare the next frame data  **
**                      if the frame being transmitted is a continuous frame. **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpTpChannelRamData                                   **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      None                                                  **
**                                                                            **
**                      Function Invoked:                                     **
**                      None                                                  **
*******************************************************************************/
#define LINTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTP_CODE) LinTp_PrepareNextTxFrame (P2VAR
  (LinTp_ChannelRamData, AUTOMATIC, LINTP_APPL_DATA)LpTpChannelRamData)
{
  /* @Trace: LinIf_SUD_API_465*/
  uint16_least LusByteCounter;
  uint8 LucCount;
  uint8 LucDiffernce;

  /* Get the number of bytes to be filled in the present frame */
  LucCount = LINTP_EIGHT - (LpTpChannelRamData->ucLocalTpData);
  /* Get the number of bytes still to be transmitted */
  LusByteCounter = LpTpChannelRamData->usTpByteCounter;
  /* Check the frame is last frame */
  if(LusByteCounter < LucCount)
  {
    /* @Trace: LinIf_SUD_API_466*/
    LucDiffernce = LucCount - (uint8)LusByteCounter;
    /* Add 0xFF for the unused bytes */
    while(LucDiffernce != LINIF_ZERO)
    {
      /* @Trace: LinIf_SUD_API_467*/
      LpTpChannelRamData->aaLinTpBuffer[((LINIF_SEVEN - LucDiffernce) + LINIF_ONE)] = LINIF_MAX_BYTE;
      LucDiffernce--;
    }
  }
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : LinTp_UpdateFrameStatus                               **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function updates the status of CF transmission   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpTpChannelRamData                                   **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                      None                                                  **
**                                                                            **
**                      Function Invoked:                                     **
**                      LinTp_PrepareNextTxFrame(),                           **
**                      SchM_Enter_LinIf_STATUS_PROTECTION(),                 **
**                      SchM_Exit_LinIf_STATUS_PROTECTION()                   **
*******************************************************************************/
#define LINTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTP_CODE) LinTp_UpdateFrameStatus(P2VAR
  (LinTp_ChannelRamData, AUTOMATIC, LINTP_APPL_DATA) LpTpChannelRamData)
{
  /* Check if the frame is not the last frame */
  if(LpTpChannelRamData->usTpByteCounter != LINIF_ZERO)
  {
    /* @Trace: LinIf_SUD_API_468*/
    /* Increment frame counter */
    (LpTpChannelRamData->ucTpFrameCounter)++;
    /* Check if frame counter is greater than 15 */
    if(LpTpChannelRamData->ucTpFrameCounter > LINTP_MAX_FRAME_COUNTER)
    {
      /* @Trace: LinIf_SUD_API_469*/
      LpTpChannelRamData->ucTpFrameCounter = LINIF_ZERO;
    }
    /* @Trace: LinIf_SUD_API_470*/
    /* Update the PCI byte */
    LpTpChannelRamData->aaLinTpBuffer[LINIF_ONE] =
      (LpTpChannelRamData->ucTpFrameCounter | LINIF_CF_PCI);
    /* Update the buffer index from where the data needs to be loaded */
    LpTpChannelRamData->ucLocalTpData = LINIF_TWO;
    /* Enter protection area */
    SchM_Enter_LinIf_STATUS_PROTECTION();
    /* Update the Tp status to buffer not ready */
    LpTpChannelRamData->ucLinTpStatus = LINTP_TX_BUSY_BUFF_NOT_RDY;
    /* Exit protection area */
    SchM_Exit_LinIf_STATUS_PROTECTION();
    /* Prepare the frame */
    LinTp_PrepareNextTxFrame(LpTpChannelRamData);
  } /* frame is not the last frame */
  else
  {
    /* @Trace: LinIf_SUD_API_471*/
    /* Set the frame counter to end */
    LpTpChannelRamData->ucTpFrameCounter = LINIF_MAX_BYTE;
  }
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
