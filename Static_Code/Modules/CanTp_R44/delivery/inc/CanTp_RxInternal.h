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
**  SRC-MODULE: CanTp_RxInternal.h                                            **
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
** 1.0.4     04-Jul-2022   HieuTM8        CP44-98                             **
** 1.0.3.1   22-Jun-2022   SMKwon         CP44-94                             **
** 1.0.1     28-Feb-2022   HieuTM8        R44-Redmine #20400                  **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/
#ifndef CANTP_RXINTERNAL_H
#define CANTP_RXINTERNAL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: SWS_CanTp_00267 */
/* @Trace: CanTp_SUD_MACRO_006 */
/* SWS_CanTp_00267: Version number macros for checking */
/* AUTOSAR specification version information */
#define CANTP_RXINTERNAL_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANTP_RXINTERNAL_AR_RELEASE_MINOR_VERSION    0x04u
#define CANTP_RXINTERNAL_AR_RELEASE_REVISION_VERSION 0x00u

/* CANTP software version information */
#define CANTP_RXINTERNAL_SW_MAJOR_VERSION            0x01u
#define CANTP_RXINTERNAL_SW_MINOR_VERSION            0x01u

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"
#if (CANTP_RX_NSDU == STD_ON)
extern FUNC(void,
  CANTP_CODE) CanTp_ReceptionComplete(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
    CANTP_VAR) ptrChannelRam, CanTp_NotifResultType result);

#endif
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
#if (CANTP_RX_NSDU == STD_ON)
extern FUNC(void,
  CANTP_CODE) CanTp_CopyRxFrame(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
    CANTP_VAR) ptrChannelRam, P2VAR(uint8, AUTOMATIC, CANTP_VAR) ptrRxSrc);

#endif
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
#if (CANTP_RX_NSDU == STD_ON)
extern FUNC(void,
  CANTP_CODE) CanTp_RequestRxBuffer(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
    CANTP_VAR) ptrChannelRam);

#endif
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#if ((CANTP_RX_PHYSICAL_ADDRESSING == STD_ON) && (CANTP_RX_NSDU == STD_ON))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,
  CANTP_CODE) CanTp_TransmitFc(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
    CANTP_VAR) ptrChannelRam);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, CANTP_CODE) CanTp_EstimateBS(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
    CANTP_VAR) ptrChannelRam,
    P2CONST(CanTp_STminBsType, AUTOMATIC, CANTP_CONST) ptrRxNSduRam,
    uint8 frameSize);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(CANTP_RX_NSDU == STD_ON)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean,
  CANTP_CODE) CanTp_RxCfDlcCheck(P2CONST(CanTp_RxNsduStaticType, AUTOMATIC,
    CANTP_CONST) ptrRxNSdu, uint8 receivedDlc);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (CANTP_RX_NSDU == STD_ON)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean,
  CANTP_CODE) CanTp_RxNewframeDlcCheck(P2CONST(CanTp_RxNsduStaticType, AUTOMATIC,
    CANTP_CONST) ptrRxNSdu, P2CONST(uint8, AUTOMATIC,
    CANTP_CONST) ptrSrc, uint8 receivedDlc);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, CANTP_CODE) CanTp_RxNewframeDlcCheckSingleframe(
  P2CONST(CanTp_RxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrRxNSdu,
  P2CONST(uint8, AUTOMATIC, CANTP_CONST) ptrSrc, 
  P2VAR(PduLengthType, AUTOMATIC, CANIF_VAR) sduLength,
  uint8 receivedDlc);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, CANTP_CODE) CanTp_RxNewframeDlcCheckfirstframe(
  P2CONST(CanTp_RxNsduStaticType, AUTOMATIC, CANTP_CONST) ptrRxNSdu,
  P2CONST(uint8, AUTOMATIC, CANTP_CONST) ptrSrc, 
  P2VAR(PduLengthType, AUTOMATIC, CANIF_VAR) sduLength,
  uint8 receivedDlc);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(BufReq_ReturnType, CANTP_CODE) CanTp_CheckRxBuffer(
  P2VAR(CanTp_ChannelRamType, AUTOMATIC, CANTP_VAR) ptrChannelRam,
  P2VAR(PduLengthType, AUTOMATIC, CANTP_VAR) bufferSize);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define CANTP_START_SEC_CODE
#include "MemMap.h"
#if ((CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
  (CANTP_RX_MIXED_ADDRESS == STD_ON) || (CANTP_TX_EXTENDED_ADDRESS == STD_ON)\
  || (CANTP_RX_MIXED29BIT_ADDRESS == STD_ON) || (CANTP_TX_MIXED29BIT_ADDRESS == STD_ON)\
  || (CANTP_TX_MIXED_ADDRESS == STD_ON)||(STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
  (STD_ON == CANTP_TX_NORMALFIXED_ADDRESS))
extern FUNC(P2CONST(CanTp_RxNSaOrNAeSduMappingType, AUTOMATIC,
    CANTP_CONST), CANTP_CODE) CanTp_RxBinarySearch(P2CONST(
    CanTp_RxNSaOrNAeSduMappingType,
    AUTOMATIC, CANTP_CONST)
  firstSduMap, uint8 size, uint8 rxNsa);

#endif /* End of if (((CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
  (CANTP_RX_MIXED_ADDRESS == STD_ON)) || ((CANTP_TX_EXTENDED_ADDRESS == STD_ON)\
  || (CANTP_RX_MIXED29BIT_ADDRESS == STD_ON)) || ((CANTP_TX_MIXED29BIT_ADDRESS == STD_ON)\
  || (CANTP_TX_MIXED_ADDRESS == STD_ON))) */
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#ifdef CANTP_DYNID_SUPPORT
#if((STD_ON == CANTP_TX_NORMALFIXED_ADDRESS) ||\
(STD_ON == CANTP_RX_NORMALFIXED_ADDRESS) ||\
(STD_ON == CANTP_TX_MIXED29BIT_ADDRESS) ||\
(STD_ON == CANTP_RX_MIXED29BIT_ADDRESS))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(P2CONST(CanTp_RxNSaOrNAeSduMappingType, AUTOMATIC,
        CANTP_CONST), CANTP_CODE) CanTp_RxSpecificBinarySearch(P2CONST(
        CanTp_RxNSaOrNAeSduMappingType, AUTOMATIC, CANTP_CONST)
        ptrFirstSduMap, uint8 size, uint8 addresMode,
        uint8 RxNSa, uint8 RxNTa, uint8 RxNAe);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,
  CANTP_CODE) CanTp_RxPduBufferChk(P2VAR(CanTp_ChannelRamType, AUTOMATIC,
    CANTP_VAR) ptrChannelRam, P2VAR(uint8, AUTOMATIC, CANTP_CONST) ptrRxSrc);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON  == CANTP_RX_NSDU) */

#endif /* CANTP_RXINTERNAL_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

