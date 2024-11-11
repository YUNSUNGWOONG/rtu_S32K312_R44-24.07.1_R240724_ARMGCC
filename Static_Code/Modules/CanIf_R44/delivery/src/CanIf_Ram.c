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
**  SRC-MODULE: CanIf_Ram.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of Global RAM Variables                             **
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
** 1.1.0     29-Feb-2024   Jh Yang        #CP44-2947                          **
** 1.0.5     30-Jun-2022   HieuTM8        #CP44-130                           **
** 1.0.2     25-Mar-2022   HieuTM8        #25534                              **
** 1.0.1     22-Sep-2021   HieuTM8        #20891                              **
** 1.0.0     21-Dec-2020   SJ Kim         Initialization                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_Ram.h"              /* CanIf RAM header */
#include "CanIf_IntTypes.h"         /* CanIf Internal types header */
#include "CanIf_PCTypes.h"          /* Pre-compile time header file */
#include "CanIf_Error.h"            /* CanIf Det file */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANIF_RAM_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_RAM_C_AR_RELEASE_MINOR_VERSION    4
#define CANIF_RAM_C_AR_RELEASE_REVISION_VERSION 0

/* File version information */
#define CANIF_RAM_C_SW_MAJOR_VERSION       1
#define CANIF_RAM_C_SW_MINOR_VERSION       1
#define CANIF_RAM_C_SW_REVISION_VERSION    0
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_RAM_AR_RELEASE_MAJOR_VERSION != \
  CANIF_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_RAM.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_RAM_AR_RELEASE_MINOR_VERSION != \
  CANIF_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_RAM.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_RAM_AR_RELEASE_REVISION_VERSION != \
  CANIF_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_RAM.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_RAM_SW_MAJOR_VERSION != CANIF_RAM_C_SW_MAJOR_VERSION)
  #error "CANIF_RAM.c : Mismatch in Software Major Version"
#endif
#if (CANIF_RAM_SW_MINOR_VERSION != CANIF_RAM_C_SW_MINOR_VERSION)
  #error "CANIF_RAM.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store Initialization status of CAN Interface */
VAR (uint8, CANIF_VAR) CanIf_CanIfStatus;
#define CANIF_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_CANTRCV_SUPPORT)
#define CANIF_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Global array for Operation Mode */
VAR (uint8, CANIF_VAR) CanIf_TrcvMode [CANIF_NO_OF_TRANSCEIVER];
#define CANIF_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

#if ((STD_ON == CANIF_CANTRCV_SUPPORT) && (STD_ON == CANIF_DEV_ERROR_DETECT))
#define CANIF_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Global array for Operation Mode */
VAR (uint8, CANIF_VAR) CanIf_OperMode [CANIF_NO_OF_TRANSCEIVER];
#define CANIF_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
#define CANIF_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Global array for Tx L-PDU structure */
VAR(uint8, CANIF_VAR) CanIf_RamInit8Bit[CANIF_NO_OF_TXLPDU];
#define CANIF_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Controller */
VAR (CanIf_ControllerType, CANIF_VAR) CanIf_Controller [CANIF_NO_OF_CONTROLLER];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Controller */
VAR (Can_IdType, CANIF_VAR) CanIf_Metadata = CANIF_ZERO;
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global variable for saving CAN identifier of received message */
VAR(Can_IdType, CANIF_NOINIT_DATA) CanIf_RxCanId;
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if(CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Rx Message Count */
VAR (uint32, CANIF_VAR) CanIf_RxMsgCnt [CANIF_NO_OF_CONTROLLER];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Tx Message Count */
VAR (uint32, CANIF_VAR) CanIf_TxMsgCnt [CANIF_NO_OF_CONTROLLER];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_TX_RX_MONITORING_SUPPORT)
#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for transmit cnt */
VAR (uint8, CANIF_VAR) CanIf_TransmitCnt[CANIF_NO_OF_TXLPDU];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_RX_LPDU)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for receive cnt */
VAR (uint8, CANIF_VAR) CanIf_ReceiveCnt[CANIF_NO_OF_RXLPDU];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Global variable for Tx Pdu status for gateway buffer */
VAR(uint8, CANIF_NOINIT_DATA) CanIf_TxPduGwStatus[CANIF_NO_OF_TXLPDU];
#define CANIF_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

/* define for Post-Build*/
#if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)

#if (STD_ON == CANIF_SETDYNAMICTXID_API)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
P2VAR(Can_IdType, AUTOMATIC, CANIF_VAR_NOINIT) CanIfCanId;
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#define CANIF_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(PduIdType, CANIF_VAR) CanIf_NoofRxLpdu;
VAR(uint16, CANIF_VAR) CanIf_Noofbuffer;
VAR(uint16, CANIF_VAR) CanIf_Noofqueue;
VAR(uint16, CANIF_VAR) CanIf_NoofBasictxlpdu;
VAR(uint16, CANIF_VAR) CanIf_NoofTxLpdu;
VAR(uint16, CANIF_VAR) CanIf_NoofHrh;
VAR(PduIdType, CANIF_VAR) CanIf_NoofdynamicCanId;
VAR(uint16, CANIF_VAR) CanIf_NoofRxnotify;
#define CANIF_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#endif /* #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT) */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
