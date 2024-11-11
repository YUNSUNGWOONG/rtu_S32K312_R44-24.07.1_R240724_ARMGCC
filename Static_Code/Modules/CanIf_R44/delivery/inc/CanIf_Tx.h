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
**  SRC-MODULE: CanIf_Tx.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Header file of CanIf_Tx.c                                     **
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
** 1.1.0    29-Feb-2024    Jh Yang        #CP44-2947                          **
** 1.0.14   13-Jun-2023    HieuTM8        #CP44-2236                          **
** 1.0.10   27-Oct-2022    HieuTM8        #CP44-1008                          **
** 1.0.7    21-Aug-2022    Jiwon Oh       #CP44-751                           **
** 1.0.5    30-Jun-2022    HieuTM8        #CP44-130                           **
** 1.0.4    09-May-2022    Jiwon Oh       #26814,#27128                       **
** 1.0.1    22-Sep-2021    HieuTM8        #20891                              **
** 1.0.0    21-Dec-2020    SJ Kim         Initialization                      **
*******************************************************************************/

#ifndef CANIF_TX_H
#define CANIF_TX_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"                  /* CanInterface header file */
#include "CanIf_Ram.h"              /* Ram header file */
#include "CanIf_IntTypes.h"         /* CanIf Internal Types header file */
#include "CanIf_Error.h"            /* CanIf DET Error file */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_TX_AR_RELEASE_MAJOR_VERSION       4
#define CANIF_TX_AR_RELEASE_MINOR_VERSION       4
#define CANIF_TX_AR_RELEASE_REVISION_VERSION    0

/* Software Version Information */
#define CANIF_TX_SW_MAJOR_VERSION       1
#define CANIF_TX_SW_MINOR_VERSION       1
#define CANIF_TX_SW_REVISION_VERSION    0
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_DETTransmit (
                       VAR(PduIdType, CANIF_VAR) CanTxPduId,
                       P2CONST(PduInfoType, AUTOMATIC, CANIF_CONST) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckPduInfo (
                       #if (((STD_ON == CANIF_SETDYNAMICTXID_API) && (STD_ON == CANIF_META_DATA_SUPPORT)) || (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT))
                       VAR(PduIdType, CANIF_VAR) CanTxPduId,
                       #endif
                       P2CONST(PduInfoType, AUTOMATIC, CANIF_CONST) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_ClearTxQueue (
    P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_TxQueueHandling (
    P2CONST(CanIf_TxBufferType, AUTOMATIC, CANIF_CONST) ptrTxBuffer,
    VAR(CanIf_TxQueueSizeType, CANIF_VAR) txQueueId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_QueueTransmit (
    P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST)ptrTxLpdu);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(CanIf_TxQueueSizeType, CANIF_CODE) CanIf_CheckQueueStatus (
    P2CONST(CanIf_TxBufferType, AUTOMATIC, CANIF_CONST)ptrTxBuffer);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, CANIF_CODE) CanIf_IsInQueue (
                      P2CONST(CanIf_TxBufferType, AUTOMATIC, CANIF_CONST)ptrTxBuffer,
                      P2CONST(Can_PduType, AUTOMATIC, CANIF_CONST) CanPduInfo);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_TxNotification (
    P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu,
    Std_ReturnType result);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_CanWriteService (
#else
extern FUNC(Can_ReturnType, CANIF_CODE) CanIf_CanWriteService (
#endif
#if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    P2CONST(CanIf_TxLpduType, AUTOMATIC, CANIF_CONST) ptrTxLpdu,
#endif
    VAR(Can_HwHandleType, CANIF_VAR) hth,
    P2CONST(Can_PduType, AUTOMATIC, CANIF_CONST) PduInfo);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_ClearTxBuffer (
    VAR(CanIf_TxQueueSizeType, CANIF_VAR) txQueueIndex,
    P2CONST(CanIf_TxBufferType, AUTOMATIC, CANIF_CONST) ptrTxBuffer);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckHthType(
                   VAR(PduIdType, CANIF_VAR) TxPduId,
                   P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"


#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_StoreLpduInQueue (
                     VAR(Can_PduType, CANIF_VAR) CanPduInfo,
                     VAR(PduIdType, CANIF_VAR) TxPduId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_StoreLpduInQueue_CAN_BUSY (
                     P2VAR(Can_PduType, AUTOMATIC, CANIF_VAR) CanPduInfo,
                     VAR(PduIdType, CANIF_VAR) TxPduId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CANIF_TX_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
