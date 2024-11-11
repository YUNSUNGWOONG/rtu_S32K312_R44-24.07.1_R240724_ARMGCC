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
**  SRC-MODULE: PduR_TxTp.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Header file of PduR_TxTp.c                                    **
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
** 1.0.4       11-Aug-2022   PhucNHM     CP44-635                             **
** 1.0.0       04-Dec-2020   AUTOEVER    Initial Version                      **
*******************************************************************************/
#ifndef PDUR_TXTP_H
#define PDUR_TXTP_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: PduR_SUD_FILE_001 */
#include "PduR_IntTypes.h"  /* PDU Router module post-build time header */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyTxData( /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType txPduId, uint8 moduleType,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr,
  P2CONST(RetryInfoType, AUTOMATIC, PDUR_CONST) ptrRetry,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) ptrAvailableDataPtr);
#else
extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyTxData(
  PduIdType txPduId,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) ptrPduInfoPtr,
  P2VAR(RetryInfoType, AUTOMATIC, PDUR_VAR) ptrRetry,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) ptrAvailableDataPtr);
#endif
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_TP_TXCONFIRMATION == STD_ON) */
#endif

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_TP_TXCONFIRMATION == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
extern FUNC(void, PDUR_CODE) PduR_LoTpTxConfirmation(PduIdType txPduId, /* polyspace MISRA-C:2012 5.1 [Not a defect:Low] "This external function is unique" */
  PduIdType moduleType, Std_ReturnType result);
#else
extern FUNC(void, PDUR_CODE) PduR_LoTpTxConfirmation(PduIdType txPduId,
  Std_ReturnType result);
#endif
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_TP_TXCONFIRMATION == STD_ON) */
#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_OFF) */





#endif /* PDUR_TXTP_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
