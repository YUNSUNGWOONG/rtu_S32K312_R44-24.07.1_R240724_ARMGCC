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
**  SRC-MODULE: LinTp_Rx.c                                                    **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : Provision of LINIF TP Rx Internal Functions                   **
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
** 1.0.10        07-Mar-2023    KhaLN1         #CP44-1811                     **
** 1.0.6         17-Oct-2022    KhaLN1         #CP44-563                      **
** 1.0.5         03-Aug-2022    KhaLN1         #CP44-513                      **
** 1.0.3         25-Apr-2022    DuyNHP2        R44-Redmine #26480             **
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
#include "LinTp_Rx.h"         /* LinIf TP Receive header */
#include "LinIf_Ram.h"        /* LinIf RAM header */
#include "LinTp_Ram.h"        /* LinTp RAM header */
#include "SchM_LinIf.h"       /* SchM header for LinIf */
#include "PduR_LinTp.h"       /* PduR callback header for LinIf */
#if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
#include "BswM_LinTp.h"       /* BswM callback header for LinTp */
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* @Trace: LinTp_SUD_MACRO_006 */
/* AUTOSAR Specification version information */
#define LINTP_RX_C_AR_RELEASE_MAJOR_VERSION    4
#define LINTP_RX_C_AR_RELEASE_MINOR_VERSION    4
#define LINTP_RX_C_AR_RELEASE_REVISION_VERSION 0

/* File version information */
#define LINTP_RX_C_SW_MAJOR_VERSION    1
#define LINTP_RX_C_SW_MINOR_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (LINTP_RX_AR_RELEASE_MAJOR_VERSION != \
  LINTP_RX_C_AR_RELEASE_MAJOR_VERSION)
  #error "LINTP_Rx.c : Mismatch in Specification Major Version"
#endif
#if (LINTP_RX_AR_RELEASE_MINOR_VERSION != \
  LINTP_RX_C_AR_RELEASE_MINOR_VERSION)
  #error "LINTP_Rx.c : Mismatch in Specification Minor Version"
#endif
#if (LINTP_RX_AR_RELEASE_REVISION_VERSION != \
  LINTP_RX_C_AR_RELEASE_REVISION_VERSION)
  #error "LINTP_Rx.c : Mismatch in Specification Revision Version"
#endif
#if (LINTP_RX_SW_MAJOR_VERSION != LINTP_RX_C_SW_MAJOR_VERSION)
  #error "LINTP_Rx.c : Mismatch in Software Major Version"
#endif
#if (LINTP_RX_SW_MINOR_VERSION != LINTP_RX_C_SW_MINOR_VERSION)
  #error "LINTP_Rx.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

static FUNC(void, LINIF_CODE) LinTp_HandleCopyRxData(
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINTP_APPL_CONST) LpTpChannelPtr,
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData,
  P2VAR(PduInfoType, AUTOMATIC, LINTP_DATA) LpRxPduInfo);

/*******************************************************************************
** Function Name      : LinTp_CheckForNewRxMsg                                **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This functions is used to check for any new Rx message**
**                      reception.                                            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpRxDataPtr, *LpTpChannelPtr                         **
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
**                      LinTp_GpFirstRxMsg                                    **
**                                                                            **
**                      Function Invoked:                                     **
**                      LinTp_ResponsePendingService(),                       **
**                      PduR_LinTpRxIndication(), LinIf_SwitchScheduleMode(), **
**                      SchM_Enter_LinIf_STATUS_PROTECTION(),                 **
**                      SchM_Exit_LinIf_STATUS_PROTECTION()                   **
*******************************************************************************/
#define LINTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTP_CODE) LinTp_CheckForNewRxMsg(
  P2VAR(uint8, AUTOMATIC, LINTP_APPL_DATA) LpRxDataPtr,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC,  LINTP_APPL_CONST) LpTpChannelPtr)
{
  /* @Trace: LinIf_SUD_API_472*/
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA)
    LpTpChannelRamData;
  P2VAR(uint8, AUTOMATIC, LINTP_DATA) LpTpRxDataPtr;
  P2CONST(LinTp_RxMsg, AUTOMATIC, LINTP_CONST) LpTpMsgPtr;
  uint16 LusIndex;
  boolean LblNADCheckStatus;

  /* Set the default value */
  /* Get pointer to Rx Msg structure */
  LpTpMsgPtr = &(LinTp_GaaRxMsg[LpTpChannelPtr->ddTpRxMsgIndex]);
  LpTpChannelRamData = LpTpChannelPtr->pLinTpChannelRamData;
  LpTpRxDataPtr = LpRxDataPtr;
  /* Get the NAD and form the received frame */
  /* polyspace-begin RTE:NIV [Justified:Low] "The value was set before" */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LpTpChannelRamData->ucActiveNad = *LpTpRxDataPtr;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  /* polyspace-end RTE:NIV [Justified:Low] "The value was set before" */
  /* Set first frame status as true */
  LpTpChannelRamData->blFirstFrame = LINIF_TRUE;
  if(LpTpChannelRamData->ucRequestedNad == LpTpChannelRamData->ucActiveNad)
  {
    /* @Trace: LinIf_SUD_API_473*/
    LblNADCheckStatus = LINIF_TRUE;
  }
  else if((LpTpChannelPtr->ucLinTpChannelStatus & LINIF_DROP_REQUEST) ==
    LINIF_ONE)
  {
    /* @Trace: LinIf_SUD_API_474*/
    LpTpMsgPtr = LinTp_RxBinarySearch(LpTpMsgPtr,
    LpTpChannelPtr->ddNoOfTpRxMsgs, LpTpChannelRamData->ucActiveNad);
    if(LpTpMsgPtr != NULL_PTR)
    {
      /* @Trace: LinIf_SUD_API_475*/
      LblNADCheckStatus = LINIF_TRUE;
    }
    else
    {
      /* @Trace: LinIf_SUD_API_476*/
      LblNADCheckStatus  = LINIF_FALSE;
    }
  }
  else
  {
    /* @Trace: LinIf_SUD_API_477*/
    LblNADCheckStatus  = LINIF_FALSE;
  }
  /* Get the PduId of the received NAD */

  /* Check if the correct NAD is received */
  if(LblNADCheckStatus  == LINIF_TRUE)
  {
    /* @Trace: LinIf_SUD_API_478*/
    LpTpChannelRamData->pTpBuffPtr = LpTpRxDataPtr;

    LpTpChannelRamData->ucLocalTpData = LINIF_ZERO;

    /* Copy the active PduId */
    /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
    LpTpChannelRamData->ddActiveTpPduId = LpTpMsgPtr->ddTpRxPduId;
    /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
    /* Enter protection area */
    SchM_Enter_LinIf_STATUS_PROTECTION();
    LpTpChannelRamData->ucLinTpStatus = LINTP_RX_BUSY_BUFF_NOT_RDY;
    /* Exit protection area */
    SchM_Exit_LinIf_STATUS_PROTECTION();
    /* polyspace-begin MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
    LpTpRxDataPtr++;
    /* polyspace-end MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
    /* Get the PCI Byte */
    /* polyspace-begin RTE:NIV [Justified:Low] "The value was set before" */
    /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
    LusIndex = *LpTpRxDataPtr;
    /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
    /* polyspace-end RTE:NIV [Justified:Low] "The value was set before" */
    /* Check if the received frame is of SF type */
    if(((LusIndex & LINIF_PCI_MASK) == LINIF_SF_PCI) &&
      ((LusIndex & LINTP_DL_MASK) != LINIF_ZERO)  &&
      ((LusIndex & LINTP_DL_MASK) <= LINIF_SIX))
    {
      /* @Trace: LinIf_SUD_API_479*/
      LusIndex = LusIndex & LINTP_DL_MASK;
      LpTpChannelRamData->usTpByteCounter = LusIndex;
      LpTpChannelRamData->ucLocalTpData = LINIF_TWO;
      /* polyspace-begin MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
      LpTpRxDataPtr++;
      /* polyspace-end MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
      /* Get the RSID of SF.( 3 rd byte of the frame ) */
      /* polyspace-begin RTE:NIV [Justified:Low] "The value was set before" */
      /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
      LpTpChannelRamData->ucLinTpRsid = *LpTpRxDataPtr;
      /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
      /* polyspace-end RTE:NIV [Justified:Low] "The value was set before" */
      /* Call the function to handle the response pending frames */
      LinTp_ResponsePendingService(LpTpChannelPtr);
    }
    /* Received frame is of type FF */
    else if((LusIndex & LINIF_PCI_MASK) == LINIF_FF_PCI)
    {
      /* @Trace: LinIf_SUD_API_480*/
      LusIndex = LusIndex & LINTP_DL_MASK;
      LusIndex  = LusIndex << LINTP_EIGHT;
      LpTpChannelRamData->usTpByteCounter = LusIndex;
      /* polyspace-begin MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
      LpTpRxDataPtr++;
      /* polyspace-end MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
      /* polyspace-begin RTE:NIV [Justified:Low] "The value was set before" */
      /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
      LusIndex = *LpTpRxDataPtr;
      /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
      /* polyspace-end RTE:NIV [Justified:Low] "The value was set before" */
      LpTpChannelRamData->usTpByteCounter |= LusIndex;
      if(LpTpChannelRamData->usTpByteCounter < LINIF_SEVEN)
      {
        /* @Trace: LinIf_SUD_API_481*/
        /* Invoke PduR Tp Rx Indication with NTFRSLT_E_UNEXP_PDU */
        PduR_LinTpRxIndication(LpTpChannelRamData->ddMRFSduId,
          NTFRSLT_E_UNEXP_PDU);
        /* Call the function to switch the mode and stop the ongoing
         * reception */
        LinIf_SwitchScheduleMode(LpTpChannelPtr, LINTP_APPLICATIVE_SCHEDULE);
      }
      else
      {
        /* @Trace: LinIf_SUD_API_482*/
        LpTpChannelRamData->ucTpFrameCounter = LINIF_ZERO;
        LpTpChannelRamData->ucLocalTpData = LINIF_THREE;
        /* polyspace-begin MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
        LpTpRxDataPtr++;
        /* polyspace-end MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
        /* Get the RSID of FF.( 4 th byte of the frame ) */
        /* polyspace-begin RTE:NIV [Justified:Low] "The value was set before" */
        /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
        LpTpChannelRamData->ucLinTpRsid = *LpTpRxDataPtr;
        /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
        /* polyspace-end RTE:NIV [Justified:Low] "The value was set before" */
        /* Call the function to handle the response pending frames */
        LinTp_ResponsePendingService(LpTpChannelPtr);
      }
    }
    /* Frame is of type CF */
     else
    {
       /* @Trace: LinIf_SUD_API_483*/
       /* Invoke PduR Tp Rx Indication with NTFRSLT_E_UNEXP_PDU */
       PduR_LinTpRxIndication(LpTpChannelRamData->ddMRFSduId,
         NTFRSLT_E_UNEXP_PDU);
       /* Call the function to switch the mode and stop the ongoing
        * reception */
       LinIf_SwitchScheduleMode(LpTpChannelPtr, LINTP_APPLICATIVE_SCHEDULE);
    }
  }/* Check if correct NAD is received */
   else
   {
     /* @Trace: LinIf_SUD_API_484*/
     /* Invoke PduR Tp Rx Indication with NTFRSLT_E_UNEXP_PDU */
     PduR_LinTpRxIndication(LpTpChannelRamData->ddMRFSduId,
       NTFRSLT_E_UNEXP_PDU);
     /* Call the function to switch the mode and stop the ongoing
      * reception */
     LinIf_SwitchScheduleMode(LpTpChannelPtr, LINTP_APPLICATIVE_SCHEDULE);
   }
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : LinTp_CheckForCfRxMsg                                 **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is used to check for new CF TP frame    **
**                      reception.                                            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpRxDataPtr, *LpTpChannelPtr                         **
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
**                      LinTp_GpFirstChannel                                  **
**                                                                            **
**                      Function Invoked:                                     **
**                      PduR_LinTpRxIndication(), LinIf_SwitchScheduleMode(), **
**                      LinTp_CheckForNewRxMsg(), BswM_LinTp_RequestMode(),   **
**                      SchM_Exit_LinIf_STATUS_PROTECTION(),                  **
**                      SchM_Enter_LinIf_STATUS_PROTECTION()                  **
*******************************************************************************/
#define LINTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTP_CODE) LinTp_CheckForCfRxMsg (
  P2VAR(uint8, AUTOMATIC, LINTP_APPL_DATA) LpRxDataPtr,
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINTP_APPL_CONST) LpTpChannelPtr)
{
  /* @Trace: LinIf_SUD_API_485*/
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA)
    LpTpChannelRamData;
  P2VAR(uint8, AUTOMATIC, LINTP_DATA) LpTpRxDataPtr;
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINTP_DATA) LpTpChannelPtrTmp;
  uint16 LusIndex;
  uint8 LucNad;

  LpTpRxDataPtr = LpRxDataPtr;
  /* polyspace-begin MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
  LpTpChannelPtrTmp = &(LinTp_GpFirstChannel[LpTpChannelPtr->ucTpChannelIndex]);
  /* polyspace-end MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LpTpChannelRamData = LpTpChannelPtrTmp->pLinTpChannelRamData;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LpTpChannelRamData->blFirstFrame = LINIF_FALSE;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  /* Decode the NAD, PCI and frame counter */
  /* polyspace-begin RTE:NIV [Justified:Low] "The value was set before" */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LucNad = *LpTpRxDataPtr;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  /* polyspace-end RTE:NIV [Justified:Low] "The value was set before" */
  /* polyspace-begin MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
  LpTpRxDataPtr++;
  /* polyspace-end MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
  /* polyspace-begin RTE:NIV [Justified:Low] "The value was set before" */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LusIndex = *LpTpRxDataPtr;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  /* polyspace-end RTE:NIV [Justified:Low] "The value was set before" */

  /* Check the NAD, PCI type and frame counter */
  if((LucNad == LpTpChannelRamData->ucActiveNad) &&
    ((LusIndex & LINIF_PCI_MASK) == LINIF_CF_PCI) &&
    ((LusIndex & LINTP_DL_MASK) ==
    LpTpChannelRamData->ucTpFrameCounter))
  {
    /* @Trace: LinIf_SUD_API_486*/
    /* polyspace-begin MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
    LpTpRxDataPtr--;
    /* polyspace-end MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
    LpTpChannelRamData->pTpBuffPtr = LpTpRxDataPtr;
    LpTpChannelRamData->ucLocalTpData = LINIF_TWO;
    /* Enter protection area */
    SchM_Enter_LinIf_STATUS_PROTECTION();
    /* Change the status to BUFF_NOT_RDY */
    LpTpChannelRamData->ucLinTpStatus = LINTP_RX_BUSY_BUFF_NOT_RDY;
    /* Exit protection area */
    SchM_Exit_LinIf_STATUS_PROTECTION();
  }
  else
  {
    /* Check if received NAD is matches with configuration.
    LpTpChannelRamData->ucActiveNad will be updated from the FF */
    if(LucNad != LpTpChannelRamData->ucActiveNad)
    {
      /* @Trace: LinIf_SUD_API_487*/
      /* LINIF655, LINIF648 and LINIF613 */
      /* Invoke Upper Layer Rx Indication with NTFRSLT_E_UNEXP_PDU */
      PduR_LinTpRxIndication(LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId,
        NTFRSLT_E_UNEXP_PDU);
      /* Call the function to switch the mode and stop the ongoing
       * transmission */
      LinIf_SwitchScheduleMode(LpTpChannelPtrTmp, LINTP_APPLICATIVE_SCHEDULE);
    }
    /* Check if the sequence number is incorrect */
    else if ((LusIndex & LINIF_PCI_MASK) != LINIF_CF_PCI)
    {
      /* @Trace: LinIf_SUD_API_488*/
      /* LINIF653, LINIF654 */
      /* Invoke Upper Layer Rx Indication with NTFRSLT_E_UNEXP_PDU */
      PduR_LinTpRxIndication(LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId,
        NTFRSLT_E_UNEXP_PDU);

      /* Call the function to switch the mode and stop the ongoing
       * transmission */
      LinIf_SwitchScheduleMode(LpTpChannelPtrTmp, LINTP_APPLICATIVE_SCHEDULE);
      /* polyspace-begin MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
      LpTpRxDataPtr--;
      /* polyspace-end MISRA-C3:17.8 [To investigate:Low] "Logic related to series of flow, will be optimized later" */
      /* Invoke internal function to check if New Tp message is
      * received */
      LinTp_CheckForNewRxMsg(LpTpRxDataPtr, LpTpChannelPtrTmp);
    }
    else
    {
      /* @Trace: LinIf_SUD_API_489*/
      /* Invoke Upper Layer Rx Indication with NTFRSLT_E_UNEXP_PDU */
      PduR_LinTpRxIndication(LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId,
        NTFRSLT_E_WRONG_SN);
      /* Call the function to switch the mode and stop the ongoing
       * transmission */
      LinIf_SwitchScheduleMode(LpTpChannelPtrTmp, LINTP_APPLICATIVE_SCHEDULE);
    }
  }
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : LinTp_RequestNewRxBuff                                **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This functions is used for requesting Receive buffer  **
**                      from the upper layer.                                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpTpChannelPtr                                       **
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
**                      PduR_LinTpStartOfReception(), PduR_LinTpRxIndication()**
**                      BswM_LinTp_RequestMode(), PduR_LinTpCopyRxData(),     **
**                      SchM_Enter_LinIf_STATUS_PROTECTION(),                 **
**                      SchM_Exit_LinIf_STATUS_PROTECTION()                   **
*******************************************************************************/
#define LINTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTP_CODE) LinTp_RequestNewRxBuff(
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINTP_APPL_CONST) LpTpChannelPtr)
{
  /* @Trace: LinIf_SUD_API_490*/
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA)
    LpTpChannelRamData;
  PduLengthType LddBufferSize = LINIF_ZERO;
  BufReq_ReturnType LenBufferStatus;
  PduInfoType LddRxPduInfo;
  uint8 LucCount;
  boolean LblCopyRxData;

  /* Get the current channel data */
  LpTpChannelRamData = LpTpChannelPtr->pLinTpChannelRamData;
  LblCopyRxData = LINIF_TRUE;
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LucCount = LpTpChannelRamData->ucLocalTpData;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  /* polyspace-begin MISRA-C3:10.7 [To investigate:Low] "Value of left and right are within range" */
  if(LpTpChannelRamData->usTpByteCounter >
    ((uint16)(LINTP_EIGHT) - (uint16)(LpTpChannelRamData->ucLocalTpData)))
  /* polyspace-end MISRA-C3:10.7 [To investigate:Low] "Value of left and right are within range" */    
  {
    /* @Trace: LinIf_SUD_API_491*/
    /* polyspace-begin MISRA-C3:10.6 [To investigate:Low] "Value of left and right are within range" */
    LpTpChannelRamData->ddTpSduLength =
    ((PduLengthType)(LINTP_EIGHT) - (PduLengthType)(LpTpChannelRamData->ucLocalTpData));
    /* polyspace-end MISRA-C3:10.6 [To investigate:Low] "Value of left and right are within range" */
  }
  else
  {
    /* @Trace: LinIf_SUD_API_492*/
    LpTpChannelRamData->ddTpSduLength = LpTpChannelRamData->usTpByteCounter;
  }
  /* @Trace: LinIf_SUD_API_493*/
  LddRxPduInfo.SduDataPtr = &(LpTpChannelRamData->pTpBuffPtr[LucCount]);
  LddRxPduInfo.SduLength = LpTpChannelRamData->ddTpSduLength;
  if(LpTpChannelRamData->blFirstFrame == LINIF_TRUE)
  { 
    /* @Trace: LinIf_SUD_API_494*/
    /* polyspace +3 CERT-C:DCL39-C [Justified:Low] "The other module will access the data in the struct by specific element, so data padding will not affect" */
    LenBufferStatus =
      PduR_LinTpStartOfReception(LpTpChannelRamData->ddActiveTpPduId,
      &LddRxPduInfo, LpTpChannelRamData->usTpByteCounter, &LddBufferSize);
    /* Check if the buffer is ready */
    if(LenBufferStatus == BUFREQ_OK)
    {
      /* polyspace-begin RTE:NIVL [Justified:Low] "The value was set before" */
      if(LddBufferSize >= LpTpChannelRamData->ddTpSduLength)
      /* polyspace-end RTE:NIVL [Justified:Low] "The value was set before" */
      {
        /* @Trace: LinIf_SUD_API_495*/
        /* Copy rx data Api invocation status */
        LblCopyRxData = LINIF_TRUE;
      }
    }
    else if ((LenBufferStatus == BUFREQ_E_NOT_OK) || (LenBufferStatus ==
      BUFREQ_E_OVFL))
    {
      /* @Trace: LinIf_SUD_API_496*/
      LblCopyRxData = LINIF_FALSE;
      /* Clear the P2 timer counter */
      LpTpChannelRamData->usP2TimerCounter = LINIF_ZERO;
      /* Invoke Upper Layer Rx Indication with NTFRSLT_E_NOT_OK */
      PduR_LinTpRxIndication(LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId,
        NTFRSLT_E_NOT_OK);
      #if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
      /* Invoke BswM with requested schedule mode */
      if(((LpTpChannelPtr->ucLinTpChannelStatus) & LINTP_DIAG_SELECT) ==
        LINTP_DIAG_SELECT)
      {
        /* @Trace: LinIf_SUD_API_497*/
        /* Invoke  BswM_LinTp_RequestMode with LINTP_APPLICATIVE_SCHEDULE */
        /* polyspace-begin RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
        BswM_LinTp_RequestMode(LinIf_GaaLtChannelInfo
          [LpTpChannelPtr->ucTpChannelIndex].ddComMNwHndlId,
          LINTP_APPLICATIVE_SCHEDULE);
        /* polyspace-end RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
      }
      #endif
    }
    else
    {
      /* @Trace: LinIf_SUD_API_498*/
      LblCopyRxData = LINIF_FALSE;
    }
    /* @Trace: LinIf_SUD_API_499*/
    LpTpChannelRamData->blFirstFrame = LINIF_FALSE;
  }
  if(LblCopyRxData == LINIF_TRUE)
  {
    LinTp_HandleCopyRxData(LpTpChannelPtr, LpTpChannelRamData, &LddRxPduInfo);
  }
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : LinTp_RxBinarySearch                                  **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This function is used to find a frame with particular **
**                      NAD in an array using binary search algorithm.        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpTpRxPtrArray, LucSize, LucRxNad                    **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : *LpRxTpMsgPtr                                         **
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
/* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */
FUNC(P2CONST(LinTp_RxMsg, AUTOMATIC, LINTP_APPL_CONST),
  LINTP_CODE)LinTp_RxBinarySearch (P2CONST(LinTp_RxMsg,
  AUTOMATIC, LINTP_APPL_CONST) LpTpRxPtrArray, uint8 LucSize,
  uint8 LucRxNad)
/* polyspace-end MISRA-C3:20.7 [Justified:Low] "Macro defined by compiler configuration, Parentheses is not needed" */  
{
  /* @Trace: LinIf_SUD_API_505*/
  P2CONST(LinTp_RxMsg, AUTOMATIC, LINTP_CONST) LpRxTpMsgPtr;
  uint8 LucTpCurrNad;
  uint8 LucLow;
  uint8 LucHigh;
  uint8 LucMid;

  /* Initialize LucHigh variable with number of Tp Rx pdus in the scheduler-1 */
  LucHigh = LucSize - LINIF_ONE;
  /* Initialize LucLow variable with zero */
  LucLow = LINIF_ONE;

  /* Initialize return value with null pointer */
  LpRxTpMsgPtr = NULL_PTR;

  /* Get the lower limit of NAD */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LucTpCurrNad = LpTpRxPtrArray->ucTpNad;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  /* Check whether search NAD is in range */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  if((LucRxNad >= LucTpCurrNad) &&
     (LucRxNad <= (LpTpRxPtrArray[LucHigh].ucTpNad)))
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  {
    /* Check w
    hether requested NAD is same as first NAD of the list */
    if(LucRxNad != LucTpCurrNad)
    {
      do
      {
        /* @Trace: LinIf_SUD_API_506*/
        /* Get the middle index number */
        LucMid = (LucHigh + LucLow) >> LINIF_ONE;
        /* Get the NAD of the mid Tp Rx PDU */
        LucTpCurrNad = (LpTpRxPtrArray[LucMid].ucTpNad);
        /* Compare NAD with the requested one */
        if(LucTpCurrNad == LucRxNad)
        {
          /* @Trace: LinIf_SUD_API_507*/
          /* Update the return pointer with the Rx L-PDU structure */
          LpRxTpMsgPtr = &LpTpRxPtrArray[LucMid];
          /* Set LucHigh to zero to break the loop */
          LucHigh = LINIF_ZERO;
        }
        /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_LinTp_Transmit" */
        else
        {
          /* Compare the NAD with the requested one */
          if(LucRxNad < LucTpCurrNad)
          {
            /* @Trace: LinIf_SUD_API_508*/
            /* If the received NAD is lower, update LucHigh */
            LucHigh = LucMid;
            /* LucHigh = LucMid - 1 */
            LucHigh--;
          }
          else
          {
            /* @Trace: LinIf_SUD_API_509*/
            /* If the received NAD is higher, update LucLow */
            LucLow = LucMid + LINIF_ONE;
          }
        }
        /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_LinTp_Transmit" */
      }while(LucLow <= LucHigh);
    } /* if(LucRxNad != LucTpCurrNad) */
    else
    {
      /* @Trace: LinIf_SUD_API_510*/
      /* Update the return pointer with the actual Rx Tp Msg structure */
      LpRxTpMsgPtr = LpTpRxPtrArray;
    }
  }
  /* @Trace: LinIf_SUD_API_511*/
  /* Return RxLpduRetVal pointer */
  return (LpRxTpMsgPtr);
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : LinIf_SwitchScheduleMode                              **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This functions is used to switch the schedule mode.   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpTpChannelPtr, LddScheduleMode                      **
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
**                      LinIf_GaaLtChannelInfo                                **
**                                                                            **
**                      Function Invoked:                                     **
**                      BswM_LinTp_RequestMode(),                             **
**                      SchM_Enter_LinIf_STATUS_PROTECTION(),                 **
**                      SchM_Exit_LinIf_STATUS_PROTECTION()                   **
*******************************************************************************/
#define LINTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinIf_SwitchScheduleMode(
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINIF_APPL_CONST) LpTpChannelPtr,
  LinTp_Mode LddScheduleMode)
{
  /* @Trace: LinIf_SUD_API_512*/
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINIF_DATA) LpTpChannelRamData;
  #if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
  NetworkHandleType LddChannel;
  #endif

  /* Get the current channel data */
  LpTpChannelRamData = LpTpChannelPtr->pLinTpChannelRamData;
  /* Enter protection area */
  SchM_Enter_LinIf_STATUS_PROTECTION();
  /* Terminate Ongoing Transmission */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  LpTpChannelRamData->ucLinTpStatus = LINTP_CHANNEL_IDLE;
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
    /* Exit protection area */
  SchM_Exit_LinIf_STATUS_PROTECTION();
  /* Reset the response pending frame counter */
  LpTpChannelRamData->usRespPendingFrameCounter = LINIF_ZERO;
  /* Reset the P2 timer Counter */
  LpTpChannelRamData->usP2TimerCounter = LINIF_ZERO;
  /* Clear the P2 timer load flag */
  LpTpChannelRamData->blP2TimerInitialLoad = LINIF_FALSE;

  #if(LINTP_SCHEDULE_CHANNEL_DIAG == STD_ON)
  /* Get the Network handle id */
  /* polyspace-begin RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
  LddChannel = LinIf_GaaLtChannelInfo[LpTpChannelPtr->ucTpChannelIndex].
    ddComMNwHndlId;
  /* polyspace-end RTE:OBAI [Justified:Low] "Array index is not outside bounds." */
  /* Invoke BswM with requested schedule mode */
  if(((LpTpChannelPtr->ucLinTpChannelStatus) & LINTP_DIAG_SELECT) ==
    LINTP_DIAG_SELECT)
  {
    /* @Trace: LinIf_SUD_API_513*/
    /* Invoke BswM with requested schedule mode */
    BswM_LinTp_RequestMode(LddChannel, LddScheduleMode);
  }
  #else
  LINIF_UNUSED(LddScheduleMode);
  #endif
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : LinTp_ResponsePendingService                          **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This functions is used to handle the Response Pending **
**                      frames.                                               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpTpChannelPtr                                       **
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
**                      BswM_LinTp_RequestMode()                              **
*******************************************************************************/
#define LINTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINIF_CODE) LinTp_ResponsePendingService(
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINTP_APPL_CONST) LpTpChannelPtr)
{
  /* @Trace: LinIf_SUD_API_514*/
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData;
  boolean LblRespPendingServiceSts;
  LblRespPendingServiceSts = LINIF_TRUE;
  /* Get the current channel data */
  LpTpChannelRamData = LpTpChannelPtr->pLinTpChannelRamData;
  /* Check whether the received frame is a Response pending frame */
  /* polyspace-begin RTE:IDP [Justified:Low] "The pointer is checked before input" */
  if(LpTpChannelRamData->ucLinTpRsid == LINTP_PENDING_RESPONSE_FRAME)
  /* polyspace-end RTE:IDP [Justified:Low] "The pointer is checked before input" */
  {
    /* @Trace: LinIf_SUD_API_515*/
    /* Increment the response pending frame counter */
    LpTpChannelRamData->usRespPendingFrameCounter++;
    /* Check whether the number of received response frame is
    less than the ucMaxNumberOfRespPendingFrames */
    if(LpTpChannelRamData->usRespPendingFrameCounter <=
	LpTpChannelPtr->usMaxRespPendingFrames)
    {
      /* @Trace: LinIf_SUD_API_516*/
      /* Set the resp pending service status as false */
      LblRespPendingServiceSts = LINIF_FALSE;
      /* Start the P2 timer counter with P2MAX */
      LpTpChannelRamData->usP2TimerCounter = LpTpChannelPtr->usP2Max;
    }
    else
    {
      /* @Trace: LinIf_SUD_API_517*/
      /* Invoke Tp Rx Indication with failure --LINIF623 */
      PduR_LinTpRxIndication(LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId,
        NTFRSLT_E_NOT_OK);
      /* Call the function to switch the mode and stop the ongoing
       * transmission */
      LinIf_SwitchScheduleMode(LpTpChannelPtr, LINTP_APPLICATIVE_SCHEDULE);
    }
  }
  else
  {
    /* @Trace: LinIf_SUD_API_518*/
    /* Set the resp pending service status as false */
    LblRespPendingServiceSts = LINIF_FALSE;
    /* Clear the P2 timer counter */
    LpTpChannelRamData->usP2TimerCounter = LINIF_ZERO;
  }
  /* Check if resp pending service status is false*/
  if(LblRespPendingServiceSts == LINIF_FALSE)
  {
    /* @Trace: LinIf_SUD_API_519*/
    /* Clear the P2 timer inital load flag */
    LpTpChannelRamData->blP2TimerInitialLoad = LINIF_FALSE;
  }
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : LinTp_HandleCopyRxData                                **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This functions is used to copy RX data into the       **
**                      buffer provided by Pdur.                              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Re-entrant                                        **
**                                                                            **
** Input Parameters   : *LpTpChannelPtr                                       **
**                                                                            **
** InOut Parameters   : *LpTpChannelRamData                                   **
**                      *LpRxPduInfo                                          **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable:                                      **
**                        LinTp_GaaTxMsg                                      **
**                                                                            **
**                      Function Invoked:                                     **
**                        PduR_LinTpCopyRxData()                              **
**                        PduR_LinTpRxIndication()                            **
**                        LinIf_SwitchScheduleMode()                          **
*******************************************************************************/
#define LINTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, LINIF_CODE) LinTp_HandleCopyRxData(
  P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINTP_APPL_CONST) LpTpChannelPtr,
  P2VAR(LinTp_ChannelRamData, AUTOMATIC, LINTP_DATA) LpTpChannelRamData,
  P2VAR(PduInfoType, AUTOMATIC, LINTP_DATA) LpRxPduInfo)
{
  BufReq_ReturnType LenBufferStatus;
  PduLengthType LddBufferSize;

  LddBufferSize = LINIF_ZERO;

  if(LpTpChannelRamData->blAvblBuff != LINIF_FALSE)
  {
    /* @Trace: LinIf_SUD_API_500*/
    /* Invoke PduR_LinTpCopyRxData with data to be copied */
    /* polyspace +2 CERT-C:DCL39-C [Justified:Low] "The other module will access the data in the struct by specific element, so data padding will not affect" */
    LenBufferStatus = PduR_LinTpCopyRxData(LpTpChannelRamData->
    ddActiveTpPduId, LpRxPduInfo, &LddBufferSize);
  }
  else
  {
    /* @Trace: LinIf_SUD_API_501*/
    /* Set the Sdulength to zero */
    LpRxPduInfo->SduLength = LINIF_ZERO;
    /* Invoke PduR_LinTpCopyRxData with data to be copied */
    /* polyspace +2 CERT-C:DCL39-C [Justified:Low] "The other module will access the data in the struct by specific element, so data padding will not affect" */
    LenBufferStatus = PduR_LinTpCopyRxData(LpTpChannelRamData->
      ddActiveTpPduId, LpRxPduInfo, &LddBufferSize);
  }
  /* Check if the buffer is ready */
  /* polyspace-begin RTE:NIVL [Justified:Low] "The value was set before" */
  if((LenBufferStatus == BUFREQ_OK) && (LddBufferSize >= LINIF_CF_SIZE))
  /* polyspace-end RTE:NIVL [Justified:Low] "The value was set before" */
  {
    /* @Trace: LinIf_SUD_API_502*/
    /* Update the byte counter with the remaining length to be received */
    LpTpChannelRamData->usTpByteCounter =
      (uint16)((LpTpChannelRamData->usTpByteCounter) -
      (LpTpChannelRamData->ddTpSduLength));
    /* Increment the frame counter */
    LpTpChannelRamData->ucTpFrameCounter++;
    /* Enter protection area */
    SchM_Enter_LinIf_STATUS_PROTECTION();
    /* Update the channel status to Buffer ready */
    LpTpChannelRamData->ucLinTpStatus = LINTP_RX_BUSY_BUFF_RDY;
    /* Exit protection area */
    SchM_Exit_LinIf_STATUS_PROTECTION();
    /* Set buffer availability to TRUE */
    LpTpChannelRamData->blAvblBuff = LINIF_TRUE;
  }/* if(LenBufferStatus == BUFREQ_OK) */
  /* polyspace-begin RTE:NIVL [Justified:Low] "The value was set before" */
  else if(LddBufferSize < LINIF_CF_SIZE)
  /* polyspace-end RTE:NIVL [Justified:Low] "The value was set before" */
  {
    /* @Trace: LinIf_SUD_API_503*/
    /* Update the channel status */
    LpTpChannelRamData->blAvblBuff = LINIF_FALSE;
  }
  /* check if PduR returns BUFREQ_E_NOT_OK */
  else if(LenBufferStatus != BUFREQ_E_BUSY)
  {
    /* @Trace: LinIf_SUD_API_504*/
    /* Invoke Tp Rx Indication with failure --LINIF677 */
    PduR_LinTpRxIndication((LinTp_GaaTxMsg[LpTpChannelRamData->ddActiveTpPduId].ddTpTxPduId),
      NTFRSLT_E_NOT_OK);
    /* Switch to applicative schedule */
    LinIf_SwitchScheduleMode(LpTpChannelPtr, LINTP_APPLICATIVE_SCHEDULE);
  }
  else
  {
    /* To avoid QAC warning */
  }
}
#define LINTP_STOP_SEC_CODE
#include "MemMap.h"

#endif
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
