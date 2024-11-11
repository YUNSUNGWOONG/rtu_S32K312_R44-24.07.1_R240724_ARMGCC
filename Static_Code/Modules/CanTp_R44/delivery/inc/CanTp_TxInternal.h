/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanTp_TxInternal.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : Internal header file for CanTp                                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0     13-Sep-2023   HieuTM8        #CP44-2819                          **
** 1.0.11    15-Jun-2023   HieuTM8        #CP44-2333                          **
** 1.0.3.1   22-Jun-2022   SMKwon         CP44-94                             **
** 1.0.3     30-May-2022   HieuTM8        R44-Redmine #26803                  **
** 1.0.1     28-Feb-2022   HieuTM8        R44-Redmine #20400                  **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/
#ifndef CANTP_TXINTERNAL_H
#define CANTP_TXINTERNAL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp_Cfg.h"            /* CanTp cfg Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: SWS_CanTp_00267 */
/* SWS_CanTp_00267: Version number macros for checking */
/* AUTOSAR specification version information */
/* @Trace: CanTp_SUD_MACRO_007 */
#define CANTP_TXINTERNAL_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANTP_TXINTERNAL_AR_RELEASE_MINOR_VERSION    0x04u
#define CANTP_TXINTERNAL_AR_RELEASE_REVISION_VERSION 0x00u

/* CANTP software version information */
#define CANTP_TXINTERNAL_SW_MAJOR_VERSION            0x01u
#define CANTP_TXINTERNAL_SW_MINOR_VERSION            0x01u

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* @Trace: CanTp_SUD_DATATYPE_007 */
#if (STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_DEV_ERROR_DETECT)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANTP_CODE) CanTp_TxDetCheck(PduIdType
  txSduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_CONST) ptrTxInfo);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of (STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_DEV_ERROR_DETECT) */

#if (CANTP_TX_NSDU == STD_ON)

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,
  CANTP_CODE) CanTp_CanIfTransmit(P2CONST(CanTp_TxNsduStaticType, AUTOMATIC,
    CANTP_CONST) ptrTxNSdu);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANTP_CODE) CanTp_UpdateTxFrameStatus(P2VAR(CanTp_ChannelRamType,
    AUTOMATIC, CANTP_VAR) ptrChannelRam, P2CONST(CanTp_TxNsduStaticType,
    AUTOMATIC, CANTP_CONST) ptrTxNSdu);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,
  CANTP_CODE) CanTp_TransmissionComplete(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
    CANTP_VAR) ptrChannelRam, CanTp_NotifResultType result);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,
  CANTP_CODE) CanTp_RequestCopyTxData(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
    CANTP_VAR) ptrChannelRam);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean,
  CANTP_CODE) CanTp_TxDlcCheck(P2CONST(CanTp_TxNsduStaticType, AUTOMATIC,
    CANTP_CONST) ptrTxNSdu, PduLengthType txDatalength);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#endif /* End of if (CANTP_TX_NSDU == STD_ON) */

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANTP_CODE) CanTp_ProcessRxFc(PduIdType txSduId, P2CONST(
    PduInfoType, AUTOMATIC, CANTP_CONST) ptrRxPduInfor);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#if (STD_ON == CANTP_DEV_ERROR_DETECT)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(StatusType, CANTP_CODE) CanTp_RxDetCheck(PduIdType rxPduId, P2CONST(
    PduInfoType, AUTOMATIC, CANTP_VAR) ptrPduInfo);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, CANTP_CODE) CanTp_CbkTxDetCheck(PduIdType txPduId);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */

#if ((STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)|| \
    (STD_ON == CANTP_RX_NSDU) )
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANTP_CODE) CanTp_ProcessRxData(PduIdType rxSduId, P2CONST( PduInfoType, AUTOMATIC, CANTP_CONST) ptrPduInfo, VAR(
    uint8, AUTOMATIC) bytePos);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) ||
        *   (STD_ON == CANTP_RX_NSDU)) */

#if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, CANTP_CODE) CanTp_ProcessRxCF(PduIdType rxSduId, P2VAR(
    uint8, AUTOMATIC, CANTP_VAR) ptrRxSrc, P2CONST(PduInfoType,
    AUTOMATIC, CANTP_CONST) ptrPduInfo, CanTp_ChannelType channel);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */

#endif /* CANTP_TXINTERNAL_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

