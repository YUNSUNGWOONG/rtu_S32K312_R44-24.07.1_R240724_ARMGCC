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
**  SRC-MODULE: CanIf_Ram.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Header file of CanIf_Ram.c                                    **
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
** 1.1.0     29-Feb-2024   Jh Yang        #CP44-2946, #CP44-2947              **
** 1.0.5     30-Jun-2022   HieuTM8        #CP44-130                           **
** 1.0.2     25-Mar-2022   HieuTM8        #25534                              **
** 1.0.1     22-Sep-2021   HieuTM8        #20891                              **
** 1.0.0.3   23-Aug-2021   HieuTM8        #19470, #19526                      **
** 1.0.0     21-Dec-2020   SJ Kim         Initialization                      **
*******************************************************************************/

#ifndef CANIF_RAM_H
#define CANIF_RAM_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"                        /* CAN Interface Module Header File */
#include "CanIf_IntTypes.h"               /* CAN Internal Types Header File */
#include "CanIf_PCTypes.h"                /* Pre-compile time header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_RAM_AR_RELEASE_MAJOR_VERSION       4
#define CANIF_RAM_AR_RELEASE_MINOR_VERSION       4
#define CANIF_RAM_AR_RELEASE_REVISION_VERSION    0

/* Software Version Information */
#define CANIF_RAM_SW_MAJOR_VERSION       1
#define CANIF_RAM_SW_MINOR_VERSION       1
#define CANIF_RAM_SW_REVISION_VERSION    0
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store Initialization status of CAN Interface */
extern VAR (uint8, CANIF_VAR) CanIf_CanIfStatus;
#define CANIF_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_CANTRCV_SUPPORT)
#define CANIF_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Global array for Operation Mode */
extern VAR (uint8, CANIF_VAR) CanIf_TrcvMode[CANIF_NO_OF_TRANSCEIVER];
#define CANIF_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

#if ((STD_ON == CANIF_CANTRCV_SUPPORT) && (STD_ON == CANIF_DEV_ERROR_DETECT))
#define CANIF_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Global array for Operation Mode */
extern VAR (uint8, CANIF_VAR) CanIf_OperMode[CANIF_NO_OF_TRANSCEIVER];
#define CANIF_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Controller */
extern VAR (CanIf_ControllerType, CANIF_VAR) CanIf_Controller[CANIF_NO_OF_CONTROLLER];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Controller */
extern VAR (Can_IdType, CANIF_VAR) CanIf_Metadata;
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global variable for saving CAN identifier of received message */
extern VAR(Can_IdType, CANIF_NOINIT_DATA) CanIf_RxCanId;
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, CANIF_NOINIT_DATA) CanIf_TxPduGwStatus[CANIF_NO_OF_TXLPDU];
#define CANIF_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

#if(CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR (uint32, CANIF_VAR) CanIf_RxMsgCnt[CANIF_NO_OF_CONTROLLER];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR (uint32, CANIF_VAR) CanIf_TxMsgCnt[CANIF_NO_OF_CONTROLLER];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_TX_RX_MONITORING_SUPPORT)
#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for transmit cnt */
extern VAR (uint8, CANIF_VAR) CanIf_TransmitCnt[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_RX_LPDU)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for receive cnt */
extern VAR (uint8, CANIF_VAR) CanIf_ReceiveCnt[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if (STD_ON == CANIF_TX_QUEUE)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global variable for the transmit queue */
extern VAR(CanIf_TxQueueType, CANIF_VAR) CanIf_TxQueue[CANIF_NO_OF_TXQUEUE];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_BASIC_CAN_TXPDU)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Queue allocation */
extern VAR (CanIf_TxPduIdType, CANIF_VAR) CanIf_TxPduToQueueMapping[CANIF_NO_OF_BASIC_TXLPDU];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if ((STD_ON == CANIF_READRXPDU_DATA_API) || (STD_ON == CANIF_READRXPDU_NOTIFY_STATUS_API))
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Rx L-PDU notify structure */
extern VAR (CanIf_RxLpduNotifyType, CANIF_VAR) CanIf_RxLpduNotify[CANIF_NO_OF_RXNOTIFY];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_READTXPDU_NOTIFY_STATUS_API)
/* Global array for Tx and Rx notificaton status */ 
#define CANIF_START_SEC_VAR_CLEARED_8
#include"MemMap.h"
extern VAR (uint8, CANIF_VAR) CanIf_BitArray[CANIF_BITARRAY_SIZE];
#define CANIF_STOP_SEC_VAR_CLEARED_8
#include"MemMap.h"
#endif

#if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
#define CANIF_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Global array for Tx L-PDU structure */
extern VAR(uint8, CANIF_VAR) CanIf_RamInit8Bit[CANIF_NO_OF_TXLPDU];
#define CANIF_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

/* define for Post-Build */
#if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)

#if (STD_ON == CANIF_SETDYNAMICTXID_API)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern P2VAR(Can_IdType, AUTOMATIC, CANIF_VAR_NOINIT) CanIfCanId;
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#define CANIF_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
extern VAR(PduIdType, CANIF_VAR) CanIf_NoofRxLpdu;
extern VAR(uint16, CANIF_VAR) CanIf_Noofbuffer;
extern VAR(uint16, CANIF_VAR) CanIf_Noofqueue;
extern VAR(uint16, CANIF_VAR) CanIf_NoofBasictxlpdu;
extern VAR(uint16, CANIF_VAR) CanIf_NoofTxLpdu;
extern VAR(uint16, CANIF_VAR) CanIf_NoofHrh;
extern VAR(PduIdType, CANIF_VAR) CanIf_NoofdynamicCanId;
extern VAR(uint16, CANIF_VAR) CanIf_NoofRxnotify;
#define CANIF_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#endif /* #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT) */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* CANIF_RAM_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
